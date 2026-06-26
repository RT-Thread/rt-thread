@page page_device_scsi SCSI host and commands

# SCSI subsystem

RT-Thread provides a **small SCSI core** for storage backends: a **host** (`rt_scsi_host`) scans targets, issues commands through **`rt_scsi_ops::transfer`**, and attaches **type-specific upper drivers** (disk `sd*`, CD-ROM, …) that register **`rt_blk_disk`** devices.

The core is **not** a device-model bus (see comment in `scsi.c`) — there is no `rt_scmi`-style match/probe bus. Host adapters call **`rt_scsi_host_register()`** after filling **`rt_scsi_host`**.

| Piece | Path |
| --- | --- |
| API / CDB layouts | `components/drivers/include/drivers/scsi.h` |
| Core | `components/drivers/scsi/scsi.c` |
| Block disk (type 0) | `components/drivers/scsi/scsi_sd.c` |
| CD-ROM (type 5) | `components/drivers/scsi/scsi_cdrom.c` |

**Kconfig**: `RT_USING_SCSI` (needs `RT_USING_DM`). Options `RT_SCSI_SD` / `RT_SCSI_CDROM` (need `RT_USING_BLK`).

---

## End-to-end flow

```
Host adapter (AHCI / UFS / VirtIO-SCSI / …)
    fills rt_scsi_host { dev, ops, max_id, max_lun, parallel_io }
    calls rt_scsi_host_register()
        ↓
For each (id, lun): INQUIRY → devtype / removable
    unknown type or inquiry fail → skip LUN
    devtype >= SCSI_DEVICE_TYPE_MAX → shrink scan, stop
        ↓
scsi_device_setup(sdev): optional reset → TEST UNIT READY (5 s) → driver_table[devtype].probe
        ↓
scsi_sd_probe / scsi_cdrom_probe: READ CAPACITY → rt_hw_blk_disk_register ("sd*a", …)
        ↓
Applications use blk API (@ref page_device_blk, @ref page_device_disk)
```

**Unregister**: `rt_scsi_host_unregister()` walks **`lun_nodes`**, optional **`ops->reset`**, type **`remove`**, frees each **`rt_scsi_device`**.

---

## Data structures (`scsi.h`)

### Host and device

```c
struct rt_scsi_host {
    struct rt_device *dev;       /* required; DMA / naming */
    const struct rt_scsi_ops *ops;
    rt_size_t max_id;            /* both must be non-zero */
    rt_size_t max_lun;
    rt_bool_t parallel_io;       /* hint for blk layer */
    rt_list_t lun_nodes;         /* filled by register */
};

struct rt_scsi_device {
    struct rt_scsi_host *host;
    rt_list_t list;
    rt_size_t id;
    rt_size_t lun;
    rt_uint32_t devtype;         /* from INQUIRY */
    rt_uint32_t removable;
    rt_size_t last_block;        /* filled by READ CAPACITY helpers */
    rt_size_t block_size;
    void *priv;                  /* scsi_sd / scsi_cdrom */
};

struct rt_scsi_ops {
    rt_err_t (*reset)(struct rt_scsi_device *sdev);   /* optional */
    rt_err_t (*transfer)(struct rt_scsi_device *sdev, struct rt_scsi_cmd *cmd);  /* required */
};
```

### Command envelope

```c
struct rt_scsi_cmd {
    union { /* CDB: inquiry, read10, write16, … */ } op;
    rt_size_t op_size;

    union {
        struct { /* fixed response structs */ } ;
        struct { void *ptr; rt_size_t size; } data;  /* DMA buffer for read/write */
    } data;
};
```

Build CDBs with packed structs in **`scsi.h`** (`rt_scsi_inquiry`, `rt_scsi_read10`, …) or fill **`cmd.op`** manually. Set **`op_size`** to the CDB length your transport accepts.

High-level helpers in **`scsi.c`** (`rt_scsi_inquiry`, `rt_scsi_read10`, `rt_scsi_write16`, `rt_scsi_read_capacity10`, …) assemble **`rt_scsi_cmd`** and call **`host->ops->transfer`**. On failure they often issue **`rt_scsi_request_sense`**.

**`rt_scsi_cmd_is_write(cmd)`** — used by VirtIO-SCSI to pick IN vs OUT virtqueue buffers.

---

## `rt_scsi_host_register` / `unregister`

### Before register (caller)

| Field | Rule |
| --- | --- |
| `dev` | Non-NULL |
| `ops` | Non-NULL; **`transfer`** required |
| `max_id` / `max_lun` | Both non-zero; define scan grid |
| `parallel_io` | Set if adapter can pipeline multiple LUN commands |
| `lun_nodes` | Do not pre-fill; core initializes the list |

### Scan behavior (`scsi.c`)

1. Nested loop **`id ∈ [0, max_id)`**, **`lun ∈ [0, max_lun)`**.
2. **`rt_scsi_inquiry(&tmp_sdev, NULL)`** — failure skips the LUN.
3. If **`devtype >= SCSI_DEVICE_TYPE_MAX`**, scan **stops** and **`max_id` / `max_lun`** are clipped to the current index (simple bus assumption).
4. Allocated **`rt_scsi_device`** is copied from the temp device (id, lun, devtype, removable).
5. **`scsi_device_setup`**: optional **`reset`** → wait **TEST UNIT READY** (up to ~5 s) → **`driver_table[devtype].probe`**.

