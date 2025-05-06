/*
 * File      : drv_can.c
 * This file is part of RT-Thread RTOS
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2025-18-03     Dmitriy Chernov      first implementation for GD32F4xx
 */

#include "drv_can.h"
#include "string.h"

#ifdef BSP_USING_CAN

#define LOG_TAG    "can_drv"
#include <drv_log.h>

#if defined(GD32F405) || defined(GD32F407) /* 42MHz(max) */
static const struct gd32_baudrate_tbl can_baudrate_tbl[] =
{
    {CAN1MBaud,     CAN_BT_SJW_1TQ, CAN_BT_BS1_11TQ, CAN_BT_BS2_2TQ, 3},
    {CAN800kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 5},
    {CAN500kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_11TQ, CAN_BT_BS2_2TQ, 6},
    {CAN250kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_11TQ, CAN_BT_BS2_2TQ, 12},
    {CAN125kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_11TQ, CAN_BT_BS2_2TQ, 24},
    {CAN100kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_11TQ, CAN_BT_BS2_2TQ, 30},
    {CAN50kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_11TQ, CAN_BT_BS2_2TQ, 60},
    {CAN20kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_11TQ, CAN_BT_BS2_2TQ, 150},
    {CAN10kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_11TQ, CAN_BT_BS2_2TQ, 300},
};
#elif defined(GD32F425) || defined(GD32F427) || defined(GD32F450) /* 50MHz(max) */
static const struct gd32_baudrate_tbl can_baudrate_tbl[] =
{
    {CAN1MBaud,     CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 5},
    {CAN800kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_12TQ, CAN_BT_BS2_2TQ, 4},
    {CAN500kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 10},
    {CAN250kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 20},
    {CAN125kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 40},
    {CAN100kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 50},
    {CAN50kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 100},
    {CAN20kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 250},
    {CAN10kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_8TQ,  CAN_BT_BS2_1TQ, 500},
};
#elif defined(GD32F470) /* 60MHz(max) */
static const struct gd32_baudrate_tbl can_baudrate_tbl[] =
{
    {CAN1MBaud,     CAN_BT_SJW_1TQ, CAN_BT_BS1_12TQ, CAN_BT_BS2_2TQ, 4},
    {CAN800kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_12TQ, CAN_BT_BS2_2TQ, 5},
    {CAN500kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_12TQ, CAN_BT_BS2_2TQ, 8},
    {CAN250kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_13TQ, CAN_BT_BS2_2TQ, 15},
    {CAN125kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_13TQ, CAN_BT_BS2_2TQ, 30},
    {CAN100kBaud,   CAN_BT_SJW_1TQ, CAN_BT_BS1_12TQ, CAN_BT_BS2_2TQ, 40},
    {CAN50kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_13TQ, CAN_BT_BS2_2TQ, 75},
    {CAN20kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_13TQ, CAN_BT_BS2_2TQ, 200},
    {CAN10kBaud,    CAN_BT_SJW_1TQ, CAN_BT_BS1_13TQ, CAN_BT_BS2_2TQ, 375},
};
#else
    #error "CAN driver not implemented for selected device"
#endif

#ifdef BSP_USING_CAN0
static struct gd32_can_device dev_can0 =
{
    .name = "can0",
    .can_x = CAN0,
};
#endif

#ifdef BSP_USING_CAN1
static struct gd32_can_device dev_can1 =
{
    "can1",
    .can_x = CAN1,
};
#endif

