@page page_device_ptp PTP clock subsystem

# PTP clock subsystem (API)

Header: **`components/drivers/include/drivers/ptp.h`**. Core: **`components/drivers/ptp/ptp.c`**.

The PTP layer wraps **IEEE 1588 hardware clocks** (PHC) behind a small, Linux-style **`rt_ptp_ops`** interface. Hardware drivers expose **read/set time**, **frequency and phase adjustment**, **external timestamp (EXTTS)**, **periodic output (PEROUT)**, **PPS**, optional **GPIO pin routing**, and **snapshot** reads. Upper layers (PTP protocol stacks, time sync services, test tools) call the **`rt_ptp_*`** helpers directly; the registered **`rt_device`** is mainly a **named handle** for lookup (`ptp0`, `ptp1`, …).

Requires **`RT_USING_PTP`** (Kconfig) and **`RT_USING_DM`**.

---

## When to use this API

| Use PTP when… | Prefer something else when… |
| --- | --- |
| The SoC or NIC provides a **dedicated PHC** with sub-microsecond discipline. | **Calendar time only** — @ref page_device_rtc or POSIX `time()`. |
| You need **ppb frequency trim**, **phase step**, or **hardware timestamping** of external events. | **OS tick / hrtimer scheduling** — @ref page_device_hwtimer or @ref page_device_clock_time_core. |
| Firmware or DT describes **EXTTS / PEROUT / PPS pins** on a PTP block. | **Software NTP only** — no PHC driver required. |

---

## Enable in menuconfig

```text
RT-Thread Components →
    Device Drivers →
        [*] Using Precision Time Protocol (PTP) IEEE 1588 clock support
```

SoC-specific options may be added under **`$(SOC_DM_PTP_DIR)/Kconfig`** when present.

---

## Roles

| Role | Responsibility |
| --- | --- |
| **PHC driver** | Fills **`struct rt_ptp_clock`**, implements **`rt_ptp_ops`**, calls **`rt_ptp_clock_register`**. Reports capabilities (`max_freq`, `alarm_nr`, `extts_nr`, `perout_nr`, `pps`, `pins_nr`). Raises **`rt_ptp_clock_event`** from ISR or bottom-half when hardware events occur. |
| **Client / stack** | Obtains **`struct rt_ptp_clock *`** (from probe, DT phandle, or **`rt_device_find("ptp0")`** + **`rt_device_to_ptp_clock`**). Uses **`rt_ptp_gettime` / `rt_ptp_adjfreq` / …** and optional **`rt_ptp_clock_notifier`** callbacks. |

The core registers each clock as **`RT_Device_Class_Char`** with **`RT_DEVICE_FLAG_DEACTIVATE`**. There is **no** standard `read`/`write`/`control` path in **`ptp.c`** — all operations go through the **`rt_ptp_*`** API.

---

## Data structures

### Time format

```c
struct rt_ptp_clock_time {
    rt_int64_t sec;
    rt_int32_t nsec;   /* 0 .. 999_999_999 when passed through rt_ptp_adjtime */
};
```

### Clock object

```c
struct rt_ptp_clock {
    struct rt_device parent;
    const struct rt_ptp_ops *ops;

    rt_int32_t max_freq;   /* ppb limit; required if ops->adjfreq is set */
    rt_int32_t alarm_nr;
    rt_int32_t pins_nr;
    rt_int32_t extts_nr;
    rt_int32_t perout_nr;
    rt_int32_t pps;

    rt_list_t notifier_nodes;
    struct rt_spinlock nodes_lock;

    struct rt_ptp_pin *pins;      /* pins_nr entries when pins_nr > 0 */
    struct rt_mutex pin_mutex;
};
```

Convert from a generic device pointer:

```c
#define rt_device_to_ptp_clock(dev) rt_container_of(dev, struct rt_ptp_clock, parent)
```

### Driver operations

```c
struct rt_ptp_ops {
    rt_err_t (*adjfreq)(struct rt_ptp_clock *ptp, rt_base_t freq);
    rt_err_t (*adjphase)(struct rt_ptp_clock *ptp, rt_int32_t phase);
    rt_err_t (*getmaxphase)(struct rt_ptp_clock *ptp, rt_int32_t *out_maxphase);
    rt_err_t (*adjtime)(struct rt_ptp_clock *ptp, rt_int64_t delta);
    rt_err_t (*gettime)(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);
    rt_err_t (*settime)(struct rt_ptp_clock *ptp, const struct rt_ptp_clock_time *ts);
    rt_err_t (*enable)(struct rt_ptp_clock *ptp, struct rt_ptp_clock_request *request, rt_bool_t on);
    rt_err_t (*verify)(struct rt_ptp_clock *ptp, rt_uint32_t pin, rt_uint32_t func, rt_uint32_t chan);
    rt_err_t (*getsnapshot)(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);
};
```

