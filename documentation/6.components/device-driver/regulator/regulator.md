@page page_device_regulator Regulator

# Regulator subsystem

Headers: **`components/drivers/include/drivers/regulator.h`**, **`components/drivers/regulator/regulator_dm.h`**. Core: **`components/drivers/regulator/regulator.c`**, DT parse: **`regulator_dm.c`**.

Models **LDO/DCDC/load switches** as **`struct rt_regulator_node`** (provider) and opaque **`struct rt_regulator`** (consumer handle). **Misuse can damage hardware** — use only the public API.

**Kconfig**: **`RT_USING_REGULATOR`** (requires **`RT_USING_DM`**). In-tree: **`regulator-fixed`**, **`regulator-gpio`**, **`regulator-pwm`**, **`regulator-fan53555`**, **`regulator-scmi`**, plus **`SOC_DM_REGULATOR_DIR`**.

---

## End-to-end flow

### Provider (rail definition)

```
Platform/PMIC driver probe
        |
        v
regulator_ofw_parse(np, &param)     /* DT limits, boot-on, always-on */
        |
        v
Fill rt_regulator_ops (enable, set_voltage, ...)
        |
        v
rt_regulator_register(reg_np)
        |
        +-- rt_ofw_data(regulator_np) = reg_np
        +-- optional: boot_on / always_on → enable at register
```

### Consumer (device that needs a rail)

```
Consumer probe (after regulator provider probed)
        |
        v
reg = rt_regulator_get(dev, "vcc")   /* DT: vcc-supply = <&reg_xyz> */
        |
        v
rt_regulator_set_voltage(reg, min_uv, max_uv)   /* before enable on some PMICs */
rt_regulator_enable(reg)
        |
        v
... use hardware ...
        |
        v
rt_regulator_disable(reg)
rt_regulator_put(reg)
```

**Not automatic**: unlike power domains, **`platform_probe` does not enable regulators** — the consumer driver must **`get` / `enable`** in **`probe`** and **`disable` / `put`** in **`remove`**.

Recommended order with other power (@ref page_device_power): **regulator → power domain → clock/reset → iomap**.

---

## Registering a regulator (important)

### Requirements for `rt_regulator_register`

| Field | Required |
| --- | --- |
| **`reg_np->dev`** | Owning **`rt_device`** (usually **`&pdev->parent`** of provider) |
| **`reg_np->param`** | **`struct rt_regulator_param`** (name, voltage/current limits, delays, flags) |
| **`reg_np->ops`** | At least **`enable`/`disable`** (and **`set_voltage`/`get_voltage`** if adjustable) |
| **`reg_np->supply_name`** | Rail name (often **`param->name`** from **`regulator-name`**) |

```c
struct my_regulator {
    struct rt_regulator_node node;
    struct rt_regulator_param param;
};

static const struct rt_regulator_ops my_ops = {
    .enable = my_enable,
    .disable = my_disable,
    .set_voltage = my_set_voltage,
    .get_voltage = my_get_voltage,
};

static rt_err_t my_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct my_regulator *r = rt_calloc(1, sizeof(*r));

    regulator_ofw_parse(dev->ofw_node, &r->param);

    r->node.dev = dev;
    r->node.param = &r->param;
    r->node.supply_name = r->param.name;
    r->node.ops = &my_ops;

    return rt_regulator_register(&r->node);
}
```

On success with **`RT_USING_OFW`**: **`rt_ofw_data(dev->ofw_node) = reg_np`** so consumers can resolve phandles.

**`boot_on` / `always_on`** in **`param`**: **`register`** calls **`regulator_enable`** immediately.

### Platform driver export

**`regulator-fixed`** pattern:

```c
RT_PLATFORM_DRIVER_EXPORT(regulator_fixed_driver);
/* or INIT_SUBSYS_EXPORT + rt_platform_driver_register */
```

Provider must probe **before** consumers that call **`rt_regulator_get`** (or **`get`** will **`rt_platform_ofw_request`** the regulator node).

---

## Device tree

**Regulator node** (provider):

```dts
vcc_3v3: regulator-3v3 {
    compatible = "regulator-fixed";
    regulator-name = "vcc";
    regulator-min-microvolt = <3300000>;
    regulator-max-microvolt = <3300000>;
    regulator-boot-on;
    gpio = <&gpio0 10 GPIO_ACTIVE_HIGH>;
};
```

**Consumer**:

```dts
mmc@ffe00000 {
    compatible = "vendor,mmc";
    vmmc-supply = <&vcc_3v3>;
    vqmmc-supply = <&vcc_1v8>;
};
```

| Consumer property | Lookup |
| --- | --- |
| **`vcc-supply`** | **`rt_regulator_get(dev, "vcc")`** |
| **`vqmmc-supply`** | **`rt_regulator_get(dev, "vqmmc")`** |

**Parent rail**: regulator node may have **`vin-supply`**; **`rt_regulator_get`** links **`parent`** via **`regulator_check_parent`** for enable/disable/voltage propagation up the tree.

---

## Consumer API

