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

#define TRA_ID 0x01
#define TRA_REG_TYPE 16 //R 8u
#define TRA_REG_PADDING 17 //R 8u
#define TRA_REG_CX 18 //R 16u
#define TRA_REG_CY 20 //R 16u
#define TRA_REG_AREA 22 //R 16u
#define TRA_REG_LEFT 24 //R 16u
#define TRA_REG_RIGHT 26 //R 16u
#define TRA_REG_TOP 28 //R 16u
#define TRA_REG_BOTTOM 30 //R 16u






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
    com_result = packet->read1ByteTxRx(port, TRA_ID, reg, &data, &error);
    return data;
}

uint16_t Read2Byte(dynamixel::PortHandler *port, dynamixel::PacketHandler *packet, uint8_t reg = 0, std::string announce = "" ) {
    uint16_t data = 0;
    uint8_t error = 0;
    int com_result = 0;
    com_result = packet->read2ByteTxRx(port, TRA_ID, reg, &data, &error);
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

#define TRA_REG_TYPE 16 //R 8u
#define TRA_REG_PADDING 17 //R 8u
#define TRA_REG_CX 18 //R 16u
#define TRA_REG_CY 20 //R 16u
#define TRA_REG_AREA 22 //R 16u
#define TRA_REG_LEFT 24 //R 16u
#define TRA_REG_RIGHT 26 //R 16u
#define TRA_REG_TOP 28 //R 16u
#define TRA_REG_BOTTOM 30 //R 16u

    while (true) {

		fmt::print("Blob 1 type     {}\n ", Read1Byte(portHandler, packetHandler, TRA_REG_TYPE, ""));
		fmt::print("Blob 1 padding  {}\n ", Read1Byte(portHandler, packetHandler, TRA_REG_PADDING, ""));
		fmt::print("Blob 1 cx       {}\n ", Read2Byte(portHandler, packetHandler, TRA_REG_CX, ""));
		fmt::print("Blob 1 cy       {}\n ", Read2Byte(portHandler, packetHandler, TRA_REG_CY, ""));
		fmt::print("Blob 1 area     {}\n ", Read2Byte(portHandler, packetHandler, TRA_REG_AREA, ""));
		fmt::print("Blob 1 left     {}\n ", Read2Byte(portHandler, packetHandler, TRA_REG_LEFT, ""));
		fmt::print("Blob 1 right    {}\n ", Read2Byte(portHandler, packetHandler, TRA_REG_RIGHT, ""));
		fmt::print("Blob 1 top      {}\n ", Read2Byte(portHandler, packetHandler, TRA_REG_TOP, ""));
		fmt::print("Blob 1 bottom   {}\n ", Read2Byte(portHandler, packetHandler, TRA_REG_BOTTOM, ""));

        sleep(1);
    }

    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}