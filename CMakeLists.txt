cmake_minimum_required(VERSION 3.20)

project(libdevic C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(lib)
add_subdirectory(examples)
