# 复位控制器框架

## 简介

RT-Thread 的复位控制器框架为嵌入式系统中的硬件复位信号管理提供了标准化接口。复位控制器对于正确初始化、恢复和管理硬件外设及子系统的状态至关重要。

### 概述

复位信号对硬件管理至关重要：

- **设备初始化**：在启动期间将设备置于已知状态
- **错误恢复**：发生错误时复位设备
- **电源管理**：进入/退出低功耗模式时复位设备
- **热插拔支持**：为热插拔场景重新初始化设备
- **系统稳定性**：确保干净的状态转换

常见的复位控制器类型包括：
- **基于寄存器**：单个寄存器控制多个复位
- **基于 GPIO**：通过 GPIO 引脚控制的复位线
- **电源管理 IC (PMIC)**：集成在电源管理芯片中的复位
- **系统控制**：通过系统控制接口（SCMI）管理的复位

### RT-Thread 实现

RT-Thread 复位控制器框架位于 `components/drivers/reset/`，提供：

1. **消费者 API**：设备驱动程序控制复位线的简单接口
2. **提供者 API**：实现复位控制器驱动程序的框架
3. **设备树集成**：从 FDT 自动配置
4. **复位操作**：断言、解除断言和脉冲复位信号
5. **数组支持**：管理设备的多条复位线
6. **状态查询**：检查复位线状态

## Kconfig 配置

### 主配置

```kconfig
menuconfig RT_USING_RESET
    bool "Using Reset Controller support"
    depends on RT_USING_DM
    depends on RT_USING_OFW
    default n
```

**在 menuconfig 中的位置**：
```
RT-Thread Components → Device Drivers → Using Reset Controller support
```

**依赖项**：
- `RT_USING_DM`：必须首先启用
- `RT_USING_OFW`：需要设备树支持

**默认值**：禁用（选择加入功能）

### 复位驱动选项

#### SCMI 复位驱动
```kconfig
config RT_RESET_SCMI
    bool "Reset driver controlled via ARM SCMI interface"
    depends on RT_USING_RESET
    depends on RT_FIRMWARE_ARM_SCMI
    default n
```

支持通过 ARM 系统控制和管理接口（SCMI）控制的复位控制器。

#### 简单复位驱动
```kconfig
config RT_RESET_SIMPLE
    bool "Simple Reset Controller Driver"
    depends on RT_USING_RESET
    default n
```

支持基本的基于寄存器的复位控制器，具有简单的位操作。

## 设备树绑定

### 复位控制器属性

复位控制器使用以下方式导出复位：

```dts
#reset-cells = <n>;              /* 复位说明符中的单元数 */
```

单元数通常表示标识特定复位线所需的值数量（通常为 1）。

### 复位消费者属性

设备使用以下方式引用复位线：

```dts
resets = <&rstc idx>;            /* 复位控制器 phandle 和索引 */
reset-names = "name";            /* 复位线名称 */
```

### 简单复位控制器示例

```dts
soc {
    /* 复位控制器节点 */
    rstc: reset-controller@1c20000 {
        compatible = "vendor,reset-controller", "reset-simple";
        reg = <0x1c20000 0x100>;
        #reset-cells = <1>;
    };
};
```

### 消费者使用示例

```dts
/* 单复位消费者 */
uart0: serial@1c28000 {
    compatible = "vendor,uart";
    reg = <0x1c28000 0x400>;
    interrupts = <0 0 4>;
    
    clocks = <&ccu 64>;
    resets = <&rstc 32>;         /* 复位索引 32 */
    reset-names = "uart";
    
    status = "okay";
};

/* 多复位消费者 */
usb0: usb@1c19000 {
    compatible = "vendor,usb-otg";
    reg = <0x1c19000 0x1000>;
    interrupts = <0 32 4>;
    
    clocks = <&ccu 24>, <&ccu 25>;
    clock-names = "ahb", "otg";
    
    resets = <&rstc 11>, <&rstc 12>;
    reset-names = "ahb", "phy";
    
    status = "okay";
};
```

