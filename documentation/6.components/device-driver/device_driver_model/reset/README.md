# Reset Controller Framework

## Introduction

The Reset Controller Framework in RT-Thread provides a standardized interface for managing hardware reset signals in embedded systems. Reset controllers are essential for properly initializing, recovering, and managing the state of hardware peripherals and subsystems.

### General Overview

Reset signals are fundamental to hardware management for:

- **Device Initialization**: Bringing devices to a known state during boot
- **Error Recovery**: Resetting devices when errors occur
- **Power Management**: Resetting devices when entering/exiting low-power modes
- **Hot-plug Support**: Reinitializing devices for hotplug scenarios
- **System Stability**: Ensuring clean state transitions

Common reset controller types include:
- **Register-based**: Single register controlling multiple resets
- **GPIO-based**: Reset lines controlled by GPIO pins
- **Power Management IC (PMIC)**: Resets integrated in power management chips
- **System Control**: Resets managed through system control interfaces (SCMI)

### RT-Thread Implementation

The RT-Thread reset controller framework, located in `components/drivers/reset/`, provides:

1. **Consumer API**: Simple interface for device drivers to control reset lines
2. **Provider API**: Framework for implementing reset controller drivers
3. **Device Tree Integration**: Automatic configuration from FDT
4. **Reset Operations**: Assert, deassert, and pulse reset signals
5. **Array Support**: Managing multiple reset lines for a device
6. **Status Query**: Checking reset line state

**Architecture**:
```
┌─────────────────────────────────────────────────────────┐
│                  Consumer Drivers                        │
│    (UART, SPI, MMC, USB, Peripheral drivers)            │
└────────────────────┬────────────────────────────────────┘
                     │ Consumer API
                     │ (get, reset, assert, deassert)
┌────────────────────┴────────────────────────────────────┐
│          Reset Controller Framework                      │
│  - Reset Control Management                              │
│  - Array Support                                         │
│  - Status Tracking                                       │
└────────────────────┬────────────────────────────────────┘
                     │ Provider API
                     │ (ops callbacks)
┌────────────────────┴────────────────────────────────────┐
│        Reset Controller Drivers                          │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
│  │   Simple    │  │    SCMI     │  │   Custom    │     │
│  │   Reset     │  │   Reset     │  │   Reset     │     │
│  └─────────────┘  └─────────────┘  └─────────────┘     │
└────────────────────┬────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────┐
│         Hardware Reset Controllers                       │
│  (Reset registers, PMICs, System controllers)           │
└──────────────────────────────────────────────────────────┘
```

## Kconfig Configuration

### Main Configuration

```kconfig
menuconfig RT_USING_RESET
    bool "Using Reset Controller support"
    depends on RT_USING_DM
    depends on RT_USING_OFW
    default n
```

**Location in menuconfig**:
```
RT-Thread Components → Device Drivers → Using Reset Controller support
```

**Dependencies**:
- `RT_USING_DM`: Must be enabled first
- `RT_USING_OFW`: Device tree support required

**Default**: Disabled (opt-in feature)

### Reset Driver Options

#### SCMI Reset Driver
```kconfig
config RT_RESET_SCMI
    bool "Reset driver controlled via ARM SCMI interface"
    depends on RT_USING_RESET
    depends on RT_FIRMWARE_ARM_SCMI
    default n
```

Supports reset controllers controlled through ARM System Control and Management Interface (SCMI).

**Dependencies**:
- `RT_FIRMWARE_ARM_SCMI`: ARM SCMI firmware interface

#### Simple Reset Driver
```kconfig
config RT_RESET_SIMPLE
    bool "Simple Reset Controller Driver"
    depends on RT_USING_RESET
    default n
```

Supports basic register-based reset controllers with simple bit operations.

### Vendor-Specific Options

```kconfig
if RT_USING_RESET
    osource "$(SOC_DM_RESET_DIR)/Kconfig"
endif
```

