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
 * 2026-09-08     CYFS                 add GD32F5xx and GD32H77D CAN FD support
 */

#include "drv_can.h"
#include "string.h"
#if defined(SOC_SERIES_GD32H77x_H78X)
#include "can_config.h"
#endif

#ifdef BSP_USING_CAN

#define LOG_TAG    "can_drv"
#include <drv_log.h>

#if defined(SOC_SERIES_GD32H77x_H78X) /* APB2 300MHz(max) */
static const struct gd32_baudrate_tbl can_baudrate_tbl[] =
{
    {CAN1MBaud,     1, 20, 27, 12, 5},
    {CAN800kBaud,   1,  2,  9,  3, 25},
    {CAN500kBaud,   1,  2,  5,  2, 60},
    {CAN250kBaud,   1,  2,  5,  2, 120},
    {CAN125kBaud,   1,  2,  5,  2, 240},
    {CAN100kBaud,   1,  2,  5,  2, 300},
    {CAN50kBaud,    1,  2,  5,  2, 600},
    {CAN20kBaud,    1, 14, 25, 10, 300},
    {CAN10kBaud,    1, 14, 25, 10, 600},
};
#elif defined(GD32F405) || defined(GD32F407) /* 42MHz(max) */
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
#elif defined(GD32F425) || defined(GD32F427) || defined(GD32F450) || defined(GD32F527)/* 50MHz(max) */
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

#if defined(BSP_USING_CAN0) && !defined(SOC_SERIES_GD32H77x_H78X)
static struct gd32_can_device dev_can0 =
{
    .name = "can0",
    .can_x = CAN0,
};
#endif

#ifdef BSP_USING_CAN1
static struct gd32_can_device dev_can1 =
{
    .name = "can1",
    .can_x = CAN1,
};
#endif

