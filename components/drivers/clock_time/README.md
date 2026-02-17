# Clock Time Subsystem

The clock_time subsystem provides a unified time base and event scheduling for
RT-Thread. It separates timekeeping (a monotonic counter) from event delivery
(a programmable timer interrupt) so platforms can combine different hardware
sources while the kernel sees consistent behavior.

## Design Principles
- Monotonic time: time readings never go backward.
- Separation of roles: a clock source provides a counter, a clock event triggers
  deadlines.
- Scaled integer conversion: counters are converted to nanoseconds with a
  resolution scale factor, avoiding floating point.
- Graceful fallback: if a hardware event is unavailable, software timers keep
  the system functional.

## Building Blocks
- Clock source: provides a stable counter and its frequency.
- Clock event: can be programmed to fire at the next deadline.
- Clock timer adapter: exposes a general timer peripheral as a clock source or
  event device.
- Clock hrtimer: software scheduler that orders high-resolution timeouts and
  programs the next event.
- Clock boottime helpers: translate the monotonic counter into common time
  formats for use by higher layers.

## Time Flow
- Read path: counter -> scaled resolution -> nanoseconds.
- Timeout path: hrtimer queue -> next expiry -> program event -> interrupt ->
  dispatch callbacks.

## BSP Integration Guidance
- Provide a stable counter or a programmable timer. One device can serve both
  roles.
- Select a default source and event device to enable accurate timekeeping and
  efficient scheduling.
- Keep ISRs minimal; the core handles conversion and scheduling.
- POSIX time APIs are layered on top of this subsystem and reuse its monotonic
  base.
