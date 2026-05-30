# CLOCK_TIMER 设备

> 说明：CLOCK_TIMER 是 `clock_time` 子系统中的统一硬件定时器设备。

# 定时器简介

硬件定时器通常有两种工作模式：定时模式与计数模式。无论哪种模式，本质都
是对输入脉冲计数。以下为常用概念：

**定时模式**：计数内部脉冲信号，常用于定时检测、响应与控制。

**计数模式**：计数器可加/减计数。16 位计数器最大计数值为 65535，32 位
计数器最大值为 4,294,967,295。

**计数频率**：在输入频率固定时，可由 `time = count / freq` 计算时间。
例如频率 1 MHz，计数器每 1 微秒加 1；16 位计数器最大定时能力约为
65.535 ms。

# 与 clock_time 的关系

CLOCK_TIMER 设备可直接通过 RT-Thread 设备框架被应用使用，也可以作为
clock_time 的事件设备。当通过 `rt_clock_timer_register()` 注册并成为默认
事件设备时，其中断会触发 `rt_clock_time_event_isr()`，驱动高精度定时器
调度。

# 访问硬件定时器设备

应用通过 RT-Thread I/O 设备管理接口访问硬件定时器，常用接口如下：

| **函数** | **描述** |
| -------------------- | ---------------------------------- |
| rt_device_find()  | 查找定时器设备 |
| rt_device_open()     | 以读写方式打开定时器设备 |
| rt_device_set_rx_indicate()   | 设置超时回调函数 |
| rt_device_control()  | 控制定时器（模式、频率、停止等） |
| rt_device_write()  | 设置超时时间并启动 |
| rt_device_read()  | 读取当前计数值 |
| rt_device_close()  | 关闭设备 |

## 查找定时器设备

```c
rt_device_t rt_device_find(const char* name);
```

| 参数 | 描述 |
| -------- | ---------------------------------- |
| name     | 定时器设备名称 |
| **返回** | —— |
| 设备句柄 | 查找成功返回句柄 |
| RT_NULL  | 未找到设备 |

通常设备名为 timer0、timer1 等。

```c
#define CLOCK_TIMER_DEV_NAME   "timer0"     /* timer name */
rt_device_t hw_dev;                     /* timer device handle */

hw_dev = rt_device_find(CLOCK_TIMER_DEV_NAME);
```

补充说明：
- 设备名由 BSP 在 `rt_clock_timer_register()` 中指定。
- 系统内注册的每个定时器都会对应一个设备节点。

## 打开定时器设备

```c
rt_err_t rt_device_open(rt_device_t dev, rt_uint16_t oflags);
```

| 参数 | 描述 |
| ---------- | ------------------------------- |
| dev        | 定时器设备句柄 |
| oflags     | 打开模式，通常为 RT_DEVICE_OFLAG_RDWR |
| **返回** | —— |
| RT_EOK     | 打开成功 |
| 其他错误码 | 打开失败 |

```c
hw_dev = rt_device_find(CLOCK_TIMER_DEV_NAME);
rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
```

补充说明：
- 打开设备会确保驱动初始化并应用当前工作频率。
- 调用 control/read/write 之前应先 open，否则可能返回 -RT_ENOSYS 或失败。

## 设置超时回调函数

```c
rt_err_t rt_device_set_rx_indicate(rt_device_t dev,
                                   rt_err_t (*rx_ind)(rt_device_t dev, rt_size_t size))
```

| 参数 | 描述 |
| ---------- | ------------------------------- |
| dev        | 设备句柄 |
| rx_ind     | 超时回调函数 |
| **返回** | —— |
| RT_EOK     | 成功 |

```c
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is clock_timer timeout callback function!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int clock_timer_sample(int argc, char *argv[])
{
    hw_dev = rt_device_find(CLOCK_TIMER_DEV_NAME);
    rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    rt_device_set_rx_indicate(hw_dev, timeout_cb);
}
```

补充说明：
- 回调在中断上下文执行，应尽量短小且避免阻塞。
- `size` 通常为 sizeof(rt_clock_timerval_t)，多数场景可忽略。

## 控制定时器设备

```c
rt_err_t rt_device_control(rt_device_t dev, rt_uint8_t cmd, void* arg);
```

| 参数 | 描述 |
| ---------------- | ------------------------------ |
| dev              | 设备句柄 |
| cmd              | 控制命令 |
| arg              | 参数 |
| **返回**       | —— |
| RT_EOK           | 成功 |
| -RT_ENOSYS       | 失败，设备为空 |
| 其他错误码 | 失败 |

控制命令：

| **控制命令** | 描述 |
| ---------------------- | ------------------------ |
| CLOCK_TIMER_CTRL_FREQ_SET | 设置计数频率 |
| CLOCK_TIMER_CTRL_STOP     | 停止定时器 |
| CLOCK_TIMER_CTRL_INFO_GET | 获取特性信息 |
| CLOCK_TIMER_CTRL_MODE_SET | 设置模式 |

模式可选：

```c
CLOCK_TIMER_MODE_ONESHOT    /* 单次定时 */
CLOCK_TIMER_MODE_PERIOD     /* 周期定时 */
```

示例：

```c
rt_clock_timer_mode_t mode;
rt_uint32_t freq = 10000;               /* counting frequency */

rt_device_control(hw_dev, CLOCK_TIMER_CTRL_FREQ_SET, &freq);
mode = CLOCK_TIMER_MODE_PERIOD;
rt_device_control(hw_dev, CLOCK_TIMER_CTRL_MODE_SET, &mode);
```

