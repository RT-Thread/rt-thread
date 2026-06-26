@page page_device_input_touch Input touch bridge

# Touch bridge (`RT_INPUT_TOUCHSCREEN`)

**`input_touch.c`** bridges **`struct rt_input_device`** (Linux-style **`EV_ABS`** / multitouch slots) to **`struct rt_touch_device`** so GUI stacks can use the legacy **touch class** API (**`rt_device_find`**, **`RT_TOUCH_CTRL_*`**, **`rt_hw_touch_isr`**) without duplicating panel drivers.

Input core and OFW drivers (e.g. ADS7846): @ref page_device_input_dm. Event helpers (**`rt_input_setup_touch`**, **`rt_input_report_touch_*`**): @ref page_device_input.

Sources: **`components/drivers/input/input_touch.c`**, **`components/drivers/input/touchscreen/`**.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_INPUT_TOUCHSCREEN`** | Build **`input_touch.c`**; **selects `RT_USING_TOUCH`** |
| **`RT_INPUT_TOUCHSCREEN_ADS7846`** | In-tree SPI resistive driver **`ts-ads7846.c`** |
| **`SOC_DM_INPUT_TOUCHSCREEN_DIR`** | BSP adds more panel drivers |

Requires **`RT_USING_INPUT`** and **`RT_USING_DM`**.

---

## Architecture

```
  Panel driver (e.g. ads7846)
        |
        |  rt_input_set_capability(EV_ABS, …)
        |  rt_input_setup_touch(idev, num_slots, &touch_info)
        |  rt_input_device_register(idev)
        v
  input_touch_register (after idev on global list)
        |
        |  rt_hw_touch_register → device "touchN"
        |  rt_input_add_handler → input_touch_cb
        v
  Driver reports: rt_input_report_touch_* / rt_input_sync
        |
        v
  input_touch_cb: EV_ABS → struct rt_touch_data
                  SYN_REPORT → rt_hw_touch_isr()
        |
        v
  GUI: rt_device_read / touch ISR callback
```

| Object | Role |
| --- | --- |
| **`struct input_touch_properties`** | Stored in **`idev->touch`**: DT-derived min/max, invert, swap, slot count |
| **`struct input_touch_device`** | Embeds **`struct rt_touch_device`** + **`rt_input_handler`** + per-slot **`rt_touch_data`** |
| **`input_touch_ops`** | **`touch_readpoint`**, **`touch_control`** (range, enable/disable, status) |

**`input_touch_register`** only creates the **`rt_touch_device`** when **`rt_input_setup_touch`** was called with non-NULL **`struct rt_touch_info *info`** ( **`prop->touch_dev`** allocated).

---

## Driver API (`input.h`)

```c
rt_err_t rt_input_setup_touch(struct rt_input_device *idev,
        rt_uint32_t num_slots, struct rt_touch_info *info);
rt_err_t rt_input_parse_touch_position(struct rt_input_device *idev,
        rt_uint32_t *out_x, rt_uint32_t *out_y);
rt_bool_t rt_input_report_touch_inactive(struct rt_input_device *idev, rt_bool_t active);
void rt_input_report_touch_position(struct rt_input_device *idev,
        rt_uint32_t x, rt_uint32_t y, rt_bool_t multitouch);
