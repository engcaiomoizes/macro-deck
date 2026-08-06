#include "hal/periodic_timer.h"

#include "pico/time.h"

#include "hal/clock.h"

namespace hal {
    PeriodicTimer::PeriodicTimer(uint32_t intervalMs) : m_interval(intervalMs), m_lastTime(to_ms_since_boot(get_absolute_time())) {}

    bool PeriodicTimer::poll() {
        if (!expired()) return false;

        restart();

        return true;
    }

    bool PeriodicTimer::expired() const {
        uint64_t now = Clock::milliseconds();

        return (now - m_lastTime) >= m_interval;
    }

    void PeriodicTimer::restart() {
        m_lastTime = Clock::milliseconds();
    }
}