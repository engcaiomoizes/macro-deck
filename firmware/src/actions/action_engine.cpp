#include "actions/action_engine.h"

#include <cstdint>

namespace actions {
    ActionEngine::ActionEngine(
        usb::UsbDevice& usbDevice
    ) : m_usbDevice(usbDevice),
        m_activeActions{},
        m_keyboardReportPending(true),
        m_consumerReportPending(true) {
        m_activeActions.fill(nullptr);
    }

    void ActionEngine::press(
        std::size_t inputIndex,
        const Action& action
    ) {
        if (inputIndex >= m_activeActions.size()) return;

        m_activeActions[inputIndex] = &action;

        switch (action.type()) {
            case ActionType::Keyboard:
                m_keyboardReportPending = true;
                break;
            case ActionType::Consumer:
                m_consumerReportPending = true;
                break;
            case ActionType::None:
                break;
        }
    }

    void ActionEngine::release(std::size_t inputIndex) {
        if (inputIndex >= m_activeActions.size()) return;

        const Action* action = m_activeActions[inputIndex];

        if (action == nullptr) return;

        switch (action->type()) {
            case ActionType::Keyboard:
                m_keyboardReportPending = true;
                break;
            case ActionType::Consumer:
                m_consumerReportPending = true;
                break;
            case ActionType::None:
                break;
        }

        m_activeActions[inputIndex] = nullptr;
    }

    void ActionEngine::update() {
        if (m_keyboardReportPending) {
            sendKeyboardReport();
        }

        if (m_consumerReportPending) {
            sendConsumerReport();
        }
    }

    void ActionEngine::sendKeyboardReport() {
        usb::UsbDevice::Keycodes keycodes{};

        uint8_t modifiers = 0;
        std::size_t reportIndex = 0;

        for (const Action* action : m_activeActions) {
            if (
                action == nullptr ||
                action->type() != ActionType::Keyboard
            ) continue;

            const KeyboardAction& keyboardAction = action->keyboardData();

            modifiers |= keyboardAction.modifiers;

            if (
                keyboardAction.keycode != 0 &&
                reportIndex < keycodes.size()
            ) {
                keycodes[reportIndex] =
                    keyboardAction.keycode;

                ++reportIndex;
            }
        }

        if (
            m_usbDevice.sendKeyboardReport(
                modifiers,
                keycodes
            )
        ) m_keyboardReportPending = false;
    }

    void ActionEngine::sendConsumerReport() {
        uint16_t usageCode = 0;

        for (const Action* action : m_activeActions) {
            if (
                action == nullptr ||
                action->type() != ActionType::Consumer
            ) continue;

            usageCode = action->consumerData().usageCode;

            // O relatório Consumer atual envia uma ação por vez.
            break;
        }

        const bool sent =
            usageCode == 0
                ? m_usbDevice.releaseConsumerReport()
                : m_usbDevice.sendConsumerReport(usageCode);

        if (sent) {
            m_consumerReportPending = false;
        }
    }
}