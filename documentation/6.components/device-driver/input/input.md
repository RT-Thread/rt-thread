@page page_device_input Input subsystem

Device-tree binding and DM registration: @ref page_device_input_dm.

| Topic | Page |
| --- | --- |
| Userspace API | @ref page_device_input_uapi |
| Touch class bridge | @ref page_device_input_touch |
| Power / restart keys | @ref page_device_input_power |

# Input subsystem (API)

Header: `drivers/input.h`. Typical stack: low-level driver → **`rt_input_event` / reporters** → handlers (GUI, shell) or **`/dev/inputN`** (@ref page_device_input_uapi).

| Path | API |
| --- | --- |
| In-kernel listener | **`rt_input_add_handler`** |
| POSIX process (Smart) | **`open` / `read` / `ioctl` / `poll` on `/dev/inputN`** — @ref page_device_input_uapi |
| Legacy touch GUI | **`struct rt_touch_device`** — @ref page_device_input_touch |

## When to use the input core

| Use **`rt_input_*`** when… | Consider raw **`rt_device`** read when… |
| --- | --- |
| You want **Linux-like** `EV_KEY` / `EV_REL` / `EV_ABS` / multitouch slot semantics and multiple listeners. | You have a **single proprietary** app talking to a vendor IOCTL-only touch stack. |
| You need **polling** (`**rt_input_setup_polling**`) for GPIO keys without IRQ storms. | GPIO IRQ latency is fine and you do not need unified event routing. |

## Event contract

1. **`rt_input_set_capability`** before **`rt_input_device_register`** so users know which **`type`/`code`** pairs are valid.
2. For each hardware change, call **`rt_input_report_*`** then **`rt_input_sync`** to close the frame (**`SYN_REPORT`**). Missing **`sync`** merges events poorly for consumers.
3. **`rt_input_trigger`** routes through optional **`idev->trigger`**—use when you wrap another input device; otherwise **`rt_input_event`** is enough.

## Callback / context rules

- **`rt_input_add_handler` → `callback`**: invoked from **`rt_input_event`** path—assume **thread or workqueue** unless your driver documents IRQ delivery; keep **`callback` short**.
- **`poller->poll`**: runs on timer tick—**must not block** or take mutexes that can deadlock with the same thread calling **`rt_input_sync`**.
- **Touch helpers**: **`rt_input_setup_touch`** / **`rt_input_report_touch_*`** require **`RT_INPUT_TOUCHSCREEN`** — @ref page_device_input_touch.

## Registration lifecycle

- **`rt_input_device_register`**: registers underlying **`rt_device`**; failures leave partially init state—clean up partial setup in error paths.
- **`rt_input_remove_config`**: tears down polling/touch dynamic config before unregister if you toggled features at runtime.

## Pitfalls

- **ABS without `rt_input_set_absinfo`**: consumers cannot clamp—set min/max/resolution for axes you report.
- **Key autorepeat**: not automatic unless a layer implements it—do not assume Linux repeat behavior.
- **Re-entrancy**: posting events from inside a handler for the same device can recurse—prefer queueing.

## See also

- @ref page_device_input_dm
- @ref page_device_input_uapi
- @ref page_device_input_touch
- @ref page_device_input_power
- `components/drivers/include/drivers/input.h`
- `components/drivers/include/drivers/input_uapi.h`
- `dt-bindings/input/event-codes.h`
