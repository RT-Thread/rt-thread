/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-29 10:21:53
 * @LastEditTime: 2021-05-25 16:41:38
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#include "ft_can.h"
#include "ft_can_hw.h"
#include "ft_assert.h"
#include "ft_debug.h"
#include "string.h"

#define FT_CAN_DEBUG_TAG "FT_CAN"

#define FT_CAN_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_CAN_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_CAN_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)

ft_error_t
FCan_CfgInitialize(FCan_t *Can_p, FCan_Config_t *Config_p)
{
    Ft_assertNonvoid(Can_p != NULL);
    Ft_assertNonvoid(Config_p != NULL);
    Can_p->Config = *Config_p;
    Can_p->IsReady = FT_COMPONENT_IS_READLY;
    FCan_Reset(Can_p);
    return FCAN_SUCCESS;
}

void FCan_GetErrorCnt(FCan_t *Can_p, u32 *TxErr, u32 *RxErr)
{
    FCan_Config_t *Config_p;
    Ft_assertVoid(Can_p != NULL);
    Ft_assertVoid(Can_p->IsReady == FT_COMPONENT_IS_READLY);
    Config_p = &Can_p->Config;

    *RxErr = FCan_ReadReg(Config_p->CanBaseAddress, FCAN_ERR_CNT_OFFSET) & FCAN_ERR_CNT_RFN_MASK;
    *TxErr = (FCan_ReadReg(Config_p->CanBaseAddress, FCAN_ERR_CNT_OFFSET) & FCAN_ERR_CNT_TFN_MASK) >> FCAN_ERR_CNT_TFN_SHIFT;
}

u32 FCan_RecvByIrq(FCan_t *Can_p, struct FCan_Frame *Frame_p, u32 FrameNumber)
{
    u32 FifoCnt = 0;
    FCan_Config_t *Config_p;
    u32 CanId;
    u32 Dlc;
    u32 CanFrameIndex = 0;
    u32 RxValue;
    Ft_assertZeroNum(Can_p != NULL);
    Ft_assertZeroNum(Can_p->IsReady == FT_COMPONENT_IS_READLY);
    Config_p = &Can_p->Config;

    FifoCnt = FCan_ReadReg(Config_p->CanBaseAddress, FCAN_FIFO_CNT_OFFSET) & 0x3f;

    if (0 == FifoCnt)
    {
        return 0;
    }

    FrameNumber = (FrameNumber > FifoCnt) ? FifoCnt : FrameNumber;

    while (FrameNumber)
    {
        /* Read a frame from Phytium CAN */
        CanId = FCan_ReadReg(Config_p->CanBaseAddress, FCAN_RX_FIFO_OFFSET);
        /* if CanId is big-endian ,use swap change to little-endian */
        CanId = FT_SWAP32(CanId);
        /* Identifier extension */
        if (CanId & FCAN_IDR_IDE_MASK)
        {
            Dlc = FCan_ReadReg(Config_p->CanBaseAddress, FCAN_RX_FIFO_OFFSET);
            Dlc = FT_SWAP32(Dlc);
            Dlc = ((Dlc & FCAN_IDR_EDLC_MASK) >> FCAN_IDR_EDLC_SHIFT);

            Frame_p[CanFrameIndex].CanId = (CanId & FCAN_IDR_ID1_MASK) >> 3;
            Frame_p[CanFrameIndex].CanId |= (CanId & FCAN_IDR_ID2_MASK) >> FCAN_IDR_ID2_SHIFT;
            Frame_p[CanFrameIndex].CanId |= CAN_EFF_FLAG;

            if (CanId & FCAN_IDR_RTR_MASK)
            {
                Frame_p[CanFrameIndex].CanId |= CAN_RTR_FLAG;
            }
        }
        else
        {
            Dlc = ((CanId & FCAN_IDR_DLC_MASK) >> FCAN_IDR_SDLC_SHIFT);

            /* The received frame is a standard format frame */
            Frame_p[CanFrameIndex].CanId = (CanId & FCAN_IDR_ID1_MASK) >> FCAN_IDR_ID1_SHIFT;
            if (CanId & FCAN_IDR_SRR_MASK)
            {
                Frame_p[CanFrameIndex].CanId |= CAN_RTR_FLAG;
            }
        }

        Frame_p[CanFrameIndex].CanDlc = (Dlc > sizeof(Frame_p[CanFrameIndex].data)) ? sizeof(Frame_p[CanFrameIndex].data) : Dlc;

        if (!(Frame_p[CanFrameIndex].CanId & CAN_RTR_FLAG))
        {
            if (Frame_p[CanFrameIndex].CanDlc > 0)
            {
                RxValue = FCan_ReadReg(Config_p->CanBaseAddress, FCAN_RX_FIFO_OFFSET);
                memcpy(Frame_p[CanFrameIndex].data, &RxValue, sizeof(RxValue));
            }

            if (Frame_p[CanFrameIndex].CanDlc > 4)
            {
                RxValue = FCan_ReadReg(Config_p->CanBaseAddress, FCAN_RX_FIFO_OFFSET);
                memcpy(&Frame_p[CanFrameIndex].data[4], &RxValue, sizeof(RxValue));
            }
        }
        FrameNumber--;
        CanFrameIndex++;
    }

    return (CanFrameIndex + 1);
}

