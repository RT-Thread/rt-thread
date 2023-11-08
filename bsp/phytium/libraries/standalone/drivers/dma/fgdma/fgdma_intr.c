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
 * FilePath: fgdma_intr.c
 * Date: 2022-05-16 17:01:48
 * LastEditTime: 2022-05-16 17:01:49
 * Description:  This file is for interrupt api implmentation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/11/5    init commit
 * 1.1   zhugengyu  2022/5/16    modify according to tech manual.
 */

/***************************** Include Files *********************************/
#include <string.h>

#include "fdrivers_port.h"
#include "fassert.h"

#include "fgdma_hw.h"
#include "fgdma.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGDMA_DEBUG_TAG "GDMA-INTR"
#define FGDMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_WARN(format, ...)    FT_DEBUG_PRINT_W(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGDMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FGDMA_DEBUG_TAG, format, ##__VA_ARGS__)

#define FGDMA_CALL_EVT_HANDLER(express, chan_irq_info_p, args) \
    do                                                  \
    {                                                   \
        if (express)                                    \
        {                                               \
            express(chan_irq_info_p, args);             \
        }                                               \
    } while (0)
/************************** Function Prototypes ******************************/
/**
 * @name FGdmaChanIrqHandler
 * @msg: GDMA通道中断处理函数
 * @return {void} 无
 * @param FGdmaChanIrq *const chan_irq_info_p 通道中断回调信息
 */
static void FGdmaChanIrqHandler(FGdmaChanIrq *const chan_irq_info_p)
{
    FASSERT(chan_irq_info_p);

    FGdmaChanIndex channel_id = chan_irq_info_p->chan_id;
    FGdma *instance_p = chan_irq_info_p->gdma_instance;
    uintptr base_addr = instance_p->config.base_addr;

    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);

    if (!(instance_p->chan_ready_flag & BIT(channel_id)))
        return;

    u32 chan_status = FGdmaReadChanStatus(base_addr, channel_id);
    FGDMA_INFO("DMA_Cx_STATE(0x2C): 0x%x", chan_status);
    if (FGDMA_CHX_INT_STATE_BUSY & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_irq_info_p->evt_handlers[FGDMA_CHAN_EVT_BUSY],
                               chan_irq_info_p, 
                               chan_irq_info_p->evt_handler_args[FGDMA_CHAN_EVT_BUSY]);
    }

    if (FGDMA_CHX_INT_STATE_TRANS_END & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_irq_info_p->evt_handlers[FGDMA_CHAN_EVT_TRANS_END],
                               chan_irq_info_p, 
                               chan_irq_info_p->evt_handler_args[FGDMA_CHAN_EVT_TRANS_END]);
    }

    if (FGDMA_CHX_INT_STATE_BDL_END & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_irq_info_p->evt_handlers[FGDMA_CHAN_EVT_BDL_END],
                               chan_irq_info_p, 
                               chan_irq_info_p->evt_handler_args[FGDMA_CHAN_EVT_BDL_END]);
    }

    if (FGDMA_CHX_INT_STATE_FIFO_FULL & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_irq_info_p->evt_handlers[FGDMA_CHAN_EVT_FIFO_FULL],
                               chan_irq_info_p, 
                               chan_irq_info_p->evt_handler_args[FGDMA_CHAN_EVT_FIFO_FULL]);
    }

    if (FGDMA_CHX_INT_STATE_FIFO_EMPTY & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_irq_info_p->evt_handlers[FGDMA_CHAN_EVT_FIFO_EMPTY],
                               chan_irq_info_p, 
                               chan_irq_info_p->evt_handler_args[FGDMA_CHAN_EVT_FIFO_EMPTY]);
    }

    FGdmaClearChanStatus(base_addr, channel_id, chan_status);
    
    chan_status = FGdmaReadChanStatus(base_addr, channel_id);
    FGDMA_INFO("After clear, DMA_Cx_STATE(0x2C): 0x%x", chan_status);
    return;
}

