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
 * 2021-05-10     Sherman      Add rtlink_status MSH command;
 *                             Optimize transmission timer Settings;
 *                             Fix known bugs
 * 2021-08-06     Sherman      Add NACK, NCRC, non-blocking transmit mode;
 *                             Add service connection status;
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
    #define RT_LINK_SENT_FRAME_TIMEOUT      100
#endif /* RT_LINK_USING_SPI */

#define RT_LINK_RECV_DATA_SEQUENCE      0
#define RT_LINK_INIT_FRAME_SEQENCE      129

#define RT_LINK_THREAD_NAME         "rtlink"
#define RT_LINK_THREAD_TICK         20
#define RT_LINK_THREAD_PRIORITY     25
#define RT_LINK_THREAD_STACK_SIZE   1024 /* 32 bytes aligned */

#define RT_LINK_FRAME_SENT      1
#define RT_LINK_FRAME_NOSEND    0

typedef enum
{
    FIND_FRAME_HEAD     = 0,
    PARSE_FRAME_HEAD    = 1,
    PARSE_FRAME_EXTEND  = 2,
    PARSE_FRAME_SEQ     = 3,
    CHECK_FRAME_CRC     = 4,
    HEADLE_FRAME_DATA   = 5,
} rt_link_frame_parse_t;

/* rtlink SCB(Session control block) */
static struct rt_link_session *rt_link_scb = RT_NULL;
struct rt_link_session *rt_link_get_scb(void)
{
    return rt_link_scb;
}

static rt_uint8_t rt_link_check_seq(rt_uint8_t new, rt_uint8_t used)
{
    rt_int16_t compare_seq = 0;
    compare_seq = new - used;
    if (compare_seq < 0)
    {
        compare_seq = compare_seq + 256;
    }
    return (rt_uint8_t)compare_seq;
}

static int rt_link_frame_init(struct rt_link_frame *frame, rt_uint8_t config)
{
    if (frame == RT_NULL)
    {
        return -RT_ERROR;
    }

    /* set frame control information */
    rt_memset(&frame->head, 0, sizeof(struct rt_link_frame_head));
    if (config & RT_LINK_FLAG_CRC)
    {
        frame->head.crc = 1;
    }
    if (config & RT_LINK_FLAG_ACK)
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
    frame->issent = RT_LINK_FRAME_NOSEND;

    rt_slist_init(&frame->slist);

    return RT_EOK;
}

/* remove the sending list node*/
static void rt_link_frame_remove(struct rt_link_service *service)
{
    RT_ASSERT(service != RT_NULL);
    struct rt_link_frame *find_frame = RT_NULL;
    rt_uint8_t total = 0;
    rt_slist_t *tem_list = rt_slist_first(&rt_link_scb->tx_data_slist);
    if (tem_list != RT_NULL)
    {
        do
        {
            find_frame = rt_container_of(tem_list, struct rt_link_frame, slist);
            tem_list = rt_slist_next(tem_list);
            if (find_frame->head.service == service->service)
            {
                if (total == 0)
                {
                    total = find_frame->total;
                }
                /* The data frame order is appended to the list,
                with total counting starting at 1 and index counting from 0 */
                LOG_D("remove seq(%d) serv (%d)", find_frame->head.sequence, service->service);
                rt_enter_critical();
                rt_slist_remove(&rt_link_scb->tx_data_slist, &find_frame->slist);
                rt_exit_critical();
                total--;
                rt_memset(find_frame, 0, sizeof(struct rt_link_frame));
                rt_free(find_frame);
            }
        } while ((total > 0) && (tem_list != RT_NULL));
    }
}

/* Configure the extended field of the frame */
static rt_err_t rt_link_frame_extend_config(struct rt_link_frame *frame, rt_link_frame_attr_e attribute, rt_uint16_t parameter)
{
    frame->head.extend = 1;
    frame->extend.attribute = attribute;
    frame->extend.parameter = parameter;
    return RT_EOK;
}

static int rt_link_command_frame_send(rt_uint16_t serv, rt_uint8_t sequence, rt_link_frame_attr_e attribute, rt_uint16_t parameter)
{
    struct rt_link_frame command_frame = {0};
    rt_uint8_t data[sizeof(command_frame.head) + sizeof(command_frame.extend)] = {0};
    rt_uint8_t data_len = 0;

    /* command frame don't need crc and ack ability */
    rt_link_frame_init(&command_frame, RT_NULL);
    data_len += sizeof(command_frame.head);

    rt_link_frame_extend_config(&command_frame, attribute, parameter);
    rt_memcpy(data + data_len, &command_frame.extend, sizeof(command_frame.extend));
    data_len += sizeof(command_frame.extend);

    command_frame.head.sequence = sequence;
    command_frame.head.service = serv;
    rt_memcpy(data, &command_frame.head, sizeof(command_frame.head));

    rt_link_hw_send(data, data_len);
    return RT_EOK;
}

