@page page_device_pci_endpoint PCI endpoint (EP) mode

# PCI endpoint framework (`endpoint/`)

Header: **`drivers/pci_endpoint.h`**. Core: **`endpoint/endpoint.c`**, **`endpoint/mem.c`**.

SoC as **PCIe device** under a remote host — not root complex. Kconfig: **`RT_PCI_ENDPOINT`**.

---

## Core objects

| Type | Role |
| --- | --- |
| **`struct rt_pci_ep`** | Controller: **`max_functions`**, **`ops`**, **`epf`** list |
| **`struct rt_pci_epf`** | Function image (driver) |
| **`struct rt_pci_ep_header`** | Emulated config header |
| **`struct rt_pci_ep_bar`** | BAR size/flags for programming |

**`rt_pci_ep_register` / `unregister`** — global controller list under lock.

---

## Controller ops

| API | `ops` | Purpose |
| --- | --- | --- |
| **`rt_pci_ep_write_header`** | **`write_header`** | Config header for **`func_no`** |
| **`rt_pci_ep_set_bar` / `clear_bar`** | **`set_bar`** | BAR programming |
| **`rt_pci_ep_map_addr` / `unmap_addr`** | **`map_addr`** | CPU ↔ PCI map |
| **`rt_pci_ep_set_msi` / `get_msi`** | MSI doorbell |
| **`rt_pci_ep_set_msix` / `get_msix`** | MSI-X table |
| **`rt_pci_ep_raise_irq`** | **`raise_irq`** | INTx/MSI/MSI-X to host |
| **`rt_pci_ep_start` / `stop`** | Link visibility |

**`func_no < max_functions`** required; missing **`ops`** → **`-RT_ENOSYS`**.

---

## BAR validation

**`rt_pci_ep_set_bar`** rejects invalid 64-bit pairs, >4 GiB on 32-bit BAR, bad I/O flags before calling hardware.

---

## Memory helpers (`mem.c`)

**`rt_pci_ep_mem_init`**, **`rt_pci_ep_mem_array_init`** — outbound/inbound windows for host mapping.

**`host/dw/pcie-dw_ep.c`** — typical **`rt_pci_ep_ops`** implementation.

---

## Host vs endpoint

| Mode | APIs | Doc |
| --- | --- | --- |
| Root complex | **`rt_pci_host_bridge_*`**, **`rt_pci_scan_*`** | @ref page_device_pci_host |
| Endpoint | **`rt_pci_ep_*`** | this page |

Do not call host enumeration on EP controllers.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`func_no` out of range** | **`-RT_EINVAL`** |
| IRQ before link **`start`** | Host may ignore |
| 64-bit BAR layout | Follow PCI pair rules |

## See also

- @ref page_device_pci
- @ref page_device_pci_host
- `components/drivers/pci/host/dw/pcie-dw_ep.c`
