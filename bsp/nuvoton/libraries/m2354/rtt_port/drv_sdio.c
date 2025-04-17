/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2022-4-21       Wayne            First version
*
******************************************************************************/

#include "rtconfig.h"

#if defined(BSP_USING_SDH)

#include <rtdevice.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_sdio.h>

#include "NuMicro.h"

#define LOG_TAG    "drv.sdh"
#undef  DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL  LOG_LVL_ASSERT
#define DBG_COLOR
#include <rtdbg.h>

#define SDH_ALIGN_LEN   4
#define SDH_BUFF_SIZE   512
#define SDH_BLOCK_SIZE  512

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
    uint32_t         u32CmdResp0;
    uint32_t         u32CmdResp1;
    uint32_t         u32CurClk;
    rt_tick_t        LastNotice;
};
typedef struct nu_sdh *nu_sdh_t;

/* Private variables ------------------------------------------------------------*/
static struct nu_sdh nu_sdh_arr [] =
{
#if defined(BSP_USING_SDH0)
    {
        .name = "sdh0",
        .base = SDH0,
        .irqn = SDH0_IRQn,
        .rstidx = SDH0_RST,
        .modid = SDH0_MODULE,
        .cachebuf = RT_NULL,
    },
#endif
#if defined(BSP_USING_SDH1)
    {
        .name = "sdh1",
        .base = SDH1,
        .irqn = SDH1_IRQn,
        .rstidx = SDH1_RST,
        .modid = SDH1_MODULE,
        .cachebuf = RT_NULL,
    },
#endif
}; /* struct nu_sdh nu_sdh_arr [] */

#define SDH_SetClock SDH_Set_clock

static int SDH_SetBusWidth(SDH_T *sdh, uint32_t bw)
{
    if (bw == 4)
    {
        sdh->CTL |= SDH_CTL_DBW_Msk;
    }
    else if (bw == 1)
    {
        sdh->CTL &= ~SDH_CTL_DBW_Msk;
    }
    else
    {
        goto exit_SDH_SetBusWidth;
    }

    return 0;

exit_SDH_SetBusWidth:

    return -1;

}

static int SDH_GetBusStatus(SDH_T *sdh, uint32_t mask)
{
    int cnt = 0x100000;
    while (cnt-- > 0)
    {
        sdh->CTL |= SDH_CTL_CLK8OEN_Msk;
        while (sdh->CTL & SDH_CTL_CLK8OEN_Msk) { }

        if (SDH_GET_INT_FLAG(sdh, SDH_INTSTS_DAT0STS_Msk))
            break;
    }
    return (cnt == 0) ? -1 : 0 ;
}

static int SDH_GetCD(SDH_T *sdh)
{
    int i32CD = 0;
    if ((sdh->GCTL & SDH_GCTL_SDEN_Msk) == SDH_GCTL_SDEN_Msk)
    {
        if ((sdh->INTEN & SDH_INTEN_CDSRC_Msk) == SDH_INTEN_CDSRC_Msk)     /* Card detect pin from GPIO */
        {
            i32CD = (sdh->INTSTS & SDH_INTSTS_CDSTS_Msk) ? 0 : 1;
        }
        else   /* Card detect pin from DAT3 mode */
        {
            __IO uint32_t i;

            sdh->CTL |= SDH_CTL_CLKKEEP_Msk;
            for (i = 0ul; i < 5000ul; i++) { }

            i32CD = ((sdh->INTSTS & SDH_INTSTS_CDSTS_Msk) == SDH_INTSTS_CDSTS_Msk) ? 1 : 0;
            sdh->CTL &= ~SDH_CTL_CLKKEEP_Msk;
        }
    }
    return i32CD;
}

