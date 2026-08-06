#include "application.h"

#include "pico/stdlib.h"

Application::Application() 
    : m_statusLed(PICO_DEFAULT_LED_PIN),
    m_blinkTimer(500),
    m_keyboardMatrix(
        keyboard::KeyboardMatrix::RowPins{2, 3},
        keyboard::KeyboardMatrix::ColumnPins{4, 5, 6, 7, 8}
    ) {}

void Application::initialize() {
    m_statusLed.initialize();
    m_keyboardMatrix.initialize();
}

void Application::update() {
    m_keyboardMatrix.scan();

    if (m_blinkTimer.poll()) {
        m_statusLed.toggle();
    }
}