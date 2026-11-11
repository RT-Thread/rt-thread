@page page_device_sdio SDIO / MMC core

# SDIO / MMC core (API)

**`RT_USING_SDIO`** enables the shared MMC/SD/SDIO core (`dev_mmcsd_core.c`, `dev_sd.c`, `dev_sdio.c`, …). It does **not** require **`RT_USING_DM`**.

| Topic | Page | Needs DM? |
| --- | --- | --- |
| OFW parse, **`sd%u`** naming | @ref page_device_sdio_dm | Yes |
| **`vmmc` / `vqmmc`** | @ref page_device_sdio_regulator | Yes (+ **`RT_USING_REGULATOR`**) |
| SDHCI controller | @ref page_device_sdhci | Yes (+ **`RT_USING_SDHCI`**) |

Headers: `drivers/dev_mmcsd_core.h`, `drivers/mmcsd_host.h`, `drivers/mmcsd_card.h`, `drivers/mmcsd_cmd.h`. Symbols below are in **lexicographic order** (only representative macros where there are many; see headers for full lists).

## `mmcsd_*` functions (A–Z)

| Symbol | Description |
| --- | --- |
| `mmcsd_alloc_host` | Allocate `rt_mmcsd_host`. |
| `mmcsd_change` | Host/card state change entry (after identification and negotiation). |
| `mmcsd_detect` | Card-detect worker / callback entry. |
| `mmcsd_deselect_cards` | Deselect cards. |
| `mmcsd_excute_tuning` | Run tuning (spelling matches header). |
| `mmcsd_free_host` | Free host. |
| `mmcsd_get_cid` / `mmcsd_get_csd` | Read CID/CSD. |
| `mmcsd_go_idle` | GO_IDLE_STATE. |
| `mmcsd_host_init` | Initialize host software state. |
| `mmcsd_host_lock` / `mmcsd_host_unlock` | Host bus lock. |
| `mmcsd_host_set_uhs_voltage` | Host-side UHS voltage switch. |
| `mmcsd_req_complete` | Called by low level when one `rt_mmcsd_req` completes. |
| `mmcsd_select_card` | Select card. |
| `mmcsd_select_voltage` | Choose operating voltage from OCR. |
| `mmcsd_send_abort_tuning` | Abort tuning sequence. |
| `mmcsd_send_cmd` | Send one command (with retries). |
| `mmcsd_send_request` | Submit full `rt_mmcsd_req`. |
| `mmcsd_send_tuning` | Send tuning-related command. |
| `mmcsd_set_bus_mode` / `mmcsd_set_bus_width` / `mmcsd_set_clock` / `mmcsd_set_timing` | Update host `io_cfg` and usually call `set_iocfg`. |
| `mmcsd_set_chip_select` | SPI chip select mode. |
| `mmcsd_set_data_timeout` | Set data timeout from card capability. |
| `mmcsd_set_initial_signal_voltage` | Initial signal voltage. |
| `mmcsd_set_signal_voltage` | Switch signal voltage. |
| `mmcsd_set_uhs_voltage` | UHS voltage path. |
| `mmcsd_spi_read_ocr` / `mmcsd_spi_use_crc` | SPI OCR/CRC. |
| `mmcsd_wait_cd_changed` | Wait for card-detect change. |

## `rt_mmcsd_*` functions (A–Z)

| Symbol | Description |
| --- | --- |
| `rt_mmcsd_blk_probe` / `rt_mmcsd_blk_remove` | Bind/unbind block device. |
| `rt_mmcsd_core_init` | Initialize MMC core. |

## `struct rt_mmcsd_host_ops` callbacks (A–Z)

| Symbol | Description |
| --- | --- |
| `card_busy` | Query card busy. |
| `enable_sdio_irq` | SDIO IRQ enable/disable. |
| `execute_tuning` | Sampling tuning. |
| `get_card_status` | Read card status. |
| `request` | Submit `rt_mmcsd_req`. |
| `set_iocfg` | Apply `rt_mmcsd_io_cfg` (clock, width, timing, voltage, …). |
| `signal_voltage_switch` | Signal voltage switch. |

## Main structs (A–Z)

| Symbol | Notes |
| --- | --- |
| `struct rt_mmcsd_cmd` | `cmd_code`, `arg`, `resp`, `flags`, `data`, `retries`, `err`, … |
| `struct rt_mmcsd_data` | `blksize`, `blks`, `buf`, `flags`, timeout, scatter-gather fields. |
| `struct rt_mmcsd_host` | `ops`, `io_cfg`, `freq_*`, `flags`, `card`, mutex/semaphore; with **`RT_USING_REGULATOR`**: optional `supply`; with OFW: `ofw_node`. |
| `struct rt_mmcsd_io_cfg` | `clock`, `vdd`, `bus_mode`, `bus_width`, `timing`, `signal_voltage`, … |
| `struct rt_mmcsd_req` | `cmd`, `data`, `stop`, `sbc`, `cap_cmd_during_tfr`. |

## See also

- @ref page_device_sdio_dm — OFW / host naming (DM)
- @ref page_device_sdio_regulator — supplies (DM + regulator)
- @ref page_device_sdhci — SDHCI (DM + SDHCI)
- `components/drivers/sdio/SConscript`
- `components/drivers/include/drivers/dev_mmcsd_core.h`
- `components/drivers/include/drivers/mmcsd_host.h`
- `components/drivers/include/drivers/mmcsd_card.h`
- `components/drivers/include/drivers/mmcsd_cmd.h`
