@page page_device_i2c_dm I2C device model (DM)

# I2C bus framework under `RT_USING_DM`

When **`RT_USING_DM`** and **`RT_USING_I2C`** are enabled, RT-Thread adds an **I2C-specific `rt_bus`** (`name = "i2c"`) on top of the core DM bus layer (@ref page_device_bus). **Bus controllers** still register as **`RT_Device_Class_I2CBUS`** devices (`i2c0`, `i2c1`, …); **slave drivers** bind as **`struct rt_i2c_client`** devices discovered from device tree children.

Legacy **manual** usage (`rt_device_find("i2c1")` + `rt_i2c_transfer`) remains valid — see @ref page_device_i2c. This page covers **automatic DT binding** and **`RT_I2C_DRIVER_EXPORT`**.

Sources:

| File | Role |
| --- | --- |
| **`dev_i2c_bus.c`** | **`struct rt_bus i2c_bus`**, match/probe, **`i2c_bus_scan_clients`** |
| **`dev_i2c_dm.c`** | **`i2c_timings_ofw_parse`** |
| **`dev_i2c_core.c`** | Calls **`i2c_bus_scan_clients`** after **`rt_i2c_bus_device_register`** |
| **`dev_i2c.h`** | **`rt_i2c_client`**, **`rt_i2c_driver`**, **`RT_I2C_DRIVER_EXPORT`** |
| **`dev_i2c_dm.h`** | **`struct i2c_timings`**, scan/timings declarations |

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_I2C`** | Core I2C stack (`dev_i2c_core.c`, `dev_i2c_dev.c`, …) |
| **`RT_USING_DM`** | Adds **`dev_i2c_bus.c`** + **`dev_i2c_dm.c`** (I2C bus + OFW scan) |
| **`RT_USING_OFW`** | Required for **`i2c_bus_scan_clients`** and **`i2c_timings_ofw_parse`** |
| **`SOC_DM_I2C_DIR`** | BSP SoC adapters (e.g. `i2c-rk3x.c`) |

Without **`RT_USING_DM`**, **`struct rt_i2c_client`** has no embedded **`rt_device`** — only **`bus`** + **`client_addr`**.

---

## Architecture

```
  Platform I2C controller (e.g. rk3x, bit-bang)
        |
        |  probe: i2c_timings_ofw_parse, rt_dm_dev_iomap, clocks
        |  bus->parent.ofw_node = controller np
        |  rt_i2c_bus_device_register(&bus->parent, "i2cN")
        v
  rt_device "i2cN"  (RT_Device_Class_I2CBUS, user_data -> rt_i2c_bus_device)
        |
        |  i2c_bus_scan_clients(bus)   /* dev_i2c_core.c */
        v
  For each available child in DT:
        alloc rt_i2c_client, reg -> client_addr, ofw_node
        rt_i2c_device_register(client)  -> rt_bus_add_device("i2c", ...)
        v
  i2c_match: driver ids[] name OR ofw_ids compatible
        |
        v
  i2c_probe -> driver->probe(client)
        |
        v
  Client driver uses client->bus + rt_i2c_transfer / master_send
```

**Two bus layers**:

| Layer | Object | Example |
| --- | --- | --- |
| **I2C bus device** | **`struct rt_i2c_bus_device`** | Hardware adapter; **`master_xfer`**, mutex **`lock`** |
| **DM I2C bus** | **`struct rt_bus` `i2c_bus`** | Binds **`rt_i2c_driver`** ↔ **`rt_i2c_client`** |

Core DM **`platform`** bus probes the **controller**; subsystem **`i2c`** bus probes **clients** under that controller’s OFW node.

---

## `struct rt_bus i2c` (dev_i2c_bus.c)

Registered at boot: **`INIT_CORE_EXPORT(i2c_bus_init)`** → **`rt_bus_register(&i2c_bus)`**.

| Callback | Behavior |
| --- | --- |
| **`i2c_match`** | 1) Match **`driver->ids[].name`** to **`client->name`** (from DT node name). 2) Else **`rt_ofw_node_match(client->ofw_node, driver->ofw_ids)`**. Sets **`client->id`** or **`client->ofw_id`**. |
| **`i2c_probe`** | Requires **`client->bus`**; calls **`driver->probe(client)`**. |
| **`i2c_remove` / `i2c_shutdown`** | Forward to driver hooks. |

**Driver registration**:

```c
rt_err_t rt_i2c_driver_register(struct rt_i2c_driver *driver);
/* RT_I2C_DRIVER_EXPORT(drv) -> RT_DRIVER_EXPORT(drv, i2c, BUILIN) */
```

Sets **`driver->parent.bus = &i2c_bus`** then **`rt_driver_register`**.

**Client registration**:

```c
rt_err_t rt_i2c_device_register(struct rt_i2c_client *client);
/* internally: rt_bus_add_device(&i2c_bus, &client->parent) */
```

---

## Device tree: controller + clients

### Controller node

```dts
i2c1: i2c@ff160000 {
    compatible = "rockchip,rk3588-i2c", "rockchip,rk3066-i2c";
    reg = <0x0 0xff160000 0x0 0x1000>;
    interrupts = <GIC_SPI 32 IRQ_TYPE_LEVEL_HIGH>;
    clocks = <&cru CLK_I2C1>, <&cru PCLK_I2C1>;
    clock-names = "i2c", "pclk";
    #address-cells = <1>;
    #size-cells = <0>;

    rtc@68 {
        compatible = "dallas,ds1307";
        reg = <0x68>;
    };
};
```

| Property | Role |
| --- | --- |
| **`clock-frequency`** | Parsed into **`struct i2c_timings.bus_freq_hz`** |
| **`i2c-scl-rising-time-ns`**, **`i2c-scl-falling-time-ns`**, … | Optional timing cells — **`i2c_timings_ofw_parse`** |
| **`#address-cells = <1>`**, **`#size-cells = <0>`** | Standard I2C child addressing |
| **Child `reg`** | 7-bit (or 10-bit) slave address → **`client->client_addr`** |

