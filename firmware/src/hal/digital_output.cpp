#include "hal/digital_output.h"

namespace hal {
    DigitalOutput::DigitalOutput(uint pin)
        : m_gpio(pin), m_state(false) {}
    
    void DigitalOutput::initialize(bool initialState) {
        m_gpio.initialize(Direction::Output);

        write(initialState);
    }

    void DigitalOutput::write(bool value) {
        m_state = value;
        m_gpio.set(value);
    }

    bool DigitalOutput::state() const {
        return m_state;
    }

    void DigitalOutput::on() {
        write(true);
    }

    void DigitalOutput::off() {
        write(false);
    }

    void DigitalOutput::toggle() {
        write(!m_state);
    }
}