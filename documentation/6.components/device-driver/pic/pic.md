@page page_device_pic PIC overview

# Programmable Interrupt Controller (PIC)

The **PIC** layer maps device-tree interrupts to **global virtual IRQ numbers**, dispatches ISRs, supports **cascaded** controllers, and integrates arch-specific controllers (in-tree reference: `pic-gicv2.c` / `pic-gicv3.c`) and MSI extensions.

| Topic | Page |
| --- | --- |
| Virtual IRQ, `pirq`, global table | @ref page_device_pic_irq_domain |
| Framework API (`pic.c`) | @ref page_device_pic_core |
| Cascade & routing | @ref page_device_pic_cascade |
| Device tree / `rt_ofw_map_irq` | @ref page_device_pic_ofw |
| MSI / MSI-X (PCI vectors) | @ref page_device_pic_msi |
| Rockchip / Raspberry Pi examples | @ref page_device_pic_examples |

Header: **`drivers/pic.h`**. Core: **`components/drivers/pic/pic.c`**.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_PIC`** | PIC framework (**`RT_USING_DM`**) |
| **`MAX_HANDLERS`** | Size of global virtual IRQ table (default 256) |
| **`RT_PIC_ARM_GIC`** | GICv1/v2 + OFW |
| **`RT_PIC_ARM_GIC_V2M`** | GIC MSI frame (PCI MSI) |
| **`RT_PIC_ARM_GIC_V3`** | GICv3 |
| **`RT_PIC_ARM_GIC_V3_ITS`** | GICv3 ITS + LPI |
| **`RT_USING_PIC_STATISTICS`** | ISR timing stats |
| **`SOC_DM_PIC_DIR`** | BSP-specific PIC drivers |

---

## Boot sequence (typical AArch64 DM)

From **`libcpu/aarch64/common/setup.c`**:

```
  rt_fdt_unflatten()
       |
       v
  rt_pic_init()              /* scan DT interrupt-controller nodes */
       |  ofw_pic_init → RT_PIC_OFW_DECLARE stubs (e.g. GIC)
       |  rt_pic_linear_irq, rt_pic_add_traps
       v
  rt_pic_irq_init()          /* per-PIC ops->irq_init (CPU IF enable) */
       |
       v
  rt_components_board_init() /* platform drivers, devices */
```

Root **PIC** (e.g. SoC interrupt controller) must initialize here before devices call **`rt_dm_dev_get_irq`**.

---

## Three IRQ numbers (do not confuse)

| Name | Field | Used by |
| --- | --- | --- |
| **hwirq** | **`pirq->hwirq`** | This PIC hardware line (GIC SPI 32 = hwirq 32) |
| **Virtual / logical IRQ** | **`pirq->irq`** | **`rt_pic_attach_irq`**, **`rt_hw_interrupt_*`**, **`rt_dm_dev_get_irq`** |
| **irq_index** | `0 … pic->irq_nr-1` | Index into **`pic->pirqs[]`** for that controller |

**`rt_pic_config_irq(pic, irq_index, hwirq)`** assigns **`irq = pic->irq_start + irq_index`** and stores hwirq.

---

## End-to-end (device driver view)

```
  DTS: device interrupts = <&gic GIC_SPI 77 IRQ_TYPE_LEVEL_HIGH>
       |
       v
  rt_dm_dev_get_irq(dev, 0)
       → rt_ofw_get_irq → rt_ofw_map_irq
       → gic irq_parse (hwirq=77+32) + irq_map (virtual irq)
       |
       v
  rt_pic_attach_irq(irq, handler, …)   /* or rt_hw_interrupt_install */
  rt_pic_irq_unmask(irq)
```

Secondary PIC (PMIC, PCIe INTx): see @ref page_device_pic_cascade.

---

## See also

- @ref page_device_ofw_irq
- @ref page_device_pci_irq
- @ref page_device_pci_msi
