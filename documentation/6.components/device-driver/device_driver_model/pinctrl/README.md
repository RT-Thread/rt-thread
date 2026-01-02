# Pin Control Framework

## Introduction

The Pin Control (pinctrl) framework in RT-Thread provides a standardized way to configure pin multiplexing, electrical properties, and GPIO functionality. It allows device drivers to dynamically configure pins without hard-coding hardware-specific details.

### General Overview

Pin control is essential for:

- **Pin Multiplexing**: Selecting between different functions for the same physical pin (UART, SPI, I2C, GPIO, etc.)
- **Electrical Configuration**: Setting pull-up/pull-down resistors, drive strength, and other electrical properties
- **Dynamic Reconfiguration**: Changing pin configurations at runtime based on system state
- **Power Management**: Configuring pins for low-power modes
- **GPIO Management**: Coordinating GPIO and peripheral pin usage

### RT-Thread Implementation

The RT-Thread pinctrl framework, located in `components/drivers/pinctrl/`, integrates with the pin device driver framework and provides:

1. **Consumer API**: Functions for device drivers to apply pin configurations
2. **Provider API**: Framework for implementing pinctrl drivers
3. **Device Tree Integration**: Automatic pin configuration from DT
4. **Pin States**: Multiple named configurations per device (default, sleep, etc.)
5. **GPIO Request**: Coordination between GPIO and peripheral usage

## Kconfig Configuration

### Main Configuration

```kconfig
menuconfig RT_USING_PINCTRL
    bool "Using Pin controllers device drivers"
    depends on RT_USING_DM
    depends on RT_USING_PIN
    default n
```

**Location in menuconfig**:
```
RT-Thread Components → Device Drivers → Using Pin controllers device drivers
```

**Dependencies**:
- `RT_USING_DM`: Device driver model required
- `RT_USING_PIN`: Pin device driver framework required

**Default**: Disabled (opt-in feature)

### Pinctrl Driver Options

#### SCMI Pinctrl Driver
```kconfig
config RT_PINCTRL_SCMI
    bool "Pinctrl driver via ARM SCMI interface"
    depends on RT_USING_PINCTRL
    depends on RT_FIRMWARE_ARM_SCMI
    default n
```

Supports pin control through ARM SCMI interface.

#### Single-Register Pinctrl Driver
```kconfig
config RT_PINCTRL_SINGLE
    bool "Single Pinctrl driver"
    depends on RT_USING_PINCTRL
    default n
```

Supports simple register-based pin controllers.

## Device Tree Bindings

### Pinctrl Provider Properties

Pin controllers export their configuration capability using:

```dts
#pinctrl-cells = <n>;            /* Number of cells in pinctrl specifier */
```

### Pinctrl Consumer Properties

Devices reference pin configurations using:

```dts
pinctrl-names = "default", "sleep";  /* State names */
pinctrl-0 = <&state0_pins>;          /* Pins for state 0 (default) */
pinctrl-1 = <&state1_pins>;          /* Pins for state 1 (sleep) */
```

### Example: Pin Controller

```dts
pio: pinctrl@1c20800 {
    compatible = "vendor,pinctrl";
    reg = <0x1c20800 0x400>;
    #pinctrl-cells = <1>;
    
    /* Pin group definitions */
    uart0_pins: uart0-pins {
        pins = "PB8", "PB9";
        function = "uart0";
        drive-strength = <40>;
        bias-pull-up;
    };
    
    uart0_sleep_pins: uart0-sleep-pins {
        pins = "PB8", "PB9";
        function = "gpio";
        bias-disable;
    };
    
    spi0_pins: spi0-pins {
        pins = "PC0", "PC1", "PC2", "PC3";
        function = "spi0";
        drive-strength = <40>;
    };
    
    i2c0_pins: i2c0-pins {
        pins = "PA11", "PA12";
        function = "i2c0";
        bias-pull-up;
    };
};
```

### Consumer Usage Examples

