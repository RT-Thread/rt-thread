//*****************************************************************************
//
// can.h - Defines and Macros for the CAN controller.
//
// Copyright (c) 2006-2009 Luminary Micro, Inc.  All rights reserved.
// Software License Agreement
// 
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's microcontroller products.
// 
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  You may not combine
// this software with "viral" open-source software in order to form a larger
// program.  Any use in violation of the foregoing restrictions may subject
// the user to criminal sanctions under applicable laws, as well as to civil
// liability for the breach of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 4694 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __CAN_H__
#define __CAN_H__

//*****************************************************************************
//
//! \addtogroup can_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Miscellaneous defines for Message ID Types
//
//*****************************************************************************

//*****************************************************************************
//
//! These are the flags used by the tCANMsgObject variable when calling the
//! CANMessageSet() and CANMessageGet() functions.
//
//*****************************************************************************
typedef enum
{
    //
    //! This indicates that transmit interrupts should be enabled, or are
    //! enabled.
    //
    MSG_OBJ_TX_INT_ENABLE =     0x00000001,

    //
    //! This indicates that receive interrupts should be enabled, or are
    //! enabled.
    //
    MSG_OBJ_RX_INT_ENABLE =     0x00000002,

    //
    //! This indicates that a message object will use or is using an extended
    //! identifier.
    //
    MSG_OBJ_EXTENDED_ID =       0x00000004,

    //
    //! This indicates that a message object will use or is using filtering
    //! based on the object's message identifier.
    //
    MSG_OBJ_USE_ID_FILTER =     0x00000008,

    //
    //! This indicates that new data was available in the message object.
    //
    MSG_OBJ_NEW_DATA =          0x00000080,

    //
    //! This indicates that data was lost since this message object was last
    //! read.
    //
    MSG_OBJ_DATA_LOST =         0x00000100,

    //
    //! This indicates that a message object will use or is using filtering
    //! based on the direction of the transfer.  If the direction filtering is
    //! used, then ID filtering must also be enabled.
    //
    MSG_OBJ_USE_DIR_FILTER =    (0x00000010 | MSG_OBJ_USE_ID_FILTER),

    //
    //! This indicates that a message object will use or is using message
    //! identifier filtering based on the extended identifier.  If the extended
    //! identifier filtering is used, then ID filtering must also be enabled.
    //
    MSG_OBJ_USE_EXT_FILTER =    (0x00000020 | MSG_OBJ_USE_ID_FILTER),

    //
    //! This indicates that a message object is a remote frame.
    //
    MSG_OBJ_REMOTE_FRAME =      0x00000040,

    //
    //! This indicates that a message object has no flags set.
    //
    MSG_OBJ_NO_FLAGS =          0x00000000
}
tCANObjFlags;

//*****************************************************************************
//
//! This define is used with the #tCANObjFlags enumerated values to allow
//! checking only status flags and not configuration flags.
//
//*****************************************************************************
#define MSG_OBJ_STATUS_MASK     (MSG_OBJ_NEW_DATA | MSG_OBJ_DATA_LOST)

//*****************************************************************************
//
//! The structure used for encapsulating all the items associated with a CAN
//! message object in the CAN controller.
//
//*****************************************************************************
typedef struct
{
    //
    //! The CAN message identifier used for 11 or 29 bit identifiers.
    //
    unsigned long ulMsgID;

    //
    //! The message identifier mask used when identifier filtering is enabled.
    //
    unsigned long ulMsgIDMask;

    //
    //! This value holds various status flags and settings specified by
    //! tCANObjFlags.
    //
    unsigned long ulFlags;

    //
    //! This value is the number of bytes of data in the message object.
    //
    unsigned long ulMsgLen;

    //
    //! This is a pointer to the message object's data.
    //
    unsigned char *pucMsgData;
}
tCANMsgObject;

//*****************************************************************************
//
//! This structure is used for encapsulating the values associated with setting
//! up the bit timing for a CAN controller.  The structure is used when calling
//! the CANGetBitTiming and CANSetBitTiming functions.
//
//*****************************************************************************
typedef struct
{
    //
    //! This value holds the sum of the Synchronization, Propagation, and Phase
    //! Buffer 1 segments, measured in time quanta.  The valid values for this
    //! setting range from 2 to 16.
    //
    unsigned int uSyncPropPhase1Seg;

    //
    //! This value holds the Phase Buffer 2 segment in time quanta.  The valid
    //! values for this setting range from 1 to 8.
    //
    unsigned int uPhase2Seg;

    //
    //! This value holds the Resynchronization Jump Width in time quanta.  The
    //! valid values for this setting range from 1 to 4.
    //
    unsigned int uSJW;

    //
    //! This value holds the CAN_CLK divider used to determine time quanta.
    //! The valid values for this setting range from 1 to 1023.
    //
    unsigned int uQuantumPrescaler;
}
tCANBitClkParms;

//*****************************************************************************
//
//! This data type is used to identify the interrupt status register.  This is
//! used when calling the CANIntStatus() function.
//
//*****************************************************************************
typedef enum
{
    //
    //! Read the CAN interrupt status information.
    //
    CAN_INT_STS_CAUSE,

    //
    //! Read a message object's interrupt status.
    //
    CAN_INT_STS_OBJECT
}
tCANIntStsReg;

//*****************************************************************************
//
//! This data type is used to identify which of several status registers to
//! read when calling the CANStatusGet() function.
//
//*****************************************************************************
typedef enum
{
    //
    //! Read the full CAN controller status.
    //
    CAN_STS_CONTROL,

    //
    //! Read the full 32-bit mask of message objects with a transmit request
    //! set.
    //
    CAN_STS_TXREQUEST,

    //
    //! Read the full 32-bit mask of message objects with new data available.
    //
    CAN_STS_NEWDAT,

    //
    //! Read the full 32-bit mask of message objects that are enabled.
    //
    CAN_STS_MSGVAL
}
tCANStsReg;

