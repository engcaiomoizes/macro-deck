#pragma once

#include <cstdint>

namespace hal {
    class PwmOutput {
        public:
            explicit PwmOutput(uint32_t pin);

            void initialize();

            void setLevel(uint16_t level);

            void setBrightness(uint8_t brightness);

            uint8_t brightness() const;

            void on();
            void off();
        
        private:
            uint32_t m_pin;
            uint32_t m_slice;
            uint32_t m_channel;

            uint8_t m_brightness;
    };
}