static const struct gd32_can gd32_can_gpio[] =
{
#ifdef BSP_USING_CAN0
    {
        .can_clk = RCU_CAN0,
        .alt_func_num = GPIO_AF_9,
#if defined BSP_CAN0_TX_PA12
        .tx_clk = RCU_GPIOA,
        .tx_pin = GET_PIN(A, 12),
#elif defined BSP_CAN0_TX_PB9
        .tx_clk = RCU_GPIOB,
        .tx_pin = GET_PIN(B, 9),
#elif defined BSP_CAN0_TX_PD1
        .tx_clk = RCU_GPIOD,
        .tx_pin = GET_PIN(D, 1),
#elif defined BSP_CAN0_TX_PH13
        .tx_clk = RCU_GPIOH,
        .tx_pin = GET_PIN(H, 13),
#else
    #error "Select CAN0 tx pin"
#endif
#if defined BSP_CAN0_RX_PA11
        .rx_clk = RCU_GPIOA,
        .rx_pin = GET_PIN(A, 11),
#elif defined BSP_CAN0_RX_PB8
        .rx_clk = RCU_GPIOB,
        .rx_pin = GET_PIN(B, 8),
#elif defined BSP_CAN0_RX_PD0
        .rx_clk = RCU_GPIOD,
        .rx_pin = GET_PIN(D, 0),
#elif defined BSP_CAN0_RX_PI9
        .rx_clk = RCU_GPIOI,
        .rx_pin = GET_PIN(I, 9),
#else
    #error "Select CAN0 rx pin"
#endif
    },
#endif

#ifdef BSP_USING_CAN1
    {
        .can_clk = RCU_CAN1,
        .alt_func_num = GPIO_AF_9,
#if defined BSP_CAN1_TX_PB6
        .tx_clk = RCU_GPIOB,
        .tx_pin = GET_PIN(B, 6),
#elif defined BSP_CAN1_TX_PB13
        .tx_clk = RCU_GPIOB,
        .tx_pin = GET_PIN(B, 13),
#else
    #error "Select CAN1 tx pin"
#endif
#if defined BSP_CAN1_RX_PB5
        .rx_clk = RCU_GPIOB,
        .rx_pin = GET_PIN(B, 5),
#elif defined BSP_CAN1_RX_PB12
        .rx_clk = RCU_GPIOB,
        .rx_pin = GET_PIN(B, 12),
#else
    #error "Select CAN1 rx pin"
#endif
    },
#endif
};

static void gd32_can_gpio_init(void)
{
    for (rt_uint32_t i = 0; i < sizeof(gd32_can_gpio) / sizeof(gd32_can_gpio[0]); i++)
    {
        rcu_periph_clock_enable(gd32_can_gpio[i].can_clk);
        rcu_periph_clock_enable(gd32_can_gpio[i].tx_clk);
        rcu_periph_clock_enable(gd32_can_gpio[i].rx_clk);

#if defined SOC_SERIES_GD32F4xx
        gpio_af_set(PIN_GDPORT(gd32_can_gpio[i].tx_pin), gd32_can_gpio[i].alt_func_num, PIN_GDPIN(gd32_can_gpio[i].tx_pin));
        gpio_af_set(PIN_GDPORT(gd32_can_gpio[i].rx_pin), gd32_can_gpio[i].alt_func_num, PIN_GDPIN(gd32_can_gpio[i].rx_pin));

        gpio_output_options_set(PIN_GDPORT(gd32_can_gpio[i].tx_pin), GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_GDPIN(gd32_can_gpio[i].tx_pin));
        gpio_output_options_set(PIN_GDPORT(gd32_can_gpio[i].rx_pin), GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_GDPIN(gd32_can_gpio[i].rx_pin));

        gpio_mode_set(PIN_GDPORT(gd32_can_gpio[i].tx_pin), GPIO_MODE_AF, GPIO_PUPD_NONE, PIN_GDPIN(gd32_can_gpio[i].tx_pin));
        gpio_mode_set(PIN_GDPORT(gd32_can_gpio[i].rx_pin), GPIO_MODE_AF, GPIO_PUPD_NONE, PIN_GDPIN(gd32_can_gpio[i].rx_pin));
#else
        gpio_init(PIN_GDPORT(gd32_can_gpio[i].tx_pin), GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, PIN_GDPIN(gd32_can_gpio[i].tx_pin));
        gpio_init(PIN_GDPORT(gd32_can_gpio[i].rx_pin), GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, PIN_GDPIN(gd32_can_gpio[i].rx_pin));
#endif
    }
}

