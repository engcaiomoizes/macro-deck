#pragma once

#include "devices/led.h"
#include "hal/periodic_timer.h"
#include "keyboard/keyboard_matrix.h"
#include "keyboard/keyboard_controller.h"
#include "usb/usb_device.h"
#include "actions/action_engine.h"
#include "leds/led_controller.h"
#include "leds/led_effect_engine.h"
#include "leds/effects/static_effect.h"
#include "leds/effects/chase_effect.h"
#include "leds/effects/blink_effect.h"
#include "leds/effects/wave_effect.h"

class Application {
    public:
        Application();

        void initialize();

        void update();
    
    private:
        devices::Led m_statusLed;
        hal::PeriodicTimer m_blinkTimer;

        keyboard::KeyboardMatrix m_keyboardMatrix;
        usb::UsbDevice m_usb;

        actions::ActionEngine m_actionEngine;
        keyboard::KeyboardController m_keyboardController;

        leds::LedController m_ledController;

        leds::StaticEffect m_staticEffect;
        leds::ChaseEffect m_chaseEffect;
        leds::BlinkEffect m_blinkEffect;
        leds::WaveEffect m_waveEffect;

        leds::LedEffectEngine m_ledEffectEngine;
};