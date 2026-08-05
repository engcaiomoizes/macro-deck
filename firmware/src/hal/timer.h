#pragma once

#include <stdint.h>

namespace hal {
    class Timer {
        public:
            Timer(uint32_t intervalMs);

            bool poll();

            void restart();
        
        private:
            bool expired();
            
            uint32_t m_interval;
            uint32_t m_lastTime;
    };
}