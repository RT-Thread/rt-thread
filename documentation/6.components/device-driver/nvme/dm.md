@page page_device_nvme_dm NVMe device model (DM)

# NVMe under `RT_USING_DM`

**`RT_USING_NVME`** builds the protocol core (**`nvme.c`**) and optionally **`nvme-pci.c`** (**`RT_NVME_PCI`**). Controllers register with **`rt_nvme_controller_register`**; each namespace becomes a **`rt_blk_disk`** for the block layer.

Controller API and queue ops: @ref page_device_nvme.

Sources: **`components/drivers/nvme/nvme.c`**, **`nvme-pci.c`**, **`components/drivers/include/drivers/nvme.h`**.

---

## Kconfig / build

| Option | Depends on | Role |
| --- | --- | --- |
| **`RT_USING_NVME`** | **`RT_USING_DM`**, **`RT_USING_BLK`**, **`RT_USING_DMA`** | Core stack |
| **`RT_USING_NVME_IO_QUEUE`** | **`RT_USING_NVME`** | Number of I/O queues (2/4/8 by priority profile) |
| **`RT_NVME_PCI`** | **`RT_USING_NVME`**, **`RT_USING_PCI`** | PCI function driver (default **y**) |
| **`SOC_DM_NVME_DIR`** | BSP | Extra non-PCI controllers |

**`RT_USING_NVME_QUEUE`** in **`nvme.h`** is **`1 + RT_USING_NVME_IO_QUEUE * RT_CPUS_NR`** (admin + per-CPU IO slots).

---

## PCI transport (`nvme-pci.c`)

### Matching

```c
static const struct rt_pci_device_id pci_nvme_ids[] = {
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0010) },
    { RT_PCI_DEVICE_CLASS(PCIS_STORAGE_EXPRESS, ~0) },
};
```

Any **NVMe class** PCI function binds **`nvme-pci`** driver.

### Probe flow

```
  pci_nvme_probe(pdev)
        |
        |  rt_pci_iomap(pdev, 0) → nvme->regs
        |  ops = quirk->ops ?: pci_nvme_std_ops ("PCI")
        |  MSI-X: rt_pci_msix_enable → nvme->irqs[i]
        |  else: single pdev->irq, rt_pci_irq_unmask
        |  rt_pci_set_master(pdev)
        v
  rt_nvme_controller_register(nvme)
        |
        v
  pdev->parent.user_data = pci_nvme
```

### Remove / shutdown

1. **`rt_nvme_controller_unregister`**
2. MSI-X disable or INTx mask
3. **`rt_pci_clear_master`**, **`rt_iounmap(regs)`**, free **`pci_nvme_controller`**

### Quirks

**`pdev->id->data`** may point to **`struct pci_nvme_quirk`** with alternate **`rt_nvme_ops`** (vendor MMIO). Default uses standard doorbell path in **`nvme.c`**.

---

## IRQ and NUMA affinity

| Mode | Behavior |
| --- | --- |
| **MSI-X** | Up to **`RT_USING_NVME_QUEUE`** vectors; linear index mapping |
| **INTx** | **`irqs_nr = 1`**, shared line — rely on **`complete_cmd`** to disambiguate if needed |

**`INIT_SECONDARY_CPU_EXPORT(nvme_queue_affinify_fixup)`** (in **`nvme.c`**):

- Runs when secondary CPUs start
- For each controller I/O queue index **`i ≡ cpuid (mod RT_CPUS_NR)`**, sets IRQ affinity to that CPU via **`rt_pic_irq_set_affinity`**
- Pairs with @ref page_device_numa when **`numa=on`** — keep queue IRQ near memory node

Assign **`nvme->irqs[]`** before **`rt_nvme_controller_register`** — core wires ISR per queue during setup.

---

## DMA

Queue rings allocated with **`rt_dma_alloc(nvme->dev, ...)`** and **`nvme_queue_dma_flags()`** (coherent / device attributes per **`dev`**).

Identify buffers use **`rt_malloc_align(..., nvme->page_size)`** after page size is negotiated from **`CAP.MPSMIN/MAX`**.

---

## Block device exposure

After Identify NS:

```c
ndev->parent.ops = &nvme_blk_ops;
ndev->parent.parallel_io = RT_TRUE;
rt_dm_dev_set_name(&ndev->parent.parent, "%sn%u", nvme->name, nsid);
rt_hw_blk_disk_register(&ndev->parent);
```

Partitions use standard **`RT_BLK_PARTITION_MAX`** — see disk/partitions docs if enabled in BSP.

---

## Non-PCI controllers

1. Map **`regs`**, implement **`struct rt_nvme_ops`** ( **`setup_queue`/`submit_cmd`/`complete_cmd`** as needed).
2. Fill **`irqs[]`** for admin + IO queues.
3. Set **`nvme->dev`** to the **`rt_device`** used for DMA mapping.
4. **`rt_nvme_controller_register`**.
5. Add Kconfig under **`SOC_DM_NVME_DIR`** and platform/PCIe-alt probe.

---

## Checklist (PCI BSP)

1. Enable **`RT_USING_DM`**, **`RT_USING_PCI`**, **`RT_USING_BLK`**, **`RT_USING_DMA`**, **`RT_USING_NVME`**, **`RT_NVME_PCI`**.
2. ECAM/host bridge probes before NVMe function.
3. Ensure **`rt_pci_set_master`** path runs (done in **`pci_nvme_probe`**).
4. Prefer **MSI-X** in firmware/DT if available.
5. For multi-node servers: **`numa=on`** + CPU/memory **`numa-node-id`** in DT (@ref page_device_numa).
6. Verify namespace appears as **`nvme0n1`** (etc.) and partition mount if used.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **BAR not mapped** | **`rt_pci_iomap`** failure → probe abort |
| **MSI-X vector shortage** | Falls back to INTx — may need **`complete_cmd`** |
| **`CSTS == -1`** | Usually bad BAR/endianness — register rejects early |
| **Inverted `setup_queue` success** | @ref page_device_nvme — match **`nvme.c`** polarity |
| **Secondary CPU IRQ affinity** | Ensure **`nvme_queue_affinify_fixup`** runs (SMP BSP) |

---

## See also

- @ref page_device_nvme
- @ref page_device_pci
- @ref page_device_numa
- @ref page_device_dma
- `components/drivers/nvme/Kconfig`
