# 时钟框架

## 简介

RT-Thread 的时钟框架为嵌入式系统中的硬件时钟管理提供了全面的基础设施。它实现了层次化时钟树模型，支持时钟门控、频率调节、父时钟切换和相位调整——这些都是电源管理和系统性能调优的关键。

### 概述

时钟管理对嵌入式系统至关重要：

- **电源管理**：关闭未使用的时钟以节省功耗
- **性能调优**：调整时钟频率以获得最佳性能
- **设备同步**：确保正确的时序关系
- **动态电压频率调节（DVFS）**：协调电压与频率
- **时钟域管理**：管理多个时钟源及其关系

常见时钟类型包括：
- **固定频率时钟**：晶振、固定 PLL
- **门控时钟**：启用/禁用控制
- **分频器**：频率分频
- **多路复用器**：父时钟选择
- **PLL**：锁相环，用于频率倍增
- **复合时钟**：上述类型的组合

### RT-Thread 实现

RT-Thread 时钟框架位于 `components/drivers/clk/`，提供：

1. **消费者 API**：设备驱动程序管理时钟的简单接口
2. **提供者 API**：实现时钟驱动程序的框架
3. **时钟树**：层次化的父子关系
4. **设备树集成**：从 FDT 自动配置
5. **引用计数**：多消费者安全启用/禁用
6. **通知链**：频率变化的事件通知
7. **频率约束**：每个消费者的最小/最大频率管理

## Kconfig 配置

### 主配置

```kconfig
menuconfig RT_USING_CLK
    bool "Using Common Clock Framework (CLK)"
    depends on RT_USING_DM
    select RT_USING_ADT_REF
    default y
```

**在 menuconfig 中的位置**：
```
RT-Thread Components → Device Drivers → Using Common Clock Framework (CLK)
```

**依赖项**：
- `RT_USING_DM`：必须首先启用
- `RT_USING_ADT_REF`：引用计数支持（自动）

**默认值**：启用 DM 时默认启用

### SCMI 时钟驱动

```kconfig
config RT_CLK_SCMI
    bool "Clock driver controlled via SCMI interface"
    depends on RT_USING_CLK
    depends on RT_FIRMWARE_ARM_SCMI
    default n
```

支持通过 ARM 系统控制和管理接口（SCMI）控制的时钟。

## 设备树绑定

### 时钟提供者属性

时钟提供者使用这些属性导出时钟：

```dts
#clock-cells = <n>;              /* 时钟说明符中的单元数 */
clock-output-names = "name1", "name2";  /* 输出时钟名称 */
```

### 时钟消费者属性

设备使用以下方式引用时钟：

```dts
clocks = <&clk_provider idx>;    /* 时钟 phandle 和索引 */
clock-names = "name";            /* 时钟连接名称 */
```

### 固定频率时钟示例

```dts
clocks {
    /* 简单固定频率振荡器 */
    osc24M: oscillator-24M {
        compatible = "fixed-clock";
        #clock-cells = <0>;
        clock-frequency = <24000000>;
        clock-output-names = "osc24M";
    };
    
    /* 带精度规范的固定频率 */
    osc32k: oscillator-32k {
        compatible = "fixed-clock";
        #clock-cells = <0>;
        clock-frequency = <32768>;
        clock-accuracy = <50>;  /* ±50 PPM */
        clock-output-names = "osc32k";
    };
};
```

### 时钟控制器示例

```dts
ccu: clock-controller@1c20000 {
    compatible = "vendor,clock-controller";
    reg = <0x1c20000 0x400>;
    #clock-cells = <1>;
    
    /* 父时钟 */
    clocks = <&osc24M>, <&osc32k>;
    clock-names = "hosc", "losc";
    
    /* 输出时钟名称（可选）*/
    clock-output-names = "pll-cpu", "pll-ddr", "ahb1", "apb1";
};
```

### 消费者使用示例

