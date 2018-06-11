#include "tue/profiling/scoped_timer.h"
#include "tue/profiling/profiler.h"

namespace tue
{

// ----------------------------------------------------------------------------------------------------

ScopedTimer::ScopedTimer(Profiler& profiler, const std::string& label)
    : profiler_(profiler)
{
    profiler_.startTimer(label);
}

// ----------------------------------------------------------------------------------------------------

ScopedTimer::~ScopedTimer()
{
    profiler_.stopTimer();
}

}
