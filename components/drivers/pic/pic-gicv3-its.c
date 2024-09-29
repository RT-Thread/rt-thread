/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-30     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.gicv3-its"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>
#include <mm_page.h>
#include <cpuport.h>
#include <dt-bindings/size.h>
#include "pic-gicv3.h"
#include "pic-gic-common.h"

#define ITS_CMD_QUEUE_SIZE                  (64 * SIZE_KB)
#define ITS_CMD_QUEUE_ALIGN                 (64 * SIZE_KB)
#define ITS_CMD_QUEUE_NR                    (ITS_CMD_QUEUE_SIZE / sizeof(struct its_command))

#define ITS_ITT_ALIGN                       (256 * SIZE_KB)

#define ITS_LPI_CONFIG_TABLE_ALIGN          (64 * SIZE_KB)
#define ITS_LPI_CONFIG_PROP_DEFAULT_PRIO    GICD_INT_DEF_PRI
#define ITS_LPI_CONFIG_PROP_SHIFT           2
#define ITS_LPI_CONFIG_PROP_MASK            RT_GENMASK(7, ITS_LPI_CONFIG_PROP_SHIFT)
#define ITS_LPI_PENDING_TABLE_ALIGN         (64 * SIZE_KB)

#define RDIST_FLAGS_PROPBASE_NEEDS_FLUSHING RT_BIT(0)
#define RDIST_FLAGS_RD_TABLES_PREALLOCATED  RT_BIT(1)
#define RDIST_FLAGS_FORCE_NON_SHAREABLE     RT_BIT(2)

#define ITS_FLAGS_CMDQ_NEEDS_FLUSHING       RT_BIT(0)
#define ITS_FLAGS_WORKAROUND_CAVIUM_22375   RT_BIT(1)
#define ITS_FLAGS_FORCE_NON_SHAREABLE       RT_BIT(2)

#define RD_LOCAL_LPI_ENABLED                RT_BIT(0)
#define RD_LOCAL_PENDTABLE_PREALLOCATED     RT_BIT(1)
#define RD_LOCAL_MEMRESERVE_DONE            RT_BIT(2)

struct its_command
{
    union
    {
        rt_le64_t code_raw[4];
        rt_uint64_t code[4];
    };
};

struct its_table
{
    void *base;
    rt_uint64_t val;
    rt_uint32_t size_bits;
    rt_uint32_t page_size;
    union
    {
        struct
        {
            rt_uint32_t itt_entries;
            rt_uint32_t lvl2_bits;
        };
    };
};

struct its_collection
{
    rt_uint64_t target_address;
    rt_uint16_t id;
};

struct gicv3_its;

struct its_map
{
    rt_list_t list;
    struct rt_ref ref;
    struct gicv3_its *its;

    int device_id;
    int lpi_base;
    int cpu_id;

    void *itt;
    void *lvl2_dte;
};

struct gicv3_its
{
    struct rt_pic parent;
    rt_list_t list;

    void *base;
    void *base_phy;

    void *cmd_base;
    rt_ubase_t cmd_idx;
    rt_uint32_t flags;
    struct rt_spinlock cmd_lock;

    struct its_table tbls[GITS_BASER_NR_REGS];
    struct its_collection collections[RT_CPUS_NR];

    struct gicv3 *gic;
    struct rt_ofw_node *np;
};

#define raw_to_gicv3_its(raw) rt_container_of(raw, struct gicv3_its, parent)

static rt_size_t lpi_nr;
static rt_uint32_t lpi_id_bits;
static void *lpi_table;
static void *lpi_pending_table;
static rt_bitmap_t *lpis_vectors = RT_NULL;
static struct rt_spinlock lpis_lock = {}, map_lock = {};
static rt_list_t its_nodes = RT_LIST_OBJECT_INIT(its_nodes);
static rt_list_t map_nodes = RT_LIST_OBJECT_INIT(map_nodes);

rt_inline rt_uint64_t its_readq(struct gicv3_its *its, int off)
{
    return HWREG32(its->base + off) |
            (rt_uint64_t)HWREG32(its->base + off + 4) << 32;
}

rt_inline void its_writeq(struct gicv3_its *its, int off, rt_uint64_t value)
{
    HWREG32(its->base + off) = (rt_uint32_t)value;
    HWREG32(its->base + off + 4) = (rt_uint32_t)(value >> 32);
}

rt_inline rt_uint32_t its_readl(struct gicv3_its *its, int off)
{
    return HWREG32(its->base + off);
}

rt_inline void its_writel(struct gicv3_its *its, int off, rt_uint32_t value)
{
    HWREG32(its->base + off) = value;
}

rt_inline rt_uint32_t its_pirq_event_id(struct gicv3_its *its, struct rt_pic_irq *pirq)
{
    return pirq->hwirq - 8192;
}

rt_inline rt_uint32_t its_pirq_device_id(struct gicv3_its *its, struct rt_pic_irq *pirq)
{
    struct its_map *map = pirq->msi_desc->priv;

    return map->device_id;
}

rt_inline rt_size_t its_device_id_bits(struct gicv3_its *its)
{
    return RT_FIELD_GET(GITS_TYPER_DEVBITS, HWREG64(its->base + GITS_TYPER)) + 1;
}

rt_inline void *lpi_base_config(int index)
{
    return &((rt_uint8_t *)lpi_table)[index - 8192];
}

static void its_mask_encode(rt_uint64_t *raw_code, rt_uint64_t val, int h, int l)
{
    rt_uint64_t mask = RT_GENMASK_ULL(h, l);
    *raw_code &= ~mask;
    *raw_code |= (val << l) & mask;
}

rt_inline void its_encode_cmd(struct its_command *cmd, rt_uint8_t cmd_nr)
{
    its_mask_encode(&cmd->code[0], cmd_nr, 7, 0);
}

rt_inline void its_encode_valid(struct its_command *cmd, rt_bool_t valid)
{
    its_mask_encode(&cmd->code[2], !!valid, 63, 63);
}

rt_inline void its_encode_phys_id(struct its_command *cmd, rt_uint32_t phys_id)
{
    its_mask_encode(&cmd->code[1], phys_id, 63, 32);
}

rt_inline void its_encode_size(struct its_command *cmd, rt_uint8_t size)
{
    its_mask_encode(&cmd->code[1], size, 4, 0);
}

rt_inline void its_encode_itt(struct its_command *cmd, rt_uint64_t itt_addr)
{
    its_mask_encode(&cmd->code[2], itt_addr >> 8, 51, 8);
}

