/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-14     CDT          first version
 */


/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_SDIO)

#if defined(BSP_USING_SDIO1) || defined(BSP_USING_SDIO2)

#include "drv_sdio.h"
#include "board_config.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/* rthw sdio */
struct rthw_sdio
{
    struct rt_mmcsd_host *host;
    struct hc32_sdio_config *config;
    struct hc32_sdio_des des;
    struct rt_event event;
    struct rt_mutex mutex;
    struct sdio_pkg *pkg;
    uint8_t *cache_buf;
};

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//#define DRV_DEBUG
#define LOG_TAG "drv.sdio"
#include <drv_log.h>

#ifndef SDIO_BUFF_SIZE
    #define SDIO_BUFF_SIZE          (4096)
#endif

#ifndef SDIO_ALIGN_LEN
    #define SDIO_ALIGN_LEN          (4)
#endif

#ifndef SDIO_MAX_FREQ
    #define SDIO_MAX_FREQ           (50*1000*1000)
#endif

#define RTHW_SDIO_LOCK(_sdio)   rt_mutex_take(&(_sdio)->mutex, RT_WAITING_FOREVER)
#define RTHW_SDIO_UNLOCK(_sdio) rt_mutex_release(&(_sdio)->mutex);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern rt_err_t rt_hw_board_sdio_init(CM_SDIOC_TypeDef *SDIOCx);

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
#ifdef BSP_USING_SDIO1
    static void _sdio1_handler(void);
#endif

#ifdef BSP_USING_SDIO2
    static void _sdio2_handler(void);
#endif

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
enum
{
#ifdef BSP_USING_SDIO1
    SDIO1_INDEX,
#endif
#ifdef BSP_USING_SDIO2
    SDIO2_INDEX,
#endif
};

static struct hc32_sdio_config _sdio_config[] =
{
#ifdef BSP_USING_SDIO1
    SDIO1_BUS_CONFIG,
#endif  /* BSP_USING_SDIO1 */
#ifdef BSP_USING_SDIO2
    SDIO2_BUS_CONFIG,
#endif  /* BSP_USING_SDIO2 */
};

static const func_ptr_t _sdio_irq_handler[] =
{
#ifdef BSP_USING_SDIO1
    _sdio1_handler,
#endif  /* BSP_USING_SDIO1 */
#ifdef BSP_USING_SDIO2
    _sdio2_handler,
#endif  /* BSP_USING_SDIO2 */
};

#ifdef BSP_USING_SDIO1
    rt_align(SDIO_ALIGN_LEN)
    static rt_uint8_t _sdio1_cache_buf[SDIO_BUFF_SIZE];
#endif

#ifdef BSP_USING_SDIO2
    rt_align(SDIO_ALIGN_LEN)
    static rt_uint8_t _sdio2_cache_buf[SDIO_BUFF_SIZE];
#endif

static rt_uint8_t *const _sdio_cache_buf[] =
{
#ifdef BSP_USING_SDIO1
    _sdio1_cache_buf,
#endif  /* BSP_USING_SDIO1 */
#ifdef BSP_USING_SDIO2
    _sdio2_cache_buf,
#endif  /* BSP_USING_SDIO2 */
};

static struct rt_mmcsd_host *_sdio_host[sizeof(_sdio_config) / sizeof(_sdio_config[0])] = {0};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Get the response type of hc32 sdioc driver.
 * @param  [in] rt_resp_type            SDIO command response type defined in mmcs_core.h
 * @retval The response type of hc32 sdioc driver
 */
static rt_uint32_t _sdio_get_cmd_resptype(rt_uint32_t rt_resptype)
{
    rt_uint32_t sdioc_resptype;

    switch (rt_resptype)
    {
    case RESP_NONE:
        sdioc_resptype = SDIOC_RESP_TYPE_NO;
        break;
    case RESP_R1:
        sdioc_resptype = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        break;
    case RESP_R2:
        sdioc_resptype = SDIOC_RESP_TYPE_R2;
        break;
    case RESP_R3:
    case RESP_R4:
        sdioc_resptype = SDIOC_RESP_TYPE_R3_R4;
        break;
    case RESP_R5:
    case RESP_R6:
    case RESP_R7:
        sdioc_resptype = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        break;
    case RESP_R1B:
        sdioc_resptype = SDIOC_RESP_TYPE_R1B_R5B;
        break;
    default:
        sdioc_resptype = SDIOC_RESP_TYPE_NO;
        LOG_E("unknown response type: %d", rt_resptype);
        break;
    }

    return sdioc_resptype;
}

