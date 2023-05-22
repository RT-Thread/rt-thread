/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-30     luobeihai    first version
 */

#include "drv_can.h"

#ifdef RT_USING_CAN

#if defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2)

#define LOG_TAG    "drv_can"
#include <drv_log.h>

#ifdef BSP_USING_CAN1
static struct apm32_can drv_can1 =
{
    .name = "can1",
    .CANx = CAN1,
};
#endif

#ifdef BSP_USING_CAN2
static struct apm32_can drv_can2 =
{
    .name = "can2",
    .CANx = CAN2,
};
#endif

/* baud calculation example: PCLK1 / ((timeSegment1 + timeSegment2 + 1) * prescaler) = 36 / ((1 + 8 + 3) * 3) = 1MHz */
#if defined (SOC_SERIES_APM32F1) || defined (SOC_SERIES_APM32E1) || defined (SOC_SERIES_APM32S1)  /* APB1 36MHz(max) */
static const struct apm32_baud_rate_tab can_baud_rate_tab[] =
{
    APM32_CAN_BAUD_DEF(CAN1MBaud,   CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_3, 3),
    APM32_CAN_BAUD_DEF(CAN800kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_5, CAN_TIME_SEGMENT2_3, 5),
    APM32_CAN_BAUD_DEF(CAN500kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_3, 6),
    APM32_CAN_BAUD_DEF(CAN250kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_3, 12),
    APM32_CAN_BAUD_DEF(CAN125kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_3, 24),
    APM32_CAN_BAUD_DEF(CAN100kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_3, 30),
    APM32_CAN_BAUD_DEF(CAN50kBaud,  CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_3, 60),
    APM32_CAN_BAUD_DEF(CAN20kBaud,  CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_3, 150),
    APM32_CAN_BAUD_DEF(CAN10kBaud,  CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_3, 300),
};
#elif defined (SOC_SERIES_APM32F4)  /* APB1 42MHz(max) */
static const struct apm32_baud_rate_tab can_baud_rate_tab[] =
{
    APM32_CAN_BAUD_DEF(CAN1MBaud,   CAN_SJW_1, CAN_TIME_SEGMENT1_9, CAN_TIME_SEGMENT2_4, 3),
    APM32_CAN_BAUD_DEF(CAN800kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_8, CAN_TIME_SEGMENT2_4, 4),
    APM32_CAN_BAUD_DEF(CAN500kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_9, CAN_TIME_SEGMENT2_4, 6),
    APM32_CAN_BAUD_DEF(CAN250kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_9, CAN_TIME_SEGMENT2_4, 12),
    APM32_CAN_BAUD_DEF(CAN125kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_9, CAN_TIME_SEGMENT2_4, 24),
    APM32_CAN_BAUD_DEF(CAN100kBaud, CAN_SJW_1, CAN_TIME_SEGMENT1_9, CAN_TIME_SEGMENT2_4, 30),
    APM32_CAN_BAUD_DEF(CAN50kBaud,  CAN_SJW_1, CAN_TIME_SEGMENT1_9, CAN_TIME_SEGMENT2_4, 60),
    APM32_CAN_BAUD_DEF(CAN20kBaud,  CAN_SJW_1, CAN_TIME_SEGMENT1_9, CAN_TIME_SEGMENT2_4, 150),
    APM32_CAN_BAUD_DEF(CAN10kBaud,  CAN_SJW_1, CAN_TIME_SEGMENT1_9, CAN_TIME_SEGMENT2_4, 300),
};
#endif

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].baud_rate == baud)
            return index;
    }

    return 0; /* default baud is CAN1MBaud */
}

