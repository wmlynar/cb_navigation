#ifndef TUE_LOOP_TIMER_H_DEF
#define TUE_LOOP_TIMER_H_DEF


#include <iostream>
#include <tue/profiling/timer.h>

namespace tue
{

class LoopTimer
{
    tue::Timer timer_;              // Timer doing the work
    long unsigned int counts_;      // Loop counter
    long double sum_;               // Sum so far
    long double c_;                 // Compensation for lost low-order bits
    bool running_;                  // Indicates that timer is running

public:
    LoopTimer();

    void start();
    void stop();
    void reset();

    double getTotalTime();
    double getAverageTime();
};

}

#endif // TUE_LOOP_TIMER_H_DEF
