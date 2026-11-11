@page page_device_sdhci SDHCI host controller

# SDHCI (SD Host Controller Interface)

**Requires device model.** In **`components/drivers/sdio/SConscript`**, **`dev_sdhci.c`**, **`dev_sdhci_dm.c`**, and **`dev_sdhci_host.c`** are built only when **`RT_USING_DM`**, **`RT_USING_SDIO`**, and **`RT_USING_SDHCI`** are all enabled. Kconfig may list **`RT_USING_SDHCI`** under SDIO alone, but the SDHCI sources in this tree **do not compile without DM**.

**`dev_sdhci.c`** implements **SDHCI 2.x/3.x/4.x** on the shared MMC/SD stack. Types and register offsets: **`drivers/dev_sdhci.h`**; **`struct rt_mmc_host`** bridge: **`drivers/dev_sdhci_host.h`**.

| Path | DM needed? | Notes |
| --- | --- | --- |
| Platform **`rt_sdhci_pltfm_*`** | Yes | **`dev_sdhci_dm.c`**: **`rt_dm_dev_iomap`**, **`rt_dm_dev_get_irq`**, DT quirks |
| PCI **`sdhci-pci.c`** | Yes | **`host/Kconfig`** is under **`RT_USING_DM && RT_USING_SDIO`** |
| Custom host without SDHCI | No (core only) | **`rt_mmcsd_host_ops`** per @ref page_device_sdio |

**`vmmc` / `vqmmc`**: power/UHS paths call **`sdio_regulator_*`** when **`RT_USING_REGULATOR`** is on—see @ref page_device_sdio_regulator.

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| **`quirks` / `quirks2`** | Prefer DT-driven bits from **`rt_sdhci_get_property`** / **`rt_sdhci_get_of_property`**, then add SoC-only flags—wrong **ADMA** or **DMA width** quirks often show up only under load as CMD / data errors. |
| **Order of init** | With DM, **`rt_dm_dev_iomap` / `rt_dm_dev_get_irq`** (or PCI BAR/IRQ) must be valid **before** **`rt_sdhci_setup_host`** reads capabilities and selects SDMA/ADMA/PIO. |
| **Probe failure / remove** | Mirror **`rt_sdhci_init_host`** with **`rt_sdhci_uninit_host`** and **`rt_sdhci_free_host`** on error and on **`remove`**—leaving a registered IRQ or workqueue causes use-after-free on unplug. |
| **UHS / 1.8 V** | **`set_uhs_signaling`**, **`voltage_switch`**, and tuning paths are board-sensitive; with regulator support, **`sdio_regulator_set_vqmmc`** must succeed. |
| **Card detect** | DT **`broken-cd`**, **`non-removable`**, and **`cap-*`** must match the socket—wrong CD polarity or missing **`non-removable`** generates spurious detect storms or no card at all. |
| **OFW** | Property names and capability flags: @ref page_device_sdio_dm. |

## Layering

| Piece | Role |
| --- | --- |
| **`struct rt_sdhci_host`** | Hardware state: **`ioaddr`**, **`irq`**, **`quirks`/`quirks2`**, **`ops`**, DMA flags, linked **`struct rt_mmc_host *mmc`**. |
| **`struct rt_mmc_host`** | Core MMC/SD/SDIO view; embedded **`rthost`** (**`struct rt_mmcsd_host`**) is what **`mmcsd_core`** uses. |
| **`struct rt_sdhci_ops`** | Optional MMIO overrides and SoC hooks (clock, bus width, reset, UHS, tuning, …). |

Default MMIO access uses **`rt_sdhci_readl` / `writel`** (and 8/16-bit variants) when **`ops->read_*`/`write_*`** are not set.

## Bring-up sequence (driver writer)

Typical order matches **`rt_sdhci_set_and_add_host`** in **`dev_sdhci.c`**:

1. **`rt_sdhci_alloc_host(dev, priv_size)`** — allocates **`rt_sdhci_host`** plus tail **`private`** bytes; wires **`mmc`** and default **`mmc_host_ops`**.
2. Fill **`host->ioaddr`**, **`host->irq`**, **`host->hw_name`**, optional **`host->ops`**, **`quirks`**, **`dma_mask`**, etc. (platform: via **`rt_sdhci_pltfm_init`**).
3. **`rt_sdhci_setup_host`** — read HCI capabilities, OCR masks, choose SDMA/ADMA/PIO, host limits.
4. **`rt_sdhci_init_host`** — timers, workqueues, IRQ **`rt_hw_interrupt_install`**, **`rt_mmc_add_host`**, card-detect enable. **`rt_sdhci_set_and_add_host`** wraps **`setup_host` + `init_host`**.

