# RT-Thread Device Driver Model (DM)

## Overview

The RT-Thread Device Driver Model (DM) is a comprehensive framework that provides a standardized, hierarchical approach to managing hardware devices and their drivers. Enabled through the `RT_USING_DM` configuration option, it introduces a sophisticated device-driver matching mechanism, bus abstraction, and seamless integration with device tree (Open Firmware) support.

The DM framework significantly enhances RT-Thread's capability to handle complex hardware systems, particularly those requiring dynamic device discovery, power management, clock control, and other hardware resource management.

### Key Features

- **Bus-Driver-Device Architecture**: Hierarchical organization of hardware components
- **Device Tree Integration**: Full Open Firmware (OFW) support for hardware description
- **Dynamic Device Management**: Runtime device discovery and driver binding
- **Resource Management**: Unified APIs for clocks, regulators, resets, power domains, etc.
- **Platform Device Model**: Abstraction for memory-mapped and non-discoverable devices
- **Reference Counting**: Safe resource lifecycle management
- **Extensible Framework**: Easy addition of new bus types and device classes

## Architecture

### Core Components

The DM framework consists of several key components:

```
┌─────────────────────────────────────────────────────────────┐
│                    Application Layer                         │
│  (Uses device APIs: clk, regulator, pinctrl, gpio, etc.)   │
└────────────────────┬────────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────────┐
│                Device Driver Model (DM)                      │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │   Bus    │  │  Driver  │  │  Device  │  │ Platform │   │
│  │ Subsys   │  │ Subsys   │  │ Subsys   │  │  Layer   │   │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘   │
│                                                              │
│  ┌──────────────────────────────────────────────────────┐  │
│  │        OFW (Open Firmware/Device Tree)               │  │
│  │  - FDT parsing  - Property reading  - IRQ mapping   │  │
│  └──────────────────────────────────────────────────────┘  │
└────────────────────┬────────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────────┐
│                Hardware Resources                            │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │  Clocks  │  │Regulator │  │  Resets  │  │  GPIOs   │   │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘   │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │ Pinctrl  │  │   DMA    │  │   IRQs   │  │  Memory  │   │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘   │
└─────────────────────────────────────────────────────────────┘
```

#### 1. Bus Subsystem

The bus subsystem (`rt_bus`) provides the foundation for organizing devices and drivers:

- **Bus Registration**: Buses are registered with the system and maintain lists of devices and drivers
- **Device-Driver Matching**: Each bus implements a match function to pair compatible drivers with devices
- **Probe/Remove**: Buses coordinate the lifecycle of device-driver bindings
- **Lock Management**: Thread-safe operations on device and driver lists

**Key Structures**:
```c
struct rt_bus {
    struct rt_object parent;
    const char *name;
    rt_list_t list;
    rt_list_t dev_list;      /* List of devices on this bus */
    rt_list_t drv_list;      /* List of drivers on this bus */
    rt_bool_t (*match)(rt_driver_t drv, rt_device_t dev);
    rt_err_t  (*probe)(rt_device_t dev);
    rt_err_t  (*remove)(rt_device_t dev);
    rt_err_t  (*shutdown)(rt_device_t dev);
};
```

#### 2. Driver Subsystem

Drivers implement hardware-specific functionality and are bound to compatible devices:

- **Driver Registration**: Drivers register with a specific bus
- **Device Operations**: Standard operations (init, open, close, read, write, control)
- **Probe/Remove Callbacks**: Initialization and cleanup when bound to devices
- **Reference Counting**: Tracks the number of active device bindings

**Key Structures**:
```c
struct rt_driver {
    struct rt_object parent;
    struct rt_bus *bus;
    rt_list_t node;
    rt_uint32_t ref_count;
    
    /* Device operations */
    rt_err_t  (*init)(rt_device_t dev);
    rt_err_t  (*open)(rt_device_t dev, rt_uint16_t oflag);
    rt_err_t  (*close)(rt_device_t dev);
    rt_ssize_t (*read)(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    rt_ssize_t (*write)(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    rt_err_t  (*control)(rt_device_t dev, int cmd, void *args);
    
    /* Lifecycle callbacks */
    int (*probe)(struct rt_device *dev);
    int (*remove)(struct rt_device *dev);
    int (*shutdown)(struct rt_device *dev);
};
```

