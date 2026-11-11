@page page_device_pic_msi PIC and PCI MSI

# MSI / MSI-X at the PIC layer

PCI **message-signalled interrupts** need an interrupt controller that can **allocate a vector**, **build the MSI message** (address + data), and **deliver** it into the same virtual IRQ space as wired IRQs.

PCI enable path: @ref page_device_pci_msi. Wiring to PIC: this page.

---

## What the MSI-capable PIC must do

| Responsibility | Typical `rt_pic_ops` |
| --- | --- |
| Hand out a **virtual IRQ** per MSI/MSI-X vector | **`irq_alloc_msi`** / **`irq_free_msi`** |
| Tell PCI what to write to the device | **`irq_compose_msi_msg`**, **`irq_write_msi_msg`** |
| Mask / unmask at hardware | Often **`irq_mask`/`irq_unmask`** + **`rt_pci_msi_*`** helpers |
| Reach the CPU interrupt architecture | Usually **cascade** to a parent PIC line (@ref page_device_pic_cascade) or a **dedicated status ISR** that demuxes bits |

The PIC driver does **not** replace PCI config-space MSI capability setup — that stays in **`pci/msi/`**. The PIC side owns **vector backing** and **message programming**.

---

## Call flow (PCI → PIC)

```
  pci/msi: rt_pci_msi_setup_irqs(pdev, nvec, type)
       |
       v
  pdev->msi_pic->ops->irq_alloc_msi(pic, msi_desc)
       |  reserve hw line / table entry
       |  rt_pic_config_irq → virtual irq
       |  optional rt_pic_cascade(child_pirq, parent_irq)
       |
       v
  irq_compose_msi_msg(pirq, &msg)  →  rt_pci_msi_write_msg
       |
       v
  Driver: rt_pic_attach_irq(virtual_irq, handler, …)
```

**`struct rt_pci_device::msi_pic`** must point at the **`struct rt_pic`** that implements these ops (from DT **`msi-parent`**, **`msi-map`**, or board setup).

---

## Implementing `irq_alloc_msi`

Typical steps inside the provider:

1. Pick a free **hwirq** / table index (bitmap or hardware allocator).
2. **`rt_pic_config_irq(pic, index, hwirq)`** — obtain **global virtual IRQ** for **`rt_pic_attach_irq`**.
3. If this PIC is not CPU-root: **`parent_irq = parent_pic->ops->irq_map(...)`** then **`rt_pic_cascade(pirq, parent_irq)`** so the parent line fires when MSI is triggered.
4. Store **`msi_desc`** on **`pirq`** if the PCI layer needs it for mask/unmask.
5. Return **virtual IRQ** (not hwirq) to **`pci/msi/irq.c`**.

**`irq_free_msi`**: **`rt_pic_uncascade`**, release index, clear bitmap.

---

## `irq_compose_msi_msg`

Fill **`struct rt_pci_msi_msg`**:

| Field | Meaning |
| --- | --- |
| **`address_lo` / `address_hi`** | Doorbell or MSI frame write target |
| **`data`** | Vector data written by device |

SoC-specific: address may be a dedicated MSI window or a parent SPI doorbell — implement per TRM, not in the generic framework.

---

## MSI vs MSI-X

| | MSI | MSI-X |
| --- | --- | --- |
| Vectors | Often power-of-two block, may need **contiguous** virtual IRQs | Per-table-entry allocation common |
| Table | Config space | Often **BAR-mapped** table — map BAR before unmask |
| PIC | Same ops; PCI layer passes count / type | Same ops; one **`irq_alloc_msi`** per entry typical |

---

## DT (optional)

Platforms may describe:

- **`msi-parent`** — phandle to MSI-capable interrupt controller
- **`msi-map` / `msi-map-mask`** — map PCI requester ID to controller + specifier

Parsing is SoC-specific; result must be **`pdev->msi_pic`** before **`rt_pci_msi_enable`**.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`RT_PCI_MSI` disabled** | Ops stubbed; PCI MSI APIs no-op |
| **`msi_pic` NULL** | Set in host/PCI probe before enable |
| Return **hwirq** to PCI | Return **virtual IRQ** from **`irq_alloc_msi`** |
| No parent link | MSI never reaches CPU — cascade or demux ISR |
| MSI-X table unmapped | Enable only after BAR iomap in PCI setup |

## See also

- @ref page_device_pci_msi
- @ref page_device_pic_cascade
- @ref page_device_pic_irq_domain
- @ref page_device_pic_core
