/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.nvme"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_dm_ida nvme_controller_ida = RT_DM_IDA_INIT(CUSTOM);
static struct rt_dm_ida nvme_ida = RT_DM_IDA_INIT(NVME);

static struct rt_spinlock nvme_lock = {};
static rt_list_t nvme_nodes = RT_LIST_OBJECT_INIT(nvme_nodes);

rt_inline rt_uint32_t nvme_readl(struct rt_nvme_controller *nvme, int offset)
{
    return HWREG32(nvme->regs + offset);
}

rt_inline void nvme_writel(struct rt_nvme_controller *nvme, int offset, rt_uint32_t value)
{
    HWREG32(nvme->regs + offset) = value;
}

rt_inline rt_uint64_t nvme_readq(struct rt_nvme_controller *nvme, int offset)
{
    rt_uint32_t lo32, hi32;

    lo32 = HWREG32(nvme->regs + offset);
    hi32 = HWREG32(nvme->regs + offset + 4);

    return ((rt_uint64_t)hi32 << 32) + lo32;
}

rt_inline void nvme_writeq(struct rt_nvme_controller *nvme, int offset, rt_uint64_t value)
{
    nvme_writel(nvme, offset, (rt_uint32_t)(value & 0xffffffff));
    nvme_writel(nvme, offset + 4, (rt_uint32_t)(value >> 32));
}

static rt_err_t nvme_poll_csts(struct rt_nvme_controller *nvme,
        rt_uint32_t mask, rt_uint32_t value)
{
    rt_tick_t timeout;

    timeout = rt_tick_from_millisecond(RT_NVME_CAP_TIMEOUT(nvme->cap) * 500);
    timeout += rt_tick_get();

    do {
        if ((nvme_readl(nvme, RT_NVME_REG_CSTS) & mask) == value)
        {
            return RT_EOK;
        }

        rt_hw_cpu_relax();
    } while (rt_tick_get() < timeout);

    return -RT_ETIMEOUT;
}

static rt_err_t nvme_enable_ctrl(struct rt_nvme_controller *nvme)
{
    nvme->ctrl_config &= ~RT_NVME_CC_SHN_MASK;
    nvme->ctrl_config |= RT_NVME_CC_ENABLE;
    nvme_writel(nvme, RT_NVME_REG_CC, nvme->ctrl_config);

    return nvme_poll_csts(nvme, RT_NVME_CSTS_RDY, RT_NVME_CSTS_RDY);
}

static rt_err_t nvme_disable_ctrl(struct rt_nvme_controller *nvme)
{
    nvme->ctrl_config &= ~RT_NVME_CC_SHN_MASK;
    nvme->ctrl_config &= ~RT_NVME_CC_ENABLE;
    nvme_writel(nvme, RT_NVME_REG_CC, nvme->ctrl_config);

    return nvme_poll_csts(nvme, RT_NVME_CSTS_RDY, 0);
}

static rt_err_t nvme_shutdown_ctrl(struct rt_nvme_controller *nvme)
{
    nvme->ctrl_config &= ~RT_NVME_CC_SHN_MASK;
    nvme->ctrl_config |= RT_NVME_CC_SHN_NORMAL;
    nvme_writel(nvme, RT_NVME_REG_CC, nvme->ctrl_config);

    return nvme_poll_csts(nvme, RT_NVME_CSTS_SHST_MASK, RT_NVME_CSTS_SHST_CMPLT);
}

rt_inline rt_le16_t nvme_next_cmdid(struct rt_nvme_controller *nvme)
{
    return rt_cpu_to_le16((rt_uint16_t)rt_atomic_add(&nvme->cmdid, 1));
}

static rt_err_t nvme_submit_cmd(struct rt_nvme_queue *queue,
        struct rt_nvme_command *cmd)
{
    rt_ubase_t level;
    rt_err_t err = RT_EOK;
    rt_uint16_t tail, head;
    struct rt_nvme_controller *nvme = queue->nvme;

_retry:
    level = rt_spin_lock_irqsave(&queue->lock);

    tail = queue->sq_tail;
    head = queue->cq_head;

    if (tail + 1 == head)
    {
        /* IO queue is full, waiting for the last IO command to complete. */
        rt_spin_unlock_irqrestore(&queue->lock, level);

        rt_thread_yield();

        goto _retry;
    }

    cmd->common.cmdid = nvme_next_cmdid(nvme);
    rt_memcpy(&queue->sq_cmds[tail], cmd, sizeof(*cmd));

    if (nvme->ops->submit_cmd)
    {
        if ((err = nvme->ops->submit_cmd(queue, cmd)))
        {
            return err;
        }
    }

    if (++tail == queue->depth)
    {
        tail = 0;
    }
    HWREG32(queue->doorbell) = tail;
    queue->sq_tail = tail;

    queue->cmd = cmd;
    queue->err = RT_EOK;

    rt_spin_unlock_irqrestore(&queue->lock, level);

    err = rt_completion_wait(&queue->done,
            rt_tick_from_millisecond(queue->qid != 0 ? RT_WAITING_FOREVER : 60));

    return err ? : queue->err;
}

static rt_err_t nvme_set_features_simple(struct rt_nvme_controller *nvme,
        rt_uint32_t fid, rt_uint32_t dword11)
{
    struct rt_nvme_command cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.features.opcode = RT_NVME_ADMIN_OPCODE_SET_FEATURES;
    cmd.features.fid = rt_cpu_to_le32(fid);
    cmd.features.dword11 = rt_cpu_to_le32(dword11);

    return nvme_submit_cmd(&nvme->admin_queue, &cmd);
}

