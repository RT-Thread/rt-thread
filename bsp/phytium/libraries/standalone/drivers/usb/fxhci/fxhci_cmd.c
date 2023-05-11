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
 * FilePath: fxhci_cmd.c
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:11:23
 * Description:  This files is for implementation of XHCI command
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include "fdebug.h"
#include "fxhci_private.h"

#define FUSB_DEBUG_TAG "FXHCI_CMD"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

FXhciTrb *FXhciNextCmdTrb(FXhci *const xhci)
{
    FXhciClearTrb(xhci->cr.cur, xhci->cr.pcs);
    return xhci->cr.cur;
}

void FXhciPostCmd(FXhci *const xhci)
{
    FUSB_INFO("Command %d (@%p).", FXHCI_TRB_GET(TT, xhci->cr.cur), xhci->cr.cur);

    FXHCI_TRB_SET(C, xhci->cr.cur, xhci->cr.pcs); /* Cycle Bit */
    ++xhci->cr.cur;

    /* pass command trb to hardware */
    WMB();

    /* Ring the doorbell */
    FXhciWriteDb32(&xhci->mmio, FXHCI_REG_DB_HOST_CONTROLLER, FXHCI_REG_DB_TARGET_HC_COMMAND);

    while (FXHCI_TRB_GET(TT, xhci->cr.cur) == FXHCI_TRB_LINK)
    {
        FUSB_DEBUG("Handling link pointer (@%p).", xhci->cr.cur);
        const int tc = FXHCI_TRB_GET(TC, xhci->cr.cur); /* Completion Code */
        FXHCI_TRB_SET(C, xhci->cr.cur, xhci->cr.pcs); /* Cycle Bit */
        xhci->cr.cur = (void *)(uintptr)(xhci->cr.cur->ptr_low);
        if (tc)
        {
            xhci->cr.pcs ^= 1;
        }
    }
}

static FXhciTransCode FXhciWaitForCmd(FXhci *const xhci,
                                      const FXhciTrb *const cmd_trb,
                                      const int clear_event)
{
    FXhciTransCode cc;
    u64 reg_val64;

    cc = FXhciWaitForCmdDone(xhci, cmd_trb, clear_event);
    if (cc != FXHCI_CC_TIMEOUT)
    {
        return cc;
    }

    /* Abort command on timeout */
    FUSB_ERROR("Aborting command (@%p), CRCR: 0x%x.", cmd_trb, FXhciReadOper64(&xhci->mmio, FXHCI_REG_OP_CRCR));

    /*
     * Ref. xHCI Specification Revision 1.2, May 2019.
     * Section 5.4.5, Table 5-24.
     *
     * Abort the command and stop the ring.
     */
    reg_val64 = FXhciReadOper64(&xhci->mmio, FXHCI_REG_OP_CRCR);
    reg_val64 |= FXHCI_REG_OP_CRCR_CA;
    FXhciWriteOper64(&xhci->mmio, FXHCI_REG_OP_CRCR, reg_val64);

    cc = FXhciWaitForCmdAborted(xhci, cmd_trb);

    if ((FXhciReadOper64(&xhci->mmio, FXHCI_REG_OP_CRCR) & FXHCI_REG_OP_CRCR_CRR))
    {
        FUSB_ERROR("FXhciWaitForCmd: Command ring still running.");
    }

    return cc;
}

FXhciTransCode FXhciCmdNop(FXhci *const xhci)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);
    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_NOOP); /* TRB Type */

    FXhciPostCmd(xhci);

    /* wait for result in event ring */
    FXhciTransCode cc = FXhciWaitForCmdDone(xhci, cmd, 1);

    FUSB_INFO("Command ring is %srunning: cc: %d.",
              (FXhciReadOper64(&xhci->mmio, FXHCI_REG_OP_CRCR) & FXHCI_REG_OP_CRCR_CRR) ? "" : "not ", /* check if cmd ring is running */
              cc);

    if (cc != FXHCI_CC_SUCCESS)
    {
        FUSB_ERROR("Noop command failed.");
    }

    return cc;
}

/*
 * xhci_cmd_* return >= 0: xhci completion code (cc)
 *            < 0: driver error code
 */

