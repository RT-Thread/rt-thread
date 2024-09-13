/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-11-19      Wayne            First version
*
******************************************************************************/

#include "rtconfig.h"

#if defined(BSP_USING_SDH)

#include <rtdevice.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_sdio.h>

#include "NuMicro.h"
#include "drv_common.h"

#define LOG_TAG    "drv.sdio"
#undef  DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL  LOG_LVL_INFO
#define DBG_COLOR
#include <rtdbg.h>

#define SDH_ALIGN_LEN   64
#define SDH_BUFF_SIZE   (512*1024)

enum
{
    SDH_START = -1,
#if defined(BSP_USING_SDH0)
    SDH0_IDX,
#endif
#if defined(BSP_USING_SDH1)
    SDH1_IDX,
#endif
    SDH_CNT
};

struct nu_sdh
{
    struct rt_mmcsd_host  *host;
    char            *name;
    SDH_T           *base;
    IRQn_Type        irqn;
    uint32_t         rstidx;
    uint32_t         modid;
    uint8_t         *cachebuf;

    struct rt_event  event;
};
typedef struct nu_sdh *nu_sdh_t;

/* Private variables ------------------------------------------------------------*/
#if defined(BSP_USING_SDH0)
    ALIGN(SDH_ALIGN_LEN)
    static uint8_t g_au8CacheBuf_SDH0[SDH_BUFF_SIZE];
#endif

#if defined(BSP_USING_SDH1)
    ALIGN(SDH_ALIGN_LEN)
    static uint8_t g_au8CacheBuf_SDH1[SDH_BUFF_SIZE];
#endif

static struct nu_sdh nu_sdh_arr [] =
{
#if defined(BSP_USING_SDH0)
    {
        .name = "sdh0",
        .base = SDH0,
        .irqn = SDH0_IRQn,
        .rstidx = SDH0_RST,
        .modid = SDH0_MODULE,
        .cachebuf = g_au8CacheBuf_SDH0,
    },
#endif
#if defined(BSP_USING_SDH1)
    {
        .name = "sdh1",
        .base = SDH1,
        .irqn = SDH1_IRQn,
        .rstidx = SDH1_RST,
        .modid = SDH1_MODULE,
        .cachebuf = g_au8CacheBuf_SDH1,
    },
#endif
}; /* struct nu_sdh nu_sdh_arr [] */

static uint32_t nu_sdh_get_cmd_resptype(uint32_t rt_resp_type)
{
    uint32_t nu_resptype = 0;
    switch (rt_resp_type)
    {
    case RESP_NONE:
        nu_resptype = MMC_RSP_NONE;
        break;
    case RESP_R1:
        nu_resptype = MMC_RSP_R1;
        break;
    case RESP_R1B:
        nu_resptype = MMC_RSP_R1b;
        break;
    case RESP_R2:
        nu_resptype = MMC_RSP_R2;
        break;
    case RESP_R3:
        nu_resptype = MMC_RSP_R3;
        break;
    case RESP_R4:
        nu_resptype = MMC_RSP_R4;
        break;
    case RESP_R6:
        nu_resptype = MMC_RSP_R6;
        break;
    case RESP_R7:
        nu_resptype = MMC_RSP_R7;
        break;
    case RESP_R5:
        nu_resptype = MMC_RSP_R5;
        break;
    default:
        nu_resptype = 0xffffffff;
    }
    return nu_resptype ;
}

static void nu_sdh_send_commanddone(SDH_T *sdh, struct mmc_cmd *cmd)
{
    if (cmd->resp_type & MMC_RSP_136)
    {
        /* CRC is stripped so we need to do some shifting. */
        cmd->response[0] = (sdh->RESP67 << 8) | sdh->S_RESP45.B3;
        cmd->response[1] = (sdh->RESP45 << 8) | sdh->S_RESP23.B3;
        cmd->response[2] = (sdh->RESP23 << 8) | sdh->S_RESP01.B3;
        cmd->response[3] = (sdh->RESP01 << 8);
    }
    else
    {
        cmd->response[0] = sdh->RESP01;
        cmd->response[1] = cmd->response[2] = cmd->response[3] = 0;
    }
}

