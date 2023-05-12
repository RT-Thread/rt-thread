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
 * FilePath: fscmi.c
 * Date: 2022-12-30 18:32:28
 * LastEditTime: 2022-12-30 18:32:28
 * Description:  This file is for scmi protocol support
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0 liushengming 2023/01/30 init
 */
#include <string.h>
#include "fscmi.h"
#include "fmhu_hw.h"
#include "fio.h"
#include "fkernel.h"
#include "fdebug.h"
#include "fsleep.h"
#include "fassert.h"
#include "fscmi_base.h"
#include "fscmi_sensors.h"
#include "fscmi_perf.h"

#define FSCMI_DEBUG_TAG "FSCMI"
#define FSCMI_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSCMI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_WARN(format, ...)   FT_DEBUG_PRINT_W(FSCMI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_INFO(format, ...)    FT_DEBUG_PRINT_I(FSCMI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSCMI_DEBUG_TAG, format, ##__VA_ARGS__)

#define MSG_ID_MASK		GENMASK(7, 0)
#define MSG_TYPE_MASK		GENMASK(9, 8)
#define MSG_PROTOCOL_ID_MASK	GENMASK(17, 10)
#define MSG_TOKEN_ID_MASK	GENMASK(27, 18)


FError FScmiDoTransport(FScmi *instance_p,struct FScmiTransferInfo *info, u32 protocol_index)
{
    FError ret;
    u32 tx_done = 0;
    u32 chan_status = 0;
    u32 delay_out = 0;
    FMhuConfig *mhu_config = &instance_p->scmi_mhu.mhu.config;

    /* write data to share buffer */
    ret = FScmiProtocolTxPrepare(instance_p,protocol_index);
    if(ret != FT_SUCCESS)
    {
        FSCMI_ERROR("%s,FScmiProtocolTxPrepare is error", __FUNCTION__);
        return ret;
    }

    if(instance_p->scmi_mhu.send_data)
    {
        instance_p->scmi_mhu.send_data(mhu_config->base_addr,mhu_config->mhu_chan_id);
    }
    chan_status = FMhuGetChanStatus(mhu_config->base_addr);
    /* 等待发送完成 */
    while (tx_done == 0)
    {   
        tx_done = instance_p->scmi_mhu.last_tx_done(mhu_config->base_addr);
        if (tx_done == 1)
        {
            break;
        }
        else
        {
            fsleep_millisec(10);
            delay_out++;
            if (delay_out == 10)
            {
                FSCMI_ERROR("Send error,addr:0x%x,last_tx_done:0x%x",mhu_config->base_addr,tx_done);
                return FSCMI_ERROR_WAIT_MBOX_TIMEOUT;
            }
        }
    }

    /* 等待数据接收完成 */
    /* poll way */

    if(info->poll_completion)
    {
        while(FScmiProtocolPollDone(instance_p,protocol_index) != TRUE);
        /* get data */
        ret = FScmiFetchResponse(instance_p,protocol_index);
        if(ret != FT_SUCCESS)
        {
            return FSCMI_ERROR_FETCH_RESPONSE;
        }
    }
    else
    {
        /* interrupt way */
    }

    return FT_SUCCESS;
}
/**
 * @name: 
 * @msg: 
 * @return {*}
 * @param {u8} pro_id
 * @param {u32} *protocol_index
 */
static FError FScmiProtocolMapping(const u8 pro_id,u32 *protocol_index)
{
    switch (pro_id)
    {
        case SCMI_PROTOCOL_BASE:
        {
            *protocol_index = BASE_PROTOCOL_INDEX;
            return FT_SUCCESS;
        }
        case SCMI_PROTOCOL_PERF:
        {
            *protocol_index = PERF_DOMAIN_INDEX;
            return FT_SUCCESS;
        }
        case SCMI_PROTOCOL_SENSOR:
        {
            *protocol_index = SENSOR_MANAGEMENT_INDEX;
            return FT_SUCCESS;
        }
        default:
        return FSCMI_ERROR_NOT_FOUND;
    }
    return FT_SUCCESS;
}

struct FScmiTransferInfo *FScmiGetInfo(FScmi *instance_p, u8 pro_id)
{
    u32 index_id = 0;
    FError ret;
    ret = FScmiProtocolMapping(pro_id, &index_id);
    if (ret != FT_SUCCESS)
    {
        FSCMI_ERROR("%s,Protocol mapping error", __FUNCTION__);
        return NULL;
    }

    return  &instance_p->info[index_id]; 
}

FError FScmiFetchResponse(FScmi *instance_p, u8 pro_id)
{
    struct FScmiSharedMem *mem =(struct FScmiSharedMem *) instance_p->config.share_mem;
    struct FScmiTransferInfo *trans_info;
    u32 index_id = 0;
    FError ret;
    ret = FScmiProtocolMapping(pro_id, &index_id);
    if (ret != FT_SUCCESS)
    {
        FSCMI_ERROR("%s,Protocol mapping error", __FUNCTION__);
        return ret;
    }
    trans_info = &instance_p->info[index_id];
    trans_info->hdr.status = FtIn32((uintptr)mem->msg_payload);
    /* Skip the length of header and statues in payload area i.e 8 bytes*/
    trans_info->rx.len = min(trans_info->rx.len, FtIn32((uintptr)(&mem->length)) - 8);

    /* Take a copy to the rx buffer.. */

    if(trans_info->rx.len)
    {
        for (u32 i = 0; i < trans_info->rx.len; i++)
        {
            trans_info->rx.buf[i] = mem->msg_payload[i+4];
        }
    }

    return FT_SUCCESS;
}

