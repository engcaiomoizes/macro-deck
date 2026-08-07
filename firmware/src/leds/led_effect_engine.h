#pragma once

#include <cstddef>

#include "leds/led_controller.h"
#include "leds/effects/i_led_effect.h"

namespace leds {
    class LedEffectEngine {
        public:
            LedEffectEngine(
                LedController& controller,
                ILedEffect& effect
            );

            void initialize();
            void update();

            void setEffect(ILedEffect& effect);
        
        private:
            LedController& m_controller;
            ILedEffect* m_effect;
    };
}