补充说明：
- CLOCK_TIMER_CTRL_FREQ_SET：
  - `arg` 指向频率值（Hz）。
  - 驱动会与 `rt_clock_timer_info` 中的 minfreq/maxfreq 做范围校验。
  - 设置成功后影响后续超时换算。
- CLOCK_TIMER_CTRL_STOP：
  - 仅停止当前定时流程，不会关闭设备。
- CLOCK_TIMER_CTRL_INFO_GET：
  - `arg` 指向 `struct rt_clock_timer_info`，返回硬件能力信息。
- CLOCK_TIMER_CTRL_MODE_SET：
  - `arg` 指向 `rt_clock_timer_mode_t`。
  - ONESHOT 单次触发；PERIOD 周期触发。

## 设置超时值

```c
rt_size_t rt_device_write(rt_device_t dev, rt_off_t pos,
                          const void* buffer, rt_size_t size);
```

| 参数 | 描述 |
| ---------- | ------------------------------------------ |
| dev                | 设备句柄 |
| pos                | 偏移，未使用，置 0 |
| buffer             | 超时结构体指针 |
| size               | 结构体大小 |
| **返回**      | —— |
| 实际写入长度 | 成功 |
| 0                  | 失败 |

超时结构体：

```c
typedef struct rt_clock_timerval
{
    rt_int32_t sec;
    rt_int32_t usec;
} rt_clock_timerval_t;
```

```c
rt_clock_timerval_t timeout_s;

timeout_s.sec = 5;
timeout_s.usec = 0;
rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s));
```

补充说明：
- `size` 必须等于 `sizeof(rt_clock_timerval_t)`，否则写入失败。
- 周期模式下，长超时可能被拆分为多个计数周期执行。
- 单次模式且超时可在一个周期内完成时，到期后自动停止。

## 读取当前计数值

```c
rt_size_t rt_device_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
```

```c
rt_clock_timerval_t timeout_s;
rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
```

补充说明：
- 返回值表示自定时启动以来的累计耗时。
- 周期模式会包含已完成周期的时间。
- 单次模式下只反映当前周期内的计数进度。

## 关闭设备

```c
rt_err_t rt_device_close(rt_device_t dev);
```

```c
rt_device_close(hw_dev);
```

补充说明：
- 关闭设备可能会停止定时器并释放硬件资源。
- 再次使用前需要重新打开设备。

> 定时误差示例：若计数器最大 0xFFFF、频率 1 MHz，定时 1.000001 s 时需拆分
> 为多次计数，误差约 1 us。

# 驱动对接（BSP/驱动作者）

实现 `rt_clock_timer_ops` 并注册设备；在中断中调用 `rt_clock_timer_isr()`。

```c
static const struct rt_clock_timer_ops timer_ops =
{
    .init      = drv_timer_init,
    .start     = drv_timer_start,
    .stop      = drv_timer_stop,
    .count_get = drv_timer_count_get,
    .control   = drv_timer_control,
};

static const struct rt_clock_timer_info timer_info =
{
    .maxfreq = 1000000,
    .minfreq = 1000,
    .maxcnt  = 0xFFFFFFFF,
    .cntmode = CLOCK_TIMER_CNTMODE_UP,
};

static rt_clock_timer_t hw_timer =
{
    .ops  = &timer_ops,
    .info = &timer_info,
};

void drv_timer_register(void)
{
    rt_clock_timer_register(&hw_timer, "timer0", RT_NULL);
}

void drv_timer_isr(void)
{
    rt_clock_timer_isr(&hw_timer);
}
```

若支持单次启动，clock_timer 设备也可作为 clock_time 默认事件设备。

补充说明：
- rt_clock_timer_register():
  - 将设备注册到 RT-Thread 设备框架，类型为 Timer。
  - 首个具备 start 操作的设备会被自动设置为 clock_time 事件设备。
  - 若默认事件尚未激活，注册后会自动初始化并打开。
- rt_clock_timer_isr():
  - 维护溢出与周期计数。
  - 通过 rx_indicate 回调上层。
  - 若为 clock_time 事件设备，会调用 `rt_clock_time_event_isr()`。

# 使用示例

以下示例演示完整流程：查找设备、打开、设置回调、周期定时、读取计数等。

```c
#include <rtthread.h>
#include <rtdevice.h>

#define CLOCK_TIMER_DEV_NAME   "timer0"     /* timer name */

static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is clock_timer timeout callback function!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int clock_timer_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_clock_timerval_t timeout_s;      /* timer timeout value */
    rt_device_t hw_dev = RT_NULL;   /* timer device handle */
    rt_clock_timer_mode_t mode;         /* timer mode */

    hw_dev = rt_device_find(CLOCK_TIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("clock_timer sample run failed! can't find %s device!\n", CLOCK_TIMER_DEV_NAME);
        return -RT_ERROR;
    }

    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", CLOCK_TIMER_DEV_NAME);
        return ret;
    }

    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    mode = CLOCK_TIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, CLOCK_TIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    timeout_s.sec = 5;
    timeout_s.usec = 0;

    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return -RT_ERROR;
    }

    rt_thread_mdelay(3500);

    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}
MSH_CMD_EXPORT(clock_timer_sample, clock_timer sample);
```
