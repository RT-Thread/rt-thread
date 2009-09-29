/******************************************************************************
 * @file:    core_cm3.h
 * @purpose: CMSIS Cortex-M3 Core Peripheral Access Layer Header File
 * @version: V1.20
 * @date:    22. May 2009
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

#ifndef __CM3_CORE_H__
#define __CM3_CORE_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#define __CM3_CMSIS_VERSION_MAIN  (0x01)                                                       /*!< [31:16] CMSIS HAL main version */
#define __CM3_CMSIS_VERSION_SUB   (0x20)                                                       /*!< [15:0]  CMSIS HAL sub version  */
#define __CM3_CMSIS_VERSION       ((__CM3_CMSIS_VERSION_MAIN << 16) | __CM3_CMSIS_VERSION_SUB) /*!< CMSIS HAL version number       */

#define __CORTEX_M                (0x03)                                                       /*!< Cortex core                    */

/**
 *  Lint configuration \n
 *  ----------------------- \n
 *
 *  The following Lint messages will be suppressed and not shown: \n
 *  \n
 *    --- Error 10: --- \n
 *    register uint32_t __regBasePri         __asm("basepri"); \n
 *    Error 10: Expecting ';' \n
 *     \n
 *    --- Error 530: --- \n
 *    return(__regBasePri); \n
 *    Warning 530: Symbol '__regBasePri' (line 264) not initialized \n
 *     \n
 *    --- Error 550: --- \n
 *      __regBasePri = (basePri & 0x1ff); \n
 *    } \n
 *    Warning 550: Symbol '__regBasePri' (line 271) not accessed \n
 *     \n
 *    --- Error 754: --- \n
 *    uint32_t RESERVED0[24]; \n
 *    Info 754: local structure member '<some, not used in the HAL>' (line 109, file ./cm3_core.h) not referenced \n
 *     \n
 *    --- Error 750: --- \n
 *    #define __CM3_CORE_H__ \n
 *    Info 750: local macro '__CM3_CORE_H__' (line 43, file./cm3_core.h) not referenced \n
 *     \n
 *    --- Error 528: --- \n
 *    static __INLINE void NVIC_DisableIRQ(uint32_t IRQn) \n
 *    Warning 528: Symbol 'NVIC_DisableIRQ(unsigned int)' (line 419, file ./cm3_core.h) not referenced \n
 *     \n
 *    --- Error 751: --- \n
 *    } InterruptType_Type; \n
 *    Info 751: local typedef 'InterruptType_Type' (line 170, file ./cm3_core.h) not referenced \n
 * \n
 * \n
 *    Note:  To re-enable a Message, insert a space before 'lint' * \n
 *
 */

/*lint -save */
/*lint -e10  */
/*lint -e530 */
/*lint -e550 */
/*lint -e754 */
/*lint -e750 */
/*lint -e528 */
/*lint -e751 */


#include <stdint.h>                           /* Include standard types */

#if defined (__ICCARM__)
  #include <intrinsics.h>                     /* IAR Intrinsics   */
#endif


#ifndef __NVIC_PRIO_BITS
  #define __NVIC_PRIO_BITS    4               /*!< standard definition for NVIC Priority Bits */
#endif




/**
 * IO definitions
 *
 * define access restrictions to peripheral registers
 */

#ifdef __cplusplus
#define     __I     volatile                  /*!< defines 'read only' permissions      */
#else
#define     __I     volatile const            /*!< defines 'read only' permissions      */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */



/*******************************************************************************
 *                 Register Abstraction
 ******************************************************************************/


/* System Reset */
#define NVIC_VECTRESET              0         /*!< Vector Reset Bit             */
#define NVIC_SYSRESETREQ            2         /*!< System Reset Request         */
#define NVIC_AIRCR_VECTKEY    (0x5FA << 16)   /*!< AIRCR Key for write access   */
#define NVIC_AIRCR_ENDIANESS        15        /*!< Endianess                    */

/* Core Debug */
#define CoreDebug_DEMCR_TRCENA (1 << 24)      /*!< DEMCR TRCENA enable          */
#define ITM_TCR_ITMENA              1         /*!< ITM enable                   */




/* memory mapping struct for Nested Vectored Interrupt Controller (NVIC) */
typedef struct
{
  __IO uint32_t ISER[8];                      /*!< Interrupt Set Enable Register            */
       uint32_t RESERVED0[24];
  __IO uint32_t ICER[8];                      /*!< Interrupt Clear Enable Register          */
       uint32_t RSERVED1[24];
  __IO uint32_t ISPR[8];                      /*!< Interrupt Set Pending Register           */
       uint32_t RESERVED2[24];
  __IO uint32_t ICPR[8];                      /*!< Interrupt Clear Pending Register         */
       uint32_t RESERVED3[24];
  __IO uint32_t IABR[8];                      /*!< Interrupt Active bit Register            */
       uint32_t RESERVED4[56];
  __IO uint8_t  IP[240];                      /*!< Interrupt Priority Register, 8Bit wide   */
       uint32_t RESERVED5[644];
  __O  uint32_t STIR;                         /*!< Software Trigger Interrupt Register      */
}  NVIC_Type;


