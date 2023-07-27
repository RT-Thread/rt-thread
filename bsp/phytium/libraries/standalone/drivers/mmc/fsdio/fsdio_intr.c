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
 * FilePath: fsdio_intr.c
 * Date: 2022-06-01 15:08:58
 * LastEditTime: 2022-06-01 15:08:58
 * Description:  This file is for SDIO interrupt related function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 */
/***************************** Include Files *********************************/

#include "fio.h"
#include "fdebug.h"
#include "fassert.h"
#include "ftypes.h"

#include "fsdio_hw.h"
#include "fsdio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIO_DEBUG_TAG "FSDIO-INTR"
#define FSDIO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)

#define FSDIO_CALL_EVT_HANDLER(instance_p, evt, status, dmac_status)                   \
    if (instance_p->evt_handlers[evt])                            \
    {                                                             \
        instance_p->evt_handlers[evt](instance_p, instance_p->evt_args[evt], status, dmac_status); \
    }

static const u32 cmd_err_ints_mask = FSDIO_INT_RTO_BIT | FSDIO_INT_RCRC_BIT | FSDIO_INT_RE_BIT |
                                     FSDIO_INT_DCRC_BIT | FSDIO_INT_DRTO_BIT |
                                     FSDIO_INT_SBE_BCI_BIT;

static const u32 dmac_err_ints_mask = FSDIO_DMAC_INT_ENA_FBE | FSDIO_DMAC_INT_ENA_DU |
                                      FSDIO_DMAC_INT_ENA_NIS | FSDIO_DMAC_INT_ENA_AIS;
/************************** Function Prototypes ******************************/

/*****************************************************************************/

/**
 * @name: FSdioGetInterruptMask
 * @msg: Get SDIO controller interrupt mask
 * @return {u32} interrupt mask bits
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioIntrType} type, Type of interrupt, controller/DMA interrupt
 */
u32 FSdioGetInterruptMask(FSdio *const instance_p, FSdioIntrType type)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 mask = 0U;

    if (0 == instance_p->config.base_addr)
    {
        FSDIO_ERROR("Device is not yet initialized!!!");
        return mask;
    }

    if (FSDIO_GENERAL_INTR == type)
    {
        mask = FSDIO_READ_REG(base_addr, FSDIO_INT_MASK_OFFSET);
    }
    else
    {
        mask = FSDIO_READ_REG(base_addr, FSDIO_DMAC_INT_EN_OFFSET);
    }

    return mask;
}

/**
 * @name: FSdioSetInterruptMask
 * @msg: Enable/Disable SDIO controller interrupt
 * @return {NONE}
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioIntrType} type, Type of interrupt, controller/DMA interrupt
 * @param {u32} set_mask, interrupt mask bits
 * @param {boolean} enable, TRUE: enable interrupt mask bits
 */
void FSdioSetInterruptMask(FSdio *const instance_p, FSdioIntrType type, u32 set_mask, boolean enable)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 mask = 0U;

    if (0 == instance_p->config.base_addr)
    {
        FSDIO_ERROR("Device is not yet initialized!!!");
        return;
    }

    mask = FSdioGetInterruptMask(instance_p, type);

    if (TRUE == enable)
    {
        mask |= set_mask;
    }
    else
    {
        mask &= ~set_mask;
    }

    if (FSDIO_GENERAL_INTR == type)
    {
        FSDIO_WRITE_REG(base_addr, FSDIO_INT_MASK_OFFSET, mask);
    }
    else
    {
        FSDIO_WRITE_REG(base_addr, FSDIO_DMAC_INT_EN_OFFSET, mask);
    }

    return;
}

/**
 * @name: FSdioInterruptHandler
 * @msg: Interrupt handler for SDIO instance
 * @return {NONE}
 * @param {s32} vector, Interrupt id
 * @param {void} *param, Interrupt params, is SDIO instance
 */
