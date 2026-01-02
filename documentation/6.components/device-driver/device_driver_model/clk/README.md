# Clock Framework

## Introduction

The Clock Framework in RT-Thread provides a comprehensive infrastructure for managing hardware clocks in embedded systems. It implements a hierarchical clock tree model with support for clock gating, frequency scaling, parent switching, and phase adjustment - all essential for power management and system performance tuning.

### General Overview

Clock management is fundamental to embedded systems for:

- **Power Management**: Gating unused clocks to save power
- **Performance Tuning**: Adjusting clock frequencies for optimal performance
- **Device Synchronization**: Ensuring correct timing relationships
- **Dynamic Voltage and Frequency Scaling (DVFS)**: Coordinating voltage with frequency
- **Clock Domain Management**: Managing multiple clock sources and their relationships

Common clock types include:
- **Fixed-Rate Clocks**: Crystal oscillators, fixed PLLs
- **Gates**: Enable/disable control
- **Dividers**: Frequency division
- **Multiplexers**: Parent selection
- **PLLs**: Phase-locked loops for frequency multiplication
- **Composite Clocks**: Combinations of above types

### RT-Thread Implementation

The RT-Thread clock framework, located in `components/drivers/clk/`, provides:

1. **Consumer API**: Simple interface for device drivers to manage clocks
2. **Provider API**: Framework for implementing clock drivers
3. **Clock Tree**: Hierarchical parent-child relationships
4. **Device Tree Integration**: Automatic configuration from FDT
5. **Reference Counting**: Safe enable/disable with multiple consumers
6. **Notifier Chains**: Event notification for rate changes
7. **Rate Constraints**: Min/max rate management per consumer

**Architecture**:
```
┌─────────────────────────────────────────────────────────┐
│                  Consumer Drivers                        │
│    (UART, SPI, MMC, CPU, Peripheral drivers)            │
└────────────────────┬────────────────────────────────────┘
                     │ Consumer API
                     │ (get, enable, set_rate, etc.)
┌────────────────────┴────────────────────────────────────┐
│              Clock Framework Core                        │
│  - Clock Tree Management                                 │
│  - Reference Counting (prepare/enable)                   │
│  - Rate Calculation and Propagation                      │
│  - Parent Switching                                      │
│  - Notifier Chains                                       │
└────────────────────┬────────────────────────────────────┘
                     │ Provider API
                     │ (ops callbacks)
┌────────────────────┴────────────────────────────────────┐
│              Clock Drivers                               │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
│  │Fixed-Rate   │  │   Gate      │  │   PLL       │     │
│  │   Clock     │  │   Clock     │  │   Clock     │     │
│  └─────────────┘  └─────────────┘  └─────────────┘     │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
│  │  Divider    │  │  Multiplexer│  │  Composite  │     │
│  │   Clock     │  │   Clock     │  │   Clock     │     │
│  └─────────────┘  └─────────────┘  └─────────────┘     │
└────────────────────┬────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────┐
│              Hardware Clock Sources                      │
│  (Oscillators, PLLs, Clock Controllers)                 │
└──────────────────────────────────────────────────────────┘
```

## Kconfig Configuration

### Main Configuration

```kconfig
menuconfig RT_USING_CLK
    bool "Using Common Clock Framework (CLK)"
    depends on RT_USING_DM
    select RT_USING_ADT_REF
    default y
```

**Location in menuconfig**:
```
RT-Thread Components → Device Drivers → Using Common Clock Framework (CLK)
```

**Dependencies**:
- `RT_USING_DM`: Must be enabled first
- `RT_USING_ADT_REF`: Reference counting support (automatic)

**Default**: Enabled when DM is enabled

### SCMI Clock Driver

```kconfig
config RT_CLK_SCMI
    bool "Clock driver controlled via SCMI interface"
    depends on RT_USING_CLK
    depends on RT_FIRMWARE_ARM_SCMI
    default n
```

Supports clocks controlled through ARM System Control and Management Interface (SCMI).

**Dependencies**:
- `RT_FIRMWARE_ARM_SCMI`: ARM SCMI firmware interface

### Vendor-Specific Options

```kconfig
if RT_USING_CLK
    osource "$(SOC_DM_CLK_DIR)/Kconfig"
endif
```

Allows SoC-specific clock drivers to add their own Kconfig options via the `SOC_DM_CLK_DIR` variable.

