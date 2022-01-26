/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-23     liuduanfei   first version
 */

#include "board.h"
#include "drv_sdio.h"
#include <dfs_fs.h>

#ifdef BSP_USING_SDMMC

#define DBG_TAG              "drv.sdio"
#ifdef DRV_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

static struct rt_mmcsd_host *host;
#define SDIO_TX_RX_COMPLETE_TIMEOUT_LOOPS    (100000)

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
    struct sdio_pkg *pkg;
};

ALIGN(SDIO_ALIGN_LEN)
static rt_uint8_t cache_buf[SDIO_BUFF_SIZE];

/**
  * @brief  This function get order from sdio.
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
  * @brief  This function wait sdio cmd completed.
  * @param  sdio rthw_sdio
  * @retval None
  */
static void rthw_sdio_wait_completed(struct rthw_sdio *sdio)
{
    rt_uint32_t status;
    struct rt_mmcsd_cmd *cmd = sdio->pkg->cmd;
    struct stm32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;

    if (rt_event_recv(&sdio->event, 0xffffffff, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      rt_tick_from_millisecond(5000), &status) != RT_EOK)
    {
        LOG_E("wait cmd completed timeout");
        cmd->err = -RT_ETIMEOUT;
        return;
    }

    cmd->resp[0] = hw_sdio->resp1;
    if (resp_type(cmd) == RESP_R2)
    {
        cmd->resp[1] = hw_sdio->resp2;
        cmd->resp[2] = hw_sdio->resp3;
        cmd->resp[3] = hw_sdio->resp4;
    }

    if (status & SDIO_ERRORS)
    {
        if ((status & SDMMC_STA_CCRCFAIL) && (resp_type(cmd) & (RESP_R3 | RESP_R4)))
        {
            cmd->err = RT_EOK;
        }
        else
        {
            cmd->err = -RT_ERROR;
        }
    }

    if (cmd->err == RT_EOK)
    {
        LOG_D("sta:0x%08X [%08X %08X %08X %08X]", status, cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
    }
    else
    {
        LOG_D("send command error = %d", cmd->err);
    }
}

/**
  * @brief  This function send command.
  * @param  sdio rthw_sdio
  * @param  pkg  sdio package
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

    LOG_D("CMD:%d ARG:0x%08x RES:%s%s%s%s%s%s%s%s%s rw:%c len:%d blksize:%d\n",
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

    hw_sdio->mask |= SDIO_MASKR_ALL;
    reg_cmd = cmd->cmd_code | SDMMC_CMD_CPSMEN;

    /* data pre configuration */
    if (data != RT_NULL)
    {
        SCB_CleanInvalidateDCache();

        reg_cmd |= SDMMC_CMD_CMDTRANS;
        hw_sdio->mask &= ~(SDMMC_MASK_CMDRENDIE | SDMMC_MASK_CMDSENTIE);
        hw_sdio->dtimer = HW_SDIO_DATATIMEOUT;
        hw_sdio->dlen = data->blks * data->blksize;
        hw_sdio->dctrl = (get_order(data->blksize)<<4) | (data->flags & DATA_DIR_READ ? SDMMC_DCTRL_DTDIR : 0);
        hw_sdio->idmabase0r = (rt_uint32_t)cache_buf;
        hw_sdio->idmatrlr = SDMMC_IDMA_IDMAEN;
    }

    if (resp_type(cmd) == RESP_R2)
        reg_cmd |= SDMMC_CMD_WAITRESP;
    else if(resp_type(cmd) != RESP_NONE)
        reg_cmd |= SDMMC_CMD_WAITRESP_0;

    hw_sdio->arg = cmd->arg;
    hw_sdio->cmd = reg_cmd;
    /* wait completed */
    rthw_sdio_wait_completed(sdio);

    /* Waiting for data to be sent to completion */
    if (data != RT_NULL)
    {
        volatile rt_uint32_t count = SDIO_TX_RX_COMPLETE_TIMEOUT_LOOPS;

        while (count && (hw_sdio->sta & SDMMC_STA_DPSMACT))
        {
            count--;
        }
        if ((count == 0) || (hw_sdio->sta & SDIO_ERRORS))
        {
            cmd->err = -RT_ERROR;
        }
    }

    /* data post configuration */
    if (data != RT_NULL)
    {
        if (data->flags & DATA_DIR_READ)
        {
            rt_memcpy(data->buf, cache_buf, data->blks * data->blksize);
            SCB_CleanInvalidateDCache();
        }
    }
}

/**
  * @brief  This function send sdio request.
  * @param  sdio  rthw_sdio
  * @param  req   request
  * @retval None
  */
static void rthw_sdio_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct sdio_pkg pkg;
    struct rthw_sdio *sdio = host->private_data;
    struct rt_mmcsd_data *data;

    if (req->cmd != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
        data = req->cmd->data;
        pkg.cmd = req->cmd;

        if (data != RT_NULL)
        {
            rt_uint32_t size = data->blks * data->blksize;

            RT_ASSERT(size <= SDIO_BUFF_SIZE);

            if (data->flags & DATA_DIR_WRITE)
            {
                rt_memcpy(cache_buf, data->buf, size);
            }
        }

        rthw_sdio_send_command(sdio, &pkg);
    }

    if (req->stop != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
        pkg.cmd = req->stop;
        rthw_sdio_send_command(sdio, &pkg);
    }

    mmcsd_req_complete(sdio->host);
}


