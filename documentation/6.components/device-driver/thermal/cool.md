@page page_device_thermal_cool Thermal cooling devices

# Cooling devices (in-tree)

Cooling drivers implement **`struct rt_thermal_cooling_device_ops`** and register with **`rt_thermal_cooling_device_register`**. Zones reference them from **`cooling-maps`** (see @ref page_device_thermal).

| Driver | Kconfig | `compatible` (typical) |
| --- | --- | --- |
| PWM fan | **`RT_THERMAL_COOL_PWM_FAN`** | **`pwm-fan`** |
| GPIO fan | **`RT_THERMAL_COOL_GPIO_FAN`** | (see `thermal-cool-gpio-fan.c`) |
| DVFS | **`RT_THERMAL_COOL_DVFS`** | (see `thermal-cool-dvfs.c`) |

Sources: `components/drivers/thermal/thermal-cool-*.c`.

---

## PWM fan (`thermal-cool-pwm-fan.c`)

### Role

Maps thermal **cooling level** (0 … **max_level**) to **PWM duty** via optional **`cooling-levels`** LUT. Optional **`fan`** regulator supply (property resolves as supply name **`fan`** → **`rt_regulator_get(dev, "fan")`**).

### Device tree

```dts
fan0: fan {
    compatible = "pwm-fan";
    pwms = <&pwm0 0 40000>;          /* phandle, channel, period (ns) */
    cooling-levels = <0 64 128 192 255>;
    /* optional: bind regulator supply id "fan" on this node */
};
```

Referenced from zone:

```dts
cooling-device = <&fan0 0 4>;   /* min level 0, max level 4 */
```

| Property | Role |
| --- | --- |
| **`pwms`** | **`#pwm-cells`**: channel, period |
| **`cooling-levels`** | PWM scale values per level; array length − 1 = **max_level** |
| Regulator | **`rt_regulator_get(dev, "fan")`** — wire **`fan`** supply in regulator/DT as on your BSP |

### Ops behavior

| Op | Behavior |
| --- | --- |
| **`get_max_level`** | **`levels_nr - 1`** |
| **`get_cur_level`** | Current level (spinlock) |
| **`set_cur_level`** | LUT → **`rt_pwm_set`**; level 0 powers off PWM/regulator |

**Power sequence**: on — **`rt_pwm_enable`** then **`rt_regulator_enable`**; off — reverse with rollback on error.

### Probe flow

1. Parse **`pwms`**, ensure PWM controller probed (**`rt_platform_ofw_request`** if needed).
2. Optional **`rt_regulator_get(dev, "fan")`**.
3. Read **`cooling-levels`** array.
4. **`rt_thermal_cooling_device_register`** — attaches default **`dumb`** governor.
5. Initial **`set_cur_level(0)`** (fan off).

Platform driver: **`RT_PLATFORM_DRIVER_EXPORT(pwm_fan_cool_driver)`**.

---

## GPIO fan (`thermal-cool-gpio-fan.c`)

**Kconfig**: **`RT_THERMAL_COOL_GPIO_FAN`** (**`RT_USING_PIN`**, **`RT_USING_OFW`**).

Controls fan speed via **GPIO pins** and a **speed table** (RPM / control value). Suitable for multi-wire fan tach/control GPIOs rather than PWM.

Inspect **`gpio_fan_cool_probe`** in the source for exact property names on your BSP.

---

## DVFS cooling (`thermal-cool-dvfs.c`)

**Kconfig**: **`RT_THERMAL_COOL_DVFS`** + **`RT_USING_DVFS`**.

Exposes **OPP table indices** as cooling levels — **`set_cur_level`** selects a lower performance point. Use when passive trip should throttle CPU/GPU frequency instead of spinning a fan.

---

## Integration checklist

1. **Register cooling device** in platform **`probe`** before dependent zone (or rely on init order).
2. Set **`parent.ofw_node`** on **`rt_thermal_cooling_device.parent`** so **`thermal_ofw_setup`** can match **`cooling-device`** phandles.
3. Define **`cooling-levels`** (PWM) or max level in ops consistently with DT **`cooling-device`** min/max cells.
4. Zone **`cooling-maps`** **`trip`** must point at a trip node parsed under the same thermal zone.
5. Test with **`rt_thermal_zone_device_update`** or wait for poller — verify **`set_cur_level`** at each trip.

---

## Pitfalls

- **Level 0**: PWM driver turns off output; confirm acoustic/thermal spec allows full stop.
- **Regulator + PWM order**: supply must match driver sequence (enable PWM before rail or as coded).
- **`set_cur_level` in ISR**: uses spinlock — do not call from ISR.
- **Governor**: **`dumb`** only nudges level on temperature delta vs **`hysteresis`** — custom governor may be needed for fine control.

---

## See also

- @ref page_device_thermal
- @ref page_device_pwm
- @ref page_device_regulator
- @ref page_device_pin
- `components/drivers/thermal/thermal-cool-pwm-fan.c`
