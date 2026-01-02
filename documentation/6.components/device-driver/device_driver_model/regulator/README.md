# Regulator Framework

## Introduction

The Regulator framework in RT-Thread provides a standardized interface for managing voltage and current regulators in embedded systems. Regulators are essential components that provide stable power supplies to various hardware peripherals, processors, and other system components.

### General Overview

Voltage regulators are electronic circuits that maintain a constant voltage level regardless of changes in load current or input voltage. They are crucial for:

- **Power Management**: Efficient power distribution and management
- **Voltage Scaling**: Dynamic voltage and frequency scaling (DVFS) for power optimization
- **Device Protection**: Protecting devices from overvoltage and overcurrent
- **System Stability**: Ensuring stable operation of hardware components

Common regulator types include:
- **Linear Regulators**: Simple, low-noise but less efficient
- **Switching Regulators (SMPS)**: More efficient but may generate noise
- **LDO (Low Dropout Regulators)**: Linear regulators with low voltage drop
- **Buck/Boost Converters**: Step-down/step-up switching regulators

### RT-Thread Implementation

The RT-Thread regulator framework, located in `components/drivers/regulator/`, provides:

1. **Consumer API**: Simple interface for device drivers to manage power supplies
2. **Provider API**: Framework for implementing regulator drivers
3. **Regulator Tree**: Hierarchical management of regulator dependencies
4. **Device Tree Integration**: Automatic configuration from device tree
5. **Reference Counting**: Safe enable/disable with multiple consumers
6. **Notifier Chains**: Event notification for voltage changes
7. **Multiple Driver Support**: Fixed, GPIO-controlled, SCMI-based regulators

**Architecture**:
```
┌─────────────────────────────────────────────────────────┐
│                  Consumer Drivers                        │
│    (UART, SPI, I2C, MMC, CPU, etc.)                     │
└────────────────────┬────────────────────────────────────┘
                     │ Consumer API
                     │ (get, enable, set_voltage, etc.)
┌────────────────────┴────────────────────────────────────┐
│             Regulator Framework Core                     │
│  - Reference Counting                                    │
│  - Regulator Tree Management                             │
│  - Notifier Chains                                       │
│  - Voltage/Current Validation                            │
└────────────────────┬────────────────────────────────────┘
                     │ Provider API
                     │ (ops callbacks)
┌────────────────────┴────────────────────────────────────┐
│            Regulator Drivers                             │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
│  │   Fixed     │  │    GPIO     │  │    SCMI     │     │
│  │  Regulator  │  │  Regulator  │  │  Regulator  │     │
│  └─────────────┘  └─────────────┘  └─────────────┘     │
└────────────────────┬────────────────────────────────────┘
                     │
┌────────────────────┴────────────────────────────────────┐
│               Hardware Regulators                        │
│  (PMIC, discrete regulators, power supplies)             │
└──────────────────────────────────────────────────────────┘
```

## Kconfig Configuration

### Main Configuration

The regulator framework depends on the Device Driver Model (DM):

```kconfig
menuconfig RT_USING_REGULATOR
    bool "Using Voltage and Current Regulator"
    select RT_USING_ADT
    select RT_USING_ADT_REF
    depends on RT_USING_DM
    default n
```

**Location in menuconfig**: 
```
RT-Thread Components → Device Drivers → Using Voltage and Current Regulator
```

**Dependencies**:
- `RT_USING_DM`: Must be enabled first
- `RT_USING_ADT`: Abstract Data Types (automatic)
- `RT_USING_ADT_REF`: Reference counting support (automatic)

### Regulator Driver Options

#### Fixed Regulator
```kconfig
config RT_REGULATOR_FIXED
    bool "Fixed regulator support"
    depends on RT_USING_REGULATOR
    depends on RT_USING_PIN
    depends on RT_USING_PINCTRL
    default y
```

Supports regulators with fixed output voltage, optionally controlled by a GPIO enable pin.

**Dependencies**:
- `RT_USING_PIN`: GPIO support
- `RT_USING_PINCTRL`: Pin control support

#### GPIO Regulator
```kconfig
config RT_REGULATOR_GPIO
    bool "GPIO regulator support"
    depends on RT_USING_REGULATOR
    depends on RT_USING_PIN
    default y
```

