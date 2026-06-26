@page page_device_phye_core Phye core API

# Core framework (`phye.c`)

Registration, reference-counted **`init`/`power_on`**, and **`set_mode`**. Source: **`components/drivers/phye/phye.c`**.

---

## Objects

| Type | Role |
| --- | --- |
| **`struct rt_phye`** | **`dev`**, **`ops`**, **`init_count`**, **`power_count`**, **`lock`** |
| **`struct rt_phye_ops`** | Provider callbacks (all optional except as needed) |

**`rt_phye_register`** requires **`phye->dev`** and **`phye->ops`**, calls **`rt_dm_dev_bind_fwdata(dev, NULL, phye)`** so **`rt_ofw_data(phy_np)`** resolves the provider.

**`rt_phye_unregister`** fails with **`-RT_EBUSY`** if **`dev->ref_count != 0`**.

---

## Reference counting

| API | Behavior |
| --- | --- |
| **`rt_phye_init` / `rt_phye_exit`** | **`ops->init`** on first **`init`**; **`ops->exit`** when **`init_count`** returns to 0 |
| **`rt_phye_power_on` / `rt_phye_power_off`** | Same pattern for **`power_on`/`power_off`** |
| **`rt_phye_reset`** | No refcount — call when driver needs pulse |
| **`rt_phye_set_mode`** | No refcount — configure mode each time (serialized by lock) |

**`NULL` phye** pointer: APIs return **`RT_EOK`** (no-op) — useful for optional PHY in consumer code.

---

## `rt_phye_ops`

| Callback | Typical use |
| --- | --- |
| **`init`** | One-time calibration, load OTP/NVMEM |
| **`exit`** | Reverse **`init`** |
| **`reset`** | GPIO or soft reset pulse |
| **`power_on`** | Enable regulators/clocks, exit reset |
| **`power_off`** | Gate power/clocks |
| **`set_mode`** | USB speed, PCIe RC/EP, SATA, MIPI, … |
| **`ofw_parse`** | Decode **`#phy-cells`** after phandle resolve |

---

## Modes (`enum rt_phye_mode`)

| Range | Examples |
| --- | --- |
| **`< RT_PHYE_MODE_MAX`** | **`RT_PHYE_MODE_USB_HOST_HS`**, **`RT_PHYE_MODE_PCIE`**, **`RT_PHYE_MODE_SATA`**, **`RT_PHYE_MODE_MIPI_DPHY`**, … |
| **`>= RT_PHYE_MODE_MAX`** (submode only) | **`RT_PHYE_MODE_PCIE_RC`**, **`RT_PHYE_MODE_PCIE_EP`**, **`RT_PHYE_MODE_PCIE_BIFURCATION`** |

**PCIe example** (base mode + submode):

```c
rt_phye_set_mode(phy, RT_PHYE_MODE_PCIE, RT_PHYE_MODE_PCIE_RC);
```

**Simple mode** (no submode):

```c
rt_phye_set_mode_simple(phy, RT_PHYE_MODE_SATA);
/* same as set_mode(..., RT_PHYE_MODE_INVALID) */
```

**`rt_phye_set_mode`** returns **`-RT_EINVAL`** if **`mode >= RT_PHYE_MODE_MAX`** or submode is invalid.

---

## Acquire / release (consumer)

| API | Role |
| --- | --- |
| **`rt_phye_get_by_index(dev, index)`** | Parse **`phys`** on **`dev->ofw_node`** |
| **`rt_phye_get_by_name(dev, id)`** | **`phy-names`** → index |
| **`rt_phye_put(phye)`** | Decrement **`dev->ref_count`** |

Returns **`rt_err_ptr(...)`** on failure — use **`rt_is_err_or_null(phye)`** before use.

**`get`** bumps **`ref_count`** under **`phye->lock`**.

---

## See also

- @ref page_device_phye_ofw
- @ref page_device_phye_provider
- @ref page_device_phye_consumer