void FSdioInterruptHandler(s32 vector, void *param)
{
    FASSERT(param);
    FSdio *const instance_p = (FSdio * const)param;
    uintptr base_addr = instance_p->config.base_addr;
    u32 events, event_mask, dmac_events, dmac_evt_mask;

    events = FSDIO_READ_REG(base_addr, FSDIO_RAW_INTS_OFFSET);
    dmac_events = FSDIO_READ_REG(base_addr, FSDIO_DMAC_STATUS_OFFSET);
    event_mask = FSDIO_READ_REG(base_addr, FSDIO_INT_MASK_OFFSET);
    dmac_evt_mask = FSDIO_READ_REG(base_addr, FSDIO_DMAC_INT_EN_OFFSET);

    if (!(events & FSDIO_INT_ALL_BITS) &&
        !(dmac_events & FSDIO_DMAC_STATUS_ALL_BITS))
    {
        FSDIO_DEBUG("irq exit with no action.");
        return; /* no interrupt status */
    }

    FSDIO_WRITE_REG(base_addr, 0xfd0U, 0U);

    FSDIO_DEBUG("events:0x%x,mask:0x%x,dmac_events:%x,dmac_mask:0x%x", events, event_mask, dmac_events, dmac_evt_mask);

    /* clear interrupt status */
    FSDIO_WRITE_REG(base_addr, FSDIO_RAW_INTS_OFFSET, events);
    FSDIO_WRITE_REG(base_addr, FSDIO_DMAC_STATUS_OFFSET, dmac_events);

    if (((events & event_mask) == 0) &&
        (((dmac_events & dmac_evt_mask) == 0)))
    {
        return; /* no need to handle interrupt */
    }

    /* handle card detect event */
    if (((events & event_mask) & FSDIO_INT_CD_BIT) && (FALSE == instance_p->config.non_removable))
    {
        FSDIO_DEBUG("sd status changed here ! status:[%d]", FSDIO_READ_REG(base_addr, FSDIO_CARD_DETECT_OFFSET));
        FSDIO_CALL_EVT_HANDLER(instance_p, FSDIO_EVT_CARD_DETECTED, events, dmac_events);
    }

    /* handle error state */
    if ((dmac_events & dmac_err_ints_mask) || (events & cmd_err_ints_mask))
    {
        FSDIO_ERROR("ERR:events:0x%x,mask:0x%x,dmac_evts:0x%x,dmac_mask:0x%x",
                    events, event_mask, dmac_events, dmac_evt_mask);
        FSDIO_CALL_EVT_HANDLER(instance_p, FSDIO_EVT_ERR_OCCURE, events, dmac_events);
    }

    if ((events & FSDIO_INT_DTO_BIT) && (events & FSDIO_INT_CMD_BIT)) /* handle cmd && data done */
    {
        FSDIO_DEBUG("Cmd and data over !!!");
        FSDIO_CALL_EVT_HANDLER(instance_p, FSDIO_EVT_CMD_DONE, events, dmac_events);
        FSDIO_CALL_EVT_HANDLER(instance_p, FSDIO_EVT_DATA_DONE, events, dmac_events);
    }
    else if (events & FSDIO_INT_CMD_BIT) /* handle cmd done */
    {
        FSDIO_DEBUG("Cmd over !!!");
        FSDIO_CALL_EVT_HANDLER(instance_p, FSDIO_EVT_CMD_DONE, events, dmac_events);
    }
    else if (events & FSDIO_INT_DTO_BIT) /* handle data done */
    {
        FSDIO_DEBUG("Data over !!!");
        FSDIO_CALL_EVT_HANDLER(instance_p, FSDIO_EVT_DATA_DONE, events, dmac_events);
    }

    return;
}

/**
 * @name: FSdioRegisterEvtHandler
 * @msg: Register event call-back function as handler for interrupt events
 * @return {NONE}
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioEvtType} evt, interrupt event
 * @param {FSdioEvtHandler} handler, event call-back function
 * @param {void} *handler_arg, argument of event call-back function
 */
void FSdioRegisterEvtHandler(FSdio *const instance_p, FSdioEvtType evt, FSdioEvtHandler handler, void *handler_arg)
{
    FASSERT(instance_p);

    instance_p->evt_handlers[evt] = handler;
    instance_p->evt_args[evt] = handler_arg;
}