static rt_err_t nvme_submit_io_cmd(struct rt_nvme_controller *nvme,
        struct rt_nvme_command *cmd)
{
    rt_uint16_t qid;

    qid = rt_atomic_add(&nvme->ioqid[rt_hw_cpu_id()], RT_CPUS_NR);
    qid %= nvme->io_queue_max;

    return nvme_submit_cmd(&nvme->io_queues[qid], cmd);
}

/*
 * PRP Mode:
 *
 * |63                                   n+1|n                0|
 * +----------------------------------------+----------+---+---+
 * |            Page Base Address           |  Offset  | 0 | 0 |
 * +----------------------------------------+----------+---+---+
 *                                                             |
 *                                                             v
 *                                            Host Physical Pages
 *                                       +----------------------------+
 * +--------------+----------+           |           Page k           |
 * |  PRP Entry1  |  Offset  +---------->+----------------------------+
 * +--------------+----------+           |         Page k + 1         |
 *                                       +----------------------------+
 *                                                     ...
 *                                       +----------------------------+
 * +--------------+----------+           |         Page k + m         |
 * |  PRP Entry2  |    0     +---------->+----------------------------+
 * +--------------+----------+           |       Page k + m + 1       |
 *                                       +----------------------------+
 * PRP List (In PRP Entry2):
 *
 * |63                                   n+1|n                0|
 * +----------------------------------------+------------------+
 * |           Page Base Address k          |        0h        |
 * +----------------------------------------+------------------+
 * |        Page Base Address k + 1         |        0h        |
 * +----------------------------------------+------------------+
 * |                            ...                            |
 * +----------------------------------------+------------------+
 * |        Page Base Address k + m         |        0h        |
 * +----------------------------------------+------------------+
 * |       Page Base Address k + m + 1      |        0h        |
 * +----------------------------------------+------------------+
 *
 * SGL Mode:
 *                                           +----- Non-transport
 * LBA                                      /
 * +---------------+---------------+-------/-------+---------------+
 * |      3KB      |      4KB      |      2KB      |      4KB      |
 * +-------+-------+-------+-------+---------------+--------+------+
 *         |               +-------------------------+      |
 *         |                                         |      |
 *         |                    +--------------------|------+
 *         |                    |                    |
 * +-------v-------+    +-------v-------+    +-------v-------+
 * |  A MEM BLOCK  |    |  B MEM BLOCK  |    |  C MEM BLOCK  |
 * +-------^-------+    +-------^-------+    +-------^-------+
 *         |                    |                    |
 *         +----------------+   |                    |
 *                          |   |                    |
 * Segment(0)               |   |                    |
 * +----------+----------+  |   |                    |
 * | Address: A          +--+   |                    |
 * +----------+----------+      |                    |
 * | Type: 0h | Len: 3KB |      |                    |
 * +----------+----------+      |                    |
 * | Address: Segment(1) +--+   |                    |
 * +----------+----------+  |   |                    |
 * | Type: 2h | Len: 48  |  |   |                    |
 * +----------+----------+  |   |                    |
 *                          |   |                    |
 * +------------------------+   |                    |
 * |                            |                    |
 * v                            |                    |
 * Segment(1)                   |                    |
 * +----------+----------+      |                    |
 * | Address: B          +------+                    |
 * +----------+----------+                           |
 * | Type: 0h | Len: 4KB |                           |
 * +----------+----------+                           |
 * | Address: <NULL>     |                           |
 * +----------+----------+                           |
 * | Type: 1h | Len: 2KB |                           |
 * +----------+----------+                           |
 * | Address: Segment(2) +--+                        |
 * +----------+----------+  |                        |
 * | Type: 0h | Len: 16  |  |                        |
 * +----------+----------+  |                        |
 *                          |                        |
 * +------------------------+                        |
 * |                                                 |
 * v                                                 |
 * Segment(2)                                        |
 * +----------+----------+                           |
 * | Address: C          +---------------------------+
 * +----------+----------+
 * | Type: 0h | Len: 4KB |
 * +----------+----------+
 */

