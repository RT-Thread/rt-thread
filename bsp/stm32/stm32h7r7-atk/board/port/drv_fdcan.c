/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-24     heyuan       the first version
 * 2020-08-17     malongwei    Fix something
 */

#include "board.h"
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_CAN

#if defined(BSP_USING_FDCAN1) || defined(BSP_USING_FDCAN2)

#include "drv_fdcan.h"

#define LOG_TAG    "drv_can"
#define DBG_LVL LOG_LVL_DBG
#include <ulog.h>

#ifdef BSP_USING_FDCAN1
static _stm32_fdcan_t st_DrvCan1 = {0};
#endif

#ifdef BSP_USING_FDCAN2
static _stm32_fdcan_t st_DrvCan2 = {0};
#endif


/*
 * note:After frequency division, the working clock of the fdcan is 100mhz
 */
static const _stm32_fdcan_NTconfig_t st_CanNTconfig[]=
/*baud brp sjw tseg1 tseg2*/
{
    {BSP_FDCAN_BAUD_DATA_5M,   1,8,15,4},  /* Only the data segments of these four can be used */
    {BSP_FDCAN_BAUD_DATA_4M,   1,8,19,5},
    {BSP_FDCAN_BAUD_DATA_2M5,  2,8,15,4},
    {BSP_FDCAN_BAUD_DATA_2M,   2,8,19,5},
    {CAN1MBaud,     5,8,15,4},  /* All of the following are fine. */
    {CAN800kBaud,   1,8,99,25},
    {CAN500kBaud,   10,8,15,4},
    {CAN250kBaud,   10,8,35,4},
    {CAN125kBaud,   20,8,35,4},
    {CAN100kBaud,   20,8,44,5},
    {CAN50kBaud,    40,8,44,5},
    {CAN20kBaud,    100,8,44,5},
    {CAN10kBaud,    200,8,44,5}
};

/*
*function name:_inline_get_NTbaud_index
*Inf: Return the index value of the above st_CanNTconfig timing configuration
*     structure array based on the passed-in baud rate size.
*
*#param: Baud rate: Decimal number
*
*#return: Index value If not found, return 0xff
*/
static uint32_t _inline_get_NTbaud_index(uint32_t baud_rate)
{
    uint32_t len, index;

    len = sizeof(st_CanNTconfig) / sizeof(st_CanNTconfig[0]);

    for (index = 0; index < len; index++)
    {
        if (st_CanNTconfig[index].u32NBaudrate == baud_rate)

        return index;
    }

    return 0xff;
}

static void _inline_can_tx_header_init(_stm32_fdcan_t *pCan)
{
      /* Prepare Tx Header */
      pCan->TxHeader.Identifier = 0x000000;
      pCan->TxHeader.IdType = FDCAN_EXTENDED_ID;
      pCan->TxHeader.TxFrameType = FDCAN_DATA_FRAME;
      pCan->TxHeader.DataLength = FDCAN_DLC_BYTES_8;
      pCan->TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
      pCan->TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
      pCan->TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
      pCan->TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
      pCan->TxHeader.MessageMarker = 0;
}


/*
 * note:When the clock is input here, it is pll1q, 600mhz. First, it is divided to 100m. The atk
 *           says the maximum is 125m, but I haven't found it. For now, I believe it
 */
