/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fddma_bdl.c
 * Created Date: 2023-08-08 15:46:34
 * Last Modified: 2023-10-07 14:37:24
 * Description:  This file is for
 *
 * Modify History:
 *   Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 */
#include <string.h>

#include "fkernel.h"
#include "fparameters.h"
#include "fassert.h"
#include "fdrivers_port.h"

#include "fddma_hw.h"
#include "fddma.h"

/***************** Macros (Inline Functions) Definitions *********************/
#define FDDMA_DEBUG_TAG "DDMA"
#define FDDMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_WARN(format, ...)   FT_DEBUG_PRINT_W(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)


/**
 * @name: FDdmaAppendBDLEntry
 * @msg:  创建DDMA描述符
 * @param {FDdmaChan } *const chan_p， DDMA通道配置
 * @param {uintptr} src_addr, DDMA传输源地址
 * @param {fsize_t} data_len, DDMA每一个描述符传输长度
 * @return {FError} FDDMA_SUCCESS表示重置成功，其它返回值表示失败
 */
FError FDdmaAppendBDLEntry(FDdmaChan *const chan_p, uintptr src_addr,  fsize_t data_len)
{
    FASSERT(chan_p != NULL);
    FASSERT(chan_p->config.descs);
    FASSERT(chan_p->config.total_desc_num > 0);

    u32 desc_idx = chan_p->config.valid_desc_num;
    FDdmaBdlDesc *desc_entry = &(chan_p->config.descs[desc_idx]);

    if (chan_p->config.valid_desc_num >= chan_p->config.total_desc_num)
    {
        FDDMA_ERROR("The total BDL descriptor num is %d and has been used up", chan_p->config.total_desc_num);
        return FDDMA_ERR_BDL_NOT_ENOUGH;
    }

#ifdef __aarch64__
    desc_entry->src_addr_l = LOWER_32_BITS(src_addr);
    desc_entry->src_addr_h = UPPER_32_BITS(src_addr);
#else
    desc_entry->src_addr_h = 0U;
    desc_entry->src_addr_l = src_addr;
#endif
    desc_entry->total_bytes = data_len ;
    desc_entry->ioc = 1U;
  
    chan_p->config.valid_desc_num++;
    return FDDMA_SUCCESS;
}

/**
 * @name: FDdmaBDLTransfer
 * @msg:  通过DDMA描述符传输数据
 * @param {FDdmaChan } *const chan_p， DDMA通道配置
 * @return {FError} FDDMA_SUCCESS表示重置成功，其它返回值表示失败
 */
FError FDdmaBDLTransfer(FDdmaChan *const chan_p)
{
    FASSERT(chan_p);
    FASSERT(chan_p->dma);

    u32 reg_val;
    u32 chan_index = chan_p->config.id;
    FDdma *const instance_p = chan_p->dma;
    uintptr base_addr = instance_p->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FDDMA_ERROR("The dma instance is not initialized !!!");
        return FDDMA_ERR_NOT_INIT;
    }

    if (0 == chan_p->config.valid_desc_num)
    {
        FDDMA_WARN("First, the BDL entries need to be allocated !!!");
        return FDDMA_ERR_BDL_NO_INVALID_BLOCK;
    }
    if (((uintptr)(void *)chan_p->config.descs % FDDMA_BDL_ADDR_ALIGMENT))
    {
        FDDMA_ERROR("BDL addr %p not aligned with %d bytes", chan_p, FDDMA_BDL_ADDR_ALIGMENT);
        return FDDMA_ERR_BDL_INVALID_ADDR;
    }
    u32 desc_idx = chan_p->config.valid_desc_num - 1;
    FDdmaBdlDesc *descs = chan_p->config.descs; /* get the first BDL entry */

    chan_p->config.descs[desc_idx].ioc = 1U;/* get the last BDL entry */

#ifdef __aarch64__
    FDdmaWriteReg(base_addr, FDDMA_CHAN_DDR_LOW_ADDR_OFFSET(chan_index),LOWER_32_BITS ((uintptr)descs));
    FDdmaWriteReg(base_addr, FDDMA_CHAN_DDR_UP_ADDR_OFFSET(chan_index), UPPER_32_BITS((uintptr)descs));
