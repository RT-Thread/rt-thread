# RT-Thread Clock Time Subsystem / RT-Thread 时钟时间子系统

English | [中文](#中文文档)

## Overview

The `clock_time` subsystem provides a unified interface for time-related hardware and software functionality in RT-Thread. It consolidates and replaces the previous separate subsystems:
- **hwtimer**: Hardware timer device drivers
- **ktime**: Kernel time and high-resolution timers
- **cputime**: CPU time measurement

## Architecture

The clock_time subsystem follows a C-OOP (C Object-Oriented Programming) design pattern with clear separation of concerns:

```
┌─────────────────────────────────────────────────────────┐
│              Application Layer                          │
│  (POSIX clock_gettime, nanosleep, etc.)                │
└────────────────┬────────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────────┐
│         Clock Time High-Level APIs                      │
│  • Boottime (monotonic time since boot)                │
│  • High-Resolution Timers (hrtimer)                    │
│  • CPU Timer (counter access)                          │
└────────────────┬────────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────────┐
│       Clock Time Device Abstraction                     │
│  struct rt_clock_time_device                           │
│  struct rt_clock_time_ops                              │
└────────────────┬────────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────────┐
│        Hardware / BSP Implementation                    │
│  • ARM Arch Timer, RISC-V RDTIME                       │
│  • SysTick, System Timer                               │
│  • Hardware Timer Peripherals                          │
└─────────────────────────────────────────────────────────┘
```

### Key Components

1. **Device Abstraction** (`clock_time.c`)
   - Unified device interface for timer hardware
   - Device registration and management
   - Capability flags (clocksource, clockevent)

2. **High-Resolution Timers** (`hrtimer.c`)
   - Software timer scheduling on hardware timers
   - Linked-list or red-black tree management
   - SMP-safe with spinlock protection

3. **Boottime APIs** (`clock_time_boottime.c`)
   - Monotonic time since system boot
   - Nanosecond, microsecond, second precision

4. **CPU Timer** (`clock_time_tick.c`, `clock_time_cputime.c`)
   - Low-level counter access
   - Frequency and resolution queries
   - Tick-based fallback for simple systems

## Configuration

Enable clock_time in menuconfig:

```
Device Drivers  --->
    [*] Using unified clock_time subsystem  --->
        [*] Enable high-resolution timer support
        [*] Enable CPU time APIs
        [*] Enable boottime APIs
```

### Backward Compatibility

When `RT_USING_CLOCK_TIME` is enabled, the old subsystems are automatically disabled and their APIs are redirected:

- `RT_USING_HWTIMER` → Automatically set (compatibility mode)
- `RT_USING_KTIME` → Automatically set (compatibility mode)
- `RT_USING_CPUTIME` → Automatically set (compatibility mode)

All `rt_ktime_*` APIs are mapped to `rt_clock_*` APIs via macros, ensuring existing code continues to work.

## API Reference

### Device Management

```c
/* Register a clock time device */
rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev,
                                        const char *name,
                                        rt_uint8_t caps);

/* Get/set default system clock device */
rt_clock_time_t rt_clock_time_default(void);
rt_err_t rt_clock_time_set_default(rt_clock_time_t dev);
```

### Boottime APIs

```c
/* Get system boottime (monotonic time since boot) */
rt_err_t rt_clock_boottime_get_ns(struct timespec *ts);  // Nanosecond precision
rt_err_t rt_clock_boottime_get_us(struct timeval *tv);   // Microsecond precision
rt_err_t rt_clock_boottime_get_s(time_t *t);             // Second precision
```

### CPU Timer APIs

```c
/* Low-level counter access */
rt_uint64_t rt_clock_cputimer_getres(void);       // Get resolution
unsigned long rt_clock_cputimer_getfrq(void);     // Get frequency in Hz
unsigned long rt_clock_cputimer_getcnt(void);     // Get current counter value
void rt_clock_cputimer_init(void);                // Initialize (called by system)
```

### High-Resolution Timer APIs

```c
/* Initialize and manage high-resolution timers */
void rt_clock_hrtimer_init(rt_clock_hrtimer_t timer, const char *name,
                            rt_uint8_t flag, void (*timeout)(void *), void *param);
rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long cnt);
rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer);
rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer);

/* Delay functions (blocking) */
rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, unsigned long ns);
rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, unsigned long us);
rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, unsigned long ms);
```

## BSP Porting Guide

### Minimal Implementation (Tick-based)

The tick-based fallback works out-of-the-box for simple systems:

```c
// No additional code needed - uses RT_TICK_PER_SECOND
// Automatically provides:
//   - rt_clock_cputimer_getcnt() → rt_tick_get()
//   - rt_clock_cputimer_getfrq() → RT_TICK_PER_SECOND
//   - Resolution based on tick rate
```

### Hardware Timer Implementation

For better precision, implement hardware timer support:

```c
#include <drivers/clock_time.h>

/* Define hardware operations */
static rt_uint64_t my_timer_get_freq(void) {
    return 1000000; // 1 MHz
}

static rt_uint64_t my_timer_get_counter(void) {
    return READ_TIMER_COUNTER_REG();
}

static rt_err_t my_timer_set_timeout(rt_uint64_t delta) {
    if (delta == 0) {
        DISABLE_TIMER_INTERRUPT();
        return RT_EOK;
    }
    SET_TIMER_COMPARE_VALUE(delta);
    ENABLE_TIMER_INTERRUPT();
    return RT_EOK;
}

static const struct rt_clock_time_ops my_timer_ops = {
    .get_freq = my_timer_get_freq,
    .get_counter = my_timer_get_counter,
    .set_timeout = my_timer_set_timeout,
};

/* Define device structure */
static struct rt_clock_time_device my_timer_dev;

/* Initialize and register */
int my_timer_init(void) {
    HARDWARE_TIMER_INIT();
    
    my_timer_dev.ops = &my_timer_ops;
    
    return rt_clock_time_device_register(&my_timer_dev, "timer0",
                RT_CLOCK_TIME_CAP_CLOCKSOURCE | RT_CLOCK_TIME_CAP_CLOCKEVENT);
}
INIT_BOARD_EXPORT(my_timer_init);

/* Timer interrupt handler */
void timer_irq_handler(void) {
    CLEAR_TIMER_INTERRUPT();
    rt_clock_hrtimer_process(); // Process expired timers
}
```

### Overriding CPU Timer Functions

For architecture-specific high-performance counters (e.g., ARM DWT, RISC-V RDTIME):

```c
/* Override weak functions in your BSP */
unsigned long rt_clock_cputimer_getcnt(void) {
    return READ_CPU_CYCLE_COUNTER();
}

unsigned long rt_clock_cputimer_getfrq(void) {
    return CPU_FREQUENCY_HZ;
}

rt_uint64_t rt_clock_cputimer_getres(void) {
    // Resolution in ns * RT_CLOCK_TIME_RESMUL
    return ((1000000000ULL * RT_CLOCK_TIME_RESMUL) / CPU_FREQUENCY_HZ);
}
```

## Migration Guide

### From ktime

All `rt_ktime_*` APIs are automatically mapped. No code changes needed:

```c
// Old code (still works)
#include <ktime.h>
rt_ktime_boottime_get_ns(&ts);
rt_ktime_hrtimer_init(&timer, "mytimer", ...);

// Equivalent new code (optional migration)
#include <drivers/clock_time.h>
rt_clock_boottime_get_ns(&ts);
rt_clock_hrtimer_init(&timer, "mytimer", ...);
```

### From hwtimer

Hardware timer drivers should be updated to use the new device abstraction:

```c
// Old: struct rt_hwtimer_device + rt_device_hwtimer_register()
// New: struct rt_clock_time_device + rt_clock_time_device_register()
```

### From cputime

CPU time APIs have been unified:

```c
// Old: clock_cpu_gettime() / clock_cpu_getres()
// New: rt_clock_cputimer_getcnt() / rt_clock_cputimer_getres()
// Note: Old APIs still work if using old cputime module
```

## Examples

### Example 1: One-shot Timer

```c
#include <drivers/clock_time.h>

static void timer_callback(void *param) {
    rt_kprintf("Timer expired!\n");
}

void example_oneshot_timer(void) {
    struct rt_clock_hrtimer timer;
    
    rt_clock_hrtimer_init(&timer, "oneshot", RT_TIMER_FLAG_ONE_SHOT,
                          timer_callback, NULL);
    
    // Start timer for 1 second (using CPU timer frequency)
    unsigned long freq = rt_clock_cputimer_getfrq();
    rt_clock_hrtimer_start(&timer, freq * 1);
    
    // Timer will fire callback after 1 second
}
```

### Example 2: Microsecond Delay

```c
#include <drivers/clock_time.h>

void example_delay(void) {
    struct rt_clock_hrtimer timer;
    
    rt_clock_hrtimer_delay_init(&timer);
    
    // Delay for 500 microseconds
    rt_clock_hrtimer_udelay(&timer, 500);
    
    rt_clock_hrtimer_delay_detach(&timer);
}
```

### Example 3: Boottime Measurement

```c
#include <drivers/clock_time.h>

void example_boottime(void) {
    struct timespec ts;
    
    rt_clock_boottime_get_ns(&ts);
    rt_kprintf("System has been running for %ld.%09ld seconds\n",
               ts.tv_sec, ts.tv_nsec);
}
```

---

## 中文文档

## 概述

`clock_time` 子系统为 RT-Thread 中的时间相关硬件和软件功能提供统一接口。它整合并替代了以前的独立子系统：
- **hwtimer**：硬件定时器设备驱动
- **ktime**：内核时间和高分辨率定时器
- **cputime**：CPU 时间测量

## 架构

clock_time 子系统遵循 C-OOP（C 语言面向对象编程）设计模式，职责清晰分离：

```
┌─────────────────────────────────────────────────────────┐
│              应用层                                      │
│  (POSIX clock_gettime, nanosleep 等)                   │
└────────────────┬────────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────────┐
│         时钟时间高层 API                                 │
│  • Boottime (自启动以来的单调时间)                      │
│  • 高分辨率定时器 (hrtimer)                             │
│  • CPU 定时器 (计数器访问)                              │
└────────────────┬────────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────────┐
│       时钟时间设备抽象                                   │
│  struct rt_clock_time_device                           │
│  struct rt_clock_time_ops                              │
└────────────────┬────────────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────────────┐
│        硬件 / BSP 实现                                   │
│  • ARM Arch Timer, RISC-V RDTIME                       │
│  • SysTick, 系统定时器                                  │
│  • 硬件定时器外设                                        │
└─────────────────────────────────────────────────────────┘
```

### 关键组件

1. **设备抽象** (`clock_time.c`)
   - 定时器硬件的统一设备接口
   - 设备注册和管理
   - 能力标志（时钟源、时钟事件）

2. **高分辨率定时器** (`hrtimer.c`)
   - 在硬件定时器上的软件定时器调度
   - 链表或红黑树管理
   - SMP 安全，带自旋锁保护

3. **Boottime API** (`clock_time_boottime.c`)
   - 自系统启动以来的单调时间
   - 纳秒、微秒、秒精度

4. **CPU 定时器** (`clock_time_tick.c`, `clock_time_cputime.c`)
   - 底层计数器访问
   - 频率和分辨率查询
   - 简单系统的基于 tick 的回退

## 配置

在 menuconfig 中启用 clock_time：

```
Device Drivers  --->
    [*] Using unified clock_time subsystem  --->
        [*] Enable high-resolution timer support
        [*] Enable CPU time APIs
        [*] Enable boottime APIs
```

### 向后兼容

当启用 `RT_USING_CLOCK_TIME` 时，旧子系统自动禁用，其 API 被重定向：

- `RT_USING_HWTIMER` → 自动设置（兼容模式）
- `RT_USING_KTIME` → 自动设置（兼容模式）
- `RT_USING_CPUTIME` → 自动设置（兼容模式）

所有 `rt_ktime_*` API 通过宏映射到 `rt_clock_*` API，确保现有代码继续工作。

## API 参考

### 设备管理

```c
/* 注册时钟时间设备 */
rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev,
                                        const char *name,
                                        rt_uint8_t caps);

/* 获取/设置默认系统时钟设备 */
rt_clock_time_t rt_clock_time_default(void);
rt_err_t rt_clock_time_set_default(rt_clock_time_t dev);
```

### Boottime API

```c
/* 获取系统启动时间（自启动以来的单调时间） */
rt_err_t rt_clock_boottime_get_ns(struct timespec *ts);  // 纳秒精度
rt_err_t rt_clock_boottime_get_us(struct timeval *tv);   // 微秒精度
rt_err_t rt_clock_boottime_get_s(time_t *t);             // 秒精度
```

### CPU 定时器 API

```c
/* 底层计数器访问 */
rt_uint64_t rt_clock_cputimer_getres(void);       // 获取分辨率
unsigned long rt_clock_cputimer_getfrq(void);     // 获取频率（Hz）
unsigned long rt_clock_cputimer_getcnt(void);     // 获取当前计数器值
void rt_clock_cputimer_init(void);                // 初始化（由系统调用）
```

### 高分辨率定时器 API

```c
/* 初始化和管理高分辨率定时器 */
void rt_clock_hrtimer_init(rt_clock_hrtimer_t timer, const char *name,
                            rt_uint8_t flag, void (*timeout)(void *), void *param);
rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long cnt);
rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer);
rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer);

/* 延时函数（阻塞） */
rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, unsigned long ns);
rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, unsigned long us);
rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, unsigned long ms);
```

## BSP 移植指南

### 最小实现（基于 Tick）

基于 tick 的回退对简单系统开箱即用：

```c
// 无需额外代码 - 使用 RT_TICK_PER_SECOND
// 自动提供：
//   - rt_clock_cputimer_getcnt() → rt_tick_get()
//   - rt_clock_cputimer_getfrq() → RT_TICK_PER_SECOND
//   - 基于 tick 速率的分辨率
```

### 硬件定时器实现

为了更好的精度，实现硬件定时器支持：

```c
#include <drivers/clock_time.h>

/* 定义硬件操作 */
static rt_uint64_t my_timer_get_freq(void) {
    return 1000000; // 1 MHz
}

static rt_uint64_t my_timer_get_counter(void) {
    return READ_TIMER_COUNTER_REG();
}

static rt_err_t my_timer_set_timeout(rt_uint64_t delta) {
    if (delta == 0) {
        DISABLE_TIMER_INTERRUPT();
        return RT_EOK;
    }
    SET_TIMER_COMPARE_VALUE(delta);
    ENABLE_TIMER_INTERRUPT();
    return RT_EOK;
}

static const struct rt_clock_time_ops my_timer_ops = {
    .get_freq = my_timer_get_freq,
    .get_counter = my_timer_get_counter,
    .set_timeout = my_timer_set_timeout,
};

/* 定义设备结构 */
static struct rt_clock_time_device my_timer_dev;

/* 初始化和注册 */
int my_timer_init(void) {
    HARDWARE_TIMER_INIT();
    
    my_timer_dev.ops = &my_timer_ops;
    
    return rt_clock_time_device_register(&my_timer_dev, "timer0",
                RT_CLOCK_TIME_CAP_CLOCKSOURCE | RT_CLOCK_TIME_CAP_CLOCKEVENT);
}
INIT_BOARD_EXPORT(my_timer_init);

/* 定时器中断处理程序 */
void timer_irq_handler(void) {
    CLEAR_TIMER_INTERRUPT();
    rt_clock_hrtimer_process(); // 处理过期定时器
}
```

### 覆盖 CPU 定时器函数

对于架构特定的高性能计数器（例如 ARM DWT、RISC-V RDTIME）：

```c
/* 在 BSP 中覆盖弱函数 */
unsigned long rt_clock_cputimer_getcnt(void) {
    return READ_CPU_CYCLE_COUNTER();
}

unsigned long rt_clock_cputimer_getfrq(void) {
    return CPU_FREQUENCY_HZ;
}

rt_uint64_t rt_clock_cputimer_getres(void) {
    // 分辨率（纳秒 * RT_CLOCK_TIME_RESMUL）
    return ((1000000000ULL * RT_CLOCK_TIME_RESMUL) / CPU_FREQUENCY_HZ);
}
```

## 迁移指南

### 从 ktime 迁移

所有 `rt_ktime_*` API 自动映射。无需更改代码：

```c
// 旧代码（仍然有效）
#include <ktime.h>
rt_ktime_boottime_get_ns(&ts);
rt_ktime_hrtimer_init(&timer, "mytimer", ...);

// 等效的新代码（可选迁移）
#include <drivers/clock_time.h>
rt_clock_boottime_get_ns(&ts);
rt_clock_hrtimer_init(&timer, "mytimer", ...);
```

### 从 hwtimer 迁移

硬件定时器驱动应更新为使用新的设备抽象：

```c
// 旧：struct rt_hwtimer_device + rt_device_hwtimer_register()
// 新：struct rt_clock_time_device + rt_clock_time_device_register()
```

### 从 cputime 迁移

CPU 时间 API 已统一：

```c
// 旧：clock_cpu_gettime() / clock_cpu_getres()
// 新：rt_clock_cputimer_getcnt() / rt_clock_cputimer_getres()
// 注意：如果使用旧 cputime 模块，旧 API 仍然有效
```

## 示例

### 示例 1：一次性定时器

```c
#include <drivers/clock_time.h>

static void timer_callback(void *param) {
    rt_kprintf("定时器过期！\n");
}

void example_oneshot_timer(void) {
    struct rt_clock_hrtimer timer;
    
    rt_clock_hrtimer_init(&timer, "oneshot", RT_TIMER_FLAG_ONE_SHOT,
                          timer_callback, NULL);
    
    // 启动定时器 1 秒（使用 CPU 定时器频率）
    unsigned long freq = rt_clock_cputimer_getfrq();
    rt_clock_hrtimer_start(&timer, freq * 1);
    
    // 定时器将在 1 秒后触发回调
}
```

### 示例 2：微秒延时

```c
#include <drivers/clock_time.h>

void example_delay(void) {
    struct rt_clock_hrtimer timer;
    
    rt_clock_hrtimer_delay_init(&timer);
    
    // 延时 500 微秒
    rt_clock_hrtimer_udelay(&timer, 500);
    
    rt_clock_hrtimer_delay_detach(&timer);
}
```

### 示例 3：启动时间测量

```c
#include <drivers/clock_time.h>

void example_boottime(void) {
    struct timespec ts;
    
    rt_clock_boottime_get_ns(&ts);
    rt_kprintf("系统已运行 %ld.%09ld 秒\n",
               ts.tv_sec, ts.tv_nsec);
}
```

## License

Apache-2.0

## References

- RT-Thread Programming Guide: https://www.rt-thread.io/document/site/
- RT-Thread Coding Style: https://github.com/RT-Thread/rt-thread/blob/master/documentation/coding_style_cn.md