```dts
/* 单时钟消费者 */
uart0: serial@1c28000 {
    compatible = "vendor,uart";
    reg = <0x1c28000 0x400>;
    interrupts = <0 0 4>;
    
    clocks = <&ccu 64>;        /* 时钟索引 64 */
    clock-names = "baudclk";
    
    status = "okay";
};

/* 多时钟消费者 */
mmc0: mmc@1c0f000 {
    compatible = "vendor,mmc";
    reg = <0x1c0f000 0x1000>;
    
    clocks = <&ccu 8>, <&ccu 9>;
    clock-names = "ahb", "mmc";
    
    status = "okay";
};
```

## 应用层 API

### 概述

消费者 API 为设备驱动程序提供管理时钟的函数。框架使用类似 Linux 的两级 prepare/enable 模型：
- **prepare**：可能休眠，可以配置 PLL
- **enable**：原子操作，不能休眠

### 获取和释放时钟

#### rt_clk_get_by_name

```c
struct rt_clk *rt_clk_get_by_name(struct rt_device *dev, const char *name);
```

通过连接名称获取时钟。

**参数**：
- `dev`：设备结构指针
- `name`：时钟连接名称（匹配设备树中的 `clock-names`）

**返回值**：
- 成功时返回时钟指针
- 失败时返回 NULL

**示例**：
```c
struct rt_clk *clk = rt_clk_get_by_name(dev, "baudclk");
if (!clk) {
    LOG_E("获取 baudclk 失败");
    return -RT_ERROR;
}
```

#### rt_clk_get_by_index

```c
struct rt_clk *rt_clk_get_by_index(struct rt_device *dev, int index);
```

通过 `clocks` 属性中的索引获取时钟。

**参数**：
- `dev`：设备结构指针
- `index`：时钟索引（从 0 开始）

#### rt_clk_get_array

```c
struct rt_clk_array *rt_clk_get_array(struct rt_device *dev);
```

获取设备的所有时钟作为数组。

**参数**：
- `dev`：设备结构指针

**返回值**：
- 成功时返回时钟数组指针
- 失败时返回错误指针（使用 `rt_is_err()` 检查）

#### rt_clk_put

```c
void rt_clk_put(struct rt_clk *clk);
```

释放时钟引用。

### Prepare 和 Enable

#### rt_clk_prepare

```c
rt_err_t rt_clk_prepare(struct rt_clk *clk);
```

为启用准备时钟。这可能会休眠，可以配置 PLL 或执行其他不能原子完成的操作。

**参数**：
- `clk`：时钟指针

**返回值**：
- 成功时返回 `RT_EOK`
- 失败时返回错误代码

**注意**：
- 可能休眠——不要从原子上下文调用
- 必须在 `rt_clk_enable()` 之前调用
- 使用引用计数

#### rt_clk_unprepare

```c
void rt_clk_unprepare(struct rt_clk *clk);
```

取消准备先前已准备的时钟。

#### rt_clk_enable

```c
rt_err_t rt_clk_enable(struct rt_clk *clk);
```

启用时钟。这是一个不能休眠的原子操作。

**参数**：
- `clk`：时钟指针

**返回值**：
- 成功时返回 `RT_EOK`
- 失败时返回错误代码

**注意**：
- 不能休眠——可以从原子上下文安全调用
- 必须在 `rt_clk_prepare()` 之后
- 使用引用计数

#### rt_clk_disable

```c
void rt_clk_disable(struct rt_clk *clk);
```

禁用先前启用的时钟。

#### rt_clk_prepare_enable

```c
rt_err_t rt_clk_prepare_enable(struct rt_clk *clk);
```

便捷函数，准备并启用时钟。

**示例**：
```c
/* 典型用法 */
ret = rt_clk_prepare_enable(clk);
if (ret != RT_EOK) {
    LOG_E("启用时钟失败: %d", ret);
    return ret;
}
```

#### rt_clk_disable_unprepare

```c
void rt_clk_disable_unprepare(struct rt_clk *clk);
```

