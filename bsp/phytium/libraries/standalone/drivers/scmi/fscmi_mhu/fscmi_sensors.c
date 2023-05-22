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
 * FilePath: fscmi_sensors.c
 * Date: 2023-01-12 20:52:41
 * LastEditTime: 2023-01-12 20:52:42
 * Description:  This file is for cpu sersor information
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/01/13 init
 */

#include "fscmi_sensors.h"
#include <string.h>
#include "fscmi.h"
#include "fscmi_base.h"
#include "fio.h"
#include "fdebug.h"
#include "fsleep.h"
#include "ftypes.h"
#include "fswap.h"
#include "fkernel.h"
#include "fassert.h"

#define FSCMI_SENSOR_DEBUG_TAG "FSCMI_SENSOR"
#define FSCMI_SENSOR_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSCMI_SENSOR_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_SENSOR_WARN(format, ...)   FT_DEBUG_PRINT_W(FSCMI_SENSOR_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_SENSOR_INFO(format, ...)    FT_DEBUG_PRINT_I(FSCMI_SENSOR_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_SENSOR_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSCMI_SENSOR_DEBUG_TAG, format, ##__VA_ARGS__)

static FError FScmiSensorGetVersion(FScmi *instance_p,u32  *rev_info)
{
    FError ret;
    struct FScmiTransferInfo *info;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_SENSOR);
    if (info == NULL)
    {
        FSCMI_SENSOR_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, SENSOR_VERSION_GET, SCMI_PROTOCOL_SENSOR, 0, sizeof(*rev_info),info->tx.buf);

    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_SENSOR);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

    /* Fill in the obtained parameters */
    *rev_info = FtIn32((uintptr)info->rx.buf);

    return FT_SUCCESS;
}

static FError FScmiSensorAttributesGet(FScmi *instance_p,struct FScmiSensorsInfo *si)
{
	FError ret;
	struct FScmiTransferInfo *info;
	struct FScmiMsgRespSensorAttributes *attr;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_SENSOR);
    if (info == NULL)
    {
        FSCMI_SENSOR_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return FSCMI_ERROR_NULL_POINTER;
    }
    
	ret = FScmiMessageInit(instance_p, SENSOR_ATTRIBUTES_GET,SCMI_PROTOCOL_SENSOR, 0, sizeof(*attr), info->tx.buf);
	if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_SENSOR);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

    /* Fill in the obtained parameters */
    attr = (struct FScmiMsgRespSensorAttributes *)info->rx.buf;
    
    si->num_sensors = (int)attr->num_sensors;
    si->max_requests = (int)attr->max_requests;
    si->reg_addr = (u32)attr->reg_addr_low | ((u64)(attr->reg_addr_high)) << 32;
    si->reg_size = (u32)(attr->reg_size);

    return FT_SUCCESS;
}

static FError FScmiSensorDescriptionGet(FScmi *instance_p,struct FScmiSensorsInfo *si)
{
	int ret, cnt;
	u32 desc_index = 0;
	u16 num_returned, num_remaining;
	struct FScmiTransferInfo *info;
	struct FScmiMsgRespSensorDescription *buf;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_SENSOR);
    if (info == NULL)
    {
        FSCMI_SENSOR_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return FSCMI_ERROR_NULL_POINTER;
    }

	ret = FScmiMessageInit(instance_p, SENSOR_DESCRIPTION_GET, SCMI_PROTOCOL_SENSOR, sizeof(u32), 0, info->tx.buf);
	if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

	buf = (struct FScmiMsgRespSensorDescription *)info->rx.buf;

    FSCMI_SENSOR_INFO("DescriptionGet:num_returned:%d,num_remaining:%d.\n",buf->num_returned,buf->num_remaining);
	do {
		/* Set the number of sensors to be skipped/already read */
		*(u32 *)info->tx.buf = desc_index;

        ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_SENSOR);
        if(ret != FT_SUCCESS)
        {
            FSCMI_SENSOR_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_SENSOR);
            return ret;
        }

		num_returned = (u16)(buf->num_returned);
		num_remaining = (u16)(buf->num_remaining);

		if (desc_index + (u32)num_returned > si->num_sensors) {
			FSCMI_SENSOR_ERROR("No. of sensors can't exceed:%d+%d > %d", desc_index, num_returned, si->num_sensors);
			break;
		}

		for (cnt = 0; cnt < num_returned; cnt++) {
			u32 attrh;
			struct FScmiSensorInfo *s;

			attrh = (u32)(buf->desc[cnt].attributes_high);
			s = &si->sensor_info[desc_index + cnt];
			s->id = (u32)(buf->desc[cnt].id);
			s->type = SENSOR_TYPE(attrh);
			strlcpy(s->name, buf->desc[cnt].name, FSCMI_MAX_STR_SIZE);
            FSCMI_SENSOR_INFO("DescriptionGet:id:%d,type:%d,name:%s.\n",s->id,s->type,s->name);
        }

        desc_index += num_returned;
		/*
		 * check for both returned and remaining to avoid infinite
		 * loop due to buggy firmware
		 */
	} while (num_returned && num_remaining);
	return ret;
}