FXhciTransCode FXhciCmdEnableSlot(FXhci *const xhci, int *const slot_id)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);
    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_ENABLE_SLOT); /* TRB Type */
    FXhciPostCmd(xhci);

    FXhciTransCode cc = FXhciWaitForCmd(xhci, cmd, 0);
    if (cc >= 0)
    {
        if (cc == FXHCI_CC_SUCCESS)
        {
            *slot_id = FXHCI_TRB_GET(ID, xhci->er.cur);
            if (*slot_id > xhci->max_slots_en)
            {
                cc = FXHCI_CC_CONTROLLER_ERROR;
            }
        }

        FXhciAdvanceEvtRing(xhci);
        FXhciHandleEvts(xhci);
    }

    return cc;
}

FXhciTransCode FXhciCmdDisableSlot(FXhci *const xhci, const int slot_id)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);

    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_DISABLE_SLOT); /* TRB Type */
    FXHCI_TRB_SET(ID, cmd, slot_id); /* Slot ID */
    FXhciPostCmd(xhci);

    return FXhciWaitForCmd(xhci, cmd, 1);
}

FXhciTransCode FXhciCmdAddressDevice(FXhci *const xhci,
                                     const int slot_id,
                                     FXhciInputCtx *const ic)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);

    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_ADDRESS_DEV); /* TRB Type */
    FXHCI_TRB_SET(ID, cmd, slot_id); /* Slot ID */
    cmd->ptr_low = (uintptr)(ic->raw);
    FXhciPostCmd(xhci);

    return FXhciWaitForCmd(xhci, cmd, 1);
}

FXhciTransCode FXhciCmdConfigureEp(FXhci *const xhci,
                                   const int slot_id,
                                   const int config_id,
                                   FXhciInputCtx *const ic)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);

    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_CONFIGURE_EP); /* TRB Type */
    FXHCI_TRB_SET(ID, cmd, slot_id); /* Slot ID */
    cmd->ptr_low = (uintptr)(ic->raw);

    if (config_id == 0)
    {
        FXHCI_TRB_SET(DC, cmd, 1);    /* Deconfigure */
    }

    FXhciPostCmd(xhci);

    return FXhciWaitForCmd(xhci, cmd, 1);
}

FXhciTransCode FXhciCmdEvaluateCtx(FXhci *const xhci,
                                   const int slot_id,
                                   FXhciInputCtx *const ic)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);

    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_EVAL_CTX); /* TRB Type */
    FXHCI_TRB_SET(ID, cmd, slot_id); /* Slot ID */

    cmd->ptr_low = (uintptr)(ic->raw);
    FXhciPostCmd(xhci);

    return FXhciWaitForCmd(xhci, cmd, 1);
}

FXhciTransCode FXhciCmdResetEp(FXhci *const xhci, const int slot_id, const int ep)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);

    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_RESET_EP); /* TRB Type */
    FXHCI_TRB_SET(ID, cmd, slot_id); /* Slot ID */
    FXHCI_TRB_SET(EP, cmd, ep); /* Endpoint ID */

    FXhciPostCmd(xhci);

    return FXhciWaitForCmd(xhci, cmd, 1);
}

FXhciTransCode FXhciCmdStopEp(FXhci *const xhci, const int slot_id, const int ep)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);

    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_STOP_EP); /* TRB Type */
    FXHCI_TRB_SET(ID, cmd, slot_id); /* Slot ID */
    FXHCI_TRB_SET(EP, cmd, ep); /* Endpoint ID */

    FXhciPostCmd(xhci);

    return FXhciWaitForCmd(xhci, cmd, 1);
}

FXhciTransCode FXhciCmdSetTrDq(FXhci *const xhci, const int slot_id, const int ep,
                               FXhciTrb *const dq_trb, const int dcs)
{
    FXhciTrb *const cmd = FXhciNextCmdTrb(xhci);

    FXHCI_TRB_SET(TT, cmd, FXHCI_TRB_CMD_SET_TR_DQ); /* TRB Type */
    FXHCI_TRB_SET(ID, cmd, slot_id); /* Slot ID */
    FXHCI_TRB_SET(EP, cmd, ep); /* Endpoint ID */

    cmd->ptr_low = (uintptr)(dq_trb) | dcs;

    FXhciPostCmd(xhci);

    return FXhciWaitForCmd(xhci, cmd, 1);
}
