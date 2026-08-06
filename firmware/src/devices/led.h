#pragma once

#include "hal/digital_output.h"

namespace devices {
    class Led {
        public:
            explicit Led(uint pin);

            void initialize();

            void on();
            void off();
            void toggle();
        
        private:
            hal::DigitalOutput m_output;
    };
}