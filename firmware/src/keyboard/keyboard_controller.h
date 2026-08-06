#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "keyboard/keyboard_matrix.h"
#include "usb/usb_device.h"
#include "config/profile.h"

namespace keyboard {
    struct KeyBinding {
        uint8_t keycode;
        uint8_t modifiers;
    };

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

            void sendCurrentState();
    };
}