```dts
/* UART with pin configuration */
uart0: serial@1c28000 {
    compatible = "vendor,uart";
    reg = <0x1c28000 0x400>;
    
    pinctrl-names = "default", "sleep";
    pinctrl-0 = <&uart0_pins>;
    pinctrl-1 = <&uart0_sleep_pins>;
    
    status = "okay";
};

/* SPI with single pin state */
spi0: spi@1c68000 {
    compatible = "vendor,spi";
    reg = <0x1c68000 0x1000>;
    
    pinctrl-names = "default";
    pinctrl-0 = <&spi0_pins>;
    
    status = "okay";
};

/* I2C with pin configuration */
i2c0: i2c@1c2ac00 {
    compatible = "vendor,i2c";
    reg = <0x1c2ac00 0x400>;
    
    pinctrl-names = "default";
    pinctrl-0 = <&i2c0_pins>;
    
    status = "okay";
};
```

## Application Layer API

### Overview

The pinctrl API allows device drivers to apply pin configurations automatically from device tree or manually by name/index.

### Applying Pin Configurations

#### rt_pin_ctrl_confs_apply

```c
rt_err_t rt_pin_ctrl_confs_apply(struct rt_device *device, int index);
```

Apply pin configuration by index.

**Parameters**:
- `device`: Device structure pointer
- `index`: Configuration index (0 for pinctrl-0, 1 for pinctrl-1, etc.)

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Example**:
```c
struct rt_device *dev = &pdev->parent;

/* Apply default pin configuration (pinctrl-0) */
ret = rt_pin_ctrl_confs_apply(dev, 0);
if (ret != RT_EOK) {
    LOG_E("Failed to apply pin configuration: %d", ret);
    return ret;
}
```

#### rt_pin_ctrl_confs_apply_by_name

```c
rt_err_t rt_pin_ctrl_confs_apply_by_name(struct rt_device *device, const char *name);
```

Apply pin configuration by state name.

**Parameters**:
- `device`: Device structure pointer
- `name`: State name (matches entry in `pinctrl-names`)

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Example**:
```c
/* Apply default pin configuration */
rt_pin_ctrl_confs_apply_by_name(dev, "default");

/* Later, switch to sleep configuration */
rt_pin_ctrl_confs_apply_by_name(dev, "sleep");
```

#### rt_pin_ctrl_confs_lookup

```c
rt_ssize_t rt_pin_ctrl_confs_lookup(struct rt_device *device, const char *name);
```

Look up the index of a named pin configuration.

**Parameters**:
- `device`: Device structure pointer
- `name`: State name to look up

**Returns**:
- Configuration index on success
- Negative error code on failure

**Example**:
```c
/* Find index of "sleep" configuration */
rt_ssize_t idx = rt_pin_ctrl_confs_lookup(dev, "sleep");
if (idx >= 0) {
    rt_pin_ctrl_confs_apply(dev, idx);
}
```

### GPIO-Related Functions

#### rt_pin_get_named_pin

```c
rt_ssize_t rt_pin_get_named_pin(struct rt_device *dev, const char *propname, 
                                int index, rt_uint8_t *out_mode, rt_uint8_t *out_value);
```

Get a GPIO pin from device tree property.

**Parameters**:
- `dev`: Device structure
- `propname`: Property name (e.g., "reset-gpios", "enable-gpios")
- `index`: Pin index in the property
- `out_mode`: Optional output for pin mode
- `out_value`: Optional output for pin value

**Returns**:
- Pin number on success
- Negative error code on failure

**Example**:
```c
rt_uint8_t mode, value;
rt_ssize_t reset_pin;

/* Get reset GPIO from device tree */
reset_pin = rt_pin_get_named_pin(dev, "reset-gpios", 0, &mode, &value);
if (reset_pin >= 0) {
    rt_pin_mode(reset_pin, PIN_MODE_OUTPUT);
    rt_pin_write(reset_pin, PIN_LOW);  /* Assert reset */
}
```

#### rt_pin_get_named_pin_count

```c
rt_ssize_t rt_pin_get_named_pin_count(struct rt_device *dev, const char *propname);
```

Get the number of GPIOs in a device tree property.

**Parameters**:
- `dev`: Device structure
- `propname`: Property name