rt_inline void its_encode_target(struct its_command *cmd, rt_uint64_t target_addr)
{
    its_mask_encode(&cmd->code[2], target_addr >> 16, 51, 16);
}

rt_inline void its_encode_device_id(struct its_command *cmd, rt_uint32_t device_id)
{
    its_mask_encode(&cmd->code[0], device_id, 63, 32);
}

rt_inline void its_encode_event_id(struct its_command *cmd, rt_uint32_t event_id)
{
    its_mask_encode(&cmd->code[1], event_id, 31, 0);
}

rt_inline void its_encode_collection(struct its_command *cmd, rt_uint16_t collection_id)
{
    its_mask_encode(&cmd->code[2], collection_id, 15, 0);
}

static struct its_table *its_baser_type(struct gicv3_its *its, int type)
{
    for (int i = 0; i < RT_ARRAY_SIZE(its->tbls); ++i)
    {
        if (GITS_BASER_TYPE(its->tbls[i].val) == type)
        {
            return &its->tbls[i];
        }
    }

    return RT_NULL;
}

static struct its_command *its_cmd_alloc(struct gicv3_its *its)
{
    struct its_command *cmd = RT_NULL;

    for (rt_uint32_t count = 0; count <= 10000; ++count)
    {
        if ((its->cmd_idx + 1) % ITS_CMD_QUEUE_NR != its_readl(its, GITS_CREADR) / sizeof(*cmd))
        {
            struct its_command *cmds = its->cmd_base;

            cmd = &cmds[its->cmd_idx++];
            its->cmd_idx %= ITS_CMD_QUEUE_NR;

            rt_memset(cmd, 0, sizeof(*cmd));

            break;
        }

        rt_hw_us_delay(10);
    }

    return cmd;
}

static rt_err_t its_cmd_submit_raw(struct gicv3_its *its, struct its_command *cmd)
{
    rt_uint64_t cwriter;
    rt_bool_t retry = RT_FALSE;

    cwriter = (void *)(cmd + 1) - its->cmd_base;
    rt_hw_rmb();

#ifdef ARCH_CPU_BIG_ENDIAN
    cmd->code_raw[0] = rt_cpu_to_le64(cmd->code[0]);
    cmd->code_raw[1] = rt_cpu_to_le64(cmd->code[1]);
    cmd->code_raw[2] = rt_cpu_to_le64(cmd->code[2]);
    cmd->code_raw[3] = rt_cpu_to_le64(cmd->code[3]);
#endif /* ARCH_CPU_BIG_ENDIAN */

    /* Make sure the commands written to memory are observable by the ITS */
    if (its->flags & ITS_FLAGS_CMDQ_NEEDS_FLUSHING)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, cmd, sizeof(*cmd));
    }
    else
    {
        rt_hw_wmb();
    }

    its_writel(its, GITS_CWRITER, cwriter);

    for (rt_uint32_t count = 0; count < 10000; ++count)
    {
        if (its_readl(its, GITS_CREADR) == cwriter)
        {
            return RT_EOK;
        }

        /* Stalled */
        if (!retry && its_readl(its, GITS_CREADR) & 1)
        {
            /* Retry */
            its_writel(its, GITS_CWRITER, cwriter);
            retry = RT_TRUE;
        }
        else if (retry)
        {
            LOG_E("Retry command 0x%02x fail", cmd->code[0] & 0xff);

            return -RT_EIO;
        }

        rt_hw_us_delay(10);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t its_cmd_submit_nomap(struct gicv3_its *its, struct its_command *cmd,
        int cpu_id, rt_bool_t sync)
{
    rt_err_t err;
    struct its_command *hw_cmd;

    rt_hw_spin_lock(&its->cmd_lock.lock);

    if (!(hw_cmd = its_cmd_alloc(its)))
    {
        err = -RT_EBUSY;
        goto _out_lock;
    }

    rt_memcpy(hw_cmd, cmd, sizeof(*hw_cmd));

    if ((err = its_cmd_submit_raw(its, hw_cmd)))
    {
        goto _out_lock;
    }

    if (sync)
    {
        if (!(hw_cmd = its_cmd_alloc(its)))
        {
            err = -RT_EBUSY;
            goto _out_lock;
        }

        its_encode_cmd(hw_cmd, GITS_CMD_SYNC);
        its_encode_target(hw_cmd, its->collections[cpu_id].target_address);

        err = its_cmd_submit_raw(its, hw_cmd);
    }

_out_lock:
    rt_hw_spin_unlock(&its->cmd_lock.lock);

    return err;
}

static rt_err_t its_cmd_submit(struct gicv3_its *its, struct its_command *cmd,
        struct its_map *map, rt_bool_t sync)
{
    return its_cmd_submit_nomap(its, cmd, map->cpu_id, sync);
}

static rt_err_t lpi_flush_config(struct gicv3_its *its, rt_uint8_t *conf,
        struct rt_pic_irq *pirq)
{
    struct its_command cmd;
    struct its_map *map = pirq->msi_desc->priv;

    if (its->gic->redist_flags & RDIST_FLAGS_PROPBASE_NEEDS_FLUSHING)
    {
        /* Clean D-cache under command */
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, conf, sizeof(*conf));
    }
    else
    {
        /* DSB inner shareable, store */
        rt_hw_wmb();
    }

    rt_memset(&cmd, 0, sizeof(cmd));
    its_encode_cmd(&cmd, GITS_CMD_INV);
    its_encode_device_id(&cmd, its_pirq_device_id(its, pirq));
    its_encode_event_id(&cmd, its_pirq_event_id(its, pirq));

    return its_cmd_submit(its, &cmd, map, RT_FALSE);
}

rt_inline void *gicr_rd_base_percpu(struct gicv3 *gic)
{
    return gic->redist_regions[rt_hw_cpu_id()].base;
}

rt_inline void *gicr_rd_base(struct gicv3_its *its)
{
    return its->gic->redist_percpu_base[rt_hw_cpu_id()];
}

rt_inline rt_uint64_t *gicr_rd_flags(struct gicv3_its *its)
{
    return &its->gic->redist_percpu_flags[rt_hw_cpu_id()];
}

static rt_bool_t gicr_supports_plpis(struct gicv3_its *its)
{
    return !!(HWREG64(gicr_rd_base(its) + GICR_TYPER) & GICR_TYPER_PLPIS);
}

