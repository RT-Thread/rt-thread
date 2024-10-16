/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/*==================================================================================================
*   @file    startup_cm7.s
*   @version 5.0.0
*
*   @brief   AUTOSAR Platform - Startup file for ARM.
*   @details Startup file for ARM.
*            This file contains sample code only. It is not part of the production code deliverables
*   @addtogroup BUILD_ENV
*   @{
*
==================================================================================================*/

#ifdef MULTIPLE_IMAGE
    #define RAM_DATA_INIT_ON_ALL_CORES
    /* If this is a secodary core, it shall wait for the MSCM clock to be initialized */
    #if defined(CORE1)||defined(CORE2)||defined(CORE3)
        #define NO_MSCM_CLOCK_INIT
    #endif
#endif

#define MAIN_CORE 0
#define CORE_M7_0 0
#define CORE_M7_1 1
#define CORE_M7_2 2
#define CORE_M7_3 3

#define MCME_CTL_KEY                0x402DC000
#define MCME_PRTN1_PUPD             0x402DC304
#define MCME_PRTN1_STAT             0x402DC308
#define MCME_PRTN1_COFB0_CLKEN      0x402DC330
#define MCME_PRTN1_COFB0_STAT       0x402DC310
#define MCRGM_DES                   0x4028C000
#define MSCM_CPXNUM                 0x40260004
#define MSCM_CPXCFG2                0x40260014
#define MSCM_CPXCFG2_ITCMZ_SHIFT    (16)
#define MSCM_CPXCFG2_DTCMZ_SHIFT    (24)
#define ITCM_LOCKSTEP_END           (__INT_ITCM_START + 0x10000)
#define ITCM_DECOUPLE_END           (__INT_ITCM_START + 0x8000)
#define DTCM_LOCKSTEP_END           (__INT_DTCM_START + 0x20000)
#define DTCM_DECOUPLE_END           (__INT_DTCM_START + 0x10000)

#define MCME_MSCM_REQ               (1 << 24)
#define MCRGM_DES_F_POR             (1)
#define MCME_KEY                    0x5AF0
#define MCME_INV_KEY                0xA50F

#define CM7_ITCMCR                  0xE000EF90
#define CM7_DTCMCR                  0xE000EF94

#define SBAF_BOOT_MARKER            (0x5AA55AA5)
#define CM7_0_ENABLE_SHIFT          (0)
#define CM7_1_ENABLE_SHIFT          (1)
#define CM7_2_ENABLE_SHIFT          (2)
#define CM7_3_ENABLE_SHIFT          (8)

#define CM7_0_ENABLE                (1)

#ifndef CM7_1_ENABLE
    #define CM7_1_ENABLE            (0)
#endif
#ifndef CM7_2_ENABLE
    #define CM7_2_ENABLE            (0)
#endif
#ifndef CM7_3_ENABLE
    #define CM7_3_ENABLE            (0)
#endif
#define CM7_0_VTOR_ADDR             (__CORE0_VTOR)
#define CM7_1_VTOR_ADDR             (__CORE1_VTOR)
#define CM7_2_VTOR_ADDR             (__CORE2_VTOR)
#define CM7_3_VTOR_ADDR             (__CORE3_VTOR)
#define LC_CONFIG_ADDR              (0)

    .syntax unified
    .arch armv7-m
/* Table for copying and zeroing */
/* Copy table:
  - Table entries count
    - entry one ram start
    - entry one rom start
    - entry one rom end
    ...
    - entry n ram start
    - entry n rom start
    - entry n rom end
  Zero Table:
    - Table entries count
      - entry one ram start
      - entry one ram end
*/
.section ".init_table", "a"
  .long 6
  .long __RAM_CACHEABLE_START
  .long __ROM_CACHEABLE_START
  .long __ROM_CACHEABLE_END
  .long __RAM_NO_CACHEABLE_START
  .long __ROM_NO_CACHEABLE_START
  .long __ROM_NO_CACHEABLE_END
  .long __RAM_SHAREABLE_START
  .long __ROM_SHAREABLE_START
  .long __ROM_SHAREABLE_END
  .long __RAM_INTERRUPT_START
  .long __INIT_INTERRUPT_START
  .long __INIT_INTERRUPT_END
  .long __RAM_ITCM_START
  .long __ROM_ITCM_START
  .long __ROM_ITCM_END
  .long __RAM_DTCM_DATA_START
  .long __ROM_DTCM_DATA_START
  .long __ROM_DTCM_END