Supports regulators with multiple voltage levels selected by GPIO pins.

**Dependencies**:
- `RT_USING_PIN`: GPIO support

#### SCMI Regulator
```kconfig
config RT_REGULATOR_SCMI
    bool "SCMI regulator support"
    depends on RT_USING_REGULATOR
    depends on RT_USING_OFW
    depends on RT_FIRMWARE_ARM_SCMI
    default n
```

Supports regulators controlled through ARM System Control and Management Interface (SCMI).

**Dependencies**:
- `RT_USING_OFW`: Device tree support
- `RT_FIRMWARE_ARM_SCMI`: ARM SCMI firmware interface

### Vendor-Specific Options

```kconfig
if RT_USING_REGULATOR
    osource "$(SOC_DM_REGULATOR_DIR)/Kconfig"
endif
```

This allows SoC-specific regulator drivers to add their own Kconfig options via the `SOC_DM_REGULATOR_DIR` variable.

## Device Tree Bindings

### Common Properties

All regulator nodes support these standard properties:

```dts
regulator-name = "supply_name";            /* Human-readable name */
regulator-min-microvolt = <value>;         /* Minimum voltage in µV */
regulator-max-microvolt = <value>;         /* Maximum voltage in µV */
regulator-min-microamp = <value>;          /* Minimum current in µA */
regulator-max-microamp = <value>;          /* Maximum current in µA */
regulator-ramp-delay = <value>;            /* Voltage change rate in µV/µs */
regulator-enable-ramp-delay = <value>;     /* Enable delay in µs */
regulator-settling-time-us = <value>;      /* Settling time in µs */
regulator-settling-time-up-us = <value>;   /* Settling time for voltage increase */
regulator-settling-time-down-us = <value>; /* Settling time for voltage decrease */
enable-active-high;                        /* Enable pin active high (default) */
regulator-boot-on;                         /* Enable at boot */
regulator-always-on;                       /* Never disable */
regulator-soft-start;                      /* Enable soft-start */
regulator-pull-down;                       /* Enable pull-down when off */
regulator-over-current-protection;         /* Enable OCP */
```

### Fixed Regulator Example

Fixed regulators have a constant output voltage:

```dts
regulators {
    /* Simple fixed 3.3V regulator */
    vcc_3v3: regulator-vcc-3v3 {
        compatible = "regulator-fixed";
        regulator-name = "vcc-3v3";
        regulator-min-microvolt = <3300000>;
        regulator-max-microvolt = <3300000>;
        regulator-always-on;
        regulator-boot-on;
    };
    
    /* Fixed regulator with GPIO enable control */
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
    
    /* Regulator supplied by another regulator */
    vcc_1v8: regulator-vcc-1v8 {
        compatible = "regulator-fixed";
        regulator-name = "vcc-1v8";
        regulator-min-microvolt = <1800000>;
        regulator-max-microvolt = <1800000>;
        vin-supply = <&vcc_3v3>;      /* Parent supply */
        regulator-always-on;
    };
};
```

### GPIO-Controlled Regulator Example

GPIO regulators support multiple voltage levels:

```dts
vcc_ddr: regulator-vcc-ddr {
    compatible = "regulator-gpio";
    regulator-name = "vcc-ddr";
    regulator-min-microvolt = <1200000>;
    regulator-max-microvolt = <1350000>;
    
    /* GPIO pins to select voltage */
    gpios = <&gpio1 5 GPIO_ACTIVE_HIGH>,
            <&gpio1 6 GPIO_ACTIVE_HIGH>;
    
    /* Voltage selection table (based on GPIO states) */
    states = <1200000 0x0    /* 1.2V: both low */
              1250000 0x1    /* 1.25V: pin6=high, pin5=low */
              1300000 0x2    /* 1.3V: pin6=low, pin5=high */
              1350000 0x3>;  /* 1.35V: both high */
    
    enable-gpio = <&gpio1 4 GPIO_ACTIVE_HIGH>;
    startup-delay-us = <50000>;
};
```

### Consumer Usage in Device Tree

Devices reference regulators using supply properties:

