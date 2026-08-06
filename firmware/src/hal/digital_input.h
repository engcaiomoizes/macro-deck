#pragma once

#include "hal/gpio.h"

namespace hal {
    class DigitalInput {
        public:
            DigitalInput(uint pin, Pull pull = Pull::Up);

            void initialize();

            bool read() const;

        private:
            Gpio m_gpio;
            Pull m_pull;
    };
}