/**
  * @brief  This function interrupt process function.
  * @param  host  rt_mmcsd_host
  * @retval None
  */
void rthw_sdio_irq_process(struct rt_mmcsd_host *host)
{
    struct rthw_sdio *sdio = host->private_data;
    struct stm32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;
    rt_uint32_t intstatus = hw_sdio->sta;

    /* clear irq flag*/
    hw_sdio->icr = intstatus;

    rt_event_send(&sdio->event, intstatus);
}

/**
  * @brief  This function config sdio.
  * @param  host    rt_mmcsd_host
  * @param  io_cfg  rt_mmcsd_io_cfg
  * @retval None
  */
static void rthw_sdio_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_uint32_t temp, clk_src;
    rt_uint32_t clk = io_cfg->clock;
    struct rthw_sdio *sdio = host->private_data;
    struct stm32_sdio *hw_sdio = sdio->sdio_des.hw_sdio;

    LOG_D("clk:%dK width:%s%s%s power:%s%s%s",
          clk/1000,
          io_cfg->bus_width == MMCSD_BUS_WIDTH_8 ? "8" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_4 ? "4" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_1 ? "1" : "",
          io_cfg->power_mode == MMCSD_POWER_OFF ? "OFF" : "",
          io_cfg->power_mode == MMCSD_POWER_UP ? "UP" : "",
          io_cfg->power_mode == MMCSD_POWER_ON ? "ON" : ""
         );

    clk_src = SDIO_CLOCK_FREQ;

    if (clk > 0)
    {
        if (clk > host->freq_max)
            clk = host->freq_max;
        temp = DIV_ROUND_UP(clk_src, 2 * clk);
        if (temp > 0x3FF)
         temp = 0x3FF;
    }

    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
        temp |= SDMMC_CLKCR_WIDBUS_0;
    else if (io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
        temp |= SDMMC_CLKCR_WIDBUS_1;

    hw_sdio->clkcr = temp;

    if (io_cfg->power_mode == MMCSD_POWER_ON)
        hw_sdio->power |= SDMMC_POWER_PWRCTRL;
}

static const struct rt_mmcsd_host_ops ops =
{
    rthw_sdio_request,
    rthw_sdio_iocfg,
    RT_NULL,
    RT_NULL,
};

/**
  * @brief  This function create mmcsd host.
  * @param  sdio_des stm32_sdio_des
  * @retval rt_mmcsd_host
  */
struct rt_mmcsd_host *sdio_host_create(struct stm32_sdio_des *sdio_des)
{
    struct rt_mmcsd_host *host;
    struct rthw_sdio *sdio = RT_NULL;

    if (sdio_des == RT_NULL)
    {
        return RT_NULL;
    }

    sdio = rt_malloc(sizeof(struct rthw_sdio));
    if (sdio == RT_NULL)
    {
        LOG_E("malloc rthw_sdio fail");
        return RT_NULL;
    }
    rt_memset(sdio, 0, sizeof(struct rthw_sdio));

    host = mmcsd_alloc_host();
    if (host == RT_NULL)
    {
        LOG_E("alloc host fail");
        goto err;
    }

    rt_memcpy(&sdio->sdio_des, sdio_des, sizeof(struct stm32_sdio_des));

    sdio->sdio_des.hw_sdio = (struct stm32_sdio *)SDIO_BASE_ADDRESS;

    rt_event_init(&sdio->event, "sdio", RT_IPC_FLAG_FIFO);

    /* set host default attributes */
    host->ops = &ops;
    host->freq_min = 400 * 1000;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = VDD_32_33 | VDD_33_34;/* The voltage range supported is 3.2v-3.4v */
#ifndef SDIO_USING_1_BIT
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED;
#else
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED;
#endif

    host->max_seg_size = SDIO_BUFF_SIZE;
    host->max_dma_segs = 1;
    host->max_blk_size = 512;
    host->max_blk_count = 512;

    /* link up host and sdio */
    sdio->host = host;
    host->private_data = sdio;

    /* ready to change */
    mmcsd_change(host);

    return host;

err:
    if (sdio) rt_free(sdio);

    return RT_NULL;
}

void SDMMC1_IRQHandler(void)
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
    hsd.Instance = SDMMC1;
    HAL_SD_MspInit(&hsd);

    host = sdio_host_create(&sdio_des);
    if (host == RT_NULL)
    {
        LOG_E("host create fail");
        return RT_NULL;
    }
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

int mnt_init(void)
{
    rt_thread_delay(RT_TICK_PER_SECOND);

    if (dfs_mount("sd0", "/", "elm", 0, 0) != 0)
    {
        rt_kprintf("file system mount failed!\n");
    }
    else
    {
        rt_kprintf("file system mount success!\n");
    }

    return 0;
}
INIT_ENV_EXPORT(mnt_init);

#endif /* BSP_USING_SDMMC */
