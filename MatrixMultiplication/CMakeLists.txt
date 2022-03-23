cmake_minimum_required(VERSION 3.18)
project("Matrix Multiplication algorithms")


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories($(CMAKE_CURRENT_SOURCE_DIR)/source)

add_executable(matrix_mult source/main.cpp)
