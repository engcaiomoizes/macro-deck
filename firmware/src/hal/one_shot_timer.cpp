#include "hal/one_shot_timer.h"

#include "pico/time.h"

#include "hal/clock.h"

namespace hal {
    OneShotTimer::OneShotTimer(uint32_t intervalMs)
        : m_interval(intervalMs),
          m_startTime(0),
          m_running(false) {}

    void OneShotTimer::restart() {
        m_startTime = Clock::milliseconds();

        m_running = true;
    }

    bool OneShotTimer::expired() {
        if (!m_running) return false;

        uint64_t now = Clock::milliseconds();

        if ((now - m_startTime) < m_interval) return false;

        m_running = false;

        return true;
    }

    bool OneShotTimer::running() const {
        return m_running;
    }
}