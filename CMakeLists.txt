cmake_minimum_required(VERSION 3.20)
project(06_Crible)

set(CMAKE_CXX_STANDARD 20)

add_executable(06_Crible main.cpp sieve.h inputValidation.h sieve.cpp inputValidation.cpp utilities.h utilities.cpp)