/**
 * @name: FGdmaIrqHandler
 * @msg: 当instance_p->caps 具有FGDMA_IRQ1_MASK特性即共享中断时,此函数作为GDMA中断处理函数
 * @return {void} 无
 * @param {s32} vector, 中断号
 * @param {void} *args, 中断参数
 */
void FGdmaIrqHandler(s32 vector, void *args)
{
    FASSERT(args);
    
    FGdma *const instance_p = (FGdma * const)args;
    uintptr base_addr = instance_p->config.base_addr;

    u32 status = FGdmaReadStatus(base_addr);
    FGDMA_INFO("DMA_STATE(0x04): 0x%x", status);

    FGdmaIrqDisable(base_addr);
    for (fsize_t chan_id = 0; chan_id < FGDMA_NUM_OF_CHAN; chan_id++)
    {
        if (!(instance_p->chan_ready_flag & BIT(chan_id)) || !(status & FGDMA_CHX_INTR_STATE(chan_id))) /* if chan not init or no intr come in, directly return */
            continue;

        FGdmaChanIrqHandler(&instance_p->chan_irq_info[chan_id]); /* if channel interrupt happens, go irq handler */
    }
    FGdmaIrqEnable(base_addr);

    status = FGdmaReadStatus(base_addr);
    FGDMA_INFO("After irq handler DMA_STATE(0x04): 0x%x", status);
    return;
}

/**
 * @name FGdmaIrqHandlerPrivateChannel
 * @msg: 当instance_p->caps具有FGDMA_IRQ2_MASK特性时，此函数作为GDMA中断处理函数
 * @return {void} 无
 * @param {s32} vector 中断号
 * @param {void} *args 中断参数
 */
void FGdmaIrqHandlerPrivateChannel(s32 vector, void *args)
{
    FASSERT(args);

    FGdmaChanIrq *chan_irq_info_p = (FGdmaChanIrq *)args;
    FGdmaChanIndex channel_id = chan_irq_info_p->chan_id;
    FGdma *instance_p = chan_irq_info_p->gdma_instance;

    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);
    
    if (!(instance_p->chan_ready_flag & BIT(channel_id)))
        return;

    u32 status = FGdmaReadStatus(instance_p->config.base_addr);
    FGDMA_INFO("FGdmaIrqHandlerPrivateChannel is here %d \r\n", vector);
    FGDMA_INFO("DMA_STATE(0x04): 0x%x", status);

    if(!(FGDMA_CHX_INTR_STATE(channel_id) & status))
    {
        FGDMA_WARN("The interrupt state does not match the interrupt chan_id, chan_id: %d, interrupt state: 0x%x ",channel_id, status);
    }

    FGdmaChanIrqHandler(chan_irq_info_p);

    status = FGdmaReadStatus(instance_p->config.base_addr);
    FGDMA_INFO("After FGdmaIrqHandlerPrivateChannel() => DMA_STATE(0x04): 0x%x", status);

    return;
}

/**
 * @name: FGdmaChanRegisterEvtHandler
 * @msg: 注册GDMA通道事件回调函数
 * @return {void} 无
 * @param FGdma *const instance_p GDMA控制器实例
 * @param FGdmaChanIndex channel_id 事件产生的GDMA通道的通道号
 * @param FGdmaChanEvtType evt, 通道事件
 * @param FGdmaChanEvtHandler handler, 事件回调函数
 * @param void *handler_arg, 事件回调函数输入参数
 */
void FGdmaChanRegisterEvtHandler(FGdma *const instance_p,
                                 FGdmaChanIndex channel_id,
                                 FGdmaChanEvtType evt,
                                 FGdmaChanEvtHandler handler, 
                                 void *handler_arg)
{
    FASSERT(instance_p);
    FASSERT(channel_id < FGDMA_NUM_OF_CHAN);
    FASSERT(evt < FGDMA_CHAN_NUM_OF_EVT);

    instance_p->chan_irq_info[channel_id].evt_handlers[evt] = handler;
    instance_p->chan_irq_info[channel_id].evt_handler_args[evt] = handler_arg;

    return;
}