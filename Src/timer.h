#ifndef _TIMER_H_
#define _TIMER_H_

#include <cstdio>

enum TimerState {TIMER_STOPPED, TIMER_STARTED, TIMER_PAUSED, TIMER_RESTARTED};

class Timer
{
    public:
    Timer(int t_interval, bool t_started = false,
          bool t_autorestart = true);
    void Start();
    void Stop();
    void Pause();
    TimerState Process();
    TimerState State() {return state;};
    int StopCount();
    int Value() {return value;};
    int Interval() {return interval;};

    protected:
    //std::string name;
            int interval;
            TimerState state;
            bool autorestart;
        int value;
    int stopcount;
};

#endif // _TIMER_H_