static rt_err_t redist_disable_lpis(struct gicv3_its *its)
{
    void *gicr = gicr_rd_base(its);
    rt_uint64_t timeout = 1000000L, val;

    if (!gicr_supports_plpis(its))
    {
        LOG_E("CPU#%d: LPIs not supported", rt_hw_cpu_id());
        return -RT_ENOSYS;
    }

    val = HWREG32(gicr + GICR_CTLR);
    if (!(val & GICR_CTLR_ENABLE_LPIS))
    {
        return RT_EOK;
    }

    /*
     * If coming via a CPU hotplug event, we don't need to disable
     * LPIs before trying to re-enable them. They are already
     * configured and all is well in the world.
     *
     * If running with preallocated tables, there is nothing to do.
     */
    if ((*gicr_rd_flags(its) & RD_LOCAL_LPI_ENABLED) ||
        (its->gic->flags & RDIST_FLAGS_RD_TABLES_PREALLOCATED))
    {
        return RT_EOK;
    }

    /* From that point on, we only try to do some damage control */
    LOG_W("CPU%d: Booted with LPIs enabled, memory probably corrupted", rt_hw_cpu_id());

    /* Disable LPIs */
    val &= ~GICR_CTLR_ENABLE_LPIS;
    HWREG32(gicr + GICR_CTLR) = val;

    /* Make sure any change to GICR_CTLR is observable by the GIC */
    rt_hw_barrier(dsb, sy);

    /*
     * Software must observe RWP==0 after clearing GICR_CTLR.EnableLPIs
     * from 1 to 0 before programming GICR_PEND{PROP}BASER registers.
     * Error out if we time out waiting for RWP to clear.
     */
    while (HWREG32(gicr + GICR_CTLR) & GICR_CTLR_RWP)
    {
        if (!timeout)
        {
            LOG_E("CPU#%d: Timeout while disabling LPIs", rt_hw_cpu_id());

            return -RT_ETIMEOUT;
        }

        rt_hw_us_delay(1);
        --timeout;
    }

    /*
     * After it has been written to 1, it is IMPLEMENTATION
     * DEFINED whether GICR_CTLR.EnableLPI becomes RES1 or can be
     * cleared to 0. Error out if clearing the bit failed.
     */
    if (HWREG32(gicr + GICR_CTLR) & GICR_CTLR_ENABLE_LPIS)
    {
        LOG_E("CPU#%d: Failed to disable LPIs", rt_hw_cpu_id());

        return -RT_EBUSY;
    }

    return RT_EOK;
}

static void gicv3_its_cpu_init_lpis(struct gicv3_its *its)
{
    void *gicr;
    rt_ubase_t paddr;
    rt_uint64_t val, tmp;

    if (*gicr_rd_flags(its) & RD_LOCAL_LPI_ENABLED)
    {
        return;
    }

    gicr = gicr_rd_base(its);

    val = HWREG32(gicr + GICR_CTLR);

    if ((its->gic->redist_flags & RDIST_FLAGS_RD_TABLES_PREALLOCATED) &&
        (val & GICR_CTLR_ENABLE_LPIS))
    {
        *gicr_rd_flags(its) |= RD_LOCAL_PENDTABLE_PREALLOCATED;

        goto _out;
    }

    paddr = (rt_ubase_t)rt_kmem_v2p(lpi_pending_table);

    /* Set PROPBASE */
    val = ((rt_ubase_t)rt_kmem_v2p(lpi_table) |
            GITS_CBASER_InnerShareable |
            GITS_CBASER_RaWaWb |
            ((lpi_id_bits - 1) & GICR_PROPBASER_IDBITS_MASK));

    HWREG64(gicr + GICR_PROPBASER) = val;
    tmp = HWREG64(gicr + GICR_PROPBASER);

    if (its->gic->redist_flags & RDIST_FLAGS_FORCE_NON_SHAREABLE)
    {
        tmp &= ~GICR_PBASER_SHARE_MASK_ALL;
    }

    if ((tmp ^ val) & GICR_PBASER_SHARE_MASK_ALL)
    {
        if (!(tmp & GICR_PBASER_SHARE_MASK_ALL))
        {
            /*
             * The HW reports non-shareable,
             * we must remove the cacheability attributes as well.
             */
            val &= ~(GICR_PBASER_SHARE_MASK_ALL | GICR_PBASER_INNER_MASK_ALL);
            val |= GICR_PBASER_nC;
            HWREG64(gicr + GICR_PROPBASER) = val;
        }

        if (!rt_hw_cpu_id())
        {
            LOG_I("Using cache flushing for LPI property table");
        }
        its->gic->redist_flags |= RDIST_FLAGS_PROPBASE_NEEDS_FLUSHING;
    }

    val = (paddr | GICR_PBASER_InnerShareable | GICR_PBASER_RaWaWb);

    HWREG64(gicr + GICR_PENDBASER) = val;
    tmp = HWREG64(gicr + GICR_PENDBASER);

    if (its->gic->redist_flags & RDIST_FLAGS_FORCE_NON_SHAREABLE)
    {
        tmp &= ~GICR_PBASER_SHARE_MASK_ALL;
    }

    if (!(tmp & GICR_PBASER_SHARE_MASK_ALL))
    {
        /*
         * The HW reports non-shareable, we must remove the
         * cacheability attributes as well.
         */
        val &= ~(GICR_PBASER_SHARE_MASK_ALL | GICR_PBASER_INNER_MASK_ALL);
        val |= GICR_PBASER_nC;
        HWREG64(gicr + GICR_PENDBASER) = val;
    }

    /* Enable LPIs */
    val = HWREG32(gicr + GICR_CTLR);
    val |= GICR_CTLR_ENABLE_LPIS;
    HWREG32(gicr + GICR_CTLR) = val;

    rt_hw_barrier(dsb, sy);

_out:
    *gicr_rd_flags(its) |= RD_LOCAL_LPI_ENABLED;
}

static void gicv3_its_cpu_init_collection(struct gicv3_its *its)
{
    rt_uint64_t target;
    int cpu_id = rt_hw_cpu_id();
    struct its_command cmd;
    struct its_collection *collection;

    if (HWREG64(its->base + GITS_TYPER) & GITS_TYPER_PTA)
    {
        target = (rt_uint64_t)rt_kmem_v2p(gicr_rd_base(its));
    }
    else
    {
        /* Linear by GICR processor number */
        target = HWREG64(gicr_rd_base(its) + GICR_TYPER);
        target = GICR_TYPER_CPU_NO(target) << 16;
    }

    collection = &its->collections[cpu_id];
    collection->target_address = target;
    collection->id = cpu_id;

    rt_memset(&cmd, 0, sizeof(cmd));
    its_encode_cmd(&cmd, GITS_CMD_MAPC);
    its_encode_collection(&cmd, collection->id);
    its_encode_target(&cmd, target);
    its_encode_valid(&cmd, RT_TRUE);
    its_cmd_submit_nomap(its, &cmd, cpu_id, RT_TRUE);

    rt_memset(&cmd, 0, sizeof(cmd));
    its_encode_cmd(&cmd, GITS_CMD_INVALL);
    its_encode_collection(&cmd, collection->id);
    its_cmd_submit_nomap(its, &cmd, cpu_id, RT_TRUE);
}

