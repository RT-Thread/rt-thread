# Clock Time Device

## Introduction

The `clock_time` subsystem provides a unified framework for time management in RT-Thread, consolidating the functionality of the legacy `hwtimer`, `ktime`, and `cputime` subsystems into a single, coherent API.

### Key Features

- **Clocksource**: Free-running counter for timekeeping and timestamps
- **Clockevent**: Programmable timeout events for high-precision timing
- **High-Resolution Timers (hrtimer)**: Efficient timer management with linked-list scheduling
- **POSIX Clock Support**: Compatible with standard POSIX clock APIs
- **Boottime Tracking**: Monotonic time since system boot
- **Backward Compatibility**: Compatibility layers for legacy APIs

### Design Philosophy

The clock_time subsystem follows RT-Thread's C-OOP (Object-Oriented Programming in C) design pattern:

1. **Unified Device Abstraction**: `rt_clock_time_device` encapsulates hardware timer capabilities
2. **Operations Structure**: `rt_clock_time_ops` defines hardware-specific operations
3. **Capability Flags**: Explicitly indicates clocksource and clockevent support
4. **Flexible Integration**: Works with both MCU and MPU platforms

## Architecture

```
┌─────────────────────────────────────────────────────────┐
│                   Application Layer                      │
│  (POSIX APIs, Delays, Timekeeping, High-Res Timers)    │
└──────────────────┬──────────────────────────────────────┘
                   │
┌──────────────────▼──────────────────────────────────────┐
│              clock_time Subsystem                        │
│  ┌─────────────┐  ┌──────────┐  ┌──────────────────┐   │
│  │ Clocksource │  │ Boottime │  │ High-Res Timers │   │
│  └─────────────┘  └──────────┘  └──────────────────┘   │
│  ┌─────────────┐  ┌──────────────────────────────┐     │
│  │ Clockevent  │  │    Compatibility Layers      │     │
│  └─────────────┘  └──────────────────────────────┘     │
└──────────────────┬──────────────────────────────────────┘
                   │
┌──────────────────▼──────────────────────────────────────┐
│           Hardware Timer Abstraction                     │
│        (rt_clock_time_device + ops)                     │
└──────────────────┬──────────────────────────────────────┘
                   │
┌──────────────────▼──────────────────────────────────────┐
│              BSP Timer Driver                           │
│   (SysTick, ARM Arch Timer, RISC-V Timer, etc.)        │
└─────────────────────────────────────────────────────────┘
```

## Usage

### Registering a Clock Time Device

BSP drivers should implement the `rt_clock_time_ops` and register a device:

```c
#include <rtdevice.h>

static rt_uint64_t my_timer_get_freq(void)
{
    return 1000000; /* 1MHz timer */
}

static rt_uint64_t my_timer_get_counter(void)
{
    return MY_TIMER->CNT; /* Read hardware counter */
}

static rt_err_t my_timer_set_timeout(rt_uint64_t delta)
{
    if (delta == 0)
    {
        /* Cancel timeout */
        MY_TIMER->CR &= ~TIMER_ENABLE;
        return RT_EOK;
    }
    
    MY_TIMER->CMP = MY_TIMER->CNT + delta;
    MY_TIMER->CR |= TIMER_ENABLE | TIMER_INT_ENABLE;
    return RT_EOK;
}

static const struct rt_clock_time_ops my_timer_ops =
{
    .get_freq = my_timer_get_freq,
    .get_counter = my_timer_get_counter,
    .set_timeout = my_timer_set_timeout,
};

static struct rt_clock_time_device my_clock_device;

int my_timer_init(void)
{
    /* Initialize hardware timer */
    my_clock_device.ops = &my_timer_ops;
    
    /* Register with both clocksource and clockevent capabilities */
    rt_clock_time_device_register(&my_clock_device, 
                                  "hw_timer",
                                  RT_CLOCK_TIME_CAP_CLOCKSOURCE | 
                                  RT_CLOCK_TIME_CAP_CLOCKEVENT);
    
    return 0;
}
INIT_DEVICE_EXPORT(my_timer_init);

/* Timer ISR should call rt_clock_hrtimer_process() */
void MY_TIMER_IRQHandler(void)
{
    /* Clear interrupt flag */
    MY_TIMER->SR = 0;
    
    /* Process hrtimer timeouts */
    rt_clock_hrtimer_process();
}
```

