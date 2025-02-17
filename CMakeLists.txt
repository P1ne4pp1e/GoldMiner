cmake_minimum_required(VERSION 3.30)
project(GoldMiner)

set(CMAKE_CXX_STANDARD 20)

include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)

add_executable(GoldMiner main.cpp)