static rt_err_t gicv3_its_irq_init(struct rt_pic *pic)
{
    rt_err_t err;
    struct gicv3_its *its = raw_to_gicv3_its(pic);

    if ((err = redist_disable_lpis(its)))
    {
        return err;
    }

    gicv3_its_cpu_init_lpis(its);
    gicv3_its_cpu_init_collection(its);

    return RT_EOK;
}

static void gicv3_its_irq_mask(struct rt_pic_irq *pirq)
{
    rt_uint8_t *conf = lpi_base_config(pirq->hwirq);
    struct gicv3_its *its = raw_to_gicv3_its(pirq->pic);

    *conf &= ~GITS_LPI_CFG_ENABLED;
    lpi_flush_config(its, conf, pirq);

    rt_pci_msi_mask_irq(pirq);
}

static void gicv3_its_irq_unmask(struct rt_pic_irq *pirq)
{
    rt_uint8_t *conf = lpi_base_config(pirq->hwirq);
    struct gicv3_its *its = raw_to_gicv3_its(pirq->pic);

    *conf |= GITS_LPI_CFG_ENABLED;
    lpi_flush_config(its, conf, pirq);

    rt_pci_msi_unmask_irq(pirq);
}

static rt_err_t gicv3_its_irq_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    rt_uint8_t *conf = lpi_base_config(pirq->hwirq);
    struct gicv3_its *its = raw_to_gicv3_its(pirq->pic);

    *conf = (priority << ITS_LPI_CONFIG_PROP_SHIFT) | (*conf & (~ITS_LPI_CONFIG_PROP_MASK));

    return lpi_flush_config(its, conf, pirq);
}

static rt_err_t gicv3_its_irq_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity)
{
    int cpu_id;
    rt_err_t err;
    struct its_map *map;
    struct its_command cmd;
    struct its_collection *collection;
    struct gicv3_its *its = raw_to_gicv3_its(pirq->pic);

    map = pirq->msi_desc->priv;
    cpu_id = rt_bitmap_next_set_bit(affinity, 0, RT_CPUS_NR);
    collection = &its->collections[cpu_id];

    if (collection->target_address == ~0ULL)
    {
        return -RT_EIO;
    }

    if (map->cpu_id == cpu_id)
    {
        return RT_EOK;
    }

    rt_memset(&cmd, 0, sizeof(cmd));
    its_encode_cmd(&cmd, GITS_CMD_MOVI);
    its_encode_device_id(&cmd, map->device_id);
    its_encode_event_id(&cmd, its_pirq_event_id(its, pirq));
    its_encode_collection(&cmd, collection->id);

    if (!(err = its_cmd_submit(its, &cmd, map, RT_TRUE)))
    {
        map->cpu_id = cpu_id;
    }

    return err;
}

static void gicv3_its_irq_compose_msi_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    rt_ubase_t addr;
    struct gicv3_its *its = raw_to_gicv3_its(pirq->pic);

    addr = (rt_ubase_t)its->base_phy + GITS_TRANSLATER;

    msg->address_hi = rt_upper_32_bits(addr);
    msg->address_lo = rt_lower_32_bits(addr);
    msg->data = its_pirq_event_id(its, pirq);
}

static int gicv3_its_irq_alloc_msi(struct rt_pic *pic, struct rt_pci_msi_desc *msi_desc)
{
    rt_ubase_t level;
    rt_uint32_t device_id = -1;
    int irq = -1, hwirq, parent_irq, hwirq_index, lpi_base = 0;
    struct its_map *map = RT_NULL, *map_tmp;
    struct its_table *tbl;
    struct its_command cmd;
    struct rt_pic_irq *pirq;
    struct rt_pci_device *pdev = msi_desc->pdev;
    struct gicv3_its *its = raw_to_gicv3_its(pic);
    struct rt_pic *ppic = &its->gic->parent;

    tbl = its_baser_type(its, GITS_BASER_TYPE_DEVICE);
    RT_ASSERT(tbl != RT_NULL);

    if (!pdev->parent.ofw_node)
    {
        device_id = rt_pci_dev_id(pdev);
    }
    else
    {
        struct rt_ofw_cell_args args;

        for (int index = 0; ; ++index)
        {
            rt_err_t err = rt_ofw_parse_phandle_cells(pdev->parent.ofw_node,
                    "msi-parent", "#msi-cells", index, &args);

            if (err)
            {
                return (int)err;
            }

            if (args.data == its->np)
            {
                device_id = args.args[0];
            }

            rt_ofw_node_put(args.data);

            if ((rt_int32_t)device_id >= 0)
            {
                break;
            }
        }
    }

    if (device_id >= (1 << tbl->size_bits))
    {
        LOG_E("Device ID = is %x not supported", device_id);

        return -RT_EINVAL;
    }

    /* Find old map info */
    level = rt_spin_lock_irqsave(&map_lock);
    rt_list_for_each_entry(map_tmp, &map_nodes, list)
    {
        if (map_tmp->device_id == device_id)
        {
            map = map_tmp;
            lpi_base = map->lpi_base - 8192;
            break;
        }
    }
    rt_spin_unlock_irqrestore(&map_lock, level);

    if (!map)
    {
        rt_size_t itt_size;

        if (!(map = rt_calloc(1, sizeof(*map))))
        {
            return -RT_ENOMEM;
        }

        itt_size = tbl->itt_entries * (RT_FIELD_GET(GITS_TYPER_ITT_ENTRY_SIZE,
                HWREG64(its->base + GITS_TYPER)) + 1);
        itt_size = rt_max_t(rt_size_t, itt_size, ITS_ITT_ALIGN) + ITS_ITT_ALIGN - 1;

        map->itt = rt_malloc_align(itt_size, ITS_ITT_ALIGN);

        if (!map->itt)
        {
            rt_free(map);
            return -RT_ENOMEM;
        }

        if (tbl->lvl2_bits)
        {
            void *lvl2_dte;
            rt_uint64_t *entry;

            entry = tbl->base;
            entry += device_id / (tbl->page_size / GITS_LVL1_ENTRY_SIZE);

            if (*entry)
            {
                lvl2_dte = (void *)(*entry - PV_OFFSET);
                rt_page_ref_inc(lvl2_dte, tbl->lvl2_bits);
            }
            else
            {
                rt_size_t dte_size;

                lvl2_dte = rt_pages_alloc(tbl->lvl2_bits);

                if (!lvl2_dte)
                {
                    rt_free_align(map->itt);
                    rt_free(map);
                    return -RT_ENOMEM;
                }

                dte_size = rt_page_bits(tbl->lvl2_bits);
                rt_memset(lvl2_dte, 0, dte_size);

                if (!(tbl->val & GITS_BASER_SHARE_MASK_ALL))
                {
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, lvl2_dte, dte_size);
                }

                *entry = rt_cpu_to_le64((rt_uint64_t)rt_kmem_v2p(lvl2_dte) | GITS_BASER_VALID);

                if (!(tbl->val & GITS_BASER_SHARE_MASK_ALL))
                {
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, entry, sizeof(*entry));
                }

                rt_hw_dsb();
            }

            map->lvl2_dte = lvl2_dte;
        }

        rt_memset(map->itt, 0, itt_size);
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, map->itt, itt_size);
    }
    msi_desc->priv = map;

    /* Alloc the LPI base on the first LPI */
    level = rt_spin_lock_irqsave(&lpis_lock);
    hwirq_index = rt_bitmap_next_clear_bit(lpis_vectors, lpi_base, lpi_nr);

    if (hwirq_index >= lpi_nr)
    {
        irq = -RT_EEMPTY;
        goto _out_lock;
    }

    hwirq = 8192 + hwirq_index;
    parent_irq = ppic->ops->irq_map(ppic, hwirq, RT_IRQ_MODE_EDGE_RISING);
    if (parent_irq < 0)
    {
        irq = parent_irq;
        goto _out_lock;
    }

    irq = rt_pic_config_irq(pic, hwirq_index, hwirq);
    if (irq < 0)
    {
        goto _out_lock;
    }
    pirq = rt_pic_find_irq(pic, hwirq_index);

    pirq->mode = RT_IRQ_MODE_EDGE_RISING;
    rt_pic_cascade(pirq, parent_irq);

    rt_bitmap_set_bit(lpis_vectors, hwirq_index);

