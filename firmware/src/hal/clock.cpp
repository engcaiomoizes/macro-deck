#include "hal/clock.h"

#include "pico/time.h"

namespace hal {
    uint64_t Clock::milliseconds() {
        return to_ms_since_boot(get_absolute_time());
    }
}