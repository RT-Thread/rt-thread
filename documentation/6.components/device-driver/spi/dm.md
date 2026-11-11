@page page_device_spi_dm SPI device model (DM)

# SPI bus framework under `RT_USING_DM`

When **`RT_USING_DM`** and **`RT_USING_SPI`** are enabled, RT-Thread adds an **SPI-specific `rt_bus`** (`name = "spi"`) on top of the core DM layer (@ref page_device_bus). **Bus controllers** register as **`RT_Device_Class_SPIBUS`** devices (`spi0`, `spi1`, …); **slave drivers** bind as **`struct rt_spi_device`** instances discovered from device-tree children.

Legacy **manual** attach (`rt_spi_bus_attach_device`, `rt_hw_spi_device_attach`, GPIO **`user_data`**) remains valid — see @ref page_device_spi. This page covers **DT scan**, **`spi_device_ofw_parse`**, and **`RT_SPI_DRIVER_EXPORT`**.

Sources:

| File | Role |
| --- | --- |
| **`dev_spi_bus.c`** | **`struct rt_bus spi_bus`**, match/probe, **`spi_bus_scan_devices`** |
| **`dev_spi_dm.c`** | **`spi_device_ofw_parse`** |
| **`dev_spi_core.c`** | **`spi_bus_register`** → scan + CS GPIO from DT |
| **`dev_spi.h`** | **`rt_spi_driver`**, **`RT_SPI_DRIVER_EXPORT`** |
| **`dev_spi_dm.h`** | Parse / scan declarations |

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_SPI`** | Core (`dev_spi_core.c`, `dev_spi.c`, …) |
| **`RT_USING_DM`** | Adds **`dev_spi_bus.c`** + **`dev_spi_dm.c`** |
| **`RT_USING_OFW`** | Required for **`spi_bus_scan_devices`** and **`spi_device_ofw_parse`** |
| **`RT_USING_QSPI`** | QSPI bus mode **`RT_SPI_BUS_MODE_QSPI`**, alloc **`rt_qspi_device`** in scan |
| **`SOC_DM_SPI_DIR`** | BSP SoC SPI/QSPI platform drivers |

Without **`RT_USING_DM`**, **`struct rt_spi_device`** has no **`name` / `id` / `ofw_id` / `chip_select[]`** — use manual attach only.

---

## Architecture

```
  Platform SPI/QSPI controller
        |
        |  probe: iomap, clk, pinctrl; bus->parent.ofw_node = controller np
        |  rt_spi_bus_register / rt_qspi_bus_register
        v
  rt_device "spiN"  (RT_Device_Class_SPIBUS)
        |
        |  spi_bus_scan_devices(bus)   /* dev_spi_core.c, after CS pins */
        v
  For each DT child with "compatible":
        alloc rt_spi_device or rt_qspi_device
        spi_device_ofw_parse → config, reg → chip_select[]
        rt_spi_device_register → rt_bus_add_device("spi", ...)
        v
  spi_match: driver ids[].name OR ofw_ids compatible
        |
        v
  spi_probe → driver->probe(device)
        |     map cs_pin from bus->cs_pins[chip_select[0]]
        |     if parent.type == Unknown → rt_spidev_device_init (user-visible dev)
        v
  App: rt_spi_transfer* on device, or rt_device_find for spidev-style node
```

**Two layers**:

| Layer | Object | Example |
| --- | --- | --- |
| **SPI bus** | **`struct rt_spi_bus`** | Hardware adapter; **`ops->configure`**, **`ops->xfer`**, mutex **`lock`** |
| **DM SPI bus** | **`struct rt_bus` `spi_bus`** | Binds **`rt_spi_driver`** ↔ **`rt_spi_device`** |

The **platform** bus probes the **controller**; subsystem **`spi`** bus probes **children** under that controller’s OFW node.

---

## `struct rt_bus spi` (`dev_spi_bus.c`)

**`INIT_CORE_EXPORT(spi_bus_init)`** → **`rt_bus_register(&spi_bus)`**.

| Callback | Behavior |
| --- | --- |
| **`spi_match`** | 1) **`driver->ids[].name`** vs **`device->name`** (DT node name). 2) Else **`rt_ofw_node_match(ofw_node, driver->ofw_ids)`**. |
| **`spi_probe`** | Requires **`device->bus`**; **`driver->probe(device)`**; then **`cs_pin = bus->cs_pins[chip_select[0]]`** if controller listed **`cs` GPIOs**; if **`parent.type == RT_Device_Class_Unknown`**, **`rt_spidev_device_init`** registers a **`RT_Device_Class_SPIDevice`** for **`rt_device_find`**. |
| **`spi_remove` / `spi_shutdown`** | Driver hook, **`rt_free(device)`**. |

**Driver registration**:

```c
rt_err_t rt_spi_driver_register(struct rt_spi_driver *driver);
/* RT_SPI_DRIVER_EXPORT(drv) -> RT_DRIVER_EXPORT(drv, spi, BUILIN) */
```

**Client registration**:

```c
rt_err_t rt_spi_device_register(struct rt_spi_device *device);
/* rt_bus_add_device(&spi_bus, &device->parent) */
```

---

## Device tree

### Controller

```dts
spi1: spi@ff640000 {
    compatible = "rockchip,rk3588-spi", "rockchip,rk3066-spi";
    reg = <0x0 0xff640000 0x0 0x1000>;
    interrupts = <GIC_SPI 106 IRQ_TYPE_LEVEL_HIGH>;
    clocks = <&cru CLK_SPI1>, <&cru PCLK_SPI1>;
    clock-names = "spiclk", "apb_pclk";
    #address-cells = <1>;
    #size-cells = <0>;
    cs-gpios = <&gpio3 RK_PB3 GPIO_ACTIVE_LOW>;

    flash@0 {
        compatible = "jedec,spi-nor";
        reg = <0>;
        spi-max-frequency = <50000000>;
    };
};
```

| Property (controller) | Role |
| --- | --- |
| **`#address-cells` / `#size-cells`** | Standard SPI child addressing |
| **`cs-gpios`** | Optional; parsed via **`rt_pin_get_named_pin(&bus->parent, "cs", i, …)`** into **`bus->cs_pins[]`** |
| **`num-cs`** (driver-specific) | Some BSPs set **`bus->num_chipselect`** |

