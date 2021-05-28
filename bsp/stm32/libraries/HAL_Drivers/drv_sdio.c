/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-22     tyx          first
 * 2018-12-12     balanceTWK   first version
 * 2019-06-11     WillianChan  Add SD card hot plug detection
 * 2020-11-09     whj4674672   fix sdio non-aligned access problem
 */

#include "board.h"
#include "drv_sdio.h"
#include "drv_config.h"

#ifdef BSP_USING_SDIO

//#define DRV_DEBUG
#define LOG_TAG             "drv.sdio"
#include <drv_log.h>

static struct stm32_sdio_config sdio_config = SDIO_BUS_CONFIG;
static struct stm32_sdio_class sdio_obj;
static struct rt_mmcsd_host *host;

#define SDIO_TX_RX_COMPLETE_TIMEOUT_LOOPS    (100000)

#define RTHW_SDIO_LOCK(_sdio)   rt_mutex_take(&_sdio->mutex, RT_WAITING_FOREVER)
#define RTHW_SDIO_UNLOCK(_sdio) rt_mutex_release(&_sdio->mutex);

struct sdio_pkg
{
    struct rt_mmcsd_cmd *cmd;
    void *buff;
    rt_uint32_t flag;
};

struct rthw_sdio
{
    struct rt_mmcsd_host *host;
    struct stm32_sdio_des sdio_des;
    struct rt_event event;
    struct rt_mutex mutex;
    struct sdio_pkg *pkg;
};

ALIGN(SDIO_ALIGN_LEN)
static rt_uint8_t cache_buf[SDIO_BUFF_SIZE];

static rt_uint32_t stm32_sdio_clk_get(struct stm32_sdio *hw_sdio)
{
    return SDIO_CLOCK_FREQ;
}

/**
  * @brief  This function get order from sdio.
  * @param  data
  * @retval sdio  order
  */
static int get_order(rt_uint32_t data)
{
    int order = 0;

    switch (data)
    {
    case 1:
        order = 0;
        break;
    case 2:
        order = 1;
        break;
    case 4:
        order = 2;
        break;
    case 8:
        order = 3;
        break;
    case 16:
        order = 4;
        break;
    case 32:
        order = 5;
        break;
    case 64:
        order = 6;
        break;
    case 128:
        order = 7;
        break;
    case 256:
        order = 8;
        break;
    case 512:
        order = 9;
        break;
    case 1024:
        order = 10;
        break;
    case 2048:
        order = 11;
        break;
    case 4096:
        order = 12;
        break;
    case 8192:
        order = 13;
        break;
    case 16384:
        order = 14;
        break;
    default :
        order = 0;
        break;
    }

    return order;
}

/**
  * @brief  This function wait sdio completed.
  * @param  sdio  rthw_sdio
  * @retval None
  */
