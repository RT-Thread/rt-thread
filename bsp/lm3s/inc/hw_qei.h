//*****************************************************************************
//
// hw_qei.h - Macros used when accessing the QEI hardware.
//
// Copyright (c) 2005-2009 Luminary Micro, Inc.  All rights reserved.
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
// This is part of revision 4694 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_QEI_H__
#define __HW_QEI_H__

//*****************************************************************************
//
// The following are defines for the QEI register offsets.
//
//*****************************************************************************
#define QEI_O_CTL               0x00000000  // Configuration and control reg.
#define QEI_O_STAT              0x00000004  // Status register
#define QEI_O_POS               0x00000008  // Current position register
#define QEI_O_MAXPOS            0x0000000C  // Maximum position register
#define QEI_O_LOAD              0x00000010  // Velocity timer load register
#define QEI_O_TIME              0x00000014  // Velocity timer register
#define QEI_O_COUNT             0x00000018  // Velocity pulse count register
#define QEI_O_SPEED             0x0000001C  // Velocity speed register
#define QEI_O_INTEN             0x00000020  // Interrupt enable register
#define QEI_O_RIS               0x00000024  // Raw interrupt status register
#define QEI_O_ISC               0x00000028  // Interrupt status register

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_CTL register.
//
//*****************************************************************************
#define QEI_CTL_FILTCNT_M       0x000F0000  // Input Filter Pre-Scale Count.
#define QEI_CTL_FILTEN          0x00002000  // Enable Input Filter.
#define QEI_CTL_STALLEN         0x00001000  // Stall enable
#define QEI_CTL_INVI            0x00000800  // Invert Index input
#define QEI_CTL_INVB            0x00000400  // Invert PhB input
#define QEI_CTL_INVA            0x00000200  // Invert PhA input
#define QEI_CTL_VELDIV_M        0x000001C0  // Velocity predivider mask
#define QEI_CTL_VELDIV_1        0x00000000  // Predivide by 1
#define QEI_CTL_VELDIV_2        0x00000040  // Predivide by 2
#define QEI_CTL_VELDIV_4        0x00000080  // Predivide by 4
#define QEI_CTL_VELDIV_8        0x000000C0  // Predivide by 8
#define QEI_CTL_VELDIV_16       0x00000100  // Predivide by 16
#define QEI_CTL_VELDIV_32       0x00000140  // Predivide by 32
#define QEI_CTL_VELDIV_64       0x00000180  // Predivide by 64
#define QEI_CTL_VELDIV_128      0x000001C0  // Predivide by 128
#define QEI_CTL_VELEN           0x00000020  // Velocity enable
#define QEI_CTL_RESMODE         0x00000010  // Position counter reset mode
#define QEI_CTL_CAPMODE         0x00000008  // Edge capture mode
#define QEI_CTL_SIGMODE         0x00000004  // Encoder signaling mode
#define QEI_CTL_SWAP            0x00000002  // Swap input signals
#define QEI_CTL_ENABLE          0x00000001  // QEI enable
#define QEI_CTL_FILTCNT_S       16

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_STAT register.
//
//*****************************************************************************
#define QEI_STAT_DIRECTION      0x00000002  // Direction of rotation
#define QEI_STAT_ERROR          0x00000001  // Signalling error detected

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_POS register.
//
//*****************************************************************************
#define QEI_POS_M               0xFFFFFFFF  // Current encoder position
#define QEI_POS_S               0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_MAXPOS register.
//
//*****************************************************************************
#define QEI_MAXPOS_M            0xFFFFFFFF  // Maximum encoder position
#define QEI_MAXPOS_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_LOAD register.
//
//*****************************************************************************
#define QEI_LOAD_M              0xFFFFFFFF  // Velocity timer load value
#define QEI_LOAD_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_TIME register.
//
//*****************************************************************************
#define QEI_TIME_M              0xFFFFFFFF  // Velocity timer current value
#define QEI_TIME_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_COUNT register.
//
//*****************************************************************************
#define QEI_COUNT_M             0xFFFFFFFF  // Encoder running pulse count
#define QEI_COUNT_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_SPEED register.
//
//*****************************************************************************
#define QEI_SPEED_M             0xFFFFFFFF  // Encoder pulse count
#define QEI_SPEED_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_INTEN register.
//
//*****************************************************************************
#define QEI_INTEN_ERROR         0x00000008  // Phase error detected
#define QEI_INTEN_DIR           0x00000004  // Direction change
#define QEI_INTEN_TIMER         0x00000002  // Velocity timer expired
#define QEI_INTEN_INDEX         0x00000001  // Index pulse detected

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_RIS register.
//
//*****************************************************************************
#define QEI_RIS_ERROR           0x00000008  // Phase error detected
#define QEI_RIS_DIR             0x00000004  // Direction change
#define QEI_RIS_TIMER           0x00000002  // Velocity timer expired
#define QEI_RIS_INDEX           0x00000001  // Index pulse detected

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_ISC register.
//
//*****************************************************************************
#define QEI_ISC_ERROR           0x00000008  // Phase Error Interrupt.
#define QEI_ISC_DIR             0x00000004  // Direction Change Interrupt.
#define QEI_ISC_TIMER           0x00000002  // Velocity Timer Expired
                                            // Interrupt.
#define QEI_ISC_INDEX           0x00000001  // Index Pulse Interrupt.

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the QEI_ISC
// register.
//
//*****************************************************************************
#define QEI_INT_ERROR           0x00000008  // Phase error detected
#define QEI_INT_DIR             0x00000004  // Direction change
#define QEI_INT_TIMER           0x00000002  // Velocity timer expired
#define QEI_INT_INDEX           0x00000001  // Index pulse detected

//*****************************************************************************
//
// The following are deprecated defines for the reset values for the QEI
// registers.
//
//*****************************************************************************
#define QEI_RV_POS              0x00000000  // Current position register
#define QEI_RV_LOAD             0x00000000  // Velocity timer load register
#define QEI_RV_CTL              0x00000000  // Configuration and control reg.
#define QEI_RV_RIS              0x00000000  // Raw interrupt status register
#define QEI_RV_ISC              0x00000000  // Interrupt status register
#define QEI_RV_SPEED            0x00000000  // Velocity speed register
#define QEI_RV_INTEN            0x00000000  // Interrupt enable register
#define QEI_RV_STAT             0x00000000  // Status register
#define QEI_RV_COUNT            0x00000000  // Velocity pulse count register
#define QEI_RV_MAXPOS           0x00000000  // Maximum position register
#define QEI_RV_TIME             0x00000000  // Velocity timer register

#endif

#endif // __HW_QEI_H__
