#pragma once

#include "actions/action_engine.h"
#include "keyboard/keyboard_matrix.h"
#include "config/profile.h"

namespace keyboard {
    class KeyboardController {
        public:
            KeyboardController(
                KeyboardMatrix& matrix,
                const config::Profile& profile,
                actions::ActionEngine& actionEngine
            );

            void update();
        
        private:
            KeyboardMatrix& m_matrix;
            const config::Profile& m_profile;
            actions::ActionEngine& m_actionEngine;
    };
}