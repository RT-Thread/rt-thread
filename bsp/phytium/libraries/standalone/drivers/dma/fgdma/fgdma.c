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

#include "fdebug.h"

#include "fgdma_hw.h"
#include "fgdma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGDMA_DEBUG_TAG "GDMA"
#define FGDMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_WARN(format, ...)    FT_DEBUG_PRINT_W(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
static void FGdmaReset(FGdma *const instance_p);

/************************** Variable Definitions *****************************/

/*****************************************************************************/

/**
 * @name: FGdmaCfgInitialize
 * @msg: 初始化GDMA控制器实例
 * @return {FError} 返回FGDMA_SUCCESS表示初始化成功，返回其它表示失败
 * @param FGdma *const instance_p, GDMA控制器实例
 * @param const FGdmaConfig *input_config, GDMA控制器配置
 */
FError FGdmaCfgInitialize(FGdma *const instance_p, const FGdmaConfig *input_config)
{
    FASSERT(instance_p && input_config);
    uintptr base_addr = input_config->base_addr;
    FError ret = FGDMA_SUCCESS;

    if (FT_COMPONENT_IS_READY == instance_p->is_ready)
    {
        FGDMA_WARN("The device has been initialized!!");
    }

    FGdmaDeInitialize(instance_p);

    if (&instance_p->config != input_config)
    {
        instance_p->config = *input_config;
    }

    FASSERT_MSG((0 != base_addr), "Invalid device base address");
    FGdmaReset(instance_p);

    if (FGDMA_SUCCESS == ret)
    {
        instance_p->is_ready = FT_COMPONENT_IS_READY;
    }

    return ret;
}

/**
 * @name: FGdmaDeInitialize
 * @msg: 去初始化GDMA控制器实例
 * @return {void} 无
 * @param FGdma *const instance_p, GDMA控制器实例
 */
void FGdmaDeInitialize(FGdma *const instance_p)
{
    FASSERT(instance_p);
    u32 chan;

    for (chan = 0; chan < FGDMA_NUM_OF_CHAN; chan++)
    {
        if (NULL != instance_p->chans[chan])
        {
            FGDMA_WARN("chans-% d may be used!!!", chan);
        }
    }

    memset(instance_p, 0, sizeof(*instance_p));
    return;
}

/**
 * @name: FGdmaSetChanQos
 * @msg: 设置GDMA通道的Qos配置
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {FGdmaChan} *dma_chan, GDMA通道实例
 */
static void FGdmaSetChanQos(uintptr base_addr, FGdmaChan *const dma_chan)
{
    FASSERT(dma_chan);
    FGdmaChanIndex chan_id = dma_chan->config.chan_id;
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CHX_MODE_OFFSET(chan_id));
    FGdmaOperPriority prev_rd_qos = FGDMA_CHX_MODE_RD_QOS_GET(reg_val);
    FGdmaOperPriority prev_wr_qos = FGDMA_CHX_MODE_WR_QOS_GET(reg_val);

    FGDMA_INFO("prev rd qos: 0x%x, set rd qos: 0x%x", prev_rd_qos, dma_chan->config.rd_qos);
    FGDMA_INFO("prev wr qos: 0x%x, set wr qos: 0x%x", prev_wr_qos, dma_chan->config.wr_qos);

    if (prev_rd_qos != dma_chan->config.rd_qos) /* need to update rd qos */
    {
        /* replace with new rd qos config */
        reg_val &= ~FGDMA_CHX_MODE_RD_QOS_MASK;
        reg_val |= FGDMA_CHX_MODE_RD_QOS_EN |
                   FGDMA_CHX_MODE_RD_QOS_SET(dma_chan->config.rd_qos);
    }

    if (prev_wr_qos != dma_chan->config.wr_qos) /* need to update wr qos */
    {
        /* replace with new wr qos config */
        reg_val &= ~FGDMA_CHX_MODE_WR_QOS_MASK;
        reg_val |= FGDMA_CHX_MODE_WR_QOS_EN |
                   FGDMA_CHX_MODE_WR_QOS_SET(dma_chan->config.wr_qos);
    }

    FGDMA_WRITEREG(base_addr, FGDMA_CHX_MODE_OFFSET(chan_id), reg_val);
    return;
}

