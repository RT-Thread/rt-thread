//*****************************************************************************
//
// bl_hooks.h - Definitions for the application-specific hook function.
//
// Copyright (c) 2009-2017 Texas Instruments Incorporated.  All rights reserved.
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

#ifndef __BL_HOOKS_H__
#define __BL_HOOKS_H__

//*****************************************************************************
//
// Prototypes for any application-specific hook functions that are defined in
// bl_config.h.  Note that the low level flash programming hooks are handled
// in bl_flash.h to allow us to define macros for internal flash programming
// in the normal case where no override functions are provided.
//
//*****************************************************************************
#ifdef BL_HW_INIT_FN_HOOK
extern void BL_HW_INIT_FN_HOOK(void);
#endif
#ifdef BL_INIT_FN_HOOK
extern void BL_INIT_FN_HOOK(void);
#endif
#ifdef BL_REINIT_FN_HOOK
extern void BL_REINIT_FN_HOOK(void);
#endif
#ifdef BL_START_FN_HOOK
extern void BL_START_FN_HOOK(void);
#endif
#ifdef BL_PROGRESS_FN_HOOK
extern void BL_PROGRESS_FN_HOOK(uint32_t ui32Completed, uint32_t ui32Total);
#endif
#ifdef BL_END_FN_HOOK
extern void BL_END_FN_HOOK(void);
#endif
#ifdef BL_DECRYPT_FN_HOOK
extern void BL_DECRYPT_FN_HOOK(uint8_t *pui8Buffer, uint32_t ui32Size);
#endif
#ifdef BL_CHECK_UPDATE_FN_HOOK
extern uint32_t BL_CHECK_UPDATE_FN_HOOK(void);
#endif

//*****************************************************************************
//
// If ENABLE_DECRYPTION is defined but we don't have a hook function set for
// decryption, default to the previous behavior which calls the stub function
// DecryptData.
//
//*****************************************************************************
#if (defined ENABLE_DECRYPTION) && !(defined BL_DECRYPT_FN_HOOK)
#define BL_DECRYPT_FN_HOOK      DecryptData
#endif

#endif // __BL_HOOKS_H__