## Device Tree Bindings

### Clock Provider Properties

Clock providers export clocks using these properties:

```dts
#clock-cells = <n>;              /* Number of cells in clock specifier */
clock-output-names = "name1", "name2";  /* Names of output clocks */
```

### Clock Consumer Properties

Devices reference clocks using:

```dts
clocks = <&clk_provider idx>;    /* Clock phandle and index */
clock-names = "name";            /* Clock connection names */
```

### Fixed-Rate Clock Example

```dts
clocks {
    /* Simple fixed-rate oscillator */
    osc24M: oscillator-24M {
        compatible = "fixed-clock";
        #clock-cells = <0>;
        clock-frequency = <24000000>;
        clock-output-names = "osc24M";
    };
    
    /* Fixed-rate with accuracy specification */
    osc32k: oscillator-32k {
        compatible = "fixed-clock";
        #clock-cells = <0>;
        clock-frequency = <32768>;
        clock-accuracy = <50>;  /* ±50 PPM */
        clock-output-names = "osc32k";
    };
};
```

### Clock Controller Example

```dts
ccu: clock-controller@1c20000 {
    compatible = "vendor,clock-controller";
    reg = <0x1c20000 0x400>;
    #clock-cells = <1>;
    
    /* Parent clocks */
    clocks = <&osc24M>, <&osc32k>;
    clock-names = "hosc", "losc";
    
    /* Output clock names (optional) */
    clock-output-names = "pll-cpu", "pll-ddr", "ahb1", "apb1", 
                         "bus-uart0", "bus-uart1";
};
```

### Consumer Usage Example

```dts
/* Single clock consumer */
uart0: serial@1c28000 {
    compatible = "vendor,uart";
    reg = <0x1c28000 0x400>;
    interrupts = <0 0 4>;
    
    clocks = <&ccu 64>;        /* Clock index 64 */
    clock-names = "baudclk";
    
    status = "okay";
};

/* Multiple clocks consumer */
mmc0: mmc@1c0f000 {
    compatible = "vendor,mmc";
    reg = <0x1c0f000 0x1000>;
    interrupts = <0 32 4>;
    
    clocks = <&ccu 8>, <&ccu 9>;
    clock-names = "ahb", "mmc";
    
    status = "okay";
};

/* Clock with parent reference */
cpu0: cpu@0 {
    compatible = "arm,cortex-a7";
    device_type = "cpu";
    reg = <0>;
    
    clocks = <&ccu 0>;
    clock-names = "cpu";
    
    operating-points-v2 = <&cpu_opp_table>;
};
```

## Application Layer API

### Overview

The consumer API provides functions for device drivers to manage their clocks. The framework uses a two-level prepare/enable model similar to Linux:
- **prepare**: May sleep, can configure PLLs
- **enable**: Atomic operation, must not sleep

### Getting and Releasing Clocks

#### rt_clk_get_by_name

```c
struct rt_clk *rt_clk_get_by_name(struct rt_device *dev, const char *name);
```

Get a clock by connection name.

**Parameters**:
- `dev`: Device structure pointer
- `name`: Clock connection name (matches `clock-names` in device tree)

**Returns**:
- Pointer to clock on success
- NULL on failure

**Example**:
```c
struct rt_device *dev = &pdev->parent;
struct rt_clk *clk;

/* Get the "baudclk" clock */
clk = rt_clk_get_by_name(dev, "baudclk");
if (!clk) {
    LOG_E("Failed to get baudclk");
    return -RT_ERROR;
}
```

#### rt_clk_get_by_index

```c
struct rt_clk *rt_clk_get_by_index(struct rt_device *dev, int index);
```

Get a clock by index in the `clocks` property.

**Parameters**:
- `dev`: Device structure pointer
- `index`: Clock index (0-based)

**Returns**:
- Pointer to clock on success
- NULL on failure

**Example**:
```c
/* Get the first clock */
struct rt_clk *clk = rt_clk_get_by_index(dev, 0);
```

#### rt_clk_get_array

```c
struct rt_clk_array *rt_clk_get_array(struct rt_device *dev);
```

Get all clocks for a device as an array.

**Parameters**:
- `dev`: Device structure pointer

**Returns**:
- Pointer to clock array on success
- Error pointer on failure (check with `rt_is_err()`)

