cmake_minimum_required(VERSION 3.15)

project(cache)
set(CMAKE_CXX_STANDARD 20)
add_executable(cache src/main.cpp
                    headers/LRUCache.h)
target_include_directories(cache PRIVATE headers)
