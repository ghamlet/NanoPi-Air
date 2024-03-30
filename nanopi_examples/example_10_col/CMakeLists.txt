cmake_minimum_required(VERSION 3.14)
project(example_10_col)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_10_col)

target_sources(example_10_col PRIVATE
    example_10_col.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_10_col PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_10_col PRIVATE -Wno-psabi)
target_include_directories(example_10_col PRIVATE
    ../src
    ../src/dynamixel_sdk
)