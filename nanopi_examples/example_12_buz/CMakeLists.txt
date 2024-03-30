cmake_minimum_required(VERSION 3.14)
project(example_12_buz)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_12_buz)

target_sources(example_12_buz PRIVATE
    example_12_buz.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_12_buz PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_12_buz PRIVATE -Wno-psabi)
target_include_directories(example_12_buz PRIVATE
    ../src
    ../src/dynamixel_sdk
)