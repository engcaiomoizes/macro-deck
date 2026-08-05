#include "application.h"

#include "pico/stdlib.h"

Application::Application() : m_statusLed(PICO_DEFAULT_LED_PIN), m_blinkTimer(500) {}

void Application::initialize() {
    m_statusLed.initialize();
}

void Application::update() {
    if (m_blinkTimer.poll()) {
        m_statusLed.toggle();
    }
}