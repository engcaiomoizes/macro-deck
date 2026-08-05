#pragma once

#include "hal/gpio.h"

namespace devices {
    class Led {
        public:
            explicit Led(uint pin);

            void initialize();

            void on();
            void off();
            void toggle();
        
        private:
            hal::Gpio m_gpio;
    };
}