static rt_err_t _inline_can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    _stm32_fdcan_t *pdrv_can;
    rt_uint32_t tmp_u32Index;
    FDCAN_FilterTypeDef canx_rxfilter = {0};

    RT_ASSERT(can);
    RT_ASSERT(cfg);

    pdrv_can = (_stm32_fdcan_t *)can->parent.user_data;

    RT_ASSERT(pdrv_can);
    /* The peripheral clock input is 600MHZ, and after 6 frequency divisions, it becomes 100MHZ */
    pdrv_can->fdcanHandle.Init.ClockDivider = FDCAN_CLOCK_DIV6;

    /* config FrameFormat */
    if (cfg->enable_canfd == BSP_FDCAN_FRAMEFORMAT_CLASSIC)
    {
        pdrv_can->fdcanHandle.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
        pdrv_can->fdcanHandle.Init.AutoRetransmission = DISABLE;
    }else if (cfg->enable_canfd == BSP_FDCAN_FRAMEFORMAT_FD_NO_BRS)
    {
        pdrv_can->fdcanHandle.Init.FrameFormat = FDCAN_FRAME_FD_NO_BRS;
        pdrv_can->fdcanHandle.Init.AutoRetransmission = ENABLE;
    }else if (cfg->enable_canfd == BSP_FDCAN_FRAMEFORMAT_FD_BRS)
    {
        pdrv_can->fdcanHandle.Init.FrameFormat = FDCAN_FRAME_FD_BRS;
        pdrv_can->fdcanHandle.Init.AutoRetransmission = ENABLE;
    }else return -RT_ERROR;

    pdrv_can->fdcanHandle.Init.Mode = FDCAN_MODE_NORMAL;
    pdrv_can->fdcanHandle.Init.TransmitPause = DISABLE;
    pdrv_can->fdcanHandle.Init.ProtocolException = DISABLE;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        pdrv_can->fdcanHandle.Init.Mode = FDCAN_MODE_NORMAL;
        break;
    case RT_CAN_MODE_LISTEN:
        pdrv_can->fdcanHandle.Init.Mode = FDCAN_MODE_BUS_MONITORING;
        break;
    case RT_CAN_MODE_LOOPBACK:
        pdrv_can->fdcanHandle.Init.Mode = FDCAN_MODE_INTERNAL_LOOPBACK;
        break;
    default:
        pdrv_can->fdcanHandle.Init.Mode = FDCAN_MODE_NORMAL;
        break;
    }

    /* Configure the classic CAN or arbitration segment rate */
    tmp_u32Index = _inline_get_NTbaud_index(cfg->baud_rate);

    /* The data segment rate cannot exceed 1M */
    if(tmp_u32Index <= 3 || tmp_u32Index == 0xff)
        return -RT_ERROR;

    pdrv_can->fdcanHandle.Init.NominalPrescaler = st_CanNTconfig[tmp_u32Index].u16Nbrp;
    pdrv_can->fdcanHandle.Init.NominalSyncJumpWidth = st_CanNTconfig[tmp_u32Index].u8Nsjw;
    pdrv_can->fdcanHandle.Init.NominalTimeSeg1 = st_CanNTconfig[tmp_u32Index].u8Ntseg1;
    pdrv_can->fdcanHandle.Init.NominalTimeSeg2 = st_CanNTconfig[tmp_u32Index].u8Ntseg2;

    /* Configure the data segment rate */
    if(cfg->enable_canfd == BSP_FDCAN_FRAMEFORMAT_FD_BRS)
    {
        tmp_u32Index = _inline_get_NTbaud_index(cfg->baud_rate_fd);
        /* The data segment rate cannot be lower than 1M due to the current timing setting issue */
        if(tmp_u32Index > 4 || tmp_u32Index == 0xff)
            return -RT_ERROR;

        pdrv_can->fdcanHandle.Init.DataPrescaler = st_CanNTconfig[tmp_u32Index].u16Nbrp;
        pdrv_can->fdcanHandle.Init.DataSyncJumpWidth = st_CanNTconfig[tmp_u32Index].u8Nsjw;
        pdrv_can->fdcanHandle.Init.DataTimeSeg1 = st_CanNTconfig[tmp_u32Index].u8Ntseg1;
        pdrv_can->fdcanHandle.Init.DataTimeSeg2 = st_CanNTconfig[tmp_u32Index].u8Ntseg2;
    }

    /* Filter */
    pdrv_can->fdcanHandle.Init.StdFiltersNbr = 28;
    pdrv_can->fdcanHandle.Init.ExtFiltersNbr = 8;

    if (HAL_FDCAN_Init(&pdrv_can->fdcanHandle) != HAL_OK)
    {
        return -RT_ERROR;
    }

    /* Install the filter */
#if defined(RT_CAN_USING_HDR)
    HAL_FDCAN_ConfigFilter(&pdrv_can->fdcanHandle , &pdrv_can->FilterConfig);