**Example**:
```c
struct rt_clk_array *clk_arr = rt_clk_get_array(dev);
if (rt_is_err(clk_arr)) {
    return rt_ptr_err(clk_arr);
}

/* Access individual clocks */
for (int i = 0; i < clk_arr->count; i++) {
    struct rt_clk *clk = clk_arr->clks[i];
    /* ... */
}
```

#### rt_clk_put

```c
void rt_clk_put(struct rt_clk *clk);
```

Release a clock reference.

**Parameters**:
- `clk`: Clock pointer obtained from get functions

#### rt_clk_array_put

```c
void rt_clk_array_put(struct rt_clk_array *clk_arr);
```

Release a clock array.

**Parameters**:
- `clk_arr`: Clock array pointer

### Prepare and Enable

#### rt_clk_prepare

```c
rt_err_t rt_clk_prepare(struct rt_clk *clk);
```

Prepare a clock for enabling. This may sleep and can configure PLLs or perform other operations that cannot be done atomically.

**Parameters**:
- `clk`: Clock pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- May sleep - don't call from atomic context
- Must be called before `rt_clk_enable()`
- Use reference counting

#### rt_clk_unprepare

```c
void rt_clk_unprepare(struct rt_clk *clk);
```

Unprepare a previously prepared clock.

**Parameters**:
- `clk`: Clock pointer

#### rt_clk_enable

```c
rt_err_t rt_clk_enable(struct rt_clk *clk);
```

Enable a clock. This is an atomic operation that must not sleep.

**Parameters**:
- `clk`: Clock pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- Must not sleep - safe to call from atomic context
- Must be preceded by `rt_clk_prepare()`
- Uses reference counting

#### rt_clk_disable

```c
void rt_clk_disable(struct rt_clk *clk);
```

Disable a previously enabled clock.

**Parameters**:
- `clk`: Clock pointer

#### rt_clk_prepare_enable

```c
rt_err_t rt_clk_prepare_enable(struct rt_clk *clk);
```

Convenience function that prepares and enables a clock.

**Parameters**:
- `clk`: Clock pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Example**:
```c
/* Typical usage */
ret = rt_clk_prepare_enable(clk);
if (ret != RT_EOK) {
    LOG_E("Failed to enable clock: %d", ret);
    return ret;
}
```

#### rt_clk_disable_unprepare

```c
void rt_clk_disable_unprepare(struct rt_clk *clk);
```

Convenience function that disables and unprepares a clock.

**Parameters**:
- `clk`: Clock pointer

### Clock Array Operations

#### rt_clk_array_prepare_enable

```c
rt_err_t rt_clk_array_prepare_enable(struct rt_clk_array *clk_arr);
```

Prepare and enable all clocks in an array.

**Parameters**:
- `clk_arr`: Clock array pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure (partial enable handled internally)

#### rt_clk_array_disable_unprepare

```c
void rt_clk_array_disable_unprepare(struct rt_clk_array *clk_arr);
```

Disable and unprepare all clocks in an array.

**Parameters**:
- `clk_arr`: Clock array pointer

### Rate Management

#### rt_clk_set_rate

```c
rt_err_t rt_clk_set_rate(struct rt_clk *clk, rt_ubase_t rate);
```

Set clock frequency.

**Parameters**:
- `clk`: Clock pointer
- `rate`: Desired frequency in Hz

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- Actual rate may differ due to hardware limitations
- Use `rt_clk_get_rate()` to verify actual rate
- May trigger notifier callbacks

**Example**:
```c
/* Set UART clock to 48MHz */
ret = rt_clk_set_rate(uart_clk, 48000000);
if (ret != RT_EOK) {
    LOG_E("Failed to set clock rate: %d", ret);
}

/* Verify actual rate */
rt_ubase_t actual_rate = rt_clk_get_rate(uart_clk);
LOG_I("Clock rate: %u Hz", actual_rate);
```

#### rt_clk_get_rate

```c
rt_ubase_t rt_clk_get_rate(struct rt_clk *clk);
```

Get current clock frequency.

**Parameters**:
- `clk`: Clock pointer

**Returns**:
- Current frequency in Hz
- 0 on error

#### rt_clk_round_rate

```c
rt_base_t rt_clk_round_rate(struct rt_clk *clk, rt_ubase_t rate);
```

Get the closest supported rate without changing the clock.

**Parameters**:
- `clk`: Clock pointer
- `rate`: Desired frequency in Hz

