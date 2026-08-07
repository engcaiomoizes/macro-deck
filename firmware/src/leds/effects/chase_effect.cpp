#include "leds/effects/chase_effect.h"

namespace leds {
    ChaseEffect::ChaseEffect(uint32_t speedMs)
        : m_timer(speedMs),
        m_index(0) {}
    
    void ChaseEffect::initialize(LedController& controller) {
        controller.allOff();

        m_index = 0;
        controller.on(m_index);

        m_timer.restart();
    }

    void ChaseEffect::update(LedController& controller) {
        if (!m_timer.poll()) return;

        controller.off(m_index);

        ++m_index;

        if (m_index >= LedController::LedCount) {
            m_index = 0;
        }

        controller.on(m_index);
    }
}