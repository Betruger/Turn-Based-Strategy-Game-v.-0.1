#include "timer.h"


Timer::Timer(int t_interval, bool t_started, bool t_autorestart)
: interval(t_interval), state(TIMER_STOPPED), autorestart(t_autorestart),
value (0), stopcount(-1)
{
    if (t_started) Start();
    else Stop();
}

void Timer::Start()
{
    if (state != TIMER_PAUSED) value = interval;
    state = TIMER_STARTED;
}

void Timer::Stop()
{
    state = TIMER_STOPPED;
    value = 0;
    stopcount++;
}

void Timer::Pause()
{
    state = TIMER_PAUSED;
}

TimerState Timer::Process(/*double time*/)
{
       //     printf("okk");
    if (state == TIMER_STARTED) value -= 1;
    if (value <= 0)
    {
        if (autorestart)
        {
            value += interval;
            return TIMER_RESTARTED;
        }
        else
        {
            value = 0;
            state = TIMER_STOPPED;
        }
    }

    return state;
}

int Timer::StopCount()
{
    return stopcount;
}