| Callback | Purpose |
| --- | --- |
| **`adjfreq`** | Fine frequency adjustment in **parts per billion (ppb)**. Core clamps to **`±max_freq`**. |
| **`adjphase`** | Phase shift in nanoseconds; core clamps using **`getmaxphase`**. |
| **`getmaxphase`** | Reports maximum absolute phase adjustment. |
| **`adjtime`** | Step the clock by **`delta`** nanoseconds (signed). |
| **`gettime` / `settime`** | Read or write absolute PHC time. |
| **`enable`** | Enable/disable **EXTTS**, **PEROUT**, or **PPS** (see **`struct rt_ptp_clock_request`**). |
| **`verify`** | Validate pin/function/channel routing before metadata is updated. **Required** when **`pins_nr > 0`**. |
| **`getsnapshot`** | Read a latched / snapshot time (hardware-specific). |

Unimplemented ops return **`-RT_ENOSYS`** from the matching **`rt_ptp_*`** wrapper.

---

## Register and unregister

```c
rt_err_t rt_ptp_clock_register(struct rt_ptp_clock *ptp);
rt_err_t rt_ptp_clock_unregister(struct rt_ptp_clock *ptp);
```

**`rt_ptp_clock_register`** checks:

| Condition | Error |
| --- | --- |
| **`ptp` or `ops` is NULL** | **`-RT_EINVAL`** |
| **`pins_nr > 0`** but **`pins` is NULL** or **`verify` is NULL** | **`-RT_EINVAL`** |
| **`extts_nr` or `perout_nr` > 0** but **`enable` is NULL** | **`-RT_EINVAL`** |
| **`adjfreq` is non-NULL** but **`max_freq <= 0`** | **`-RT_EINVAL`** |
| IDA exhausted | **`-RT_EFULL`** |

On success the device name is **`ptp<N>`** (for example **`ptp0`**).

**`rt_ptp_clock_unregister`**:

- Fails with **`-RT_EINVAL`** if **`ref_count != 0`**
- Warns if notifiers are still registered
- Disables all **EXTTS** channels, **PEROUT** channels, and **PPS**
- Detaches **`pin_mutex`** when **`pins_nr > 0`**

---

## Time discipline API

```c
rt_err_t rt_ptp_adjfreq(struct rt_ptp_clock *ptp, rt_base_t freq);
rt_err_t rt_ptp_adjphase(struct rt_ptp_clock *ptp, rt_int32_t phase);
rt_err_t rt_ptp_getmaxphase(struct rt_ptp_clock *ptp, rt_int32_t *out_maxphase);
rt_err_t rt_ptp_adjtime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);
rt_err_t rt_ptp_gettime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);
rt_err_t rt_ptp_settime(struct rt_ptp_clock *ptp, const struct rt_ptp_clock_time *ts);
rt_err_t rt_ptp_getsnapshot(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts);
```

**`rt_ptp_adjtime`** converts **`ts->sec` / `ts->nsec`** to a signed nanosecond delta and forwards it to **`ops->adjtime`**. **`nsec`** must be in **`[0, 10⁹)`**.

**`rt_ptp_adjfreq`**: if **`max_freq <= 0`**, only **`freq == 0`** is accepted (no-op success).

---

## EXTTS, PEROUT, and PPS

### External timestamps (EXTTS)

```c
struct rt_ptp_request_extts {
    rt_uint32_t chan;
    rt_uint32_t flags;   /* PTP_ENABLE_FEATURE, PTP_RISING_EDGE, PTP_FALLING_EDGE, PTP_STRICT_FLAGS */
};

rt_err_t rt_ptp_request_extts(struct rt_ptp_clock *ptp, struct rt_ptp_request_extts *extts);
```

