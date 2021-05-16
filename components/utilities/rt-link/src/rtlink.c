/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-02     xiangxistu   the first version
 * 2021-03-19     Sherman      Optimize the transfer process
 * 2021-04-20     Sherman      Optimize memory footprint
 * 2021-05-10     Sherman      Add rtlink_status  MSH command; Optimize transmission timer Settings; Fix known bugs
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rthw.h>

#include <rtlink.h>
#include <rtlink_hw.h>
#include <rtlink_utils.h>

#define DBG_ENABLE
#ifdef USING_RT_LINK_DEBUG
    #define DBG_LVL DBG_LOG
#else
    #define DBG_LVL DBG_INFO
#endif
#define DBG_TAG "rtlink"
#define DBG_COLOR
#include <rtdbg.h>

#ifdef RT_LINK_USING_SPI
    #define RT_LINK_LONG_FRAME_TIMEOUT      50
    #define RT_LINK_SENT_FRAME_TIMEOUT      100
#else
    #define RT_LINK_LONG_FRAME_TIMEOUT      100
    #define RT_LINK_SENT_FRAME_TIMEOUT      200
#endif /* RT_LINK_USING_SPI */

#define RT_LINK_RECV_DATA_SEQUENCE      0
#define RT_LINK_INIT_FRAME_SEQENCE      129

#define RT_LINK_THREAD_NAME "rtlink"
#define RT_LINK_THREAD_TICK    20
#define RT_LINK_THREAD_PRIORITY    15
#define RT_LINK_THREAD_STACK_SIZE      832 /* 32 bytes aligned */

typedef enum
{
    FIND_FRAME_HEAD = 0,
    PARSE_FRAME_HEAD,
    PARSE_FRAME_EXTEND,
    PARSE_FRAME_SEQ,
    CHECK_FRAME_CRC,
    HEADLE_FRAME_DATA,
} rt_link_frame_parse_t;

/* rtlink SCB(Session control block) */
static struct rt_link_session *rt_link_scb = RT_NULL;
struct rt_link_session *rt_link_get_scb(void)
{
    return rt_link_scb;
}

static rt_int16_t rt_link_check_seq(rt_uint8_t new, rt_uint8_t used)
{
    rt_int16_t compare_seq = 0;
    compare_seq = new - used;
    if (compare_seq < 0)
    {
        compare_seq = compare_seq + 256;
    }
    return compare_seq;
}

static int rt_link_frame_init(struct rt_link_frame *frame, rt_uint8_t config)
{
    if (frame == RT_NULL)
    {
        return -RT_ERROR;
    }

    /* set frame control information */
    rt_memset(&frame->head, 0, sizeof(struct rt_link_frame_head));
    if (config & FRAME_CRC)
    {
        frame->head.crc = 1;
    }
    if (config & FRAME_ACK)
    {
        frame->head.ack = 1;
    }

    frame->head.magicid = RT_LINK_FRAME_HEAD;
    /* frame data information */
    rt_memset(&frame->extend, 0, sizeof(struct rt_link_extend));
    frame->crc = 0;
    frame->real_data = RT_NULL;
    frame->data_len = 0;
    frame->index = 0;
    frame->total = 0;
    frame->attribute = RT_LINK_RESERVE_FRAME;

    rt_slist_init(&frame->slist);

    return RT_EOK;
}

static rt_err_t rt_link_frame_free(struct rt_link_frame *frame)
{
    if (frame == RT_NULL)
    {
        return -RT_ERROR;
    }

    if (frame->real_data != RT_NULL)
    {
        rt_free(frame->real_data);
        frame->real_data = RT_NULL;
    }
    rt_memset(frame, 0, sizeof(struct rt_link_frame));
    rt_free(frame);
    return RT_EOK;
}

/* performs data transmission */
static rt_err_t rt_link_frame_send(rt_slist_t *slist)
{
    struct rt_link_frame *frame = RT_NULL;
    rt_uint8_t *origin_data = RT_NULL;
    rt_uint8_t *data = RT_NULL;
    rt_size_t length = 0;
    rt_uint8_t send_max = RT_LINK_ACK_MAX;  /* The number of '1' in the binary number */

    /* if slist is tx_data_slist, we should send all data on the slist*/
    if (slist == &rt_link_scb->tx_data_slist)
    {
        slist = rt_slist_next(&rt_link_scb->tx_data_slist);
    }
    if (slist == RT_NULL)
    {
        LOG_W("tx_data_slist NULL");
        return -RT_ERROR;
    }
    data = rt_malloc(RT_LINK_MAX_FRAME_LENGTH);
    if (data == RT_NULL)
    {
        LOG_E("rt link alloc memory(%d B) failed, send frame failed.", RT_LINK_MAX_FRAME_LENGTH);
        return -RT_ENOMEM;
    }
    origin_data = data;

    do
    {
        /* get frame for send */
        frame = rt_container_of(slist, struct rt_link_frame, slist);
        slist = rt_slist_next(slist);

        length = RT_LINK_HEAD_LENGTH;
        if (frame->head.crc)
        {
            length += RT_LINK_CRC_LENGTH;
        }
        if (frame->head.extend)
        {
            length += RT_LINK_MAX_EXTEND_LENGTH;
        }

        length += frame->data_len;
        frame->head.length = frame->data_len;
        rt_memcpy(data, &frame->head, RT_LINK_HEAD_LENGTH);
        data = data + RT_LINK_HEAD_LENGTH;
        if (frame->head.extend)
        {
            rt_memcpy(data, &frame->extend, RT_LINK_MAX_EXTEND_LENGTH);
            data = data + RT_LINK_MAX_EXTEND_LENGTH;
        }
        if (frame->attribute == RT_LINK_SHORT_DATA_FRAME || frame->attribute == RT_LINK_LONG_DATA_FRAME)
        {
            rt_memcpy(data, frame->real_data, frame->data_len);
            data = data + frame->data_len;
        }
        if (frame->head.crc)
        {
            frame->crc = rt_link_scb->calculate_crc(RT_FALSE, origin_data, length - RT_LINK_CRC_LENGTH);
            rt_memcpy(data, &frame->crc, RT_LINK_CRC_LENGTH);
        }

        LOG_D("frame send(%d) len(%d) attr:(%d), crc:(0x%08x).", frame->head.sequence, length, frame->attribute, frame->crc);
        rt_link_hw_send(origin_data, length);

        data = origin_data;
        if (slist == RT_NULL)
        {
            send_max = 0;
        }
        send_max >>= 1;
    }while (send_max);
    rt_free(origin_data);
    return RT_EOK;
}

