@page page_device_platform Platform bus

# Platform bus

Most **MMIO / on-SoC** peripherals under **`RT_USING_DM`** bind through the **platform bus**: a **`rt_platform_driver`** matches a **`rt_platform_device`**, then **`probe`** runs after the bus has applied common setup (pinctrl, clocks, power domain, IOMMU).

- Header: **`components/drivers/include/drivers/platform.h`**
- Bus logic: **`components/drivers/core/platform.c`**
- OFW enumeration: **`components/drivers/core/platform_ofw.c`**

---

## Data structures

```c
struct rt_platform_device {
    struct rt_device parent;   /* parent.ofw_node, parent.bus, parent.drv */
    int dev_id;
    const char *name;        /* non-OFW matching only */
    const struct rt_ofw_node_id *id;  /* filled by match; use id->data */
    void *priv;              /* optional driver private pointer */
};

struct rt_platform_driver {
    struct rt_driver parent;
    const char *name;
    const struct rt_ofw_node_id *ids;   /* compatible table, sentinel last */
    rt_err_t (*probe)(struct rt_platform_device *pdev);
    rt_err_t (*remove)(struct rt_platform_device *pdev);
    rt_err_t (*shutdown)(struct rt_platform_device *pdev);
};
```

In **`probe`**, almost all DM helpers take **`struct rt_device *dev = &pdev->parent`**.

---

## Boot and init order

Init levels (linker sort key, see **`rtdef.h`**):

| Level | Typical use |
| --- | --- |
| **`INIT_CORE_EXPORT`** (`"1.0"`) | **`platform_bus_init`** — **`rt_bus_register(&platform_bus)`** |
| **`INIT_SUBSYS_EXPORT`** (`"1.1"`) | Early drivers: manual **`rt_platform_driver_register()`** (e.g. **`pin-pl061`**, **`pinctrl-single`**) |
| **`INIT_PLATFORM_EXPORT`** (`"1.2"`) | **`platform_ofw_device_probe`** — walk DT, **`rt_platform_device_register`** |
| **`INIT_DEVICE_EXPORT`** (`"3"`) | **`RT_PLATFORM_DRIVER_EXPORT`** — registers driver, then probes **all** devices already on the bus |

```
INIT_CORE          → platform bus exists
INIT_SUBSYS        → some drivers registered (optional)
INIT_PLATFORM      → DT nodes → platform devices on bus → match + probe if driver already present
INIT_DEVICE        → RT_PLATFORM_DRIVER_EXPORT → register driver → probe every unmatched device
```

**Takeaway**: DT devices appear at **`INIT_PLATFORM`**. Drivers using **`RT_PLATFORM_DRIVER_EXPORT`** register later and then bind via **`rt_bus_add_driver` -> `rt_bus_for_each_dev`**. Drivers that must run before the bulk DT scan use **`INIT_SUBSYS_EXPORT`** + manual **`rt_platform_driver_register`**.

---

## Registering a driver (important)

### Method A — `RT_PLATFORM_DRIVER_EXPORT` (most common)

```c
static const struct rt_ofw_node_id my_ofw_ids[] = {
    { .compatible = "vendor,my-device" },
    { /* sentinel */ }
};

static rt_err_t my_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    /* iomap, clk, init hardware, register char/block device */
    return RT_EOK;
}

static rt_err_t my_remove(struct rt_platform_device *pdev)
{
    /* reverse probe: unregister, free */
    return RT_EOK;
}

static struct rt_platform_driver my_driver = {
    .name = "my-device",
    .ids = my_ofw_ids,
    .probe = my_probe,
    .remove = my_remove,
};

RT_PLATFORM_DRIVER_EXPORT(my_driver);
```

Macro expansion (**`driver.h`**):

```c
#define RT_PLATFORM_DRIVER_EXPORT(driver)  RT_DRIVER_EXPORT(driver, platform, BUILIN)

/* → static init calls rt_platform_driver_register(&driver) at INIT_DEVICE_EXPORT */
```

Requirements:

- **`name`**: driver name string — used for **name-based match** (see below); keep unique.
- **`ids`**: optional — **`compatible`** table for DT match; omit or set **`RT_NULL`** when using **name-only** binding.
- **`probe`**: return **`RT_EOK`** on success, **negative `rt_err_t`** on failure.
- **`remove`**: optional but recommended if **`probe`** allocates resources.

