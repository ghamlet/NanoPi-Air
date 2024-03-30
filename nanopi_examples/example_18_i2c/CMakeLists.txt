cmake_minimum_required(VERSION 3.14)
project(example_18_i2c)

file(GLOB SRC_DYNAMIXEL
     "../src/dynamixel_sdk/*.cpp"
)

file(GLOB SRC_SSD1306
     "../src/libssd1306/*.cxx"
)

add_executable(example_18_i2c)

target_sources(example_18_i2c PRIVATE
    example_18_i2c.cpp
    ${SRC_DYNAMIXEL}
    ${SRC_SSD1306}
)

target_compile_definitions(example_18_i2c PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(example_18_i2c PRIVATE -Wno-psabi)
target_include_directories(example_18_i2c PRIVATE
    ../src
    ../src/dynamixel_sdk
    ../src/libssd1306
)