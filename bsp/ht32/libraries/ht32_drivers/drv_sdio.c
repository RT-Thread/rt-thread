/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-06     QT-one       first version
 */

#include <rtdbg.h>
#include "drv_sdio.h"

#ifdef BSP_USING_SDIO
#if !defined (BSP_USING_SDIO)
    #error "Please define at least one SDIOx"
#endif

#define RT_HW_SDIO_LOCK(_sdio) rt_mutex_take(&_sdio->mutex, RT_WAITING_FOREVER)
#define RT_HW_SDIO_UNLOCK(_sdio) rt_mutex_release(&_sdio->mutex);

typedef rt_err_t (*dma_txconfig)(rt_uint32_t *src, rt_uint32_t *dst, int size);
typedef rt_err_t (*dma_rxconfig)(rt_uint32_t *src, rt_uint32_t *dst, int size);
typedef rt_uint32_t (*sdio_clk_get)(HT_SDIO_TypeDef *hw_sdio);

struct ht32_sdio_config
{
    SDIO_InitTypeDef sdio_cfg;          /* SDIO Configuration Structure */
    PDMACH_InitTypeDef dma_tx_cfg;      /* TX DMA Configuration Structure */
    PDMACH_InitTypeDef dma_rx_cfg;      /* RX DMA Configuration Structure */
};

struct ht32_sdio_des
{
    HT_SDIO_TypeDef *hw_sdio;           /* Pointer to sdio hardware structure */
    dma_txconfig txconfig;              /* Pointer to the configuration function for the TX DMA */
    dma_rxconfig rxconfig;              /* Pointer to the configuration function for the RX DMA */
    sdio_clk_get clk_get;               /* Pointer to get sdio clock function */
};

struct sdio_pkg
{
    struct rt_mmcsd_cmd *cmd;           /* RTT-defined mmcsd command structure */
    void *buff;                         /* Pointer to hold data */
    SDIO_CmdInitTypeDef sdio_cmd_str;   /* Send Command Configuration */
    SDIO_DataInitTypeDef sdio_dat_str;  /* Send Data Configuration */
};

struct rt_hw_sdio
{
    struct rt_mmcsd_host *host;         /* mmcsd host structure */
    struct ht32_sdio_des sdio_des;      /* Configuration information for sdio */
    struct rt_event dat_event;          /* data event variable */
    struct rt_event cmd_event;          /* command event variable */
    struct rt_mutex mutex;              /* mutually exclusive variable */
    struct sdio_pkg *pkg;               /* package structure */
};

rt_align(SDIO_ALIGN_LEN)                        /* Ensure data alignment */
static rt_uint8_t cache_buf[SDIO_BUFF_SIZE];    /* Buff caches allocated to SDIOs */

static struct rt_mmcsd_host *host;
static struct ht32_sdio_config sdio_cfg;

static void sdio_delay(rt_uint32_t ms)
{
    while (ms > 0)
        ms--;
}

static rt_uint32_t ht32_sdio_clk_get(HT_SDIO_TypeDef *hw_sdio)
{
    return SDIO_CLOCK_FREQ;
}
/**
  * @brief  this function transfer data by dma.
  * @param  sdio rt_hw_sdio
  * @param  pkg sdio package
  * @retval none
  */
static void rt_hw_sdio_transfer_by_dma(struct rt_hw_sdio *sdio, struct sdio_pkg *pkg)
{
    struct rt_mmcsd_data *data;
    void *buff;
    HT_SDIO_TypeDef *hw_sdio;
    if ((RT_NULL == pkg) || (RT_NULL == sdio))
    {
        LOG_E("rt_hw_sdio_transfer_by_dma invalid args");
        return;
    }

    data = pkg->cmd->data;
    if (RT_NULL == data)
    {
        LOG_E("rt_hw_sdio_transfer_by_dma invalid args");
        return;
    }

    buff = pkg->buff;
    if (RT_NULL == buff)
    {
        LOG_E("rt_hw_sdio_transfer_by_dma invalid args");
        return;
    }

    hw_sdio = sdio->sdio_des.hw_sdio;
    if (data->flags & DATA_DIR_WRITE)
    {
        LOG_D("SDIO write!");
        sdio->sdio_des.txconfig((rt_uint32_t *)buff, (rt_uint32_t *)&hw_sdio->DR, (data->blks * data->blksize));
    }
    else if (data->flags & DATA_DIR_READ)
    {
        LOG_D("SDIO read!");
        sdio->sdio_des.rxconfig((rt_uint32_t *)&hw_sdio->DR, (rt_uint32_t *)buff, (data->blks * data->blksize));
    }
}
/**
  * @brief  this function send command.
  * @param  sdio rt_hw_sdio
  * @param  pkg sdio package
  * @retval none
  */
