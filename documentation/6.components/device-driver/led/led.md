@page page_device_led LED subsystem

Device-tree binding and platform drivers: @ref page_device_led_dm.

# LED subsystem (API)

Header: **`components/drivers/include/drivers/led.h`**. Core: **`components/drivers/led/led.c`**.

Each **`struct rt_led_device`** registers as a char device **`led0`**, **`led1`**, … under **`RT_USING_DM`**. Control via **`rt_led_*`** APIs or by **`read`/`write`** on the device node (shell / DFS).

---

## When to use the LED core

| Use **`rt_led_*`** when… | Raw GPIO/PWM may suffice when… |
| --- | --- |
| DT **`gpio-leds`** / **`pwm-leds`** should create uniform **`ledN`** devices. | One debug LED toggled directly in board code. |
| **`power_supply`** or policy code drives charging/status indicators. | LED is bootloader-only, never touched at runtime. |
| Userspace or MSH writes **`on`/`off`** or a brightness number to the device file. | No registration or naming needed. |

---

## States and operations

```c
enum rt_led_state {
    RT_LED_S_OFF,
    RT_LED_S_ON,
    RT_LED_S_TOGGLE,
    RT_LED_S_BLINK,
};

rt_err_t rt_led_register(struct rt_led_device *led);
rt_err_t rt_led_unregister(struct rt_led_device *led);

rt_err_t rt_led_set_state(struct rt_led_device *led, enum rt_led_state state);
rt_err_t rt_led_get_state(struct rt_led_device *led, enum rt_led_state *out_state);
rt_err_t rt_led_set_period(struct rt_led_device *led, rt_uint32_t period_ms);
rt_err_t rt_led_set_brightness(struct rt_led_device *led, rt_uint32_t brightness);
```

| API | Behavior |
| --- | --- |
| **`set_state`** | Calls **`led->ops->set_state`** under spinlock; stops software blink timer when leaving blink |
| **`RT_LED_S_BLINK`** | If ops returns **`-RT_ENOSYS`** and core allocated **`blink_timer`**, starts periodic timer (**heartbeat-style** timing in **`led.c`**) |
| **`get_state`** | Requires **`ops->get_state`** — else **`-RT_ENOSYS`** |
| **`set_period`** | Uses **`ops->set_period`** if present; else adjusts software blink timer period |
| **`set_brightness`** | Requires **`ops->set_brightness`** (PWM backend) |

### `struct rt_led_ops`

```c
struct rt_led_ops {
    rt_err_t (*set_state)(struct rt_led_device *led, enum rt_led_state state);
    rt_err_t (*get_state)(struct rt_led_device *led, enum rt_led_state *out_state);
    rt_err_t (*set_period)(struct rt_led_device *led, rt_uint32_t period_ms);
    rt_err_t (*set_brightness)(struct rt_led_device *led, rt_uint32_t brightness);
};
```

Implement only the callbacks your hardware supports; missing hooks return **`-RT_ENOSYS`** from the matching **`rt_led_*`** wrapper.

---

## Char device interface (`led.c`)

Registered with **`RT_DEVICE_FLAG_RDWR`**.

### `write`

| Input | Action |
| --- | --- |
| **`off`**, **`on`**, **`toggle`**, **`blink`** | String match → **`rt_led_set_state`** |
| Decimal digits | **`rt_led_set_brightness`** (e.g. **`128`** on PWM LED) |

### `read`

Returns ASCII state name: **`off`**, **`on`**, **`toggle`**, or **`blink`** (from **`rt_led_get_state`**).

Example (MSH / POSIX):

```text
echo on > /dev/led0
echo 200 > /dev/led1    /* brightness, PWM LED */
cat /dev/led0
```

---

## Software blink (`led.c`)

When **`ops->set_period`** is NULL but **`ops->set_state`** exists, **`rt_led_register`** creates a **`blink_timer`** in **`led->sysdata`**:

- **`RT_LED_S_BLINK`** with GPIO/syscon ops (no native blink) triggers the timer path in **`rt_led_set_state`**.
- Timer toggles off/on with **~80 ms** on and **~1000 ms** off phases (heartbeat-like pattern).
- **`rt_led_set_period`** can change the long off interval via **`RT_TIMER_CTRL_SET_TIME`**.

For **hardware** PWM blink, implement **`set_period`** in **`rt_led_ops`** instead.

---

## Driver embed pattern

```c
struct my_led {
    struct rt_led_device parent;
    /* hardware private */
};

static const struct rt_led_ops my_led_ops = {
    .set_state = my_led_set_state,
    .get_state = my_led_get_state,
};

static int my_led_init(void)
{
    struct my_led *ml = ...;
    ml->parent.ops = &my_led_ops;
    return rt_led_register(&ml->parent);
}
```

OFW platform drivers should use **`rt_led_register`** in **`probe`** and **`rt_led_unregister`** in **`remove`** — see @ref page_device_led_dm.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`ops` NULL at register** | **`rt_led_register`** returns **`-RT_EINVAL`** |
| **Unregister while blinking** | **`rt_led_unregister`** stops timer and forces off |
| **Brightness on GPIO LED** | **`set_brightness`** not implemented — use **`set_state`** only |
| **Concurrent access** | Core uses **`led->spinlock`** — keep **`ops`** callbacks short |
| **Same pin as GPIO driver** | One owner only — @ref page_device_led_dm |

---

## See also

- @ref page_device_led_dm — **`gpio-leds`**, **`pwm-leds`**, **`register-bit-led`**
- @ref page_device_syscon
- @ref page_device_power_supply — charging LEDs
- `components/drivers/include/drivers/led.h`
