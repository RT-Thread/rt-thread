@page page_device_ata ATA / AHCI

# AHCI host abstraction (`ahci.h`)

This page documents **`struct rt_ahci_host`**, **`struct rt_ahci_ops`**, and per-port **`struct rt_ahci_port`** in **`drivers/ahci.h`**, as driven by **`rt_ahci_host_register` / `rt_ahci_host_unregister`** in `components/drivers/ata/ahci.c`.

## `struct rt_ahci_host` (caller fills before `rt_ahci_host_register`)

```368:383:components/drivers/include/drivers/ahci.h
struct rt_ahci_host
{
    struct rt_scsi_host parent;

    int irq;
    void *regs;

    rt_size_t ports_nr;
    rt_uint32_t ports_map;
    struct rt_ahci_port ports[32];

    rt_uint32_t cap;
    rt_uint32_t max_blocks;

    const struct rt_ahci_ops *ops;
};
```

| Member | Owner | Meaning |
| --- | --- | --- |
| `parent` | **Caller** | Embedded **`rt_scsi_host`**; **`parent.dev` must be non-NULL** (used for `rt_dma_alloc_coherent`, etc.). |
| `irq` | **Caller** | Global host IRQ; the core installs the ISR with `struct rt_ahci_host *` as parameter. |
| `regs` | **Caller** | Virtual base of the HBA (AHCI 1.0) register block. |
| `ports_nr` | **Core** | Filled from **`CAP.NP`**; do not rely on the initial value. |
| `ports_map` | **Core (DT may override)** | Read from **`PI`**; if the node has **`ports-implemented`**, that property wins. |
| `ports[]` | **Core + ops** | See **Per-port state** below. |
| `cap` | **Core** | Read from **`RT_AHCI_HBA_CAP`** (masked); used with SG paths for **64-bit DMA** (**`RT_AHCI_CAP_64`**, etc.). |
| `max_blocks` | **Caller (may be 0)** | Max blocks per SCSI split; **0** is replaced with **`0x80`** at register time. |
| `ops` | **Caller** | **Required**; every callback is optional (**`NULL`** = core default), but failures in **`host_init` / `port_init` / `port_dma_init`** skip the port or log DMA errors. |

## `struct rt_ahci_port` (fields visible to `ops`)

```346:366:components/drivers/include/drivers/ahci.h
struct rt_ahci_port
{
    void *regs;

    void *dma;
    rt_ubase_t dma_handle;

    struct rt_ahci_cmd_hdr *cmd_slot;
    struct rt_ahci_sg *cmd_tbl_sg;
    void *cmd_tbl;
    rt_ubase_t cmd_tbl_dma;
    void *rx_fis;

    rt_uint32_t int_enabled;
    rt_size_t block_size;

    rt_uint16_t *ataid;

    rt_bool_t link;
    struct rt_completion done;
};
```

| Member | Owner | Meaning |
| --- | --- | --- |
| `regs` | **Core** | `host->regs + 0x100 + port_index * 0x80`; valid before **`port_init`**. |
| `dma`, `dma_handle`, `cmd_slot`, `rx_fis`, `cmd_tbl`, `cmd_tbl_dma`, `cmd_tbl_sg` | **Core** | After **`link == RT_TRUE`**, **`RT_AHCI_DMA_SIZE`** coherent memory is allocated and laid out; **`CLB`/`CLBU`**, **`FB`/`FBU`** programmed. |
| `int_enabled` | **Core** | **`RT_AHCI_PORT_INTE_*`** mask written to **`PORT_INTE`** after DMA engines start. |
| `block_size` | **Core** | **512** or **2048** from Identify / Inquiry and **SIG** / **ATAPI**. |
| `ataid` | **Core** | Identify buffer; used with **`rt_ahci_ata_id_*`** helpers. |
| `link` | **Core** | **`RT_TRUE`** when link is up; ISR calls **`port_isr`** and **`rt_completion_done`** only if **`link`**. |
| `done` | **Core** | **`rt_completion_init`**; command path **`rt_completion_wait(&port->done, …)`** after **`PORT_CI`**; **`port_isr`** must stay consistent with **`done`**. |