static void rt_hw_sdio_send_command(struct rt_hw_sdio *sdio, struct sdio_pkg *pkg)
{
    rt_uint32_t status = 0;
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    HT_SDIO_TypeDef *hw_sdio = sdio->sdio_des.hw_sdio;

    /* save pkg */
    sdio->pkg = pkg;

    LOG_D("CMD:%d ARG:0x%08x RES:%s%s%s%s%s%s%s%s%s rw:%c len:%d blksize:%d",
          cmd->cmd_code,
          cmd->arg,
          resp_type(cmd) == RESP_NONE ? "NONE"  : "",
          resp_type(cmd) == RESP_R1  ? "R1"  : "",
          resp_type(cmd) == RESP_R1B ? "R1B"  : "",
          resp_type(cmd) == RESP_R2  ? "R2"  : "",
          resp_type(cmd) == RESP_R3  ? "R3"  : "",
          resp_type(cmd) == RESP_R4  ? "R4"  : "",
          resp_type(cmd) == RESP_R5  ? "R5"  : "",
          resp_type(cmd) == RESP_R6  ? "R6"  : "",
          resp_type(cmd) == RESP_R7  ? "R7"  : "",
          data ? (data->flags & DATA_DIR_WRITE ?  'w' : 'r') : '-',
          data ? data->blks * data->blksize : 0,
          data ? data->blksize : 0
         );

    /* config cmd reg */
    pkg->sdio_cmd_str.SDIO_DatPresent   = SDIO_Data_Present_No;

    /* config data reg */
    if (data != RT_NULL)
    {
        rt_uint32_t dir = 0;
        dir = (data->flags & DATA_DIR_READ) ? SDIO_TransferDir_ToSDIO : SDIO_TransferDir_ToCard;
        if (SDIO_TransferDir_ToSDIO == dir) /* read */
            SDIO_FlagConfig(SDIO_FLAG_BUF_OVERFLOW | SDIO_FLAG_DATA_CRCERR | SDIO_FLAG_DATA_TIMEOUT | SDIO_FLAG_TRANS_END, ENABLE);
        else if (SDIO_TransferDir_ToCard == dir) /* write */
            SDIO_FlagConfig(SDIO_FLAG_BUF_UNDERFLOW | SDIO_FLAG_DATA_CRCERR | SDIO_FLAG_DATA_TIMEOUT | SDIO_FLAG_TRANS_END, ENABLE);
        if (data->blksize > 2048)
            LOG_E("Block length out of range!");
        pkg->sdio_dat_str.SDIO_DataBlockCount   = data->blks;                       /* Specify the number of data blocks to be transferred 1~65535 */
        pkg->sdio_dat_str.SDIO_DataBlockSize    = data->blksize;                    /* Specify the size of the data block to be transferred 1~2048 */
        pkg->sdio_dat_str.SDIO_DataTimeOut      = HW_SDIO_DATATIMEOUT;              /* Specify the data timeout period 0x1 ~ 0x00ffffff */
        pkg->sdio_dat_str.SDIO_TransferDir      = dir;                              /* Specify the direction of data transmission r/w */
        if (data->blks > 1)
            pkg->sdio_dat_str.SDIO_TransferMode     = SDIO_MultiBlock_DMA_Transfer;     /* multiblock transfer mode */
        else
            pkg->sdio_dat_str.SDIO_TransferMode     = SDIO_SingleBlock_DMA_Transfer;    /* single-block transfer mode */
        SDIO_DataConfig(&pkg->sdio_dat_str);

        pkg->sdio_cmd_str.SDIO_DatPresent       = SDIO_Data_Present_Yes;

        rt_hw_sdio_transfer_by_dma(sdio, pkg);
    }

    /* Configuring Response Mode */
    if (resp_type(cmd) == RESP_NONE)
        pkg->sdio_cmd_str.SDIO_Response     = SDIO_Response_No;
    else if (resp_type(cmd) == RESP_R2)
        pkg->sdio_cmd_str.SDIO_Response     = SDIO_Response_Long;
    else
        pkg->sdio_cmd_str.SDIO_Response     = SDIO_Response_Short;

    if (resp_type(cmd) & (RESP_R1 | RESP_R6))
        pkg->sdio_cmd_str.SDIO_CmdIdxChk    = SDIO_CmdIdxChk_Yes;
    else
        pkg->sdio_cmd_str.SDIO_CmdIdxChk    = SDIO_Data_Present_No;

    if (resp_type(cmd) & (RESP_R3))
        pkg->sdio_cmd_str.SDIO_CmdCrcChk    = SDIO_CmdCrcChk_No;
    else
        pkg->sdio_cmd_str.SDIO_CmdCrcChk    = SDIO_CmdCrcChk_Yes;
    /* send cmd */
    pkg->sdio_cmd_str.SDIO_Argument     = cmd->arg;                 /* sdio Command Parameters */
    pkg->sdio_cmd_str.SDIO_CmdIndex     = (cmd->cmd_code << 8);     /* Index of sdio commands  0x01 ~ 0x40*/
    /* open irq */
    SDIO_FlagConfig(HW_SDIO_CMD_FLAG, ENABLE);
    SDIO_IntConfig(HW_SDIO_CMD_FLAG, ENABLE);
    SDIO_SendCommand(&pkg->sdio_cmd_str);
    /* wait completed */
    if (rt_event_recv(&sdio->cmd_event, 0xffffffff, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      rt_tick_from_millisecond(5000), &status) != RT_EOK)
    {
        LOG_E("wait completed timeout");
        cmd->err = -RT_ETIMEOUT;
        return;
    }
    SDIO_IntConfig(HW_SDIO_CMD_FLAG, DISABLE);
    if (cmd->err != RT_EOK)
        LOG_D("cmd err!");

    /* waiting for data to be sent to completion */
    if (data != RT_NULL)
    {
        status = 0;
        SDIO_IntConfig(SDIO_INT_BUF_OVERFLOW | SDIO_INT_DATA_CRCERR | SDIO_INT_DATA_TIMEOUT | SDIO_INT_TRANS_END, ENABLE);
        if (rt_event_recv(&sdio->dat_event, 0xffffffff, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                          rt_tick_from_millisecond(5000), &status) != RT_EOK)
        {
            LOG_E("wait completed timeout");
            data->err = -RT_ETIMEOUT;
            return;
        }
        SDIO_IntConfig(SDIO_INT_BUF_OVERFLOW | SDIO_INT_DATA_CRCERR | SDIO_INT_DATA_TIMEOUT | SDIO_INT_TRANS_END, DISABLE);
        if (data->err != RT_EOK)
            LOG_D("data err!");
    }
    /* close irq, keep sdio irq */
    hw_sdio->IER = 0x00;
    /* clear pkg */
    sdio->pkg = RT_NULL;
}
/**
  * @brief  this function send sdio request.
  * @param  sdio rt_hw_sdio
  * @param  req request
  * @retval none
  */
