#pragma once

#include "actions/keyboard_action.h"
#include "actions/consumer_action.h"

namespace actions {
    enum class ActionType : uint8_t {
        None,
        Keyboard,
        Consumer
    };

    class Action {
        public:
            static Action none();

            static Action keyboard(
                uint8_t keycode,
                uint8_t modifiers = 0
            );

            static Action consumer(uint16_t usageCode);

            ActionType type() const;

            const KeyboardAction& keyboardData() const;
            const ConsumerAction& consumerData() const;
        
        private:
            Action(
                ActionType type,
                const KeyboardAction& keyboardAction,
                const ConsumerAction& consumerAction
            );

            ActionType m_type;

            KeyboardAction m_keyboardAction;
            ConsumerAction m_consumerAction;
    };
}