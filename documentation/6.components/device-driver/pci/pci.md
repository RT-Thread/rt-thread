@page page_device_pci PCI / PCIe

# PCI and PCIe overview

**PCI/PCIe** support in RT-Thread covers config-space access, bus enumeration, BAR assignment, INTx/MSI/MSI-X, and function drivers. Implementation layout matches **`components/drivers/pci/`**.

| Source / topic | Documentation |
| --- | --- |
| **`probe.c`** — scan, setup, drivers | @ref page_device_pci_probe |
| **`access.c`** — config accessors | @ref page_device_pci_access |
| **`ecam.c`**, **`host/`** — root complex | @ref page_device_pci_host |
| **`irq.c`** — INTx assign/mask | @ref page_device_pci_irq |
| **`pme.c`** — power management | @ref page_device_pci_pme |
| **`ofw.c`** — DT ranges/IRQ | @ref page_device_pci_ofw |
| **`msi/`** | @ref page_device_pci_msi |
| **`host-bridge.c`** — bridge function driver | @ref page_device_pci_bridge |
| **`endpoint/`** — EP mode | @ref page_device_pci_endpoint |

Header: **`drivers/pci.h`**. Requires **`RT_USING_DM`** and **`RT_USING_PIC`**.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_PCI`** | Core PCI stack |
| **`RT_PCI_MSI`** | MSI / MSI-X (default y) |
| **`RT_PCI_ENDPOINT`** | Endpoint framework |
| **`RT_PCI_ECAM`** | ECAM config access |
| **`RT_PCI_SYS_64BIT`** | 64-bit resource alloc |
| **`RT_PCI_CACHE_LINE_SIZE`** | Cache line bytes written to config |
| **`RT_PCI_LOCKLESS`** | Skip global config spinlock |

Host-specific options: **`pci/host/Kconfig`**, **`pci/host/dw/Kconfig`**.

---

## Topology

```
  CPU + Host Bridge (platform driver)
        → rt_pci_host_bridge
        → root_bus (bus 0)
        → scan: endpoints + PCI bridges
        → sub-buses
        → rt_pci_driver probe per function
```

| Object | Role |
| --- | --- |
| **`struct rt_pci_host_bridge`** | Domain, **`bus_regions`**, **`rt_pci_ops`**, optional OFW node |
| **`struct rt_pci_bus`** | Bus number, device list, **`ops`** chain |
| **`struct rt_pci_device`** | BDF, BARs **`resource[]`**, caps, **`irq`**, bound driver |
| **`struct rt_pci_driver`** | **`ids[]`**, **`probe`/`remove`** |

**BDF macros**: **`RT_PCI_DEVFN`**, **`RT_PCI_DEVID`**, **`RT_PCI_SLOT`**, **`RT_PCI_FUNC`**.

---

## Bring-up order

Full call chain (host → scan → BAR → function driver): **@ref page_device_pci_probe** §「Full initialization flow」.

1. Platform **host** driver probes — @ref page_device_pci_host  
2. **`rt_pci_host_bridge_init`** — **`ranges`**, **`bus-range`** — @ref page_device_pci_ofw  
3. **`rt_pci_host_bridge_probe`** — DFS enumeration, **`rt_pci_setup_device`**, **`rt_pci_device_register`**  
4. Bus **`pci_probe`** → **`rt_pci_assign_irq`** → function **`pdrv->probe`** — IRQ: @ref page_device_pci_irq, MSI: @ref page_device_pci_msi

---

## Function driver checklist

1. Wait until **`rt_pci_setup_device`** completed (BARs in **`pdev->resource`**).
2. **`void *base = rt_pci_iomap(pdev, bar)`** before MMIO.
3. **`rt_pci_set_master`** only when DMA is ready.
4. IRQ: **`rt_pci_alloc_vector`** or **`rt_pci_msi_enable`** — not raw INTx unless legacy.
5. **`remove`**: **`rt_pci_free_vector`**, **`rt_pci_clear_master`**, disable INTx.

---

## When to use PCI

| PCI | Platform / AMBA |
| --- | --- |
| Device behind root complex with config space | Fixed SoC block with only **`reg`/`interrupts`** |

---

## See also

- @ref page_device_pic
- @ref page_device_ofw_irq
- @ref page_device_nvme
- `components/drivers/include/drivers/pci.h`
