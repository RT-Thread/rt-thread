@page page_device_input_dm Input device model (DM)

# Input subsystem under `RT_USING_DM`

The **input core** (`components/drivers/input/input.c`) is built only when **`RT_USING_INPUT`** is enabled. That Kconfig option **`depends on RT_USING_DM`** — there is **no** legacy non-DM input stack in-tree. Drivers publish Linux-style **`EV_*`** events through **`struct rt_input_device`**; consumers attach via **`rt_input_add_handler`** or POSIX **`/dev/inputN`** (@ref page_device_input_uapi).

Event reporting API, polling rules, and pitfalls: @ref page_device_input.

| Topic | Page |
| --- | --- |
| Userspace **`open`/`read`/`ioctl`** | @ref page_device_input_uapi |
| **`rt_touch_device`** bridge | @ref page_device_input_touch |
| **`KEY_POWER` / `KEY_RESTART`** shutdown/reset | @ref page_device_input_power |

Sources:

| File | Role |
| --- | --- |
| **`input.c`** | Global device list, **`rt_dm_ida`** naming (`input0`…), **`rt_input_device_register`** |
| **`input_power.c`** | @ref page_device_input_power |
| **`input_touch.c`** | @ref page_device_input_touch |
| **`input_uapi.c`** | @ref page_device_input_uapi |
| **`keyboard/`**, **`joystick/`**, **`touchscreen/`**, **`misc/`** | OFW platform/SPI drivers |

---

## Kconfig / build

| Option | Role |
| --- | --- |
| **`RT_USING_DM`** | Parent — input cannot be enabled without DM |
| **`RT_USING_INPUT`** | Core **`input.c`**; selects **`RT_USING_ADT`** + bitmap ADT |
| **`RT_INPUT_POWER`** | @ref page_device_input_power (default **y**) |
| **`RT_INPUT_UAPI`** | @ref page_device_input_uapi |
| **`RT_INPUT_KEYBOARD`** | **`gpio-keys`**, **`adc-keys`** (see sub-options) |
| **`RT_INPUT_JOYSTICK`** | **`adc-joystick`** |
| **`RT_INPUT_TOUCHSCREEN`** | @ref page_device_input_touch |
| **`RT_INPUT_MISC`** | e.g. **`ettus,e3x0-button`** |
| **`SOC_DM_INPUT_*_DIR`** | BSP adds more platform drivers via **`osource`** in sub-Kconfig |

**Unlike @ref page_device_i2c_dm**, input has **no dedicated `rt_bus`**. Each hardware block is a normal **`struct rt_platform_driver`** (or **`struct rt_spi_driver`**) that embeds or owns **`struct rt_input_device`** and calls **`rt_input_device_register`** from **`probe`**.

---

## Architecture

```
  Device tree node (compatible = "gpio-keys", "adc-keys", …)
        |
        |  platform bus match (rt_ofw_node_id) or SPI bus match
        v
  driver probe(pdev)
        |
        |  parse OFW (gpios, io-channels, irq, …)
        |  rt_input_set_capability(idev, EV_KEY|EV_ABS, code)
        |  optional: rt_input_setup_polling / rt_input_setup_touch
        v
  rt_input_device_register(idev)
        |
        |  rt_dm_ida_alloc → name "inputN"
        |  rt_device_register (RT_Device_Class_Char, DEACTIVATE)
        |  [RT_INPUT_UAPI] input_uapi_init
        |  list on input_device_nodes
        v
  [RT_INPUT_TOUCHSCREEN] input_touch_register → rt_touch_device
  [RT_INPUT_POWER]       global KEY_POWER / KEY_RESTART handlers
        |
        v
  Hardware IRQ / timer poll → rt_input_report_* → rt_input_sync
        |
        v
  rt_input_event → handlers / UAPI queue
```

| Layer | Object | Notes |
| --- | --- | --- |
| **Input device** | **`struct rt_input_device`** | Embeds **`struct rt_device parent`**; capabilities in bitmaps |
| **DM naming** | **`input_ida`** in **`input.c`** | **`rt_dm_dev_set_name(&idev->parent, "input%u", id)`** |
| **Platform binding** | **`RT_PLATFORM_DRIVER_EXPORT`** | Probe/remove on **`struct rt_platform_device`** |
| **SPI touch** | **`RT_SPI_DRIVER_EXPORT`** | e.g. ADS7846 — see @ref page_device_input_touch |

---

## Core registration (`input.c`)

```c
rt_err_t rt_input_device_register(struct rt_input_device *idev);
rt_err_t rt_input_device_unregister(struct rt_input_device *idev);
```

| Step | Behavior |
| --- | --- |
| **Allocate ID** | **`rt_dm_ida_alloc(&input_ida)`** — failure → **`-RT_EFULL`** |
| **Init lists / lock** | Per-device **`handler_nodes`**, **`rt_spinlock`** |
| **Register char dev** | **`RT_Device_Class_Char`**, flag **`RT_DEVICE_FLAG_DEACTIVATE`** |
| **Post-register** | Start poller timer if **`idev->poller`**; **`input_touch_register`**; UAPI fops if enabled |
| **Unregister** | Refcount check; UAPI/touch teardown; **`rt_dm_ida_free`** |

**Driver pattern** — embed input at a known offset:

```c
struct my_input {
    struct rt_input_device parent;
    /* private */
};

static void my_report(struct my_input *mi)
{
    rt_input_report_key(&mi->parent, KEY_ENTER, 1);
    rt_input_sync(&mi->parent);
}
```