static rt_err_t apm32_can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    struct apm32_can *drv_can;
    rt_uint32_t baud_index;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    drv_can = (struct apm32_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

    /* init can gpio and enable can clock */
    extern void apm32_msp_can_init(void *Instance);
    apm32_msp_can_init(drv_can->CANx);

    CAN_ConfigStructInit(&drv_can->can_init);

    drv_can->can_init.autoBusOffManage = ENABLE;
    drv_can->can_init.autoWakeUpMode   = DISABLE;
    drv_can->can_init.nonAutoRetran    = DISABLE;
    drv_can->can_init.rxFIFOLockMode   = DISABLE;
    drv_can->can_init.txFIFOPriority   = ENABLE;

    /* can mode config */
    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        drv_can->can_init.mode = CAN_MODE_NORMAL;
        break;

    case RT_CAN_MODE_LISTEN:
        drv_can->can_init.mode = CAN_MODE_SILENT;
        break;

    case RT_CAN_MODE_LOOPBACK:
        drv_can->can_init.mode = CAN_MODE_LOOPBACK;
        break;

    case RT_CAN_MODE_LOOPBACKANLISTEN:
        drv_can->can_init.mode = CAN_MODE_SILENT_LOOPBACK;
        break;

    default:
        drv_can->can_init.mode = CAN_MODE_NORMAL;
        break;
    }

    /* can baud config */
    baud_index = get_can_baud_index(cfg->baud_rate);
    drv_can->can_init.syncJumpWidth    = can_baud_rate_tab[baud_index].syncJumpWidth;
    drv_can->can_init.timeSegment1     = can_baud_rate_tab[baud_index].timeSegment1;
    drv_can->can_init.timeSegment2     = can_baud_rate_tab[baud_index].timeSegment2;
    drv_can->can_init.prescaler        = can_baud_rate_tab[baud_index].prescaler;

    /* init can */
    if (CAN_Config(drv_can->CANx, &drv_can->can_init) != SUCCESS)
    {
        LOG_D("Can init error");
        return -RT_ERROR;
    }

    /* default filter config */
#if defined(SOC_SERIES_APM32F4) || defined(APM32F10X_CL)
    CAN_ConfigFilter(&drv_can->FilterConfig);
#else
    CAN_ConfigFilter(drv_can->CANx, &drv_can->FilterConfig);
#endif

    return RT_EOK;
}

static rt_err_t apm32_can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct apm32_can *drv_can;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    drv_can = (struct apm32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            if (CAN1 == drv_can->CANx)
            {
                NVIC_DisableIRQRequest(CAN1_RX0_IRQn);
                NVIC_DisableIRQRequest(CAN1_RX1_IRQn);
            }
#ifdef BSP_USING_CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_DisableIRQRequest(CAN2_RX0_IRQn);
                NVIC_DisableIRQRequest(CAN2_RX1_IRQn);
            }
#endif
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_F0MP);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_F0FULL);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_F0OVR);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_F1MP);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_F1FULL);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_F1OVR);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            if (CAN1 == drv_can->CANx)
            {
                NVIC_DisableIRQRequest(CAN1_TX_IRQn);
            }
#ifdef BSP_USING_CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_DisableIRQRequest(CAN2_TX_IRQn);
            }
#endif
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_TXME);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            if (CAN1 == drv_can->CANx)
            {
                NVIC_DisableIRQRequest(CAN1_SCE_IRQn);
            }
#ifdef BSP_USING_CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_DisableIRQRequest(CAN2_SCE_IRQn);
            }
#endif
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_ERRW);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_ERRP);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_BOF);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_LEC);
            CAN_DisableInterrupt(drv_can->CANx, CAN_INT_ERR);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_F0MP);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_F0FULL);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_F0OVR);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_F1MP);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_F1FULL);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_F1OVR);

            if (CAN1 == drv_can->CANx)
            {
                NVIC_EnableIRQRequest(CAN1_RX0_IRQn, 1, 0);
                NVIC_EnableIRQRequest(CAN1_RX1_IRQn, 1, 0);
            }
#ifdef BSP_USING_CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_EnableIRQRequest(CAN2_RX0_IRQn, 1, 0);
                NVIC_EnableIRQRequest(CAN2_RX1_IRQn, 1, 0);
            }
#endif
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_TXME);

            if (CAN1 == drv_can->CANx)
            {
                NVIC_EnableIRQRequest(CAN1_TX_IRQn, 1, 0);
            }
#ifdef BSP_USING_CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_EnableIRQRequest(CAN2_TX_IRQn, 1, 0);
            }
#endif
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_ERRW);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_ERRP);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_BOF);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_LEC);
            CAN_EnableInterrupt(drv_can->CANx, CAN_INT_ERR);

            if (CAN1 == drv_can->CANx)
            {
                NVIC_EnableIRQRequest(CAN1_SCE_IRQn, 1, 0);
            }
#ifdef BSP_USING_CAN2
            if (CAN2 == drv_can->CANx)
            {
                NVIC_EnableIRQRequest(CAN2_SCE_IRQn, 1, 0);
            }
