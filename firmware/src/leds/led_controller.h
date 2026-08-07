#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "devices/led.h"
// #include "hal/periodic_timer.h"

namespace leds {
    class LedController {
        public:
            static constexpr std::size_t LedCount = 10;

            using Pins = std::array<uint32_t, LedCount>;

            explicit LedController(const Pins& pins);

            void initialize();
            // void update();

            void set(std::size_t index, bool state);
            void on(std::size_t index);
            void off(std::size_t index);
            void toggle(std::size_t index);

            void setBrightness(
                std::size_t index,
                uint8_t brightness
            );

            uint8_t brightness(std::size_t index) const;

            void allOn();
            void allOff();
        
        private:
            std::array<devices::Led, LedCount> m_leds;
            
            // hal::PeriodicTimer m_effectTimer;
            // std::size_t m_effectIndex;
    };
}