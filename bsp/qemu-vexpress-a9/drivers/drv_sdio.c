#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/mmcsd_core.h>

#include <stdint.h>
#include <stdio.h>

#include "drv_sdio.h"

#ifdef RT_USING_SDIO

#define MMC_BASE_ADDR    (0x10005000)

#define PL180_POWER             (0x00)
#define PL180_CLOCK             (0x04)
#define PL180_ARGUMENT          (0x08)
#define PL180_COMMAND           (0x0c)
#define PL180_RESPCMD           (0x10)
#define PL180_RESP0             (0x14)
#define PL180_RESP1             (0x18)
#define PL180_RESP2             (0x1c)
#define PL180_RESP3             (0x20)
#define PL180_DATA_TIMER        (0x24)
#define PL180_DATA_LENGTH       (0x28)
#define PL180_DATA_CTRL         (0x2c)
#define PL180_DATA_CNT          (0x30)
#define PL180_STATUS            (0x34)
#define PL180_CLEAR             (0x38)
#define PL180_MASK0             (0x3c)
#define PL180_MASK1             (0x40)
#define PL180_SELECT            (0x44)
#define PL180_FIFO_CNT          (0x48)
#define PL180_FIFO              (0x80)

#define PL180_RSP_NONE          (0 << 0)
#define PL180_RSP_PRESENT       (1 << 0)
#define PL180_RSP_136BIT        (1 << 1)
#define PL180_RSP_CRC           (1 << 2)

#define PL180_CMD_WAITRESP      (1 << 6)
#define PL180_CMD_LONGRSP       (1 << 7)
#define PL180_CMD_WAITINT       (1 << 8)
#define PL180_CMD_WAITPEND      (1 << 9)
#define PL180_CMD_ENABLE        (1 << 10)

#define PL180_STAT_CMD_CRC_FAIL (1 << 0)
#define PL180_STAT_DAT_CRC_FAIL (1 << 1)
#define PL180_STAT_CMD_TIME_OUT (1 << 2)
#define PL180_STAT_DAT_TIME_OUT (1 << 3)
#define PL180_STAT_TX_UNDERRUN  (1 << 4)
#define PL180_STAT_RX_OVERRUN   (1 << 5)
#define PL180_STAT_CMD_RESP_END (1 << 6)
#define PL180_STAT_CMD_SENT     (1 << 7)
#define PL180_STAT_DAT_END      (1 << 8)
#define PL180_STAT_DAT_BLK_END  (1 << 10)
#define PL180_STAT_CMD_ACT      (1 << 11)
#define PL180_STAT_TX_ACT       (1 << 12)
#define PL180_STAT_RX_ACT       (1 << 13)
#define PL180_STAT_TX_FIFO_HALF (1 << 14)
#define PL180_STAT_RX_FIFO_HALF (1 << 15)
#define PL180_STAT_TX_FIFO_FULL (1 << 16)
#define PL180_STAT_RX_FIFO_FULL (1 << 17)
#define PL180_STAT_TX_FIFO_ZERO (1 << 18)
#define PL180_STAT_RX_DAT_ZERO  (1 << 19)
#define PL180_STAT_TX_DAT_AVL   (1 << 20)
#define PL180_STAT_RX_FIFO_AVL  (1 << 21)

#define PL180_CLR_CMD_CRC_FAIL  (1 << 0)
#define PL180_CLR_DAT_CRC_FAIL  (1 << 1)
#define PL180_CLR_CMD_TIMEOUT   (1 << 2)
#define PL180_CLR_DAT_TIMEOUT   (1 << 3)
#define PL180_CLR_TX_UNDERRUN   (1 << 4)
#define PL180_CLR_RX_OVERRUN    (1 << 5)
#define PL180_CLR_CMD_RESP_END  (1 << 6)
#define PL180_CLR_CMD_SENT      (1 << 7)
#define PL180_CLR_DAT_END       (1 << 8)
#define PL180_CLR_DAT_BLK_END   (1 << 10)

#define DBG_TAG "drv.sdio"
#define DBG_LVL DBG_INFO
#include "rtdbg.h"

struct sdhci_pl180_pdata_t
{
    rt_uint32_t virt;
};

static inline rt_uint32_t read32(uint32_t addr)
{
    return( *((volatile rt_uint32_t *)(addr)) );
}

static inline void write32(uint32_t addr, rt_uint32_t value)
{
    *((volatile rt_uint32_t *)(addr)) = value;
}

