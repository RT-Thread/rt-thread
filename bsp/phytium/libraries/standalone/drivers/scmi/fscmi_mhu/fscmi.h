/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: fscmi.h
 * scmi.h
 * Date: 2022-12-30 18:32:33
 * LastEditTime: 2022-12-30 18:32:33
 * Description:  This file is for scmi protocol struct and application interface
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0 liushengming 2023/01/31 init
 */


#ifndef FSCMI_H
#define FSCMI_H

#include "ftypes.h"
#include "ferror_code.h"
#include "fmhu.h"
#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* error code */

#define FSCMI_ERROR_TYPE				FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x1u)
#define FSCMI_ERROR_RANGE				FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x2u)
#define FSCMI_ERROR_NOT_FOUND			FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x3u)
#define FSCMI_ERROR_NULL_POINTER		FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x4u)
#define FSCMI_ERROR_WAIT_MBOX_TIMEOUT	FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x5u)
#define FSCMI_ERROR_WAIT_MEM_TIMEOUT	FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x6u)
#define FSCMI_ERROR_FETCH_RESPONSE		FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x7u)
#define FSCMI_ERROR_REQUEST				FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x8u)
#define FSCMI_ERROR_VERSION				FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0x9u)
#define FSCMI_ERROR_INIT				FT_CODE_ERR(ErrModBsp, ErrBspScmi, 0xau)

#define FSCMI_MBOX_MHU_TYPE 0
#define FSCMI_VERSION		0x20000
/*
 * SCMI specification requires all parameters, message headers, return
 * arguments or any protocol data to be expressed in little endian
 * format only.
 */
struct FScmiSharedMem {
	u32 reserved;
	u32 channel_status;
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR	BIT(1)
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE	BIT(0)
	u32 reserved1[2];
	u32 flags;
#define SCMI_SHMEM_FLAG_INTR_ENABLED	BIT(0)
	u32 length;
	u32 msg_header;
	u8 msg_payload[0];
};

enum FScmiStdProtocol {
	SCMI_PROTOCOL_BASE = 0x10,
	SCMI_PROTOCOL_POWER = 0x11,
	SCMI_PROTOCOL_SYSTEM = 0x12,
	SCMI_PROTOCOL_PERF = 0x13,
	SCMI_PROTOCOL_CLOCK = 0x14,
	SCMI_PROTOCOL_SENSOR = 0x15,
};

enum FScmiProtocolIndex
{
    BASE_PROTOCOL_INDEX ,
	PERF_DOMAIN_INDEX ,
    SENSOR_MANAGEMENT_INDEX ,
    FSCMI_SUPPORT_PROTOCOL_NUM ,
};

/* base protocol */
struct FScmiRevisionInfo 
{
    u32 version;
    u16 major_ver;
    u16 minor_ver;
	u8 num_protocols;
	u8 num_agents;
	u32 impl_ver;
	char vendor_id[FSCMI_MAX_STR_SIZE];
	char sub_vendor_id[FSCMI_MAX_STR_SIZE];
};

/* Sensor protocol  */
struct FScmiSensorInfo {
	u32 id;
	u8 type;
	char name[FSCMI_MAX_STR_SIZE];
};

struct FScmiSensorsInfo {
	u32 version;
	u16 major_ver;
    u16 minor_ver;
	u32 num_sensors;
	u32 max_requests;
	u64 reg_addr;
	u32 reg_size;
	struct FScmiSensorInfo sensor_info[FSCMI_MAX_NUM_SENSOR];/* TS0 TS1 */
};

/* Performance domain protocol */

struct FScmiOpp {
	u32 perf_val;
	u32 power;
	u32 trans_latency_us;
};

struct FPerfDomInfo {
	boolean set_limits;
	boolean set_perf;
	boolean perf_limit_notify;
	boolean perf_level_notify;
	u32 opp_count;
	u32 sustained_freq_khz;
	u32 sustained_perf_level;
	u32 mult_factor;
	char name[FSCMI_MAX_STR_SIZE];
	struct FScmiOpp opp[FSCMI_MAX_OPPS];
};

struct FScmiPerfInfo {
	u32 version;
    u16 major_ver;
    u16 minor_ver;
	u32 num_domains;
	boolean power_scale_mw;
	u64 stats_addr;
	u32 stats_size;
	struct FPerfDomInfo dom_info[FSCMI_MAX_PERF_DOMAINS];
};

/* Scmi massage package */
struct FScmiMsgHdr 
{
	u8 id;              /* message id   */
	u8 protocol_id;     /* protocol id */
	u16 seq;            /* message token */ 
	u32 status;         /* protocal status */
};

struct FScmiMsg
{
	u8 buf[FSCMI_MSG_SIZE];          /* buffer in normal memory */
	u32 len;        /* buffer length */
};

struct FScmiTransferInfo 
{
    struct FScmiMsgHdr hdr ; /* Message(Tx/Rx) header */
    struct FScmiMsg tx ;
    struct FScmiMsg rx ;
    boolean poll_completion;
};

/* Scmi protocol struct */
struct FScmiConfig
{
	uintptr share_mem;	/* Chan transport protocol shared memory */
	u32 mbox_type;      /* select mbox driver */
};

typedef struct
{
    u32 is_ready; /* Device is ininitialized and ready*/
    struct FScmiConfig config;
    struct FScmiRevisionInfo revision;
	struct FScmiSensorsInfo sensors;
	struct FScmiPerfInfo perf;
	struct FScmiTransferInfo info[FSCMI_SUPPORT_PROTOCOL_NUM];
	u8 protocols_imp[FSCMI_MAX_PROTOCOLS_IMP];/* List of protocols implemented, currently maximum of FSCMI_MAX_PROTOCOLS_IMP elements allocated by the base protocol */
	FScmiMhu scmi_mhu;
} FScmi;

/* Base protocol function */
FError FScmiCfgInitialize(FScmi *instance_p, const struct FScmiConfig *config);
FError FScmiMessageInit(FScmi *instance_p, u8 msg_id, u8 pro_id, u32 tx_size, u32 rx_size, u8 *tx_buffer);
FError FScmiProtocolTxPrepare(FScmi *instance_p, u8 pro_id);
FError FScmiProtocolPollDone(FScmi *instance_p, u8 pro_id);
FError FScmiFetchResponse(FScmi *instance_p, u8 pro_id);
struct FScmiTransferInfo *FScmiGetInfo(FScmi *instance_p, u8 pro_id);
FError FScmiDoTransport(FScmi *instance_p, struct FScmiTransferInfo *info, u32 protocol_index);
/* Sensor protocol function */
FError FScmiSensorGetTemp(FScmi *instance_p, u32 sensor_id,s64 *temp);
/* Performance domain function */
FError FScmiDvfsFreqSet(FScmi *instance_p, u32 domain, u64 freq, boolean poll);
FError FScmiDvfsFreqGet(FScmi *instance_p, u32 domain, u64 *freq, boolean poll);
u64 FScmiPerfGetOppFreq(FScmi *instance_p, u32 domain, u32 opp_num);

#ifdef __cplusplus
}
#endif


#endif