static void rthw_sdio_wait_completed(struct rthw_sdio *sdio)
{
    rt_uint32_t status;
    struct rt_mmcsd_cmd *cmd = sdio->pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    struct stm32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;

    if (rt_event_recv(&sdio->event, 0xffffffff, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      rt_tick_from_millisecond(5000), &status) != RT_EOK)
    {
        LOG_E("wait completed timeout");
        cmd->err = -RT_ETIMEOUT;
        return;
    }

    if (sdio->pkg == RT_NULL)
    {
        return;
    }

    cmd->resp[0] = hw_sdio->resp1;
    cmd->resp[1] = hw_sdio->resp2;
    cmd->resp[2] = hw_sdio->resp3;
    cmd->resp[3] = hw_sdio->resp4;

    if (status & HW_SDIO_ERRORS)
    {
        if ((status & HW_SDIO_IT_CCRCFAIL) && (resp_type(cmd) & (RESP_R3 | RESP_R4)))
        {
            cmd->err = RT_EOK;
        }
        else
        {
            cmd->err = -RT_ERROR;
        }

        if (status & HW_SDIO_IT_CTIMEOUT)
        {
            cmd->err = -RT_ETIMEOUT;
        }

        if (status & HW_SDIO_IT_DCRCFAIL)
        {
            data->err = -RT_ERROR;
        }

        if (status & HW_SDIO_IT_DTIMEOUT)
        {
            data->err = -RT_ETIMEOUT;
        }

        if (cmd->err == RT_EOK)
        {
            LOG_D("sta:0x%08X [%08X %08X %08X %08X]", status, cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
        }
        else
        {
            LOG_D("err:0x%08x, %s%s%s%s%s%s%s cmd:%d arg:0x%08x rw:%c len:%d blksize:%d",
                  status,
                  status & HW_SDIO_IT_CCRCFAIL  ? "CCRCFAIL "    : "",
                  status & HW_SDIO_IT_DCRCFAIL  ? "DCRCFAIL "    : "",
                  status & HW_SDIO_IT_CTIMEOUT  ? "CTIMEOUT "    : "",
                  status & HW_SDIO_IT_DTIMEOUT  ? "DTIMEOUT "    : "",
                  status & HW_SDIO_IT_TXUNDERR  ? "TXUNDERR "    : "",
                  status & HW_SDIO_IT_RXOVERR   ? "RXOVERR "     : "",
                  status == 0                   ? "NULL"         : "",
                  cmd->cmd_code,
                  cmd->arg,
                  data ? (data->flags & DATA_DIR_WRITE ?  'w' : 'r') : '-',
                  data ? data->blks * data->blksize : 0,
                  data ? data->blksize : 0
                 );
        }
    }
    else
    {
        cmd->err = RT_EOK;
        LOG_D("sta:0x%08X [%08X %08X %08X %08X]", status, cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
    }
}

/**
  * @brief  This function transfer data by dma.
  * @param  sdio  rthw_sdio
  * @param  pkg   sdio package
  * @retval None
  */
static void rthw_sdio_transfer_by_dma(struct rthw_sdio *sdio, struct sdio_pkg *pkg)
{
    struct rt_mmcsd_data *data;
    int size;
    void *buff;
    struct stm32_sdio *hw_sdio;

    if ((RT_NULL == pkg) || (RT_NULL == sdio))
    {
        LOG_E("rthw_sdio_transfer_by_dma invalid args");
        return;
    }

    data = pkg->cmd->data;
    if (RT_NULL == data)
    {
        LOG_E("rthw_sdio_transfer_by_dma invalid args");
        return;
    }

    buff = pkg->buff;
    if (RT_NULL == buff)
    {
        LOG_E("rthw_sdio_transfer_by_dma invalid args");
        return;
    }
    hw_sdio = sdio->sdio_des.hw_sdio;
    size = data->blks * data->blksize;

    if (data->flags & DATA_DIR_WRITE)
    {
        sdio->sdio_des.txconfig((rt_uint32_t *)buff, (rt_uint32_t *)&hw_sdio->fifo, size);
        hw_sdio->dctrl |= HW_SDIO_DMA_ENABLE;
    }
    else if (data->flags & DATA_DIR_READ)
    {
        sdio->sdio_des.rxconfig((rt_uint32_t *)&hw_sdio->fifo, (rt_uint32_t *)buff, size);
        hw_sdio->dctrl |= HW_SDIO_DMA_ENABLE | HW_SDIO_DPSM_ENABLE;
    }
}

/**
  * @brief  This function send command.
  * @param  sdio  rthw_sdio
  * @param  pkg   sdio package
  * @retval None
  */
static void rthw_sdio_send_command(struct rthw_sdio *sdio, struct sdio_pkg *pkg)
{
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    struct stm32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;
    rt_uint32_t reg_cmd;

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
    reg_cmd = cmd->cmd_code | HW_SDIO_CPSM_ENABLE;
    if (resp_type(cmd) == RESP_NONE)
        reg_cmd |= HW_SDIO_RESPONSE_NO;
    else if (resp_type(cmd) == RESP_R2)
        reg_cmd |= HW_SDIO_RESPONSE_LONG;
    else
        reg_cmd |= HW_SDIO_RESPONSE_SHORT;

    /* config data reg */
    if (data != RT_NULL)
    {
        rt_uint32_t dir = 0;
        rt_uint32_t size = data->blks * data->blksize;
        int order;

        hw_sdio->dctrl = 0;
        hw_sdio->dtimer = HW_SDIO_DATATIMEOUT;
        hw_sdio->dlen = size;
        order = get_order(data->blksize);
        dir = (data->flags & DATA_DIR_READ) ? HW_SDIO_TO_HOST : 0;
        hw_sdio->dctrl = HW_SDIO_IO_ENABLE | (order << 4) | dir;
    }

    /* transfer config */
    if (data != RT_NULL)
    {
        rthw_sdio_transfer_by_dma(sdio, pkg);
    }

    /* open irq */
    hw_sdio->mask |= HW_SDIO_IT_CMDSENT | HW_SDIO_IT_CMDREND | HW_SDIO_ERRORS;
    if (data != RT_NULL)
    {
        hw_sdio->mask |= HW_SDIO_IT_DATAEND;
    }

    /* send cmd */
    hw_sdio->arg = cmd->arg;
    hw_sdio->cmd = reg_cmd;

    /* wait completed */
    rthw_sdio_wait_completed(sdio);

    /* Waiting for data to be sent to completion */
    if (data != RT_NULL)
    {
        volatile rt_uint32_t count = SDIO_TX_RX_COMPLETE_TIMEOUT_LOOPS;

        while (count && (hw_sdio->sta & (HW_SDIO_IT_TXACT | HW_SDIO_IT_RXACT)))
        {
            count--;
        }

        if ((count == 0) || (hw_sdio->sta & HW_SDIO_ERRORS))
        {
            cmd->err = -RT_ERROR;
        }
    }

    /* close irq, keep sdio irq */
    hw_sdio->mask = hw_sdio->mask & HW_SDIO_IT_SDIOIT ? HW_SDIO_IT_SDIOIT : 0x00;

    /* clear pkg */
    sdio->pkg = RT_NULL;
}

/**
  * @brief  This function send sdio request.
  * @param  host  rt_mmcsd_host
  * @param  req   request
  * @retval None
  */
static void rthw_sdio_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct sdio_pkg pkg;
    struct rthw_sdio *sdio = host->private_data;
    struct rt_mmcsd_data *data;

    RTHW_SDIO_LOCK(sdio);

    if (req->cmd != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
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
                    rt_memcpy(cache_buf, data->buf, size);
                }
            }
        }

        rthw_sdio_send_command(sdio, &pkg);

        if ((data != RT_NULL) && (data->flags & DATA_DIR_READ) && ((rt_uint32_t)data->buf & (SDIO_ALIGN_LEN - 1)))
        {
            rt_memcpy(data->buf, cache_buf, data->blksize * data->blks);
        }
    }

    if (req->stop != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
        pkg.cmd = req->stop;
        rthw_sdio_send_command(sdio, &pkg);
    }

    RTHW_SDIO_UNLOCK(sdio);

    mmcsd_req_complete(sdio->host);
}