#else/* If HDR support is not enabled, it will be accepted by default */

    /* Configure the CAN filter */
    canx_rxfilter.IdType = FDCAN_STANDARD_ID;                           
    canx_rxfilter.FilterIndex = 0;                                     
    canx_rxfilter.FilterType = FDCAN_FILTER_MASK;                      
    canx_rxfilter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;               
    canx_rxfilter.FilterID1 = 0x0000;                                   
    canx_rxfilter.FilterID2 = 0x0000;                                   
    /* Filter configuration */
    if (HAL_FDCAN_ConfigFilter(&pdrv_can->fdcanHandle, &canx_rxfilter) != HAL_OK)
    {
        return -RT_ERROR;
    }

    /* Extended ID */
    canx_rxfilter.IdType = FDCAN_EXTENDED_ID;
    if (HAL_FDCAN_ConfigFilter(&pdrv_can->fdcanHandle, &canx_rxfilter) != HAL_OK)
    {
        return -RT_ERROR;
    }
#endif

    if (HAL_FDCAN_ConfigGlobalFilter(&pdrv_can->fdcanHandle, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
    {
        return -RT_ERROR;
    }

    /* Initialize the sending head */
    _inline_can_tx_header_init(pdrv_can);

    /* Start peripheral devices */
    HAL_FDCAN_Start(&pdrv_can->fdcanHandle);
    return RT_EOK;
}

/* There is a temporary problem with HDR, can't use */
#ifdef RT_CAN_USING_HDR
static rt_err_t _inline_can_filter_config(_stm32_fdcan_t *pdrv_can,struct rt_can_filter_config *puser_can_filter_config)
{
    int tmp_i32IndexCount;

    RT_ASSERT(pdrv_can);
    RT_ASSERT(puser_can_filter_config);

    pdrv_can->ext_filter_num = 0;
    pdrv_can->std_filter_num = 0;

    /* get default filter */
    for (tmp_i32IndexCount = 0; tmp_i32IndexCount < puser_can_filter_config->count; tmp_i32IndexCount++)
    {
        if(puser_can_filter_config->items[tmp_i32IndexCount].hdr_bank < 0) continue;

        _FilterIndex = (rt_uint32_t)puser_can_filter_config->items[tmp_i32IndexCount].hdr_bank;

        if(puser_can_filter_config->items[tmp_i32IndexCount].ide == RT_CAN_EXTID)
        {
            pdrv_can->FilterConfig.IdType = FDCAN_EXTENDED_ID;
            if(_FilterIndex > 7) return -RT_ERROR;
        }
        else
        {
            pdrv_can->FilterConfig.IdType = FDCAN_STANDARD_ID;
            if(_FilterIndex > 27) return -RT_ERROR;
        }

        pdrv_can->FilterConfig.FilterIndex = _FilterIndex;
        pdrv_can->FilterConfig.FilterID1 = puser_can_filter_config->items[tmp_i32IndexCount].id;
        pdrv_can->FilterConfig.FilterID2 = puser_can_filter_config->items[tmp_i32IndexCount].mask;

        pdrv_can->FilterConfig.FilterType = FDCAN_FILTER_MASK;
        pdrv_can->FilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
        if(HAL_FDCAN_ConfigFilter(&pdrv_can->fdcanHandle , &pdrv_can->FilterConfig) != HAL_OK)
        {
            return -RT_ERROR;
        }
    }
    return RT_EOK;
}
#endif

static rt_err_t _inline_can_control(struct rt_can_device *can, int cmd, void *arg)
{

    rt_uint32_t argval;
    _stm32_fdcan_t *pdrv_can;
    rt_uint32_t tmp_u32Errcount;
    rt_uint32_t tmp_u32status;

    RT_ASSERT(can != RT_NULL);
    pdrv_can = (_stm32_fdcan_t *)can->parent.user_data;
    RT_ASSERT(pdrv_can != RT_NULL);

    switch (cmd)
    {

    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            HAL_FDCAN_DeactivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_RX_FIFO0_NEW_MESSAGE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            HAL_FDCAN_DeactivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_TX_FIFO_EMPTY);
            HAL_FDCAN_DeactivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_TX_COMPLETE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            HAL_FDCAN_DeactivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_ERROR_WARNING);
            HAL_FDCAN_DeactivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_ERROR_PASSIVE);
            HAL_FDCAN_DeactivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_ERROR_LOGGING_OVERFLOW);
            HAL_FDCAN_DeactivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_BUS_OFF);
            HAL_FDCAN_DeactivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_ARB_PROTOCOL_ERROR);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            HAL_FDCAN_ConfigInterruptLines(&pdrv_can->fdcanHandle, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, FDCAN_INTERRUPT_LINE0);
            HAL_FDCAN_ActivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);

            if(FDCAN1 == pdrv_can->fdcanHandle.Instance)
            {
                HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 0, 1);
                HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
            }
            else
            {
                HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, 0, 1);
                HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
            }

        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            HAL_FDCAN_ConfigInterruptLines(&pdrv_can->fdcanHandle, FDCAN_IT_TX_COMPLETE, FDCAN_INTERRUPT_LINE1);
            HAL_FDCAN_ActivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_TX_COMPLETE, FDCAN_TX_BUFFER0);
            HAL_FDCAN_ActivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_TX_COMPLETE, FDCAN_TX_BUFFER1);
            HAL_FDCAN_ActivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_TX_COMPLETE, FDCAN_TX_BUFFER2);

            if(FDCAN1 == pdrv_can->fdcanHandle.Instance)
            {
                HAL_NVIC_SetPriority(FDCAN1_IT1_IRQn, 0, 2);
                HAL_NVIC_EnableIRQ(FDCAN1_IT1_IRQn);
            }
            else
            {
                HAL_NVIC_SetPriority(FDCAN2_IT1_IRQn, 0, 2);
                HAL_NVIC_EnableIRQ(FDCAN2_IT1_IRQn);
            }
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            HAL_FDCAN_ConfigInterruptLines(&pdrv_can->fdcanHandle, FDCAN_IT_BUS_OFF, FDCAN_INTERRUPT_LINE1);
            HAL_FDCAN_ConfigInterruptLines(&pdrv_can->fdcanHandle, FDCAN_IT_ERROR_WARNING, FDCAN_INTERRUPT_LINE1);
            HAL_FDCAN_ConfigInterruptLines(&pdrv_can->fdcanHandle, FDCAN_IT_ERROR_PASSIVE, FDCAN_INTERRUPT_LINE1);
            HAL_FDCAN_ConfigInterruptLines(&pdrv_can->fdcanHandle, FDCAN_IT_ARB_PROTOCOL_ERROR, FDCAN_INTERRUPT_LINE1);

            HAL_FDCAN_ActivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_BUS_OFF, 0);
            HAL_FDCAN_ActivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_ERROR_WARNING, 0);
            HAL_FDCAN_ActivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_ERROR_PASSIVE, 0);
            HAL_FDCAN_ActivateNotification(&pdrv_can->fdcanHandle,  FDCAN_IT_ARB_PROTOCOL_ERROR, 0);
            if(FDCAN1 == pdrv_can->fdcanHandle.Instance)
            {
                HAL_NVIC_SetPriority(FDCAN1_IT1_IRQn, 0, 2);
                HAL_NVIC_EnableIRQ(FDCAN1_IT1_IRQn);
            }
            else
            {
                HAL_NVIC_SetPriority(FDCAN2_IT1_IRQn, 0, 2);
                HAL_NVIC_EnableIRQ(FDCAN2_IT1_IRQn);
            }
        }
        break;

