#include "leds/led_effect_engine.h"

namespace leds {
    LedEffectEngine::LedEffectEngine(
        LedController& controller,
        ILedEffect& effect
    ) : m_controller(controller),
        m_effect(&effect) {}

    void LedEffectEngine::initialize() {
        if (m_effect == nullptr) return;

        m_effect->initialize(m_controller);
    }

    void LedEffectEngine::update() {
        if (m_effect == nullptr) return;

        m_effect->update(m_controller);
    }

    void LedEffectEngine::setEffect(ILedEffect& effect) {
        m_effect = &effect;

        m_effect->initialize(m_controller);
    }
}