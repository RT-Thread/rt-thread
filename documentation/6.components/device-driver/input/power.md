@page page_device_input_power Input power keys

# Power / restart key handlers (`RT_INPUT_POWER`)

**`input_power.c`** installs global **`rt_input_handler`** instances that map **`KEY_POWER`** and **`KEY_RESTART`** release events to **`rt_hw_cpu_shutdown()`** and **`rt_hw_cpu_reset()`**. Any input device that advertises these keys in its capability bitmap can trigger system power actions without a dedicated PMIC driver hook.

DM and keyboard drivers: @ref page_device_input_dm. Handler API: @ref page_device_input.

Source: **`components/drivers/input/input_power.c`**.

---

## Kconfig

| Option | Default | Role |
| --- | --- | --- |
| **`RT_INPUT_POWER`** | **y** | Build **`input_power.c`**, run **`input_event_power_init`** at env init |

Depends on **`RT_USING_INPUT`**. Disable on boards where **`KEY_POWER`** must only be handled by application code.

---

## Architecture

```
  INIT_ENV_EXPORT(input_event_power_init)
        |
        +-- power_handler_install(KEY_POWER)
        +-- power_handler_install(KEY_RESTART)
                |
                |  (1) tmp_handler: identify=test, callback=power_input_callback
                |      rt_input_add_handler → scans all idevs, counts matches
                v
        (2) For each matching input device index:
                alloc rt_input_handler[N]
                identify=power_input_identify (binds to Nth device with key)
                callback=power_input_callback
                rt_input_add_handler
        |
        v
  Any idev reports KEY_POWER/KEY_RESTART release (value==0)
        → rt_input_event → handler → shutdown/reset
```

| Phase | Behavior |
| --- | --- |
| **Probe pass** | Temporary handler increments **`cap.value`** for each **`rt_input_device`** with **`key_map[code]`** set |
| **Install pass** | One persistent handler per matching device; **`identify`** matches the **`current`**-th device |
| **Runtime** | **`power_input_callback`**: on **`value == 0`** (key release), call BSP hook |

Handlers return **`RT_TRUE`** from **`callback`** to stop further handler dispatch for that event.

---

## Key actions

| Linux code | Event | Action |
| --- | --- | --- |
| **`KEY_POWER`** (116) | **`EV_KEY`**, **`value == 0`** (release) | **`rt_hw_cpu_shutdown()`** |
| **`KEY_RESTART`** | **`EV_KEY`**, **`value == 0`** | **`rt_hw_cpu_reset()`** |

Press (**`value == 1`**) does nothing in **`input_power.c`** — only release triggers power ops.

BSP must implement **`rt_hw_cpu_shutdown`** / **`rt_hw_cpu_reset`** (weak symbols or SoC-specific).

---

## Interaction with drivers

- **`gpio-keys`** child with **`linux,code = <116>`** registers an **`inputN`** with **`KEY_POWER`** in **`key_map`** — power handler attaches automatically when **`RT_INPUT_POWER`** is on.
- **`ettus,e3x0-button`** reports **`KEY_POWER`** on IRQ — same path.
- Does **not** require a dedicated compatible string; only the **advertised key code** matters.

If multiple devices expose **`KEY_POWER`**, each gets its own handler instance; any of them can shut down the system on release.

---

## Disabling or overriding

| Goal | Approach |
| --- | --- |
| **No automatic shutdown** | Set **`RT_INPUT_POWER=n`** in Kconfig |
| **Custom policy** | Disable **`RT_INPUT_POWER`** and use **`rt_input_add_handler`** with higher priority logic, or handle **`KEY_POWER`** only in userspace via @ref page_device_input_uapi |
| **Hold-to-power-off** | Not implemented here — implement in driver (long-press timer) before reporting release |

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **Unexpected shutdown** | Any stray **`KEY_POWER`** release shuts down — verify DT **`linux,code`** and test harnesses |
| **Missing capability** | Driver must **`rt_input_set_capability(idev, EV_KEY, KEY_POWER)`** before register |
| **Press-only testing** | Release is required — press alone does not call shutdown |
| **No matching devices** | **`power_handler_install`** exits early if count is zero (no handlers allocated) |

---

## See also

- @ref page_device_input_dm — **`gpio-keys`** DT example with **`KEY_POWER`**
- @ref page_device_input
- `dt-bindings/input/linux-event-codes.h` (or **`event-codes.h`**)
