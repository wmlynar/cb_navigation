#include <tue/profiling/profiler.h>
#include <tue/profiling/scoped_timer.h>

tue::Profiler profiler;

void a()
{
    tue::ScopedTimer t(profiler, "a");
}

void b()
{
    tue::ScopedTimer t(profiler, "b");
    a();
}

void c()
{
    tue::ScopedTimer t(profiler, "c");
    b();
    a();
}

int main(int argc, char **argv) {

    profiler.setName("test");

    profiler.startTimer("total");

    for(unsigned int i = 0; i < 1000; ++i)
    {
        tue::ScopedTimer t_iteration(profiler, "iteration");

        a();
        b();
        c();
    }

    profiler.stopTimer();

    std::cout << profiler << std::endl;

    return 0;
}
