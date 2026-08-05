cmake_minimum_required(VERSION 3.16)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")

include(pico_sdk_import.cmake)

project(macro_deck C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(macro_deck
    src/main.cpp
    src/application.cpp
)

target_include_directories(macro_deck PRIVATE
    src
)

target_link_libraries(macro_deck
    pico_stdlib
)

pico_add_extra_outputs(macro_deck)

pico_enable_stdio_usb(macro_deck 0)
pico_enable_stdio_uart(macro_deck 0)