## 应用层 API

### 概述

消费者 API 为设备驱动程序提供简单的函数来控制复位线。复位操作通常在设备初始化和错误恢复期间执行。

### 获取和释放复位控制

#### rt_reset_control_get_by_name

```c
struct rt_reset_control *rt_reset_control_get_by_name(struct rt_device *dev, 
                                                       const char *name);
```

通过名称获取复位控制。

**参数**：
- `dev`：设备结构指针
- `name`：复位线名称（匹配设备树中的 `reset-names`）

**返回值**：
- 成功时返回复位控制指针
- 失败时返回 NULL

**示例**：
```c
struct rt_reset_control *rst;

/* 获取 "phy" 复位线 */
rst = rt_reset_control_get_by_name(dev, "phy");
if (!rst) {
    LOG_W("没有 phy 复位线");
    /* 不致命 - 某些板可能没有 */
}
```

#### rt_reset_control_get_by_index

```c
struct rt_reset_control *rt_reset_control_get_by_index(struct rt_device *dev, 
                                                        int index);
```

通过索引获取复位控制。

**参数**：
- `dev`：设备结构指针
- `index`：`resets` 属性中的复位索引（从 0 开始）

**返回值**：
- 成功时返回复位控制指针
- 失败时返回 NULL

#### rt_reset_control_get_array

```c
struct rt_reset_control *rt_reset_control_get_array(struct rt_device *dev);
```

获取设备的所有复位控制作为数组。

**参数**：
- `dev`：设备结构指针

**返回值**：
- 成功时返回复位控制数组指针
- 失败时返回 NULL

#### rt_reset_control_put

```c
void rt_reset_control_put(struct rt_reset_control *rstc);
```

释放复位控制。

**参数**：
- `rstc`：复位控制指针

### 复位操作

#### rt_reset_control_reset

```c
rt_err_t rt_reset_control_reset(struct rt_reset_control *rstc);
```

执行复位脉冲：断言然后解除断言。

**参数**：
- `rstc`：复位控制指针

**返回值**：
- 成功时返回 `RT_EOK`
- 失败时返回错误代码

**注意**：
- 这是最常见的操作
- 自动断言然后以适当的延迟解除断言
- 即使复位控制为 NULL 也安全调用

**示例**：
```c
/* 在初始化期间复位外设 */
ret = rt_reset_control_reset(rst);
if (ret != RT_EOK) {
    LOG_E("复位外设失败: %d", ret);
    return ret;
}

/* 等待硬件稳定 */
rt_thread_mdelay(10);
```

#### rt_reset_control_assert

```c
rt_err_t rt_reset_control_assert(struct rt_reset_control *rstc);
```

断言（激活）复位信号。

**参数**：
- `rstc`：复位控制指针

**返回值**：
- 成功时返回 `RT_EOK`
- 失败时返回错误代码

**注意**：
- 将设备置于复位状态
- 必须跟随解除断言以恢复操作
- 即使复位控制为 NULL 也安全调用

**示例**：
```c
/* 在断电前将设备置于复位状态 */
rt_reset_control_assert(rst);
```

#### rt_reset_control_deassert

```c
rt_err_t rt_reset_control_deassert(struct rt_reset_control *rstc);
```

解除断言（停用）复位信号。

**参数**：
- `rstc`：复位控制指针

**返回值**：
- 成功时返回 `RT_EOK`
- 失败时返回错误代码

**注意**：
- 将设备从复位状态中取出
- 应在断言之后调用
- 即使复位控制为 NULL 也安全调用

**示例**：
```c
/* 将设备从复位中取出 */
rt_reset_control_deassert(rst);

/* 等待硬件准备好 */
rt_thread_mdelay(1);
```

#### rt_reset_control_status

```c
int rt_reset_control_status(struct rt_reset_control *rstc);
```

获取复位线的当前状态。

