#pragma once

#include <array>
#include <cstddef>

#include "config/key_binding.h"

namespace config {
    class Profile {
        public:
            static constexpr std::size_t KeyCount = 10;

            using Keymap = std::array<KeyBinding, KeyCount>;

            explicit Profile(const Keymap& keymap) : m_keymap(keymap) {}

            const KeyBinding& binding(std::size_t keyIndex) const {
                return m_keymap[keyIndex];
            }

            const Keymap& keymap() const {
                return m_keymap;
            }
        
        private:
            Keymap m_keymap;
    };
}