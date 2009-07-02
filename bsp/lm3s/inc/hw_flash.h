//*****************************************************************************
//
// hw_flash.h - Macros used when accessing the flash controller.
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

#ifndef __HW_FLASH_H__
#define __HW_FLASH_H__

//*****************************************************************************
//
// The following are defines for the FLASH register offsets.
//
//*****************************************************************************
#define FLASH_FMA               0x400FD000  // Memory address register
#define FLASH_FMD               0x400FD004  // Memory data register
#define FLASH_FMC               0x400FD008  // Memory control register
#define FLASH_FCRIS             0x400FD00C  // Raw interrupt status register
#define FLASH_FCIM              0x400FD010  // Interrupt mask register
#define FLASH_FCMISC            0x400FD014  // Interrupt status register
#define FLASH_FMC2              0x400FD020  // Flash Memory Control 2
#define FLASH_FWBVAL            0x400FD030  // Flash Write Buffer Valid
#define FLASH_FWBN              0x400FD100  // Flash Write Buffer Register n
#define FLASH_RMCTL             0x400FE0F0  // ROM Control
#define FLASH_RMVER             0x400FE0F4  // ROM Version Register
#define FLASH_FMPRE             0x400FE130  // FLASH read protect register
#define FLASH_FMPPE             0x400FE134  // FLASH program protect register
#define FLASH_USECRL            0x400FE140  // uSec reload register
#define FLASH_USERDBG           0x400FE1D0  // User Debug
#define FLASH_USERREG0          0x400FE1E0  // User Register 0
#define FLASH_USERREG1          0x400FE1E4  // User Register 1
#define FLASH_USERREG2          0x400FE1E8  // User Register 2
#define FLASH_USERREG3          0x400FE1EC  // User Register 3
#define FLASH_FMPRE0            0x400FE200  // FLASH read protect register 0
#define FLASH_FMPRE1            0x400FE204  // FLASH read protect register 1
#define FLASH_FMPRE2            0x400FE208  // FLASH read protect register 2
#define FLASH_FMPRE3            0x400FE20C  // FLASH read protect register 3
#define FLASH_FMPPE0            0x400FE400  // FLASH program protect register 0
#define FLASH_FMPPE1            0x400FE404  // FLASH program protect register 1
#define FLASH_FMPPE2            0x400FE408  // FLASH program protect register 2
#define FLASH_FMPPE3            0x400FE40C  // FLASH program protect register 3

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMC register.
//
//*****************************************************************************
#define FLASH_FMC_WRKEY_M       0xFFFF0000  // FLASH write key mask
#define FLASH_FMC_WRKEY         0xA4420000  // FLASH write key
#define FLASH_FMC_COMT          0x00000008  // Commit user register
#define FLASH_FMC_MERASE        0x00000004  // Mass erase FLASH
#define FLASH_FMC_ERASE         0x00000002  // Erase FLASH page
#define FLASH_FMC_WRITE         0x00000001  // Write FLASH word
#define FLASH_FMC_WRKEY_S       16

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMC2 register.
//
//*****************************************************************************
#define FLASH_FMC2_WRKEY        0xA4420000  // FLASH write key
#define FLASH_FMC2_WRBUF        0x00000001  // Buffered Flash Write.

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FCRIS register.
//
//*****************************************************************************
#define FLASH_FCRIS_PRIS        0x00000002  // Programming Raw Interrupt
                                            // Status.
#define FLASH_FCRIS_ARIS        0x00000001  // Access Raw Interrupt Status.

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FCIM register.
//
//*****************************************************************************
#define FLASH_FCIM_PMASK        0x00000002  // Programming Interrupt Mask.
#define FLASH_FCIM_AMASK        0x00000001  // Access Interrupt Mask.

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMIS register.
//
//*****************************************************************************
#define FLASH_FCMISC_PMISC      0x00000002  // Programming Masked Interrupt
                                            // Status and Clear.
