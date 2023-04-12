# STM32 MCU Libraries

This is very simple library for STM32 MCUs. It is using CMSIS approach.

## Motivation

Don't look for deep meaning. This simply exist because I don't like HAL
solution provided by STM32 (also known as CUBE). And wanted to have
something easy to use for my personal hobby projects.

Also it was nice opportunity to demystify some of the peripherals that
STM32 platform offers.

## How to use it

Subdirectory src contain all libraries. Each library have custom
CMakeLists.txt. Include directory that you are interested in and link
library to your target.

Don't forget to set your `${MCU}` variable in CMake correctly, please
take a look at `cmake/mcu_family_select.cmake`.

Most of the drivers presented in this repository are not complete.
They are providing only very basic functionality and there are many
many bugs.

## License

Copyright © 2023 Bc. Vladislav Mlejnecký <v.mlejnecky@seznam.cz>

This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar. See COPYING file for more details.
