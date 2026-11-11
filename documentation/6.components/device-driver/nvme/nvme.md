@page page_device_nvme NVMe subsystem

# NVMe controller API

Header: **`components/drivers/include/drivers/nvme.h`**. Core: **`components/drivers/nvme/nvme.c`**.

RT-Thread implements an **NVMe host** stack: admin + I/O queues, Identify, namespace scan, and **`rt_hw_blk_disk_register`** per namespace. PCI binding: @ref page_device_nvme_dm.

---

## Kconfig (summary)

| Option | Role |
| --- | --- |
| **`RT_USING_NVME`** | Core **`nvme.c`** — needs **`RT_USING_DM`**, **`RT_USING_BLK`**, **`RT_USING_DMA`** |
| **`RT_USING_NVME_IO_QUEUE`** | I/O queue count (default scales with **`RT_THREAD_PRIORITY_*`**) |
| **`RT_NVME_PCI`** | **`nvme-pci.c`** — needs **`RT_USING_PCI`** |

---

## Architecture

```
  Transport (e.g. PCI): map BAR, setup IRQs/MSI-X
        |
        |  fill struct rt_nvme_controller + ops
        v
  rt_nvme_controller_register(nvme)
        |
        |  CAP/MQES, admin queue, IO queues (DMA)
        |  Identify Controller, scan namespaces
        v
  Per-NS: rt_hw_blk_disk_register → block device "nvme0n1" ...
        |
        v
  blk layer: read/write/flush via nvme_submit_io_cmd (per-CPU queue)
```

---

## `struct rt_nvme_controller` (caller fills before register)

| Member | Owner | Meaning |
| --- | --- | --- |
| **`dev`** | **Caller** | Used for **`rt_dma_alloc`/`free`** on queue buffers |
| **`regs`** | **Caller** | MMIO base (**`CAP`**, **`CC`**, doorbells) |
| **`ops`** | **Caller** | **Required**; at least **`name`** for logging |
| **`irqs_nr`**, **`irqs[]`** | **Caller** | One entry per queue (MSI-X preferred); see PCI glue |
| **`nvme_id`**, **`name`** | **Core** | **`rt_dm_ida`**, **`nvme%u`** |
| **`cap`**, **`queue_depth`**, **`doorbell_*`** | **Core** | From **`CAP`** register |
| **`max_transfer_shift`**, **`write_zeroes`**, **`sgl_mode`** | **Core** | From Identify Controller |
| **`queue[]`**, **`admin_queue`**, **`io_queues[]`** | **Core** | SQ/CQ DMA rings + completions |

Do not pre-fill queue state—the core zeroes and allocates DMA in **`nvme_alloc_queue`**.

---

## `struct rt_nvme_ops`

```c
struct rt_nvme_ops {
    const char *name;
    rt_err_t (*setup_queue)(struct rt_nvme_queue *queue);
    rt_err_t (*cleanup_queue)(struct rt_nvme_queue *queue);
    rt_err_t (*submit_cmd)(struct rt_nvme_queue *queue, struct rt_nvme_command *cmd);
    void (*complete_cmd)(struct rt_nvme_queue *queue, struct rt_nvme_command *cmd);
};
```

| Callback | When | Role |
| --- | --- | --- |
| **`name`** | Logging | e.g. **`"PCI"`** |
| **`setup_queue`** | After SQ/CQ DMA alloc in **`nvme_alloc_queue`** | SoC-specific queue programming |
| **`cleanup_queue`** | **`nvme_free_queue`** | Undo setup |
| **`submit_cmd`** | After command copied to SQ slot, before doorbell | Custom doorbell / FIFO |
| **`complete_cmd`** | CQ ISR after phase check | Extra HW ack (shared IRQ, vendor IP) |

**Return polarity (important):** in current **`nvme.c`**, **`setup_queue`** / **`cleanup_queue`** use **`if (!(err = ops->...))`** — a **non-zero** return is treated as **success**, **zero** as failure. Match this when porting quirks, or align **`nvme.c`** with upstream when fixing.

**`submit_cmd`**: uses normal **`RT_EOK`** — non-zero aborts submit.

---

## Registration API

```c
rt_err_t rt_nvme_controller_register(struct rt_nvme_controller *nvme);
rt_err_t rt_nvme_controller_unregister(struct rt_nvme_controller *nvme);
```

### `rt_nvme_controller_register` sequence

1. Validate **`nvme`**, **`ops`**; check **`CSTS`** not **`0xffffffff`**
2. **`rt_dm_ida_alloc`** → **`nvme%u`**
3. Read **`CAP`**, configure **admin queue** (disable → alloc → enable)
4. Create **I/O queues** (**`RT_USING_NVME_IO_QUEUE * RT_CPUS_NR`** max)
5. **Identify Controller** — MDTS, VWC, ONCS, SGL support
6. **`nvme_scan_device`** — for each namespace id: Identify NS, **`rt_hw_blk_disk_register`**
7. Link on global **`nvme_nodes`** list

### `rt_nvme_controller_unregister`

Removes namespaces, IO/admin queues, frees IDA, **shutdown + disable** controller.

---

## Namespaces (`struct rt_nvme_device`)

| Field | Role |
| --- | --- |
| Embeds **`struct rt_blk_disk parent`** | Block layer entry |
| **`nsid`** | Namespace ID (1-based in scan loop) |
| **`lba_shift`** | From active LBA format |
| **`id`** | Copy of **`struct rt_nvme_id_ns`** |

Disk name pattern: **`nvme{N}n{nsid}`** (e.g. **`nvme0n1`**).

---

## Command path (I/O)

- **`nvme_submit_io_cmd`**: picks I/O queue **`rt_atomic_add(&ioqid[cpu], RT_CPUS_NR) % io_queue_max`** (per-CPU striping).
- **`nvme_submit_cmd`**: copies **`struct rt_nvme_command`** to SQ tail, rings doorbell (unless **`ops->submit_cmd`**), **`rt_completion_wait`** for CQ.
- Data path: **PRP** by default; **SGL** if Identify reports SGL support.

Admin commands use **`admin_queue`** with a **60 s** completion timeout; I/O queues use **`RT_WAITING_FOREVER`**.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`setup_queue` return code** | Inverted vs **`RT_EOK`** — see ops table above |
| **Page size** | Host **`ARCH_PAGE_SHIFT`** must be ≥ device **`MPSMIN`** or register fails |
| **IRQ count** | **`irqs_nr`** should cover admin + IO queues used; MSI-X preferred (@ref page_device_nvme_dm) |
| **Unregister order** | Mask IRQs in transport **`remove`** before **`rt_nvme_controller_unregister`** |
| **Admin queue blocking** | Do not hold locks that block admin path from I/O context |

---

## See also

- @ref page_device_nvme_dm
- @ref page_device_pci
- @ref page_device_numa
- @ref page_device_dma
- <https://nvmexpress.org/developers/>
- `components/drivers/nvme/nvme.c`
- `components/drivers/nvme/nvme-pci.c`