static int nu_sdh_xfer_data(SDH_T *sdh, struct mmc_data *data)
{
    uint32_t start_addr, timeout;

    if (data->flags & DATA_DIR_READ)
    {
        start_addr = (uint32_t)data->dest;
    }
    else
    {
        start_addr = (uint32_t)data->src;
    }

    timeout = 1000000;

    while (!sdh->S_NORMAL_INT_STAT.XFER_COMPLETE) /* SDHCI_INT_DATA_END? */
    {
        if (sdh->S_NORMAL_INT_STAT.ERR_INTERRUPT == 1)
            return -1;

        if (sdh->S_NORMAL_INT_STAT.DMA_INTERRUPT)        /* SDHCI_INT_DMA_END */
        {
            sdh->S_NORMAL_INT_STAT.DMA_INTERRUPT = 1;    /* Clear SDHCI_INT_DMA_END */

            start_addr &= ~(SDH_BLOCK_SIZE * 1024 - 1);
            start_addr += SDH_BLOCK_SIZE * 1024;

            sdh->SDMASA = start_addr;
        }
        if (timeout-- > 0)
            rt_hw_us_delay(10);
        else
            return -2;
    }

    return 0;
}

static void nu_sdh_list_errors(SDH_T *sdh)
{
    if (sdh->S_NORMAL_INT_STAT.ERR_INTERRUPT)
    {
        LOG_D("Error List:");
        if (sdh->S_ERROR_INT_STAT.CMD_TOUT_ERR)
            LOG_D("\tCMD_TOUT_ERR.");
        if (sdh->S_ERROR_INT_STAT.CMD_CRC_ERR)
            LOG_D("\tCMD_CRC_ERR.");
        if (sdh->S_ERROR_INT_STAT.CMD_END_BIT_ERR)
            LOG_D("\tCMD_END_BIT_ERR.");
        if (sdh->S_ERROR_INT_STAT.CMD_IDX_ERR)
            LOG_D("\tCMD_IDX_ERR.");
        if (sdh->S_ERROR_INT_STAT.DATA_TOUT_ERR)
            LOG_D("\tDATA_TOUT_ERR.");
        if (sdh->S_ERROR_INT_STAT.DATA_CRC_ERR)
            LOG_D("\tDATA_CRC_ERR.");
        if (sdh->S_ERROR_INT_STAT.DATA_END_BIT_ERR)
            LOG_D("\tDATA_END_BIT_ERR.");
        if (sdh->S_ERROR_INT_STAT.CUR_LMT_ERR)
            LOG_D("\tCUR_LMT_ERR.");

        if (sdh->S_ERROR_INT_STAT.AUTO_CMD_ERR)
            LOG_D("\tAUTO_CMD_ERR.");
        if (sdh->S_ERROR_INT_STAT.ADMA_ERR)
            LOG_D("\tADMA_ERR.");
        if (sdh->S_ERROR_INT_STAT.TUNING_ERR)
            LOG_D("\tTUNING_ERR.");
        if (sdh->S_ERROR_INT_STAT.RESP_ERR)
            LOG_D("\tRESP_ERR.");
        if (sdh->S_ERROR_INT_STAT.BOOT_ACK_ERR)
            LOG_D("\tBOOT_ACK_ERR.");
        if (sdh->S_ERROR_INT_STAT.VENDOR_ERR1)
            LOG_D("\tVENDOR_ERR1.");
        if (sdh->S_ERROR_INT_STAT.VENDOR_ERR2)
            LOG_D("\tVENDOR_ERR2.");
        if (sdh->S_ERROR_INT_STAT.VENDOR_ERR3)
            LOG_D("\tVENDOR_ERR3.");
    }
}

/**
  * @brief  This function send command.
  * @param  sdio  rthw_sdio
  * @param  pkg   sdio package
  * @retval None
  */