static void rt_link_service_send_finish(rt_link_err_e err)
{
    struct rt_link_frame *frame = RT_NULL;
    rt_uint16_t service = RT_LINK_SERVICE_MAX;
    void *buffer = RT_NULL;
    rt_slist_t *tem_list = rt_slist_first(&rt_link_scb->tx_data_slist);
    if (tem_list == RT_NULL)
    {
        return ;
    }
    frame = rt_container_of(tem_list, struct rt_link_frame, slist);
    if (frame)
    {
        service = frame->head.service;
        buffer = frame->real_data - (frame->index * RT_LINK_MAX_DATA_LENGTH);
        rt_link_scb->service[service]->err = err;
        rt_link_scb->sendtimer.parameter = 0;
        rt_link_frame_remove(rt_link_scb->service[service]);
        if (rt_link_scb->service[service]->timeout_tx != RT_WAITING_NO)
        {
            rt_event_send(&rt_link_scb->sendevent, (0x01 << service));
        }
        else
        {
            rt_link_scb->service[service]->send_cb(rt_link_scb->service[service], buffer);
        }
    }
}

static rt_size_t frame_send(struct rt_link_frame *frame)
{
    rt_size_t length = 0;
    rt_uint8_t *data = RT_NULL;

    rt_memset(rt_link_scb->sendbuffer, 0, sizeof(rt_link_scb->sendbuffer));
    data = rt_link_scb->sendbuffer;
    length = RT_LINK_HEAD_LENGTH;
    if (frame->head.crc)
    {
        length += RT_LINK_CRC_LENGTH;
    }
    if (frame->head.extend)
    {
        length += RT_LINK_EXTEND_LENGTH;
    }

    length += frame->data_len;
    frame->head.length = frame->data_len;
    rt_memcpy(data, &frame->head, RT_LINK_HEAD_LENGTH);
    data = data + RT_LINK_HEAD_LENGTH;
    if (frame->head.extend)
    {
        rt_memcpy(data, &frame->extend, RT_LINK_EXTEND_LENGTH);
        data = data + RT_LINK_EXTEND_LENGTH;
    }
    if (frame->attribute == RT_LINK_SHORT_DATA_FRAME || frame->attribute == RT_LINK_LONG_DATA_FRAME)
    {
        rt_memcpy(data, frame->real_data, frame->data_len);
        data = data + frame->data_len;
    }
    if (frame->head.crc)
    {
        frame->crc = rt_link_scb->calculate_crc(RT_FALSE, rt_link_scb->sendbuffer, length - RT_LINK_CRC_LENGTH);
        rt_memcpy(data, &frame->crc, RT_LINK_CRC_LENGTH);
    }

    LOG_D("frame send seq(%d) len(%d) attr:(%d), crc:(0x%08x).", frame->head.sequence, length, frame->attribute, frame->crc);
    return rt_link_hw_send(rt_link_scb->sendbuffer, length);
}

/* performs data transmission */
static rt_err_t rt_link_frame_send(rt_slist_t *slist)
{
    rt_uint8_t is_finish = RT_FALSE;
    struct rt_link_frame *frame = RT_NULL;
    rt_uint8_t send_max = RT_LINK_ACK_MAX;

    /* if slist is tx_data_slist, we should send all data on the slist*/
    if (slist == &rt_link_scb->tx_data_slist)
    {
        slist = rt_slist_next(&rt_link_scb->tx_data_slist);
    }
    if (slist == RT_NULL)
    {
        LOG_W("send data list NULL");
        return -RT_ERROR;
    }

    do
    {
        /* get frame for send */
        frame = rt_container_of(slist, struct rt_link_frame, slist);
        slist = rt_slist_next(slist);

        if (frame_send(frame) == 0)
        {
            rt_link_scb->service[frame->head.service]->err = RT_LINK_EIO;
            goto __err;
        }
        frame->issent = RT_LINK_FRAME_SENT;
        if ((slist == RT_NULL) || (frame->index + 1 >= frame->total))
        {
            send_max = 0;
            is_finish = RT_TRUE;
        }
        else
        {
            send_max >>= 1;
        }
    }while (send_max);

    if ((is_finish) && (frame->head.ack == 0))
    {
        /* NACK frame send finish, remove after sending */
        rt_link_service_send_finish(RT_LINK_EOK);
        if (slist != RT_NULL)
        {
            LOG_D("Continue sending");
            rt_event_send(&rt_link_scb->event, RT_LINK_SEND_READY_EVENT);
        }
    }
    else
    {
        rt_int32_t timeout = RT_LINK_SENT_FRAME_TIMEOUT;
        rt_timer_control(&rt_link_scb->sendtimer, RT_TIMER_CTRL_SET_TIME, &timeout);
        rt_timer_start(&rt_link_scb->sendtimer);
    }
    return RT_EOK;
__err:
    return -RT_ERROR;
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
    if (rt_link_scb->rx_record.dataspace)
    {
        rt_free(rt_link_scb->rx_record.dataspace);
    }
    rt_link_scb->rx_record.dataspace = RT_NULL;
    rt_link_scb->rx_record.long_count = 0;
    rt_link_scb->rx_record.total = 0;

    rt_timer_stop(&rt_link_scb->recvtimer);
    rt_link_scb->recvtimer.parameter = 0;
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
            frame_send(find_frame);
            break;
        }
        tem_list = tem_list->next;
    }

    if (tem_list == RT_NULL)
    {
        LOG_D("frame resent failed, can't find(%d).", receive_frame->head.sequence);
        rt_link_command_frame_send(receive_frame->head.service,
                                   receive_frame->head.sequence,
                                   RT_LINK_SESSION_END, RT_NULL);
    }
    return RT_EOK;
}