/**
  * @brief  This function config sdio.
  * @param  host    rt_mmcsd_host
  * @param  io_cfg  rt_mmcsd_io_cfg
  * @retval None
  */
static void rthw_sdio_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_uint32_t clkcr, div, clk_src;
    rt_uint32_t clk = io_cfg->clock;
    struct rthw_sdio *sdio = host->private_data;
    struct stm32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;

    clk_src = sdio->sdio_des.clk_get(sdio->sdio_des.hw_sdio);
    if (clk_src < 400 * 1000)
    {
        LOG_E("The clock rate is too low! rata:%d", clk_src);
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

    RTHW_SDIO_LOCK(sdio);

    div = clk_src / clk;
    if ((clk == 0) || (div == 0))
    {
        clkcr = 0;
    }
    else
    {
        if (div < 2)
        {
            div = 2;
        }
        else if (div > 0xFF)
        {
            div = 0xFF;
        }
        div -= 2;
        clkcr = div | HW_SDIO_CLK_ENABLE;
    }

    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
    {
        clkcr |= HW_SDIO_BUSWIDE_8B;
    }
    else if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
    {
        clkcr |= HW_SDIO_BUSWIDE_4B;
    }
    else
    {
        clkcr |= HW_SDIO_BUSWIDE_1B;
    }

    hw_sdio->clkcr = clkcr;

    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_OFF:
        hw_sdio->power = HW_SDIO_POWER_OFF;
        break;
    case MMCSD_POWER_UP:
        hw_sdio->power = HW_SDIO_POWER_UP;
        break;
    case MMCSD_POWER_ON:
        hw_sdio->power = HW_SDIO_POWER_ON;
        break;
    default:
        LOG_W("unknown power_mode %d", io_cfg->power_mode);
        break;
    }

    RTHW_SDIO_UNLOCK(sdio);
}