#else
    FDdmaWriteReg(base_addr, FDDMA_CHAN_DDR_UP_ADDR_OFFSET(chan_index), 0x0U);
    FDdmaWriteReg(base_addr, FDDMA_CHAN_DDR_LOW_ADDR_OFFSET(chan_index), (u32)((uintptr)descs));
#endif
    if (0 != (chan_p->config.trans_len % FDDMA_BDL_VALID_NUM))
    {
        FDDMA_ERROR("BDL addr %p not aligned with %d bytes", chan_p, FDDMA_BDL_VALID_NUM);
        return FDDMA_ERR_BDL_INVALID_SIZE;
    }
   FDdmaWriteReg(base_addr, FDDMA_CHAN_DEV_ADDR_OFFSET(chan_index), chan_p->config.dev_addr);
    FDdmaWriteReg(base_addr, FDDMA_CHAN_BUFFER_SIZE(chan_index), chan_p->config.trans_len);
    FDdmaWriteReg(base_addr, FDDMA_CHAN_BDL_VALID_NUM(chan_index),chan_p->config.valid_desc_num - 1);

    if (chan_p->config.req_mode == FDDMA_CHAN_REQ_TX)
    {
        /*通道信号线源选择，通道0做发送端，通道1做接收端*/
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_0_3_CFG_OFFSET);
        reg_val |= FDDMA_CHAN_0_3_SEL_EN(chan_index);
        reg_val &= ~ FDDMA_CHAN_0_3_SEL_BDL(chan_index);
        FDdmaWriteReg(base_addr, FDDMA_CHAN_0_3_CFG_OFFSET, reg_val);

        /*AXI读写每次传输字节长度*/
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_DSIZE(chan_index));
        reg_val |= FDDMA_CHAN_AXI_READ_SIZE0_SET(FDDMA_BURST_SIZE_4_BYTE);
        reg_val |= FDDMA_CHAN_AXI_WRITE_SIZE0_SET(FDDMA_BURST_SIZE_2_BYTE);
        FDdmaWriteReg(base_addr, FDDMA_CHAN_DSIZE(chan_index), reg_val);

        /*AXI读写每次传输长度*/
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_DLENTH(chan_index));
        reg_val |= FDDMA_CHAN_AXI_READ_LENTH_SET(FDDMA_BURST_LENTH_1);
        reg_val |= FDDMA_CHAN_AXI_WRITE_SIZE0_SET(FDDMA_BURST_LENTH_1);
        FDdmaWriteReg(base_addr, FDDMA_CHAN_DLENTH(chan_index), reg_val);

        /*配置通道DMA->device传输模式*/
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan_index));
        reg_val &= ~FDDMA_CHAN_CTL_RXTX_MODE;
        FDdmaWriteReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan_index), reg_val);
        /*打开通道 DMA请求传输完成中断*/
    }

    else
    {
        /*通道信号线源选择，通道0做发送端，通道1做接收端*/
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_0_3_CFG_OFFSET);
        reg_val |= FDDMA_CHAN_0_3_SEL_EN(chan_index);
        reg_val |= FDDMA_CHAN_0_3_SEL_BDL(chan_index);
        FDdmaWriteReg(base_addr, FDDMA_CHAN_0_3_CFG_OFFSET, reg_val);

        /*AXI读写每次传输字节长度*/
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_DSIZE(chan_index));
        reg_val |= FDDMA_CHAN_AXI_READ_SIZE0_SET(FDDMA_BURST_SIZE_2_BYTE);
        reg_val |= FDDMA_CHAN_AXI_WRITE_SIZE0_SET(FDDMA_BURST_SIZE_4_BYTE);
        FDdmaWriteReg(base_addr, FDDMA_CHAN_DSIZE(chan_index), reg_val);

        /*AXI读写每次传输长度*/
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_DLENTH(chan_index));
        reg_val |= FDDMA_CHAN_AXI_READ_LENTH_SET(FDDMA_BURST_LENTH_1);
        reg_val |= FDDMA_CHAN_AXI_WRITE_SIZE0_SET(FDDMA_BURST_LENTH_1);
        FDdmaWriteReg(base_addr, FDDMA_CHAN_DLENTH(chan_index), reg_val);
        /*配置通道device - > DMA传输模式*/
        reg_val = FDdmaReadReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan_index));
        reg_val |= FDDMA_CHAN_CTL_RXTX_MODE;
        FDdmaWriteReg(base_addr, FDDMA_CHAN_CTL_OFFSET(chan_index), reg_val);

    }
    FDdmaClearChanIrq(base_addr, chan_index, instance_p->config.caps);  /* clear interrupt status */
    FDdmaEnableChanIrq(base_addr, chan_index, instance_p->config.caps);
    FDdmaEnableChan(base_addr, chan_index);
    FDdmaEnableGlobalIrq(base_addr, instance_p->config.caps);
    /*使能整个DMA控制器*/
    FDdmaEnable(base_addr);
    return FDDMA_SUCCESS;
}