.section ".zero_table", "a"
  .long 3
  .long __BSS_SRAM_SH_START
  .long __BSS_SRAM_SH_END
  .long __BSS_SRAM_NC_START
  .long __BSS_SRAM_NC_END
  .long __BSS_SRAM_START
  .long __BSS_SRAM_END

.globl RESET_CATCH_CORE
.globl _core_loop
.section ".core_loop","ax"
.thumb

_core_loop:
    nop
    nop
    nop
    nop
    b _core_loop

/* Structure definition of image vector table:
 *
 * 1. Please note that the definition of the image vector table provided here
 *    is for demonstration purposes and is based on the S32K3xx S32M27xx Reference Manuals.
 *         - S32K3xx Reference Manual, Rev.9, Draft A, 05/2024
 *         - S32K39 and S32K37 Reference Manual, Rev. 3, 03/2024
 *         - S32M27x Reference Manual, Rev.3, 06/2024
 *
 * 2. If your SoC integrated a version of HSE,
 *    please find detail information of IVT header in HSE Reference Manual.
 *
 * 3. Detail of content of IVT table need to be defined and customized manually by user.
 *    RTD does not provide a tool to configure it.
 *    Integration detail should strictly follow Reference Manual or HSE Reference Manual.
 *    However, IVT tool available from S32 configuration tool can aid process of creation of IVT table.
 *    For detail please find information of IVT tool in help content of S32 design studio.
 */
