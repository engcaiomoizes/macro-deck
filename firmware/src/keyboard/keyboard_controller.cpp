#include "keyboard/keyboard_controller.h"

namespace keyboard {
    KeyboardController::KeyboardController(
        KeyboardMatrix& matrix,
        usb::UsbDevice& usbDevice,
        const config::Profile& profile
    ) : m_matrix(matrix),
        m_usbDevice(usbDevice),
        m_profile(profile),
        m_reportPending(true) {}
    
    void KeyboardController::update() {
        for (std::size_t keyIndex = 0; keyIndex < KeyboardMatrix::KeyCount; ++keyIndex) {
            if (m_matrix.event(keyIndex) != KeyEvent::None) {
                m_reportPending = true;
            }
        }

        if (m_reportPending) {
            sendCurrentState();
        }
    }

    void KeyboardController::sendCurrentState() {
        usb::UsbDevice::Keycodes keycodes{};
        uint8_t modifiers = 0;
        std::size_t reportIndex = 0;

        for (std::size_t keyIndex = 0; keyIndex < KeyboardMatrix::KeyCount; ++keyIndex) {
            if (!m_matrix.isPressed(keyIndex)) continue;

            const config::KeyBinding& binding = m_profile.binding(keyIndex);

            modifiers |= binding.modifiers;

            if (binding.keycode != 0 && reportIndex < keycodes.size()) {
                keycodes[reportIndex] = binding.keycode;
                ++reportIndex;
            }
        }

        if (m_usbDevice.sendKeyboardReport(modifiers, keycodes)) {
            m_reportPending = false;
        }
    }
}