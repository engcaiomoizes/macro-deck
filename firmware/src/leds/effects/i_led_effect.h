#pragma once

#include "leds/led_controller.h"

namespace leds {
    class ILedEffect {
        public:
            virtual ~ILedEffect() = default;

            virtual void initialize(LedController& controller) = 0;

            virtual void update(LedController& controller) = 0;
    };
}