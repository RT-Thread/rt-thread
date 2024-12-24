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

#define DBG_TAG "rtdm.ahci"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define HWREG32_FLUSH(base, value)  \
do {                                \
    rt_uint32_t __value = value;    \
    HWREG32(base) = __value;        \
    __value = HWREG32(base);        \
} while (0)

static void ahci_fill_cmd_slot(struct rt_ahci_port *port, rt_uint32_t opts)
{
    rt_ubase_t dma_addr = port->cmd_tbl_dma;
    struct rt_ahci_cmd_hdr *cmd_slot = port->cmd_slot;

    cmd_slot->opts = rt_cpu_to_le32(opts);
    cmd_slot->status = 0;
    cmd_slot->tbl_addr_lo = rt_cpu_to_le32(rt_lower_32_bits(dma_addr));
    cmd_slot->tbl_addr_hi = rt_cpu_to_le32(rt_upper_32_bits(dma_addr));
}

static int ahci_fill_sg(struct rt_ahci_host *host, int id,
        void *buffer, rt_size_t buffer_size)
{
    int sg_count;
    rt_ubase_t dma_addr;
    struct rt_ahci_port *port = &host->ports[id];
    struct rt_ahci_sg *ahci_sg = port->cmd_tbl_sg;

    sg_count = ((buffer_size - 1) / RT_ACHI_PRDT_BYTES_MAX) + 1;

    if (sg_count > RT_AHCI_MAX_SG)
    {
        return -1;
    }

    dma_addr = (rt_ubase_t)rt_kmem_v2p(buffer);

    for (int i = 0; i < sg_count; ++i, ++ahci_sg)
    {
        ahci_sg->addr_lo = rt_cpu_to_le32(rt_lower_32_bits(dma_addr));
        ahci_sg->addr_hi = rt_cpu_to_le32(rt_upper_32_bits(dma_addr));

        if (ahci_sg->addr_hi && !(host->cap & RT_AHCI_CAP_64))
        {
            return -1;
        }

        ahci_sg->flags_size = rt_cpu_to_le32(0x3fffff &
                (rt_min_t(rt_uint32_t, buffer_size, RT_ACHI_PRDT_BYTES_MAX) - 1));

        dma_addr += RT_ACHI_PRDT_BYTES_MAX;
        buffer_size -= RT_ACHI_PRDT_BYTES_MAX;
    }

    return sg_count;
}

static rt_err_t ahci_request_io(struct rt_ahci_host *host, int id,
        void *fis, rt_size_t fis_size,
        void *buffer, rt_size_t buffer_size, rt_bool_t is_read)
{
    int sg_count;
    rt_err_t err;
    struct rt_ahci_port *port = &host->ports[id];

    if ((HWREG32(port->regs + RT_AHCI_PORT_SSTS) & 0xf) != RT_AHCI_PORT_SSTS_DET_PHYRDY)
    {
        return -RT_EIO;
    }

    if ((sg_count = ahci_fill_sg(host, id, buffer, buffer_size)) <= 0)
    {
        return -RT_EINVAL;
    }

    rt_memcpy(port->cmd_tbl, fis, fis_size);
    ahci_fill_cmd_slot(port, (fis_size >> 2) | (sg_count << 16) | (!is_read << 6));

    if (!is_read)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, buffer, buffer_size);
    }

    HWREG32_FLUSH(port->regs + RT_AHCI_PORT_CI, 1);

    err = rt_completion_wait(&port->done, rt_tick_from_millisecond(10000));

    if (!err && is_read)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, buffer, buffer_size);
    }

    return err;
}

