//*****************************************************************************
//
// bl_can.h - Definitions for the CAN transport functions.
//
// Copyright (c) 2008-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#ifndef __BL_CAN_H__
#define __BL_CAN_H__

//*****************************************************************************
//
// These defines are used to define the range of values that are used for
// the CAN update protocol.
//
//*****************************************************************************
#define CAN_MSGID_DTYPE_UPDATE  0x1f000000
#define CAN_MSGID_MFR_SL        0x00020000

//*****************************************************************************
//
// The masks of the fields that are used in the message identifier.
//
//*****************************************************************************
#define CAN_MSGID_DEVNO_M       0x0000003f
#define CAN_MSGID_API_M         0x0000ffc0
#define CAN_MSGID_MFR_M         0x00ff0000
#define CAN_MSGID_DTYPE_M       0x1f000000
#define CAN_MSGID_DEVNO_S       0
#define CAN_MSGID_API_S         6
#define CAN_MSGID_MFR_S         16
#define CAN_MSGID_DTYPE_S       24

//*****************************************************************************
//
//  Firmware Update API definitions.
//
//*****************************************************************************
#define SL_API_UPD              (CAN_MSGID_MFR_SL | CAN_MSGID_DTYPE_UPDATE)
#define SL_API_UPD_PING         (SL_API_UPD | (0 << CAN_MSGID_API_S))
#define SL_API_UPD_DOWNLOAD     (SL_API_UPD | (1 << CAN_MSGID_API_S))
#define SL_API_UPD_SEND_DATA    (SL_API_UPD | (2 << CAN_MSGID_API_S))
#define SL_API_UPD_RESET        (SL_API_UPD | (3 << CAN_MSGID_API_S))
#define SL_API_UPD_ACK          (SL_API_UPD | (4 << CAN_MSGID_API_S))
#define SL_API_UPD_REQUEST      (SL_API_UPD | (6 << CAN_MSGID_API_S))

#endif // __BL_CAN_H__
