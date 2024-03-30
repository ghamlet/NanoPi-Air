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

#define MOT2_ID 0x06
#define MOT2_REG_MPOW 24 //W 16u
#define MOT2_REG_ENCM 27 //W 8u
#define MOT2_REG_M1POW 28 //W 16u
#define MOT2_REG_M2POW 30 //W 16u
#define MOT2_REG_M1ENC 32 //R 16u
#define MOT2_REG_M1PSPE 34 //R 16u
#define MOT2_REG_M2ENC 36 //R 16u
#define MOT2_REG_M2PSPE 38 //R 16u
#define MOT2_REG_M1GSPE 40 //W 16u
#define MOT2_REG_M2GSPE 42 //W 16u
#define MOT2_REG_CPER 45 //W 8u
#define MOT2_REG_PIDP 47 //W 8u
#define MOT2_REG_PIDI 48 //W 8u
#define MOT2_REG_PIDD 49 //W 8u





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
    com_result = packet->read2ByteTxRx(port, MOT2_ID, reg, &data, &error);
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
    int16_t speed;

	
    while (true) {
		  for ( speed = 0; speed < 1023; speed++ ) {
			  packetHandler->write2ByteTxRx(portHandler, MOT2_ID, MOT2_REG_M1POW, speed, &dxl_error);   
			  fmt::print("speed M1 = {}\n", speed);
		  }
		  for ( speed = 1023; speed > -1023; speed-- ) {
			  packetHandler->write2ByteTxRx(portHandler, MOT2_ID, MOT2_REG_M1POW, speed, &dxl_error);   
			  fmt::print("speed M1 = {}\n", speed);
		  }
      for ( speed = -1023; speed < 0; speed++ ) {
			  packetHandler->write2ByteTxRx(portHandler, MOT2_ID, MOT2_REG_M1POW, speed, &dxl_error);   
			  fmt::print("speed M1 = {}\n", speed);
		  }
		  for ( speed = 0; speed < 1023; speed++ ) {
			  packetHandler->write2ByteTxRx(portHandler, MOT2_ID, MOT2_REG_M2POW, speed, &dxl_error);   
			  fmt::print("speed M2 = {}\n", speed);
		  }
		  for ( speed = 1023; speed > -1023; speed-- ) {
			  packetHandler->write2ByteTxRx(portHandler, MOT2_ID, MOT2_REG_M2POW, speed, &dxl_error);   
			  fmt::print("speed M2 = {}\n", speed);
		  }
      for ( speed = -1023; speed < 0; speed++ ) {
			  packetHandler->write2ByteTxRx(portHandler, MOT2_ID, MOT2_REG_M2POW, speed, &dxl_error);   
			  fmt::print("speed M2 = {}\n", speed);
		  }
        sleep(10);
    }

    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}