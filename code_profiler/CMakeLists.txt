cmake_minimum_required(VERSION 2.8.3)
project(code_profiler)

find_package(catkin REQUIRED COMPONENTS roscpp message_generation)
find_package(Boost REQUIRED COMPONENTS thread system)

add_message_files(FILES
	Statistics.msg
)

generate_messages(DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
)

catkin_package(
	INCLUDE_DIRS include
	LIBRARIES codeprofiler
	CATKIN_DEPENDS roscpp message_runtime
	DEPENDS Boost
)

include_directories(include ${Boost_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

set(SRC_PROFILING
    src/profiling/Timer.cpp
    src/profiling/ProfileLog.cpp
    src/profiling/StatsPublisher.cpp
    src/profiler.cpp
    src/timer.cpp
    src/scoped_timer.cpp
    src/loop_timer.cpp
    src/ros/profile_publisher.cpp
)

add_library(codeprofiler ${SRC_PROFILING})
target_link_libraries(codeprofiler ${catkin_LIBRARIES} ${Boost_LIBRARIES})
set_property(TARGET codeprofiler PROPERTY COMPILE_DEFINITIONS "PROFILEAPP")

add_executable(profiler_test src/main.cpp)
target_link_libraries(profiler_test codeprofiler)

add_executable(test_profiler test/test_profiler.cpp)
target_link_libraries(test_profiler codeprofiler)

add_executable(test_loop_timer test/test_loop_timer.cpp)
target_link_libraries(test_loop_timer codeprofiler)

add_dependencies(codeprofiler ${PROJECT_NAME}_generate_messages_cpp)
