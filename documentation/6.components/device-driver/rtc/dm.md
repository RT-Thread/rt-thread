@page page_device_rtc_dm RTC DM helpers (`rtc_dm.h`)

# `rtc_dm.h` API

Header: **`components/drivers/rtc/rtc_dm.h`**. Implementation: **`components/drivers/rtc/rtc_dm.c`**.

DM RTC chip drivers include this header at **`probe`** to set the registered device name and to convert alarm fields. Chip **`control()`** / **`RT_DEVICE_CTRL_RTC_*`** and application **`set_date` / `set_time`** are documented in @ref page_device_rtc.

---

## `rtc_dev_set_name`

```c
int rtc_dev_set_name(struct rt_device *rtc_dev);
```

Assigns the RTC **`rt_device`** name before **`rt_device_register`**:

| Condition | Name set |
| --- | --- |
| No device named **`"rtc"`** yet | **`rtc`** |
| **`"rtc"`** already exists | **`rtc1`**, **`rtc2`**, … (incrementing id) |

Returns the result of **`rt_dm_dev_set_name`** (0 on success).

**Note:** **`set_date()` / `set_time()`** in **`dev_rtc.c`** only look up **`"rtc"`**, not **`rtc1`**.

---

## `rtc_wkalarm_to_timestamp`

```c
time_t rtc_wkalarm_to_timestamp(struct rt_rtc_wkalarm *alarm);
```

Builds a **`time_t`** for **today’s calendar date** (from current **`time()`**) with hour/minute/second taken from **`alarm`** (`tm_hour`, `tm_min`, `tm_sec`). Other **`rt_rtc_wkalarm`** fields are ignored.

Uses **`localtime_r`** + **`timegm`**.

---

## `rtc_timestamp_to_wkalarm`

```c
void rtc_timestamp_to_wkalarm(time_t timestamp, struct rt_rtc_wkalarm *alarm);
```

Fills **`alarm->tm_hour`**, **`tm_min`**, **`tm_sec`** from **`timestamp`** (local time). Does not set **`enable`** or date fields.

---

## See also

- @ref page_device_rtc
- `components/drivers/include/drivers/dev_rtc.h` — **`struct rt_rtc_wkalarm`**, **`RT_DEVICE_CTRL_RTC_*`**
