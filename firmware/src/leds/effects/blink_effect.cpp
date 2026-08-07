#include "leds/effects/blink_effect.h"

namespace leds {
    BlinkEffect::BlinkEffect(uint32_t speedMs)
        : m_timer(speedMs),
        m_state(true) {}

    void BlinkEffect::initialize(LedController& controller) {
        m_state = true;

        controller.allOn();

        m_timer.restart();
    }

    void BlinkEffect::update(LedController& controller) {
        if (!m_timer.poll()) return;

        m_state = !m_state;

        if (m_state) {
            controller.allOn();
        } else {
            controller.allOff();
        }
    }
}