static const struct gd32_can gd32_can_gpio[] =
{
#if defined(BSP_USING_CAN0) && !defined(SOC_SERIES_GD32H77x_H78X)
    {
        .can_clk = RCU_CAN0,
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx
        .alt_func_num = GPIO_AF_9,
#endif
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
#if defined(SOC_SERIES_GD32H77x_H78X)
    CAN1_GPIO_CONFIG,
#else
    {
        .can_clk = RCU_CAN1,
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx
        .alt_func_num = GPIO_AF_9,
#endif

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
#endif
};

static rt_err_t gd32_can_gpio_init(void)
{
    for (rt_uint32_t i = 0; i < sizeof(gd32_can_gpio) / sizeof(gd32_can_gpio[0]); i++)
    {
#if defined(SOC_SERIES_GD32H77x_H78X)
        rt_uint32_t tx_port, rx_port;
        rt_uint32_t tx_pin, rx_pin;
        rt_uint32_t tx_af, rx_af;
        rcu_periph_enum tx_clk, rx_clk;

        if (get_pin_config(gd32_can_gpio[i].tx_pin_name, &tx_port, &tx_pin, &tx_clk) != RT_EOK ||
                get_pin_config(gd32_can_gpio[i].rx_pin_name, &rx_port, &rx_pin, &rx_clk) != RT_EOK ||
                pin_alternate_config(gd32_can_gpio[i].tx_alternate, &tx_af) != RT_EOK ||
                pin_alternate_config(gd32_can_gpio[i].rx_alternate, &rx_af) != RT_EOK)
        {
            return -RT_EINVAL;
        }

#ifdef BSP_USING_CAN1
        rcu_can_clock_config(IDX_CAN1, RCU_CANSRC_APB2);
#endif
        rcu_periph_clock_enable(gd32_can_gpio[i].can_clk);
        rcu_periph_clock_enable(tx_clk);
        rcu_periph_clock_enable(rx_clk);

        gpio_output_options_set(tx_port, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, tx_pin);
        gpio_mode_set(tx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, tx_pin);
        gpio_af_set(tx_port, tx_af, tx_pin);

        gpio_output_options_set(rx_port, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, rx_pin);
        gpio_mode_set(rx_port, GPIO_MODE_AF, GPIO_PUPD_NONE, rx_pin);
        gpio_af_set(rx_port, rx_af, rx_pin);
#else
        rcu_periph_clock_enable(gd32_can_gpio[i].can_clk);
        rcu_periph_clock_enable(gd32_can_gpio[i].tx_clk);
        rcu_periph_clock_enable(gd32_can_gpio[i].rx_clk);

#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx
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
#endif
    }

    return RT_EOK;
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

#if defined(SOC_SERIES_GD32H77x_H78X) && defined(RT_CAN_USING_CANFD)
static rt_bool_t _can_timing_segments(rt_uint32_t quanta, rt_bool_t data_phase,
        struct gd32_baudrate_tbl *timing)
{
    rt_uint32_t segment_1;
    rt_uint32_t min_prop = data_phase ? 0U : 1U;
    rt_uint32_t max_prop = data_phase ? 63U : 64U;

    if (quanta < 5U || quanta > 1U + max_prop + 32U + 32U)
    {
        return RT_FALSE;
    }

    timing->tseg2 = (quanta + 2U) / 5U;
    if (timing->tseg2 < 2U)
    {
        timing->tseg2 = 2U;
    }
    segment_1 = quanta - 1U - timing->tseg2;
    timing->prop_seg = segment_1 > 32U ? segment_1 - 32U : min_prop;
    timing->tseg1 = segment_1 - timing->prop_seg;
    timing->sjw = 1U;

    return timing->prop_seg <= max_prop && timing->tseg1 >= 1U && timing->tseg1 <= 32U;
}

static rt_err_t _can_fd_timing_get(const struct can_configure *cfg,
        struct gd32_baudrate_tbl *nominal, struct gd32_baudrate_tbl *data)
{
    rt_uint32_t clock = rcu_clock_freq_get(CK_APB2);

    if (cfg->baud_rate < CAN10kBaud || cfg->baud_rate > CAN1MBaud ||
            cfg->baud_rate_fd < cfg->baud_rate || cfg->baud_rate_fd > 8000000U)
    {
        return -RT_EINVAL;
    }

    for (rt_uint32_t prescaler = 1U; prescaler <= 1024U; prescaler++)
    {
        rt_uint32_t bit_clock = clock / prescaler;

        if (clock % prescaler != 0U || bit_clock % cfg->baud_rate != 0U ||
                bit_clock % cfg->baud_rate_fd != 0U)
        {
            continue;
        }
        if (_can_timing_segments(bit_clock / cfg->baud_rate, RT_FALSE, nominal) &&
                _can_timing_segments(bit_clock / cfg->baud_rate_fd, RT_TRUE, data))
        {
            nominal->prescaler = prescaler;
            data->prescaler = prescaler;
            return RT_EOK;
        }
    }

    return -RT_EINVAL;
}
#endif

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    can_parameter_struct can_init_struct;
    rt_uint32_t baudrate_index;
#if defined(SOC_SERIES_GD32H77x_H78X)
    rt_uint32_t interrupt_mask;
    rt_bool_t error_interrupt;
#ifdef RT_CAN_USING_CANFD
    struct gd32_baudrate_tbl nominal_timing = {0};
    struct gd32_baudrate_tbl data_timing = {0};
#endif
#endif

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    RT_ASSERT(can_dev != RT_NULL);

#if defined(SOC_SERIES_GD32H77x_H78X)
    if (cfg->sndboxnumber == 0U || cfg->sndboxnumber > GD32_CAN_TX_MAILBOX_NUM ||
            (can->parent.ref_count != 0U &&
             (cfg->sndboxnumber != can->config.sndboxnumber || cfg->msgboxsz != can->config.msgboxsz)))
    {
        return -RT_EINVAL;
    }
#ifdef RT_CAN_USING_CANFD
    if (cfg->sndboxnumber == GD32_CAN_TX_MAILBOX_NUM)
    {
        return -RT_EINVAL;
    }
    if (cfg->use_bit_timing)
    {
        return -RT_ENOSYS;
    }
    if (cfg->enable_canfd > 1U ||
            (cfg->enable_canfd && _can_fd_timing_get(cfg, &nominal_timing, &data_timing) != RT_EOK))
    {
        return -RT_EINVAL;
    }
#endif
    if (can->parent.ref_count != 0U)
    {
        for (rt_uint32_t mailbox = GD32_CAN_TX_MAILBOX_FIRST; mailbox < GD32_CAN_MAILBOX_NUM; mailbox++)
        {
            rt_uint32_t code = can_mailbox_code_get(can_dev->can_x, mailbox);

            if (code == CAN_MB_TX_STATUS_DATA || code == CAN_MB_TX_STATUS_ABORT)
            {
                return -RT_EBUSY;
            }
        }
    }
    interrupt_mask = CAN_INTEN(can_dev->can_x);
    error_interrupt = (CAN_CTL1(can_dev->can_x) & CAN_CTL1_ERRSIE) != 0U;
#endif

    can_deinit(can_dev->can_x);
    can_struct_para_init(CAN_INIT_STRUCT, &can_init_struct);

    baudrate_index = get_can_baudrate_index(cfg->baud_rate);

#if defined(SOC_SERIES_GD32H77x_H78X)
    can_init_struct.internal_counter_source = CAN_TIMER_SOURCE_BIT_CLOCK;
    can_init_struct.self_reception = DISABLE;
    can_init_struct.mb_tx_order = CAN_TX_HIGH_PRIORITY_MB_FIRST;
    can_init_struct.mb_tx_abort_enable = ENABLE;
    can_init_struct.local_priority_enable = DISABLE;
    can_init_struct.mb_rx_ide_rtr_type = CAN_IDE_RTR_FILTERED;
    can_init_struct.mb_remote_frame = CAN_STORE_REMOTE_REQUEST_FRAME;
    can_init_struct.rx_private_filter_queue_enable = ENABLE;
    can_init_struct.edge_filter_enable = DISABLE;
    can_init_struct.protocol_exception_enable = DISABLE;
    can_init_struct.rx_filter_order = CAN_RX_FILTER_ORDER_MAILBOX_FIRST;
    can_init_struct.memory_size = CAN_MEMSIZE_32_UNIT;
    can_init_struct.mb_public_filter = 0U;
    can_init_struct.resync_jump_width = can_baudrate_tbl[baudrate_index].sjw;
    can_init_struct.prop_time_segment = can_baudrate_tbl[baudrate_index].prop_seg;
    can_init_struct.time_segment_1 = can_baudrate_tbl[baudrate_index].tseg1;
    can_init_struct.time_segment_2 = can_baudrate_tbl[baudrate_index].tseg2;
    can_init_struct.prescaler = can_baudrate_tbl[baudrate_index].prescaler;

#ifdef RT_CAN_USING_CANFD
    if (cfg->enable_canfd)
    {
        can_init_struct.resync_jump_width = nominal_timing.sjw;
        can_init_struct.prop_time_segment = nominal_timing.prop_seg;
        can_init_struct.time_segment_1 = nominal_timing.tseg1;
        can_init_struct.time_segment_2 = nominal_timing.tseg2;
        can_init_struct.prescaler = nominal_timing.prescaler;
    }
#endif
    if (can_init(can_dev->can_x, &can_init_struct) != SUCCESS)
    {
        return -RT_ERROR;
    }
    can_auto_busoff_recovery_enable(can_dev->can_x);

#ifdef RT_CAN_USING_CANFD
    if (cfg->enable_canfd)
    {
        can_fd_parameter_struct fd_init;
        rt_uint32_t offset = data_timing.prescaler * (1U + data_timing.prop_seg + data_timing.tseg1);

        can_struct_para_init(CAN_FD_INIT_STRUCT, &fd_init);
        fd_init.iso_can_fd_enable = ENABLE;
        fd_init.bitrate_switch_enable = ENABLE;
        fd_init.mailbox_data_size = CAN_MAILBOX_DATA_SIZE_64_BYTES;
        fd_init.prescaler = data_timing.prescaler;
        fd_init.resync_jump_width = data_timing.sjw;
        fd_init.prop_time_segment = data_timing.prop_seg;
        fd_init.time_segment_1 = data_timing.tseg1;
        fd_init.time_segment_2 = data_timing.tseg2;
        fd_init.tdc_enable = cfg->baud_rate_fd > CAN1MBaud ? ENABLE : DISABLE;
        fd_init.tdc_offset = offset > 127U ? 127U : offset;
        can_fd_config(can_dev->can_x, &fd_init);
    }
#endif

    rt_memset(can_dev->rx_message_valid, 0, sizeof(can_dev->rx_message_valid));
    for (rt_uint32_t mailbox = 0U; mailbox < GD32_CAN_RX_MAILBOX_NUM; mailbox++)
    {
        can_struct_para_init(CAN_MDSC_STRUCT, &can_dev->rx_message[mailbox]);
        can_dev->rx_message[mailbox].code = CAN_MB_RX_STATUS_EMPTY;
        can_dev->rx_message[mailbox].id = 0x55U;
        can_mailbox_config(can_dev->can_x, mailbox, &can_dev->rx_message[mailbox]);
        can_private_filter_config(can_dev->can_x, mailbox, 0U);
    }
    for (rt_uint32_t mailbox = GD32_CAN_TX_MAILBOX_FIRST; mailbox < GD32_CAN_MAILBOX_NUM; mailbox++)
    {
        can_mailbox_transmit_inactive(can_dev->can_x, mailbox);
    }

    can_dev->tx_abort_mask = 0U;
    CAN_STAT(can_dev->can_x) = GD32_CAN_TX_INT_MASK;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_LISTEN:
        can_dev->mode = CAN_MONITOR_MODE;
        break;
    case RT_CAN_MODE_LOOPBACK:
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        can_dev->mode = CAN_LOOPBACK_SILENT_MODE;
        break;
    case RT_CAN_MODE_NORMAL:
    default:
        can_dev->mode = CAN_NORMAL_MODE;
        break;
    }

    if (can_operation_mode_enter(can_dev->can_x, can_dev->mode) != SUCCESS)
    {
        return -RT_ERROR;
    }
    can->config = *cfg;
    CAN_INTEN(can_dev->can_x) = interrupt_mask;
    if (error_interrupt)
    {
        can_interrupt_enable(can_dev->can_x, CAN_INT_ERR_SUMMARY);
#ifdef RT_CAN_USING_CANFD
        can_interrupt_enable(can_dev->can_x, CAN_INT_ERR_SUMMARY_FD);
#endif
    }
#else

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

    can_init_struct.resync_jump_width = can_baudrate_tbl[baudrate_index].sjw;
    can_init_struct.time_segment_1 = can_baudrate_tbl[baudrate_index].tseg1;
    can_init_struct.time_segment_2 = can_baudrate_tbl[baudrate_index].tseg2;
    can_init_struct.prescaler = can_baudrate_tbl[baudrate_index].prescaler;
    if (can_init(can_dev->can_x, &can_init_struct) != SUCCESS)
    {
        return -RT_ERROR;
    }

    can_filter_init(&can_dev->filter_config);
#endif

    return RT_EOK;
}

#if defined(SOC_SERIES_GD32H77x_H78X)
static void _can_message_irq_config(rt_uint32_t can_x, rt_bool_t enable)
{
#ifdef CAN0
    if (can_x == CAN0)
    {
        if (enable)
        {
            nvic_irq_enable(CAN0_Message_IRQn, 1, 0);
        }
        else
        {
            nvic_irq_disable(CAN0_Message_IRQn);
        }
    }
#endif
#ifdef CAN1
    if (can_x == CAN1)
    {
        if (enable)
        {
            nvic_irq_enable(CAN1_Message_IRQn, 1, 0);
        }
        else
        {
            nvic_irq_disable(CAN1_Message_IRQn);
        }
    }
#endif
}

static void _can_error_irq_config(rt_uint32_t can_x, rt_bool_t enable)
{
#ifdef CAN0
    if (can_x == CAN0)
    {
        if (enable)
        {
            nvic_irq_enable(CAN0_Error_IRQn, 1, 0);
        }
        else
        {
            nvic_irq_disable(CAN0_Error_IRQn);
        }
    }
#endif
#ifdef CAN1
    if (can_x == CAN1)
    {
        if (enable)
        {
            nvic_irq_enable(CAN1_Error_IRQn, 1, 0);
        }
        else
        {
            nvic_irq_disable(CAN1_Error_IRQn);
        }
    }
#endif
}

static rt_uint32_t _can_error_code_get(rt_uint32_t errtype)
{
    rt_uint32_t errcode = 0U;
    rt_uint32_t state = GET_ERR1_ERRSI(errtype);

    if ((errtype & (CAN_ERR1_RWERRF | CAN_ERR1_TWERRF)) != 0U)
    {
        errcode |= BIT(0);
    }
    if (state == CAN_ERROR_STATE_PASSIVE)
    {
        errcode |= BIT(1);
    }
    else if (state >= CAN_ERROR_STATE_BUS_OFF)
    {
        errcode |= BIT(2);
    }

    return errcode;
}

static rt_uint32_t _can_last_error_get(rt_uint32_t errtype)
{
    if ((errtype & (CAN_ERR1_STFERR | CAN_ERR1_STFFERR)) != 0U)
    {
        return RT_CAN_BUS_BIT_PAD_ERR;
    }
    if ((errtype & (CAN_ERR1_FMERR | CAN_ERR1_FMFERR)) != 0U)
    {
        return RT_CAN_BUS_FORMAT_ERR;
    }
    if ((errtype & CAN_ERR1_ACKERR) != 0U)
    {
        return RT_CAN_BUS_ACK_ERR;
    }
    if ((errtype & (CAN_ERR1_BRERR | CAN_ERR1_BRFERR)) != 0U)
    {
        return RT_CAN_BUS_IMPLICIT_BIT_ERR;
    }
    if ((errtype & (CAN_ERR1_BDERR | CAN_ERR1_BDFERR)) != 0U)
    {
        return RT_CAN_BUS_EXPLICIT_BIT_ERR;
    }
    if ((errtype & (CAN_ERR1_CRCERR | CAN_ERR1_CRCFERR)) != 0U)
    {
        return RT_CAN_BUS_CRC_ERR;
    }

    return RT_CAN_BUS_NO_ERR;
}
#endif

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
#if defined(SOC_SERIES_GD32H77x_H78X)
    struct can_configure config;
#else
    struct rt_can_filter_config *filter_cfg;
#endif

    RT_ASSERT(can != RT_NULL);
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    RT_ASSERT(can_dev != RT_NULL);
#if defined(SOC_SERIES_GD32H77x_H78X)
    config = can->config;
#endif

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
#if defined(SOC_SERIES_GD32H77x_H78X)
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_INTEN(can_dev->can_x) &= ~GD32_CAN_RX_INT_MASK;
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_INTEN(can_dev->can_x) &= ~GD32_CAN_TX_INT_MASK;
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            can_interrupt_disable(can_dev->can_x, CAN_INT_ERR_SUMMARY);
#ifdef RT_CAN_USING_CANFD
            can_interrupt_disable(can_dev->can_x, CAN_INT_ERR_SUMMARY_FD);
#endif
            _can_error_irq_config(can_dev->can_x, RT_FALSE);
        }

        if ((CAN_INTEN(can_dev->can_x) & BITS(0, 31)) == 0U)
        {
            _can_message_irq_config(can_dev->can_x, RT_FALSE);
        }