static int FScmiSensorsTripPointSet(FScmi *instance_p,u32 sensor_id, u8 trip_id, u64 trip_value)
{
    FError ret;
    u32 evt_cntl = SENSOR_TP_BOTH;
    struct FScmiTransferInfo *info;
    struct FScmiMsgSetSensorTripPoint *trip;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_SENSOR);
    if (info == NULL)
    {
        FSCMI_SENSOR_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, SENSOR_TRIP_POINT_SET, SCMI_PROTOCOL_SENSOR, sizeof(*trip), 0,info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

    trip = (struct FScmiMsgSetSensorTripPoint *)info->tx.buf;
	trip->id = sensor_id;
	trip->event_control = evt_cntl;
    trip->value_low = trip_value & 0xffffffff;
    trip->value_high = trip_value >> 32;

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_SENSOR);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }
    
    return FT_SUCCESS;
}
static FError FScmiSensorsConfigurationSet(FScmi *instance_p,u32 sensor_id)
{
    FError ret;
    u32 evt_cntl = BIT(0);
    struct FScmiTransferInfo *info;
    struct FScmiMsgSetSensorConfig *cfg;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_SENSOR);
    if (info == NULL)
    {
        FSCMI_SENSOR_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, SENSOR_CONFIG_SET, SCMI_PROTOCOL_SENSOR, sizeof(*cfg), 0,info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

    cfg = (struct FScmiMsgSetSensorConfig *)info->tx.buf;
	cfg->id = sensor_id;
	cfg->event_control = evt_cntl;

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_SENSOR);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }
    
    return FT_SUCCESS;
}

static FError FScmiSensorsReadingGet(FScmi *instance_p,u32 sensor_id, boolean async, s64 *value)
{
    FError ret;
    struct FScmiTransferInfo *info;
    struct FcmiMsgSensorReadingGet *sensor;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_SENSOR);
    if (info == NULL)
    {
        FSCMI_SENSOR_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, SENSOR_READING_GET, SCMI_PROTOCOL_SENSOR, sizeof(*sensor), sizeof(u64),info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

    sensor = (struct FcmiMsgSensorReadingGet *)info->tx.buf;
    sensor->id = sensor_id;
    sensor->flags = async ? SENSOR_READ_ASYNC:0;

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_SENSOR);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_SENSOR);
        return ret;
    }

    /* Fill in the obtained parameters */
    u32 *pval = (u32 *)info->rx.buf;
    *value = *pval;
    *value |= (s64)(*(pval +1)) << 32;
    return FT_SUCCESS;
}

/**
 * @name: FScmiSensorGetTemp
 * @msg: 
 * @return {FError}             返回值
 * @param {FScmi} *instance_p   scmi协议实例
 * @param {u32} sensor_id       传感器ID，可以在初始化后获取
 * @param {s64} *temp           获取对应ID传感器的温度
 */
FError FScmiSensorGetTemp(FScmi *instance_p, u32 sensor_id,s64 *temp)
{
    FASSERT(instance_p != NULL);
    FASSERT(temp != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    FError ret;

    if(instance_p->sensors.num_sensors > 0 && instance_p->sensors.num_sensors > sensor_id)
    {
        if (instance_p->sensors.sensor_info[sensor_id].type == DEGRESS_C)
        {
            FScmiSensorsReadingGet(instance_p, sensor_id, FALSE, temp);
            FSCMI_SENSOR_INFO("FScmiSensorsReadingGet type DEGRESS_C value: %d `C.",*temp);
        }
    }
    else
    {
        FSCMI_SENSOR_ERROR("Can't find sensor,please running function FScmiSensorInit first.");
    }
    return FT_SUCCESS;
}

/**
 * @name: FScmiSensorInit
 * @msg: Sensor initialization
 * @return {FError}             返回值
 * @param {FScmi} *instance_p   scmi协议实例
 */
FError FScmiSensorInit(FScmi *instance_p)
{
	u32 version;
    FError ret;
    struct FScmiSensorsInfo *sinfo;
    sinfo = &instance_p->sensors;

    ret = FScmiSensorGetVersion(instance_p,&instance_p->sensors.version);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Can't get version,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }
    instance_p->sensors.major_ver = (instance_p->sensors.version >> 16);
    instance_p->sensors.minor_ver = (instance_p->sensors.version & 0xffff);
	FSCMI_SENSOR_INFO("Sensor Version %d.%d\n",instance_p->sensors.major_ver, instance_p->sensors.minor_ver);

	ret = FScmiSensorAttributesGet(instance_p, sinfo);
    if(ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Can't get version,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }

    FSCMI_SENSOR_INFO("SCMI Sensors num:%d,requests:%d,reg_addr:0x%x,reg_size:0x%x.\n", instance_p->sensors.num_sensors,
                                                                                      instance_p->sensors.max_requests,
                                                                                      instance_p->sensors.reg_addr,
                                                                                      instance_p->sensors.reg_size);
    ret = FScmiSensorDescriptionGet(instance_p, sinfo);
    if (ret != FT_SUCCESS)
    {
        FSCMI_SENSOR_ERROR("Can't get version,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }
    return FT_SUCCESS;
}