### Child (slave)

| Property | Role |
| --- | --- |
| **`compatible`** | Required for scan (children without it are skipped) |
| **`reg`** | Chip select index(es) → **`chip_select[]`** (up to **`RT_SPI_CS_CNT_MAX`**) |
| **`spi-max-frequency`** | **`config.max_hz`** |
| **`spi-cpol`**, **`spi-cpha`**, **`spi-cs-high`**, **`spi-lsb-first`**, **`spi-3wire`** | **`config.mode`** bits |
| **`spi-tx-bus-width`**, **`spi-rx-bus-width`** | Dual/quad line width hints (DM **`data_width_tx/rx`**) |
| **`spi-cs-setup-delay-ns`**, **`spi-cs-hold-delay-ns`**, **`spi-cs-inactive-delay-ns`** | **`rt_spi_delay`** on device |

**`spi_device_ofw_parse`** (`dev_spi_dm.c`) fills **`struct rt_spi_configuration`** and CS indices before **`rt_spi_device_register`**.

---

## `spi_bus_scan_devices`

Called from **`spi_bus_register`** when **`RT_USING_DM`** and **`bus->parent.ofw_node`** is set.

For each **available** child with **`compatible`**:

1. Allocate **`struct rt_spi_device`** or **`struct rt_qspi_device`** from **`bus->mode`**.
2. **`spi_dev->bus = bus`**, **`name = rt_ofw_node_name`**, **`parent.ofw_node = child`**.
3. **`rt_dm_dev_set_name(..., rt_ofw_node_full_name)`** (full path string).
4. **`spi_device_ofw_parse(spi_dev)`** — on error, skip device.
5. **`rt_spi_device_register(spi_dev)`** → match + probe.

**Order**: Controller **`probe`** should run before client drivers need the bus; **`RT_SPI_DRIVER_EXPORT`** drivers link at **`INIT_DEVICE_EXPORT`**. If a driver registers before the bus exists, no auto re-scan — ensure bus registers first (typical platform init order).

---

## Bus controller driver (adapter)

Pattern (SoC-specific sources under **`SOC_DM_SPI_DIR`** or BSP):

```c
static rt_err_t my_spi_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct my_spi *spi = rt_calloc(1, sizeof(*spi));

    spi->regs = rt_dm_dev_iomap(dev, 0);
    spi->irq  = rt_dm_dev_get_irq(dev, 0);
    /* rt_clk_get_by_name, prepare_enable; pinctrl from DT */

    spi->parent.parent.ofw_node = dev->ofw_node;
    spi->parent.ops = &my_spi_ops;

    rt_dm_dev_set_name_auto(&spi->parent.parent, "spi");

    return rt_spi_bus_register(&spi->parent, rt_dm_dev_get_name(dev), &my_spi_ops);
}
```

| Step | API |
| --- | --- |
| Resources | **`rt_dm_dev_iomap`**, **`rt_dm_dev_get_irq`**, **`rt_clk_*`** (@ref page_device_clk) |
| Pins | **`cs-gpios`** on controller → automatic in **`spi_bus_register`**; **`pinctrl-*`** on controller (@ref page_device_pinctrl) |
| Publish | **`rt_spi_bus_register`** or **`rt_qspi_bus_register`** — triggers **scan** |

Bit-bang: **`rt_spi_bit_add_bus`** → same **`rt_spi_bus_register`** path.

---

## Client driver (SPI slave)

