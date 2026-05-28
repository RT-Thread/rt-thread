@page page_device_pic_ofw PIC and device tree

# Device tree integration

How **`interrupts`** properties become virtual IRQs via **`irq_parse`** + **`irq_map`**.

Sources: **`pic.c`** (`ofw_pic_init`), **`ofw/irq.c`** (`rt_ofw_map_irq`).

---

## Boot: discovering controllers

**`rt_pic_init()`** → **`ofw_pic_init()`**:

```c
rt_ofw_foreach_node_by_prop(ic_np, "interrupt-controller")
    rt_ofw_stub_probe_range(ic_np, &_pic_ofw_start, &_pic_ofw_end);
```

**`RT_PIC_OFW_DECLARE(name, ids, handler)`** expands to **`RT_OFW_STUB_EXPORT(..., pic, handler)`** — same mechanism as other OFW stubs, linker section **`.rt_ofw_data.stub.*`**.

Handler (e.g. **`gicv2_ofw_init`**) must:

1. Map MMIO
2. **`rt_pic_linear_irq`**
3. **`rt_pic_add_traps`** (root only)
4. **`rt_ofw_data(np) = &pic`**

---

## Device IRQ resolution

**`rt_dm_dev_get_irq(dev, index)`** → **`ofw_api_call(get_irq)`** → **`rt_ofw_get_irq`** → **`rt_ofw_map_irq`**.

### `rt_ofw_map_irq` (core logic)

```c
pic = rt_pic_dynamic_cast(rt_ofw_data(ic_np));
pic->ops->irq_parse(pic, irq_args, &pirq);   /* RT_EOK == 0 */
irq = pic->ops->irq_map(pic, pirq.hwirq, pirq.mode);
```

| Step | Responsibility |
| --- | --- |
| **`rt_ofw_parse_irq_cells`** | Fill **`rt_ofw_cell_args`** from **`interrupts`** |
| **`irq_parse`** | Set **`out_pirq->hwirq`**, **`mode`** (GIC: type + number) |
| **`irq_map`** | **`rt_pic_config_irq`**, return **virtual IRQ** |

**`rt_pic_dynamic_cast`**: finds **`struct rt_pic`** embedded after **`rt_device`** or **`rt_object`** (name **`"PIC"`**).

---

## Example: GIC-style `#interrupt-cells` (3 cells)

From **`pic-gicv2.c`** / **`pic-gicv3.c`**:

| Cell 0 | Cell 1 | Cell 2 |
| --- | --- | --- |
| **0** = SPI, **1** = PPI, … | Interrupt number | Flags → **`RT_IRQ_MODE_*`** |

SPI DT number **0** → **hwirq 32** (`args[1] + 32`).

DTS example (Raspberry Pi 4, **`bcm2711-rpi-4-b.dts`**):

```dts
interrupts = <GIC_SPI 77 IRQ_TYPE_LEVEL_HIGH>;
```

---

## Secondary `interrupt-controller`

Child node must expose **`interrupt-controller`** + **`#interrupt-cells`** and set **`rt_ofw_data`** to its **`struct rt_pic`**.

Consumers use **`interrupt-parent = <&child_ic>`** or inherited parent.

**PCI `interrupt-map`**: resolves to parent GIC cells via @ref page_device_pci_ofw — still ends in **`rt_ofw_map_irq`**.

---

## Provider requirements for OFW

| `ops` | Required for DT devices |
| --- | --- |
| **`irq_parse`** | Yes |
| **`irq_map`** | Yes |
| **`irq_mask` / `irq_unmask`** | Strongly recommended |

Without **`irq_map`**, **`rt_ofw_map_irq`** logs error and fails.

---

## `RT_PIC_OFW_DECLARE` template

```c
static rt_err_t my_ic_ofw_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    /* map MMIO, fill my_pic.ops */
    rt_pic_linear_irq(&my_pic, NUM_LINES);
    rt_ofw_data(np) = &my_pic;
    return RT_EOK;
}

static const struct rt_ofw_node_id my_ic_ids[] = {
    { .compatible = "vendor,my-ic" },
    { /* sentinel */ },
};
RT_PIC_OFW_DECLARE(my_ic, my_ic_ids, my_ic_ofw_init);
```

Non-root: no **`rt_pic_add_traps`**; use parent ISR or cascade.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`rt_ofw_data` NULL** | Provider not probed — **`rt_platform_ofw_request`** before cast |
| **`irq_parse` returns error** | **`rt_ofw_map_irq`** fails — check cell count |
| Wrong **`interrupt-parent`** | Walk **`rt_ofw_find_irq_parent`** in OFW IRQ code |
| Mix hwirq / virtual in driver | Only use **`rt_dm_dev_get_irq`** return value |

## See also

- @ref page_device_pic_irq_domain
- @ref page_device_ofw_irq
