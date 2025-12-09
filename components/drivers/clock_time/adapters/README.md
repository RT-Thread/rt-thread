# Clock Time Adapters

This directory contains reference adapter implementations for various hardware timers.
These adapters demonstrate how to integrate hardware timers with the unified `clock_time` subsystem.

## Available Adapters

### 1. ARM Generic Timer (`clock_time_arm_gtimer.c`)

**Target Platforms:**
- ARMv7-A (ARM Cortex-A with Generic Timer)
- ARMv8-A/ARMv8-R (AArch64 and AArch32)

**Features:**
- Clocksource: Uses CNTPCT (physical counter)
- Clockevent: Uses CNTP_TVAL/CVAL for programmable interrupts
- Full capabilities: Both CLOCKSOURCE and CLOCKEVENT

**Usage:**
```c
// In your BSP board.c or timer initialization
rt_clock_time_arm_gtimer_init();

// In your timer ISR
void ARM_GTIMER_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_time_arm_gtimer_isr();
    rt_interrupt_leave();
}
```

**Registers Used:**
- CNTFRQ_EL0: Counter frequency
- CNTPCT_EL0: Physical counter value
- CNTP_TVAL_EL0: Timer value (countdown)
- CNTP_CTL_EL0: Timer control

### 2. SysTick/DWT (`clock_time_systick.c`)

**Target Platforms:**
- ARM Cortex-M0/M0+/M3/M4/M7/M33/M55

**Features:**
- Clocksource: Uses DWT CYCCNT (cycle counter) if available
- Falls back to tick counter if DWT is not available
- Clockevent: Not supported (SysTick is used for system tick)

**Usage:**
```c
// DWT is automatically enabled during initialization
// No ISR needed - this is clocksource only

// Optional: Set CPU frequency if SystemCoreClock is not accurate
rt_clock_time_systick_set_freq(168000000); // 168 MHz
```

**Notes:**
- DWT may not be available on all Cortex-M cores or may be disabled by debugger
- Provides microsecond-level precision on typical MCUs (>= 1 MHz clock)
- For clockevent capability, pair with a hardware timer (TIM, LPTIM, etc.)

## Creating Your Own Adapter

To create an adapter for your hardware timer:

### Step 1: Implement the ops structure

```c
static rt_uint64_t my_timer_get_freq(void)
{
    return TIMER_FREQUENCY_HZ;
}

static rt_uint64_t my_timer_get_counter(void)
{
    return MY_TIMER->COUNT;  /* Read hardware counter */
}

static rt_err_t my_timer_set_timeout(rt_uint64_t delta)
{
    if (delta == 0)
    {
        /* Cancel timeout */
        MY_TIMER->CTRL &= ~TIMER_ENABLE;
        return RT_EOK;
    }
    
    /* Set compare value for interrupt */
    MY_TIMER->COMPARE = MY_TIMER->COUNT + delta;
    MY_TIMER->CTRL |= TIMER_ENABLE | TIMER_INT_ENABLE;
    
    return RT_EOK;
}

static const struct rt_clock_time_ops my_timer_ops =
{
    .get_freq = my_timer_get_freq,
    .get_counter = my_timer_get_counter,
    .set_timeout = my_timer_set_timeout,
};
```

### Step 2: Register the device

```c
int my_timer_init(void)
{
    static struct rt_clock_time_device my_device;
    
    /* Initialize hardware */
    // ... hardware setup code ...
    
    my_device.ops = &my_timer_ops;
    
    /* Register with appropriate capabilities */
    return rt_clock_time_device_register(&my_device, "my_timer",
        RT_CLOCK_TIME_CAP_CLOCKSOURCE | RT_CLOCK_TIME_CAP_CLOCKEVENT);
}
INIT_DEVICE_EXPORT(my_timer_init);
```

### Step 3: Implement ISR (if using clockevent)

```c
void MY_TIMER_IRQHandler(void)
{
    rt_interrupt_enter();
    
    /* Clear hardware interrupt flag */
    MY_TIMER->STATUS = TIMER_INT_FLAG;
    
    /* Process high-resolution timer timeouts */
    rt_clock_hrtimer_process();
    
    rt_interrupt_leave();
}
```

## Capability Selection Guidelines

### Clocksource Only
Use when:
- Timer can only provide a counter, no interrupt capability
- Timer is already used for system tick
- Examples: SysTick (used for OS tick), Read-only counters

### Clockevent Only
Use when:
- Timer can generate interrupts but has no readable counter
- Rare case, most timers have both

### Both Clocksource and Clockevent
Use when:
- Timer has a readable counter AND can generate interrupts
- This is the most common and preferred configuration
- Examples: ARM Generic Timer, most hardware timers

## Performance Considerations

### Counter Frequency
- **Low frequency (1-100 kHz)**: Good for power-sensitive applications, limited precision
- **Medium frequency (1-10 MHz)**: Good balance for most MCU applications
- **High frequency (>10 MHz)**: Best precision, higher CPU overhead

### Counter Width
- **16-bit**: May overflow quickly, need careful handling
- **32-bit**: Good for most applications, overflows after ~4 seconds at 1 GHz
- **64-bit**: Effectively never overflows, preferred for ARMv8

### Interrupt Latency
- Keep ISR short - only call `rt_clock_hrtimer_process()`
- Disable timer interrupt while processing to avoid re-entry
- Consider interrupt priority relative to other system interrupts

## Debugging Tips

1. **Verify frequency**: Print actual frequency during initialization
   ```c
   rt_kprintf("Timer freq: %d Hz\n", (rt_uint32_t)rt_clock_time_getfreq());
   ```

2. **Test counter increment**: Verify counter is actually counting
   ```c
   rt_uint64_t cnt1 = rt_clock_time_getcnt();
   rt_thread_mdelay(1);
   rt_uint64_t cnt2 = rt_clock_time_getcnt();
   rt_kprintf("Counter delta: %d (expected ~%d)\n", 
              (rt_uint32_t)(cnt2 - cnt1), 
              (rt_uint32_t)(rt_clock_time_getfreq() / 1000));
   ```

3. **Check interrupt firing**: Add debug output in ISR
   ```c
   static int isr_count = 0;
   void timer_isr(void) {
       isr_count++;
       if (isr_count % 1000 == 0) {
           rt_kprintf("Timer ISR count: %d\n", isr_count);
       }
   }
   ```

## Examples in BSPs

Look for these files in various BSPs for real-world examples:
- `bsp/qemu-virt64-aarch64/drivers/drv_timer.c` - ARM Generic Timer
- `bsp/stm32/libraries/HAL_Drivers/drv_hwtimer.c` - STM32 hardware timers
- `bsp/rockchip/*/driver/hwtimer/` - Rockchip timer drivers

## Contributing

When contributing a new adapter:
1. Add comprehensive comments explaining hardware specifics
2. Include initialization and ISR examples
3. Document any platform-specific requirements
4. Test on actual hardware if possible
5. Update this README with your adapter details
