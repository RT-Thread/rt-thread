/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "drv_sdio.h"

#ifdef RT_USING_SDIO
#ifdef BSP_USING_SDIO

//#define DRV_DEBUG
#define LOG_TAG "drv.sdio"
#include <drv_log.h>

#define SDIO_BUFF_SIZE 4096
#define SDIO_ALIGN_LEN 4

#ifndef SDIO_MAX_FREQ
#define SDIO_MAX_FREQ (30000000)
#endif

struct swm_sdio_pkg
{
    struct rt_mmcsd_cmd *cmd;
    void *buff;
    rt_uint32_t flag;
};

typedef rt_err_t (*sdio_txconfig)(struct swm_sdio_pkg *pkg, rt_uint32_t *buff, int size);
typedef rt_err_t (*sdio_rxconfig)(struct swm_sdio_pkg *pkg, rt_uint32_t *buff, int size);
typedef rt_uint32_t (*sdio_clk_get)(SDIO_TypeDef *swm_sdio);

struct swm_sdio_des
{
    SDIO_TypeDef *swm_sdio;
    sdio_txconfig txconfig;
    sdio_rxconfig rxconfig;
    sdio_clk_get clk_get;
};

static struct rt_mmcsd_host *host;

#define RTHW_SDIO_LOCK(_sdio) rt_mutex_take(&_sdio->mutex, RT_WAITING_FOREVER)
#define RTHW_SDIO_UNLOCK(_sdio) rt_mutex_release(&_sdio->mutex);

struct swm_sdio_device
{
    struct rt_mmcsd_host *host;
    struct swm_sdio_des sdio_des;
    struct rt_event event;
    struct rt_mutex mutex;
    struct swm_sdio_pkg *pkg;
};

rt_align(SDIO_ALIGN_LEN)
static rt_uint8_t cache_buf[SDIO_BUFF_SIZE];

/**
  * @brief  This function wait sdio completed.
  * @param  sdio  swm_sdio_device
  * @retval None
  */