### Using Clocksource APIs

#### Get Time Information

```c
/* Get clock resolution (in ns, scaled by RT_CLOCK_TIME_RESMUL) */
rt_uint64_t res = rt_clock_time_getres();

/* Get clock frequency in Hz */
rt_uint64_t freq = rt_clock_time_getfreq();

/* Get current counter value */
rt_uint64_t cnt = rt_clock_time_getcnt();
```

#### Get Boottime

```c
struct timespec ts;
rt_clock_time_boottime_ns(&ts);
rt_kprintf("Boot time: %d.%09d seconds\n", ts.tv_sec, ts.tv_nsec);

struct timeval tv;
rt_clock_time_boottime_us(&tv);

time_t t;
rt_clock_time_boottime_s(&t);
```

#### Time Conversion

```c
rt_uint64_t cnt = 1000000; /* counter ticks */

/* Convert to time units */
rt_uint64_t ns = rt_clock_time_cnt_to_ns(cnt);
rt_uint64_t us = rt_clock_time_cnt_to_us(cnt);
rt_uint64_t ms = rt_clock_time_cnt_to_ms(cnt);

/* Convert from time units */
cnt = rt_clock_time_ns_to_cnt(1000000); /* 1ms in nanoseconds */
cnt = rt_clock_time_us_to_cnt(1000);    /* 1ms in microseconds */
cnt = rt_clock_time_ms_to_cnt(1);       /* 1ms */
```

### Using High-Resolution Timers

#### Create and Start a Timer

```c
#include <rtdevice.h>

static void timeout_callback(void *param)
{
    rt_kprintf("Timer timeout!\n");
}

void hrtimer_example(void)
{
    struct rt_clock_hrtimer timer;
    
    /* Initialize timer */
    rt_clock_hrtimer_init(&timer, "my_timer", 
                         RT_TIMER_FLAG_ONE_SHOT,
                         timeout_callback, 
                         RT_NULL);
    
    /* Start timer with 1ms delay */
    rt_uint64_t delay_cnt = rt_clock_time_ms_to_cnt(1);
    rt_clock_hrtimer_start(&timer, delay_cnt);
    
    /* ... */
    
    /* Stop timer if needed */
    rt_clock_hrtimer_stop(&timer);
    
    /* Cleanup */
    rt_clock_hrtimer_detach(&timer);
}
```

#### Periodic Timer

```c
static void periodic_callback(void *param)
{
    rt_kprintf("Periodic tick\n");
}

void periodic_timer_example(void)
{
    struct rt_clock_hrtimer timer;
    
    rt_clock_hrtimer_init(&timer, "periodic", 
                         RT_TIMER_FLAG_PERIODIC,
                         periodic_callback, 
                         RT_NULL);
    
    /* Start with 100ms period */
    rt_uint64_t period_cnt = rt_clock_time_ms_to_cnt(100);
    rt_clock_hrtimer_start(&timer, period_cnt);
}
```

### High-Precision Delays

```c
/* Delay in nanoseconds */
rt_clock_ndelay(1000);  /* 1 microsecond */

/* Delay in microseconds */
rt_clock_udelay(1000);  /* 1 millisecond */

/* Delay in milliseconds */
rt_clock_mdelay(100);   /* 100 milliseconds */

/* Using a custom timer for delays */
struct rt_clock_hrtimer timer;
rt_clock_hrtimer_mdelay(&timer, 50);  /* 50ms delay */
```

## Migration Guide

### From ktime

The clock_time subsystem provides direct API compatibility when `RT_CLOCK_TIME_COMPAT_KTIME` is enabled:

| Old ktime API | New clock_time API |
|--------------|-------------------|
| `rt_ktime_boottime_get_ns()` | `rt_clock_time_boottime_ns()` |
| `rt_ktime_cputimer_getres()` | `rt_clock_time_getres()` |
| `rt_ktime_cputimer_getcnt()` | `rt_clock_time_getcnt()` |
| `rt_ktime_hrtimer_init()` | `rt_clock_hrtimer_init()` |
| `rt_ktime_hrtimer_start()` | `rt_clock_hrtimer_start()` |