Allows SoC-specific reset drivers to add their own Kconfig options.

## Device Tree Bindings

### Reset Controller Properties

Reset controllers export resets using:

```dts
#reset-cells = <n>;              /* Number of cells in reset specifier */
```

The number of cells typically indicates how many values are needed to identify a specific reset line (usually 1).

### Reset Consumer Properties

Devices reference reset lines using:

```dts
resets = <&rstc idx>;            /* Reset controller phandle and index */
reset-names = "name";            /* Reset line names */
```

### Simple Reset Controller Example

```dts
soc {
    /* Reset controller node */
    rstc: reset-controller@1c20000 {
        compatible = "vendor,reset-controller", "reset-simple";
        reg = <0x1c20000 0x100>;
        #reset-cells = <1>;
    };
};
```

### Consumer Usage Examples

```dts
/* Single reset consumer */
uart0: serial@1c28000 {
    compatible = "vendor,uart";
    reg = <0x1c28000 0x400>;
    interrupts = <0 0 4>;
    
    clocks = <&ccu 64>;
    resets = <&rstc 32>;         /* Reset index 32 */
    reset-names = "uart";
    
    status = "okay";
};

/* Multiple resets consumer */
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

/* Reset with shared line */
mmc0: mmc@1c0f000 {
    compatible = "vendor,mmc";
    reg = <0x1c0f000 0x1000>;
    
    resets = <&rstc 8>;
    /* No reset-names for single reset */
    
    status = "okay";
};
```

## Application Layer API

### Overview

The consumer API provides simple functions for device drivers to control reset lines. Reset operations are typically performed during device initialization and error recovery.

### Getting and Releasing Reset Controls

#### rt_reset_control_get_by_name

```c
struct rt_reset_control *rt_reset_control_get_by_name(struct rt_device *dev, 
                                                       const char *name);
```

Get a reset control by name.

**Parameters**:
- `dev`: Device structure pointer
- `name`: Reset line name (matches `reset-names` in device tree)

**Returns**:
- Pointer to reset control on success
- NULL on failure

**Example**:
```c
struct rt_device *dev = &pdev->parent;
struct rt_reset_control *rst;

/* Get the "phy" reset line */
rst = rt_reset_control_get_by_name(dev, "phy");
if (!rst) {
    LOG_W("No phy reset line");
    /* Not fatal - some boards may not have it */
}
```

#### rt_reset_control_get_by_index

```c
struct rt_reset_control *rt_reset_control_get_by_index(struct rt_device *dev, 
                                                        int index);
```

Get a reset control by index.

**Parameters**:
- `dev`: Device structure pointer
- `index`: Reset index (0-based) in `resets` property

**Returns**:
- Pointer to reset control on success
- NULL on failure

**Example**:
```c
/* Get the first reset */
struct rt_reset_control *rst = rt_reset_control_get_by_index(dev, 0);
```

#### rt_reset_control_get_array

```c
struct rt_reset_control *rt_reset_control_get_array(struct rt_device *dev);
```

Get all reset controls for a device as an array.

**Parameters**:
- `dev`: Device structure pointer

**Returns**:
- Pointer to reset control array on success
- NULL on failure

**Example**:
```c
struct rt_reset_control *rst_array = rt_reset_control_get_array(dev);
if (rst_array) {
    /* All resets can be controlled as a group */
}
```

#### rt_reset_control_get_count

```c
rt_ssize_t rt_reset_control_get_count(struct rt_device *dev);
```

Get the number of reset lines for a device.

**Parameters**:
- `dev`: Device structure pointer

**Returns**:
- Number of reset lines
- Negative error code on failure

#### rt_reset_control_put

```c
void rt_reset_control_put(struct rt_reset_control *rstc);
```

Release a reset control.

**Parameters**:
- `rstc`: Reset control pointer

### Reset Operations

#### rt_reset_control_reset

```c
rt_err_t rt_reset_control_reset(struct rt_reset_control *rstc);
```

