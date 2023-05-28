/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author          Notes
 * 2023-05-28   flyingcys       the first version
 */
#include <rtdevice.h>
#include "board.h"

#ifdef RT_USING_DFS

#define LOG_TAG "drv.sdh"
#ifdef BSP_DRIVER_DEBUG
#define DBG_LEVEL   DBG_LOG
#else
#define DBG_LEVEL   DBG_INFO
#endif
#include <rtdbg.h>

#include <drivers/mmcsd_core.h>
#include <drivers/sdio.h>
#include "drv_sdh.h"

#if defined(BL808)
#include "bl808_common.h"
#include "bl808_glb.h"
#include "bl808_sdh.h"
#elif defined(BL606P)
#include "bl606p_common.h"
#include "bl606p_glb.h"
#include "bl606p_sdh.h"
#elif defined(BL616)
#include "bl616_common.h"
#include "bl616_glb.h"
#include "bl616_sdh.h"
#elif defined(BL628)
#include "bl628_common.h"
#include "bl628_glb.h"
#include "bl628_smih.h"
#endif

#include "bflb_mtimer.h"
#include "bflb_l1c.h"

#define SDIO_BUFF_SIZE                         4096
static uint8_t sdh_buffer[SDIO_BUFF_SIZE];

#define SDIO_CMDTIMEOUT_MS   (2000)

static uint32_t sdhClockInit = 100ul;
static uint32_t sdhClockSrc = 100ul;

static SDH_Cfg_Type SDH_Cfg_Type_Instance;
static SDH_DMA_Cfg_Type SDH_DMA_Cfg_TypeInstance;
/*causion: ADMA related variables must on OCRAM or shared ram*/
static __attribute__((aligned(32), section(".noncacheable"))) SDH_ADMA2_Desc_Type adma2Entries[16];

typedef enum {
    SD_OK = 0,
    SD_CMD_ERROR,
    SD_DataCfg_ERROR,
    SD_WAITING,
} SD_Error;

#ifdef BSP_USING_BL808

static void sdh_clock_init(void)
{
    PERIPHERAL_CLOCK_SDH_ENABLE();
    uint32_t tmp_val;
    tmp_val = BL_RD_REG(PDS_BASE, PDS_CTL5);
    uint32_t tmp_val2 = BL_GET_REG_BITS_VAL(tmp_val, PDS_CR_PDS_GPIO_KEEP_EN);
    tmp_val2 &= ~(1 << 0);
    tmp_val = BL_SET_REG_BITS_VAL(tmp_val, PDS_CR_PDS_GPIO_KEEP_EN, tmp_val2);
    BL_WR_REG(PDS_BASE, PDS_CTL5, tmp_val);
    GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_SDH);
}

static void sdh_gpio_init(void)
{
    struct bflb_device_s *gpio;

    gpio = bflb_device_get_by_name("gpio");
    bflb_gpio_init(gpio, GPIO_PIN_0, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_1, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_2, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_3, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_4, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_5, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
}

#elif defined(BSP_USING_BL61X)

static void sdh_clock_init(void)
{
    PERIPHERAL_CLOCK_SDH_ENABLE();
    GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_EXT_SDH);
}

