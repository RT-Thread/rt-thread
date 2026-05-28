@page page_device_dma DMA engine

# DMA subsystem

## 1. DMA controller (`rt_dma_controller` / `rt_dma_controller_ops`)

Same style as **`ata/ata.md`**, for **`rt_dma_controller_register` / `rt_dma_controller_unregister`** (`components/drivers/dma/dma.c`).

### `struct rt_dma_controller` (before register)

| Member | Rule | Meaning |
| --- | --- | --- |
| `dev` | **Non-NULL** | Bound **`rt_device`**; checked at register; may **`rt_dm_dev_bind_fwdata`**. |
| `ops` | **Non-NULL** | **`rt_dma_controller_ops`**. |
| `dir_cap` | **At least one bit** | **`rt_dma_controller_add_direction`**; register fails if no direction is set. |
| `addr_mask` | **Caller** | **`RT_DMA_ADDR_MASK(n)`**, DMA-visible physical range. |
| `channels_nodes` / `mutex` | **Core** | Initialized in **`rt_dma_controller_register`**. |

### `struct rt_dma_controller_ops`

| Callback | Role |
| --- | --- |
| **`request_chan`** | Return **`rt_dma_chan`** for **`slave`** + **`fw_data`** (usually parsed **`dmas`/`dma-names`**). |
| **`release_chan`** | Pair of **`request_chan`**. |
| **`config` / `prep_*` / `start` / `pause` / `stop`** | Channel programming and run control. |

Slaves use **`rt_dma_chan_request(dev, name)`**, then **`rt_dma_chan_config`**, **`rt_dma_prep_*`**, **`rt_dma_chan_start`**, etc. (see **`drivers/dma.h`**).

### Buffers and `dma_map_ops`

**`rt_dma_alloc` / `rt_dma_free` / `rt_dma_alloc_coherent`**, **`rt_dma_sync_*`**, **`rt_dma_device_set_ops`** — see **`drivers/dma.h`**. Coherent/CMA **pools** are documented in **`documentation/6.components/device-driver/dma/pool.md`**.

### When DMA framework vs memcpy

| Prefer **`rt_dma_chan_*`** when… | memcpy / PIO may be OK when… |
| --- | --- |
| **SDIO / SPI / UART / MAC** has **`dmas`** in DTS and high throughput. | **Bootloader-stage** tiny transfers or debug-only paths. |
| You need **scatter-gather** or **cyclic** audio/I2S. | Transfer is **< cache line** and latency matters more than CPU load. |

### Slave driver checklist

1. **`rt_dma_chan_request`** in `probe` with **`dma-names`** matching DTS.
2. **`rt_dma_chan_config`** with **`src_addr_width`**, **`direction`**, **`dst_maxburst`** aligned to FIFO depth—wrong burst causes underrun/overrun.
3. **`rt_dma_prep_*` + `rt_dma_chan_start`**: pass **physical or bus addresses** per `map_ops`—never feed unrelated virtual pointers unless your `dma_map_ops` handles them.
4. **`rt_dma_chan_release`** in `remove` even if `request` partially failed after cleanup.
5. **Completion**: ISR or **`rt_dma_chan_done`**—do not sleep in ISR; wake thread for heavy post-processing.

### Controller author pitfalls

- **`dir_cap` empty** → register fails—set at least one **`RT_DMA_DIR_*`** before register.
- **`addr_mask` too narrow** → peripherals above 4G cannot be targeted—set from SoC spec.

---

## 2. API index (symbols)

Quick index into **`drivers/dma.h`** (full definitions in the header).

**Enums:** `enum rt_dma_slave_buswidth`, `enum rt_dma_transfer_direction`.

**Macros:** `RT_DMA_ADDR_MASK(n)`, `RT_DMA_F_*`, `RT_DMA_PAGE_SIZE`.

**Structs:** `struct rt_dma_chan`, `struct rt_dma_controller`, `struct rt_dma_controller_ops`, `struct rt_dma_map_ops`, `struct rt_dma_pool`, `struct rt_dma_slave_config`, `struct rt_dma_slave_transfer`.

**Inlines:** `rt_dma_alloc_coherent`, `rt_dma_free_coherent`, `rt_dma_controller_add_direction`, `rt_dma_controller_set_addr_mask`, `rt_dma_device_is_coherent`, `rt_dma_device_set_ops`.

**Functions:** `rt_dma_alloc` / `rt_dma_free`, `rt_dma_chan_config` / `done` / `pause` / `start` / `stop`, `rt_dma_chan_request` / `release`, `rt_dma_controller_register` / `unregister`, `rt_dma_pool_extract` / `install`, `rt_dma_prep_cyclic` / `memcpy` / `single`, `rt_dma_sync_in_data` / `out_data`.

## See also

- DMA memory pools: `documentation/6.components/device-driver/dma/pool.md`
- `components/drivers/include/drivers/dma.h`
- `components/drivers/dma/dma.c`
