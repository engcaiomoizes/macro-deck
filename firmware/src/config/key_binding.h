#pragma once

#include <cstdint>

namespace config {
    struct KeyBinding {
        uint8_t keycode;
        uint8_t modifiers;
    };
}