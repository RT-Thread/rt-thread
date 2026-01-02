# Pin Control (Pinctrl) 框架

## 概述

Pin Control 框架提供了一个统一的接口来管理 SoC 的引脚功能复用和配置。现代 SoC 通常具有多功能引脚，可以配置为不同的功能（如 GPIO、UART、SPI 等）并具有各种电气属性（上拉、下拉、驱动强度等）。

### RT-Thread 实现

RT-Thread 的 Pinctrl 框架集成了设备驱动模型，允许：

- 基于设备树的引脚配置
- 运行时引脚功能切换
- 引脚状态管理（用于电源管理）
- 与 GPIO 框架协同工作
- 通过 SCMI 进行引脚控制

## Kconfig 配置

### 主要配置选项

#### RT_USING_PINCTRL

启用 Pin Control 框架支持。

**路径**: `RT-Thread Components` → `Device Drivers` → `Using Pin Control (pinctrl)`

**说明**: 启用后可以使用设备树配置引脚功能和参数。

#### RT_PINCTRL_SCMI

通过 SCMI (System Control and Management Interface) 协议进行引脚控制。

**路径**: `RT-Thread Components` → `Device Drivers` → `Using Pin Control (pinctrl)` → `Enable SCMI pinctrl driver`

**说明**: 用于带有专用系统控制处理器的系统。

#### RT_PINCTRL_SINGLE

Simple pinctrl driver 支持单寄存器引脚配置。

**路径**: `RT-Thread Components` → `Device Drivers` → `Using Pin Control (pinctrl)` → `Enable simple pinctrl driver`

**说明**: 适用于简单的 SoC，其中每个引脚用单个寄存器配置。

## 设备树绑定

### Pinctrl 控制器节点

```dts
pinctrl: pinctrl@11002000 {
    compatible = "vendor,soc-pinctrl";
    reg = <0x11002000 0x1000>;
    #pinctrl-cells = <2>;  /* 功能, 配置 */
    
    /* 引脚组定义 */
    uart0_pins: uart0 {
        pins = <10 11>;  /* TX, RX 引脚 */
        function = <1>;  /* UART 功能 */
        drive-strength = <8>;  /* mA */
        bias-pull-up;
    };
    
    spi0_default: spi0_default {
        pins = <20 21 22 23>;  /* CLK, MOSI, MISO, CS */
        function = <2>;  /* SPI 功能 */
        drive-strength = <12>;
    };
    
    spi0_sleep: spi0_sleep {
        pins = <20 21 22 23>;
        function = <0>;  /* GPIO 功能 */
        bias-pull-down;
    };
};
```

### 消费者设备

```dts
uart0: serial@11003000 {
    compatible = "vendor,uart";
    reg = <0x11003000 0x1000>;
    
    /* 引用引脚配置 */
    pinctrl-names = "default";
    pinctrl-0 = <&uart0_pins>;
};

spi0: spi@11004000 {
    compatible = "vendor,spi";
    reg = <0x11004000 0x1000>;
    
    /* 多状态引脚配置 */
    pinctrl-names = "default", "sleep";
    pinctrl-0 = <&spi0_default>;
    pinctrl-1 = <&spi0_sleep>;
};

/* 具有 GPIO 引用的设备 */
device@11005000 {
    compatible = "vendor,device";
    reg = <0x11005000 0x1000>;
    
    reset-gpios = <&gpio 10 GPIO_ACTIVE_LOW>;
    enable-gpios = <&gpio 11 GPIO_ACTIVE_HIGH>;
};
```

### 引脚配置属性

常用的引脚配置属性：

- `bias-disable`: 禁用上拉/下拉
- `bias-pull-up`: 启用上拉
- `bias-pull-down`: 启用下拉
- `drive-strength`: 驱动强度（mA）
- `input-enable`: 启用输入缓冲器
- `output-high`: 设置输出为高电平
- `output-low`: 设置输出为低电平

## 应用层 API

### 引脚配置 API

#### rt_pin_ctrl_confs_apply

按索引应用引脚配置。

```c
rt_err_t rt_pin_ctrl_confs_apply(struct rt_device *dev, int index);
```

**参数**:
- `dev`: 设备指针
- `index`: 设备树中的配置索引（0 表示 pinctrl-0）

**返回值**:
- `RT_EOK`: 成功
- `-RT_EINVAL`: 无效参数
- `-RT_EIO`: I/O 错误

**示例**:
```c
/* 应用默认配置（pinctrl-0） */
rt_pin_ctrl_confs_apply(spi_dev, 0);

/* 应用休眠配置（pinctrl-1） */
rt_pin_ctrl_confs_apply(spi_dev, 1);
```

