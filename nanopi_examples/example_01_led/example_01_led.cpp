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

#define LED_ID 0x09
#define LED_REG 0x1A //W 8u


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


int main() {
    portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL);
    if (portHandler->setBaudRate(BAUDRATE)) {
        fmt::print("SUCCESS : set BAUDRATE to {}\n",BAUDRATE);
    } else {
        fmt::print("FAILURE : set BAUDRATE to {}\n",BAUDRATE);
        return 1;
    }
    if (portHandler->openPort()) {
        fmt::print("SUCCESS : open PORT {}\n", DEVICENAME);
    } else {
        fmt::print("FAILURE : open PORT {}\n", DEVICENAME);
    }

    uint8_t dxl_error;

    for ( int i = 0; i < 3; i++ ) {

        packetHandler->write1ByteTxRx(portHandler, LED_ID, LED_REG, 254, &dxl_error);
        fmt::print("LED ON\n");
        sleep(1);
        packetHandler->write1ByteTxRx(portHandler, LED_ID, LED_REG, 0, &dxl_error);
        fmt::print("LED OFF\n");
        sleep(1);
        
    }
    fmt::print("Finish\n");
    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}