/* memory mapping struct for System Control Block */
typedef struct
{
  __I  uint32_t CPUID;                        /*!< CPU ID Base Register                                     */
  __IO uint32_t ICSR;                         /*!< Interrupt Control State Register                         */
  __IO uint32_t VTOR;                         /*!< Vector Table Offset Register                             */
  __IO uint32_t AIRCR;                        /*!< Application Interrupt / Reset Control Register           */
  __IO uint32_t SCR;                          /*!< System Control Register                                  */
  __IO uint32_t CCR;                          /*!< Configuration Control Register                           */
  __IO uint8_t  SHP[12];                      /*!< System Handlers Priority Registers (4-7, 8-11, 12-15)    */
  __IO uint32_t SHCSR;                        /*!< System Handler Control and State Register                */
  __IO uint32_t CFSR;                         /*!< Configurable Fault Status Register                       */
  __IO uint32_t HFSR;                         /*!< Hard Fault Status Register                               */
  __IO uint32_t DFSR;                         /*!< Debug Fault Status Register                              */
  __IO uint32_t MMFAR;                        /*!< Mem Manage Address Register                              */
  __IO uint32_t BFAR;                         /*!< Bus Fault Address Register                               */
  __IO uint32_t AFSR;                         /*!< Auxiliary Fault Status Register                          */
  __I  uint32_t PFR[2];                       /*!< Processor Feature Register                               */
  __I  uint32_t DFR;                          /*!< Debug Feature Register                                   */
  __I  uint32_t ADR;                          /*!< Auxiliary Feature Register                               */
  __I  uint32_t MMFR[4];                      /*!< Memory Model Feature Register                            */
  __I  uint32_t ISAR[5];                      /*!< ISA Feature Register                                     */
} SCB_Type;


/* memory mapping struct for SysTick */
typedef struct
{
  __IO uint32_t CTRL;                         /*!< SysTick Control and Status Register */
  __IO uint32_t LOAD;                         /*!< SysTick Reload Value Register       */
  __IO uint32_t VAL;                          /*!< SysTick Current Value Register      */
  __I  uint32_t CALIB;                        /*!< SysTick Calibration Register        */
} SysTick_Type;


/* memory mapping structur for ITM */
typedef struct
{
  __O  union  
  {
    __O  uint8_t    u8;                       /*!< ITM Stimulus Port 8-bit               */
    __O  uint16_t   u16;                      /*!< ITM Stimulus Port 16-bit              */
    __O  uint32_t   u32;                      /*!< ITM Stimulus Port 32-bit              */
  }  PORT [32];                               /*!< ITM Stimulus Port Registers           */
       uint32_t RESERVED0[864];
  __IO uint32_t TER;                          /*!< ITM Trace Enable Register             */
       uint32_t RESERVED1[15];
  __IO uint32_t TPR;                          /*!< ITM Trace Privilege Register          */
       uint32_t RESERVED2[15];
  __IO uint32_t TCR;                          /*!< ITM Trace Control Register            */
       uint32_t RESERVED3[29];
  __IO uint32_t IWR;                          /*!< ITM Integration Write Register        */
  __IO uint32_t IRR;                          /*!< ITM Integration Read Register         */
  __IO uint32_t IMCR;                         /*!< ITM Integration Mode Control Register */
       uint32_t RESERVED4[43];
  __IO uint32_t LAR;                          /*!< ITM Lock Access Register              */
  __IO uint32_t LSR;                          /*!< ITM Lock Status Register              */
       uint32_t RESERVED5[6];
  __I  uint32_t PID4;                         /*!< ITM Product ID Registers              */
  __I  uint32_t PID5;
  __I  uint32_t PID6;
  __I  uint32_t PID7;
  __I  uint32_t PID0;
  __I  uint32_t PID1;
  __I  uint32_t PID2;
  __I  uint32_t PID3;
  __I  uint32_t CID0;
  __I  uint32_t CID1;
  __I  uint32_t CID2;
  __I  uint32_t CID3;
} ITM_Type;


/* memory mapped struct for Interrupt Type */
typedef struct
{
       uint32_t RESERVED0;
  __I  uint32_t ICTR;                         /*!< Interrupt Control Type Register  */
#if ((defined __CM3_REV) && (__CM3_REV >= 0x200))
  __IO uint32_t ACTLR;                        /*!< Auxiliary Control Register       */
#else
       uint32_t RESERVED1;
#endif
} InterruptType_Type;