static void rt_hw_sdio_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct sdio_pkg pkg;
    struct rt_hw_sdio *sdio = host->private_data;
    struct rt_mmcsd_data *data;

    RT_HW_SDIO_LOCK(sdio);
    /* Send commands and data */
    if (req->cmd != RT_NULL)
    {
        memset(&pkg, 0, sizeof(pkg));
        data = req->cmd->data;
        pkg.cmd = req->cmd;

        if (data != RT_NULL)
        {
            rt_uint32_t size = data->blks * data->blksize;
            RT_ASSERT(size <= SDIO_BUFF_SIZE);
            pkg.buff = data->buf;
            if ((rt_uint32_t)data->buf & (SDIO_ALIGN_LEN - 1))
            {
                pkg.buff = cache_buf;
                if (data->flags & DATA_DIR_WRITE)
                {
                    memcpy(cache_buf, data->buf, size);
                }
            }
        }
        rt_hw_sdio_send_command(sdio, &pkg);
        if ((data != RT_NULL) && (data->flags & DATA_DIR_READ) && ((rt_uint32_t)data->buf & (SDIO_ALIGN_LEN - 1)))
        {
            memcpy(data->buf, cache_buf, data->blksize * data->blks);
        }
    }
    /* Send stop command */
    if (req->stop != RT_NULL)
    {
        memset(&pkg, 0, sizeof(pkg));
        pkg.cmd = req->stop;
        rt_hw_sdio_send_command(sdio, &pkg);
    }
    RT_HW_SDIO_UNLOCK(sdio);
    mmcsd_req_complete(sdio->host);
}
/**
  * @brief  this function config sdio.
  * @param  host rt_mmcsd_host
  * @param  io_cfg rt_mmcsd_io_cfg
  * @retval none
  */
