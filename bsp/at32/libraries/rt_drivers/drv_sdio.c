/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include "drv_common.h"
#include "drv_sdio.h"

#ifdef BSP_USING_SDIO
#if !defined (BSP_USING_SDIO1)
#error "Please define at least one SDIOx"
#endif

//#define DRV_DEBUG
#define LOG_TAG             "drv.sdio"
#include <drv_log.h>

static struct at32_sdio_config sdio_config = SDIO_BUS_CONFIG;
static struct at32_sdio_class sdio_obj;
static struct rt_mmcsd_host *host;

#define SDIO_TX_RX_COMPLETE_TIMEOUT_LOOPS    (100000)

#define RT_HW_SDIO_LOCK(_sdio) rt_mutex_take(&_sdio->mutex, RT_WAITING_FOREVER)
#define RT_HW_SDIO_UNLOCK(_sdio) rt_mutex_release(&_sdio->mutex);

struct sdio_pkg
{
    struct rt_mmcsd_cmd *cmd;
    void *buff;
    rt_uint32_t flag;
};

struct rt_hw_sdio
{
    struct rt_mmcsd_host *host;
    struct at32_sdio_des sdio_des;
    struct rt_event event;
    struct rt_mutex mutex;
    struct sdio_pkg *pkg;
};

rt_align(SDIO_ALIGN_LEN)
static rt_uint8_t cache_buf[SDIO_BUFF_SIZE];

static rt_uint32_t at32_sdio_clk_get(struct at32_sdio *hw_sdio)
{
    return SDIO_CLOCK_FREQ;
}

/**
  * @brief  this function get order from sdio.
  * @param  data
  * @retval sdio order
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
  * @brief  this function wait sdio completed.
  * @param  sdio rt_hw_sdio
  * @retval none
  */
