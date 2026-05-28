@page page_device_clk_fixed Fixed clock provider

# `fixed-clock` platform driver

Implementation: **`components/drivers/clk/clk-fixed-rate.c`**. Driver name: **`clk-fixed-rate`**. Overview: @ref page_device_clk.

Registers a **constant-frequency**, **always-on** clock with no gate, parent, or rate programming — the leaf most SoC trees hang PLLs from.

---

## Device tree

```dts
osc24m: fixed-clock {
    compatible = "fixed-clock";
    #clock-cells = <0>;
    clock-frequency = <24000000>;
    clock-accuracy = <0>;          /* optional, ppb */
    clock-output-names = "osc24m"; /* optional; becomes cell name */
};
```

Consumers:

```dts
uart0: serial@40000000 {
    clocks = <&osc24m>;
    /* clock-names optional when only one clock */
};
```

With **`#clock-cells = <0>`**, the specifier in **`clocks = <&osc24m>`** has **no extra integers** (implicit index 0).

---

## Probe flow

1. **`rt_platform_driver_register`** via **`INIT_SUBSYS_EXPORT(fixed_clk_drv_register)`** — early registration so crystal nodes probe before CCM consumers.
2. **`fixed_clk_probe`**: `rt_calloc` **`struct clk_fixed`** (embeds **`rt_clk_node`** + one **`rt_clk_fixed_rate`**).
3. **`rt_dm_dev_prop_read_u32(dev, "clock-frequency", &val)`** — **required**; probe fails without it.
4. Optional **`clock-accuracy`**, **`clock-output-names`** → **`fcell.cell.name`**.
5. Wire **`cells[0]`**, **`fixed_clk_ops`** (only **`.recalc_rate`**).
6. **`rt_clk_register(&cf->parent)`** — may run **`rt_ofw_clk_set_defaults`** if the fixed-clock node has **`assigned-clocks*`** (unusual on leaf osc).

---

## Data structures

```c
struct clk_fixed {
    struct rt_clk_node parent;
    struct rt_clk_fixed_rate fcell;
    struct rt_clk_cell *cells[1];
};

struct rt_clk_fixed_rate {
    struct rt_clk_cell cell;
    rt_ubase_t fixed_rate;
    rt_ubase_t fixed_accuracy;
};
```

| Member | Role |
| --- | --- |
| **`fixed_rate`** | Hz from **`clock-frequency`** |
| **`fixed_accuracy`** | Optional ppb from DT |
| **`cell.ops->recalc_rate`** | Returns **`fixed_rate`**; ignores parent |

No **`enable`/`disable`/`prepare`** — enabling is a no-op at ops level; framework refcount still works for consumers.

---

## OFW matching

```c
static const struct rt_ofw_node_id fixed_clk_ofw_ids[] = {
    { .compatible = "fixed-clock" },
    { /* sentinel */ }
};
```

Linux-compatible binding; same node can be shared across BSP DTS and upstream dt-bindings.

---

## When to use vs SoC CCM

| Use **`fixed-clock`** | Use SoC driver (e.g. `rockchip,*-cru`) |
| --- | --- |
| Crystal, RC oscillator, external clock input | PLL, mux, divider, gate |
| Rate fixed at boot | DVFS, dynamic reparent |
| No MMIO (or MMIO not managed here) | Large clock controller IP |

---

## Consumer example

```c
struct rt_clk *clk = rt_clk_get_by_name(dev, "uart_clk");
/* or index 0 if no clock-names */
rt_err_t err = rt_clk_prepare_enable(clk);
rt_ubase_t hz = rt_clk_get_rate(clk);
```

Fixed clocks rarely need **`rt_clk_set_rate`** — rate is fixed; **`rt_clk_get_rate`** reads **`recalc_rate`**.

---

## Pitfalls

- **Missing `clock-frequency`** — probe fails, phandle resolution returns NULL for consumers.
- **Wrong Hz in DT** — all derived PLL math wrong; UART baud, SDIO timing, etc. break silently.
- **Using `fixed-clock` for gated peripherals** — use a gate driver cell instead.
- **Name collisions** — **`clock-output-names`** should be unique enough for **`rt_clk_get_by_name`** fallback lookup.

## See also

- @ref page_device_clk
- `components/drivers/clk/clk-fixed-rate.c`
- `components/drivers/include/drivers/clk.h`
