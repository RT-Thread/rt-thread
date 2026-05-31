@page page_device_reset Reset controller

# Reset controller (`rt_reset_control`)

Header: **`components/drivers/include/drivers/reset.h`**. Core: **`components/drivers/reset/reset.c`**.

Resolves device-tree **`resets`** / **`#reset-cells`** / **`reset-names`** into **`struct rt_reset_control`** handles, then drives **`assert` / `deassert` / `reset`** on the owning **`struct rt_reset_controller`**.

This is **per-IP reset lines** (SoC reset manager), **not** whole-system power off — see @ref page_device_power_board_reset and @ref page_device_dm_power.

**Kconfig**: **`RT_USING_RESET`** (requires **`RT_USING_DM`** + **`RT_USING_OFW`**). In-tree: **`reset-simple`**, **`reset-scmi`**, **`SOC_DM_RESET_DIR`**.

---

## End-to-end flow

### Controller (provider)

```
Platform / SCMI driver probe
        |
        v
Fill rt_reset_control_ops (ofw_parse, assert, deassert [, reset, status])
        |
        v
rt_reset_controller_register(rstcer)
        |
        +-- rstcer->ofw_node set
        +-- rt_ofw_data(np) = rstcer   (object name "RSTC")
```

### Consumer (device using a reset line)

```
Consumer probe (reset controller must be registered first)
        |
        v
rstc = rt_reset_control_get_by_name(dev, "reset")
     or rt_reset_control_get_by_index(dev, 0)
        |
        v
rt_reset_control_deassert(rstc)    /* release IP from reset — typical */
        |
        v
... clocks enabled, iomap, init ...
        |
        v
remove: rt_reset_control_assert(rstc)   /* optional */
        rt_reset_control_put(rstc)
```

**Not automatic**: **`platform_probe`** does not deassert resets — the driver must **`get`** and **`deassert`** explicitly.

Typical bring-up order (@ref page_device_power): **regulator → power domain → clock → reset deassert → MMIO**.

---

## Registering a reset controller (important)

### `rt_reset_controller_register`

| Field | Role |
| --- | --- |
| **`rstcer->ofw_node`** | Controller DT node — **`rt_ofw_data`** stored here |
| **`rstcer->ops`** | **`struct rt_reset_control_ops`** |
| **`rstcer->priv`** | Driver private state (MMIO base, SCMI device, …) |

```c
struct my_rstc {
    struct rt_reset_controller controller;
    void __iomem *base;
};

static rt_err_t my_assert(struct rt_reset_control *rstc)
{
    /* rstc->id from #reset-cells — put line into reset */
    return RT_EOK;
}

static rt_err_t my_deassert(struct rt_reset_control *rstc)
{
    /* take line out of reset */
    return RT_EOK;
}

static const struct rt_reset_control_ops my_rst_ops = {
    .assert = my_assert,
    .deassert = my_deassert,
};

static rt_err_t my_rst_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct my_rstc *r = rt_calloc(1, sizeof(*r));

    r->base = rt_dm_dev_iomap(dev, 0);
    r->controller.ofw_node = dev->ofw_node;
    r->controller.ops = &my_rst_ops;
    r->controller.priv = r;

    return rt_reset_controller_register(&r->controller);
}
```

Reference: **`reset-simple.c`** — MMIO bit per line, **`INIT_SUBSYS_EXPORT`** + **`rt_platform_driver_register`**.

### `rt_reset_control_ops`

| Callback | Role |
| --- | --- |
| **`ofw_parse(rstc, args)`** | Optional: validate cells, store extra data in **`rstc->priv`** |
| **`assert`** | Active **in reset** (hold block) |
| **`deassert`** | Active **out of reset** (run block) |
| **`reset`** | Optional pulse: assert → delay → deassert |
| **`status`** | Optional: report whether line is asserted |

Default after parse: **`rstc->id = reset_args.args[0]`** (first **`#reset-cells`** argument).

Polarity (**active-low** vs **high**) is **inside** your **`assert`/`deassert`** — read the SoC TRM, not just DT naming.

### Unregister

**`rt_reset_controller_unregister`**: **`-RT_EBUSY`** if any consumer handle remains on **`rstc_nodes`** — **`put`** all **`rt_reset_control`** first.

---

## Device tree

**Controller:**

```dts
rst: reset-controller@1000 {
    compatible = "vendor,reset";
    reg = <0x1000 0x100>;
    #reset-cells = <1>;
};
```

**Consumer:**

```dts
uart@2000 {
    compatible = "vendor,uart";
    reg = <0x2000 0x100>;
    resets = <&rst 5>;
    reset-names = "uart";
};
```

| Property | Role |
| --- | --- |
| **`resets`** | Phandle + cell(s) per **`#reset-cells`** |
| **`reset-names`** | Maps name → index for **`get_by_name`** |

