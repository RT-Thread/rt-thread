/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-02     xiangxistu   the first version
 * 2021-03-19     Sherman      Streamline the struct rt_link_session
 */

#ifndef __RT_LINK_H__
#define __RT_LINK_H__

#include <rtdef.h>

#define RT_LINK_AUTO_INIT

#define RT_LINK_FRAME_HEAD                 0x15
#define RT_LINK_FRAME_HEAD_MASK            0x1F
#define RT_LINK_MAX_DATA_LENGTH            2044 /*can exact divide by 4 bytes*/
#define RT_LINK_FRAMES_MAX   0x03   /* The maximum number of split frames for a long package*/

#define RT_LINK_ACK_MAX   0x07
#define RT_LINK_CRC_LENGTH          4
#define RT_LINK_HEAD_LENGTH         4
#define RT_LINK_MAX_EXTEND_LENGTH       4
#define RT_LINK_MAX_FRAME_LENGTH        (RT_LINK_HEAD_LENGTH + RT_LINK_MAX_EXTEND_LENGTH + RT_LINK_MAX_DATA_LENGTH + RT_LINK_CRC_LENGTH)
#define RT_LINK_RECEIVE_BUFFER_LENGTH       (RT_LINK_MAX_FRAME_LENGTH * RT_LINK_FRAMES_MAX + RT_LINK_HEAD_LENGTH + RT_LINK_MAX_EXTEND_LENGTH)

typedef enum
{
    RT_LINK_SERVICE_RTLINK = 0,
    RT_LINK_SERVICE_LINK_SOCKET = 1,
    RT_LINK_SERVICE_LINK_WIFI = 2,
    RT_LINK_SERVICE_LINK_MNGT = 3,
    RT_LINK_SERVICE_LINK_MSHTOOLS = 4,
    RT_LINK_SERVICE_MAX
} rt_link_service_t;

enum
{
    FRAME_EXTEND = 1 << 0,
    FRAME_CRC    = 1 << 1,
    FRAME_ACK    = 1 << 2
};

typedef enum
{
    RT_LINK_RESERVE_FRAME = 0,

    RT_LINK_RESEND_FRAME,
    RT_LINK_CONFIRM_FRAME,
    RT_LINK_SHORT_DATA_FRAME,
    RT_LINK_LONG_DATA_FRAME,
    RT_LINK_SESSION_END,  /* The retring failed to end the session */

    RT_LINK_HANDSHAKE_FRAME
} rt_link_frame_attribute_t;

typedef enum
{
    /* receive event */
    RT_LINK_READ_CHECK_EVENT            = 1 << 0,
    RT_LINK_RECV_TIMEOUT_FRAME_EVENT    = 1 << 1,
    RT_LINK_RECV_TIMEOUT_LONG_EVENT     = 1 << 2,

    /* send event */
    RT_LINK_SEND_READY_EVENT    = 1 << 4,
    RT_LINK_SEND_OK_EVENT       = 1 << 5,
    RT_LINK_SEND_FAILED_EVENT   = 1 << 6,
    RT_LINK_SEND_TIMEOUT_EVENT  = 1 << 7
} rt_link_notice_t;

typedef enum
{
    RT_LINK_ESTABLISHING = 0,
    RT_LINK_NO_RESPONSE,
    RT_LINK_CONNECT_DONE,
} rt_link_linkstatus_t;

typedef enum
{
    RECVTIMER_NONE = 0,
    RECVTIMER_FRAME,
    RECVTIMER_LONGFRAME
} rt_link_recvtimer_status_t;

struct rt_link_receive_buffer
{
    rt_uint8_t data[RT_LINK_RECEIVE_BUFFER_LENGTH]; /* rt-link receive data buffer */
    rt_uint8_t *read_point;
    rt_uint8_t *write_point;
    rt_uint8_t *end_point;
};

struct rt_link_frame_head
{
    rt_uint8_t magicid : 5;
    rt_uint8_t extend  : 1;
    rt_uint8_t crc     : 1;
    rt_uint8_t ack     : 1;
    rt_uint8_t sequence;
    rt_uint16_t channel: 5;
    rt_uint16_t length : 11;
};

/* record frame information that opposite */
struct rt_link_record
{
    rt_uint8_t rx_seq; /* record the opposite sequence */
    rt_uint8_t total;       /* the number of long frame number */
    rt_uint8_t long_count;  /* long packet recv counter */
    rt_uint8_t *dataspace;  /* the space of long frame */
};

struct rt_link_extend
{
    rt_uint16_t attribute;           /* rt_link_frame_attribute_t */
    rt_uint16_t parameter;
};

struct rt_link_frame
{
    struct rt_link_frame_head head;         /* frame head */
    struct rt_link_extend extend;           /* frame extend data */
    rt_uint8_t *real_data;                  /* the origin data */
    rt_uint32_t crc;                        /* CRC result */

    rt_uint16_t data_len;         /* the length of frame length */
    rt_uint16_t attribute;        /* this will show frame attribute , rt_link_frame_attribute_t */

    rt_uint8_t index;              /* the index frame for long frame */
    rt_uint8_t total;               /* the total frame for long frame */

    rt_slist_t slist;            /* the frame will hang on the send list on session */
};

struct rt_link_service
{
    rt_err_t (*upload_callback)(void *data, rt_size_t size);
};

struct rt_link_session
{
    rt_link_linkstatus_t link_status;   /* Link connection status*/
    struct rt_event event;      /* the event that core logic */
    struct rt_link_service channel[RT_LINK_SERVICE_MAX]; /* thansfer to app layer */

    rt_slist_t tx_data_slist;
    rt_uint8_t tx_seq;     /* sequence for frame */
    struct rt_mutex tx_lock;    /* protect send data interface, only one thread can hold it */
    struct rt_timer sendtimer;  /* send function timer for rt link */

    struct rt_link_record rx_record;    /* the memory of receive status */
    struct rt_timer recvtimer;          /* receive a frame timer for rt link */
    struct rt_timer longframetimer;     /* receive long frame timer for rt link */

    struct rt_link_receive_buffer *rx_buffer; /* the buffer will store data */
    rt_uint32_t (*calculate_crc)(rt_uint8_t using_buffer_ring, rt_uint8_t *data, rt_size_t size); /* this function will calculate crc */
};

/* rtlink init and deinit */
int rt_link_init(void);
rt_err_t rt_link_deinit(void);
/* rtlink send data interface */
rt_size_t rt_link_send(rt_link_service_t service, void *data, rt_size_t size);
/* rtlink service attach and detach */
rt_err_t rt_link_service_attach(rt_link_service_t service, rt_err_t (*function)(void *data, rt_size_t size));
rt_err_t rt_link_service_detach(rt_link_service_t service);

/* Private operator function */
struct rt_link_session *rt_link_get_scb(void);

#endif /* __RT_LINK_H__ */
