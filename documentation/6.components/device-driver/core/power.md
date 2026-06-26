@page page_device_dm_power System power off and reboot (core)

# DM power control (`power.h`)

Header: `components/drivers/include/drivers/core/power.h`. Implementation: `components/drivers/core/power.c`.

This layer handles **system-wide shutdown and reset**, **ordered power-off callbacks**, and **reboot mode** strings—not battery/charger UI (**`documentation/6.components/device-driver/power/supply.md`**) and not per-IP **power domains** (**`documentation/6.components/device-driver/power_domain/power_domain.md`**).

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| **Callback context** | **`rt_dm_power_off_handler`** callbacks run from **`rt_hw_cpu_shutdown` / `rt_hw_cpu_reset`** paths—may be IRQ or dedicated power thread; **do not sleep** unless your platform guarantees thread context. |
| **Priority bands** | Handlers run **low index first** within each **`rt_dm_power_off_priority`** level, then next priority—register reboot-mode notifiers at **`RT_DM_POWER_OFF_PRIO_HIGH`** if they must run before generic GPIO poweroff. |
| **`-RT_EEMPTY` on domain attach** | **`rt_dm_power_domain_attach`** returning **`-RT_EEMPTY`** means no **`power-domains`** in DTS—often OK; RPMsg/platform code treats it as non-fatal. |

## Power-off handlers

```c
rt_err_t rt_dm_power_off_handler(struct rt_device *dev, int mode, int priority,
        rt_err_t (*callback)(struct rt_device *));
```

| `mode` | Use |
| --- | --- |
| `RT_DM_POWER_OFF_MODE_SHUTDOWN` | Full power down (PMIC off, etc.). |
| `RT_DM_POWER_OFF_MODE_RESET` | Warm reset path before **`rt_hw_cpu_reset`**. |

| `priority` (increasing order) | Typical registrant |
| --- | --- |
| `RT_DM_POWER_OFF_PRIO_PLATFORM` | SoC-specific flush |
| `RT_DM_POWER_OFF_PRIO_LOW` / `DEFAULT` / `HIGH` | Drivers, storage sync |
| `RT_DM_POWER_OFF_PRIO_FIRMWARE` | Last-chance firmware handoff |

Registration appends to a per-mode, per-priority singly linked list. On shutdown/reset the core walks **all priority levels** and invokes each callback; a non-**`RT_EOK`** return is logged but does not stop later handlers.

**Examples:** `components/drivers/power/reset/gpio-poweroff.c` and **`gpio-restart.c`** register GPIO drivers via **`rt_dm_power_off_handler`**.

## Machine hooks

```c
extern void (*rt_dm_machine_shutdown)(void);
extern void (*rt_dm_machine_reset)(void);
```

BSP or SoC code sets these to enter PMIC/PSCI/firmware sequences after DM handlers run.

## Reboot mode

```c
rt_err_t rt_dm_reboot_mode_register(struct rt_device *dev,
        rt_err_t (*callback)(struct rt_device *, char *cmd));
rt_err_t rt_dm_reboot_mode_unregister(struct rt_device *dev);
void rt_hw_cpu_reset_mode(char *cmd);
```

- **`rt_hw_cpu_reset_mode`** updates the global command string (e.g. **`"recovery"`**) and calls **`rt_hw_cpu_reset()`**.
- On reset, handlers registered at **`RT_DM_POWER_OFF_MODE_RESET`** run—core init registers **`dm_reboot_notifiy`** at **`RT_DM_POWER_OFF_PRIO_HIGH`** to apply reboot-mode callbacks before the CPU resets.

Use **`syscon-reboot-mode`** / NVMEM-backed mode drivers to persist **`cmd`** across boots.

## Relation to power domains

**`rt_dm_power_domain_attach(dev, on)`** (in **`power_domain.h`**) is called from **`platform` probe** and some buses (e.g. RPMsg) to power **on** the device’s IP block **before** driver init. That is independent of **system** shutdown:

| API | Scope |
| --- | --- |
| `rt_dm_power_domain_*` | Per-device SoC power island while system is running. |
| `rt_dm_power_off_handler` | Whole-system off/reset. |
| `rt_power_supply_*` | Charger/battery reporting. |

Recommended order for a consumer **`probe`**: **regulator enable → power domain on → clock/reset → `rt_dm_dev_iomap`**.

## Pitfalls

- **Missing `rt_dm_machine_shutdown`**: handlers run but hardware never powers off—set machine hooks in BSP.
- **Reboot mode without storage**: **`cmd`** is RAM-only unless a **`reboot-mode`** driver writes persistent storage.
- **GPIO poweroff polarity**: wrong active level looks like “hang on shutdown”—verify DTS and **`gpio-poweroff`** properties.

## See also

- Power domains: `documentation/6.components/device-driver/power_domain/power_domain.md`
- Power supply (battery/charger): `documentation/6.components/device-driver/power/supply.md`
- Regulator: `documentation/6.components/device-driver/regulator/regulator.md`
- Syscon reboot: `components/drivers/power/reset/syscon-reboot.c`, `syscon-reboot-mode.c`
- DM helpers: `documentation/6.components/device-driver/core/dm.md`
- Header: `components/drivers/include/drivers/core/power.h`