#else
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
#endif
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
#if defined(SOC_SERIES_GD32H77x_H78X)
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_INTEN(can_dev->can_x) |= GD32_CAN_RX_INT_MASK;
            _can_message_irq_config(can_dev->can_x, RT_TRUE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_INTEN(can_dev->can_x) |= GD32_CAN_TX_INT_MASK;
            _can_message_irq_config(can_dev->can_x, RT_TRUE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            can_interrupt_enable(can_dev->can_x, CAN_INT_ERR_SUMMARY);
#ifdef RT_CAN_USING_CANFD
            can_interrupt_enable(can_dev->can_x, CAN_INT_ERR_SUMMARY_FD);
#endif
            _can_error_irq_config(can_dev->can_x, RT_TRUE);
        }
#else
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
#endif
        break;
    case RT_CAN_CMD_SET_FILTER:
    {
#if defined(SOC_SERIES_GD32H77x_H78X)
        if (arg != RT_NULL)
        {
            return -RT_ENOSYS;
        }
#else
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
#ifdef RT_CAN_USING_HDR
                        filter_cfg->items[i].hdr_bank = i;
#endif
                    }
                    else if (rt_strcmp(can_dev->name, "can1") == 0)
                    {
                        /* can1 banks 14~27 */
                        can_dev->filter_config.filter_number = i + 14;
#ifdef RT_CAN_USING_HDR
                        filter_cfg->items[i].hdr_bank = i + 14;
#endif
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
#endif
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
#if defined(SOC_SERIES_GD32H77x_H78X)
            config.mode = argval;
            return _can_config(can, &config);
#else
            can_dev->device.config.mode = argval;
            return _can_config(&can_dev->device, &can_dev->device.config);
#endif
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
#if defined(SOC_SERIES_GD32H77x_H78X)
            config.baud_rate = argval;
            return _can_config(can, &config);
#else
            can_dev->device.config.baud_rate = argval;
            return _can_config(&can_dev->device, &can_dev->device.config);
#endif
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
#if defined(SOC_SERIES_GD32H77x_H78X)
            config.privmode = argval;
            return _can_config(can, &config);
#else
            can_dev->device.config.privmode = argval;
            return _can_config(&can_dev->device, &can_dev->device.config);
#endif
        }
        break;
    case RT_CAN_CMD_SET_CANFD:
#if defined(SOC_SERIES_GD32H77x_H78X) && defined(RT_CAN_USING_CANFD)
        argval = (rt_uint32_t)arg;
        if (argval > 1U)
        {
            return -RT_EINVAL;
        }
        if (config.enable_canfd != argval)
        {
            config.enable_canfd = argval;
            return _can_config(can, &config);
        }
        break;
#else
        return -RT_ENOSYS;
#endif
    case RT_CAN_CMD_SET_BAUD_FD:
#if defined(SOC_SERIES_GD32H77x_H78X) && defined(RT_CAN_USING_CANFD)
    {
        struct gd32_baudrate_tbl nominal = {0};
        struct gd32_baudrate_tbl data = {0};

        config.baud_rate_fd = (rt_uint32_t)arg;
        if (_can_fd_timing_get(&config, &nominal, &data) != RT_EOK)
        {
            return -RT_EINVAL;
        }
        if (config.baud_rate_fd != can->config.baud_rate_fd)
        {
            return _can_config(can, &config);
        }
        break;
    }
#else
        return -RT_ENOSYS;
#endif
    case RT_CAN_CMD_SET_BITTIMING:
        return -RT_ENOSYS;
    case RT_CAN_CMD_GET_STATUS:
    {
#if defined(SOC_SERIES_GD32H77x_H78X)
        can_error_counter_struct error_count;
        rt_uint32_t errtype = CAN_ERR1(can_dev->can_x);

        can_error_counter_get(can_dev->can_x, &error_count);
        can_dev->device.status.rcverrcnt = error_count.rx_errcnt;
        can_dev->device.status.snderrcnt = error_count.tx_errcnt;
        can_dev->device.status.lasterrtype = _can_last_error_get(errtype);
        can_dev->device.status.errcode = _can_error_code_get(errtype);
#else
        rt_uint32_t errtype;
        errtype = CAN_STAT(can_dev->can_x);
        can_dev->device.status.rcverrcnt = errtype >> 24;
        can_dev->device.status.snderrcnt = (errtype >> 16 & 0xFF);
        can_dev->device.status.lasterrtype = errtype & 0x70;
        can_dev->device.status.errcode = errtype & 0x07;
#endif

        rt_memcpy(arg, &can_dev->device.status, sizeof(can_dev->device.status));
        break;
    }
    }

    return RT_EOK;
}