static rt_err_t pl180_transfer_command(struct sdhci_pl180_pdata_t * pdat, struct sdhci_cmd_t * cmd)
{
    rt_uint32_t cmdidx;
    rt_uint32_t status;
    rt_err_t ret = RT_EOK;

    if(read32(pdat->virt + PL180_COMMAND) & PL180_CMD_ENABLE)
        write32(pdat->virt + PL180_COMMAND, 0x0);

    cmdidx = (cmd->cmdidx & 0xff) | PL180_CMD_ENABLE;
    if(cmd->resptype)
    {
        cmdidx |= PL180_CMD_WAITRESP;
        if(cmd->resptype & PL180_RSP_136BIT)
            cmdidx |= PL180_CMD_LONGRSP;
    }

    write32(pdat->virt + PL180_ARGUMENT, cmd->cmdarg);
    write32(pdat->virt + PL180_COMMAND, cmdidx);

    do {
        status = read32(pdat->virt + PL180_STATUS);
    } while(!(status & (PL180_STAT_CMD_SENT | PL180_STAT_CMD_RESP_END | PL180_STAT_CMD_TIME_OUT | PL180_STAT_CMD_CRC_FAIL)));
    LOG_D("mmc status done!");

    if(cmd->resptype & PL180_RSP_PRESENT)
    {
        cmd->response[0] = read32(pdat->virt + PL180_RESP0);
        if(cmd->resptype & PL180_RSP_136BIT)
        {
            LOG_D("136bit response");
            cmd->response[1] = read32(pdat->virt + PL180_RESP1);
            cmd->response[2] = read32(pdat->virt + PL180_RESP2);
            cmd->response[3] = read32(pdat->virt + PL180_RESP3);
        }
    }

    if(status & PL180_STAT_CMD_TIME_OUT)
    {
        ret = -RT_ETIMEOUT;
    }
    else if ((status & PL180_STAT_CMD_CRC_FAIL) && (cmd->resptype & PL180_RSP_CRC))
    {
        ret = -RT_ERROR;
    }

    write32(pdat->virt + PL180_CLEAR, (PL180_CLR_CMD_SENT | PL180_CLR_CMD_RESP_END | PL180_CLR_CMD_TIMEOUT | PL180_CLR_CMD_CRC_FAIL));
    return ret;
}

static rt_err_t read_bytes(struct sdhci_pl180_pdata_t * pdat, rt_uint32_t * buf, rt_uint32_t blkcount, rt_uint32_t blksize)
{
    rt_uint32_t * tmp = buf;
    rt_uint32_t count = blkcount * blksize;
    rt_uint32_t status, err;

    status = read32(pdat->virt + PL180_STATUS);
    err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_RX_OVERRUN);
    while((!err) && (count >= sizeof(rt_uint32_t)))
    {
        if(status & PL180_STAT_RX_FIFO_AVL)
        {
            *(tmp) = read32(pdat->virt + PL180_FIFO);
            tmp++;
            count -= sizeof(rt_uint32_t);
        }
        status = read32(pdat->virt + PL180_STATUS);
        err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_RX_OVERRUN);
    }

    err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_DAT_BLK_END | PL180_STAT_RX_OVERRUN);
    while(!err)
    {
        status = read32(pdat->virt + PL180_STATUS);
        err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_DAT_BLK_END | PL180_STAT_RX_OVERRUN);
    }

    if(status & PL180_STAT_DAT_TIME_OUT)
        return -RT_ERROR;
    else if (status & PL180_STAT_DAT_CRC_FAIL)
        return -RT_ERROR;
    else if (status & PL180_STAT_RX_OVERRUN)
        return -RT_ERROR;
    write32(pdat->virt + PL180_CLEAR, 0x1DC007FF);

    if(count)
        return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t write_bytes(struct sdhci_pl180_pdata_t * pdat, rt_uint32_t * buf, rt_uint32_t blkcount, rt_uint32_t blksize)
{
    rt_uint32_t * tmp = buf;
    rt_uint32_t count = blkcount * blksize;
    rt_uint32_t status, err;
    int i;

    status = read32(pdat->virt + PL180_STATUS);
    err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT);
    while(!err && count)
    {
        if(status & PL180_STAT_TX_FIFO_HALF)
        {
            if(count >= 8 * sizeof(rt_uint32_t))
            {
                for(i = 0; i < 8; i++)
                    write32(pdat->virt + PL180_FIFO, *(tmp + i));
                tmp += 8;
                count -= 8 * sizeof(rt_uint32_t);
            }
            else
            {
                while(count >= sizeof(rt_uint32_t))
                {
                    write32(pdat->virt + PL180_FIFO, *tmp);
                    tmp++;
                    count -= sizeof(rt_uint32_t);
                }
            }
        }
        status = read32(pdat->virt + PL180_STATUS);
        err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT);
    }

    err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_DAT_BLK_END);
    while(!err)
    {
        status = read32(pdat->virt + PL180_STATUS);
        err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_DAT_BLK_END);
    }

    if(status & PL180_STAT_DAT_TIME_OUT)
        return -RT_ERROR;
    else if (status & PL180_STAT_DAT_CRC_FAIL)
        return -RT_ERROR;
    write32(pdat->virt + PL180_CLEAR, 0x1DC007FF);

    if(count)
        return -RT_ERROR;
    return RT_EOK;
}