Teardown: **`rt_sdhci_uninit_host`**, **`rt_sdhci_free_host`**.

## `struct rt_sdhci_ops` (selected callbacks)

| Callback | Typical use |
| --- | --- |
| **`set_clock` / `set_bus_width` / `reset` / `set_uhs_signaling`** | Platform defaults in **`dev_sdhci_dm.c`** delegate to **`rt_sdhci_set_clock`**, **`rt_sdhci_set_bus_width`**, **`rt_sdhci_reset`**, **`rt_sdhci_set_uhs`**. |
| **`read_*` / `write_*`** | Non-memory-mapped HCI (sparse IO) or endian fixups. |
| **`irq`** | Vendor-specific interrupt demux before generic SDHCI handling. |
| **`set_power`**, **`voltage_switch`**, **`hw_reset`**, **`card_event`** | Power / card-detect / eMMC HW reset integration. |
| **`platform_execute_tuning`** | SoC-specific tuning when the generic CMD19 path is not enough. |

Full list: **`drivers/dev_sdhci.h`**.

## Quirks

**`RT_SDHCI_QUIRK_*`** and **`RT_SDHCI_QUIRK2_*`** in **`dev_sdhci.h`** document controller-specific workarounds (DMA width, ADMA, card-detect, HS200/DDR50, CMD23, preset values, …). Set them from **`struct rt_sdhci_pltfm_data`** or after **`rt_sdhci_get_property`** merges DT-driven bits.

## Platform DM (`dev_sdhci_dm.c` / `dev_sdhci_dm.h`)

Only with **`RT_USING_DM`**. **`rt_platform_device`** probe should use these helpers instead of duplicating MMIO/IRQ mapping.

| API | Role |
| --- | --- |
| **`rt_sdhci_pltfm_init(pdev, pdata, priv_size)`** | **`rt_dm_dev_iomap(dev, 0)`**, **`rt_dm_dev_get_irq(dev, 0)`**, **`rt_sdhci_alloc_host`**, assign **`sdhci_pltfm_ops`** or **`pdata->ops`**, copy **`pdata->quirks`**. |
| **`rt_sdhci_get_property` / `rt_sdhci_get_of_property`** | Reads **`sdhci,auto-cmd12`**, **`sdhci,1-bit-only`**, **`bus-width`**, **`broken-cd`**, **`no-1-8-v`**, **`clock-frequency`**, **`keep-power-in-suspend`**, **`wakeup-source`** / **`enable-sdio-wakeup`**, and sets **`quirks`**, **`quirks2`**, **`pm_caps`**. |
| **`rt_sdhci_pltfm_init_and_add_host`** | **`pltfm_init`** → **`get_property`** → **`rt_sdhci_init_host`**. |
| **`rt_sdhci_pltfm_remove` / `rt_sdhci_pltfm_free`** | **`rt_sdhci_uninit_host`** and **`rt_sdhci_free_host`**. |
| **`rt_sdhci_pltfm_clk_get_max_clock`** | **`rt_clk_get_rate`** on the platform **`clk`**. |

**`struct rt_sdhci_pltfm_data`** carries **`ops`**, **`quirks`**, **`quirks2`**. **`struct rt_sdhci_pltfm_host`** holds **`clk`**, **`clock`**, **`xfer_mode_shadow`**, and trailing private data (**`rt_sdhci_pltfm_priv`**).

## PCI glue

**`components/drivers/sdio/host/sdhci-pci.c`** (Kconfig: **`RT_SDIO_SDHCI_PCI`**, requires **`RT_USING_DM`** and **`RT_USING_SDIO`**) allocates the host with **`rt_sdhci_alloc_host`**, maps BAR0 via **`rt_pci_iomap`**, uses **`pdev->irq`**, **`rt_pci_irq_unmask`**, **`rt_pci_set_master`**, then **`rt_sdhci_set_and_add_host`**.

## Registers and spec

**`drivers/dev_sdhci.h`** defines **`RT_SDHCI_*`** MMIO offsets and capability bits aligned with the **SDHCI** and **SD Physical Layer** documents. For behaviour beyond this tree, refer to the **SD Host Controller Simplified Specification** (SD Association).

## See also

- `components/drivers/sdio/dev_sdhci.c`, `dev_sdhci_host.c`, `dev_sdhci_dm.c`, `host/sdhci-pci.c`
- `components/drivers/sdio/SConscript`
- `components/drivers/include/drivers/dev_sdhci.h`, `dev_sdhci_host.h`, `sdio/dev_sdhci_dm.h`
- @ref page_device_sdio
- @ref page_device_sdio_dm
- @ref page_device_sdio_regulator
- @ref page_device_pci