/**
 * @brief  This function wait sdio completed.
 * @param  [in] sdio                    Pointer to a @ref rthw_sdio structure
 * @retval None
 */
static void _sdio_wait_completed(struct rthw_sdio *sdio)
{
    rt_uint32_t status;
    rt_uint32_t response[4];
    __IO rt_uint32_t to_count;
    struct rt_mmcsd_cmd *cmd = sdio->pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    CM_SDIOC_TypeDef *instance = sdio->config->instance;

    if (rt_event_recv(&sdio->event, 0xFFFFFFFF, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      rt_tick_from_millisecond(5000), &status) != RT_EOK)
    {
        LOG_E("[%s timeout] sta=0x%08X, cmd %d, arg:0x%08X", __func__, status, cmd->cmd_code, cmd->arg);
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
        (void)SDIOC_GetResponse(instance, SDIOC_RESP_REG_BIT0_31,   &response[0]);
        (void)SDIOC_GetResponse(instance, SDIOC_RESP_REG_BIT32_63,  &response[1]);
        (void)SDIOC_GetResponse(instance, SDIOC_RESP_REG_BIT64_95,  &response[2]);
        (void)SDIOC_GetResponse(instance, SDIOC_RESP_REG_BIT96_127, &response[3]);

        cmd->resp[0] = (response[3] << 8) + ((response[2] >> 24) & 0xFF);
        cmd->resp[1] = (response[2] << 8) + ((response[1] >> 24) & 0xFF);
        cmd->resp[2] = (response[1] << 8) + ((response[0] >> 24) & 0xFF);
        cmd->resp[3] = (response[0] << 8) + 0x00;
    }
    else
    {
        (void)SDIOC_GetResponse(instance, SDIOC_RESP_REG_BIT0_31, &response[0]);
        cmd->resp[0] = response[0];
    }

    if (status & SDIOC_INT_FLAG_EI)
    {
        if (status & (SDIOC_INT_FLAG_CTOE | SDIOC_INT_FLAG_CCE | SDIOC_INT_FLAG_CEBE | SDIOC_INT_FLAG_CIE))
        {
            SDIOC_SWReset(instance, SDIOC_SW_RST_CMD_LINE);
            cmd->err = -RT_ERROR;
            LOG_D("[%s cmd err] sta=0x%08X, %s%s%s%s cmd %d arg:0x%08X",
                  __func__,
                  status,
                  status & SDIOC_INT_FLAG_CCE  ? "Command CRC Error "    : "",
                  status & SDIOC_INT_FLAG_CEBE ? "Command End Bit Error" : "",
                  status & SDIOC_INT_FLAG_CTOE ? "Command Timeout Error" : "",
                  status == 0 ? "NULL" : "",
                  cmd->cmd_code,
                  cmd->arg);
        }

        if (status & (SDIOC_INT_FLAG_DTOE | SDIOC_INT_FLAG_DCE | SDIOC_INT_FLAG_DEBE))
        {
            SDIOC_SWReset(instance, SDIOC_SW_RST_DATA_LINE);
            if (data != NULL)
            {
                data->err = -RT_ERROR;
                LOG_D("[%s dat err] sta=0x%08X, %s%s%s%s cmd %d arg:0x%08X rw:%c len:%d blksize:%d",
                      __func__,
                      status,
                      status & SDIOC_INT_FLAG_DCE  ? "Data CRC Error "    : "",
                      status & SDIOC_INT_FLAG_DEBE ? "Data End Bit Error" : "",
                      status & SDIOC_INT_FLAG_DTOE ? "Data Timeout Error" : "",
                      status == 0 ? "NULL" : "",
                      cmd->cmd_code,
                      cmd->arg,
                      data ? (data->flags & DATA_DIR_WRITE ? 'w' : 'r') : '-',
                      data ? data->blks * data->blksize : 0,
                      data ? data->blksize : 0);
            }
        }
    }
    else
    {
        cmd->err = RT_EOK;
        LOG_D("[%s xfer ok] sta=0x%08X, cmd %d, arg:0x%08X, resp[%08X %08X %08X %08X]",
              __func__,
              status,
              cmd->cmd_code,
              cmd->arg,
              cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
    }
}

/**
 * @brief  Transfer data by dma.
 * @param  [in] sdio                    Pointer to a @ref rthw_sdio structure
 * @param  [in] pkg                     Pointer to a @ref sdio_pkg structure
 * @retval None
 */
static void _sdio_transfer_by_dma(struct rthw_sdio *sdio, struct sdio_pkg *pkg)
{
    struct rt_mmcsd_data *data = pkg->cmd->data;

    if ((NULL == sdio) || (NULL == pkg) || (NULL == pkg->buf) || (NULL == pkg->cmd) || (NULL == pkg->cmd->data))
    {
        LOG_E("%s function arguments error: %s %s %s %s %s",
              __func__,
              (sdio == RT_NULL ? "sdio is NULL" : ""),
              (pkg  == RT_NULL ? "pkg is NULL"  : ""),
              (sdio ? (pkg->buf == RT_NULL ? "pkg->buf is NULL" : "") : ""),
              (sdio ? (pkg->cmd == RT_NULL ? "pkg->cmd is NULL" : "") : ""),
              (sdio ? (pkg->cmd->data == RT_NULL ? "pkg->cmd->data is NULL" : "") : "")
             );
        return;
    }

    if (data->flags & DATA_DIR_WRITE)
    {
        sdio->des.txconfig(sdio->config->dma_tx.Instance, sdio->config->dma_tx.channel, pkg);
        DMA_ChCmd(sdio->config->dma_tx.Instance, sdio->config->dma_tx.channel, ENABLE);
    }
    else if (data->flags & DATA_DIR_READ)
    {
        sdio->des.rxconfig(sdio->config->dma_rx.Instance, sdio->config->dma_rx.channel, pkg);
        DMA_ChCmd(sdio->config->dma_rx.Instance, sdio->config->dma_rx.channel, ENABLE);
    }
}

/**
 * @brief  Send command.
 * @param  [in] sdio                    Pointer to a @ref rthw_sdio structure
 * @param  [in] pkg                     Pointer to a @ref sdio_pkg structure
 * @retval None
 */
static void _sdio_send_command(struct rthw_sdio *sdio, struct sdio_pkg *pkg)
{
    rt_int32_t ret;
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    CM_SDIOC_TypeDef *instance = sdio->config->instance;
    stc_sdioc_cmd_config_t stcCmdConfig;
    stc_sdioc_data_config_t stcDataConfig;

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

    /* config command */
    stcCmdConfig.u16CmdIndex = cmd->cmd_code;

    /* config command argument */
    stcCmdConfig.u32Argument = cmd->arg;

    /* config command type */
    stcCmdConfig.u16CmdType  = SDIOC_CMD_TYPE_NORMAL;

    /* config response type */
    stcCmdConfig.u16ResponseType = _sdio_get_cmd_resptype(resp_type(cmd));

    if (data != RT_NULL)
    {
        /* config data */
        stcDataConfig.u16BlockSize   = data->blksize;
        stcDataConfig.u16BlockCount  = data->blks;
        stcDataConfig.u16TransDir    = (data->flags & DATA_DIR_READ) ? SDIOC_TRANS_DIR_TO_HOST : SDIOC_TRANS_DIR_TO_CARD;
        stcDataConfig.u16AutoCmd12   = SDIOC_AUTO_SEND_CMD12_DISABLE;
        stcDataConfig.u16DataTimeout = SDIOC_DATA_TIMEOUT_CLK_2E27;
        stcDataConfig.u16TransMode   = (data->blks > 1U) ? SDIOC_TRANS_MD_MULTI : SDIOC_TRANS_MD_SINGLE;
        ret = SDIOC_ConfigData(instance, &stcDataConfig);
        if (ret != 0)
        {
            LOG_E("configure data error : %d", ret);
        }

        /* transfer config */
        _sdio_transfer_by_dma(sdio, pkg);

        stcCmdConfig.u16DataLine = SDIOC_DATA_LINE_ENABLE;;
    }
    else
    {
        stcCmdConfig.u16DataLine = SDIOC_DATA_LINE_DISABLE;
    }

    /* send cmd */
    ret = SDIOC_SendCommand(instance, &stcCmdConfig);
    if (ret != 0)
    {
        LOG_E("send command error : %d", ret);
    }

    /* wait completed */
    _sdio_wait_completed(sdio);

    /* clear pkg */
    sdio->pkg = RT_NULL;
}

/**
 * @brief  Send sdio request.
 * @param  [in] host                   Pointer to a @ref rt_mmcsd_host structure
 * @param  [in] req                    Pointer to a @ref rt_mmcsd_req structure
 * @retval None
 */
static void _sdio_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    rt_uint32_t mask;
    struct sdio_pkg pkg;
    struct rt_mmcsd_data *data;
    struct rthw_sdio *sdio = host->private_data;

    if ((NULL == host) || (NULL == req) || (NULL == sdio) || (NULL == sdio->config))
    {
        LOG_E("%s function arguments error: %s %s %s %s",
              __func__,
              (host == RT_NULL ? "host is NULL" : ""),
              (req  == RT_NULL ? "req is NULL"  : ""),
              (sdio == RT_NULL ? "sdio is NULL" : ""),
              (sdio ? (sdio->config == RT_NULL ? "sdio->config is NULL" : "") : "")
             );
        return;
    }

    RTHW_SDIO_LOCK(sdio);

    if (req->cmd != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
        data = req->cmd->data;
        pkg.cmd = req->cmd;

        if (SD_SEND_IF_COND == pkg.cmd->cmd_code)
        {
            mask = (CM_SDIOC1 == sdio->config->instance) ? PERIC_SDIOC_SYCTLREG_SELMMC1 : PERIC_SDIOC_SYCTLREG_SELMMC2;
            if (data == RT_NULL)
            {
                CM_PERIC->SDIOC_SYCTLREG &= ~mask;
            }
            else
            {
                CM_PERIC->SDIOC_SYCTLREG |= mask;
            }
        }

        if (data != RT_NULL)
        {
            rt_uint32_t size = data->blks * data->blksize;

            RT_ASSERT(size <= SDIO_BUFF_SIZE);

            /* buffer unaligned */
            if ((rt_uint32_t)data->buf & (SDIO_ALIGN_LEN - 1))
            {
                if (data->flags & DATA_DIR_WRITE)
                {
                    rt_memcpy(sdio->cache_buf, data->buf, size);
                }
                pkg.buf = sdio->cache_buf;
            }
            else
            {
                pkg.buf = data->buf;
            }
        }

        _sdio_send_command(sdio, &pkg);

        if ((data != RT_NULL) && (data->flags & DATA_DIR_READ) && ((rt_uint32_t)data->buf & (SDIO_ALIGN_LEN - 1)))
        {
            rt_memcpy(data->buf, sdio->cache_buf, data->blksize * data->blks);
        }
    }

    if (req->stop != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
        pkg.cmd = req->stop;
        _sdio_send_command(sdio, &pkg);
    }

    RTHW_SDIO_UNLOCK(sdio);

    mmcsd_req_complete(sdio->host);
}

