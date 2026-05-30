# Clock HRTimer

clock hrtimer 在 clock_time 之上提供高精度超时调度。它维护按到期时间排序的
队列，编程下一次事件，并在到期时执行回调。

# 关键点

- 时间基准：延时 cnt 基于默认时钟源的计数单位。
- 事件编程：将下一次到期换算为事件单位后调用事件设备。
- 退化机制：缺少硬件事件时自动使用软件定时器触发处理。

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

flag 复用 RT_TIMER_FLAG_* 定义（单次/周期/硬定时器）。cnt 为默认时钟源计数
单位。

## rt_clock_hrtimer_init

```c
void rt_clock_hrtimer_init(rt_clock_hrtimer_t timer,
                           const char *name,
                           rt_uint8_t flag,
                           void (*timeout)(void *parameter),
                           void *parameter);
```

- 作用：初始化一个高精度定时器对象。
- 参数：
  - `timer`：待初始化的 hrtimer 对象。
  - `name`：定时器名称（超过 RT_NAME_MAX-1 会截断）。
  - `flag`：RT_TIMER_FLAG_* 标志（单次/周期/硬定时器）。
  - `timeout`：超时回调函数。
  - `parameter`：回调参数。
- 行为：
  - 清理内部状态，初始化链表节点与 completion。
  - 仅初始化，不会启动，需要调用 `rt_clock_hrtimer_start()`。
- 上下文：线程上下文。

## rt_clock_hrtimer_start

```c
rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long cnt);
```

- 作用：启动定时器，在 `cnt` 个计数后到期。
- 参数：
  - `cnt`：相对延时，单位为默认时钟源计数。
- 返回值：
  - RT_EOK：启动成功。
  - -RT_ERROR：定时器已激活或 `cnt` 非法。
- 说明：
  - `cnt` 需小于计数器最大值的一半，以避免回绕歧义。
  - 启动后可能重新编程下一次事件。

## rt_clock_hrtimer_stop

```c
rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer);
```

- 作用：停止一个正在运行的定时器。
- 返回值：
  - RT_EOK：停止成功。
  - -RT_ERROR：定时器未激活。
- 说明：停止定时器可能触发重新编程下一次事件。

## rt_clock_hrtimer_control

```c
rt_err_t rt_clock_hrtimer_control(rt_clock_hrtimer_t timer, int cmd, void *arg);
```

- 作用：查询或修改定时器属性。
- 常用命令（与 RT-Thread 定时器一致）：
  - RT_TIMER_CTRL_GET_TIME：读取 `delay_cnt` 到 `*(unsigned long *)arg`。
  - RT_TIMER_CTRL_SET_TIME：用 `*(unsigned long *)arg` 设置 `delay_cnt`。
  - RT_TIMER_CTRL_SET_ONESHOT / RT_TIMER_CTRL_SET_PERIODIC：设置模式。
  - RT_TIMER_CTRL_GET_STATE：查询激活状态。
  - RT_TIMER_CTRL_GET_REMAIN_TIME：获取绝对到期计数值。
  - RT_TIMER_CTRL_GET_FUNC / RT_TIMER_CTRL_SET_FUNC：获取/设置回调。
  - RT_TIMER_CTRL_GET_PARM / RT_TIMER_CTRL_SET_PARM：获取/设置参数。
- 说明：
  - 修改时间或模式不会自动启动已停止的定时器。

## rt_clock_hrtimer_detach

```c
rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer);
```

- 作用：分离定时器，并唤醒等待者。
- 行为：
  - 标记定时器为未激活。
  - 唤醒 `rt_clock_hrtimer_sleep()` 的等待线程并返回错误。
- 适用场景：定时器资源释放或任务退出。

## rt_clock_hrtimer_delay_init

```c
void rt_clock_hrtimer_delay_init(struct rt_clock_hrtimer *timer);
```

- 作用：初始化用于阻塞延时的 one-shot hrtimer。
- 行为：设置内部回调为 completion 触发函数。

## rt_clock_hrtimer_delay_detach

```c
void rt_clock_hrtimer_delay_detach(struct rt_clock_hrtimer *timer);
```

- 作用：释放 delay_init 初始化的定时器。
- 说明：即使已超时也可安全调用。

## rt_clock_hrtimer_sleep

```c
rt_err_t rt_clock_hrtimer_sleep(struct rt_clock_hrtimer *timer, unsigned long cnt);
```

- 作用：阻塞当前线程，直到超时。
- 参数：`timer` 需已初始化（通常通过 delay_init）。
- 返回值：
  - RT_EOK：正常到期。
  - -RT_EINTR：被信号打断或 detach。
  - -RT_EINVAL：`cnt` 为 0。
- 上下文：仅线程上下文可用。

## rt_clock_hrtimer_ndelay / udelay / mdelay

```c
rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, unsigned long ns);
rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, unsigned long us);
rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, unsigned long ms);
```

- 作用：按纳秒/微秒/毫秒为单位进行阻塞延时。
- 行为：根据 clock_time 分辨率换算为计数后调用 `rt_clock_hrtimer_sleep()`。
- 说明：
  - 实际延时受计数频率与事件编程粒度限制。

# 典型流程

1. 初始化 hrtimer 并设置回调。
2. 将时间转换为计数值，或使用 ndelay/udelay/mdelay 辅助函数。
3. 启动定时器，系统会自动编程下一次事件。
4. 事件中断调用 rt_clock_time_event_isr()，触发 hrtimer 处理与回调分发。

# 示例：单次超时

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

# 示例：延时辅助

```c
static void demo_hrtimer_sleep(void)
{
    struct rt_clock_hrtimer timer;

    rt_clock_hrtimer_delay_init(&timer);
    rt_clock_hrtimer_mdelay(&timer, 10);
    rt_clock_hrtimer_delay_detach(&timer);
}
```

# 注意事项

- 使用硬件事件时，回调可能在中断上下文执行。
- rt_clock_hrtimer_sleep() 会等待 completion，可能返回 -RT_EINTR。