static void SDH_Enable(SDH_T *sdh)
{
    /* Reset sdh and its DMA engine at first. */
    sdh->DMACTL |= SDH_DMACTL_DMARST_Msk | SDH_DMACTL_DMAEN_Msk;
    while ((sdh->DMACTL & SDH_DMACTL_DMARST_Msk) == SDH_DMACTL_DMARST_Msk) { }
    sdh->DMACTL = SDH_DMACTL_DMAEN_Msk;
    sdh->DMAINTSTS = SDH_DMAINTSTS_ABORTIF_Msk | SDH_DMAINTSTS_WEOTIF_Msk;  // clear all interrupt flag

    sdh->GCTL = SDH_GCTL_GCTLRST_Msk;
    while ((sdh->GCTL & SDH_GCTL_GCTLRST_Msk) == SDH_GCTL_GCTLRST_Msk) { }// clear all interrupt flag
    sdh->GINTSTS = SDH_GINTSTS_DTAIF_Msk;
    sdh->GCTL = SDH_GCTL_SDEN_Msk;

    sdh->CTL |= SDH_CTL_CTLRST_Msk;
    while ((sdh->CTL & SDH_CTL_CTLRST_Msk) == SDH_CTL_CTLRST_Msk) { }

    sdh->INTSTS = 0xFFFFFFFF;                  // clear all interrupt flag

    sdh->INTEN  |= SDH_INTEN_CDSRC_Msk;
    sdh->INTEN  |= SDH_INTEN_CDIEN_Msk;
}

/**
  * @brief  This function get command responding.
  * @param  sdh   SDH instance
  * @param  cmd   rt_mmcsd_cmd
  * @retval none
  */
static void nu_sdh_sendcmd_done(SDH_T *sdh, struct rt_mmcsd_cmd *cmd)
{
    if (resp_type(cmd) == RESP_R2)
    {
        uint8_t *c = (uint8_t *)&sdh->FB[0];
        int i, j, tmp[5];

        for (i = 0, j = 0; j < 5; i += 4, j++)
        {
            tmp[j] = (*(c + i) << 24) | (*(c + i + 1) << 16) | (*(c + i + 2) << 8) | (*(c + i + 3));
        }
        for (i = 0; i < 4; i++)
        {
            cmd->resp[i] = ((tmp[i] & 0x00ffffff) << 8) |
                           ((tmp[i + 1] & 0xff000000) >> 24);
        }
    }
    else
    {
        cmd->resp[0] = (sdh->RESP0 << 8) | (sdh->RESP1 & 0xff);
        cmd->resp[1] = cmd->resp[2] = cmd->resp[3] = 0;
    }
}

/**
  * @brief  This function wait data-sending/receiving.
  * @param  sdh   SDH instance
  * @param  data  rt_mmcsd_data
  * @retval error code
  */
static int nu_sdh_xfer_data(SDH_T *sdh, struct rt_mmcsd_data *data)
{
    while (!SDH_GET_INT_FLAG(sdh, SDH_INTSTS_BLKDIF_Msk)) { }

    SDH_CLR_INT_FLAG(sdh, SDH_INTSTS_BLKDIF_Msk);

    if (data->flags & DATA_DIR_WRITE)
    {
        sdh->CTL |= SDH_CTL_CLKKEEP_Msk;

        while (!SDH_GET_INT_FLAG(sdh, SDH_INTSTS_DAT0STS_Msk)) { }

        sdh->CTL &= ~SDH_CTL_CLKKEEP_Msk;
    }

    return 0;
}

/**
  * @brief  This function send command and wait its response.
  * @param  host  rt_mmcsd_host
  * @param  cmd   rt_mmcsd_cmd
  * @param  data  rt_mmcsd_data
  * @retval error code
  */
