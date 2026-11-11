@page page_device_sdio_regulator SDIO supplies (regulator)

# SDIO / MMC and regulators

**Requires device model.** **`dev_regulator.c`** is added in **`components/drivers/sdio/SConscript`** only when **`RT_USING_DM`** and **`RT_USING_REGULATOR`** are both enabled (the regulator subsystem also depends on **`RT_USING_DM`**). You still need **`RT_USING_SDIO`** for the MMC stack.

This file links **`struct rt_mmcsd_host`** to optional **`vmmc`** (card VDD) and **`vqmmc`** (I/O / VCCQ) through **`struct rt_mmcsd_supply`** in **`drivers/mmcsd_host.h`**. Public helpers are declared in **`dev_sdio_dm.h`** (under **`#ifdef RT_USING_REGULATOR`**).

Without **`RT_USING_DM`**, there is no **`sdio_regulator_*`** implementation in-tree—handle power in your host driver or board init.

## Supply handles

| Field | Role |
| --- | --- |
| **`host->supply.vmmc`** | Card power rail from **`rt_regulator_get(dev, "vmmc")`**. |
| **`host->supply.vqmmc`** | I/O rail from **`rt_regulator_get(dev, "vqmmc")`**. |

Missing supplies are allowed (**`RT_NULL`**); hard errors from **`rt_regulator_get`** are propagated and any acquired handles are **`rt_regulator_put`** on failure paths in **`sdio_regulator_get_supply`**.

## API summary

| Function | Role |
| --- | --- |
| **`sdio_regulator_get_supply(dev, host)`** | Resolve **`vmmc`** / **`vqmmc`** for the DM **`rt_device`** backing the host. Call once from probe after **`host`** exists. |
| **`sdio_regulator_set_ocr(host, supply, vdd_bit)`** | Drives **`vmmc`** from the card OCR **vdd** bit: **`rt_regulator_set_voltage`** after **`ocrbitnum_to_vdd`**; enable/disable paths use **`host->supply.regulator_enabled`** (see **`components/drivers/sdio/dev_regulator.c`**). **`supply`** may be **`RT_NULL`** (no-op). |
| **`sdio_regulator_set_vqmmc(host, ios)`** | Adjusts **`vqmmc`** voltage for **`ios->signal_voltage`** (**`MMCSD_SIGNAL_VOLTAGE_330` / `_180` / `_120`**), using **`rt_regulator_is_supported_voltage`**, **`rt_regulator_get_voltage`**, and **`rt_regulator_set_voltage_triplet`**. For **3.3 V**, the target may be derived from **`host->io_cfg.vdd`**. Returns **`-RT_EINVAL`** if **`vqmmc`** is missing. |
| **`sdio_regulator_enable_vqmmc` / `sdio_regulator_disable_vqmmc`** | Enable or disable **`vqmmc`** and track **`vqmmc_enabled`**. |

**`host->supply.regulator_enabled`** tracks whether **`vmmc`** was enabled through the OCR path; **`vqmmc_enabled`** tracks the I/O rail.

SDHCI and DesignWare MMC hosts in-tree call these helpers during power and UHS voltage switch when **`RT_USING_REGULATOR`** is enabled (those host drivers also require DM).

## Device tree

Use the same supply names your **`rt_regulator_get`** path expects (**`vmmc`**, **`vqmmc`**) so phandles resolve to the correct **`struct rt_regulator`**. The generic regulator subsystem is described in @ref page_device_regulator.

## See also

- `components/drivers/sdio/dev_regulator.c`, `dev_sdio_dm.h`
- `components/drivers/sdio/SConscript`
- `components/drivers/include/drivers/mmcsd_host.h` (`struct rt_mmcsd_supply`, **`RT_USING_REGULATOR`**)
- @ref page_device_regulator
- @ref page_device_sdio_dm
- @ref page_device_sdhci
