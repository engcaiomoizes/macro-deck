#include "application.h"

#include "pico/stdlib.h"

#include "config/default_profile.h"

Application::Application() 
    : m_statusLed(PICO_DEFAULT_LED_PIN),
    m_blinkTimer(500),
    m_keyboardMatrix(
        keyboard::KeyboardMatrix::RowPins{2, 3},
        keyboard::KeyboardMatrix::ColumnPins{4, 5, 6, 7, 8}
    ),
    m_usb(),
    m_keyboardController(
        m_keyboardMatrix,
        m_usb,
        config::defaultProfile()
    ) {}

void Application::initialize() {
    m_statusLed.initialize();
    m_keyboardMatrix.initialize();
    m_usb.initialize();
}

void Application::update() {
    m_usb.update();
    m_keyboardMatrix.scan();
    m_keyboardController.update();

    if (m_blinkTimer.poll()) {
        m_statusLed.toggle();
    }
}