@page page_device_sdio_dm SDIO device model

# SDIO / MMC device model (DM)

The **MMC/SD core** (`dev_mmcsd_core.c`, …) builds with **`RT_USING_SDIO`** alone. **DM helpers** are an extra layer: only when **`RT_USING_DM`** is on does **`SConscript`** add **`dev_sdio_dm.c`** (see **`components/drivers/sdio/SConscript`**). APIs live in **`dev_sdio_dm.h`**.

| Feature | Kconfig (typical) | Source (only with **`RT_USING_DM`**) |
| --- | --- | --- |
| Host naming, OFW parse | **`RT_USING_DM`** + **`RT_USING_OFW`** for parse | `dev_sdio_dm.c` |
| SDHCI stack | **`RT_USING_DM`** + **`RT_USING_SDIO`** + **`RT_USING_SDHCI`** | `dev_sdhci.c`, `dev_sdhci_dm.c`, `dev_sdhci_host.c` |
| **`vmmc` / `vqmmc`** | **`RT_USING_DM`** + **`RT_USING_REGULATOR`** | `dev_regulator.c` |
| SoC SDHCI / DW MMC hosts | **`RT_USING_DM`** + **`RT_USING_SDIO`** | `sdio/host/*` (see **`host/Kconfig`**) |

Without **`RT_USING_DM`**, implement **`struct rt_mmcsd_host_ops`** yourself and use @ref page_device_sdio; there is **no** in-tree **`dev_sdhci_*`** or **`sdio_regulator_*`** build.

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| **Parse before card activity** | Call **`sdio_ofw_parse`** (when **`RT_USING_OFW`**) while filling **`struct rt_mmcsd_host`** and **before** the core starts enumeration—invalid **`bus-width`** yields **`-RT_EIO`**; handle in **`probe`** instead of at first transaction. |
| **Stable host names** | Prefer DTS **`aliases { mmcN = &...; }`** so **`sdio_host_set_name`** matches board wiring and userland scripts; purely software hosts still rely on **`rt_ofw_get_alias_last_id("mmc")`** to avoid colliding with aliased indices. |
| **Supplies** | **`vmmc` / `vqmmc`** need DM + regulator—see @ref page_device_sdio_regulator and @ref page_device_regulator. |
| **SDHCI (DM only)** | **`RT_USING_SDHCI`** is implemented only with DM. Platform drivers use **`dev_sdhci_dm.c`** (**`rt_dm_dev_iomap`**, **`rt_dm_dev_get_irq`**, **`rt_sdhci_get_property`**)—see @ref page_device_sdhci. |

## Host naming: `sdio_host_set_name`

**`sdio_host_set_name(host, out_devname)`** fills **`host->name`** with a stable **`sd%u`** string.

- If **`RT_USING_OFW`** and **`host->ofw_node`** are set, it first tries **`rt_ofw_get_alias_id(host->ofw_node, "mmc")`** so names align with **`aliases { mmc0 = &...; }`** in DTS.
- Otherwise it allocates a monotonic numeric id (atomically, seeded from **`rt_ofw_get_alias_last_id("mmc")`** when OFW is enabled so software-only hosts do not collide with aliased indices).

Optional **`out_devname`** receives a copy of the same string (up to **`RT_NAME_MAX`**).

## Open Firmware: `sdio_ofw_parse`

When **`RT_USING_OFW`** is enabled, **`sdio_ofw_parse(dev_np, host)`** parses common MMC controller properties from **`dev_np`** into **`struct rt_mmcsd_host`**:

| Property | Effect |
| --- | --- |
| **`bus-width`** | **`1` / `4` / `8`** → sets **`MMCSD_BUSWIDTH_*`** in **`host->flags`**; invalid values return **`-RT_EIO`**. |
| **`max-frequency`** | **`host->freq_max`**. |
| **`non-removable`** | **`MMCSD_SUP_NONREMOVABLE`**. |
| **`cap-sdio-irq`** | **`MMCSD_SUP_SDIO_IRQ`**. |
| **`cap-sd-highspeed`** / **`cap-mmc-highspeed`** | **`MMCSD_SUP_HIGHSPEED`**. |
| **`mmc-ddr-*`**, **`mmc-hs200-*`**, **`mmc-hs400-*`** | DDR / HS200 / HS400 capability flags. |
| **`sd-uhs-*`** | UHS SDR/DDR capability flags. |

It also assigns **`host->ofw_node`** if it was not already set (**`host->ofw_node ? : dev_np`**), and forces **`MMCSD_MUTBLKWRITE`** in **`host->flags`**.

Without **`RT_USING_OFW`**, **`sdio_ofw_parse`** is a stub that returns **`RT_EOK`** and does nothing.

## Regulator hooks (DM + regulator)

**`dev_regulator.c`** is compiled only when **`RT_USING_DM`** and **`RT_USING_REGULATOR`** are both set (regulator framework itself depends on DM). See @ref page_device_sdio_regulator for **`vmmc` / `vqmmc`**.

## SDHCI (DM + SDHCI)

**`RT_USING_SDHCI`** pulls in **`dev_sdhci.c`** only under **`RT_USING_DM`**. Platform probe uses **`dev_sdhci_dm.c`** (**`rt_sdhci_pltfm_init`**, **`rt_dm_dev_iomap`**, **`rt_dm_dev_get_irq`**, **`rt_sdhci_get_property`**). Details: @ref page_device_sdhci.

## See also

- `components/drivers/sdio/dev_sdio_dm.c`, `dev_sdio_dm.h`
- `components/drivers/sdio/SConscript`
- Core bus / driver binding: `documentation/6.components/device-driver/core/bus.md`
- OFW runtime API: `documentation/6.components/device-driver/ofw/ofw.md`
- @ref page_device_sdio_regulator
- @ref page_device_sdhci
