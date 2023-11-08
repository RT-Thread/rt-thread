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
 * FilePath: fgdma.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This file is for gdma user function implmentation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0   huanghe    2021/11/5    init commit
 *  1.1   zhugengyu  2022/5/16    support chan alloc. and qos setting
 */

/***************************** Include Files *********************************/
#include <string.h>

#include "fdrivers_port.h"

#include "fgdma_hw.h"
#include "fgdma.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGDMA_DEBUG_TAG "GDMA"
#define FGDMA_ERROR(format, ...) FT_DEBUG_PRINT_E(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_WARN(format, ...) FT_DEBUG_PRINT_W(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_INFO(format, ...) FT_DEBUG_PRINT_I(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_DEBUG(format, ...) FT_DEBUG_PRINT_D(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
/************************** Function Prototypes ******************************/
FError FGdmaChanAbort(FGdma *const instance_p, FGdmaChanIndex channel_id);
/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @name: FGdmaSetQos
 * @msg: 设置GDMA控制器的全局Qos配置
 * @return {void} 无
 * @param {FGdma} *instance_p, GDMA控制器实例
 */
static void FGdmaSetQos(FGdma *const instance_p)
{
    uintptr base_addr = instance_p->config.base_addr;
    FGdmaOperPriority rd_qos = instance_p->config.rd_qos;
    FGdmaOperPriority wr_qos = instance_p->config.wr_qos;
    u32 reg_val;

    /* enable or disable QoS */
    reg_val = FGDMA_READREG(base_addr, FGDMA_CTL_OFFSET);
    if (FGDMA_OPER_NONE_PRIORITY_POLL == rd_qos)
    {
        reg_val &= ~FGDMA_CTL_RD_ARB;
    }
    else
    {
        reg_val |= FGDMA_CTL_RD_ARB; /* read operation QoS mode */
    }
    if (FGDMA_OPER_NONE_PRIORITY_POLL == wr_qos)
    {
        reg_val &= ~FGDMA_CTL_WR_ARB;
    }
    else
    {
        reg_val |= FGDMA_CTL_WR_ARB; /* write operation QoS mode */
    }
    FGDMA_WRITEREG(base_addr, FGDMA_CTL_OFFSET, reg_val);

    /* set QoS value */
    reg_val = FGDMA_READREG(base_addr, FGDMA_QOS_CFG_OFFSET);
    if (FGDMA_OPER_NONE_PRIORITY_POLL == rd_qos)
    {
        reg_val &= ~FGDMA_QOS_CFG_ARGOS_MASK;
    }
    else
    {
        reg_val |= FGDMA_QOS_CFG_ARGOS_SET((u32)rd_qos); /* read operation QoS value */
    }
    if (FGDMA_OPER_NONE_PRIORITY_POLL == wr_qos)
    {
        reg_val &= ~FGDMA_QOS_CFG_AWQOS_MASK;
    }
    else
    {
        reg_val |= FGDMA_QOS_CFG_AWQOS_SET((u32)wr_qos); /*  write operation QoS value */
    }
    FGDMA_WRITEREG(base_addr, FGDMA_QOS_CFG_OFFSET, reg_val);

    return;
}

/**
 * @name: FGdmaReset
 * @msg: 重置GDMA控制器
 * @return {void} 无
 * @param {FGdma} *instance_p, GDMA控制器实例
 */
static void FGdmaReset(FGdma *const instance_p)
{
    uintptr base_addr = instance_p->config.base_addr;

    FGdmaDisable(base_addr);
    FGdmaIrqDisable(base_addr);
    FGdmaSoftReset(base_addr);
    FGDMA_INFO("Reset GDMA controller.");

    for (int chan_id = 0; chan_id < FGDMA_NUM_OF_CHAN; chan_id++) /* 通道重置 */
    {
        instance_p->chan_irq_info[chan_id].chan_id = chan_id;
        instance_p->chan_irq_info[chan_id].gdma_instance = instance_p;
        if (instance_p->chan_ready_flag & BIT(chan_id)) /* 如果通道被配置过，则进行通道重置 */
        {
            FGdmaChanAbort(instance_p, chan_id);
            FGdmaChanIrqDisable(base_addr, chan_id);
            FGdmaClearChanStatus(base_addr, chan_id, FGDMA_CHX_INT_STATE_ALL);
            FGdmaChanSoftReset(base_addr, chan_id);
            FGdmaSetChanClock(base_addr, chan_id, FALSE);
            instance_p->chan_ready_flag |~ BIT(chan_id);
        }
    }
    FGDMA_INFO("Reset all GDMA chans.");
}