.section ".boot_header","ax"
  .long SBAF_BOOT_MARKER /* Offset 0x00: IVT marker */
  .long (CM7_0_ENABLE << CM7_0_ENABLE_SHIFT) | (CM7_1_ENABLE << CM7_1_ENABLE_SHIFT) | (CM7_2_ENABLE << CM7_2_ENABLE_SHIFT) | (CM7_3_ENABLE << CM7_3_ENABLE_SHIFT) /* Offset 0x04: Boot configuration word */
  .long 0xffffffff /* Offset 0x08: Reserved */
  .long CM7_0_VTOR_ADDR /* Offset 0x0C: CM7_0 Start address */
  .long 0xffffffff /* Offset 0x10: Reserved */
  .long CM7_1_VTOR_ADDR /* Offset 0x14: CM7_1 Start address */
  .long 0xffffffff /* Offset 0x18: Reserved */
  .long CM7_2_VTOR_ADDR /* Offset 0x1C: CM7_2 Start address */
  .long 0xffffffff /* Offset 0x20: Reserved */
  .long LC_CONFIG_ADDR /* Offset 0x24: Lifecycle configuration pointer */
  .long CM7_3_VTOR_ADDR /* Offset 0x28: CM7_3 Start address */
  .long 0xffffffff /* Offset 0x2C: Reserved */
  .long 0xffffffff /* Offset 0x30: Reserved */
  .long 0xffffffff /* Offset 0x34: Reserved */
  .long 0xffffffff /* Offset 0x38: Reserved */
  .long 0xffffffff /* Offset 0x3C: Reserved */
  .long 0xffffffff /* Offset 0x40: Reserved */
  .long 0xffffffff /* Offset 0x44: Reserved */
  .long 0xffffffff /* Offset 0x48: Reserved */
  .long 0xffffffff /* Offset 0x4C: Reserved */
  .long 0xffffffff /* Offset 0x50: Reserved */
  .long 0xffffffff /* Offset 0x54: Reserved */
  .long 0xffffffff /* Offset 0x58: Reserved */
  .long 0xffffffff /* Offset 0x5C: Reserved */
  .long 0xffffffff /* Offset 0x60: Reserved */
  .long 0xffffffff /* Offset 0x64: Reserved */
  .long 0xffffffff /* Offset 0x68: Reserved */
  .long 0xffffffff /* Offset 0x6C: Reserved */
  .long 0xffffffff /* Offset 0x70: Reserved */
  .long 0xffffffff /* Offset 0x74: Reserved */
  .long 0xffffffff /* Offset 0x78: Reserved */
  .long 0xffffffff /* Offset 0x7C: Reserved */
  .long 0xffffffff /* Offset 0x80: Reserved */
  .long 0xffffffff /* Offset 0x84: Reserved */
  .long 0xffffffff /* Offset 0x88: Reserved */
  .long 0xffffffff /* Offset 0x8C: Reserved */
  .long 0xffffffff /* Offset 0x90: Reserved */
  .long 0xffffffff /* Offset 0x94: Reserved */
  .long 0xffffffff /* Offset 0x98: Reserved */
  .long 0xffffffff /* Offset 0x9C: Reserved */
  .long 0xffffffff /* Offset 0xA0: Reserved */
  .long 0xffffffff /* Offset 0xA4: Reserved */
  .long 0xffffffff /* Offset 0xA8: Reserved */
  .long 0xffffffff /* Offset 0xAC: Reserved */
  .long 0xffffffff /* Offset 0xB0: Reserved */
  .long 0xffffffff /* Offset 0xB4: Reserved */
  .long 0xffffffff /* Offset 0xB8: Reserved */
  .long 0xffffffff /* Offset 0xBC: Reserved */
  .long 0xffffffff /* Offset 0xC0: Reserved */
  .long 0xffffffff /* Offset 0xC4: Reserved */
  .long 0xffffffff /* Offset 0xC8: Reserved */
  .long 0xffffffff /* Offset 0xCC: Reserved */
  .long 0xffffffff /* Offset 0xD0: Reserved */
  .long 0xffffffff /* Offset 0xD4: Reserved */
  .long 0xffffffff /* Offset 0xD8: Reserved */
  .long 0xffffffff /* Offset 0xDC: Reserved */
  .long 0xffffffff /* Offset 0xE0: Reserved */
  .long 0xffffffff /* Offset 0xE4: Reserved */
  .long 0xffffffff /* Offset 0xE8: Reserved */
  .long 0xffffffff /* Offset 0xEC: Reserved */
  .long 0xffffffff /* Offset 0xF0: Reserved */
  .long 0xffffffff /* Offset 0xF4: Reserved */
  .long 0xffffffff /* Offset 0xF8: Reserved */
  .long 0xffffffff /* Offset 0xFC: Reserved */
.globl VTABLE
.section ".startup","ax"
.thumb
/************************************************************************/
/* Autosar startup code (See MCU Specification):                        */
/*                                                                      */
/*   Before the MCU driver can be initialized, a basic initialization   */
/*   of the MCU has to be executed. This MCU specific initialization is */
/*   typically executed in a start-up code. The start-up code of the    */
/*   MCU shall be executed after power up and any kind of micro-        */
/*   controller reset. It shall perform very basic and microcontroller  */
/*   specific start-up initialization and shall be kept short, because  */
/*   the MCU clock and PLL is not yet initialized. The start-up code    */
/*   shall cover MCU specific initialization, which is not part of      */
/*   other MCU services or other MCAL drivers. The following steps      */
/*   summarizes basic functionality which shall be included in the      */
/*   start-up code. They are listed for guidance, because some          */
/*   functionality might not be supported. No code will be found in     */
/*   case.                                                              */
/************************************************************************/
.set VTOR_REG, 0xE000ED08
.thumb
.thumb_func
.globl Reset_Handler
Reset_Handler:
/*****************************************************/
/* Skip normal entry point as nothing is initialized */
/*****************************************************/
/* Disable System Interrupts */
 cpsid i
 /* Initialize GPRs */
 mov   r0, #0
 mov   r1, #0
 mov   r2, #0
 mov   r3, #0
 mov   r4, #0
 mov   r5, #0
 mov   r6, #0
 mov   r7, #0