/**
 * @brief  Config sdio.
 * @param  [in] host                   Pointer to a @ref rt_mmcsd_host structure
 * @param  [in] io_cfg                 Pointer to a @ref rt_mmcsd_io_cfg structure
 * @retval None
 */
static void _sdio_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_int32_t ret;
    rt_uint32_t clk;
    rt_uint16_t clk_div;
    rt_uint32_t clk_src;
    struct rthw_sdio *sdio = host->private_data;
    CM_SDIOC_TypeDef *instance;

    if ((NULL == host) || (NULL == io_cfg) || (NULL == sdio) || (NULL == sdio->config))
    {
        LOG_E("%s function arguments error: %s %s %s %s",
              __func__,
              (host   == RT_NULL ? "host is NULL"     : ""),
              (io_cfg == RT_NULL ? "io_cfg is NULL"   : ""),
              (sdio   == RT_NULL ? "sdio_des is NULL" : ""),
              (sdio ? (sdio->config == RT_NULL ? "sdio->config is NULL" : "") : "")
             );
        return;
    }

    instance = sdio->config->instance;

    clk_src = sdio->des.clk_get(instance);
    if (clk_src < 400 * 1000)
    {
        LOG_E("clock rate is too low! rate:%d", clk_src);
        return;
    }

    clk = io_cfg->clock;
    if (clk > host->freq_max)
    {
        clk = host->freq_max;
    }

    if (clk > clk_src)
    {
        LOG_W("setting rate is greater than clock source rate.");
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

    switch (io_cfg->bus_width)
    {
    case MMCSD_BUS_WIDTH_1:
        SDIOC_SetBusWidth(instance, SDIOC_BUS_WIDTH_1BIT);
        break;
    case MMCSD_BUS_WIDTH_4:
        SDIOC_SetBusWidth(instance, SDIOC_BUS_WIDTH_4BIT);
        break;
    case MMCSD_BUS_WIDTH_8:
        SDIOC_SetBusWidth(instance, SDIOC_BUS_WIDTH_8BIT);
        break;
    default:
        LOG_E("unknown bus width: %d", io_cfg->bus_width);
        break;
    }

    switch (io_cfg->power_mode)
    {
    case MMCSD_POWER_OFF:
        SDIOC_PowerCmd(instance, DISABLE);
        break;
    case MMCSD_POWER_UP:
    case MMCSD_POWER_ON:
        SDIOC_PowerCmd(instance, ENABLE);
        break;
    default:
        LOG_W("unknown power_mode %d", io_cfg->power_mode);
        break;
    }

    instance->CLKCON = 0;

    if (clk > 0)
    {
        ret = SDIOC_GetOptimumClockDiv(clk, &clk_div);
        if (ret != LL_OK)
        {
            LOG_E("clock division error");
        }
        else
        {
            SDIOC_SetClockDiv(instance, clk_div);

            if ((clk << 1) <= host->freq_max)
            {
                SDIOC_SetSpeedMode(instance, SDIOC_SPEED_MD_NORMAL);
            }
            else
            {
                SDIOC_SetSpeedMode(instance, SDIOC_SPEED_MD_HIGH);
            }

            instance->CLKCON = (clk_div | SDIOC_CLKCON_ICE | SDIOC_CLKCON_CE);
        }
    }

    RTHW_SDIO_UNLOCK(sdio);
}

