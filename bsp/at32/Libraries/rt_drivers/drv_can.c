/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-09     shelton      the first version
 */

#include "drv_can.h"
#ifdef BSP_USING_CAN

#define LOG_TAG    "drv_can"
#include <drv_log.h>

/* attention !!! baud calculation example: apbclk / ((ss + bs1 + bs2) * brp), ep: 120 / ((1 + 8 + 3) * 10) = 1MHz*/
static const struct at32_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud,   CAN_SJW_2tq, CAN_BS1_8tq,  CAN_BS2_3tq, 10},
    {CAN800kBaud, CAN_SJW_2tq, CAN_BS1_7tq,  CAN_BS2_2tq, 15},
    {CAN500kBaud, CAN_SJW_2tq, CAN_BS1_9tq,  CAN_BS2_2tq, 20},
    {CAN250kBaud, CAN_SJW_2tq, CAN_BS1_9tq,  CAN_BS2_2tq, 40},
    {CAN125kBaud, CAN_SJW_2tq, CAN_BS1_9tq,  CAN_BS2_2tq, 80},
    {CAN100kBaud, CAN_SJW_2tq, CAN_BS1_13tq, CAN_BS2_2tq, 75},
    {CAN50kBaud,  CAN_SJW_2tq, CAN_BS1_13tq, CAN_BS2_2tq, 150},
    {CAN20kBaud,  CAN_SJW_2tq, CAN_BS1_13tq, CAN_BS2_2tq, 375},
    {CAN10kBaud,  CAN_SJW_2tq, CAN_BS1_13tq, CAN_BS2_2tq, 750}
};

#ifdef BSP_USING_CAN1
static struct at32_can can_instance1 =
{
    .name = "can1",
    .CanConfig.Instance = CAN1,
};
#endif

#ifdef BSP_USING_CAN2
static struct at32_can can_instance2 =
{
    .name = "can2",
    .CanConfig.Instance = CAN2,
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

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    struct at32_can *can_instance;
    rt_uint32_t baud_index;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    can_instance = (struct at32_can *)can->parent.user_data;
    RT_ASSERT(can_instance);

    at32_msp_can_init((void *)can_instance->CanConfig.Instance);

    CAN_StructInit(&(can_instance->CanConfig.CanInit));

    can_instance->CanConfig.CanInit.CAN_Mode = DISABLE;
    can_instance->CanConfig.CanInit.CAN_ABO = ENABLE;
    can_instance->CanConfig.CanInit.CAN_AWU = ENABLE;
    can_instance->CanConfig.CanInit.CAN_NART = DISABLE;
    can_instance->CanConfig.CanInit.CAN_RFL = DISABLE;
    can_instance->CanConfig.CanInit.CAN_TFP = ENABLE;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        can_instance->CanConfig.CanInit.CAN_Mode = CAN_Mode_Normal;
        break;
    case RT_CAN_MODE_LISEN:
        can_instance->CanConfig.CanInit.CAN_Mode = CAN_Mode_Silent;
        break;
    case RT_CAN_MODE_LOOPBACK:
        can_instance->CanConfig.CanInit.CAN_Mode = CAN_Mode_LoopBack;
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        can_instance->CanConfig.CanInit.CAN_Mode = CAN_Mode_Silent_LoopBack;
        break;
    }

    baud_index = get_can_baud_index(cfg->baud_rate);
    can_instance->CanConfig.CanInit.CAN_SJW = can_baud_rate_tab[baud_index].sjw;
    can_instance->CanConfig.CanInit.CAN_BS1 = can_baud_rate_tab[baud_index].bs1;
    can_instance->CanConfig.CanInit.CAN_BS2 = can_baud_rate_tab[baud_index].bs2;
    can_instance->CanConfig.CanInit.CAN_Prescaler = can_baud_rate_tab[baud_index].psc;

    /* init can */
    if (CAN_Init(can_instance->CanConfig.Instance, &(can_instance->CanConfig.CanInit)) != CAN_InitStatus_Success)
    {
        return -RT_ERROR;
    }

    /* default filter config */
    CAN_FilterInit(can_instance->CanConfig.Instance, &can_instance->CanConfig.FilterConfig);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    NVIC_InitType NVIC_InitStruct;
    struct at32_can *can_instance;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    can_instance = (struct at32_can *)can->parent.user_data;
    RT_ASSERT(can_instance != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            if (CAN1 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);

                NVIC_InitStruct.NVIC_IRQChannel = CAN1_RX1_IRQn;
                NVIC_Init(&NVIC_InitStruct);
            }
