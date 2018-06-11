#ifndef CODE_PROFILER_STATS_PUBLISHER_H_
#define CODE_PROFILER_STATS_PUBLISHER_H_

#include <string>
#include <map>
#include <stack>
#include <ros/publisher.h>

#include "profiling/Timer.h"

struct ScopeStat
{

    ScopeStat() {}

    ScopeStat(const std::string& name_) : name(name_) {}

    std::string name;
    Timer timer;
};

class StatsPublisher
{

public:

    StatsPublisher();

    virtual ~StatsPublisher();

    void initialize();

    void startTimer(const std::string& label);

    void stopTimer(const std::string& label);

    void publish() const;

protected:

    ros::Publisher pub_stats_;

    std::map<std::string, Timer> timers_;

    std::stack<ScopeStat> stack_;




};

#endif