static int nu_sdh_sendcmd(struct rt_mmcsd_host *host, struct rt_mmcsd_cmd *cmd, struct rt_mmcsd_data *data)
{
    int ret;
    nu_sdh_t NuSdh = (nu_sdh_t)host->private_data;
    SDH_T *sdh = NuSdh->base;

    volatile uint32_t ctl = 0, tout = 0;

    switch (host->io_cfg.bus_width)
    {
    case MMCSD_BUS_WIDTH_1:
        ctl &= ~SDH_CTL_DBW_Msk;
        break;

    case MMCSD_BUS_WIDTH_4:
        ctl |= SDH_CTL_DBW_Msk;
        break;

    case MMCSD_BUS_WIDTH_8:
    default:
        return -1;
    }

    /* Reset sdh and its DMA engine at first. */
    sdh->DMACTL |= SDH_DMACTL_DMARST_Msk | SDH_DMACTL_DMAEN_Msk;
    while ((sdh->DMACTL & SDH_DMACTL_DMARST_Msk) == SDH_DMACTL_DMARST_Msk) { }
    sdh->DMACTL = SDH_DMACTL_DMAEN_Msk;
    sdh->DMAINTSTS = SDH_DMAINTSTS_ABORTIF_Msk | SDH_DMAINTSTS_WEOTIF_Msk;  // clear all interrupt flag

    if (resp_type(cmd) != RESP_NONE)
    {
        if (resp_type(cmd) == RESP_R2)
        {
            ctl |= SDH_CTL_R2EN_Msk;
        }
        else
        {
            ctl |= SDH_CTL_RIEN_Msk;
        }
        tout = 0xFFFF;
    }

    /* Set SDNWR and BLK_CNT to 1 */
    ctl |= ((9 << SDH_CTL_SDNWR_Pos) | (1 << SDH_CTL_BLKCNT_Pos));
    ctl |= ((cmd->cmd_code << SDH_CTL_CMDCODE_Pos) | SDH_CTL_COEN_Msk);

    /* Set Transfer mode regarding to data flag */
    if (data != RT_NULL)
    {
        sdh->BLEN = data->blksize - 1;

        if (data->blksize <= 0x200)
        {
            if (data->blks < 256)
            {
                ctl = (ctl & ~SDH_CTL_BLKCNT_Msk) | (data->blks << SDH_CTL_BLKCNT_Pos);
            }
            else
            {
                LOG_E("SD Max block transfer is 255!!");
            }
        }

        if (data->flags & DATA_DIR_READ)
        {
            tout = 0xFFFFFF;
            ctl |= SDH_CTL_DIEN_Msk; // Data-in
            sdh->DMASA = (uint32_t)data->buf; // Read from dest
        }
        else if (data->flags & DATA_DIR_WRITE)
        {
            ctl |= SDH_CTL_DOEN_Msk; // Data-out
            sdh->DMASA = (uint32_t)data->buf; // Write to dest
        }
    }
    else if (resp_type(cmd) == RESP_R1B)
    {
    }

    /* Clear response-timeout flag first for safty and reset new timeout value. */
    SDH_CLR_INT_FLAG(sdh, SDH_INTSTS_RTOIF_Msk);
    sdh->TOUT   = tout;

    /* Set argument and start a transaction. */
    sdh->CMDARG = cmd->arg;
    sdh->CTL    = ctl;

    /* Wait a command done. */
    while ((sdh->CTL & (SDH_CTL_COEN_Msk)) == SDH_CTL_COEN_Msk) { }

    if (resp_type(cmd) != RESP_NONE)
    {
        if (resp_type(cmd) == RESP_R2)
        {
            /* Wait to receive a response R2 from SD card and store the response data into DMC's Flash buffer (exclude CRC7). */
            while (sdh->CTL & SDH_CTL_R2EN_Msk)
            {
                /* When get a Response timeout, break the polling. */
                if (SDH_GET_INT_FLAG(sdh, SDH_INTSTS_RTOIF_Msk))
                {
                    ret = __LINE__;
                    goto exit_nu_sdh_sendcmd;
                }
            }
        }
        else
        {
            /* Wait to receive a response from SD card. */
            while ((sdh->CTL & SDH_CTL_RIEN_Msk))
            {
                /* When get a Response timeout, break the polling. */
                if (SDH_GET_INT_FLAG(sdh, SDH_INTSTS_RTOIF_Msk))
                {
                    ret = __LINE__;
                    goto exit_nu_sdh_sendcmd;
                }
            }

            /* TOFIX: ISSUE: Sometimes, SDH's RIEN is cleared automatically by controller after host sending CMD5 to SD card. */
            /* Workaround: To check previous cmd's response with CMD's.  */
            if (cmd->cmd_code == 5)
            {
                if ((NuSdh->u32CmdResp0 == sdh->RESP0) && (NuSdh->u32CmdResp1 == sdh->RESP1))
                {
                    LOG_E("False CMD5-RESP issue occured.\n");
                    ret = __LINE__;
                    goto exit_nu_sdh_sendcmd;
                }
            }
            NuSdh->u32CmdResp0 = sdh->RESP0;
            NuSdh->u32CmdResp1 = sdh->RESP1;
        }

        /* Get response from FB or register */
        nu_sdh_sendcmd_done(sdh, cmd);
    }

    if (data != RT_NULL)
    {
        /* Wait data processing done */
        nu_sdh_xfer_data(sdh, data);

        ret = SDH_GetBusStatus(sdh, 0);
        if (ret)
        {
            LOG_E("ERROR: Busy %d\n", ret);
            ret = __LINE__;
            goto exit_nu_sdh_sendcmd;
        }
    }

    /* Handle CRC flag */
    if (SDH_GET_INT_FLAG(sdh, SDH_INTSTS_CRCIF_Msk))   // Fault
    {
        uint32_t u32INTSTS = sdh->INTSTS;
        SDH_CLR_INT_FLAG(sdh, SDH_INTSTS_CRCIF_Msk);
        ret = __LINE__;

        if ((resp_type(cmd) != RESP_R3) && (u32INTSTS & SDH_INTSTS_CRC7_Msk) == 0)      //CRC7, Ignore R3
        {
            LOG_E("CRC7 error! (resp_type=%d)", resp_type(cmd));
            goto exit_nu_sdh_sendcmd;
        }

        if ((u32INTSTS & SDH_INTSTS_CRC16_Msk) == 0)   //CRC16
        {
            LOG_E("CRC16 error! (resp_type=%d)", resp_type(cmd));
            goto exit_nu_sdh_sendcmd;
        }
    }

    return 0;


exit_nu_sdh_sendcmd:

    LOG_D("[%s %d] cmdid=%d error line=%d", __func__, __LINE__, cmd->cmd_code, ret);

    cmd->resp[0] = cmd->resp[1] = cmd->resp[2] = cmd->resp[3] = 0;
    sdh->TOUT = 0;
    SDH_Enable(sdh);

    return -ret;
}