/* Memory Protection Unit */
#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1)
typedef struct
{
  __I  uint32_t TYPE;                         /*!< MPU Type Register                               */
  __IO uint32_t CTRL;                         /*!< MPU Control Register                            */
  __IO uint32_t RNR;                          /*!< MPU Region RNRber Register                      */
  __IO uint32_t RBAR;                         /*!< MPU Region Base Address Register                */
  __IO uint32_t RASR;                         /*!< MPU Region Attribute and Size Register          */
  __IO uint32_t RBAR_A1;                      /*!< MPU Alias 1 Region Base Address Register        */
  __IO uint32_t RASR_A1;                      /*!< MPU Alias 1 Region Attribute and Size Register  */
  __IO uint32_t RBAR_A2;                      /*!< MPU Alias 2 Region Base Address Register        */
  __IO uint32_t RASR_A2;                      /*!< MPU Alias 2 Region Attribute and Size Register  */
  __IO uint32_t RBAR_A3;                      /*!< MPU Alias 3 Region Base Address Register        */
  __IO uint32_t RASR_A3;                      /*!< MPU Alias 3 Region Attribute and Size Register  */
} MPU_Type;
#endif


/* Core Debug Register */
typedef struct
{
  __IO uint32_t DHCSR;                        /*!< Debug Halting Control and Status Register       */
  __O  uint32_t DCRSR;                        /*!< Debug Core Register Selector Register           */
  __IO uint32_t DCRDR;                        /*!< Debug Core Register Data Register               */
  __IO uint32_t DEMCR;                        /*!< Debug Exception and Monitor Control Register    */
} CoreDebug_Type;


/* Memory mapping of Cortex-M3 Hardware */
#define SCS_BASE            (0xE000E000)                              /*!< System Control Space Base Address    */
#define ITM_BASE            (0xE0000000)                              /*!< ITM Base Address                     */
#define CoreDebug_BASE      (0xE000EDF0)                              /*!< Core Debug Base Address              */
#define SysTick_BASE        (SCS_BASE +  0x0010)                      /*!< SysTick Base Address                 */
#define NVIC_BASE           (SCS_BASE +  0x0100)                      /*!< NVIC Base Address                    */
#define SCB_BASE            (SCS_BASE +  0x0D00)                      /*!< System Control Block Base Address    */

#define InterruptType       ((InterruptType_Type *) SCS_BASE)         /*!< Interrupt Type Register              */
#define SCB                 ((SCB_Type *)           SCB_BASE)         /*!< SCB configuration struct             */
#define SysTick             ((SysTick_Type *)       SysTick_BASE)     /*!< SysTick configuration struct         */
#define NVIC                ((NVIC_Type *)          NVIC_BASE)        /*!< NVIC configuration struct            */
#define ITM                 ((ITM_Type *)           ITM_BASE)         /*!< ITM configuration struct             */
#define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE)   /*!< Core Debug configuration struct      */

#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1)
  #define MPU_BASE          (SCS_BASE +  0x0D90)                      /*!< Memory Protection Unit               */
  #define MPU               ((MPU_Type*)            MPU_BASE)         /*!< Memory Protection Unit               */
#endif



/*******************************************************************************
 *                Hardware Abstraction Layer
 ******************************************************************************/


#if defined ( __CC_ARM   )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm                                       /*!< asm keyword for IAR Compiler           */
  #define __INLINE        inline                                      /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */

#elif defined   (  __GNUC__  )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */

#elif defined   (  __TASKING__  )
  #define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler       */

#endif


/* ###################  Compiler specific Intrinsics  ########################### */

#if defined ( __CC_ARM   ) /*------------------RealView Compiler -----------------*/
/* ARM armcc specific functions */

#define __enable_fault_irq                __enable_fiq
#define __disable_fault_irq               __disable_fiq

#define __NOP                             __nop
#define __WFI                             __wfi
#define __WFE                             __wfe
#define __SEV                             __sev
#define __ISB()                           __isb(0)
#define __DSB()                           __dsb(0)
#define __DMB()                           __dmb(0)
#define __REV                             __rev
#define __RBIT                            __rbit
#define __LDREXB(ptr)                     ((unsigned char ) __ldrex(ptr))
#define __LDREXH(ptr)                     ((unsigned short) __ldrex(ptr))
#define __LDREXW(ptr)                     ((unsigned int  ) __ldrex(ptr))
#define __STREXB(value, ptr)              __strex(value, ptr)
#define __STREXH(value, ptr)              __strex(value, ptr)
#define __STREXW(value, ptr)              __strex(value, ptr)


/* intrinsic unsigned long long __ldrexd(volatile void *ptr) */
/* intrinsic int __strexd(unsigned long long val, volatile void *ptr) */
/* intrinsic void __enable_irq();     */
/* intrinsic void __disable_irq();    */


/**
 * @brief  Return the Process Stack Pointer
 *
 * @param  none
 * @return uint32_t ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
extern uint32_t __get_PSP(void);

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  uint32_t Process Stack Pointer
 * @return none
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */
extern void __set_PSP(uint32_t topOfProcStack);

