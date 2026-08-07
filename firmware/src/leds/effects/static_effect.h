#pragma once

#include "leds/effects/i_led_effect.h"

namespace leds {
    class StaticEffect : public ILedEffect {
        public:
            void initialize(LedController& controller) override;

            void update(LedController& controller) override;
    };
}