#### rt_pin_ctrl_confs_apply_by_name

按名称应用引脚配置。

```c
rt_err_t rt_pin_ctrl_confs_apply_by_name(struct rt_device *dev, const char *name);
```

**参数**:
- `dev`: 设备指针
- `name`: pinctrl-names 中的配置名称

**返回值**:
- `RT_EOK`: 成功
- `-RT_EINVAL`: 无效参数或未找到名称
- `-RT_EIO`: I/O 错误

**示例**:
```c
/* 在设备初始化时应用默认引脚 */
rt_pin_ctrl_confs_apply_by_name(dev, "default");

/* 在挂起前切换到低功耗引脚 */
rt_pin_ctrl_confs_apply_by_name(dev, "sleep");
```

#### rt_pin_ctrl_confs_lookup

在设备树中查找引脚配置索引。

```c
int rt_pin_ctrl_confs_lookup(struct rt_device *dev, const char *name);
```

**参数**:
- `dev`: 设备指针
- `name`: pinctrl-names 中的配置名称

**返回值**:
- `>= 0`: 配置索引
- `< 0`: 未找到错误

**示例**:
```c
int idx = rt_pin_ctrl_confs_lookup(dev, "idle");
if (idx >= 0) {
    rt_pin_ctrl_confs_apply(dev, idx);
}
```

### GPIO 辅助 API

#### rt_pin_get_named_pin

从设备树获取 GPIO 引脚编号。

```c
rt_ssize_t rt_pin_get_named_pin(struct rt_device *dev, 
                                 const char *propname,
                                 int index,
                                 rt_uint8_t *out_mode,
                                 rt_uint8_t *out_value);
```

**参数**:
- `dev`: 设备指针
- `propname`: GPIO 属性名称（如 "reset-gpios"）
- `index`: GPIO 数组中的索引（对于单个 GPIO 为 0）
- `out_mode`: 输出 GPIO 模式（可以为 NULL）
- `out_value`: 输出 GPIO 值（可以为 NULL）

**返回值**:
- `>= 0`: GPIO 引脚编号
- `< 0`: 错误

**示例**:
```c
rt_uint8_t mode, value;
rt_ssize_t pin = rt_pin_get_named_pin(dev, "reset-gpios", 0, &mode, &value);
if (pin >= 0) {
    /* 配置和使用 GPIO 引脚 */
    rt_pin_mode(pin, mode);
    rt_pin_write(pin, value);
}
```

#### rt_pin_get_named_pin_count

计算 GPIO 属性中的引脚数量。

```c
int rt_pin_get_named_pin_count(struct rt_device *dev, const char *propname);
```

**参数**:
- `dev`: 设备指针
- `propname`: GPIO 属性名称

**返回值**:
- `>= 0`: GPIO 引脚数量
- `< 0`: 错误

**示例**:
```c
int count = rt_pin_get_named_pin_count(dev, "gpios");
for (int i = 0; i < count; i++) {
    rt_ssize_t pin = rt_pin_get_named_pin(dev, "gpios", i, NULL, NULL);
    /* 使用引脚 */
}
```

## 使用示例

### SPI 驱动的引脚管理示例