#if defined(SOC_SERIES_GD32H77x_H78X)
static rt_err_t _can_message_validate(struct gd32_can_device *can_dev, const struct rt_can_msg *pmsg)
{
#ifdef RT_CAN_USING_CANFD
    if (pmsg->fd_frame)
    {
        if (!can_dev->device.config.enable_canfd || pmsg->rtr || pmsg->len > 64U)
        {
            return -RT_EINVAL;
        }
        return RT_EOK;
    }
    if (pmsg->brs)
    {
        return -RT_EINVAL;
    }
#else
    RT_UNUSED(can_dev);
#endif
    return pmsg->len <= 8U ? RT_EOK : -RT_EINVAL;
}

static rt_ssize_t _can_mailbox_send(struct gd32_can_device *can_dev,
        const struct rt_can_msg *pmsg, rt_uint32_t box_num)
{
    rt_uint32_t mailbox = box_num + GD32_CAN_TX_MAILBOX_FIRST;

    if (box_num >= GD32_CAN_TX_MAILBOX_NUM || _can_message_validate(can_dev, pmsg) != RT_EOK)
    {
        return -RT_EINVAL;
    }
    if (can_mailbox_code_get(can_dev->can_x, mailbox) != CAN_MB_TX_STATUS_INACTIVE)
    {
        return -RT_EBUSY;
    }

    rt_memset(&can_dev->tx_message[box_num], 0, sizeof(can_dev->tx_message[box_num]));
    can_dev->tx_message[box_num].rtr = pmsg->rtr;
    can_dev->tx_message[box_num].ide = pmsg->ide;
    can_dev->tx_message[box_num].code = CAN_MB_TX_STATUS_DATA;
    can_dev->tx_message[box_num].id = pmsg->id;
    can_dev->tx_message[box_num].prio = pmsg->priv;
    can_dev->tx_message[box_num].data_bytes = pmsg->len;
#ifdef RT_CAN_USING_CANFD
    can_dev->tx_message[box_num].fdf = pmsg->fd_frame;
    can_dev->tx_message[box_num].brs = pmsg->brs;
    if (pmsg->fd_frame && pmsg->len > 8U)
    {
        static const rt_uint8_t lengths[] = {12U, 16U, 20U, 24U, 32U, 48U, 64U};

        for (rt_uint32_t index = 0U; index < sizeof(lengths); index++)
        {
            if (pmsg->len <= lengths[index])
            {
                can_dev->tx_message[box_num].data_bytes = lengths[index];
                break;
            }
        }
    }
#endif
    rt_memcpy(can_dev->tx_message[box_num].data, pmsg->data, pmsg->len);
    can_mailbox_config(can_dev->can_x, mailbox, &can_dev->tx_message[box_num]);

    return RT_EOK;
}
#endif

