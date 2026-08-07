#pragma once

#include "hal/pwm_output.h"

namespace devices {
    class Led {
        public:
            explicit Led(uint32_t pin);

            void initialize();

            void on();
            void off();
            void toggle();

            void setBrightness(uint8_t brightness);
            uint8_t brightness() const;
        
        private:
            hal::PwmOutput m_output;
    };
}