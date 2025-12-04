# Clock Time Examples

This directory contains examples demonstrating the use of the unified `clock_time` subsystem.

## Prerequisites

Enable `RT_USING_CLOCK_TIME` in your configuration:
```
CONFIG_RT_USING_CLOCK_TIME=y
```

## Available Examples

### 1. Clock Time Information (`clock_time_info_example`)
Displays basic information about the clock_time device:
- Clock frequency
- Clock resolution
- Current counter value
- Device capabilities

**Usage:**
```
msh> clock_time_info_example
```

### 2. Boottime Tracking (`clock_boottime_example`)
Shows system uptime in different formats:
- Nanosecond precision
- Microsecond precision
- Second precision

**Usage:**
```
msh> clock_boottime_example
```

### 3. Time Conversion (`clock_conversion_example`)
Demonstrates conversion between counter ticks and time units (ms, us, ns).

**Usage:**
```
msh> clock_conversion_example
```

### 4. High-Precision Delay (`clock_delay_example`)
Tests high-precision delay functions and measures actual delays:
- Microsecond delays (`rt_clock_udelay`)
- Millisecond delays (`rt_clock_mdelay`)

**Usage:**
```
msh> clock_delay_example
```

### 5. One-Shot Timer (`clock_hrtimer_oneshot_example`)
Demonstrates using a high-resolution timer for one-shot timeouts.

**Usage:**
```
msh> clock_hrtimer_oneshot_example
```

**Expected Output:**
```
=== High-Resolution Timer (One-Shot) Example ===
Starting timer for 500ms...
Timer started successfully
High-resolution timer fired! Parameter: One-shot timer
Timer example complete
```

### 6. Periodic Timer (`clock_hrtimer_periodic_example`)
Demonstrates using a high-resolution timer for periodic callbacks.

**Usage:**
```
msh> clock_hrtimer_periodic_example
```

**Expected Output:**
```
=== High-Resolution Timer (Periodic) Example ===
Starting periodic timer (200ms period)...
Timer started successfully
Periodic timer tick #1
Periodic timer tick #2
Periodic timer tick #3
Periodic timer tick #4
Periodic timer tick #5
Timer stopped. Total ticks: 5
```

### 7. Performance Benchmark (`clock_benchmark_example`)
Measures the overhead of clock_time operations:
- `get_counter()` call overhead
- Time conversion overhead

**Usage:**
```
msh> clock_benchmark_example
```

### Run All Examples (`clock_time_examples_all`)
Runs all examples in sequence.

**Usage:**
```
msh> clock_time_examples_all
```

## Building the Examples

### Method 1: Include in BSP

Add to your BSP's `applications/SConscript`:
```python
src += Glob('../../examples/clock_time/*.c')
```

### Method 2: Manual Compilation

Copy `clock_time_example.c` to your BSP's `applications` directory and rebuild.

### Method 3: menuconfig

Some BSPs may include examples in menuconfig. Look for:
```
RT-Thread online packages --->
    miscellaneous packages --->
        [*] Enable clock_time examples
```

## Interpreting Results

### Delay Accuracy
The delay examples measure actual vs. target delays. Typical results:
- **Good**: Actual delay within 1-5% of target
- **Acceptable**: Actual delay within 10% of target
- **Poor**: Actual delay > 10% off target (may indicate timer issues)

Factors affecting accuracy:
- Timer resolution
- Interrupt latency
- System load
- Compiler optimizations

### Performance Benchmarks
Typical overhead values (depending on platform):
- `get_counter()`: 10-100 ns per call
- `cnt_to_us()`: 50-500 ns per call

Lower values are better. Very high values may indicate:
- Slow hardware timer access
- Cache misses
- Inefficient implementation

## Troubleshooting

### "RT_USING_CLOCK_TIME is not enabled"
Enable the clock_time subsystem in Kconfig:
```
Device Drivers --->
    [*] Using unified clock_time subsystem
```

### "No clock_time device found"
No clock_time device has been registered. Options:
1. Enable an adapter (e.g., ARM Generic Timer, SysTick)
2. Implement a custom adapter for your hardware
3. The tick-based fallback should be available

### Timer callbacks not firing
If one-shot or periodic timers don't fire:
1. Check that your clock_time device supports `RT_CLOCK_TIME_CAP_CLOCKEVENT`
2. Verify the timer ISR calls `rt_clock_hrtimer_process()`
3. Check interrupt configuration and priority
4. Ensure timer interrupts are enabled

### Inaccurate delays
If delays are consistently off:
1. Verify timer frequency with `clock_time_info_example`
2. Check for interrupt latency issues
3. Ensure timer counter is actually counting
4. Consider using a higher frequency timer

## Advanced Usage

### Custom Timer Callbacks

```c
static void my_callback(void *parameter)
{
    int *count = (int *)parameter;
    (*count)++;
    rt_kprintf("Callback executed %d times\n", *count);
}

void custom_timer_example(void)
{
    struct rt_clock_hrtimer timer;
    int count = 0;
    
    rt_clock_hrtimer_init(&timer, "custom", 
                         RT_TIMER_FLAG_PERIODIC,
                         my_callback, 
                         &count);
    
    unsigned long period = (unsigned long)rt_clock_time_ms_to_cnt(100);
    rt_clock_hrtimer_start(&timer, period);
    
    /* Let it run... */
    rt_thread_mdelay(1000);
    
    rt_clock_hrtimer_stop(&timer);
    rt_clock_hrtimer_detach(&timer);
}
```

### Precision Timing

```c
void measure_function_time(void)
{
    unsigned long start = (unsigned long)rt_clock_time_getcnt();
    
    /* Function to measure */
    my_function();
    
    unsigned long end = (unsigned long)rt_clock_time_getcnt();
    unsigned long delta = end - start;
    
    rt_kprintf("Function took %u us\n", 
               (rt_uint32_t)rt_clock_time_cnt_to_us(delta));
}
```

## See Also

- [Clock Time Documentation](../../documentation/6.components/device-driver/clock_time.md)
- [Clock Time README](../../components/drivers/clock_time/README.md)
- [Adapter Examples](../../components/drivers/clock_time/adapters/)