```dts
/* UART with multiple power supplies */
uart0: serial@10000000 {
    compatible = "vendor,uart";
    reg = <0x10000000 0x1000>;
    interrupts = <32>;
    clocks = <&clk_uart0>;
    
    /* Power supplies */
    vdd-supply = <&vcc_3v3>;       /* Core supply */
    vddio-supply = <&vcc_1v8>;     /* I/O supply */
    
    status = "okay";
};

/* MMC/SD controller with regulator control */
mmc0: mmc@20000000 {
    compatible = "vendor,mmc";
    reg = <0x20000000 0x1000>;
    
    vmmc-supply = <&vcc_sd>;       /* Card power supply */
    vqmmc-supply = <&vcc_1v8>;     /* I/O level shifter supply */
    
    status = "okay";
};
```

## Application Layer API

### Overview

The consumer API provides functions for device drivers to manage their power supplies. All operations use opaque `struct rt_regulator` pointers obtained through the get API.

### Getting and Releasing Regulators

#### rt_regulator_get

```c
struct rt_regulator *rt_regulator_get(struct rt_device *dev, const char *id);
```

Get a regulator for a device.

**Parameters**:
- `dev`: Pointer to the device structure
- `id`: Supply name (matches `<name>-supply` in device tree, e.g., "vdd", "vmmc")

**Returns**:
- Pointer to regulator on success
- NULL on failure

**Example**:
```c
struct rt_device *dev = &pdev->parent;
struct rt_regulator *vdd_reg;

/* Get the "vdd" supply */
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

Release a regulator reference.

**Parameters**:
- `reg`: Regulator pointer obtained from `rt_regulator_get()`

**Example**:
```c
rt_regulator_put(vdd_reg);
```

### Enable and Disable

#### rt_regulator_enable

```c
rt_err_t rt_regulator_enable(struct rt_regulator *reg);
```

Enable a regulator. Uses reference counting, so multiple enables require matching disables.

**Parameters**:
- `reg`: Regulator pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- Automatically enables parent regulators
- Waits for enable delay if configured
- Calls notifier chains

**Example**:
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

Disable a regulator. Only actually disables when reference count reaches zero.

**Parameters**:
- `reg`: Regulator pointer

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- Respects `regulator-always-on` property
- Waits for off-on delay if re-enabling soon
- Calls notifier chains

**Example**:
```c
rt_regulator_disable(vdd_reg);
```

#### rt_regulator_is_enabled

```c
rt_bool_t rt_regulator_is_enabled(struct rt_regulator *reg);
```

Check if a regulator is currently enabled.

**Parameters**:
- `reg`: Regulator pointer

**Returns**:
- `RT_TRUE` if enabled
- `RT_FALSE` if disabled

**Example**:
```c
if (rt_regulator_is_enabled(vdd_reg)) {
    LOG_I("Regulator is enabled");
}
```

### Voltage Control

#### rt_regulator_set_voltage

```c
rt_err_t rt_regulator_set_voltage(struct rt_regulator *reg, int min_uvolt, int max_uvolt);
```

Set regulator output voltage within a range.

**Parameters**:
- `reg`: Regulator pointer
- `min_uvolt`: Minimum acceptable voltage in microvolts (µV)
- `max_uvolt`: Maximum acceptable voltage in microvolts (µV)

**Returns**:
- `RT_EOK` on success
- `-RT_ENOSYS` if voltage control not supported
- Error code on failure

**Notes**:
- Voltage must be within regulator's configured range
- Framework selects optimal voltage within specified range
- Waits for settling time after voltage change
- Calls notifier chains with voltage change events

**Example**:
```c
/* Set voltage to 1.8V ±5% */
ret = rt_regulator_set_voltage(vdd_reg, 1710000, 1890000);
if (ret != RT_EOK) {
    LOG_E("Failed to set voltage: %d", ret);
}

/* Set precise voltage */
ret = rt_regulator_set_voltage(vdd_reg, 3300000, 3300000);
```

#### rt_regulator_set_voltage_triplet

```c
rt_inline rt_err_t rt_regulator_set_voltage_triplet(struct rt_regulator *reg,
        int min_uvolt, int target_uvolt, int max_uvolt);
