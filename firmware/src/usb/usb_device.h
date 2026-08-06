#pragma once

#include <array>
#include <cstdint>

namespace usb {
    class UsbDevice {
        public:
            static constexpr std::size_t MaxKeyboardKeys = 6;
            using Keycodes = std::array<uint8_t, MaxKeyboardKeys>;

            void initialize();
            void update();

            bool mounted() const;

            bool sendKeyboardReport(
                uint8_t modifiers,
                const Keycodes& keycodes
            );

            bool releaseKeys();
        
        private:
            static constexpr uint8_t ReportId = 1;
    };
}