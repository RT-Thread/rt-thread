/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-30     greedyhao         first version
 */

#include "drv_sdio.h"
#include "interrupt.h"
#include <rthw.h>

#ifdef BSP_USING_SDIO

// #define DRV_DEBUG
#define LOG_TAG             "drv.sdio"
#include <drv_log.h>

#define SDIO_USING_1_BIT

static struct ab32_sdio_config sdio_config[] =
{
    {.instance = SDMMC0_BASE,
    },
};
static struct rt_mmcsd_host *host = RT_NULL;

#define RTHW_SDIO_LOCK(_sdio)   rt_mutex_take(&(_sdio)->mutex, RT_WAITING_FOREVER)
#define RTHW_SDIO_UNLOCK(_sdio) rt_mutex_release(&(_sdio)->mutex);

struct sdio_pkg
{
    struct rt_mmcsd_cmd *cmd;
    void *buff;
    rt_uint32_t flag;
    rt_uint32_t xfer_blks;
};

struct rthw_sdio
{
    struct rt_mmcsd_host *host;
    struct ab32_sdio_des sdio_des;
    struct rt_event event;
    struct rt_mutex mutex;
    struct sdio_pkg *pkg;
};

ALIGN(SDIO_ALIGN_LEN)
static rt_uint8_t cache_buf[SDIO_BUFF_SIZE];

static uint8_t sd_baud = 119;

uint8_t sysclk_update_baud(uint8_t baud);

