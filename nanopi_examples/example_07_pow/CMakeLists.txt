cmake_minimum_required(VERSION 3.14)
project(example_07_for)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_07_for)

target_sources(example_07_for PRIVATE
    example_07_for.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_07_for PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_07_for PRIVATE -Wno-psabi)
target_include_directories(example_07_for PRIVATE
    ../src
    ../src/dynamixel_sdk
)