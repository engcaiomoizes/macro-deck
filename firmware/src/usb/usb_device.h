#pragma once

#include <cstdint>

namespace usb {
    class UsbDevice {
        public:
            void initialize();
            void update();

            bool mounted() const;

            bool sendKey(
                uint8_t keycode,
                uint8_t modifiers = 0
            );

            bool releaseKeys();
        
        private:
            static constexpr uint8_t ReportId = 1;
    };
}