@page page_device_ofw_io OFW addressing and MMIO

# Addressing and I/O (`io.c`)

Decode **`reg`**, follow **`ranges` / `dma-ranges`**, and **`ioremap`**. Header: **`drivers/ofw_io.h`**.

---

## Address cells

| API | Role |
| --- | --- |
| **`rt_ofw_bus_addr_cells` / `rt_ofw_bus_size_cells`** | Walk parents for bus **`#address-cells`** |
| **`rt_ofw_io_addr_cells` / `rt_ofw_io_size_cells`** | Parent cells used to decode this node's **`reg`** |

**`rt_ofw_get_address`** applies **`rt_ofw_translate_address`** so returned CPU physical addresses include parent **`ranges`**.

---

## `reg` decoding

| API | Role |
| --- | --- |
| **`rt_ofw_get_address_count`** | Number of **`reg`** tuples |
| **`rt_ofw_get_address(np, index, &addr, &size)`** | One tuple (translated base + size) |
| **`rt_ofw_get_address_by_name`** | Match **`reg-names`** |
| **`rt_ofw_get_address_array`** | Batch decode |

Example in **`probe`**:

```c
rt_uint64_t base, size;
if (rt_ofw_get_address(np, 0, &base, &size) != RT_EOK)
    return -RT_ERROR;
pdev->iomem = rt_dm_dev_iomap(np, 0);  /* or rt_ofw_iomap(np, 0) */
```

---

## Translation

| API | Role |
| --- | --- |
| **`rt_ofw_translate_address(np, range_type, addr)`** | Follow **`ranges`** or **`dma-ranges`** (**`range_type`** = **`"ranges"`** / **`"dma-ranges"`**, or **`RT_NULL`**) |
| **`rt_ofw_reverse_address`** | Child → parent bus address |
| **`rt_ofw_translate_dma2cpu`** | DMA bus → CPU physical (inline) |
| **`rt_ofw_translate_cpu2dma`** | CPU → DMA bus (inline) |

**`io.c`** caches up to **`RT_USING_OFW_BUS_RANGES_NUMBER`** **`ranges`** tables for performance.

---

## MMIO map

| API | Role |
| --- | --- |
| **`rt_ofw_iomap(np, index)`** | **`ioremap`** for **`reg`** index |
| **`rt_ofw_iomap_by_name`** | Named **`reg-names`** segment |

Prefer **`rt_dm_dev_iomap`** in DM drivers when **`struct rt_device`** is available (@ref page_device_dm).

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Wrong **`#address-cells`** | Always use **`rt_ofw_io_*`**, not constants |
| **`reg` without `ranges` on bus** | Translation may be identity — verify DTS |
| Multiple **`reg`** | Index 0 is not always the only MMIO bank |
| **`reg-names` mismatch** | **`rt_ofw_get_address_by_name`** returns **`-RT_EEMPTY`** |

## See also

- @ref page_device_ofw
- @ref page_device_ofw_base
- @ref page_device_ofw_boot
- @ref page_device_platform
