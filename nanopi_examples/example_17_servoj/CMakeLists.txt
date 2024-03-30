cmake_minimum_required(VERSION 3.14)
project(example_17_servoj)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_17_servoj)

target_sources(example_17_servoj PRIVATE
    example_17_servoj.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_17_servoj PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_17_servoj PRIVATE -Wno-psabi)
target_include_directories(example_17_servoj PRIVATE
    ../src
    ../src/dynamixel_sdk
)