/**
  * @brief  This function send request.
  * @param  host  rt_mmcsd_host
  * @param  req   request
  * @retval None
  */
static void nu_sdh_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    nu_sdh_t NuSdh;
    SDH_T *sdh;

    RT_ASSERT(host);
    RT_ASSERT(req);

    NuSdh = (nu_sdh_t)host->private_data;
    sdh = NuSdh->base;

    if (!SDH_GetCD(sdh))   // card is not present
    {
        LOG_E("Card is not present");
        req->cmd->err = -RT_EIO;
        goto exit_nu_sdh_request;
    }

    if (req->cmd != RT_NULL)
    {
        struct rt_mmcsd_cmd *cmd = req->cmd;
        struct rt_mmcsd_data *data = req->data;

        LOG_D("[%s%s%s%s%s]REQ: CMD:%d ARG:0x%08x RESP_TYPE:%d rw:%c addr:%08x, blks:%d, blksize:%d datalen:%d",
              (host->card == RT_NULL) ? "Unknown" : "",
              (host->card) && (host->card->card_type == CARD_TYPE_MMC) ? "MMC" : "",
              (host->card) && (host->card->card_type == CARD_TYPE_SD) ? "SD" : "",
              (host->card) && (host->card->card_type == CARD_TYPE_SDIO) ? "SDIO" : "",
              (host->card) && (host->card->card_type == CARD_TYPE_SDIO_COMBO) ? "SDIO_COMBO" : "",
              cmd->cmd_code,
              cmd->arg,
              resp_type(cmd),
              data ? (data->flags & DATA_DIR_WRITE ?  'w' : 'r') : '-',
              data ? data->buf : 0,
              data ? data->blks : 0,
              data ? data->blksize : 0,
              data ? data->blks * data->blksize : 0);

        if (data != RT_NULL)
        {
            rt_uint32_t size;
            rt_int32_t IsNonaligned = 0;
            rt_uint32_t  *org_data_buf = data->buf;

            size = data->blksize * data->blks;

            RT_ASSERT(org_data_buf);

            IsNonaligned = (((rt_uint32_t)data->buf & (SDH_ALIGN_LEN - 1)) > 0) ? 1 : 0;
            if (IsNonaligned)
            {
                /* Allocate memory temp buffer on demand. */
                RT_ASSERT(size <= SDH_BUFF_SIZE);

                if (NuSdh->cachebuf == RT_NULL)
                {
                    NuSdh->cachebuf = rt_malloc_align(SDH_BUFF_SIZE, SDH_ALIGN_LEN);
                    RT_ASSERT(NuSdh->cachebuf);
                }

                data->buf = (rt_uint32_t *)NuSdh->cachebuf;
                if (data->flags & DATA_DIR_WRITE)
                {
                    LOG_D("Un-aligned, prepare into cache buf(%d)", size);
                    rt_memcpy(data->buf, org_data_buf, size);
                }
            }

            cmd->err = nu_sdh_sendcmd(host, cmd, data);

            if (!cmd->err && IsNonaligned)
            {
                if (data->flags & DATA_DIR_READ)
                {
                    LOG_D("Un-aligned, restore from cache buf(%d)", size);
                    rt_memcpy(org_data_buf, data->buf, size);
                }
            }
            data->buf = org_data_buf;

            LOG_HEX("data.dest", 16, (void *)data->buf, size);
        }
        else
        {
            cmd->err = nu_sdh_sendcmd(host, cmd, NULL);
        }

        if (resp_type(cmd) != RESP_NONE)
            LOG_HEX("cmd->resp", 16, (void *)&cmd->resp[0], 16);
    }

    if (req->stop != RT_NULL)
    {
        struct rt_mmcsd_cmd *stop = req->stop;

        stop->err = nu_sdh_sendcmd(host, stop, NULL);

        if (resp_type(stop) != RESP_NONE)
            LOG_HEX("stop->resp", 16, (void *)&stop->resp[0], 16);

    }