static rt_ssize_t nvme_blk_rw(struct rt_nvme_device *ndev, rt_off_t slba,
        rt_ubase_t buffer_dma, rt_size_t lbas, rt_uint8_t opcode)
{
    rt_err_t err;
    rt_uint16_t max_lbas;
    rt_uint32_t lba_shift;
    rt_size_t tlbas;
    rt_ssize_t data_length;
    struct rt_nvme_command cmd;
    struct rt_nvme_controller *nvme = ndev->ctrl;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.rw.opcode = opcode;
    cmd.rw.flags = nvme->sgl_mode << RT_NVME_CMD_FLAGS_PSDT_SHIFT;
    cmd.rw.nsid = rt_cpu_to_le32(ndev->nsid);

    tlbas = lbas;
    lba_shift = ndev->lba_shift;
    max_lbas = 1 << (nvme->max_transfer_shift - lba_shift);

    if (nvme->sgl_mode)
    {
        while ((rt_ssize_t)lbas > 0)
        {
            if (lbas < max_lbas)
            {
                max_lbas = (rt_uint16_t)lbas;
            }

            data_length = max_lbas << lba_shift;

            cmd.rw.sgl.adddress = rt_cpu_to_le64(buffer_dma);
            cmd.rw.sgl.length = rt_cpu_to_le32(data_length);
            cmd.rw.sgl.sgl_identify = SGL_DESC_TYPE_DATA_BLOCK;
            cmd.rw.slba = rt_cpu_to_le16(slba);
            cmd.rw.length = rt_cpu_to_le16(max_lbas - 1);

            if ((err = nvme_submit_io_cmd(nvme, &cmd)))
            {
                tlbas -= lbas;
                break;
            }

            lbas -= max_lbas;
            slba += max_lbas;
            buffer_dma += data_length;
        }
    }
    else
    {
        void *prp_list = RT_NULL;
        rt_size_t prp_list_size = 0, page_size;

        page_size = nvme->page_size;

        while ((rt_ssize_t)lbas > 0)
        {
            rt_uint64_t prp2_addr, dma_addr;
            rt_ssize_t remain_length, page_offset;

            if (lbas < max_lbas)
            {
                max_lbas = (rt_uint16_t)lbas;
            }

            /*
             * PRP transfer:
             *  1. data_length <= 4KB:
             *      prp1 = buffer_dma
             *      prp2 = 0
             *
             *  2. 4KB < data_length <= 8KB:
             *      prp1 = buffer_dma
             *      prp2 = buffer_dma
             *
             *  3. 8KB < data_length:
             *      prp1 = buffer_dma(0, 4k)
             *      prp2 = buffer_dma(4k, ~)
             */
            dma_addr = buffer_dma;
            page_offset = buffer_dma & (page_size - 1);
            data_length = max_lbas << lba_shift;
            remain_length = data_length - (page_size - page_offset);

            do {
                rt_size_t prps_per_page, prps, pages;
                rt_uint64_t *prp_list_ptr, prp_list_dma;

                if (remain_length <= 0)
                {
                    prp2_addr = 0;
                    break;
                }

                if (remain_length)
                {
                    dma_addr += (page_size - page_offset);
                }

                if (remain_length <= page_size)
                {
                    prp2_addr = dma_addr;
                    break;
                }

                prps_per_page = page_size / sizeof(rt_uint64_t);
                prps = RT_DIV_ROUND_UP(remain_length, page_size);
                pages = RT_DIV_ROUND_UP(prps - 1, prps_per_page - 1);

                if (prps > prp_list_size)
                {
                    if (prp_list)
                    {
                        rt_free_align(prp_list);
                    }

                    prp_list = rt_malloc_align(pages * page_size, page_size);

                    if (!prp_list)
                    {
                        LOG_D("No memory to create a PRP List");
                        /* Ask user to try again */
                        return tlbas - lbas;
                    }

                    prp_list_size = pages * (prps_per_page - 1) + 1;
                }
                prp_list_ptr = prp_list;
                prp_list_dma = (rt_uint64_t)rt_kmem_v2p(prp_list_ptr);

                prp2_addr = prp_list_dma;

                for (int i = 0; prps; --prps, ++i)
                {
                    /* End of the entry, fill the next entry addr if remain */
                    if ((i == (prps_per_page - 1)) && prps > 1)
                    {
                        prp_list_dma += page_size;
                        *prp_list_ptr = rt_cpu_to_le64(prp_list_dma);

                        /* Start to fill the next PRP */
                        i = 0;
                    }

                    *prp_list_ptr = rt_cpu_to_le64(dma_addr);
                    dma_addr += page_size;
                }

                rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, prp_list_ptr, prp_list_size);
            } while (0);

            cmd.rw.prp1 = rt_cpu_to_le64(buffer_dma);
            cmd.rw.prp2 = rt_cpu_to_le64(prp2_addr);
            cmd.rw.slba = rt_cpu_to_le16(slba);
            cmd.rw.length = rt_cpu_to_le16(max_lbas - 1);

            if ((err = nvme_submit_io_cmd(nvme, &cmd)))
            {
                tlbas -= lbas;
                break;
            }

            lbas -= max_lbas;
            slba += max_lbas;
            buffer_dma += data_length;
        }

        if (prp_list)
        {
            rt_free_align(prp_list);
        }
    }

    return tlbas;
}

static rt_ssize_t nvme_blk_read(struct rt_blk_disk *disk, rt_off_t sector,
        void *buffer, rt_size_t sector_count)
{
    rt_ssize_t res;
    rt_uint32_t page_bits;
    rt_size_t buffer_size;
    rt_ubase_t buffer_dma;
    void *temp_buffer = RT_NULL;
    struct rt_nvme_device *ndev = rt_disk_to_nvme_device(disk);
    struct rt_nvme_controller *nvme = ndev->ctrl;

    buffer_size = (1 << ndev->lba_shift) * sector_count;
    buffer_dma = (rt_ubase_t)rt_kmem_v2p(buffer);

    if ((nvme->sgl_mode && (buffer_dma & RT_GENMASK(1, 0))) ||
        (!nvme->sgl_mode && (buffer_dma & ARCH_PAGE_MASK)))
    {
        LOG_D("DMA PRP direct %s buffer MUST 4-bytes or page aligned", "read");

        page_bits = rt_page_bits(buffer_size);
        temp_buffer = rt_pages_alloc(page_bits);

        if (!temp_buffer)
        {
            return -RT_ENOMEM;
        }

        buffer_dma = (rt_ubase_t)rt_kmem_v2p(temp_buffer);
    }

    res = nvme_blk_rw(ndev, sector, buffer_dma, sector_count, RT_NVME_CMD_READ);

    if (res > 0)
    {
        if (res != sector_count)
        {
            /*
             * Don't always aim for optimization, checking for equality
             * is much faster than multiplication calculation.
             */
            buffer_size = res * (1 << ndev->lba_shift);
        }

        if (temp_buffer)
        {
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, temp_buffer, buffer_size);
            rt_memcpy(buffer, temp_buffer, buffer_size);
        }
        else
        {
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, buffer, buffer_size);
        }
    }

    if (temp_buffer)
    {
        rt_pages_free(temp_buffer, page_bits);
    }

    return res;
}