static int nu_sdh_send_command(SDH_T *sdh, struct mmc_cmd *cmd, struct mmc_data *data)
{
    int ret;
    uint32_t mask, flags, mode;
    volatile unsigned int time = 0;
    volatile unsigned int cmd_timeout, stat;

    LOG_D("[CMD:%d ARG:0x%08x] RESP_TYPE:0x%08x rw:%c addr:0x%08x len:%d blksize:%d",
          cmd->cmdidx,
          cmd->cmdarg,
          cmd->resp_type,
          data ? (data->flags & DATA_DIR_WRITE ?  'w' : 'r') : '-',
          data ? data->src : 0,
          data ? data->blocks * data->blocksize : 0,
          data ? data->blocksize : 0);

    mask = 0x3; /* SDH_CMD_INHIBIT | SDH_DATA_INHIBIT */
    if (cmd->cmdidx == MMC_CMD_STOP_TRANSMISSION)
        mask &= ~0x2;   /* SDH_DATA_INHIBIT */

    ret = SD_GetBusStatus(sdh, mask);
    if (ret)
    {
        LOG_E("ERROR: Busy %d\n", ret);
        ret = __LINE__;
        goto exit_nu_sdh_send_command;
    }

    /* SDHCI_INT_ALL_MASK */
    sdh->NORMAL_INT_STAT = 0xFFFF;
    sdh->ERROR_INT_STAT = 0xFFFF;

    mask = 0x1;     /* SDHCI_INT_RESPONSE */

    if (!(cmd->resp_type & MMC_RSP_PRESENT))
        flags = SDH_CMD_RESP_NONE;
    else if (cmd->resp_type & MMC_RSP_136)
        flags = SDH_CMD_RESP_LONG;
    else if (cmd->resp_type & MMC_RSP_BUSY)
    {
        flags = SDH_CMD_RESP_SHORT_BUSY;
        if (data)
            mask |= 0x2;    /* SDHCI_INT_DATA_END */
    }
    else
        flags = SDH_CMD_RESP_SHORT;

    if (cmd->resp_type & MMC_RSP_CRC)
        flags |= SDH_CMD_CRC;

    if (cmd->resp_type & MMC_RSP_OPCODE)
        flags |= SDH_CMD_INDEX;

    /* Set Transfer mode regarding to data flag */
    if (data)
    {
        flags |= SDH_CMD_DATA;

        sdh->S_TOUT_CTRL.TOUT_CNT = 0xE;

        mode = 0x2; /* SDHCI_TRNS_BLK_CNT_EN */
        if (data->blocks > 1)
            mode |= 0x20;   /* SDHCI_TRNS_MULTI */

        if (data->flags & DATA_DIR_READ)
        {
            mode |= 0x10;   /* SDHCI_TRNS_READ */
            sdh->SDMASA = (uint32_t)data->dest;
        }
        else
        {
            sdh->SDMASA = (uint32_t)data->src;
        }

        mode |= 0x1;
        sdh->S_HOST_CTRL1.DMA_SEL = 0; //SDMA is selected

        /* 512 Kbytes SDMA Buffer Boundary */
        sdh->S_BLOCKSIZE.SDMA_BUF_BDARY = 0x7;

        /* Set Block Size */
        sdh->S_BLOCKSIZE.XFER_BLOCK_SIZE = data->blocksize;

        /* Set Block count */
        sdh->S_BLOCKCOUNT.BLOCK_CNT = data->blocks;

        /* Set transfer mode */
        sdh->XFER_MODE = mode;
    }
    else if (cmd->resp_type & MMC_RSP_BUSY)
    {
        sdh->S_TOUT_CTRL.TOUT_CNT = 0xE;
    }

    sdh->ARGUMENT = cmd->cmdarg;
    sdh->CMD = ((cmd->cmdidx & 0xff) << 8) | (flags & 0xff);

    cmd_timeout = 10000000;
    time = 0;
    do
    {
        stat = sdh->NORMAL_INT_STAT;
        if (stat & 0x8000) /* SDHCI_INT_ERROR */
            break;

        if (time > cmd_timeout)
        {
            ret = __LINE__;
            LOG_E("[%s %d] timeout stat=%04x, mask=%04x", __func__, __LINE__, stat, mask);
            goto exit_nu_sdh_send_command;
        }
        time++;
    }
    while ((stat & mask) != mask);

    if ((stat & (0x8000 | mask)) == mask)
    {
        //LOG_D("[%s %d] Done. cmdid=%d restore", __func__, __LINE__, cmd->cmdidx);

        nu_sdh_send_commanddone(sdh, cmd);
        nu_sdh_list_errors(sdh);

        /* Send data */
        if (data)
        {
            ret = nu_sdh_xfer_data(sdh, data);
        }
        stat = sdh->ERROR_INT_STAT;

        sdh->NORMAL_INT_STAT = mask;
        ret = 0;
    }
    else
    {
        //LOG_E("[%s %d] Error. cmdid=%d not restored %08x %08x", __func__, __LINE__, cmd->cmdidx, stat, mask);
        ret = __LINE__;

        nu_sdh_list_errors(sdh);
        goto exit_nu_sdh_send_command;
    }

    /* SDHCI_INT_ALL_MASK */
    sdh->NORMAL_INT_STAT = 0xFFFF;
    sdh->ERROR_INT_STAT = 0xFFFF;

    if (ret)
    {
        LOG_E("[%s %d] ret=%d cmd->cmdidx=%d, error=0x%x", __func__, __LINE__, ret, cmd->cmdidx, stat);
        ret = __LINE__;
        goto exit_nu_sdh_send_command;
    }

    return 0;

exit_nu_sdh_send_command:

    SDH_Reset(sdh, SDH_RESET_CMD);
    SDH_Reset(sdh, SDH_RESET_DATA);

    //LOG_E("[%s %d] cmdid=%d error line=%d", __func__, __LINE__, cmd->cmdidx, ret);

    return ret;
}


/**
  * @brief  This function send sdio request.
  * @param  host  rt_mmcsd_host
  * @param  req   request
  * @retval None
  */
