cmake_minimum_required(VERSION 3.14)
project(example_14_mot2)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_14_mot2)

target_sources(example_14_mot2 PRIVATE
    example_14_mot2.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_14_mot2 PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_14_mot2 PRIVATE -Wno-psabi)
target_include_directories(example_14_mot2 PRIVATE
    ../src
    ../src/dynamixel_sdk
)