/**
  * @brief  This function update sdio interrupt.
  * @param  host    rt_mmcsd_host
  * @param  enable
  * @retval None
  */
void rthw_sdio_irq_update(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    struct rthw_sdio *sdio = host->private_data;
    struct stm32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;

    if (enable)
    {
        LOG_D("enable sdio irq");
        hw_sdio->mask |= HW_SDIO_IT_SDIOIT;
    }
    else
    {
        LOG_D("disable sdio irq");
        hw_sdio->mask &= ~HW_SDIO_IT_SDIOIT;
    }
}

/**
  * @brief  This function detect sdcard.
  * @param  host    rt_mmcsd_host
  * @retval 0x01
  */
static rt_int32_t rthw_sd_detect(struct rt_mmcsd_host *host)
{
    LOG_D("try to detect device");
    return 0x01;
}

/**
  * @brief  This function interrupt process function.
  * @param  host  rt_mmcsd_host
  * @retval None
  */
void rthw_sdio_irq_process(struct rt_mmcsd_host *host)
{
    int complete = 0;
    struct rthw_sdio *sdio = host->private_data;
    struct stm32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;
    rt_uint32_t intstatus = hw_sdio->sta;

    if (intstatus & HW_SDIO_ERRORS)
    {
        hw_sdio->icr = HW_SDIO_ERRORS;
        complete = 1;
    }
    else
    {
        if (intstatus & HW_SDIO_IT_CMDREND)
        {
            hw_sdio->icr = HW_SDIO_IT_CMDREND;

            if (sdio->pkg != RT_NULL)
            {
                if (!sdio->pkg->cmd->data)
                {
                    complete = 1;
                }
                else if ((sdio->pkg->cmd->data->flags & DATA_DIR_WRITE))
                {
                    hw_sdio->dctrl |= HW_SDIO_DPSM_ENABLE;
                }
            }
        }

        if (intstatus & HW_SDIO_IT_CMDSENT)
        {
            hw_sdio->icr = HW_SDIO_IT_CMDSENT;

            if (resp_type(sdio->pkg->cmd) == RESP_NONE)
            {
                complete = 1;
            }
        }

        if (intstatus & HW_SDIO_IT_DATAEND)
        {
            hw_sdio->icr = HW_SDIO_IT_DATAEND;
            complete = 1;
        }
    }

    if ((intstatus & HW_SDIO_IT_SDIOIT) && (hw_sdio->mask & HW_SDIO_IT_SDIOIT))
    {
        hw_sdio->icr = HW_SDIO_IT_SDIOIT;
        sdio_irq_wakeup(host);
    }

    if (complete)
    {
        hw_sdio->mask &= ~HW_SDIO_ERRORS;
        rt_event_send(&sdio->event, intstatus);
    }
}

static const struct rt_mmcsd_host_ops ops =
{
    rthw_sdio_request,
    rthw_sdio_iocfg,
    rthw_sd_detect,
    rthw_sdio_irq_update,
};

/**
  * @brief  This function create mmcsd host.
  * @param  sdio_des  stm32_sdio_des
  * @retval rt_mmcsd_host
  */
