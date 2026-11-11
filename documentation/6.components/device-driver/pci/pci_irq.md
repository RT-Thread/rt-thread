@page page_device_pci_irq PCI INTx interrupts

# Legacy INTx (`irq.c` + core)

**INTx** (legacy PCI pin A–D) assignment and masking. MSI/MSI-X: @ref page_device_pci_msi. DT routing: @ref page_device_pci_ofw.

Sources: **`components/drivers/pci/irq.c`**, INTx helpers in **`pci.c`**.

---

## Assignment (`rt_pci_assign_irq`)

During setup, if host provides **`irq_map`**:

1. Read **`PCIR_INTPIN`** from config
2. Optional **`irq_slot`** swizzle on bridges
3. **`irq_map(pdev, slot, pin)`** → **`pdev->irq`**
4. Write **`PCIR_INTLINE`** in config

Without **`irq_map`**, logs debug and leaves IRQ 0 — use OFW or MSI.

### OFW path

**`rt_pci_ofw_irq_parse_and_map`** sets **`pdev->intx_pic`** and IRQ via **`rt_ofw_map_irq`** — preferred on DT platforms (@ref page_device_pci_ofw).

---

## Swizzling

| API | Role |
| --- | --- |
| **`rt_pci_irq_intx(pdev, pin)`** | Swizzle INTPIN across P2P bridges |
| **`rt_pci_irq_slot(pdev, &pin)`** | Slot number for **`interrupt-map`** key |

Used when building **`interrupt-map`** address cells on root bridge.

---

## Mask / unmask

| API | Role |
| --- | --- |
| **`rt_pci_intx(pdev, enable)`** | Enable/disable INTx in command register |
| **`rt_pci_check_and_mask_intx`** | Mask if supported |
| **`rt_pci_check_and_unmask_intx`** | Unmask |
| **`rt_pci_irq_mask` / `rt_pci_irq_unmask`** | Device-level helpers |

**`pdev->broken_intx_masking`**: set when hardware cannot mask INTx reliably.

---

## Unified vector API (`pci.h`, `RT_PCI_MSI`)

**`rt_pci_alloc_vector(pdev, min, max, flags, affinities)`**:

| Flag | Meaning |
| --- | --- |
| **`RT_PCI_IRQ_F_LEGACY`** | Allow INTx |
| **`RT_PCI_IRQ_F_MSI`** | Allow MSI |
| **`RT_PCI_IRQ_F_MSIX`** | Allow MSI-X |
| **`RT_PCI_IRQ_F_AFFINITY`** | CPU affinity |

Picks best available type; **`rt_pci_free_vector`** on teardown.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| MSI + INTx both active | Core often masks INTx when MSI enabled — use one path |
| **`interrupt-map` missing** | **`-RT_EEMPTY`** from OFW — enable MSI or fix DTS |
| Wrong pin after bridge | Use **`rt_pci_irq_intx`**, not raw config pin on child |
| **`irq == 0`** | May mean unassigned — do not register handler |

## See also

- @ref page_device_pci_msi
- @ref page_device_pci_ofw
- @ref page_device_ofw_irq
- @ref page_device_pic