static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    RT_ASSERT(can);
    RT_ASSERT(buf);

#if defined(SOC_SERIES_GD32H77x_H78X)
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    const struct rt_can_msg *pmsg = (const struct rt_can_msg *)buf;

    return _can_mailbox_send(can_dev, pmsg, box_num);
#else
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
#endif
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    RT_ASSERT(can);
    RT_ASSERT(buf);

#if defined(SOC_SERIES_GD32H77x_H78X)
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;

    if (fifo >= GD32_CAN_RX_MAILBOX_NUM || can_dev->rx_message_valid[fifo] == 0U)
    {
        return -RT_EEMPTY;
    }

    can_dev->rx_message_valid[fifo] = 0U;
    rt_memset(pmsg, 0, sizeof(*pmsg));
    pmsg->id = can_dev->rx_message[fifo].id;
    pmsg->ide = can_dev->rx_message[fifo].ide;
    pmsg->rtr = can_dev->rx_message[fifo].rtr;
    pmsg->len = can_dev->rx_message[fifo].data_bytes;
    pmsg->priv = 0U;
    pmsg->rxfifo = fifo;
    pmsg->hdr_index = fifo;
#ifdef RT_CAN_USING_CANFD
    pmsg->fd_frame = can_dev->rx_message[fifo].fdf;
    pmsg->brs = can_dev->rx_message[fifo].brs;