#ifdef RT_CAN_USING_HDR
    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL == arg)
        {
            /* default filter config */
            HAL_FDCAN_ConfigFilter(&pdrv_can->fdcanHandle , &pdrv_can->FilterConfig);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            _inline_can_filter_config(pdrv_can, filter_cfg);
        }
        break;
#endif

    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
            argval != RT_CAN_MODE_LISTEN &&
            argval != RT_CAN_MODE_LOOPBACK &&
            argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != pdrv_can->device.config.mode)
        {
            pdrv_can->device.config.mode = argval;
            return _inline_can_config(&pdrv_can->device, &pdrv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t ) arg;
        /*just low to 50kbit/s*/
        if (argval != CAN1MBaud &&
            argval != CAN800kBaud &&
            argval != CAN500kBaud &&
            argval != CAN250kBaud &&
            argval != CAN125kBaud &&
            argval != CAN100kBaud &&
            argval != CAN50kBaud  &&
            argval != CAN20kBaud  &&
            argval != CAN10kBaud)
        {
            return -RT_ERROR;
        }
        if (argval != pdrv_can->device.config.baud_rate)
        {
            pdrv_can->device.config.baud_rate = argval;
            return _inline_can_config(&pdrv_can->device, &pdrv_can->device.config);
        }
        break;

    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != pdrv_can->device.config.privmode)
        {
            pdrv_can->device.config.privmode = argval;

            return RT_EOK;
        }
        break;

    case RT_CAN_CMD_GET_STATUS:
        tmp_u32Errcount = pdrv_can->fdcanHandle.Instance->ECR;
        tmp_u32status = pdrv_can->fdcanHandle.Instance->PSR;

        pdrv_can->device.status.rcverrcnt = (tmp_u32Errcount>>8)&0x000000ff;
        pdrv_can->device.status.snderrcnt = (tmp_u32Errcount)&0x000000ff;
        pdrv_can->device.status.lasterrtype = tmp_u32status&0x000000007;

        rt_memcpy(arg, &pdrv_can->device.status, sizeof(pdrv_can->device.status));
        break;

    case BSP_CAN_CMD_SET_BRS_BAUD:
            argval = (rt_uint32_t ) arg;
            /*just low to 50kbit/s*/
            if (argval != BSP_FDCAN_BAUD_DATA_2M &&
                argval != BSP_FDCAN_BAUD_DATA_2M5 &&
                argval != BSP_FDCAN_BAUD_DATA_4M &&
                argval != BSP_FDCAN_BAUD_DATA_5M)
            {
                return -RT_ERROR;
            }
            if (argval != pdrv_can->device.config.baud_rate_fd)
            {
                pdrv_can->device.config.baud_rate_fd = argval;
                return _inline_can_config(&pdrv_can->device, &pdrv_can->device.config);
            }
            break;
    }

    return RT_EOK;
}

