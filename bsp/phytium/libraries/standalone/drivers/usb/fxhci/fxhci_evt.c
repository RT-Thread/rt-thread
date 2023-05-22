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
 * FilePath: fxhci_evt.c
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:13:09
 * Description:  This files is for implementation of XHCI event
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include "fsleep.h"
#include "fdebug.h"

#include "fxhci_private.h"

#define FUSB_DEBUG_TAG "FXHCI-EVT"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 * @name: FXhciResetEvtRing
 * @msg: 重置Event TRB ring
 * @return {*}
 * @param {FXhciEvtRing} *er, Event TRB ring实例
 */
void FXhciResetEvtRing(FXhciEvtRing *const er)
{
    int i;
    for (i = 0; i < FXHCI_EVENT_RING_SIZE; ++i)
    {
        er->ring[i].control &= ~FXHCI_TRB_CYCLE;
    }
    er->cur = er->ring;
    er->last = er->ring + FXHCI_EVENT_RING_SIZE;
    er->ccs = 1;
    er->adv = 1;
}

static inline int FXhciEvtReady(const FXhciEvtRing *const er)
{
    return (er->cur->control & FXHCI_TRB_CYCLE) == er->ccs;
}

void FXhciUpdateEvtDQ(FXhci *const xhci)
{
    if (xhci->er.adv)
    {
        FUSB_DEBUG("Updating dq ptr: @0x%lx -> %p.",
                   FXhciReadRt64(&xhci->mmio, 0, FXHCI_REG_RT_IR_ERDP),
                   xhci->er.cur);
        FXhciWriteRt64(&xhci->mmio, 0, FXHCI_REG_RT_IR_ERDP, FXHCI_REG_RT_IR_ERDP_MASK & ((u64)(uintptr)xhci->er.cur));
        xhci->er.adv = 0;
    }
}

void FXhciAdvanceEvtRing(FXhci *const xhci)
{
    xhci->er.cur++;
    xhci->er.adv = 1;
    if (xhci->er.cur == xhci->er.last)
    {
        FUSB_DEBUG("Roll over in event ring.");
        xhci->er.cur = xhci->er.ring;
        xhci->er.ccs ^= 1;
        FXhciUpdateEvtDQ(xhci);
    }
}

static void FXhciHandleTransferEvt(FXhci *const xhci)
{
    const FXhciTrb *const ev = xhci->er.cur;

    const FXhciTransCode cc = FXHCI_TRB_GET(CC, ev); /* Completion Code */
    const int id = FXHCI_TRB_GET(ID, ev);
    const int ep = FXHCI_TRB_GET(EP, ev);

    FXhciIntrQ *intrq;

    if (id && id <= xhci->max_slots_en &&
        (intrq = xhci->dev[id].interrupt_queues[ep]))
    {
        /* It's a running interrupt endpoint */
        intrq->ready = (void *)(uintptr)(ev->ptr_low);
        if (cc == FXHCI_CC_SUCCESS || cc == FXHCI_CC_SHORT_PACKET)
        {
            FXHCI_TRB_SET(TL, intrq->ready,
                          intrq->size - FXHCI_TRB_GET(EVTL, ev)); /* Transfer Length */
        }
        else
        {
            FUSB_INFO("Interrupt transfer failed: %d.", cc);
            FXHCI_TRB_SET(TL, intrq->ready, 0); /* Transfer Length */
        }
    }
    else if (cc == FXHCI_CC_STOPPED || cc == FXHCI_CC_STOPPED_LENGTH_INVALID)
    {
        /* Ignore 'Forced Stop Events' */
    }
    else
    {
        FUSB_WARN("Warning: \r\n"
                  "Spurious transfer event for ID %d, EP %d: \r\n"
                  "  Pointer: 0x%08x%08x \r\n"
                  "       TL: 0x%06x \r\n"
                  "       CC: %d ",
                  id, ep,
                  ev->ptr_high, ev->ptr_low,
                  FXHCI_TRB_GET(EVTL, ev), cc);
    }

    FXhciAdvanceEvtRing(xhci);
}

static void FXhciHandleCmdCompletionEvt(FXhci *const xhci)
{
    const FXhciTrb *const ev = xhci->er.cur;

    FUSB_INFO("Warning: Spurious command completion event: \r\n"
              "  Pointer: 0x%08x%08x \r\n"
              "       CC: %d \r\n"
              "  Slot ID: %d \r\n"
              "    Cycle: %d ",
              ev->ptr_high, ev->ptr_low,
              FXHCI_TRB_GET(CC, ev), FXHCI_TRB_GET(ID, ev), ev->control & FXHCI_TRB_CYCLE);
    FXhciAdvanceEvtRing(xhci);
}

