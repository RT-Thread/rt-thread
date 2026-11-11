# Clock Boottime 辅助

boottime 辅助函数将 clock_time 的单调计数转换为常见时间格式，返回值表示
“系统启动以来的时间”，不受 RTC 或墙上时间设置影响。

# API

```c
rt_err_t rt_clock_boottime_get_us(struct timeval *tv);
rt_err_t rt_clock_boottime_get_s(time_t *t);
rt_err_t rt_clock_boottime_get_ns(struct timespec *ts);
```

成功返回 RT_EOK；若时钟源不可用则返回 -RT_ERROR。返回值单调递增，适合用于
测量耗时。

## rt_clock_boottime_get_us

```c
rt_err_t rt_clock_boottime_get_us(struct timeval *tv);
```

- 作用：获取启动以来的时间，格式为秒 + 微秒。
- 参数：`tv` 需为有效的 `struct timeval` 指针。
- 返回值：
  - RT_EOK：成功写入 `tv`。
  - -RT_ERROR：无有效时钟源或换算失败。
- 说明：
  - `tv_usec` 由 clock_time 分辨率换算而来，不一定严格为 1 us 精度。

## rt_clock_boottime_get_s

```c
rt_err_t rt_clock_boottime_get_s(time_t *t);
```

- 作用：获取启动以来的整秒数。
- 参数：`t` 需为有效的 `time_t` 指针。
- 返回值：
  - RT_EOK：成功写入 `*t`。
  - -RT_ERROR：无有效时钟源或换算失败。
- 说明：
  - 该接口仅返回秒，若需亚秒精度请使用其它接口。

## rt_clock_boottime_get_ns

```c
rt_err_t rt_clock_boottime_get_ns(struct timespec *ts);
```

- 作用：获取启动以来的时间，格式为秒 + 纳秒。
- 参数：`ts` 需为有效的 `struct timespec` 指针。
- 返回值：
  - RT_EOK：成功写入 `ts`。
  - -RT_ERROR：无有效时钟源或换算失败。
- 说明：
  - `tv_nsec` 的精度取决于计数频率，不一定达到 1 ns。

# 示例

```c
#include <drivers/clock_time.h>

static void demo_boottime(void)
{
    struct timespec ts;

    if (rt_clock_boottime_get_ns(&ts) == RT_EOK)
    {
        rt_kprintf("boottime: %ld.%09ld\n", (long)ts.tv_sec, ts.tv_nsec);
    }
}
```

# 注意事项

- 软 RTC 会使用 boottime 作为稳定基准。
- 未注册时钟源时，系统退化为 tick 计数，分辨率由 RT_TICK_PER_SECOND 决定。
