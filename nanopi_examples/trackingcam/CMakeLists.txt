cmake_minimum_required(VERSION 3.14)
project(trackingcam3)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(trackingcam3)

target_sources(trackingcam3 PRIVATE
    trackingcam3.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(trackingcam3 PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(trackingcam3 PRIVATE -Wno-psabi)
target_include_directories(trackingcam3 PRIVATE
    ../src
    ../src/dynamixel_sdk
)