cmake_minimum_required(VERSION 3.26)
project(adventOfCode2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(adventOfCode2023 main.cpp util.cpp one/one.cpp two/two.cpp
        three/three.cpp
        three/schematic.cpp
        four/four.cpp
        five/five.cpp
        five/mapchain.hpp
        seven/seven.cpp
        eight/eight.cpp
        eight/graph.cpp
        eight/graph.hpp
        nine/nine.cpp
        ten/ten.cpp
)
target_include_directories(adventOfCode2023 PRIVATE inc)