Perform a reset pulse: assert then deassert.

**Parameters**:
- `rstc`: Reset control pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- This is the most common operation
- Automatically asserts and then deasserts with appropriate delay
- Safe to call even if reset control is NULL

**Example**:
```c
/* Reset a peripheral during initialization */
ret = rt_reset_control_reset(rst);
if (ret != RT_EOK) {
    LOG_E("Failed to reset peripheral: %d", ret);
    return ret;
}

/* Wait for hardware to stabilize */
rt_thread_mdelay(10);
```

#### rt_reset_control_assert

```c
rt_err_t rt_reset_control_assert(struct rt_reset_control *rstc);
```

Assert (activate) the reset signal.

**Parameters**:
- `rstc`: Reset control pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- Puts the device into reset state
- Must be followed by deassert to restore operation
- Safe to call even if reset control is NULL

**Example**:
```c
/* Put device into reset before power off */
rt_reset_control_assert(rst);
```

#### rt_reset_control_deassert

```c
rt_err_t rt_reset_control_deassert(struct rt_reset_control *rstc);
```

Deassert (deactivate) the reset signal.

**Parameters**:
- `rstc`: Reset control pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- Takes the device out of reset state
- Should be called after assert
- Safe to call even if reset control is NULL

**Example**:
```c
/* Take device out of reset */
rt_reset_control_deassert(rst);

/* Wait for hardware to be ready */
rt_thread_mdelay(1);
```

#### rt_reset_control_status

```c
int rt_reset_control_status(struct rt_reset_control *rstc);
```

Get the current status of a reset line.

**Parameters**:
- `rstc`: Reset control pointer

**Returns**:
- 1 if asserted (in reset)
- 0 if deasserted (not in reset)
- Negative error code on failure

**Example**:
```c
int status = rt_reset_control_status(rst);
if (status > 0) {
    LOG_W("Device is currently in reset");
}
```

## Complete Application Example

### Example: USB Driver with Reset Control

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/clk.h>
#include <drivers/reset.h>
#include <drivers/usb.h>

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
    
    /* Enable clocks first */
    ret = rt_clk_prepare_enable(usb->ahb_clk);
    if (ret != RT_EOK) {
        LOG_E("Failed to enable AHB clock: %d", ret);
        return ret;
    }
    
    ret = rt_clk_prepare_enable(usb->otg_clk);
    if (ret != RT_EOK) {
        LOG_E("Failed to enable OTG clock: %d", ret);
        goto err_disable_ahb;
    }
    
    /* Deassert resets after clocks are enabled */
    ret = rt_reset_control_deassert(usb->ahb_rst);
    if (ret != RT_EOK) {
        LOG_E("Failed to deassert AHB reset: %d", ret);
        goto err_disable_otg;
    }
    
    ret = rt_reset_control_deassert(usb->phy_rst);
    if (ret != RT_EOK) {
        LOG_E("Failed to deassert PHY reset: %d", ret);
        goto err_assert_ahb;
    }
    
    /* Wait for hardware to stabilize */
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
    /* Assert resets before disabling clocks */
    rt_reset_control_assert(usb->phy_rst);
    rt_reset_control_assert(usb->ahb_rst);
    
    /* Disable clocks */
    rt_clk_disable_unprepare(usb->otg_clk);
    rt_clk_disable_unprepare(usb->ahb_clk);
}