/**
 * @brief  Return the Main Stack Pointer
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
extern uint32_t __get_MSP(void);

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  uint32_t Main Stack Pointer
 * @return none
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */
extern void __set_MSP(uint32_t topOfMainStack);

/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  uint16_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in unsigned short value
 */
extern uint32_t __REV16(uint16_t value);

/*
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param  int16_t value to reverse
 * @return int32_t reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */
extern int32_t __REVSH(int16_t value);


#if (__ARMCC_VERSION < 400000)

/**
 * @brief  Remove the exclusive lock created by ldrex
 *
 * @param  none
 * @return none
 *
 * Removes the exclusive lock which is created by ldrex.
 */
extern void __CLREX(void);

/**
 * @brief  Return the Base Priority value
 *
 * @param  none
 * @return uint32_t BasePriority
 *
 * Return the content of the base priority register
 */
extern uint32_t __get_BASEPRI(void);

/**
 * @brief  Set the Base Priority value
 *
 * @param  uint32_t BasePriority
 * @return none
 *
 * Set the base priority register
 */
extern void __set_BASEPRI(uint32_t basePri);

/**
 * @brief  Return the Priority Mask value
 *
 * @param  none
 * @return uint32_t PriMask
 *
 * Return the state of the priority mask bit from the priority mask
 * register
 */
extern uint32_t __get_PRIMASK(void);

/**
 * @brief  Set the Priority Mask value
 *
 * @param  uint32_t PriMask
 * @return none
 *
 * Set the priority mask bit in the priority mask register
 */
extern void __set_PRIMASK(uint32_t priMask);

/**
 * @brief  Return the Fault Mask value
 *
 * @param  none
 * @return uint32_t FaultMask
 *
 * Return the content of the fault mask register
 */
extern uint32_t __get_FAULTMASK(void);

/**
 * @brief  Set the Fault Mask value
 *
 * @param  uint32_t faultMask value
 * @return none
 *
 * Set the fault mask register
 */
extern void __set_FAULTMASK(uint32_t faultMask);

/**
 * @brief  Return the Control Register value
 * 
 * @param  none
 * @return uint32_t Control value
 *
 * Return the content of the control register
 */
extern uint32_t __get_CONTROL(void);

/**
 * @brief  Set the Control Register value
 *
 * @param  uint32_t Control value
 * @return none
 *
 * Set the control register
 */
extern void __set_CONTROL(uint32_t control);

#else  /* (__ARMCC_VERSION >= 400000)  */


/**
 * @brief  Remove the exclusive lock created by ldrex
 *
 * @param  none
 * @return none
 *
 * Removes the exclusive lock which is created by ldrex.
 */
#define __CLREX                           __clrex

/**
 * @brief  Return the Base Priority value
 *
 * @param  none
 * @return uint32_t BasePriority
 *
 * Return the content of the base priority register
 */
static __INLINE uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __ASM("basepri");
  return(__regBasePri);
}

/**
 * @brief  Set the Base Priority value
 *
 * @param  uint32_t BasePriority
 * @return none
 *
 * Set the base priority register
 */
static __INLINE void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __ASM("basepri");
  __regBasePri = (basePri & 0x1ff);
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
static __INLINE uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __ASM("primask");
  return(__regPriMask);
}

/**
 * @brief  Set the Priority Mask value
 *
 * @param  uint32_t PriMask
 * @return none
 *
 * Set the priority mask bit in the priority mask register
 */
static __INLINE void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __ASM("primask");
  __regPriMask = (priMask);
}

/**
 * @brief  Return the Fault Mask value
 *
 * @param  none
 * @return uint32_t FaultMask
 *
 * Return the content of the fault mask register
 */
static __INLINE uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __ASM("faultmask");
  return(__regFaultMask);
}

/**
 * @brief  Set the Fault Mask value
 *
 * @param  uint32_t faultMask value
 * @return none
 *
 * Set the fault mask register
 */
static __INLINE void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __ASM("faultmask");
  __regFaultMask = (faultMask & 1);
}

/**
 * @brief  Return the Control Register value
 * 
 * @param  none
 * @return uint32_t Control value
 *
 * Return the content of the control register
 */
static __INLINE uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __ASM("control");
  return(__regControl);
}

/**
 * @brief  Set the Control Register value
 *
 * @param  uint32_t Control value
 * @return none
 *
 * Set the control register
 */
static __INLINE void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __ASM("control");
  __regControl = control;
}

#endif /* __ARMCC_VERSION  */ 



#elif (defined (__ICCARM__)) /*------------------ ICC Compiler -------------------*/
/* IAR iccarm specific functions */

#define __enable_irq                              __enable_interrupt        /*!< global Interrupt enable */
#define __disable_irq                             __disable_interrupt       /*!< global Interrupt disable */

