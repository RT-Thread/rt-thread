
/******************************************************************************
*
* Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*  Redistributions of source code must retain the above copyright
*  notice, this list of conditions and the following disclaimer.
*
*  Redistributions in binary form must reproduce the above copyright
*  notice, this list of conditions and the following disclaimer in the
*  documentation and/or other materials provided with the
*  distribution.
*
*  Neither the name of Texas Instruments Incorporated nor the names of
*  its contributors may be used to endorse or promote products derived
*  from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* MSP432E401Y Register Definitions
*
* This file includes CMSIS compliant component and register definitions
*
*
* With CMSIS definitions, the register defines have been reformatted:
*     ModuleName[ModuleInstance]->RegisterName
*
* Writing to CMSIS bit fields can be done through register level
* or via bitband area access:
*  - ADC14->CTL0 |= ADC14_CTL0_ENC;
*  - BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 1;
*
* File creation date: 2018-10-12
*
******************************************************************************/

#ifndef __MSP432E401Y_H__
#define __MSP432E401Y_H__

#ifdef __cplusplus
extern "C" {
#endif

#define __MSP432_HEADER_VERSION__ 3260

/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum
{
    /* -------------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */
    Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
    NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
    HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
    MemoryManagement_IRQn         = -12,              /*!<   4  Memory Management, MPU mismatch, including Access Violation
                                                         and No Match                                                          */
    BusFault_IRQn                 = -11,              /*!<   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                         related Fault                                                         */
    UsageFault_IRQn               = -10,              /*!<   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition    */
    SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
    DebugMonitor_IRQn             =  -4,              /*!<  12  Debug Monitor                                                    */
    PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
    SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
    /* ------------------  MSP432E401Y Specific Interrupt Numbers  ------------------ */
    GPIOA_IRQn                    =   0,              /*!<   0  GPIOA                                                            */
    GPIOB_IRQn                    =   1,              /*!<   1  GPIOB                                                            */
    GPIOC_IRQn                    =   2,              /*!<   2  GPIOC                                                            */
    GPIOD_IRQn                    =   3,              /*!<   3  GPIOD                                                            */
    GPIOE_IRQn                    =   4,              /*!<   4  GPIOE                                                            */
    UART0_IRQn                    =   5,              /*!<   5  UART0                                                            */
    UART1_IRQn                    =   6,              /*!<   6  UART1                                                            */
    SSI0_IRQn                     =   7,              /*!<   7  SSI0                                                             */
    I2C0_IRQn                     =   8,              /*!<   8  I2C0                                                             */
    PWM0_FAULT_IRQn               =   9,              /*!<   9  PWM0_FAULT                                                       */
    PWM0_0_IRQn                   =  10,              /*!<  10  PWM0_0                                                           */
    PWM0_1_IRQn                   =  11,              /*!<  11  PWM0_1                                                           */
    PWM0_2_IRQn                   =  12,              /*!<  12  PWM0_2                                                           */
    QEI0_IRQn                     =  13,              /*!<  13  QEI0                                                             */
    ADC0SS0_IRQn                  =  14,              /*!<  14  ADC0SS0                                                          */
    ADC0SS1_IRQn                  =  15,              /*!<  15  ADC0SS1                                                          */
    ADC0SS2_IRQn                  =  16,              /*!<  16  ADC0SS2                                                          */
    ADC0SS3_IRQn                  =  17,              /*!<  17  ADC0SS3                                                          */
    WATCHDOG0_IRQn                =  18,              /*!<  18  WATCHDOG0                                                        */
    TIMER0A_IRQn                  =  19,              /*!<  19  TIMER0A                                                          */
    TIMER0B_IRQn                  =  20,              /*!<  20  TIMER0B                                                          */
    TIMER1A_IRQn                  =  21,              /*!<  21  TIMER1A                                                          */
    TIMER1B_IRQn                  =  22,              /*!<  22  TIMER1B                                                          */
    TIMER2A_IRQn                  =  23,              /*!<  23  TIMER2A                                                          */
    TIMER2B_IRQn                  =  24,              /*!<  24  TIMER2B                                                          */
    COMP0_IRQn                    =  25,              /*!<  25  COMP0                                                            */
    COMP1_IRQn                    =  26,              /*!<  26  COMP1                                                            */
    COMP2_IRQn                    =  27,              /*!<  27  COMP2                                                            */
    SYSCTL_IRQn                   =  28,              /*!<  28  SYSCTL                                                           */
    FLASH_CTRL_IRQn               =  29,              /*!<  29  FLASH_CTRL                                                       */
    GPIOF_IRQn                    =  30,              /*!<  30  GPIOF                                                            */
    GPIOG_IRQn                    =  31,              /*!<  31  GPIOG                                                            */
    GPIOH_IRQn                    =  32,              /*!<  32  GPIOH                                                            */
    UART2_IRQn                    =  33,              /*!<  33  UART2                                                            */
    SSI1_IRQn                     =  34,              /*!<  34  SSI1                                                             */
    TIMER3A_IRQn                  =  35,              /*!<  35  TIMER3A                                                          */
    TIMER3B_IRQn                  =  36,              /*!<  36  TIMER3B                                                          */
    I2C1_IRQn                     =  37,              /*!<  37  I2C1                                                             */
    CAN0_IRQn                     =  38,              /*!<  38  CAN0                                                             */
    CAN1_IRQn                     =  39,              /*!<  39  CAN1                                                             */
    EMAC0_IRQn                    =  40,              /*!<  40  EMAC0                                                            */
    HIB_IRQn                      =  41,              /*!<  41  HIB                                                              */
    USB0_IRQn                     =  42,              /*!<  42  USB0                                                             */
    PWM0_3_IRQn                   =  43,              /*!<  43  PWM0_3                                                           */
    UDMA_IRQn                     =  44,              /*!<  44  UDMA                                                             */
    UDMAERR_IRQn                  =  45,              /*!<  45  UDMAERR                                                          */
    ADC1SS0_IRQn                  =  46,              /*!<  46  ADC1SS0                                                          */
    ADC1SS1_IRQn                  =  47,              /*!<  47  ADC1SS1                                                          */
    ADC1SS2_IRQn                  =  48,              /*!<  48  ADC1SS2                                                          */
    ADC1SS3_IRQn                  =  49,              /*!<  49  ADC1SS3                                                          */
    EPI0_IRQn                     =  50,              /*!<  50  EPI0                                                             */
    GPIOJ_IRQn                    =  51,              /*!<  51  GPIOJ                                                            */
    GPIOK_IRQn                    =  52,              /*!<  52  GPIOK                                                            */
    GPIOL_IRQn                    =  53,              /*!<  53  GPIOL                                                            */
    SSI2_IRQn                     =  54,              /*!<  54  SSI2                                                             */
    SSI3_IRQn                     =  55,              /*!<  55  SSI3                                                             */
    UART3_IRQn                    =  56,              /*!<  56  UART3                                                            */
    UART4_IRQn                    =  57,              /*!<  57  UART4                                                            */
    UART5_IRQn                    =  58,              /*!<  58  UART5                                                            */
    UART6_IRQn                    =  59,              /*!<  59  UART6                                                            */
    UART7_IRQn                    =  60,              /*!<  60  UART7                                                            */
    I2C2_IRQn                     =  61,              /*!<  61  I2C2                                                             */
    I2C3_IRQn                     =  62,              /*!<  62  I2C3                                                             */
    TIMER4A_IRQn                  =  63,              /*!<  63  TIMER4A                                                          */
    TIMER4B_IRQn                  =  64,              /*!<  64  TIMER4B                                                          */
    TIMER5A_IRQn                  =  65,              /*!<  65  TIMER5A                                                          */
    TIMER5B_IRQn                  =  66,              /*!<  66  TIMER5B                                                          */
    SYSEXC_IRQn                   =  67,              /*!<  67  Floating-Point Exception (imprecise)                             */
    I2C4_IRQn                     =  70,              /*!<  70  I2C4                                                             */
    I2C5_IRQn                     =  71,              /*!<  71  I2C5                                                             */
    GPIOM_IRQn                    =  72,              /*!<  72  GPIOM                                                            */
    GPION_IRQn                    =  73,              /*!<  73  GPION                                                            */
    GPIOP0_IRQn                   =  76,              /*!<  76  GPIOP0                                                           */
    GPIOP1_IRQn                   =  77,              /*!<  77  GPIOP1                                                           */
    GPIOP2_IRQn                   =  78,              /*!<  78  GPIOP2                                                           */
    GPIOP3_IRQn                   =  79,              /*!<  79  GPIOP3                                                           */
    GPIOP4_IRQn                   =  80,              /*!<  80  GPIOP4                                                           */
    GPIOP5_IRQn                   =  81,              /*!<  81  GPIOP5                                                           */
    GPIOP6_IRQn                   =  82,              /*!<  82  GPIOP6                                                           */
    GPIOP7_IRQn                   =  83,              /*!<  83  GPIOP7                                                           */
    GPIOQ0_IRQn                   =  84,              /*!<  84  GPIOQ0                                                           */
    GPIOQ1_IRQn                   =  85,              /*!<  85  GPIOQ1                                                           */
    GPIOQ2_IRQn                   =  86,              /*!<  86  GPIOQ2                                                           */
    GPIOQ3_IRQn                   =  87,              /*!<  87  GPIOQ3                                                           */
    GPIOQ4_IRQn                   =  88,              /*!<  88  GPIOQ4                                                           */
    GPIOQ5_IRQn                   =  89,              /*!<  89  GPIOQ5                                                           */
    GPIOQ6_IRQn                   =  90,              /*!<  90  GPIOQ6                                                           */
    GPIOQ7_IRQn                   =  91,              /*!<  91  GPIOQ7                                                           */
    SHA_MD5_IRQn                  =  94,              /*!<  94  SHA/MD5                                                          */
    AES_IRQn                      =  95,              /*!<  95  AES                                                              */
    DES_IRQn                      =  96,              /*!<  96  DES                                                              */
    TIMER6A_IRQn                  =  98,              /*!<  98  TIMER6A                                                          */
    TIMER6B_IRQn                  =  99,              /*!<  99  TIMER6B                                                          */
    TIMER7A_IRQn                  = 100,              /*!< 100  TIMER7A                                                          */
    TIMER7B_IRQn                  = 101,              /*!< 101  TIMER7B                                                          */
    I2C6_IRQn                     = 102,              /*!< 102  I2C6                                                             */
    I2C7_IRQn                     = 103,              /*!< 103  I2C7                                                             */
    I2C8_IRQn                     = 109,              /*!< 109  I2C8                                                             */
    I2C9_IRQn                     = 110               /*!< 110  I2C9                                                             */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M4 Processor and Core Peripherals---------------- */
#define __CM4_REV                 0x0102            /*!< Cortex-M4 Core Revision                                               */
#define __MPU_PRESENT                  1            /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               3            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
#define __FPU_PRESENT                  1            /*!< FPU present or not                                                    */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm4.h"                               /*!< Cortex-M4 processor and core peripherals                              */
#include "system_msp432e401y.h"                         /*!< MSP432E401Y System                                                  */

/******************************************************************************
* Definition of standard bits                                                 *
******************************************************************************/
#define BIT0                                     (uint16_t)(0x0001)
#define BIT1                                     (uint16_t)(0x0002)
#define BIT2                                     (uint16_t)(0x0004)
#define BIT3                                     (uint16_t)(0x0008)
#define BIT4                                     (uint16_t)(0x0010)
#define BIT5                                     (uint16_t)(0x0020)
#define BIT6                                     (uint16_t)(0x0040)
#define BIT7                                     (uint16_t)(0x0080)
#define BIT8                                     (uint16_t)(0x0100)
#define BIT9                                     (uint16_t)(0x0200)
#define BITA                                     (uint16_t)(0x0400)
#define BITB                                     (uint16_t)(0x0800)
#define BITC                                     (uint16_t)(0x1000)
#define BITD                                     (uint16_t)(0x2000)
#define BITE                                     (uint16_t)(0x4000)
#define BITF                                     (uint16_t)(0x8000)
#define BIT(x)                                 ((uint16_t)1 << (x))

/* ================================================================================ */
/* ================              Available Peripherals             ================ */
/* ================================================================================ */
#define __MCU_HAS_ADC0__                            /*!< Module ADC0 is available                                              */
#define __MCU_HAS_ADC1__                            /*!< Module ADC1 is available                                              */
#define __MCU_HAS_AES0__                            /*!< Module AES is available                                               */
#define __MCU_HAS_CAN0__                            /*!< Module CAN 0 is available                                             */
#define __MCU_HAS_CAN1__                            /*!< Module CAN 1 is available                                             */
#define __MCU_HAS_CCM0__                            /*!< Module EC is available                                                */
#define __MCU_HAS_COMP0__                           /*!< Module Analog Comparator 0 is available                               */
#define __MCU_HAS_COMP1__                           /*!< Module Analog Comparator 1 is available                               */
#define __MCU_HAS_COMP2__                           /*!< Module Analog Comparator 2 is available                               */
#define __MCU_HAS_DES0__                            /*!< Module DES is available                                               */
#define __MCU_HAS_EEPROM__                          /*!< Module EEPROM is available                                            */
#define __MCU_HAS_EMAC0__                           /*!< Module Ethernet MAC 0 is available                                    */
#define __MCU_HAS_EPI0__                            /*!< Module EPI 0 is available                                             */
#define __MCU_HAS_FLASH_CTRL__                      /*!< Module Flash Memory Control is available                              */
#define __MCU_HAS_GPIOA__                           /*!< Module GPIO Port A is available                                       */
#define __MCU_HAS_GPIOB__                           /*!< Module GPIO Port A is available                                       */
#define __MCU_HAS_GPIOC__                           /*!< Module GPIO Port C is available                                       */
#define __MCU_HAS_GPIOD__                           /*!< Module GPIO Port D is available                                       */
#define __MCU_HAS_GPIOE__                           /*!< Module GPIO Port E is available                                       */
#define __MCU_HAS_GPIOF__                           /*!< Module GPIO Port F is available                                       */
#define __MCU_HAS_GPIOG__                           /*!< Module GPIO Port G is available                                       */
#define __MCU_HAS_GPIOH__                           /*!< Module GPIO Port H is available                                       */
#define __MCU_HAS_GPIOJ__                           /*!< Module GPIO Port J is available                                       */
#define __MCU_HAS_GPIOK__                           /*!< Module GPIO Port K is available                                       */
#define __MCU_HAS_GPIOL__                           /*!< Module GPIO Port L is available                                       */
#define __MCU_HAS_GPIOM__                           /*!< Module GPIO Port M is available                                       */
#define __MCU_HAS_GPION__                           /*!< Module GPIO Port N is available                                       */
#define __MCU_HAS_GPIOP__                           /*!< Module GPIO Port P is available                                       */
#define __MCU_HAS_GPIOQ__                           /*!< Module GPIO Port Q is available                                       */
#define __MCU_HAS_HIBERNATE__                       /*!< Module HIB is available                                               */
#define __MCU_HAS_I2C0__                            /*!< Module I2C0 is available                                              */
#define __MCU_HAS_I2C1__                            /*!< Module I2C1 is available                                              */
#define __MCU_HAS_I2C2__                            /*!< Module I2C2 is available                                              */
#define __MCU_HAS_I2C3__                            /*!< Module I2C3 is available                                              */
#define __MCU_HAS_I2C4__                            /*!< Module I2C4 is available                                              */
#define __MCU_HAS_I2C5__                            /*!< Module I2C5 is available                                              */
#define __MCU_HAS_I2C6__                            /*!< Module I2C6 is available                                              */
#define __MCU_HAS_I2C7__                            /*!< Module I2C7 is available                                              */
#define __MCU_HAS_I2C8__                            /*!< Module I2C8 is available                                              */
#define __MCU_HAS_I2C9__                            /*!< Module I2C9 is available                                              */
#define __MCU_HAS_PWM0__                            /*!< Module PWM0 is available                                              */
#define __MCU_HAS_QEI0__                            /*!< Module QEI0 is available                                              */
#define __MCU_HAS_SHA0__                            /*!< Module SHA/MD5 is available                                           */
#define __MCU_HAS_SSI0__                            /*!< Module SSI0 is available                                              */
#define __MCU_HAS_SSI1__                            /*!< Module SSI1 is available                                              */
#define __MCU_HAS_SSI2__                            /*!< Module SSI2 is available                                              */
#define __MCU_HAS_SSI3__                            /*!< Module SSI3 is available                                              */
#define __MCU_HAS_SYSCTL__                          /*!< Module System Control is available                                    */
#define __MCU_HAS_SYSEXC__                          /*!< Module Floating-Point Exception is available                          */
#define __MCU_HAS_TEMPER0__                         /*!< Module Temper is available                                            */
#define __MCU_HAS_TIMER0A__                         /*!< Module 16/32-Bit Timer 0A is available                                */
#define __MCU_HAS_TIMER0B__                         /*!< Module 16/32-Bit Timer 0B is available                                */
#define __MCU_HAS_TIMER1A__                         /*!< Module 16/32-Bit Timer 1A is available                                */
#define __MCU_HAS_TIMER1B__                         /*!< Module 16/32-Bit Timer 1B is available                                */
#define __MCU_HAS_TIMER2A__                         /*!< Module 16/32-Bit Timer 2A is available                                */
#define __MCU_HAS_TIMER2B__                         /*!< Module 16/32-Bit Timer 2B is available                                */
#define __MCU_HAS_TIMER3A__                         /*!< Module 16/32-Bit Timer 3A is available                                */
#define __MCU_HAS_TIMER3B__                         /*!< Module 16/32-Bit Timer 3B is available                                */
#define __MCU_HAS_TIMER4A__                         /*!< Module 16/32-Bit Timer 4A is available                                */
#define __MCU_HAS_TIMER4B__                         /*!< Module 16/32-Bit Timer 4B is available                                */
#define __MCU_HAS_TIMER5A__                         /*!< Module 16/32-Bit Timer 5A is available                                */
#define __MCU_HAS_TIMER5B__                         /*!< Module 16/32-Bit Timer 5B is available                                */
#define __MCU_HAS_TIMER6A__                         /*!< Module 16/32-Bit Timer 6A is available                                */
#define __MCU_HAS_TIMER6B__                         /*!< Module 16/32-Bit Timer 6B is available                                */
#define __MCU_HAS_TIMER7A__                         /*!< Module 16/32-Bit Timer 7A is available                                */
#define __MCU_HAS_TIMER7B__                         /*!< Module 16/32-Bit Timer 7B is available                                */
#define __MCU_HAS_UART0__                           /*!< Module UART0 is available                                             */
#define __MCU_HAS_UART1__                           /*!< Module UART1 is available                                             */
#define __MCU_HAS_UART2__                           /*!< Module UART2 is available                                             */
#define __MCU_HAS_UART3__                           /*!< Module UART3 is available                                             */
#define __MCU_HAS_UART4__                           /*!< Module UART4 is available                                             */
#define __MCU_HAS_UART5__                           /*!< Module UART5 is available                                             */
#define __MCU_HAS_UART6__                           /*!< Module UART6 is available                                             */
#define __MCU_HAS_UART7__                           /*!< Module UART7 is available                                             */
#define __MCU_HAS_UDMA__                            /*!< Module uDMA 0 Software is available                                   */
#define __MCU_HAS_USB0__                            /*!< Module USB MAC is available                                           */
#define __MCU_HAS_WATCHDOG0__                       /*!< Module Watchdog Timer 0 is available                                  */
#define __MCU_HAS_WATCHDOG1__                       /*!< Module Watchdog Timer 1 is available                                  */

/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined(__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#elif defined(__GNUC__)
/* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
#pragma warning 586
#else
#warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================                    WATCHDOG0                   ================ */
/* ================================================================================ */


/**
  * @brief Register map for WATCHDOG0 peripheral (WATCHDOG0)
  */

typedef struct                                      /*!< WATCHDOG0 Structure                                                   */
{
    __IO uint32_t  LOAD;                              /*!< Watchdog Load                                                         */
    __IO uint32_t  VALUE;                             /*!< Watchdog Value                                                        */
    __IO uint32_t  CTL;                               /*!< Watchdog Control                                                      */
    __O  uint32_t  ICR;                               /*!< Watchdog Interrupt Clear                                              */
    __IO uint32_t  RIS;                               /*!< Watchdog Raw Interrupt Status                                         */
    __IO uint32_t  MIS;                               /*!< Watchdog Masked Interrupt Status                                      */
    __I  uint32_t  RESERVED0[256];
    __IO uint32_t  TEST;                              /*!< Watchdog Test                                                         */
    __I  uint32_t  RESERVED1[505];
    __IO uint32_t  LOCK;                              /*!< Watchdog Lock                                                         */
} WATCHDOG0_Type;


/* ================================================================================ */
/* ================                      SSI0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for SSI0 peripheral (SSI0)
  */

typedef struct                                      /*!< SSI0 Structure                                                        */
{
    __IO uint32_t  CR0;                               /*!< SSI Control 0                                                         */
    __IO uint32_t  CR1;                               /*!< SSI Control 1                                                         */
    __IO uint32_t  DR;                                /*!< SSI Data                                                              */
    __IO uint32_t  SR;                                /*!< SSI Status                                                            */
    __IO uint32_t  CPSR;                              /*!< SSI Clock Prescale                                                    */
    __IO uint32_t  IM;                                /*!< SSI Interrupt Mask                                                    */
    __IO uint32_t  RIS;                               /*!< SSI Raw Interrupt Status                                              */
    __IO uint32_t  MIS;                               /*!< SSI Masked Interrupt Status                                           */
    __O  uint32_t  ICR;                               /*!< SSI Interrupt Clear                                                   */
    __IO uint32_t  DMACTL;                            /*!< SSI DMA Control                                                       */
    __I  uint32_t  RESERVED0[998];
    __IO uint32_t  PP;                                /*!< SSI Peripheral Properties                                             */
    __I  uint32_t  RESERVED1;
    __IO uint32_t  CC;                                /*!< SSI Clock Configuration                                               */
} SSI0_Type;


/* ================================================================================ */
/* ================                      UART0                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for UART0 peripheral (UART0)
  */

typedef struct                                      /*!< UART0 Structure                                                       */
{
    __IO uint32_t  DR;                                /*!< UART Data                                                             */

    union
    {
        __IO uint32_t  ECR;                             /*!< UART Receive Status/Error Clear                                       */
        __IO uint32_t  RSR;                             /*!< UART Receive Status/Error Clear                                       */
    };
    __I  uint32_t  RESERVED0[4];
    __IO uint32_t  FR;                                /*!< UART Flag                                                             */
    __I  uint32_t  RESERVED1;
    __IO uint32_t  ILPR;                              /*!< UART IrDA Low-Power Register                                          */
    __IO uint32_t  IBRD;                              /*!< UART Integer Baud-Rate Divisor                                        */
    __IO uint32_t  FBRD;                              /*!< UART Fractional Baud-Rate Divisor                                     */
    __IO uint32_t  LCRH;                              /*!< UART Line Control                                                     */
    __IO uint32_t  CTL;                               /*!< UART Control                                                          */
    __IO uint32_t  IFLS;                              /*!< UART Interrupt FIFO Level Select                                      */
    __IO uint32_t  IM;                                /*!< UART Interrupt Mask                                                   */
    __IO uint32_t  RIS;                               /*!< UART Raw Interrupt Status                                             */
    __IO uint32_t  MIS;                               /*!< UART Masked Interrupt Status                                          */
    __O  uint32_t  ICR;                               /*!< UART Interrupt Clear                                                  */
    __IO uint32_t  DMACTL;                            /*!< UART DMA Control                                                      */
    __I  uint32_t  RESERVED2[22];
    __IO uint32_t  _9BITADDR;                         /*!< UART 9-Bit Self Address                                               */
    __IO uint32_t  _9BITAMASK;                        /*!< UART 9-Bit Self Address Mask                                          */
    __I  uint32_t  RESERVED3[965];
    __IO uint32_t  PP;                                /*!< UART Peripheral Properties                                            */
    __I  uint32_t  RESERVED4;
    __IO uint32_t  CC;                                /*!< UART Clock Configuration                                              */
} UART0_Type;


/* ================================================================================ */
/* ================                      I2C0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for I2C0 peripheral (I2C0)
  */

typedef struct                                      /*!< I2C0 Structure                                                        */
{
    __IO uint32_t  MSA;                               /*!< I2C Master Slave Address                                              */
    __IO uint32_t  MCS;                               /*!< I2C Master Control/Status                                             */
    __IO uint32_t  MDR;                               /*!< I2C Master Data                                                       */
    __IO uint32_t  MTPR;                              /*!< I2C Master Timer Period                                               */
    __IO uint32_t  MIMR;                              /*!< I2C Master Interrupt Mask                                             */
    __IO uint32_t  MRIS;                              /*!< I2C Master Raw Interrupt Status                                       */
    __IO uint32_t  MMIS;                              /*!< I2C Master Masked Interrupt Status                                    */
    __O  uint32_t  MICR;                              /*!< I2C Master Interrupt Clear                                            */
    __IO uint32_t  MCR;                               /*!< I2C Master Configuration                                              */
    __IO uint32_t  MCLKOCNT;                          /*!< I2C Master Clock Low Timeout Count                                    */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  MBMON;                             /*!< I2C Master Bus Monitor                                                */
    __IO uint32_t  MBLEN;                             /*!< I2C Master Burst Length                                               */
    __IO uint32_t  MBCNT;                             /*!< I2C Master Burst Count                                                */
    __I  uint32_t  RESERVED1[498];
    __IO uint32_t  SOAR;                              /*!< I2C Slave Own Address                                                 */
    __IO uint32_t  SCSR;                              /*!< I2C Slave Control/Status                                              */
    __IO uint32_t  SDR;                               /*!< I2C Slave Data                                                        */
    __IO uint32_t  SIMR;                              /*!< I2C Slave Interrupt Mask                                              */
    __IO uint32_t  SRIS;                              /*!< I2C Slave Raw Interrupt Status                                        */
    __IO uint32_t  SMIS;                              /*!< I2C Slave Masked Interrupt Status                                     */
    __O  uint32_t  SICR;                              /*!< I2C Slave Interrupt Clear                                             */
    __IO uint32_t  SOAR2;                             /*!< I2C Slave Own Address 2                                               */
    __IO uint32_t  SACKCTL;                           /*!< I2C Slave ACK Control                                                 */
    __I  uint32_t  RESERVED2[439];
    __IO uint32_t  FIFODATA;                          /*!< I2C FIFO Data                                                         */
    __IO uint32_t  FIFOCTL;                           /*!< I2C FIFO Control                                                      */
    __IO uint32_t  FIFOSTATUS;                        /*!< I2C FIFO Status                                                       */
    __I  uint32_t  RESERVED3[45];
    __IO uint32_t  PP;                                /*!< I2C Peripheral Properties                                             */
    __IO uint32_t  PC;                                /*!< I2C Peripheral Configuration                                          */
} I2C0_Type;


/* ================================================================================ */
/* ================                      PWM0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for PWM0 peripheral (PWM0)
  */

typedef struct                                      /*!< PWM0 Structure                                                        */
{
    __IO uint32_t  CTL;                               /*!< PWM Master Control                                                    */
    __IO uint32_t  SYNC;                              /*!< PWM Time Base Sync                                                    */
    __IO uint32_t  ENABLE;                            /*!< PWM Output Enable                                                     */
    __IO uint32_t  INVERT;                            /*!< PWM Output Inversion                                                  */
    __IO uint32_t  FAULT;                             /*!< PWM Output Fault                                                      */
    __IO uint32_t  INTEN;                             /*!< PWM Interrupt Enable                                                  */
    __IO uint32_t  RIS;                               /*!< PWM Raw Interrupt Status                                              */
    __IO uint32_t  ISC;                               /*!< PWM Interrupt Status and Clear                                        */
    __IO uint32_t  STATUS;                            /*!< PWM Status                                                            */
    __IO uint32_t  FAULTVAL;                          /*!< PWM Fault Condition Value                                             */
    __IO uint32_t  ENUPD;                             /*!< PWM Enable Update                                                     */
    __I  uint32_t  RESERVED0[5];
    __IO uint32_t  _0_CTL;                            /*!< PWM0 Control                                                          */
    __IO uint32_t  _0_INTEN;                          /*!< PWM0 Interrupt and Trigger Enable                                     */
    __IO uint32_t  _0_RIS;                            /*!< PWM0 Raw Interrupt Status                                             */
    __IO uint32_t  _0_ISC;                            /*!< PWM0 Interrupt Status and Clear                                       */
    __IO uint32_t  _0_LOAD;                           /*!< PWM0 Load                                                             */
    __IO uint32_t  _0_COUNT;                          /*!< PWM0 Counter                                                          */
    __IO uint32_t  _0_CMPA;                           /*!< PWM0 Compare A                                                        */
    __IO uint32_t  _0_CMPB;                           /*!< PWM0 Compare B                                                        */
    __IO uint32_t  _0_GENA;                           /*!< PWM0 Generator A Control                                              */
    __IO uint32_t  _0_GENB;                           /*!< PWM0 Generator B Control                                              */
    __IO uint32_t  _0_DBCTL;                          /*!< PWM0 Dead-Band Control                                                */
    __IO uint32_t  _0_DBRISE;                         /*!< PWM0 Dead-Band Rising-Edge Delay                                      */
    __IO uint32_t  _0_DBFALL;                         /*!< PWM0 Dead-Band Falling-Edge-Delay                                     */
    __IO uint32_t  _0_FLTSRC0;                        /*!< PWM0 Fault Source 0                                                   */
    __IO uint32_t  _0_FLTSRC1;                        /*!< PWM0 Fault Source 1                                                   */
    __IO uint32_t  _0_MINFLTPER;                      /*!< PWM0 Minimum Fault Period                                             */
    __IO uint32_t  _1_CTL;                            /*!< PWM1 Control                                                          */
    __IO uint32_t  _1_INTEN;                          /*!< PWM1 Interrupt and Trigger Enable                                     */
    __IO uint32_t  _1_RIS;                            /*!< PWM1 Raw Interrupt Status                                             */
    __IO uint32_t  _1_ISC;                            /*!< PWM1 Interrupt Status and Clear                                       */
    __IO uint32_t  _1_LOAD;                           /*!< PWM1 Load                                                             */
    __IO uint32_t  _1_COUNT;                          /*!< PWM1 Counter                                                          */
    __IO uint32_t  _1_CMPA;                           /*!< PWM1 Compare A                                                        */
    __IO uint32_t  _1_CMPB;                           /*!< PWM1 Compare B                                                        */
    __IO uint32_t  _1_GENA;                           /*!< PWM1 Generator A Control                                              */
    __IO uint32_t  _1_GENB;                           /*!< PWM1 Generator B Control                                              */
    __IO uint32_t  _1_DBCTL;                          /*!< PWM1 Dead-Band Control                                                */
    __IO uint32_t  _1_DBRISE;                         /*!< PWM1 Dead-Band Rising-Edge Delay                                      */
    __IO uint32_t  _1_DBFALL;                         /*!< PWM1 Dead-Band Falling-Edge-Delay                                     */
    __IO uint32_t  _1_FLTSRC0;                        /*!< PWM1 Fault Source 0                                                   */
    __IO uint32_t  _1_FLTSRC1;                        /*!< PWM1 Fault Source 1                                                   */
    __IO uint32_t  _1_MINFLTPER;                      /*!< PWM1 Minimum Fault Period                                             */
    __IO uint32_t  _2_CTL;                            /*!< PWM2 Control                                                          */
    __IO uint32_t  _2_INTEN;                          /*!< PWM2 Interrupt and Trigger Enable                                     */
    __IO uint32_t  _2_RIS;                            /*!< PWM2 Raw Interrupt Status                                             */
    __IO uint32_t  _2_ISC;                            /*!< PWM2 Interrupt Status and Clear                                       */
    __IO uint32_t  _2_LOAD;                           /*!< PWM2 Load                                                             */
    __IO uint32_t  _2_COUNT;                          /*!< PWM2 Counter                                                          */
    __IO uint32_t  _2_CMPA;                           /*!< PWM2 Compare A                                                        */
    __IO uint32_t  _2_CMPB;                           /*!< PWM2 Compare B                                                        */
    __IO uint32_t  _2_GENA;                           /*!< PWM2 Generator A Control                                              */
    __IO uint32_t  _2_GENB;                           /*!< PWM2 Generator B Control                                              */
    __IO uint32_t  _2_DBCTL;                          /*!< PWM2 Dead-Band Control                                                */
    __IO uint32_t  _2_DBRISE;                         /*!< PWM2 Dead-Band Rising-Edge Delay                                      */
    __IO uint32_t  _2_DBFALL;                         /*!< PWM2 Dead-Band Falling-Edge-Delay                                     */
    __IO uint32_t  _2_FLTSRC0;                        /*!< PWM2 Fault Source 0                                                   */
    __IO uint32_t  _2_FLTSRC1;                        /*!< PWM2 Fault Source 1                                                   */
    __IO uint32_t  _2_MINFLTPER;                      /*!< PWM2 Minimum Fault Period                                             */
    __IO uint32_t  _3_CTL;                            /*!< PWM3 Control                                                          */
    __IO uint32_t  _3_INTEN;                          /*!< PWM3 Interrupt and Trigger Enable                                     */
    __IO uint32_t  _3_RIS;                            /*!< PWM3 Raw Interrupt Status                                             */
    __IO uint32_t  _3_ISC;                            /*!< PWM3 Interrupt Status and Clear                                       */
    __IO uint32_t  _3_LOAD;                           /*!< PWM3 Load                                                             */
    __IO uint32_t  _3_COUNT;                          /*!< PWM3 Counter                                                          */
    __IO uint32_t  _3_CMPA;                           /*!< PWM3 Compare A                                                        */
    __IO uint32_t  _3_CMPB;                           /*!< PWM3 Compare B                                                        */
    __IO uint32_t  _3_GENA;                           /*!< PWM3 Generator A Control                                              */
    __IO uint32_t  _3_GENB;                           /*!< PWM3 Generator B Control                                              */
    __IO uint32_t  _3_DBCTL;                          /*!< PWM3 Dead-Band Control                                                */
    __IO uint32_t  _3_DBRISE;                         /*!< PWM3 Dead-Band Rising-Edge Delay                                      */
    __IO uint32_t  _3_DBFALL;                         /*!< PWM3 Dead-Band Falling-Edge-Delay                                     */
    __IO uint32_t  _3_FLTSRC0;                        /*!< PWM3 Fault Source 0                                                   */
    __IO uint32_t  _3_FLTSRC1;                        /*!< PWM3 Fault Source 1                                                   */
    __IO uint32_t  _3_MINFLTPER;                      /*!< PWM3 Minimum Fault Period                                             */
    __I  uint32_t  RESERVED1[432];
    __IO uint32_t  _0_FLTSEN;                         /*!< PWM0 Fault Pin Logic Sense                                            */
    __I  uint32_t  _0_FLTSTAT0;                       /*!< PWM0 Fault Status 0                                                   */
    __I  uint32_t  _0_FLTSTAT1;                       /*!< PWM0 Fault Status 1                                                   */
    __I  uint32_t  RESERVED2[29];
    __IO uint32_t  _1_FLTSEN;                         /*!< PWM1 Fault Pin Logic Sense                                            */
    __I  uint32_t  _1_FLTSTAT0;                       /*!< PWM1 Fault Status 0                                                   */
    __I  uint32_t  _1_FLTSTAT1;                       /*!< PWM1 Fault Status 1                                                   */
    __I  uint32_t  RESERVED3[29];
    __IO uint32_t  _2_FLTSEN;                         /*!< PWM2 Fault Pin Logic Sense                                            */
    __I  uint32_t  _2_FLTSTAT0;                       /*!< PWM2 Fault Status 0                                                   */
    __I  uint32_t  _2_FLTSTAT1;                       /*!< PWM2 Fault Status 1                                                   */
    __I  uint32_t  RESERVED4[29];
    __IO uint32_t  _3_FLTSEN;                         /*!< PWM3 Fault Pin Logic Sense                                            */
    __I  uint32_t  _3_FLTSTAT0;                       /*!< PWM3 Fault Status 0                                                   */
    __I  uint32_t  _3_FLTSTAT1;                       /*!< PWM3 Fault Status 1                                                   */
    __I  uint32_t  RESERVED5[397];
    __IO uint32_t  PP;                                /*!< PWM Peripheral Properties                                             */
    __I  uint32_t  RESERVED6;
    __IO uint32_t  CC;                                /*!< PWM Clock Configuration                                               */
} PWM0_Type;


/* ================================================================================ */
/* ================                      QEI0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for QEI0 peripheral (QEI0)
  */

typedef struct                                      /*!< QEI0 Structure                                                        */
{
    __IO uint32_t  CTL;                               /*!< QEI Control                                                           */
    __IO uint32_t  STAT;                              /*!< QEI Status                                                            */
    __IO uint32_t  POS;                               /*!< QEI Position                                                          */
    __IO uint32_t  MAXPOS;                            /*!< QEI Maximum Position                                                  */
    __IO uint32_t  LOAD;                              /*!< QEI Timer Load                                                        */
    __IO uint32_t  TIME;                              /*!< QEI Timer                                                             */
    __IO uint32_t  COUNT;                             /*!< QEI Velocity Counter                                                  */
    __IO uint32_t  SPEED;                             /*!< QEI Velocity                                                          */
    __IO uint32_t  INTEN;                             /*!< QEI Interrupt Enable                                                  */
    __IO uint32_t  RIS;                               /*!< QEI Raw Interrupt Status                                              */
    __IO uint32_t  ISC;                               /*!< QEI Interrupt Status and Clear                                        */
} QEI0_Type;


/* ================================================================================ */
/* ================                     TIMER0                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for TIMER0 peripheral (TIMER0)
  */

typedef struct                                      /*!< TIMER0 Structure                                                      */
{
    __IO uint32_t  CFG;                               /*!< GPTM Configuration                                                    */
    __IO uint32_t  TAMR;                              /*!< GPTM Timer A Mode                                                     */
    __IO uint32_t  TBMR;                              /*!< GPTM Timer B Mode                                                     */
    __IO uint32_t  CTL;                               /*!< GPTM Control                                                          */
    __IO uint32_t  SYNC;                              /*!< GPTM Synchronize                                                      */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  IMR;                               /*!< GPTM Interrupt Mask                                                   */
    __IO uint32_t  RIS;                               /*!< GPTM Raw Interrupt Status                                             */
    __IO uint32_t  MIS;                               /*!< GPTM Masked Interrupt Status                                          */
    __O  uint32_t  ICR;                               /*!< GPTM Interrupt Clear                                                  */
    __IO uint32_t  TAILR;                             /*!< GPTM Timer A Interval Load                                            */
    __IO uint32_t  TBILR;                             /*!< GPTM Timer B Interval Load                                            */
    __IO uint32_t  TAMATCHR;                          /*!< GPTM Timer A Match                                                    */
    __IO uint32_t  TBMATCHR;                          /*!< GPTM Timer B Match                                                    */
    __IO uint32_t  TAPR;                              /*!< GPTM Timer A Prescale                                                 */
    __IO uint32_t  TBPR;                              /*!< GPTM Timer B Prescale                                                 */
    __IO uint32_t  TAPMR;                             /*!< GPTM TimerA Prescale Match                                            */
    __IO uint32_t  TBPMR;                             /*!< GPTM TimerB Prescale Match                                            */
    __IO uint32_t  TAR;                               /*!< GPTM Timer A                                                          */
    __IO uint32_t  TBR;                               /*!< GPTM Timer B                                                          */
    __IO uint32_t  TAV;                               /*!< GPTM Timer A Value                                                    */
    __IO uint32_t  TBV;                               /*!< GPTM Timer B Value                                                    */
    __IO uint32_t  RTCPD;                             /*!< GPTM RTC Predivide                                                    */
    __IO uint32_t  TAPS;                              /*!< GPTM Timer A Prescale Snapshot                                        */
    __IO uint32_t  TBPS;                              /*!< GPTM Timer B Prescale Snapshot                                        */
    __IO uint32_t  TAPV;                              /*!< GPTM Timer A Prescale Value                                           */
    __IO uint32_t  TBPV;                              /*!< GPTM Timer B Prescale Value                                           */
    __IO uint32_t  DMAEV;                             /*!< GPTM DMA Event                                                        */
    __IO uint32_t  ADCEV;                             /*!< GPTM ADC Event                                                        */
    __I  uint32_t  RESERVED1[979];
    __IO uint32_t  PP;                                /*!< GPTM Peripheral Properties                                            */
} TIMER0_Type;


/* ================================================================================ */
/* ================                      ADC0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for ADC0 peripheral (ADC0)
  */

typedef struct                                      /*!< ADC0 Structure                                                        */
{
    __IO uint32_t  ACTSS;                             /*!< ADC Active Sample Sequencer                                           */
    __IO uint32_t  RIS;                               /*!< ADC Raw Interrupt Status                                              */
    __IO uint32_t  IM;                                /*!< ADC Interrupt Mask                                                    */
    __IO uint32_t  ISC;                               /*!< ADC Interrupt Status and Clear                                        */
    __IO uint32_t  OSTAT;                             /*!< ADC Overflow Status                                                   */
    __IO uint32_t  EMUX;                              /*!< ADC Event Multiplexer Select                                          */
    __IO uint32_t  USTAT;                             /*!< ADC Underflow Status                                                  */
    __IO uint32_t  TSSEL;                             /*!< ADC Trigger Source Select                                             */
    __IO uint32_t  SSPRI;                             /*!< ADC Sample Sequencer Priority                                         */
    __IO uint32_t  SPC;                               /*!< ADC Sample Phase Control                                              */
    __IO uint32_t  PSSI;                              /*!< ADC Processor Sample Sequence Initiate                                */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  SAC;                               /*!< ADC Sample Averaging Control                                          */
    __IO uint32_t  DCISC;                             /*!< ADC Digital Comparator Interrupt Status and Clear                     */
    __IO uint32_t  CTL;                               /*!< ADC Control                                                           */
    __I  uint32_t  RESERVED1;
    __IO uint32_t  SSMUX0;                            /*!< ADC Sample Sequence Input Multiplexer Select 0                        */
    __IO uint32_t  SSCTL0;                            /*!< ADC Sample Sequence Control 0                                         */
    __IO uint32_t  SSFIFO0;                           /*!< ADC Sample Sequence Result FIFO 0                                     */
    __IO uint32_t  SSFSTAT0;                          /*!< ADC Sample Sequence FIFO 0 Status                                     */
    __IO uint32_t  SSOP0;                             /*!< ADC Sample Sequence 0 Operation                                       */
    __IO uint32_t  SSDC0;                             /*!< ADC Sample Sequence 0 Digital Comparator Select                       */
    __IO uint32_t  SSEMUX0;                           /*!< ADC Sample Sequence Extended Input Multiplexer Select 0               */
    __IO uint32_t  SSTSH0;                            /*!< ADC Sample Sequence 0 Sample and Hold Time                            */
    __IO uint32_t  SSMUX1;                            /*!< ADC Sample Sequence Input Multiplexer Select 1                        */
    __IO uint32_t  SSCTL1;                            /*!< ADC Sample Sequence Control 1                                         */
    __IO uint32_t  SSFIFO1;                           /*!< ADC Sample Sequence Result FIFO 1                                     */
    __IO uint32_t  SSFSTAT1;                          /*!< ADC Sample Sequence FIFO 1 Status                                     */
    __IO uint32_t  SSOP1;                             /*!< ADC Sample Sequence 1 Operation                                       */
    __IO uint32_t  SSDC1;                             /*!< ADC Sample Sequence 1 Digital Comparator Select                       */
    __IO uint32_t  SSEMUX1;                           /*!< ADC Sample Sequence Extended Input Multiplexer Select 1               */
    __IO uint32_t  SSTSH1;                            /*!< ADC Sample Sequence 1 Sample and Hold Time                            */
    __IO uint32_t  SSMUX2;                            /*!< ADC Sample Sequence Input Multiplexer Select 2                        */
    __IO uint32_t  SSCTL2;                            /*!< ADC Sample Sequence Control 2                                         */
    __IO uint32_t  SSFIFO2;                           /*!< ADC Sample Sequence Result FIFO 2                                     */
    __IO uint32_t  SSFSTAT2;                          /*!< ADC Sample Sequence FIFO 2 Status                                     */
    __IO uint32_t  SSOP2;                             /*!< ADC Sample Sequence 2 Operation                                       */
    __IO uint32_t  SSDC2;                             /*!< ADC Sample Sequence 2 Digital Comparator Select                       */
    __IO uint32_t  SSEMUX2;                           /*!< ADC Sample Sequence Extended Input Multiplexer Select 2               */
    __IO uint32_t  SSTSH2;                            /*!< ADC Sample Sequence 2 Sample and Hold Time                            */
    __IO uint32_t  SSMUX3;                            /*!< ADC Sample Sequence Input Multiplexer Select 3                        */
    __IO uint32_t  SSCTL3;                            /*!< ADC Sample Sequence Control 3                                         */
    __IO uint32_t  SSFIFO3;                           /*!< ADC Sample Sequence Result FIFO 3                                     */
    __IO uint32_t  SSFSTAT3;                          /*!< ADC Sample Sequence FIFO 3 Status                                     */
    __IO uint32_t  SSOP3;                             /*!< ADC Sample Sequence 3 Operation                                       */
    __IO uint32_t  SSDC3;                             /*!< ADC Sample Sequence 3 Digital Comparator Select                       */
    __IO uint32_t  SSEMUX3;                           /*!< ADC Sample Sequence Extended Input Multiplexer Select 3               */
    __IO uint32_t  SSTSH3;                            /*!< ADC Sample Sequence 3 Sample and Hold Time                            */
    __I  uint32_t  RESERVED2[784];
    __O  uint32_t  DCRIC;                             /*!< ADC Digital Comparator Reset Initial Conditions                       */
    __I  uint32_t  RESERVED3[63];
    __IO uint32_t  DCCTL0;                            /*!< ADC Digital Comparator Control 0                                      */
    __IO uint32_t  DCCTL1;                            /*!< ADC Digital Comparator Control 1                                      */
    __IO uint32_t  DCCTL2;                            /*!< ADC Digital Comparator Control 2                                      */
    __IO uint32_t  DCCTL3;                            /*!< ADC Digital Comparator Control 3                                      */
    __IO uint32_t  DCCTL4;                            /*!< ADC Digital Comparator Control 4                                      */
    __IO uint32_t  DCCTL5;                            /*!< ADC Digital Comparator Control 5                                      */
    __IO uint32_t  DCCTL6;                            /*!< ADC Digital Comparator Control 6                                      */
    __IO uint32_t  DCCTL7;                            /*!< ADC Digital Comparator Control 7                                      */
    __I  uint32_t  RESERVED4[8];
    __IO uint32_t  DCCMP0;                            /*!< ADC Digital Comparator Range 0                                        */
    __IO uint32_t  DCCMP1;                            /*!< ADC Digital Comparator Range 1                                        */
    __IO uint32_t  DCCMP2;                            /*!< ADC Digital Comparator Range 2                                        */
    __IO uint32_t  DCCMP3;                            /*!< ADC Digital Comparator Range 3                                        */
    __IO uint32_t  DCCMP4;                            /*!< ADC Digital Comparator Range 4                                        */
    __IO uint32_t  DCCMP5;                            /*!< ADC Digital Comparator Range 5                                        */
    __IO uint32_t  DCCMP6;                            /*!< ADC Digital Comparator Range 6                                        */
    __IO uint32_t  DCCMP7;                            /*!< ADC Digital Comparator Range 7                                        */
    __I  uint32_t  RESERVED5[88];
    __IO uint32_t  PP;                                /*!< ADC Peripheral Properties                                             */
    __IO uint32_t  PC;                                /*!< ADC Peripheral Configuration                                          */
    __IO uint32_t  CC;                                /*!< ADC Clock Configuration                                               */
} ADC0_Type;


/* ================================================================================ */
/* ================                      COMP                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for COMP peripheral (COMP)
  */

typedef struct                                      /*!< COMP Structure                                                        */
{
    __IO uint32_t  ACMIS;                             /*!< Analog Comparator Masked Interrupt Status                             */
    __IO uint32_t  ACRIS;                             /*!< Analog Comparator Raw Interrupt Status                                */
    __IO uint32_t  ACINTEN;                           /*!< Analog Comparator Interrupt Enable                                    */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  ACREFCTL;                          /*!< Analog Comparator Reference Voltage Control                           */
    __I  uint32_t  RESERVED1[3];
    __IO uint32_t  ACSTAT0;                           /*!< Analog Comparator Status 0                                            */
    __IO uint32_t  ACCTL0;                            /*!< Analog Comparator Control 0                                           */
    __I  uint32_t  RESERVED2[6];
    __IO uint32_t  ACSTAT1;                           /*!< Analog Comparator Status 1                                            */
    __IO uint32_t  ACCTL1;                            /*!< Analog Comparator Control 1                                           */
    __I  uint32_t  RESERVED3[6];
    __IO uint32_t  ACSTAT2;                           /*!< Analog Comparator Status 2                                            */
    __IO uint32_t  ACCTL2;                            /*!< Analog Comparator Control 2                                           */
    __I  uint32_t  RESERVED4[982];
    __IO uint32_t  PP;                                /*!< Analog Comparator Peripheral Properties                               */
} COMP_Type;


/* ================================================================================ */
/* ================                      CAN0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for CAN0 peripheral (CAN0)
  */

typedef struct                                      /*!< CAN0 Structure                                                        */
{
    __IO uint32_t  CTL;                               /*!< CAN Control                                                           */
    __IO uint32_t  STS;                               /*!< CAN Status                                                            */
    __IO uint32_t  ERR;                               /*!< CAN Error Counter                                                     */
    __IO uint32_t  BIT;                               /*!< CAN Bit Timing                                                        */
    __IO uint32_t  INT;                               /*!< CAN Interrupt                                                         */
    __IO uint32_t  TST;                               /*!< CAN Test                                                              */
    __IO uint32_t  BRPE;                              /*!< CAN Baud Rate Prescaler Extension                                     */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  IF1CRQ;                            /*!< CAN IF1 Command Request                                               */
    __IO uint32_t  IF1CMSK;                           /*!< CAN IF1 Command Mask                                                  */
    __IO uint32_t  IF1MSK1;                           /*!< CAN IF1 Mask 1                                                        */
    __IO uint32_t  IF1MSK2;                           /*!< CAN IF1 Mask 2                                                        */
    __IO uint32_t  IF1ARB1;                           /*!< CAN IF1 Arbitration 1                                                 */
    __IO uint32_t  IF1ARB2;                           /*!< CAN IF1 Arbitration 2                                                 */
    __IO uint32_t  IF1MCTL;                           /*!< CAN IF1 Message Control                                               */
    __IO uint32_t  IF1DA1;                            /*!< CAN IF1 Data A1                                                       */
    __IO uint32_t  IF1DA2;                            /*!< CAN IF1 Data A2                                                       */
    __IO uint32_t  IF1DB1;                            /*!< CAN IF1 Data B1                                                       */
    __IO uint32_t  IF1DB2;                            /*!< CAN IF1 Data B2                                                       */
    __I  uint32_t  RESERVED1[13];
    __IO uint32_t  IF2CRQ;                            /*!< CAN IF2 Command Request                                               */
    __IO uint32_t  IF2CMSK;                           /*!< CAN IF2 Command Mask                                                  */
    __IO uint32_t  IF2MSK1;                           /*!< CAN IF2 Mask 1                                                        */
    __IO uint32_t  IF2MSK2;                           /*!< CAN IF2 Mask 2                                                        */
    __IO uint32_t  IF2ARB1;                           /*!< CAN IF2 Arbitration 1                                                 */
    __IO uint32_t  IF2ARB2;                           /*!< CAN IF2 Arbitration 2                                                 */
    __IO uint32_t  IF2MCTL;                           /*!< CAN IF2 Message Control                                               */
    __IO uint32_t  IF2DA1;                            /*!< CAN IF2 Data A1                                                       */
    __IO uint32_t  IF2DA2;                            /*!< CAN IF2 Data A2                                                       */
    __IO uint32_t  IF2DB1;                            /*!< CAN IF2 Data B1                                                       */
    __IO uint32_t  IF2DB2;                            /*!< CAN IF2 Data B2                                                       */
    __I  uint32_t  RESERVED2[21];
    __IO uint32_t  TXRQ1;                             /*!< CAN Transmission Request 1                                            */
    __IO uint32_t  TXRQ2;                             /*!< CAN Transmission Request 2                                            */
    __I  uint32_t  RESERVED3[6];
    __IO uint32_t  NWDA1;                             /*!< CAN New Data 1                                                        */
    __IO uint32_t  NWDA2;                             /*!< CAN New Data 2                                                        */
    __I  uint32_t  RESERVED4[6];
    __IO uint32_t  MSG1INT;                           /*!< CAN Message 1 Interrupt Pending                                       */
    __IO uint32_t  MSG2INT;                           /*!< CAN Message 2 Interrupt Pending                                       */
    __I  uint32_t  RESERVED5[6];
    __IO uint32_t  MSG1VAL;                           /*!< CAN Message 1 Valid                                                   */
    __IO uint32_t  MSG2VAL;                           /*!< CAN Message 2 Valid                                                   */
} CAN0_Type;


/* ================================================================================ */
/* ================                      USB0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for USB0 peripheral (USB0)
  */

typedef struct                                      /*!< USB0 Structure                                                        */
{
    __IO uint8_t   FADDR;                             /*!< USB Device Functional Address                                         */
    __IO uint8_t   POWER;                             /*!< USB Power                                                             */
    __IO uint16_t  TXIS;                              /*!< USB Transmit Interrupt Status                                         */
    __IO uint16_t  RXIS;                              /*!< USB Receive Interrupt Status                                          */
    __IO uint16_t  TXIE;                              /*!< USB Transmit Interrupt Enable                                         */
    __IO uint16_t  RXIE;                              /*!< USB Receive Interrupt Enable                                          */
    __IO uint8_t   IS;                                /*!< USB General Interrupt Status                                          */
    __IO uint8_t   IE;                                /*!< USB Interrupt Enable                                                  */
    __IO uint16_t  FRAME;                             /*!< USB Frame Value                                                       */
    __IO uint8_t   EPIDX;                             /*!< USB Endpoint Index                                                    */
    __IO uint8_t   TEST;                              /*!< USB Test Mode                                                         */
    __I  uint32_t  RESERVED0[4];
    union
    {
        __IO uint8_t   FIFO0_BYTE;                      /*!< USB FIFO Endpoint 0                                                   */
        __IO uint16_t  FIFO0_HALF;                      /*!< USB FIFO Endpoint 0                                                   */
        __IO uint32_t  FIFO0_WORD;                      /*!< USB FIFO Endpoint 0                                                   */
    };
    union
    {
        __IO uint8_t   FIFO1_BYTE;                      /*!< USB FIFO Endpoint 1                                                   */
        __IO uint16_t  FIFO1_HALF;                      /*!< USB FIFO Endpoint 1                                                   */
        __IO uint32_t  FIFO1_WORD;                      /*!< USB FIFO Endpoint 1                                                   */
    };
    union
    {
        __IO uint8_t   FIFO2_BYTE;                      /*!< USB FIFO Endpoint 2                                                   */
        __IO uint16_t  FIFO2_HALF;                      /*!< USB FIFO Endpoint 2                                                   */
        __IO uint32_t  FIFO2_WORD;                      /*!< USB FIFO Endpoint 2                                                   */
    };
    union
    {
        __IO uint8_t   FIFO3_BYTE;                      /*!< USB FIFO Endpoint 3                                                   */
        __IO uint16_t  FIFO3_HALF;                      /*!< USB FIFO Endpoint 3                                                   */
        __IO uint32_t  FIFO3_WORD;                      /*!< USB FIFO Endpoint 3                                                   */
    };
    union
    {
        __IO uint8_t   FIFO4_BYTE;                      /*!< USB FIFO Endpoint 4                                                   */
        __IO uint16_t  FIFO4_HALF;                      /*!< USB FIFO Endpoint 4                                                   */
        __IO uint32_t  FIFO4_WORD;                      /*!< USB FIFO Endpoint 4                                                   */
    };
    union
    {
        __IO uint8_t   FIFO5_BYTE;                      /*!< USB FIFO Endpoint 5                                                   */
        __IO uint16_t  FIFO5_HALF;                      /*!< USB FIFO Endpoint 5                                                   */
        __IO uint32_t  FIFO5_WORD;                      /*!< USB FIFO Endpoint 5                                                   */
    };
    union
    {
        __IO uint8_t   FIFO6_BYTE;                      /*!< USB FIFO Endpoint 6                                                   */
        __IO uint16_t  FIFO6_HALF;                      /*!< USB FIFO Endpoint 6                                                   */
        __IO uint32_t  FIFO6_WORD;                      /*!< USB FIFO Endpoint 6                                                   */
    };
    union
    {
        __IO uint8_t   FIFO7_BYTE;                      /*!< USB FIFO Endpoint 7                                                   */
        __IO uint16_t  FIFO7_HALF;                      /*!< USB FIFO Endpoint 7                                                   */
        __IO uint32_t  FIFO7_WORD;                      /*!< USB FIFO Endpoint 7                                                   */
    };
    __I  uint32_t  RESERVED1[8];
    __IO uint8_t   DEVCTL;                            /*!< USB Device Control                                                    */
    __IO uint8_t   CCONF;                             /*!< USB Common Configuration                                              */
    __IO uint8_t   TXFIFOSZ;                          /*!< USB Transmit Dynamic FIFO Sizing                                      */
    __IO uint8_t   RXFIFOSZ;                          /*!< USB Receive Dynamic FIFO Sizing                                       */
    __IO uint16_t  TXFIFOADD;                         /*!< USB Transmit FIFO Start Address                                       */
    __IO uint16_t  RXFIFOADD;                         /*!< USB Receive FIFO Start Address                                        */
    __I  uint32_t  RESERVED2[2];
    __IO uint8_t   ULPIVBUSCTL;                       /*!< USB ULPI VBUS Control                                                 */
    __I  uint8_t   RESERVED3[3];
    __IO uint8_t   ULPIREGDATA;                       /*!< USB ULPI Register Data                                                */
    __IO uint8_t   ULPIREGADDR;                       /*!< USB ULPI Register Address                                             */
    __IO uint8_t   ULPIREGCTL;                        /*!< USB ULPI Register Control                                             */
    __I  uint8_t   RESERVED4;
    __IO uint8_t   EPINFO;                            /*!< USB Endpoint Information                                              */
    __IO uint8_t   RAMINFO;                           /*!< USB RAM Information                                                   */
    __IO uint8_t   CONTIM;                            /*!< USB Connect Timing                                                    */
    __IO uint8_t   VPLEN;                             /*!< USB OTG VBUS Pulse Timing                                             */
    __IO uint8_t   HSEOF;                             /*!< USB High-Speed Last Transaction to End of Frame Timing                */
    __IO uint8_t   FSEOF;                             /*!< USB Full-Speed Last Transaction to End of Frame Timing                */
    __IO uint8_t   LSEOF;                             /*!< USB Low-Speed Last Transaction to End of Frame Timing                 */
    __I  uint8_t   RESERVED5;
    __IO uint8_t   TXFUNCADDR0;                       /*!< USB Transmit Functional Address Endpoint 0                            */
    __I  uint8_t   RESERVED6;
    __IO uint8_t   TXHUBADDR0;                        /*!< USB Transmit Hub Address Endpoint 0                                   */
    __IO uint8_t   TXHUBPORT0;                        /*!< USB Transmit Hub Port Endpoint 0                                      */
    __I  uint32_t  RESERVED7;
    __IO uint8_t   TXFUNCADDR1;                       /*!< USB Transmit Functional Address Endpoint 1                            */
    __I  uint8_t   RESERVED8;
    __IO uint8_t   TXHUBADDR1;                        /*!< USB Transmit Hub Address Endpoint 1                                   */
    __IO uint8_t   TXHUBPORT1;                        /*!< USB Transmit Hub Port Endpoint 1                                      */
    __IO uint8_t   RXFUNCADDR1;                       /*!< USB Receive Functional Address Endpoint 1                             */
    __I  uint8_t   RESERVED9;
    __IO uint8_t   RXHUBADDR1;                        /*!< USB Receive Hub Address Endpoint 1                                    */
    __IO uint8_t   RXHUBPORT1;                        /*!< USB Receive Hub Port Endpoint 1                                       */
    __IO uint8_t   TXFUNCADDR2;                       /*!< USB Transmit Functional Address Endpoint 2                            */
    __I  uint8_t   RESERVED10;
    __IO uint8_t   TXHUBADDR2;                        /*!< USB Transmit Hub Address Endpoint 2                                   */
    __IO uint8_t   TXHUBPORT2;                        /*!< USB Transmit Hub Port Endpoint 2                                      */
    __IO uint8_t   RXFUNCADDR2;                       /*!< USB Receive Functional Address Endpoint 2                             */
    __I  uint8_t   RESERVED11;
    __IO uint8_t   RXHUBADDR2;                        /*!< USB Receive Hub Address Endpoint 2                                    */
    __IO uint8_t   RXHUBPORT2;                        /*!< USB Receive Hub Port Endpoint 2                                       */
    __IO uint8_t   TXFUNCADDR3;                       /*!< USB Transmit Functional Address Endpoint 3                            */
    __I  uint8_t   RESERVED12;
    __IO uint8_t   TXHUBADDR3;                        /*!< USB Transmit Hub Address Endpoint 3                                   */
    __IO uint8_t   TXHUBPORT3;                        /*!< USB Transmit Hub Port Endpoint 3                                      */
    __IO uint8_t   RXFUNCADDR3;                       /*!< USB Receive Functional Address Endpoint 3                             */
    __I  uint8_t   RESERVED13;
    __IO uint8_t   RXHUBADDR3;                        /*!< USB Receive Hub Address Endpoint 3                                    */
    __IO uint8_t   RXHUBPORT3;                        /*!< USB Receive Hub Port Endpoint 3                                       */
    __IO uint8_t   TXFUNCADDR4;                       /*!< USB Transmit Functional Address Endpoint 4                            */
    __I  uint8_t   RESERVED14;
    __IO uint8_t   TXHUBADDR4;                        /*!< USB Transmit Hub Address Endpoint 4                                   */
    __IO uint8_t   TXHUBPORT4;                        /*!< USB Transmit Hub Port Endpoint 4                                      */
    __IO uint8_t   RXFUNCADDR4;                       /*!< USB Receive Functional Address Endpoint 4                             */
    __I  uint8_t   RESERVED15;
    __IO uint8_t   RXHUBADDR4;                        /*!< USB Receive Hub Address Endpoint 4                                    */
    __IO uint8_t   RXHUBPORT4;                        /*!< USB Receive Hub Port Endpoint 4                                       */
    __IO uint8_t   TXFUNCADDR5;                       /*!< USB Transmit Functional Address Endpoint 5                            */
    __I  uint8_t   RESERVED16;
    __IO uint8_t   TXHUBADDR5;                        /*!< USB Transmit Hub Address Endpoint 5                                   */
    __IO uint8_t   TXHUBPORT5;                        /*!< USB Transmit Hub Port Endpoint 5                                      */
    __IO uint8_t   RXFUNCADDR5;                       /*!< USB Receive Functional Address Endpoint 5                             */
    __I  uint8_t   RESERVED17;
    __IO uint8_t   RXHUBADDR5;                        /*!< USB Receive Hub Address Endpoint 5                                    */
    __IO uint8_t   RXHUBPORT5;                        /*!< USB Receive Hub Port Endpoint 5                                       */
    __IO uint8_t   TXFUNCADDR6;                       /*!< USB Transmit Functional Address Endpoint 6                            */
    __I  uint8_t   RESERVED18;
    __IO uint8_t   TXHUBADDR6;                        /*!< USB Transmit Hub Address Endpoint 6                                   */
    __IO uint8_t   TXHUBPORT6;                        /*!< USB Transmit Hub Port Endpoint 6                                      */
    __IO uint8_t   RXFUNCADDR6;                       /*!< USB Receive Functional Address Endpoint 6                             */
    __I  uint8_t   RESERVED19;
    __IO uint8_t   RXHUBADDR6;                        /*!< USB Receive Hub Address Endpoint 6                                    */
    __IO uint8_t   RXHUBPORT6;                        /*!< USB Receive Hub Port Endpoint 6                                       */
    __IO uint8_t   TXFUNCADDR7;                       /*!< USB Transmit Functional Address Endpoint 7                            */
    __I  uint8_t   RESERVED20;
    __IO uint8_t   TXHUBADDR7;                        /*!< USB Transmit Hub Address Endpoint 7                                   */
    __IO uint8_t   TXHUBPORT7;                        /*!< USB Transmit Hub Port Endpoint 7                                      */
    __IO uint8_t   RXFUNCADDR7;                       /*!< USB Receive Functional Address Endpoint 7                             */
    __I  uint8_t   RESERVED21;
    __IO uint8_t   RXHUBADDR7;                        /*!< USB Receive Hub Address Endpoint 7                                    */
    __IO uint8_t   RXHUBPORT7;                        /*!< USB Receive Hub Port Endpoint 7                                       */
    __I  uint32_t  RESERVED22[16];
    __I  uint16_t  RESERVED23;
    __O  uint8_t   CSRL0;                             /*!< USB Control and Status Endpoint 0 Low                                 */
    __O  uint8_t   CSRH0;                             /*!< USB Control and Status Endpoint 0 High                                */
    __I  uint16_t  RESERVED24[2];
    __IO uint8_t   COUNT0;                            /*!< USB Receive Byte Count Endpoint 0                                     */
    __I  uint8_t   RESERVED25;
    __IO uint8_t   TYPE0;                             /*!< USB Type Endpoint 0                                                   */
    __IO uint8_t   NAKLMT;                            /*!< USB NAK Limit                                                         */
    __I  uint32_t  RESERVED26;
    __IO uint16_t  TXMAXP1;                           /*!< USB Maximum Transmit Data Endpoint 1                                  */
    __IO uint8_t   TXCSRL1;                           /*!< USB Transmit Control and Status Endpoint 1 Low                        */
    __IO uint8_t   TXCSRH1;                           /*!< USB Transmit Control and Status Endpoint 1 High                       */
    __IO uint16_t  RXMAXP1;                           /*!< USB Maximum Receive Data Endpoint 1                                   */
    __IO uint8_t   RXCSRL1;                           /*!< USB Receive Control and Status Endpoint 1 Low                         */
    __IO uint8_t   RXCSRH1;                           /*!< USB Receive Control and Status Endpoint 1 High                        */
    __IO uint16_t  RXCOUNT1;                          /*!< USB Receive Byte Count Endpoint 1                                     */
    __IO uint8_t   TXTYPE1;                           /*!< USB Host Transmit Configure Type Endpoint 1                           */
    __IO uint8_t   TXINTERVAL1;                       /*!< USB Host Transmit Interval Endpoint 1                                 */
    __IO uint8_t   RXTYPE1;                           /*!< USB Host Configure Receive Type Endpoint 1                            */
    __IO uint8_t   RXINTERVAL1;                       /*!< USB Host Receive Polling Interval Endpoint 1                          */
    __I  uint16_t  RESERVED27;
    __IO uint16_t  TXMAXP2;                           /*!< USB Maximum Transmit Data Endpoint 2                                  */
    __IO uint8_t   TXCSRL2;                           /*!< USB Transmit Control and Status Endpoint 2 Low                        */
    __IO uint8_t   TXCSRH2;                           /*!< USB Transmit Control and Status Endpoint 2 High                       */
    __IO uint16_t  RXMAXP2;                           /*!< USB Maximum Receive Data Endpoint 2                                   */
    __IO uint8_t   RXCSRL2;                           /*!< USB Receive Control and Status Endpoint 2 Low                         */
    __IO uint8_t   RXCSRH2;                           /*!< USB Receive Control and Status Endpoint 2 High                        */
    __IO uint16_t  RXCOUNT2;                          /*!< USB Receive Byte Count Endpoint 2                                     */
    __IO uint8_t   TXTYPE2;                           /*!< USB Host Transmit Configure Type Endpoint 2                           */
    __IO uint8_t   TXINTERVAL2;                       /*!< USB Host Transmit Interval Endpoint 2                                 */
    __IO uint8_t   RXTYPE2;                           /*!< USB Host Configure Receive Type Endpoint 2                            */
    __IO uint8_t   RXINTERVAL2;                       /*!< USB Host Receive Polling Interval Endpoint 2                          */
    __I  uint16_t  RESERVED28;
    __IO uint16_t  TXMAXP3;                           /*!< USB Maximum Transmit Data Endpoint 3                                  */
    __IO uint8_t   TXCSRL3;                           /*!< USB Transmit Control and Status Endpoint 3 Low                        */
    __IO uint8_t   TXCSRH3;                           /*!< USB Transmit Control and Status Endpoint 3 High                       */
    __IO uint16_t  RXMAXP3;                           /*!< USB Maximum Receive Data Endpoint 3                                   */
    __IO uint8_t   RXCSRL3;                           /*!< USB Receive Control and Status Endpoint 3 Low                         */
    __IO uint8_t   RXCSRH3;                           /*!< USB Receive Control and Status Endpoint 3 High                        */
    __IO uint16_t  RXCOUNT3;                          /*!< USB Receive Byte Count Endpoint 3                                     */
    __IO uint8_t   TXTYPE3;                           /*!< USB Host Transmit Configure Type Endpoint 3                           */
    __IO uint8_t   TXINTERVAL3;                       /*!< USB Host Transmit Interval Endpoint 3                                 */
    __IO uint8_t   RXTYPE3;                           /*!< USB Host Configure Receive Type Endpoint 3                            */
    __IO uint8_t   RXINTERVAL3;                       /*!< USB Host Receive Polling Interval Endpoint 3                          */
    __I  uint16_t  RESERVED29;
    __IO uint16_t  TXMAXP4;                           /*!< USB Maximum Transmit Data Endpoint 4                                  */
    __IO uint8_t   TXCSRL4;                           /*!< USB Transmit Control and Status Endpoint 4 Low                        */
    __IO uint8_t   TXCSRH4;                           /*!< USB Transmit Control and Status Endpoint 4 High                       */
    __IO uint16_t  RXMAXP4;                           /*!< USB Maximum Receive Data Endpoint 4                                   */
    __IO uint8_t   RXCSRL4;                           /*!< USB Receive Control and Status Endpoint 4 Low                         */
    __IO uint8_t   RXCSRH4;                           /*!< USB Receive Control and Status Endpoint 4 High                        */
    __IO uint16_t  RXCOUNT4;                          /*!< USB Receive Byte Count Endpoint 4                                     */
    __IO uint8_t   TXTYPE4;                           /*!< USB Host Transmit Configure Type Endpoint 4                           */
    __IO uint8_t   TXINTERVAL4;                       /*!< USB Host Transmit Interval Endpoint 4                                 */
    __IO uint8_t   RXTYPE4;                           /*!< USB Host Configure Receive Type Endpoint 4                            */
    __IO uint8_t   RXINTERVAL4;                       /*!< USB Host Receive Polling Interval Endpoint 4                          */
    __I  uint16_t  RESERVED30;
    __IO uint16_t  TXMAXP5;                           /*!< USB Maximum Transmit Data Endpoint 5                                  */
    __IO uint8_t   TXCSRL5;                           /*!< USB Transmit Control and Status Endpoint 5 Low                        */
    __IO uint8_t   TXCSRH5;                           /*!< USB Transmit Control and Status Endpoint 5 High                       */
    __IO uint16_t  RXMAXP5;                           /*!< USB Maximum Receive Data Endpoint 5                                   */
    __IO uint8_t   RXCSRL5;                           /*!< USB Receive Control and Status Endpoint 5 Low                         */
    __IO uint8_t   RXCSRH5;                           /*!< USB Receive Control and Status Endpoint 5 High                        */
    __IO uint16_t  RXCOUNT5;                          /*!< USB Receive Byte Count Endpoint 5                                     */
    __IO uint8_t   TXTYPE5;                           /*!< USB Host Transmit Configure Type Endpoint 5                           */
    __IO uint8_t   TXINTERVAL5;                       /*!< USB Host Transmit Interval Endpoint 5                                 */
    __IO uint8_t   RXTYPE5;                           /*!< USB Host Configure Receive Type Endpoint 5                            */
    __IO uint8_t   RXINTERVAL5;                       /*!< USB Host Receive Polling Interval Endpoint 5                          */
    __I  uint16_t  RESERVED31;
    __IO uint16_t  TXMAXP6;                           /*!< USB Maximum Transmit Data Endpoint 6                                  */
    __IO uint8_t   TXCSRL6;                           /*!< USB Transmit Control and Status Endpoint 6 Low                        */
    __IO uint8_t   TXCSRH6;                           /*!< USB Transmit Control and Status Endpoint 6 High                       */
    __IO uint16_t  RXMAXP6;                           /*!< USB Maximum Receive Data Endpoint 6                                   */
    __IO uint8_t   RXCSRL6;                           /*!< USB Receive Control and Status Endpoint 6 Low                         */
    __IO uint8_t   RXCSRH6;                           /*!< USB Receive Control and Status Endpoint 6 High                        */
    __IO uint16_t  RXCOUNT6;                          /*!< USB Receive Byte Count Endpoint 6                                     */
    __IO uint8_t   TXTYPE6;                           /*!< USB Host Transmit Configure Type Endpoint 6                           */
    __IO uint8_t   TXINTERVAL6;                       /*!< USB Host Transmit Interval Endpoint 6                                 */
    __IO uint8_t   RXTYPE6;                           /*!< USB Host Configure Receive Type Endpoint 6                            */
    __IO uint8_t   RXINTERVAL6;                       /*!< USB Host Receive Polling Interval Endpoint 6                          */
    __I  uint16_t  RESERVED32;
    __IO uint16_t  TXMAXP7;                           /*!< USB Maximum Transmit Data Endpoint 7                                  */
    __IO uint8_t   TXCSRL7;                           /*!< USB Transmit Control and Status Endpoint 7 Low                        */
    __IO uint8_t   TXCSRH7;                           /*!< USB Transmit Control and Status Endpoint 7 High                       */
    __IO uint16_t  RXMAXP7;                           /*!< USB Maximum Receive Data Endpoint 7                                   */
    __IO uint8_t   RXCSRL7;                           /*!< USB Receive Control and Status Endpoint 7 Low                         */
    __IO uint8_t   RXCSRH7;                           /*!< USB Receive Control and Status Endpoint 7 High                        */
    __IO uint16_t  RXCOUNT7;                          /*!< USB Receive Byte Count Endpoint 7                                     */
    __IO uint8_t   TXTYPE7;                           /*!< USB Host Transmit Configure Type Endpoint 7                           */
    __IO uint8_t   TXINTERVAL7;                       /*!< USB Host Transmit Interval Endpoint 7                                 */
    __IO uint8_t   RXTYPE7;                           /*!< USB Host Configure Receive Type Endpoint 7                            */
    __IO uint8_t   RXINTERVAL7;                       /*!< USB Host Receive Polling Interval Endpoint 7                          */
    __I  uint16_t  RESERVED33[65];
    __IO uint8_t   DMAINTR;                           /*!< USB DMA Interrupt                                                     */
    __I  uint8_t   RESERVED34[3];
    __IO uint16_t  DMACTL0;                           /*!< USB DMA Control 0                                                     */
    __I  uint16_t  RESERVED35;
    __IO uint32_t  DMAADDR0;                          /*!< USB DMA Address 0                                                     */
    __IO uint32_t  DMACOUNT0;                         /*!< USB DMA Count 0                                                       */
    __I  uint32_t  RESERVED36;
    __IO uint16_t  DMACTL1;                           /*!< USB DMA Control 1                                                     */
    __I  uint16_t  RESERVED37;
    __IO uint32_t  DMAADDR1;                          /*!< USB DMA Address 1                                                     */
    __IO uint32_t  DMACOUNT1;                         /*!< USB DMA Count 1                                                       */
    __I  uint32_t  RESERVED38;
    __IO uint16_t  DMACTL2;                           /*!< USB DMA Control 2                                                     */
    __I  uint16_t  RESERVED39;
    __IO uint32_t  DMAADDR2;                          /*!< USB DMA Address 2                                                     */
    __IO uint32_t  DMACOUNT2;                         /*!< USB DMA Count 2                                                       */
    __I  uint32_t  RESERVED40;
    __IO uint16_t  DMACTL3;                           /*!< USB DMA Control 3                                                     */
    __I  uint16_t  RESERVED41;
    __IO uint32_t  DMAADDR3;                          /*!< USB DMA Address 3                                                     */
    __IO uint32_t  DMACOUNT3;                         /*!< USB DMA Count 3                                                       */
    __I  uint32_t  RESERVED42;
    __IO uint16_t  DMACTL4;                           /*!< USB DMA Control 4                                                     */
    __I  uint16_t  RESERVED43;
    __IO uint32_t  DMAADDR4;                          /*!< USB DMA Address 4                                                     */
    __IO uint32_t  DMACOUNT4;                         /*!< USB DMA Count 4                                                       */
    __I  uint32_t  RESERVED44;
    __IO uint16_t  DMACTL5;                           /*!< USB DMA Control 5                                                     */
    __I  uint16_t  RESERVED45;
    __IO uint32_t  DMAADDR5;                          /*!< USB DMA Address 5                                                     */
    __IO uint32_t  DMACOUNT5;                         /*!< USB DMA Count 5                                                       */
    __I  uint32_t  RESERVED46;
    __IO uint16_t  DMACTL6;                           /*!< USB DMA Control 6                                                     */
    __I  uint16_t  RESERVED47;
    __IO uint32_t  DMAADDR6;                          /*!< USB DMA Address 6                                                     */
    __IO uint32_t  DMACOUNT6;                         /*!< USB DMA Count 6                                                       */
    __I  uint32_t  RESERVED48;
    __IO uint16_t  DMACTL7;                           /*!< USB DMA Control 7                                                     */
    __I  uint16_t  RESERVED49;
    __IO uint32_t  DMAADDR7;                          /*!< USB DMA Address 7                                                     */
    __IO uint32_t  DMACOUNT7;                         /*!< USB DMA Count 7                                                       */
    __I  uint32_t  RESERVED50[33];
    __IO uint16_t  RQPKTCOUNT1;                       /*!< USB Request Packet Count in Block Transfer Endpoint 1                 */
    __I  uint16_t  RESERVED51;
    __IO uint16_t  RQPKTCOUNT2;                       /*!< USB Request Packet Count in Block Transfer Endpoint 2                 */
    __I  uint16_t  RESERVED52;
    __IO uint16_t  RQPKTCOUNT3;                       /*!< USB Request Packet Count in Block Transfer Endpoint 3                 */
    __I  uint16_t  RESERVED53;
    __IO uint16_t  RQPKTCOUNT4;                       /*!< USB Request Packet Count in Block Transfer Endpoint 4                 */
    __I  uint16_t  RESERVED54;
    __IO uint16_t  RQPKTCOUNT5;                       /*!< USB Request Packet Count in Block Transfer Endpoint 5                 */
    __I  uint16_t  RESERVED55;
    __IO uint16_t  RQPKTCOUNT6;                       /*!< USB Request Packet Count in Block Transfer Endpoint 6                 */
    __I  uint16_t  RESERVED56;
    __IO uint16_t  RQPKTCOUNT7;                       /*!< USB Request Packet Count in Block Transfer Endpoint 7                 */
    __I  uint16_t  RESERVED57[17];
    __IO uint16_t  RXDPKTBUFDIS;                      /*!< USB Receive Double Packet Buffer Disable                              */
    __IO uint16_t  TXDPKTBUFDIS;                      /*!< USB Transmit Double Packet Buffer Disable                             */
    __IO uint16_t  CTO;                               /*!< USB Chirp Timeout                                                     */
    __IO uint16_t  HHSRTN;                            /*!< USB High Speed to UTM Operating Delay                                 */
    __IO uint16_t  HSBT;                              /*!< USB High Speed Time-out Adder                                         */
    __I  uint16_t  RESERVED58[11];
    __IO uint16_t  LPMATTR;                           /*!< USB LPM Attributes                                                    */
    __IO uint8_t   LPMCNTRL;                          /*!< USB LPM Control                                                       */
    __IO uint8_t   LPMIM;                             /*!< USB LPM Interrupt Mask                                                */
    __IO uint8_t   LPMRIS;                            /*!< USB LPM Raw Interrupt Status                                          */
    __IO uint8_t   LPMFADDR;                          /*!< USB LPM Function Address                                              */
    __I  uint16_t  RESERVED59[77];
    __IO uint32_t  EPC;                               /*!< USB External Power Control                                            */
    __IO uint32_t  EPCRIS;                            /*!< USB External Power Control Raw Interrupt Status                       */
    __IO uint32_t  EPCIM;                             /*!< USB External Power Control Interrupt Mask                             */
    __IO uint32_t  EPCISC;                            /*!< USB External Power Control Interrupt Status and Clear                 */
    __IO uint32_t  DRRIS;                             /*!< USB Device RESUME Raw Interrupt Status                                */
    __IO uint32_t  DRIM;                              /*!< USB Device RESUME Interrupt Mask                                      */
    __O  uint32_t  DRISC;                             /*!< USB Device RESUME Interrupt Status and Clear                          */
    __IO uint32_t  GPCS;                              /*!< USB General-Purpose Control and Status                                */
    __I  uint32_t  RESERVED60[4];
    __IO uint32_t  VDC;                               /*!< USB VBUS Droop Control                                                */
    __IO uint32_t  VDCRIS;                            /*!< USB VBUS Droop Control Raw Interrupt Status                           */
    __IO uint32_t  VDCIM;                             /*!< USB VBUS Droop Control Interrupt Mask                                 */
    __IO uint32_t  VDCISC;                            /*!< USB VBUS Droop Control Interrupt Status and Clear                     */
    __I  uint32_t  RESERVED61[736];
    __IO uint32_t  PP;                                /*!< USB Peripheral Properties                                             */
    __IO uint32_t  PC;                                /*!< USB Peripheral Configuration                                          */
    __IO uint32_t  CC;                                /*!< USB Clock Configuration                                               */
} USB0_Type;


/* ================================================================================ */
/* ================                    GPIO                        ================ */
/* ================================================================================ */


/**
  * @brief Register map for GPIO peripheral (GPIO)
  */

typedef struct                                      /*!< GPIO Structure                                                        */
{
    __I  uint32_t  RESERVED0[255];
    __IO uint32_t  DATA;                              /*!< GPIO Data                                                             */
    __IO uint32_t  DIR;                               /*!< GPIO Direction                                                        */
    __IO uint32_t  IS;                                /*!< GPIO Interrupt Sense                                                  */
    __IO uint32_t  IBE;                               /*!< GPIO Interrupt Both Edges                                             */
    __IO uint32_t  IEV;                               /*!< GPIO Interrupt Event                                                  */
    __IO uint32_t  IM;                                /*!< GPIO Interrupt Mask                                                   */
    __IO uint32_t  RIS;                               /*!< GPIO Raw Interrupt Status                                             */
    __IO uint32_t  MIS;                               /*!< GPIO Masked Interrupt Status                                          */
    __O  uint32_t  ICR;                               /*!< GPIO Interrupt Clear                                                  */
    __IO uint32_t  AFSEL;                             /*!< GPIO Alternate Function Select                                        */
    __I  uint32_t  RESERVED1[55];
    __IO uint32_t  DR2R;                              /*!< GPIO 2-mA Drive Select                                                */
    __IO uint32_t  DR4R;                              /*!< GPIO 4-mA Drive Select                                                */
    __IO uint32_t  DR8R;                              /*!< GPIO 8-mA Drive Select                                                */
    __IO uint32_t  ODR;                               /*!< GPIO Open Drain Select                                                */
    __IO uint32_t  PUR;                               /*!< GPIO Pull-Up Select                                                   */
    __IO uint32_t  PDR;                               /*!< GPIO Pull-Down Select                                                 */
    __IO uint32_t  SLR;                               /*!< GPIO Slew Rate Control Select                                         */
    __IO uint32_t  DEN;                               /*!< GPIO Digital Enable                                                   */
    __IO uint32_t  LOCK;                              /*!< GPIO Lock                                                             */
    __IO uint32_t  CR;                                /*!< GPIO Commit                                                           */
    __IO uint32_t  AMSEL;                             /*!< GPIO Analog Mode Select                                               */
    __IO uint32_t  PCTL;                              /*!< GPIO Port Control                                                     */
    __IO uint32_t  ADCCTL;                            /*!< GPIO ADC Control                                                      */
    __IO uint32_t  DMACTL;                            /*!< GPIO DMA Control                                                      */
    __IO uint32_t  SI;                                /*!< GPIO Select Interrupt                                                 */
    __IO uint32_t  DR12R;                             /*!< GPIO 12-mA Drive Select                                               */
    __IO uint32_t  WAKEPEN;                           /*!< GPIO Wake Pin Enable                                                  */
    __IO uint32_t  WAKELVL;                           /*!< GPIO Wake Level                                                       */
    __IO uint32_t  WAKESTAT;                          /*!< GPIO Wake Status                                                      */
    __I  uint32_t  RESERVED2[669];
    __IO uint32_t  PP;                                /*!< GPIO Peripheral Property                                              */
    __IO uint32_t  PC;                                /*!< GPIO Peripheral Configuration                                         */
} GPIO_Type;


/* ================================================================================ */
/* ================                     EEPROM                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for EEPROM peripheral (EEPROM)
  */

typedef struct                                      /*!< EEPROM Structure                                                      */
{
    __IO uint32_t  EESIZE;                            /*!< EEPROM Size Information                                               */
    __IO uint32_t  EEBLOCK;                           /*!< EEPROM Current Block                                                  */
    __IO uint32_t  EEOFFSET;                          /*!< EEPROM Current Offset                                                 */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  EERDWR;                            /*!< EEPROM Read-Write                                                     */
    __IO uint32_t  EERDWRINC;                         /*!< EEPROM Read-Write with Increment                                      */
    __IO uint32_t  EEDONE;                            /*!< EEPROM Done Status                                                    */
    __IO uint32_t  EESUPP;                            /*!< EEPROM Support Control and Status                                     */
    __IO uint32_t  EEUNLOCK;                          /*!< EEPROM Unlock                                                         */
    __I  uint32_t  RESERVED1[3];
    __IO uint32_t  EEPROT;                            /*!< EEPROM Protection                                                     */
    __IO uint32_t  EEPASS0;                           /*!< EEPROM Password                                                       */
    __IO uint32_t  EEPASS1;                           /*!< EEPROM Password                                                       */
    __IO uint32_t  EEPASS2;                           /*!< EEPROM Password                                                       */
    __IO uint32_t  EEINT;                             /*!< EEPROM Interrupt                                                      */
    __I  uint32_t  RESERVED2[3];
    __IO uint32_t  EEHIDE0;                           /*!< EEPROM Block Hide 0                                                   */
    __IO uint32_t  EEHIDE1;                           /*!< EEPROM Block Hide 1                                                   */
    __IO uint32_t  EEHIDE2;                           /*!< EEPROM Block Hide 2                                                   */
    __I  uint32_t  RESERVED3[9];
    __IO uint32_t  EEDBGME;                           /*!< EEPROM Debug Mass Erase                                               */
    __I  uint32_t  RESERVED4[975];
    __IO uint32_t  PP;                                /*!< EEPROM Peripheral Properties                                          */
} EEPROM_Type;


/* ================================================================================ */
/* ================                      EPI0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for EPI0 peripheral (EPI0)
  */

typedef struct                                      /*!< EPI0 Structure                                                        */
{
    __IO uint32_t  CFG;                               /*!< EPI Configuration                                                     */
    __IO uint32_t  BAUD;                              /*!< EPI Main Baud Rate                                                    */
    __IO uint32_t  BAUD2;                             /*!< EPI Main Baud Rate                                                    */
    __I  uint32_t  RESERVED0;

    union
    {
        __IO uint32_t  HB16CFG;                         /*!< EPI Host-Bus 16 Configuration                                         */
        __IO uint32_t  GPCFG;                           /*!< EPI General-Purpose Configuration                                     */
        __IO uint32_t  SDRAMCFG;                        /*!< EPI SDRAM Configuration                                               */
        __IO uint32_t  HB8CFG;                          /*!< EPI Host-Bus 8 Configuration                                          */
    };

    union
    {
        __IO uint32_t  HB8CFG2;                         /*!< EPI Host-Bus 8 Configuration 2                                        */
        __IO uint32_t  HB16CFG2;                        /*!< EPI Host-Bus 16 Configuration 2                                       */
    };
    __I  uint32_t  RESERVED1;
    __IO uint32_t  ADDRMAP;                           /*!< EPI Address Map                                                       */
    __IO uint32_t  RSIZE0;                            /*!< EPI Read Size 0                                                       */
    __IO uint32_t  RADDR0;                            /*!< EPI Read Address 0                                                    */
    __IO uint32_t  RPSTD0;                            /*!< EPI Non-Blocking Read Data 0                                          */
    __I  uint32_t  RESERVED2;
    __IO uint32_t  RSIZE1;                            /*!< EPI Read Size 1                                                       */
    __IO uint32_t  RADDR1;                            /*!< EPI Read Address 1                                                    */
    __IO uint32_t  RPSTD1;                            /*!< EPI Non-Blocking Read Data 1                                          */
    __I  uint32_t  RESERVED3[9];
    __IO uint32_t  STAT;                              /*!< EPI Status                                                            */
    __I  uint32_t  RESERVED4[2];
    __IO uint32_t  RFIFOCNT;                          /*!< EPI Read FIFO Count                                                   */
    __IO uint32_t  READFIFO0;                         /*!< EPI Read FIFO                                                         */
    __IO uint32_t  READFIFO1;                         /*!< EPI Read FIFO Alias 1                                                 */
    __IO uint32_t  READFIFO2;                         /*!< EPI Read FIFO Alias 2                                                 */
    __IO uint32_t  READFIFO3;                         /*!< EPI Read FIFO Alias 3                                                 */
    __IO uint32_t  READFIFO4;                         /*!< EPI Read FIFO Alias 4                                                 */
    __IO uint32_t  READFIFO5;                         /*!< EPI Read FIFO Alias 5                                                 */
    __IO uint32_t  READFIFO6;                         /*!< EPI Read FIFO Alias 6                                                 */
    __IO uint32_t  READFIFO7;                         /*!< EPI Read FIFO Alias 7                                                 */
    __I  uint32_t  RESERVED5[92];
    __IO uint32_t  FIFOLVL;                           /*!< EPI FIFO Level Selects                                                */
    __IO uint32_t  WFIFOCNT;                          /*!< EPI Write FIFO Count                                                  */
    __IO uint32_t  DMATXCNT;                          /*!< EPI DMA Transmit Count                                                */
    __I  uint32_t  RESERVED6;
    __IO uint32_t  IM;                                /*!< EPI Interrupt Mask                                                    */
    __IO uint32_t  RIS;                               /*!< EPI Raw Interrupt Status                                              */
    __IO uint32_t  MIS;                               /*!< EPI Masked Interrupt Status                                           */
    __IO uint32_t  EISC;                              /*!< EPI Error and Interrupt Status and Clear                              */
    __I  uint32_t  RESERVED7[58];

    union
    {
        __IO uint32_t  HB8CFG3;                         /*!< EPI Host-Bus 8 Configuration 3                                        */
        __IO uint32_t  HB16CFG3;                        /*!< EPI Host-Bus 16 Configuration 3                                       */
    };

    union
    {
        __IO uint32_t  HB8CFG4;                         /*!< EPI Host-Bus 8 Configuration 4                                        */
        __IO uint32_t  HB16CFG4;                        /*!< EPI Host-Bus 16 Configuration 4                                       */
    };

    union
    {
        __IO uint32_t  HB8TIME;                         /*!< EPI Host-Bus 8 Timing Extension                                       */
        __IO uint32_t  HB16TIME;                        /*!< EPI Host-Bus 16 Timing Extension                                      */
    };

    union
    {
        __IO uint32_t  HB8TIME2;                        /*!< EPI Host-Bus 8 Timing Extension                                       */
        __IO uint32_t  HB16TIME2;                       /*!< EPI Host-Bus 16 Timing Extension                                      */
    };

    union
    {
        __IO uint32_t  HB8TIME3;                        /*!< EPI Host-Bus 8 Timing Extension                                       */
        __IO uint32_t  HB16TIME3;                       /*!< EPI Host-Bus 16 Timing Extension                                      */
    };

    union
    {
        __IO uint32_t  HB8TIME4;                        /*!< EPI Host-Bus 8 Timing Extension                                       */
        __IO uint32_t  HB16TIME4;                       /*!< EPI Host-Bus 16 Timing Extension                                      */
    };
    __I  uint32_t  RESERVED8[16];
    __IO uint32_t  HBPSRAM;                           /*!< EPI Host-Bus PSRAM                                                    */
} EPI0_Type;


/* ================================================================================ */
/* ================                      EMAC0                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for EMAC0 peripheral (EMAC0)
  */

typedef struct                                      /*!< EMAC0 Structure                                                       */
{
    __IO uint32_t  CFG;                               /*!< Ethernet MAC Configuration                                            */
    __IO uint32_t  FRAMEFLTR;                         /*!< Ethernet MAC Frame Filter                                             */
    __IO uint32_t  HASHTBLH;                          /*!< Ethernet MAC Hash Table High                                          */
    __IO uint32_t  HASHTBLL;                          /*!< Ethernet MAC Hash Table Low                                           */
    __IO uint32_t  MIIADDR;                           /*!< Ethernet MAC MII Address                                              */
    __IO uint32_t  MIIDATA;                           /*!< Ethernet MAC MII Data Register                                        */
    __IO uint32_t  FLOWCTL;                           /*!< Ethernet MAC Flow Control                                             */
    __IO uint32_t  VLANTG;                            /*!< Ethernet MAC VLAN Tag                                                 */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  STATUS;                            /*!< Ethernet MAC Status                                                   */
    __IO uint32_t  RWUFF;                             /*!< Ethernet MAC Remote Wake-Up Frame Filter                              */
    __IO uint32_t  PMTCTLSTAT;                        /*!< Ethernet MAC PMT Control and Status Register                          */
    __IO uint32_t  LPICTLSTAT;                        /*!< Ethernet MAC Low Power Idle Control and Status Register               */
    __IO uint32_t  LPITIMERCTL;                       /*!< Ethernet MAC Low Power Idle Timer Control Register                    */
    __IO uint32_t  RIS;                               /*!< Ethernet MAC Raw Interrupt Status                                     */
    __IO uint32_t  IM;                                /*!< Ethernet MAC Interrupt Mask                                           */
    __IO uint32_t  ADDR0H;                            /*!< Ethernet MAC Address 0 High                                           */
    __IO uint32_t  ADDR0L;                            /*!< Ethernet MAC Address 0 Low Register                                   */
    __IO uint32_t  ADDR1H;                            /*!< Ethernet MAC Address 1 High                                           */
    __IO uint32_t  ADDR1L;                            /*!< Ethernet MAC Address 1 Low                                            */
    __IO uint32_t  ADDR2H;                            /*!< Ethernet MAC Address 2 High                                           */
    __IO uint32_t  ADDR2L;                            /*!< Ethernet MAC Address 2 Low                                            */
    __IO uint32_t  ADDR3H;                            /*!< Ethernet MAC Address 3 High                                           */
    __IO uint32_t  ADDR3L;                            /*!< Ethernet MAC Address 3 Low                                            */
    __I  uint32_t  RESERVED1[31];
    __IO uint32_t  WDOGTO;                            /*!< Ethernet MAC Watchdog Timeout                                         */
    __I  uint32_t  RESERVED2[8];
    __IO uint32_t  MMCCTRL;                           /*!< Ethernet MAC MMC Control                                              */
    __IO uint32_t  MMCRXRIS;                          /*!< Ethernet MAC MMC Receive Raw Interrupt Status                         */
    __IO uint32_t  MMCTXRIS;                          /*!< Ethernet MAC MMC Transmit Raw Interrupt Status                        */
    __IO uint32_t  MMCRXIM;                           /*!< Ethernet MAC MMC Receive Interrupt Mask                               */
    __IO uint32_t  MMCTXIM;                           /*!< Ethernet MAC MMC Transmit Interrupt Mask                              */
    __I  uint32_t  RESERVED3;
    __IO uint32_t  TXCNTGB;                           /*!< Ethernet MAC Transmit Frame Count for Good and Bad Frames             */
    __I  uint32_t  RESERVED4[12];
    __IO uint32_t  TXCNTSCOL;                         /*!< Ethernet MAC Transmit Frame Count for Frames Transmitted after
                                                         Single Collision                                                      */
    __IO uint32_t  TXCNTMCOL;                         /*!< Ethernet MAC Transmit Frame Count for Frames Transmitted after
                                                         Multiple Collisions                                                   */
    __I  uint32_t  RESERVED5[4];
    __IO uint32_t  TXOCTCNTG;                         /*!< Ethernet MAC Transmit Octet Count Good                                */
    __I  uint32_t  RESERVED6[6];
    __IO uint32_t  RXCNTGB;                           /*!< Ethernet MAC Receive Frame Count for Good and Bad Frames              */
    __I  uint32_t  RESERVED7[4];
    __IO uint32_t  RXCNTCRCERR;                       /*!< Ethernet MAC Receive Frame Count for CRC Error Frames                 */
    __IO uint32_t  RXCNTALGNERR;                      /*!< Ethernet MAC Receive Frame Count for Alignment Error Frames           */
    __I  uint32_t  RESERVED8[10];
    __IO uint32_t  RXCNTGUNI;                         /*!< Ethernet MAC Receive Frame Count for Good Unicast Frames              */
    __I  uint32_t  RESERVED9[239];
    __IO uint32_t  VLNINCREP;                         /*!< Ethernet MAC VLAN Tag Inclusion or Replacement                        */
    __IO uint32_t  VLANHASH;                          /*!< Ethernet MAC VLAN Hash Table                                          */
    __I  uint32_t  RESERVED10[93];
    __IO uint32_t  TIMSTCTRL;                         /*!< Ethernet MAC Timestamp Control                                        */
    __IO uint32_t  SUBSECINC;                         /*!< Ethernet MAC Sub-Second Increment                                     */
    __IO uint32_t  TIMSEC;                            /*!< Ethernet MAC System Time - Seconds                                    */
    __IO uint32_t  TIMNANO;                           /*!< Ethernet MAC System Time - Nanoseconds                                */
    __IO uint32_t  TIMSECU;                           /*!< Ethernet MAC System Time - Seconds Update                             */
    __IO uint32_t  TIMNANOU;                          /*!< Ethernet MAC System Time - Nanoseconds Update                         */
    __IO uint32_t  TIMADD;                            /*!< Ethernet MAC Timestamp Addend                                         */
    __IO uint32_t  TARGSEC;                           /*!< Ethernet MAC Target Time Seconds                                      */
    __IO uint32_t  TARGNANO;                          /*!< Ethernet MAC Target Time Nanoseconds                                  */
    __IO uint32_t  HWORDSEC;                          /*!< Ethernet MAC System Time-Higher Word Seconds                          */
    __IO uint32_t  TIMSTAT;                           /*!< Ethernet MAC Timestamp Status                                         */
    __IO uint32_t  PPSCTRL;                           /*!< Ethernet MAC PPS Control                                              */
    __I  uint32_t  RESERVED11[12];
    __IO uint32_t  PPS0INTVL;                         /*!< Ethernet MAC PPS0 Interval                                            */
    __IO uint32_t  PPS0WIDTH;                         /*!< Ethernet MAC PPS0 Width                                               */
    __I  uint32_t  RESERVED12[294];
    __IO uint32_t  DMABUSMOD;                         /*!< Ethernet MAC DMA Bus Mode                                             */
    __O  uint32_t  TXPOLLD;                           /*!< Ethernet MAC Transmit Poll Demand                                     */
    __O  uint32_t  RXPOLLD;                           /*!< Ethernet MAC Receive Poll Demand                                      */
    __IO uint32_t  RXDLADDR;                          /*!< Ethernet MAC Receive Descriptor List Address                          */
    __IO uint32_t  TXDLADDR;                          /*!< Ethernet MAC Transmit Descriptor List Address                         */
    __IO uint32_t  DMARIS;                            /*!< Ethernet MAC DMA Interrupt Status                                     */
    __IO uint32_t  DMAOPMODE;                         /*!< Ethernet MAC DMA Operation Mode                                       */
    __IO uint32_t  DMAIM;                             /*!< Ethernet MAC DMA Interrupt Mask Register                              */
    __IO uint32_t  MFBOC;                             /*!< Ethernet MAC Missed Frame and Buffer Overflow Counter                 */
    __IO uint32_t  RXINTWDT;                          /*!< Ethernet MAC Receive Interrupt Watchdog Timer                         */
    __I  uint32_t  RESERVED13[8];
    __IO uint32_t  HOSTXDESC;                         /*!< Ethernet MAC Current Host Transmit Descriptor                         */
    __IO uint32_t  HOSRXDESC;                         /*!< Ethernet MAC Current Host Receive Descriptor                          */
    __IO uint32_t  HOSTXBA;                           /*!< Ethernet MAC Current Host Transmit Buffer Address                     */
    __IO uint32_t  HOSRXBA;                           /*!< Ethernet MAC Current Host Receive Buffer Address                      */
    __I  uint32_t  RESERVED14[218];
    __IO uint32_t  PP;                                /*!< Ethernet MAC Peripheral Property Register                             */
    __IO uint32_t  PC;                                /*!< Ethernet MAC Peripheral Configuration Register                        */
    __IO uint32_t  CC;                                /*!< Ethernet MAC Clock Configuration Register                             */
    __IO uint32_t  EPHYRIS;                           /*!< Ethernet PHY Raw Interrupt Status                                     */
    __IO uint32_t  EPHYIM;                            /*!< Ethernet PHY Interrupt Mask                                           */
    __IO uint32_t  EPHYMISC;                          /*!< Ethernet PHY Masked Interrupt Status and Clear                        */
} EMAC0_Type;


/* ================================================================================ */
/* ================                     SYSEXC                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for SYSEXC peripheral (SYSEXC)
  */

typedef struct                                      /*!< SYSEXC Structure                                                      */
{
    __IO uint32_t  RIS;                               /*!< System Exception Raw Interrupt Status                                 */
    __IO uint32_t  IM;                                /*!< System Exception Interrupt Mask                                       */
    __IO uint32_t  MIS;                               /*!< System Exception Masked Interrupt Status                              */
    __O  uint32_t  IC;                                /*!< System Exception Interrupt Clear                                      */
} SYSEXC_Type;


/* ================================================================================ */
/* ================                       HIB                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for HIB peripheral (HIB)
  */

typedef struct                                      /*!< HIB Structure                                                         */
{
    __IO uint32_t  RTCC;                              /*!< Hibernation RTC Counter                                               */
    __IO uint32_t  RTCM0;                             /*!< Hibernation RTC Match 0                                               */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  RTCLD;                             /*!< Hibernation RTC Load                                                  */
    __IO uint32_t  CTL;                               /*!< Hibernation Control                                                   */
    __IO uint32_t  IM;                                /*!< Hibernation Interrupt Mask                                            */
    __IO uint32_t  RIS;                               /*!< Hibernation Raw Interrupt Status                                      */
    __IO uint32_t  MIS;                               /*!< Hibernation Masked Interrupt Status                                   */
    __IO uint32_t  IC;                                /*!< Hibernation Interrupt Clear                                           */
    __IO uint32_t  RTCT;                              /*!< Hibernation RTC Trim                                                  */
    __IO uint32_t  RTCSS;                             /*!< Hibernation RTC Sub Seconds                                           */
    __IO uint32_t  IO;                                /*!< Hibernation IO Configuration                                          */
    __IO uint32_t  DATA;                              /*!< Hibernation Data                                                      */
    __I  uint32_t  RESERVED1[179];
    __IO uint32_t  CALCTL;                            /*!< Hibernation Calendar Control                                          */
    __I  uint32_t  RESERVED2[3];
    __IO uint32_t  CAL0;                              /*!< Hibernation Calendar 0                                                */
    __IO uint32_t  CAL1;                              /*!< Hibernation Calendar 1                                                */
    __I  uint32_t  RESERVED3[2];
    __O  uint32_t  CALLD0;                            /*!< Hibernation Calendar Load 0                                           */
    __O  uint32_t  CALLD1;                            /*!< Hibernation Calendar Load                                             */
    __I  uint32_t  RESERVED4[2];
    __IO uint32_t  CALM0;                             /*!< Hibernation Calendar Match 0                                          */
    __IO uint32_t  CALM1;                             /*!< Hibernation Calendar Match 1                                          */
    __I  uint32_t  RESERVED5[10];
    __IO uint32_t  LOCK;                              /*!< Hibernation Lock                                                      */
    __I  uint32_t  RESERVED6[39];
    __IO uint32_t  TPCTL;                             /*!< HIB Tamper Control                                                    */
    __IO uint32_t  TPSTAT;                            /*!< HIB Tamper Status                                                     */
    __I  uint32_t  RESERVED7[2];
    __IO uint32_t  TPIO;                              /*!< HIB Tamper I/O Control                                                */
    __I  uint32_t  RESERVED8[51];
    __IO uint32_t  TPLOG0;                            /*!< HIB Tamper Log 0                                                      */
    __IO uint32_t  TPLOG1;                            /*!< HIB Tamper Log 1                                                      */
    __IO uint32_t  TPLOG2;                            /*!< HIB Tamper Log 2                                                      */
    __IO uint32_t  TPLOG3;                            /*!< HIB Tamper Log 3                                                      */
    __IO uint32_t  TPLOG4;                            /*!< HIB Tamper Log 4                                                      */
    __IO uint32_t  TPLOG5;                            /*!< HIB Tamper Log 5                                                      */
    __IO uint32_t  TPLOG6;                            /*!< HIB Tamper Log 6                                                      */
    __IO uint32_t  TPLOG7;                            /*!< HIB Tamper Log 7                                                      */
    __I  uint32_t  RESERVED9[688];
    __IO uint32_t  PP;                                /*!< Hibernation Peripheral Properties                                     */
    __I  uint32_t  RESERVED10;
    __IO uint32_t  CC;                                /*!< Hibernation Clock Control                                             */
} HIB_Type;


/* ================================================================================ */
/* ================                   FLASH_CTRL                   ================ */
/* ================================================================================ */


/**
  * @brief Register map for FLASH_CTRL peripheral (FLASH_CTRL)
  */

typedef struct                                      /*!< FLASH_CTRL Structure                                                  */
{
    __IO uint32_t  FMA;                               /*!< Flash Memory Address                                                  */
    __IO uint32_t  FMD;                               /*!< Flash Memory Data                                                     */
    __IO uint32_t  FMC;                               /*!< Flash Memory Control                                                  */
    __IO uint32_t  FCRIS;                             /*!< Flash Controller Raw Interrupt Status                                 */
    __IO uint32_t  FCIM;                              /*!< Flash Controller Interrupt Mask                                       */
    __IO uint32_t  FCMISC;                            /*!< Flash Controller Masked Interrupt Status and Clear                    */
    __I  uint32_t  RESERVED0[2];
    __IO uint32_t  FMC2;                              /*!< Flash Memory Control 2                                                */
    __I  uint32_t  RESERVED1[3];
    __IO uint32_t  FWBVAL;                            /*!< Flash Write Buffer Valid                                              */
    __I  uint32_t  RESERVED2[2];
    __IO uint32_t  FLPEKEY;                           /*!< Flash Program/Erase Key                                               */
    __I  uint32_t  RESERVED3[48];
    __IO uint32_t  FWBN[32];                          /*!< Flash Write Buffer n                                                  */
    __I  uint32_t  RESERVED4[912];

    union
    {
        __IO uint32_t  PP;                              /*!< Flash Peripheral Properties                                           */
        __IO uint32_t  FSIZE;                           /*!< Flash Size                                                            */
    };
    __IO uint32_t  SSIZE;                             /*!< SRAM Size                                                             */
    __IO uint32_t  CONF;                              /*!< Flash Configuration Register                                          */
    __IO uint32_t  ROMSWMAP;                          /*!< ROM Software Map                                                      */
    __IO uint32_t  DMASZ;                             /*!< Flash DMA Address Size                                                */
    __IO uint32_t  DMAST;                             /*!< Flash DMA Starting Address                                            */
    __I  uint32_t  RESERVED5[63];
    __IO uint32_t  RVP;                               /*!< Reset Vector Pointer                                                  */
    __I  uint32_t  RESERVED7[62];
    __IO uint32_t  BOOTCFG;                           /*!< Boot Configuration                                                    */
    __I  uint32_t  RESERVED8[3];
    __IO uint32_t  USERREG0;                          /*!< User Register 0                                                       */
    __IO uint32_t  USERREG1;                          /*!< User Register 1                                                       */
    __IO uint32_t  USERREG2;                          /*!< User Register 2                                                       */
    __IO uint32_t  USERREG3;                          /*!< User Register 3                                                       */
    __I  uint32_t  RESERVED9[4];
    __IO uint32_t  FMPRE0;                            /*!< Flash Memory Protection Read Enable 0                                 */
    __IO uint32_t  FMPRE1;                            /*!< Flash Memory Protection Read Enable 1                                 */
    __IO uint32_t  FMPRE2;                            /*!< Flash Memory Protection Read Enable 2                                 */
    __IO uint32_t  FMPRE3;                            /*!< Flash Memory Protection Read Enable 3                                 */
    __IO uint32_t  FMPRE4;                            /*!< Flash Memory Protection Read Enable 4                                 */
    __IO uint32_t  FMPRE5;                            /*!< Flash Memory Protection Read Enable 5                                 */
    __IO uint32_t  FMPRE6;                            /*!< Flash Memory Protection Read Enable 6                                 */
    __IO uint32_t  FMPRE7;                            /*!< Flash Memory Protection Read Enable 7                                 */
    __IO uint32_t  FMPRE8;                            /*!< Flash Memory Protection Read Enable 8                                 */
    __IO uint32_t  FMPRE9;                            /*!< Flash Memory Protection Read Enable 9                                 */
    __IO uint32_t  FMPRE10;                           /*!< Flash Memory Protection Read Enable 10                                */
    __IO uint32_t  FMPRE11;                           /*!< Flash Memory Protection Read Enable 11                                */
    __IO uint32_t  FMPRE12;                           /*!< Flash Memory Protection Read Enable 12                                */
    __IO uint32_t  FMPRE13;                           /*!< Flash Memory Protection Read Enable 13                                */
    __IO uint32_t  FMPRE14;                           /*!< Flash Memory Protection Read Enable 14                                */
    __IO uint32_t  FMPRE15;                           /*!< Flash Memory Protection Read Enable 15                                */
    __I  uint32_t  RESERVED10[112];
    __IO uint32_t  FMPPE0;                            /*!< Flash Memory Protection Program Enable 0                              */
    __IO uint32_t  FMPPE1;                            /*!< Flash Memory Protection Program Enable 1                              */
    __IO uint32_t  FMPPE2;                            /*!< Flash Memory Protection Program Enable 2                              */
    __IO uint32_t  FMPPE3;                            /*!< Flash Memory Protection Program Enable 3                              */
    __IO uint32_t  FMPPE4;                            /*!< Flash Memory Protection Program Enable 4                              */
    __IO uint32_t  FMPPE5;                            /*!< Flash Memory Protection Program Enable 5                              */
    __IO uint32_t  FMPPE6;                            /*!< Flash Memory Protection Program Enable 6                              */
    __IO uint32_t  FMPPE7;                            /*!< Flash Memory Protection Program Enable 7                              */
    __IO uint32_t  FMPPE8;                            /*!< Flash Memory Protection Program Enable 8                              */
    __IO uint32_t  FMPPE9;                            /*!< Flash Memory Protection Program Enable 9                              */
    __IO uint32_t  FMPPE10;                           /*!< Flash Memory Protection Program Enable 10                             */
    __IO uint32_t  FMPPE11;                           /*!< Flash Memory Protection Program Enable 11                             */
    __IO uint32_t  FMPPE12;                           /*!< Flash Memory Protection Program Enable 12                             */
    __IO uint32_t  FMPPE13;                           /*!< Flash Memory Protection Program Enable 13                             */
    __IO uint32_t  FMPPE14;                           /*!< Flash Memory Protection Program Enable 14                             */
    __IO uint32_t  FMPPE15;                           /*!< Flash Memory Protection Program Enable 15                             */
} FLASH_CTRL_Type;


/* ================================================================================ */
/* ================                     SYSCTL                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for SYSCTL peripheral (SYSCTL)
  */

typedef struct                                      /*!< SYSCTL Structure                                                      */
{
    __IO uint32_t  DID0;                              /*!< Device Identification 0                                               */
    __IO uint32_t  DID1;                              /*!< Device Identification 1                                               */
    __I  uint32_t  RESERVED0[12];
    __IO uint32_t  PTBOCTL;                           /*!< Power-Temp Brown Out Control                                          */
    __I  uint32_t  RESERVED1[5];
    __IO uint32_t  RIS;                               /*!< Raw Interrupt Status                                                  */
    __IO uint32_t  IMC;                               /*!< Interrupt Mask Control                                                */
    __IO uint32_t  MISC;                              /*!< Masked Interrupt Status and Clear                                     */
    __IO uint32_t  RESC;                              /*!< Reset Cause                                                           */
    __IO uint32_t  PWRTC;                             /*!< Power-Temperature Cause                                               */
    __IO uint32_t  NMIC;                              /*!< NMI Cause Register                                                    */
    __I  uint32_t  RESERVED2[5];
    __IO uint32_t  MOSCCTL;                           /*!< Main Oscillator Control                                               */
    __I  uint32_t  RESERVED3[12];
    __IO uint32_t  RSCLKCFG;                          /*!< Run and Sleep Mode Configuration Register                             */
    __I  uint32_t  RESERVED4[3];
    __IO uint32_t  MEMTIM0;                           /*!< Memory Timing Parameter Register 0 for Main Flash and EEPROM          */
    __I  uint32_t  RESERVED5[29];
    __IO uint32_t  ALTCLKCFG;                         /*!< Alternate Clock Configuration                                         */
    __I  uint32_t  RESERVED6[2];
    __IO uint32_t  DSCLKCFG;                          /*!< Deep Sleep Clock Configuration Register                               */
    __IO uint32_t  DIVSCLK;                           /*!< Divisor and Source Clock Configuration                                */
    __IO uint32_t  SYSPROP;                           /*!< System Properties                                                     */
    __IO uint32_t  PIOSCCAL;                          /*!< Precision Internal Oscillator Calibration                             */
    __IO uint32_t  PIOSCSTAT;                         /*!< Precision Internal Oscillator Statistics                              */
    __I  uint32_t  RESERVED7[2];
    __IO uint32_t  PLLFREQ0;                          /*!< PLL Frequency 0                                                       */
    __IO uint32_t  PLLFREQ1;                          /*!< PLL Frequency 1                                                       */
    __IO uint32_t  PLLSTAT;                           /*!< PLL Status                                                            */
    __I  uint32_t  RESERVED8[7];
    __IO uint32_t  SLPPWRCFG;                         /*!< Sleep Power Configuration                                             */
    __IO uint32_t  DSLPPWRCFG;                        /*!< Deep-Sleep Power Configuration                                        */
    __I  uint32_t  RESERVED9[4];
    __IO uint32_t  NVMSTAT;                           /*!< Non-Volatile Memory Information                                       */
    __I  uint32_t  RESERVED10[4];
    __IO uint32_t  LDOSPCTL;                          /*!< LDO Sleep Power Control                                               */
    __I  uint32_t  RESERVED11;
    __IO uint32_t  LDODPCTL;                          /*!< LDO Deep-Sleep Power Control                                          */
    __I  uint32_t  RESERVED12[6];
    __IO uint32_t  RESBEHAVCTL;                       /*!< Reset Behavior Control Register                                       */
    __I  uint32_t  RESERVED13[6];
    __IO uint32_t  HSSR;                              /*!< Hardware System Service Request                                       */
    __I  uint32_t  RESERVED14[34];
    __IO uint32_t  USBPDS;                            /*!< USB Power Domain Status                                               */
    __IO uint32_t  USBMPC;                            /*!< USB Memory Power Control                                              */
    __IO uint32_t  EMACPDS;                           /*!< Ethernet MAC Power Domain Status                                      */
    __IO uint32_t  EMACMPC;                           /*!< Ethernet MAC Memory Power Control                                     */
    __I  uint32_t  RESERVED15[28];
    __IO uint32_t  PPWD;                              /*!< Watchdog Timer Peripheral Present                                     */
    __IO uint32_t  PPTIMER;                           /*!< 16/32-Bit General-Purpose Timer Peripheral Present                    */
    __IO uint32_t  PPGPIO;                            /*!< General-Purpose Input/Output Peripheral Present                       */
    __IO uint32_t  PPDMA;                             /*!< Micro Direct Memory Access Peripheral Present                         */
    __IO uint32_t  PPEPI;                             /*!< EPI Peripheral Present                                                */
    __IO uint32_t  PPHIB;                             /*!< Hibernation Peripheral Present                                        */
    __IO uint32_t  PPUART;                            /*!< Universal Asynchronous Receiver/Transmitter Peripheral Present        */
    __IO uint32_t  PPSSI;                             /*!< Synchronous Serial Interface Peripheral Present                       */
    __IO uint32_t  PPI2C;                             /*!< Inter-Integrated Circuit Peripheral Present                           */
    __I  uint32_t  RESERVED16;
    __IO uint32_t  PPUSB;                             /*!< Universal Serial Bus Peripheral Present                               */
    __I  uint32_t  RESERVED17;
    __IO uint32_t  PPEPHY;                            /*!< Ethernet PHY Peripheral Present                                       */
    __IO uint32_t  PPCAN;                             /*!< Controller Area Network Peripheral Present                            */
    __IO uint32_t  PPADC;                             /*!< Analog-to-Digital Converter Peripheral Present                        */
    __IO uint32_t  PPACMP;                            /*!< Analog Comparator Peripheral Present                                  */
    __IO uint32_t  PPPWM;                             /*!< Pulse Width Modulator Peripheral Present                              */
    __IO uint32_t  PPQEI;                             /*!< Quadrature Encoder Interface Peripheral Present                       */
    __I  uint32_t  RESERVED18[4];
    __IO uint32_t  PPEEPROM;                          /*!< EEPROM Peripheral Present                                             */
    __I  uint32_t  RESERVED19[6];
    __IO uint32_t  PPCCM;                             /*!< CRC and Cryptographic Modules Peripheral Present                      */
    __I  uint32_t  RESERVED20[6];
    __IO uint32_t  PPLCD;                             /*!< LCD Peripheral Present                                                */
    __I  uint32_t  RESERVED21;
    __IO uint32_t  PPOWIRE;                           /*!< 1-Wire Peripheral Present                                             */
    __IO uint32_t  PPEMAC;                            /*!< Ethernet MAC Peripheral Present                                       */
    __I  uint32_t  RESERVED22[88];
    __IO uint32_t  SRWD;                              /*!< Watchdog Timer Software Reset                                         */
    __IO uint32_t  SRTIMER;                           /*!< 16/32-Bit General-Purpose Timer Software Reset                        */
    __IO uint32_t  SRGPIO;                            /*!< General-Purpose Input/Output Software Reset                           */
    __IO uint32_t  SRDMA;                             /*!< Micro Direct Memory Access Software Reset                             */
    __IO uint32_t  SREPI;                             /*!< EPI Software Reset                                                    */
    __IO uint32_t  SRHIB;                             /*!< Hibernation Software Reset                                            */
    __IO uint32_t  SRUART;                            /*!< Universal Asynchronous Receiver/Transmitter Software Reset            */
    __IO uint32_t  SRSSI;                             /*!< Synchronous Serial Interface Software Reset                           */
    __IO uint32_t  SRI2C;                             /*!< Inter-Integrated Circuit Software Reset                               */
    __I  uint32_t  RESERVED23;
    __IO uint32_t  SRUSB;                             /*!< Universal Serial Bus Software Reset                                   */
    __I  uint32_t  RESERVED24;
    __IO uint32_t  SREPHY;                            /*!< Ethernet PHY Software Reset                                           */
    __IO uint32_t  SRCAN;                             /*!< Controller Area Network Software Reset                                */
    __IO uint32_t  SRADC;                             /*!< Analog-to-Digital Converter Software Reset                            */
    __IO uint32_t  SRACMP;                            /*!< Analog Comparator Software Reset                                      */
    __IO uint32_t  SRPWM;                             /*!< Pulse Width Modulator Software Reset                                  */
    __IO uint32_t  SRQEI;                             /*!< Quadrature Encoder Interface Software Reset                           */
    __I  uint32_t  RESERVED25[4];
    __IO uint32_t  SREEPROM;                          /*!< EEPROM Software Reset                                                 */
    __I  uint32_t  RESERVED26[6];
    __IO uint32_t  SRCCM;                             /*!< CRC and Cryptographic Modules Software Reset                          */
    __I  uint32_t  RESERVED27[9];
    __IO uint32_t  SREMAC;                            /*!< Ethernet MAC Software Reset                                           */
    __I  uint32_t  RESERVED28[24];
    __IO uint32_t  RCGCWD;                            /*!< Watchdog Timer Run Mode Clock Gating Control                          */
    __IO uint32_t  RCGCTIMER;                         /*!< 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control         */
    __IO uint32_t  RCGCGPIO;                          /*!< General-Purpose Input/Output Run Mode Clock Gating Control            */
    __IO uint32_t  RCGCDMA;                           /*!< Micro Direct Memory Access Run Mode Clock Gating Control              */
    __IO uint32_t  RCGCEPI;                           /*!< EPI Run Mode Clock Gating Control                                     */
    __IO uint32_t  RCGCHIB;                           /*!< Hibernation Run Mode Clock Gating Control                             */
    __IO uint32_t  RCGCUART;                          /*!< Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating
                                                         Control                                                               */
    __IO uint32_t  RCGCSSI;                           /*!< Synchronous Serial Interface Run Mode Clock Gating Control            */
    __IO uint32_t  RCGCI2C;                           /*!< Inter-Integrated Circuit Run Mode Clock Gating Control                */
    __I  uint32_t  RESERVED29;
    __IO uint32_t  RCGCUSB;                           /*!< Universal Serial Bus Run Mode Clock Gating Control                    */
    __I  uint32_t  RESERVED30;
    __IO uint32_t  RCGCEPHY;                          /*!< Ethernet PHY Run Mode Clock Gating Control                            */
    __IO uint32_t  RCGCCAN;                           /*!< Controller Area Network Run Mode Clock Gating Control                 */
    __IO uint32_t  RCGCADC;                           /*!< Analog-to-Digital Converter Run Mode Clock Gating Control             */
    __IO uint32_t  RCGCACMP;                          /*!< Analog Comparator Run Mode Clock Gating Control                       */
    __IO uint32_t  RCGCPWM;                           /*!< Pulse Width Modulator Run Mode Clock Gating Control                   */
    __IO uint32_t  RCGCQEI;                           /*!< Quadrature Encoder Interface Run Mode Clock Gating Control            */
    __I  uint32_t  RESERVED31[4];
    __IO uint32_t  RCGCEEPROM;                        /*!< EEPROM Run Mode Clock Gating Control                                  */
    __I  uint32_t  RESERVED32[6];
    __IO uint32_t  RCGCCCM;                           /*!< CRC and Cryptographic Modules Run Mode Clock Gating Control           */
    __I  uint32_t  RESERVED33[9];
    __IO uint32_t  RCGCEMAC;                          /*!< Ethernet MAC Run Mode Clock Gating Control                            */
    __I  uint32_t  RESERVED34[24];
    __IO uint32_t  SCGCWD;                            /*!< Watchdog Timer Sleep Mode Clock Gating Control                        */
    __IO uint32_t  SCGCTIMER;                         /*!< 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control       */
    __IO uint32_t  SCGCGPIO;                          /*!< General-Purpose Input/Output Sleep Mode Clock Gating Control          */
    __IO uint32_t  SCGCDMA;                           /*!< Micro Direct Memory Access Sleep Mode Clock Gating Control            */
    __IO uint32_t  SCGCEPI;                           /*!< EPI Sleep Mode Clock Gating Control                                   */
    __IO uint32_t  SCGCHIB;                           /*!< Hibernation Sleep Mode Clock Gating Control                           */
    __IO uint32_t  SCGCUART;                          /*!< Universal Asynchronous Receiver/Transmitter Sleep Mode Clock
                                                         Gating Control                                                        */
    __IO uint32_t  SCGCSSI;                           /*!< Synchronous Serial Interface Sleep Mode Clock Gating Control          */
    __IO uint32_t  SCGCI2C;                           /*!< Inter-Integrated Circuit Sleep Mode Clock Gating Control              */
    __I  uint32_t  RESERVED35;
    __IO uint32_t  SCGCUSB;                           /*!< Universal Serial Bus Sleep Mode Clock Gating Control                  */
    __I  uint32_t  RESERVED36;
    __IO uint32_t  SCGCEPHY;                          /*!< Ethernet PHY Sleep Mode Clock Gating Control                          */
    __IO uint32_t  SCGCCAN;                           /*!< Controller Area Network Sleep Mode Clock Gating Control               */
    __IO uint32_t  SCGCADC;                           /*!< Analog-to-Digital Converter Sleep Mode Clock Gating Control           */
    __IO uint32_t  SCGCACMP;                          /*!< Analog Comparator Sleep Mode Clock Gating Control                     */
    __IO uint32_t  SCGCPWM;                           /*!< Pulse Width Modulator Sleep Mode Clock Gating Control                 */
    __IO uint32_t  SCGCQEI;                           /*!< Quadrature Encoder Interface Sleep Mode Clock Gating Control          */
    __I  uint32_t  RESERVED37[4];
    __IO uint32_t  SCGCEEPROM;                        /*!< EEPROM Sleep Mode Clock Gating Control                                */
    __I  uint32_t  RESERVED38[6];
    __IO uint32_t  SCGCCCM;                           /*!< CRC and Cryptographic Modules Sleep Mode Clock Gating Control         */
    __I  uint32_t  RESERVED39[9];
    __IO uint32_t  SCGCEMAC;                          /*!< Ethernet MAC Sleep Mode Clock Gating Control                          */
    __I  uint32_t  RESERVED40[24];
    __IO uint32_t  DCGCWD;                            /*!< Watchdog Timer Deep-Sleep Mode Clock Gating Control                   */
    __IO uint32_t  DCGCTIMER;                         /*!< 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating
                                                         Control                                                               */
    __IO uint32_t  DCGCGPIO;                          /*!< General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control     */
    __IO uint32_t  DCGCDMA;                           /*!< Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control       */
    __IO uint32_t  DCGCEPI;                           /*!< EPI Deep-Sleep Mode Clock Gating Control                              */
    __IO uint32_t  DCGCHIB;                           /*!< Hibernation Deep-Sleep Mode Clock Gating Control                      */
    __IO uint32_t  DCGCUART;                          /*!< Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode
                                                         Clock Gating Control                                                  */
    __IO uint32_t  DCGCSSI;                           /*!< Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control     */
    __IO uint32_t  DCGCI2C;                           /*!< Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control         */
    __I  uint32_t  RESERVED41;
    __IO uint32_t  DCGCUSB;                           /*!< Universal Serial Bus Deep-Sleep Mode Clock Gating Control             */
    __I  uint32_t  RESERVED42;
    __IO uint32_t  DCGCEPHY;                          /*!< Ethernet PHY Deep-Sleep Mode Clock Gating Control                     */
    __IO uint32_t  DCGCCAN;                           /*!< Controller Area Network Deep-Sleep Mode Clock Gating Control          */
    __IO uint32_t  DCGCADC;                           /*!< Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control      */
    __IO uint32_t  DCGCACMP;                          /*!< Analog Comparator Deep-Sleep Mode Clock Gating Control                */
    __IO uint32_t  DCGCPWM;                           /*!< Pulse Width Modulator Deep-Sleep Mode Clock Gating Control            */
    __IO uint32_t  DCGCQEI;                           /*!< Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control     */
    __I  uint32_t  RESERVED43[4];
    __IO uint32_t  DCGCEEPROM;                        /*!< EEPROM Deep-Sleep Mode Clock Gating Control                           */
    __I  uint32_t  RESERVED44[6];
    __IO uint32_t  DCGCCCM;                           /*!< CRC and Cryptographic Modules Deep-Sleep Mode Clock Gating Control    */
    __I  uint32_t  RESERVED45[9];
    __IO uint32_t  DCGCEMAC;                          /*!< Ethernet MAC Deep-Sleep Mode Clock Gating Control                     */
    __I  uint32_t  RESERVED46[24];
    __IO uint32_t  PCWD;                              /*!< Watchdog Timer Power Control                                          */
    __IO uint32_t  PCTIMER;                           /*!< 16/32-Bit General-Purpose Timer Power Control                         */
    __IO uint32_t  PCGPIO;                            /*!< General-Purpose Input/Output Power Control                            */
    __IO uint32_t  PCDMA;                             /*!< Micro Direct Memory Access Power Control                              */
    __IO uint32_t  PCEPI;                             /*!< External Peripheral Interface Power Control                           */
    __IO uint32_t  PCHIB;                             /*!< Hibernation Power Control                                             */
    __IO uint32_t  PCUART;                            /*!< Universal Asynchronous Receiver/Transmitter Power Control             */
    __IO uint32_t  PCSSI;                             /*!< Synchronous Serial Interface Power Control                            */
    __IO uint32_t  PCI2C;                             /*!< Inter-Integrated Circuit Power Control                                */
    __I  uint32_t  RESERVED47;
    __IO uint32_t  PCUSB;                             /*!< Universal Serial Bus Power Control                                    */
    __I  uint32_t  RESERVED48;
    __IO uint32_t  PCEPHY;                            /*!< Ethernet PHY Power Control                                            */
    __IO uint32_t  PCCAN;                             /*!< Controller Area Network Power Control                                 */
    __IO uint32_t  PCADC;                             /*!< Analog-to-Digital Converter Power Control                             */
    __IO uint32_t  PCACMP;                            /*!< Analog Comparator Power Control                                       */
    __IO uint32_t  PCPWM;                             /*!< Pulse Width Modulator Power Control                                   */
    __IO uint32_t  PCQEI;                             /*!< Quadrature Encoder Interface Power Control                            */
    __I  uint32_t  RESERVED49[4];
    __IO uint32_t  PCEEPROM;                          /*!< EEPROM Power Control                                                  */
    __I  uint32_t  RESERVED50[6];
    __IO uint32_t  PCCCM;                             /*!< CRC and Cryptographic Modules Power Control                           */
    __I  uint32_t  RESERVED51[9];
    __IO uint32_t  PCEMAC;                            /*!< Ethernet MAC Power Control                                            */
    __I  uint32_t  RESERVED52[24];
    __IO uint32_t  PRWD;                              /*!< Watchdog Timer Peripheral Ready                                       */
    __IO uint32_t  PRTIMER;                           /*!< 16/32-Bit General-Purpose Timer Peripheral Ready                      */
    __IO uint32_t  PRGPIO;                            /*!< General-Purpose Input/Output Peripheral Ready                         */
    __IO uint32_t  PRDMA;                             /*!< Micro Direct Memory Access Peripheral Ready                           */
    __IO uint32_t  PREPI;                             /*!< EPI Peripheral Ready                                                  */
    __IO uint32_t  PRHIB;                             /*!< Hibernation Peripheral Ready                                          */
    __IO uint32_t  PRUART;                            /*!< Universal Asynchronous Receiver/Transmitter Peripheral Ready          */
    __IO uint32_t  PRSSI;                             /*!< Synchronous Serial Interface Peripheral Ready                         */
    __IO uint32_t  PRI2C;                             /*!< Inter-Integrated Circuit Peripheral Ready                             */
    __I  uint32_t  RESERVED53;
    __IO uint32_t  PRUSB;                             /*!< Universal Serial Bus Peripheral Ready                                 */
    __I  uint32_t  RESERVED54;
    __IO uint32_t  PREPHY;                            /*!< Ethernet PHY Peripheral Ready                                         */
    __IO uint32_t  PRCAN;                             /*!< Controller Area Network Peripheral Ready                              */
    __IO uint32_t  PRADC;                             /*!< Analog-to-Digital Converter Peripheral Ready                          */
    __IO uint32_t  PRACMP;                            /*!< Analog Comparator Peripheral Ready                                    */
    __IO uint32_t  PRPWM;                             /*!< Pulse Width Modulator Peripheral Ready                                */
    __IO uint32_t  PRQEI;                             /*!< Quadrature Encoder Interface Peripheral Ready                         */
    __I  uint32_t  RESERVED55[4];
    __IO uint32_t  PREEPROM;                          /*!< EEPROM Peripheral Ready                                               */
    __I  uint32_t  RESERVED56[6];
    __IO uint32_t  PRCCM;                             /*!< CRC and Cryptographic Modules Peripheral Ready                        */
    __I  uint32_t  RESERVED57[9];
    __IO uint32_t  PREMAC;                            /*!< Ethernet MAC Peripheral Ready                                         */
    __I  uint32_t  RESERVED58[288];
    __IO uint32_t  UNIQUEID0;                         /*!< Unique ID 0                                                           */
    __IO uint32_t  UNIQUEID1;                         /*!< Unique ID 1                                                           */
    __IO uint32_t  UNIQUEID2;                         /*!< Unique ID 2                                                           */
    __IO uint32_t  UNIQUEID3;                         /*!< Unique ID 3                                                           */
} SYSCTL_Type;

/* ================================================================================ */
/* ================                      UDMA                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for UDMA peripheral (UDMA)
  */

typedef struct                                      /*!< UDMA Structure                                                        */
{
    __IO uint32_t  STAT;                              /*!< DMA Status                                                            */
    __O  uint32_t  CFG;                               /*!< DMA Configuration                                                     */
    __IO uint32_t  CTLBASE;                           /*!< DMA Channel Control Base Pointer                                      */
    __IO uint32_t  ALTBASE;                           /*!< DMA Alternate Channel Control Base Pointer                            */
    __IO uint32_t  WAITSTAT;                          /*!< DMA Channel Wait-on-Request Status                                    */
    __O  uint32_t  SWREQ;                             /*!< DMA Channel Software Request                                          */
    __IO uint32_t  USEBURSTSET;                       /*!< DMA Channel Useburst Set                                              */
    __O  uint32_t  USEBURSTCLR;                       /*!< DMA Channel Useburst Clear                                            */
    __IO uint32_t  REQMASKSET;                        /*!< DMA Channel Request Mask Set                                          */
    __O  uint32_t  REQMASKCLR;                        /*!< DMA Channel Request Mask Clear                                        */
    __IO uint32_t  ENASET;                            /*!< DMA Channel Enable Set                                                */
    __O  uint32_t  ENACLR;                            /*!< DMA Channel Enable Clear                                              */
    __IO uint32_t  ALTSET;                            /*!< DMA Channel Primary Alternate Set                                     */
    __O  uint32_t  ALTCLR;                            /*!< DMA Channel Primary Alternate Clear                                   */
    __IO uint32_t  PRIOSET;                           /*!< DMA Channel Priority Set                                              */
    __O  uint32_t  PRIOCLR;                           /*!< DMA Channel Priority Clear                                            */
    __I  uint32_t  RESERVED0[3];
    __IO uint32_t  ERRCLR;                            /*!< DMA Bus Error Clear                                                   */
    __I  uint32_t  RESERVED1[304];
    __IO uint32_t  CHMAP0;                            /*!< DMA Channel Map Select 0                                              */
    __IO uint32_t  CHMAP1;                            /*!< DMA Channel Map Select 1                                              */
    __IO uint32_t  CHMAP2;                            /*!< DMA Channel Map Select 2                                              */
    __IO uint32_t  CHMAP3;                            /*!< DMA Channel Map Select 3                                              */
} UDMA_Type;


/* ================================================================================ */
/* ================                      CCM0                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for CCM0 peripheral (CCM0)
  */

typedef struct                                      /*!< CCM0 Structure                                                        */
{
    __I  uint32_t  RESERVED0[129];
    __IO uint32_t  CGREQ;                             /*!< Cryptographic Modules Clock Gating Request                            */
} CCM0_Type;


/* ================================================================================ */
/* ================                      CRC                       ================ */
/* ================================================================================ */


/**
  * @brief Register map for CRC peripheral (CRC)
  */

typedef struct                                      /*!< CRC Structure                                                         */
{
    __IO uint32_t  CTRL;                              /*!< CRC Control                                                           */
    __I  uint32_t  RESERVED2[3];
    __IO uint32_t  SEED;                              /*!< CRC SEED/Context                                                      */
    __IO uint32_t  DIN;                               /*!< CRC Data Input                                                        */
    __IO uint32_t  RSLTPP;                            /*!< CRC Post Processing Result                                            */
} CRC_Type;


/* ================================================================================ */
/* ================                     SHAMD5                     ================ */
/* ================================================================================ */


/**
  * @brief Register map for SHAMD5 peripheral (SHAMD5)
  */

typedef struct                                      /*!< SHAMD5 Structure                                                      */
{
    __IO uint32_t  ODIGEST_A;                         /*!< SHA Outer Digest A                                                    */
    __IO uint32_t  ODIGEST_B;                         /*!< SHA Outer Digest B                                                    */
    __IO uint32_t  ODIGEST_C;                         /*!< SHA Outer Digest C                                                    */
    __IO uint32_t  ODIGEST_D;                         /*!< SHA Outer Digest D                                                    */
    __IO uint32_t  ODIGEST_E;                         /*!< SHA Outer Digest E                                                    */
    __IO uint32_t  ODIGEST_F;                         /*!< SHA Outer Digest F                                                    */
    __IO uint32_t  ODIGEST_G;                         /*!< SHA Outer Digest G                                                    */
    __IO uint32_t  ODIGEST_H;                         /*!< SHA Outer Digest H                                                    */
    __IO uint32_t  IDIGEST_A;                         /*!< SHA Inner Digest A                                                    */
    __IO uint32_t  IDIGEST_B;                         /*!< SHA Inner Digest B                                                    */
    __IO uint32_t  IDIGEST_C;                         /*!< SHA Inner Digest C                                                    */
    __IO uint32_t  IDIGEST_D;                         /*!< SHA Inner Digest D                                                    */
    __IO uint32_t  IDIGEST_E;                         /*!< SHA Inner Digest E                                                    */
    __IO uint32_t  IDIGEST_F;                         /*!< SHA Inner Digest F                                                    */
    __IO uint32_t  IDIGEST_G;                         /*!< SHA Inner Digest G                                                    */
    __IO uint32_t  IDIGEST_H;                         /*!< SHA Inner Digest H                                                    */
    __IO uint32_t  DIGEST_COUNT;                      /*!< SHA Digest Count                                                      */
    __IO uint32_t  MODE;                              /*!< SHA Mode                                                              */
    __IO uint32_t  LENGTH;                            /*!< SHA Length                                                            */
    __I  uint32_t  RESERVED0[13];
    __IO uint32_t  DATA_0_IN;                         /*!< SHA Data 0 Input                                                      */
    __IO uint32_t  DATA_1_IN;                         /*!< SHA Data 1 Input                                                      */
    __IO uint32_t  DATA_2_IN;                         /*!< SHA Data 2 Input                                                      */
    __IO uint32_t  DATA_3_IN;                         /*!< SHA Data 3 Input                                                      */
    __IO uint32_t  DATA_4_IN;                         /*!< SHA Data 4 Input                                                      */
    __IO uint32_t  DATA_5_IN;                         /*!< SHA Data 5 Input                                                      */
    __IO uint32_t  DATA_6_IN;                         /*!< SHA Data 6 Input                                                      */
    __IO uint32_t  DATA_7_IN;                         /*!< SHA Data 7 Input                                                      */
    __IO uint32_t  DATA_8_IN;                         /*!< SHA Data 8 Input                                                      */
    __IO uint32_t  DATA_9_IN;                         /*!< SHA Data 9 Input                                                      */
    __IO uint32_t  DATA_10_IN;                        /*!< SHA Data 10 Input                                                     */
    __IO uint32_t  DATA_11_IN;                        /*!< SHA Data 11 Input                                                     */
    __IO uint32_t  DATA_12_IN;                        /*!< SHA Data 12 Input                                                     */
    __IO uint32_t  DATA_13_IN;                        /*!< SHA Data 13 Input                                                     */
    __IO uint32_t  DATA_14_IN;                        /*!< SHA Data 14 Input                                                     */
    __IO uint32_t  DATA_15_IN;                        /*!< SHA Data 15 Input                                                     */
    __I  uint32_t  RESERVED1[16];
    __IO uint32_t  REVISION;                          /*!< SHA Revision                                                          */
    __I  uint32_t  RESERVED2[3];
    __IO uint32_t  SYSCONFIG;                         /*!< SHA System Configuration                                              */
    __IO uint32_t  SYSSTATUS;                         /*!< SHA System Status                                                     */
    __IO uint32_t  IRQSTATUS;                         /*!< SHA Interrupt Status                                                  */
    __IO uint32_t  IRQENABLE;                         /*!< SHA Interrupt Enable                                                  */
} SHAMD5_Type;

typedef struct
{
    __IO uint32_t  DMAIM;                             /*!< SHA DMA Interrupt Mask                                                */
    __IO uint32_t  DMARIS;                            /*!< SHA DMA Raw Interrupt Status                                          */
    __IO uint32_t  DMAMIS;                            /*!< SHA DMA Masked Interrupt Status                                       */
    __IO uint32_t  DMAIC;                             /*!< SHA DMA Interrupt Clear                                               */
} SHAMD5_DMA_Type;

/* ================================================================================ */
/* ================                       AES                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for AES peripheral (AES)
  */

typedef struct                                      /*!< AES Structure                                                         */
{
    __IO uint32_t  KEY2_6;                            /*!< AES Key 2_6                                                           */
    __IO uint32_t  KEY2_7;                            /*!< AES Key 2_7                                                           */
    __IO uint32_t  KEY2_4;                            /*!< AES Key 2_4                                                           */
    __IO uint32_t  KEY2_5;                            /*!< AES Key 2_5                                                           */
    __IO uint32_t  KEY2_2;                            /*!< AES Key 2_2                                                           */
    __IO uint32_t  KEY2_3;                            /*!< AES Key 2_3                                                           */
    __IO uint32_t  KEY2_0;                            /*!< AES Key 2_0                                                           */
    __IO uint32_t  KEY2_1;                            /*!< AES Key 2_1                                                           */
    __IO uint32_t  KEY1_6;                            /*!< AES Key 1_6                                                           */
    __IO uint32_t  KEY1_7;                            /*!< AES Key 1_7                                                           */
    __IO uint32_t  KEY1_4;                            /*!< AES Key 1_4                                                           */
    __IO uint32_t  KEY1_5;                            /*!< AES Key 1_5                                                           */
    __IO uint32_t  KEY1_2;                            /*!< AES Key 1_2                                                           */
    __IO uint32_t  KEY1_3;                            /*!< AES Key 1_3                                                           */
    __IO uint32_t  KEY1_0;                            /*!< AES Key 1_0                                                           */
    __IO uint32_t  KEY1_1;                            /*!< AES Key 1_1                                                           */
    __IO uint32_t  IV_IN_0;                           /*!< AES Initialization Vector Input 0                                     */
    __IO uint32_t  IV_IN_1;                           /*!< AES Initialization Vector Input 1                                     */
    __IO uint32_t  IV_IN_2;                           /*!< AES Initialization Vector Input 2                                     */
    __IO uint32_t  IV_IN_3;                           /*!< AES Initialization Vector Input 3                                     */
    __IO uint32_t  CTRL;                              /*!< AES Control                                                           */
    __IO uint32_t  C_LENGTH_0;                        /*!< AES Crypto Data Length 0                                              */
    __IO uint32_t  C_LENGTH_1;                        /*!< AES Crypto Data Length 1                                              */
    __IO uint32_t  AUTH_LENGTH;                       /*!< AES Authentication Data Length                                        */
    __IO uint32_t  DATA_IN_0;                         /*!< AES Data RW Plaintext/Ciphertext 0                                    */
    __IO uint32_t  DATA_IN_1;                         /*!< AES Data RW Plaintext/Ciphertext 1                                    */
    __IO uint32_t  DATA_IN_2;                         /*!< AES Data RW Plaintext/Ciphertext 2                                    */
    __IO uint32_t  DATA_IN_3;                         /*!< AES Data RW Plaintext/Ciphertext 3                                    */
    __IO uint32_t  TAG_OUT_0;                         /*!< AES Hash Tag Out 0                                                    */
    __IO uint32_t  TAG_OUT_1;                         /*!< AES Hash Tag Out 1                                                    */
    __IO uint32_t  TAG_OUT_2;                         /*!< AES Hash Tag Out 2                                                    */
    __IO uint32_t  TAG_OUT_3;                         /*!< AES Hash Tag Out 3                                                    */
    __IO uint32_t  REVISION;                          /*!< AES IP Revision Identifier                                            */
    __IO uint32_t  SYSCONFIG;                         /*!< AES System Configuration                                              */
    __IO uint32_t  SYSSTATUS;                         /*!< AES System Status                                                     */
    __IO uint32_t  IRQSTATUS;                         /*!< AES Interrupt Status                                                  */
    __IO uint32_t  IRQENABLE;                         /*!< AES Interrupt Enable                                                  */
    __IO uint32_t  DIRTYBITS;                         /*!< AES Dirty Bits                                                        */
} AES_Type;

typedef struct
{
    __IO uint32_t  DMAIM;                             /*!< AES DMA Interrupt Mask                                                */
    __IO uint32_t  DMARIS;                            /*!< AES DMA Raw Interrupt Status                                          */
    __IO uint32_t  DMAMIS;                            /*!< AES DMA Masked Interrupt Status                                       */
    __IO uint32_t  DMAIC;                             /*!< AES DMA Interrupt Clear                                               */
} AES_DMA_Type;

/* ================================================================================ */
/* ================                       DES                      ================ */
/* ================================================================================ */


/**
  * @brief Register map for DES peripheral (DES)
  */

typedef struct                                      /*!< DES Structure                                                         */
{
    __IO uint32_t  KEY3_L;                            /*!< DES Key 3 LSW for 192-Bit Key                                         */
    __IO uint32_t  KEY3_H;                            /*!< DES Key 3 MSW for 192-Bit Key                                         */
    __IO uint32_t  KEY2_L;                            /*!< DES Key 2 LSW for 128-Bit Key                                         */
    __IO uint32_t  KEY2_H;                            /*!< DES Key 2 MSW for 128-Bit Key                                         */
    __IO uint32_t  KEY1_L;                            /*!< DES Key 1 LSW for 64-Bit Key                                          */
    __IO uint32_t  KEY1_H;                            /*!< DES Key 1 MSW for 64-Bit Key                                          */
    __IO uint32_t  IV_L;                              /*!< DES Initialization Vector                                             */
    __IO uint32_t  IV_H;                              /*!< DES Initialization Vector                                             */
    __IO uint32_t  CTRL;                              /*!< DES Control                                                           */
    __IO uint32_t  LENGTH;                            /*!< DES Cryptographic Data Length                                         */
    __IO uint32_t  DATA_L;                            /*!< DES LSW Data RW                                                       */
    __IO uint32_t  DATA_H;                            /*!< DES MSW Data RW                                                       */
    __IO uint32_t  REVISION;                          /*!< DES Revision Number                                                   */
    __IO uint32_t  SYSCONFIG;                         /*!< DES System Configuration                                              */
    __IO uint32_t  SYSSTATUS;                         /*!< DES System Status                                                     */
    __IO uint32_t  IRQSTATUS;                         /*!< DES Interrupt Status                                                  */
    __IO uint32_t  IRQENABLE;                         /*!< DES Interrupt Enable                                                  */
    __IO uint32_t  DIRTYBITS;                         /*!< DES Dirty Bits                                                        */
} DES_Type;

typedef struct
{
    __IO uint32_t  DMAIM;                             /*!< DES DMA Interrupt Mask                                                */
    __IO uint32_t  DMARIS;                            /*!< DES DMA Raw Interrupt Status                                          */
    __IO uint32_t  DMAMIS;                            /*!< DES DMA Masked Interrupt Status                                       */
    __IO uint32_t  DMAIC;                             /*!< DES DMA Interrupt Clear                                               */
} DES_DMA_Type;



/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
#pragma pop
#elif defined(__ICCARM__)
/* leave anonymous unions enabled */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
/* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
#pragma warning restore
#else
#warning Not supported compiler type
#endif




/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define FLASH_BASE                      ((uint32_t)0x00000000)
#define SRAM_BASE                       ((uint32_t)0x20000000)
#define WATCHDOG0_BASE                  ((uint32_t)0x40000000)
#define WATCHDOG1_BASE                  ((uint32_t)0x40001000)
#define SSI0_BASE                       ((uint32_t)0x40008000)
#define SSI1_BASE                       ((uint32_t)0x40009000)
#define SSI2_BASE                       ((uint32_t)0x4000A000)
#define SSI3_BASE                       ((uint32_t)0x4000B000)
#define UART0_BASE                      ((uint32_t)0x4000C000)
#define UART1_BASE                      ((uint32_t)0x4000D000)
#define UART2_BASE                      ((uint32_t)0x4000E000)
#define UART3_BASE                      ((uint32_t)0x4000F000)
#define UART4_BASE                      ((uint32_t)0x40010000)
#define UART5_BASE                      ((uint32_t)0x40011000)
#define UART6_BASE                      ((uint32_t)0x40012000)
#define UART7_BASE                      ((uint32_t)0x40013000)
#define I2C0_BASE                       ((uint32_t)0x40020000)
#define I2C1_BASE                       ((uint32_t)0x40021000)
#define I2C2_BASE                       ((uint32_t)0x40022000)
#define I2C3_BASE                       ((uint32_t)0x40023000)
#define PWM0_BASE                       ((uint32_t)0x40028000)
#define QEI0_BASE                       ((uint32_t)0x4002C000)
#define TIMER0_BASE                     ((uint32_t)0x40030000)
#define TIMER1_BASE                     ((uint32_t)0x40031000)
#define TIMER2_BASE                     ((uint32_t)0x40032000)
#define TIMER3_BASE                     ((uint32_t)0x40033000)
#define TIMER4_BASE                     ((uint32_t)0x40034000)
#define TIMER5_BASE                     ((uint32_t)0x40035000)
#define ADC0_BASE                       ((uint32_t)0x40038000)
#define ADC1_BASE                       ((uint32_t)0x40039000)
#define COMP_BASE                       ((uint32_t)0x4003C000)
#define CAN0_BASE                       ((uint32_t)0x40040000)
#define CAN1_BASE                       ((uint32_t)0x40041000)
#define USB0_BASE                       ((uint32_t)0x40050000)
#define GPIO_PORTA_BASE                 ((uint32_t)0x40058000)
#define GPIO_PORTB_BASE                 ((uint32_t)0x40059000)
#define GPIO_PORTC_BASE                 ((uint32_t)0x4005A000)
#define GPIO_PORTD_BASE                 ((uint32_t)0x4005B000)
#define GPIO_PORTE_BASE                 ((uint32_t)0x4005C000)
#define GPIO_PORTF_BASE                 ((uint32_t)0x4005D000)
#define GPIO_PORTG_BASE                 ((uint32_t)0x4005E000)
#define GPIO_PORTH_BASE                 ((uint32_t)0x4005F000)
#define GPIO_PORTJ_BASE                 ((uint32_t)0x40060000)
#define GPIO_PORTK_BASE                 ((uint32_t)0x40061000)
#define GPIO_PORTL_BASE                 ((uint32_t)0x40062000)
#define GPIO_PORTM_BASE                 ((uint32_t)0x40063000)
#define GPIO_PORTN_BASE                 ((uint32_t)0x40064000)
#define GPIO_PORTP_BASE                 ((uint32_t)0x40065000)
#define GPIO_PORTQ_BASE                 ((uint32_t)0x40066000)
#define EEPROM_BASE                     ((uint32_t)0x400AF000)
#define I2C8_BASE                       ((uint32_t)0x400B8000)
#define I2C9_BASE                       ((uint32_t)0x400B9000)
#define I2C4_BASE                       ((uint32_t)0x400C0000)
#define I2C5_BASE                       ((uint32_t)0x400C1000)
#define I2C6_BASE                       ((uint32_t)0x400C2000)
#define I2C7_BASE                       ((uint32_t)0x400C3000)
#define EPI0_BASE                       ((uint32_t)0x400D0000)
#define TIMER6_BASE                     ((uint32_t)0x400E0000)
#define TIMER7_BASE                     ((uint32_t)0x400E1000)
#define EMAC0_BASE                      ((uint32_t)0x400EC000)
#define SYSEXC_BASE                     ((uint32_t)0x400F9000)
#define HIB_BASE                        ((uint32_t)0x400FC000)
#define FLASH_CTRL_BASE                 ((uint32_t)0x400FD000)
#define SYSCTL_BASE                     ((uint32_t)0x400FE000)
#define UDMA_BASE                       ((uint32_t)0x400FF000)
#define CCM0_BASE                       ((uint32_t)0x44030000)
#define CRC_BASE                        (CCM0_BASE+0x00000400)
#define SHAMD5_BASE                     ((uint32_t)0x44034000)
#define SHAMD5_DMA_BASE                 (CCM0_BASE+0x00000010)
#define AES_BASE                        ((uint32_t)0x44036000)
#define AES_DMA_BASE                    (CCM0_BASE+0x00000020)
#define DES_BASE                        ((uint32_t)0x44038000)
#define DES_DMA_BASE                    (CCM0_BASE+0x00000030)


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define WATCHDOG0                       ((WATCHDOG0_Type          *) WATCHDOG0_BASE)
#define WATCHDOG1                       ((WATCHDOG0_Type          *) WATCHDOG1_BASE)
#define SSI0                            ((SSI0_Type               *) SSI0_BASE)
#define SSI1                            ((SSI0_Type               *) SSI1_BASE)
#define SSI2                            ((SSI0_Type               *) SSI2_BASE)
#define SSI3                            ((SSI0_Type               *) SSI3_BASE)
#define UART0                           ((UART0_Type              *) UART0_BASE)
#define UART1                           ((UART0_Type              *) UART1_BASE)
#define UART2                           ((UART0_Type              *) UART2_BASE)
#define UART3                           ((UART0_Type              *) UART3_BASE)
#define UART4                           ((UART0_Type              *) UART4_BASE)
#define UART5                           ((UART0_Type              *) UART5_BASE)
#define UART6                           ((UART0_Type              *) UART6_BASE)
#define UART7                           ((UART0_Type              *) UART7_BASE)
#define I2C0                            ((I2C0_Type               *) I2C0_BASE)
#define I2C1                            ((I2C0_Type               *) I2C1_BASE)
#define I2C2                            ((I2C0_Type               *) I2C2_BASE)
#define I2C3                            ((I2C0_Type               *) I2C3_BASE)
#define PWM0                            ((PWM0_Type               *) PWM0_BASE)
#define QEI0                            ((QEI0_Type               *) QEI0_BASE)
#define TIMER0                          ((TIMER0_Type             *) TIMER0_BASE)
#define TIMER1                          ((TIMER0_Type             *) TIMER1_BASE)
#define TIMER2                          ((TIMER0_Type             *) TIMER2_BASE)
#define TIMER3                          ((TIMER0_Type             *) TIMER3_BASE)
#define TIMER4                          ((TIMER0_Type             *) TIMER4_BASE)
#define TIMER5                          ((TIMER0_Type             *) TIMER5_BASE)
#define ADC0                            ((ADC0_Type               *) ADC0_BASE)
#define ADC1                            ((ADC0_Type               *) ADC1_BASE)
#define COMP                            ((COMP_Type               *) COMP_BASE)
#define CAN0                            ((CAN0_Type               *) CAN0_BASE)
#define CAN1                            ((CAN0_Type               *) CAN1_BASE)
#define USB0                            ((USB0_Type               *) USB0_BASE)
#define GPIOA                           ((GPIO_Type               *) GPIO_PORTA_BASE)
#define GPIOB                           ((GPIO_Type               *) GPIO_PORTB_BASE)
#define GPIOC                           ((GPIO_Type               *) GPIO_PORTC_BASE)
#define GPIOD                           ((GPIO_Type               *) GPIO_PORTD_BASE)
#define GPIOE                           ((GPIO_Type               *) GPIO_PORTE_BASE)
#define GPIOF                           ((GPIO_Type               *) GPIO_PORTF_BASE)
#define GPIOG                           ((GPIO_Type               *) GPIO_PORTG_BASE)
#define GPIOH                           ((GPIO_Type               *) GPIO_PORTH_BASE)
#define GPIOJ                           ((GPIO_Type               *) GPIO_PORTJ_BASE)
#define GPIOK                           ((GPIO_Type               *) GPIO_PORTK_BASE)
#define GPIOL                           ((GPIO_Type               *) GPIO_PORTL_BASE)
#define GPIOM                           ((GPIO_Type               *) GPIO_PORTM_BASE)
#define GPION                           ((GPIO_Type               *) GPIO_PORTN_BASE)
#define GPIOP                           ((GPIO_Type               *) GPIO_PORTP_BASE)
#define GPIOQ                           ((GPIO_Type               *) GPIO_PORTQ_BASE)
#define EEPROM                          ((EEPROM_Type             *) EEPROM_BASE)
#define I2C8                            ((I2C0_Type               *) I2C8_BASE)
#define I2C9                            ((I2C0_Type               *) I2C9_BASE)
#define I2C4                            ((I2C0_Type               *) I2C4_BASE)
#define I2C5                            ((I2C0_Type               *) I2C5_BASE)
#define I2C6                            ((I2C0_Type               *) I2C6_BASE)
#define I2C7                            ((I2C0_Type               *) I2C7_BASE)
#define EPI0                            ((EPI0_Type               *) EPI0_BASE)
#define TIMER6                          ((TIMER0_Type             *) TIMER6_BASE)
#define TIMER7                          ((TIMER0_Type             *) TIMER7_BASE)
#define EMAC0                           ((EMAC0_Type              *) EMAC0_BASE)
#define SYSEXC                          ((SYSEXC_Type             *) SYSEXC_BASE)
#define HIB                             ((HIB_Type                *) HIB_BASE)
#define FLASH_CTRL                      ((FLASH_CTRL_Type         *) FLASH_CTRL_BASE)
#define SYSCTL                          ((SYSCTL_Type             *) SYSCTL_BASE)
#define UDMA                            ((UDMA_Type               *) UDMA_BASE)
#define CCM0                            ((CCM0_Type               *) CCM0_BASE)
#define CRC                             ((CRC_Type                *) CRC_BASE)
#define SHAMD5                          ((SHAMD5_Type             *) SHAMD5_BASE)
#define SHAMD5_DMA                      ((SHAMD5_DMA_Type         *) SHAMD5_DMA_BASE)
#define AES                             ((AES_Type                *) AES_BASE)
#define AES_DMA                         ((AES_DMA_Type            *) AES_DMA_BASE)
#define DES                             ((DES_Type                *) DES_BASE)
#define DES_DMA                         ((DES_DMA_Type            *) DES_DMA_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */

/** @addtogroup Device_Peripheral_Bitfields
  * @{
  */

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_LOAD register.
//
//*****************************************************************************
#define WDT_LOAD_M              0xFFFFFFFF  // Watchdog Load Value
#define WDT_LOAD_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_VALUE register.
//
//*****************************************************************************
#define WDT_VALUE_M             0xFFFFFFFF  // Watchdog Value
#define WDT_VALUE_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_CTL register.
//
//*****************************************************************************
#define WDT_CTL_WRC             0x80000000  // Write Complete
#define WDT_CTL_INTTYPE         0x00000004  // Watchdog Interrupt Type
#define WDT_CTL_RESEN           0x00000002  // Watchdog Reset Enable
#define WDT_CTL_INTEN           0x00000001  // Watchdog Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_ICR register.
//
//*****************************************************************************
#define WDT_ICR_M               0xFFFFFFFF  // Watchdog Interrupt Clear
#define WDT_ICR_S               0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_RIS register.
//
//*****************************************************************************
#define WDT_RIS_WDTRIS          0x00000001  // Watchdog Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_MIS register.
//
//*****************************************************************************
#define WDT_MIS_WDTMIS          0x00000001  // Watchdog Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_TEST register.
//
//*****************************************************************************
#define WDT_TEST_STALL          0x00000100  // Watchdog Stall Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_LOCK register.
//
//*****************************************************************************
#define WDT_LOCK_M              0xFFFFFFFF  // Watchdog Lock
#define WDT_LOCK_UNLOCKED       0x00000000  // Unlocked
#define WDT_LOCK_LOCKED         0x00000001  // Locked
#define WDT_LOCK_UNLOCK         0x1ACCE551  // Unlocks the watchdog timer

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR0 register.
//
//*****************************************************************************
#define SSI_CR0_SCR_M           0x0000FF00  // SSI Serial Clock Rate
#define SSI_CR0_SPH             0x00000080  // SSI Serial Clock Phase
#define SSI_CR0_SPO             0x00000040  // SSI Serial Clock Polarity
#define SSI_CR0_FRF_M           0x00000030  // SSI Frame Format Select
#define SSI_CR0_FRF_MOTO        0x00000000  // Freescale SPI Frame Format
#define SSI_CR0_FRF_TI          0x00000010  // Synchronous Serial Frame Format
#define SSI_CR0_DSS_M           0x0000000F  // SSI Data Size Select
#define SSI_CR0_DSS_4           0x00000003  // 4-bit data
#define SSI_CR0_DSS_5           0x00000004  // 5-bit data
#define SSI_CR0_DSS_6           0x00000005  // 6-bit data
#define SSI_CR0_DSS_7           0x00000006  // 7-bit data
#define SSI_CR0_DSS_8           0x00000007  // 8-bit data
#define SSI_CR0_DSS_9           0x00000008  // 9-bit data
#define SSI_CR0_DSS_10          0x00000009  // 10-bit data
#define SSI_CR0_DSS_11          0x0000000A  // 11-bit data
#define SSI_CR0_DSS_12          0x0000000B  // 12-bit data
#define SSI_CR0_DSS_13          0x0000000C  // 13-bit data
#define SSI_CR0_DSS_14          0x0000000D  // 14-bit data
#define SSI_CR0_DSS_15          0x0000000E  // 15-bit data
#define SSI_CR0_DSS_16          0x0000000F  // 16-bit data
#define SSI_CR0_SCR_S           8

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR1 register.
//
//*****************************************************************************
#define SSI_CR1_EOM             0x00000800  // Stop Frame (End of Message)
#define SSI_CR1_FSSHLDFRM       0x00000400  // FSS Hold Frame
#define SSI_CR1_HSCLKEN         0x00000200  // High Speed Clock Enable
#define SSI_CR1_DIR             0x00000100  // SSI Direction of Operation
#define SSI_CR1_MODE_M          0x000000C0  // SSI Mode
#define SSI_CR1_MODE_LEGACY     0x00000000  // Legacy SSI mode
#define SSI_CR1_MODE_BI         0x00000040  // Bi-SSI mode
#define SSI_CR1_MODE_QUAD       0x00000080  // Quad-SSI Mode
#define SSI_CR1_MODE_ADVANCED   0x000000C0  // Advanced SSI Mode with 8-bit
// packet size
#define SSI_CR1_EOT             0x00000010  // End of Transmission
#define SSI_CR1_MS              0x00000004  // SSI Master/Slave Select
#define SSI_CR1_SSE             0x00000002  // SSI Synchronous Serial Port
// Enable
#define SSI_CR1_LBM             0x00000001  // SSI Loopback Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_DR register.
//
//*****************************************************************************
#define SSI_DR_DATA_M           0x0000FFFF  // SSI Receive/Transmit Data
#define SSI_DR_DATA_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_SR register.
//
//*****************************************************************************
#define SSI_SR_BSY              0x00000010  // SSI Busy Bit
#define SSI_SR_RFF              0x00000008  // SSI Receive FIFO Full
#define SSI_SR_RNE              0x00000004  // SSI Receive FIFO Not Empty
#define SSI_SR_TNF              0x00000002  // SSI Transmit FIFO Not Full
#define SSI_SR_TFE              0x00000001  // SSI Transmit FIFO Empty

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CPSR register.
//
//*****************************************************************************
#define SSI_CPSR_CPSDVSR_M      0x000000FF  // SSI Clock Prescale Divisor
#define SSI_CPSR_CPSDVSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_IM register.
//
//*****************************************************************************
#define SSI_IM_EOTIM            0x00000040  // End of Transmit Interrupt Mask
#define SSI_IM_DMATXIM          0x00000020  // SSI Transmit DMA Interrupt Mask
#define SSI_IM_DMARXIM          0x00000010  // SSI Receive DMA Interrupt Mask
#define SSI_IM_TXIM             0x00000008  // SSI Transmit FIFO Interrupt Mask
#define SSI_IM_RXIM             0x00000004  // SSI Receive FIFO Interrupt Mask
#define SSI_IM_RTIM             0x00000002  // SSI Receive Time-Out Interrupt
// Mask
#define SSI_IM_RORIM            0x00000001  // SSI Receive Overrun Interrupt
// Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_RIS register.
//
//*****************************************************************************
#define SSI_RIS_EOTRIS          0x00000040  // End of Transmit Raw Interrupt
// Status
#define SSI_RIS_DMATXRIS        0x00000020  // SSI Transmit DMA Raw Interrupt
// Status
#define SSI_RIS_DMARXRIS        0x00000010  // SSI Receive DMA Raw Interrupt
// Status
#define SSI_RIS_TXRIS           0x00000008  // SSI Transmit FIFO Raw Interrupt
// Status
#define SSI_RIS_RXRIS           0x00000004  // SSI Receive FIFO Raw Interrupt
// Status
#define SSI_RIS_RTRIS           0x00000002  // SSI Receive Time-Out Raw
// Interrupt Status
#define SSI_RIS_RORRIS          0x00000001  // SSI Receive Overrun Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_MIS register.
//
//*****************************************************************************
#define SSI_MIS_EOTMIS          0x00000040  // End of Transmit Masked Interrupt
// Status
#define SSI_MIS_DMATXMIS        0x00000020  // SSI Transmit DMA Masked
// Interrupt Status
#define SSI_MIS_DMARXMIS        0x00000010  // SSI Receive DMA Masked Interrupt
// Status
#define SSI_MIS_TXMIS           0x00000008  // SSI Transmit FIFO Masked
// Interrupt Status
#define SSI_MIS_RXMIS           0x00000004  // SSI Receive FIFO Masked
// Interrupt Status
#define SSI_MIS_RTMIS           0x00000002  // SSI Receive Time-Out Masked
// Interrupt Status
#define SSI_MIS_RORMIS          0x00000001  // SSI Receive Overrun Masked
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_ICR register.
//
//*****************************************************************************
#define SSI_ICR_EOTIC           0x00000040  // End of Transmit Interrupt Clear
#define SSI_ICR_DMATXIC         0x00000020  // SSI Transmit DMA Interrupt Clear
#define SSI_ICR_DMARXIC         0x00000010  // SSI Receive DMA Interrupt Clear
#define SSI_ICR_RTIC            0x00000002  // SSI Receive Time-Out Interrupt
// Clear
#define SSI_ICR_RORIC           0x00000001  // SSI Receive Overrun Interrupt
// Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_DMACTL register.
//
//*****************************************************************************
#define SSI_DMACTL_TXDMAE       0x00000002  // Transmit DMA Enable
#define SSI_DMACTL_RXDMAE       0x00000001  // Receive DMA Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_PP register.
//
//*****************************************************************************
#define SSI_PP_FSSHLDFRM        0x00000008  // FSS Hold Frame Capability
#define SSI_PP_MODE_M           0x00000006  // Mode of Operation
#define SSI_PP_MODE_LEGACY      0x00000000  // Legacy SSI mode
#define SSI_PP_MODE_ADVBI       0x00000002  // Legacy mode, Advanced SSI mode
// and Bi-SSI mode enabled
#define SSI_PP_MODE_ADVBIQUAD   0x00000004  // Legacy mode, Advanced mode,
// Bi-SSI and Quad-SSI mode enabled
#define SSI_PP_HSCLK            0x00000001  // High Speed Capability

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CC register.
//
//*****************************************************************************
#define SSI_CC_CS_M             0x0000000F  // SSI Baud Clock Source
#define SSI_CC_CS_SYSPLL        0x00000000  // System clock (based on clock
// source and divisor factor)
#define SSI_CC_CS_PIOSC         0x00000005  // PIOSC

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_DR register.
//
//*****************************************************************************
#define UART_DR_OE              0x00000800  // UART Overrun Error
#define UART_DR_BE              0x00000400  // UART Break Error
#define UART_DR_PE              0x00000200  // UART Parity Error
#define UART_DR_FE              0x00000100  // UART Framing Error
#define UART_DR_DATA_M          0x000000FF  // Data Transmitted or Received
#define UART_DR_DATA_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_RSR register.
//
//*****************************************************************************
#define UART_RSR_OE             0x00000008  // UART Overrun Error
#define UART_RSR_BE             0x00000004  // UART Break Error
#define UART_RSR_PE             0x00000002  // UART Parity Error
#define UART_RSR_FE             0x00000001  // UART Framing Error

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_ECR register.
//
//*****************************************************************************
#define UART_ECR_DATA_M         0x000000FF  // Error Clear
#define UART_ECR_DATA_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_FR register.
//
//*****************************************************************************
#define UART_FR_RI              0x00000100  // Ring Indicator
#define UART_FR_TXFE            0x00000080  // UART Transmit FIFO Empty
#define UART_FR_RXFF            0x00000040  // UART Receive FIFO Full
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_FR_BUSY            0x00000008  // UART Busy
#define UART_FR_DCD             0x00000004  // Data Carrier Detect
#define UART_FR_DSR             0x00000002  // Data Set Ready
#define UART_FR_CTS             0x00000001  // Clear To Send

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_ILPR register.
//
//*****************************************************************************
#define UART_ILPR_ILPDVSR_M     0x000000FF  // IrDA Low-Power Divisor
#define UART_ILPR_ILPDVSR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_IBRD register.
//
//*****************************************************************************
#define UART_IBRD_DIVINT_M      0x0000FFFF  // Integer Baud-Rate Divisor
#define UART_IBRD_DIVINT_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_FBRD register.
//
//*****************************************************************************
#define UART_FBRD_DIVFRAC_M     0x0000003F  // Fractional Baud-Rate Divisor
#define UART_FBRD_DIVFRAC_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_LCRH register.
//
//*****************************************************************************
#define UART_LCRH_SPS           0x00000080  // UART Stick Parity Select
#define UART_LCRH_WLEN_M        0x00000060  // UART Word Length
#define UART_LCRH_WLEN_5        0x00000000  // 5 bits (default)
#define UART_LCRH_WLEN_6        0x00000020  // 6 bits
#define UART_LCRH_WLEN_7        0x00000040  // 7 bits
#define UART_LCRH_WLEN_8        0x00000060  // 8 bits
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_LCRH_STP2          0x00000008  // UART Two Stop Bits Select
#define UART_LCRH_EPS           0x00000004  // UART Even Parity Select
#define UART_LCRH_PEN           0x00000002  // UART Parity Enable
#define UART_LCRH_BRK           0x00000001  // UART Send Break

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_CTL register.
//
//*****************************************************************************
#define UART_CTL_CTSEN          0x00008000  // Enable Clear To Send
#define UART_CTL_RTSEN          0x00004000  // Enable Request to Send
#define UART_CTL_RTS            0x00000800  // Request to Send
#define UART_CTL_DTR            0x00000400  // Data Terminal Ready
#define UART_CTL_RXE            0x00000200  // UART Receive Enable
#define UART_CTL_TXE            0x00000100  // UART Transmit Enable
#define UART_CTL_LBE            0x00000080  // UART Loop Back Enable
#define UART_CTL_HSE            0x00000020  // High-Speed Enable
#define UART_CTL_EOT            0x00000010  // End of Transmission
#define UART_CTL_SMART          0x00000008  // ISO 7816 Smart Card Support
#define UART_CTL_SIRLP          0x00000004  // UART SIR Low-Power Mode
#define UART_CTL_SIREN          0x00000002  // UART SIR Enable
#define UART_CTL_UARTEN         0x00000001  // UART Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_IFLS register.
//
//*****************************************************************************
#define UART_IFLS_RX_M          0x00000038  // UART Receive Interrupt FIFO
// Level Select
#define UART_IFLS_RX1_8         0x00000000  // RX FIFO >= 1/8 full
#define UART_IFLS_RX2_8         0x00000008  // RX FIFO >= 1/4 full
#define UART_IFLS_RX4_8         0x00000010  // RX FIFO >= 1/2 full (default)
#define UART_IFLS_RX6_8         0x00000018  // RX FIFO >= 3/4 full
#define UART_IFLS_RX7_8         0x00000020  // RX FIFO >= 7/8 full
#define UART_IFLS_TX_M          0x00000007  // UART Transmit Interrupt FIFO
// Level Select
#define UART_IFLS_TX1_8         0x00000000  // TX FIFO <= 1/8 full
#define UART_IFLS_TX2_8         0x00000001  // TX FIFO <= 1/4 full
#define UART_IFLS_TX4_8         0x00000002  // TX FIFO <= 1/2 full (default)
#define UART_IFLS_TX6_8         0x00000003  // TX FIFO <= 3/4 full
#define UART_IFLS_TX7_8         0x00000004  // TX FIFO <= 7/8 full

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_IM register.
//
//*****************************************************************************
#define UART_IM_DMATXIM         0x00020000  // Transmit DMA Interrupt Mask
#define UART_IM_DMARXIM         0x00010000  // Receive DMA Interrupt Mask
#define UART_IM_9BITIM          0x00001000  // 9-Bit Mode Interrupt Mask
#define UART_IM_EOTIM           0x00000800  // End of Transmission Interrupt
// Mask
#define UART_IM_OEIM            0x00000400  // UART Overrun Error Interrupt
// Mask
#define UART_IM_BEIM            0x00000200  // UART Break Error Interrupt Mask
#define UART_IM_PEIM            0x00000100  // UART Parity Error Interrupt Mask
#define UART_IM_FEIM            0x00000080  // UART Framing Error Interrupt
// Mask
#define UART_IM_RTIM            0x00000040  // UART Receive Time-Out Interrupt
// Mask
#define UART_IM_TXIM            0x00000020  // UART Transmit Interrupt Mask
#define UART_IM_RXIM            0x00000010  // UART Receive Interrupt Mask
#define UART_IM_DSRMIM          0x00000008  // UART Data Set Ready Modem
// Interrupt Mask
#define UART_IM_DCDMIM          0x00000004  // UART Data Carrier Detect Modem
// Interrupt Mask
#define UART_IM_CTSMIM          0x00000002  // UART Clear to Send Modem
// Interrupt Mask
#define UART_IM_RIMIM           0x00000001  // UART Ring Indicator Modem
// Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_RIS register.
//
//*****************************************************************************
#define UART_RIS_DMATXRIS       0x00020000  // Transmit DMA Raw Interrupt
// Status
#define UART_RIS_DMARXRIS       0x00010000  // Receive DMA Raw Interrupt Status
#define UART_RIS_9BITRIS        0x00001000  // 9-Bit Mode Raw Interrupt Status
#define UART_RIS_EOTRIS         0x00000800  // End of Transmission Raw
// Interrupt Status
#define UART_RIS_OERIS          0x00000400  // UART Overrun Error Raw Interrupt
// Status
#define UART_RIS_BERIS          0x00000200  // UART Break Error Raw Interrupt
// Status
#define UART_RIS_PERIS          0x00000100  // UART Parity Error Raw Interrupt
// Status
#define UART_RIS_FERIS          0x00000080  // UART Framing Error Raw Interrupt
// Status
#define UART_RIS_RTRIS          0x00000040  // UART Receive Time-Out Raw
// Interrupt Status
#define UART_RIS_TXRIS          0x00000020  // UART Transmit Raw Interrupt
// Status
#define UART_RIS_RXRIS          0x00000010  // UART Receive Raw Interrupt
// Status
#define UART_RIS_DSRRIS         0x00000008  // UART Data Set Ready Modem Raw
// Interrupt Status
#define UART_RIS_DCDRIS         0x00000004  // UART Data Carrier Detect Modem
// Raw Interrupt Status
#define UART_RIS_CTSRIS         0x00000002  // UART Clear to Send Modem Raw
// Interrupt Status
#define UART_RIS_RIRIS          0x00000001  // UART Ring Indicator Modem Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_MIS register.
//
//*****************************************************************************
#define UART_MIS_DMATXMIS       0x00020000  // Transmit DMA Masked Interrupt
// Status
#define UART_MIS_DMARXMIS       0x00010000  // Receive DMA Masked Interrupt
// Status
#define UART_MIS_9BITMIS        0x00001000  // 9-Bit Mode Masked Interrupt
// Status
#define UART_MIS_EOTMIS         0x00000800  // End of Transmission Masked
// Interrupt Status
#define UART_MIS_OEMIS          0x00000400  // UART Overrun Error Masked
// Interrupt Status
#define UART_MIS_BEMIS          0x00000200  // UART Break Error Masked
// Interrupt Status
#define UART_MIS_PEMIS          0x00000100  // UART Parity Error Masked
// Interrupt Status
#define UART_MIS_FEMIS          0x00000080  // UART Framing Error Masked
// Interrupt Status
#define UART_MIS_RTMIS          0x00000040  // UART Receive Time-Out Masked
// Interrupt Status
#define UART_MIS_TXMIS          0x00000020  // UART Transmit Masked Interrupt
// Status
#define UART_MIS_RXMIS          0x00000010  // UART Receive Masked Interrupt
// Status
#define UART_MIS_DSRMIS         0x00000008  // UART Data Set Ready Modem Masked
// Interrupt Status
#define UART_MIS_DCDMIS         0x00000004  // UART Data Carrier Detect Modem
// Masked Interrupt Status
#define UART_MIS_CTSMIS         0x00000002  // UART Clear to Send Modem Masked
// Interrupt Status
#define UART_MIS_RIMIS          0x00000001  // UART Ring Indicator Modem Masked
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_ICR register.
//
//*****************************************************************************
#define UART_ICR_DMATXIC        0x00020000  // Transmit DMA Interrupt Clear
#define UART_ICR_DMARXIC        0x00010000  // Receive DMA Interrupt Clear
#define UART_ICR_9BITIC         0x00001000  // 9-Bit Mode Interrupt Clear
#define UART_ICR_EOTIC          0x00000800  // End of Transmission Interrupt
// Clear
#define UART_ICR_OEIC           0x00000400  // Overrun Error Interrupt Clear
#define UART_ICR_BEIC           0x00000200  // Break Error Interrupt Clear
#define UART_ICR_PEIC           0x00000100  // Parity Error Interrupt Clear
#define UART_ICR_FEIC           0x00000080  // Framing Error Interrupt Clear
#define UART_ICR_RTIC           0x00000040  // Receive Time-Out Interrupt Clear
#define UART_ICR_TXIC           0x00000020  // Transmit Interrupt Clear
#define UART_ICR_RXIC           0x00000010  // Receive Interrupt Clear
#define UART_ICR_DSRMIC         0x00000008  // UART Data Set Ready Modem
// Interrupt Clear
#define UART_ICR_DCDMIC         0x00000004  // UART Data Carrier Detect Modem
// Interrupt Clear
#define UART_ICR_CTSMIC         0x00000002  // UART Clear to Send Modem
// Interrupt Clear
#define UART_ICR_RIMIC          0x00000001  // UART Ring Indicator Modem
// Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_DMACTL register.
//
//*****************************************************************************
#define UART_DMACTL_DMAERR      0x00000004  // DMA on Error
#define UART_DMACTL_TXDMAE      0x00000002  // Transmit DMA Enable
#define UART_DMACTL_RXDMAE      0x00000001  // Receive DMA Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_9BITADDR
// register.
//
//*****************************************************************************
#define UART_9BITADDR_9BITEN    0x00008000  // Enable 9-Bit Mode
#define UART_9BITADDR_ADDR_M    0x000000FF  // Self Address for 9-Bit Mode
#define UART_9BITADDR_ADDR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_9BITAMASK
// register.
//
//*****************************************************************************
#define UART_9BITAMASK_MASK_M   0x000000FF  // Self Address Mask for 9-Bit Mode
#define UART_9BITAMASK_MASK_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_PP register.
//
//*****************************************************************************
#define UART_PP_MSE             0x00000008  // Modem Support Extended
#define UART_PP_MS              0x00000004  // Modem Support
#define UART_PP_NB              0x00000002  // 9-Bit Support
#define UART_PP_SC              0x00000001  // Smart Card Support

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_CC register.
//
//*****************************************************************************
#define UART_CC_CS_M            0x0000000F  // UART Baud Clock Source
#define UART_CC_CS_SYSCLK       0x00000000  // System clock (based on clock
// source and divisor factor)
#define UART_CC_CS_PIOSC        0x00000005  // PIOSC

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MSA register.
//
//*****************************************************************************
#define I2C_MSA_SA_M            0x000000FE  // I2C Slave Address
#define I2C_MSA_RS              0x00000001  // Receive not send
#define I2C_MSA_SA_S            1

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCS register.
//
//*****************************************************************************
#define I2C_MCS_ACTDMARX        0x80000000  // DMA RX Active Status
#define I2C_MCS_ACTDMATX        0x40000000  // DMA TX Active Status
#define I2C_MCS_CLKTO           0x00000080  // Clock Timeout Error
#define I2C_MCS_BURST           0x00000040  // Burst Enable
#define I2C_MCS_BUSBSY          0x00000040  // Bus Busy
#define I2C_MCS_IDLE            0x00000020  // I2C Idle
#define I2C_MCS_QCMD            0x00000020  // Quick Command
#define I2C_MCS_ARBLST          0x00000010  // Arbitration Lost
#define I2C_MCS_HS              0x00000010  // High-Speed Enable
#define I2C_MCS_ACK             0x00000008  // Data Acknowledge Enable
#define I2C_MCS_DATACK          0x00000008  // Acknowledge Data
#define I2C_MCS_ADRACK          0x00000004  // Acknowledge Address
#define I2C_MCS_STOP            0x00000004  // Generate STOP
#define I2C_MCS_ERROR           0x00000002  // Error
#define I2C_MCS_START           0x00000002  // Generate START
#define I2C_MCS_RUN             0x00000001  // I2C Master Enable
#define I2C_MCS_BUSY            0x00000001  // I2C Busy

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MDR register.
//
//*****************************************************************************
#define I2C_MDR_DATA_M          0x000000FF  // This byte contains the data
// transferred during a transaction
#define I2C_MDR_DATA_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MTPR register.
//
//*****************************************************************************
#define I2C_MTPR_PULSEL_M       0x00070000  // Glitch Suppression Pulse Width
#define I2C_MTPR_PULSEL_BYPASS  0x00000000  // Bypass
#define I2C_MTPR_PULSEL_1       0x00010000  // 1 clock
#define I2C_MTPR_PULSEL_2       0x00020000  // 2 clocks
#define I2C_MTPR_PULSEL_3       0x00030000  // 3 clocks
#define I2C_MTPR_PULSEL_4       0x00040000  // 4 clocks
#define I2C_MTPR_PULSEL_8       0x00050000  // 8 clocks
#define I2C_MTPR_PULSEL_16      0x00060000  // 16 clocks
#define I2C_MTPR_PULSEL_31      0x00070000  // 31 clocks
#define I2C_MTPR_HS             0x00000080  // High-Speed Enable
#define I2C_MTPR_TPR_M          0x0000007F  // Timer Period
#define I2C_MTPR_TPR_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MIMR register.
//
//*****************************************************************************
#define I2C_MIMR_RXFFIM         0x00000800  // Receive FIFO Full Interrupt Mask
#define I2C_MIMR_TXFEIM         0x00000400  // Transmit FIFO Empty Interrupt
// Mask
#define I2C_MIMR_RXIM           0x00000200  // Receive FIFO Request Interrupt
// Mask
#define I2C_MIMR_TXIM           0x00000100  // Transmit FIFO Request Interrupt
// Mask
#define I2C_MIMR_ARBLOSTIM      0x00000080  // Arbitration Lost Interrupt Mask
#define I2C_MIMR_STOPIM         0x00000040  // STOP Detection Interrupt Mask
#define I2C_MIMR_STARTIM        0x00000020  // START Detection Interrupt Mask
#define I2C_MIMR_NACKIM         0x00000010  // Address/Data NACK Interrupt Mask
#define I2C_MIMR_DMATXIM        0x00000008  // Transmit DMA Interrupt Mask
#define I2C_MIMR_DMARXIM        0x00000004  // Receive DMA Interrupt Mask
#define I2C_MIMR_CLKIM          0x00000002  // Clock Timeout Interrupt Mask
#define I2C_MIMR_IM             0x00000001  // Master Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MRIS register.
//
//*****************************************************************************
#define I2C_MRIS_RXFFRIS        0x00000800  // Receive FIFO Full Raw Interrupt
// Status
#define I2C_MRIS_TXFERIS        0x00000400  // Transmit FIFO Empty Raw
// Interrupt Status
#define I2C_MRIS_RXRIS          0x00000200  // Receive FIFO Request Raw
// Interrupt Status
#define I2C_MRIS_TXRIS          0x00000100  // Transmit Request Raw Interrupt
// Status
#define I2C_MRIS_ARBLOSTRIS     0x00000080  // Arbitration Lost Raw Interrupt
// Status
#define I2C_MRIS_STOPRIS        0x00000040  // STOP Detection Raw Interrupt
// Status
#define I2C_MRIS_STARTRIS       0x00000020  // START Detection Raw Interrupt
// Status
#define I2C_MRIS_NACKRIS        0x00000010  // Address/Data NACK Raw Interrupt
// Status
#define I2C_MRIS_DMATXRIS       0x00000008  // Transmit DMA Raw Interrupt
// Status
#define I2C_MRIS_DMARXRIS       0x00000004  // Receive DMA Raw Interrupt Status
#define I2C_MRIS_CLKRIS         0x00000002  // Clock Timeout Raw Interrupt
// Status
#define I2C_MRIS_RIS            0x00000001  // Master Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MMIS register.
//
//*****************************************************************************
#define I2C_MMIS_RXFFMIS        0x00000800  // Receive FIFO Full Interrupt Mask
#define I2C_MMIS_TXFEMIS        0x00000400  // Transmit FIFO Empty Interrupt
// Mask
#define I2C_MMIS_RXMIS          0x00000200  // Receive FIFO Request Interrupt
// Mask
#define I2C_MMIS_TXMIS          0x00000100  // Transmit Request Interrupt Mask
#define I2C_MMIS_ARBLOSTMIS     0x00000080  // Arbitration Lost Interrupt Mask
#define I2C_MMIS_STOPMIS        0x00000040  // STOP Detection Interrupt Mask
#define I2C_MMIS_STARTMIS       0x00000020  // START Detection Interrupt Mask
#define I2C_MMIS_NACKMIS        0x00000010  // Address/Data NACK Interrupt Mask
#define I2C_MMIS_DMATXMIS       0x00000008  // Transmit DMA Interrupt Status
#define I2C_MMIS_DMARXMIS       0x00000004  // Receive DMA Interrupt Status
#define I2C_MMIS_CLKMIS         0x00000002  // Clock Timeout Masked Interrupt
// Status
#define I2C_MMIS_MIS            0x00000001  // Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MICR register.
//
//*****************************************************************************
#define I2C_MICR_RXFFIC         0x00000800  // Receive FIFO Full Interrupt
// Clear
#define I2C_MICR_TXFEIC         0x00000400  // Transmit FIFO Empty Interrupt
// Clear
#define I2C_MICR_RXIC           0x00000200  // Receive FIFO Request Interrupt
// Clear
#define I2C_MICR_TXIC           0x00000100  // Transmit FIFO Request Interrupt
// Clear
#define I2C_MICR_ARBLOSTIC      0x00000080  // Arbitration Lost Interrupt Clear
#define I2C_MICR_STOPIC         0x00000040  // STOP Detection Interrupt Clear
#define I2C_MICR_STARTIC        0x00000020  // START Detection Interrupt Clear
#define I2C_MICR_NACKIC         0x00000010  // Address/Data NACK Interrupt
// Clear
#define I2C_MICR_DMATXIC        0x00000008  // Transmit DMA Interrupt Clear
#define I2C_MICR_DMARXIC        0x00000004  // Receive DMA Interrupt Clear
#define I2C_MICR_CLKIC          0x00000002  // Clock Timeout Interrupt Clear
#define I2C_MICR_IC             0x00000001  // Master Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCR register.
//
//*****************************************************************************
#define I2C_MCR_SFE             0x00000020  // I2C Slave Function Enable
#define I2C_MCR_MFE             0x00000010  // I2C Master Function Enable
#define I2C_MCR_LPBK            0x00000001  // I2C Loopback

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCLKOCNT register.
//
//*****************************************************************************
#define I2C_MCLKOCNT_CNTL_M     0x000000FF  // I2C Master Count
#define I2C_MCLKOCNT_CNTL_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MBMON register.
//
//*****************************************************************************
#define I2C_MBMON_SDA           0x00000002  // I2C SDA Status
#define I2C_MBMON_SCL           0x00000001  // I2C SCL Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MBLEN register.
//
//*****************************************************************************
#define I2C_MBLEN_CNTL_M        0x000000FF  // I2C Burst Length
#define I2C_MBLEN_CNTL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MBCNT register.
//
//*****************************************************************************
#define I2C_MBCNT_CNTL_M        0x000000FF  // I2C Master Burst Count
#define I2C_MBCNT_CNTL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SOAR register.
//
//*****************************************************************************
#define I2C_SOAR_OAR_M          0x0000007F  // I2C Slave Own Address
#define I2C_SOAR_OAR_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SCSR register.
//
//*****************************************************************************
#define I2C_SCSR_ACTDMARX       0x80000000  // DMA RX Active Status
#define I2C_SCSR_ACTDMATX       0x40000000  // DMA TX Active Status
#define I2C_SCSR_QCMDRW         0x00000020  // Quick Command Read / Write
#define I2C_SCSR_QCMDST         0x00000010  // Quick Command Status
#define I2C_SCSR_OAR2SEL        0x00000008  // OAR2 Address Matched
#define I2C_SCSR_FBR            0x00000004  // First Byte Received
#define I2C_SCSR_RXFIFO         0x00000004  // RX FIFO Enable
#define I2C_SCSR_TXFIFO         0x00000002  // TX FIFO Enable
#define I2C_SCSR_TREQ           0x00000002  // Transmit Request
#define I2C_SCSR_DA             0x00000001  // Device Active
#define I2C_SCSR_RREQ           0x00000001  // Receive Request

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SDR register.
//
//*****************************************************************************
#define I2C_SDR_DATA_M          0x000000FF  // Data for Transfer
#define I2C_SDR_DATA_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SIMR register.
//
//*****************************************************************************
#define I2C_SIMR_RXFFIM         0x00000100  // Receive FIFO Full Interrupt Mask
#define I2C_SIMR_TXFEIM         0x00000080  // Transmit FIFO Empty Interrupt
// Mask
#define I2C_SIMR_RXIM           0x00000040  // Receive FIFO Request Interrupt
// Mask
#define I2C_SIMR_TXIM           0x00000020  // Transmit FIFO Request Interrupt
// Mask
#define I2C_SIMR_DMATXIM        0x00000010  // Transmit DMA Interrupt Mask
#define I2C_SIMR_DMARXIM        0x00000008  // Receive DMA Interrupt Mask
#define I2C_SIMR_STOPIM         0x00000004  // Stop Condition Interrupt Mask
#define I2C_SIMR_STARTIM        0x00000002  // Start Condition Interrupt Mask
#define I2C_SIMR_DATAIM         0x00000001  // Data Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SRIS register.
//
//*****************************************************************************
#define I2C_SRIS_RXFFRIS        0x00000100  // Receive FIFO Full Raw Interrupt
// Status
#define I2C_SRIS_TXFERIS        0x00000080  // Transmit FIFO Empty Raw
// Interrupt Status
#define I2C_SRIS_RXRIS          0x00000040  // Receive FIFO Request Raw
// Interrupt Status
#define I2C_SRIS_TXRIS          0x00000020  // Transmit Request Raw Interrupt
// Status
#define I2C_SRIS_DMATXRIS       0x00000010  // Transmit DMA Raw Interrupt
// Status
#define I2C_SRIS_DMARXRIS       0x00000008  // Receive DMA Raw Interrupt Status
#define I2C_SRIS_STOPRIS        0x00000004  // Stop Condition Raw Interrupt
// Status
#define I2C_SRIS_STARTRIS       0x00000002  // Start Condition Raw Interrupt
// Status
#define I2C_SRIS_DATARIS        0x00000001  // Data Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SMIS register.
//
//*****************************************************************************
#define I2C_SMIS_RXFFMIS        0x00000100  // Receive FIFO Full Interrupt Mask
#define I2C_SMIS_TXFEMIS        0x00000080  // Transmit FIFO Empty Interrupt
// Mask
#define I2C_SMIS_RXMIS          0x00000040  // Receive FIFO Request Interrupt
// Mask
#define I2C_SMIS_TXMIS          0x00000020  // Transmit FIFO Request Interrupt
// Mask
#define I2C_SMIS_DMATXMIS       0x00000010  // Transmit DMA Masked Interrupt
// Status
#define I2C_SMIS_DMARXMIS       0x00000008  // Receive DMA Masked Interrupt
// Status
#define I2C_SMIS_STOPMIS        0x00000004  // Stop Condition Masked Interrupt
// Status
#define I2C_SMIS_STARTMIS       0x00000002  // Start Condition Masked Interrupt
// Status
#define I2C_SMIS_DATAMIS        0x00000001  // Data Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SICR register.
//
//*****************************************************************************
#define I2C_SICR_RXFFIC         0x00000100  // Receive FIFO Full Interrupt Mask
#define I2C_SICR_TXFEIC         0x00000080  // Transmit FIFO Empty Interrupt
// Mask
#define I2C_SICR_RXIC           0x00000040  // Receive Request Interrupt Mask
#define I2C_SICR_TXIC           0x00000020  // Transmit Request Interrupt Mask
#define I2C_SICR_DMATXIC        0x00000010  // Transmit DMA Interrupt Clear
#define I2C_SICR_DMARXIC        0x00000008  // Receive DMA Interrupt Clear
#define I2C_SICR_STOPIC         0x00000004  // Stop Condition Interrupt Clear
#define I2C_SICR_STARTIC        0x00000002  // Start Condition Interrupt Clear
#define I2C_SICR_DATAIC         0x00000001  // Data Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SOAR2 register.
//
//*****************************************************************************
#define I2C_SOAR2_OAR2EN        0x00000080  // I2C Slave Own Address 2 Enable
#define I2C_SOAR2_OAR2_M        0x0000007F  // I2C Slave Own Address 2
#define I2C_SOAR2_OAR2_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SACKCTL register.
//
//*****************************************************************************
#define I2C_SACKCTL_ACKOVAL     0x00000002  // I2C Slave ACK Override Value
#define I2C_SACKCTL_ACKOEN      0x00000001  // I2C Slave ACK Override Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_FIFODATA register.
//
//*****************************************************************************
#define I2C_FIFODATA_DATA_M     0x000000FF  // I2C TX FIFO Write Data Byte
#define I2C_FIFODATA_DATA_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_FIFOCTL register.
//
//*****************************************************************************
#define I2C_FIFOCTL_RXASGNMT    0x80000000  // RX Control Assignment
#define I2C_FIFOCTL_RXFLUSH     0x40000000  // RX FIFO Flush
#define I2C_FIFOCTL_DMARXENA    0x20000000  // DMA RX Channel Enable
#define I2C_FIFOCTL_RXTRIG_M    0x00070000  // RX FIFO Trigger
#define I2C_FIFOCTL_TXASGNMT    0x00008000  // TX Control Assignment
#define I2C_FIFOCTL_TXFLUSH     0x00004000  // TX FIFO Flush
#define I2C_FIFOCTL_DMATXENA    0x00002000  // DMA TX Channel Enable
#define I2C_FIFOCTL_TXTRIG_M    0x00000007  // TX FIFO Trigger
#define I2C_FIFOCTL_RXTRIG_S    16
#define I2C_FIFOCTL_TXTRIG_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_FIFOSTATUS
// register.
//
//*****************************************************************************
#define I2C_FIFOSTATUS_RXABVTRIG                                              \
                                0x00040000  // RX FIFO Above Trigger Level
#define I2C_FIFOSTATUS_RXFF     0x00020000  // RX FIFO Full
#define I2C_FIFOSTATUS_RXFE     0x00010000  // RX FIFO Empty
#define I2C_FIFOSTATUS_TXBLWTRIG                                              \
                                0x00000004  // TX FIFO Below Trigger Level
#define I2C_FIFOSTATUS_TXFF     0x00000002  // TX FIFO Full
#define I2C_FIFOSTATUS_TXFE     0x00000001  // TX FIFO Empty

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_PP register.
//
//*****************************************************************************
#define I2C_PP_HS               0x00000001  // High-Speed Capable

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_PC register.
//
//*****************************************************************************
#define I2C_PC_HS               0x00000001  // High-Speed Capable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_CTL register.
//
//*****************************************************************************
#define PWM_CTL_GLOBALSYNC3     0x00000008  // Update PWM Generator 3
#define PWM_CTL_GLOBALSYNC2     0x00000004  // Update PWM Generator 2
#define PWM_CTL_GLOBALSYNC1     0x00000002  // Update PWM Generator 1
#define PWM_CTL_GLOBALSYNC0     0x00000001  // Update PWM Generator 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_SYNC register.
//
//*****************************************************************************
#define PWM_SYNC_SYNC3          0x00000008  // Reset Generator 3 Counter
#define PWM_SYNC_SYNC2          0x00000004  // Reset Generator 2 Counter
#define PWM_SYNC_SYNC1          0x00000002  // Reset Generator 1 Counter
#define PWM_SYNC_SYNC0          0x00000001  // Reset Generator 0 Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_ENABLE register.
//
//*****************************************************************************
#define PWM_ENABLE_PWM7EN       0x00000080  // MnPWM7 Output Enable
#define PWM_ENABLE_PWM6EN       0x00000040  // MnPWM6 Output Enable
#define PWM_ENABLE_PWM5EN       0x00000020  // MnPWM5 Output Enable
#define PWM_ENABLE_PWM4EN       0x00000010  // MnPWM4 Output Enable
#define PWM_ENABLE_PWM3EN       0x00000008  // MnPWM3 Output Enable
#define PWM_ENABLE_PWM2EN       0x00000004  // MnPWM2 Output Enable
#define PWM_ENABLE_PWM1EN       0x00000002  // MnPWM1 Output Enable
#define PWM_ENABLE_PWM0EN       0x00000001  // MnPWM0 Output Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_INVERT register.
//
//*****************************************************************************
#define PWM_INVERT_PWM7INV      0x00000080  // Invert MnPWM7 Signal
#define PWM_INVERT_PWM6INV      0x00000040  // Invert MnPWM6 Signal
#define PWM_INVERT_PWM5INV      0x00000020  // Invert MnPWM5 Signal
#define PWM_INVERT_PWM4INV      0x00000010  // Invert MnPWM4 Signal
#define PWM_INVERT_PWM3INV      0x00000008  // Invert MnPWM3 Signal
#define PWM_INVERT_PWM2INV      0x00000004  // Invert MnPWM2 Signal
#define PWM_INVERT_PWM1INV      0x00000002  // Invert MnPWM1 Signal
#define PWM_INVERT_PWM0INV      0x00000001  // Invert MnPWM0 Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_FAULT register.
//
//*****************************************************************************
#define PWM_FAULT_FAULT7        0x00000080  // MnPWM7 Fault
#define PWM_FAULT_FAULT6        0x00000040  // MnPWM6 Fault
#define PWM_FAULT_FAULT5        0x00000020  // MnPWM5 Fault
#define PWM_FAULT_FAULT4        0x00000010  // MnPWM4 Fault
#define PWM_FAULT_FAULT3        0x00000008  // MnPWM3 Fault
#define PWM_FAULT_FAULT2        0x00000004  // MnPWM2 Fault
#define PWM_FAULT_FAULT1        0x00000002  // MnPWM1 Fault
#define PWM_FAULT_FAULT0        0x00000001  // MnPWM0 Fault

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_INTEN register.
//
//*****************************************************************************
#define PWM_INTEN_INTFAULT3     0x00080000  // Interrupt Fault 3
#define PWM_INTEN_INTFAULT2     0x00040000  // Interrupt Fault 2
#define PWM_INTEN_INTFAULT1     0x00020000  // Interrupt Fault 1
#define PWM_INTEN_INTFAULT0     0x00010000  // Interrupt Fault 0
#define PWM_INTEN_INTPWM3       0x00000008  // PWM3 Interrupt Enable
#define PWM_INTEN_INTPWM2       0x00000004  // PWM2 Interrupt Enable
#define PWM_INTEN_INTPWM1       0x00000002  // PWM1 Interrupt Enable
#define PWM_INTEN_INTPWM0       0x00000001  // PWM0 Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_RIS register.
//
//*****************************************************************************
#define PWM_RIS_INTFAULT3       0x00080000  // Interrupt Fault PWM 3
#define PWM_RIS_INTFAULT2       0x00040000  // Interrupt Fault PWM 2
#define PWM_RIS_INTFAULT1       0x00020000  // Interrupt Fault PWM 1
#define PWM_RIS_INTFAULT0       0x00010000  // Interrupt Fault PWM 0
#define PWM_RIS_INTPWM3         0x00000008  // PWM3 Interrupt Asserted
#define PWM_RIS_INTPWM2         0x00000004  // PWM2 Interrupt Asserted
#define PWM_RIS_INTPWM1         0x00000002  // PWM1 Interrupt Asserted
#define PWM_RIS_INTPWM0         0x00000001  // PWM0 Interrupt Asserted

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_ISC register.
//
//*****************************************************************************
#define PWM_ISC_INTFAULT3       0x00080000  // FAULT3 Interrupt Asserted
#define PWM_ISC_INTFAULT2       0x00040000  // FAULT2 Interrupt Asserted
#define PWM_ISC_INTFAULT1       0x00020000  // FAULT1 Interrupt Asserted
#define PWM_ISC_INTFAULT0       0x00010000  // FAULT0 Interrupt Asserted
#define PWM_ISC_INTPWM3         0x00000008  // PWM3 Interrupt Status
#define PWM_ISC_INTPWM2         0x00000004  // PWM2 Interrupt Status
#define PWM_ISC_INTPWM1         0x00000002  // PWM1 Interrupt Status
#define PWM_ISC_INTPWM0         0x00000001  // PWM0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_STATUS register.
//
//*****************************************************************************
#define PWM_STATUS_FAULT3       0x00000008  // Generator 3 Fault Status
#define PWM_STATUS_FAULT2       0x00000004  // Generator 2 Fault Status
#define PWM_STATUS_FAULT1       0x00000002  // Generator 1 Fault Status
#define PWM_STATUS_FAULT0       0x00000001  // Generator 0 Fault Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_FAULTVAL register.
//
//*****************************************************************************
#define PWM_FAULTVAL_PWM7       0x00000080  // MnPWM7 Fault Value
#define PWM_FAULTVAL_PWM6       0x00000040  // MnPWM6 Fault Value
#define PWM_FAULTVAL_PWM5       0x00000020  // MnPWM5 Fault Value
#define PWM_FAULTVAL_PWM4       0x00000010  // MnPWM4 Fault Value
#define PWM_FAULTVAL_PWM3       0x00000008  // MnPWM3 Fault Value
#define PWM_FAULTVAL_PWM2       0x00000004  // MnPWM2 Fault Value
#define PWM_FAULTVAL_PWM1       0x00000002  // MnPWM1 Fault Value
#define PWM_FAULTVAL_PWM0       0x00000001  // MnPWM0 Fault Value

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_ENUPD register.
//
//*****************************************************************************
#define PWM_ENUPD_ENUPD7_M      0x0000C000  // MnPWM7 Enable Update Mode
#define PWM_ENUPD_ENUPD7_IMM    0x00000000  // Immediate
#define PWM_ENUPD_ENUPD7_LSYNC  0x00008000  // Locally Synchronized
#define PWM_ENUPD_ENUPD7_GSYNC  0x0000C000  // Globally Synchronized
#define PWM_ENUPD_ENUPD6_M      0x00003000  // MnPWM6 Enable Update Mode
#define PWM_ENUPD_ENUPD6_IMM    0x00000000  // Immediate
#define PWM_ENUPD_ENUPD6_LSYNC  0x00002000  // Locally Synchronized
#define PWM_ENUPD_ENUPD6_GSYNC  0x00003000  // Globally Synchronized
#define PWM_ENUPD_ENUPD5_M      0x00000C00  // MnPWM5 Enable Update Mode
#define PWM_ENUPD_ENUPD5_IMM    0x00000000  // Immediate
#define PWM_ENUPD_ENUPD5_LSYNC  0x00000800  // Locally Synchronized
#define PWM_ENUPD_ENUPD5_GSYNC  0x00000C00  // Globally Synchronized
#define PWM_ENUPD_ENUPD4_M      0x00000300  // MnPWM4 Enable Update Mode
#define PWM_ENUPD_ENUPD4_IMM    0x00000000  // Immediate
#define PWM_ENUPD_ENUPD4_LSYNC  0x00000200  // Locally Synchronized
#define PWM_ENUPD_ENUPD4_GSYNC  0x00000300  // Globally Synchronized
#define PWM_ENUPD_ENUPD3_M      0x000000C0  // MnPWM3 Enable Update Mode
#define PWM_ENUPD_ENUPD3_IMM    0x00000000  // Immediate
#define PWM_ENUPD_ENUPD3_LSYNC  0x00000080  // Locally Synchronized
#define PWM_ENUPD_ENUPD3_GSYNC  0x000000C0  // Globally Synchronized
#define PWM_ENUPD_ENUPD2_M      0x00000030  // MnPWM2 Enable Update Mode
#define PWM_ENUPD_ENUPD2_IMM    0x00000000  // Immediate
#define PWM_ENUPD_ENUPD2_LSYNC  0x00000020  // Locally Synchronized
#define PWM_ENUPD_ENUPD2_GSYNC  0x00000030  // Globally Synchronized
#define PWM_ENUPD_ENUPD1_M      0x0000000C  // MnPWM1 Enable Update Mode
#define PWM_ENUPD_ENUPD1_IMM    0x00000000  // Immediate
#define PWM_ENUPD_ENUPD1_LSYNC  0x00000008  // Locally Synchronized
#define PWM_ENUPD_ENUPD1_GSYNC  0x0000000C  // Globally Synchronized
#define PWM_ENUPD_ENUPD0_M      0x00000003  // MnPWM0 Enable Update Mode
#define PWM_ENUPD_ENUPD0_IMM    0x00000000  // Immediate
#define PWM_ENUPD_ENUPD0_LSYNC  0x00000002  // Locally Synchronized
#define PWM_ENUPD_ENUPD0_GSYNC  0x00000003  // Globally Synchronized

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_CTL register.
//
//*****************************************************************************
#define PWM_0_CTL_LATCH         0x00040000  // Latch Fault Input
#define PWM_0_CTL_MINFLTPER     0x00020000  // Minimum Fault Period
#define PWM_0_CTL_FLTSRC        0x00010000  // Fault Condition Source
#define PWM_0_CTL_DBFALLUPD_M   0x0000C000  // PWMnDBFALL Update Mode
#define PWM_0_CTL_DBFALLUPD_I   0x00000000  // Immediate
#define PWM_0_CTL_DBFALLUPD_LS  0x00008000  // Locally Synchronized
#define PWM_0_CTL_DBFALLUPD_GS  0x0000C000  // Globally Synchronized
#define PWM_0_CTL_DBRISEUPD_M   0x00003000  // PWMnDBRISE Update Mode
#define PWM_0_CTL_DBRISEUPD_I   0x00000000  // Immediate
#define PWM_0_CTL_DBRISEUPD_LS  0x00002000  // Locally Synchronized
#define PWM_0_CTL_DBRISEUPD_GS  0x00003000  // Globally Synchronized
#define PWM_0_CTL_DBCTLUPD_M    0x00000C00  // PWMnDBCTL Update Mode
#define PWM_0_CTL_DBCTLUPD_I    0x00000000  // Immediate
#define PWM_0_CTL_DBCTLUPD_LS   0x00000800  // Locally Synchronized
#define PWM_0_CTL_DBCTLUPD_GS   0x00000C00  // Globally Synchronized
#define PWM_0_CTL_GENBUPD_M     0x00000300  // PWMnGENB Update Mode
#define PWM_0_CTL_GENBUPD_I     0x00000000  // Immediate
#define PWM_0_CTL_GENBUPD_LS    0x00000200  // Locally Synchronized
#define PWM_0_CTL_GENBUPD_GS    0x00000300  // Globally Synchronized
#define PWM_0_CTL_GENAUPD_M     0x000000C0  // PWMnGENA Update Mode
#define PWM_0_CTL_GENAUPD_I     0x00000000  // Immediate
#define PWM_0_CTL_GENAUPD_LS    0x00000080  // Locally Synchronized
#define PWM_0_CTL_GENAUPD_GS    0x000000C0  // Globally Synchronized
#define PWM_0_CTL_CMPBUPD       0x00000020  // Comparator B Update Mode
#define PWM_0_CTL_CMPAUPD       0x00000010  // Comparator A Update Mode
#define PWM_0_CTL_LOADUPD       0x00000008  // Load Register Update Mode
#define PWM_0_CTL_DEBUG         0x00000004  // Debug Mode
#define PWM_0_CTL_MODE          0x00000002  // Counter Mode
#define PWM_0_CTL_ENABLE        0x00000001  // PWM Block Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_INTEN register.
//
//*****************************************************************************
#define PWM_0_INTEN_TRCMPBD     0x00002000  // Trigger for Counter=PWMnCMPB
// Down
#define PWM_0_INTEN_TRCMPBU     0x00001000  // Trigger for Counter=PWMnCMPB Up
#define PWM_0_INTEN_TRCMPAD     0x00000800  // Trigger for Counter=PWMnCMPA
// Down
#define PWM_0_INTEN_TRCMPAU     0x00000400  // Trigger for Counter=PWMnCMPA Up
#define PWM_0_INTEN_TRCNTLOAD   0x00000200  // Trigger for Counter=PWMnLOAD
#define PWM_0_INTEN_TRCNTZERO   0x00000100  // Trigger for Counter=0
#define PWM_0_INTEN_INTCMPBD    0x00000020  // Interrupt for Counter=PWMnCMPB
// Down
#define PWM_0_INTEN_INTCMPBU    0x00000010  // Interrupt for Counter=PWMnCMPB
// Up
#define PWM_0_INTEN_INTCMPAD    0x00000008  // Interrupt for Counter=PWMnCMPA
// Down
#define PWM_0_INTEN_INTCMPAU    0x00000004  // Interrupt for Counter=PWMnCMPA
// Up
#define PWM_0_INTEN_INTCNTLOAD  0x00000002  // Interrupt for Counter=PWMnLOAD
#define PWM_0_INTEN_INTCNTZERO  0x00000001  // Interrupt for Counter=0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_RIS register.
//
//*****************************************************************************
#define PWM_0_RIS_INTCMPBD      0x00000020  // Comparator B Down Interrupt
// Status
#define PWM_0_RIS_INTCMPBU      0x00000010  // Comparator B Up Interrupt Status
#define PWM_0_RIS_INTCMPAD      0x00000008  // Comparator A Down Interrupt
// Status
#define PWM_0_RIS_INTCMPAU      0x00000004  // Comparator A Up Interrupt Status
#define PWM_0_RIS_INTCNTLOAD    0x00000002  // Counter=Load Interrupt Status
#define PWM_0_RIS_INTCNTZERO    0x00000001  // Counter=0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_ISC register.
//
//*****************************************************************************
#define PWM_0_ISC_INTCMPBD      0x00000020  // Comparator B Down Interrupt
#define PWM_0_ISC_INTCMPBU      0x00000010  // Comparator B Up Interrupt
#define PWM_0_ISC_INTCMPAD      0x00000008  // Comparator A Down Interrupt
#define PWM_0_ISC_INTCMPAU      0x00000004  // Comparator A Up Interrupt
#define PWM_0_ISC_INTCNTLOAD    0x00000002  // Counter=Load Interrupt
#define PWM_0_ISC_INTCNTZERO    0x00000001  // Counter=0 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_LOAD register.
//
//*****************************************************************************
#define PWM_0_LOAD_M            0x0000FFFF  // Counter Load Value
#define PWM_0_LOAD_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_COUNT register.
//
//*****************************************************************************
#define PWM_0_COUNT_M           0x0000FFFF  // Counter Value
#define PWM_0_COUNT_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_CMPA register.
//
//*****************************************************************************
#define PWM_0_CMPA_M            0x0000FFFF  // Comparator A Value
#define PWM_0_CMPA_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_CMPB register.
//
//*****************************************************************************
#define PWM_0_CMPB_M            0x0000FFFF  // Comparator B Value
#define PWM_0_CMPB_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_GENA register.
//
//*****************************************************************************
#define PWM_0_GENA_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_0_GENA_ACTCMPBD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_0_GENA_ACTCMPBD_INV 0x00000400  // Invert pwmA
#define PWM_0_GENA_ACTCMPBD_ZERO                                              \
                                0x00000800  // Drive pwmA Low
#define PWM_0_GENA_ACTCMPBD_ONE 0x00000C00  // Drive pwmA High
#define PWM_0_GENA_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_0_GENA_ACTCMPBU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_0_GENA_ACTCMPBU_INV 0x00000100  // Invert pwmA
#define PWM_0_GENA_ACTCMPBU_ZERO                                              \
                                0x00000200  // Drive pwmA Low
#define PWM_0_GENA_ACTCMPBU_ONE 0x00000300  // Drive pwmA High
#define PWM_0_GENA_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_0_GENA_ACTCMPAD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_0_GENA_ACTCMPAD_INV 0x00000040  // Invert pwmA
#define PWM_0_GENA_ACTCMPAD_ZERO                                              \
                                0x00000080  // Drive pwmA Low
#define PWM_0_GENA_ACTCMPAD_ONE 0x000000C0  // Drive pwmA High
#define PWM_0_GENA_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_0_GENA_ACTCMPAU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_0_GENA_ACTCMPAU_INV 0x00000010  // Invert pwmA
#define PWM_0_GENA_ACTCMPAU_ZERO                                              \
                                0x00000020  // Drive pwmA Low
#define PWM_0_GENA_ACTCMPAU_ONE 0x00000030  // Drive pwmA High
#define PWM_0_GENA_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_0_GENA_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_0_GENA_ACTLOAD_INV  0x00000004  // Invert pwmA
#define PWM_0_GENA_ACTLOAD_ZERO 0x00000008  // Drive pwmA Low
#define PWM_0_GENA_ACTLOAD_ONE  0x0000000C  // Drive pwmA High
#define PWM_0_GENA_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_0_GENA_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_0_GENA_ACTZERO_INV  0x00000001  // Invert pwmA
#define PWM_0_GENA_ACTZERO_ZERO 0x00000002  // Drive pwmA Low
#define PWM_0_GENA_ACTZERO_ONE  0x00000003  // Drive pwmA High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_GENB register.
//
//*****************************************************************************
#define PWM_0_GENB_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_0_GENB_ACTCMPBD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_0_GENB_ACTCMPBD_INV 0x00000400  // Invert pwmB
#define PWM_0_GENB_ACTCMPBD_ZERO                                              \
                                0x00000800  // Drive pwmB Low
#define PWM_0_GENB_ACTCMPBD_ONE 0x00000C00  // Drive pwmB High
#define PWM_0_GENB_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_0_GENB_ACTCMPBU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_0_GENB_ACTCMPBU_INV 0x00000100  // Invert pwmB
#define PWM_0_GENB_ACTCMPBU_ZERO                                              \
                                0x00000200  // Drive pwmB Low
#define PWM_0_GENB_ACTCMPBU_ONE 0x00000300  // Drive pwmB High
#define PWM_0_GENB_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_0_GENB_ACTCMPAD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_0_GENB_ACTCMPAD_INV 0x00000040  // Invert pwmB
#define PWM_0_GENB_ACTCMPAD_ZERO                                              \
                                0x00000080  // Drive pwmB Low
#define PWM_0_GENB_ACTCMPAD_ONE 0x000000C0  // Drive pwmB High
#define PWM_0_GENB_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_0_GENB_ACTCMPAU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_0_GENB_ACTCMPAU_INV 0x00000010  // Invert pwmB
#define PWM_0_GENB_ACTCMPAU_ZERO                                              \
                                0x00000020  // Drive pwmB Low
#define PWM_0_GENB_ACTCMPAU_ONE 0x00000030  // Drive pwmB High
#define PWM_0_GENB_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_0_GENB_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_0_GENB_ACTLOAD_INV  0x00000004  // Invert pwmB
#define PWM_0_GENB_ACTLOAD_ZERO 0x00000008  // Drive pwmB Low
#define PWM_0_GENB_ACTLOAD_ONE  0x0000000C  // Drive pwmB High
#define PWM_0_GENB_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_0_GENB_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_0_GENB_ACTZERO_INV  0x00000001  // Invert pwmB
#define PWM_0_GENB_ACTZERO_ZERO 0x00000002  // Drive pwmB Low
#define PWM_0_GENB_ACTZERO_ONE  0x00000003  // Drive pwmB High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_DBCTL register.
//
//*****************************************************************************
#define PWM_0_DBCTL_ENABLE      0x00000001  // Dead-Band Generator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_DBRISE register.
//
//*****************************************************************************
#define PWM_0_DBRISE_DELAY_M    0x00000FFF  // Dead-Band Rise Delay
#define PWM_0_DBRISE_DELAY_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_DBFALL register.
//
//*****************************************************************************
#define PWM_0_DBFALL_DELAY_M    0x00000FFF  // Dead-Band Fall Delay
#define PWM_0_DBFALL_DELAY_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_FLTSRC0
// register.
//
//*****************************************************************************
#define PWM_0_FLTSRC0_FAULT3    0x00000008  // Fault3 Input
#define PWM_0_FLTSRC0_FAULT2    0x00000004  // Fault2 Input
#define PWM_0_FLTSRC0_FAULT1    0x00000002  // Fault1 Input
#define PWM_0_FLTSRC0_FAULT0    0x00000001  // Fault0 Input

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_FLTSRC1
// register.
//
//*****************************************************************************
#define PWM_0_FLTSRC1_DCMP7     0x00000080  // Digital Comparator 7
#define PWM_0_FLTSRC1_DCMP6     0x00000040  // Digital Comparator 6
#define PWM_0_FLTSRC1_DCMP5     0x00000020  // Digital Comparator 5
#define PWM_0_FLTSRC1_DCMP4     0x00000010  // Digital Comparator 4
#define PWM_0_FLTSRC1_DCMP3     0x00000008  // Digital Comparator 3
#define PWM_0_FLTSRC1_DCMP2     0x00000004  // Digital Comparator 2
#define PWM_0_FLTSRC1_DCMP1     0x00000002  // Digital Comparator 1
#define PWM_0_FLTSRC1_DCMP0     0x00000001  // Digital Comparator 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_MINFLTPER
// register.
//
//*****************************************************************************
#define PWM_0_MINFLTPER_M       0x0000FFFF  // Minimum Fault Period
#define PWM_0_MINFLTPER_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_CTL register.
//
//*****************************************************************************
#define PWM_1_CTL_LATCH         0x00040000  // Latch Fault Input
#define PWM_1_CTL_MINFLTPER     0x00020000  // Minimum Fault Period
#define PWM_1_CTL_FLTSRC        0x00010000  // Fault Condition Source
#define PWM_1_CTL_DBFALLUPD_M   0x0000C000  // PWMnDBFALL Update Mode
#define PWM_1_CTL_DBFALLUPD_I   0x00000000  // Immediate
#define PWM_1_CTL_DBFALLUPD_LS  0x00008000  // Locally Synchronized
#define PWM_1_CTL_DBFALLUPD_GS  0x0000C000  // Globally Synchronized
#define PWM_1_CTL_DBRISEUPD_M   0x00003000  // PWMnDBRISE Update Mode
#define PWM_1_CTL_DBRISEUPD_I   0x00000000  // Immediate
#define PWM_1_CTL_DBRISEUPD_LS  0x00002000  // Locally Synchronized
#define PWM_1_CTL_DBRISEUPD_GS  0x00003000  // Globally Synchronized
#define PWM_1_CTL_DBCTLUPD_M    0x00000C00  // PWMnDBCTL Update Mode
#define PWM_1_CTL_DBCTLUPD_I    0x00000000  // Immediate
#define PWM_1_CTL_DBCTLUPD_LS   0x00000800  // Locally Synchronized
#define PWM_1_CTL_DBCTLUPD_GS   0x00000C00  // Globally Synchronized
#define PWM_1_CTL_GENBUPD_M     0x00000300  // PWMnGENB Update Mode
#define PWM_1_CTL_GENBUPD_I     0x00000000  // Immediate
#define PWM_1_CTL_GENBUPD_LS    0x00000200  // Locally Synchronized
#define PWM_1_CTL_GENBUPD_GS    0x00000300  // Globally Synchronized
#define PWM_1_CTL_GENAUPD_M     0x000000C0  // PWMnGENA Update Mode
#define PWM_1_CTL_GENAUPD_I     0x00000000  // Immediate
#define PWM_1_CTL_GENAUPD_LS    0x00000080  // Locally Synchronized
#define PWM_1_CTL_GENAUPD_GS    0x000000C0  // Globally Synchronized
#define PWM_1_CTL_CMPBUPD       0x00000020  // Comparator B Update Mode
#define PWM_1_CTL_CMPAUPD       0x00000010  // Comparator A Update Mode
#define PWM_1_CTL_LOADUPD       0x00000008  // Load Register Update Mode
#define PWM_1_CTL_DEBUG         0x00000004  // Debug Mode
#define PWM_1_CTL_MODE          0x00000002  // Counter Mode
#define PWM_1_CTL_ENABLE        0x00000001  // PWM Block Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_INTEN register.
//
//*****************************************************************************
#define PWM_1_INTEN_TRCMPBD     0x00002000  // Trigger for Counter=PWMnCMPB
// Down
#define PWM_1_INTEN_TRCMPBU     0x00001000  // Trigger for Counter=PWMnCMPB Up
#define PWM_1_INTEN_TRCMPAD     0x00000800  // Trigger for Counter=PWMnCMPA
// Down
#define PWM_1_INTEN_TRCMPAU     0x00000400  // Trigger for Counter=PWMnCMPA Up
#define PWM_1_INTEN_TRCNTLOAD   0x00000200  // Trigger for Counter=PWMnLOAD
#define PWM_1_INTEN_TRCNTZERO   0x00000100  // Trigger for Counter=0
#define PWM_1_INTEN_INTCMPBD    0x00000020  // Interrupt for Counter=PWMnCMPB
// Down
#define PWM_1_INTEN_INTCMPBU    0x00000010  // Interrupt for Counter=PWMnCMPB
// Up
#define PWM_1_INTEN_INTCMPAD    0x00000008  // Interrupt for Counter=PWMnCMPA
// Down
#define PWM_1_INTEN_INTCMPAU    0x00000004  // Interrupt for Counter=PWMnCMPA
// Up
#define PWM_1_INTEN_INTCNTLOAD  0x00000002  // Interrupt for Counter=PWMnLOAD
#define PWM_1_INTEN_INTCNTZERO  0x00000001  // Interrupt for Counter=0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_RIS register.
//
//*****************************************************************************
#define PWM_1_RIS_INTCMPBD      0x00000020  // Comparator B Down Interrupt
// Status
#define PWM_1_RIS_INTCMPBU      0x00000010  // Comparator B Up Interrupt Status
#define PWM_1_RIS_INTCMPAD      0x00000008  // Comparator A Down Interrupt
// Status
#define PWM_1_RIS_INTCMPAU      0x00000004  // Comparator A Up Interrupt Status
#define PWM_1_RIS_INTCNTLOAD    0x00000002  // Counter=Load Interrupt Status
#define PWM_1_RIS_INTCNTZERO    0x00000001  // Counter=0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_ISC register.
//
//*****************************************************************************
#define PWM_1_ISC_INTCMPBD      0x00000020  // Comparator B Down Interrupt
#define PWM_1_ISC_INTCMPBU      0x00000010  // Comparator B Up Interrupt
#define PWM_1_ISC_INTCMPAD      0x00000008  // Comparator A Down Interrupt
#define PWM_1_ISC_INTCMPAU      0x00000004  // Comparator A Up Interrupt
#define PWM_1_ISC_INTCNTLOAD    0x00000002  // Counter=Load Interrupt
#define PWM_1_ISC_INTCNTZERO    0x00000001  // Counter=0 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_LOAD register.
//
//*****************************************************************************
#define PWM_1_LOAD_LOAD_M       0x0000FFFF  // Counter Load Value
#define PWM_1_LOAD_LOAD_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_COUNT register.
//
//*****************************************************************************
#define PWM_1_COUNT_COUNT_M     0x0000FFFF  // Counter Value
#define PWM_1_COUNT_COUNT_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_CMPA register.
//
//*****************************************************************************
#define PWM_1_CMPA_COMPA_M      0x0000FFFF  // Comparator A Value
#define PWM_1_CMPA_COMPA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_CMPB register.
//
//*****************************************************************************
#define PWM_1_CMPB_COMPB_M      0x0000FFFF  // Comparator B Value
#define PWM_1_CMPB_COMPB_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_GENA register.
//
//*****************************************************************************
#define PWM_1_GENA_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_1_GENA_ACTCMPBD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_1_GENA_ACTCMPBD_INV 0x00000400  // Invert pwmA
#define PWM_1_GENA_ACTCMPBD_ZERO                                              \
                                0x00000800  // Drive pwmA Low
#define PWM_1_GENA_ACTCMPBD_ONE 0x00000C00  // Drive pwmA High
#define PWM_1_GENA_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_1_GENA_ACTCMPBU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_1_GENA_ACTCMPBU_INV 0x00000100  // Invert pwmA
#define PWM_1_GENA_ACTCMPBU_ZERO                                              \
                                0x00000200  // Drive pwmA Low
#define PWM_1_GENA_ACTCMPBU_ONE 0x00000300  // Drive pwmA High
#define PWM_1_GENA_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_1_GENA_ACTCMPAD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_1_GENA_ACTCMPAD_INV 0x00000040  // Invert pwmA
#define PWM_1_GENA_ACTCMPAD_ZERO                                              \
                                0x00000080  // Drive pwmA Low
#define PWM_1_GENA_ACTCMPAD_ONE 0x000000C0  // Drive pwmA High
#define PWM_1_GENA_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_1_GENA_ACTCMPAU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_1_GENA_ACTCMPAU_INV 0x00000010  // Invert pwmA
#define PWM_1_GENA_ACTCMPAU_ZERO                                              \
                                0x00000020  // Drive pwmA Low
#define PWM_1_GENA_ACTCMPAU_ONE 0x00000030  // Drive pwmA High
#define PWM_1_GENA_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_1_GENA_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_1_GENA_ACTLOAD_INV  0x00000004  // Invert pwmA
#define PWM_1_GENA_ACTLOAD_ZERO 0x00000008  // Drive pwmA Low
#define PWM_1_GENA_ACTLOAD_ONE  0x0000000C  // Drive pwmA High
#define PWM_1_GENA_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_1_GENA_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_1_GENA_ACTZERO_INV  0x00000001  // Invert pwmA
#define PWM_1_GENA_ACTZERO_ZERO 0x00000002  // Drive pwmA Low
#define PWM_1_GENA_ACTZERO_ONE  0x00000003  // Drive pwmA High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_GENB register.
//
//*****************************************************************************
#define PWM_1_GENB_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_1_GENB_ACTCMPBD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_1_GENB_ACTCMPBD_INV 0x00000400  // Invert pwmB
#define PWM_1_GENB_ACTCMPBD_ZERO                                              \
                                0x00000800  // Drive pwmB Low
#define PWM_1_GENB_ACTCMPBD_ONE 0x00000C00  // Drive pwmB High
#define PWM_1_GENB_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_1_GENB_ACTCMPBU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_1_GENB_ACTCMPBU_INV 0x00000100  // Invert pwmB
#define PWM_1_GENB_ACTCMPBU_ZERO                                              \
                                0x00000200  // Drive pwmB Low
#define PWM_1_GENB_ACTCMPBU_ONE 0x00000300  // Drive pwmB High
#define PWM_1_GENB_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_1_GENB_ACTCMPAD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_1_GENB_ACTCMPAD_INV 0x00000040  // Invert pwmB
#define PWM_1_GENB_ACTCMPAD_ZERO                                              \
                                0x00000080  // Drive pwmB Low
#define PWM_1_GENB_ACTCMPAD_ONE 0x000000C0  // Drive pwmB High
#define PWM_1_GENB_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_1_GENB_ACTCMPAU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_1_GENB_ACTCMPAU_INV 0x00000010  // Invert pwmB
#define PWM_1_GENB_ACTCMPAU_ZERO                                              \
                                0x00000020  // Drive pwmB Low
#define PWM_1_GENB_ACTCMPAU_ONE 0x00000030  // Drive pwmB High
#define PWM_1_GENB_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_1_GENB_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_1_GENB_ACTLOAD_INV  0x00000004  // Invert pwmB
#define PWM_1_GENB_ACTLOAD_ZERO 0x00000008  // Drive pwmB Low
#define PWM_1_GENB_ACTLOAD_ONE  0x0000000C  // Drive pwmB High
#define PWM_1_GENB_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_1_GENB_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_1_GENB_ACTZERO_INV  0x00000001  // Invert pwmB
#define PWM_1_GENB_ACTZERO_ZERO 0x00000002  // Drive pwmB Low
#define PWM_1_GENB_ACTZERO_ONE  0x00000003  // Drive pwmB High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_DBCTL register.
//
//*****************************************************************************
#define PWM_1_DBCTL_ENABLE      0x00000001  // Dead-Band Generator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_DBRISE register.
//
//*****************************************************************************
#define PWM_1_DBRISE_RISEDELAY_M                                              \
                                0x00000FFF  // Dead-Band Rise Delay
#define PWM_1_DBRISE_RISEDELAY_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_DBFALL register.
//
//*****************************************************************************
#define PWM_1_DBFALL_FALLDELAY_M                                              \
                                0x00000FFF  // Dead-Band Fall Delay
#define PWM_1_DBFALL_FALLDELAY_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_FLTSRC0
// register.
//
//*****************************************************************************
#define PWM_1_FLTSRC0_FAULT3    0x00000008  // Fault3 Input
#define PWM_1_FLTSRC0_FAULT2    0x00000004  // Fault2 Input
#define PWM_1_FLTSRC0_FAULT1    0x00000002  // Fault1 Input
#define PWM_1_FLTSRC0_FAULT0    0x00000001  // Fault0 Input

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_FLTSRC1
// register.
//
//*****************************************************************************
#define PWM_1_FLTSRC1_DCMP7     0x00000080  // Digital Comparator 7
#define PWM_1_FLTSRC1_DCMP6     0x00000040  // Digital Comparator 6
#define PWM_1_FLTSRC1_DCMP5     0x00000020  // Digital Comparator 5
#define PWM_1_FLTSRC1_DCMP4     0x00000010  // Digital Comparator 4
#define PWM_1_FLTSRC1_DCMP3     0x00000008  // Digital Comparator 3
#define PWM_1_FLTSRC1_DCMP2     0x00000004  // Digital Comparator 2
#define PWM_1_FLTSRC1_DCMP1     0x00000002  // Digital Comparator 1
#define PWM_1_FLTSRC1_DCMP0     0x00000001  // Digital Comparator 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_MINFLTPER
// register.
//
//*****************************************************************************
#define PWM_1_MINFLTPER_MFP_M   0x0000FFFF  // Minimum Fault Period
#define PWM_1_MINFLTPER_MFP_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_CTL register.
//
//*****************************************************************************
#define PWM_2_CTL_LATCH         0x00040000  // Latch Fault Input
#define PWM_2_CTL_MINFLTPER     0x00020000  // Minimum Fault Period
#define PWM_2_CTL_FLTSRC        0x00010000  // Fault Condition Source
#define PWM_2_CTL_DBFALLUPD_M   0x0000C000  // PWMnDBFALL Update Mode
#define PWM_2_CTL_DBFALLUPD_I   0x00000000  // Immediate
#define PWM_2_CTL_DBFALLUPD_LS  0x00008000  // Locally Synchronized
#define PWM_2_CTL_DBFALLUPD_GS  0x0000C000  // Globally Synchronized
#define PWM_2_CTL_DBRISEUPD_M   0x00003000  // PWMnDBRISE Update Mode
#define PWM_2_CTL_DBRISEUPD_I   0x00000000  // Immediate
#define PWM_2_CTL_DBRISEUPD_LS  0x00002000  // Locally Synchronized
#define PWM_2_CTL_DBRISEUPD_GS  0x00003000  // Globally Synchronized
#define PWM_2_CTL_DBCTLUPD_M    0x00000C00  // PWMnDBCTL Update Mode
#define PWM_2_CTL_DBCTLUPD_I    0x00000000  // Immediate
#define PWM_2_CTL_DBCTLUPD_LS   0x00000800  // Locally Synchronized
#define PWM_2_CTL_DBCTLUPD_GS   0x00000C00  // Globally Synchronized
#define PWM_2_CTL_GENBUPD_M     0x00000300  // PWMnGENB Update Mode
#define PWM_2_CTL_GENBUPD_I     0x00000000  // Immediate
#define PWM_2_CTL_GENBUPD_LS    0x00000200  // Locally Synchronized
#define PWM_2_CTL_GENBUPD_GS    0x00000300  // Globally Synchronized
#define PWM_2_CTL_GENAUPD_M     0x000000C0  // PWMnGENA Update Mode
#define PWM_2_CTL_GENAUPD_I     0x00000000  // Immediate
#define PWM_2_CTL_GENAUPD_LS    0x00000080  // Locally Synchronized
#define PWM_2_CTL_GENAUPD_GS    0x000000C0  // Globally Synchronized
#define PWM_2_CTL_CMPBUPD       0x00000020  // Comparator B Update Mode
#define PWM_2_CTL_CMPAUPD       0x00000010  // Comparator A Update Mode
#define PWM_2_CTL_LOADUPD       0x00000008  // Load Register Update Mode
#define PWM_2_CTL_DEBUG         0x00000004  // Debug Mode
#define PWM_2_CTL_MODE          0x00000002  // Counter Mode
#define PWM_2_CTL_ENABLE        0x00000001  // PWM Block Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_INTEN register.
//
//*****************************************************************************
#define PWM_2_INTEN_TRCMPBD     0x00002000  // Trigger for Counter=PWMnCMPB
// Down
#define PWM_2_INTEN_TRCMPBU     0x00001000  // Trigger for Counter=PWMnCMPB Up
#define PWM_2_INTEN_TRCMPAD     0x00000800  // Trigger for Counter=PWMnCMPA
// Down
#define PWM_2_INTEN_TRCMPAU     0x00000400  // Trigger for Counter=PWMnCMPA Up
#define PWM_2_INTEN_TRCNTLOAD   0x00000200  // Trigger for Counter=PWMnLOAD
#define PWM_2_INTEN_TRCNTZERO   0x00000100  // Trigger for Counter=0
#define PWM_2_INTEN_INTCMPBD    0x00000020  // Interrupt for Counter=PWMnCMPB
// Down
#define PWM_2_INTEN_INTCMPBU    0x00000010  // Interrupt for Counter=PWMnCMPB
// Up
#define PWM_2_INTEN_INTCMPAD    0x00000008  // Interrupt for Counter=PWMnCMPA
// Down
#define PWM_2_INTEN_INTCMPAU    0x00000004  // Interrupt for Counter=PWMnCMPA
// Up
#define PWM_2_INTEN_INTCNTLOAD  0x00000002  // Interrupt for Counter=PWMnLOAD
#define PWM_2_INTEN_INTCNTZERO  0x00000001  // Interrupt for Counter=0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_RIS register.
//
//*****************************************************************************
#define PWM_2_RIS_INTCMPBD      0x00000020  // Comparator B Down Interrupt
// Status
#define PWM_2_RIS_INTCMPBU      0x00000010  // Comparator B Up Interrupt Status
#define PWM_2_RIS_INTCMPAD      0x00000008  // Comparator A Down Interrupt
// Status
#define PWM_2_RIS_INTCMPAU      0x00000004  // Comparator A Up Interrupt Status
#define PWM_2_RIS_INTCNTLOAD    0x00000002  // Counter=Load Interrupt Status
#define PWM_2_RIS_INTCNTZERO    0x00000001  // Counter=0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_ISC register.
//
//*****************************************************************************
#define PWM_2_ISC_INTCMPBD      0x00000020  // Comparator B Down Interrupt
#define PWM_2_ISC_INTCMPBU      0x00000010  // Comparator B Up Interrupt
#define PWM_2_ISC_INTCMPAD      0x00000008  // Comparator A Down Interrupt
#define PWM_2_ISC_INTCMPAU      0x00000004  // Comparator A Up Interrupt
#define PWM_2_ISC_INTCNTLOAD    0x00000002  // Counter=Load Interrupt
#define PWM_2_ISC_INTCNTZERO    0x00000001  // Counter=0 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_LOAD register.
//
//*****************************************************************************
#define PWM_2_LOAD_LOAD_M       0x0000FFFF  // Counter Load Value
#define PWM_2_LOAD_LOAD_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_COUNT register.
//
//*****************************************************************************
#define PWM_2_COUNT_COUNT_M     0x0000FFFF  // Counter Value
#define PWM_2_COUNT_COUNT_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_CMPA register.
//
//*****************************************************************************
#define PWM_2_CMPA_COMPA_M      0x0000FFFF  // Comparator A Value
#define PWM_2_CMPA_COMPA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_CMPB register.
//
//*****************************************************************************
#define PWM_2_CMPB_COMPB_M      0x0000FFFF  // Comparator B Value
#define PWM_2_CMPB_COMPB_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_GENA register.
//
//*****************************************************************************
#define PWM_2_GENA_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_2_GENA_ACTCMPBD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_2_GENA_ACTCMPBD_INV 0x00000400  // Invert pwmA
#define PWM_2_GENA_ACTCMPBD_ZERO                                              \
                                0x00000800  // Drive pwmA Low
#define PWM_2_GENA_ACTCMPBD_ONE 0x00000C00  // Drive pwmA High
#define PWM_2_GENA_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_2_GENA_ACTCMPBU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_2_GENA_ACTCMPBU_INV 0x00000100  // Invert pwmA
#define PWM_2_GENA_ACTCMPBU_ZERO                                              \
                                0x00000200  // Drive pwmA Low
#define PWM_2_GENA_ACTCMPBU_ONE 0x00000300  // Drive pwmA High
#define PWM_2_GENA_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_2_GENA_ACTCMPAD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_2_GENA_ACTCMPAD_INV 0x00000040  // Invert pwmA
#define PWM_2_GENA_ACTCMPAD_ZERO                                              \
                                0x00000080  // Drive pwmA Low
#define PWM_2_GENA_ACTCMPAD_ONE 0x000000C0  // Drive pwmA High
#define PWM_2_GENA_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_2_GENA_ACTCMPAU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_2_GENA_ACTCMPAU_INV 0x00000010  // Invert pwmA
#define PWM_2_GENA_ACTCMPAU_ZERO                                              \
                                0x00000020  // Drive pwmA Low
#define PWM_2_GENA_ACTCMPAU_ONE 0x00000030  // Drive pwmA High
#define PWM_2_GENA_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_2_GENA_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_2_GENA_ACTLOAD_INV  0x00000004  // Invert pwmA
#define PWM_2_GENA_ACTLOAD_ZERO 0x00000008  // Drive pwmA Low
#define PWM_2_GENA_ACTLOAD_ONE  0x0000000C  // Drive pwmA High
#define PWM_2_GENA_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_2_GENA_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_2_GENA_ACTZERO_INV  0x00000001  // Invert pwmA
#define PWM_2_GENA_ACTZERO_ZERO 0x00000002  // Drive pwmA Low
#define PWM_2_GENA_ACTZERO_ONE  0x00000003  // Drive pwmA High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_GENB register.
//
//*****************************************************************************
#define PWM_2_GENB_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_2_GENB_ACTCMPBD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_2_GENB_ACTCMPBD_INV 0x00000400  // Invert pwmB
#define PWM_2_GENB_ACTCMPBD_ZERO                                              \
                                0x00000800  // Drive pwmB Low
#define PWM_2_GENB_ACTCMPBD_ONE 0x00000C00  // Drive pwmB High
#define PWM_2_GENB_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_2_GENB_ACTCMPBU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_2_GENB_ACTCMPBU_INV 0x00000100  // Invert pwmB
#define PWM_2_GENB_ACTCMPBU_ZERO                                              \
                                0x00000200  // Drive pwmB Low
#define PWM_2_GENB_ACTCMPBU_ONE 0x00000300  // Drive pwmB High
#define PWM_2_GENB_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_2_GENB_ACTCMPAD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_2_GENB_ACTCMPAD_INV 0x00000040  // Invert pwmB
#define PWM_2_GENB_ACTCMPAD_ZERO                                              \
                                0x00000080  // Drive pwmB Low
#define PWM_2_GENB_ACTCMPAD_ONE 0x000000C0  // Drive pwmB High
#define PWM_2_GENB_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_2_GENB_ACTCMPAU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_2_GENB_ACTCMPAU_INV 0x00000010  // Invert pwmB
#define PWM_2_GENB_ACTCMPAU_ZERO                                              \
                                0x00000020  // Drive pwmB Low
#define PWM_2_GENB_ACTCMPAU_ONE 0x00000030  // Drive pwmB High
#define PWM_2_GENB_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_2_GENB_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_2_GENB_ACTLOAD_INV  0x00000004  // Invert pwmB
#define PWM_2_GENB_ACTLOAD_ZERO 0x00000008  // Drive pwmB Low
#define PWM_2_GENB_ACTLOAD_ONE  0x0000000C  // Drive pwmB High
#define PWM_2_GENB_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_2_GENB_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_2_GENB_ACTZERO_INV  0x00000001  // Invert pwmB
#define PWM_2_GENB_ACTZERO_ZERO 0x00000002  // Drive pwmB Low
#define PWM_2_GENB_ACTZERO_ONE  0x00000003  // Drive pwmB High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_DBCTL register.
//
//*****************************************************************************
#define PWM_2_DBCTL_ENABLE      0x00000001  // Dead-Band Generator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_DBRISE register.
//
//*****************************************************************************
#define PWM_2_DBRISE_RISEDELAY_M                                              \
                                0x00000FFF  // Dead-Band Rise Delay
#define PWM_2_DBRISE_RISEDELAY_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_DBFALL register.
//
//*****************************************************************************
#define PWM_2_DBFALL_FALLDELAY_M                                              \
                                0x00000FFF  // Dead-Band Fall Delay
#define PWM_2_DBFALL_FALLDELAY_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_FLTSRC0
// register.
//
//*****************************************************************************
#define PWM_2_FLTSRC0_FAULT3    0x00000008  // Fault3 Input
#define PWM_2_FLTSRC0_FAULT2    0x00000004  // Fault2 Input
#define PWM_2_FLTSRC0_FAULT1    0x00000002  // Fault1 Input
#define PWM_2_FLTSRC0_FAULT0    0x00000001  // Fault0 Input

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_FLTSRC1
// register.
//
//*****************************************************************************
#define PWM_2_FLTSRC1_DCMP7     0x00000080  // Digital Comparator 7
#define PWM_2_FLTSRC1_DCMP6     0x00000040  // Digital Comparator 6
#define PWM_2_FLTSRC1_DCMP5     0x00000020  // Digital Comparator 5
#define PWM_2_FLTSRC1_DCMP4     0x00000010  // Digital Comparator 4
#define PWM_2_FLTSRC1_DCMP3     0x00000008  // Digital Comparator 3
#define PWM_2_FLTSRC1_DCMP2     0x00000004  // Digital Comparator 2
#define PWM_2_FLTSRC1_DCMP1     0x00000002  // Digital Comparator 1
#define PWM_2_FLTSRC1_DCMP0     0x00000001  // Digital Comparator 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_MINFLTPER
// register.
//
//*****************************************************************************
#define PWM_2_MINFLTPER_MFP_M   0x0000FFFF  // Minimum Fault Period
#define PWM_2_MINFLTPER_MFP_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_CTL register.
//
//*****************************************************************************
#define PWM_3_CTL_LATCH         0x00040000  // Latch Fault Input
#define PWM_3_CTL_MINFLTPER     0x00020000  // Minimum Fault Period
#define PWM_3_CTL_FLTSRC        0x00010000  // Fault Condition Source
#define PWM_3_CTL_DBFALLUPD_M   0x0000C000  // PWMnDBFALL Update Mode
#define PWM_3_CTL_DBFALLUPD_I   0x00000000  // Immediate
#define PWM_3_CTL_DBFALLUPD_LS  0x00008000  // Locally Synchronized
#define PWM_3_CTL_DBFALLUPD_GS  0x0000C000  // Globally Synchronized
#define PWM_3_CTL_DBRISEUPD_M   0x00003000  // PWMnDBRISE Update Mode
#define PWM_3_CTL_DBRISEUPD_I   0x00000000  // Immediate
#define PWM_3_CTL_DBRISEUPD_LS  0x00002000  // Locally Synchronized
#define PWM_3_CTL_DBRISEUPD_GS  0x00003000  // Globally Synchronized
#define PWM_3_CTL_DBCTLUPD_M    0x00000C00  // PWMnDBCTL Update Mode
#define PWM_3_CTL_DBCTLUPD_I    0x00000000  // Immediate
#define PWM_3_CTL_DBCTLUPD_LS   0x00000800  // Locally Synchronized
#define PWM_3_CTL_DBCTLUPD_GS   0x00000C00  // Globally Synchronized
#define PWM_3_CTL_GENBUPD_M     0x00000300  // PWMnGENB Update Mode
#define PWM_3_CTL_GENBUPD_I     0x00000000  // Immediate
#define PWM_3_CTL_GENBUPD_LS    0x00000200  // Locally Synchronized
#define PWM_3_CTL_GENBUPD_GS    0x00000300  // Globally Synchronized
#define PWM_3_CTL_GENAUPD_M     0x000000C0  // PWMnGENA Update Mode
#define PWM_3_CTL_GENAUPD_I     0x00000000  // Immediate
#define PWM_3_CTL_GENAUPD_LS    0x00000080  // Locally Synchronized
#define PWM_3_CTL_GENAUPD_GS    0x000000C0  // Globally Synchronized
#define PWM_3_CTL_CMPBUPD       0x00000020  // Comparator B Update Mode
#define PWM_3_CTL_CMPAUPD       0x00000010  // Comparator A Update Mode
#define PWM_3_CTL_LOADUPD       0x00000008  // Load Register Update Mode
#define PWM_3_CTL_DEBUG         0x00000004  // Debug Mode
#define PWM_3_CTL_MODE          0x00000002  // Counter Mode
#define PWM_3_CTL_ENABLE        0x00000001  // PWM Block Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_INTEN register.
//
//*****************************************************************************
#define PWM_3_INTEN_TRCMPBD     0x00002000  // Trigger for Counter=PWMnCMPB
// Down
#define PWM_3_INTEN_TRCMPBU     0x00001000  // Trigger for Counter=PWMnCMPB Up
#define PWM_3_INTEN_TRCMPAD     0x00000800  // Trigger for Counter=PWMnCMPA
// Down
#define PWM_3_INTEN_TRCMPAU     0x00000400  // Trigger for Counter=PWMnCMPA Up
#define PWM_3_INTEN_TRCNTLOAD   0x00000200  // Trigger for Counter=PWMnLOAD
#define PWM_3_INTEN_TRCNTZERO   0x00000100  // Trigger for Counter=0
#define PWM_3_INTEN_INTCMPBD    0x00000020  // Interrupt for Counter=PWMnCMPB
// Down
#define PWM_3_INTEN_INTCMPBU    0x00000010  // Interrupt for Counter=PWMnCMPB
// Up
#define PWM_3_INTEN_INTCMPAD    0x00000008  // Interrupt for Counter=PWMnCMPA
// Down
#define PWM_3_INTEN_INTCMPAU    0x00000004  // Interrupt for Counter=PWMnCMPA
// Up
#define PWM_3_INTEN_INTCNTLOAD  0x00000002  // Interrupt for Counter=PWMnLOAD
#define PWM_3_INTEN_INTCNTZERO  0x00000001  // Interrupt for Counter=0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_RIS register.
//
//*****************************************************************************
#define PWM_3_RIS_INTCMPBD      0x00000020  // Comparator B Down Interrupt
// Status
#define PWM_3_RIS_INTCMPBU      0x00000010  // Comparator B Up Interrupt Status
#define PWM_3_RIS_INTCMPAD      0x00000008  // Comparator A Down Interrupt
// Status
#define PWM_3_RIS_INTCMPAU      0x00000004  // Comparator A Up Interrupt Status
#define PWM_3_RIS_INTCNTLOAD    0x00000002  // Counter=Load Interrupt Status
#define PWM_3_RIS_INTCNTZERO    0x00000001  // Counter=0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_ISC register.
//
//*****************************************************************************
#define PWM_3_ISC_INTCMPBD      0x00000020  // Comparator B Down Interrupt
#define PWM_3_ISC_INTCMPBU      0x00000010  // Comparator B Up Interrupt
#define PWM_3_ISC_INTCMPAD      0x00000008  // Comparator A Down Interrupt
#define PWM_3_ISC_INTCMPAU      0x00000004  // Comparator A Up Interrupt
#define PWM_3_ISC_INTCNTLOAD    0x00000002  // Counter=Load Interrupt
#define PWM_3_ISC_INTCNTZERO    0x00000001  // Counter=0 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_LOAD register.
//
//*****************************************************************************
#define PWM_3_LOAD_LOAD_M       0x0000FFFF  // Counter Load Value
#define PWM_3_LOAD_LOAD_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_COUNT register.
//
//*****************************************************************************
#define PWM_3_COUNT_COUNT_M     0x0000FFFF  // Counter Value
#define PWM_3_COUNT_COUNT_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_CMPA register.
//
//*****************************************************************************
#define PWM_3_CMPA_COMPA_M      0x0000FFFF  // Comparator A Value
#define PWM_3_CMPA_COMPA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_CMPB register.
//
//*****************************************************************************
#define PWM_3_CMPB_COMPB_M      0x0000FFFF  // Comparator B Value
#define PWM_3_CMPB_COMPB_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_GENA register.
//
//*****************************************************************************
#define PWM_3_GENA_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_3_GENA_ACTCMPBD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_3_GENA_ACTCMPBD_INV 0x00000400  // Invert pwmA
#define PWM_3_GENA_ACTCMPBD_ZERO                                              \
                                0x00000800  // Drive pwmA Low
#define PWM_3_GENA_ACTCMPBD_ONE 0x00000C00  // Drive pwmA High
#define PWM_3_GENA_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_3_GENA_ACTCMPBU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_3_GENA_ACTCMPBU_INV 0x00000100  // Invert pwmA
#define PWM_3_GENA_ACTCMPBU_ZERO                                              \
                                0x00000200  // Drive pwmA Low
#define PWM_3_GENA_ACTCMPBU_ONE 0x00000300  // Drive pwmA High
#define PWM_3_GENA_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_3_GENA_ACTCMPAD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_3_GENA_ACTCMPAD_INV 0x00000040  // Invert pwmA
#define PWM_3_GENA_ACTCMPAD_ZERO                                              \
                                0x00000080  // Drive pwmA Low
#define PWM_3_GENA_ACTCMPAD_ONE 0x000000C0  // Drive pwmA High
#define PWM_3_GENA_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_3_GENA_ACTCMPAU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_3_GENA_ACTCMPAU_INV 0x00000010  // Invert pwmA
#define PWM_3_GENA_ACTCMPAU_ZERO                                              \
                                0x00000020  // Drive pwmA Low
#define PWM_3_GENA_ACTCMPAU_ONE 0x00000030  // Drive pwmA High
#define PWM_3_GENA_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_3_GENA_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_3_GENA_ACTLOAD_INV  0x00000004  // Invert pwmA
#define PWM_3_GENA_ACTLOAD_ZERO 0x00000008  // Drive pwmA Low
#define PWM_3_GENA_ACTLOAD_ONE  0x0000000C  // Drive pwmA High
#define PWM_3_GENA_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_3_GENA_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_3_GENA_ACTZERO_INV  0x00000001  // Invert pwmA
#define PWM_3_GENA_ACTZERO_ZERO 0x00000002  // Drive pwmA Low
#define PWM_3_GENA_ACTZERO_ONE  0x00000003  // Drive pwmA High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_GENB register.
//
//*****************************************************************************
#define PWM_3_GENB_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_3_GENB_ACTCMPBD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_3_GENB_ACTCMPBD_INV 0x00000400  // Invert pwmB
#define PWM_3_GENB_ACTCMPBD_ZERO                                              \
                                0x00000800  // Drive pwmB Low
#define PWM_3_GENB_ACTCMPBD_ONE 0x00000C00  // Drive pwmB High
#define PWM_3_GENB_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_3_GENB_ACTCMPBU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_3_GENB_ACTCMPBU_INV 0x00000100  // Invert pwmB
#define PWM_3_GENB_ACTCMPBU_ZERO                                              \
                                0x00000200  // Drive pwmB Low
#define PWM_3_GENB_ACTCMPBU_ONE 0x00000300  // Drive pwmB High
#define PWM_3_GENB_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_3_GENB_ACTCMPAD_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_3_GENB_ACTCMPAD_INV 0x00000040  // Invert pwmB
#define PWM_3_GENB_ACTCMPAD_ZERO                                              \
                                0x00000080  // Drive pwmB Low
#define PWM_3_GENB_ACTCMPAD_ONE 0x000000C0  // Drive pwmB High
#define PWM_3_GENB_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_3_GENB_ACTCMPAU_NONE                                              \
                                0x00000000  // Do nothing
#define PWM_3_GENB_ACTCMPAU_INV 0x00000010  // Invert pwmB
#define PWM_3_GENB_ACTCMPAU_ZERO                                              \
                                0x00000020  // Drive pwmB Low
#define PWM_3_GENB_ACTCMPAU_ONE 0x00000030  // Drive pwmB High
#define PWM_3_GENB_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_3_GENB_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_3_GENB_ACTLOAD_INV  0x00000004  // Invert pwmB
#define PWM_3_GENB_ACTLOAD_ZERO 0x00000008  // Drive pwmB Low
#define PWM_3_GENB_ACTLOAD_ONE  0x0000000C  // Drive pwmB High
#define PWM_3_GENB_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_3_GENB_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_3_GENB_ACTZERO_INV  0x00000001  // Invert pwmB
#define PWM_3_GENB_ACTZERO_ZERO 0x00000002  // Drive pwmB Low
#define PWM_3_GENB_ACTZERO_ONE  0x00000003  // Drive pwmB High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_DBCTL register.
//
//*****************************************************************************
#define PWM_3_DBCTL_ENABLE      0x00000001  // Dead-Band Generator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_DBRISE register.
//
//*****************************************************************************
#define PWM_3_DBRISE_RISEDELAY_M                                              \
                                0x00000FFF  // Dead-Band Rise Delay
#define PWM_3_DBRISE_RISEDELAY_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_DBFALL register.
//
//*****************************************************************************
#define PWM_3_DBFALL_FALLDELAY_M                                              \
                                0x00000FFF  // Dead-Band Fall Delay
#define PWM_3_DBFALL_FALLDELAY_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_FLTSRC0
// register.
//
//*****************************************************************************
#define PWM_3_FLTSRC0_FAULT3    0x00000008  // Fault3 Input
#define PWM_3_FLTSRC0_FAULT2    0x00000004  // Fault2 Input
#define PWM_3_FLTSRC0_FAULT1    0x00000002  // Fault1 Input
#define PWM_3_FLTSRC0_FAULT0    0x00000001  // Fault0 Input

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_FLTSRC1
// register.
//
//*****************************************************************************
#define PWM_3_FLTSRC1_DCMP7     0x00000080  // Digital Comparator 7
#define PWM_3_FLTSRC1_DCMP6     0x00000040  // Digital Comparator 6
#define PWM_3_FLTSRC1_DCMP5     0x00000020  // Digital Comparator 5
#define PWM_3_FLTSRC1_DCMP4     0x00000010  // Digital Comparator 4
#define PWM_3_FLTSRC1_DCMP3     0x00000008  // Digital Comparator 3
#define PWM_3_FLTSRC1_DCMP2     0x00000004  // Digital Comparator 2
#define PWM_3_FLTSRC1_DCMP1     0x00000002  // Digital Comparator 1
#define PWM_3_FLTSRC1_DCMP0     0x00000001  // Digital Comparator 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_MINFLTPER
// register.
//
//*****************************************************************************
#define PWM_3_MINFLTPER_MFP_M   0x0000FFFF  // Minimum Fault Period
#define PWM_3_MINFLTPER_MFP_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_FLTSEN register.
//
//*****************************************************************************
#define PWM_0_FLTSEN_FAULT3     0x00000008  // Fault3 Sense
#define PWM_0_FLTSEN_FAULT2     0x00000004  // Fault2 Sense
#define PWM_0_FLTSEN_FAULT1     0x00000002  // Fault1 Sense
#define PWM_0_FLTSEN_FAULT0     0x00000001  // Fault0 Sense

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_FLTSTAT0
// register.
//
//*****************************************************************************
#define PWM_0_FLTSTAT0_FAULT3   0x00000008  // Fault Input 3
#define PWM_0_FLTSTAT0_FAULT2   0x00000004  // Fault Input 2
#define PWM_0_FLTSTAT0_FAULT1   0x00000002  // Fault Input 1
#define PWM_0_FLTSTAT0_FAULT0   0x00000001  // Fault Input 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_FLTSTAT1
// register.
//
//*****************************************************************************
#define PWM_0_FLTSTAT1_DCMP7    0x00000080  // Digital Comparator 7 Trigger
#define PWM_0_FLTSTAT1_DCMP6    0x00000040  // Digital Comparator 6 Trigger
#define PWM_0_FLTSTAT1_DCMP5    0x00000020  // Digital Comparator 5 Trigger
#define PWM_0_FLTSTAT1_DCMP4    0x00000010  // Digital Comparator 4 Trigger
#define PWM_0_FLTSTAT1_DCMP3    0x00000008  // Digital Comparator 3 Trigger
#define PWM_0_FLTSTAT1_DCMP2    0x00000004  // Digital Comparator 2 Trigger
#define PWM_0_FLTSTAT1_DCMP1    0x00000002  // Digital Comparator 1 Trigger
#define PWM_0_FLTSTAT1_DCMP0    0x00000001  // Digital Comparator 0 Trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_FLTSEN register.
//
//*****************************************************************************
#define PWM_1_FLTSEN_FAULT3     0x00000008  // Fault3 Sense
#define PWM_1_FLTSEN_FAULT2     0x00000004  // Fault2 Sense
#define PWM_1_FLTSEN_FAULT1     0x00000002  // Fault1 Sense
#define PWM_1_FLTSEN_FAULT0     0x00000001  // Fault0 Sense

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_FLTSTAT0
// register.
//
//*****************************************************************************
#define PWM_1_FLTSTAT0_FAULT3   0x00000008  // Fault Input 3
#define PWM_1_FLTSTAT0_FAULT2   0x00000004  // Fault Input 2
#define PWM_1_FLTSTAT0_FAULT1   0x00000002  // Fault Input 1
#define PWM_1_FLTSTAT0_FAULT0   0x00000001  // Fault Input 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_1_FLTSTAT1
// register.
//
//*****************************************************************************
#define PWM_1_FLTSTAT1_DCMP7    0x00000080  // Digital Comparator 7 Trigger
#define PWM_1_FLTSTAT1_DCMP6    0x00000040  // Digital Comparator 6 Trigger
#define PWM_1_FLTSTAT1_DCMP5    0x00000020  // Digital Comparator 5 Trigger
#define PWM_1_FLTSTAT1_DCMP4    0x00000010  // Digital Comparator 4 Trigger
#define PWM_1_FLTSTAT1_DCMP3    0x00000008  // Digital Comparator 3 Trigger
#define PWM_1_FLTSTAT1_DCMP2    0x00000004  // Digital Comparator 2 Trigger
#define PWM_1_FLTSTAT1_DCMP1    0x00000002  // Digital Comparator 1 Trigger
#define PWM_1_FLTSTAT1_DCMP0    0x00000001  // Digital Comparator 0 Trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_FLTSEN register.
//
//*****************************************************************************
#define PWM_2_FLTSEN_FAULT3     0x00000008  // Fault3 Sense
#define PWM_2_FLTSEN_FAULT2     0x00000004  // Fault2 Sense
#define PWM_2_FLTSEN_FAULT1     0x00000002  // Fault1 Sense
#define PWM_2_FLTSEN_FAULT0     0x00000001  // Fault0 Sense

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_FLTSTAT0
// register.
//
//*****************************************************************************
#define PWM_2_FLTSTAT0_FAULT3   0x00000008  // Fault Input 3
#define PWM_2_FLTSTAT0_FAULT2   0x00000004  // Fault Input 2
#define PWM_2_FLTSTAT0_FAULT1   0x00000002  // Fault Input 1
#define PWM_2_FLTSTAT0_FAULT0   0x00000001  // Fault Input 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_2_FLTSTAT1
// register.
//
//*****************************************************************************
#define PWM_2_FLTSTAT1_DCMP7    0x00000080  // Digital Comparator 7 Trigger
#define PWM_2_FLTSTAT1_DCMP6    0x00000040  // Digital Comparator 6 Trigger
#define PWM_2_FLTSTAT1_DCMP5    0x00000020  // Digital Comparator 5 Trigger
#define PWM_2_FLTSTAT1_DCMP4    0x00000010  // Digital Comparator 4 Trigger
#define PWM_2_FLTSTAT1_DCMP3    0x00000008  // Digital Comparator 3 Trigger
#define PWM_2_FLTSTAT1_DCMP2    0x00000004  // Digital Comparator 2 Trigger
#define PWM_2_FLTSTAT1_DCMP1    0x00000002  // Digital Comparator 1 Trigger
#define PWM_2_FLTSTAT1_DCMP0    0x00000001  // Digital Comparator 0 Trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_FLTSEN register.
//
//*****************************************************************************
#define PWM_3_FLTSEN_FAULT3     0x00000008  // Fault3 Sense
#define PWM_3_FLTSEN_FAULT2     0x00000004  // Fault2 Sense
#define PWM_3_FLTSEN_FAULT1     0x00000002  // Fault1 Sense
#define PWM_3_FLTSEN_FAULT0     0x00000001  // Fault0 Sense

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_FLTSTAT0
// register.
//
//*****************************************************************************
#define PWM_3_FLTSTAT0_FAULT3   0x00000008  // Fault Input 3
#define PWM_3_FLTSTAT0_FAULT2   0x00000004  // Fault Input 2
#define PWM_3_FLTSTAT0_FAULT1   0x00000002  // Fault Input 1
#define PWM_3_FLTSTAT0_FAULT0   0x00000001  // Fault Input 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_3_FLTSTAT1
// register.
//
//*****************************************************************************
#define PWM_3_FLTSTAT1_DCMP7    0x00000080  // Digital Comparator 7 Trigger
#define PWM_3_FLTSTAT1_DCMP6    0x00000040  // Digital Comparator 6 Trigger
#define PWM_3_FLTSTAT1_DCMP5    0x00000020  // Digital Comparator 5 Trigger
#define PWM_3_FLTSTAT1_DCMP4    0x00000010  // Digital Comparator 4 Trigger
#define PWM_3_FLTSTAT1_DCMP3    0x00000008  // Digital Comparator 3 Trigger
#define PWM_3_FLTSTAT1_DCMP2    0x00000004  // Digital Comparator 2 Trigger
#define PWM_3_FLTSTAT1_DCMP1    0x00000002  // Digital Comparator 1 Trigger
#define PWM_3_FLTSTAT1_DCMP0    0x00000001  // Digital Comparator 0 Trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_PP register.
//
//*****************************************************************************
#define PWM_PP_ONE              0x00000400  // One-Shot Mode
#define PWM_PP_EFAULT           0x00000200  // Extended Fault
#define PWM_PP_ESYNC            0x00000100  // Extended Synchronization
#define PWM_PP_FCNT_M           0x000000F0  // Fault Inputs (per PWM unit)
#define PWM_PP_GCNT_M           0x0000000F  // Generators
#define PWM_PP_FCNT_S           4
#define PWM_PP_GCNT_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_CC register.
//
//*****************************************************************************
#define PWM_CC_USEPWM           0x00000100  // Use PWM Clock Divisor
#define PWM_CC_PWMDIV_M         0x00000007  // PWM Clock Divider
#define PWM_CC_PWMDIV_2         0x00000000  // /2
#define PWM_CC_PWMDIV_4         0x00000001  // /4
#define PWM_CC_PWMDIV_8         0x00000002  // /8
#define PWM_CC_PWMDIV_16        0x00000003  // /16
#define PWM_CC_PWMDIV_32        0x00000004  // /32
#define PWM_CC_PWMDIV_64        0x00000005  // /64

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_CTL register.
//
//*****************************************************************************
#define QEI_CTL_FILTCNT_M       0x000F0000  // Input Filter Prescale Count
#define QEI_CTL_FILTEN          0x00002000  // Enable Input Filter
#define QEI_CTL_STALLEN         0x00001000  // Stall QEI
#define QEI_CTL_INVI            0x00000800  // Invert Index Pulse
#define QEI_CTL_INVB            0x00000400  // Invert PhB
#define QEI_CTL_INVA            0x00000200  // Invert PhA
#define QEI_CTL_VELDIV_M        0x000001C0  // Predivide Velocity
#define QEI_CTL_VELDIV_1        0x00000000  // QEI clock /1
#define QEI_CTL_VELDIV_2        0x00000040  // QEI clock /2
#define QEI_CTL_VELDIV_4        0x00000080  // QEI clock /4
#define QEI_CTL_VELDIV_8        0x000000C0  // QEI clock /8
#define QEI_CTL_VELDIV_16       0x00000100  // QEI clock /16
#define QEI_CTL_VELDIV_32       0x00000140  // QEI clock /32
#define QEI_CTL_VELDIV_64       0x00000180  // QEI clock /64
#define QEI_CTL_VELDIV_128      0x000001C0  // QEI clock /128
#define QEI_CTL_VELEN           0x00000020  // Capture Velocity
#define QEI_CTL_RESMODE         0x00000010  // Reset Mode
#define QEI_CTL_CAPMODE         0x00000008  // Capture Mode
#define QEI_CTL_SIGMODE         0x00000004  // Signal Mode
#define QEI_CTL_SWAP            0x00000002  // Swap Signals
#define QEI_CTL_ENABLE          0x00000001  // Enable QEI
#define QEI_CTL_FILTCNT_S       16

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_STAT register.
//
//*****************************************************************************
#define QEI_STAT_DIRECTION      0x00000002  // Direction of Rotation
#define QEI_STAT_ERROR          0x00000001  // Error Detected

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_POS register.
//
//*****************************************************************************
#define QEI_POS_M               0xFFFFFFFF  // Current Position Integrator
// Value
#define QEI_POS_S               0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_MAXPOS register.
//
//*****************************************************************************
#define QEI_MAXPOS_M            0xFFFFFFFF  // Maximum Position Integrator
// Value
#define QEI_MAXPOS_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_LOAD register.
//
//*****************************************************************************
#define QEI_LOAD_M              0xFFFFFFFF  // Velocity Timer Load Value
#define QEI_LOAD_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_TIME register.
//
//*****************************************************************************
#define QEI_TIME_M              0xFFFFFFFF  // Velocity Timer Current Value
#define QEI_TIME_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_COUNT register.
//
//*****************************************************************************
#define QEI_COUNT_M             0xFFFFFFFF  // Velocity Pulse Count
#define QEI_COUNT_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_SPEED register.
//
//*****************************************************************************
#define QEI_SPEED_M             0xFFFFFFFF  // Velocity
#define QEI_SPEED_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_INTEN register.
//
//*****************************************************************************
#define QEI_INTEN_ERROR         0x00000008  // Phase Error Interrupt Enable
#define QEI_INTEN_DIR           0x00000004  // Direction Change Interrupt
// Enable
#define QEI_INTEN_TIMER         0x00000002  // Timer Expires Interrupt Enable
#define QEI_INTEN_INDEX         0x00000001  // Index Pulse Detected Interrupt
// Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_RIS register.
//
//*****************************************************************************
#define QEI_RIS_ERROR           0x00000008  // Phase Error Detected
#define QEI_RIS_DIR             0x00000004  // Direction Change Detected
#define QEI_RIS_TIMER           0x00000002  // Velocity Timer Expired
#define QEI_RIS_INDEX           0x00000001  // Index Pulse Asserted

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_ISC register.
//
//*****************************************************************************
#define QEI_ISC_ERROR           0x00000008  // Phase Error Interrupt
#define QEI_ISC_DIR             0x00000004  // Direction Change Interrupt
#define QEI_ISC_TIMER           0x00000002  // Velocity Timer Expired Interrupt
#define QEI_ISC_INDEX           0x00000001  // Index Pulse Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_CFG register.
//
//*****************************************************************************
#define TIMER_CFG_M             0x00000007  // GPTM Configuration
#define TIMER_CFG_32_BIT_TIMER  0x00000000  // For a 16/32-bit timer, this
// value selects the 32-bit timer
// configuration
#define TIMER_CFG_32_BIT_RTC    0x00000001  // For a 16/32-bit timer, this
// value selects the 32-bit
// real-time clock (RTC) counter
// configuration
#define TIMER_CFG_16_BIT        0x00000004  // For a 16/32-bit timer, this
// value selects the 16-bit timer
// configuration

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMR register.
//
//*****************************************************************************
#define TIMER_TAMR_TCACT_M      0x0000E000  // Timer Compare Action Select
#define TIMER_TAMR_TCACT_NONE   0x00000000  // Disable compare operations
#define TIMER_TAMR_TCACT_TOGGLE 0x00002000  // Toggle State on Time-Out
#define TIMER_TAMR_TCACT_CLRTO  0x00004000  // Clear CCP on Time-Out
#define TIMER_TAMR_TCACT_SETTO  0x00006000  // Set CCP on Time-Out
#define TIMER_TAMR_TCACT_SETTOGTO                                             \
                                0x00008000  // Set CCP immediately and toggle
// on Time-Out
#define TIMER_TAMR_TCACT_CLRTOGTO                                             \
                                0x0000A000  // Clear CCP immediately and toggle
// on Time-Out
#define TIMER_TAMR_TCACT_SETCLRTO                                             \
                                0x0000C000  // Set CCP immediately and clear on
// Time-Out
#define TIMER_TAMR_TCACT_CLRSETTO                                             \
                                0x0000E000  // Clear CCP immediately and set on
// Time-Out
#define TIMER_TAMR_TACINTD      0x00001000  // One-shot/Periodic Interrupt
// Disable
#define TIMER_TAMR_TAPLO        0x00000800  // GPTM Timer A PWM Legacy
// Operation
#define TIMER_TAMR_TAMRSU       0x00000400  // GPTM Timer A Match Register
// Update
#define TIMER_TAMR_TAPWMIE      0x00000200  // GPTM Timer A PWM Interrupt
// Enable
#define TIMER_TAMR_TAILD        0x00000100  // GPTM Timer A Interval Load Write
#define TIMER_TAMR_TASNAPS      0x00000080  // GPTM Timer A Snap-Shot Mode
#define TIMER_TAMR_TAWOT        0x00000040  // GPTM Timer A Wait-on-Trigger
#define TIMER_TAMR_TAMIE        0x00000020  // GPTM Timer A Match Interrupt
// Enable
#define TIMER_TAMR_TACDIR       0x00000010  // GPTM Timer A Count Direction
#define TIMER_TAMR_TAAMS        0x00000008  // GPTM Timer A Alternate Mode
// Select
#define TIMER_TAMR_TACMR        0x00000004  // GPTM Timer A Capture Mode
#define TIMER_TAMR_TAMR_M       0x00000003  // GPTM Timer A Mode
#define TIMER_TAMR_TAMR_1_SHOT  0x00000001  // One-Shot Timer mode
#define TIMER_TAMR_TAMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_TAMR_TAMR_CAP     0x00000003  // Capture mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMR register.
//
//*****************************************************************************
#define TIMER_TBMR_TCACT_M      0x0000E000  // Timer Compare Action Select
#define TIMER_TBMR_TCACT_NONE   0x00000000  // Disable compare operations
#define TIMER_TBMR_TCACT_TOGGLE 0x00002000  // Toggle State on Time-Out
#define TIMER_TBMR_TCACT_CLRTO  0x00004000  // Clear CCP on Time-Out
#define TIMER_TBMR_TCACT_SETTO  0x00006000  // Set CCP on Time-Out
#define TIMER_TBMR_TCACT_SETTOGTO                                             \
                                0x00008000  // Set CCP immediately and toggle
// on Time-Out
#define TIMER_TBMR_TCACT_CLRTOGTO                                             \
                                0x0000A000  // Clear CCP immediately and toggle
// on Time-Out
#define TIMER_TBMR_TCACT_SETCLRTO                                             \
                                0x0000C000  // Set CCP immediately and clear on
// Time-Out
#define TIMER_TBMR_TCACT_CLRSETTO                                             \
                                0x0000E000  // Clear CCP immediately and set on
// Time-Out
#define TIMER_TBMR_TBCINTD      0x00001000  // One-Shot/Periodic Interrupt
// Disable
#define TIMER_TBMR_TBPLO        0x00000800  // GPTM Timer B PWM Legacy
// Operation
#define TIMER_TBMR_TBMRSU       0x00000400  // GPTM Timer B Match Register
// Update
#define TIMER_TBMR_TBPWMIE      0x00000200  // GPTM Timer B PWM Interrupt
// Enable
#define TIMER_TBMR_TBILD        0x00000100  // GPTM Timer B Interval Load Write
#define TIMER_TBMR_TBSNAPS      0x00000080  // GPTM Timer B Snap-Shot Mode
#define TIMER_TBMR_TBWOT        0x00000040  // GPTM Timer B Wait-on-Trigger
#define TIMER_TBMR_TBMIE        0x00000020  // GPTM Timer B Match Interrupt
// Enable
#define TIMER_TBMR_TBCDIR       0x00000010  // GPTM Timer B Count Direction
#define TIMER_TBMR_TBAMS        0x00000008  // GPTM Timer B Alternate Mode
// Select
#define TIMER_TBMR_TBCMR        0x00000004  // GPTM Timer B Capture Mode
#define TIMER_TBMR_TBMR_M       0x00000003  // GPTM Timer B Mode
#define TIMER_TBMR_TBMR_1_SHOT  0x00000001  // One-Shot Timer mode
#define TIMER_TBMR_TBMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_TBMR_TBMR_CAP     0x00000003  // Capture mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_CTL register.
//
//*****************************************************************************
#define TIMER_CTL_TBPWML        0x00004000  // GPTM Timer B PWM Output Level
#define TIMER_CTL_TBOTE         0x00002000  // GPTM Timer B Output Trigger
// Enable
#define TIMER_CTL_TBEVENT_M     0x00000C00  // GPTM Timer B Event Mode
#define TIMER_CTL_TBEVENT_POS   0x00000000  // Positive edge
#define TIMER_CTL_TBEVENT_NEG   0x00000400  // Negative edge
#define TIMER_CTL_TBEVENT_BOTH  0x00000C00  // Both edges
#define TIMER_CTL_TBSTALL       0x00000200  // GPTM Timer B Stall Enable
#define TIMER_CTL_TBEN          0x00000100  // GPTM Timer B Enable
#define TIMER_CTL_TAPWML        0x00000040  // GPTM Timer A PWM Output Level
#define TIMER_CTL_TAOTE         0x00000020  // GPTM Timer A Output Trigger
// Enable
#define TIMER_CTL_RTCEN         0x00000010  // GPTM RTC Stall Enable
#define TIMER_CTL_TAEVENT_M     0x0000000C  // GPTM Timer A Event Mode
#define TIMER_CTL_TAEVENT_POS   0x00000000  // Positive edge
#define TIMER_CTL_TAEVENT_NEG   0x00000004  // Negative edge
#define TIMER_CTL_TAEVENT_BOTH  0x0000000C  // Both edges
#define TIMER_CTL_TASTALL       0x00000002  // GPTM Timer A Stall Enable
#define TIMER_CTL_TAEN          0x00000001  // GPTM Timer A Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_SYNC register.
//
//*****************************************************************************
#define TIMER_SYNC_SYNCT7_M     0x0000C000  // Synchronize GPTM Timer 7
#define TIMER_SYNC_SYNCT7_NONE  0x00000000  // GPT7 is not affected
#define TIMER_SYNC_SYNCT7_TA    0x00004000  // A timeout event for Timer A of
// GPTM7 is triggered
#define TIMER_SYNC_SYNCT7_TB    0x00008000  // A timeout event for Timer B of
// GPTM7 is triggered
#define TIMER_SYNC_SYNCT7_TATB  0x0000C000  // A timeout event for both Timer A
// and Timer B of GPTM7 is
// triggered
#define TIMER_SYNC_SYNCT6_M     0x00003000  // Synchronize GPTM Timer 6
#define TIMER_SYNC_SYNCT6_NONE  0x00000000  // GPTM6 is not affected
#define TIMER_SYNC_SYNCT6_TA    0x00001000  // A timeout event for Timer A of
// GPTM6 is triggered
#define TIMER_SYNC_SYNCT6_TB    0x00002000  // A timeout event for Timer B of
// GPTM6 is triggered
#define TIMER_SYNC_SYNCT6_TATB  0x00003000  // A timeout event for both Timer A
// and Timer B of GPTM6 is
// triggered
#define TIMER_SYNC_SYNCT5_M     0x00000C00  // Synchronize GPTM Timer 5
#define TIMER_SYNC_SYNCT5_NONE  0x00000000  // GPTM5 is not affected
#define TIMER_SYNC_SYNCT5_TA    0x00000400  // A timeout event for Timer A of
// GPTM5 is triggered
#define TIMER_SYNC_SYNCT5_TB    0x00000800  // A timeout event for Timer B of
// GPTM5 is triggered
#define TIMER_SYNC_SYNCT5_TATB  0x00000C00  // A timeout event for both Timer A
// and Timer B of GPTM5 is
// triggered
#define TIMER_SYNC_SYNCT4_M     0x00000300  // Synchronize GPTM Timer 4
#define TIMER_SYNC_SYNCT4_NONE  0x00000000  // GPTM4 is not affected
#define TIMER_SYNC_SYNCT4_TA    0x00000100  // A timeout event for Timer A of
// GPTM4 is triggered
#define TIMER_SYNC_SYNCT4_TB    0x00000200  // A timeout event for Timer B of
// GPTM4 is triggered
#define TIMER_SYNC_SYNCT4_TATB  0x00000300  // A timeout event for both Timer A
// and Timer B of GPTM4 is
// triggered
#define TIMER_SYNC_SYNCT3_M     0x000000C0  // Synchronize GPTM Timer 3
#define TIMER_SYNC_SYNCT3_NONE  0x00000000  // GPTM3 is not affected
#define TIMER_SYNC_SYNCT3_TA    0x00000040  // A timeout event for Timer A of
// GPTM3 is triggered
#define TIMER_SYNC_SYNCT3_TB    0x00000080  // A timeout event for Timer B of
// GPTM3 is triggered
#define TIMER_SYNC_SYNCT3_TATB  0x000000C0  // A timeout event for both Timer A
// and Timer B of GPTM3 is
// triggered
#define TIMER_SYNC_SYNCT2_M     0x00000030  // Synchronize GPTM Timer 2
#define TIMER_SYNC_SYNCT2_NONE  0x00000000  // GPTM2 is not affected
#define TIMER_SYNC_SYNCT2_TA    0x00000010  // A timeout event for Timer A of
// GPTM2 is triggered
#define TIMER_SYNC_SYNCT2_TB    0x00000020  // A timeout event for Timer B of
// GPTM2 is triggered
#define TIMER_SYNC_SYNCT2_TATB  0x00000030  // A timeout event for both Timer A
// and Timer B of GPTM2 is
// triggered
#define TIMER_SYNC_SYNCT1_M     0x0000000C  // Synchronize GPTM Timer 1
#define TIMER_SYNC_SYNCT1_NONE  0x00000000  // GPTM1 is not affected
#define TIMER_SYNC_SYNCT1_TA    0x00000004  // A timeout event for Timer A of
// GPTM1 is triggered
#define TIMER_SYNC_SYNCT1_TB    0x00000008  // A timeout event for Timer B of
// GPTM1 is triggered
#define TIMER_SYNC_SYNCT1_TATB  0x0000000C  // A timeout event for both Timer A
// and Timer B of GPTM1 is
// triggered
#define TIMER_SYNC_SYNCT0_M     0x00000003  // Synchronize GPTM Timer 0
#define TIMER_SYNC_SYNCT0_NONE  0x00000000  // GPTM0 is not affected
#define TIMER_SYNC_SYNCT0_TA    0x00000001  // A timeout event for Timer A of
// GPTM0 is triggered
#define TIMER_SYNC_SYNCT0_TB    0x00000002  // A timeout event for Timer B of
// GPTM0 is triggered
#define TIMER_SYNC_SYNCT0_TATB  0x00000003  // A timeout event for both Timer A
// and Timer B of GPTM0 is
// triggered

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_IMR register.
//
//*****************************************************************************
#define TIMER_IMR_DMABIM        0x00002000  // GPTM Timer B DMA Done Interrupt
// Mask
#define TIMER_IMR_TBMIM         0x00000800  // GPTM Timer B Match Interrupt
// Mask
#define TIMER_IMR_CBEIM         0x00000400  // GPTM Timer B Capture Mode Event
// Interrupt Mask
#define TIMER_IMR_CBMIM         0x00000200  // GPTM Timer B Capture Mode Match
// Interrupt Mask
#define TIMER_IMR_TBTOIM        0x00000100  // GPTM Timer B Time-Out Interrupt
// Mask
#define TIMER_IMR_DMAAIM        0x00000020  // GPTM Timer A DMA Done Interrupt
// Mask
#define TIMER_IMR_TAMIM         0x00000010  // GPTM Timer A Match Interrupt
// Mask
#define TIMER_IMR_RTCIM         0x00000008  // GPTM RTC Interrupt Mask
#define TIMER_IMR_CAEIM         0x00000004  // GPTM Timer A Capture Mode Event
// Interrupt Mask
#define TIMER_IMR_CAMIM         0x00000002  // GPTM Timer A Capture Mode Match
// Interrupt Mask
#define TIMER_IMR_TATOIM        0x00000001  // GPTM Timer A Time-Out Interrupt
// Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_RIS register.
//
//*****************************************************************************
#define TIMER_RIS_DMABRIS       0x00002000  // GPTM Timer B DMA Done Raw
// Interrupt Status
#define TIMER_RIS_TBMRIS        0x00000800  // GPTM Timer B Match Raw Interrupt
#define TIMER_RIS_CBERIS        0x00000400  // GPTM Timer B Capture Mode Event
// Raw Interrupt
#define TIMER_RIS_CBMRIS        0x00000200  // GPTM Timer B Capture Mode Match
// Raw Interrupt
#define TIMER_RIS_TBTORIS       0x00000100  // GPTM Timer B Time-Out Raw
// Interrupt
#define TIMER_RIS_DMAARIS       0x00000020  // GPTM Timer A DMA Done Raw
// Interrupt Status
#define TIMER_RIS_TAMRIS        0x00000010  // GPTM Timer A Match Raw Interrupt
#define TIMER_RIS_RTCRIS        0x00000008  // GPTM RTC Raw Interrupt
#define TIMER_RIS_CAERIS        0x00000004  // GPTM Timer A Capture Mode Event
// Raw Interrupt
#define TIMER_RIS_CAMRIS        0x00000002  // GPTM Timer A Capture Mode Match
// Raw Interrupt
#define TIMER_RIS_TATORIS       0x00000001  // GPTM Timer A Time-Out Raw
// Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_MIS register.
//
//*****************************************************************************
#define TIMER_MIS_DMABMIS       0x00002000  // GPTM Timer B DMA Done Masked
// Interrupt
#define TIMER_MIS_TBMMIS        0x00000800  // GPTM Timer B Match Masked
// Interrupt
#define TIMER_MIS_CBEMIS        0x00000400  // GPTM Timer B Capture Mode Event
// Masked Interrupt
#define TIMER_MIS_CBMMIS        0x00000200  // GPTM Timer B Capture Mode Match
// Masked Interrupt
#define TIMER_MIS_TBTOMIS       0x00000100  // GPTM Timer B Time-Out Masked
// Interrupt
#define TIMER_MIS_DMAAMIS       0x00000020  // GPTM Timer A DMA Done Masked
// Interrupt
#define TIMER_MIS_TAMMIS        0x00000010  // GPTM Timer A Match Masked
// Interrupt
#define TIMER_MIS_RTCMIS        0x00000008  // GPTM RTC Masked Interrupt
#define TIMER_MIS_CAEMIS        0x00000004  // GPTM Timer A Capture Mode Event
// Masked Interrupt
#define TIMER_MIS_CAMMIS        0x00000002  // GPTM Timer A Capture Mode Match
// Masked Interrupt
#define TIMER_MIS_TATOMIS       0x00000001  // GPTM Timer A Time-Out Masked
// Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_ICR register.
//
//*****************************************************************************
#define TIMER_ICR_DMABINT       0x00002000  // GPTM Timer B DMA Done Interrupt
// Clear
#define TIMER_ICR_TBMCINT       0x00000800  // GPTM Timer B Match Interrupt
// Clear
#define TIMER_ICR_CBECINT       0x00000400  // GPTM Timer B Capture Mode Event
// Interrupt Clear
#define TIMER_ICR_CBMCINT       0x00000200  // GPTM Timer B Capture Mode Match
// Interrupt Clear
#define TIMER_ICR_TBTOCINT      0x00000100  // GPTM Timer B Time-Out Interrupt
// Clear
#define TIMER_ICR_DMAAINT       0x00000020  // GPTM Timer A DMA Done Interrupt
// Clear
#define TIMER_ICR_TAMCINT       0x00000010  // GPTM Timer A Match Interrupt
// Clear
#define TIMER_ICR_RTCCINT       0x00000008  // GPTM RTC Interrupt Clear
#define TIMER_ICR_CAECINT       0x00000004  // GPTM Timer A Capture Mode Event
// Interrupt Clear
#define TIMER_ICR_CAMCINT       0x00000002  // GPTM Timer A Capture Mode Match
// Interrupt Clear
#define TIMER_ICR_TATOCINT      0x00000001  // GPTM Timer A Time-Out Raw
// Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAILR register.
//
//*****************************************************************************
#define TIMER_TAILR_M           0xFFFFFFFF  // GPTM Timer A Interval Load
// Register
#define TIMER_TAILR_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBILR register.
//
//*****************************************************************************
#define TIMER_TBILR_M           0xFFFFFFFF  // GPTM Timer B Interval Load
// Register
#define TIMER_TBILR_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMATCHR
// register.
//
//*****************************************************************************
#define TIMER_TAMATCHR_TAMR_M   0xFFFFFFFF  // GPTM Timer A Match Register
#define TIMER_TAMATCHR_TAMR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMATCHR
// register.
//
//*****************************************************************************
#define TIMER_TBMATCHR_TBMR_M   0xFFFFFFFF  // GPTM Timer B Match Register
#define TIMER_TBMATCHR_TBMR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPR register.
//
//*****************************************************************************
#define TIMER_TAPR_TAPSR_M      0x000000FF  // GPTM Timer A Prescale
#define TIMER_TAPR_TAPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPR register.
//
//*****************************************************************************
#define TIMER_TBPR_TBPSR_M      0x000000FF  // GPTM Timer B Prescale
#define TIMER_TBPR_TBPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPMR register.
//
//*****************************************************************************
#define TIMER_TAPMR_TAPSMR_M    0x000000FF  // GPTM TimerA Prescale Match
#define TIMER_TAPMR_TAPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPMR register.
//
//*****************************************************************************
#define TIMER_TBPMR_TBPSMR_M    0x000000FF  // GPTM TimerB Prescale Match
#define TIMER_TBPMR_TBPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAR register.
//
//*****************************************************************************
#define TIMER_TAR_M             0xFFFFFFFF  // GPTM Timer A Register
#define TIMER_TAR_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBR register.
//
//*****************************************************************************
#define TIMER_TBR_M             0xFFFFFFFF  // GPTM Timer B Register
#define TIMER_TBR_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAV register.
//
//*****************************************************************************
#define TIMER_TAV_M             0xFFFFFFFF  // GPTM Timer A Value
#define TIMER_TAV_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBV register.
//
//*****************************************************************************
#define TIMER_TBV_M             0xFFFFFFFF  // GPTM Timer B Value
#define TIMER_TBV_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_RTCPD register.
//
//*****************************************************************************
#define TIMER_RTCPD_RTCPD_M     0x0000FFFF  // RTC Predivide Counter Value
#define TIMER_RTCPD_RTCPD_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPS register.
//
//*****************************************************************************
#define TIMER_TAPS_PSS_M        0x0000FFFF  // GPTM Timer A Prescaler Snapshot
#define TIMER_TAPS_PSS_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPS register.
//
//*****************************************************************************
#define TIMER_TBPS_PSS_M        0x0000FFFF  // GPTM Timer A Prescaler Value
#define TIMER_TBPS_PSS_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_DMAEV register.
//
//*****************************************************************************
#define TIMER_DMAEV_TBMDMAEN    0x00000800  // GPTM B Mode Match Event DMA
// Trigger Enable
#define TIMER_DMAEV_CBEDMAEN    0x00000400  // GPTM B Capture Event DMA Trigger
// Enable
#define TIMER_DMAEV_CBMDMAEN    0x00000200  // GPTM B Capture Match Event DMA
// Trigger Enable
#define TIMER_DMAEV_TBTODMAEN   0x00000100  // GPTM B Time-Out Event DMA
// Trigger Enable
#define TIMER_DMAEV_TAMDMAEN    0x00000010  // GPTM A Mode Match Event DMA
// Trigger Enable
#define TIMER_DMAEV_RTCDMAEN    0x00000008  // GPTM A RTC Match Event DMA
// Trigger Enable
#define TIMER_DMAEV_CAEDMAEN    0x00000004  // GPTM A Capture Event DMA Trigger
// Enable
#define TIMER_DMAEV_CAMDMAEN    0x00000002  // GPTM A Capture Match Event DMA
// Trigger Enable
#define TIMER_DMAEV_TATODMAEN   0x00000001  // GPTM A Time-Out Event DMA
// Trigger Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_ADCEV register.
//
//*****************************************************************************
#define TIMER_ADCEV_TBMADCEN    0x00000800  // GPTM B Mode Match Event ADC
// Trigger Enable
#define TIMER_ADCEV_CBEADCEN    0x00000400  // GPTM B Capture Event ADC Trigger
// Enable
#define TIMER_ADCEV_CBMADCEN    0x00000200  // GPTM B Capture Match Event ADC
// Trigger Enable
#define TIMER_ADCEV_TBTOADCEN   0x00000100  // GPTM B Time-Out Event ADC
// Trigger Enable
#define TIMER_ADCEV_TAMADCEN    0x00000010  // GPTM A Mode Match Event ADC
// Trigger Enable
#define TIMER_ADCEV_RTCADCEN    0x00000008  // GPTM RTC Match Event ADC Trigger
// Enable
#define TIMER_ADCEV_CAEADCEN    0x00000004  // GPTM A Capture Event ADC Trigger
// Enable
#define TIMER_ADCEV_CAMADCEN    0x00000002  // GPTM A Capture Match Event ADC
// Trigger Enable
#define TIMER_ADCEV_TATOADCEN   0x00000001  // GPTM A Time-Out Event ADC
// Trigger Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_PP register.
//
//*****************************************************************************
#define TIMER_PP_SYNCCNT        0x00000020  // Synchronize Start
#define TIMER_PP_CHAIN          0x00000010  // Chain with Other Timers
#define TIMER_PP_SIZE_M         0x0000000F  // Count Size
#define TIMER_PP_SIZE_16        0x00000000  // Timer A and Timer B counters are
// 16 bits each with an 8-bit
// prescale counter
#define TIMER_PP_SIZE_32        0x00000001  // Timer A and Timer B counters are
// 32 bits each with a 16-bit
// prescale counter

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_ACTSS register.
//
//*****************************************************************************
#define ADC_ACTSS_BUSY          0x00010000  // ADC Busy
#define ADC_ACTSS_ADEN3         0x00000800  // ADC SS3 DMA Enable
#define ADC_ACTSS_ADEN2         0x00000400  // ADC SS2 DMA Enable
#define ADC_ACTSS_ADEN1         0x00000200  // ADC SS1 DMA Enable
#define ADC_ACTSS_ADEN0         0x00000100  // ADC SS1 DMA Enable
#define ADC_ACTSS_ASEN3         0x00000008  // ADC SS3 Enable
#define ADC_ACTSS_ASEN2         0x00000004  // ADC SS2 Enable
#define ADC_ACTSS_ASEN1         0x00000002  // ADC SS1 Enable
#define ADC_ACTSS_ASEN0         0x00000001  // ADC SS0 Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_RIS register.
//
//*****************************************************************************
#define ADC_RIS_INRDC           0x00010000  // Digital Comparator Raw Interrupt
// Status
#define ADC_RIS_DMAINR3         0x00000800  // SS3 DMA Raw Interrupt Status
#define ADC_RIS_DMAINR2         0x00000400  // SS2 DMA Raw Interrupt Status
#define ADC_RIS_DMAINR1         0x00000200  // SS1 DMA Raw Interrupt Status
#define ADC_RIS_DMAINR0         0x00000100  // SS0 DMA Raw Interrupt Status
#define ADC_RIS_INR3            0x00000008  // SS3 Raw Interrupt Status
#define ADC_RIS_INR2            0x00000004  // SS2 Raw Interrupt Status
#define ADC_RIS_INR1            0x00000002  // SS1 Raw Interrupt Status
#define ADC_RIS_INR0            0x00000001  // SS0 Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_IM register.
//
//*****************************************************************************
#define ADC_IM_DCONSS3          0x00080000  // Digital Comparator Interrupt on
// SS3
#define ADC_IM_DCONSS2          0x00040000  // Digital Comparator Interrupt on
// SS2
#define ADC_IM_DCONSS1          0x00020000  // Digital Comparator Interrupt on
// SS1
#define ADC_IM_DCONSS0          0x00010000  // Digital Comparator Interrupt on
// SS0
#define ADC_IM_DMAMASK3         0x00000800  // SS3 DMA Interrupt Mask
#define ADC_IM_DMAMASK2         0x00000400  // SS2 DMA Interrupt Mask
#define ADC_IM_DMAMASK1         0x00000200  // SS1 DMA Interrupt Mask
#define ADC_IM_DMAMASK0         0x00000100  // SS0 DMA Interrupt Mask
#define ADC_IM_MASK3            0x00000008  // SS3 Interrupt Mask
#define ADC_IM_MASK2            0x00000004  // SS2 Interrupt Mask
#define ADC_IM_MASK1            0x00000002  // SS1 Interrupt Mask
#define ADC_IM_MASK0            0x00000001  // SS0 Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_ISC register.
//
//*****************************************************************************
#define ADC_ISC_DCINSS3         0x00080000  // Digital Comparator Interrupt
// Status on SS3
#define ADC_ISC_DCINSS2         0x00040000  // Digital Comparator Interrupt
// Status on SS2
#define ADC_ISC_DCINSS1         0x00020000  // Digital Comparator Interrupt
// Status on SS1
#define ADC_ISC_DCINSS0         0x00010000  // Digital Comparator Interrupt
// Status on SS0
#define ADC_ISC_DMAIN3          0x00000800  // SS3 DMA Interrupt Status and
// Clear
#define ADC_ISC_DMAIN2          0x00000400  // SS2 DMA Interrupt Status and
// Clear
#define ADC_ISC_DMAIN1          0x00000200  // SS1 DMA Interrupt Status and
// Clear
#define ADC_ISC_DMAIN0          0x00000100  // SS0 DMA Interrupt Status and
// Clear
#define ADC_ISC_IN3             0x00000008  // SS3 Interrupt Status and Clear
#define ADC_ISC_IN2             0x00000004  // SS2 Interrupt Status and Clear
#define ADC_ISC_IN1             0x00000002  // SS1 Interrupt Status and Clear
#define ADC_ISC_IN0             0x00000001  // SS0 Interrupt Status and Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_OSTAT register.
//
//*****************************************************************************
#define ADC_OSTAT_OV3           0x00000008  // SS3 FIFO Overflow
#define ADC_OSTAT_OV2           0x00000004  // SS2 FIFO Overflow
#define ADC_OSTAT_OV1           0x00000002  // SS1 FIFO Overflow
#define ADC_OSTAT_OV0           0x00000001  // SS0 FIFO Overflow

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_EMUX register.
//
//*****************************************************************************
#define ADC_EMUX_EM3_M          0x0000F000  // SS3 Trigger Select
#define ADC_EMUX_EM3_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM3_COMP0      0x00001000  // Analog Comparator 0
#define ADC_EMUX_EM3_COMP1      0x00002000  // Analog Comparator 1
#define ADC_EMUX_EM3_COMP2      0x00003000  // Analog Comparator 2
#define ADC_EMUX_EM3_EXTERNAL   0x00004000  // External (GPIO Pins)
#define ADC_EMUX_EM3_TIMER      0x00005000  // Timer
#define ADC_EMUX_EM3_PWM0       0x00006000  // PWM generator 0
#define ADC_EMUX_EM3_PWM1       0x00007000  // PWM generator 1
#define ADC_EMUX_EM3_PWM2       0x00008000  // PWM generator 2
#define ADC_EMUX_EM3_PWM3       0x00009000  // PWM generator 3
#define ADC_EMUX_EM3_NEVER      0x0000E000  // Never Trigger
#define ADC_EMUX_EM3_ALWAYS     0x0000F000  // Always (continuously sample)
#define ADC_EMUX_EM2_M          0x00000F00  // SS2 Trigger Select
#define ADC_EMUX_EM2_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM2_COMP0      0x00000100  // Analog Comparator 0
#define ADC_EMUX_EM2_COMP1      0x00000200  // Analog Comparator 1
#define ADC_EMUX_EM2_COMP2      0x00000300  // Analog Comparator 2
#define ADC_EMUX_EM2_EXTERNAL   0x00000400  // External (GPIO Pins)
#define ADC_EMUX_EM2_TIMER      0x00000500  // Timer
#define ADC_EMUX_EM2_PWM0       0x00000600  // PWM generator 0
#define ADC_EMUX_EM2_PWM1       0x00000700  // PWM generator 1
#define ADC_EMUX_EM2_PWM2       0x00000800  // PWM generator 2
#define ADC_EMUX_EM2_PWM3       0x00000900  // PWM generator 3
#define ADC_EMUX_EM2_NEVER      0x00000E00  // Never Trigger
#define ADC_EMUX_EM2_ALWAYS     0x00000F00  // Always (continuously sample)
#define ADC_EMUX_EM1_M          0x000000F0  // SS1 Trigger Select
#define ADC_EMUX_EM1_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM1_COMP0      0x00000010  // Analog Comparator 0
#define ADC_EMUX_EM1_COMP1      0x00000020  // Analog Comparator 1
#define ADC_EMUX_EM1_COMP2      0x00000030  // Analog Comparator 2
#define ADC_EMUX_EM1_EXTERNAL   0x00000040  // External (GPIO Pins)
#define ADC_EMUX_EM1_TIMER      0x00000050  // Timer
#define ADC_EMUX_EM1_PWM0       0x00000060  // PWM generator 0
#define ADC_EMUX_EM1_PWM1       0x00000070  // PWM generator 1
#define ADC_EMUX_EM1_PWM2       0x00000080  // PWM generator 2
#define ADC_EMUX_EM1_PWM3       0x00000090  // PWM generator 3
#define ADC_EMUX_EM1_NEVER      0x000000E0  // Never Trigger
#define ADC_EMUX_EM1_ALWAYS     0x000000F0  // Always (continuously sample)
#define ADC_EMUX_EM0_M          0x0000000F  // SS0 Trigger Select
#define ADC_EMUX_EM0_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM0_COMP0      0x00000001  // Analog Comparator 0
#define ADC_EMUX_EM0_COMP1      0x00000002  // Analog Comparator 1
#define ADC_EMUX_EM0_COMP2      0x00000003  // Analog Comparator 2
#define ADC_EMUX_EM0_EXTERNAL   0x00000004  // External (GPIO Pins)
#define ADC_EMUX_EM0_TIMER      0x00000005  // Timer
#define ADC_EMUX_EM0_PWM0       0x00000006  // PWM generator 0
#define ADC_EMUX_EM0_PWM1       0x00000007  // PWM generator 1
#define ADC_EMUX_EM0_PWM2       0x00000008  // PWM generator 2
#define ADC_EMUX_EM0_PWM3       0x00000009  // PWM generator 3
#define ADC_EMUX_EM0_NEVER      0x0000000E  // Never Trigger
#define ADC_EMUX_EM0_ALWAYS     0x0000000F  // Always (continuously sample)

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_USTAT register.
//
//*****************************************************************************
#define ADC_USTAT_UV3           0x00000008  // SS3 FIFO Underflow
#define ADC_USTAT_UV2           0x00000004  // SS2 FIFO Underflow
#define ADC_USTAT_UV1           0x00000002  // SS1 FIFO Underflow
#define ADC_USTAT_UV0           0x00000001  // SS0 FIFO Underflow

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_TSSEL register.
//
//*****************************************************************************
#define ADC_TSSEL_PS3_M         0x30000000  // Generator 3 PWM Module Trigger
// Select
#define ADC_TSSEL_PS3_0         0x00000000  // Use Generator 3 (and its
// trigger) in PWM module 0
#define ADC_TSSEL_PS2_M         0x00300000  // Generator 2 PWM Module Trigger
// Select
#define ADC_TSSEL_PS2_0         0x00000000  // Use Generator 2 (and its
// trigger) in PWM module 0
#define ADC_TSSEL_PS1_M         0x00003000  // Generator 1 PWM Module Trigger
// Select
#define ADC_TSSEL_PS1_0         0x00000000  // Use Generator 1 (and its
// trigger) in PWM module 0
#define ADC_TSSEL_PS0_M         0x00000030  // Generator 0 PWM Module Trigger
// Select
#define ADC_TSSEL_PS0_0         0x00000000  // Use Generator 0 (and its
// trigger) in PWM module 0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSPRI register.
//
//*****************************************************************************
#define ADC_SSPRI_SS3_M         0x00003000  // SS3 Priority
#define ADC_SSPRI_SS2_M         0x00000300  // SS2 Priority
#define ADC_SSPRI_SS1_M         0x00000030  // SS1 Priority
#define ADC_SSPRI_SS0_M         0x00000003  // SS0 Priority

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SPC register.
//
//*****************************************************************************
#define ADC_SPC_PHASE_M         0x0000000F  // Phase Difference
#define ADC_SPC_PHASE_0         0x00000000  // ADC sample lags by 0.0
#define ADC_SPC_PHASE_22_5      0x00000001  // ADC sample lags by 22.5
#define ADC_SPC_PHASE_45        0x00000002  // ADC sample lags by 45.0
#define ADC_SPC_PHASE_67_5      0x00000003  // ADC sample lags by 67.5
#define ADC_SPC_PHASE_90        0x00000004  // ADC sample lags by 90.0
#define ADC_SPC_PHASE_112_5     0x00000005  // ADC sample lags by 112.5
#define ADC_SPC_PHASE_135       0x00000006  // ADC sample lags by 135.0
#define ADC_SPC_PHASE_157_5     0x00000007  // ADC sample lags by 157.5
#define ADC_SPC_PHASE_180       0x00000008  // ADC sample lags by 180.0
#define ADC_SPC_PHASE_202_5     0x00000009  // ADC sample lags by 202.5
#define ADC_SPC_PHASE_225       0x0000000A  // ADC sample lags by 225.0
#define ADC_SPC_PHASE_247_5     0x0000000B  // ADC sample lags by 247.5
#define ADC_SPC_PHASE_270       0x0000000C  // ADC sample lags by 270.0
#define ADC_SPC_PHASE_292_5     0x0000000D  // ADC sample lags by 292.5
#define ADC_SPC_PHASE_315       0x0000000E  // ADC sample lags by 315.0
#define ADC_SPC_PHASE_337_5     0x0000000F  // ADC sample lags by 337.5

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_PSSI register.
//
//*****************************************************************************
#define ADC_PSSI_GSYNC          0x80000000  // Global Synchronize
#define ADC_PSSI_SYNCWAIT       0x08000000  // Synchronize Wait
#define ADC_PSSI_SS3            0x00000008  // SS3 Initiate
#define ADC_PSSI_SS2            0x00000004  // SS2 Initiate
#define ADC_PSSI_SS1            0x00000002  // SS1 Initiate
#define ADC_PSSI_SS0            0x00000001  // SS0 Initiate

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SAC register.
//
//*****************************************************************************
#define ADC_SAC_AVG_M           0x00000007  // Hardware Averaging Control
#define ADC_SAC_AVG_OFF         0x00000000  // No hardware oversampling
#define ADC_SAC_AVG_2X          0x00000001  // 2x hardware oversampling
#define ADC_SAC_AVG_4X          0x00000002  // 4x hardware oversampling
#define ADC_SAC_AVG_8X          0x00000003  // 8x hardware oversampling
#define ADC_SAC_AVG_16X         0x00000004  // 16x hardware oversampling
#define ADC_SAC_AVG_32X         0x00000005  // 32x hardware oversampling
#define ADC_SAC_AVG_64X         0x00000006  // 64x hardware oversampling

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCISC register.
//
//*****************************************************************************
#define ADC_DCISC_DCINT7        0x00000080  // Digital Comparator 7 Interrupt
// Status and Clear
#define ADC_DCISC_DCINT6        0x00000040  // Digital Comparator 6 Interrupt
// Status and Clear
#define ADC_DCISC_DCINT5        0x00000020  // Digital Comparator 5 Interrupt
// Status and Clear
#define ADC_DCISC_DCINT4        0x00000010  // Digital Comparator 4 Interrupt
// Status and Clear
#define ADC_DCISC_DCINT3        0x00000008  // Digital Comparator 3 Interrupt
// Status and Clear
#define ADC_DCISC_DCINT2        0x00000004  // Digital Comparator 2 Interrupt
// Status and Clear
#define ADC_DCISC_DCINT1        0x00000002  // Digital Comparator 1 Interrupt
// Status and Clear
#define ADC_DCISC_DCINT0        0x00000001  // Digital Comparator 0 Interrupt
// Status and Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_CTL register.
//
//*****************************************************************************
#define ADC_CTL_VREF_M          0x00000001  // Voltage Reference Select
#define ADC_CTL_VREF_INTERNAL   0x00000000  // VDDA and GNDA are the voltage
// references
#define ADC_CTL_VREF_EXT_3V     0x00000001  // The external VREFA+ and VREFA-
// inputs are the voltage
// references

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSMUX0 register.
//
//*****************************************************************************
#define ADC_SSMUX0_MUX7_M       0xF0000000  // 8th Sample Input Select
#define ADC_SSMUX0_MUX6_M       0x0F000000  // 7th Sample Input Select
#define ADC_SSMUX0_MUX5_M       0x00F00000  // 6th Sample Input Select
#define ADC_SSMUX0_MUX4_M       0x000F0000  // 5th Sample Input Select
#define ADC_SSMUX0_MUX3_M       0x0000F000  // 4th Sample Input Select
#define ADC_SSMUX0_MUX2_M       0x00000F00  // 3rd Sample Input Select
#define ADC_SSMUX0_MUX1_M       0x000000F0  // 2nd Sample Input Select
#define ADC_SSMUX0_MUX0_M       0x0000000F  // 1st Sample Input Select
#define ADC_SSMUX0_MUX7_S       28
#define ADC_SSMUX0_MUX6_S       24
#define ADC_SSMUX0_MUX5_S       20
#define ADC_SSMUX0_MUX4_S       16
#define ADC_SSMUX0_MUX3_S       12
#define ADC_SSMUX0_MUX2_S       8
#define ADC_SSMUX0_MUX1_S       4
#define ADC_SSMUX0_MUX0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL0 register.
//
//*****************************************************************************
#define ADC_SSCTL0_TS7          0x80000000  // 8th Sample Temp Sensor Select
#define ADC_SSCTL0_IE7          0x40000000  // 8th Sample Interrupt Enable
#define ADC_SSCTL0_END7         0x20000000  // 8th Sample is End of Sequence
#define ADC_SSCTL0_D7           0x10000000  // 8th Sample Differential Input
// Select
#define ADC_SSCTL0_TS6          0x08000000  // 7th Sample Temp Sensor Select
#define ADC_SSCTL0_IE6          0x04000000  // 7th Sample Interrupt Enable
#define ADC_SSCTL0_END6         0x02000000  // 7th Sample is End of Sequence
#define ADC_SSCTL0_D6           0x01000000  // 7th Sample Differential Input
// Select
#define ADC_SSCTL0_TS5          0x00800000  // 6th Sample Temp Sensor Select
#define ADC_SSCTL0_IE5          0x00400000  // 6th Sample Interrupt Enable
#define ADC_SSCTL0_END5         0x00200000  // 6th Sample is End of Sequence
#define ADC_SSCTL0_D5           0x00100000  // 6th Sample Differential Input
// Select
#define ADC_SSCTL0_TS4          0x00080000  // 5th Sample Temp Sensor Select
#define ADC_SSCTL0_IE4          0x00040000  // 5th Sample Interrupt Enable
#define ADC_SSCTL0_END4         0x00020000  // 5th Sample is End of Sequence
#define ADC_SSCTL0_D4           0x00010000  // 5th Sample Differential Input
// Select
#define ADC_SSCTL0_TS3          0x00008000  // 4th Sample Temp Sensor Select
#define ADC_SSCTL0_IE3          0x00004000  // 4th Sample Interrupt Enable
#define ADC_SSCTL0_END3         0x00002000  // 4th Sample is End of Sequence
#define ADC_SSCTL0_D3           0x00001000  // 4th Sample Differential Input
// Select
#define ADC_SSCTL0_TS2          0x00000800  // 3rd Sample Temp Sensor Select
#define ADC_SSCTL0_IE2          0x00000400  // 3rd Sample Interrupt Enable
#define ADC_SSCTL0_END2         0x00000200  // 3rd Sample is End of Sequence
#define ADC_SSCTL0_D2           0x00000100  // 3rd Sample Differential Input
// Select
#define ADC_SSCTL0_TS1          0x00000080  // 2nd Sample Temp Sensor Select
#define ADC_SSCTL0_IE1          0x00000040  // 2nd Sample Interrupt Enable
#define ADC_SSCTL0_END1         0x00000020  // 2nd Sample is End of Sequence
#define ADC_SSCTL0_D1           0x00000010  // 2nd Sample Differential Input
// Select
#define ADC_SSCTL0_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL0_IE0          0x00000004  // 1st Sample Interrupt Enable
#define ADC_SSCTL0_END0         0x00000002  // 1st Sample is End of Sequence
#define ADC_SSCTL0_D0           0x00000001  // 1st Sample Differential Input
// Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFIFO0 register.
//
//*****************************************************************************
#define ADC_SSFIFO0_DATA_M      0x00000FFF  // Conversion Result Data
#define ADC_SSFIFO0_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFSTAT0 register.
//
//*****************************************************************************
#define ADC_SSFSTAT0_FULL       0x00001000  // FIFO Full
#define ADC_SSFSTAT0_EMPTY      0x00000100  // FIFO Empty
#define ADC_SSFSTAT0_HPTR_M     0x000000F0  // FIFO Head Pointer
#define ADC_SSFSTAT0_TPTR_M     0x0000000F  // FIFO Tail Pointer
#define ADC_SSFSTAT0_HPTR_S     4
#define ADC_SSFSTAT0_TPTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSOP0 register.
//
//*****************************************************************************
#define ADC_SSOP0_S7DCOP        0x10000000  // Sample 7 Digital Comparator
// Operation
#define ADC_SSOP0_S6DCOP        0x01000000  // Sample 6 Digital Comparator
// Operation
#define ADC_SSOP0_S5DCOP        0x00100000  // Sample 5 Digital Comparator
// Operation
#define ADC_SSOP0_S4DCOP        0x00010000  // Sample 4 Digital Comparator
// Operation
#define ADC_SSOP0_S3DCOP        0x00001000  // Sample 3 Digital Comparator
// Operation
#define ADC_SSOP0_S2DCOP        0x00000100  // Sample 2 Digital Comparator
// Operation
#define ADC_SSOP0_S1DCOP        0x00000010  // Sample 1 Digital Comparator
// Operation
#define ADC_SSOP0_S0DCOP        0x00000001  // Sample 0 Digital Comparator
// Operation

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSDC0 register.
//
//*****************************************************************************
#define ADC_SSDC0_S7DCSEL_M     0xF0000000  // Sample 7 Digital Comparator
// Select
#define ADC_SSDC0_S6DCSEL_M     0x0F000000  // Sample 6 Digital Comparator
// Select
#define ADC_SSDC0_S5DCSEL_M     0x00F00000  // Sample 5 Digital Comparator
// Select
#define ADC_SSDC0_S4DCSEL_M     0x000F0000  // Sample 4 Digital Comparator
// Select
#define ADC_SSDC0_S3DCSEL_M     0x0000F000  // Sample 3 Digital Comparator
// Select
#define ADC_SSDC0_S2DCSEL_M     0x00000F00  // Sample 2 Digital Comparator
// Select
#define ADC_SSDC0_S1DCSEL_M     0x000000F0  // Sample 1 Digital Comparator
// Select
#define ADC_SSDC0_S0DCSEL_M     0x0000000F  // Sample 0 Digital Comparator
// Select
#define ADC_SSDC0_S6DCSEL_S     24
#define ADC_SSDC0_S5DCSEL_S     20
#define ADC_SSDC0_S4DCSEL_S     16
#define ADC_SSDC0_S3DCSEL_S     12
#define ADC_SSDC0_S2DCSEL_S     8
#define ADC_SSDC0_S1DCSEL_S     4
#define ADC_SSDC0_S0DCSEL_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSEMUX0 register.
//
//*****************************************************************************
#define ADC_SSEMUX0_EMUX7       0x10000000  // 8th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX0_EMUX6       0x01000000  // 7th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX0_EMUX5       0x00100000  // 6th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX0_EMUX4       0x00010000  // 5th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX0_EMUX3       0x00001000  // 4th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX0_EMUX2       0x00000100  // 3rd Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX0_EMUX1       0x00000010  // 2th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX0_EMUX0       0x00000001  // 1st Sample Input Select (Upper
// Bit)

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSTSH0 register.
//
//*****************************************************************************
#define ADC_SSTSH0_TSH7_M       0xF0000000  // 8th Sample and Hold Period
// Select
#define ADC_SSTSH0_TSH6_M       0x0F000000  // 7th Sample and Hold Period
// Select
#define ADC_SSTSH0_TSH5_M       0x00F00000  // 6th Sample and Hold Period
// Select
#define ADC_SSTSH0_TSH4_M       0x000F0000  // 5th Sample and Hold Period
// Select
#define ADC_SSTSH0_TSH3_M       0x0000F000  // 4th Sample and Hold Period
// Select
#define ADC_SSTSH0_TSH2_M       0x00000F00  // 3rd Sample and Hold Period
// Select
#define ADC_SSTSH0_TSH1_M       0x000000F0  // 2nd Sample and Hold Period
// Select
#define ADC_SSTSH0_TSH0_M       0x0000000F  // 1st Sample and Hold Period
// Select
#define ADC_SSTSH0_TSH7_S       28
#define ADC_SSTSH0_TSH6_S       24
#define ADC_SSTSH0_TSH5_S       20
#define ADC_SSTSH0_TSH4_S       16
#define ADC_SSTSH0_TSH3_S       12
#define ADC_SSTSH0_TSH2_S       8
#define ADC_SSTSH0_TSH1_S       4
#define ADC_SSTSH0_TSH0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSMUX1 register.
//
//*****************************************************************************
#define ADC_SSMUX1_MUX3_M       0x0000F000  // 4th Sample Input Select
#define ADC_SSMUX1_MUX2_M       0x00000F00  // 3rd Sample Input Select
#define ADC_SSMUX1_MUX1_M       0x000000F0  // 2nd Sample Input Select
#define ADC_SSMUX1_MUX0_M       0x0000000F  // 1st Sample Input Select
#define ADC_SSMUX1_MUX3_S       12
#define ADC_SSMUX1_MUX2_S       8
#define ADC_SSMUX1_MUX1_S       4
#define ADC_SSMUX1_MUX0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL1 register.
//
//*****************************************************************************
#define ADC_SSCTL1_TS3          0x00008000  // 4th Sample Temp Sensor Select
#define ADC_SSCTL1_IE3          0x00004000  // 4th Sample Interrupt Enable
#define ADC_SSCTL1_END3         0x00002000  // 4th Sample is End of Sequence
#define ADC_SSCTL1_D3           0x00001000  // 4th Sample Differential Input
// Select
#define ADC_SSCTL1_TS2          0x00000800  // 3rd Sample Temp Sensor Select
#define ADC_SSCTL1_IE2          0x00000400  // 3rd Sample Interrupt Enable
#define ADC_SSCTL1_END2         0x00000200  // 3rd Sample is End of Sequence
#define ADC_SSCTL1_D2           0x00000100  // 3rd Sample Differential Input
// Select
#define ADC_SSCTL1_TS1          0x00000080  // 2nd Sample Temp Sensor Select
#define ADC_SSCTL1_IE1          0x00000040  // 2nd Sample Interrupt Enable
#define ADC_SSCTL1_END1         0x00000020  // 2nd Sample is End of Sequence
#define ADC_SSCTL1_D1           0x00000010  // 2nd Sample Differential Input
// Select
#define ADC_SSCTL1_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL1_IE0          0x00000004  // 1st Sample Interrupt Enable
#define ADC_SSCTL1_END0         0x00000002  // 1st Sample is End of Sequence
#define ADC_SSCTL1_D0           0x00000001  // 1st Sample Differential Input
// Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFIFO1 register.
//
//*****************************************************************************
#define ADC_SSFIFO1_DATA_M      0x00000FFF  // Conversion Result Data
#define ADC_SSFIFO1_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFSTAT1 register.
//
//*****************************************************************************
#define ADC_SSFSTAT1_FULL       0x00001000  // FIFO Full
#define ADC_SSFSTAT1_EMPTY      0x00000100  // FIFO Empty
#define ADC_SSFSTAT1_HPTR_M     0x000000F0  // FIFO Head Pointer
#define ADC_SSFSTAT1_TPTR_M     0x0000000F  // FIFO Tail Pointer
#define ADC_SSFSTAT1_HPTR_S     4
#define ADC_SSFSTAT1_TPTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSOP1 register.
//
//*****************************************************************************
#define ADC_SSOP1_S3DCOP        0x00001000  // Sample 3 Digital Comparator
// Operation
#define ADC_SSOP1_S2DCOP        0x00000100  // Sample 2 Digital Comparator
// Operation
#define ADC_SSOP1_S1DCOP        0x00000010  // Sample 1 Digital Comparator
// Operation
#define ADC_SSOP1_S0DCOP        0x00000001  // Sample 0 Digital Comparator
// Operation

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSDC1 register.
//
//*****************************************************************************
#define ADC_SSDC1_S3DCSEL_M     0x0000F000  // Sample 3 Digital Comparator
// Select
#define ADC_SSDC1_S2DCSEL_M     0x00000F00  // Sample 2 Digital Comparator
// Select
#define ADC_SSDC1_S1DCSEL_M     0x000000F0  // Sample 1 Digital Comparator
// Select
#define ADC_SSDC1_S0DCSEL_M     0x0000000F  // Sample 0 Digital Comparator
// Select
#define ADC_SSDC1_S2DCSEL_S     8
#define ADC_SSDC1_S1DCSEL_S     4
#define ADC_SSDC1_S0DCSEL_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSEMUX1 register.
//
//*****************************************************************************
#define ADC_SSEMUX1_EMUX3       0x00001000  // 4th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX1_EMUX2       0x00000100  // 3rd Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX1_EMUX1       0x00000010  // 2th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX1_EMUX0       0x00000001  // 1st Sample Input Select (Upper
// Bit)

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSTSH1 register.
//
//*****************************************************************************
#define ADC_SSTSH1_TSH3_M       0x0000F000  // 4th Sample and Hold Period
// Select
#define ADC_SSTSH1_TSH2_M       0x00000F00  // 3rd Sample and Hold Period
// Select
#define ADC_SSTSH1_TSH1_M       0x000000F0  // 2nd Sample and Hold Period
// Select
#define ADC_SSTSH1_TSH0_M       0x0000000F  // 1st Sample and Hold Period
// Select
#define ADC_SSTSH1_TSH3_S       12
#define ADC_SSTSH1_TSH2_S       8
#define ADC_SSTSH1_TSH1_S       4
#define ADC_SSTSH1_TSH0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSMUX2 register.
//
//*****************************************************************************
#define ADC_SSMUX2_MUX3_M       0x0000F000  // 4th Sample Input Select
#define ADC_SSMUX2_MUX2_M       0x00000F00  // 3rd Sample Input Select
#define ADC_SSMUX2_MUX1_M       0x000000F0  // 2nd Sample Input Select
#define ADC_SSMUX2_MUX0_M       0x0000000F  // 1st Sample Input Select
#define ADC_SSMUX2_MUX3_S       12
#define ADC_SSMUX2_MUX2_S       8
#define ADC_SSMUX2_MUX1_S       4
#define ADC_SSMUX2_MUX0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL2 register.
//
//*****************************************************************************
#define ADC_SSCTL2_TS3          0x00008000  // 4th Sample Temp Sensor Select
#define ADC_SSCTL2_IE3          0x00004000  // 4th Sample Interrupt Enable
#define ADC_SSCTL2_END3         0x00002000  // 4th Sample is End of Sequence
#define ADC_SSCTL2_D3           0x00001000  // 4th Sample Differential Input
// Select
#define ADC_SSCTL2_TS2          0x00000800  // 3rd Sample Temp Sensor Select
#define ADC_SSCTL2_IE2          0x00000400  // 3rd Sample Interrupt Enable
#define ADC_SSCTL2_END2         0x00000200  // 3rd Sample is End of Sequence
#define ADC_SSCTL2_D2           0x00000100  // 3rd Sample Differential Input
// Select
#define ADC_SSCTL2_TS1          0x00000080  // 2nd Sample Temp Sensor Select
#define ADC_SSCTL2_IE1          0x00000040  // 2nd Sample Interrupt Enable
#define ADC_SSCTL2_END1         0x00000020  // 2nd Sample is End of Sequence
#define ADC_SSCTL2_D1           0x00000010  // 2nd Sample Differential Input
// Select
#define ADC_SSCTL2_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL2_IE0          0x00000004  // 1st Sample Interrupt Enable
#define ADC_SSCTL2_END0         0x00000002  // 1st Sample is End of Sequence
#define ADC_SSCTL2_D0           0x00000001  // 1st Sample Differential Input
// Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFIFO2 register.
//
//*****************************************************************************
#define ADC_SSFIFO2_DATA_M      0x00000FFF  // Conversion Result Data
#define ADC_SSFIFO2_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFSTAT2 register.
//
//*****************************************************************************
#define ADC_SSFSTAT2_FULL       0x00001000  // FIFO Full
#define ADC_SSFSTAT2_EMPTY      0x00000100  // FIFO Empty
#define ADC_SSFSTAT2_HPTR_M     0x000000F0  // FIFO Head Pointer
#define ADC_SSFSTAT2_TPTR_M     0x0000000F  // FIFO Tail Pointer
#define ADC_SSFSTAT2_HPTR_S     4
#define ADC_SSFSTAT2_TPTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSOP2 register.
//
//*****************************************************************************
#define ADC_SSOP2_S3DCOP        0x00001000  // Sample 3 Digital Comparator
// Operation
#define ADC_SSOP2_S2DCOP        0x00000100  // Sample 2 Digital Comparator
// Operation
#define ADC_SSOP2_S1DCOP        0x00000010  // Sample 1 Digital Comparator
// Operation
#define ADC_SSOP2_S0DCOP        0x00000001  // Sample 0 Digital Comparator
// Operation

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSDC2 register.
//
//*****************************************************************************
#define ADC_SSDC2_S3DCSEL_M     0x0000F000  // Sample 3 Digital Comparator
// Select
#define ADC_SSDC2_S2DCSEL_M     0x00000F00  // Sample 2 Digital Comparator
// Select
#define ADC_SSDC2_S1DCSEL_M     0x000000F0  // Sample 1 Digital Comparator
// Select
#define ADC_SSDC2_S0DCSEL_M     0x0000000F  // Sample 0 Digital Comparator
// Select
#define ADC_SSDC2_S2DCSEL_S     8
#define ADC_SSDC2_S1DCSEL_S     4
#define ADC_SSDC2_S0DCSEL_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSEMUX2 register.
//
//*****************************************************************************
#define ADC_SSEMUX2_EMUX3       0x00001000  // 4th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX2_EMUX2       0x00000100  // 3rd Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX2_EMUX1       0x00000010  // 2th Sample Input Select (Upper
// Bit)
#define ADC_SSEMUX2_EMUX0       0x00000001  // 1st Sample Input Select (Upper
// Bit)

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSTSH2 register.
//
//*****************************************************************************
#define ADC_SSTSH2_TSH3_M       0x0000F000  // 4th Sample and Hold Period
// Select
#define ADC_SSTSH2_TSH2_M       0x00000F00  // 3rd Sample and Hold Period
// Select
#define ADC_SSTSH2_TSH1_M       0x000000F0  // 2nd Sample and Hold Period
// Select
#define ADC_SSTSH2_TSH0_M       0x0000000F  // 1st Sample and Hold Period
// Select
#define ADC_SSTSH2_TSH3_S       12
#define ADC_SSTSH2_TSH2_S       8
#define ADC_SSTSH2_TSH1_S       4
#define ADC_SSTSH2_TSH0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSMUX3 register.
//
//*****************************************************************************
#define ADC_SSMUX3_MUX0_M       0x0000000F  // 1st Sample Input Select
#define ADC_SSMUX3_MUX0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL3 register.
//
//*****************************************************************************
#define ADC_SSCTL3_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL3_IE0          0x00000004  // Sample Interrupt Enable
#define ADC_SSCTL3_END0         0x00000002  // End of Sequence
#define ADC_SSCTL3_D0           0x00000001  // Sample Differential Input Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFIFO3 register.
//
//*****************************************************************************
#define ADC_SSFIFO3_DATA_M      0x00000FFF  // Conversion Result Data
#define ADC_SSFIFO3_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFSTAT3 register.
//
//*****************************************************************************
#define ADC_SSFSTAT3_FULL       0x00001000  // FIFO Full
#define ADC_SSFSTAT3_EMPTY      0x00000100  // FIFO Empty
#define ADC_SSFSTAT3_HPTR_M     0x000000F0  // FIFO Head Pointer
#define ADC_SSFSTAT3_TPTR_M     0x0000000F  // FIFO Tail Pointer
#define ADC_SSFSTAT3_HPTR_S     4
#define ADC_SSFSTAT3_TPTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSOP3 register.
//
//*****************************************************************************
#define ADC_SSOP3_S0DCOP        0x00000001  // Sample 0 Digital Comparator
// Operation

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSDC3 register.
//
//*****************************************************************************
#define ADC_SSDC3_S0DCSEL_M     0x0000000F  // Sample 0 Digital Comparator
// Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSEMUX3 register.
//
//*****************************************************************************
#define ADC_SSEMUX3_EMUX0       0x00000001  // 1st Sample Input Select (Upper
// Bit)

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSTSH3 register.
//
//*****************************************************************************
#define ADC_SSTSH3_TSH0_M       0x0000000F  // 1st Sample and Hold Period
// Select
#define ADC_SSTSH3_TSH0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCRIC register.
//
//*****************************************************************************
#define ADC_DCRIC_DCTRIG7       0x00800000  // Digital Comparator Trigger 7
#define ADC_DCRIC_DCTRIG6       0x00400000  // Digital Comparator Trigger 6
#define ADC_DCRIC_DCTRIG5       0x00200000  // Digital Comparator Trigger 5
#define ADC_DCRIC_DCTRIG4       0x00100000  // Digital Comparator Trigger 4
#define ADC_DCRIC_DCTRIG3       0x00080000  // Digital Comparator Trigger 3
#define ADC_DCRIC_DCTRIG2       0x00040000  // Digital Comparator Trigger 2
#define ADC_DCRIC_DCTRIG1       0x00020000  // Digital Comparator Trigger 1
#define ADC_DCRIC_DCTRIG0       0x00010000  // Digital Comparator Trigger 0
#define ADC_DCRIC_DCINT7        0x00000080  // Digital Comparator Interrupt 7
#define ADC_DCRIC_DCINT6        0x00000040  // Digital Comparator Interrupt 6
#define ADC_DCRIC_DCINT5        0x00000020  // Digital Comparator Interrupt 5
#define ADC_DCRIC_DCINT4        0x00000010  // Digital Comparator Interrupt 4
#define ADC_DCRIC_DCINT3        0x00000008  // Digital Comparator Interrupt 3
#define ADC_DCRIC_DCINT2        0x00000004  // Digital Comparator Interrupt 2
#define ADC_DCRIC_DCINT1        0x00000002  // Digital Comparator Interrupt 1
#define ADC_DCRIC_DCINT0        0x00000001  // Digital Comparator Interrupt 0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCTL0 register.
//
//*****************************************************************************
#define ADC_DCCTL0_CTE          0x00001000  // Comparison Trigger Enable
#define ADC_DCCTL0_CTC_M        0x00000C00  // Comparison Trigger Condition
#define ADC_DCCTL0_CTC_LOW      0x00000000  // Low Band
#define ADC_DCCTL0_CTC_MID      0x00000400  // Mid Band
#define ADC_DCCTL0_CTC_HIGH     0x00000C00  // High Band
#define ADC_DCCTL0_CTM_M        0x00000300  // Comparison Trigger Mode
#define ADC_DCCTL0_CTM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL0_CTM_ONCE     0x00000100  // Once
#define ADC_DCCTL0_CTM_HALWAYS  0x00000200  // Hysteresis Always
#define ADC_DCCTL0_CTM_HONCE    0x00000300  // Hysteresis Once
#define ADC_DCCTL0_CIE          0x00000010  // Comparison Interrupt Enable
#define ADC_DCCTL0_CIC_M        0x0000000C  // Comparison Interrupt Condition
#define ADC_DCCTL0_CIC_LOW      0x00000000  // Low Band
#define ADC_DCCTL0_CIC_MID      0x00000004  // Mid Band
#define ADC_DCCTL0_CIC_HIGH     0x0000000C  // High Band
#define ADC_DCCTL0_CIM_M        0x00000003  // Comparison Interrupt Mode
#define ADC_DCCTL0_CIM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL0_CIM_ONCE     0x00000001  // Once
#define ADC_DCCTL0_CIM_HALWAYS  0x00000002  // Hysteresis Always
#define ADC_DCCTL0_CIM_HONCE    0x00000003  // Hysteresis Once

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCTL1 register.
//
//*****************************************************************************
#define ADC_DCCTL1_CTE          0x00001000  // Comparison Trigger Enable
#define ADC_DCCTL1_CTC_M        0x00000C00  // Comparison Trigger Condition
#define ADC_DCCTL1_CTC_LOW      0x00000000  // Low Band
#define ADC_DCCTL1_CTC_MID      0x00000400  // Mid Band
#define ADC_DCCTL1_CTC_HIGH     0x00000C00  // High Band
#define ADC_DCCTL1_CTM_M        0x00000300  // Comparison Trigger Mode
#define ADC_DCCTL1_CTM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL1_CTM_ONCE     0x00000100  // Once
#define ADC_DCCTL1_CTM_HALWAYS  0x00000200  // Hysteresis Always
#define ADC_DCCTL1_CTM_HONCE    0x00000300  // Hysteresis Once
#define ADC_DCCTL1_CIE          0x00000010  // Comparison Interrupt Enable
#define ADC_DCCTL1_CIC_M        0x0000000C  // Comparison Interrupt Condition
#define ADC_DCCTL1_CIC_LOW      0x00000000  // Low Band
#define ADC_DCCTL1_CIC_MID      0x00000004  // Mid Band
#define ADC_DCCTL1_CIC_HIGH     0x0000000C  // High Band
#define ADC_DCCTL1_CIM_M        0x00000003  // Comparison Interrupt Mode
#define ADC_DCCTL1_CIM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL1_CIM_ONCE     0x00000001  // Once
#define ADC_DCCTL1_CIM_HALWAYS  0x00000002  // Hysteresis Always
#define ADC_DCCTL1_CIM_HONCE    0x00000003  // Hysteresis Once

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCTL2 register.
//
//*****************************************************************************
#define ADC_DCCTL2_CTE          0x00001000  // Comparison Trigger Enable
#define ADC_DCCTL2_CTC_M        0x00000C00  // Comparison Trigger Condition
#define ADC_DCCTL2_CTC_LOW      0x00000000  // Low Band
#define ADC_DCCTL2_CTC_MID      0x00000400  // Mid Band
#define ADC_DCCTL2_CTC_HIGH     0x00000C00  // High Band
#define ADC_DCCTL2_CTM_M        0x00000300  // Comparison Trigger Mode
#define ADC_DCCTL2_CTM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL2_CTM_ONCE     0x00000100  // Once
#define ADC_DCCTL2_CTM_HALWAYS  0x00000200  // Hysteresis Always
#define ADC_DCCTL2_CTM_HONCE    0x00000300  // Hysteresis Once
#define ADC_DCCTL2_CIE          0x00000010  // Comparison Interrupt Enable
#define ADC_DCCTL2_CIC_M        0x0000000C  // Comparison Interrupt Condition
#define ADC_DCCTL2_CIC_LOW      0x00000000  // Low Band
#define ADC_DCCTL2_CIC_MID      0x00000004  // Mid Band
#define ADC_DCCTL2_CIC_HIGH     0x0000000C  // High Band
#define ADC_DCCTL2_CIM_M        0x00000003  // Comparison Interrupt Mode
#define ADC_DCCTL2_CIM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL2_CIM_ONCE     0x00000001  // Once
#define ADC_DCCTL2_CIM_HALWAYS  0x00000002  // Hysteresis Always
#define ADC_DCCTL2_CIM_HONCE    0x00000003  // Hysteresis Once

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCTL3 register.
//
//*****************************************************************************
#define ADC_DCCTL3_CTE          0x00001000  // Comparison Trigger Enable
#define ADC_DCCTL3_CTC_M        0x00000C00  // Comparison Trigger Condition
#define ADC_DCCTL3_CTC_LOW      0x00000000  // Low Band
#define ADC_DCCTL3_CTC_MID      0x00000400  // Mid Band
#define ADC_DCCTL3_CTC_HIGH     0x00000C00  // High Band
#define ADC_DCCTL3_CTM_M        0x00000300  // Comparison Trigger Mode
#define ADC_DCCTL3_CTM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL3_CTM_ONCE     0x00000100  // Once
#define ADC_DCCTL3_CTM_HALWAYS  0x00000200  // Hysteresis Always
#define ADC_DCCTL3_CTM_HONCE    0x00000300  // Hysteresis Once
#define ADC_DCCTL3_CIE          0x00000010  // Comparison Interrupt Enable
#define ADC_DCCTL3_CIC_M        0x0000000C  // Comparison Interrupt Condition
#define ADC_DCCTL3_CIC_LOW      0x00000000  // Low Band
#define ADC_DCCTL3_CIC_MID      0x00000004  // Mid Band
#define ADC_DCCTL3_CIC_HIGH     0x0000000C  // High Band
#define ADC_DCCTL3_CIM_M        0x00000003  // Comparison Interrupt Mode
#define ADC_DCCTL3_CIM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL3_CIM_ONCE     0x00000001  // Once
#define ADC_DCCTL3_CIM_HALWAYS  0x00000002  // Hysteresis Always
#define ADC_DCCTL3_CIM_HONCE    0x00000003  // Hysteresis Once

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCTL4 register.
//
//*****************************************************************************
#define ADC_DCCTL4_CTE          0x00001000  // Comparison Trigger Enable
#define ADC_DCCTL4_CTC_M        0x00000C00  // Comparison Trigger Condition
#define ADC_DCCTL4_CTC_LOW      0x00000000  // Low Band
#define ADC_DCCTL4_CTC_MID      0x00000400  // Mid Band
#define ADC_DCCTL4_CTC_HIGH     0x00000C00  // High Band
#define ADC_DCCTL4_CTM_M        0x00000300  // Comparison Trigger Mode
#define ADC_DCCTL4_CTM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL4_CTM_ONCE     0x00000100  // Once
#define ADC_DCCTL4_CTM_HALWAYS  0x00000200  // Hysteresis Always
#define ADC_DCCTL4_CTM_HONCE    0x00000300  // Hysteresis Once
#define ADC_DCCTL4_CIE          0x00000010  // Comparison Interrupt Enable
#define ADC_DCCTL4_CIC_M        0x0000000C  // Comparison Interrupt Condition
#define ADC_DCCTL4_CIC_LOW      0x00000000  // Low Band
#define ADC_DCCTL4_CIC_MID      0x00000004  // Mid Band
#define ADC_DCCTL4_CIC_HIGH     0x0000000C  // High Band
#define ADC_DCCTL4_CIM_M        0x00000003  // Comparison Interrupt Mode
#define ADC_DCCTL4_CIM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL4_CIM_ONCE     0x00000001  // Once
#define ADC_DCCTL4_CIM_HALWAYS  0x00000002  // Hysteresis Always
#define ADC_DCCTL4_CIM_HONCE    0x00000003  // Hysteresis Once

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCTL5 register.
//
//*****************************************************************************
#define ADC_DCCTL5_CTE          0x00001000  // Comparison Trigger Enable
#define ADC_DCCTL5_CTC_M        0x00000C00  // Comparison Trigger Condition
#define ADC_DCCTL5_CTC_LOW      0x00000000  // Low Band
#define ADC_DCCTL5_CTC_MID      0x00000400  // Mid Band
#define ADC_DCCTL5_CTC_HIGH     0x00000C00  // High Band
#define ADC_DCCTL5_CTM_M        0x00000300  // Comparison Trigger Mode
#define ADC_DCCTL5_CTM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL5_CTM_ONCE     0x00000100  // Once
#define ADC_DCCTL5_CTM_HALWAYS  0x00000200  // Hysteresis Always
#define ADC_DCCTL5_CTM_HONCE    0x00000300  // Hysteresis Once
#define ADC_DCCTL5_CIE          0x00000010  // Comparison Interrupt Enable
#define ADC_DCCTL5_CIC_M        0x0000000C  // Comparison Interrupt Condition
#define ADC_DCCTL5_CIC_LOW      0x00000000  // Low Band
#define ADC_DCCTL5_CIC_MID      0x00000004  // Mid Band
#define ADC_DCCTL5_CIC_HIGH     0x0000000C  // High Band
#define ADC_DCCTL5_CIM_M        0x00000003  // Comparison Interrupt Mode
#define ADC_DCCTL5_CIM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL5_CIM_ONCE     0x00000001  // Once
#define ADC_DCCTL5_CIM_HALWAYS  0x00000002  // Hysteresis Always
#define ADC_DCCTL5_CIM_HONCE    0x00000003  // Hysteresis Once

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCTL6 register.
//
//*****************************************************************************
#define ADC_DCCTL6_CTE          0x00001000  // Comparison Trigger Enable
#define ADC_DCCTL6_CTC_M        0x00000C00  // Comparison Trigger Condition
#define ADC_DCCTL6_CTC_LOW      0x00000000  // Low Band
#define ADC_DCCTL6_CTC_MID      0x00000400  // Mid Band
#define ADC_DCCTL6_CTC_HIGH     0x00000C00  // High Band
#define ADC_DCCTL6_CTM_M        0x00000300  // Comparison Trigger Mode
#define ADC_DCCTL6_CTM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL6_CTM_ONCE     0x00000100  // Once
#define ADC_DCCTL6_CTM_HALWAYS  0x00000200  // Hysteresis Always
#define ADC_DCCTL6_CTM_HONCE    0x00000300  // Hysteresis Once
#define ADC_DCCTL6_CIE          0x00000010  // Comparison Interrupt Enable
#define ADC_DCCTL6_CIC_M        0x0000000C  // Comparison Interrupt Condition
#define ADC_DCCTL6_CIC_LOW      0x00000000  // Low Band
#define ADC_DCCTL6_CIC_MID      0x00000004  // Mid Band
#define ADC_DCCTL6_CIC_HIGH     0x0000000C  // High Band
#define ADC_DCCTL6_CIM_M        0x00000003  // Comparison Interrupt Mode
#define ADC_DCCTL6_CIM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL6_CIM_ONCE     0x00000001  // Once
#define ADC_DCCTL6_CIM_HALWAYS  0x00000002  // Hysteresis Always
#define ADC_DCCTL6_CIM_HONCE    0x00000003  // Hysteresis Once

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCTL7 register.
//
//*****************************************************************************
#define ADC_DCCTL7_CTE          0x00001000  // Comparison Trigger Enable
#define ADC_DCCTL7_CTC_M        0x00000C00  // Comparison Trigger Condition
#define ADC_DCCTL7_CTC_LOW      0x00000000  // Low Band
#define ADC_DCCTL7_CTC_MID      0x00000400  // Mid Band
#define ADC_DCCTL7_CTC_HIGH     0x00000C00  // High Band
#define ADC_DCCTL7_CTM_M        0x00000300  // Comparison Trigger Mode
#define ADC_DCCTL7_CTM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL7_CTM_ONCE     0x00000100  // Once
#define ADC_DCCTL7_CTM_HALWAYS  0x00000200  // Hysteresis Always
#define ADC_DCCTL7_CTM_HONCE    0x00000300  // Hysteresis Once
#define ADC_DCCTL7_CIE          0x00000010  // Comparison Interrupt Enable
#define ADC_DCCTL7_CIC_M        0x0000000C  // Comparison Interrupt Condition
#define ADC_DCCTL7_CIC_LOW      0x00000000  // Low Band
#define ADC_DCCTL7_CIC_MID      0x00000004  // Mid Band
#define ADC_DCCTL7_CIC_HIGH     0x0000000C  // High Band
#define ADC_DCCTL7_CIM_M        0x00000003  // Comparison Interrupt Mode
#define ADC_DCCTL7_CIM_ALWAYS   0x00000000  // Always
#define ADC_DCCTL7_CIM_ONCE     0x00000001  // Once
#define ADC_DCCTL7_CIM_HALWAYS  0x00000002  // Hysteresis Always
#define ADC_DCCTL7_CIM_HONCE    0x00000003  // Hysteresis Once

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCMP0 register.
//
//*****************************************************************************
#define ADC_DCCMP0_COMP1_M      0x0FFF0000  // Compare 1
#define ADC_DCCMP0_COMP0_M      0x00000FFF  // Compare 0
#define ADC_DCCMP0_COMP1_S      16
#define ADC_DCCMP0_COMP0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCMP1 register.
//
//*****************************************************************************
#define ADC_DCCMP1_COMP1_M      0x0FFF0000  // Compare 1
#define ADC_DCCMP1_COMP0_M      0x00000FFF  // Compare 0
#define ADC_DCCMP1_COMP1_S      16
#define ADC_DCCMP1_COMP0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCMP2 register.
//
//*****************************************************************************
#define ADC_DCCMP2_COMP1_M      0x0FFF0000  // Compare 1
#define ADC_DCCMP2_COMP0_M      0x00000FFF  // Compare 0
#define ADC_DCCMP2_COMP1_S      16
#define ADC_DCCMP2_COMP0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCMP3 register.
//
//*****************************************************************************
#define ADC_DCCMP3_COMP1_M      0x0FFF0000  // Compare 1
#define ADC_DCCMP3_COMP0_M      0x00000FFF  // Compare 0
#define ADC_DCCMP3_COMP1_S      16
#define ADC_DCCMP3_COMP0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCMP4 register.
//
//*****************************************************************************
#define ADC_DCCMP4_COMP1_M      0x0FFF0000  // Compare 1
#define ADC_DCCMP4_COMP0_M      0x00000FFF  // Compare 0
#define ADC_DCCMP4_COMP1_S      16
#define ADC_DCCMP4_COMP0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCMP5 register.
//
//*****************************************************************************
#define ADC_DCCMP5_COMP1_M      0x0FFF0000  // Compare 1
#define ADC_DCCMP5_COMP0_M      0x00000FFF  // Compare 0
#define ADC_DCCMP5_COMP1_S      16
#define ADC_DCCMP5_COMP0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCMP6 register.
//
//*****************************************************************************
#define ADC_DCCMP6_COMP1_M      0x0FFF0000  // Compare 1
#define ADC_DCCMP6_COMP0_M      0x00000FFF  // Compare 0
#define ADC_DCCMP6_COMP1_S      16
#define ADC_DCCMP6_COMP0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_DCCMP7 register.
//
//*****************************************************************************
#define ADC_DCCMP7_COMP1_M      0x0FFF0000  // Compare 1
#define ADC_DCCMP7_COMP0_M      0x00000FFF  // Compare 0
#define ADC_DCCMP7_COMP1_S      16
#define ADC_DCCMP7_COMP0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_PP register.
//
//*****************************************************************************
#define ADC_PP_APSHT            0x01000000  // Application-Programmable
// Sample-and-Hold Time
#define ADC_PP_TS               0x00800000  // Temperature Sensor
#define ADC_PP_RSL_M            0x007C0000  // Resolution
#define ADC_PP_TYPE_M           0x00030000  // ADC Architecture
#define ADC_PP_TYPE_SAR         0x00000000  // SAR
#define ADC_PP_DC_M             0x0000FC00  // Digital Comparator Count
#define ADC_PP_CH_M             0x000003F0  // ADC Channel Count
#define ADC_PP_MCR_M            0x0000000F  // Maximum Conversion Rate
#define ADC_PP_MCR_FULL         0x00000007  // Full conversion rate (FCONV) as
// defined by TADC and NSH
#define ADC_PP_RSL_S            18
#define ADC_PP_DC_S             10
#define ADC_PP_CH_S             4

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_PC register.
//
//*****************************************************************************
#define ADC_PC_MCR_M            0x0000000F  // Conversion Rate
#define ADC_PC_MCR_1_8          0x00000001  // Eighth conversion rate. After a
// conversion completes, the logic
// pauses for 112 TADC periods
// before starting the next
// conversion
#define ADC_PC_MCR_1_4          0x00000003  // Quarter conversion rate. After a
// conversion completes, the logic
// pauses for 48 TADC periods
// before starting the next
// conversion
#define ADC_PC_MCR_1_2          0x00000005  // Half conversion rate. After a
// conversion completes, the logic
// pauses for 16 TADC periods
// before starting the next
// conversion
#define ADC_PC_MCR_FULL         0x00000007  // Full conversion rate (FCONV) as
// defined by TADC and NSH

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_CC register.
//
//*****************************************************************************
#define ADC_CC_CLKDIV_M         0x000003F0  // PLL VCO Clock Divisor
#define ADC_CC_CS_M             0x0000000F  // ADC Clock Source
#define ADC_CC_CS_SYSPLL        0x00000000  // PLL VCO divided by CLKDIV
#define ADC_CC_CS_PIOSC         0x00000001  // PIOSC
#define ADC_CC_CS_MOSC          0x00000002  // MOSC
#define ADC_CC_CLKDIV_S         4

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACMIS register.
//
//*****************************************************************************
#define COMP_ACMIS_IN2          0x00000004  // Comparator 2 Masked Interrupt
// Status
#define COMP_ACMIS_IN1          0x00000002  // Comparator 1 Masked Interrupt
// Status
#define COMP_ACMIS_IN0          0x00000001  // Comparator 0 Masked Interrupt
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACRIS register.
//
//*****************************************************************************
#define COMP_ACRIS_IN2          0x00000004  // Comparator 2 Interrupt Status
#define COMP_ACRIS_IN1          0x00000002  // Comparator 1 Interrupt Status
#define COMP_ACRIS_IN0          0x00000001  // Comparator 0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACINTEN register.
//
//*****************************************************************************
#define COMP_ACINTEN_IN2        0x00000004  // Comparator 2 Interrupt Enable
#define COMP_ACINTEN_IN1        0x00000002  // Comparator 1 Interrupt Enable
#define COMP_ACINTEN_IN0        0x00000001  // Comparator 0 Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACREFCTL
// register.
//
//*****************************************************************************
#define COMP_ACREFCTL_EN        0x00000200  // Resistor Ladder Enable
#define COMP_ACREFCTL_RNG       0x00000100  // Resistor Ladder Range
#define COMP_ACREFCTL_VREF_M    0x0000000F  // Resistor Ladder Voltage Ref
#define COMP_ACREFCTL_VREF_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACSTAT0 register.
//
//*****************************************************************************
#define COMP_ACSTAT0_OVAL       0x00000002  // Comparator Output Value

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACCTL0 register.
//
//*****************************************************************************
#define COMP_ACCTL0_TOEN        0x00000800  // Trigger Output Enable
#define COMP_ACCTL0_ASRCP_M     0x00000600  // Analog Source Positive
#define COMP_ACCTL0_ASRCP_PIN   0x00000000  // Pin value of Cn+
#define COMP_ACCTL0_ASRCP_PIN0  0x00000200  // Pin value of C0+
#define COMP_ACCTL0_ASRCP_REF   0x00000400  // Internal voltage reference
#define COMP_ACCTL0_TSLVAL      0x00000080  // Trigger Sense Level Value
#define COMP_ACCTL0_TSEN_M      0x00000060  // Trigger Sense
#define COMP_ACCTL0_TSEN_LEVEL  0x00000000  // Level sense, see TSLVAL
#define COMP_ACCTL0_TSEN_FALL   0x00000020  // Falling edge
#define COMP_ACCTL0_TSEN_RISE   0x00000040  // Rising edge
#define COMP_ACCTL0_TSEN_BOTH   0x00000060  // Either edge
#define COMP_ACCTL0_ISLVAL      0x00000010  // Interrupt Sense Level Value
#define COMP_ACCTL0_ISEN_M      0x0000000C  // Interrupt Sense
#define COMP_ACCTL0_ISEN_LEVEL  0x00000000  // Level sense, see ISLVAL
#define COMP_ACCTL0_ISEN_FALL   0x00000004  // Falling edge
#define COMP_ACCTL0_ISEN_RISE   0x00000008  // Rising edge
#define COMP_ACCTL0_ISEN_BOTH   0x0000000C  // Either edge
#define COMP_ACCTL0_CINV        0x00000002  // Comparator Output Invert

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACSTAT1 register.
//
//*****************************************************************************
#define COMP_ACSTAT1_OVAL       0x00000002  // Comparator Output Value

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACCTL1 register.
//
//*****************************************************************************
#define COMP_ACCTL1_TOEN        0x00000800  // Trigger Output Enable
#define COMP_ACCTL1_ASRCP_M     0x00000600  // Analog Source Positive
#define COMP_ACCTL1_ASRCP_PIN   0x00000000  // Pin value of Cn+
#define COMP_ACCTL1_ASRCP_PIN0  0x00000200  // Pin value of C0+
#define COMP_ACCTL1_ASRCP_REF   0x00000400  // Internal voltage reference
#define COMP_ACCTL1_TSLVAL      0x00000080  // Trigger Sense Level Value
#define COMP_ACCTL1_TSEN_M      0x00000060  // Trigger Sense
#define COMP_ACCTL1_TSEN_LEVEL  0x00000000  // Level sense, see TSLVAL
#define COMP_ACCTL1_TSEN_FALL   0x00000020  // Falling edge
#define COMP_ACCTL1_TSEN_RISE   0x00000040  // Rising edge
#define COMP_ACCTL1_TSEN_BOTH   0x00000060  // Either edge
#define COMP_ACCTL1_ISLVAL      0x00000010  // Interrupt Sense Level Value
#define COMP_ACCTL1_ISEN_M      0x0000000C  // Interrupt Sense
#define COMP_ACCTL1_ISEN_LEVEL  0x00000000  // Level sense, see ISLVAL
#define COMP_ACCTL1_ISEN_FALL   0x00000004  // Falling edge
#define COMP_ACCTL1_ISEN_RISE   0x00000008  // Rising edge
#define COMP_ACCTL1_ISEN_BOTH   0x0000000C  // Either edge
#define COMP_ACCTL1_CINV        0x00000002  // Comparator Output Invert

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACSTAT2 register.
//
//*****************************************************************************
#define COMP_ACSTAT2_OVAL       0x00000002  // Comparator Output Value

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACCTL2 register.
//
//*****************************************************************************
#define COMP_ACCTL2_TOEN        0x00000800  // Trigger Output Enable
#define COMP_ACCTL2_ASRCP_M     0x00000600  // Analog Source Positive
#define COMP_ACCTL2_ASRCP_PIN   0x00000000  // Pin value of Cn+
#define COMP_ACCTL2_ASRCP_PIN0  0x00000200  // Pin value of C0+
#define COMP_ACCTL2_ASRCP_REF   0x00000400  // Internal voltage reference
#define COMP_ACCTL2_TSLVAL      0x00000080  // Trigger Sense Level Value
#define COMP_ACCTL2_TSEN_M      0x00000060  // Trigger Sense
#define COMP_ACCTL2_TSEN_LEVEL  0x00000000  // Level sense, see TSLVAL
#define COMP_ACCTL2_TSEN_FALL   0x00000020  // Falling edge
#define COMP_ACCTL2_TSEN_RISE   0x00000040  // Rising edge
#define COMP_ACCTL2_TSEN_BOTH   0x00000060  // Either edge
#define COMP_ACCTL2_ISLVAL      0x00000010  // Interrupt Sense Level Value
#define COMP_ACCTL2_ISEN_M      0x0000000C  // Interrupt Sense
#define COMP_ACCTL2_ISEN_LEVEL  0x00000000  // Level sense, see ISLVAL
#define COMP_ACCTL2_ISEN_FALL   0x00000004  // Falling edge
#define COMP_ACCTL2_ISEN_RISE   0x00000008  // Rising edge
#define COMP_ACCTL2_ISEN_BOTH   0x0000000C  // Either edge
#define COMP_ACCTL2_CINV        0x00000002  // Comparator Output Invert

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_PP register.
//
//*****************************************************************************
#define COMP_PP_C2O             0x00040000  // Comparator Output 2 Present
#define COMP_PP_C1O             0x00020000  // Comparator Output 1 Present
#define COMP_PP_C0O             0x00010000  // Comparator Output 0 Present
#define COMP_PP_CMP2            0x00000004  // Comparator 2 Present
#define COMP_PP_CMP1            0x00000002  // Comparator 1 Present
#define COMP_PP_CMP0            0x00000001  // Comparator 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_CTL register.
//
//*****************************************************************************
#define CAN_CTL_TEST            0x00000080  // Test Mode Enable
#define CAN_CTL_CCE             0x00000040  // Configuration Change Enable
#define CAN_CTL_DAR             0x00000020  // Disable Automatic-Retransmission
#define CAN_CTL_EIE             0x00000008  // Error Interrupt Enable
#define CAN_CTL_SIE             0x00000004  // Status Interrupt Enable
#define CAN_CTL_IE              0x00000002  // CAN Interrupt Enable
#define CAN_CTL_INIT            0x00000001  // Initialization

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_STS register.
//
//*****************************************************************************
#define CAN_STS_BOFF            0x00000080  // Bus-Off Status
#define CAN_STS_EWARN           0x00000040  // Warning Status
#define CAN_STS_EPASS           0x00000020  // Error Passive
#define CAN_STS_RXOK            0x00000010  // Received a Message Successfully
#define CAN_STS_TXOK            0x00000008  // Transmitted a Message
// Successfully
#define CAN_STS_LEC_M           0x00000007  // Last Error Code
#define CAN_STS_LEC_NONE        0x00000000  // No Error
#define CAN_STS_LEC_STUFF       0x00000001  // Stuff Error
#define CAN_STS_LEC_FORM        0x00000002  // Format Error
#define CAN_STS_LEC_ACK         0x00000003  // ACK Error
#define CAN_STS_LEC_BIT1        0x00000004  // Bit 1 Error
#define CAN_STS_LEC_BIT0        0x00000005  // Bit 0 Error
#define CAN_STS_LEC_CRC         0x00000006  // CRC Error
#define CAN_STS_LEC_NOEVENT     0x00000007  // No Event

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_ERR register.
//
//*****************************************************************************
#define CAN_ERR_RP              0x00008000  // Received Error Passive
#define CAN_ERR_REC_M           0x00007F00  // Receive Error Counter
#define CAN_ERR_TEC_M           0x000000FF  // Transmit Error Counter
#define CAN_ERR_REC_S           8
#define CAN_ERR_TEC_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_BIT register.
//
//*****************************************************************************
#define CAN_BIT_TSEG2_M         0x00007000  // Time Segment after Sample Point
#define CAN_BIT_TSEG1_M         0x00000F00  // Time Segment Before Sample Point
#define CAN_BIT_SJW_M           0x000000C0  // (Re)Synchronization Jump Width
#define CAN_BIT_BRP_M           0x0000003F  // Baud Rate Prescaler
#define CAN_BIT_TSEG2_S         12
#define CAN_BIT_TSEG1_S         8
#define CAN_BIT_SJW_S           6
#define CAN_BIT_BRP_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_INT register.
//
//*****************************************************************************
#define CAN_INT_INTID_M         0x0000FFFF  // Interrupt Identifier
#define CAN_INT_INTID_NONE      0x00000000  // No interrupt pending
#define CAN_INT_INTID_STATUS    0x00008000  // Status Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_TST register.
//
//*****************************************************************************
#define CAN_TST_RX              0x00000080  // Receive Observation
#define CAN_TST_TX_M            0x00000060  // Transmit Control
#define CAN_TST_TX_CANCTL       0x00000000  // CAN Module Control
#define CAN_TST_TX_SAMPLE       0x00000020  // Sample Point
#define CAN_TST_TX_DOMINANT     0x00000040  // Driven Low
#define CAN_TST_TX_RECESSIVE    0x00000060  // Driven High
#define CAN_TST_LBACK           0x00000010  // Loopback Mode
#define CAN_TST_SILENT          0x00000008  // Silent Mode
#define CAN_TST_BASIC           0x00000004  // Basic Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_BRPE register.
//
//*****************************************************************************
#define CAN_BRPE_BRPE_M         0x0000000F  // Baud Rate Prescaler Extension
#define CAN_BRPE_BRPE_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1CRQ register.
//
//*****************************************************************************
#define CAN_IF1CRQ_BUSY         0x00008000  // Busy Flag
#define CAN_IF1CRQ_MNUM_M       0x0000003F  // Message Number
#define CAN_IF1CRQ_MNUM_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1CMSK register.
//
//*****************************************************************************
#define CAN_IF1CMSK_WRNRD       0x00000080  // Write, Not Read
#define CAN_IF1CMSK_MASK        0x00000040  // Access Mask Bits
#define CAN_IF1CMSK_ARB         0x00000020  // Access Arbitration Bits
#define CAN_IF1CMSK_CONTROL     0x00000010  // Access Control Bits
#define CAN_IF1CMSK_CLRINTPND   0x00000008  // Clear Interrupt Pending Bit
#define CAN_IF1CMSK_NEWDAT      0x00000004  // Access New Data
#define CAN_IF1CMSK_TXRQST      0x00000004  // Access Transmission Request
#define CAN_IF1CMSK_DATAA       0x00000002  // Access Data Byte 0 to 3
#define CAN_IF1CMSK_DATAB       0x00000001  // Access Data Byte 4 to 7

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MSK1 register.
//
//*****************************************************************************
#define CAN_IF1MSK1_IDMSK_M     0x0000FFFF  // Identifier Mask
#define CAN_IF1MSK1_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MSK2 register.
//
//*****************************************************************************
#define CAN_IF1MSK2_MXTD        0x00008000  // Mask Extended Identifier
#define CAN_IF1MSK2_MDIR        0x00004000  // Mask Message Direction
#define CAN_IF1MSK2_IDMSK_M     0x00001FFF  // Identifier Mask
#define CAN_IF1MSK2_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1ARB1 register.
//
//*****************************************************************************
#define CAN_IF1ARB1_ID_M        0x0000FFFF  // Message Identifier
#define CAN_IF1ARB1_ID_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1ARB2 register.
//
//*****************************************************************************
#define CAN_IF1ARB2_MSGVAL      0x00008000  // Message Valid
#define CAN_IF1ARB2_XTD         0x00004000  // Extended Identifier
#define CAN_IF1ARB2_DIR         0x00002000  // Message Direction
#define CAN_IF1ARB2_ID_M        0x00001FFF  // Message Identifier
#define CAN_IF1ARB2_ID_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MCTL register.
//
//*****************************************************************************
#define CAN_IF1MCTL_NEWDAT      0x00008000  // New Data
#define CAN_IF1MCTL_MSGLST      0x00004000  // Message Lost
#define CAN_IF1MCTL_INTPND      0x00002000  // Interrupt Pending
#define CAN_IF1MCTL_UMASK       0x00001000  // Use Acceptance Mask
#define CAN_IF1MCTL_TXIE        0x00000800  // Transmit Interrupt Enable
#define CAN_IF1MCTL_RXIE        0x00000400  // Receive Interrupt Enable
#define CAN_IF1MCTL_RMTEN       0x00000200  // Remote Enable
#define CAN_IF1MCTL_TXRQST      0x00000100  // Transmit Request
#define CAN_IF1MCTL_EOB         0x00000080  // End of Buffer
#define CAN_IF1MCTL_DLC_M       0x0000000F  // Data Length Code
#define CAN_IF1MCTL_DLC_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1DA1 register.
//
//*****************************************************************************
#define CAN_IF1DA1_DATA_M       0x0000FFFF  // Data
#define CAN_IF1DA1_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1DA2 register.
//
//*****************************************************************************
#define CAN_IF1DA2_DATA_M       0x0000FFFF  // Data
#define CAN_IF1DA2_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1DB1 register.
//
//*****************************************************************************
#define CAN_IF1DB1_DATA_M       0x0000FFFF  // Data
#define CAN_IF1DB1_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1DB2 register.
//
//*****************************************************************************
#define CAN_IF1DB2_DATA_M       0x0000FFFF  // Data
#define CAN_IF1DB2_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2CRQ register.
//
//*****************************************************************************
#define CAN_IF2CRQ_BUSY         0x00008000  // Busy Flag
#define CAN_IF2CRQ_MNUM_M       0x0000003F  // Message Number
#define CAN_IF2CRQ_MNUM_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2CMSK register.
//
//*****************************************************************************
#define CAN_IF2CMSK_WRNRD       0x00000080  // Write, Not Read
#define CAN_IF2CMSK_MASK        0x00000040  // Access Mask Bits
#define CAN_IF2CMSK_ARB         0x00000020  // Access Arbitration Bits
#define CAN_IF2CMSK_CONTROL     0x00000010  // Access Control Bits
#define CAN_IF2CMSK_CLRINTPND   0x00000008  // Clear Interrupt Pending Bit
#define CAN_IF2CMSK_NEWDAT      0x00000004  // Access New Data
#define CAN_IF2CMSK_TXRQST      0x00000004  // Access Transmission Request
#define CAN_IF2CMSK_DATAA       0x00000002  // Access Data Byte 0 to 3
#define CAN_IF2CMSK_DATAB       0x00000001  // Access Data Byte 4 to 7

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2MSK1 register.
//
//*****************************************************************************
#define CAN_IF2MSK1_IDMSK_M     0x0000FFFF  // Identifier Mask
#define CAN_IF2MSK1_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2MSK2 register.
//
//*****************************************************************************
#define CAN_IF2MSK2_MXTD        0x00008000  // Mask Extended Identifier
#define CAN_IF2MSK2_MDIR        0x00004000  // Mask Message Direction
#define CAN_IF2MSK2_IDMSK_M     0x00001FFF  // Identifier Mask
#define CAN_IF2MSK2_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2ARB1 register.
//
//*****************************************************************************
#define CAN_IF2ARB1_ID_M        0x0000FFFF  // Message Identifier
#define CAN_IF2ARB1_ID_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2ARB2 register.
//
//*****************************************************************************
#define CAN_IF2ARB2_MSGVAL      0x00008000  // Message Valid
#define CAN_IF2ARB2_XTD         0x00004000  // Extended Identifier
#define CAN_IF2ARB2_DIR         0x00002000  // Message Direction
#define CAN_IF2ARB2_ID_M        0x00001FFF  // Message Identifier
#define CAN_IF2ARB2_ID_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2MCTL register.
//
//*****************************************************************************
#define CAN_IF2MCTL_NEWDAT      0x00008000  // New Data
#define CAN_IF2MCTL_MSGLST      0x00004000  // Message Lost
#define CAN_IF2MCTL_INTPND      0x00002000  // Interrupt Pending
#define CAN_IF2MCTL_UMASK       0x00001000  // Use Acceptance Mask
#define CAN_IF2MCTL_TXIE        0x00000800  // Transmit Interrupt Enable
#define CAN_IF2MCTL_RXIE        0x00000400  // Receive Interrupt Enable
#define CAN_IF2MCTL_RMTEN       0x00000200  // Remote Enable
#define CAN_IF2MCTL_TXRQST      0x00000100  // Transmit Request
#define CAN_IF2MCTL_EOB         0x00000080  // End of Buffer
#define CAN_IF2MCTL_DLC_M       0x0000000F  // Data Length Code
#define CAN_IF2MCTL_DLC_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2DA1 register.
//
//*****************************************************************************
#define CAN_IF2DA1_DATA_M       0x0000FFFF  // Data
#define CAN_IF2DA1_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2DA2 register.
//
//*****************************************************************************
#define CAN_IF2DA2_DATA_M       0x0000FFFF  // Data
#define CAN_IF2DA2_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2DB1 register.
//
//*****************************************************************************
#define CAN_IF2DB1_DATA_M       0x0000FFFF  // Data
#define CAN_IF2DB1_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2DB2 register.
//
//*****************************************************************************
#define CAN_IF2DB2_DATA_M       0x0000FFFF  // Data
#define CAN_IF2DB2_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_TXRQ1 register.
//
//*****************************************************************************
#define CAN_TXRQ1_TXRQST_M      0x0000FFFF  // Transmission Request Bits
#define CAN_TXRQ1_TXRQST_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_TXRQ2 register.
//
//*****************************************************************************
#define CAN_TXRQ2_TXRQST_M      0x0000FFFF  // Transmission Request Bits
#define CAN_TXRQ2_TXRQST_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_NWDA1 register.
//
//*****************************************************************************
#define CAN_NWDA1_NEWDAT_M      0x0000FFFF  // New Data Bits
#define CAN_NWDA1_NEWDAT_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_NWDA2 register.
//
//*****************************************************************************
#define CAN_NWDA2_NEWDAT_M      0x0000FFFF  // New Data Bits
#define CAN_NWDA2_NEWDAT_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_MSG1INT register.
//
//*****************************************************************************
#define CAN_MSG1INT_INTPND_M    0x0000FFFF  // Interrupt Pending Bits
#define CAN_MSG1INT_INTPND_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_MSG2INT register.
//
//*****************************************************************************
#define CAN_MSG2INT_INTPND_M    0x0000FFFF  // Interrupt Pending Bits
#define CAN_MSG2INT_INTPND_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_MSG1VAL register.
//
//*****************************************************************************
#define CAN_MSG1VAL_MSGVAL_M    0x0000FFFF  // Message Valid Bits
#define CAN_MSG1VAL_MSGVAL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_MSG2VAL register.
//
//*****************************************************************************
#define CAN_MSG2VAL_MSGVAL_M    0x0000FFFF  // Message Valid Bits
#define CAN_MSG2VAL_MSGVAL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FADDR register.
//
//*****************************************************************************
#define USB_FADDR_M             0x0000007F  // Function Address
#define USB_FADDR_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_POWER register.
//
//*****************************************************************************
#define USB_POWER_ISOUP         0x00000080  // Isochronous Update
#define USB_POWER_SOFTCONN      0x00000040  // Soft Connect/Disconnect
#define USB_POWER_HSENAB        0x00000020  // High Speed Enable
#define USB_POWER_HSMODE        0x00000010  // High Speed Enable
#define USB_POWER_RESET         0x00000008  // RESET Signaling
#define USB_POWER_RESUME        0x00000004  // RESUME Signaling
#define USB_POWER_SUSPEND       0x00000002  // SUSPEND Mode
#define USB_POWER_PWRDNPHY      0x00000001  // Power Down PHY

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXIS register.
//
//*****************************************************************************
#define USB_TXIS_EP7            0x00000080  // TX Endpoint 7 Interrupt
#define USB_TXIS_EP6            0x00000040  // TX Endpoint 6 Interrupt
#define USB_TXIS_EP5            0x00000020  // TX Endpoint 5 Interrupt
#define USB_TXIS_EP4            0x00000010  // TX Endpoint 4 Interrupt
#define USB_TXIS_EP3            0x00000008  // TX Endpoint 3 Interrupt
#define USB_TXIS_EP2            0x00000004  // TX Endpoint 2 Interrupt
#define USB_TXIS_EP1            0x00000002  // TX Endpoint 1 Interrupt
#define USB_TXIS_EP0            0x00000001  // TX and RX Endpoint 0 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXIS register.
//
//*****************************************************************************
#define USB_RXIS_EP7            0x00000080  // RX Endpoint 7 Interrupt
#define USB_RXIS_EP6            0x00000040  // RX Endpoint 6 Interrupt
#define USB_RXIS_EP5            0x00000020  // RX Endpoint 5 Interrupt
#define USB_RXIS_EP4            0x00000010  // RX Endpoint 4 Interrupt
#define USB_RXIS_EP3            0x00000008  // RX Endpoint 3 Interrupt
#define USB_RXIS_EP2            0x00000004  // RX Endpoint 2 Interrupt
#define USB_RXIS_EP1            0x00000002  // RX Endpoint 1 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXIE register.
//
//*****************************************************************************
#define USB_TXIE_EP7            0x00000080  // TX Endpoint 7 Interrupt Enable
#define USB_TXIE_EP6            0x00000040  // TX Endpoint 6 Interrupt Enable
#define USB_TXIE_EP5            0x00000020  // TX Endpoint 5 Interrupt Enable
#define USB_TXIE_EP4            0x00000010  // TX Endpoint 4 Interrupt Enable
#define USB_TXIE_EP3            0x00000008  // TX Endpoint 3 Interrupt Enable
#define USB_TXIE_EP2            0x00000004  // TX Endpoint 2 Interrupt Enable
#define USB_TXIE_EP1            0x00000002  // TX Endpoint 1 Interrupt Enable
#define USB_TXIE_EP0            0x00000001  // TX and RX Endpoint 0 Interrupt
// Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXIE register.
//
//*****************************************************************************
#define USB_RXIE_EP7            0x00000080  // RX Endpoint 7 Interrupt Enable
#define USB_RXIE_EP6            0x00000040  // RX Endpoint 6 Interrupt Enable
#define USB_RXIE_EP5            0x00000020  // RX Endpoint 5 Interrupt Enable
#define USB_RXIE_EP4            0x00000010  // RX Endpoint 4 Interrupt Enable
#define USB_RXIE_EP3            0x00000008  // RX Endpoint 3 Interrupt Enable
#define USB_RXIE_EP2            0x00000004  // RX Endpoint 2 Interrupt Enable
#define USB_RXIE_EP1            0x00000002  // RX Endpoint 1 Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_IS register.
//
//*****************************************************************************
#define USB_IS_VBUSERR          0x00000080  // VBUS Error (OTG only)
#define USB_IS_SESREQ           0x00000040  // SESSION REQUEST (OTG only)
#define USB_IS_DISCON           0x00000020  // Session Disconnect (OTG only)
#define USB_IS_CONN             0x00000010  // Session Connect
#define USB_IS_SOF              0x00000008  // Start of Frame
#define USB_IS_BABBLE           0x00000004  // Babble Detected
#define USB_IS_RESET            0x00000004  // RESET Signaling Detected
#define USB_IS_RESUME           0x00000002  // RESUME Signaling Detected
#define USB_IS_SUSPEND          0x00000001  // SUSPEND Signaling Detected

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_IE register.
//
//*****************************************************************************
#define USB_IE_VBUSERR          0x00000080  // Enable VBUS Error Interrupt (OTG
// only)
#define USB_IE_SESREQ           0x00000040  // Enable Session Request (OTG
// only)
#define USB_IE_DISCON           0x00000020  // Enable Disconnect Interrupt
#define USB_IE_CONN             0x00000010  // Enable Connect Interrupt
#define USB_IE_SOF              0x00000008  // Enable Start-of-Frame Interrupt
#define USB_IE_BABBLE           0x00000004  // Enable Babble Interrupt
#define USB_IE_RESET            0x00000004  // Enable RESET Interrupt
#define USB_IE_RESUME           0x00000002  // Enable RESUME Interrupt
#define USB_IE_SUSPND           0x00000001  // Enable SUSPEND Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FRAME register.
//
//*****************************************************************************
#define USB_FRAME_M             0x000007FF  // Frame Number
#define USB_FRAME_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPIDX register.
//
//*****************************************************************************
#define USB_EPIDX_EPIDX_M       0x0000000F  // Endpoint Index
#define USB_EPIDX_EPIDX_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TEST register.
//
//*****************************************************************************
#define USB_TEST_FORCEH         0x00000080  // Force Host Mode
#define USB_TEST_FIFOACC        0x00000040  // FIFO Access
#define USB_TEST_FORCEFS        0x00000020  // Force Full-Speed Mode
#define USB_TEST_FORCEHS        0x00000010  // Force High-Speed Mode
#define USB_TEST_TESTPKT        0x00000008  // Test Packet Mode Enable
#define USB_TEST_TESTK          0x00000004  // Test_K Mode Enable
#define USB_TEST_TESTJ          0x00000002  // Test_J Mode Enable
#define USB_TEST_TESTSE0NAK     0x00000001  // Test_SE0_NAK Test Mode Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO0 register.
//
//*****************************************************************************
#define USB_FIFO0_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO0_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO1 register.
//
//*****************************************************************************
#define USB_FIFO1_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO1_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO2 register.
//
//*****************************************************************************
#define USB_FIFO2_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO2_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO3 register.
//
//*****************************************************************************
#define USB_FIFO3_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO3_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO4 register.
//
//*****************************************************************************
#define USB_FIFO4_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO4_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO5 register.
//
//*****************************************************************************
#define USB_FIFO5_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO5_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO6 register.
//
//*****************************************************************************
#define USB_FIFO6_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO6_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FIFO7 register.
//
//*****************************************************************************
#define USB_FIFO7_EPDATA_M      0xFFFFFFFF  // Endpoint Data
#define USB_FIFO7_EPDATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DEVCTL register.
//
//*****************************************************************************
#define USB_DEVCTL_DEV          0x00000080  // Device Mode (OTG only)
#define USB_DEVCTL_FSDEV        0x00000040  // Full-Speed Device Detected
#define USB_DEVCTL_LSDEV        0x00000020  // Low-Speed Device Detected
#define USB_DEVCTL_VBUS_M       0x00000018  // VBUS Level (OTG only)
#define USB_DEVCTL_VBUS_NONE    0x00000000  // Below SessionEnd
#define USB_DEVCTL_VBUS_SEND    0x00000008  // Above SessionEnd, below AValid
#define USB_DEVCTL_VBUS_AVALID  0x00000010  // Above AValid, below VBUSValid
#define USB_DEVCTL_VBUS_VALID   0x00000018  // Above VBUSValid
#define USB_DEVCTL_HOST         0x00000004  // Host Mode
#define USB_DEVCTL_HOSTREQ      0x00000002  // Host Request (OTG only)
#define USB_DEVCTL_SESSION      0x00000001  // Session Start/End (OTG only)

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CCONF register.
//
//*****************************************************************************
#define USB_CCONF_TXEDMA        0x00000002  // TX Early DMA Enable
#define USB_CCONF_RXEDMA        0x00000001  // TX Early DMA Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFIFOSZ register.
//
//*****************************************************************************
#define USB_TXFIFOSZ_DPB        0x00000010  // Double Packet Buffer Support
#define USB_TXFIFOSZ_SIZE_M     0x0000000F  // Max Packet Size
#define USB_TXFIFOSZ_SIZE_8     0x00000000  // 8
#define USB_TXFIFOSZ_SIZE_16    0x00000001  // 16
#define USB_TXFIFOSZ_SIZE_32    0x00000002  // 32
#define USB_TXFIFOSZ_SIZE_64    0x00000003  // 64
#define USB_TXFIFOSZ_SIZE_128   0x00000004  // 128
#define USB_TXFIFOSZ_SIZE_256   0x00000005  // 256
#define USB_TXFIFOSZ_SIZE_512   0x00000006  // 512
#define USB_TXFIFOSZ_SIZE_1024  0x00000007  // 1024
#define USB_TXFIFOSZ_SIZE_2048  0x00000008  // 2048

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFIFOSZ register.
//
//*****************************************************************************
#define USB_RXFIFOSZ_DPB        0x00000010  // Double Packet Buffer Support
#define USB_RXFIFOSZ_SIZE_M     0x0000000F  // Max Packet Size
#define USB_RXFIFOSZ_SIZE_8     0x00000000  // 8
#define USB_RXFIFOSZ_SIZE_16    0x00000001  // 16
#define USB_RXFIFOSZ_SIZE_32    0x00000002  // 32
#define USB_RXFIFOSZ_SIZE_64    0x00000003  // 64
#define USB_RXFIFOSZ_SIZE_128   0x00000004  // 128
#define USB_RXFIFOSZ_SIZE_256   0x00000005  // 256
#define USB_RXFIFOSZ_SIZE_512   0x00000006  // 512
#define USB_RXFIFOSZ_SIZE_1024  0x00000007  // 1024
#define USB_RXFIFOSZ_SIZE_2048  0x00000008  // 2048

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFIFOADD
// register.
//
//*****************************************************************************
#define USB_TXFIFOADD_ADDR_M    0x000001FF  // Transmit/Receive Start Address
#define USB_TXFIFOADD_ADDR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFIFOADD
// register.
//
//*****************************************************************************
#define USB_RXFIFOADD_ADDR_M    0x000001FF  // Transmit/Receive Start Address
#define USB_RXFIFOADD_ADDR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_ULPIVBUSCTL
// register.
//
//*****************************************************************************
#define USB_ULPIVBUSCTL_USEEXTVBUSIND                                         \
                                0x00000002  // Use External VBUS Indicator
#define USB_ULPIVBUSCTL_USEEXTVBUS                                            \
                                0x00000001  // Use External VBUS

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_ULPIREGDATA
// register.
//
//*****************************************************************************
#define USB_ULPIREGDATA_REGDATA_M                                             \
                                0x000000FF  // Register Data
#define USB_ULPIREGDATA_REGDATA_S                                             \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_ULPIREGADDR
// register.
//
//*****************************************************************************
#define USB_ULPIREGADDR_ADDR_M  0x000000FF  // Register Address
#define USB_ULPIREGADDR_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_ULPIREGCTL
// register.
//
//*****************************************************************************
#define USB_ULPIREGCTL_RDWR     0x00000004  // Read/Write Control
#define USB_ULPIREGCTL_REGCMPLT 0x00000002  // Register Access Complete
#define USB_ULPIREGCTL_REGACC   0x00000001  // Initiate Register Access

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPINFO register.
//
//*****************************************************************************
#define USB_EPINFO_RXEP_M       0x000000F0  // RX Endpoints
#define USB_EPINFO_TXEP_M       0x0000000F  // TX Endpoints
#define USB_EPINFO_RXEP_S       4
#define USB_EPINFO_TXEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RAMINFO register.
//
//*****************************************************************************
#define USB_RAMINFO_DMACHAN_M   0x000000F0  // DMA Channels
#define USB_RAMINFO_RAMBITS_M   0x0000000F  // RAM Address Bus Width
#define USB_RAMINFO_DMACHAN_S   4
#define USB_RAMINFO_RAMBITS_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CONTIM register.
//
//*****************************************************************************
#define USB_CONTIM_WTCON_M      0x000000F0  // Connect Wait
#define USB_CONTIM_WTID_M       0x0000000F  // Wait ID
#define USB_CONTIM_WTCON_S      4
#define USB_CONTIM_WTID_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VPLEN register.
//
//*****************************************************************************
#define USB_VPLEN_VPLEN_M       0x000000FF  // VBUS Pulse Length
#define USB_VPLEN_VPLEN_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_HSEOF register.
//
//*****************************************************************************
#define USB_HSEOF_HSEOFG_M      0x000000FF  // HIgh-Speed End-of-Frame Gap
#define USB_HSEOF_HSEOFG_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_FSEOF register.
//
//*****************************************************************************
#define USB_FSEOF_FSEOFG_M      0x000000FF  // Full-Speed End-of-Frame Gap
#define USB_FSEOF_FSEOFG_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LSEOF register.
//
//*****************************************************************************
#define USB_LSEOF_LSEOFG_M      0x000000FF  // Low-Speed End-of-Frame Gap
#define USB_LSEOF_LSEOFG_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR0
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR0_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR0_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR0
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR0_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR0_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT0
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT0_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT0_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR1
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR1_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR1_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR1
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR1_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR1_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT1
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT1_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT1_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR1
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR1_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR1_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR1
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR1_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR1_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT1
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT1_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT1_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR2
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR2_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR2_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR2
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR2_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR2_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT2
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT2_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT2_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR2
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR2_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR2_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR2
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR2_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR2_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT2
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT2_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT2_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR3
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR3_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR3_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR3
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR3_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR3_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT3
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT3_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT3_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR3
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR3_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR3_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR3
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR3_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR3_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT3
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT3_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT3_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR4
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR4_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR4_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR4
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR4_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR4_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT4
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT4_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT4_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR4
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR4_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR4_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR4
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR4_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR4_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT4
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT4_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT4_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR5
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR5_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR5_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR5
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR5_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR5_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT5
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT5_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT5_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR5
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR5_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR5_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR5
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR5_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR5_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT5
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT5_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT5_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR6
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR6_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR6_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR6
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR6_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR6_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT6
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT6_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT6_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR6
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR6_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR6_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR6
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR6_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR6_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT6
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT6_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT6_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXFUNCADDR7
// register.
//
//*****************************************************************************
#define USB_TXFUNCADDR7_ADDR_M  0x0000007F  // Device Address
#define USB_TXFUNCADDR7_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBADDR7
// register.
//
//*****************************************************************************
#define USB_TXHUBADDR7_ADDR_M   0x0000007F  // Hub Address
#define USB_TXHUBADDR7_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXHUBPORT7
// register.
//
//*****************************************************************************
#define USB_TXHUBPORT7_PORT_M   0x0000007F  // Hub Port
#define USB_TXHUBPORT7_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXFUNCADDR7
// register.
//
//*****************************************************************************
#define USB_RXFUNCADDR7_ADDR_M  0x0000007F  // Device Address
#define USB_RXFUNCADDR7_ADDR_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBADDR7
// register.
//
//*****************************************************************************
#define USB_RXHUBADDR7_ADDR_M   0x0000007F  // Hub Address
#define USB_RXHUBADDR7_ADDR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXHUBPORT7
// register.
//
//*****************************************************************************
#define USB_RXHUBPORT7_PORT_M   0x0000007F  // Hub Port
#define USB_RXHUBPORT7_PORT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CSRL0 register.
//
//*****************************************************************************
#define USB_CSRL0_NAKTO         0x00000080  // NAK Timeout
#define USB_CSRL0_SETENDC       0x00000080  // Setup End Clear
#define USB_CSRL0_STATUS        0x00000040  // STATUS Packet
#define USB_CSRL0_RXRDYC        0x00000040  // RXRDY Clear
#define USB_CSRL0_REQPKT        0x00000020  // Request Packet
#define USB_CSRL0_STALL         0x00000020  // Send Stall
#define USB_CSRL0_SETEND        0x00000010  // Setup End
#define USB_CSRL0_ERROR         0x00000010  // Error
#define USB_CSRL0_DATAEND       0x00000008  // Data End
#define USB_CSRL0_SETUP         0x00000008  // Setup Packet
#define USB_CSRL0_STALLED       0x00000004  // Endpoint Stalled
#define USB_CSRL0_TXRDY         0x00000002  // Transmit Packet Ready
#define USB_CSRL0_RXRDY         0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CSRH0 register.
//
//*****************************************************************************
#define USB_CSRH0_DISPING       0x00000008  // PING Disable
#define USB_CSRH0_DTWE          0x00000004  // Data Toggle Write Enable
#define USB_CSRH0_DT            0x00000002  // Data Toggle
#define USB_CSRH0_FLUSH         0x00000001  // Flush FIFO

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_COUNT0 register.
//
//*****************************************************************************
#define USB_COUNT0_COUNT_M      0x0000007F  // FIFO Count
#define USB_COUNT0_COUNT_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TYPE0 register.
//
//*****************************************************************************
#define USB_TYPE0_SPEED_M       0x000000C0  // Operating Speed
#define USB_TYPE0_SPEED_HIGH    0x00000040  // High
#define USB_TYPE0_SPEED_FULL    0x00000080  // Full
#define USB_TYPE0_SPEED_LOW     0x000000C0  // Low

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_NAKLMT register.
//
//*****************************************************************************
#define USB_NAKLMT_NAKLMT_M     0x0000001F  // EP0 NAK Limit
#define USB_NAKLMT_NAKLMT_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP1 register.
//
//*****************************************************************************
#define USB_TXMAXP1_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP1_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL1 register.
//
//*****************************************************************************
#define USB_TXCSRL1_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL1_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL1_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL1_STALL       0x00000010  // Send STALL
#define USB_TXCSRL1_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL1_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL1_ERROR       0x00000004  // Error
#define USB_TXCSRL1_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL1_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL1_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH1 register.
//
//*****************************************************************************
#define USB_TXCSRH1_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH1_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH1_MODE        0x00000020  // Mode
#define USB_TXCSRH1_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH1_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH1_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH1_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH1_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP1 register.
//
//*****************************************************************************
#define USB_RXMAXP1_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP1_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL1 register.
//
//*****************************************************************************
#define USB_RXCSRL1_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL1_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL1_STALL       0x00000020  // Send STALL
#define USB_RXCSRL1_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL1_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL1_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL1_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL1_OVER        0x00000004  // Overrun
#define USB_RXCSRL1_ERROR       0x00000004  // Error
#define USB_RXCSRL1_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL1_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH1 register.
//
//*****************************************************************************
#define USB_RXCSRH1_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH1_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH1_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH1_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH1_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH1_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH1_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH1_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH1_DT          0x00000002  // Data Toggle
#define USB_RXCSRH1_INCOMPRX    0x00000001  // Incomplete RX Transmission
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT1 register.
//
//*****************************************************************************
#define USB_RXCOUNT1_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT1_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE1 register.
//
//*****************************************************************************
#define USB_TXTYPE1_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE1_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE1_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE1_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE1_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE1_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE1_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE1_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE1_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE1_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE1_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE1_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL1
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL1_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL1_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL1_TXPOLL_S                                              \
                                0
#define USB_TXINTERVAL1_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE1 register.
//
//*****************************************************************************
#define USB_RXTYPE1_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE1_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE1_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE1_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE1_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE1_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE1_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE1_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE1_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE1_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE1_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE1_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL1
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL1_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL1_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL1_TXPOLL_S                                              \
                                0
#define USB_RXINTERVAL1_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP2 register.
//
//*****************************************************************************
#define USB_TXMAXP2_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP2_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL2 register.
//
//*****************************************************************************
#define USB_TXCSRL2_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL2_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL2_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL2_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL2_STALL       0x00000010  // Send STALL
#define USB_TXCSRL2_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL2_ERROR       0x00000004  // Error
#define USB_TXCSRL2_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL2_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL2_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH2 register.
//
//*****************************************************************************
#define USB_TXCSRH2_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH2_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH2_MODE        0x00000020  // Mode
#define USB_TXCSRH2_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH2_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH2_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH2_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH2_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP2 register.
//
//*****************************************************************************
#define USB_RXMAXP2_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP2_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL2 register.
//
//*****************************************************************************
#define USB_RXCSRL2_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL2_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL2_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL2_STALL       0x00000020  // Send STALL
#define USB_RXCSRL2_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL2_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL2_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL2_ERROR       0x00000004  // Error
#define USB_RXCSRL2_OVER        0x00000004  // Overrun
#define USB_RXCSRL2_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL2_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH2 register.
//
//*****************************************************************************
#define USB_RXCSRH2_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH2_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH2_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH2_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH2_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH2_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH2_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH2_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH2_DT          0x00000002  // Data Toggle
#define USB_RXCSRH2_INCOMPRX    0x00000001  // Incomplete RX Transmission
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT2 register.
//
//*****************************************************************************
#define USB_RXCOUNT2_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT2_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE2 register.
//
//*****************************************************************************
#define USB_TXTYPE2_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE2_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE2_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE2_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE2_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE2_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE2_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE2_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE2_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE2_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE2_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE2_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL2
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL2_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL2_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL2_NAKLMT_S                                              \
                                0
#define USB_TXINTERVAL2_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE2 register.
//
//*****************************************************************************
#define USB_RXTYPE2_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE2_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE2_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE2_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE2_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE2_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE2_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE2_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE2_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE2_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE2_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE2_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL2
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL2_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL2_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL2_TXPOLL_S                                              \
                                0
#define USB_RXINTERVAL2_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP3 register.
//
//*****************************************************************************
#define USB_TXMAXP3_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP3_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL3 register.
//
//*****************************************************************************
#define USB_TXCSRL3_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL3_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL3_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL3_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL3_STALL       0x00000010  // Send STALL
#define USB_TXCSRL3_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL3_ERROR       0x00000004  // Error
#define USB_TXCSRL3_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL3_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL3_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH3 register.
//
//*****************************************************************************
#define USB_TXCSRH3_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH3_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH3_MODE        0x00000020  // Mode
#define USB_TXCSRH3_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH3_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH3_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH3_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH3_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP3 register.
//
//*****************************************************************************
#define USB_RXMAXP3_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP3_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL3 register.
//
//*****************************************************************************
#define USB_RXCSRL3_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL3_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL3_STALL       0x00000020  // Send STALL
#define USB_RXCSRL3_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL3_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL3_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL3_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL3_ERROR       0x00000004  // Error
#define USB_RXCSRL3_OVER        0x00000004  // Overrun
#define USB_RXCSRL3_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL3_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH3 register.
//
//*****************************************************************************
#define USB_RXCSRH3_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH3_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH3_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH3_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH3_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH3_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH3_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH3_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH3_DT          0x00000002  // Data Toggle
#define USB_RXCSRH3_INCOMPRX    0x00000001  // Incomplete RX Transmission
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT3 register.
//
//*****************************************************************************
#define USB_RXCOUNT3_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT3_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE3 register.
//
//*****************************************************************************
#define USB_TXTYPE3_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE3_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE3_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE3_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE3_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE3_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE3_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE3_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE3_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE3_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE3_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE3_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL3
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL3_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL3_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL3_TXPOLL_S                                              \
                                0
#define USB_TXINTERVAL3_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE3 register.
//
//*****************************************************************************
#define USB_RXTYPE3_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE3_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE3_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE3_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE3_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE3_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE3_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE3_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE3_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE3_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE3_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE3_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL3
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL3_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL3_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL3_TXPOLL_S                                              \
                                0
#define USB_RXINTERVAL3_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP4 register.
//
//*****************************************************************************
#define USB_TXMAXP4_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP4_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL4 register.
//
//*****************************************************************************
#define USB_TXCSRL4_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL4_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL4_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL4_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL4_STALL       0x00000010  // Send STALL
#define USB_TXCSRL4_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL4_ERROR       0x00000004  // Error
#define USB_TXCSRL4_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL4_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL4_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH4 register.
//
//*****************************************************************************
#define USB_TXCSRH4_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH4_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH4_MODE        0x00000020  // Mode
#define USB_TXCSRH4_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH4_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH4_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH4_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH4_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP4 register.
//
//*****************************************************************************
#define USB_RXMAXP4_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP4_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL4 register.
//
//*****************************************************************************
#define USB_RXCSRL4_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL4_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL4_STALL       0x00000020  // Send STALL
#define USB_RXCSRL4_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL4_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL4_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL4_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL4_OVER        0x00000004  // Overrun
#define USB_RXCSRL4_ERROR       0x00000004  // Error
#define USB_RXCSRL4_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL4_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH4 register.
//
//*****************************************************************************
#define USB_RXCSRH4_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH4_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH4_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH4_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH4_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH4_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH4_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH4_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH4_DT          0x00000002  // Data Toggle
#define USB_RXCSRH4_INCOMPRX    0x00000001  // Incomplete RX Transmission
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT4 register.
//
//*****************************************************************************
#define USB_RXCOUNT4_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT4_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE4 register.
//
//*****************************************************************************
#define USB_TXTYPE4_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE4_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE4_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE4_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE4_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE4_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE4_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE4_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE4_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE4_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE4_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE4_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL4
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL4_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL4_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL4_NAKLMT_S                                              \
                                0
#define USB_TXINTERVAL4_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE4 register.
//
//*****************************************************************************
#define USB_RXTYPE4_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE4_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE4_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE4_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE4_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE4_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE4_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE4_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE4_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE4_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE4_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE4_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL4
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL4_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL4_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL4_NAKLMT_S                                              \
                                0
#define USB_RXINTERVAL4_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP5 register.
//
//*****************************************************************************
#define USB_TXMAXP5_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP5_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL5 register.
//
//*****************************************************************************
#define USB_TXCSRL5_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL5_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL5_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL5_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL5_STALL       0x00000010  // Send STALL
#define USB_TXCSRL5_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL5_ERROR       0x00000004  // Error
#define USB_TXCSRL5_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL5_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL5_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH5 register.
//
//*****************************************************************************
#define USB_TXCSRH5_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH5_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH5_MODE        0x00000020  // Mode
#define USB_TXCSRH5_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH5_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH5_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH5_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH5_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP5 register.
//
//*****************************************************************************
#define USB_RXMAXP5_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP5_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL5 register.
//
//*****************************************************************************
#define USB_RXCSRL5_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL5_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL5_STALL       0x00000020  // Send STALL
#define USB_RXCSRL5_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL5_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL5_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL5_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL5_ERROR       0x00000004  // Error
#define USB_RXCSRL5_OVER        0x00000004  // Overrun
#define USB_RXCSRL5_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL5_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH5 register.
//
//*****************************************************************************
#define USB_RXCSRH5_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH5_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH5_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH5_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH5_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH5_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH5_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH5_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH5_DT          0x00000002  // Data Toggle
#define USB_RXCSRH5_INCOMPRX    0x00000001  // Incomplete RX Transmission
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT5 register.
//
//*****************************************************************************
#define USB_RXCOUNT5_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT5_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE5 register.
//
//*****************************************************************************
#define USB_TXTYPE5_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE5_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE5_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE5_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE5_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE5_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE5_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE5_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE5_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE5_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE5_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE5_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL5
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL5_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL5_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL5_NAKLMT_S                                              \
                                0
#define USB_TXINTERVAL5_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE5 register.
//
//*****************************************************************************
#define USB_RXTYPE5_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE5_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE5_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE5_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE5_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE5_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE5_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE5_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE5_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE5_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE5_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE5_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL5
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL5_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL5_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL5_TXPOLL_S                                              \
                                0
#define USB_RXINTERVAL5_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP6 register.
//
//*****************************************************************************
#define USB_TXMAXP6_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP6_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL6 register.
//
//*****************************************************************************
#define USB_TXCSRL6_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL6_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL6_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL6_STALL       0x00000010  // Send STALL
#define USB_TXCSRL6_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL6_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL6_ERROR       0x00000004  // Error
#define USB_TXCSRL6_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL6_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL6_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH6 register.
//
//*****************************************************************************
#define USB_TXCSRH6_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH6_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH6_MODE        0x00000020  // Mode
#define USB_TXCSRH6_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH6_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH6_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH6_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH6_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP6 register.
//
//*****************************************************************************
#define USB_RXMAXP6_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP6_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL6 register.
//
//*****************************************************************************
#define USB_RXCSRL6_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL6_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL6_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL6_STALL       0x00000020  // Send STALL
#define USB_RXCSRL6_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL6_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL6_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL6_ERROR       0x00000004  // Error
#define USB_RXCSRL6_OVER        0x00000004  // Overrun
#define USB_RXCSRL6_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL6_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH6 register.
//
//*****************************************************************************
#define USB_RXCSRH6_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH6_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH6_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH6_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH6_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH6_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH6_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH6_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH6_DT          0x00000002  // Data Toggle
#define USB_RXCSRH6_INCOMPRX    0x00000001  // Incomplete RX Transmission
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT6 register.
//
//*****************************************************************************
#define USB_RXCOUNT6_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT6_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE6 register.
//
//*****************************************************************************
#define USB_TXTYPE6_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE6_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE6_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE6_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE6_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE6_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE6_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE6_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE6_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE6_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE6_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE6_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL6
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL6_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL6_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL6_TXPOLL_S                                              \
                                0
#define USB_TXINTERVAL6_NAKLMT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE6 register.
//
//*****************************************************************************
#define USB_RXTYPE6_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE6_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE6_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE6_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE6_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE6_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE6_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE6_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE6_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE6_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE6_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE6_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL6
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL6_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL6_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL6_NAKLMT_S                                              \
                                0
#define USB_RXINTERVAL6_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXMAXP7 register.
//
//*****************************************************************************
#define USB_TXMAXP7_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_TXMAXP7_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRL7 register.
//
//*****************************************************************************
#define USB_TXCSRL7_NAKTO       0x00000080  // NAK Timeout
#define USB_TXCSRL7_CLRDT       0x00000040  // Clear Data Toggle
#define USB_TXCSRL7_STALLED     0x00000020  // Endpoint Stalled
#define USB_TXCSRL7_STALL       0x00000010  // Send STALL
#define USB_TXCSRL7_SETUP       0x00000010  // Setup Packet
#define USB_TXCSRL7_FLUSH       0x00000008  // Flush FIFO
#define USB_TXCSRL7_ERROR       0x00000004  // Error
#define USB_TXCSRL7_UNDRN       0x00000004  // Underrun
#define USB_TXCSRL7_FIFONE      0x00000002  // FIFO Not Empty
#define USB_TXCSRL7_TXRDY       0x00000001  // Transmit Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXCSRH7 register.
//
//*****************************************************************************
#define USB_TXCSRH7_AUTOSET     0x00000080  // Auto Set
#define USB_TXCSRH7_ISO         0x00000040  // Isochronous Transfers
#define USB_TXCSRH7_MODE        0x00000020  // Mode
#define USB_TXCSRH7_DMAEN       0x00000010  // DMA Request Enable
#define USB_TXCSRH7_FDT         0x00000008  // Force Data Toggle
#define USB_TXCSRH7_DMAMOD      0x00000004  // DMA Request Mode
#define USB_TXCSRH7_DTWE        0x00000002  // Data Toggle Write Enable
#define USB_TXCSRH7_DT          0x00000001  // Data Toggle

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXMAXP7 register.
//
//*****************************************************************************
#define USB_RXMAXP7_MAXLOAD_M   0x000007FF  // Maximum Payload
#define USB_RXMAXP7_MAXLOAD_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRL7 register.
//
//*****************************************************************************
#define USB_RXCSRL7_CLRDT       0x00000080  // Clear Data Toggle
#define USB_RXCSRL7_STALLED     0x00000040  // Endpoint Stalled
#define USB_RXCSRL7_REQPKT      0x00000020  // Request Packet
#define USB_RXCSRL7_STALL       0x00000020  // Send STALL
#define USB_RXCSRL7_FLUSH       0x00000010  // Flush FIFO
#define USB_RXCSRL7_DATAERR     0x00000008  // Data Error
#define USB_RXCSRL7_NAKTO       0x00000008  // NAK Timeout
#define USB_RXCSRL7_ERROR       0x00000004  // Error
#define USB_RXCSRL7_OVER        0x00000004  // Overrun
#define USB_RXCSRL7_FULL        0x00000002  // FIFO Full
#define USB_RXCSRL7_RXRDY       0x00000001  // Receive Packet Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCSRH7 register.
//
//*****************************************************************************
#define USB_RXCSRH7_AUTOCL      0x00000080  // Auto Clear
#define USB_RXCSRH7_ISO         0x00000040  // Isochronous Transfers
#define USB_RXCSRH7_AUTORQ      0x00000040  // Auto Request
#define USB_RXCSRH7_DMAEN       0x00000020  // DMA Request Enable
#define USB_RXCSRH7_PIDERR      0x00000010  // PID Error
#define USB_RXCSRH7_DISNYET     0x00000010  // Disable NYET
#define USB_RXCSRH7_DMAMOD      0x00000008  // DMA Request Mode
#define USB_RXCSRH7_DTWE        0x00000004  // Data Toggle Write Enable
#define USB_RXCSRH7_DT          0x00000002  // Data Toggle
#define USB_RXCSRH7_INCOMPRX    0x00000001  // Incomplete RX Transmission
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXCOUNT7 register.
//
//*****************************************************************************
#define USB_RXCOUNT7_COUNT_M    0x00001FFF  // Receive Packet Count
#define USB_RXCOUNT7_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXTYPE7 register.
//
//*****************************************************************************
#define USB_TXTYPE7_SPEED_M     0x000000C0  // Operating Speed
#define USB_TXTYPE7_SPEED_DFLT  0x00000000  // Default
#define USB_TXTYPE7_SPEED_HIGH  0x00000040  // High
#define USB_TXTYPE7_SPEED_FULL  0x00000080  // Full
#define USB_TXTYPE7_SPEED_LOW   0x000000C0  // Low
#define USB_TXTYPE7_PROTO_M     0x00000030  // Protocol
#define USB_TXTYPE7_PROTO_CTRL  0x00000000  // Control
#define USB_TXTYPE7_PROTO_ISOC  0x00000010  // Isochronous
#define USB_TXTYPE7_PROTO_BULK  0x00000020  // Bulk
#define USB_TXTYPE7_PROTO_INT   0x00000030  // Interrupt
#define USB_TXTYPE7_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_TXTYPE7_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXINTERVAL7
// register.
//
//*****************************************************************************
#define USB_TXINTERVAL7_TXPOLL_M                                              \
                                0x000000FF  // TX Polling
#define USB_TXINTERVAL7_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_TXINTERVAL7_NAKLMT_S                                              \
                                0
#define USB_TXINTERVAL7_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXTYPE7 register.
//
//*****************************************************************************
#define USB_RXTYPE7_SPEED_M     0x000000C0  // Operating Speed
#define USB_RXTYPE7_SPEED_DFLT  0x00000000  // Default
#define USB_RXTYPE7_SPEED_HIGH  0x00000040  // High
#define USB_RXTYPE7_SPEED_FULL  0x00000080  // Full
#define USB_RXTYPE7_SPEED_LOW   0x000000C0  // Low
#define USB_RXTYPE7_PROTO_M     0x00000030  // Protocol
#define USB_RXTYPE7_PROTO_CTRL  0x00000000  // Control
#define USB_RXTYPE7_PROTO_ISOC  0x00000010  // Isochronous
#define USB_RXTYPE7_PROTO_BULK  0x00000020  // Bulk
#define USB_RXTYPE7_PROTO_INT   0x00000030  // Interrupt
#define USB_RXTYPE7_TEP_M       0x0000000F  // Target Endpoint Number
#define USB_RXTYPE7_TEP_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXINTERVAL7
// register.
//
//*****************************************************************************
#define USB_RXINTERVAL7_TXPOLL_M                                              \
                                0x000000FF  // RX Polling
#define USB_RXINTERVAL7_NAKLMT_M                                              \
                                0x000000FF  // NAK Limit
#define USB_RXINTERVAL7_NAKLMT_S                                              \
                                0
#define USB_RXINTERVAL7_TXPOLL_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAINTR register.
//
//*****************************************************************************
#define USB_DMAINTR_CH7         0x00000080  // Channel 7 DMA Interrupt
#define USB_DMAINTR_CH6         0x00000040  // Channel 6 DMA Interrupt
#define USB_DMAINTR_CH5         0x00000020  // Channel 5 DMA Interrupt
#define USB_DMAINTR_CH4         0x00000010  // Channel 4 DMA Interrupt
#define USB_DMAINTR_CH3         0x00000008  // Channel 3 DMA Interrupt
#define USB_DMAINTR_CH2         0x00000004  // Channel 2 DMA Interrupt
#define USB_DMAINTR_CH1         0x00000002  // Channel 1 DMA Interrupt
#define USB_DMAINTR_CH0         0x00000001  // Channel 0 DMA Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL0 register.
//
//*****************************************************************************
#define USB_DMACTL0_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL0_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL0_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL0_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
// length
#define USB_DMACTL0_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
// unspecified length
#define USB_DMACTL0_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL0_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL0_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL0_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL0_DIR         0x00000002  // DMA Direction
#define USB_DMACTL0_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL0_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR0 register.
//
//*****************************************************************************
#define USB_DMAADDR0_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR0_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT0
// register.
//
//*****************************************************************************
#define USB_DMACOUNT0_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT0_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL1 register.
//
//*****************************************************************************
#define USB_DMACTL1_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL1_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL1_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL1_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
// length
#define USB_DMACTL1_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
// unspecified length
#define USB_DMACTL1_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL1_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL1_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL1_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL1_DIR         0x00000002  // DMA Direction
#define USB_DMACTL1_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL1_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR1 register.
//
//*****************************************************************************
#define USB_DMAADDR1_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR1_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT1
// register.
//
//*****************************************************************************
#define USB_DMACOUNT1_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT1_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL2 register.
//
//*****************************************************************************
#define USB_DMACTL2_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL2_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL2_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL2_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
// length
#define USB_DMACTL2_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
// unspecified length
#define USB_DMACTL2_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL2_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL2_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL2_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL2_DIR         0x00000002  // DMA Direction
#define USB_DMACTL2_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL2_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR2 register.
//
//*****************************************************************************
#define USB_DMAADDR2_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR2_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT2
// register.
//
//*****************************************************************************
#define USB_DMACOUNT2_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT2_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL3 register.
//
//*****************************************************************************
#define USB_DMACTL3_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL3_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL3_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL3_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
// length
#define USB_DMACTL3_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
// unspecified length
#define USB_DMACTL3_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL3_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL3_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL3_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL3_DIR         0x00000002  // DMA Direction
#define USB_DMACTL3_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL3_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR3 register.
//
//*****************************************************************************
#define USB_DMAADDR3_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR3_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT3
// register.
//
//*****************************************************************************
#define USB_DMACOUNT3_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT3_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL4 register.
//
//*****************************************************************************
#define USB_DMACTL4_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL4_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL4_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL4_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
// length
#define USB_DMACTL4_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
// unspecified length
#define USB_DMACTL4_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL4_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL4_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL4_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL4_DIR         0x00000002  // DMA Direction
#define USB_DMACTL4_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL4_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR4 register.
//
//*****************************************************************************
#define USB_DMAADDR4_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR4_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT4
// register.
//
//*****************************************************************************
#define USB_DMACOUNT4_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT4_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL5 register.
//
//*****************************************************************************
#define USB_DMACTL5_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL5_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL5_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL5_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
// length
#define USB_DMACTL5_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
// unspecified length
#define USB_DMACTL5_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL5_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL5_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL5_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL5_DIR         0x00000002  // DMA Direction
#define USB_DMACTL5_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL5_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR5 register.
//
//*****************************************************************************
#define USB_DMAADDR5_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR5_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT5
// register.
//
//*****************************************************************************
#define USB_DMACOUNT5_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT5_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL6 register.
//
//*****************************************************************************
#define USB_DMACTL6_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL6_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL6_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL6_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
// length
#define USB_DMACTL6_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
// unspecified length
#define USB_DMACTL6_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL6_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL6_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL6_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL6_DIR         0x00000002  // DMA Direction
#define USB_DMACTL6_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL6_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR6 register.
//
//*****************************************************************************
#define USB_DMAADDR6_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR6_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT6
// register.
//
//*****************************************************************************
#define USB_DMACOUNT6_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT6_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACTL7 register.
//
//*****************************************************************************
#define USB_DMACTL7_BRSTM_M     0x00000600  // Burst Mode
#define USB_DMACTL7_BRSTM_ANY   0x00000000  // Bursts of unspecified length
#define USB_DMACTL7_BRSTM_INC4  0x00000200  // INCR4 or unspecified length
#define USB_DMACTL7_BRSTM_INC8  0x00000400  // INCR8, INCR4 or unspecified
// length
#define USB_DMACTL7_BRSTM_INC16 0x00000600  // INCR16, INCR8, INCR4 or
// unspecified length
#define USB_DMACTL7_ERR         0x00000100  // Bus Error Bit
#define USB_DMACTL7_EP_M        0x000000F0  // Endpoint number
#define USB_DMACTL7_IE          0x00000008  // DMA Interrupt Enable
#define USB_DMACTL7_MODE        0x00000004  // DMA Transfer Mode
#define USB_DMACTL7_DIR         0x00000002  // DMA Direction
#define USB_DMACTL7_ENABLE      0x00000001  // DMA Transfer Enable
#define USB_DMACTL7_EP_S        4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMAADDR7 register.
//
//*****************************************************************************
#define USB_DMAADDR7_ADDR_M     0xFFFFFFFC  // DMA Address
#define USB_DMAADDR7_ADDR_S     2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DMACOUNT7
// register.
//
//*****************************************************************************
#define USB_DMACOUNT7_COUNT_M   0xFFFFFFFC  // DMA Count
#define USB_DMACOUNT7_COUNT_S   2

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT1
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT1_M       0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT1_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT2
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT2_M       0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT2_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT3
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT3_M       0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT3_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT4
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT4_COUNT_M 0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT4_COUNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT5
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT5_COUNT_M 0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT5_COUNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT6
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT6_COUNT_M 0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT6_COUNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RQPKTCOUNT7
// register.
//
//*****************************************************************************
#define USB_RQPKTCOUNT7_COUNT_M 0x0000FFFF  // Block Transfer Packet Count
#define USB_RQPKTCOUNT7_COUNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_RXDPKTBUFDIS
// register.
//
//*****************************************************************************
#define USB_RXDPKTBUFDIS_EP7    0x00000080  // EP7 RX Double-Packet Buffer
// Disable
#define USB_RXDPKTBUFDIS_EP6    0x00000040  // EP6 RX Double-Packet Buffer
// Disable
#define USB_RXDPKTBUFDIS_EP5    0x00000020  // EP5 RX Double-Packet Buffer
// Disable
#define USB_RXDPKTBUFDIS_EP4    0x00000010  // EP4 RX Double-Packet Buffer
// Disable
#define USB_RXDPKTBUFDIS_EP3    0x00000008  // EP3 RX Double-Packet Buffer
// Disable
#define USB_RXDPKTBUFDIS_EP2    0x00000004  // EP2 RX Double-Packet Buffer
// Disable
#define USB_RXDPKTBUFDIS_EP1    0x00000002  // EP1 RX Double-Packet Buffer
// Disable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_TXDPKTBUFDIS
// register.
//
//*****************************************************************************
#define USB_TXDPKTBUFDIS_EP7    0x00000080  // EP7 TX Double-Packet Buffer
// Disable
#define USB_TXDPKTBUFDIS_EP6    0x00000040  // EP6 TX Double-Packet Buffer
// Disable
#define USB_TXDPKTBUFDIS_EP5    0x00000020  // EP5 TX Double-Packet Buffer
// Disable
#define USB_TXDPKTBUFDIS_EP4    0x00000010  // EP4 TX Double-Packet Buffer
// Disable
#define USB_TXDPKTBUFDIS_EP3    0x00000008  // EP3 TX Double-Packet Buffer
// Disable
#define USB_TXDPKTBUFDIS_EP2    0x00000004  // EP2 TX Double-Packet Buffer
// Disable
#define USB_TXDPKTBUFDIS_EP1    0x00000002  // EP1 TX Double-Packet Buffer
// Disable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CTO register.
//
//*****************************************************************************
#define USB_CTO_CCTV_M          0x0000FFFF  // Configurable Chirp Timeout Value
#define USB_CTO_CCTV_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_HHSRTN register.
//
//*****************************************************************************
#define USB_HHSRTN_HHSRTN_M     0x0000FFFF  // HIgh Speed to UTM Operating
// Delay
#define USB_HHSRTN_HHSRTN_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_HSBT register.
//
//*****************************************************************************
#define USB_HSBT_HSBT_M         0x0000000F  // High Speed Timeout Adder
#define USB_HSBT_HSBT_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMATTR register.
//
//*****************************************************************************
#define USB_LPMATTR_ENDPT_M     0x0000F000  // Endpoint
#define USB_LPMATTR_RMTWAK      0x00000100  // Remote Wake
#define USB_LPMATTR_HIRD_M      0x000000F0  // Host Initiated Resume Duration
#define USB_LPMATTR_LS_M        0x0000000F  // Link State
#define USB_LPMATTR_LS_L1       0x00000001  // Sleep State (L1)
#define USB_LPMATTR_ENDPT_S     12
#define USB_LPMATTR_HIRD_S      4

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMCNTRL register.
//
//*****************************************************************************
#define USB_LPMCNTRL_NAK        0x00000010  // LPM NAK
#define USB_LPMCNTRL_EN_M       0x0000000C  // LPM Enable
#define USB_LPMCNTRL_EN_NONE    0x00000000  // LPM and Extended transactions
// are not supported. In this case,
// the USB does not respond to LPM
// transactions and LPM
// transactions cause a timeout
#define USB_LPMCNTRL_EN_EXT     0x00000004  // LPM is not supported but
// extended transactions are
// supported. In this case, the USB
// does respond to an LPM
// transaction with a STALL
#define USB_LPMCNTRL_EN_LPMEXT  0x0000000C  // The USB supports LPM extended
// transactions. In this case, the
// USB responds with a NYET or an
// ACK as determined by the value
// of TXLPM and other conditions
#define USB_LPMCNTRL_RES        0x00000002  // LPM Resume
#define USB_LPMCNTRL_TXLPM      0x00000001  // Transmit LPM Transaction Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMIM register.
//
//*****************************************************************************
#define USB_LPMIM_ERR           0x00000020  // LPM Error Interrupt Mask
#define USB_LPMIM_RES           0x00000010  // LPM Resume Interrupt Mask
#define USB_LPMIM_NC            0x00000008  // LPM NC Interrupt Mask
#define USB_LPMIM_ACK           0x00000004  // LPM ACK Interrupt Mask
#define USB_LPMIM_NY            0x00000002  // LPM NY Interrupt Mask
#define USB_LPMIM_STALL         0x00000001  // LPM STALL Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMRIS register.
//
//*****************************************************************************
#define USB_LPMRIS_ERR          0x00000020  // LPM Interrupt Status
#define USB_LPMRIS_RES          0x00000010  // LPM Resume Interrupt Status
#define USB_LPMRIS_NC           0x00000008  // LPM NC Interrupt Status
#define USB_LPMRIS_ACK          0x00000004  // LPM ACK Interrupt Status
#define USB_LPMRIS_NY           0x00000002  // LPM NY Interrupt Status
#define USB_LPMRIS_LPMST        0x00000001  // LPM STALL Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_LPMFADDR register.
//
//*****************************************************************************
#define USB_LPMFADDR_ADDR_M     0x0000007F  // LPM Function Address
#define USB_LPMFADDR_ADDR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPC register.
//
//*****************************************************************************
#define USB_EPC_PFLTACT_M       0x00000300  // Power Fault Action
#define USB_EPC_PFLTACT_UNCHG   0x00000000  // Unchanged
#define USB_EPC_PFLTACT_TRIS    0x00000100  // Tristate
#define USB_EPC_PFLTACT_LOW     0x00000200  // Low
#define USB_EPC_PFLTACT_HIGH    0x00000300  // High
#define USB_EPC_PFLTAEN         0x00000040  // Power Fault Action Enable
#define USB_EPC_PFLTSEN_HIGH    0x00000020  // Power Fault Sense
#define USB_EPC_PFLTEN          0x00000010  // Power Fault Input Enable
#define USB_EPC_EPENDE          0x00000004  // EPEN Drive Enable
#define USB_EPC_EPEN_M          0x00000003  // External Power Supply Enable
// Configuration
#define USB_EPC_EPEN_LOW        0x00000000  // Power Enable Active Low
#define USB_EPC_EPEN_HIGH       0x00000001  // Power Enable Active High
#define USB_EPC_EPEN_VBLOW      0x00000002  // Power Enable High if VBUS Low
// (OTG only)
#define USB_EPC_EPEN_VBHIGH     0x00000003  // Power Enable High if VBUS High
// (OTG only)

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPCRIS register.
//
//*****************************************************************************
#define USB_EPCRIS_PF           0x00000001  // USB Power Fault Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPCIM register.
//
//*****************************************************************************
#define USB_EPCIM_PF            0x00000001  // USB Power Fault Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_EPCISC register.
//
//*****************************************************************************
#define USB_EPCISC_PF           0x00000001  // USB Power Fault Interrupt Status
// and Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DRRIS register.
//
//*****************************************************************************
#define USB_DRRIS_RESUME        0x00000001  // RESUME Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DRIM register.
//
//*****************************************************************************
#define USB_DRIM_RESUME         0x00000001  // RESUME Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_DRISC register.
//
//*****************************************************************************
#define USB_DRISC_RESUME        0x00000001  // RESUME Interrupt Status and
// Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_GPCS register.
//
//*****************************************************************************
#define USB_GPCS_DEVMOD_M       0x00000007  // Device Mode
#define USB_GPCS_DEVMOD_OTG     0x00000000  // Use USB0VBUS and USB0ID pin
#define USB_GPCS_DEVMOD_HOST    0x00000002  // Force USB0VBUS and USB0ID low
#define USB_GPCS_DEVMOD_DEV     0x00000003  // Force USB0VBUS and USB0ID high
#define USB_GPCS_DEVMOD_HOSTVBUS                                              \
                                0x00000004  // Use USB0VBUS and force USB0ID
// low
#define USB_GPCS_DEVMOD_DEVVBUS 0x00000005  // Use USB0VBUS and force USB0ID
// high

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VDC register.
//
//*****************************************************************************
#define USB_VDC_VBDEN           0x00000001  // VBUS Droop Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VDCRIS register.
//
//*****************************************************************************
#define USB_VDCRIS_VD           0x00000001  // VBUS Droop Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VDCIM register.
//
//*****************************************************************************
#define USB_VDCIM_VD            0x00000001  // VBUS Droop Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_VDCISC register.
//
//*****************************************************************************
#define USB_VDCISC_VD           0x00000001  // VBUS Droop Interrupt Status and
// Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_PP register.
//
//*****************************************************************************
#define USB_PP_ECNT_M           0x0000FF00  // Endpoint Count
#define USB_PP_USB_M            0x000000C0  // USB Capability
#define USB_PP_USB_DEVICE       0x00000040  // DEVICE
#define USB_PP_USB_HOSTDEVICE   0x00000080  // HOST
#define USB_PP_USB_OTG          0x000000C0  // OTG
#define USB_PP_ULPI             0x00000020  // ULPI Present
#define USB_PP_PHY              0x00000010  // PHY Present
#define USB_PP_TYPE_M           0x0000000F  // Controller Type
#define USB_PP_TYPE_0           0x00000000  // The first-generation USB
// controller
#define USB_PP_TYPE_1           0x00000001  // The second-generation USB
// controller revision
#define USB_PP_ECNT_S           8

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_PC register.
//
//*****************************************************************************
#define USB_PC_ULPIEN           0x00010000  // ULPI Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the USB_O_CC register.
//
//*****************************************************************************
#define USB_CC_CLKEN            0x00000200  // USB Clock Enable
#define USB_CC_CSD              0x00000100  // Clock Source/Direction
#define USB_CC_CLKDIV_M         0x0000000F  // PLL Clock Divisor
#define USB_CC_CLKDIV_S         0


//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_IM register.
//
//*****************************************************************************
#define GPIO_IM_DMAIME          0x00000100  // GPIO uDMA Done Interrupt Mask
// Enable
#define GPIO_IM_GPIO_M          0x000000FF  // GPIO Interrupt Mask Enable
#define GPIO_IM_GPIO_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_RIS register.
//
//*****************************************************************************
#define GPIO_RIS_DMARIS         0x00000100  // GPIO uDMA Done Interrupt Raw
// Status
#define GPIO_RIS_GPIO_M         0x000000FF  // GPIO Interrupt Raw Status
#define GPIO_RIS_GPIO_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_MIS register.
//
//*****************************************************************************
#define GPIO_MIS_DMAMIS         0x00000100  // GPIO uDMA Done Masked Interrupt
// Status
#define GPIO_MIS_GPIO_M         0x000000FF  // GPIO Masked Interrupt Status
#define GPIO_MIS_GPIO_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_ICR register.
//
//*****************************************************************************
#define GPIO_ICR_DMAIC          0x00000100  // GPIO uDMA Interrupt Clear
#define GPIO_ICR_GPIO_M         0x000000FF  // GPIO Interrupt Clear
#define GPIO_ICR_GPIO_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_LOCK register.
//
//*****************************************************************************
#define GPIO_LOCK_M             0xFFFFFFFF  // GPIO Lock
#define GPIO_LOCK_UNLOCKED      0x00000000  // The GPIOCR register is unlocked
// and may be modified
#define GPIO_LOCK_LOCKED        0x00000001  // The GPIOCR register is locked
// and may not be modified
#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_SI register.
//
//*****************************************************************************
#define GPIO_SI_SUM             0x00000001  // Summary Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_DR12R register.
//
//*****************************************************************************
#define GPIO_DR12R_DRV12_M      0x000000FF  // Output Pad 12-mA Drive Enable
#define GPIO_DR12R_DRV12_12MA   0x00000001  // The corresponding GPIO pin has
// 12-mA drive. This encoding is
// only valid if the GPIOPP EDE bit
// is set and the appropriate
// GPIOPC EDM bit field is
// programmed to 0x3

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_WAKEPEN register.
//
//*****************************************************************************
#define GPIO_WAKEPEN_WAKEP4     0x00000010  // P[4] Wake Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_WAKELVL register.
//
//*****************************************************************************
#define GPIO_WAKELVL_WAKELVL4   0x00000010  // P[4] Wake Level

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_WAKESTAT
// register.
//
//*****************************************************************************
#define GPIO_WAKESTAT_STAT4     0x00000010  // P[4] Wake Status

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_PP register.
//
//*****************************************************************************
#define GPIO_PP_EDE             0x00000001  // Extended Drive Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_PC register.
//
//*****************************************************************************
#define GPIO_PC_EDM7_M          0x0000C000  // Extended Drive Mode Bit 7
#define GPIO_PC_EDM6_M          0x00003000  // Extended Drive Mode Bit 6
#define GPIO_PC_EDM5_M          0x00000C00  // Extended Drive Mode Bit 5
#define GPIO_PC_EDM4_M          0x00000300  // Extended Drive Mode Bit 4
#define GPIO_PC_EDM3_M          0x000000C0  // Extended Drive Mode Bit 3
#define GPIO_PC_EDM2_M          0x00000030  // Extended Drive Mode Bit 2
#define GPIO_PC_EDM1_M          0x0000000C  // Extended Drive Mode Bit 1
#define GPIO_PC_EDM0_M          0x00000003  // Extended Drive Mode Bit 0
#define GPIO_PC_EDM0_DISABLE    0x00000000  // Drive values of 2, 4 and 8 mA
// are maintained. GPIO n Drive
// Select (GPIODRnR) registers
// function as normal
#define GPIO_PC_EDM0_6MA        0x00000001  // An additional 6 mA option is
// provided
#define GPIO_PC_EDM0_PLUS2MA    0x00000003  // A 2 mA driver is always enabled;
// setting the corresponding
// GPIODR4R register bit adds 2 mA
// and setting the corresponding
// GPIODR8R of GPIODR12R register
// bit adds an additional 4 mA
#define GPIO_PC_EDM7_S          14
#define GPIO_PC_EDM6_S          12
#define GPIO_PC_EDM5_S          10
#define GPIO_PC_EDM4_S          8
#define GPIO_PC_EDM3_S          6
#define GPIO_PC_EDM2_S          4
#define GPIO_PC_EDM1_S          2

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EESIZE register.
//
//*****************************************************************************
#define EEPROM_EESIZE_BLKCNT_M  0x07FF0000  // Number of 16-Word Blocks
#define EEPROM_EESIZE_WORDCNT_M 0x0000FFFF  // Number of 32-Bit Words
#define EEPROM_EESIZE_BLKCNT_S  16
#define EEPROM_EESIZE_WORDCNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEBLOCK register.
//
//*****************************************************************************
#define EEPROM_EEBLOCK_BLOCK_M  0x0000FFFF  // Current Block
#define EEPROM_EEBLOCK_BLOCK_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEOFFSET
// register.
//
//*****************************************************************************
#define EEPROM_EEOFFSET_OFFSET_M                                              \
                                0x0000000F  // Current Address Offset
#define EEPROM_EEOFFSET_OFFSET_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EERDWR register.
//
//*****************************************************************************
#define EEPROM_EERDWR_VALUE_M   0xFFFFFFFF  // EEPROM Read or Write Data
#define EEPROM_EERDWR_VALUE_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EERDWRINC
// register.
//
//*****************************************************************************
#define EEPROM_EERDWRINC_VALUE_M                                              \
                                0xFFFFFFFF  // EEPROM Read or Write Data with
// Increment
#define EEPROM_EERDWRINC_VALUE_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEDONE register.
//
//*****************************************************************************
#define EEPROM_EEDONE_WRBUSY    0x00000020  // Write Busy
#define EEPROM_EEDONE_NOPERM    0x00000010  // Write Without Permission
#define EEPROM_EEDONE_WKCOPY    0x00000008  // Working on a Copy
#define EEPROM_EEDONE_WKERASE   0x00000004  // Working on an Erase
#define EEPROM_EEDONE_WORKING   0x00000001  // EEPROM Working

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EESUPP register.
//
//*****************************************************************************
#define EEPROM_EESUPP_PRETRY    0x00000008  // Programming Must Be Retried
#define EEPROM_EESUPP_ERETRY    0x00000004  // Erase Must Be Retried

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEUNLOCK
// register.
//
//*****************************************************************************
#define EEPROM_EEUNLOCK_UNLOCK_M                                              \
                                0xFFFFFFFF  // EEPROM Unlock

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEPROT register.
//
//*****************************************************************************
#define EEPROM_EEPROT_ACC       0x00000008  // Access Control
#define EEPROM_EEPROT_PROT_M    0x00000007  // Protection Control
#define EEPROM_EEPROT_PROT_RWNPW                                              \
                                0x00000000  // This setting is the default. If
// there is no password, the block
// is not protected and is readable
// and writable
#define EEPROM_EEPROT_PROT_RWPW 0x00000001  // If there is a password, the
// block is readable or writable
// only when unlocked
#define EEPROM_EEPROT_PROT_RONPW                                              \
                                0x00000002  // If there is no password, the
// block is readable, not writable

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEPASS0 register.
//
//*****************************************************************************
#define EEPROM_EEPASS0_PASS_M   0xFFFFFFFF  // Password
#define EEPROM_EEPASS0_PASS_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEPASS1 register.
//
//*****************************************************************************
#define EEPROM_EEPASS1_PASS_M   0xFFFFFFFF  // Password
#define EEPROM_EEPASS1_PASS_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEPASS2 register.
//
//*****************************************************************************
#define EEPROM_EEPASS2_PASS_M   0xFFFFFFFF  // Password
#define EEPROM_EEPASS2_PASS_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEINT register.
//
//*****************************************************************************
#define EEPROM_EEINT_INT        0x00000001  // Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEHIDE0 register.
//
//*****************************************************************************
#define EEPROM_EEHIDE0_HN_M     0xFFFFFFFE  // Hide Block

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEHIDE1 register.
//
//*****************************************************************************
#define EEPROM_EEHIDE1_HN_M     0xFFFFFFFF  // Hide Block

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEHIDE2 register.
//
//*****************************************************************************
#define EEPROM_EEHIDE2_HN_M     0xFFFFFFFF  // Hide Block

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_EEDBGME register.
//
//*****************************************************************************
#define EEPROM_EEDBGME_KEY_M    0xFFFF0000  // Erase Key
#define EEPROM_EEDBGME_ME       0x00000001  // Mass Erase
#define EEPROM_EEDBGME_KEY_S    16

//*****************************************************************************
//
// The following are defines for the bit fields in the EEPROM_PP register.
//
//*****************************************************************************
#define EEPROM_PP_SIZE_M        0x0000FFFF  // EEPROM Size
#define EEPROM_PP_SIZE_64       0x00000000  // 64 bytes of EEPROM
#define EEPROM_PP_SIZE_128      0x00000001  // 128 bytes of EEPROM
#define EEPROM_PP_SIZE_256      0x00000003  // 256 bytes of EEPROM
#define EEPROM_PP_SIZE_512      0x00000007  // 512 bytes of EEPROM
#define EEPROM_PP_SIZE_1K       0x0000000F  // 1 KB of EEPROM
#define EEPROM_PP_SIZE_2K       0x0000001F  // 2 KB of EEPROM
#define EEPROM_PP_SIZE_3K       0x0000003F  // 3 KB of EEPROM
#define EEPROM_PP_SIZE_4K       0x0000007F  // 4 KB of EEPROM
#define EEPROM_PP_SIZE_5K       0x000000FF  // 5 KB of EEPROM
#define EEPROM_PP_SIZE_6K       0x000001FF  // 6 KB of EEPROM

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_CFG register.
//
//*****************************************************************************
#define EPI_CFG_INTDIV          0x00000100  // Integer Clock Divider Enable
#define EPI_CFG_BLKEN           0x00000010  // Block Enable
#define EPI_CFG_MODE_M          0x0000000F  // Mode Select
#define EPI_CFG_MODE_NONE       0x00000000  // General Purpose
#define EPI_CFG_MODE_SDRAM      0x00000001  // SDRAM
#define EPI_CFG_MODE_HB8        0x00000002  // 8-Bit Host-Bus (HB8)
#define EPI_CFG_MODE_HB16       0x00000003  // 16-Bit Host-Bus (HB16)

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_BAUD register.
//
//*****************************************************************************
#define EPI_BAUD_COUNT1_M       0xFFFF0000  // Baud Rate Counter 1
#define EPI_BAUD_COUNT0_M       0x0000FFFF  // Baud Rate Counter 0
#define EPI_BAUD_COUNT1_S       16
#define EPI_BAUD_COUNT0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_BAUD2 register.
//
//*****************************************************************************
#define EPI_BAUD2_COUNT1_M      0xFFFF0000  // CS3n Baud Rate Counter 1
#define EPI_BAUD2_COUNT0_M      0x0000FFFF  // CS2n Baud Rate Counter 0
#define EPI_BAUD2_COUNT1_S      16
#define EPI_BAUD2_COUNT0_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB16CFG register.
//
//*****************************************************************************
#define EPI_HB16CFG_CLKGATE     0x80000000  // Clock Gated
#define EPI_HB16CFG_CLKGATEI    0x40000000  // Clock Gated Idle
#define EPI_HB16CFG_CLKINV      0x20000000  // Invert Output Clock Enable
#define EPI_HB16CFG_RDYEN       0x10000000  // Input Ready Enable
#define EPI_HB16CFG_IRDYINV     0x08000000  // Input Ready Invert
#define EPI_HB16CFG_XFFEN       0x00800000  // External FIFO FULL Enable
#define EPI_HB16CFG_XFEEN       0x00400000  // External FIFO EMPTY Enable
#define EPI_HB16CFG_WRHIGH      0x00200000  // WRITE Strobe Polarity
#define EPI_HB16CFG_RDHIGH      0x00100000  // READ Strobe Polarity
#define EPI_HB16CFG_ALEHIGH     0x00080000  // ALE Strobe Polarity
#define EPI_HB16CFG_WRCRE       0x00040000  // PSRAM Configuration Register
// Write
#define EPI_HB16CFG_RDCRE       0x00020000  // PSRAM Configuration Register
// Read
#define EPI_HB16CFG_BURST       0x00010000  // Burst Mode
#define EPI_HB16CFG_MAXWAIT_M   0x0000FF00  // Maximum Wait
#define EPI_HB16CFG_WRWS_M      0x000000C0  // Write Wait States
#define EPI_HB16CFG_WRWS_2      0x00000000  // Active WRn is 2 EPI clocks
#define EPI_HB16CFG_WRWS_4      0x00000040  // Active WRn is 4 EPI clocks
#define EPI_HB16CFG_WRWS_6      0x00000080  // Active WRn is 6 EPI clocks
#define EPI_HB16CFG_WRWS_8      0x000000C0  // Active WRn is 8 EPI clocks
#define EPI_HB16CFG_RDWS_M      0x00000030  // Read Wait States
#define EPI_HB16CFG_RDWS_2      0x00000000  // Active RDn is 2 EPI clocks
#define EPI_HB16CFG_RDWS_4      0x00000010  // Active RDn is 4 EPI clocks
#define EPI_HB16CFG_RDWS_6      0x00000020  // Active RDn is 6 EPI clocks
#define EPI_HB16CFG_RDWS_8      0x00000030  // Active RDn is 8 EPI clocks
#define EPI_HB16CFG_BSEL        0x00000004  // Byte Select Configuration
#define EPI_HB16CFG_MODE_M      0x00000003  // Host Bus Sub-Mode
#define EPI_HB16CFG_MODE_ADMUX  0x00000000  // ADMUX - AD[15:0]
#define EPI_HB16CFG_MODE_ADNMUX 0x00000001  // ADNONMUX - D[15:0]
#define EPI_HB16CFG_MODE_SRAM   0x00000002  // Continuous Read - D[15:0]
#define EPI_HB16CFG_MODE_XFIFO  0x00000003  // XFIFO - D[15:0]
#define EPI_HB16CFG_MAXWAIT_S   8

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_GPCFG register.
//
//*****************************************************************************
#define EPI_GPCFG_CLKPIN        0x80000000  // Clock Pin
#define EPI_GPCFG_CLKGATE       0x40000000  // Clock Gated
#define EPI_GPCFG_FRM50         0x04000000  // 50/50 Frame
#define EPI_GPCFG_FRMCNT_M      0x03C00000  // Frame Count
#define EPI_GPCFG_WR2CYC        0x00080000  // 2-Cycle Writes
#define EPI_GPCFG_ASIZE_M       0x00000030  // Address Bus Size
#define EPI_GPCFG_ASIZE_NONE    0x00000000  // No address
#define EPI_GPCFG_ASIZE_4BIT    0x00000010  // Up to 4 bits wide
#define EPI_GPCFG_ASIZE_12BIT   0x00000020  // Up to 12 bits wide. This size
// cannot be used with 24-bit data
#define EPI_GPCFG_ASIZE_20BIT   0x00000030  // Up to 20 bits wide. This size
// cannot be used with data sizes
// other than 8
#define EPI_GPCFG_DSIZE_M       0x00000003  // Size of Data Bus
#define EPI_GPCFG_DSIZE_4BIT    0x00000000  // 8 Bits Wide (EPI0S0 to EPI0S7)
#define EPI_GPCFG_DSIZE_16BIT   0x00000001  // 16 Bits Wide (EPI0S0 to EPI0S15)
#define EPI_GPCFG_DSIZE_24BIT   0x00000002  // 24 Bits Wide (EPI0S0 to EPI0S23)
#define EPI_GPCFG_DSIZE_32BIT   0x00000003  // 32 Bits Wide (EPI0S0 to EPI0S31)
#define EPI_GPCFG_FRMCNT_S      22

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_SDRAMCFG register.
//
//*****************************************************************************
#define EPI_SDRAMCFG_FREQ_M     0xC0000000  // EPI Frequency Range
#define EPI_SDRAMCFG_FREQ_NONE  0x00000000  // 0 - 15 MHz
#define EPI_SDRAMCFG_FREQ_15MHZ 0x40000000  // 15 - 30 MHz
#define EPI_SDRAMCFG_FREQ_30MHZ 0x80000000  // 30 - 50 MHz
#define EPI_SDRAMCFG_RFSH_M     0x07FF0000  // Refresh Counter
#define EPI_SDRAMCFG_SLEEP      0x00000200  // Sleep Mode
#define EPI_SDRAMCFG_SIZE_M     0x00000003  // Size of SDRAM
#define EPI_SDRAMCFG_SIZE_8MB   0x00000000  // 64 megabits (8MB)
#define EPI_SDRAMCFG_SIZE_16MB  0x00000001  // 128 megabits (16MB)
#define EPI_SDRAMCFG_SIZE_32MB  0x00000002  // 256 megabits (32MB)
#define EPI_SDRAMCFG_SIZE_64MB  0x00000003  // 512 megabits (64MB)
#define EPI_SDRAMCFG_RFSH_S     16

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB8CFG register.
//
//*****************************************************************************
#define EPI_HB8CFG_CLKGATE      0x80000000  // Clock Gated
#define EPI_HB8CFG_CLKGATEI     0x40000000  // Clock Gated when Idle
#define EPI_HB8CFG_CLKINV       0x20000000  // Invert Output Clock Enable
#define EPI_HB8CFG_RDYEN        0x10000000  // Input Ready Enable
#define EPI_HB8CFG_IRDYINV      0x08000000  // Input Ready Invert
#define EPI_HB8CFG_XFFEN        0x00800000  // External FIFO FULL Enable
#define EPI_HB8CFG_XFEEN        0x00400000  // External FIFO EMPTY Enable
#define EPI_HB8CFG_WRHIGH       0x00200000  // WRITE Strobe Polarity
#define EPI_HB8CFG_RDHIGH       0x00100000  // READ Strobe Polarity
#define EPI_HB8CFG_ALEHIGH      0x00080000  // ALE Strobe Polarity
#define EPI_HB8CFG_MAXWAIT_M    0x0000FF00  // Maximum Wait
#define EPI_HB8CFG_WRWS_M       0x000000C0  // Write Wait States
#define EPI_HB8CFG_WRWS_2       0x00000000  // Active WRn is 2 EPI clocks
#define EPI_HB8CFG_WRWS_4       0x00000040  // Active WRn is 4 EPI clocks
#define EPI_HB8CFG_WRWS_6       0x00000080  // Active WRn is 6 EPI clocks
#define EPI_HB8CFG_WRWS_8       0x000000C0  // Active WRn is 8 EPI clocks
#define EPI_HB8CFG_RDWS_M       0x00000030  // Read Wait States
#define EPI_HB8CFG_RDWS_2       0x00000000  // Active RDn is 2 EPI clocks
#define EPI_HB8CFG_RDWS_4       0x00000010  // Active RDn is 4 EPI clocks
#define EPI_HB8CFG_RDWS_6       0x00000020  // Active RDn is 6 EPI clocks
#define EPI_HB8CFG_RDWS_8       0x00000030  // Active RDn is 8 EPI clocks
#define EPI_HB8CFG_MODE_M       0x00000003  // Host Bus Sub-Mode
#define EPI_HB8CFG_MODE_MUX     0x00000000  // ADMUX - AD[7:0]
#define EPI_HB8CFG_MODE_NMUX    0x00000001  // ADNONMUX - D[7:0]
#define EPI_HB8CFG_MODE_SRAM    0x00000002  // Continuous Read - D[7:0]
#define EPI_HB8CFG_MODE_FIFO    0x00000003  // XFIFO - D[7:0]
#define EPI_HB8CFG_MAXWAIT_S    8

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB8CFG2 register.
//
//*****************************************************************************
#define EPI_HB8CFG2_CSCFGEXT    0x08000000  // Chip Select Extended
// Configuration
#define EPI_HB8CFG2_CSBAUD      0x04000000  // Chip Select Baud Rate and
// Multiple Sub-Mode Configuration
// enable
#define EPI_HB8CFG2_CSCFG_M     0x03000000  // Chip Select Configuration
#define EPI_HB8CFG2_CSCFG_ALE   0x00000000  // ALE Configuration
#define EPI_HB8CFG2_CSCFG_CS    0x01000000  // CSn Configuration
#define EPI_HB8CFG2_CSCFG_DCS   0x02000000  // Dual CSn Configuration
#define EPI_HB8CFG2_CSCFG_ADCS  0x03000000  // ALE with Dual CSn Configuration
#define EPI_HB8CFG2_WRHIGH      0x00200000  // CS1n WRITE Strobe Polarity
#define EPI_HB8CFG2_RDHIGH      0x00100000  // CS1n READ Strobe Polarity
#define EPI_HB8CFG2_ALEHIGH     0x00080000  // CS1n ALE Strobe Polarity
#define EPI_HB8CFG2_WRWS_M      0x000000C0  // CS1n Write Wait States
#define EPI_HB8CFG2_WRWS_2      0x00000000  // Active WRn is 2 EPI clocks
#define EPI_HB8CFG2_WRWS_4      0x00000040  // Active WRn is 4 EPI clocks
#define EPI_HB8CFG2_WRWS_6      0x00000080  // Active WRn is 6 EPI clocks
#define EPI_HB8CFG2_WRWS_8      0x000000C0  // Active WRn is 8 EPI clocks
#define EPI_HB8CFG2_RDWS_M      0x00000030  // CS1n Read Wait States
#define EPI_HB8CFG2_RDWS_2      0x00000000  // Active RDn is 2 EPI clocks
#define EPI_HB8CFG2_RDWS_4      0x00000010  // Active RDn is 4 EPI clocks
#define EPI_HB8CFG2_RDWS_6      0x00000020  // Active RDn is 6 EPI clocks
#define EPI_HB8CFG2_RDWS_8      0x00000030  // Active RDn is 8 EPI clocks
#define EPI_HB8CFG2_MODE_M      0x00000003  // CS1n Host Bus Sub-Mode
#define EPI_HB8CFG2_MODE_ADMUX  0x00000000  // ADMUX - AD[7:0]
#define EPI_HB8CFG2_MODE_AD     0x00000001  // ADNONMUX - D[7:0]

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB16CFG2 register.
//
//*****************************************************************************
#define EPI_HB16CFG2_CSCFGEXT   0x08000000  // Chip Select Extended
// Configuration
#define EPI_HB16CFG2_CSBAUD     0x04000000  // Chip Select Baud Rate and
// Multiple Sub-Mode Configuration
// enable
#define EPI_HB16CFG2_CSCFG_M    0x03000000  // Chip Select Configuration
#define EPI_HB16CFG2_CSCFG_ALE  0x00000000  // ALE Configuration
#define EPI_HB16CFG2_CSCFG_CS   0x01000000  // CSn Configuration
#define EPI_HB16CFG2_CSCFG_DCS  0x02000000  // Dual CSn Configuration
#define EPI_HB16CFG2_CSCFG_ADCS 0x03000000  // ALE with Dual CSn Configuration
#define EPI_HB16CFG2_WRHIGH     0x00200000  // CS1n WRITE Strobe Polarity
#define EPI_HB16CFG2_RDHIGH     0x00100000  // CS1n READ Strobe Polarity
#define EPI_HB16CFG2_ALEHIGH    0x00080000  // CS1n ALE Strobe Polarity
#define EPI_HB16CFG2_WRCRE      0x00040000  // CS1n PSRAM Configuration
// Register Write
#define EPI_HB16CFG2_RDCRE      0x00020000  // CS1n PSRAM Configuration
// Register Read
#define EPI_HB16CFG2_BURST      0x00010000  // CS1n Burst Mode
#define EPI_HB16CFG2_WRWS_M     0x000000C0  // CS1n Write Wait States
#define EPI_HB16CFG2_WRWS_2     0x00000000  // Active WRn is 2 EPI clocks
#define EPI_HB16CFG2_WRWS_4     0x00000040  // Active WRn is 4 EPI clocks
#define EPI_HB16CFG2_WRWS_6     0x00000080  // Active WRn is 6 EPI clocks
#define EPI_HB16CFG2_WRWS_8     0x000000C0  // Active WRn is 8 EPI clocks
#define EPI_HB16CFG2_RDWS_M     0x00000030  // CS1n Read Wait States
#define EPI_HB16CFG2_RDWS_2     0x00000000  // Active RDn is 2 EPI clocks
#define EPI_HB16CFG2_RDWS_4     0x00000010  // Active RDn is 4 EPI clocks
#define EPI_HB16CFG2_RDWS_6     0x00000020  // Active RDn is 6 EPI clocks
#define EPI_HB16CFG2_RDWS_8     0x00000030  // Active RDn is 8 EPI clocks
#define EPI_HB16CFG2_MODE_M     0x00000003  // CS1n Host Bus Sub-Mode
#define EPI_HB16CFG2_MODE_ADMUX 0x00000000  // ADMUX - AD[15:0]
#define EPI_HB16CFG2_MODE_AD    0x00000001  // ADNONMUX - D[15:0]

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_ADDRMAP register.
//
//*****************************************************************************
#define EPI_ADDRMAP_ECSZ_M      0x00000C00  // External Code Size
#define EPI_ADDRMAP_ECSZ_256B   0x00000000  // 256 bytes; lower address range:
// 0x00 to 0xFF
#define EPI_ADDRMAP_ECSZ_64KB   0x00000400  // 64 KB; lower address range:
// 0x0000 to 0xFFFF
#define EPI_ADDRMAP_ECSZ_16MB   0x00000800  // 16 MB; lower address range:
// 0x00.0000 to 0xFF.FFFF
#define EPI_ADDRMAP_ECSZ_256MB  0x00000C00  // 256MB; lower address range:
// 0x000.0000 to 0x0FFF.FFFF
#define EPI_ADDRMAP_ECADR_M     0x00000300  // External Code Address
#define EPI_ADDRMAP_ECADR_NONE  0x00000000  // Not mapped
#define EPI_ADDRMAP_ECADR_1000  0x00000100  // At 0x1000.0000
#define EPI_ADDRMAP_EPSZ_M      0x000000C0  // External Peripheral Size
#define EPI_ADDRMAP_EPSZ_256B   0x00000000  // 256 bytes; lower address range:
// 0x00 to 0xFF
#define EPI_ADDRMAP_EPSZ_64KB   0x00000040  // 64 KB; lower address range:
// 0x0000 to 0xFFFF
#define EPI_ADDRMAP_EPSZ_16MB   0x00000080  // 16 MB; lower address range:
// 0x00.0000 to 0xFF.FFFF
#define EPI_ADDRMAP_EPSZ_256MB  0x000000C0  // 256 MB; lower address range:
// 0x000.0000 to 0xFFF.FFFF
#define EPI_ADDRMAP_EPADR_M     0x00000030  // External Peripheral Address
#define EPI_ADDRMAP_EPADR_NONE  0x00000000  // Not mapped
#define EPI_ADDRMAP_EPADR_A000  0x00000010  // At 0xA000.0000
#define EPI_ADDRMAP_EPADR_C000  0x00000020  // At 0xC000.0000
#define EPI_ADDRMAP_EPADR_HBQS  0x00000030  // Only to be used with Host Bus
// quad chip select. In quad chip
// select mode, CS2n maps to
// 0xA000.0000 and CS3n maps to
// 0xC000.0000
#define EPI_ADDRMAP_ERSZ_M      0x0000000C  // External RAM Size
#define EPI_ADDRMAP_ERSZ_256B   0x00000000  // 256 bytes; lower address range:
// 0x00 to 0xFF
#define EPI_ADDRMAP_ERSZ_64KB   0x00000004  // 64 KB; lower address range:
// 0x0000 to 0xFFFF
#define EPI_ADDRMAP_ERSZ_16MB   0x00000008  // 16 MB; lower address range:
// 0x00.0000 to 0xFF.FFFF
#define EPI_ADDRMAP_ERSZ_256MB  0x0000000C  // 256 MB; lower address range:
// 0x000.0000 to 0xFFF.FFFF
#define EPI_ADDRMAP_ERADR_M     0x00000003  // External RAM Address
#define EPI_ADDRMAP_ERADR_NONE  0x00000000  // Not mapped
#define EPI_ADDRMAP_ERADR_6000  0x00000001  // At 0x6000.0000
#define EPI_ADDRMAP_ERADR_8000  0x00000002  // At 0x8000.0000
#define EPI_ADDRMAP_ERADR_HBQS  0x00000003  // Only to be used with Host Bus
// quad chip select. In quad chip
// select mode, CS0n maps to
// 0x6000.0000 and CS1n maps to
// 0x8000.0000

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_RSIZE0 register.
//
//*****************************************************************************
#define EPI_RSIZE0_SIZE_M       0x00000003  // Current Size
#define EPI_RSIZE0_SIZE_8BIT    0x00000001  // Byte (8 bits)
#define EPI_RSIZE0_SIZE_16BIT   0x00000002  // Half-word (16 bits)
#define EPI_RSIZE0_SIZE_32BIT   0x00000003  // Word (32 bits)

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_RADDR0 register.
//
//*****************************************************************************
#define EPI_RADDR0_ADDR_M       0xFFFFFFFF  // Current Address
#define EPI_RADDR0_ADDR_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_RPSTD0 register.
//
//*****************************************************************************
#define EPI_RPSTD0_POSTCNT_M    0x00001FFF  // Post Count
#define EPI_RPSTD0_POSTCNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_RSIZE1 register.
//
//*****************************************************************************
#define EPI_RSIZE1_SIZE_M       0x00000003  // Current Size
#define EPI_RSIZE1_SIZE_8BIT    0x00000001  // Byte (8 bits)
#define EPI_RSIZE1_SIZE_16BIT   0x00000002  // Half-word (16 bits)
#define EPI_RSIZE1_SIZE_32BIT   0x00000003  // Word (32 bits)

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_RADDR1 register.
//
//*****************************************************************************
#define EPI_RADDR1_ADDR_M       0xFFFFFFFF  // Current Address
#define EPI_RADDR1_ADDR_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_RPSTD1 register.
//
//*****************************************************************************
#define EPI_RPSTD1_POSTCNT_M    0x00001FFF  // Post Count
#define EPI_RPSTD1_POSTCNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_STAT register.
//
//*****************************************************************************
#define EPI_STAT_XFFULL         0x00000100  // External FIFO Full
#define EPI_STAT_XFEMPTY        0x00000080  // External FIFO Empty
#define EPI_STAT_INITSEQ        0x00000040  // Initialization Sequence
#define EPI_STAT_WBUSY          0x00000020  // Write Busy
#define EPI_STAT_NBRBUSY        0x00000010  // Non-Blocking Read Busy
#define EPI_STAT_ACTIVE         0x00000001  // Register Active

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_RFIFOCNT register.
//
//*****************************************************************************
#define EPI_RFIFOCNT_COUNT_M    0x0000000F  // FIFO Count
#define EPI_RFIFOCNT_COUNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_READFIFO0
// register.
//
//*****************************************************************************
#define EPI_READFIFO0_DATA_M    0xFFFFFFFF  // Reads Data
#define EPI_READFIFO0_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_READFIFO1
// register.
//
//*****************************************************************************
#define EPI_READFIFO1_DATA_M    0xFFFFFFFF  // Reads Data
#define EPI_READFIFO1_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_READFIFO2
// register.
//
//*****************************************************************************
#define EPI_READFIFO2_DATA_M    0xFFFFFFFF  // Reads Data
#define EPI_READFIFO2_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_READFIFO3
// register.
//
//*****************************************************************************
#define EPI_READFIFO3_DATA_M    0xFFFFFFFF  // Reads Data
#define EPI_READFIFO3_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_READFIFO4
// register.
//
//*****************************************************************************
#define EPI_READFIFO4_DATA_M    0xFFFFFFFF  // Reads Data
#define EPI_READFIFO4_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_READFIFO5
// register.
//
//*****************************************************************************
#define EPI_READFIFO5_DATA_M    0xFFFFFFFF  // Reads Data
#define EPI_READFIFO5_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_READFIFO6
// register.
//
//*****************************************************************************
#define EPI_READFIFO6_DATA_M    0xFFFFFFFF  // Reads Data
#define EPI_READFIFO6_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_READFIFO7
// register.
//
//*****************************************************************************
#define EPI_READFIFO7_DATA_M    0xFFFFFFFF  // Reads Data
#define EPI_READFIFO7_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_FIFOLVL register.
//
//*****************************************************************************
#define EPI_FIFOLVL_WFERR       0x00020000  // Write Full Error
#define EPI_FIFOLVL_RSERR       0x00010000  // Read Stall Error
#define EPI_FIFOLVL_WRFIFO_M    0x00000070  // Write FIFO
#define EPI_FIFOLVL_WRFIFO_EMPT 0x00000000  // Interrupt is triggered while
// WRFIFO is empty.
#define EPI_FIFOLVL_WRFIFO_2    0x00000020  // Interrupt is triggered until
// there are only two slots
// available. Thus, trigger is
// deasserted when there are two
// WRFIFO entries present. This
// configuration is optimized for
// bursts of 2
#define EPI_FIFOLVL_WRFIFO_1    0x00000030  // Interrupt is triggered until
// there is one WRFIFO entry
// available. This configuration
// expects only single writes
#define EPI_FIFOLVL_WRFIFO_NFULL                                              \
                                0x00000040  // Trigger interrupt when WRFIFO is
// not full, meaning trigger will
// continue to assert until there
// are four entries in the WRFIFO
#define EPI_FIFOLVL_RDFIFO_M    0x00000007  // Read FIFO
#define EPI_FIFOLVL_RDFIFO_1    0x00000001  // Trigger when there are 1 or more
// entries in the NBRFIFO
#define EPI_FIFOLVL_RDFIFO_2    0x00000002  // Trigger when there are 2 or more
// entries in the NBRFIFO
#define EPI_FIFOLVL_RDFIFO_4    0x00000003  // Trigger when there are 4 or more
// entries in the NBRFIFO
#define EPI_FIFOLVL_RDFIFO_6    0x00000004  // Trigger when there are 6 or more
// entries in the NBRFIFO
#define EPI_FIFOLVL_RDFIFO_7    0x00000005  // Trigger when there are 7 or more
// entries in the NBRFIFO
#define EPI_FIFOLVL_RDFIFO_8    0x00000006  // Trigger when there are 8 entries
// in the NBRFIFO

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_WFIFOCNT register.
//
//*****************************************************************************
#define EPI_WFIFOCNT_WTAV_M     0x00000007  // Available Write Transactions
#define EPI_WFIFOCNT_WTAV_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_DMATXCNT register.
//
//*****************************************************************************
#define EPI_DMATXCNT_TXCNT_M    0x0000FFFF  // DMA Count
#define EPI_DMATXCNT_TXCNT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_IM register.
//
//*****************************************************************************
#define EPI_IM_DMAWRIM          0x00000010  // Write uDMA Interrupt Mask
#define EPI_IM_DMARDIM          0x00000008  // Read uDMA Interrupt Mask
#define EPI_IM_WRIM             0x00000004  // Write FIFO Empty Interrupt Mask
#define EPI_IM_RDIM             0x00000002  // Read FIFO Full Interrupt Mask
#define EPI_IM_ERRIM            0x00000001  // Error Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_RIS register.
//
//*****************************************************************************
#define EPI_RIS_DMAWRRIS        0x00000010  // Write uDMA Raw Interrupt Status
#define EPI_RIS_DMARDRIS        0x00000008  // Read uDMA Raw Interrupt Status
#define EPI_RIS_WRRIS           0x00000004  // Write Raw Interrupt Status
#define EPI_RIS_RDRIS           0x00000002  // Read Raw Interrupt Status
#define EPI_RIS_ERRRIS          0x00000001  // Error Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_MIS register.
//
//*****************************************************************************
#define EPI_MIS_DMAWRMIS        0x00000010  // Write uDMA Masked Interrupt
// Status
#define EPI_MIS_DMARDMIS        0x00000008  // Read uDMA Masked Interrupt
// Status
#define EPI_MIS_WRMIS           0x00000004  // Write Masked Interrupt Status
#define EPI_MIS_RDMIS           0x00000002  // Read Masked Interrupt Status
#define EPI_MIS_ERRMIS          0x00000001  // Error Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_EISC register.
//
//*****************************************************************************
#define EPI_EISC_DMAWRIC        0x00000010  // Write uDMA Interrupt Clear
#define EPI_EISC_DMARDIC        0x00000008  // Read uDMA Interrupt Clear
#define EPI_EISC_WTFULL         0x00000004  // Write FIFO Full Error
#define EPI_EISC_RSTALL         0x00000002  // Read Stalled Error
#define EPI_EISC_TOUT           0x00000001  // Timeout Error

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB8CFG3 register.
//
//*****************************************************************************
#define EPI_HB8CFG3_WRHIGH      0x00200000  // CS2n WRITE Strobe Polarity
#define EPI_HB8CFG3_RDHIGH      0x00100000  // CS2n READ Strobe Polarity
#define EPI_HB8CFG3_ALEHIGH     0x00080000  // CS2n ALE Strobe Polarity
#define EPI_HB8CFG3_WRWS_M      0x000000C0  // CS2n Write Wait States
#define EPI_HB8CFG3_WRWS_2      0x00000000  // Active WRn is 2 EPI clocks
#define EPI_HB8CFG3_WRWS_4      0x00000040  // Active WRn is 4 EPI clocks
#define EPI_HB8CFG3_WRWS_6      0x00000080  // Active WRn is 6 EPI clocks
#define EPI_HB8CFG3_WRWS_8      0x000000C0  // Active WRn is 8 EPI clocks
#define EPI_HB8CFG3_RDWS_M      0x00000030  // CS2n Read Wait States
#define EPI_HB8CFG3_RDWS_2      0x00000000  // Active RDn is 2 EPI clocks
#define EPI_HB8CFG3_RDWS_4      0x00000010  // Active RDn is 4 EPI clocks
#define EPI_HB8CFG3_RDWS_6      0x00000020  // Active RDn is 6 EPI clocks
#define EPI_HB8CFG3_RDWS_8      0x00000030  // Active RDn is 8 EPI clocks
#define EPI_HB8CFG3_MODE_M      0x00000003  // CS2n Host Bus Sub-Mode
#define EPI_HB8CFG3_MODE_ADMUX  0x00000000  // ADMUX - AD[7:0]
#define EPI_HB8CFG3_MODE_AD     0x00000001  // ADNONMUX - D[7:0]

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB16CFG3 register.
//
//*****************************************************************************
#define EPI_HB16CFG3_WRHIGH     0x00200000  // CS2n WRITE Strobe Polarity
#define EPI_HB16CFG3_RDHIGH     0x00100000  // CS2n READ Strobe Polarity
#define EPI_HB16CFG3_ALEHIGH    0x00080000  // CS2n ALE Strobe Polarity
#define EPI_HB16CFG3_WRCRE      0x00040000  // CS2n PSRAM Configuration
// Register Write
#define EPI_HB16CFG3_RDCRE      0x00020000  // CS2n PSRAM Configuration
// Register Read
#define EPI_HB16CFG3_BURST      0x00010000  // CS2n Burst Mode
#define EPI_HB16CFG3_WRWS_M     0x000000C0  // CS2n Write Wait States
#define EPI_HB16CFG3_WRWS_2     0x00000000  // Active WRn is 2 EPI clocks
#define EPI_HB16CFG3_WRWS_4     0x00000040  // Active WRn is 4 EPI clocks
#define EPI_HB16CFG3_WRWS_6     0x00000080  // Active WRn is 6 EPI clocks
#define EPI_HB16CFG3_WRWS_8     0x000000C0  // Active WRn is 8 EPI clocks
#define EPI_HB16CFG3_RDWS_M     0x00000030  // CS2n Read Wait States
#define EPI_HB16CFG3_RDWS_2     0x00000000  // Active RDn is 2 EPI clocks
#define EPI_HB16CFG3_RDWS_4     0x00000010  // Active RDn is 4 EPI clocks
#define EPI_HB16CFG3_RDWS_6     0x00000020  // Active RDn is 6 EPI clocks
#define EPI_HB16CFG3_RDWS_8     0x00000030  // Active RDn is 8 EPI clocks
#define EPI_HB16CFG3_MODE_M     0x00000003  // CS2n Host Bus Sub-Mode
#define EPI_HB16CFG3_MODE_ADMUX 0x00000000  // ADMUX - AD[15:0]
#define EPI_HB16CFG3_MODE_AD    0x00000001  // ADNONMUX - D[15:0]

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB16CFG4 register.
//
//*****************************************************************************
#define EPI_HB16CFG4_WRHIGH     0x00200000  // CS3n WRITE Strobe Polarity
#define EPI_HB16CFG4_RDHIGH     0x00100000  // CS3n READ Strobe Polarity
#define EPI_HB16CFG4_ALEHIGH    0x00080000  // CS3n ALE Strobe Polarity
#define EPI_HB16CFG4_WRCRE      0x00040000  // CS3n PSRAM Configuration
// Register Write
#define EPI_HB16CFG4_RDCRE      0x00020000  // CS3n PSRAM Configuration
// Register Read
#define EPI_HB16CFG4_BURST      0x00010000  // CS3n Burst Mode
#define EPI_HB16CFG4_WRWS_M     0x000000C0  // CS3n Write Wait States
#define EPI_HB16CFG4_WRWS_2     0x00000000  // Active WRn is 2 EPI clocks
#define EPI_HB16CFG4_WRWS_4     0x00000040  // Active WRn is 4 EPI clocks
#define EPI_HB16CFG4_WRWS_6     0x00000080  // Active WRn is 6 EPI clocks
#define EPI_HB16CFG4_WRWS_8     0x000000C0  // Active WRn is 8 EPI clocks
#define EPI_HB16CFG4_RDWS_M     0x00000030  // CS3n Read Wait States
#define EPI_HB16CFG4_RDWS_2     0x00000000  // Active RDn is 2 EPI clocks
#define EPI_HB16CFG4_RDWS_4     0x00000010  // Active RDn is 4 EPI clocks
#define EPI_HB16CFG4_RDWS_6     0x00000020  // Active RDn is 6 EPI clocks
#define EPI_HB16CFG4_RDWS_8     0x00000030  // Active RDn is 8 EPI clocks
#define EPI_HB16CFG4_MODE_M     0x00000003  // CS3n Host Bus Sub-Mode
#define EPI_HB16CFG4_MODE_ADMUX 0x00000000  // ADMUX - AD[15:0]
#define EPI_HB16CFG4_MODE_AD    0x00000001  // ADNONMUX - D[15:0]

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB8CFG4 register.
//
//*****************************************************************************
#define EPI_HB8CFG4_WRHIGH      0x00200000  // CS3n WRITE Strobe Polarity
#define EPI_HB8CFG4_RDHIGH      0x00100000  // CS2n READ Strobe Polarity
#define EPI_HB8CFG4_ALEHIGH     0x00080000  // CS3n ALE Strobe Polarity
#define EPI_HB8CFG4_WRWS_M      0x000000C0  // CS3n Write Wait States
#define EPI_HB8CFG4_WRWS_2      0x00000000  // Active WRn is 2 EPI clocks
#define EPI_HB8CFG4_WRWS_4      0x00000040  // Active WRn is 4 EPI clocks
#define EPI_HB8CFG4_WRWS_6      0x00000080  // Active WRn is 6 EPI clocks
#define EPI_HB8CFG4_WRWS_8      0x000000C0  // Active WRn is 8 EPI clocks
#define EPI_HB8CFG4_RDWS_M      0x00000030  // CS3n Read Wait States
#define EPI_HB8CFG4_RDWS_2      0x00000000  // Active RDn is 2 EPI clocks
#define EPI_HB8CFG4_RDWS_4      0x00000010  // Active RDn is 4 EPI clocks
#define EPI_HB8CFG4_RDWS_6      0x00000020  // Active RDn is 6 EPI clocks
#define EPI_HB8CFG4_RDWS_8      0x00000030  // Active RDn is 8 EPI clocks
#define EPI_HB8CFG4_MODE_M      0x00000003  // CS3n Host Bus Sub-Mode
#define EPI_HB8CFG4_MODE_ADMUX  0x00000000  // ADMUX - AD[7:0]
#define EPI_HB8CFG4_MODE_AD     0x00000001  // ADNONMUX - D[7:0]

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB8TIME register.
//
//*****************************************************************************
#define EPI_HB8TIME_IRDYDLY_M   0x03000000  // CS0n Input Ready Delay
#define EPI_HB8TIME_CAPWIDTH_M  0x00003000  // CS0n Inter-transfer Capture
// Width
#define EPI_HB8TIME_WRWSM       0x00000010  // Write Wait State Minus One
#define EPI_HB8TIME_RDWSM       0x00000001  // Read Wait State Minus One
#define EPI_HB8TIME_IRDYDLY_S   24
#define EPI_HB8TIME_CAPWIDTH_S  12

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB16TIME register.
//
//*****************************************************************************
#define EPI_HB16TIME_IRDYDLY_M  0x03000000  // CS0n Input Ready Delay
#define EPI_HB16TIME_PSRAMSZ_M  0x00070000  // PSRAM Row Size
#define EPI_HB16TIME_PSRAMSZ_0  0x00000000  // No row size limitation
#define EPI_HB16TIME_PSRAMSZ_128B                                             \
                                0x00010000  // 128 B
#define EPI_HB16TIME_PSRAMSZ_256B                                             \
                                0x00020000  // 256 B
#define EPI_HB16TIME_PSRAMSZ_512B                                             \
                                0x00030000  // 512 B
#define EPI_HB16TIME_PSRAMSZ_1KB                                              \
                                0x00040000  // 1024 B
#define EPI_HB16TIME_PSRAMSZ_2KB                                              \
                                0x00050000  // 2048 B
#define EPI_HB16TIME_PSRAMSZ_4KB                                              \
                                0x00060000  // 4096 B
#define EPI_HB16TIME_PSRAMSZ_8KB                                              \
                                0x00070000  // 8192 B
#define EPI_HB16TIME_CAPWIDTH_M 0x00003000  // CS0n Inter-transfer Capture
// Width
#define EPI_HB16TIME_WRWSM      0x00000010  // Write Wait State Minus One
#define EPI_HB16TIME_RDWSM      0x00000001  // Read Wait State Minus One
#define EPI_HB16TIME_IRDYDLY_S  24
#define EPI_HB16TIME_CAPWIDTH_S 12

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB8TIME2 register.
//
//*****************************************************************************
#define EPI_HB8TIME2_IRDYDLY_M  0x03000000  // CS1n Input Ready Delay
#define EPI_HB8TIME2_CAPWIDTH_M 0x00003000  // CS1n Inter-transfer Capture
// Width
#define EPI_HB8TIME2_WRWSM      0x00000010  // CS1n Write Wait State Minus One
#define EPI_HB8TIME2_RDWSM      0x00000001  // CS1n Read Wait State Minus One
#define EPI_HB8TIME2_IRDYDLY_S  24
#define EPI_HB8TIME2_CAPWIDTH_S 12

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB16TIME2
// register.
//
//*****************************************************************************
#define EPI_HB16TIME2_IRDYDLY_M 0x03000000  // CS1n Input Ready Delay
#define EPI_HB16TIME2_PSRAMSZ_M 0x00070000  // PSRAM Row Size
#define EPI_HB16TIME2_PSRAMSZ_0 0x00000000  // No row size limitation
#define EPI_HB16TIME2_PSRAMSZ_128B                                            \
                                0x00010000  // 128 B
#define EPI_HB16TIME2_PSRAMSZ_256B                                            \
                                0x00020000  // 256 B
#define EPI_HB16TIME2_PSRAMSZ_512B                                            \
                                0x00030000  // 512 B
#define EPI_HB16TIME2_PSRAMSZ_1KB                                             \
                                0x00040000  // 1024 B
#define EPI_HB16TIME2_PSRAMSZ_2KB                                             \
                                0x00050000  // 2048 B
#define EPI_HB16TIME2_PSRAMSZ_4KB                                             \
                                0x00060000  // 4096 B
#define EPI_HB16TIME2_PSRAMSZ_8KB                                             \
                                0x00070000  // 8192 B
#define EPI_HB16TIME2_CAPWIDTH_M                                              \
                                0x00003000  // CS1n Inter-transfer Capture
// Width
#define EPI_HB16TIME2_WRWSM     0x00000010  // CS1n Write Wait State Minus One
#define EPI_HB16TIME2_RDWSM     0x00000001  // CS1n Read Wait State Minus One
#define EPI_HB16TIME2_IRDYDLY_S 24
#define EPI_HB16TIME2_CAPWIDTH_S                                              \
                                12

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB16TIME3
// register.
//
//*****************************************************************************
#define EPI_HB16TIME3_IRDYDLY_M 0x03000000  // CS2n Input Ready Delay
#define EPI_HB16TIME3_PSRAMSZ_M 0x00070000  // PSRAM Row Size
#define EPI_HB16TIME3_PSRAMSZ_0 0x00000000  // No row size limitation
#define EPI_HB16TIME3_PSRAMSZ_128B                                            \
                                0x00010000  // 128 B
#define EPI_HB16TIME3_PSRAMSZ_256B                                            \
                                0x00020000  // 256 B
#define EPI_HB16TIME3_PSRAMSZ_512B                                            \
                                0x00030000  // 512 B
#define EPI_HB16TIME3_PSRAMSZ_1KB                                             \
                                0x00040000  // 1024 B
#define EPI_HB16TIME3_PSRAMSZ_2KB                                             \
                                0x00050000  // 2048 B
#define EPI_HB16TIME3_PSRAMSZ_4KB                                             \
                                0x00060000  // 4096 B
#define EPI_HB16TIME3_PSRAMSZ_8KB                                             \
                                0x00070000  // 8192 B
#define EPI_HB16TIME3_CAPWIDTH_M                                              \
                                0x00003000  // CS2n Inter-transfer Capture
// Width
#define EPI_HB16TIME3_WRWSM     0x00000010  // CS2n Write Wait State Minus One
#define EPI_HB16TIME3_RDWSM     0x00000001  // CS2n Read Wait State Minus One
#define EPI_HB16TIME3_IRDYDLY_S 24
#define EPI_HB16TIME3_CAPWIDTH_S                                              \
                                12

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB8TIME3 register.
//
//*****************************************************************************
#define EPI_HB8TIME3_IRDYDLY_M  0x03000000  // CS2n Input Ready Delay
#define EPI_HB8TIME3_CAPWIDTH_M 0x00003000  // CS2n Inter-transfer Capture
// Width
#define EPI_HB8TIME3_WRWSM      0x00000010  // CS2n Write Wait State Minus One
#define EPI_HB8TIME3_RDWSM      0x00000001  // CS2n Read Wait State Minus One
#define EPI_HB8TIME3_IRDYDLY_S  24
#define EPI_HB8TIME3_CAPWIDTH_S 12

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB8TIME4 register.
//
//*****************************************************************************
#define EPI_HB8TIME4_IRDYDLY_M  0x03000000  // CS3n Input Ready Delay
#define EPI_HB8TIME4_CAPWIDTH_M 0x00003000  // CS3n Inter-transfer Capture
// Width
#define EPI_HB8TIME4_WRWSM      0x00000010  // CS3n Write Wait State Minus One
#define EPI_HB8TIME4_RDWSM      0x00000001  // CS3n Read Wait State Minus One
#define EPI_HB8TIME4_IRDYDLY_S  24
#define EPI_HB8TIME4_CAPWIDTH_S 12

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HB16TIME4
// register.
//
//*****************************************************************************
#define EPI_HB16TIME4_IRDYDLY_M 0x03000000  // CS3n Input Ready Delay
#define EPI_HB16TIME4_PSRAMSZ_M 0x00070000  // PSRAM Row Size
#define EPI_HB16TIME4_PSRAMSZ_0 0x00000000  // No row size limitation
#define EPI_HB16TIME4_PSRAMSZ_128B                                            \
                                0x00010000  // 128 B
#define EPI_HB16TIME4_PSRAMSZ_256B                                            \
                                0x00020000  // 256 B
#define EPI_HB16TIME4_PSRAMSZ_512B                                            \
                                0x00030000  // 512 B
#define EPI_HB16TIME4_PSRAMSZ_1KB                                             \
                                0x00040000  // 1024 B
#define EPI_HB16TIME4_PSRAMSZ_2KB                                             \
                                0x00050000  // 2048 B
#define EPI_HB16TIME4_PSRAMSZ_4KB                                             \
                                0x00060000  // 4096 B
#define EPI_HB16TIME4_PSRAMSZ_8KB                                             \
                                0x00070000  // 8192 B
#define EPI_HB16TIME4_CAPWIDTH_M                                              \
                                0x00003000  // CS3n Inter-transfer Capture
// Width
#define EPI_HB16TIME4_WRWSM     0x00000010  // CS3n Write Wait State Minus One
#define EPI_HB16TIME4_RDWSM     0x00000001  // CS3n Read Wait State Minus One
#define EPI_HB16TIME4_IRDYDLY_S 24
#define EPI_HB16TIME4_CAPWIDTH_S                                              \
                                12

//*****************************************************************************
//
// The following are defines for the bit fields in the EPI_O_HBPSRAM register.
//
//*****************************************************************************
#define EPI_HBPSRAM_CR_M        0x001FFFFF  // PSRAM Config Register
#define EPI_HBPSRAM_CR_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSEXC_RIS register.
//
//*****************************************************************************
#define SYSEXC_RIS_FPIXCRIS     0x00000020  // Floating-Point Inexact Exception
// Raw Interrupt Status
#define SYSEXC_RIS_FPOFCRIS     0x00000010  // Floating-Point Overflow
// Exception Raw Interrupt Status
#define SYSEXC_RIS_FPUFCRIS     0x00000008  // Floating-Point Underflow
// Exception Raw Interrupt Status
#define SYSEXC_RIS_FPIOCRIS     0x00000004  // Floating-Point Invalid Operation
// Raw Interrupt Status
#define SYSEXC_RIS_FPDZCRIS     0x00000002  // Floating-Point Divide By 0
// Exception Raw Interrupt Status
#define SYSEXC_RIS_FPIDCRIS     0x00000001  // Floating-Point Input Denormal
// Exception Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSEXC_IM register.
//
//*****************************************************************************
#define SYSEXC_IM_FPIXCIM       0x00000020  // Floating-Point Inexact Exception
// Interrupt Mask
#define SYSEXC_IM_FPOFCIM       0x00000010  // Floating-Point Overflow
// Exception Interrupt Mask
#define SYSEXC_IM_FPUFCIM       0x00000008  // Floating-Point Underflow
// Exception Interrupt Mask
#define SYSEXC_IM_FPIOCIM       0x00000004  // Floating-Point Invalid Operation
// Interrupt Mask
#define SYSEXC_IM_FPDZCIM       0x00000002  // Floating-Point Divide By 0
// Exception Interrupt Mask
#define SYSEXC_IM_FPIDCIM       0x00000001  // Floating-Point Input Denormal
// Exception Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSEXC_MIS register.
//
//*****************************************************************************
#define SYSEXC_MIS_FPIXCMIS     0x00000020  // Floating-Point Inexact Exception
// Masked Interrupt Status
#define SYSEXC_MIS_FPOFCMIS     0x00000010  // Floating-Point Overflow
// Exception Masked Interrupt
// Status
#define SYSEXC_MIS_FPUFCMIS     0x00000008  // Floating-Point Underflow
// Exception Masked Interrupt
// Status
#define SYSEXC_MIS_FPIOCMIS     0x00000004  // Floating-Point Invalid Operation
// Masked Interrupt Status
#define SYSEXC_MIS_FPDZCMIS     0x00000002  // Floating-Point Divide By 0
// Exception Masked Interrupt
// Status
#define SYSEXC_MIS_FPIDCMIS     0x00000001  // Floating-Point Input Denormal
// Exception Masked Interrupt
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSEXC_IC register.
//
//*****************************************************************************
#define SYSEXC_IC_FPIXCIC       0x00000020  // Floating-Point Inexact Exception
// Interrupt Clear
#define SYSEXC_IC_FPOFCIC       0x00000010  // Floating-Point Overflow
// Exception Interrupt Clear
#define SYSEXC_IC_FPUFCIC       0x00000008  // Floating-Point Underflow
// Exception Interrupt Clear
#define SYSEXC_IC_FPIOCIC       0x00000004  // Floating-Point Invalid Operation
// Interrupt Clear
#define SYSEXC_IC_FPDZCIC       0x00000002  // Floating-Point Divide By 0
// Exception Interrupt Clear
#define SYSEXC_IC_FPIDCIC       0x00000001  // Floating-Point Input Denormal
// Exception Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCC register.
//
//*****************************************************************************
#define HIB_RTCC_M              0xFFFFFFFF  // RTC Counter
#define HIB_RTCC_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCM0 register.
//
//*****************************************************************************
#define HIB_RTCM0_M             0xFFFFFFFF  // RTC Match 0
#define HIB_RTCM0_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCLD register.
//
//*****************************************************************************
#define HIB_RTCLD_M             0xFFFFFFFF  // RTC Load
#define HIB_RTCLD_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CTL register.
//
//*****************************************************************************
#define HIB_CTL_WRC             0x80000000  // Write Complete/Capable
#define HIB_CTL_RETCLR          0x40000000  // GPIO Retention/Clear
#define HIB_CTL_OSCSEL          0x00080000  // Oscillator Select
#define HIB_CTL_OSCDRV          0x00020000  // Oscillator Drive Capability
#define HIB_CTL_OSCBYP          0x00010000  // Oscillator Bypass
#define HIB_CTL_VBATSEL_M       0x00006000  // Select for Low-Battery
// Comparator
#define HIB_CTL_VBATSEL_1_9V    0x00000000  // 1.9 Volts
#define HIB_CTL_VBATSEL_2_1V    0x00002000  // 2.1 Volts (default)
#define HIB_CTL_VBATSEL_2_3V    0x00004000  // 2.3 Volts
#define HIB_CTL_VBATSEL_2_5V    0x00006000  // 2.5 Volts
#define HIB_CTL_BATCHK          0x00000400  // Check Battery Status
#define HIB_CTL_BATWKEN         0x00000200  // Wake on Low Battery
#define HIB_CTL_VDD3ON          0x00000100  // VDD Powered
#define HIB_CTL_VABORT          0x00000080  // Power Cut Abort Enable
#define HIB_CTL_CLK32EN         0x00000040  // Clocking Enable
#define HIB_CTL_PINWEN          0x00000010  // External Wake Pin Enable
#define HIB_CTL_RTCWEN          0x00000008  // RTC Wake-up Enable
#define HIB_CTL_HIBREQ          0x00000002  // Hibernation Request
#define HIB_CTL_RTCEN           0x00000001  // RTC Timer Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_IM register.
//
//*****************************************************************************
#define HIB_IM_VDDFAIL          0x00000080  // VDD Fail Interrupt Mask
#define HIB_IM_RSTWK            0x00000040  // Reset Pad I/O Wake-Up Interrupt
// Mask
#define HIB_IM_PADIOWK          0x00000020  // Pad I/O Wake-Up Interrupt Mask
#define HIB_IM_WC               0x00000010  // External Write Complete/Capable
// Interrupt Mask
#define HIB_IM_EXTW             0x00000008  // External Wake-Up Interrupt Mask
#define HIB_IM_LOWBAT           0x00000004  // Low Battery Voltage Interrupt
// Mask
#define HIB_IM_RTCALT0          0x00000001  // RTC Alert 0 Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RIS register.
//
//*****************************************************************************
#define HIB_RIS_VDDFAIL         0x00000080  // VDD Fail Raw Interrupt Status
#define HIB_RIS_RSTWK           0x00000040  // Reset Pad I/O Wake-Up Raw
// Interrupt Status
#define HIB_RIS_PADIOWK         0x00000020  // Pad I/O Wake-Up Raw Interrupt
// Status
#define HIB_RIS_WC              0x00000010  // Write Complete/Capable Raw
// Interrupt Status
#define HIB_RIS_EXTW            0x00000008  // External Wake-Up Raw Interrupt
// Status
#define HIB_RIS_LOWBAT          0x00000004  // Low Battery Voltage Raw
// Interrupt Status
#define HIB_RIS_RTCALT0         0x00000001  // RTC Alert 0 Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_MIS register.
//
//*****************************************************************************
#define HIB_MIS_VDDFAIL         0x00000080  // VDD Fail Interrupt Mask
#define HIB_MIS_RSTWK           0x00000040  // Reset Pad I/O Wake-Up Interrupt
// Mask
#define HIB_MIS_PADIOWK         0x00000020  // Pad I/O Wake-Up Interrupt Mask
#define HIB_MIS_WC              0x00000010  // Write Complete/Capable Masked
// Interrupt Status
#define HIB_MIS_EXTW            0x00000008  // External Wake-Up Masked
// Interrupt Status
#define HIB_MIS_LOWBAT          0x00000004  // Low Battery Voltage Masked
// Interrupt Status
#define HIB_MIS_RTCALT0         0x00000001  // RTC Alert 0 Masked Interrupt
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_IC register.
//
//*****************************************************************************
#define HIB_IC_VDDFAIL          0x00000080  // VDD Fail Interrupt Clear
#define HIB_IC_RSTWK            0x00000040  // Reset Pad I/O Wake-Up Interrupt
// Clear
#define HIB_IC_PADIOWK          0x00000020  // Pad I/O Wake-Up Interrupt Clear
#define HIB_IC_WC               0x00000010  // Write Complete/Capable Interrupt
// Clear
#define HIB_IC_EXTW             0x00000008  // External Wake-Up Interrupt Clear
#define HIB_IC_LOWBAT           0x00000004  // Low Battery Voltage Interrupt
// Clear
#define HIB_IC_RTCALT0          0x00000001  // RTC Alert0 Masked Interrupt
// Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCT register.
//
//*****************************************************************************
#define HIB_RTCT_TRIM_M         0x0000FFFF  // RTC Trim Value
#define HIB_RTCT_TRIM_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCSS register.
//
//*****************************************************************************
#define HIB_RTCSS_RTCSSM_M      0x7FFF0000  // RTC Sub Seconds Match
#define HIB_RTCSS_RTCSSC_M      0x00007FFF  // RTC Sub Seconds Count
#define HIB_RTCSS_RTCSSM_S      16
#define HIB_RTCSS_RTCSSC_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_IO register.
//
//*****************************************************************************
#define HIB_IO_IOWRC            0x80000000  // I/O Write Complete
#define HIB_IO_WURSTEN          0x00000010  // Reset Wake Source Enable
#define HIB_IO_WUUNLK           0x00000001  // I/O Wake Pad Configuration
// Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_DATA register.
//
//*****************************************************************************
#define HIB_DATA_RTD_M          0xFFFFFFFF  // Hibernation Module NV Data
#define HIB_DATA_RTD_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CALCTL register.
//
//*****************************************************************************
#define HIB_CALCTL_CAL24        0x00000004  // Calendar Mode
#define HIB_CALCTL_CALEN        0x00000001  // RTC Calendar/Counter Mode Select

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CAL0 register.
//
//*****************************************************************************
#define HIB_CAL0_VALID          0x80000000  // Valid Calendar Load
#define HIB_CAL0_AMPM           0x00400000  // AM/PM Designation
#define HIB_CAL0_HR_M           0x001F0000  // Hours
#define HIB_CAL0_MIN_M          0x00003F00  // Minutes
#define HIB_CAL0_SEC_M          0x0000003F  // Seconds
#define HIB_CAL0_HR_S           16
#define HIB_CAL0_MIN_S          8
#define HIB_CAL0_SEC_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CAL1 register.
//
//*****************************************************************************
#define HIB_CAL1_VALID          0x80000000  // Valid Calendar Load
#define HIB_CAL1_DOW_M          0x07000000  // Day of Week
#define HIB_CAL1_YEAR_M         0x007F0000  // Year Value
#define HIB_CAL1_MON_M          0x00000F00  // Month
#define HIB_CAL1_DOM_M          0x0000001F  // Day of Month
#define HIB_CAL1_DOW_S          24
#define HIB_CAL1_YEAR_S         16
#define HIB_CAL1_MON_S          8
#define HIB_CAL1_DOM_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CALLD0 register.
//
//*****************************************************************************
#define HIB_CALLD0_AMPM         0x00400000  // AM/PM Designation
#define HIB_CALLD0_HR_M         0x001F0000  // Hours
#define HIB_CALLD0_MIN_M        0x00003F00  // Minutes
#define HIB_CALLD0_SEC_M        0x0000003F  // Seconds
#define HIB_CALLD0_HR_S         16
#define HIB_CALLD0_MIN_S        8
#define HIB_CALLD0_SEC_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CALLD1 register.
//
//*****************************************************************************
#define HIB_CALLD1_DOW_M        0x07000000  // Day of Week
#define HIB_CALLD1_YEAR_M       0x007F0000  // Year Value
#define HIB_CALLD1_MON_M        0x00000F00  // Month
#define HIB_CALLD1_DOM_M        0x0000001F  // Day of Month
#define HIB_CALLD1_DOW_S        24
#define HIB_CALLD1_YEAR_S       16
#define HIB_CALLD1_MON_S        8
#define HIB_CALLD1_DOM_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CALM0 register.
//
//*****************************************************************************
#define HIB_CALM0_AMPM          0x00400000  // AM/PM Designation
#define HIB_CALM0_HR_M          0x001F0000  // Hours
#define HIB_CALM0_MIN_M         0x00003F00  // Minutes
#define HIB_CALM0_SEC_M         0x0000003F  // Seconds
#define HIB_CALM0_HR_S          16
#define HIB_CALM0_MIN_S         8
#define HIB_CALM0_SEC_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CALM1 register.
//
//*****************************************************************************
#define HIB_CALM1_DOM_M         0x0000001F  // Day of Month
#define HIB_CALM1_DOM_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_LOCK register.
//
//*****************************************************************************
#define HIB_LOCK_HIBLOCK_M      0xFFFFFFFF  // HIbernate Lock
#define HIB_LOCK_HIBLOCK_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPCTL register.
//
//*****************************************************************************
#define HIB_TPCTL_WAKE          0x00000800  // Wake from Hibernate on a Tamper
// Event
#define HIB_TPCTL_MEMCLR_M      0x00000300  // HIB Memory Clear on Tamper Event
#define HIB_TPCTL_MEMCLR_NONE   0x00000000  // Do not Clear HIB memory on
// tamper event
#define HIB_TPCTL_MEMCLR_LOW32  0x00000100  // Clear Lower 32 Bytes of HIB
// memory on tamper event
#define HIB_TPCTL_MEMCLR_HIGH32 0x00000200  // Clear upper 32 Bytes of HIB
// memory on tamper event
#define HIB_TPCTL_MEMCLR_ALL    0x00000300  // Clear all HIB memory on tamper
// event
#define HIB_TPCTL_TPCLR         0x00000010  // Tamper Event Clear
#define HIB_TPCTL_TPEN          0x00000001  // Tamper Module Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPSTAT register.
//
//*****************************************************************************
#define HIB_TPSTAT_STATE_M      0x0000000C  // Tamper Module Status
#define HIB_TPSTAT_STATE_DISABLED                                             \
                                0x00000000  // Tamper disabled
#define HIB_TPSTAT_STATE_CONFIGED                                             \
                                0x00000004  // Tamper configured
#define HIB_TPSTAT_STATE_ERROR  0x00000008  // Tamper pin event occurred
#define HIB_TPSTAT_XOSCST       0x00000002  // External Oscillator Status
#define HIB_TPSTAT_XOSCFAIL     0x00000001  // External Oscillator Failure

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPIO register.
//
//*****************************************************************************
#define HIB_TPIO_GFLTR3         0x08000000  // TMPR3 Glitch Filtering
#define HIB_TPIO_PUEN3          0x04000000  // TMPR3 Internal Weak Pull-up
// Enable
#define HIB_TPIO_LEV3           0x02000000  // TMPR3 Trigger Level
#define HIB_TPIO_EN3            0x01000000  // TMPR3 Enable
#define HIB_TPIO_GFLTR2         0x00080000  // TMPR2 Glitch Filtering
#define HIB_TPIO_PUEN2          0x00040000  // TMPR2 Internal Weak Pull-up
// Enable
#define HIB_TPIO_LEV2           0x00020000  // TMPR2 Trigger Level
#define HIB_TPIO_EN2            0x00010000  // TMPR2 Enable
#define HIB_TPIO_GFLTR1         0x00000800  // TMPR1 Glitch Filtering
#define HIB_TPIO_PUEN1          0x00000400  // TMPR1 Internal Weak Pull-up
// Enable
#define HIB_TPIO_LEV1           0x00000200  // TMPR1 Trigger Level
#define HIB_TPIO_EN1            0x00000100  // TMPR1Enable
#define HIB_TPIO_GFLTR0         0x00000008  // TMPR0 Glitch Filtering
#define HIB_TPIO_PUEN0          0x00000004  // TMPR0 Internal Weak Pull-up
// Enable
#define HIB_TPIO_LEV0           0x00000002  // TMPR0 Trigger Level
#define HIB_TPIO_EN0            0x00000001  // TMPR0 Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPLOG0 register.
//
//*****************************************************************************
#define HIB_TPLOG0_TIME_M       0xFFFFFFFF  // Tamper Log Calendar Information
#define HIB_TPLOG0_TIME_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPLOG1 register.
//
//*****************************************************************************
#define HIB_TPLOG1_XOSC         0x00010000  // Status of external 32
#define HIB_TPLOG1_TRIG3        0x00000008  // Status of TMPR[3] Trigger
#define HIB_TPLOG1_TRIG2        0x00000004  // Status of TMPR[2] Trigger
#define HIB_TPLOG1_TRIG1        0x00000002  // Status of TMPR[1] Trigger
#define HIB_TPLOG1_TRIG0        0x00000001  // Status of TMPR[0] Trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPLOG2 register.
//
//*****************************************************************************
#define HIB_TPLOG2_TIME_M       0xFFFFFFFF  // Tamper Log Calendar Information
#define HIB_TPLOG2_TIME_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPLOG3 register.
//
//*****************************************************************************
#define HIB_TPLOG3_XOSC         0x00010000  // Status of external 32
#define HIB_TPLOG3_TRIG3        0x00000008  // Status of TMPR[3] Trigger
#define HIB_TPLOG3_TRIG2        0x00000004  // Status of TMPR[2] Trigger
#define HIB_TPLOG3_TRIG1        0x00000002  // Status of TMPR[1] Trigger
#define HIB_TPLOG3_TRIG0        0x00000001  // Status of TMPR[0] Trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPLOG4 register.
//
//*****************************************************************************
#define HIB_TPLOG4_TIME_M       0xFFFFFFFF  // Tamper Log Calendar Information
#define HIB_TPLOG4_TIME_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPLOG5 register.
//
//*****************************************************************************
#define HIB_TPLOG5_XOSC         0x00010000  // Status of external 32
#define HIB_TPLOG5_TRIG3        0x00000008  // Status of TMPR[3] Trigger
#define HIB_TPLOG5_TRIG2        0x00000004  // Status of TMPR[2] Trigger
#define HIB_TPLOG5_TRIG1        0x00000002  // Status of TMPR[1] Trigger
#define HIB_TPLOG5_TRIG0        0x00000001  // Status of TMPR[0] Trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPLOG6 register.
//
//*****************************************************************************
#define HIB_TPLOG6_TIME_M       0xFFFFFFFF  // Tamper Log Calendar Information
#define HIB_TPLOG6_TIME_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_TPLOG7 register.
//
//*****************************************************************************
#define HIB_TPLOG7_XOSC         0x00010000  // Status of external 32
#define HIB_TPLOG7_TRIG3        0x00000008  // Status of TMPR[3] Trigger
#define HIB_TPLOG7_TRIG2        0x00000004  // Status of TMPR[2] Trigger
#define HIB_TPLOG7_TRIG1        0x00000002  // Status of TMPR[1] Trigger
#define HIB_TPLOG7_TRIG0        0x00000001  // Status of TMPR[0] Trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_PP register.
//
//*****************************************************************************
#define HIB_PP_TAMPER           0x00000002  // Tamper Pin Presence
#define HIB_PP_WAKENC           0x00000001  // Wake Pin Presence

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CC register.
//
//*****************************************************************************
#define HIB_CC_SYSCLKEN         0x00000001  // RTCOSC to System Clock Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMA register.
//
//*****************************************************************************
#define FLASH_FMA_OFFSET_M      0x000FFFFF  // Address Offset
#define FLASH_FMA_OFFSET_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMD register.
//
//*****************************************************************************
#define FLASH_FMD_DATA_M        0xFFFFFFFF  // Data Value
#define FLASH_FMD_DATA_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMC register.
//
//*****************************************************************************
#define FLASH_FMC_WRKEY         0xA4420000  // FLASH write key
#define FLASH_FMC_COMT          0x00000008  // Commit Register Value
#define FLASH_FMC_MERASE        0x00000004  // Mass Erase Flash Memory
#define FLASH_FMC_ERASE         0x00000002  // Erase a Page of Flash Memory
#define FLASH_FMC_WRITE         0x00000001  // Write a Word into Flash Memory

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FCRIS register.
//
//*****************************************************************************
#define FLASH_FCRIS_PROGRIS     0x00002000  // Program Verify Error Raw
// Interrupt Status
#define FLASH_FCRIS_ERRIS       0x00000800  // Erase Verify Error Raw Interrupt
// Status
#define FLASH_FCRIS_INVDRIS     0x00000400  // Invalid Data Raw Interrupt
// Status
#define FLASH_FCRIS_VOLTRIS     0x00000200  // Pump Voltage Raw Interrupt
// Status
#define FLASH_FCRIS_ERIS        0x00000004  // EEPROM Raw Interrupt Status
#define FLASH_FCRIS_PRIS        0x00000002  // Programming Raw Interrupt Status
#define FLASH_FCRIS_ARIS        0x00000001  // Access Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FCIM register.
//
//*****************************************************************************
#define FLASH_FCIM_PROGMASK     0x00002000  // PROGVER Interrupt Mask
#define FLASH_FCIM_ERMASK       0x00000800  // ERVER Interrupt Mask
#define FLASH_FCIM_INVDMASK     0x00000400  // Invalid Data Interrupt Mask
#define FLASH_FCIM_VOLTMASK     0x00000200  // VOLT Interrupt Mask
#define FLASH_FCIM_EMASK        0x00000004  // EEPROM Interrupt Mask
#define FLASH_FCIM_PMASK        0x00000002  // Programming Interrupt Mask
#define FLASH_FCIM_AMASK        0x00000001  // Access Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FCMISC register.
//
//*****************************************************************************
#define FLASH_FCMISC_PROGMISC   0x00002000  // PROGVER Masked Interrupt Status
// and Clear
#define FLASH_FCMISC_ERMISC     0x00000800  // ERVER Masked Interrupt Status
// and Clear
#define FLASH_FCMISC_INVDMISC   0x00000400  // Invalid Data Masked Interrupt
// Status and Clear
#define FLASH_FCMISC_VOLTMISC   0x00000200  // VOLT Masked Interrupt Status and
// Clear
#define FLASH_FCMISC_EMISC      0x00000004  // EEPROM Masked Interrupt Status
// and Clear
#define FLASH_FCMISC_PMISC      0x00000002  // Programming Masked Interrupt
// Status and Clear
#define FLASH_FCMISC_AMISC      0x00000001  // Access Masked Interrupt Status
// and Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMC2 register.
//
//*****************************************************************************
#define FLASH_FMC2_WRBUF        0x00000001  // Buffered Flash Memory Write

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FWBVAL register.
//
//*****************************************************************************
#define FLASH_FWBVAL_FWB_M      0xFFFFFFFF  // Flash Memory Write Buffer

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FLPEKEY register.
//
//*****************************************************************************
#define FLASH_FLPEKEY_PEKEY_M   0x0000FFFF  // Key Value
#define FLASH_FLPEKEY_PEKEY_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FWBN register.
//
//*****************************************************************************
#define FLASH_FWBN_DATA_M       0xFFFFFFFF  // Data

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_PP register.
//
//*****************************************************************************
#define FLASH_PP_PFC            0x40000000  // Prefetch Buffer Mode
#define FLASH_PP_FMM            0x20000000  // Flash Mirror Mode
#define FLASH_PP_DFA            0x10000000  // DMA Flash Access
#define FLASH_PP_EESS_M         0x00780000  // EEPROM Sector Size of the
// physical bank
#define FLASH_PP_EESS_1KB       0x00000000  // 1 KB
#define FLASH_PP_EESS_2KB       0x00080000  // 2 KB
#define FLASH_PP_EESS_4KB       0x00100000  // 4 KB
#define FLASH_PP_EESS_8KB       0x00180000  // 8 KB
#define FLASH_PP_MAINSS_M       0x00070000  // Flash Sector Size of the
// physical bank
#define FLASH_PP_MAINSS_1KB     0x00000000  // 1 KB
#define FLASH_PP_MAINSS_2KB     0x00010000  // 2 KB
#define FLASH_PP_MAINSS_4KB     0x00020000  // 4 KB
#define FLASH_PP_MAINSS_8KB     0x00030000  // 8 KB
#define FLASH_PP_MAINSS_16KB    0x00040000  // 16 KB
#define FLASH_PP_SIZE_M         0x0000FFFF  // Flash Size
#define FLASH_PP_SIZE_1MB       0x000001FF  // 1024 KB of Flash

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_SSIZE register.
//
//*****************************************************************************
#define FLASH_SSIZE_SIZE_M      0x0000FFFF  // SRAM Size
#define FLASH_SSIZE_SIZE_256KB  0x000003FF  // 256 KB of SRAM

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_CONF register.
//
//*****************************************************************************
#define FLASH_CONF_FMME         0x40000000  // Flash Mirror Mode Enable
#define FLASH_CONF_SPFE         0x20000000  // Single Prefetch Mode Enable
#define FLASH_CONF_CLRTV        0x00100000  // Clear Valid Tags
#define FLASH_CONF_FPFON        0x00020000  // Force Prefetch On
#define FLASH_CONF_FPFOFF       0x00010000  // Force Prefetch Off

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_ROMSWMAP register.
//
//*****************************************************************************
#define FLASH_ROMSWMAP_SW7EN_M  0x0000C000  // ROM SW Region 7 Availability
#define FLASH_ROMSWMAP_SW7EN_NOTVIS                                           \
                                0x00000000  // Software region not available to
// the core
#define FLASH_ROMSWMAP_SW7EN_CORE                                             \
                                0x00004000  // Region available to core
#define FLASH_ROMSWMAP_SW6EN_M  0x00003000  // ROM SW Region 6 Availability
#define FLASH_ROMSWMAP_SW6EN_NOTVIS                                           \
                                0x00000000  // Software region not available to
// the core
#define FLASH_ROMSWMAP_SW6EN_CORE                                             \
                                0x00001000  // Region available to core
#define FLASH_ROMSWMAP_SW5EN_M  0x00000C00  // ROM SW Region 5 Availability
#define FLASH_ROMSWMAP_SW5EN_NOTVIS                                           \
                                0x00000000  // Software region not available to
// the core
#define FLASH_ROMSWMAP_SW5EN_CORE                                             \
                                0x00000400  // Region available to core
#define FLASH_ROMSWMAP_SW4EN_M  0x00000300  // ROM SW Region 4 Availability
#define FLASH_ROMSWMAP_SW4EN_NOTVIS                                           \
                                0x00000000  // Software region not available to
// the core
#define FLASH_ROMSWMAP_SW4EN_CORE                                             \
                                0x00000100  // Region available to core
#define FLASH_ROMSWMAP_SW3EN_M  0x000000C0  // ROM SW Region 3 Availability
#define FLASH_ROMSWMAP_SW3EN_NOTVIS                                           \
                                0x00000000  // Software region not available to
// the core
#define FLASH_ROMSWMAP_SW3EN_CORE                                             \
                                0x00000040  // Region available to core
#define FLASH_ROMSWMAP_SW2EN_M  0x00000030  // ROM SW Region 2 Availability
#define FLASH_ROMSWMAP_SW2EN_NOTVIS                                           \
                                0x00000000  // Software region not available to
// the core
#define FLASH_ROMSWMAP_SW2EN_CORE                                             \
                                0x00000010  // Region available to core
#define FLASH_ROMSWMAP_SW1EN_M  0x0000000C  // ROM SW Region 1 Availability
#define FLASH_ROMSWMAP_SW1EN_NOTVIS                                           \
                                0x00000000  // Software region not available to
// the core
#define FLASH_ROMSWMAP_SW1EN_CORE                                             \
                                0x00000004  // Region available to core
#define FLASH_ROMSWMAP_SW0EN_M  0x00000003  // ROM SW Region 0 Availability
#define FLASH_ROMSWMAP_SW0EN_NOTVIS                                           \
                                0x00000000  // Software region not available to
// the core
#define FLASH_ROMSWMAP_SW0EN_CORE                                             \
                                0x00000001  // Region available to core

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_DMASZ register.
//
//*****************************************************************************
#define FLASH_DMASZ_SIZE_M      0x0003FFFF  // uDMA-accessible Memory Size
#define FLASH_DMASZ_SIZE_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_DMAST register.
//
//*****************************************************************************
#define FLASH_DMAST_ADDR_M      0x1FFFF800  // Contains the starting address of
// the flash region accessible by
// uDMA if the FLASHPP register DFA
// bit is set
#define FLASH_DMAST_ADDR_S      11

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_RVP register.
//
//*****************************************************************************
#define FLASH_RVP_RV_M          0xFFFFFFFF  // Reset Vector Pointer Address
#define FLASH_RVP_RV_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_BOOTCFG register.
//
//*****************************************************************************
#define FLASH_BOOTCFG_NW        0x80000000  // Not Written
#define FLASH_BOOTCFG_PORT_M    0x0000E000  // Boot GPIO Port
#define FLASH_BOOTCFG_PORT_A    0x00000000  // Port A
#define FLASH_BOOTCFG_PORT_B    0x00002000  // Port B
#define FLASH_BOOTCFG_PORT_C    0x00004000  // Port C
#define FLASH_BOOTCFG_PORT_D    0x00006000  // Port D
#define FLASH_BOOTCFG_PORT_E    0x00008000  // Port E
#define FLASH_BOOTCFG_PORT_F    0x0000A000  // Port F
#define FLASH_BOOTCFG_PORT_G    0x0000C000  // Port G
#define FLASH_BOOTCFG_PORT_H    0x0000E000  // Port H
#define FLASH_BOOTCFG_PIN_M     0x00001C00  // Boot GPIO Pin
#define FLASH_BOOTCFG_PIN_0     0x00000000  // Pin 0
#define FLASH_BOOTCFG_PIN_1     0x00000400  // Pin 1
#define FLASH_BOOTCFG_PIN_2     0x00000800  // Pin 2
#define FLASH_BOOTCFG_PIN_3     0x00000C00  // Pin 3
#define FLASH_BOOTCFG_PIN_4     0x00001000  // Pin 4
#define FLASH_BOOTCFG_PIN_5     0x00001400  // Pin 5
#define FLASH_BOOTCFG_PIN_6     0x00001800  // Pin 6
#define FLASH_BOOTCFG_PIN_7     0x00001C00  // Pin 7
#define FLASH_BOOTCFG_POL       0x00000200  // Boot GPIO Polarity
#define FLASH_BOOTCFG_EN        0x00000100  // Boot GPIO Enable
#define FLASH_BOOTCFG_KEY       0x00000010  // KEY Select
#define FLASH_BOOTCFG_DBG1      0x00000002  // Debug Control 1
#define FLASH_BOOTCFG_DBG0      0x00000001  // Debug Control 0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG0 register.
//
//*****************************************************************************
#define FLASH_USERREG0_DATA_M   0xFFFFFFFF  // User Data
#define FLASH_USERREG0_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG1 register.
//
//*****************************************************************************
#define FLASH_USERREG1_DATA_M   0xFFFFFFFF  // User Data
#define FLASH_USERREG1_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG2 register.
//
//*****************************************************************************
#define FLASH_USERREG2_DATA_M   0xFFFFFFFF  // User Data
#define FLASH_USERREG2_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG3 register.
//
//*****************************************************************************
#define FLASH_USERREG3_DATA_M   0xFFFFFFFF  // User Data
#define FLASH_USERREG3_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE8 register.
//
//*****************************************************************************
#define FLASH_FMPRE8_READ_ENABLE_M                                            \
                                0xFFFFFFFF  // Flash Read Enable
#define FLASH_FMPRE8_READ_ENABLE_S                                            \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE9 register.
//
//*****************************************************************************
#define FLASH_FMPRE9_READ_ENABLE_M                                            \
                                0xFFFFFFFF  // Flash Read Enable
#define FLASH_FMPRE9_READ_ENABLE_S                                            \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE10 register.
//
//*****************************************************************************
#define FLASH_FMPRE10_READ_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Read Enable
#define FLASH_FMPRE10_READ_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE11 register.
//
//*****************************************************************************
#define FLASH_FMPRE11_READ_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Read Enable
#define FLASH_FMPRE11_READ_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE12 register.
//
//*****************************************************************************
#define FLASH_FMPRE12_READ_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Read Enable
#define FLASH_FMPRE12_READ_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE13 register.
//
//*****************************************************************************
#define FLASH_FMPRE13_READ_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Read Enable
#define FLASH_FMPRE13_READ_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE14 register.
//
//*****************************************************************************
#define FLASH_FMPRE14_READ_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Read Enable
#define FLASH_FMPRE14_READ_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPRE15 register.
//
//*****************************************************************************
#define FLASH_FMPRE15_READ_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Read Enable
#define FLASH_FMPRE15_READ_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPPE8 register.
//
//*****************************************************************************
#define FLASH_FMPPE8_PROG_ENABLE_M                                            \
                                0xFFFFFFFF  // Flash Programming Enable
#define FLASH_FMPPE8_PROG_ENABLE_S                                            \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPPE9 register.
//
//*****************************************************************************
#define FLASH_FMPPE9_PROG_ENABLE_M                                            \
                                0xFFFFFFFF  // Flash Programming Enable
#define FLASH_FMPPE9_PROG_ENABLE_S                                            \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPPE10 register.
//
//*****************************************************************************
#define FLASH_FMPPE10_PROG_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Programming Enable
#define FLASH_FMPPE10_PROG_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPPE11 register.
//
//*****************************************************************************
#define FLASH_FMPPE11_PROG_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Programming Enable
#define FLASH_FMPPE11_PROG_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPPE12 register.
//
//*****************************************************************************
#define FLASH_FMPPE12_PROG_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Programming Enable
#define FLASH_FMPPE12_PROG_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPPE13 register.
//
//*****************************************************************************
#define FLASH_FMPPE13_PROG_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Programming Enable
#define FLASH_FMPPE13_PROG_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPPE14 register.
//
//*****************************************************************************
#define FLASH_FMPPE14_PROG_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Programming Enable
#define FLASH_FMPPE14_PROG_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMPPE15 register.
//
//*****************************************************************************
#define FLASH_FMPPE15_PROG_ENABLE_M                                           \
                                0xFFFFFFFF  // Flash Programming Enable
#define FLASH_FMPPE15_PROG_ENABLE_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DID0 register.
//
//*****************************************************************************
#define SYSCTL_DID0_VER_M       0x70000000  // DID0 Version
#define SYSCTL_DID0_VER_1       0x10000000  // Second version of the DID0
// register format.
#define SYSCTL_DID0_CLASS_M     0x00FF0000  // Device Class
#define SYSCTL_DID0_CLASS_MSP432E4                                            \
                                0x000C0000  // MSP432E4 microcontrollers
#define SYSCTL_DID0_MAJ_M       0x0000FF00  // Major Revision
#define SYSCTL_DID0_MAJ_REVA    0x00000000  // Revision A (initial device)
#define SYSCTL_DID0_MAJ_REVB    0x00000100  // Revision B (first base layer
// revision)
#define SYSCTL_DID0_MAJ_REVC    0x00000200  // Revision C (second base layer
// revision)
#define SYSCTL_DID0_MIN_M       0x000000FF  // Minor Revision
#define SYSCTL_DID0_MIN_0       0x00000000  // Initial device, or a major
// revision update
#define SYSCTL_DID0_MIN_1       0x00000001  // First metal layer change
#define SYSCTL_DID0_MIN_2       0x00000002  // Second metal layer change

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DID1 register.
//
//*****************************************************************************
#define SYSCTL_DID1_VER_M       0xF0000000  // DID1 Version
#define SYSCTL_DID1_VER_1       0x10000000  // Second version of DID1
#define SYSCTL_DID1_FAM_M       0x0F000000  // Family
#define SYSCTL_DID1_FAM_MSP432E4                                            \
                                0x00000000  // MSP432E4 family of microcontollers
#define SYSCTL_DID1_PRTNO_M     0x00FF0000  // Part Number
#define SYSCTL_DID1_PRTNO_MSP432E401Y                                       \
                                0x002D0000  // MSP432E401Y
#define SYSCTL_DID1_PINCNT_M    0x0000E000  // Package Pin Count
#define SYSCTL_DID1_PINCNT_128  0x0000C000  // 128-pin TQFP package
#define SYSCTL_DID1_PINCNT_212  0x0000E000  // 212-pin BGA package
#define SYSCTL_DID1_TEMP_M      0x000000E0  // Temperature Range
#define SYSCTL_DID1_TEMP_C      0x00000000  // Commercial temperature range
#define SYSCTL_DID1_TEMP_I      0x00000020  // Industrial temperature range
#define SYSCTL_DID1_TEMP_E      0x00000040  // Extended temperature range
#define SYSCTL_DID1_PKG_M       0x00000018  // Package Type
#define SYSCTL_DID1_PKG_QFP     0x00000008  // QFP package
#define SYSCTL_DID1_PKG_BGA     0x00000010  // BGA package
#define SYSCTL_DID1_ROHS        0x00000004  // RoHS-Compliance
#define SYSCTL_DID1_QUAL_M      0x00000003  // Qualification Status
#define SYSCTL_DID1_QUAL_ES     0x00000000  // Engineering Sample (unqualified)
#define SYSCTL_DID1_QUAL_PP     0x00000001  // Pilot Production (unqualified)
#define SYSCTL_DID1_QUAL_FQ     0x00000002  // Fully Qualified

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PTBOCTL register.
//
//*****************************************************************************
#define SYSCTL_PTBOCTL_VDDA_UBOR_M                                            \
                                0x00000300  // VDDA under BOR Event Action
#define SYSCTL_PTBOCTL_VDDA_UBOR_NONE                                         \
                                0x00000000  // No Action
#define SYSCTL_PTBOCTL_VDDA_UBOR_SYSINT                                       \
                                0x00000100  // System control interrupt
#define SYSCTL_PTBOCTL_VDDA_UBOR_NMI                                          \
                                0x00000200  // NMI
#define SYSCTL_PTBOCTL_VDDA_UBOR_RST                                          \
                                0x00000300  // Reset
#define SYSCTL_PTBOCTL_VDD_UBOR_M                                             \
                                0x00000003  // VDD (VDDS) under BOR Event
// Action
#define SYSCTL_PTBOCTL_VDD_UBOR_NONE                                          \
                                0x00000000  // No Action
#define SYSCTL_PTBOCTL_VDD_UBOR_SYSINT                                        \
                                0x00000001  // System control interrupt
#define SYSCTL_PTBOCTL_VDD_UBOR_NMI                                           \
                                0x00000002  // NMI
#define SYSCTL_PTBOCTL_VDD_UBOR_RST                                           \
                                0x00000003  // Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RIS register.
//
//*****************************************************************************
#define SYSCTL_RIS_MOSCPUPRIS   0x00000100  // MOSC Power Up Raw Interrupt
// Status
#define SYSCTL_RIS_PLLLRIS      0x00000040  // PLL Lock Raw Interrupt Status
#define SYSCTL_RIS_MOFRIS       0x00000008  // Main Oscillator Failure Raw
// Interrupt Status
#define SYSCTL_RIS_BORRIS       0x00000002  // Brown-Out Reset Raw Interrupt
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_IMC register.
//
//*****************************************************************************
#define SYSCTL_IMC_MOSCPUPIM    0x00000100  // MOSC Power Up Interrupt Mask
#define SYSCTL_IMC_PLLLIM       0x00000040  // PLL Lock Interrupt Mask
#define SYSCTL_IMC_MOFIM        0x00000008  // Main Oscillator Failure
// Interrupt Mask
#define SYSCTL_IMC_BORIM        0x00000002  // Brown-Out Reset Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_MISC register.
//
//*****************************************************************************
#define SYSCTL_MISC_MOSCPUPMIS  0x00000100  // MOSC Power Up Masked Interrupt
// Status
#define SYSCTL_MISC_PLLLMIS     0x00000040  // PLL Lock Masked Interrupt Status
#define SYSCTL_MISC_MOFMIS      0x00000008  // Main Oscillator Failure Masked
// Interrupt Status
#define SYSCTL_MISC_BORMIS      0x00000002  // BOR Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RESC register.
//
//*****************************************************************************
#define SYSCTL_RESC_MOSCFAIL    0x00010000  // MOSC Failure Reset
#define SYSCTL_RESC_HSSR        0x00001000  // HSSR Reset
#define SYSCTL_RESC_WDT1        0x00000020  // Watchdog Timer 1 Reset
#define SYSCTL_RESC_SW          0x00000010  // Software Reset
#define SYSCTL_RESC_WDT0        0x00000008  // Watchdog Timer 0 Reset
#define SYSCTL_RESC_BOR         0x00000004  // Brown-Out Reset
#define SYSCTL_RESC_POR         0x00000002  // Power-On Reset
#define SYSCTL_RESC_EXT         0x00000001  // External Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PWRTC register.
//
//*****************************************************************************
#define SYSCTL_PWRTC_VDDA_UBOR  0x00000010  // VDDA Under BOR Status
#define SYSCTL_PWRTC_VDD_UBOR   0x00000001  // VDD Under BOR Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_NMIC register.
//
//*****************************************************************************
#define SYSCTL_NMIC_MOSCFAIL    0x00010000  // MOSC Failure NMI
#define SYSCTL_NMIC_TAMPER      0x00000200  // Tamper Event NMI
#define SYSCTL_NMIC_WDT1        0x00000020  // Watch Dog Timer (WDT) 1 NMI
#define SYSCTL_NMIC_WDT0        0x00000008  // Watch Dog Timer (WDT) 0 NMI
#define SYSCTL_NMIC_POWER       0x00000004  // Power/Brown Out Event NMI
#define SYSCTL_NMIC_EXTERNAL    0x00000001  // External Pin NMI

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_MOSCCTL register.
//
//*****************************************************************************
#define SYSCTL_MOSCCTL_OSCRNG   0x00000010  // Oscillator Range
#define SYSCTL_MOSCCTL_PWRDN    0x00000008  // Power Down
#define SYSCTL_MOSCCTL_NOXTAL   0x00000004  // No Crystal Connected
#define SYSCTL_MOSCCTL_MOSCIM   0x00000002  // MOSC Failure Action
#define SYSCTL_MOSCCTL_CVAL     0x00000001  // Clock Validation for MOSC

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RSCLKCFG
// register.
//
//*****************************************************************************
#define SYSCTL_RSCLKCFG_MEMTIMU 0x80000000  // Memory Timing Register Update
#define SYSCTL_RSCLKCFG_NEWFREQ 0x40000000  // New PLLFREQ Accept
#define SYSCTL_RSCLKCFG_ACG     0x20000000  // Auto Clock Gating
#define SYSCTL_RSCLKCFG_USEPLL  0x10000000  // Use PLL
#define SYSCTL_RSCLKCFG_PLLSRC_M                                              \
                                0x0F000000  // PLL Source
#define SYSCTL_RSCLKCFG_PLLSRC_PIOSC                                          \
                                0x00000000  // PIOSC is PLL input clock source
#define SYSCTL_RSCLKCFG_PLLSRC_MOSC                                           \
                                0x03000000  // MOSC is the PLL input clock
// source
#define SYSCTL_RSCLKCFG_OSCSRC_M                                              \
                                0x00F00000  // Oscillator Source
#define SYSCTL_RSCLKCFG_OSCSRC_PIOSC                                          \
                                0x00000000  // PIOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_LFIOSC                                         \
                                0x00200000  // LFIOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_MOSC                                           \
                                0x00300000  // MOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_RTC                                            \
                                0x00400000  // Hibernation Module RTC
// Oscillator (RTCOSC)
#define SYSCTL_RSCLKCFG_OSYSDIV_M                                             \
                                0x000FFC00  // Oscillator System Clock Divisor
#define SYSCTL_RSCLKCFG_PSYSDIV_M                                             \
                                0x000003FF  // PLL System Clock Divisor
#define SYSCTL_RSCLKCFG_OSYSDIV_S                                             \
                                10
#define SYSCTL_RSCLKCFG_PSYSDIV_S                                             \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_MEMTIM0 register.
//
//*****************************************************************************
#define SYSCTL_MEMTIM0_EBCHT_M  0x03C00000  // EEPROM Clock High Time
#define SYSCTL_MEMTIM0_EBCHT_0_5                                              \
                                0x00000000  // 1/2 system clock period
#define SYSCTL_MEMTIM0_EBCHT_1  0x00400000  // 1 system clock period
#define SYSCTL_MEMTIM0_EBCHT_1_5                                              \
                                0x00800000  // 1.5 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_2  0x00C00000  // 2 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_2_5                                              \
                                0x01000000  // 2.5 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_3  0x01400000  // 3 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_3_5                                              \
                                0x01800000  // 3.5 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_4  0x01C00000  // 4 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_4_5                                              \
                                0x02000000  // 4.5 system clock periods
#define SYSCTL_MEMTIM0_EBCE     0x00200000  // EEPROM Bank Clock Edge
#define SYSCTL_MEMTIM0_MB1      0x00100010  // Must be one
#define SYSCTL_MEMTIM0_EWS_M    0x000F0000  // EEPROM Wait States
#define SYSCTL_MEMTIM0_FBCHT_M  0x000003C0  // Flash Bank Clock High Time
#define SYSCTL_MEMTIM0_FBCHT_0_5                                              \
                                0x00000000  // 1/2 system clock period
#define SYSCTL_MEMTIM0_FBCHT_1  0x00000040  // 1 system clock period
#define SYSCTL_MEMTIM0_FBCHT_1_5                                              \
                                0x00000080  // 1.5 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_2  0x000000C0  // 2 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_2_5                                              \
                                0x00000100  // 2.5 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_3  0x00000140  // 3 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_3_5                                              \
                                0x00000180  // 3.5 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_4  0x000001C0  // 4 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_4_5                                              \
                                0x00000200  // 4.5 system clock periods
#define SYSCTL_MEMTIM0_FBCE     0x00000020  // Flash Bank Clock Edge
#define SYSCTL_MEMTIM0_FWS_M    0x0000000F  // Flash Wait State
#define SYSCTL_MEMTIM0_EWS_S    16
#define SYSCTL_MEMTIM0_FWS_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_ALTCLKCFG
// register.
//
//*****************************************************************************
#define SYSCTL_ALTCLKCFG_ALTCLK_M                                             \
                                0x0000000F  // Alternate Clock Source
#define SYSCTL_ALTCLKCFG_ALTCLK_PIOSC                                         \
                                0x00000000  // PIOSC
#define SYSCTL_ALTCLKCFG_ALTCLK_RTCOSC                                        \
                                0x00000003  // Hibernation Module Real-time
// clock output (RTCOSC)
#define SYSCTL_ALTCLKCFG_ALTCLK_LFIOSC                                        \
                                0x00000004  // Low-frequency internal
// oscillator (LFIOSC)

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DSCLKCFG
// register.
//
//*****************************************************************************
#define SYSCTL_DSCLKCFG_PIOSCPD 0x80000000  // PIOSC Power Down
#define SYSCTL_DSCLKCFG_MOSCDPD 0x40000000  // MOSC Disable Power Down
#define SYSCTL_DSCLKCFG_DSOSCSRC_M                                            \
                                0x00F00000  // Deep Sleep Oscillator Source
#define SYSCTL_DSCLKCFG_DSOSCSRC_PIOSC                                        \
                                0x00000000  // PIOSC
#define SYSCTL_DSCLKCFG_DSOSCSRC_LFIOSC                                       \
                                0x00200000  // LFIOSC
#define SYSCTL_DSCLKCFG_DSOSCSRC_MOSC                                         \
                                0x00300000  // MOSC
#define SYSCTL_DSCLKCFG_DSOSCSRC_RTC                                          \
                                0x00400000  // Hibernation Module RTCOSC
#define SYSCTL_DSCLKCFG_DSSYSDIV_M                                            \
                                0x000003FF  // Deep Sleep Clock Divisor
#define SYSCTL_DSCLKCFG_DSSYSDIV_S                                            \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DIVSCLK register.
//
//*****************************************************************************
#define SYSCTL_DIVSCLK_EN       0x80000000  // DIVSCLK Enable
#define SYSCTL_DIVSCLK_SRC_M    0x00030000  // Clock Source
#define SYSCTL_DIVSCLK_SRC_SYSCLK                                             \
                                0x00000000  // System Clock
#define SYSCTL_DIVSCLK_SRC_PIOSC                                              \
                                0x00010000  // PIOSC
#define SYSCTL_DIVSCLK_SRC_MOSC 0x00020000  // MOSC
#define SYSCTL_DIVSCLK_DIV_M    0x000000FF  // Divisor Value
#define SYSCTL_DIVSCLK_DIV_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SYSPROP register.
//
//*****************************************************************************
#define SYSCTL_SYSPROP_FPU      0x00000001  // FPU Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PIOSCCAL
// register.
//
//*****************************************************************************
#define SYSCTL_PIOSCCAL_UTEN    0x80000000  // Use User Trim Value
#define SYSCTL_PIOSCCAL_CAL     0x00000200  // Start Calibration
#define SYSCTL_PIOSCCAL_UPDATE  0x00000100  // Update Trim
#define SYSCTL_PIOSCCAL_UT_M    0x0000007F  // User Trim Value
#define SYSCTL_PIOSCCAL_UT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PIOSCSTAT
// register.
//
//*****************************************************************************
#define SYSCTL_PIOSCSTAT_DT_M   0x007F0000  // Default Trim Value
#define SYSCTL_PIOSCSTAT_CR_M   0x00000300  // Calibration Result
#define SYSCTL_PIOSCSTAT_CRNONE 0x00000000  // Calibration has not been
// attempted
#define SYSCTL_PIOSCSTAT_CRPASS 0x00000100  // The last calibration operation
// completed to meet 1% accuracy
#define SYSCTL_PIOSCSTAT_CRFAIL 0x00000200  // The last calibration operation
// failed to meet 1% accuracy
#define SYSCTL_PIOSCSTAT_CT_M   0x0000007F  // Calibration Trim Value
#define SYSCTL_PIOSCSTAT_DT_S   16
#define SYSCTL_PIOSCSTAT_CT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PLLFREQ0
// register.
//
//*****************************************************************************
#define SYSCTL_PLLFREQ0_PLLPWR  0x00800000  // PLL Power
#define SYSCTL_PLLFREQ0_MFRAC_M 0x000FFC00  // PLL M Fractional Value
#define SYSCTL_PLLFREQ0_MINT_M  0x000003FF  // PLL M Integer Value
#define SYSCTL_PLLFREQ0_MFRAC_S 10
#define SYSCTL_PLLFREQ0_MINT_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PLLFREQ1
// register.
//
//*****************************************************************************
#define SYSCTL_PLLFREQ1_Q_M     0x00001F00  // PLL Q Value
#define SYSCTL_PLLFREQ1_N_M     0x0000001F  // PLL N Value
#define SYSCTL_PLLFREQ1_Q_S     8
#define SYSCTL_PLLFREQ1_N_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PLLSTAT register.
//
//*****************************************************************************
#define SYSCTL_PLLSTAT_LOCK     0x00000001  // PLL Lock

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SLPPWRCFG
// register.
//
//*****************************************************************************
#define SYSCTL_SLPPWRCFG_FLASHPM_M                                            \
                                0x00000030  // Flash Power Modes
#define SYSCTL_SLPPWRCFG_FLASHPM_NRM                                          \
                                0x00000000  // Active Mode
#define SYSCTL_SLPPWRCFG_FLASHPM_SLP                                          \
                                0x00000020  // Low Power Mode
#define SYSCTL_SLPPWRCFG_SRAMPM_M                                             \
                                0x00000003  // SRAM Power Modes
#define SYSCTL_SLPPWRCFG_SRAMPM_NRM                                           \
                                0x00000000  // Active Mode
#define SYSCTL_SLPPWRCFG_SRAMPM_SBY                                           \
                                0x00000001  // Standby Mode
#define SYSCTL_SLPPWRCFG_SRAMPM_LP                                            \
                                0x00000003  // Low Power Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DSLPPWRCFG
// register.
//
//*****************************************************************************
#define SYSCTL_DSLPPWRCFG_LDOSM 0x00000200  // LDO Sleep Mode
#define SYSCTL_DSLPPWRCFG_TSPD  0x00000100  // Temperature Sense Power Down
#define SYSCTL_DSLPPWRCFG_FLASHPM_M                                           \
                                0x00000030  // Flash Power Modes
#define SYSCTL_DSLPPWRCFG_FLASHPM_NRM                                         \
                                0x00000000  // Active Mode
#define SYSCTL_DSLPPWRCFG_FLASHPM_SLP                                         \
                                0x00000020  // Low Power Mode
#define SYSCTL_DSLPPWRCFG_SRAMPM_M                                            \
                                0x00000003  // SRAM Power Modes
#define SYSCTL_DSLPPWRCFG_SRAMPM_NRM                                          \
                                0x00000000  // Active Mode
#define SYSCTL_DSLPPWRCFG_SRAMPM_SBY                                          \
                                0x00000001  // Standby Mode
#define SYSCTL_DSLPPWRCFG_SRAMPM_LP                                           \
                                0x00000003  // Low Power Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_NVMSTAT register.
//
//*****************************************************************************
#define SYSCTL_NVMSTAT_FWB      0x00000001  // 32 Word Flash Write Buffer
// Available

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_LDOSPCTL
// register.
//
//*****************************************************************************
#define SYSCTL_LDOSPCTL_VADJEN  0x80000000  // Voltage Adjust Enable
#define SYSCTL_LDOSPCTL_VLDO_M  0x000000FF  // LDO Output Voltage
#define SYSCTL_LDOSPCTL_VLDO_0_90V                                            \
                                0x00000012  // 0.90 V
#define SYSCTL_LDOSPCTL_VLDO_0_95V                                            \
                                0x00000013  // 0.95 V
#define SYSCTL_LDOSPCTL_VLDO_1_00V                                            \
                                0x00000014  // 1.00 V
#define SYSCTL_LDOSPCTL_VLDO_1_05V                                            \
                                0x00000015  // 1.05 V
#define SYSCTL_LDOSPCTL_VLDO_1_10V                                            \
                                0x00000016  // 1.10 V
#define SYSCTL_LDOSPCTL_VLDO_1_15V                                            \
                                0x00000017  // 1.15 V
#define SYSCTL_LDOSPCTL_VLDO_1_20V                                            \
                                0x00000018  // 1.20 V

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_LDODPCTL
// register.
//
//*****************************************************************************
#define SYSCTL_LDODPCTL_VADJEN  0x80000000  // Voltage Adjust Enable
#define SYSCTL_LDODPCTL_VLDO_M  0x000000FF  // LDO Output Voltage
#define SYSCTL_LDODPCTL_VLDO_0_90V                                            \
                                0x00000012  // 0.90 V
#define SYSCTL_LDODPCTL_VLDO_0_95V                                            \
                                0x00000013  // 0.95 V
#define SYSCTL_LDODPCTL_VLDO_1_00V                                            \
                                0x00000014  // 1.00 V
#define SYSCTL_LDODPCTL_VLDO_1_05V                                            \
                                0x00000015  // 1.05 V
#define SYSCTL_LDODPCTL_VLDO_1_10V                                            \
                                0x00000016  // 1.10 V
#define SYSCTL_LDODPCTL_VLDO_1_15V                                            \
                                0x00000017  // 1.15 V
#define SYSCTL_LDODPCTL_VLDO_1_20V                                            \
                                0x00000018  // 1.20 V
#define SYSCTL_LDODPCTL_VLDO_1_25V                                            \
                                0x00000019  // 1.25 V
#define SYSCTL_LDODPCTL_VLDO_1_30V                                            \
                                0x0000001A  // 1.30 V
#define SYSCTL_LDODPCTL_VLDO_1_35V                                            \
                                0x0000001B  // 1.35 V

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RESBEHAVCTL
// register.
//
//*****************************************************************************
#define SYSCTL_RESBEHAVCTL_WDOG1_M                                            \
                                0x000000C0  // Watchdog 1 Reset Operation
#define SYSCTL_RESBEHAVCTL_WDOG1_SYSRST                                       \
                                0x00000080  // Watchdog 1 issues a system
// reset. The application starts
// within 10 us
#define SYSCTL_RESBEHAVCTL_WDOG1_POR                                          \
                                0x000000C0  // Watchdog 1 issues a simulated
// POR sequence. Application starts
// less than 500 us after
// deassertion (Default)
#define SYSCTL_RESBEHAVCTL_WDOG0_M                                            \
                                0x00000030  // Watchdog 0 Reset Operation
#define SYSCTL_RESBEHAVCTL_WDOG0_SYSRST                                       \
                                0x00000020  // Watchdog 0 issues a system
// reset. The application starts
// within 10 us
#define SYSCTL_RESBEHAVCTL_WDOG0_POR                                          \
                                0x00000030  // Watchdog 0 issues a simulated
// POR sequence. Application starts
// less than 500 us after
// deassertion (Default)
#define SYSCTL_RESBEHAVCTL_BOR_M                                              \
                                0x0000000C  // BOR Reset operation
#define SYSCTL_RESBEHAVCTL_BOR_SYSRST                                         \
                                0x00000008  // Brown Out Reset issues system
// reset. The application starts
// within 10 us
#define SYSCTL_RESBEHAVCTL_BOR_POR                                            \
                                0x0000000C  // Brown Out Reset issues a
// simulated POR sequence. The
// application starts less than 500
// us after deassertion (Default)
#define SYSCTL_RESBEHAVCTL_EXTRES_M                                           \
                                0x00000003  // External RST Pin Operation
#define SYSCTL_RESBEHAVCTL_EXTRES_SYSRST                                      \
                                0x00000002  // External RST assertion issues a
// system reset. The application
// starts within 10 us
#define SYSCTL_RESBEHAVCTL_EXTRES_POR                                         \
                                0x00000003  // External RST assertion issues a
// simulated POR sequence.
// Application starts less than 500
// us after deassertion (Default)

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_HSSR register.
//
//*****************************************************************************
#define SYSCTL_HSSR_KEY_M       0xFF000000  // Write Key
#define SYSCTL_HSSR_CDOFF_M     0x00FFFFFF  // Command Descriptor Pointer
#define SYSCTL_HSSR_KEY_S       24
#define SYSCTL_HSSR_CDOFF_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_USBPDS register.
//
//*****************************************************************************
#define SYSCTL_USBPDS_MEMSTAT_M 0x0000000C  // Memory Array Power Status
#define SYSCTL_USBPDS_MEMSTAT_OFF                                             \
                                0x00000000  // Array OFF
#define SYSCTL_USBPDS_MEMSTAT_RETAIN                                          \
                                0x00000004  // SRAM Retention
#define SYSCTL_USBPDS_MEMSTAT_ON                                              \
                                0x0000000C  // Array On
#define SYSCTL_USBPDS_PWRSTAT_M 0x00000003  // Power Domain Status
#define SYSCTL_USBPDS_PWRSTAT_OFF                                             \
                                0x00000000  // OFF
#define SYSCTL_USBPDS_PWRSTAT_ON                                              \
                                0x00000003  // ON

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_USBMPC register.
//
//*****************************************************************************
#define SYSCTL_USBMPC_PWRCTL_M  0x00000003  // Memory Array Power Control
#define SYSCTL_USBMPC_PWRCTL_OFF                                              \
                                0x00000000  // Array OFF
#define SYSCTL_USBMPC_PWRCTL_RETAIN                                           \
                                0x00000001  // SRAM Retention
#define SYSCTL_USBMPC_PWRCTL_ON 0x00000003  // Array On

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_EMACPDS register.
//
//*****************************************************************************
#define SYSCTL_EMACPDS_MEMSTAT_M                                              \
                                0x0000000C  // Memory Array Power Status
#define SYSCTL_EMACPDS_MEMSTAT_OFF                                            \
                                0x00000000  // Array OFF
#define SYSCTL_EMACPDS_MEMSTAT_ON                                             \
                                0x0000000C  // Array On
#define SYSCTL_EMACPDS_PWRSTAT_M                                              \
                                0x00000003  // Power Domain Status
#define SYSCTL_EMACPDS_PWRSTAT_OFF                                            \
                                0x00000000  // OFF
#define SYSCTL_EMACPDS_PWRSTAT_ON                                             \
                                0x00000003  // ON

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_EMACMPC register.
//
//*****************************************************************************
#define SYSCTL_EMACMPC_PWRCTL_M 0x00000003  // Memory Array Power Control
#define SYSCTL_EMACMPC_PWRCTL_OFF                                             \
                                0x00000000  // Array OFF
#define SYSCTL_EMACMPC_PWRCTL_ON                                              \
                                0x00000003  // Array On

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPWD register.
//
//*****************************************************************************
#define SYSCTL_PPWD_P1          0x00000002  // Watchdog Timer 1 Present
#define SYSCTL_PPWD_P0          0x00000001  // Watchdog Timer 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPTIMER register.
//
//*****************************************************************************
#define SYSCTL_PPTIMER_P7       0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Present
#define SYSCTL_PPTIMER_P6       0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Present
#define SYSCTL_PPTIMER_P5       0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Present
#define SYSCTL_PPTIMER_P4       0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Present
#define SYSCTL_PPTIMER_P3       0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Present
#define SYSCTL_PPTIMER_P2       0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Present
#define SYSCTL_PPTIMER_P1       0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Present
#define SYSCTL_PPTIMER_P0       0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPGPIO register.
//
//*****************************************************************************
#define SYSCTL_PPGPIO_P14       0x00004000  // GPIO Port Q Present
#define SYSCTL_PPGPIO_P13       0x00002000  // GPIO Port P Present
#define SYSCTL_PPGPIO_P12       0x00001000  // GPIO Port N Present
#define SYSCTL_PPGPIO_P11       0x00000800  // GPIO Port M Present
#define SYSCTL_PPGPIO_P10       0x00000400  // GPIO Port L Present
#define SYSCTL_PPGPIO_P9        0x00000200  // GPIO Port K Present
#define SYSCTL_PPGPIO_P8        0x00000100  // GPIO Port J Present
#define SYSCTL_PPGPIO_P7        0x00000080  // GPIO Port H Present
#define SYSCTL_PPGPIO_P6        0x00000040  // GPIO Port G Present
#define SYSCTL_PPGPIO_P5        0x00000020  // GPIO Port F Present
#define SYSCTL_PPGPIO_P4        0x00000010  // GPIO Port E Present
#define SYSCTL_PPGPIO_P3        0x00000008  // GPIO Port D Present
#define SYSCTL_PPGPIO_P2        0x00000004  // GPIO Port C Present
#define SYSCTL_PPGPIO_P1        0x00000002  // GPIO Port B Present
#define SYSCTL_PPGPIO_P0        0x00000001  // GPIO Port A Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPDMA register.
//
//*****************************************************************************
#define SYSCTL_PPDMA_P0         0x00000001  // uDMA Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPEPI register.
//
//*****************************************************************************
#define SYSCTL_PPEPI_P0         0x00000001  // EPI Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPHIB register.
//
//*****************************************************************************
#define SYSCTL_PPHIB_P0         0x00000001  // Hibernation Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPUART register.
//
//*****************************************************************************
#define SYSCTL_PPUART_P7        0x00000080  // UART Module 7 Present
#define SYSCTL_PPUART_P6        0x00000040  // UART Module 6 Present
#define SYSCTL_PPUART_P5        0x00000020  // UART Module 5 Present
#define SYSCTL_PPUART_P4        0x00000010  // UART Module 4 Present
#define SYSCTL_PPUART_P3        0x00000008  // UART Module 3 Present
#define SYSCTL_PPUART_P2        0x00000004  // UART Module 2 Present
#define SYSCTL_PPUART_P1        0x00000002  // UART Module 1 Present
#define SYSCTL_PPUART_P0        0x00000001  // UART Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPSSI register.
//
//*****************************************************************************
#define SYSCTL_PPSSI_P3         0x00000008  // SSI Module 3 Present
#define SYSCTL_PPSSI_P2         0x00000004  // SSI Module 2 Present
#define SYSCTL_PPSSI_P1         0x00000002  // SSI Module 1 Present
#define SYSCTL_PPSSI_P0         0x00000001  // SSI Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPI2C register.
//
//*****************************************************************************
#define SYSCTL_PPI2C_P9         0x00000200  // I2C Module 9 Present
#define SYSCTL_PPI2C_P8         0x00000100  // I2C Module 8 Present
#define SYSCTL_PPI2C_P7         0x00000080  // I2C Module 7 Present
#define SYSCTL_PPI2C_P6         0x00000040  // I2C Module 6 Present
#define SYSCTL_PPI2C_P5         0x00000020  // I2C Module 5 Present
#define SYSCTL_PPI2C_P4         0x00000010  // I2C Module 4 Present
#define SYSCTL_PPI2C_P3         0x00000008  // I2C Module 3 Present
#define SYSCTL_PPI2C_P2         0x00000004  // I2C Module 2 Present
#define SYSCTL_PPI2C_P1         0x00000002  // I2C Module 1 Present
#define SYSCTL_PPI2C_P0         0x00000001  // I2C Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPUSB register.
//
//*****************************************************************************
#define SYSCTL_PPUSB_P0         0x00000001  // USB Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPEPHY register.
//
//*****************************************************************************
#define SYSCTL_PPEPHY_P0        0x00000001  // Ethernet PHY Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPCAN register.
//
//*****************************************************************************
#define SYSCTL_PPCAN_P1         0x00000002  // CAN Module 1 Present
#define SYSCTL_PPCAN_P0         0x00000001  // CAN Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPADC register.
//
//*****************************************************************************
#define SYSCTL_PPADC_P1         0x00000002  // ADC Module 1 Present
#define SYSCTL_PPADC_P0         0x00000001  // ADC Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPACMP register.
//
//*****************************************************************************
#define SYSCTL_PPACMP_P0        0x00000001  // Analog Comparator Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPPWM register.
//
//*****************************************************************************
#define SYSCTL_PPPWM_P0         0x00000001  // PWM Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPQEI register.
//
//*****************************************************************************
#define SYSCTL_PPQEI_P0         0x00000001  // QEI Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_PPEEPROM_P0      0x00000001  // EEPROM Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPCCM register.
//
//*****************************************************************************
#define SYSCTL_PPCCM_P0         0x00000001  // CRC and Cryptographic Modules
// Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPLCD register.
//
//*****************************************************************************
#define SYSCTL_PPLCD_P0         0x00000001  // LCD Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPOWIRE register.
//
//*****************************************************************************
#define SYSCTL_PPOWIRE_P0       0x00000001  // 1-Wire Module Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPEMAC register.
//
//*****************************************************************************
#define SYSCTL_PPEMAC_P0        0x00000001  // Ethernet Controller Module
// Present


//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRWD register.
//
//*****************************************************************************
#define SYSCTL_SRWD_R1          0x00000002  // Watchdog Timer 1 Software Reset
#define SYSCTL_SRWD_R0          0x00000001  // Watchdog Timer 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRTIMER register.
//
//*****************************************************************************
#define SYSCTL_SRTIMER_R7       0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Software Reset
#define SYSCTL_SRTIMER_R6       0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Software Reset
#define SYSCTL_SRTIMER_R5       0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Software Reset
#define SYSCTL_SRTIMER_R4       0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Software Reset
#define SYSCTL_SRTIMER_R3       0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Software Reset
#define SYSCTL_SRTIMER_R2       0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Software Reset
#define SYSCTL_SRTIMER_R1       0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Software Reset
#define SYSCTL_SRTIMER_R0       0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRGPIO register.
//
//*****************************************************************************
#define SYSCTL_SRGPIO_R14       0x00004000  // GPIO Port Q Software Reset
#define SYSCTL_SRGPIO_R13       0x00002000  // GPIO Port P Software Reset
#define SYSCTL_SRGPIO_R12       0x00001000  // GPIO Port N Software Reset
#define SYSCTL_SRGPIO_R11       0x00000800  // GPIO Port M Software Reset
#define SYSCTL_SRGPIO_R10       0x00000400  // GPIO Port L Software Reset
#define SYSCTL_SRGPIO_R9        0x00000200  // GPIO Port K Software Reset
#define SYSCTL_SRGPIO_R8        0x00000100  // GPIO Port J Software Reset
#define SYSCTL_SRGPIO_R7        0x00000080  // GPIO Port H Software Reset
#define SYSCTL_SRGPIO_R6        0x00000040  // GPIO Port G Software Reset
#define SYSCTL_SRGPIO_R5        0x00000020  // GPIO Port F Software Reset
#define SYSCTL_SRGPIO_R4        0x00000010  // GPIO Port E Software Reset
#define SYSCTL_SRGPIO_R3        0x00000008  // GPIO Port D Software Reset
#define SYSCTL_SRGPIO_R2        0x00000004  // GPIO Port C Software Reset
#define SYSCTL_SRGPIO_R1        0x00000002  // GPIO Port B Software Reset
#define SYSCTL_SRGPIO_R0        0x00000001  // GPIO Port A Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRDMA register.
//
//*****************************************************************************
#define SYSCTL_SRDMA_R0         0x00000001  // uDMA Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SREPI register.
//
//*****************************************************************************
#define SYSCTL_SREPI_R0         0x00000001  // EPI Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRHIB register.
//
//*****************************************************************************
#define SYSCTL_SRHIB_R0         0x00000001  // Hibernation Module Software
// Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRUART register.
//
//*****************************************************************************
#define SYSCTL_SRUART_R7        0x00000080  // UART Module 7 Software Reset
#define SYSCTL_SRUART_R6        0x00000040  // UART Module 6 Software Reset
#define SYSCTL_SRUART_R5        0x00000020  // UART Module 5 Software Reset
#define SYSCTL_SRUART_R4        0x00000010  // UART Module 4 Software Reset
#define SYSCTL_SRUART_R3        0x00000008  // UART Module 3 Software Reset
#define SYSCTL_SRUART_R2        0x00000004  // UART Module 2 Software Reset
#define SYSCTL_SRUART_R1        0x00000002  // UART Module 1 Software Reset
#define SYSCTL_SRUART_R0        0x00000001  // UART Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRSSI register.
//
//*****************************************************************************
#define SYSCTL_SRSSI_R3         0x00000008  // SSI Module 3 Software Reset
#define SYSCTL_SRSSI_R2         0x00000004  // SSI Module 2 Software Reset
#define SYSCTL_SRSSI_R1         0x00000002  // SSI Module 1 Software Reset
#define SYSCTL_SRSSI_R0         0x00000001  // SSI Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRI2C register.
//
//*****************************************************************************
#define SYSCTL_SRI2C_R9         0x00000200  // I2C Module 9 Software Reset
#define SYSCTL_SRI2C_R8         0x00000100  // I2C Module 8 Software Reset
#define SYSCTL_SRI2C_R7         0x00000080  // I2C Module 7 Software Reset
#define SYSCTL_SRI2C_R6         0x00000040  // I2C Module 6 Software Reset
#define SYSCTL_SRI2C_R5         0x00000020  // I2C Module 5 Software Reset
#define SYSCTL_SRI2C_R4         0x00000010  // I2C Module 4 Software Reset
#define SYSCTL_SRI2C_R3         0x00000008  // I2C Module 3 Software Reset
#define SYSCTL_SRI2C_R2         0x00000004  // I2C Module 2 Software Reset
#define SYSCTL_SRI2C_R1         0x00000002  // I2C Module 1 Software Reset
#define SYSCTL_SRI2C_R0         0x00000001  // I2C Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRUSB register.
//
//*****************************************************************************
#define SYSCTL_SRUSB_R0         0x00000001  // USB Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SREPHY register.
//
//*****************************************************************************
#define SYSCTL_SREPHY_R0        0x00000001  // Ethernet PHY Module Software
// Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRCAN register.
//
//*****************************************************************************
#define SYSCTL_SRCAN_R1         0x00000002  // CAN Module 1 Software Reset
#define SYSCTL_SRCAN_R0         0x00000001  // CAN Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRADC register.
//
//*****************************************************************************
#define SYSCTL_SRADC_R1         0x00000002  // ADC Module 1 Software Reset
#define SYSCTL_SRADC_R0         0x00000001  // ADC Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRACMP register.
//
//*****************************************************************************
#define SYSCTL_SRACMP_R0        0x00000001  // Analog Comparator Module 0
// Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRPWM register.
//
//*****************************************************************************
#define SYSCTL_SRPWM_R0         0x00000001  // PWM Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRQEI register.
//
//*****************************************************************************
#define SYSCTL_SRQEI_R0         0x00000001  // QEI Module 0 Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SREEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_SREEPROM_R0      0x00000001  // EEPROM Module Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRCCM register.
//
//*****************************************************************************
#define SYSCTL_SRCCM_R0         0x00000001  // CRC and Cryptographic Modules
// Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SREMAC register.
//
//*****************************************************************************
#define SYSCTL_SREMAC_R0        0x00000001  // Ethernet Controller MAC Module 0
// Software Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCWD register.
//
//*****************************************************************************
#define SYSCTL_RCGCWD_R1        0x00000002  // Watchdog Timer 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCWD_R0        0x00000001  // Watchdog Timer 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCTIMER
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCTIMER_R7     0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R6     0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R5     0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R4     0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R3     0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R2     0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R1     0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Run Mode Clock Gating Control
#define SYSCTL_RCGCTIMER_R0     0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Run Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCGPIO
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCGPIO_R14     0x00004000  // GPIO Port Q Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R13     0x00002000  // GPIO Port P Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R12     0x00001000  // GPIO Port N Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R11     0x00000800  // GPIO Port M Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R10     0x00000400  // GPIO Port L Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R9      0x00000200  // GPIO Port K Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R8      0x00000100  // GPIO Port J Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R7      0x00000080  // GPIO Port H Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R6      0x00000040  // GPIO Port G Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R5      0x00000020  // GPIO Port F Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R4      0x00000010  // GPIO Port E Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R3      0x00000008  // GPIO Port D Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R2      0x00000004  // GPIO Port C Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R1      0x00000002  // GPIO Port B Run Mode Clock
// Gating Control
#define SYSCTL_RCGCGPIO_R0      0x00000001  // GPIO Port A Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCDMA register.
//
//*****************************************************************************
#define SYSCTL_RCGCDMA_R0       0x00000001  // uDMA Module Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCEPI register.
//
//*****************************************************************************
#define SYSCTL_RCGCEPI_R0       0x00000001  // EPI Module Run Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCHIB register.
//
//*****************************************************************************
#define SYSCTL_RCGCHIB_R0       0x00000001  // Hibernation Module Run Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCUART
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCUART_R7      0x00000080  // UART Module 7 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R6      0x00000040  // UART Module 6 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R5      0x00000020  // UART Module 5 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R4      0x00000010  // UART Module 4 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R3      0x00000008  // UART Module 3 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R2      0x00000004  // UART Module 2 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R1      0x00000002  // UART Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCUART_R0      0x00000001  // UART Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCSSI register.
//
//*****************************************************************************
#define SYSCTL_RCGCSSI_R3       0x00000008  // SSI Module 3 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCSSI_R2       0x00000004  // SSI Module 2 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCSSI_R1       0x00000002  // SSI Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCSSI_R0       0x00000001  // SSI Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCI2C register.
//
//*****************************************************************************
#define SYSCTL_RCGCI2C_R9       0x00000200  // I2C Module 9 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R8       0x00000100  // I2C Module 8 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R7       0x00000080  // I2C Module 7 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R6       0x00000040  // I2C Module 6 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R5       0x00000020  // I2C Module 5 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R4       0x00000010  // I2C Module 4 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R3       0x00000008  // I2C Module 3 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R2       0x00000004  // I2C Module 2 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R1       0x00000002  // I2C Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCI2C_R0       0x00000001  // I2C Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCUSB register.
//
//*****************************************************************************
#define SYSCTL_RCGCUSB_R0       0x00000001  // USB Module Run Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCEPHY
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCEPHY_R0      0x00000001  // Ethernet PHY Module Run Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCCAN register.
//
//*****************************************************************************
#define SYSCTL_RCGCCAN_R1       0x00000002  // CAN Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCCAN_R0       0x00000001  // CAN Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCADC register.
//
//*****************************************************************************
#define SYSCTL_RCGCADC_R1       0x00000002  // ADC Module 1 Run Mode Clock
// Gating Control
#define SYSCTL_RCGCADC_R0       0x00000001  // ADC Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCACMP
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCACMP_R0      0x00000001  // Analog Comparator Module 0 Run
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCPWM register.
//
//*****************************************************************************
#define SYSCTL_RCGCPWM_R0       0x00000001  // PWM Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCQEI register.
//
//*****************************************************************************
#define SYSCTL_RCGCQEI_R0       0x00000001  // QEI Module 0 Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCEEPROM_R0    0x00000001  // EEPROM Module Run Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCCCM register.
//
//*****************************************************************************
#define SYSCTL_RCGCCCM_R0       0x00000001  // CRC and Cryptographic Modules
// Run Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCEMAC
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCEMAC_R0      0x00000001  // Ethernet MAC Module 0 Run Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCWD register.
//
//*****************************************************************************
#define SYSCTL_SCGCWD_S1        0x00000002  // Watchdog Timer 1 Sleep Mode
// Clock Gating Control
#define SYSCTL_SCGCWD_S0        0x00000001  // Watchdog Timer 0 Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCTIMER
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCTIMER_S7     0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S6     0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S5     0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S4     0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S3     0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S2     0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S1     0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Sleep Mode Clock Gating
// Control
#define SYSCTL_SCGCTIMER_S0     0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCGPIO
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCGPIO_S14     0x00004000  // GPIO Port Q Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S13     0x00002000  // GPIO Port P Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S12     0x00001000  // GPIO Port N Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S11     0x00000800  // GPIO Port M Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S10     0x00000400  // GPIO Port L Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S9      0x00000200  // GPIO Port K Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S8      0x00000100  // GPIO Port J Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S7      0x00000080  // GPIO Port H Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S6      0x00000040  // GPIO Port G Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S5      0x00000020  // GPIO Port F Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S4      0x00000010  // GPIO Port E Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S3      0x00000008  // GPIO Port D Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S2      0x00000004  // GPIO Port C Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S1      0x00000002  // GPIO Port B Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCGPIO_S0      0x00000001  // GPIO Port A Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCDMA register.
//
//*****************************************************************************
#define SYSCTL_SCGCDMA_S0       0x00000001  // uDMA Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCEPI register.
//
//*****************************************************************************
#define SYSCTL_SCGCEPI_S0       0x00000001  // EPI Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCHIB register.
//
//*****************************************************************************
#define SYSCTL_SCGCHIB_S0       0x00000001  // Hibernation Module Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCUART
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCUART_S7      0x00000080  // UART Module 7 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S6      0x00000040  // UART Module 6 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S5      0x00000020  // UART Module 5 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S4      0x00000010  // UART Module 4 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S3      0x00000008  // UART Module 3 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S2      0x00000004  // UART Module 2 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S1      0x00000002  // UART Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCUART_S0      0x00000001  // UART Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCSSI register.
//
//*****************************************************************************
#define SYSCTL_SCGCSSI_S3       0x00000008  // SSI Module 3 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCSSI_S2       0x00000004  // SSI Module 2 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCSSI_S1       0x00000002  // SSI Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCSSI_S0       0x00000001  // SSI Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCI2C register.
//
//*****************************************************************************
#define SYSCTL_SCGCI2C_S9       0x00000200  // I2C Module 9 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S8       0x00000100  // I2C Module 8 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S7       0x00000080  // I2C Module 7 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S6       0x00000040  // I2C Module 6 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S5       0x00000020  // I2C Module 5 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S4       0x00000010  // I2C Module 4 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S3       0x00000008  // I2C Module 3 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S2       0x00000004  // I2C Module 2 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S1       0x00000002  // I2C Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCI2C_S0       0x00000001  // I2C Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCUSB register.
//
//*****************************************************************************
#define SYSCTL_SCGCUSB_S0       0x00000001  // USB Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCEPHY
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCEPHY_S0      0x00000001  // PHY Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCCAN register.
//
//*****************************************************************************
#define SYSCTL_SCGCCAN_S1       0x00000002  // CAN Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCCAN_S0       0x00000001  // CAN Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCADC register.
//
//*****************************************************************************
#define SYSCTL_SCGCADC_S1       0x00000002  // ADC Module 1 Sleep Mode Clock
// Gating Control
#define SYSCTL_SCGCADC_S0       0x00000001  // ADC Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCACMP
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCACMP_S0      0x00000001  // Analog Comparator Module 0 Sleep
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCPWM register.
//
//*****************************************************************************
#define SYSCTL_SCGCPWM_S0       0x00000001  // PWM Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCQEI register.
//
//*****************************************************************************
#define SYSCTL_SCGCQEI_S0       0x00000001  // QEI Module 0 Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCEEPROM_S0    0x00000001  // EEPROM Module Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCCCM register.
//
//*****************************************************************************
#define SYSCTL_SCGCCCM_S0       0x00000001  // CRC and Cryptographic Modules
// Sleep Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCEMAC
// register.
//
//*****************************************************************************
#define SYSCTL_SCGCEMAC_S0      0x00000001  // Ethernet MAC Module 0 Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCWD register.
//
//*****************************************************************************
#define SYSCTL_DCGCWD_D1        0x00000002  // Watchdog Timer 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCWD_D0        0x00000001  // Watchdog Timer 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCTIMER
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCTIMER_D7     0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D6     0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D5     0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D4     0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D3     0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D2     0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D1     0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Deep-Sleep Mode Clock Gating
// Control
#define SYSCTL_DCGCTIMER_D0     0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Deep-Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCGPIO
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCGPIO_D14     0x00004000  // GPIO Port Q Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D13     0x00002000  // GPIO Port P Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D12     0x00001000  // GPIO Port N Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D11     0x00000800  // GPIO Port M Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D10     0x00000400  // GPIO Port L Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D9      0x00000200  // GPIO Port K Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D8      0x00000100  // GPIO Port J Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D7      0x00000080  // GPIO Port H Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D6      0x00000040  // GPIO Port G Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D5      0x00000020  // GPIO Port F Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D4      0x00000010  // GPIO Port E Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D3      0x00000008  // GPIO Port D Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D2      0x00000004  // GPIO Port C Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D1      0x00000002  // GPIO Port B Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCGPIO_D0      0x00000001  // GPIO Port A Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCDMA register.
//
//*****************************************************************************
#define SYSCTL_DCGCDMA_D0       0x00000001  // uDMA Module Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCEPI register.
//
//*****************************************************************************
#define SYSCTL_DCGCEPI_D0       0x00000001  // EPI Module Deep-Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCHIB register.
//
//*****************************************************************************
#define SYSCTL_DCGCHIB_D0       0x00000001  // Hibernation Module Deep-Sleep
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCUART
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCUART_D7      0x00000080  // UART Module 7 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D6      0x00000040  // UART Module 6 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D5      0x00000020  // UART Module 5 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D4      0x00000010  // UART Module 4 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D3      0x00000008  // UART Module 3 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D2      0x00000004  // UART Module 2 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D1      0x00000002  // UART Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCUART_D0      0x00000001  // UART Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCSSI register.
//
//*****************************************************************************
#define SYSCTL_DCGCSSI_D3       0x00000008  // SSI Module 3 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCSSI_D2       0x00000004  // SSI Module 2 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCSSI_D1       0x00000002  // SSI Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCSSI_D0       0x00000001  // SSI Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCI2C register.
//
//*****************************************************************************
#define SYSCTL_DCGCI2C_D9       0x00000200  // I2C Module 9 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D8       0x00000100  // I2C Module 8 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D7       0x00000080  // I2C Module 7 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D6       0x00000040  // I2C Module 6 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D5       0x00000020  // I2C Module 5 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D4       0x00000010  // I2C Module 4 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D3       0x00000008  // I2C Module 3 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D2       0x00000004  // I2C Module 2 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D1       0x00000002  // I2C Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCI2C_D0       0x00000001  // I2C Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCUSB register.
//
//*****************************************************************************
#define SYSCTL_DCGCUSB_D0       0x00000001  // USB Module Deep-Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCEPHY
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCEPHY_D0      0x00000001  // PHY Module Deep-Sleep Mode Clock
// Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCCAN register.
//
//*****************************************************************************
#define SYSCTL_DCGCCAN_D1       0x00000002  // CAN Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCCAN_D0       0x00000001  // CAN Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCADC register.
//
//*****************************************************************************
#define SYSCTL_DCGCADC_D1       0x00000002  // ADC Module 1 Deep-Sleep Mode
// Clock Gating Control
#define SYSCTL_DCGCADC_D0       0x00000001  // ADC Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCACMP
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCACMP_D0      0x00000001  // Analog Comparator Module 0
// Deep-Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCPWM register.
//
//*****************************************************************************
#define SYSCTL_DCGCPWM_D0       0x00000001  // PWM Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCQEI register.
//
//*****************************************************************************
#define SYSCTL_DCGCQEI_D0       0x00000001  // QEI Module 0 Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCEEPROM_D0    0x00000001  // EEPROM Module Deep-Sleep Mode
// Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCCCM register.
//
//*****************************************************************************
#define SYSCTL_DCGCCCM_D0       0x00000001  // CRC and Cryptographic Modules
// Deep-Sleep Mode Clock Gating
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGCEMAC
// register.
//
//*****************************************************************************
#define SYSCTL_DCGCEMAC_D0      0x00000001  // Ethernet MAC Module 0 Deep-Sleep
// Mode Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCWD register.
//
//*****************************************************************************
#define SYSCTL_PCWD_P1          0x00000002  // Watchdog Timer 1 Power Control
#define SYSCTL_PCWD_P0          0x00000001  // Watchdog Timer 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCTIMER register.
//
//*****************************************************************************
#define SYSCTL_PCTIMER_P7       0x00000080  // General-Purpose Timer 7 Power
// Control
#define SYSCTL_PCTIMER_P6       0x00000040  // General-Purpose Timer 6 Power
// Control
#define SYSCTL_PCTIMER_P5       0x00000020  // General-Purpose Timer 5 Power
// Control
#define SYSCTL_PCTIMER_P4       0x00000010  // General-Purpose Timer 4 Power
// Control
#define SYSCTL_PCTIMER_P3       0x00000008  // General-Purpose Timer 3 Power
// Control
#define SYSCTL_PCTIMER_P2       0x00000004  // General-Purpose Timer 2 Power
// Control
#define SYSCTL_PCTIMER_P1       0x00000002  // General-Purpose Timer 1 Power
// Control
#define SYSCTL_PCTIMER_P0       0x00000001  // General-Purpose Timer 0 Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCGPIO register.
//
//*****************************************************************************
#define SYSCTL_PCGPIO_P14       0x00004000  // GPIO Port Q Power Control
#define SYSCTL_PCGPIO_P13       0x00002000  // GPIO Port P Power Control
#define SYSCTL_PCGPIO_P12       0x00001000  // GPIO Port N Power Control
#define SYSCTL_PCGPIO_P11       0x00000800  // GPIO Port M Power Control
#define SYSCTL_PCGPIO_P10       0x00000400  // GPIO Port L Power Control
#define SYSCTL_PCGPIO_P9        0x00000200  // GPIO Port K Power Control
#define SYSCTL_PCGPIO_P8        0x00000100  // GPIO Port J Power Control
#define SYSCTL_PCGPIO_P7        0x00000080  // GPIO Port H Power Control
#define SYSCTL_PCGPIO_P6        0x00000040  // GPIO Port G Power Control
#define SYSCTL_PCGPIO_P5        0x00000020  // GPIO Port F Power Control
#define SYSCTL_PCGPIO_P4        0x00000010  // GPIO Port E Power Control
#define SYSCTL_PCGPIO_P3        0x00000008  // GPIO Port D Power Control
#define SYSCTL_PCGPIO_P2        0x00000004  // GPIO Port C Power Control
#define SYSCTL_PCGPIO_P1        0x00000002  // GPIO Port B Power Control
#define SYSCTL_PCGPIO_P0        0x00000001  // GPIO Port A Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCDMA register.
//
//*****************************************************************************
#define SYSCTL_PCDMA_P0         0x00000001  // uDMA Module Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCEPI register.
//
//*****************************************************************************
#define SYSCTL_PCEPI_P0         0x00000001  // EPI Module Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCHIB register.
//
//*****************************************************************************
#define SYSCTL_PCHIB_P0         0x00000001  // Hibernation Module Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCUART register.
//
//*****************************************************************************
#define SYSCTL_PCUART_P7        0x00000080  // UART Module 7 Power Control
#define SYSCTL_PCUART_P6        0x00000040  // UART Module 6 Power Control
#define SYSCTL_PCUART_P5        0x00000020  // UART Module 5 Power Control
#define SYSCTL_PCUART_P4        0x00000010  // UART Module 4 Power Control
#define SYSCTL_PCUART_P3        0x00000008  // UART Module 3 Power Control
#define SYSCTL_PCUART_P2        0x00000004  // UART Module 2 Power Control
#define SYSCTL_PCUART_P1        0x00000002  // UART Module 1 Power Control
#define SYSCTL_PCUART_P0        0x00000001  // UART Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCSSI register.
//
//*****************************************************************************
#define SYSCTL_PCSSI_P3         0x00000008  // SSI Module 3 Power Control
#define SYSCTL_PCSSI_P2         0x00000004  // SSI Module 2 Power Control
#define SYSCTL_PCSSI_P1         0x00000002  // SSI Module 1 Power Control
#define SYSCTL_PCSSI_P0         0x00000001  // SSI Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCI2C register.
//
//*****************************************************************************
#define SYSCTL_PCI2C_P9         0x00000200  // I2C Module 9 Power Control
#define SYSCTL_PCI2C_P8         0x00000100  // I2C Module 8 Power Control
#define SYSCTL_PCI2C_P7         0x00000080  // I2C Module 7 Power Control
#define SYSCTL_PCI2C_P6         0x00000040  // I2C Module 6 Power Control
#define SYSCTL_PCI2C_P5         0x00000020  // I2C Module 5 Power Control
#define SYSCTL_PCI2C_P4         0x00000010  // I2C Module 4 Power Control
#define SYSCTL_PCI2C_P3         0x00000008  // I2C Module 3 Power Control
#define SYSCTL_PCI2C_P2         0x00000004  // I2C Module 2 Power Control
#define SYSCTL_PCI2C_P1         0x00000002  // I2C Module 1 Power Control
#define SYSCTL_PCI2C_P0         0x00000001  // I2C Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCUSB register.
//
//*****************************************************************************
#define SYSCTL_PCUSB_P0         0x00000001  // USB Module Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCEPHY register.
//
//*****************************************************************************
#define SYSCTL_PCEPHY_P0        0x00000001  // Ethernet PHY Module Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCCAN register.
//
//*****************************************************************************
#define SYSCTL_PCCAN_P1         0x00000002  // CAN Module 1 Power Control
#define SYSCTL_PCCAN_P0         0x00000001  // CAN Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCADC register.
//
//*****************************************************************************
#define SYSCTL_PCADC_P1         0x00000002  // ADC Module 1 Power Control
#define SYSCTL_PCADC_P0         0x00000001  // ADC Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCACMP register.
//
//*****************************************************************************
#define SYSCTL_PCACMP_P0        0x00000001  // Analog Comparator Module 0 Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCPWM register.
//
//*****************************************************************************
#define SYSCTL_PCPWM_P0         0x00000001  // PWM Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCQEI register.
//
//*****************************************************************************
#define SYSCTL_PCQEI_P0         0x00000001  // QEI Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCEEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_PCEEPROM_P0      0x00000001  // EEPROM Module 0 Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCCCM register.
//
//*****************************************************************************
#define SYSCTL_PCCCM_P0         0x00000001  // CRC and Cryptographic Modules
// Power Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PCEMAC register.
//
//*****************************************************************************
#define SYSCTL_PCEMAC_P0        0x00000001  // Ethernet MAC Module 0 Power
// Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRWD register.
//
//*****************************************************************************
#define SYSCTL_PRWD_R1          0x00000002  // Watchdog Timer 1 Peripheral
// Ready
#define SYSCTL_PRWD_R0          0x00000001  // Watchdog Timer 0 Peripheral
// Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRTIMER register.
//
//*****************************************************************************
#define SYSCTL_PRTIMER_R7       0x00000080  // 16/32-Bit General-Purpose Timer
// 7 Peripheral Ready
#define SYSCTL_PRTIMER_R6       0x00000040  // 16/32-Bit General-Purpose Timer
// 6 Peripheral Ready
#define SYSCTL_PRTIMER_R5       0x00000020  // 16/32-Bit General-Purpose Timer
// 5 Peripheral Ready
#define SYSCTL_PRTIMER_R4       0x00000010  // 16/32-Bit General-Purpose Timer
// 4 Peripheral Ready
#define SYSCTL_PRTIMER_R3       0x00000008  // 16/32-Bit General-Purpose Timer
// 3 Peripheral Ready
#define SYSCTL_PRTIMER_R2       0x00000004  // 16/32-Bit General-Purpose Timer
// 2 Peripheral Ready
#define SYSCTL_PRTIMER_R1       0x00000002  // 16/32-Bit General-Purpose Timer
// 1 Peripheral Ready
#define SYSCTL_PRTIMER_R0       0x00000001  // 16/32-Bit General-Purpose Timer
// 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRGPIO register.
//
//*****************************************************************************
#define SYSCTL_PRGPIO_R14       0x00004000  // GPIO Port Q Peripheral Ready
#define SYSCTL_PRGPIO_R13       0x00002000  // GPIO Port P Peripheral Ready
#define SYSCTL_PRGPIO_R12       0x00001000  // GPIO Port N Peripheral Ready
#define SYSCTL_PRGPIO_R11       0x00000800  // GPIO Port M Peripheral Ready
#define SYSCTL_PRGPIO_R10       0x00000400  // GPIO Port L Peripheral Ready
#define SYSCTL_PRGPIO_R9        0x00000200  // GPIO Port K Peripheral Ready
#define SYSCTL_PRGPIO_R8        0x00000100  // GPIO Port J Peripheral Ready
#define SYSCTL_PRGPIO_R7        0x00000080  // GPIO Port H Peripheral Ready
#define SYSCTL_PRGPIO_R6        0x00000040  // GPIO Port G Peripheral Ready
#define SYSCTL_PRGPIO_R5        0x00000020  // GPIO Port F Peripheral Ready
#define SYSCTL_PRGPIO_R4        0x00000010  // GPIO Port E Peripheral Ready
#define SYSCTL_PRGPIO_R3        0x00000008  // GPIO Port D Peripheral Ready
#define SYSCTL_PRGPIO_R2        0x00000004  // GPIO Port C Peripheral Ready
#define SYSCTL_PRGPIO_R1        0x00000002  // GPIO Port B Peripheral Ready
#define SYSCTL_PRGPIO_R0        0x00000001  // GPIO Port A Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRDMA register.
//
//*****************************************************************************
#define SYSCTL_PRDMA_R0         0x00000001  // uDMA Module Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PREPI register.
//
//*****************************************************************************
#define SYSCTL_PREPI_R0         0x00000001  // EPI Module Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRHIB register.
//
//*****************************************************************************
#define SYSCTL_PRHIB_R0         0x00000001  // Hibernation Module Peripheral
// Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRUART register.
//
//*****************************************************************************
#define SYSCTL_PRUART_R7        0x00000080  // UART Module 7 Peripheral Ready
#define SYSCTL_PRUART_R6        0x00000040  // UART Module 6 Peripheral Ready
#define SYSCTL_PRUART_R5        0x00000020  // UART Module 5 Peripheral Ready
#define SYSCTL_PRUART_R4        0x00000010  // UART Module 4 Peripheral Ready
#define SYSCTL_PRUART_R3        0x00000008  // UART Module 3 Peripheral Ready
#define SYSCTL_PRUART_R2        0x00000004  // UART Module 2 Peripheral Ready
#define SYSCTL_PRUART_R1        0x00000002  // UART Module 1 Peripheral Ready
#define SYSCTL_PRUART_R0        0x00000001  // UART Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRSSI register.
//
//*****************************************************************************
#define SYSCTL_PRSSI_R3         0x00000008  // SSI Module 3 Peripheral Ready
#define SYSCTL_PRSSI_R2         0x00000004  // SSI Module 2 Peripheral Ready
#define SYSCTL_PRSSI_R1         0x00000002  // SSI Module 1 Peripheral Ready
#define SYSCTL_PRSSI_R0         0x00000001  // SSI Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRI2C register.
//
//*****************************************************************************
#define SYSCTL_PRI2C_R9         0x00000200  // I2C Module 9 Peripheral Ready
#define SYSCTL_PRI2C_R8         0x00000100  // I2C Module 8 Peripheral Ready
#define SYSCTL_PRI2C_R7         0x00000080  // I2C Module 7 Peripheral Ready
#define SYSCTL_PRI2C_R6         0x00000040  // I2C Module 6 Peripheral Ready
#define SYSCTL_PRI2C_R5         0x00000020  // I2C Module 5 Peripheral Ready
#define SYSCTL_PRI2C_R4         0x00000010  // I2C Module 4 Peripheral Ready
#define SYSCTL_PRI2C_R3         0x00000008  // I2C Module 3 Peripheral Ready
#define SYSCTL_PRI2C_R2         0x00000004  // I2C Module 2 Peripheral Ready
#define SYSCTL_PRI2C_R1         0x00000002  // I2C Module 1 Peripheral Ready
#define SYSCTL_PRI2C_R0         0x00000001  // I2C Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRUSB register.
//
//*****************************************************************************
#define SYSCTL_PRUSB_R0         0x00000001  // USB Module Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PREPHY register.
//
//*****************************************************************************
#define SYSCTL_PREPHY_R0        0x00000001  // Ethernet PHY Module Peripheral
// Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRCAN register.
//
//*****************************************************************************
#define SYSCTL_PRCAN_R1         0x00000002  // CAN Module 1 Peripheral Ready
#define SYSCTL_PRCAN_R0         0x00000001  // CAN Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRADC register.
//
//*****************************************************************************
#define SYSCTL_PRADC_R1         0x00000002  // ADC Module 1 Peripheral Ready
#define SYSCTL_PRADC_R0         0x00000001  // ADC Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRACMP register.
//
//*****************************************************************************
#define SYSCTL_PRACMP_R0        0x00000001  // Analog Comparator Module 0
// Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRPWM register.
//
//*****************************************************************************
#define SYSCTL_PRPWM_R0         0x00000001  // PWM Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRQEI register.
//
//*****************************************************************************
#define SYSCTL_PRQEI_R0         0x00000001  // QEI Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PREEPROM
// register.
//
//*****************************************************************************
#define SYSCTL_PREEPROM_R0      0x00000001  // EEPROM Module Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRCCM register.
//
//*****************************************************************************
#define SYSCTL_PRCCM_R0         0x00000001  // CRC and Cryptographic Modules
// Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PREMAC register.
//
//*****************************************************************************
#define SYSCTL_PREMAC_R0        0x00000001  // Ethernet MAC Module 0 Peripheral
// Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_STAT register.
//
//*****************************************************************************
#define UDMA_STAT_DMACHANS_M    0x001F0000  // Available uDMA Channels Minus 1
#define UDMA_STAT_STATE_M       0x000000F0  // Control State Machine Status
#define UDMA_STAT_STATE_IDLE    0x00000000  // Idle
#define UDMA_STAT_STATE_RD_CTRL 0x00000010  // Reading channel controller data
#define UDMA_STAT_STATE_RD_SRCENDP                                            \
                                0x00000020  // Reading source end pointer
#define UDMA_STAT_STATE_RD_DSTENDP                                            \
                                0x00000030  // Reading destination end pointer
#define UDMA_STAT_STATE_RD_SRCDAT                                             \
                                0x00000040  // Reading source data
#define UDMA_STAT_STATE_WR_DSTDAT                                             \
                                0x00000050  // Writing destination data
#define UDMA_STAT_STATE_WAIT    0x00000060  // Waiting for uDMA request to
// clear
#define UDMA_STAT_STATE_WR_CTRL 0x00000070  // Writing channel controller data
#define UDMA_STAT_STATE_STALL   0x00000080  // Stalled
#define UDMA_STAT_STATE_DONE    0x00000090  // Done
#define UDMA_STAT_STATE_UNDEF   0x000000A0  // Undefined
#define UDMA_STAT_MASTEN        0x00000001  // Master Enable Status
#define UDMA_STAT_DMACHANS_S    16

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_CFG register.
//
//*****************************************************************************
#define UDMA_CFG_MASTEN         0x00000001  // Controller Master Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_CTLBASE register.
//
//*****************************************************************************
#define UDMA_CTLBASE_ADDR_M     0xFFFFFC00  // Channel Control Base Address
#define UDMA_CTLBASE_ADDR_S     10

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_ALTBASE register.
//
//*****************************************************************************
#define UDMA_ALTBASE_ADDR_M     0xFFFFFFFF  // Alternate Channel Address
// Pointer
#define UDMA_ALTBASE_ADDR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_WAITSTAT register.
//
//*****************************************************************************
#define UDMA_WAITSTAT_WAITREQ_M 0xFFFFFFFF  // Channel [n] Wait Status

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_SWREQ register.
//
//*****************************************************************************
#define UDMA_SWREQ_M            0xFFFFFFFF  // Channel [n] Software Request

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_USEBURSTSET
// register.
//
//*****************************************************************************
#define UDMA_USEBURSTSET_SET_M  0xFFFFFFFF  // Channel [n] Useburst Set

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_USEBURSTCLR
// register.
//
//*****************************************************************************
#define UDMA_USEBURSTCLR_CLR_M  0xFFFFFFFF  // Channel [n] Useburst Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_REQMASKSET
// register.
//
//*****************************************************************************
#define UDMA_REQMASKSET_SET_M   0xFFFFFFFF  // Channel [n] Request Mask Set

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_REQMASKCLR
// register.
//
//*****************************************************************************
#define UDMA_REQMASKCLR_CLR_M   0xFFFFFFFF  // Channel [n] Request Mask Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_ENASET register.
//
//*****************************************************************************
#define UDMA_ENASET_SET_M       0xFFFFFFFF  // Channel [n] Enable Set

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_ENACLR register.
//
//*****************************************************************************
#define UDMA_ENACLR_CLR_M       0xFFFFFFFF  // Clear Channel [n] Enable Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_ALTSET register.
//
//*****************************************************************************
#define UDMA_ALTSET_SET_M       0xFFFFFFFF  // Channel [n] Alternate Set

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_ALTCLR register.
//
//*****************************************************************************
#define UDMA_ALTCLR_CLR_M       0xFFFFFFFF  // Channel [n] Alternate Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_PRIOSET register.
//
//*****************************************************************************
#define UDMA_PRIOSET_SET_M      0xFFFFFFFF  // Channel [n] Priority Set

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_PRIOCLR register.
//
//*****************************************************************************
#define UDMA_PRIOCLR_CLR_M      0xFFFFFFFF  // Channel [n] Priority Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_ERRCLR register.
//
//*****************************************************************************
#define UDMA_ERRCLR_ERRCLR      0x00000001  // uDMA Bus Error Status

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_CHASGN register.
//
//*****************************************************************************
#define UDMA_CHASGN_M           0xFFFFFFFF  // Channel [n] Assignment Select
#define UDMA_CHASGN_PRIMARY     0x00000000  // Use the primary channel
// assignment
#define UDMA_CHASGN_SECONDARY   0x00000001  // Use the secondary channel
// assignment

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_CHMAP0 register.
//
//*****************************************************************************
#define UDMA_CHMAP0_CH7SEL_M    0xF0000000  // uDMA Channel 7 Source Select
#define UDMA_CHMAP0_CH6SEL_M    0x0F000000  // uDMA Channel 6 Source Select
#define UDMA_CHMAP0_CH5SEL_M    0x00F00000  // uDMA Channel 5 Source Select
#define UDMA_CHMAP0_CH4SEL_M    0x000F0000  // uDMA Channel 4 Source Select
#define UDMA_CHMAP0_CH3SEL_M    0x0000F000  // uDMA Channel 3 Source Select
#define UDMA_CHMAP0_CH2SEL_M    0x00000F00  // uDMA Channel 2 Source Select
#define UDMA_CHMAP0_CH1SEL_M    0x000000F0  // uDMA Channel 1 Source Select
#define UDMA_CHMAP0_CH0SEL_M    0x0000000F  // uDMA Channel 0 Source Select
#define UDMA_CHMAP0_CH7SEL_S    28
#define UDMA_CHMAP0_CH6SEL_S    24
#define UDMA_CHMAP0_CH5SEL_S    20
#define UDMA_CHMAP0_CH4SEL_S    16
#define UDMA_CHMAP0_CH3SEL_S    12
#define UDMA_CHMAP0_CH2SEL_S    8
#define UDMA_CHMAP0_CH1SEL_S    4
#define UDMA_CHMAP0_CH0SEL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_CHMAP1 register.
//
//*****************************************************************************
#define UDMA_CHMAP1_CH15SEL_M   0xF0000000  // uDMA Channel 15 Source Select
#define UDMA_CHMAP1_CH14SEL_M   0x0F000000  // uDMA Channel 14 Source Select
#define UDMA_CHMAP1_CH13SEL_M   0x00F00000  // uDMA Channel 13 Source Select
#define UDMA_CHMAP1_CH12SEL_M   0x000F0000  // uDMA Channel 12 Source Select
#define UDMA_CHMAP1_CH11SEL_M   0x0000F000  // uDMA Channel 11 Source Select
#define UDMA_CHMAP1_CH10SEL_M   0x00000F00  // uDMA Channel 10 Source Select
#define UDMA_CHMAP1_CH9SEL_M    0x000000F0  // uDMA Channel 9 Source Select
#define UDMA_CHMAP1_CH8SEL_M    0x0000000F  // uDMA Channel 8 Source Select
#define UDMA_CHMAP1_CH15SEL_S   28
#define UDMA_CHMAP1_CH14SEL_S   24
#define UDMA_CHMAP1_CH13SEL_S   20
#define UDMA_CHMAP1_CH12SEL_S   16
#define UDMA_CHMAP1_CH11SEL_S   12
#define UDMA_CHMAP1_CH10SEL_S   8
#define UDMA_CHMAP1_CH9SEL_S    4
#define UDMA_CHMAP1_CH8SEL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_CHMAP2 register.
//
//*****************************************************************************
#define UDMA_CHMAP2_CH23SEL_M   0xF0000000  // uDMA Channel 23 Source Select
#define UDMA_CHMAP2_CH22SEL_M   0x0F000000  // uDMA Channel 22 Source Select
#define UDMA_CHMAP2_CH21SEL_M   0x00F00000  // uDMA Channel 21 Source Select
#define UDMA_CHMAP2_CH20SEL_M   0x000F0000  // uDMA Channel 20 Source Select
#define UDMA_CHMAP2_CH19SEL_M   0x0000F000  // uDMA Channel 19 Source Select
#define UDMA_CHMAP2_CH18SEL_M   0x00000F00  // uDMA Channel 18 Source Select
#define UDMA_CHMAP2_CH17SEL_M   0x000000F0  // uDMA Channel 17 Source Select
#define UDMA_CHMAP2_CH16SEL_M   0x0000000F  // uDMA Channel 16 Source Select
#define UDMA_CHMAP2_CH23SEL_S   28
#define UDMA_CHMAP2_CH22SEL_S   24
#define UDMA_CHMAP2_CH21SEL_S   20
#define UDMA_CHMAP2_CH20SEL_S   16
#define UDMA_CHMAP2_CH19SEL_S   12
#define UDMA_CHMAP2_CH18SEL_S   8
#define UDMA_CHMAP2_CH17SEL_S   4
#define UDMA_CHMAP2_CH16SEL_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_CHMAP3 register.
//
//*****************************************************************************
#define UDMA_CHMAP3_CH31SEL_M   0xF0000000  // uDMA Channel 31 Source Select
#define UDMA_CHMAP3_CH30SEL_M   0x0F000000  // uDMA Channel 30 Source Select
#define UDMA_CHMAP3_CH29SEL_M   0x00F00000  // uDMA Channel 29 Source Select
#define UDMA_CHMAP3_CH28SEL_M   0x000F0000  // uDMA Channel 28 Source Select
#define UDMA_CHMAP3_CH27SEL_M   0x0000F000  // uDMA Channel 27 Source Select
#define UDMA_CHMAP3_CH26SEL_M   0x00000F00  // uDMA Channel 26 Source Select
#define UDMA_CHMAP3_CH25SEL_M   0x000000F0  // uDMA Channel 25 Source Select
#define UDMA_CHMAP3_CH24SEL_M   0x0000000F  // uDMA Channel 24 Source Select
#define UDMA_CHMAP3_CH31SEL_S   28
#define UDMA_CHMAP3_CH30SEL_S   24
#define UDMA_CHMAP3_CH29SEL_S   20
#define UDMA_CHMAP3_CH28SEL_S   16
#define UDMA_CHMAP3_CH27SEL_S   12
#define UDMA_CHMAP3_CH26SEL_S   8
#define UDMA_CHMAP3_CH25SEL_S   4
#define UDMA_CHMAP3_CH24SEL_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_O_SRCENDP register.
//
//*****************************************************************************
#define UDMA_SRCENDP_ADDR_M     0xFFFFFFFF  // Source Address End Pointer
#define UDMA_SRCENDP_ADDR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_O_DSTENDP register.
//
//*****************************************************************************
#define UDMA_DSTENDP_ADDR_M     0xFFFFFFFF  // Destination Address End Pointer
#define UDMA_DSTENDP_ADDR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the UDMA_O_CHCTL register.
//
//*****************************************************************************
#define UDMA_CHCTL_DSTINC_M     0xC0000000  // Destination Address Increment
#define UDMA_CHCTL_DSTINC_8     0x00000000  // Byte
#define UDMA_CHCTL_DSTINC_16    0x40000000  // Half-word
#define UDMA_CHCTL_DSTINC_32    0x80000000  // Word
#define UDMA_CHCTL_DSTINC_NONE  0xC0000000  // No increment
#define UDMA_CHCTL_DSTSIZE_M    0x30000000  // Destination Data Size
#define UDMA_CHCTL_DSTSIZE_8    0x00000000  // Byte
#define UDMA_CHCTL_DSTSIZE_16   0x10000000  // Half-word
#define UDMA_CHCTL_DSTSIZE_32   0x20000000  // Word
#define UDMA_CHCTL_SRCINC_M     0x0C000000  // Source Address Increment
#define UDMA_CHCTL_SRCINC_8     0x00000000  // Byte
#define UDMA_CHCTL_SRCINC_16    0x04000000  // Half-word
#define UDMA_CHCTL_SRCINC_32    0x08000000  // Word
#define UDMA_CHCTL_SRCINC_NONE  0x0C000000  // No increment
#define UDMA_CHCTL_SRCSIZE_M    0x03000000  // Source Data Size
#define UDMA_CHCTL_SRCSIZE_8    0x00000000  // Byte
#define UDMA_CHCTL_SRCSIZE_16   0x01000000  // Half-word
#define UDMA_CHCTL_SRCSIZE_32   0x02000000  // Word
#define UDMA_CHCTL_DSTPROT0     0x00200000  // Destination Privilege Access
#define UDMA_CHCTL_SRCPROT0     0x00040000  // Source Privilege Access
#define UDMA_CHCTL_ARBSIZE_M    0x0003C000  // Arbitration Size
#define UDMA_CHCTL_ARBSIZE_1    0x00000000  // 1 Transfer
#define UDMA_CHCTL_ARBSIZE_2    0x00004000  // 2 Transfers
#define UDMA_CHCTL_ARBSIZE_4    0x00008000  // 4 Transfers
#define UDMA_CHCTL_ARBSIZE_8    0x0000C000  // 8 Transfers
#define UDMA_CHCTL_ARBSIZE_16   0x00010000  // 16 Transfers
#define UDMA_CHCTL_ARBSIZE_32   0x00014000  // 32 Transfers
#define UDMA_CHCTL_ARBSIZE_64   0x00018000  // 64 Transfers
#define UDMA_CHCTL_ARBSIZE_128  0x0001C000  // 128 Transfers
#define UDMA_CHCTL_ARBSIZE_256  0x00020000  // 256 Transfers
#define UDMA_CHCTL_ARBSIZE_512  0x00024000  // 512 Transfers
#define UDMA_CHCTL_ARBSIZE_1024 0x00028000  // 1024 Transfers
#define UDMA_CHCTL_XFERSIZE_M   0x00003FF0  // Transfer Size (minus 1)
#define UDMA_CHCTL_NXTUSEBURST  0x00000008  // Next Useburst
#define UDMA_CHCTL_XFERMODE_M   0x00000007  // uDMA Transfer Mode
#define UDMA_CHCTL_XFERMODE_STOP                                              \
                                0x00000000  // Stop
#define UDMA_CHCTL_XFERMODE_BASIC                                             \
                                0x00000001  // Basic
#define UDMA_CHCTL_XFERMODE_AUTO                                              \
                                0x00000002  // Auto-Request
#define UDMA_CHCTL_XFERMODE_PINGPONG                                          \
                                0x00000003  // Ping-Pong
#define UDMA_CHCTL_XFERMODE_MEM_SG                                            \
                                0x00000004  // Memory Scatter-Gather
#define UDMA_CHCTL_XFERMODE_MEM_SGA                                           \
                                0x00000005  // Alternate Memory Scatter-Gather
#define UDMA_CHCTL_XFERMODE_PER_SG                                            \
                                0x00000006  // Peripheral Scatter-Gather
#define UDMA_CHCTL_XFERMODE_PER_SGA                                           \
                                0x00000007  // Alternate Peripheral
// Scatter-Gather
#define UDMA_CHCTL_XFERSIZE_S   4

//*****************************************************************************
//
// The following are defines for the bit fields in the CCM_CGREQ
// register.
//
//*****************************************************************************
#define CCM_CGREQ_DESCFG     0x00000004  // DES Clock Gating Request
#define CCM_CGREQ_AESCFG     0x00000002  // AES Clock Gating Request
#define CCM_CGREQ_SHACFG     0x00000001  // SHA/MD5 Clock Gating Request

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC_CTRL register.
//
//*****************************************************************************
#define CRC_CTRL_INIT_M      0x00006000  // CRC Initialization
#define CRC_CTRL_INIT_SEED   0x00000000  // Use the CRCSEED register context
// as the starting value
#define CRC_CTRL_INIT_0      0x00004000  // Initialize to all '0s'
#define CRC_CTRL_INIT_1      0x00006000  // Initialize to all '1s'
#define CRC_CTRL_SIZE        0x00001000  // Input Data Size
#define CRC_CTRL_RESINV      0x00000200  // Result Inverse Enable
#define CRC_CTRL_OBR         0x00000100  // Output Reverse Enable
#define CRC_CTRL_BR          0x00000080  // Bit reverse enable
#define CRC_CTRL_ENDIAN_M    0x00000030  // Endian Control
#define CRC_CTRL_ENDIAN_SBHW 0x00000000  // Configuration unchanged. (B3,
// B2, B1, B0)
#define CRC_CTRL_ENDIAN_SHW  0x00000010  // Bytes are swapped in half-words
// but half-words are not swapped
// (B2, B3, B0, B1)
#define CRC_CTRL_ENDIAN_SHWNB                                              \
                                0x00000020  // Half-words are swapped but bytes
// are not swapped in half-word.
// (B1, B0, B3, B2)
#define CRC_CTRL_ENDIAN_SBSW 0x00000030  // Bytes are swapped in half-words
// and half-words are swapped. (B0,
// B1, B2, B3)
#define CRC_CTRL_TYPE_M      0x0000000F  // Operation Type
#define CRC_CTRL_TYPE_P8055  0x00000000  // Polynomial 0x8005
#define CRC_CTRL_TYPE_P1021  0x00000001  // Polynomial 0x1021
#define CRC_CTRL_TYPE_P4C11DB7                                             \
                                0x00000002  // Polynomial 0x4C11DB7
#define CRC_CTRL_TYPE_P1EDC6F41                                            \
                                0x00000003  // Polynomial 0x1EDC6F41
#define CRC_CTRL_TYPE_TCPCHKSUM                                            \
                                0x00000008  // TCP checksum

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC_SEED register.
//
//*****************************************************************************
#define CRC_SEED_SEED_M      0xFFFFFFFF  // SEED/Context Value
#define CRC_SEED_SEED_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC_DIN register.
//
//*****************************************************************************
#define CRC_DIN_DATAIN_M     0xFFFFFFFF  // Data Input
#define CRC_DIN_DATAIN_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC_RSLTPP
// register.
//
//*****************************************************************************
#define CRC_RSLTPP_RSLTPP_M  0xFFFFFFFF  // Post Processing Result
#define CRC_RSLTPP_RSLTPP_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_ODIGEST_A
// register.
//
//*****************************************************************************
#define SHAMD5_ODIGEST_A_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_ODIGEST_A_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_ODIGEST_B
// register.
//
//*****************************************************************************
#define SHAMD5_ODIGEST_B_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_ODIGEST_B_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_ODIGEST_C
// register.
//
//*****************************************************************************
#define SHAMD5_ODIGEST_C_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_ODIGEST_C_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_ODIGEST_D
// register.
//
//*****************************************************************************
#define SHAMD5_ODIGEST_D_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_ODIGEST_D_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_ODIGEST_E
// register.
//
//*****************************************************************************
#define SHAMD5_ODIGEST_E_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_ODIGEST_E_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_ODIGEST_F
// register.
//
//*****************************************************************************
#define SHAMD5_ODIGEST_F_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_ODIGEST_F_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_ODIGEST_G
// register.
//
//*****************************************************************************
#define SHAMD5_ODIGEST_G_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_ODIGEST_G_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_ODIGEST_H
// register.
//
//*****************************************************************************
#define SHAMD5_ODIGEST_H_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_ODIGEST_H_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IDIGEST_A
// register.
//
//*****************************************************************************
#define SHAMD5_IDIGEST_A_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_IDIGEST_A_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IDIGEST_B
// register.
//
//*****************************************************************************
#define SHAMD5_IDIGEST_B_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_IDIGEST_B_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IDIGEST_C
// register.
//
//*****************************************************************************
#define SHAMD5_IDIGEST_C_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_IDIGEST_C_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IDIGEST_D
// register.
//
//*****************************************************************************
#define SHAMD5_IDIGEST_D_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_IDIGEST_D_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IDIGEST_E
// register.
//
//*****************************************************************************
#define SHAMD5_IDIGEST_E_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_IDIGEST_E_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IDIGEST_F
// register.
//
//*****************************************************************************
#define SHAMD5_IDIGEST_F_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_IDIGEST_F_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IDIGEST_G
// register.
//
//*****************************************************************************
#define SHAMD5_IDIGEST_G_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_IDIGEST_G_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IDIGEST_H
// register.
//
//*****************************************************************************
#define SHAMD5_IDIGEST_H_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_IDIGEST_H_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DIGEST_COUNT
// register.
//
//*****************************************************************************
#define SHAMD5_DIGEST_COUNT_M   0xFFFFFFFF  // Digest Count
#define SHAMD5_DIGEST_COUNT_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_MODE register.
//
//*****************************************************************************
#define SHAMD5_MODE_HMAC_OUTER_HASH                                           \
                                0x00000080  // HMAC Outer Hash Processing
// Enable
#define SHAMD5_MODE_HMAC_KEY_PROC                                             \
                                0x00000020  // HMAC Key Processing Enable
#define SHAMD5_MODE_CLOSE_HASH  0x00000010  // Performs the padding, the
// Hash/HMAC will be 'closed' at
// the end of the block, as per
// MD5/SHA-1/SHA-2 specification
#define SHAMD5_MODE_ALGO_CONSTANT                                             \
                                0x00000008  // The initial digest register will
// be overwritten with the
// algorithm constants for the
// selected algorithm when hashing
// and the initial digest count
// register will be reset to 0
#define SHAMD5_MODE_ALGO_M      0x00000007  // Hash Algorithm
#define SHAMD5_MODE_ALGO_MD5    0x00000000  // MD5
#define SHAMD5_MODE_ALGO_SHA1   0x00000002  // SHA-1
#define SHAMD5_MODE_ALGO_SHA224 0x00000004  // SHA-224
#define SHAMD5_MODE_ALGO_SHA256 0x00000006  // SHA-256

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_LENGTH
// register.
//
//*****************************************************************************
#define SHAMD5_LENGTH_M         0xFFFFFFFF  // Block Length/Remaining Byte
// Count
#define SHAMD5_LENGTH_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_0_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_0_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_0_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_1_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_1_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_1_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_2_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_2_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_2_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_3_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_3_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_3_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_4_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_4_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_4_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_5_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_5_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_5_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_6_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_6_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_6_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_7_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_7_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_7_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_8_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_8_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_8_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_9_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_9_IN_DATA_M 0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_9_IN_DATA_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_10_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_10_IN_DATA_M                                              \
                                0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_10_IN_DATA_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_11_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_11_IN_DATA_M                                              \
                                0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_11_IN_DATA_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_12_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_12_IN_DATA_M                                              \
                                0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_12_IN_DATA_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_13_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_13_IN_DATA_M                                              \
                                0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_13_IN_DATA_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_14_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_14_IN_DATA_M                                              \
                                0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_14_IN_DATA_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DATA_15_IN
// register.
//
//*****************************************************************************
#define SHAMD5_DATA_15_IN_DATA_M                                              \
                                0xFFFFFFFF  // Digest/Key Data
#define SHAMD5_DATA_15_IN_DATA_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_REVISION
// register.
//
//*****************************************************************************
#define SHAMD5_REVISION_M       0xFFFFFFFF  // Revision Number
#define SHAMD5_REVISION_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_SYSCONFIG
// register.
//
//*****************************************************************************
#define SHAMD5_SYSCONFIG_SADVANCED                                            \
                                0x00000080  // Advanced Mode Enable
#define SHAMD5_SYSCONFIG_SIDLE_M                                              \
                                0x00000030  // Sidle mode
#define SHAMD5_SYSCONFIG_SIDLE_FORCE                                          \
                                0x00000000  // Force-idle mode
#define SHAMD5_SYSCONFIG_DMA_EN 0x00000008  // uDMA Request Enable
#define SHAMD5_SYSCONFIG_IT_EN  0x00000004  // Interrupt Enable
#define SHAMD5_SYSCONFIG_SOFTRESET                                            \
                                0x00000002  // Soft reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_SYSSTATUS
// register.
//
//*****************************************************************************
#define SHAMD5_SYSSTATUS_RESETDONE                                            \
                                0x00000001  // Reset done status

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IRQSTATUS
// register.
//
//*****************************************************************************
#define SHAMD5_IRQSTATUS_CONTEXT_READY                                        \
                                0x00000008  // Context Ready Status
#define SHAMD5_IRQSTATUS_INPUT_READY                                          \
                                0x00000002  // Input Ready Status
#define SHAMD5_IRQSTATUS_OUTPUT_READY                                         \
                                0x00000001  // Output Ready Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_IRQENABLE
// register.
//
//*****************************************************************************
#define SHAMD5_IRQENABLE_CONTEXT_READY                                        \
                                0x00000008  // Mask for context ready interrupt
#define SHAMD5_IRQENABLE_INPUT_READY                                          \
                                0x00000002  // Mask for input ready interrupt
#define SHAMD5_IRQENABLE_OUTPUT_READY                                         \
                                0x00000001  // Mask for output ready interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DMAIM register.
//
//*****************************************************************************
#define SHAMD5_DMAIM_COUT       0x00000004  // Context Out DMA Done Interrupt
// Mask
#define SHAMD5_DMAIM_DIN        0x00000002  // Data In DMA Done Interrupt Mask
#define SHAMD5_DMAIM_CIN        0x00000001  // Context In DMA Done Interrupt
// Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DMARIS
// register.
//
//*****************************************************************************
#define SHAMD5_DMARIS_COUT      0x00000004  // Context Out DMA Done Raw
// Interrupt Status
#define SHAMD5_DMARIS_DIN       0x00000002  // Data In DMA Done Raw Interrupt
// Status
#define SHAMD5_DMARIS_CIN       0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DMAMIS
// register.
//
//*****************************************************************************
#define SHAMD5_DMAMIS_COUT      0x00000004  // Context Out DMA Done Masked
// Interrupt Status
#define SHAMD5_DMAMIS_DIN       0x00000002  // Data In DMA Done Masked
// Interrupt Status
#define SHAMD5_DMAMIS_CIN       0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SHAMD5_O_DMAIC register.
//
//*****************************************************************************
#define SHAMD5_DMAIC_COUT       0x00000004  // Context Out DMA Done Masked
// Interrupt Status
#define SHAMD5_DMAIC_DIN        0x00000002  // Data In DMA Done Interrupt Clear
#define SHAMD5_DMAIC_CIN        0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY2_6 register.
//
//*****************************************************************************
#define AES_KEY2_6_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY2_6_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY2_7 register.
//
//*****************************************************************************
#define AES_KEY2_7_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY2_7_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY2_4 register.
//
//*****************************************************************************
#define AES_KEY2_4_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY2_4_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY2_5 register.
//
//*****************************************************************************
#define AES_KEY2_5_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY2_5_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY2_2 register.
//
//*****************************************************************************
#define AES_KEY2_2_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY2_2_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY2_3 register.
//
//*****************************************************************************
#define AES_KEY2_3_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY2_3_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY2_0 register.
//
//*****************************************************************************
#define AES_KEY2_0_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY2_0_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY2_1 register.
//
//*****************************************************************************
#define AES_KEY2_1_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY2_1_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY1_6 register.
//
//*****************************************************************************
#define AES_KEY1_6_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY1_6_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY1_7 register.
//
//*****************************************************************************
#define AES_KEY1_7_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY1_7_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY1_4 register.
//
//*****************************************************************************
#define AES_KEY1_4_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY1_4_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY1_5 register.
//
//*****************************************************************************
#define AES_KEY1_5_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY1_5_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY1_2 register.
//
//*****************************************************************************
#define AES_KEY1_2_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY1_2_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY1_3 register.
//
//*****************************************************************************
#define AES_KEY1_3_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY1_3_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY1_0 register.
//
//*****************************************************************************
#define AES_KEY1_0_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY1_0_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_KEY1_1 register.
//
//*****************************************************************************
#define AES_KEY1_1_KEY_M        0xFFFFFFFF  // Key Data
#define AES_KEY1_1_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_IV_IN_0 register.
//
//*****************************************************************************
#define AES_IV_IN_0_DATA_M      0xFFFFFFFF  // Initialization Vector Input
#define AES_IV_IN_0_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_IV_IN_1 register.
//
//*****************************************************************************
#define AES_IV_IN_1_DATA_M      0xFFFFFFFF  // Initialization Vector Input
#define AES_IV_IN_1_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_IV_IN_2 register.
//
//*****************************************************************************
#define AES_IV_IN_2_DATA_M      0xFFFFFFFF  // Initialization Vector Input
#define AES_IV_IN_2_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_IV_IN_3 register.
//
//*****************************************************************************
#define AES_IV_IN_3_DATA_M      0xFFFFFFFF  // Initialization Vector Input
#define AES_IV_IN_3_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_CTRL register.
//
//*****************************************************************************
#define AES_CTRL_CTXTRDY        0x80000000  // Context Data Registers Ready
#define AES_CTRL_SVCTXTRDY      0x40000000  // AES TAG/IV Block(s) Ready
#define AES_CTRL_SAVE_CONTEXT   0x20000000  // TAG or Result IV Save
#define AES_CTRL_CCM_M_M        0x01C00000  // Counter with CBC-MAC (CCM)
#define AES_CTRL_CCM_L_M        0x00380000  // L Value
#define AES_CTRL_CCM_L_2        0x00080000  // width = 2
#define AES_CTRL_CCM_L_4        0x00180000  // width = 4
#define AES_CTRL_CCM_L_8        0x00380000  // width = 8
#define AES_CTRL_CCM            0x00040000  // AES-CCM Mode Enable
#define AES_CTRL_GCM_M          0x00030000  // AES-GCM Mode Enable
#define AES_CTRL_GCM_NOP        0x00000000  // No operation
#define AES_CTRL_GCM_HLY0ZERO   0x00010000  // GHASH with H loaded and
// Y0-encrypted forced to zero
#define AES_CTRL_GCM_HLY0CALC   0x00020000  // GHASH with H loaded and
// Y0-encrypted calculated
// internally
#define AES_CTRL_GCM_HY0CALC    0x00030000  // Autonomous GHASH (both H and
// Y0-encrypted calculated
// internally)
#define AES_CTRL_CBCMAC         0x00008000  // AES-CBC MAC Enable
#define AES_CTRL_F9             0x00004000  // AES f9 Mode Enable
#define AES_CTRL_F8             0x00002000  // AES f8 Mode Enable
#define AES_CTRL_XTS_M          0x00001800  // AES-XTS Operation Enabled
#define AES_CTRL_XTS_NOP        0x00000000  // No operation
#define AES_CTRL_XTS_TWEAKJL    0x00000800  // Previous/intermediate tweak
// value and j loaded (value is
// loaded via IV, j is loaded via
// the AAD length register)
#define AES_CTRL_XTS_K2IJL      0x00001000  // Key2, n and j are loaded (n is
// loaded via IV, j is loaded via
// the AAD length register)
#define AES_CTRL_XTS_K2ILJ0     0x00001800  // Key2 and n are loaded; j=0 (n is
// loaded via IV)
#define AES_CTRL_CFB            0x00000400  // Full block AES cipher feedback
// mode (CFB128) Enable
#define AES_CTRL_ICM            0x00000200  // AES Integer Counter Mode (ICM)
// Enable
#define AES_CTRL_CTR_WIDTH_M    0x00000180  // AES-CTR Mode Counter Width
#define AES_CTRL_CTR_WIDTH_32   0x00000000  // Counter is 32 bits
#define AES_CTRL_CTR_WIDTH_64   0x00000080  // Counter is 64 bits
#define AES_CTRL_CTR_WIDTH_96   0x00000100  // Counter is 96 bits
#define AES_CTRL_CTR_WIDTH_128  0x00000180  // Counter is 128 bits
#define AES_CTRL_CTR            0x00000040  // Counter Mode
#define AES_CTRL_MODE           0x00000020  // ECB/CBC Mode
#define AES_CTRL_KEY_SIZE_M     0x00000018  // Key Size
#define AES_CTRL_KEY_SIZE_128   0x00000008  // Key is 128 bits
#define AES_CTRL_KEY_SIZE_192   0x00000010  // Key is 192 bits
#define AES_CTRL_KEY_SIZE_256   0x00000018  // Key is 256 bits
#define AES_CTRL_DIRECTION      0x00000004  // Encryption/Decryption Selection
#define AES_CTRL_INPUT_READY    0x00000002  // Input Ready Status
#define AES_CTRL_OUTPUT_READY   0x00000001  // Output Ready Status
#define AES_CTRL_CCM_M_S        22

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_C_LENGTH_0
// register.
//
//*****************************************************************************
#define AES_C_LENGTH_0_LENGTH_M 0xFFFFFFFF  // Data Length
#define AES_C_LENGTH_0_LENGTH_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_C_LENGTH_1
// register.
//
//*****************************************************************************
#define AES_C_LENGTH_1_LENGTH_M 0xFFFFFFFF  // Data Length
#define AES_C_LENGTH_1_LENGTH_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_AUTH_LENGTH
// register.
//
//*****************************************************************************
#define AES_AUTH_LENGTH_AUTH_M  0xFFFFFFFF  // Authentication Data Length
#define AES_AUTH_LENGTH_AUTH_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DATA_IN_0
// register.
//
//*****************************************************************************
#define AES_DATA_IN_0_DATA_M    0xFFFFFFFF  // Secure Data RW
// Plaintext/Ciphertext
#define AES_DATA_IN_0_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DATA_IN_1
// register.
//
//*****************************************************************************
#define AES_DATA_IN_1_DATA_M    0xFFFFFFFF  // Secure Data RW
// Plaintext/Ciphertext
#define AES_DATA_IN_1_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DATA_IN_2
// register.
//
//*****************************************************************************
#define AES_DATA_IN_2_DATA_M    0xFFFFFFFF  // Secure Data RW
// Plaintext/Ciphertext
#define AES_DATA_IN_2_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DATA_IN_3
// register.
//
//*****************************************************************************
#define AES_DATA_IN_3_DATA_M    0xFFFFFFFF  // Secure Data RW
// Plaintext/Ciphertext
#define AES_DATA_IN_3_DATA_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_TAG_OUT_0
// register.
//
//*****************************************************************************
#define AES_TAG_OUT_0_HASH_M    0xFFFFFFFF  // Hash Result
#define AES_TAG_OUT_0_HASH_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_TAG_OUT_1
// register.
//
//*****************************************************************************
#define AES_TAG_OUT_1_HASH_M    0xFFFFFFFF  // Hash Result
#define AES_TAG_OUT_1_HASH_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_TAG_OUT_2
// register.
//
//*****************************************************************************
#define AES_TAG_OUT_2_HASH_M    0xFFFFFFFF  // Hash Result
#define AES_TAG_OUT_2_HASH_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_TAG_OUT_3
// register.
//
//*****************************************************************************
#define AES_TAG_OUT_3_HASH_M    0xFFFFFFFF  // Hash Result
#define AES_TAG_OUT_3_HASH_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_REVISION register.
//
//*****************************************************************************
#define AES_REVISION_M          0xFFFFFFFF  // Revision number
#define AES_REVISION_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_SYSCONFIG
// register.
//
//*****************************************************************************
#define AES_SYSCONFIG_K3        0x00001000  // K3 Select
#define AES_SYSCONFIG_KEYENC    0x00000800  // Key Encoding
#define AES_SYSCONFIG_MAP_CONTEXT_OUT_ON_DATA_OUT                             \
                                0x00000200  // Map Context Out on Data Out
// Enable
#define AES_SYSCONFIG_DMA_REQ_CONTEXT_OUT_EN                                  \
                                0x00000100  // DMA Request Context Out Enable
#define AES_SYSCONFIG_DMA_REQ_CONTEXT_IN_EN                                   \
                                0x00000080  // DMA Request Context In Enable
#define AES_SYSCONFIG_DMA_REQ_DATA_OUT_EN                                     \
                                0x00000040  // DMA Request Data Out Enable
#define AES_SYSCONFIG_DMA_REQ_DATA_IN_EN                                      \
                                0x00000020  // DMA Request Data In Enable
#define AES_SYSCONFIG_SOFTRESET 0x00000002  // Soft reset

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_SYSSTATUS
// register.
//
//*****************************************************************************
#define AES_SYSSTATUS_RESETDONE 0x00000001  // Reset Done

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_IRQSTATUS
// register.
//
//*****************************************************************************
#define AES_IRQSTATUS_CONTEXT_OUT                                             \
                                0x00000008  // Context Output Interrupt Status
#define AES_IRQSTATUS_DATA_OUT  0x00000004  // Data Out Interrupt Status
#define AES_IRQSTATUS_DATA_IN   0x00000002  // Data In Interrupt Status
#define AES_IRQSTATUS_CONTEXT_IN                                              \
                                0x00000001  // Context In Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_IRQENABLE
// register.
//
//*****************************************************************************
#define AES_IRQENABLE_CONTEXT_OUT                                             \
                                0x00000008  // Context Out Interrupt Enable
#define AES_IRQENABLE_DATA_OUT  0x00000004  // Data Out Interrupt Enable
#define AES_IRQENABLE_DATA_IN   0x00000002  // Data In Interrupt Enable
#define AES_IRQENABLE_CONTEXT_IN                                              \
                                0x00000001  // Context In Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DIRTYBITS
// register.
//
//*****************************************************************************
#define AES_DIRTYBITS_S_DIRTY   0x00000002  // AES Dirty Bit
#define AES_DIRTYBITS_S_ACCESS  0x00000001  // AES Access Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DMAIM register.
//
//*****************************************************************************
#define AES_DMAIM_DOUT          0x00000008  // Data Out DMA Done Interrupt Mask
#define AES_DMAIM_DIN           0x00000004  // Data In DMA Done Interrupt Mask
#define AES_DMAIM_COUT          0x00000002  // Context Out DMA Done Interrupt
// Mask
#define AES_DMAIM_CIN           0x00000001  // Context In DMA Done Interrupt
// Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DMARIS register.
//
//*****************************************************************************
#define AES_DMARIS_DOUT         0x00000008  // Data Out DMA Done Raw Interrupt
// Status
#define AES_DMARIS_DIN          0x00000004  // Data In DMA Done Raw Interrupt
// Status
#define AES_DMARIS_COUT         0x00000002  // Context Out DMA Done Raw
// Interrupt Status
#define AES_DMARIS_CIN          0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DMAMIS register.
//
//*****************************************************************************
#define AES_DMAMIS_DOUT         0x00000008  // Data Out DMA Done Masked
// Interrupt Status
#define AES_DMAMIS_DIN          0x00000004  // Data In DMA Done Masked
// Interrupt Status
#define AES_DMAMIS_COUT         0x00000002  // Context Out DMA Done Masked
// Interrupt Status
#define AES_DMAMIS_CIN          0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the AES_O_DMAIC register.
//
//*****************************************************************************
#define AES_DMAIC_DOUT          0x00000008  // Data Out DMA Done Interrupt
// Clear
#define AES_DMAIC_DIN           0x00000004  // Data In DMA Done Interrupt Clear
#define AES_DMAIC_COUT          0x00000002  // Context Out DMA Done Masked
// Interrupt Status
#define AES_DMAIC_CIN           0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_KEY3_L register.
//
//*****************************************************************************
#define DES_KEY3_L_KEY_M        0xFFFFFFFF  // Key Data
#define DES_KEY3_L_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_KEY3_H register.
//
//*****************************************************************************
#define DES_KEY3_H_KEY_M        0xFFFFFFFF  // Key Data
#define DES_KEY3_H_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_KEY2_L register.
//
//*****************************************************************************
#define DES_KEY2_L_KEY_M        0xFFFFFFFF  // Key Data
#define DES_KEY2_L_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_KEY2_H register.
//
//*****************************************************************************
#define DES_KEY2_H_KEY_M        0xFFFFFFFF  // Key Data
#define DES_KEY2_H_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_KEY1_L register.
//
//*****************************************************************************
#define DES_KEY1_L_KEY_M        0xFFFFFFFF  // Key Data
#define DES_KEY1_L_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_KEY1_H register.
//
//*****************************************************************************
#define DES_KEY1_H_KEY_M        0xFFFFFFFF  // Key Data
#define DES_KEY1_H_KEY_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_IV_L register.
//
//*****************************************************************************
#define DES_IV_L_M              0xFFFFFFFF  // Initialization vector for CBC,
// CFB modes (LSW)
#define DES_IV_L_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_IV_H register.
//
//*****************************************************************************
#define DES_IV_H_M              0xFFFFFFFF  // Initialization vector for CBC,
// CFB modes (MSW)
#define DES_IV_H_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_CTRL register.
//
//*****************************************************************************
#define DES_CTRL_CONTEXT        0x80000000  // If 1, this read-only status bit
// indicates that the context data
// registers can be overwritten and
// the host is permitted to write
// the next context
#define DES_CTRL_MODE_M         0x00000030  // Select CBC, ECB or CFB mode0x0:
// ECB mode0x1: CBC mode0x2: CFB
// mode0x3: reserved
#define DES_CTRL_TDES           0x00000008  // Select DES or triple DES
// encryption/decryption
#define DES_CTRL_DIRECTION      0x00000004  // Select encryption/decryption
// 0x0: decryption is selected0x1:
// Encryption is selected
#define DES_CTRL_INPUT_READY    0x00000002  // When 1, ready to encrypt/decrypt
// data
#define DES_CTRL_OUTPUT_READY   0x00000001  // When 1, Data decrypted/encrypted
// ready
#define DES_CTRL_MODE_S         4

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_LENGTH register.
//
//*****************************************************************************
#define DES_LENGTH_M            0xFFFFFFFF  // Cryptographic data length in
// bytes for all modes
#define DES_LENGTH_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_DATA_L register.
//
//*****************************************************************************
#define DES_DATA_L_M            0xFFFFFFFF  // Data for encryption/decryption,
// LSW
#define DES_DATA_L_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_DATA_H register.
//
//*****************************************************************************
#define DES_DATA_H_M            0xFFFFFFFF  // Data for encryption/decryption,
// MSW
#define DES_DATA_H_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_REVISION register.
//
//*****************************************************************************
#define DES_REVISION_M          0xFFFFFFFF  // Revision number
#define DES_REVISION_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_SYSCONFIG
// register.
//
//*****************************************************************************
#define DES_SYSCONFIG_DMA_REQ_CONTEXT_IN_EN                                   \
                                0x00000080  // DMA Request Context In Enable
#define DES_SYSCONFIG_DMA_REQ_DATA_OUT_EN                                     \
                                0x00000040  // DMA Request Data Out Enable
#define DES_SYSCONFIG_DMA_REQ_DATA_IN_EN                                      \
                                0x00000020  // DMA Request Data In Enable
#define DES_SYSCONFIG_SIDLE_M   0x0000000C  // Sidle mode
#define DES_SYSCONFIG_SIDLE_FORCE                                             \
                                0x00000000  // Force-idle mode
#define DES_SYSCONFIG_SOFTRESET 0x00000002  // Soft reset

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_SYSSTATUS
// register.
//
//*****************************************************************************
#define DES_SYSSTATUS_RESETDONE 0x00000001  // Reset Done

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_IRQSTATUS
// register.
//
//*****************************************************************************
#define DES_IRQSTATUS_DATA_OUT  0x00000004  // This bit indicates data output
// interrupt is active and triggers
// the interrupt output
#define DES_IRQSTATUS_DATA_IN   0x00000002  // This bit indicates data input
// interrupt is active and triggers
// the interrupt output
#define DES_IRQSTATUS_CONTEX_IN 0x00000001  // This bit indicates context
// interrupt is active and triggers
// the interrupt output

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_IRQENABLE
// register.
//
//*****************************************************************************
#define DES_IRQENABLE_M_DATA_OUT                                              \
                                0x00000004  // If this bit is set to 1 the data
// output interrupt is enabled
#define DES_IRQENABLE_M_DATA_IN 0x00000002  // If this bit is set to 1 the data
// input interrupt is enabled
#define DES_IRQENABLE_M_CONTEX_IN                                             \
                                0x00000001  // If this bit is set to 1 the
// context interrupt is enabled

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_DIRTYBITS
// register.
//
//*****************************************************************************
#define DES_DIRTYBITS_S_DIRTY   0x00000002  // This bit is set to 1 by the
// module if any of the DES_*
// registers is written
#define DES_DIRTYBITS_S_ACCESS  0x00000001  // This bit is set to 1 by the
// module if any of the DES_*
// registers is read

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_DMAIM register.
//
//*****************************************************************************
#define DES_DMAIM_DOUT          0x00000004  // Data Out DMA Done Interrupt Mask
#define DES_DMAIM_DIN           0x00000002  // Data In DMA Done Interrupt Mask
#define DES_DMAIM_CIN           0x00000001  // Context In DMA Done Interrupt
// Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_DMARIS register.
//
//*****************************************************************************
#define DES_DMARIS_DOUT         0x00000004  // Data Out DMA Done Raw Interrupt
// Status
#define DES_DMARIS_DIN          0x00000002  // Data In DMA Done Raw Interrupt
// Status
#define DES_DMARIS_CIN          0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_DMAMIS register.
//
//*****************************************************************************
#define DES_DMAMIS_DOUT         0x00000004  // Data Out DMA Done Masked
// Interrupt Status
#define DES_DMAMIS_DIN          0x00000002  // Data In DMA Done Masked
// Interrupt Status
#define DES_DMAMIS_CIN          0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the DES_O_DMAIC register.
//
//*****************************************************************************
#define DES_DMAIC_DOUT          0x00000004  // Data Out DMA Done Interrupt
// Clear
#define DES_DMAIC_DIN           0x00000002  // Data In DMA Done Interrupt Clear
#define DES_DMAIC_CIN           0x00000001  // Context In DMA Done Raw
// Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ACTLR register.
//
//*****************************************************************************
#define NVIC_ACTLR_DISOOFP      0x00000200  // Disable Out-Of-Order Floating
// Point
#define NVIC_ACTLR_DISFPCA      0x00000100  // Disable CONTROL
#define NVIC_ACTLR_DISFOLD      0x00000004  // Disable IT Folding
#define NVIC_ACTLR_DISWBUF      0x00000002  // Disable Write Buffer
#define NVIC_ACTLR_DISMCYC      0x00000001  // Disable Interrupts of Multiple
// Cycle Instructions

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ST_CTRL register.
//
//*****************************************************************************
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count Flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt Enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ST_RELOAD register.
//
//*****************************************************************************
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Reload Value
#define NVIC_ST_RELOAD_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ST_CURRENT
// register.
//
//*****************************************************************************
#define NVIC_ST_CURRENT_M       0x00FFFFFF  // Current Value
#define NVIC_ST_CURRENT_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_EN0 register.
//
//*****************************************************************************
#define NVIC_EN0_INT_M          0xFFFFFFFF  // Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_EN1 register.
//
//*****************************************************************************
#define NVIC_EN1_INT_M          0xFFFFFFFF  // Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_EN2 register.
//
//*****************************************************************************
#define NVIC_EN2_INT_M          0xFFFFFFFF  // Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_EN3 register.
//
//*****************************************************************************
#define NVIC_EN3_INT_M          0xFFFFFFFF  // Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DIS0 register.
//
//*****************************************************************************
#define NVIC_DIS0_INT_M         0xFFFFFFFF  // Interrupt Disable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DIS1 register.
//
//*****************************************************************************
#define NVIC_DIS1_INT_M         0xFFFFFFFF  // Interrupt Disable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DIS2 register.
//
//*****************************************************************************
#define NVIC_DIS2_INT_M         0xFFFFFFFF  // Interrupt Disable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DIS3 register.
//
//*****************************************************************************
#define NVIC_DIS3_INT_M         0xFFFFFFFF  // Interrupt Disable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PEND0 register.
//
//*****************************************************************************
#define NVIC_PEND0_INT_M        0xFFFFFFFF  // Interrupt Set Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PEND1 register.
//
//*****************************************************************************
#define NVIC_PEND1_INT_M        0xFFFFFFFF  // Interrupt Set Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PEND2 register.
//
//*****************************************************************************
#define NVIC_PEND2_INT_M        0xFFFFFFFF  // Interrupt Set Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PEND3 register.
//
//*****************************************************************************
#define NVIC_PEND3_INT_M        0xFFFFFFFF  // Interrupt Set Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_UNPEND0 register.
//
//*****************************************************************************
#define NVIC_UNPEND0_INT_M      0xFFFFFFFF  // Interrupt Clear Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_UNPEND1 register.
//
//*****************************************************************************
#define NVIC_UNPEND1_INT_M      0xFFFFFFFF  // Interrupt Clear Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_UNPEND2 register.
//
//*****************************************************************************
#define NVIC_UNPEND2_INT_M      0xFFFFFFFF  // Interrupt Clear Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_UNPEND3 register.
//
//*****************************************************************************
#define NVIC_UNPEND3_INT_M      0xFFFFFFFF  // Interrupt Clear Pending

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ACTIVE0 register.
//
//*****************************************************************************
#define NVIC_ACTIVE0_INT_M      0xFFFFFFFF  // Interrupt Active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ACTIVE1 register.
//
//*****************************************************************************
#define NVIC_ACTIVE1_INT_M      0xFFFFFFFF  // Interrupt Active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ACTIVE2 register.
//
//*****************************************************************************
#define NVIC_ACTIVE2_INT_M      0xFFFFFFFF  // Interrupt Active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ACTIVE3 register.
//
//*****************************************************************************
#define NVIC_ACTIVE3_INT_M      0xFFFFFFFF  // Interrupt Active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI0 register.
//
//*****************************************************************************
#define NVIC_PRI0_INT3_M        0xE0000000  // Interrupt 3 Priority Mask
#define NVIC_PRI0_INT2_M        0x00E00000  // Interrupt 2 Priority Mask
#define NVIC_PRI0_INT1_M        0x0000E000  // Interrupt 1 Priority Mask
#define NVIC_PRI0_INT0_M        0x000000E0  // Interrupt 0 Priority Mask
#define NVIC_PRI0_INT3_S        29
#define NVIC_PRI0_INT2_S        21
#define NVIC_PRI0_INT1_S        13
#define NVIC_PRI0_INT0_S        5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI1 register.
//
//*****************************************************************************
#define NVIC_PRI1_INT7_M        0xE0000000  // Interrupt 7 Priority Mask
#define NVIC_PRI1_INT6_M        0x00E00000  // Interrupt 6 Priority Mask
#define NVIC_PRI1_INT5_M        0x0000E000  // Interrupt 5 Priority Mask
#define NVIC_PRI1_INT4_M        0x000000E0  // Interrupt 4 Priority Mask
#define NVIC_PRI1_INT7_S        29
#define NVIC_PRI1_INT6_S        21
#define NVIC_PRI1_INT5_S        13
#define NVIC_PRI1_INT4_S        5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI2 register.
//
//*****************************************************************************
#define NVIC_PRI2_INT11_M       0xE0000000  // Interrupt 11 Priority Mask
#define NVIC_PRI2_INT10_M       0x00E00000  // Interrupt 10 Priority Mask
#define NVIC_PRI2_INT9_M        0x0000E000  // Interrupt 9 Priority Mask
#define NVIC_PRI2_INT8_M        0x000000E0  // Interrupt 8 Priority Mask
#define NVIC_PRI2_INT11_S       29
#define NVIC_PRI2_INT10_S       21
#define NVIC_PRI2_INT9_S        13
#define NVIC_PRI2_INT8_S        5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI3 register.
//
//*****************************************************************************
#define NVIC_PRI3_INT15_M       0xE0000000  // Interrupt 15 Priority Mask
#define NVIC_PRI3_INT14_M       0x00E00000  // Interrupt 14 Priority Mask
#define NVIC_PRI3_INT13_M       0x0000E000  // Interrupt 13 Priority Mask
#define NVIC_PRI3_INT12_M       0x000000E0  // Interrupt 12 Priority Mask
#define NVIC_PRI3_INT15_S       29
#define NVIC_PRI3_INT14_S       21
#define NVIC_PRI3_INT13_S       13
#define NVIC_PRI3_INT12_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI4 register.
//
//*****************************************************************************
#define NVIC_PRI4_INT19_M       0xE0000000  // Interrupt 19 Priority Mask
#define NVIC_PRI4_INT18_M       0x00E00000  // Interrupt 18 Priority Mask
#define NVIC_PRI4_INT17_M       0x0000E000  // Interrupt 17 Priority Mask
#define NVIC_PRI4_INT16_M       0x000000E0  // Interrupt 16 Priority Mask
#define NVIC_PRI4_INT19_S       29
#define NVIC_PRI4_INT18_S       21
#define NVIC_PRI4_INT17_S       13
#define NVIC_PRI4_INT16_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI5 register.
//
//*****************************************************************************
#define NVIC_PRI5_INT23_M       0xE0000000  // Interrupt 23 Priority Mask
#define NVIC_PRI5_INT22_M       0x00E00000  // Interrupt 22 Priority Mask
#define NVIC_PRI5_INT21_M       0x0000E000  // Interrupt 21 Priority Mask
#define NVIC_PRI5_INT20_M       0x000000E0  // Interrupt 20 Priority Mask
#define NVIC_PRI5_INT23_S       29
#define NVIC_PRI5_INT22_S       21
#define NVIC_PRI5_INT21_S       13
#define NVIC_PRI5_INT20_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI6 register.
//
//*****************************************************************************
#define NVIC_PRI6_INT27_M       0xE0000000  // Interrupt 27 Priority Mask
#define NVIC_PRI6_INT26_M       0x00E00000  // Interrupt 26 Priority Mask
#define NVIC_PRI6_INT25_M       0x0000E000  // Interrupt 25 Priority Mask
#define NVIC_PRI6_INT24_M       0x000000E0  // Interrupt 24 Priority Mask
#define NVIC_PRI6_INT27_S       29
#define NVIC_PRI6_INT26_S       21
#define NVIC_PRI6_INT25_S       13
#define NVIC_PRI6_INT24_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI7 register.
//
//*****************************************************************************
#define NVIC_PRI7_INT31_M       0xE0000000  // Interrupt 31 Priority Mask
#define NVIC_PRI7_INT30_M       0x00E00000  // Interrupt 30 Priority Mask
#define NVIC_PRI7_INT29_M       0x0000E000  // Interrupt 29 Priority Mask
#define NVIC_PRI7_INT28_M       0x000000E0  // Interrupt 28 Priority Mask
#define NVIC_PRI7_INT31_S       29
#define NVIC_PRI7_INT30_S       21
#define NVIC_PRI7_INT29_S       13
#define NVIC_PRI7_INT28_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI8 register.
//
//*****************************************************************************
#define NVIC_PRI8_INT35_M       0xE0000000  // Interrupt 35 Priority Mask
#define NVIC_PRI8_INT34_M       0x00E00000  // Interrupt 34 Priority Mask
#define NVIC_PRI8_INT33_M       0x0000E000  // Interrupt 33 Priority Mask
#define NVIC_PRI8_INT32_M       0x000000E0  // Interrupt 32 Priority Mask
#define NVIC_PRI8_INT35_S       29
#define NVIC_PRI8_INT34_S       21
#define NVIC_PRI8_INT33_S       13
#define NVIC_PRI8_INT32_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI9 register.
//
//*****************************************************************************
#define NVIC_PRI9_INT39_M       0xE0000000  // Interrupt 39 Priority Mask
#define NVIC_PRI9_INT38_M       0x00E00000  // Interrupt 38 Priority Mask
#define NVIC_PRI9_INT37_M       0x0000E000  // Interrupt 37 Priority Mask
#define NVIC_PRI9_INT36_M       0x000000E0  // Interrupt 36 Priority Mask
#define NVIC_PRI9_INT39_S       29
#define NVIC_PRI9_INT38_S       21
#define NVIC_PRI9_INT37_S       13
#define NVIC_PRI9_INT36_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI10 register.
//
//*****************************************************************************
#define NVIC_PRI10_INT43_M      0xE0000000  // Interrupt 43 Priority Mask
#define NVIC_PRI10_INT42_M      0x00E00000  // Interrupt 42 Priority Mask
#define NVIC_PRI10_INT41_M      0x0000E000  // Interrupt 41 Priority Mask
#define NVIC_PRI10_INT40_M      0x000000E0  // Interrupt 40 Priority Mask
#define NVIC_PRI10_INT43_S      29
#define NVIC_PRI10_INT42_S      21
#define NVIC_PRI10_INT41_S      13
#define NVIC_PRI10_INT40_S      5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI11 register.
//
//*****************************************************************************
#define NVIC_PRI11_INT47_M      0xE0000000  // Interrupt 47 Priority Mask
#define NVIC_PRI11_INT46_M      0x00E00000  // Interrupt 46 Priority Mask
#define NVIC_PRI11_INT45_M      0x0000E000  // Interrupt 45 Priority Mask
#define NVIC_PRI11_INT44_M      0x000000E0  // Interrupt 44 Priority Mask
#define NVIC_PRI11_INT47_S      29
#define NVIC_PRI11_INT46_S      21
#define NVIC_PRI11_INT45_S      13
#define NVIC_PRI11_INT44_S      5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI12 register.
//
//*****************************************************************************
#define NVIC_PRI12_INT51_M      0xE0000000  // Interrupt 51 Priority Mask
#define NVIC_PRI12_INT50_M      0x00E00000  // Interrupt 50 Priority Mask
#define NVIC_PRI12_INT49_M      0x0000E000  // Interrupt 49 Priority Mask
#define NVIC_PRI12_INT48_M      0x000000E0  // Interrupt 48 Priority Mask
#define NVIC_PRI12_INT51_S      29
#define NVIC_PRI12_INT50_S      21
#define NVIC_PRI12_INT49_S      13
#define NVIC_PRI12_INT48_S      5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI13 register.
//
//*****************************************************************************
#define NVIC_PRI13_INT55_M      0xE0000000  // Interrupt 55 Priority Mask
#define NVIC_PRI13_INT54_M      0x00E00000  // Interrupt 54 Priority Mask
#define NVIC_PRI13_INT53_M      0x0000E000  // Interrupt 53 Priority Mask
#define NVIC_PRI13_INT52_M      0x000000E0  // Interrupt 52 Priority Mask
#define NVIC_PRI13_INT55_S      29
#define NVIC_PRI13_INT54_S      21
#define NVIC_PRI13_INT53_S      13
#define NVIC_PRI13_INT52_S      5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI14 register.
//
//*****************************************************************************
#define NVIC_PRI14_INTD_M       0xE0000000  // Interrupt 59 Priority Mask
#define NVIC_PRI14_INTC_M       0x00E00000  // Interrupt 58 Priority Mask
#define NVIC_PRI14_INTB_M       0x0000E000  // Interrupt 57 Priority Mask
#define NVIC_PRI14_INTA_M       0x000000E0  // Interrupt 56 Priority Mask
#define NVIC_PRI14_INTD_S       29
#define NVIC_PRI14_INTC_S       21
#define NVIC_PRI14_INTB_S       13
#define NVIC_PRI14_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI15 register.
//
//*****************************************************************************
#define NVIC_PRI15_INTD_M       0xE0000000  // Interrupt 63 Priority Mask
#define NVIC_PRI15_INTC_M       0x00E00000  // Interrupt 62 Priority Mask
#define NVIC_PRI15_INTB_M       0x0000E000  // Interrupt 61 Priority Mask
#define NVIC_PRI15_INTA_M       0x000000E0  // Interrupt 60 Priority Mask
#define NVIC_PRI15_INTD_S       29
#define NVIC_PRI15_INTC_S       21
#define NVIC_PRI15_INTB_S       13
#define NVIC_PRI15_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI16 register.
//
//*****************************************************************************
#define NVIC_PRI16_INTD_M       0xE0000000  // Interrupt 67 Priority Mask
#define NVIC_PRI16_INTC_M       0x00E00000  // Interrupt 66 Priority Mask
#define NVIC_PRI16_INTB_M       0x0000E000  // Interrupt 65 Priority Mask
#define NVIC_PRI16_INTA_M       0x000000E0  // Interrupt 64 Priority Mask
#define NVIC_PRI16_INTD_S       29
#define NVIC_PRI16_INTC_S       21
#define NVIC_PRI16_INTB_S       13
#define NVIC_PRI16_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI17 register.
//
//*****************************************************************************
#define NVIC_PRI17_INTD_M       0xE0000000  // Interrupt 71 Priority Mask
#define NVIC_PRI17_INTC_M       0x00E00000  // Interrupt 70 Priority Mask
#define NVIC_PRI17_INTB_M       0x0000E000  // Interrupt 69 Priority Mask
#define NVIC_PRI17_INTA_M       0x000000E0  // Interrupt 68 Priority Mask
#define NVIC_PRI17_INTD_S       29
#define NVIC_PRI17_INTC_S       21
#define NVIC_PRI17_INTB_S       13
#define NVIC_PRI17_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI18 register.
//
//*****************************************************************************
#define NVIC_PRI18_INTD_M       0xE0000000  // Interrupt 75 Priority Mask
#define NVIC_PRI18_INTC_M       0x00E00000  // Interrupt 74 Priority Mask
#define NVIC_PRI18_INTB_M       0x0000E000  // Interrupt 73 Priority Mask
#define NVIC_PRI18_INTA_M       0x000000E0  // Interrupt 72 Priority Mask
#define NVIC_PRI18_INTD_S       29
#define NVIC_PRI18_INTC_S       21
#define NVIC_PRI18_INTB_S       13
#define NVIC_PRI18_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI19 register.
//
//*****************************************************************************
#define NVIC_PRI19_INTD_M       0xE0000000  // Interrupt 79 Priority Mask
#define NVIC_PRI19_INTC_M       0x00E00000  // Interrupt 78 Priority Mask
#define NVIC_PRI19_INTB_M       0x0000E000  // Interrupt 77 Priority Mask
#define NVIC_PRI19_INTA_M       0x000000E0  // Interrupt 76 Priority Mask
#define NVIC_PRI19_INTD_S       29
#define NVIC_PRI19_INTC_S       21
#define NVIC_PRI19_INTB_S       13
#define NVIC_PRI19_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI20 register.
//
//*****************************************************************************
#define NVIC_PRI20_INTD_M       0xE0000000  // Interrupt 83 Priority Mask
#define NVIC_PRI20_INTC_M       0x00E00000  // Interrupt 82 Priority Mask
#define NVIC_PRI20_INTB_M       0x0000E000  // Interrupt 81 Priority Mask
#define NVIC_PRI20_INTA_M       0x000000E0  // Interrupt 80 Priority Mask
#define NVIC_PRI20_INTD_S       29
#define NVIC_PRI20_INTC_S       21
#define NVIC_PRI20_INTB_S       13
#define NVIC_PRI20_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI21 register.
//
//*****************************************************************************
#define NVIC_PRI21_INTD_M       0xE0000000  // Interrupt 87 Priority Mask
#define NVIC_PRI21_INTC_M       0x00E00000  // Interrupt 86 Priority Mask
#define NVIC_PRI21_INTB_M       0x0000E000  // Interrupt 85 Priority Mask
#define NVIC_PRI21_INTA_M       0x000000E0  // Interrupt 84 Priority Mask
#define NVIC_PRI21_INTD_S       29
#define NVIC_PRI21_INTC_S       21
#define NVIC_PRI21_INTB_S       13
#define NVIC_PRI21_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI22 register.
//
//*****************************************************************************
#define NVIC_PRI22_INTD_M       0xE0000000  // Interrupt 91 Priority Mask
#define NVIC_PRI22_INTC_M       0x00E00000  // Interrupt 90 Priority Mask
#define NVIC_PRI22_INTB_M       0x0000E000  // Interrupt 89 Priority Mask
#define NVIC_PRI22_INTA_M       0x000000E0  // Interrupt 88 Priority Mask
#define NVIC_PRI22_INTD_S       29
#define NVIC_PRI22_INTC_S       21
#define NVIC_PRI22_INTB_S       13
#define NVIC_PRI22_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI23 register.
//
//*****************************************************************************
#define NVIC_PRI23_INTD_M       0xE0000000  // Interrupt 95 Priority Mask
#define NVIC_PRI23_INTC_M       0x00E00000  // Interrupt 94 Priority Mask
#define NVIC_PRI23_INTB_M       0x0000E000  // Interrupt 93 Priority Mask
#define NVIC_PRI23_INTA_M       0x000000E0  // Interrupt 92 Priority Mask
#define NVIC_PRI23_INTD_S       29
#define NVIC_PRI23_INTC_S       21
#define NVIC_PRI23_INTB_S       13
#define NVIC_PRI23_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI24 register.
//
//*****************************************************************************
#define NVIC_PRI24_INTD_M       0xE0000000  // Interrupt 99 Priority Mask
#define NVIC_PRI24_INTC_M       0x00E00000  // Interrupt 98 Priority Mask
#define NVIC_PRI24_INTB_M       0x0000E000  // Interrupt 97 Priority Mask
#define NVIC_PRI24_INTA_M       0x000000E0  // Interrupt 96 Priority Mask
#define NVIC_PRI24_INTD_S       29
#define NVIC_PRI24_INTC_S       21
#define NVIC_PRI24_INTB_S       13
#define NVIC_PRI24_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI25 register.
//
//*****************************************************************************
#define NVIC_PRI25_INTD_M       0xE0000000  // Interrupt 103 Priority Mask
#define NVIC_PRI25_INTC_M       0x00E00000  // Interrupt 102 Priority Mask
#define NVIC_PRI25_INTB_M       0x0000E000  // Interrupt 101 Priority Mask
#define NVIC_PRI25_INTA_M       0x000000E0  // Interrupt 100 Priority Mask
#define NVIC_PRI25_INTD_S       29
#define NVIC_PRI25_INTC_S       21
#define NVIC_PRI25_INTB_S       13
#define NVIC_PRI25_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI26 register.
//
//*****************************************************************************
#define NVIC_PRI26_INTD_M       0xE0000000  // Interrupt 107 Priority Mask
#define NVIC_PRI26_INTC_M       0x00E00000  // Interrupt 106 Priority Mask
#define NVIC_PRI26_INTB_M       0x0000E000  // Interrupt 105 Priority Mask
#define NVIC_PRI26_INTA_M       0x000000E0  // Interrupt 104 Priority Mask
#define NVIC_PRI26_INTD_S       29
#define NVIC_PRI26_INTC_S       21
#define NVIC_PRI26_INTB_S       13
#define NVIC_PRI26_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI27 register.
//
//*****************************************************************************
#define NVIC_PRI27_INTD_M       0xE0000000  // Interrupt 111 Priority Mask
#define NVIC_PRI27_INTC_M       0x00E00000  // Interrupt 110 Priority Mask
#define NVIC_PRI27_INTB_M       0x0000E000  // Interrupt 109 Priority Mask
#define NVIC_PRI27_INTA_M       0x000000E0  // Interrupt 108 Priority Mask
#define NVIC_PRI27_INTD_S       29
#define NVIC_PRI27_INTC_S       21
#define NVIC_PRI27_INTB_S       13
#define NVIC_PRI27_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI28 register.
//
//*****************************************************************************
#define NVIC_PRI28_INTD_M       0xE0000000  // Interrupt 115 Priority Mask
#define NVIC_PRI28_INTC_M       0x00E00000  // Interrupt 114 Priority Mask
#define NVIC_PRI28_INTB_M       0x0000E000  // Interrupt 113 Priority Mask
#define NVIC_PRI28_INTA_M       0x000000E0  // Interrupt 112 Priority Mask
#define NVIC_PRI28_INTD_S       29
#define NVIC_PRI28_INTC_S       21
#define NVIC_PRI28_INTB_S       13
#define NVIC_PRI28_INTA_S       5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_CPUID register.
//
//*****************************************************************************
#define NVIC_CPUID_IMP_M        0xFF000000  // Implementer Code
#define NVIC_CPUID_IMP_ARM      0x41000000  // ARM
#define NVIC_CPUID_VAR_M        0x00F00000  // Variant Number
#define NVIC_CPUID_CON_M        0x000F0000  // Constant
#define NVIC_CPUID_PARTNO_M     0x0000FFF0  // Part Number
#define NVIC_CPUID_PARTNO_CM4   0x0000C240  // Cortex-M4 processor
#define NVIC_CPUID_REV_M        0x0000000F  // Revision Number

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_INT_CTRL register.
//
//*****************************************************************************
#define NVIC_INT_CTRL_NMI_SET   0x80000000  // NMI Set Pending
#define NVIC_INT_CTRL_PEND_SV   0x10000000  // PendSV Set Pending
#define NVIC_INT_CTRL_UNPEND_SV 0x08000000  // PendSV Clear Pending
#define NVIC_INT_CTRL_PENDSTSET 0x04000000  // SysTick Set Pending
#define NVIC_INT_CTRL_PENDSTCLR 0x02000000  // SysTick Clear Pending
#define NVIC_INT_CTRL_ISR_PRE   0x00800000  // Debug Interrupt Handling
#define NVIC_INT_CTRL_ISR_PEND  0x00400000  // Interrupt Pending
#define NVIC_INT_CTRL_VEC_PEN_M 0x000FF000  // Interrupt Pending Vector Number
#define NVIC_INT_CTRL_VEC_PEN_NMI                                             \
                                0x00002000  // NMI
#define NVIC_INT_CTRL_VEC_PEN_HARD                                            \
                                0x00003000  // Hard fault
#define NVIC_INT_CTRL_VEC_PEN_MEM                                             \
                                0x00004000  // Memory management fault
#define NVIC_INT_CTRL_VEC_PEN_BUS                                             \
                                0x00005000  // Bus fault
#define NVIC_INT_CTRL_VEC_PEN_USG                                             \
                                0x00006000  // Usage fault
#define NVIC_INT_CTRL_VEC_PEN_SVC                                             \
                                0x0000B000  // SVCall
#define NVIC_INT_CTRL_VEC_PEN_PNDSV                                           \
                                0x0000E000  // PendSV
#define NVIC_INT_CTRL_VEC_PEN_TICK                                            \
                                0x0000F000  // SysTick
#define NVIC_INT_CTRL_RET_BASE  0x00000800  // Return to Base
#define NVIC_INT_CTRL_VEC_ACT_M 0x000000FF  // Interrupt Pending Vector Number
#define NVIC_INT_CTRL_VEC_ACT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_VTABLE register.
//
//*****************************************************************************
#define NVIC_VTABLE_OFFSET_M    0xFFFFFC00  // Vector Table Offset
#define NVIC_VTABLE_OFFSET_S    10

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_APINT register.
//
//*****************************************************************************
#define NVIC_APINT_VECTKEY_M    0xFFFF0000  // Register Key
#define NVIC_APINT_VECTKEY      0x05FA0000  // Vector key
#define NVIC_APINT_ENDIANESS    0x00008000  // Data Endianess
#define NVIC_APINT_PRIGROUP_M   0x00000700  // Interrupt Priority Grouping
#define NVIC_APINT_PRIGROUP_7_1 0x00000000  // Priority group 7.1 split
#define NVIC_APINT_PRIGROUP_6_2 0x00000100  // Priority group 6.2 split
#define NVIC_APINT_PRIGROUP_5_3 0x00000200  // Priority group 5.3 split
#define NVIC_APINT_PRIGROUP_4_4 0x00000300  // Priority group 4.4 split
#define NVIC_APINT_PRIGROUP_3_5 0x00000400  // Priority group 3.5 split
#define NVIC_APINT_PRIGROUP_2_6 0x00000500  // Priority group 2.6 split
#define NVIC_APINT_PRIGROUP_1_7 0x00000600  // Priority group 1.7 split
#define NVIC_APINT_PRIGROUP_0_8 0x00000700  // Priority group 0.8 split
#define NVIC_APINT_SYSRESETREQ  0x00000004  // System Reset Request
#define NVIC_APINT_VECT_CLR_ACT 0x00000002  // Clear Active NMI / Fault
#define NVIC_APINT_VECT_RESET   0x00000001  // System Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_CTRL register.
//
//*****************************************************************************
#define NVIC_SYS_CTRL_SEVONPEND 0x00000010  // Wake Up on Pending
#define NVIC_SYS_CTRL_SLEEPDEEP 0x00000004  // Deep Sleep Enable
#define NVIC_SYS_CTRL_SLEEPEXIT 0x00000002  // Sleep on ISR Exit

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_CFG_CTRL register.
//
//*****************************************************************************
#define NVIC_CFG_CTRL_STKALIGN  0x00000200  // Stack Alignment on Exception
// Entry
#define NVIC_CFG_CTRL_BFHFNMIGN 0x00000100  // Ignore Bus Fault in NMI and
// Fault
#define NVIC_CFG_CTRL_DIV0      0x00000010  // Trap on Divide by 0
#define NVIC_CFG_CTRL_UNALIGNED 0x00000008  // Trap on Unaligned Access
#define NVIC_CFG_CTRL_MAIN_PEND 0x00000002  // Allow Main Interrupt Trigger
#define NVIC_CFG_CTRL_BASE_THR  0x00000001  // Thread State Control

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_PRI1 register.
//
//*****************************************************************************
#define NVIC_SYS_PRI1_USAGE_M   0x00E00000  // Usage Fault Priority
#define NVIC_SYS_PRI1_BUS_M     0x0000E000  // Bus Fault Priority
#define NVIC_SYS_PRI1_MEM_M     0x000000E0  // Memory Management Fault Priority
#define NVIC_SYS_PRI1_USAGE_S   21
#define NVIC_SYS_PRI1_BUS_S     13
#define NVIC_SYS_PRI1_MEM_S     5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_PRI2 register.
//
//*****************************************************************************
#define NVIC_SYS_PRI2_SVC_M     0xE0000000  // SVCall Priority
#define NVIC_SYS_PRI2_SVC_S     29

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_PRI3 register.
//
//*****************************************************************************
#define NVIC_SYS_PRI3_TICK_M    0xE0000000  // SysTick Exception Priority
#define NVIC_SYS_PRI3_PENDSV_M  0x00E00000  // PendSV Priority
#define NVIC_SYS_PRI3_DEBUG_M   0x000000E0  // Debug Priority
#define NVIC_SYS_PRI3_TICK_S    29
#define NVIC_SYS_PRI3_PENDSV_S  21
#define NVIC_SYS_PRI3_DEBUG_S   5

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_HND_CTRL
// register.
//
//*****************************************************************************
#define NVIC_SYS_HND_CTRL_USAGE 0x00040000  // Usage Fault Enable
#define NVIC_SYS_HND_CTRL_BUS   0x00020000  // Bus Fault Enable
#define NVIC_SYS_HND_CTRL_MEM   0x00010000  // Memory Management Fault Enable
#define NVIC_SYS_HND_CTRL_SVC   0x00008000  // SVC Call Pending
#define NVIC_SYS_HND_CTRL_BUSP  0x00004000  // Bus Fault Pending
#define NVIC_SYS_HND_CTRL_MEMP  0x00002000  // Memory Management Fault Pending
#define NVIC_SYS_HND_CTRL_USAGEP                                              \
                                0x00001000  // Usage Fault Pending
#define NVIC_SYS_HND_CTRL_TICK  0x00000800  // SysTick Exception Active
#define NVIC_SYS_HND_CTRL_PNDSV 0x00000400  // PendSV Exception Active
#define NVIC_SYS_HND_CTRL_MON   0x00000100  // Debug Monitor Active
#define NVIC_SYS_HND_CTRL_SVCA  0x00000080  // SVC Call Active
#define NVIC_SYS_HND_CTRL_USGA  0x00000008  // Usage Fault Active
#define NVIC_SYS_HND_CTRL_BUSA  0x00000002  // Bus Fault Active
#define NVIC_SYS_HND_CTRL_MEMA  0x00000001  // Memory Management Fault Active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_FAULT_STAT
// register.
//
//*****************************************************************************
#define NVIC_FAULT_STAT_DIV0    0x02000000  // Divide-by-Zero Usage Fault
#define NVIC_FAULT_STAT_UNALIGN 0x01000000  // Unaligned Access Usage Fault
#define NVIC_FAULT_STAT_NOCP    0x00080000  // No Coprocessor Usage Fault
#define NVIC_FAULT_STAT_INVPC   0x00040000  // Invalid PC Load Usage Fault
#define NVIC_FAULT_STAT_INVSTAT 0x00020000  // Invalid State Usage Fault
#define NVIC_FAULT_STAT_UNDEF   0x00010000  // Undefined Instruction Usage
// Fault
#define NVIC_FAULT_STAT_BFARV   0x00008000  // Bus Fault Address Register Valid
#define NVIC_FAULT_STAT_BLSPERR 0x00002000  // Bus Fault on Floating-Point Lazy
// State Preservation
#define NVIC_FAULT_STAT_BSTKE   0x00001000  // Stack Bus Fault
#define NVIC_FAULT_STAT_BUSTKE  0x00000800  // Unstack Bus Fault
#define NVIC_FAULT_STAT_IMPRE   0x00000400  // Imprecise Data Bus Error
#define NVIC_FAULT_STAT_PRECISE 0x00000200  // Precise Data Bus Error
#define NVIC_FAULT_STAT_IBUS    0x00000100  // Instruction Bus Error
#define NVIC_FAULT_STAT_MMARV   0x00000080  // Memory Management Fault Address
// Register Valid
#define NVIC_FAULT_STAT_MLSPERR 0x00000020  // Memory Management Fault on
// Floating-Point Lazy State
// Preservation
#define NVIC_FAULT_STAT_MSTKE   0x00000010  // Stack Access Violation
#define NVIC_FAULT_STAT_MUSTKE  0x00000008  // Unstack Access Violation
#define NVIC_FAULT_STAT_DERR    0x00000002  // Data Access Violation
#define NVIC_FAULT_STAT_IERR    0x00000001  // Instruction Access Violation

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_HFAULT_STAT
// register.
//
//*****************************************************************************
#define NVIC_HFAULT_STAT_DBG    0x80000000  // Debug Event
#define NVIC_HFAULT_STAT_FORCED 0x40000000  // Forced Hard Fault
#define NVIC_HFAULT_STAT_VECT   0x00000002  // Vector Table Read Fault

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DEBUG_STAT
// register.
//
//*****************************************************************************
#define NVIC_DEBUG_STAT_EXTRNL  0x00000010  // EDBGRQ asserted
#define NVIC_DEBUG_STAT_VCATCH  0x00000008  // Vector catch
#define NVIC_DEBUG_STAT_DWTTRAP 0x00000004  // DWT match
#define NVIC_DEBUG_STAT_BKPT    0x00000002  // Breakpoint instruction
#define NVIC_DEBUG_STAT_HALTED  0x00000001  // Halt request

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MM_ADDR register.
//
//*****************************************************************************
#define NVIC_MM_ADDR_M          0xFFFFFFFF  // Fault Address
#define NVIC_MM_ADDR_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_FAULT_ADDR
// register.
//
//*****************************************************************************
#define NVIC_FAULT_ADDR_M       0xFFFFFFFF  // Fault Address
#define NVIC_FAULT_ADDR_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_CPAC register.
//
//*****************************************************************************
#define NVIC_CPAC_CP11_M        0x00C00000  // CP11 Coprocessor Access
// Privilege
#define NVIC_CPAC_CP11_DIS      0x00000000  // Access Denied
#define NVIC_CPAC_CP11_PRIV     0x00400000  // Privileged Access Only
#define NVIC_CPAC_CP11_FULL     0x00C00000  // Full Access
#define NVIC_CPAC_CP10_M        0x00300000  // CP10 Coprocessor Access
// Privilege
#define NVIC_CPAC_CP10_DIS      0x00000000  // Access Denied
#define NVIC_CPAC_CP10_PRIV     0x00100000  // Privileged Access Only
#define NVIC_CPAC_CP10_FULL     0x00300000  // Full Access

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_TYPE register.
//
//*****************************************************************************
#define NVIC_MPU_TYPE_IREGION_M 0x00FF0000  // Number of I Regions
#define NVIC_MPU_TYPE_DREGION_M 0x0000FF00  // Number of D Regions
#define NVIC_MPU_TYPE_SEPARATE  0x00000001  // Separate or Unified MPU
#define NVIC_MPU_TYPE_IREGION_S 16
#define NVIC_MPU_TYPE_DREGION_S 8

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_CTRL register.
//
//*****************************************************************************
#define NVIC_MPU_CTRL_PRIVDEFEN 0x00000004  // MPU Default Region
#define NVIC_MPU_CTRL_HFNMIENA  0x00000002  // MPU Enabled During Faults
#define NVIC_MPU_CTRL_ENABLE    0x00000001  // MPU Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_NUMBER
// register.
//
//*****************************************************************************
#define NVIC_MPU_NUMBER_M       0x00000007  // MPU Region to Access
#define NVIC_MPU_NUMBER_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_BASE register.
//
//*****************************************************************************
#define NVIC_MPU_BASE_ADDR_M    0xFFFFFFE0  // Base Address Mask
#define NVIC_MPU_BASE_VALID     0x00000010  // Region Number Valid
#define NVIC_MPU_BASE_REGION_M  0x00000007  // Region Number
#define NVIC_MPU_BASE_ADDR_S    5
#define NVIC_MPU_BASE_REGION_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_ATTR register.
//
//*****************************************************************************
#define NVIC_MPU_ATTR_XN        0x10000000  // Instruction Access Disable
#define NVIC_MPU_ATTR_AP_M      0x07000000  // Access Privilege
#define NVIC_MPU_ATTR_TEX_M     0x00380000  // Type Extension Mask
#define NVIC_MPU_ATTR_SHAREABLE 0x00040000  // Shareable
#define NVIC_MPU_ATTR_CACHEABLE 0x00020000  // Cacheable
#define NVIC_MPU_ATTR_BUFFRABLE 0x00010000  // Bufferable
#define NVIC_MPU_ATTR_SRD_M     0x0000FF00  // Subregion Disable Bits
#define NVIC_MPU_ATTR_SIZE_M    0x0000003E  // Region Size Mask
#define NVIC_MPU_ATTR_ENABLE    0x00000001  // Region Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_BASE1 register.
//
//*****************************************************************************
#define NVIC_MPU_BASE1_ADDR_M   0xFFFFFFE0  // Base Address Mask
#define NVIC_MPU_BASE1_VALID    0x00000010  // Region Number Valid
#define NVIC_MPU_BASE1_REGION_M 0x00000007  // Region Number
#define NVIC_MPU_BASE1_ADDR_S   5
#define NVIC_MPU_BASE1_REGION_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_ATTR1 register.
//
//*****************************************************************************
#define NVIC_MPU_ATTR1_XN       0x10000000  // Instruction Access Disable
#define NVIC_MPU_ATTR1_AP_M     0x07000000  // Access Privilege
#define NVIC_MPU_ATTR1_TEX_M    0x00380000  // Type Extension Mask
#define NVIC_MPU_ATTR1_SHAREABLE                                              \
                                0x00040000  // Shareable
#define NVIC_MPU_ATTR1_CACHEABLE                                              \
                                0x00020000  // Cacheable
#define NVIC_MPU_ATTR1_BUFFRABLE                                              \
                                0x00010000  // Bufferable
#define NVIC_MPU_ATTR1_SRD_M    0x0000FF00  // Subregion Disable Bits
#define NVIC_MPU_ATTR1_SIZE_M   0x0000003E  // Region Size Mask
#define NVIC_MPU_ATTR1_ENABLE   0x00000001  // Region Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_BASE2 register.
//
//*****************************************************************************
#define NVIC_MPU_BASE2_ADDR_M   0xFFFFFFE0  // Base Address Mask
#define NVIC_MPU_BASE2_VALID    0x00000010  // Region Number Valid
#define NVIC_MPU_BASE2_REGION_M 0x00000007  // Region Number
#define NVIC_MPU_BASE2_ADDR_S   5
#define NVIC_MPU_BASE2_REGION_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_ATTR2 register.
//
//*****************************************************************************
#define NVIC_MPU_ATTR2_XN       0x10000000  // Instruction Access Disable
#define NVIC_MPU_ATTR2_AP_M     0x07000000  // Access Privilege
#define NVIC_MPU_ATTR2_TEX_M    0x00380000  // Type Extension Mask
#define NVIC_MPU_ATTR2_SHAREABLE                                              \
                                0x00040000  // Shareable
#define NVIC_MPU_ATTR2_CACHEABLE                                              \
                                0x00020000  // Cacheable
#define NVIC_MPU_ATTR2_BUFFRABLE                                              \
                                0x00010000  // Bufferable
#define NVIC_MPU_ATTR2_SRD_M    0x0000FF00  // Subregion Disable Bits
#define NVIC_MPU_ATTR2_SIZE_M   0x0000003E  // Region Size Mask
#define NVIC_MPU_ATTR2_ENABLE   0x00000001  // Region Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_BASE3 register.
//
//*****************************************************************************
#define NVIC_MPU_BASE3_ADDR_M   0xFFFFFFE0  // Base Address Mask
#define NVIC_MPU_BASE3_VALID    0x00000010  // Region Number Valid
#define NVIC_MPU_BASE3_REGION_M 0x00000007  // Region Number
#define NVIC_MPU_BASE3_ADDR_S   5
#define NVIC_MPU_BASE3_REGION_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_ATTR3 register.
//
//*****************************************************************************
#define NVIC_MPU_ATTR3_XN       0x10000000  // Instruction Access Disable
#define NVIC_MPU_ATTR3_AP_M     0x07000000  // Access Privilege
#define NVIC_MPU_ATTR3_TEX_M    0x00380000  // Type Extension Mask
#define NVIC_MPU_ATTR3_SHAREABLE                                              \
                                0x00040000  // Shareable
#define NVIC_MPU_ATTR3_CACHEABLE                                              \
                                0x00020000  // Cacheable
#define NVIC_MPU_ATTR3_BUFFRABLE                                              \
                                0x00010000  // Bufferable
#define NVIC_MPU_ATTR3_SRD_M    0x0000FF00  // Subregion Disable Bits
#define NVIC_MPU_ATTR3_SIZE_M   0x0000003E  // Region Size Mask
#define NVIC_MPU_ATTR3_ENABLE   0x00000001  // Region Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DBG_CTRL register.
//
//*****************************************************************************
#define NVIC_DBG_CTRL_DBGKEY_M  0xFFFF0000  // Debug key mask
#define NVIC_DBG_CTRL_DBGKEY    0xA05F0000  // Debug key
#define NVIC_DBG_CTRL_S_RESET_ST                                              \
                                0x02000000  // Core has reset since last read
#define NVIC_DBG_CTRL_S_RETIRE_ST                                             \
                                0x01000000  // Core has executed insruction
// since last read
#define NVIC_DBG_CTRL_S_LOCKUP  0x00080000  // Core is locked up
#define NVIC_DBG_CTRL_S_SLEEP   0x00040000  // Core is sleeping
#define NVIC_DBG_CTRL_S_HALT    0x00020000  // Core status on halt
#define NVIC_DBG_CTRL_S_REGRDY  0x00010000  // Register read/write available
#define NVIC_DBG_CTRL_C_SNAPSTALL                                             \
                                0x00000020  // Breaks a stalled load/store
#define NVIC_DBG_CTRL_C_MASKINT 0x00000008  // Mask interrupts when stepping
#define NVIC_DBG_CTRL_C_STEP    0x00000004  // Step the core
#define NVIC_DBG_CTRL_C_HALT    0x00000002  // Halt the core
#define NVIC_DBG_CTRL_C_DEBUGEN 0x00000001  // Enable debug

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DBG_XFER register.
//
//*****************************************************************************
#define NVIC_DBG_XFER_REG_WNR   0x00010000  // Write or not read
#define NVIC_DBG_XFER_REG_SEL_M 0x0000001F  // Register
#define NVIC_DBG_XFER_REG_R0    0x00000000  // Register R0
#define NVIC_DBG_XFER_REG_R1    0x00000001  // Register R1
#define NVIC_DBG_XFER_REG_R2    0x00000002  // Register R2
#define NVIC_DBG_XFER_REG_R3    0x00000003  // Register R3
#define NVIC_DBG_XFER_REG_R4    0x00000004  // Register R4
#define NVIC_DBG_XFER_REG_R5    0x00000005  // Register R5
#define NVIC_DBG_XFER_REG_R6    0x00000006  // Register R6
#define NVIC_DBG_XFER_REG_R7    0x00000007  // Register R7
#define NVIC_DBG_XFER_REG_R8    0x00000008  // Register R8
#define NVIC_DBG_XFER_REG_R9    0x00000009  // Register R9
#define NVIC_DBG_XFER_REG_R10   0x0000000A  // Register R10
#define NVIC_DBG_XFER_REG_R11   0x0000000B  // Register R11
#define NVIC_DBG_XFER_REG_R12   0x0000000C  // Register R12
#define NVIC_DBG_XFER_REG_R13   0x0000000D  // Register R13
#define NVIC_DBG_XFER_REG_R14   0x0000000E  // Register R14
#define NVIC_DBG_XFER_REG_R15   0x0000000F  // Register R15
#define NVIC_DBG_XFER_REG_FLAGS 0x00000010  // xPSR/Flags register
#define NVIC_DBG_XFER_REG_MSP   0x00000011  // Main SP
#define NVIC_DBG_XFER_REG_PSP   0x00000012  // Process SP
#define NVIC_DBG_XFER_REG_DSP   0x00000013  // Deep SP
#define NVIC_DBG_XFER_REG_CFBP  0x00000014  // Control/Fault/BasePri/PriMask

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DBG_DATA register.
//
//*****************************************************************************
#define NVIC_DBG_DATA_M         0xFFFFFFFF  // Data temporary cache
#define NVIC_DBG_DATA_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DBG_INT register.
//
//*****************************************************************************
#define NVIC_DBG_INT_HARDERR    0x00000400  // Debug trap on hard fault
#define NVIC_DBG_INT_INTERR     0x00000200  // Debug trap on interrupt errors
#define NVIC_DBG_INT_BUSERR     0x00000100  // Debug trap on bus error
#define NVIC_DBG_INT_STATERR    0x00000080  // Debug trap on usage fault state
#define NVIC_DBG_INT_CHKERR     0x00000040  // Debug trap on usage fault check
#define NVIC_DBG_INT_NOCPERR    0x00000020  // Debug trap on coprocessor error
#define NVIC_DBG_INT_MMERR      0x00000010  // Debug trap on mem manage fault
#define NVIC_DBG_INT_RESET      0x00000008  // Core reset status
#define NVIC_DBG_INT_RSTPENDCLR 0x00000004  // Clear pending core reset
#define NVIC_DBG_INT_RSTPENDING 0x00000002  // Core reset is pending
#define NVIC_DBG_INT_RSTVCATCH  0x00000001  // Reset vector catch

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SW_TRIG register.
//
//*****************************************************************************
#define NVIC_SW_TRIG_INTID_M    0x000000FF  // Interrupt ID
#define NVIC_SW_TRIG_INTID_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_FPCC register.
//
//*****************************************************************************
#define NVIC_FPCC_ASPEN         0x80000000  // Automatic State Preservation
// Enable
#define NVIC_FPCC_LSPEN         0x40000000  // Lazy State Preservation Enable
#define NVIC_FPCC_MONRDY        0x00000100  // Monitor Ready
#define NVIC_FPCC_BFRDY         0x00000040  // Bus Fault Ready
#define NVIC_FPCC_MMRDY         0x00000020  // Memory Management Fault Ready
#define NVIC_FPCC_HFRDY         0x00000010  // Hard Fault Ready
#define NVIC_FPCC_THREAD        0x00000008  // Thread Mode
#define NVIC_FPCC_USER          0x00000002  // User Privilege Level
#define NVIC_FPCC_LSPACT        0x00000001  // Lazy State Preservation Active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_FPCA register.
//
//*****************************************************************************
#define NVIC_FPCA_ADDRESS_M     0xFFFFFFF8  // Address
#define NVIC_FPCA_ADDRESS_S     3

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_FPDSC register.
//
//*****************************************************************************
#define NVIC_FPDSC_AHP          0x04000000  // AHP Bit Default
#define NVIC_FPDSC_DN           0x02000000  // DN Bit Default
#define NVIC_FPDSC_FZ           0x01000000  // FZ Bit Default
#define NVIC_FPDSC_RMODE_M      0x00C00000  // RMODE Bit Default
#define NVIC_FPDSC_RMODE_RN     0x00000000  // Round to Nearest (RN) mode
#define NVIC_FPDSC_RMODE_RP     0x00400000  // Round towards Plus Infinity (RP)
// mode
#define NVIC_FPDSC_RMODE_RM     0x00800000  // Round towards Minus Infinity
// (RM) mode
#define NVIC_FPDSC_RMODE_RZ     0x00C00000  // Round towards Zero (RZ) mode

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_CFG register.
//
//*****************************************************************************
#define EMAC_CFG_TWOKPEN        0x08000000  // IEEE 802
#define EMAC_CFG_CST            0x02000000  // CRC Stripping for Type Frames
#define EMAC_CFG_WDDIS          0x00800000  // Watchdog Disable
#define EMAC_CFG_JD             0x00400000  // Jabber Disable
#define EMAC_CFG_JFEN           0x00100000  // Jumbo Frame Enable
#define EMAC_CFG_IFG_M          0x000E0000  // Inter-Frame Gap (IFG)
#define EMAC_CFG_IFG_96         0x00000000  // 96 bit times
#define EMAC_CFG_IFG_88         0x00020000  // 88 bit times
#define EMAC_CFG_IFG_80         0x00040000  // 80 bit times
#define EMAC_CFG_IFG_72         0x00060000  // 72 bit times
#define EMAC_CFG_IFG_64         0x00080000  // 64 bit times
#define EMAC_CFG_IFG_56         0x000A0000  // 56 bit times
#define EMAC_CFG_IFG_48         0x000C0000  // 48 bit times
#define EMAC_CFG_IFG_40         0x000E0000  // 40 bit times
#define EMAC_CFG_DISCRS         0x00010000  // Disable Carrier Sense During
// Transmission
#define EMAC_CFG_PS             0x00008000  // Port Select
#define EMAC_CFG_FES            0x00004000  // Speed
#define EMAC_CFG_DRO            0x00002000  // Disable Receive Own
#define EMAC_CFG_LOOPBM         0x00001000  // Loopback Mode
#define EMAC_CFG_DUPM           0x00000800  // Duplex Mode
#define EMAC_CFG_IPC            0x00000400  // Checksum Offload
#define EMAC_CFG_DR             0x00000200  // Disable Retry
#define EMAC_CFG_ACS            0x00000080  // Automatic Pad or CRC Stripping
#define EMAC_CFG_BL_M           0x00000060  // Back-Off Limit
#define EMAC_CFG_BL_1024        0x00000000  // k = min (n,10)
#define EMAC_CFG_BL_256         0x00000020  // k = min (n,8)
#define EMAC_CFG_BL_8           0x00000040  // k = min (n,4)
#define EMAC_CFG_BL_2           0x00000060  // k = min (n,1)
#define EMAC_CFG_DC             0x00000010  // Deferral Check
#define EMAC_CFG_TE             0x00000008  // Transmitter Enable
#define EMAC_CFG_RE             0x00000004  // Receiver Enable
#define EMAC_CFG_PRELEN_M       0x00000003  // Preamble Length for Transmit
// Frames
#define EMAC_CFG_PRELEN_7       0x00000000  // 7 bytes of preamble
#define EMAC_CFG_PRELEN_5       0x00000001  // 5 bytes of preamble
#define EMAC_CFG_PRELEN_3       0x00000002  // 3 bytes of preamble

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_FRAMEFLTR
// register.
//
//*****************************************************************************
#define EMAC_FRAMEFLTR_RA       0x80000000  // Receive All
#define EMAC_FRAMEFLTR_VTFE     0x00010000  // VLAN Tag Filter Enable
#define EMAC_FRAMEFLTR_HPF      0x00000400  // Hash or Perfect Filter
#define EMAC_FRAMEFLTR_SAF      0x00000200  // Source Address Filter Enable
#define EMAC_FRAMEFLTR_SAIF     0x00000100  // Source Address (SA) Inverse
// Filtering
#define EMAC_FRAMEFLTR_PCF_M    0x000000C0  // Pass Control Frames
#define EMAC_FRAMEFLTR_PCF_ALL  0x00000000  // The MAC filters all control
// frames from reaching application
#define EMAC_FRAMEFLTR_PCF_PAUSE                                              \
                                0x00000040  // MAC forwards all control frames
// except PAUSE control frames to
// application even if they fail
// the address filter
#define EMAC_FRAMEFLTR_PCF_NONE 0x00000080  // MAC forwards all control frames
// to application even if they fail
// the address Filter
#define EMAC_FRAMEFLTR_PCF_ADDR 0x000000C0  // MAC forwards control frames that
// pass the address Filter
#define EMAC_FRAMEFLTR_DBF      0x00000020  // Disable Broadcast Frames
#define EMAC_FRAMEFLTR_PM       0x00000010  // Pass All Multicast
#define EMAC_FRAMEFLTR_DAIF     0x00000008  // Destination Address (DA) Inverse
// Filtering
#define EMAC_FRAMEFLTR_HMC      0x00000004  // Hash Multicast
#define EMAC_FRAMEFLTR_HUC      0x00000002  // Hash Unicast
#define EMAC_FRAMEFLTR_PR       0x00000001  // Promiscuous Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_HASHTBLH
// register.
//
//*****************************************************************************
#define EMAC_HASHTBLH_HTH_M     0xFFFFFFFF  // Hash Table High
#define EMAC_HASHTBLH_HTH_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_HASHTBLL
// register.
//
//*****************************************************************************
#define EMAC_HASHTBLL_HTL_M     0xFFFFFFFF  // Hash Table Low
#define EMAC_HASHTBLL_HTL_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_MIIADDR register.
//
//*****************************************************************************
#define EMAC_MIIADDR_PLA_M      0x0000F800  // Physical Layer Address
#define EMAC_MIIADDR_MII_M      0x000007C0  // MII Register
#define EMAC_MIIADDR_CR_M       0x0000003C  // Clock Reference Frequency
// Selection
#define EMAC_MIIADDR_CR_60_100  0x00000000  // The frequency of the System
// Clock is 60 to 100 MHz providing
// a MDIO clock of SYSCLK/42
#define EMAC_MIIADDR_CR_100_150 0x00000004  // The frequency of the System
// Clock is 100 to 150 MHz
// providing a MDIO clock of
// SYSCLK/62
#define EMAC_MIIADDR_CR_20_35   0x00000008  // The frequency of the System
// Clock is 20-35 MHz providing a
// MDIO clock of System Clock/16
#define EMAC_MIIADDR_CR_35_60   0x0000000C  // The frequency of the System
// Clock is 35 to 60 MHz providing
// a MDIO clock of System Clock/26
#define EMAC_MIIADDR_MIIW       0x00000002  // MII Write
#define EMAC_MIIADDR_MIIB       0x00000001  // MII Busy
#define EMAC_MIIADDR_PLA_S      11
#define EMAC_MIIADDR_MII_S      6

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_MIIDATA register.
//
//*****************************************************************************
#define EMAC_MIIDATA_DATA_M     0x0000FFFF  // MII Data
#define EMAC_MIIDATA_DATA_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_FLOWCTL register.
//
//*****************************************************************************
#define EMAC_FLOWCTL_PT_M       0xFFFF0000  // Pause Time
#define EMAC_FLOWCTL_DZQP       0x00000080  // Disable Zero-Quanta Pause
#define EMAC_FLOWCTL_UP         0x00000008  // Unicast Pause Frame Detect
#define EMAC_FLOWCTL_RFE        0x00000004  // Receive Flow Control Enable
#define EMAC_FLOWCTL_TFE        0x00000002  // Transmit Flow Control Enable
#define EMAC_FLOWCTL_FCBBPA     0x00000001  // Flow Control Busy or
// Back-pressure Activate
#define EMAC_FLOWCTL_PT_S       16

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_VLANTG register.
//
//*****************************************************************************
#define EMAC_VLANTG_VTHM        0x00080000  // VLAN Tag Hash Table Match Enable
#define EMAC_VLANTG_ESVL        0x00040000  // Enable S-VLAN
#define EMAC_VLANTG_VTIM        0x00020000  // VLAN Tag Inverse Match Enable
#define EMAC_VLANTG_ETV         0x00010000  // Enable 12-Bit VLAN Tag
// Comparison
#define EMAC_VLANTG_VL_M        0x0000FFFF  // VLAN Tag Identifier for Receive
// Frames
#define EMAC_VLANTG_VL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_STATUS register.
//
//*****************************************************************************
#define EMAC_STATUS_TXFF        0x02000000  // TX/RX Controller TX FIFO Full
// Status
#define EMAC_STATUS_TXFE        0x01000000  // TX/RX Controller TX FIFO Not
// Empty Status
#define EMAC_STATUS_TWC         0x00400000  // TX/RX Controller TX FIFO Write
// Controller Active Status
#define EMAC_STATUS_TRC_M       0x00300000  // TX/RX Controller's TX FIFO Read
// Controller Status
#define EMAC_STATUS_TRC_IDLE    0x00000000  // IDLE state
#define EMAC_STATUS_TRC_READ    0x00100000  // READ state (transferring data to
// MAC transmitter)
#define EMAC_STATUS_TRC_WAIT    0x00200000  // Waiting for TX Status from MAC
// transmitter
#define EMAC_STATUS_TRC_WRFLUSH 0x00300000  // Writing the received TX Status
// or flushing the TX FIFO
#define EMAC_STATUS_TXPAUSED    0x00080000  // MAC Transmitter PAUSE
#define EMAC_STATUS_TFC_M       0x00060000  // MAC Transmit Frame Controller
// Status
#define EMAC_STATUS_TFC_IDLE    0x00000000  // IDLE state
#define EMAC_STATUS_TFC_STATUS  0x00020000  // Waiting for status of previous
// frame or IFG or backoff period
// to be over
#define EMAC_STATUS_TFC_PAUSE   0x00040000  // Generating and transmitting a
// PAUSE control frame (in the
// full-duplex mode)
#define EMAC_STATUS_TFC_INPUT   0x00060000  // Transferring input frame for
// transmission
#define EMAC_STATUS_TPE         0x00010000  // MAC MII Transmit Protocol Engine
// Status
#define EMAC_STATUS_RXF_M       0x00000300  // TX/RX Controller RX FIFO
// Fill-level Status
#define EMAC_STATUS_RXF_EMPTY   0x00000000  // RX FIFO Empty
#define EMAC_STATUS_RXF_BELOW   0x00000100  // RX FIFO fill level is below the
// flow-control deactivate
// threshold
#define EMAC_STATUS_RXF_ABOVE   0x00000200  // RX FIFO fill level is above the
// flow-control activate threshold
#define EMAC_STATUS_RXF_FULL    0x00000300  // RX FIFO Full
#define EMAC_STATUS_RRC_M       0x00000060  // TX/RX Controller Read Controller
// State
#define EMAC_STATUS_RRC_IDLE    0x00000000  // IDLE state
#define EMAC_STATUS_RRC_STATUS  0x00000020  // Reading frame data
#define EMAC_STATUS_RRC_DATA    0x00000040  // Reading frame status (or
// timestamp)
#define EMAC_STATUS_RRC_FLUSH   0x00000060  // Flushing the frame data and
// status
#define EMAC_STATUS_RWC         0x00000010  // TX/RX Controller RX FIFO Write
// Controller Active Status
#define EMAC_STATUS_RFCFC_M     0x00000006  // MAC Receive Frame Controller
// FIFO Status
#define EMAC_STATUS_RPE         0x00000001  // MAC MII Receive Protocol Engine
// Status
#define EMAC_STATUS_RFCFC_S     1

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RWUFF register.
//
//*****************************************************************************
#define EMAC_RWUFF_WAKEUPFIL_M  0xFFFFFFFF  // Remote Wake-Up Frame Filter
#define EMAC_RWUFF_WAKEUPFIL_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_PMTCTLSTAT
// register.
//
//*****************************************************************************
#define EMAC_PMTCTLSTAT_WUPFRRST                                              \
                                0x80000000  // Wake-Up Frame Filter Register
// Pointer Reset
#define EMAC_PMTCTLSTAT_RWKPTR_M                                              \
                                0x07000000  // Remote Wake-Up FIFO Pointer
#define EMAC_PMTCTLSTAT_GLBLUCAST                                             \
                                0x00000200  // Global Unicast
#define EMAC_PMTCTLSTAT_WUPRX   0x00000040  // Wake-Up Frame Received
#define EMAC_PMTCTLSTAT_MGKPRX  0x00000020  // Magic Packet Received
#define EMAC_PMTCTLSTAT_WUPFREN 0x00000004  // Wake-Up Frame Enable
#define EMAC_PMTCTLSTAT_MGKPKTEN                                              \
                                0x00000002  // Magic Packet Enable
#define EMAC_PMTCTLSTAT_PWRDWN  0x00000001  // Power Down
#define EMAC_PMTCTLSTAT_RWKPTR_S                                              \
                                24

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_LPICTLSTAT
// register.
//
//*****************************************************************************
#define EMAC_LPICTLSTAT_LPITXA  0x00080000  // LPI TX Automate
#define EMAC_LPICTLSTAT_PLSEN   0x00040000  // PHY Link Status Enable
#define EMAC_LPICTLSTAT_PLS     0x00020000  // PHY Link Status
#define EMAC_LPICTLSTAT_LPIEN   0x00010000  // LPI Enable
#define EMAC_LPICTLSTAT_RLPIST  0x00000200  // Receive LPI State
#define EMAC_LPICTLSTAT_TLPIST  0x00000100  // Transmit LPI State
#define EMAC_LPICTLSTAT_RLPIEX  0x00000008  // Receive LPI Exit
#define EMAC_LPICTLSTAT_RLPIEN  0x00000004  // Receive LPI Entry
#define EMAC_LPICTLSTAT_TLPIEX  0x00000002  // Transmit LPI Exit
#define EMAC_LPICTLSTAT_TLPIEN  0x00000001  // Transmit LPI Entry

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_LPITIMERCTL
// register.
//
//*****************************************************************************
#define EMAC_LPITIMERCTL_LST_M  0x03FF0000  // Low Power Idle LS Timer
#define EMAC_LPITIMERCTL_LST_S  16
#define EMAC_LPITIMERCTL_TWT_M  0x0000FFFF  // Low Power Idle TW Timer
#define EMAC_LPITIMERCTL_TWT_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RIS register.
//
//*****************************************************************************
#define EMAC_RIS_LPI            0x00000400  // LPI Interrupt Status
#define EMAC_RIS_TS             0x00000200  // Timestamp Interrupt Status
#define EMAC_RIS_MMCTX          0x00000040  // MMC Transmit Interrupt Status
#define EMAC_RIS_MMCRX          0x00000020  // MMC Receive Interrupt Status
#define EMAC_RIS_MMC            0x00000010  // MMC Interrupt Status
#define EMAC_RIS_PMT            0x00000008  // PMT Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_IM register.
//
//*****************************************************************************
#define EMAC_IM_LPI             0x00000400  // LPI Interrupt Mask
#define EMAC_IM_TSI             0x00000200  // Timestamp Interrupt Mask
#define EMAC_IM_PMT             0x00000008  // PMT Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_ADDR0H register.
//
//*****************************************************************************
#define EMAC_ADDR0H_AE          0x80000000  // Address Enable
#define EMAC_ADDR0H_ADDRHI_M    0x0000FFFF  // MAC Address0 [47:32]
#define EMAC_ADDR0H_ADDRHI_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_ADDR0L register.
//
//*****************************************************************************
#define EMAC_ADDR0L_ADDRLO_M    0xFFFFFFFF  // MAC Address0 [31:0]
#define EMAC_ADDR0L_ADDRLO_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_ADDR1H register.
//
//*****************************************************************************
#define EMAC_ADDR1H_AE          0x80000000  // Address Enable
#define EMAC_ADDR1H_SA          0x40000000  // Source Address
#define EMAC_ADDR1H_MBC_M       0x3F000000  // Mask Byte Control
#define EMAC_ADDR1H_ADDRHI_M    0x0000FFFF  // MAC Address1 [47:32]
#define EMAC_ADDR1H_MBC_S       24
#define EMAC_ADDR1H_ADDRHI_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_ADDR1L register.
//
//*****************************************************************************
#define EMAC_ADDR1L_ADDRLO_M    0xFFFFFFFF  // MAC Address1 [31:0]
#define EMAC_ADDR1L_ADDRLO_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_ADDR2H register.
//
//*****************************************************************************
#define EMAC_ADDR2H_AE          0x80000000  // Address Enable
#define EMAC_ADDR2H_SA          0x40000000  // Source Address
#define EMAC_ADDR2H_MBC_M       0x3F000000  // Mask Byte Control
#define EMAC_ADDR2H_ADDRHI_M    0x0000FFFF  // MAC Address2 [47:32]
#define EMAC_ADDR2H_MBC_S       24
#define EMAC_ADDR2H_ADDRHI_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_ADDR2L register.
//
//*****************************************************************************
#define EMAC_ADDR2L_ADDRLO_M    0xFFFFFFFF  // MAC Address2 [31:0]
#define EMAC_ADDR2L_ADDRLO_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_ADDR3H register.
//
//*****************************************************************************
#define EMAC_ADDR3H_AE          0x80000000  // Address Enable
#define EMAC_ADDR3H_SA          0x40000000  // Source Address
#define EMAC_ADDR3H_MBC_M       0x3F000000  // Mask Byte Control
#define EMAC_ADDR3H_ADDRHI_M    0x0000FFFF  // MAC Address3 [47:32]
#define EMAC_ADDR3H_MBC_S       24
#define EMAC_ADDR3H_ADDRHI_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_ADDR3L register.
//
//*****************************************************************************
#define EMAC_ADDR3L_ADDRLO_M    0xFFFFFFFF  // MAC Address3 [31:0]
#define EMAC_ADDR3L_ADDRLO_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_WDOGTO register.
//
//*****************************************************************************
#define EMAC_WDOGTO_PWE         0x00010000  // Programmable Watchdog Enable
#define EMAC_WDOGTO_WTO_M       0x00003FFF  // Watchdog Timeout
#define EMAC_WDOGTO_WTO_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_MMCCTRL register.
//
//*****************************************************************************
#define EMAC_MMCCTRL_UCDBC      0x00000100  // Update MMC Counters for Dropped
// Broadcast Frames
#define EMAC_MMCCTRL_CNTPRSTLVL 0x00000020  // Full/Half Preset Level Value
#define EMAC_MMCCTRL_CNTPRST    0x00000010  // Counters Preset
#define EMAC_MMCCTRL_CNTFREEZ   0x00000008  // MMC Counter Freeze
#define EMAC_MMCCTRL_RSTONRD    0x00000004  // Reset on Read
#define EMAC_MMCCTRL_CNTSTPRO   0x00000002  // Counters Stop Rollover
#define EMAC_MMCCTRL_CNTRST     0x00000001  // Counters Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_MMCRXRIS
// register.
//
//*****************************************************************************
#define EMAC_MMCRXRIS_UCGF      0x00020000  // MMC Receive Unicast Good Frame
// Counter Interrupt Status
#define EMAC_MMCRXRIS_ALGNERR   0x00000040  // MMC Receive Alignment Error
// Frame Counter Interrupt Status
#define EMAC_MMCRXRIS_CRCERR    0x00000020  // MMC Receive CRC Error Frame
// Counter Interrupt Status
#define EMAC_MMCRXRIS_GBF       0x00000001  // MMC Receive Good Bad Frame
// Counter Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_MMCTXRIS
// register.
//
//*****************************************************************************
#define EMAC_MMCTXRIS_OCTCNT    0x00100000  // Octet Counter Interrupt Status
#define EMAC_MMCTXRIS_MCOLLGF   0x00008000  // MMC Transmit Multiple Collision
// Good Frame Counter Interrupt
// Status
#define EMAC_MMCTXRIS_SCOLLGF   0x00004000  // MMC Transmit Single Collision
// Good Frame Counter Interrupt
// Status
#define EMAC_MMCTXRIS_GBF       0x00000002  // MMC Transmit Good Bad Frame
// Counter Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_MMCRXIM register.
//
//*****************************************************************************
#define EMAC_MMCRXIM_UCGF       0x00020000  // MMC Receive Unicast Good Frame
// Counter Interrupt Mask
#define EMAC_MMCRXIM_ALGNERR    0x00000040  // MMC Receive Alignment Error
// Frame Counter Interrupt Mask
#define EMAC_MMCRXIM_CRCERR     0x00000020  // MMC Receive CRC Error Frame
// Counter Interrupt Mask
#define EMAC_MMCRXIM_GBF        0x00000001  // MMC Receive Good Bad Frame
// Counter Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_MMCTXIM register.
//
//*****************************************************************************
#define EMAC_MMCTXIM_OCTCNT     0x00100000  // MMC Transmit Good Octet Counter
// Interrupt Mask
#define EMAC_MMCTXIM_MCOLLGF    0x00008000  // MMC Transmit Multiple Collision
// Good Frame Counter Interrupt
// Mask
#define EMAC_MMCTXIM_SCOLLGF    0x00004000  // MMC Transmit Single Collision
// Good Frame Counter Interrupt
// Mask
#define EMAC_MMCTXIM_GBF        0x00000002  // MMC Transmit Good Bad Frame
// Counter Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TXCNTGB register.
//
//*****************************************************************************
#define EMAC_TXCNTGB_TXFRMGB_M  0xFFFFFFFF  // This field indicates the number
// of good and bad frames
// transmitted, exclusive of
// retried frames
#define EMAC_TXCNTGB_TXFRMGB_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TXCNTSCOL
// register.
//
//*****************************************************************************
#define EMAC_TXCNTSCOL_TXSNGLCOLG_M                                           \
                                0xFFFFFFFF  // This field indicates the number
// of successfully transmitted
// frames after a single collision
// in the half-duplex mode
#define EMAC_TXCNTSCOL_TXSNGLCOLG_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TXCNTMCOL
// register.
//
//*****************************************************************************
#define EMAC_TXCNTMCOL_TXMULTCOLG_M                                           \
                                0xFFFFFFFF  // This field indicates the number
// of successfully transmitted
// frames after multiple collisions
// in the half-duplex mode
#define EMAC_TXCNTMCOL_TXMULTCOLG_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TXOCTCNTG
// register.
//
//*****************************************************************************
#define EMAC_TXOCTCNTG_TXOCTG_M 0xFFFFFFFF  // This field indicates the number
// of bytes transmitted, exclusive
// of preamble, in good frames
#define EMAC_TXOCTCNTG_TXOCTG_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RXCNTGB register.
//
//*****************************************************************************
#define EMAC_RXCNTGB_RXFRMGB_M  0xFFFFFFFF  // This field indicates the number
// of received good and bad frames
#define EMAC_RXCNTGB_RXFRMGB_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RXCNTCRCERR
// register.
//
//*****************************************************************************
#define EMAC_RXCNTCRCERR_RXCRCERR_M                                           \
                                0xFFFFFFFF  // This field indicates the number
// of frames received with CRC
// error
#define EMAC_RXCNTCRCERR_RXCRCERR_S                                           \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RXCNTALGNERR
// register.
//
//*****************************************************************************
#define EMAC_RXCNTALGNERR_RXALGNERR_M                                         \
                                0xFFFFFFFF  // This field indicates the number
// of frames received with
// alignment (dribble) error
#define EMAC_RXCNTALGNERR_RXALGNERR_S                                         \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RXCNTGUNI
// register.
//
//*****************************************************************************
#define EMAC_RXCNTGUNI_RXUCASTG_M                                             \
                                0xFFFFFFFF  // This field indicates the number
// of received good unicast frames
#define EMAC_RXCNTGUNI_RXUCASTG_S                                             \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_VLNINCREP
// register.
//
//*****************************************************************************
#define EMAC_VLNINCREP_CSVL     0x00080000  // C-VLAN or S-VLAN
#define EMAC_VLNINCREP_VLP      0x00040000  // VLAN Priority Control
#define EMAC_VLNINCREP_VLC_M    0x00030000  // VLAN Tag Control in Transmit
// Frames
#define EMAC_VLNINCREP_VLC_NONE 0x00000000  // No VLAN tag deletion, insertion,
// or replacement
#define EMAC_VLNINCREP_VLC_TAGDEL                                             \
                                0x00010000  // VLAN tag deletion
#define EMAC_VLNINCREP_VLC_TAGINS                                             \
                                0x00020000  // VLAN tag insertion
#define EMAC_VLNINCREP_VLC_TAGREP                                             \
                                0x00030000  // VLAN tag replacement
#define EMAC_VLNINCREP_VLT_M    0x0000FFFF  // VLAN Tag for Transmit Frames
#define EMAC_VLNINCREP_VLT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_VLANHASH
// register.
//
//*****************************************************************************
#define EMAC_VLANHASH_VLHT_M    0x0000FFFF  // VLAN Hash Table
#define EMAC_VLANHASH_VLHT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TIMSTCTRL
// register.
//
//*****************************************************************************
#define EMAC_TIMSTCTRL_PTPFLTR  0x00040000  // Enable MAC address for PTP Frame
// Filtering
#define EMAC_TIMSTCTRL_SELPTP_M 0x00030000  // Select PTP packets for Taking
// Snapshots
#define EMAC_TIMSTCTRL_TSMAST   0x00008000  // Enable Snapshot for Messages
// Relevant to Master
#define EMAC_TIMSTCTRL_TSEVNT   0x00004000  // Enable Timestamp Snapshot for
// Event Messages
#define EMAC_TIMSTCTRL_PTPIPV4  0x00002000  // Enable Processing of PTP Frames
// Sent over IPv4-UDP
#define EMAC_TIMSTCTRL_PTPIPV6  0x00001000  // Enable Processing of PTP Frames
// Sent Over IPv6-UDP
#define EMAC_TIMSTCTRL_PTPETH   0x00000800  // Enable Processing of PTP Over
// Ethernet Frames
#define EMAC_TIMSTCTRL_PTPVER2  0x00000400  // Enable PTP Packet Processing For
// Version 2 Format
#define EMAC_TIMSTCTRL_DGTLBIN  0x00000200  // Timestamp Digital or Binary
// Rollover Control
#define EMAC_TIMSTCTRL_ALLF     0x00000100  // Enable Timestamp For All Frames
#define EMAC_TIMSTCTRL_ADDREGUP 0x00000020  // Addend Register Update
#define EMAC_TIMSTCTRL_INTTRIG  0x00000010  // Timestamp Interrupt Trigger
// Enable
#define EMAC_TIMSTCTRL_TSUPDT   0x00000008  // Timestamp Update
#define EMAC_TIMSTCTRL_TSINIT   0x00000004  // Timestamp Initialize
#define EMAC_TIMSTCTRL_TSFCUPDT 0x00000002  // Timestamp Fine or Coarse Update
#define EMAC_TIMSTCTRL_TSEN     0x00000001  // Timestamp Enable
#define EMAC_TIMSTCTRL_SELPTP_S 16

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_SUBSECINC
// register.
//
//*****************************************************************************
#define EMAC_SUBSECINC_SSINC_M  0x000000FF  // Sub-second Increment Value
#define EMAC_SUBSECINC_SSINC_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TIMSEC register.
//
//*****************************************************************************
#define EMAC_TIMSEC_TSS_M       0xFFFFFFFF  // Timestamp Second
#define EMAC_TIMSEC_TSS_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TIMNANO register.
//
//*****************************************************************************
#define EMAC_TIMNANO_TSSS_M     0x7FFFFFFF  // Timestamp Sub-Seconds
#define EMAC_TIMNANO_TSSS_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TIMSECU register.
//
//*****************************************************************************
#define EMAC_TIMSECU_TSS_M      0xFFFFFFFF  // Timestamp Second
#define EMAC_TIMSECU_TSS_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TIMNANOU
// register.
//
//*****************************************************************************
#define EMAC_TIMNANOU_ADDSUB    0x80000000  // Add or subtract time
#define EMAC_TIMNANOU_TSSS_M    0x7FFFFFFF  // Timestamp Sub-Second
#define EMAC_TIMNANOU_TSSS_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TIMADD register.
//
//*****************************************************************************
#define EMAC_TIMADD_TSAR_M      0xFFFFFFFF  // Timestamp Addend Register
#define EMAC_TIMADD_TSAR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TARGSEC register.
//
//*****************************************************************************
#define EMAC_TARGSEC_TSTR_M     0xFFFFFFFF  // Target Time Seconds Register
#define EMAC_TARGSEC_TSTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TARGNANO
// register.
//
//*****************************************************************************
#define EMAC_TARGNANO_TRGTBUSY  0x80000000  // Target Time Register Busy
#define EMAC_TARGNANO_TTSLO_M   0x7FFFFFFF  // Target Timestamp Low Register
#define EMAC_TARGNANO_TTSLO_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_HWORDSEC
// register.
//
//*****************************************************************************
#define EMAC_HWORDSEC_TSHWR_M   0x0000FFFF  // Target Timestamp Higher Word
// Register
#define EMAC_HWORDSEC_TSHWR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TIMSTAT register.
//
//*****************************************************************************
#define EMAC_TIMSTAT_TSTARGT    0x00000002  // Timestamp Target Time Reached
#define EMAC_TIMSTAT_TSSOVF     0x00000001  // Timestamp Seconds Overflow

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_PPSCTRL register.
//
//*****************************************************************************
#define EMAC_PPSCTRL_TRGMODS0_M 0x00000060  // Target Time Register Mode for
// PPS0 Output
#define EMAC_PPSCTRL_TRGMODS0_INTONLY                                         \
                                0x00000000  // Indicates that the Target Time
// registers are programmed only
// for generating the interrupt
// event
#define EMAC_PPSCTRL_TRGMODS0_INTPPS0                                         \
                                0x00000040  // Indicates that the Target Time
// registers are programmed for
// generating the interrupt event
// and starting or stopping the
// generation of the EN0PPS output
// signal
#define EMAC_PPSCTRL_TRGMODS0_PPS0ONLY                                        \
                                0x00000060  // Indicates that the Target Time
// registers are programmed only
// for starting or stopping the
// generation of the EN0PPS output
// signal. No interrupt is asserted
#define EMAC_PPSCTRL_PPSEN0     0x00000010  // Flexible PPS Output Mode Enable
#define EMAC_PPSCTRL_PPSCTRL_M  0x0000000F  // EN0PPS Output Frequency Control
// (PPSCTRL) or Command Control
// (PPSCMD)

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_PPS0INTVL
// register.
//
//*****************************************************************************
#define EMAC_PPS0INTVL_PPS0INT_M                                              \
                                0xFFFFFFFF  // PPS0 Output Signal Interval
#define EMAC_PPS0INTVL_PPS0INT_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_PPS0WIDTH
// register.
//
//*****************************************************************************
#define EMAC_PPS0WIDTH_M        0xFFFFFFFF  // EN0PPS Output Signal Width
#define EMAC_PPS0WIDTH_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_DMABUSMOD
// register.
//
//*****************************************************************************
#define EMAC_DMABUSMOD_RIB      0x80000000  // Rebuild Burst
#define EMAC_DMABUSMOD_TXPR     0x08000000  // Transmit Priority
#define EMAC_DMABUSMOD_MB       0x04000000  // Mixed Burst
#define EMAC_DMABUSMOD_AAL      0x02000000  // Address Aligned Beats
#define EMAC_DMABUSMOD_8XPBL    0x01000000  // 8 x Programmable Burst Length
// (PBL) Mode
#define EMAC_DMABUSMOD_USP      0x00800000  // Use Separate Programmable Burst
// Length (PBL)
#define EMAC_DMABUSMOD_RPBL_M   0x007E0000  // RX DMA Programmable Burst Length
// (PBL)
#define EMAC_DMABUSMOD_FB       0x00010000  // Fixed Burst
#define EMAC_DMABUSMOD_PR_M     0x0000C000  // Priority Ratio
#define EMAC_DMABUSMOD_PBL_M    0x00003F00  // Programmable Burst Length
#define EMAC_DMABUSMOD_ATDS     0x00000080  // Alternate Descriptor Size
#define EMAC_DMABUSMOD_DSL_M    0x0000007C  // Descriptor Skip Length
#define EMAC_DMABUSMOD_DA       0x00000002  // DMA Arbitration Scheme
#define EMAC_DMABUSMOD_SWR      0x00000001  // DMA Software Reset
#define EMAC_DMABUSMOD_RPBL_S   17
#define EMAC_DMABUSMOD_PR_S     14
#define EMAC_DMABUSMOD_PBL_S    8
#define EMAC_DMABUSMOD_DSL_S    2

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TXPOLLD register.
//
//*****************************************************************************
#define EMAC_TXPOLLD_TPD_M      0xFFFFFFFF  // Transmit Poll Demand
#define EMAC_TXPOLLD_TPD_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RXPOLLD register.
//
//*****************************************************************************
#define EMAC_RXPOLLD_RPD_M      0xFFFFFFFF  // Receive Poll Demand
#define EMAC_RXPOLLD_RPD_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RXDLADDR
// register.
//
//*****************************************************************************
#define EMAC_RXDLADDR_STRXLIST_M                                              \
                                0xFFFFFFFC  // Start of Receive List
#define EMAC_RXDLADDR_STRXLIST_S                                              \
                                2

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_TXDLADDR
// register.
//
//*****************************************************************************
#define EMAC_TXDLADDR_TXDLADDR_M                                              \
                                0xFFFFFFFC  // Start of Transmit List Base
// Address
#define EMAC_TXDLADDR_TXDLADDR_S                                              \
                                2

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_DMARIS register.
//
//*****************************************************************************
#define EMAC_DMARIS_LPI         0x40000000  // LPI Trigger Interrupt Status
#define EMAC_DMARIS_TT          0x20000000  // Timestamp Trigger Interrupt
// Status
#define EMAC_DMARIS_PMT         0x10000000  // MAC PMT Interrupt Status
#define EMAC_DMARIS_MMC         0x08000000  // MAC MMC Interrupt
#define EMAC_DMARIS_AE_M        0x03800000  // Access Error
#define EMAC_DMARIS_AE_RXDMAWD  0x00000000  // Error during RX DMA Write Data
// Transfer
#define EMAC_DMARIS_AE_TXDMARD  0x01800000  // Error during TX DMA Read Data
// Transfer
#define EMAC_DMARIS_AE_RXDMADW  0x02000000  // Error during RX DMA Descriptor
// Write Access
#define EMAC_DMARIS_AE_TXDMADW  0x02800000  // Error during TX DMA Descriptor
// Write Access
#define EMAC_DMARIS_AE_RXDMADR  0x03000000  // Error during RX DMA Descriptor
// Read Access
#define EMAC_DMARIS_AE_TXDMADR  0x03800000  // Error during TX DMA Descriptor
// Read Access
#define EMAC_DMARIS_TS_M        0x00700000  // Transmit Process State
#define EMAC_DMARIS_TS_STOP     0x00000000  // Stopped; Reset or Stop transmit
// command processed
#define EMAC_DMARIS_TS_RUNTXTD  0x00100000  // Running; Fetching transmit
// transfer descriptor
#define EMAC_DMARIS_TS_STATUS   0x00200000  // Running; Waiting for status
#define EMAC_DMARIS_TS_RUNTX    0x00300000  // Running; Reading data from host
// memory buffer and queuing it to
// transmit buffer (TX FIFO)
#define EMAC_DMARIS_TS_TSTAMP   0x00400000  // Writing Timestamp
#define EMAC_DMARIS_TS_SUSPEND  0x00600000  // Suspended; Transmit descriptor
// unavailable or transmit buffer
// underflow
#define EMAC_DMARIS_TS_RUNCTD   0x00700000  // Running; Closing transmit
// descriptor
#define EMAC_DMARIS_RS_M        0x000E0000  // Received Process State
#define EMAC_DMARIS_RS_STOP     0x00000000  // Stopped: Reset or stop receive
// command issued
#define EMAC_DMARIS_RS_RUNRXTD  0x00020000  // Running: Fetching receive
// transfer descriptor
#define EMAC_DMARIS_RS_RUNRXD   0x00060000  // Running: Waiting for receive
// packet
#define EMAC_DMARIS_RS_SUSPEND  0x00080000  // Suspended: Receive descriptor
// unavailable
#define EMAC_DMARIS_RS_RUNCRD   0x000A0000  // Running: Closing receive
// descriptor
#define EMAC_DMARIS_RS_TSWS     0x000C0000  // Writing Timestamp
#define EMAC_DMARIS_RS_RUNTXD   0x000E0000  // Running: Transferring the
// receive packet data from receive
// buffer to host memory
#define EMAC_DMARIS_NIS         0x00010000  // Normal Interrupt Summary
#define EMAC_DMARIS_AIS         0x00008000  // Abnormal Interrupt Summary
#define EMAC_DMARIS_ERI         0x00004000  // Early Receive Interrupt
#define EMAC_DMARIS_FBI         0x00002000  // Fatal Bus Error Interrupt
#define EMAC_DMARIS_ETI         0x00000400  // Early Transmit Interrupt
#define EMAC_DMARIS_RWT         0x00000200  // Receive Watchdog Timeout
#define EMAC_DMARIS_RPS         0x00000100  // Receive Process Stopped
#define EMAC_DMARIS_RU          0x00000080  // Receive Buffer Unavailable
#define EMAC_DMARIS_RI          0x00000040  // Receive Interrupt
#define EMAC_DMARIS_UNF         0x00000020  // Transmit Underflow
#define EMAC_DMARIS_OVF         0x00000010  // Receive Overflow
#define EMAC_DMARIS_TJT         0x00000008  // Transmit Jabber Timeout
#define EMAC_DMARIS_TU          0x00000004  // Transmit Buffer Unavailable
#define EMAC_DMARIS_TPS         0x00000002  // Transmit Process Stopped
#define EMAC_DMARIS_TI          0x00000001  // Transmit Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_DMAOPMODE
// register.
//
//*****************************************************************************
#define EMAC_DMAOPMODE_DT       0x04000000  // Disable Dropping of TCP/IP
// Checksum Error Frames
#define EMAC_DMAOPMODE_RSF      0x02000000  // Receive Store and Forward
#define EMAC_DMAOPMODE_DFF      0x01000000  // Disable Flushing of Received
// Frames
#define EMAC_DMAOPMODE_TSF      0x00200000  // Transmit Store and Forward
#define EMAC_DMAOPMODE_FTF      0x00100000  // Flush Transmit FIFO
#define EMAC_DMAOPMODE_TTC_M    0x0001C000  // Transmit Threshold Control
#define EMAC_DMAOPMODE_TTC_64   0x00000000  // 64 bytes
#define EMAC_DMAOPMODE_TTC_128  0x00004000  // 128 bytes
#define EMAC_DMAOPMODE_TTC_192  0x00008000  // 192 bytes
#define EMAC_DMAOPMODE_TTC_256  0x0000C000  // 256 bytes
#define EMAC_DMAOPMODE_TTC_40   0x00010000  // 40 bytes
#define EMAC_DMAOPMODE_TTC_32   0x00014000  // 32 bytes
#define EMAC_DMAOPMODE_TTC_24   0x00018000  // 24 bytes
#define EMAC_DMAOPMODE_TTC_16   0x0001C000  // 16 bytes
#define EMAC_DMAOPMODE_ST       0x00002000  // Start or Stop Transmission
// Command
#define EMAC_DMAOPMODE_FEF      0x00000080  // Forward Error Frames
#define EMAC_DMAOPMODE_FUF      0x00000040  // Forward Undersized Good Frames
#define EMAC_DMAOPMODE_DGF      0x00000020  // Drop Giant Frame Enable
#define EMAC_DMAOPMODE_RTC_M    0x00000018  // Receive Threshold Control
#define EMAC_DMAOPMODE_RTC_64   0x00000000  // 64 bytes
#define EMAC_DMAOPMODE_RTC_32   0x00000008  // 32 bytes
#define EMAC_DMAOPMODE_RTC_96   0x00000010  // 96 bytes
#define EMAC_DMAOPMODE_RTC_128  0x00000018  // 128 bytes
#define EMAC_DMAOPMODE_OSF      0x00000004  // Operate on Second Frame
#define EMAC_DMAOPMODE_SR       0x00000002  // Start or Stop Receive

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_DMAIM register.
//
//*****************************************************************************
#define EMAC_DMAIM_NIE          0x00010000  // Normal Interrupt Summary Enable
#define EMAC_DMAIM_AIE          0x00008000  // Abnormal Interrupt Summary
// Enable
#define EMAC_DMAIM_ERE          0x00004000  // Early Receive Interrupt Enable
#define EMAC_DMAIM_FBE          0x00002000  // Fatal Bus Error Enable
#define EMAC_DMAIM_ETE          0x00000400  // Early Transmit Interrupt Enable
#define EMAC_DMAIM_RWE          0x00000200  // Receive Watchdog Timeout Enable
#define EMAC_DMAIM_RSE          0x00000100  // Receive Stopped Enable
#define EMAC_DMAIM_RUE          0x00000080  // Receive Buffer Unavailable
// Enable
#define EMAC_DMAIM_RIE          0x00000040  // Receive Interrupt Enable
#define EMAC_DMAIM_UNE          0x00000020  // Underflow Interrupt Enable
#define EMAC_DMAIM_OVE          0x00000010  // Overflow Interrupt Enable
#define EMAC_DMAIM_TJE          0x00000008  // Transmit Jabber Timeout Enable
#define EMAC_DMAIM_TUE          0x00000004  // Transmit Buffer Unvailable
// Enable
#define EMAC_DMAIM_TSE          0x00000002  // Transmit Stopped Enable
#define EMAC_DMAIM_TIE          0x00000001  // Transmit Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_MFBOC register.
//
//*****************************************************************************
#define EMAC_MFBOC_OVFCNTOVF    0x10000000  // Overflow Bit for FIFO Overflow
// Counter
#define EMAC_MFBOC_OVFFRMCNT_M  0x0FFE0000  // Overflow Frame Counter
#define EMAC_MFBOC_MISCNTOVF    0x00010000  // Overflow bit for Missed Frame
// Counter
#define EMAC_MFBOC_MISFRMCNT_M  0x0000FFFF  // Missed Frame Counter
#define EMAC_MFBOC_OVFFRMCNT_S  17
#define EMAC_MFBOC_MISFRMCNT_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_RXINTWDT
// register.
//
//*****************************************************************************
#define EMAC_RXINTWDT_RIWT_M    0x000000FF  // Receive Interrupt Watchdog Timer
// Count
#define EMAC_RXINTWDT_RIWT_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_HOSTXDESC
// register.
//
//*****************************************************************************
#define EMAC_HOSTXDESC_CURTXDESC_M                                            \
                                0xFFFFFFFF  // Host Transmit Descriptor Address
// Pointer
#define EMAC_HOSTXDESC_CURTXDESC_S                                            \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_HOSRXDESC
// register.
//
//*****************************************************************************
#define EMAC_HOSRXDESC_CURRXDESC_M                                            \
                                0xFFFFFFFF  // Host Receive Descriptor Address
// Pointer
#define EMAC_HOSRXDESC_CURRXDESC_S                                            \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_HOSTXBA register.
//
//*****************************************************************************
#define EMAC_HOSTXBA_CURTXBUFA_M                                              \
                                0xFFFFFFFF  // Host Transmit Buffer Address
// Pointer
#define EMAC_HOSTXBA_CURTXBUFA_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_HOSRXBA register.
//
//*****************************************************************************
#define EMAC_HOSRXBA_CURRXBUFA_M                                              \
                                0xFFFFFFFF  // Host Receive Buffer Address
// Pointer
#define EMAC_HOSRXBA_CURRXBUFA_S                                              \
                                0

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_PP register.
//
//*****************************************************************************
#define EMAC_PP_MACTYPE_M       0x00000700  // Ethernet MAC Type
#define EMAC_PP_MACTYPE_1       0x00000100  // MSP432E4 class MAC
#define EMAC_PP_PHYTYPE_M       0x00000007  // Ethernet PHY Type
#define EMAC_PP_PHYTYPE_NONE    0x00000000  // No PHY
#define EMAC_PP_PHYTYPE_1       0x00000003  // MSP432E4 class PHY

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_PC register.
//
//*****************************************************************************
#define EMAC_PC_PHYEXT          0x80000000  // PHY Select
#define EMAC_PC_PINTFS_M        0x70000000  // Ethernet Interface Select
#define EMAC_PC_PINTFS_IMII     0x00000000  // MII (default) Used for internal
// PHY or external PHY connected
// via MII
#define EMAC_PC_PINTFS_RMII     0x40000000  // RMII: Used for external PHY
// connected via RMII
#define EMAC_PC_DIGRESTART      0x02000000  // PHY Soft Restart
#define EMAC_PC_NIBDETDIS       0x01000000  // Odd Nibble TXER Detection
// Disable
#define EMAC_PC_RXERIDLE        0x00800000  // RXER Detection During Idle
#define EMAC_PC_ISOMIILL        0x00400000  // Isolate MII in Link Loss
#define EMAC_PC_LRR             0x00200000  // Link Loss Recovery
#define EMAC_PC_TDRRUN          0x00100000  // TDR Auto Run
#define EMAC_PC_FASTLDMODE_M    0x000F8000  // Fast Link Down Mode
#define EMAC_PC_POLSWAP         0x00004000  // Polarity Swap
#define EMAC_PC_MDISWAP         0x00002000  // MDI Swap
#define EMAC_PC_RBSTMDIX        0x00001000  // Robust Auto MDI-X
#define EMAC_PC_FASTMDIX        0x00000800  // Fast Auto MDI-X
#define EMAC_PC_MDIXEN          0x00000400  // MDIX Enable
#define EMAC_PC_FASTRXDV        0x00000200  // Fast RXDV Detection
#define EMAC_PC_FASTLUPD        0x00000100  // FAST Link-Up in Parallel Detect
#define EMAC_PC_EXTFD           0x00000080  // Extended Full Duplex Ability
#define EMAC_PC_FASTANEN        0x00000040  // Fast Auto Negotiation Enable
#define EMAC_PC_FASTANSEL_M     0x00000030  // Fast Auto Negotiation Select
#define EMAC_PC_ANEN            0x00000008  // Auto Negotiation Enable
#define EMAC_PC_ANMODE_M        0x00000006  // Auto Negotiation Mode
#define EMAC_PC_ANMODE_10HD     0x00000000  // When ANEN = 0x0, the mode is
// 10Base-T, Half-Duplex
#define EMAC_PC_ANMODE_10FD     0x00000002  // When ANEN = 0x0, the mode is
// 10Base-T, Full-Duplex
#define EMAC_PC_ANMODE_100HD    0x00000004  // When ANEN = 0x0, the mode is
// 100Base-TX, Half-Duplex
#define EMAC_PC_ANMODE_100FD    0x00000006  // When ANEN = 0x0, the mode is
// 100Base-TX, Full-Duplex
#define EMAC_PC_PHYHOLD         0x00000001  // Ethernet PHY Hold
#define EMAC_PC_FASTLDMODE_S    15
#define EMAC_PC_FASTANSEL_S     4

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_CC register.
//
//*****************************************************************************
#define EMAC_CC_PTPCEN          0x00040000  // PTP Clock Reference Enable
#define EMAC_CC_POL             0x00020000  // LED Polarity Control
#define EMAC_CC_CLKEN           0x00010000  // EN0RREF_CLK Signal Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_EPHYRIS register.
//
//*****************************************************************************
#define EMAC_EPHYRIS_INT        0x00000001  // Ethernet PHY Raw Interrupt
// Status

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_EPHYIM register.
//
//*****************************************************************************
#define EMAC_EPHYIM_INT         0x00000001  // Ethernet PHY Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the EMAC_O_EPHYMISC
// register.
//
//*****************************************************************************
#define EMAC_EPHYMISC_INT       0x00000001  // Ethernet PHY Status and Clear
// register

//*****************************************************************************
//
// The following are defines for the EPHY register offsets.
//
//*****************************************************************************
#define EPHY_BMCR               0x00000000  // Ethernet PHY Basic Mode Control
#define EPHY_BMSR               0x00000001  // Ethernet PHY Basic Mode Status
#define EPHY_ID1                0x00000002  // Ethernet PHY Identifier Register
// 1
#define EPHY_ID2                0x00000003  // Ethernet PHY Identifier Register
// 2
#define EPHY_ANA                0x00000004  // Ethernet PHY Auto-Negotiation
// Advertisement
#define EPHY_ANLPA              0x00000005  // Ethernet PHY Auto-Negotiation
// Link Partner Ability
#define EPHY_ANER               0x00000006  // Ethernet PHY Auto-Negotiation
// Expansion
#define EPHY_ANNPTR             0x00000007  // Ethernet PHY Auto-Negotiation
// Next Page TX
#define EPHY_ANLNPTR            0x00000008  // Ethernet PHY Auto-Negotiation
// Link Partner Ability Next Page
#define EPHY_CFG1               0x00000009  // Ethernet PHY Configuration 1
#define EPHY_CFG2               0x0000000A  // Ethernet PHY Configuration 2
#define EPHY_CFG3               0x0000000B  // Ethernet PHY Configuration 3
#define EPHY_REGCTL             0x0000000D  // Ethernet PHY Register Control
#define EPHY_ADDAR              0x0000000E  // Ethernet PHY Address or Data
#define EPHY_STS                0x00000010  // Ethernet PHY Status
#define EPHY_SCR                0x00000011  // Ethernet PHY Specific Control
#define EPHY_MISR1              0x00000012  // Ethernet PHY MII Interrupt
// Status 1
#define EPHY_MISR2              0x00000013  // Ethernet PHY MII Interrupt
// Status 2
#define EPHY_FCSCR              0x00000014  // Ethernet PHY False Carrier Sense
// Counter
#define EPHY_RXERCNT            0x00000015  // Ethernet PHY Receive Error Count
#define EPHY_BISTCR             0x00000016  // Ethernet PHY BIST Control
#define EPHY_LEDCR              0x00000018  // Ethernet PHY LED Control
#define EPHY_CTL                0x00000019  // Ethernet PHY Control
#define EPHY_10BTSC             0x0000001A  // Ethernet PHY 10Base-T
// Status/Control - MR26
#define EPHY_BICSR1             0x0000001B  // Ethernet PHY BIST Control and
// Status 1
#define EPHY_BICSR2             0x0000001C  // Ethernet PHY BIST Control and
// Status 2
#define EPHY_CDCR               0x0000001E  // Ethernet PHY Cable Diagnostic
// Control
#define EPHY_RCR                0x0000001F  // Ethernet PHY Reset Control
#define EPHY_LEDCFG             0x00000025  // Ethernet PHY LED Configuration

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_BMCR register.
//
//*****************************************************************************
#define EPHY_BMCR_MIIRESET      0x00008000  // MII Register reset
#define EPHY_BMCR_MIILOOPBK     0x00004000  // MII Loopback
#define EPHY_BMCR_SPEED         0x00002000  // Speed Select
#define EPHY_BMCR_ANEN          0x00001000  // Auto-Negotiate Enable
#define EPHY_BMCR_PWRDWN        0x00000800  // Power Down
#define EPHY_BMCR_ISOLATE       0x00000400  // Port Isolate
#define EPHY_BMCR_RESTARTAN     0x00000200  // Restart Auto-Negotiation
#define EPHY_BMCR_DUPLEXM       0x00000100  // Duplex Mode
#define EPHY_BMCR_COLLTST       0x00000080  // Collision Test

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_BMSR register.
//
//*****************************************************************************
#define EPHY_BMSR_100BTXFD      0x00004000  // 100Base-TX Full Duplex Capable
#define EPHY_BMSR_100BTXHD      0x00002000  // 100Base-TX Half Duplex Capable
#define EPHY_BMSR_10BTFD        0x00001000  // 10 Base-T Full Duplex Capable
#define EPHY_BMSR_10BTHD        0x00000800  // 10 Base-T Half Duplex Capable
#define EPHY_BMSR_MFPRESUP      0x00000040  // Preamble Suppression Capable
#define EPHY_BMSR_ANC           0x00000020  // Auto-Negotiation Complete
#define EPHY_BMSR_RFAULT        0x00000010  // Remote Fault
#define EPHY_BMSR_ANEN          0x00000008  // Auto Negotiation Enabled
#define EPHY_BMSR_LINKSTAT      0x00000004  // Link Status
#define EPHY_BMSR_JABBER        0x00000002  // Jabber Detect
#define EPHY_BMSR_EXTEN         0x00000001  // Extended Capability Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_ID1 register.
//
//*****************************************************************************
#define EPHY_ID1_OUIMSB_M       0x0000FFFF  // OUI Most Significant Bits
#define EPHY_ID1_OUIMSB_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_ID2 register.
//
//*****************************************************************************
#define EPHY_ID2_OUILSB_M       0x0000FC00  // OUI Least Significant Bits
#define EPHY_ID2_VNDRMDL_M      0x000003F0  // Vendor Model Number
#define EPHY_ID2_MDLREV_M       0x0000000F  // Model Revision Number
#define EPHY_ID2_OUILSB_S       10
#define EPHY_ID2_VNDRMDL_S      4
#define EPHY_ID2_MDLREV_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_ANA register.
//
//*****************************************************************************
#define EPHY_ANA_NP             0x00008000  // Next Page Indication
#define EPHY_ANA_RF             0x00002000  // Remote Fault
#define EPHY_ANA_ASMDUP         0x00000800  // Asymmetric PAUSE support for
// Full Duplex Links
#define EPHY_ANA_PAUSE          0x00000400  // PAUSE Support for Full Duplex
// Links
#define EPHY_ANA_100BT4         0x00000200  // 100Base-T4 Support
#define EPHY_ANA_100BTXFD       0x00000100  // 100Base-TX Full Duplex Support
#define EPHY_ANA_100BTX         0x00000080  // 100Base-TX Support
#define EPHY_ANA_10BTFD         0x00000040  // 10Base-T Full Duplex Support
#define EPHY_ANA_10BT           0x00000020  // 10Base-T Support
#define EPHY_ANA_SELECT_M       0x0000001F  // Protocol Selection
#define EPHY_ANA_SELECT_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_ANLPA register.
//
//*****************************************************************************
#define EPHY_ANLPA_NP           0x00008000  // Next Page Indication
#define EPHY_ANLPA_ACK          0x00004000  // Acknowledge
#define EPHY_ANLPA_RF           0x00002000  // Remote Fault
#define EPHY_ANLPA_ASMDUP       0x00000800  // Asymmetric PAUSE
#define EPHY_ANLPA_PAUSE        0x00000400  // PAUSE
#define EPHY_ANLPA_100BT4       0x00000200  // 100Base-T4 Support
#define EPHY_ANLPA_100BTXFD     0x00000100  // 100Base-TX Full Duplex Support
#define EPHY_ANLPA_100BTX       0x00000080  // 100Base-TX Support
#define EPHY_ANLPA_10BTFD       0x00000040  // 10Base-T Full Duplex Support
#define EPHY_ANLPA_10BT         0x00000020  // 10Base-T Support
#define EPHY_ANLPA_SELECT_M     0x0000001F  // Protocol Selection
#define EPHY_ANLPA_SELECT_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_ANER register.
//
//*****************************************************************************
#define EPHY_ANER_PDF           0x00000010  // Parallel Detection Fault
#define EPHY_ANER_LPNPABLE      0x00000008  // Link Partner Next Page Able
#define EPHY_ANER_NPABLE        0x00000004  // Next Page Able
#define EPHY_ANER_PAGERX        0x00000002  // Link Code Word Page Received
#define EPHY_ANER_LPANABLE      0x00000001  // Link Partner Auto-Negotiation
// Able

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_ANNPTR register.
//
//*****************************************************************************
#define EPHY_ANNPTR_NP          0x00008000  // Next Page Indication
#define EPHY_ANNPTR_MP          0x00002000  // Message Page
#define EPHY_ANNPTR_ACK2        0x00001000  // Acknowledge 2
#define EPHY_ANNPTR_TOGTX       0x00000800  // Toggle
#define EPHY_ANNPTR_CODE_M      0x000007FF  // Code
#define EPHY_ANNPTR_CODE_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_ANLNPTR register.
//
//*****************************************************************************
#define EPHY_ANLNPTR_NP         0x00008000  // Next Page Indication
#define EPHY_ANLNPTR_ACK        0x00004000  // Acknowledge
#define EPHY_ANLNPTR_MP         0x00002000  // Message Page
#define EPHY_ANLNPTR_ACK2       0x00001000  // Acknowledge 2
#define EPHY_ANLNPTR_TOG        0x00000800  // Toggle
#define EPHY_ANLNPTR_CODE_M     0x000007FF  // Code
#define EPHY_ANLNPTR_CODE_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_CFG1 register.
//
//*****************************************************************************
#define EPHY_CFG1_DONE          0x00008000  // Configuration Done
#define EPHY_CFG1_TDRAR         0x00000100  // TDR Auto-Run at Link Down
#define EPHY_CFG1_LLR           0x00000080  // Link Loss Recovery
#define EPHY_CFG1_FAMDIX        0x00000040  // Fast Auto MDI/MDIX
#define EPHY_CFG1_RAMDIX        0x00000020  // Robust Auto MDI/MDIX
#define EPHY_CFG1_FASTANEN      0x00000010  // Fast Auto Negotiation Enable
#define EPHY_CFG1_FANSEL_M      0x0000000C  // Fast Auto-Negotiation Select
// Configuration
#define EPHY_CFG1_FANSEL_BLT80  0x00000000  // Break Link Timer: 80 ms
#define EPHY_CFG1_FANSEL_BLT120 0x00000004  // Break Link Timer: 120 ms
#define EPHY_CFG1_FANSEL_BLT240 0x00000008  // Break Link Timer: 240 ms
#define EPHY_CFG1_FRXDVDET      0x00000002  // FAST RXDV Detection

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_CFG2 register.
//
//*****************************************************************************
#define EPHY_CFG2_FLUPPD        0x00000040  // Fast Link-Up in Parallel Detect
// Mode
#define EPHY_CFG2_EXTFD         0x00000020  // Extended Full-Duplex Ability
#define EPHY_CFG2_ENLEDLINK     0x00000010  // Enhanced LED Functionality
#define EPHY_CFG2_ISOMIILL      0x00000008  // Isolate MII outputs when
// Enhanced Link is not Achievable
#define EPHY_CFG2_RXERRIDLE     0x00000004  // Detection of Receive Symbol
// Error During IDLE State
#define EPHY_CFG2_ODDNDETDIS    0x00000002  // Detection of Transmit Error

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_CFG3 register.
//
//*****************************************************************************
#define EPHY_CFG3_POLSWAP       0x00000080  // Polarity Swap
#define EPHY_CFG3_MDIMDIXS      0x00000040  // MDI/MDIX Swap
#define EPHY_CFG3_FLDWNM_M      0x0000001F  // Fast Link Down Modes
#define EPHY_CFG3_FLDWNM_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_REGCTL register.
//
//*****************************************************************************
#define EPHY_REGCTL_FUNC_M      0x0000C000  // Function
#define EPHY_REGCTL_FUNC_ADDR   0x00000000  // Address
#define EPHY_REGCTL_FUNC_DATANI 0x00004000  // Data, no post increment
#define EPHY_REGCTL_FUNC_DATAPIRW                                             \
                                0x00008000  // Data, post increment on read and
// write
#define EPHY_REGCTL_FUNC_DATAPIWO                                             \
                                0x0000C000  // Data, post increment on write
// only
#define EPHY_REGCTL_DEVAD_M     0x0000001F  // Device Address
#define EPHY_REGCTL_DEVAD_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_ADDAR register.
//
//*****************************************************************************
#define EPHY_ADDAR_ADDRDATA_M   0x0000FFFF  // Address or Data
#define EPHY_ADDAR_ADDRDATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_STS register.
//
//*****************************************************************************
#define EPHY_STS_MDIXM          0x00004000  // MDI-X Mode
#define EPHY_STS_RXLERR         0x00002000  // Receive Error Latch
#define EPHY_STS_POLSTAT        0x00001000  // Polarity Status
#define EPHY_STS_FCSL           0x00000800  // False Carrier Sense Latch
#define EPHY_STS_SD             0x00000400  // Signal Detect
#define EPHY_STS_DL             0x00000200  // Descrambler Lock
#define EPHY_STS_PAGERX         0x00000100  // Link Code Page Received
#define EPHY_STS_MIIREQ         0x00000080  // MII Interrupt Pending
#define EPHY_STS_RF             0x00000040  // Remote Fault
#define EPHY_STS_JD             0x00000020  // Jabber Detect
#define EPHY_STS_ANS            0x00000010  // Auto-Negotiation Status
#define EPHY_STS_MIILB          0x00000008  // MII Loopback Status
#define EPHY_STS_DUPLEX         0x00000004  // Duplex Status
#define EPHY_STS_SPEED          0x00000002  // Speed Status
#define EPHY_STS_LINK           0x00000001  // Link Status

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_SCR register.
//
//*****************************************************************************
#define EPHY_SCR_DISCLK         0x00008000  // Disable CLK
#define EPHY_SCR_PSEN           0x00004000  // Power Saving Modes Enable
#define EPHY_SCR_PSMODE_M       0x00003000  // Power Saving Modes
#define EPHY_SCR_PSMODE_NORMAL  0x00000000  // Normal: Normal operation mode.
// PHY is fully functional
#define EPHY_SCR_PSMODE_LOWPWR  0x00001000  // IEEE Power Down
#define EPHY_SCR_PSMODE_ACTWOL  0x00002000  // Active Sleep
#define EPHY_SCR_PSMODE_PASWOL  0x00003000  // Passive Sleep
#define EPHY_SCR_SBPYASS        0x00000800  // Scrambler Bypass
#define EPHY_SCR_LBFIFO_M       0x00000300  // Loopback FIFO Depth
#define EPHY_SCR_LBFIFO_4       0x00000000  // Four nibble FIFO
#define EPHY_SCR_LBFIFO_5       0x00000100  // Five nibble FIFO
#define EPHY_SCR_LBFIFO_6       0x00000200  // Six nibble FIFO
#define EPHY_SCR_LBFIFO_8       0x00000300  // Eight nibble FIFO
#define EPHY_SCR_COLFDM         0x00000010  // Collision in Full-Duplex Mode
#define EPHY_SCR_TINT           0x00000004  // Test Interrupt
#define EPHY_SCR_INTEN          0x00000002  // Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_MISR1 register.
//
//*****************************************************************************
#define EPHY_MISR1_LINKSTAT     0x00002000  // Change of Link Status Interrupt
#define EPHY_MISR1_SPEED        0x00001000  // Change of Speed Status Interrupt
#define EPHY_MISR1_DUPLEXM      0x00000800  // Change of Duplex Status
// Interrupt
#define EPHY_MISR1_ANC          0x00000400  // Auto-Negotiation Complete
// Interrupt
#define EPHY_MISR1_FCHF         0x00000200  // False Carrier Counter Half-Full
// Interrupt
#define EPHY_MISR1_RXHF         0x00000100  // Receive Error Counter Half-Full
// Interrupt
#define EPHY_MISR1_LINKSTATEN   0x00000020  // Link Status Interrupt Enable
#define EPHY_MISR1_SPEEDEN      0x00000010  // Speed Change Interrupt Enable
#define EPHY_MISR1_DUPLEXMEN    0x00000008  // Duplex Status Interrupt Enable
#define EPHY_MISR1_ANCEN        0x00000004  // Auto-Negotiation Complete
// Interrupt Enable
#define EPHY_MISR1_FCHFEN       0x00000002  // False Carrier Counter Register
// half-full Interrupt Enable
#define EPHY_MISR1_RXHFEN       0x00000001  // Receive Error Counter Register
// Half-Full Event Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_MISR2 register.
//
//*****************************************************************************
#define EPHY_MISR2_ANERR        0x00004000  // Auto-Negotiation Error Interrupt
#define EPHY_MISR2_PAGERX       0x00002000  // Page Receive Interrupt
#define EPHY_MISR2_LBFIFO       0x00001000  // Loopback FIFO Overflow/Underflow
// Event Interrupt
#define EPHY_MISR2_MDICO        0x00000800  // MDI/MDIX Crossover Status
// Changed Interrupt
#define EPHY_MISR2_SLEEP        0x00000400  // Sleep Mode Event Interrupt
#define EPHY_MISR2_POLINT       0x00000200  // Polarity Changed Interrupt
#define EPHY_MISR2_JABBER       0x00000100  // Jabber Detect Event Interrupt
#define EPHY_MISR2_ANERREN      0x00000040  // Auto-Negotiation Error Interrupt
// Enable
#define EPHY_MISR2_PAGERXEN     0x00000020  // Page Receive Interrupt Enable
#define EPHY_MISR2_LBFIFOEN     0x00000010  // Loopback FIFO Overflow/Underflow
// Interrupt Enable
#define EPHY_MISR2_MDICOEN      0x00000008  // MDI/MDIX Crossover Status
// Changed Interrupt Enable
#define EPHY_MISR2_SLEEPEN      0x00000004  // Sleep Mode Event Interrupt
// Enable
#define EPHY_MISR2_POLINTEN     0x00000002  // Polarity Changed Interrupt
// Enable
#define EPHY_MISR2_JABBEREN     0x00000001  // Jabber Detect Event Interrupt
// Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_FCSCR register.
//
//*****************************************************************************
#define EPHY_FCSCR_FCSCNT_M     0x000000FF  // False Carrier Event Counter
#define EPHY_FCSCR_FCSCNT_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_RXERCNT register.
//
//*****************************************************************************
#define EPHY_RXERCNT_RXERRCNT_M 0x0000FFFF  // Receive Error Count
#define EPHY_RXERCNT_RXERRCNT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_BISTCR register.
//
//*****************************************************************************
#define EPHY_BISTCR_PRBSM       0x00004000  // PRBS Single/Continuous Mode
#define EPHY_BISTCR_PRBSPKT     0x00002000  // Generated PRBS Packets
#define EPHY_BISTCR_PKTEN       0x00001000  // Packet Generation Enable
#define EPHY_BISTCR_PRBSCHKLK   0x00000800  // PRBS Checker Lock Indication
#define EPHY_BISTCR_PRBSCHKSYNC 0x00000400  // PRBS Checker Lock Sync Loss
// Indication
#define EPHY_BISTCR_PKTGENSTAT  0x00000200  // Packet Generator Status
// Indication
#define EPHY_BISTCR_PWRMODE     0x00000100  // Power Mode Indication
#define EPHY_BISTCR_TXMIILB     0x00000040  // Transmit Data in MII Loopback
// Mode
#define EPHY_BISTCR_LBMODE_M    0x0000001F  // Loopback Mode Select
#define EPHY_BISTCR_LBMODE_NPCSIN                                             \
                                0x00000001  // Near-end loopback: PCS Input
// Loopback
#define EPHY_BISTCR_LBMODE_NPCSOUT                                            \
                                0x00000002  // Near-end loopback: PCS Output
// Loopback (In 100Base-TX only)
#define EPHY_BISTCR_LBMODE_NDIG 0x00000004  // Near-end loopback: Digital
// Loopback
#define EPHY_BISTCR_LBMODE_NANA 0x00000008  // Near-end loopback: Analog
// Loopback (requires 100 Ohm
// termination)
#define EPHY_BISTCR_LBMODE_FREV 0x00000010  // Far-end Loopback: Reverse
// Loopback

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_LEDCR register.
//
//*****************************************************************************
#define EPHY_LEDCR_BLINKRATE_M  0x00000600  // LED Blinking Rate (ON/OFF
// duration):
#define EPHY_LEDCR_BLINKRATE_20HZ                                             \
                                0x00000000  // 20 Hz (50 ms)
#define EPHY_LEDCR_BLINKRATE_10HZ                                             \
                                0x00000200  // 10 Hz (100 ms)
#define EPHY_LEDCR_BLINKRATE_5HZ                                              \
                                0x00000400  // 5 Hz (200 ms)
#define EPHY_LEDCR_BLINKRATE_2HZ                                              \
                                0x00000600  // 2 Hz (500 ms)

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_CTL register.
//
//*****************************************************************************
#define EPHY_CTL_AUTOMDI        0x00008000  // Auto-MDIX Enable
#define EPHY_CTL_FORCEMDI       0x00004000  // Force MDIX
#define EPHY_CTL_PAUSERX        0x00002000  // Pause Receive Negotiated Status
#define EPHY_CTL_PAUSETX        0x00001000  // Pause Transmit Negotiated Status
#define EPHY_CTL_MIILNKSTAT     0x00000800  // MII Link Status
#define EPHY_CTL_BYPLEDSTRCH    0x00000080  // Bypass LED Stretching

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_10BTSC register.
//
//*****************************************************************************
#define EPHY_10BTSC_RXTHEN      0x00002000  // Lower Receiver Threshold Enable
#define EPHY_10BTSC_SQUELCH_M   0x00001E00  // Squelch Configuration
#define EPHY_10BTSC_NLPDIS      0x00000080  // Normal Link Pulse (NLP)
// Transmission Control
#define EPHY_10BTSC_POLSTAT     0x00000010  // 10 Mb Polarity Status
#define EPHY_10BTSC_JABBERD     0x00000001  // Jabber Disable
#define EPHY_10BTSC_SQUELCH_S   9

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_BICSR1 register.
//
//*****************************************************************************
#define EPHY_BICSR1_ERRCNT_M    0x0000FF00  // BIST Error Count
#define EPHY_BICSR1_IPGLENGTH_M 0x000000FF  // BIST IPG Length
#define EPHY_BICSR1_ERRCNT_S    8
#define EPHY_BICSR1_IPGLENGTH_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_BICSR2 register.
//
//*****************************************************************************
#define EPHY_BICSR2_PKTLENGTH_M 0x000007FF  // BIST Packet Length
#define EPHY_BICSR2_PKTLENGTH_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_CDCR register.
//
//*****************************************************************************
#define EPHY_CDCR_START         0x00008000  // Cable Diagnostic Process Start
#define EPHY_CDCR_LINKQUAL_M    0x00000300  // Link Quality Indication
#define EPHY_CDCR_LINKQUAL_GOOD 0x00000100  // Good Quality Link Indication
#define EPHY_CDCR_LINKQUAL_MILD 0x00000200  // Mid- Quality Link Indication
#define EPHY_CDCR_LINKQUAL_POOR 0x00000300  // Poor Quality Link Indication
#define EPHY_CDCR_DONE          0x00000002  // Cable Diagnostic Process Done
#define EPHY_CDCR_FAIL          0x00000001  // Cable Diagnostic Process Fail

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_RCR register.
//
//*****************************************************************************
#define EPHY_RCR_SWRST          0x00008000  // Software Reset
#define EPHY_RCR_SWRESTART      0x00004000  // Software Restart

//*****************************************************************************
//
// The following are defines for the bit fields in the EPHY_LEDCFG register.
//
//*****************************************************************************
#define EPHY_LEDCFG_LED2_M      0x00000F00  // LED2 Configuration
#define EPHY_LEDCFG_LED2_LINK   0x00000000  // Link OK
#define EPHY_LEDCFG_LED2_RXTX   0x00000100  // RX/TX Activity
#define EPHY_LEDCFG_LED2_TX     0x00000200  // TX Activity
#define EPHY_LEDCFG_LED2_RX     0x00000300  // RX Activity
#define EPHY_LEDCFG_LED2_COL    0x00000400  // Collision
#define EPHY_LEDCFG_LED2_100BT  0x00000500  // 100-Base TX
#define EPHY_LEDCFG_LED2_10BT   0x00000600  // 10-Base TX
#define EPHY_LEDCFG_LED2_FD     0x00000700  // Full Duplex
#define EPHY_LEDCFG_LED2_LINKTXRX                                             \
                                0x00000800  // Link OK/Blink on TX/RX Activity
#define EPHY_LEDCFG_LED1_M      0x000000F0  // LED1 Configuration
#define EPHY_LEDCFG_LED1_LINK   0x00000000  // Link OK
#define EPHY_LEDCFG_LED1_RXTX   0x00000010  // RX/TX Activity
#define EPHY_LEDCFG_LED1_TX     0x00000020  // TX Activity
#define EPHY_LEDCFG_LED1_RX     0x00000030  // RX Activity
#define EPHY_LEDCFG_LED1_COL    0x00000040  // Collision
#define EPHY_LEDCFG_LED1_100BT  0x00000050  // 100-Base TX
#define EPHY_LEDCFG_LED1_10BT   0x00000060  // 10-Base TX
#define EPHY_LEDCFG_LED1_FD     0x00000070  // Full Duplex
#define EPHY_LEDCFG_LED1_LINKTXRX                                             \
                                0x00000080  // Link OK/Blink on TX/RX Activity
#define EPHY_LEDCFG_LED0_M      0x0000000F  // LED0 Configuration
#define EPHY_LEDCFG_LED0_LINK   0x00000000  // Link OK
#define EPHY_LEDCFG_LED0_RXTX   0x00000001  // RX/TX Activity
#define EPHY_LEDCFG_LED0_TX     0x00000002  // TX Activity
#define EPHY_LEDCFG_LED0_RX     0x00000003  // RX Activity
#define EPHY_LEDCFG_LED0_COL    0x00000004  // Collision
#define EPHY_LEDCFG_LED0_100BT  0x00000005  // 100-Base TX
#define EPHY_LEDCFG_LED0_10BT   0x00000006  // 10-Base TX
#define EPHY_LEDCFG_LED0_FD     0x00000007  // Full Duplex
#define EPHY_LEDCFG_LED0_LINKTXRX                                             \
                                0x00000008  // Link OK/Blink on TX/RX Activity

/** @} */ /* End of group Device_Peripheral_Bitfields */

#ifdef __cplusplus
}
#endif


#endif  /* __MSP432E401Y_H__ */

