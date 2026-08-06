#include "keyboard/keyboard_controller.h"

namespace keyboard {
    KeyboardController::KeyboardController(
        KeyboardMatrix& matrix,
        usb::UsbDevice& usbDevice,
        const Keymap& keymap
    ) : m_matrix(matrix),
        m_usbDevice(usbDevice),
        m_keymap(keymap),
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

            const KeyBinding& binding = m_keymap[keyIndex];

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