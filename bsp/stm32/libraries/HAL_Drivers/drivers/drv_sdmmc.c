/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-23     liuduanfei   first version
 * 2020-08-25     wanghaijing  add sdmmmc2
 * 2023-03-26     wdfk-prog    Distinguish between SDMMC and SDIO drivers
 */
#include "board.h"

#ifdef RT_USING_SDIO

#if !defined(BSP_USING_SDIO1) && !defined(BSP_USING_SDIO2)
    #error "Please define at least one BSP_USING_SDIOx"
#endif

#include "drv_sdmmc.h"

#define DBG_TAG              "drv.sdmmc"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

static struct stm32_sdio_class sdio_obj;
static struct rt_mmcsd_host *host1;
static struct rt_mmcsd_host *host2;

#define SDIO_TX_RX_COMPLETE_TIMEOUT_LOOPS    (1000000)

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

rt_align(SDIO_ALIGN_LEN)
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
    struct rt_mmcsd_data *data = cmd->data;
    SD_TypeDef *hsd = sdio->sdio_des.hw_sdio.Instance;

    if (rt_event_recv(&sdio->event, 0xffffffff, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      rt_tick_from_millisecond(5000), &status) != RT_EOK)
    {
        LOG_E("wait cmd completed timeout");
        cmd->err = -RT_ETIMEOUT;
        return;
    }

    if (sdio->pkg == RT_NULL)
    {
        return;
    }
    /* Get Card Specific Data */
    cmd->resp[0] = hsd->RESP1;
    if (resp_type(cmd) == RESP_R2)
    {
        cmd->resp[1] = hsd->RESP2;
        cmd->resp[2] = hsd->RESP3;
        cmd->resp[3] = hsd->RESP4;
    }
     /* Check for error conditions */
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
    else
    {
        cmd->err = RT_EOK;
    }

    if (status & SDMMC_IT_CTIMEOUT)
    {
        cmd->err = -RT_ETIMEOUT;
    }
    if (status & SDMMC_IT_DCRCFAIL)
    {
        data->err = -RT_ERROR;
    }

    if (status & SDMMC_IT_DTIMEOUT)
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
    SD_TypeDef *hsd = sdio->sdio_des.hw_sdio.Instance;
    rt_uint32_t reg_cmd;

    rt_event_control(&sdio->event, RT_IPC_CMD_RESET, RT_NULL);
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

    /* open irq */
    __HAL_SD_ENABLE_IT(&sdio->sdio_des.hw_sdio, SDIO_MASKR_ALL);
    reg_cmd = cmd->cmd_code | SDMMC_CMD_CPSMEN;

    /* data pre configuration */
    if (data != RT_NULL)
    {
        SCB_CleanInvalidateDCache();

        reg_cmd |= SDMMC_CMD_CMDTRANS;
        __HAL_SD_DISABLE_IT(&sdio->sdio_des.hw_sdio, SDMMC_MASK_CMDRENDIE | SDMMC_MASK_CMDSENTIE);
        hsd->DTIMER = HW_SDIO_DATATIMEOUT;
        hsd->DLEN = data->blks * data->blksize;
        hsd->DCTRL = (get_order(data->blksize) << 4) | (data->flags & DATA_DIR_READ ? SDMMC_DCTRL_DTDIR : 0);
        hsd->IDMABASE0 = (rt_uint32_t)cache_buf;
        hsd->IDMACTRL = SDMMC_IDMA_IDMAEN;
    }
     /* config cmd reg */
   if (resp_type(cmd) == RESP_NONE)
       reg_cmd |= SDMMC_RESPONSE_NO;
   else if (resp_type(cmd) == RESP_R2)
       reg_cmd |= SDMMC_RESPONSE_LONG;
   else
       reg_cmd |= SDMMC_RESPONSE_SHORT;

    hsd->ARG = cmd->arg;
    hsd->CMD = reg_cmd;
    /* wait completed */
    rthw_sdio_wait_completed(sdio);

    /* Waiting for data to be sent to completion */
    if (data != RT_NULL)
    {
        volatile rt_uint32_t count = SDIO_TX_RX_COMPLETE_TIMEOUT_LOOPS;

        while (count && (hsd->STA & SDMMC_STA_DPSMACT))
        {
            count--;
        }

        if ((count == 0) || (hsd->STA & SDIO_ERRORS))
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
    rt_uint32_t temp, clk_src;
    rt_uint32_t clk = io_cfg->clock;
    struct rthw_sdio *sdio = host->private_data;
    SD_HandleTypeDef *hsd = &sdio->sdio_des.hw_sdio;
    SDMMC_InitTypeDef Init = {0};
    rt_uint32_t sdmmc_clk  = sdio->sdio_des.clk_get();

    if (sdmmc_clk < 400 * 1000)
    {
        LOG_E("The clock rate is too low! rata:%d", sdmmc_clk);
        return;
    }

    if (clk > host->freq_max)
        clk = host->freq_max;

    if (clk > sdmmc_clk)
    {
        LOG_W("Setting rate is greater than clock source rate.");
        clk = sdmmc_clk;
    }

    LOG_D("clk:%dK width:%s%s%s power:%s%s%s",
          clk / 1000,
          io_cfg->bus_width == MMCSD_BUS_WIDTH_8 ? "8" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_4 ? "4" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_1 ? "1" : "",
          io_cfg->power_mode == MMCSD_POWER_OFF ? "OFF" : "",
          io_cfg->power_mode == MMCSD_POWER_UP ? "UP" : "",
          io_cfg->power_mode == MMCSD_POWER_ON ? "ON" : ""
         );

    if (sdmmc_clk != 0U)
    {
        hsd->Init.ClockDiv = sdmmc_clk / (2U * SD_INIT_FREQ);
        /* Configure the SDMMC peripheral */
        Init.ClockEdge           = hsd->Init.ClockEdge;
        Init.ClockPowerSave      = hsd->Init.ClockPowerSave;
        if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
        {
            Init.BusWide             = SDMMC_BUS_WIDE_4B;
        }
        else if (io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
        {
            Init.BusWide             = SDMMC_BUS_WIDE_8B;
        }
        else
        {
            Init.BusWide             = SDMMC_BUS_WIDE_1B;
        }
        Init.HardwareFlowControl = hsd->Init.HardwareFlowControl;
        /* Check if user Clock div < Normal speed 25Mhz, no change in Clockdiv */
        if (hsd->Init.ClockDiv >= (sdmmc_clk / (2U * SD_NORMAL_SPEED_FREQ)))
        {
            Init.ClockDiv = hsd->Init.ClockDiv;
        }
        //CARD_ULTRA_HIGH_SPEED :UHS-I SD Card <50Mo/s for SDR50, DDR5 Cards and <104Mo/s for SDR104, Spec version 3.01
        else if (MMCSD_TIMING_UHS_SDR50 <= io_cfg->timing && io_cfg->timing <= MMCSD_TIMING_UHS_DDR50)
        {
            /* UltraHigh speed SD card,user Clock div */
            Init.ClockDiv = hsd->Init.ClockDiv;
        }
        //CARD_HIGH_SPEED: High Speed Card <25Mo/s , Spec version 2.00
        else if (io_cfg->timing == MMCSD_TIMING_SD_HS)
        {
            /* High speed SD card, Max Frequency = 50Mhz */
            if (hsd->Init.ClockDiv == 0U)
            {
                if (sdmmc_clk > SD_HIGH_SPEED_FREQ)
                {
                    Init.ClockDiv = sdmmc_clk / (2U * SD_HIGH_SPEED_FREQ);
                }
                else
                {
                    Init.ClockDiv = hsd->Init.ClockDiv;
                }
            }
            else
            {
                if ((sdmmc_clk/(2U * hsd->Init.ClockDiv)) > SD_HIGH_SPEED_FREQ)
                {
                    Init.ClockDiv = sdmmc_clk / (2U * SD_HIGH_SPEED_FREQ);
                }
                else
                {
                    Init.ClockDiv = hsd->Init.ClockDiv;
                }
            }
        }
        //CARD_NORMAL_SPEED: Normal Speed Card <12.5Mo/s , Spec Version 1.01
        else if (io_cfg->timing == MMCSD_TIMING_LEGACY)
        {
            /* No High speed SD card, Max Frequency = 25Mhz */
            if (hsd->Init.ClockDiv == 0U)
            {
                if (sdmmc_clk > SD_NORMAL_SPEED_FREQ)
                {
                    Init.ClockDiv = sdmmc_clk / (2U * SD_NORMAL_SPEED_FREQ);
                }
                else
                {
                    Init.ClockDiv = hsd->Init.ClockDiv;
                }
            }
            else
            {
                if ((sdmmc_clk/(2U * hsd->Init.ClockDiv)) > SD_NORMAL_SPEED_FREQ)
                {
                    Init.ClockDiv = sdmmc_clk / (2U * SD_NORMAL_SPEED_FREQ);
                }
                else
                {
                    Init.ClockDiv = hsd->Init.ClockDiv;
                }
            }
        }
        (void)SDMMC_Init(hsd->Instance, Init);
    }
    switch ((io_cfg->power_mode)&0X03)
    {
    case MMCSD_POWER_OFF:
        /* Set Power State to OFF */
        (void)SDMMC_PowerState_OFF(hsd->Instance);
        break;
    case MMCSD_POWER_UP:
        /* In  F4 series chips, 0X01 is reserved bit and has no practical effect.
           For F7 series chips, 0X01 is power-on after power-off,The SDMMC disables the function and the card clock stops.
           For H7 series chips, 0X03 is the power-on function.
        */
    case MMCSD_POWER_ON:
        /* Set Power State to ON */
        (void)SDMMC_PowerState_ON(hsd->Instance);
        break;
    default:
        LOG_W("unknown power mode %d", io_cfg->power_mode);
        break;
    }
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

    if (enable)
    {
        LOG_D("enable sdio irq");
        __HAL_SD_ENABLE_IT(&sdio->sdio_des.hw_sdio, SDMMC_IT_SDIOIT);
    }
    else
    {
        LOG_D("disable sdio irq");
        __HAL_SD_ENABLE_IT(&sdio->sdio_des.hw_sdio, SDMMC_IT_SDIOIT);
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
    struct rthw_sdio *sdio = host->private_data;
    rt_uint32_t intstatus = sdio->sdio_des.hw_sdio.Instance->STA;

    /* clear irq flag*/
    __HAL_SD_CLEAR_FLAG(&sdio->sdio_des.hw_sdio, intstatus);
    rt_event_send(&sdio->event, intstatus);
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
  * @param  sdio_des stm32_sdio_des
  * @retval rt_mmcsd_host
  */
struct rt_mmcsd_host *sdio_host_create(struct stm32_sdio_des *sdio_des)
{
    struct rt_mmcsd_host *host;
    struct rthw_sdio *sdio = RT_NULL;

    if (sdio_des == RT_NULL)
    {
        LOG_E("L:%d F:%s",(sdio_des == RT_NULL ? "sdio_des is NULL" : ""));
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
#ifdef BSP_USING_SDIO1
    if(sdio_des->hw_sdio.Instance == SDMMC1)
    {
        rt_event_init(&sdio->event, "sdio1", RT_IPC_FLAG_FIFO);
        rt_mutex_init(&sdio->mutex, "sdio1", RT_IPC_FLAG_PRIO);
    }
#endif /* BSP_USING_SDIO1 */
#ifdef BSP_USING_SDIO2
    if(sdio_des->hw_sdio.Instance == SDMMC2)
    {
        rt_event_init(&sdio->event, "sdio2", RT_IPC_FLAG_FIFO);
        rt_mutex_init(&sdio->mutex, "sdio2", RT_IPC_FLAG_PRIO);
    }
#endif /* BSP_USING_SDIO2 */

    /* set host default attributes */
    host->ops = &ops;
    host->freq_min = 400 * 1000;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = 0X00FFFF80;/* The voltage range supported is 1.65v-3.6v */

#ifndef SDIO_USING_1_BIT
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED;
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
  * @brief  This function get stm32 sdio clock.
  * @param  hw_sdio: stm32_sdio
  * @retval PCLK2Freq
  */
static rt_uint32_t stm32_sdio_clock_get(void)
{
    return HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SDMMC);
}

void SDMMC1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    /* Process All SDIO Interrupt Sources */
    rthw_sdio_irq_process(host1);
    /* leave interrupt */
    rt_interrupt_leave();
}

void SDMMC2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    /* Process All SDIO Interrupt Sources */
    rthw_sdio_irq_process(host2);
    /* leave interrupt */
    rt_interrupt_leave();
}

int rt_hw_sdio_init(void)
{
#ifdef BSP_USING_SDIO1
    struct stm32_sdio_des sdio_des1 = {0};
    sdio_des1.hw_sdio.Instance = SDMMC1;

    HAL_SD_MspInit(&sdio_des1.hw_sdio);
    HAL_NVIC_SetPriority(SDMMC1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);

    sdio_des1.clk_get  = stm32_sdio_clock_get;

    host1 = sdio_host_create(&sdio_des1);

    if (host1 == RT_NULL)
    {
        LOG_E("host1 create fail");
        return -RT_ERROR;
    }
#endif /* BSP_USING_SDIO1 */

#ifdef BSP_USING_SDIO2
    struct stm32_sdio_des sdio_des2 = {0};
    sdio_des2.hw_sdio.Instance = SDMMC2;

    HAL_SD_MspInit(&sdio_des2.hw_sdio);
    HAL_NVIC_SetPriority(SDMMC2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(SDMMC2_IRQn);

    sdio_des2.clk_get  = stm32_sdio_clock_get;

    host2 = sdio_host_create(&sdio_des2);

    if (host2 == RT_NULL)
    {
        LOG_E("host2 create fail");
        return -RT_ERROR;
    }
#endif /* BSP_USING_SDIO2 */
     return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

void stm32_mmcsd_change(void)
{
#ifdef BSP_USING_SDIO1
    mmcsd_change(host1);
#endif /* BSP_USING_SDIO2 */
#ifdef BSP_USING_SDIO2
    mmcsd_change(host2);
#endif /* BSP_USING_SDIO2 */
}

#endif /* RT_USING_SDIO */
