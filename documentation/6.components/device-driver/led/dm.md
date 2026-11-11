@page page_device_led_dm LED device model (DM)

# LED subsystem under `RT_USING_DM`

**`RT_USING_LED`** (`components/drivers/led/`) depends on **`RT_USING_DM`**. The core **`led.c`** registers **`struct rt_led_device`** as char devices **`led0`**, **`led1`**, … via **`rt_dm_ida`**. In-tree OFW drivers bind Linux-style **`gpio-leds`**, **`pwm-leds`**, and **`register-bit-led`** nodes.

Public API and char-device **`read`/`write`**: @ref page_device_led.

Sources:

| File | Role |
| --- | --- |
| **`led.c`** | **`rt_led_register`**, software blink timer, sysfs-style **`read`/`write`** |
| **`led-gpio.c`** | **`gpio-leds`** parent + per-child GPIO LED |
| **`led-pwm.c`** | **`pwm-leds`** + **`pwms`** phandle, brightness |
| **`led-syscon.c`** | **`register-bit-led`** via @ref page_device_syscon |

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_DM`** | Required parent |
| **`RT_USING_LED`** | Core **`led.c`** |
| **`RT_LED_GPIO`** | **`led-gpio.c`** — needs **`RT_USING_PINCTRL`**, **`RT_USING_OFW`** |
| **`RT_LED_PWM`** | **`led-pwm.c`** — needs **`RT_USING_PWM`**, **`RT_USING_OFW`** |
| **`RT_LED_SYSCON`** | **`led-syscon.c`** — needs **`RT_MFD_SYSCON`** |
| **`SOC_DM_LED_DIR`** | BSP adds more LED drivers via **`osource`** |

**No `rt_bus`**: each LED is a **`RT_PLATFORM_DRIVER_EXPORT`** that calls **`rt_led_register`** from **`probe`**.

---

## Architecture

```
  DT: gpio-leds / pwm-leds / register-bit-led
        |
        |  platform match (rt_ofw_node_id)
        v
  probe: per-child or single node
        |
        |  parse gpios / pwms / syscon offset+mask
        |  fill struct rt_led_ops
        |  rt_led_register(&led->parent)  → "ledN"
        v
  rt_device (RT_Device_Class_Char, RDWR)
        |
        +-- rt_led_set_state / set_brightness / set_period
        +-- optional software blink (led.c timer)
        +-- write "on"|"off"|digits  /  read state string
```

| Backend | Compatible | One **`rt_led_device` per… |
| --- | --- | --- |
| GPIO | **`gpio-leds`** | **Child subnode** (like Linux) |
| PWM | **`pwm-leds`** | **Child subnode** |
| Syscon | **`register-bit-led`** | **Platform node** (one LED per compatible node) |

---

## Core registration (`led.c`)

```c
rt_err_t rt_led_register(struct rt_led_device *led);
rt_err_t rt_led_unregister(struct rt_led_device *led);
```

| Requirement | Detail |
| --- | --- |
| **`led->ops`** | Must be non-NULL at register |
| **Naming** | **`rt_dm_dev_set_name(..., "led%u", id)`** |
| **Blink fallback** | If **`set_state`** exists but **`set_period`** is NULL, **`led.c`** allocates **`blink_timer`** in **`sysdata`** for **`RT_LED_S_BLINK`** |
| **Unregister** | Forces **`RT_LED_S_OFF`**, detaches blink timer |

---

## GPIO LEDs (`led-gpio.c`)

**Parent** node:

```dts
/ {
    leds {
        compatible = "gpio-leds";
        pinctrl-0 = <&led_pins>;   /* optional: apply once for all children */

        status {
            gpios = <&gpio0 10 GPIO_ACTIVE_HIGH>;
            label = "status";
            default-state = "off";
            linux,default-trigger = "heartbeat";
        };
    };
};
```

| Property | Role |
| --- | --- |
| **`gpios`** | **`rt_ofw_get_named_pin`** — **`active_val`** from DT flags |
| **`default-state`** | **`"on"`** → **`RT_LED_S_ON`** at probe; else off |
| **`linux,default-trigger`** (fuzzy **`default-trigger$`**) | **`heartbeat`** or **`timer`** → **`RT_LED_S_BLINK`** (software blink in **`led.c`**) |
| **`pinctrl-0` on parent** | Applied once for all children; else per-child **`rt_pin_ctrl_confs_apply_by_name`** |

**Ops**: **`set_state`** (off/on/toggle), **`get_state`** (reads pin level). **`RT_LED_S_BLINK`** not implemented in GPIO ops — handled by core timer when **`set_state`** returns **`-RT_ENOSYS`**.

---

## PWM LEDs (`led-pwm.c`)

```dts
pwm-leds {
    compatible = "pwm-leds";

    backlight {
        pwms = <&pwm0 0 1000000>;   /* channel, period (ns) */
        max-brightness = <255>;
        active-low;
        default-state = "on";
    };
};
```

| Property | Role |
| --- | --- |
| **`pwms`** | Phandle + **`#pwm-cells`** — args[0] channel, args[1] **period (ns)** |
| **`max-brightness`** | Required; scales **`rt_led_set_brightness`** |
| **`active-low`** | Inverts duty calculation |
| **`default-state`** | **`on`**, **`keep`** (preserve existing PWM duty), or off |
| **`default-trigger`** | Same as GPIO — software blink |