static rt_ssize_t _inline_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{

    _stm32_fdcan_t *pdrv_can;
    struct rt_can_msg *pmsg;
    uint32_t tmp_u32DataLen;
    RT_ASSERT(can);
    RT_ASSERT(buf);

    pdrv_can = (_stm32_fdcan_t *)can->parent.user_data;

    RT_ASSERT(pdrv_can);

    pmsg = (struct rt_can_msg *) buf;

    /* Check the parameters */
    tmp_u32DataLen = pmsg->len;
#ifndef RT_CAN_USING_CANFD
    if(pmsg->len > 8)
    {
        tmp_u32DataLen = 8;
    }
#else
    if(pmsg->len > 64)
    {
        tmp_u32DataLen = 64;
    }
#endif
    /* id */
    pdrv_can->TxHeader.Identifier = pmsg->id;

    /* id-type */
    if(pmsg->ide == RT_CAN_EXTID)
    {
        pdrv_can->TxHeader.IdType = FDCAN_EXTENDED_ID;
    }
    else
    {
        pdrv_can->TxHeader.IdType = FDCAN_STANDARD_ID;
    }

    /* tx-frame-type */
    if (pmsg->rtr == RT_CAN_DTR)
    {
        pdrv_can->TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    }
    else
    {
        pdrv_can->TxHeader.TxFrameType = FDCAN_REMOTE_FRAME;
    }

    /* data-length */
    if(tmp_u32DataLen <= 8){
        pdrv_can->TxHeader.DataLength = tmp_u32DataLen;
    }else if (tmp_u32DataLen <= 12) {
        pdrv_can->TxHeader.DataLength = FDCAN_DLC_BYTES_12;
    }else if (tmp_u32DataLen <= 16) {
        pdrv_can->TxHeader.DataLength = FDCAN_DLC_BYTES_16;
    }else if (tmp_u32DataLen <= 20) {
        pdrv_can->TxHeader.DataLength = FDCAN_DLC_BYTES_20;
    }else if (tmp_u32DataLen <= 24) {
        pdrv_can->TxHeader.DataLength = FDCAN_DLC_BYTES_24;
    }else if (tmp_u32DataLen <= 32) {
        pdrv_can->TxHeader.DataLength = FDCAN_DLC_BYTES_32;
    }else if (tmp_u32DataLen <= 48) {
        pdrv_can->TxHeader.DataLength = FDCAN_DLC_BYTES_48;
    }else if (tmp_u32DataLen <= 64) {
        pdrv_can->TxHeader.DataLength = FDCAN_DLC_BYTES_64;
    }

    /* brs */
    if (pmsg->brs == 1)
    {
        pdrv_can->TxHeader.BitRateSwitch = FDCAN_BRS_ON;
    }
    else
    {
        pdrv_can->TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    }

    /* FDFormat */
    if (pmsg->fd_frame == 1)
    {
        pdrv_can->TxHeader.FDFormat = FDCAN_FD_CAN;
    }
    else
    {
        pdrv_can->TxHeader.FDFormat = FDCAN_FD_CAN;
    }

    pdrv_can->TxHeader.MessageMarker = 0;
    pdrv_can->TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    pdrv_can->TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;

    if(HAL_FDCAN_AddMessageToTxFifoQ(&pdrv_can->fdcanHandle, &pdrv_can->TxHeader, pmsg->data) != HAL_OK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_ssize_t _inline_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{

    struct rt_can_msg *pmsg;
    _stm32_fdcan_t *pdrv_can;

    RT_ASSERT(can);
    RT_ASSERT(buf);

    pdrv_can = (_stm32_fdcan_t *)can->parent.user_data;
    pmsg = (struct rt_can_msg *) buf;
    if(HAL_FDCAN_GetRxMessage(&pdrv_can->fdcanHandle, FDCAN_RX_FIFO0, &pdrv_can->RxHeader, pmsg->data) != HAL_OK)
    {
        return -RT_ERROR;
    }
    else
    {
        pmsg->id = pdrv_can->RxHeader.Identifier;
        if(pdrv_can->RxHeader.IdType == FDCAN_EXTENDED_ID)
        {
            pmsg->ide = RT_CAN_EXTID;
        }
        else
        {
            pmsg->ide = RT_CAN_STDID;
        }

        if(pdrv_can->RxHeader.RxFrameType == FDCAN_DATA_FRAME)
        {
            pmsg->rtr = RT_CAN_DTR;
        }
        else
        {
            pmsg->rtr = RT_CAN_RTR;
        }

        /* length */
        if(pdrv_can->RxHeader.DataLength <= 8)
        {
            pmsg->len = pdrv_can->RxHeader.DataLength;
        }
        else
        {
            switch(pdrv_can->RxHeader.DataLength)
            {
                case FDCAN_DLC_BYTES_12:
                    pmsg->len = 12;
                    break;

                case FDCAN_DLC_BYTES_16:
                    pmsg->len = 16;
                    break;

                case FDCAN_DLC_BYTES_20:
                    pmsg->len = 20;
                    break;

                case FDCAN_DLC_BYTES_24:
                    pmsg->len = 24;
                    break;

                case FDCAN_DLC_BYTES_32:
                    pmsg->len = 32;
                    break;

                case FDCAN_DLC_BYTES_48:
                    pmsg->len = 48;
                    break;

                case FDCAN_DLC_BYTES_64:
                    pmsg->len = 64;
                    break;

                default:
                    pmsg->len = 0;
                    break;
            }
        }


        if(pdrv_can->RxHeader.FDFormat == FDCAN_FD_CAN)
        {
            pmsg->fd_frame = 1;
        }else pmsg->fd_frame = 0;

        if(pdrv_can->RxHeader.BitRateSwitch == FDCAN_BRS_ON)
        {
            pmsg->brs = 1;
        }else pmsg->brs = 0;

        pmsg->hdr_index = pdrv_can->RxHeader.FilterIndex;
        return RT_EOK;

    }
}

static const struct rt_can_ops _can_ops =
{
    _inline_can_config,
    _inline_can_control,
    _inline_can_sendmsg,
    _inline_can_recvmsg,
};

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
    {
        if(hfdcan->Instance == FDCAN1)
        {
#ifdef BSP_USING_FDCAN1
            //CAN1
            /* Retreive Rx messages from RX FIFO0 */
            rt_hw_can_isr(&st_DrvCan1.device, RT_CAN_EVENT_RX_IND | 0 << 8);
#endif
        }
        else
        {
#ifdef BSP_USING_FDCAN2
            //CAN2
            /* Retreive Rx messages from RX FIFO0 */
            rt_hw_can_isr(&st_DrvCan2.device, RT_CAN_EVENT_RX_IND | 0 << 8);
#endif
        }
    }
}

void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{
    if(hfdcan->Instance == FDCAN1)
    {
#ifdef BSP_USING_FDCAN1
        //can1
        rt_hw_can_isr(&st_DrvCan1.device, RT_CAN_EVENT_TX_DONE | (((0) << 8)));
#endif
    }
    else
    {
#ifdef BSP_USING_FDCAN2
        //can2
        rt_hw_can_isr(&st_DrvCan2.device, RT_CAN_EVENT_TX_DONE | ((BufferIndexes-1) << 8));
#endif
    }

}


void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan)
{
    if(hfdcan->Instance == FDCAN1)
    {
        //can1
    }
    else
    {
        //can2
    }
}

