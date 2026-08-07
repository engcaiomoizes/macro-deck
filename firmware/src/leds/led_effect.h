#pragma once

#include <cstdint>

namespace leds {
    enum class LedEffectType : uint8_t {
        Static,
        Chase,
        Blink,
        Wave,
        Reactive
    };

    struct LedEffectConfig {
        LedEffectType type;
        uint32_t speedMs;
    };
}