static rt_err_t ahci_scsi_cmd_rw(struct rt_ahci_host *host, int id,
        rt_off_t lba, void *buffer, rt_ssize_t size, rt_bool_t is_read)
{
    rt_err_t err;
    rt_uint8_t fis[20];
    struct rt_ahci_port *port = &host->ports[id];

    rt_memset(fis, 0, sizeof(fis));
    fis[0] = RT_AHCI_FIS_TYPE_REG_H2D;
    fis[1] = 1 << 7; /* Command */
    fis[2] = is_read ? RT_AHCI_ATA_CMD_READ_EXT : RT_AHCI_ATA_CMD_WRITE_EXT;

    while (size > 0)
    {
        rt_size_t t_size, t_lba;

        t_lba = rt_min_t(rt_size_t, host->max_blocks, size);
        t_size = port->block_size * t_lba;

        fis[3] = 0xe0;                  /* Features */
        fis[4] = (lba >> 0) & 0xff;     /* LBA low register */
        fis[5] = (lba >> 8) & 0xff;     /* LBA mid register */
        fis[6] = (lba >> 16) & 0xff;    /* LBA high register */
        fis[7] = 1 << 6;                /* Device */
        fis[8] = ((lba >> 24) & 0xff);  /* LBA register, 31:24 */
        fis[9] = ((lba >> 32) & 0xff);  /* LBA register, 39:32 */
        fis[10] = ((lba >> 40) & 0xff); /* LBA register, 47:40 */
        fis[12] = (t_lba >> 0) & 0xff;  /* Count register, 7:0 */
        fis[13] = (t_lba >> 8) & 0xff;  /* Count register, 15:8 */

        if ((err = ahci_request_io(host, id, fis, sizeof(fis), buffer, t_size, is_read)))
        {
            return err;
        }

        size -= t_lba;
        lba += t_lba;
        buffer += t_size;
    }

    return RT_EOK;
}

static rt_err_t ahci_scsi_synchronize_cache(struct rt_ahci_host *host, int id,
        rt_off_t lba, rt_size_t size)
{
    rt_uint8_t fis[20];
    rt_uint16_t *ataid;
    struct rt_ahci_port *port = &host->ports[id];

    ataid = port->ataid;

    if (!rt_ahci_ata_id_wcache_enabled(ataid) &&
        !rt_ahci_ata_id_has_flush(ataid) &&
        !rt_ahci_ata_id_has_flush_ext(ataid))
    {
        return -RT_ENOSYS;
    }

    rt_memset(fis, 0, sizeof(fis));
    fis[0] = RT_AHCI_FIS_TYPE_REG_H2D;
    fis[1] = 1 << 7; /* Command */

    if (rt_ahci_ata_id_has_flush_ext(ataid))
    {
        fis[2] = RT_AHCI_ATA_CMD_FLUSH_EXT;
    }
    else
    {
        fis[2] = RT_AHCI_ATA_CMD_FLUSH;
    }

    rt_memcpy(port->cmd_tbl, fis, 20);
    ahci_fill_cmd_slot(port, 5);

    HWREG32_FLUSH(port->regs + RT_AHCI_PORT_CI, 1);

    return rt_completion_wait(&port->done, rt_tick_from_millisecond(5000));
}

static rt_err_t ahci_scsi_cmd_write_same(struct rt_ahci_host *host, int id,
        rt_off_t lba, rt_size_t size)
{
    rt_uint8_t fis[20];
    struct rt_ahci_port *port = &host->ports[id];

    rt_memset(fis, 0, sizeof(fis));
    fis[0] = RT_AHCI_FIS_TYPE_REG_H2D;
    fis[1] = 1 << 7;                /* Command */
    fis[2] = RT_AHCI_ATA_CMD_DSM;
    fis[3] = RT_AHCI_ATA_DSM_TRIM;  /* Features */
    fis[4] = (lba >> 0) & 0xff;     /* LBA low register */
    fis[5] = (lba >> 8) & 0xff;     /* LBA mid register */
    fis[6] = (lba >> 16) & 0xff;    /* LBA high register */
    fis[7] = 1 << 6;                /* Device */
    fis[8] = ((lba >> 24) & 0xff);  /* LBA register, 31:24 */
    fis[9] = ((lba >> 32) & 0xff);  /* LBA register, 39:32 */
    fis[10] = ((lba >> 40) & 0xff); /* LBA register, 47:40 */
    fis[12] = (size >> 0) & 0xff;   /* Count register, 7:0 */
    fis[13] = (size >> 8) & 0xff;   /* Count register, 15:8 */

    HWREG32_FLUSH(port->regs + RT_AHCI_PORT_CI, 1);

    return rt_completion_wait(&port->done, rt_tick_from_millisecond(5000));
}

