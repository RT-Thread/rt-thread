@page page_device_blk Block layer (`blk`)

# Block storage subsystem

The **blk** layer turns a single physical storage backend into one or more **RT-Thread block devices** that applications and **DFS** can open, read/write by **sector**, and control with standard IOCTLs. Hardware drivers implement **`struct rt_blk_disk_ops`** on an embedded **`struct rt_blk_disk`**; the core registers the disk, scans partition tables, and creates child volumes (**`struct rt_blk_device`**) such as **`sda1`** or **`mmcsd0p1`**.

Header: `components/drivers/include/drivers/blk.h`. IOCTLs and geometry: `components/drivers/include/drivers/classes/block.h`. Core: `components/drivers/block/blk.c`, `blk_dev.c`, `blk_partition.c`.

## Architecture

```
  [NVMe / SDIO / SCSI SD / … driver]
              │ rt_blk_disk_ops (read/write/getgeome/…)
              ▼
       struct rt_blk_disk  ← rt_hw_blk_disk_register()
              │ rt_blk_disk_probe_partition()  (inside register)
              ▼
   struct rt_blk_device × N  ← disk_add_blk_dev() / blk_dev.c
              │ rt_device_read/write (sector-relative)
              ▼
        DFS / applications / POSIX devio
```

| Layer | Struct | Document |
| --- | --- | --- |
| **Physical disk** | `struct rt_blk_disk` | @ref page_device_disk |
| **Partition table** | (on-disk metadata) | @ref page_device_partitions |
| **Volume (partition)** | `struct rt_blk_device` | **This page** — application-facing nodes |

Both disk and volume nodes use **`RT_Device_Class_Block`**. Applications normally open **volumes** (`sda1`), not the raw disk device, unless probing created a single full-disk volume with **`partno == 0`**.

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_BLK`** | Master switch for `components/drivers/block/` |
| **`RT_BLK_PARTITION_EFI`** | GPT / protective MBR parser (`partitions/efi.c`) |
| **`RT_BLK_PARTITION_DFS`** | Legacy DFS superblock layout on sector 0 (`partitions/dfs.c`, needs **`RT_USING_DFS`**) |

**`rt_hw_blk_disk_register`** always calls **`rt_blk_disk_probe_partition`**; partition scan errors are **ignored** (register still succeeds).

---

# Access block devices (applications)

Same usage model as other char/block devices: **find → open → read/write → control → close**. Sector index is **0-based within the opened device** (for a partition device, sector 0 is the start of that partition).

## Find device

```c
rt_device_t rt_device_find(const char *name);
```

| Parameter | Description |
| --- | --- |
| `name` | Volume name, e.g. **`sda0`**, **`sda1`**, **`mmcsd0`**, **`nvme0n1`** (from DM naming — see @ref page_device_disk) |
| **Return** | Device handle, or **`RT_NULL`** if not found |

```c
#define BLK_DEV_NAME   "sda1"
rt_device_t blk = rt_device_find(BLK_DEV_NAME);
```

## Open / close

```c
rt_err_t rt_device_open(rt_device_t dev, rt_uint16_t oflag);
rt_err_t rt_device_close(rt_device_t dev);
```

| `oflag` | Notes |
| --- | --- |
| **`RT_DEVICE_OFLAG_RDONLY`** | Always valid |
| **`RT_DEVICE_OFLAG_WRONLY`** | Fails on disk/volume if backend is read-only (**`ops->write == NULL`** sets **`read_only`**) |

Opening a **partition** device (`rt_blk_device`) internally **opens the parent disk** (`blk_dev_open` → `rt_device_open(&blk->disk->parent)`).

## Read / write (sectors)

```c
rt_ssize_t rt_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
rt_ssize_t rt_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
```

For block class devices, **`pos`** is the **starting sector number**, **`size`** is **sector count** (not bytes).

| Parameter | Partition volume | Whole disk |
| --- | --- | --- |
| `pos` | 0 … `sector_count - 1` (relative to partition) | 0 … disk capacity − 1 |
| `size` | Sectors to transfer | Same |
| **Return** | Sectors actually transferred, or negative error | Same |

```c
#define SECTOR_SIZE   512
rt_uint8_t buf[SECTOR_SIZE];