static void _stop_recv_long(void)
{
    rt_timer_stop(&rt_link_scb->longframetimer);
    if (rt_link_scb->rx_record.dataspace != RT_NULL)
    {
        rt_free(rt_link_scb->rx_record.dataspace);
        rt_link_scb->rx_record.dataspace = RT_NULL;
    }
    rt_link_scb->rx_record.long_count = 0;
    rt_link_scb->rx_record.total = 0;
}

static rt_err_t rt_link_frame_stop_receive(struct rt_link_frame *frame)
{
    rt_memset(frame, 0, sizeof(struct rt_link_frame));
    rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, rt_link_hw_recv_len(rt_link_scb->rx_buffer));
    return RT_EOK;
}

/* Configure the extended field of the frame */
static rt_err_t rt_link_frame_extend_config(struct rt_link_frame *frame, rt_link_frame_attribute_t attribute, rt_uint16_t parameter)
{
    frame->head.extend = 1;
    frame->extend.attribute = attribute;
    frame->extend.parameter = parameter;
    return RT_EOK;
}

static int rt_link_command_frame_send(rt_uint8_t sequence, rt_link_frame_attribute_t attribute, rt_uint16_t parameter)
{
    struct rt_link_frame command_frame = {0};
    rt_uint8_t extend_flag = RT_FALSE;

    /* command frame don't need crc and ack ability */
    rt_link_frame_init(&command_frame, RT_NULL);
    command_frame.head.sequence = sequence;
    command_frame.head.length = RT_LINK_MAX_EXTEND_LENGTH;
    command_frame.attribute = attribute;
    switch (attribute)
    {
    case RT_LINK_RESEND_FRAME:
        extend_flag = RT_TRUE;
        LOG_D("send RESEND_FRAME(%d).", command_frame.head.sequence);
        break;

    case RT_LINK_HANDSHAKE_FRAME:
        extend_flag = RT_TRUE;
        LOG_D("send HANDSHAKE_FRAME(%d).", command_frame.head.sequence);
        break;

    case RT_LINK_CONFIRM_FRAME:
        LOG_D("send CONFIRM_FRAME(%d).", command_frame.head.sequence);
        break;

    default:
        break;
    }

    if (extend_flag)
    {
        rt_link_frame_extend_config(&command_frame, attribute, parameter);
    }
    rt_link_frame_send(&command_frame.slist);
    return RT_EOK;
}

static rt_err_t rt_link_resend_handle(struct rt_link_frame *receive_frame)
{
    struct rt_link_frame *find_frame = RT_NULL;
    rt_slist_t *tem_list = RT_NULL;

    tem_list = rt_slist_first(&rt_link_scb->tx_data_slist);
    while (tem_list != RT_NULL)
    {
        find_frame = rt_container_of(tem_list, struct rt_link_frame, slist);
        if (find_frame->head.sequence == receive_frame->head.sequence)
        {
            LOG_D("resend frame(%d)", find_frame->head.sequence);
            rt_link_frame_send(&find_frame->slist);
            break;
        }
        tem_list = tem_list->next;
    }

    if (tem_list == RT_NULL)
    {
        LOG_D("frame resent failed, can't find(%d).", receive_frame->head.sequence);
        rt_link_command_frame_send(receive_frame->head.sequence, RT_LINK_SESSION_END, RT_NULL);
    }
    return RT_EOK;
}

