/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-10-29     mazhiyuan         first version
 */

#include "drv_can.h"

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

static void ra_can_get_config(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
#ifdef BSP_USING_CAN0
    can_obj[CAN0_INDEX].can_dev.config = config;
    can_obj[CAN0_INDEX].can_dev.config.msgboxsz = CAN_NO_OF_MAILBOXES_g_can0;
    can_obj[CAN0_INDEX].can_dev.config.sndboxnumber = 1;
    can_obj[CAN0_INDEX].can_dev.config.ticks = 50;
#endif
#ifdef BSP_USING_CAN1
    can_obj[CAN1_INDEX].can_dev.config = config;
    can_obj[CAN1_INDEX].can_dev.config.msgboxsz = CAN_NO_OF_MAILBOXES_g_can1;
    can_obj[CAN1_INDEX].can_dev.config.sndboxnumber = 1;
    can_obj[CAN1_INDEX].can_dev.config.ticks = 50;
#endif
}
rt_err_t ra_can_configure(struct rt_can_device *can_dev, struct can_configure *cfg)
{
    struct ra_can *can;
    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    fsp_err_t err = FSP_SUCCESS;

    can = rt_container_of(can_dev, struct ra_can, can_dev);
    RT_ASSERT(can != RT_NULL);
    err = R_CAN_Open(can->config->p_api_ctrl, can->config->p_cfg);
    if (FSP_SUCCESS != err)
    {
        return RT_ERROR;
    }
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
    case RT_DEVICE_CTRL_CLR_INT:
        R_BSP_IrqStatusClear((IRQn_Type)arg);
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
            can->can_dev.config.baud_rate = argval;
            uint32_t index = get_can_baud_index(argval);
            can->config->p_cfg->p_bit_timing->baud_rate_prescaler = can_baud_rate_tab[index].prescaler;
            can->config->p_cfg->p_bit_timing->synchronization_jump_width = can_baud_rate_tab[index].sjw;
            can->config->p_cfg->p_bit_timing->time_segment_1 = can_baud_rate_tab[index].ts1;
            can->config->p_cfg->p_bit_timing->time_segment_2 = can_baud_rate_tab[index].ts2;
            return ra_can_configure(&can->can_dev, &can->can_dev.config);
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
            can->can_dev.config.mode = argval;
            switch (argval)
            {
            case RT_CAN_MODE_NORMAL:
                mode_to_set = CAN_TEST_MODE_DISABLED;
            case RT_CAN_MODE_LISTEN:
                mode_to_set = CAN_TEST_MODE_LISTEN;
            case RT_CAN_MODE_LOOPBACK:
                mode_to_set = CAN_TEST_MODE_LOOPBACK_INTERNAL;
            }
            R_CAN_ModeTransition(can->config->p_api_ctrl, ((can_instance_ctrl_t *)(can->config->p_api_ctrl))->operation_mode, mode_to_set);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
        R_CAN_InfoGet(can->config->p_api_ctrl, &can_info);
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
int ra_can_sendmsg(struct rt_can_device *can_dev, const void *buf, rt_uint32_t boxno)
{
    struct ra_can *can;
    can_frame_t g_can_tx_frame;
    struct rt_can_msg *msg_rt = (struct rt_can_msg *)buf;
    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    g_can_tx_frame.id = msg_rt->id;
    g_can_tx_frame.id_mode = msg_rt->ide;
    g_can_tx_frame.type = msg_rt->rtr;
    g_can_tx_frame.data_length_code = msg_rt->len;
    g_can_tx_frame.options = 0;
    memcpy(g_can_tx_frame.data, msg_rt->data, 8);
    can = rt_container_of(can_dev, struct ra_can, can_dev);
    RT_ASSERT(boxno < can->config->num_of_mailboxs);

    if (R_CAN_Write(can->config->p_api_ctrl, boxno, &g_can_tx_frame) != FSP_SUCCESS)
    {
        rt_exit_critical();
        return RT_ERROR;
    }
    return RT_EOK;
}

int ra_can_recvmsg(struct rt_can_device *can_dev, void *buf, rt_uint32_t boxno)
{
    struct rt_can_msg *msg_rt = (struct rt_can_msg *)buf;
    can_frame_t *msg_ra;
    struct ra_can *can;

    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    can = rt_container_of(can_dev, struct ra_can, can_dev);
    RT_ASSERT(boxno < can->config->num_of_mailboxs);
    if (can->callback_args->mailbox != boxno)
        return 0;
    msg_ra = can->callback_args->p_frame;

    msg_rt->id = msg_ra->id;
    msg_rt->ide = msg_ra->id_mode;
    msg_rt->rtr = msg_ra->type;
    msg_rt->rsv = RT_NULL;
    msg_rt->len = msg_ra->data_length_code;
    msg_rt->priv = boxno;
    msg_rt->hdr_index = RT_NULL;
    memcpy(msg_rt->data, msg_ra->data, msg_ra->data_length_code);
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
        can_obj[CAN0_INDEX].callback_args = p_args;
        if (p_args->event == CAN_EVENT_RX_COMPLETE)
            rt_hw_can_isr(&can_obj[CAN0_INDEX].can_dev, RT_CAN_EVENT_RX_IND | p_args->mailbox << 8);
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
    {
        break;
    }
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
        can_obj[CAN1_INDEX].callback_args = p_args;
        if (p_args->event == CAN_EVENT_RX_COMPLETE)
            rt_hw_can_isr(&can_obj[CAN1_INDEX].can_dev, RT_CAN_EVENT_RX_IND | p_args->mailbox << 8);
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
