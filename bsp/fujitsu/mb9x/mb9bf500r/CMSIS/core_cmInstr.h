/**************************************************************************//**
 * @file     core_cmInstr.h
 * @brief    CMSIS Cortex-M Core Instruction Access Header File
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

#ifndef __CORE_CMINSTR_H__
#define __CORE_CMINSTR_H__

/* ##########################  Core Instruction Access  ######################### */

#if defined ( __CC_ARM   ) /*------------------ RealView Compiler ----------------*/
/* ARM armcc specific functions */

 /**
 * @brief  No Operation
 *
 * No Operation does nothing. This instruction can be used for code alignment 
 * purposes.
 */
#define __NOP                             __nop

 /**
 * @brief  Wait For Interrupt
 *
 * Wait For Interrupt is a hint instruction that suspends execution until 
 * one of a number of events occurs.
 */
#define __WFI                             __wfi

 /**
 * @brief  Wait For Event
 *
 * Wait For Event is a hint instruction that permits the processor to enter 
 * a low-power state until one of a number of events occurs.
 */
#define __WFE                             __wfe

 /**
 * @brief  Send Event
 *
 * Send Event is a hint instruction. It causes an event to be signaled 
 * to the CPU.
 */
#define __SEV                             __sev

 /**
 * @brief  Instruction Synchronization Barrier
 *
 * Instruction Synchronization Barrier flushes the pipeline in the processor, 
 * so that all instructions following the ISB are fetched from cache or 
 * memory, after the instruction has been completed
 */
#define __ISB()                           __isb(0xF)

 /**
 * @brief  Data Synchronization Barrier
 *
 * The DSB instruction operation acts as a special kind of Data Memory Barrier. 
 * The DSB operation completes when all explicit memory accesses before this 
 * instruction complete. 
 */
#define __DSB()                           __dsb(0xF)

 /**
 * @brief  Data Memory Barrier
 *
 * DMB ensures the apparent order of the explicit memory operations before 
 * and after the instruction, without ensuring their completion. 
 */
#define __DMB()                           __dmb(0xF)

/**
 * @brief  Reverse byte order (32 bit)
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in integer value
 */
#define __REV                             __rev

/**
 * @brief  Reverse byte order (16 bit)
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in unsigned short value
 */
#if (__ARMCC_VERSION < 400677)
extern uint32_t __REV16(uint16_t value);
#else  /* (__ARMCC_VERSION >= 400677)  */
static __INLINE __ASM uint32_t __REV16(uint16_t value)
{
  rev16 r0, r0
  bx lr
}
#endif /* __ARMCC_VERSION  */ 

/**
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */
#if (__ARMCC_VERSION < 400677)
extern int32_t __REVSH(int16_t value);
#else  /* (__ARMCC_VERSION >= 400677)  */
static __INLINE __ASM int32_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}
#endif /* __ARMCC_VERSION  */ 


#if       (__CORTEX_M >= 0x03)

/**
 * @brief  Reverse bit order of value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse bit order of value
 */
#define __RBIT                            __rbit

/**
 * @brief  LDR Exclusive (8 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 8 bit value
 */
#define __LDREXB(ptr)                     ((unsigned char ) __ldrex(ptr))

/**
 * @brief  LDR Exclusive (16 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 16 bit values
 */
#define __LDREXH(ptr)                     ((unsigned short) __ldrex(ptr))

/**
 * @brief  LDR Exclusive (32 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 32 bit values
 */
#define __LDREXW(ptr)                     ((unsigned int  ) __ldrex(ptr))

/**
 * @brief  STR Exclusive (8 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 8 bit values
 */
#define __STREXB(value, ptr)              __strex(value, ptr)

/**
 * @brief  STR Exclusive (16 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 16 bit values
 */
#define __STREXH(value, ptr)              __strex(value, ptr)

/**
 * @brief  STR Exclusive (32 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 32 bit values
 */
#define __STREXW(value, ptr)              __strex(value, ptr)

 /**
 * @brief  Remove the exclusive lock created by ldrex
 *
 * Removes the exclusive lock which is created by ldrex.
 */
#if (__ARMCC_VERSION < 400000)
extern void __CLREX(void);
#else  /* (__ARMCC_VERSION >= 400000)  */
#define __CLREX                           __clrex
#endif /* __ARMCC_VERSION  */ 

#endif /* (__CORTEX_M >= 0x03) */