#endif
    if (pmsg->len > sizeof(pmsg->data))
    {
        return -RT_EINVAL;
    }
    rt_memcpy(pmsg->data, can_dev->rx_message[fifo].data, pmsg->len);

    return RT_EOK;
#else
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
#endif
}

rt_ssize_t _can_get_freebox(rt_uint32_t can_x)
{
    rt_uint32_t freebox = 0;
#if defined(SOC_SERIES_GD32H77x_H78X)
    for (rt_uint32_t mailbox = GD32_CAN_TX_MAILBOX_FIRST; mailbox < GD32_CAN_MAILBOX_NUM; mailbox++)
    {
        if (can_mailbox_code_get(can_x, mailbox) == CAN_MB_TX_STATUS_INACTIVE)
        {
            freebox++;
        }
    }
#else
    if ((CAN_STAT(can_x) & CAN_TSTAT_TME0) != 0U)
    {
        freebox++;
    }
    if ((CAN_STAT(can_x) & CAN_TSTAT_TME1) != 0U)
    {
        freebox++;
    }
    if ((CAN_STAT(can_x) & CAN_TSTAT_TME2) != 0U)
    {
        freebox++;
    }
#endif
    return freebox;
}

rt_ssize_t _can_sendmsg_nonblocking(struct rt_can_device *can, const void *buf)
{
    RT_ASSERT(can);
    RT_ASSERT(buf);

#if defined(SOC_SERIES_GD32H77x_H78X)
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    const struct rt_can_msg *pmsg = (const struct rt_can_msg *)buf;

    if (_can_message_validate(can_dev, pmsg) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    for (rt_uint32_t box_num = can->config.sndboxnumber; box_num < GD32_CAN_TX_MAILBOX_NUM; box_num++)
    {
        rt_uint32_t mailbox = box_num + GD32_CAN_TX_MAILBOX_FIRST;

        if (can_mailbox_code_get(can_dev->can_x, mailbox) == CAN_MB_TX_STATUS_INACTIVE)
        {
            return _can_mailbox_send(can_dev, pmsg, box_num);
        }
    }

    return -RT_EBUSY;
#else
    can_trasnmit_message_struct transmit_message;
    can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &transmit_message);
    rt_uint32_t can_x = ((struct gd32_can_device *)can->parent.user_data)->can_x;
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;

    if(_can_get_freebox(can_x) == 0)
    {
        return -RT_EBUSY;
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
    if(can_message_transmit(can_x, &transmit_message) == CAN_NOMAILBOX)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
#endif
}

static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
    _can_sendmsg_nonblocking,
};

