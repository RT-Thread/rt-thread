//*****************************************************************************
//
// flash.h - Prototypes for the flash driver.
//
// Copyright (c) 2005-2011 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 8264 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __FLASH_H__
#define __FLASH_H__

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
// Values that can be passed to FlashProtectSet(), and returned by
// FlashProtectGet().
//
//*****************************************************************************
typedef enum
{
    FlashReadWrite,                         // Flash can be read and written
    FlashReadOnly,                          // Flash can only be read
    FlashExecuteOnly                        // Flash can only be executed
}
tFlashProtection;

//*****************************************************************************
//
// Values passed to FlashIntEnable(), FlashIntDisable() and FlashIntClear() and
// returned from FlashIntStatus().
//
//*****************************************************************************
#define FLASH_INT_PROGRAM     0x00000002 // Programming Interrupt Mask
#define FLASH_INT_ACCESS      0x00000001 // Access Interrupt Mask
#define FLASH_INT_EEPROM      0x00000004 // EEPROM Interrupt Mask
#define FLASH_INT_VOLTAGE_ERR 0x00000200 // Voltage Error Interrupt Mask
#define FLASH_INT_DATA_ERR    0x00000400 // Invalid Data Interrupt Mask
#define FLASH_INT_ERASE_ERR   0x00000800 // Erase Error Interrupt Mask
#define FLASH_INT_PROGRAM_ERR 0x00002000 // Program Verify Error Interrupt Mask

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern unsigned long FlashUsecGet(void);
extern void FlashUsecSet(unsigned long ulClocks);
extern long FlashErase(unsigned long ulAddress);
extern long FlashProgram(unsigned long *pulData, unsigned long ulAddress,
                         unsigned long ulCount);
extern tFlashProtection FlashProtectGet(unsigned long ulAddress);
extern long FlashProtectSet(unsigned long ulAddress,
                            tFlashProtection eProtect);
extern long FlashProtectSave(void);
extern long FlashUserGet(unsigned long *pulUser0, unsigned long *pulUser1);
extern long FlashUserSet(unsigned long ulUser0, unsigned long ulUser1);
extern long FlashUserSave(void);
extern void FlashIntRegister(void (*pfnHandler)(void));
extern void FlashIntUnregister(void);
extern void FlashIntEnable(unsigned long ulIntFlags);
extern void FlashIntDisable(unsigned long ulIntFlags);
extern unsigned long FlashIntStatus(tBoolean bMasked);
extern void FlashIntClear(unsigned long ulIntFlags);

//*****************************************************************************
//
// Deprecated function names.  These definitions ensure backwards compatibility
// but new code should avoid using deprecated function names since these will
// be removed at some point in the future.
//
//*****************************************************************************
#ifndef DEPRECATED
#define FlashIntGetStatus       FlashIntStatus
#endif

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __FLASH_H__