/**
 * @name: FGdmaAllocateChan
 * @msg: 分配指定GDMA通道
 * @return {FError} FGDMA_SUCCESS表示分配成功，返回其它值表示分配失败
 * @param FGdma *const instance_p, GDMA控制器实例
 * @param FGdmaChan *const dma_chan, GDMA通道实例
 * @param const FGdmaChanConfig *dma_chan_config, GDMA通道配置
 */
FError FGdmaAllocateChan(FGdma *const instance_p, FGdmaChan *const dma_chan,
                         const FGdmaChanConfig *dma_chan_config)
{
    FASSERT(instance_p);
    FASSERT(dma_chan);
    FASSERT(dma_chan_config);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FGDMA_SUCCESS;
    FGdmaChanIndex chan_idx = dma_chan_config->chan_id;
    u32 reg_val;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FGDMA_ERROR("The dma instance is not initialized !!!");
        return FGDMA_ERR_NOT_INIT;
    }

    if(chan_idx >= FGDMA_NUM_OF_CHAN)
    {
        FGDMA_ERROR("Channel %d is in use !!!", chan_idx);
        return FGDMA_ERR_CHAN_IN_USE;
    }

    if (NULL != instance_p->chans[chan_idx])
    {
        FGDMA_ERROR("Channel %d is in use !!!", chan_idx);
        return FGDMA_ERR_CHAN_IN_USE;
    }

    if (&dma_chan->config != dma_chan_config)
    {
        dma_chan->config = *dma_chan_config;
    }

    /* disable and reset chan */
    FGdmaChanDisable(base_addr, chan_idx);
    FGdmaChanReset(base_addr, chan_idx);

    /* enable channel clock */
    FGdmaSetChanClock(base_addr, chan_idx, TRUE);

    /* set chan mode */
    reg_val = FGDMA_READREG(base_addr, FGDMA_CHX_MODE_OFFSET(chan_idx));
    if (FGDMA_OPER_BDL == dma_chan->config.trans_mode)
    {
        FGDMA_INFO("Set to BDL mode");
        reg_val |= FGDMA_CHX_MODE_BDL_EN;

        if (dma_chan->config.roll_back)
        {
            reg_val |= FGDMA_CHX_MODE_BDL_ROLL_EN; /* run BDL in roll-back mode */
        }
        else
        {
            reg_val &= ~FGDMA_CHX_MODE_BDL_ROLL_EN;
        }
    }
    else
    {
        FGDMA_INFO("Set to Direct mode");
        reg_val &= ~FGDMA_CHX_MODE_BDL_EN;
        reg_val &= ~FGDMA_CHX_MODE_BDL_ROLL_EN;
    }
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_MODE_OFFSET(chan_idx), reg_val);

    FGdmaSetChanQos(base_addr, dma_chan);
    FGDMA_INFO("mode: 0x%x", FGDMA_READREG(base_addr, FGDMA_CHX_MODE_OFFSET(chan_idx)));

    /* set xfer config */
    reg_val = 0;
    reg_val |= FGDMA_CHX_XFER_CFG_AR_LEN_SET(FGDMA_BURST_LEN) | /* burst length configed as max 8, which adapted when trans bytes less than 8 */
               FGDMA_CHX_XFER_CFG_AR_SIZE_SET((u32)dma_chan->config.rd_size) |
               FGDMA_CHX_XFER_CFG_AR_BRUST_SET(FGDMA_INCR); /* mem to mem trans work in incr mode */

    reg_val |= FGDMA_CHX_XFER_CFG_AW_LEN_SET(FGDMA_BURST_LEN) |
               FGDMA_CHX_XFER_CFG_AW_SIZE_SET((u32)dma_chan->config.wr_size) |
               FGDMA_CHX_XFER_CFG_AW_BRUST_SET(FGDMA_INCR); /* mem to mem trans work in incr mode */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_XFER_CFG_OFFSET(chan_idx), reg_val);
    FGDMA_INFO("xfer cfg: 0x%x", FGDMA_READREG(base_addr, FGDMA_CHX_XFER_CFG_OFFSET(chan_idx)));

    instance_p->chans[chan_idx] = dma_chan;
    dma_chan->gdma = instance_p;

    if (dma_chan->config.wait_mode == FGDMA_WAIT_INTR)
    {
        /* enable channel interrupt */
        FGdmaChanIrqEnable(base_addr, chan_idx, FGDMA_CHX_INT_CTRL_TRANS_END_ENABLE);
    }
    
    return ret;
}

