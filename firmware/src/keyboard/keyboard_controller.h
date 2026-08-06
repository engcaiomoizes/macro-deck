#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "keyboard/keyboard_matrix.h"
#include "usb/usb_device.h"
#include "config/profile.h"

namespace keyboard {
    class KeyboardController {
        public:
            KeyboardController(
                KeyboardMatrix& matrix,
                usb::UsbDevice& usbDevice,
                const config::Profile& profile
            );

            void update();
        
        private:
            KeyboardMatrix& m_matrix;
            usb::UsbDevice& m_usbDevice;
            
            const config::Profile& m_profile;

            bool m_reportPending;

            bool m_consumerReportPending;
            uint16_t m_activeConsumerUsage;

            void sendCurrentState();

            void updateConsumerActions();
    };
}