static void FXhciHandleHostCtrlEvt(FXhci *const xhci)
{
    const FXhciTrb *const ev = xhci->er.cur;

    const FXhciTransCode cc = FXHCI_TRB_GET(CC, ev);
    switch (cc)
    {
        case FXHCI_CC_EVENT_RING_FULL_ERROR:
            FUSB_INFO("Event ring full! (@%p).", xhci->er.cur);
            /*
             * If we get here, we have processed the whole queue:
             * xHC pushes this event, when it sees the ring full,
             * full of other events.
             * IMO it's save and necessary to update the dequeue
             * pointer here.
             */
            FXhciAdvanceEvtRing(xhci);
            FXhciUpdateEvtDQ(xhci);
            break;
        default:
            FUSB_INFO("Warning: spurious host controller event: %d.", cc);
            FXhciAdvanceEvtRing(xhci);
            break;
    }
}

/* handle standard types:
 * - command completion event
 * - port status change event
 * - transfer event
 * - host controller event
 */
static void FXhciHandleEvt(FXhci *const xhci)
{
    const FXhciTrb *const ev = xhci->er.cur;

    const int trb_type = FXHCI_TRB_GET(TT, ev);
    switch (trb_type)
    {
        /* Either pass along the event or advance event ring */
        case FXHCI_TRB_EV_TRANSFER:
            FXhciHandleTransferEvt(xhci);
            break;
        case FXHCI_TRB_EV_CMD_CMPL:
            FXhciHandleCmdCompletionEvt(xhci);
            break;
        case FXHCI_TRB_EV_PORTSC:
            FUSB_INFO("Port status change event for %d: %d. ",
                      FXHCI_TRB_GET(PORT, ev), FXHCI_TRB_GET(CC, ev));
            /* We ignore the event as we look for the PORTSC
               registers instead, at a time when it suits _us_. */
            FXhciAdvanceEvtRing(xhci);
            break;
        case FXHCI_TRB_EV_HOST:
            FXhciHandleHostCtrlEvt(xhci);
            break;
        default:
            FUSB_INFO("Warning: spurious event: %d, completion code: %d.",
                      trb_type, FXHCI_TRB_GET(CC, ev));
            FXhciAdvanceEvtRing(xhci);
            break;
    }
}

void FXhciHandleEvts(FXhci *const xhci)
{
    while (FXhciEvtReady(&xhci->er))
    {
        FXhciHandleEvt(xhci);
    }

    FXhciUpdateEvtDQ(xhci);
    return;
}

static unsigned long FXhciWaitForEvt(const FXhciEvtRing *const er,
                                     unsigned long *const timeout_us)
{
    while (!FXhciEvtReady(er) && *timeout_us)
    {
        --*timeout_us;
        fsleep_microsec(1);
    }
    return *timeout_us;
}

static unsigned long FXhciWaitForEvtType(FXhci *const xhci,
        const int trb_type,
        unsigned long *const timeout_us)
{
    while (FXhciWaitForEvt(&xhci->er, timeout_us))
    {
        if (FXHCI_TRB_GET(TT, xhci->er.cur) == (unsigned int)trb_type)
        {
            break;
        }

        FXhciHandleEvt(xhci);
    }

    return *timeout_us;
}

/*
 * Ref. xHCI Specification Revision 1.2, May 2019.
 * Section 4.6.1.2.
 *
 * Process events from xHCI Abort command.
 *
 * Returns FXHCI_CC_COMMAND_RING_STOPPED on success and FXHCI_CC_TIMEOUT on failure.
 */