/**
 * @name: FGdmaDellocateChan
 * @msg: 释放GDMA通道
 * @return {FError} FGDMA_SUCCESS表示处理成功
 * @param FGdmaChan *const dma_chan, GDMA通道实例
 */
FError FGdmaDellocateChan(FGdmaChan *const dma_chan)
{
    FASSERT(dma_chan);
    FASSERT(dma_chan->gdma);
    FGdma *const instance_p = dma_chan->gdma;
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FGDMA_SUCCESS;
    FGdmaChanIndex chan_idx = dma_chan->config.chan_id;
    u32 reg_val;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FGDMA_ERROR("The dma instance is not initialized !!!");
        return FGDMA_ERR_NOT_INIT;
    }

    if (dma_chan != instance_p->chans[chan_idx])
    {
        FGDMA_ERROR("chan %d not bind !!!", chan_idx);
        return FGDMA_ERR_CHAN_NOT_INIT;
    }

    /* disable chan and it irq */
    FGdmaChanIrqDisable(base_addr, chan_idx);
    FGdmaChanDisable(base_addr, chan_idx);

    /* disable channel clock */
    FGdmaSetChanClock(base_addr, chan_idx, FALSE);

    instance_p->chans[chan_idx] = NULL;
    memset(dma_chan, 0, sizeof(*dma_chan));

    return ret;
}

/**
 * @name: FGdmaDirectTransfer
 * @msg: 直接操作模式下发起DMA传输
 * @return {FError} FGDMA_SUCCESS表示传输成功
 * @param FGdmaChan *const chan_p, GDMA通道实例
 * @param uintptr src_addr, 传输源地址
 * @param uintptr dst_addr, 传输目的地址
 */
FError FGdmaDirectTransfer(FGdmaChan *const chan_p, uintptr src_addr, uintptr dst_addr, fsize_t data_len)
{
    FASSERT(chan_p);
    FASSERT(chan_p->gdma);
    u32 reg_val;
    FGdma *const instance_p = chan_p->gdma;
    uintptr base_addr = instance_p->config.base_addr;
    FGdmaChanIndex chan_idx = chan_p->config.chan_id;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FGDMA_ERROR("The dma instance is not initialized !!!");
        return FGDMA_ERR_NOT_INIT;
    }

    if ((src_addr % FGDMA_GET_BURST_BYTE(chan_p->config.rd_size)) ||
        (dst_addr % FGDMA_GET_BURST_BYTE(chan_p->config.wr_size))) /* 报文传输的首地址需要与burst size所代表的单次burst传输的最大数据字节数对齐 */
    {
        FGDMA_ERROR("src addr 0x%x or dst addr 0x%x not aligned with burst size !!!",
                    src_addr, dst_addr);
        return FGDMA_ERR_INVALID_ADDR;
    }

    if (0 != (data_len % FGDMA_GET_BURST_BYTE(chan_p->config.wr_size))) /* 报文传输的总数据量必须是burst size所代表的单次burst传输的最大数据字节数的整数倍 */
    {
        FGDMA_ERROR("data length %d must be N times of burst size: %d bytes!!!",
                    data_len, FGDMA_GET_BURST_BYTE(chan_p->config.wr_size));
        return FGDMA_ERR_INVALID_SIZE;
    }

    /* src address */
#ifdef __aarch64__
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(chan_idx), UPPER_32_BITS(src_addr));
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(chan_idx), LOWER_32_BITS(src_addr));
#else
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(chan_idx), 0x0U);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(chan_idx), (u32)(src_addr));
#endif

    FGDMA_INFO("src: 0x%x-0x%x",
               FGDMA_READREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(chan_idx)),
               FGDMA_READREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(chan_idx)));

    /* dest address */
