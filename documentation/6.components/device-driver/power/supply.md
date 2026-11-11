@page page_device_power_supply Power supply

# Power supply (`rt_power_supply`)

Header: **`components/drivers/include/drivers/power_supply.h`**. Core: **`components/drivers/power/supply/supply.c`**.

Models **batteries, USB ports, mains**, etc. as property objects (Linux power_supply–like). Chargers use the **same class** — @ref page_device_power_charger.

**Kconfig**: **`RT_USING_POWER_SUPPLY`**, optional **`RT_POWER_SUPPLY_DAEMON`**.

---

## Architecture

```
Platform driver probe
        |
        v
  Fill struct rt_power_supply (type, properties, ops, dev)
        |
        v
  rt_power_supply_register(psy)
        |
        +-- global list + rt_ofw_data(np) = psy
        +-- optional thermal zone (PROP_TEMP)
        +-- changed_work for notifiers / LED update
        |
        v
  Consumers: rt_power_supply_get_property / notifier / daemon
```

There is **no separate platform bus** for power supplies: the **platform driver** owns **`struct rt_platform_device`**, and the **`rt_power_supply`** hangs off **`psy->dev = &pdev->parent`**.

---

## Registering a power supply (important)

### 1. Platform driver (`RT_PLATFORM_DRIVER_EXPORT`)

Bind to DT with **`compatible`**, then register the supply in **`probe`**:

```c
struct my_psy_priv {
    struct rt_power_supply psy;
    /* hardware state */
};

static enum rt_power_supply_property my_props[] = {
    RT_POWER_SUPPLY_PROP_STATUS,
    RT_POWER_SUPPLY_PROP_CAPACITY,
};

static rt_err_t my_get_property(struct rt_power_supply *psy,
        enum rt_power_supply_property prop, union rt_power_supply_property_val *val)
{
    /* read hardware, fill val->intval or val->strval */
    return RT_EOK;
}

static const struct rt_power_supply_ops my_ops = {
    .get_property = my_get_property,
};

static rt_err_t my_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct my_psy_priv *priv = rt_calloc(1, sizeof(*priv));

    priv->psy.dev = dev;
    priv->psy.type = RT_POWER_SUPPLY_TYPE_BATTERY;
    priv->psy.properties = my_props;
    priv->psy.properties_nr = RT_ARRAY_SIZE(my_props);
    priv->psy.ops = &my_ops;

    return rt_power_supply_register(&priv->psy);
}

static rt_err_t my_remove(struct rt_platform_device *pdev)
{
    struct my_psy_priv *priv = rt_dm_dev_get_fwdata(&pdev->parent);
    rt_power_supply_unregister(&priv->psy);
    rt_free(priv);
    return RT_EOK;
}
```

Reference: **`gpio-charger.c`** — **`RT_PLATFORM_DRIVER_EXPORT(gpio_charger_driver)`**.

### 2. `rt_power_supply_register` requirements

| Field | Required |
| --- | --- |
| **`psy->dev`** | Yes — usually **`&pdev->parent`** |
| **`psy->ops`** + **`properties`** + **`properties_nr`** | Yes, unless **`battery_info`** is set (static battery descriptor path) |
| **`psy->type`** | Set before register (USB type, battery, mains, …) |
| **`psy->battery_info`** | Alternative to dynamic properties for some battery profiles |

On success:

- Inserts **`psy`** into global list
- **`rt_dm_dev_bind_fwdata(psy->dev, NULL, psy)`** when **`dev->ofw_node`** is set
- Initializes **`changed_work`** for **`rt_power_supply_changed()`**

**`rt_power_supply_unregister`**: removes from list; fails with **`-RT_EBUSY`** if **`rt_power_supply_get`** refcount > 1.

### 3. Optional: `set_property`

Implement **`ops->set_property`** for writable limits (e.g. charge current). Only properties listed in **`properties[]`** are exposed via **`rt_power_supply_set_property`**.

### 4. Notify userspace / daemon / LED

After hardware state changes (GPIO IRQ, PMIC interrupt):

```c
rt_power_supply_changed(psy);
```

This queues **`power_supply_changed_work`**, which:

- Updates bound **`led_dev`** if **`RT_USING_LED`**
- Calls all **`rt_power_supply_notifier`** callbacks

Register a notifier:

```c
static rt_err_t my_notify(struct rt_power_supply_notifier *n,
        struct rt_power_supply *psy) { ... return RT_EOK; }

static struct rt_power_supply_notifier n = {
    .callback = my_notify,
};
rt_power_supply_notifier_register(&n);
```

**`RT_POWER_SUPPLY_DAEMON`**: built-in notifier drives low-battery / PM hints when **`RT_USING_PM`**.

---

## Property API

```c
rt_err_t rt_power_supply_get_property(psy, prop, &val);
rt_err_t rt_power_supply_set_property(psy, prop, &val);
```

**`get_property`** only succeeds if **`prop`** is in **`psy->properties[]`** (or **`battery_info`** path for supported static props).

Common properties: **`STATUS`**, **`CAPACITY`**, **`ONLINE`**, **`VOLTAGE_NOW`**, **`CURRENT_NOW`**, **`TEMP`**, **`CONSTANT_CHARGE_CURRENT_MAX`**, … — see enum in **`power_supply.h`**.

---

## Lookup from another device

```c
struct rt_power_supply *psy = rt_power_supply_get(consumer_dev, "battery");
if (rt_is_err(psy))
    ...
rt_power_supply_get_property(psy, RT_POWER_SUPPLY_PROP_CAPACITY, &val);
rt_power_supply_put(psy);
```

**`id`** is a **DT phandle property name** on **`consumer_dev`** (e.g. **`power-supply = <&bat>`** → **`"power-supply"`**). Resolves **`rt_ofw_data`** on the supply’s OFW node after register.

---

## DT consumer example

```dts
thermal-zone {
    polling-delay = <1000>;
    thermal-sensors = <&bat>;
};

bat: battery {
    compatible = "vendor,fuel-gauge";
    monitored-battery;
};
```

Fuel-gauge driver **`probe`** registers **`rt_power_supply`** on node **`bat`**. Thermal references **`&bat`** via **`rt_power_supply_thermal_register`** when **`PROP_TEMP`** exists.

---

## Integration

| Subsystem | Hook |
| --- | --- |
| **LED** | Assign **`psy->led_dev`** before register; **`changed`** updates indicators |
| **Thermal** | **`power_supply_thermal_register`** if **`PROP_TEMP`** |
| **Regulator** | Charger **`set_property`** may adjust rails (see **`gpio-charger`**) |
| **PM** | Daemon may request sleep modes on low SOC |

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Register before **`psy->dev`** set | **`register`** returns **`-RT_EINVAL`** |
| Empty **`properties`** | Must list every prop **`get_property`** handles |
| Forget **`rt_power_supply_changed`** | Notifiers/LED/PM stay stale |
| **`unregister` with active get** | **`put`** all references first |
| **`get_property` from ISR** | Defer to workqueue; gauge I2C may block |
| Stale SOC cache | Re-read hardware in **`get_property`** |

---

## See also

- @ref page_device_power — stack overview
- @ref page_device_power_charger — **`gpio-charger`**
- @ref page_device_platform — driver export
- `components/drivers/power/supply/supply.c`
