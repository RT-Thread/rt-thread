/**************************************************************************//**
 * @file     core_cmFunc.h
 * @brief    CMSIS Cortex-M Core Function Access Header File
 * @version  V1.40
 * @date     16. February 2010
 *
 * @note
 * Copyright (C) 2009-2010 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#ifndef __CORE_CMFUNC_H__
#define __CORE_CMFUNC_H__

/* ###########################  Core Function Access  ########################### */

#if defined ( __CC_ARM   ) /*------------------ RealView Compiler ----------------*/
/* ARM armcc specific functions */

 /**
 * @brief  Enable IRQ Interrupts
 *
 * Enables IRQ interrupts by clearing the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
/* intrinsic void __enable_irq();     */

 /**
 * @brief  Disable IRQ Interrupts
 *
 * Disables IRQ interrupts by setting the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
/* intrinsic void __disable_irq();    */

/**
 * @brief  Return the Control Register value
*
*  @return Control value
 *
 * Return the content of the control register
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_CONTROL(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __ASM("control");
  return(__regControl);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Set the Control Register value
 *
 * @param  control  Control value
 *
 * Set the control register
 */
#if       (__ARMCC_VERSION <  400000)
extern          void __set_CONTROL(uint32_t control);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __ASM("control");
  __regControl = control;
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Get IPSR Register value
 *
 * @return uint32_t IPSR value
 *
 * return the content of the IPSR register
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_IPSR(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __ASM("ipsr");
  return(__regIPSR);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Get APSR Register value
 *
 * @return uint32_t APSR value
 *
 * return the content of the APSR register
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_APSR(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __ASM("apsr");
  return(__regAPSR);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Get xPSR Register value
 *
 * @return uint32_t xPSR value
 *
 * return the content of the xPSR register
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_xPSR(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __ASM("xpsr");
  return(__regXPSR);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Return the Process Stack Pointer
 *
 * @return ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_PSP(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __ASM("psp");
  return(__regProcessStackPointer);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  topOfProcStack  Process Stack Pointer
 *
 * Assign the value ProcessStackPointer to the MSP
 * (process stack pointer) Cortex processor register
 */
#if       (__ARMCC_VERSION <  400000)
extern          void __set_PSP(uint32_t topOfProcStack);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __ASM("psp");
  __regProcessStackPointer = topOfProcStack;
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Return the Main Stack Pointer
 *
 * @return Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_MSP(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __ASM("msp");
  return(__regMainStackPointer);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  topOfMainStack  Main Stack Pointer
 *
 * Assign the value mainStackPointer to the MSP
 * (main stack pointer) Cortex processor register
 */
#if       (__ARMCC_VERSION <  400000)
extern          void __set_MSP(uint32_t topOfMainStack);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE void __set_MSP(uint32_t mainStackPointer)
{
  register uint32_t __regMainStackPointer     __ASM("msp");
  __regMainStackPointer = mainStackPointer;
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Return the Priority Mask value
 *
 * @return PriMask
 *
 * Return state of the priority mask bit from the priority mask register
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_PRIMASK(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __ASM("primask");
  return(__regPriMask);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Set the Priority Mask value
 *
 * @param  priMask  PriMask
 *
 * Set the priority mask bit in the priority mask register
 */
#if       (__ARMCC_VERSION <  400000)
extern          void __set_PRIMASK(uint32_t priMask);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __ASM("primask");
  __regPriMask = (priMask);
}
#endif /*  __ARMCC_VERSION  */


#if       (__CORTEX_M >= 0x03)

 /**
 * @brief  Enable FIQ Interrupts
 *
 * Enables FIQ interrupts by clearing the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
#define __enable_fault_irq                __enable_fiq

 /**
 * @brief  Disable FIQ Interrupts
 *
 * Disables FIQ interrupts by setting the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
#define __disable_fault_irq               __disable_fiq

/**
 * @brief  Return the Base Priority value
 *
 * @return BasePriority
 *
 * Return the content of the base priority register
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_BASEPRI(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __ASM("basepri");
  return(__regBasePri);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Set the Base Priority value
 *
 * @param  basePri  BasePriority
 *
 * Set the base priority register
 */
#if       (__ARMCC_VERSION <  400000)
extern          void __set_BASEPRI(uint32_t basePri);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __ASM("basepri");
  __regBasePri = (basePri & 0xff);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Return the Fault Mask value
 *
 * @return FaultMask
 *
 * Return the content of the fault mask register
 */
#if       (__ARMCC_VERSION <  400000)
extern          uint32_t __get_FAULTMASK(void);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __ASM("faultmask");
  return(__regFaultMask);
}
#endif /*  __ARMCC_VERSION  */

/**
 * @brief  Set the Fault Mask value
 *
 * @param  faultMask  faultMask value
 *
 * Set the fault mask register
 */
#if       (__ARMCC_VERSION <  400000)
extern          void __set_FAULTMASK(uint32_t faultMask);
#else  /* (__ARMCC_VERSION >= 400000) */
static __INLINE void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __ASM("faultmask");
  __regFaultMask = (faultMask & 1);
}
#endif /*  __ARMCC_VERSION  */

#endif /* (__CORTEX_M >= 0x03) */


#if       (__CORTEX_M == 0x04)

/**
 * @brief  Return the FPSCR value
 *
 * @return FloatingPointStatusControlRegister
 *
 * Return the content of the FPSCR register
 */
static __INLINE uint32_t __get_FPSCR(void)
{
#if (__FPU_PRESENT == 1)
  register uint32_t __regfpscr         __ASM("fpscr");
  return(__regfpscr);
#else
   return(0);
#endif
}

/**
 * @brief  Set the FPSCR value
 *
 * @param  fpscr  FloatingPointStatusControlRegister
 *
 * Set the FPSCR register
 */
static __INLINE void __set_FPSCR(uint32_t fpscr)
{
#if (__FPU_PRESENT == 1)
  register uint32_t __regfpscr         __ASM("fpscr");
  __regfpscr = (fpscr);
#endif
}

#endif /* (__CORTEX_M == 0x04) */


 #elif (defined (__ICCARM__)) /*---------------- ICC Compiler ---------------------*/
/* IAR iccarm specific functions */
#if defined (__ICCARM__)
  #include <intrinsics.h>                     /* IAR Intrinsics   */
#endif

#pragma diag_suppress=Pe940

 /**
 * @brief  Enable IRQ Interrupts
 *
 * Enables IRQ interrupts by clearing the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
#define __enable_irq                              __enable_interrupt

 /**
 * @brief  Disable IRQ Interrupts
 *
 * Disables IRQ interrupts by setting the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
#define __disable_irq                             __disable_interrupt

/**
 * @brief  Return the Control Register value
*
*  @return Control value
 *
 * Return the content of the control register
 */
/* intrinsic unsigned long __get_CONTROL( void ); (see intrinsic.h) */

/**
 * @brief  Set the Control Register value
 *
 * @param  control  Control value
 *
 * Set the control register
 */
/* intrinsic void __set_CONTROL( unsigned long ); (see intrinsic.h) */

/**
 * @brief  Get IPSR Register value
 *
 * @return uint32_t IPSR value
 *
 * return the content of the IPSR register
 */
static uint32_t __get_IPSR(void)
{
  __ASM("mrs r0, ipsr");
}

/**
 * @brief  Get APSR Register value
 *
 * @return uint32_t APSR value
 *
 * return the content of the APSR register
 */
/* __intrinsic unsigned long __get_APSR( void ); (see intrinsic.h) */

/**
 * @brief  Get xPSR Register value
 *
 * @return uint32_t xPSR value
 *
 * return the content of the xPSR register
 */
static uint32_t __get_xPSR(void)
{
  __ASM("mrs r0, psr");           // assembler does not know "xpsr"
}

/**
 * @brief  Return the Process Stack Pointer
 *
 * @return ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
 static uint32_t __get_PSP(void)
{
  __ASM("mrs r0, psp");
}

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  topOfProcStack  Process Stack Pointer
 *
 * Assign the value ProcessStackPointer to the MSP
 * (process stack pointer) Cortex processor register
 */
static void __set_PSP(uint32_t topOfProcStack)
{
  __ASM("msr psp, r0");
}

/**
 * @brief  Return the Main Stack Pointer
 *
 * @return Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
static uint32_t __get_MSP(void)
{
  __ASM("mrs r0, msp");
}

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  topOfMainStack  Main Stack Pointer
 *
 * Assign the value mainStackPointer to the MSP
 * (main stack pointer) Cortex processor register
 */
static void __set_MSP(uint32_t topOfMainStack)
{
  __ASM("msr msp, r0");
}

/**
 * @brief  Return the Priority Mask value
 *
 * @return PriMask
 *
 * Return state of the priority mask bit from the priority mask register
 */
/* intrinsic unsigned long __get_PRIMASK( void ); (see intrinsic.h) */

/**
 * @brief  Set the Priority Mask value
 *
 * @param  priMask  PriMask
 *
 * Set the priority mask bit in the priority mask register
 */
/* intrinsic void __set_PRIMASK( unsigned long ); (see intrinsic.h) */


#if       (__CORTEX_M >= 0x03)

 /**
 * @brief  Enable FIQ Interrupts
 *
 * Enables FIQ interrupts by clearing the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
static __INLINE void __enable_fault_irq()         { __ASM ("cpsie f"); }

 /**
 * @brief  Disable FIQ Interrupts
 *
 * Disables FIQ interrupts by setting the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
static __INLINE void __disable_fault_irq()        { __ASM ("cpsid f"); }

/**
 * @brief  Return the Base Priority value
 *
 * @return BasePriority
 *
 * Return the content of the base priority register
 */
/* intrinsic unsigned long __get_BASEPRI( void ); (see intrinsic.h) */

/**
 * @brief  Set the Base Priority value
 *
 * @param  basePri  BasePriority
 *
 * Set the base priority register
 */
/* intrinsic void __set_BASEPRI( unsigned long ); (see intrinsic.h) */

/**
 * @brief  Return the Fault Mask value
 *
 * @return FaultMask
 *
 * Return the content of the fault mask register
 */
/* intrinsic unsigned long __get_FAULTMASK( void ); (see intrinsic.h) */

/**
 * @brief  Set the Fault Mask value
 *
 * @param  faultMask  faultMask value
 *
 * Set the fault mask register
 */
/* intrinsic void __set_FAULTMASK(unsigned long); (see intrinsic.h) */

#endif /* (__CORTEX_M >= 0x03) */


#if       (__CORTEX_M == 0x04)

/**
 * @brief  Return the FPSCR value
 *
 * @return FloatingPointStatusControlRegister
 *
 * Return the content of the FPSCR register
 */
static __INLINE uint32_t __get_FPSCR(void)
{
#if (__FPU_PRESENT == 1)
  /* not yet implemented */
  return(0);
#else
  return(0);
#endif
}

/**
 * @brief  Set the FPSCR value
 *
 * @param  fpscr  FloatingPointStatusControlRegister
 *
 * Set the FPSCR register
 */
static __INLINE void __set_FPSCR(uint32_t fpscr)
{
#if (__FPU_PRESENT == 1)
  /* not yet implemented */
#endif
}

#endif /* (__CORTEX_M == 0x04) */

#pragma diag_default=Pe940


#elif (defined (__GNUC__)) /*------------------ GNU Compiler ---------------------*/
/* GNU gcc specific functions */
 /**
 * @brief  Enable IRQ Interrupts
 *
 * Enables IRQ interrupts by clearing the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
static __INLINE void __enable_irq()               { __ASM volatile ("cpsie i"); }

 /**
 * @brief  Disable IRQ Interrupts
 *
 * Disables IRQ interrupts by setting the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
static __INLINE void __disable_irq()              { __ASM volatile ("cpsid i"); }

/**
 * @brief  Return the Control Register value
*
*  @return Control value
 *
 * Return the content of the control register
 */
static __INLINE uint32_t __get_CONTROL(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Control Register value
 *
 * @param  control  Control value
 *
 * Set the control register
 */
static __INLINE void __set_CONTROL(uint32_t control)
{
  __ASM volatile ("MSR control, %0" : : "r" (control) );
}

/**
 * @brief  Get IPSR Register value
 *
 * @return uint32_t IPSR value
 *
 * return the content of the IPSR register
 */
static __INLINE uint32_t __get_IPSR(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}

/**
 * @brief  Get APSR Register value
 *
 * @return uint32_t APSR value
 *
 * return the content of the APSR register
 */
static __INLINE uint32_t __get_APSR(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}

/**
 * @brief  Get xPSR Register value
 *
 * @return uint32_t xPSR value
 *
 * return the content of the xPSR register
 */
static __INLINE uint32_t __get_xPSR(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}

/**
 * @brief  Return the Process Stack Pointer
 *
 * @return ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
static __INLINE uint32_t __get_PSP(void) __attribute__( ( naked ) );
static __INLINE uint32_t __get_PSP(void)
{
  register uint32_t result __ASM ("r0") = 0;

  __ASM volatile ("MRS %0, psp\n"
                  "BX  lr     \n"  : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  topOfProcStack  Process Stack Pointer
 *
 * Assign the value ProcessStackPointer to the MSP
 * (process stack pointer) Cortex processor register
 */
static __INLINE void __set_PSP(uint32_t topOfProcStack) __attribute__( ( naked ) );
static __INLINE void __set_PSP(uint32_t topOfProcStack)
{
  __ASM volatile ("MSR psp, %0\n"
                  "BX  lr     \n" : : "r" (topOfProcStack) );
}

/**
 * @brief  Return the Main Stack Pointer
 *
 * @return Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
static __INLINE uint32_t __get_MSP(void) __attribute__( ( naked ) );
static __INLINE uint32_t __get_MSP(void)
{
  register uint32_t result __ASM ("r0") = 0;

  __ASM volatile ("MRS %0, msp\n"
                  "BX  lr     \n"  : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  topOfMainStack  Main Stack Pointer
 *
 * Assign the value mainStackPointer to the MSP
 * (main stack pointer) Cortex processor register
 */
static __INLINE void __set_MSP(uint32_t topOfMainStack) __attribute__( ( naked ) );
static __INLINE void __set_MSP(uint32_t topOfMainStack)
{
  __ASM volatile ("MSR msp, %0\n"
                  "BX  lr     \n" : : "r" (topOfMainStack) );
}

/**
 * @brief  Return the Priority Mask value
 *
 * @return PriMask
 *
 * Return state of the priority mask bit from the priority mask register
 */
static __INLINE uint32_t __get_PRIMASK(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Priority Mask value
 *
 * @param  priMask  PriMask
 *
 * Set the priority mask bit in the priority mask register
 */
static __INLINE void __set_PRIMASK(uint32_t priMask)
{
  __ASM volatile ("MSR primask, %0" : : "r" (priMask) );
}


#if       (__CORTEX_M >= 0x03)

 /**
 * @brief  Enable FIQ Interrupts
 *
 * Enables FIQ interrupts by clearing the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
static __INLINE void __enable_fault_irq()         { __ASM volatile ("cpsie f"); }

 /**
 * @brief  Disable FIQ Interrupts
 *
 * Disables FIQ interrupts by setting the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
static __INLINE void __disable_fault_irq()        { __ASM volatile ("cpsid f"); }

/**
 * @brief  Return the Base Priority value
 *
 * @return BasePriority
 *
 * Return the content of the base priority register
 */
static __INLINE uint32_t __get_BASEPRI(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, basepri_max" : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Base Priority value
 *
 * @param  basePri  BasePriority
 *
 * Set the base priority register
 */
static __INLINE void __set_BASEPRI(uint32_t value)
{
  __ASM volatile ("MSR basepri, %0" : : "r" (value) );
}

/**
 * @brief  Return the Fault Mask value
 *
 * @return FaultMask
 *
 * Return the content of the fault mask register
 */
static __INLINE uint32_t __get_FAULTMASK(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, faultmask" : "=r" (result) );
  return(result);
}

#endif /* (__CORTEX_M >= 0x03) */

/**
 * @brief  Set the Fault Mask value
 *
 * @param  faultMask  faultMask value
 *
 * Set the fault mask register
 */
static __INLINE void __set_FAULTMASK(uint32_t faultMask)
{
  __ASM volatile ("MSR faultmask, %0" : : "r" (faultMask) );
}


#if       (__CORTEX_M == 0x04)

/**
 * @brief  Return the FPSCR value
 *
 * @return FloatingPointStatusControlRegister
 *
 * Return the content of the FPSCR register
 */
static __INLINE uint32_t __get_FPSCR(void)
{
#if (__FPU_PRESENT == 1)
  uint32_t result=0;

  __ASM volatile ("MRS %0, fpscr" : "=r" (result) );
  return(result);
#else
   return(0);
#endif
}

/**
 * @brief  Set the FPSCR value
 *
 * @param  fpscr  FloatingPointStatusControlRegister
 *
 * Set the FPSCR register
 */
static __INLINE void __set_FPSCR(uint32_t fpscr)
{
#if (__FPU_PRESENT == 1)
  __ASM volatile ("MSR control, %0" : : "r" (fpscr) );
#endif
}

#endif /* (__CORTEX_M == 0x04) */


#elif (defined (__TASKING__)) /*--------------- TASKING Compiler -----------------*/
/* TASKING carm specific functions */

/*
 * The CMSIS functions have been implemented as intrinsics in the compiler.
 * Please use "carm -?i" to get an up to date list of all instrinsics,
 * Including the CMSIS ones.
 */

#endif

#endif // __CORE_CMFUNC_H__
