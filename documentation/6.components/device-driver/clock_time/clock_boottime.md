@page page_device_clock_boottime Clock Boottime Helpers

# Overview

Boottime helpers convert the clock_time monotonic counter into standard time
formats. The resulting values represent time since boot and do not depend on
RTC or wall-clock settings.

# API

```c
rt_err_t rt_clock_boottime_get_us(struct timeval *tv);
rt_err_t rt_clock_boottime_get_s(time_t *t);
rt_err_t rt_clock_boottime_get_ns(struct timespec *ts);
```

All functions return RT_EOK on success or -RT_ERROR if the clock source is
unavailable. The returned values are monotonic and suitable for measuring
elapsed time.

## rt_clock_boottime_get_us

```c
rt_err_t rt_clock_boottime_get_us(struct timeval *tv);
```

- Purpose: get time since boot as seconds + microseconds.
- Parameters: `tv` must be a valid pointer to `struct timeval`.
- Return values:
  - RT_EOK: data written to `tv`.
  - -RT_ERROR: no valid clock_time source or conversion failed.
- Notes:
  - `tv_usec` is derived from the clock_time resolution and may not be exact
    microseconds if the underlying counter does not align to 1 us.

## rt_clock_boottime_get_s

```c
rt_err_t rt_clock_boottime_get_s(time_t *t);
```

- Purpose: get time since boot in whole seconds.
- Parameters: `t` must be a valid pointer to `time_t`.
- Return values:
  - RT_EOK: `*t` updated.
  - -RT_ERROR: no valid clock_time source or conversion failed.
- Notes:
  - Sub-second precision is discarded; use `rt_clock_boottime_get_us()` or
    `rt_clock_boottime_get_ns()` if needed.

## rt_clock_boottime_get_ns

```c
rt_err_t rt_clock_boottime_get_ns(struct timespec *ts);
```

- Purpose: get time since boot as seconds + nanoseconds.
- Parameters: `ts` must be a valid pointer to `struct timespec`.
- Return values:
  - RT_EOK: data written to `ts`.
  - -RT_ERROR: no valid clock_time source or conversion failed.
- Notes:
  - `tv_nsec` reflects the clock_time resolution; it may not be 1 ns granularity
    if the counter frequency is lower.

# Example

```c
#include <drivers/clock_time.h>

static void demo_boottime(void)
{
    struct timespec ts;

    if (rt_clock_boottime_get_ns(&ts) == RT_EOK)
    {
        rt_kprintf("boottime: %ld.%09ld\n", (long)ts.tv_sec, ts.tv_nsec);
    }
}
```

# Notes

- The boottime helpers are used by the soft RTC implementation to build a
  stable base time.
- If no clock_time source is registered, the subsystem falls back to the tick
  counter and the resolution matches RT_TICK_PER_SECOND.
