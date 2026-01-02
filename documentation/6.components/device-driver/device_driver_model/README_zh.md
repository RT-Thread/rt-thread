# RT-Thread 设备驱动模型 (DM)

## 概述

RT-Thread 设备驱动模型（Device Driver Model，简称 DM）是一个全面的框架，提供了标准化的层次化方法来管理硬件设备及其驱动程序。通过 `RT_USING_DM` 配置选项启用，它引入了复杂的设备-驱动匹配机制、总线抽象以及与设备树（Open Firmware）的无缝集成。

DM 框架显著增强了 RT-Thread 处理复杂硬件系统的能力，特别是那些需要动态设备发现、电源管理、时钟控制和其他硬件资源管理的系统。

### 主要特性

- **总线-驱动-设备架构**：硬件组件的层次化组织
- **设备树集成**：完整的 Open Firmware (OFW) 支持用于硬件描述
- **动态设备管理**：运行时设备发现和驱动绑定
- **资源管理**：统一的时钟、电压调节器、复位、电源域等 API
- **平台设备模型**：内存映射和不可发现设备的抽象
- **引用计数**：安全的资源生命周期管理
- **可扩展框架**：轻松添加新的总线类型和设备类

## 架构

### 核心组件

DM 框架由几个关键组件组成：

```
┌─────────────────────────────────────────────────────────────┐
│                      应用层                                  │
│    (使用设备 API: clk, regulator, pinctrl, gpio 等)        │
└────────────────────┬────────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────────┐
│                设备驱动模型 (DM)                             │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │   总线   │  │   驱动   │  │   设备   │  │   平台   │   │
│  │  子系统  │  │  子系统  │  │  子系统  │  │   层     │   │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘   │
│                                                              │
│  ┌──────────────────────────────────────────────────────┐  │
│  │       OFW (开放固件/设备树)                          │  │
│  │  - FDT 解析  - 属性读取  - IRQ 映射                 │  │
│  └──────────────────────────────────────────────────────┘  │
└────────────────────┬────────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────────┐
│                    硬件资源                                  │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │   时钟   │  │  调节器  │  │   复位   │  │   GPIO   │   │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘   │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │ 引脚控制 │  │   DMA    │  │   中断   │  │   内存   │   │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘   │
└─────────────────────────────────────────────────────────────┘
```

#### 1. 总线子系统

总线子系统（`rt_bus`）为组织设备和驱动程序提供了基础：

- **总线注册**：总线在系统中注册并维护设备和驱动程序列表
- **设备-驱动匹配**：每个总线实现匹配函数以配对兼容的驱动程序和设备
- **探测/移除**：总线协调设备-驱动绑定的生命周期
- **锁管理**：设备和驱动程序列表的线程安全操作

**核心结构**:
```c
struct rt_bus {
    struct rt_object parent;
    const char *name;
    rt_list_t list;
    rt_list_t dev_list;      /* 此总线上的设备列表 */
    rt_list_t drv_list;      /* 此总线上的驱动程序列表 */
    rt_bool_t (*match)(rt_driver_t drv, rt_device_t dev);
    rt_err_t  (*probe)(rt_device_t dev);
    rt_err_t  (*remove)(rt_device_t dev);
    rt_err_t  (*shutdown)(rt_device_t dev);
};
```

#### 2. 驱动子系统

驱动程序实现硬件特定功能并绑定到兼容的设备：

- **驱动注册**：驱动程序向特定总线注册
- **设备操作**：标准操作（init、open、close、read、write、control）
- **探测/移除回调**：绑定到设备时的初始化和清理
- **引用计数**：跟踪活动设备绑定的数量

**核心结构**:
```c
struct rt_driver {
    struct rt_object parent;
    struct rt_bus *bus;
    rt_list_t node;
    rt_uint32_t ref_count;
    
    /* 设备操作 */
    rt_err_t  (*init)(rt_device_t dev);
    rt_err_t  (*open)(rt_device_t dev, rt_uint16_t oflag);
    rt_err_t  (*close)(rt_device_t dev);
    rt_ssize_t (*read)(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    rt_ssize_t (*write)(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    rt_err_t  (*control)(rt_device_t dev, int cmd, void *args);
    
    /* 生命周期回调 */
    int (*probe)(struct rt_device *dev);
    int (*remove)(struct rt_device *dev);
    int (*shutdown)(struct rt_device *dev);
};
```