```

Set voltage with a preferred target value.

**Parameters**:
- `reg`: Regulator pointer
- `min_uvolt`: Minimum voltage in µV
- `target_uvolt`: Preferred voltage in µV
- `max_uvolt`: Maximum voltage in µV

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notes**:
- First attempts to set target voltage
- Falls back to min-max range if target fails

**Example**:
```c
/* Prefer 1.8V, but accept 1.71V-1.89V */
ret = rt_regulator_set_voltage_triplet(vdd_reg, 1710000, 1800000, 1890000);
```

#### rt_regulator_get_voltage

```c
int rt_regulator_get_voltage(struct rt_regulator *reg);
```

Get current regulator output voltage.

**Parameters**:
- `reg`: Regulator pointer

**Returns**:
- Current voltage in microvolts (µV)
- Negative error code on failure

**Example**:
```c
int voltage = rt_regulator_get_voltage(vdd_reg);
if (voltage > 0) {
    LOG_I("Current voltage: %d.%03dV", voltage / 1000000, (voltage / 1000) % 1000);
}
```

#### rt_regulator_is_supported_voltage

```c
rt_bool_t rt_regulator_is_supported_voltage(struct rt_regulator *reg, 
                                            int min_uvolt, int max_uvolt);
```

Check if a voltage range is supported.

**Parameters**:
- `reg`: Regulator pointer
- `min_uvolt`: Minimum voltage in µV
- `max_uvolt`: Maximum voltage in µV

**Returns**:
- `RT_TRUE` if supported
- `RT_FALSE` if not supported

**Example**:
```c
if (rt_regulator_is_supported_voltage(vdd_reg, 1800000, 1800000)) {
    rt_regulator_set_voltage(vdd_reg, 1800000, 1800000);
}
```

### Operating Modes

#### rt_regulator_set_mode

```c
rt_err_t rt_regulator_set_mode(struct rt_regulator *reg, rt_uint32_t mode);
```

Set regulator operating mode.

**Parameters**:
- `reg`: Regulator pointer
- `mode`: Operating mode flags:
  - `RT_REGULATOR_MODE_FAST`: High-speed mode (higher power consumption)
  - `RT_REGULATOR_MODE_NORMAL`: Normal operation mode
  - `RT_REGULATOR_MODE_IDLE`: Idle mode (reduced performance)
  - `RT_REGULATOR_MODE_STANDBY`: Standby mode (minimal power)

**Returns**:
- `RT_EOK` on success
- `-RT_ENOSYS` if mode control not supported
- Error code on failure

**Example**:
```c
/* Set to low-power mode during idle */
rt_regulator_set_mode(vdd_reg, RT_REGULATOR_MODE_IDLE);

/* Restore normal mode */
rt_regulator_set_mode(vdd_reg, RT_REGULATOR_MODE_NORMAL);
```

#### rt_regulator_get_mode

```c
rt_int32_t rt_regulator_get_mode(struct rt_regulator *reg);
```

Get current regulator operating mode.

**Parameters**:
- `reg`: Regulator pointer

**Returns**:
- Current mode flags
- `RT_REGULATOR_MODE_INVALID` on error

### Notification API

#### rt_regulator_notifier_register

```c
rt_err_t rt_regulator_notifier_register(struct rt_regulator *reg,
                                        struct rt_regulator_notifier *notifier);
```

Register a notifier for regulator events.

**Parameters**:
- `reg`: Regulator pointer
- `notifier`: Notifier structure with callback

**Returns**:
- `RT_EOK` on success
- Error code on failure

**Notifier Structure**:
```c
struct rt_regulator_notifier {
    rt_list_t list;
    struct rt_regulator *regulator;
    rt_regulator_notifier_callback callback;
    void *priv;
};

typedef rt_err_t (*rt_regulator_notifier_callback)(
    struct rt_regulator_notifier *notifier,
    rt_ubase_t msg,
    void *data);
```

**Event Messages**:
- `RT_REGULATOR_MSG_ENABLE`: Regulator enabled
- `RT_REGULATOR_MSG_DISABLE`: Regulator disabled
- `RT_REGULATOR_MSG_VOLTAGE_CHANGE`: Voltage changed successfully
- `RT_REGULATOR_MSG_VOLTAGE_CHANGE_ERR`: Voltage change failed

**Example**:
```c
static rt_err_t voltage_change_callback(struct rt_regulator_notifier *notifier,
                                       rt_ubase_t msg, void *data)
{
    if (msg == RT_REGULATOR_MSG_VOLTAGE_CHANGE) {
        union rt_regulator_notifier_args *args = data;
        LOG_I("Voltage changed: %d -> %d µV", 
              args->old_uvolt, args->min_uvolt);
    }
    return RT_EOK;
}

