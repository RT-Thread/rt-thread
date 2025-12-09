# 时钟时间设备

## 简介

`clock_time` 子系统为 RT-Thread 提供了统一的时间管理框架，将原有的 `hwtimer`、`ktime` 和 `cputime` 子系统的功能整合到一个一致的 API 中。

### 主要特性

- **时钟源（Clocksource）**：用于计时和时间戳的自由运行计数器
- **时钟事件（Clockevent）**：可编程超时事件，用于高精度定时
- **高分辨率定时器（hrtimer）**：采用链表调度的高效定时器管理
- **POSIX 时钟支持**：与标准 POSIX 时钟 API 兼容
- **启动时间追踪**：记录系统启动以来的单调时间
- **向后兼容**：为旧 API 提供兼容层

### 设计理念

clock_time 子系统遵循 RT-Thread 的 C-OOP（C 语言中的面向对象编程）设计模式：

1. **统一设备抽象**：`rt_clock_time_device` 封装硬件定时器能力
2. **操作结构**：`rt_clock_time_ops` 定义硬件特定操作
3. **能力标志**：明确指示时钟源和时钟事件支持
4. **灵活集成**：同时适用于 MCU 和 MPU 平台

## 架构

```
┌─────────────────────────────────────────────────────────┐
│                     应用层                               │
│  (POSIX API、延时、计时、高分辨率定时器)                │
└──────────────────┬──────────────────────────────────────┘
                   │
┌──────────────────▼──────────────────────────────────────┐
│              clock_time 子系统                           │
│  ┌─────────────┐  ┌──────────┐  ┌──────────────────┐   │
│  │   时钟源    │  │  启动时间 │  │ 高分辨率定时器   │   │
│  └─────────────┘  └──────────┘  └──────────────────┘   │
│  ┌─────────────┐  ┌──────────────────────────────┐     │
│  │  时钟事件   │  │       兼容层                 │     │
│  └─────────────┘  └──────────────────────────────┘     │
└──────────────────┬──────────────────────────────────────┘
                   │
┌──────────────────▼──────────────────────────────────────┐
│            硬件定时器抽象                                │
│        (rt_clock_time_device + ops)                     │
└──────────────────┬──────────────────────────────────────┘
                   │
┌──────────────────▼──────────────────────────────────────┐
│              BSP 定时器驱动                              │
│   (SysTick、ARM 架构定时器、RISC-V 定时器等)            │
└─────────────────────────────────────────────────────────┘
```

## 使用方法

### 注册时钟时间设备

BSP 驱动应实现 `rt_clock_time_ops` 并注册设备：

```c
#include <rtdevice.h>

static rt_uint64_t my_timer_get_freq(void)
{
    return 1000000; /* 1MHz 定时器 */
}

static rt_uint64_t my_timer_get_counter(void)
{
    return MY_TIMER->CNT; /* 读取硬件计数器 */
}

static rt_err_t my_timer_set_timeout(rt_uint64_t delta)
{
    if (delta == 0)
    {
        /* 取消超时 */
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
    /* 初始化硬件定时器 */
    my_clock_device.ops = &my_timer_ops;
    
    /* 注册设备，同时支持时钟源和时钟事件能力 */
    rt_clock_time_device_register(&my_clock_device, 
                                  "hw_timer",
                                  RT_CLOCK_TIME_CAP_CLOCKSOURCE | 
                                  RT_CLOCK_TIME_CAP_CLOCKEVENT);
    
    return 0;
}
INIT_DEVICE_EXPORT(my_timer_init);

/* 定时器中断服务程序应调用 rt_clock_hrtimer_process() */
void MY_TIMER_IRQHandler(void)
{
    /* 清除中断标志 */
    MY_TIMER->SR = 0;
    
    /* 处理 hrtimer 超时 */
    rt_clock_hrtimer_process();
}
```

### 使用时钟源 API

#### 获取时间信息