static rt_err_t usb_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct usb_device *usb;
    
    /* Allocate device structure */
    usb = rt_calloc(1, sizeof(*usb));
    if (!usb)
        return -RT_ENOMEM;
    
    /* Map MMIO region */
    usb->base = rt_dm_dev_iomap(dev, 0);
    if (!usb->base) {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* Get IRQ */
    usb->irq = rt_dm_dev_get_irq(dev, 0);
    if (usb->irq < 0) {
        ret = usb->irq;
        goto err_unmap;
    }
    
    /* Get clocks */
    usb->ahb_clk = rt_clk_get_by_name(dev, "ahb");
    if (!usb->ahb_clk) {
        LOG_E("Failed to get AHB clock");
        ret = -RT_ERROR;
        goto err_unmap;
    }
    
    usb->otg_clk = rt_clk_get_by_name(dev, "otg");
    if (!usb->otg_clk) {
        LOG_E("Failed to get OTG clock");
        ret = -RT_ERROR;
        goto err_put_ahb_clk;
    }
    
    /* Get resets */
    usb->ahb_rst = rt_reset_control_get_by_name(dev, "ahb");
    if (!usb->ahb_rst) {
        LOG_W("No AHB reset line");
        /* Not fatal - some platforms may not have it */
    }
    
    usb->phy_rst = rt_reset_control_get_by_name(dev, "phy");
    if (!usb->phy_rst) {
        LOG_W("No PHY reset line");
        /* Not fatal */
    }
    
    /* Initialize hardware */
    ret = usb_hw_init(usb);
    if (ret != RT_EOK) {
        goto err_put_resets;
    }
    
    /* Register USB controller */
    /* ... */
    
    pdev->priv = usb;
    LOG_I("USB device initialized");
    
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

static rt_err_t usb_remove(struct rt_platform_device *pdev)
{
    struct usb_device *usb = pdev->priv;
    
    /* Deinitialize hardware */
    usb_hw_deinit(usb);
    
    /* Release resources */
    if (usb->phy_rst)
        rt_reset_control_put(usb->phy_rst);
    if (usb->ahb_rst)
        rt_reset_control_put(usb->ahb_rst);
    rt_clk_put(usb->otg_clk);
    rt_clk_put(usb->ahb_clk);
    rt_iounmap(usb->base);
    rt_free(usb);
    
    return RT_EOK;
}

static const struct rt_ofw_node_id usb_ofw_ids[] = {
    { .compatible = "vendor,usb-otg" },
    { /* sentinel */ }
};

static struct rt_platform_driver usb_driver = {
    .name = "usb-otg",
    .ids = usb_ofw_ids,
    .probe = usb_probe,
    .remove = usb_remove,
};

RT_PLATFORM_DRIVER_EXPORT(usb_driver);
```

## Driver Implementation Guide

### Key Structures

#### rt_reset_controller

```c
struct rt_reset_controller {
    struct rt_object parent;
    rt_list_t rstc_nodes;                    /* List of reset controls */
    
    const char *name;                        /* Controller name */
    const struct rt_reset_control_ops *ops;  /* Operations */
    
    struct rt_ofw_node *ofw_node;            /* Device tree node */
    void *priv;                              /* Private data */
    
    struct rt_spinlock spinlock;             /* Lock for thread safety */
};
```

#### rt_reset_control_ops

```c
struct rt_reset_control_ops {
    /* Parse device tree arguments */
    rt_err_t (*ofw_parse)(struct rt_reset_control *rstc, 
                         struct rt_ofw_cell_args *args);
    
    /* Reset operations */
    rt_err_t (*reset)(struct rt_reset_control *rstc);
    rt_err_t (*assert)(struct rt_reset_control *rstc);
    rt_err_t (*deassert)(struct rt_reset_control *rstc);
    int      (*status)(struct rt_reset_control *rstc);
};
```

### Example: Simple Reset Controller Driver

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
    /* args->args[0] contains reset index */
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
    
    /* Set bit to assert reset */
    writel(readl(sr->base + RESET_ASSERT) | mask, 
           sr->base + RESET_ASSERT);
    
    return RT_EOK;
}

static rt_err_t simple_reset_deassert(struct rt_reset_control *rstc)
{
    struct simple_reset *sr = rstc->rstcer->priv;
    rt_uint32_t mask = RT_BIT(rstc->id);
    
    /* Set bit to deassert reset */
    writel(readl(sr->base + RESET_DEASSERT) | mask,
           sr->base + RESET_DEASSERT);
    
    return RT_EOK;
}

static int simple_reset_status(struct rt_reset_control *rstc)
{
    struct simple_reset *sr = rstc->rstcer->priv;
    rt_uint32_t status = readl(sr->base + RESET_STATUS);
    
    /* Return 1 if in reset, 0 if not */
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
    
    /* Allocate driver structure */
    sr = rt_calloc(1, sizeof(*sr));
    if (!sr)
        return -RT_ENOMEM;
    
    /* Map reset controller registers */
    sr->base = rt_dm_dev_iomap(dev, 0);
    if (!sr->base) {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* Get number of reset lines */
    if (rt_dm_dev_prop_read_u32(dev, "reset-count", &nr_resets)) {
        nr_resets = 32;  /* Default */
    }
    sr->nr_resets = nr_resets;
    
    /* Initialize reset controller */
    sr->rstcer.ops = &simple_reset_ops;
    sr->rstcer.ofw_node = dev->ofw_node;
    sr->rstcer.priv = sr;
    
    /* Register with framework */
    ret = rt_reset_controller_register(&sr->rstcer);
    if (ret != RT_EOK) {
        LOG_E("Failed to register reset controller: %d", ret);
        goto err_unmap;
    }
    
    pdev->priv = sr;
    LOG_I("Simple reset controller registered: %u lines", nr_resets);
    
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

## Best Practices

### For Consumer Drivers

1. **Check return values**: Reset operations can fail
2. **Order matters**: Enable clocks before deasserting resets
3. **Handle missing resets**: Not all platforms have reset lines (check for NULL)
4. **Wait after reset**: Allow hardware time to stabilize
5. **Reset during errors**: Use reset for error recovery
6. **Assert before power off**: Put devices in reset before disabling power

### Common Patterns

#### Initialization Sequence

```c
/* Correct initialization order */
rt_clk_prepare_enable(clk);          /* 1. Enable clocks */
rt_reset_control_deassert(rst);      /* 2. Take out of reset */
rt_thread_mdelay(10);                 /* 3. Wait for stability */
/* Initialize hardware registers */
```

#### Cleanup Sequence

```c
/* Correct cleanup order (reverse of init) */
/* Disable hardware */
rt_reset_control_assert(rst);         /* 1. Put into reset */
rt_clk_disable_unprepare(clk);        /* 2. Disable clocks */
```

#### Error Recovery

```c
/* Reset device on error */
if (device_error_detected()) {
    rt_reset_control_reset(rst);      /* Pulse reset */
    rt_thread_mdelay(10);
    reinitialize_device();
}
```

## Troubleshooting

### Common Issues

1. **Reset not found**
   - Check device tree: Ensure `resets` and `reset-names` properties exist
   - Check compatible string: Verify reset driver is loaded
   - Check Kconfig: Enable reset controller support

2. **Device doesn't work after reset**
   - Check clock order: Clocks must be enabled before deassert
   - Check delay: Add delay after reset for hardware stabilization
   - Check reset polarity: Verify assert/deassert are correct

3. **System hangs during reset**
   - Check clock status: Device clock must be running
   - Check dependencies: Some resets depend on others
   - Check power: Device power must be on

## Performance Considerations

### Memory Usage

- Each reset controller: ~100 bytes
- Each reset control: ~40 bytes
- Minimal overhead

### Timing

- Reset operations: Usually fast (register writes)
- May need delays: For hardware stabilization
- No complex calculations

## Related Modules

- **clk**: Clock management, coordinate with resets
- **regulator**: Power supply, coordinate with resets
- **pinctrl**: Pin configuration, may need after reset
- **pmdomain**: Power domain, higher-level control

## References

- RT-Thread Source: `components/drivers/reset/`
- Header File: `components/drivers/include/drivers/reset.h`
- Device Tree Bindings: [Linux Reset Bindings](https://www.kernel.org/doc/Documentation/devicetree/bindings/reset/)
- [RT-Thread DM Documentation](../README.md)