static rt_err_t rt_link_confirm_handle(struct rt_link_frame *receive_frame)
{
    static struct rt_link_frame *send_frame = RT_NULL;
    struct rt_link_frame *find_frame = RT_NULL;
    rt_slist_t *tem_list = RT_NULL;
    rt_uint16_t seq_offset = 0;

    LOG_D("confirm seq(%d) frame", receive_frame->head.sequence);
    if (rt_link_scb->link_status == RT_LINK_NO_RESPONSE)
    {
        /* The handshake success and resends the data frame */
        LOG_D("link_status RT_LINK_CONNECT_DONE, resend data");
        rt_link_scb->link_status = RT_LINK_CONNECT_DONE;
        if (rt_slist_first(&rt_link_scb->tx_data_slist))
        {
            rt_event_send(&rt_link_scb->event, RT_LINK_SEND_READY_EVENT);
        }
        return RT_EOK;
    }

    /* Check to see if the frame is send for confirm */
    tem_list = rt_slist_first(&rt_link_scb->tx_data_slist);
    if (tem_list == RT_NULL)
    {
        return -RT_ERROR;
    }

    send_frame = rt_container_of(tem_list, struct rt_link_frame, slist);
    seq_offset = rt_link_check_seq(receive_frame->head.sequence,
                                   rt_link_scb->tx_seq);
    if (seq_offset <= send_frame->total)
    {
        LOG_D("confirm frame (%d)", receive_frame->head.sequence);
        for (int i = 0; i < seq_offset; i++)
        {
            find_frame = rt_container_of(tem_list, struct rt_link_frame, slist);
            LOG_D("confirm(%d), remove(%d)", receive_frame->head.sequence, find_frame->head.sequence);

            rt_enter_critical();
            rt_slist_remove(&rt_link_scb->tx_data_slist, &find_frame->slist);
            rt_exit_critical();
            find_frame->real_data = RT_NULL;
            rt_link_frame_free(find_frame);

            tem_list = rt_slist_first(&rt_link_scb->tx_data_slist);
            if (tem_list == RT_NULL)
            {
                break;
            }
        }
        rt_link_scb->tx_seq = receive_frame->head.sequence;
        rt_link_scb->link_status = RT_LINK_CONNECT_DONE;
        if (tem_list == RT_NULL)
        {
            LOG_D("SEND_OK");
            rt_event_send(&rt_link_scb->event, RT_LINK_SEND_OK_EVENT);
        }
        else
        {
            LOG_D("Continue sending");
            rt_event_send(&rt_link_scb->event, RT_LINK_SEND_READY_EVENT);
        }
    }
    return RT_EOK;
}

static rt_err_t rt_link_short_handle(struct rt_link_frame *receive_frame)
{
    LOG_D("Seq(%d) short data", receive_frame->head.sequence);
    rt_link_scb->rx_record.dataspace = rt_malloc(receive_frame->data_len);
    if (rt_link_scb->rx_record.dataspace != RT_NULL)
    {
        rt_link_command_frame_send(receive_frame->head.sequence, RT_LINK_CONFIRM_FRAME, RT_NULL);
        rt_link_scb->rx_record.rx_seq = receive_frame->head.sequence;

        if (rt_link_scb->channel[receive_frame->head.channel].upload_callback == RT_NULL)
        {
            rt_free(rt_link_scb->rx_record.dataspace);
            LOG_E("Channel %d has not been registered", receive_frame->head.channel);
        }
        else
        {
            rt_enter_critical();
            rt_link_hw_copy(rt_link_scb->rx_record.dataspace, receive_frame->real_data, receive_frame->data_len);
            rt_exit_critical();
            rt_link_scb->channel[receive_frame->head.channel].upload_callback(rt_link_scb->rx_record.dataspace, receive_frame->data_len);
        }
        rt_link_scb->rx_record.dataspace = RT_NULL;
        rt_link_frame_stop_receive(receive_frame);
    }
    else
    {
        LOG_W("short data %dB alloc failed", receive_frame->data_len);
    }
    receive_frame->real_data = RT_NULL;
    return 0;
}

static void _long_handle_first(struct rt_link_frame *receive_frame, rt_uint8_t *count_mask)
{
    if (receive_frame->extend.parameter % RT_LINK_MAX_DATA_LENGTH == 0)
    {
        receive_frame->total = receive_frame->extend.parameter / RT_LINK_MAX_DATA_LENGTH;
    }
    else
    {
        receive_frame->total = receive_frame->extend.parameter / RT_LINK_MAX_DATA_LENGTH + 1;
    }

    rt_link_scb->rx_record.total = receive_frame->total;
    rt_link_scb->rx_record.dataspace = rt_malloc(receive_frame->extend.parameter);
    if (rt_link_scb->rx_record.dataspace == RT_NULL)
    {
        LOG_W("long data %dB alloc failed.", receive_frame->extend.parameter);
    }

}

