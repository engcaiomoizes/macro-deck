#include "devices/led.h"

namespace devices {
    Led::Led(uint pin) : m_gpio(pin) {}

    void Led::initialize() {
        m_gpio.initialize(hal::Direction::Output);
    }

    void Led::on() {
        m_gpio.set(true);
    }

    void Led::off() {
        m_gpio.set(false);
    }

    void Led::toggle() {
        m_gpio.toggle();
    }
}