/**
 * @name: FGdmaCfgInitialize
 * @msg: 初始化GDMA控制器
 * @return {FError} 返回FGDMA_SUCCESS表示初始化成功，返回其它表示失败
 * @param FGdma *const instance_p, GDMA控制器实例
 * @param FGdmaConfig const *input_config, GDMA控制器配置
 */
FError FGdmaCfgInitialize(FGdma *const instance_p, const FGdmaConfig* controller_config_p)
{
    FASSERT(instance_p);
    FASSERT(controller_config_p);

    if (instance_p->gdma_ready == FT_COMPONENT_IS_READY)
        FGdmaDeInitialize(instance_p);

    instance_p->config = *controller_config_p;

    /* 初始化操作 */
    FGdmaReset(instance_p);
    if (instance_p->config.wait_mode == FGDMA_WAIT_INTR)
    {
        FGdmaIrqEnable(instance_p->config.base_addr);
    }
    FGdmaSetQos(instance_p);

    instance_p->gdma_ready = FT_COMPONENT_IS_READY;

    return FGDMA_SUCCESS;
}

/**
 * @name: FGdmaDeInitialize
 * @msg: 去初始化GDMA控制器
 * @return {void} 无
 * @param FGdma *const instance_p, GDMA控制器实例
 */
void FGdmaDeInitialize(FGdma *const instance_p)
{
    FASSERT(instance_p);

    FGdmaReset(instance_p);
    memset(instance_p, 0, sizeof(*instance_p));
}

/**
 * @name FGdmaChanSetQos
 * @msg: 设置GDMA通道的QoS配置
 * @return {void} 无
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @param FGdmaOperPriority rd_qos GDMA通道读操作QoS优先级
 * @param FGdmaOperPriority wr_qos GDMA通道写操作QoS优先级
 */
static void FGdmaChanSetQos(FGdma *const instance_p, 
                            FGdmaChanIndex channel_id, 
                            FGdmaOperPriority rd_qos, 
                            FGdmaOperPriority wr_qos)
{
    FASSERT(instance_p);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);

    u32 reg_val = FGDMA_READREG(instance_p->config.base_addr, FGDMA_CHX_MODE_OFFSET(channel_id));
    if (FGDMA_OPER_NONE_PRIORITY_POLL == rd_qos)
    {
        reg_val &= ~FGDMA_CHX_MODE_RD_QOS_EN;
    }
    else 
    {
        reg_val &= ~FGDMA_CHX_MODE_RD_QOS_MASK;
        reg_val |= FGDMA_CHX_MODE_RD_QOS_EN |
                   FGDMA_CHX_MODE_RD_QOS_SET(rd_qos);
    }
    if (FGDMA_OPER_NONE_PRIORITY_POLL == wr_qos)
    {
        reg_val &= ~FGDMA_CHX_MODE_WR_QOS_EN;
    }
    else
    {
        reg_val &= ~FGDMA_CHX_MODE_WR_QOS_MASK;
        reg_val |= FGDMA_CHX_MODE_WR_QOS_EN |
                   FGDMA_CHX_MODE_WR_QOS_SET(wr_qos);
    }
    FGDMA_WRITEREG(instance_p->config.base_addr, FGDMA_CHX_MODE_OFFSET(channel_id), reg_val);

    return;
}

/**
 * @name FGdmaChanDirectSetBasic
 * @msg: Direct模式下GDMA通道基础配置
 * @return {FError} FGDMA_SUCCESS表示分配成功，返回其它值表示分配失败
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @param FGdmaChanConfig const *channel_config_p GDMA通道配置
 */
