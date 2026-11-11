@page page_device_pci_pme PCI power management

# PME and D-states (`pme.c`)

PCI Power Management capability: D0/D1/D2/D3hot/D3cold and PME wake.

Source: **`components/drivers/pci/pme.c`**. Init from **`rt_pci_setup_device`** via **`rt_pci_pme_init`**.

---

## API

| API | Role |
| --- | --- |
| **`rt_pci_pme_init(pdev)`** | Find **`PCIY_PMG`** cap, fill **`pme_support`** bitmask |
| **`rt_pci_pme_active(pdev, enable)`** | Enable/disable PME# generation |
| **`rt_pci_enable_wake(pdev, state, enable)`** | Program wake for **D1/D2/D3hot/D3cold** |
| **`rt_pci_pme_capable(pdev, state)`** | Test **`pme_support`** bit |

**`enum rt_pci_power`**: **`RT_PCI_D0`** … **`RT_PCI_D3COLD`**, **`RT_PCI_PME_MAX`**.

---

## Bridge driver integration

**`host-bridge.c`** PM ops (**`RT_USING_PM`**) walk the bus with **`rt_pci_enum_device`** and call **`rt_pci_enable_wake`** per device on system sleep (@ref page_device_pci_bridge).

| Sleep mode | PCI target |
| --- | --- |
| Idle | D3hot |
| Light / Deep | D1 |
| Standby | D2 |
| Shutdown | D3cold |

Coordinate with **`power-domain`**, **`clk`**, **`reset`** from DM — PCI D-state alone may not gate SoC power.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| PME spec > 3 | **`rt_pci_pme_init`** logs error and aborts |
| Wake without **`pme_cap`** | **`rt_pci_pme_capable`** returns false |
| D3cold without platform support | May need PMIC/SCPI outside PCI layer |

## See also

- @ref page_device_pci_probe
- @ref page_device_pci_bridge
- @ref page_device_pci