/**
 * @name: FDdmaBdlSetChan
 * @msg:  检查并设置用于DDMA BDL模式的通道
 * @param {FDdma} *instance, DDMA控制器实例
 * @param {FDdmaChan} *dma_chan, DDMA通道实例
 * @param {FDdmaChanConfig} *dma_chan_config, DDMA通道配置
 * @return {FError} FDDMA_SUCCESS表示重置成功，其它返回值表示失败
 */
FError FDdmaBdlSetChan(FDdma *const instance, FDdmaChan *const dma_chan, const FDdmaChanConfig *dma_chan_config)
{

    FASSERT(instance && dma_chan && dma_chan_config);
    FError ret = FDDMA_SUCCESS;
    const FDdmaChanIndex chan_idx = dma_chan_config->id;
    u32 reg_val;
    uintptr base_addr = instance->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FDDMA_ERROR("The Dma instance is not initialized !!!");
        return FDDMA_ERR_NOT_INIT;
    }

    if ((TRUE == dma_chan->is_used) || (BIT(chan_idx) & instance->bind_status))
    {
        FDDMA_ERROR("Channel -%d has already been used !!!", chan_idx);
        return FDDMA_ERR_CHAN_BINDED;
    }

    if (FDdmaIsChanRunning(base_addr, chan_idx))
    {
        FDDMA_ERROR("Channel -%d is running !!!", chan_idx);
        return FDDMA_ERR_CHAN_BINDED;
    }

    if (dma_chan_config->ddr_addr % FDDMA_DDR_ADDR_ALIGMENT)
    {
        FDDMA_ERROR("DDR addr 0x%x must be aligned with %d bytes",
                    dma_chan_config->ddr_addr, FDDMA_DDR_ADDR_ALIGMENT);
        return FDDMA_ERR_INVALID_DDR_ADDR;
    }

    if ((FDDMA_MIN_TRANSFER_LEN > dma_chan_config->trans_len) ||
        (0 != dma_chan_config->trans_len % FDDMA_MIN_TRANSFER_LEN))
    {
        FDDMA_ERROR("Invalid transfer size %d bytes !!!", dma_chan_config->trans_len);
        return FDDMA_ERR_INVALID_TRANS_SIZE;
    }

    dma_chan->dma = instance;
    instance->chan[chan_idx] = dma_chan;

    if (&(dma_chan->config) != dma_chan_config)
    {
        dma_chan->config = *dma_chan_config;
    }

    FDdmaStop(instance); /* disable irq */

    if (FDDMA_SUCCESS != FDdmaDisableChan(base_addr, chan_idx))
    {
        FDDMA_ERROR("Failed to disable DDMA@0x%x channel %d !!!", base_addr, chan_idx);
        return FDDMA_ERR_WAIT_TIMEOUT;
    }

    FDdmaResetChan(base_addr, chan_idx); /* reset channel */
    FDdmaEnableChanIrq(base_addr, chan_idx, instance->config.caps);

    return ret;
}


