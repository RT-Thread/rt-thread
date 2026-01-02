# Regulator 框架

## 简介

RT-Thread 的 Regulator（调节器）框架为嵌入式系统中的电压和电流调节器管理提供了标准化接口。调节器是为各种硬件外设、处理器和其他系统组件提供稳定电源供应的关键组件。

### 概述

电压调节器是一种电子电路，无论负载电流或输入电压如何变化，都能保持恒定的电压水平。它们对于以下方面至关重要：

- **电源管理**：高效的电源分配和管理
- **电压调节**：动态电压和频率调节（DVFS）以优化功耗
- **设备保护**：保护设备免受过压和过流影响
- **系统稳定性**：确保硬件组件稳定运行

常见的调节器类型包括：
- **线性调节器**：简单、低噪声但效率较低
- **开关调节器（SMPS）**：更高效但可能产生噪声
- **LDO（低压差调节器）**：压差低的线性调节器
- **降压/升压转换器**：降压/升压开关调节器

### RT-Thread 实现

RT-Thread 的调节器框架位于 `components/drivers/regulator/`，提供：

1. **消费者 API**：设备驱动程序管理电源的简单接口
2. **提供者 API**：实现调节器驱动程序的框架
3. **调节器树**：调节器依赖关系的层次化管理
4. **设备树集成**：从设备树自动配置
5. **引用计数**：多消费者安全启用/禁用
6. **通知链**：电压变化的事件通知
7. **多驱动支持**：固定、GPIO 控制、SCMI 基础的调节器

**架构**：
```
┌─────────────────────────────────────────────────────────┐
│                  消费者驱动程序                          │
│    (UART, SPI, I2C, MMC, CPU 等)                        │
└────────────────────┬────────────────────────────────────┘
                     │ 消费者 API
                     │ (get, enable, set_voltage 等)
┌────────────────────┴────────────────────────────────────┐
│             Regulator 框架核心                           │
│  - 引用计数                                              │
│  - 调节器树管理                                          │
│  - 通知链                                                │
│  - 电压/电流验证                                         │
└────────────────────┬────────────────────────────────────┘
                     │ 提供者 API
                     │ (操作回调)
┌────────────────────┴────────────────────────────────────┐
│            调节器驱动程序                                 │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
│  │   固定      │  │    GPIO     │  │    SCMI     │     │
│  │  调节器     │  │   调节器    │  │   调节器    │     │
│  └─────────────┘  └─────────────┘  └─────────────┘     │
└────────────────────┬────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────┐
│               硬件调节器                                  │
│  (PMIC、分立调节器、电源)                                │
└──────────────────────────────────────────────────────────┘
```

## Kconfig 配置

### 主配置

调节器框架依赖于设备驱动模型（DM）：

```kconfig
menuconfig RT_USING_REGULATOR
    bool "Using Voltage and Current Regulator"
    select RT_USING_ADT
    select RT_USING_ADT_REF
    depends on RT_USING_DM
    default n
```

**在 menuconfig 中的位置**：
```
RT-Thread Components → Device Drivers → Using Voltage and Current Regulator
```

**依赖项**：
- `RT_USING_DM`：必须首先启用
- `RT_USING_ADT`：抽象数据类型（自动）
- `RT_USING_ADT_REF`：引用计数支持（自动）

### 调节器驱动选项

#### 固定调节器
```kconfig
config RT_REGULATOR_FIXED
    bool "Fixed regulator support"
    depends on RT_USING_REGULATOR
    depends on RT_USING_PIN
    depends on RT_USING_PINCTRL
    default y
```

支持固定输出电压的调节器，可选通过 GPIO 使能引脚控制。

#### GPIO 调节器
```kconfig
config RT_REGULATOR_GPIO
    bool "GPIO regulator support"
    depends on RT_USING_REGULATOR
    depends on RT_USING_PIN
    default y
```

支持通过 GPIO 引脚选择多个电压级别的调节器。

