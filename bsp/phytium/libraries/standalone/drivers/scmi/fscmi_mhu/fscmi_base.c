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
 * FilePath: fscmi_base.c
 * Date: 2022-12-31 21:38:31
 * LastEditTime: 2022-12-31 21:47:30
 * Description:  This file is for base protocol
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/01/12 init
 */

#include <string.h>
#include "fscmi.h"
#include "fscmi_base.h"
#include "fio.h"
#include "fdebug.h"
#include "fsleep.h"
#include "ftypes.h"
#include "fswap.h"
#include "fkernel.h"

#define FSCMI_BASE_DEBUG_TAG "FSCMI_BASE"
#define FSCMI_BASE_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSCMI_BASE_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_BASE_WARN(format, ...)   FT_DEBUG_PRINT_W(FSCMI_BASE_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_BASE_INFO(format, ...)    FT_DEBUG_PRINT_I(FSCMI_BASE_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_BASE_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSCMI_BASE_DEBUG_TAG, format, ##__VA_ARGS__)

struct FScmiBaseAttributes {
	u8 num_protocols;
	u8 num_agents;
	u16 reserved;
};

static FError FScmiBaseGetVersion(FScmi *instance_p,u32  *rev_info)
{
    FError ret;
    struct FScmiTransferInfo *info;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_BASE);
    if (info == NULL)
    {
        FSCMI_BASE_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, FSCMI_BASE_PROTOCOL_VERSION, SCMI_PROTOCOL_BASE, 0, sizeof(*rev_info),info->tx.buf);

    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_BASE);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Transport package error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    /* Fill in the obtained parameters */
    *rev_info = FtIn32((uintptr)info->rx.buf);

    return FT_SUCCESS;
}

static FError FScmiBaseGetVendor(FScmi *instance_p,boolean sub_vendor)
{
    FError ret;
    struct FScmiTransferInfo *info;
    u8 cmd;
    char *vendor_id;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_BASE);
    if (info == NULL)
    {
        FSCMI_BASE_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return FSCMI_ERROR_NULL_POINTER;
    }

    if (sub_vendor) {
		cmd = FSCMI_BASE_PROTOCOL_DISCOVER_SUB_VENDOR;
		vendor_id = instance_p->revision.sub_vendor_id;
	} else {
		cmd = FSCMI_BASE_PROTOCOL_DISCOVER_VENDOR;
		vendor_id = instance_p->revision.vendor_id;
	}
    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, cmd, SCMI_PROTOCOL_BASE, 0, FSCMI_MAX_STR_SIZE,info->tx.buf);

    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_BASE);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Transport package error error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    /* Fill in the obtained parameters */
    memcpy(vendor_id,info->rx.buf,FSCMI_MAX_STR_SIZE);

    return FT_SUCCESS;
}

static FError FScmiBaseGetAttributes(FScmi *instance_p, u8 *num_protocols, u8 *num_agents)
{
    FError ret;
    struct FScmiTransferInfo *info;
    struct FScmiBaseAttributes *attr_info;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_BASE);
    if (info == NULL)
    {
        FSCMI_BASE_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, FSCMI_BASE_PROTOCOL_ATTRIBUTES, SCMI_PROTOCOL_BASE, 0, sizeof(*attr_info),info->tx.buf);

    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_BASE);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Transport package error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    /* Fill in the obtained parameters */
    attr_info = (struct FScmiBaseAttributes *)info->rx.buf;
    instance_p->revision.num_protocols = attr_info->num_protocols;
	instance_p->revision.num_agents = attr_info->num_agents;

    return FT_SUCCESS;
}

static FError FScmiBaseGetImplementVersion(FScmi *instance_p, u32 *impl_ver)
{
    FError ret;
    struct FScmiTransferInfo *info;
    struct FScmiBaseAttributes *attr_info;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_BASE);
    if (info == NULL)
    {
        FSCMI_BASE_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, FSCMI_BASE_PROTOCOL_DISCOVER_IMPLEMENTATION_VERSION, SCMI_PROTOCOL_BASE, 0, sizeof(*impl_ver),info->tx.buf);

    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_BASE);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Transport package error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    /* Fill in the obtained parameters */
    *impl_ver = FtIn32((uintptr)info->rx.buf);

    return FT_SUCCESS;
}