Multiple lines:

```dts
dma@3000 {
    resets = <&rst 10>, <&rst 11>;
    reset-names = "dma", "dma-ocp";
};
```

---

## Consumer API

| API | Role |
| --- | --- |
| **`rt_reset_control_get_by_index(dev, index)`** | Parse **`resets`** entry **index** |
| **`rt_reset_control_get_by_name(dev, name)`** | Match **`reset-names`** |
| **`rt_reset_control_get_array(dev)`** | Synthetic array control (see below) |
| **`rt_reset_control_put(rstc)`** | Remove from controller list, **`rt_free`** |
| **`rt_reset_control_deassert(rstc)`** | Release from reset (usual **probe** step) |
| **`rt_reset_control_assert(rstc)`** | Hold in reset (**remove** / suspend) |
| **`rt_reset_control_reset(rstc)`** | Pulse if **`ops->reset`** exists |
| **`rt_reset_control_status(rstc)`** | **`-RT_ENOSYS`** if no **`status`** op |

OFW variants on raw node: **`rt_ofw_get_reset_control_by_index`**, **`_by_name`**, **`_array`**.

### Error pointers

**`get_*`** may return **`rt_err_ptr(-RT_ENOMEM)`** etc. Always test:

```c
rstc = rt_reset_control_get_by_name(dev, "reset");
if (rt_is_err(rstc))
    return rt_ptr_err(rstc);
if (!rstc)
    return -RT_EEMPTY;   /* no resets property */
```

### NULL handle

**`assert` / `deassert` / `reset`** on **`NULL`** return **`RT_EOK`** (no-op). Do not use that to detect “no reset in DT” — check **`get`** return.

### Reset arrays

**`rt_reset_control_get_array`**: builds a captain **`rstc`** with **`is_array`**; **`assert`/`deassert`/`reset`** recurse into child controls with **rollback** on partial failure. Use when one logical block needs several **`resets`** entries applied together.

---

## Consumer `probe` / `remove` pattern

```c
static rt_err_t my_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rt_reset_control *rstc;
    rt_err_t err;

    rstc = rt_reset_control_get_by_name(dev, "reset");
    if (rt_is_err(rstc))
        return rt_ptr_err(rstc);

    if (rstc && (err = rt_reset_control_deassert(rstc)))
        goto err_put;

    /* clk_prepare_enable, rt_dm_dev_iomap, ... */
    pdev->priv = rstc;
    return RT_EOK;

err_put:
    if (rstc)
        rt_reset_control_put(rstc);
    return err;
}

static rt_err_t my_remove(struct rt_platform_device *pdev)
{
    struct rt_reset_control *rstc = pdev->priv;

    if (rstc) {
        rt_reset_control_assert(rstc);
        rt_reset_control_put(rstc);
    }
    return RT_EOK;
}
```

Example in-tree: **`dma-pl330.c`** (**`dma`**, **`dma-ocp`**), **`sdio-dw.c`**, **`8250-ofw.c`**, **`pinctrl-single.c`** (**`aib_rst`**).

---

## In-tree providers

| Driver | Binding | Registration |
| --- | --- | --- |
| **reset-simple** | **`snps,dw-low-reset`**, **`st,stm32-rcc`**, Allwinner, Aspeed, … | Platform **`probe`** → **`rt_reset_controller_register`** |
| **reset-scmi** | SCMI protocol **`reset`** | SCMI **`probe`** → register on agent node |

---

## Semantics cheat sheet

| Term in API | Typical meaning |
| --- | --- |
| **assert** | Line active → block held in reset |
| **deassert** | Line inactive → block can run |
| **reset** | Short assert then deassert (pulse) |

Exact bit polarity is **driver-specific** (**`reset-simple`** uses **`active_low`** in platform data).

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Controller not probed | **`get`** fails — **`rt_platform_ofw_request`** on provider or fix init order |
| **Clock vs reset order** | Enable clock only after **deassert** (or follow TRM) |
| **Skip `put`** | **`unregister`** busy; memory leak |
| **Shared reset line** | One driver **assert** while another runs → crash |
| **Wrong `id` cell** | Match **`#reset-cells`** layout in BSP doc |
| Confuse with **gpio-poweroff** | System off ≠ IP **`resets`** |
| Array partial failure | Core rolls back earlier entries — ops must be reversible |

---

## See also

- @ref page_device_power — ordering with regulator / domain / clk
- @ref page_device_power_board_reset — system shutdown GPIO (not this API)
- @ref page_device_platform — provider driver binding
- @ref page_device_clk
- @ref page_device_ofw — phandles, **`#reset-cells`**
- `components/drivers/reset/reset.c`, `reset-simple.c`