static FError FGdmaChanDirectSetBasic(FGdma *const instance_p, FGdmaChanIndex channel_id, FGdmaChanConfig const *channel_config_p)
{
    FASSERT(instance_p);
    FASSERT(channel_config_p);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);
    
    uintptr base_addr = instance_p->config.base_addr;

    /* set chan mode */
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CHX_MODE_OFFSET(channel_id));
    reg_val &= ~FGDMA_CHX_MODE_BDL_EN;
    reg_val &= ~FGDMA_CHX_MODE_BDL_ROLL_EN;
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_MODE_OFFSET(channel_id), reg_val);
    FGDMA_INFO("Set to Direct mode");

    /* set channel QoS */
    FGdmaChanSetQos(instance_p, channel_id, channel_config_p->rd_qos, channel_config_p->wr_qos);
    FGDMA_INFO("DMA_Cx_MODE(0x24): 0x%x", FGDMA_READREG(base_addr, FGDMA_CHX_MODE_OFFSET(channel_id)));

    /* set xfer config */
    reg_val = 0;
    reg_val |= FGDMA_CHX_XFER_CFG_AR_LEN_SET((u32)channel_config_p->rd_length) |
               FGDMA_CHX_XFER_CFG_AR_SIZE_SET((u32)channel_config_p->rd_size) |
               FGDMA_CHX_XFER_CFG_AR_BRUST_SET((u32)channel_config_p->rd_type);

    reg_val |= FGDMA_CHX_XFER_CFG_AW_LEN_SET((u32)channel_config_p->wr_length) |
               FGDMA_CHX_XFER_CFG_AW_SIZE_SET((u32)channel_config_p->wr_size) |
               FGDMA_CHX_XFER_CFG_AW_BRUST_SET((u32)channel_config_p->rd_type);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_XFER_CFG_OFFSET(channel_id), reg_val);
    FGDMA_INFO("DMA_Cx_XFER_CFG(0x48): 0x%x", FGDMA_READREG(base_addr, FGDMA_CHX_XFER_CFG_OFFSET(channel_id)));

    if (channel_config_p->wait_mode == FGDMA_WAIT_INTR)
    {
        /* enable channel interrupt */
        FGdmaChanIrqEnable(base_addr, channel_id, FGDMA_CHX_INT_CTRL_TRANS_END_ENABLE);
    }

    return 0;
}

/**
 * @name FGdmaDirectSetTrans
 * @msg: Direct模式下GDMA通道传输信息准备
 * @return {FError} FGDMA_SUCCESS表示配置成功
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @param uintptr src_addr 传输源地址
 * @param uintptr dst_addr 传输目的地址
 * @param fsize_t data_len 传输的总数据量
 */
static FError FGdmaChanDirectSetTrans(FGdma *const instance_p, FGdmaChanIndex channel_id,uintptr src_addr, uintptr dst_addr, fsize_t data_len)
{
    FASSERT(instance_p);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);

    uintptr base_addr = instance_p->config.base_addr;
    
    /* src address */
#ifdef __aarch64__
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(channel_id), UPPER_32_BITS(src_addr));
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(channel_id), LOWER_32_BITS(src_addr));
#else
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(channel_id), 0x0U);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(channel_id), (u32)(src_addr));
#endif
    FGDMA_INFO("src: 0x%x-0x%x",
               FGDMA_READREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(channel_id)),
               FGDMA_READREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(channel_id)));

    /* dest address */
#ifdef __aarch64__
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(channel_id), UPPER_32_BITS(dst_addr));
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(channel_id), LOWER_32_BITS(dst_addr));
#else
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(channel_id), 0x0U);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(channel_id), (u32)(dst_addr));
#endif
    FGDMA_INFO("DMA_Cx_UPDADDR(0x40)-DMA_Cx_LWDADDR (0x44): 0x%x-0x%x",
               FGDMA_READREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(channel_id)),
               FGDMA_READREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(channel_id)));

    /* num of BDL entry not used in direct mode */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LVI_OFFSET(channel_id), 0x0U);

    /* length of data to transfer */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_TS_OFFSET(channel_id), data_len);
    FGDMA_INFO("DMA_Cx_TS(0x34): 0x%x", FGDMA_READREG(base_addr, FGDMA_CHX_TS_OFFSET(channel_id)));

    instance_p->chan_ready_flag |= BIT(channel_id);

    return FGDMA_SUCCESS;
}