static rt_ssize_t nvme_blk_write(struct rt_blk_disk *disk, rt_off_t sector,
        const void *buffer, rt_size_t sector_count)
{
    rt_ssize_t res;
    rt_uint32_t page_bits;
    rt_size_t buffer_size;
    rt_ubase_t buffer_dma;
    void *temp_buffer = RT_NULL;
    struct rt_nvme_device *ndev = rt_disk_to_nvme_device(disk);
    struct rt_nvme_controller *nvme = ndev->ctrl;

    buffer_size = (1 << ndev->lba_shift) * sector_count;
    buffer_dma = (rt_ubase_t)rt_kmem_v2p((void *)buffer);

    if ((nvme->sgl_mode && (buffer_dma & RT_GENMASK(1, 0))) ||
        (!nvme->sgl_mode && (buffer_dma & ARCH_PAGE_MASK)))
    {
        LOG_D("DMA PRP direct %s buffer MUST 4-bytes or page aligned", "write");

        page_bits = rt_page_bits(buffer_size);
        temp_buffer = rt_pages_alloc(page_bits);

        if (!temp_buffer)
        {
            return -RT_ENOMEM;
        }

        buffer_dma = (rt_ubase_t)rt_kmem_v2p(temp_buffer);

        rt_memcpy(temp_buffer, buffer, buffer_size);
        buffer = temp_buffer;
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)buffer, buffer_size);

    res = nvme_blk_rw(ndev, sector, buffer_dma, sector_count, RT_NVME_CMD_WRITE);

    if (temp_buffer)
    {
        rt_pages_free(temp_buffer, page_bits);
    }

    return res;
}

static rt_err_t nvme_blk_getgeome(struct rt_blk_disk *disk,
        struct rt_device_blk_geometry *geometry)
{
    struct rt_nvme_device *ndev = rt_disk_to_nvme_device(disk);

    geometry->bytes_per_sector = 1 << ndev->lba_shift;
    geometry->block_size = 1 << ndev->lba_shift;
    geometry->sector_count = rt_le64_to_cpu(ndev->id.nsze);

    return RT_EOK;
}

static rt_err_t nvme_blk_sync(struct rt_blk_disk *disk)
{
    struct rt_nvme_command cmd;
    struct rt_nvme_device *ndev = rt_disk_to_nvme_device(disk);

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.common.opcode = RT_NVME_CMD_FLUSH;
    cmd.common.nsid = rt_cpu_to_le32(ndev->nsid);

    return nvme_submit_io_cmd(ndev->ctrl, &cmd);
}

static rt_err_t nvme_blk_erase(struct rt_blk_disk *disk)
{
    rt_err_t err = RT_EOK;
    rt_ssize_t slba, lbas, max_lbas;
    struct rt_nvme_command cmd;
    struct rt_nvme_device *ndev = rt_disk_to_nvme_device(disk);
    struct rt_nvme_controller *nvme = ndev->ctrl;

    if (!nvme->write_zeroes)
    {
        return -RT_ENOSYS;
    }

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.write_zeroes.opcode = RT_NVME_CMD_WRITE_ZEROES;
    cmd.write_zeroes.nsid = rt_cpu_to_le32(ndev->nsid);

    slba = 0;
    lbas = rt_le64_to_cpu(ndev->id.nsze);
    max_lbas = 1 << (nvme->max_transfer_shift - ndev->lba_shift);

    while ((rt_ssize_t)lbas > 0)
    {
        if (lbas < max_lbas)
        {
            max_lbas = (rt_uint16_t)lbas;
        }

        cmd.write_zeroes.slba = rt_cpu_to_le16(slba);
        cmd.write_zeroes.length = rt_cpu_to_le16(max_lbas - 1);

        if ((err = nvme_submit_io_cmd(nvme, &cmd)))
        {
            break;
        }

        lbas -= max_lbas;
        slba += max_lbas;
    }

    return err;
}

static rt_err_t nvme_blk_autorefresh(struct rt_blk_disk *disk, rt_bool_t is_auto)
{
    struct rt_nvme_device *ndev = rt_disk_to_nvme_device(disk);
    struct rt_nvme_controller *nvme = ndev->ctrl;

    if (nvme->volatile_write_cache & RT_NVME_CTRL_VWC_PRESENT)
    {
        return nvme_set_features_simple(nvme, RT_NVME_FEAT_VOLATILE_WC, !!is_auto);
    }
    else if (!is_auto)
    {
        return RT_EOK;
    }

    return -RT_ENOSYS;
}

static const struct rt_blk_disk_ops nvme_blk_ops =
{
    .read = nvme_blk_read,
    .write = nvme_blk_write,
    .getgeome = nvme_blk_getgeome,
    .sync = nvme_blk_sync,
    .erase = nvme_blk_erase,
    .autorefresh = nvme_blk_autorefresh,
};

