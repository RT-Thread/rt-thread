@page page_device_ufs UFS host

# UFS host controller

Header: **`components/drivers/include/drivers/ufs.h`**. Core: **`components/drivers/ufs/ufs.c`**, link/PA PM: **`ufs_pm.c`**.

RT-Thread implements a **UFSHCI host**: UIC for UniPro link (DME), UTP for SCSI-over-UPIU, then **`rt_scsi_host_register`** so the existing SCSI core scans LUNs and registers **`sd*`** disks (@ref page_device_scsi, **`RT_SCSI_SD`**).

There is **no separate UFS device-model bus** in-tree—only the **host adapter** API plus optional **PCI** glue (`ufs-pci.c`). SoC controllers use **`struct rt_ufs_ops::init` / `exit`** (and BSP code under **`SOC_DM_UFS_DIR`** when enabled in Kconfig) for clocks, reset, PHY, and supplies.

---

## Kconfig

| Option | Depends on | Role |
| --- | --- | --- |
| **`RT_USING_UFS`** | **`RT_USING_DM`**, **`RT_USING_DMA`**, **`RT_SCSI_SD`** | **`ufs.c`**, **`ufs_pm.c`** |
| **`RT_UFS_PCI`** | **`RT_USING_UFS`**, **`RT_USING_PCI`** | **`ufs-pci.c`** (`RT_PCI_DRIVER_EXPORT`) |
| **`SOC_DM_UFS_DIR`** | **`RT_USING_UFS`** | BSP Kconfig / SoC UFS platform driver (out of tree here) |

Enable **`RT_USING_SCSI`** and **`RT_SCSI_SD`** before UFS; the stack ends at **`rt_blk_disk`** / **`sd*`** (@ref page_device_blk, @ref page_device_disk).

---

## End-to-end flow

```
  Platform / PCI: MMIO (regs), IRQ, parent.dev for DMA
        |
        |  static struct my_ufs { struct rt_ufs_host parent; ... };
        |  fill regs, irq, ops; parent.dev = &controller->parent;
        v
  rt_ufs_host_register(ufs)
        |  CAP → nutrs; alloc UTRL/UCD/bounce (coherent via parent.dev)
        |  ops->init (optional): clk, reset, regulator, PHY
        |  HCE, program UTRLBA/UTMRLBA, UTRLRSR/UTMRLRSR
        |  DME_LINKSTARTUP if HCS not ready (+ link_startup_notify PRE/POST)
        |  rt_ufs_pm_post_linkup (IRQ aggregation, Auto-H8 AHIT)
        |  IRQ install; parent.ops = ufs_host_ops; parallel_io = RT_TRUE
        v
  rt_scsi_host_register(&ufs->parent)
        |  INQUIRY per (id, lun) → scsi_sd_probe → sd*
        v
  Applications use blk API
```

**Unregister**: **`rt_ufs_host_unregister`** → **`rt_scsi_host_unregister`** → **`ops->exit`**, free DMA, mask IRQ.

**Runtime I/O**: SCSI **`transfer`** builds UPIU + UTRD, rings doorbell, waits on **`ufs->done`** (ISR sets completion on **`UTRCS`** / fatal bits). Small buffers use an internal **bounce** region (4 KiB) so inquiry/sense/capacity do not require caller DMA mapping.

---

## Host driver responsibilities (before register)

| Field | Caller | Notes |
| --- | --- | --- |
| **`parent.dev`** | **Required** | Every **`rt_dma_alloc_coherent`** uses this device; set **`ofw_node`** consistently for DM naming. |
| **`regs`** | **Required** | UFSHCI MMIO base. |
| **`irq`** | **Required** | Installed at end of register; name **`ufs-<devname>`**. |
| **`ops`** | **Required** | Struct pointer; individual hooks optional. |
| **`ucd_size`** | Optional | **0** → **`RT_UFS_UCD_SIZE`**. |
| **`ahit`** | Optional | Raw **AHIT** register; **0** → default in **`rt_ufs_pm_post_linkup`** when **`CAP_AUTOH8`**. |
| **`parent.max_id` / `max_lun`** | Optional | Raised to at least **1** if zero; tune scan range for your topology. |
| UTRL/UCD/bounce/`cap`/`nutrs`/… | **Core** | Do not pre-allocate. |

After success, **`ufs->parent.ops`** points to internal **`ufs_host_ops`** (SCSI path). Vendor hooks stay in **`struct rt_ufs_ops`** only.

---

## `struct rt_ufs_ops`

| Callback | When | Role |
| --- | --- | --- |
| **`init`** | After DMA alloc, before **HCE** and list base programming | Clocks, reset, PHY, vendor regs; failure rolls back buffers. |
| **`link_startup_notify`** | Before/after **`DME_LINKSTARTUP`** when lists not ready | **`RT_UFS_NOTIFY_CHANGE_STATUS_PRE` / `POST`** for extra DME traffic—keep short. |
| **`reset`** | SCSI host **`reset`** path | Controller/link recovery (optional). |
| **`exit`** | After **`rt_scsi_host_unregister`** | Undo **`init`**; errors logged only. |

