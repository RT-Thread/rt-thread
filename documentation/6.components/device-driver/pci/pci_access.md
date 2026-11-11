@page page_device_pci_access PCI config space access

# Config space (`access.c`, `rt_pci_ops`)

All enumeration and drivers reach hardware through **`struct rt_pci_ops`** on each **`rt_pci_bus`**.

Sources: **`components/drivers/pci/access.c`**, **`ecam.c`** (typical **`ops`** implementation).

---

## `struct rt_pci_ops`

| Callback | Role |
| --- | --- |
| **`map(bus, devfn, reg)`** | Optional MMIO pointer to config dword (ECAM) |
| **`read(bus, devfn, reg, width, &value)`** | Config read |
| **`write(bus, devfn, reg, width, value)`** | Config write |
| **`add` / `remove`** | Bus hook (optional) |

Host bridge sets **`host_bridge->ops`**; child buses inherit or use **`child_ops`**.

---

## Locked accessors (`access.c`)

| API | Role |
| --- | --- |
| **`rt_pci_bus_read_config_u8/u16/u32`** | Bus-level read |
| **`rt_pci_bus_write_config_u8/u16/u32`** | Bus-level write |
| **`rt_pci_bus_read_config_uxx`** | Width 1/2/4; uses **`map`** if implemented |
| **`rt_pci_read_config_* (pdev, …)`** | Inline wrappers using **`pdev->devfn`** |

Global **`rt_pci_lock`** serializes config unless **`RT_PCI_LOCKLESS=y`**.

On read error, typed helpers may return **`~0`** — check **`rt_err_t`** from **`bus->ops->read`** when critical.

---

## ECAM fast path

**`pci_ecam_map`** computes:

```text
win + (bus_offset | devfn_offset | reg_offset)
```

**`rt_pci_bus_read_config_uxx`** reads via **`HWREG8/16/32`** when **`map`** is non-NULL.

See @ref page_device_pci_host for **`pci_generic_ecam_ops`** and DesignWare **`bus_shift`** variants.

---

## Config space size

**`pdev->cfg_size`** set in **`rt_pci_setup_device`**:

- Standard 256 bytes, or extended 4 KiB if extended capability present.

Use **`rt_pci_find_capability`** only within valid size.

---

## MMIO from BAR (not config)

| API | Role |
| --- | --- |
| **`rt_pci_iomap(pdev, bar_idx)`** | **`rt_ioremap(resource[bar].base, size)`** |

BAR CPU addresses come from enumeration — do not confuse with ECAM config window.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Config during IRQ | Lock held by **`access.c`** — avoid long callbacks under lock |
| **`map` returns NULL** | Fall back to **`read`/`write`** ops only |
| Wrong **`devfn`** on secondary bus | Always use **`pdev->devfn`** on device's bus |
| Byte enables on IO | Use correct width API for register layout |

## See also

- @ref page_device_pci_probe
- @ref page_device_pci_host
- @ref page_device_pci
