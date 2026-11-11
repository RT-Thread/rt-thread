@page page_device_power Power subsystem overview

@subpage page_device_power_supply
@subpage page_device_power_charger
@subpage page_device_power_board_reset

# Power (overview)

RT-Thread splits **power** into several layers. They are related but **not interchangeable**:

| Layer | Page | Scope |
| --- | --- | --- |
| **Regulator** | @ref page_device_regulator | Shared rails (LDO/DCDC): enable, voltage, refcount |
| **Power domain** | @ref page_device_power_domain | SoC power islands while system is running |
| **Power supply** | @ref page_device_power_supply | Battery/charger reporting (`rt_power_supply`) |
| **Board off/restart** | @ref page_device_power_board_reset | GPIO/syscon **shutdown** and **reset** |
| **System DM power** | @ref page_device_dm_power | Ordered **`rt_dm_power_off_handler`** + machine hooks |

**Reset controller** (IP block reset lines) is a different subsystem: @ref page_device_reset — not under `components/drivers/power/reset/`.

Sources under **`components/drivers/power/`**:

| Path | Role |
| --- | --- |
| **`supply/`** | `rt_power_supply` core, daemon, **`gpio-charger`**, emulator |
| **eset/** | **gpio-poweroff**, **gpio-restart**, **syscon-*** reboot/poweroff |

Power domain providers: **components/drivers/pmdomain/** (see @ref page_device_power_domain).

---

## Typical consumer `probe` order

When a platform device comes up (@ref page_device_platform):

```
pinctrl (bus)
    → clock defaults (bus)
    → power domain attach (bus)     [optional, -RT_EEMPTY OK]
    → IOMMU attach (bus)            [optional]
    → driver probe:
          regulator get/enable      [your driver]
          reset deassert / clk enable
          rt_dm_dev_iomap
          register functional device
```

For **battery/charger UI** or **PM policy**, drivers register **`rt_power_supply`** (see @ref page_device_power_supply).

For **whole-system power off / reboot**, drivers register **`rt_dm_power_off_handler`** (see @ref page_device_power_board_reset, @ref page_device_dm_power).

---

## Kconfig (`components/drivers/power/`)

| Option | Role |
| --- | --- |
| **`RT_USING_POWER_SUPPLY`** | Power supply class + workqueue |
| **`RT_POWER_SUPPLY_DAEMON`** | Poll/notify policy thread |
| **`RT_POWER_SUPPLY_CHARGER_GPIO`** | **`gpio-charger`** |
| **`RT_POWER_SUPPLY_EMU`** | Test battery/charger |
| **`RT_USING_POWER_RESET`** | Board poweroff/restart drivers |
| **`RT_POWER_RESET_GPIO_*`**, **`RT_POWER_RESET_SYSCON_*`** | In-tree reset drivers |

Regulator and power domain have separate Kconfig trees under **`components/drivers/regulator/`** and **`core/power_domain.c`**.

---

## Quick map: what to implement

| Goal | Register / API |
| --- | --- |
| Report SOC, charging, USB online | **`rt_power_supply_register`** + **`RT_PLATFORM_DRIVER_EXPORT`** |
| Shutdown PMIC / assert poweroff GPIO | **`rt_dm_power_off_handler(..., SHUTDOWN, ...)`** |
| Warm reset / recovery mode | **`rt_dm_power_off_handler(..., RESET, ...)`** + **`rt_dm_reboot_mode_register`** |
| Keep an IP block powered | **`rt_dm_power_domain_attach`** / **`rt_regulator_get`** |
| Share 3.3 V rail | **`rt_regulator_enable`** / **`put`** |

---

## See also

- @ref page_device_platform — device/driver binding
- @ref page_device_pin — GPIO for chargers and gpio-poweroff
- `components/drivers/power/Kconfig`