/************************************************************************/
/* Delay trap for debugger attachs before touching any peripherals      */
/* This is workaround for debugger cannot handle halt process properly, */
/* User can safely disable this delay trap using -DDISABLE_DEBUGGER_TRAP*/
/************************************************************************/
#ifndef DISABLE_DEBUGGER_TRAP
    mov r0, #100
DELAY_LOOP:
    subs r0, #1
    cmp r0,#0
    bgt DELAY_LOOP
#endif

/******************************************************************************/
/*                      MSCM initialization process                           */
/* Only Master core can initialize clock for MSCM module in multicore testing */
/******************************************************************************/
#ifndef NO_MSCM_CLOCK_INIT
InitMSCMClock:
  /* If the MSCM clock is enabled, skip this sequence */
  ldr r0, =MCME_PRTN1_COFB0_STAT
  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ
  and r1, r1, r2
  cmp r1, 0
  bne EndInitMSCMClock

  /* Step1: Enable clock in PRTN1 */
  ldr r0, =MCME_PRTN1_COFB0_CLKEN
  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ
  orr r1, r2
  str r1, [r0]

  /* Step2: Set PUPD field */
  ldr r0, =MCME_PRTN1_PUPD
  ldr r1, [r0]
  ldr r2, =1
  orr r1, r2
  str r1, [r0]

  /* Step3: Trigger update by writing valid key */
  ldr r0, =MCME_CTL_KEY
  ldr r1, =MCME_KEY
  str r1, [r0]
  ldr r1, =MCME_INV_KEY
  str r1, [r0]

  /* Step4: Wait for process to complete */
  WaitForInitProcess:
  ldr r0, =MCME_PRTN1_PUPD
  ldr r1, [r0]
  ldr r2, =1
  and r1, r1, r2
  cmp r1, 1
  beq WaitForInitProcess
#endif

  /* Step5: Check if the MSCM clock is enabled */
#ifndef SIM_TYPE_VDK
WaitForClock:
  ldr r0, =MCME_PRTN1_COFB0_STAT
  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ
  and r1, r1, r2
  cmp r1, 0
  beq WaitForClock
#endif
#ifndef NO_MSCM_CLOCK_INIT
EndInitMSCMClock:
#endif
/*******************************************************************/
/* NXP Guidance  - Init registers to avoid lock-step issues        */
/* N/A                                                             */
/*******************************************************************/

/*******************************************************************/
/* NXP Guidance  - MMU Initialization for CPU                      */
/*  TLB0 - PbridgeB                                                */
/*  TLB1 - Internal Flash                                          */
/*  TLB2 - External SRAM                                           */
/*  TLB3 - Internal SRAM                                           */
/*  TLB4 - PbridgeA                                                */
/*******************************************************************/
/******************************************************************/
/* Autosar Guidance   - The start-up code shall ensure that the   */
/* MCU internal watchdog shall not be serviced until the watchdog */
/* is initialized from the MCAL watchdog driver. This can be      */
/* done for example by increasing the watchdog service time.      */
/*                                                                */
/******************************************************************/

#ifdef MULTIPLE_CORE
/*GetCoreID*/
ldr  r0, =MSCM_CPXNUM
ldr  r1,[r0]

ldr  r0, =MAIN_CORE
cmp  r1,r0
bne  SetVTOR
#endif

/* Disable wdg0 */
ldr  r0, =0x40270010
ldr  r1, =0xC520
str  r1, [r0]
ldr  r1, =0xD928
str  r1, [r0]
ldr  r0, =0x40270000
ldr  r1, =0xFF000040
str  r1, [r0]