In **`port_init` / `port_dma_init`** you may touch **`port->regs`** and other HW state not yet filled by the core. **Do not assume `dma` exists inside `port_init`** (DMA is allocated only after a successful link).

## `struct rt_ahci_ops` (order inside `rt_ahci_host_register`)

```385:392:components/drivers/include/drivers/ahci.h
struct rt_ahci_ops
{
    rt_err_t (*host_init)(struct rt_ahci_host *host);
    rt_err_t (*port_init)(struct rt_ahci_host *host, struct rt_ahci_port *port);
    rt_err_t (*port_link_up)(struct rt_ahci_host *host, struct rt_ahci_port *port);
    rt_err_t (*port_dma_init)(struct rt_ahci_host *host, struct rt_ahci_port *port);
    rt_err_t (*port_isr)(struct rt_ahci_host *host, struct rt_ahci_port *port, rt_uint32_t isr);
};
```

| Callback | When | Role |
| --- | --- | --- |
| **`host_init`** | After HBA soft reset, **`GHC.AHCI_EN`**, **CAP** read/mask, **`PI` write**, before port enumeration. | Optional. HBA-level, clocks, PHY, vendor regs; non-**`RT_EOK`** fails **`rt_ahci_host_register`**. |
| **`port_init`** | After **`PORT_CMD`** has **LIST_ON/FIS_ON/START/FIS_RX** cleared and the port has quiesced, before **SPIN_UP**. | Optional. Port reset, **`SCTL`**, non-standard **SIG**; **`port->regs`** valid. Failure **`continue`**s the port. |
| **`port_link_up`** | After **`port_init`** and the core has set **SPIN_UP**. | Optional. If **`NULL`**, core polls **`SSTS.DET`** for **`PHYRDY`**. Must return **`RT_EOK`** when the link is usable. |
| **`port_dma_init`** | After **`CLB`/`FB`** and DMA buffers are programmed, before the core writes **`PORT_CMD`** (ACTIVE, FIS_RX, POWER_ON, SPIN_UP, START). | Optional. Extra SoC DMA/port setup; errors are logged but the core still asserts **`PORT_CMD`**. |
| **`port_isr`** | Global ISR: bit set in **`HBA_INTS`**, **`port->link`**, **`PORT_INTS`** read into **`isr`**. | Optional. SoC-specific IRQ handling; core always **`rt_completion_done(&port->done)`** and clears **`PORT_INTS`**. |

### Common integration pitfalls

- **`port_init` vs DMA**: **`port->dma` is not allocated yet** inside **`port_init`**—only touch **`port->regs`** and PHY-level setup there.
- **`port_dma_init` errors are logged only**: the core still enables **`PORT_CMD`**—if your SoC cannot run without extra setup, fail earlier in **`port_link_up`** instead.
- **`port_isr`**: if you override, ensure you still cooperate with **`rt_completion_done`** semantics expected by **`ahci.c`** command path, or commands hang.
- **64-bit DMA**: honor **`RT_AHCI_CAP_64`** when building PRDT—SG list addresses must match HBA capability.

## Registration API

| API | Role |
| --- | --- |
| **`rt_ahci_host_register(host)`** | Validates **`host`**, **`host->parent.dev`**, **`host->ops`**; HBA reset, ports, link, DMA, **`rt_scsi_host_register`**, IRQ. |
| **`rt_ahci_host_unregister(host)`** | Masks IRQ, frees per-port DMA, unregisters the SCSI host. |

## See also

- `components/drivers/include/drivers/ahci.h` (**`RT_AHCI_*`**, **`struct rt_ahci_cmd_hdr`**, **`struct rt_ahci_sg`**)
- `components/drivers/ata/ahci.c`

**Same documentation pattern** (fill structs + `ops` + register order): `documentation/6.components/device-driver/ufs/ufs.md`, `nvme/nvme.md`, `scsi/scsi.md` (section 1), `block/disk.md`, `dma/dma.md` (section 1).