_out_lock:
    rt_spin_unlock_irqrestore(&lpis_lock, level);

    if (irq < 0)
    {
        return irq;
    }

    if (map->its)
    {
        rt_ref_get(&map->ref);
    }
    else
    {
        rt_list_init(&map->list);
        rt_ref_init(&map->ref);
        map->its = its;
        map->device_id = device_id;
        map->lpi_base = hwirq;

        level = rt_spin_lock_irqsave(&map_lock);
        rt_list_insert_before(&map_nodes, &map->list);
        rt_spin_unlock_irqrestore(&map_lock, level);
    }

    /* Default to CPU#0 */
    map->cpu_id = 0;
    RT_IRQ_AFFINITY_SET(pirq->affinity, map->cpu_id);

    rt_memset(&cmd, 0, sizeof(cmd));
    its_encode_cmd(&cmd, GITS_CMD_MAPD);
    its_encode_device_id(&cmd, device_id);
    its_encode_size(&cmd, rt_ilog2(tbl->itt_entries) - 1);
    its_encode_itt(&cmd, (rt_uint64_t)rt_kmem_v2p(map->itt));
    its_encode_valid(&cmd, RT_TRUE);
    its_cmd_submit(its, &cmd, map, RT_FALSE);

    rt_memset(&cmd, 0, sizeof(cmd));
    its_encode_cmd(&cmd, GITS_CMD_MAPTI);
    its_encode_device_id(&cmd, device_id);
    its_encode_event_id(&cmd, its_pirq_event_id(its, pirq));
    its_encode_phys_id(&cmd, hwirq);
    its_encode_collection(&cmd, its->collections[map->cpu_id].id);
    its_cmd_submit(its, &cmd, map, RT_TRUE);

    return irq;
}

static void its_map_release(struct rt_ref *r)
{
    rt_ubase_t level;
    struct gicv3_its *its;
    struct its_table *tbl;
    struct its_command cmd;
    struct its_map *map = rt_container_of(r, struct its_map, ref);

    its = map->its;
    tbl = its_baser_type(its, GITS_BASER_TYPE_DEVICE);

    rt_memset(&cmd, 0, sizeof(cmd));
    its_encode_cmd(&cmd, GITS_CMD_MAPD);
    its_encode_device_id(&cmd, map->device_id);
    its_encode_size(&cmd, rt_ilog2(tbl->itt_entries) - 1);
    its_encode_itt(&cmd, (rt_uint64_t)rt_kmem_v2p(map->itt));
    its_encode_valid(&cmd, RT_FALSE);
    its_cmd_submit(its, &cmd, map, RT_TRUE);

    level = rt_spin_lock_irqsave(&map_lock);
    rt_list_insert_before(&map_nodes, &map->list);
    rt_spin_unlock_irqrestore(&map_lock, level);

    if (map->itt)
    {
        rt_free_align(map->itt);
    }
    if (map->lvl2_dte)
    {
        if (rt_page_ref_get(map->lvl2_dte, tbl->lvl2_bits) == 1)
        {
            rt_uint64_t *entry;

            entry = tbl->base + (map->device_id / (tbl->page_size / GITS_LVL1_ENTRY_SIZE));
            *entry = rt_cpu_to_le64(0);

            if (!(tbl->val & GITS_BASER_SHARE_MASK_ALL))
            {
                rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, entry, sizeof(*entry));
            }
        }
        rt_pages_free(map->lvl2_dte, tbl->lvl2_bits);
    }
    rt_free(map);
}

static void gicv3_its_irq_free_msi(struct rt_pic *pic, int irq)
{
    rt_ubase_t level;
    struct its_map *map;
    struct its_command cmd;
    struct rt_pic_irq *pirq;
    struct gicv3_its *its = raw_to_gicv3_its(pic);

    pirq = rt_pic_find_pirq(pic, irq);

    if (!pirq)
    {
        return;
    }

    map = pirq->msi_desc->priv;

    rt_memset(&cmd, 0, sizeof(cmd));
    its_encode_cmd(&cmd, GITS_CMD_DISCARD);
    its_encode_device_id(&cmd, map->device_id);
    its_encode_event_id(&cmd, its_pirq_event_id(its, pirq));
    its_cmd_submit(its, &cmd, map, RT_TRUE);

    rt_pic_uncascade(pirq);

    level = rt_spin_lock_irqsave(&lpis_lock);
    rt_bitmap_clear_bit(lpis_vectors, pirq->hwirq - 8192);
    rt_spin_unlock_irqrestore(&lpis_lock, level);

    rt_ref_put(&map->ref, its_map_release);
}