```

| API | Role |
| --- | --- |
| **`rt_input_setup_touch`** | Allocate **`idev->touch`**, parse DT, optional multitouch absinfo (**`ABS_MT_SLOT`**, **`ABS_MT_TRACKING_ID`**) |
| **`num_slots == 0`** | Single-touch (**`ABS_X`/`ABS_Y`**); **`num_slots > 0`** | Multitouch slot protocol |
| **`rt_input_report_touch_position`** | Apply invert/swap from DT, then **`rt_input_report_abs`** |
| **`rt_input_report_touch_inactive`** | Emit **`ABS_MT_TRACKING_ID = -1`** on release |
| **`rt_input_parse_touch_position`** | Map raw x/y through **`touchscreen-inverted-*`** / **`touchscreen-swapped-x-y`** |

Call **`rt_input_setup_touch`** before **`rt_input_device_register`**. **`input_touch_register`** runs inside register after the device is linked globally.

---

## Device tree properties (`input_touch_parse`)

Read from the **`rt_input_device`**'s **`rt_device`** OFW node via **`rt_dm_dev_prop_*`**:

| Property | Effect |
| --- | --- |
| **`touchscreen-min-x`**, **`touchscreen-size-x`**, **`touchscreen-fuzz-x`** | Override **`ABS_X`** or **`ABS_MT_POSITION_X`** absinfo |
| **`touchscreen-min-y`**, **`touchscreen-size-y`**, **`touchscreen-fuzz-y`** | Y axis |
| **`touchscreen-max-pressure`**, **`touchscreen-fuzz-pressure`** | Pressure axis |
| **`touchscreen-inverted-x`**, **`touchscreen-inverted-y`** | Flip coordinates in **`rt_input_parse_touch_position`** |
| **`touchscreen-swapped-x-y`** | Swap X/Y absinfo and coordinates |

Missing properties fall back to values already set by **`rt_input_set_absinfo`** in the panel driver.

---

## Handler translation (`input_touch_cb`)

When **`touch_dev->enabled`**:

| Input event | Touch side |
| --- | --- |
| **`ABS_MT_SLOT`** | Select active slot index |
| **`ABS_MT_TRACKING_ID == -1`** | **`RT_TOUCH_EVENT_UP`**, **`rt_hw_touch_isr`** |
| **`ABS_MT_TRACKING_ID` valid** | DOWN / MOVE, increment **`down`** count |
| **`ABS_MT_POSITION_X/Y`** or **`ABS_X/Y`** | Scale raw value to **`range_x`/`range_y`** using absinfo min/max |
| **`EV_SYN` + `SYN_REPORT`** | **`rt_hw_touch_isr`** (frame complete) |

**`input_touch_readpoint`** returns one **`struct rt_touch_data`** for the current slot (GUI pull model).

---

## Example (driver probe sketch)

```c
struct rt_touch_info info = {
    .type = RT_TOUCH_TYPE_CAPACITANCE,
    .vendor = RT_TOUCH_VENDOR_UNKNOWN,
    .point_num = 1,
    .range_x = 800,
    .range_y = 480,
};

rt_input_set_capability(idev, EV_ABS, ABS_X);
rt_input_set_capability(idev, EV_ABS, ABS_Y);
rt_input_set_absinfo(idev, ABS_X, 0, max_x, 0, 0);
rt_input_set_absinfo(idev, ABS_Y, 0, max_y, 0, 0);

rt_input_setup_touch(idev, 0, &info);   /* 0 slots = single touch */
rt_input_device_register(idev);

/* in IRQ / thread: */
rt_input_report_touch_position(idev, x, y, RT_FALSE);
rt_input_sync(idev);
```

For multitouch, pass **`num_slots > 0`**, use **`rt_input_report_touch_slot`**, tracking id helpers, then **`rt_input_sync`** per frame.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`setup_touch` after register** | **`input_touch_register`** won't run correctly — setup before register |
| **`info == NULL`** | Properties-only mode: no **`rt_touch_device`** exported (handler-only path not used for HW touch register) |
| **Missing `rt_input_sync`** | Touch ISR won't see a full frame |
| **ABS range zero** | Scaling in **`input_touch_cb`** divides by **`maximum - minimum`** — set absinfo first |
| **Unregister order** | **`input_touch_unregister`** from **`rt_input_device_unregister`** — drop touch fd users first |

---

## See also

- @ref page_device_input_dm — **`ti,ads7846`** SPI binding
- @ref page_device_input
- @ref page_device_input_uapi — parallel POSIX event path on same **`inputN`**
- `components/drivers/include/drivers/dev_touch.h`
