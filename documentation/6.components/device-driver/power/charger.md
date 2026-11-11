@page page_device_power_charger Charger (gpio-charger)

# Charger as `rt_power_supply`

Chargers are **not** a separate class. A charger is a **`struct rt_power_supply`** with USB/mains **`type`** and properties such as **`ONLINE`**, **`STATUS`**, **`CONSTANT_CHARGE_CURRENT_MAX`**.

Core registration flow: @ref page_device_power_supply.

**Kconfig**: **`RT_POWER_SUPPLY_CHARGER_GPIO`** → **`components/drivers/power/supply/gpio-charger.c`**.

---

## Registration flow (`gpio-charger`)

```
RT_PLATFORM_DRIVER_EXPORT(gpio_charger_driver)
        |
        v
gpio_charger_probe(pdev)
        |
        +-- rt_pin_get_named_pin (VBUS / status GPIOs)
        +-- optional charge-current-limit GPIOs + mapping table
        +-- parse charger-type → psy->type
        +-- build gpio_charger_properties[] (only supported props)
        +-- psy->dev = &pdev->parent; psy->ops = &gpio_charger_ops
        +-- rt_power_supply_register(&gpioc->parent)
        +-- GPIO IRQ → gpio_charger_isr → rt_power_supply_changed()
```

---

## Device tree (typical)

```dts
charger {
    compatible = "gpio-charger";
    charger-type = "usb-dcp";
    gpios = <&gpio0 12 GPIO_ACTIVE_HIGH>;          /* online */
    charge-status-gpios = <&gpio0 13 GPIO_ACTIVE_LOW>;
    charge-current-limit-gpios = <&gpio0 14>, <&gpio0 15>;
    charge-current-limit-mapping = <100000 0>, <500000 1>, <1500000 3>;
};
```

Properties actually exposed depend on which GPIOs/mapping are present — the driver builds **`properties[]`** dynamically in **`probe`**.

---

## `get_property` / `set_property`

| Property | Behavior |
| --- | --- |
| **`ONLINE`** | Read VBUS GPIO |
| **`STATUS`** | Charging vs not from **`charge-status`** GPIO |
| **`CONSTANT_CHARGE_CURRENT_MAX`** | Mapping table + limit GPIOs; **`set_property`** selects limit |

---

## Emulator

**`emu-power.c`** (**`RT_POWER_SUPPLY_EMU`**): registers test battery + charger; MSH **`emu_charger`** toggles state for thermal/PM tests.

---

## See also

- @ref page_device_power_supply
- @ref page_device_regulator
- @ref page_device_pin
- `components/drivers/power/supply/gpio-charger.c`