static rt_err_t pl180_transfer_data(struct sdhci_pl180_pdata_t * pdat, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat)
{
    rt_uint32_t dlen = (rt_uint32_t)(dat->blkcnt * dat->blksz);
    rt_uint32_t blksz_bits = dat->blksz - 1;
    rt_uint32_t dctrl = (blksz_bits << 4) | (0x1 << 0) | (0x1 << 14);
    rt_err_t ret = -RT_ERROR;

    write32(pdat->virt + PL180_DATA_TIMER, 0xffff);
    write32(pdat->virt + PL180_DATA_LENGTH, dlen);

    if(dat->flag & DATA_DIR_READ)
    {
        dctrl |= (0x1 << 1);
        write32(pdat->virt + PL180_DATA_CTRL, dctrl);
        ret = pl180_transfer_command(pdat, cmd);
        if (ret < 0) return ret;
        ret = read_bytes(pdat, (rt_uint32_t *)dat->buf, dat->blkcnt, dat->blksz);
    }
    else if(dat->flag & DATA_DIR_WRITE)
    {
        ret = pl180_transfer_command(pdat, cmd);
        if (ret < 0) return ret;
        write32(pdat->virt + PL180_DATA_CTRL, dctrl);
        ret = write_bytes(pdat, (rt_uint32_t *)dat->buf, dat->blkcnt, dat->blksz);
    }

    return ret;
}

static rt_err_t sdhci_pl180_detect(struct sdhci_t * sdhci)
{
    return RT_EOK;
}

static rt_err_t sdhci_pl180_setwidth(struct sdhci_t * sdhci, rt_uint32_t width)
{
    return RT_EOK;
}

static rt_err_t sdhci_pl180_setclock(struct sdhci_t * sdhci, rt_uint32_t clock)
{
    rt_uint32_t temp = 0;
    struct sdhci_pl180_pdata_t * pdat = (struct sdhci_pl180_pdata_t *)sdhci->priv;

    if(clock)
    {
        temp = read32(pdat->virt + PL180_CLOCK) | (0x1<<8);
        temp = temp; // skip warning 
        write32(pdat->virt + PL180_CLOCK, 0x100);
    }
    else
    {
        //write32(pdat->virt + PL180_CLOCK, read32(pdat->virt + PL180_CLOCK) & (~(0x1<<8)));
    }
    return RT_EOK;
}

static rt_err_t sdhci_pl180_transfer(struct sdhci_t * sdhci, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat)
{
    struct sdhci_pl180_pdata_t * pdat = (struct sdhci_pl180_pdata_t *)sdhci->priv;

    if(!dat)
        return pl180_transfer_command(pdat, cmd);

    return pl180_transfer_data(pdat, cmd, dat);
}

