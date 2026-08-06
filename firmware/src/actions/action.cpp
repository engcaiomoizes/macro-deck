#include "actions/action.h"

namespace actions {
    Action::Action(
        ActionType type,
        const KeyboardAction& keyboardAction,
        const ConsumerAction& consumerAction
    ) : m_type(type),
        m_keyboardAction(keyboardAction),
        m_consumerAction(consumerAction) {}

    Action Action::none() {
        return Action(
            ActionType::None,
            KeyboardAction{0, 0},
            ConsumerAction{0}
        );
    }

    Action Action::keyboard(
        uint8_t keycode,
        uint8_t modifiers
    ) {
        return Action(
            ActionType::Keyboard,
            KeyboardAction{
                keycode,
                modifiers
            },
            ConsumerAction{0}
        );
    }

    Action Action::consumer(uint16_t usageCode) {
        return Action(
            ActionType::Consumer,
            KeyboardAction{0, 0},
            ConsumerAction{usageCode}
        );
    }

    ActionType Action::type() const {
        return m_type;
    }

    const KeyboardAction& Action::keyboardData() const {
        return m_keyboardAction;
    }

    const ConsumerAction& Action::consumerData() const {
        return m_consumerAction;
    }
}