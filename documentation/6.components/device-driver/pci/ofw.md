@page page_device_pci_ofw PCI and device tree

# PCI Open Firmware integration

Implementation: **`components/drivers/pci/ofw.c`**. Requires **`RT_USING_OFW`**.

Host controllers probe as **platform** devices; this file connects enumerated **`rt_pci_device`** instances to DT **`ranges`** and **INTx** routing.

---

## INTx: `pci_ofw_irq_parse`

Resolves **legacy PCI INTx**:

1. Device node has **`interrupts`** → **`rt_ofw_parse_irq_cells`**
2. Else read **`INTPIN`** from config; **`pin == 0`** → **`-RT_ENOSYS`**
3. Walk bus tree:
   - Device-local **`interrupt-map`** if present
   - Else P2P bridge or **host bridge** node → **`rt_ofw_parse_irq_map`** with key:

```text
map_addr[0] = (bus->number << 16) | (devfn << 8)
map_addr[3] = swizzled INTx pin   /* rt_pci_irq_intx */
```

Missing **`interrupt-map`** on root → **`-RT_EEMPTY`** (logged).

---

## `rt_pci_ofw_irq_parse_and_map`

```c
int rt_pci_ofw_irq_parse_and_map(struct rt_pci_device *pdev,
        rt_uint8_t slot, rt_uint8_t pin);
```

Calls **`pci_ofw_irq_parse`**, then **`rt_ofw_map_irq`**. Sets **`pdev->intx_pic`** from **`rt_ofw_data(irq_args.data)`**.

Host bridge may wire **`host_bridge->irq_map`** to this helper during init.

---

## `ranges` parsing

**`pci_ofw_parse_ranges`** / **`rt_pci_ofw_parse_ranges`**:

- Decodes PCI address **`space_code`** (config / I/O / 32-bit mem / 64-bit mem)
- Fills **`host_bridge->bus_regions`**: CPU phys, PCI bus addr, size, prefetch flags
- Used before **`rt_pci_region_setup`**

**`rt_pci_ofw_host_bridge_init`**, **`rt_pci_ofw_bus_init`**, **`rt_pci_ofw_device_init`** — per-node OFW hooks during probe.

---

## DT artifacts

| Property | Use |
| --- | --- |
| Host **`compatible`** | Select host driver (@ref page_device_pci_host) |
| **`reg`** | ECAM MMIO |
| **`ranges` / `dma-ranges`** | MEM/IO windows |
| **`interrupt-map` / `interrupt-map-mask`** | INTx → PIC |
| Endpoint **`reg`** (optional) | Direct **`interrupts`** on slot |

BAR values still come from config space after enumeration.

---

## MSI/MSI-X

MSI message address/data from **PIC** (**`pdev->msi_pic`**), not **`interrupts`** cells. Ensure PIC/MSI parent in DT matches host setup (@ref page_device_pci_msi).

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Missing root **`interrupt-map`** | Use MSI or fix DTS |
| Wrong swizzling | Use **`rt_pci_irq_intx`** for map key |
| Empty **`ranges`** | BAR assignment fails |

## See also

- @ref page_device_pci
- @ref page_device_pci_host
- @ref page_device_pci_irq
- @ref page_device_pci_msi
- @ref page_device_ofw_irq
- `components/drivers/pci/ofw.c`