#### 3. Platform Device Model

The platform device model is the most common usage of DM in RT-Thread, handling memory-mapped devices:

- **Platform Bus**: A virtual bus for devices not on a physical bus
- **Device Tree Integration**: Automatic device creation from FDT nodes
- **Resource Abstraction**: Unified access to memory regions, IRQs, clocks, etc.
- **Driver Binding**: Automatic matching based on compatible strings

**Key Structures**:
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
    const struct rt_ofw_node_id *ids;  /* Compatible strings */
    
    rt_err_t (*probe)(struct rt_platform_device *pdev);
    rt_err_t (*remove)(struct rt_platform_device *pdev);
    rt_err_t (*shutdown)(struct rt_platform_device *pdev);
};
```

#### 4. OFW (Open Firmware) Support

The OFW subsystem provides device tree support:

- **FDT Parsing**: Flattened Device Tree (FDT) binary format parsing
- **Device Node Management**: Hierarchical device tree node representation
- **Property Reading**: APIs to read device tree properties
- **Resource Mapping**: Translation of DT resources to system resources (IRQ, memory, etc.)

### Device Lifecycle

The typical lifecycle of a device in the DM framework:

```
     Device Tree          Platform           Driver
         │                   │                  │
         │  Parse DT         │                  │
         ├──────────────────>│                  │
         │                   │                  │
         │  Create Platform  │                  │
         │     Device        │                  │
         │                   │                  │
         │  Register Device  │                  │
         │  on Platform Bus  │                  │
         │                   │                  │
         │                   │  Match Device    │
         │                   │  with Driver     │
         │                   ├─────────────────>│
         │                   │                  │
         │                   │  Driver Probe    │
         │                   │<─────────────────┤
         │                   │                  │
         │                   │  Initialize HW   │
         │                   │                  │
         │                   │  Register APIs   │
         │                   │                  │
         │                   │    RUNNING       │
         │                   │                  │
         │                   │  Driver Remove   │
         │                   ├─────────────────>│
         │                   │                  │
         │                   │  Cleanup         │
         │                   │<─────────────────┤
         │                   │                  │
```

## Kconfig Configuration

### Main DM Option

The Device Driver Model is enabled through the main Kconfig option:

```kconfig
config RT_USING_DM
    bool "Enable device driver model with device tree"
    default n
    help
        Enable device driver model with device tree (FDT). It will use more memory
        to parse and support device tree feature.
```

**Location in menuconfig**: `RT-Thread Components → Device Drivers → Enable device driver model with device tree`

### Related Options

#### Device Bus
```kconfig
config RT_USING_DEV_BUS
    bool "Using Device Bus device drivers"
    default y if RT_USING_SMART
    default n
```

#### Open Firmware (OFW)
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

**Location**: `RT-Thread Components → Device Drivers → Using Open Firmware (OFW)`

#### Builtin FDT
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

## Device Tree Integration

### Device Tree Basics

When `RT_USING_DM` and `RT_USING_OFW` are enabled, RT-Thread can parse and use device tree (FDT) to describe hardware:

#### Example Device Tree Node

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

### Using Device Tree in Drivers

#### Getting Device Node

```c
#include <drivers/ofw.h>

struct rt_ofw_node *np = dev->ofw_node;
```

#### Reading Properties

```c
/* Read string property */
const char *status;
rt_ofw_prop_read_string(np, "status", &status);

/* Read u32 property */
rt_uint32_t freq;
rt_ofw_prop_read_u32(np, "clock-frequency", &freq);

/* Read array */
rt_uint32_t reg[2];
rt_ofw_prop_read_u32_array(np, "reg", reg, 2);
```

#### Getting Resources

```c
/* Get memory resources */
rt_uint64_t addr, size;
rt_dm_dev_get_address(dev, 0, &addr, &size);

