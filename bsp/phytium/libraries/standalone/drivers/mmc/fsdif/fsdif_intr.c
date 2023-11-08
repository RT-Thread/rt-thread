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
 * FilePath: fsdif_intr.c
 * Date: 2022-06-01 15:08:58
 * LastEditTime: 2022-06-01 15:08:58
 * Description:  This file is for sdif interrupt related function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 * 2.0   zhugengyu  2023/9/16    rename as sdif, support SD 3.0 and rework clock timing
 * 2.1   zhugengyu  2023/10/23   add sdio interrupt handler
 */
/***************************** Include Files *********************************/

#include "fio.h"
#include "fdrivers_port.h"
#include "fassert.h"
#include "ftypes.h"

#include "fsdif_hw.h"
#include "fsdif.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIF_DEBUG_TAG "FSDIF-INTR"
#define FSDIF_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)

#define FSDIF_CALL_EVT_HANDLER(instance_p, evt, status, dmac_status)                   \
    if (instance_p->evt_handlers[evt])                            \
    {                                                             \
        instance_p->evt_handlers[evt](instance_p, instance_p->evt_args[evt], status, dmac_status); \
    }

static const u32 cmd_err_ints_mask = FSDIF_INT_RTO_BIT | FSDIF_INT_RCRC_BIT | FSDIF_INT_RE_BIT |
                                     FSDIF_INT_DCRC_BIT | FSDIF_INT_DRTO_BIT |
                                     FSDIF_INT_SBE_BCI_BIT;

static const u32 dmac_err_ints_mask = FSDIF_DMAC_INT_ENA_FBE | FSDIF_DMAC_INT_ENA_DU |
                                      FSDIF_DMAC_INT_ENA_NIS | FSDIF_DMAC_INT_ENA_AIS;
/************************** Function Prototypes ******************************/

/*****************************************************************************/

/**
 * @name: FSdifGetInterruptMask
 * @msg: Get SDIF controller interrupt mask
 * @return {u32} interrupt mask bits
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifIntrType} type, Type of interrupt, controller/DMA interrupt
 */
u32 FSdifGetInterruptMask(FSdif *const instance_p, FSdifIntrType type)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 mask = 0U;

    if (0 == instance_p->config.base_addr)
    {
        FSDIF_ERROR("Device is not yet initialized!!!");
        return mask;
    }

    if (FSDIF_GENERAL_INTR == type)
    {
        mask = FSDIF_READ_REG(base_addr, FSDIF_INT_MASK_OFFSET);
    }
    else
    {
        mask = FSDIF_READ_REG(base_addr, FSDIF_DMAC_INT_EN_OFFSET);
    }

    return mask;
}

/**
 * @name: FSdifSetInterruptMask
 * @msg: Enable/Disable SDIF controller interrupt
 * @return {NONE}
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifIntrType} type, Type of interrupt, controller/DMA interrupt
 * @param {u32} set_mask, interrupt mask bits, refer to FSDIF_INT_XXX or FSDIF_DMAC_INT_XXX
 * @param {boolean} enable, TRUE: enable interrupt mask bits
 */
void FSdifSetInterruptMask(FSdif *const instance_p, FSdifIntrType type, u32 set_mask, boolean enable)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 mask = 0U;

    if (0 == instance_p->config.base_addr)
    {
        FSDIF_ERROR("Device is not yet initialized!!!");
        return;
    }

    mask = FSdifGetInterruptMask(instance_p, type);

    if (TRUE == enable)
    {
        mask |= set_mask;
    }
    else
    {
        mask &= ~set_mask;
    }

    if (FSDIF_GENERAL_INTR == type)
    {
        FSDIF_WRITE_REG(base_addr, FSDIF_INT_MASK_OFFSET, mask);
    }
    else
    {
        FSDIF_WRITE_REG(base_addr, FSDIF_DMAC_INT_EN_OFFSET, mask);
    }

    return;
}

/**
 * @name: FSdifInterruptHandler
 * @msg: Interrupt handler for SDIF instance
 * @return {NONE}
 * @param {s32} vector, Interrupt id
 * @param {void} *param, Interrupt params, is SDIF instance
 */