static __INLINE void __enable_fault_irq()         { __ASM ("cpsie f"); }
static __INLINE void __disable_fault_irq()        { __ASM ("cpsid f"); }

#define __NOP                                     __no_operation()          /*!< no operation intrinsic in IAR Compiler */ 
static __INLINE  void __WFI()                     { __ASM ("wfi"); }
static __INLINE  void __WFE()                     { __ASM ("wfe"); }
static __INLINE  void __SEV()                     { __ASM ("sev"); }
static __INLINE  void __CLREX()                   { __ASM ("clrex"); }

/* intrinsic void __ISB(void)                                     */
/* intrinsic void __DSB(void)                                     */
/* intrinsic void __DMB(void)                                     */
/* intrinsic void __set_PRIMASK();                                */
/* intrinsic void __get_PRIMASK();                                */
/* intrinsic void __set_FAULTMASK();                              */
/* intrinsic void __get_FAULTMASK();                              */
/* intrinsic uint32_t __REV(uint32_t value);                      */
/* intrinsic uint32_t __REVSH(uint32_t value);                    */
/* intrinsic unsigned long __STREX(unsigned long, unsigned long); */
/* intrinsic unsigned long __LDREX(unsigned long *);              */


/**
 * @brief  Return the Process Stack Pointer
 *
 * @param  none
 * @return uint32_t ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
extern uint32_t __get_PSP(void);

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  uint32_t Process Stack Pointer
 * @return none
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */
extern void __set_PSP(uint32_t topOfProcStack);

/**
 * @brief  Return the Main Stack Pointer
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
extern uint32_t __get_MSP(void);

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  uint32_t Main Stack Pointer
 * @return none
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */
extern void __set_MSP(uint32_t topOfMainStack);

/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  uint16_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in unsigned short value
 */
extern uint32_t __REV16(uint16_t value);

/**
 * @brief  Reverse bit order of value
 *
 * @param  uint32_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse bit order of value
 */
extern uint32_t __RBIT(uint32_t value);

/**
 * @brief  LDR Exclusive
 *
 * @param  uint8_t* address
 * @return uint8_t value of (*address)
 *
 * Exclusive LDR command
 */
extern uint8_t __LDREXB(uint8_t *addr);

/**
 * @brief  LDR Exclusive
 *
 * @param  uint16_t* address
 * @return uint16_t value of (*address)
 *
 * Exclusive LDR command
 */
extern uint16_t __LDREXH(uint16_t *addr);

/**
 * @brief  LDR Exclusive
 *
 * @param  uint32_t* address
 * @return uint32_t value of (*address)
 *
 * Exclusive LDR command
 */
extern uint32_t __LDREXW(uint32_t *addr);

/**
 * @brief  STR Exclusive
 *
 * @param  uint8_t *address
 * @param  uint8_t value to store
 * @return uint32_t successful / failed
 *
 * Exclusive STR command
 */
extern uint32_t __STREXB(uint8_t value, uint8_t *addr);

/**
 * @brief  STR Exclusive
 *
 * @param  uint16_t *address
 * @param  uint16_t value to store
 * @return uint32_t successful / failed
 *
 * Exclusive STR command
 */
extern uint32_t __STREXH(uint16_t value, uint16_t *addr);

/**
 * @brief  STR Exclusive
 *
 * @param  uint32_t *address
 * @param  uint32_t value to store
 * @return uint32_t successful / failed
 *
 * Exclusive STR command
 */
extern uint32_t __STREXW(uint32_t value, uint32_t *addr);



#elif (defined (__GNUC__)) /*------------------ GNU Compiler ---------------------*/
/* GNU gcc specific functions */

static __INLINE void __enable_irq()               { __ASM volatile ("cpsie i"); }
static __INLINE void __disable_irq()              { __ASM volatile ("cpsid i"); }

static __INLINE void __enable_fault_irq()         { __ASM volatile ("cpsie f"); }
static __INLINE void __disable_fault_irq()        { __ASM volatile ("cpsid f"); }

static __INLINE void __NOP()                      { __ASM volatile ("nop"); }
static __INLINE void __WFI()                      { __ASM volatile ("wfi"); }
static __INLINE void __WFE()                      { __ASM volatile ("wfe"); }
static __INLINE void __SEV()                      { __ASM volatile ("sev"); }
static __INLINE void __ISB()                      { __ASM volatile ("isb"); }
static __INLINE void __DSB()                      { __ASM volatile ("dsb"); }
static __INLINE void __DMB()                      { __ASM volatile ("dmb"); }
static __INLINE void __CLREX()                    { __ASM volatile ("clrex"); }


/**
 * @brief  Return the Process Stack Pointer
 *
 * @param  none
 * @return uint32_t ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
extern uint32_t __get_PSP(void);

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  uint32_t Process Stack Pointer
 * @return none
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */
extern void __set_PSP(uint32_t topOfProcStack);