exit_nu_sdh_request:

    mmcsd_req_complete(host);
}

/**
  * @brief  This function config.
  * @param  host    rt_mmcsd_host
  * @param  io_cfg  rt_mmcsd_io_cfg
  * @retval None
  */
static void nu_sdh_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    nu_sdh_t NuSdh;
    rt_uint32_t clk;
    SDH_T *sdh;

    RT_ASSERT(host);
    RT_ASSERT(io_cfg);

    NuSdh = (nu_sdh_t)host->private_data;
    sdh = NuSdh->base;
    clk = io_cfg->clock;

    LOG_D("[%s]clk:%d width(%d):%s%s%s power:%s%s%s",
          NuSdh->name,
          clk,
          io_cfg->bus_width,
          (io_cfg->bus_width) == MMCSD_BUS_WIDTH_8 ? "8" : "",
          (io_cfg->bus_width) == MMCSD_BUS_WIDTH_4 ? "4" : "",
          (io_cfg->bus_width) == MMCSD_BUS_WIDTH_1 ? "1" : "",
          io_cfg->power_mode == MMCSD_POWER_OFF ? "OFF" : "",
          io_cfg->power_mode == MMCSD_POWER_UP ? "UP" : "",
          io_cfg->power_mode == MMCSD_POWER_ON ? "ON" : "");

    /* Clock */
    if (clk > host->freq_max)
        clk = host->freq_max;

    if (clk < host->freq_min)
        clk = host->freq_min;

    LOG_D("[%s] ExceptedFreq: %d kHz", NuSdh->name, clk / 1000);
    if (NuSdh->u32CurClk != (clk / 1000))
    {
        SDH_SetClock(sdh, clk / 1000);
        NuSdh->u32CurClk = (clk / 1000);
    }

    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_UP:
        if (clk <= 400000)
        {
            /* power ON 74 clock */
            sdh->CTL |= SDH_CTL_CLK74OEN_Msk;

            while ((sdh->CTL & SDH_CTL_CLK74OEN_Msk) == SDH_CTL_CLK74OEN_Msk)
            {
            }
        }
        break;

    case MMCSD_POWER_ON:
        break;

    case MMCSD_POWER_OFF:
        break;

    default:
        break;
    }

    /* Bus width */
    switch ((io_cfg->bus_width))
    {
    case MMCSD_BUS_WIDTH_1:
        SDH_SetBusWidth(sdh,  1);
        break;

    case MMCSD_BUS_WIDTH_4:
        SDH_SetBusWidth(sdh,  4);
        break;

    case MMCSD_BUS_WIDTH_8:
    default:
        break;
    }

}

