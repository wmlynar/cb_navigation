#ifndef PROFILER_H
#define PROFILER_H
#include <string>
#include <map>
#include <vector>
#include <boost/thread.hpp>
#include <boost/utility.hpp>
#include "Timer.h"
#include "profiling/ProfileLog.h"


#ifdef PROFILEAPP

static std::string LOGGING_LOCATION = "~/profile_logs";

struct Statistics
{
    Timer timer;
    double msec;
    int callAmount;

    std::string parent;
    bool running;

    Statistics() : msec(0), callAmount(0), parent(""), running(true) {}
    Statistics(std::string p) : msec(0), callAmount(0), parent(p), running(true){}
};

typedef std::map< std::string, Statistics >  FunctionStats;
typedef std::map< std::string, Statistics >* FunctionStatsPtr;

class ThreadProfiler
{

public:
    ThreadProfiler()
    {
        threadId = boost::this_thread::get_id();
        currentlyProfiling = "";
        stats = new FunctionStats();
    }
    virtual ~ThreadProfiler();

    static void Start(const std::string &name);
    static void Stop(const std::string& name);
    static FunctionStatsPtr ReturnCurrentStatistics();


    FunctionStatsPtr stats;

private:
    boost::thread::id threadId;
    std::string currentlyProfiling;
};

class ThreadProfilerManager
{
public:

    ThreadProfilerManager();

    inline ThreadProfiler& Profiler()
    {
        if(profiler.get() == NULL)
        {
            profiler.reset(new ThreadProfiler());
            boost::lock_guard<boost::mutex> lock(mutex);
            threadStats.push_back(profiler.get()->stats);
        }

        return *profiler.get();
    }

    ~ThreadProfilerManager();
private:
    boost::thread_specific_ptr<ThreadProfiler> profiler;
    boost::mutex mutex;
    std::vector<FunctionStatsPtr> threadStats;
    Timer timer;

};

//Global threadProfiler
static ThreadProfilerManager manager;

//Implementation of ThreadProfiler methods
inline void ThreadProfiler::Start(const std::string& name)
{
    ThreadProfiler& instance = manager.Profiler();
    if(instance.stats->find(name) == instance.stats->end() && !instance.stats->find(name)->second.running)
    {
       (*instance.stats)[name] = Statistics(instance.currentlyProfiling);
    }
    (*instance.stats)[name].timer.start();
    (*instance.stats)[name].running = true;
    instance.currentlyProfiling = name;
}

inline void ThreadProfiler::Stop(const std::string &name)
{
    ThreadProfiler& instance = manager.Profiler();
    FunctionStats::iterator mapIt = instance.stats->find(name);

    if(mapIt == instance.stats->end())
        return;

    mapIt->second.msec += mapIt->second.timer.getElapsedTimeInMilliSec();
    mapIt->second.callAmount++;
    mapIt->second.running = false;
}

inline FunctionStatsPtr ThreadProfiler::ReturnCurrentStatistics()
{
    ThreadProfiler& instance = manager.Profiler();
    return instance.stats;
}

namespace
{
    template<typename T>
    void deleteElement(T t)
    {
        delete t;
    }

    template<typename _Element, typename T>
    void deleteAll(T &t)
    {
        std::for_each(t.begin(), t.end(), deleteElement<_Element>);
    }
}

inline ThreadProfiler::~ThreadProfiler(){ }

inline ThreadProfilerManager::ThreadProfilerManager()
{
    timer.start();
}

inline ThreadProfilerManager::~ThreadProfilerManager()
{
    timer.stop();
    ProfileLog::PrintLog(threadStats, timer.getElapsedTimeInMilliSec());
   deleteAll<FunctionStatsPtr>(threadStats);
}


#else
class ThreadProfiler
{
public:
    static void Start(std::string name);
    static void Stop(std::string name);
};

inline void ThreadProfiler::Start(std::string){}
inline void ThreadProfiler::Stop(std::string){}
#endif

#endif
