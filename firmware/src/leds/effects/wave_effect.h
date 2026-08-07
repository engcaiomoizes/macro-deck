#pragma once

#include <cstddef>
#include <cstdint>

#include "hal/periodic_timer.h"
#include "leds/effects/i_led_effect.h"

namespace leds {
    class WaveEffect : public ILedEffect {
        public:
            explicit WaveEffect(uint32_t speedMs = 100);

            void initialize(LedController& controller) override;

            void update(LedController& controller) override;

        private:
            hal::PeriodicTimer m_timer;
            std::size_t m_index;
    };
}