/* Get IRQ */
int irq = rt_dm_dev_get_irq(dev, 0);

/* Map MMIO */
void *base = rt_dm_dev_iomap(dev, 0);

/* Get clock */
struct rt_clk *clk = rt_clk_get_by_name(dev, "baudclk");
```

## DM-Dependent Modules

The Device Driver Model supports numerous hardware subsystems. Each module provides standardized APIs for both application layer and driver implementation:

| Module | Description | Documentation |
|--------|-------------|---------------|
| **clk** | Clock management framework | [clk.md](clk/README.md) |
| **regulator** | Voltage/current regulation | [regulator.md](regulator/README.md) |
| **pinctrl** | Pin multiplexing and configuration | [pinctrl.md](pinctrl/README.md) |
| **reset** | Reset controller management | [reset.md](reset/README.md) |
| **pmdomain** | Power domain management | [pmdomain.md](pmdomain/README.md) |
| **pic** | Platform interrupt controller | [pic.md](pic/README.md) |
| **nvmem** | Non-volatile memory framework | [nvmem.md](nvmem/README.md) |
| **mailbox** | Mailbox/doorbell communication | [mailbox.md](mailbox/README.md) |
| **thermal** | Thermal management | [thermal.md](thermal/README.md) |
| **mfd** | Multi-function device | [mfd.md](mfd/README.md) |
| **dma** | DMA engine management | [dma.md](dma/README.md) |
| **iio** | Industrial I/O subsystem | [iio.md](iio/README.md) |
| **phy** | PHY (physical layer) framework | [phy.md](phy/README.md) |
| **phye** | Ethernet PHY framework | [phye.md](phye/README.md) |
| **pci** | PCI bus support | [pci.md](pci/README.md) |
| **ofw** | Open Firmware/Device Tree | [ofw.md](ofw/README.md) |

## Common APIs

### Device Management

```c
/* Find device by master_id and device_id */
rt_device_t rt_dm_device_find(int master_id, int device_id);

/* Set device name */
int rt_dm_dev_set_name(rt_device_t dev, const char *format, ...);
int rt_dm_dev_set_name_auto(rt_device_t dev, const char *prefix);

/* Get device name */
const char *rt_dm_dev_get_name(rt_device_t dev);
int rt_dm_dev_get_name_id(rt_device_t dev);
```

### Device Tree APIs

```c
/* Get address resources */
int rt_dm_dev_get_address_count(rt_device_t dev);
rt_err_t rt_dm_dev_get_address(rt_device_t dev, int index,
                               rt_uint64_t *out_address, rt_uint64_t *out_size);
rt_err_t rt_dm_dev_get_address_by_name(rt_device_t dev, const char *name,
                                       rt_uint64_t *out_address, rt_uint64_t *out_size);

/* Map MMIO regions */
void *rt_dm_dev_iomap(rt_device_t dev, int index);
void *rt_dm_dev_iomap_by_name(rt_device_t dev, const char *name);

/* Get IRQ resources */
int rt_dm_dev_get_irq_count(rt_device_t dev);
int rt_dm_dev_get_irq(rt_device_t dev, int index);
int rt_dm_dev_get_irq_by_name(rt_device_t dev, const char *name);
```

### Property Reading

```c
/* Read various property types */
int rt_dm_dev_prop_read_u8_array_index(rt_device_t dev, const char *propname,
                                       int index, int nr, rt_uint8_t *out_values);
int rt_dm_dev_prop_read_u32_array_index(rt_device_t dev, const char *propname,
                                        int index, int nr, rt_uint32_t *out_values);
int rt_dm_dev_prop_read_string_index(rt_device_t dev, const char *propname,
                                     int index, const char **out_string);

/* Simplified single-value reading */
#define rt_dm_dev_prop_read_u32(dev, propname, out_value) \
    rt_dm_dev_prop_read_u32_array_index(dev, propname, 0, 1, out_value)
```

### Platform Device APIs

```c
/* Register platform driver */
rt_err_t rt_platform_driver_register(struct rt_platform_driver *pdrv);

/* Register platform device */
rt_err_t rt_platform_device_register(struct rt_platform_device *pdev);