便捷函数，禁用并取消准备时钟。

### 频率管理

#### rt_clk_set_rate

```c
rt_err_t rt_clk_set_rate(struct rt_clk *clk, rt_ubase_t rate);
```

设置时钟频率。

**参数**：
- `clk`：时钟指针
- `rate`：期望频率（Hz）

**返回值**：
- 成功时返回 `RT_EOK`
- 失败时返回错误代码

**注意**：
- 由于硬件限制，实际频率可能不同
- 使用 `rt_clk_get_rate()` 验证实际频率
- 可能触发通知器回调

**示例**：
```c
/* 将 UART 时钟设置为 48MHz */
ret = rt_clk_set_rate(uart_clk, 48000000);
if (ret != RT_EOK) {
    LOG_E("设置时钟频率失败: %d", ret);
}

/* 验证实际频率 */
rt_ubase_t actual_rate = rt_clk_get_rate(uart_clk);
LOG_I("时钟频率: %u Hz", actual_rate);
```

#### rt_clk_get_rate

```c
rt_ubase_t rt_clk_get_rate(struct rt_clk *clk);
```

获取当前时钟频率。

**参数**：
- `clk`：时钟指针

**返回值**：
- 当前频率（Hz）
- 错误时返回 0

#### rt_clk_round_rate

```c
rt_base_t rt_clk_round_rate(struct rt_clk *clk, rt_ubase_t rate);
```

获取最接近的支持频率，但不更改时钟。

**参数**：
- `clk`：时钟指针
- `rate`：期望频率（Hz）

**返回值**：
- 最接近的支持频率
- 失败时返回负错误代码

#### rt_clk_set_rate_range

```c
rt_err_t rt_clk_set_rate_range(struct rt_clk *clk, rt_ubase_t min, rt_ubase_t max);
```

为此消费者设置可接受的频率范围。

**参数**：
- `clk`：时钟指针
- `min`：最小可接受频率（Hz）
- `max`：最大可接受频率（Hz）

**示例**：
```c
/* UART 需要 48MHz ±2% */
rt_clk_set_rate_range(uart_clk, 47040000, 48960000);
```

### 父时钟管理

#### rt_clk_set_parent

```c
rt_err_t rt_clk_set_parent(struct rt_clk *clk, struct rt_clk *parent);
```

更改时钟父时钟（用于多路复用器时钟）。

**参数**：
- `clk`：时钟指针
- `parent`：新的父时钟

#### rt_clk_get_parent

```c
struct rt_clk *rt_clk_get_parent(struct rt_clk *clk);
```

获取当前父时钟。

### 相位控制

#### rt_clk_set_phase

```c
rt_err_t rt_clk_set_phase(struct rt_clk *clk, int degrees);
```

以度为单位设置时钟相位。

**参数**：
- `clk`：时钟指针
- `degrees`：相位（度，0-359）

**返回值**：
- 成功时返回 `RT_EOK`
- 不支持时返回 `-RT_ENOSYS`

#### rt_clk_get_phase

```c
rt_base_t rt_clk_get_phase(struct rt_clk *clk);
```

获取当前时钟相位。

### 通知器 API

#### rt_clk_notifier_register

```c
rt_err_t rt_clk_notifier_register(struct rt_clk *clk, 
                                   struct rt_clk_notifier *notifier);
```

为时钟事件注册通知器。

**通知器结构**：
```c
struct rt_clk_notifier {
    rt_list_t list;
    struct rt_clk *clk;
    rt_clk_notifier_callback callback;
    void *priv;
};

typedef rt_err_t (*rt_clk_notifier_callback)(
    struct rt_clk_notifier *notifier,
    rt_ubase_t msg,
    rt_ubase_t old_rate,
    rt_ubase_t new_rate);
```

**事件消息**：
- `RT_CLK_MSG_PRE_RATE_CHANGE`：频率变化前
- `RT_CLK_MSG_POST_RATE_CHANGE`：频率成功变化后
- `RT_CLK_MSG_ABORT_RATE_CHANGE`：频率变化中止

