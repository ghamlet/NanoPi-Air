cmake_minimum_required(VERSION 3.14)
project(example_19_spi)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)



add_executable(example_19_spi)

target_sources(example_19_spi PRIVATE
    example_19_spi.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(example_19_spi PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_19_spi PRIVATE -Wno-psabi)
target_include_directories(example_19_spi PRIVATE
    ../src
    ../src/dynamixel_sdk
)