/* Create platform device from device tree */
rt_err_t rt_platform_ofw_device_probe_child(struct rt_ofw_node *np);
```

## Writing a Platform Driver

### Basic Driver Structure

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
    
    /* Allocate private data */
    data = rt_calloc(1, sizeof(*data));
    if (!data)
        return -RT_ENOMEM;
    
    /* Map MMIO region */
    data->base = rt_dm_dev_iomap(dev, 0);
    if (!data->base) {
        rt_free(data);
        return -RT_ERROR;
    }
    
    /* Get IRQ */
    data->irq = rt_dm_dev_get_irq(dev, 0);
    
    /* Get clock */
    data->clk = rt_clk_get_by_name(dev, "baudclk");
    if (data->clk) {
        rt_clk_prepare_enable(data->clk);
    }
    
    /* Store private data */
    pdev->priv = data;
    
    /* Initialize hardware */
    /* ... */
    
    return RT_EOK;
}

static rt_err_t mydevice_remove(struct rt_platform_device *pdev)
{
    struct mydevice_data *data = pdev->priv;
    
    /* Cleanup hardware */
    /* ... */
    
    /* Release resources */
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

/* Auto-register driver at boot */
RT_PLATFORM_DRIVER_EXPORT(mydevice_driver);
```

### Device Tree Binding

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

## Best Practices

### 1. Resource Management

- Always check return values when getting resources
- Use reference counting for shared resources (clocks, regulators)
- Clean up resources in the remove callback
- Handle probe deferral for dependencies

### 2. Device Tree

- Use standard bindings when available
- Document custom properties in driver documentation
- Use labels for phandle references
- Keep device tree and driver in sync

### 3. Error Handling

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
    
    /* Success */
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

### 4. Thread Safety

- Use spinlocks for hardware register access
- Use mutexes for long operations
- Consider interrupt context in ISRs
- Protect shared data structures

## Performance Considerations

### Memory Usage

DM adds memory overhead:
- Device tree parsing requires memory for FDT and node structures
- Each device/driver adds object overhead
- Additional metadata for resource management

**Recommendations**:
- Only enable DM for systems that need it
- Consider memory constraints when designing device trees
- Use static allocation where possible

### Boot Time

- Device tree parsing happens early in boot
- Driver probing can be deferred
- Parallel initialization where possible

## Debugging

### Enable Debug Output

```c
#define DBG_TAG "mydriver"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

LOG_D("Debug message");
LOG_I("Info message");
LOG_W("Warning message");
LOG_E("Error message");
```

### DM-Specific Debugging

```
/* In menuconfig, enable OFW debugging */
RT-Thread Components → Device Drivers → Using Open Firmware (OFW)
```

### Common Issues

1. **Device not probing**: Check compatible string matches
2. **Resource not found**: Verify device tree properties
3. **Probe deferral loop**: Check for circular dependencies
4. **Memory access fault**: Verify MMIO mapping is correct

## Migration Guide

### From Traditional RT-Thread Drivers

Traditional RT-Thread drivers:
```c
rt_device_t dev = rt_device_find("uart0");
rt_device_open(dev, RT_DEVICE_OFLAG_RDWR);
```

With DM:
```c
/* Device automatically created from device tree */
rt_device_t dev = rt_device_find("uart0");
rt_device_open(dev, RT_DEVICE_OFLAG_RDWR);
/* API remains the same for users */
```

Driver implementation changes:
- Add platform driver structure
- Implement probe/remove callbacks
- Use DM APIs for resource management
- Add device tree binding

## Related Documentation

- [Open Firmware (OFW) Documentation](../ofw/dtc.md)
- [Device Framework](../framework/device.md)
- For module-specific documentation, see the links in the DM-Dependent Modules section

## References

- [Device Tree Specification](https://devicetree-specification.readthedocs.io/)
- [Linux Kernel Driver Model](https://www.kernel.org/doc/html/latest/driver-api/driver-model/index.html)
- RT-Thread Source Code: `components/drivers/core/`, `components/drivers/ofw/`