/**
 * @name FGdmaBDLSetDesc
 * @msg: 设置一个BDL描述符
 * @return {FError} FGDMA_SUCCESS 表示设置成功
 * @param FGdmaBdlDesc *const first_desc_addr_p BDL描述符列表首地址
 * @param FGdmaBdlDescConfig const *bdl_desc_config_p BDL描述符配置
 * @note 在BDL模式通道配置前应该先完成BDL描述符配置
 */
FError FGdmaBDLSetDesc(FGdmaBdlDesc *const first_desc_addr_p, FGdmaBdlDescConfig const *bdl_desc_config_p)
{
    FASSERT(first_desc_addr_p);
    FASSERT(bdl_desc_config_p);

    FGdmaBdlDesc *bdl_desc_p = &first_desc_addr_p[bdl_desc_config_p->current_desc_num];
    uintptr src_addr = bdl_desc_config_p->src_addr;
    uintptr dst_addr = bdl_desc_config_p->dst_addr;
    fsize_t trans_length = bdl_desc_config_p->trans_length;  
    FGdmaBurstSize rd_size = bdl_desc_config_p->rd_size;
    FGdmaBurstSize wr_size = bdl_desc_config_p->wr_size;

    if (src_addr == 0 || 
        dst_addr == 0 ||
        (0U != (src_addr % FGDMA_GET_BURST_BYTE(rd_size))) ||
        (0U != (dst_addr % FGDMA_GET_BURST_BYTE(wr_size)))) /* 报文传输的首地址需要与burst size所代表的单次burst传输的最大数据字节数对齐 */
    {
        FGDMA_ERROR("src addr 0x%x or dst addr 0x%x are NOT-ALIGNED with the burst size.", src_addr, dst_addr);
        return FGDMA_ERR_INVALID_ADDR;
    }

    if (trans_length == 0 ||
        0U != (trans_length % FGDMA_GET_BURST_BYTE(rd_size)) ||
        0U != (trans_length % FGDMA_GET_BURST_BYTE(wr_size))) /* 报文传输的总数据量必须是burst size所代表的单次burst传输的最大数据字节数的整数倍 */
    {
        FGDMA_ERROR("The data length %d is not N times of burst size.", trans_length);
        return FGDMA_ERR_INVALID_SIZE;
    }

#ifdef __aarch64___
    bdl_desc_p->src_addr_h = UPPER_32_BITS(src_addr);
    bdl_desc_p->src_addr_l = LOWER_32_BITS(src_addr);
    bdl_desc_p->dst_addr_h = UPPER_32_BITS(dst_addr);
    bdl_desc_p->dst_addr_l = LOWER_32_BITS(dst_addr);
#else
    bdl_desc_p->src_addr_h = 0U;
    bdl_desc_p->src_addr_l = src_addr;
    bdl_desc_p->dst_addr_h = 0U;
    bdl_desc_p->dst_addr_l = dst_addr;
#endif

    /* rd = src */
    bdl_desc_p->src_tc = FGDMA_SRC_TC_BDL_BURST_SET((u32)bdl_desc_config_p->rd_type) |
                         FGDMA_SRC_TC_BDL_SIZE_SET((u32)rd_size) |
                         FGDMA_SRC_TC_BDL_LEN_SET((u32)bdl_desc_config_p->rd_length);

    /* wr = dst */
    bdl_desc_p->dst_tc = FGDMA_DST_TC_BDL_BURST_SET((u32)bdl_desc_config_p->wr_type) |
                         FGDMA_DST_TC_BDL_SIZE_SET((u32)wr_size) |
                         FGDMA_DST_TC_BDL_LEN_SET((u32)bdl_desc_config_p->wr_length);

    bdl_desc_p->total_bytes = trans_length;

    if (bdl_desc_config_p->ioc)
    {
        bdl_desc_p->ioc = 1U;
    }
    else
    {
        bdl_desc_p->ioc = 0U;
    }

    return FGDMA_SUCCESS;
}

