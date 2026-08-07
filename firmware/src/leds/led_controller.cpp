#include "leds/led_controller.h"

namespace leds {
    LedController::LedController(const Pins& pins)
        : m_leds{
              devices::Led(pins[0]),
              devices::Led(pins[1]),
              devices::Led(pins[2]),
              devices::Led(pins[3]),
              devices::Led(pins[4]),
              devices::Led(pins[5]),
              devices::Led(pins[6]),
              devices::Led(pins[7]),
              devices::Led(pins[8]),
              devices::Led(pins[9])
          } {}

    void LedController::initialize() {
        for (auto& led : m_leds) {
            led.initialize();
        }

        allOff();
    }

    void LedController::set(
        std::size_t index,
        bool state
    ) {
        if (index >= LedCount) return;

        if (state) {
            m_leds[index].on();
        } else {
            m_leds[index].off();
        }
    }

    void LedController::on(std::size_t index) {
        set(index, true);
    }

    void LedController::off(std::size_t index) {
        set(index, false);
    }

    void LedController::toggle(std::size_t index) {
        if (index >= LedCount) return;

        m_leds[index].toggle();
    }

    void LedController::setBrightness(
        std::size_t index,
        uint8_t brightness
    ) {
        if (index >= LedCount) return;

        m_leds[index].setBrightness(brightness);
    }

    uint8_t LedController::brightness(std::size_t index) const {
        if (index >= LedCount) {
            return 0;
        }

        return m_leds[index].brightness();
    }

    void LedController::allOn() {
        for (auto& led : m_leds) {
            led.on();
        }
    }

    void LedController::allOff() {
        for (auto& led : m_leds) {
            led.off();
        }
    }
}