FError FScmiProtocolPollDone(FScmi *instance_p,u8 pro_id)
{
    struct FScmiSharedMem  *mem =(struct FScmiSharedMem *) instance_p->config.share_mem;
    u32 index_id = 0;
    FError ret;
    ret = FScmiProtocolMapping(pro_id, &index_id);
    if(ret != FT_SUCCESS)
    {
        FSCMI_ERROR("%s,Protocol mapping error",__FUNCTION__);
        return FALSE;
    }

    return FtIn32((uintptr)(&mem->channel_status)) &
        (SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR |
        SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE);
}


static u32 FScmiPackHeader(struct FScmiMsgHdr *hdr_p)
{

    return FIELD_PREP(MSG_ID_MASK, hdr_p->id) |
        FIELD_PREP(MSG_TOKEN_ID_MASK, hdr_p->seq) |
        FIELD_PREP(MSG_PROTOCOL_ID_MASK, hdr_p->protocol_id);
}

FError FScmiProtocolTxPrepare(FScmi *instance_p,u8 pro_id)
{
    struct FScmiSharedMem  *mem =(struct FScmiSharedMem *) instance_p->config.share_mem;
    struct FScmiTransferInfo *trans_info;
    u32 index_id = 0;
    u32 time_out;
    FError ret;
    static int is_init = 0;
    ret = FScmiProtocolMapping(pro_id, &index_id);
    if(ret != FT_SUCCESS)
    {
        FSCMI_ERROR("Protocol mapping error");
        return ret;
    }
    trans_info = &instance_p->info[index_id];
    if(!is_init)
    {
        FtOut32((uintptr)&mem->channel_status,SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE);
        is_init = 1;
    }

    while (0 == (FtIn32((uintptr)&mem->channel_status) &SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE))
    {
        time_out++;
        fsleep_millisec(10);
        if (time_out == 10)
        {
            FSCMI_ERROR("Memory of scmi status error,please check mhu channel set or memory addrs...");
            return FSCMI_ERROR_WAIT_MEM_TIMEOUT;
        }
    }

    FtOut32((uintptr)&mem->channel_status,0);
    FtOut32((uintptr)&mem->flags, 0);
    FtOut32((uintptr)&mem->length, sizeof(mem->msg_header) + trans_info->tx.len);
    FtOut32((uintptr)&mem->msg_header,FScmiPackHeader(&trans_info->hdr));

    if(trans_info->tx.len)
    {
        for (u32 i = 0; i < trans_info->tx.len; i++)
        {
            mem->msg_payload[i] = trans_info->tx.buf[i];
        }
    }

    return FT_SUCCESS;
}

FError FScmiMessageInit(FScmi *instance_p,u8 msg_id,u8 pro_id,u32 tx_size,u32 rx_size,u8 *tx_buffer)
{
    u32 index_id = 0;
    FError ret;
    struct FScmiTransferInfo *trans_info;

    ret = FScmiProtocolMapping(pro_id, &index_id);
    if(ret != FT_SUCCESS)
    {
        FSCMI_ERROR("Protocol mapping error");
        return ret;
    }
    trans_info = &instance_p->info[index_id];

    /* 检查 tx_size / rx_size 的长度*/
    if(tx_size > FSCMI_MSG_SIZE || rx_size > FSCMI_MSG_SIZE)
    {
        return FSCMI_ERROR_RANGE;
    }

    if(tx_size > 0 && tx_buffer == NULL)
    {
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* init hdr */
    trans_info->hdr.seq = pro_id + msg_id ;
    trans_info->hdr.id = msg_id;
    trans_info->hdr.protocol_id = pro_id;

    /* init buffer */
    trans_info->tx.len = tx_size;
    if(tx_size && tx_buffer)
    {
        memcpy(trans_info->tx.buf, tx_buffer, tx_size);
    }

    trans_info->rx.len = rx_size ?  :FSCMI_MSG_SIZE;/*  */
    trans_info->poll_completion = TRUE;

    return FT_SUCCESS;
    
}


FError FScmiCfgInitialize(FScmi *instance_p, const struct FScmiConfig *config)
{
    /* first init  */
    instance_p->config = *config;
    
    FError ret;
    
    /*  Second choice is the mbox driver */
    if (instance_p->config.mbox_type == FSCMI_MBOX_MHU_TYPE)
    {
        FMhuChanProbe(&instance_p->scmi_mhu);
    }
    else
    {
        return FSCMI_ERROR_TYPE;
    }
    
    instance_p->config.share_mem = config->share_mem;

    /* The third initializes the base protocol */
    ret = FScmiBaseInit(instance_p);
    if (instance_p->revision.version != FSCMI_VERSION)
    {
        return FSCMI_ERROR_VERSION;
    }
    
    ret = FScmiSensorInit(instance_p);
    if(ret != FT_SUCCESS)
    {
        FSCMI_ERROR("FScmiSensorInit init error.Error code:0x%x.",ret);
        return FSCMI_ERROR_INIT;
    }
    
    ret = FScmiPerfInit(instance_p);
    if(ret != FT_SUCCESS)
    {
        FSCMI_ERROR("FScmiPerfInit init error.Error code:0x%x.",ret);
        return FSCMI_ERROR_INIT;
    }
    /* Finally confirm the completion status */
    instance_p->is_ready = FT_COMPONENT_IS_READY;

    return FT_SUCCESS;
}