/**
 * @brief  Update the sdio interrupt.
 * @param  [in] host                    Pointer to a @ref rt_mmcsd_host structure
 * @param  [in] enable                  Enable interrupt when value is non-zero
 * @retval None
 */
static void _sdio_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    struct rthw_sdio *sdio = host->private_data;
    CM_SDIOC_TypeDef *instance = sdio->config->instance;

    if (enable)
    {
        LOG_D("enable sdio interrupt");
        SDIOC_IntStatusCmd(instance, SDIOC_INT_CINTSEN, ENABLE);
        SDIOC_IntCmd(instance, SDIOC_INT_CINTSEN, ENABLE);
    }
    else
    {
        LOG_D("disable sdio interrupt");
        SDIOC_IntStatusCmd(instance, SDIOC_INT_CINTSEN, DISABLE);
        SDIOC_IntCmd(instance, SDIOC_INT_CINTSEN, DISABLE);
    }
}

/**
 * @brief  update all of the using interrupt.
 * @param  [in] host                    Pointer to a @ref rt_mmcsd_host structure
 * @param  [in] enable                  Enable interrupt when value is non-zero
 * @retval None
 */
static void _sdio_update_irq(struct rt_mmcsd_host *host, rt_int32_t enable)
{
    struct rthw_sdio *sdio = host->private_data;
    CM_SDIOC_TypeDef *instance = sdio->config->instance;
    const rt_uint32_t int_type = (SDIOC_INT_CCSEN | SDIOC_INT_TCSEN | SDIOC_ERR_INT_ALL);

    if (enable)
    {
        LOG_D("enable all of the using interrupt");
        SDIOC_IntStatusCmd(instance, (int_type | SDIOC_INT_BRRSEN | SDIOC_INT_BWRSEN), ENABLE);
        SDIOC_IntCmd(instance, int_type, ENABLE);
    }
    else
    {
        LOG_D("disable all of the using interrupt");
        SDIOC_IntStatusCmd(instance, (int_type | SDIOC_INT_BRRSEN | SDIOC_INT_BWRSEN), DISABLE);
        SDIOC_IntCmd(instance, int_type, DISABLE);
    }
}

