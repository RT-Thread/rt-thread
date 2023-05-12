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
 * FilePath: fxhci_debug.c
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:12:15
 * Description:  This files is for implementation of XHCI debug utilities
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include <inttypes.h>
#include "fdebug.h"
#include "fxhci_private.h"

#define FUSB_DEBUG_TAG "FXHCI_DEBUG"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

void FXhciDumpSlotCtx(const FXhciSlotCtx *const sc)
{
    FUSB_INFO("Slot Context (@%p): ", sc);
    FUSB_INFO(" FIELD1\t0x%08x ", sc->f1);
    FUSB_INFO(" FIELD2\t0x%08x ", sc->f2);
    FUSB_INFO(" FIELD3\t0x%08x ", sc->f3);
    FUSB_INFO(" FIELD4\t0x%08x ", sc->f4);
    FXHCI_SC_DUMP(FUSB_INFO, ROUTE, sc);
    FXHCI_SC_DUMP(FUSB_INFO, SPEED1, sc);
    FXHCI_SC_DUMP(FUSB_INFO, MTT, sc);
    FXHCI_SC_DUMP(FUSB_INFO, HUB, sc);
    FXHCI_SC_DUMP(FUSB_INFO, CTXENT, sc);
    FXHCI_SC_DUMP(FUSB_INFO, RHPORT, sc);
    FXHCI_SC_DUMP(FUSB_INFO, NPORTS, sc);
    FXHCI_SC_DUMP(FUSB_INFO, TTID, sc);
    FXHCI_SC_DUMP(FUSB_INFO, TTPORT, sc);
    FXHCI_SC_DUMP(FUSB_INFO, TTT, sc);
    FXHCI_SC_DUMP(FUSB_INFO, UADDR, sc);
    FXHCI_SC_DUMP(FUSB_INFO, STATE, sc);
}

void FXhciDumpEpCtx(const FXhciEpCtx *const ec)
{
    FUSB_INFO("Endpoint Context (@%p): ", ec);
    FUSB_INFO(" FIELD1\t0x%08x ", ec->f1);
    FUSB_INFO(" FIELD2\t0x%08x ", ec->f2);
    FUSB_INFO(" TRDQ_L\t0x%08x ", ec->tr_dq_low);
    FUSB_INFO(" TRDQ_H\t0x%08x ", ec->tr_dq_high);
    FUSB_INFO(" FIELD5\t0x%08x ", ec->f5);
    FXHCI_EC_DUMP(FUSB_INFO, STATE, ec);
    FXHCI_EC_DUMP(FUSB_INFO, INTVAL, ec);
    FXHCI_EC_DUMP(FUSB_INFO, CERR, ec);
    FXHCI_EC_DUMP(FUSB_INFO, TYPE, ec);
    FXHCI_EC_DUMP(FUSB_INFO, MBS, ec);
    FXHCI_EC_DUMP(FUSB_INFO, MPS, ec);
    FXHCI_EC_DUMP(FUSB_INFO, DCS, ec);
    FXHCI_EC_DUMP(FUSB_INFO, AVRTRB, ec);
    FXHCI_EC_DUMP(FUSB_INFO, MXESIT, ec);
}

void FXhciDumpDevCtx(const FXhciDevCtx *const dc, const u32 ctx_mask)
{
    unsigned int i;

    if (ctx_mask & 1)
    {
        FXhciDumpSlotCtx(dc->slot);
    }

    for (i = 1; i <= FXHCI_SC_GET(CTXENT, dc->slot); ++i)
    {
        if (ctx_mask & (1 << i))
        {
            FXhciDumpEpCtx(dc->ep[i]);
        }
    }
}

void FXhciDumpInputCtx(const FXhciInputCtx *const ic)
{
    FUSB_INFO("Input Control  add: 0x%08x ", *ic->add);
    FUSB_INFO("Input Control drop: 0x%08x ", *ic->drop);
    FXhciDumpDevCtx(&ic->dev, *ic->add);
}

void FXhciDumpTransferTrb(const FXhciTrb *const cur)
{
    FUSB_INFO("Transfer TRB (@%p): ", cur);
    FUSB_INFO(" PTR_L\t0x%08x ", cur->ptr_low);
    FUSB_INFO(" PTR_H\t0x%08x ", cur->ptr_high);
    FUSB_INFO(" STATUS\t0x%08x ", cur->status);
    FUSB_INFO(" CNTRL\t0x%08x ", cur->control);
    FXHCI_TRB_DUMP(FUSB_INFO, TL, cur);
    FXHCI_TRB_DUMP(FUSB_INFO, TDS, cur);
    FXHCI_TRB_DUMP(FUSB_INFO, C, cur);
    FXHCI_TRB_DUMP(FUSB_INFO, ISP, cur);
    FXHCI_TRB_DUMP(FUSB_INFO, CH, cur);
    FXHCI_TRB_DUMP(FUSB_INFO, IOC, cur);
    FXHCI_TRB_DUMP(FUSB_INFO, IDT, cur);
    FXHCI_TRB_DUMP(FUSB_INFO, TT, cur);
    FXHCI_TRB_DUMP(FUSB_INFO, DIR, cur);
}

static const FXhciTrb *FXhciNextTrb(const FXhciTrb *const cur)
{
    if (FXHCI_TRB_GET(TT, cur) == FXHCI_TRB_LINK)
    {
        return (!cur->ptr_low) ? NULL : (void *)(uintptr)(cur->ptr_low);
    }
    else
    {
        return cur + 1;
    }
}

void FXhciDumpTransferTrbs(const FXhciTrb *const first, const FXhciTrb *const last)
{
    const FXhciTrb *cur;
    for (cur = first; cur; cur = FXhciNextTrb(cur))
    {
        FXhciDumpTransferTrb(cur);
        if (cur == last)
        {
            break;
        }
    }
}
