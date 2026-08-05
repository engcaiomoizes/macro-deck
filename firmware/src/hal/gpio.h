#pragma once

#include <hardware/gpio.h>

namespace hal {
    enum class Direction {
        Input,
        Output
    };

    class Gpio {
        public:
            explicit Gpio(uint pin);

            void initialize(Direction direction);

            void set(bool value);
            bool read() const;

            void toggle();
        
        private:
            uint m_pin;
    };
}