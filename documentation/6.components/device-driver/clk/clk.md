@page page_device_clk Clock framework (CLK)

# Common Clock Framework (CCF)

RT-Thread’s **CLK** subsystem (`components/drivers/clk/`) is the **Device Model (DM)** clock provider layer: device tree **`clocks`** / **`#clock-cells`** resolve to **`struct rt_clk`** handles, with **reference-counted** `prepare` / `enable` and optional **rate** / **parent** changes. It mirrors the Linux common clock model closely enough to reuse **dt-bindings** and DTS fragments.

Header: `components/drivers/include/drivers/clk.h`. Core: `components/drivers/clk/clk.c`.

Built-in providers in-tree:

| Module | Role |
| --- | --- |
| **`clk-fixed-rate.c`** | DT **`fixed-clock`** — @ref page_device_clk_fixed |
| **`clk-scmi.c`** | Clocks owned by **ARM SCMI** firmware — needs **`RT_CLK_SCMI`** |
| **`bsp/*/dm/clk/`** (e.g. Rockchip) | SoC CCM / PLL / mux / gate — via **`SOC_DM_CLK_DIR`** |

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_DM`** | Required parent — CLK is a DM feature |
| **`RT_USING_CLK`** | Build `clk.c` + selected providers; selects **`RT_USING_ADT_REF`** |
| **`RT_CLK_SCMI`** | `clk-scmi.c`; depends on **`RT_FIRMWARE_ARM_SCMI`** |
| **`SOC_DM_CLK_DIR`** | SoC adds Kconfig/SConscript under BSP `dm/clk/` |

Boot argument (OFW): **`clk_ignore_unused`** — when set, cells with **`RT_CLK_F_IGNORE_UNUSED`** skip **`disable`** even at refcount zero (debug / bring-up).

---

## Architecture

```
  Device tree consumer node
      clocks = <&cru CLK_UART2_SCLK>;
      clock-names = "baudclk", "apb_pclk";
              │
              ▼
  rt_clk_get_by_name(dev, "baudclk")  /  rt_ofw_get_clk(np, 0)
              │
              ▼
  struct rt_clk  (consumer handle: dev_id, con_id, min/max rate)
              │
              ▼
  struct rt_clk_cell  (one output: PLL child, gate, mux, fixed, …)
              │
              ▼
  struct rt_clk_node  (provider: registered with rt_clk_register)
              │
              ▼
  rt_clk_ops  (prepare/enable/recalc_rate/set_rate/set_parent/…)
```

| Object | Meaning |
| --- | --- |
| **`rt_clk_node`** | One **clock controller** in DT (e.g. `&cru`, `fixed-clock`, SCMI clock device) |
| **`rt_clk_cell`** | One **output clock** from that controller (index from `#clock-cells`) |
| **`rt_clk`** | **Consumer reference** to a cell; allocated per `get` |
| **`rt_clk_array`** | All clocks listed in consumer’s **`clocks`** property |

Provider registration stores the node on a global list (`RT_CLK_NODE_OBJ_NAME` = **`"CLKNP"`**) and attaches **`rt_ofw_data(np)`** so phandle lookup works.

---

## Consumer API (platform drivers)

Typical **`probe`** sequence on a DM device (`struct rt_device *dev` with **`dev->ofw_node`**):

```c
struct my_dev {
    struct rt_clk *clk;
    struct rt_clk *pclk;
};

/* By connection name (matches clock-names) */
pdev->clk = rt_clk_get_by_name(dev, "spiclk");
pdev->pclk = rt_clk_get_by_name(dev, "apb_pclk");

/* Or all clocks at once */
pdev->clk_arr = rt_clk_get_array(dev);

if (rt_clk_prepare_enable(pdev->pclk))
    return err;

if (rt_clk_prepare_enable(pdev->clk))
    goto disable_pclk;

freq = rt_clk_get_rate(pdev->clk);
```

| API | Role |
| --- | --- |
| **`rt_clk_get_array(dev)`** | Parse **`clocks`** + **`clock-names`** → `rt_clk_array` |
| **`rt_clk_get_by_index(dev, i)`** | Nth entry in **`clocks`** |
| **`rt_clk_get_by_name(dev, name)`** | Match **`clock-names`**; fallback: scan registered cells by **`cell->name`** |
| **`rt_clk_prepare` / `unprepare`** | May sleep (rails, firmware); refcounted per **cell** |
| **`rt_clk_enable` / `disable`** | Fast gate; enables **parent** first; refcounted |
| **`rt_clk_prepare_enable`** | `prepare` then `enable` (common in probe) |
| **`rt_clk_disable_unprepare`** | Reverse; use in `remove` / error paths |
| **`rt_clk_get_rate` / `set_rate` / `round_rate`** | Rate query and change |
| **`rt_clk_set_parent` / `get_parent`** | Reparent mux |
| **`rt_clk_set_rate_range`** | Consumer min/max constraints |
| **`rt_clk_put` / `rt_clk_array_put`** | Free consumer handles (does not disable) |

