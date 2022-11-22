/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-16     lik          first version
 */

#include "drv_can.h"

#ifdef RT_USING_CAN
#ifdef BSP_USING_CAN

//#define DRV_DEBUG
#define LOG_TAG "drv.can"
#include <drv_log.h>

#if !defined(BSP_USING_CAN0) && !defined(BSP_USING_CAN1)
#error "Please define at least one BSP_USING_CANx"
/* this driver can be disabled at menuconfig ? RT-Thread Components ? Device Drivers */
#endif

#ifdef BSP_USING_CAN0
#ifndef CAN0_CFG
#define CAN0_CFG        \
    {                   \
        .name = "can0", \
        .CANx = CAN0,   \
    }
#endif /* CAN0_CFG */
#endif /* BSP_USING_CAN0 */

#ifdef BSP_USING_CAN1
#ifndef CAN1_CFG
#define CAN1_CFG        \
    {                   \
        .name = "can1", \
        .CANx = CAN1,   \
    }
#endif /* CAN1_CFG */
#endif /* BSP_USING_CAN1 */

#define PRESCL_Pos 0
#define BS1_Pos 16
#define BS2_Pos 20
#define SJW_Pos 24
#define PRESCL_Msk (0x3FF << PRESCL_Pos)
#define BS1_Msk ((0x0F) << BS1_Pos)
#define BS2_Msk ((0x07) << BS2_Pos)
#define SJW_Msk (0x3 << SJW_Pos)

struct swm_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t config_data;
};
#define BAUD_DATA(TYPE, NO) ((can_baud_rate_tab[NO].config_data & TYPE##_Msk) >> TYPE##_Pos)

struct swm_can_cfg
{
    const char *name;
    CAN_TypeDef *CANx;
    CAN_InitStructure CAN_initstruct;
};

struct swm_can_device
{
    struct swm_can_cfg *can_cfg;
    struct rt_can_device can_device;
};
/* SystemCoreClock 152MHz(max) 150MHz不能生成CAN1MBaud */
static const struct swm_baud_rate_tab can_baud_rate_tab[] =
    {
        {CAN1MBaud, ((CAN_SJW_4tq << SJW_Pos) | (CAN_BS1_12tq << BS1_Pos) | (CAN_BS2_6tq << BS2_Pos) | (1 << PRESCL_Pos))},
        {CAN500kBaud, ((CAN_SJW_4tq << SJW_Pos) | (CAN_BS1_12tq << BS1_Pos) | (CAN_BS2_6tq << BS2_Pos) | (3 << PRESCL_Pos))},
        {CAN250kBaud, ((CAN_SJW_4tq << SJW_Pos) | (CAN_BS1_12tq << BS1_Pos) | (CAN_BS2_6tq << BS2_Pos) | (7 << PRESCL_Pos))},
        {CAN125kBaud, ((CAN_SJW_4tq << SJW_Pos) | (CAN_BS1_12tq << BS1_Pos) | (CAN_BS2_6tq << BS2_Pos) | (15 << PRESCL_Pos))},
        {CAN100kBaud, ((CAN_SJW_4tq << SJW_Pos) | (CAN_BS1_12tq << BS1_Pos) | (CAN_BS2_6tq << BS2_Pos) | (19 << PRESCL_Pos))},
        {CAN50kBaud, ((CAN_SJW_4tq << SJW_Pos) | (CAN_BS1_12tq << BS1_Pos) | (CAN_BS2_6tq << BS2_Pos) | (39 << PRESCL_Pos))},
        {CAN20kBaud, ((CAN_SJW_4tq << SJW_Pos) | (CAN_BS1_12tq << BS1_Pos) | (CAN_BS2_6tq << BS2_Pos) | (99 << PRESCL_Pos))},
        {CAN10kBaud, ((CAN_SJW_4tq << SJW_Pos) | (CAN_BS1_12tq << BS1_Pos) | (CAN_BS2_6tq << BS2_Pos) | (199 << PRESCL_Pos))}};

enum
{
#ifdef BSP_USING_CAN0
    CAN0_INDEX,
#endif
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
};

static struct swm_can_cfg swm_can_cfg[] =
    {
#ifdef BSP_USING_CAN0
        CAN0_CFG,
#endif
#ifdef BSP_USING_CAN1
        CAN1_CFG,
#endif
};

static struct swm_can_device can_obj[sizeof(swm_can_cfg) / sizeof(swm_can_cfg[0])];

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