struct rt_regulator_notifier my_notifier = {
    .callback = voltage_change_callback,
    .priv = NULL,
};

rt_regulator_notifier_register(vdd_reg, &my_notifier);
```

#### rt_regulator_notifier_unregister

```c
rt_err_t rt_regulator_notifier_unregister(struct rt_regulator *reg,
                                          struct rt_regulator_notifier *notifier);
```

Unregister a regulator notifier.

**Parameters**:
- `reg`: Regulator pointer
- `notifier`: Notifier to unregister

**Returns**:
- `RT_EOK` on success
- Error code on failure

## Complete Application Example

### Example: MMC/SD Driver with Regulator Control

```c
#include <rtthread.h>
#include <drivers/platform.h>
#include <drivers/regulator.h>
#include <drivers/clk.h>

struct mmc_host {
    void *base;
    int irq;
    struct rt_clk *clk;
    struct rt_regulator *vmmc;  /* Card power supply */
    struct rt_regulator *vqmmc; /* I/O voltage supply */
};

static rt_err_t mmc_set_ios_voltage(struct mmc_host *host, int voltage)
{
    rt_err_t ret;
    
    /* Set I/O voltage level */
    if (voltage == 1800000) {
        ret = rt_regulator_set_voltage(host->vqmmc, 1800000, 1800000);
    } else {
        ret = rt_regulator_set_voltage(host->vqmmc, 3300000, 3300000);
    }
    
    if (ret != RT_EOK) {
        LOG_E("Failed to set I/O voltage: %d", ret);
        return ret;
    }
    
    /* Wait for voltage to stabilize */
    rt_thread_mdelay(10);
    
    return RT_EOK;
}

static rt_err_t mmc_power_on(struct mmc_host *host)
{
    rt_err_t ret;
    
    /* Enable card power supply */
    ret = rt_regulator_enable(host->vmmc);
    if (ret != RT_EOK) {
        LOG_E("Failed to enable vmmc: %d", ret);
        return ret;
    }
    
    /* Set I/O voltage to 3.3V initially */
    ret = rt_regulator_enable(host->vqmmc);
    if (ret != RT_EOK) {
        LOG_E("Failed to enable vqmmc: %d", ret);
        goto err_disable_vmmc;
    }
    
    ret = mmc_set_ios_voltage(host, 3300000);
    if (ret != RT_EOK) {
        goto err_disable_vqmmc;
    }
    
    /* Enable clock */
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
    /* Disable clock */
    rt_clk_disable_unprepare(host->clk);
    
    /* Disable regulators in reverse order */
    rt_regulator_disable(host->vqmmc);
    rt_regulator_disable(host->vmmc);
}

static rt_err_t mmc_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct mmc_host *host;
    
    /* Allocate host structure */
    host = rt_calloc(1, sizeof(*host));
    if (!host)
        return -RT_ENOMEM;
    
    /* Map MMIO region */
    host->base = rt_dm_dev_iomap(dev, 0);
    if (!host->base) {
        ret = -RT_ERROR;
        goto err_free_host;
    }
    
    /* Get IRQ */
    host->irq = rt_dm_dev_get_irq(dev, 0);
    if (host->irq < 0) {
        ret = host->irq;
        goto err_iounmap;
    }
    
    /* Get clock */
    host->clk = rt_clk_get_by_name(dev, "mmc");
    if (!host->clk) {
        ret = -RT_ERROR;
        goto err_iounmap;
    }
    
    /* Get regulators */
    host->vmmc = rt_regulator_get(dev, "vmmc");
    if (!host->vmmc) {
        LOG_W("No vmmc regulator");
        /* Not fatal, some boards don't have switchable power */
    }
    
    host->vqmmc = rt_regulator_get(dev, "vqmmc");
    if (!host->vqmmc) {
        LOG_W("No vqmmc regulator");
        /* Not fatal, fixed I/O voltage is acceptable */
    }
    
    /* Power on MMC */
    if (host->vmmc || host->vqmmc) {
        ret = mmc_power_on(host);
        if (ret != RT_EOK) {
            goto err_put_regulators;
        }
    }
    
    /* Initialize MMC hardware */
    /* ... */
    
    pdev->priv = host;
    LOG_I("MMC host initialized");
    
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