### Client discovery (`i2c_bus_scan_clients`)

Called automatically when **`rt_i2c_bus_device_register`** succeeds (**`RT_USING_DM`** only).

For each **available** child of **`bus->parent.ofw_node`**:

1. If child has **`compatible`**, use it as client node; else look one level deeper (**i2c-mux** style).
2. **`rt_calloc`** **`struct rt_i2c_client`**.
3. Read **`reg`** → **`client_addr`**.
4. **`client->parent.ofw_node`**, **`client->name = rt_ofw_node_name`**, **`client->bus = bus`**.
5. **`rt_dm_dev_set_name(&client->parent, "%s", name)`**.
6. **`rt_i2c_device_register(client)`** → triggers **`i2c_match`** + **`probe`** if a driver is already registered.

**Order note**: If the **client driver** registers before the **bus**, clients are not scanned yet. Typically **controller `probe` runs first** (platform init), then scan instantiates clients while **I2C drivers** are already linked via **`RT_I2C_DRIVER_EXPORT`**. If a driver loads late, you may need manual **`rt_i2c_device_register`** or re-scan (not provided in-tree — ensure init order).

---

## Bus controller driver (adapter)

Pattern from SoC drivers (e.g. **`bsp/rockchip/dm/i2c/i2c-rk3x.c`**):

```c
static rt_err_t my_i2c_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct my_i2c *i2c = rt_calloc(1, sizeof(*i2c));

    i2c_timings_ofw_parse(dev->ofw_node, &i2c->timings, RT_TRUE);

    i2c->regs = rt_dm_dev_iomap(dev, 0);
    i2c->irq  = rt_dm_dev_get_irq(dev, 0);
    /* clocks: rt_clk_get_by_name, prepare_enable */

    rt_dm_dev_set_name_auto(&i2c->parent.parent, "i2c");

    i2c->parent.ops = &my_i2c_ops;
    i2c->parent.parent.ofw_node = dev->ofw_node;
    dev->user_data = i2c;

    return rt_i2c_bus_device_register(&i2c->parent, rt_dm_dev_get_name(dev));
}
```

| Step | API |
| --- | --- |
| Timings | **`i2c_timings_ofw_parse(np, &timings, use_defaults)`** |
| Resources | **`rt_dm_dev_iomap`**, **`rt_dm_dev_get_irq`**, **`rt_clk_*`** (@ref page_device_clk) |
| Naming | **`rt_dm_dev_set_name`** / **`rt_dm_dev_set_name_auto`** → **`i2c0`**, **`i2c1`**, … |
| Publish bus | **`rt_i2c_bus_device_register(&i2c->parent, name)`** — triggers **client scan** |

**`rt_i2c_bus_device`** embeds **`struct rt_device parent`**; **`user_data`** on that device points at the full adapter struct (controller private data).

Bit-bang buses (**`RT_USING_I2C_BITOPS`**) call **`rt_i2c_bit_add_bus`** → same **`rt_i2c_bus_device_register`** path.

---

## Client driver (I2C slave)

```c
static const struct rt_ofw_node_id my_ids[] = {
    { .compatible = "vendor,my-sensor", .data = (void *)&chip_info },
    { /* sentinel */ },
};

static const struct rt_i2c_device_id my_tbl[] = {
    { .name = "my-sensor", .data = (void *)&chip_info },
    { /* sentinel */ },
};

static struct rt_i2c_driver my_driver = {
    .ids     = my_tbl,      /* optional: match by DT node name */
    .ofw_ids = my_ids,      /* match by compatible */
    .probe   = my_probe,
    .remove  = my_remove,
};
RT_I2C_DRIVER_EXPORT(my_driver);

static rt_err_t my_probe(struct rt_i2c_client *client)
{
    struct rt_i2c_bus_device *bus = client->bus;
    rt_uint16_t addr = client->client_addr;
    const void *cfg = rt_i2c_client_id_data(client);

    /* Use rt_i2c_master_send/recv or rt_i2c_transfer on client->bus */
    return RT_EOK;
}
```

