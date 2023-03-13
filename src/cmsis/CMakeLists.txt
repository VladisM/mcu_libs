cmake_minimum_required(VERSION 3.13)
project(mylibs_cmsis C)

set(target "cmsis")

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/mcu_family_select.cmake)

set(cmsis_inc)
set(cmsis_src)

mcu_family_select()

if("${MCU_FAMILY}" STREQUAL "STM32F4")
    set(cmsis_src ${cmsis_src} ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4/Source/Templates/system_stm32f4xx.c)
    set(cmsis_inc ${cmsis_inc} ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4/Include/)
else()
    message(FATAL_ERROR "Unknown family of CPU! Please select correct supported MCU!")
endif()

set(cmsis_inc ${cmsis_inc} ${CMAKE_CURRENT_SOURCE_DIR}/)
set(cmsis_inc ${cmsis_inc} ${CMAKE_CURRENT_SOURCE_DIR}/arm/CMSIS/Core/Include/)

add_library(${target} ${cmsis_src})
target_include_directories(${target} PUBLIC ${cmsis_inc})
target_compile_definitions(${target} PUBLIC ${MCU_FAMILY})
