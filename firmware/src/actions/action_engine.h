#pragma once

#include <array>
#include <cstddef>

#include "actions/action.h"
#include "config/profile.h"
#include "usb/usb_device.h"

namespace actions {
    class ActionEngine {
        public:
            ActionEngine(usb::UsbDevice& usbDevice);

            void press(
                std::size_t inputIndex,
                const Action& action
            );

            void release(std::size_t inputIndex);

            void update();

        private:
            using ActiveActions =
                std::array<const Action*, config::Profile::KeyCount>;

            usb::UsbDevice& m_usbDevice;

            ActiveActions m_activeActions;

            bool m_keyboardReportPending;
            bool m_consumerReportPending;

            void sendKeyboardReport();
            void sendConsumerReport();
    };
}