void HAL_FDCAN_TxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{

}

void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan)
{
    rt_uint32_t tmp_u32Errcount;
    rt_uint32_t tmp_u32status;
    uint32_t ret = HAL_FDCAN_GetError(hfdcan);

    if(hfdcan->Instance == FDCAN1)
    {
#ifdef BSP_USING_FDCAN1
        //can1
        if( (ret & FDCAN_IT_ARB_PROTOCOL_ERROR) &&
            (hfdcan->Instance->CCCR & FDCAN_CCCR_INIT_Msk))
        {
            hfdcan->Instance->CCCR &= ~FDCAN_CCCR_INIT_Msk;
            st_DrvCan1.device.status.errcode = 0xff;
        }
        else
        {
            tmp_u32Errcount = st_DrvCan1.fdcanHandle.Instance->ECR;
            tmp_u32status = st_DrvCan1.fdcanHandle.Instance->PSR;

            st_DrvCan1.device.status.rcverrcnt = (tmp_u32Errcount>>8)&0x000000ff;
            st_DrvCan1.device.status.snderrcnt = (tmp_u32Errcount)&0x000000ff;
            st_DrvCan1.device.status.lasterrtype = tmp_u32status&0x000000007;
        }
#endif /*BSP_USING_FDCAN1*/
    }
    else
    {
#ifdef BSP_USING_FDCAN2
        if( (ret & FDCAN_IT_ARB_PROTOCOL_ERROR) &&
            (hfdcan->Instance->CCCR & FDCAN_CCCR_INIT_Msk))
        {
            hfdcan->Instance->CCCR &= ~FDCAN_CCCR_INIT_Msk;
            st_DrvCan2.device.status.errcode = 0xff;
        }
        else
        {
            //can2
            tmp_u32Errcount = st_DrvCan2.fdcanHandle.Instance->ECR;
            tmp_u32status = st_DrvCan2.fdcanHandle.Instance->PSR;
            st_DrvCan2.device.status.rcverrcnt = (tmp_u32Errcount>>8)&0x000000ff;
            st_DrvCan2.device.status.snderrcnt = (tmp_u32Errcount)&0x000000ff;
            st_DrvCan2.device.status.lasterrtype = tmp_u32status&0x000000007;
        }
#endif /*BSP_USING_FDCAN2*/
    }
}

