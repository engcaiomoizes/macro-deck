#include "hal/gpio.h"

namespace hal {
    Gpio::Gpio(uint pin) : m_pin(pin) {}

    void Gpio::initialize(Direction direction) {
        gpio_init(m_pin);
        gpio_set_dir(m_pin, direction == Direction::Output);
    }

    void Gpio::set(bool value) {
        gpio_put(m_pin, value);
    }

    bool Gpio::read() const {
        return gpio_get(m_pin);
    }

    void Gpio::toggle() {
        set(!read());
    }
}