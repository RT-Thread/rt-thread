@page page_device_thermal Thermal management

# Thermal subsystem

RT-Thread thermal management ties **temperature sensors** (**thermal zones**) to **cooling devices** (fan, DVFS, …) using **trip points** and **governors**. Temperatures are in **millidegrees Celsius (m°C)**.

| Piece | Path |
| --- | --- |
| API | `components/drivers/include/drivers/thermal.h` |
| Core + OFW | `components/drivers/thermal/thermal.c`, `thermal_dm.c` |
| Kconfig | **`RT_USING_THERMAL`** (requires **`RT_USING_DM`**, **`RT_USING_OFW`** for DT maps) |

Cooling device details: @ref page_device_thermal_cool.

---

## Architecture

```
Sensor driver (I2C, on-chip, SCMI, …)
    embeds struct rt_thermal_zone_device
    fills rt_thermal_zone_ops (get_temp required)
    sets parent.ofw_node, zone_id
        ↓
rt_thermal_zone_device_register(zdev)
    ├─ thermal_ofw_setup()  ← walks /thermal-zones, trips, cooling-maps
    ├─ work queue: thermal_zone_poll → rt_thermal_zone_device_update()
    └─ global thermal_zone_device_nodes list

Cooling driver (pwm-fan, dvfs, gpio-fan, …)
    rt_thermal_cooling_device_register(cdev)
    └─ global thermal_cooling_device_nodes list
        ↓
OFW cooling-map links trip → cdev via phandle
    thermal_bind() in thermal_ofw_setup
        ↓
Trip exceeded → rt_thermal_cooling_device_kick()
    governor tuning → cdev->ops->set_cur_level()
```

**Governor**: Built-in **`dumb`** governor is registered at **`INIT_CORE_EXPORT`**. **`rt_thermal_cooling_device_register`** attaches **`dumb`** unless **`rt_thermal_cooling_device_change_governor`** selects another.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_THERMAL`** | Core **`thermal.c`** + **`thermal_dm.c`** |
| **`RT_THERMAL_SCMI`** | Sensor zones via SCMI (`thermal-scmi.c`, needs @ref page_device_scmi) |
| **`RT_THERMAL_COOL_PWM_FAN`** | `thermal-cool-pwm-fan.c` |
| **`RT_THERMAL_COOL_GPIO_FAN`** | `thermal-cool-gpio-fan.c` |
| **`RT_THERMAL_COOL_DVFS`** | `thermal-cool-dvfs.c` (needs **`RT_USING_DVFS`**) |
| **`SOC_DM_THERMAL_DIR`** | BSP sensor drivers |
| **`SOC_DM_THERMAL_COOL_DIR`** | BSP cooling drivers |

---

## Thermal zone

```c
struct rt_thermal_zone_device {
    struct rt_device parent;
    int zone_id;
    const struct rt_thermal_zone_ops *ops;
    struct rt_thermal_trip *trips;
    rt_size_t trips_nr;
    struct rt_thermal_cooling_map *cooling_maps;
    rt_tick_t polling_delay, passive_delay;
    /* temperature, cooling, poller work, mutex, … */
};

struct rt_thermal_zone_ops {
    rt_err_t (*get_temp)(struct rt_thermal_zone_device *zdev, int *out_temp);  /* required */
    rt_err_t (*set_trips)(...);      /* optional HW trip window */
    rt_err_t (*set_trip_temp)(...);
    rt_err_t (*set_trip_hyst)(...);
    void (*hot)(...);
    void (*critical)(...);
};
```

### Registering a zone

```c
static rt_err_t my_get_temp(struct rt_thermal_zone_device *zdev, int *out_temp)
{
    *out_temp = read_sensor_mc();  /* m°C, or RT_THERMAL_TEMP_INVALID */
    return RT_EOK;
}

static const struct rt_thermal_zone_ops my_tz_ops = {
    .get_temp = my_get_temp,
};

/* probe */
zdev->ops = &my_tz_ops;
zdev->zone_id = 0;
zdev->parent.ofw_node = sensor_np;
rt_thermal_zone_device_register(zdev);
```

| Requirement | Detail |
| --- | --- |
| **`get_temp`** | Mandatory; called from **`rt_thermal_zone_device_update`** |
| **`parent.ofw_node`** | Sensor node referenced from **`/thermal-zones/.../thermal-sensors`** |
| **Trips** | From DT under zone, or pre-filled **`zdev->trips`** before register |
| **Polling** | **`rt_work`** resubmits every **`polling_delay`** / **`passive_delay`** (from DT, ms → ticks) |

---

## Device tree (`thermal_ofw_setup`)

Linux-style layout under **`/thermal-zones`**:

```dts
thermal-zones {
    cpu-thermal {
        polling-delay-passive = <250>;
        polling-delay = <1000>;
        thermal-sensors = <&cpu_temp 0>;

        trips {
            passive: trip-passive {
                temperature = <85000>;   /* 85 °C in m°C */
                hysteresis = <2000>;
                type = "passive";
            };
            critical: trip-critical {
                temperature = <105000>;
                hysteresis = <2000>;
                type = "critical";
            };
        };

        cooling-maps {
            map0 {
                trip = <&passive>;
                cooling-device = <&fan0 0 3>, <&cpu_dvfs 0 5>;
                contribution = <1024>;
            };
        };
    };
};

cpu_temp: cpu-temp@... { /* sensor OFW node */ };