void FSdifInterruptHandler(s32 vector, void *param)
{
    FASSERT(param);
    FSdif *const instance_p = (FSdif * const)param;
    uintptr base_addr = instance_p->config.base_addr;
    u32 events, event_mask, dmac_events, dmac_evt_mask;

    events = FSDIF_READ_REG(base_addr, FSDIF_RAW_INTS_OFFSET);
    dmac_events = FSDIF_READ_REG(base_addr, FSDIF_DMAC_STATUS_OFFSET);
    event_mask = FSDIF_READ_REG(base_addr, FSDIF_INT_MASK_OFFSET);
    dmac_evt_mask = FSDIF_READ_REG(base_addr, FSDIF_DMAC_INT_EN_OFFSET);

    if (!(events & FSDIF_INT_ALL_BITS) &&
        !(dmac_events & FSDIF_DMAC_STATUS_ALL_BITS))
    {
        FSDIF_DEBUG("irq exit with no action.");
        return; /* no interrupt status */
    }

    FSDIF_WRITE_REG(base_addr, 0xfd0U, 0U);

    if ((!events) && (!(dmac_events & 0x1fff)))
    {
        return; /* no need to handle interrupt */
    }

    FSDIF_DEBUG("events:0x%x,mask:0x%x,dmac_events:%x,dmac_mask:0x%x", events, event_mask, dmac_events, dmac_evt_mask);

    /* clear interrupt status */
    FSDIF_WRITE_REG(base_addr, FSDIF_RAW_INTS_OFFSET, events);
    FSDIF_WRITE_REG(base_addr, FSDIF_DMAC_STATUS_OFFSET, dmac_events);

    /* handle sdio irq */
    if ((events & event_mask) & FSDIF_INT_SDIO_BIT)
    {
        FSDIF_DEBUG("SDIO interrupt here !");
        FSDIF_CALL_EVT_HANDLER(instance_p, FSDIF_EVT_SDIO_IRQ, events, dmac_events);
    }

    /* handle card detect event */
    if (((events & event_mask) & FSDIF_INT_CD_BIT) && (FALSE == instance_p->config.non_removable))
    {
        FSDIF_DEBUG("SD status changed here ! status:[%d]", FSDIF_READ_REG(base_addr, FSDIF_CARD_DETECT_OFFSET));
        FSDIF_CALL_EVT_HANDLER(instance_p, FSDIF_EVT_CARD_DETECTED, events, dmac_events);
    }

    /* handle error state */
    if ((dmac_events & dmac_err_ints_mask) || (events & cmd_err_ints_mask))
    {
        FSDIF_ERROR("Cmd@0x%x, index:%d, arg: 0x%x", instance_p->cur_cmd,
                    instance_p->cur_cmd ? instance_p->cur_cmd->cmdidx : -1,
                    instance_p->cur_cmd ? instance_p->cur_cmd->cmdarg : 0);
        FSDIF_ERROR("ERR:events:0x%x,mask:0x%x,dmac_evts:0x%x,dmac_mask:0x%x",
                    events, event_mask, dmac_events, dmac_evt_mask);
        FSDIF_CALL_EVT_HANDLER(instance_p, FSDIF_EVT_ERR_OCCURE, events, dmac_events);
    }

    if ((events & FSDIF_INT_DTO_BIT) && (events & FSDIF_INT_CMD_BIT)) /* handle cmd && data done */
    {
        FSDIF_DEBUG("Cmd and data over !!!");
        FSDIF_CALL_EVT_HANDLER(instance_p, FSDIF_EVT_CMD_DONE, events, dmac_events);
        FSDIF_CALL_EVT_HANDLER(instance_p, FSDIF_EVT_DATA_DONE, events, dmac_events);
    }
    else if ((events & FSDIF_INT_CMD_BIT) ||
             ((events & FSDIF_INT_HTO_BIT) && (FSDIF_SWITCH_VOLTAGE == instance_p->cur_cmd->cmdidx))) /* handle cmd done */
    {
        FSDIF_DEBUG("Cmd over !!!");
        FSDIF_CALL_EVT_HANDLER(instance_p, FSDIF_EVT_CMD_DONE, events, dmac_events);
    }
    else if (events & FSDIF_INT_DTO_BIT) /* handle data done */
    {
        FSDIF_DEBUG("Data over !!!");
        FSDIF_CALL_EVT_HANDLER(instance_p, FSDIF_EVT_DATA_DONE, events, dmac_events);
    }

    return;
}

/**
 * @name: FSdifRegisterEvtHandler
 * @msg: Register event call-back function as handler for interrupt events
 * @return {NONE}
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifEvtType} evt, interrupt event
 * @param {FSdifEvtHandler} handler, event call-back function
 * @param {void} *handler_arg, argument of event call-back function
 */
void FSdifRegisterEvtHandler(FSdif *const instance_p, FSdifEvtType evt, FSdifEvtHandler handler, void *handler_arg)
{
    FASSERT(instance_p);

    instance_p->evt_handlers[evt] = handler;
    instance_p->evt_args[evt] = handler_arg;
}
