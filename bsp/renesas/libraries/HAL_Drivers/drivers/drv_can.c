/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-10-29     mazhiyuan         first version
 * 2025-02-11     kurisaW           support can and canfd drivers for RZ family
 */

#include "drv_can.h"

#if defined(BSP_USING_CANFD) && defined(BSP_FEATURE_CANFD_HAS_CLOCK) && \
    BSP_FEATURE_CANFD_HAS_CLOCK
#define RA_CAN_USING_DYNAMIC_CANFD_TIMING
#endif

static struct ra_can_config can_config[] =
{
#ifdef BSP_USING_CAN0
    CAN0_CONFIG,
#endif

#ifdef BSP_USING_CAN1
    CAN1_CONFIG
#endif
};

enum
{
#ifdef BSP_USING_CAN0
    CAN0_INDEX,
#endif

#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
};

static struct ra_can can_obj[sizeof(can_config) / sizeof(can_config[0])] = {0};

#ifndef RA_CAN_USING_DYNAMIC_CANFD_TIMING
static const struct ra_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud, 3, 6, 3, 1 + 4},
    {CAN800kBaud, 4, 15, 5, 1 + 2},
    {CAN500kBaud, 4, 14, 5, 1 + 4},
    {CAN250kBaud, 4, 14, 5, 1 + 9},
    {CAN125kBaud, 4, 14, 5, 1 + 19},
    {CAN100kBaud, 4, 14, 5, 1 + 24},
    {CAN50kBaud, 4, 14, 5, 1 + 49},
    {CAN20kBaud, 4, 14, 5, 1 + 124},
    {CAN10kBaud, 4, 14, 5, 1 + 249}
};
#endif

#if defined(BSP_USING_CANFD)

#define can_instance_ctrl_t         canfd_instance_ctrl_t

#define R_CAN_Open                  R_CANFD_Open
#define R_BSP_IrqStatusClear        R_BSP_IrqClearPending
#define R_CAN_ModeTransition        R_CANFD_ModeTransition
#define R_CAN_InfoGet               R_CANFD_InfoGet
#define R_CAN_Write                 R_CANFD_Write
#define R_CAN_Close                 R_CANFD_Close

#define can0_callback               canfd0_callback
#define can1_callback               canfd1_callback

#ifdef BSP_USING_CAN0
const canfd_afl_entry_t p_canfd0_afl[CANFD_CFG_AFL_CH0_RULE_NUM] =
{
    {
        .id =
        {
            .id         = 0x00,
            .frame_type = CAN_FRAME_TYPE_DATA,
            .id_mode    = CAN_ID_MODE_STANDARD
        },
        .destination =
        {
            .minimum_dlc       = CANFD_MINIMUM_DLC_0,
            .rx_buffer         = CANFD_RX_MB_NONE,
            .fifo_select_flags = CANFD_RX_FIFO_0
        }
    },
};
#endif

#ifdef BSP_USING_CAN1
const canfd_afl_entry_t p_canfd1_afl[CANFD_CFG_AFL_CH1_RULE_NUM] =
{
    {
        .id =
        {
            .id         = 0x01,
            .frame_type = CAN_FRAME_TYPE_DATA,
            .id_mode    = CAN_ID_MODE_STANDARD
        },
        .destination =
        {
            .minimum_dlc       = CANFD_MINIMUM_DLC_1,
            .rx_buffer         = CANFD_RX_MB_NONE,
#if defined(BSP_FEATURE_CANFD_NUM_INSTANCES) && BSP_FEATURE_CANFD_NUM_INSTANCES > 1
            .fifo_select_flags = CANFD_RX_FIFO_0
#else
            .fifo_select_flags = CANFD_RX_FIFO_1
#endif
        }
    },
};
#endif

#endif

#ifndef RA_CAN_USING_DYNAMIC_CANFD_TIMING
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
#endif

