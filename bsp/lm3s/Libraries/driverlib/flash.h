//*****************************************************************************
//
// flash.h - Prototypes for the flash driver.
//
// Copyright (c) 2005-2007 Luminary Micro, Inc.  All rights reserved
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
extern unsigned long FlashIntGetStatus(tBoolean bMasked);
extern void FlashIntClear(unsigned long ulIntFlags);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __FLASH_H__