static rt_err_t gicv3_its_irq_set_state(struct rt_pic *pic, int hwirq, int type, rt_bool_t state)
{
    struct its_map *map;
    struct its_command cmd;
    struct rt_pic_irq *pirq;
    struct gicv3_its *its = raw_to_gicv3_its(pic);

    if (type != RT_IRQ_STATE_PENDING || hwirq > 8192 + lpi_nr)
    {
        return -RT_ENOSYS;
    }

    if (!(pirq = rt_pic_find_irq(pic, hwirq - 8192)))
    {
        return -RT_ENOSYS;
    }

    map = pirq->msi_desc->priv;
    rt_memset(&cmd, 0, sizeof(cmd));

    if (state)
    {
        its_encode_cmd(&cmd, GITS_CMD_INT);
        its_encode_device_id(&cmd, map->device_id);
        its_encode_event_id(&cmd, its_pirq_event_id(its, pirq));
    }
    else
    {
        its_encode_cmd(&cmd, GITS_CMD_CLEAR);
        its_encode_device_id(&cmd, map->device_id);
        its_encode_event_id(&cmd, its_pirq_event_id(its, pirq));
    }

    its_cmd_submit(its, &cmd, map, RT_TRUE);

    return RT_EOK;
}

const static struct rt_pic_ops gicv3_its_ops =
{
    .name = "GICv3-ITS",
    .irq_init = gicv3_its_irq_init,
    .irq_ack = rt_pic_irq_parent_ack,
    .irq_mask = gicv3_its_irq_mask,
    .irq_unmask = gicv3_its_irq_unmask,
    .irq_eoi = rt_pic_irq_parent_eoi,
    .irq_set_priority = gicv3_its_irq_set_priority,
    .irq_set_affinity = gicv3_its_irq_set_affinity,
    .irq_compose_msi_msg = gicv3_its_irq_compose_msi_msg,
    .irq_alloc_msi = gicv3_its_irq_alloc_msi,
    .irq_free_msi = gicv3_its_irq_free_msi,
    .irq_set_state = gicv3_its_irq_set_state,
    .flags = RT_PIC_F_IRQ_ROUTING,
};

static rt_ssize_t its_baser_page_size(struct gicv3_its *its, struct its_table *tbl)
{
    rt_size_t page_size = 64 * SIZE_KB;

    while (page_size)
    {
        rt_uint64_t val, baser_page_size;
        rt_off_t baser = GITS_BASERn((int)(tbl - its->tbls));

        val = its_readq(its, baser);
        val &= ~GITS_BASER_PAGE_SIZE_MASK;

        switch (page_size)
        {
        case 64 * SIZE_KB:
            baser_page_size = GITS_BASER_PAGE_SIZE_64K;
            break;
        case 16 * SIZE_KB:
            baser_page_size = GITS_BASER_PAGE_SIZE_16K;
            break;
        case 4 * SIZE_KB:
        default:
            baser_page_size = GITS_BASER_PAGE_SIZE_4K;
            break;
        }

        baser_page_size >>= GITS_BASER_PAGE_SIZE_SHIFT;

        val |= RT_FIELD_PREP(GITS_BASER_PAGE_SIZE_MASK, baser_page_size);
        its_writeq(its, baser, val);
        tbl->val = its_readq(its, baser);

        if (RT_FIELD_GET(GITS_BASER_PAGE_SIZE_MASK, tbl->val) == baser_page_size)
        {
            break;
        }

        switch (page_size)
        {
        case 64 * SIZE_KB:
            page_size = 16 * SIZE_KB;
            break;
        case 16 * SIZE_KB:
            page_size = 4 * SIZE_KB;
            break;
        case 4 * SIZE_KB:
        default:
            return -RT_EINVAL;
        }
    }

    return page_size;
}

static rt_err_t its_table_init(struct gicv3_its *its)
{
    int inited = 0;
    rt_off_t baser;
    rt_bool_t indirect = RT_FALSE;
    rt_size_t pages_nr, alloc_size;
    rt_uint64_t val, type, entry_size, share, cache;
    struct its_table *tbl;

    share = GITS_BASER_InnerShareable;
    cache = GITS_BASER_RaWaWb;

    for (int i = 0; i < RT_ARRAY_SIZE(its->tbls); ++i)
    {
        tbl = &its->tbls[i];

        val = its_readq(its, GITS_BASERn(i));
        type = GITS_BASER_TYPE(val);

        if (type != GITS_BASER_TYPE_DEVICE &&
            type != GITS_BASER_TYPE_COLLECTION)
        {
            continue;
        }

        tbl->page_size = its_baser_page_size(its, tbl);

        if (tbl->page_size < 0)
        {
            continue;
        }

        baser = GITS_BASERn((int)(tbl - its->tbls));
        entry_size = GITS_BASER_ENTRY_SIZE(val);

        if (type == GITS_BASER_TYPE_DEVICE)
        {
            tbl->size_bits = its_device_id_bits(its);
            LOG_D("Device Max IDs = %lu", 1UL << tbl->size_bits);

            /* For MSI-X */
            tbl->itt_entries = 2048;
            while (MAX_HANDLERS / tbl->itt_entries < (1 << tbl->size_bits) &&
                tbl->itt_entries > 32)
            {
                tbl->itt_entries >>= 1;
            }
        }

        its_writeq(its, baser, tbl->val | GITS_BASER_INDIRECT);
        tbl->val = its_readq(its, baser);

        indirect = !!(tbl->val & GITS_BASER_INDIRECT);
        if (indirect && type == GITS_BASER_TYPE_DEVICE)
        {
            /* The size of the level 2 table is equal to ITS page size */
            tbl->lvl2_bits = tbl->size_bits - rt_ilog2(tbl->page_size / (int)entry_size);

            /* Get level 1 entries count */
            alloc_size = (1 << tbl->size_bits) / (tbl->page_size / entry_size);
            alloc_size *= GITS_LVL1_ENTRY_SIZE;
        }
        else
        {
            alloc_size = (1 << tbl->size_bits) * entry_size;
            indirect = RT_FALSE;
        }

        tbl->base = rt_malloc_align(alloc_size, tbl->page_size);
        pages_nr = alloc_size / tbl->page_size;

        if (!tbl->base)
        {
            return -RT_ENOMEM;
        }

        if (its->flags & ITS_FLAGS_WORKAROUND_CAVIUM_22375)
        {
            cache = GITS_BASER_nCnB;
        }

        if (its->flags & ITS_FLAGS_FORCE_NON_SHAREABLE)
        {
            cache = GITS_BASER_nC;
            share = 0;
        }

        val = ((rt_ubase_t)rt_kmem_v2p(tbl->base) |
                (type << GITS_BASER_TYPE_SHIFT) |
                ((entry_size - 1) << GITS_BASER_ENTRY_SIZE_SHIFT) |
                (pages_nr << GITS_BASER_PAGES_SHIFT) |
                cache | share | GITS_BASER_VALID);
        val |= indirect ? GITS_BASER_INDIRECT : 0;

        switch (tbl->page_size)
        {
        case 4 * SIZE_KB:
            val |= GITS_BASER_PAGE_SIZE_4K;
            break;
        case 16 * SIZE_KB:
            val |= GITS_BASER_PAGE_SIZE_16K;
            break;
        case 64 * SIZE_KB:
            val |= GITS_BASER_PAGE_SIZE_64K;
            break;
        }

        its_writeq(its, baser, val);
        tbl->val = its_readq(its, baser);

        rt_memset(tbl->base, 0, alloc_size);
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, tbl->base, alloc_size);

        cache = tbl->val & GITS_BASER_INNER_MASK_ALL;
        share = tbl->val & GITS_BASER_SHARE_MASK_ALL;

        ++inited;
    }

    return inited == 2 ? RT_EOK : -RT_ENOSYS;
}