static rt_err_t swm_can_config(struct rt_can_device *can_device, struct can_configure *cfg)
{
    struct swm_can_device *can_dev;
    rt_uint32_t baud_index;
    rt_uint32_t can_mode;

    RT_ASSERT(can_device);
    RT_ASSERT(cfg);
    can_dev = (struct swm_can_device *)can_device->parent.user_data;
    RT_ASSERT(can_dev);

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        can_mode = CAN_MODE_NORMAL;
        break;
    case RT_CAN_MODE_LISTEN:
        can_mode = CAN_MODE_LISTEN;
        break;
    case RT_CAN_MODE_LOOPBACK:
        can_mode = CAN_MODE_SELFTEST;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        can_mode = CAN_MODE_SELFTEST;
        break;
    }

    baud_index = get_can_baud_index(cfg->baud_rate);

    CAN_Close(can_dev->can_cfg->CANx); //一些关键寄存器只能在CAN关闭时设置

    can_dev->can_cfg->CANx->CR &= ~(CAN_CR_LOM_Msk | CAN_CR_STM_Msk);
    can_dev->can_cfg->CANx->CR |= (can_mode << CAN_CR_LOM_Pos);

    can_dev->can_cfg->CANx->BT1 = (0 << CAN_BT1_SAM_Pos) |
                                  (BAUD_DATA(BS1, baud_index) << CAN_BT1_TSEG1_Pos) |
                                  (BAUD_DATA(BS2, baud_index) << CAN_BT1_TSEG2_Pos);

    can_dev->can_cfg->CANx->BT0 = (BAUD_DATA(SJW, baud_index) << CAN_BT0_SJW_Pos) |
                                  ((BAUD_DATA(PRESCL, baud_index) & 0x3F) << CAN_BT0_BRP_Pos);

    can_dev->can_cfg->CANx->BT2 = ((BAUD_DATA(PRESCL, baud_index) >> 6) << CAN_BT2_BRP_Pos);

    can_dev->can_cfg->CANx->RXERR = 0; //只能在复位模式下清除
    can_dev->can_cfg->CANx->TXERR = 0;

    /* can start */
    CAN_Open(can_dev->can_cfg->CANx);

    return RT_EOK;
}

