/*
 * File      : drv_sdio.c
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <string.h>

#include "drv_sdio.h"
#include "interrupt.h"
#include "drv_gpio.h"

#include "bcm283x.h"
#include <drivers/mmcsd_core.h>
#include "bcm283x.h"


#include <rtdbg.h>

#ifdef RT_USING_SDIO
#define CONFIG_MMC_USE_DMA
#define DMA_ALIGN       (32U)

typedef struct EMMCCommand
{
    const char* name;
    unsigned int code;
    unsigned char resp;
    unsigned char rca;
    int delay;
} EMMCCommand;

static EMMCCommand sdCommandTable[] =
{
    {"GO_IDLE_STATE", 0x00000000 | CMD_RSPNS_NO                             , RESP_NO , RCA_NO  ,0},
    {"ALL_SEND_CID" , 0x02000000 | CMD_RSPNS_136                            , RESP_R2I, RCA_NO  ,0},
    {"SEND_REL_ADDR", 0x03000000 | CMD_RSPNS_48                             , RESP_R6 , RCA_NO  ,0},
    {"SET_DSR"      , 0x04000000 | CMD_RSPNS_NO                             , RESP_NO , RCA_NO  ,0},
    {"SWITCH_FUNC"  , 0x06000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"CARD_SELECT"  , 0x07000000 | CMD_RSPNS_48B                            , RESP_R1b, RCA_YES ,0},
    {"SEND_IF_COND" , 0x08000000 | CMD_RSPNS_48                             , RESP_R7 , RCA_NO  ,100},
    {"SEND_CSD"     , 0x09000000 | CMD_RSPNS_136                            , RESP_R2S, RCA_YES ,0},
    {"SEND_CID"     , 0x0A000000 | CMD_RSPNS_136                            , RESP_R2I, RCA_YES ,0},
    {"VOLT_SWITCH"  , 0x0B000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"STOP_TRANS"   , 0x0C000000 | CMD_RSPNS_48B                            , RESP_R1b, RCA_NO  ,0},
    {"SEND_STATUS"  , 0x0D000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_YES ,0},
    {"GO_INACTIVE"  , 0x0F000000 | CMD_RSPNS_NO                             , RESP_NO , RCA_YES ,0},
    {"SET_BLOCKLEN" , 0x10000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"READ_SINGLE"  , 0x11000000 | CMD_RSPNS_48 | CMD_IS_DATA   | TM_DAT_DIR_CH, RESP_R1 , RCA_NO  ,0},
    {"READ_MULTI"   , 0x12000000 | CMD_RSPNS_48 | TM_MULTI_DATA | TM_DAT_DIR_CH, RESP_R1 , RCA_NO  ,0},
    {"SEND_TUNING"  , 0x13000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"SPEED_CLASS"  , 0x14000000 | CMD_RSPNS_48B                            , RESP_R1b, RCA_NO  ,0},
    {"SET_BLOCKCNT" , 0x17000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"WRITE_SINGLE" , 0x18000000 | CMD_RSPNS_48 | CMD_IS_DATA   | TM_DAT_DIR_HC, RESP_R1 , RCA_NO  ,0},
    {"WRITE_MULTI"  , 0x19000000 | CMD_RSPNS_48 | TM_MULTI_DATA | TM_DAT_DIR_HC, RESP_R1 , RCA_NO  ,0},
    {"PROGRAM_CSD"  , 0x1B000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"SET_WRITE_PR" , 0x1C000000 | CMD_RSPNS_48B                            , RESP_R1b, RCA_NO  ,0},
    {"CLR_WRITE_PR" , 0x1D000000 | CMD_RSPNS_48B                            , RESP_R1b, RCA_NO  ,0},
    {"SND_WRITE_PR" , 0x1E000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"ERASE_WR_ST"  , 0x20000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"ERASE_WR_END" , 0x21000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"ERASE"        , 0x26000000 | CMD_RSPNS_48B                            , RESP_R1b, RCA_NO  ,0},
    {"LOCK_UNLOCK"  , 0x2A000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"APP_CMD"      , 0x37000000 | CMD_RSPNS_NO                             , RESP_NO , RCA_NO  ,100},
    {"APP_CMD"      , 0x37000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_YES ,0},
    {"GEN_CMD"      , 0x38000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},

  // APP commands must be prefixed by an APP_CMD.
    {"SET_BUS_WIDTH", 0x06000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"SD_STATUS"    , 0x0D000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_YES ,0}, // RCA???
    {"SEND_NUM_WRBL", 0x16000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"SEND_NUM_ERS" , 0x17000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"SD_SENDOPCOND", 0x29000000 | CMD_RSPNS_48                             , RESP_R3 , RCA_NO  ,1000},
    {"SET_CLR_DET"  , 0x2A000000 | CMD_RSPNS_48                             , RESP_R1 , RCA_NO  ,0},
    {"SEND_SCR"     , 0x33000000 | CMD_RSPNS_48 | CMD_IS_DATA | TM_DAT_DIR_CH   , RESP_R1 , RCA_NO  ,0},
};

static rt_err_t sdhci_setwidth(struct sdhci_t * sdhci, rt_uint32_t width);
static rt_err_t sdhci_setclock(struct sdhci_t * sdhci, rt_uint32_t clock);
static rt_err_t sdhci_transfer(struct sdhci_t * sdhci, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat);

static inline rt_uint32_t read32(rt_uint32_t addr)
{
    return( *((volatile rt_uint32_t *)(addr)) );
}

static inline void write32(rt_uint32_t addr, rt_uint32_t value)
{
    *((volatile rt_uint32_t *)(addr)) = value;
}

static rt_err_t raspi_transfer_command(struct sdhci_pdata_t * pdat, struct sdhci_cmd_t * cmd)
{
    rt_uint32_t cmdidx;
    rt_uint32_t status;
    rt_err_t ret = RT_EOK;

    if(read32(pdat->virt + EMMC_STATUS) & SR_CMD_INHIBIT)
        write32(pdat->virt + EMMC_CMDTM, 0x0);

    EMMCCommand* cmdtab = &sdCommandTable[cmd->cmdidx];

    cmdidx = cmdtab->code;

    write32(pdat->virt + EMMC_ARG1, cmd->cmdarg);
    write32(pdat->virt + EMMC_CMDTM, cmdidx);

    do {
        status = read32(pdat->virt + EMMC_STATUS);
    } while(!(status & SR_CMD_INHIBIT));

    if(cmd->resptype & RESP_MASK)
    {
        cmd->response[0] = read32(pdat->virt + EMMC_RESP0);
        if(cmd->resptype & RESP_R2)
        {
            cmd->response[1] = read32(pdat->virt + EMMC_RESP1);
            cmd->response[2] = read32(pdat->virt + EMMC_RESP2);
            cmd->response[3] = read32(pdat->virt + EMMC_RESP3);
        }
    }

    return ret;
}

static rt_err_t read_bytes(struct sdhci_pdata_t * pdat, rt_uint32_t * buf, rt_uint32_t blkcount, rt_uint32_t blksize)
{
    rt_uint32_t * tmp = buf;
    rt_uint32_t count = blkcount * blksize;
    rt_uint32_t status, err;

//    status = read32(pdat->virt + PL180_STATUS);
//    err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_RX_OVERRUN);
//    while((!err) && (count >= sizeof(rt_uint32_t)))
//    {
//        if(status & PL180_STAT_RX_FIFO_AVL)
//        {
//            *(tmp) = read32(pdat->virt + PL180_FIFO);
//            tmp++;
//            count -= sizeof(rt_uint32_t);
//        }
//        status = read32(pdat->virt + PL180_STATUS);
//        err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_RX_OVERRUN);
//    }
//
//    err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_DAT_BLK_END | PL180_STAT_RX_OVERRUN);
//    while(!err)
//    {
//        status = read32(pdat->virt + PL180_STATUS);
//        err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_DAT_BLK_END | PL180_STAT_RX_OVERRUN);
//    }
//
//    if(status & PL180_STAT_DAT_TIME_OUT)
//        return -RT_ERROR;
//    else if (status & PL180_STAT_DAT_CRC_FAIL)
//        return -RT_ERROR;
//    else if (status & PL180_STAT_RX_OVERRUN)
//        return -RT_ERROR;
//    write32(pdat->virt + PL180_CLEAR, 0x1DC007FF);
//
//    if(count)
//        return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t write_bytes(struct sdhci_pdata_t * pdat, rt_uint32_t * buf, rt_uint32_t blkcount, rt_uint32_t blksize)
{
    rt_uint32_t * tmp = buf;
    rt_uint32_t count = blkcount * blksize;
    rt_uint32_t status, err;
    int i;

//    status = read32(pdat->virt + PL180_STATUS);
//    err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT);
//    while(!err && count)
//    {
//        if(status & PL180_STAT_TX_FIFO_HALF)
//        {
//            if(count >= 8 * sizeof(rt_uint32_t))
//            {
//                for(i = 0; i < 8; i++)
//                    write32(pdat->virt + PL180_FIFO, *(tmp + i));
//                tmp += 8;
//                count -= 8 * sizeof(rt_uint32_t);
//            }
//            else
//            {
//                while(count >= sizeof(rt_uint32_t))
//                {
//                    write32(pdat->virt + PL180_FIFO, *tmp);
//                    tmp++;
//                    count -= sizeof(rt_uint32_t);
//                }
//            }
//        }
//        status = read32(pdat->virt + PL180_STATUS);
//        err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT);
//    }
//
//    err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_DAT_BLK_END);
//    while(!err)
//    {
//        status = read32(pdat->virt + PL180_STATUS);
//        err = status & (PL180_STAT_DAT_CRC_FAIL | PL180_STAT_DAT_TIME_OUT | PL180_STAT_DAT_BLK_END);
//    }
//
//    if(status & PL180_STAT_DAT_TIME_OUT)
//        return -RT_ERROR;
//    else if (status & PL180_STAT_DAT_CRC_FAIL)
//        return -RT_ERROR;
//    write32(pdat->virt + PL180_CLEAR, 0x1DC007FF);
//
//    if(count)
//        return -RT_ERROR;
    return RT_EOK;
}

static rt_err_t raspi_transfer_data(struct sdhci_pdata_t * pdat, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat)
{
    rt_uint32_t dlen = (rt_uint32_t)(dat->blkcnt * dat->blksz);
    rt_uint32_t blksz_bits = dat->blksz - 1;
    rt_err_t ret = -RT_ERROR;

    write32(pdat->virt + EMMC_BLKSIZECNT, dlen);

    if(dat->flag & DATA_DIR_READ)
    {
        write32(pdat->virt + EMMC_STATUS, SR_READ_TRANSFER);
        ret = raspi_transfer_command(pdat, cmd);
        if (ret < 0) return ret;
        ret = read_bytes(pdat, (rt_uint32_t *)dat->buf, dat->blkcnt, dat->blksz);
    }
    else if(dat->flag & DATA_DIR_WRITE)
    {
        ret = raspi_transfer_command(pdat, cmd);
        if (ret < 0) return ret;
        write32(pdat->virt + EMMC_STATUS, SR_WRITE_TRANSFER);
        ret = write_bytes(pdat, (rt_uint32_t *)dat->buf, dat->blkcnt, dat->blksz);
    }

    return ret;
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
    EMMCCommand* cmdtab = &sdCommandTable[cmd.cmdidx];
    cmd.cmdarg = req->cmd->arg;
    cmd.resptype = cmdtab->resp;

    if(req->data)
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
        cmdtab = &sdCommandTable[cmd.cmdidx];
        stop.cmdarg = req->stop->arg;
        cmd.resptype = cmdtab->resp;

        req->stop->err = sdhci_transfer(sdhci, &stop, RT_NULL);
    }

    mmcsd_req_complete(host);
}


static rt_err_t sdhci_transfer(struct sdhci_t * sdhci, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat)
{
    struct sdhci_pdata_t * pdat = (struct sdhci_pdata_t *)sdhci->priv;

    if(!dat)
        return raspi_transfer_command(pdat, cmd);

    return raspi_transfer_data(pdat, cmd, dat);
}


//#ifdef CONFIG_MMC_USE_DMA
//#ifdef BSP_USING_SDIO0
////ALIGN(32) static rt_uint8_t dma_buffer[64 * 1024];
//static rt_uint8_t dma_buffer[64 * 1024];
//#endif
//#endif


static void mmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    struct sdhci_t * sdhci = (struct sdhci_t *)host->private_data;
    sdhci_setclock(sdhci, io_cfg->clock);
    sdhci_setwidth(sdhci, io_cfg->bus_width);
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
    temp = read32((pdat->virt + EMMC_CONTROL0));
    temp |= C0_HCTL_HS_EN;
    temp |= C0_HCTL_DWITDH;   // always use 4 data lines:
    write32((pdat->virt + EMMC_CONTROL0), temp);

    return RT_EOK;
}

static rt_uint32_t sdhci_getdivider( rt_uint32_t sdHostVer, rt_uint32_t freq )
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

    if (divisor <= 2) {
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
    struct sdhci_pdata_t * pdat = (struct sdhci_pdata_t *)sdhci->priv;

    temp = read32(pdat->virt + EMMC_STATUS);
    while((temp & (SR_CMD_INHIBIT | SR_DAT_INHIBIT))&&(--count))
        bcm283x_clo_delayMicros(1);

    if( count <= 0 )
    {
        rt_kprintf("EMMC: Set clock: timeout waiting for inhibit flags. Status %08x.\n", temp);
        return RT_ERROR;
    }

    // Switch clock off.
    temp = read32((pdat->virt + EMMC_CONTROL1));
    temp |= ~C1_CLK_EN;
    write32((pdat->virt + EMMC_CONTROL1),temp);

    bcm283x_clo_delayMicros(10);

    // Request the new clock setting and enable the clock
    temp = read32(pdat->virt + EMMC_SLOTISR_VER);
    sdHostVer = (temp & HOST_SPEC_NUM) >> HOST_SPEC_NUM_SHIFT;

    int cdiv = sdhci_getdivider(sdHostVer, clock);
    temp = read32((pdat->virt + EMMC_CONTROL1));
    temp = (temp & 0xffff003f) | cdiv;
    write32((pdat->virt + EMMC_CONTROL1),temp);
    bcm283x_clo_delayMicros(10);

    // Enable the clock.
    temp = read32(pdat->virt + EMMC_CONTROL1);
    temp |= C1_CLK_EN;
    write32((pdat->virt + EMMC_CONTROL1),temp);
    bcm283x_clo_delayMicros(10);

    // Wait for clock to be stable.
    count = 10000;
    temp = read32(pdat->virt + EMMC_CONTROL1);
    while( !(temp & C1_CLK_STABLE) && count-- )
        bcm283x_clo_delayMicros(10);

    if( count <= 0 )
    {
        rt_kprintf("EMMC: ERROR: failed to get stable clock.\n");
        return RT_ERROR;
    }

    return RT_EOK;
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
    int pin;

    for (pin = BCM_GPIO_PIN_48; pin <= BCM_GPIO_PIN_53; pin++)
    {
        bcm283x_gpio_set_pud(pin, BCM283X_GPIO_PUD_UP);
        bcm283x_gpio_fsel(pin, BCM283X_GPIO_FSEL_ALT3);
    }
    bcm283x_gpio_set_pud(pin, BCM283X_GPIO_PUD_UP);
    bcm283x_gpio_fsel(pin, BCM283X_GPIO_FSEL_INPT);
}

int raspi_sdmmc_init(void)
{
    rt_uint32_t virt;
    rt_uint32_t id;
    struct rt_mmcsd_host * host = RT_NULL;
    struct sdhci_pdata_t * pdat = RT_NULL;
    struct sdhci_t * sdhci = RT_NULL;

    rt_kprintf("raspi_sdmmc_init start\n");

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

    rt_kprintf(">> sdmmc_gpio_init\n");
    sdmmc_gpio_init();
    rt_kprintf("<< sdmmc_gpio_init\n");

    virt = MMC0_BASE_ADDR;

    pdat = (struct sdhci_pdata_t *)rt_malloc(sizeof(struct sdhci_pdata_t));
    RT_ASSERT(pdat != RT_NULL);

    pdat->virt = (rt_uint32_t)virt;

    sdhci->name = "sd0";
    sdhci->voltages = VDD_33_34;
    sdhci->width = MMCSD_BUSWIDTH_4;
    sdhci->clock = 26 * 1000 * 1000;
    sdhci->removeable = RT_TRUE;

    sdhci->detect = sdhci_detect;
    sdhci->setwidth = sdhci_setwidth;
    sdhci->setclock = sdhci_setclock;
    sdhci->transfer = sdhci_transfer;
    sdhci->priv = pdat;
    //write32(pdat->virt + PL180_POWER, 0xbf);

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
#endif
}
INIT_APP_EXPORT(raspi_sdmmc_init);
#endif