| Field / API | Role |
| --- | --- |
| **`client->bus`** | Parent adapter — **must** be set (scan sets it; manual clients must assign). |
| **`client->client_addr`** | From DT **`reg`** (scan) or driver setup. |
| **`client->parent.ofw_node`** | Child DT node for **`rt_dm_dev_get_irq`** etc. |
| **`rt_i2c_client_id_data(client)`** | **`id->data`** or **`ofw_id->data`** from match table |

After **`probe`**, many drivers register a functional device (RTC, sensor, regulator) on top of the client, using **`client->parent`** only as the DM binding handle.

---

## `struct i2c_timings` (OFW)

Defined in **`dev_i2c_dm.h`**. **`i2c_timings_ofw_parse(dev_np, timings, use_defaults)`** reads:

| DT property | Field |
| --- | --- |
| **`clock-frequency`** | **`bus_freq_hz`** (default 100 kHz if missing and **`use_defaults`**) |
| **`i2c-scl-rising-time-ns`** | **`scl_rise_ns`** |
| **`i2c-scl-falling-time-ns`** | **`scl_fall_ns`** |
| **`i2c-scl-internal-delay-ns`** | **`scl_int_delay_ns`** |
| **`i2c-sda-falling-time-ns`** | **`sda_fall_ns`** |
| **`i2c-sda-hold-time-ns`** | **`sda_hold_ns`** |
| **`i2c-digital-filter-width-ns`** | **`digital_filter_width_ns`** |
| **`i2c-analog-filter-cutoff-frequency`** | **`analog_filter_cutoff_freq_hz`** |

Controller **`probe`** passes parsed timings into IP-specific **`calc_timings`** (SoC-specific).

---

## Transfer path (unchanged by DM)

DM only changes **how clients appear**. Data path is still:

```c
rt_i2c_bus_lock(bus, timeout);
rt_i2c_transfer(bus, msgs, num);   /* -> ops->master_xfer */
rt_i2c_bus_unlock(bus);
```

Or **`rt_i2c_master_send` / `rt_i2c_master_recv`**. Bus mutex serializes masters on one adapter.

---

## DM vs non-DM summary

| Topic | With **`RT_USING_DM`** | Without DM |
| --- | --- | --- |
| Client struct | **`rt_i2c_client`** embeds **`rt_device parent`** | **`bus` + `client_addr` only |
| Binding | **`RT_I2C_DRIVER_EXPORT`** + DT scan | App finds bus, bit-bangs address manually |
| Bus register side effect | **`i2c_bus_scan_clients`** | No scan |
| Timing helpers | **`i2c_timings_ofw_parse`** | Driver parses DT itself or fixed Hz |

---

## Engineer checklist

1. **Controller**: platform **`probe`** → timings + resources → **`rt_i2c_bus_device_register`** with **`ofw_node`** on **`bus->parent`**.
2. **Client driver**: **`ofw_ids`** + optional **`ids`**, **`RT_I2C_DRIVER_EXPORT`**, **`probe`** uses **`client->bus`** and **`client_addr`**.
3. **DT**: controller **`#address-cells` / `#size-cells`**, child **`reg`** + **`compatible`**.
4. **Transfers**: always through **`client->bus`**, respect **`rt_i2c_bus_lock`** if sharing with other code.
5. **Remove**: controller **`remove`** should **`rt_device_unregister`** bus; clients removed via **`i2c_remove`** when bus tears down (verify BSP order).

---

## Pitfalls

- **`client->bus == NULL`** in **`i2c_probe`** → **`-RT_EINVAL`** — scan did not run or client registered manually without **`bus`**.
- **Wrong `reg` address** — probe succeeds but **`rt_i2c_transfer`** NACKs on wire.
- **Driver before bus** — no automatic re-scan; child never **`probe`** until bus registers.
- **i2c-mux depth** — scan only handles **one** level of non-compatible wrapper; deeper mux trees may need explicit client creation.
- **Name vs compatible match** — **`ids[].name`** must match DT **node name**, not **`compatible`** string; prefer **`ofw_ids`** for compatible-based binding.
- **Mixing DM client with legacy app** — app can still **`rt_i2c_bus_device_find("i2c1")`**; ensure mutex discipline if both access the same bus.

---

## See also

- @ref page_device_i2c — protocol, **`rt_i2c_transfer`**, application usage
- @ref page_device_bus — core **`rt_bus`** / **`rt_driver`**
- @ref page_device_dm — **`rt_dm_dev_iomap`**, naming
- @ref page_device_platform — controller **`RT_PLATFORM_DRIVER_EXPORT`**
- @ref page_device_ofw — DT properties
- `components/drivers/include/drivers/dev_i2c.h`
- `components/drivers/i2c/dev_i2c_bus.c`, `dev_i2c_core.c`, `dev_i2c_dm.c`