static rt_err_t mmc_remove(struct rt_platform_device *pdev)
{
    struct mmc_host *host = pdev->priv;
    
    /* Power off */
    if (host->vmmc || host->vqmmc) {
        mmc_power_off(host);
    }
    
    /* Release resources */
    if (host->vqmmc)
        rt_regulator_put(host->vqmmc);
    if (host->vmmc)
        rt_regulator_put(host->vmmc);
    rt_clk_put(host->clk);
    rt_iounmap(host->base);
    rt_free(host);
    
    return RT_EOK;
}

static const struct rt_ofw_node_id mmc_ofw_ids[] = {
    { .compatible = "vendor,mmc" },
    { /* sentinel */ }
};

static struct rt_platform_driver mmc_driver = {
    .name = "mmc",
    .ids = mmc_ofw_ids,
    .probe = mmc_probe,
    .remove = mmc_remove,
};

RT_PLATFORM_DRIVER_EXPORT(mmc_driver);
```

## Driver Implementation Guide

### Overview

Implementing a regulator driver involves:
1. Defining regulator parameters
2. Implementing regulator operations
3. Registering with the framework
4. (Optional) Parsing device tree properties

### Key Structures

#### rt_regulator_node

```c
struct rt_regulator_node {
    rt_list_t list;
    rt_list_t children_nodes;
    
    struct rt_device *dev;                      /* Parent device */
    struct rt_regulator_node *parent;           /* Parent regulator */
    
    const char *supply_name;                    /* Supply name */
    const struct rt_regulator_ops *ops;         /* Operations */
    
    struct rt_ref ref;                          /* Reference count */
    rt_atomic_t enabled_count;                  /* Enable count */
    
    const struct rt_regulator_param *param;     /* Parameters */
    rt_list_t notifier_nodes;                   /* Notifier list */
    
    void *priv;                                 /* Private data */
};
```

#### rt_regulator_param

```c
struct rt_regulator_param {
    const char *name;               /* Regulator name */
    
    int min_uvolt;                  /* Minimum voltage in µV */
    int max_uvolt;                  /* Maximum voltage in µV */
    int min_uamp;                   /* Minimum current in µA */
    int max_uamp;                   /* Maximum current in µA */
    int ramp_delay;                 /* Voltage ramp rate in µV/µs */
    int enable_delay;               /* Enable delay in µs */
    int off_on_delay;               /* Off-to-on delay in µs */
    int settling_time;              /* General settling time */
    int settling_time_up;           /* Voltage increase settling time */
    int settling_time_down;         /* Voltage decrease settling time */
    
