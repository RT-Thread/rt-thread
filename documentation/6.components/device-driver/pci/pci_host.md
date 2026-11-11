@page page_device_pci_host PCI host controllers

# Host controllers (`ecam.c`, `host/`)

SoC **root complex** drivers: map config space, parse DT **`ranges`**, call **`rt_pci_host_bridge_probe`**. Distinct from the PCI **bridge function** driver (@ref page_device_pci_bridge).

---

## ECAM (`ecam.c`, `ecam.h`)

| API | Role |
| --- | --- |
| **`pci_ecam_create(host_bridge, ops)`** | Attach **`pci_generic_ecam_ops`** (or variant) to host |
| **`pci_ecam_map(bus, devfn, where)`** | Config MMIO address |
| **`pci_generic_ecam_ops`** | Standard **`bus_shift`** ECAM |

**`struct pci_ecam_config_window`**: **`win`** base, **`bus_range[2]`**, **`bus_shift`**, **`ops`**.

### DesignWare / slot-0 quirk

**`pci_dw_ecam_bus_ops`**: on root bus, **`devfn` slot > 0** returns **`NULL`** from **`map`** (only device 0 on bus 0) — used by **`snps,dw-pcie-ecam`**, Marvell, Socionext compatibles.

---

## Generic platform host (`host/pci-host-generic.c`)

**`RT_PLATFORM_DRIVER_EXPORT(gen_pci_driver)`**

| `compatible` | ECAM ops |
| --- | --- |
| **`pci-host-ecam-generic`** | **`pci_generic_ecam_ops`** |
| **`pci-host-cam-generic`** | CAM layout, **`bus_shift = 16`** |
| **`snps,dw-pcie-ecam`**, **`marvell,armada8k-pcie-ecam`**, … | **`pci_dw_ecam_bus_ops`** |

**`pci_host_common_probe`** (`host/pci-host-common.c`):

1. **`rt_pci_host_bridge_alloc`**
2. **`rt_dm_dev_iomap(dev, 0)`** — ECAM **`reg`**
3. **`rt_pci_host_bridge_init`** — OFW ranges
4. **`pci_ecam_create`**, **`conf_win->win = base`**
5. **`rt_pci_host_bridge_probe`**

---

## DesignWare host (`host/dw/`)

| File | Role |
| --- | --- |
| **`pcie-dw_host.c`** | RC mode: DBI, link, **`rt_pci_host_bridge_probe`** |
| **`pcie-dw_ep.c`** | EP mode — @ref page_device_pci_endpoint |
| **`pcie-dw_platfrom.c`** | Platform glue |

Enable via **`pci/host/dw/Kconfig`**. DT binding typically **`snps,dw-pcie`** plus ECAM child node.

---

## Host bridge callbacks (IRQ without full OFW)

**`struct rt_pci_host_bridge`** optional:

| Field | Role |
| --- | --- |
| **`irq_slot(pdev, &pin)`** | ACPI/legacy slot for INTx |
| **`irq_map(pdev, slot, pin)`** | Return Linux IRQ number |

If NULL, OFW path or no INTx (@ref page_device_pci_irq, @ref page_device_pci_ofw).

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| ECAM **`reg` not iomapped** | **`pci_host_common_probe`** fails with **`-RT_EIO`** |
| Empty **`ranges`** | **`rt_pci_ofw_parse_ranges`** fails — no MEM/IO for BARs |
| Wrong **`compatible`** | Pick ops matching hardware CAM vs ECAM |
| Confusing with **`host-bridge.c`** | That file is PCI **function** driver for bridge devices |

## See also

- @ref page_device_pci_probe
- @ref page_device_pci_ofw
- @ref page_device_pci_access
- @ref page_device_platform