#### 3. 平台设备模型

平台设备模型是 RT-Thread 中 DM 最常见的用法，处理内存映射设备：

- **平台总线**：用于非物理总线上设备的虚拟总线
- **设备树集成**：从 FDT 节点自动创建设备
- **资源抽象**：统一访问内存区域、中断、时钟等
- **驱动绑定**：基于 compatible 字符串的自动匹配

**核心结构**:
```c
struct rt_platform_device {
    struct rt_device parent;
    int dev_id;
    const char *name;
    const struct rt_ofw_node_id *id;
    void *priv;
};

struct rt_platform_driver {
    struct rt_driver parent;
    const char *name;
    const struct rt_ofw_node_id *ids;  /* Compatible 字符串 */
    
    rt_err_t (*probe)(struct rt_platform_device *pdev);
    rt_err_t (*remove)(struct rt_platform_device *pdev);
    rt_err_t (*shutdown)(struct rt_platform_device *pdev);
};
```

#### 4. OFW（开放固件）支持

OFW 子系统提供设备树支持：

- **FDT 解析**：扁平设备树（FDT）二进制格式解析
- **设备节点管理**：层次化设备树节点表示
- **属性读取**：读取设备树属性的 API
- **资源映射**：将 DT 资源转换为系统资源（IRQ、内存等）

### 设备生命周期

DM 框架中设备的典型生命周期：

```
     设备树              平台               驱动
         │                   │                  │
         │  解析 DT          │                  │
         ├──────────────────>│                  │
         │                   │                  │
         │  创建平台         │                  │
         │    设备           │                  │
         │                   │                  │
         │  在平台总线上     │                  │
         │  注册设备         │                  │
         │                   │                  │
         │                   │  匹配设备        │
         │                   │  与驱动          │
         │                   ├─────────────────>│
         │                   │                  │
         │                   │  驱动探测        │
         │                   │<─────────────────┤
         │                   │                  │
         │                   │  初始化硬件      │
         │                   │                  │
         │                   │  注册 API        │
         │                   │                  │
         │                   │    运行中        │
         │                   │                  │
         │                   │  驱动移除        │
         │                   ├─────────────────>│
         │                   │                  │
         │                   │  清理            │
         │                   │<─────────────────┤
         │                   │                  │
```

## Kconfig 配置

### 主 DM 选项

通过主 Kconfig 选项启用设备驱动模型：

```kconfig
config RT_USING_DM
    bool "Enable device driver model with device tree"
    default n
    help
        Enable device driver model with device tree (FDT). It will use more memory
        to parse and support device tree feature.
```

**在 menuconfig 中的位置**：`RT-Thread Components → Device Drivers → Enable device driver model with device tree`

### 相关选项

#### 设备总线
```kconfig
config RT_USING_DEV_BUS
    bool "Using Device Bus device drivers"
    default y if RT_USING_SMART
    default n
```

#### 开放固件（OFW）
```kconfig
menuconfig RT_USING_OFW
    bool "Using Open Firmware (OFW)"
    select RT_USING_ADT
    select RT_USING_ADT_REF
    select RT_USING_ADT_BITMAP
    select RT_USING_MEMBLOCK
    depends on RT_USING_DM
    default n
```

**位置**：`RT-Thread Components → Device Drivers → Using Open Firmware (OFW)`

#### 内置 FDT
```kconfig
config RT_USING_BUILTIN_FDT
    bool "Using builtin fdt in kernel"
    depends on RT_USING_OFW
    default n

config RT_BUILTIN_FDT_PATH
    string "Builtin fdt path, will rebuild if have dts"
    depends on RT_USING_BUILTIN_FDT
    default "rtthread.dtb"
```

## 设备树集成

### 设备树基础

当启用 `RT_USING_DM` 和 `RT_USING_OFW` 时，RT-Thread 可以解析和使用设备树（FDT）来描述硬件：