/******************************************************************/
/* Autosar Guidance - The start-up code shall initialize the      */
/* base addresses for interrupt and trap vector tables. These base*/
/* addresses are provided as configuration parameters or          */
/* linker/locator setting.                                        */
/******************************************************************/
SetVTOR:
/* Set VTOR to default vector table */
ldr  r0, =VTOR_REG
ldr  r1, =__INIT_INTERRUPT_START
str  r1,[r0]

/******************************************************************/
/* Autosar Guidance  - The start-up code shall initialize the     */
/* interrupt stack pointer, if an interrupt stack is              */
/* supported by the MCU. The interrupt stack pointer base address */
/* and the stack size are provided as configuration parameter or  */
/* linker/locator setting.                                        */
/*                                                                */
/******************************************************************/
/* Enable DTCM and Disable RETEN bit */
LDR r1, =CM7_DTCMCR
LDR r0, [r1]
bic r0, r0, #0x4
orr r0, r0, #0x1
str r0, [r1]
/* Enable ITCM and Disable RETEN bit */
LDR r1, =CM7_ITCMCR
LDR r0, [r1]
bic r0, r0, #0x4
orr r0, r0, #0x1
str r0, [r1]

#if defined(MULTIPLE_CORE) && !defined(MULTIPLE_IMAGE)
/*GetCoreID*/
ldr r0, =MSCM_CPXNUM
ldr r1,[r0]

ldr r0, =MAIN_CORE
cmp r1,r0
bne DTCM_Init
#endif

/******************************************************************/
/* Autosar Guidance   - If the MCU supports context save          */
/* operation, the start-up code shall initialize the memory which */
/* is used for context save operation. The maximum amount of      */
/* consecutive context save operations is provided as             */
/* configuration parameter or linker/locator setting.             */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance    - The start-up code shall initialize a     */
/* minimum amount of RAM in order to allow proper execution of    */
/* the MCU driver services and the caller of these services.      */
/******************************************************************/
RamInit:
    /* Initialize SRAM ECC */
    ldr  r0, =__RAM_INIT
    cmp  r0, 0
    /* Skip if __RAM_INIT is not set */
    beq SRAM_LOOP_END

    ldr r0, =MCRGM_DES
    ldr r1, [r0]
    ldr r2, =MCRGM_DES_F_POR
    and r1, r1, r2
    cmp r1, 0
    beq NO_INIT_STANDBY_REGION

    ldr r2, =__INT_SRAM_START
    ldr r3, =__INT_SRAM_END
    b   ZERO_64B_RAM

NO_INIT_STANDBY_REGION:
#ifdef EXTEND_LOWRAM_DERIVATIVES
    #if defined(S32K310)||defined(S32K311)||defined(S32M276)||defined(S32M274)
    ldr r2, =__BSS_SRAM_NC_START
    #else
    ldr r2, =__BSS_SRAM_START
    #endif
#else
    ldr r2, =__BSS_SRAM_START
#endif
    ldr r3, =__INT_SRAM_END

ZERO_64B_RAM:
    cmp r2, r3
    bge SRAM_LOOP_END

    movs    r0, 0
    movs    r1, 0
SRAM_LOOP:
    strd    r0, r1, [r2], #8
    cmp     r2, r3
    blt     SRAM_LOOP
SRAM_LOOP_END:

#if defined(MULTIPLE_CORE) && defined(MULTIPLE_IMAGE)
    /* Initialize SHAREABLE SRAM ECC */
    ldr  r0, =MSCM_CPXNUM
    ldr  r1,[r0]
    ldr  r0, =MAIN_CORE
    cmp  r1,r0
    bne  DTCM_Init

    ldr  r0, =__RAM_INIT
    cmp  r0, 0
    /* Skip if __RAM_INIT is not set */
    beq  DTCM_Init
    ldr  r2, =__INT_SRAM_SHARE_START
    ldr  r3, =__INT_SRAM_SHARE_END

    cmp  r2, r3
    bge  DTCM_Init
    movs r0, 0
    movs r1, 0