Use **`rt_container_of(idev, struct my_input, parent)`** in poll/IRQ callbacks.

---

## In-tree OFW drivers

| Compatible / binding | Driver file | Bus | Summary |
| --- | --- | --- | --- |
| **`gpio-keys`** | **`keyboard/keys-gpio.c`** | platform | Parent node; **each child** → one **`inputN`** per key |
| **`adc-keys`** | **`keyboard/keys-adc.c`** | platform | **`io-channels`** via @ref page_device_iio_dm; polling |
| **`adc-joystick`** | **`joystick/js-adc.c`** | platform | Per-child **`reg`**, IIO, **`EV_ABS`** polling |
| **`ti,ads7846`** … **`ti,xpt2046`** | **`touchscreen/ts-ads7846.c`** | SPI | @ref page_device_input_touch |
| **`ettus,e3x0-button`** | **`misc/button-e3x0.c`** | platform | IRQ **`press`/`release`** → **`KEY_POWER`** |

### `gpio-keys` (platform + children)

- Parent **`compatible = "gpio-keys"`**; **subnodes** are individual buttons.
- Each child: **`rt_ofw_get_named_pin`**, property matching **`*,code$`** (e.g. **`linux,code`**), optional **`debounce-interval`**.
- **One `rt_input_device` per child** (not one device for the whole parent).

### `adc-keys` / `adc-joystick` (IIO consumers)

- Resolve ADC through **`rt_iio_channel_get_by_name`** / **`rt_iio_channel_get_by_index`** (@ref page_device_iio_dm).
- Default **`poll-interval`** **200 ms** if property missing.

### ADS7846 family (SPI)

- **`RT_SPI_DRIVER_EXPORT(ads7846_driver)`**; regulator, IRQ, worker thread.
- DT axis/touch properties consumed by **`input_touch_parse`** — @ref page_device_input_touch.

---

## Device tree examples

### GPIO key (child node)

```dts
gpio-keys {
    compatible = "gpio-keys";

    power-key {
        label = "Power";
        gpios = <&gpio0 5 GPIO_ACTIVE_LOW>;
        linux,code = <116>;   /* KEY_POWER — see page_device_input_power */
        debounce-interval = <15>;
    };
};
```

### ADC resistor ladder

```dts
adc-keys {
    compatible = "adc-keys";
    io-channels = <&saradc 0>;
    io-channel-names = "buttons";
    poll-interval = <100>;
    keyup-threshold-microvolt = <1800000>;

    up {
        press-threshold-microvolt = <500000>;
        linux,code = <103>;   /* KEY_UP */
    };
};
```

### SPI resistive touch

```dts
touch: touchscreen@0 {
    compatible = "ti,ads7846";
    reg = <0>;
    interrupt-parent = <&gpio1>;
    interrupts = <25 IRQ_TYPE_EDGE_FALLING>;
    ti,x-min = /bits/ 16 <0>;
    ti,x-max = /bits/ 16 <4095>;
    ti,y-min = /bits/ 16 <0>;
    ti,y-max = /bits/ 16 <4095>;
    vcc-supply = <&reg_3v3>;
};
```

(SPI **`reg`** / **`spi-max-frequency`** belong on the child under the SPI controller node per your BSP.)

---

## New platform input driver checklist

1. Enable **`RT_USING_DM`**, **`RT_USING_OFW`**, **`RT_USING_INPUT`** (and subsystem menu if you add under **`keyboard/`** etc.).
2. **`struct rt_platform_driver`** with **`ofw_ids[]`** matching Linux binding where possible.
3. In **`probe`**: allocate driver private struct with **`struct rt_input_device`** embedded first (or pointer field).
4. **`rt_input_set_capability`** for every **`type`/`code`** you will report; for **`EV_ABS`**, call **`rt_input_set_absinfo`** (after capability allocates **`absinfo`**).
5. IRQ or **`rt_input_setup_polling`** — poller **`poll`** must not block (@ref page_device_input).
6. On each logical event frame: **`rt_input_report_*`** then **`rt_input_sync`**.
7. **`rt_input_device_register`** only when hardware is ready; store private data in **`pdev->parent.user_data`** or **`rt_ofw_data(np)`** for **`remove`**.
8. **`remove`**: stop IRQ/poller, **`rt_input_device_unregister`**, free memory.
9. **`RT_PLATFORM_DRIVER_EXPORT(drv)`** (or **`RT_SPI_DRIVER_EXPORT`** on SPI slaves).

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **Missing `rt_input_sync`** | Consumers see partial frames — always end with **`rt_input_sync`**. |
| **Capability after register** | Set capabilities **before** **`rt_input_device_register`**. |
| **`EV_ABS` without absinfo** | Call **`rt_input_set_capability(EV_ABS, axis)`** then **`rt_input_set_absinfo`**. |
| **Unregister with open UAPI fd** | Close **`/dev/inputN`** first — @ref page_device_input_uapi |
| **gpio-keys child vs parent** | Driver registers **per child**; do not expect one **`input0`** for the whole node. |
| **IIO channel NULL** | Fix DT **`io-channels`** — @ref page_device_iio_dm |
| **Power handler surprise** | @ref page_device_input_power |

---

## See also

- @ref page_device_input
- @ref page_device_input_uapi
- @ref page_device_input_touch
- @ref page_device_input_power
- @ref page_device_iio_dm
- @ref page_device_bus
- `components/drivers/include/drivers/input.h`
- `components/drivers/input/Kconfig`
