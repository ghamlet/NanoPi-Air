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
#define PROTOCOL 1.0
#define BAUDRATE 1000000

#define SER_ID 0x01
#define SER_REG_ID 3 //WR 8u
#define SER_REG_BAU 4 //WR 8u
#define SER_REG_RET 5 //WR 8u
#define SER_REG_CW_LIM 6 //WR 16u
#define SER_REG_CCW_LIM 8 //WR 16u
#define SER_REG_PRE_POS 36 //R 16u
#define SER_REG_PRE_SPE 38 //R 16u
#define SER_REG_PRE_LOA 40 //R 16u
#define SER_REG_PRE_TEM 43 //R 8u
#define SER_REG_MOV_SPE 32 //WR 16u
#define SER_REG_GOA_POS 30 //WR 16u
#define SER_REG_TOR 24 //WR 8u




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


uint16_t Read1Byte(dynamixel::PortHandler *port, dynamixel::PacketHandler *packet, uint8_t reg = 0, std::string announce = "" ) {
    uint8_t data = 0;
    uint8_t error = 0;
    int com_result = 0;
    com_result = packet->read1ByteTxRx(port, SER_ID, reg, &data, &error);
    return data;
}

uint16_t Read2Byte(dynamixel::PortHandler *port, dynamixel::PacketHandler *packet, uint8_t reg = 0, std::string announce = "" ) {
    uint16_t data = 0;
    uint8_t error = 0;
    int com_result = 0;
    com_result = packet->read2ByteTxRx(port, SER_ID, reg, &data, &error);
    return data;
}

int main() {
    portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL);
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
	
  uint8_t dxl_error;
 
	packetHandler->write2ByteTxRx(portHandler, SER_ID, SER_REG_CW_LIM, 0, &dxl_error);
	packetHandler->write2ByteTxRx(portHandler, SER_ID, SER_REG_CCW_LIM, 0, &dxl_error);
	packetHandler->write1ByteTxRx(portHandler, SER_ID, SER_REG_TOR, 1, &dxl_error);
	
	fmt::print("Start wheel mode \n ");

    while (true) {
		packetHandler->write2ByteTxRx(portHandler, SER_ID, SER_REG_MOV_SPE, 2047, &dxl_error);
		fmt::print("Moving speed = {}\n ", Read2Byte(portHandler, packetHandler, SER_REG_MOV_SPE, ""));
		sleep(3);
		packetHandler->write2ByteTxRx(portHandler, SER_ID, SER_REG_MOV_SPE, 1023, &dxl_error);
		fmt::print("Moving speed = {}\n ", Read2Byte(portHandler, packetHandler, SER_REG_MOV_SPE, ""));
        sleep(3);
    }

    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}