static void FCan_SendFifo(FCan_t *Can_p, struct FCan_Frame *Frame_p)
{
    u32 Id, Dlc;
    FCan_Config_t *Config_p;
    u32 SendBuffer = 0;
    Ft_assertVoid(Can_p != NULL);
    Ft_assertVoid(Can_p->IsReady == FT_COMPONENT_IS_READLY);
    Config_p = &Can_p->Config;
    if (Frame_p->CanId & CAN_EFF_FLAG)
    {
        /* Extended CAN ID format */
        Id = ((Frame_p->CanId & CAN_EFF_MASK) << FCAN_IDR_ID2_SHIFT) &
             FCAN_IDR_ID2_MASK;
        Id |= (((Frame_p->CanId & CAN_EFF_MASK) >>
                (CAN_EFF_ID_BITS - CAN_SFF_ID_BITS))
               << FCAN_IDR_ID1_SHIFT) &
              FCAN_IDR_ID1_MASK;

        Id |= FCAN_IDR_IDE_MASK | FCAN_IDR_SRR_MASK;
        if (Frame_p->CanId & CAN_RTR_FLAG)
        {
            Id |= FCAN_IDR_RTR_MASK;
        }

        Dlc = Frame_p->CanDlc << FCAN_IDR_EDLC_SHIFT;

        FCan_WriteReg(Config_p->CanBaseAddress, FCAN_TX_FIFO_OFFSET, FT_SWAP32(Id));
        FCan_WriteReg(Config_p->CanBaseAddress, FCAN_TX_FIFO_OFFSET, FT_SWAP32(Dlc));
    }
    else
    {
        /* Standard CAN ID format */
        Id = ((Frame_p->CanId & CAN_SFF_MASK) << FCAN_IDR_ID1_SHIFT) &
             FCAN_IDR_ID1_MASK;
        if (Frame_p->CanId & CAN_RTR_FLAG)
            Id |= FCAN_IDR_SRR_MASK;

        Dlc = ((Frame_p->CanDlc << FCAN_IDR_SDLC_SHIFT) | FCAN_IDR_PAD_MASK);
        Id |= Dlc;
        FCan_WriteReg(Config_p->CanBaseAddress, FCAN_TX_FIFO_OFFSET, FT_SWAP32(Id));
    }

    if (!(Frame_p->CanId & CAN_RTR_FLAG))
    {
        if (Frame_p->CanDlc > 0)
        {
            memcpy(&SendBuffer, Frame_p->data, 4);
            FCan_WriteReg(Config_p->CanBaseAddress, FCAN_TX_FIFO_OFFSET, SendBuffer);
        }

        if (Frame_p->CanDlc > 4)
        {
            memcpy(&SendBuffer, &Frame_p->data[4], 4);
            FCan_WriteReg(Config_p->CanBaseAddress, FCAN_TX_FIFO_OFFSET, SendBuffer);
        }
    }
}