#### 设备树节点示例

```dts
/ {
    compatible = "myboard,example";
    #address-cells = <1>;
    #size-cells = <1>;
    
    clocks {
        osc24M: osc24M_clk {
            #clock-cells = <0>;
            compatible = "fixed-clock";
            clock-frequency = <24000000>;
            clock-output-names = "osc24M";
        };
    };
    
    soc {
        compatible = "simple-bus";
        #address-cells = <1>;
        #size-cells = <1>;
        ranges;
        
        uart0: serial@10000000 {
            compatible = "myvendor,uart";
            reg = <0x10000000 0x1000>;
            interrupts = <32>;
            clocks = <&osc24M>;
            clock-names = "baudclk";
            status = "okay";
        };
    };
    
    regulators {
        vcc_3v3: regulator-vcc-3v3 {
            compatible = "regulator-fixed";
            regulator-name = "vcc-3v3";
            regulator-min-microvolt = <3300000>;
            regulator-max-microvolt = <3300000>;
            regulator-always-on;
            regulator-boot-on;
        };
    };
};
```

### 在驱动中使用设备树

#### 获取设备节点

```c
#include <drivers/ofw.h>

struct rt_ofw_node *np = dev->ofw_node;
```

#### 读取属性

```c
/* 读取字符串属性 */
const char *status;
rt_ofw_prop_read_string(np, "status", &status);

/* 读取 u32 属性 */
rt_uint32_t freq;
rt_ofw_prop_read_u32(np, "clock-frequency", &freq);

/* 读取数组 */
rt_uint32_t reg[2];
rt_ofw_prop_read_u32_array(np, "reg", reg, 2);
```

#### 获取资源

```c
/* 获取内存资源 */
rt_uint64_t addr, size;
rt_dm_dev_get_address(dev, 0, &addr, &size);

/* 获取 IRQ */
int irq = rt_dm_dev_get_irq(dev, 0);

/* 映射 MMIO */
void *base = rt_dm_dev_iomap(dev, 0);

/* 获取时钟 */
struct rt_clk *clk = rt_clk_get_by_name(dev, "baudclk");
```

## DM 依赖模块

设备驱动模型支持众多硬件子系统。每个模块为应用层和驱动实现提供标准化的 API：

| 模块 | 描述 | 文档 |
|------|------|------|
| **clk** | 时钟管理框架 | [clk.md](clk/README_zh.md) |
| **regulator** | 电压/电流调节 | [regulator.md](regulator/README_zh.md) |
| **pinctrl** | 引脚复用和配置 | [pinctrl.md](pinctrl/README_zh.md) |
| **reset** | 复位控制器管理 | [reset.md](reset/README_zh.md) |
| **pmdomain** | 电源域管理 | [pmdomain.md](pmdomain/README_zh.md) |
| **pic** | 平台中断控制器 | [pic.md](pic/README_zh.md) |
| **nvmem** | 非易失性内存框架 | [nvmem.md](nvmem/README_zh.md) |
| **mailbox** | 邮箱/门铃通信 | [mailbox.md](mailbox/README_zh.md) |
| **thermal** | 热管理 | [thermal.md](thermal/README_zh.md) |
| **mfd** | 多功能设备 | [mfd.md](mfd/README_zh.md) |
| **dma** | DMA 引擎管理 | [dma.md](dma/README_zh.md) |
| **iio** | 工业 I/O 子系统 | [iio.md](iio/README_zh.md) |
| **phy** | PHY（物理层）框架 | [phy.md](phy/README_zh.md) |
| **phye** | 以太网 PHY 框架 | [phye.md](phye/README_zh.md) |
| **pci** | PCI 总线支持 | [pci.md](pci/README_zh.md) |
| **ofw** | 开放固件/设备树 | [ofw.md](ofw/README_zh.md) |

## 常用 API

### 设备管理

