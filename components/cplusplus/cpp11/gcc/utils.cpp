#include "__utils.h"
#include <sys/time.h>

tick_clock::time_point tick_clock::now()
{
    tick_clock::rep cur_tk = clock();
    tick_clock::duration cur_time(cur_tk);

    return tick_clock::time_point(cur_time);
}

real_time_clock::time_point real_time_clock::now() noexcept
{
    timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);

    return time_point(duration(std::chrono::seconds(tp.tv_sec))
                        + std::chrono::nanoseconds(tp.tv_nsec));
}