static void rt_hw_sdio_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_uint32_t div, clk_src;
    rt_uint32_t clk = io_cfg->clock;
    struct rt_hw_sdio *sdio = host->private_data;
    /* SDIO Clock Acquisition and Limiting */
    clk_src = sdio->sdio_des.clk_get(sdio->sdio_des.hw_sdio);
    if (clk_src < 400 * 1000)
    {
        LOG_E("Chip clock frequency too low! fre:%d", clk_src);
        return;
    }
    if (clk > host->freq_max) clk = host->freq_max;
    if (clk > clk_src)
    {
        LOG_W("Setting rate is greater than clock source rate.");
        clk = clk_src;
    }

    LOG_D("clk:%d width:%s%s%s power:%s%s%s",
          clk,
          io_cfg->bus_width == MMCSD_BUS_WIDTH_8 ? "8" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_4 ? "4" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_1 ? "1" : "",
          io_cfg->power_mode == MMCSD_POWER_OFF ? "OFF" : "",
          io_cfg->power_mode == MMCSD_POWER_UP ? "UP" : "",
          io_cfg->power_mode == MMCSD_POWER_ON ? "ON" : ""
         );

    RT_HW_SDIO_LOCK(sdio);
    /* SDIO Clock Division Configuration */
    div = clk_src / clk;
    if ((clk == 0) || (div == 0))
    {
        div = 1;
    }
    else
    {
        if (div < 1)
        {
            div = 1;
        }
        else if (div > 0xff)
        {
            div = 0xff;
        }
    }
    sdio_cfg.sdio_cfg.SDIO_ClockDiv         = div;
    if (div % 2)
        sdio_cfg.sdio_cfg.SDIO_ClockPeriod = SDIO_Clock_LowPeriod_Longer;
    else
        sdio_cfg.sdio_cfg.SDIO_ClockPeriod = SDIO_Clock_LowPeriod_Shorter;

    /* Data bus mode configuration */
    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
    {
        LOG_E("8-bit data width not supported!");
        return;
    }
    else if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        sdio_cfg.sdio_cfg.SDIO_BusWide = SDIO_BusWide_4b;
        sdio_cfg.sdio_cfg.SDIO_BusMode = SDIO_BusMode_HighSpeed;
    }
    else
    {
        sdio_cfg.sdio_cfg.SDIO_BusWide = SDIO_BusWide_1b;
        sdio_cfg.sdio_cfg.SDIO_BusMode = SDIO_BusMode_NormalSpeed;
    }
    /* Power Mode Configuration */
    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_OFF:
        sdio_cfg.sdio_cfg.SDIO_ClockPowerSave = SDIO_Clock_PowerSave_Disable;
        break;
    case MMCSD_POWER_UP:
        sdio_cfg.sdio_cfg.SDIO_ClockPowerSave = SDIO_Clock_PowerSave_StopHigh;
        break;
    case MMCSD_POWER_ON:
        sdio_cfg.sdio_cfg.SDIO_ClockPowerSave = SDIO_Clock_PowerSave_StopLow;
        break;
    default:
        LOG_W("unknown power_mode %d", io_cfg->power_mode);
        break;
    }
    SDIO_Init(&sdio_cfg.sdio_cfg);
    RT_HW_SDIO_UNLOCK(sdio);
}
/**
  * @brief  this function update sdio interrupt.
  * @param  host rt_mmcsd_host
  * @param  enable
  * @retval none
  */
void rt_hw_sdio_irq_update(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    if (enable)
    {
        LOG_D("enable sdio irq");
        NVIC_EnableIRQ(SDIO_IRQn);
    }
    else
    {
        LOG_D("disable sdio irq");
        NVIC_DisableIRQ(SDIO_IRQn);
    }
}
/**
  * @brief  this function delect sdcard.
  * @param  host rt_mmcsd_host
  * @retval 0x01
  */
static rt_int32_t rt_hw_sd_delect(struct rt_mmcsd_host *host)
{
    LOG_D("try to detect device");
    return 0x01;
}
/**
  * @brief  this function interrupt process function.
  * @param  host rt_mmcsd_host
  * @retval none
  */
