cmake_minimum_required(VERSION 3.14)
project(RunzhongMachine)

set(CMAKE_CXX_STANDARD 17)
include_directories(.)

add_executable(lrznb
        main.cpp
        RunzhongMachine/lexical_analysis.hpp
        RunzhongMachine/RunzhongMachine.hpp
        RunzhongMachine/utility.hpp RunzhongMachine/token.hpp RunzhongMachine/ll1.hpp)