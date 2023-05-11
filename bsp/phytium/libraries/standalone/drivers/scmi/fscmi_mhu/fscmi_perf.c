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
 * FilePath: fscmi_perf.c
 * Date: 2023-01-18 15:38:15
 * LastEditTime: 2023-01-18 15:38:17
 * Description:  This file is for performance domain control
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/01/31 init
 */

#include "fscmi_perf.h"
#include <string.h>
#include "fscmi.h"
#include "fscmi_base.h"
#include "fio.h"
#include "fdebug.h"
#include "ftypes.h"
#include "fswap.h"
#include "fkernel.h"
#include "fassert.h"

#define FSCMI_PERF_DEBUG_TAG "FSCMI_PERF"
#define FSCMI_PERF_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSCMI_PERF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_PERF_WARN(format, ...)   FT_DEBUG_PRINT_W(FSCMI_PERF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_PERF_INFO(format, ...)    FT_DEBUG_PRINT_I(FSCMI_PERF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSCMI_PERF_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSCMI_PERF_DEBUG_TAG, format, ##__VA_ARGS__)

static FError FScmiPerfGetVersion(FScmi *instance_p,u32  *rev_info)
{
    FError ret;
    struct FScmiTransferInfo *info;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_PERF);
    if (info == NULL)
    {
        FSCMI_PERF_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, PERF_VERSION_GET, SCMI_PROTOCOL_PERF, 0, sizeof(*rev_info),info->tx.buf);

    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_PERF);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    /* Fill in the obtained parameters */
    *rev_info = FtIn32((uintptr)info->rx.buf);

    return FT_SUCCESS;
}

static FError FScmiPerfAttributesGet(FScmi *instance_p,struct FScmiPerfInfo *pinfo)
{
    FError ret;
    struct FScmiTransferInfo *info;
    struct FScmiMsgRespPerfAttributes *attr;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_PERF);
    if (info == NULL)
    {
        FSCMI_PERF_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return FSCMI_ERROR_NULL_POINTER;
    }
    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, PERF_ATTRIBUTES_GET, SCMI_PROTOCOL_PERF, 0, sizeof(*attr),info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    attr = (struct FScmiMsgRespPerfAttributes *)info->rx.buf;

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_PERF);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    u16 flags = attr->flags;
    pinfo->num_domains = attr->num_domains;
    pinfo->power_scale_mw = POWER_SCALE_IN_MILLIWATT(flags);
    pinfo->stats_addr = (u32)attr->stats_addr_low | ((u64)(attr->stats_addr_high) << 32);
    pinfo->stats_size = attr->stats_size;

    return FT_SUCCESS;
}

static FError FScmiPerfDomainAttributesGet(FScmi *instance_p, u32 domain, struct FPerfDomInfo *dom_info)
{
    FError ret;
    struct FScmiTransferInfo *info;
    struct FScmiMsgRespPerfDomainAttributes *attr;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_PERF);
    if (info == NULL)
    {
        FSCMI_PERF_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, PERF_DOMAIN_ATTRIBUTES, SCMI_PROTOCOL_PERF, sizeof(domain), sizeof(*attr),info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    *(u32 *)info->tx.buf = domain;
    attr = (struct FScmiMsgRespPerfDomainAttributes *)info->rx.buf;

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_PERF);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    u32 flags = attr->flags;
    
    dom_info->set_limits = SUPPORTS_SET_LIMITS(flags);
    dom_info->set_perf = SUPPORTS_SET_PERF_LVL(flags);
    dom_info->perf_limit_notify = SUPPORTS_PERF_LIMIT_NOTIFY(flags);
    dom_info->perf_level_notify = SUPPORTS_PERF_LEVEL_NOTIFY(flags);
    dom_info->sustained_freq_khz = attr->sustained_freq_khz;
    dom_info->sustained_perf_level = attr->sustained_perf_level;
    if (!dom_info->sustained_freq_khz ||
        !dom_info->sustained_perf_level)
        /* CPUFreq converts to kHz, hence default 1000 */
        dom_info->mult_factor =	1000;
    else
        dom_info->mult_factor =
                (dom_info->sustained_freq_khz * 1000) /
                dom_info->sustained_perf_level;
    strlcpy(dom_info->name, attr->name, FSCMI_MAX_STR_SIZE);
    
    return FT_SUCCESS;
}