| API | Role |
| --- | --- |
| **`rt_regulator_get(dev, id)`** | Resolve **`{id}-supply`** phandle → allocate **`struct rt_regulator`**, **`ref_get`** on node |
| **`rt_regulator_put(reg)`** | **`ref_put`**; may **`unregister`** node when last reference |
| **`rt_regulator_enable(reg)`** | Enable rail (parent first); applies **`enable_delay`** |
| **`rt_regulator_disable(reg)`** | Consumer refcount then hardware off when last user |
| **`rt_regulator_set_voltage(reg, min, max)`** | Notifiers + **`set_voltage`**; parent voltage updated too |
| **`rt_regulator_get_voltage(reg)`** | Read back µV |
| **`rt_regulator_is_supported_voltage(reg, min, max)`** | Check against **`param`** range |
| **`rt_regulator_set_mode` / `get_mode`** | Optional PMIC modes |

### Enable / disable sharing

Multiple consumers on one rail:

- First **`enable`**: runs hardware **`ops->enable`**, bumps internal **`enabled_count`**.
- Further **`enable`**: if already on, returns **`RT_EOK`** immediately.
- **`disable`**: decrements consumer **`enabled_count`** until zero, then hardware **`disable`**.

Each consumer should still call **`enable`/`disable`/`put`** symmetrically.

### Notifiers

```c
static rt_err_t my_notifier(struct rt_regulator_notifier *n,
        rt_ubase_t msg, void *data)
{
    /* RT_REGULATOR_MSG_ENABLE, DISABLE, VOLTAGE_CHANGE, ... */
    return RT_EOK;
}

struct rt_regulator_notifier notifier = { .callback = my_notifier };
rt_regulator_notifier_register(reg, &notifier);
```

Keep callbacks short — they may run under regulator lock.

---

## `struct rt_regulator_param` (DT via `regulator_ofw_parse`)

| DT property | `param` field |
| --- | --- |
| **`regulator-name`** | **`name`** |
| **`regulator-min/max-microvolt`** | **`min_uvolt` / `max_uvolt`** |
| **`regulator-min/max-microamp`** | **`min_uamp` / `max_uamp`** |
| **`regulator-boot-on`** | **`boot_on`** |
| **`regulator-always-on`** | **`always_on`** |
| **`enable-active-high`** | **`enable_active_high`** |
| **`regulator-ramp-delay`** | **`ramp_delay`** (or **`ramp_disable`**) |
| **`regulator-enable-ramp-delay`** | **`enable_delay`** |

---

## In-tree provider drivers (reference)

| Driver | Compatible / binding | Registration |
| --- | --- | --- |
| **fixed** | **`regulator-fixed`** | GPIO enable, **`regulator_ofw_parse`**, **`rt_regulator_register`** |
| **gpio** | GPIO-controlled rail | Same pattern |
| **pwm** | PWM duty → voltage | **`RT_REGULATOR_PWM`** |
| **fan53555** | I2C PMIC | **`RT_REGULATOR_FAN53555`** |
| **scmi** | SCMI voltage protocol | **`RT_REGULATOR_SCMI`** |

---

## Example: consumer in `probe`

```c
static rt_err_t my_drv_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rt_regulator *vcc;
    rt_err_t err;

    vcc = rt_regulator_get(dev, "vcc");
    if (rt_is_err(vcc))
        return rt_ptr_err(vcc);

    if (!rt_regulator_is_supported_voltage(vcc, 3300000, 3300000))
    {
        err = -RT_EINVAL;
        goto err_put;
    }

    err = rt_regulator_set_voltage(vcc, 3300000, 3300000);
    if (err)
        goto err_put;

    err = rt_regulator_enable(vcc);
    if (err)
        goto err_put;

    /* iomap, clocks, ... */
    pdev->priv = vcc;
    return RT_EOK;

err_put:
    rt_regulator_put(vcc);
    return err;
}

static rt_err_t my_drv_remove(struct rt_platform_device *pdev)
{
    struct rt_regulator *vcc = pdev->priv;

    rt_regulator_disable(vcc);
    rt_regulator_put(vcc);
    return RT_EOK;
}
```

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Provider not registered | **`get`** fails — ensure regulator **`probe`** runs first or defer consumer |
| Wrong property name | **`id`** must match **`{id}-supply`** in DT |
| **Enable before voltage** | Many PMICs need **`set_voltage`** then **`enable`** |
| **Skip `put`** | Leaks **`struct rt_regulator`** and node **`ref`** |
| **`set_voltage` in IRQ** | May sleep (I2C PMIC) |
| **Shared rail** | One consumer lowering voltage affects all — coordinate in DT |
| Bypass framework | Do not write PMIC registers from random drivers |
| **`always_on` rail** | **`disable`** may no-op in ops — still call **`put`** |

---

## See also

- @ref page_device_power — probe ordering
- @ref page_device_power_domain
- @ref page_device_platform — provider **`RT_PLATFORM_DRIVER_EXPORT`**
- @ref page_device_pin — GPIO enables on **regulator-fixed**
- `components/drivers/regulator/regulator.c`
- `components/drivers/regulator/regulator-fixed.c`