#ifdef CAN2
            if (CAN2 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = CAN2_RX0_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);

                NVIC_InitStruct.NVIC_IRQChannel = CAN2_RX1_IRQn;
                NVIC_Init(&NVIC_InitStruct);
            }
#endif
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFP0, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFFU0, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFOV0, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFP1, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFFU1, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFOV1, DISABLE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            if (CAN1 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);
            }
#ifdef CAN2
            if (CAN2 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = CAN2_TX_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);
            }
#endif
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_TSME, DISABLE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            if (CAN1 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = CAN1_SCE_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);
            }
#ifdef CAN2
            if (CAN2 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = CAN2_SCE_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);
            }
#endif
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_ERG, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_ERP, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_BU, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_LEC, DISABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_ERR, DISABLE);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFP0, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFFU0, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFOV0, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFP1, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFFU1, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_RFOV1, ENABLE);

            if (CAN1 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);

                NVIC_InitStruct.NVIC_IRQChannel = CAN1_RX1_IRQn;
                NVIC_Init(&NVIC_InitStruct);
            }
#ifdef CAN2
            if (CAN2 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = CAN2_RX0_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);

                NVIC_InitStruct.NVIC_IRQChannel = CAN2_RX1_IRQn;
                NVIC_Init(&NVIC_InitStruct);
            }
#endif
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_TSME, ENABLE);

            if (CAN1 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);
            }
#ifdef CAN2
            if (CAN2 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = CAN2_TX_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);
            }
#endif
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_ERG, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_ERP, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_BU, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_LEC, ENABLE);
            CAN_INTConfig(can_instance->CanConfig.Instance, CAN_INT_ERR, ENABLE);

            if (CAN1 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = CAN1_SCE_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);
            }
#ifdef CAN2
            if (CAN2 == can_instance->CanConfig.Instance)
            {
                NVIC_InitStruct.NVIC_IRQChannel = CAN2_SCE_IRQn;
                NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
                NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
                NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
                NVIC_Init(&NVIC_InitStruct);
            }
#endif
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL == arg)
        {
            /* default filter config */
            CAN_FilterInit(can_instance->CanConfig.Instance, &can_instance->CanConfig.FilterConfig);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                can_instance->CanConfig.FilterConfig.CAN_FilterNumber = filter_cfg->items[i].hdr & (0x1fU);
                can_instance->CanConfig.FilterConfig.CAN_FilterIdHigh = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                can_instance->CanConfig.FilterConfig.CAN_FilterIdLow = ((filter_cfg->items[i].id << 3) |
                                                    (filter_cfg->items[i].ide << 2) |
                                                    (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                can_instance->CanConfig.FilterConfig.CAN_FilterMskIdHigh = (filter_cfg->items[i].mask >> 16) & 0xFFFF;
                can_instance->CanConfig.FilterConfig.CAN_FilterMskIdLow = filter_cfg->items[i].mask & 0xFFFF;
                can_instance->CanConfig.FilterConfig.CAN_FilterMode = filter_cfg->items[i].mode;
                /* Filter conf */
                CAN_FilterInit(can_instance->CanConfig.Instance, &can_instance->CanConfig.FilterConfig);
            }
        }
        break;
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
            argval != RT_CAN_MODE_LISEN &&
            argval != RT_CAN_MODE_LOOPBACK &&
            argval != RT_CAN_MODE_LOOPBACKANLISEN)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->device.config.mode)
        {
            can_instance->device.config.mode = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
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
        if (argval != can_instance->device.config.baud_rate)
        {
            can_instance->device.config.baud_rate = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
            argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->device.config.privmode)
        {
            can_instance->device.config.privmode = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = can_instance->CanConfig.Instance->ESTS;
        can_instance->device.status.rcverrcnt = errtype >> 24;
        can_instance->device.status.snderrcnt = (errtype >> 16 & 0xFF);
        can_instance->device.status.lasterrtype = errtype & 0x70;
        can_instance->device.status.errcode = errtype & 0x07;

        rt_memcpy(arg, &can_instance->device.status, sizeof(can_instance->device.status));
    }
    break;
    }

    return RT_EOK;
}