static rt_err_t its_cmd_queue_init(struct gicv3_its *its)
{
    void *cmd_phy_base;
    rt_uint64_t baser, tmp;

    its->cmd_base = rt_malloc_align(ITS_CMD_QUEUE_SIZE, ITS_CMD_QUEUE_ALIGN);

    if (!its->cmd_base)
    {
        return -RT_ENOMEM;
    }

    its->cmd_idx = 0;
    rt_memset(its->cmd_base, 0, ITS_CMD_QUEUE_SIZE);

    cmd_phy_base = rt_kmem_v2p(its->cmd_base);

    baser = GITS_CBASER_VALID | GITS_CBASER_RaWaWb | GITS_CBASER_InnerShareable | \
            ((rt_uint64_t)cmd_phy_base) | (ITS_CMD_QUEUE_SIZE / (4 * SIZE_KB) - 1);

    its_writeq(its, GITS_CBASER, baser);
    tmp = its_readq(its, GITS_CBASER);

    if (its->flags & ITS_FLAGS_FORCE_NON_SHAREABLE)
    {
        tmp &= ~GITS_CBASER_SHARE_MASK_ALL;
    }

    if ((tmp ^ baser) & GITS_CBASER_SHARE_MASK_ALL)
    {
        if (!(tmp & GITS_CBASER_SHARE_MASK_ALL))
        {
            /* The HW reports non-shareable, we must remove the cacheability attributes as well */
            baser &= ~(GITS_CBASER_SHARE_MASK_ALL | GITS_CBASER_INNER_MASK_ALL);
            baser |= GITS_CBASER_nC;

            its_writeq(its, GITS_CBASER, baser);
        }

        LOG_I("Using cache flushing for CMD queue");
        its->flags |= ITS_FLAGS_CMDQ_NEEDS_FLUSHING;

        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, its->cmd_base, ITS_CMD_QUEUE_SIZE);
    }

    /* Get the next command from the start of the buffer */
    its_writeq(its, GITS_CWRITER, 0);

    return RT_EOK;
}

static rt_err_t its_lpi_table_init(struct gicv3 *gic)
{
    rt_size_t lpi_table_size, lpi_pending_table_size;
    rt_uint32_t numlpis = 1UL << GICD_TYPER_NUM_LPIS(gic->gicd_typer);

    if (HWREG32(gicr_rd_base_percpu(gic) + GICR_CTLR) & GICR_CTLR_ENABLE_LPIS)
    {
        gic->redist_flags |= RDIST_FLAGS_RD_TABLES_PREALLOCATED;
        gic->redist_flags |= RDIST_FLAGS_PROPBASE_NEEDS_FLUSHING;

        LOG_I("Using preallocated redistributor tables");
    }

    lpi_id_bits = GICD_TYPER_ID_BITS(gic->gicd_typer);

    if (gic->redist_flags & RDIST_FLAGS_RD_TABLES_PREALLOCATED)
    {
        rt_uint64_t val = HWREG64(gicr_rd_base_percpu(gic) + GICR_PROPBASER);
        lpi_id_bits = rt_min_t(rt_uint32_t, lpi_id_bits, (val & GICR_PROPBASER_IDBITS_MASK) + 1);
    }

    lpi_nr = rt_min_t(rt_size_t, (1UL << lpi_id_bits) - 8192, gic->lpi_nr);
    lpi_id_bits = __rt_clz(lpi_nr + 8192);

    if (numlpis > 2 && numlpis > lpi_nr)
    {
        lpi_nr = numlpis;
        LOG_W("Using hypervisor restricted LPI range [%u]", lpi_nr);
    }

    gic->lpi_nr = lpi_nr;

    /* LPI Configuration table entry is 1 byte, Pending table bytes is N / 8. */
    lpi_table_size = RT_GENMASK(lpi_id_bits, 0);
    lpi_pending_table_size = lpi_table_size / 8;

    lpi_table = rt_malloc_align(lpi_table_size, ITS_LPI_CONFIG_TABLE_ALIGN);
    lpi_pending_table = rt_malloc_align(lpi_pending_table_size, ITS_LPI_PENDING_TABLE_ALIGN);
    lpis_vectors = rt_calloc(1, RT_BITMAP_LEN(lpi_nr) * sizeof(rt_bitmap_t));

    if (!lpi_table || !lpi_pending_table || !lpis_vectors)
    {
        if (lpi_table)
        {
            rt_free_align(lpi_table);
        }
        if (lpi_pending_table)
        {
            rt_free_align(lpi_pending_table);
        }
        if (lpis_vectors)
        {
            rt_free_align(lpis_vectors);
        }

        lpi_table = RT_NULL;
        lpi_pending_table = RT_NULL;
        lpis_vectors = RT_NULL;

        return -RT_ENOMEM;
    }

    /* Set the default configuration */
    rt_memset(lpi_table, ITS_LPI_CONFIG_PROP_DEFAULT_PRIO | GITS_LPI_CFG_GROUP1, lpi_table_size);
    /*
     * We should make a full mask size with lpi_id_bits,
     * otherwise 'undefined' LPI will occur.
     */
    rt_memset(lpi_pending_table, 0, lpi_pending_table_size);

    /* Flush the table to memory */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, lpi_table, lpi_table_size);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, lpi_pending_table, lpi_pending_table_size);

    LOG_D("ITS: Allocator initialized for %u LPIs", lpi_nr);

    return RT_EOK;
}