#elif (defined (__ICCARM__)) /*---------------- ICC Compiler ---------------------*/
/* IAR iccarm specific functions */
#if defined (__ICCARM__)
  #include <intrinsics.h>                     /* IAR Intrinsics   */
#endif

#pragma diag_suppress=Pe940

 /**
 * @brief  No Operation
 *
 * No Operation does nothing. This instruction can be used for code alignment 
 * purposes.
 */
#define __NOP                           __no_operation

 /**
 * @brief  Wait For Interrupt
 *
 * Wait For Interrupt is a hint instruction that suspends execution until 
 * one of a number of events occurs.
 */
static __INLINE  void __WFI()           { __ASM ("wfi"); }

 /**
 * @brief  Wait For Event
 *
 * Wait For Event is a hint instruction that permits the processor to enter 
 * a low-power state until one of a number of events occurs.
 */
static __INLINE  void __WFE()           { __ASM ("wfe"); }

 /**
 * @brief  Send Event
 *
 * Send Event is a hint instruction. It causes an event to be signaled 
 * to the CPU.
 */
static __INLINE  void __SEV()           { __ASM ("sev"); }

 /**
 * @brief  Instruction Synchronization Barrier
 *
 * Instruction Synchronization Barrier flushes the pipeline in the processor, 
 * so that all instructions following the ISB are fetched from cache or 
 * memory, after the instruction has been completed
 */
/* intrinsic void __ISB(void)  (see intrinsics.h */

 /**
 * @brief  Data Synchronization Barrier
 *
 * The DSB instruction operation acts as a special kind of Data Memory Barrier. 
 * The DSB operation completes when all explicit memory accesses before this 
 * instruction complete. 
 */
/* intrinsic void __DSB(void)  (see intrinsics.h */

 /**
 * @brief  Data Memory Barrier
 *
 * DMB ensures the apparent order of the explicit memory operations before 
 * and after the instruction, without ensuring their completion. 
 */
/* intrinsic void __DMB(void)  (see intrinsics.h */

/**
 * @brief  Reverse byte order (32 bit)
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in integer value
 */
/* intrinsic uint32_t __REV(uint32_t value)  (see intrinsics.h */

/**
 * @brief  Reverse byte order (16 bit)
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in unsigned short value
 */
static uint32_t __REV16(uint16_t value)
{
  __ASM("rev16 r0, r0");
}

/**
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */
/* intrinsic uint32_t __REVSH(uint32_t value)  (see intrinsics.h */


#if       (__CORTEX_M >= 0x03)

/**
 * @brief  Reverse bit order of value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse bit order of value
 */
static uint32_t __RBIT(uint32_t value)
{
  __ASM("rbit r0, r0");
}

/**
 * @brief  LDR Exclusive (8 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 8 bit value
 */
static uint8_t __LDREXB(uint8_t *addr)
{
  __ASM("ldrexb r0, [r0]");
}

/**
 * @brief  LDR Exclusive (16 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 16 bit values
 */
static uint16_t __LDREXH(uint16_t *addr)
{
  __ASM("ldrexh r0, [r0]");
}

/**
 * @brief  LDR Exclusive (32 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 32 bit values
 */
/* intrinsic unsigned long __LDREX(unsigned long *)  (see intrinsics.h */
static uint32_t __LDREXW(uint32_t *addr)
{
  __ASM("ldrex r0, [r0]");
}

/**
 * @brief  STR Exclusive (8 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 8 bit values
 */
static uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
  __ASM("strexb r0, r0, [r1]");
}

/**
 * @brief  STR Exclusive (16 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 16 bit values
 */
static uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
  __ASM("strexh r0, r0, [r1]");
}

/**
 * @brief  STR Exclusive (32 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 32 bit values
 */
/* intrinsic unsigned long __STREX(unsigned long, unsigned long)  (see intrinsics.h */
static uint32_t __STREXW(uint32_t value, uint32_t *addr)
{
  __ASM("strex r0, r0, [r1]");
}

 /**
 * @brief  Remove the exclusive lock created by ldrex
 *
 * Removes the exclusive lock which is created by ldrex.
 */
static __INLINE  void __CLREX()                   { __ASM ("clrex"); }

#endif /* (__CORTEX_M >= 0x03) */

#pragma diag_default=Pe940


#elif (defined (__GNUC__)) /*------------------ GNU Compiler ---------------------*/
/* GNU gcc specific functions */

 /**
 * @brief  No Operation
 *
 * No Operation does nothing. This instruction can be used for code alignment 
 * purposes.
 */