static int _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct CAN_Handler *hcan;
    hcan = &((struct at32_can *) can->parent.user_data)->CanConfig;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    CanTxMsg TxMessage;
    rt_uint32_t i;

    /* Check the parameters */
    RT_ASSERT(IS_CAN_DLC(pmsg->len));

    /*check select mailbox  is empty */
    switch (1 << box_num)
    {
      case CAN_TX_MAILBOX0:
        if ((hcan->Instance->TSTS & CAN_TSTS_TSME0) != CAN_TSTS_TSME0)
        {
            /* Return function status */
            return -RT_ERROR;
        }
        break;
    case CAN_TX_MAILBOX1:
        if ((hcan->Instance->TSTS & CAN_TSTS_TSME1) != CAN_TSTS_TSME1)
        {
            /* Return function status */
            return -RT_ERROR;
        }
        break;
    case CAN_TX_MAILBOX2:
        if ((hcan->Instance->TSTS & CAN_TSTS_TSME2) != CAN_TSTS_TSME2)
        {
            /* Return function status */
            return -RT_ERROR;
        }
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    if (RT_CAN_STDID == pmsg->ide)
    {
        TxMessage.IDT = CAN_ID_STD;
        RT_ASSERT(IS_CAN_STDID(pmsg->id));
        TxMessage.StdId = pmsg->id;
    }
    else
    {
        TxMessage.IDT = CAN_ID_EXT;
        RT_ASSERT(IS_CAN_EXTID(pmsg->id));
        TxMessage.ExtId = pmsg->id;
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
        TxMessage.RTR = CAN_RTR_DATA;
    }
    else
    {
        TxMessage.RTR = CAN_RTR_REMOTE;
    }

    /* Set up the DLC */
    TxMessage.DLC = pmsg->len & 0x0FU;
    /* Set up the data field */
    TxMessage.Data[0] = (uint32_t)pmsg->data[0];
    TxMessage.Data[1] = (uint32_t)pmsg->data[1];
    TxMessage.Data[2] = (uint32_t)pmsg->data[2];
    TxMessage.Data[3] = (uint32_t)pmsg->data[3];
    TxMessage.Data[4] = (uint32_t)pmsg->data[4];
    TxMessage.Data[5] = (uint32_t)pmsg->data[5];
    TxMessage.Data[6] = (uint32_t)pmsg->data[6];
    TxMessage.Data[7] = (uint32_t)pmsg->data[7];

    CAN_Transmit(hcan->Instance, &TxMessage);
    while((CAN_TransmitStatus(hcan->Instance, box_num) != CANTXOK) && (i != 0xFFFF))
    {
        i++;
    }

    return RT_EOK;
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct CAN_Handler *hcan;
    hcan = &((struct at32_can *) can->parent.user_data)->CanConfig;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    CanRxMsg RxMessage;

    RT_ASSERT(can);

    /* get data */
    CAN_Receive(hcan->Instance, fifo, &RxMessage);

    pmsg->data[0] = RxMessage.Data[0];
    pmsg->data[1] = RxMessage.Data[1];
    pmsg->data[2] = RxMessage.Data[2];
    pmsg->data[3] = RxMessage.Data[3];
    pmsg->data[4] = RxMessage.Data[4];
    pmsg->data[5] = RxMessage.Data[5];
    pmsg->data[6] = RxMessage.Data[6];
    pmsg->data[7] = RxMessage.Data[7];

    pmsg->len = RxMessage.DLC;
    pmsg->id = RxMessage.IDT;

    if (RxMessage.IDT == CAN_ID_STD)
        pmsg->id = RxMessage.StdId;
    else
        pmsg->ide = RxMessage.ExtId;
    pmsg->rtr = RxMessage.RTR;

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
};