static void rt_hw_sdio_wait_completed(struct rt_hw_sdio *sdio)
{
    rt_uint32_t status;
    struct rt_mmcsd_cmd *cmd = sdio->pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    struct at32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;

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
  * @brief  this function transfer data by dma.
  * @param  sdio rt_hw_sdio
  * @param  pkg sdio package
  * @retval none
  */
static void rt_hw_sdio_transfer_by_dma(struct rt_hw_sdio *sdio, struct sdio_pkg *pkg)
{
    struct rt_mmcsd_data *data;
    int size;
    void *buff;
    struct at32_sdio *hw_sdio;

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
  * @brief  this function send command.
  * @param  sdio rt_hw_sdio
  * @param  pkg sdio package
  * @retval none
  */
static void rt_hw_sdio_send_command(struct rt_hw_sdio *sdio, struct sdio_pkg *pkg)
{
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    struct at32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;
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
        hw_sdio->dctrl = /* HW_SDIO_IO_ENABLE | */ (order << 4) | dir;
    }

    /* transfer config */
    if (data != RT_NULL)
    {
        rt_hw_sdio_transfer_by_dma(sdio, pkg);
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
    rt_hw_sdio_wait_completed(sdio);

    /* waiting for data to be sent to completion */
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
    rt_uint32_t clkcr, div, clk_src;
    rt_uint32_t clk = io_cfg->clock;
    struct rt_hw_sdio *sdio = host->private_data;
    struct at32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;

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

    RT_HW_SDIO_LOCK(sdio);

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
        else if (div > 0x3FF)
        {
            div = 0x3FF;
        }
        div -= 2;
        clkcr = (div & 0xFF) | ((div & 0x300) << 7) | HW_SDIO_CLK_ENABLE;
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
    struct rt_hw_sdio *sdio = host->private_data;
    struct at32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;

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
    int complete = 0;
    struct rt_hw_sdio *sdio = host->private_data;
    struct at32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;
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
    rt_hw_sdio_request,
    rt_hw_sdio_iocfg,
    rt_hw_sd_delect,
    rt_hw_sdio_irq_update,
};

/**
  * @brief  this function create mmcsd host.
  * @param  sdio_des at32_sdio_des
  * @retval rt_mmcsd_host
  */
struct rt_mmcsd_host *sdio_host_create(struct at32_sdio_des *sdio_des)
{
    struct rt_mmcsd_host *host;
    struct rt_hw_sdio *sdio = RT_NULL;

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

    rt_memcpy(&sdio->sdio_des, sdio_des, sizeof(struct at32_sdio_des));
    sdio->sdio_des.hw_sdio = (sdio_des->hw_sdio == RT_NULL ? (struct at32_sdio *)SDIO_BASE_ADDRESS : sdio_des->hw_sdio);
    sdio->sdio_des.clk_get = (sdio_des->clk_get == RT_NULL ? at32_sdio_clk_get : sdio_des->clk_get);

    rt_event_init(&sdio->event, "sdio", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&sdio->mutex, "sdio", RT_IPC_FLAG_PRIO);

    /* set host defautl attributes */
    host->ops = &ops;
    host->freq_min = 400 * 1000;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = 0X00FFFF80;/* the voltage range supported is 1.65v-3.6v */
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
    static uint32_t size = 0;
    dma_init_type dma_init_struct;

    size += buffer_size * 4;
    sdio_obj.cfg = &sdio_config;

    dma_default_para_init(&dma_init_struct);
    sdio_obj.dma.handle_tx = sdio_config.dma_tx.dma_channel;
    dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
    dma_init_struct.buffer_size = buffer_size;
    dma_init_struct.memory_base_addr = (uint32_t)src;
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_WORD;
    dma_init_struct.memory_inc_enable = TRUE;
    dma_init_struct.peripheral_base_addr = (uint32_t)dst;
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_WORD;
    dma_init_struct.peripheral_inc_enable = FALSE;
    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;

    nvic_irq_enable(sdio_config.dma_tx.dma_irq, 2, 0);

    dma_init(sdio_obj.dma.handle_tx, &dma_init_struct);
    dma_interrupt_enable(sdio_obj.dma.handle_tx, DMA_FDT_INT, TRUE);

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437)
    dmamux_init(sdio_config.dma_tx.dmamux_channel, sdio_config.dma_tx.dmamux_id);
    dmamux_enable(sdio_config.dma_tx.dma_x, TRUE);
#endif

    dma_channel_enable(sdio_obj.dma.handle_tx, TRUE);
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
    sdio_obj.cfg = &sdio_config;
    dma_init_type dma_init_struct;

    dma_default_para_init(&dma_init_struct);
    sdio_obj.dma.handle_rx = sdio_config.dma_rx.dma_channel;
    dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
    dma_init_struct.buffer_size = buffer_size;
    dma_init_struct.memory_base_addr = (uint32_t)dst;
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_WORD;
    dma_init_struct.memory_inc_enable = TRUE;
    dma_init_struct.peripheral_base_addr = (uint32_t)src;
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_WORD;
    dma_init_struct.peripheral_inc_enable = FALSE;
    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;

    nvic_irq_enable(sdio_config.dma_rx.dma_irq, 2, 0);

    dma_init(sdio_obj.dma.handle_rx, &dma_init_struct);
    dma_interrupt_enable(sdio_obj.dma.handle_rx, DMA_FDT_INT, TRUE);

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437)
    dmamux_init(sdio_config.dma_rx.dmamux_channel, sdio_config.dma_rx.dmamux_id);
    dmamux_enable(sdio_config.dma_rx.dma_x, TRUE);
#endif

    dma_channel_enable(sdio_obj.dma.handle_rx, TRUE);
}

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437)
void DMA2_Channel4_IRQHandler(void)
#else
void DMA2_Channel4_5_IRQHandler(void)
#endif
{
    if(dma_flag_get(DMA2_FDT4_FLAG))
    {
        dma_flag_clear(DMA2_FDT4_FLAG);
        dma_channel_enable(sdio_config.dma_rx.dma_channel, FALSE);
    }
}

/**
  * @brief  this function get at32 sdio clock.
  * @param  hw_sdio: at32_sdio
  * @retval ahb frequency
  */
static rt_uint32_t at32_sdio_clock_get(struct at32_sdio *hw_sdio)
{
    crm_clocks_freq_type clocks;

    crm_clocks_freq_get(&clocks);
    return clocks.ahb_freq;
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

void SDIO1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_sdio_irq_process(host);

    /* leave interrupt */
    rt_interrupt_leave();
}

int rt_hw_sdio_init(void)
{
    struct at32_sdio_des sdio_des;
    struct at32_sdio_config hsd;

    hsd.sdio_x = SDCARD_INSTANCE;
    at32_msp_sdio_init((void *)(hsd.sdio_x));

    nvic_irq_enable(SDIO1_IRQn, 2, 0);

    sdio_des.clk_get = at32_sdio_clock_get;
    sdio_des.hw_sdio = (struct at32_sdio *)SDCARD_INSTANCE;
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

void at32_mmcsd_change(void)
{
    mmcsd_change(host);
}

#endif