/**
 * @brief  Get card status.
 * @param  [in] host                    Pointer to a @ref rt_mmcsd_host structure
 * @retval rt_int32_t:
 *           - 0: No card
 *           - 1: Card inserted
 */
static rt_int32_t _sdio_get_card_status(struct rt_mmcsd_host *host)
{
    struct rthw_sdio *sdio = host->private_data;

    LOG_D("try to detect device");
    return (rt_int32_t)SDIOC_GetHostStatus(sdio->config->instance, SDIOC_HOST_FLAG_CIN);
}

static const struct rt_mmcsd_host_ops _mmcsd_host_ops =
{
    _sdio_request,
    _sdio_iocfg,
    _sdio_get_card_status,
    _sdio_enable_sdio_irq,
};

/**
 * @brief  Get SDIO clock source frequency.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 * @retval SDIO clock source frequency
 */
static rt_uint32_t _sdio_clock_get(CM_SDIOC_TypeDef *SDIOCx)
{
    rt_uint32_t clk;

    (void)SDIOCx;
#if defined (HC32F4A0)
    clk = CLK_GetBusClockFreq(CLK_BUS_PCLK1);
#elif defined (HC32F460)
    clk = CLK_GetBusClockFreq(CLK_BUS_EXCLK);
#endif

    return clk;
}

