cmake_minimum_required(VERSION 3.14)
project(example_11_hum)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_11_hum)

target_sources(example_11_hum PRIVATE
    example_11_hum.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_11_hum PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_11_hum PRIVATE -Wno-psabi)
target_include_directories(example_11_hum PRIVATE
    ../src
    ../src/dynamixel_sdk
)