static void _long_handle_second(struct rt_link_frame *receive_frame, rt_uint8_t count_mask)
{
    static rt_uint8_t ack_mask = RT_LINK_ACK_MAX;

    void *data = RT_NULL;
    rt_size_t size = 0;
    rt_uint16_t serve = 0;
    rt_size_t offset = 0; /* offset, count from 0 */

    receive_frame->index = rt_link_check_seq(receive_frame->head.sequence, rt_link_scb->rx_record.rx_seq) - 1;
    LOG_D("index= %d, count= 0x%x, seq(%d), rxseq(%d)", receive_frame->index, rt_link_scb->rx_record.long_count, receive_frame->head.sequence, rt_link_scb->rx_record.rx_seq);

    if ((receive_frame->index > RT_LINK_FRAMES_MAX) || (rt_link_scb->rx_record.long_count & (0x01 << receive_frame->index)))
    {
        LOG_D("ERR:index %d, rx_seq %d", receive_frame->index, rt_link_scb->rx_record.rx_seq);
    }
    else if (rt_link_scb->rx_record.dataspace != RT_NULL)
    {
        LOG_D("long_count (0x%02x)index(%d)total(%d) seq(%d)", rt_link_scb->rx_record.long_count, receive_frame->index, receive_frame->total, receive_frame->head.sequence);
        rt_link_scb->rx_record.long_count |= (0x01 << receive_frame->index);
        offset = RT_LINK_MAX_DATA_LENGTH * receive_frame->index;

        rt_enter_critical();
        rt_link_hw_copy(rt_link_scb->rx_record.dataspace + offset, receive_frame->real_data, receive_frame->data_len);
        rt_exit_critical();

        if (rt_link_utils_num1(rt_link_scb->rx_record.long_count) == rt_link_scb->rx_record.total)
        {
            rt_link_command_frame_send((rt_link_scb->rx_record.rx_seq + rt_link_scb->rx_record.total), RT_LINK_CONFIRM_FRAME, RT_NULL);
        }
        else if ((rt_link_scb->rx_record.long_count & ack_mask) == ack_mask)
        {
            rt_link_command_frame_send((rt_link_scb->rx_record.rx_seq + rt_link_utils_num1(ack_mask)), RT_LINK_CONFIRM_FRAME, RT_NULL);
            ack_mask |= ack_mask << rt_link_utils_num1(RT_LINK_ACK_MAX);
        }

        /* receive a complete package */
        if (rt_link_utils_num1(rt_link_scb->rx_record.long_count) == rt_link_scb->rx_record.total)
        {
            rt_timer_stop(&rt_link_scb->longframetimer);

            rt_enter_critical();
            data = rt_link_scb->rx_record.dataspace;
            size = receive_frame->extend.parameter;
            serve = receive_frame->head.channel;
            /* empty  rx_record */
            rt_link_scb->rx_record.rx_seq += rt_link_scb->rx_record.total;
            rt_link_scb->rx_record.dataspace = RT_NULL;
            rt_link_scb->rx_record.long_count = 0;
            rt_link_scb->rx_record.total = 0;
            ack_mask = RT_LINK_ACK_MAX;
            rt_link_frame_stop_receive(receive_frame);
            rt_exit_critical();

            if (rt_link_scb->channel[serve].upload_callback == RT_NULL)
            {
                rt_free(data);
                LOG_E("channel %d haven't been registered.", serve);
            }
            else
            {
                rt_link_scb->channel[serve].upload_callback(data, size);
            }
        }
        else if (rt_link_hw_recv_len(rt_link_scb->rx_buffer) < (receive_frame->data_len % RT_LINK_MAX_DATA_LENGTH))
        {
            rt_int32_t timeout = RT_LINK_LONG_FRAME_TIMEOUT;
            rt_timer_control(&rt_link_scb->longframetimer, RT_TIMER_CTRL_SET_TIME, &timeout);
            rt_timer_start(&rt_link_scb->longframetimer);
        }
    }
}

static rt_err_t rt_link_long_handle(struct rt_link_frame *receive_frame)
{
    static rt_uint8_t count_mask = 0;
    if (rt_link_scb->rx_record.long_count == 0)
    {
        /* Receive this long package for the first time:
         * calculates the total number of frames,
         * requests space, and turns on the receive timer */
        _long_handle_first(receive_frame, &count_mask);
    }
    if (rt_link_scb->rx_record.total > 0)
    {
        /* Intermediate frame processing:
         * serial number repeated check,
         * receive completion check, reply to ACK */
        _long_handle_second(receive_frame, count_mask);
    }
    receive_frame->real_data = RT_NULL;
    return RT_EOK;
}

static rt_err_t rt_link_handshake_handle(struct rt_link_frame *receive_frame)
{
    LOG_D("Sequence(%d) is a connect handshake frame.", receive_frame->head.sequence);
    rt_link_scb->link_status = RT_LINK_CONNECT_DONE;
    /* sync requester tx seq, responder rx seq = requester tx seq */
    rt_link_scb->rx_record.rx_seq = receive_frame->head.sequence;
    /* sync requester rx seq, responder tx seq = requester rx seq */
    rt_link_scb->tx_seq = receive_frame->extend.parameter;
    rt_link_command_frame_send(receive_frame->head.sequence, RT_LINK_CONFIRM_FRAME, RT_NULL);
    return RT_EOK;
}

/* Discriminate frame type */
static rt_err_t rt_link_parse_frame(struct rt_link_frame *receive_frame)
{
    switch (receive_frame->attribute)
    {
    case RT_LINK_RESEND_FRAME:
        rt_link_resend_handle(receive_frame);
        break;
    case RT_LINK_CONFIRM_FRAME:
        rt_link_confirm_handle(receive_frame);
        break;
    case RT_LINK_SHORT_DATA_FRAME:
        rt_link_short_handle(receive_frame);
        break;
    case RT_LINK_LONG_DATA_FRAME:
        rt_link_long_handle(receive_frame);
        break;
    case RT_LINK_HANDSHAKE_FRAME:
        rt_link_handshake_handle(receive_frame);
        break;
    case RT_LINK_SESSION_END:
        rt_link_frame_stop_receive(receive_frame);
        break;
    default:
        break;
    }
    return RT_EOK;
}

/* Empty the sending list */
static void rt_link_datalist_empty(void)
{
    struct rt_link_frame *find_frame = RT_NULL;
    rt_slist_t *tem_list = rt_slist_first(&rt_link_scb->tx_data_slist);
    while (tem_list != RT_NULL)
    {
        find_frame = rt_container_of(tem_list, struct rt_link_frame, slist);
        tem_list = rt_slist_next(tem_list);
        rt_enter_critical();
        rt_slist_remove(&rt_link_scb->tx_data_slist, &find_frame->slist);
        rt_exit_critical();

        find_frame->real_data = RT_NULL;
        rt_link_frame_free(find_frame);
    }
}