static void nvme_queue_isr(int irqno, void *param)
{
    rt_ubase_t level;
    rt_uint16_t head, phase, status;
    struct rt_nvme_queue *queue = param;
    struct rt_nvme_controller *nvme = queue->nvme;

    level = rt_spin_lock_irqsave(&queue->lock);

    head = queue->cq_head;
    phase = queue->cq_phase;
    status = HWREG16(&queue->cq_entry[head].status);
    status = rt_le16_to_cpu(status);

    if ((status & 0x01) == phase)
    {
        if ((status >> 1))
        {
            queue->err = -RT_EIO;
            goto _end_cmd;
        }

        if (nvme->ops->complete_cmd)
        {
            nvme->ops->complete_cmd(queue, queue->cmd);
        }

    _end_cmd:
        if (++head == queue->depth)
        {
            head = 0;
            phase = !phase;
        }

        HWREG32(queue->doorbell + nvme->doorbell_stride) = head;
        queue->cq_head = head;
        queue->cq_phase = phase;

        rt_completion_done(&queue->done);
    }

    rt_spin_unlock_irqrestore(&queue->lock, level);
}

static rt_err_t nvme_identify(struct rt_nvme_controller *nvme,
        rt_uint32_t nsid, rt_uint32_t cns, void *data)
{
    rt_err_t err;
    rt_uint32_t page_size = nvme->page_size;
    rt_ubase_t data_phy = (rt_ubase_t)rt_kmem_v2p(data);
    int offset = data_phy & (page_size - 1);
    struct rt_nvme_command cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.identify.opcode = RT_NVME_ADMIN_OPCODE_IDENTIFY;
    cmd.identify.nsid = rt_cpu_to_le32(nsid);
    cmd.identify.prp1 = rt_cpu_to_le64(data_phy);

    if (sizeof(struct rt_nvme_id_ctrl) <= page_size - offset)
    {
        cmd.identify.prp2 = 0;
    }
    else
    {
        data_phy += (page_size - offset);
        cmd.identify.prp2 = rt_cpu_to_le64(data_phy);
    }
    cmd.identify.cns = rt_cpu_to_le32(cns);

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, data, sizeof(struct rt_nvme_id_ctrl));

    if (!(err = nvme_submit_cmd(&nvme->admin_queue, &cmd)))
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, data, sizeof(struct rt_nvme_id_ctrl));
    }

    return err;
}

static rt_err_t nvme_attach_queue(struct rt_nvme_queue *queue, rt_uint8_t opcode)
{
    struct rt_nvme_command cmd;
    struct rt_nvme_controller *nvme = queue->nvme;
    rt_uint16_t flags = RT_NVME_QUEUE_PHYS_CONTIG;

    rt_memset(&cmd, 0, sizeof(cmd));

    if (opcode == RT_NVME_ADMIN_OPCODE_CREATE_CQ)
    {
        cmd.create_cq.opcode = opcode;
        cmd.create_cq.prp1 = rt_cpu_to_le64(queue->cq_entry_phy);
        cmd.create_cq.cqid = rt_cpu_to_le16(queue->qid);
        cmd.create_cq.qsize = rt_cpu_to_le16(queue->depth - 1);
        cmd.create_cq.cq_flags = rt_cpu_to_le16(flags | RT_NVME_CQ_IRQ_ENABLED);
        cmd.create_cq.irq_vector = rt_cpu_to_le16(nvme->irqs_nr > 1 ? queue->qid : 0);
    }
    else if (opcode == RT_NVME_ADMIN_OPCODE_CREATE_SQ)
    {
        cmd.create_sq.opcode = opcode;
        cmd.create_sq.prp1 = rt_cpu_to_le64(queue->sq_cmds_phy);
        cmd.create_sq.sqid = rt_cpu_to_le16(queue->qid);
        cmd.create_sq.qsize = rt_cpu_to_le16(queue->depth - 1);
        cmd.create_sq.sq_flags = rt_cpu_to_le16(flags | RT_NVME_SQ_PRIO_MEDIUM);
        cmd.create_sq.cqid = rt_cpu_to_le16(queue->qid);
    }
    else
    {
        LOG_E("What the fuck opcode = %x", opcode);
        RT_ASSERT(0);
    }

    return nvme_submit_cmd(&nvme->admin_queue, &cmd);
}

rt_inline rt_err_t nvme_attach_queue_sq(struct rt_nvme_queue *queue)
{
    return nvme_attach_queue(queue, RT_NVME_ADMIN_OPCODE_CREATE_SQ);
}

rt_inline rt_err_t nvme_attach_queue_cq(struct rt_nvme_queue *queue)
{
    return nvme_attach_queue(queue, RT_NVME_ADMIN_OPCODE_CREATE_CQ);
}

static rt_err_t nvme_detach_queue(struct rt_nvme_queue *queue,
        rt_uint8_t opcode)
{
    struct rt_nvme_command cmd;
    struct rt_nvme_controller *nvme = queue->nvme;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.delete_queue.opcode = opcode;
    cmd.delete_queue.qid = rt_cpu_to_le16(queue->qid);

    return nvme_submit_cmd(&nvme->admin_queue, &cmd);
}

rt_inline rt_ubase_t nvme_queue_dma_flags(void)
{
    return RT_DMA_F_NOCACHE | RT_DMA_F_LINEAR;
}