#define FLASH_FCMISC_AMISC      0x00000001  // Access Masked Interrupt Status
                                            // and Clear.

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE and
// FLASH_FMPPE registers.
//
//*****************************************************************************
#define FLASH_FMP_BLOCK_31      0x80000000  // Enable for block 31
#define FLASH_FMP_BLOCK_30      0x40000000  // Enable for block 30
#define FLASH_FMP_BLOCK_29      0x20000000  // Enable for block 29
#define FLASH_FMP_BLOCK_28      0x10000000  // Enable for block 28
#define FLASH_FMP_BLOCK_27      0x08000000  // Enable for block 27
#define FLASH_FMP_BLOCK_26      0x04000000  // Enable for block 26
#define FLASH_FMP_BLOCK_25      0x02000000  // Enable for block 25
#define FLASH_FMP_BLOCK_24      0x01000000  // Enable for block 24
#define FLASH_FMP_BLOCK_23      0x00800000  // Enable for block 23
#define FLASH_FMP_BLOCK_22      0x00400000  // Enable for block 22
#define FLASH_FMP_BLOCK_21      0x00200000  // Enable for block 21
#define FLASH_FMP_BLOCK_20      0x00100000  // Enable for block 20
#define FLASH_FMP_BLOCK_19      0x00080000  // Enable for block 19
#define FLASH_FMP_BLOCK_18      0x00040000  // Enable for block 18
#define FLASH_FMP_BLOCK_17      0x00020000  // Enable for block 17
#define FLASH_FMP_BLOCK_16      0x00010000  // Enable for block 16
#define FLASH_FMP_BLOCK_15      0x00008000  // Enable for block 15
#define FLASH_FMP_BLOCK_14      0x00004000  // Enable for block 14
#define FLASH_FMP_BLOCK_13      0x00002000  // Enable for block 13
#define FLASH_FMP_BLOCK_12      0x00001000  // Enable for block 12
#define FLASH_FMP_BLOCK_11      0x00000800  // Enable for block 11
#define FLASH_FMP_BLOCK_10      0x00000400  // Enable for block 10
#define FLASH_FMP_BLOCK_9       0x00000200  // Enable for block 9
#define FLASH_FMP_BLOCK_8       0x00000100  // Enable for block 8
#define FLASH_FMP_BLOCK_7       0x00000080  // Enable for block 7
#define FLASH_FMP_BLOCK_6       0x00000040  // Enable for block 6
#define FLASH_FMP_BLOCK_5       0x00000020  // Enable for block 5
#define FLASH_FMP_BLOCK_4       0x00000010  // Enable for block 4
#define FLASH_FMP_BLOCK_3       0x00000008  // Enable for block 3
#define FLASH_FMP_BLOCK_2       0x00000004  // Enable for block 2
#define FLASH_FMP_BLOCK_1       0x00000002  // Enable for block 1
#define FLASH_FMP_BLOCK_0       0x00000001  // Enable for block 0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USECRL register.
//
//*****************************************************************************
#define FLASH_USECRL_M          0x000000FF  // Microsecond Reload Value.
#define FLASH_USECRL_S          0