static void its_init_fail(struct gicv3_its *its)
{
    if (its->base)
    {
        rt_iounmap(its->base);
    }

    if (its->cmd_base)
    {
        rt_free_align(its->cmd_base);
    }

    for (int i = 0; i < RT_ARRAY_SIZE(its->tbls); ++i)
    {
        struct its_table *tbl = &its->tbls[i];

        if (tbl->base)
        {
            rt_free_align(tbl->base);
        }
    }

    rt_list_remove(&its->list);
    rt_free(its);
}

static rt_err_t its_quirk_cavium_22375(void *data)
{
    struct gicv3_its *its = data;

    its->flags |= ITS_FLAGS_WORKAROUND_CAVIUM_22375;

    return RT_EOK;
}

static rt_err_t its_enable_rockchip(void *data)
{
    struct gicv3_its *its = data;
    struct gicv3 *gic = its->gic;

    if (!rt_ofw_machine_is_compatible("rockchip,rk3566") &&
        !rt_ofw_machine_is_compatible("rockchip,rk3567") &&
        !rt_ofw_machine_is_compatible("rockchip,rk3568") &&
        !rt_ofw_machine_is_compatible("rockchip,rk3588") &&
        !rt_ofw_machine_is_compatible("rockchip,rk3588s"))
    {
        return -RT_EINVAL;
    }

    its->flags |= ITS_FLAGS_FORCE_NON_SHAREABLE;
    gic->redist_flags |= RDIST_FLAGS_FORCE_NON_SHAREABLE;

    return RT_EOK;
}

static rt_err_t its_set_non_coherent(void *data)
{
    struct gicv3_its *its = data;

    if (!rt_ofw_prop_read_bool(its->np, "dma-noncoherent"))
    {
        return -RT_EINVAL;
    }

    its->flags |= ITS_FLAGS_FORCE_NON_SHAREABLE;

    return RT_EOK;
}

static const struct gic_quirk _its_quirks[] =
{
    {
        .desc       = "ITS: Cavium ThunderX errata: 22375, 24313",
        .iidr       = 0xa100034c,
        .iidr_mask  = 0xffff0fff,
        .init       = its_quirk_cavium_22375,
    },
    {
        .desc       = "ITS: Rockchip erratum RK3566 ~ RK3588",
        .iidr       = 0x0201743b,
        .iidr_mask  = 0xffffffff,
        .init       = its_enable_rockchip,
    },
    {
        .desc       = "ITS: non-coherent attribute",
        .compatible = "arm,gic-v3-its",
        .init       = its_set_non_coherent,
    },
    { /* sentinel */ }
};

static const struct rt_ofw_node_id gicv3_its_ofw_match[] =
{
    { .compatible = "arm,gic-v3-its" },
    { /* sentinel */ }
};

rt_err_t gicv3_its_ofw_probe(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err = -RT_EEMPTY;
    struct rt_ofw_node *its_np;
    struct gicv3_its *its, *its_next;

    rt_ofw_foreach_available_child_node(np, its_np)
    {
        if (!rt_ofw_node_match(its_np, gicv3_its_ofw_match))
        {
            continue;
        }

        if (!rt_ofw_prop_read_bool(its_np, "msi-controller"))
        {
            continue;
        }

        if (!(its = rt_calloc(1, sizeof(struct gicv3_its))))
        {
            rt_ofw_node_put(its_np);

            err = -RT_ENOMEM;
            goto _free_all;
        }

        its->base = rt_ofw_iomap(its_np, 0);

        if (!its->base)
        {
            LOG_E("%s: IO map failed", rt_ofw_node_full_name(its_np));
            its_init_fail(its);
            continue;
        }

        /*
         * Make sure ALL the ITS are reset before we probe any,
         * as they may be sharing memory
         */
        for (int i = 0; i < GITS_BASER_NR_REGS; ++i)
        {
            its_writeq(its, GITS_BASER + (i << 3), 0);
        }

        its->np = its_np;
        rt_list_init(&its->list);
        rt_list_insert_before(&its_nodes, &its->list);
    }

    if (!rt_list_isempty(&its_nodes))
    {
        if ((err = its_lpi_table_init(rt_ofw_data(np))))
        {
            goto _free_all;
        }
    }

    rt_list_for_each_entry_safe(its, its_next, &its_nodes, list)
    {
        rt_uint32_t ctlr;

        its->base_phy = rt_kmem_v2p(its->base);
        its->gic = rt_ofw_data(np);

        gic_common_init_quirk_hw(HWREG32(its->base + GITS_IIDR), _its_quirks, its);
        gic_common_init_quirk_ofw(its->np, _its_quirks, its);

        if ((err = its_cmd_queue_init(its)))
        {
            goto _fail;
        }
        rt_spin_lock_init(&its->cmd_lock);

        if ((err = its_table_init(its)))
        {
            goto _fail;
        }

        for (int i = 0; i < RT_CPUS_NR; ++i)
        {
            its->collections[i].target_address = ~0ULL;
        }

        ctlr = its_readl(its, GITS_CTLR);
        ctlr |= GITS_CTLR_ENABLE;
        its_writel(its, GITS_CTLR, ctlr);

        its->parent.priv_data = its;
        its->parent.ops = &gicv3_its_ops;

        rt_pic_linear_irq(&its->parent, its->gic->lpi_nr);
        rt_pic_user_extends(&its->parent);

        its_np = its->np;
        rt_ofw_data(its_np) = &its->parent;
        rt_ofw_node_set_flag(its_np, RT_OFW_F_READLY);

        continue;

    _fail:
        its_init_fail(its);

        if (err == -RT_ENOMEM)
        {
            break;
        }
    }

    if (rt_list_isempty(&its_nodes) && lpis_vectors)
    {
        rt_free(lpis_vectors);
        rt_free_align(lpi_table);
        rt_free_align(lpi_pending_table);
        lpis_vectors = RT_NULL;
    }

    return err;

_free_all:
    rt_list_for_each_entry_safe(its, its_next, &its_nodes, list)
    {
        rt_free(its);
        rt_list_remove(&its->list);
    }

    return err;
}
