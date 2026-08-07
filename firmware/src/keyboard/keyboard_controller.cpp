#include "keyboard/keyboard_controller.h"

namespace keyboard {
    KeyboardController::KeyboardController(
        KeyboardMatrix& matrix,
        const config::Profile& profile,
        actions::ActionEngine& actionEngine
    ) : m_matrix(matrix),
        m_profile(profile),
        m_actionEngine(actionEngine) {}
    
    void KeyboardController::update() {
        for (std::size_t keyIndex = 0; keyIndex < KeyboardMatrix::KeyCount; ++keyIndex) {
            switch (m_matrix.event(keyIndex)) {
                case KeyEvent::Pressed:
                    m_actionEngine.press(
                        keyIndex,
                        m_profile.action(keyIndex)
                    );
                    break;
                case KeyEvent::Released:
                    m_actionEngine.release(keyIndex);
                    break;
                case KeyEvent::None:
                    break;
            }
        }
    }
}