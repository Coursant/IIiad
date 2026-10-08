cmake_minimum_required(VERSION 3.16)
project(WonderTraderLab VERSION 0.1.0 LANGUAGES CXX)

add_executable(wondertrader_lab src/main.cpp)
set_target_properties(wondertrader_lab PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_compile_options(wondertrader_lab PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow
)