#ifdef BSP_USING_FDCAN1

void FDCAN1_IT0_IRQHandler(void)             /* FDCAN2 interrupt line 0      */
{
    rt_interrupt_enter();
    HAL_FDCAN_IRQHandler(&st_DrvCan1.fdcanHandle);
    rt_interrupt_leave();
}

void FDCAN1_IT1_IRQHandler(void)             /* FDCAN2 interrupt line 1      */
{
    rt_interrupt_enter();
    HAL_FDCAN_IRQHandler(&st_DrvCan1.fdcanHandle);
    rt_interrupt_leave();
}

#endif /*BSP_USING_FDCAN1*/

#ifdef BSP_USING_FDCAN2
void FDCAN2_IT0_IRQHandler(void)             /* FDCAN2 interrupt line 0      */
{
    rt_interrupt_enter();
    HAL_FDCAN_IRQHandler(&st_DrvCan2.fdcanHandle);
    rt_interrupt_leave();
}

void FDCAN2_IT1_IRQHandler(void)             /* FDCAN2 interrupt line 1      */
{
    rt_interrupt_enter();
    HAL_FDCAN_IRQHandler(&st_DrvCan2.fdcanHandle);
    rt_interrupt_leave();
}
#endif/*BSP_USING_FDCAN2*/


