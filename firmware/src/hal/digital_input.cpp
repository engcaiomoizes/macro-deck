#include "hal/digital_input.h"

namespace hal {
    DigitalInput::DigitalInput(uint pin, Pull pull)
        : m_gpio(pin), m_pull(pull) {}
    
    void DigitalInput::initialize() {
        m_gpio.initialize(Direction::Input, m_pull);
    }

    bool DigitalInput::read() const {
        return m_gpio.read();
    }
}