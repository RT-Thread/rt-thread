# Clock Time Subsystem

## Overview

The `clock_time` subsystem is a unified framework for time management in RT-Thread, replacing the legacy `hwtimer`, `ktime`, and `cputime` subsystems with a single, coherent API.

## Background

Previously, RT-Thread had three separate time-related subsystems:

1. **hwtimer**: Device abstraction for hardware timers with read/write interfaces
2. **cputime**: CPU time tracking with ops structure for high-resolution counters
3. **ktime**: Kernel time with boottime tracking and high-resolution timers (hrtimer)

These subsystems had overlapping functionality, inconsistent APIs, and no clear separation of concerns, leading to:
- Confusion about which subsystem to use
- Duplicated code in BSP drivers
- Difficulty maintaining compatibility
- Scattered documentation

## Design Goals

The `clock_time` subsystem addresses these issues by:

1. **Unification**: Single device abstraction (`rt_clock_time_device`) for all timer hardware
2. **Clarity**: Clear separation between clocksource (counter) and clockevent (timeout) capabilities
3. **Compatibility**: Backward compatibility layers for all legacy APIs
4. **Simplicity**: Fewer concepts to learn, easier BSP integration
5. **Flexibility**: Works with both MCU (tick-based fallback) and MPU (high-res timers) platforms

## Architecture

```
┌─────────────────────────────────────────────┐
│         Application / POSIX APIs            │
└───────────────────┬─────────────────────────┘
                    │
┌───────────────────▼─────────────────────────┐
│         Unified clock_time API              │
│  - Clocksource (counter, boottime)          │
│  - Clockevent (timeout, hrtimer)            │
│  - Time conversion utilities                │
└───────────────────┬─────────────────────────┘
                    │
┌───────────────────▼─────────────────────────┐
│      rt_clock_time_device + ops             │
│  Capability flags: CLOCKSOURCE | CLOCKEVENT │
└───────────────────┬─────────────────────────┘
                    │
┌───────────────────▼─────────────────────────┐
│         BSP Hardware Timer Driver           │
│  (SysTick, ARM Timer, RISC-V Timer, etc.)   │
└─────────────────────────────────────────────┘
```

## Key Components

### 1. Clock Time Device

The `rt_clock_time_device` structure encapsulates a hardware timer with:
- **ops**: Operations structure (`rt_clock_time_ops`)
- **caps**: Capability flags indicating supported features
- **res_scale**: Resolution scaling factor

### 2. Operations Structure

```c
struct rt_clock_time_ops
{
    rt_uint64_t (*get_freq)(void);                  /* Get frequency in Hz */
    rt_uint64_t (*get_counter)(void);               /* Get current counter */
    rt_err_t    (*set_timeout)(rt_uint64_t delta);  /* Set timeout, 0 to cancel */
};
```

### 3. Capabilities

- `RT_CLOCK_TIME_CAP_CLOCKSOURCE`: Provides free-running counter for timekeeping
- `RT_CLOCK_TIME_CAP_CLOCKEVENT`: Supports programmable timeout events

### 4. High-Resolution Timers

The `rt_clock_hrtimer` provides:
- One-shot and periodic timers
- Sorted linked-list scheduling
- SMP-safe spinlock protection
- Fallback to software timers when hardware timeout is unavailable

## Migration Guide

### For BSP Developers

**Old hwtimer approach:**
```c
static const struct rt_hwtimer_ops my_ops = { ... };
static struct rt_hwtimer_device my_device;
rt_device_hwtimer_register(&my_device, "timer0", RT_NULL);
```

**New clock_time approach:**
```c
static const struct rt_clock_time_ops my_ops = {
    .get_freq = my_get_freq,
    .get_counter = my_get_counter,
    .set_timeout = my_set_timeout,
};
static struct rt_clock_time_device my_device;
my_device.ops = &my_ops;
rt_clock_time_device_register(&my_device, "timer0",
    RT_CLOCK_TIME_CAP_CLOCKSOURCE | RT_CLOCK_TIME_CAP_CLOCKEVENT);
```

### For Application Developers

**Old cputime/ktime APIs** still work when compatibility layers are enabled:
- `clock_cpu_gettime()` → `rt_clock_time_getcnt()`
- `rt_ktime_boottime_get_ns()` → `rt_clock_time_boottime_ns()`
- `rt_ktime_hrtimer_start()` → `rt_clock_hrtimer_start()`

**Recommended new APIs:**
```c
/* Get time information */
rt_uint64_t freq = rt_clock_time_getfreq();
rt_uint64_t cnt = rt_clock_time_getcnt();

/* High-precision delays */
rt_clock_udelay(100);  /* 100 microseconds */
rt_clock_mdelay(10);   /* 10 milliseconds */

/* High-resolution timers */
struct rt_clock_hrtimer timer;
rt_clock_hrtimer_init(&timer, "my_timer", RT_TIMER_FLAG_ONE_SHOT,
                     callback, param);
rt_clock_hrtimer_start(&timer, delay_cnt);
```

## Compatibility Layers

Three compatibility layers are provided via Kconfig:

1. **RT_CLOCK_TIME_COMPAT_KTIME**: Enables ktime API compatibility
2. **RT_CLOCK_TIME_COMPAT_CPUTIME**: Enables cputime API compatibility  
3. **RT_CLOCK_TIME_COMPAT_HWTIMER**: Enables hwtimer device API compatibility

These allow gradual migration without breaking existing code.

## File Structure

```
components/drivers/clock_time/
├── Kconfig                      # Configuration options
├── SConscript                   # Build script
├── src/
│   ├── clock_time.c            # Core device management
│   ├── hrtimer.c               # High-resolution timer implementation
│   ├── clock_time_tick.c       # Tick-based fallback adapter
│   ├── ktime_compat.c          # ktime compatibility layer
│   └── cputime_compat.c        # cputime compatibility layer
└── include/drivers/
    └── clock_time.h            # Public API header
```

## Testing Status

- [x] Basic compilation verified
- [ ] BSP integration examples created
- [ ] QEMU runtime testing
- [ ] CI build verification
- [ ] Performance benchmarking

## Known Limitations

1. **Type width**: `unsigned long` is used for counter values to maintain ktime compatibility. On 32-bit systems, this limits maximum counter values. For very high-frequency timers (>4GHz), consider using 64-bit platforms or prescaling.

2. **Fallback mode**: When no hardware clockevent is available, the system falls back to software timers (tick-based). This provides lower precision but ensures functionality.

3. **Migration timeline**: The old subsystems are marked as deprecated but not removed to allow time for migration.

## Future Work

1. **Architecture-specific optimizations**: Add optimized adapters for common architectures (ARM Generic Timer, RISC-V timer, etc.)
2. **Power management integration**: Better support for low-power modes with clock gating
3. **Advanced scheduling**: Consider red-black tree for timer scheduling in scenarios with many concurrent timers
4. **Complete migration**: Remove deprecated subsystems after all BSPs migrate

## Documentation

- [English Documentation](../../documentation/6.components/device-driver/clock_time.md)
- [Chinese Documentation](../../documentation/6.components/device-driver/clock_time_zh.md)

## Contributing

When contributing to clock_time:

1. Maintain backward compatibility with existing APIs
2. Add tests for new functionality
3. Update documentation
4. Follow RT-Thread coding style
5. Consider both MCU and MPU use cases

## References

- Issue: [Feature] 对 hwtimer/ktime/cputime 进行整体重构
- Design discussion in issue comments
- POSIX clock APIs: clock_gettime(2), clock_settime(2)
- Linux clocksource/clockevent framework