**Returns**:
- Number of pins
- Negative error code on failure

## Complete Application Example

### Example: SPI Driver with Pinctrl

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/spi.h>
#include <drivers/pin.h>

struct spi_device {
    void *base;
    int irq;
    struct rt_clk *clk;
    rt_ssize_t cs_pin;
    struct rt_spi_bus spi_bus;
};

static rt_err_t spi_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct spi_device *spi;
    
    /* Allocate device structure */
    spi = rt_calloc(1, sizeof(*spi));
    if (!spi)
        return -RT_ENOMEM;
    
    /* Map MMIO region */
    spi->base = rt_dm_dev_iomap(dev, 0);
    if (!spi->base) {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* Apply pin configuration from device tree */
    ret = rt_pin_ctrl_confs_apply_by_name(dev, "default");
    if (ret != RT_EOK) {
        LOG_E("Failed to apply pin configuration: %d", ret);
        goto err_unmap;
    }
    
    /* Get optional chip select GPIO */
    spi->cs_pin = rt_pin_get_named_pin(dev, "cs-gpios", 0, RT_NULL, RT_NULL);
    if (spi->cs_pin >= 0) {
        rt_pin_mode(spi->cs_pin, PIN_MODE_OUTPUT);
        rt_pin_write(spi->cs_pin, PIN_HIGH);  /* Deassert CS */
        LOG_I("Using GPIO %d for CS", spi->cs_pin);
    }
    
    /* Get clock */
    spi->clk = rt_clk_get_by_name(dev, "spi");
    if (!spi->clk) {
        LOG_E("Failed to get SPI clock");
        ret = -RT_ERROR;
        goto err_unmap;
    }
    
    ret = rt_clk_prepare_enable(spi->clk);
    if (ret != RT_EOK) {
        goto err_put_clk;
    }
    
    /* Initialize SPI bus */
    spi->spi_bus.parent.user_data = spi;
    ret = rt_spi_bus_register(&spi->spi_bus, rt_dm_dev_get_name(dev), &spi_ops);
    if (ret != RT_EOK) {
        goto err_disable_clk;
    }
    
    pdev->priv = spi;
    LOG_I("SPI device registered");
    
    return RT_EOK;
    
err_disable_clk:
    rt_clk_disable_unprepare(spi->clk);
err_put_clk:
    rt_clk_put(spi->clk);
err_unmap:
    rt_iounmap(spi->base);
err_free:
    rt_free(spi);
    return ret;
}

static rt_err_t spi_suspend(struct rt_device *dev)
{
    /* Switch to sleep pin configuration */
    return rt_pin_ctrl_confs_apply_by_name(dev, "sleep");
}

static rt_err_t spi_resume(struct rt_device *dev)
{
    /* Restore default pin configuration */
    return rt_pin_ctrl_confs_apply_by_name(dev, "default");
}

static const struct rt_ofw_node_id spi_ofw_ids[] = {
    { .compatible = "vendor,spi" },
    { /* sentinel */ }
};

static struct rt_platform_driver spi_driver = {
    .name = "spi",
    .ids = spi_ofw_ids,
    .probe = spi_probe,
};

RT_PLATFORM_DRIVER_EXPORT(spi_driver);
```

## Driver Implementation Guide

### Key Structures

#### rt_pin_ops (with pinctrl)

```c
struct rt_pin_ops {
    /* Standard pin operations */
    void (*pin_mode)(struct rt_device *device, rt_base_t pin, rt_uint8_t mode);
    void (*pin_write)(struct rt_device *device, rt_base_t pin, rt_uint8_t value);
    rt_ssize_t (*pin_read)(struct rt_device *device, rt_base_t pin);
    