#ifdef RA_CAN_USING_DYNAMIC_CANFD_TIMING
static rt_uint32_t ra_canfd_clock_divisor_get(void)
{
#if BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_1
    return 1;
#elif BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_2
    return 2;
#elif defined(BSP_CLOCKS_CANFD_CLOCK_DIV_3) && \
    BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_3
    return 3;
#elif BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_4
    return 4;
#elif defined(BSP_CLOCKS_CANFD_CLOCK_DIV_5) && \
    BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_5
    return 5;
#elif BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_6
    return 6;
#elif BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_8
    return 8;
#elif defined(BSP_CLOCKS_CANFD_CLOCK_DIV_10) && \
    BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_10
    return 10;
#elif defined(BSP_CLOCKS_CANFD_CLOCK_DIV_16) && \
    BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_16
    return 16;
#elif defined(BSP_CLOCKS_CANFD_CLOCK_DIV_32) && \
    BSP_CFG_CANFDCLK_DIV == BSP_CLOCKS_CANFD_CLOCK_DIV_32
    return 32;
#else
    return 0;
#endif
}

static rt_uint32_t ra_canfd_clock_hz_get(void)
{
    rt_uint32_t source_clock;

    source_clock = R_BSP_SourceClockHzGet((fsp_priv_source_clock_t)BSP_CFG_CANFDCLK_SOURCE);
#if BSP_CFG_CANFDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC
    return source_clock;
#else
    rt_uint32_t divisor = ra_canfd_clock_divisor_get();

    return divisor == 0 ? 0 : source_clock / divisor;
#endif
}

static rt_err_t ra_canfd_timing_calculate(can_bit_timing_cfg_t *timing,
                                          rt_uint32_t clock_hz,
                                          rt_uint32_t baud,
                                          rt_bool_t data_phase)
{
    rt_uint32_t max_prescaler = data_phase ? 256 : 1024;
    rt_uint32_t max_time_segment_1 = data_phase ? 32 : 256;
    rt_uint32_t max_time_segment_2 = data_phase ? 16 : 128;
    rt_uint32_t prescaler;

    if (timing == RT_NULL || clock_hz == 0 || baud == 0)
    {
        return -RT_EINVAL;
    }

    for (prescaler = 1; prescaler <= max_prescaler; prescaler++)
    {
        rt_uint32_t denominator = baud * prescaler;
        rt_uint32_t total_tq;
        rt_uint32_t sample_tq;
        rt_uint32_t time_segment_1;
        rt_uint32_t time_segment_2;

        if (denominator == 0 || clock_hz % denominator != 0)
        {
            continue;
        }

        total_tq = clock_hz / denominator;
        if (total_tq < 8 ||
                total_tq > max_time_segment_1 + max_time_segment_2 + 1)
        {
            continue;
        }

        sample_tq = (total_tq * 3) / 4;
        time_segment_1 = sample_tq - 1;
        time_segment_2 = total_tq - sample_tq;
        if (time_segment_1 > max_time_segment_1 ||
                time_segment_2 > max_time_segment_2 ||
                time_segment_1 <= time_segment_2 || time_segment_2 == 0)
        {
            continue;
        }

        timing->baud_rate_prescaler = prescaler;
        timing->time_segment_1 = time_segment_1;
        timing->time_segment_2 = time_segment_2;
        timing->synchronization_jump_width = time_segment_2 < 4 ? time_segment_2 : 4;
        return RT_EOK;
    }

    return -RT_EINVAL;
}
#endif

static rt_err_t ra_can_apply_baud(struct ra_can *can, rt_uint32_t baud)
{
    can_bit_timing_cfg_t *timing = can->config->p_cfg->p_bit_timing;

#ifdef RA_CAN_USING_DYNAMIC_CANFD_TIMING
    rt_uint32_t clock_hz = ra_canfd_clock_hz_get();

    return ra_canfd_timing_calculate(timing, clock_hz, baud, RT_FALSE);
#else
    rt_uint32_t index = get_can_baud_index(baud);

    timing->baud_rate_prescaler = can_baud_rate_tab[index].prescaler;
    timing->synchronization_jump_width = can_baud_rate_tab[index].sjw;
    timing->time_segment_1 = can_baud_rate_tab[index].ts1;
    timing->time_segment_2 = can_baud_rate_tab[index].ts2;
    return RT_EOK;
#endif
}