static int opp_cmp_func(const void *opp1, const void *opp2)
{
	const struct FScmiOpp *t1 = opp1, *t2 = opp2;

	return t1->perf_val - t2->perf_val;
}

static FError FScmiPerfDescribeLevelsGet(FScmi *instance_p, u32 domain, struct FPerfDomInfo *perf_dom)
{
    FError ret;
    u32 cnt;
    struct FScmiTransferInfo *info;
    u32 tot_opp_cnt = 0;
	u16 num_returned, num_remaining;
	struct FScmiOpp *opp;
	struct FScmiMsgPerfDescribeLevels *dom_info;
	struct FScmiMsgRespPerfDescribeLevels *level_info;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_PERF);
    if (info == NULL)
    {
        FSCMI_PERF_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, PERF_DESCRIBE_LEVELS, SCMI_PROTOCOL_PERF, sizeof(*dom_info), 0,info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    dom_info = (struct FScmiMsgPerfDescribeLevels*)info->tx.buf;
	level_info = (struct FScmiMsgRespPerfDescribeLevels *)info->rx.buf;

    do
    {
        dom_info->domain = domain;
		/* Set the number of OPPs to be skipped/already read */
		dom_info->level_index = tot_opp_cnt;

		ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_PERF);
        if(ret != FT_SUCCESS)
        {
            FSCMI_PERF_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_PERF);
            return ret;
        }

		num_returned = level_info->num_returned;
		num_remaining = level_info->num_remaining;
		if (tot_opp_cnt + num_returned > FSCMI_MAX_OPPS) 
        {
			FSCMI_PERF_ERROR("No. of OPPs exceeded MAX_OPPS");
			break;
		}

		opp = &perf_dom->opp[tot_opp_cnt];
		for (cnt = 0; cnt < num_returned; cnt++, opp++) {
			opp->perf_val = level_info->opp[cnt].perf_val;
			opp->power = level_info->opp[cnt].power;
			opp->trans_latency_us = level_info->opp[cnt].transition_latency_us;

			FSCMI_PERF_INFO("Level %d: %d KHz Power cost%d Latency %dus\n", cnt, opp->perf_val, opp->power, opp->trans_latency_us);
		}

		tot_opp_cnt += num_returned;
		/*
		 * check for both returned and remaining to avoid infinite
		 * loop due to buggy firmware
		 */
    } while (num_returned && num_remaining);

    perf_dom->opp_count = tot_opp_cnt;
    //sort(perf_dom->opp, tot_opp_cnt, sizeof(*opp), opp_cmp_func, NULL);

    return FT_SUCCESS;
}

static FError FScmiPerfLimitsSet(FScmi *instance_p, u32 domain, u32 max_perf, u32 min_perf)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(domain < instance_p->perf.num_domains);

    FError ret;
    struct FScmiTransferInfo *info;
    struct FScmiPerfSetLimits *limits;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_PERF);
    if (info == NULL)
    {
        FSCMI_PERF_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, PERF_LIMITS_SET, SCMI_PROTOCOL_PERF, sizeof(*limits), 0,info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    limits = (struct FScmiPerfSetLimits *)info->tx.buf;
    limits->domain = domain;
    limits->max_level = max_perf;
    limits->min_level = min_perf;

    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_PERF);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    FSCMI_PERF_INFO("FScmiPerfLimitsSet domain:%d max_level:%d KHz, min_level:%d KHz.",limits->domain,limits->max_level,limits->min_level);
    //FSCMI_PERF_INFO("FScmiPerfLimitsSet status:%d.",(int)instance_p->info->hdr.status);
    return FT_SUCCESS;
}

