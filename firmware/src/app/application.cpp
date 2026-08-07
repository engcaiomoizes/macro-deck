#include "application.h"

#include "pico/stdlib.h"

#include "config/default_profile.h"
#include "config/pins.h"

Application::Application() 
    : m_statusLed(PICO_DEFAULT_LED_PIN),
    m_blinkTimer(500),
    m_keyboardMatrix(
        keyboard::KeyboardMatrix::RowPins{2, 3},
        keyboard::KeyboardMatrix::ColumnPins{4, 5, 6, 7, 8}
    ),
    m_usb(),
    m_actionEngine(m_usb),
    m_keyboardController(
        m_keyboardMatrix,
        config::defaultProfile(),
        m_actionEngine
    ),
    m_ledController(config::LedPins),
    m_staticEffect(),
    m_chaseEffect(100),
    m_blinkEffect(500),
    m_waveEffect(100),
    m_ledEffectEngine(
        m_ledController,
        m_staticEffect
    ) {}

void Application::initialize() {
    m_statusLed.initialize();
    m_keyboardMatrix.initialize();
    m_usb.initialize();

    m_ledController.initialize();
    m_ledEffectEngine.initialize();
}

void Application::update() {
    m_usb.update();

    m_keyboardMatrix.scan();
    m_keyboardController.update();
    m_actionEngine.update();

    m_ledEffectEngine.update();

    if (m_blinkTimer.poll()) {
        m_statusLed.toggle();
    }
}