**`NULL` clock**: `rt_clk_enable(NULL)` and `rt_clk_prepare(NULL)` return **`RT_EOK`** — useful for optional clocks; still check **`rt_clk_get_*`** return before use.

Array helpers: **`rt_clk_array_prepare_enable`**, **`rt_clk_array_disable_unprepare`**, etc. — stop on first error during prepare/enable loops.

### OFW-only helpers

| API | Role |
| --- | --- |
| **`rt_ofw_get_clk(np, index)`** | Resolve phandle without `rt_device` |
| **`rt_ofw_get_clk_by_name(np, name)`** | By **`clock-names`** |
| **`rt_ofw_get_clk_array(np)`** | Full **`clocks`** list |
| **`rt_ofw_count_of_clk(clk_np)`** | Provider output count |
| **`rt_ofw_clk_get_parent_name(np, index)`** | Debug / parent name |
| **`rt_ofw_clk_set_defaults(np)`** | Apply **`assigned-clocks*`** (see below) |

If the provider is not registered yet, **`ofw_get_clk`** may call **`rt_platform_ofw_request(clk_ofw_np)`** to defer probe.

---

## Device tree (consumers)

```dts
uart2: serial@ff1a0000 {
    compatible = "rockchip,rk3588-uart", "snps,dw-apb-uart";
    reg = <0x0 0xff1a0000 0x0 0x100>;
    clocks = <&cru CLK_UART2_SRC>, <&cru CLK_UART2_FRAC>, <&cru PCLK_UART2>;
    clock-names = "baudclk", "apb_pclk";
    assigned-clocks = <&cru CLK_UART2_SRC>;
    assigned-clock-rates = <24000000>;
};
```

| Property | Role |
| --- | --- |
| **`clocks`** | Phandle + `#clock-cells` specifier per input |
| **`clock-names`** | Stable names for **`rt_clk_get_by_name`** |
| **`assigned-clocks`** | Clocks to configure when provider registers |
| **`assigned-clock-parents`** | Optional parent for each assigned clock |
| **`assigned-clock-rates`** | Optional Hz for each assigned clock |

**`rt_clk_register()`** calls **`rt_ofw_clk_set_defaults(dev->ofw_node)`** when the provider has a bound OFW node — applies assigned settings **before** consumers rely on rates.

Provider node exports clocks:

```dts
cru: clock-controller@fd7c0000 {
    compatible = "rockchip,rk3588-cru";
    #clock-cells = <1>;
    clock-output-names = "clk_uart2_src", "...";
};
```

Custom providers with multi-cell specifiers implement **`clk_np->ofw_parse(np, args)`**; default parser uses **`args->args[0]`** as cell index. **`clock-indices`** remaps DT indices to internal cell order.

---

## Provider API (clock drivers)

### `struct rt_clk_ops`

| Callback | Typical use |
| --- | --- |
| **`prepare` / `unprepare`** | PMIC / slow path; paired refcount |
| **`enable` / `disable`** | Clock gate bit |
| **`is_prepared` / `is_enabled`** | Query HW state (optional) |
| **`recalc_rate`** | Return Hz from parent rate + dividers |
| **`round_rate`** | Snap requested rate |
| **`set_rate`** | Program dividers / PLL |
| **`set_parent` / `get_parent`** | Mux select |
| **`set_phase` / `get_phase`** | DDR / SDIO phase (optional) |

Leave unused ops **`NULL`**; core skips them.

### `struct rt_clk_cell` flags

| Flag | Effect |
| --- | --- |
| **`RT_CLK_F_SET_RATE_GATE`** | Gate across rate change |
| **`RT_CLK_F_SET_PARENT_GATE`** | Gate across reparent |
| **`RT_CLK_F_SET_RATE_PARENT`** | Propagate rate change to parent |
| **`RT_CLK_F_IGNORE_UNUSED`** | Skip disable when unused (with **`clk_ignore_unused`**) |
| **`RT_CLK_F_IS_CRITICAL`** | Never auto-disable |
| **`RT_CLK_F_GET_RATE_NOCACHE`** | Always call **`recalc_rate`** |

### Register a provider