static void ra_can_irq_control(IRQn_Type irq, rt_bool_t enable)
{
    if (irq < 0)
    {
        return;
    }

    if (enable)
    {
        R_BSP_IrqEnable(irq);
    }
    else
    {
        R_BSP_IrqDisable(irq);
        R_BSP_IrqStatusClear(irq);
    }
}

#if defined(BSP_USING_CANFD) && defined(VECTOR_NUMBER_CAN_RXF)
static rt_bool_t ra_can_other_rx_irq_enabled(struct ra_can *can)
{
    rt_size_t index;

    for (index = 0; index < sizeof(can_obj) / sizeof(can_obj[0]); index++)
    {
        struct rt_can_device *can_dev = &can_obj[index].can_dev;

        if (&can_obj[index] != can && can_dev->can_rx != RT_NULL &&
                (can_dev->parent.open_flag & RT_DEVICE_FLAG_INT_RX))
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}
#endif

static void ra_can_get_config(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
#ifdef BSP_USING_CAN0
    can_obj[CAN0_INDEX].can_dev.config = config;
    can_obj[CAN0_INDEX].can_dev.config.msgboxsz = 32;
    can_obj[CAN0_INDEX].can_dev.config.sndboxnumber = 1;
    can_obj[CAN0_INDEX].can_dev.config.ticks = 50;
#endif
#ifdef BSP_USING_CAN1
    can_obj[CAN1_INDEX].can_dev.config = config;
    can_obj[CAN1_INDEX].can_dev.config.msgboxsz = 32;
    can_obj[CAN1_INDEX].can_dev.config.sndboxnumber = 1;
    can_obj[CAN1_INDEX].can_dev.config.ticks = 50;
#endif
}
rt_err_t ra_can_configure(struct rt_can_device *can_dev, struct can_configure *cfg)
{
    struct ra_can *can;
    rt_err_t result;
    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    fsp_err_t err = FSP_SUCCESS;

    can = rt_container_of(can_dev, struct ra_can, can_dev);
    RT_ASSERT(can != RT_NULL);

    result = ra_can_apply_baud(can, cfg->baud_rate);
    if (result != RT_EOK)
    {
        return result;
    }

#if defined(RA_CAN_USING_DYNAMIC_CANFD_TIMING) && defined(BSP_USING_CANFD)
    if (cfg->enable_canfd)
    {
        canfd_extended_cfg_t *extend = (canfd_extended_cfg_t *)can->config->p_cfg->p_extend;

        if (extend == RT_NULL || extend->p_data_timing == RT_NULL)
        {
            return -RT_EINVAL;
        }

        result = ra_canfd_timing_calculate(extend->p_data_timing,
                                           ra_canfd_clock_hz_get(),
                                           cfg->baud_rate_fd,
                                           RT_TRUE);
        if (result != RT_EOK)
        {
            return result;
        }
    }
#endif

    if (((can_instance_ctrl_t *)can->config->p_api_ctrl)->open != 0)
    {
        err = R_CAN_Close(can->config->p_api_ctrl);
        if (FSP_SUCCESS != err)
        {
            return -RT_ERROR;
        }
    }

    err = R_CAN_Open(can->config->p_api_ctrl, can->config->p_cfg);
    if (FSP_SUCCESS != err)
    {
        return -RT_ERROR;
    }
    can_dev->config = *cfg;
    return RT_EOK;
}
rt_err_t ra_can_control(struct rt_can_device *can_dev, int cmd, void *arg)
{
    struct ra_can *can;
    can_info_t can_info;
    rt_uint32_t argval;
    RT_ASSERT(can_dev != RT_NULL);
    can = rt_container_of(can_dev, struct ra_can, can_dev);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t)(rt_ubase_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            ra_can_irq_control(can->config->p_cfg->rx_irq, cmd == RT_DEVICE_CTRL_SET_INT);
#if defined(BSP_USING_CANFD) && defined(VECTOR_NUMBER_CAN_RXF)
            if (cmd == RT_DEVICE_CTRL_SET_INT || !ra_can_other_rx_irq_enabled(can))
            {
                ra_can_irq_control(VECTOR_NUMBER_CAN_RXF, cmd == RT_DEVICE_CTRL_SET_INT);
            }
#endif
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            ra_can_irq_control(can->config->p_cfg->tx_irq, cmd == RT_DEVICE_CTRL_SET_INT);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            ra_can_irq_control(can->config->p_cfg->error_irq, cmd == RT_DEVICE_CTRL_SET_INT);
        }
        else
        {
            return -RT_EINVAL;
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
        if (argval != can->can_dev.config.baud_rate)
        {
            struct can_configure config = can->can_dev.config;

            config.baud_rate = argval;
            return ra_can_configure(&can->can_dev, &config);
        }
        break;
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
                argval != RT_CAN_MODE_LISTEN &&
                argval != RT_CAN_MODE_LOOPBACK)
        {
            return -RT_ERROR;
        }
        if (argval != can->can_dev.config.mode)
        {
            can_test_mode_t mode_to_set;

            switch (argval)
            {
            case RT_CAN_MODE_NORMAL:
                mode_to_set = CAN_TEST_MODE_DISABLED;
                break;
            case RT_CAN_MODE_LISTEN:
                mode_to_set = CAN_TEST_MODE_LISTEN;
                break;
            case RT_CAN_MODE_LOOPBACK:
                mode_to_set = CAN_TEST_MODE_LOOPBACK_INTERNAL;
                break;
            default:
                return -RT_EINVAL;
            }
            if (R_CAN_ModeTransition(can->config->p_api_ctrl,
                                     ((can_instance_ctrl_t *)can->config->p_api_ctrl)->operation_mode,
                                     mode_to_set) != FSP_SUCCESS)
            {
                return -RT_ERROR;
            }
            can->can_dev.config.mode = argval;
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
        if (R_CAN_InfoGet(can->config->p_api_ctrl, &can_info) != FSP_SUCCESS)
        {
            return -RT_ERROR;
        }
        can->can_dev.status.rcverrcnt = can_info.error_count_receive;
        can->can_dev.status.snderrcnt = can_info.error_count_transmit;
        can->can_dev.status.errcode = can_info.error_code;
        rt_memcpy(arg, &can->can_dev.status, sizeof(can->can_dev.status));
        break;
    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}

#if defined(BSP_USING_CANFD)
static rt_err_t ra_can_dlc_to_length(rt_uint8_t dlc, rt_uint8_t *length)
{
    static const rt_uint8_t dlc_to_length[] =
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
    };

    if (dlc >= sizeof(dlc_to_length))
    {
        return -RT_EINVAL;
    }

    *length = dlc_to_length[dlc];
    return RT_EOK;
}

