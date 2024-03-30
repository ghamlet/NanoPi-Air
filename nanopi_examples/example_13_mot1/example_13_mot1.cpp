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

#define MOT1_ID 0x05
#define MOT1_REG_MPOW 24 //W 16u
#define MOT1_REG_ENCM 27 //W 8u
#define MOT1_REG_POW 28 //W 16u
#define MOT1_REG_ENC 32 //R 16u
#define MOT1_REG_PSPE 34 //R 16u
#define MOT1_REG_GSPE 40 //W 16u
#define MOT1_REG_CPER 45 //W 8u
#define MOT1_REG_PIDP 47 //W 8u
#define MOT1_REG_PIDI 48 //W 8u
#define MOT1_REG_PIDD 49 //W 8u





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
    com_result = packet->read2ByteTxRx(port, MOT1_ID, reg, &data, &error);
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
    int16_t forward = 1023;
    int16_t backward = -1023;
    

	
    while (true) {
      packetHandler->write2ByteTxRx(portHandler, MOT1_ID, MOT1_REG_POW, 0, &dxl_error);   
      fmt::print("STOP\n");
	    packetHandler->write2ByteTxRx(portHandler, MOT1_ID, MOT1_REG_POW, 1023, &dxl_error);
      fmt::print("Rotate clockwise\n");
      sleep(1);
      packetHandler->write2ByteTxRx(portHandler, MOT1_ID, MOT1_REG_POW, 0, &dxl_error);  
      fmt::print("STOP\n");
		  packetHandler->write2ByteTxRx(portHandler, MOT1_ID, MOT1_REG_POW, -1023, &dxl_error);
      fmt::print("Rotate counterclockwise\n");  
      sleep(1);
    }

    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}