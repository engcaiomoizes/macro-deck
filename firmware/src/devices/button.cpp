#include "devices/button.h"

namespace devices {
    Button::Button(
        uint pin,
        uint32_t debounceMs
    ) : m_input(pin, hal::Pull::Up),
        m_debounceTimer(debounceMs),
        m_currentState(false),
        m_candidateState(false),
        m_event(ButtonEvent::None) {}

    void Button::initialize() {
        m_input.initialize();

        // Sicroniza os estados iniciais com o hardware
        m_currentState = !m_input.read();
        m_candidateState = m_currentState;
        m_event = ButtonEvent::None;
    }

    void Button::update() {
        m_event = ButtonEvent::None;

        // Pull-up: LOW significa pressionado.
        const bool reading = !m_input.read();
        
        // Detectou mudança no sinal?
        if (reading != m_candidateState) {
            m_candidateState = reading;
            m_debounceTimer.restart();

            return;
        }

        // Ainda aguardando estabilizar
        if (!m_debounceTimer.expired()) return;

        // O estado estabilizado não mudou
        if (m_currentState == m_candidateState) return;

        // Atualiza estado estabilizado
        m_currentState = m_candidateState;

        m_event = m_currentState
            ? ButtonEvent::Pressed
            : ButtonEvent::Released;
    }

    bool Button::isPressed() const {
        return m_currentState;
    }

    ButtonEvent Button::event() const {
        return m_event;
    }
}