static rt_err_t ra_can_length_to_dlc(rt_uint8_t length, rt_uint8_t *dlc)
{
    static const rt_uint8_t dlc_to_length[] =
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
    };
    rt_uint8_t index;

    for (index = 0; index < sizeof(dlc_to_length); index++)
    {
        if (dlc_to_length[index] == length)
        {
            *dlc = index;
            return RT_EOK;
        }
    }

    return -RT_EINVAL;
}
#endif

rt_ssize_t ra_can_sendmsg(struct rt_can_device *can_dev, const void *buf, rt_uint32_t boxno)
{
    struct ra_can *can;
    can_frame_t g_can_tx_frame;
    struct rt_can_msg *msg_rt = (struct rt_can_msg *)buf;
    rt_uint8_t payload_length;
    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    rt_memset(&g_can_tx_frame, 0, sizeof(g_can_tx_frame));
    g_can_tx_frame.id = msg_rt->id;
    g_can_tx_frame.id_mode = msg_rt->ide;
    g_can_tx_frame.type = msg_rt->rtr;
#if defined(BSP_USING_CANFD)
#ifdef BSP_USING_CANFD
    if ((!msg_rt->fd_frame && (msg_rt->len > 8 || msg_rt->brs)) ||
            (msg_rt->fd_frame && msg_rt->rtr))
    {
        return -RT_EINVAL;
    }
#else
    if (msg_rt->len > 8)
    {
        return -RT_EINVAL;
    }
#endif
    if (ra_can_dlc_to_length(msg_rt->len, &payload_length) != RT_EOK)
    {
        return -RT_EINVAL;
    }
    g_can_tx_frame.data_length_code = payload_length;
#else
    if (msg_rt->len > 8)
    {
        return -RT_EINVAL;
    }
    payload_length = msg_rt->len;
    g_can_tx_frame.data_length_code = msg_rt->len;
#endif
#if defined(BSP_USING_CANFD)
    g_can_tx_frame.options = 0;
#ifdef BSP_USING_CANFD
    if (msg_rt->fd_frame)
    {
        g_can_tx_frame.options |= CANFD_FRAME_OPTION_FD;
        if (msg_rt->brs)
        {
            g_can_tx_frame.options |= CANFD_FRAME_OPTION_BRS;
        }
    }
#endif
#else
    g_can_tx_frame.options = 0;
#endif
    memcpy(g_can_tx_frame.data, msg_rt->data, payload_length);
    can = rt_container_of(can_dev, struct ra_can, can_dev);
    RT_ASSERT(boxno < can->config->num_of_mailboxs);

    if (R_CAN_Write(can->config->p_api_ctrl, boxno, &g_can_tx_frame) != FSP_SUCCESS)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

rt_ssize_t ra_can_recvmsg(struct rt_can_device *can_dev, void *buf, rt_uint32_t boxno)
{
    struct rt_can_msg *msg_rt = (struct rt_can_msg *)buf;
    can_frame_t *msg_ra;
    struct ra_can *can;
    rt_uint8_t dlc;
    rt_uint8_t payload_length;

    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    can = rt_container_of(can_dev, struct ra_can, can_dev);
    RT_ASSERT(boxno < can->config->num_of_mailboxs);
    if (can->callback_args->mailbox != boxno)
        return 0;

    msg_ra = &can->callback_args->frame;
    payload_length = msg_ra->data_length_code;
    if (payload_length > sizeof(msg_rt->data))
    {
        return -RT_EINVAL;
    }

    rt_memset(msg_rt, 0, sizeof(*msg_rt));
    msg_rt->id = msg_ra->id;
    msg_rt->ide = msg_ra->id_mode;
    msg_rt->rtr = msg_ra->type;
    msg_rt->rsv = RT_NULL;
#if defined(BSP_USING_CANFD)
    if (ra_can_length_to_dlc(payload_length, &dlc) != RT_EOK)
    {
        return -RT_ERROR;
    }
    msg_rt->len = dlc;
#else
    msg_rt->len = payload_length;
#endif
    msg_rt->priv = boxno;
    msg_rt->hdr_index = -1;
#if defined(BSP_USING_CANFD)
    msg_rt->fd_frame = (msg_ra->options & CANFD_FRAME_OPTION_FD) != 0;
    msg_rt->brs = (msg_ra->options & CANFD_FRAME_OPTION_BRS) != 0;
    if (boxno >= 32)
    {
        msg_rt->rxfifo = boxno - 32;
    }
#endif
    memcpy(msg_rt->data, msg_ra->data, payload_length);
    return sizeof(struct rt_can_msg);
}
const struct rt_can_ops ra_can_ops =
{
    .configure = ra_can_configure,
    .control = ra_can_control,
    .sendmsg = ra_can_sendmsg,
    .recvmsg = ra_can_recvmsg
};

#ifdef BSP_USING_CAN0
void can0_callback(can_callback_args_t *p_args)
{
    rt_interrupt_enter();
    switch (p_args->event)
    {
    case CAN_EVENT_TX_COMPLETE:
        rt_hw_can_isr(&can_obj[CAN0_INDEX].can_dev, RT_CAN_EVENT_TX_DONE | p_args->mailbox << 8);
        break;
    case CAN_EVENT_RX_COMPLETE:
        if (can_obj[CAN0_INDEX].can_dev.can_rx != RT_NULL &&
                (can_obj[CAN0_INDEX].can_dev.parent.open_flag & RT_DEVICE_FLAG_INT_RX))
        {
            can_obj[CAN0_INDEX].callback_args = p_args;
            rt_hw_can_isr(&can_obj[CAN0_INDEX].can_dev, RT_CAN_EVENT_RX_IND | p_args->mailbox << 8);
        }
        break;
    case CAN_EVENT_TX_ABORTED:
        rt_hw_can_isr(&can_obj[CAN0_INDEX].can_dev, RT_CAN_EVENT_TX_FAIL | p_args->mailbox << 8);
        break;
    case CAN_EVENT_MAILBOX_MESSAGE_LOST:    //overwrite/overrun error event
    case CAN_EVENT_BUS_RECOVERY:            //Bus recovery error event
    case CAN_EVENT_ERR_BUS_OFF:             //error Bus Off event
    case CAN_EVENT_ERR_PASSIVE:             //error passive event
    case CAN_EVENT_ERR_WARNING:             //error warning event
    case CAN_EVENT_ERR_BUS_LOCK:            //error bus lock
    case CAN_EVENT_ERR_CHANNEL:             //error channel
    case CAN_EVENT_ERR_GLOBAL:              //error global
    case CAN_EVENT_TX_FIFO_EMPTY:           //error transmit FIFO is empty
    {
        break;
    }
    default:
        break;
    }
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CAN1
void can1_callback(can_callback_args_t *p_args)
{
    rt_interrupt_enter();
    switch (p_args->event)
    {
    case CAN_EVENT_TX_COMPLETE:
        rt_hw_can_isr(&can_obj[CAN1_INDEX].can_dev, RT_CAN_EVENT_TX_DONE | p_args->mailbox << 8);
        break;
    case CAN_EVENT_RX_COMPLETE:
        if (can_obj[CAN1_INDEX].can_dev.can_rx != RT_NULL &&
                (can_obj[CAN1_INDEX].can_dev.parent.open_flag & RT_DEVICE_FLAG_INT_RX))
        {
            can_obj[CAN1_INDEX].callback_args = p_args;
            rt_hw_can_isr(&can_obj[CAN1_INDEX].can_dev, RT_CAN_EVENT_RX_IND | p_args->mailbox << 8);
        }
        break;
    case CAN_EVENT_TX_ABORTED:
        rt_hw_can_isr(&can_obj[CAN1_INDEX].can_dev, RT_CAN_EVENT_TX_FAIL | p_args->mailbox << 8);
        break;
    case CAN_EVENT_MAILBOX_MESSAGE_LOST:    //overwrite/overrun error event
    case CAN_EVENT_BUS_RECOVERY:            //Bus recovery error event
    case CAN_EVENT_ERR_BUS_OFF:             //error Bus Off event
    case CAN_EVENT_ERR_PASSIVE:             //error passive event
    case CAN_EVENT_ERR_WARNING:             //error warning event
    case CAN_EVENT_ERR_BUS_LOCK:            //error bus lock
    case CAN_EVENT_ERR_CHANNEL:             //error channel
    case CAN_EVENT_ERR_GLOBAL:              //error global
    {
        break;
    }
    default:
        break;
    }
    rt_interrupt_leave();
}
#endif

int rt_hw_can_init(void)
{
    rt_err_t result = 0;
    rt_size_t obj_num = sizeof(can_obj) / sizeof(struct ra_can);
    ra_can_get_config();
    for (int i = 0; i < obj_num; i++)
    {
        /* init CAN object */
        can_obj[i].config = &can_config[i];
        can_obj[i].can_dev.ops = &ra_can_ops;
        /* register CAN device */
        result = rt_hw_can_register(&can_obj[i].can_dev, can_obj[i].config->name, can_obj[i].can_dev.ops, RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_can_init);