static rt_uint32_t get_can_baudrate_index(rt_uint32_t baudrate)
{
    rt_uint32_t len = sizeof(can_baudrate_tbl) / sizeof(can_baudrate_tbl[0]);
    for (rt_uint32_t index = 0; index < len; index++)
    {
        if (can_baudrate_tbl[index].baudrate == baudrate)
        {
            return index;
        }
    }

    return 0; /* default baudrate is CAN1MBaud */
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    can_parameter_struct can_init_struct;
    can_struct_para_init(CAN_INIT_STRUCT, &can_init_struct);

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    RT_ASSERT(can_dev != RT_NULL);

    can_deinit(can_dev->can_x);

    can_init_struct.time_triggered = DISABLE;
    can_init_struct.auto_bus_off_recovery = ENABLE;
    can_init_struct.auto_wake_up = ENABLE;
    can_init_struct.auto_retrans = DISABLE;
    can_init_struct.rec_fifo_overwrite = DISABLE;
    can_init_struct.trans_fifo_order = DISABLE;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        can_init_struct.working_mode = CAN_NORMAL_MODE;
        break;
    case RT_CAN_MODE_LISTEN:
        can_init_struct.working_mode = CAN_SILENT_MODE;
        break;
    case RT_CAN_MODE_LOOPBACK:
        can_init_struct.working_mode = CAN_LOOPBACK_MODE;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        can_init_struct.working_mode = CAN_SILENT_LOOPBACK_MODE;
        break;
    }

    rt_uint32_t baudrate_index = get_can_baudrate_index(cfg->baud_rate);
    can_init_struct.resync_jump_width = can_baudrate_tbl[baudrate_index].sjw;
    can_init_struct.time_segment_1 = can_baudrate_tbl[baudrate_index].tseg1;
    can_init_struct.time_segment_2 = can_baudrate_tbl[baudrate_index].tseg2;
    can_init_struct.prescaler = can_baudrate_tbl[baudrate_index].prescaler;
    if (can_init(can_dev->can_x, &can_init_struct) != SUCCESS)
    {
        return -RT_ERROR;
    }

    can_filter_init(&can_dev->filter_config);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    RT_ASSERT(can_dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
#ifdef CAN0
            if (CAN0 == can_dev->can_x)
            {
                nvic_irq_disable(CAN0_RX0_IRQn);
                nvic_irq_disable(CAN0_RX1_IRQn);
            }
#endif
#ifdef CAN1
            if (CAN1 == can_dev->can_x)
            {
                nvic_irq_disable(CAN1_RX0_IRQn);
                nvic_irq_disable(CAN1_RX1_IRQn);
            }
#endif
            can_interrupt_disable(can_dev->can_x, CAN_INT_RFNE0);
            can_interrupt_disable(can_dev->can_x, CAN_INT_RFF0);
            can_interrupt_disable(can_dev->can_x, CAN_INT_RFO0);
            can_interrupt_disable(can_dev->can_x, CAN_INT_RFNE1);
            can_interrupt_disable(can_dev->can_x, CAN_INT_RFF1);
            can_interrupt_disable(can_dev->can_x, CAN_INT_RFO1);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
#ifdef CAN0
            if (CAN0 == can_dev->can_x)
            {
                nvic_irq_disable(CAN0_TX_IRQn);
            }
#endif
#ifdef CAN1
            if (CAN1 == can_dev->can_x)
            {
                nvic_irq_disable(CAN1_TX_IRQn);
            }
#endif
            can_interrupt_disable(can_dev->can_x, CAN_INT_TME);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
#ifdef CAN0
            if (CAN0 == can_dev->can_x)
            {
                nvic_irq_disable(CAN0_EWMC_IRQn);
            }
#endif
#ifdef CAN1
            if (CAN1 == can_dev->can_x)
            {
                nvic_irq_disable(CAN1_EWMC_IRQn);
            }
#endif
            can_interrupt_disable(can_dev->can_x, CAN_INT_WERR);
            can_interrupt_disable(can_dev->can_x, CAN_INT_PERR);
            can_interrupt_disable(can_dev->can_x, CAN_INT_BO);
            can_interrupt_disable(can_dev->can_x, CAN_INT_ERRN);
            can_interrupt_disable(can_dev->can_x, CAN_INT_ERR);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            can_interrupt_enable(can_dev->can_x, CAN_INT_RFNE0);
            can_interrupt_enable(can_dev->can_x, CAN_INT_RFF0);
            can_interrupt_enable(can_dev->can_x, CAN_INT_RFO0);
            can_interrupt_enable(can_dev->can_x, CAN_INT_RFNE1);
            can_interrupt_enable(can_dev->can_x, CAN_INT_RFF1);
            can_interrupt_enable(can_dev->can_x, CAN_INT_RFO1);
#ifdef CAN0
            if (CAN0 == can_dev->can_x)
            {
                nvic_irq_enable(CAN0_RX0_IRQn, 1, 0);
                nvic_irq_enable(CAN0_RX1_IRQn, 1, 0);
            }
#endif
#ifdef CAN1
            if (CAN1 == can_dev->can_x)
            {
                nvic_irq_enable(CAN1_RX0_IRQn, 1, 0);
                nvic_irq_enable(CAN1_RX1_IRQn, 1, 0);
            }
#endif
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            can_interrupt_enable(can_dev->can_x, CAN_INT_TME);
#ifdef CAN0
            if (CAN0 == can_dev->can_x)
            {
                nvic_irq_enable(CAN0_TX_IRQn, 1, 0);
            }
#endif
#ifdef CAN1
            if (CAN1 == can_dev->can_x)
            {
                nvic_irq_enable(CAN1_TX_IRQn, 1, 0);
            }
#endif
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            can_interrupt_enable(can_dev->can_x, CAN_INT_WERR);
            can_interrupt_enable(can_dev->can_x, CAN_INT_PERR);
            can_interrupt_enable(can_dev->can_x, CAN_INT_BO);
            can_interrupt_enable(can_dev->can_x, CAN_INT_ERRN);
            can_interrupt_enable(can_dev->can_x, CAN_INT_ERR);
#ifdef CAN0
            if (CAN0 == can_dev->can_x)
            {
                nvic_irq_enable(CAN0_EWMC_IRQn, 1, 0);
            }
#endif
#ifdef CAN1
            if (CAN1 == can_dev->can_x)
            {
                nvic_irq_enable(CAN1_EWMC_IRQn, 1, 0);
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
        rt_uint32_t mask_l_tail = 0;  /*CAN_FxR2 bit [2:0]*/

        if (RT_NULL == arg)
        {
            /* default filter config */
            can_filter_init(&can_dev->filter_config);
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
                    if (rt_strcmp(can_dev->name, "can0") == 0)
                    {
                        /* can0 banks 0~13 */
                        can_dev->filter_config.filter_number = i;
                    }
                    else if (rt_strcmp(can_dev->name, "can1") == 0)
                    {
                        /* can1 banks 14~27 */
                        can_dev->filter_config.filter_number = i + 14;
                    }
                }
                else
                {
                    /* use user-defined filter bank settings */
                    can_dev->filter_config.filter_number = filter_cfg->items[i].hdr_bank;
                }

                if (filter_cfg->items[i].mode == CAN_FILTERMODE_MASK)
                {
                    mask_l_tail = 0x06;
                }
                else if (filter_cfg->items[i].mode == CAN_FILTERMODE_LIST)
                {
                    mask_l_tail = (filter_cfg->items[i].ide << 2) |
                                  (filter_cfg->items[i].rtr << 1);
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
                can_dev->filter_config.filter_list_high = id_h;
                can_dev->filter_config.filter_list_low = id_l;
                can_dev->filter_config.filter_mask_high = mask_h;
                can_dev->filter_config.filter_mask_low = mask_l;

                can_dev->filter_config.filter_mode = filter_cfg->items[i].mode;
                can_dev->filter_config.filter_fifo_number = filter_cfg->items[i].rxfifo;/*rxfifo = CAN_RX_FIFO0/CAN_RX_FIFO1*/
                /* Filter conf */
                can_filter_init(&can_dev->filter_config);
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
        if (argval != can_dev->device.config.mode)
        {
            can_dev->device.config.mode = argval;
            return _can_config(&can_dev->device, &can_dev->device.config);
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
        if (argval != can_dev->device.config.baud_rate)
        {
            can_dev->device.config.baud_rate = argval;
            return _can_config(&can_dev->device, &can_dev->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != can_dev->device.config.privmode)
        {
            can_dev->device.config.privmode = argval;
            return _can_config(&can_dev->device, &can_dev->device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = CAN_STAT(can_dev->can_x);
        can_dev->device.status.rcverrcnt = errtype >> 24;
        can_dev->device.status.snderrcnt = (errtype >> 16 & 0xFF);
        can_dev->device.status.lasterrtype = errtype & 0x70;
        can_dev->device.status.errcode = errtype & 0x07;

        rt_memcpy(arg, &can_dev->device.status, sizeof(can_dev->device.status));
        break;
    }
    }

    return RT_EOK;
}

static int _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    RT_ASSERT(can);

    can_trasnmit_message_struct transmit_message;
    can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &transmit_message);
    rt_uint32_t can_x = ((struct gd32_can_device *)can->parent.user_data)->can_x;
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;

    switch (box_num)
    {
    case CAN_MAILBOX0:
        if (!CAN_STAT(can_x) & CAN_TSTAT_TME0)
        {
            /* Return function status */
            return -RT_ERROR;
        }
        break;
    case CAN_MAILBOX1:
        if (!CAN_STAT(can_x) & CAN_TSTAT_TME1)
        {
            /* Return function status */
            return -RT_ERROR;
        }
        break;
    case CAN_MAILBOX2:
        if (!CAN_STAT(can_x) & CAN_TSTAT_TME2)
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
        transmit_message.tx_ff = CAN_FF_STANDARD;
        transmit_message.tx_sfid = pmsg->id;
    }
    else
    {
        transmit_message.tx_ff = CAN_FF_EXTENDED;
        transmit_message.tx_efid = pmsg->id;
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
        transmit_message.tx_ft = CAN_FT_DATA;
        memcpy(transmit_message.tx_data, pmsg->data, pmsg->len);
    }
    else
    {
        transmit_message.tx_ft = CAN_FT_REMOTE;
    }

    transmit_message.tx_dlen = pmsg->len;

    CAN_TMI(can_x, box_num) &= CAN_TMI_TEN;

    if (RT_CAN_STDID == pmsg->ide)
    {
        CAN_TMI(can_x, box_num) |= (uint32_t)(TMI_SFID(transmit_message.tx_sfid) | \
                                    transmit_message.tx_ft);
    }
    else
    {
        CAN_TMI(can_x, box_num) |= (uint32_t)(TMI_EFID(transmit_message.tx_efid) | \
                                    transmit_message.tx_ff | \
                                    transmit_message.tx_ft);
    }
    CAN_TMP(can_x, box_num) &= ~CAN_TMP_DLENC;
    CAN_TMP(can_x, box_num) |= transmit_message.tx_dlen;

    CAN_TMDATA0(can_x, box_num) = TMDATA0_DB3(transmit_message.tx_data[3]) | \
    TMDATA0_DB2(transmit_message.tx_data[2]) | \
    TMDATA0_DB1(transmit_message.tx_data[1]) | \
    TMDATA0_DB0(transmit_message.tx_data[0]);
    CAN_TMDATA1(can_x, box_num) = TMDATA1_DB7(transmit_message.tx_data[7]) | \
    TMDATA1_DB6(transmit_message.tx_data[6]) | \
    TMDATA1_DB5(transmit_message.tx_data[5]) | \
    TMDATA1_DB4(transmit_message.tx_data[4]);

    CAN_TMI(can_x, box_num) |= CAN_TMI_TEN;

    return RT_EOK;
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    RT_ASSERT(can);

    can_receive_message_struct receive_message;
    can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &receive_message);
    rt_uint32_t can_x = ((struct gd32_can_device *)can->parent.user_data)->can_x;
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;

    can_message_receive(can_x, fifo, &receive_message);

    if (receive_message.rx_ff == CAN_FF_STANDARD)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = receive_message.rx_sfid;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = receive_message.rx_efid;
    }

    if (receive_message.rx_ft == CAN_FT_DATA)
    {
        pmsg->rtr = RT_CAN_DTR;
        memcpy(pmsg->data, receive_message.rx_data, receive_message.rx_dlen);
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    pmsg->rxfifo = fifo;

    pmsg->len = receive_message.rx_dlen;

#ifdef CAN1
    if (can_x == CAN1)
    {
        pmsg->hdr_index = receive_message.rx_fi;
    }
#endif
#ifdef CAN2
    if (can_x == CAN2)
    {
       pmsg->hdr_index = receive_message.rx_fi;
    }
#endif

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
    RT_ASSERT(can);
    rt_uint32_t can_x = ((struct gd32_can_device *)can->parent.user_data)->can_x;

    switch (fifo)
    {
    case CAN_RX_FIFO0:
        /* save to user list */
        if (can_receive_message_length_get(can_x, CAN_RX_FIFO0) && can_interrupt_flag_get(can_x, CAN_INT_FLAG_RFL0))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        /* Check FULL flag for FIFO0 */
        if (can_flag_get(can_x, CAN_FLAG_RFF0) && can_interrupt_flag_get(can_x, CAN_INT_FLAG_RFF0))
        {
            /* Clear FIFO0 FULL Flag */
            can_flag_clear(can_x, CAN_INT_FLAG_RFF0);
        }

        /* Check Overrun flag for FIFO0 */
        if (can_flag_get(can_x, CAN_FLAG_RFO0) && can_interrupt_flag_get(can_x, CAN_INT_FLAG_RFO0))
        {
            /* Clear FIFO0 Overrun Flag */
            can_flag_clear(can_x, CAN_INT_FLAG_RFO0);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    case CAN_RX_FIFO1:
        /* save to user list */
        if (can_receive_message_length_get(can_x, CAN_RX_FIFO1) && can_interrupt_flag_get(can_x, CAN_INT_FLAG_RFL1))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
        }
        /* Check FULL flag for FIFO0 */
        if (can_flag_get(can_x, CAN_FLAG_RFF1) && can_interrupt_flag_get(can_x, CAN_INT_FLAG_RFF1))
        {
            /* Clear FIFO0 FULL Flag */
            can_interrupt_flag_clear(can_x, CAN_INT_FLAG_RFF1);
        }

        /* Check Overrun flag for FIFO0 */
        if (can_flag_get(can_x, CAN_FLAG_RFO0) && can_interrupt_flag_get(can_x, CAN_INT_FLAG_RFO0))
        {
            /* Clear FIFO0 Overrun Flag */
            can_interrupt_flag_clear(can_x, CAN_INT_FLAG_RFO1);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    }
}

static void _can_ewmc_isr(struct rt_can_device *can)
{
    RT_ASSERT(can);
    rt_uint32_t can_x = ((struct gd32_can_device *)can->parent.user_data)->can_x;
    rt_uint32_t errtype = CAN_ERR(can_x);

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
            if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF0))
            {
                if (!can_interrupt_flag_get(can_x, CAN_FLAG_MTFNERR0))
                {
                    rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
                }
                can_interrupt_flag_clear(can_x, CAN_INT_FLAG_MTF0);
            }
            else if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF1))
            {
                if (!can_interrupt_flag_get(can_x, CAN_FLAG_MTFNERR1))
                {
                    rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 1 << 8);
                }
                can_interrupt_flag_clear(can_x, CAN_INT_FLAG_MTF1);
            }
            else if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF2))
            {
                if (!can_interrupt_flag_get(can_x, CAN_FLAG_MTFNERR2))
                {
                    rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 2 << 8);
                }
                can_interrupt_flag_clear(can_x, CAN_INT_FLAG_MTF2);
            }
            else
            {
                if (can_interrupt_flag_get(can_x, CAN_FLAG_MTE0))/*IF AutoRetransmission = ENABLE,ACK ERR handler*/
                {
                    CAN_TSTAT(can_x) |= CAN_TSTAT_MST0;/*Abort the send request, trigger the TX interrupt,release completion quantity*/
                }
                else if (can_interrupt_flag_get(can_x, CAN_FLAG_MTE1))
                {
                    CAN_TSTAT(can_x) |= CAN_TSTAT_MST1;
                }
                else if (can_interrupt_flag_get(can_x, CAN_FLAG_MTE2))
                {
                    CAN_TSTAT(can_x) |= CAN_TSTAT_MST2;
                }
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
    CAN_STAT(can_x) |= CAN_STAT_ERRIF;
}

