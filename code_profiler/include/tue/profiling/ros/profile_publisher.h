#ifndef TUE_CODE_PROFILER_PROFILING_ROS_PROFILE_PUBLISHER_H_
#define TUE_CODE_PROFILER_PROFILING_ROS_PROFILE_PUBLISHER_H_

#include <ros/publisher.h>

namespace tue
{

class Profiler;

class ProfilePublisher {

public:

    ProfilePublisher();

    virtual ~ProfilePublisher();

    void initialize(const Profiler& profiler);

    void publish() const;

protected:

    const Profiler* profiler_;

    ros::Publisher pub_stats_;

};

}

#endif
