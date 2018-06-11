#ifndef TUE_PROFILING_SCOPED_TIMER_H_
#define TUE_PROFILING_SCOPED_TIMER_H_

#include <string>

namespace tue
{

class Profiler;

class ScopedTimer
{

public:

    ScopedTimer(Profiler& profiler, const std::string& label);

    virtual ~ScopedTimer();

private:

    Profiler& profiler_;

};

}

#endif
