@page page_device_partitions Disk partition probing

# Partition tables on `rt_blk_disk`

After **`rt_hw_blk_disk_register`**, the core calls **`rt_blk_disk_probe_partition`** to read the on-disk partition layout and register one **`rt_blk_device`** per slice via **`blk_put_partition`**. Implementation: **`components/drivers/block/blk_partition.c`**; parsers in **`components/drivers/block/partitions/`**.

Volume naming and application access: @ref page_device_blk. Disk registration: @ref page_device_disk.

---

## Kconfig

| Option | File | Role |
| --- | --- | --- |
| **`RT_BLK_PARTITION_EFI`** | `partitions/efi.c` | Protective MBR + **GPT** (UEFI-style) |
| **`RT_BLK_PARTITION_DFS`** | `partitions/dfs.c` | **DFS** legacy partition table in sector 0 |

Both can be enabled; **`partition_list[]`** order is **EFI first**, then **DFS**. The first parser returning **0** wins.

---

## `rt_blk_disk_probe_partition`

```103:154:components/drivers/block/blk_partition.c
rt_err_t rt_blk_disk_probe_partition(struct rt_blk_disk *disk)
```

| Step | Behavior |
| --- | --- |
| 1 | **`disk == NULL`** → **`-RT_EINVAL`** |
| 2 | **`disk->partitions != 0`** → return **success** (already probed) |
| 3 | **`max_partitions == RT_BLK_PARTITION_NONE`** → **`-RT_EEMPTY`** |
| 4 | Loop **`partition_list[i](disk)`** |
| 5 | Parser **`-RT_ENOMEM`** → abort, return **`-RT_ENOMEM`** |
| 6 | Parser **0** → success, stop |
| 7 | No parser matched → **full-disk volume**: **`blk_put_partition(disk, NULL, 0, total_sectors, 0)`** |

So a blank or unknown layout still yields **one** mountable device covering the entire disk (**`partno == 0`**).

---

## `blk_put_partition`

```27:100:components/drivers/block/blk_partition.c
rt_err_t blk_put_partition(struct rt_blk_disk *disk, const char *type,
        rt_size_t start, rt_size_t count, int partno)
```

| Phase | Action |
| --- | --- |
| Allocate | **`struct rt_blk_device`** |
| Init | **`blk_dev_initialize(blk)`** |
| Range | **`sector_start = start`**, **`sector_count = count`**, **`partno`** |
| DFS meta | **`partition.offset`**, **`partition.size`**, **`partition.lock = &disk->usr_lock`** |
| Register | **`disk_add_blk_dev(disk, blk)`** → **`rt_device_register`**, link **`part_nodes`** |
| Count | **`disk->partitions++`** |

### Console log

For non-**`"dfs"`** types, printk partition index, byte offset, and human-readable size (KB/MB/GB).

### Failure

**`-RT_ENOMEM`** frees the partial **`rt_blk_device`** and logs via **`LOG_E`**.

---

## EFI / GPT (`partitions/efi.c`)

### Boot-time `force_gpt`

**`INIT_CORE_EXPORT(force_gpt_setup)`** reads bootarg **`gpt`** via **`rt_ofw_bootargs_select("gpt", 0)`** when **`RT_USING_OFW`**. When set, GPT probing is forced even if protective MBR checks are ambiguous.

### Validation flow (summary)

1. Read LBA 0 — check **protective MBR** (EFI GPT type, starting LBA 1).
2. Read **primary GPT header** at LBA 1 (or from **`force_gpt`** path).
3. Verify signature **"EFI PART"**, header CRC (**`efi_crc32`**), **`my_lba`**, **`first_usable_lba` / `last_usable_lba`** vs disk capacity (**`last_lba()`** = **`rt_blk_disk_get_capacity - 1`**).
4. Load partition entry array; validate entry CRC.
5. For each valid entry: **`blk_put_partition(disk, type, start, count, partno)`** with type string / GUID mapping where implemented.

### Sector size

All LBA math uses **`rt_blk_disk_get_logical_block_size(disk)`** — must stay consistent with **`getgeome`**.

### Enable

Menu: **`RT_BLK_PARTITION_EFI`** (default **y** when blk partitions menu is on).

---

## DFS partition (`partitions/dfs.c`)

Legacy path for RT-Thread **DFS** on-disk superblock layout:

1. Allocate one sector buffer.
2. **`disk->ops->read(disk, 0, sector, 1)`**.
3. Loop **`dfs_filesystem_get_partition(&part, sector, i)`** for **`i < max_partitions`**.
4. **`blk_put_partition(disk, "dfs", part.offset, part.size, i)`**.

Requires **`RT_USING_DFS`** and **`RT_BLK_PARTITION_DFS`**.

---

## Volume naming after probe

Handled in **`disk_add_blk_dev`** (`blk_dev.c`):

| Disk name ends with | Example disk | Volume examples |
| --- | --- | --- |
| Letter **`a`–`z`** | **`sda`** | **`sdap1`**, **`sdap2`** |
| Digit / other | **`mmcsd0`**, **`nvme0n1`** | **`mmcsd0p1`**, **`nvme0n1p2`** |

---

## When to call probe

| Scenario | Action |
| --- | --- |
| Normal driver | Rely on **`rt_hw_blk_disk_register`** (automatic) |
| Media just formatted | Unregister disk, register again, or call **`rt_blk_disk_probe_partition`** if **`partitions == 0`** |
| Disable tables | Set **`max_partitions = RT_BLK_PARTITION_NONE`** |
| RAM disk / single volume | Still get one full-disk **`partno 0`** unless you manage volumes manually |

### Call sites in tree

| Location | Notes |
| --- | --- |
| **`blk.c`** | End of **`rt_hw_blk_disk_register`** |
| Driver after hotplug | Rare; prefer re-register |

---

## Interaction with disk IOCTLs

| IOCTL | Multi-partition disk |
| --- | --- |
| **ERASE / AUTOREFRESH** on **volume** | **`-RT_EIO`** if **`disk->partitions > 1`** |
| **ERASE** on **disk** | Removes **all** volumes first, then **`ops->erase`** |
| **GETGEOME** on **volume** | **`sector_count`** = partition only |

---

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| **Order** | EFI before DFS — do not rely on DFS if GPT is present |
| **`max_partitions`** | SDIO passes **`RT_MMCSD_MAX_PARTITION`**; NVMe uses **`RT_BLK_PARTITION_MAX`** |
| **Empty card** | Probe still creates full-disk volume — mount may need valid FS |
| **Re-probe** | Not supported with existing volumes; unregister disk first |
| **Custom layouts** | Add a parser to **`partition_list[]`** or call **`blk_put_partition`** from driver code |

## See also

- @ref page_device_blk
- @ref page_device_disk
- `components/drivers/block/blk_partition.c`
- `components/drivers/block/partitions/efi.c`
- `components/drivers/block/partitions/dfs.c`