/* RT_LINK_READ_CHECK_EVENT handle */
static void rt_link_frame_check(void)
{
    static struct rt_link_frame receive_frame = {0};
    static rt_link_frame_parse_t analysis_status = FIND_FRAME_HEAD;
    static rt_uint8_t *data = RT_NULL;
    static rt_uint16_t buff_len = RT_LINK_HEAD_LENGTH;

    struct rt_link_frame *send_frame = RT_NULL;
    rt_tick_t timeout = 0;
    rt_uint8_t *real_data = RT_NULL;
    rt_uint32_t temporary_crc = 0;

    rt_uint8_t offset = 0;
    rt_size_t recv_len = rt_link_hw_recv_len(rt_link_scb->rx_buffer);
    while (recv_len > 0)
    {
        switch (analysis_status)
        {
        case FIND_FRAME_HEAD:
        {
            /* if we can't find frame head, throw that data */
            if ((*rt_link_scb->rx_buffer->read_point & RT_LINK_FRAME_HEAD_MASK) == RT_LINK_FRAME_HEAD)
            {
                analysis_status = PARSE_FRAME_HEAD;
                break;
            }
            rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, 1);
            break;
        }

        case PARSE_FRAME_HEAD:
        {
            if (recv_len < buff_len)
            {
                LOG_D("The length is not enough,recv=%d buff=%d", recv_len, buff_len);
                return ;
            }
            /* Data is an offset address */
            data = rt_link_scb->rx_buffer->read_point;
            rt_link_frame_init(&receive_frame, RT_NULL);
            rt_link_hw_copy((rt_uint8_t *)&receive_frame.head, data, sizeof(struct rt_link_frame_head));
            rt_link_hw_buffer_point_shift(&data, sizeof(struct rt_link_frame_head));
            receive_frame.data_len = receive_frame.head.length;
            LOG_D("check seq(%d) data len(%d).", receive_frame.head.sequence, receive_frame.data_len);

            if (receive_frame.head.extend)
            {
                buff_len += RT_LINK_MAX_EXTEND_LENGTH;
                analysis_status = PARSE_FRAME_EXTEND;
            }
            else
            {
                analysis_status = PARSE_FRAME_SEQ;
            }
        }

        case PARSE_FRAME_EXTEND:
        {
            if (receive_frame.head.extend)
            {
                if (recv_len < buff_len)
                {
                    LOG_D("PARSE_FRAME_EXTEND: actual: %d, need: %d.", recv_len, buff_len);

                    /* should set timer, control receive frame timeout, one shot */
                    timeout = 50;
                    rt_timer_control(&rt_link_scb->recvtimer, RT_TIMER_CTRL_SET_TIME, &timeout);
                    rt_timer_start(&rt_link_scb->recvtimer);
                    return;
                }
                rt_link_hw_copy((rt_uint8_t *)&receive_frame.extend, data, sizeof(struct rt_link_extend));
                rt_link_hw_buffer_point_shift(&data, sizeof(struct rt_link_extend));
                switch (receive_frame.extend.attribute)
                {
                case RT_LINK_RESEND_FRAME:
                case RT_LINK_LONG_DATA_FRAME:
                case RT_LINK_HANDSHAKE_FRAME:
                    receive_frame.attribute = receive_frame.extend.attribute;
                    break;
                default:
                    receive_frame.attribute = RT_LINK_RESERVE_FRAME;
                    break;
                }
            }
            else
            {
                if (receive_frame.head.crc)
                {
                    receive_frame.attribute = RT_LINK_SHORT_DATA_FRAME;
                }
                else
                {
                    receive_frame.attribute = RT_LINK_CONFIRM_FRAME;
                }
            }
            if (receive_frame.attribute == RT_LINK_RESERVE_FRAME)
            {
                LOG_D("quick filter error frame.");
                rt_link_frame_stop_receive(&receive_frame);
                buff_len = RT_LINK_HEAD_LENGTH;
                analysis_status = FIND_FRAME_HEAD;
                break;
            }
            analysis_status = PARSE_FRAME_SEQ;
        }

        case PARSE_FRAME_SEQ:
        {
            if ((receive_frame.attribute == RT_LINK_CONFIRM_FRAME) || (receive_frame.attribute == RT_LINK_RESEND_FRAME))
            {
                offset = rt_link_check_seq(receive_frame.head.sequence, rt_link_scb->tx_seq);
                if (rt_slist_first(&rt_link_scb->tx_data_slist) != RT_NULL)
                {
                    send_frame = rt_container_of(rt_link_scb->tx_data_slist.next, struct rt_link_frame, slist);
                    if (offset > send_frame->total)
                    {
                        /* exceptional frame, ignore it */
                        LOG_D("seq (%d) failed, tx_seq (%d).offset=(%d) total= (%d)", receive_frame.head.sequence, rt_link_scb->tx_seq, offset, send_frame->total);
                        rt_link_frame_stop_receive(&receive_frame);
                        buff_len = RT_LINK_HEAD_LENGTH;
                        analysis_status = FIND_FRAME_HEAD;
                        break;
                    }
                }
            }
            else
            {
                offset = rt_link_check_seq(receive_frame.head.sequence, rt_link_scb->rx_record.rx_seq) - 1;
                if ((offset > RT_LINK_FRAMES_MAX) && (receive_frame.attribute != RT_LINK_HANDSHAKE_FRAME))
                {
                    /* exceptional frame, ignore it */
                    LOG_D("seq (%d) failed, rx_seq (%d) offset=(%d) attr= (%d) status (%d)", receive_frame.head.sequence, rt_link_scb->rx_record.rx_seq, offset, receive_frame.attribute, rt_link_scb->link_status);
                    rt_link_frame_stop_receive(&receive_frame);
                    buff_len = RT_LINK_HEAD_LENGTH;
                    analysis_status = FIND_FRAME_HEAD;
                    break;
                }
            }

            buff_len += receive_frame.data_len;
            if (receive_frame.head.crc)
            {
                buff_len += RT_LINK_CRC_LENGTH;
                analysis_status = CHECK_FRAME_CRC;
            }
            else
            {
                analysis_status = HEADLE_FRAME_DATA;
            }
        }

        case CHECK_FRAME_CRC:
        {
            if (receive_frame.head.crc)
            {
                if (recv_len < buff_len)
                {
                    /* should set timer, control receive frame timeout, one shot */
                    timeout = 50;
                    rt_timer_control(&rt_link_scb->recvtimer, RT_TIMER_CTRL_SET_TIME, &timeout);
                    rt_timer_start(&rt_link_scb->recvtimer);
                    return;
                }

                real_data = data;
                rt_timer_stop(&rt_link_scb->recvtimer);
                rt_link_hw_buffer_point_shift(&data, receive_frame.data_len);
                rt_link_hw_copy((rt_uint8_t *)&receive_frame.crc, data, RT_LINK_CRC_LENGTH);
                temporary_crc = rt_link_scb->calculate_crc(RT_TRUE, rt_link_scb->rx_buffer->read_point, buff_len - RT_LINK_CRC_LENGTH);
                if (receive_frame.crc != temporary_crc)
                {
                    /* check failed. ready resent */
                    LOG_D("CRC: calc:(0x%08x) ,recv:(0x%08x).", temporary_crc, receive_frame.crc);
                    /* quick resent, when sequence is right, we can ask for reset this frame */
                    rt_link_command_frame_send(receive_frame.head.sequence, RT_LINK_RESEND_FRAME, RT_NULL);

                    /* throw the error frame */
                    buff_len = RT_LINK_HEAD_LENGTH;
                    rt_link_frame_stop_receive(&receive_frame);

                    /* clear the frame information */
                    analysis_status = FIND_FRAME_HEAD;
                    break;
                }
                /* fill real data point */
                receive_frame.real_data = real_data;
            }
            analysis_status = HEADLE_FRAME_DATA;
        }

        case HEADLE_FRAME_DATA:
        {
            rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, buff_len);
            rt_link_parse_frame(&receive_frame);
            data = RT_NULL;
            buff_len = RT_LINK_HEAD_LENGTH;
            analysis_status = FIND_FRAME_HEAD;
            break;
        }

        default:
            LOG_E("analysis_status is error.");
            break;
        }
        recv_len = rt_link_hw_recv_len(rt_link_scb->rx_buffer);
    }
}