/**
 * @brief  Return the Main Stack Pointer
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
extern uint32_t __get_MSP(void);

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  uint32_t Main Stack Pointer
 * @return none
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */
extern void __set_MSP(uint32_t topOfMainStack);

/**
 * @brief  Return the Base Priority value
 *
 * @param  none
 * @return uint32_t BasePriority
 *
 * Return the content of the base priority register
 */
extern uint32_t __get_BASEPRI(void);

/**
 * @brief  Set the Base Priority value
 *
 * @param  uint32_t BasePriority
 * @return none
 *
 * Set the base priority register
 */
extern void __set_BASEPRI(uint32_t basePri);

/**
 * @brief  Return the Priority Mask value
 *
 * @param  none
 * @return uint32_t PriMask
 *
 * Return the state of the priority mask bit from the priority mask
 * register
 */
extern uint32_t  __get_PRIMASK(void);

/**
 * @brief  Set the Priority Mask value
 *
 * @param  uint32_t PriMask
 * @return none
 *
 * Set the priority mask bit in the priority mask register
 */
extern void __set_PRIMASK(uint32_t priMask);

/**
 * @brief  Return the Fault Mask value
 *
 * @param  none
 * @return uint32_t FaultMask
 *
 * Return the content of the fault mask register
 */
extern uint32_t __get_FAULTMASK(void);

/**
 * @brief  Set the Fault Mask value
 *
 * @param  uint32_t faultMask value
 * @return none
 *
 * Set the fault mask register
 */
extern void __set_FAULTMASK(uint32_t faultMask);

/**
 * @brief  Return the Control Register value
* 
*  @param  none
*  @return uint32_t Control value
 *
 * Return the content of the control register
 */
extern uint32_t __get_CONTROL(void);

/**
 * @brief  Set the Control Register value
 *
 * @param  uint32_t Control value
 * @return none
 *
 * Set the control register
 */
extern void __set_CONTROL(uint32_t control);

/**
 * @brief  Reverse byte order in integer value
 *
 * @param  uint32_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in integer value
 */
extern uint32_t __REV(uint32_t value);

/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  uint16_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in unsigned short value
 */
extern uint32_t __REV16(uint16_t value);

/*
 * Reverse byte order in signed short value with sign extension to integer
 *
 * @param  int16_t value to reverse
 * @return int32_t reversed value
 *
 * @brief  Reverse byte order in signed short value with sign extension to integer
 */
extern int32_t __REVSH(int16_t value);

/**
 * @brief  Reverse bit order of value
 *
 * @param  uint32_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse bit order of value
 */
extern uint32_t __RBIT(uint32_t value);

/**
 * @brief  LDR Exclusive
 *
 * @param  uint8_t* address
 * @return uint8_t value of (*address)
 *
 * Exclusive LDR command
 */
extern uint8_t __LDREXB(uint8_t *addr);

/**
 * @brief  LDR Exclusive
 *
 * @param  uint16_t* address
 * @return uint16_t value of (*address)
 *
 * Exclusive LDR command
 */
extern uint16_t __LDREXH(uint16_t *addr);

/**
 * @brief  LDR Exclusive
 *
 * @param  uint32_t* address
 * @return uint32_t value of (*address)
 *
 * Exclusive LDR command
 */
extern uint32_t __LDREXW(uint32_t *addr);

/**
 * @brief  STR Exclusive
 *
 * @param  uint8_t *address
 * @param  uint8_t value to store
 * @return uint32_t successful / failed
 *
 * Exclusive STR command
 */
extern uint32_t __STREXB(uint8_t value, uint8_t *addr);

/**
 * @brief  STR Exclusive
 *
 * @param  uint16_t *address
 * @param  uint16_t value to store
 * @return uint32_t successful / failed
 *
 * Exclusive STR command
 */
extern uint32_t __STREXH(uint16_t value, uint16_t *addr);

/**
 * @brief  STR Exclusive
 *
 * @param  uint32_t *address
 * @param  uint32_t value to store
 * @return uint32_t successful / failed
 *
 * Exclusive STR command
 */
extern uint32_t __STREXW(uint32_t value, uint32_t *addr);


#elif (defined (__TASKING__)) /*------------------ TASKING Compiler ---------------------*/
/* TASKING carm specific functions */

/*
 * The CMSIS functions have been implemented as intrinsics in the compiler.
 * Please use "carm -?i" to get an up to date list of all instrinsics,
 * Including the CMSIS ones.
 */

#endif



/* ##########################   NVIC functions  #################################### */


/**
 * @brief  Set the Priority Grouping in NVIC Interrupt Controller
 *
 * @param  uint32_t priority_grouping is priority grouping field
 * @return none 
 *
 * Set the priority grouping field using the required unlock sequence.
 * The parameter priority_grouping is assigned to the field 
 * SCB->AIRCR [10:8] PRIGROUP field. Only values from 0..7 are used.
 * In case of a conflict between priority grouping and available
 * priority bits (__NVIC_PRIO_BITS) the smallest possible priority group is set.
 */
