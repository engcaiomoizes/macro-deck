#pragma once

#include <array>
#include <cstddef>

#include "actions/action.h"

namespace config {
    class Profile {
        public:
            static constexpr std::size_t KeyCount = 10;

            using ActionMap = std::array<actions::Action, KeyCount>;

            explicit Profile(const ActionMap& actions) : m_actions(actions) {}

            const actions::Action& action(std::size_t keyIndex) const {
                return m_actions[keyIndex];
            }

            const ActionMap& actions() const {
                return m_actions;
            }
        
        private:
            ActionMap m_actions;
    };
}