- **`chan`** must be **`< extts_nr`**
- With **`PTP_STRICT_FLAGS`**, enabling requires at least one of **`PTP_RISING_EDGE`** or **`PTP_FALLING_EDGE`**
- Clearing **`PTP_ENABLE_FEATURE`** (or zero flags) disables the channel via **`enable(..., RT_FALSE)`**

### Periodic output (PEROUT)

```c
struct rt_ptp_request_perout {
    rt_uint32_t chan;
    rt_uint32_t flags;   /* PTP_PEROUT_ONE_SHOT, PTP_PEROUT_DUTY_CYCLE, PTP_PEROUT_PHASE */
    struct rt_ptp_clock_time period;       /* zero period disables output */
    struct rt_ptp_clock_time on;             /* high time when PTP_PEROUT_DUTY_CYCLE */
    struct rt_ptp_clock_time start_phase;    /* start or phase offset when PTP_PEROUT_PHASE */
};

rt_err_t rt_ptp_request_perout(struct rt_ptp_clock *ptp, struct rt_ptp_request_perout *perout);
```

- **`chan`** must be **`< perout_nr`**
- With **`PTP_STRICT_FLAGS`**: duty **`on`** must not exceed **`period`**; **`start_phase`** must be strictly less than one period when **`PTP_PEROUT_PHASE`** is set
- Enable is inferred: **`period.sec || period.nsec`**

### PPS

```c
rt_err_t rt_ptp_enable_pps(struct rt_ptp_clock *ptp, rt_bool_t on);
```

Uses **`request.type = PTP_CLK_REQ_PPS`** and **`ops->enable`**.

---

## GPIO pin routing

When **`pins_nr > 0`**, the core keeps a **`pins[]`** table describing which physical pin is mapped to which function and channel.

```c
enum {
    PTP_PIN_FUNC_NONE,
    PTP_PIN_FUNC_EXTTS,
    PTP_PIN_FUNC_PEROUT,
    PTP_PIN_FUNC_PHYSYNC,
};

rt_err_t rt_ptp_get_pin_func(struct rt_ptp_clock *ptp, rt_uint32_t pin, struct rt_ptp_pin *out_pin);
rt_err_t rt_ptp_set_pin_func(struct rt_ptp_clock *ptp, rt_uint32_t pin, rt_uint32_t func, rt_uint32_t chan);
```

**Important:** **`rt_ptp_set_pin_func`** only updates **routing metadata** and disables the previous function on affected pins. It does **not** start EXTTS or PEROUT hardware. After assigning a pin, call **`rt_ptp_request_extts`** or **`rt_ptp_request_perout`** separately.

**`rt_ptp_set_pin_func`** flow:

1. Validate **`func`** / **`chan`** against **`extts_nr`**, **`perout_nr`**, or PHYSYNC rules
2. Call **`ops->verify`**
3. Disable any other pin already using the same **`func` + `chan`**
4. Disable the old function on the target pin, then store the new mapping

Access to **`pins[]`** is serialized with **`pin_mutex`**.

---

## Event notifiers

Hardware drivers call **`rt_ptp_clock_event`** when an alarm fires, an external timestamp is captured, PPS is observed, etc.

```c
enum {
    PTP_CLOCK_EV_ALARM,
    PTP_CLOCK_EV_EXTTS,
    PTP_CLOCK_EV_EXTOFF,
    PTP_CLOCK_EV_PPS,
    PTP_CLOCK_EV_PPSUSR,
};

struct rt_ptp_clock_event {
    rt_uint32_t type;
    rt_uint32_t index;
    union {
        rt_uint64_t timestamp;
        rt_int64_t offset;
        struct rt_ptp_clock_time pps_times;
    };
};

struct rt_ptp_clock_notifier {
    rt_list_t list;
    rt_uint32_t event_mask;   /* RT_BIT(PTP_CLOCK_EV_*) bits */
    struct rt_ptp_clock *ptp;
    void (*callback)(struct rt_ptp_clock_notifier *notifier, struct rt_ptp_clock_event *ev);
    void *priv;
};

rt_err_t rt_ptp_clock_notifier_register(struct rt_ptp_clock *ptp, struct rt_ptp_clock_notifier *notifier);
rt_err_t rt_ptp_clock_notifier_unregister(struct rt_ptp_clock *ptp, struct rt_ptp_clock_notifier *notifier);
void rt_ptp_clock_event(struct rt_ptp_clock *ptp, struct rt_ptp_clock_event *ev);
```