static rt_err_t ahci_scsi_cmd_read_capacity(struct rt_ahci_host *host, int id,
        rt_size_t *out_last_block, rt_size_t *out_block_size)
{
    struct rt_ahci_port *port = &host->ports[id];

    if (!port->ataid)
    {
        return -RT_EIO;
    }

    *out_last_block = rt_ahci_ata_id_n_sectors(port->ataid) - 1;
    *out_block_size = port->block_size;

    return RT_EOK;
}

static rt_err_t ahci_scsi_cmd_test_unit_ready(struct rt_ahci_host *host, int id)
{
    struct rt_ahci_port *port = &host->ports[id];

    return port->ataid ? RT_EOK : -RT_EIO;
}

static rt_err_t ahci_scsi_cmd_inquiry(struct rt_ahci_host *host, int id,
        char *prodid, rt_size_t prodid_len, char *prodrev, rt_size_t prodrev_len)
{
    rt_err_t err;
    rt_uint8_t fis[20];
    rt_uint16_t *ataid;
    struct rt_ahci_port *port = &host->ports[id];

    if (!port->link)
    {
        return -RT_EIO;
    }

    if (!port->ataid && !(port->ataid = rt_malloc(RT_AHCI_ATA_ID_WORDS * 2)))
    {
        return -RT_ENOMEM;
    }
    ataid = port->ataid;

    rt_memset(fis, 0, sizeof(fis));
    fis[0] = RT_AHCI_FIS_TYPE_REG_H2D;
    fis[1] = 1 << 7; /* Command */
    fis[2] = RT_AHCI_ATA_CMD_ID_ATA;

    if ((err = ahci_request_io(host, id, fis, sizeof(fis),
            ataid, RT_AHCI_ATA_ID_WORDS * 2, RT_TRUE)))
    {
        return err;
    }

    for (int i = 0; i < RT_AHCI_ATA_ID_WORDS; ++i)
    {
        ataid[i] = rt_le16_to_cpu(ataid[i]);
    }

    for (int i = 0; i < prodid_len / 2; ++i)
    {
        rt_uint16_t src = ataid[RT_AHCI_ATA_ID_PROD + i];

        prodid[i] = (src & 0x00ff) << 8 | (src & 0xff00) >> 8;
    }

    for (int i = 0; i < prodrev_len / 2; ++i)
    {
        rt_uint16_t src = ataid[RT_AHCI_ATA_ID_FW_REV + i];

        prodrev[i] = (src & 0x00ff) << 8 | (src & 0xff00) >> 8;
    }

    return err;
}

static rt_err_t ahci_scsi_transfer(struct rt_scsi_device *sdev,
        struct rt_scsi_cmd *cmd)
{
    rt_err_t err;
    struct rt_ahci_host *host;

    host = rt_container_of(sdev->host, struct rt_ahci_host, parent);