static void sdh_gpio_init(void)
{
    struct bflb_device_s *gpio;

    gpio = bflb_device_get_by_name("gpio");
    bflb_gpio_init(gpio, GPIO_PIN_10, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_11, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_12, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_13, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_14, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    bflb_gpio_init(gpio, GPIO_PIN_15, GPIO_FUNC_SDH | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
}
#else
#error "The Current Chip Does Not Support SDH!"
#endif

static void sdh_set_bus_width(SDH_Data_Bus_Width_Type width)
{
    SDH_Cfg_Type_Instance.vlot18Enable = DISABLE;
    SDH_Cfg_Type_Instance.highSpeed = ENABLE;
    SDH_Cfg_Type_Instance.dataWidth = width;
    SDH_Cfg_Type_Instance.volt = SDH_VOLTAGE_3P3V;
    SDH_Cfg_Type_Instance.srcClock = sdhClockSrc;
    SDH_Cfg_Type_Instance.busClock = sdhClockInit;
    SDH_Ctrl_Init(&SDH_Cfg_Type_Instance);
}

static void sdio_host_init(void)
{
    GLB_Set_SDH_CLK(ENABLE, GLB_SDH_CLK_WIFIPLL_96M, 7);

    /* initialise SDH controller*/
    SDH_Cfg_Type_Instance.vlot18Enable = DISABLE;
    SDH_Cfg_Type_Instance.highSpeed = ENABLE;
    SDH_Cfg_Type_Instance.dataWidth = SDH_DATA_BUS_WIDTH_1BIT;
    SDH_Cfg_Type_Instance.volt = SDH_VOLTAGE_3P3V;
    SDH_Cfg_Type_Instance.srcClock = sdhClockSrc;
    SDH_Cfg_Type_Instance.busClock = sdhClockInit;
    SDH_Ctrl_Init(&SDH_Cfg_Type_Instance);

    /*setup timeout counter*/
    SDH_Set_Timeout(0x0e);
}

static SDH_Resp_Type sdio_host_get_resp_type(struct rt_mmcsd_cmd *cmd)
{
    SDH_Resp_Type respType;

    switch (resp_type(cmd))
    {
        case RESP_NONE:
            respType = SDH_RESP_NONE;
            break;

        case RESP_R1:
            respType = SDH_RESP_R1;
            break;

        case RESP_R1B:
            respType = SDH_RESP_R1B;
            break;

        case RESP_R2:
            respType = SDH_RESP_R2;
            break;

        case RESP_R3:
            respType = SDH_RESP_R3;
            break;

        case RESP_R4:
            respType = SDH_RESP_R4;
            break;

        case RESP_R5:
            respType = SDH_RESP_R5;
            break;

        case RESP_R6:
            respType = SDH_RESP_R6;
            break;

        case RESP_R7:
            respType = SDH_RESP_R7;
            break;

        default:
            respType = SDH_RESP_NONE;
            break;
    }

    return respType;
}

static rt_err_t sdio_host_send_command(SDH_CMD_Cfg_Type *SDH_CMD_Cfg_TypeInstance)
{
    SD_Error sd_status;
    uint32_t time_node;

    SDH_ClearIntStatus(SDH_INT_CMD_COMPLETED | SDH_INT_CMD_ERRORS);

    SDH_SendCommand(SDH_CMD_Cfg_TypeInstance);

    time_node = (uint32_t)bflb_mtimer_get_time_ms();

    uint32_t intFlag;
    while (1)
    {
        intFlag = SDH_GetIntStatus();
        if (intFlag & SDH_INT_CMD_ERRORS)
        {
            sd_status = SD_CMD_ERROR;
            break;
        }
        else if (intFlag & SDH_INT_CMD_COMPLETED)
        {
            sd_status = SD_OK;
            break;
        }
        else if ((uint32_t)bflb_mtimer_get_time_ms() - time_node > SDIO_CMDTIMEOUT_MS)
        {
            LOG_D("SDH send CMD%ld timeout: %ld ms", SDH_CMD_Cfg_TypeInstance->index, (uint32_t)bflb_mtimer_get_time_ms() - time_node);
            return -RT_ETIMEOUT;
        }
        BL_DRV_DUMMY;
        BL_DRV_DUMMY;
    }
    SDH_ClearIntStatus(intFlag & (SDH_INT_CMD_ERRORS | SDH_INT_CMD_COMPLETED));

    if (sd_status != SD_OK)
    {
        LOG_E("SDH send CMD%ld error", SDH_CMD_Cfg_TypeInstance->index);
        return -RT_ERROR;
    }
    else
    {
        LOG_D("SDH send CMD%ld success", SDH_CMD_Cfg_TypeInstance->index);

        SDH_CMD_Cfg_TypeInstance->response[0] = BL_RD_REG(SDH_BASE, SDH_SD_RESP_0);
        SDH_CMD_Cfg_TypeInstance->response[1] = BL_RD_REG(SDH_BASE, SDH_SD_RESP_2);
        SDH_CMD_Cfg_TypeInstance->response[2] = BL_RD_REG(SDH_BASE, SDH_SD_RESP_4);
        SDH_CMD_Cfg_TypeInstance->response[3] = BL_RD_REG(SDH_BASE, SDH_SD_RESP_6);
    }

    return RT_EOK;
}

static rt_err_t SDH_CardTransferNonBlocking(SDH_DMA_Cfg_Type *dmaCfg, SDH_Trans_Cfg_Type *transfer)
{
    rt_err_t ret = RT_EOK;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;

    stat = SDH_TransferNonBlocking(dmaCfg, transfer);
    if (stat != SDH_STAT_SUCCESS) {
        LOG_E("SDH_TransferNonBlocking error:%d", stat);
        return -RT_ERROR;
    }

    /* Flush ADMA2-descriptor-table to RAM, Otherwise ADMA2 will fail */
    bflb_l1c_dcache_clean_range((void *)(dmaCfg->admaEntries), dmaCfg->maxEntries * sizeof(SDH_ADMA2_Desc_Type));

    ret = sdio_host_send_command(transfer->cmdCfg);
    if (ret != RT_EOK)
    {
        LOG_E("sdio_host_send_command error:%d", transfer->cmdCfg->index);
        return ret;
    }

    rt_uint32_t intFlag;
    SD_Error sd_status;
    rt_uint32_t time_node;

    time_node = (uint32_t)bflb_mtimer_get_time_ms();
    while (1)
    {
        intFlag = SDH_GetIntStatus();
        if (intFlag & SDH_INT_DATA_ERRORS || intFlag & SDH_INT_DMA_ERROR || intFlag & SDH_INT_AUTO_CMD12_ERROR)
        {
            sd_status = SD_CMD_ERROR;
            break;

        }
        else if (intFlag & SDH_INT_DATA_COMPLETED)
        {
            sd_status = SD_OK;
            break;

        }
        else if ((uint32_t)bflb_mtimer_get_time_ms() - time_node > SDIO_CMDTIMEOUT_MS)
        {
            LOG_E("SDH read data timeout: %ld ms", (uint32_t)bflb_mtimer_get_time_ms() - time_node);
            return -RT_ETIMEOUT;
        }
        BL_DRV_DUMMY;
        BL_DRV_DUMMY;
    }
    SDH_ClearIntStatus(intFlag);

    if (sd_status != SD_OK)
    {
        LOG_E("sd_status :%d", sd_status);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t rt_hw_sdh_data_transfer(struct rt_mmcsd_host *host, struct rt_mmcsd_cmd *cmd, struct rt_mmcsd_data *data)
{
    rt_err_t ret = RT_EOK;
    SDH_Data_Cfg_Type SDH_Data_Cfg_TypeInstance;
    SDH_CMD_Cfg_Type SDH_CMD_Cfg_TypeInstance = {0};
    SDH_Trans_Cfg_Type SDH_Trans_Cfg_TypeInstance = { &SDH_Data_Cfg_TypeInstance, &SDH_CMD_Cfg_TypeInstance };

#if defined(BL808) || defined(BL606P)
    /* BL808/BL606 supports only 8-byte aligned addresses */
    if ((uintptr_t)data->buf % 8 != 0)
    {
        return -RT_EINVAL;
    }
#endif

    SDH_CMD_Cfg_TypeInstance.index = cmd->cmd_code;
    SDH_CMD_Cfg_TypeInstance.argument = cmd->arg;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = sdio_host_get_resp_type(cmd);
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;

    /*set data parameter */
    SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
    SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
    SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
    SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
    SDH_Data_Cfg_TypeInstance.blockSize = data->blksize;
    SDH_Data_Cfg_TypeInstance.blockCount = data->blks;

    if (cmd->cmd_code == READ_SINGLE_BLOCK || cmd->cmd_code == READ_MULTIPLE_BLOCK)
    {
        SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
        SDH_Data_Cfg_TypeInstance.rxData = (rt_uint32_t *)sdh_buffer;
        // SDH_Data_Cfg_TypeInstance.rxData = (rt_uint32_t *)data->buf;
        SDH_Data_Cfg_TypeInstance.txDataLen = 0;
        SDH_Data_Cfg_TypeInstance.txData = NULL;
    }
    else
    {
        rt_memcpy((void *)sdh_buffer, (void *)data->buf, data->blksize);
        SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
        SDH_Data_Cfg_TypeInstance.rxData = NULL;
        SDH_Data_Cfg_TypeInstance.txDataLen = 0;
        // SDH_Data_Cfg_TypeInstance.txData = (rt_uint32_t *)data->buf;
        SDH_Data_Cfg_TypeInstance.txData = (rt_uint32_t *)sdh_buffer;
    }

    /*set parameters for SDH_DMA_Cfg_TypeInstance*/
    SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
    SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_128_BYTES;

    if (cmd->cmd_code == READ_SINGLE_BLOCK || cmd->cmd_code == READ_MULTIPLE_BLOCK)
    {
            SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_BURST_SIZE_128_BYTES;
    }
    else
        SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;

    SDH_DMA_Cfg_TypeInstance.admaEntries = (rt_uint32_t *)adma2Entries;
    SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries) / sizeof(adma2Entries[0]);

    if (data->flags & DATA_DIR_WRITE)
    {
        bflb_l1c_dcache_clean_range((void *)(data->buf), data->blksize * data->blks);
    }

    ret = SDH_CardTransferNonBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);
    if (ret != RT_EOK)
    {
        LOG_E("SDH_CardTransferNonBlocking error:%d", ret);
        return ret;
    }

    if (resp_type(cmd) != RESP_NONE)
    {
        cmd->resp[0] = SDH_CMD_Cfg_TypeInstance.response[0];
        LOG_D("resp[0]: %08x", cmd->resp[0]);
    }

    if (data->flags & DATA_DIR_READ)
    {
        bflb_l1c_dcache_invalidate_range((void *)(sdh_buffer), data->blksize * data->blks);
        rt_memcpy(data->buf, sdh_buffer, data->blks * data->blksize);
    }

    return RT_EOK;
}

static rt_err_t rt_hw_sdh_cmd_transfer(struct rt_mmcsd_host *host, struct rt_mmcsd_cmd *cmd, struct rt_mmcsd_data *data)
{
    rt_err_t ret = RT_EOK;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    SDH_Data_Cfg_Type SDH_Data_Cfg_TypeInstance;
    SDH_CMD_Cfg_Type SDH_CMD_Cfg_TypeInstance = {0};

    if (data != RT_NULL)
    {
        SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
        SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
        SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
        SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
        SDH_Data_Cfg_TypeInstance.blockSize = data->blksize;
        SDH_Data_Cfg_TypeInstance.blockCount = data->blks;
        SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
        SDH_Data_Cfg_TypeInstance.rxData = (rt_uint32_t *)data->buf;
        SDH_Data_Cfg_TypeInstance.txDataLen = 0;
        SDH_Data_Cfg_TypeInstance.txData = NULL;

        /* Config the data transfer parameter */
        stat = SDH_ConfigDataTranfer(&SDH_Data_Cfg_TypeInstance);
        if (stat != SDH_STAT_SUCCESS)
        {
            return -RT_ERROR;
        }

        SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;
    }
    else
        SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    SDH_CMD_Cfg_TypeInstance.index = cmd->cmd_code;
    SDH_CMD_Cfg_TypeInstance.argument = cmd->arg;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = sdio_host_get_resp_type(cmd);

    ret = sdio_host_send_command(&SDH_CMD_Cfg_TypeInstance);
    if (ret != RT_EOK)
    {
        memset(cmd->resp, 0, sizeof(cmd->resp));
        return ret;
    }

    if (resp_type(cmd) != RESP_NONE)
    {
        if (resp_type(cmd) == RESP_R2)
        {
            cmd->resp[0] = ((SDH_CMD_Cfg_TypeInstance.response[3] << 8) & ~0xff);
            cmd->resp[0] |= ((SDH_CMD_Cfg_TypeInstance.response[2] >> 24) & 0xff);
            cmd->resp[1] = ((SDH_CMD_Cfg_TypeInstance.response[2] << 8) & ~0xff);
            cmd->resp[1] |= ((SDH_CMD_Cfg_TypeInstance.response[1] >> 24) & 0xff);
            cmd->resp[2] = ((SDH_CMD_Cfg_TypeInstance.response[1] << 8) & ~0xff);
            cmd->resp[2] |= ((SDH_CMD_Cfg_TypeInstance.response[0] >> 24) & 0xff);
            cmd->resp[3] = ((SDH_CMD_Cfg_TypeInstance.response[3] << 8) & ~0xff);

            LOG_D("resp[0]: %08x %08x %08x %08x", cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
        }
        else
        {
            cmd->resp[0] = SDH_CMD_Cfg_TypeInstance.response[0];
            LOG_D("resp[0]: %08x", cmd->resp[0]);
        }
    }

    if (data != RT_NULL)
    {
        SD_Error sd_status;
        uint32_t time_node;
        time_node = (uint32_t)bflb_mtimer_get_time_ms();
        uint32_t intFlag;
        while (1)
        {
            intFlag = SDH_GetIntStatus();
            if (intFlag & SDH_INT_DATA_ERRORS || intFlag & SDH_INT_DMA_ERROR)
            {
                sd_status = SD_DataCfg_ERROR;
                break;

            }
            else if (intFlag & SDH_INT_BUFFER_READ_READY || intFlag & SDH_INT_DATA_COMPLETED)
            {
                sd_status = SD_OK;
                break;

            }
            else if ((uint32_t)bflb_mtimer_get_time_ms() - time_node > SDIO_CMDTIMEOUT_MS)
            {
                LOG_E("SDH get csr data timeout: %ld ms", (uint32_t)bflb_mtimer_get_time_ms() - time_node);
                return -RT_ETIMEOUT;
            }
            BL_DRV_DUMMY;
            BL_DRV_DUMMY;
        }
        SDH_ClearIntStatus(intFlag);

        if (sd_status != SD_OK)
        {
            return -RT_ERROR;
        }

        if (data->flags & DATA_DIR_READ)
        {
            rt_uint32_t ret = SDH_ReadDataPort(&SDH_Data_Cfg_TypeInstance);
            if (ret <= 0)
                return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static void rt_hw_sdh_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(req != RT_NULL);

    if (req->cmd != RT_NULL)
    {
        struct rt_mmcsd_cmd *cmd = req->cmd;
        struct rt_mmcsd_data *data = req->data;

        LOG_D("[%s%s%s%s%s]REQ: CMD:%d ARG:0x%08x RES:%s%s%s%s%s%s%s%s%s rw:%c addr:%08x, blks:%d, blksize:%d datalen:%d",
                (host->card == RT_NULL) ? "Unknown" : "",
                (host->card) && (host->card->card_type == CARD_TYPE_MMC) ? "MMC" : "",
                (host->card) && (host->card->card_type == CARD_TYPE_SD) ? "SD" : "",
                (host->card) && (host->card->card_type == CARD_TYPE_SDIO) ? "SDIO" : "",
                (host->card) && (host->card->card_type == CARD_TYPE_SDIO_COMBO) ? "SDIO_COMBO" : "",
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
                data ? data->buf : 0,
                data ? data->blks : 0,
                data ? data->blksize : 0,
                data ? data->blks * data->blksize : 0);

        if (cmd->cmd_code == READ_SINGLE_BLOCK || cmd->cmd_code == READ_MULTIPLE_BLOCK || \
            cmd->cmd_code == WRITE_BLOCK || cmd->cmd_code == WRITE_MULTIPLE_BLOCK)
        {
            cmd->err = rt_hw_sdh_data_transfer(host, cmd, data);
        }
        else
        {
            cmd->err = rt_hw_sdh_cmd_transfer(host, cmd, data);
        }
    }

    if (req->stop != RT_NULL)
    {
        struct rt_mmcsd_cmd *stop = req->stop;

        stop->err = rt_hw_sdh_cmd_transfer(host, stop, RT_NULL);
    }

    mmcsd_req_complete(host);
}

static void rt_hw_sdh_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    rt_uint32_t clk;

    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(io_cfg != RT_NULL);

    clk = io_cfg->clock;

    LOG_D("clk:%d width:%s%s%s power:%s%s%s",
          clk,
          io_cfg->bus_width == MMCSD_BUS_WIDTH_8 ? "8" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_4 ? "4" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_1 ? "1" : "",
          io_cfg->power_mode == MMCSD_POWER_OFF ? "OFF" : "",
          io_cfg->power_mode == MMCSD_POWER_UP ? "UP" : "",
          io_cfg->power_mode == MMCSD_POWER_ON ? "ON" : ""
         );

    /* clock */
    if (clk > host->freq_max)
        clk = host->freq_max;

    if (clk < host->freq_min)
        clk = host->freq_min;

    /* power mode */
    switch (io_cfg->power_mode)
    {
        case MMCSD_POWER_UP:
            break;

        case MMCSD_POWER_ON:
            SDH_Powon();
            break;

        case MMCSD_POWER_OFF:
            break;

        default:
            break;
    }

    /* bus width */
    switch (io_cfg->bus_width)
    {
        case MMCSD_BUS_WIDTH_1:
            sdh_set_bus_width(SDH_DATA_BUS_WIDTH_1BIT);
            break;

        case MMCSD_BUS_WIDTH_4:
            sdh_set_bus_width(SDH_DATA_BUS_WIDTH_4BITS);
            break;

        case MMCSD_BUS_WIDTH_8:
            sdh_set_bus_width(SDH_DATA_BUS_WIDTH_8BITS);
            break;

        default:
            LOG_E("nonsupport bus width: %d", io_cfg->bus_width);
            break;
    }
}

static const struct rt_mmcsd_host_ops ops =
{
    rt_hw_sdh_request,
    rt_hw_sdh_iocfg,
    RT_NULL,
    RT_NULL,
};

int rt_hw_sdh_init(void)
{
    struct rt_mmcsd_host *host;

    host = mmcsd_alloc_host();
    RT_ASSERT(host != RT_NULL);

    sdh_clock_init();
    sdh_gpio_init();

    /* reset SDH controller*/
    SDH_Reset();

    sdio_host_init();

    /* set host default attributes */
    host->ops = &ops;
    host->freq_min = 40 * 1000;
    host->freq_max = 50 * 1000 * 1000;
    host->valid_ocr = VDD_31_32 | VDD_32_33 | VDD_33_34;
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED | MMCSD_BUSWIDTH_4;
    host->max_seg_size = SDIO_BUFF_SIZE;
    host->max_dma_segs = 1;
    host->max_blk_size = 512;
    host->max_blk_count = 512;

    /* link up host and sdio */
    host->private_data = host;

    mmcsd_change(host);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_sdh_init);

#endif /* RT_USING_DFS */