void rt_hw_sdio_irq_process(struct rt_mmcsd_host *host)
{
    rt_uint8_t cmd_flag = 0;
    rt_uint8_t data_flag = 0;
    struct rt_hw_sdio *sdio = host->private_data;
    HT_SDIO_TypeDef *hw_sdio = sdio->sdio_des.hw_sdio;
    rt_uint32_t intstatus = hw_sdio->SR;
    struct rt_mmcsd_cmd *cmd = sdio->pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    if (sdio->pkg == NULL)
    {
        SDIO_FlagConfig(HW_SDIO_CMD_FLAG, DISABLE);
        SDIO_ClearFlag(HW_SDIO_CMD_FLAG);
        SDIO_FlagConfig(HW_SDIO_DATA_FLAG, DISABLE);
        SDIO_ClearFlag(HW_SDIO_DATA_FLAG);
        return;
    }
    /* Command Response Processing */
    if (cmd != NULL)
    {
        if (intstatus != 0x00000001)
            sdio_delay(10000);
        cmd->resp[0] = hw_sdio->RESP0;
        cmd->resp[1] = hw_sdio->RESP1;
        cmd->resp[2] = hw_sdio->RESP2;
        cmd->resp[3] = hw_sdio->RESP3;
        cmd->err = RT_EOK;
        if (SDIO_GetFlagStatus(SDIO_FLAG_CMD_SEND))
        {
            SDIO_FlagConfig(HW_SDIO_CMD_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_CMD_SEND);
            cmd_flag = 1;
        }
        if (SDIO_GetFlagStatus(SDIO_FLAG_CMD_TIMEOUT))
        {
            SDIO_FlagConfig(HW_SDIO_CMD_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_CMD_TIMEOUT);
            RESET_CPSM();
            cmd->err = -RT_ETIMEOUT;
            cmd_flag = 1;
        }
        if ((SDIO_GetFlagStatus(SDIO_FLAG_CMD_CRCERR)) && (resp_type(cmd) & (RESP_R3 | RESP_R4)))
        {
            SDIO_FlagConfig(HW_SDIO_CMD_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_CMD_CRCERR);
            cmd->err = RT_EOK;
            cmd_flag = 1;
        }
        else if (SDIO_GetFlagStatus(SDIO_FLAG_CMD_CRCERR))
        {
            SDIO_FlagConfig(HW_SDIO_CMD_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_CMD_CRCERR);
            cmd->err = -RT_ERROR;
            cmd_flag = 1;
        }
        if ((SDIO_GetFlagStatus(SDIO_FLAG_CMD_IDXERR)) && (resp_type(cmd) & (RESP_R1 | RESP_R6)) && (cmd->err == RT_EOK))
        {
            SDIO_FlagConfig(HW_SDIO_CMD_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_CMD_IDXERR);
            cmd->err = RT_EOK;
            cmd_flag = 1;
        }
        else if (SDIO_GetFlagStatus(SDIO_FLAG_CMD_IDXERR))
        {
            SDIO_FlagConfig(HW_SDIO_CMD_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_CMD_IDXERR);
            cmd->err = -RT_ERROR;
            cmd_flag = 1;
        }
        if (cmd_flag)
        {
            rt_event_send(&sdio->cmd_event, intstatus);
        }
    }
    /* Data response processing */
    if (data != NULL)
    {
        data->err = RT_EOK;
        if (SDIO_GetFlagStatus(SDIO_FLAG_TRANS_END))
        {
            SDIO_FlagConfig(HW_SDIO_DATA_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_TRANS_END);
            data_flag = 1;
        }

        if (SDIO_GetFlagStatus(SDIO_FLAG_DATA_TIMEOUT))
        {
            SDIO_FlagConfig(HW_SDIO_DATA_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_DATA_TIMEOUT);
            data->err = -RT_ETIMEOUT;
            data_flag = 1;
        }
        if (SDIO_GetFlagStatus(SDIO_FLAG_DATA_CRCERR))
        {
            SDIO_FlagConfig(HW_SDIO_DATA_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_DATA_CRCERR);
            data->err = -RT_ERROR;
            data_flag = 1;
        }
        if (SDIO_GetFlagStatus(SDIO_FLAG_BUF_OVERFLOW))
        {
            SDIO_FlagConfig(HW_SDIO_DATA_FLAG, DISABLE);
            SDIO_ClearFlag(SDIO_FLAG_BUF_OVERFLOW);
            data->err = -RT_ERROR;
            data_flag = 1;
        }
        /* 如果操作完成 */
        if (data_flag)
        {
            rt_event_send(&sdio->dat_event, intstatus);         /* 发送事件，通知操作完成 */
        }
    }


}
static const struct rt_mmcsd_host_ops ops =
{
    .request            = rt_hw_sdio_request,
    .set_iocfg          = rt_hw_sdio_iocfg,
    .get_card_status    = rt_hw_sd_delect,
    .enable_sdio_irq    = rt_hw_sdio_irq_update,
};
/**
  * @brief  this function create mmcsd host.
  * @param  sdio_des at32_sdio_des
  * @retval rt_mmcsd_host
  */
