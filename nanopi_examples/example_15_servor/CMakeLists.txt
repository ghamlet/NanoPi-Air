cmake_minimum_required(VERSION 3.14)
project(example_15_servor)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_15_servor)

target_sources(example_15_servor PRIVATE
    example_15_servor.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_15_servor PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_15_servor PRIVATE -Wno-psabi)
target_include_directories(example_15_servor PRIVATE
    ../src
    ../src/dynamixel_sdk
)