```c
struct my_cru {
    struct rt_clk_node clk_np;
    struct rt_clk_cell *cells[N];
    /* … */
};

static struct rt_clk_cell *my_cru_ofw_parse(struct rt_clk_node *np,
        struct rt_ofw_cell_args *args)
{
    rt_uint32_t idx = args->args[0];
    if (idx >= np->cells_nr)
        return RT_NULL;
    return np->cells[idx];
}

/* In probe, after filling cells[] and ops */
cru->clk_np.dev = dev;
cru->clk_np.cells = cru->cells;
cru->clk_np.cells_nr = num_clocks;
cru->clk_np.ofw_parse = my_cru_ofw_parse;

err = rt_clk_register(&cru->clk_np);
```

If the provider itself has parent clocks in DT, set **`clk_np->dev`** before register — core calls **`rt_clk_get_array(dev)`** into **`clk_np->parents_clk`**.

**`rt_clk_unregister()`** — rollback only; does not free cells.

### Notifiers

**`rt_clk_notifier_register(clk, notifier)`** — callback on **`RT_CLK_MSG_PRE_RATE_CHANGE`**, **`POST_RATE_CHANGE`**, **`ABORT_RATE_CHANGE`**.

---

## Reference counting behavior

- **`prepare_count`** / **`enable_count`** are per **`rt_clk_cell`**, shared by all consumers of that cell.
- **Enable** walks **parent** chain first; **disable** walks parent last (after local gate).
- **`rt_clk_put`** frees only the **consumer** `struct rt_clk` if it is not the cell’s primary binding — **does not** disable the clock; call **`rt_clk_disable_unprepare`** before remove.

---

## SCMI clocks

With **`RT_CLK_SCMI`**, firmware exposes clocks via **`struct rt_scmi_device`**. **`clk-scmi.c`** probes SCMI, enumerates clock IDs, and registers one **`rt_clk_node`** with many cells (`enable`/`disable`/`set_rate` via SCMI protocol).

Consumers use the same **`rt_clk_get_*`** APIs; DT points at the SCMI clock provider node. Details: @ref page_device_scmi and `components/drivers/clk/clk-scmi.c`.

---

## SoC drivers (Rockchip example)

**`bsp/rockchip/dm/clk/`** implements **`rockchip,*-cru`** style controllers: PLL (`clk-rk-pll.c`), mux, gate, divider, composite, CPU clock, MMC phase, etc. Kconfig: **`RT_CLK_ROCKCHIP`**, per-SoC **`RT_CLK_ROCKCHIP_RK3588`**, …

Consumer drivers (SPI, UART, ADC, PCIe, …) only call **`rt_clk_get_by_name`** + **`rt_clk_prepare_enable`** — they do not touch CCM registers directly.

---

## Debug

MSH ( **`RT_USING_CONSOLE`** + **`RT_USING_MSH`** ):

```text
list_clk
```

Dumps each registered **cell**: name, enable/prepare counts, rate, consumer `dev_id` / `con_id`, parent name.

---

## When to use CLK vs direct CCM writes

| Use **`rt_clk_*`** | Direct register writes may remain |
| --- | --- |
| DT lists **`clocks = <&provider …>`** | Early asm/ROM before DM |
| Multiple drivers share PLL parents | One-off bring-up with no DT |
| **`assigned-clocks`** / DVFS coordination | Fixed, always-on root osc (often still modeled as **`fixed-clock`**) |

## Engineer checklist

1. **Provider**: implement **`rt_clk_ops`**, **`ofw_parse`**, **`rt_clk_register`**; publish **`clock-output-names`**.
2. **Consumer**: **`rt_clk_get_by_name`** → **`rt_clk_prepare_enable`** → **`rt_clk_get_rate`** for divider config.
3. **Remove**: **`rt_clk_disable_unprepare`** in reverse order, then **`rt_clk_put`** / **`rt_clk_array_put`**.
4. **Probe order**: provider must register before consumers resolve phandles (deferred probe handles late providers).
5. **Optional clocks**: missing phandle → **`NULL`**; do not enable.

## Pitfalls

- **`rt_clk_put` without disable** — leaves clocks gated on and burns power.
- **Wrong `#clock-cells`** — `ofw_get_clk` fails or picks wrong mux output.
- **Rate set before enable** — some IPs need **`RT_CLK_F_SET_RATE_GATE`** or enable-first ordering.
- **assigned-clocks on consumer vs provider** — defaults run on the node that **owns** the `assigned-clocks` property when **that** node’s provider registers.
- **ISR context** — do not call **`prepare`** / **`prepare_enable`** ( **`RT_DEBUG_NOT_IN_INTERRUPT`** ).

## Detailed documents

- @ref page_device_clk_fixed — **`fixed-clock`** provider

## See also

- `components/drivers/include/drivers/clk.h`
- `components/drivers/clk/clk.c`
- @ref page_device_ofw — phandle / `clock-indices`
- @ref page_device_scmi — SCMI clock protocol
- @ref page_device_reset — often sequenced with clock enable
- @ref page_device_regulator, @ref page_device_power_domain — rails with prepare
