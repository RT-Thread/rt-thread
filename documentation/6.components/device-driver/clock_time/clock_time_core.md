@page page_device_clock_time_core Clock Time Core

# Overview

The clock_time core defines the device model and conversion helpers used by the
subsystem. It manages the default clock source and clock event devices and
provides fixed-point conversion between counters and nanoseconds.

# Device Model

## Clock Time Operations

```c
struct rt_clock_time_ops
{
    rt_uint64_t (*get_freq)(struct rt_clock_time_device *dev);
    rt_uint64_t (*get_counter)(struct rt_clock_time_device *dev);
    rt_err_t    (*set_timeout)(struct rt_clock_time_device *dev, rt_uint64_t delta);
};
```

### get_freq

- Purpose: return the counter frequency in Hz.
- Requirements:
  - Must be stable and match the source used by get_counter.
  - Should be non-zero; zero indicates the device is not ready.

### get_counter

- Purpose: return a monotonically increasing counter value.
- Requirements:
  - Must not go backwards.
  - Wrap behavior is allowed but should be consistent with the width of the
    counter used by the device.

### set_timeout

- Purpose: program the next timeout relative to the current counter value.
- Parameters: `delta` is in the same counter units returned by get_counter.
- Behavior:
  - If `delta` is 0 and the hardware supports it, the event can be canceled.
  - Return -RT_ENOSYS when the device does not support event programming.

## Clock Time Device

```c
struct rt_clock_time_device
{
    struct rt_device parent;
    const struct rt_clock_time_ops *ops;
    rt_uint64_t res_scale;
    rt_uint8_t caps; /* RT_CLOCK_TIME_CAP_SOURCE / RT_CLOCK_TIME_CAP_EVENT */
};
```

- res_scale provides extra precision in the conversion pipeline. If set to 0,
  RT_CLOCK_TIME_RESMUL is used by default.
- caps advertises whether the device can be used as a clock source, a clock
  event, or both.

## Register and Select Devices

```c
rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev,
                                       const char *name,
                                       rt_uint8_t caps);
void rt_clock_time_set_default_source(struct rt_clock_time_device *dev);
void rt_clock_time_set_default_event(struct rt_clock_time_device *dev);
struct rt_clock_time_device *rt_clock_time_get_default_source(void);
struct rt_clock_time_device *rt_clock_time_get_default_event(void);
```

### rt_clock_time_device_register

- Purpose: register a clock_time device and its capabilities.
- Parameters:
  - `dev`: device object with ops and res_scale initialized.
  - `name`: device name; if NULL, only capability registration is performed.
  - `caps`: RT_CLOCK_TIME_CAP_SOURCE and/or RT_CLOCK_TIME_CAP_EVENT.
- Behavior:
  - Registers the device under RT_Device_Class_Timer when `name` is provided.
  - If this is the first source, it becomes the default source.
  - If this is the first event, it becomes the default event.
- Return values:
  - RT_EOK on success.
  - Negative error code if device registration fails.

### rt_clock_time_set_default_source / rt_clock_time_set_default_event

- Purpose: explicitly select the default source or event device.
- Behavior: overrides the auto-selected default.

### rt_clock_time_get_default_source / rt_clock_time_get_default_event

- Purpose: query the current default devices.
- Behavior:
  - Source defaults to the internal tick-based device if none was registered.
  - Event returns NULL if no event device is available.

### rt_clock_time_source_init

- Purpose: BSP hook to register an architecture counter or board source.
- Notes: this function is weak and may be overridden by BSP code.

# Clock Time Query APIs

```c
rt_uint64_t rt_clock_time_get_freq(void);
rt_uint64_t rt_clock_time_get_counter(void);
rt_uint64_t rt_clock_time_get_event_freq(void);
rt_uint64_t rt_clock_time_get_event_res_scaled(void);
```

## rt_clock_time_get_freq

- Purpose: return the frequency of the default source in Hz.
- Return values:
  - Non-zero frequency on success.
  - 0 if no valid source is available.

## rt_clock_time_get_counter

