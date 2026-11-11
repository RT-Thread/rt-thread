@page page_device_clock_time Clock Time Subsystem

# Overview

The clock_time subsystem provides a unified, high-resolution time base and
programmable event scheduling for RT-Thread. It decouples a monotonic counter
(clock source) from deadline delivery (clock event), so platforms can mix
hardware counters and timers while the kernel and libc see consistent behavior.

# Architecture

![Clock time architecture](figures/clock_time_arch.svg)

## Layering and Responsibilities

- Upper layers:
  - POSIX/libc time APIs (clock_gettime, nanosleep) use boottime and hrtimer APIs.
  - Soft RTC uses boottime as its monotonic time base for timekeeping.
  - Device drivers (input event timestamps, vDSO, PIC statistics) use boottime
    for timestamping.
- clock_time subsystem: core APIs, clock source/event devices, the hrtimer
  scheduler, boottime helpers, and the clock_timer adapter.
- Lower layers: BSP drivers provide hardware counters and timers, which are
  wrapped as clock_time devices or clock_timer devices.

## Internal Components

- Core API (clock_time_core.c)
  - Registers clock_time devices, manages default source/event selection, and
    provides counter <-> nanosecond conversion with fixed-point scaling.
- Clock source device (rt_clock_time_device + RT_CLOCK_TIME_CAP_SOURCE)
  - Supplies a free-running counter and frequency for monotonic time reads.
- Clock event device (rt_clock_time_device + RT_CLOCK_TIME_CAP_EVENT)
  - Programs the next deadline and calls rt_clock_time_event_isr() on expiry.
- Clock hrtimer (clock_hrtimer.c)
  - Schedules high-resolution timeouts, programs the next event, and dispatches
    callbacks. Falls back to software timer when no hardware event is available.
- Boottime helpers (clock_boottime.c)
  - Converts the monotonic counter into timeval/timespec/seconds for upper
    layers.
- Clock timer adapter (clock_timer.c)
  - Exposes a unified hardware timer device (rt_clock_timer) and can register
    itself as a clock_time event device.
- Architecture sources (arch/* and clock_time_arm_arch.c)
  - Provide fast CPU counters or architectural timers and register them as the
    default clock source when available.

## Data Flow

- Read path
  - Clock source counter -> scaled resolution -> nanoseconds -> boottime or
    clock_gettime.
- Timeout path
  - HRTimer queue -> next expiry -> set_timeout on event device -> event ISR ->
    hrtimer processing -> callbacks.

# Configuration

Enable the subsystem in menuconfig:

```
RT-Thread Components ->
    Device Drivers ->
        [*] Clock time subsystem (RT_USING_CLOCK_TIME)
```

Optional settings:

- CLOCK_TIMER_FREQ (RISC-V): base counter frequency used by the clock source.
- RT_CLOCK_TIME_ARM_ARCH: enable ARM architected timer integration (DM/OFW).

# BSP Integration Checklist

- Provide a clock source:
  - Register a rt_clock_time_device with CAP_SOURCE, or use the provided
    architecture source (AArch64/RISC-V) via rt_clock_time_source_init().
- Provide a clock event:
  - Register a rt_clock_time_device with CAP_EVENT and call
    rt_clock_time_event_isr() in its interrupt handler.
  - Or register a rt_clock_timer device; it can become the default event
    device automatically.
- Keep event ISRs short; heavy work should run in thread context if needed.

# Detailed Documents

- @subpage page_device_clock_time_core
- @subpage page_device_clock_hrtimer
- @subpage page_device_clock_boottime
- @subpage page_device_clock_timer
