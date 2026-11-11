@page page_device_pinctrl Pin control (pinctrl)

# Pinctrl subsystem

Pinctrl applies **device-tree pin configurations** (mux, pull, drive strength, and related pad settings) before or during driver **`probe`**.

- Core: **`components/drivers/pinctrl/pinctrl.c`**
- API / **`PIN_CONFIG_*`**: **`components/drivers/include/drivers/dev_pin.h`**

**Kconfig**: **`RT_USING_PINCTRL`** (requires **`RT_USING_DM`** and **`RT_USING_PIN`**). BSP may add more providers via **`SOC_DM_PINCTRL_DIR`**.

---

## End-to-end flow

### 1. Device tree (consumer)

The **consumer** node (UART, I2C, SPI, …) references **config subnodes** under a pinctrl controller:

| Property | Role |
| --- | --- |
| **`pinctrl-0`**, **`pinctrl-1`**, … | Phandles to config subnodes (one **state** per index) |
| **`pinctrl-names`** | Names for each index: `"default"`, `"sleep"`, `"active"`, … |

```dts
uart0: serial@40000000 {
    compatible = "vendor,uart";
    reg = <0x40000000 0x1000>;
    pinctrl-names = "default", "sleep";
    pinctrl-0 = <&uart0_pins>;
    pinctrl-1 = <&uart0_sleep_pins>;
};

pinctrl: pinctrl@20000000 {
    compatible = "vendor,pinctrl";
    reg = <0x20000000 0x1000>;

    uart0_pins: uart0-pins {
        /* properties interpreted by the provider driver */
    };
};
```

**`pinctrl-0`** may contain **several** phandles (e.g. separate SCL/SDA nodes). They are applied **in order**; the first error stops the rest.

Phandles must target a **config child** of the controller, not the controller root nor the consumer itself (see comment in **`ofw_pin_ctrl_confs_apply()`**).

### 2. Core apply (`pinctrl.c`)

For **`rt_pin_ctrl_confs_apply(dev, index)`** (or after name lookup):

```
foreach phandle in consumer's "pinctrl-<index>":
    conf_np  = node from phandle
    walk parents until node has "compatible"  →  provider_np
    if !rt_ofw_data(provider_np):
        rt_platform_ofw_request(provider_np)
    pinctrl = rt_ofw_data(provider_np)   /* struct rt_device_pin * */
    pinctrl->ops->pin_ctrl_confs_apply(&pinctrl->parent, conf_np)
```

### 3. Provider

The **provider** is a platform driver for the pinctrl controller. At **`probe`** it typically:

1. Maps **`reg`**, enables clock/reset.
2. Sets **`struct rt_pin_ops.pin_ctrl_confs_apply`** to parse **`fw_conf_np`** and program hardware.
3. Sets **`rt_ofw_data(controller_ofw_node) = &struct rt_device_pin.parent`**.

Optional: **`pin_ctrl_gpio_request`** — pad setup when the GPIO layer claims a line (**`pin_gpio_request`** in **`dev_pin_dm.c`**).

### 4. Platform bus (automatic)

**`platform_probe()`** runs **before** the driver **`probe`**:

```c
#ifdef RT_USING_PINCTRL
    if (rt_pin_ctrl_confs_apply_by_name(dev, RT_NULL))   /* "default" */
    {
        rt_pin_ctrl_confs_apply(dev, 0);                 /* fallback pinctrl-0 */
    }
#endif
```

So most drivers only need correct DT; they do **not** need to call pinctrl in **`probe`** unless switching states at runtime.

Full platform order: @ref page_device_platform.

---

## Usage

### Consumer driver (typical)

**Boot-time mux** — no code; define **`pinctrl-names`** + **`pinctrl-0`** (and extra states if needed).

**Runtime state change** (sleep, high-speed, etc.):

```c
/* By name */
rt_pin_ctrl_confs_apply_by_name(&pdev->parent, "active");

/* By index */
rt_ssize_t idx = rt_pin_ctrl_confs_lookup(&pdev->parent, "high-speed");
if (idx >= 0)
    rt_pin_ctrl_confs_apply(&pdev->parent, (int)idx);
```

**`name == NULL`** in **`rt_pin_ctrl_confs_apply_by_name`** means **`"default"`**.

Some drivers (**`regulator-fixed`**, **`led-gpio`**, …) call apply again before using GPIO-related pads so DT and hardware stay aligned.

### Public API

| API | Role |
| --- | --- |
| **`rt_pin_ctrl_confs_lookup(dev, name)`** | Index in **`pinctrl-names`**; **`-RT_EEMPTY`** if missing |
| **`rt_pin_ctrl_confs_apply(dev, index)`** | Apply all phandles in **`pinctrl-<index>`** |
| **`rt_pin_ctrl_confs_apply_by_name(dev, name)`** | Lookup + apply |

Without **`RT_USING_OFW`**: **`-RT_ENOSYS`**.

| Return | Meaning |
| --- | --- |
| **`RT_EOK`** | State applied |
| **`-RT_EEMPTY`** | No property / no name |
| **`-RT_ERROR`** | Provider missing or no **`pin_ctrl_confs_apply`** |
| **`-RT_EIO`** | Bad phandle |

### Provider driver (BSP)

1. Embed **`struct rt_device_pin`** (usually first member of private struct).
2. Implement **`pin_ctrl_confs_apply(device, fw_conf_np)`** — read provider-specific properties on **`fw_conf_np`** and write pad registers (or firmware, etc.).
3. **`rt_ofw_data(dev->ofw_node) = &pin_dev->parent`** at end of probe.
4. Document your binding (property names and cell layout) in the BSP; the core does not parse SoC-specific tuples.

**`PIN_CONFIG_*`** in **`dev_pin.h`** are generic semantic types; providers map DT properties to hardware as needed.

---

## DT layout example (multi-phandle)

From **`pinctrl.c`** comments — one consumer, two phandles, two config nodes:

```dts
i2c@4700 {
    pinctrl-names = "default";
    pinctrl-0 = <&i2c_pin_scl, &i2c_pin_sda>;
};

&pinctrl {
    i2c_pin_scl { /* provider-specific */ };
    i2c_pin_sda { /* provider-specific */ };
};
```

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Provider not probed | Register platform driver; core calls **`rt_platform_ofw_request`** |
| Wrong phandle | Must point to **config subnode** under controller |
| Name / index mismatch | **`rt_pin_ctrl_confs_lookup`** string must match **`pinctrl-names`** |
| Partial apply | First failing phandle aborts the list |
| No **`rt_ofw_data`** | Provider **`probe`** must set it on controller node |
| Runtime PM | Add **`pinctrl-1`** + **`"sleep"`**; **`apply_by_name`** on suspend/resume |

---

## See also

- @ref page_device_platform — probe order
- @ref page_device_ofw — phandles
- `components/drivers/pinctrl/pinctrl.c`
- `components/drivers/core/platform.c`