    rt_uint32_t enable_active_high:1;       /* Enable pin polarity */
    rt_uint32_t boot_on:1;                  /* Enabled at boot */
    rt_uint32_t always_on:1;                /* Never disable */
    rt_uint32_t soft_start:1;               /* Soft-start enabled */
    rt_uint32_t pull_down:1;                /* Pull-down when off */
    rt_uint32_t over_current_protection:1;  /* OCP enabled */
    rt_uint32_t ramp_disable:1;             /* Ramp disabled */
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
    rt_err_t    (*set_ramp_delay)(struct rt_regulator_node *reg, int ramp);
    rt_uint32_t (*enable_time)(struct rt_regulator_node *reg);
};
```

All callbacks are optional. Implement only what the hardware supports.

### Example: Simple Fixed Regulator Driver

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

static rt_bool_t my_regulator_is_enabled(struct rt_regulator_node *reg_node)
{
    struct my_regulator *reg = rt_container_of(reg_node, struct my_regulator, reg_node);
    
    if (reg->enable_pin >= 0) {
        rt_uint8_t value;
        rt_pin_mode(reg->enable_pin, PIN_MODE_INPUT);
        value = rt_pin_read(reg->enable_pin);
        return (value == PIN_HIGH) == reg->param.enable_active_high;
    }
    
    return RT_TRUE;  /* Always on if no enable pin */
}

static int my_regulator_get_voltage(struct rt_regulator_node *reg_node)
{
    struct my_regulator *reg = rt_container_of(reg_node, struct my_regulator, reg_node);
    
    /* Fixed voltage: return average of min and max */
    return (reg->param.min_uvolt + reg->param.max_uvolt) / 2;
}

static const struct rt_regulator_ops my_regulator_ops = {
    .enable = my_regulator_enable,
    .disable = my_regulator_disable,
    .is_enabled = my_regulator_is_enabled,
    .get_voltage = my_regulator_get_voltage,
};

static rt_err_t my_regulator_probe(struct rt_platform_device *pdev)
{
    rt_err_t ret;
    struct rt_device *dev = &pdev->parent;
    struct my_regulator *reg;
    rt_uint32_t voltage;
    
    /* Allocate regulator structure */
    reg = rt_calloc(1, sizeof(*reg));
    if (!reg)
        return -RT_ENOMEM;
    
    /* Parse device tree properties */
    if (rt_dm_dev_prop_read_u32(dev, "regulator-min-microvolt", &voltage) == 0) {
        reg->param.min_uvolt = voltage;
    }
    
    if (rt_dm_dev_prop_read_u32(dev, "regulator-max-microvolt", &voltage) == 0) {
        reg->param.max_uvolt = voltage;
    }
    
    reg->param.name = rt_dm_dev_get_name(dev);
    reg->param.enable_active_high = 
        rt_dm_dev_prop_read_bool(dev, "enable-active-high");
    reg->param.always_on = 
        rt_dm_dev_prop_read_bool(dev, "regulator-always-on");
    reg->param.boot_on = 
        rt_dm_dev_prop_read_bool(dev, "regulator-boot-on");
    
    /* Get enable GPIO pin */
    reg->enable_pin = rt_pin_get_named_pin(dev, "enable", 0, RT_NULL, RT_NULL);
    if (reg->enable_pin < 0) {
        reg->enable_pin = -1;  /* No GPIO control */
    }
    
    /* Apply pin control configuration */
    rt_pin_ctrl_confs_apply(dev, 0);
    
    /* Initialize regulator node */
    reg->reg_node.dev = dev;
    reg->reg_node.supply_name = reg->param.name;
    reg->reg_node.ops = &my_regulator_ops;
    reg->reg_node.param = &reg->param;
    
    /* Register with framework */
    ret = rt_regulator_register(&reg->reg_node);
    if (ret != RT_EOK) {
        LOG_E("Failed to register regulator: %d", ret);
        rt_free(reg);
        return ret;
    }
    
    pdev->priv = reg;
    LOG_I("Regulator '%s' registered: %d-%d µV", 
          reg->param.name, reg->param.min_uvolt, reg->param.max_uvolt);
    
    return RT_EOK;
}

static rt_err_t my_regulator_remove(struct rt_platform_device *pdev)
{
    struct my_regulator *reg = pdev->priv;
    
    rt_regulator_unregister(&reg->reg_node);
    rt_free(reg);
    
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
    .remove = my_regulator_remove,
};

RT_PLATFORM_DRIVER_EXPORT(my_regulator_driver);
```

### Helper Function: Device Tree Parsing

The framework provides a helper to parse standard regulator properties:

```c
#ifdef RT_USING_OFW
rt_err_t regulator_ofw_parse(struct rt_ofw_node *np, 
                            struct rt_regulator_param *param);
#endif
```

**Usage in Driver**:
```c
#include "regulator_dm.h"  /* Internal header */

static rt_err_t my_probe(struct rt_platform_device *pdev)
{
    struct my_regulator *reg;
    struct rt_device *dev = &pdev->parent;
    
    reg = rt_calloc(1, sizeof(*reg));
    if (!reg)
        return -RT_ENOMEM;
    
    /* Parse standard properties */
    regulator_ofw_parse(dev->ofw_node, &reg->param);
    
    /* Parse custom properties */
    /* ... */
    
    return RT_EOK;
}
```

## Architecture Diagram

The regulator framework architecture with component relationships:

![Regulator Architecture](regulator-architecture.svg)

## Best Practices

### For Consumer Drivers

1. **Always check return values**: Regulator operations can fail
2. **Balance enable/disable**: Match every enable with a disable
3. **Order matters**: Enable regulators before clocks, disable in reverse order
4. **Use voltage ranges**: Specify acceptable voltage ranges, not exact values
5. **Handle probe deferral**: Regulators may not be available during early boot

