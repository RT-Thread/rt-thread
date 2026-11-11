//*****************************************************************************
//
// hw_types.h - Common types and macros.
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
// This is part of revision 8264 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_TYPES_H__
#define __HW_TYPES_H__

//*****************************************************************************
//
// Define a boolean type, and values for true and false.
//
//*****************************************************************************
typedef unsigned char tBoolean;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

//*****************************************************************************
//
// Macros for hardware access, both direct and via the bit-band region.
//
//*****************************************************************************
#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((unsigned long)(x) & 0xF0000000) | 0x02000000 |                \
              (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))

//*****************************************************************************
//
// Helper Macros for determining silicon revisions, etc.
//
// These macros will be used by Driverlib at "run-time" to create necessary
// conditional code blocks that will allow a single version of the Driverlib
// "binary" code to support multiple(all) Stellaris silicon revisions.
//
// It is expected that these macros will be used inside of a standard 'C'
// conditional block of code, e.g.
//
//     if(CLASS_IS_SANDSTORM)
//     {
//         do some Sandstorm-class specific code here.
//     }
//
// By default, these macros will be defined as run-time checks of the
// appropriate register(s) to allow creation of run-time conditional code
// blocks for a common DriverLib across the entire Stellaris family.
//
// However, if code-space optimization is required, these macros can be "hard-
// coded" for a specific version of Stellaris silicon.  Many compilers will
// then detect the "hard-coded" conditionals, and appropriately optimize the
// code blocks, eliminating any "unreachable" code.  This would result in
// a smaller Driverlib, thus producing a smaller final application size, but
// at the cost of limiting the Driverlib binary to a specific Stellaris
// silicon revision.
//
//*****************************************************************************
#ifndef CLASS_IS_SANDSTORM
#define CLASS_IS_SANDSTORM                                                    \
        (((HWREG(SYSCTL_DID0) & SYSCTL_DID0_VER_M) == SYSCTL_DID0_VER_0) ||   \
         ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_VER_M | SYSCTL_DID0_CLASS_M)) == \
          (SYSCTL_DID0_VER_1 | SYSCTL_DID0_CLASS_SANDSTORM)))
#endif

#ifndef CLASS_IS_FURY
#define CLASS_IS_FURY                                                        \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_VER_M | SYSCTL_DID0_CLASS_M)) == \
         (SYSCTL_DID0_VER_1 | SYSCTL_DID0_CLASS_FURY))
#endif

#ifndef CLASS_IS_DUSTDEVIL
#define CLASS_IS_DUSTDEVIL                                                   \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_VER_M | SYSCTL_DID0_CLASS_M)) == \
         (SYSCTL_DID0_VER_1 | SYSCTL_DID0_CLASS_DUSTDEVIL))
#endif

#ifndef CLASS_IS_TEMPEST
#define CLASS_IS_TEMPEST                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_VER_M | SYSCTL_DID0_CLASS_M)) == \
         (SYSCTL_DID0_VER_1 | SYSCTL_DID0_CLASS_TEMPEST))
#endif

#ifndef CLASS_IS_FIRESTORM
#define CLASS_IS_FIRESTORM                                                   \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_VER_M | SYSCTL_DID0_CLASS_M)) == \
         (SYSCTL_DID0_VER_1 | SYSCTL_DID0_CLASS_FIRESTORM))
#endif

#ifndef CLASS_IS_BLIZZARD
#define CLASS_IS_BLIZZARD                                                    \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_VER_M | SYSCTL_DID0_CLASS_M)) == \
         (SYSCTL_DID0_VER_1 | SYSCTL_DID0_CLASS_BLIZZARD))
#endif

#ifndef REVISION_IS_A0
#define REVISION_IS_A0                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVA | SYSCTL_DID0_MIN_0))
#endif

#ifndef REVISION_IS_A1
#define REVISION_IS_A1                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVA | SYSCTL_DID0_MIN_0))
#endif

#ifndef REVISION_IS_A2
#define REVISION_IS_A2                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVA | SYSCTL_DID0_MIN_2))
#endif

#ifndef REVISION_IS_B0
#define REVISION_IS_B0                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVB | SYSCTL_DID0_MIN_0))
#endif

#ifndef REVISION_IS_B1
#define REVISION_IS_B1                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVB | SYSCTL_DID0_MIN_1))
#endif

#ifndef REVISION_IS_C0
#define REVISION_IS_C0                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVC | SYSCTL_DID0_MIN_0))
#endif

#ifndef REVISION_IS_C1
#define REVISION_IS_C1                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVC | SYSCTL_DID0_MIN_1))
#endif

#ifndef REVISION_IS_C2
#define REVISION_IS_C2                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVC | SYSCTL_DID0_MIN_2))
#endif

#ifndef REVISION_IS_C3
#define REVISION_IS_C3                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVC | SYSCTL_DID0_MIN_3))
#endif

#ifndef REVISION_IS_C5
#define REVISION_IS_C5                                                     \
        ((HWREG(SYSCTL_DID0) & (SYSCTL_DID0_MAJ_M | SYSCTL_DID0_MIN_M)) == \
         (SYSCTL_DID0_MAJ_REVC | SYSCTL_DID0_MIN_5))
#endif

//*****************************************************************************
//
// Deprecated silicon class and revision detection macros.
//
//*****************************************************************************
#ifndef DEPRECATED
#define DEVICE_IS_SANDSTORM     CLASS_IS_SANDSTORM
#define DEVICE_IS_FURY          CLASS_IS_FURY
#define DEVICE_IS_REVA2         REVISION_IS_A2
#define DEVICE_IS_REVC1         REVISION_IS_C1
#define DEVICE_IS_REVC2         REVISION_IS_C2
#endif

#endif // __HW_TYPES_H__
