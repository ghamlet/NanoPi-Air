cmake_minimum_required(VERSION 3.14)
project(example_01_led)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)



add_executable(example_01_led)

target_sources(example_01_led PRIVATE
    example_01_led.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_01_led PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_01_led PRIVATE -Wno-psabi)
target_include_directories(example_01_led PRIVATE
    ../src
    ../src/dynamixel_sdk
)