cmake_minimum_required(VERSION 3.14)
project(example_02_RGB)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_02_RGB)

target_sources(example_02_RGB PRIVATE
    example_02_RGB.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_02_RGB PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_02_RGB PRIVATE -Wno-psabi)
target_include_directories(example_02_RGB PRIVATE
    ../src
    ../src/dynamixel_sdk
)