Returns **`RT_EOK`** if at least one LUN probed; **`-RT_EEMPTY`** if none; **`-RT_EINVAL`** / **`-RT_ENOMEM`** on bad args or OOM (partial LUNs may remain on ENOMEM mid-scan).

### `transfer` contract

- Fill or consume **`cmd->data`** (`ptr` + `size` for READ/WRITE; embedded structs for INQUIRY / capacity).
- Return **`RT_EOK`** on command completion; RT error codes on transport failure.
- Sense: adapters may copy sense into **`cmd->data.request_sense`**; helpers already call **REQUEST SENSE** after some failures.

---

## Upper-layer drivers (`driver_table`)

| `devtype` (`SCSI_DEVICE_TYPE_*`) | Kconfig | Probe | Block device |
| --- | --- | --- | --- |
| `0x00` DIRECT | `RT_SCSI_SD` | `scsi_sd_probe` | `sd*a` — read/write/sync/erase |
| `0x05` CDROM | `RT_SCSI_CDROM` | `scsi_cdrom_probe` | `sr*a` — read-only |

Other inquiry types log **not supported** and are skipped.

**`scsi_sd_probe`**: READ CAPACITY 10; if last LBA is `0xffffffff`, READ CAPACITY 16 and use READ/WRITE **16** ops; sets geometry from **`sdev->block_size`** / **`last_block`**; **`rt_hw_blk_disk_register`**. Honors **`host->parallel_io`** on the disk.

**`scsi_cdrom_probe`**: capacity + read-only **`rt_blk_disk`** (uses READ 10/12/16 by LBA width).

---

## Built-in SCSI hosts (examples)

These embed **`struct rt_scsi_host parent`** and call **`rt_scsi_host_register`** after hardware init:

| Backend | Source | Notes |
| --- | --- | --- |
| **AHCI** | `ata/ahci.c` | SATA/ATAPI → `ahci_scsi_ops.transfer`; see @ref page_device_ata |
| **UFS** | `ufs/ufs.c` | UTP carries SCSI CDBs; `ufs_host_ops`, often `parallel_io = RT_TRUE` |
| **VirtIO SCSI** | `virtio/virtio-scsi.c` | `RT_VIRTIO_DRIVER_EXPORT`; 3 queues; hotplug via `config_changed` + work queue re-register |

Typical host setup (pattern):

```c
struct my_hba {
    struct rt_scsi_host parent;
    /* private */
};

static rt_err_t my_scsi_transfer(struct rt_scsi_device *sdev, struct rt_scsi_cmd *cmd)
{
    /* map id/lun, push CDB + data to hardware */
    return RT_EOK;
}

static const struct rt_scsi_ops my_scsi_ops = {
    .reset = my_scsi_reset,      /* optional */
    .transfer = my_scsi_transfer,
};

/* after controller ready */
hba->parent.dev = &controller_dev;
hba->parent.ops = &my_scsi_ops;
hba->parent.max_id = 1;
hba->parent.max_lun = 8;
hba->parent.parallel_io = RT_FALSE;
rt_scsi_host_register(&hba->parent);
```

Teardown: **`rt_scsi_host_unregister(&hba->parent)`** before freeing the controller.

---

## Command reference (`scsi.h`)

Opcodes and structs are defined for common storage commands:

| Opcode macro | Struct | Helper |
| --- | --- | --- |
| `RT_SCSI_CMD_INQUIRY` | `rt_scsi_inquiry` | `rt_scsi_inquiry()` |
| `RT_SCSI_CMD_TEST_UNIT_READY` | `rt_scsi_test_unit_ready` | `rt_scsi_test_unit_ready()` |
| `RT_SCSI_CMD_READ_CAPACITY10/16` | capacity structs | `rt_scsi_read_capacity10/16()` |
| `RT_SCSI_CMD_READ10/12/16` | read structs | `rt_scsi_read10/12/16()` |
| `RT_SCSI_CMD_WRITE10/12/16` | write structs | `rt_scsi_write10/12/16()` |
| `RT_SCSI_CMD_SYNCHRONIZE_CACHE10/16` | sync cache | `rt_scsi_synchronize_cache10/16()` |
| `RT_SCSI_CMD_WRITE_SAME10/16` | write same | `rt_scsi_write_same10/16()` (erase path in `scsi_sd`) |
| Mode select/sense | mode structs | `rt_scsi_mode_*` (auto-refresh in `scsi_sd`) |

Use these when implementing **`transfer`** for a new HBA or when extending **`driver_table`** for another device type.

---

## Debugging

| Symptom | Checks |
| --- | --- |
| `-RT_EEMPTY` | No LUN answered INQUIRY — wiring, power, `max_id`/`max_lun`, firmware |
| `-RT_ETIMEOUT` in setup | Media not ready — TEST UNIT READY loop |
| `-RT_ENOSYS` | Unsupported `devtype` — enable `RT_SCSI_SD` / `RT_SCSI_CDROM` or add `driver_table` entry |
| READ/WRITE fail | Sense via `rt_scsi_request_sense`; verify `cmd->data.size` is in **sectors** for READ/WRITE helpers |
| VirtIO hotplug | `virtio_scsi_config_changed` → rescan; log `virtio.dev.scsi` |

---

## See also

- @ref page_device_ata — AHCI port → SCSI → `sd*`
- @ref page_device_blk — block layer API
- @ref page_device_disk — `rt_blk_disk` registration
- `components/drivers/include/drivers/scsi.h`
- `components/drivers/scsi/scsi.c`
- `components/drivers/virtio/virtio-scsi.c`
