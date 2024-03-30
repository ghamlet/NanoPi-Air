cmake_minimum_required(VERSION 3.14)
project(example_06_pot)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_06_pot)

target_sources(example_06_pot PRIVATE
    example_06_pot.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_06_pot PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_06_pot PRIVATE -Wno-psabi)
target_include_directories(example_06_pot PRIVATE
    ../src
    ../src/dynamixel_sdk
)