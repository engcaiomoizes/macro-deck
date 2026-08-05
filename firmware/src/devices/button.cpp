#include "devices/button.h"

namespace devices {
    Button::Button(
        uint pin,
        uint32_t debounceMs
    ) : m_gpio(pin),
        m_currentState(false),
        m_candidateState(false),
        m_event(ButtonEvent::None) {}

    void Button::initialize() {
        m_gpio.initialize(hal::Direction::Input, hal::Pull::Up);
    }

    void Button::update() {
        bool reading = !m_gpio.read();

        m_event = ButtonEvent::None;
        
        // Detectou mudança no sinal?
        if (reading != m_candidateState) {
            m_candidateState = reading;
            m_debounceTimer.restart();

            return;
        }

        // Ainda aguardando estabilizar
        if (!m_debouceTimer.poll()) return;

        // Atualiza estado estabilizado
        m_currentState = m_candidateState;

        if (m_currentState)
            m_event = ButtonEvent::Pressed;
        else
            m_event = ButtonEvent::Released;
    }

    bool Button::isPressed() const {
        return m_currentState;
    }

    ButtonEvent Button::event() const {
        return m_event;
    }
}