/**
 * @name FGdmaChanBDLSetBasic
 * @msg: BDL模式下GDMA通道基础配置
 * @return {FError} FGDMA_SUCCESS表示配置成功，返回其它值表示分配失败
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @param FGdmaChanConfig const *channel_config_p GDMA通道配置
 */
static FError FGdmaChanBDLSetBasic(FGdma *const instance_p, FGdmaChanIndex channel_id, const FGdmaChanConfig *channel_config_p)
{
    FASSERT(instance_p);
    FASSERT(channel_config_p);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);

    uintptr base_addr = instance_p->config.base_addr;

    /* set chan mode */
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CHX_MODE_OFFSET(channel_id));
    reg_val |= FGDMA_CHX_MODE_BDL_EN;
    if (channel_config_p->roll_back)
    {
        reg_val |= FGDMA_CHX_MODE_BDL_ROLL_EN; /* run BDL in roll-back mode */
    }
    else
    {
        reg_val &= ~FGDMA_CHX_MODE_BDL_ROLL_EN;
    }
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_MODE_OFFSET(channel_id), reg_val);
    FGDMA_INFO("Set to BDL mode.");

    /* Qos设置 */
    FGdmaChanSetQos(instance_p, channel_id, channel_config_p->rd_qos, channel_config_p->wr_qos);
    FGDMA_INFO("DMA_Cx_MODE(0x24): 0x%x", FGDMA_READREG(base_addr, FGDMA_CHX_MODE_OFFSET(channel_id)));

    if (channel_config_p->wait_mode == FGDMA_WAIT_INTR)
    {
        /* enable channel interrupt */
        FGdmaChanIrqEnable(base_addr, channel_id, FGDMA_CHX_INT_CTRL_TRANS_END_ENABLE | FGDMA_CHX_INT_CTRL_BDL_END_ENABLE);
    }

    return 0;
}

/**
 * @name FGdmaChanBDLSetTrans
 * @msg: BDL模式下GDMA通道传输信息准备
 * @return {FError} FGDMA_SUCCESS 表示配置成功
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @param FGdmaChanConfig const *channel_config_p GDMA通道配置
 */
static FError FGdmaChanBDLSetTrans(FGdma *const instance_p, FGdmaChanIndex channel_id, const FGdmaChanConfig *channel_config_p)
{
    FASSERT(instance_p);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);
    FASSERT(channel_config_p);
    FASSERT(channel_config_p->first_desc_addr && channel_config_p->valid_desc_num > 0);

    FGdmaBdlDesc *first_desc_addr_p = channel_config_p->first_desc_addr;

    /* check BDL desc list */
    for (fsize_t loop = 0; loop < channel_config_p->valid_desc_num; loop++)
    {
        if (first_desc_addr_p[loop].src_addr_l == 0 && first_desc_addr_p[loop].src_addr_h == 0)
        {   
            FGDMA_ERROR("BDL descriptor-%d has not been set.", loop + 1);
            return FGDMA_ERR_COMMON;
        }
    }
    FGDMA_INFO("BDL descriptor list has been completely set.");

    uintptr base_addr = instance_p->config.base_addr;

    /* src address, and dst address has been defined in BDL */
#ifdef __aarch64__
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(channel_id), UPPER_32_BITS((uintptr)first_desc_addr_p));
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(channel_id), LOWER_32_BITS((uintptr)first_desc_addr_p));
#else
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(channel_id), 0x0U);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(channel_id), (u32)((uintptr)first_desc_addr_p));
#endif

    /* dst address not used in BDL mode */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(channel_id), 0x0U);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(channel_id), 0x0U);

    /* ts not used in BDL mode */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_TS_OFFSET(channel_id), 0x0U);

    /* num of BDL entry */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LVI_OFFSET(channel_id), FGDMA_CHX_LVI_SET(channel_config_p->valid_desc_num));


    instance_p->chan_ready_flag |= BIT(channel_id);

    return FGDMA_SUCCESS;
}

/**
 * @name FGdmaChanDirectConfiguration
 * @msg: Direct模式下GDMA通道配置，这一步还不会开始传输，FGdmaStart后才会开始传输
 * @return {FError} FGDMA_SUCCESS表示配置成功
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @param FGdmaChanConfig const* channel_config_p GDMA通道配置
 */
