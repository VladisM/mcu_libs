function(mcu_family_select)

    if(
        "${MCU}" STREQUAL "STM32F405xx" OR
        "${MCU}" STREQUAL "STM32F415xx" OR
        "${MCU}" STREQUAL "STM32F407xx" OR
        "${MCU}" STREQUAL "STM32F417xx" OR
        "${MCU}" STREQUAL "STM32F427xx" OR
        "${MCU}" STREQUAL "STM32F437xx" OR
        "${MCU}" STREQUAL "STM32F429xx" OR
        "${MCU}" STREQUAL "STM32F439xx" OR
        "${MCU}" STREQUAL "STM32F401xC" OR
        "${MCU}" STREQUAL "STM32F401xE" OR
        "${MCU}" STREQUAL "STM32F410Tx" OR
        "${MCU}" STREQUAL "STM32F410Cx" OR
        "${MCU}" STREQUAL "STM32F410Rx" OR
        "${MCU}" STREQUAL "STM32F411xE" OR
        "${MCU}" STREQUAL "STM32F446xx" OR
        "${MCU}" STREQUAL "STM32F469xx" OR
        "${MCU}" STREQUAL "STM32F479xx" OR
        "${MCU}" STREQUAL "STM32F412Cx" OR
        "${MCU}" STREQUAL "STM32F412Rx" OR
        "${MCU}" STREQUAL "STM32F412Vx" OR
        "${MCU}" STREQUAL "STM32F412Zx" OR
        "${MCU}" STREQUAL "STM32F413xx" OR
        "${MCU}" STREQUAL "STM32F423xx")

        set(MCU_FAMILY "STM32F4" PARENT_SCOPE)

    else()

        message(FATAL_ERROR "Selected MCU didn't found! Please set your MCU variable correctly.")

    endif()

endfunction()