#### SCMI 调节器
```kconfig
config RT_REGULATOR_SCMI
    bool "SCMI regulator support"
    depends on RT_USING_REGULATOR
    depends on RT_USING_OFW
    depends on RT_FIRMWARE_ARM_SCMI
    default n
```

支持通过 ARM 系统控制和管理接口（SCMI）控制的调节器。

## 设备树绑定

### 通用属性

所有调节器节点支持这些标准属性：

```dts
regulator-name = "supply_name";            /* 可读名称 */
regulator-min-microvolt = <value>;         /* 最小电压（µV）*/
regulator-max-microvolt = <value>;         /* 最大电压（µV）*/
regulator-min-microamp = <value>;          /* 最小电流（µA）*/
regulator-max-microamp = <value>;          /* 最大电流（µA）*/
regulator-ramp-delay = <value>;            /* 电压变化率（µV/µs）*/
regulator-enable-ramp-delay = <value>;     /* 使能延迟（µs）*/
regulator-settling-time-us = <value>;      /* 稳定时间（µs）*/
regulator-settling-time-up-us = <value>;   /* 电压升高稳定时间 */
regulator-settling-time-down-us = <value>; /* 电压降低稳定时间 */
enable-active-high;                        /* 使能引脚高电平有效（默认）*/
regulator-boot-on;                         /* 启动时使能 */
regulator-always-on;                       /* 永不禁用 */
regulator-soft-start;                      /* 使能软启动 */
regulator-pull-down;                       /* 关闭时使能下拉 */
regulator-over-current-protection;         /* 使能过流保护 */
```

### 固定调节器示例

固定调节器具有恒定的输出电压：

```dts
regulators {
    /* 简单的固定 3.3V 调节器 */
    vcc_3v3: regulator-vcc-3v3 {
        compatible = "regulator-fixed";
        regulator-name = "vcc-3v3";
        regulator-min-microvolt = <3300000>;
        regulator-max-microvolt = <3300000>;
        regulator-always-on;
        regulator-boot-on;
    };
    
    /* 带 GPIO 使能控制的固定调节器 */
    vcc_sd: regulator-vcc-sd {
        compatible = "regulator-fixed";
        regulator-name = "vcc-sd";
        regulator-min-microvolt = <3300000>;
        regulator-max-microvolt = <3300000>;
        gpio = <&gpio0 10 GPIO_ACTIVE_HIGH>;
        pinctrl-names = "default";
        pinctrl-0 = <&sd_power_pins>;
        enable-active-high;
        startup-delay-us = <100000>;  /* 100ms */
        off-on-delay-us = <10000>;    /* 10ms */
    };
    
    /* 由另一个调节器供电的调节器 */
    vcc_1v8: regulator-vcc-1v8 {
        compatible = "regulator-fixed";
        regulator-name = "vcc-1v8";
        regulator-min-microvolt = <1800000>;
        regulator-max-microvolt = <1800000>;
        vin-supply = <&vcc_3v3>;      /* 父供电 */
        regulator-always-on;
    };
};
```

### 设备树中的消费者使用

设备使用 supply 属性引用调节器：

```dts
/* 带多个电源的 UART */
uart0: serial@10000000 {
    compatible = "vendor,uart";
    reg = <0x10000000 0x1000>;
    interrupts = <32>;
    clocks = <&clk_uart0>;
    
    /* 电源 */
    vdd-supply = <&vcc_3v3>;       /* 核心供电 */
    vddio-supply = <&vcc_1v8>;     /* I/O 供电 */
    
    status = "okay";
};

/* 带调节器控制的 MMC/SD 控制器 */
mmc0: mmc@20000000 {
    compatible = "vendor,mmc";
    reg = <0x20000000 0x1000>;
    
    vmmc-supply = <&vcc_sd>;       /* 卡电源 */
    vqmmc-supply = <&vcc_1v8>;     /* I/O 电平转换器电源 */
    
    status = "okay";
};
```

## 应用层 API

### 概述

消费者 API 为设备驱动程序提供管理其电源供应的函数。所有操作都使用通过 get API 获得的不透明 `struct rt_regulator` 指针。