static void rt_link_send_ready(void)
{
    if (rt_link_scb->link_status != RT_LINK_CONNECT_DONE)
    {
        rt_link_scb->link_status = RT_LINK_NO_RESPONSE;
        rt_link_command_frame_send(rt_link_scb->tx_seq, RT_LINK_HANDSHAKE_FRAME, rt_link_scb->rx_record.rx_seq);
    }
    else
    {
        if (RT_EOK != rt_link_frame_send(&rt_link_scb->tx_data_slist))
        {
            rt_event_send(&rt_link_scb->event, RT_LINK_SEND_FAILED_EVENT);
        }
    }
}

static void rt_link_frame_recv_timeout(void)
{
    /* The receiving frame timeout and a new receive begins */
    rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, rt_link_hw_recv_len(rt_link_scb->rx_buffer));
}

static void rt_link_send_timeout(void)
{
    static rt_uint8_t count = 0;
    if (count++ > 5)
    {
        LOG_W("Send timeout, please check the link status!");
        count = 0;
        rt_event_send(&rt_link_scb->event, RT_LINK_SEND_FAILED_EVENT);
    }
    else
    {
        rt_timer_start(&rt_link_scb->sendtimer);
        rt_link_command_frame_send(rt_link_scb->tx_seq, RT_LINK_HANDSHAKE_FRAME, rt_link_scb->rx_record.rx_seq);
    }
}

static int rt_link_long_recv_timeout(void)
{
    static rt_uint8_t count = 0;
    if (count++ > 5)
    {
        LOG_W("long package receive timeout");
        count = 0;
        _stop_recv_long();
    }
    else
    {
        for (rt_uint8_t total = rt_link_scb->rx_record.total; total > 0; total--)
        {
            if (((rt_link_scb->rx_record.long_count >> (total - 1)) & 0x01) == 0x00)
            {
                /* resend command */
                rt_link_command_frame_send((rt_link_scb->rx_record.rx_seq + total), RT_LINK_RESEND_FRAME, RT_NULL);
            }
        }
    }
    return RT_EOK;
}

void rt_link_thread(void *parameter)
{
    rt_uint32_t recved = 0;
    while (1)
    {
        rt_event_recv(&rt_link_scb->event, RT_LINK_READ_CHECK_EVENT |
                      RT_LINK_SEND_READY_EVENT  |
                      RT_LINK_SEND_TIMEOUT_EVENT |
                      RT_LINK_RECV_TIMEOUT_FRAME_EVENT |
                      RT_LINK_RECV_TIMEOUT_LONG_EVENT,
                      RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      RT_WAITING_FOREVER,
                      &recved);

        if (recved & RT_LINK_READ_CHECK_EVENT)
        {
            rt_link_frame_check();
        }

        if (recved & RT_LINK_SEND_READY_EVENT)
        {
            rt_link_send_ready();
        }

        if (recved & RT_LINK_SEND_TIMEOUT_EVENT)
        {
            rt_link_send_timeout();
        }

        if (recved & RT_LINK_RECV_TIMEOUT_FRAME_EVENT)
        {
            rt_link_frame_recv_timeout();
        }

        if (recved & RT_LINK_RECV_TIMEOUT_LONG_EVENT)
        {
            rt_link_long_recv_timeout();
        }
    }
}

static void rt_link_sendtimer_callback(void *parameter)
{
    rt_event_send(&rt_link_scb->event, RT_LINK_SEND_TIMEOUT_EVENT);
}

