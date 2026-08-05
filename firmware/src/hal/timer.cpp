#include "hal/timer.h"

#include "pico/time.h"

namespace hal {
    Timer::Timer(uint32_t intervalMs) : m_interval(intervalMs), m_lastTime(to_ms_since_boot(get_absolute_time())) {}

    bool Timer::poll() {
        if (!expired()) return false;

        restart();

        return true;
    }

    bool Timer::expired() {
        uint64_t now = to_ms_since_boot(get_absolute_time());

        return (now - m_lastTime) >= m_interval;
    }

    void Timer::restart() {
        m_lastTime = to_ms_since_boot(get_absolute_time());
    }
}