static void _can_rx_isr(struct rt_can_device *can, rt_uint32_t fifo)
{
    struct CAN_Handler *hcan;
    RT_ASSERT(can);
    hcan = &((struct at32_can *) can->parent.user_data)->CanConfig;

    switch (fifo)
    {
    case CAN_FIFO0:
        /* save to user list */
        if (CAN_MessagePending(hcan->Instance, CAN_FIFO0) && CAN_GetINTStatus(hcan->Instance, CAN_INT_RFP0))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        /* Check FULL flag for FIFO0 */
        if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RFFU0) && CAN_GetINTStatus(hcan->Instance, CAN_INT_RFFU0))
        {
            /* Clear FIFO0 FULL Flag */
            CAN_ClearFlag(hcan->Instance, CAN_FLAG_RFFU0);
        }

        /* Check Overrun flag for FIFO0 */
        if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RFOV0) && CAN_GetINTStatus(hcan->Instance, CAN_INT_RFOV0))
        {
            /* Clear FIFO0 Overrun Flag */
            CAN_ClearFlag(hcan->Instance, CAN_FLAG_RFOV0);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    case CAN_FIFO1:
        /* save to user list */
        if (CAN_MessagePending(hcan->Instance, CAN_FIFO1) && CAN_GetINTStatus(hcan->Instance, CAN_INT_RFP1))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        /* Check FULL flag for FIFO1 */
        if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RFFU1) && CAN_GetINTStatus(hcan->Instance, CAN_INT_RFFU1))
        {
            /* Clear FIFO1 FULL Flag */
            CAN_ClearFlag(hcan->Instance, CAN_FLAG_RFFU1);
        }

        /* Check Overrun flag for FIFO1 */
        if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RFOV1) && CAN_GetINTStatus(hcan->Instance, CAN_INT_RFOV1))
        {
            /* Clear FIFO1 Overrun Flag */
            CAN_ClearFlag(hcan->Instance, CAN_FLAG_RFOV1);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    }
}

#ifdef BSP_USING_CAN1
/**
 * @brief This function handles CAN1 TX interrupts. transmit fifo0/1/2 is empty can trigger this interrupt
 */
void USB_HP_CAN1_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    struct CAN_Handler *hcan;
    hcan = &can_instance1.CanConfig;
    if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RQCP0))
    {
        if ((hcan->Instance->TSTS & CAN_TSTS_TOK0) == CAN_TSTS_TOK0)
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        hcan->Instance->TSTS |= CAN_TSTS_RQC0;
    }
    else if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RQCP1))
    {
        if ((hcan->Instance->TSTS & CAN_TSTS_TOK1) == CAN_TSTS_TOK1)
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        hcan->Instance->TSTS |= CAN_TSTS_RQC1;
    }
    else if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RQCP2))
    {
        if ((hcan->Instance->TSTS & CAN_TSTS_TOK2) == CAN_TSTS_TOK2)
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        hcan->Instance->TSTS |= CAN_TSTS_RQC2;
    }
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&can_instance1.device, CAN_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&can_instance1.device, CAN_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 SCE interrupts.
 */
void CAN1_SCE_IRQHandler(void)
{
    rt_uint32_t errtype;
    struct CAN_Handler *hcan;

    hcan = &can_instance1.CanConfig;
    errtype = hcan->Instance->ESTS;

    rt_interrupt_enter();

    switch ((errtype & 0x70) >> 4)
    {
    case RT_CAN_BUS_BIT_PAD_ERR:
        can_instance1.device.status.bitpaderrcnt++;
        break;
    case RT_CAN_BUS_FORMAT_ERR:
        can_instance1.device.status.formaterrcnt++;
        break;
    case RT_CAN_BUS_ACK_ERR:/* attention !!! test ack err's unit is transmit unit */
        can_instance1.device.status.ackerrcnt++;
        if (!(can_instance1.CanConfig.Instance->TSTS & CAN_TSTS_TOK0))
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        else if (!(can_instance1.CanConfig.Instance->TSTS & CAN_TSTS_TOK0))
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        else if (!(can_instance1.CanConfig.Instance->TSTS & CAN_TSTS_TOK0))
            rt_hw_can_isr(&can_instance1.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        break;
    case RT_CAN_BUS_IMPLICIT_BIT_ERR:
    case RT_CAN_BUS_EXPLICIT_BIT_ERR:
        can_instance1.device.status.biterrcnt++;
        break;
    case RT_CAN_BUS_CRC_ERR:
        can_instance1.device.status.crcerrcnt++;
        break;
    }

    can_instance1.device.status.lasterrtype = errtype & 0x70;
    can_instance1.device.status.rcverrcnt = errtype >> 24;
    can_instance1.device.status.snderrcnt = (errtype >> 16 & 0xFF);
    can_instance1.device.status.errcode = errtype & 0x07;
    hcan->Instance->MSTS |= CAN_MSTS_ERIT;
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
    struct CAN_Handler *hcan;
    hcan = &can_instance2.CanConfig;
    if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RQCP0))
    {
        if ((hcan->Instance->TSTS & CAN_TSTS_TOK0) == CAN_TSTS_TOK0)
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        hcan->Instance->TSTS |= CAN_TSTS_RQC0;
    }
    else if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RQCP1))
    {
        if ((hcan->Instance->TSTS & CAN_TSTS_TOK1) == CAN_TSTS_TOK1)
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        hcan->Instance->TSTS |= CAN_TSTS_RQC1;
    }
    else if (CAN_GetFlagStatus(hcan->Instance, CAN_FLAG_RQCP2))
    {
        if ((hcan->Instance->TSTS & CAN_TSTS_TOK2) == CAN_TSTS_TOK2)
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        hcan->Instance->TSTS |= CAN_TSTS_RQC2;
    }
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX0 interrupts.
 */