static void _can_rx_isr(struct rt_can_device *can, rt_uint32_t fifo)
{
    RT_ASSERT(can);
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    rt_uint32_t can_x = can_dev->can_x;

#if defined(SOC_SERIES_GD32H77x_H78X)
    RT_UNUSED(fifo);
    for (rt_uint32_t mailbox = 0U; mailbox < GD32_CAN_RX_MAILBOX_NUM; mailbox++)
    {
        if ((CAN_STAT(can_x) & CAN_INTEN(can_x) & BIT(mailbox)) != 0U)
        {
            if (can_mailbox_receive_data_read(can_x, mailbox, &can_dev->rx_message[mailbox]) == SUCCESS)
            {
                can_dev->rx_message_valid[mailbox] = 1U;
                rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | (mailbox << 8));
            }
            else
            {
                CAN_STAT(can_x) = BIT(mailbox);
            }
        }
    }
#else
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
#endif
}

static void _can_ewmc_isr(struct rt_can_device *can)
{
    RT_ASSERT(can);
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;
    rt_uint32_t can_x = can_dev->can_x;
#if defined(SOC_SERIES_GD32H77x_H78X)
    rt_uint32_t errtype;

    if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_ERR_SUMMARY) == SET ||
            can_interrupt_flag_get(can_x, CAN_INT_FLAG_ERR_SUMMARY_FD) == SET)
    {
        errtype = CAN_ERR1(can_x);
        if ((errtype & (CAN_ERR1_STFERR | CAN_ERR1_STFFERR)) != 0U)
        {
            can->status.bitpaderrcnt++;
        }
        if ((errtype & (CAN_ERR1_FMERR | CAN_ERR1_FMFERR)) != 0U)
        {
            can->status.formaterrcnt++;
        }
        if ((errtype & (CAN_ERR1_CRCERR | CAN_ERR1_CRCFERR)) != 0U)
        {
            can->status.crcerrcnt++;
        }
        if ((errtype & CAN_ERR1_ACKERR) != 0U)
        {
            can->status.ackerrcnt++;
        }
        if ((errtype & (CAN_ERR1_BDERR | CAN_ERR1_BRERR | CAN_ERR1_BDFERR | CAN_ERR1_BRFERR)) != 0U)
        {
            can->status.biterrcnt++;
        }
        can->status.lasterrtype = _can_last_error_get(errtype);
        can->status.errcode = _can_error_code_get(errtype);

        if (((errtype & CAN_ERR1_ACKERR) != 0U) ||
                ((errtype & CAN_ERR1_BOF) != 0U) ||
                (((errtype & CAN_ERR1_TS) != 0U) &&
                 ((errtype & (CAN_ERR1_STFERR | CAN_ERR1_FMERR | CAN_ERR1_CRCERR |
                              CAN_ERR1_BDERR | CAN_ERR1_BRERR | CAN_ERR1_STFFERR |
                              CAN_ERR1_FMFERR | CAN_ERR1_CRCFERR | CAN_ERR1_BDFERR |
                              CAN_ERR1_BRFERR)) != 0U)))
        {
            for (rt_uint32_t box_num = 0U; box_num < GD32_CAN_TX_MAILBOX_NUM; box_num++)
            {
                rt_uint32_t mailbox = box_num + GD32_CAN_TX_MAILBOX_FIRST;

                if (can_mailbox_code_get(can_x, mailbox) == CAN_MB_TX_STATUS_DATA)
                {
                    can_dev->tx_abort_mask |= (rt_uint16_t)BIT(box_num);
                    can_mailbox_transmit_abort(can_x, mailbox);
                }
            }
        }
        can_interrupt_flag_clear(can_x, CAN_INT_FLAG_ERR_SUMMARY);
        can_interrupt_flag_clear(can_x, CAN_INT_FLAG_ERR_SUMMARY_FD);
    }