static rt_err_t swm_can_control(struct rt_can_device *can_device, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct swm_can_device *can_dev;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can_device != RT_NULL);
    can_dev = (struct swm_can_device *)can_device->parent.user_data;
    RT_ASSERT(can_dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            can_dev->can_cfg->CANx->IE &= ~(CAN_IE_RXDA_Msk | CAN_IE_RXOV_Msk);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            can_dev->can_cfg->CANx->IE &= ~CAN_IE_TXBR_Msk;
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            can_dev->can_cfg->CANx->IE &= ~(CAN_IE_ARBLOST_Msk | CAN_IE_BUSERR_Msk | CAN_IE_ERRWARN_Msk | CAN_IE_ERRPASS_Msk);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            can_dev->can_cfg->CANx->IE |= (CAN_IE_RXDA_Msk | CAN_IE_RXOV_Msk);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            can_dev->can_cfg->CANx->IE |= CAN_IE_TXBR_Msk;
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            can_dev->can_cfg->CANx->IE |= (CAN_IE_ARBLOST_Msk | CAN_IE_BUSERR_Msk | CAN_IE_ERRWARN_Msk | CAN_IE_ERRPASS_Msk);
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
    {
        rt_uint32_t filter_idx = 0;

        if (RT_NULL == arg)
        {
            /* default filter config */
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                if (filter_cfg->items[i].hdr_bank == -1)
                {
                    filter_idx = i;
                }
                else
                {
                    filter_idx = filter_cfg->items[i].hdr_bank;
                }

                if (filter_cfg->items[i].ide == RT_CAN_STDID)
                {
                    can_dev->can_cfg->CANx->AFM &= ~(1 << filter_idx);

                    can_dev->can_cfg->CANx->ACR[filter_idx] = __REV(filter_cfg->items[i].id << 5);
                    can_dev->can_cfg->CANx->AMR[filter_idx] = __REV(~(filter_cfg->items[i].mask << 5));

                    can_dev->can_cfg->CANx->AFE |= (1 << filter_idx);
                }
                else if (filter_cfg->items[i].ide == RT_CAN_EXTID)
                {
                    can_dev->can_cfg->CANx->AFM |= (1 << filter_idx);

                    can_dev->can_cfg->CANx->ACR[filter_idx] = __REV(filter_cfg->items[i].id << 3);
                    can_dev->can_cfg->CANx->AMR[filter_idx] = __REV(~(filter_cfg->items[i].mask << 3));

                    can_dev->can_cfg->CANx->AFE |= (1 << filter_idx);
                }
            }
        }
        break;
    }
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t)arg;
        if (argval != RT_CAN_MODE_NORMAL &&
            argval != RT_CAN_MODE_LISTEN &&
            argval != RT_CAN_MODE_LOOPBACK &&
            argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != can_dev->can_device.config.mode)
        {
            can_dev->can_device.config.mode = argval;
            return swm_can_config(&can_dev->can_device, &can_dev->can_device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t)arg;
        if (argval != CAN1MBaud &&
            argval != CAN800kBaud &&
            argval != CAN500kBaud &&
            argval != CAN250kBaud &&
            argval != CAN125kBaud &&
            argval != CAN100kBaud &&
            argval != CAN50kBaud &&
            argval != CAN20kBaud &&
            argval != CAN10kBaud)
        {
            return -RT_ERROR;
        }
        if (argval != can_dev->can_device.config.baud_rate)
        {
            can_dev->can_device.config.baud_rate = argval;
            return swm_can_config(&can_dev->can_device, &can_dev->can_device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t)arg;
        if (argval != RT_CAN_MODE_PRIV &&
            argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != can_dev->can_device.config.privmode)
        {
            can_dev->can_device.config.privmode = argval;
            return swm_can_config(&can_dev->can_device, &can_dev->can_device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        can_dev->can_device.status.rcverrcnt = can_dev->can_cfg->CANx->RXERR;
        can_dev->can_device.status.snderrcnt = can_dev->can_cfg->CANx->TXERR;
        can_dev->can_device.status.lasterrtype = (can_dev->can_cfg->CANx->ECC >> 6) & 0x03;
        can_dev->can_device.status.errcode = can_dev->can_cfg->CANx->ECC & 0x1F;
        rt_memcpy(arg, &can_dev->can_device.status, sizeof(can_dev->can_device.status));
    }
    break;
    }

    return RT_EOK;
}

static int swm_can_sendmsg(struct rt_can_device *can_device, const void *buf, rt_uint32_t box_num)
{
    uint32_t i;
    struct swm_can_device *can_dev;

    RT_ASSERT(can_device != RT_NULL);
    can_dev = (struct swm_can_device *)can_device->parent.user_data;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;

    if (RT_CAN_STDID == pmsg->ide)
    {
        can_dev->can_cfg->CANx->FRAME.DATA[0] = pmsg->id >> 3;
        can_dev->can_cfg->CANx->FRAME.DATA[1] = pmsg->id << 5;

        if (RT_CAN_DTR == pmsg->rtr)
        {
            can_dev->can_cfg->CANx->FRAME.INFO = (0 << CAN_INFO_FF_Pos)  |
                                                (0 << CAN_INFO_RTR_Pos) |
                                                (pmsg->len << CAN_INFO_DLC_Pos);

            for(i = 0; i < pmsg->len; i++)
            {
                can_dev->can_cfg->CANx->FRAME.DATA[i+2] = pmsg->data[i];
            }

            if(can_dev->can_cfg->CANx->CR & CAN_CR_STM_Msk)
            {
                can_dev->can_cfg->CANx->CMD = (1 << CAN_CMD_SRR_Pos);
            }
            else
            {
                can_dev->can_cfg->CANx->CMD = (1 << CAN_CMD_TXREQ_Pos);
            }
        }
        else
        {
            can_dev->can_cfg->CANx->FRAME.INFO = (0 << CAN_INFO_FF_Pos)  |
                                                (1 << CAN_INFO_RTR_Pos) |
                                                (0 << CAN_INFO_DLC_Pos);

            can_dev->can_cfg->CANx->CMD = (1 << CAN_CMD_TXREQ_Pos);
        }
    }
    else
    {
        can_dev->can_cfg->CANx->FRAME.DATA[0] = pmsg->id >> 21;
        can_dev->can_cfg->CANx->FRAME.DATA[1] = pmsg->id >> 13;
        can_dev->can_cfg->CANx->FRAME.DATA[2] = pmsg->id >>  5;
        can_dev->can_cfg->CANx->FRAME.DATA[3] = pmsg->id <<  3;

        if (RT_CAN_DTR == pmsg->rtr)
        {
            can_dev->can_cfg->CANx->FRAME.INFO = (1 << CAN_INFO_FF_Pos)  |
                                                (0 << CAN_INFO_RTR_Pos) |
                                                (pmsg->len << CAN_INFO_DLC_Pos);

            for(i = 0; i < pmsg->len; i++)
            {
                can_dev->can_cfg->CANx->FRAME.DATA[i+4] = pmsg->data[i];
            }

            if(can_dev->can_cfg->CANx->CR & CAN_CR_STM_Msk)
            {
                can_dev->can_cfg->CANx->CMD = (1 << CAN_CMD_SRR_Pos);
            }
            else
            {
                can_dev->can_cfg->CANx->CMD = (1 << CAN_CMD_TXREQ_Pos);
            }
        }
        else
        {
            can_dev->can_cfg->CANx->FRAME.INFO = (1 << CAN_INFO_FF_Pos)  |
                                                (1 << CAN_INFO_RTR_Pos) |
                                                (0 << CAN_INFO_DLC_Pos);

            can_dev->can_cfg->CANx->CMD = (1 << CAN_CMD_TXREQ_Pos);
        }
    }
    return RT_EOK;
}

static int swm_can_recvmsg(struct rt_can_device *can_device, void *buf, rt_uint32_t fifo)
{
    uint32_t i;
    struct swm_can_device *can_dev;
    RT_ASSERT(can_device != RT_NULL);
    can_dev = (struct swm_can_device *)can_device->parent.user_data;

    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;

    CAN_RXMessage CAN_RXMsg;

    /* get data */
    CAN_Receive(can_dev->can_cfg->CANx, &CAN_RXMsg);
    /* get id */
    if (CAN_RXMsg.format == CAN_FRAME_STD)
    {
        pmsg->ide = RT_CAN_STDID;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
    }
    pmsg->id = CAN_RXMsg.id;

    /* get type */
    if (CAN_RXMsg.remote == 0)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /* get len */
    pmsg->len = CAN_RXMsg.size;

    for(i = 0; i < pmsg->len; i++)
    {
        pmsg->data[i] = CAN_RXMsg.data[i];
    }

    return RT_EOK;
}

static const struct rt_can_ops swm_can_ops =
{
    .configure = swm_can_config,
    .control = swm_can_control,
    .sendmsg = swm_can_sendmsg,
    .recvmsg = swm_can_recvmsg,
};

static void swm_can_isr(struct rt_can_device *can_device)
{
    struct swm_can_device *can_dev;
    RT_ASSERT(can_device != RT_NULL);
    can_dev = (struct swm_can_device *)can_device->parent.user_data;

    uint32_t int_sr = CAN_INTStat(can_dev->can_cfg->CANx);

    if(int_sr & CAN_IF_RXDA_Msk)
    {
        rt_hw_can_isr(can_device, RT_CAN_EVENT_RX_IND);
    }
    else if (int_sr & CAN_IF_RXOV_Msk)
    {
        rt_hw_can_isr(can_device, RT_CAN_EVENT_RXOF_IND);
    }
    else if (int_sr & CAN_IF_TXBR_Msk)
    {
        rt_hw_can_isr(can_device, RT_CAN_EVENT_TX_DONE);
    }
    else if (int_sr & CAN_IE_ERRWARN_Msk)
    {
    }
    else if (int_sr & CAN_IE_ERRPASS_Msk)
    {
    }
    else if (int_sr & CAN_IE_ARBLOST_Msk)
    {
    }
    else if (int_sr & CAN_IE_BUSERR_Msk)
    {
    }
}

#ifdef BSP_USING_CAN0
/**
 * @brief This function handles CAN0 interrupts.
 */
void CAN0_Handler(void)
{
    rt_interrupt_enter();
    swm_can_isr(&(can_obj[CAN0_INDEX].can_device));
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN0 */

#ifdef BSP_USING_CAN1
/**
 * @brief This function handles CAN1 interrupts.
 */
void CAN1_Handler(void)
{
    rt_interrupt_enter();
    swm_can_isr(&(can_obj[CAN0_INDEX].can_device));
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN1 */

int swm_can_init(void)
{
    int i = 0;
    int result = RT_EOK;

    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 16;
#endif

#ifdef BSP_USING_CAN0
    PORT_Init(PORTB, PIN5, PORTB_PIN5_CAN0_RX, 1);
    PORT_Init(PORTB, PIN4, PORTB_PIN4_CAN0_TX, 0);
    SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_CAN0_Pos);
    NVIC_EnableIRQ(CAN0_IRQn);
#endif

#ifdef BSP_USING_CAN1
    PORT_Init(PORTB, PIN3, PORTB_PIN3_CAN1_RX, 1);
    PORT_Init(PORTB, PIN2, PORTB_PIN2_CAN1_TX, 0);
    SYS->CLKEN1 |= (0x01 << SYS_CLKEN1_CAN1_Pos);
    NVIC_EnableIRQ(CAN1_IRQn);
#endif

    for (i = 0; i < sizeof(swm_can_cfg) / sizeof(swm_can_cfg[0]); i++)
    {
        can_obj[i].can_device.config = config;
        can_obj[i].can_cfg = &swm_can_cfg[i];
        result = rt_hw_can_register(&can_obj[i].can_device,
                                        can_obj[i].can_cfg->name,
                                        &swm_can_ops,
                                        &can_obj[i]);
        if (result != RT_EOK)
        {
            LOG_E("%s register fail.", can_obj[i].can_cfg->name);
        }
        else
        {
            LOG_D("%s register success.", can_obj[i].can_cfg->name);
        }
    }

    return result;
    return 0;
}

INIT_BOARD_EXPORT(swm_can_init);

#endif /* BSP_USING_CAN */
#endif /* RT_USING_CAN */
