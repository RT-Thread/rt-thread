@page page_device_disk Physical disk (`rt_blk_disk`)

# Disk device (driver writer guide)

**`struct rt_blk_disk`** is the **physical backing store**: one contiguous LBA space implemented by your driver’s **`rt_blk_disk_ops`**. The blk core wraps it as an **`rt_device`**, then creates **volume** children — see @ref page_device_blk and @ref page_device_partitions.

Implementation: **`components/drivers/block/blk.c`**. Header: **`components/drivers/include/drivers/blk.h`**.

Same documentation pattern as **`documentation/6.components/device-driver/ata/ata.md`**: fill structures before **`rt_hw_blk_disk_register`**, implement **`ops`**, then let the core attach partitions and DFS-facing devices.

---

## `struct rt_blk_disk` (before `rt_hw_blk_disk_register`)

```34:57:components/drivers/include/drivers/blk.h
struct rt_blk_disk
{
    struct rt_device parent;
    const struct rt_blk_disk_ops *ops;
#ifdef RT_USING_DM
    struct rt_dm_ida *ida;
#endif
    rt_uint32_t read_only:1;
    rt_uint32_t parallel_io:1;
    rt_uint32_t removable:1;
    rt_uint32_t __magic;
    rt_uint32_t partitions;
    rt_int32_t max_partitions;
    rt_list_t part_nodes;
    struct rt_spinlock lock;
    struct rt_semaphore usr_lock;
};
```

| Member | Owner | Rule / meaning |
| --- | --- | --- |
| **`parent`** | **Caller** | Embedded **`rt_device`**. **Name must be set** before register (first char of **`parent.parent.name` ≠ `\0`**). |
| **`ops`** | **Caller** | **Required**; see **`struct rt_blk_disk_ops`** below. |
| **`ida`** | **Caller** (`RT_USING_DM`) | **Non-NULL**; shared with all volume children for **`rt_dm_ida_alloc`**. |
| **`read_only`** | **Caller / core** | If **`ops->write == NULL`**, core sets **`read_only = RT_TRUE`**. |
| **`parallel_io`** | **Caller** | **`RT_TRUE`**: disk read/write skip **`usr_lock`** (NVMe uses this). |
| **`removable`** | **Caller** | Hint for removable media (e.g. SDIO sets from host). |
| **`max_partitions`** | **Caller** | Cap for parsers; **`RT_BLK_PARTITION_NONE`** disables probing. **`RT_BLK_PARTITION_MAX`** = unlimited. |
| **`partitions`** | **Core** | Count of registered **`rt_blk_device`** nodes. |
| **`part_nodes`** | **Core** | List of **`struct rt_blk_device`**. |
| **`lock`** | **Core** | Spinlock for list / unregister / erase. |
| **`usr_lock`** | **Core** | Semaphore (prio) serializing I/O when not **`parallel_io`**. |
| **`__magic`** | **Core** | Set to **`RT_BLK_DISK_MAGIC`** at register. |

---

## `struct rt_blk_disk_ops`

```62:73:components/drivers/include/drivers/blk.h
struct rt_blk_disk_ops
{
    rt_ssize_t (*read)(struct rt_blk_disk *disk, rt_off_t sector, void *buffer,
            rt_size_t sector_count);
    rt_ssize_t (*write)(struct rt_blk_disk *disk, rt_off_t sector, const void *buffer,
            rt_size_t sector_count);
    rt_err_t (*getgeome)(struct rt_blk_disk *disk, struct rt_device_blk_geometry *geometry);
    rt_err_t (*sync)(struct rt_blk_disk *disk);
    rt_err_t (*erase)(struct rt_blk_disk *disk);
    rt_err_t (*autorefresh)(struct rt_blk_disk *disk, rt_bool_t is_auto);
    rt_err_t (*control)(struct rt_blk_disk *disk, struct rt_blk_device *blk, int cmd, void *args);
};
```

| Callback | Required? | Contract |
| --- | --- | --- |
| **`read`** | **Yes** (practical) | **`sector`**, **`sector_count`** in **512-byte sectors** unless **`getgeome`** says otherwise. Return sectors read or **`< 0`** error. |
| **`write`** | Optional | **`NULL`** → disk read-only. Same addressing as **`read`**. |
| **`getgeome`** | **Yes** (practical) | Fill **`sector_count`**, **`bytes_per_sector`**, **`block_size`**. Used by partition code and DFS. |
| **`sync`** | Optional | Flush caches; called on unregister and **`RT_DEVICE_CTRL_BLK_SYNC`**. |
| **`erase`** | Optional | Whole-device erase; disk IOCTL may remove partitions first. |
| **`autorefresh`** | Optional | **`RT_DEVICE_CTRL_BLK_AUTOREFRESH`** (e.g. SD auto refresh). |
| **`control`** | Optional | Vendor IOCTLs; **`blk`** is **`NULL`** on raw disk, non-NULL on volume forwarding. |

### Sector addressing expectations

