#include "profiling/Profiler.h"
#ifdef PROFILEAPP
#include "profiling/ProfileLog.h"
#include <iomanip>
#include <boost/filesystem.hpp>
#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;

void ProfileLog::PrintLog(std::ostream &stream, std::vector< std::map< std::string, Statistics >* >& stats, double totalTime)
{
    int threadNum = 0;
    for(vector< map<string, Statistics>* >::iterator it = stats.begin(); it != stats.end(); ++it)
    {
        stream << fixed;
        stream << left;
        stream << "Thread info for thread " << ++threadNum << ":" << std::endl;

        stream << setw(15) << "Name:" << setw(20) << "Total Time:" << setw(30) << "Average time" << setw(30) << "Relative Time:" << setw(15) << "Called #:" << endl;
        stream << setfill('-') << setw(100) << "" << endl;
        stream << setfill(' ');

        for(map<string, Statistics>::iterator it2 = (*it)->begin(); it2 != (*it)->end(); ++it2)
        {
            Statistics stats = it2->second;
            if(!stats.running)
                stream << setw(15) <<  it2->first << setw(20) << stats.msec << setw(30) << (stats.msec / stats.callAmount) << setw(30) << stats.msec/totalTime << setw(30) << stats.callAmount << endl;
            else
                stream << setw(15) <<  it2->first << "ERROR(" << it2->first << ") was never stopped!" << endl;
        }
        cout << endl;
    }

}


void ProfileLog::PrintLog(std::vector< std::map< std::string, Statistics >* >& stats, double totalTime)
{
    ProfileLog::PrintLog(std::cout, stats, totalTime);

}

#endif