static void nu_sdh_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    nu_sdh_t sdh = (nu_sdh_t)host->private_data;

    RT_ASSERT(host);
    RT_ASSERT(req);

    if (host->card)
    {
        if (host->card->card_type == CARD_TYPE_MMC)
        {
            sdh->base->S_EMMC_CTRL.CARD_IS_EMMC = 1;
            sdh->base->S_EMMC_CTRL.DISABLE_DATA_CRC_CHK = 1;
        }
        else
        {
            sdh->base->S_EMMC_CTRL.CARD_IS_EMMC = 0;
            sdh->base->S_EMMC_CTRL.DISABLE_DATA_CRC_CHK = 0;
        }
    }

    if (req->cmd != RT_NULL)
    {
        struct mmc_cmd cmd;

        LOG_D("[%s%s%s%s%s]REQ: CMD:%d ARG:0x%08x RESP_TYPE:0x%08x, 0x%08x",
              (host->card == RT_NULL) ? "Unknown" : "",
              (host->card) && (host->card->card_type == CARD_TYPE_MMC) ? "MMC" : "",
              (host->card) && (host->card->card_type == CARD_TYPE_SD) ? "SD" : "",
              (host->card) && (host->card->card_type == CARD_TYPE_SDIO) ? "SDIO" : "",
              (host->card) && (host->card->card_type == CARD_TYPE_SDIO_COMBO) ? "SDIO_COMBO" : "",
              req->cmd->cmd_code,
              req->cmd->arg,
              resp_type(req->cmd),
              nu_sdh_get_cmd_resptype(resp_type(req->cmd)));

        rt_memset(&cmd, 0, sizeof(struct mmc_cmd));

        cmd.cmdidx    = req->cmd->cmd_code;
        cmd.cmdarg    = req->cmd->arg;
        cmd.resp_type = nu_sdh_get_cmd_resptype(resp_type(req->cmd));

        if (req->data != RT_NULL)
        {
            struct mmc_data data;
            rt_uint32_t size;
            rt_int32_t IsNonaligned = 0;


            LOG_D("[%s]REQ: BUF:%08x FLAGS:0x%08x BLKSIZE:%d, BLKCOUNT:%d",
                  sdh->name,
                  req->data->buf,
                  req->data->flags,
                  req->data->blksize,
                  req->data->blks);

            rt_memset(&data, 0, sizeof(struct mmc_data));

            data.dest = (char *)req->data->buf;
            data.flags = req->data->flags;
            data.blocksize = req->data->blksize;
            data.blocks = req->data->blks;

            size = data.blocksize * data.blocks;

            RT_ASSERT(size <= SDH_BUFF_SIZE);

            IsNonaligned = (((rt_uint32_t)data.dest & (SDH_ALIGN_LEN - 1)) > 0) ? 1 : 0;
            if (IsNonaligned)
            {
                data.dest = (char *)sdh->cachebuf;
                if (data.flags & DATA_DIR_WRITE)
                {
                    LOG_D("Un-aligned, prepare into cache buf(%d)", size);
                    rt_memcpy(data.dest, req->data->buf, size);
                }
            }

            rt_hw_cpu_dcache_clean_and_invalidate((void *)data.dest, size);
            req->cmd->err = nu_sdh_send_command(sdh->base, &cmd, &data);
            rt_hw_cpu_dcache_invalidate((void *)data.dest, size);

            if (!req->cmd->err && IsNonaligned)
            {
                if (data.flags & DATA_DIR_READ)
                {
                    LOG_D("Un-aligned, restore from cache buf(%d)", size);
                    rt_memcpy(req->data->buf, data.dest, size);
                }
            }
            LOG_HEX("data.dest", 16, (void *)data.dest, size);

        }
        else
        {
            req->cmd->err = nu_sdh_send_command(sdh->base, &cmd, NULL);
        }

        /* Report response words */
        req->cmd->resp[3] = cmd.response[3];
        req->cmd->resp[2] = cmd.response[2];
        req->cmd->resp[1] = cmd.response[1];
        req->cmd->resp[0] = cmd.response[0];

        LOG_HEX("req->cmd->resp", 16, (void *)&req->cmd->resp[0], 16);

    }

    if (req->stop != RT_NULL)
    {
        struct mmc_cmd stop;
        rt_memset(&stop, 0, sizeof(struct mmc_cmd));

        stop.cmdidx = req->stop->cmd_code;
        stop.cmdarg = req->stop->arg;
        stop.resp_type = nu_sdh_get_cmd_resptype(resp_type(req->stop));

        req->stop->err = nu_sdh_send_command(sdh->base, &stop, NULL);

        /* Report response words */
        req->stop->resp[3] = stop.response[3];
        req->stop->resp[2] = stop.response[2];
        req->stop->resp[1] = stop.response[1];
        req->stop->resp[0] = stop.response[0];

        LOG_HEX("req->stop->resp", 16, (void *)&req->stop->resp[0], 16);

    }

    mmcsd_req_complete(host);
}

