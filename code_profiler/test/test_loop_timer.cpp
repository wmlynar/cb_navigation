#include <tue/profiling/loop_timer.h>

class LoopTimerTest
{
    tue::LoopTimer lt1_, lt2_, lt3_;
    tue::Timer timer_;
    int n_;
    double tot_;

public:
    LoopTimerTest(int n): n_(n), tot_(0.0)
    {}

    void run( )
    {
        lt1_.start();

        for ( int i = 0; i < n_; ++i )
        {
            lt2_.start();

            for ( int j = 0; j < n_; ++j )
            {
                timer_.start();
                timer_.stop();
                tot_ += timer_.getElapsedTime();
                lt3_.start();
                lt3_.stop();
            }

            lt2_.stop();
        }

        lt3_.stop();
    }

    void printResults()
    {
        std::cout << "Total times (using Kahan summation) over " << n_*n_ << " loops: "
                  << "\n\ttimer1: " << lt1_.getTotalTime()*1e3 << " ms"
                  << "\n\ttimer2: " << lt2_.getTotalTime()*1e3 << " ms"
                  << "\n\ttimer3: " << lt3_.getTotalTime()*1e3 << " ms"
                  << "\n" << std::endl;

        std::cout << "tue::timer total time: " << tot_*1e3 << " ms (without numerical error compensation)\n" << std::endl;

        std::cout << "Average times using Kahan summation: over " << n_*n_ << " loops: "
                  << "\n\ttimer1: " << lt1_.getAverageTime()*1e3 << " ms"
                  << "\n\ttimer2: " << lt2_.getAverageTime()*1e3 << " ms"
                  << "\n\ttimer3: " << lt3_.getAverageTime()*1e3 << " ms"
                  << "\n" << std::endl;

        std::cout << "tue::timer average time: " << tot_/(n_*n_)*1e3 << " ms (without numerical error compensation)\n" << std::endl;
    }
};

int main(int argc, char **argv) {

    LoopTimerTest ltt(1000);

    ltt.run();

    ltt.printResults();

    return 0;
}
