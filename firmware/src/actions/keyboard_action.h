#pragma once

#include <cstdint>

namespace actions {
    struct KeyboardAction {
        uint8_t keycode;
        uint8_t modifiers;
    };
}