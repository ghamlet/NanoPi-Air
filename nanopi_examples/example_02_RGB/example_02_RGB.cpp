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


#define RGB_ID 0x15
#define RGB_G 26 //W 8u
#define RGB_R 27 //W 8u
#define RGB_B 28 //W 8u

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

    uint8_t RGB_addreses[3] = {RGB_G, RGB_R, RGB_B};
    const char* RGB_data[3] = {"GREEN", "RED", "BLUE"};
    uint8_t dxl_error;

    for ( int i = 0; i < 3; i++ ) {

        packetHandler->write1ByteTxRx(portHandler, RGB_ID, RGB_addreses[i], 254, &dxl_error);
        fmt::print("{} LED ON \n", RGB_data[i]);
        sleep(1);
        packetHandler->write1ByteTxRx(portHandler, RGB_ID, RGB_addreses[i], 0, &dxl_error);
        fmt::print("{} LED OFF \n", RGB_data[i]);
        sleep(1);
        
    }
    
    fmt::print("Finish \n");
    
    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}