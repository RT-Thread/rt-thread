//*****************************************************************************
//
// hw_sysexc.h - Macros used when accessing the system exception module.
//
// Copyright (c) 2011 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 8264 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_SYSEXC_H__
#define __HW_SYSEXC_H__

//*****************************************************************************
//
// The following are defines for the System Exception Module register
// addresses.
//
//*****************************************************************************
#define SYSEXC_RIS              0x400F9000  // System Exception Raw Interrupt
                                            // Status
#define SYSEXC_IM               0x400F9004  // System Exception Interrupt Mask
#define SYSEXC_MIS              0x400F9008  // System Exception Raw Interrupt
                                            // Status
#define SYSEXC_IC               0x400F900C  // System Exception Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSEXC_RIS register.
//
//*****************************************************************************
#define SYSEXC_RIS_IXCRIS       0x00000020  // Inexact Exception Flag
#define SYSEXC_RIS_OFCRIS       0x00000010  // Overflow Exception Flag
#define SYSEXC_RIS_UFCRIS       0x00000008  // Underflow Exception Flag
#define SYSEXC_RIS_IOCRIS       0x00000004  // Invalid Operation Flag
#define SYSEXC_RIS_DZCRIS       0x00000002  // Divide By 0 Exception Flag
#define SYSEXC_RIS_IDCRIS       0x00000001  // Input Denormal Exception Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSEXC_IM register.
//
//*****************************************************************************
#define SYSEXC_IM_IXCIM         0x00000020  // Inexact Exception Flag
#define SYSEXC_IM_OFCIM         0x00000010  // Overflow Exception Flag
#define SYSEXC_IM_UFCIM         0x00000008  // Underflow Exception Flag
#define SYSEXC_IM_IOCIM         0x00000004  // Invalid Operation Flag
#define SYSEXC_IM_DZCIM         0x00000002  // Divide By 0 Exception Flag
#define SYSEXC_IM_IDCIM         0x00000001  // Input Denormal Exception Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSEXC_MIS register.
//
//*****************************************************************************
#define SYSEXC_MIS_IXCMIS       0x00000020  // Inexact Exception Flag
#define SYSEXC_MIS_OFCMIS       0x00000010  // Overflow Exception Flag
#define SYSEXC_MIS_UFCMIS       0x00000008  // Underflow Exception Flag
#define SYSEXC_MIS_IOCMIS       0x00000004  // Invalid Operation Flag
#define SYSEXC_MIS_DZCMIS       0x00000002  // Divide By 0 Exception Flag
#define SYSEXC_MIS_IDCMIS       0x00000001  // Input Denormal Exception Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSEXC_IC register.
//
//*****************************************************************************
#define SYSEXC_IC_IXCIC         0x00000020  // Inexact Exception Flag
#define SYSEXC_IC_OFCIC         0x00000010  // Overflow Exception Flag
#define SYSEXC_IC_UFCIC         0x00000008  // Underflow Exception Flag
#define SYSEXC_IC_IOCIC         0x00000004  // Invalid Operation Flag
#define SYSEXC_IC_DZCIC         0x00000002  // Divide By 0 Exception Flag
#define SYSEXC_IC_IDCIC         0x00000001  // Input Denormal Exception Flag

#endif // __HW_SYSEXC_H__
