#pragma once

#include "hal/gpio.h"

namespace hal {
    class DigitalOutput {
        public:
            DigitalOutput(uint pin);

            void initialize(bool initialState = false);

            void write(bool value);

            bool state() const;

            void on();
            void off();
            void toggle();

        private:
            Gpio m_gpio;
            bool m_state;
    };
}