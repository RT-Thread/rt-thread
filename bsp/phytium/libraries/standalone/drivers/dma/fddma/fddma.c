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
 * FilePath: fddma.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:47
 * Description:  This file is for ddma interface implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/13    init commit
 */

/***************************** Include Files *********************************/
#include <string.h>

#include "fkernel.h"
#include "fparameters.h"
#include "fassert.h"
#include "fdebug.h"

#include "fddma_hw.h"
#include "fddma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FDDMA_DEBUG_TAG "DDMA"
#define FDDMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_WARN(format, ...)   FT_DEBUG_PRINT_W(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
static FError FDdmaReset(FDdma *const instance);

/****************************************************************************/
/**
 * @name: FDdmaCfgInitialization
 * @msg: 初始化DDMA控制器
 * @return {FError} FDDMA_SUCCESS表示初始化成功，其它返回值表示初始化失败
 * @param {FDdma} *instance, DDMA控制器实例
 * @param {FDdmaConfig} *input_config, DDMA控制器配置
 */
FError FDdmaCfgInitialization(FDdma *const instance, const FDdmaConfig *input_config)
{
    FASSERT(instance && input_config);
    uintptr base_addr = input_config->base_addr;
    FError ret = FDDMA_SUCCESS;

    if (FT_COMPONENT_IS_READY == instance->is_ready)
    {
        FDDMA_WARN("The device has been initialized !!!");
    }

    FDdmaDeInitialization(instance);
    instance->config = *input_config;

    ret = FDdmaReset(instance);
    if (FDDMA_SUCCESS == ret)
    {
        instance->is_ready = FT_COMPONENT_IS_READY;
        FDDMA_INFO("ddma@0x%x initialized successfully !!!", base_addr);
    }

    return ret;
}

/**
 * @name: FDdmaStart
 * @msg: 启动DDMA控制器，开始传输
 * @return {FError} FDDMA_SUCCESS表示启动成功，其它返回值表示启动失败
 * @param {FDdma} *instance, DDMA控制器实例
 */
FError FDdmaStart(FDdma *const instance)
{
    FASSERT(instance);
    FError ret = FDDMA_SUCCESS;
    uintptr base_addr = instance->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FDDMA_ERROR("The Dma instance is not initialized !!!");
        return FDDMA_ERR_NOT_INIT;
    }

    FDdmaEnableGlobalIrq(base_addr); /* enable ddma irq */
    FDdmaEnable(base_addr);
    return FDDMA_SUCCESS;
}

/**
 * @name: FDdmaStop
 * @msg: 停止DDMA控制器
 * @return {FError} FDDMA_SUCCESS表示停止成功，其它返回值表示停止失败
 * @param {FDdma} *instance, DDMA控制器实例
 */
FError FDdmaStop(FDdma *const instance)
{
    FASSERT(instance);
    FError ret = FDDMA_SUCCESS;
    uintptr base_addr = instance->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FDDMA_ERROR("The Dma instance is not initialized !!!");
        return FDDMA_ERR_NOT_INIT;
    }

    FDdmaDisableGlobalIrq(base_addr); /* enable ddma irq */
    FDdmaDisable(base_addr);
    return FDDMA_SUCCESS;
}

/**
 * @name: FDdmaDeInitialization
 * @msg: 去初始化DDMA控制器
 * @return {无}
 * @param {FDdma} *instance, DDMA控制器实例
 */
void FDdmaDeInitialization(FDdma *const instance)
{
    FASSERT(instance);
    u32 chan;

    for (chan = 0; chan < FDDMA_NUM_OF_CHAN; chan++)
    {
        if (instance->bind_status & BIT(chan))
        {
            FDDMA_WARN("Channel %d is not yet unbound", chan);
        }
    }

    memset(instance, 0, sizeof(*instance));
    return;
}