**`event_mask`** must be non-zero at register time. **`rt_ptp_clock_event`** walks registered notifiers under **`nodes_lock`** and invokes matching callbacks **without holding the lock** during the callback.

---

## Example (PHC driver sketch)

```c
#include <drivers/ptp.h>

static rt_err_t my_ptp_gettime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts)
{
    /* read hardware counter */
    ts->sec = 0;
    ts->nsec = 0;
    return RT_EOK;
}

static rt_err_t my_ptp_adjfreq(struct rt_ptp_clock *ptp, rt_base_t freq)
{
    /* program frequency trim in ppb */
    return RT_EOK;
}

static rt_err_t my_ptp_enable(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_request *req, rt_bool_t on)
{
    switch (req->type) {
    case PTP_CLK_REQ_EXTTS:
        /* configure edge detect on req->extts.chan */
        break;
    case PTP_CLK_REQ_PEROUT:
        /* program req->perout period/on */
        break;
    case PTP_CLK_REQ_PPS:
        /* enable/disable PPS output */
        break;
    default:
        return -RT_EINVAL;
    }
    return RT_EOK;
}

static const struct rt_ptp_ops my_ptp_ops = {
    .gettime = my_ptp_gettime,
    .settime = my_ptp_settime,
    .adjfreq = my_ptp_adjfreq,
    .adjtime = my_ptp_adjtime,
    .enable = my_ptp_enable,
    .verify = my_ptp_verify,   /* required when pins_nr > 0 */
};

static struct rt_ptp_clock my_ptp = {
    .ops = &my_ptp_ops,
    .max_freq = 500000,   /* 500 ppm if 1 ppb == 1 Hz at 1 GHz; driver-defined scale */
    .extts_nr = 2,
    .perout_nr = 1,
    .pps = 1,
};

static int my_ptp_probe(struct rt_platform_device *pdev)
{
    return rt_ptp_clock_register(&my_ptp);
}
```

### Client lookup

```c
struct rt_ptp_clock *ptp;
rt_device_t dev = rt_device_find("ptp0");

if (dev)
    ptp = rt_device_to_ptp_clock(dev);

if (ptp) {
    struct rt_ptp_clock_time ts;
    rt_ptp_gettime(ptp, &ts);
}
```

### POSIX dynamic clock (`clock_gettime`)

When **`RT_USING_POSIX_CLOCK`**, **`RT_USING_POSIX_FS`**, and **`RT_USING_PTP`** are enabled, PHC devices follow the Linux [dynamic clock](https://www.man7.org/linux/man-pages/man3/clock_gettime.3.html) model:

```c
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

int fd = open("/dev/ptp0", O_RDWR);
clockid_t clkid = FD_TO_CLOCKID(fd);
struct timespec ts;

clock_gettime(clkid, &ts);
clock_settime(clkid, &ts);   /* requires ops->settime */
clock_getres(clkid, &ts);
```

Macros in **`sys/time.h`**: **`CLOCKFD`**, **`FD_TO_CLOCKID`**, **`CLOCKID_TO_FD`**. Implementation: **`components/libc/compilers/common/ctime.c`**.

The fd must refer to an **open** `/dev/ptpN` device node (devfs). **`CLOCK_REALTIME`** still uses RTC; dynamic **`clockid_t`** values are separate from fixed POSIX clock IDs.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`set_pin_func` without `request_extts` / `request_perout`** | Pin table updates only; explicitly enable the feature afterward. |
| **`adjfreq` without `max_freq`** | Registration fails; set **`max_freq`** to the hardware ppb limit. |
| **Notifier left registered at unregister** | Core logs a warning; unregister notifiers in client teardown. |
| **Calling `rt_ptp_clock_event` with wrong `type`** | **`RT_ASSERT`** in debug builds; keep **`type < PTP_CLOCK_EV_MAX`**. |
| **Blocking in notifier callback** | Callback runs with lock dropped but may be invoked from interrupt context depending on the driver — keep callbacks short or defer work. |
| **Confusing PTP with RTC** | RTC is wall-clock calendar time; PTP PHC is for **precision sync** and **hardware timestamping**. |

---

## See also

- @ref page_device_rtc — calendar RTC
- @ref page_device_clock_time_core — kernel clock source / clock event devices
- @ref page_device_hwtimer — general-purpose hardware timers
- `components/drivers/ptp/ptp.c`
- `components/drivers/include/drivers/ptp.h`
