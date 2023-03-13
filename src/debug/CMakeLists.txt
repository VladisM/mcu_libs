cmake_minimum_required(VERSION 3.13)
project(debug C)

set(target "debugLib")

set(debug_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(debug_src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debug.c
)

add_library(${target} ${debug_src})
target_include_directories(${target} PUBLIC ${debug_inc})
