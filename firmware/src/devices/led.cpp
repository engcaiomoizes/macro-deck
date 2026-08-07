#include "devices/led.h"

namespace devices {
    Led::Led(uint32_t pin) : m_output(pin) {}

    void Led::initialize() {
        m_output.initialize();
    }

    void Led::on() {
        m_output.on();
    }

    void Led::off() {
        m_output.off();
    }

    void Led::toggle() {
        if (m_output.brightness() > 0) {
            off();
        } else {
            on();
        }
    }

    void Led::setBrightness(uint8_t brightness) {
        m_output.setBrightness(brightness);
    }

    uint8_t Led::brightness() const {
        return m_output.brightness();
    }
}