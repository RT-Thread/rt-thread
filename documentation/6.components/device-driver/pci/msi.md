@page page_device_pci_msi PCI MSI and MSI-X

# PCI MSI / MSI-X (`msi/`)

Headers: **`drivers/pci_msi.h`**, **`pci_regs.h`**.

| File | Role |
| --- | --- |
| **`msi/msi.c`** | Capability parse, mask/unmask, message write |
| **`msi/irq.c`** | **`rt_pci_msi_setup_irqs`**, PIC allocation |
| **`msi/device.c`** | Device enable helpers |

Disabled when **`RT_PCI_MSI=n`** — stubs in **`pci.h`**.

---

## Prerequisites

- **`pdev->msi_pic`**: **`struct rt_pic`** with **`irq_alloc_msi`**, **`irq_free_msi`**, **`irq_compose_msi_msg`**
- **`pdev->msi_cap`** / **`pdev->msix_cap`** from **`rt_pci_msi_init`** / **`rt_pci_msix_init`** in setup

---

## Setup flow (`irq.c`)

**`rt_pci_msi_setup_irqs(pdev, nvec, type)`**:

### MSI

1. Read **`multi_msg_use`** (log2 vectors) from first **`rt_pci_msi_desc`**
2. **`irq_alloc_msi`** until **`nvec`** contiguous IRQs obtained
3. Per vector: **`irq_compose_msi_msg`**, **`rt_pci_msi_write_msg`**

### MSI-X

- Per table entry: separate **`irq_alloc_msi`**
- Table must be mapped (BAR assigned before enable)

**`rt_pci_msi_cleanup_irqs`** frees allocations.

---

## Driver API

| API | Use |
| --- | --- |
| **`rt_pci_msi_enable(pdev)`** | Single vector |
| **`rt_pci_msi_enable_range(pdev, min, max)`** | Power-of-two count |
| **`rt_pci_msi_enable_range_affinity(...)`** | With CPU masks |
| **`rt_pci_msix_enable(pdev, entries, count)`** | MSI-X table indices |
| **`rt_pci_msi_disable` / `rt_pci_msix_disable`** | Tear down |
| **`rt_pci_alloc_vector`** | Unified legacy/MSI/MSI-X picker (@ref page_device_pci_irq) |

---

## Masking (`msi.c`)

- **MSI**: config **`mask`** register when **`cap.is_masking`**
- **MSI-X**: per-entry vector control in table

**`rt_pci_msi_mask_irq` / `rt_pci_msi_unmask_irq`** — PIC integration.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Non-contiguous MSI vectors | Allocator retries; check return |
| MSI-X before BAR map | Enable only after **`rt_pci_setup_device`** |
| INTx still firing | Enable MSI only after masking INTx in core |
| Large MSI-X table | Default affinity storage capped — review for 2k+ entries |

## See also

- @ref page_device_pci
- @ref page_device_pci_irq
- @ref page_device_pci_ofw
- @ref page_device_pic
- `components/drivers/pci/msi/`
