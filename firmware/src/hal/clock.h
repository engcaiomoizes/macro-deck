#pragma once

#include <stdint.h>

namespace hal {
    class Clock {
        public:
            static uint64_t milliseconds();
    };
}