static void mmc_request_send(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct sdhci_t *sdhci = (struct sdhci_t *)host->private_data;
    struct sdhci_cmd_t cmd;
    struct sdhci_cmd_t stop;
    struct sdhci_data_t dat;

    rt_memset(&cmd, 0, sizeof(struct sdhci_cmd_t));
    rt_memset(&stop, 0, sizeof(struct sdhci_cmd_t));
    rt_memset(&dat, 0, sizeof(struct sdhci_data_t));

    cmd.cmdidx = req->cmd->cmd_code;
    cmd.cmdarg = req->cmd->arg;
    if (req->cmd->flags & RESP_MASK)
    {
        cmd.resptype = PL180_RSP_PRESENT;
        if (resp_type(req->cmd) == RESP_R2)
            cmd.resptype |= PL180_RSP_136BIT;
    }
    else
        cmd.resptype = 0;

    if(req->data)
    {
        dat.buf = (rt_uint8_t *)req->data->buf;
        dat.flag = req->data->flags;
        dat.blksz = req->data->blksize;
        dat.blkcnt = req->data->blks;

        req->cmd->err = sdhci_pl180_transfer(sdhci, &cmd, &dat);
    }
    else
    {
        req->cmd->err = sdhci_pl180_transfer(sdhci, &cmd, RT_NULL);
    }

    LOG_D("cmdarg:%d", cmd.cmdarg);
    LOG_D("cmdidx:%d", cmd.cmdidx);

    LOG_D("[0]:0x%08x [1]:0x%08x [2]:0x%08x [3]:0x%08x", cmd.response[0], cmd.response[1], cmd.response[2], cmd.response[3]);
    req->cmd->resp[3] = cmd.response[3];
    req->cmd->resp[2] = cmd.response[2];
    req->cmd->resp[1] = cmd.response[1];
    req->cmd->resp[0] = cmd.response[0];

    if (req->stop)
    {
        stop.cmdidx = req->stop->cmd_code;
        stop.cmdarg = req->stop->arg;
        if (req->stop->flags & RESP_MASK)
        {
            stop.resptype = PL180_RSP_PRESENT;
            if (resp_type(req->stop) == RESP_R2)
                stop.resptype |= PL180_RSP_136BIT;
        }
        else
            stop.resptype = 0;

        req->stop->err = sdhci_pl180_transfer(sdhci, &stop, RT_NULL);
    }

    mmcsd_req_complete(host);
}

static void mmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    struct sdhci_t * sdhci = (struct sdhci_t *)host->private_data;

    sdhci_pl180_setclock(sdhci, io_cfg->clock);
    sdhci_pl180_setwidth(sdhci, io_cfg->bus_width);
    LOG_D("clock:%d bus_width:%d", io_cfg->clock, io_cfg->bus_width);
}

static const struct rt_mmcsd_host_ops ops = 
{
    mmc_request_send,
    mmc_set_iocfg,
    RT_NULL,
    RT_NULL,
};

int pl180_init(void)
{
    rt_uint32_t virt;
    rt_uint32_t id;
    struct rt_mmcsd_host * host = RT_NULL;
    struct sdhci_pl180_pdata_t * pdat = RT_NULL;
    struct sdhci_t * sdhci = RT_NULL;

    host = mmcsd_alloc_host();
    if (!host)
    {
        LOG_E("alloc host failed");
        goto err;
    }

    sdhci = rt_malloc(sizeof(struct sdhci_t));
    if (!sdhci)
    {
        LOG_E("alloc sdhci failed");
        goto err;
    }
    rt_memset(sdhci, 0, sizeof(struct sdhci_t));

    virt = MMC_BASE_ADDR;
    id = (((read32((virt + 0xfec)) & 0xff) << 24) |
                ((read32((virt + 0xfe8)) & 0xff) << 16) |
                ((read32((virt + 0xfe4)) & 0xff) <<  8) |
                ((read32((virt + 0xfe0)) & 0xff) <<  0));

    LOG_D("id=0x%08x", id);
    if(((id >> 12) & 0xff) != 0x41 || (id & 0xfff) != 0x181)
    {
        LOG_E("check id  failed");
        goto err;
    }

    pdat = (struct sdhci_pl180_pdata_t *)rt_malloc(sizeof(struct sdhci_pl180_pdata_t));
    RT_ASSERT(pdat != RT_NULL);

    pdat->virt = (uint32_t)virt;

    sdhci->name = "sd0";
    sdhci->voltages = VDD_33_34;
    sdhci->width = MMCSD_BUSWIDTH_4;
    sdhci->clock = 26 * 1000 * 1000;
    sdhci->removeable = RT_TRUE;
    sdhci->detect = sdhci_pl180_detect;
    sdhci->setwidth = sdhci_pl180_setwidth;
    sdhci->setclock = sdhci_pl180_setclock;
    sdhci->transfer = sdhci_pl180_transfer;
    sdhci->priv = pdat;
    write32(pdat->virt + PL180_POWER, 0xbf);

    host->ops = &ops;
    host->freq_min = 400000;
    host->freq_max = 50000000;
    host->valid_ocr = VDD_32_33 | VDD_33_34;
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ | MMCSD_BUSWIDTH_4;
    host->max_seg_size = 2048;
    host->max_dma_segs = 10;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;

    host->private_data = sdhci;

    mmcsd_change(host);

    return RT_EOK;

err:
    if(host)  rt_free(host);
    if(sdhci) rt_free(sdhci);

    return -RT_EIO;
}
INIT_DEVICE_EXPORT(pl180_init);

#endif
