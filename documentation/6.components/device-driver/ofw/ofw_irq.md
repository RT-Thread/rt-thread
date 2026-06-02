@page page_device_ofw_irq OFW interrupts

# Interrupts (`irq.c`)

Parse **`interrupts`**, **`interrupt-parent`**, and **`interrupt-map`** into logical IRQ numbers for @ref page_device_pic / **`rt_pic_*`**.

Header: **`drivers/ofw_irq.h`**. Source: **`components/drivers/ofw/irq.c`**.

---

## Two wiring styles

| Style | DTS | Typical use |
| --- | --- | --- |
| **Direct** | **`interrupts`** + optional **`interrupt-parent`** | SoC device on GIC |
| **Mapped** | **`interrupt-map`** + **`interrupt-map-mask`** on bridge | PCI, AMBA behind nexus |

---

## API

| API | Role |
| --- | --- |
| **`rt_ofw_irq_cells(np)`** | **`#interrupt-cells`** of interrupt controller |
| **`rt_ofw_find_irq_parent`** | Walk **`interrupt-parent`**; returns parent **`np`** and cell count |
| **`rt_ofw_parse_irq_cells(np, index, &args)`** | Parse **`interrupts`** entry → **`rt_ofw_cell_args`** |
| **`rt_ofw_parse_irq_map(np, &args)`** | Match **`interrupt-map`** row for this device |
| **`rt_ofw_map_irq(&args)`** | Final logical IRQ number via PIC layer |
| **`rt_ofw_get_irq_count`** | Number of interrupt specifiers |
| **`rt_ofw_get_irq(np, index)`** | Convenience: parse + map in one call |
| **`rt_ofw_get_irq_by_name`** | **`interrupt-names`** lookup |

---

## Recommended probe pattern

```c
struct rt_ofw_cell_args irq_args;
int irq;

if (rt_ofw_get_prop(np, "interrupt-map", RT_NULL))
{
    if (rt_ofw_parse_irq_map(np, &irq_args) != RT_EOK)
        return -RT_ERROR;
}
else
{
    if (rt_ofw_parse_irq_cells(np, 0, &irq_args) != RT_EOK)
        return -RT_ERROR;
}

irq = rt_ofw_map_irq(&irq_args);
if (irq < 0)
    return irq;

rt_pic_irq_enable(irq);  /* subsystem-specific */
```

For multiple IRQs, loop **`rt_ofw_get_irq(np, i)`** or use **`interrupt-names`**.

---

## `interrupt-map` (bridge)

Each map entry contains (per spec comment in **`irq.c`**):

1. Child unit address (**`#address-cells`** of bridge)
2. Child interrupt specifier (**`#interrupt-cells`** of bridge)
3. **`interrupt-parent`** phandle
4. Parent unit address
5. Parent interrupt specifier

**`interrupt-map-mask`** masks bits before compare. PCI host bridges are the common case — see also @ref page_device_pci_ofw.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Missing **`interrupt-parent`** | Must inherit from bus or use **`interrupt-map`** |
| Using **`rt_ofw_get_irq`** on PCI endpoint | Often need **`parse_irq_map`** first |
| Cell count mismatch | Verify parent **`#interrupt-cells`** |
| IRQ vs trigger type | Specifier may include flags — pass full **`irq_args`** to PIC driver |

## See also

- @ref page_device_ofw
- @ref page_device_ofw_base
- @ref page_device_ofw_io
- @ref page_device_pic
- @ref page_device_pci_ofw
