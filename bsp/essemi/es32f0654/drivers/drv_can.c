/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-11-09     wangyq        the first version
 */

#include "drv_can.h"

#ifdef BSP_USING_CAN

static struct es32f0_can can;

/* attention !!! baud calculation example: Pclk / ((sjw + seg1 + seg2) * psc)  48 / ((1 + 3 + 2) * 8) = 1MHz */
static const struct es32f0_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud, 8},
    {CAN800kBaud, 10},
    {CAN500kBaud, 16},
    {CAN250kBaud, 32},
    {CAN125kBaud, 64},
    {CAN100kBaud, 80},
    {CAN50kBaud, 160},
    {CAN20kBaud, 400},
    {CAN10kBaud, 800}
};

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

static rt_err_t _can_config(struct rt_can_device *can_device, struct can_configure *cfg)
{
    struct es32f0_can *drv_can;
    rt_uint32_t baud_index;

    RT_ASSERT(can_device);
    RT_ASSERT(cfg);
    drv_can = (struct es32f0_can *)can_device->parent.user_data;
    RT_ASSERT(drv_can);

    drv_can->CanHandle.perh = CAN0;
    drv_can->CanHandle.init.ttcm = DISABLE;
    drv_can->CanHandle.init.abom = ENABLE;
    drv_can->CanHandle.init.awk = DISABLE;
    drv_can->CanHandle.init.artx = DISABLE;
    drv_can->CanHandle.init.rfom   = DISABLE;
    drv_can->CanHandle.init.txmp   = ENABLE;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        drv_can->CanHandle.init.mode = CAN_MODE_NORMAL;
        break;
    case RT_CAN_MODE_LISEN:
        drv_can->CanHandle.init.mode = CAN_MODE_SILENT;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_can->CanHandle.init.mode = CAN_MODE_LOOPBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        drv_can->CanHandle.init.mode = CAN_MODE_SILENT_LOOPBACK;
        break;
    }

    baud_index = get_can_baud_index(cfg->baud_rate);
    drv_can->CanHandle.init.sjw = CAN_SJW_1;
    drv_can->CanHandle.init.seg1 = CAN_SEG1_3;
    drv_can->CanHandle.init.seg2 = CAN_SEG2_2;
    drv_can->CanHandle.init.psc = can_baud_rate_tab[baud_index].config_data;
    /* init can */
    if (ald_can_init(&drv_can->CanHandle) != OK)
    {
        return -RT_ERROR;
    }
    /* default filter config */
    ald_can_filter_config(&drv_can->CanHandle, &drv_can->FilterConfig);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can_device, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct es32f0_can *drv_can;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can_device != RT_NULL);
    drv_can = (struct es32f0_can *)can_device->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            ald_can_interrupt_config(&drv_can->CanHandle, (can_it_t)(CAN_IT_FP0 | CAN_IT_FF0 | CAN_IT_FOV0 |
                                     CAN_IT_FP1 | CAN_IT_FF1 | CAN_IT_FOV1), DISABLE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_TXM, DISABLE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            ald_can_interrupt_config(&drv_can->CanHandle, (can_it_t)(CAN_IT_WARN | CAN_IT_PERR | CAN_IT_BOF |
                                     CAN_IT_PRERR | CAN_IT_ERR), DISABLE);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            NVIC_SetPriority(CAN0_IRQn, 1);
            NVIC_EnableIRQ(CAN0_IRQn);

            ald_can_interrupt_config(&drv_can->CanHandle, (can_it_t)(CAN_IT_FP0 | CAN_IT_FP1), ENABLE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            NVIC_SetPriority(CAN0_IRQn, 1);
            NVIC_EnableIRQ(CAN0_IRQn);

            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_TXM, ENABLE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            NVIC_SetPriority(CAN0_IRQn, 1);
            NVIC_EnableIRQ(CAN0_IRQn);

            ald_can_interrupt_config(&drv_can->CanHandle, (can_it_t)(CAN_IT_WARN | CAN_IT_PERR | CAN_IT_BOF |
                                     CAN_IT_PRERR | CAN_IT_ERR), ENABLE);
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL == arg)
        {
            /* default filter config */
            ald_can_filter_config(&drv_can->CanHandle, &drv_can->FilterConfig);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                drv_can->FilterConfig.number = filter_cfg->items[i].hdr;
                drv_can->FilterConfig.id_high = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                drv_can->FilterConfig.id_low = ((filter_cfg->items[i].id << 3) |
                                                (filter_cfg->items[i].ide << 2) |
                                                (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                drv_can->FilterConfig.mask_id_high = (filter_cfg->items[i].mask >> 16) & 0xFFFF;
                drv_can->FilterConfig.mask_id_low = filter_cfg->items[i].mask & 0xFFFF;
                drv_can->FilterConfig.mode = (can_filter_mode_t)filter_cfg->items[i].mode;
                /* Filter conf */
                ald_can_filter_config(&drv_can->CanHandle, &drv_can->FilterConfig);
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
        if (argval != drv_can->device.config.mode)
        {
            drv_can->device.config.mode = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
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
            return _can_config(&drv_can->device, &drv_can->device.config);
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
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = drv_can->CanHandle.perh->ERRSTAT;
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

static int _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    can_handle_t *h_can;
    h_can = &((struct es32f0_can *) can->parent.user_data)->CanHandle;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    can_tx_msg_t txheader = {0};
    can_state_t state = h_can->state;

    /* Check the parameters */
    RT_ASSERT(IS_CAN_DATA_LEN(pmsg->len));

    if ((state == CAN_STATE_READY) ||
            (state == CAN_STATE_BUSY_RX))
    {
        /*check select mailbox  is empty */
        switch (1 << box_num)
        {
        case CAN_TX_MAILBOX_0:
            if (ald_can_get_flag_status(h_can, CAN_FLAG_TXM0) != SET)
            {
                /* Change CAN state */
                h_can->state = CAN_STATE_ERROR;
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        case CAN_TX_MAILBOX_1:
            if (ald_can_get_flag_status(h_can, CAN_FLAG_TXM1) != SET)
            {
                /* Change CAN state */
                h_can->state = CAN_STATE_ERROR;
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        case CAN_TX_MAILBOX_2:
            if (ald_can_get_flag_status(h_can, CAN_FLAG_TXM2) != SET)
            {
                /* Change CAN state */
                h_can->state = CAN_STATE_ERROR;
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
            txheader.type = CAN_ID_STD;
            RT_ASSERT(IS_CAN_STDID(pmsg->id));
            txheader.std = pmsg->id;
        }
        else
        {
            txheader.type = CAN_ID_EXT;
            RT_ASSERT(IS_CAN_EXTID(pmsg->id));
            txheader.ext = pmsg->id;
        }

        if (RT_CAN_DTR == pmsg->rtr)
        {
            txheader.rtr = CAN_RTR_DATA;
        }
        else
        {
            txheader.rtr = CAN_RTR_REMOTE;
        }
        /* clear TIR */
        h_can->perh->TxMailBox[box_num].TXID &= CAN_TXID0_TXMREQ_MSK;
        /* Set up the Id */
        if (RT_CAN_STDID == pmsg->ide)
        {
            h_can->perh->TxMailBox[box_num].TXID |= (txheader.std << CAN_TXID0_STDID_POSS) | txheader.rtr;
        }
        else
        {
            h_can->perh->TxMailBox[box_num].TXID |= (txheader.ext << CAN_TXID0_EXID_POSS) | txheader.type | txheader.rtr;
        }
        /* Set up the DLC */
        h_can->perh->TxMailBox[box_num].TXFCON = pmsg->len & 0x0FU;
        /* Set up the data field */
        WRITE_REG(h_can->perh->TxMailBox[box_num].TXDH,
                  ((uint32_t)pmsg->data[7] << CAN_TXDH0_BYTE7_POSS) |
                  ((uint32_t)pmsg->data[6] << CAN_TXDH0_BYTE6_POSS) |
                  ((uint32_t)pmsg->data[5] << CAN_TXDH0_BYTE5_POSS) |
                  ((uint32_t)pmsg->data[4] << CAN_TXDH0_BYTE4_POSS));
        WRITE_REG(h_can->perh->TxMailBox[box_num].TXDL,
                  ((uint32_t)pmsg->data[3] << CAN_TXDL0_BYTE3_POSS) |
                  ((uint32_t)pmsg->data[2] << CAN_TXDL0_BYTE2_POSS) |
                  ((uint32_t)pmsg->data[1] << CAN_TXDL0_BYTE1_POSS) |
                  ((uint32_t)pmsg->data[0] << CAN_TXDL0_BYTE0_POSS));
        /* Request transmission */
        SET_BIT(h_can->perh->TxMailBox[box_num].TXID, CAN_TXID0_TXMREQ_MSK);

        return RT_EOK;
    }
    else
    {
        /* Update error code */
        h_can->err |= 0x00040000U;

        return -RT_ERROR;
    }
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    can_handle_t *h_can;
    struct rt_can_msg *pmsg;
    can_rx_msg_t rxheader = {0};

    RT_ASSERT(can);

    h_can = &((struct es32f0_can *)can->parent.user_data)->CanHandle;
    pmsg = (struct rt_can_msg *) buf;

    /* get data */
    if (ald_can_recv(h_can, (can_rx_fifo_t)fifo, &rxheader, 0xFFFF) != OK)
        return -RT_ERROR;
    pmsg->data[0] = rxheader.data[0];
    pmsg->data[1] = rxheader.data[1];
    pmsg->data[2] = rxheader.data[2];
    pmsg->data[3] = rxheader.data[3];
    pmsg->data[4] = rxheader.data[4];
    pmsg->data[5] = rxheader.data[5];
    pmsg->data[6] = rxheader.data[6];
    pmsg->data[7] = rxheader.data[7];

    /* get id */
    if (CAN_ID_STD == rxheader.type)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = rxheader.std;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = rxheader.ext;
    }
    /* get type */
    if (CAN_RTR_DATA == rxheader.rtr)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /* get len */
    pmsg->len = rxheader.len;
    /* get hdr */
    pmsg->hdr = (rxheader.fmi + 1) >> 1;

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
    can_handle_t *h_can;
    RT_ASSERT(can);
    h_can = &((struct es32f0_can *) can->parent.user_data)->CanHandle;

    switch (fifo)
    {
    case CAN_RX_FIFO0:
        /* Check Overrun flag for FIFO0 */
        if (ald_can_get_flag_status(h_can, CAN_FLAG_FOV0) && ald_can_get_it_status(h_can, CAN_IT_FOV0))
        {
            /* Clear FIFO0 Overrun Flag */
            ald_can_clear_flag_status(h_can, CAN_FLAG_FOV0);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        /* RX interrupt */
        else
        {
            /* save to user list */
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);

            /* Clear FIFO0 rx Flag */
            SET_BIT(h_can->perh->RXF0, CAN_RXF0_FREE_MSK);
        }
        break;
    case CAN_RX_FIFO1:
        /* Check Overrun flag for FIFO1 */
        if (ald_can_get_flag_status(h_can, CAN_FLAG_FOV1) && ald_can_get_it_status(h_can, CAN_IT_FOV1))
        {
            /* Clear FIFO1 Overrun Flag */
            ald_can_clear_flag_status(h_can, CAN_FLAG_FOV1);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        /* RX interrupt */
        else
        {
            /* save to user list */
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);

            /* Clear FIFO0 rx Flag */
            SET_BIT(h_can->perh->RXF1, CAN_RXF1_FREE_MSK);
        }
        break;
    }
}

/**
 * @brief This function handles CAN interrupts.
 */
void CAN0_Handler(void)
{
    rt_interrupt_enter();

    rt_uint32_t errtype;
    can_handle_t *h_can;
    h_can = &can.CanHandle;

    /* RX FIFO0 interrupt */
    if ((ald_can_get_it_status(h_can, CAN_IT_FP0)) && (CAN_RX_MSG_PENDING(h_can, CAN_RX_FIFO0) != 0))
    {
        _can_rx_isr(&can.device, CAN_RX_FIFO0);
    }

    /* RX FIFO1 interrupt */
    if ((ald_can_get_it_status(h_can, CAN_IT_FP1)) && (CAN_RX_MSG_PENDING(h_can, CAN_RX_FIFO1) != 0))
    {
        _can_rx_isr(&can.device, CAN_RX_FIFO1);
    }

    /* TX interrupt. transmit fifo0/1/2 is empty can trigger this interrupt */
    if (ald_can_get_flag_status(h_can, CAN_FLAG_M0REQC) && ald_can_get_it_status(h_can, CAN_IT_TXM))
    {
        if (ald_can_get_flag_status(h_can, CAN_FLAG_M0TXC))
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* Clear transmission status flag M0REQC */
        ald_can_clear_flag_status(h_can, CAN_FLAG_M0REQC);
    }
    else if (ald_can_get_flag_status(h_can, CAN_FLAG_M1REQC) && ald_can_get_it_status(h_can, CAN_IT_TXM))
    {
        if (ald_can_get_flag_status(h_can, CAN_FLAG_M1TXC))
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        ald_can_clear_flag_status(h_can, CAN_FLAG_M1REQC);
    }
    else if (ald_can_get_flag_status(h_can, CAN_FLAG_M2REQC) && ald_can_get_it_status(h_can, CAN_IT_TXM))
    {
        if (ald_can_get_flag_status(h_can, CAN_FLAG_M2REQC))
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        ald_can_clear_flag_status(h_can, CAN_FLAG_M2REQC);
    }

    /* CAN error interrupt */
    if (ald_can_get_flag_status(h_can, CAN_FLAG_ERR) && ald_can_get_it_status(h_can, CAN_IT_ERR))
    {
        errtype = h_can->perh->ERRSTAT;
        switch ((errtype & 0x70) >> 4)
        {
        case RT_CAN_BUS_BIT_PAD_ERR:
            can.device.status.bitpaderrcnt++;
            break;
        case RT_CAN_BUS_FORMAT_ERR:
            can.device.status.formaterrcnt++;
            break;
        case RT_CAN_BUS_ACK_ERR:/* attention !!! test ack err's unit is transmit unit */
            can.device.status.ackerrcnt++;
            if (!READ_BIT(can.CanHandle.perh->TXSTAT, CAN_FLAG_M0TXC))
                rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
            else if (!READ_BIT(can.CanHandle.perh->TXSTAT, CAN_FLAG_M0TXC))
                rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
            else if (!READ_BIT(can.CanHandle.perh->TXSTAT, CAN_FLAG_M0TXC))
                rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
            break;
        case RT_CAN_BUS_IMPLICIT_BIT_ERR:
        case RT_CAN_BUS_EXPLICIT_BIT_ERR:
            can.device.status.biterrcnt++;
            break;
        case RT_CAN_BUS_CRC_ERR:
            can.device.status.crcerrcnt++;
            break;
        }

        can.device.status.lasterrtype = errtype & 0x70;
        can.device.status.rcverrcnt = errtype >> 24;
        can.device.status.snderrcnt = (errtype >> 16 & 0xFF);
        can.device.status.errcode = errtype & 0x07;
        h_can->perh->IFC |= CAN_IFC_ERRIFC_MSK;
    }

    rt_interrupt_leave();
}

int rt_hw_can_init(void)
{
    gpio_init_t h_gpio;
    struct can_configure config = CANDEFAULTCONFIG;

    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#endif

    /* Initialize can common pin */
    h_gpio.odos = GPIO_PUSH_PULL;
    h_gpio.pupd = GPIO_PUSH_UP;
    h_gpio.odrv = GPIO_OUT_DRIVE_NORMAL;
    h_gpio.flt  = GPIO_FILTER_DISABLE;
    h_gpio.type = GPIO_TYPE_TTL;
    h_gpio.func = GPIO_FUNC_4;

    /* Initialize can rx pin */
    h_gpio.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOA, GPIO_PIN_11, &h_gpio);

    /* Initialize can tx pin */
    h_gpio.mode = GPIO_MODE_OUTPUT;
    ald_gpio_init(GPIOA, GPIO_PIN_12, &h_gpio);

    /* config default filter */
    can_filter_t filter = {0};
    filter.id_high = 0x0000;
    filter.id_low = 0x0000;
    filter.mask_id_high = 0x0000;
    filter.mask_id_low = 0x0000;
    filter.fifo = CAN_FILTER_FIFO0;
    filter.number = 0;
    filter.mode = CAN_FILTER_MODE_MASK;
    filter.scale = CAN_FILTER_SCALE_32;
    filter.active = ENABLE;
    filter.bank_number = 14;

    can.FilterConfig = filter;
    can.device.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&can.device, "can", &_can_ops, &can);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */
