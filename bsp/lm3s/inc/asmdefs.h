//*****************************************************************************
//
// asmdefs.h - Macros to allow assembly code be portable among toolchains.
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

#ifndef __ASMDEFS_H__
#define __ASMDEFS_H__

//*****************************************************************************
//
// The defines required for code_red.
//
//*****************************************************************************
#ifdef codered

//
// The assembly code preamble required to put the assembler into the correct
// configuration.
//
    .syntax unified
    .thumb

//
// Section headers.
//
#define __LIBRARY__             @
#define __TEXT__                .text
#define __DATA__                .data
#define __BSS__                 .bss
#define __TEXT_NOROOT__         .text

//
// Assembler nmenonics.
//
#define __ALIGN__               .balign 4
#define __END__                 .end
#define __EXPORT__              .globl
#define __IMPORT__              .extern
#define __LABEL__               :
#define __STR__                 .ascii
#define __THUMB_LABEL__         .thumb_func
#define __WORD__                .word
#define __INLINE_DATA__

#endif // codered

//*****************************************************************************
//
// The defines required for EW-ARM.
//
//*****************************************************************************
#ifdef ewarm

//
// Section headers.
//
#define __LIBRARY__             module
#define __TEXT__                rseg CODE:CODE(2)
#define __DATA__                rseg DATA:DATA(2)
#define __BSS__                 rseg DATA:DATA(2)
#define __TEXT_NOROOT__         rseg CODE:CODE:NOROOT(2)

//
// Assembler nmenonics.
//
#define __ALIGN__               alignrom 2
#define __END__                 end
#define __EXPORT__              export
#define __IMPORT__              import
#define __LABEL__
#define __STR__                 dcb
#define __THUMB_LABEL__         thumb
#define __WORD__                dcd
#define __INLINE_DATA__         data

#endif // ewarm

//*****************************************************************************
//
// The defines required for GCC.
//
//*****************************************************************************
#if defined(gcc)

//
// The assembly code preamble required to put the assembler into the correct
// configuration.
//
    .syntax unified
    .thumb

//
// Section headers.
//
#define __LIBRARY__             @
#define __TEXT__                .text
#define __DATA__                .data
#define __BSS__                 .bss
#define __TEXT_NOROOT__         .text

//
// Assembler nmenonics.
//
#define __ALIGN__               .balign 4
#define __END__                 .end
#define __EXPORT__              .globl
#define __IMPORT__              .extern
#define __LABEL__               :
#define __STR__                 .ascii
#define __THUMB_LABEL__         .thumb_func
#define __WORD__                .word
#define __INLINE_DATA__

#endif // gcc

//*****************************************************************************
//
// The defines required for RV-MDK.
//
//*****************************************************************************
#ifdef rvmdk

//
// The assembly code preamble required to put the assembler into the correct
// configuration.
//
    thumb
    require8
    preserve8

//
// Section headers.
//
#define __LIBRARY__             ;
#define __TEXT__                area ||.text||, code, readonly, align=2
#define __DATA__                area ||.data||, data, align=2
#define __BSS__                 area ||.bss||, noinit, align=2
#define __TEXT_NOROOT__         area ||.text||, code, readonly, align=2

//
// Assembler nmenonics.
//
#define __ALIGN__               align 4
#define __END__                 end
#define __EXPORT__              export
#define __IMPORT__              import
#define __LABEL__
#define __STR__                 dcb
#define __THUMB_LABEL__
#define __WORD__                dcd
#define __INLINE_DATA__

#endif // rvmdk

//*****************************************************************************
//
// The defines required for Sourcery G++.
//
//*****************************************************************************
#if defined(sourcerygxx)

//
// The assembly code preamble required to put the assembler into the correct
// configuration.
//
    .syntax unified
    .thumb

//
// Section headers.
//
#define __LIBRARY__             @
#define __TEXT__                .text
#define __DATA__                .data
#define __BSS__                 .bss
#define __TEXT_NOROOT__         .text

//
// Assembler nmenonics.
//
#define __ALIGN__               .balign 4
#define __END__                 .end
#define __EXPORT__              .globl
#define __IMPORT__              .extern
#define __LABEL__               :
#define __STR__                 .ascii
#define __THUMB_LABEL__         .thumb_func
#define __WORD__                .word
#define __INLINE_DATA__

#endif // sourcerygxx

#endif // __ASMDEF_H__