**Returns**:
- Closest supported rate
- Negative error code on failure

**Example**:
```c
/* Check if desired rate is supported */
rt_base_t rounded = rt_clk_round_rate(clk, 50000000);
if (rounded < 0) {
    LOG_E("Cannot determine supported rate");
} else {
    LOG_I("Closest supported rate: %d Hz", rounded);
}
```

#### rt_clk_set_rate_range

```c
rt_err_t rt_clk_set_rate_range(struct rt_clk *clk, rt_ubase_t min, rt_ubase_t max);
```

Set acceptable rate range for this consumer.

**Parameters**:
- `clk`: Clock pointer
- `min`: Minimum acceptable rate in Hz
- `max`: Maximum acceptable rate in Hz

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Example**:
```c
/* UART requires 48MHz ±2% */
rt_clk_set_rate_range(uart_clk, 47040000, 48960000);
```

### Parent Management

#### rt_clk_set_parent

```c
rt_err_t rt_clk_set_parent(struct rt_clk *clk, struct rt_clk *parent);
```

Change clock parent (for multiplexer clocks).

**Parameters**:
- `clk`: Clock pointer
- `parent`: New parent clock

**Returns**:
- `RT_EOK` on success
- Error code on failure

#### rt_clk_get_parent

```c
struct rt_clk *rt_clk_get_parent(struct rt_clk *clk);
```

Get current parent clock.

**Parameters**:
- `clk`: Clock pointer

**Returns**:
- Pointer to parent clock
- NULL if no parent or error

### Phase Control

#### rt_clk_set_phase

```c
rt_err_t rt_clk_set_phase(struct rt_clk *clk, int degrees);
```

Set clock phase in degrees.

**Parameters**:
- `clk`: Clock pointer
- `degrees`: Phase in degrees (0-359)

**Returns**:
- `RT_EOK` on success
- `-RT_ENOSYS` if not supported
- Error code on failure

#### rt_clk_get_phase

```c
rt_base_t rt_clk_get_phase(struct rt_clk *clk);
```

Get current clock phase.

**Parameters**:
- `clk`: Clock pointer

**Returns**:
- Phase in degrees (0-359)
- Negative error code on failure

### Notifier API

#### rt_clk_notifier_register

```c
rt_err_t rt_clk_notifier_register(struct rt_clk *clk, 
                                   struct rt_clk_notifier *notifier);
```

Register a notifier for clock events.

**Parameters**:
- `clk`: Clock pointer
- `notifier`: Notifier structure with callback

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notifier Structure**:
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

**Event Messages**:
- `RT_CLK_MSG_PRE_RATE_CHANGE`: Before rate change
- `RT_CLK_MSG_POST_RATE_CHANGE`: After successful rate change
- `RT_CLK_MSG_ABORT_RATE_CHANGE`: Rate change aborted

**Example**:
```c
static rt_err_t clk_notifier_cb(struct rt_clk_notifier *notifier,
                                rt_ubase_t msg, 
                                rt_ubase_t old_rate,
                                rt_ubase_t new_rate)
{
    if (msg == RT_CLK_MSG_PRE_RATE_CHANGE) {
        LOG_I("Clock rate changing: %u -> %u Hz", old_rate, new_rate);
        /* Prepare for rate change */
    } else if (msg == RT_CLK_MSG_POST_RATE_CHANGE) {
        LOG_I("Clock rate changed successfully");
        /* Update hardware configuration */
    }
    return RT_EOK;
}

struct rt_clk_notifier my_notifier = {
    .callback = clk_notifier_cb,
    .priv = NULL,
};

rt_clk_notifier_register(clk, &my_notifier);
```

## Complete Application Example

### Example: UART Driver with Clock Management

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/clk.h>
#include <drivers/serial.h>

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
    
    /* Get clock rate */
    clk_rate = rt_clk_get_rate(uart->clk);
    if (clk_rate == 0) {
        LOG_E("Invalid clock rate");
        return -RT_ERROR;
    }
    
    /* Calculate baud rate divisor */
    divisor = clk_rate / (16 * cfg->baud_rate);
    
    /* Configure hardware */
    writel(divisor & 0xFF, uart->base + UART_DLL);
    writel((divisor >> 8) & 0xFF, uart->base + UART_DLH);
    
    LOG_D("UART: clk=%u Hz, baud=%u, divisor=%u", 
          clk_rate, cfg->baud_rate, divisor);
    
    return RT_EOK;
}