static FError FScmiPerfLimitsGet(FScmi *instance_p, u32 domain, u32 *max_perf, u32 *min_perf)
{
    FASSERT(instance_p != NULL);
    FASSERT(max_perf != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(domain < instance_p->perf.num_domains);

    FError ret;
    s32 status;
    struct FScmiTransferInfo *info;
    struct FScmiPerfGetLimits *limits;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_PERF);
    if (info == NULL)
    {
        FSCMI_PERF_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, PERF_LIMITS_GET, SCMI_PROTOCOL_PERF, sizeof(u32), 0,info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    *(u32 *)info->tx.buf = domain;
    
    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_PERF);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }
    limits = (struct FScmiPerfGetLimits *)info->rx.buf;
    //status = limits->status;
    *max_perf = limits->max_level;
    *min_perf = limits->min_level;
    FSCMI_PERF_INFO("FScmiPerfLimitsGet domain:%d, max_level:%d KHz, min_level:%d KHz.",domain,*max_perf,*min_perf);
    return FT_SUCCESS;
}

static FError FScmiPerfLevelSet(FScmi *instance_p, u32 domain, u32 level, boolean poll)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(domain < instance_p->perf.num_domains);

    FError ret;
    struct FScmiTransferInfo *info;
    struct FScmiPerfSetLevel *lvl;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_PERF);
    if (info == NULL)
    {
        FSCMI_PERF_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, PERF_LEVEL_SET, SCMI_PROTOCOL_PERF, sizeof(*lvl), 0,info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    info->poll_completion = poll;
    lvl = (struct FScmiPerfSetLevel *)info->tx.buf;
    lvl->domain = domain;
    lvl->level = level;
    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_PERF);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }
    FSCMI_PERF_INFO("FScmiPerfLevelSet domain:%d level:%d KHz.",lvl->domain,lvl->level);
    return FT_SUCCESS;
}

static FError FScmiPerfLevelGet(FScmi *instance_p, u32 domain, u32 *level, boolean poll)
{
    FASSERT(instance_p != NULL);
    FASSERT(level != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(domain < instance_p->perf.num_domains);

    FError ret;
    struct FScmiTransferInfo *info;

    info = FScmiGetInfo(instance_p, SCMI_PROTOCOL_PERF);
    if (info == NULL)
    {
        FSCMI_PERF_ERROR("Info data structure not found ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return FSCMI_ERROR_NULL_POINTER;
    }

    /* Prepare hdr packaging */
    ret = FScmiMessageInit(instance_p, PERF_LEVEL_GET, SCMI_PROTOCOL_PERF, sizeof(u32), sizeof(u32),info->tx.buf);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Prepare hdr packaging is error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    info->poll_completion = poll;
    *(u32 *)info->tx.buf = domain;
    
    ret = FScmiDoTransport(instance_p, info, SCMI_PROTOCOL_PERF);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Transport package error,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }

    *level = *(u32 *)info->rx.buf;
    FSCMI_PERF_INFO("FScmiPerfLevelGet domain:%d level:%d KHz.",domain,*level);
    return FT_SUCCESS;
}

/**
 * @name: FScmiDvfsFreqSet
 * @msg: Dynamic frequency scaling set
 * @return {FError}             返回值
 * @param {FScmi} *instance_p   scmi协议实例
 * @param {u32} domain          性能域id
 * @param {u64} freq            频率值Hz,依据初始化获得的level对应的值写入，不支持任意调频
 * @param {boolean} poll        写入模式
 */
FError FScmiDvfsFreqSet(FScmi *instance_p, u32 domain, u64 freq_Hz, boolean poll)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(domain < instance_p->perf.num_domains);

    FError ret;
    struct FScmiPerfInfo *pi = &instance_p->perf;
	struct FPerfDomInfo *dom = pi->dom_info + domain;

    ret = FScmiPerfLevelSet(instance_p, domain, freq_Hz / dom->mult_factor, poll);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("FScmiPerfLevelSet error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }
    return FT_SUCCESS;
}

/**
 * @name: FScmiDvfsFreqGet
 * @msg: Dynamic frequency scaling get
 * @return {FError}             返回值
 * @param {FScmi} *instance_p   scmi协议实例
 * @param {u32} domain          性能域id
 * @param {u64} *freq           当前性能域的频率值
 * @param {boolean} poll        写入模式
 */
FError FScmiDvfsFreqGet(FScmi *instance_p, u32 domain, u64 *freq, boolean poll)
{
    FASSERT(instance_p != NULL);
    FASSERT(freq != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(domain < instance_p->perf.num_domains);

    FError ret;
    u32 level;
	struct FScmiPerfInfo *pi = &instance_p->perf;
	struct FPerfDomInfo *dom = pi->dom_info + domain;

    ret = FScmiPerfLevelGet(instance_p, domain, &level, poll);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("FScmiPerfLevelGet error ,protocol id is %d",SCMI_PROTOCOL_PERF);
        return ret;
    }
    *freq = level * dom->mult_factor;
    return FT_SUCCESS;
}

u64 FScmiPerfGetOppFreq(FScmi *instance_p,u32 domain,u32 opp_num)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(domain < instance_p->perf.num_domains);

    struct FPerfDomInfo *dom = &instance_p->perf.dom_info[domain];
    
    if (opp_num > dom->opp_count)
    {
        FSCMI_PERF_ERROR("Can't find opp_num,please check.");
        return FSCMI_ERROR_REQUEST;
    }

    return dom->opp[opp_num].perf_val * dom->mult_factor;
}