/**
  * @brief  This function detect sdcard.
  * @param  host    rt_mmcsd_host
  * @retval card detection status
  */
static rt_int32_t nu_sdh_card_detect(struct rt_mmcsd_host *host)
{
    nu_sdh_t NuSdh;
    RT_ASSERT(host);

    NuSdh   = (nu_sdh_t)host->private_data;
    SDH_T *sdh = NuSdh->base;

    LOG_D("try to detect device");
    return SDH_GetCD(sdh);
}

static void nu_sdh_isr(nu_sdh_t NuSdh)
{
    SDH_T *sdh = NuSdh->base;
    uint32_t isr = sdh->INTSTS;

    /* card detected */
    if (isr & SDH_INTSTS_CDIF_Msk)
    {
        rt_tick_t cur_tick = rt_tick_get();
        rt_tick_t diff_tick;

        /* ready to change */
        if (cur_tick >= NuSdh->LastNotice)
            diff_tick = (cur_tick - NuSdh->LastNotice);
        else
            diff_tick = ((rt_tick_t) -1) - NuSdh->LastNotice + cur_tick;

        if (!NuSdh->LastNotice || (diff_tick > (RT_TICK_PER_SECOND / 5))) // Debounce 200ms
        {
            NuSdh->LastNotice = cur_tick;
            mmcsd_change(NuSdh->host);
        }

        /* Clear CDIF interrupt flag */
        SDH_CLR_INT_FLAG(sdh, SDH_INTSTS_CDIF_Msk);
    }
}

#if defined(BSP_USING_SDH0)
void SDH0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_sdh_isr(&nu_sdh_arr[SDH0_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SDH1)
void SDH1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_sdh_isr(&nu_sdh_arr[SDH1_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif


/**
  * @brief  This function update sdh interrupt.
  * @param  host    rt_mmcsd_host
  * @param  enable
  * @retval None
  */
void nu_sdh_irq_update(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    nu_sdh_t NuSdh = (nu_sdh_t)host->private_data;
    SDH_T *sdh = NuSdh->base;

    if (enable)
    {
        LOG_D("Enable %s irq", NuSdh->name);
        SDH_ENABLE_INT(sdh, SDH_INTSTS_CDIF_Msk);
    }
    else
    {
        LOG_D("Disable %s irq", NuSdh->name);
        SDH_DISABLE_INT(sdh, SDH_INTSTS_CDIF_Msk);
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
void nu_sdh_host_init(nu_sdh_t sdh)
{
    struct rt_mmcsd_host *host = mmcsd_alloc_host();
    RT_ASSERT(host);

    /* set host default attributes */
    host->ops = &ops;
    host->freq_min = 300 * 1000;
    host->freq_max = 48  * 1000 * 1000;
    host->valid_ocr = VDD_26_27 | VDD_27_28 | VDD_28_29 | VDD_29_30 | VDD_30_31 | VDD_31_32 | VDD_32_33 | VDD_33_34;

    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED;

    host->max_seg_size = SDH_BUFF_SIZE;
    host->max_dma_segs = 1;
    host->max_blk_size = SDH_BLOCK_SIZE;
    host->max_blk_count = (SDH_BUFF_SIZE / SDH_BLOCK_SIZE);

    /* link up host and sdio */
    host->private_data = sdh;
    sdh->host = host;

    /* Enable DMA engine at first. */
    SDH_Enable(sdh->base);

    /* Install ISR. */
    NVIC_EnableIRQ(sdh->irqn);

    /* ready to change */
    //mmcsd_change(host);
}

static int rt_hw_sdh_init(void)
{
    int i;

    for (i = (SDH_START + 1); i < SDH_CNT; i++)
    {
        CLK_EnableModuleClock(nu_sdh_arr[i].modid);
        SYS_ResetModule(nu_sdh_arr[i].rstidx);

        nu_sdh_host_init(&nu_sdh_arr[i]);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_sdh_init);

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
    for (i = (SDH_START + 1); i < SDH_CNT; i++)
    {
        if (nu_sdh_arr[i].host)
            LOG_HEX("sdh_reg", 16, (void *)nu_sdh_arr[i].base, sizeof(SDH_T));
    }
}
MSH_CMD_EXPORT(nu_sd_regdump, dump sdh registers);

#endif
