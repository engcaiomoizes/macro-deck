#pragma once

#include <cstdint>

#include "hal/periodic_timer.h"
#include "leds/effects/i_led_effect.h"

namespace leds {
    class BlinkEffect : public ILedEffect {
        public:
            explicit BlinkEffect(uint32_t speedMs = 500);

            void initialize(LedController& controller) override;

            void update(LedController& controller) override;
        
        private:
            hal::PeriodicTimer m_timer;
            bool m_state;
    };
}