/**
 * @brief  Initialize DMA for SDIO.
 * @param  [in] config                  Pointer to hc32_sdio_config structure
 * @retval None
 */
static void _sdio_dma_init(struct hc32_sdio_config *config)
{
    stc_dma_init_t stcDmaInit;

    /* Enable DMA and AOS clock */
    FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_AOS, ENABLE);
    FCG_Fcg0PeriphClockCmd(config->dma_rx.clock, ENABLE);
    FCG_Fcg0PeriphClockCmd(config->dma_tx.clock, ENABLE);

    /* Initialize DMA config structure */
    (void)DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32BlockSize = 512UL;
    stcDmaInit.u32DataWidth = DMA_DATAWIDTH_32BIT;

    /* Configure DMA_RX Transfer */
    stcDmaInit.u32SrcAddr = (uint32_t)(&config->instance->BUF0);
    stcDmaInit.u32DestAddr = 0UL;
    stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_FIX;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_INC;
    if (LL_OK != DMA_Init(config->dma_rx.Instance, config->dma_rx.channel, &stcDmaInit))
    {
        LOG_E("DMA_RX initialization fail");
    }
    AOS_SetTriggerEventSrc(config->dma_rx.trigger_select, config->dma_rx.trigger_event);

    /* Configure DMA_TX Transfer */
    stcDmaInit.u32SrcAddr = 0UL;
    stcDmaInit.u32DestAddr = (uint32_t)(&config->instance->BUF0);
    stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_INC;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_FIX;
    if (LL_OK != DMA_Init(config->dma_tx.Instance, config->dma_tx.channel, &stcDmaInit))
    {
        LOG_E("DMA_TX initialization fail");
    }
    AOS_SetTriggerEventSrc(config->dma_tx.trigger_select, config->dma_tx.trigger_event);

    /* Enable DMA */
    DMA_Cmd(config->dma_rx.Instance, ENABLE);
    DMA_Cmd(config->dma_tx.Instance, ENABLE);
}

/**
 * @brief  Configure DMA for SDIO receiving.
 * @param  [in] instance                Pointer to DMA instance register base
 * @param  [in] ch                      DMA channel
 * @param  [in] pkg                     Pointer to sdio_pkg structure
 * @retval RT_EOK
 */
static rt_err_t _sdio_dma_rxconfig(CM_DMA_TypeDef *instance, rt_uint8_t ch, struct sdio_pkg *pkg)
{
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;

    DMA_ClearTransCompleteStatus(instance, (DMA_INTSTAT1_BTC_0 | DMA_INTSTAT1_TC_0) << ch);
    DMA_SetDestAddr(instance, ch, (rt_uint32_t)pkg->buf);
    DMA_SetBlockSize(instance, ch, (rt_uint16_t)(data->blksize >> 2));
    DMA_SetTransCount(instance, ch, (rt_uint16_t)data->blks);
    return RT_EOK;
}

/**
 * @brief  Configure DMA for SDIO transmitting.
 * @param  [in] instance                Pointer to DMA instance register base
 * @param  [in] ch                      DMA channel
 * @param  [in] pkg                     Pointer to sdio_pkg structure
 * @retval RT_EOK
 */
static rt_err_t _sdio_dma_txconfig(CM_DMA_TypeDef *instance, rt_uint8_t ch, struct sdio_pkg *pkg)
{
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;

    DMA_ClearTransCompleteStatus(instance, (DMA_INTSTAT1_BTC_0 | DMA_INTSTAT1_TC_0) << ch);
    DMA_SetSrcAddr(instance, ch, (rt_uint32_t)pkg->buf);
    DMA_SetBlockSize(instance, ch, (rt_uint16_t)(data->blksize >> 2));
    DMA_SetTransCount(instance, ch, (rt_uint16_t)data->blks);
    return RT_EOK;
}

/**
  * @brief  This function interrupt process function.
  * @param  [in] host                   Pointer to rt_mmcsd_host structure
  * @retval None
  */
