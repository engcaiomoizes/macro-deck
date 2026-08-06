#pragma once

#include <stdint.h>

#include "hal/digital_input.h"
#include "hal/one_shot_timer.h"

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
            hal::DigitalInput m_input;

            hal::OneShotTimer m_debounceTimer;

            bool m_currentState;
            // bool m_previousState;
            bool m_candidateState;

            ButtonEvent m_event;
    };
}