#endif
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
    {
        rt_uint32_t id_h = 0;
        rt_uint32_t id_l = 0;
        rt_uint32_t mask_h = 0;
        rt_uint32_t mask_l = 0;
        rt_uint32_t mask_l_tail = 0;  //CAN_FxR2 bit [2:0]

        if (RT_NULL == arg)
        {
            /* default filter config */
#if defined(SOC_SERIES_APM32F4) || defined(APM32F10X_CL)
            CAN_ConfigFilter(&drv_can->FilterConfig);
#else
            CAN_ConfigFilter(drv_can->CANx, &drv_can->FilterConfig);
#endif
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                if (filter_cfg->items[i].hdr_bank == -1)
                {
                    /* use default filter bank settings */
                    if (rt_strcmp(drv_can->name, "can1") == 0)
                    {
                        /* can1 banks 0~13 */
                        drv_can->FilterConfig.filterNumber = i;
                    }
                    else if (rt_strcmp(drv_can->name, "can2") == 0)
                    {
                        /* can2 banks 14~27 */
                        drv_can->FilterConfig.filterNumber = i + 14;
                    }
                }
                else
                {
                    /* use user-defined filter bank settings */
                    drv_can->FilterConfig.filterNumber = filter_cfg->items[i].hdr_bank;
                }
                 /**
                 * ID     | CAN_FxR1[31:24] | CAN_FxR1[23:16] | CAN_FxR1[15:8] | CAN_FxR1[7:0]       |
                 * MASK   | CAN_FxR2[31:24] | CAN_FxR2[23:16] | CAN_FxR2[15:8] | CAN_FxR2[7:0]       |
                 * STD ID |     STID[10:3]  | STDID[2:0] |<-                21bit                  ->|
                 * EXT ID |    EXTID[28:21] | EXTID[20:13]    | EXTID[12:5]    | EXTID[4:0] IDE RTR 0|
                 * @note the 32bit STD ID must << 21 to fill CAN_FxR1[31:21] and EXT ID must << 3,
                 *       -> but the id bit of struct rt_can_filter_item is 29,
                 *       -> so STD id << 18 and EXT id Don't need << 3, when get the high 16bit.
                 *       -> FilterIdHigh : (((STDid << 18) or (EXT id)) >> 13) & 0xFFFF,
                 *       -> FilterIdLow:   ((STDid << 18) or (EXT id << 3)) & 0xFFFF.
                 * @note the mask bit of struct rt_can_filter_item is 32,
                 *       -> FilterMaskIdHigh: (((STD mask << 21) or (EXT mask <<3)) >> 16) & 0xFFFF
                 *       -> FilterMaskIdLow: ((STD mask << 21) or (EXT mask <<3)) & 0xFFFF
                 */
                if (filter_cfg->items[i].mode == CAN_FILTER_MODE_IDMASK)
                {
                    /* make sure the CAN_FxR1[2:0](IDE RTR) work */
                    mask_l_tail = 0x06;
                    drv_can->FilterConfig.filterMode = CAN_FILTER_MODE_IDMASK;
                }
                else if (filter_cfg->items[i].mode == CAN_FILTER_MODE_IDLIST)
                {
                    /* same as CAN_FxR1 */
                    mask_l_tail = (filter_cfg->items[i].ide << 2) | (filter_cfg->items[i].rtr << 1);
                    drv_can->FilterConfig.filterMode = CAN_FILTER_MODE_IDLIST;
                }
                if (filter_cfg->items[i].ide == RT_CAN_STDID)
                {
                    id_h = ((filter_cfg->items[i].id << 18) >> 13) & 0xFFFF;
                    id_l = ((filter_cfg->items[i].id << 18) |
                            (filter_cfg->items[i].ide << 2) |
                            (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                    mask_h = ((filter_cfg->items[i].mask << 21) >> 16) & 0xFFFF;
                    mask_l = ((filter_cfg->items[i].mask << 21) | mask_l_tail) & 0xFFFF;
                }
                else if (filter_cfg->items[i].ide == RT_CAN_EXTID)
                {
                    id_h = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                    id_l = ((filter_cfg->items[i].id << 3)   |
                            (filter_cfg->items[i].ide << 2)  |
                            (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                    mask_h = ((filter_cfg->items[i].mask << 3) >> 16) & 0xFFFF;
                    mask_l = ((filter_cfg->items[i].mask << 3) | mask_l_tail) & 0xFFFF;
                }
                drv_can->FilterConfig.filterIdHigh = id_h;
                drv_can->FilterConfig.filterIdLow = id_l;
                drv_can->FilterConfig.filterMaskIdHigh = mask_h;
                drv_can->FilterConfig.filterMaskIdLow = mask_l;
                drv_can->FilterConfig.filterFIFO = CAN_FILTER_FIFO_0;
                drv_can->FilterConfig.filterScale = CAN_FILTER_SCALE_32BIT;
                drv_can->FilterConfig.filterActivation = ENABLE;

                /* Filter conf */
#if defined(SOC_SERIES_APM32F4) || defined(APM32F10X_CL)
                CAN_ConfigFilter(&drv_can->FilterConfig);
#else
                CAN_ConfigFilter(drv_can->CANx, &drv_can->FilterConfig);
#endif
            }
        }
        break;
    }
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
                argval != RT_CAN_MODE_LISTEN &&
                argval != RT_CAN_MODE_LOOPBACK &&
                argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.mode)
        {
            drv_can->device.config.mode = argval;
            return apm32_can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
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
        if (argval != drv_can->device.config.baud_rate)
        {
            drv_can->device.config.baud_rate = argval;
            return apm32_can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.privmode)
        {
            drv_can->device.config.privmode = argval;
            return apm32_can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
        {
            rt_uint32_t errtype;
            errtype = drv_can->CANx->ERRSTS;
            drv_can->device.status.rcverrcnt = errtype >> 24;
            drv_can->device.status.snderrcnt = (errtype >> 16 & 0xFF);
            drv_can->device.status.lasterrtype = errtype & 0x70;
            drv_can->device.status.errcode = errtype & 0x07;

            rt_memcpy(arg, &drv_can->device.status, sizeof(drv_can->device.status));
        }
        break;
    }

    return RT_EOK;
}

static int can_send_rtmsg(CAN_T *CANx, struct rt_can_msg *pmsg, uint32_t mailbox_index)
{
    CAN_TxMessage_T CAN_TxMessage = {0};
    CAN_TxMessage_T *TxMessage = &CAN_TxMessage;

    if (RT_CAN_STDID == pmsg->ide)
    {
        TxMessage->typeID = CAN_TYPEID_STD;
        TxMessage->stdID = pmsg->id;
    }
    else
    {
        TxMessage->typeID = CAN_TYPEID_EXT;
        TxMessage->extID = pmsg->id;
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
        TxMessage->remoteTxReq = CAN_RTXR_DATA;
    }
    else
    {
        TxMessage->remoteTxReq = CAN_RTXR_REMOTE;
    }

    /* Set up the Id */
    CANx->sTxMailBox[mailbox_index].TXMID &= 0x00000001;
    if (TxMessage->typeID == CAN_TYPEID_STD)
    {
        CANx->sTxMailBox[mailbox_index].TXMID |= (TxMessage->stdID << 21) | (TxMessage->remoteTxReq);
    }
    else
    {
        CANx->sTxMailBox[mailbox_index].TXMID |= (TxMessage->extID << 3) | (TxMessage->typeID) | (TxMessage->remoteTxReq);
    }

    /* Set up the TXDLEN */
    TxMessage->dataLengthCode = pmsg->len & 0x0FU;
    CANx->sTxMailBox[mailbox_index].TXDLEN &= (uint32_t)0xFFFFFFF0;
    CANx->sTxMailBox[mailbox_index].TXDLEN |= TxMessage->dataLengthCode;

    /* Set up the data field */
    CANx->sTxMailBox[mailbox_index].TXMDH = (((uint32_t)pmsg->data[7] << 24) |
                                            ((uint32_t)pmsg->data[6] << 16)  |
                                            ((uint32_t)pmsg->data[5] << 8)   |
                                            ((uint32_t)pmsg->data[4]));
    CANx->sTxMailBox[mailbox_index].TXMDL = (((uint32_t)pmsg->data[3] << 24) |
                                            ((uint32_t)pmsg->data[2] << 16)  |
                                            ((uint32_t)pmsg->data[1] << 8)   |
                                            ((uint32_t)pmsg->data[0]));

    /* Request transmission */
    CANx->sTxMailBox[mailbox_index].TXMID |= 0x00000001;

    return RT_EOK;
}

static int apm32_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct apm32_can *drv_can;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    drv_can = (struct apm32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    /* Select one empty transmit mailbox */
    switch (box_num)
    {
        case CAN_TX_MAILBIX_0:
            if ((drv_can->CANx->TXSTS & 0x04000000) != 0x04000000)
            {
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        case CAN_TX_MAILBIX_1:
            if ((drv_can->CANx->TXSTS & 0x08000000) != 0x08000000)
            {
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        case CAN_TX_MAILBIX_2:
            if ((drv_can->CANx->TXSTS & 0x10000000) != 0x10000000)
            {
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        default:
            RT_ASSERT(0);
            break;
    }

    /* Start send msg */
    return can_send_rtmsg(drv_can->CANx, ((struct rt_can_msg *)buf), box_num);
}

static int apm32_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct apm32_can *drv_can;
    struct rt_can_msg *pmsg;
    CAN_RxMessage_T RxMessage = {0};

    RT_ASSERT(can);

    drv_can = (struct apm32_can *)can->parent.user_data;

    pmsg = (struct rt_can_msg *) buf;

    CAN_RxMessage(drv_can->CANx, (CAN_RX_FIFO_T)fifo, &RxMessage);

    /* get data  */
    pmsg->data[0] = RxMessage.data[0];
    pmsg->data[1] = RxMessage.data[1];
    pmsg->data[2] = RxMessage.data[2];
    pmsg->data[3] = RxMessage.data[3];
    pmsg->data[4] = RxMessage.data[4];
    pmsg->data[5] = RxMessage.data[5];
    pmsg->data[6] = RxMessage.data[6];
    pmsg->data[7] = RxMessage.data[7];

    /* get id */
    if (CAN_TYPEID_STD == RxMessage.typeID)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = RxMessage.stdID;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = RxMessage.extID;
    }

    /* get type */
    if (CAN_RTXR_DATA == RxMessage.remoteTxReq)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /*get rxfifo = CAN_RX_FIFO0/CAN_RX_FIFO1*/
    pmsg->rxfifo = fifo;

    /* get len */
    pmsg->len = RxMessage.dataLengthCode;

    /* get hdr_index */
    if (drv_can->CANx == CAN1)
    {
        pmsg->hdr_index = RxMessage.filterMatchIndex;
    }
#ifdef CAN2
    else if (drv_can->CANx == CAN2)
    {
       pmsg->hdr_index = RxMessage.filterMatchIndex;
    }
#endif

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    apm32_can_config,
    apm32_can_control,
    apm32_can_sendmsg,
    apm32_can_recvmsg,
};

static void _can_rx_isr(struct rt_can_device *can, rt_uint32_t fifo)
{
    struct apm32_can *drv_can;
    RT_ASSERT(can != RT_NULL);
    drv_can = (struct apm32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    switch (fifo)
    {
    case CAN_RX_FIFO_0:
        /* save to user list */
        if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_F0MP) && CAN_PendingMessage(drv_can->CANx, CAN_RX_FIFO_0))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        /* Check FULL flag for FIFO0 */
        if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_F0FULL))
        {
            /* Clear FIFO0 FULL Flag */
            CAN_ClearStatusFlag(drv_can->CANx, CAN_FLAG_F0FULL);
        }
        /* Check Overrun flag for FIFO0 */
        if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_F0OVR))
        {
            /* Clear FIFO0 Overrun Flag */
            CAN_ClearStatusFlag(drv_can->CANx, CAN_FLAG_F0OVR);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;

    case CAN_RX_FIFO_1:
        /* save to user list */
        if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_F1MP) && CAN_PendingMessage(drv_can->CANx, CAN_RX_FIFO_1))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        /* Check FULL flag for FIFO1 */
        if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_F1FULL))
        {
            /* Clear FIFO1 FULL Flag */
            CAN_ClearStatusFlag(drv_can->CANx, CAN_FLAG_F1FULL);
        }
        /* Check Overrun flag for FIFO1 */
        if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_F1OVR))
        {
            /* Clear FIFO1 Overrun Flag */
            CAN_ClearStatusFlag(drv_can->CANx, CAN_FLAG_F1OVR);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    }
}

