#include "leds/effects/wave_effect.h"

namespace leds {
    WaveEffect::WaveEffect(uint32_t speedMs)
        : m_timer(speedMs),
        m_index(0) {}

    void WaveEffect::initialize(LedController& controller) {
        controller.allOff();

        m_index = 0;

        controller.on(0);

        m_timer.restart();
    }

    void WaveEffect::update(LedController& controller) {
        if (!m_timer.poll()) return;

        controller.allOff();

        controller.on(m_index);

        const std::size_t previous =
            m_index == 0
                ? LedController::LedCount - 1
                : m_index - 1;

        controller.on(previous);

        ++m_index;

        if (m_index >= LedController::LedCount) {
            m_index = 0;
        }
    }
}