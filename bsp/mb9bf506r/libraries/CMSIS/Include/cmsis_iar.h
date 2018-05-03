/**************************************************
 *
 * This file shall be included in appropriate CMSIS header
 * files, to provide required functions and intrinsics when
 * building with the IAR C/C++ Compiler for ARM (iccarm).
 *
 * Copyright 2011 IAR Systems. All rights reserved.
 *
 * $Revision: 50409 $
 *
 **************************************************/

#ifndef __CMSIS_IAR_H__
#define __CMSIS_IAR_H__

#ifndef __ICCARM__
  #error This file should only be compiled by ICCARM
#endif

#pragma system_include

#include <intrinsics.h>

#if (__CORE__ == __ARM6M__)
  /* Avoid clash between intrinsics.h and arm_math.h when compiling for Cortex-M0. */
  #define __CLZ __cmsis_iar_clz
  #define __SSAT __cmsis_iar_ssat
#endif

#pragma diag_suppress=Pe940
#pragma diag_suppress=Pe177

#define __enable_irq    __enable_interrupt
#define __disable_irq   __disable_interrupt
#define __NOP           __no_operation

#if (__VER__ < 6020000)  /* If iccarm version is older than 6.20.0 ---------- */

#if (__VER__ < 6010002)  /* If iccarm version is older than 6.10.2 ---------- */

static uint32_t __get_APSR(void)
{
  __ASM("mrs r0, apsr");
}

static uint32_t __get_xPSR(void)
{
  __ASM("mrs r0, psr");           /* assembler does not know "xpsr" */
}

#endif                   /* __VER__ < 6010002 */

static uint32_t __get_IPSR(void)
{
  __ASM("mrs r0, ipsr");
}

static uint32_t __get_PSR(void)
{
  __ASM("mrs r0, psr");
}

static uint32_t __get_PSP(void)
{
  __ASM("mrs r0, psp");
}
 
static void __set_PSP(uint32_t topOfProcStack)
{
  __ASM("msr psp, r0");
}

static uint32_t __get_MSP(void)
{
  __ASM("mrs r0, msp");
}
 
static void __set_MSP(uint32_t topOfMainStack)
{
  __ASM("msr msp, r0");
}

static __INLINE  void __WFI(void)
{
  __ASM ("wfi");
}

static __INLINE  void __WFE(void)
{
  __ASM ("wfe");
}

static __INLINE  void __SEV(void)
{
  __ASM ("sev");
}

static uint32_t __REV16(uint32_t value)
{
  __ASM("rev16 r0, r0");
}

#else                   /* __VER__ < 6020000 */

static uint32_t __get_xPSR(void)
{
  return __get_PSR();   /* __get_PSR() intrinsic introduced in iccarm 6.20 */
}

#endif                   /* __VER__ < 6020000 */

#if (__CORTEX_M >= 0x03)   /* __CORTEX_M is defined in core_cm0.h, core_cm3.h and core_cm4.h. */

#if (__VER__ < 6020000)  /* If iccarm version is older than 6.20.0 ---------- */

static __INLINE void __enable_fault_irq(void)
{
  __ASM ("cpsie f");
}

static __INLINE void __disable_fault_irq(void)
{
  __ASM ("cpsid f");
}

static uint32_t __RBIT(uint32_t value)
{
  __ASM("rbit r0, r0");
}

static uint8_t __LDREXB(volatile uint8_t *addr)
{
  __ASM("ldrexb r0, [r0]");
}

static uint16_t __LDREXH(volatile uint16_t *addr)
{
  __ASM("ldrexh r0, [r0]");
}

static uint32_t __LDREXW(volatile uint32_t *addr)
{
  __ASM("ldrex r0, [r0]");
}

static uint32_t __STREXB(uint8_t value, volatile uint8_t *addr)
{
  __ASM("strexb r0, r0, [r1]");
}

static uint32_t __STREXH(uint16_t value, volatile uint16_t *addr)
{
  __ASM("strexh r0, r0, [r1]");
}

static uint32_t __STREXW(uint32_t value, volatile uint32_t *addr)
{
  __ASM("strex r0, r0, [r1]");
}

static __INLINE void __CLREX(void)
{
  __ASM ("clrex");
}

#else                  /* __VER__ >= 6020000 --------------------- */

#define __LDREXW        __LDREX
#define __STREXW        __STREX
#define __enable_fault_irq __enable_fiq
#define __disable_fault_irq __disable_fiq

#endif                 /* __VER__ < 6020000 */

#endif /* (__CORTEX_M >= 0x03) */

#if (__CORTEX_M == 0x04)   /* __CORTEX_M is defined in core_cm0.h, core_cm3.h and core_cm4.h. */

#if (__VER__ < 6020000)  /* If iccarm version is older than 6.20.0 ---------- */

static uint32_t __get_FPSCR(void)
{
#if (__FPU_PRESENT == 1)   /* __FPU_PRESENT is defined in the device header file, if present in current device. */
  __ASM("vmrs r0, fpscr"); 
#else
  return(0);
#endif
}

static void __set_FPSCR(uint32_t fpscr)
{
#if (__FPU_PRESENT == 1)   /* __FPU_PRESENT is defined in the device header file, if present in current device. */
  __ASM("vmsr fpscr, r0");
#endif
}

#endif                 /* __VER__ < 6020000 */

#endif /* (__CORTEX_M == 0x04) */

static __INLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  return (op1 >> op2) | (op1 << ((sizeof(op1)*8)-op2));
}

#pragma diag_default=Pe940
#pragma diag_default=Pe177

#endif /* __CMSIS_IAR_H__ */