//*****************************************************************************
//
//! These definitions are used to specify interrupt sources to CANIntEnable()
//! and CANIntDisable().
//
//*****************************************************************************
typedef enum
{
    //
    //! This flag is used to allow a CAN controller to generate error
    //! interrupts.
    //
    CAN_INT_ERROR =             0x00000008,

    //
    //! This flag is used to allow a CAN controller to generate status
    //! interrupts.
    //
    CAN_INT_STATUS =            0x00000004,

    //
    //! This flag is used to allow a CAN controller to generate any CAN
    //! interrupts.  If this is not set, then no interrupts will be generated
    //! by the CAN controller.
    //
    CAN_INT_MASTER =            0x00000002
}
tCANIntFlags;

//*****************************************************************************
//
//! This definition is used to determine the type of message object that will
//! be set up via a call to the CANMessageSet() API.
//
//*****************************************************************************
typedef enum
{
    //
    //! Transmit message object.
    //
    MSG_OBJ_TYPE_TX,

    //
    //! Transmit remote request message object
    //
    MSG_OBJ_TYPE_TX_REMOTE,

    //
    //! Receive message object.
    //
    MSG_OBJ_TYPE_RX,

    //
    //! Receive remote request message object.
    //
    MSG_OBJ_TYPE_RX_REMOTE,

    //
    //! Remote frame receive remote, with auto-transmit message object.
    //
    MSG_OBJ_TYPE_RXTX_REMOTE
}
tMsgObjType;

//*****************************************************************************
//
//! The following enumeration contains all error or status indicators that can
//! be returned when calling the CANStatusGet() function.
//
//*****************************************************************************
typedef enum
{
    //
    //! CAN controller has entered a Bus Off state.
    //
    CAN_STATUS_BUS_OFF =        0x00000080,

    //
    //! CAN controller error level has reached warning level.
    //
    CAN_STATUS_EWARN =          0x00000040,

    //
    //! CAN controller error level has reached error passive level.
    //
    CAN_STATUS_EPASS =          0x00000020,

    //
    //! A message was received successfully since the last read of this status.
    //
    CAN_STATUS_RXOK =           0x00000010,

    //
    //! A message was transmitted successfully since the last read of this
    //! status.
    //
    CAN_STATUS_TXOK =           0x00000008,

    //
    //! This is the mask for the last error code field.
    //
    CAN_STATUS_LEC_MSK =        0x00000007,

    //
    //! There was no error.
    //
    CAN_STATUS_LEC_NONE =       0x00000000,

    //
    //! A bit stuffing error has occurred.
    //
    CAN_STATUS_LEC_STUFF =      0x00000001,

    //
    //! A formatting error has occurred.
    //
    CAN_STATUS_LEC_FORM =       0x00000002,

    //
    //! An acknowledge error has occurred.
    //
    CAN_STATUS_LEC_ACK =        0x00000003,

    //
    //! The bus remained a bit level of 1 for longer than is allowed.
    //
    CAN_STATUS_LEC_BIT1 =       0x00000004,

    //
    //! The bus remained a bit level of 0 for longer than is allowed.
    //
    CAN_STATUS_LEC_BIT0 =       0x00000005,

    //
    //! A CRC error has occurred.
    //
    CAN_STATUS_LEC_CRC =        0x00000006,

    //
    //! This is the mask for the CAN Last Error Code (LEC).
    //
    CAN_STATUS_LEC_MASK =       0x00000007
}
tCANStatusCtrl;

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern void CANBitTimingGet(unsigned long ulBase, tCANBitClkParms *pClkParms);
extern void CANBitTimingSet(unsigned long ulBase, tCANBitClkParms *pClkParms);
extern unsigned long CANBitRateSet(unsigned long ulBase,
                                   unsigned long ulSourceClock,
                                   unsigned long ulBitRate);
extern void CANDisable(unsigned long ulBase);
extern void CANEnable(unsigned long ulBase);
extern tBoolean CANErrCntrGet(unsigned long ulBase, unsigned long *pulRxCount,
                              unsigned long *pulTxCount);
extern void CANInit(unsigned long ulBase);
extern void CANIntClear(unsigned long ulBase, unsigned long ulIntClr);
extern void CANIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern void CANIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void CANIntRegister(unsigned long ulBase, void (*pfnHandler)(void));
extern unsigned long CANIntStatus(unsigned long ulBase,
                                  tCANIntStsReg eIntStsReg);
extern void CANIntUnregister(unsigned long ulBase);
extern void CANMessageClear(unsigned long ulBase, unsigned long ulObjID);
extern void CANMessageGet(unsigned long ulBase, unsigned long ulObjID,
                          tCANMsgObject *pMsgObject, tBoolean bClrPendingInt);
extern void CANMessageSet(unsigned long ulBase, unsigned long ulObjID,
                          tCANMsgObject *pMsgObject, tMsgObjType eMsgType);
extern tBoolean CANRetryGet(unsigned long ulBase);
extern void CANRetrySet(unsigned long ulBase, tBoolean bAutoRetry);
extern unsigned long CANStatusGet(unsigned long ulBase, tCANStsReg eStatusReg);

//*****************************************************************************
//
// Several CAN APIs have been renamed, with the original function name being
// deprecated.  These defines provide backward compatibility.
//
//*****************************************************************************
#ifndef DEPRECATED
#define CANSetBitTiming(a, b)   CANBitTimingSet(a, b)
#define CANGetBitTiming(a, b)   CANBitTimingGet(a, b)
#endif

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#endif //  __CAN_H__
