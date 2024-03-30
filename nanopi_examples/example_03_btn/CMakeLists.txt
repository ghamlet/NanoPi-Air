cmake_minimum_required(VERSION 3.14)
project(example_03_btn)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_03_btn)

target_sources(example_03_btn PRIVATE
    example_03_btn.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_03_btn PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_03_btn PRIVATE -Wno-psabi)
target_include_directories(example_03_btn PRIVATE
    ../src
    ../src/dynamixel_sdk
)