fan0: fan {
    compatible = "pwm-fan";
    pwms = <&pwm0 0 40000>;
    cooling-levels = <0 50 100 150 200 255>;
    /* optional: regulator consumer supply id "fan" (see regulator DT) */
};
```

| Zone property | Effect |
| --- | --- |
| **`thermal-sensors`** | Phandle + optional index → matches sensor **`ofw_node`** and **`zone_id`** |
| **`polling-delay`** / **`polling-delay-passive`** | Work reschedule interval |
| **`sustainable-power`**, **`coefficients`** | **`rt_thermal_zone_params`** |
| **Child `trips`** | **`temperature`**, **`hysteresis`**, **`type`** (`active` / `passive` / `hot` / `critical`) |
| **`cooling-maps`** | **`trip`**, **`cooling-device`** (`#cooling-cells`: min/max level), **`contribution`** |

**`cooling-device`** phandle resolves to a registered **`rt_thermal_cooling_device`** by matching **`cdev->parent.ofw_node`**. Register **cooling devices before** the zone that references them (or ensure cooling nodes are probed first).

---

## Cooling device

```c
struct rt_thermal_cooling_device {
    struct rt_device parent;
    const struct rt_thermal_cooling_device_ops *ops;
    rt_ubase_t max_level;
    struct rt_thermal_cooling_governor *gov;
    /* … */
};

struct rt_thermal_cooling_device_ops {
    rt_err_t (*bind)(struct rt_thermal_cooling_device *cdev,
            struct rt_thermal_zone_device *zdev);
    rt_err_t (*unbind)(...);
    rt_err_t (*get_max_level)(...);
    rt_err_t (*get_cur_level)(...);
    rt_err_t (*set_cur_level)(struct rt_thermal_cooling_device *cdev, rt_ubase_t level);
};
```

**`rt_thermal_cooling_device_register`** requires **`get_max_level`**, **`get_cur_level`**, **`set_cur_level`**. **`bind`/`unbind`** optional (forwarded by **`thermal_bind`** in `thermal_dm.c`).

---

## Update loop and trips

**`rt_thermal_zone_device_update(zdev, msg)`**:

1. Reads temperature via **`get_temp`**.
2. For each trip with **`temperature < current`**, handles type:
   - **`PASSIVE`** / default → **`cooling = true`**, **`rt_thermal_cooling_device_kick`**
   - **`CRITICAL`** → **`ops->critical`** or cool; may **`rt_hw_cpu_reset`** if still over limit
   - **`HOT`** → **`ops->hot`** if present
3. Governor **`tuning`** adjusts levels per **cooling-map** cell; **`set_cur_level`** applied.
4. Notifiers receive **`msg`** bitmask (`RT_THERMAL_MSG_TRIP_VIOLATED`, `RT_THERMAL_MSG_EVENT_TEMP_SAMPLE`, …).

Call **`update`** from the zone poller (automatic after register) or manually for testing.

---

## Built-in drivers

| Driver | Binding | Role |
| --- | --- | --- |
| **`thermal-scmi.c`** | **`RT_SCMI_DRIVER_EXPORT`**, protocol sensor `"thermal"` | One zone per SCMI temperature sensor |
| **`thermal-cool-pwm-fan.c`** | **`compatible = "pwm-fan"`** | PWM + optional regulator — @ref page_device_thermal_cool |
| **`thermal-cool-gpio-fan.c`** | GPIO + speed table | Discrete fan speeds |
| **`thermal-cool-dvfs.c`** | DVFS OPP levels as cooling steps | Throttle CPU/GPU via @ref page_device_dvfs |

BSP sensors (e.g. board thermal IC) typically **`rt_thermal_zone_device_register`** in platform **`probe`** after filling trips in code or relying entirely on **`thermal_ofw_setup`**.

---

## Key APIs

| API | Role |
| --- | --- |
| `rt_thermal_zone_device_register` / `unregister` | Zone lifecycle + OFW parse + start poller |
| `rt_thermal_zone_device_update` | Sample temp, trips, cooling, notifiers |
| `rt_thermal_zone_set_trip` / `get_trip` | Runtime trip change |
| `rt_thermal_zone_notifier_register` | Event callback |
| `rt_thermal_cooling_device_register` / `unregister` | Cooling device |
| `rt_thermal_cooling_device_kick` | Re-run governor for a zone |
| `rt_thermal_cooling_governor_register` | Custom governor |
| `rt_thermal_cooling_device_change_governor` | Per-device governor selection |

Constants: **`RT_THERMAL_TEMP_INVALID`** (−274000), **`RT_THERMAL_NO_LIMIT`**.

---

## Pitfalls

- **Units**: always **m°C** in trips and **`get_temp`** (85 °C → `85000`).
- **`get_temp` cost**: slow buses (I2C) in every poll — cache or shorten **`polling-delay`** thoughtfully.
- **Cooling registration order**: maps reference **`cdev`** by OFW node; probe cooling before zone register.
- **Missing maps**: trips fire but no **`cooling-maps`** → log/events only, no fan/DVFS change.
- **Hysteresis / noise**: tight trips without **`hysteresis`** cause level oscillation.
- **Mutex**: transfer APIs in other subsystems aside — zone **`update`** uses **`zdev->mutex`** when not in ISR.
- **Unregister**: detach notifiers and stop polling before destroying hardware.

---

## See also

- @ref page_device_thermal_cool — PWM fan cooling device
- @ref page_device_dvfs — DVFS framework and Rockchip cpufreq
- @ref page_device_scmi — SCMI sensor protocol
- @ref page_device_pwm
- @ref page_device_regulator
- `components/drivers/include/drivers/thermal.h`
- `components/drivers/thermal/thermal.c`