### 获取和释放调节器

#### rt_regulator_get

```c
struct rt_regulator *rt_regulator_get(struct rt_device *dev, const char *id);
```

为设备获取调节器。

**参数**：
- `dev`：设备结构指针
- `id`：供电名称（匹配设备树中的 `<name>-supply`，例如 "vdd"、"vmmc"）

**返回值**：
- 成功时返回调节器指针
- 失败时返回 NULL

**示例**：
```c
struct rt_device *dev = &pdev->parent;
struct rt_regulator *vdd_reg;

/* 获取 "vdd" 供电 */
vdd_reg = rt_regulator_get(dev, "vdd");
if (!vdd_reg) {
    LOG_E("Failed to get vdd regulator");
    return -RT_ERROR;
}
```

#### rt_regulator_put

```c
void rt_regulator_put(struct rt_regulator *reg);
```

释放调节器引用。

**参数**：
- `reg`：从 `rt_regulator_get()` 获得的调节器指针

### 启用和禁用

#### rt_regulator_enable

```c
rt_err_t rt_regulator_enable(struct rt_regulator *reg);
```

启用调节器。使用引用计数，因此多次启用需要匹配的禁用。

**参数**：
- `reg`：调节器指针

**返回值**：
- 成功时返回 `RT_EOK`
- 失败时返回错误代码

**注意**：
- 自动启用父调节器
- 如果配置了启用延迟，则等待
- 调用通知链

**示例**：
```c
rt_err_t ret;

ret = rt_regulator_enable(vdd_reg);
if (ret != RT_EOK) {
    LOG_E("Failed to enable regulator: %d", ret);
    return ret;
}
```

#### rt_regulator_disable

```c
rt_err_t rt_regulator_disable(struct rt_regulator *reg);
```

禁用调节器。仅当引用计数达到零时才实际禁用。

**参数**：
- `reg`：调节器指针

**返回值**：
- 成功时返回 `RT_EOK`
- 失败时返回错误代码

#### rt_regulator_is_enabled

```c
rt_bool_t rt_regulator_is_enabled(struct rt_regulator *reg);
```

检查调节器当前是否启用。

**参数**：
- `reg`：调节器指针

**返回值**：
- 启用时返回 `RT_TRUE`
- 禁用时返回 `RT_FALSE`

### 电压控制

#### rt_regulator_set_voltage

```c
rt_err_t rt_regulator_set_voltage(struct rt_regulator *reg, int min_uvolt, int max_uvolt);
```

在范围内设置调节器输出电压。

**参数**：
- `reg`：调节器指针
- `min_uvolt`：最小可接受电压（微伏，µV）
- `max_uvolt`：最大可接受电压（微伏，µV）

**返回值**：
- 成功时返回 `RT_EOK`
- 不支持电压控制时返回 `-RT_ENOSYS`
- 失败时返回错误代码

**注意**：
- 电压必须在调节器配置的范围内
- 框架在指定范围内选择最佳电压
- 电压变化后等待稳定时间
- 调用通知链并发送电压变化事件

**示例**：
```c
/* 将电压设置为 1.8V ±5% */
ret = rt_regulator_set_voltage(vdd_reg, 1710000, 1890000);
if (ret != RT_EOK) {
    LOG_E("Failed to set voltage: %d", ret);
}

/* 设置精确电压 */
ret = rt_regulator_set_voltage(vdd_reg, 3300000, 3300000);
```

#### rt_regulator_get_voltage

```c
int rt_regulator_get_voltage(struct rt_regulator *reg);
```

获取当前调节器输出电压。

**参数**：
- `reg`：调节器指针

**返回值**：
- 当前电压（微伏，µV）
- 失败时返回负错误代码

**示例**：
```c
int voltage = rt_regulator_get_voltage(vdd_reg);
if (voltage > 0) {
    LOG_I("当前电压: %d.%03dV", voltage / 1000000, (voltage / 1000) % 1000);
}
```

### 工作模式