/**
 * @name: FDdmaAllocateChan
 * @msg: 按照配置分配DDMA通道
 * @return {FError} FDDMA_SUCCESS表示分配成功，其它返回值表示分配失败
 * @param {FDdma} *instance, DDMA控制器实例
 * @param {FDdmaChan} *dma_chan, DDMA通道实例
 * @param {FDdmaChanConfig} *dma_chan_config, DDMA通道配置
 */
FError FDdmaAllocateChan(FDdma *const instance, FDdmaChan *const dma_chan, const FDdmaChanConfig *dma_chan_config)
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

    if ((FDDMA_MAX_TRANSFER_LEN < dma_chan_config->trans_len) ||
        (FDDMA_MIN_TRANSFER_LEN > dma_chan_config->trans_len) ||
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
    FDdmaSetChanSelection(base_addr, chan_idx, dma_chan->config.slave_id); /* select channel */
    FDdmaSetChanBind(base_addr, chan_idx, TRUE); /* bind channel */

    /* setup transfer src and dst */
    /*     dma_tx_req: ddr --> dev 从内存中读取数据，写入外设 */
    /*     dma_rx_req: dev --> ddr 从外设读取数据到内存 */
#ifdef __aarch64___
    FDdmaWriteReg(base_addr, FDDMA_CHAN_DDR_LOW_ADDR_OFFSET(chan_idx), LOWER_32_BITS(dma_chan_config->ddr_addr));
    FDdmaWriteReg(base_addr, FDDMA_CHAN_DDR_UP_ADDR_OFFSET(chan_idx), UPPER_32_BITS(dma_chan_config->ddr_addr));
#else
    FDdmaWriteReg(base_addr, FDDMA_CHAN_DDR_LOW_ADDR_OFFSET(chan_idx), (u32)(dma_chan_config->ddr_addr));
    FDdmaWriteReg(base_addr, FDDMA_CHAN_DDR_UP_ADDR_OFFSET(chan_idx), 0);
#endif

    FDdmaWriteReg(base_addr, FDDMA_CHAN_DEV_ADDR_OFFSET(chan_idx), dma_chan_config->dev_addr);
    FDdmaWriteReg(base_addr, FDDMA_CHAN_TS_OFFSET(chan_idx), dma_chan_config->trans_len); /* block size */

    /* set channel request direction */
    FDdmaSetChanDirection(base_addr, chan_idx,
                          (FDDMA_CHAN_REQ_RX == dma_chan->config.req_mode) ? TRUE : FALSE);

    FDDMA_INFO("channel-%d ddr @0x%x", chan_idx, FDDMA_CHAN_DDR_LOW_ADDR_OFFSET(chan_idx));
    FDDMA_INFO("ddr addr: 0x%x", FDdmaReadReg(base_addr, FDDMA_CHAN_DDR_LOW_ADDR_OFFSET(chan_idx)));
    FDDMA_INFO("dev addr: 0x%x", FDdmaReadReg(base_addr, FDDMA_CHAN_DEV_ADDR_OFFSET(chan_idx)));
    FDDMA_INFO("transfer len: %d", FDdmaReadReg(base_addr, FDDMA_CHAN_TS_OFFSET(chan_idx)));

    FDdmaSetChanTimeout(base_addr, chan_idx, 0xffff);
    FDdmaEnableChanIrq(base_addr, chan_idx);

    if (FDDMA_SUCCESS == ret)
    {
        instance->bind_status |= BIT(chan_idx);
        dma_chan->is_used = TRUE;
        FDDMA_INFO("Allocate channel %d", chan_idx);
    }

    return ret;
}

/**
 * @name: FDdmaDellocateChan
 * @msg: 释放之前分配的DDMA通道
 * @return {FError} FDDMA_SUCCESS表示释放成功，其它返回值表示释放失败
 * @param {FDdmaChan} *dma_chan, DDMA控制器实例
 */