    /* Pinctrl-specific operations */
    rt_err_t (*pin_ctrl_confs_apply)(struct rt_device *device, void *fw_conf_np);
    rt_err_t (*pin_ctrl_gpio_request)(struct rt_device *device, rt_base_t gpio, rt_uint32_t flags);
};
```

### Pin Configuration Parameters

Common pin configuration parameters (from `PIN_CONFIG_*` enum):

- `PIN_CONFIG_BIAS_DISABLE`: Disable bias (no pull-up/down)
- `PIN_CONFIG_BIAS_PULL_UP`: Enable pull-up resistor
- `PIN_CONFIG_BIAS_PULL_DOWN`: Enable pull-down resistor
- `PIN_CONFIG_DRIVE_STRENGTH`: Set output drive strength
- `PIN_CONFIG_INPUT_ENABLE`: Enable input buffer
- `PIN_CONFIG_OUTPUT_ENABLE`: Enable output buffer
- `PIN_CONFIG_INPUT_DEBOUNCE`: Set input debounce time
- `PIN_CONFIG_SLEW_RATE`: Control signal slew rate

## Best Practices

### For Consumer Drivers

1. **Apply pin configuration early**: During probe, before accessing hardware
2. **Use named states**: More maintainable than numeric indices
3. **Handle missing pinctrl gracefully**: Not all platforms require it
4. **Support power management**: Switch pin states for suspend/resume
5. **Check GPIO availability**: Verify GPIO pins exist before using them

### Common Patterns

#### Basic Pin Configuration

```c
/* Apply default pin configuration */
ret = rt_pin_ctrl_confs_apply_by_name(dev, "default");
if (ret != RT_EOK && ret != -RT_ENOSYS) {
    /* Real error, not just missing pinctrl */
    LOG_E("Pin configuration failed: %d", ret);
    return ret;
}
```

#### Power Management with Pinctrl

```c
static rt_err_t device_suspend(struct rt_device *dev)
{
    /* Save device state */
    
    /* Apply sleep pin configuration */
    rt_pin_ctrl_confs_apply_by_name(dev, "sleep");
    
    /* Disable clocks, etc. */
    return RT_EOK;
}

static rt_err_t device_resume(struct rt_device *dev)
{
    /* Enable clocks, etc. */
    
    /* Restore default pin configuration */
    rt_pin_ctrl_confs_apply_by_name(dev, "default");
    
    /* Restore device state */
    return RT_EOK;
}
```

#### GPIO with Pinctrl

```c
/* Get multiple GPIOs */
rt_ssize_t num_gpios = rt_pin_get_named_pin_count(dev, "reset-gpios");
for (int i = 0; i < num_gpios; i++) {
    rt_ssize_t pin = rt_pin_get_named_pin(dev, "reset-gpios", i, 
                                          RT_NULL, RT_NULL);
    if (pin >= 0) {
        rt_pin_mode(pin, PIN_MODE_OUTPUT);
        rt_pin_write(pin, PIN_LOW);
    }
}
```

## Troubleshooting

### Common Issues

1. **Pin configuration not applied**
   - Check device tree: Ensure `pinctrl-*` properties exist
   - Check compatible: Verify pinctrl driver is loaded
   - Check Kconfig: Enable RT_USING_PINCTRL

2. **GPIO conflicts**
   - Check pin multiplexing: Pin may be claimed by peripheral
   - Check pinctrl configuration: May conflict with GPIO usage
   - Use `pin_ctrl_gpio_request` for coordination

3. **Pin not working after configuration**
   - Check electrical properties: Drive strength, pull resistors
   - Check pin function: Verify correct function is selected
   - Check hardware: Verify pin is connected correctly

## Performance Considerations

### Memory Usage

- Pin configuration cached in device tree nodes
- Minimal runtime overhead
- Pin states stored per device

### Timing

- Configuration application: Usually fast (register writes)
- No complex calculations required
- One-time setup during probe

## Related Modules

- **pin**: Core pin device driver framework
- **gpio**: GPIO functionality
- **clk**: May need clocks enabled for pin configuration
- **pmdomain**: Power domain coordination

## References

- RT-Thread Source: `components/drivers/pinctrl/`
- Header File: `components/drivers/include/drivers/dev_pin.h`
- Pin Device Driver: `components/drivers/pin/`
- Device Tree Bindings: [Linux Pinctrl Bindings](https://www.kernel.org/doc/Documentation/devicetree/bindings/pinctrl/)
- [RT-Thread DM Documentation](../README.md)
