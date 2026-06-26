@page page_device_power_board_reset Board poweroff and restart

# Board-level shutdown and restart

**`components/drivers/power/reset/`** — drivers that hook **system-wide** power off or CPU reset, not per-IP reset lines (@ref page_device_reset).

**Kconfig**: **`RT_USING_POWER_RESET`**, plus **`RT_POWER_RESET_GPIO_*`** or **`RT_POWER_RESET_SYSCON_*`**.

API header: **`components/drivers/include/drivers/core/power.h`** — details in @ref page_device_dm_power.

---

## Registration model

These drivers are **platform drivers** whose **`probe`** registers a **callback** with the DM power core. They do **not** register a char device for normal I/O.

```
RT_PLATFORM_DRIVER_EXPORT(gpio_poweroff_driver)
        |
        v
gpio_poweroff_probe(pdev)
        |
        +-- parse GPIO (rt_pin_get_named_pin) or syscon reg
        +-- rt_dm_power_off_handler(dev, MODE, PRIORITY, callback)
        |
        v
On rt_hw_cpu_shutdown() / rt_hw_cpu_reset():
        walk handlers by priority → callback → rt_dm_machine_shutdown/reset
```

### `rt_dm_power_off_handler`

```c
rt_err_t rt_dm_power_off_handler(struct rt_device *dev, int mode, int priority,
        rt_err_t (*callback)(struct rt_device *));
```

| `mode` | When invoked |
| --- | --- |
| **`RT_DM_POWER_OFF_MODE_SHUTDOWN`** | System power off (**`rt_hw_cpu_shutdown`**) |
| **`RT_DM_POWER_OFF_MODE_RESET`** | Warm reset path (**`rt_hw_cpu_reset`**) |

| `priority` (low → high) | Typical use |
| --- | --- |
| **`RT_DM_POWER_OFF_PRIO_PLATFORM`** | SoC flush |
| **`RT_DM_POWER_OFF_PRIO_LOW` / `DEFAULT` / `HIGH`** | Drivers, filesystem sync |
| **`RT_DM_POWER_OFF_PRIO_FIRMWARE`** | Last handoff |

Callbacks run in order; non-**`RT_EOK`** is logged but later handlers still run.

**`dev`**: passed to callback as **`dev->user_data`** context holder (GPIO drivers store private struct in **`user_data`**).

---

## In-tree drivers

| Driver | Compatible / binding | Registration |
| --- | --- | --- |
| **`gpio-poweroff`** | **`gpio-poweroff`** | **`RT_DM_POWER_OFF_MODE_SHUTDOWN`**, **`rt_pin_get_named_pin`** |
| **`gpio-restart`** | **`gpio-restart`** | **`RT_DM_POWER_OFF_MODE_RESET`** |
| **`syscon-poweroff`** | syscon reg | MMIO write in callback |
| **`syscon-reboot`** | syscon reg | reset trigger |
| **`syscon-reboot-mode`** | NVMEM + syscon | **`rt_dm_reboot_mode_register`** |

All use **`RT_PLATFORM_DRIVER_EXPORT`** except some syscon drivers use **`INIT_SUBSYS_EXPORT` + `rt_platform_driver_register`** (same binding, different init level — see @ref page_device_platform).

### GPIO poweroff example (flow)

```c
static rt_err_t gpio_poweroff_do_poweroff(struct rt_device *dev)
{
    struct gpio_poweroff *gp = dev->user_data;
    /* assert GPIO sequence, mdelay per DT timeout-ms */
    return RT_EOK;
}

static rt_err_t gpio_poweroff_probe(struct rt_platform_device *pdev)
{
    ...
    dev->user_data = gp;
    return rt_dm_power_off_handler(dev, RT_DM_POWER_OFF_MODE_SHUTDOWN,
            RT_DM_POWER_OFF_PRIO_DEFAULT, gpio_poweroff_do_poweroff);
}
RT_PLATFORM_DRIVER_EXPORT(gpio_poweroff_driver);
```

DT:

```dts
poweroff {
    compatible = "gpio-poweroff";
    gpios = <&gpio0 99 GPIO_ACTIVE_HIGH>;
    timeout-ms = <3000>;
    active-delay-ms = <100>;
    inactive-delay-ms = <100>;
};
```

---

## Reboot mode

```c
rt_dm_reboot_mode_register(dev, reboot_mode_callback);
rt_hw_cpu_reset_mode("recovery");  /* sets cmd + rt_hw_cpu_reset() */
```

**`syscon-reboot-mode`** persists mode to NVMEM/syscon so the next boot loader can read it. See **`reboot-mode.h`**, @ref page_device_dm_power.

---

## Machine hooks

BSP sets after handlers:

```c
rt_dm_machine_shutdown = board_shutdown;  /* PMIC off */
rt_dm_machine_reset = board_reset;        /* PSCI / watchdog */
```

Without these, callbacks may run but SoC never powers off.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Wrong GPIO polarity | Match **`gpios`** flags and **`active_value`** from **`rt_pin_get_named_pin`** |
| **`RT_USING_PINCTRL` off** for gpio-poweroff | Kconfig depends on pinctrl for pad mux |
| Confuse with **`rt_reset_control`** | IP reset lines ≠ system poweroff |
| Handler sleeps in IRQ context | GPIO driver uses **`rt_thread_mdelay`** — ensure thread context |
| No **`rt_dm_machine_shutdown`** | Set BSP hook |

---

## See also

- @ref page_device_dm_power — handler lists, priorities
- @ref page_device_power — overview
- @ref page_device_platform
- @ref page_device_reset — reset **controller** API (different)
- `components/drivers/power/reset/`
