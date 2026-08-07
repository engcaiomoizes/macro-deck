#include "hal/pwm_output.h"

#include "hardware/gpio.h"
#include "hardware/pwm.h"

namespace hal {
    PwmOutput::PwmOutput(uint32_t pin)
        : m_pin(pin),
        m_slice(0),
        m_channel(0),
        m_brightness(0) {}

    void PwmOutput::initialize() {
        gpio_set_function(
            m_pin,
            GPIO_FUNC_PWM
        );

        m_slice = pwm_gpio_to_slice_num(m_pin);
        m_channel = pwm_gpio_to_channel(m_pin);

        pwm_config config = pwm_get_default_config();

        pwm_config_set_wrap(
            &config,
            255
        );

        pwm_init(
            m_slice,
            &config,
            true
        );

        setBrightness(0);
    }

    void PwmOutput::setLevel(uint16_t level) {
        if (level > 255) {
            level = 255;
        }

        m_brightness = static_cast<uint8_t>(level);

        pwm_set_chan_level(
            m_slice,
            m_channel,
            level
        );
    }

    void PwmOutput::setBrightness(uint8_t brightness) {
        setLevel(brightness);
    }

    uint8_t PwmOutput::brightness() const {
        return m_brightness;
    }

    void PwmOutput::on() {
        setBrightness(255);
    }

    void PwmOutput::off() {
        setBrightness(0);
    }
}