static void swm_sdio_wait_completed(struct swm_sdio_device *sdio)
{
    rt_uint32_t status;
    struct rt_mmcsd_cmd *cmd = sdio->pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    SDIO_TypeDef *swm_sdio = sdio->sdio_des.swm_sdio;

    if (rt_event_recv(&sdio->event, 0xffffffff, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      rt_tick_from_millisecond(2000), &status) != RT_EOK)
    {
        LOG_E("wait completed timeout");
        cmd->err = -RT_ETIMEOUT;
        return;
    }

    if (sdio->pkg == RT_NULL)
    {
        return;
    }

    if (resp_type(cmd) == RESP_NONE)
    {
        ;
    }
    else if (resp_type(cmd) == RESP_R2)
    {
        LOG_D("R2");
        cmd->resp[0] = (swm_sdio->RESP[3] << 8) + ((swm_sdio->RESP[2] >> 24) & 0xFF);
        cmd->resp[1] = (swm_sdio->RESP[2] << 8) + ((swm_sdio->RESP[1] >> 24) & 0xFF);
        cmd->resp[2] = (swm_sdio->RESP[1] << 8) + ((swm_sdio->RESP[0] >> 24) & 0xFF);
        cmd->resp[3] = (swm_sdio->RESP[0] << 8) + 0x00;
    }
    else
    {
        cmd->resp[0] = swm_sdio->RESP[0];
    }

    if (status & SDIO_IF_ERROR_Msk)
    {
        if ((status & SDIO_IF_CMDCRCERR_Msk) && (resp_type(cmd) & (RESP_R3 | RESP_R4)))
        {
            cmd->err = RT_EOK;
        }
        else
        {
            cmd->err = -RT_ERROR;
        }

        if (status & SDIO_IF_CMDCRCERR_Msk)
        {
            SDIO->CR2 |= (1 << SDIO_CR2_RSTCMD_Pos);
            data->err = -RT_ERROR;
        }

        if (status & SDIO_IF_CMDTIMEOUT_Msk)
        {
            SDIO->CR2 |= (1 << SDIO_CR2_RSTCMD_Pos);
            cmd->err = -RT_ETIMEOUT;
        }

        if (status & SDIO_IF_DATCRCERR_Msk)
        {
            SDIO->CR2 |= (1 << SDIO_CR2_RSTDAT_Pos);
            data->err = -RT_ERROR;
        }

        if (status & SDIO_IF_DATTIMEOUT_Msk)
        {
            SDIO->CR2 |= (1 << SDIO_CR2_RSTDAT_Pos);
            data->err = -RT_ETIMEOUT;
        }

        if (cmd->err == RT_EOK)
        {
            LOG_D("sta:0x%08X [%08X %08X %08X %08X]", status, cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
        }
        else
        {
            LOG_D("err:0x%08x, %s%s%s%s%s cmd:%d arg:0x%08x rw:%c len:%d blksize:%d",
                  status,
                  status & SDIO_IF_CMDCRCERR_Msk  ? "CCRCFAIL "    : "",
                  status & SDIO_IF_DATCRCERR_Msk  ? "DCRCFAIL "    : "",
                  status & SDIO_IF_CMDTIMEOUT_Msk ? "CTIMEOUT "    : "",
                  status & SDIO_IF_DATTIMEOUT_Msk ? "DTIMEOUT "    : "",
                  status == 0 ? "NULL" : "",
                  cmd->cmd_code,
                  cmd->arg,
                  data ? (data->flags & DATA_DIR_WRITE ? 'w' : 'r') : '-',
                  data ? data->blks * data->blksize : 0,
                  data ? data->blksize : 0);
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
  * @param  sdio  swm_sdio_device
  * @param  pkg   sdio package
  * @retval None
  */
static void swm_sdio_transfer(struct swm_sdio_device *sdio, struct swm_sdio_pkg *pkg)
{
    struct rt_mmcsd_data *data;
    int size;
    void *buff;

    if ((RT_NULL == pkg) || (RT_NULL == sdio))
    {
        LOG_E("swm_sdio_transfer invalid args");
        return;
    }

    data = pkg->cmd->data;
    if (RT_NULL == data)
    {
        LOG_E("swm_sdio_transfer invalid args");
        return;
    }

    buff = pkg->buff;
    if (RT_NULL == buff)
    {
        LOG_E("swm_sdio_transfer invalid args");
        return;
    }

    size = data->blks * data->blksize;

    if (data->flags & DATA_DIR_WRITE)
    {
        sdio->sdio_des.txconfig(pkg, (rt_uint32_t *)buff, size);
    }
    else if (data->flags & DATA_DIR_READ)
    {
        sdio->sdio_des.rxconfig(pkg, (rt_uint32_t *)buff, size);
    }
}

/**
  * @brief  This function send command.
  * @param  sdio  swm_sdio_device
  * @param  pkg   sdio package
  * @retval None
  */
static void swm_sdio_send_command(struct swm_sdio_device *sdio, struct swm_sdio_pkg *pkg)
{
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    SDIO_TypeDef *swm_sdio = sdio->sdio_des.swm_sdio;
    rt_uint32_t reg_cmd;

    /* save pkg */
    sdio->pkg = pkg;

    LOG_D("CMD:%d ARG:0x%08x RES:%s%s%s%s%s%s%s%s%s rw:%c len:%d blksize:%d",
          cmd->cmd_code,
          cmd->arg,
          resp_type(cmd) == RESP_NONE ? "NONE" : "",
          resp_type(cmd) == RESP_R1 ? "R1" : "",
          resp_type(cmd) == RESP_R1B ? "R1B" : "",
          resp_type(cmd) == RESP_R2 ? "R2" : "",
          resp_type(cmd) == RESP_R3 ? "R3" : "",
          resp_type(cmd) == RESP_R4 ? "R4" : "",
          resp_type(cmd) == RESP_R5 ? "R5" : "",
          resp_type(cmd) == RESP_R6 ? "R6" : "",
          resp_type(cmd) == RESP_R7 ? "R7" : "",
          data ? (data->flags & DATA_DIR_WRITE ? 'w' : 'r') : '-',
          data ? data->blks * data->blksize : 0,
          data ? data->blksize : 0);

    /* config cmd reg */
    reg_cmd = (cmd->cmd_code << SDIO_CMD_CMDINDX_Pos) |
              (0 << SDIO_CMD_CMDTYPE_Pos) |
              (0 << SDIO_CMD_IDXCHECK_Pos) |
              (0 << SDIO_CMD_CRCCHECK_Pos) |
              (0 << SDIO_CMD_DMAEN_Pos);
    if (resp_type(cmd) == RESP_NONE)
        reg_cmd |= SD_RESP_NO << SDIO_CMD_RESPTYPE_Pos;
    else if (resp_type(cmd) == RESP_R2)
        reg_cmd |= SD_RESP_128b << SDIO_CMD_RESPTYPE_Pos;
    else
        reg_cmd |= SD_RESP_32b << SDIO_CMD_RESPTYPE_Pos;

    /* config data reg */
    if (data != RT_NULL)
    {
        rt_uint32_t dir = 0;
        dir = (data->flags & DATA_DIR_READ) ? 1 : 0;

        swm_sdio->BLK = (data->blks << SDIO_BLK_COUNT_Pos) | (data->blksize << SDIO_BLK_SIZE_Pos);

        reg_cmd |= (1 << SDIO_CMD_HAVEDATA_Pos) |
                   (dir << SDIO_CMD_DIRREAD_Pos) |
                   ((data->blks > 1) << SDIO_CMD_MULTBLK_Pos) |
                   ((data->blks > 1) << SDIO_CMD_BLKCNTEN_Pos) |
                   (0 << SDIO_CMD_AUTOCMD12_Pos);
    }
    else
    {
        reg_cmd |= (0 << SDIO_CMD_HAVEDATA_Pos);
    }

    /* send cmd */
    swm_sdio->ARG = cmd->arg;
    swm_sdio->CMD = reg_cmd;

    /* transfer config */
    if (data != RT_NULL)
    {
        swm_sdio_transfer(sdio, pkg);
    }

    /* wait completed */
    swm_sdio_wait_completed(sdio);

    /* clear pkg */
    sdio->pkg = RT_NULL;
}

/**
  * @brief  This function send sdio request.
  * @param  sdio  swm_sdio_device
  * @param  req   request
  * @retval None
  */
static void swm_sdio_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct swm_sdio_pkg pkg;
    struct swm_sdio_device *sdio = host->private_data;
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

        swm_sdio_send_command(sdio, &pkg);

        if ((data != RT_NULL) && (data->flags & DATA_DIR_READ) && ((rt_uint32_t)data->buf & (SDIO_ALIGN_LEN - 1)))
        {
            rt_memcpy(data->buf, cache_buf, data->blksize * data->blks);
        }
    }

    if (req->stop != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
        pkg.cmd = req->stop;
        swm_sdio_send_command(sdio, &pkg);
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
static void swm_sdio_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_uint32_t clkcr, div, clk_src;
    rt_uint32_t clk = io_cfg->clock;
    struct swm_sdio_device *sdio = host->private_data;
    SDIO_TypeDef *swm_sdio = sdio->sdio_des.swm_sdio;

    clk_src = sdio->sdio_des.clk_get(sdio->sdio_des.swm_sdio);
    if (clk_src < 400 * 1000)
    {
        LOG_E("The clock rate is too low! rata:%d", clk_src);
        return;
    }

    if (clk > host->freq_max)
        clk = host->freq_max;

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
          io_cfg->power_mode == MMCSD_POWER_ON ? "ON" : "");

    RTHW_SDIO_LOCK(sdio);

    swm_sdio->CR1 = (1 << SDIO_CR1_CDSRC_Pos) | (7 << SDIO_CR1_VOLT_Pos);
    if (io_cfg->bus_width == MMCSD_BUS_WIDTH_8)
    {
        swm_sdio->CR1 |= (1 << SDIO_CR1_8BIT_Pos);
    }
    else
    {
        swm_sdio->CR1 &= ~SDIO_CR1_8BIT_Msk;
        if (io_cfg->bus_width == MMCSD_BUS_WIDTH_4)
        {
            swm_sdio->CR1 |= (1 << SDIO_CR1_4BIT_Pos);
        }
        else
        {
            swm_sdio->CR1 &= ~SDIO_CR1_4BIT_Msk;
        }
    }
    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_OFF:
        swm_sdio->CR1 &= ~SDIO_CR1_PWRON_Msk;
        break;
    case MMCSD_POWER_UP:
    case MMCSD_POWER_ON:
        swm_sdio->CR1 |= (1 << SDIO_CR1_PWRON_Pos);
        break;
    default:
        LOG_W("unknown power_mode %d", io_cfg->power_mode);
        break;
    }

    div = clk_src / clk;
    if ((clk == 0) || (div == 0))
    {
        clkcr = 0;
    }
    else
    {
        if (div > 128)
            clkcr = 0x80;
        else if (div > 64)
            clkcr = 0x40;
        else if (div > 32)
            clkcr = 0x20;
        else if (div > 16)
            clkcr = 0x10;
        else if (div > 8)
            clkcr = 0x08;
        else if (div > 4)
            clkcr = 0x04;
        else if (div > 2)
            clkcr = 0x02;
        else if (div > 1)
            clkcr = 0x01;
        else
            clkcr = 0x00;
    }

    SDIO->CR2 = (1 << SDIO_CR2_CLKEN_Pos) |
                (1 << SDIO_CR2_SDCLKEN_Pos) |
                (clkcr << SDIO_CR2_SDCLKDIV_Pos) |
                (0xC << SDIO_CR2_TIMEOUT_Pos); // 2**25 SDIO_CLK

    while ((SDIO->CR2 & SDIO_CR2_CLKRDY_Msk) == 0)
        ;

    RTHW_SDIO_UNLOCK(sdio);
}

/**
  * @brief  This function delect sdcard.
  * @param  host    rt_mmcsd_host
  * @retval 0x01
  */
static rt_int32_t swm_sdio_get_card_status(struct rt_mmcsd_host *host)
{
    LOG_D("try to detect device");
    return 0x01;
}

/**
  * @brief  This function update sdio interrupt.
  * @param  host    rt_mmcsd_host
  * @param  enable
  * @retval None
  */
void swm_sdio_enable_irq(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    struct swm_sdio_device *sdio = host->private_data;
    SDIO_TypeDef *swm_sdio = sdio->sdio_des.swm_sdio;

    if (enable)
    {
        LOG_D("enable sdio irq");
        swm_sdio->IM = 0xFFFFFFFF;
        swm_sdio->IE = 0xFFFF000F;
    }
    else
    {
        LOG_D("disable sdio irq");
        swm_sdio->IM &= ~0xFFFFFFFF;
        swm_sdio->IE &= ~0xFFFFFFFF;
    }
}

static const struct rt_mmcsd_host_ops swm_sdio_ops =
    {
        .request = swm_sdio_request,
        .set_iocfg = swm_sdio_set_iocfg,
        .get_card_status = swm_sdio_get_card_status,
        .enable_sdio_irq = swm_sdio_enable_irq,
};

struct rt_mmcsd_host *swm_sdio_host_create(struct swm_sdio_des *sdio_des)
{
    struct rt_mmcsd_host *host;
    struct swm_sdio_device *sdio = RT_NULL;

    if ((sdio_des == RT_NULL) || (sdio_des->txconfig == RT_NULL) || (sdio_des->rxconfig == RT_NULL))
    {
        LOG_E("L:%d F:%s %s %s %s",
              (sdio_des == RT_NULL ? "sdio_des is NULL" : ""),
              (sdio_des ? (sdio_des->txconfig ? "txconfig is NULL" : "") : ""),
              (sdio_des ? (sdio_des->rxconfig ? "rxconfig is NULL" : "") : ""));
        return RT_NULL;
    }

    sdio = rt_malloc(sizeof(struct swm_sdio_device));
    if (sdio == RT_NULL)
    {
        LOG_E("L:%d F:%s malloc swm_sdio_device fail");
        return RT_NULL;
    }
    rt_memset(sdio, 0, sizeof(struct swm_sdio_device));

    host = mmcsd_alloc_host();
    if (host == RT_NULL)
    {
        LOG_E("L:%d F:%s mmcsd alloc host fail");
        rt_free(sdio);
        return RT_NULL;
    }

    rt_memcpy(&sdio->sdio_des, sdio_des, sizeof(struct swm_sdio_des));

    rt_event_init(&sdio->event, "sdio", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&sdio->mutex, "sdio", RT_IPC_FLAG_FIFO);

    /* set host defautl attributes */
    host->ops = &swm_sdio_ops;
    host->freq_min = 400 * 1000;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = 0X00FFFF80; /* The voltage range supported is 1.65v-3.6v */
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

    swm_sdio_enable_irq(host, 1);

    /* ready to change */
    mmcsd_change(host);

    return host;
}

static rt_uint32_t swm_sdio_clock_get(SDIO_TypeDef *swm_sdio)
{
    uint32_t prediv = ((SYS->CLKDIV & SYS_CLKDIV_SDIO_Msk) >> SYS_CLKDIV_SDIO_Pos);
    return (SystemCoreClock / (1 << prediv));
}

static rt_err_t swm_sdio_rxconfig(struct swm_sdio_pkg *pkg, rt_uint32_t *buff, int size)
{
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    int offset = 0;
    for (uint32_t i = 0; i < data->blks; i++)
    {
        offset = i* data->blksize / 4;
        while ((SDIO->IF & SDIO_IF_BUFRDRDY_Msk) == 0)
            __NOP();
        SDIO->IF = SDIO_IF_BUFRDRDY_Msk;
        for (uint32_t j = 0; j < data->blksize / 4; j++)
        {
            buff[offset + j] = SDIO->DATA;
        }
    }
    return RT_EOK;
}

static rt_err_t swm_sdio_txconfig(struct swm_sdio_pkg *pkg, rt_uint32_t *buff, int size)
{
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    int offset = 0;
    for (uint32_t i = 0; i < data->blks; i++)
    {
        offset = i* data->blksize / 4;
        while ((SDIO->IF & SDIO_IF_BUFWRRDY_Msk) == 0)
            __NOP();
        SDIO->IF = SDIO_IF_BUFWRRDY_Msk;
        for (uint32_t j = 0; j < data->blksize / 4; j++)
        {
            SDIO->DATA = buff[offset + j];
        }
    }
    return RT_EOK;
}

/**
  * @brief  This function interrupt process function.
  * @param  host  rt_mmcsd_host
  * @retval None
  */
static void swm_sdio_irq_process(struct rt_mmcsd_host *host)
{
    int complete = 0;
    struct swm_sdio_device *sdio = host->private_data;
    SDIO_TypeDef *swm_sdio = sdio->sdio_des.swm_sdio;
    rt_uint32_t intstatus = swm_sdio->IF;

    if (intstatus & SDIO_IF_ERROR_Msk)
    {
        swm_sdio->IF = 0xFFFFFFFF;
        complete = 1;
    }
    else
    {
        if (intstatus & SDIO_IF_CMDDONE_Msk)
        {
            swm_sdio->IF = SDIO_IF_CMDDONE_Msk;
            if (sdio->pkg != RT_NULL)
            {
                if (!sdio->pkg->cmd->data)
                {
                    complete = 1;
                }
            }
        }

        if (intstatus & SDIO_IF_TRXDONE_Msk)
        {
            swm_sdio->IF = SDIO_IF_TRXDONE_Msk;
            complete = 1;
        }
    }

    if (complete)
    {
        rt_event_send(&sdio->event, intstatus);
    }
}

void SDIO_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    /* Process All SDIO Interrupt Sources */
    swm_sdio_irq_process(host);
    /* leave interrupt */
    rt_interrupt_leave();
}

