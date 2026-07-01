@page page_device_pic_cascade PIC cascade and routing

# Cascaded interrupt controllers

When a **secondary PIC** (PMIC, GPIO aggregator, PCIe INTx block, GICv2m MSI frame) sits **below** a **parent** line on another PIC.

---

## Concepts

```
  Device hwirq  →  Child PIC  →  parent virtual IRQ  →  Root PIC (GIC)  →  CPU
       |              |                    |
   irq_parse      irq_map            cascade link
```

| Link | Set by |
| --- | --- |
| **Child `pirq->hwirq`** | Child **`irq_parse`** |
| **Child virtual `irq`** | Child **`irq_map`** → **`rt_pic_config_irq`** |
| **Parent line** | **`rt_pic_cascade(child_pirq, parent_virtual_irq)`** |

---

## `rt_pic_cascade` / `rt_pic_uncascade`

```c
rt_err_t rt_pic_cascade(struct rt_pic_irq *pirq, int parent_irq);
```

| Step | Effect |
| --- | --- |
| **`pirq->parent`** | Parent **`pirq`** from **`irq2pirq(parent_irq)`** |
| Copy | **`priority`**, **`affinity`** from parent |
| **`RT_PIC_F_IRQ_ROUTING`** | Insert **`pirq`** on **`parent->children_nodes`** |

**`rt_pic_uncascade`** clears parent link and removes from children list.

**`parent_irq`** must be a **virtual IRQ** on the **parent PIC** (often from parent **`irq_map`**).

---

## Dispatch modes

### A — Hardware routing (`RT_PIC_F_IRQ_ROUTING`)

Parent **`rt_pic_handle_isr`** walks **`children_nodes`**, ack/ISR/eoi each child.

Used when parent trap fires for a **shared** line and children are registered in software tree.

### B — Dedicated parent ISR (no routing flag)

Parent IRQ has its own handler that **polls** child status and calls **`rt_pic_handle_isr`** per child.

**Rockchip PCIe INTx** (`pcie-dw-rockchip.c`):

- GIC **`legacy`** IRQ → **`rockchip_pcie_legacy_isr`**
- Reads **`PCIE_CLIENT_INTR_STATUS_LEGACY`**, per pin **`rt_pic_find_irq(&intx_pic, pin)`** → **`rt_pic_handle_isr`**

Child **`intx_pic`** has **`irq_parse`/`irq_map`** for PCI **`interrupt-map`**; cascade to GIC is via **DT** mapping the legacy line, not **`rt_pic_cascade`**.

### C — MSI / MSI-X child PIC

MSI provider allocates a line on the **child** PIC, then wires it to the **parent**:

```c
parent_irq = parent_pic->ops->irq_map(parent_pic, parent_hwirq, mode);
irq = rt_pic_config_irq(msi_pic, index, hwirq);
rt_pic_cascade(pirq, parent_irq);
```

PCI sees the **child** virtual IRQ from **`irq_alloc_msi`**. Hardware delivery is parent-specific — see @ref page_device_pic_msi.

---

## Parent helpers

After cascade, child drivers may call:

```c
rt_pic_irq_parent_mask(pirq);
rt_pic_irq_parent_unmask(pirq);
rt_pic_irq_parent_eoi(pirq);
/* … */
```

---

## Rockchip RK8xx PMIC IRQ chip

**`bsp/rockchip/dm/mfd/rk8xx.c`** — reference cascade:

1. PMIC **`rk8xx->irq`** (GPIO/IRQ from SoC) → **`rk8xx_pmic_isr`** wakes thread
2. Child **`rk8xx_irqchip`**: **`rt_pic_linear_irq`**, **`irq_map`** does:
   ```c
   irq = rt_pic_config_irq(pic, hwirq, hwirq);
   rt_pic_cascade(pirq, rk8xx_ic->rk8xx->irq);  /* PMIC pin → PMIC sub-IRQ */
   ```
3. **`irq_parse`**: one cell = sub-hwirq index
4. Thread scans status registers → **`rt_pic_handle_isr`** per pending bit

DT: **`interrupts`** on RK8xx children point at **`interrupt-controller`** sub-node.

---

## Design checklist

| Step | Action |
| --- | --- |
| 1 | Parent PIC up (**`rt_pic_init`**) |
| 2 | Child **`rt_pic_linear_irq`** |
| 3 | Child **`irq_map`** → virtual IRQ |
| 4 | **`rt_pic_cascade(child_pirq, parent_irq)`** |
| 5 | **`rt_ofw_data(child_ic_np) = child_pic`** |
| 6 | Parent ISR or **`RT_PIC_F_IRQ_ROUTING`** |

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Cascade before parent mapped | **`irq_map`** parent first |
| Wrong **`parent_irq`** | Must be virtual IRQ on parent PIC |
| Level IRQ EOI order | Child clear source before parent **EOI** |
| Missing routing + no demux ISR | Children never run |

## See also

- @ref page_device_pic_examples
- @ref page_device_pic_msi