- Arguments are **LBA sector indices** on the **whole disk**, not bytes.
- **`getgeome()->bytes_per_sector`** must match what **`read`/`write`** use.
- **`getgeome()->sector_count`** is full device capacity in sectors.
- If **`parallel_io`**, **`read`/`write`** may overlap — use driver-internal locking or queue depth as needed.

---

## `rt_hw_blk_disk_register` (core sequence)

```228:337:components/drivers/block/blk.c
rt_err_t rt_hw_blk_disk_register(struct rt_blk_disk *disk)
```

| Step | Action |
| --- | --- |
| 1 | Validate **`disk`**, **`ops`**, name, **`ida`** (DM). |
| 2 | **`rt_dm_ida_alloc(disk->ida)`** for the **disk** device id. |
| 3 | Init **`usr_lock`**, **`part_nodes`**, **`lock`**. |
| 4 | Hook **`blk_ops`** or **`blk_parallel_ops`** on **`parent`**. |
| 5 | If **`!ops->write`** → **`read_only = 1`**. |
| 6 | **`device_set_blk_fops`**, **`rt_device_register`** with RD/WR flags. |
| 7 | **`rt_blk_disk_probe_partition(disk)`** — errors ignored. |

**Return**: register error only; partition failure does not fail register.

### Disk `rt_device` ops (internal)

| Op | `parallel_io == 0` | `parallel_io == 1` |
| --- | --- | --- |
| read/write | Under **`usr_lock`** | Direct **`ops->read/write`** |
| control | **`blk_control`** → **`ops`** | Same |

**`RT_DEVICE_CTRL_BLK_PARTITION`** on the **disk** node returns **`-RT_EINVAL`** (use volume devices).

---

## `rt_hw_blk_disk_unregister`

| Step | Action |
| --- | --- |
| 1 | **`ref_count > 0`** → **`-RT_EBUSY`** |
| 2 | **`ops->sync`** if present |
| 3 | **`blk_remove_all`** — unregister every **`rt_blk_device`** |
| 4 | **`rt_dm_ida_free`** for disk id, **`rt_device_unregister`** |

Unmount DFS / close handles before unregister.

---

## Helper APIs

| API | Role |
| --- | --- |
| **`rt_blk_disk_probe_partition(disk)`** | Re-run parsers if **`partitions == 0`**; see @ref page_device_partitions |
| **`rt_blk_disk_get_capacity(disk)`** | **`getgeome`** → **`sector_count`** |
| **`rt_blk_disk_get_logical_block_size(disk)`** | **`getgeome`** → **`bytes_per_sector`** |

---

## In-tree integration examples

### NVMe (`nvme/nvme.c`)

Per namespace:

- **`rt_dm_dev_set_name(&ndev->parent.parent, "%sn%u", nvme->name, nsid)`**
- **`parallel_io = RT_TRUE`**, **`ops = &nvme_blk_ops`**, **`ida = &nvme_ida`**
- **`max_partitions = RT_BLK_PARTITION_MAX`**
- **`rt_hw_blk_disk_register(&ndev->parent)`** after identify

### SDIO / MMC (`sdio/dev_block.c`)

- Geometry from card CSD: **`sector_count`**, **`bytes_per_sector`**, **`block_size`**
- **`mmcsd_set_blksize`** before register
- **`removable`**, **`max_partitions = RT_MMCSD_MAX_PARTITION`**
- Name from **`host->name`** → volumes **`hostp1`** style

### SCSI SD (`scsi/scsi_sd.c`)

- READ CAPACITY (10/16) → geometry
- **`rt_dm_dev_set_name(..., "sd%c%c", letter_name(sd_id))`** — names like **`sda`**
- **`parallel_io`** from SCSI host
- **`ida = &scsi_sd_ida`**

### SCSI CD-ROM (`scsi/scsi_cdrom.c`)

Same blk registration pattern; typically read-only media (**`write`** omitted or read-only flag).

---

## DM naming checklist

1. **`RT_DM_IDA_INIT`** per disk family (e.g. **`scsi_sd_ida`**, **`nvme_ida`**, **`sdio_ida`**).
2. Set **`disk->ida`** before register.
3. Disk name via **`rt_dm_dev_set_name(&disk->parent.parent, ...)`**.
4. Volumes are named automatically at probe — do not register **`rt_blk_device`** yourself unless you bypass **`blk_put_partition`**.

---

## Driver cautions

| Topic | Guidance |
| --- | --- |
| **DMA / buffers** | Bounce in **`ops`** if callers pass non-DMA-safe pointers |
| **Capacity change** | Unregister, update geometry, register again |
| **Hotplug** | Remove card → **`rt_hw_blk_disk_unregister`**; insert → register fresh |
| **GPT + DFS** | Enable both Kconfig parsers; EFI runs first in **`partition_list[]`** |
| **Custom IOCTL** | Implement **`control(disk, blk, cmd, args)`**; forward unknown cmds from **`blk_control`** default case |

## See also

- @ref page_device_blk — application API and volume layer
- @ref page_device_partitions
- `components/drivers/block/blk.c`
- `components/drivers/include/drivers/blk.h`