static void nvme_free_queue(struct rt_nvme_queue *queue)
{
    rt_ubase_t dma_flags;
    struct rt_nvme_controller *nvme = queue->nvme;

    if (nvme->ops->cleanup_queue)
    {
        rt_err_t err;

        if (!(err = nvme->ops->cleanup_queue(queue)))
        {
            LOG_W("Cleanup[%s] queue error = %s", nvme->ops->name, rt_strerror(err));
        }
    }

    dma_flags = nvme_queue_dma_flags();

    if (queue->sq_cmds)
    {
        rt_dma_free(nvme->dev, sizeof(*queue->sq_cmds) * queue->depth,
                queue->sq_cmds, queue->sq_cmds_phy, dma_flags);
    }

    if (queue->cq_entry)
    {
        rt_dma_free(nvme->dev, sizeof(*queue->cq_entry) * queue->depth,
                queue->cq_entry, queue->cq_entry_phy, dma_flags);
    }
}

static struct rt_nvme_queue *nvme_alloc_queue(struct rt_nvme_controller *nvme,
        int qid, int depth)
{
    rt_err_t err;
    rt_ubase_t dma_flags;
    struct rt_nvme_queue *queue = &nvme->queue[qid];

    rt_memset(queue, 0, sizeof(*queue));

    queue->nvme = nvme;
    queue->doorbell = &nvme->doorbell_tbl[qid * 2 * nvme->doorbell_stride];
    queue->qid = qid;
    queue->depth = depth;
    queue->cq_head = 0;
    queue->cq_phase = 1;
    rt_completion_init(&queue->done);
    rt_spin_lock_init(&queue->lock);

    dma_flags = nvme_queue_dma_flags();

    /* struct rt_nvme_command */
    queue->sq_cmds = rt_dma_alloc(nvme->dev,
            sizeof(*queue->sq_cmds) * depth, &queue->sq_cmds_phy, dma_flags);

    if (!queue->sq_cmds)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    /* struct rt_nvme_completion */
    queue->cq_entry = rt_dma_alloc(nvme->dev,
            sizeof(*queue->cq_entry) * depth, &queue->cq_entry_phy, dma_flags);

    if (!queue->cq_entry)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    rt_memset(queue->sq_cmds, 0, sizeof(struct rt_nvme_command) * depth);
    rt_memset(queue->cq_entry, 0, sizeof(struct rt_nvme_completion) * depth);

    if (nvme->ops->setup_queue)
    {
        if (!(err = nvme->ops->setup_queue(queue)))
        {
            LOG_E("Setup[%s] queue error = %s", nvme->ops->name, rt_strerror(err));

            goto _fail;
        }
    }

    return queue;

_fail:
    nvme_free_queue(queue);

    return rt_err_ptr(err);
}

static rt_err_t nvme_configure_admin_queue(struct rt_nvme_controller *nvme)
{
    rt_err_t err;
    int irq;
    char name[RT_NAME_MAX];
    rt_uint32_t aqa;
    rt_uint32_t page_shift = ARCH_PAGE_SHIFT;
    rt_uint32_t page_min = RT_NVME_CAP_MPSMIN(nvme->cap) + 12;
    rt_uint32_t page_max = RT_NVME_CAP_MPSMAX(nvme->cap) + 12;
    struct rt_nvme_queue *admin_queue;

    if (page_shift < page_min)
    {
        LOG_E("Device %s page size (%u) %s than host (%u)",
                "minimum", 1 << page_min, "larger", 1 << page_shift);
        return -RT_EINVAL;
    }

    if (page_shift > page_max)
    {
        LOG_W("Device %s page size (%u) %s than host (%u)",
                "maximum", 1 << page_max, "smaller", 1 << page_shift);
        page_shift = page_max;
    }

    if ((err = nvme_disable_ctrl(nvme)))
    {
        return err;
    }

    admin_queue = nvme_alloc_queue(nvme, 0, RT_NVME_AQ_DEPTH);

    if (rt_is_err(admin_queue))
    {
        return rt_ptr_err(admin_queue);
    }

    aqa = admin_queue->depth - 1;
    aqa |= aqa << 16;

    nvme->page_shift = page_shift;
    nvme->page_size = 1U << page_shift;

    nvme->ctrl_config = RT_NVME_CC_CSS_NVM;
    nvme->ctrl_config |= (page_shift - 12) << RT_NVME_CC_MPS_SHIFT;
    nvme->ctrl_config |= RT_NVME_CC_ARB_RR | RT_NVME_CC_SHN_NONE;
    nvme->ctrl_config |= RT_NVME_CC_IOSQES | RT_NVME_CC_IOCQES;

    nvme_writel(nvme, RT_NVME_REG_AQA, aqa);
    nvme_writeq(nvme, RT_NVME_REG_ASQ, admin_queue->sq_cmds_phy);
    nvme_writeq(nvme, RT_NVME_REG_ACQ, admin_queue->cq_entry_phy);

    if ((err = nvme_enable_ctrl(nvme)))
    {
        nvme_free_queue(admin_queue);

        return err;
    }

    irq = nvme->irqs[0];

    rt_snprintf(name, RT_NAME_MAX, "%s-admin-queue", nvme->name);

    rt_hw_interrupt_install(irq, nvme_queue_isr, &nvme->admin_queue, name);
    rt_hw_interrupt_umask(irq);

    return RT_EOK;
}