static rt_err_t rt_link_confirm_handle(struct rt_link_frame *receive_frame)
{
    static struct rt_link_frame *send_frame = RT_NULL;
    rt_slist_t *tem_list = RT_NULL;
    rt_uint16_t seq_offset = 0;
    LOG_D("confirm seq(%d) frame", receive_frame->head.sequence);

    rt_timer_stop(&rt_link_scb->sendtimer);

    if (rt_link_scb->service[receive_frame->head.service] != RT_NULL)
    {
        rt_link_scb->service[receive_frame->head.service]->state = RT_LINK_CONNECT;
    }

    if (rt_link_scb->state != RT_LINK_CONNECT)
    {
        /* The handshake success and resends the data frame */
        rt_link_scb->state = RT_LINK_CONNECT;
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
    seq_offset = rt_link_check_seq(receive_frame->head.sequence, send_frame->head.sequence);
    if (seq_offset <= send_frame->total)
    {
        rt_link_service_send_finish(RT_LINK_EOK);
        rt_link_scb->state = RT_LINK_CONNECT;

        tem_list = rt_slist_first(&rt_link_scb->tx_data_slist);
        if (tem_list != RT_NULL)
        {
            LOG_D("Continue sending");
            rt_event_send(&rt_link_scb->event, RT_LINK_SEND_READY_EVENT);
        }
    }
    return RT_EOK;
}

/* serv type rt_link_service_e */
static void rt_link_recv_finish(rt_uint16_t serv, void *data, rt_size_t size)
{
    if (rt_link_scb->service[serv] == RT_NULL)
    {
        rt_link_command_frame_send(serv, 0, RT_LINK_DETACH_FRAME, RT_NULL);
        return;
    }

    if (rt_link_scb->service[serv]->recv_cb == RT_NULL)
    {
        rt_free(data);
        LOG_W("service %d haven't been registered.", serv);
    }
    else
    {
        rt_link_scb->service[serv]->recv_cb(rt_link_scb->service[serv], data, size);
    }
}

static rt_err_t rt_link_short_handle(struct rt_link_frame *receive_frame)
{
    LOG_D("Seq(%d) short data", receive_frame->head.sequence);
    rt_link_scb->rx_record.dataspace = rt_malloc(receive_frame->data_len);
    if (rt_link_scb->rx_record.dataspace != RT_NULL)
    {
        if (receive_frame->head.ack)
        {
            rt_link_command_frame_send(receive_frame->head.service,
                                       receive_frame->head.sequence,
                                       RT_LINK_CONFIRM_FRAME, RT_NULL);
        }
        rt_link_scb->rx_record.rx_seq = receive_frame->head.sequence;
        rt_link_hw_copy(rt_link_scb->rx_record.dataspace, receive_frame->real_data, receive_frame->data_len);
        rt_link_recv_finish(receive_frame->head.service, rt_link_scb->rx_record.dataspace, receive_frame->data_len);
        rt_link_scb->rx_record.dataspace = RT_NULL;
    }
    else
    {
        LOG_W("short data %dB alloc failed", receive_frame->data_len);
    }
    receive_frame->real_data = RT_NULL;
    return 0;
}

static void _long_handle_first(struct rt_link_frame *receive_frame)
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
        LOG_W("long data (%dB) alloc failed.", receive_frame->extend.parameter);
    }
}