static rt_uint32_t ab32_sdio_clk_get(hal_sfr_t hw_sdio)
{
    return (get_sysclk_nhz() / (sd_baud+1));
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
    rt_uint32_t status = 0;
    struct rt_mmcsd_cmd *cmd = sdio->pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    hal_sfr_t hw_sdio = sdio->sdio_des.hw_sdio;
    rt_err_t tx_finish = -RT_ERROR;

    if (rt_event_recv(&sdio->event, 0xFFFFFFFF & ~HW_SDIO_CON_DFLAG, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
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

    cmd->resp[0] = hw_sdio[SDxARG3];
    cmd->resp[1] = hw_sdio[SDxARG2];
    cmd->resp[2] = hw_sdio[SDxARG1];
    cmd->resp[3] = hw_sdio[SDxARG0];

    if (!(status & HW_SDIO_CON_NRPS)) {
        cmd->err = RT_EOK;
        LOG_D("sta:0x%08X [%08X %08X %08X %08X]", status, cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
    } else {
        cmd->err = -RT_ERROR;
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
    hal_sfr_t hw_sdio = sdio->sdio_des.hw_sdio;

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
        LOG_D("DATA_DIR_WRITE %d", pkg->xfer_blks);
        sdio->sdio_des.txconfig((rt_uint32_t *)((rt_uint8_t *)buff + (pkg->xfer_blks * data->blksize)), 512);
    }
    else if (data->flags & DATA_DIR_READ)
    {
        LOG_D("DATA_DIR_WRITE %d", pkg->xfer_blks);
        sdio->sdio_des.rxconfig((rt_uint32_t *)((rt_uint8_t *)buff + (pkg->xfer_blks * data->blksize)), data->blksize);
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
    hal_sfr_t hw_sdio = sdio->sdio_des.hw_sdio;
    rt_uint32_t reg_cmd = 0;
    rt_uint32_t data_flag = 0;

    /* save pkg */
    sdio->pkg = pkg;

    #define CK8E            BIT(11)             //在命令/数据包后加上8CLK
    #define CBUSY           BIT(10)             //Busy Check
    #define CLRSP           BIT(9)              //17Byte Long Rsp
    #define CRSP            BIT(8)              //Need Rsp

    /* config cmd reg */
    if (cmd->cmd_code != 18) {
        reg_cmd = cmd->cmd_code | 0x40 | CK8E;
    } else {
        reg_cmd = cmd->cmd_code | 0x40;
    }

    switch (resp_type(cmd))
    {
    case RESP_R1B:
        reg_cmd |= CBUSY | CRSP;
        break;
    case RESP_R2:
        reg_cmd |= CLRSP | CRSP;
        break;
    default:
        reg_cmd |= CRSP;
        break;
    }

    LOG_D("CMD:%d 0x%04X ARG:0x%08x RES:%s%s%s%s%s%s%s%s%s rw:%c len:%d blksize:%d",
          cmd->cmd_code,
          reg_cmd,
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

    /* config data reg */
    if (data != RT_NULL)
    {
        rt_uint32_t dir = 0;
        rt_uint32_t size = data->blks * data->blksize;
        int order;

        order = get_order(data->blksize);
        dir = (data->flags & DATA_DIR_READ) ? HW_SDIO_TO_HOST : 0;

        data_flag = data->flags;
    }

    /* transfer config */
    if (data_flag & DATA_DIR_READ)
    {
        rthw_sdio_transfer_by_dma(sdio, pkg);
    }

    /* send cmd */
    hw_sdio[SDxARG3] = cmd->arg;
    hw_sdio[SDxCMD]  = reg_cmd;

    /* wait cmd completed */
    rthw_sdio_wait_completed(sdio);

    /* transfer config */
    if (data != RT_NULL)
    {
        do {
            if ((data_flag & DATA_DIR_WRITE) || ((data_flag & DATA_DIR_READ) && (pkg->xfer_blks != 0))) {
                rthw_sdio_transfer_by_dma(sdio, pkg);
            }

            rt_uint32_t status = 0;

            if (rt_event_recv(&sdio->event, 0xFFFFFFFF & ~HW_SDIO_CON_DFLAG, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            rt_tick_from_millisecond(5000), &status) != RT_EOK)
            {
                LOG_E("wait completed timeout");
                LOG_E("SDxCON=0x%X SDxCMD=0x%X\n", hw_sdio[SDxCON], hw_sdio[SDxCMD]);
                cmd->err = -RT_ETIMEOUT;
            }

            if (data_flag & DATA_DIR_WRITE) {
                if (((hw_sdio[SDxCON] & HW_SDIO_CON_CRCS) >> 17) != 2) {
                    LOG_E("Write CRC error!");
                    cmd->err = -RT_ERROR;
                    hw_sdio[SDxCPND] = HW_SDIO_CON_DFLAG;
                }
            }
        } while(++pkg->xfer_blks != data->blks);
    }

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
    hal_sfr_t hw_sdio = sdio->sdio_des.hw_sdio;

    clk_src = sdio->sdio_des.clk_get(sdio->sdio_des.hw_sdio);
    if (clk_src < 240 * 1000)
    {
        LOG_E("The clock rate is too low! rata:%d", clk_src);
        return;
    }

    if (clk > host->freq_max) clk = host->freq_max;

    if (clk > clk_src)
    {
        // LOG_W("Setting rate(%d) is greater than clock source rate(%d).", clk, clk_src);
        // clk = clk_src;
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

    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_OFF:
        hw_sdio[SDxCON] &= ~BIT(0);
        break;
    case MMCSD_POWER_UP:
        sd_baud = 199;
        hw_sdio[SDxCON] = 0;
        rt_thread_mdelay(1);

        hw_sdio[SDxCON] |= BIT(0);                 /* SD control enable */
        hw_sdio[SDxBAUD] = sysclk_update_baud(sd_baud);
        hw_sdio[SDxCON] |= BIT(3);                 /* Keep clock output */
        hw_sdio[SDxCON] |= BIT(4);
        hw_sdio[SDxCON] |= BIT(5);                 /* Data interrupt enable */

        hal_mdelay(40);
        break;
    case MMCSD_POWER_ON:
        if (clk == SDIO_MAX_FREQ) {
            hw_sdio[SDxCON] &= ~BIT(3);
            sd_baud = 3;
            hw_sdio[SDxBAUD] = sysclk_update_baud(sd_baud);
        }
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
    hal_sfr_t hw_sdio = sdio->sdio_des.hw_sdio;

    if (enable)
    {
        LOG_D("enable sdio irq");
        rt_hw_irq_enable(IRQ_SD_VECTOR);
    }
    else
    {
        LOG_D("disable sdio irq");
        rt_hw_irq_disable(IRQ_SD_VECTOR);
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
    hal_sfr_t hw_sdio = sdio->sdio_des.hw_sdio;
    rt_uint32_t intstatus = hw_sdio[SDxCON];

    /* clear flag */
    if (intstatus & HW_SDIO_CON_CFLAG) {
        complete = 1;
        hw_sdio[SDxCPND] = HW_SDIO_CON_CFLAG;
    }

    if (intstatus & HW_SDIO_CON_DFLAG) {
        complete = 1;
        hw_sdio[SDxCPND] = HW_SDIO_CON_DFLAG;
    }

    if (complete)
    {
        rt_event_send(&sdio->event, intstatus);
    }
}

static const struct rt_mmcsd_host_ops ab32_sdio_ops =
{
    rthw_sdio_request,
    rthw_sdio_iocfg,
    rthw_sd_detect,
    rthw_sdio_irq_update,
};

/**
  * @brief  This function create mmcsd host.
  * @param  sdio_des  ab32_sdio_des
  * @retval rt_mmcsd_host
  */
struct rt_mmcsd_host *sdio_host_create(struct ab32_sdio_des *sdio_des)
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

    rt_memcpy(&sdio->sdio_des, sdio_des, sizeof(struct ab32_sdio_des));
    sdio->sdio_des.hw_sdio = (sdio_des->hw_sdio == RT_NULL ? SDMMC0_BASE : sdio_des->hw_sdio);
    sdio->sdio_des.clk_get = (sdio_des->clk_get == RT_NULL ? ab32_sdio_clk_get : sdio_des->clk_get);

    rt_event_init(&sdio->event, "sdio", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&sdio->mutex, "sdio", RT_IPC_FLAG_FIFO);

    /* set host defautl attributes */
    host->ops = &ab32_sdio_ops;
    host->freq_min = 240 * 1000;
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

static rt_err_t _dma_txconfig(rt_uint32_t *src, int Size)
{
    hal_sfr_t sdiox = sdio_config->instance;

    sdiox[SDxDMAADR] = DMA_ADR(src);
    sdiox[SDxDMACNT] = BIT(18) | BIT(17) | BIT(16) | Size;
    return RT_EOK;
}

static rt_err_t _dma_rxconfig(rt_uint32_t *dst, int Size)
{
    hal_sfr_t sdiox = sdio_config->instance;

    sdiox[SDxDMAADR] = DMA_ADR(dst);
    sdiox[SDxDMACNT] = (Size);
    return RT_EOK;
}

void sdio_isr(int vector, void *param)
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
    struct ab32_sdio_des sdio_des = {0};
    struct sd_handle hsd = {0};
    uint8_t param = 0;
    hsd.instance = SDMMC0_BASE;

    hal_rcu_periph_clk_enable(RCU_SD0);
    hal_sd_mspinit(&hsd);

    rt_hw_interrupt_install(IRQ_SD_VECTOR, sdio_isr, &param, "sd_isr");

    sdio_des.clk_get    = ab32_sdio_clk_get;
    sdio_des.hw_sdio    = SDMMC0_BASE;
    sdio_des.rxconfig   = _dma_rxconfig;
    sdio_des.txconfig   = _dma_txconfig;

    host = sdio_host_create(&sdio_des);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

void ab32_mmcsd_change(void)
{
    mmcsd_change(host);
}

#endif // 0