### Matching: `ids` (compatible) vs `name`

**`platform_match`** tries **both** (in order):

| Step | Condition | Match when |
| --- | --- | --- |
| 1 | **`dev->ofw_node`** set and **`pdrv->ids`** non-NULL | **`compatible`** matches an entry in **`ids`** → **`pdev->id`** points at that entry |
| 2 | **`pdev->name`** and **`pdrv->name`** both set | Strings equal (same pointer or **`rt_strcmp` == 0**) |

Implications:

- **DT devices** (from **`INIT_PLATFORM`**): normally matched by **`ids`** / **`compatible`**. This is what most drivers use.
- **No `ids`**: set **`.ids = RT_NULL`** (or omit the field) and match by **`name`** — typical when the **device** is created in board code with **`rt_platform_device_alloc("same-string")`** and **`pdev->name`** equals **`pdrv->name`**.
- **Both** can be filled: compatible is tried first; if it fails, **name** is still tried (useful only if **`pdev->name`** is a non-empty string).

Name-only driver + device:

```c
static rt_err_t legacy_probe(struct rt_platform_device *pdev) { ... return RT_EOK; }

static struct rt_platform_driver legacy_driver = {
    .name = "board-uart",   /* must equal pdev->name */
    .ids  = RT_NULL,        /* no compatible table */
    .probe = legacy_probe,
};

RT_PLATFORM_DRIVER_EXPORT(legacy_driver);

/* In board init, after bus is up: */
void board_uart_init(void)
{
    struct rt_platform_device *pdev = rt_platform_device_alloc("board-uart");
    pdev->name = "board-uart";
    rt_platform_device_register(pdev);
}
```

### Method B — manual `rt_platform_driver_register`

Used when the driver must register **before** **`INIT_PLATFORM`** (dependency ordering) or the file predates the export macro:

```c
static int my_drv_register(void)
{
    return rt_platform_driver_register(&my_driver);
}
INIT_SUBSYS_EXPORT(my_drv_register);
```

Same **`struct rt_platform_driver`** layout as method A.

### What `rt_platform_driver_register` does

1. Sets **`pdrv->parent.bus = &platform_bus`**
2. Copies **`pdrv->name`** into **`pdrv->parent.parent.name`**
3. **`rt_driver_register`** → **`rt_bus_add_driver`**
4. **`rt_bus_for_each_dev`** — for each device without **`dev->drv`**, **`platform_match`**; on match, **`platform_probe`**

Registering the driver **never** creates devices; it only enables binding.

---

## How devices get on the bus

### Automatic — device tree (`INIT_PLATFORM`)

**`platform_ofw_device_probe`** walks the tree (root, **`/clocks`**, **`/firmware`**, chosen framebuffer, …). For each **available** child with **`compatible`** (or a valid node name):

1. **`alloc_ofw_platform_device(np)`** — **`rt_platform_device_alloc`**, **`pdev->parent.ofw_node = np`**, **`np->dev = &pdev->parent`**
2. **`rt_platform_device_register(pdev)`** → **`rt_bus_add_device`** → try all drivers

**Bus nodes** (`simple-bus`, `simple-mfd`, `arm,amba-bus`, …): the walker **recurses into children first** without instantiating a device for the bus node itself (unless something else requests it).

Device naming: **`ofw_device_rename`** — e.g. **`fe300000.serial:uart0`** from **`reg`** + node name + alias.

### On demand — `rt_platform_ofw_request(np)`

Called when another driver needs a **provider** (clock, gpio, pinctrl, regulator, phye, …) before or without global probe:

| `np->dev` | Action |
| --- | --- |
| **NULL** | Allocate platform device, register on bus → match + probe |
| Set, **`dev->drv` NULL** | **`rt_bus_reload_driver_device`** — retry match |
| Set, **`dev->drv` set** | **`RT_EOK`** (already probed) |

### Manual — non-OFW / board code

```c
struct rt_platform_device *pdev = rt_platform_device_alloc("my-uart");
pdev->name = "my-uart";   /* must match pdrv->name for name-based match */
rt_platform_device_register(pdev);
```

