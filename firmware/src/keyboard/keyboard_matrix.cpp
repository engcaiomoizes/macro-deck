#include "keyboard/keyboard_matrix.h"

#include "hal/clock.h"

namespace keyboard {
    KeyboardMatrix::KeyboardMatrix(
        const RowPins& rowPins,
        const ColumnPins& columnPins,
        uint32_t debounceMs
    ) : m_rows{
        hal::DigitalInput(rowPins[0], hal::Pull::Up),
        hal::DigitalInput(rowPins[1], hal::Pull::Up)
    }, m_columns{
        hal::DigitalOutput(columnPins[0]),
        hal::DigitalOutput(columnPins[1]),
        hal::DigitalOutput(columnPins[2]),
        hal::DigitalOutput(columnPins[3]),
        hal::DigitalOutput(columnPins[4])
    }, m_stableStates{}, m_candidateStates{}, m_candidateSince{}, m_events{}, m_debounceMs(debounceMs) {}

    void KeyboardMatrix::initialize() {
        for (auto& row : m_rows) {
            row.initialize();
        }

        for (auto& column : m_columns) {
            // HIGH significa coluna inativa.
            column.initialize(true);
        }

        m_stableStates.fill(false);
        m_candidateStates.fill(false);
        m_candidateSince.fill(hal::Clock::milliseconds());
        m_events.fill(KeyEvent::None);
    }

    void KeyboardMatrix::scan() {
        m_events.fill(KeyEvent::None);

        const uint64_t now = hal::Clock::milliseconds();

        deactivateAllColumns();

        for (std::size_t column = 0; column < ColumnCount; column++) {
            // Ativa somente a coluna atual.
            m_columns[column].off();

            for (std::size_t row = 0; row < RowCount; row++) {
                // Pull-up: LOW significa tecla pressionada.
                const bool rawPressed = !m_rows[row].read();
                const std::size_t keyIndex = indexOf(row, column);

                updateKey(keyIndex, rawPressed, now);
            }

            // Desativa a coluna antes de passar para a próxima.
            m_columns[column].on();
        }
    }

    void KeyboardMatrix::updateKey(
        std::size_t keyIndex,
        bool rawPressed,
        uint64_t now
    ) {
        if (rawPressed != m_candidateStates[keyIndex]) {
            m_candidateStates[keyIndex] = rawPressed;
            m_candidateSince[keyIndex] = now;
            return;
        }

        if (rawPressed == m_stableStates[keyIndex]) return;

        const uint64_t elapsed = now - m_candidateSince[keyIndex];

        if (elapsed < m_debounceMs) return;

        m_stableStates[keyIndex] = rawPressed;

        m_events[keyIndex] = rawPressed
            ? KeyEvent::Pressed
            : KeyEvent::Released;
    }

    bool KeyboardMatrix::isPressed(
        std::size_t row,
        std::size_t column
    ) const {
        if (row >= RowCount || column >= ColumnCount) return false;

        return m_stableStates[indexOf(row, column)];
    }

    bool KeyboardMatrix::isPressed(std::size_t keyIndex) const {
        if (keyIndex >= KeyCount) return false;

        return m_stableStates[keyIndex];
    }

    KeyEvent KeyboardMatrix::event(
        std::size_t row,
        std::size_t column
    ) const {
        if (row >= RowCount || column >= ColumnCount) {
            return KeyEvent::None;
        }

        return m_events[indexOf(row, column)];
    }

    KeyEvent KeyboardMatrix::event(std::size_t keyIndex) const {
        if (keyIndex >= KeyCount) {
            return KeyEvent::None;
        }

        return m_events[keyIndex];
    }

    void KeyboardMatrix::deactivateAllColumns() {
        for (auto& column : m_columns) {
            column.on();
        }
    }
}