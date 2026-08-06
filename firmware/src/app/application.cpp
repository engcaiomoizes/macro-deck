#include "application.h"

#include "pico/stdlib.h"
#include "tusb.h"

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
        keyboard::KeyboardController::Keymap{
            keyboard::KeyBinding{HID_KEY_A, 0},
            keyboard::KeyBinding{HID_KEY_B, 0},
            keyboard::KeyBinding{HID_KEY_C, 0},
            keyboard::KeyBinding{HID_KEY_D, 0},
            keyboard::KeyBinding{HID_KEY_E, 0},
            keyboard::KeyBinding{HID_KEY_F, 0},
            keyboard::KeyBinding{HID_KEY_G, 0},
            keyboard::KeyBinding{HID_KEY_H, 0},
            keyboard::KeyBinding{HID_KEY_I, 0},
            keyboard::KeyBinding{HID_KEY_J, 0}
        }
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