static void rt_link_recvtimer_callback(void *parameter)
{
    rt_event_send(&rt_link_scb->event, RT_LINK_RECV_TIMEOUT_FRAME_EVENT);
}

static void rt_link_receive_long_frame_callback(void *parameter)
{
    rt_event_send(&rt_link_scb->event, RT_LINK_RECV_TIMEOUT_LONG_EVENT);
}

/**
 * rtlink send data interface
 * @param service   Registered service channel, choose enum rt_link_service_t
 * @param data      send data
 * @param size      send data size
 * @return The actual size of the data sent
 * */
rt_size_t rt_link_send(rt_link_service_t service, void *data, rt_size_t size)
{
    if ((size == 0) || (data == RT_NULL) || (service >= RT_LINK_SERVICE_MAX))
    {
        return 0;
    }
    rt_mutex_take(&rt_link_scb->tx_lock, RT_WAITING_FOREVER);

    rt_uint32_t recved = 0;
    rt_err_t result = RT_EOK;
    rt_uint32_t timeout = 0;

    rt_uint8_t total = 0; /* The total number of frames to send */
    rt_uint8_t index = 0; /* The index of the split packet */
    rt_size_t offset = 0; /* The offset of the send data */

    struct rt_link_frame *send_frame = RT_NULL;
    rt_link_frame_attribute_t attribute;
    if (size % RT_LINK_MAX_DATA_LENGTH == 0)
    {
        total = size / RT_LINK_MAX_DATA_LENGTH;
    }
    else
    {
        total = size / RT_LINK_MAX_DATA_LENGTH + 1;
    }

    if (total > RT_LINK_FRAMES_MAX)
    {
        result = -RT_ENOMEM;
        goto __exit;
    }
    else if (total > 1)
    {
        attribute =  RT_LINK_LONG_DATA_FRAME;
    }
    else
    {
        attribute = RT_LINK_SHORT_DATA_FRAME;
    }

    do
    {
        send_frame = rt_malloc(sizeof(struct rt_link_frame));
        rt_link_frame_init(send_frame, FRAME_CRC | FRAME_ACK);
        send_frame->head.sequence = rt_link_scb->tx_seq + 1 + index;
        send_frame->head.channel = service;
        send_frame->real_data = (rt_uint8_t *)data + offset;
        send_frame->index = index;
        send_frame->total = total;

        if (attribute == RT_LINK_LONG_DATA_FRAME)
        {
            send_frame->attribute = RT_LINK_LONG_DATA_FRAME;
            if (offset + RT_LINK_MAX_DATA_LENGTH > size)
            {
                send_frame->data_len = size - offset;
            }
            else
            {
                send_frame->data_len = RT_LINK_MAX_DATA_LENGTH;
                offset += RT_LINK_MAX_DATA_LENGTH;
            }

            rt_link_frame_extend_config(send_frame, RT_LINK_LONG_DATA_FRAME, size);
        }
        else
        {
            send_frame->attribute = RT_LINK_SHORT_DATA_FRAME;
            send_frame->data_len = size;
        }

        /* append the frame on the tail of list */
        LOG_D("new data append on the send slist, seq(%d), len(%d).", send_frame->head.sequence, send_frame->data_len);
        rt_slist_append(&rt_link_scb->tx_data_slist, &send_frame->slist);

        index++;
    }while(total > index);

    timeout = RT_LINK_SENT_FRAME_TIMEOUT * total;
    rt_timer_control(&rt_link_scb->sendtimer, RT_TIMER_CTRL_SET_TIME, &timeout);
    rt_timer_start(&rt_link_scb->sendtimer);
    /* Notify the core thread to send packet */
    rt_event_send(&rt_link_scb->event, RT_LINK_SEND_READY_EVENT);

    /* Wait for the packet to be sent successfully */
    rt_event_recv(&rt_link_scb->event, RT_LINK_SEND_OK_EVENT | RT_LINK_SEND_FAILED_EVENT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved);

    if (recved & RT_LINK_SEND_OK_EVENT)
    {
        result = RT_EOK;
    }
    else if (recved & RT_LINK_SEND_FAILED_EVENT)
    {
        LOG_E("the data (%dB) send failed", size);
        result = -RT_ERROR;
    }
    else
    {
        LOG_E("unexpected event.");
        result = -RT_ERROR;
    }
__exit:
    rt_timer_stop(&rt_link_scb->sendtimer);
    /* Empty the sending list */
    rt_link_datalist_empty();
    rt_mutex_release(&rt_link_scb->tx_lock);
    if (result == RT_EOK)
    {
        return size;
    }
    return result;
}