```c
/* 通过 master_id 和 device_id 查找设备 */
rt_device_t rt_dm_device_find(int master_id, int device_id);

/* 设置设备名称 */
int rt_dm_dev_set_name(rt_device_t dev, const char *format, ...);
int rt_dm_dev_set_name_auto(rt_device_t dev, const char *prefix);

/* 获取设备名称 */
const char *rt_dm_dev_get_name(rt_device_t dev);
int rt_dm_dev_get_name_id(rt_device_t dev);
```

### 设备树 API

```c
/* 获取地址资源 */
int rt_dm_dev_get_address_count(rt_device_t dev);
rt_err_t rt_dm_dev_get_address(rt_device_t dev, int index,
                               rt_uint64_t *out_address, rt_uint64_t *out_size);
rt_err_t rt_dm_dev_get_address_by_name(rt_device_t dev, const char *name,
                                       rt_uint64_t *out_address, rt_uint64_t *out_size);

/* 映射 MMIO 区域 */
void *rt_dm_dev_iomap(rt_device_t dev, int index);
void *rt_dm_dev_iomap_by_name(rt_device_t dev, const char *name);

/* 获取 IRQ 资源 */
int rt_dm_dev_get_irq_count(rt_device_t dev);
int rt_dm_dev_get_irq(rt_device_t dev, int index);
int rt_dm_dev_get_irq_by_name(rt_device_t dev, const char *name);
```

### 属性读取

```c
/* 读取各种属性类型 */
int rt_dm_dev_prop_read_u8_array_index(rt_device_t dev, const char *propname,
                                       int index, int nr, rt_uint8_t *out_values);
int rt_dm_dev_prop_read_u32_array_index(rt_device_t dev, const char *propname,
                                        int index, int nr, rt_uint32_t *out_values);
int rt_dm_dev_prop_read_string_index(rt_device_t dev, const char *propname,
                                     int index, const char **out_string);

/* 简化的单值读取 */
#define rt_dm_dev_prop_read_u32(dev, propname, out_value) \
    rt_dm_dev_prop_read_u32_array_index(dev, propname, 0, 1, out_value)
```

### 平台设备 API

```c
/* 注册平台驱动 */
rt_err_t rt_platform_driver_register(struct rt_platform_driver *pdrv);

/* 注册平台设备 */
rt_err_t rt_platform_device_register(struct rt_platform_device *pdev);

/* 从设备树创建平台设备 */
rt_err_t rt_platform_ofw_device_probe_child(struct rt_ofw_node *np);
```

## 编写平台驱动

### 基本驱动结构

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/ofw.h>

struct mydevice_data {
    void *base;
    int irq;
    struct rt_clk *clk;
};

static rt_err_t mydevice_probe(struct rt_platform_device *pdev)
{
    struct mydevice_data *data;
    struct rt_device *dev = &pdev->parent;
    
    /* 分配私有数据 */
    data = rt_calloc(1, sizeof(*data));
    if (!data)
        return -RT_ENOMEM;
    
    /* 映射 MMIO 区域 */
    data->base = rt_dm_dev_iomap(dev, 0);
    if (!data->base) {
        rt_free(data);
        return -RT_ERROR;
    }
    
    /* 获取 IRQ */
    data->irq = rt_dm_dev_get_irq(dev, 0);
    
    /* 获取时钟 */
    data->clk = rt_clk_get_by_name(dev, "baudclk");
    if (data->clk) {
        rt_clk_prepare_enable(data->clk);
    }
    
    /* 存储私有数据 */
    pdev->priv = data;
    
    /* 初始化硬件 */
    /* ... */
    
    return RT_EOK;
}

static rt_err_t mydevice_remove(struct rt_platform_device *pdev)
{
    struct mydevice_data *data = pdev->priv;
    
    /* 清理硬件 */
    /* ... */
    
    /* 释放资源 */
    if (data->clk) {
        rt_clk_disable_unprepare(data->clk);
        rt_clk_put(data->clk);
    }
    
    rt_free(data);
    
    return RT_EOK;
}

static const struct rt_ofw_node_id mydevice_ofw_ids[] = {
    { .compatible = "myvendor,mydevice" },
    { /* sentinel */ }
};

static struct rt_platform_driver mydevice_driver = {
    .name = "mydevice",
    .ids = mydevice_ofw_ids,
    .probe = mydevice_probe,
    .remove = mydevice_remove,
};