#else
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
                if (!can_flag_get(can_x, CAN_FLAG_MTFNERR0))
                {
                    rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
                }
                can_interrupt_flag_clear(can_x, CAN_INT_FLAG_MTF0);
            }
            else if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF1))
            {
                if (!can_flag_get(can_x, CAN_FLAG_MTFNERR1))
                {
                    rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 1 << 8);
                }
                can_interrupt_flag_clear(can_x, CAN_INT_FLAG_MTF1);
            }
            else if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF2))
            {
                if (!can_flag_get(can_x, CAN_FLAG_MTFNERR2))
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
#endif
}

static void _can_tx_isr(struct rt_can_device *can)
{
    RT_ASSERT(can);
    rt_uint32_t can_x = ((struct gd32_can_device *)can->parent.user_data)->can_x;

#if defined(SOC_SERIES_GD32H77x_H78X)
    struct gd32_can_device *can_dev = (struct gd32_can_device *)can->parent.user_data;

    for (rt_uint32_t mailbox = GD32_CAN_TX_MAILBOX_FIRST; mailbox < GD32_CAN_MAILBOX_NUM; mailbox++)
    {
        if ((CAN_STAT(can_x) & CAN_INTEN(can_x) & BIT(mailbox)) != 0U)
        {
            rt_uint32_t box_num = mailbox - GD32_CAN_TX_MAILBOX_FIRST;
            rt_uint32_t event = RT_CAN_EVENT_TX_DONE;

            if ((can_dev->tx_abort_mask & BIT(box_num)) != 0U ||
                    can_mailbox_code_get(can_x, mailbox) != CAN_MB_TX_STATUS_INACTIVE)
            {
                can_dev->tx_abort_mask &= (rt_uint16_t)~BIT(box_num);
                can_mailbox_transmit_inactive(can_x, mailbox);
                event = RT_CAN_EVENT_TX_FAIL;
            }
            CAN_STAT(can_x) = BIT(mailbox);
            rt_hw_can_isr(can, event | (box_num << 8));
        }
    }
#else
    if (can_interrupt_flag_get(can_x, CAN_INT_FLAG_MTF0))
    {
        if (can_flag_get(can_x, CAN_FLAG_MTFNERR0))
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
        if (can_flag_get(can_x, CAN_FLAG_MTFNERR1))
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
        if (can_flag_get(can_x, CAN_FLAG_MTFNERR2))
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
#endif
}

#if defined(SOC_SERIES_GD32H77x_H78X)
#ifdef BSP_USING_CAN1
void CAN1_Message_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&dev_can1.device, 0U);
    _can_tx_isr(&dev_can1.device);
    rt_interrupt_leave();
}

void CAN1_Error_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_ewmc_isr(&dev_can1.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN1 */
#else
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
#endif /* SOC_SERIES_GD32H77x_H78X */

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
#if !defined(SOC_SERIES_GD32H77x_H78X)
    can_filter_parameter_struct filter_config = {0};
#endif

    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#if defined(SOC_SERIES_GD32H77x_H78X) && defined(RT_CAN_USING_CANFD)
    config.baud_rate_fd = 2000000U;
#endif
#ifdef RT_CAN_USING_HDR
#if defined(SOC_SERIES_GD32H77x_H78X)
    config.maxhdr = GD32_CAN_RX_MAILBOX_NUM;
#else
    config.maxhdr = 14;
#ifdef CAN1
    config.maxhdr = 28;
#endif
#endif
#endif

    if (gd32_can_gpio_init() != RT_EOK)
    {
        return -RT_ERROR;
    }

#if !defined(SOC_SERIES_GD32H77x_H78X)
    /* config default filter */
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
#endif

#if defined(SOC_SERIES_GD32H77x_H78X)
#ifdef BSP_USING_CAN1
    dev_can1.device.config = config;
    if (rt_hw_can_register(&dev_can1.device, dev_can1.name, &_can_ops, &dev_can1) != RT_EOK)
    {
        return -RT_ERROR;
    }
#endif
#else
#ifdef BSP_USING_CAN0
    filter_config.filter_number = 0;

    dev_can0.filter_config = filter_config;
    dev_can0.device.config = config;
    rt_hw_can_register(&dev_can0.device,
                       dev_can0.name,
                       &_can_ops,
                       &dev_can0);
#endif /* BSP_USING_CAN0 */

#ifdef BSP_USING_CAN1
    filter_config.filter_number = 14;

    dev_can1.filter_config = filter_config;
    dev_can1.device.config = config;
    rt_hw_can_register(&dev_can1.device,
                       dev_can1.name,
                       &_can_ops,
                       &dev_can1);
#endif /* BSP_USING_CAN1 */
#endif

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
