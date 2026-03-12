@page page_device_clock_hrtimer Clock HRTimer

# Overview

The clock hrtimer layer provides high-resolution timeout scheduling on top of
clock_time. It keeps a sorted timeout list, programs the next deadline, and
runs callbacks when the deadline expires.

# Key Concepts

- Time base: delay counts are expressed in the clock source counter units.
- Event programming: the next expiry is converted to event units and sent to
  the clock event device.
- Fallback: if no hardware event exists, a software timer triggers processing.

# API

```c
void rt_clock_hrtimer_init(rt_clock_hrtimer_t timer,
                           const char *name,
                           rt_uint8_t flag,
                           void (*timeout)(void *parameter),
                           void *parameter);
rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long cnt);
rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer);
rt_err_t rt_clock_hrtimer_control(rt_clock_hrtimer_t timer, int cmd, void *arg);
rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer);

void rt_clock_hrtimer_delay_init(struct rt_clock_hrtimer *timer);
void rt_clock_hrtimer_delay_detach(struct rt_clock_hrtimer *timer);
rt_err_t rt_clock_hrtimer_sleep(struct rt_clock_hrtimer *timer, unsigned long cnt);
rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, unsigned long ns);
rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, unsigned long us);
rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, unsigned long ms);
```

Flags reuse RT_TIMER_FLAG_* definitions (one-shot/periodic/hard timer). `cnt`
is a counter delta based on the default clock source.

## rt_clock_hrtimer_init

```c
void rt_clock_hrtimer_init(rt_clock_hrtimer_t timer,
                           const char *name,
                           rt_uint8_t flag,
                           void (*timeout)(void *parameter),
                           void *parameter);
```

- Purpose: initialize a high-resolution timer object.
- Parameters:
  - `timer`: the hrtimer object to initialize.
  - `name`: timer name (truncated to RT_NAME_MAX-1).
  - `flag`: RT_TIMER_FLAG_* (one-shot/periodic/hard timer).
  - `timeout`: callback function on expiry.
  - `parameter`: user parameter passed to the callback.
- Behavior:
  - Clears internal state, initializes list node and completion.
  - Does not start the timer; call `rt_clock_hrtimer_start()` to arm it.
- Context: thread context.

## rt_clock_hrtimer_start

```c
rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long cnt);
```

- Purpose: arm a timer to expire after `cnt` counter ticks.
- Parameters:
  - `cnt`: relative delay in clock source counter units.
- Return values:
  - RT_EOK: timer armed.
  - -RT_ERROR: timer already active or invalid `cnt`.
- Notes:
  - `cnt` must be less than half of the maximum counter range to avoid wrap
    ambiguity.
  - Starting a timer programs the next clock event if this timer becomes the
    earliest deadline.

## rt_clock_hrtimer_stop

```c
rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer);
```

- Purpose: cancel an active timer.
- Return values:
  - RT_EOK: timer stopped.
  - -RT_ERROR: timer was not active.
- Notes: stopping a timer may reprogram the next event.

## rt_clock_hrtimer_control

```c
rt_err_t rt_clock_hrtimer_control(rt_clock_hrtimer_t timer, int cmd, void *arg);
```

- Purpose: query or modify a timer after initialization.
- Common commands (same as RT-Thread timers):
  - RT_TIMER_CTRL_GET_TIME: get `delay_cnt` into `*(unsigned long *)arg`.
  - RT_TIMER_CTRL_SET_TIME: set `delay_cnt` from `*(unsigned long *)arg`.
  - RT_TIMER_CTRL_SET_ONESHOT / RT_TIMER_CTRL_SET_PERIODIC: set mode.
  - RT_TIMER_CTRL_GET_STATE: return activated/deactivated state.
  - RT_TIMER_CTRL_GET_REMAIN_TIME: get absolute timeout counter.
  - RT_TIMER_CTRL_GET_FUNC / RT_TIMER_CTRL_SET_FUNC: get/set callback.
  - RT_TIMER_CTRL_GET_PARM / RT_TIMER_CTRL_SET_PARM: get/set parameter.
- Notes:
  - Changing time or mode while active updates internal deadline but does not
    implicitly restart a stopped timer.

## rt_clock_hrtimer_detach

```c
rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer);
```

- Purpose: detach a timer and wake any waiters.
- Behavior:
  - Marks the timer inactive and wakes `rt_clock_hrtimer_sleep()` waiters with
    an error code.
  - Removes the timer from the list if needed.
- Use case: cleanup when a timer is no longer valid.

## rt_clock_hrtimer_delay_init

```c
void rt_clock_hrtimer_delay_init(struct rt_clock_hrtimer *timer);
```

- Purpose: initialize a one-shot hrtimer for blocking delays.
- Behavior: sets a built-in timeout callback that signals a completion.

## rt_clock_hrtimer_delay_detach

```c
void rt_clock_hrtimer_delay_detach(struct rt_clock_hrtimer *timer);
```

- Purpose: detach a delay timer created by `rt_clock_hrtimer_delay_init()`.
- Notes: safe to call even if the timer has already expired.

## rt_clock_hrtimer_sleep

```c
rt_err_t rt_clock_hrtimer_sleep(struct rt_clock_hrtimer *timer, unsigned long cnt);
```

- Purpose: block the current thread until the delay expires.
- Parameters: `timer` must be initialized (typically by delay_init).
- Return values:
  - RT_EOK: timeout expired normally.
  - -RT_EINTR: interrupted by signal or detach.
  - -RT_EINVAL: `cnt` is zero.
- Context: thread context only.

## rt_clock_hrtimer_ndelay / udelay / mdelay

```c
rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, unsigned long ns);
rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, unsigned long us);
rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, unsigned long ms);
```

- Purpose: sleep for a duration expressed in nanoseconds, microseconds, or
  milliseconds.
- Behavior:
  - Converts the time into counter units using the current clock_time
    resolution and calls `rt_clock_hrtimer_sleep()`.
- Notes:
  - The actual delay is limited by the clock source resolution and event
    programming granularity.

# Typical Flow

1. Initialize a hrtimer with a callback.
2. Convert a time interval to counter units, or use the ndelay/udelay/mdelay
   helpers.
3. Start the timer; the subsystem will program the next event.
4. When the event ISR fires, rt_clock_time_event_isr() runs hrtimer processing
   and dispatches callbacks.

# Example: One-shot Timeout

```c
#include <drivers/clock_time.h>

static struct rt_clock_hrtimer demo_timer;

static void demo_timeout(void *parameter)
{
    RT_UNUSED(parameter);
    rt_kprintf("hrtimer timeout\n");
}

static void demo_hrtimer_start(void)
{
    rt_uint64_t ns = 5ULL * 1000 * 1000; /* 5 ms */
    unsigned long cnt = (unsigned long)rt_clock_time_ns_to_counter(ns);

    rt_clock_hrtimer_init(&demo_timer, "demo", RT_TIMER_FLAG_ONE_SHOT,
                          demo_timeout, RT_NULL);
    rt_clock_hrtimer_start(&demo_timer, cnt);
}
```

# Example: Sleep Helper

```c
static void demo_hrtimer_sleep(void)
{
    struct rt_clock_hrtimer timer;

    rt_clock_hrtimer_delay_init(&timer);
    rt_clock_hrtimer_mdelay(&timer, 10);
    rt_clock_hrtimer_delay_detach(&timer);
}
```

# Notes

- Callbacks may run in interrupt context when using a hardware event device.
- rt_clock_hrtimer_sleep() waits on a completion and may return -RT_EINTR if
  interrupted.