```c
/* 获取时钟分辨率（以纳秒为单位，按 RT_CLOCK_TIME_RESMUL 缩放）*/
rt_uint64_t res = rt_clock_time_getres();

/* 获取时钟频率（Hz）*/
rt_uint64_t freq = rt_clock_time_getfreq();

/* 获取当前计数器值 */
rt_uint64_t cnt = rt_clock_time_getcnt();
```

#### 获取启动时间

```c
struct timespec ts;
rt_clock_time_boottime_ns(&ts);
rt_kprintf("启动时间: %d.%09d 秒\n", ts.tv_sec, ts.tv_nsec);

struct timeval tv;
rt_clock_time_boottime_us(&tv);

time_t t;
rt_clock_time_boottime_s(&t);
```

#### 时间转换

```c
rt_uint64_t cnt = 1000000; /* 计数器滴答 */

/* 转换为时间单位 */
rt_uint64_t ns = rt_clock_time_cnt_to_ns(cnt);
rt_uint64_t us = rt_clock_time_cnt_to_us(cnt);
rt_uint64_t ms = rt_clock_time_cnt_to_ms(cnt);

/* 从时间单位转换 */
cnt = rt_clock_time_ns_to_cnt(1000000); /* 1ms（纳秒）*/
cnt = rt_clock_time_us_to_cnt(1000);    /* 1ms（微秒）*/
cnt = rt_clock_time_ms_to_cnt(1);       /* 1ms */
```

### 使用高分辨率定时器

#### 创建并启动定时器

```c
#include <rtdevice.h>

static void timeout_callback(void *param)
{
    rt_kprintf("定时器超时!\n");
}

void hrtimer_example(void)
{
    struct rt_clock_hrtimer timer;
    
    /* 初始化定时器 */
    rt_clock_hrtimer_init(&timer, "my_timer", 
                         RT_TIMER_FLAG_ONE_SHOT,
                         timeout_callback, 
                         RT_NULL);
    
    /* 以 1ms 延迟启动定时器 */
    rt_uint64_t delay_cnt = rt_clock_time_ms_to_cnt(1);
    rt_clock_hrtimer_start(&timer, delay_cnt);
    
    /* ... */
    
    /* 如果需要可以停止定时器 */
    rt_clock_hrtimer_stop(&timer);
    
    /* 清理 */
    rt_clock_hrtimer_detach(&timer);
}
```

#### 周期定时器

```c
static void periodic_callback(void *param)
{
    rt_kprintf("周期滴答\n");
}

void periodic_timer_example(void)
{
    struct rt_clock_hrtimer timer;
    
    rt_clock_hrtimer_init(&timer, "periodic", 
                         RT_TIMER_FLAG_PERIODIC,
                         periodic_callback, 
                         RT_NULL);
    
    /* 以 100ms 周期启动 */
    rt_uint64_t period_cnt = rt_clock_time_ms_to_cnt(100);
    rt_clock_hrtimer_start(&timer, period_cnt);
}
```

### 高精度延时

```c
/* 纳秒延时 */
rt_clock_ndelay(1000);  /* 1 微秒 */

/* 微秒延时 */
rt_clock_udelay(1000);  /* 1 毫秒 */

/* 毫秒延时 */
rt_clock_mdelay(100);   /* 100 毫秒 */

/* 使用自定义定时器进行延时 */
struct rt_clock_hrtimer timer;
rt_clock_hrtimer_mdelay(&timer, 50);  /* 50ms 延时 */
```

## 迁移指南

### 从 ktime 迁移

当启用 `RT_CLOCK_TIME_COMPAT_KTIME` 时，clock_time 子系统提供直接的 API 兼容性：

| 旧 ktime API | 新 clock_time API |
|--------------|-------------------|
| `rt_ktime_boottime_get_ns()` | `rt_clock_time_boottime_ns()` |
| `rt_ktime_cputimer_getres()` | `rt_clock_time_getres()` |
| `rt_ktime_cputimer_getcnt()` | `rt_clock_time_getcnt()` |
| `rt_ktime_hrtimer_init()` | `rt_clock_hrtimer_init()` |
| `rt_ktime_hrtimer_start()` | `rt_clock_hrtimer_start()` |

