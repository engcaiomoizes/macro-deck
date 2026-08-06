#pragma once

#include <array>
#include <cstddef>

#include "hal/digital_input.h"
#include "hal/digital_output.h"

namespace keyboard {
    enum class KeyEvent {
        None,
        Pressed,
        Released
    };

    class KeyboardMatrix {
        public:
            static constexpr std::size_t RowCount = 2;
            static constexpr std::size_t ColumnCount = 5;
            static constexpr std::size_t KeyCount = RowCount * ColumnCount;

            using RowPins = std::array<uint, RowCount>;
            using ColumnPins = std::array<uint, ColumnCount>;

            KeyboardMatrix(
                const RowPins& rowPins,
                const ColumnPins& columnPins,
                uint32_t debounceMs = 5
            );

            void initialize();
            void scan();

            bool isPressed(
                std::size_t row,
                std::size_t column
            ) const;

            bool isPressed(std::size_t keyIndex) const;

            KeyEvent event(
                std::size_t row,
                std::size_t column
            ) const;

            KeyEvent event(std::size_t keyIndex) const;
        
        private:
            std::array<hal::DigitalInput, RowCount> m_rows;
            std::array<hal::DigitalOutput, ColumnCount> m_columns;

            std::array<bool, KeyCount> m_stableStates;
            std::array<bool, KeyCount> m_candidateStates;
            std::array<uint64_t, KeyCount> m_candidateSince;
            std::array<KeyEvent, KeyCount> m_events;

            uint32_t m_debounceMs;

            static constexpr std::size_t indexOf(
                std::size_t row,
                std::size_t column
            ) {
                return row * ColumnCount + column;
            }

            void deactivateAllColumns();

            void updateKey(
                std::size_t keyIndex,
                bool rawPressed,
                uint64_t now
            );
    };
}