static FError FScmiBaseGetImplementList(FScmi *instance_p , u8 *protocols_imp)
{
    FError ret;
    struct FScmiTransferInfo *info;
    struct FScmiBaseAttributes *attr_info;

    u32 *num_skip, *num_ret;
    u8 *list;
    u32 tot_num_ret = 0, loop_num_ret;
    u32 loop;
    
    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_BASE);
    if (info == NULL)
    {
        FSCMI_BASE_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, FSCMI_BASE_PROTOCOL_DISCOVER_LIST_PROTOCOLS, SCMI_PROTOCOL_BASE, sizeof(*num_skip), 0,info->tx.buf);

    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    /* Fill in the obtained parameters */
    num_skip = (u32 *)info->tx.buf;
	num_ret = (u32 *)info->rx.buf;
    list = info->rx.buf + sizeof(num_ret);

    do {
		/* Set the number of protocols to be skipped/already read */
		*num_skip = tot_num_ret;

		ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_BASE);
        if(ret != FT_SUCCESS)
        {
            FSCMI_BASE_ERROR("Transport package error ,protocol id is %d",SCMI_PROTOCOL_BASE);
            return ret;
        }

		loop_num_ret = (*num_ret);

        if (tot_num_ret + loop_num_ret > FSCMI_MAX_PROTOCOLS_IMP)
        {
            FSCMI_BASE_ERROR("No. of Protocol > MAX_PROTOCOLS_IMP");
			break;
        }

        for (loop = 0; loop < loop_num_ret; loop++)
			protocols_imp[tot_num_ret + loop] = *(list + loop);

		tot_num_ret += loop_num_ret;
	} while (loop_num_ret);

    return FT_SUCCESS;
}

static FError FScmiBaseGetAgent(FScmi *instance_p,int id,char *name)
{
    FError ret;
    struct FScmiTransferInfo *info;
    struct FScmiBaseAttributes *attr_info;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_BASE);
    if (info == NULL)
    {
        FSCMI_BASE_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, FSCMI_BASE_PROTOCOL_DISCOVER_AGENT, SCMI_PROTOCOL_BASE, sizeof(u32), FSCMI_MAX_STR_SIZE,info->tx.buf);

    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    *info->tx.buf = id;
    
    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_BASE);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Transport package error ,protocol id is %d",SCMI_PROTOCOL_BASE);
        return ret;
    }

    /* Fill in the obtained parameters */
    memcpy(name, info->rx.buf, FSCMI_MAX_STR_SIZE);

    return FT_SUCCESS;
}

/**
 * @name: FScmiBaseInit
 * @msg: Base protocol get SCMI support information
 * @return {FError}             返回值
 * @param {FScmi} *instance_p   scmi协议实例
 */
FError FScmiBaseInit(FScmi *instance_p)
{
    FError ret;
    char name[FSCMI_MAX_STR_SIZE];
    int id;

    /* first get PROTOCOL_VERSION FSCMI_BASE_PROTOCOL_VERSION*/
    ret = FScmiBaseGetVersion(instance_p,&instance_p->revision.version);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Can't get version,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }
    /* FSCMI_BASE_PROTOCOL_ATTRIBUTES */
    ret = FScmiBaseGetAttributes(instance_p,&instance_p->revision.num_protocols,&instance_p->revision.num_agents);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Can't get num_protocols,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }
    /* FSCMI_BASE_PROTOCOL_DISCOVER_VENDOR and FSCMI_BASE_PROTOCOL_DISCOVER_SUB_VENDOR */
    ret = FScmiBaseGetVendor(instance_p,FALSE);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Can't get major_ver,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }
    ret = FScmiBaseGetVendor(instance_p,TRUE);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Can't get major_ver,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }
    /* FSCMI_BASE_PROTOCOL_DISCOVER_IMPLEMENTATION_VERSION */
    ret = FScmiBaseGetImplementVersion(instance_p,&instance_p->revision.impl_ver);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Can't get impl_ver,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }
    /* FSCMI_BASE_PROTOCOL_DISCOVER_LIST_PROTOCOLS */
    ret = FScmiBaseGetImplementList(instance_p,instance_p->protocols_imp);
    if(ret != FT_SUCCESS)
    {
        FSCMI_BASE_ERROR("Can't get vendor_id,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }

    instance_p->revision.major_ver = (instance_p->revision.version >> 16);
    instance_p->revision.minor_ver = (instance_p->revision.version & 0xffff);

    FSCMI_BASE_INFO("SCMI Protocol v%d.%d '%s:%s' Firmware version 0x%x\n", instance_p->revision.major_ver,
                                                                            instance_p->revision.minor_ver,
                                                                            instance_p->revision.vendor_id,
                                                                            instance_p->revision.sub_vendor_id,
                                                                            instance_p->revision.impl_ver);

    FSCMI_BASE_INFO("Found %d protocol(s) %d agent(s)\n",instance_p->revision.num_protocols,instance_p->revision.num_agents);

    /* FSCMI_BASE_PROTOCOL_DISCOVER_AGENT */
    for ( id = 0; id < instance_p->revision.num_agents; id++)
    {
        ret = FScmiBaseGetAgent(instance_p,id,name);
        if(ret != FT_SUCCESS)
        {
            FSCMI_BASE_ERROR("Can't get sub_vendor_id,please check mem_address or chan_id.Error code:0x%x.",ret);
            return FSCMI_ERROR_REQUEST;
        }
        FSCMI_BASE_INFO("Agent %d:%s\n",id,name);
    }

    return FT_SUCCESS;
}
