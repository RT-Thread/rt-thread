#include <arm-tpl.h>
#include <sys/time.h>
#include "rtthread.h"

#ifndef NANOSECOND_PER_TICK
/* posix clock and timer */
#define MILLISECOND_PER_SECOND  1000UL
#define MICROSECOND_PER_SECOND  1000000UL
#define NANOSECOND_PER_SECOND   1000000000UL

#define MILLISECOND_PER_TICK    (MILLISECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define MICROSECOND_PER_TICK    (MICROSECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define NANOSECOND_PER_TICK     (NANOSECOND_PER_SECOND  / RT_TICK_PER_SECOND)
#endif

extern "C" int __ARM_TPL_clock_realtime(__ARM_TPL_timespec_t* __ts)
{
  unsigned int t = std::time(nullptr);
  __ts->tv_sec = t;
  __ts->tv_nsec = 0;
  return 0;
}

extern "C" int __ARM_TPL_clock_monotonic(__ARM_TPL_timespec_t* __ts)
{
  unsigned int t = rt_tick_get();
  __ts->tv_sec = t / RT_TICK_PER_SECOND;
  __ts->tv_nsec = (t %RT_TICK_PER_SECOND) * NANOSECOND_PER_TICK  ;//TODO 
  return 0;
}
