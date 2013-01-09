/******************************************************************************
 * @file:    core_cm0.c
 * @purpose: CMSIS Cortex-M0 Core Peripheral Access Layer Source File
 * @version: V1.10
 * @date:    24. Feb. 2009
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-Mx 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/



#include <stdint.h>


/* define compiler specific symbols */
#if defined   ( __CC_ARM   )
  #define __ASM            __asm           /*!< asm keyword for armcc          */
  #define __INLINE         __inline        /*!< inline keyword for armcc        */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm            /*!< asm keyword for iarcc           */
  #define __INLINE        inline           /*!< inline keyword for iarcc. Only avaiable in High optimization mode! */
  #define __nop           __no_operation   /*!< no operation intrinsic in iarcc */

#elif defined (  __GNUC__  )
  #define __ASM             asm            /*!< asm keyword for gcc            */
  #define __INLINE          inline         /*!< inline keyword for gcc         */
#endif



#if defined ( __CC_ARM   ) /*------------------RealView Compiler -----------------*/

/**
 * @brief  Return the Process Stack Pointer
 *
 * @param  none
 * @return uint32_t ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
__ASM uint32_t __get_PSP(void)
{
  mrs r0, psp
  bx lr
}

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  uint32_t Process Stack Pointer
 * @return none
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */
__ASM void __set_PSP(uint32_t topOfProcStack)
{
  msr psp, r0
  bx lr
}

/**
 * @brief  Return the Main Stack Pointer
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
__ASM uint32_t __get_MSP(void)
{
  mrs r0, msp
  bx lr
}

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  uint32_t Main Stack Pointer
 * @return none
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */
__ASM void __set_MSP(uint32_t mainStackPointer)
{
  msr msp, r0
  bx lr
}

/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  uint16_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in unsigned short value
 */
__ASM uint32_t __REV16(uint16_t value)
{
  rev16 r0, r0
  bx lr
}

/**
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param  int16_t value to reverse
 * @return int32_t reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */
__ASM int32_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}


#if (__ARMCC_VERSION < 400000)


/**
 * @brief  Return the Priority Mask value
 *
 * @param  none
 * @return uint32_t PriMask
 *
 * Return the state of the priority mask bit from the priority mask
 * register
 */
__ASM uint32_t __get_PRIMASK(void)
{
  mrs r0, primask
  bx lr
}

/**
 * @brief  Set the Priority Mask value
 *
 * @param  uint32_t PriMask
 * @return none
 *
 * Set the priority mask bit in the priority mask register
 */
__ASM void __set_PRIMASK(uint32_t priMask)
{
  msr primask, r0
  bx lr
}


/**
 * @brief  Return the Control Register value
 * 
 * @param  none
 * @return uint32_t Control value
 *
 * Return the content of the control register
 */
__ASM uint32_t  __get_CONTROL(void)
{
  mrs r0, control
  bx lr
}

/**
 * @brief  Set the Control Register value
 *
 * @param  uint32_t Control value
 * @return none
 *
 * Set the control register
 */
__ASM void __set_CONTROL(uint32_t control)
{
  msr control, r0
  bx lr
}

#endif /* __ARMCC_VERSION  */ 


#elif (defined (__ICCARM__)) /*------------------ ICC Compiler -------------------*/
#pragma diag_suppress=Pe940

/**
 * @brief  Return the Process Stack Pointer
 *
 * @param  none
 * @return uint32_t ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
uint32_t __get_PSP(void)
{
  __ASM("mrs r0, psp");
  __ASM("bx lr");
}

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  uint32_t Process Stack Pointer
 * @return none
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */
void __set_PSP(uint32_t topOfProcStack)
{
  __ASM("msr psp, r0");
  __ASM("bx lr");
}

/**
 * @brief  Return the Main Stack Pointer
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
uint32_t __get_MSP(void)
{
  __ASM("mrs r0, msp");
  __ASM("bx lr");
}

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  uint32_t Main Stack Pointer
 * @return none
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */
void __set_MSP(uint32_t topOfMainStack)
{
  __ASM("msr msp, r0");
  __ASM("bx lr");
}

/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  uint16_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in unsigned short value
 */
uint32_t __REV16(uint16_t value)
{
  __ASM("rev16 r0, r0");
  __ASM("bx lr");
}


#pragma diag_default=Pe940




#elif (defined (__GNUC__)) /*------------------ GNU Compiler ---------------------*/

/**
 * @brief  Return the Process Stack Pointer
 *
 * @param  none
 * @return uint32_t ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
uint32_t __get_PSP(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  uint32_t Process Stack Pointer
 * @return none
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */
void __set_PSP(uint32_t topOfProcStack)
{
  __ASM volatile ("MSR psp, %0" : : "r" (topOfProcStack) );
}

/**
 * @brief  Return the Main Stack Pointer
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
uint32_t __get_MSP(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  uint32_t Main Stack Pointer
 * @return none
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */
void __set_MSP(uint32_t topOfMainStack)
{
  __ASM volatile ("MSR msp, %0" : : "r" (topOfMainStack) );
}


/**
 * @brief  Return the Priority Mask value
 *
 * @param  none
 * @return uint32_t PriMask
 *
 * Return the state of the priority mask bit from the priority mask
 * register
 */
uint32_t __get_PRIMASK(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Priority Mask value
 *
 * @param  uint32_t PriMask
 * @return none
 *
 * Set the priority mask bit in the priority mask register
 */
void __set_PRIMASK(uint32_t priMask)
{
  __ASM volatile ("MSR primask, %0" : : "r" (priMask) );
}


/**
 * @brief  Reverse byte order in integer value
 *
 * @param  uint32_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in integer value
 */
uint32_t __REV(uint32_t value)
{
  uint32_t result=0;
  
  __ASM volatile ("rev %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}

/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  uint16_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in unsigned short value
 */
uint32_t __REV16(uint16_t value)
{
  uint32_t result=0;
  
  __ASM volatile ("rev16 %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}

/**
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param  int32_t value to reverse
 * @return int32_t reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */
int32_t __REVSH(int16_t value)
{
  uint32_t result=0;
  
  __ASM volatile ("revsh %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}


/**
 * @brief  Return the Control Register value
 * 
 * @param  none
 * @return uint32_t Control value
 *
 * Return the content of the control register
 */
uint32_t __get_CONTROL(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}

/**
 * @brief  Set the Control Register value
 *
 * @param  uint32_t Control value
 * @return none
 *
 * Set the control register
 */
void __set_CONTROL(uint32_t control)
{
  __ASM volatile ("MSR control, %0" : : "r" (control) );
}

#endif

