```c
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/pin.h>

struct my_spi {
    struct rt_spi_bus parent;
    void *base;
    struct rt_device *dev;
    
    /* GPIO 引脚 */
    rt_ssize_t cs_pin;
    rt_ssize_t reset_pin;
};

static rt_err_t my_spi_probe(struct rt_platform_device *pdev)
{
    struct my_spi *spi;
    struct rt_device *dev = &pdev->parent;
    rt_err_t ret;
    
    spi = rt_calloc(1, sizeof(*spi));
    if (!spi)
        return -RT_ENOMEM;
    
    spi->dev = dev;
    
    /* 应用默认引脚配置 */
    ret = rt_pin_ctrl_confs_apply_by_name(dev, "default");
    if (ret) {
        rt_kprintf("Failed to apply default pinctrl: %d\n", ret);
        goto err_free;
    }
    
    /* 获取 GPIO 引脚 */
    spi->cs_pin = rt_pin_get_named_pin(dev, "cs-gpios", 0, NULL, NULL);
    if (spi->cs_pin < 0) {
        rt_kprintf("Failed to get CS GPIO\n");
        ret = spi->cs_pin;
        goto err_free;
    }
    
    spi->reset_pin = rt_pin_get_named_pin(dev, "reset-gpios", 0, NULL, NULL);
    if (spi->reset_pin >= 0) {
        /* 配置复位引脚 */
        rt_pin_mode(spi->reset_pin, PIN_MODE_OUTPUT);
        rt_pin_write(spi->reset_pin, PIN_HIGH);
    }
    
    /* 配置 CS 引脚 */
    rt_pin_mode(spi->cs_pin, PIN_MODE_OUTPUT);
    rt_pin_write(spi->cs_pin, PIN_HIGH);
    
    /* 注册 SPI 总线 */
    ret = rt_spi_bus_register(&spi->parent, "spi0", &spi_ops);
    if (ret)
        goto err_free;
    
    rt_platform_set_drvdata(pdev, spi);
    
    rt_kprintf("SPI driver probed successfully\n");
    return RT_EOK;
    
err_free:
    rt_free(spi);
    return ret;
}

static rt_err_t my_spi_remove(struct rt_platform_device *pdev)
{
    struct my_spi *spi = rt_platform_get_drvdata(pdev);
    
    /* 释放 GPIO 引脚 */
    if (spi->reset_pin >= 0) {
        rt_pin_write(spi->reset_pin, PIN_LOW);
    }
    
    rt_spi_bus_unregister(&spi->parent);
    rt_free(spi);
    
    return RT_EOK;
}

/* 电源管理钩子 */
static int my_spi_suspend(const struct rt_device *dev, rt_uint8_t mode)
{
    /* 切换到休眠引脚配置 */
    return rt_pin_ctrl_confs_apply_by_name((struct rt_device *)dev, "sleep");
}

static void my_spi_resume(const struct rt_device *dev, rt_uint8_t mode)
{
    /* 恢复默认引脚配置 */
    rt_pin_ctrl_confs_apply_by_name((struct rt_device *)dev, "default");
}

static const struct rt_device_ops spi_ops = {
    .suspend = my_spi_suspend,
    .resume = my_spi_resume,
};

static const struct rt_ofw_node_id my_spi_ids[] = {
    { .compatible = "vendor,my-spi" },
    { /* sentinel */ }
};

static struct rt_platform_driver my_spi_driver = {
    .name = "my-spi",
    .ids = my_spi_ids,
    .probe = my_spi_probe,
    .remove = my_spi_remove,
};

static int my_spi_drv_register(void)
{
    rt_platform_driver_register(&my_spi_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(my_spi_drv_register);
```

## 驱动实现指南

### Simple Pinctrl 驱动示例

```c
#include <rtthread.h>
#include <rtdevice.h>

struct simple_pinctrl {
    struct rt_device parent;
    void *base;
    rt_size_t ngroups;
};

static rt_err_t simple_pinctrl_set_mux(struct rt_pinctrl *ctrl,
                                        rt_uint32_t group,
                                        rt_uint32_t function)
{
    struct simple_pinctrl *pinctrl = rt_container_of(ctrl, struct simple_pinctrl, parent);
    void *reg = pinctrl->base + (group * 4);
    
    /* 设置功能复用 */
    rt_uint32_t val = readl(reg);
    val &= ~0xFF;
    val |= function & 0xFF;
    writel(val, reg);
    
    return RT_EOK;
}

static rt_err_t simple_pinctrl_set_config(struct rt_pinctrl *ctrl,
                                           rt_uint32_t group,
                                           rt_ubase_t config)
{
    struct simple_pinctrl *pinctrl = rt_container_of(ctrl, struct simple_pinctrl, parent);
    void *reg = pinctrl->base + (group * 4);
    rt_uint32_t param = RT_PINCTRL_CONFIG_PARAM(config);
    rt_uint32_t arg = RT_PINCTRL_CONFIG_ARG(config);
    rt_uint32_t val;
    
    val = readl(reg);
    
    switch (param) {
    case PIN_CONFIG_BIAS_DISABLE:
        val &= ~(BIT(8) | BIT(9));  /* 清除上拉/下拉 */
        break;
        
    case PIN_CONFIG_BIAS_PULL_UP:
        val |= BIT(8);
        val &= ~BIT(9);
        break;
        
    case PIN_CONFIG_BIAS_PULL_DOWN:
        val |= BIT(9);
        val &= ~BIT(8);
        break;
        
    case PIN_CONFIG_DRIVE_STRENGTH:
        val &= ~(0xF << 16);
        val |= (arg & 0xF) << 16;
        break;
        
    default:
        return -RT_EINVAL;
    }
    
    writel(val, reg);
    return RT_EOK;
}

static const struct rt_pinctrl_ops simple_pinctrl_ops = {
    .set_mux = simple_pinctrl_set_mux,
    .set_config = simple_pinctrl_set_config,
};

static rt_err_t simple_pinctrl_probe(struct rt_platform_device *pdev)
{
    struct simple_pinctrl *pinctrl;
    rt_err_t ret;
    
    pinctrl = rt_calloc(1, sizeof(*pinctrl));
    if (!pinctrl)
        return -RT_ENOMEM;
    
    /* 映射寄存器 */
    pinctrl->base = rt_dm_dev_iomap(&pdev->parent, 0);
    if (!pinctrl->base) {
        ret = -RT_EIO;
        goto err_free;
    }
    
    /* 获取引脚组数量 */
    rt_dm_dev_prop_read_u32(&pdev->parent, "pinctrl-groups", &pinctrl->ngroups);
    
    /* 注册 pinctrl 设备 */
    pinctrl->parent.ops = &simple_pinctrl_ops;
    ret = rt_pinctrl_register(&pinctrl->parent, &pdev->parent);
    if (ret)
        goto err_unmap;
    
    rt_platform_set_drvdata(pdev, pinctrl);
    
    return RT_EOK;
    
err_unmap:
    rt_dm_dev_iounmap(&pdev->parent, pinctrl->base);
err_free:
    rt_free(pinctrl);
    return ret;
}

static const struct rt_ofw_node_id simple_pinctrl_ids[] = {
    { .compatible = "simple-pinctrl" },
    { /* sentinel */ }
};

static struct rt_platform_driver simple_pinctrl_driver = {
    .name = "simple-pinctrl",
    .ids = simple_pinctrl_ids,
    .probe = simple_pinctrl_probe,
};
```