#### rt_regulator_set_mode

```c
rt_err_t rt_regulator_set_mode(struct rt_regulator *reg, rt_uint32_t mode);
```

设置调节器工作模式。

**参数**：
- `reg`：调节器指针
- `mode`：工作模式标志：
  - `RT_REGULATOR_MODE_FAST`：高速模式（功耗较高）
  - `RT_REGULATOR_MODE_NORMAL`：正常工作模式
  - `RT_REGULATOR_MODE_IDLE`：空闲模式（性能降低）
  - `RT_REGULATOR_MODE_STANDBY`：待机模式（功耗最低）

**返回值**：
- 成功时返回 `RT_EOK`
- 不支持模式控制时返回 `-RT_ENOSYS`
- 失败时返回错误代码

**示例**：
```c
/* 空闲期间设置为低功耗模式 */
rt_regulator_set_mode(vdd_reg, RT_REGULATOR_MODE_IDLE);

/* 恢复正常模式 */
rt_regulator_set_mode(vdd_reg, RT_REGULATOR_MODE_NORMAL);
```

## 完整应用示例

### 示例：带调节器控制的 MMC/SD 驱动程序

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/regulator.h>
#include <drivers/clk.h>

struct mmc_host {
    void *base;
    int irq;
    struct rt_clk *clk;
    struct rt_regulator *vmmc;  /* 卡电源 */
    struct rt_regulator *vqmmc; /* I/O 电压电源 */
};

static rt_err_t mmc_power_on(struct mmc_host *host)
{
    rt_err_t ret;
    
    /* 启用卡电源 */
    ret = rt_regulator_enable(host->vmmc);
    if (ret != RT_EOK) {
        LOG_E("启用 vmmc 失败: %d", ret);
        return ret;
    }
    
    /* 将 I/O 电压设置为初始 3.3V */
    ret = rt_regulator_enable(host->vqmmc);
    if (ret != RT_EOK) {
        LOG_E("启用 vqmmc 失败: %d", ret);
        goto err_disable_vmmc;
    }
    
    ret = rt_regulator_set_voltage(host->vqmmc, 3300000, 3300000);
    if (ret != RT_EOK) {
        goto err_disable_vqmmc;
    }
    
    /* 启用时钟 */
    ret = rt_clk_prepare_enable(host->clk);
    if (ret != RT_EOK) {
        goto err_disable_vqmmc;
    }
    
    return RT_EOK;
    
err_disable_vqmmc:
    rt_regulator_disable(host->vqmmc);
err_disable_vmmc:
    rt_regulator_disable(host->vmmc);
    return ret;
}

static void mmc_power_off(struct mmc_host *host)
{
    /* 禁用时钟 */
    rt_clk_disable_unprepare(host->clk);
    
    /* 按相反顺序禁用调节器 */
    rt_regulator_disable(host->vqmmc);
    rt_regulator_disable(host->vmmc);
}

static rt_err_t mmc_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct mmc_host *host;
    
    /* 分配主机结构 */
    host = rt_calloc(1, sizeof(*host));
    if (!host)
        return -RT_ENOMEM;
    
    /* 映射 MMIO 区域 */
    host->base = rt_dm_dev_iomap(dev, 0);
    if (!host->base) {
        ret = -RT_ERROR;
        goto err_free_host;
    }
    
    /* 获取 IRQ */
    host->irq = rt_dm_dev_get_irq(dev, 0);
    
    /* 获取时钟 */
    host->clk = rt_clk_get_by_name(dev, "mmc");
    if (!host->clk) {
        ret = -RT_ERROR;
        goto err_iounmap;
    }
    
    /* 获取调节器 */
    host->vmmc = rt_regulator_get(dev, "vmmc");
    host->vqmmc = rt_regulator_get(dev, "vqmmc");
    
    /* 启动 MMC */
    if (host->vmmc || host->vqmmc) {
        ret = mmc_power_on(host);
        if (ret != RT_EOK) {
            goto err_put_regulators;
        }
    }
    
    pdev->priv = host;
    LOG_I("MMC 主机已初始化");
    
    return RT_EOK;
    
