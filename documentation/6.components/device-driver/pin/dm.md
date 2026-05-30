@page page_device_pin_dm GPIO device model (DM)

# GPIO / PIN under `RT_USING_DM`

**`RT_USING_PIN`** with **`RT_USING_DM`** adds a **global GPIO namespace**: each platform GPIO controller registers a contiguous **virtual pin number** range. Application code still uses **`rt_pin_mode` / `rt_pin_write` / `rt_pin_read`** (@ref page_device_pin); drivers use **`rt_pin_get_named_pin`** and optional **GPIO IRQ domains**.

Sources:

| File | Role |
| --- | --- |
| **`dev_pin_dm.c`** | Global pin table, **`pin_api_init`**, **`pin_pic_init`**, DM **`rt_pin_ops`** shim |
| **`dev_pin_ofw.c`** | **`rt_ofw_get_named_pin`** — `gpios` / `gpio` properties |
| **`dev_pin.c`** | Legacy single **`gpio`** device when no DM controllers |
| **`pin-pl061.c`** | Reference platform driver (`arm,pl061`) |

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_PIN`** | GPIO framework (default **y**) |
| **`RT_USING_DM`** | Required for DM path described here |
| **`RT_PIN_PL061`** | In-tree PL061 driver |
| **`SOC_DM_PIN_DIR`** | BSP adds SoC GPIO drivers via **`osource`** |

---

## Architecture

```
  DT: gpio-controller node (#gpio-cells, interrupt-controller optional)
        |
        |  platform probe
        v
  struct rt_device_pin + rt_pin_ops (per controller)
        |
        +-- pin_api_init(gpio, pin_nr)     → global pin_start..pin_start+nr-1
        +-- pin_pic_init(gpio, irq)        → optional per-line PIC domain
        +-- rt_dm_dev_bind_fwdata → rt_ofw_data(np) = gpio
        |
        v
  First controller also: rt_device_pin_register("gpio", pin_api_dm_ops)
        |
        v
  Consumers:
        rt_pin_get_named_pin(dev, "foo", index, &mode, &val)
        rt_pin_mode(pin, mode); rt_pin_write(pin, val);
```

| Concept | Meaning |
| --- | --- |
| **Local pin** | Index `0 … pin_nr-1` passed to **`rt_pin_ops`** |
| **Virtual pin** | **`pin_start + local`** — value for **`rt_pin_*`** and **`rt_pin_get_named_pin`** |
| **`pin_device_find`** | Maps virtual pin → owning **`struct rt_device_pin`** |

Controllers are linked on **`pin_nodes`**; **`pin_total_nr`** only grows (ranges are not recycled).

---

## Platform driver checklist

1. **`struct rt_device_pin`** (or embed as first member of private struct).
2. Implement **`struct rt_pin_ops`**: at minimum **`pin_mode`**, **`pin_write`**, **`pin_read`**.
3. **`probe`**: iomap, clock, **`rt_dm_dev_bind_fwdata(dev, NULL, &gpio->parent)`**.
4. **`pin_api_init(&gpio->parent, gpio_count)`** — assigns **`pin_start`**.
5. If GPIO has a shared IRQ line:
   - **`irq = rt_dm_dev_get_irq(dev, 0)`**
   - **`pin_pic_init(&gpio->parent, irq)`**
   - Hardware ISR: loop pending bits → **`pin_pic_handle_isr(&gpio->parent, local_pin)`**
   - Install **`rt_hw_interrupt_install(irq, …)`** + **`umask`**
6. Optional **`pin_parse`** for non-default **`#gpio-cells`** (flags from **`dt-bindings/pin/pin.h`**).

Reference: **`pin-pl061.c`** (`pl061_probe`).

---

## `struct rt_pin_ops` (DM-relevant)

| Callback | Role |
| --- | --- |
| **`pin_mode`** | Input / output / pull / open-drain |
| **`pin_write` / `pin_read`** | Level |
| **`pin_attach_irq`** | Direct per-pin ISR (optional) |
| **`pin_detach_irq`** | Remove handler |
| **`pin_irq_enable`** | Enable/disable line interrupt |
| **`pin_irq_mode`** | Edge/level when using legacy IRQ path |
| **`pin_parse`** | Decode **`#gpio-cells`** → local pin + **`flags`** |
| **`pin_get`** | Name → virtual pin (optional) |
| **`pin_debounce`** | Debounce time |

If **`pin_attach_irq`** is **NULL**, **`dev_pin_dm.c`** stores handlers in **`legacy_isr[]`** and relies on **`pin_irq_mode`** + **`pin_pic_handle_isr`**.

---

## Device tree: `gpios` properties

**`rt_ofw_get_named_pin(np, propname, index, out_mode, out_value)`** tries:

- **`{propname}-gpios`**, then **`{propname}-gpio`**
- If **`propname`** is **`NULL`**, tries **`gpios`** / **`gpio`**

Flow:

1. **`rt_ofw_parse_phandle_cells(..., "#gpio-cells", …)`**
2. **`rt_platform_ofw_request`** on GPIO provider if needed
3. **`pin_parse`** or default: **`args[0]`** = local pin
4. Convert **`flags`** → **`PIN_MODE_*`**, active level
5. Return **`local + pin_dev->pin_start`** (virtual pin)

Wrapper on device:

```c
rt_ssize_t rt_pin_get_named_pin(struct rt_device *dev, const char *propname,
        int index, rt_uint8_t *out_mode, rt_uint8_t *out_value);
rt_ssize_t rt_pin_get_named_pin_count(struct rt_device *dev, const char *propname);
```

Typical **`probe`**:

```c
pin = rt_pin_get_named_pin(dev, "reset", 0, &mode, &active);
if (pin < 0)
    return pin;
rt_pin_mode(pin, mode);
rt_pin_write(pin, active);   /* or inactive per DT flags */
```

Examples in-tree: **`phye-generic-usb.c`** (`reset`), **`gpio-restart.c`**, **`led-gpio.c`** (child node), **`backlight-gpio.c`**.

---

## GPIO IRQ + PIC

**`struct rt_pin_irqchip`** is embedded in **`struct rt_device_pin`** (after **`parent`**).

| API | Role |
| --- | --- |
| **`pin_pic_init(gpio, irq)`** | **`rt_pic_linear_irq`**, **`legacy_isr`** array, **`pin_dm_ops`** |
| **`pin_pic_handle_isr(gpio, local_pin)`** | Dispatch **PIC** path and/or **legacy_isr** callback |

Per-line DT interrupt (2 cells: pin + flags) uses **`pin_dm_ops.irq_parse`** / **`irq_map`**:

- Maps hwirq → virtual IRQ
- **`rt_pic_cascade(pirq, gpio->irqchip.irq)`** — GPIO block IRQ cascades to controller's **`rt_dm_dev_get_irq`**

For **`rt_pin_attach_irq(virtual_pin, …)`** without DT interrupt on that line, legacy path + **`pin_irq_enable`** on hardware still applies.

---

## Application / driver usage

DM systems should prefer:

```c
/* Not GET_PIN(port, n) from old BSP tables */
pin = rt_pin_get_named_pin(&pdev->parent, "led", 0, &mode, NULL);
rt_pin_mode(pin, mode);
```

Legacy **`GET_PIN`** / **`drv_gpio.c`** pin tables apply to non-DM BSP GPIO only.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Skip **`pin_api_init`** | **`rt_ofw_get_named_pin`** adds wrong **`pin_start`** |
| **`pin_parse` missing** | Only **`args[0]`** used; wrong if `#gpio-cells` > 1 with flags |
| IRQ without **`pin_pic_init`** | Shared IRQ controllers need **`pin_pic_handle_isr`** |
| **`pin_attach_irq` vs legacy** | If **`pin_attach_irq` NULL**, must enable via **`pin_irq_enable`** after attach |
| Provider not probed | Ensure **`rt_platform_ofw_request`** or platform driver registered |

---

## See also

- @ref page_device_pin — **`rt_pin_*`** application API
- @ref page_device_pic_cascade — GPIO PIC cascade
- `components/drivers/include/drivers/dev_pin.h`
- `components/drivers/pin/dev_pin_dm.c`, `dev_pin_ofw.c`
