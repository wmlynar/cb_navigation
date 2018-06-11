#include "tue/profiling/loop_timer.h"
#include <stdlib.h>

namespace tue
{

LoopTimer::LoopTimer():
    counts_(0),
    sum_(0.0),
    c_(0.0),
    running_(false)
{}

void LoopTimer::start()
{
    ++counts_;
    running_ = true;
    timer_.start();
}

void LoopTimer::stop()
{
    timer_.stop();
    running_ = false;
    long double time = timer_.getElapsedTime();
    long double y = time - c_;
    long double x = sum_ + y;
    c_ = ( x - sum_ ) - y;
    sum_ = x;
}

void LoopTimer::reset()
{
    timer_.stop();
    running_ = false;
    counts_ = 0;
    sum_ = 0.0;
    c_ = 0.0;
}

double LoopTimer::getTotalTime()
{
    if ( running_ )
        this->stop();

    return sum_;
}

double LoopTimer::getAverageTime()
{
    if ( running_ )
        this->stop();

    return sum_/counts_;
}

}

