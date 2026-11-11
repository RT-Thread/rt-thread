@page page_device_phye Generic PHY (Phye)

# PHY abstraction (phye) overview

**Phye** is the DM framework for **external PHY** blocks: SerDes/USB/PCIe/SATA/MIPI PHY that sit beside the MAC/host controller and are shared via device tree **`phys`** phandles.

| Topic | Page |
| --- | --- |
| Core API, refcount, modes | @ref page_device_phye_core |
| Device tree **`phys` / `#phy-cells`** | @ref page_device_phye_ofw |
| Implement a PHY provider | @ref page_device_phye_provider |
| Host / MAC consumer pattern | @ref page_device_phye_consumer |
| Built-in **`usb-nop-xceiv`** | @ref page_device_phye_generic_usb |

Header: **`drivers/phye.h`**. Core: **`components/drivers/phye/phye.c`**.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_PHYE`** | Framework (**`RT_USING_DM`**) |
| **`RT_PHYE_GENERIC_USB`** | **`usb-nop-xceiv`** platform driver |
| **`SOC_DM_PHYE_DIR`** | BSP adds SoC-specific PHY drivers via **`osource`** |

Use phye only when the PHY is **not** fully embedded in the controller IP.

---

## Architecture

```
  PHY provider (platform driver)
       rt_phye_register()  →  rt_ofw_data(phy_node) = rt_phye *
              ^
              |  phys + #phy-cells [+ phy-names]
              |
  Consumer (USB/PCIe/SATA/AHCI/… host driver)
       rt_phye_get_by_index/name → init → power_on → set_mode
       … link training / MAC start …
       power_off → exit → rt_phye_put
```

Providers implement **`struct rt_phye_ops`**; the core handles **reference counting** on **`init`** / **`power_on`**.

---

## When to use phye

| Use **`rt_phye_*`** | Skip phye |
| --- | --- |
| DT **`phys`** on host; PHY has own **`compatible`** node | PHY registers only touched inside one driver |
| Same PHY IP shared (mux) or tuning table reused | No OFW and fixed **`board.c`** init |

---

## Power-up order (typical)

Follow SoC TRM; common sequence:

1. Regulator / power domain  
2. Reference clock (**`rt_clk_prepare_enable`**)  
3. Deassert reset  
4. **`rt_phye_init`** → **`rt_phye_power_on`**  
5. **`rt_phye_set_mode`** (lane rate, USB HS/SS, PCIe RC/EP, …)  
6. Host link training / MAC enable  

Teardown in reverse; see @ref page_device_phye_consumer.

---

## In-tree consumers (examples)

| Consumer | PHY lookup | Source |
| --- | --- | --- |
| DesignWare AHCI | **`rt_phye_get_by_name(dev, "sata-phy")`** | **`ata/ahci-dw.c`** |
| USB host/device | **`phys`** → generic or SoC PHY | BSP + @ref page_device_phye_generic_usb |

PCIe host drivers may call **`RT_PHYE_MODE_PCIE`** before training when BSP supplies a PHY driver under **`SOC_DM_PHYE_DIR`**.

---

## See also

- @ref page_device_ofw_base — phandle pattern
- @ref page_device_pci_host
- @ref page_device_clk
- `components/drivers/include/drivers/phye.h`