**示例**：
```c
static rt_err_t clk_notifier_cb(struct rt_clk_notifier *notifier,
                                rt_ubase_t msg, 
                                rt_ubase_t old_rate,
                                rt_ubase_t new_rate)
{
    if (msg == RT_CLK_MSG_PRE_RATE_CHANGE) {
        LOG_I("时钟频率变化: %u -> %u Hz", old_rate, new_rate);
        /* 为频率变化做准备 */
    }
    return RT_EOK;
}

struct rt_clk_notifier my_notifier = {
    .callback = clk_notifier_cb,
};

rt_clk_notifier_register(clk, &my_notifier);
```

## 完整应用示例

### 示例：带时钟管理的 UART 驱动

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/clk.h>

struct uart_device {
    void *base;
    int irq;
    struct rt_clk *clk;
    struct rt_serial_device serial;
};

static rt_err_t uart_configure(struct rt_serial_device *serial,
                               struct serial_configure *cfg)
{
    struct uart_device *uart = rt_container_of(serial, 
                                               struct uart_device, serial);
    rt_ubase_t clk_rate;
    rt_uint32_t divisor;
    
    /* 获取时钟频率 */
    clk_rate = rt_clk_get_rate(uart->clk);
    if (clk_rate == 0) {
        LOG_E("无效的时钟频率");
        return -RT_ERROR;
    }
    
    /* 计算波特率分频器 */
    divisor = clk_rate / (16 * cfg->baud_rate);
    
    /* 配置硬件 */
    writel(divisor & 0xFF, uart->base + UART_DLL);
    writel((divisor >> 8) & 0xFF, uart->base + UART_DLH);
    
    return RT_EOK;
}

static rt_err_t uart_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct uart_device *uart;
    
    /* 分配设备结构 */
    uart = rt_calloc(1, sizeof(*uart));
    if (!uart)
        return -RT_ENOMEM;
    
    /* 映射 MMIO 区域 */
    uart->base = rt_dm_dev_iomap(dev, 0);
    if (!uart->base) {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* 获取 IRQ */
    uart->irq = rt_dm_dev_get_irq(dev, 0);
    
    /* 获取时钟 */
    uart->clk = rt_clk_get_by_name(dev, "baudclk");
    if (!uart->clk) {
        LOG_E("获取 baudclk 失败");
        ret = -RT_ERROR;
        goto err_unmap;
    }
    
    /* 准备并启用时钟 */
    ret = rt_clk_prepare_enable(uart->clk);
    if (ret != RT_EOK) {
        LOG_E("启用时钟失败: %d", ret);
        goto err_put_clk;
    }
    
    /* 注册串口设备 */
    ret = rt_hw_serial_register(&uart->serial, 
                                rt_dm_dev_get_name(dev),
                                RT_DEVICE_FLAG_RDWR,
                                uart);
    if (ret != RT_EOK) {
        goto err_disable_clk;
    }
    
    pdev->priv = uart;
    return RT_EOK;
    
err_disable_clk:
    rt_clk_disable_unprepare(uart->clk);
err_put_clk:
    rt_clk_put(uart->clk);
err_unmap:
    rt_iounmap(uart->base);
err_free:
    rt_free(uart);
    return ret;
}

static rt_err_t uart_remove(struct rt_platform_device *pdev)
{
    struct uart_device *uart = pdev->priv;
    
    /* 取消注册串口设备 */
    rt_device_unregister(&uart->serial.parent);
    
    /* 禁用并释放时钟 */
    rt_clk_disable_unprepare(uart->clk);
    rt_clk_put(uart->clk);
    
    /* 释放资源 */
    rt_iounmap(uart->base);
    rt_free(uart);
    
    return RT_EOK;
}

static const struct rt_ofw_node_id uart_ofw_ids[] = {
    { .compatible = "vendor,uart" },
    { /* sentinel */ }
};