static FError FGdmaChanDirectConfiguration(FGdma *const instance_p, FGdmaChanIndex channel_id, FGdmaChanConfig const *channel_config_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->gdma_ready);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);
    FASSERT(channel_config_p);

    FError ret = FGDMA_SUCCESS;

    /* 报文传输的首地址需要与burst size所代表的单次burst传输的最大数据字节数对齐 */
    if (channel_config_p->src_addr == 0 ||
        channel_config_p->dst_addr == 0 ||
        (channel_config_p->src_addr % FGDMA_GET_BURST_BYTE(channel_config_p->rd_size)) ||
        (channel_config_p->dst_addr % FGDMA_GET_BURST_BYTE(channel_config_p->wr_size)))
    {
        FGDMA_ERROR("src addr 0x%x or dst addr 0x%x is NOT-ALIGNED with burst size.", channel_config_p->src_addr, channel_config_p->dst_addr);
        return FGDMA_ERR_INVALID_ADDR;
    }

    /* 报文传输的总数据量必须是burst size所代表的单次burst传输的最大数据字节数的整数倍 */
    if (channel_config_p->trans_length == 0 ||
        (channel_config_p->trans_length % FGDMA_GET_BURST_BYTE(channel_config_p->wr_size)) ||
        (channel_config_p->trans_length % FGDMA_GET_BURST_BYTE(channel_config_p->rd_size)))
    {
        FGDMA_ERROR("Data length %d is not N times of burst size.", channel_config_p->trans_length);
        return FGDMA_ERR_INVALID_SIZE;
    }

    if (channel_config_p->trans_length == 0)
    {
        FGDMA_ERROR("trans_length can not be 0.");
    }
    ret = FGdmaChanDirectSetBasic(instance_p, channel_id, channel_config_p);
    if (ret)
    {
        FGDMA_ERROR("FGdmaChanDirectSetBasic() ERROR.");
        return FGDMA_ERR_COMMON;
    }

    ret = FGdmaChanDirectSetTrans(instance_p,
                                  channel_id, 
                                  channel_config_p->src_addr, 
                                  channel_config_p->dst_addr, 
                                  channel_config_p->trans_length);
    if (ret)
    {
        FGDMA_ERROR("FGdmaChanDirectSetTrans() ERROR.");
        return FGDMA_ERR_COMMON;
    }

    return FGDMA_SUCCESS;
}

/**
 * @name: FGdmaChanBDLConfiguration
 * @msg: BDL模式下GDMA通道配置，这一步还不会开始传输，FGdmaStart后才会开始传输
 * @return {FError} FGDMA_SUCCESS表示配置成功
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @param FGdmaChanConfig const *channel_config_p, GDMA通道配置
 */
static FError FGdmaChanBDLConfiguration(FGdma *const instance_p, FGdmaChanIndex channel_id, const FGdmaChanConfig *channel_config_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->gdma_ready);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);
    FASSERT(channel_config_p);

    FError ret = FGDMA_SUCCESS;

    ret = FGdmaChanBDLSetBasic(instance_p, channel_id, channel_config_p);
    if (ret)
    {
        FGDMA_ERROR("FGdmaChanBDLSetBasic() ERROR.");
        return FGDMA_ERR_COMMON;
    }

    if (((uintptr)channel_config_p->first_desc_addr) % FGDMA_BDL_DESC_ALIGMENT)
    {
        FGDMA_ERROR("BDL descriptor addr %p is not aligned with %d bytes.", channel_config_p->first_desc_addr, FGDMA_BDL_DESC_ALIGMENT);
        return FGDMA_ERR_INVALID_ADDR;
    }

    ret = FGdmaChanBDLSetTrans(instance_p, channel_id, channel_config_p);
    if (ret)
    {
        FGDMA_ERROR("FGdmaChanBDLSetTrans() ERROR.");
        return FGDMA_ERR_COMMON;
    }

    return FGDMA_SUCCESS;
}

/**
 * @name: FGdmaChanConfigure
 * @msg: GDMA通道配置，按照模式将分流为Direct与BDL两种不同模式
 * @return {FError} FGDMA_SUCCESS表示配置成功
 * @param FGdma *const instance_p, GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @param FGdmaChanConfig const *channel_config_p, GDMA通道配置
 */