static rt_err_t uart_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct uart_device *uart;
    
    /* Allocate device structure */
    uart = rt_calloc(1, sizeof(*uart));
    if (!uart)
        return -RT_ENOMEM;
    
    /* Map MMIO region */
    uart->base = rt_dm_dev_iomap(dev, 0);
    if (!uart->base) {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* Get IRQ */
    uart->irq = rt_dm_dev_get_irq(dev, 0);
    if (uart->irq < 0) {
        ret = uart->irq;
        goto err_unmap;
    }
    
    /* Get clock */
    uart->clk = rt_clk_get_by_name(dev, "baudclk");
    if (!uart->clk) {
        LOG_E("Failed to get baudclk");
        ret = -RT_ERROR;
        goto err_unmap;
    }
    
    /* Prepare and enable clock */
    ret = rt_clk_prepare_enable(uart->clk);
    if (ret != RT_EOK) {
        LOG_E("Failed to enable clock: %d", ret);
        goto err_put_clk;
    }
    
    /* Log clock rate */
    LOG_I("UART clock rate: %u Hz", rt_clk_get_rate(uart->clk));
    
    /* Initialize serial device */
    uart->serial.ops = &uart_ops;
    uart->serial.config = RT_SERIAL_CONFIG_DEFAULT;
    
    /* Register serial device */
    ret = rt_hw_serial_register(&uart->serial, 
                                rt_dm_dev_get_name(dev),
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                uart);
    if (ret != RT_EOK) {
        goto err_disable_clk;
    }
    
    pdev->priv = uart;
    LOG_I("UART device registered");
    
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
    
    /* Unregister serial device */
    rt_device_unregister(&uart->serial.parent);
    
    /* Disable and release clock */
    rt_clk_disable_unprepare(uart->clk);
    rt_clk_put(uart->clk);
    
    /* Release resources */
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

## Driver Implementation Guide

### Key Structures

#### rt_clk_cell

```c
struct rt_clk_cell {
    struct rt_clk_node *clk_np;     /* Parent clock node */
    const char *name;                /* Clock name */
    const struct rt_clk_ops *ops;    /* Operations */
    
    rt_uint8_t parents_nr;           /* Number of parents */
    union {
        const char *parent_name;     /* Single parent */
        const char *const *parent_names;  /* Multiple parents */
    };
    
    rt_ubase_t rate;                 /* Cached rate */
    struct rt_clk *clk;              /* Consumer reference */
    struct rt_clk *parent;           /* Current parent */
    
    int prepare_count;               /* Prepare reference count */
    int enable_count;                /* Enable reference count */
    
    rt_uint32_t flags;               /* Clock flags */
    void *priv;                      /* Private data */
};
```

#### rt_clk_ops

```c
struct rt_clk_ops {
    /* Prepare/unprepare (may sleep) */
    rt_err_t    (*prepare)(struct rt_clk_cell *cell);
    void        (*unprepare)(struct rt_clk_cell *cell);
    rt_bool_t   (*is_prepared)(struct rt_clk_cell *cell);
    
    /* Enable/disable (atomic) */
    rt_err_t    (*enable)(struct rt_clk_cell *cell);
    void        (*disable)(struct rt_clk_cell *cell);
    rt_bool_t   (*is_enabled)(struct rt_clk_cell *cell);
    
    /* Rate control */
    rt_ubase_t  (*recalc_rate)(struct rt_clk_cell *cell, rt_ubase_t parent_rate);
    rt_base_t   (*round_rate)(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate);
    rt_err_t    (*set_rate)(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate);
    
    /* Parent control */
    rt_err_t    (*set_parent)(struct rt_clk_cell *cell, rt_uint8_t idx);
    rt_uint8_t  (*get_parent)(struct rt_clk_cell *cell);
    
    /* Phase control */
    rt_err_t    (*set_phase)(struct rt_clk_cell *cell, int degrees);
    rt_base_t   (*get_phase)(struct rt_clk_cell *cell);
};
```

### Example: Fixed-Rate Clock Driver

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
    
    /* Allocate driver structure */
    cf = rt_calloc(1, sizeof(*cf));
    if (!cf)
        return -RT_ENOMEM;
    
    /* Read clock frequency from device tree */
    if ((err = rt_dm_dev_prop_read_u32(dev, "clock-frequency", &val))) {
        LOG_E("Missing clock-frequency property");
        goto _fail;
    }
    cf->fcell.fixed_rate = val;
    
    /* Read optional accuracy */
    val = 0;
    rt_dm_dev_prop_read_u32(dev, "clock-accuracy", &val);
    cf->fcell.fixed_accuracy = val;
    
    /* Read optional clock name */
    rt_dm_dev_prop_read_string(dev, "clock-output-names", 
                               &cf->fcell.cell.name);
    
    /* Initialize clock node */
    cf->parent.dev = dev;
    cf->parent.cells_nr = 1;
    cf->parent.cells = cf->cells;
    cf->cells[0] = &cf->fcell.cell;
    cf->fcell.cell.ops = &fixed_clk_ops;
    
    /* Register with framework */
    if ((err = rt_clk_register(&cf->parent))) {
        LOG_E("Failed to register clock: %d", err);
        goto _fail;
    }
    
    LOG_I("Fixed clock '%s' registered: %u Hz", 
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

## Best Practices

### For Consumer Drivers

1. **Always use prepare_enable/disable_unprepare**: Simpler and safer
2. **Check return values**: Clock operations can fail
3. **Balance enable/disable**: Match every enable with a disable
4. **Order matters**: Enable clocks before using hardware
5. **Handle rate changes**: Use notifiers if rate changes affect operation
6. **Set rate constraints**: Use `rt_clk_set_rate_range()` when needed

### For Provider Drivers

1. **Implement only supported operations**: Leave unsupported ops NULL
2. **Cache rates when possible**: Avoid hardware access in `get_rate()`
3. **Handle reference counting**: Framework manages prepare/enable counts
4. **Propagate rate changes**: Update cached rates in children
5. **Support multiple parents**: For multiplexer clocks
6. **Document constraints**: Min/max rates, parent relationships

### Common Patterns

#### Simple Clock Usage

```c
/* Get and enable clock */
struct rt_clk *clk = rt_clk_get_by_name(dev, "clk");
if (!clk)
    return -RT_ERROR;

ret = rt_clk_prepare_enable(clk);
if (ret != RT_EOK) {
    rt_clk_put(clk);
    return ret;
}

/* Use hardware */

/* Cleanup */
rt_clk_disable_unprepare(clk);
rt_clk_put(clk);
```

#### Dynamic Frequency Scaling

```c
/* Change frequency based on workload */
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

## Troubleshooting

### Common Issues

1. **Clock not found**
   - Check device tree: Ensure `clocks` and `clock-names` properties exist
   - Check compatible string: Verify clock driver is loaded
   - Check Kconfig: Enable clock framework and drivers

2. **Enable fails**
   - Check parent clocks: Parents must be enabled first
   - Check prepare: Must prepare before enable
   - Check hardware: Verify clock controller is accessible

3. **Wrong frequency**
   - Check parent rate: Parent must be correct frequency
   - Check dividers: Hardware may have limited divider values
   - Use `rt_clk_round_rate()`: Verify supported rates

4. **System instability**
   - Check critical clocks: Some clocks must never be disabled
   - Check rate constraints: Don't exceed hardware limits
   - Check dependencies: Some clocks depend on others

## Performance Considerations

### Memory Usage

- Each clock cell: ~80-100 bytes
- Each consumer reference: ~40 bytes
- Clock tree overhead: Depends on hierarchy depth

### Timing

- prepare/enable: Can be slow (ms for PLLs)
- Rate changes: May be slow, use notifiers
- get_rate: Usually fast (cached)

### Optimization Tips

1. **Cache clock pointers**: Don't call get/put repeatedly
2. **Batch operations**: Use clock arrays when possible
3. **Avoid unnecessary rate changes**: Check current rate first
4. **Use prepare_enable**: Combines two operations

## Related Modules

- **regulator**: Power supply management, coordinate with clocks
- **pinctrl**: Pin configuration, may need clock enable
- **reset**: Reset control, coordinate with clock enable
- **pmdomain**: Power domain, higher-level power management

## References

- RT-Thread Source: `components/drivers/clk/`
- Header File: `components/drivers/include/drivers/clk.h`
- Device Tree Bindings: [Linux Clock Bindings](https://www.kernel.org/doc/Documentation/devicetree/bindings/clock/)
- [RT-Thread DM Documentation](../README.md)