static struct rt_platform_driver uart_driver = {
    .name = "uart",
    .ids = uart_ofw_ids,
    .probe = uart_probe,
    .remove = uart_remove,
};

RT_PLATFORM_DRIVER_EXPORT(uart_driver);
```

## 驱动实现指南

### 核心结构

#### rt_clk_ops

```c
struct rt_clk_ops {
    /* Prepare/unprepare (可能休眠) */
    rt_err_t    (*prepare)(struct rt_clk_cell *cell);
    void        (*unprepare)(struct rt_clk_cell *cell);
    rt_bool_t   (*is_prepared)(struct rt_clk_cell *cell);
    
    /* Enable/disable (原子操作) */
    rt_err_t    (*enable)(struct rt_clk_cell *cell);
    void        (*disable)(struct rt_clk_cell *cell);
    rt_bool_t   (*is_enabled)(struct rt_clk_cell *cell);
    
    /* 频率控制 */
    rt_ubase_t  (*recalc_rate)(struct rt_clk_cell *cell, rt_ubase_t parent_rate);
    rt_base_t   (*round_rate)(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate);
    rt_err_t    (*set_rate)(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate);
    
    /* 父时钟控制 */
    rt_err_t    (*set_parent)(struct rt_clk_cell *cell, rt_uint8_t idx);
    rt_uint8_t  (*get_parent)(struct rt_clk_cell *cell);
};
```

### 示例：固定频率时钟驱动

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/clk.h>

struct clk_fixed {
    struct rt_clk_node parent;
    struct rt_clk_fixed_rate fcell;
    struct rt_clk_cell *cells[1];
};

static rt_ubase_t fixed_clk_recalc_rate(struct rt_clk_cell *cell, 
                                        rt_ubase_t parent_rate)
{
    struct rt_clk_fixed_rate *fr = rt_container_of(cell, 
                                                   struct rt_clk_fixed_rate, 
                                                   cell);
    return fr->fixed_rate;
}

static struct rt_clk_ops fixed_clk_ops = {
    .recalc_rate = fixed_clk_recalc_rate,
};

static rt_err_t fixed_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t val;
    struct rt_device *dev = &pdev->parent;
    struct clk_fixed *cf;
    
    /* 分配驱动结构 */
    cf = rt_calloc(1, sizeof(*cf));
    if (!cf)
        return -RT_ENOMEM;
    
    /* 从设备树读取时钟频率 */
    if ((err = rt_dm_dev_prop_read_u32(dev, "clock-frequency", &val))) {
        LOG_E("缺少 clock-frequency 属性");
        goto _fail;
    }
    cf->fcell.fixed_rate = val;
    
    /* 读取可选的精度 */
    val = 0;
    rt_dm_dev_prop_read_u32(dev, "clock-accuracy", &val);
    cf->fcell.fixed_accuracy = val;
    
    /* 读取可选的时钟名称 */
    rt_dm_dev_prop_read_string(dev, "clock-output-names", 
                               &cf->fcell.cell.name);
    
    /* 初始化时钟节点 */
    cf->parent.dev = dev;
    cf->parent.cells_nr = 1;
    cf->parent.cells = cf->cells;
    cf->cells[0] = &cf->fcell.cell;
    cf->fcell.cell.ops = &fixed_clk_ops;
    
    /* 向框架注册 */
    if ((err = rt_clk_register(&cf->parent))) {
        LOG_E("注册时钟失败: %d", err);
        goto _fail;
    }
    
    LOG_I("固定时钟 '%s' 已注册: %u Hz", 
          cf->fcell.cell.name, cf->fcell.fixed_rate);
    
    return RT_EOK;
    
_fail:
    rt_free(cf);
    return err;
}

static const struct rt_ofw_node_id fixed_clk_ofw_ids[] = {
    { .compatible = "fixed-clock" },
    { /* sentinel */ }
};

static struct rt_platform_driver fixed_clk_driver = {
    .name = "clk-fixed-rate",
    .ids = fixed_clk_ofw_ids,
    .probe = fixed_clk_probe,
};

static int fixed_clk_drv_register(void)
{
    rt_platform_driver_register(&fixed_clk_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(fixed_clk_drv_register);
```

