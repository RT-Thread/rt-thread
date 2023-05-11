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
 * FilePath: fscmi_sensors.h
 * Date: 2023-01-12 20:53:01
 * LastEditTime: 2023-01-12 20:53:01
 * Description:  This file is for cpu sensor message struct
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/01/13 init
 */

#ifndef FSCMI_SENSORS_PROTOCOL_H
#define FSCMI_SENSORS_PROTOCOL_H

#include "ftypes.h"
#include "ferror_code.h"
#include "fparameters.h"
#include "fscmi.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Sensor Type Enumerations */
enum FScmiSensorType
{
	NONE=0x0,
	UNSPECIFIED,
	DEGRESS_C,
	DEGRESS_F,
	DEGRESS_K,
};

enum FScmiSensorProtocolCmd {
    SENSOR_VERSION_GET = 0x0,
    SENSOR_ATTRIBUTES_GET = 0x1,
	SENSOR_DESCRIPTION_GET = 0x3,
	SENSOR_CONFIG_SET = 0x4,
	SENSOR_TRIP_POINT_SET = 0x5,
	SENSOR_READING_GET = 0x6,
};

struct FScmiMsgRespSensorAttributes {
	u16 num_sensors;
	u8 max_requests;
	u8 reserved;
	u32 reg_addr_low;
	u32 reg_addr_high;
	u32 reg_size;
};

struct FScmiMsgRespSensorDescription {
	u16 num_returned;
	u16 num_remaining;
	struct {
		u32 id;
		u32 attributes_low;
#define SUPPORTS_ASYNC_READ(x)	((x) & BIT(31))
#define NUM_TRIP_POINTS(x)	((x) & 0xff)
		u32 attributes_high;
#define SENSOR_TYPE(x)		((x) & 0xff)
#define SENSOR_SCALE(x)		(((x) >> 11) & 0x1f)
#define SENSOR_UPDATE_SCALE(x)	(((x) >> 22) & 0x1f)
#define SENSOR_UPDATE_BASE(x)	(((x) >> 27) & 0x1f)
		u8 name[FSCMI_MAX_STR_SIZE];
	} desc[0];
};

struct FScmiMsgSetSensorConfig {
	u32 id;
	u32 event_control;
};

struct FScmiMsgSetSensorTripPoint {
	u32 id;
	u32 event_control;
#define SENSOR_TP_EVENT_MASK	(0x3)
#define SENSOR_TP_DISABLED	0x0
#define SENSOR_TP_POSITIVE	0x1
#define SENSOR_TP_NEGATIVE	0x2
#define SENSOR_TP_BOTH		0x3
#define SENSOR_TP_ID(x)		(((x) & 0xff) << 4)
	u32 value_low;
	u32 value_high;
};

struct FcmiMsgSensorReadingGet {
	u32 id;
	u32 flags;
#define SENSOR_READ_ASYNC	BIT(0)
};

FError FScmiSensorInit(FScmi *instance_p);

#ifdef __cplusplus
}
#endif


#endif