Rare on DM + DT boards; used for legacy or test bring-up.

### Child node only — `rt_platform_ofw_device_probe_child(np)`

Registers **one** node as a platform device when it is not under **`/`** and not already **`RT_OFW_F_PLATFORM`**. Used by umbrella drivers that expose children explicitly.

---

## Match rules (`platform_match`)

See **Matching: `ids` vs `name`** above. Summary:

1. **OFW / DT**: **`rt_ofw_node_match(np, pdrv->ids)`** when **`ids`** is set — **`pdev->id`** → use **`pdev->id->data`** for SoC variants.
2. **Name**: **`pdev->name`** vs **`pdrv->name`** — works without **`ids`**; primary path for **manually registered** devices.

DT enumeration sets **`pdev->name`** from **`rt_platform_device_alloc("")`** (empty); binding those nodes still relies on **`compatible`** unless board code assigns a non-empty **`pdev->name`** that matches the driver.

Only **one** driver binds per device. No match → device stays on **`dev_list`** until a driver registers later.

---

## `platform_probe` wrapper (before your `probe`)

The bus runs **before** **`pdrv->probe(pdev)`**:

| Step | Function | Notes |
| --- | --- | --- |
| 1 | **`rt_pin_ctrl_confs_apply_by_name(dev, NULL)`** / **`pinctrl-0`** | @ref page_device_pinctrl |
| 2 | **`rt_ofw_clk_set_defaults(dev->ofw_node)`** | Assigned clocks |
| 3 | **`rt_dm_power_domain_attach(dev, RT_TRUE)`** | **`-RT_EEMPTY`** OK |
| 4 | **`rt_iommu_attach(dev)`** | **`-RT_EEMPTY`** OK if no IOMMU |
| 5 | **`pdrv->probe(pdev)`** | Your driver |

On **`probe` failure**: IOMMU detach, power domain detach, **`dev->drv` cleared**.

On **success**: **`RT_OFW_F_READLY`** set on the OFW node.

Your **`probe`** should: parse resources (**`rt_dm_dev_iomap`**, **`rt_dm_dev_get_irq`**, **`rt_clk_get_by_name`**, …) → enable hardware → register the functional **`rt_device`** (UART, pin, LED, …). Return negative **`rt_err_t`** on hard errors and free what you already allocated.

---

## Typical `probe` / `remove` pattern

```c
static rt_err_t my_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct my_dev *priv = rt_calloc(1, sizeof(*priv));

    if (!priv)
        return -RT_ENOMEM;

    priv->regs = rt_dm_dev_iomap(dev, 0);
    if (!priv->regs) {
        err = -RT_EIO;
        goto err_free;
    }

    priv->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(priv->clk)) {
        err = rt_ptr_err(priv->clk);
        goto err_unmap;
    }

    if ((err = rt_clk_prepare_enable(priv->clk)))
        goto err_clk_put;

    /* register rt_device, set rt_ofw_data for providers */
    rt_dm_dev_bind_fwdata(dev, RT_NULL, priv);

    return RT_EOK;

err_clk_put:
    rt_clk_put(priv->clk);
err_unmap:
    rt_iounmap(priv->regs);
err_free:
    rt_free(priv);
    return err;
}

static rt_err_t my_remove(struct rt_platform_device *pdev)
{
    struct my_dev *priv = rt_dm_dev_get_fwdata(&pdev->parent);
    /* unregister child device, disable clk, iounmap, rt_free(priv) */
    return RT_EOK;
}
```

**`remove` / `shutdown`**: bus calls **`pdrv->remove`**, then **`rt_iommu_detach`**, **`rt_dm_power_domain_detach`**, **`rt_platform_ofw_free(pdev)`** (drops OFW node ref, **`rt_free(pdev)`**).

---

## `pdev` fields in practice

| Field | Use |
| --- | --- |
| **`&pdev->parent`** | Pass to **`rt_dm_dev_*`**, **`rt_pin_get_named_pin`**, **`rt_ofw_*`** |
| **`pdev->id`** | After match: SoC variant via **`pdev->id->data`** (see **`pinctrl-single`** **`pcs_ofw_ids`**) |
| **`pdev->priv`** | Optional; core does not allocate it — prefer embedding **`rt_platform_device`** in your private struct or **`rt_dm_dev_bind_fwdata`** |
| **`pdev->parent.ofw_node`** | DT node for this instance |

