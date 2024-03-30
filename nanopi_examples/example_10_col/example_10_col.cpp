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

#define COL_ID 0x04                 
#define COL_REG_CLE 24 //R 16u     
#define COL_REG_RED 26 //R 16u        
#define COL_REG_GRE 28 //R 16u        
#define COL_REG_BLU 30 //R 16u       
#define COL_REG_LUX 32 //R 16u        
#define COL_REG_CTE 34 //R 16u        
#define COL_REG_HUE 36 //R 16u        
#define COL_REG_GAI 38 //R 8u         
#define COL_REG_COL 40 //R 8u         
#define COL_REG_LIG 42 //W 8u         
#define COL_REG_BLA 46 //W 16u       
#define COL_REG_WHI 48 //W 8u         


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
    com_result = packet->read2ByteTxRx(port, COL_ID, reg, &data, &error);
    return data;
}

uint16_t Read1Byte(dynamixel::PortHandler *port, dynamixel::PacketHandler *packet, uint8_t reg = 0, std::string announce = "" ) {
    uint8_t data = 0;
    uint8_t error = 0;
    int com_result = 0;
    com_result = packet->read1ByteTxRx(port, COL_ID, reg, &data, &error);
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
    packetHandler->write1ByteTxRx(portHandler, COL_ID, COL_REG_LIG, 0, &dxl_error);
    packetHandler->write2ByteTxRx(portHandler, COL_ID, COL_REG_BLA, 850, &dxl_error);
    packetHandler->write1ByteTxRx(portHandler, COL_ID, COL_REG_WHI, 7, &dxl_error);

    while (true) {
	    	fmt::print("CLEAR data is {}\n ", Read2Byte(portHandler, packetHandler, COL_REG_CLE, ""));
        fmt::print("RED data is {}\n ", Read2Byte(portHandler, packetHandler, COL_REG_RED, ""));
        fmt::print("GREEN data is {}\n ", Read2Byte(portHandler, packetHandler, COL_REG_GRE, ""));
        fmt::print("BLUE data is {}\n ", Read2Byte(portHandler, packetHandler, COL_REG_BLU, ""));
        fmt::print("LUX data is {}\n ", Read2Byte(portHandler, packetHandler, COL_REG_LUX, ""));
        fmt::print("CALVIN TEMP data is {}\n ", Read2Byte(portHandler, packetHandler, COL_REG_CTE, ""));
        fmt::print("GAIN data is {}\n ", Read1Byte(portHandler, packetHandler, COL_REG_GAI, ""));
        fmt::print("COLOR data is {}\n\n ", Read2Byte(portHandler, packetHandler, COL_REG_COL, ""));\
        sleep(1);
    }
    portHandler->closePort();
    fmt::print("CLOSED PORT\n");
    return 0;
}