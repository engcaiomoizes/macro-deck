#include "devices/led.h"

namespace devices {
    Led::Led(uint pin) : m_output(pin) {}

    void Led::initialize() {
        m_output.initialize(false);
    }

    void Led::on() {
        m_output.on();
    }

    void Led::off() {
        m_output.off();
    }

    void Led::toggle() {
        m_output.toggle();
    }
}