## 最佳实践

### 消费者最佳实践

1. **始终应用默认配置**
   ```c
   rt_pin_ctrl_confs_apply_by_name(dev, "default");
   ```

2. **使用命名状态进行电源管理**
   ```c
   /* 挂起 */
   rt_pin_ctrl_confs_apply_by_name(dev, "sleep");
   
   /* 恢复 */
   rt_pin_ctrl_confs_apply_by_name(dev, "default");
   ```

3. **检查 GPIO 可用性**
   ```c
   rt_ssize_t pin = rt_pin_get_named_pin(dev, "reset-gpios", 0, NULL, NULL);
   if (pin >= 0) {
       /* GPIO 可用 */
   }
   ```

4. **使用 pinctrl 进行专用功能，使用 GPIO 进行 GPIO**
   - Pinctrl：功能复用、电气配置
   - GPIO：运行时 GPIO 操作

### 提供者最佳实践

1. **支持所有相关的配置参数**
   - 上拉/下拉
   - 驱动强度
   - 输入使能
   - 其他特定于硬件的参数

2. **验证引脚组索引**
   ```c
   if (group >= pinctrl->ngroups)
       return -RT_EINVAL;
   ```

3. **实现原子配置更新**
   - 读取-修改-写入序列
   - 考虑寄存器锁定

## 故障排除

### 引脚配置失败

**症状**: rt_pin_ctrl_confs_apply 返回错误

**可能原因**:
1. 设备树中的 pinctrl 引用不正确
2. Pinctrl 驱动未加载
3. 引脚组索引超出范围

**解决方案**:
```c
/* 检查 pinctrl 引用 */
int idx = rt_pin_ctrl_confs_lookup(dev, "default");
if (idx < 0) {
    rt_kprintf("Pinctrl 'default' not found in DT\n");
}

/* 验证 pinctrl 驱动 */
if (!dev->pinctrl) {
    rt_kprintf("No pinctrl controller available\n");
}
```

### GPIO 与 Pinctrl 冲突

**症状**: GPIO 操作不起作用或引脚不响应

**可能原因**:
- 引脚复用为外设功能而不是 GPIO
- 冲突的引脚配置

**解决方案**:
```c
/* 对于 GPIO 使用，确保引脚复用为 GPIO 功能 */
/* 在设备树中或通过 pinctrl 驱动程序 */
```

### 电源管理状态切换

**症状**: 从休眠恢复后外设不工作

**可能原因**:
- 忘记恢复默认引脚状态
- 引脚状态切换顺序不正确

**解决方案**:
```c
/* 在恢复时始终恢复默认状态 */
static void my_device_resume(const struct rt_device *dev, rt_uint8_t mode)
{
    rt_pin_ctrl_confs_apply_by_name((struct rt_device *)dev, "default");
    
    /* 然后重新初始化硬件 */
}
```

## 相关模块

- **GPIO 框架**: 运行时 GPIO 操作
- **OFW (设备树)**: 设备树解析
- **电源管理**: 引脚状态用于低功耗模式
- **SCMI**: 固件引脚控制

## 参考

- `components/drivers/include/drivers/pin.h`
- `components/drivers/core/pinctrl.c`
- Linux Pinctrl 子系统文档