void rtlink_status(void)
{
    rt_kprintf("rtlink status:\n");
    if (rt_link_scb != RT_NULL)
    {
        rt_kprintf("\tlink status=%d\n", rt_link_scb->link_status);

        rt_kprintf("\trx seq=%d\n", rt_link_scb->rx_record.rx_seq);
        rt_kprintf("\ttx seq=%d\n", rt_link_scb->tx_seq);
        rt_kprintf("\trecv len=%d\n", rt_link_hw_recv_len(rt_link_scb->rx_buffer));

        rt_tick_t state = 0;
        rt_timer_control(&rt_link_scb->longframetimer, RT_TIMER_CTRL_GET_STATE, &state);
        rt_kprintf("\tlong timer state=%d\n", state);
        rt_timer_control(&rt_link_scb->sendtimer, RT_TIMER_CTRL_GET_STATE, &state);
        rt_kprintf("\tsend timer state=%d\n", state);

        rt_kprintf("\tevent set=0x%08x\n", rt_link_scb->event.set);
        if (rt_link_scb->tx_data_slist.next)
        {
            rt_slist_t *data = RT_NULL;
            rt_slist_for_each(data, &rt_link_scb->tx_data_slist)
            {
                rt_kprintf("\tsend data list: serv %u\t", ((struct rt_link_frame_head *)data)->channel);
                rt_kprintf(" seq %u\t", ((struct rt_link_frame_head *)data)->sequence);
                rt_kprintf(" len %u\n", ((struct rt_link_frame_head *)data)->length);
            }
        }
        else
        {
            rt_kprintf("\tsend data list: NULL\n");
        }

        rt_uint8_t serv = sizeof(rt_link_scb->channel) / sizeof(struct rt_link_service);
        while (serv--)
        {
            rt_kprintf("\tservices [%d](0x%p)\n", serv, rt_link_scb->channel[serv]);
        }
    }
    else
    {
        rt_kprintf("status NULL, please check the initialization status!\n");
    }
}
MSH_CMD_EXPORT(rtlink_status, Display RTLINK status);

/**
 * rtlink deinit the interface
 * */
rt_err_t rt_link_deinit(void)
{
    rt_enter_critical();
    rt_link_hw_deinit();
    if (rt_link_scb)
    {
        rt_timer_detach(&rt_link_scb->longframetimer);
        rt_timer_detach(&rt_link_scb->sendtimer);
        rt_timer_detach(&rt_link_scb->recvtimer);
        rt_mutex_detach(&rt_link_scb->tx_lock);
        rt_event_detach(&rt_link_scb->event);
        rt_free(rt_link_scb);
        rt_link_scb = RT_NULL;
    }
    rt_thread_t thread = rt_thread_find(RT_LINK_THREAD_NAME);
    if (thread)
    {
        rt_thread_delete(thread);
    }
    rt_exit_critical();
    return RT_EOK;
}
MSH_CMD_EXPORT(rt_link_deinit, rt link deinit);

/**
 * rtlink initializes the interface, usually automatically.
 * @return int Function Execution Result
 * */
int rt_link_init(void)
{
    rt_err_t result = RT_EOK;
    rt_thread_t thread = RT_NULL;

    if (rt_link_scb != RT_NULL)
    {
        goto __exit;
    }

    rt_link_scb = rt_malloc(sizeof(struct rt_link_session));
    if (rt_link_scb == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    }

    rt_memset(rt_link_scb, 0, sizeof(struct rt_link_session));
    rt_event_init(&rt_link_scb->event, "lny_event", RT_IPC_FLAG_FIFO);
    rt_event_control(&rt_link_scb->event, RT_IPC_CMD_RESET, RT_NULL);

    rt_mutex_init(&rt_link_scb->tx_lock, "tx_lock", RT_IPC_FLAG_FIFO);
    rt_timer_init(&rt_link_scb->sendtimer, "tx_time", rt_link_sendtimer_callback,
                  RT_NULL, 0, RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_PERIODIC);
    rt_timer_init(&rt_link_scb->recvtimer, "rx_time", rt_link_recvtimer_callback,
                  RT_NULL, 0, RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_ONE_SHOT);
    rt_timer_init(&rt_link_scb->longframetimer, "rxl_time", rt_link_receive_long_frame_callback,
                  RT_NULL, 0, RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_PERIODIC);

    rt_link_scb->link_status = RT_LINK_ESTABLISHING;

    rt_link_scb->rx_record.rx_seq = 255;

    rt_slist_init(&rt_link_scb->tx_data_slist);
    rt_link_scb->tx_seq = RT_LINK_INIT_FRAME_SEQENCE;

    /* create rtlink core work thread */
    thread = rt_thread_create(RT_LINK_THREAD_NAME,
                              rt_link_thread,
                              RT_NULL,
                              RT_LINK_THREAD_STACK_SIZE,
                              RT_LINK_THREAD_PRIORITY,
                              RT_LINK_THREAD_TICK);
    if (thread == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    }
    rt_thread_startup(thread);
    result = rt_link_hw_init();

__exit:
    if (result != RT_EOK)
    {
        LOG_E("rtlink init failed.");
        rt_link_deinit();
    }
    else
    {
        LOG_I("rtlink init success.");
    }
    return result;
}
#ifdef RT_LINK_AUTO_INIT
    INIT_ENV_EXPORT(rt_link_init);
#endif
MSH_CMD_EXPORT(rt_link_init, rt link init);

/**
 * rtlink service attach
 * @param service   Registered service channel, choose enum rt_link_service_t
 * @param function  receive callback function
 * @return Function Execution Result
 * */
rt_err_t rt_link_service_attach(rt_link_service_t service, rt_err_t (*function)(void *data, rt_size_t size))
{
    if (service >= RT_LINK_SERVICE_MAX)
    {
        LOG_W("Invalid parameter.");
        return -RT_ERROR;
    }
    rt_link_scb->channel[service].upload_callback = function;
    LOG_I("rt link attach service[%02d].", service);
    return RT_EOK;
}

/**
 * rtlink service detach
 * @param service   Registered service channel, choose enum rt_link_service_t
 * @return rt_err_t Function Execution Result
 * */
rt_err_t rt_link_service_detach(rt_link_service_t service)
{
    if (service >= RT_LINK_SERVICE_MAX)
    {
        LOG_W("Invalid parameter.");
        return -RT_ERROR;
    }
    rt_link_scb->channel[service].upload_callback = RT_NULL;
    LOG_I("rt link detach service[%02d].", service);
    return RT_EOK;
}
