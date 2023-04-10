cmake_minimum_required(VERSION 3.13)
project(driver_mcu C)

set(target "driver_mcu")

set(driver_mcu_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(driver_mcu_src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clock_ll.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mcu_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/qspi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/uart.c
)

add_library(${target} ${driver_mcu_src})
target_include_directories(${target} PUBLIC ${driver_mcu_inc})
target_link_libraries(${target} PUBLIC cmsis)
target_link_libraries(${target} PRIVATE debugLib)