void CAN2_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&can_instance2.device, CAN_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX1 interrupts.
 */
void CAN2_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&can_instance2.device, CAN_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 SCE interrupts.
 */
void CAN2_SCE_IRQHandler(void)
{
    rt_uint32_t errtype;
    struct CAN_Handler *hcan;

    hcan = &can_instance2.CanConfig;
    errtype = hcan->Instance->ESTS;

    rt_interrupt_enter();

    switch ((errtype & 0x70) >> 4)
    {
    case RT_CAN_BUS_BIT_PAD_ERR:
        can_instance2.device.status.bitpaderrcnt++;
        break;
    case RT_CAN_BUS_FORMAT_ERR:
        can_instance2.device.status.formaterrcnt++;
        break;
    case RT_CAN_BUS_ACK_ERR:
        can_instance2.device.status.ackerrcnt++;
        if (!(can_instance1.CanConfig.Instance->TSTS & CAN_TSTS_TOK0))
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        else if (!(can_instance2.CanConfig.Instance->TSTS & CAN_TSTS_TOK0))
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        else if (!(can_instance2.CanConfig.Instance->TSTS & CAN_TSTS_TOK0))
            rt_hw_can_isr(&can_instance2.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        break;
    case RT_CAN_BUS_IMPLICIT_BIT_ERR:
    case RT_CAN_BUS_EXPLICIT_BIT_ERR:
        can_instance2.device.status.biterrcnt++;
        break;
    case RT_CAN_BUS_CRC_ERR:
        can_instance2.device.status.crcerrcnt++;
        break;
    }

    can_instance2.device.status.lasterrtype = errtype & 0x70;
    can_instance2.device.status.rcverrcnt = errtype >> 24;
    can_instance2.device.status.snderrcnt = (errtype >> 16 & 0xFF);
    can_instance2.device.status.errcode = errtype & 0x07;
    hcan->Instance->MSTS |= CAN_MSTS_ERIT;
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN2 */

/**
 * @brief  Error CAN callback.
 * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void HAL_CAN_ErrorCallback(struct CAN_Handler *hcan)
{
    CAN_INTConfig(hcan->Instance, CAN_INT_TSME |
                        CAN_INT_RFP0  |
                        CAN_INT_RFFU0 |
                        CAN_INT_RFOV0 |
                        CAN_INT_RFP1  |
                        CAN_INT_RFFU1 |
                        CAN_INT_RFOV1 |
                        CAN_INT_ERG   |
                        CAN_INT_ERP   |
                        CAN_INT_LEC   |
                        CAN_INT_ERR   |
                        CAN_INT_WK, ENABLE);
}

int rt_hw_can_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#endif
    /* config default filter */
    CAN_FilterInitType filterConf = {0};
    filterConf.CAN_FilterIdHigh = 0x0000;
    filterConf.CAN_FilterIdLow = 0x0000;
    filterConf.CAN_FilterMskIdHigh = 0x0000;
    filterConf.CAN_FilterMskIdLow = 0x0000;
    filterConf.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    filterConf.CAN_FilterNumber = 0;
    filterConf.CAN_FilterMode = CAN_FilterMode_IdMask;
    filterConf.CAN_FilterScale = CAN_FilterScale_32bit;
    filterConf.CAN_FilterActivation = ENABLE;

#ifdef BSP_USING_CAN1
    filterConf.CAN_FilterNumber = 0;

    can_instance1.CanConfig.FilterConfig = filterConf;
    can_instance1.device.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&can_instance1.device,
                       can_instance1.name,
                       &_can_ops,
                       &can_instance1);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
    filterConf.CAN_FilterNumber = 0;

    can_instance2.CanConfig.FilterConfig = filterConf;
    can_instance2.device.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&can_instance2.device,
                       can_instance2.name,
                       &_can_ops,
                       &can_instance2);
#endif /* BSP_USING_CAN2 */

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