static void _can_sce_isr(struct rt_can_device *can)
{
    struct apm32_can *drv_can;
    RT_ASSERT(can != RT_NULL);
    drv_can = (struct apm32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    rt_uint32_t errtype = drv_can->CANx->ERRSTS;

    switch ((errtype & 0x70) >> 4)
    {
        case RT_CAN_BUS_BIT_PAD_ERR:
            can->status.bitpaderrcnt++;
            break;
        case RT_CAN_BUS_FORMAT_ERR:
            can->status.formaterrcnt++;
            break;
        case RT_CAN_BUS_ACK_ERR:/* attention !!! test ack err's unit is transmit unit */
            can->status.ackerrcnt++;
            if (!READ_BIT(drv_can->CANx->TXSTS, 0x00000002))
            {
                rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
            }
            else if (!READ_BIT(drv_can->CANx->TXSTS, 0x00000200))
            {
                rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 1 << 8);
            }
            else if (!READ_BIT(drv_can->CANx->TXSTS, 0x00020000))
            {
                rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 2 << 8);
            }
            break;
        case RT_CAN_BUS_IMPLICIT_BIT_ERR:
        case RT_CAN_BUS_EXPLICIT_BIT_ERR:
            can->status.biterrcnt++;
            break;
        case RT_CAN_BUS_CRC_ERR:
            can->status.crcerrcnt++;
            break;
    }

    can->status.lasterrtype = errtype & 0x70;
    can->status.rcverrcnt = errtype >> 24;
    can->status.snderrcnt = (errtype >> 16 & 0xFF);
    can->status.errcode = errtype & 0x07;

    /* clear error interrupt flag */
    CAN_ClearIntFlag(drv_can->CANx, CAN_INT_ERR);
}

