#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "keyboard/keyboard_matrix.h"
#include "usb/usb_device.h"

namespace keyboard {
    struct KeyBinding {
        uint8_t keycode;
        uint8_t modifiers;
    };

    class KeyboardController {
        public:
            using Keymap = std::array<KeyBinding, KeyboardMatrix::KeyCount>;

            KeyboardController(
                KeyboardMatrix& matrix,
                usb::UsbDevice& usbDevice,
                const Keymap& keymap
            );

            void update();
        
        private:
            KeyboardMatrix& m_matrix;
            usb::UsbDevice& m_usbDevice;
            Keymap m_keymap;

            bool m_reportPending;

            void sendCurrentState();
    };
}