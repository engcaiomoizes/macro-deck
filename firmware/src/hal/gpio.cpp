#include "hal/gpio.h"

namespace hal {
    Gpio::Gpio(uint pin) : m_pin(pin) {}

    void Gpio::initialize(Direction direction, Pull pull) {
        gpio_init(m_pin);
        gpio_set_dir(m_pin, direction == Direction::Output);

        if (direction == Direction::Input) {
            switch (pull) {
                case Pull::None:
                    gpio_disable_pulls(m_pin);
                    break;
                case Pull::Up:
                    gpio_pull_up(m_pin);
                    break;
                case Pull::Down:
                    gpio_pull_down(m_pin);
                    break;
            }
        }
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