err_put_regulators:
    if (host->vqmmc)
        rt_regulator_put(host->vqmmc);
    if (host->vmmc)
        rt_regulator_put(host->vmmc);
    rt_clk_put(host->clk);
err_iounmap:
    rt_iounmap(host->base);
err_free_host:
    rt_free(host);
    return ret;
}
```

## 驱动实现指南

### 核心结构

#### rt_regulator_param

```c
struct rt_regulator_param {
    const char *name;               /* 调节器名称 */
    
    int min_uvolt;                  /* 最小电压（µV）*/
    int max_uvolt;                  /* 最大电压（µV）*/
    int min_uamp;                   /* 最小电流（µA）*/
    int max_uamp;                   /* 最大电流（µA）*/
    int ramp_delay;                 /* 电压爬坡率（µV/µs）*/
    int enable_delay;               /* 使能延迟（µs）*/
    int off_on_delay;               /* 关闭到打开延迟（µs）*/
    
    rt_uint32_t enable_active_high:1;       /* 使能引脚极性 */
    rt_uint32_t boot_on:1;                  /* 启动时启用 */
    rt_uint32_t always_on:1;                /* 永不禁用 */
    rt_uint32_t soft_start:1;               /* 软启动启用 */
};
```

#### rt_regulator_ops

```c
struct rt_regulator_ops {
    rt_err_t    (*enable)(struct rt_regulator_node *reg);
    rt_err_t    (*disable)(struct rt_regulator_node *reg);
    rt_bool_t   (*is_enabled)(struct rt_regulator_node *reg);
    rt_err_t    (*set_voltage)(struct rt_regulator_node *reg, int min_uvolt, int max_uvolt);
    int         (*get_voltage)(struct rt_regulator_node *reg);
    rt_err_t    (*set_mode)(struct rt_regulator_node *reg, rt_uint32_t mode);
    rt_int32_t  (*get_mode)(struct rt_regulator_node *reg);
};
```

所有回调都是可选的。只实现硬件支持的功能。

### 简单固定调节器驱动程序示例

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/regulator.h>
#include <drivers/pin.h>

struct my_regulator {
    struct rt_regulator_node reg_node;
    struct rt_regulator_param param;
    rt_base_t enable_pin;
};

static rt_err_t my_regulator_enable(struct rt_regulator_node *reg_node)
{
    struct my_regulator *reg = rt_container_of(reg_node, struct my_regulator, reg_node);
    
    if (reg->enable_pin >= 0) {
        rt_pin_mode(reg->enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(reg->enable_pin, 
                    reg->param.enable_active_high ? PIN_HIGH : PIN_LOW);
    }
    
    return RT_EOK;
}

static rt_err_t my_regulator_disable(struct rt_regulator_node *reg_node)
{
    struct my_regulator *reg = rt_container_of(reg_node, struct my_regulator, reg_node);
    
    if (reg->enable_pin >= 0) {
        rt_pin_mode(reg->enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(reg->enable_pin,
                    reg->param.enable_active_high ? PIN_LOW : PIN_HIGH);
    }
    
    return RT_EOK;
}

static const struct rt_regulator_ops my_regulator_ops = {
    .enable = my_regulator_enable,
    .disable = my_regulator_disable,
};

static rt_err_t my_regulator_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct my_regulator *reg;
    rt_uint32_t voltage;
    
    /* 分配调节器结构 */
    reg = rt_calloc(1, sizeof(*reg));
    if (!reg)
        return -RT_ENOMEM;
    
    /* 解析设备树属性 */
    rt_dm_dev_prop_read_u32(dev, "regulator-min-microvolt", &voltage);
    reg->param.min_uvolt = voltage;
    
    rt_dm_dev_prop_read_u32(dev, "regulator-max-microvolt", &voltage);
    reg->param.max_uvolt = voltage;
    
    reg->param.name = rt_dm_dev_get_name(dev);
    reg->param.enable_active_high = 
        rt_dm_dev_prop_read_bool(dev, "enable-active-high");
    
    /* 获取使能 GPIO 引脚 */
    reg->enable_pin = rt_pin_get_named_pin(dev, "enable", 0, RT_NULL, RT_NULL);
    
    /* 初始化调节器节点 */
    reg->reg_node.dev = dev;
    reg->reg_node.supply_name = reg->param.name;
    reg->reg_node.ops = &my_regulator_ops;
    reg->reg_node.param = &reg->param;
    
    /* 向框架注册 */
    ret = rt_regulator_register(&reg->reg_node);
    if (ret != RT_EOK) {
        rt_free(reg);
        return ret;
    }
    
    pdev->priv = reg;
    return RT_EOK;
}

static const struct rt_ofw_node_id my_regulator_ofw_ids[] = {
    { .compatible = "myvendor,my-regulator" },
    { /* sentinel */ }
};

static struct rt_platform_driver my_regulator_driver = {
    .name = "my-regulator",
    .ids = my_regulator_ofw_ids,
    .probe = my_regulator_probe,
};

RT_PLATFORM_DRIVER_EXPORT(my_regulator_driver);
```

