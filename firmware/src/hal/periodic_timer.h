#pragma once

#include <stdint.h>

namespace hal {
    class PeriodicTimer {
        public:
            explicit PeriodicTimer(uint32_t intervalMs);

            bool poll();

            void restart();

        private:
            bool expired() const;

            uint32_t m_interval;
            uint64_t m_lastTime;
    };
}