static int rt_hw_can_init(void)
{
    struct can_configure config;
    config.baud_rate = CAN500kBaud;
    config.msgboxsz = 30;
    config.sndboxnumber = 1;
    config.mode = RT_CAN_MODE_NORMAL;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
    config.baud_rate_fd = BSP_FDCAN_BAUD_DATA_2M;
    config.use_bit_timing = 0;  // does not use the timing in config

#ifdef RT_CAN_USING_HDR
    config.maxhdr = 36;
    FDCAN_FilterTypeDef sFilterConfig;
    sFilterConfig.IdType = FDCAN_STANDARD_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0;
    sFilterConfig.FilterID2 = 0;
#endif

#ifdef BSP_USING_FDCAN1
#if defined(BSP_FDCAN1_FRAME_CLASSIC)
    config.enable_canfd = BSP_FDCAN_FRAMEFORMAT_CLASSIC;
#elif defined(BSP_FDCAN1_FRAME_FD)
    config.enable_canfd = BSP_FDCAN_FRAMEFORMAT_FD_NO_BRS;
#else
    config.enable_canfd = BSP_FDCAN_FRAMEFORMAT_FD_BRS;
#endif

#ifdef RT_CAN_USING_HDR
    st_DrvCan1.FilterConfig = sFilterConfig;
#endif

    st_DrvCan1.name = "can1";
    st_DrvCan1.fdcanHandle.Instance = FDCAN1;
    st_DrvCan1.device.config = config;

    /* register FDCAN1 device */
    rt_hw_can_register(&st_DrvCan1.device, st_DrvCan1.name, &_can_ops, &st_DrvCan1);
#endif /* BSP_USING_FDCAN1 */

#ifdef BSP_USING_FDCAN2
#if defined(BSP_FDCAN2_FRAME_CLASSIC)
    config.enable_canfd = BSP_FDCAN_FRAMEFORMAT_CLASSIC;
#elif defined(BSP_FDCAN2_FRAME_FD)
    config.enable_canfd = BSP_FDCAN_FRAMEFORMAT_FD_NO_BRS;
#else
    config.enable_canfd = BSP_FDCAN_FRAMEFORMAT_FD_BRS;
#endif

#ifdef RT_CAN_USING_HDR
    st_DrvCan2.FilterConfig = sFilterConfig;
#endif
	st_DrvCan2.name = "can2";
    st_DrvCan2.fdcanHandle.Instance = FDCAN2;
    st_DrvCan2.device.config = config;

    /* register FDCAN1 device */
    rt_hw_can_register(&st_DrvCan2.device, st_DrvCan2.name, &_can_ops, &st_DrvCan2);
#endif /* BSP_USING_FDCAN2 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_FDCAN1 || BSP_USING_FDCAN2 */
#endif /* RT_USING_CAN */