```c
/* Good: Flexible voltage range */
ret = rt_regulator_set_voltage(reg, 1710000, 1890000);

/* Avoid: Overly strict requirement */
ret = rt_regulator_set_voltage(reg, 1800000, 1800000);
```

### For Provider Drivers

1. **Implement only supported operations**: Leave unsupported ops NULL
2. **Use reference counting**: Don't track enables yourself, the framework does it
3. **Report accurate parameters**: Provide correct voltage ranges and delays
4. **Handle parent supplies**: Set `vin-supply` in device tree for chained regulators
5. **Use atomic operations carefully**: `enabled_count` is managed by the framework

### Common Patterns

#### Power Sequencing

```c
/* Correct power-on sequence */
rt_regulator_enable(core_supply);
rt_regulator_enable(io_supply);
rt_clk_prepare_enable(clock);
/* Initialize hardware */

/* Correct power-off sequence (reverse order) */
/* Shutdown hardware */
rt_clk_disable_unprepare(clock);
rt_regulator_disable(io_supply);
rt_regulator_disable(core_supply);
```

#### Voltage Scaling

```c
/* Dynamic voltage scaling for performance modes */
switch (perf_mode) {
case PERF_HIGH:
    rt_regulator_set_voltage(cpu_supply, 1200000, 1200000);
    rt_clk_set_rate(cpu_clk, 1000000000);  /* 1GHz */
    break;
case PERF_NORMAL:
    rt_clk_set_rate(cpu_clk, 800000000);   /* 800MHz */
    rt_regulator_set_voltage(cpu_supply, 1000000, 1000000);
    break;
case PERF_LOW:
    rt_clk_set_rate(cpu_clk, 400000000);   /* 400MHz */
    rt_regulator_set_voltage(cpu_supply, 900000, 900000);
    break;
}
```

## Troubleshooting

### Common Issues

1. **Regulator not found**
   - Check device tree: Ensure `<name>-supply` property exists
   - Check compatible string: Verify regulator driver is loaded
   - Check Kconfig: Enable regulator support and driver

2. **Enable/disable balance errors**
   - Count enable/disable calls: They must match
   - Check error paths: Ensure cleanup code disables on failure
   - Use debugging: Add LOG_D calls to track reference count

3. **Voltage out of range**
   - Check device tree: Verify `regulator-min/max-microvolt` properties
   - Check hardware: Ensure physical regulator supports the voltage
   - Check parent supply: Parent must support child's voltage range

4. **Boot failures**
   - Check boot-on property: Critical regulators need `regulator-boot-on`
   - Check always-on property: Some regulators must never be disabled
   - Check sequencing: Power supplies must enable before consumers

### Debug Logging

Enable regulator debug logging:

```c
#define DBG_TAG "rtdm.regulator"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
```

Or at runtime:
```
msh> ulog_tag_lvl_set rtdm.regulator 7
```

## Performance Considerations

### Memory Usage

- Each regulator node: ~100-150 bytes
- Each consumer reference: ~16 bytes
- Device tree overhead: Depends on complexity

### Timing Considerations

- Enable delays: Specified by hardware (µs to ms)
- Ramp delays: Voltage-dependent (µs per volt)
- Notifier overhead: Linear with number of registered notifiers
- Lock contention: Minimal with per-regulator locking

### Optimization Tips

1. **Group voltage changes**: Change multiple voltages before delays
2. **Use async operations**: Don't block on regulator delays if possible
3. **Cache voltage values**: Avoid unnecessary get_voltage calls
4. **Minimize mode changes**: Mode switching can be expensive

## Related Modules

- **clk**: Clock management, often paired with regulator control
- **pinctrl**: Pin configuration, may require voltage switching
- **pmdomain**: Power domain management, higher-level power control
- **thermal**: Thermal management, may trigger voltage/frequency scaling

## References

- RT-Thread Source: `components/drivers/regulator/`
- Header File: `components/drivers/include/drivers/regulator.h`
- Device Tree Bindings: [Linux Regulator Bindings](https://www.kernel.org/doc/Documentation/devicetree/bindings/regulator/)
- [RT-Thread DM Documentation](../README.md)