- Purpose: return the current counter from the default source.
- Return values:
  - Monotonic counter value on success.
  - 0 if no valid source is available.

## rt_clock_time_get_event_freq

- Purpose: return the event device frequency in Hz.
- Behavior: if no event device exists, falls back to the default source.

## rt_clock_time_get_event_res_scaled

- Purpose: return the scaled resolution for the event device.
- Behavior: if no event device exists, falls back to the default source.

# Conversion Helpers

```c
rt_uint64_t rt_clock_time_get_res_scaled(void);
rt_uint64_t rt_clock_time_counter_to_ns(rt_uint64_t cnt);
rt_uint64_t rt_clock_time_ns_to_counter(rt_uint64_t ns);
```

## rt_clock_time_get_res_scaled

- Purpose: return the scaled resolution for the default source.
- Return values:
  - Non-zero scaled resolution when the source is ready.
  - 0 when the source is missing or frequency is invalid.

## rt_clock_time_counter_to_ns

- Purpose: convert a counter value to nanoseconds based on the default source.
- Notes: returns 0 when resolution is unavailable.

## rt_clock_time_ns_to_counter

- Purpose: convert nanoseconds to counter units for the default source.
- Notes: returns 0 when resolution is unavailable.

Internally, the core computes a scaled resolution:

```
res_scaled = (1e9 * res_scale) / freq
```

Nanoseconds are then derived using the scale factor RT_CLOCK_TIME_RESMUL to
avoid floating-point math. This keeps precision stable even when freq is not a
power of ten.

# Event API

```c
rt_err_t rt_clock_time_set_timeout(rt_uint64_t delta);
void rt_clock_time_event_isr(void);
```

## rt_clock_time_set_timeout

- Purpose: program the next event using the default event device.
- Parameters: `delta` in event counter units (same as event get_counter).
- Return values:
  - RT_EOK on success.
  - -RT_ENOSYS if no event device exists or set_timeout is unsupported.

## rt_clock_time_event_isr

- Purpose: drive the hrtimer scheduler when an event expires.
- Usage:
  - Call from the hardware timer ISR after acknowledging the interrupt.
  - This function processes expired hrtimers and programs the next event.

# BSP Integration Example

## Register a Clock Source

```c
static rt_uint64_t demo_get_freq(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    return 10000000ULL; /* 10 MHz */
}

static rt_uint64_t demo_get_counter(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    return demo_hw_counter_read();
}

static const struct rt_clock_time_ops demo_src_ops =
{
    demo_get_freq,
    demo_get_counter,
    RT_NULL,
};

static struct rt_clock_time_device demo_src_dev =
{
    .ops = &demo_src_ops,
    .res_scale = RT_CLOCK_TIME_RESMUL,
};

void rt_clock_time_source_init(void)
{
    rt_clock_time_device_register(&demo_src_dev, "clock_time_demo_src",
                                  RT_CLOCK_TIME_CAP_SOURCE);
    rt_clock_time_set_default_source(&demo_src_dev);
}
```

## Register a Clock Event

```c
static rt_err_t demo_set_timeout(struct rt_clock_time_device *dev, rt_uint64_t delta)
{
    RT_UNUSED(dev);
    return demo_hw_timer_program(delta);
}

static const struct rt_clock_time_ops demo_evt_ops =
{
    demo_get_freq,
    demo_get_counter,
    demo_set_timeout,
};

static struct rt_clock_time_device demo_evt_dev =
{
    .ops = &demo_evt_ops,
    .res_scale = RT_CLOCK_TIME_RESMUL,
};

static void demo_timer_isr(void)
{
    demo_hw_timer_ack();
    rt_clock_time_event_isr();
}

void demo_register_event(void)
{
    rt_clock_time_device_register(&demo_evt_dev, "clock_time_demo_evt",
                                  RT_CLOCK_TIME_CAP_EVENT);
    rt_clock_time_set_default_event(&demo_evt_dev);
}
```

# Notes

- Event callbacks may run in interrupt context when backed by a hardware event.
- If no event device is available, the hrtimer subsystem falls back to a
  software timer.