#ifdef __aarch64__
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(chan_idx), UPPER_32_BITS(dst_addr));
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(chan_idx), LOWER_32_BITS(dst_addr));
#else
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(chan_idx), 0x0U);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(chan_idx), (u32)(dst_addr));
#endif

    FGDMA_INFO("dst: 0x%x-0x%x",
               FGDMA_READREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(chan_idx)),
               FGDMA_READREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(chan_idx)));

    /* num of BDL entry not used in direct mode */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LVI_OFFSET(chan_idx), 0x0U);

    /* length of data to transfer */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_TS_OFFSET(chan_idx), data_len);

    FGDMA_INFO("ts: 0x%x", FGDMA_READREG(base_addr, FGDMA_CHX_TS_OFFSET(chan_idx)));

    /* enable channel and start transfer */
    FGdmaChanEnable(base_addr, chan_idx);

    return FGDMA_SUCCESS;
}

/**
 * @name: FGdmaSetupBDLEntry
 * @msg: 设置BDL描述符的一个条目
 * @return {FError} FGDMA_SUCCESS 表示设置成功
 * @param FGdmaBdlDesc *desc_entry, 一条BDL描述符
 * @param uintptr src_addr, 传输源地址
 * @param uintptr dst_addr, 传输目的地址
 * @param fsize_t data_len, 传输数据长度
 */
FError FGdmaAppendBDLEntry(FGdmaChan *const chan_p, uintptr src_addr, uintptr dst_addr, fsize_t data_len)
{
    FASSERT(chan_p);
    FASSERT_MSG((chan_p->config.descs) && (chan_p->config.total_desc_num > 0), "The list of BDL descriptors has not yet been assigned !!!");
    u32 desc_idx = chan_p->config.valid_desc_num;
    FGdmaBdlDesc *desc_entry = &(chan_p->config.descs[desc_idx]);

    if (chan_p->config.valid_desc_num >= chan_p->config.total_desc_num)
    {
        FGDMA_ERROR("The total BDL descriptor num is %d and has been used up", chan_p->config.total_desc_num);
        return FGDMA_ERR_BDL_NOT_ENOUGH;
    }

    if ((0U != (dst_addr % FGDMA_GET_BURST_BYTE(chan_p->config.wr_size))) || 
        (0U != (src_addr % FGDMA_GET_BURST_BYTE(chan_p->config.rd_size)))) /* 报文传输的首地址需要与burst size所代表的单次burst传输的最大数据字节数对齐 */
    {
        FGDMA_ERROR("SRC addr 0x%x or DST addr 0x%x are not aligned with the %d transfer size",
                    src_addr, dst_addr, FGDMA_GET_BURST_BYTE(chan_p->config.wr_size));
        return FGDMA_ERR_INVALID_ADDR;
    }

    if (0U != (data_len % FGDMA_GET_BURST_BYTE(chan_p->config.wr_size))) /* 报文传输的总数据量必须是burst size所代表的单次burst传输的最大数据字节数的整数倍 */
    {
        FGDMA_ERROR("The data length %d must be N times the burst size %d !!!",
                    data_len, FGDMA_GET_BURST_BYTE(chan_p->config.wr_size));
        return FGDMA_ERR_INVALID_SIZE;
    }

#ifdef __aarch64___
    desc_entry->src_addr_h = UPPER_32_BITS(src_addr);
    desc_entry->src_addr_l = LOWER_32_BITS(src_addr);
    desc_entry->dst_addr_h = UPPER_32_BITS(dst_addr);
    desc_entry->dst_addr_l = LOWER_32_BITS(dst_addr);
#else
    desc_entry->src_addr_h = 0U;
    desc_entry->src_addr_l = src_addr;
    desc_entry->dst_addr_h = 0U;
    desc_entry->dst_addr_l = dst_addr;
#endif

    /* rd = src */
    desc_entry->src_tc = FGDMA_SRC_TC_BDL_BURST_SET(FGDMA_INCR) |
                         FGDMA_SRC_TC_BDL_SIZE_SET((u32)chan_p->config.rd_size) |
                         FGDMA_SRC_TC_BDL_LEN_SET(FGDMA_BURST_LEN);

    /* wr = dst */
    desc_entry->dst_tc = FGDMA_DST_TC_BDL_BURST_SET(FGDMA_INCR) |
                         FGDMA_DST_TC_BDL_SIZE_SET((u32)chan_p->config.wr_size) |
                         FGDMA_DST_TC_BDL_LEN_SET(FGDMA_BURST_LEN);

    desc_entry->total_bytes = data_len;
    desc_entry->ioc = 0U;

    chan_p->config.valid_desc_num++;

    return FGDMA_SUCCESS;
}

