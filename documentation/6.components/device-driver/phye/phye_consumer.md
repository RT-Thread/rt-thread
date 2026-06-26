@page page_device_phye_consumer Phye consumer integration

# Host / MAC consumer pattern

How link-layer drivers acquire and sequence PHY bring-up **before** training or DMA.

---

## Recommended sequence

```c
struct rt_phye *phy;

phy = rt_phye_get_by_name(dev, "sata-phy");
if (rt_is_err_or_null(phy))
    return rt_ptr_err(phy) ? rt_ptr_err(phy) : -RT_ERROR;

err = rt_phye_init(phy);
if (err)
    goto put;

err = rt_phye_power_on(phy);
if (err)
    goto exit;

err = rt_phye_set_mode_simple(phy, RT_PHYE_MODE_SATA);
if (err)
    goto power_off;

/* optional: rt_phye_reset(phy) */

err = host_enable_and_train();   /* MAC-specific */
if (err)
    goto power_off;

/* store phy in driver private */

power_off:
    rt_phye_power_off(phy);
exit:
    rt_phye_exit(phy);
put:
    rt_phye_put(phy);
return err;
```

On success, keep PHY powered until **`remove`** — do not **`put`** until teardown.

---

## DesignWare AHCI example (`ata/ahci-dw.c`)

| Step | Call |
| --- | --- |
| Get | **`rt_phye_get_by_name(dev, "sata-phy")`** |
| Clocks | **`rt_clk_array_prepare_enable`** (before PHY) |
| PHY | **`rt_phye_init`** → **`rt_phye_power_on`** |
| Host | **`rt_ahci_host_register`** |
| Fail path | **`power_off`** → **`exit`** → disable clocks → **`rt_phye_put`** |
| Remove | **`exit`** + **`power_off`** (note order in source) |

DTS: host node needs **`phys`** / **`phy-names = "sata-phy"`** pointing at SATA PHY provider.

---

## PCIe host (typical)

Before **`rt_pci_host_bridge_probe`** or link training:

```c
phy = rt_phye_get_by_index(dev, 0);
rt_phye_init(phy);
rt_phye_power_on(phy);
rt_phye_set_mode(phy, RT_PHYE_MODE_PCIE, RT_PHYE_MODE_PCIE_RC);
/* then DWC / generic PCIe host probe */
```

Exact ordering vs **`clk`/`reset`** is SoC-specific — @ref page_device_pci_host.

---

## USB

Often uses **`usb-nop-xceiv`** (@ref page_device_phye_generic_usb) or SoC USB PHY:

```c
phy = rt_phye_get_by_index(dev, 0);
rt_phye_power_on(phy);
rt_phye_set_mode_simple(phy, RT_PHYE_MODE_USB_HOST_SS);
```

Generic USB driver may only implement **`power_on`/`power_off`/`reset`** — mode set optional.

---

## Error handling

| Return | Meaning |
| --- | --- |
| **`rt_err_ptr(-RT_EINVAL)`** | Bad args |
| **`rt_err_ptr` from `ofw_parse`** | DT cells wrong |
| **`NULL`** | No **`phys`** / provider missing |

Always **`rt_phye_put`** for every successful **`get`**.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Train before **`power_on`** | Link fails — follow TRM order |
| **`set_mode` while link up** | Down link first |
| Leak **`put`** | Pair with **`get`** on all paths |
| Double **`power_off`** in remove | Match **`probe`** success path |

## See also

- @ref page_device_phye
- @ref page_device_phye_ofw
- @ref page_device_pci_probe
- @ref page_device_ata