static void _sdio_irq_process(struct rt_mmcsd_host *host)
{
    int complete = 0;
    struct rthw_sdio *sdio = host->private_data;
    CM_SDIOC_TypeDef *instance = sdio->config->instance;
    rt_uint32_t norint_status = (rt_uint32_t)instance->NORINTST;
    rt_uint32_t errint_status = (rt_uint32_t)instance->ERRINTST;
    rt_uint32_t status = (errint_status << 16) | norint_status;

    LOG_D("[%s] sta=0x%08X, cmd %d, arg=0x%08X", __func__, status, sdio->pkg->cmd->cmd_code, sdio->pkg->cmd->arg);

    if (norint_status & (SDIOC_INT_FLAG_CRM | SDIOC_INT_FLAG_CIST))
    {
        SDIOC_ClearIntStatus(instance, SDIOC_INT_FLAG_CLR_ALL);

        /* ready to change */
        mmcsd_change(host);

        LOG_D("[%s] card insert or remove", __func__);
        complete = 1;
    }
    else
    {
        if (norint_status & SDIOC_INT_FLAG_EI)
        {
            SDIOC_ClearIntStatus(instance, SDIOC_INT_FLAG_CLR_ALL);
            complete = 1;

            LOG_D("[%s] error", __func__);
        }
        else
        {
            if (norint_status & SDIOC_INT_FLAG_CC)
            {
                SDIOC_ClearIntStatus(instance, SDIOC_INT_FLAG_CC);
                if (sdio->pkg != RT_NULL)
                {
                    if ((!sdio->pkg->cmd->data) && (resp_type(sdio->pkg->cmd) != RESP_R1B))
                    {
                        complete = 1;
                    }
                }
            }

            if (norint_status & SDIOC_INT_FLAG_TC)
            {
                SDIOC_ClearIntStatus(instance, SDIOC_INT_FLAG_TC);
                complete = 1;
            }
        }
    }

    if (norint_status & SDIOC_INT_FLAG_CINT)
    {
        SDIOC_ClearIntStatus(instance, SDIOC_INT_FLAG_CINT);
        sdio_irq_wakeup(host);
    }

    if (complete)
    {
        rt_event_send(&sdio->event, status);
        LOG_D("[%s] complete", __func__);
    }
}

#ifdef BSP_USING_SDIO1
/**
 * @brief  SDIOC1 irq handler.
 * @param  None
 * @retval None
 */