```c
static const struct rt_ofw_node_id my_ids[] = {
    { .compatible = "vendor,my-flash" },
    { /* sentinel */ },
};

static struct rt_spi_driver my_driver = {
    .ofw_ids = my_ids,
    .probe   = my_probe,
    .remove  = my_remove,
};
RT_SPI_DRIVER_EXPORT(my_driver);

static rt_err_t my_probe(struct rt_spi_device *device)
{
    /* device->bus, device->chip_select[], device->config already parsed */
    /* Optional: rt_spi_configure(device, &device->config); */
    /* Register MTD/sensor or use transfers directly */
    return RT_EOK;
}
```

| Field / API | Role |
| --- | --- |
| **`device->bus`** | Parent adapter — required (**`-RT_EINVAL`** in **`spi_probe`** if NULL) |
| **`device->chip_select[0]`** | From DT **`reg`**; used with **`bus->cs_pins[]`** |
| **`device->cs_pin`** | Set in **`spi_probe`** from GPIO table or **`PIN_NONE`** |
| **`rt_spi_device_id_data(device)`** | **`id->data`** or **`ofw_id->data`** |

### Generic `spidev` path (`dev_spi.c`)

Built-in **`spidev_driver`** matches known **`compatible`** strings and DT node **names** (table in **`dev_spi.c`**). After **`spidev_probe`**, **`spi_probe`** may call **`rt_spidev_device_init`** so users get **`rt_device_find("spi1_0")`**-style names (**`%s_%d`**, bus name + CS).

**Note**: Nodes whose **`compatible`** is exactly **`"spidev"`** are **rejected** in **`spidev_probe`** — use a vendor entry from the table (e.g. **`rockchip,spidev`** is listed but contains **`spidev`** substring — the check uses **`rt_dm_dev_prop_index_of_string(..., "spidev")`** which may match **`rockchip,spidev`** — that would fail! Line 175-179 checks index of "spidev" in compatible - rockchip,spidev would match and return error. That might be intentional to block linux spidev nodes.

---

## Transfer path (unchanged by DM)

DM only affects **how devices appear**. Data path is still:

```c
rt_spi_configure(device, &cfg);   /* or use pre-parsed device->config */
rt_spi_transfer(device, tx, rx, len);
/* or rt_spi_transfer_message, send_then_recv, take_bus / release */
```

Bus mutex: **`rt_spi_take_bus`** / **`rt_spi_release_bus`**. Do not call transfer APIs from ISR (they take mutex).

---

## DM vs non-DM

| Topic | With **`RT_USING_DM`** | Without DM |
| --- | --- | --- |
| Device struct | **`rt_spi_device`** + **`rt_device parent`**, OFW fields | **`bus`**, **`config`**, **`cs_pin`**, **`user_data`** |
| Binding | **`RT_SPI_DRIVER_EXPORT`** + DT scan | **`rt_spi_bus_attach_device`**, manual **`cs_pin`** |
| Bus register | **`spi_bus_scan_devices`**, **`cs-gpios`** parse | No scan |
| Config from DT | **`spi_device_ofw_parse`** | **`rt_spi_configure`** in init code |

---

## Engineer checklist

1. **Controller**: platform **`probe`** → resources → **`bus->parent.ofw_node`** → **`rt_spi_bus_register`**.
2. **DT**: controller **`#address-cells` / `#size-cells`**, **`cs-gpios`** if needed; child **`reg`** + **`compatible`** + **`spi-max-frequency`**.
3. **Client driver**: **`ofw_ids`** (+ optional **`ids`** by node name), **`RT_SPI_DRIVER_EXPORT`**, **`probe`** uses **`device->bus`** and **`rt_spi_*`** APIs.
4. **CS**: Prefer controller **`cs-gpios`** + child **`reg`**; legacy boards can still pass GPIO in **`rt_spi_bus_attach_device`** **`user_data`** without DM.
5. **Remove**: Tear down controller bus; **`spi_remove`** frees scanned devices when bus unregisters (verify BSP order).

---

## Pitfalls

- **`device->bus == NULL`** → probe fails — scan did not run or manual device missing **`bus`**.
- **No `compatible` on child** — skipped by scan silently.
- **Wrong `reg` (CS index)** — probe OK, wrong chip selected on wire.
- **Driver before bus** — no in-tree re-scan; child never probes.
- **`ids[].name`** must match DT **node name**, not **`compatible`** — prefer **`ofw_ids`**.
- **QSPI child on SPI bus** — scan picks type from **`bus->mode`**; mismatch causes alloc/assert issues.
- **Mixing DM scan with manual attach** on same bus — possible but avoid duplicate CS / duplicate device names.

---

## See also

- @ref page_device_spi — **`rt_spi_transfer`**, attach API, QSPI, examples
- @ref page_device_bus — core **`rt_bus`**
- @ref page_device_platform — controller **`RT_PLATFORM_DRIVER_EXPORT`**
- @ref page_device_pin — **`cs-gpios`**
- @ref page_device_ofw
- `components/drivers/include/drivers/dev_spi.h`
- `components/drivers/spi/dev_spi_bus.c`, `dev_spi_core.c`, `dev_spi_dm.c`