struct rt_mmcsd_host *sdio_host_create(struct stm32_sdio_des *sdio_des)
{
    struct rt_mmcsd_host *host;
    struct rthw_sdio *sdio = RT_NULL;

    if ((sdio_des == RT_NULL) || (sdio_des->txconfig == RT_NULL) || (sdio_des->rxconfig == RT_NULL))
    {
        LOG_E("L:%d F:%s %s %s %s",
              (sdio_des == RT_NULL ? "sdio_des is NULL" : ""),
              (sdio_des ? (sdio_des->txconfig ? "txconfig is NULL" : "") : ""),
              (sdio_des ? (sdio_des->rxconfig ? "rxconfig is NULL" : "") : "")
             );
        return RT_NULL;
    }

    sdio = rt_malloc(sizeof(struct rthw_sdio));
    if (sdio == RT_NULL)
    {
        LOG_E("L:%d F:%s malloc rthw_sdio fail");
        return RT_NULL;
    }
    rt_memset(sdio, 0, sizeof(struct rthw_sdio));

    host = mmcsd_alloc_host();
    if (host == RT_NULL)
    {
        LOG_E("L:%d F:%s mmcsd alloc host fail");
        rt_free(sdio);
        return RT_NULL;
    }

    rt_memcpy(&sdio->sdio_des, sdio_des, sizeof(struct stm32_sdio_des));
    sdio->sdio_des.hw_sdio = (sdio_des->hw_sdio == RT_NULL ? (struct stm32_sdio *)SDIO_BASE_ADDRESS : sdio_des->hw_sdio);
    sdio->sdio_des.clk_get = (sdio_des->clk_get == RT_NULL ? stm32_sdio_clk_get : sdio_des->clk_get);

    rt_event_init(&sdio->event, "sdio", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&sdio->mutex, "sdio", RT_IPC_FLAG_FIFO);

    /* set host defautl attributes */
    host->ops = &ops;
    host->freq_min = 400 * 1000;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = 0X00FFFF80;/* The voltage range supported is 1.65v-3.6v */
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

    rthw_sdio_irq_update(host, 1);

    /* ready to change */
    mmcsd_change(host);

    return host;
}

/**
  * @brief  This function configures the DMATX.
  * @param  BufferSRC: pointer to the source buffer
  * @param  BufferSize: buffer size
  * @retval None
  */
