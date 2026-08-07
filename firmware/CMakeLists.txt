cmake_minimum_required(VERSION 3.16)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")

include(pico_sdk_import.cmake)

project(macro_deck C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(macro_deck
    src/main.cpp
    src/app/application.cpp
    src/hal/gpio.cpp
    src/hal/periodic_timer.cpp
    src/hal/one_shot_timer.cpp
    src/hal/clock.cpp
    src/hal/digital_input.cpp
    src/hal/digital_output.cpp
    src/hal/pwm_output.cpp
    src/devices/led.cpp
    src/devices/button.cpp
    src/keyboard/keyboard_matrix.cpp
    src/keyboard/keyboard_controller.cpp
    src/usb/usb_device.cpp
    src/usb/usb_descriptors.c
    src/config/default_profile.cpp
    src/actions/action.cpp
    src/actions/action_engine.cpp
    src/leds/led_controller.cpp
    src/leds/led_effect_engine.cpp
    src/leds/effects/static_effect.cpp
    src/leds/effects/chase_effect.cpp
    src/leds/effects/blink_effect.cpp
    src/leds/effects/wave_effect.cpp
)

target_include_directories(macro_deck PRIVATE
    src
)

target_link_libraries(macro_deck
    pico_stdlib
    hardware_pwm
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(macro_deck)

pico_enable_stdio_usb(macro_deck 0)
pico_enable_stdio_uart(macro_deck 0)