## 最佳实践

### 对于消费者驱动程序

1. **始终检查返回值**：调节器操作可能失败
2. **平衡启用/禁用**：每次启用都要匹配一次禁用
3. **顺序很重要**：在时钟之前启用调节器，按相反顺序禁用
4. **使用电压范围**：指定可接受的电压范围，而不是精确值
5. **处理探测延迟**：调节器在早期启动时可能不可用

### 对于提供者驱动程序

1. **仅实现支持的操作**：不支持的操作留 NULL
2. **使用引用计数**：不要自己跟踪启用，框架会处理
3. **报告准确的参数**：提供正确的电压范围和延迟
4. **处理父供电**：在设备树中为链式调节器设置 `vin-supply`

### 常见模式

#### 电源时序

```c
/* 正确的上电顺序 */
rt_regulator_enable(core_supply);
rt_regulator_enable(io_supply);
rt_clk_prepare_enable(clock);
/* 初始化硬件 */

/* 正确的断电顺序（相反顺序）*/
/* 关闭硬件 */
rt_clk_disable_unprepare(clock);
rt_regulator_disable(io_supply);
rt_regulator_disable(core_supply);
```

## 故障排除

### 常见问题

1. **找不到调节器**
   - 检查设备树：确保 `<name>-supply` 属性存在
   - 检查 compatible 字符串：验证调节器驱动已加载
   - 检查 Kconfig：启用调节器支持和驱动程序

2. **启用/禁用不平衡**
   - 计数启用/禁用调用：它们必须匹配
   - 检查错误路径：确保清理代码在失败时禁用
   - 使用调试：添加 LOG_D 调用以跟踪引用计数

3. **电压超出范围**
   - 检查设备树：验证 `regulator-min/max-microvolt` 属性
   - 检查硬件：确保物理调节器支持该电压
   - 检查父供电：父级必须支持子级的电压范围

## 性能考虑

### 内存使用

- 每个调节器节点：约 100-150 字节
- 每个消费者引用：约 16 字节
- 设备树开销：取决于复杂性

### 时序考虑

- 使能延迟：由硬件指定（µs 到 ms）
- 爬坡延迟：电压相关（µs/伏）
- 通知器开销：与注册的通知器数量成线性关系

## 相关模块

- **clk**：时钟管理，通常与调节器控制配对
- **pinctrl**：引脚配置，可能需要电压切换
- **pmdomain**：电源域管理，更高级别的电源控制
- **thermal**：热管理，可能触发电压/频率调节

## 参考资料

- RT-Thread 源代码：`components/drivers/regulator/`
- 头文件：`components/drivers/include/drivers/regulator.h`
- 设备树绑定：[Linux Regulator 绑定](https://www.kernel.org/doc/Documentation/devicetree/bindings/regulator/)
- [RT-Thread DM 文档](../README_zh.md)