static __INLINE void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                         /* only values 0..7 are used          */
  
  reg_value  = SCB->AIRCR;                                                    /* read old register configuration    */
  reg_value &= ~((0xFFFFU << 16) | (0x0F << 8));                              /* clear bits to change               */
  reg_value  = ((reg_value | NVIC_AIRCR_VECTKEY | (PriorityGroupTmp << 8)));  /* Insert write key and priorty group */
  SCB->AIRCR = reg_value;
}

/**
 * @brief  Get the Priority Grouping from NVIC Interrupt Controller
 *
 * @param  none
 * @return uint32_t   priority grouping field 
 *
 * Get the priority grouping from NVIC Interrupt Controller.
 * priority grouping is SCB->AIRCR [10:8] PRIGROUP field.
 */
static __INLINE uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((SCB->AIRCR >> 8) & 0x07);                                          /* read priority grouping field */
}

/**
 * @brief  Enable Interrupt in NVIC Interrupt Controller
 *
 * @param  IRQn_Type IRQn specifies the interrupt number
 * @return none 
 *
 * Enable a device specific interupt in the NVIC interrupt controller.
 * The interrupt number cannot be a negative value.
 */
static __INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  NVIC->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* enable interrupt */
}

/**
 * @brief  Disable the interrupt line for external interrupt specified
 * 
 * @param  IRQn_Type IRQn is the positive number of the external interrupt
 * @return none
 * 
 * Disable a device specific interupt in the NVIC interrupt controller.
 * The interrupt number cannot be a negative value.
 */
static __INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  NVIC->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* disable interrupt */
}

/**
 * @brief  Read the interrupt pending bit for a device specific interrupt source
 * 
 * @param  IRQn_Type IRQn is the number of the device specifc interrupt
 * @return uint32_t 1 if pending interrupt else 0
 *
 * Read the pending register in NVIC and return 1 if its status is pending, 
 * otherwise it returns 0
 */
static __INLINE uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((NVIC->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0)); /* Return 1 if pending else 0 */
}

/**
 * @brief  Set the pending bit for an external interrupt
 * 
 * @param  IRQn_Type IRQn is the Number of the interrupt
 * @return none
 *
 * Set the pending bit for the specified interrupt.
 * The interrupt number cannot be a negative value.
 */
static __INLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  NVIC->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* set interrupt pending */
}

/**
 * @brief  Clear the pending bit for an external interrupt
 *
 * @param  IRQn_Type IRQn is the Number of the interrupt
 * @return none
 *
 * Clear the pending bit for the specified interrupt. 
 * The interrupt number cannot be a negative value.
 */
static __INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  NVIC->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* Clear pending interrupt */
}

/**
 * @brief  Read the active bit for an external interrupt
 *
 * @param  IRQn_Type  IRQn is the Number of the interrupt
 * @return uint32_t   1 if active else 0
 *
 * Read the active register in NVIC and returns 1 if its status is active, 
 * otherwise it returns 0.
 */
static __INLINE uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((NVIC->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0)); /* Return 1 if active else 0 */
}

/**
 * @brief  Set the priority for an interrupt
 *
 * @param  IRQn_Type IRQn is the Number of the interrupt
 * @param  priority is the priority for the interrupt
 * @return none
 *
 * Set the priority for the specified interrupt. The interrupt 
 * number can be positive to specify an external (device specific) 
 * interrupt, or negative to specify an internal (core) interrupt. \n
 *
 * Note: The priority cannot be set for every core interrupt.
 */
static __INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    SCB->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff); } /* set Priority for Cortex-M3 System Interrupts */
  else {
    NVIC->IP[(uint32_t)(IRQn)] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff);    }        /* set Priority for device specific Interrupts      */
}

/**
 * @brief  Read the priority for an interrupt
 *
 * @param  IRQn_Type IRQn is the Number of the interrupt
 * @return uint32_t  priority is the priority for the interrupt
 *
 * Read the priority for the specified interrupt. The interrupt 
 * number can be positive to specify an external (device specific) 
 * interrupt, or negative to specify an internal (core) interrupt.
 *
 * The returned priority value is automatically aligned to the implemented
 * priority bits of the microcontroller.
 *
 * Note: The priority cannot be set for every core interrupt.
 */
static __INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(SCB->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - __NVIC_PRIO_BITS)));  } /* get priority for Cortex-M3 system interrupts */
  else {
    return((uint32_t)(NVIC->IP[(uint32_t)(IRQn)]           >> (8 - __NVIC_PRIO_BITS)));  } /* get priority for device specific interrupts  */
}