FError FGdmaChanConfigure(FGdma *const instance_p, FGdmaChanIndex channel_id, FGdmaChanConfig const* channel_config_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->gdma_ready);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);
    FASSERT(channel_config_p);

    /* disable and reset chan */
    FGdmaChanAbort(instance_p, channel_id);
    FGdmaChanIrqDisable(instance_p->config.base_addr, channel_id);
    FGdmaClearChanStatus(instance_p->config.base_addr, channel_id, FGDMA_CHX_INT_STATE_ALL);
    FGdmaChanSoftReset(instance_p->config.base_addr, channel_id);
    FGdmaSetChanClock(instance_p->config.base_addr, channel_id, TRUE); /* enable channel clock */

    FError ret = FGDMA_SUCCESS;
    if (channel_config_p->trans_mode == FGDMA_OPER_DIRECT)
    {
        ret = FGdmaChanDirectConfiguration(instance_p, channel_id, channel_config_p);
        if (ret)
        {
            FGDMA_ERROR("FGdmaChanBDLConfiguration() ERROR.");
            return FGDMA_ERR_COMMON;
        }
    }
    else if (channel_config_p->trans_mode == FGDMA_OPER_BDL)
    {
        ret = FGdmaChanBDLConfiguration(instance_p, channel_id, channel_config_p);
        if (ret)
        {
            FGDMA_ERROR("FGdmaChanBDLConfiguration() ERROR.");
            return FGDMA_ERR_COMMON;
        }
    }
    else
    {
        FGDMA_ERROR("trans_mode WRONG.");
        return FGDMA_ERR_WRONG_PARA;
    }

    return FGDMA_SUCCESS;
}

/**
 * @name: FGdmaChanDeconfigure
 * @msg: 释放GDMA通道
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 */
FError FGdmaChanDeconfigure(FGdma *const instance_p, FGdmaChanIndex channel_id)
{
    FASSERT(instance_p);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);

    if (!(instance_p->chan_ready_flag & BIT(channel_id))) /* if chan not init, directly return */
        return 0;

    uintptr base_addr = instance_p->config.base_addr;

    /* disable chan and it's irq */
    FGdmaChanIrqDisable(base_addr, channel_id);
    FGdmaClearChanStatus(base_addr, channel_id, FGDMA_CHX_INT_STATE_ALL);
    FGdmaChanDisable(base_addr, channel_id);
    FGdmaChanSoftReset(base_addr, channel_id);

    /* disable channel clock */
    FGdmaSetChanClock(base_addr, channel_id, FALSE);

    instance_p->chan_ready_flag &= ~BIT(channel_id);

    return FGDMA_SUCCESS;
}

/**
 * @name FGdmaStartTrans
 * @msg: 启动某个GDMA通道传输
 * @return {FError} FGDMA_SUCCESS表示启动成功
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @note 启动传输操作前，请确保：1.通道已（重新）完成配置 2.上一次传输已正常停止
 */
void FGdmaChanStartTrans(FGdma *const instance_p, FGdmaChanIndex channel_id)
{
    FASSERT(instance_p);
    FASSERT(instance_p->gdma_ready);
    FASSERT_MSG((instance_p->chan_ready_flag & BIT(channel_id)), "selected chan has NOT been initialized.");

    uintptr base_addr = instance_p->config.base_addr;

    /* enable channel */
    FGdmaChanEnable(base_addr, channel_id);

    if (FGDMA_TRANS_NEED_RESET_MASK & instance_p->config.caps)
    {
        FGdmaSoftReset(base_addr);
    }

    /* enable controller */
    FGdmaEnable(base_addr);

    return;
}

/**
 * @name FGdmaGlobalStartTrans
 * @msg: 全局启动GDMA传输，被配置的GDMA通道将同时开始传输
 * @return {FError} FGDMA_SUCCESS表示启动成功
 * @param FGdma *const instance_p GDMA控制器实例
 * @note 启动传输操作前，请确保：1.通道已（重新）完成配置 2.上一次传输已正常停止
 */
