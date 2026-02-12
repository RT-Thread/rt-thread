# Clock Time Core

clock_time core 定义了子系统的设备模型与换算接口，负责默认时钟源/事件
选择，并提供计数值与纳秒之间的定点换算。

# 设备模型

## 时钟操作接口

```c
struct rt_clock_time_ops
{
    rt_uint64_t (*get_freq)(struct rt_clock_time_device *dev);
    rt_uint64_t (*get_counter)(struct rt_clock_time_device *dev);
    rt_err_t    (*set_timeout)(struct rt_clock_time_device *dev, rt_uint64_t delta);
};
```

### get_freq

- 作用：返回计数频率（Hz）。
- 要求：
  - 频率应稳定并与 get_counter 使用的计数源一致。
  - 返回 0 表示设备尚不可用。

### get_counter

- 作用：返回单调递增计数值。
- 要求：
  - 不能回退。
  - 允许回绕，但需与硬件计数位宽一致。

### set_timeout

- 作用：设置相对当前计数的超时事件。
- 参数：`delta` 为计数单位，与 get_counter 一致。
- 行为：
  - 若 `delta` 为 0 且硬件支持，可取消事件。
  - 不支持时应返回 -RT_ENOSYS。

## 时钟设备对象

```c
struct rt_clock_time_device
{
    struct rt_device parent;
    const struct rt_clock_time_ops *ops;
    rt_uint64_t res_scale;
    rt_uint8_t caps; /* RT_CLOCK_TIME_CAP_SOURCE / RT_CLOCK_TIME_CAP_EVENT */
};
```

- res_scale 用于提高换算精度，0 表示使用 RT_CLOCK_TIME_RESMUL 默认值。
- caps 用于标识设备能力：时钟源或时钟事件。

## 注册与默认选择

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

- 作用：注册 clock_time 设备及其能力。
- 参数：
  - `dev`：设备对象，需初始化 ops 与 res_scale。
  - `name`：设备名；为 NULL 时仅注册能力，不进入设备框架。
  - `caps`：RT_CLOCK_TIME_CAP_SOURCE / RT_CLOCK_TIME_CAP_EVENT。
- 行为：
  - 当 `name` 非空时，以 RT_Device_Class_Timer 注册到设备框架。
  - 首个时钟源/事件默认成为系统默认。
- 返回值：成功返回 RT_EOK，失败返回负错误码。

### rt_clock_time_set_default_source / rt_clock_time_set_default_event

- 作用：显式设置默认时钟源/事件设备。
- 说明：会覆盖自动选择结果。

### rt_clock_time_get_default_source / rt_clock_time_get_default_event

- 作用：获取当前默认设备。
- 行为：
  - 若无时钟源，返回内部 tick 源。
  - 若无事件设备，返回 NULL。

### rt_clock_time_source_init

- 作用：BSP 提供时钟源的弱符号入口。
- 说明：可在 BSP 中重写该函数完成设备注册。

# 时钟查询接口

```c
rt_uint64_t rt_clock_time_get_freq(void);
rt_uint64_t rt_clock_time_get_counter(void);
rt_uint64_t rt_clock_time_get_event_freq(void);
rt_uint64_t rt_clock_time_get_event_res_scaled(void);
```

## rt_clock_time_get_freq

- 作用：获取默认时钟源频率（Hz）。
- 返回值：成功返回非 0 频率；无有效时钟源则返回 0。

## rt_clock_time_get_counter

- 作用：获取默认时钟源计数值。
- 返回值：成功返回计数值；无有效时钟源则返回 0。

## rt_clock_time_get_event_freq

- 作用：获取事件设备频率（Hz）。
- 行为：若无事件设备则回退使用默认时钟源。

## rt_clock_time_get_event_res_scaled

- 作用：获取事件设备的缩放分辨率。
- 行为：若无事件设备则回退使用默认时钟源。

# 换算接口

```c
rt_uint64_t rt_clock_time_get_res_scaled(void);
rt_uint64_t rt_clock_time_counter_to_ns(rt_uint64_t cnt);
rt_uint64_t rt_clock_time_ns_to_counter(rt_uint64_t ns);
```

## rt_clock_time_get_res_scaled

- 作用：获取默认时钟源的缩放分辨率。
- 返回值：无有效时钟源时返回 0。

## rt_clock_time_counter_to_ns

- 作用：将计数值换算为纳秒。
- 说明：当分辨率不可用时返回 0。

## rt_clock_time_ns_to_counter

- 作用：将纳秒换算为计数值。
- 说明：当分辨率不可用时返回 0。

核心使用定点缩放换算：

```
res_scaled = (1e9 * res_scale) / freq
```

然后用 RT_CLOCK_TIME_RESMUL 进行定点缩放，以避免浮点运算带来的精度损失。

# 事件接口

```c
rt_err_t rt_clock_time_set_timeout(rt_uint64_t delta);
void rt_clock_time_event_isr(void);
```

## rt_clock_time_set_timeout

- 作用：通过默认事件设备设置下一次超时。
- 参数：`delta` 为事件设备计数单位。
- 返回值：
  - RT_EOK：成功。
  - -RT_ENOSYS：无事件设备或不支持 set_timeout。

## rt_clock_time_event_isr

- 作用：事件到期时驱动 hrtimer 处理。
- 使用方式：
  - 在硬件中断中确认中断后调用该函数。
  - 该函数处理已到期的 hrtimer 并编程下一次事件。

# BSP 集成示例

## 注册时钟源

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

## 注册时钟事件

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

# 注意事项

- 使用硬件事件时，回调可能运行于中断上下文。
- 未提供事件设备时，hrtimer 会退化到软件定时器实现。
