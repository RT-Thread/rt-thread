@page page_device_pci_bridge PCI bridge function driver

# PCI bridge function driver (`host-bridge.c`)

**Not** the SoC host controller (@ref page_device_pci_host). This is the **`RT_PCI_DRIVER_EXPORT`** driver for **PCI bridge functions** (root ports, P2P bridges, certain virtual bridges).

Source: **`components/drivers/pci/host-bridge.c`**.

---

## Matched devices

```c
static const struct rt_pci_device_id host_bridge_pci_ids[] = {
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0008) },
    { RT_PCI_DEVICE_CLASS(PCIS_BRIDGE_PCI_NORMAL, ~0) },
    { RT_PCI_DEVICE_CLASS(PCIS_BRIDGE_PCI_SUBTRACTIVE, ~0) },
    { RT_PCI_DEVICE_CLASS(((PCIS_SYSTEM_RCEC << 8) | 0x00), ~0) },
    { /* sentinel */ }
};
```

Vendor-specific bridge drivers should register **narrower** **`rt_pci_device_id`** entries **before** this generic match.

---

## Probe / remove

| Callback | Behavior |
| --- | --- |
| **`host_bridge_probe`** | **`rt_pci_set_master(pdev)`**; optional PM register |
| **`host_bridge_remove`** | **`rt_pci_clear_master`** |
| **`host_bridge_shutdown`** | PM unregister |

No BAR programming here — windows configured during enumeration (@ref page_device_pci_probe).

---

## Power management (`RT_USING_PM`)

**`host_bridge_pm_suspend` / `resume`**: **`rt_pci_enum_device`** on bus, **`rt_pci_enable_wake`** per function (@ref page_device_pci_pme).

| Sleep | PCI state |
| --- | --- |
| Idle | D3hot |
| Light / Deep | D1 |
| Standby | D2 |
| Shutdown | D3cold |

---

## Component map

| Layer | Location | Role |
| --- | --- | --- |
| Host RC | **`pci/host/`**, **`ecam.c`** | Enumeration |
| Bridge function | **`host-bridge.c`** | Bus master + PM on bridge devfn |
| OFW INTx | **`pci/ofw.c`** | **`interrupt-map`** |

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Expect BAR setup here | Done in core PCI |
| Generic class match | Override with specific driver if needed |

## See also

- @ref page_device_pci
- @ref page_device_pci_host
- @ref page_device_pci_pme
- @ref page_device_pci_ofw
