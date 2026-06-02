@page page_device_hwcache Hardware cache (hwcache)

# CPU cache maintenance (hwcache)

On RT-Thread, **CPU D-cache / I-cache** maintenance for DMA coherence, MMU table updates, and dynamic code loading is done through architecture code in **`libcpu`** and, when **`RT_USING_HWCACHE`** is enabled, the DM helper module **`components/drivers/hwcache/`**.

**Most drivers in the tree call the BSP APIs** in **`include/rthw.h`** (`rt_hw_cpu_dcache_ops`, `rt_hw_cpu_icache_ops`). The **`rt_hwcache_*`** functions in **`drivers/hwcache.h`** are a thin DM layer that forwards to **`struct rt_hwcache_ops`** pointers filled from device tree stubs or SoC code.

Documentation path: **`hwcache/hwcache.md`** (not `cache/` — the subsystem name is **hwcache**).

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_CACHE`** | Enables **`rthw.h`** cache APIs (required for real flush/invalidate) |
| **`RT_USING_HWCACHE`** | Builds **`components/drivers/hwcache/hwcache.c`**; depends on **`RT_USING_DM`** and **`RT_USING_CACHE`** |
| **`SOC_DM_HWCACHE_DIR`** | BSP may add extra Kconfig under SoC DM hwcache drivers |

If **`RT_USING_CACHE`** is off, **`rthw.h`** defines **`rt_hw_cpu_*_ops`** as empty macros — maintenance becomes no-ops.

---

## Two API layers (do not mix up)

```
  Application / NVMe / SDIO / DMA pool / …
              │
              ▼
   rt_hw_cpu_dcache_ops() / rt_hw_cpu_icache_ops()   ← include/rthw.h (usual)
              │
              ▼
   libcpu/*/cache.c (per architecture)

  Optional parallel path when RT_USING_HWCACHE:
              │
              ▼
   rt_hwcache_dcache_ops() / rt_hwcache_icache_ops()   ← drivers/hwcache.h
              │
              ▼
   rt_dm_cpu_dcache_ops / rt_dm_cpu_icache_ops
              │
              ▼
   struct rt_hwcache_ops (flush/invalidate from OFW stub or SoC init)
```

| Layer | Header | Typical caller |
| --- | --- | --- |
| **Architecture (primary)** | `rthw.h` | **`nvme`**, **`sdio`**, **`ahci`**, **`ufs`**, **`dma_pool`**, USB glue, **`lwp`**, **`dlmodule`** |
| **DM hwcache** | `drivers/hwcache.h` | Code that explicitly uses **`rt_hwcache_*`** or SoC **`RT_HWCACHE_OFW_DECLARE`** setup |

Unless your BSP connects **`rt_dm_cpu_dcache_ops`** to the same implementation as **`rt_hw_cpu_dcache_ops`**, calling only one layer may be insufficient. **Driver authors: use `rt_hw_cpu_dcache_ops` unless the BSP documents `rt_hwcache_*` as the canonical path.**

---

## Architecture API (`rthw.h`)

Enabled when **`RT_USING_CACHE`** is set.

### Opcodes

```c
enum RT_HW_CACHE_OPS {
    RT_HW_CACHE_FLUSH      = 0x01,  /* clean / write-back to RAM */
    RT_HW_CACHE_INVALIDATE = 0x02,  /* discard cached copy, refetch from RAM */
};
```

**`RT_CPU_CACHE_LINE_SZ`** (default 32) is the usual alignment hint for maintenance ranges.

### D-cache

| Function | Role |
| --- | --- |
| **`rt_hw_cpu_dcache_enable()`** | Enable D-cache |
| **`rt_hw_cpu_dcache_disable()`** | Disable D-cache |
| **`rt_hw_cpu_dcache_status()`** | Non-zero if enabled |
| **`rt_hw_cpu_dcache_ops(ops, addr, size)`** | Flush or invalidate **`[addr, addr+size)`** |

### I-cache

| Function | Role |
| --- | --- |
| **`rt_hw_cpu_icache_enable()`** | Enable I-cache |
| **`rt_hw_cpu_icache_disable()`** | Disable I-cache |
| **`rt_hw_cpu_icache_status()`** | Non-zero if enabled |
| **`rt_hw_cpu_icache_ops(ops, addr, size)`** | Typically **invalidate** after loading code |

### Example (DMA TX buffer)

```c
/* CPU filled buffer; device DMA will read RAM */
rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, buf, len);