static void _can_tx_isr(struct rt_can_device *can)
{
    RT_ASSERT(can);
    rt_uint32_t can_x = ((struct gd32_can_device *)can->parent.user_data)->can_x;

    if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF0))
    {
        if (can_interrupt_flag_get(can_x, CAN_FLAG_MTFNERR0))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        can_interrupt_flag_clear(can_x, CAN_INT_FLAG_MTF0);
    }
    else if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF1))
    {
        if (can_interrupt_flag_get(can_x, CAN_FLAG_MTFNERR1))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        can_interrupt_flag_clear(can_x, CAN_INT_FLAG_MTF1);
    }
    else if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF2))
    {
        if (can_interrupt_flag_get(can_x, CAN_FLAG_MTFNERR2))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        can_interrupt_flag_clear(can_x, CAN_INT_FLAG_MTF2);
    }
}

#ifdef BSP_USING_CAN0
/**
 * @brief This function handles CAN0 TX interrupts. transmit fifo0/1/2 is empty can trigger this interrupt
 */
void CAN0_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_isr(&dev_can0.device);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN0 RX0 interrupts.
 */
void CAN0_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&dev_can0.device, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN0 RX1 interrupts.
 */
void CAN0_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&dev_can0.device, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN0 EWMC interrupts.
 */
