cmake_minimum_required(VERSION 3.14)
project(example_13_mot1)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_13_mot1)

target_sources(example_13_mot1 PRIVATE
    example_13_mot1.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_13_mot1 PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_13_mot1 PRIVATE -Wno-psabi)
target_include_directories(example_13_mot1 PRIVATE
    ../src
    ../src/dynamixel_sdk
)