/* After device DMA wrote RAM; CPU will read buffer */
rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, buf, len);
```

---

## DM hwcache API (`drivers/hwcache.h`)

Implementation: **`components/drivers/hwcache/hwcache.c`**.

### `struct rt_hwcache_ops`

| Callback | Role |
| --- | --- |
| **`enable` / `disable`** | Turn cache on/off |
| **`status`** | Query enabled state |
| **`flush(vaddr, size)`** | Clean D-cache (or unified) for region |
| **`invalidate(vaddr, size)`** | Invalidate region |

Global pointers (set by platform init or OFW stub):

- **`rt_dm_cpu_dcache_ops`**
- **`rt_dm_cpu_icache_ops`**

### `rt_hwcache_*` wrappers

| Function | Maps to |
| --- | --- |
| **`rt_hwcache_dcache_enable/disable/status`** | **`rt_dm_cpu_dcache_ops`** |
| **`rt_hwcache_dcache_ops(op, addr, size)`** | **`flush`** if **`op == RT_HW_CACHE_FLUSH`**, **`invalidate`** if **`RT_HW_CACHE_INVALIDATE`** |
| **`rt_hwcache_icache_*`** | Same for **`rt_dm_cpu_icache_ops`** |

If the corresponding **`rt_dm_cpu_*_ops`** is **`NULL`**, calls are no-ops (safe but ineffective).

### Initialization

```c
rt_err_t rt_hwcache_init(void);
```

With **`RT_USING_OFW`**, walks all DT nodes and runs **`rt_ofw_stub_probe_range`** for stubs in the **`hwcache`** linker range (**`RT_OFW_STUB_RANGE_EXPORT(hwcache, ...)`** in `hwcache.c`). Stub handlers typically assign **`rt_dm_cpu_dcache_ops`** / **`rt_dm_cpu_icache_ops`**.

### OFW registration macro

```c
RT_HWCACHE_OFW_DECLARE(name, ids, handler);
```

Expands to **`RT_OFW_STUB_EXPORT(name, ids, hwcache, handler)`**. **`handler(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)`** should install **`struct rt_hwcache_ops`** into the global pointers. See @ref page_device_ofw (stub sections).

SoC-specific drivers may live under **`SOC_DM_HWCACHE_DIR`** (per **`hwcache/Kconfig`**).

---

## DMA and coherence

| Path | Cache maintenance |
| --- | --- |
| **`dma-coherent` DT property** | **`rt_dma_device_is_coherent`** — map ops may skip explicit flush (platform-dependent) |
| **Coherent DMA pool** (`dma_pool.c`) | **`sync_out`**: **`rt_hw_cpu_dcache_ops(FLUSH)`**; **`sync_in`**: **`INVALIDATE`** |
| **Non-coherent pool** | Physical address only; CPU must still maintain if CPU touches the buffer |

Coordinate with @ref page_device_dma and @ref page_device_dma_pool — avoid **double flush** and **invalidate-before-flush** on dirty TX buffers.

---

## Drivers that use cache maintenance (examples)

| Subsystem | File | Typical pattern |
| --- | --- | --- |
| **NVMe** | `nvme/nvme.c` | Flush PRP/list buffers before doorbell; invalidate after read |
| **SDHCI / SDIO** | `sdio/dev_sdhci.c`, `sdio-dw.c` | Flush before TX DMA; invalidate after RX |
| **AHCI** | `ata/ahci.c` | Flush/invalidate command tables and DMA buffers |
| **UFS** | `ufs/ufs.c` | Flush UTRD/UCD before run; invalidate after completion |
| **DMA PL330** | `dma/dma-pl330.c` | Flush microcode buffer |
| **USB** | CherryUSB glue | Platform-specific flush/invalidate hooks |
| **GICv3 ITS** | `pic/pic-gicv3-its.c` | Flush ITS command/ITT tables |
| **DFS pcache** | `dfs_v2/dfs_pcache.c` | Flush + I-invalidate on mapped pages |
| **Dynamic load** | `libc/dlmodule.c`, `lwp/` | Flush data, invalidate I-cache for new code |

These use **`rt_hw_cpu_*_ops`** from **`rthw.h`**, not **`rt_hwcache_*`**, unless your port unifies them.

---

## Use cases

1. **Non-coherent DMA** — CPU writes → **flush** before device read; device writes → **invalidate** before CPU read.
2. **MMU / page tables** — flush page table memory after CPU fills entries (see **`libcpu/*/mmu.c`**).
3. **Self-modifying / relocated code** — flush D-cache if instructions were stored through D-cache, then **invalidate I-cache**.
4. **Framebuffer / uncached mapping** — prefer correct **MMU memory attributes** (@ref page_device_graphic_framebuffer); use explicit ops only when mapping is cacheable.

---

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| **Prefer `rt_hw_cpu_*`** | Matches existing storage and DMA drivers in **`components/drivers`** |
| **Range size** | Cover full DMA buffer; align to cache line when port requires it |
| **TX ordering** | **Flush** before kicking device — never **invalidate** dirty lines first |
| **RX ordering** | **Invalidate** before CPU reads device-written RAM |
| **Harvard cores** | After loading code via data path: flush D + invalidate I |
| **`rt_hwcache_init`** | Call during early init if SoC uses **`RT_HWCACHE_OFW_DECLARE`** to publish ops |
| **Performance** | Scope maintenance to touched regions; do not flush entire RAM |

## Pitfalls

- **`rt_hwcache_*_disable()`** in **`hwcache.c`** currently invokes **`ops->enable`** in **`hwcache_disable()`** (likely a bug). Prefer **`rt_hw_cpu_dcache_disable()`** or fix SoC ops until upstream is corrected.
- **Double maintenance** with **`rt_dma_sync_*`** and manual **`rt_hw_cpu_dcache_ops`** on the same buffer.
- **`RT_USING_CACHE` off** — silent no-ops; DMA corruption on non-coherent SoCs.
- **Assuming `rt_hwcache_*` runs on all boards** — only effective after **`rt_dm_cpu_*_ops`** are assigned.
- **I-cache only invalidate** after external loaders without D-cache flush when stores went through D-cache.

## See also

- `components/drivers/include/drivers/hwcache.h`
- `components/drivers/hwcache/hwcache.c`
- `include/rthw.h` — **`RT_HW_CACHE_*`**, **`rt_hw_cpu_dcache_ops`**
- @ref page_device_dma
- @ref page_device_dma_pool
- @ref page_device_ofw — OFW stub mechanism