Minimal PCI reference uses empty **`pci_ufs_std_ops`**—BAR map + **`rt_ufs_host_register`** only (`ufs-pci.c`). SoC hosts should implement **`init`/`exit`** for @ref page_device_regulator, @ref page_device_clk, @ref page_device_reset, @ref page_device_power_domain.

---

## `rt_ufs_host_register` sequence (core)

1. Validate **`ufs`**, **`ops`**, **`regs`**; read **`CAP`**, **`nutrs`** (cap 32 slots).
2. Allocate **UTRL** (1 KiB aligned), **UCD**, **bounce** via **`parent.dev`**.
3. **`ops->init`** if present.
4. **HCE** pulse; program **UTRLBA/U**, **UTMRLBA/U**; set **UTRLRSR**, **UTMRLRSR**.
5. If **HCS** lacks **UTRLRDY/UTMRLRDY/UCRDY**: optional notify → **`rt_ufs_uic_cmd_send(DME_LINKSTARTUP)`** → notify.
6. **`rt_ufs_pm_post_linkup`** (see below).
7. IRQ + **`rt_scsi_host_register`** with **`ufs_host_ops`**.

UIC helpers (**`rt_ufs_uic_cmd_send`**, **`rt_ufs_dme_set`/`get`**) are for bring-up and PM; normal storage traffic stays on the SCSI path.

---

## Link and HCI power management

Implementation: **`ufs_pm.c`**. This layer is **UniPro PA / Hibernate8 / UFSHCI idle features**, not system suspend. Rails and clocks belong in **`init`/`exit`**.

### Boot defaults (`rt_ufs_pm_post_linkup`)

Called from register after link-up (safe to call again after custom training):

| Step | API | Role |
| --- | --- | --- |
| IRQ aggregation | **`rt_ufs_intr_aggr_configure(ufs, RT_TRUE, cnt, 2)`** | **UTRIACR** — batch completion IRQs (`cnt` ≈ **`nutrs - 1`**, max 31) |
| Auto-Hibernate8 | **`rt_ufs_auto_hibern8_set`** | If **`cap & RT_UFS_REG_CAP_AUTOH8`**, programs **AHIT** |

**`ahit`**: **0** uses **`RT_UFS_AHIT_DEFAULT`** (~150 ms idle); non-zero is written as-is; disable later with **`rt_ufs_auto_hibern8_set(ufs, 0)`**. Encode timers with **`rt_ufs_ahit_encode(timer, scale)`**.

### PA power mode (optional, not auto at register)

```c
struct rt_ufs_pa_layer_attr attr = { /* gear, lanes, pwr_rx/tx, hs_rate */ };
rt_ufs_pa_power_mode_set(ufs, &attr, force);
```

Skips when attributes match cached **`pwr_active`** unless **`force`**. Use after link is stable for performance vs power; **`ufs-pci.c`** does not set PA mode today.

### Hibernate8

| API | Use |
| --- | --- |
| **`rt_ufs_hibern8_enter` / `exit`** | Explicit **DME_HIBERNATE_ENTER/EXIT** when **`CAP_AUTOH8`** is absent or for long idle policy |

Finish outstanding UTP transfers before enter; exit before new SCSI commands.

### Suggested bring-up order

1. **`ops->init`**: SoC clock / reset / regulator / PHY.
2. **`rt_ufs_host_register`** → link startup → **`rt_ufs_pm_post_linkup`**.
3. Optional **`rt_ufs_pa_power_mode_set`** for target gear/mode.
4. Runtime: Auto-H8 and/or manual Hibernate8.
5. **`rt_ufs_host_unregister`** → **`ops->exit`**.

---

## PCI binding (`RT_UFS_PCI`)

**`ufs-pci.c`**: **`pci_ufs_probe`** iomaps BAR0, takes **`pdev->irq`**, **`rt_pci_set_master`**, **`rt_ufs_host_register`**. IDs include Red Hat **`0x0013`** and Samsung **`0xc00c`**. **`remove`/`shutdown`** call **`rt_ufs_host_unregister`**, unmap, free host struct.

No regulator or PA tuning in PCI glue—add a **`pci_ufs_quirk`** with custom **`rt_ufs_ops`** if a device needs it.

---

## Caches and debugging

UFS DMA paths use **`rt_hw_cpu_dcache_ops`** around UTRD/UCD (see @ref page_device_hwcache). Log tags: **`rtdm.ufs`**, **`rtdm.ufs.pm`**.

---

## See also

| Topic | Page / path |
| --- | --- |
| SCSI scan, **`sd*`**, CDB flow | @ref page_device_scsi |
| AHCI as another SCSI host | @ref page_device_ata |
| Sources | `components/drivers/ufs/ufs.c`, `ufs_pm.c`, `ufs-pci.c` |