/* 启动时自动注册驱动 */
RT_PLATFORM_DRIVER_EXPORT(mydevice_driver);
```

### 设备树绑定

```dts
mydev: mydevice@10000000 {
    compatible = "myvendor,mydevice";
    reg = <0x10000000 0x1000>;
    interrupts = <32>;
    clocks = <&osc24M>;
    clock-names = "baudclk";
    status = "okay";
};
```

## 最佳实践

### 1. 资源管理

- 获取资源时始终检查返回值
- 对共享资源（时钟、调节器）使用引用计数
- 在移除回调中清理资源
- 处理依赖项的探测延迟

### 2. 设备树

- 尽可能使用标准绑定
- 在驱动文档中记录自定义属性
- 使用标签进行 phandle 引用
- 保持设备树和驱动同步

### 3. 错误处理

```c
static rt_err_t mydevice_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct mydevice_data *data;
    
    data = rt_calloc(1, sizeof(*data));
    if (!data)
        return -RT_ENOMEM;
    
    data->base = rt_dm_dev_iomap(&pdev->parent, 0);
    if (!data->base) {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    data->clk = rt_clk_get_by_name(&pdev->parent, "baudclk");
    if (!data->clk) {
        ret = -RT_ERROR;
        goto err_unmap;
    }
    
    ret = rt_clk_prepare_enable(data->clk);
    if (ret)
        goto err_put_clk;
    
    /* 成功 */
    pdev->priv = data;
    return RT_EOK;
    
err_put_clk:
    rt_clk_put(data->clk);
err_unmap:
    rt_iounmap(data->base);
err_free:
    rt_free(data);
    return ret;
}
```

### 4. 线程安全

- 对硬件寄存器访问使用自旋锁
- 对长操作使用互斥锁
- 在 ISR 中考虑中断上下文
- 保护共享数据结构

## 性能考虑

### 内存使用

DM 增加了内存开销：
- 设备树解析需要 FDT 和节点结构的内存
- 每个设备/驱动添加对象开销
- 资源管理的额外元数据

**建议**：
- 仅为需要它的系统启用 DM
- 设计设备树时考虑内存限制
- 尽可能使用静态分配

### 启动时间

- 设备树解析在启动早期进行
- 驱动探测可以延迟
- 尽可能并行初始化

## 调试

### 启用调试输出

```c
#define DBG_TAG "mydriver"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

LOG_D("调试消息");
LOG_I("信息消息");
LOG_W("警告消息");
LOG_E("错误消息");
```

### DM 特定调试

```
/* 在 menuconfig 中启用 OFW 调试 */
RT-Thread Components → Device Drivers → Using Open Firmware (OFW)
```

### 常见问题

1. **设备未探测**：检查 compatible 字符串是否匹配
2. **资源未找到**：验证设备树属性
3. **探测延迟循环**：检查循环依赖
4. **内存访问错误**：验证 MMIO 映射正确

## 迁移指南

### 从传统 RT-Thread 驱动

传统 RT-Thread 驱动：
```c
rt_device_t dev = rt_device_find("uart0");
rt_device_open(dev, RT_DEVICE_OFLAG_RDWR);
```

使用 DM：
```c
/* 设备从设备树自动创建 */
rt_device_t dev = rt_device_find("uart0");
rt_device_open(dev, RT_DEVICE_OFLAG_RDWR);
/* 用户 API 保持不变 */
```

驱动实现变化：
- 添加平台驱动结构
- 实现探测/移除回调
- 使用 DM API 进行资源管理
- 添加设备树绑定

## 相关文档

- [开放固件（OFW）文档](../ofw/dtc.md)
- [设备框架](../framework/device.md)
- 有关模块特定文档，请参阅 DM 依赖模块部分中的链接

## 参考资料

- [设备树规范](https://devicetree-specification.readthedocs.io/)
- [Linux 内核驱动模型](https://www.kernel.org/doc/html/latest/driver-api/driver-model/index.html)
- RT-Thread 源代码：`components/drivers/core/`、`components/drivers/ofw/`