void FGdmaGlobalStartTrans(FGdma *const instance_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->gdma_ready);
    FASSERT_MSG((instance_p->chan_ready_flag), "NO ready chan to use.");

    uintptr base_addr = instance_p->config.base_addr;

    /* enable all ready channels */
    for (fsize_t chan_id = 0; chan_id < FGDMA_NUM_OF_CHAN; chan_id++)
    {
        if (instance_p->chan_ready_flag & BIT(chan_id))
            FGdmaChanEnable(base_addr, chan_id);
    }

    if (FGDMA_TRANS_NEED_RESET_MASK & instance_p->config.caps)
    {
        FGdmaSoftReset(base_addr);
    }

    /* enable controller */
    FGdmaEnable(base_addr);

    return;
}

/**
 * @name FGdmaChanAbort
 * @msg: GDMA通道Abort操作，可以暂停某个通道的输出，也可以作为单通道传输完毕后的通道停止操作，不会进行软复位操作
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 操作的GDMA通道的ID
 * @note Abort操作后，可使用FGdmaChanEnable函数继续未完成的传输，也可以使用FGdmaChanConfigure重新配置通道
 */
FError FGdmaChanAbort(FGdma *const instance_p, FGdmaChanIndex channel_id)
{
    FASSERT(instance_p);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);

    if (!(instance_p->chan_ready_flag & BIT(channel_id))) /* if chan not init, directly return */
        return FGDMA_SUCCESS;

    uintptr base_addr = instance_p->config.base_addr;
    fsize_t timeout = 10000;
    u32 chan_status;

    /* Abort流程 */
    FGdmaChanDisable(base_addr, channel_id); /* 停止通道传输 */
    while (TRUE)
    {
        chan_status = FGdmaReadChanStatus(base_addr, channel_id);
        if (!(chan_status & FGDMA_CHX_INT_STATE_BUSY)) /* 轮询通道状态，确认是否已经停止通道传输 */
        {
            FGDMA_INFO("chan-%d completed the current AXI packet request for abort.", channel_id);
            break;
        }
        else
        {
            FGdmaChanDisable(base_addr, channel_id); /* 再次尝试停止通道传输 */
        }

        if (--timeout <= 0)
        {
            FGDMA_ERROR("chan-%d abort ERROR.", channel_id);
            return FGDMA_ERR_COMMON;
        }

        FDriverUdelay(2);
    }

    return FGDMA_SUCCESS;
}

/**
 * @name FGdmaGlobalStop
 * @msg: GDMA全局停止操作，所有通道传输停止，但是不会进行软复位操作
 * @param FGdma *const instance_p GDMA控制器实例
 * @note 该操作会对GDMA通道进行软复位操作，未完成的传输将会被舍弃
 */
FError FGdmaGlobalStop(FGdma *const instance_p)
{
    FASSERT(instance_p);

    uintptr base_addr = instance_p->config.base_addr;
    fsize_t timeout;
    u32 chan_status;

    /* 每一个通道都进行Abort流程 */
    for (fsize_t chan_id = 0; chan_id < FGDMA_NUM_OF_CHAN; chan_id++)
    {
        if (!(instance_p->chan_ready_flag & BIT(chan_id))) /* if chan not init, directly break */
            break;

        timeout = 10000;
        FGdmaChanDisable(base_addr, chan_id); /* 停止通道传输 */
        while (TRUE)
        {
            chan_status = FGdmaReadChanStatus(base_addr, chan_id);
            if (!(chan_status & FGDMA_CHX_INT_STATE_BUSY)) /* 轮询通道状态，确认是否已经停止通道传输 */
            {
                FGDMA_INFO("chan-%d completed the current AXI packet request for abort.", chan_id);
                break;
            }
            else
            {
                FGdmaChanDisable(base_addr, chan_id); /* 再次尝试停止通道传输 */
            }

            if (--timeout <= 0)
            {
                FGDMA_ERROR("chan-%d abort ERROR.", chan_id);
                return FGDMA_ERR_COMMON;
            }

            FDriverUdelay(2);
        }
    }

    FGdmaDisable(base_addr);

    return FGDMA_SUCCESS;
}