/**
 * @name: FGdmaBDLTransfer
 * @msg: BDL操作模式下发起DMA传输
 * @return {FError} FGDMA_SUCCESS 表示传输成功
 * @param FGdmaChan *const chan_p, DMA通道实例
 */
FError FGdmaBDLTransfer(FGdmaChan *const chan_p)
{
    FASSERT(chan_p);
    FASSERT(chan_p->gdma);
    FASSERT_MSG((chan_p->config.descs) && (chan_p->config.total_desc_num > 0), "BDL descriptor list not yet assign !!!");
    u32 reg_val;
    FGdma *const instance_p = chan_p->gdma;
    uintptr base_addr = instance_p->config.base_addr;
    FGdmaChanIndex chan_idx = chan_p->config.chan_id;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FGDMA_ERROR("The dma instance is not initialized !!!");
        return FGDMA_ERR_NOT_INIT;
    }

    if (0 == chan_p->config.valid_desc_num)
    {
        FGDMA_WARN("First, the BDL entries need to be allocated !!!");
        return FGDMA_SUCCESS;
    }

    if (((uintptr)(void *)chan_p->config.descs) % FGDMA_ADDR_ALIGMENT)
    {
        FGDMA_ERROR("BDL addr %p not aligned with %d bytes", chan_p->config.descs, FGDMA_ADDR_ALIGMENT);
        return FGDMA_ERR_INVALID_ADDR;
    }

    u32 desc_idx = chan_p->config.valid_desc_num - 1;
    FGdmaBdlDesc *descs = chan_p->config.descs; /* get the first BDL entry */

    chan_p->config.descs[desc_idx].ioc = 1U; /* set as the last BDL entry */

    /* src address, and dst address has been defined in BDL */
#ifdef __aarch64__
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(chan_idx), UPPER_32_BITS((uintptr)descs));
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(chan_idx), LOWER_32_BITS((uintptr)descs));
#else
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPSADDR_OFFSET(chan_idx), 0x0U);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWSADDR_OFFSET(chan_idx), (u32)((uintptr)descs));
#endif

    /* dst address not used in BDL mode */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_UPDADDR_OFFSET(chan_idx), 0x0U);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LWDADDR_OFFSET(chan_idx), 0x0U);

    /* ts not used in BDL mode */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_TS_OFFSET(chan_idx), 0x0U);

    /* num of BDL entry */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_LVI_OFFSET(chan_idx), FGDMA_CHX_LVI_SET(chan_p->config.valid_desc_num));

    /* enable channel and start transfer */
    FGdmaChanEnable(base_addr, chan_idx);

    return FGDMA_SUCCESS;
}

/**
 * @name: FGdmaStart
 * @msg: 使能启动GDMA控制器
 * @return {FError} FGDMA_SUCCESS表示启动成功
 * @param FGdma *const instance_p, GDMA控制器实例
 * @note: 先调用此函数，后调用FGdmaAllocateChan配置特定通道
 */
FError FGdmaStart(FGdma *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;
    
    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FGDMA_ERROR("The dma instance is not initialized !!!");
        return FGDMA_ERR_NOT_INIT;
    }
    if(FGDMA_TRANS_NEED_RESET_MASK & instance_p->config.caps)
    {
        FGdmaSoftwareReset(base_addr);
    }
    FGdmaIrqEnable(base_addr);

    reg_val = FGDMA_READREG(base_addr, FGDMA_CTL_OFFSET);
    reg_val &= ~FGDMA_CTL_OT_MASK;
    reg_val |= FGDMA_CTL_OT_SET(FGDMA_OUTSTANDING); /* 设置传输outstanding数 */
    reg_val |= FGDMA_CTL_ENABLE; /* 使能DMA传输 */
    FGDMA_WRITEREG(base_addr, FGDMA_CTL_OFFSET, reg_val);

    return FGDMA_SUCCESS; //放到初始化
}