/**
  * @brief  This function config sdio.
  * @param  host    rt_mmcsd_host
  * @param  io_cfg  rt_mmcsd_io_cfg
  * @retval None
  */
static void nu_sdh_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    nu_sdh_t NuSdh;
    rt_uint32_t clk = io_cfg->clock;
    SDH_T *sdh;

    RT_ASSERT(host);
    RT_ASSERT(io_cfg);

    NuSdh = (nu_sdh_t)host->private_data;
    sdh = NuSdh->base;

    LOG_D("[%s]clk:%d width:%s%s%s power:%s%s%s",
          NuSdh->name,
          clk,
          io_cfg->bus_width == MMCSD_BUS_WIDTH_8 ? "8" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_4 ? "4" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_1 ? "1" : "",
          io_cfg->power_mode == MMCSD_POWER_OFF ? "OFF" : "",
          io_cfg->power_mode == MMCSD_POWER_UP ? "UP" : "",
          io_cfg->power_mode == MMCSD_POWER_ON ? "ON" : "");

    /* Bus width */
    switch (io_cfg->bus_width)
    {
    case MMCSD_BUS_WIDTH_1:
    case MMCSD_BUS_WIDTH_4:
    case MMCSD_BUS_WIDTH_8:
        SDH_SetBusWidth(sdh,  1 << io_cfg->bus_width);
        break;
    default:
        break;
    }

    /* Power */
    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_UP:
    case MMCSD_POWER_ON:
        SDH_SetPower(sdh, 1);
        break;

    case MMCSD_POWER_OFF:
        SDH_SetPower(sdh, 0);
        break;
    default:
        break;
    }

    /* Clock */
    if (clk > host->freq_max)
        clk = host->freq_max;

    if (clk < host->freq_min)
        clk = host->freq_min;

    if (clk)
    {
        uint32_t u32SrcFreqInHz = 0, u32ModRealFreqInHz;
        uint32_t u32ModSrcIdx = CLK_GetModuleClockSource(NuSdh->modid);

        switch (u32ModSrcIdx)
        {
        case 0: // From SYSPLL
            u32SrcFreqInHz = CLK_GetPLLClockFreq(SYSPLL);
            break;
        default: // From APLL
            u32SrcFreqInHz = CLK_GetPLLClockFreq(APLL);
            break;
        }

        u32ModRealFreqInHz = SDH_SetClock(sdh, u32SrcFreqInHz, clk);
        u32ModRealFreqInHz = u32ModRealFreqInHz; //Avoid warning

        LOG_D("[%s] SrcClock: %d kHz, ExceptedFreq: %d kHz, RealFreq: %d kHz", NuSdh->name, u32SrcFreqInHz / 1000, clk / 1000, u32ModRealFreqInHz / 1000);
    }

}

/**
  * @brief  This function detect sdcard.
  * @param  host    rt_mmcsd_host
  * @retval 0x01
  */
static rt_int32_t nu_sdh_card_detect(struct rt_mmcsd_host *host)
{
    LOG_D("try to detect device");
    return 0x01;
}

/**
  * @brief  This function interrupt process function.
  * @param  host  rt_mmcsd_host
  * @retval None
  */
static void nu_sdh_isr(int vector, void *param)
{
    nu_sdh_t sdh = (nu_sdh_t)param;
    struct rt_mmcsd_host *host = sdh->host;
    SDH_T *base = sdh->base;
    volatile unsigned int isr = base->NORMAL_INT_STAT;

    /* We just catch card detection here. */
    if (isr & 0xc0)
    {
        /* ready to change */
        mmcsd_change(host);
        base->NORMAL_INT_STAT = 0xC0;
    }
}

/**
  * @brief  This function update sdh interrupt.
  * @param  host    rt_mmcsd_host
  * @param  enable
  * @retval None
  */