SHARE_RAM_LOOP:
    strd r0, r1, [r2], #8
    cmp  r2, r3
    blt  SHARE_RAM_LOOP
#endif

DTCM_Init:
    /* Initialize DTCM ECC */
    ldr  r0, =__DTCM_INIT
    cmp  r0, 0
    /* Skip if __DTCM_INIT is not set */
    beq DTCM_LOOP_END

DTCM_SIZE_PRECALCULATE_ENTRY:
    ldr r2, =MSCM_CPXCFG2
    ldr r2, [r2]
    ldr r3, =0xFF000000
    and r2, r2, r3
    lsr r2, r2, MSCM_CPXCFG2_DTCMZ_SHIFT
    cmp r2, #9
    bne DTCM_DECOUPLE
DTCM_LOCKSTEP:
    ldr r2, =__INT_DTCM_START
    ldr r3, =DTCM_LOCKSTEP_END
    b   DTCM_SIZE_PRECALCULATE_EXIT
DTCM_DECOUPLE:
    ldr r2, =__INT_DTCM_START
    ldr r3, =DTCM_DECOUPLE_END

DTCM_SIZE_PRECALCULATE_EXIT:
    cmp r2, r3
    bge DTCM_LOOP_END

    movs    r0, 0
    movs    r1, 0
DTCM_LOOP:
    strd    r0, r1, [r2], #8
    cmp     r2, r3
    blt     DTCM_LOOP
DTCM_LOOP_END:

ITCM_Init:
    /* Initialize ITCM ECC */
    ldr  r0, =__ITCM_INIT
    cmp  r0, 0
    /* Skip if __TCM_INIT is not set */
    beq ITCM_LOOP_END

ITCM_SIZE_PRECALCULATE_ENTRY:
    ldr r2, =MSCM_CPXCFG2
    ldr r2, [r2]
    ldr r3, =0x00FF0000
    and r2, r2, r3
    lsr r2, r2, MSCM_CPXCFG2_ITCMZ_SHIFT
    cmp r2, #8
    bne ITCM_DECOUPLE
ITCM_LOCKSTEP:
    ldr r2, =__INT_ITCM_START
    ldr r3, = ITCM_LOCKSTEP_END
    b   ITCM_SIZE_PRECALCULATE_EXIT
ITCM_DECOUPLE:
    ldr r2, =__INT_ITCM_START
    ldr r3, =ITCM_DECOUPLE_END

ITCM_SIZE_PRECALCULATE_EXIT:
    cmp r2, r3
    bge ITCM_LOOP_END

    movs    r0, 0
    movs    r1, 0
ITCM_LOOP:
    strd    r0, r1, [r2], #8
    cmp     r2, r3
    blt     ITCM_LOOP
ITCM_LOOP_END:

DebuggerHeldCoreLoop:
    ldr  r0, =RESET_CATCH_CORE
    ldr  r0, [r0]
    ldr  r1, =0x5A5A5A5A
    cmp  r0, r1
    beq  DebuggerHeldCoreLoop

/******************************************************************/
/* Autosar Guidance   - The start-up code shall initialize the    */
/* user stack pointer. The user stack pointer base address and    */
/* the stack size are provided as configuration parameter or      */
/* linker/locator setting.                                        */
/******************************************************************/
/* set up stack; r13 SP*/
    ldr  r0, =__Stack_dtcm_start
    msr MSP, r0

#if defined(MULTIPLE_CORE) && !defined(MULTIPLE_IMAGE)
    ldr  r0, =MSCM_CPXNUM
    ldr  r1,[r0]
    ldr  r0, =MAIN_CORE
    cmp  r1,r0
    bne  _DATA_INIT