/**
 * @name: FGdmaStop
 * @msg: 停止GDMA控制器
 * @return {FError} FGDMA_SUCCESS表示处理成功
 * @param FGdma *const instance_p, GDMA控制器实例
 */
FError FGdmaStop(FGdma *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;
    u32 chan_id;
    u32 chan_status;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FGDMA_ERROR("The dma instance is not initialized !!!");
        return FGDMA_ERR_NOT_INIT;
    }

    /* Abort 流程 */
    for (chan_id = 0; chan_id < FGDMA_NUM_OF_CHAN; chan_id++)
    {
        if (NULL == instance_p->chans[chan_id])
        {
            continue;    /* skip un-allocate channel */
        }

        chan_status = FGdmaReadChanStatus(base_addr, chan_id);
        if (FGDMA_CHX_INT_STATE_BUSY & chan_status)
        {
            FGDMA_WARN("chan-%d was forcibly closed !!!", chan_id);
            FGdmaChanDisable(base_addr, chan_id); /* 关闭通道 */
            FGdmaChanReset(base_addr, chan_id); /* 需要进行软复位，否则再次使能通道时，仍然会执行之前的请求 */
        }
        else
        {
            FGdmaChanDisable(base_addr, chan_id); /* 关闭通道 */
        }

        FGdmaClearChanStatus(base_addr, chan_id, chan_status); /* 清除通道状态 */
    }

    FGdmaDisable(base_addr);
    
    return FGDMA_SUCCESS;
}

/**
 * @name: FGdmaSetQos
 * @msg: 设置GDMA控制器的全局Qos配置
 * @return {void} 无
 * @param {FGdma} *instance_p, GDMA控制器实例
 */
static void FGdmaSetQos(FGdma *const instance_p)
{
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;

    /* enable/disable Qos */
    reg_val = FGDMA_READREG(base_addr, FGDMA_CTL_OFFSET);
    if (FGDMA_OPER_NONE_PRIORITY_POLL == instance_p->config.rd_qos) /* Poll mode */
    {
        reg_val &= ~FGDMA_CTL_RD_ARB;
    }
    else /* Qos mode */
    {
        reg_val |= FGDMA_CTL_RD_ARB;
    }

    if (FGDMA_OPER_NONE_PRIORITY_POLL == instance_p->config.wr_qos) /* Poll mode */
    {
        reg_val &= ~FGDMA_CTL_WR_ARB;
    }
    else /* Qos mode */
    {
        reg_val |= FGDMA_CTL_WR_ARB;
    }
    FGDMA_WRITEREG(base_addr, FGDMA_CTL_OFFSET, reg_val);

    /* set Qos configure */
    reg_val = FGDMA_READREG(base_addr, FGDMA_QOS_CFG_OFFSET);
    if (FGDMA_OPER_NONE_PRIORITY_POLL == instance_p->config.rd_qos) /* Poll mode */
    {
        reg_val &= ~FGDMA_QOS_CFG_ARGOS_MASK;
    }
    else /* Qos value */
    {
        reg_val |= FGDMA_QOS_CFG_ARGOS_SET((u32)instance_p->config.rd_qos);
    }

    if (FGDMA_OPER_NONE_PRIORITY_POLL == instance_p->config.wr_qos) /* Poll mode */
    {
        reg_val &= ~FGDMA_QOS_CFG_AWQOS_MASK;
    }
    else /* Qos value */
    {
        reg_val |= FGDMA_QOS_CFG_AWQOS_SET((u32)instance_p->config.wr_qos);
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
    u32 chan;
    u32 reg_val;

    FGDMA_INFO("Controller base address is %p ...", base_addr);

    FGdmaDisable(base_addr);
    FGdmaSoftwareReset(base_addr);

    FGdmaSetQos(instance_p);

    FGDMA_INFO("Reset channel");

    for (chan = 0; chan < FGDMA_NUM_OF_CHAN; chan++)
    {
        FGdmaChanDisable(base_addr, chan);
        FGdmaChanIrqDisable(base_addr, chan);
        FGdmaChanReset(base_addr, chan);
        FGdmaSetChanClock(base_addr, chan, FALSE);
    }
    
    return;
}