    switch (cmd->op.unknow.opcode)
    {
    case RT_SCSI_CMD_REQUEST_SENSE:
    {
        struct rt_scsi_request_sense_data *request_sense = &cmd->data.request_sense;

        request_sense->error_code = 0x72;

        err = RT_EOK;
    }
        break;

    case RT_SCSI_CMD_READ10:
    {
        struct rt_scsi_read10 *read10 = &cmd->op.read10;

        err = ahci_scsi_cmd_rw(host, sdev->id,
                rt_be32_to_cpu(read10->lba),
                cmd->data.ptr,
                rt_be16_to_cpu(read10->size),
                RT_TRUE);
    }
        break;

    case RT_SCSI_CMD_READ16:
    {
        struct rt_scsi_read16 *read16 = &cmd->op.read16;

        err = ahci_scsi_cmd_rw(host, sdev->id,
                rt_be64_to_cpu(read16->lba),
                cmd->data.ptr,
                rt_be32_to_cpu(read16->size),
                RT_TRUE);
    }
        break;

    case RT_SCSI_CMD_READ12:
    {
        struct rt_scsi_read12 *read12 = &cmd->op.read12;

        err = ahci_scsi_cmd_rw(host, sdev->id,
                rt_be32_to_cpu(read12->lba),
                cmd->data.ptr,
                rt_be32_to_cpu(read12->size),
                RT_TRUE);
    }
        break;

    case RT_SCSI_CMD_WRITE10:
    {
        struct rt_scsi_write10 *write10 = &cmd->op.write10;

        err = ahci_scsi_cmd_rw(host, sdev->id,
                rt_be32_to_cpu(write10->lba),
                cmd->data.ptr,
                rt_be16_to_cpu(write10->size),
                RT_FALSE);
    }
        break;

    case RT_SCSI_CMD_WRITE16:
    {
        struct rt_scsi_write16 *write16 = &cmd->op.write16;

        err = ahci_scsi_cmd_rw(host, sdev->id,
                rt_be64_to_cpu(write16->lba),
                cmd->data.ptr,
                rt_be32_to_cpu(write16->size),
                RT_FALSE);
    }
        break;

    case RT_SCSI_CMD_WRITE12:
    {
        struct rt_scsi_write12 *write12 = &cmd->op.write12;

        err = ahci_scsi_cmd_rw(host, sdev->id,
                rt_be32_to_cpu(write12->lba),
                cmd->data.ptr,
                rt_be32_to_cpu(write12->size),
                RT_FALSE);
    }
        break;

    case RT_SCSI_CMD_SYNCHRONIZE_CACHE10:
    {
        struct rt_scsi_synchronize_cache10 *synchronize_cache10 = &cmd->op.synchronize_cache10;

        err = ahci_scsi_synchronize_cache(host, sdev->id,
                rt_be32_to_cpu(synchronize_cache10->lba),
                rt_be16_to_cpu(synchronize_cache10->size));
    }
        break;

    case RT_SCSI_CMD_SYNCHRONIZE_CACHE16:
    {
        struct rt_scsi_synchronize_cache16 *synchronize_cache16 = &cmd->op.synchronize_cache16;

        err = ahci_scsi_synchronize_cache(host, sdev->id,
                rt_be64_to_cpu(synchronize_cache16->lba),
                rt_be32_to_cpu(synchronize_cache16->size));
    }
        break;

    case RT_SCSI_CMD_WRITE_SAME10:
    {
        struct rt_scsi_write_same10 *write_same10 = &cmd->op.write_same10;

        err = ahci_scsi_cmd_write_same(host, sdev->id,
                rt_be32_to_cpu(write_same10->lba), rt_be16_to_cpu(write_same10->size));
    }
        break;

    case RT_SCSI_CMD_WRITE_SAME16:
    {
        struct rt_scsi_write_same16 *write_same16 = &cmd->op.write_same16;

        err = ahci_scsi_cmd_write_same(host, sdev->id,
                rt_be64_to_cpu(write_same16->lba), rt_be32_to_cpu(write_same16->size));
    }
        break;

    case RT_SCSI_CMD_READ_CAPACITY10:
    {
        rt_size_t last_block, block_size;
        struct rt_scsi_read_capacity10_data *data = &cmd->data.read_capacity10;

        err = ahci_scsi_cmd_read_capacity(host, sdev->id, &last_block, &block_size);

        if (!err)
        {
            if (last_block > 0x100000000ULL)
            {
                last_block = 0xffffffff;
            }

            data->last_block = rt_cpu_to_be32(last_block);
            data->block_size = rt_cpu_to_be32(block_size);
        }
    }
        break;

    case RT_SCSI_CMD_READ_CAPACITY16:
    {
        rt_size_t last_block, block_size;
        struct rt_scsi_read_capacity16_data *data = &cmd->data.read_capacity16;

        err = ahci_scsi_cmd_read_capacity(host, sdev->id, &last_block, &block_size);

        if (!err)
        {
            data->last_block = rt_cpu_to_be64(last_block);
            data->block_size = rt_cpu_to_be32(block_size);
        }
    }
        break;

    case RT_SCSI_CMD_TEST_UNIT_READY:
        err = ahci_scsi_cmd_test_unit_ready(host, sdev->id);
        break;

    case RT_SCSI_CMD_INQUIRY:
    {
        struct rt_ahci_port *port = &host->ports[sdev->id];
        struct rt_scsi_inquiry_data *inquiry = &cmd->data.inquiry;

        err = ahci_scsi_cmd_inquiry(host, sdev->id,
                inquiry->prodid, sizeof(inquiry->prodid),
                inquiry->prodrev, sizeof(inquiry->prodrev));

        if (!err)
        {
            rt_memcpy(inquiry->vendor, "ATA     ", sizeof(inquiry->vendor));

            if (HWREG32(port->regs + RT_AHCI_PORT_SIG) != RT_AHCI_PORT_SIG_SATA_CDROM)
            {
                port->block_size = 512;
                inquiry->devtype = SCSI_DEVICE_TYPE_DIRECT;
            }
            else
            {
                port->block_size = 2048;
                inquiry->devtype = SCSI_DEVICE_TYPE_CDROM;
            }
            inquiry->rmb = 0;
            inquiry->length = 95 - 4;
        }
    }
        break;

    case RT_SCSI_CMD_MODE_SENSE:
    case RT_SCSI_CMD_MODE_SENSE10:
    case RT_SCSI_CMD_MODE_SELECT:
    case RT_SCSI_CMD_MODE_SELECT10:
        return -RT_ENOSYS;

    default:
        return -RT_EINVAL;
    }