static __INLINE void __NOP()                      { __ASM volatile ("nop"); }

 /**
 * @brief  Wait For Interrupt
 *
 * Wait For Interrupt is a hint instruction that suspends execution until 
 * one of a number of events occurs.
 */
static __INLINE void __WFI()                      { __ASM volatile ("wfi"); }

 /**
 * @brief  Wait For Event
 *
 * Wait For Event is a hint instruction that permits the processor to enter 
 * a low-power state until one of a number of events occurs.
 */
static __INLINE void __WFE()                      { __ASM volatile ("wfe"); }

 /**
 * @brief  Send Event
 *
 * Send Event is a hint instruction. It causes an event to be signaled 
 * to the CPU.
 */
static __INLINE void __SEV()                      { __ASM volatile ("sev"); }

 /**
 * @brief  Instruction Synchronization Barrier
 *
 * Instruction Synchronization Barrier flushes the pipeline in the processor, 
 * so that all instructions following the ISB are fetched from cache or 
 * memory, after the instruction has been completed
 */
static __INLINE void __ISB()                      { __ASM volatile ("isb"); }

 /**
 * @brief  Data Synchronization Barrier
 *
 * The DSB instruction operation acts as a special kind of Data Memory Barrier. 
 * The DSB operation completes when all explicit memory accesses before this 
 * instruction complete. 
 */
static __INLINE void __DSB()                      { __ASM volatile ("dsb"); }

 /**
 * @brief  Data Memory Barrier
 *
 * DMB ensures the apparent order of the explicit memory operations before 
 * and after the instruction, without ensuring their completion. 
 */
static __INLINE void __DMB()                      { __ASM volatile ("dmb"); }

/**
 * @brief  Reverse byte order (32 bit)
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in integer value
 */
static __INLINE uint32_t __REV(uint32_t value)
{
  uint32_t result=0;
  
  __ASM volatile ("rev %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}

/**
 * @brief  Reverse byte order (16 bit)
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in unsigned short value
 */
static __INLINE uint32_t __REV16(uint16_t value)
{
  uint32_t result=0;
  
  __ASM volatile ("rev16 %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}

/**
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */
static __INLINE int32_t __REVSH(int16_t value)
{
  uint32_t result=0;
  
  __ASM volatile ("revsh %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}


#if       (__CORTEX_M >= 0x03)

/**
 * @brief  Reverse bit order of value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse bit order of value
 */
static __INLINE uint32_t __RBIT(uint32_t value)
{
  uint32_t result=0;
  
   __ASM volatile ("rbit %0, %1" : "=r" (result) : "r" (value) );
   return(result);
}

/**
 * @brief  LDR Exclusive (8 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 8 bit value
 */
static __INLINE uint8_t __LDREXB(uint8_t *addr)
{
    uint8_t result=0;
  
   __ASM volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}

/**
 * @brief  LDR Exclusive (16 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 16 bit values
 */
static __INLINE uint16_t __LDREXH(uint16_t *addr)
{
    uint16_t result=0;
  
   __ASM volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}

/**
 * @brief  LDR Exclusive (32 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 32 bit values
 */
static __INLINE uint32_t __LDREXW(uint32_t *addr)
{
    uint32_t result=0;
  
   __ASM volatile ("ldrex %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}

/**
 * @brief  STR Exclusive (8 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 8 bit values
 */
static __INLINE uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
   uint32_t result=0;
  
   __ASM volatile ("strexb %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}

/**
 * @brief  STR Exclusive (16 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 16 bit values
 */
static __INLINE uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
   uint32_t result=0;
  
   __ASM volatile ("strexh %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}

/**
 * @brief  STR Exclusive (32 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 32 bit values
 */
static __INLINE uint32_t __STREXW(uint32_t value, uint32_t *addr)
{
   uint32_t result=0;
  
   __ASM volatile ("strex %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}

 /**
 * @brief  Remove the exclusive lock created by ldrex
 *
 * Removes the exclusive lock which is created by ldrex.
 */
static __INLINE void __CLREX()                    { __ASM volatile ("clrex"); }

#endif /* (__CORTEX_M >= 0x03) */


#elif (defined (__TASKING__)) /*--------------- TASKING Compiler -----------------*/
/* TASKING carm specific functions */

/*
 * The CMSIS functions have been implemented as intrinsics in the compiler.
 * Please use "carm -?i" to get an up to date list of all instrinsics,
 * Including the CMSIS ones.
 */

#endif

#endif // __CORE_CMINSTR_H__
