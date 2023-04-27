/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
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
 * FilePath: fscmi_perf.h
 * Date: 2022-12-29 16:40:54
 * LastEditTime: 2022-12-29 16:40:55
 * Description:  This file is for performance message struct
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/01/31 init
 */
#ifndef FSCMI_PERF_H
#define FSCMI_PERF_H

#include "ftypes.h"
#include "ferror_code.h"
#include "fparameters.h"
#include "fscmi.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum FScmiPerformanceProtocolCmd {
	PERF_VERSION_GET = 0x0,
	PERF_ATTRIBUTES_GET = 0x1,
	PERF_DOMAIN_ATTRIBUTES = 0x3,
	PERF_DESCRIBE_LEVELS = 0x4,
	PERF_LIMITS_SET = 0x5,
	PERF_LIMITS_GET = 0x6,
	PERF_LEVEL_SET = 0x7,
	PERF_LEVEL_GET = 0x8,
	PERF_NOTIFY_LIMITS = 0x9,
	PERF_NOTIFY_LEVEL = 0xa,
};

struct FScmiMsgRespPerfAttributes {
	u16 num_domains;
	u16 flags;
#define POWER_SCALE_IN_MILLIWATT(x)	((x) & BIT(0))
	u32 stats_addr_low;
	u32 stats_addr_high;
	u32 stats_size;
};

struct FScmiMsgRespPerfDomainAttributes {
	u32 flags;
#define SUPPORTS_SET_LIMITS(x)		((x) & BIT(31))
#define SUPPORTS_SET_PERF_LVL(x)	((x) & BIT(30))
#define SUPPORTS_PERF_LIMIT_NOTIFY(x)	((x) & BIT(29))
#define SUPPORTS_PERF_LEVEL_NOTIFY(x)	((x) & BIT(28))
	u32 rate_limit_us;
	u32 sustained_freq_khz;
	u32 sustained_perf_level;
	u8 name[FSCMI_MAX_STR_SIZE];
};

struct FScmiMsgPerfDescribeLevels {
	u32 domain;
	u32 level_index;
};

struct FScmiPerfSetLimits {
	u32 domain;
	u32 max_level;
	u32 min_level;
};

struct FScmiPerfGetLimits {
	u32 max_level;
	u32 min_level;
};

struct FScmiPerfSetLevel {
	u32 domain;
	u32 level;
};

struct FScmiPerfNotifyLevelOrLimits {
	u32 domain;
	u32 notify_enable;
};

struct FScmiMsgRespPerfDescribeLevels {
	u16 num_returned;
	u16 num_remaining;
	struct {
		u32 perf_val;/* Performance level value */
		u32 power;/* Power cost */
		u16 transition_latency_us;/* Worst-case transition latency in microseconds to move from any supported performance to the level indicated by this entry in the array */
		u16 reserved;
	} opp[0];
};

FError FScmiPerfInit(FScmi *instance_p);

#ifdef __cplusplus
}
#endif

#endif