**参数**：
- `rstc`：复位控制指针

**返回值**：
- 如果已断言（处于复位状态）返回 1
- 如果已解除断言（不处于复位状态）返回 0
- 失败时返回负错误代码

## 完整应用示例

### 示例：带复位控制的 USB 驱动

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/clk.h>
#include <drivers/reset.h>

struct usb_device {
    void *base;
    int irq;
    struct rt_clk *ahb_clk;
    struct rt_clk *otg_clk;
    struct rt_reset_control *ahb_rst;
    struct rt_reset_control *phy_rst;
};

static rt_err_t usb_hw_init(struct usb_device *usb)
{
    rt_err_t ret;
    
    /* 首先启用时钟 */
    ret = rt_clk_prepare_enable(usb->ahb_clk);
    if (ret != RT_EOK) {
        LOG_E("启用 AHB 时钟失败: %d", ret);
        return ret;
    }
    
    ret = rt_clk_prepare_enable(usb->otg_clk);
    if (ret != RT_EOK) {
        LOG_E("启用 OTG 时钟失败: %d", ret);
        goto err_disable_ahb;
    }
    
    /* 启用时钟后解除断言复位 */
    ret = rt_reset_control_deassert(usb->ahb_rst);
    if (ret != RT_EOK) {
        LOG_E("解除断言 AHB 复位失败: %d", ret);
        goto err_disable_otg;
    }
    
    ret = rt_reset_control_deassert(usb->phy_rst);
    if (ret != RT_EOK) {
        LOG_E("解除断言 PHY 复位失败: %d", ret);
        goto err_assert_ahb;
    }
    
    /* 等待硬件稳定 */
    rt_thread_mdelay(10);
    
    return RT_EOK;
    
err_assert_ahb:
    rt_reset_control_assert(usb->ahb_rst);
err_disable_otg:
    rt_clk_disable_unprepare(usb->otg_clk);
err_disable_ahb:
    rt_clk_disable_unprepare(usb->ahb_clk);
    return ret;
}

static void usb_hw_deinit(struct usb_device *usb)
{
    /* 在禁用时钟之前断言复位 */
    rt_reset_control_assert(usb->phy_rst);
    rt_reset_control_assert(usb->ahb_rst);
    
    /* 禁用时钟 */
    rt_clk_disable_unprepare(usb->otg_clk);
    rt_clk_disable_unprepare(usb->ahb_clk);
}

static rt_err_t usb_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct usb_device *usb;
    
    /* 分配设备结构 */
    usb = rt_calloc(1, sizeof(*usb));
    if (!usb)
        return -RT_ENOMEM;
    
    /* 映射 MMIO 区域 */
    usb->base = rt_dm_dev_iomap(dev, 0);
    if (!usb->base) {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* 获取 IRQ */
    usb->irq = rt_dm_dev_get_irq(dev, 0);
    
    /* 获取时钟 */
    usb->ahb_clk = rt_clk_get_by_name(dev, "ahb");
    if (!usb->ahb_clk) {
        LOG_E("获取 AHB 时钟失败");
        ret = -RT_ERROR;
        goto err_unmap;
    }
    
    usb->otg_clk = rt_clk_get_by_name(dev, "otg");
    if (!usb->otg_clk) {
        LOG_E("获取 OTG 时钟失败");
        ret = -RT_ERROR;
        goto err_put_ahb_clk;
    }
    
    /* 获取复位 */
    usb->ahb_rst = rt_reset_control_get_by_name(dev, "ahb");
    if (!usb->ahb_rst) {
        LOG_W("没有 AHB 复位线");
        /* 不致命 - 某些平台可能没有 */
    }
    
    usb->phy_rst = rt_reset_control_get_by_name(dev, "phy");
    if (!usb->phy_rst) {
        LOG_W("没有 PHY 复位线");
        /* 不致命 */
    }
    
    /* 初始化硬件 */
    ret = usb_hw_init(usb);
    if (ret != RT_EOK) {
        goto err_put_resets;
    }
    
    pdev->priv = usb;
    LOG_I("USB 设备已初始化");
    
    return RT_EOK;
    
err_put_resets:
    if (usb->phy_rst)
        rt_reset_control_put(usb->phy_rst);
    if (usb->ahb_rst)
        rt_reset_control_put(usb->ahb_rst);
    rt_clk_put(usb->otg_clk);
err_put_ahb_clk:
    rt_clk_put(usb->ahb_clk);
err_unmap:
    rt_iounmap(usb->base);
err_free:
    rt_free(usb);
    return ret;
}
```

## 驱动实现指南

### 核心结构

#### rt_reset_control_ops

```c
struct rt_reset_control_ops {
    /* 解析设备树参数 */
    rt_err_t (*ofw_parse)(struct rt_reset_control *rstc, 
                         struct rt_ofw_cell_args *args);
    