/**
 * @brief  Encode the priority for an interrupt
 *
 * @param  uint32_t PriorityGroup   is the used priority group
 * @param  uint32_t PreemptPriority is the preemptive priority value (starting from 0)
 * @param  uint32_t SubPriority     is the sub priority value (starting from 0)
 * @return uint32_t                    the priority for the interrupt
 *
 * Encode the priority for an interrupt with the given priority group,
 * preemptive priority value and sub priority value.
 * In case of a conflict between priority grouping and available
 * priority bits (__NVIC_PRIO_BITS) the samllest possible priority group is set.
 *
 * The returned priority value can be used for NVIC_SetPriority(...) function
 */
static __INLINE uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                         /* only values 0..7 are used          */
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > __NVIC_PRIO_BITS) ? __NVIC_PRIO_BITS : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + __NVIC_PRIO_BITS) < 7) ? 0 : PriorityGroupTmp - 7 + __NVIC_PRIO_BITS;
 
  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}


/**
 * @brief  Decode the priority of an interrupt
 *
 * @param  uint32_t   Priority       the priority for the interrupt
 * @param  uint32_t   PrioGroup   is the used priority group
 * @param  uint32_t* pPreemptPrio is the preemptive priority value (starting from 0)
 * @param  uint32_t* pSubPrio     is the sub priority value (starting from 0)
 * @return none
 *
 * Decode an interrupt priority value with the given priority group to 
 * preemptive priority value and sub priority value.
 * In case of a conflict between priority grouping and available
 * priority bits (__NVIC_PRIO_BITS) the samllest possible priority group is set.
 *
 * The priority value can be retrieved with NVIC_GetPriority(...) function
 */
static __INLINE void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                         /* only values 0..7 are used          */
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > __NVIC_PRIO_BITS) ? __NVIC_PRIO_BITS : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + __NVIC_PRIO_BITS) < 7) ? 0 : PriorityGroupTmp - 7 + __NVIC_PRIO_BITS;
  
  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}



/* ##################################    SysTick function  ############################################ */

#if (!defined (__Vendor_SysTickConfig)) || (__Vendor_SysTickConfig == 0)

/* SysTick constants */
#define SYSTICK_ENABLE              0                                          /* Config-Bit to start or stop the SysTick Timer                         */
#define SYSTICK_TICKINT             1                                          /* Config-Bit to enable or disable the SysTick interrupt                 */
#define SYSTICK_CLKSOURCE           2                                          /* Clocksource has the offset 2 in SysTick Control and Status Register   */
#define SYSTICK_MAXCOUNT       ((1<<24) -1)                                    /* SysTick MaxCount                                                      */

/**
 * @brief  Initialize and start the SysTick counter and its interrupt.
 *
 * @param  uint32_t ticks is the number of ticks between two interrupts
 * @return  none
 *
 * Initialise the system tick timer and its interrupt and start the
 * system tick timer / counter in free running mode to generate 
 * periodical interrupts.
 */
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SYSTICK_MAXCOUNT)  return (1);                                             /* Reload value impossible */

  SysTick->LOAD  =  (ticks & SYSTICK_MAXCOUNT) - 1;                                      /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);                            /* set Priority for Cortex-M0 System Interrupts */
  SysTick->VAL   =  (0x00);                                                              /* Load the SysTick Counter Value */
  SysTick->CTRL = (1 << SYSTICK_CLKSOURCE) | (1<<SYSTICK_ENABLE) | (1<<SYSTICK_TICKINT); /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                                            /* Function successful */
}

#endif





/* ##################################    Reset function  ############################################ */

/**
 * @brief  Initiate a system reset request.
 *
 * @param   none
 * @return  none
 *
 * Initialize a system reset request to reset the MCU
 */
static __INLINE void NVIC_SystemReset(void)
{
  SCB->AIRCR  = (NVIC_AIRCR_VECTKEY | (SCB->AIRCR & (0x700)) | (1<<NVIC_SYSRESETREQ)); /* Keep priority group unchanged */
  __DSB();                                                                             /* Ensure completion of memory access */              
  while(1);                                                                            /* wait until reset */
}


/* ##################################    Debug Output  function  ############################################ */


/**
 * @brief  Outputs a character via the ITM channel 0
 *
 * @param   uint32_t character to output
 * @return  uint32_t input character
 *
 * The function outputs a character via the ITM channel 0. 
 * The function returns when no debugger is connected that has booked the output.  
 * It is blocking when a debugger is connected, but the previous character send is not transmitted. 
 */
static __INLINE uint32_t ITM_SendChar (uint32_t ch)
{
  if (ch == '\n') ITM_SendChar('\r');
  
  if ((CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA)  &&
      (ITM->TCR & ITM_TCR_ITMENA)                  &&
      (ITM->TER & (1UL << 0))  ) 
  {
    while (ITM->PORT[0].u32 == 0);
    ITM->PORT[0].u8 = (uint8_t) ch;
  }  
  return (ch);
}

#ifdef __cplusplus
}
#endif

#endif /* __CM3_CORE_H__ */

/*lint -restore */