static void _sdio1_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* process all SDIO interrupt sources */
    _sdio_irq_process(_sdio_host[0]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_SDIO2
/**
 * @brief  SDIOC2 irq handler.
 * @param  None
 * @retval None
 */
static void _sdio2_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* process all SDIO interrupt sources */
    _sdio_irq_process(_sdio_host[1]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

/**
 * @brief  verify bus clock frequency.
 * @param  [in] config                  Pointer to hc32_sdio_config structure
 * @retval RT_EOK                       pass to verify
 *         -RT_ERROR                    fail to verify
 */
static rt_err_t _sdio_verify_bus_clock_frequency(struct hc32_sdio_config *config)
{
    rt_err_t ret = RT_EOK;

#if defined (HC32F4A0)
    rt_uint32_t pclk1;
    rt_uint32_t exlck;

    (void)config;
    /* ensure bus frequency condition: EXCLK >= PCLK1 */
    pclk1 = CLK_GetBusClockFreq(CLK_BUS_PCLK1);
    exlck = CLK_GetBusClockFreq(CLK_BUS_EXCLK);
    if (exlck < pclk1)
    {
        LOG_E("bus frequency error: EXCLK < PCLK1. Please meet the bus frequency condition: EXCLK >= PCLK1");
        ret = -RT_ERROR;
    }
#endif

    return ret;
}

/**
 * @brief  Enable SDIO clock.
 * @param  [in] config                  Pointer to hc32_sdio_config structure
 * @retval RT_EOK                       pass to enable SDIO clock
 *         -RT_ERROR                    fail to enable SDIO clock
 */
static rt_err_t _sdio_clock_enable(struct hc32_sdio_config *config)
{
    /* verify bus clock frequency */
    if (_sdio_verify_bus_clock_frequency(config) != RT_EOK)
    {
        LOG_E("[%s] fail to verify bus clock frequency", __func__);
        return -RT_ERROR;
    }

    FCG_Fcg1PeriphClockCmd(config->clock, ENABLE);
    return RT_EOK;
}

/**
 * @brief  Create mmcsd host.
 * @param  [in] config                  Pointer to a @ref hc32_sdio_config structure
 * @param  [in] cache_buf               Pointer to cache buffer
 * @param  [in] sdio_des                Pointer to a @ref hc32_sdio_des structure
 * @retval rt_mmcsd_host
 */
static struct rt_mmcsd_host *_sdio_host_create(struct hc32_sdio_config *config,
        uint8_t *cache_buf,
        const struct hc32_sdio_des *sdio_des)
{
    struct rt_mmcsd_host *host;
    struct rthw_sdio *sdio = RT_NULL;

    if ((config == RT_NULL) || (cache_buf == RT_NULL) || \
            (sdio_des == RT_NULL) || (sdio_des->txconfig == RT_NULL) || (sdio_des->rxconfig == RT_NULL))
    {
        LOG_E("function arguments error: %s %s %s %s %s",
              (config == RT_NULL ? "config is NULL" : ""),
              (cache_buf == RT_NULL ? "cache_buf is NULL" : ""),
              (sdio_des == RT_NULL ? "sdio_des is NULL" : ""),
              (sdio_des ? (sdio_des->txconfig ? "txconfig is NULL" : "") : ""),
              (sdio_des ? (sdio_des->rxconfig ? "rxconfig is NULL" : "") : "")
             );
        return RT_NULL;
    }

    /* malloc rthw_sdio */
    sdio = rt_malloc(sizeof(struct rthw_sdio));
    if (sdio == RT_NULL)
    {
        LOG_E("malloc rthw_sdio fail");
        return RT_NULL;
    }
    rt_memset(sdio, 0, sizeof(struct rthw_sdio));

    /* malloc mmcsd_alloc_host */
    host = mmcsd_alloc_host();
    if (host == RT_NULL)
    {
        LOG_E("mmcsd_alloc_host fail");
        rt_free(sdio);
        return RT_NULL;
    }

    rt_memcpy(&sdio->des, sdio_des, sizeof(struct hc32_sdio_des));

    rt_event_init(&sdio->event, "sdio", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&sdio->mutex, "sdio", RT_IPC_FLAG_FIFO);

    /* set host default attributes */
    host->ops = &_mmcsd_host_ops;
    host->freq_min = 400 * 1000;
    host->freq_max = SDIO_MAX_FREQ;
    host->valid_ocr = VDD_26_27 | VDD_27_28 | VDD_28_29 | VDD_29_30 | VDD_30_31 | VDD_31_32 | VDD_32_33 | VDD_33_34;/* The voltage range supported is 2.6v-3.4v */
    host->valid_ocr = VDD_32_33 | VDD_33_34;
#ifndef SDIO_USING_1_BIT
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ;
#else
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ;
#endif
    host->max_seg_size = SDIO_BUFF_SIZE;
    host->max_dma_segs = 1;
    host->max_blk_size = 512;
    host->max_blk_count = (SDIO_BUFF_SIZE / host->max_blk_size);

    /* link up host, config, cache_buf and sdio */
    sdio->host = host;
    sdio->config = config;
    sdio->cache_buf = cache_buf;
    host->private_data = sdio;

    /* enable interrupt */
    _sdio_update_irq(host, 1);

    /* ready to change */
    mmcsd_change(host);

    return host;
}

int rt_hw_sdio_init(void)
{
    struct rt_mmcsd_host *host;
    struct hc32_sdio_config *sdio_config;
    rt_size_t obj_num = sizeof(_sdio_config) / sizeof(struct hc32_sdio_config);

    const struct hc32_sdio_des sdio_des =
    {
        .clk_get  = _sdio_clock_get,
        .rxconfig = _sdio_dma_rxconfig,
        .txconfig = _sdio_dma_txconfig,
    };

    for (rt_size_t i = 0; i < obj_num; i++)
    {
        sdio_config = &_sdio_config[i];

        if (_sdio_clock_enable(sdio_config) != RT_EOK)
        {
            LOG_E("clock enable fail");
            return -1;
        }

        host = _sdio_host_create(sdio_config, _sdio_cache_buf[i], &sdio_des);
        if (host == RT_NULL)
        {
            LOG_E("host create fail");
            return -1;
        }
        else
        {
            /* link host */
            _sdio_host[i] = host;

            /* init board pin */
            rt_hw_board_sdio_init(sdio_config->instance);

            /* init DMA */
            _sdio_dma_init(sdio_config);

            /* register the irq handler */
            hc32_install_irq_handler(&sdio_config->irq_config, _sdio_irq_handler[i], RT_TRUE);
        }
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

#endif /* BSP_USING_SDIO */
#endif /* RT_USING_SDIO */