    /* 复位操作 */
    rt_err_t (*reset)(struct rt_reset_control *rstc);
    rt_err_t (*assert)(struct rt_reset_control *rstc);
    rt_err_t (*deassert)(struct rt_reset_control *rstc);
    int      (*status)(struct rt_reset_control *rstc);
};
```

### 示例：简单复位控制器驱动

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/reset.h>

#define RESET_ASSERT   0x0
#define RESET_DEASSERT 0x4
#define RESET_STATUS   0x8

struct simple_reset {
    struct rt_reset_controller rstcer;
    void *base;
    rt_uint32_t nr_resets;
};

static rt_err_t simple_reset_ofw_parse(struct rt_reset_control *rstc,
                                       struct rt_ofw_cell_args *args)
{
    /* args->args[0] 包含复位索引 */
    if (args->args_count != 1) {
        return -RT_EINVAL;
    }
    
    rstc->id = args->args[0];
    return RT_EOK;
}

static rt_err_t simple_reset_assert(struct rt_reset_control *rstc)
{
    struct simple_reset *sr = rstc->rstcer->priv;
    rt_uint32_t mask = RT_BIT(rstc->id);
    
    /* 设置位以断言复位 */
    writel(readl(sr->base + RESET_ASSERT) | mask, 
           sr->base + RESET_ASSERT);
    
    return RT_EOK;
}

static rt_err_t simple_reset_deassert(struct rt_reset_control *rstc)
{
    struct simple_reset *sr = rstc->rstcer->priv;
    rt_uint32_t mask = RT_BIT(rstc->id);
    
    /* 设置位以解除断言复位 */
    writel(readl(sr->base + RESET_DEASSERT) | mask,
           sr->base + RESET_DEASSERT);
    
    return RT_EOK;
}

static int simple_reset_status(struct rt_reset_control *rstc)
{
    struct simple_reset *sr = rstc->rstcer->priv;
    rt_uint32_t status = readl(sr->base + RESET_STATUS);
    
    /* 如果处于复位状态返回 1，否则返回 0 */
    return !!(status & RT_BIT(rstc->id));
}

static const struct rt_reset_control_ops simple_reset_ops = {
    .ofw_parse = simple_reset_ofw_parse,
    .assert = simple_reset_assert,
    .deassert = simple_reset_deassert,
    .status = simple_reset_status,
};

static rt_err_t simple_reset_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    rt_uint32_t nr_resets;
    struct rt_device *dev = &pdev->parent;
    struct simple_reset *sr;
    
    /* 分配驱动结构 */
    sr = rt_calloc(1, sizeof(*sr));
    if (!sr)
        return -RT_ENOMEM;
    
    /* 映射复位控制器寄存器 */
    sr->base = rt_dm_dev_iomap(dev, 0);
    if (!sr->base) {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* 获取复位线数量 */
    if (rt_dm_dev_prop_read_u32(dev, "reset-count", &nr_resets)) {
        nr_resets = 32;  /* 默认值 */
    }
    sr->nr_resets = nr_resets;
    
    /* 初始化复位控制器 */
    sr->rstcer.ops = &simple_reset_ops;
    sr->rstcer.ofw_node = dev->ofw_node;
    sr->rstcer.priv = sr;
    
    /* 向框架注册 */
    ret = rt_reset_controller_register(&sr->rstcer);
    if (ret != RT_EOK) {
        LOG_E("注册复位控制器失败: %d", ret);
        goto err_unmap;
    }
    
    pdev->priv = sr;
    LOG_I("简单复位控制器已注册: %u 线", nr_resets);
    
    return RT_EOK;
    
err_unmap:
    rt_iounmap(sr->base);
err_free:
    rt_free(sr);
    return ret;
}

static const struct rt_ofw_node_id simple_reset_ofw_ids[] = {
    { .compatible = "simple-reset" },
    { /* sentinel */ }
};

static struct rt_platform_driver simple_reset_driver = {
    .name = "simple-reset",
    .ids = simple_reset_ofw_ids,
    .probe = simple_reset_probe,
};

static int simple_reset_drv_register(void)
{
    rt_platform_driver_register(&simple_reset_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(simple_reset_drv_register);
```

