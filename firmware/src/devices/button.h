#pragma once

#include <stdint.h>

#include "hal/gpio.h"
#include "hal/timer.h"

namespace devices {
    enum class ButtonEvent {
        None,
        Pressed,
        Released
    };

    class Button {
        public:
            explicit Button(uint pin, uint32_t debounceMs = 5);

            void initialize();

            void update();

            bool isPressed() const;
            
            ButtonEvent event() const;
        
        private:
            hal::Gpio m_gpio;

            hal::Timer m_debounceTimer;

            bool m_currentState;
            // bool m_previousState;
            bool m_candidateState;

            ButtonEvent m_event;
    };
}