### From cputime

When `RT_CLOCK_TIME_COMPAT_CPUTIME` is enabled:

| Old cputime API | New clock_time API |
|----------------|-------------------|
| `clock_cpu_gettime()` | `rt_clock_time_getcnt()` |
| `clock_cpu_getres()` | `rt_clock_time_getres()` |
| `rt_cputime_sleep()` | `rt_clock_mdelay()` or use hrtimer |
| `rt_cputime_udelay()` | `rt_clock_udelay()` |

### From hwtimer

Hardware timer devices should be migrated to the new clock_time device model:

**Old hwtimer approach:**
```c
static const struct rt_hwtimer_ops my_ops = { ... };
static struct rt_hwtimer_device my_device;
my_device.ops = &my_ops;
rt_device_hwtimer_register(&my_device, "timer0", RT_NULL);
```

**New clock_time approach:**
```c
static const struct rt_clock_time_ops my_ops = { ... };
static struct rt_clock_time_device my_device;
my_device.ops = &my_ops;
rt_clock_time_device_register(&my_device, "timer0",
    RT_CLOCK_TIME_CAP_CLOCKSOURCE | RT_CLOCK_TIME_CAP_CLOCKEVENT);
```

## Configuration

### Kconfig Options

```
RT_USING_CLOCK_TIME              - Enable clock_time subsystem
RT_CLOCK_TIME_COMPAT_KTIME       - Enable ktime compatibility layer
RT_CLOCK_TIME_COMPAT_CPUTIME     - Enable cputime compatibility layer
RT_CLOCK_TIME_COMPAT_HWTIMER     - Enable hwtimer compatibility layer
```

### Typical Configuration

For new projects:
```
CONFIG_RT_USING_CLOCK_TIME=y
# Compatibility layers not needed
```

For migrating projects:
```
CONFIG_RT_USING_CLOCK_TIME=y
CONFIG_RT_CLOCK_TIME_COMPAT_KTIME=y
CONFIG_RT_CLOCK_TIME_COMPAT_CPUTIME=y
CONFIG_RT_CLOCK_TIME_COMPAT_HWTIMER=y
```

## Best Practices

### For MCU Scenarios

1. **Use SysTick or similar**: For basic timekeeping, SysTick provides adequate resolution
2. **Hardware timers for precision**: Use dedicated hardware timers for microsecond-level precision
3. **Consider power**: Minimize timer wakeups in low-power applications

### For MPU Scenarios

1. **Architecture timers**: Use ARM Generic Timer or RISC-V timer for best performance
2. **SMP safety**: The hrtimer implementation uses spinlocks for SMP systems
3. **High-frequency sources**: MPUs can handle higher frequency timers (MHz range)

### General Guidelines

1. **Single default device**: Register one primary clock_time device as the system default
2. **ISR efficiency**: Keep `rt_clock_hrtimer_process()` call in ISR short
3. **Resolution vs. overhead**: Higher resolution timers have higher overhead
4. **Fallback support**: The tick-based fallback ensures functionality even without hardware timer

## API Reference

See the complete API documentation in `/components/drivers/include/drivers/clock_time.h`.

## Examples

Complete examples can be found in:
- `/examples/clock_time/` - Basic usage examples
- BSP timer driver implementations for reference

## Troubleshooting

### Timer not firing

- Verify hardware timer is properly configured
- Check that ISR calls `rt_clock_hrtimer_process()`
- Ensure timer interrupt is enabled

### Poor precision

- Verify timer frequency is appropriate for your use case
- Check for interrupt latency issues
- Consider using a higher frequency timer

### Compatibility issues

- Enable appropriate compatibility layer in Kconfig
- Check for API signature changes in migration
- Verify BSP-specific timer implementation

## See Also

- [Timer Management](timer.md)
- [Real-Time Clock (RTC)](rtc.md)
- [Device Driver Framework](framework.md)
