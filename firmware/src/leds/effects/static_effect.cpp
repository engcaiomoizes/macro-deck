#include "leds/effects/static_effect.h"

namespace leds {
    void StaticEffect::initialize(LedController& controller) {
        for (std::size_t i = 0; i < LedController::LedCount; ++i) {
            controller.setBrightness(i, 255);
        }
    }

    void StaticEffect::update(LedController& controller) {
        (void) controller;
    }
}