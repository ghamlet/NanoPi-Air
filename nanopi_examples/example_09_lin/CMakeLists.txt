cmake_minimum_required(VERSION 3.14)
project(example_09_lin)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_09_lin)

target_sources(example_09_lin PRIVATE
    example_09_lin.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_09_lin PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_09_lin PRIVATE -Wno-psabi)
target_include_directories(example_09_lin PRIVATE
    ../src
    ../src/dynamixel_sdk
)