FXhciTransCode FXhciWaitForCmdAborted(FXhci *const xhci, const FXhciTrb *const address)
{
    /*
     * Specification says that something might be seriously wrong, if
     * we don't get a response after 5s. Still, let the caller decide,
     * what to do then.
     */
    unsigned long timeout_us = FUSB_USB_MAX_PROCESSING_TIME_US; /* 5s */
    FXhciTransCode cc = FXHCI_CC_TIMEOUT;
    /*
     * Expects two command completion events:
     * The first with CC == COMMAND_ABORTED should point to address
     * (not present if command was not running),
     * the second with CC == COMMAND_RING_STOPPED should point to new dq.
     */
    while (FXhciWaitForEvtType(xhci, FXHCI_TRB_EV_CMD_CMPL, &timeout_us))
    {
        if ((xhci->er.cur->ptr_low == (uintptr)(address)) &&
            (xhci->er.cur->ptr_high == 0))
        {
            cc = FXHCI_TRB_GET(CC, xhci->er.cur);
            FXhciAdvanceEvtRing(xhci);
            break;
        }

        FXhciHandleCmdCompletionEvt(xhci);
    }
    if (timeout_us == 0)
    {
        FUSB_INFO("Warning: timeout waiting COMMAND_ABORTED or COMMAND_RING_STOPPED.");
        goto update_and_return;
    }
    if (cc == FXHCI_CC_COMMAND_RING_STOPPED)
    {
        /* There may not have been a command to abort. */
        goto update_and_return;
    }

    timeout_us = FUSB_USB_MAX_PROCESSING_TIME_US; /* 5s */
    while (FXhciWaitForEvtType(xhci, FXHCI_TRB_EV_CMD_CMPL, &timeout_us))
    {
        if (FXHCI_TRB_GET(CC, xhci->er.cur) == FXHCI_CC_COMMAND_RING_STOPPED)
        {
            cc = FXHCI_CC_COMMAND_RING_STOPPED;
            FXhciAdvanceEvtRing(xhci);
            break;
        }

        FXhciHandleCmdCompletionEvt(xhci);
    }
    if (timeout_us == 0)
        FUSB_INFO("Warning: timeout waiting for COMMAND_RING_STOPPED.");

update_and_return:
    FXhciUpdateEvtDQ(xhci);
    return cc;
}

/*
 * returns cc of command in question (pointed to by `address`)
 * caller should abort command if cc is FXHCI_CC_TIMEOUT
 */
FXhciTransCode FXhciWaitForCmdDone(FXhci *const xhci,
                                   const FXhciTrb *const address,
                                   const int clear_event)
{
    unsigned long timeout_us = FUSB_USB_MAX_PROCESSING_TIME_US; /* 5s */
    FXhciTransCode cc = FXHCI_CC_TIMEOUT;

    while (FXhciWaitForEvtType(xhci, FXHCI_TRB_EV_CMD_CMPL, &timeout_us))
    {
        if ((xhci->er.cur->ptr_low == (uintptr)(address)) &&
            (xhci->er.cur->ptr_high == 0))
        {
            cc = FXHCI_TRB_GET(CC, xhci->er.cur);
            break;
        }

        FXhciHandleCmdCompletionEvt(xhci);
    }

    if (!timeout_us)
    {
        FUSB_INFO("Warning: timeout waiting for FXHCI_TRB_EV_CMD_CMPL.");
    }
    else if (clear_event)
    {
        FXhciAdvanceEvtRing(xhci);
    }

    FXhciUpdateEvtDQ(xhci);
    return cc;
}

/* returns amount of bytes transferred on success, negative CC on error */
FXhciTransCode FXhciWaitForTransfer(FXhci *const xhci, const int slot_id, const int ep_id)
{
    /* 5s for all types of transfers */
    unsigned long timeout_us = FUSB_USB_MAX_PROCESSING_TIME_US;
    FXhciTransCode ret = FXHCI_CC_TIMEOUT;
    while (FXhciWaitForEvtType(xhci, FXHCI_TRB_EV_TRANSFER, &timeout_us))
    {
        if (FXHCI_TRB_GET(ID, xhci->er.cur) == (unsigned int)slot_id &&
            FXHCI_TRB_GET(EP, xhci->er.cur) == (unsigned int)ep_id)
        {
            ret = -FXHCI_TRB_GET(CC, xhci->er.cur);
            if (ret == -FXHCI_CC_SUCCESS || ret == -FXHCI_CC_SHORT_PACKET)
            {
                ret = FXHCI_TRB_GET(EVTL, xhci->er.cur);
            }
            FXhciAdvanceEvtRing(xhci);
            break;
        }

        FXhciHandleTransferEvt(xhci);
    }
    if (!timeout_us)
    {
        FUSB_INFO("Warning: timeout waiting for FXHCI_TRB_EV_TRANSFER. ");
    }

    FXhciUpdateEvtDQ(xhci);
    return ret;
}