Common pattern: embed **`struct rt_platform_device`** as **not** used — instead embed nothing and use **`struct rt_device *dev = &pdev->parent`** only; provider drivers embed **`struct rt_device_pin parent`** etc.

---

## Examples

### A — DT + `ids` (typical)

Device tree:

```dts
mydev: device@40010000 {
    compatible = "vendor,my-device";
    reg = <0x40010000 0x100>;
    interrupts = <GIC_SPI 42 IRQ_TYPE_LEVEL_HIGH>;
};
```

Driver:

```c
static rt_err_t my_probe(struct rt_platform_device *pdev) { ... }

static const struct rt_ofw_node_id my_ids[] = {
    { .compatible = "vendor,my-device" },
    { },
};

static struct rt_platform_driver my_driver = {
    .name = "vendor-my-device",
    .ids = my_ids,              /* match by compatible */
    .probe = my_probe,
};
RT_PLATFORM_DRIVER_EXPORT(my_driver);
```

**`INIT_PLATFORM`** creates the device from DT; **`INIT_DEVICE`** registers the driver and **`probe`** runs. No **`rt_platform_device_register`** in board code.

### B — name only, no `ids`

No **`compatible`** binding — driver and device share the same **`name`** string:

```c
static struct rt_platform_driver board_uart_driver = {
    .name  = "uart0",
    .ids   = RT_NULL,
    .probe = board_uart_probe,
};
RT_PLATFORM_DRIVER_EXPORT(board_uart_driver);

/* board.c */
    struct rt_platform_device *pdev = rt_platform_device_alloc("uart0");
    pdev->name = "uart0";
    rt_platform_device_register(pdev);
```

Use for legacy BSP devices not described in DT, or tests. On DM + full DT boards, prefer **example A**.

---

## When to use platform vs other buses

| Use **platform** | Use another bus |
| --- | --- |
| SoC DT node with **`compatible`**, **`reg`**, **`interrupts`** | **PCI** endpoint → **`rt_pci_driver`** |
| GPIO LED, UART, GPIO controller, syscon, firmware node | **I2C** sensor → **`rt_i2c_driver`** + client |
| Provider requested via **`rt_platform_ofw_request`** | **SPI** slave → **`rt_spi_driver`** |

Platform is the default for **on-chip** devices described in the board DTS.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`compatible` typo** | No match on DT path; device never probes — check logs |
| **Name mismatch** | **`pdev->name`** must equal **`pdrv->name`**; empty **`pdev->name`** does not match |
| **Expect name match on DT node** | DT devices need **`ids`** unless you set **`pdev->name`** explicitly |
| Driver after device is OK | **`RT_PLATFORM_DRIVER_EXPORT`** relies on **`rt_bus_add_driver`** re-walk |
| Driver too late for early deps | Use **`INIT_SUBSYS_EXPORT`** or split provider driver earlier |
| **`probe` success but no driver** | Returning **`RT_EOK`** without work — still marks node **`READLY`** |
| Missing **`remove`** | OFW node freed by bus; leaks if you allocated IRQ/DMA without teardown |
| Provider not probed | **`rt_platform_ofw_request(np)`** from consumer before using phandle |
| **`pdev->priv` unset** | Do not assume bus sets it; use **`rt_calloc`** / **`bind_fwdata`** |
| Console not ready in early **`probe`** | **`INIT_DEVICE`** is late; use **`LOG_D`** or defer prints |
| Re-probe | **`rt_bus_reload_driver_device`** when driver registers after deferred provider |

---

## See also

- @ref page_device_pinctrl — applied in **`platform_probe`** before driver **`probe`**
- @ref page_device_ofw — DT nodes, phandles
- @ref page_device_dm — **`rt_dm_dev_iomap`**, clocks, IRQ
- `documentation/6.components/device-driver/core/bus.md` — generic **`rt_bus`** / **`RT_DRIVER_EXPORT`**
- `components/drivers/core/platform.c`, `platform_ofw.c`