u32 FCan_SendByIrq(FCan_t *Can_p,
                   struct FCan_Frame *Frame_p,
                   u32 FrameNumber, void (*UserIrqWait)(void))
{
    FCan_Config_t *Config_p;
    u32 FrameIndex = 0;
    u32 NeedSendOnce;
    u32 cnt = 0;
    Ft_assertZeroNum(Can_p != NULL);
    Ft_assertZeroNum(Can_p->IsReady == FT_COMPONENT_IS_READLY);
    Config_p = &Can_p->Config;

    if (NULL == Frame_p)
    {
        FT_CAN_DEBUG_E("Frame_p is NULL , %s: %d", __FILE__, __LINE__);
        return 0;
    }

    if (0 == FrameNumber)
    {
        FT_CAN_DEBUG_E("FrameNumber is 0 , %s: %d", __FILE__, __LINE__);
        return 0;
    }

    for (; 0 < FrameNumber;)
    {
        if (FrameNumber > Config_p->TxFifoDeepth)
        {
            NeedSendOnce = Config_p->TxFifoDeepth;
            FrameNumber -= Config_p->TxFifoDeepth;
        }
        else
        {
            NeedSendOnce = FrameNumber;
            FrameNumber = 0;
        }
        Ft_printf("shut down tranmission \r\n");
        /*shut down tranmission*/
        FCan_ClearBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
        FCan_ClearBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK);
        FCan_SetBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
        Ft_printf("NeedSendOnce %d \r\n", NeedSendOnce);
        for (cnt = 0; cnt < NeedSendOnce; cnt++)
        {
            FCan_SendFifo(Can_p, &Frame_p[FrameIndex]);
            FrameIndex++;
        }
        Can_p->TxFifoCnt = NeedSendOnce;

        /* triggers tranmission */
        FCan_ClearBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
        FCan_SetBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK);
        FCan_SetBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK | FCAN_CTRL_XFER_MASK);

        if (UserIrqWait)
        {
            UserIrqWait();
        }
        else
        {
            while (0 != Can_p->TxFifoCnt)
            {
            };
        }
    }

    return FrameIndex + 1;
}

ft_error_t FCan_SetTiming(FCan_t *Can_p,
                          struct FCan_Bittiming *Bittiming_p)
{
    u32 Btr = 0;
    FCan_Config_t *Config_p;
    u32 IsConfigMode;
    Ft_assertNonvoid(Can_p != NULL);
    Ft_assertNonvoid(Can_p->IsReady == FT_COMPONENT_IS_READLY);
    Config_p = &Can_p->Config;

    Ft_assertNonvoid(Bittiming_p->brp != 0);
    Ft_assertNonvoid(Bittiming_p->prop_seg != 0);
    Ft_assertNonvoid(Bittiming_p->phase_seg1 != 0);
    Ft_assertNonvoid(Bittiming_p->phase_seg2 != 0);

    /* Setting Baud Rate prescalar value in BRPR Register */
    Btr = (Bittiming_p->brp - 1) << 16;
    Btr |= (Bittiming_p->prop_seg - 1) << 2;
    Btr |= (Bittiming_p->phase_seg1 - 1) << 5;
    Btr |= (Bittiming_p->phase_seg2 - 1) << 8;
    Btr |= (Bittiming_p->sjw - 1);

    IsConfigMode = (FCan_ReadReg(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET) & FCAN_CTRL_XFER_MASK);

    if (IsConfigMode)
    {
        FCan_WriteReg(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
    }

    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_DAT_RATE_CTRL_OFFSET, Btr);
    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_ARB_RATE_CTRL_OFFSET, Btr);

    /*Enable Transfer*/
    FCan_SetBit(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);

    return FCAN_SUCCESS;
}

void FCan_Enable(FCan_t *Can_p)
{
    FCan_Config_t *Config_p;
    Ft_assertVoid(Can_p != NULL);
    Ft_assertVoid(Can_p->IsReady == FT_COMPONENT_IS_READLY);
    Config_p = &Can_p->Config;

    FCan_WriteReg(Config_p->CanBaseAddress, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
}
