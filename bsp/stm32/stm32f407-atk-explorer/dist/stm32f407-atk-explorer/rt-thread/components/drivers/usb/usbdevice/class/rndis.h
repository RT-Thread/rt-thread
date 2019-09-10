/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2012-12-24     heyuanjie87       first version
 */

#ifndef  __RNDIS_H__
#define  __RNDIS_H__

#include <rtthread.h>

#define USB_ETH_MTU	                    1500+14
#define RNDIS_MESSAGE_BUFFER_SIZE       128

#define RESPONSE_AVAILABLE            0x00000001

/* Remote NDIS version numbers */
#define RNDIS_MAJOR_VERSION	1
#define RNDIS_MINOR_VERSION 0

/* common status values */
#define RNDIS_STATUS_SUCCESS 			0X00000000
#define RNDIS_STATUS_FAILURE			0XC0000001
#define RNDIS_STATUS_INVALID_DATA		0XC0010015
#define RNDIS_STATUS_NOT_SUPPORTED 		0XC00000BB
#define RNDIS_STATUS_MEDIA_CONNECT		0X4001000B
#define RNDIS_STATUS_MEDIA_DISCONNECT	0X4001000C

/* Remote NDIS message types */
#define REMOTE_NDIS_PACKET_MSG			0x00000001
#define REMOTE_NDIS_INITIALIZE_MSG		0X00000002
#define REMOTE_NDIS_HALT_MSG			0X00000003
#define REMOTE_NDIS_QUERY_MSG			0X00000004
#define REMOTE_NDIS_SET_MSG				0X00000005
#define REMOTE_NDIS_RESET_MSG			0X00000006
#define REMOTE_NDIS_INDICATE_STATUS_MSG 0X00000007
#define REMOTE_NDIS_KEEPALIVE_MSG		0X00000008
#define REMOTE_NDIS_INITIALIZE_CMPLT	0X80000002
#define REMOTE_NDIS_QUERY_CMPLT			0X80000004
#define REMOTE_NDIS_SET_CMPLT			0X80000005
#define REMOTE_NDIS_RESET_CMPLT			0X80000006
#define REMOTE_NDIS_KEEPALIVE_CMPLT		0X80000008

/* device flags */
#define RNDIS_DF_CONNECTIONLESS			0x00000001
#define RNDIS_DF_CONNECTION_ORIENTED	0x00000002
/* mediums */
#define RNDIS_MEDIUM_802_3				0x00000000

struct ucls_rndis
{
    uep_t notify;
    rt_uint32_t filter;
    rt_bool_t header;
    rt_uint8_t rndis_state;
    rt_uint8_t media_state;
    rt_uint8_t ethaddr[6];
};

/* Remote NDIS generic message type */
struct rndis_gen_msg
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
};
typedef struct rndis_gen_msg* rndis_gen_msg_t;

struct rndis_packet_msg
{
	rt_uint32_t	MessageType;
	rt_uint32_t	MessageLength;
	rt_uint32_t	DataOffset;
	rt_uint32_t	DataLength;
	rt_uint32_t	OOBDataOffset;
	rt_uint32_t	OOBDataLength;
	rt_uint32_t	NumOOBDataElements;
	rt_uint32_t	PerPacketInfoOffset;
	rt_uint32_t	PerPacketInfoLength;
	rt_uint32_t	VcHandle;
	rt_uint32_t	Reserved;
};
typedef struct rndis_packet_msg* rndis_packet_msg_t;

/* Remote NDIS Initialize Message */
struct rndis_init_msg
{
    rt_uint32_t MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	RequestId;
    rt_uint32_t	MajorVersion;
    rt_uint32_t	MinorVersion;
    rt_uint32_t	MaxTransferSize;
};
typedef struct rndis_init_msg* rndis_init_msg_t;

/* Response */
struct rndis_init_cmplt
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	RequestId;
    rt_uint32_t	Status;
    rt_uint32_t	MajorVersion;
    rt_uint32_t	MinorVersion;
    rt_uint32_t	DeviceFlags;
    rt_uint32_t	Medium;
    rt_uint32_t MaxPacketsPerTransfer;
    rt_uint32_t	MaxTransferSize;
    rt_uint32_t PacketAlignmentFactor;
    rt_uint32_t	AfListOffset;
    rt_uint32_t	AfListSize;
};
typedef struct rndis_init_cmplt* rndis_init_cmplt_t;

/* Remote NDIS Halt Message */
struct rndis_halt_msg
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	RequestId;
};

/* Remote NDIS Query Message */
struct rndis_query_msg
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	RequestId;
    rt_uint32_t	Oid;
    rt_uint32_t	InformationBufferLength;
    rt_uint32_t	InformationBufferOffset;
    rt_uint32_t	DeviceVcHandle;
};
typedef struct rndis_query_msg* rndis_query_msg_t;

/* Response */
struct rndis_query_cmplt
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	RequestId;
    rt_uint32_t	Status;
    rt_uint32_t	InformationBufferLength;
    rt_uint32_t	InformationBufferOffset;
};
typedef struct rndis_query_cmplt* rndis_query_cmplt_t;

/* Remote NDIS Set Message */
struct rndis_set_msg
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	RequestId;
    rt_uint32_t	Oid;
    rt_uint32_t	InformationBufferLength;
    rt_uint32_t	InformationBufferOffset;
    rt_uint32_t	DeviceVcHandle;
};
typedef struct rndis_set_msg* rndis_set_msg_t;

/* Response */
struct rndis_set_cmplt
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	RequestId;
    rt_uint32_t	Status;
};
typedef struct rndis_set_cmplt* rndis_set_cmplt_t;

/* Remote NDIS Soft Reset Message */
struct rndis_reset_msg
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	Reserved;
};

/* Remote NDIS Soft Reset Response */
struct rndis_reset_cmplt
{
    rt_uint32_t	MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	Status;
    rt_uint32_t	AddressingReset;
};

/* Remote NDIS Indicate Status Message */
struct rndis_indicate_status_msg
{
    rt_uint32_t MessageType;
    rt_uint32_t	MessageLength;
    rt_uint32_t	Status;
    rt_uint32_t	StatusBufferLength;
    rt_uint32_t	StatusBufferOffset;
};
typedef struct rndis_indicate_status_msg* rndis_indicate_status_msg_t;

struct rndis_keepalive_msg
{
	rt_uint32_t	MessageType;
	rt_uint32_t	MessageLength;
	rt_uint32_t	RequestID;
};
typedef struct rndis_keepalive_msg* rndis_keepalive_msg_t;

/* Response: */
struct rndis_keepalive_cmplt
{
	rt_uint32_t	MessageType;
	rt_uint32_t	MessageLength;
	rt_uint32_t	RequestId;
	rt_uint32_t	Status;
};
typedef struct rndis_keepalive_cmplt* rndis_keepalive_cmplt_t;







#endif
