#pragma once

#include "devices/led.h"
#include "hal/periodic_timer.h"
#include "keyboard/keyboard_matrix.h"

class Application {
    public:
        Application();

        void initialize();

        void update();
    
    private:
        devices::Led m_statusLed;
        hal::PeriodicTimer m_blinkTimer;

        keyboard::KeyboardMatrix m_keyboardMatrix;
};