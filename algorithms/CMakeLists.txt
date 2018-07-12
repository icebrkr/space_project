cmake_minimum_required(VERSION 3.1)
project(algorithms_project)

# eqrlier than 3.1
#add_compile_options(-std=c++11)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(graph)

add_executable(cut_rod cut_rod.cpp)