static rt_err_t nvme_setup_io_queues(struct rt_nvme_controller *nvme)
{
    rt_err_t err;
    rt_uint32_t value;
    int irq, cpuid = 0;
    char name[RT_NAME_MAX];
    rt_bool_t affinity_fixup = RT_FALSE;
    RT_IRQ_AFFINITY_DECLARE(affinity) = { 0 };
    struct rt_nvme_queue *queue;

    nvme->io_queue_max = nvme->irqs_nr > 1 ? nvme->irqs_nr - 1 : 1;
    value = (nvme->io_queue_max - 1) | ((nvme->io_queue_max - 1) << 16);

    if ((err = nvme_set_features_simple(nvme, RT_NVME_FEAT_NUM_QUEUES, value)))
    {
        return err;
    }

    for (int i = 0, q_idx = 1; i < nvme->io_queue_max; ++i, ++q_idx)
    {
        queue = nvme_alloc_queue(nvme, q_idx, nvme->queue_depth);

        if (!queue)
        {
            return -RT_ENOMEM;
        }

        if ((err = nvme_attach_queue_cq(queue)) ||
            (err = nvme_attach_queue_sq(queue)))
        {
            return err;
        }
    }

    for (int i = 0, irq_idx = 1; i < nvme->io_queue_max; ++i, ++irq_idx)
    {
        irq = nvme->irqs[irq_idx % nvme->irqs_nr];

        rt_snprintf(name, RT_NAME_MAX, "%s-io-queue%d", nvme->name, i);

        if (!affinity_fixup)
        {
            RT_IRQ_AFFINITY_SET(affinity, cpuid % RT_CPUS_NR);
            if (rt_pic_irq_set_affinity(irq, affinity))
            {
                /* Fixup in secondary CPU startup */
                affinity_fixup = RT_TRUE;
            }
            RT_IRQ_AFFINITY_CLEAR(affinity, cpuid++ % RT_CPUS_NR);
        }

        rt_hw_interrupt_install(irq, nvme_queue_isr, &nvme->io_queues[i], name);
        rt_hw_interrupt_umask(irq);
    }

    return RT_EOK;
}

static void nvme_remove_io_queues(struct rt_nvme_controller *nvme)
{
    int irq;
    struct rt_nvme_queue *queue;

    for (int i = 0, irq_idx = 1; i < nvme->io_queue_max; ++i, ++irq_idx)
    {
        queue = &nvme->io_queues[i];

        nvme_detach_queue(queue, RT_NVME_ADMIN_OPCODE_DELETE_SQ);
        nvme_detach_queue(queue, RT_NVME_ADMIN_OPCODE_DELETE_CQ);
        nvme_free_queue(queue);

        irq = nvme->irqs[irq_idx % nvme->irqs_nr];

        rt_hw_interrupt_mask(irq);
        rt_pic_detach_irq(irq, queue);
    }
}

static void nvme_remove_admin_queues(struct rt_nvme_controller *nvme)
{
    int irq = nvme->irqs[0];

    rt_hw_interrupt_mask(irq);
    rt_pic_detach_irq(irq, &nvme->admin_queue);

    nvme_free_queue(&nvme->admin_queue);
}

static void nvme_remove_devices(struct rt_nvme_controller *nvme)
{
    struct rt_nvme_device *ndev, *next_ndev;

    rt_list_for_each_entry_safe(ndev, next_ndev, &nvme->ns_nodes, list)
    {
        rt_list_remove(&ndev->list);

        rt_hw_blk_disk_unregister(&ndev->parent);
        rt_free(ndev);
    }
}

static rt_err_t nvme_scan_device(struct rt_nvme_controller *nvme,
        rt_size_t number_of_ns)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t lbaf;
    struct rt_nvme_id_ns *id = RT_NULL;

    if (!(id = rt_malloc_align(sizeof(*id), nvme->page_size)))
    {
        return -RT_ENOMEM;
    }

    /* NVME Namespace is start with "1" */
    for (rt_uint32_t nsid = 1; nsid <= number_of_ns; ++nsid)
    {
        struct rt_nvme_device *ndev = rt_calloc(1, sizeof(*ndev));

        if (!ndev)
        {
            err = -RT_ENOMEM;
            goto _free_res;
        }

        rt_memset(id, 0, sizeof(*id));
        if ((err = nvme_identify(nvme, nsid, 0, id)))
        {
            goto _free_res;
        }

        if (!id->nsze)
        {
            continue;
        }

        ndev->ctrl = nvme;

        rt_memcpy(&ndev->id, id, sizeof(ndev->id));
        lbaf = id->flbas & RT_NVME_NS_FLBAS_LBA_MASK;
        lbaf |= ((id->flbas & RT_NVME_NS_FLBAS_LBA_UMASK) >> RT_NVME_NS_FLBAS_LBA_SHIFT);

        ndev->nsid = nsid;
        ndev->lba_shift = id->lbaf[lbaf].ds;

        ndev->parent.ida = &nvme_ida;
        ndev->parent.parallel_io = RT_TRUE;
        ndev->parent.ops = &nvme_blk_ops;
        ndev->parent.max_partitions = RT_BLK_PARTITION_MAX;
        rt_dm_dev_set_name(&ndev->parent.parent, "%sn%u", nvme->name, nsid);

        if ((err = rt_hw_blk_disk_register(&ndev->parent)))
        {
            goto _free_res;
        }

        rt_list_init(&ndev->list);
        rt_list_insert_before(&nvme->ns_nodes, &ndev->list);
    }

_free_res:
    rt_free_align(id);

    return err;
}

rt_inline rt_size_t strip_len(const char *str, rt_size_t max_len)
{
    rt_size_t size = 0;

    for (int i = 0; *str && i < max_len; ++i, ++str)
    {
        if (*str != ' ')
        {
            size = i + 1;
        }
    }

    return size;
}