struct rt_mmcsd_host *sdio_host_create(struct ht32_sdio_des *sdio_des)
{
    struct rt_mmcsd_host *host;
    struct rt_hw_sdio *sdio = RT_NULL;
    /* effective parameter */
    if ((sdio_des == RT_NULL) || (sdio_des->txconfig == RT_NULL) || (sdio_des->rxconfig == RT_NULL))
    {
        LOG_E("L:%d F:%s %s %s %s",
              (sdio_des == RT_NULL ? "sdio_des is NULL" : ""),
              (sdio_des ? (sdio_des->txconfig ? "txconfig is NULL" : "") : ""),
              (sdio_des ? (sdio_des->rxconfig ? "rxconfig is NULL" : "") : "")
             );
        return RT_NULL;
    }

    sdio = rt_malloc(sizeof(struct rt_hw_sdio));
    if (sdio == RT_NULL)
    {
        LOG_E("L:%d F:%s malloc rt_hw_sdio fail");
        return RT_NULL;
    }
    rt_memset(sdio, 0, sizeof(struct rt_hw_sdio));

    host = mmcsd_alloc_host();
    if (host == RT_NULL)
    {
        LOG_E("L:%d F:%s mmcsd alloc host fail");
        rt_free(sdio);
        return RT_NULL;
    }

    rt_memcpy(&sdio->sdio_des, sdio_des, sizeof(struct ht32_sdio_des));
    sdio->sdio_des.hw_sdio = (sdio_des->hw_sdio == RT_NULL ? (HT_SDIO_TypeDef *)SDIO_BASE_ADDRESS : sdio_des->hw_sdio);
    sdio->sdio_des.clk_get = (sdio_des->clk_get == RT_NULL ? ht32_sdio_clk_get : sdio_des->clk_get);
    /* Initialising events and mutexes */
    rt_event_init(&sdio->dat_event, "sdio", RT_IPC_FLAG_FIFO);
    rt_event_init(&sdio->cmd_event, "sdio_cmd", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&sdio->mutex, "sdio", RT_IPC_FLAG_PRIO);

    /* set host defautl attributes */
    host->ops = &ops;
    host->freq_min = 400 * 1000;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = 0X00FFFF80;
#ifndef SDIO_USING_1_BIT
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ;
#else
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ;
#endif
    host->max_seg_size = SDIO_BUFF_SIZE;
    host->max_dma_segs = 1;
    host->max_blk_size = 512;
    host->max_blk_count = 512;

    /* link up host and sdio */
    sdio->host = host;
    host->private_data = sdio;

    rt_hw_sdio_irq_update(host, 1);

    /* ready to change */
    mmcsd_change(host);

    return host;
}

/**
  * @brief  this function configures the dmatx.
  * @param  src: pointer to the source buffer
  * @param  dst: pointer to the destination buffer
  * @param  buffer_size: size of tx buffer
  * @retval none
  */
void sd_lowlevel_dmatx_config(uint32_t *src, uint32_t *dst, uint32_t buffer_size)
{
    PDMACH_InitTypeDef PDMACH_InitStruct;
    /* Configure */
    PDMACH_InitStruct.PDMACH_SrcAddr = (u32)src;
    PDMACH_InitStruct.PDMACH_DstAddr = (u32)dst;
    PDMACH_InitStruct.PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
    PDMACH_InitStruct.PDMACH_BlkCnt = buffer_size;
    PDMACH_InitStruct.PDMACH_BlkLen = 1;
    PDMACH_InitStruct.PDMACH_DataSize = WIDTH_32BIT;
    PDMACH_InitStruct.PDMACH_Priority = H_PRIO;
    PDMA_Config(PDMA_SDIO_TX, &PDMACH_InitStruct);
    PDMA_IntConfig(PDMA_SDIO_TX, (PDMA_INT_GE | PDMA_INT_TC | PDMA_INT_TE), ENABLE);
    NVIC_EnableIRQ(PDMACH7_IRQn);
    PDMA_EnaCmd(PDMA_SDIO_TX, ENABLE);
}