## 最佳实践

### 对于消费者驱动程序

1. **检查返回值**：复位操作可能失败
2. **顺序很重要**：在解除断言复位之前启用时钟
3. **处理缺失的复位**：并非所有平台都有复位线（检查 NULL）
4. **复位后等待**：让硬件有时间稳定
5. **错误时复位**：使用复位进行错误恢复
6. **断电前断言**：在禁用电源之前将设备置于复位状态

### 常见模式

#### 初始化序列

```c
/* 正确的初始化顺序 */
rt_clk_prepare_enable(clk);          /* 1. 启用时钟 */
rt_reset_control_deassert(rst);      /* 2. 从复位中取出 */
rt_thread_mdelay(10);                 /* 3. 等待稳定 */
/* 初始化硬件寄存器 */
```

#### 清理序列

```c
/* 正确的清理顺序（初始化的相反顺序）*/
/* 禁用硬件 */
rt_reset_control_assert(rst);         /* 1. 置于复位状态 */
rt_clk_disable_unprepare(clk);        /* 2. 禁用时钟 */
```

#### 错误恢复

```c
/* 发生错误时复位设备 */
if (device_error_detected()) {
    rt_reset_control_reset(rst);      /* 脉冲复位 */
    rt_thread_mdelay(10);
    reinitialize_device();
}
```

## 故障排除

### 常见问题

1. **找不到复位**
   - 检查设备树：确保 `resets` 和 `reset-names` 属性存在
   - 检查 compatible 字符串：验证复位驱动已加载
   - 检查 Kconfig：启用复位控制器支持

2. **复位后设备不工作**
   - 检查时钟顺序：解除断言前必须启用时钟
   - 检查延迟：复位后添加延迟以便硬件稳定
   - 检查复位极性：验证断言/解除断言是否正确

3. **复位期间系统挂起**
   - 检查时钟状态：设备时钟必须运行
   - 检查依赖关系：某些复位依赖于其他复位
   - 检查电源：设备电源必须打开

## 性能考虑

### 内存使用

- 每个复位控制器：约 100 字节
- 每个复位控制：约 40 字节
- 开销最小

### 时序

- 复位操作：通常很快（寄存器写入）
- 可能需要延迟：用于硬件稳定
- 无复杂计算

## 相关模块

- **clk**：时钟管理，与复位协调
- **regulator**：电源，与复位协调
- **pinctrl**：引脚配置，复位后可能需要
- **pmdomain**：电源域，更高级别的控制

## 参考资料

- RT-Thread 源代码：`components/drivers/reset/`
- 头文件：`components/drivers/include/drivers/reset.h`
- 设备树绑定：[Linux Reset Bindings](https://www.kernel.org/doc/Documentation/devicetree/bindings/reset/)
- [RT-Thread DM 文档](../README_zh.md)
