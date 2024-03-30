#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <thread>

#include "dynamixel_sdk.h"
#include "fmt/format.h"

#define DEVICENAME "/dev/ttyS2"
#define PROTOHUM 1.0
#define BAUDRATE 57600

#define HUM_ID 0x16
#define HUM_REG_RH_INT 24 //R 8u
#define HUM_REG_RH_DEC 26 //R 8u
#define HUM_REG_TEM_INT 28 //R 8u
#define HUM_REG_TEM_DEC 30 //R 8u
#define HUM_REG_TEM_16 34 //R 16u





dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

void setRegister(int id, int reg, int size, int value) {
    fmt::print("setRegister\n   DEVICE: {}\n   REG: {}\n   SIZE: {}\n   VALUE: {}\n", id, reg, size, value);
    int retry = 0;
    do {
        if ( packetHandler->writeTxRx(portHandler, id, reg, size, (uint8_t *)&value) == COMM_SUCCESS ) {
            fmt::print("--->OK\n");
            return;
        }
        retry++;
    }
    while ( retry < 3 );
    fmt::print("--->FAILED\n");
}


uint16_t Read2Byte(dynamixel::PortHandler *port, dynamixel::PacketHandler *packet, uint8_t reg = 0, std::string announce = "" ) {
    uint16_t data = 0;
    uint8_t error = 0;
    int com_result = 0;
    com_result = packet->read2ByteTxRx(port, HUM_ID, reg, &data, &error);
    return data;
}

int main() {
    portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOHUM);
    if (portHandler->setBaudRate(BAUDRATE)) {
        fmt::print("SUCCESS: set BAUDRATE to {}\n",BAUDRATE);
    } else {
        fmt::print("FAILED: set BAUDRATE to {}\n",BAUDRATE);
        return 1;
    }
    if (portHandler->openPort()) {
        fmt::print("SUCCESS: open PORT {}\n", DEVICENAME);
    } else {
        fmt::print("FAILED: open PORT {}\n", DEVICENAME);
    }

	uint8_t rh_int;
	uint8_t rh_dec;
	uint8_t temp_int;
	uint8_t temp_dec;
  float temp_16;
	
    while (true) {
    rh_int = Read2Byte(portHandler, packetHandler, HUM_REG_RH_INT, "");
		rh_dec = Read2Byte(portHandler, packetHandler, HUM_REG_RH_DEC, "");
		temp_int = Read2Byte(portHandler, packetHandler, HUM_REG_TEM_INT, "");
		temp_dec = Read2Byte(portHandler, packetHandler, HUM_REG_TEM_DEC, "");
		temp_16 = Read2Byte(portHandler, packetHandler, HUM_REG_TEM_16, "")/10.0;
		fmt::print("HUMIDITY is {},{} %\n ", rh_int, rh_dec);
    fmt::print("TEMPERATURE is {},{} *C\n ", temp_int, temp_dec);
    fmt::print("TEMP16 data is {}\n\n ", temp_16);

        sleep(1);
    }

    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}