void SD_LowLevel_DMA_TxConfig(uint32_t *src, uint32_t *dst, uint32_t BufferSize)
{
#if defined(SOC_SERIES_STM32F1)
    static uint32_t size = 0;
    size += BufferSize * 4;
    sdio_obj.cfg = &sdio_config;
    sdio_obj.dma.handle_tx.Instance = sdio_config.dma_tx.Instance;
    sdio_obj.dma.handle_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    sdio_obj.dma.handle_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    sdio_obj.dma.handle_tx.Init.MemInc              = DMA_MINC_ENABLE;
    sdio_obj.dma.handle_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    sdio_obj.dma.handle_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    sdio_obj.dma.handle_tx.Init.Priority            = DMA_PRIORITY_MEDIUM;
    /* DMA_PFCTRL */
    HAL_DMA_DeInit(&sdio_obj.dma.handle_tx);
    HAL_DMA_Init(&sdio_obj.dma.handle_tx);

    HAL_DMA_Start(&sdio_obj.dma.handle_tx, (uint32_t)src, (uint32_t)dst, BufferSize);

#elif defined(SOC_SERIES_STM32L4)
    static uint32_t size = 0;
    size += BufferSize * 4;
    sdio_obj.cfg = &sdio_config;
    sdio_obj.dma.handle_tx.Instance = sdio_config.dma_tx.Instance;
    sdio_obj.dma.handle_tx.Init.Request             = sdio_config.dma_tx.request;
    sdio_obj.dma.handle_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    sdio_obj.dma.handle_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    sdio_obj.dma.handle_tx.Init.MemInc              = DMA_MINC_ENABLE;
    sdio_obj.dma.handle_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    sdio_obj.dma.handle_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    sdio_obj.dma.handle_tx.Init.Mode                = DMA_NORMAL;
    sdio_obj.dma.handle_tx.Init.Priority            = DMA_PRIORITY_MEDIUM;

    HAL_DMA_DeInit(&sdio_obj.dma.handle_tx);
    HAL_DMA_Init(&sdio_obj.dma.handle_tx);

    HAL_DMA_Start(&sdio_obj.dma.handle_tx, (uint32_t)src, (uint32_t)dst, BufferSize);
#else
    static uint32_t size = 0;
    size += BufferSize * 4;
    sdio_obj.cfg = &sdio_config;
    sdio_obj.dma.handle_tx.Instance = sdio_config.dma_tx.Instance;
    sdio_obj.dma.handle_tx.Init.Channel = sdio_config.dma_tx.channel;
    sdio_obj.dma.handle_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    sdio_obj.dma.handle_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    sdio_obj.dma.handle_tx.Init.MemInc              = DMA_MINC_ENABLE;
    sdio_obj.dma.handle_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    sdio_obj.dma.handle_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    sdio_obj.dma.handle_tx.Init.Mode                = DMA_PFCTRL;
    sdio_obj.dma.handle_tx.Init.Priority            = DMA_PRIORITY_MEDIUM;
    sdio_obj.dma.handle_tx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
    sdio_obj.dma.handle_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    sdio_obj.dma.handle_tx.Init.MemBurst            = DMA_MBURST_INC4;
    sdio_obj.dma.handle_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
    /* DMA_PFCTRL */
    HAL_DMA_DeInit(&sdio_obj.dma.handle_tx);
    HAL_DMA_Init(&sdio_obj.dma.handle_tx);

    HAL_DMA_Start(&sdio_obj.dma.handle_tx, (uint32_t)src, (uint32_t)dst, BufferSize);
#endif
}

/**
  * @brief  This function configures the DMARX.
  * @param  BufferDST: pointer to the destination buffer
  * @param  BufferSize: buffer size
  * @retval None
  */
void SD_LowLevel_DMA_RxConfig(uint32_t *src, uint32_t *dst, uint32_t BufferSize)
{
#if defined(SOC_SERIES_STM32F1)
    sdio_obj.cfg = &sdio_config;
    sdio_obj.dma.handle_rx.Instance = sdio_config.dma_tx.Instance;
    sdio_obj.dma.handle_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    sdio_obj.dma.handle_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    sdio_obj.dma.handle_rx.Init.MemInc              = DMA_MINC_ENABLE;
    sdio_obj.dma.handle_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    sdio_obj.dma.handle_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
    sdio_obj.dma.handle_rx.Init.Priority            = DMA_PRIORITY_MEDIUM;

    HAL_DMA_DeInit(&sdio_obj.dma.handle_rx);
    HAL_DMA_Init(&sdio_obj.dma.handle_rx);

    HAL_DMA_Start(&sdio_obj.dma.handle_rx, (uint32_t)src, (uint32_t)dst, BufferSize);
#elif defined(SOC_SERIES_STM32L4)
    sdio_obj.cfg = &sdio_config;
    sdio_obj.dma.handle_rx.Instance = sdio_config.dma_tx.Instance;
    sdio_obj.dma.handle_rx.Init.Request             = sdio_config.dma_tx.request;
    sdio_obj.dma.handle_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    sdio_obj.dma.handle_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
    sdio_obj.dma.handle_rx.Init.MemInc              = DMA_MINC_ENABLE;
    sdio_obj.dma.handle_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    sdio_obj.dma.handle_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    sdio_obj.dma.handle_rx.Init.Mode                = DMA_NORMAL;
    sdio_obj.dma.handle_rx.Init.Priority            = DMA_PRIORITY_LOW;

    HAL_DMA_DeInit(&sdio_obj.dma.handle_rx);
    HAL_DMA_Init(&sdio_obj.dma.handle_rx);

    HAL_DMA_Start(&sdio_obj.dma.handle_rx, (uint32_t)src, (uint32_t)dst, BufferSize);
#else
    sdio_obj.cfg = &sdio_config;
    sdio_obj.dma.handle_rx.Instance = sdio_config.dma_tx.Instance;
    sdio_obj.dma.handle_rx.Init.Channel = sdio_config.dma_tx.channel;
    sdio_obj.dma.handle_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    sdio_obj.dma.handle_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
    sdio_obj.dma.handle_rx.Init.MemInc              = DMA_MINC_ENABLE;
    sdio_obj.dma.handle_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    sdio_obj.dma.handle_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    sdio_obj.dma.handle_rx.Init.Mode                = DMA_PFCTRL;
    sdio_obj.dma.handle_rx.Init.Priority            = DMA_PRIORITY_MEDIUM;
    sdio_obj.dma.handle_rx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
    sdio_obj.dma.handle_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    sdio_obj.dma.handle_rx.Init.MemBurst            = DMA_MBURST_INC4;
    sdio_obj.dma.handle_rx.Init.PeriphBurst         = DMA_PBURST_INC4;

    HAL_DMA_DeInit(&sdio_obj.dma.handle_rx);
    HAL_DMA_Init(&sdio_obj.dma.handle_rx);

    HAL_DMA_Start(&sdio_obj.dma.handle_rx, (uint32_t)src, (uint32_t)dst, BufferSize);
#endif

}