**Ops**: **`set_state`**, **`get_state`** (tracks **`enabled`**), **`set_brightness`**. Brightness maps to **`rt_pwm_set`** pulse width.

PWM controller must be probed (**`rt_platform_ofw_request`** on provider if needed); cookie **`rt_ofw_data(pwm_np)`** → **`struct rt_device_pwm *`**.

---

## Syscon bit LEDs (`led-syscon.c`)

```dts
syscon: syscon@10000000 {
    compatible = "syscon";
    reg = <0x10000000 0x1000>;
};

status-led {
    compatible = "register-bit-led";
    offset = <0x10>;
    mask = <0x1>;
    default-state = "on";
};
```

| Property | Role |
| --- | --- |
| **`offset`** | Byte offset into parent **syscon** register block |
| **`mask`** | Bit mask for **`rt_syscon_update_bits`** |
| Parent | **`rt_syscon_find_by_ofw_node`** on **parent OFW node** |

**Ops**: **`set_state`**, **`get_state`** via **`rt_syscon_read`**. One platform device per LED node (**`pdev->parent.user_data`**).

---

## New LED backend checklist

1. Enable **`RT_USING_DM`**, **`RT_USING_LED`**, and backend Kconfig.
2. Embed **`struct rt_led_device parent`** first in private struct.
3. Implement **`struct rt_led_ops`** — at minimum **`set_state`**; add **`set_brightness`** for dimming, **`set_period`** for hardware blink.
4. **`rt_led_register`** after hardware/pinctrl/PWM is ready.
5. Apply **`default-state`** / **`default-trigger`** like in-tree drivers.
6. Store **`rt_ofw_data(child_np) = &led->parent`** (GPIO/PWM) or **`user_data`** (syscon) for **`remove`**.
7. **`remove`**: **`rt_led_unregister`**, free private data.
8. **`RT_PLATFORM_DRIVER_EXPORT`**.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **Double GPIO ownership** | Do not export the same pin as **`RT_USING_PIN`** device and LED |
| **PWM not probed** | Ensure PWM controller **`compatible`** probes before **`pwm-leds`** children |
| **Missing `max-brightness`** | PWM child probe fails with **`-RT_EINVAL`** |
| **Syscon parent** | **`register-bit-led`** must sit under / reference probed **syscon** |
| **Blink on GPIO** | Uses **software** timer in **`led.c`** — not hardware PWM blink |
| **Char write brightness** | Only works when **`set_brightness`** op exists (PWM path) |

---

## See also

- @ref page_device_input
- @ref page_device_syscon
- @ref page_device_pwm
- @ref page_device_pinctrl
- `components/drivers/include/drivers/led.h`
- `components/drivers/led/Kconfig`