if (rt_device_read(blk, 0, buf, 1) == 1)
{
    /* one sector at LBA 0 of this partition */
}
```

## Control (IOCTL)

```c
rt_err_t rt_device_control(rt_device_t dev, int cmd, void *args);
```

### Standard commands (`classes/block.h`)

| Command | `args` type | Partition volume | Raw disk |
| --- | --- | --- | --- |
| **`RT_DEVICE_CTRL_BLK_GETGEOME`** | `struct rt_device_blk_geometry *` | **`sector_count`** = partition size; **`bytes_per_sector`** from disk | Full disk geometry |
| **`RT_DEVICE_CTRL_BLK_SYNC`** | ignored | Flushes parent disk | **`ops->sync`** under lock |
| **`RT_DEVICE_CTRL_BLK_ERASE`** | ignored | Only if **`disk->partitions <= 1`**; else **`-RT_EIO`** | May remove all partitions then **`ops->erase`** |
| **`RT_DEVICE_CTRL_BLK_AUTOREFRESH`** | `rt_bool_t *` / pointer treated as enable flag | Delegates to disk if single partition | **`ops->autorefresh`** |
| **`RT_DEVICE_CTRL_BLK_PARTITION`** | `struct dfs_partition *` | Copies **`blk->partition`** | **`-RT_EINVAL`** on disk node |

### DFS helpers (`blk_dfs.h`)

| Command | Role |
| --- | --- |
| **`RT_DEVICE_CTRL_BLK_SSIZEGET`** | Fills `*(rt_off_t *)args` with **bytes per sector** |
| **`RT_DEVICE_CTRL_ALL_BLK_SSIZEGET`** | Total byte size = sectors × bytes_per_sector (used by DFS v2 POSIX layer) |

Vendor-specific IOCTLs pass through **`disk->ops->control(disk, blk, cmd, args)`** on the volume path; on the disk path **`blk` is NULL**.

### Geometry structure

```c
struct rt_device_blk_geometry {
    rt_uint64_t sector_count;
    rt_uint32_t bytes_per_sector;
    rt_uint32_t block_size;   /* erase block size for flash-style media */
};
```

---

# Partition volumes (`rt_blk_device`)

Defined in **`blk.h`** when DFS headers are available.

| Field | Meaning |
| --- | --- |
| `disk` | Parent **`rt_blk_disk`** |
| `sector_start` / `sector_count` | Slice on the physical disk (LBA range) |
| `partno` | Index used in device name (`%sp%d` / `%s%d`) |
| `partition` | **`struct dfs_partition`** for DFS mount; **`partition.lock`** → **`disk->usr_lock`** |
| `list` | Node on **`disk->part_nodes`** |

### `blk_dev.c` forwarding

| Operation | Behavior |
| --- | --- |
| **read/write** | Translates to **`disk->parent`** at **`sector_start + pos`** |
| **GETGEOME** | Disk geometry with **`sector_count`** replaced by partition length |
| **SYNC** | **`rt_device_control(&disk->parent, SYNC)`** |
| **ERASE / AUTOREFRESH** | Allowed only when **`disk->partitions <= 1`** |

### Device naming (DM)

**`disk_add_blk_dev`** (`blk_dev.c`):

- If disk name’s last character is **`'a'`–`'z'`** (e.g. **`sda`**): volume name **`sdap1`** (`%sp%d`).
- Otherwise (e.g. **`mmcsd0`**, **`nvme0n1`**): **`mmcsd0p1`**, **`nvme0n1p2`** (`%s%d`).

Each volume gets its own **`rt_dm_ida_alloc(disk->ida)`** slot under the same **`master_id`** as the disk.

---

# DFS integration

When **`RT_USING_DFS`** and **`RT_USING_POSIX_DEVIO`** (and DFS v2 as implemented in-tree), **`blk_dfs.c`** registers file operations that:

1. On **open**: **`GETGEOME`** + **`ALL_BLK_SSIZEGET`** for file size.
2. On **read/write**: byte-oriented I/O with unaligned head/tail sector handling via a bounce sector buffer.
3. **ioctl**: forwards to **`rt_device_control`**.

Mount the **volume** device name (not the disk) with the appropriate filesystem driver after partition probe.

---

# Drivers already using blk

These drivers embed **`struct rt_blk_disk`**, set **`ops`**, **`ida`**, and call **`rt_hw_blk_disk_register`** when media is present:

| Driver | File | Typical name | Notable `rt_blk_disk` fields |
| --- | --- | --- | --- |
| **NVMe** | `nvme/nvme.c` | `nvme0n1`, … | **`parallel_io = RT_TRUE`**, per-namespace disk, **`max_partitions = RT_BLK_PARTITION_MAX`** |
| **SDIO/MMC** | `sdio/dev_block.c` | host name / `mmcsd0p*` | **`removable`**, **`max_partitions = RT_MMCSD_MAX_PARTITION`**, sets geometry before register |
| **SCSI disk** | `scsi/scsi_sd.c` | `sda`, `sdb`, … | **`parallel_io`** from host, READ CAPACITY 10/16, **`sd_ida`** |
| **SCSI CD-ROM** | `scsi/scsi_cdrom.c` | optical media | Read-only style backend |

**AHCI/SATA** path: **`ata/ahci.c`** exposes SCSI devices; **SD card** goes through **`scsi_sd`** or **MMC `dev_block`**, then blk.

### Minimal driver pattern

```c
static const struct rt_blk_disk_ops my_blk_ops = {
    .read     = my_read,
    .write    = my_write,
    .getgeome = my_getgeome,
    .sync     = my_sync,
};