//*****************************************************************************
//
// The following are defines for the erase size of the FLASH block that is
// erased by an erase operation, and the protect size is the size of the FLASH
// block that is protected by each protection register.
//
//*****************************************************************************
#define FLASH_PROTECT_SIZE      0x00000800
#define FLASH_ERASE_SIZE        0x00000400

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMA register.
//
//*****************************************************************************
#define FLASH_FMA_OFFSET_M      0x0003FFFF  // Address Offset.
#define FLASH_FMA_OFFSET_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMD register.
//
//*****************************************************************************
#define FLASH_FMD_DATA_M        0xFFFFFFFF  // Data Value.
#define FLASH_FMD_DATA_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERDBG register.
//
//*****************************************************************************
#define FLASH_USERDBG_NW        0x80000000  // User Debug Not Written.
#define FLASH_USERDBG_DATA_M    0x7FFFFFFC  // User Data.
#define FLASH_USERDBG_DBG1      0x00000002  // Debug Control 1.
#define FLASH_USERDBG_DBG0      0x00000001  // Debug Control 0.
#define FLASH_USERDBG_DATA_S    2

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG0 register.
//
//*****************************************************************************
#define FLASH_USERREG0_NW       0x80000000  // Not Written.
#define FLASH_USERREG0_DATA_M   0x7FFFFFFF  // User Data.
#define FLASH_USERREG0_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG1 register.
//
//*****************************************************************************
#define FLASH_USERREG1_NW       0x80000000  // Not Written.
#define FLASH_USERREG1_DATA_M   0x7FFFFFFF  // User Data.
#define FLASH_USERREG1_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_RMCTL register.
//
//*****************************************************************************
#define FLASH_RMCTL_BA          0x00000001  // Boot Alias.

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_RMVER register.
//
//*****************************************************************************
#define FLASH_RMVER_CONT_M      0xFF000000  // ROM Contents.
#define FLASH_RMVER_CONT_LM     0x00000000  // Stellaris Boot Loader &
                                            // DriverLib
#define FLASH_RMVER_CONT_LM_AES 0x02000000  // Stellaris Boot Loader &
                                            // DriverLib with AES
#define FLASH_RMVER_CONT_LM_AES_SAFERTOS \
                                0x03000000  // Stellaris Boot Loader &
                                            // DriverLib with AES and SAFERTOS
#define FLASH_RMVER_SIZE_M      0x00FF0000  // ROM Size.
#define FLASH_RMVER_SIZE_11K    0x00000000  // 11KB Size
#define FLASH_RMVER_SIZE_23_75K 0x00020000  // 23.75KB Size
#define FLASH_RMVER_SIZE_28_25K 0x00030000  // 28.25KB Size
#define FLASH_RMVER_VER_M       0x0000FF00  // ROM Version.
#define FLASH_RMVER_REV_M       0x000000FF  // ROM Revision.
#define FLASH_RMVER_VER_S       8
#define FLASH_RMVER_REV_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG2 register.
//
//*****************************************************************************
#define FLASH_USERREG2_NW       0x80000000  // Not Written.
#define FLASH_USERREG2_DATA_M   0x7FFFFFFF  // User Data.
#define FLASH_USERREG2_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG3 register.
//
//*****************************************************************************
#define FLASH_USERREG3_NW       0x80000000  // Not Written.
#define FLASH_USERREG3_DATA_M   0x7FFFFFFF  // User Data.
#define FLASH_USERREG3_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FWBVAL register.
//
//*****************************************************************************
#define FLASH_FWBVAL_FWB_M      0xFFFFFFFF  // Flash Write Buffer.

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FWBN register.
//
//*****************************************************************************
#define FLASH_FWBN_DATA_M       0xFFFFFFFF  // Data.

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the FLASH_FMC
// register.
//
//*****************************************************************************
#define FLASH_FMC_WRKEY_MASK    0xFFFF0000  // FLASH write key mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the FLASH_FCRIS
// register.
//
//*****************************************************************************
#define FLASH_FCRIS_PROGRAM     0x00000002  // Programming status
#define FLASH_FCRIS_ACCESS      0x00000001  // Invalid access status

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the FLASH_FCIM
// register.
//
//*****************************************************************************
#define FLASH_FCIM_PROGRAM      0x00000002  // Programming mask
#define FLASH_FCIM_ACCESS       0x00000001  // Invalid access mask

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the FLASH_FMIS
// register.
//
//*****************************************************************************
#define FLASH_FCMISC_PROGRAM    0x00000002  // Programming status
#define FLASH_FCMISC_ACCESS     0x00000001  // Invalid access status

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the FLASH_USECRL
// register.
//
//*****************************************************************************
#define FLASH_USECRL_MASK       0x000000FF  // Clock per uSec
#define FLASH_USECRL_SHIFT      0

#endif

#endif // __HW_FLASH_H__