FError FDdmaDellocateChan(FDdmaChan *const dma_chan)
{
    FASSERT(dma_chan && dma_chan->dma);
    FDdma *const instance = dma_chan->dma;
    const FDdmaChanIndex chan_idx = dma_chan->config.id;
    uintptr base_addr = instance->config.base_addr;
    FError ret = FDDMA_SUCCESS;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FDDMA_ERROR("The Dma instance is not initialized !!!");
        return FDDMA_ERR_NOT_INIT;
    }

    if (FDDMA_SUCCESS != FDdmaDisableChan(base_addr, chan_idx))
    {
        FDDMA_ERROR("Failed to disable DDMA@0x%x channel %d !!!", base_addr, chan_idx);
        return FDDMA_ERR_WAIT_TIMEOUT;
    }

    FDdmaResetChan(base_addr, chan_idx);

    FDdmaSetChanBind(base_addr, chan_idx, FALSE); /* unbind channel */
    ret = FDdmaDisableChan(base_addr, chan_idx);
    if (FDDMA_SUCCESS != ret) /* disable channel */
    {
        FDDMA_ERROR("Failure to disable ddma@%p channel %d !!!", base_addr, chan_idx);
        return ret;
    }

    FDdmaDisableChanIrq(base_addr, chan_idx); /* disable channel irq */

    instance->bind_status &= ~BIT(chan_idx); /* set bind status */
    instance->chan[chan_idx] = NULL;

    FDDMA_INFO("DeAllocate channels %d", chan_idx);
    memset(dma_chan, 0, sizeof(*dma_chan));

    return ret;
}

/**
 * @name: FDdmaActiveChan
 * @msg: 使能指定的DDMA通道
 * @note: 调用FDdmaAllocateChan后无需调用此函数
 * @return {FError} 返回FDDMA_SUCCESS表示成功，返回其它表示失败
 * @param FDdmaChan *const dma_chan, DDMA通道实例
 */
FError FDdmaActiveChan(FDdmaChan *const dma_chan)
{
    FASSERT(dma_chan && dma_chan->dma);
    FDdma *const instance = dma_chan->dma;
    uintptr base_addr = instance->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FDDMA_ERROR("The Dma instance is not initialized !!!");
        return FDDMA_ERR_NOT_INIT;
    }

    FDdmaEnableChan(base_addr, dma_chan->config.id);
    FDdmaClearChanIrq(base_addr, dma_chan->config.id);  /* clear interrupt status */
    return FDDMA_SUCCESS;
}

FError FDdmaDeactiveChan(FDdmaChan *const dma_chan)
{
    FASSERT(dma_chan && dma_chan->dma);
    FDdma *const instance = dma_chan->dma;
    uintptr base_addr = instance->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FDDMA_ERROR("The Dma instance is not initialized !!!");
        return FDDMA_ERR_NOT_INIT;
    }

    return FDdmaDisableChan(base_addr, dma_chan->config.id);
}

/**
 * @name: FDdmaReset
 * @msg: 重置DDMA控制器
 * @return {FError} FDDMA_SUCCESS表示重置成功，其它返回值表示失败
 * @param {FDdma} *instance, DDMA控制器实例
 */
static FError FDdmaReset(FDdma *const instance)
{
    FASSERT(instance);
    uintptr base_addr = instance->config.base_addr;
    FError ret = FDDMA_SUCCESS;
    u32 reg_val;
    u32 chan;

    if (0 != instance->bind_status)
    {
        FDDMA_WARN("Some channels are not yet unbound !!!");
    }

    FDdmaDisable(base_addr); /* disable ddma  */
    FDdmaSoftwareReset(base_addr); /* do software reset */
    FDdmaDisableGlobalIrq(base_addr);

    /* disable channel and its irq */
    for (u32 chan = FDDMA_CHAN_0; chan < FDDMA_NUM_OF_CHAN; chan++)
    {
        /* disable channel */
        ret = FDdmaDisableChan(base_addr, chan);
        if (FDDMA_SUCCESS != ret)
        {
            FDDMA_ERROR("Failure to disable ddma@%p channel %d !!!", base_addr, chan);
            break;
        }
    }

    FDdmaDumpRegisters(base_addr);

    return ret;
}