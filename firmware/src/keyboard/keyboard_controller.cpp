#include "keyboard/keyboard_controller.h"
#include "actions/action.h"

namespace keyboard {
    KeyboardController::KeyboardController(
        KeyboardMatrix& matrix,
        usb::UsbDevice& usbDevice,
        const config::Profile& profile
    ) : m_matrix(matrix),
        m_usbDevice(usbDevice),
        m_profile(profile),
        m_reportPending(true),
        m_consumerReportPending(false),
        m_activeConsumerUsage(0) {}
    
    void KeyboardController::update() {
        for (std::size_t keyIndex = 0; keyIndex < KeyboardMatrix::KeyCount; ++keyIndex) {
            if (m_matrix.event(keyIndex) != KeyEvent::None) {
                m_reportPending = true;
                m_consumerReportPending = true;
            }
        }

        if (m_reportPending) {
            sendCurrentState();
        }

        if (m_consumerReportPending) {
            updateConsumerActions();
        }
    }

    void KeyboardController::sendCurrentState() {
        usb::UsbDevice::Keycodes keycodes{};

        uint8_t modifiers = 0;
        std::size_t reportIndex = 0;

        for (std::size_t keyIndex = 0; keyIndex < KeyboardMatrix::KeyCount; ++keyIndex) {
            if (!m_matrix.isPressed(keyIndex)) continue;

            const actions::Action& action = m_profile.action(keyIndex);

            if (action.type() != actions::ActionType::Keyboard) continue;

            const actions::KeyboardAction& keyboardAction = action.keyboardData();

            modifiers |= keyboardAction.modifiers;

            if (keyboardAction.keycode != 0 && reportIndex < keycodes.size()) {
                keycodes[reportIndex] = keyboardAction.keycode;
                ++reportIndex;
            }
        }

        if (m_usbDevice.sendKeyboardReport(modifiers, keycodes)) {
            m_reportPending = false;
        }
    }

    void KeyboardController::updateConsumerActions() {
        uint16_t consumerUsage = 0;

        for (std::size_t keyIndex = 0; keyIndex < KeyboardMatrix::KeyCount; ++keyIndex) {
            if (!m_matrix.isPressed(keyIndex)) continue;

            const actions::Action& action = m_profile.action(keyIndex);

            if (action.type() != actions::ActionType::Consumer) continue;

            consumerUsage = action.consumerData().usageCode;
            break;
        }

        bool sent = false;

        if (consumerUsage == 0) {
            sent = m_usbDevice.releaseConsumerReport();
        } else {
            sent = m_usbDevice.sendConsumerReport(consumerUsage);
        }

        if (sent) {
            m_activeConsumerUsage = consumerUsage;
            m_consumerReportPending = false;
        }
    }
}