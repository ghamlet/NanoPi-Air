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
#define BAUDRATE 57600

#define POS_ID 0x02
#define POS_REG1 26 //R 8u
#define POS_REG2 27 //R 8u

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


uint8_t Read1Byte(dynamixel::PortHandler *port, dynamixel::PacketHandler *packet, uint8_t reg = 0, std::string announce = "" ) {
    uint8_t data = 0;
    uint8_t error = 0;
    int com_result = 0;
    com_result = packet->read1ByteTxRx(port, POS_ID, reg, &data, &error);
    if (com_result != COMM_SUCCESS) {
        fmt::print("FAILURE : {} : {}\n", announce, com_result);
    } else {
        fmt::print("SUCCESS : {} : {}\n", announce, data);
    }
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

    uint8_t pos1Data;
  	uint8_t pos2Data;

    while (true) {
        pos1Data = Read1Byte(portHandler, packetHandler, POS_REG1, "");
		    pos2Data = Read1Byte(portHandler, packetHandler, POS_REG2, "");
        
		fmt::print("position sensor state is x = {} y = {}\n ", pos1Data, pos2Data);
        sleep(1);
    }

    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}