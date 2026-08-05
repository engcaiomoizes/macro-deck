#pragma once

#include "devices/led.h"
#include "hal/timer.h"


class Application {
    public:
        Application();

        void initialize();

        void update();
    
    private:
        devices::Led m_statusLed;

        hal::Timer m_blinkTimer;
};