### 从 cputime 迁移

当启用 `RT_CLOCK_TIME_COMPAT_CPUTIME` 时：

| 旧 cputime API | 新 clock_time API |
|----------------|-------------------|
| `clock_cpu_gettime()` | `rt_clock_time_getcnt()` |
| `clock_cpu_getres()` | `rt_clock_time_getres()` |
| `rt_cputime_sleep()` | `rt_clock_mdelay()` 或使用 hrtimer |
| `rt_cputime_udelay()` | `rt_clock_udelay()` |

### 从 hwtimer 迁移

硬件定时器设备应迁移到新的 clock_time 设备模型：

**旧 hwtimer 方式：**
```c
static const struct rt_hwtimer_ops my_ops = { ... };
static struct rt_hwtimer_device my_device;
my_device.ops = &my_ops;
rt_device_hwtimer_register(&my_device, "timer0", RT_NULL);
```

**新 clock_time 方式：**
```c
static const struct rt_clock_time_ops my_ops = { ... };
static struct rt_clock_time_device my_device;
my_device.ops = &my_ops;
rt_clock_time_device_register(&my_device, "timer0",
    RT_CLOCK_TIME_CAP_CLOCKSOURCE | RT_CLOCK_TIME_CAP_CLOCKEVENT);
```

## 配置

### Kconfig 选项

```
RT_USING_CLOCK_TIME              - 启用 clock_time 子系统
RT_CLOCK_TIME_COMPAT_KTIME       - 启用 ktime 兼容层
RT_CLOCK_TIME_COMPAT_CPUTIME     - 启用 cputime 兼容层
RT_CLOCK_TIME_COMPAT_HWTIMER     - 启用 hwtimer 兼容层
```

### 典型配置

对于新项目：
```
CONFIG_RT_USING_CLOCK_TIME=y
# 不需要兼容层
```

对于迁移项目：
```
CONFIG_RT_USING_CLOCK_TIME=y
CONFIG_RT_CLOCK_TIME_COMPAT_KTIME=y
CONFIG_RT_CLOCK_TIME_COMPAT_CPUTIME=y
CONFIG_RT_CLOCK_TIME_COMPAT_HWTIMER=y
```

## 最佳实践

### MCU 场景

1. **使用 SysTick 或类似定时器**：对于基本计时，SysTick 提供足够的分辨率
2. **硬件定时器提供精度**：使用专用硬件定时器实现微秒级精度
3. **考虑功耗**：在低功耗应用中最小化定时器唤醒

### MPU 场景

1. **架构定时器**：使用 ARM 通用定时器或 RISC-V 定时器以获得最佳性能
2. **SMP 安全**：hrtimer 实现使用自旋锁支持 SMP 系统
3. **高频率源**：MPU 可以处理更高频率的定时器（MHz 范围）

### 通用准则

1. **单一默认设备**：注册一个主要的 clock_time 设备作为系统默认
2. **中断服务程序效率**：在 ISR 中保持 `rt_clock_hrtimer_process()` 调用简短
3. **分辨率与开销**：更高分辨率的定时器有更高的开销
4. **回退支持**：基于滴答的回退确保即使没有硬件定时器也能正常工作

## API 参考

完整的 API 文档请参阅 `/components/drivers/include/drivers/clock_time.h`。

## 示例

完整示例可在以下位置找到：
- `/examples/clock_time/` - 基本使用示例
- BSP 定时器驱动实现供参考

## 故障排除

### 定时器不触发

- 验证硬件定时器配置正确
- 检查 ISR 是否调用 `rt_clock_hrtimer_process()`
- 确保定时器中断已启用

### 精度差

- 验证定时器频率适合您的用例
- 检查中断延迟问题
- 考虑使用更高频率的定时器

### 兼容性问题

- 在 Kconfig 中启用适当的兼容层
- 检查迁移中的 API 签名更改
- 验证 BSP 特定的定时器实现

## 另请参阅

- [定时器管理](timer.md)
- [实时时钟（RTC）](rtc.md)
- [设备驱动框架](framework.md)
