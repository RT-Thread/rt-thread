@page page_device_dma_pool DMA memory pools

# DMA coherent / CMA pools

Header: `struct rt_dma_pool` and **`rt_dma_pool_*`** in `components/drivers/include/drivers/dma.h`. Implementation: `components/drivers/dma/dma_pool.c`.

**`rt_dma_alloc` / `rt_dma_free`** (and default **`rt_dma_map_ops`**) allocate from installed pools instead of the generic heap when **`RT_USING_DMA`** and memblock reservations are configured. Controllers and slaves still use **`documentation/6.components/device-driver/dma/dma.md`** for channel programming; pools only back **buffer memory**.

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| **Boot reservation** | Call **`rt_dma_pool_extract`** early (memblock **`dma-pool`** region) before drivers **`rt_dma_alloc`**. |
| **Coherent vs CMA** | **`coherent_pool`** is carved from the **low** end of the reserved region; **CMA** uses the remainder—**`cma_size` must be ≥ `coherent_pool_size`**. |
| **32-bit DMA** | Pools below **4 GiB** set **`RT_DMA_F_32BITS`** on the pool—devices with limited addressing need buffers from these pools. |
| **`dma-coherent` DT** | **`rt_dma_device_is_coherent(dev)`** reads the property; map ops may skip flush on coherent devices. |

## `struct rt_dma_pool`

| Field | Meaning |
| --- | --- |
| `region` | Physical **`start` / `end`**, optional **`name`**. |
| `map` / `bits` | Page bitmap (**`ARCH_PAGE_SIZE`** granule). |
| `flags` | e.g. **`RT_DMA_F_32BITS`**, **`RT_DMA_F_NOCACHE`**. |
| `list` | Global pool list (internal). |

## Public API

| API | Role |
| --- | --- |
| **`rt_dma_pool_install(region)`** | Register a physical memory region as a pool; returns **`struct rt_dma_pool *`** or **NULL** on error. |
| **`rt_dma_pool_extract(cma_size, coherent_pool_size)`** | Find memblock region named **`dma-pool`**, split into **`coherent-pool`** + **`cma`** sub-regions, install both pools, mark memblock as consumed. Returns **`-RT_EEMPTY`** if no suitable region, **`-RT_EINVAL`** if sizes are inconsistent. |

**`rt_dma_pool_install`** is also used directly when the BSP hands a fixed **`rt_region_t`** without going through memblock extract.

## How allocation uses pools

1. **`rt_dma_alloc(dev, size, &handle, flags)`** walks installed pools (under **`dma_pools_lock`**), picks a pool matching flags (coherent, 32-bit, device, etc.).
2. Default **`rt_dma_map_ops`**:
   - **Coherent**: flush on **`sync_out_data`**, invalidate on **`sync_in_data`**.
   - **Non-coherent**: physical address via **`rt_kmem_v2p`** without cache maintenance on sync-in.
3. With **`RT_USING_OFW`**, **`rt_dma_device_set_ops`** may install **`ofw_dma_map_*`** that translates CPU ↔ DMA bus addresses via **`rt_ofw_translate_cpu2dma`**.

Slaves should use **`rt_dma_alloc_coherent`** for ring buffers the CPU and DMA both touch.

## Boot flow (typical)

1. Bootloader or memblock code reserves **`dma-pool`** in device tree / memblock.
2. Early init calls **`rt_dma_pool_extract(SIZE_MB(8), SIZE_MB(2))`** (example sizes).
3. Drivers **`probe`** and **`rt_dma_alloc`** for descriptor rings and payload buffers.

## Debugging

With **`RT_USING_CONSOLE`** and **`RT_USING_MSH`**, **`list_dma_pool`** prints installed regions (name, size, base).

## Pitfalls

- **Pool exhausted**: **`rt_dma_alloc`** returns **NULL**—size requests must fit contiguous free pages in a matching pool.
- **CMA smaller than coherent**: **`rt_dma_pool_extract`** rejects **`cma_size < coherent_pool_size`**.
- **High memory only**: if no sub-4G **`dma-pool`** chunk is large enough, extract may fall back with a warning—DMA to peripherals that cannot reach high memory will fail.
- **Double extract**: second call may find memblock already consumed—guard in BSP init.

## See also

- DMA engine and channels: `documentation/6.components/device-driver/dma/dma.md`
- OFW DMA range: `documentation/6.components/device-driver/ofw/ofw.md`
- NUMA / affinity: `documentation/6.components/device-driver/numa/numa.md`
- Source: `components/drivers/dma/dma_pool.c`
- Header: `components/drivers/include/drivers/dma.h`
