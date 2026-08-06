#pragma once

#include <stdint.h>

namespace hal {
    class OneShotTimer {
        public:
            explicit OneShotTimer(uint32_t intervalMs);

            void restart();

            bool expired();

            bool running() const;

        private:
            uint32_t m_interval;
            uint64_t m_startTime;
            bool m_running;
    };
}