void nu_sdh_irq_update(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    nu_sdh_t sdh = (nu_sdh_t)host->private_data;
    SDH_T *sdh_base = sdh->base;

    if (enable)
    {
        LOG_D("Enable %s irq", sdh->name);

        /* Enable only interrupts served by the SD controller */
        /* sdh_base->NORMAL_INT_STAT_EN = 0x00FB; */
        sdh_base->S_NORMAL_INT_STAT_EN.CMD_COMPLETE_STAT_EN = 1;
        sdh_base->S_NORMAL_INT_STAT_EN.XFER_COMPLETE_STAT_EN = 1;
        sdh_base->S_NORMAL_INT_STAT_EN.DMA_INTERRUPT_STAT_EN = 1;

        sdh_base->S_NORMAL_INT_STAT_EN.BUF_WR_READY_STAT_EN = 1;
        sdh_base->S_NORMAL_INT_STAT_EN.BUF_RD_READY_STAT_EN = 1;
        sdh_base->S_NORMAL_INT_STAT_EN.CARD_INSERTION_STAT_EN = 1;
        sdh_base->S_NORMAL_INT_STAT_EN.CARD_REMOVAL_STAT_EN = 1;

        /* sdh_base->ERROR_INT_STAT_EN = 0x0271; */
        sdh_base->S_ERROR_INT_STAT_EN.CMD_TOUT_ERR_STAT_EN = 1;
        sdh_base->S_ERROR_INT_STAT_EN.DATA_TOUT_ERR_STAT_EN = 1;
        sdh_base->S_ERROR_INT_STAT_EN.DATA_CRC_ERR_STAT_EN = 1;
        sdh_base->S_ERROR_INT_STAT_EN.DATA_END_BIT_ERR_STAT_EN = 1;
        sdh_base->S_ERROR_INT_STAT_EN.ADMA_ERR_STAT_EN = 1;

        /* Mask all interrupt sources */
        /* sdh_base->NORMAL_INT_SIGNAL_EN = 0xC0; */
        sdh_base->S_NORMAL_INT_SIGNAL_EN.CARD_INSERTION_SIGNAL_EN = 1;
        sdh_base->S_NORMAL_INT_SIGNAL_EN.CARD_REMOVAL_SIGNAL_EN = 1;

        sdh_base->ERROR_INT_SIGNAL_EN = 0;

        //sdh_base->NORMAL_INT_STAT_EN = 0x7FFF;
        //sdh_base->ERROR_INT_STAT_EN = 0xFFFF;
        //sdh_base->NORMAL_INT_SIGNAL_EN=0x7FFF;
        //sdh_base->ERROR_INT_SIGNAL_EN=0xFFFF;
    }
    else
    {
        LOG_D("Disable %s irq", sdh->name);

        sdh_base->NORMAL_INT_STAT_EN = 0x0;
        sdh_base->ERROR_INT_STAT_EN = 0x0;
        sdh_base->NORMAL_INT_SIGNAL_EN = 0x0;
        sdh_base->ERROR_INT_SIGNAL_EN = 0x0;
    }
}

static const struct rt_mmcsd_host_ops ops =
{
    nu_sdh_request,
    nu_sdh_iocfg,
    nu_sdh_card_detect,
    nu_sdh_irq_update,
};

/**
  * @brief  This function create mmcsd host.
  * @param  sdh  nu_sdh_t
  * @retval nuvton
  */