rt_err_t rt_nvme_controller_register(struct rt_nvme_controller *nvme)
{
    rt_err_t err;
    struct rt_nvme_id_ctrl *ctrl = RT_NULL;

    if (!nvme || !nvme->ops)
    {
        return -RT_EINVAL;
    }

    if (nvme_readl(nvme, RT_NVME_REG_CSTS) == (rt_uint32_t)-1)
    {
        LOG_E("Out of memory");

        return -RT_EINVAL;
    }

    if ((nvme->nvme_id = rt_dm_ida_alloc(&nvme_controller_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rt_snprintf(nvme->name, RT_NAME_MAX, "nvme%u", nvme->nvme_id);

    nvme->cap = nvme_readq(nvme, RT_NVME_REG_CAP);
    nvme->queue_depth = RT_NVME_CAP_MQES(nvme->cap) + 1;
    nvme->doorbell_stride = 1 << RT_NVME_CAP_STRIDE(nvme->cap);
    nvme->doorbell_tbl = nvme->regs + RT_NVME_REG_DBS;

    if ((err = nvme_configure_admin_queue(nvme)))
    {
        LOG_E("Configure admin queue error = %s", rt_strerror(err));
        goto _free_admin_queue;
    }

    if ((err = nvme_setup_io_queues(nvme)))
    {
        LOG_E("Unable to setup I/O queues error = %s", rt_strerror(err));
        goto _free_admin_queue;
    }

    if (!(ctrl = rt_malloc_align(sizeof(*ctrl), nvme->page_size)))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    if ((err = nvme_identify(nvme, 0, 1, ctrl)))
    {
        goto _fail;
    }

    if (ctrl->mdts)
    {
        nvme->max_transfer_shift = ctrl->mdts + (RT_NVME_CAP_MPSMIN(nvme->cap) + 12);
    }
    else
    {
        /* 1MB is recommended. */
        nvme->max_transfer_shift = 20;
    }
    nvme->volatile_write_cache = ctrl->vwc;
    nvme->write_zeroes = !!(rt_le64_to_cpu(ctrl->oncs) & RT_NVME_CTRL_ONCS_WRITE_ZEROES);

    if ((rt_le32_to_cpu(ctrl->sgls) & RT_NVME_ID_SGL_SUPPORT_MASK))
    {
        nvme->sgl_mode = RT_NVME_PSDT_SGL_MPTR_SGL;
    }

    LOG_I("NVM Express v%d.%d (%s, %-*.s, %-*.s)",
            nvme_readl(nvme, RT_NVME_REG_VS) >> 16,
            nvme_readl(nvme, RT_NVME_REG_VS) & 0xff,
            nvme->ops->name,
            strip_len(ctrl->mn, sizeof(ctrl->mn)), ctrl->mn,
            strip_len(ctrl->fr, sizeof(ctrl->fr)), ctrl->fr);

    rt_list_init(&nvme->ns_nodes);
    if ((err = nvme_scan_device(nvme, rt_le32_to_cpu(ctrl->nn))))
    {
        goto _fail;
    }

    rt_free_align(ctrl);

    rt_spin_lock(&nvme_lock);
    rt_list_insert_after(&nvme_nodes, &nvme->list);
    rt_spin_unlock(&nvme_lock);

    return RT_EOK;

_fail:
    if (ctrl)
    {
        rt_free_align(ctrl);
    }
    nvme_remove_devices(nvme);
    nvme_remove_io_queues(nvme);
_free_admin_queue:
    nvme_remove_admin_queues(nvme);

    rt_dm_ida_free(&nvme_controller_ida, nvme->nvme_id);

    return err;
}

rt_err_t rt_nvme_controller_unregister(struct rt_nvme_controller *nvme)
{
    rt_err_t err;

    if (!nvme)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&nvme_lock);
    rt_list_remove(&nvme->list);
    rt_spin_unlock(&nvme_lock);

    nvme_remove_devices(nvme);
    nvme_remove_io_queues(nvme);
    nvme_remove_admin_queues(nvme);

    rt_dm_ida_free(&nvme_controller_ida, nvme->nvme_id);

    if (!(err = nvme_shutdown_ctrl(nvme)))
    {
        err = nvme_disable_ctrl(nvme);
    }
    else
    {
        LOG_E("%s: shutdown error = %s", nvme->name, rt_strerror(err));
    }

    return err;
}

/*
 * NVME's IO queue should be Per-CPU, fixup the affinity after the secondary CPU
 * startup, this stage can make sure the affinity setting success as possible.
 */
static int nvme_queue_affinify_fixup(void)
{
    int cpuid = rt_hw_cpu_id();
    struct rt_nvme_controller *nvme;
    RT_IRQ_AFFINITY_DECLARE(affinity) = { 0 };
    RT_IRQ_AFFINITY_DECLARE(current_affinity) = { 0 };

    RT_IRQ_AFFINITY_SET(affinity, cpuid);

    rt_hw_spin_lock(&nvme_lock.lock);
    rt_list_for_each_entry(nvme, &nvme_nodes, list)
    {
        for (int i = cpuid % RT_CPUS_NR; i < nvme->io_queue_max; i += RT_CPUS_NR)
        {
            int irq = nvme->irqs[i];

            if (!rt_pic_irq_get_affinity(irq, current_affinity) &&
                !rt_bitmap_test_bit(current_affinity, cpuid))
            {
                rt_ubase_t level = rt_hw_interrupt_disable();

                rt_pic_irq_set_affinity(irq, affinity);

                rt_hw_interrupt_enable(level);
            }
        }
    }
    rt_hw_spin_unlock(&nvme_lock.lock);

    return 0;
}
INIT_SECONDARY_CPU_EXPORT(nvme_queue_affinify_fixup);
