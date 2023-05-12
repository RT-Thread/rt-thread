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
 * FilePath: fddma_intr.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:47
 * Description:  This file is for ddma interrupt implementation
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
#define FDDMA_DEBUG_TAG "DDMA-INTR"
#define FDDMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_WARN(format, ...)   FT_DEBUG_PRINT_W(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FDDMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FDDMA_DEBUG_TAG, format, ##__VA_ARGS__)

#define FDDMA_CALL_EVT_HANDLER(express, dma_chan, args) \
    if (express)                                       \
    {                                                  \
        express(dma_chan, args);                       \
    }

/************************** Function Prototypes ******************************/

/****************************************************************************/
/**
 * @name: FDdmaChanIrqHandler
 * @msg: DDMA通道中断处理函数
 * @return {*}
 * @param {FDdma} *instance, DDMA实例
 * @param {FDdmaChanIndex} chan_idx, DDMA通道号
 */
static void FDdmaChanIrqHandler(FDdma *const instance, FDdmaChanIndex chan_idx)
{
    FASSERT(instance && instance->chan[chan_idx]);
    FDdmaChan *const dma_chan = instance->chan[chan_idx];
    uintptr base_addr = instance->config.base_addr;
    u32 status = FDdmaReadChanStatus(base_addr, chan_idx);

    FDDMA_INFO("chan-%d irq status: 0x%x", chan_idx, status);

    FDDMA_CALL_EVT_HANDLER(dma_chan->evt_handler[FDDMA_CHAN_EVT_REQ_DONE], dma_chan,
                           dma_chan->evt_handler_args[FDDMA_CHAN_EVT_REQ_DONE]);

    if (FDDMA_CHAN_STS_FIFO_EMPTY & status)
    {
        FDDMA_CALL_EVT_HANDLER(dma_chan->evt_handler[FDDMA_CHAN_EVT_FIFO_EMPTY], dma_chan,
                               dma_chan->evt_handler_args[FDDMA_CHAN_EVT_FIFO_EMPTY]);
    }

    if (FDDMA_CHAN_STS_FIFO_FULL & status)
    {
        FDDMA_CALL_EVT_HANDLER(dma_chan->evt_handler[FDDMA_CHAN_EVT_FIFO_FULL], dma_chan,
                               dma_chan->evt_handler_args[FDDMA_CHAN_EVT_FIFO_FULL]);
    }

    /* submit queued descriptor after processing the completed ones */
    return;
}

/**
 * @name: FDdmaIrqHandler
 * @msg: DDMA中断处理函数
 * @return {无}
 * @param {s32} vector
 * @param {void} *param, 输入参数
 */
void FDdmaIrqHandler(s32 vector, void *args)
{
    FASSERT(NULL != args);
    FDdma *const instance = (FDdma * const)args;
    uintptr base_addr = instance->config.base_addr;
    u32 status = FDdmaReadStatus(base_addr);
    u32 chan;

    FDDMA_INFO("ddma irq 0x%x", status);
    FDdmaDisableGlobalIrq(base_addr); /* disable interrupt from occur again */

    /* poll, clear and process every chanel interrupt status */
    for (chan = FDDMA_CHAN_0; chan < FDDMA_NUM_OF_CHAN; chan++)
    {
        if (0 == (FDDMA_STA_CHAN_REQ_DONE(chan) & status))
        {
            continue;
        }

        FDDMA_INFO("handle chan %d", chan);
        FDdmaClearChanIrq(base_addr, chan);  /* clear interrupt status */
        FDdmaChanIrqHandler(instance, chan); /* channel interrupt handle */
    }

    FDdmaEnableGlobalIrq(base_addr); /* re-enable interrupt */
    return;
}

/**
 * @name: FDdmaRegisterChanEvtHandler
 * @msg: 注册DDMA通道中断响应事件函数
 * @return {无}
 * @param {FDdmaChan} *dma_chan, DDMA通道
 * @param {FDdmaChanEvt} evt, 中断事件
 * @param {FDdmaChanEvtHandler} handler, 中断响应事件函数
 * @param {void} *handler_arg, 中断响应事件函数输入参数
 */
void FDdmaRegisterChanEvtHandler(FDdmaChan *const dma_chan, FDdmaChanEvt evt, FDdmaChanEvtHandler handler, void *handler_arg)
{
    FASSERT(dma_chan);
    dma_chan->evt_handler[evt] = handler;
    dma_chan->evt_handler_args[evt] = handler_arg;
    return;
}