/**
  * @brief  this function configures the dmarx.
  * @param  src: pointer to the source buffer
  * @param  dst: pointer to the destination buffer
  * @param  buffer_size: size of rx buffer
  * @retval none
  */
void sd_lowlevel_dmarx_config(uint32_t *src, uint32_t *dst, uint32_t buffer_size)
{
    PDMACH_InitTypeDef PDMACH_InitStruct;
    /* Configure */
    PDMACH_InitStruct.PDMACH_SrcAddr = (u32)src;
    PDMACH_InitStruct.PDMACH_DstAddr = (u32)dst;
    PDMACH_InitStruct.PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC;
    PDMACH_InitStruct.PDMACH_BlkCnt = buffer_size;
    PDMACH_InitStruct.PDMACH_BlkLen = 1;
    PDMACH_InitStruct.PDMACH_DataSize = WIDTH_32BIT;
    PDMACH_InitStruct.PDMACH_Priority = H_PRIO;
    PDMA_Config(PDMA_SDIO_RX, &PDMACH_InitStruct);
    PDMA_IntConfig(PDMA_SDIO_RX, (PDMA_INT_GE | PDMA_INT_TC | PDMA_INT_TE), ENABLE);
    NVIC_EnableIRQ(PDMACH6_IRQn);
    PDMA_EnaCmd(PDMA_SDIO_RX, ENABLE);
}


/**
  * @brief  this function get at32 sdio clock.
  * @param  hw_sdio: at32_sdio
  * @retval ahb frequency
  */
static rt_uint32_t ht32_sdio_clock_get(HT_SDIO_TypeDef *hw_sdio)
{
    return SystemCoreClock;
}
static rt_err_t dma_tx_config(rt_uint32_t *src, rt_uint32_t *dst, int size)
{
    sd_lowlevel_dmatx_config((uint32_t *)src, (uint32_t *)dst, size / 4);
    return RT_EOK;
}
static rt_err_t dma_rx_config(rt_uint32_t *src, rt_uint32_t *dst, int size)
{
    sd_lowlevel_dmarx_config((uint32_t *)src, (uint32_t *)dst, size / 4);
    return RT_EOK;
}

int rt_hw_sdio_init(void)
{
    struct ht32_sdio_des sdio_des;

    ht32_sdio_gpio_init((void *)(HT_SDIO));
    sdio_des.clk_get = ht32_sdio_clock_get;
    sdio_des.hw_sdio = (HT_SDIO_TypeDef *)HT_SDIO;
    sdio_des.rxconfig = dma_rx_config;
    sdio_des.txconfig = dma_tx_config;
    host = sdio_host_create(&sdio_des);
    if (host == RT_NULL)
    {
        LOG_E("host create fail");
        return -1;
    }
    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_sdio_init);

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH6 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH6_IRQHandler(void)
{
    if (HT_PDMA->ISR1 & (PDMA_FLAG_TE << ((PDMA_CH6 - 6) * 5)))
    {
        LOG_E(" TE6");
        while (1);
    }

    HT_PDMA->ISCR1 = PDMA_FLAG_TC << ((PDMA_CH6 - 6) * 5);
    PDMA_EnaCmd(PDMA_SDIO_RX, DISABLE);
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA_CH7 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH7_IRQHandler(void)
{
    if (HT_PDMA->ISR1 & (PDMA_FLAG_TE << ((PDMA_CH7 - 6) * 5)))
    {
        LOG_E(" TE7");
        while (1);
    }

    HT_PDMA->ISCR1 = PDMA_FLAG_TC << ((PDMA_CH7 - 6) * 5);
    PDMA_EnaCmd(PDMA_SDIO_TX, DISABLE);
}

/*********************************************************************************************************//**
 * @brief   This function handles SDIO interrupt.
 * @retval  None
 ************************************************************************************************************/
void SDIO_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_sdio_irq_process(host);
    /* leave interrupt */
    rt_interrupt_leave();
}

void ht32_mmcsd_change(void)
{
    mmcsd_change(host);
}

#endif /* BSP_USING_SDIO */
