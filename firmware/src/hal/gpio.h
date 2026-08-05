#pragma once

#include <hardware/gpio.h>

namespace hal {
    enum class Direction {
        Input,
        Output
    };

    enum class Pull {
        None,
        Up,
        Down
    };

    class Gpio {
        public:
            explicit Gpio(uint pin);

            void initialize(Direction direction, Pull pull = Pull::None);

            void set(bool value);
            bool read() const;

            void toggle();
        
        private:
            uint m_pin;
    };
}