static void _can_tx_isr(struct rt_can_device *can)
{
    struct apm32_can *drv_can;
    RT_ASSERT(can != RT_NULL);
    drv_can = (struct apm32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_REQC0))
    {
        rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | (0x00 << 8));
        CAN_ClearStatusFlag(drv_can->CANx, CAN_FLAG_REQC0);
    }
    if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_REQC1))
    {
        rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | (0x01 << 8));
        CAN_ClearStatusFlag(drv_can->CANx, CAN_FLAG_REQC1);
    }
    if (CAN_ReadStatusFlag(drv_can->CANx, CAN_FLAG_REQC2))
    {
        rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | (0x02 << 8));
        CAN_ClearStatusFlag(drv_can->CANx, CAN_FLAG_REQC2);
    }
}

#ifdef BSP_USING_CAN1
/**
 * @brief This function handles CAN1 TX interrupts. transmit fifo0/1/2 is empty can trigger this interrupt
 */
void CAN1_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_isr(&drv_can1.device);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void CAN1_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&drv_can1.device, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&drv_can1.device, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 SCE interrupts.
 */
void CAN1_SCE_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_sce_isr(&drv_can1.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
/**
 * @brief This function handles CAN2 TX interrupts.
 */
void CAN2_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_isr(&drv_can2.device);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX0 interrupts.
 */
void CAN2_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&drv_can2.device, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX1 interrupts.
 */
void CAN2_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&drv_can2.device, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 SCE interrupts.
 */
void CAN2_SCE_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_sce_isr(&drv_can2.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN2 */

int rt_hw_can_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#if defined(CAN2) && (defined(APM32F10X_CL) || defined(SOC_SERIES_APM32F4))
    config.maxhdr = 28;
#endif
#endif
    /* config default filter */
    CAN_FilterConfig_T filterConf = {0};
    filterConf.filterNumber = 0;
    filterConf.filterIdHigh = 0x0000;
    filterConf.filterIdLow = 0x0000;
    filterConf.filterMaskIdHigh = 0x0000;
    filterConf.filterMaskIdLow = 0x0000;
    filterConf.filterFIFO = CAN_FILTER_FIFO_0;
    filterConf.filterMode = CAN_FILTER_MODE_IDMASK;
    filterConf.filterScale = CAN_FILTER_SCALE_32BIT;
    filterConf.filterActivation = ENABLE;

#ifdef BSP_USING_CAN1
    filterConf.filterNumber = 0;

    drv_can1.FilterConfig = filterConf;
    drv_can1.device.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&drv_can1.device, drv_can1.name, &_can_ops, &drv_can1);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
#if defined(APM32F10X_HD) || defined(APM32E10X_HD) || defined(APM32S10X_MD)
    filterConf.filterNumber = 0;
#elif defined(APM32F10X_CL) || defined(SOC_SERIES_APM32F4)
    filterConf.filterNumber = 14;
#else
    filterConf.filterNumber = 0;
#endif
    drv_can2.FilterConfig = filterConf;
    drv_can2.device.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&drv_can2.device, drv_can2.name, &_can_ops, &drv_can2);
#endif /* BSP_USING_CAN2 */

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2) */
#endif /*RT_USING_CAN*/
