/*
 * File      : drv_sdio.c
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include "drv_sdio.h"
#include "raspi.h"

static rt_uint32_t sdCommandTable[] = {
    SD_CMD_INDEX(0),
    SD_CMD_RESERVED(1),
    SD_CMD_INDEX(2) | SD_RESP_R2,
    SD_CMD_INDEX(3) | SD_RESP_R1,
    SD_CMD_INDEX(4),
    SD_CMD_RESERVED(5), //SD_CMD_INDEX(5) | SD_RESP_R4,
    SD_CMD_INDEX(6) | SD_RESP_R1,
    SD_CMD_INDEX(7) | SD_RESP_R1b,
    SD_CMD_INDEX(8) | SD_RESP_R1,
    SD_CMD_INDEX(9) | SD_RESP_R2,
    SD_CMD_INDEX(10) | SD_RESP_R2,
    SD_CMD_INDEX(11) | SD_RESP_R1,
    SD_CMD_INDEX(12) | SD_RESP_R1b | SD_CMD_TYPE_ABORT,
    SD_CMD_INDEX(13) | SD_RESP_R1,
    SD_CMD_RESERVED(14),
    SD_CMD_INDEX(15),
    SD_CMD_INDEX(16) | SD_RESP_R1,
    SD_CMD_INDEX(17) | SD_RESP_R1 | SD_DATA_READ,
    SD_CMD_INDEX(18) | SD_RESP_R1 | SD_DATA_READ | SD_CMD_MULTI_BLOCK | SD_CMD_BLKCNT_EN,
    SD_CMD_INDEX(19) | SD_RESP_R1 | SD_DATA_READ,
    SD_CMD_INDEX(20) | SD_RESP_R1b,
    SD_CMD_RESERVED(21),
    SD_CMD_RESERVED(22),
    SD_CMD_INDEX(23) | SD_RESP_R1,
    SD_CMD_INDEX(24) | SD_RESP_R1 | SD_DATA_WRITE,
    SD_CMD_INDEX(25) | SD_RESP_R1 | SD_DATA_WRITE | SD_CMD_MULTI_BLOCK | SD_CMD_BLKCNT_EN,
    SD_CMD_INDEX(26) | SD_RESP_R1 | SD_DATA_WRITE, //add
    SD_CMD_INDEX(27) | SD_RESP_R1 | SD_DATA_WRITE,
    SD_CMD_INDEX(28) | SD_RESP_R1b,
    SD_CMD_INDEX(29) | SD_RESP_R1b,
    SD_CMD_INDEX(30) | SD_RESP_R1 | SD_DATA_READ,
    SD_CMD_RESERVED(31),
    SD_CMD_INDEX(32) | SD_RESP_R1,
    SD_CMD_INDEX(33) | SD_RESP_R1,
    SD_CMD_RESERVED(34),
    SD_CMD_INDEX(35) | SD_RESP_R1, //add
    SD_CMD_INDEX(36) | SD_RESP_R1, //add
    SD_CMD_RESERVED(37),
    SD_CMD_INDEX(38) | SD_RESP_R1b,
    SD_CMD_INDEX(39) | SD_RESP_R4, //add
    SD_CMD_INDEX(40) | SD_RESP_R5, //add
    SD_CMD_INDEX(41) | SD_RESP_R3, //add, mov from harbote
    SD_CMD_RESERVED(42) | SD_RESP_R1,
    SD_CMD_RESERVED(43),
    SD_CMD_RESERVED(44),
    SD_CMD_RESERVED(45),
    SD_CMD_RESERVED(46),
    SD_CMD_RESERVED(47),
    SD_CMD_RESERVED(48),
    SD_CMD_RESERVED(49),
    SD_CMD_RESERVED(50),
    SD_CMD_INDEX(51) | SD_RESP_R1 | SD_DATA_READ,
    SD_CMD_RESERVED(52),
    SD_CMD_RESERVED(53),
    SD_CMD_RESERVED(54),
    SD_CMD_INDEX(55) | SD_RESP_R3,
    SD_CMD_INDEX(56) | SD_RESP_R1 | SD_CMD_ISDATA,
    SD_CMD_RESERVED(57),
    SD_CMD_RESERVED(58),
    SD_CMD_RESERVED(59),
    SD_CMD_RESERVED(60),
    SD_CMD_RESERVED(61),
    SD_CMD_RESERVED(62),
    SD_CMD_RESERVED(63)
};

static inline rt_uint32_t read32(rt_uint32_t addr)
{
    return (*((volatile unsigned int*)((rt_uint64_t)addr)));
    //return (*((volatile rt_uint64_t *)(((long))addr)));
}

static inline void write32(rt_uint32_t addr, rt_uint32_t value)
{
    (*((volatile unsigned int*)((rt_uint64_t)addr))) = value;
    //*((volatile rt_uint64_t *)(((long))addr)) = value;
}

rt_err_t sd_int(struct sdhci_pdata_t * pdat, unsigned int mask)
{
    unsigned int r;
    unsigned int m = mask | INT_ERROR_MASK;
    int cnt = 1000000;
    while (!(read32(pdat->virt + EMMC_INTERRUPT) & (m | INT_ERROR_MASK)) && cnt--)
        DELAY_MICROS(1);
    r = read32(pdat->virt + EMMC_INTERRUPT);
    if (cnt <= 0 || (r & INT_CMD_TIMEOUT) || (r & INT_DATA_TIMEOUT))
    {
        write32(pdat->virt + EMMC_INTERRUPT, r);
        //qemu maybe can not use sdcard
        //rt_kprintf("send cmd/data timeout wait for %x int: %x, status: %x\n",mask, r, read32(pdat->virt + EMMC_STATUS));
        //return -RT_ETIMEOUT;
    }
    else if (r & INT_ERROR_MASK)
    {
        write32(pdat->virt + EMMC_INTERRUPT, r);
        rt_kprintf("send cmd/data error %x -> %x\n",r, read32(pdat->virt + EMMC_INTERRUPT));
        return -RT_ERROR;
    }
    write32(pdat->virt + EMMC_INTERRUPT, mask);
    return RT_EOK;
}

rt_err_t sd_status(struct sdhci_pdata_t * pdat, unsigned int mask)
{
    int cnt = 500000;
    while ((read32(pdat->virt + EMMC_STATUS) & mask) && !(read32(pdat->virt + EMMC_INTERRUPT) & INT_ERROR_MASK) && cnt--)
        DELAY_MICROS(1);
    if (cnt <= 0)
    {
        return -RT_ETIMEOUT;
    }
    else if (read32(pdat->virt + EMMC_INTERRUPT) & INT_ERROR_MASK)
    {
        return  -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t raspi_transfer_command(struct sdhci_pdata_t * pdat, struct sdhci_cmd_t * cmd)
{
    rt_uint32_t cmdidx;
    rt_err_t ret = RT_EOK;
    ret = sd_status(pdat, SR_CMD_INHIBIT);
    if (ret)
    {
        rt_kprintf("ERROR: EMMC busy %d\n", ret);
        return ret;
    }

    cmdidx = sdCommandTable[cmd->cmdidx];
    if (cmdidx == 0xFFFFFFFF)
        return -RT_EINVAL;
    if (cmd->datarw == DATA_READ)
        cmdidx |= SD_DATA_READ;
    if (cmd->datarw == DATA_WRITE)
        cmdidx |= SD_DATA_WRITE;
    mmcsd_dbg("transfer cmd %x(%d) %x %x\n", cmdidx, cmd->cmdidx, cmd->cmdarg, read32(pdat->virt + EMMC_INTERRUPT));
    write32(pdat->virt + EMMC_INTERRUPT,read32(pdat->virt + EMMC_INTERRUPT));
    write32(pdat->virt + EMMC_ARG1, cmd->cmdarg);
    write32(pdat->virt + EMMC_CMDTM, cmdidx);
    if (cmd->cmdidx == SD_APP_OP_COND)
        DELAY_MICROS(1000);
    else if ((cmd->cmdidx == SD_SEND_IF_COND) || (cmd->cmdidx == APP_CMD))
        DELAY_MICROS(100);
    ret = sd_int(pdat, INT_CMD_DONE);
    if (ret)
    {
        return ret;
    }
    if (cmd->resptype & RESP_MASK)
    {

        if (cmd->resptype & RESP_R2)
        {
            rt_uint32_t resp[4];
            resp[0] = read32(pdat->virt + EMMC_RESP0);
            resp[1] = read32(pdat->virt + EMMC_RESP1);
            resp[2] = read32(pdat->virt + EMMC_RESP2);
            resp[3] = read32(pdat->virt + EMMC_RESP3);
            if (cmd->resptype == RESP_R2)
            {
                cmd->response[0] = resp[3]<<8 |((resp[2]>>24)&0xff);
                cmd->response[1] = resp[2]<<8 |((resp[1]>>24)&0xff);
                cmd->response[2] = resp[1]<<8 |((resp[0]>>24)&0xff);
                cmd->response[3] = resp[0]<<8 ;
            }
            else
            {
                cmd->response[0] = resp[0];
                cmd->response[1] = resp[1];
                cmd->response[2] = resp[2];
                cmd->response[3] = resp[3];
            }
        }
        else
            cmd->response[0] = read32(pdat->virt + EMMC_RESP0);
    }
    mmcsd_dbg("response: %x: %x %x %x %x (%x, %x)\n", cmd->resptype, cmd->response[0], cmd->response[1], cmd->response[2], cmd->response[3], read32(pdat->virt + EMMC_STATUS),read32(pdat->virt + EMMC_INTERRUPT));
    return ret;
}

static rt_err_t read_bytes(struct sdhci_pdata_t * pdat, rt_uint32_t * buf, rt_uint32_t blkcount, rt_uint32_t blksize)
{
    int c = 0;
    rt_err_t ret;
    int d;
    while (c < blkcount)
    {
        if ((ret = sd_int(pdat, INT_READ_RDY)))
        {
            rt_kprintf("timeout happens when reading block %d\n",c);
            return ret;
        }
        for (d=0; d < blksize / 4; d++)
            if (read32(pdat->virt + EMMC_STATUS) & SR_READ_AVAILABLE)
                buf[d] = read32(pdat->virt + EMMC_DATA);
        c++;
        buf += blksize / 4;
    }
    return RT_EOK;
}

static rt_err_t write_bytes(struct sdhci_pdata_t * pdat, rt_uint32_t * buf, rt_uint32_t blkcount, rt_uint32_t blksize)
{
    int c = 0;
    rt_err_t ret;
    int d;
    while (c < blkcount)
    {
        if ((ret = sd_int(pdat, INT_WRITE_RDY)))
        {
            return ret;
        }
        for (d=0; d < blksize / 4; d++)
            write32(pdat->virt + EMMC_DATA, buf[d]);
        c++;
        buf += blksize / 4;
    }
    if ((ret = sd_int(pdat, INT_DATA_DONE)))
    {
        return ret;
    }
    return RT_EOK;
}

static rt_err_t raspi_transfer_data(struct sdhci_pdata_t * pdat, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat)
{
    rt_uint32_t dlen = (rt_uint32_t)(dat->blkcnt * dat->blksz);
    rt_err_t ret = sd_status(pdat, SR_DAT_INHIBIT);
    if (ret)
    {
        rt_kprintf("ERROR: EMMC busy\n");
        return ret;
    }
    if (dat->blkcnt > 1)
    {
        struct sdhci_cmd_t newcmd;
        newcmd.cmdidx = SET_BLOCK_COUNT;
        newcmd.cmdarg = dat->blkcnt;
        newcmd.resptype = RESP_R1;
        ret = raspi_transfer_command(pdat, &newcmd);
        if (ret) return ret;
    }

    if(dlen < 512)
    {
        write32(pdat->virt + EMMC_BLKSIZECNT, dlen | 1 << 16);
    }
    else
    {
        write32(pdat->virt + EMMC_BLKSIZECNT, 512 | (dat->blkcnt) << 16);
    }
    if (dat->flag & DATA_DIR_READ)
    {
        cmd->datarw = DATA_READ;
        ret = raspi_transfer_command(pdat, cmd);
        if (ret) return ret;
        mmcsd_dbg("read_block %d, %d\n", dat->blkcnt, dat->blksz );
        ret = read_bytes(pdat, (rt_uint32_t *)dat->buf, dat->blkcnt, dat->blksz);
    }
    else if (dat->flag & DATA_DIR_WRITE)
    {
        cmd->datarw = DATA_WRITE;
        ret = raspi_transfer_command(pdat, cmd);
        if (ret) return ret;
        mmcsd_dbg("write_block %d, %d", dat->blkcnt, dat->blksz );
        ret = write_bytes(pdat, (rt_uint32_t *)dat->buf, dat->blkcnt, dat->blksz);
    }
    return ret;
}

static rt_err_t sdhci_transfer(struct sdhci_t * sdhci, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat)
{
    struct sdhci_pdata_t * pdat = (struct sdhci_pdata_t *)sdhci->priv;
    if (!dat)
        return raspi_transfer_command(pdat, cmd);

    return raspi_transfer_data(pdat, cmd, dat);
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
    cmd.resptype =resp_type(req->cmd);
    if (req->data)
    {
        dat.buf = (rt_uint8_t *)req->data->buf;
        dat.flag = req->data->flags;
        dat.blksz = req->data->blksize;
        dat.blkcnt = req->data->blks;

        req->cmd->err = sdhci_transfer(sdhci, &cmd, &dat);
    }
    else
    {
        req->cmd->err = sdhci_transfer(sdhci, &cmd, RT_NULL);
    }

    req->cmd->resp[3] = cmd.response[3];
    req->cmd->resp[2] = cmd.response[2];
    req->cmd->resp[1] = cmd.response[1];
    req->cmd->resp[0] = cmd.response[0];

    if (req->stop)
    {
        stop.cmdidx = req->stop->cmd_code;
        stop.cmdarg = req->stop->arg;
        cmd.resptype =resp_type(req->stop);
        req->stop->err = sdhci_transfer(sdhci, &stop, RT_NULL);
    }

    mmcsd_req_complete(host);
}

rt_int32_t mmc_card_status(struct rt_mmcsd_host *host)
{
    return 0;
}

void mmc_enable_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{

}

static rt_err_t sdhci_detect(struct sdhci_t * sdhci)
{
    return RT_EOK;
}

static rt_err_t sdhci_setwidth(struct sdhci_t * sdhci, rt_uint32_t width)
{
    rt_uint32_t temp = 0;
    struct sdhci_pdata_t * pdat = (struct sdhci_pdata_t *)sdhci->priv;
    if (width == MMCSD_BUS_WIDTH_4)
    {
        temp = read32((pdat->virt + EMMC_CONTROL0));
        temp |= C0_HCTL_HS_EN;
        temp |= C0_HCTL_DWITDH;   // always use 4 data lines:
        write32((pdat->virt + EMMC_CONTROL0), temp);
    }
    return RT_EOK;
}

static rt_uint32_t sdhci_getdivider(rt_uint32_t sdHostVer, rt_uint32_t freq)
{
    rt_uint32_t divisor;
    rt_uint32_t closest = 41666666 / freq;
    rt_uint32_t shiftcount = __rt_fls(closest - 1);


    if (shiftcount > 0) shiftcount--;
    if (shiftcount > 7) shiftcount = 7;
    if (sdHostVer > HOST_SPEC_V2)
        divisor = closest;
    else
        divisor = (1 << shiftcount);

    if (divisor <= 2)
    {
        divisor = 2;
        shiftcount = 0;
    }

    rt_uint32_t hi = 0;
    if (sdHostVer > HOST_SPEC_V2)
        hi = (divisor & 0x300) >> 2;
    rt_uint32_t lo = (divisor & 0x0ff);
    rt_uint32_t cdiv = (lo << 8) + hi;
    return cdiv;
}

static rt_err_t sdhci_setclock(struct sdhci_t * sdhci, rt_uint32_t clock)
{
    rt_uint32_t temp = 0;
    rt_uint32_t sdHostVer = 0;
    int count = 100000;
    struct sdhci_pdata_t * pdat = (struct sdhci_pdata_t *)(sdhci->priv);

    while ((read32(pdat->virt + EMMC_STATUS) & (SR_CMD_INHIBIT | SR_DAT_INHIBIT)) && (--count))
        DELAY_MICROS(1);
    if (count <= 0)
    {
        rt_kprintf("EMMC: Set clock: timeout waiting for inhibit flags. Status %08x.\n",read32(pdat->virt + EMMC_STATUS));
        return RT_ERROR;
    }

    // Switch clock off.
    temp = read32((pdat->virt + EMMC_CONTROL1));
    temp &= ~C1_CLK_EN;
    write32((pdat->virt + EMMC_CONTROL1),temp);
    DELAY_MICROS(10);
    // Request the new clock setting and enable the clock
    temp = read32(pdat->virt + EMMC_SLOTISR_VER);
    sdHostVer = (temp & HOST_SPEC_NUM) >> HOST_SPEC_NUM_SHIFT;
    int cdiv = sdhci_getdivider(sdHostVer, clock);
    temp = read32((pdat->virt + EMMC_CONTROL1));
    temp = (temp & 0xffff003f) | cdiv;
    write32((pdat->virt + EMMC_CONTROL1),temp);
    DELAY_MICROS(10);

    // Enable the clock.
    temp = read32(pdat->virt + EMMC_CONTROL1);
    temp |= C1_CLK_EN;
    write32((pdat->virt + EMMC_CONTROL1),temp);
    DELAY_MICROS(10);
    // Wait for clock to be stable.
    count = 10000;
    while (!(read32(pdat->virt + EMMC_CONTROL1) & C1_CLK_STABLE) && count--)
        DELAY_MICROS(10);
    if (count <= 0)
    {
        rt_kprintf("EMMC: ERROR: failed to get stable clock %d.\n", clock);
        return RT_ERROR;
    }
    mmcsd_dbg("set stable clock %d.\n", clock);
    return RT_EOK;
}

static void mmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    struct sdhci_t * sdhci = (struct sdhci_t *)host->private_data;
    sdhci_setclock(sdhci, io_cfg->clock);
    sdhci_setwidth(sdhci, io_cfg->bus_width);
}

static const struct rt_mmcsd_host_ops ops =
{
    mmc_request_send,
    mmc_set_iocfg,
    RT_NULL,
    RT_NULL,
};

static void sdmmc_gpio_init()
{
//    int pin;
//    bcm283x_gpio_fsel(47,BCM283X_GPIO_FSEL_INPT);
//    bcm283x_gpio_set_pud(47, BCM283X_GPIO_PUD_UP);
//    bcm283x_peri_set_bits(BCM283X_GPIO_BASE + BCM283X_GPIO_GPHEN1, 1<<15, 1<<15);
//    for (pin = 53; pin >= 48; pin--)
//    {
//        bcm283x_gpio_fsel(pin, BCM283X_GPIO_FSEL_ALT3);
//        bcm283x_gpio_set_pud(pin, BCM283X_GPIO_PUD_UP);
//    }
}

static rt_err_t reset_emmc(struct sdhci_pdata_t * pdat){
    rt_uint32_t temp;
    int cnt;
    write32((pdat->virt + EMMC_CONTROL0),0);
    temp = read32((pdat->virt + EMMC_CONTROL1));
    temp |= C1_SRST_HC;
    write32((pdat->virt + EMMC_CONTROL1),temp);
    cnt = 10000;
    do
    {
        DELAY_MICROS(10);
    }
    while ((read32((pdat->virt + EMMC_CONTROL1)) & C1_SRST_HC) && cnt--);
    if (cnt <= 0)
    {
        rt_kprintf("ERROR: failed to reset EMMC\n");
        return RT_ERROR;
    }
    temp = read32((pdat->virt + EMMC_CONTROL1));
    temp |= C1_CLK_INTLEN | C1_TOUNIT_MAX;
    write32((pdat->virt + EMMC_CONTROL1),temp);
    DELAY_MICROS(10);
    return RT_EOK;
}

#ifdef RT_MMCSD_DBG
void dump_registers(struct sdhci_pdata_t * pdat){
    rt_kprintf("EMMC registers:");
    int i = EMMC_ARG2;
    for (; i <= EMMC_CONTROL2; i += 4)
        rt_kprintf("\t%x:%x\n", i, read32(pdat->virt + i));
    rt_kprintf("\t%x:%x\n", 0x50, read32(pdat->virt + 0x50));
    rt_kprintf("\t%x:%x\n", 0x70, read32(pdat->virt + 0x70));
    rt_kprintf("\t%x:%x\n", 0x74, read32(pdat->virt + 0x74));
    rt_kprintf("\t%x:%x\n", 0x80, read32(pdat->virt + 0x80));
    rt_kprintf("\t%x:%x\n", 0x84, read32(pdat->virt + 0x84));
    rt_kprintf("\t%x:%x\n", 0x88, read32(pdat->virt + 0x88));
    rt_kprintf("\t%x:%x\n", 0x8c, read32(pdat->virt + 0x8c));
    rt_kprintf("\t%x:%x\n", 0x90, read32(pdat->virt + 0x90));
    rt_kprintf("\t%x:%x\n", 0xf0, read32(pdat->virt + 0xf0));
    rt_kprintf("\t%x:%x\n", 0xfc, read32(pdat->virt + 0xfc));
}
#endif

int raspi_sdmmc_init(void)
{
    rt_uint32_t virt;
    struct rt_mmcsd_host * host = RT_NULL;
    struct sdhci_pdata_t * pdat = RT_NULL;
    struct sdhci_t * sdhci = RT_NULL;
#ifdef BSP_USING_SDIO0
    host = mmcsd_alloc_host();
    if (!host)
    {
        rt_kprintf("alloc host failed");
        goto err;
    }

    sdhci = rt_malloc(sizeof(struct sdhci_t));
    if (!sdhci)
    {
        rt_kprintf("alloc sdhci failed");
        goto err;
    }
    rt_memset(sdhci, 0, sizeof(struct sdhci_t));

    sdmmc_gpio_init();
    virt = MMC0_BASE_ADDR;

    pdat = (struct sdhci_pdata_t *)rt_malloc(sizeof(struct sdhci_pdata_t));
    RT_ASSERT(pdat != RT_NULL);

    pdat->virt = (rt_uint32_t)virt;
    reset_emmc(pdat);

    sdhci->name = "sd0";
    sdhci->voltages = VDD_33_34;
    sdhci->width = MMCSD_BUSWIDTH_4;
    sdhci->clock = 200 * 1000 * 1000;
    sdhci->removeable = RT_TRUE;

    sdhci->detect = sdhci_detect;
    sdhci->setwidth = sdhci_setwidth;
    sdhci->setclock = sdhci_setclock;
    sdhci->transfer = sdhci_transfer;
    sdhci->priv = pdat;

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

    write32((pdat->virt + EMMC_IRPT_EN),0xffffffff);
    write32((pdat->virt + EMMC_IRPT_MASK),0xffffffff);
#ifdef RT_MMCSD_DBG
    dump_registers(pdat);
#endif
    mmcsd_change(host);
#endif
    return RT_EOK;

err:
    if (host)  rt_free(host);
    if (sdhci) rt_free(sdhci);

    return -RT_EIO;
}

INIT_DEVICE_EXPORT(raspi_sdmmc_init);