/**
  * @brief  This function get stm32 sdio clock.
  * @param  hw_sdio: stm32_sdio
  * @retval PCLK2Freq
  */
static rt_uint32_t stm32_sdio_clock_get(struct stm32_sdio *hw_sdio)
{
    return HAL_RCC_GetPCLK2Freq();
}

static rt_err_t DMA_TxConfig(rt_uint32_t *src, rt_uint32_t *dst, int Size)
{
    SD_LowLevel_DMA_TxConfig((uint32_t *)src, (uint32_t *)dst, Size / 4);
    return RT_EOK;
}

static rt_err_t DMA_RxConfig(rt_uint32_t *src, rt_uint32_t *dst, int Size)
{
    SD_LowLevel_DMA_RxConfig((uint32_t *)src, (uint32_t *)dst, Size / 4);
    return RT_EOK;
}

void SDIO_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    /* Process All SDIO Interrupt Sources */
    rthw_sdio_irq_process(host);

    /* leave interrupt */
    rt_interrupt_leave();
}

int rt_hw_sdio_init(void)
{
    struct stm32_sdio_des sdio_des;
    SD_HandleTypeDef hsd;
    hsd.Instance = SDCARD_INSTANCE;
    {
        rt_uint32_t tmpreg = 0x00U;
#if defined(SOC_SERIES_STM32F1)
        /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
        SET_BIT(RCC->AHBENR, sdio_config.dma_rx.dma_rcc);
        tmpreg = READ_BIT(RCC->AHBENR, sdio_config.dma_rx.dma_rcc);
#elif defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F2)
        SET_BIT(RCC->AHB1ENR, sdio_config.dma_rx.dma_rcc);
        /* Delay after an RCC peripheral clock enabling */
        tmpreg = READ_BIT(RCC->AHB1ENR, sdio_config.dma_rx.dma_rcc);
#endif
        UNUSED(tmpreg); /* To avoid compiler warnings */
    }
    HAL_NVIC_SetPriority(SDIO_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(SDIO_IRQn);
    HAL_SD_MspInit(&hsd);

    sdio_des.clk_get = stm32_sdio_clock_get;
    sdio_des.hw_sdio = (struct stm32_sdio *)SDCARD_INSTANCE;
    sdio_des.rxconfig = DMA_RxConfig;
    sdio_des.txconfig = DMA_TxConfig;

    host = sdio_host_create(&sdio_des);
    if (host == RT_NULL)
    {
        LOG_E("host create fail");
        return -1;
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

void stm32_mmcsd_change(void)
{
    mmcsd_change(host);
}

#endif