## 最佳实践

### 对于消费者驱动程序

1. **始终使用 prepare_enable/disable_unprepare**：更简单、更安全
2. **检查返回值**：时钟操作可能失败
3. **平衡 enable/disable**：每次启用都要匹配一次禁用
4. **顺序很重要**：在使用硬件之前启用时钟
5. **处理频率变化**：如果频率变化影响操作，使用通知器
6. **设置频率约束**：需要时使用 `rt_clk_set_rate_range()`

### 对于提供者驱动程序

1. **仅实现支持的操作**：不支持的操作留 NULL
2. **尽可能缓存频率**：避免在 `get_rate()` 中访问硬件
3. **处理引用计数**：框架管理 prepare/enable 计数
4. **传播频率变化**：更新子时钟的缓存频率
5. **支持多个父时钟**：用于多路复用器时钟

### 常见模式

#### 简单时钟使用

```c
/* 获取并启用时钟 */
struct rt_clk *clk = rt_clk_get_by_name(dev, "clk");
if (!clk)
    return -RT_ERROR;

ret = rt_clk_prepare_enable(clk);
if (ret != RT_EOK) {
    rt_clk_put(clk);
    return ret;
}

/* 使用硬件 */

/* 清理 */
rt_clk_disable_unprepare(clk);
rt_clk_put(clk);
```

#### 动态频率调节

```c
/* 根据工作负载更改频率 */
switch (perf_level) {
case PERF_HIGH:
    rt_clk_set_rate(cpu_clk, 1000000000);  /* 1GHz */
    break;
case PERF_NORMAL:
    rt_clk_set_rate(cpu_clk, 800000000);   /* 800MHz */
    break;
case PERF_LOW:
    rt_clk_set_rate(cpu_clk, 400000000);   /* 400MHz */
    break;
}
```

## 故障排除

### 常见问题

1. **找不到时钟**
   - 检查设备树：确保 `clocks` 和 `clock-names` 属性存在
   - 检查 compatible 字符串：验证时钟驱动已加载
   - 检查 Kconfig：启用时钟框架和驱动程序

2. **启用失败**
   - 检查父时钟：父时钟必须先启用
   - 检查 prepare：必须在 enable 之前 prepare
   - 检查硬件：验证时钟控制器是否可访问

3. **频率错误**
   - 检查父频率：父时钟必须是正确的频率
   - 检查分频器：硬件可能有有限的分频器值
   - 使用 `rt_clk_round_rate()`：验证支持的频率

## 性能考虑

### 内存使用

- 每个时钟单元：约 80-100 字节
- 每个消费者引用：约 40 字节
- 时钟树开销：取决于层次深度

### 时序

- prepare/enable：可能很慢（PLL 需要 ms）
- 频率变化：可能很慢，使用通知器
- get_rate：通常很快（已缓存）

### 优化技巧

1. **缓存时钟指针**：不要重复调用 get/put
2. **批量操作**：尽可能使用时钟数组
3. **避免不必要的频率变化**：先检查当前频率
4. **使用 prepare_enable**：组合两个操作

## 相关模块

- **regulator**：电源管理，与时钟协调
- **pinctrl**：引脚配置，可能需要启用时钟
- **reset**：复位控制，与时钟启用协调
- **pmdomain**：电源域，更高级别的电源管理

## 参考资料

- RT-Thread 源代码：`components/drivers/clk/`
- 头文件：`components/drivers/include/drivers/clk.h`
- 设备树绑定：[Linux Clock Bindings](https://www.kernel.org/doc/Documentation/devicetree/bindings/clock/)
- [RT-Thread DM 文档](../README_zh.md)
