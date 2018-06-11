//////////////////////////////////////////////////////////////////////////////
// Timer.h
// =======
// High Resolution Timer.
// This timer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system 
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2006-01-13
//
// Copyright (c) 2003 Song Ho Ahn
//////////////////////////////////////////////////////////////////////////////

#ifndef TIMER_H_DEF
#define TIMER_H_DEF

#ifdef WIN32   // Windows system specific
#include <windows.h>
#else          // Unix based system specific
#include <sys/time.h>
#endif

#include <iostream>
#include <string>


class Timer
{
public:
    Timer();                                    // default constructor
    ~Timer();                                   // default destructor

    void   start();                             // start timer
    void   stop();                              // stop the timer
    double getElapsedTime() const;                    // get elapsed time in second
    double getElapsedTimeInSec() const;               // get elapsed time in second (same as getElapsedTime)
    double getElapsedTimeInMilliSec() const;          // get elapsed time in milli-second
    double getElapsedTimeInMicroSec() const;    // get elapsed time in micro-second
    void   printLastElapsedTime(std::string);
    void   printLastElapsedTimeMSec(std::string);


protected:


private:
//    double startTimeInMicroSec;                 // starting time in micro-second
//    double endTimeInMicroSec;                   // ending time in micro-second
    int    stopped;                             // stop flag 
#ifdef WIN32
    LARGE_INTEGER frequency;                    // ticks per second
    LARGE_INTEGER startCount;                   //
    LARGE_INTEGER endCount;                     //
#else
    timeval start_count_;                         //
    timeval end_count_;                           //
#endif
};

#define TIMER_START Timer t; t.start();
#define TIMER_STOP(x) (t. printLastElapsedTime(x))
#define TIMER_STOP_M(x) (t.printLastElapsedTimeMSec(x))

#endif // TIMER_H_DEF
