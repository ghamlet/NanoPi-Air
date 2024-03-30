cmake_minimum_required(VERSION 3.14)
project(example_08_noi)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

add_executable(example_08_noi)

target_sources(example_08_noi PRIVATE
    example_08_noi.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_08_noi PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_08_noi PRIVATE -Wno-psabi)
target_include_directories(example_08_noi PRIVATE
    ../src
    ../src/dynamixel_sdk
)