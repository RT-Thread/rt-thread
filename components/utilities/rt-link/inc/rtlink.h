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

#define RT_LINK_VER     "0.2.0"

#define RT_LINK_AUTO_INIT

#define RT_LINK_FLAG_ACK            0x01U
#define RT_LINK_FLAG_CRC            0x02U

#define RT_LINK_FRAME_HEAD          0x15U
#define RT_LINK_FRAME_HEAD_MASK     0x1FU
/* The maximum number of split frames for a long package */
#define RT_LINK_FRAMES_MAX          0x03U
/* The length in the rt_link_frame_head structure occupies 11 bits,
so the value range after 4-byte alignment is 0-2044.*/
#define RT_LINK_MAX_FRAME_LENGTH    1024U

#define RT_LINK_ACK_MAX             0x07U
#define RT_LINK_CRC_LENGTH          4U
#define RT_LINK_HEAD_LENGTH         4U
#define RT_LINK_EXTEND_LENGTH       4U

#define RT_LINK_MAX_DATA_LENGTH         (RT_LINK_MAX_FRAME_LENGTH - \
                                        RT_LINK_HEAD_LENGTH - \
                                        RT_LINK_EXTEND_LENGTH - \
                                        RT_LINK_CRC_LENGTH)
#define RT_LINK_RECEIVE_BUFFER_LENGTH   (RT_LINK_MAX_FRAME_LENGTH * \
                                        RT_LINK_FRAMES_MAX + \
                                        RT_LINK_HEAD_LENGTH + \
                                        RT_LINK_EXTEND_LENGTH)

typedef enum
{
    RT_LINK_SERVICE_RTLINK   = 0,
    RT_LINK_SERVICE_SOCKET   = 1,
    RT_LINK_SERVICE_WIFI     = 2,
    RT_LINK_SERVICE_MNGT     = 3,
    RT_LINK_SERVICE_MSHTOOLS = 4,

    /* Expandable to a maximum of 31 */
    RT_LINK_SERVICE_MAX
} rt_link_service_e;

typedef enum
{
    RT_LINK_RESEND_FRAME     = 0,
    RT_LINK_CONFIRM_FRAME    = 1,

    RT_LINK_HANDSHAKE_FRAME  = 2,
    RT_LINK_DETACH_FRAME     = 3,   /* service is not online */
    RT_LINK_SESSION_END      = 4,   /* The retring failed to end the session */

    RT_LINK_LONG_DATA_FRAME  = 5,
    RT_LINK_SHORT_DATA_FRAME = 6,

    RT_LINK_RESERVE_FRAME    = 7
} rt_link_frame_attr_e;

typedef enum
{
    /* receive event */
    RT_LINK_READ_CHECK_EVENT          = 1 << 0,
    RT_LINK_RECV_TIMEOUT_FRAME_EVENT  = 1 << 1,
    RT_LINK_RECV_TIMEOUT_LONG_EVENT   = 1 << 2,

    /* send event */
    RT_LINK_SEND_READY_EVENT    = 1 << 4,
    RT_LINK_SEND_OK_EVENT       = 1 << 5,
    RT_LINK_SEND_FAILED_EVENT   = 1 << 6,
    RT_LINK_SEND_TIMEOUT_EVENT  = 1 << 7
} rt_link_notice_e;

typedef enum
{
    RT_LINK_INIT    = 0,
    RT_LINK_DISCONN = 1,
    RT_LINK_CONNECT = 2,
} rt_link_linkstate_e;

typedef enum
{
    RT_LINK_EOK         = 0,
    RT_LINK_ERR         = 1,
    RT_LINK_ETIMEOUT    = 2,
    RT_LINK_EFULL       = 3,
    RT_LINK_EEMPTY      = 4,
    RT_LINK_ENOMEM      = 5,
    RT_LINK_EIO         = 6,
    RT_LINK_ESESSION    = 7,
    RT_LINK_ESERVICE    = 8,

    RT_LINK_EMAX
} rt_link_err_e;

struct rt_link_receive_buffer
{
    /* rt-link receive data buffer */
    rt_uint8_t data[RT_LINK_RECEIVE_BUFFER_LENGTH];
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
    rt_uint16_t service: 5;
    rt_uint16_t length : 11; /* range 0~2047 */
};

/* record frame information that opposite */
struct rt_link_record
{
    rt_uint8_t rx_seq;      /* record the opposite sequence */
    rt_uint8_t total;       /* the number of long frame number */
    rt_uint8_t long_count;  /* long packet recv counter */
    rt_uint8_t *dataspace;  /* the space of long frame */
};

struct rt_link_extend
{
    rt_uint16_t attribute;  /* rt_link_frame_attr_e */
    rt_uint16_t parameter;
};

struct rt_link_frame
{
    struct rt_link_frame_head head;  /* frame head */
    struct rt_link_extend extend;    /* frame extend data */
    rt_uint8_t *real_data;           /* the origin data */
    rt_uint32_t crc;                 /* CRC result */

    rt_uint16_t data_len;   /* the length of frame length */
    rt_uint16_t attribute;  /* rt_link_frame_attr_e */

    rt_uint8_t issent;
    rt_uint8_t index;       /* the index frame for long frame */
    rt_uint8_t total;       /* the total frame for long frame */

    rt_slist_t slist;       /* the frame will hang on the send list on session */
};

struct rt_link_service
{
    rt_int32_t timeout_tx;
    void (*send_cb)(struct rt_link_service *service, void *buffer);
    void (*recv_cb)(struct rt_link_service *service, void *data, rt_size_t size);
    void *user_data;

    rt_uint8_t flag;            /* Whether to use the CRC and ACK */
    rt_link_service_e service;
    rt_link_linkstate_e state;  /* channel link state */
    rt_link_err_e err;
};

struct rt_link_session
{
    struct rt_event event;
    struct rt_link_service *service[RT_LINK_SERVICE_MAX];

    rt_uint8_t tx_seq;  /* Sequence number of the send data frame */
    rt_slist_t tx_data_slist;
    rt_uint8_t sendbuffer[RT_LINK_MAX_FRAME_LENGTH];
    struct rt_event sendevent;
    struct rt_timer sendtimer;

    struct rt_link_record rx_record;  /* the memory of receive status */
    struct rt_timer recvtimer;        /* receive a frame timer for rt link */
    struct rt_timer longframetimer;   /* receive long frame timer for rt link */

    struct rt_link_receive_buffer *rx_buffer;
    rt_uint32_t (*calculate_crc)(rt_uint8_t using_buffer_ring, rt_uint8_t *data, rt_size_t size);
    rt_link_linkstate_e state;  /* Link status */
};

#define SERV_ERR_GET(service)   (service->err)

/* rtlink init and deinit, default is automatic initialization*/
int rt_link_init(void);
rt_err_t rt_link_deinit(void);

rt_size_t rt_link_send(struct rt_link_service *service, const void *data, rt_size_t size);

/* rtlink service attach and detach */
rt_err_t rt_link_service_attach(struct rt_link_service *service);
rt_err_t rt_link_service_detach(struct rt_link_service *service);

/* Private operator function */
struct rt_link_session *rt_link_get_scb(void);

#endif /* __RT_LINK_H__ */