#if (CM7_1_ENABLE == 1)
EnableCore1:
    ldr  r0, =0x402DC168     /* MC_ME.PRTN0_CORE1_STAT */
    ldr  r1, [r0]
    ldr  r2, =1
    and  r1, r1, r2
    cmp  r1, 0
    bne  EndEnableCore1

    ldr  r0, =0x402DC16C     /* MC_ME.PRTN0_CORE1_ADDR */
    ldr  r1, =__INIT_INTERRUPT_START
    str  r1, [r0]

    ldr  r0, =0x402DC160     /* MC_ME.PRTN0_CORE1_PCONF */
    ldr  r1, =1
    str  r1, [r0]

    ldr  r0, =0x402DC164     /* MC_ME.PRTN0_CORE1_PUPD */
    str  r1, [r0]

    ldr  r0, =0x402DC000     /* MC_ME.MC_ME_CTL_KEY */
    ldr  r1, =MCME_KEY
    str  r1, [r0]

    ldr  r1, =MCME_INV_KEY
    str  r1, [r0]

WaitForCore1Clock:
    ldr  r0, =0x402DC168     /* MC_ME.PRTN0_CORE1_STAT */
    ldr  r1, [r0]
    ldr  r2, =1
    and  r1, r1, r2
    cmp  r1, 0
    beq  WaitForCore1Clock
EndEnableCore1:
#endif /* CM7_1_ENABLE == 1 */

#if (CM7_2_ENABLE == 1)
EnableCore2:
    ldr  r0, =0x402DC1C8     /* MC_ME.PRTN0_CORE4_STAT */
    ldr  r1, [r0]
    ldr  r2, =1
    and  r1, r1, r2
    cmp  r1, 0
    bne  EndEnableCore2

    ldr  r0, =0x402DC1CC     /* MC_ME.PRTN0_CORE4_ADDR */
    ldr  r1, =__INIT_INTERRUPT_START
    str  r1, [r0]

    ldr  r0, =0x402DC1C0     /* MC_ME.PRTN0_CORE4_PCONF */
    ldr  r1, =1
    str  r1, [r0]

    ldr  r0, =0x402DC1C4     /* MC_ME.PRTN0_CORE4_PUPD */
    str  r1, [r0]

    ldr  r0, =0x402DC000     /* MC_ME.MC_ME_CTL_KEY */
    ldr  r1, =MCME_KEY
    str  r1, [r0]

    ldr  r1, =MCME_INV_KEY
    str  r1, [r0]

WaitForCore2Clock:
    ldr  r0, =0x402DC1C8     /* MC_ME.PRTN0_CORE4_STAT */
    ldr  r1, [r0]
    ldr  r2, =1
    and  r1, r1, r2
    cmp  r1, 0
    beq  WaitForCore2Clock
EndEnableCore2:
#endif /* CM7_2_ENABLE == 1 */

#if (CM7_3_ENABLE == 1)
EnableCore3:
    ldr  r0, =0x402DC1A8     /* MC_ME.PRTN0_CORE3_STAT */
    ldr  r1, [r0]
    ldr  r2, =1
    and  r1, r1, r2
    cmp  r1, 0
    bne  EndEnableCore3

    ldr  r0, =0x402DC1AC     /* MC_ME.PRTN0_CORE3_ADDR */
    ldr  r1, =__INIT_INTERRUPT_START
    str  r1, [r0]

    ldr  r0, =0x402DC1A0     /* MC_ME.PRTN0_CORE3_PCONF */
    ldr  r1, =1
    str  r1, [r0]

    ldr  r0, =0x402DC1A4     /* MC_ME.PRTN0_CORE3_PUPD */
    str  r1, [r0]

    ldr  r0, =0x402DC000     /* MC_ME.MC_ME_CTL_KEY */
    ldr  r1, =MCME_KEY
    str  r1, [r0]

    ldr  r1, =MCME_INV_KEY
    str  r1, [r0]

WaitForCore3Clock:
    ldr  r0, =0x402DC1A8     /* MC_ME.PRTN0_CORE3_STAT */
    ldr  r1, [r0]
    ldr  r2, =1
    and  r1, r1, r2
    cmp  r1, 0
    beq  WaitForCore3Clock
