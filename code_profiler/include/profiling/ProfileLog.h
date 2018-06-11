#ifndef PROFILELOG_H
#define PROFILELOG_H
#ifdef PROFILEAPP
#include <iostream>
#include <vector>
#include <map>

struct Statistics;
class ProfileLog
{
public:
    static void PrintLog(std::ostream& stream, std::vector< std::map< std::string, Statistics >* >&  stats, double totalTime);
    static void PrintLog(std::vector< std::map< std::string, Statistics >* >& stats, double totalTime);

};
#endif

#endif // PROFILELOG_H
