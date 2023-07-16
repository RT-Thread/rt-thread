//*****************************************************************************
//
// bl_flash.h - Flash programming functions used by the boot loader.
//
// Copyright (c) 2006-2017 Texas Instruments Incorporated.  All rights reserved.
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

#ifndef __BL_FLASH_H__
#define __BL_FLASH_H__

#include "ti/devices/msp432e4/driverlib/driverlib.h"


//*****************************************************************************
//
// Basic functions for erasing and programming internal flash.
//
//*****************************************************************************
extern void BLInternalFlashErase(uint32_t ui32Address);
extern void BLInternalFlashProgram(uint32_t ui32DstAddr, uint8_t *pui8SrcData,
                                   uint32_t ui32Length);
extern uint32_t BLInternalFlashSizeGet(void);
extern uint32_t BLInternalFlashStartAddrCheck(uint32_t ui32Addr,
                                              uint32_t ui32ImgSize);
extern uint32_t BLInternalFlashErrorCheck(void);
extern void BLInternalFlashErrorClear(void);

//*****************************************************************************
//
// If the user has not specified which flash programming functions to use,
// default to the basic, internal flash functions on Sandstorm, Fury and
// DustDevil parts or the ROM-resident function for Tempest-class parts.
//
//*****************************************************************************
#ifndef BL_FLASH_ERASE_FN_HOOK
#define BL_FLASH_ERASE_FN_HOOK(ui32Address)                                   \
        {                                                                     \
            FLASH_CTRL->FMA = (ui32Address);                                  \
            FLASH_CTRL->FMC = FLASH_FMC_WRKEY | FLASH_FMC_ERASE;              \
            while(FLASH_CTRL->FMC & FLASH_FMC_ERASE)                          \
            {                                                                 \
            }                                                                 \
        }
#else
extern void BL_FLASH_ERASE_FN_HOOK(uint32_t ui32Address);
#endif

#ifndef BL_FLASH_PROGRAM_FN_HOOK
#ifdef ROM_FlashProgram
#define BL_FLASH_PROGRAM_FN_HOOK(ui32DstAddr, pui8SrcData, ui32Length)        \
        ROM_FlashProgram((uint32_t *)pui8SrcData, ui32DstAddr,                \
                         (((ui32Length) + 3) & ~3))
#else
#define BL_FLASH_PROGRAM_FN_HOOK(ui32DstAddr, pui8SrcData, ui32Length)        \
        {                                                                     \
            uint32_t ui32FlashProgLoop;                                       \
                                                                              \
            for(ui32FlashProgLoop = 0; ui32FlashProgLoop < (ui32Length);      \
                ui32FlashProgLoop += 4)                                       \
            {                                                                 \
                FLASH_CTRL->FMA = (ui32DstAddr) + ui32FlashProgLoop;          \
                FLASH_CTRL->FMD = *(uint32_t *)((pui8SrcData) +               \
                                                 ui32FlashProgLoop);          \
                FLASH_CTRL->FMC = FLASH_FMC_WRKEY | FLASH_FMC_WRITE;          \
                while(FLASH_CTRL->FMC & FLASH_FMC_WRITE)                      \
                {                                                             \
                }                                                             \
            }                                                                 \
        }
#endif
#else
extern uint32_t BL_FLASH_PROGRAM_FN_HOOK(uint32_t ui32DstAddr,
                                         uint8_t *pui8SrcData,
                                         uint32_t ui32Length);
#endif

#ifndef BL_FLASH_CL_ERR_FN_HOOK
#define BL_FLASH_CL_ERR_FN_HOOK() FLASH_CTRL->FCMISC = FLASH_FCMISC_AMISC
#else
extern void BL_FLASH_CL_ERR_FN_HOOK(void);
#endif

#ifndef BL_FLASH_ERROR_FN_HOOK
#define BL_FLASH_ERROR_FN_HOOK()  (FLASH_CTRL->FCRIS & FLASH_FCRIS_ARIS)
#else
extern uint32_t BL_FLASH_ERROR_FN_HOOK(void);
#endif

#ifndef BL_FLASH_SIZE_FN_HOOK
#define BL_FLASH_SIZE_FN_HOOK()                                               \
        (((FLASH_CTRL->PP & FLASH_PP_SIZE_M) + 1) << 11)
#else
extern uint32_t BL_FLASH_SIZE_FN_HOOK(void);
#endif

#ifndef BL_FLASH_END_FN_HOOK
#define BL_FLASH_END_FN_HOOK()                                               \
        (((FLASH_CTRL->PP & FLASH_PP_SIZE_M) + 1) << 11)
#else
extern uint32_t BL_FLASH_END_FN_HOOK(void);
#endif

#ifndef BL_FLASH_AD_CHECK_FN_HOOK
#define BL_FLASH_AD_CHECK_FN_HOOK(ui32Addr, ui32Size)                         \
        BLInternalFlashStartAddrCheck((ui32Addr), (ui32Size))
#else
extern uint32_t BL_FLASH_AD_CHECK_FN_HOOK(uint32_t ui32Address,
                                          uint32_t ui32Length);
#endif

#endif // __BL_FLASH_H__