EndEnableCore3:
#endif /* CM7_3_ENABLE == 1 */

#endif /* defined(MULTIPLE_CORE) && !defined(MULTIPLE_IMAGE) */
/************************/
/* Erase ".bss Section" */
/************************/
_DATA_INIT:
/***************************************************************/
/* FPU need to enable prior to data-initialization process,in  */
/* case optimization level set to O3 compiler can utilize SIMD */
/* instruction which required involvement of FPU co-processor  */
/***************************************************************/
  bl   Enable_FPU
#ifndef RAM_DATA_INIT_ON_ALL_CORES
    /* If this is the primary core, initialize data and bss */
    ldr  r0, =MSCM_CPXNUM
    ldr  r1,[r0]

    ldr  r0, =MAIN_CORE
    cmp  r1,r0
    beq  _INIT_DATA_BSS
    bl   init_data_bss_core2
    b    SET_VTOR_TCM
#endif

_INIT_DATA_BSS:
  bl init_data_bss

SET_VTOR_TCM:
/* Set VTOR to default vector table */
ldr  r0, =VTOR_REG
ldr  r1, =__RAM_INTERRUPT_START
str  r1,[r0]


/******************************************************************/
/* Autosar Guidance   - If the MCU supports cache memory for data */
/* and/or code, it shall be initialized and enabled in the        */
/* start-up code.                                                 */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance   - The start-up code shall initialize MCU    */
/* specific features of internal memory like memory protection.   */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance   - If external memory is used, the memory    */
/* shall be initialized in the start-up code. The start-up code   */
/* shall be prepared to support different memory configurations   */
/* depending on code location. Different configuration options    */
/* shall be taken into account for code execution from            */
/* external/internal memory.                                      */
/* N/A - external memory is not used                              */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance   - The settings of the different memories    */
/* shall be provided to the start-up code as configuration        */
/* parameters.                                                    */
/* N/A - all memories are already configured                      */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance    - In the start-up code a default           */
/* initialization of the MCU clock system shall be performed      */
/* including global clock prescalers.                             */
/******************************************************************/
__SYSTEM_INIT:
  bl SystemInit

/******************************************************************/
/* Autosar Guidance   - The start-up code shall ensure that the   */
/* MCU internal watchdog shall not be serviced until the watchdog */
/* is initialized from the MCAL watchdog driver. This can be      */
/* done for example by increasing the watchdog service time.      */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance    - The start-up code shall enable           */
/* protection mechanisms for special function registers(SFRs),    */
/* if supported by the MCU.                                       */
/* N/A - will be handled by Autosar OS                            */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance    - The start-up code shall initialize all   */
/* necessary write once registers or registers common to several  */
/* drivers where one write, rather than repeated writes, to the   */
/* register is required or highly desirable.                      */
/******************************************************************/

/*********************************/
/* Set the small ro data pointer */
/*********************************/


/*********************************/
/* Set the small rw data pointer */
/*********************************/

/******************************************************************/
/* Call Main Routine                                              */
/******************************************************************/
_MAIN:
  cpsie i
  bl startup_go_to_user_mode
  bl entry

/******************************************************************/
/* Init runtime check data space                                  */
/******************************************************************/
.globl MCAL_LTB_TRACE_OFF
 MCAL_LTB_TRACE_OFF:
    nop

#ifdef CCOV_ENABLE
    /* code coverage is requested */
    bl ccov_main
#endif

    /*BKPT #1 - removed to avoid debug fault being escalated to hardfault when debugger is not attached or on VDK*/ /* last instruction for the debugger to dump results data */
.globl _end_of_eunit_test
_end_of_eunit_test:
    b .

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
.globl startup_getControlRegisterValue
startup_getControlRegisterValue:
mrs r0, CONTROL
bx r14

.globl startup_getAipsRegisterValue
startup_getAipsRegisterValue:
mrs r0, IPSR
bx r14
#endif

.align 4
.ltorg