int swm_sdio_init(void)
{
    int result = RT_EOK;
    struct swm_sdio_des sdio_des;

#if 1
    PORT_Init(PORTB, PIN1, PORTB_PIN1_SD_CLK, 0);
    PORT_Init(PORTB, PIN2, PORTB_PIN2_SD_CMD, 1);
    PORT_Init(PORTB, PIN3, PORTB_PIN3_SD_D0, 1);
    PORT_Init(PORTB, PIN4, PORTB_PIN4_SD_D1, 1);
    PORT_Init(PORTB, PIN5, PORTB_PIN5_SD_D2, 1);
    PORT_Init(PORTB, PIN6, PORTB_PIN6_SD_D3, 1);
#else
    PORT_Init(PORTP, PIN11, PORTP_PIN11_SD_CLK, 0);
    PORT_Init(PORTP, PIN10, PORTP_PIN10_SD_CMD, 1);
    PORT_Init(PORTP, PIN9, PORTP_PIN9_SD_D0, 1);
    PORT_Init(PORTP, PIN8, PORTP_PIN8_SD_D1, 1);
    PORT_Init(PORTP, PIN7, PORTP_PIN7_SD_D2, 1);
    PORT_Init(PORTP, PIN6, PORTP_PIN6_SD_D3, 1);
#endif
    NVIC_EnableIRQ(SDIO_IRQn);
    SYS->CLKDIV &= ~SYS_CLKDIV_SDIO_Msk;
    if (SystemCoreClock > 80000000)                //SDIO时钟需要小于52MHz
        SYS->CLKDIV |= (2 << SYS_CLKDIV_SDIO_Pos); //SDCLK = SYSCLK / 4
    else
        SYS->CLKDIV |= (1 << SYS_CLKDIV_SDIO_Pos); //SDCLK = SYSCLK / 2

    SYS->CLKEN |= (0x01 << SYS_CLKEN_SDIO_Pos);

    SDIO->CR2 = (1 << SDIO_CR2_RSTALL_Pos);

    NVIC_EnableIRQ(SDIO_IRQn);
    sdio_des.clk_get = swm_sdio_clock_get;
    sdio_des.swm_sdio = SDIO;
    sdio_des.rxconfig = swm_sdio_rxconfig;
    sdio_des.txconfig = swm_sdio_txconfig;

    host = swm_sdio_host_create(&sdio_des);
    if (host == RT_NULL)
    {
        LOG_E("host create fail.");
        result = -1;
    }
    else
    {
        LOG_D("host create success.");
        result = 0;
    }
    return result;
}
INIT_DEVICE_EXPORT(swm_sdio_init);

#endif /* BSP_USING_SDIO */
#endif /* RT_USING_SDIO */