/**
 * @name: FScmiPerfInit
 * @msg: Performance domain initialization
 * @return {FError} 返回值
 * @param {FScmi} *instance_p scmi协议实例
 */
FError FScmiPerfInit(FScmi *instance_p)
{
    FError ret;
    struct FScmiPerfInfo *pinfo;
    pinfo = &instance_p->perf;

    ret = FScmiPerfGetVersion(instance_p,&instance_p->perf.version);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Can't get version,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }
    instance_p->perf.major_ver = (instance_p->perf.version >> 16);
    instance_p->perf.minor_ver = (instance_p->perf.version & 0xffff);
	FSCMI_PERF_INFO("Perf Version %d.%d\n",instance_p->perf.major_ver, instance_p->perf.minor_ver);

	ret = FScmiPerfAttributesGet(instance_p, pinfo);
    if(ret != FT_SUCCESS)
    {
        FSCMI_PERF_ERROR("Can't get version,please check mem_address or chan_id.Error code:0x%x.",ret);
        return FSCMI_ERROR_REQUEST;
    }

    FSCMI_PERF_INFO("SCMI Perf num_domains:%d,power_scale_mw:%d,stats_addr:0x%x,stats_size:0x%x.\n", instance_p->perf.num_domains,
                                                                                      instance_p->perf.power_scale_mw,
                                                                                      instance_p->perf.stats_addr,
                                                                                      instance_p->perf.stats_size);
    for (u32 i = 0; i < pinfo->num_domains; i++)
    {
        struct FPerfDomInfo *dom = pinfo->dom_info + i;
        
        ret = FScmiPerfDomainAttributesGet(instance_p, i, dom);
        if (ret != FT_SUCCESS)
        {
            FSCMI_PERF_ERROR("Can't get version,please check mem_address or chan_id.Error code:0x%x.",ret);
            return FSCMI_ERROR_REQUEST;
        }
        
        ret = FScmiPerfDescribeLevelsGet(instance_p, i, dom);
        if (ret != FT_SUCCESS)
        {
            FSCMI_PERF_ERROR("Can't get version,please check mem_address or chan_id.Error code:0x%x.",ret);
            return FSCMI_ERROR_REQUEST;
        }
        FSCMI_PERF_INFO("SCMI Perf opp_count:%d,sustained_freq_khz:%d KHz,sustained_perf_level:%d KHz,mult_factor:%d Hz,name:%s.\n", dom->opp_count,
                                                                                                                                dom->sustained_freq_khz,
                                                                                                                                dom->sustained_perf_level,
                                                                                                                                dom->mult_factor,
                                                                                                                                dom->name);
    }
    
    return FT_SUCCESS;
}