static void _long_handle_second(struct rt_link_frame *receive_frame)
{
    static rt_uint8_t ack_mask = RT_LINK_ACK_MAX;
    rt_size_t offset = 0; /* offset, count from 0 */

    receive_frame->index = rt_link_check_seq(receive_frame->head.sequence, rt_link_scb->rx_record.rx_seq) - 1;
    LOG_D("seq(%d), rxseq(%d), index(%d), total(%d), count(0x%x)"
          , receive_frame->head.sequence
          , rt_link_scb->rx_record.rx_seq
          , receive_frame->index
          , receive_frame->total
          , rt_link_scb->rx_record.long_count);

    if ((receive_frame->index > RT_LINK_FRAMES_MAX) || (rt_link_scb->rx_record.long_count & (0x01 << receive_frame->index)))
    {
        LOG_D("ERR:index %d, rx_seq %d", receive_frame->index, rt_link_scb->rx_record.rx_seq);
    }
    else if (rt_link_scb->rx_record.dataspace != RT_NULL)
    {
        rt_link_scb->rx_record.long_count |= (0x01 << receive_frame->index);
        offset = RT_LINK_MAX_DATA_LENGTH * receive_frame->index;
        rt_link_hw_copy(rt_link_scb->rx_record.dataspace + offset, receive_frame->real_data, receive_frame->data_len);

        if (receive_frame->head.ack)
        {
            if (rt_link_utils_num1(rt_link_scb->rx_record.long_count) == rt_link_scb->rx_record.total)
            {
                rt_link_command_frame_send(receive_frame->head.service,
                                           (rt_link_scb->rx_record.rx_seq + rt_link_scb->rx_record.total),
                                           RT_LINK_CONFIRM_FRAME, RT_NULL);
            }
            else if ((rt_link_scb->rx_record.long_count & ack_mask) == ack_mask)
            {
                rt_link_command_frame_send(receive_frame->head.service,
                                           (rt_link_scb->rx_record.rx_seq + rt_link_utils_num1(ack_mask)),
                                           RT_LINK_CONFIRM_FRAME, RT_NULL);
                ack_mask |= ack_mask << rt_link_utils_num1(RT_LINK_ACK_MAX);
            }
        }

        /* receive a complete package */
        if (rt_link_utils_num1(rt_link_scb->rx_record.long_count) == rt_link_scb->rx_record.total)
        {
            rt_timer_stop(&rt_link_scb->longframetimer);
            rt_link_recv_finish(receive_frame->head.service, rt_link_scb->rx_record.dataspace, receive_frame->extend.parameter);

            rt_enter_critical();
            /* empty  rx_record */
            rt_link_scb->rx_record.rx_seq += rt_link_scb->rx_record.total;
            rt_link_scb->rx_record.dataspace = RT_NULL;
            rt_link_scb->rx_record.long_count = 0;
            rt_link_scb->rx_record.total = 0;
            ack_mask = RT_LINK_ACK_MAX;
            rt_exit_critical();
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
    if (rt_link_scb->rx_record.long_count == 0)
    {
        /* Receive this long package for the first time:
         * calculates the total number of frames,
         * requests space, and turns on the receive timer */
        _long_handle_first(receive_frame);
    }
    if (rt_link_scb->rx_record.total > 0)
    {
        /* Intermediate frame processing:
         * serial number repeated check,
         * receive completion check, reply to ACK */
        _long_handle_second(receive_frame);
    }
    receive_frame->real_data = RT_NULL;
    return RT_EOK;
}

static rt_err_t rt_link_handshake_handle(struct rt_link_frame *receive_frame)
{
    LOG_D("HANDSHAKE: seq(%d) param(%d)", receive_frame->head.sequence, receive_frame->extend.parameter);
    rt_link_scb->state = RT_LINK_CONNECT;
    /* sync requester tx seq, responder rx seq = requester tx seq */
    rt_link_scb->rx_record.rx_seq = receive_frame->head.sequence;
    /* sync requester rx seq, responder tx seq = requester rx seq */
    rt_link_scb->tx_seq = (rt_uint8_t)receive_frame->extend.parameter;

    if (rt_link_scb->service[receive_frame->head.service] != RT_NULL)
    {
        rt_link_scb->service[receive_frame->head.service]->state = RT_LINK_CONNECT;
        rt_link_command_frame_send(receive_frame->head.service,
                                   receive_frame->head.sequence,
                                   RT_LINK_CONFIRM_FRAME, RT_NULL);
    }
    else
    {
        rt_link_command_frame_send(receive_frame->head.service,
                                   receive_frame->head.sequence,
                                   RT_LINK_DETACH_FRAME, RT_NULL);
    }
    return RT_EOK;
}

static rt_err_t rt_link_detach_handle(struct rt_link_frame *receive_frame)
{
    if (rt_link_scb->service[receive_frame->head.service] != RT_NULL)
    {
        rt_link_scb->service[receive_frame->head.service]->state = RT_LINK_DISCONN;
    }
    return RT_EOK;
}

static rt_err_t rt_link_session_end_handle(struct rt_link_frame *receive_frame)
{
    rt_link_frame_stop_receive(receive_frame);
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
    case RT_LINK_HANDSHAKE_FRAME:
        rt_link_handshake_handle(receive_frame);
        break;
    case RT_LINK_SESSION_END:
        rt_link_session_end_handle(receive_frame);
        break;
    case RT_LINK_DETACH_FRAME:
        rt_link_detach_handle(receive_frame);
        break;

    case RT_LINK_SHORT_DATA_FRAME:
        rt_link_short_handle(receive_frame);
        break;
    case RT_LINK_LONG_DATA_FRAME:
        rt_link_long_handle(receive_frame);
        break;

    default:
        return -RT_ERROR;
    }
    return RT_EOK;
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
                LOG_D("HEAD: actual: %d, need: %d.", recv_len, buff_len);
                return ;
            }
            /* Data is an offset address */
            data = rt_link_scb->rx_buffer->read_point;
            rt_link_frame_init(&receive_frame, RT_NULL);
            rt_link_hw_copy((rt_uint8_t *)&receive_frame.head, data, sizeof(struct rt_link_frame_head));
            rt_link_hw_buffer_point_shift(&data, sizeof(struct rt_link_frame_head));

            LOG_D("HEAD: seq(%d) serv(%d) ack(%d) crc(%d) ext(%d) len(%d) attr(%d)(0x%x)"
                  , receive_frame.head.sequence
                  , receive_frame.head.service
                  , receive_frame.head.ack
                  , receive_frame.head.crc
                  , receive_frame.head.extend
                  , receive_frame.head.length
                  , receive_frame.extend.attribute
                  , receive_frame.extend.parameter);

            receive_frame.data_len = receive_frame.head.length;
            if (receive_frame.head.service >= RT_LINK_SERVICE_MAX)
            {
                rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, 1);
                goto __find_head;
            }

            if (receive_frame.head.extend)
            {
                buff_len += RT_LINK_EXTEND_LENGTH;
                analysis_status = PARSE_FRAME_EXTEND;
            }
            else
            {
                receive_frame.attribute = RT_LINK_SHORT_DATA_FRAME;
                analysis_status = PARSE_FRAME_SEQ;
            }
        }

        case PARSE_FRAME_EXTEND:
        {
            if (receive_frame.head.extend)
            {
                if (recv_len < buff_len)
                {
                    LOG_D("EXTEND: actual: %d, need: %d.", recv_len, buff_len);
                    /* should set timer, control receive frame timeout, one shot */
                    timeout = 50;
                    rt_timer_control(&rt_link_scb->recvtimer, RT_TIMER_CTRL_SET_TIME, &timeout);
                    rt_timer_start(&rt_link_scb->recvtimer);
                    return;
                }
                rt_timer_stop(&rt_link_scb->recvtimer);
                rt_link_hw_copy((rt_uint8_t *)&receive_frame.extend, data, sizeof(struct rt_link_extend));
                rt_link_hw_buffer_point_shift(&data, sizeof(struct rt_link_extend));
                if (receive_frame.extend.attribute < RT_LINK_RESERVE_FRAME)
                {
                    receive_frame.attribute = receive_frame.extend.attribute;
                }
                else
                {
                    LOG_D("EXTEND: attr(%d) err", receive_frame.extend.attribute);
                    rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, 1);
                    goto __find_head;
                }
            }
            analysis_status = PARSE_FRAME_SEQ;
        }

        case PARSE_FRAME_SEQ:
        {
            switch (receive_frame.attribute)
            {
            case RT_LINK_CONFIRM_FRAME:
            case RT_LINK_RESEND_FRAME:
            {
                /* Check the send sequence */
                offset = rt_link_check_seq(receive_frame.head.sequence, rt_link_scb->tx_seq);
                if (rt_slist_first(&rt_link_scb->tx_data_slist) != RT_NULL)
                {
                    send_frame = rt_container_of(rt_link_scb->tx_data_slist.next, struct rt_link_frame, slist);
                    if (offset > send_frame->total)
                    {
                        /* exceptional frame, ignore it */
                        LOG_D("seq (%d) failed, tx_seq (%d).offset=(%d) total= (%d)", receive_frame.head.sequence, rt_link_scb->tx_seq, offset, send_frame->total);
                        rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, 1);
                        goto __find_head;
                    }
                }
                break;
            }
            case RT_LINK_LONG_DATA_FRAME:
            case RT_LINK_SHORT_DATA_FRAME:
            case RT_LINK_SESSION_END:
            {
                /* Check the receive sequence */
                offset = rt_link_check_seq(receive_frame.head.sequence, rt_link_scb->rx_record.rx_seq) - 1;
                if (offset > RT_LINK_FRAMES_MAX)
                {
                    /* exceptional frame, ignore it */
                    LOG_D("seq (%d) failed, rx_seq (%d) offset=(%d) attr= (%d) status (%d)", receive_frame.head.sequence, rt_link_scb->rx_record.rx_seq, offset, receive_frame.attribute, rt_link_scb->state);
                    rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, 1);
                    goto __find_head;
                }
            }
            case RT_LINK_HANDSHAKE_FRAME:
            case RT_LINK_DETACH_FRAME:
                analysis_status = HEADLE_FRAME_DATA;
                break;

            default:
                LOG_D("quick filter error frame.");
                rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, 1);
                goto __find_head;
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
            /* fill real data point */
            receive_frame.real_data = data;
        }

        case CHECK_FRAME_CRC:
        {
            if (receive_frame.head.crc)
            {
                if (recv_len < buff_len)
                {
                    LOG_D("CRC: actual: %d, need: %d.", recv_len, buff_len);
                    /* should set timer, control receive frame timeout, one shot */
                    timeout = 50;
                    rt_timer_control(&rt_link_scb->recvtimer, RT_TIMER_CTRL_SET_TIME, &timeout);
                    rt_timer_start(&rt_link_scb->recvtimer);
                    return;
                }

                rt_timer_stop(&rt_link_scb->recvtimer);
                rt_link_hw_buffer_point_shift(&data, receive_frame.data_len);
                rt_link_hw_copy((rt_uint8_t *)&receive_frame.crc, data, RT_LINK_CRC_LENGTH);
                temporary_crc = rt_link_scb->calculate_crc(RT_TRUE, rt_link_scb->rx_buffer->read_point, buff_len - RT_LINK_CRC_LENGTH);
                if (receive_frame.crc != temporary_crc)
                {
                    /* check failed. ready resent */
                    LOG_D("CRC: calc:(0x%08x) ,recv:(0x%08x).", temporary_crc, receive_frame.crc);
                    rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, 1);
                    goto __find_head;
                }
            }
            analysis_status = HEADLE_FRAME_DATA;
        }

        case HEADLE_FRAME_DATA:
        {
            if (recv_len < buff_len)
            {
                LOG_D("PARSE: actual: %d, need: %d.", recv_len, buff_len);
                /* should set timer, control receive frame timeout, one shot */
                timeout = 50;
                rt_timer_control(&rt_link_scb->recvtimer, RT_TIMER_CTRL_SET_TIME, &timeout);
                rt_timer_start(&rt_link_scb->recvtimer);
                return;
            }
            LOG_D("PARSE: buff_len (%d) r (0x%p)  w (0x%p)"
                  , buff_len, rt_link_scb->rx_buffer->read_point
                  , rt_link_scb->rx_buffer->write_point);
            rt_timer_stop(&rt_link_scb->recvtimer);
            rt_link_hw_buffer_point_shift(&rt_link_scb->rx_buffer->read_point, buff_len);
            rt_link_parse_frame(&receive_frame);
            data = RT_NULL;
            buff_len = RT_LINK_HEAD_LENGTH;
            analysis_status = FIND_FRAME_HEAD;
            break;
        }

        default:
__find_head:
            LOG_D("to find head (%d)", analysis_status);
            rt_link_frame_stop_receive(&receive_frame);
            buff_len = RT_LINK_HEAD_LENGTH;
            analysis_status = FIND_FRAME_HEAD;
            break;
        }

        recv_len = rt_link_hw_recv_len(rt_link_scb->rx_buffer);
    }
}

static void rt_link_send_ready(void)
{
    struct rt_link_frame *frame = RT_NULL;
    rt_uint8_t seq = rt_link_scb->tx_seq;
    if (rt_slist_next(&rt_link_scb->tx_data_slist))
    {
        frame = rt_container_of(rt_slist_next(&rt_link_scb->tx_data_slist), struct rt_link_frame, slist);
    }

    if (rt_link_scb->state != RT_LINK_CONNECT)
    {
        rt_link_scb->state = RT_LINK_DISCONN;
        rt_link_command_frame_send(RT_LINK_SERVICE_RTLINK, seq,
                                   RT_LINK_HANDSHAKE_FRAME, rt_link_scb->rx_record.rx_seq);

        rt_int32_t timeout = 50;
        rt_timer_control(&rt_link_scb->sendtimer, RT_TIMER_CTRL_SET_TIME, &timeout);
        rt_timer_start(&rt_link_scb->sendtimer);
    }
    else
    {
        /* Avoid sending the first data frame multiple times */
        if ((frame != RT_NULL) && (frame->issent == RT_LINK_FRAME_NOSEND))
        {
            if (RT_EOK != rt_link_frame_send(&rt_link_scb->tx_data_slist))
            {
                rt_link_scb->state = RT_LINK_DISCONN;
                rt_link_service_send_finish(RT_LINK_EIO);
            }
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
    LOG_D("send count(%d)", (rt_uint32_t)rt_link_scb->sendtimer.parameter);
    if ((rt_uint32_t)rt_link_scb->sendtimer.parameter >= 5)
    {
        rt_timer_stop(&rt_link_scb->sendtimer);
        LOG_W("Send timeout, please check the link status!");
        rt_link_scb->sendtimer.parameter = 0x00;
        rt_link_service_send_finish(RT_LINK_ETIMEOUT);
    }
    else
    {
        if (rt_slist_next(&rt_link_scb->tx_data_slist))
        {
            struct rt_link_frame *frame = rt_container_of(rt_slist_next(&rt_link_scb->tx_data_slist), struct rt_link_frame, slist);
            frame->issent = RT_LINK_FRAME_NOSEND;
            rt_link_command_frame_send(RT_LINK_SERVICE_RTLINK,
                                       frame->head.sequence,
                                       RT_LINK_HANDSHAKE_FRAME,
                                       rt_link_scb->rx_record.rx_seq);
        }
    }
}

static void rt_link_long_recv_timeout(void)
{
    if ((rt_uint32_t)rt_link_scb->longframetimer.parameter >= 5)
    {
        LOG_W("long package receive timeout");
        rt_link_scb->longframetimer.parameter = 0x00;
        _stop_recv_long();
        rt_timer_stop(&rt_link_scb->longframetimer);
    }
    else
    {
        rt_uint8_t total = rt_link_scb->rx_record.total;
        for (; total > 0; total--)
        {
            if (((rt_link_scb->rx_record.long_count >> (total - 1)) & 0x01) == 0x00)
            {
                /* resend command */
                rt_link_command_frame_send(RT_LINK_SERVICE_RTLINK,
                                           (rt_link_scb->rx_record.rx_seq + total),
                                           RT_LINK_RESEND_FRAME, RT_NULL);
            }
        }
    }
}

void rt_link_thread(void *parameter)
{
    rt_uint32_t recved = 0;
    while (1)
    {
        rt_event_recv(&rt_link_scb->event,
                      RT_LINK_READ_CHECK_EVENT |
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
    rt_uint32_t count = (rt_uint32_t)rt_link_scb->sendtimer.parameter + 1;
    rt_link_scb->sendtimer.parameter = (void *)count;
    rt_event_send(&rt_link_scb->event, RT_LINK_SEND_TIMEOUT_EVENT);
}

static void rt_link_recvtimer_callback(void *parameter)
{
    rt_event_send(&rt_link_scb->event, RT_LINK_RECV_TIMEOUT_FRAME_EVENT);
}

static void rt_link_receive_long_frame_callback(void *parameter)
{
    rt_uint32_t count = (rt_uint32_t)rt_link_scb->longframetimer.parameter + 1;
    rt_link_scb->longframetimer.parameter = (void *)count;
    rt_event_send(&rt_link_scb->event, RT_LINK_RECV_TIMEOUT_LONG_EVENT);
}

/**
 * rtlink send data interface
 * @param service   Registered service channel, struct rt_link_service
 * @param data      send data
 * @param size      send data size
 * @return The actual size of the data sent
 * */
rt_size_t rt_link_send(struct rt_link_service *service, const void *data, rt_size_t size)
{
    RT_ASSERT(service != RT_NULL);

    rt_uint32_t recved = 0;
    rt_uint8_t total = 0; /* The total number of frames to send */
    rt_uint8_t index = 0; /* The index of the split packet */
    rt_size_t offset = 0; /* The offset of the send data */
    rt_size_t send_len = 0;

    struct rt_link_frame *send_frame = RT_NULL;
    rt_link_frame_attr_e attribute = RT_LINK_SHORT_DATA_FRAME;

    if ((size == 0) || (data == RT_NULL))
    {
        service->err = RT_LINK_ERR;
        goto __exit;
    }

    service->err = RT_LINK_EOK;
    if (size % RT_LINK_MAX_DATA_LENGTH == 0)
    {
        total = (rt_uint8_t)(size / RT_LINK_MAX_DATA_LENGTH);
    }
    else
    {
        total = (rt_uint8_t)(size / RT_LINK_MAX_DATA_LENGTH + 1);
    }

    if (total > RT_LINK_FRAMES_MAX)
    {
        service->err = RT_LINK_ENOMEM;
        goto __exit;
    }
    else if (total > 1)
    {
        attribute =  RT_LINK_LONG_DATA_FRAME;
    }

    do
    {
        send_frame = rt_malloc(sizeof(struct rt_link_frame));
        if (send_frame == RT_NULL)
        {
            service->err = RT_LINK_ENOMEM;
            goto __exit;
        }
        rt_link_frame_init(send_frame, service->flag);
        send_frame->head.sequence = ++rt_link_scb->tx_seq;
        send_frame->head.service = service->service;
        send_frame->real_data = (rt_uint8_t *)data + offset;
        send_frame->index = index;
        send_frame->total = total;

        if (attribute == RT_LINK_LONG_DATA_FRAME)
        {
            send_frame->attribute = RT_LINK_LONG_DATA_FRAME;
            if (offset + RT_LINK_MAX_DATA_LENGTH > size)
            {
                send_frame->data_len = (rt_uint16_t)(size - offset);
            }
            else
            {
                send_frame->data_len = RT_LINK_MAX_DATA_LENGTH;
                offset += RT_LINK_MAX_DATA_LENGTH;
            }

            rt_link_frame_extend_config(send_frame, RT_LINK_LONG_DATA_FRAME, (rt_uint16_t)size);
        }
        else
        {
            send_frame->attribute = RT_LINK_SHORT_DATA_FRAME;
            send_frame->data_len = (rt_uint16_t)size;
        }

        /* append the frame on the tail of list */
        LOG_D("append send slist, seq(%d), len(%d)", send_frame->head.sequence, send_frame->data_len);
        rt_slist_append(&rt_link_scb->tx_data_slist, &send_frame->slist);

        index++;
        send_len += send_frame->data_len;
    }while(total > index);

    /* Notify the core thread to send packet */
    rt_event_send(&rt_link_scb->event, RT_LINK_SEND_READY_EVENT);

    if (service->timeout_tx != RT_WAITING_NO)
    {
        /* Wait for the packet to send the result */
        rt_err_t ret = rt_event_recv(&rt_link_scb->sendevent, (0x01 << service->service),
                                     RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                                     service->timeout_tx, &recved);
        if (ret == -RT_ETIMEOUT)
        {
            service->err = RT_LINK_ETIMEOUT;
            send_len = 0;
        }
    }

__exit:
    return send_len;
}

void rtlink_status(void)
{
    rt_kprintf("rtlink(v%s) status:\n", RT_LINK_VER);
    if (rt_link_scb != RT_NULL)
    {
        rt_kprintf("\tlink status=%d\n", rt_link_scb->state);

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
                rt_kprintf("\tsend data list: serv %u\t", ((struct rt_link_frame_head *)data)->service);
                rt_kprintf(" seq %u\t", ((struct rt_link_frame_head *)data)->sequence);
                rt_kprintf(" len %u\n", ((struct rt_link_frame_head *)data)->length);
            }
        }
        else
        {
            rt_kprintf("\tsend data list: NULL\n");
        }

        rt_uint8_t serv = RT_LINK_SERVICE_MAX - 1;
        while (serv--)
        {
            rt_kprintf("\tservices [%d](0x%p)\n", serv, rt_link_scb->service[serv]);
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
    rt_event_init(&rt_link_scb->event, "rtlink", RT_IPC_FLAG_FIFO);
    rt_event_control(&rt_link_scb->event, RT_IPC_CMD_RESET, RT_NULL);

    rt_event_init(&rt_link_scb->sendevent, "send_rtlink", RT_IPC_FLAG_FIFO);
    rt_event_control(&rt_link_scb->sendevent, RT_IPC_CMD_RESET, RT_NULL);

    rt_timer_init(&rt_link_scb->sendtimer, "tx_time", rt_link_sendtimer_callback,
                  RT_NULL, 0, RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_PERIODIC);
    rt_timer_init(&rt_link_scb->recvtimer, "rx_time", rt_link_recvtimer_callback,
                  RT_NULL, 0, RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_ONE_SHOT);
    rt_timer_init(&rt_link_scb->longframetimer, "rxl_time", rt_link_receive_long_frame_callback,
                  RT_NULL, 0, RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_PERIODIC);

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

    rt_link_scb->state = RT_LINK_INIT;
__exit:
    if (result != RT_EOK)
    {
        LOG_E("rtlink init failed.");
        rt_link_deinit();
    }
    else
    {
        LOG_I("rtlink init success(VER:%s).", RT_LINK_VER);
    }
    return result;
}
#ifdef RT_LINK_AUTO_INIT
    INIT_ENV_EXPORT(rt_link_init);
#endif
MSH_CMD_EXPORT(rt_link_init, rt link init);

/**
 * rtlink service attach
 * @param service   Registered service channel, struct rt_link_service
 * @return Function Execution Result
 * */
rt_err_t rt_link_service_attach(struct rt_link_service *serv)
{
    RT_ASSERT(serv != RT_NULL);
    if (serv->service >= RT_LINK_SERVICE_MAX)
    {
        LOG_W("Invalid parameter.");
        return -RT_EINVAL;
    }
    rt_uint8_t seq = rt_link_scb->tx_seq;
    rt_link_hw_init();
    rt_link_scb->service[serv->service] = serv;
    serv->state = RT_LINK_INIT;
    LOG_I("rt link attach service[%02d].", serv->service);

    if (rt_slist_next(&rt_link_scb->tx_data_slist))
    {
        struct rt_link_frame *frame = rt_container_of(rt_slist_next(&rt_link_scb->tx_data_slist), struct rt_link_frame, slist);
        seq = frame->head.sequence;
    }
    rt_link_command_frame_send(serv->service, seq, RT_LINK_HANDSHAKE_FRAME, rt_link_scb->rx_record.rx_seq);
    return RT_EOK;
}

/**
 * rtlink service detach
 * @param service   Registered service channel, struct rt_link_service
 * @return rt_err_t Function Execution Result
 * */
rt_err_t rt_link_service_detach(struct rt_link_service *serv)
{
    RT_ASSERT(serv != RT_NULL);
    if (serv->service >= RT_LINK_SERVICE_MAX)
    {
        LOG_W("Invalid parameter.");
        return -RT_EINVAL;
    }
    rt_link_command_frame_send(serv->service,
                               rt_link_scb->tx_seq,
                               RT_LINK_DETACH_FRAME,
                               rt_link_scb->rx_record.rx_seq);

    serv->state = RT_LINK_DISCONN;
    rt_link_scb->service[serv->service] = RT_NULL;
    LOG_I("rt link detach service[%02d].", serv->service);
    return RT_EOK;
}
