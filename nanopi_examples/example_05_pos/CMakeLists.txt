cmake_minimum_required(VERSION 3.14)
project(example_05_pos)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_05_pos)

target_sources(example_05_pos PRIVATE
    example_05_pos.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_05_pos PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_05_pos PRIVATE -Wno-psabi)
target_include_directories(example_05_pos PRIVATE
    ../src
    ../src/dynamixel_sdk
)