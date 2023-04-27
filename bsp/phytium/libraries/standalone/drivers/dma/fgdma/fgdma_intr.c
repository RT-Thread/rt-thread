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

#include "fdebug.h"
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

#define FGDMA_CALL_EVT_HANDLER(express, dma_chan, args) \
    do                                                  \
    {                                                   \
        if (express)                                    \
        {                                               \
            express(dma_chan, args);                    \
        }                                               \
    } while (0)

/************************** Function Prototypes ******************************/
/**
 * @name: FGdmaChanIrqHandler
 * @msg: GDMA通道中断处理函数
 * @return {void} 无
 * @param {FGdmaChan} *chan_p, GDMA通道实例
 */
static void FGdmaChanIrqHandler(FGdmaChan *const chan_p)
{
    FGdma *const instance_p = chan_p->gdma;
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 chan_status = FGdmaReadChanStatus(base_addr, chan_p->config.chan_id);

    if (FGDMA_CHX_INT_STATE_BUSY & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_p->evt_handlers[FGDMA_CHAN_EVT_BUSY],
                               chan_p, chan_p->evt_handler_args[FGDMA_CHAN_EVT_BUSY]);
    }

    if (FGDMA_CHX_INT_STATE_TRANS_END & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_p->evt_handlers[FGDMA_CHAN_EVT_TRANS_END],
                               chan_p, chan_p->evt_handler_args[FGDMA_CHAN_EVT_TRANS_END]);
    }

    if (FGDMA_CHX_INT_STATE_BDL_END & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_p->evt_handlers[FGDMA_CHAN_EVT_BDL_END],
                               chan_p, chan_p->evt_handler_args[FGDMA_CHAN_EVT_BDL_END]);
    }

    if (FGDMA_CHX_INT_STATE_FIFO_FULL & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_p->evt_handlers[FGDMA_CHAN_EVT_FIFO_FULL],
                               chan_p, chan_p->evt_handler_args[FGDMA_CHAN_EVT_FIFO_FULL]);
    }

    if (FGDMA_CHX_INT_STATE_FIFO_EMPTY & chan_status)
    {
        FGDMA_CALL_EVT_HANDLER(chan_p->evt_handlers[FGDMA_CHAN_EVT_FIFO_EMPTY],
                               chan_p, chan_p->evt_handler_args[FGDMA_CHAN_EVT_FIFO_EMPTY]);
    }

    FGdmaClearChanStatus(base_addr, chan_p->config.chan_id, chan_status);
    return;
}

/**
 * @name: FGdmaIrqHandler
 * @msg: 当instance_p->config.caps 具有FGDMA_IRQ1_MASK特性时,此函数作为GDMA中断处理函数
 * @return {void} 无
 * @param {s32} vector, 中断号
 * @param {void} *args, 中断参数
 */
void FGdmaIrqHandler(s32 vector, void *args)
{
    FASSERT(args);
    FGdma *const instance_p = (FGdma * const)args;
    FASSERT(FT_COMPONENT_IS_READY == instance_p->is_ready);
    FASSERT(FGDMA_IRQ1_MASK & instance_p->config.caps);
    uintptr base_addr = instance_p->config.base_addr;
    u32 chan_id;

    u32 status = FGdmaReadStatus(base_addr);
    FGDMA_INFO("status: 0x%x", status);

    FGdmaIrqDisable(base_addr);
    for (chan_id = 0; chan_id < FGDMA_NUM_OF_CHAN; chan_id++)
    {
        if (!(FGDMA_CHX_INTR_STATE(chan_id) & status)) 
        {
            continue;
        }

        /* channel interrupt happens */
        FASSERT_MSG((NULL != instance_p->chans[chan_id]), "invalid chan interrupt event !!!");
        FGdmaChanIrqHandler(instance_p->chans[chan_id]);
    }
    FGdmaIrqEnable(base_addr);
    status = FGdmaReadStatus(base_addr);
    FGDMA_INFO("after status: 0x%x", status);
    return;
}

/**
 * @name: FGdmaIrqHandlerPrivateChannel
 * @msg: 当instance_p->config.caps 具有FGDMA_IRQ2_MASK特性时,此函数作为GDMA中断处理函数
 * @return {void} 无
 * @param {s32} vector, 中断号
 * @param {void} *args, 中断参数
 */
void FGdmaIrqHandlerPrivateChannel(s32 vector, void *args)
{
    FASSERT(args);
    FGdmaChan *gdma_chan = (FGdmaChan *)args;
    FASSERT(gdma_chan);
    FGdma *const instance_p = (FGdma *const)gdma_chan->gdma;
    FASSERT(FT_COMPONENT_IS_READY == instance_p->is_ready);
    FASSERT(FGDMA_IRQ2_MASK & instance_p->config.caps);
    uintptr base_addr = instance_p->config.base_addr;
    u32 chan_id;
    FGDMA_INFO("FGdmaIrqHandlerPrivateChannel is here %d \r\n",vector);
    chan_id = gdma_chan->config.chan_id ;
    FASSERT(chan_id <= FGDMA_NUM_OF_CHAN);
    u32 status = FGdmaReadStatus(base_addr);
    FGDMA_INFO("status: 0x%x", status);
    if(!(FGDMA_CHX_INTR_STATE(chan_id) & status))
    {
        FGDMA_WARN("The interrupt state does not match the interrupt chan_id ,chan_id is %d, interrupt state is 0x%x ",chan_id,status);
    }
    
    FASSERT_MSG((NULL != instance_p->chans[chan_id]), "invalid chan interrupt event !!!");
    FGdmaChanIrqHandler(instance_p->chans[chan_id]);
    status = FGdmaReadStatus(base_addr);
    FGDMA_INFO("after status: 0x%x", status);
    return;
}


/**
 * @name: FGdmaChanRegisterEvtHandler
 * @msg: 注册GDMA通道事件回调函数
 * @return {void} 无
 * @param {FGdmaChan} *chan_p, GDMA通道实例
 * @param {FGdmaChanEvtType} evt, 通道事件
 * @param {FGdmaChanEvtHandler} handler, 事件回调函数
 * @param {void} *handler_arg, 事件回调函数输入参数
 */
void FGdmaChanRegisterEvtHandler(FGdmaChan *const chan_p, FGdmaChanEvtType evt,
                                 FGdmaChanEvtHandler handler, void *handler_arg)
{
    FASSERT(chan_p);
    FASSERT(FGDMA_CHAN_NUM_OF_EVT > evt);

    chan_p->evt_handlers[evt] = handler;
    chan_p->evt_handler_args[evt] = handler_arg;

    return;
}