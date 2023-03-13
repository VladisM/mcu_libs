cmake_minimum_required(VERSION 3.13)
project(driver_dev C)

set(target "driver_dev")

set(driver_dev_inc
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(driver_dev_src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/button.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/eeprom.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/led.c
)

add_library(${target} ${driver_dev_src})
target_include_directories(${target} PUBLIC ${driver_dev_inc})
target_link_libraries(${target} PRIVATE driver_mcu debugLib)