    return err;
}

static struct rt_scsi_ops ahci_scsi_ops =
{
    .transfer = ahci_scsi_transfer,
};

static void ahci_isr(int irqno, void *param)
{
    int id;
    rt_uint32_t isr;
    rt_bitmap_t int_map;
    struct rt_ahci_port *port;
    struct rt_ahci_host *host = param;

    int_map = HWREG32(host->regs + RT_AHCI_HBA_INTS);

    rt_bitmap_for_each_set_bit(&int_map, id, host->ports_nr)
    {
        port = &host->ports[id];

        isr = HWREG32(port->regs + RT_AHCI_PORT_INTS);

        if (port->link)
        {
            if (host->ops->port_isr)
            {
                host->ops->port_isr(host, port, isr);
            }

            rt_completion_done(&port->done);
        }

        HWREG32(port->regs + RT_AHCI_PORT_INTS) = isr;
    }

    HWREG32(host->regs + RT_AHCI_HBA_INTS) = int_map;
}

rt_err_t rt_ahci_host_register(struct rt_ahci_host *host)
{
    rt_err_t err;
    rt_uint32_t value;
    char dev_name[RT_NAME_MAX];
    struct rt_scsi_host *scsi;

    if (!host || !host->parent.dev || !host->ops)
    {
        return -RT_EINVAL;
    }

    host->max_blocks = host->max_blocks ? : 0x80;

    /*
     * 1. Reset HBA.
     */
    err = -RT_EIO;
    value = HWREG32(host->regs + RT_AHCI_HBA_GHC);

    if (!(value & RT_AHCI_GHC_RESET))
    {
        HWREG32_FLUSH(host->regs + RT_AHCI_HBA_GHC, value | RT_AHCI_GHC_RESET);
    }

    for (int i = 0; i < 5; ++i)
    {
        rt_thread_mdelay(200);

        if (!(HWREG32(host->regs + RT_AHCI_HBA_GHC) & RT_AHCI_GHC_RESET))
        {
            err = RT_EOK;
            break;
        }
    }

    if (err)
    {
        goto _fail;
    }

    /*
     * 2. Enable AHCI and get the ports' information.
     */
    HWREG32_FLUSH(host->regs + RT_AHCI_HBA_GHC, RT_AHCI_GHC_AHCI_EN);

    host->cap = HWREG32(host->regs + RT_AHCI_HBA_CAP);
    host->cap &= RT_AHCI_CAP_SPM | RT_AHCI_CAP_SSS | RT_AHCI_CAP_SIS;
    HWREG32(host->regs + RT_AHCI_HBA_CAP) = host->cap;
    host->cap = HWREG32(host->regs + RT_AHCI_HBA_CAP);

    HWREG32_FLUSH(host->regs + RT_AHCI_HBA_PI, 0xf);

    if (host->ops->host_init && (err = host->ops->host_init(host)))
    {
        goto _fail;
    }

    host->ports_nr = (host->cap & RT_AHCI_CAP_NP) + 1;
    host->ports_map = HWREG32(host->regs + RT_AHCI_HBA_PI);

    /* Check implemented in firmware */
    rt_dm_dev_prop_read_u32(host->parent.dev, "ports-implemented", &host->ports_map);

    for (int i = 0; i < host->ports_nr; ++i)
    {
        struct rt_ahci_port *port;

        if (!(host->ports_map & RT_BIT(i)))
        {
            continue;
        }
        port = &host->ports[i];

        /*
         * 3. Alloc port io memory.
         */
        port->regs = host->regs + 0x100 + (i * 0x80);

        /*
         * 4. Make port stop.
         */
        value = HWREG32(port->regs + RT_AHCI_PORT_CMD);
        if (value & (RT_AHCI_PORT_CMD_LIST_ON | RT_AHCI_PORT_CMD_FIS_ON |
                RT_AHCI_PORT_CMD_FIS_RX | RT_AHCI_PORT_CMD_START))
        {
            value &= ~(RT_AHCI_PORT_CMD_LIST_ON | RT_AHCI_PORT_CMD_FIS_ON |
                    RT_AHCI_PORT_CMD_FIS_RX | RT_AHCI_PORT_CMD_START);

            HWREG32_FLUSH(port->regs + RT_AHCI_PORT_CMD, value);

            rt_thread_mdelay(500);
        }

        if (host->ops->port_init && (err = host->ops->port_init(host, port)))
        {
            LOG_E("Init port[%d] error = %s", rt_strerror(err));
            continue;
        }

        value = HWREG32(port->regs + RT_AHCI_PORT_CMD);
        value |= RT_AHCI_PORT_CMD_SPIN_UP;
        HWREG32(port->regs + RT_AHCI_PORT_CMD) = value;

        /*
         * 5. Enable port's SATA link.
         */
        if (host->ops->port_link_up)
        {
            err = host->ops->port_link_up(host, port);
        }
        else
        {
            err = -RT_ETIMEOUT;

            for (int retry = 0; retry < 5; ++retry)
            {
                value = HWREG32(port->regs + RT_AHCI_PORT_SSTS);

                if ((value & RT_AHCI_PORT_SSTS_DET_MASK) == RT_AHCI_PORT_SSTS_DET_PHYRDY)
                {
                    err = RT_EOK;
                    break;
                }

                rt_thread_mdelay(2);
            }
        }

        if (err)
        {
            if (HWREG32(port->regs + RT_AHCI_PORT_SSTS) & RT_AHCI_PORT_SSTS_DET_MASK)
            {
                LOG_E("SATA[%d] link error = %s", i, rt_strerror(err));
            }
            else
            {
                LOG_D("SATA[%d] not device", i);
            }

            continue;
        }

        /* Clear error status */
        if ((value = HWREG32(port->regs + RT_AHCI_PORT_SERR)))
        {
            HWREG32(port->regs + RT_AHCI_PORT_SERR) = value;
        }

        for (int retry = 0; retry < 5; ++retry)
        {
            value = HWREG32(port->regs + RT_AHCI_PORT_TFD);
            if (!(value & (RT_AHCI_PORT_TFDATA_BSY | RT_AHCI_PORT_TFDATA_DRQ)))
            {
                break;
            }

            rt_thread_mdelay(2);

            value = HWREG32(port->regs + RT_AHCI_PORT_SSTS);
            if ((value & RT_AHCI_PORT_SSTS_DET_MASK) == RT_AHCI_PORT_SSTS_DET_PHYRDY)
            {
                break;
            }
        }

        value = HWREG32(port->regs + RT_AHCI_PORT_SSTS) & RT_AHCI_PORT_SSTS_DET_MASK;
        if (value == RT_AHCI_PORT_SSTS_DET_COMINIT)
        {
            /* Retry to setup */
            --i;
            continue;
        }

        /* Clear error */
        value = HWREG32(port->regs + RT_AHCI_PORT_SERR);
        HWREG32(port->regs + RT_AHCI_PORT_SERR) = value;

        /* Clear pending IRQ */
        if ((value = HWREG32(port->regs + RT_AHCI_PORT_INTS)))
        {
            HWREG32(port->regs + RT_AHCI_PORT_INTS) = value;
        }

        HWREG32(host->regs + RT_AHCI_HBA_INTS) = RT_BIT(i);

        value = HWREG32(port->regs + RT_AHCI_PORT_SSTS);
        if ((value & RT_AHCI_PORT_SSTS_DET_MASK) == RT_AHCI_PORT_SSTS_DET_PHYRDY)
        {
            port->link = RT_TRUE;
        }
    }

    HWREG32(host->regs + RT_AHCI_HBA_GHC) |= RT_AHCI_GHC_IRQ_EN;

    for (int i = 0; i < host->ports_nr; ++i)
    {
        void *dma;
        rt_ubase_t dma_addr;
        rt_tick_t timeout;
        struct rt_ahci_port *port = &host->ports[i];

        if (!port->link)
        {
            continue;
        }

        /*
         * 6. Alloc transport memory, Port x Command List and FIS Base Address.
         */
        port->dma = rt_dma_alloc_coherent(host->parent.dev,
                RT_AHCI_DMA_SIZE, &port->dma_handle);

        if (!port->dma)
        {
            LOG_E("No memory to setup port[%d]", i);
            break;
        }
        dma = port->dma;

        rt_memset(dma, 0, RT_AHCI_DMA_SIZE);

        port->cmd_slot = dma;
        dma += (RT_AHCI_CMD_SLOT_SIZE + 224);

        port->rx_fis = dma;
        dma += RT_AHCI_RX_FIS_SIZE;

        port->cmd_tbl = dma;
        port->cmd_tbl_dma = (rt_ubase_t)rt_kmem_v2p(dma);
        dma += RT_AHCI_CMD_TBL_HDR;

        port->cmd_tbl_sg = dma;

        dma_addr = (rt_ubase_t)rt_kmem_v2p(port->cmd_slot);
        HWREG32_FLUSH(port->regs + RT_AHCI_PORT_CLB, rt_lower_32_bits(dma_addr));
        HWREG32_FLUSH(port->regs + RT_AHCI_PORT_CLBU, rt_upper_32_bits(dma_addr));

        dma_addr = (rt_ubase_t)rt_kmem_v2p(port->rx_fis);
        HWREG32_FLUSH(port->regs + RT_AHCI_PORT_FB, rt_lower_32_bits(dma_addr));
        HWREG32_FLUSH(port->regs + RT_AHCI_PORT_FBU, rt_upper_32_bits(dma_addr));

        if (host->ops->port_dma_init && (err = host->ops->port_dma_init(host, port)))
        {
            LOG_E("Init port[%d] DMA error = %s", rt_strerror(err));
        }

        HWREG32_FLUSH(port->regs + RT_AHCI_PORT_CMD, RT_AHCI_PORT_CMD_ACTIVE |
                RT_AHCI_PORT_CMD_FIS_RX | RT_AHCI_PORT_CMD_POWER_ON |
                RT_AHCI_PORT_CMD_SPIN_UP | RT_AHCI_PORT_CMD_START);

        /* Wait spinup */
        err = -RT_ETIMEOUT;
        timeout = rt_tick_from_millisecond(20000);
        timeout += rt_tick_get();
        do {
            if (!(HWREG32(port->regs + RT_AHCI_PORT_TFD) & RT_AHCI_PORT_TFDATA_BSY))
            {
                err = RT_EOK;
                break;
            }

            rt_hw_cpu_relax();
        } while (rt_tick_get() < timeout);

        if (err)
        {
            rt_dma_free_coherent(host->parent.dev, RT_AHCI_DMA_SIZE, port->dma,
                    port->dma_handle);
            port->dma = RT_NULL;

            LOG_E("Start up port[%d] fail", i);
            continue;
        }

        port->int_enabled |= RT_AHCI_PORT_INTE_HBUS_ERR | RT_AHCI_PORT_INTE_IF_ERR |
                RT_AHCI_PORT_INTE_CONNECT | RT_AHCI_PORT_INTE_PHYRDY |
                RT_AHCI_PORT_INTE_UNK_FIS | RT_AHCI_PORT_INTE_BAD_PMP |
                RT_AHCI_PORT_INTE_TF_ERR | RT_AHCI_PORT_INTE_HBUS_DATA_ERR |
                RT_AHCI_PORT_INTE_SG_DONE | RT_AHCI_PORT_INTE_SDB_FIS |
                RT_AHCI_PORT_INTE_DMAS_FIS | RT_AHCI_PORT_INTE_PIOS_FIS |
                RT_AHCI_PORT_INTE_D2H_REG_FIS;

        HWREG32(port->regs + RT_AHCI_PORT_INTE) = port->int_enabled;

        rt_completion_init(&port->done);
    }

    rt_snprintf(dev_name, sizeof(dev_name), "ahci-%s",
            rt_dm_dev_get_name(host->parent.dev));

    rt_hw_interrupt_install(host->irq, ahci_isr, host, dev_name);
    rt_hw_interrupt_umask(host->irq);

    scsi = &host->parent;
    scsi->max_lun = rt_max_t(rt_size_t, scsi->max_lun, 1);
    scsi->max_id = host->ports_nr;
    scsi->ops = &ahci_scsi_ops;

    if ((err = rt_scsi_host_register(scsi)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_hw_interrupt_mask(host->irq);
    rt_pic_detach_irq(host->irq, host);

    return err;
}

rt_err_t rt_ahci_host_unregister(struct rt_ahci_host *host)
{
    rt_err_t err;
    struct rt_scsi_host *scsi;

    if (!host)
    {
        return -RT_EINVAL;
    }

    scsi = &host->parent;

    if ((err = rt_scsi_host_unregister(scsi)))
    {
        return err;
    }

    rt_hw_interrupt_mask(host->irq);
    rt_pic_detach_irq(host->irq, host);

    for (int i = 0; i < host->ports_nr; ++i)
    {
        struct rt_ahci_port *port = &host->ports[i];

        if (port->ataid)
        {
            rt_free(port->ataid);
        }

        HWREG32(port->regs) &= ~(RT_AHCI_PORT_CMD_ACTIVE | RT_AHCI_PORT_CMD_POWER_ON |
                RT_AHCI_PORT_CMD_SPIN_UP | RT_AHCI_PORT_CMD_START);

        if (port->dma)
        {
            rt_dma_free_coherent(host->parent.dev, RT_AHCI_DMA_SIZE, port->dma,
                    port->dma_handle);
        }
    }

    HWREG32(host->regs + RT_AHCI_HBA_GHC) &= ~(RT_AHCI_GHC_AHCI_EN | RT_AHCI_GHC_IRQ_EN);

    return RT_EOK;
}