static struct rt_dm_ida my_ida = RT_DM_IDA_INIT(MY_DISK);

void my_disk_register(struct my_hw *hw)
{
    struct rt_blk_disk *disk = &hw->blk;

    disk->ops = &my_blk_ops;
    disk->ida = &my_ida;
    disk->parallel_io = RT_FALSE;  /* or RT_TRUE if ops are reentrant */
    rt_dm_dev_set_name(&disk->parent.parent, "sda");  /* example */

    rt_hw_blk_disk_register(disk);  /* also runs partition probe */
}
```

Details: @ref page_device_disk.

---

# Locks and concurrency

| Mechanism | Scope |
| --- | --- |
| **`disk->usr_lock`** (semaphore) | Serializes disk **`read`/`write`/`sync`** when **`parallel_io == 0`** |
| **`disk->lock`** (spinlock) | Partition list, unregister, erase path |
| **`parallel_io == 1`** | Disk **`read`/`write`** skip **`usr_lock`** — backend must be safe for concurrent I/O |

Partition volume I/O still goes through the disk node and follows the disk’s **`parallel_io`** / lock rules.

---

# Typical bring-up sequence

1. Allocate **`struct rt_blk_disk`** (often embedded in driver private data).
2. Implement **`rt_blk_disk_ops`**; set **`ida`**, name, flags (**`read_only`**, **`removable`**, **`parallel_io`**, **`max_partitions`**).
3. **`rt_hw_blk_disk_register(disk)`** — partition probe runs automatically.
4. Application or init code **`rt_device_find("sda1")`**, mount DFS, or run filesystem code.
5. **`rt_hw_blk_disk_unregister(disk)`** after unmount — syncs, removes all volumes, checks **`ref_count`**.

To **re-scan** partitions after media change, unregister, update geometry, register again (or call **`rt_blk_disk_probe_partition`** only if **`disk->partitions == 0`**).

---

# Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| **Name before register** | First character of **`disk->parent.parent.name`** must be non-NUL |
| **`ida`** | Mandatory with **`RT_USING_DM`**; disk and each volume consume IDA slots |
| **Probe errors** | Ignored at register — check **`disk->partitions`** or open volumes explicitly |
| **`max_partitions`** | Set **`RT_BLK_PARTITION_NONE`** to skip table parsing |
| **Read-only** | Omit **`write`** in **`ops`** — core forces **`read_only`** |
| **Unmount first** | **`unregister`** returns **`-RT_EBUSY`** if **`ref_count > 0`** |
| **Erase** | Disk erase IOCTL removes **all** partition devices first |

## See also

- @ref page_device_disk — `rt_blk_disk` / `rt_blk_disk_ops` / register API
- @ref page_device_partitions — GPT/EFI and DFS parsers
- @ref page_device_ata — AHCI → SCSI → blk path
- @ref page_device_nvme
- @ref page_device_sdio
- @ref page_device_scsi
- `components/drivers/block/blk.c`
- `components/drivers/block/blk_dev.c`
- `components/drivers/block/blk_partition.c`
