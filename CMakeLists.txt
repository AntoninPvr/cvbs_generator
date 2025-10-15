cmake_minimum_required(VERSION 3.10)
project(cvbs_generator)

set(CMAKE_CXX_STANDARD 17)

add_executable(cvbs_generator src/main.cpp)

target_include_directories(cvbs_generator PRIVATE inc)