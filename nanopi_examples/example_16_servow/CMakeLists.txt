cmake_minimum_required(VERSION 3.14)
project(example_16_servow)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_16_servow)

target_sources(example_16_servow PRIVATE
    example_16_servow.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_16_servow PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_16_servow PRIVATE -Wno-psabi)
target_include_directories(example_16_servow PRIVATE
    ../src
    ../src/dynamixel_sdk
)