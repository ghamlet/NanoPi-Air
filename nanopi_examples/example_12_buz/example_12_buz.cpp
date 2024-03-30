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

#define BUZ_ID 0x18
#define BUZ_REG_FRE 26 //W 16u
#define BUZ_REG_POR 28 //W 8u

uint16_t C3 = 1046;
uint16_t D3 = 1174;
uint16_t E3 = 1318;
uint16_t F3 = 1397;
uint16_t G3 = 1600;
uint16_t A3 = 1720;
uint16_t B3 = 1975;
uint16_t C4 = 2093;

uint16_t note_table[8] = {C3, D3, E3, F3, G3, A3, B3, C4};

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
 
  packetHandler->write1ByteTxRx(portHandler, BUZ_ID, BUZ_REG_POR, 128, &dxl_error);

 for ( int i = 0; i < 8; i++ ) {
        packetHandler->write2ByteTxRx(portHandler, BUZ_ID, BUZ_REG_FRE, note_table[i], &dxl_error);
        packetHandler->write1ByteTxRx(portHandler, BUZ_ID, BUZ_REG_POR, 128, &dxl_error);
        fmt::print("Buzzer play note to frequency {}\n ", note_table[i]);
        sleep(1); 
        packetHandler->write1ByteTxRx(portHandler, BUZ_ID, BUZ_REG_POR, 0, &dxl_error);
        sleep(1); 
    }
    
    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}