void CAN0_EWMC_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_ewmc_isr(&dev_can0.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN0 */

#ifdef BSP_USING_CAN1
/**
 * @brief This function handles CAN1 TX interrupts.
 */
void CAN1_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_isr(&dev_can1.device);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void CAN1_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&dev_can1.device, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&dev_can1.device, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 EWMC interrupts.
 */
void CAN1_EWMC_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_ewmc_isr(&dev_can1.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN1 */

// void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
// {
//     can_interrupt_enable(hcan, CAN_INT_WERR |
//                         CAN_INT_PERR |
//                         CAN_INT_BO |
//                         CAN_INT_ERRN |
//                         CAN_INT_ERR |
//                         CAN_INT_RFNE0 |
//                         CAN_INT_RFO0 |
//                         CAN_INT_RFF0 |
//                         CAN_INT_RFNE1 |
//                         CAN_INT_RFO1 |
//                         CAN_INT_RFF1 |
//                         CAN_INT_TME);
// }

int rt_hw_can_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#ifdef CAN1
    config.maxhdr = 28;
#endif
#endif

    gd32_can_gpio_init();

    /* config default filter */
    can_filter_parameter_struct filter_config = {0};
    can_struct_para_init(CAN_FILTER_STRUCT, &filter_config);

    filter_config.filter_list_high = 0x0000;
    filter_config.filter_list_low = 0x0000;
    filter_config.filter_mask_high = 0x0000;
    filter_config.filter_mask_low = 0x0000;
    filter_config.filter_fifo_number = CAN_FIFO0;
    filter_config.filter_number = 0;
    filter_config.filter_mode = CAN_FILTERMODE_MASK;
    filter_config.filter_bits = CAN_FILTERBITS_32BIT;
    filter_config.filter_enable = ENABLE;

#ifdef BSP_USING_CAN0
    filter_config.filter_number = 0;

    dev_can0.filter_config = filter_config;
    dev_can0.device.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&dev_can0.device,
                       dev_can0.name,
                       &_can_ops,
                       &dev_can0);
#endif /* BSP_USING_CAN0 */

#ifdef BSP_USING_CAN1
    filter_config.filter_number = 14;

    dev_can1.filter_config = filter_config;
    dev_can1.device.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&dev_can1.device,
                       dev_can1.name,
                       &_can_ops,
                       &dev_can1);
#endif /* BSP_USING_CAN1 */

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