void nu_sdh_host_initial(nu_sdh_t sdh)
{
    struct rt_mmcsd_host *host;
    rt_err_t ret = RT_EOK;

    host = mmcsd_alloc_host();
    RT_ASSERT(host != RT_NULL);

    ret = rt_event_init(&sdh->event, "sdh_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(ret == RT_EOK);

    /* Reset sdh at first. */
    SDH_Reset(sdh->base, SDH_RESET_ALL);

    /* set host default attributes */
    host->ops = &ops;
    host->freq_min = 200 * 1000;
    host->freq_max = 50 * 1000 * 1000;
    host->valid_ocr = VDD_30_31 | VDD_31_32 | VDD_32_33 | VDD_33_34; // | VDD_165_195;

    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ | MMCSD_SUP_HIGHSPEED;

    host->max_seg_size = SDH_BUFF_SIZE;
    host->max_dma_segs = 1;
    host->max_blk_size = SDH_BLOCK_SIZE;
    host->max_blk_count = (SDH_BUFF_SIZE / SDH_BLOCK_SIZE);

    /* link up host and sdio */
    host->private_data = sdh;
    sdh->host = host;

    /* Set initial state: high speed */
    sdh->base->S_HOST_CTRL1.HIGH_SPEED_EN = 1;

    /* Set SDR50 mode */
    sdh->base->S_HOST_CTRL2.UHS_MODE_SEL = 2;

    /* Install ISR. */
    rt_hw_interrupt_install(sdh->irqn, nu_sdh_isr, (void *)sdh, sdh->name);
    rt_hw_interrupt_umask(sdh->irqn);

    /* Enable interrupt. */
    nu_sdh_irq_update(host, 1);

    /* ready to change */
    //mmcsd_change(host);
}

void nu_sd_attach(void)
{
    int i;
    /* ready to change */
    for (i = (SDH_START + 1); i < SDH_CNT; i++)
    {
        if (nu_sdh_arr[i].host)
            mmcsd_change(nu_sdh_arr[i].host);
    }
}
MSH_CMD_EXPORT(nu_sd_attach, attach card);

void nu_sd_regdump(void)
{
    int i;
    /* ready to change */
    for (i = (SDH_START + 1); i < SDH_CNT; i++)
    {
        if (nu_sdh_arr[i].host)
            SDH_DumpReg(nu_sdh_arr[i].base);
    }
}
MSH_CMD_EXPORT(nu_sd_regdump, dump sdh registers);

static int rt_hw_sdh_init(void)
{
    int i;

    for (i = (SDH_START + 1); i < SDH_CNT; i++)
    {
        CLK_EnableModuleClock(nu_sdh_arr[i].modid);
        SYS_ResetModule(nu_sdh_arr[i].rstidx);

        nu_sdh_host_initial(&nu_sdh_arr[i]);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_sdh_init);

/* A simple MBR writer. */
struct mbr
{
    uint8_t code[440];
    union
    {
        uint32_t disk_signature;
        struct
        {
            uint32_t disk_signature_B0: 8;
            uint32_t disk_signature_B1: 8;
            uint32_t disk_signature_B2: 8;
            uint32_t disk_signature_B3: 8;
        } s_disk_signature;
    };
    uint16_t unused;
    struct mbr_partition
    {
        uint8_t status;

        uint8_t first_cylinder;
        uint8_t first_head;
        uint8_t first_sector;

        uint8_t partition_type;

        uint8_t last_cylinder;
        uint8_t last_head;
        uint8_t last_sector;

        union
        {
            uint32_t first_sector_lba;
            struct
            {
                uint32_t first_sector_lba_B0: 8;
                uint32_t first_sector_lba_B1: 8;
                uint32_t first_sector_lba_B2: 8;
                uint32_t first_sector_lba_B3: 8;
            } s_first_sector_lba;
        };

        union
        {
            uint32_t sectors ;
            struct
            {
                uint32_t sectors_B0: 8;
                uint32_t sectors_B1: 8;
                uint32_t sectors_B2: 8;
                uint32_t sectors_B3: 8;
            } s_sectors;
        };

    } partition[4];

    uint16_t mbr_signature;

} __attribute__((packed));

#define MBR_SIGNATURE         0xAA55
#define MBR_STATUS_BOOTABLE   0x80

#define le2(a, o) ((a)[o] << 0 | (a)[(o)+1] << 8)
#define le4(a, o) (le2(a,o) | (a)[(o)+2] << 16 | (a)[(o)+3] << 24)

static int nu_sd_mbr_read(const char *devname)
{
    rt_device_t mmc_device = RT_NULL;
    rt_err_t ret;
    struct rt_device_blk_geometry geo = {0};
    struct mbr *psMbr = RT_NULL;

    if ((mmc_device = rt_device_find(devname)) == RT_NULL)
    {
        LOG_E("find device %s failed!\n", devname);
        goto fail_nu_sd_mbr_read;
    }

    if (rt_device_open(mmc_device, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        LOG_E("open device %s failed!\n", devname);
        mmc_device = RT_NULL;
        goto fail_nu_sd_mbr_read;
    }

    if (rt_device_control(mmc_device, RT_DEVICE_CTRL_BLK_GETGEOME, &geo) != RT_EOK)
    {
        LOG_E("control device %s failed!\n", devname);
        goto fail_nu_sd_mbr_read;
    }

    LOG_I("device information:\n");
    LOG_I("sector  size : %d byte\n", geo.bytes_per_sector);
    LOG_I("sector count : %d \n", geo.sector_count);
    LOG_I("block   size : %d byte\n", geo.block_size);
    LOG_I("MBR size : %d byte\n", sizeof(struct mbr));

    psMbr = rt_malloc(sizeof(struct mbr));
    if (psMbr == RT_NULL)
    {
        LOG_E("no memory for mbr buffer!\n");
        goto fail_nu_sd_mbr_read;
    }
    rt_memset(psMbr, 0, sizeof(struct mbr));

    ret = rt_device_read(mmc_device, 0, psMbr, 1);
    if (ret != 1)
    {
        LOG_E("read device %s %d failed!\n", devname, ret);
        goto fail_nu_sd_mbr_read;
    }

    LOG_I("disk_signature = %08x\n", psMbr->disk_signature);
    LOG_I("unused = %02x\n", psMbr->unused);
    for (int i = 0; i < 4; i++)
    {
        LOG_I("[%d] status = %02x\n", i, psMbr->partition[i].status);
        LOG_I("[%d] first_cylinder = %d\n",   i, psMbr->partition[i].first_cylinder);
        LOG_I("[%d] first_head = %d\n",   i, psMbr->partition[i].first_head);
        LOG_I("[%d] first_sector = %d\n",   i, psMbr->partition[i].first_sector);
        LOG_I("[%d] partition_type = %02x\n", i, psMbr->partition[i].partition_type);
        LOG_I("[%d] last_cylinder = %d\n",   i, psMbr->partition[i].last_cylinder);
        LOG_I("[%d] last_head = %d\n",   i, psMbr->partition[i].last_head);
        LOG_I("[%d] last_sector = %d\n",   i, psMbr->partition[i].last_sector);
        LOG_I("[%d] first_sector_lba = %u\n",   i, psMbr->partition[i].first_sector_lba);
        LOG_I("[%d] sectors = %u\n",   i, psMbr->partition[i].sectors);
    }

    LOG_I("signature = %02x\n", psMbr->mbr_signature);

    rt_free(psMbr);

    rt_device_close(mmc_device);

    return 0;

fail_nu_sd_mbr_read:

    if (psMbr != RT_NULL)
        rt_free(psMbr);

    if (mmc_device != RT_NULL)
        rt_device_close(mmc_device);

    return -1;
}


int nu_sd_mbr_dump(int argc, char *argv[])
{
// argc=1: string, mmcblk device name.
    if (argc != 2)
        return -1;
    return nu_sd_mbr_read(argv[1]);
}
MSH_CMD_EXPORT(nu_sd_mbr_dump, dump sd card device);

static int nu_sd_mbr_write(const char *devname, int32_t u32Sectors)
{
    rt_device_t mmc_device = RT_NULL;
    rt_err_t ret;
    struct rt_device_blk_geometry geo;
    struct mbr *psMbr = RT_NULL;

    if ((mmc_device = rt_device_find(devname)) == RT_NULL)
    {
        LOG_E("find device %s failed!\n", devname);
        goto fail_nu_sd_mbr_write;
    }

    if (rt_device_open(mmc_device, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        mmc_device = RT_NULL;
        LOG_E("open device %s failed!\n", devname);
        goto fail_nu_sd_mbr_write;
    }

    rt_memset(&geo, 0, sizeof(geo));
    ret = rt_device_control(mmc_device, RT_DEVICE_CTRL_BLK_GETGEOME, &geo);
    if (ret != RT_EOK)
    {
        LOG_E("control device %s failed!\n", devname);
        goto fail_nu_sd_mbr_write;
    }
    LOG_I("device information:\n");
    LOG_I("sector  size : %d byte\n", geo.bytes_per_sector);
    LOG_I("sector count : %d \n", geo.sector_count);
    LOG_I("block   size : %d byte\n", geo.block_size);

    if (u32Sectors >= geo.sector_count)
    {
        LOG_E("no enough sectors for reserved. %s failed!\n", devname);
        goto fail_nu_sd_mbr_write;
    }

    psMbr = rt_malloc(sizeof(struct mbr));
    if (psMbr == RT_NULL)
    {
        LOG_E("no memory for mbr buffer!\n");
        goto fail_nu_sd_mbr_write;
    }
    rt_memset(psMbr, 0, sizeof(struct mbr));

    psMbr->disk_signature = 0xa8e7d068;
    psMbr->mbr_signature = MBR_SIGNATURE;

    psMbr->partition[0].status = 0;

    //psMbr->partition[0].first_cylinder = 0x00;
    //psMbr->partition[0].first_head = 0x21;
    //psMbr->partition[0].first_sector = 0x21;
    psMbr->partition[0].partition_type = 0x0C;
    //psMbr->partition[0].last_head = 0xFE;
    //psMbr->partition[0].last_sector = 0x3F;
    //psMbr->partition[0].last_cylinder = 0xFF;
    psMbr->partition[0].first_sector_lba = u32Sectors;
    psMbr->partition[0].sectors = geo.sector_count - u32Sectors;

    ret = rt_device_write(mmc_device, 0, psMbr, 1);
    if (ret != 1)
    {
        LOG_E("write device %s %d failed!\n", devname, ret);
        goto fail_nu_sd_mbr_write;
    }

fail_nu_sd_mbr_write:

    if (psMbr != RT_NULL)
        rt_free(psMbr);

    if (mmc_device)
        rt_device_close(mmc_device);

    return -1;
}

int nu_sd_mbr_layout(int argc, char *argv[])
{
// argc=1: string, mmcblk device name.
// argc=2: Reserved sectors for bootable code and remains sectors are for elm mounting.

    if (argc != 3)
        return -1;

    return nu_sd_mbr_write((const char *)argv[1], atoi(argv[2]));
}
MSH_CMD_EXPORT(nu_sd_mbr_layout, layout sd device);

#endif
