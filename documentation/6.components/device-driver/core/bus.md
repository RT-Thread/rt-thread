@page page_device_bus Bus and driver binding (core)

# Device model: bus and driver

RT-Thread **DM** binds **drivers** to **devices** through **`struct rt_bus`**: each bus keeps linked lists of devices and drivers, runs **`match`**, then **`probe`** / **`remove`** / **`shutdown`**. Most SoC drivers use the built-in **`platform`** bus; other stacks (e.g. **RPMsg**) register their own bus type on the same core.

Headers: `components/drivers/include/drivers/core/bus.h`, `driver.h`. Core: `components/drivers/core/bus.c`. Reference bus: `components/drivers/core/platform.c`.

Device-side helpers (`rt_dm_dev_iomap`, properties, IRQ): @ref page_device_dm.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_DM`** | Enables **`bus.c`**, **`driver.c`**, platform bus, and DM helpers |
| **`RT_USING_DEV_BUS`** | Optional **`rt_device_bus_create`** — bus as **`RT_Device_Class_Bus`** device |
| **`RT_USING_OFW`** | Platform **`match`** uses **`compatible`**; devices carry **`dev->ofw_node`** |
| **`RT_USING_PINCTRL`** | Platform **`probe`** applies **`pinctrl-*`** before driver **`probe`** |
| **`RT_USING_CLK`** | Platform **`probe`** runs **`rt_ofw_clk_set_defaults`** |

---

## Architecture

```
  rt_bus_register(bus)
         |
         v
  struct rt_bus (platform, rpmsg, ...)
    dev_list --> rt_device
    drv_list --> rt_driver
    match / probe / remove / shutdown
```

**Binding** (`bus.c`): **`rt_bus_add_device`** walks **`drv_list`**; **`rt_bus_add_driver`** walks **`dev_list`**. **`match`** must succeed before **`dev->drv`** is set and **`bus->probe(dev)`** runs. Failed probe clears **`dev->drv`**.

| Object | Role |
| --- | --- |
| **`struct rt_bus`** | Bus type and lifecycle hooks |
| **`struct rt_driver`** | Driver on a bus; **`ref_count`** = bound devices |
| **`struct rt_platform_device`** | Platform device embedding **`rt_device`** |

---

## `struct rt_bus` callbacks

| Callback | Contract |
| --- | --- |
| **`match`** | **Pure** — no HW access; return **`RT_TRUE`** to bind |
| **`probe`** | Bus-level setup (platform: pinctrl, clocks, power domain) then driver **`probe`** |
| **`remove`** | Teardown; platform calls **`pdrv->remove`** and **`rt_platform_ofw_free`** |
| **`shutdown`** | Invoked from **`rt_bus_shutdown()`** on system off |

---

## Bus and driver API

| API | Role |
| --- | --- |
| **`rt_bus_register`** | Register bus on global **`bus_nodes`** |
| **`rt_bus_add_device` / `rt_bus_add_driver`** | Add node and run matching |
| **`rt_bus_remove_device` / `rt_bus_remove_driver`** | Remove; driver busy if **`ref_count > 0`** |
| **`rt_bus_for_each_dev` / `rt_bus_for_each_drv`** | Iterate under spinlock |
| **`rt_bus_find_by_name`** | Find **`"platform"`** etc. |
| **`rt_bus_reload_driver_device`** | Move device to another bus |
| **`rt_bus_shutdown`** | Shutdown all devices on all buses |
| **`rt_driver_register` / `unregister`** | Driver attach/detach |

---

## `RT_DRIVER_EXPORT` / platform

```c
#define RT_DRIVER_EXPORT(driver, bus_name, mode)  /* INIT_DEVICE_EXPORT */
#define RT_PLATFORM_DRIVER_EXPORT(driver) \
    RT_DRIVER_EXPORT(driver, platform, BUILIN)
```

Example:

```c
static const struct rt_ofw_node_id my_ids[] = {
    { .compatible = "vendor,my-ip" },
    { /* sentinel */ },
};

static struct rt_platform_driver my_drv = {
    .name = "my-ip",
    .ids  = my_ids,
    .probe  = my_probe,
    .remove = my_remove,
};
RT_PLATFORM_DRIVER_EXPORT(my_drv);
```

---

## Platform bus

**`INIT_CORE_EXPORT(platform_bus_init)`** registers **`name = "platform"`**.

### `platform_match`

1. **`rt_ofw_node_match(np, pdrv->ids)`** when **`dev->ofw_node`** is set.
2. Else compare **`pdev->name`** and **`pdrv->name`**.

### `platform_probe` (before `pdrv->probe`)

1. Pinctrl default / index 0 — @ref page_device_pinctrl
2. **`rt_ofw_clk_set_defaults`** — @ref page_device_clk
3. **`rt_dm_power_domain_attach(dev, RT_TRUE)`** — **`-RT_EEMPTY`** OK — @ref page_device_power_domain
4. **`pdrv->probe(pdev)`** — map MMIO, clocks, register **`rt_device`**

| OFW API | Role |
| --- | --- |
| **`rt_platform_ofw_request`** | Instantiate from DT node |
| **`rt_platform_ofw_device_probe_child`** | Probe children |
| **`rt_platform_ofw_free`** | Free OFW state on remove |

See @ref page_device_platform, @ref page_device_ofw.

---

## Custom `rt_bus`

| New bus when… | Use **platform** when… |
| --- | --- |
| Non-OFW enumeration (RPMsg, internal stack bus) | **`/soc`** MMIO + **`compatible`** |

Implement **`match`/`probe`/`remove`**, **`rt_bus_register`** at init, then **`rt_bus_add_driver`** / **`rt_bus_add_device`**.

---

## SDIO vs core

MMC-specific DM: @ref page_device_sdio_dm. This page covers **`rt_bus` / `rt_driver`** only.

---

## Power and probe order

| Topic | Document |
| --- | --- |
| System shutdown | @ref page_device_dm_power |
| Power domains | @ref page_device_power_domain |
| Regulators | @ref page_device_regulator |

Typical order: **regulator → power domain → clock/reset → `rt_dm_dev_iomap`**.

---

## Engineer checklist

1. Export driver with **`RT_PLATFORM_DRIVER_EXPORT`** (or subsystem **`RT_DRIVER_EXPORT`**).
2. Request device via **`rt_platform_ofw_request`** or manual register.
3. In **`probe`**: resources → HW → register functional device; unwind on error.
4. In **`remove`**: reverse order; disable IRQ before free.

---

## Pitfalls

- **`match` with side effects** breaks re-probe.
- **Double `rt_bus_add_device`** without remove.
- **`rt_driver_unregister` while devices bound** — **`-RT_EBUSY`**.
- **Link order is not probe order** — defer on missing phandles.

---

## See also

- @ref page_device_dm
- @ref page_device_dm_power
- @ref page_device_platform
- @ref page_device_ofw, @ref page_device_dtc
- @ref page_device_sdio_dm
- `components/drivers/core/bus.c`, `platform.c`
