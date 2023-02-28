/*!
 * @file        apm32f0xx.h
 *
 * @brief       CMSIS Cortex-M0 Device Peripheral Access Layer Header File.
 *
 * @details     This file contains all the peripheral register's definitions, bits definitions and memory mapping
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F0XX_H
#define __APM32F0XX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32F0xx
  * @brief Peripheral Access Layer
  @{
*/
#if defined (APM32F030x6) || defined (APM32F030x8) || defined (APM32F030xC)
#define    APM32F030
#endif /*!< APM32F030x6 or APM32F030x8 or APM32F030xC */

#if defined (APM32F051x6) || defined (APM32F051x8)
#define    APM32F051
#endif /*!< APM32F051x6 or APM32F051x8 */

#if defined (APM32F070xB)
#define    APM32F070
#endif /*!< APM32F070xB */

#if defined (APM32F071x8) || defined (APM32F071xB)
#define    APM32F071
#endif /*!< APM32F071x8 or  APM32F071xB */

#if defined (APM32F072x8) || defined (APM32F072xB)
#define    APM32F072
#endif /*!< APM32F072x8 or  APM32F072xB */

#if defined (APM32F091xB) || defined (APM32F091xC)
#define    APM32F091
#endif /*!< APM32F091xB or APM32F091xC */

#if !defined (APM32F030) && !defined (APM32F051) && !defined (APM32F070) && \
    !defined (APM32F071) && !defined (APM32F072) && !defined (APM32F091)
#error "Please select first the target APM32F0xx device used in your application (in apm32f0xx.h file)"
#endif

/** @defgroup HSE_Macros
  @{
*/

/**
 * @brief Define Value of the External oscillator in Hz
 */
#ifndef  HSE_VALUE
#define  HSE_VALUE              ((uint32_t)8000000)
#endif

/* Time out for HSE start up */
#define HSE_STARTUP_TIMEOUT     ((uint32_t)0x10000)

/* Time out for HSI start up */
#define HSI_STARTUP_TIMEOUT    ((uint32_t)0x0500)

/* Value of the Internal oscillator in Hz */
#define HSI_VALUE              ((uint32_t)8000000)
#define HSI14_VALUE            ((uint32_t)14000000)
#define HSI48_VALUE            ((uint32_t)48000000)

#define LSE_VALUE              ((uint32_t)32768)
#define LSI_VALUE              ((uint32_t)40000)

/**@} end of group HSE_Macros */

/** @defgroup APM32F0xx_StdPeripheral_Library_Version
  @{
*/

/*!< [31:16] APM32F0XX Standard Peripheral Library main version V1.0.3*/
#define __APM32F0_DEVICE_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __APM32F0_DEVICE_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __APM32F0_DEVICE_VERSION_SUB2   (0x03) /*!< [15:8]  sub2 version */
#define __APM32F0_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __APM32F0_DEVICE_VERSION        ((__APM32F0_DEVICE_VERSION_MAIN << 24)\
                                        |(__APM32F0_DEVICE_VERSION_SUB1 << 16)\
                                        |(__APM32F0_DEVICE_VERSION_SUB2 << 8 )\
                                        |(__APM32F0_DEVICE_VERSION_RC))

/**@} end of group APM32F0xx_StdPeripheral_Library_Version */

/** @defgroup Configuraion_for_CMSIS
  @{
*/

/* Core Revision r0p1  */
#define __CM0PLUS_REV             0
/* APM32F0xx do not provide MPU  */
#define __MPU_PRESENT             0
/* APM32F0xx uses 2 Bits for the Priority Levels */
#define __NVIC_PRIO_BITS          2
/* Set to 1 if different SysTick Config is used */
#define __Vendor_SysTickConfig    0
/* Set to 1 if different Vector Table Offset is used */
#define __VTOR_PRESENT            1

/**
 * @brief    Interrupt Number Definition
 */
typedef enum
{
    /*  Cortex-M0 Processor Exceptions Numbers */
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt */
    HardFault_IRQn              = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt */
    SVC_IRQn                    = -5,     /*!< 11 Cortex-M0 SV Call Interrupt */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M0 System Tick Interrupt */

#if defined (APM32F030)
    /*  APM32F030 specific Interrupt Numbers */
    WWDT_IRQn                   =  0,     /*!< Window WatchDog Interrupt */
    RTC_IRQn                    =  2,     /*!< RTC Interrupt through EINT Lines 17, 19 and 20 */
    FLASH_IRQn                  =  3,     /*!< FLASH global Interrupt */
    RCM_IRQn                    =  4,     /*!< RCM global Interrupt */
    EINT0_1_IRQn                =  5,     /*!< EINT Line 0 and 1 Interrupt */
    EINT2_3_IRQn                =  6,     /*!< EINT Line 2 and 3 Interrupt */
    EINT4_15_IRQn               =  7,     /*!< EINT Line 4 to 15 Interrupt */
    DMA1_CH1_IRQn               =  9,     /*!< DMA1 Channel 1 Interrupt */
    DMA1_CH2_3_IRQn             = 10,     /*!< DMA1 Channel 2 and Channel 3 Interrupt */
    DMA1_CH4_5_IRQn             = 11,     /*!< DMA1 Channel 4 and Channel 5 Interrupt */
    ADC1_IRQn                   = 12,     /*!< ADC1 Interrupt */
    TMR1_BRK_UP_TRG_COM_IRQn    = 13,     /*!< TMR1 Break, Update, Trigger and Commutation Interrupt */
    TMR1_CC_IRQn                = 14,     /*!< TMR1 Capture Compare Interrupt */
    TMR3_IRQn                   = 16,     /*!< TMR3 global Interrupt */
    TMR6_IRQn                   = 17,     /*!< TMR6 global Interrupt */
    TMR7_IRQn                   = 18,     /*!< TMR7 global Interrupt */
    TMR14_IRQn                  = 19,     /*!< TMR14 global Interrupt */
    TMR15_IRQn                  = 20,     /*!< TMR15 global Interrupt */
    TMR16_IRQn                  = 21,     /*!< TMR16 global Interrupt */
    TMR17_IRQn                  = 22,     /*!< TMR17 global Interrupt */
    I2C1_IRQn                   = 23,     /*!< I2C1 Event Interrupt */
    I2C2_IRQn                   = 24,     /*!< I2C2 Event Interrupt */
    SPI1_IRQn                   = 25,     /*!< SPI1 global Interrupt */
    SPI2_IRQn                   = 26,     /*!< SPI2 global Interrupt */
    USART1_IRQn                 = 27,     /*!< USART1 global Interrupt */
    USART2_IRQn                 = 28,     /*!< USART2 global Interrupt */
    USART3_6_IRQn               = 29      /*!< USART3 to USART6 global Interrupt */
#elif defined (APM32F051)
    /*  APM32F051 specific Interrupt Numbers */
    WWDT_IRQn                   =  0,     /*!< Window WatchDog Interrupt */
    PVD_IRQn                    =  1,     /*!< PVD through EXTI Line detect Interrupt */
    RTC_IRQn                    =  2,     /*!< RTC Interrupt through EINT Lines 17, 19 and 20 */
    FLASH_IRQn                  =  3,     /*!< FLASH global Interrupt */
    RCM_IRQn                    =  4,     /*!< RCM global Interrupt */
    EINT0_1_IRQn                =  5,     /*!< EINT Line 0 and 1 Interrupt */
    EINT2_3_IRQn                =  6,     /*!< EINT Line 2 and 3 Interrupt */
    EINT4_15_IRQn               =  7,     /*!< EINT Line 4 to 15 Interrupt */
    TSC_IRQn                    =  8,     /*!< TSC  Interrupt */
    DMA1_CH1_IRQn               =  9,     /*!< DMA1 Channel 1 Interrupt */
    DMA1_CH2_3_IRQn             = 10,     /*!< DMA1 Channel 2 and Channel 3 Interrupt */
    DMA1_CH4_5_IRQn             = 11,     /*!< DMA1 Channel 4 and Channel 5 Interrupt */
    ADC1_COMP_IRQn              = 12,     /*!< ADC1 and comparator Interrupt */
    TMR1_BRK_UP_TRG_COM_IRQn    = 13,     /*!< TMR1 Break, Update, Trigger and Commutation Interrupt */
    TMR1_CC_IRQn                = 14,     /*!< TMR1 Capture Compare Interrupt */
    TMR2_IRQn                   = 15,     /*!< TMR2 global Interrupt */
    TMR3_IRQn                   = 16,     /*!< TMR3 global Interrupt */
    TMR6_DAC_IRQn               = 17,     /*!< TMR6 and DAC Interrupt */
    TMR14_IRQn                  = 19,     /*!< TMR14 global Interrupt */
    TMR15_IRQn                  = 20,     /*!< TMR15 global Interrupt */
    TMR16_IRQn                  = 21,     /*!< TMR16 global Interrupt */
    TMR17_IRQn                  = 22,     /*!< TMR17 global Interrupt */
    I2C1_IRQn                   = 23,     /*!< I2C1 Event Interrupt */
    I2C2_IRQn                   = 24,     /*!< I2C2 Event Interrupt */
    SPI1_IRQn                   = 25,     /*!< SPI1 global Interrupt */
    SPI2_IRQn                   = 26,     /*!< SPI2 global Interrupt */
    USART1_IRQn                 = 27,     /*!< USART1 global Interrupt */
    USART2_IRQn                 = 28,     /*!< USART2 global Interrupt */
    CEC_IRQn                    = 30      /*!< CEC global Interrupt */
#elif defined (APM32F070)
    /*  APM32F070 specific Interrupt Numbers */
    WWDT_IRQn                   =  0,     /*!< Window WatchDog Interrupt */
    RTC_IRQn                    =  2,     /*!< RTC Interrupt through EINT Lines */
    FLASH_IRQn                  =  3,     /*!< FLASH global Interrupt */
    RCM_IRQn                    =  4,     /*!< RCM global Interrupt */
    EINT0_1_IRQn                =  5,     /*!< EINT Line 0 and 1 Interrupt */
    EINT2_3_IRQn                =  6,     /*!< EINT Line 2 and 3 Interrupt */
    EINT4_15_IRQn               =  7,     /*!< EINT Line 4 to 15 Interrupt */
    DMA1_CH1_IRQn               =  9,     /*!< DMA1 Channel 1 Interrupt */
    DMA1_CH2_3_IRQn             = 10,     /*!< DMA1 Channel 2 and Channel 3 Interrupts */
    DMA1_CH4_5_IRQn             = 11,     /*!< DMA1 Channel 4, Channel 5 Interrupts */
    ADC1_IRQn                   = 12,     /*!< ADC1 Interrupt */
    TMR1_BRK_UP_TRG_COM_IRQn    = 13,     /*!< TMR1 Break, Update, Trigger and Commutation Interrupt */
    TMR1_CC_IRQn                = 14,     /*!< TMR1 Capture Compare Interrupt */
    TMR3_IRQn                   = 16,     /*!< TMR3 global Interrupt */
    TMR6_IRQn                   = 17,     /*!< TMR6 global Interrupt */
    TMR7_IRQn                   = 18,     /*!< TMR7 global Interrupt */
    TMR14_IRQn                  = 19,     /*!< TMR14 global Interrupt */
    TMR15_IRQn                  = 20,     /*!< TMR15 global Interrupt */
    TMR16_IRQn                  = 21,     /*!< TMR16 global Interrupt */
    TMR17_IRQn                  = 22,     /*!< TMR17 global Interrupt */
    I2C1_IRQn                   = 23,     /*!< I2C1 Event Interrupt */
    I2C2_IRQn                   = 24,     /*!< I2C2 Event Interrupt */
    SPI1_IRQn                   = 25,     /*!< SPI1 global Interrupt */
    SPI2_IRQn                   = 26,     /*!< SPI2 global Interrupt */
    USART1_IRQn                 = 27,     /*!< USART1 global Interrupt */
    USART2_IRQn                 = 28,     /*!< USART2 global Interrupt */
    USART3_4_IRQn               = 29,     /*!< USART3 and USART4 global Interrupt */
    USBD_IRQn                   = 31      /*!< USB Low Priority global Interrupt */
#elif defined (APM32F071)
    /*  APM32F071 specific Interrupt Numbers */
    WWDT_IRQn                   =  0,     /*!< Window WatchDog Interrupt */
    PVD_VDDIO2_IRQn             =  1,     /*!< PVD and VDDIO2 Interrupt */
    RTC_IRQn                    =  2,     /*!< RTC Interrupt through EINT Lines */
    FLASH_IRQn                  =  3,     /*!< FLASH global Interrupt */
    RCM_CRS_IRQn                =  4,     /*!< RCM and CRS global Interrupt */
    EINT0_1_IRQn                =  5,     /*!< EINT Line 0 and 1 Interrupt */
    EINT2_3_IRQn                =  6,     /*!< EINT Line 2 and 3 Interrupt */
    EINT4_15_IRQn               =  7,     /*!< EINT Line 4 to 15 Interrupt */
    TSC_IRQn                    =  8,     /*!< TSC Interrupt */
    DMA1_CH1_IRQn               =  9,     /*!< DMA1 Channel 1 Interrupt */
    DMA1_CH2_3_IRQn             = 10,     /*!< DMA1 Channel 2 and Channel 3 Interrupts */
    DMA1_CH4_5_6_7_IRQn         = 11,     /*!< DMA1 Channel 4, Channel 5, Channel 6 and Channel 7 Interrupts */
    ADC1_COMP_IRQn              = 12,     /*!< ADC1 and comparator Interrupt */
    TMR1_BRK_UP_TRG_COM_IRQn    = 13,     /*!< TMR1 Break, Update, Trigger and Commutation Interrupt */
    TMR1_CC_IRQn                = 14,     /*!< TMR1 Capture Compare Interrupt */
    TMR2_IRQn                   = 15,     /*!< TMR2 global Interrupt */
    TMR3_IRQn                   = 16,     /*!< TMR3 global Interrupt */
    TMR6_DAC_IRQn               = 17,     /*!< TMR6 and DAC Interrupt */
    TMR7_IRQn                   = 18,     /*!< TMR7 global Interrupt */
    TMR14_IRQn                  = 19,     /*!< TMR14 global Interrupt */
    TMR15_IRQn                  = 20,     /*!< TMR15 global Interrupt */
    TMR16_IRQn                  = 21,     /*!< TMR16 global Interrupt */
    TMR17_IRQn                  = 22,     /*!< TMR17 global Interrupt */
    I2C1_IRQn                   = 23,     /*!< I2C1 Event Interrupt */
    I2C2_IRQn                   = 24,     /*!< I2C2 Event Interrupt */
    SPI1_IRQn                   = 25,     /*!< SPI1 global Interrupt */
    SPI2_IRQn                   = 26,     /*!< SPI2 global Interrupt */
    USART1_IRQn                 = 27,     /*!< USART1 global Interrupt */
    USART2_IRQn                 = 28,     /*!< USART2 global Interrupt */
    USART3_4_IRQn               = 29,     /*!< USART3 and USART4 global Interrupt */
    CEC_IRQn                    = 30      /*!< CEC global Interrupt */
#elif defined (APM32F072)
    /*  APM32F072 specific Interrupt Numbers */
    WWDT_IRQn                   =  0,     /*!< Window WatchDog Interrupt */
    PVD_VDDIO2_IRQn             =  1,     /*!< PVD and VDDIO2 Interrupt */
    RTC_IRQn                    =  2,     /*!< RTC Interrupt through EINT Lines 17, 19 and 20 */
    FLASH_IRQn                  =  3,     /*!< FLASH global Interrupt */
    RCM_CRS_IRQn                =  4,     /*!< RCM and CRS global Interrupt */
    EINT0_1_IRQn                =  5,     /*!< EINT Line 0 and 1 Interrupt */
    EINT2_3_IRQn                =  6,     /*!< EINT Line 2 and 3 Interrupt */
    EINT4_15_IRQn               =  7,     /*!< EINT Line 4 to 15 Interrupt */
    TSC_IRQn                    =  8,     /*!< TSC Interrupt */
    DMA1_CH1_IRQn               =  9,     /*!< DMA1 Channel 1 Interrupt */
    DMA1_CH2_3_IRQn             = 10,     /*!< DMA1 Channel 2 and Channel 3 Interrupts */
    DMA1_CH4_5_6_7_IRQn         = 11,     /*!< DMA1 Channel 4, Channel 5, Channel 6 and Channel 7 Interrupts */
    ADC1_COMP_IRQn              = 12,     /*!< ADC1 and comparator Interrupt */
    TMR1_BRK_UP_TRG_COM_IRQn    = 13,     /*!< TMR1 Break, Update, Trigger and Commutation Interrupt */
    TMR1_CC_IRQn                = 14,     /*!< TMR1 Capture Compare Interrupt */
    TMR2_IRQn                   = 15,     /*!< TMR2 global Interrupt */
    TMR3_IRQn                   = 16,     /*!< TMR3 global Interrupt */
    TMR6_DAC_IRQn               = 17,     /*!< TMR6 and DAC Interrupt */
    TMR7_IRQn                   = 18,     /*!< TMR7 global Interrupt */
    TMR14_IRQn                  = 19,     /*!< TMR14 global Interrupt */
    TMR15_IRQn                  = 20,     /*!< TMR15 global Interrupt */
    TMR16_IRQn                  = 21,     /*!< TMR16 global Interrupt */
    TMR17_IRQn                  = 22,     /*!< TMR17 global Interrupt */
    I2C1_IRQn                   = 23,     /*!< I2C1 Event Interrupt */
    I2C2_IRQn                   = 24,     /*!< I2C2 Event Interrupt */
    SPI1_IRQn                   = 25,     /*!< SPI1 global Interrupt */
    SPI2_IRQn                   = 26,     /*!< SPI2 global Interrupt */
    USART1_IRQn                 = 27,     /*!< USART1 global Interrupt */
    USART2_IRQn                 = 28,     /*!< USART2 global Interrupt */
    USART3_4_IRQn               = 29,     /*!< USART3 and USART4 global Interrupt */
    CEC_CAN_IRQn                = 30,     /*!< CEC and CAN global Interrupt */
    USBD_IRQn                   = 31      /*!< USB Low Priority global Interrupt */
#elif defined (APM32F091)
    /*  APM32F091 specific Interrupt Numbers */
    WWDT_IRQn                   =  0,     /*!< Window WatchDog Interrupt */
    PVD_VDDIO2_IRQn             =  1,     /*!< PVD and VDDIO2 Interrupt */
    RTC_IRQn                    =  2,     /*!< RTC Interrupt through EINT Lines 17, 19 and 20 */
    FLASH_IRQn                  =  3,     /*!< FLASH global Interrupt */
    RCM_CRS_IRQn                =  4,     /*!< RCM and CRS global Interrupt */
    EINT0_1_IRQn                =  5,     /*!< EINT Line 0 and 1 Interrupt */
    EINT2_3_IRQn                =  6,     /*!< EINT Line 2 and 3 Interrupt */
    EINT4_15_IRQn               =  7,     /*!< EINT Line 4 to 15 Interrupt */
    TSC_IRQn                    =  8,     /*!< TSC Interrupt */
    DMA1_CH1_IRQn               =  9,     /*!< DMA1 Channel 1 Interrupt */
    DMA1_CH2_3_DMA2_CH1_2_IRQn  = 10,     /*!< DMA1 Channel 2 and 3 DMA2 Channel 1 and 2 Interrupts */
    DMA1_CH4_7_DMA2_CH3_5_IRQn  = 11,     /*!< DMA1 Channel 4 to 7  DMA2 Channel 3 to 5 Interrupts */
    ADC1_COMP_IRQn              = 12,     /*!< ADC1 and comparator Interrupt */
    TMR1_BRK_UP_TRG_COM_IRQn    = 13,     /*!< TMR1 Break, Update, Trigger and Commutation Interrupt */
    TMR1_CC_IRQn                = 14,     /*!< TMR1 Capture Compare Interrupt */
    TMR2_IRQn                   = 15,     /*!< TMR2 global Interrupt */
    TMR3_IRQn                   = 16,     /*!< TMR3 global Interrupt */
    TMR6_DAC_IRQn               = 17,     /*!< TMR6 and DAC Interrupt */
    TMR7_IRQn                   = 18,     /*!< TMR7 global Interrupt */
    TMR14_IRQn                  = 19,     /*!< TMR14 global Interrupt */
    TMR15_IRQn                  = 20,     /*!< TMR15 global Interrupt */
    TMR16_IRQn                  = 21,     /*!< TMR16 global Interrupt */
    TMR17_IRQn                  = 22,     /*!< TMR17 global Interrupt */
    I2C1_IRQn                   = 23,     /*!< I2C1 Event Interrupt */
    I2C2_IRQn                   = 24,     /*!< I2C2 Event Interrupt */
    SPI1_IRQn                   = 25,     /*!< SPI1 global Interrupt */
    SPI2_IRQn                   = 26,     /*!< SPI2 global Interrupt */
    USART1_IRQn                 = 27,     /*!< USART1 global Interrupt */
    USART2_IRQn                 = 28,     /*!< USART2 global Interrupt */
    USART3_8_IRQn               = 29,     /*!< USART3 and USART8 global Interrupt */
    CEC_CAN_IRQn                = 30      /*!< CEC and CAN global Interrupt */
#endif
} IRQn_Type;

/**@} end of group Configuraion_for_CMSIS */

/* Includes */

#include "core_cm0plus.h"     /*!< Cortex-M0+ processor and core peripherals */
#include "system_apm32f0xx.h" /*!< APM32F0xx System Header */
#include <stdint.h>

/** @defgroup Exported_types
  * @{
*/

typedef enum {FALSE, TRUE} BOOL;

enum {BIT_RESET, BIT_SET};

enum {RESET = 0, SET = !RESET};

enum {DISABLE = 0, ENABLE = !DISABLE};

enum {ERROR = 0, SUCCESS = !ERROR};

#ifndef __IM
#define __IM   __I
#endif
#ifndef __OM
#define __OM   __O
#endif
#ifndef __IOM
#define __IOM  __IO
#endif

#ifndef NULL
#define NULL   ((void *)0)
#endif

#if defined (__CC_ARM )
#pragma anon_unions
#endif

/**@} end of group Exported_types */

/** @defgroup Peripheral_registers_structures
  @{
*/


/**
  * @brief Analog-to-digital converter (ADC)
  */

typedef struct
{
    /* interrupt and status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t ADCRDYFLG  : 1;
            __IOM uint32_t EOSMPFLG   : 1;
            __IOM uint32_t EOCFLG     : 1;
            __IOM uint32_t EOSEQFLG   : 1;
            __IOM uint32_t OVREFLG    : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t AWDFLG     : 1;
            __IM  uint32_t RESERVED2  : 24;
        } STS_B;
    } ;

    /* interrupt enable register */
    union
    {
        __IOM uint32_t INT;

        struct
        {
            __IOM uint32_t ADCRDYIEN  : 1;
            __IOM uint32_t EOSMPIEN   : 1;
            __IOM uint32_t EOCIEN     : 1;
            __IOM uint32_t EOSEQIEN   : 1;
            __IOM uint32_t OVRIEN     : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t AWDIEN     : 1;
            __IM  uint32_t RESERVED2  : 24;
        } INT_B;
    } ;

    /* control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t ADCEN      : 1;
            __IOM uint32_t ADCD       : 1;
            __IOM uint32_t STARTCEN   : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t STOPCEN    : 1;
            __IM  uint32_t RESERVED2  : 26;
            __IOM uint32_t CAL        : 1;
        } CTRL_B;
    } ;

    /* configuration register 1 */
    union
    {
        __IOM uint32_t CFG1;

        struct
        {
            __IOM uint32_t DMAEN      : 1;
            __IOM uint32_t DMACFG     : 1;
            __IOM uint32_t SCANSEQDIR : 1;
            __IOM uint32_t DATARESCFG : 2;
            __IOM uint32_t DALIGCFG   : 1;
            __IOM uint32_t EXTTRGSEL  : 3;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t EXTPOLSEL  : 2;
            __IOM uint32_t OVRMAG     : 1;
            __IOM uint32_t CMODESEL   : 1;
            __IOM uint32_t WAITCEN    : 1;
            __IOM uint32_t AOEN       : 1;
            __IOM uint32_t DISCEN     : 1;
            __IM  uint32_t RESERVED2  : 5;
            __IOM uint32_t AWDCHEN    : 1;
            __IOM uint32_t AWDEN      : 1;
            __IM  uint32_t RESERVED3  : 2;
            __IOM uint32_t AWDCHSEL   : 5;
            __IM  uint32_t RESERVED4  : 1;
        } CFG1_B;
    } ;

    /* configuration register 2 */
    union
    {
        __IOM uint32_t CFG2;

        struct
        {
            __IM  uint32_t RESERVED1  : 30;
            __IOM uint32_t CLKCFG     : 2;
        } CFG2_B;
    } ;

    /* sampling time register */
    union
    {
        __IOM uint32_t SMPTIM;

        struct
        {
            __IOM uint32_t SMPCYCSEL  : 3;
            __IM  uint32_t RESERVED1  : 29;
        } SMPTIM_B;
    } ;
    __IM  uint32_t  RESERVED[2];

    /* watchdog threshold register */
    union
    {
        __IOM uint32_t AWDT;

        struct
        {
            __IOM uint32_t AWDLT      : 12;
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t AWDHT      : 12;
            __IM  uint32_t RESERVED2  : 4;
        } AWDT_B;
    } ;
    __IM  uint32_t  RESERVED1;

    /* channel selection register */
    union
    {
        __IOM uint32_t CHSEL;

        struct
        {
            __IOM uint32_t CH0SEL     : 1;
            __IOM uint32_t CH1SEL     : 1;
            __IOM uint32_t CH2SEL     : 1;
            __IOM uint32_t CH3SEL     : 1;
            __IOM uint32_t CH4SEL     : 1;
            __IOM uint32_t CH5SEL     : 1;
            __IOM uint32_t CH6SEL     : 1;
            __IOM uint32_t CH7SEL     : 1;
            __IOM uint32_t CH8SEL     : 1;
            __IOM uint32_t CH9SEL     : 1;
            __IOM uint32_t CH10SEL    : 1;
            __IOM uint32_t CH11SEL    : 1;
            __IOM uint32_t CH12SEL    : 1;
            __IOM uint32_t CH13SEL    : 1;
            __IOM uint32_t CH14SEL    : 1;
            __IOM uint32_t CH15SEL    : 1;
            __IOM uint32_t CH16SEL    : 1;
            __IOM uint32_t CH17SEL    : 1;
            __IOM uint32_t CH18SEL    : 1;
            __IM  uint32_t RESERVED1  : 13;
        } CHSEL_B;
    } ;
    __IM  uint32_t  RESERVED2[5];

    /* data register */
    union
    {
        __IM  uint32_t DATA;

        struct
        {
            __IM  uint32_t DATA       : 16;
            __IM  uint32_t RESERVED1  : 16;
        } DATA_B;
    } ;
    __IM  uint32_t  RESERVED3[177];

    /* common configuration register */
    union
    {
        __IOM uint32_t CCFG;

        struct
        {
            __IM  uint32_t RESERVED1  : 22;
            __IOM uint32_t VREFEN     : 1;
            __IOM uint32_t TSEN       : 1;
            __IOM uint32_t VBATEN     : 1;
            __IM  uint32_t RESERVED2  : 7;
        } CCFG_B;
    } ;
} ADC_T;

/**
 * @brief Controller area network (CAN) TxMailBox Typedef
 */
typedef struct
{
    /* TX mailbox identifier register */
    union
    {
        __IOM uint32_t TXMID;

        struct
        {
            __IOM uint32_t TXMREQ     : 1;
            __IOM uint32_t TXRFREQ    : 1;
            __IOM uint32_t IDTYPESEL  : 1;
            __IOM uint32_t EXTID      : 18;
            __IOM uint32_t STDID      : 11;
        } TXMID_B;
    } ;

    /* Mailbox data length control and time stamp register */
    union
    {
        __IOM uint32_t TXDLEN;

        struct
        {
            __IOM uint32_t DLCODE     : 4;
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t TXGT       : 1;
            __IM  uint32_t RESERVED2  : 7;
            __IOM uint32_t MTS        : 16;
        } TXDLEN_B;
    } ;

    /* Mailbox data low register 0*/
    union
    {
        __IOM uint32_t TXMDL;

        struct
        {
            __IOM uint32_t DATABYTE0  : 8;
            __IOM uint32_t DATABYTE1  : 8;
            __IOM uint32_t DATABYTE2  : 8;
            __IOM uint32_t DATABYTE3  : 8;
        } TXMDL_B;
    } ;

    /* Mailbox data high register 0*/
    union
    {
        __IOM uint32_t TXMDH;

        struct
        {
            __IOM uint32_t DATABYTE4  : 8;
            __IOM uint32_t DATABYTE5  : 8;
            __IOM uint32_t DATABYTE6  : 8;
            __IOM uint32_t DATABYTE7  : 8;
        } TXMDH_B;
    } ;

} CAN_TxMailBox_T;

/**
 * @brief Controller area network (CAN) Receive FIFO MailBox Typedef
 */
typedef struct
{
    /* Receive FIFO mailbox identifier register */
    union
    {
        __IM  uint32_t RXMID;

        struct
        {
            __IM  uint32_t RESERVED1  : 1;
            __IM  uint32_t RFTXREQ    : 1;
            __IM  uint32_t IDTYPESEL  : 1;
            __IM  uint32_t EXTID      : 18;
            __IM  uint32_t STDID      : 11;
        } RXMID_B;
    } ;

    /* Receive FIFO mailbox data length control and time stamp register */
    union
    {
        __IM  uint32_t RXDLEN;

        struct
        {
            __IM  uint32_t DLCODE     : 4;
            __IM  uint32_t RESERVED1  : 4;
            __IM  uint32_t FMIDX      : 8;
            __IM  uint32_t MTS        : 16;
        } RXDLEN_B;
    } ;

    /* Receive FIFO mailbox data low register */
    union
    {
        __IM  uint32_t RXMDL;

        struct
        {
            __IM  uint32_t DATABYTE0  : 8;
            __IM  uint32_t DATABYTE1  : 8;
            __IM  uint32_t DATABYTE2  : 8;
            __IM  uint32_t DATABYTE3  : 8;
        } RXMDL_B;
    } ;

    /*  Receive FIFO mailbox data high register */
    union
    {
        __IM  uint32_t RXMDH;

        struct
        {
            __IM  uint32_t DATABYTE4  : 8;
            __IM  uint32_t DATABYTE5  : 8;
            __IM  uint32_t DATABYTE6  : 8;
            __IM  uint32_t DATABYTE7  : 8;
        } RXMDH_B;
    } ;

} CAN_RxFIFO_T;

/**
 * @brief Controller area network (CAN) Filter register Typedef
 */
typedef struct
{
    /* CAN Filter1 register */
    union
    {
        __IOM uint32_t  R1;

        struct
        {
            __IOM uint32_t FBIT0      : 1;
            __IOM uint32_t FBIT1      : 1;
            __IOM uint32_t FBIT2      : 1;
            __IOM uint32_t FBIT3      : 1;
            __IOM uint32_t FBIT4      : 1;
            __IOM uint32_t FBIT5      : 1;
            __IOM uint32_t FBIT6      : 1;
            __IOM uint32_t FBIT7      : 1;
            __IOM uint32_t FBIT8      : 1;
            __IOM uint32_t FBIT9      : 1;
            __IOM uint32_t FBIT10     : 1;
            __IOM uint32_t FBIT11     : 1;
            __IOM uint32_t FBIT12     : 1;
            __IOM uint32_t FBIT13     : 1;
            __IOM uint32_t FBIT14     : 1;
            __IOM uint32_t FBIT15     : 1;
            __IOM uint32_t FBIT16     : 1;
            __IOM uint32_t FBIT17     : 1;
            __IOM uint32_t FBIT18     : 1;
            __IOM uint32_t FBIT19     : 1;
            __IOM uint32_t FBIT20     : 1;
            __IOM uint32_t FBIT21     : 1;
            __IOM uint32_t FBIT22     : 1;
            __IOM uint32_t FBIT23     : 1;
            __IOM uint32_t FBIT24     : 1;
            __IOM uint32_t FBIT25     : 1;
            __IOM uint32_t FBIT26     : 1;
            __IOM uint32_t FBIT27     : 1;
            __IOM uint32_t FBIT28     : 1;
            __IOM uint32_t FBIT29     : 1;
            __IOM uint32_t FBIT30     : 1;
            __IOM uint32_t FBIT31     : 1;
        } R1_B;
    };

    /* CAN Filter2 register */
    union
    {
        __IOM uint32_t  R2;

        struct
        {
            __IOM uint32_t FBIT0      : 1;
            __IOM uint32_t FBIT1      : 1;
            __IOM uint32_t FBIT2      : 1;
            __IOM uint32_t FBIT3      : 1;
            __IOM uint32_t FBIT4      : 1;
            __IOM uint32_t FBIT5      : 1;
            __IOM uint32_t FBIT6      : 1;
            __IOM uint32_t FBIT7      : 1;
            __IOM uint32_t FBIT8      : 1;
            __IOM uint32_t FBIT9      : 1;
            __IOM uint32_t FBIT10     : 1;
            __IOM uint32_t FBIT11     : 1;
            __IOM uint32_t FBIT12     : 1;
            __IOM uint32_t FBIT13     : 1;
            __IOM uint32_t FBIT14     : 1;
            __IOM uint32_t FBIT15     : 1;
            __IOM uint32_t FBIT16     : 1;
            __IOM uint32_t FBIT17     : 1;
            __IOM uint32_t FBIT18     : 1;
            __IOM uint32_t FBIT19     : 1;
            __IOM uint32_t FBIT20     : 1;
            __IOM uint32_t FBIT21     : 1;
            __IOM uint32_t FBIT22     : 1;
            __IOM uint32_t FBIT23     : 1;
            __IOM uint32_t FBIT24     : 1;
            __IOM uint32_t FBIT25     : 1;
            __IOM uint32_t FBIT26     : 1;
            __IOM uint32_t FBIT27     : 1;
            __IOM uint32_t FBIT28     : 1;
            __IOM uint32_t FBIT29     : 1;
            __IOM uint32_t FBIT30     : 1;
            __IOM uint32_t FBIT31     : 1;
        } R2_B;
    };
} CAN_FilterRegister_T;

/**
  * @brief Controller area network (CAN)
  */

typedef struct
{
    /* Master control register */
    union
    {
        __IOM uint32_t MCTRL;

        struct
        {
            __IOM uint32_t INITREQ    : 1;
            __IOM uint32_t SLEEPREQ   : 1;
            __IOM uint32_t TXFPCFG    : 1;
            __IOM uint32_t RXFLOCK    : 1;
            __IOM uint32_t ARTXMD     : 1;
            __IOM uint32_t AWUPCFG    : 1;
            __IOM uint32_t ALBOFFM    : 1;
            __IOM uint32_t TTCM       : 1;
            __IM  uint32_t RESERVED1  : 7;
            __IOM uint32_t SWRST      : 1;
            __IOM uint32_t DBGFRZE    : 1;
            __IM  uint32_t RESERVED2  : 15;
        } MCTRL_B;
    } ;

    /* Master status register */
    union
    {
        __IOM uint32_t MSTS;

        struct
        {
            __IM  uint32_t INITFLG    : 1;
            __IM  uint32_t SLEEPFLG   : 1;
            __IOM uint32_t ERRIFLG    : 1;
            __IOM uint32_t WUPIFLG    : 1;
            __IOM uint32_t SLEEPIFLG  : 1;
            __IM  uint32_t RESERVED1  : 3;
            __IM  uint32_t TXMFLG     : 1;
            __IM  uint32_t RXMFLG     : 1;
            __IM  uint32_t LSAMVALUE  : 1;
            __IM  uint32_t RXSIGL     : 1;
            __IM  uint32_t RESERVED2  : 20;
        } MSTS_B;
    } ;

    /* Transmit status register */
    union
    {
        __IOM uint32_t TXSTS;

        struct
        {
            __IOM uint32_t REQCFLG0   : 1;
            __IOM uint32_t TXSUSFLG0  : 1;
            __IOM uint32_t ARBLSTFLG0 : 1;
            __IOM uint32_t TXERRFLG0  : 1;
            __IM  uint32_t RESERVED1  : 3;
            __IOM uint32_t ABREQFLG0  : 1;
            __IOM uint32_t REQCFLG1   : 1;
            __IOM uint32_t TXSUSFLG1  : 1;
            __IOM uint32_t ARBLSTFLG1 : 1;
            __IOM uint32_t TXERRFLG1  : 1;
            __IM  uint32_t RESERVED2  : 3;
            __IOM uint32_t ABREQFLG1  : 1;
            __IOM uint32_t REQCFLG2   : 1;
            __IOM uint32_t TXSUSFLG2  : 1;
            __IOM uint32_t ARBLSTFLG2 : 1;
            __IOM uint32_t TXERRFLG2  : 1;
            __IM  uint32_t RESERVED3  : 3;
            __IOM uint32_t ABREQFLG2  : 1;
            __IM  uint32_t EMNUM      : 2;
            __IM  uint32_t TXMEFLG0   : 1;
            __IM  uint32_t TXMEFLG1   : 1;
            __IM  uint32_t TXMEFLG2   : 1;
            __IM  uint32_t LOWESTP0   : 1;
            __IM  uint32_t LOWESTP1   : 1;
            __IM  uint32_t LOWESTP2   : 1;
        } TXSTS_B;
    } ;

    /* Receive FIFO 0 register */
    union
    {
        __IOM uint32_t RXF0;

        struct
        {
            __IM  uint32_t FMNUM0     : 2;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t FFULLFLG0  : 1;
            __IOM uint32_t FOVRFLG0   : 1;
            __IOM uint32_t RFOM0      : 1;
            __IM  uint32_t RESERVED2  : 26;
        } RXF0_B;
    } ;

    /* Receive FIFO 1 register */
    union
    {
        __IOM uint32_t RXF1;

        struct
        {
            __IM  uint32_t FMNUM1     : 2;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t FFULLFLG1  : 1;
            __IOM uint32_t FOVRFLG1   : 1;
            __IOM uint32_t RFOM1      : 1;
            __IM  uint32_t RESERVED2  : 26;
        } RXF1_B;
    } ;

    /* Interrupt enable register */
    union
    {
        __IOM uint32_t INTEN;

        struct
        {
            __IOM uint32_t TXMEIE     : 1;
            __IOM uint32_t FMIEN0     : 1;
            __IOM uint32_t FFULLIEN0  : 1;
            __IOM uint32_t FOVRIEN0   : 1;
            __IOM uint32_t FMPIEN1    : 1;
            __IOM uint32_t FFULLIEN1  : 1;
            __IOM uint32_t FOVRIEN1   : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t ERRWIEN    : 1;
            __IOM uint32_t ERRPIEN    : 1;
            __IOM uint32_t BOFFIEN    : 1;
            __IOM uint32_t LECIEN     : 1;
            __IM  uint32_t RESERVED2  : 3;
            __IOM uint32_t ERRIEN     : 1;
            __IOM uint32_t WUPIEN     : 1;
            __IOM uint32_t SLEEPIEN   : 1;
            __IM  uint32_t RESERVED3  : 14;
        } INTEN_B;
    } ;

    /* Error status register */
    union
    {
        __IOM uint32_t ERRSTS;

        struct
        {
            __IM  uint32_t ERRWFLG    : 1;
            __IM  uint32_t ERRPFLG    : 1;
            __IM  uint32_t BOFLG      : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t LERRC      : 3;
            __IM  uint32_t RESERVED2  : 9;
            __IM  uint32_t TXERRCNT   : 8;
            __IM  uint32_t RXERRCNT   : 8;
        } ERRSTS_B;
    } ;

    /* Bit timing register */
    union
    {
        __IOM uint32_t BITTIM;

        struct
        {
            __IOM uint32_t BRPSC      : 10;
            __IM  uint32_t RESERVED1  : 6;
            __IOM uint32_t TIMSEG1    : 4;
            __IOM uint32_t TIMSEG2    : 3;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t RSYNJW     : 2;
            __IM  uint32_t RESERVED3  : 4;
            __IOM uint32_t LBKMEN     : 1;
            __IOM uint32_t SILMEN     : 1;
        } BITTIM_B;
    } ;
    __IM uint32_t  RESERVED1[88];

    CAN_TxMailBox_T sTxMailBox[3];

    CAN_RxFIFO_T sRxFIFO[2];

    __IM uint32_t  RESERVED2[12];

    /* Filter master register */
    union
    {
        __IOM uint32_t FCTRL;

        struct
        {
            __IOM uint32_t FIM        : 1;
            __IM  uint32_t RESERVED1  : 31;
        } FCTRL_B;
    } ;

    /*  Filter mode register */
    union
    {
        __IOM uint32_t FMCFG;

        struct
        {
            __IOM uint32_t FMCFG0     : 1;
            __IOM uint32_t FMCFG1     : 1;
            __IOM uint32_t FMCFG2     : 1;
            __IOM uint32_t FMCFG3     : 1;
            __IOM uint32_t FMCFG4     : 1;
            __IOM uint32_t FMCFG5     : 1;
            __IOM uint32_t FMCFG6     : 1;
            __IOM uint32_t FMCFG7     : 1;
            __IOM uint32_t FMCFG8     : 1;
            __IOM uint32_t FMCFG9     : 1;
            __IOM uint32_t FMCFG10    : 1;
            __IOM uint32_t FMCFG11    : 1;
            __IOM uint32_t FMCFG12    : 1;
            __IOM uint32_t FMCFG13    : 1;
            __IM  uint32_t RESERVED1  : 18;
        } FMCFG_B;
    } ;
    __IM  uint32_t  RESERVED3;

    /* Filter scale register */
    union
    {
        __IOM uint32_t FSCFG;

        struct
        {
            __IOM uint32_t FSCFG0     : 1;
            __IOM uint32_t FSCFG1     : 1;
            __IOM uint32_t FSCFG2     : 1;
            __IOM uint32_t FSCFG3     : 1;
            __IOM uint32_t FSCFG4     : 1;
            __IOM uint32_t FSCFG5     : 1;
            __IOM uint32_t FSCFG6     : 1;
            __IOM uint32_t FSCFG7     : 1;
            __IOM uint32_t FSCFG8     : 1;
            __IOM uint32_t FSCFG9     : 1;
            __IOM uint32_t FSCFG10    : 1;
            __IOM uint32_t FSCFG11    : 1;
            __IOM uint32_t FSCFG12    : 1;
            __IOM uint32_t FSCFG13    : 1;
            __IM  uint32_t RESERVED1  : 18;
        } FSCFG_B;
    } ;
    __IM  uint32_t  RESERVED4;

    /* Filter FIFO assignment register */
    union
    {
        __IOM uint32_t FFASS;

        struct
        {
            __IOM uint32_t FFASS0     : 1;
            __IOM uint32_t FFASS1     : 1;
            __IOM uint32_t FFASS2     : 1;
            __IOM uint32_t FFASS3     : 1;
            __IOM uint32_t FFASS4     : 1;
            __IOM uint32_t FFASS5     : 1;
            __IOM uint32_t FFASS6     : 1;
            __IOM uint32_t FFASS7     : 1;
            __IOM uint32_t FFASS8     : 1;
            __IOM uint32_t FFASS9     : 1;
            __IOM uint32_t FFASS10    : 1;
            __IOM uint32_t FFASS11    : 1;
            __IOM uint32_t FFASS12    : 1;
            __IOM uint32_t FFASS13    : 1;
            __IM  uint32_t RESERVED1  : 18;
        } FFASS_B;
    } ;
    __IM  uint32_t  RESERVED5;

    /* Filter activation register */
    union
    {
        __IOM uint32_t FACT;

        struct
        {
            __IOM uint32_t FACT0      : 1;
            __IOM uint32_t FACT1      : 1;
            __IOM uint32_t FACT2      : 1;
            __IOM uint32_t FACT3      : 1;
            __IOM uint32_t FACT4      : 1;
            __IOM uint32_t FACT5      : 1;
            __IOM uint32_t FACT6      : 1;
            __IOM uint32_t FACT7      : 1;
            __IOM uint32_t FACT8      : 1;
            __IOM uint32_t FACT9      : 1;
            __IOM uint32_t FACT10     : 1;
            __IOM uint32_t FACT11     : 1;
            __IOM uint32_t FACT12     : 1;
            __IOM uint32_t FACT13     : 1;
            __IM  uint32_t RESERVED1  : 18;
        } FACT_B;
    } ;
    __IM  uint32_t  RESERVED6[8];

    /* Filter bank register */
    CAN_FilterRegister_T sFilterRegister[14];
} CAN_T;

/**
  * @brief HDMI-CEC registers (CEC)
  */

typedef struct
{
    /* Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t CECEN      : 1;
            __IOM uint32_t TXSM       : 1;
            __IOM uint32_t TXEM       : 1;
            __IM  uint32_t RESERVED1  : 29;
        } CTRL_B;
    } ;

    /* Configuration register */
    union
    {
        __IOM uint32_t CFG;

        struct
        {
            __IOM uint32_t SFTCFG     : 3;
            __IOM uint32_t RXTCFG     : 1;
            __IOM uint32_t RXSBRERR   : 1;
            __IOM uint32_t GEBRERR    : 1;
            __IOM uint32_t GELBPERR   : 1;
            __IOM uint32_t AEBGIB     : 1;
            __IOM uint32_t SFTOB      : 1;
            __IM  uint32_t RESERVED1  : 7;
            __IOM uint32_t OACFG      : 15;
            __IOM uint32_t LMODSEL    : 1;
        } CFG_B;
    } ;

    /* Tx data register */
    union
    {
        __OM  uint32_t TXDATA;

        struct
        {
            __OM  uint32_t TXDATA     : 8;
            __IM  uint32_t RESERVED1  : 24;
        } TXDATA_B;
    } ;

    /* Rx data register */
    union
    {
        __IM  uint32_t RXDATA;

        struct
        {
            __IM  uint32_t RXDATA     : 8;
            __IM  uint32_t RESERVED1  : 24;
        } RXDATA_B;
    } ;

    /* Interrupt and Status Register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t RXBREFLG   : 1;
            __IOM uint32_t RXEFLG     : 1;
            __IOM uint32_t RXOVRFLG   : 1;
            __IOM uint32_t RXBRERRFLG : 1;
            __IOM uint32_t RXSBPEFLG  : 1;
            __IOM uint32_t RXLBPEFLG  : 1;
            __IOM uint32_t RXMACKFLG  : 1;
            __IOM uint32_t ARBLOSFLG  : 1;
            __IOM uint32_t TXBREFLG   : 1;
            __IOM uint32_t TXEFLG     : 1;
            __IOM uint32_t TXBUFLG    : 1;
            __IOM uint32_t TXERRFLG   : 1;
            __IOM uint32_t TXMACKFLG  : 1;
            __IM  uint32_t RESERVED1  : 19;
        } STS_B;
    } ;

    /* interrupt enable register */
    union
    {
        __IOM uint32_t INTEN;

        struct
        {
            __IOM uint32_t RXBREIEN   : 1;
            __IOM uint32_t RXEIEN     : 1;
            __IOM uint32_t RXOVRIEN   : 1;
            __IOM uint32_t RXBRERRIEN : 1;
            __IOM uint32_t RXSBPEIEN  : 1;
            __IOM uint32_t RXLBPEIEN  : 1;
            __IOM uint32_t RXMACKIEN  : 1;
            __IOM uint32_t ARBLOSIEN  : 1;
            __IOM uint32_t TXBREIEN   : 1;
            __IOM uint32_t TXIEN      : 1;
            __IOM uint32_t TXBUIEN    : 1;
            __IOM uint32_t TXERRIEN   : 1;
            __IOM uint32_t TXMACKIEN  : 1;
            __IM  uint32_t RESERVED1  : 19;
        } INTEN_B;
    } ;
} CEC_T;

/**
  * @brief Cyclic redundancy check calculation unit (CRC)
  */

typedef struct
{
    /* Data register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA       : 32;
        } DATA_B;
    } ;

    /* Independent data register */
    union
    {
        __IOM uint32_t INDATA;

        struct
        {
            __IOM uint32_t INDATA     : 8;
            __IM  uint32_t RESERVED1  : 24;
        } INDATA_B;
    } ;

    /* Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t RST        : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t POLSIZE    : 2;
            __IOM uint32_t REVI       : 2;
            __IOM uint32_t REVO       : 1;
            __IM  uint32_t RESERVED2  : 24;
        } CTRL_B;
    } ;
    __IM  uint32_t  RESERVED;

    /* Initial CRC value */
    union
    {
        __IOM uint32_t INITVAL;

        struct
        {
            __IOM uint32_t VALUE      : 32;
        } INITVAL_B;
    } ;

    /* CRC polynomia register*/
    union
    {
        __IOM uint32_t POL;

        struct
        {
            __IOM uint32_t PPOL       : 32;
        } POL_B;
    } ;
} CRC_T;

/**
  * @brief CRS registers (CRS)
  */

typedef struct
{
    /* Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t SNINTEN    : 1;
            __IOM uint32_t SWINTEN    : 1;
            __IOM uint32_t EINTEN     : 1;
            __IOM uint32_t ESINTEN    : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t CNTEN      : 1;
            __IOM uint32_t AUTOTRMEN  : 1;
            __IOM uint32_t SWSGNR     : 1;
            __IOM uint32_t HSI48TRM   : 6;
            __IM  uint32_t RESERVED2  : 18;
        } CTRL_B;
    } ;

    union
    {
        __IOM uint32_t CFG;

        struct
        {
            __IOM uint32_t RLDVAL     : 16;
            __IOM uint32_t FELMT      : 8;
            __IOM uint32_t SYNCPSC    : 3;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t SYNCSRCSEL : 2;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t SYNCPOLSEL : 1;
        } CFG_B;
    } ;

    union
    {
        __IM  uint32_t INTSTS;

        struct
        {
            __IM  uint32_t SNFLG      : 1;
            __IM  uint32_t SWFLG      : 1;
            __IM  uint32_t EFLG       : 1;
            __IM  uint32_t ESFLG      : 1;
            __IM  uint32_t RESERVED1  : 4;
            __IM  uint32_t ERRORFLG   : 1;
            __IM  uint32_t SYNCMISS   : 1;
            __IM  uint32_t TRMFLG     : 1;
            __IM  uint32_t RESERVED2  : 4;
            __IM  uint32_t CNTDRCT    : 1;
            __IM  uint32_t FECPT      : 16;
        } INTSTS_B;
    } ;

    union
    {
        __IOM uint32_t INTCLR;

        struct
        {
            __IOM uint32_t SNCLR      : 1;
            __IOM uint32_t SWCLR      : 1;
            __IOM uint32_t ECLR       : 1;
            __IOM uint32_t ESCLR      : 1;
            __IM  uint32_t RESERVED1  : 28;
        } INTCLR_B;
    } ;
} CRS_T;

/**
  * @brief Comparator (COMP)
  */

typedef struct
{
    /* control and status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IOM uint32_t EN1        : 1;
            __IOM uint32_t SW1        : 1;
            __IOM uint32_t MOD1       : 2;
            __IOM uint32_t INVINSEL1  : 3;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t OUTSEL1    : 3;
            __IOM uint32_t OPINV1     : 1;
            __IOM uint32_t HYSCFG1    : 2;
            __IM  uint32_t OUTSTS1    : 1;
            __IOM uint32_t LOCK1      : 1;
            __IOM uint32_t EN2        : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t MOD2       : 2;
            __IOM uint32_t INVINSEL2  : 3;
            __IOM uint32_t WMODEN     : 1;
            __IOM uint32_t OUTSEL2    : 3;
            __IOM uint32_t OPINV2     : 1;
            __IOM uint32_t HYSCFG2    : 2;
            __IM  uint32_t OUTSTS2    : 1;
            __IOM uint32_t LOCK2      : 1;
        } CSTS_B;
    } ;
} COMP_T;

/**
  * @brief Digital-to-Analog converter (DAC)
  */

typedef struct
{
    /* Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t ENCH1      : 1;
            __IOM uint32_t BUFFDCH1   : 1;
            __IOM uint32_t TRGENCH1   : 1;
            __IOM uint32_t TRGSELCH1  : 3;
            __IOM uint32_t WAVENCH1   : 2;
            __IOM uint32_t MAMPSELCH1 : 4;
            __IOM uint32_t DMAENCH1   : 1;
            __IOM uint32_t DMAUDRIEN1 : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t ENCH2      : 1;
            __IOM uint32_t BUFFDCH2   : 1;
            __IOM uint32_t TRGENCH2   : 1;
            __IOM uint32_t TRGSELCH2  : 3;
            __IOM uint32_t WAVENCH2   : 2;
            __IOM uint32_t MAMPSELCH2 : 4;
            __IOM uint32_t DMAENCH2   : 1;
            __IOM uint32_t DMAUDRIEN2 : 1;
            __IM  uint32_t RESERVED2  : 2;
        } CTRL_B;
    } ;

    /* Software trigger register */
    union
    {
        __OM  uint32_t SWTRG;

        struct
        {
            __OM  uint32_t SWTRG1     : 1;
            __OM  uint32_t SWTRG2     : 1;
            __IM  uint32_t RESERVED1  : 30;
        } SWTRG_B;
    } ;

    /* Channel1 12-bit right-aligned data holding register */
    union
    {
        __IOM uint32_t DH12R1;

        struct
        {
            __IOM uint32_t DATA       : 12;
            __IM  uint32_t RESERVED1  : 20;
        } DH12R1_B;
    } ;

    /* Channel1 12-bit left-aligned data holding register */
    union
    {
        __IOM uint32_t DH12L1;

        struct
        {
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t DATA       : 12;
            __IM  uint32_t RESERVED2  : 16;
        } DH12L1_B;
    } ;

    /* Channel1 8-bit right-aligned data holding register */
    union
    {
        __IOM uint32_t DH8R1;

        struct
        {
            __IOM uint32_t DATA       : 8;
            __IM  uint32_t RESERVED2  : 24;
        } DH8R1_B;
    } ;

    /* Channel2 12-bit right-aligned data holding register */
    union
    {
        __IOM uint32_t DH12R2;

        struct
        {
            __IOM uint32_t DATA       : 12;
            __IM  uint32_t RESERVED1  : 20;
        } DH12R2_B;
    } ;

    /* Channel2 12-bit left-aligned data holding register */
    union
    {
        __IOM uint32_t DH12L2;

        struct
        {
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t DATA       : 12;
            __IM  uint32_t RESERVED2  : 16;
        } DH12L2_B;
    } ;

    /* Channel2 8-bit right-aligned data holding register */
    union
    {
        __IOM uint32_t DH8R2;

        struct
        {
            __IOM uint32_t DATA       : 8;
            __IM  uint32_t RESERVED1  : 24;
        } DH8R2_B;
    } ;

    /* Dual DAC 12-bit right-aligned data holding register */
    union
    {
        __IOM uint32_t DH12RDUAL;

        struct
        {
            __IOM uint32_t DATACH1    : 12;
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t DATACH2    : 12;
            __IM  uint32_t RESERVED2  : 4;
        } DH12RDUAL_B;
    } ;

    /* Dual DAC 12-bit left-aligned data holding register */
    union
    {
        __IOM uint32_t DH12LDUAL;

        struct
        {
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t DATACH1    : 12;
            __IM  uint32_t RESERVED2  : 4;
            __IOM uint32_t DATACH2    : 12;
        } DH12LDUAL_B;
    } ;

    /* Dual DAC 8-bit right-aligned data holding register */
    union
    {
        __IOM uint32_t DH8RDUAL;

        struct
        {
            __IOM uint32_t DATACH1    : 8;
            __IOM uint32_t DATACH2    : 8;
            __IM  uint32_t RESERVED1  : 16;
        } DH8RDUAL_B;
    } ;

    /* DAC channel1 data output register  */
    union
    {
        __IM  uint32_t DATAOCH1;

        struct
        {
            __IM  uint32_t DATA       : 12;
            __IM  uint32_t RESERVED1  : 20;
        } DATAOCH1_B;
    } ;

    /* DAC channel2 data output register  */
    union
    {
        __IM  uint32_t DATAOCH2;

        struct
        {
            __IM  uint32_t DATA       : 12;
            __IM  uint32_t RESERVED1  : 20;
        } DATAOCH2_B;
    } ;

    /* Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t RESERVED1  : 13;
            __IOM uint32_t DMAUDRFLG1 : 1;
            __IM  uint32_t RESERVED2  : 15;
            __IOM uint32_t DMAUDRFLG2 : 1;
            __IM  uint32_t RESERVED3  : 2;
        } STS_B;
    } ;
} DAC_T;

/**
  * @brief Debug support (DBG)
  */

typedef struct
{

    /* MCU Device ID Code Register */
    union
    {
        __IM  uint32_t IDCODE;

        struct
        {
            __IM  uint32_t EQR        : 12;
            __IM  uint32_t RESERVED1  : 4;
            __IM  uint32_t WVR        : 16;
        } IDCODE_B;
    } ;

    /* Debug MCU Configuration Register */
    union
    {
        __IOM uint32_t CFG;

        struct
        {
            __IM  uint32_t RESERVED1        : 1;
            __IOM uint32_t STOP_CLK_STS     : 1;
            __IOM uint32_t STANDBY_CLK_STS  : 1;
            __IM  uint32_t RESERVED2        : 29;
        } CFG_B;
    } ;

    /* APB Low Freeze Register */
    union
    {
        __IOM uint32_t APB1F;

        struct
        {
            __IOM uint32_t TMR2_STS   : 1;
            __IOM uint32_t TMR3_STS   : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t TMR6_STS   : 1;
            __IOM uint32_t TMR7_STS   : 1;
            __IM  uint32_t RESERVED2  : 2;
            __IOM uint32_t TMR14_STS  : 1;
            __IM  uint32_t RESERVED3  : 1;
            __IOM uint32_t RTC_STS    : 1;
            __IOM uint32_t WWDT_STS   : 1;
            __IOM uint32_t IWDT_STS   : 1;
            __IM  uint32_t RESERVED4  : 8;
            __IOM uint32_t I2C1_SMBUS_TIMEOUT_STS : 1;
            __IM  uint32_t RESERVED5  : 3;
            __IOM uint32_t CAN_STS    : 1;
            __IM  uint32_t RESERVED6  : 6;
        } APB1F_B;
    } ;

    /* APB High Freeze Register */
    union
    {
        __IOM uint32_t APB2F;

        struct
        {
            __IM  uint32_t RESERVED1  : 11;
            __IOM uint32_t TMR1_STS   : 1;
            __IM  uint32_t RESERVED2  : 4;
            __IOM uint32_t TMR15_STS  : 1;
            __IOM uint32_t TMR16_STS  : 1;
            __IOM uint32_t TMR17_STS  : 1;
            __IM  uint32_t RESERVED3  : 13;
        } APB2F_B;
    } ;
} DBG_T;

/**
  * @brief DMA controller (DMA)
  */

typedef struct
{

    /* DMA interrupt status register */
    union
    {
        __IM  uint32_t INTSTS;

        struct
        {
            __IM  uint32_t GINTFLG1   : 1;
            __IM  uint32_t TCFLG1     : 1;
            __IM  uint32_t HTFLG1     : 1;
            __IM  uint32_t TERRFLG1   : 1;
            __IM  uint32_t GINTFLG2   : 1;
            __IM  uint32_t TCFLG2     : 1;
            __IM  uint32_t HTFLG2     : 1;
            __IM  uint32_t TERRFLG2   : 1;
            __IM  uint32_t GINTFLG3   : 1;
            __IM  uint32_t TCFLG3     : 1;
            __IM  uint32_t HTFLG3     : 1;
            __IM  uint32_t TERRFLG3   : 1;
            __IM  uint32_t GINTFLG4   : 1;
            __IM  uint32_t TCFLG4     : 1;
            __IM  uint32_t HTFLG4     : 1;
            __IM  uint32_t TERRFLG4   : 1;
            __IM  uint32_t GINTFLG5   : 1;
            __IM  uint32_t TCFLG5     : 1;
            __IM  uint32_t HTFLG5     : 1;
            __IM  uint32_t TERRFLG5   : 1;
            __IM  uint32_t GINTFLG6   : 1;
            __IM  uint32_t TCFLG6     : 1;
            __IM  uint32_t HTFLG6     : 1;
            __IM  uint32_t TERRFLG6   : 1;
            __IM  uint32_t GINTFLG7   : 1;
            __IM  uint32_t TCFLG7     : 1;
            __IM  uint32_t HTFLG7     : 1;
            __IM  uint32_t TERRFLG7   : 1;
            __IM  uint32_t RESERVED1  : 4;
        } ISTS_B;
    } ;

    /* DMA interrupt flag clear register */
    union
    {
        __OM  uint32_t INTFCLR;

        struct
        {
            __OM  uint32_t GINTCLR1   : 1;
            __OM  uint32_t TCCLR1     : 1;
            __OM  uint32_t HTCLR1     : 1;
            __OM  uint32_t TERRCLR1   : 1;
            __OM  uint32_t GINTCLR2   : 1;
            __OM  uint32_t TCCLR2     : 1;
            __OM  uint32_t HTCLR2     : 1;
            __OM  uint32_t TERRCLR2   : 1;
            __OM  uint32_t GINTCLR3   : 1;
            __OM  uint32_t TCCLR3     : 1;
            __OM  uint32_t HTCLR3     : 1;
            __OM  uint32_t TERRCLR3   : 1;
            __OM  uint32_t GINTCLR4   : 1;
            __OM  uint32_t TCCLR4     : 1;
            __OM  uint32_t HTCLR4     : 1;
            __OM  uint32_t TERRCLR4   : 1;
            __OM  uint32_t GINTCLR5   : 1;
            __OM  uint32_t TCCLR5     : 1;
            __OM  uint32_t HTCLR5     : 1;
            __OM  uint32_t TERRCLR5   : 1;
            __OM  uint32_t GINTCLR6   : 1;
            __OM  uint32_t TCCLR6     : 1;
            __OM  uint32_t HTCLR6     : 1;
            __OM  uint32_t TERRCLR6   : 1;
            __OM  uint32_t GINTCLR7   : 1;
            __OM  uint32_t TCCLR7     : 1;
            __OM  uint32_t HTCLR7     : 1;
            __OM  uint32_t TERRCLR7   : 1;
            __IM  uint32_t RESERVED1  : 4;
        } INTFCLR_B;
    } ;

    /* DMA channel configuration register */
    union
    {
        __IOM uint32_t CHCFG1;

        struct
        {
            __IOM uint32_t CHEN       : 1;
            __IOM uint32_t TCINTEN    : 1;
            __IOM uint32_t HTINTEN    : 1;
            __IOM uint32_t TERRINTEN  : 1;
            __IOM uint32_t DIRCFG     : 1;
            __IOM uint32_t CIRMODE    : 1;
            __IOM uint32_t PERIMODE   : 1;
            __IOM uint32_t MIMODE     : 1;
            __IOM uint32_t PERSIZE    : 2;
            __IOM uint32_t MSIZE      : 2;
            __IOM uint32_t CHPL       : 2;
            __IOM uint32_t M2MMODE    : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CHCFG1_B;
    } ;

    /* DMA channel 1 number of data register */
    union
    {
        __IOM uint32_t CHNDATA1;

        struct
        {
            __IOM uint32_t NDATAT     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CHNDATA1_B;
    } ;

    /* DMA channel 1 peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR1;

        struct
        {
            __IOM uint32_t PERADDR    : 32;
        } CHPADDR1_B;
    } ;

    /* DMA channel 1 memory address register */
    union
    {
        __IOM uint32_t CHMADDR1;

        struct
        {
            __IOM uint32_t MEMADD     : 32;
        } CHMADDR1_B;
    } ;
    __IM  uint32_t  RESERVED1;

    /* DMA channel configuration register */
    union
    {
        __IOM uint32_t CHCFG2;

        struct
        {
            __IOM uint32_t CHEN       : 1;
            __IOM uint32_t TCINTEN    : 1;
            __IOM uint32_t HTINTEN    : 1;
            __IOM uint32_t TERRINTEN  : 1;
            __IOM uint32_t DIRCFG     : 1;
            __IOM uint32_t CIRMODE    : 1;
            __IOM uint32_t PERIMODE   : 1;
            __IOM uint32_t MIMODE     : 1;
            __IOM uint32_t PERSIZE    : 2;
            __IOM uint32_t MSIZE      : 2;
            __IOM uint32_t CHPL       : 2;
            __IOM uint32_t M2MMODE    : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CHCFG2_B;
    } ;

    /* DMA channel 2 number of data register */
    union
    {
        __IOM uint32_t CHNDATA2;

        struct
        {
            __IOM uint32_t NDATAT     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CHNDATA2_B;
    } ;

    /* DMA channel 2 peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR2;

        struct
        {
            __IOM uint32_t PERADDR    : 32;
        } CHPADDR2_B;
    } ;

    /* DMA channel 2 memory address register */
    union
    {
        __IOM uint32_t CHMADDR2;

        struct
        {
            __IOM uint32_t MEMADD     : 32;
        } CHMADDR2_B;
    } ;
    __IM  uint32_t  RESERVED2;

    /* DMA channel configuration register */
    union
    {
        __IOM uint32_t CHCFG3;

        struct
        {
            __IOM uint32_t CHEN       : 1;
            __IOM uint32_t TCINTEN    : 1;
            __IOM uint32_t HTINTEN    : 1;
            __IOM uint32_t TERRINTEN  : 1;
            __IOM uint32_t DIRCFG     : 1;
            __IOM uint32_t CIRMODE    : 1;
            __IOM uint32_t PERIMODE   : 1;
            __IOM uint32_t MIMODE     : 1;
            __IOM uint32_t PERSIZE    : 2;
            __IOM uint32_t MSIZE      : 2;
            __IOM uint32_t CHPL       : 2;
            __IOM uint32_t M2MMODE    : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CHCFG3_B;
    } ;

    /* DMA channel 3 number of data register */
    union
    {
        __IOM uint32_t CHNDATA3;

        struct
        {
            __IOM uint32_t NDATAT     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CHNDATA3_B;
    } ;

    /* DMA channel 3 peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR3;

        struct
        {
            __IOM uint32_t PERADDR    : 32;
        } CHPADDR3_B;
    } ;

    /* DMA channel 3 memory address register */
    union
    {
        __IOM uint32_t CHMADDR3;

        struct
        {
            __IOM uint32_t MEMADD     : 32;
        } CHMADDR3_B;
    } ;
    __IM  uint32_t  RESERVED3;

    /* DMA channel configuration register */
    union
    {
        __IOM uint32_t CHCFG4;

        struct
        {
            __IOM uint32_t CHEN       : 1;
            __IOM uint32_t TCINTEN    : 1;
            __IOM uint32_t HTINTEN    : 1;
            __IOM uint32_t TERRINTEN  : 1;
            __IOM uint32_t DIRCFG     : 1;
            __IOM uint32_t CIRMODE    : 1;
            __IOM uint32_t PERIMODE   : 1;
            __IOM uint32_t MIMODE     : 1;
            __IOM uint32_t PERSIZE    : 2;
            __IOM uint32_t MSIZE      : 2;
            __IOM uint32_t CHPL       : 2;
            __IOM uint32_t M2MMODE    : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CHCFG4_B;
    } ;

    /* DMA channel 4 number of data register */
    union
    {
        __IOM uint32_t CHNDATA4;

        struct
        {
            __IOM uint32_t NDATAT     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CHNDATA4_B;
    } ;

    /* DMA channel 4 peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR4;

        struct
        {
            __IOM uint32_t PERADDR    : 32;
        } CHPADDR4_B;
    } ;

    /* DMA channel 4 memory address register */
    union
    {
        __IOM uint32_t CHMADDR4;

        struct
        {
            __IOM uint32_t MEMADD     : 32;
        } CHMADDR4_B;
    } ;
    __IM  uint32_t  RESERVED4;

    /* DMA channel configuration register */
    union
    {
        __IOM uint32_t CHCFG5;

        struct
        {
            __IOM uint32_t CHEN       : 1;
            __IOM uint32_t TCINTEN    : 1;
            __IOM uint32_t HTINTEN    : 1;
            __IOM uint32_t TERRINTEN  : 1;
            __IOM uint32_t DIRCFG     : 1;
            __IOM uint32_t CIRMODE    : 1;
            __IOM uint32_t PERIMODE   : 1;
            __IOM uint32_t MIMODE     : 1;
            __IOM uint32_t PERSIZE    : 2;
            __IOM uint32_t MSIZE      : 2;
            __IOM uint32_t CHPL       : 2;
            __IOM uint32_t M2MMODE    : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CHCFG5_B;
    } ;

    /* DMA channel 5 number of data register */
    union
    {
        __IOM uint32_t CHNDATA5;

        struct
        {
            __IOM uint32_t NDATAT     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CHNDATA5_B;
    } ;

    /* DMA channel 5 peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR5;

        struct
        {
            __IOM uint32_t PERADDR    : 32;
        } CHPADDR5_B;
    } ;

    /* DMA channel 5 memory address register */
    union
    {
        __IOM uint32_t CHMADDR5;

        struct
        {
            __IOM uint32_t MEMADD     : 32;
        } CHMADDR5_B;
    } ;
    __IM  uint32_t  RESERVED5;

    /* DMA channel configuration register */
    union
    {
        __IOM uint32_t CHCFG6;

        struct
        {
            __IOM uint32_t CHEN       : 1;
            __IOM uint32_t TCINTEN    : 1;
            __IOM uint32_t HTINTEN    : 1;
            __IOM uint32_t TERRINTEN  : 1;
            __IOM uint32_t DIRCFG     : 1;
            __IOM uint32_t CIRMODE    : 1;
            __IOM uint32_t PERIMODE   : 1;
            __IOM uint32_t MIMODE     : 1;
            __IOM uint32_t PERSIZE    : 2;
            __IOM uint32_t MSIZE      : 2;
            __IOM uint32_t CHPL       : 2;
            __IOM uint32_t M2MMODE    : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CHCFG6_B;
    } ;

    /* DMA channel 6 number of data register */
    union
    {
        __IOM uint32_t CHNDATA6;

        struct
        {
            __IOM uint32_t NDATAT     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CHNDATA6_B;
    } ;

    /* DMA channel 6 peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR6;

        struct
        {
            __IOM uint32_t PERADDR    : 32;
        } CHPADDR6_B;
    } ;

    /* DMA channel 6 memory address register */
    union
    {
        __IOM uint32_t CHMADDR6;

        struct
        {
            __IOM uint32_t MEMADD     : 32;
        } CHMADDR6_B;
    } ;
    __IM  uint32_t  RESERVED6;

    /* DMA channel configuration register */
    union
    {
        __IOM uint32_t CHCFG7;

        struct
        {
            __IOM uint32_t CHEN       : 1;
            __IOM uint32_t TCINTEN    : 1;
            __IOM uint32_t HTINTEN    : 1;
            __IOM uint32_t TERRINTEN  : 1;
            __IOM uint32_t DIRCFG     : 1;
            __IOM uint32_t CIRMODE    : 1;
            __IOM uint32_t PERIMODE   : 1;
            __IOM uint32_t MIMODE     : 1;
            __IOM uint32_t PERSIZE    : 2;
            __IOM uint32_t MSIZE      : 2;
            __IOM uint32_t CHPL       : 2;
            __IOM uint32_t M2MMODE    : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CHCFG7_B;
    } ;

    /* DMA channel 7 number of data register */
    union
    {
        __IOM uint32_t CHNDATA7;

        struct
        {
            __IOM uint32_t NDATAT     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CHNDATA7_B;
    } ;

    /* DMA channel 7 peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR7;

        struct
        {
            __IOM uint32_t PERADDR    : 32;
        } CHPADDR7_B;
    } ;

    /* DMA channel 7 memory address register */
    union
    {
        __IOM uint32_t CHMADDR7;

        struct
        {
            __IOM uint32_t MEMADD     : 32;
        } CHMADDR7_B;
    } ;
    __IM  uint32_t  RESERVED7[6];

    /* DMA channel remap selection register */
    union
    {
        __IOM uint32_t CHSEL;

        struct
        {
            __IOM uint32_t CHSEL1     : 4;
            __IOM uint32_t CHSEL2     : 4;
            __IOM uint32_t CHSEL3     : 4;
            __IOM uint32_t CHSEL4     : 4;
            __IOM uint32_t CHSEL5     : 4;
            __IOM uint32_t CHSEL6     : 4;
            __IOM uint32_t CHSEL7     : 4;
            __IM  uint32_t RESERVED1  : 4;
        } CHSEL_B;
    } ;
} DMA_T;

/**
  * @brief DMA CHANNEL register
  */

typedef struct
{

    /* DMA channel configuration register */
    union
    {
        __IOM uint32_t CHCFG;

        struct
        {
            __IOM uint32_t CHEN       : 1;
            __IOM uint32_t TCINTEN    : 1;
            __IOM uint32_t HTINTEN    : 1;
            __IOM uint32_t TERRINTEN  : 1;
            __IOM uint32_t DIRCFG     : 1;
            __IOM uint32_t CIRMODE    : 1;
            __IOM uint32_t PERIMODE   : 1;
            __IOM uint32_t MIMODE     : 1;
            __IOM uint32_t PERSIZE    : 2;
            __IOM uint32_t MSIZE      : 2;
            __IOM uint32_t CHPL       : 2;
            __IOM uint32_t M2MMODE    : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CHCFG_B;
    } ;

    /* DMA channelx  number of data register */
    union
    {
        __IOM uint32_t CHNDATA;

        struct
        {
            __IOM uint32_t NDATAT     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CHNDATA_B;
    } ;

    /* DMA channelx  peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR;

        struct
        {
            __IOM uint32_t PERADDR    : 32;
        } CHPADDR_B;
    } ;

    /* DMA channelx  memory address register */
    union
    {
        __IOM uint32_t CHMADDR;

        struct
        {
            __IOM uint32_t MEMADD     : 32;
        } CHMADDR_B;
    } ;
} DMA_CHANNEL_T;

/**
  * @brief External interrupt/event  controller (EINT)
  */

typedef struct
{
    /* Interrupt mask register */
    union
    {
        __IOM uint32_t IMASK;

        struct
        {
            __IOM uint32_t IMASK0     : 1;
            __IOM uint32_t IMASK1     : 1;
            __IOM uint32_t IMASK2     : 1;
            __IOM uint32_t IMASK3     : 1;
            __IOM uint32_t IMASK4     : 1;
            __IOM uint32_t IMASK5     : 1;
            __IOM uint32_t IMASK6     : 1;
            __IOM uint32_t IMASK7     : 1;
            __IOM uint32_t IMASK8     : 1;
            __IOM uint32_t IMASK9     : 1;
            __IOM uint32_t IMASK10    : 1;
            __IOM uint32_t IMASK11    : 1;
            __IOM uint32_t IMASK12    : 1;
            __IOM uint32_t IMASK13    : 1;
            __IOM uint32_t IMASK14    : 1;
            __IOM uint32_t IMASK15    : 1;
            __IOM uint32_t IMASK16    : 1;
            __IOM uint32_t IMASK17    : 1;
            __IOM uint32_t IMASK18    : 1;
            __IOM uint32_t IMASK19    : 1;
            __IOM uint32_t IMASK20    : 1;
            __IOM uint32_t IMASK21    : 1;
            __IOM uint32_t IMASK22    : 1;
            __IOM uint32_t IMASK23    : 1;
            __IOM uint32_t IMASK24    : 1;
            __IOM uint32_t IMASK25    : 1;
            __IOM uint32_t IMASK26    : 1;
            __IOM uint32_t IMASK27    : 1;
            __IOM uint32_t IMASK28    : 1;
            __IOM uint32_t IMASK29    : 1;
            __IOM uint32_t IMASK30    : 1;
            __IOM uint32_t IMASK31    : 1;
        } IMASK_B;
    } ;

    /* Event mask register (EINT_EVTMASK) */
    union
    {

        __IOM uint32_t EMASK;

        struct
        {
            __IOM uint32_t EMASK0     : 1;
            __IOM uint32_t EMASK1     : 1;
            __IOM uint32_t EMASK2     : 1;
            __IOM uint32_t EMASK3     : 1;
            __IOM uint32_t EMASK4     : 1;
            __IOM uint32_t EMASK5     : 1;
            __IOM uint32_t EMASK6     : 1;
            __IOM uint32_t EMASK7     : 1;
            __IOM uint32_t EMASK8     : 1;
            __IOM uint32_t EMASK9     : 1;
            __IOM uint32_t EMASK10    : 1;
            __IOM uint32_t EMASK11    : 1;
            __IOM uint32_t EMASK12    : 1;
            __IOM uint32_t EMASK13    : 1;
            __IOM uint32_t EMASK14    : 1;
            __IOM uint32_t EMASK15    : 1;
            __IOM uint32_t EMASK16    : 1;
            __IOM uint32_t EMASK17    : 1;
            __IOM uint32_t EMASK18    : 1;
            __IOM uint32_t EMASK19    : 1;
            __IOM uint32_t EMASK20    : 1;
            __IOM uint32_t EMASK21    : 1;
            __IOM uint32_t EMASK22    : 1;
            __IOM uint32_t EMASK23    : 1;
            __IOM uint32_t EMASK24    : 1;
            __IOM uint32_t EMASK25    : 1;
            __IOM uint32_t EMASK26    : 1;
            __IOM uint32_t EMASK27    : 1;
            __IOM uint32_t EMASK28    : 1;
            __IOM uint32_t EMASK29    : 1;
            __IOM uint32_t EMASK30    : 1;
            __IOM uint32_t EMASK31    : 1;
        } EMASK_B;
    } ;

    union
    {
        __IOM uint32_t RTEN;

        struct
        {
            __IOM uint32_t RTEN0      : 1;
            __IOM uint32_t RTEN1      : 1;
            __IOM uint32_t RTEN2      : 1;
            __IOM uint32_t RTEN3      : 1;
            __IOM uint32_t RTEN4      : 1;
            __IOM uint32_t RTEN5      : 1;
            __IOM uint32_t RTEN6      : 1;
            __IOM uint32_t RTEN7      : 1;
            __IOM uint32_t RTEN8      : 1;
            __IOM uint32_t RTEN9      : 1;
            __IOM uint32_t RTEN10     : 1;
            __IOM uint32_t RTEN11     : 1;
            __IOM uint32_t RTEN12     : 1;
            __IOM uint32_t RTEN13     : 1;
            __IOM uint32_t RTEN14     : 1;
            __IOM uint32_t RTEN15     : 1;
            __IOM uint32_t RTEN16     : 1;
            __IOM uint32_t RTEN17     : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t RTEN19     : 1;
            __IOM uint32_t RTEN20     : 1;
            __IOM uint32_t RTEN21     : 1;
            __IOM uint32_t RTEN22     : 1;
            __IM  uint32_t RESERVED2  : 8;
            __IOM uint32_t RTEN31     : 1;
        } RTEN_B;
    } ;

    /* Falling Trigger selection register */
    union
    {
        __IOM uint32_t FTEN;

        struct
        {
            __IOM uint32_t FTEN0      : 1;
            __IOM uint32_t FTEN1      : 1;
            __IOM uint32_t FTEN2      : 1;
            __IOM uint32_t FTEN3      : 1;
            __IOM uint32_t FTEN4      : 1;
            __IOM uint32_t FTEN5      : 1;
            __IOM uint32_t FTEN6      : 1;
            __IOM uint32_t FTEN7      : 1;
            __IOM uint32_t FTEN8      : 1;
            __IOM uint32_t FTEN9      : 1;
            __IOM uint32_t FTEN10     : 1;
            __IOM uint32_t FTEN11     : 1;
            __IOM uint32_t FTEN12     : 1;
            __IOM uint32_t FTEN13     : 1;
            __IOM uint32_t FTEN14     : 1;
            __IOM uint32_t FTEN15     : 1;
            __IOM uint32_t FTEN16     : 1;
            __IOM uint32_t FTEN17     : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t FTEN19     : 1;
            __IOM uint32_t FTEN20     : 1;
            __IOM uint32_t FTEN21     : 1;
            __IOM uint32_t FTEN22     : 1;
            __IM  uint32_t RESERVED2  : 8;
            __IOM uint32_t FTEN31     : 1;
        } FTEN_B;
    } ;

    /* Software interrupt event register */
    union
    {
        __IOM uint32_t SWINTE;

        struct
        {
            __IOM uint32_t SWINTE0    : 1;
            __IOM uint32_t SWINTE1    : 1;
            __IOM uint32_t SWINTE2    : 1;
            __IOM uint32_t SWINTE3    : 1;
            __IOM uint32_t SWINTE4    : 1;
            __IOM uint32_t SWINTE5    : 1;
            __IOM uint32_t SWINTE6    : 1;
            __IOM uint32_t SWINTE7    : 1;
            __IOM uint32_t SWINTE8    : 1;
            __IOM uint32_t SWINTE9    : 1;
            __IOM uint32_t SWINTE10   : 1;
            __IOM uint32_t SWINTE11   : 1;
            __IOM uint32_t SWINTE12   : 1;
            __IOM uint32_t SWINTE13   : 1;
            __IOM uint32_t SWINTE14   : 1;
            __IOM uint32_t SWINTE15   : 1;
            __IOM uint32_t SWINTE16   : 1;
            __IOM uint32_t SWINTE17   : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t SWINTE19   : 1;
            __IOM uint32_t SWINTE20   : 1;
            __IOM uint32_t SWINTE21   : 1;
            __IOM uint32_t SWINTE22   : 1;
            __IM  uint32_t RESERVED2  : 8;
            __IOM uint32_t SWINTE31   : 1;
        } SWINTE_B;
    } ;

    /* Pending register */
    union
    {
        __IOM uint32_t IPEND;

        struct
        {
            __IOM uint32_t IPEND0     : 1;
            __IOM uint32_t IPEND1     : 1;
            __IOM uint32_t IPEND2     : 1;
            __IOM uint32_t IPEND3     : 1;
            __IOM uint32_t IPEND4     : 1;
            __IOM uint32_t IPEND5     : 1;
            __IOM uint32_t IPEND6     : 1;
            __IOM uint32_t IPEND7     : 1;
            __IOM uint32_t IPEND8     : 1;
            __IOM uint32_t IPEND9     : 1;
            __IOM uint32_t IPEND10    : 1;
            __IOM uint32_t IPEND11    : 1;
            __IOM uint32_t IPEND12    : 1;
            __IOM uint32_t IPEND13    : 1;
            __IOM uint32_t IPEND14    : 1;
            __IOM uint32_t IPEND15    : 1;
            __IOM uint32_t IPEND16    : 1;
            __IOM uint32_t IPEND17    : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t IPEND19    : 1;
            __IOM uint32_t IPEND20    : 1;
            __IOM uint32_t IPEND21    : 1;
            __IOM uint32_t IPEND22    : 1;
            __IM  uint32_t RESERVED2  : 8;
            __IOM uint32_t IPEND31    : 1;
        } IPEND_B;
    } ;
} EINT_T;

/**
  * @brief FMC (FMC)
  */

typedef struct
{

    /* Flash access control register  */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t WS         : 3;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t PBEN       : 1;
            __IM  uint32_t PBSF       : 1;
            __IM  uint32_t RESERVED3  : 26;
        } CTRL1_B;
    } ;

    /* Flash key register  */
    union
    {
        __OM  uint32_t KEY;

        struct
        {
            __OM  uint32_t KEY        : 32;
        } KEY_B;
    } ;

    /* Flash option key register   */
    union
    {
        __OM  uint32_t OBKEY;

        struct
        {
            __OM  uint32_t OBKEY      : 32;
        } OBKEY_B;
    } ;

    /* Flash status register  */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t BUSYF      : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t PEF        : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t WPEF       : 1;
            __IOM uint32_t OCF        : 1;
            __IM  uint32_t RESERVED3  : 26;
        } STS_B;
    } ;

    /* Flash control register */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t PG         : 1;
            __IOM uint32_t PAGEERA    : 1;
            __IOM uint32_t MASSERA    : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t OBP        : 1;
            __IOM uint32_t OBE        : 1;
            __IOM uint32_t STA        : 1;
            __IOM uint32_t LOCK       : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t OBWEN      : 1;
            __IOM uint32_t ERRIE      : 1;
            __IM  uint32_t RESERVED3  : 1;
            __IOM uint32_t OCIE       : 1;
            __IOM uint32_t OBLOAD     : 1;
            __IM  uint32_t RESERVED4  : 18;
        } CTRL2_B;
    } ;

    /* Flash address register */
    union
    {
        __OM  uint32_t ADDR;

        struct
        {
            __OM  uint32_t ADDR       : 32;
        } ADDR_B;
    } ;
    __IM  uint32_t  RESERVED;

    /* Option byte register */
    union
    {
        __IM  uint32_t OBCS;

        struct
        {
            __IM  uint32_t OBE        : 1;
            __IM  uint32_t READPROT   : 2;
            __IM  uint32_t RESERVED1  : 5;
            __IM  uint32_t WDTSEL     : 1;
            __IM  uint32_t RSTSTOP    : 1;
            __IM  uint32_t RSTSTDB    : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IM  uint32_t nBOOT1     : 1;
            __IM  uint32_t VDDAMONI   : 1;
            __IM  uint32_t SRAMPARITY : 1;
            __IM  uint32_t nBOOT0     : 1;
            __IM  uint32_t DATA0      : 8;
            __IM  uint32_t DATA1      : 8;
        } OBCS_B;
    } ;

    /* Write protection register */
    union
    {
        __IM  uint32_t WRTPROT;

        struct
        {
            __IM  uint32_t WRTPROT    : 32;
        } WRTPROT_B;
    } ;
} FMC_T;

/*
  * @brief General-purpose I/Os (GPIO)
  */

typedef struct
{
    /* GPIO port mode register*/
    union
    {
        __IOM uint32_t MODE;

        struct
        {
            __IOM uint32_t MODE0      : 2;
            __IOM uint32_t MODE1      : 2;
            __IOM uint32_t MODE2      : 2;
            __IOM uint32_t MODE3      : 2;
            __IOM uint32_t MODE4      : 2;
            __IOM uint32_t MODE5      : 2;
            __IOM uint32_t MODE6      : 2;
            __IOM uint32_t MODE7      : 2;
            __IOM uint32_t MODE8      : 2;
            __IOM uint32_t MODE9      : 2;
            __IOM uint32_t MODE10     : 2;
            __IOM uint32_t MODE11     : 2;
            __IOM uint32_t MODE12     : 2;
            __IOM uint32_t MODE13     : 2;
            __IOM uint32_t MODE14     : 2;
            __IOM uint32_t MODE15     : 2;
        } MODE_B;
    } ;

    /* GPIO port output type register*/
    union
    {
        __IOM uint32_t OMODE;

        struct
        {
            __IOM uint32_t OMODE0     : 1;
            __IOM uint32_t OMODE1     : 1;
            __IOM uint32_t OMODE2     : 1;
            __IOM uint32_t OMODE3     : 1;
            __IOM uint32_t OMODE4     : 1;
            __IOM uint32_t OMODE5     : 1;
            __IOM uint32_t OMODE6     : 1;
            __IOM uint32_t OMODE7     : 1;
            __IOM uint32_t OMODE8     : 1;
            __IOM uint32_t OMODE9     : 1;
            __IOM uint32_t OMODE10    : 1;
            __IOM uint32_t OMODE11    : 1;
            __IOM uint32_t OMODE12    : 1;
            __IOM uint32_t OMODE13    : 1;
            __IOM uint32_t OMODE14    : 1;
            __IOM uint32_t OMODE15    : 1;
            __IOM uint32_t RESERVED1  : 16;
        } OMODE_B;
    } ;

    /* GPIO port output speed register*/
    union
    {
        __IOM uint32_t OSSEL;

        struct
        {
            __IOM uint32_t OSSEL0     : 2;
            __IOM uint32_t OSSEL1     : 2;
            __IOM uint32_t OSSEL2     : 2;
            __IOM uint32_t OSSEL3     : 2;
            __IOM uint32_t OSSEL4     : 2;
            __IOM uint32_t OSSEL5     : 2;
            __IOM uint32_t OSSEL6     : 2;
            __IOM uint32_t OSSEL7     : 2;
            __IOM uint32_t OSSEL8     : 2;
            __IOM uint32_t OSSEL9     : 2;
            __IOM uint32_t OSSEL10    : 2;
            __IOM uint32_t OSSEL11    : 2;
            __IOM uint32_t OSSEL12    : 2;
            __IOM uint32_t OSSEL13    : 2;
            __IOM uint32_t OSSEL14    : 2;
            __IOM uint32_t OSSEL15    : 2;
        } OSSEL_B;
    } ;

    /* GPIO port pull-up/pull-down register*/
    union
    {
        __IOM uint32_t PUPD;

        struct
        {
            __IOM uint32_t PUPD0      : 2;
            __IOM uint32_t PUPD1      : 2;
            __IOM uint32_t PUPD2      : 2;
            __IOM uint32_t PUPD3      : 2;
            __IOM uint32_t PUPD4      : 2;
            __IOM uint32_t PUPD5      : 2;
            __IOM uint32_t PUPD6      : 2;
            __IOM uint32_t PUPD7      : 2;
            __IOM uint32_t PUPD8      : 2;
            __IOM uint32_t PUPD9      : 2;
            __IOM uint32_t PUPD10     : 2;
            __IOM uint32_t PUPD11     : 2;
            __IOM uint32_t PUPD12     : 2;
            __IOM uint32_t PUPD13     : 2;
            __IOM uint32_t PUPD14     : 2;
            __IOM uint32_t PUPD15     : 2;
        } PUPD_B;
    } ;

    /* GPIO port input data register*/
    union
    {
        __IM  uint32_t IDATA;

        struct
        {
            __IM  uint32_t IDATA0       : 1;
            __IM  uint32_t IDATA1       : 1;
            __IM  uint32_t IDATA2       : 1;
            __IM  uint32_t IDATA3       : 1;
            __IM  uint32_t IDATA4       : 1;
            __IM  uint32_t IDATA5       : 1;
            __IM  uint32_t IDATA6       : 1;
            __IM  uint32_t IDATA7       : 1;
            __IM  uint32_t IDATA8       : 1;
            __IM  uint32_t IDATA9       : 1;
            __IM  uint32_t IDATA10      : 1;
            __IM  uint32_t IDATA11      : 1;
            __IM  uint32_t IDATA12      : 1;
            __IM  uint32_t IDATA13      : 1;
            __IM  uint32_t IDATA14      : 1;
            __IM  uint32_t IDATA15      : 1;
            __IM  uint32_t RESERVED1  : 16;
        } IDATA_B;
    } ;

    /* GPIO port output data register*/
    union
    {
        __IOM uint32_t ODATA;

        struct
        {
            __IOM uint32_t ODATA0      : 1;
            __IOM uint32_t ODATA1      : 1;
            __IOM uint32_t ODATA2      : 1;
            __IOM uint32_t ODATA3      : 1;
            __IOM uint32_t ODATA4      : 1;
            __IOM uint32_t ODATA5      : 1;
            __IOM uint32_t ODATA6      : 1;
            __IOM uint32_t ODATA7      : 1;
            __IOM uint32_t ODATA8      : 1;
            __IOM uint32_t ODATA9      : 1;
            __IOM uint32_t ODATA10     : 1;
            __IOM uint32_t ODATA11     : 1;
            __IOM uint32_t ODATA12     : 1;
            __IOM uint32_t ODATA13     : 1;
            __IOM uint32_t ODATA14     : 1;
            __IOM uint32_t ODATA15     : 1;
            __IOM uint32_t RESERVED1  : 16;
        } ODATA_B;
    } ;

    /* GPIO port bit set/clear register*/
    union
    {
        __OM  uint32_t BSC;

        struct
        {
            __OM  uint32_t BS0        : 1;
            __OM  uint32_t BS1        : 1;
            __OM  uint32_t BS2        : 1;
            __OM  uint32_t BS3        : 1;
            __OM  uint32_t BS4        : 1;
            __OM  uint32_t BS5        : 1;
            __OM  uint32_t BS6        : 1;
            __OM  uint32_t BS7        : 1;
            __OM  uint32_t BS8        : 1;
            __OM  uint32_t BS9        : 1;
            __OM  uint32_t BS10       : 1;
            __OM  uint32_t BS11       : 1;
            __OM  uint32_t BS12       : 1;
            __OM  uint32_t BS13       : 1;
            __OM  uint32_t BS14       : 1;
            __OM  uint32_t BS15       : 1;
            __OM  uint32_t BC0        : 1;
            __OM  uint32_t BC1        : 1;
            __OM  uint32_t BC2        : 1;
            __OM  uint32_t BC3        : 1;
            __OM  uint32_t BC4        : 1;
            __OM  uint32_t BC5        : 1;
            __OM  uint32_t BC6        : 1;
            __OM  uint32_t BC7        : 1;
            __OM  uint32_t BC8        : 1;
            __OM  uint32_t BC9        : 1;
            __OM  uint32_t BC10       : 1;
            __OM  uint32_t BC11       : 1;
            __OM  uint32_t BC12       : 1;
            __OM  uint32_t BC13       : 1;
            __OM  uint32_t BC14       : 1;
            __OM  uint32_t BC15       : 1;
        } BSC_B;
    } ;

    /* GPIO port configuration lock register*/
    union
    {
        __IOM uint32_t LOCK;

        struct
        {
            __IOM uint32_t LOCK0      : 1;
            __IOM uint32_t LOCK1      : 1;
            __IOM uint32_t LOCK2      : 1;
            __IOM uint32_t LOCK3      : 1;
            __IOM uint32_t LOCK4      : 1;
            __IOM uint32_t LOCK5      : 1;
            __IOM uint32_t LOCK6      : 1;
            __IOM uint32_t LOCK7      : 1;
            __IOM uint32_t LOCK8      : 1;
            __IOM uint32_t LOCK9      : 1;
            __IOM uint32_t LOCK10     : 1;
            __IOM uint32_t LOCK11     : 1;
            __IOM uint32_t LOCK12     : 1;
            __IOM uint32_t LOCK13     : 1;
            __IOM uint32_t LOCK14     : 1;
            __IOM uint32_t LOCK15     : 1;
            __IOM uint32_t LOCKKEY    : 1;
            __IOM uint32_t RESERVED1  : 15;
        } LOCK_B;
    } ;

    /* GPIO alternate function low register*/
    union
    {
        __IOM uint32_t ALFL;

        struct
        {
            __IOM uint32_t AF0        : 4;
            __IOM uint32_t AF1        : 4;
            __IOM uint32_t AF2        : 4;
            __IOM uint32_t AF3        : 4;
            __IOM uint32_t AF4        : 4;
            __IOM uint32_t AF5        : 4;
            __IOM uint32_t AF6        : 4;
            __IOM uint32_t AF7        : 4;
        } ALFL_B;
    } ;

    /* GPIO alternate function high register*/
    union
    {
        __IOM uint32_t ALFH;

        struct
        {
            __IOM uint32_t AF0        : 4;
            __IOM uint32_t AF1        : 4;
            __IOM uint32_t AF2        : 4;
            __IOM uint32_t AF3        : 4;
            __IOM uint32_t AF4        : 4;
            __IOM uint32_t AF5        : 4;
            __IOM uint32_t AF6        : 4;
            __IOM uint32_t AF7        : 4;
        } ALFH_B;
    } ;

    /* Port bit clear register*/
    union
    {
        __OM  uint32_t BR;

        struct
        {
            __OM  uint32_t BR0        : 1;
            __OM  uint32_t BR1        : 1;
            __OM  uint32_t BR2        : 1;
            __OM  uint32_t BR3        : 1;
            __OM  uint32_t BR4        : 1;
            __OM  uint32_t BR5        : 1;
            __OM  uint32_t BR6        : 1;
            __OM  uint32_t BR7        : 1;
            __OM  uint32_t BR8        : 1;
            __OM  uint32_t BR9        : 1;
            __OM  uint32_t BR10       : 1;
            __OM  uint32_t BR11       : 1;
            __OM  uint32_t BR12       : 1;
            __OM  uint32_t BR13       : 1;
            __OM  uint32_t BR14       : 1;
            __OM  uint32_t BR15       : 1;
            __OM  uint32_t RESERVED1  : 16;
        } BR_B;
    } ;
} GPIO_T;


/**
  * @brief Inter-integrated circuit (I2C)
  */

typedef struct
{
    /* Control register 1*/
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t I2CEN      : 1;
            __IOM uint32_t TXIEN      : 1;
            __IOM uint32_t RXIEN      : 1;
            __IOM uint32_t SADDRMIEN  : 1;
            __IOM uint32_t NACKRXIEN  : 1;
            __IOM uint32_t STOPIEN    : 1;
            __IOM uint32_t TXCIEN     : 1;
            __IOM uint32_t ERRIEN     : 1;
            __IOM uint32_t DNFCFG     : 4;
            __IOM uint32_t ANFD       : 1;
            __OM  uint32_t SWRST      : 1;
            __IOM uint32_t DMATXEN    : 1;
            __IOM uint32_t DMARXEN    : 1;
            __IOM uint32_t SBCEN      : 1;
            __IOM uint32_t CLKSTRETCHD : 1;
            __IOM uint32_t WUPEN      : 1;
            __IOM uint32_t RBEN       : 1;
            __IOM uint32_t HADDREN    : 1;
            __IOM uint32_t DEADDREN   : 1;
            __IOM uint32_t ALTEN      : 1;
            __IOM uint32_t PECEN      : 1;
            __IM  uint32_t RESERVED2  : 8;
        } CTRL1_B;
    } ;

    /* Control register 2*/
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t SADDR0     : 1;
            __IOM uint32_t SADDR1     : 7;
            __IOM uint32_t SADDR8     : 2;
            __IOM uint32_t TXDIR      : 1;
            __IOM uint32_t SADDRLEN   : 1;
            __IOM uint32_t ADDR10     : 1;
            __IOM uint32_t START      : 1;
            __IOM uint32_t STOP       : 1;
            __IOM uint32_t NACKEN     : 1;
            __IOM uint32_t NUMBYT     : 8;
            __IOM uint32_t RELOADEN   : 1;
            __IOM uint32_t ENDCFG     : 1;
            __IOM uint32_t PEC        : 1;
            __IOM uint32_t RESERVED1  : 5;
        } CTRL2_B;
    } ;

    /* Own address register 1*/
    union
    {
        __IOM uint32_t ADDR1;

        struct
        {
            __IOM uint32_t ADDR0      : 1;
            __IOM uint32_t ADDR1      : 7;
            __IOM uint32_t ADDR8      : 2;
            __IOM uint32_t ADDR1LEN   : 1;
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t ADDR1EN    : 1;
            __IM  uint32_t RESERVED2  : 16;
        } ADDR1_B;
    } ;

    /* Own address register 2*/
    union
    {
        __IOM uint32_t ADDR2;

        struct
        {
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t ADDR2      : 7;
            __IOM uint32_t ADDR2MSK   : 3;
            __IM  uint32_t RESERVED2  : 4;
            __IOM uint32_t ADDR2EN    : 1;
            __IM  uint32_t RESERVED3  : 16;
        } ADDR2_B;
    } ;

    /* Timing register*/
    union
    {
        __IOM uint32_t TIMING;

        struct
        {
            __IOM uint32_t SCLL       : 8;
            __IOM uint32_t SCLH       : 8;
            __IOM uint32_t DATAHT     : 4;
            __IOM uint32_t DATAT      : 4;
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t TIMINGPSC  : 4;
        } TIMING_B;
    } ;

    /* Status register 1*/
    union
    {
        __IOM uint32_t TIMEOUT;

        struct
        {
            __IOM uint32_t TIMEOUTA   : 12;
            __IOM uint32_t IDLECLKTO  : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t CLKTOEN    : 1;
            __IOM uint32_t TIMEOUTB   : 12;
            __IM  uint32_t RESERVED2  : 3;
            __IOM uint32_t EXCLKTOEN  : 1;
        } TIMEOUT_B;
    } ;

    /* Interrupt and Status register*/
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t TXBEFLG    : 1;
            __IOM uint32_t TXINTFLG   : 1;
            __IM  uint32_t RXBNEFLG   : 1;
            __IM  uint32_t ADDRMFLG   : 1;
            __IM  uint32_t NACKFLG    : 1;
            __IM  uint32_t STOPFLG    : 1;
            __IM  uint32_t TXCFLG     : 1;
            __IM  uint32_t TXCRFLG    : 1;
            __IM  uint32_t BERRFLG    : 1;
            __IM  uint32_t ALFLG      : 1;
            __IM  uint32_t OVRURFLG   : 1;
            __IM  uint32_t PECEFLG    : 1;
            __IM  uint32_t TTEFLG     : 1;
            __IM  uint32_t SMBALTFLG  : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IM  uint32_t BUSBSYFLG  : 1;
            __IM  uint32_t TXDIRFLG   : 1;
            __IM  uint32_t ADDRCMFLG  : 7;
            __IM  uint32_t RESERVED2  : 8;
        } STS_B;
    } ;

    /* Interrupt clear register*/
    union
    {
        __OM  uint32_t INTFCLR;

        struct
        {
            __IM  uint32_t RESERVED1  : 3;
            __OM  uint32_t ADDRMCLR   : 1;
            __OM  uint32_t NACKCLR    : 1;
            __OM  uint32_t STOPCLR    : 1;
            __IM  uint32_t RESERVED2  : 2;
            __OM  uint32_t BERRCLR    : 1;
            __OM  uint32_t ALCLR      : 1;
            __OM  uint32_t OVRURCLR   : 1;
            __OM  uint32_t PECECLR    : 1;
            __OM  uint32_t TTECLR     : 1;
            __OM  uint32_t SMBALTCLR  : 1;
            __IM  uint32_t RESERVED3  : 18;
        } INTFCLR_B;
    } ;

    /* PEC data register*/
    union
    {
        __IM  uint32_t PEC;

        struct
        {
            __IM  uint32_t PEC        : 8;
            __IM  uint32_t RESERVED1  : 24;
        } PEC_B;
    } ;

    /* Receive data register*/
    union
    {
        __IM  uint32_t RXDATA;

        struct
        {
            __IM  uint32_t RXDATA     : 8;
            __IM  uint32_t RESERVED1  : 24;
        } RXDATA_B;
    } ;

    /* Transmit data register*/
    union
    {
        __IOM uint32_t TXDATA;

        struct
        {
            __IOM uint32_t TXDATA     : 8;
            __IOM uint32_t RESERVED1  : 24;
        } TXDATA_B;
    } ;
} I2C_T;

/**
  * @brief Independent watchdog (IWDT)
  */

typedef struct
{

    /* Key register */
    union
    {
        __OM  uint32_t KEY;

        struct
        {
            __OM  uint32_t KEY        : 16;
            __IM  uint32_t RESERVED1  : 16;
        } KEY_B;
    } ;

    /* Prescaler register */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint32_t PSC        : 3;
            __IM  uint32_t RESERVED1  : 29;
        } PSC_B;
    } ;

    /* Counter reload register */
    union
    {
        __IOM uint32_t CNTRLD;

        struct
        {
            __IOM uint32_t CNTRLD     : 12;
            __IM  uint32_t RESERVED1  : 20;
        } CNTRLD_B;
    } ;

    /* Status register */
    union
    {
        __IM  uint32_t STS;

        struct
        {
            __IM  uint32_t PSCUFLG    : 1;
            __IM  uint32_t CNTUFLG    : 1;
            __IM  uint32_t WINUFLG    : 1;
            __IM  uint32_t RESERVED1  : 29;
        } STS_B;
    } ;

    /* Window register */
    union
    {
        __IOM uint32_t WIN;

        struct
        {
            __IOM uint32_t WIN        : 12;
            __IM  uint32_t RESERVED1  : 20;
        } WIN_B;
    } ;
} IWDT_T;

/**
  * @brief Option bytes (OB)
  */

typedef struct
{

    /* Read protection option byte */
    union
    {
        __IOM uint16_t READPROT;

        struct
        {
            __IOM uint16_t READPROT   : 8;
            __IOM uint16_t nREADPROT  : 8;
        } READPORT_B;
    } ;

    /* User protection option byte */
    union
    {
        __IOM uint16_t USER;

        struct
        {
            __IOM uint16_t WDTSEL     : 1;
            __IOM uint16_t RSTSTOP    : 1;
            __IOM uint16_t RSTSTDBY   : 1;
            __IM  uint16_t RESERVED1  : 1;
            __IOM uint16_t BOT1       : 1;
            __IOM uint16_t VDDAMON    : 1;
            __IOM uint16_t RPC        : 1;
            __IM  uint16_t RESERVED2  : 1;
            __IOM uint16_t nUSER      : 8;
        } USER_B;
    } ;

    /* User data option byte */
    union
    {
        __IOM uint16_t DATA0;

        struct
        {
            __IOM uint16_t DATA0      : 8;
            __IOM uint16_t nDATA0     : 8;
        } DATA0_B;
    } ;

    /* User data option byte */
    union
    {
        __IOM uint16_t DATA1;

        struct
        {
            __IOM uint16_t DATA1      : 8;
            __IOM uint16_t nDATA1     : 8;
        } DATA1_B;
    } ;

    /* Write protection option byte */
    union
    {
        __IOM uint16_t WRTPROT0;

        struct
        {
            __IOM uint16_t WRTPROT0   : 8;
            __IOM uint16_t nWRTPROT0  : 8;
        } WRTPROT0_B;
    } ;

    /* Write protection option byte */
    union
    {
        __IOM uint16_t WRTPROT1;

        struct
        {
            __IOM uint16_t WRTPROT1   : 8;
            __IOM uint16_t nWRTPROT1  : 8;
        } WRTPROT1_B;
    } ;
} OB_T;

/**
  * @brief Power control (PMU)
  */

typedef struct
{
    /* power control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t LPDSCFG    : 1;
            __IOM uint32_t PDDSCFG    : 1;
            __IOM uint32_t WUFLGCLR   : 1;
            __IOM uint32_t SBFLGCLR   : 1;
            __IOM uint32_t PVDEN      : 1;
            __IOM uint32_t PLSEL      : 3;
            __IOM uint32_t BPWEN      : 1;
            __IM  uint32_t RESERVED1  : 23;

        } CTRL_B;
    } ;

    /* power control/status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IM  uint32_t WUEFLG     : 1;
            __IM  uint32_t SBFLG      : 1;
            __IM  uint32_t PVDOFLG    : 1;
            __IM  uint32_t RESERVED1  : 5;
            __IOM uint32_t WKUPCFG1   : 1;
            __IOM uint32_t WKUPCFG2   : 1;
            __IOM uint32_t WKUPCFG3   : 1;
            __IOM uint32_t WKUPCFG4   : 1;
            __IOM uint32_t WKUPCFG5   : 1;
            __IOM uint32_t WKUPCFG6   : 1;
            __IOM uint32_t WKUPCFG7   : 1;
            __IOM uint32_t WKUPCFG8   : 1;
            __IM  uint32_t RESERVED2  : 16;
        } CSTS_B;
    } ;
} PMU_T;

/**
  * @brief Reset and clock control (RCM)
  */

typedef struct
{
    /*Clock control register 1 */
    union
    {
        /* Clock control register */
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t HSIEN      : 1;
            __IM  uint32_t HSIRDYFLG  : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t HSITRM     : 5;
            __IM  uint32_t HSICAL     : 8;
            __IOM uint32_t HSEEN      : 1;
            __IM  uint32_t HSERDYFLG  : 1;
            __IOM uint32_t HSEBCFG    : 1;
            __IOM uint32_t CSSEN      : 1;
            __IM  uint32_t RESERVED2  : 4;
            __IOM uint32_t PLLEN      : 1;
            __IM  uint32_t PLLRDYFLG  : 1;
            __IM  uint32_t RESERVED3  : 6;
        } CTRL1_B;
    } ;

    /* Clock configuration register 1 */
    union
    {
        __IOM uint32_t CFG1;

        struct
        {
            __IOM uint32_t SCLKSEL    : 2;
            __IM  uint32_t SCLKSWSTS  : 2;
            __IOM uint32_t AHBPSC     : 4;
            __IOM uint32_t APB1PSC    : 3;
            __IM  uint32_t RESERVED1  : 3;
            __IOM uint32_t ADCPSC     : 1;
            __IOM uint32_t PLLSRCSEL  : 2;
            __IOM uint32_t PLLHSEPSC  : 1;
            __IOM uint32_t PLLMULCFG  : 4;
            __IM  uint32_t RESERVED3  : 2;
            __IOM uint32_t MCOSEL     : 4;
            __IOM uint32_t MCOPSC     : 3;
            __IOM uint32_t MCOPLLPSC  : 1;
        } CFG1_B;
    } ;

    /* Clock interrupt register */
    union
    {
        __IOM uint32_t INT;

        struct
        {
            __IM  uint32_t LSIRDYFLG  : 1;
            __IM  uint32_t LSERDYFLG  : 1;
            __IM  uint32_t HSIRDYFLG  : 1;
            __IM  uint32_t HSERDYFLG  : 1;
            __IM  uint32_t PLLRDYFLG  : 1;
            __IM  uint32_t HSI14RDYFLG : 1;
            __IM  uint32_t HSI48RDYFLG : 1;
            __IM  uint32_t CSSFLG     : 1;
            __IOM uint32_t LSIRDYEN   : 1;
            __IOM uint32_t LSERDYEN   : 1;
            __IOM uint32_t HSIRDYEN   : 1;
            __IOM uint32_t HSERDYEN   : 1;
            __IOM uint32_t PLLRDYEN   : 1;
            __IOM uint32_t HSI14RDYEN : 1;
            __IOM uint32_t HSI48RDYEN : 1;
            __IM  uint32_t RESERVED1  : 1;
            __OM  uint32_t LSIRDYCLR  : 1;
            __OM  uint32_t LSERDYCLR  : 1;
            __OM  uint32_t HSIRDYCLR  : 1;
            __OM  uint32_t HSERDYCLR  : 1;
            __OM  uint32_t PLLRDYCLR  : 1;
            __OM  uint32_t HSI14RDYCLR : 1;
            __OM  uint32_t HSI48RDYCLR : 1;
            __OM  uint32_t CSSCLR     : 1;
            __IM  uint32_t RESERVED2  : 8;
        } INT_B;
    } ;

    /* APB2 peripheral reset register */
    union
    {
        __IOM uint32_t APBRST2;

        struct
        {
            __IOM uint32_t SYSCFGRST     : 1;
            __IM  uint32_t RESERVED1     : 4;
            __IOM uint32_t USART5RST     : 1;
            __IOM uint32_t USART6RST     : 1;
            __IOM uint32_t USART7RST     : 1;
            __IM  uint32_t RESERVED2     : 1;
            __IOM uint32_t ADCRST        : 1;
            __IM  uint32_t RESERVED3     : 1;
            __IOM uint32_t TMR1RST       : 1;
            __IOM uint32_t SPI1RST       : 1;
            __IM  uint32_t RESERVED4     : 1;
            __IOM uint32_t USART1RST     : 1;
            __IM  uint32_t RESERVED5     : 1;
            __IOM uint32_t TMR15RST      : 1;
            __IOM uint32_t TMR16RST      : 1;
            __IOM uint32_t TMR17RST      : 1;
            __IM  uint32_t RESERVED6     : 3;
            __IOM uint32_t DBGRST        : 1;
            __IM  uint32_t RESERVED7     : 9;
        } APBRST2_B;
    } ;

    /*APB1 peripheral reset register */
    union
    {
        __IOM uint32_t APBRST1;

        struct
        {
            __IOM uint32_t TMR2RST       : 1;
            __IOM uint32_t TMR3RST       : 1;
            __IM  uint32_t RESERVED1     : 2;
            __IOM uint32_t TMR6RST       : 1;
            __IOM uint32_t TMR7RST       : 1;
            __IM  uint32_t RESERVED2     : 2;
            __IOM uint32_t TMR14RST      : 1;
            __IM  uint32_t RESERVED3     : 2;
            __IOM uint32_t WWDTRST       : 1;
            __IM  uint32_t RESERVED4     : 2;
            __IOM uint32_t SPI2RST       : 1;
            __IM  uint32_t RESERVED5     : 2;
            __IOM uint32_t USART2RST     : 1;
            __IOM uint32_t USART3RST     : 1;
            __IOM uint32_t USART4RST     : 1;
            __IOM uint32_t USART5RST     : 1;
            __IOM uint32_t I2C1RST       : 1;
            __IOM uint32_t I2C2RST       : 1;
            __IOM uint32_t USBDRST       : 1;
            __IM  uint32_t RESERVED6     : 1;
            __IOM uint32_t CANRST        : 1;
            __IM  uint32_t RESERVED7     : 1;
            __IOM uint32_t CRSRST        : 1;
            __IOM uint32_t PMURST        : 1;
            __IOM uint32_t DACRST        : 1;
            __IOM uint32_t CECRST        : 1;
            __IM  uint32_t RESERVED8     : 1;
        } APBRST1_B;
    } ;

    /* AHB Peripheral Clock enable register */
    union
    {
        __IOM uint32_t AHBCLKEN;

        struct
        {
            __IOM uint32_t DMA1EN       : 1;
            __IOM uint32_t DMA2EN       : 1;
            __IOM uint32_t SRAMEN       : 1;
            __IM  uint32_t RESERVED1    : 1;
            __IOM uint32_t FMCEN        : 1;
            __IM  uint32_t RESERVED2    : 1;
            __IOM uint32_t CRCEN        : 1;
            __IM  uint32_t RESERVED3    : 10;
            __IOM uint32_t PAEN         : 1;
            __IOM uint32_t PBEN         : 1;
            __IOM uint32_t PCEN         : 1;
            __IOM uint32_t PDEN         : 1;
            __IOM uint32_t PEEN         : 1;
            __IOM uint32_t PFEN         : 1;
            __IM  uint32_t RESERVED4    : 1;
            __IOM uint32_t TSCEN        : 1;
            __IM  uint32_t RESERVED5    : 7;
        } AHBCLKEN_B;
    } ;

    union
    {
        __IOM uint32_t APBCLKEN2;

        struct
        {
            __IOM uint32_t SCFGCOMPEN   : 1;
            __IM  uint32_t RESERVED1    : 4;
            __IOM uint32_t USART6EN     : 1;
            __IOM uint32_t USART7EN     : 1;
            __IOM uint32_t USART8EN     : 1;
            __IM  uint32_t RESERVED2    : 1;
            __IOM uint32_t ADCEN        : 1;
            __IM  uint32_t RESERVED3    : 1;
            __IOM uint32_t TMR1EN       : 1;
            __IOM uint32_t SPI1EN       : 1;
            __IM  uint32_t RESERVED4    : 1;
            __IOM uint32_t USART1V     : 1;
            __IM  uint32_t RESERVED5    : 1;
            __IOM uint32_t TMR15EN      : 1;
            __IOM uint32_t TMR16EN      : 1;
            __IOM uint32_t TMR17EN      : 1;
            __IM  uint32_t RESERVED6    : 3;
            __IOM uint32_t DBGEN        : 1;
            __IM  uint32_t RESERVED7    : 9;
        } APBCLKEN2_B;
    } ;

    /* APB1 peripheral clock enable register */
    union
    {
        __IOM uint32_t APBCLKEN1;

        struct
        {
            __IOM uint32_t TMR2EN       : 1;
            __IOM uint32_t TMR3EN       : 1;
            __IM  uint32_t RESERVED1    : 2;
            __IOM uint32_t TMR6EN       : 1;
            __IOM uint32_t TMR7EN       : 1;
            __IM  uint32_t RESERVED2    : 2;
            __IOM uint32_t TMR14EN      : 1;
            __IM  uint32_t RESERVED3    : 2;
            __IOM uint32_t WWDTEN       : 1;
            __IM  uint32_t RESERVED4    : 2;
            __IOM uint32_t SPI2EN       : 1;
            __IM  uint32_t RESERVED5    : 2;
            __IOM uint32_t USART2EN     : 1;
            __IOM uint32_t USART3EN     : 1;
            __IOM uint32_t USART4EN     : 1;
            __IOM uint32_t USART5EN     : 1;
            __IOM uint32_t I2C1EN       : 1;
            __IOM uint32_t I2C2EN       : 1;
            __IOM uint32_t USBDEN       : 1;
            __IM  uint32_t RESERVED6    : 1;
            __IOM uint32_t CANEN        : 1;
            __IM  uint32_t RESERVED7    : 1;
            __IOM uint32_t CRSEN        : 1;
            __IOM uint32_t PMUEN        : 1;
            __IOM uint32_t DACEN        : 1;
            __IOM uint32_t CECEN        : 1;
            __IM  uint32_t RESERVED8    : 1;
        } APBCLKEN1_B;
    } ;

    /* Backup domain control register */
    union
    {
        __IOM uint32_t BDCTRL;

        struct
        {
            __IOM uint32_t LSEEN      : 1;
            __IM  uint32_t LSERDYFLG  : 1;
            __IOM uint32_t LSEBCFG    : 1;
            __IOM uint32_t LSEDRVCFG  : 2;
            __IM  uint32_t RESERVED1  : 3;
            __IOM uint32_t RTCSRCSEL  : 2;
            __IM  uint32_t RESERVED2  : 5;
            __IOM uint32_t RTCCLKEN   : 1;
            __IOM uint32_t BDRST      : 1;
            __IM  uint32_t RESERVED3  : 15;
        } BDCTRL_B;
    } ;

    /* Control/status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IOM uint32_t LSIEN      : 1;
            __IM  uint32_t LSIRDYFLG  : 1;
            __IM  uint32_t RESERVED1  : 21;
            __IM  uint32_t PWRRSTFLG  : 1;
            __IOM uint32_t RSTFLGCLR  : 1;
            __IM  uint32_t OBRSTFLG   : 1;
            __IM  uint32_t PINRSTFLG  : 1;
            __IM  uint32_t PODRSTFLG  : 1;
            __IM  uint32_t SWRSTFLG   : 1;
            __IM  uint32_t IWDTRSTFLG : 1;
            __IM  uint32_t WWDTRSTFLG : 1;
            __IM  uint32_t LPWRRSTFLG : 1;
        } CSTS_B;
    } ;

    /* AHB peripheral reset register */
    union
    {
        __IOM uint32_t AHBRST;

        struct
        {
            __IM  uint32_t RESERVED1  : 17;
            __IOM uint32_t PARST      : 1;
            __IOM uint32_t PBRST      : 1;
            __IOM uint32_t PCRST      : 1;
            __IOM uint32_t PDRST      : 1;
            __IOM uint32_t PERST      : 1;
            __IOM uint32_t PFRST      : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t TSCRST     : 1;
            __IM  uint32_t RESERVED3  : 7;
        } AHBRST_B;
    } ;

    /* Clock configuration register 2 */
    union
    {
        __IOM uint32_t CFG2;

        struct
        {
            __IOM uint32_t PLLDIVCFG  : 4;
            __IM  uint32_t RESERVED1  : 28;
        } CFG2_B;
    } ;

    /*Clock configuration register 3 */
    union
    {
        __IOM uint32_t CFG3;

        struct
        {
            __IOM uint32_t USART1SEL  : 2;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t I2C1SEL    : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t CECSEL     : 1;
            __IOM uint32_t USBDSEL    : 1;
            __IOM uint32_t ADCSEL     : 1;
            __IM  uint32_t RESERVED3  : 7;
            __IOM uint32_t USART2SEL  : 2;
            __IOM uint32_t USART3SEL  : 2;
            __IM  uint32_t RESERVED4  : 12;
        } CFG3_B;
    } ;

    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t HSI14EN    : 1;
            __IM  uint32_t HSI14RDFLG : 1;
            __IOM uint32_t HSI14TO    : 1;
            __IOM uint32_t HSI14TRM   : 5;
            __IM  uint32_t HSI14CAL   : 8;
            __IOM uint32_t HSI48EN    : 1;
            __IM  uint32_t HSI48RDFLG : 1;
            __IM  uint32_t RESERVED1  : 6;
            __IM  uint32_t HSI48CAL   : 8;
        } CTRL2_B;
    } ;
} RCM_T;

/**
  * @brief Real-time clock (RTC)
  */

typedef struct
{

    /* time register */
    union
    {
        __IOM uint32_t TIME;

        struct
        {
            __IOM uint32_t SECU       : 4;
            __IOM uint32_t SECT       : 3;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t MINU       : 4;
            __IOM uint32_t MINT       : 3;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t HRU        : 4;
            __IOM uint32_t HRT        : 2;
            __IOM uint32_t TIMEFCFG   : 1;
            __IM  uint32_t RESERVED3  : 9;
        } TIME_B;
    } ;

    /* date register */
    union
    {
        __IOM uint32_t DATE;

        struct
        {
            __IOM uint32_t DAYU       : 4;
            __IOM uint32_t DAYT       : 2;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t MONU       : 4;
            __IOM uint32_t MONT       : 1;
            __IOM uint32_t WEEKSEL    : 3;
            __IOM uint32_t YRU        : 4;
            __IOM uint32_t YRT        : 4;
            __IM  uint32_t RESERVED2  : 8;
        } DATE_B;
    } ;

    /* control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t WUCLKSEL   : 3;
            __IOM uint32_t TSETECFG   : 1;
            __IOM uint32_t RCLKDEN    : 1;
            __IOM uint32_t RCMCFG     : 1;
            __IOM uint32_t TIMEFCFG   : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t ALREN      : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t WUTEN      : 1;
            __IOM uint32_t TSEN       : 1;
            __IOM uint32_t ALRIEN     : 1;
            __IM  uint32_t RESERVED3  : 1;
            __IOM uint32_t WUTIEN     : 1;
            __IOM uint32_t TSIEN      : 1;
            __OM  uint32_t STCCFG     : 1;
            __OM  uint32_t WTCCFG     : 1;
            __IOM uint32_t BAKP       : 1;
            __IOM uint32_t CALOSEL    : 1;
            __IOM uint32_t POLCFG     : 1;
            __IOM uint32_t OUTSEL     : 2;
            __IOM uint32_t CALOEN     : 1;
            __IM  uint32_t RESERVED4  : 8;
        } CTRL_B;
    } ;

    /* initialization and status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t ALRWFLG    : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t WUTWFLG    : 1;
            __IOM uint32_t SOPFLG     : 1;
            __IM  uint32_t INITSFLG   : 1;
            __IOM uint32_t RSFLG      : 1;
            __IM  uint32_t RINITFLG   : 1;
            __IOM uint32_t INITEN     : 1;
            __IOM uint32_t ALRAFLG    : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t WUTFLG     : 1;
            __IOM uint32_t TSFLG      : 1;
            __IOM uint32_t TSOVRFLG   : 1;
            __IOM uint32_t TP1FLG     : 1;
            __IOM uint32_t TP2FLG     : 1;
            __IM  uint32_t TP3FLG     : 1;
            __IM  uint32_t RCALPFLG   : 1;
            __IM  uint32_t RESERVED3  : 15;
        } STS_B;
    } ;

    /* prescaler register */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint32_t SPSC       : 15;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t APSC       : 7;
            __IM  uint32_t RESERVED2  : 9;
        } PSC_B;
    } ;

    /* auto-reload register */
    union
    {
        __OM  uint32_t AUTORLD;

        struct
        {
            __OM  uint32_t WUAUTORE   : 15;
            __IM  uint32_t RESERVED1  : 17;
        } AUTORLD_B;
    } ;
    __IM  uint32_t  RESERVED;

    /* alarm A register */
    union
    {
        __IOM uint32_t ALRMA;

        struct
        {
            __IOM uint32_t SECU       : 4;
            __IOM uint32_t SECT       : 3;
            __IOM uint32_t SECMEN     : 1;
            __IOM uint32_t MINU       : 4;
            __IOM uint32_t MINT       : 3;
            __IOM uint32_t MINMEN     : 1;
            __IOM uint32_t HRU        : 4;
            __IOM uint32_t HRT        : 2;
            __IOM uint32_t TIMEFCFG   : 1;
            __IOM uint32_t HRMEN      : 1;
            __IOM uint32_t DAYU       : 4;
            __IOM uint32_t DAYT       : 2;
            __IOM uint32_t WEEKSEL    : 1;
            __IOM uint32_t DATEMEN    : 1;
        } ALRMA_B;
    } ;

    __IM  uint32_t  RESERVED1;

    /* write protection register */
    union
    {
        __OM  uint32_t WRPROT;

        struct
        {
            __OM  uint32_t KEY        : 8;
            __IM  uint32_t RESERVED1  : 24;
        } WRPROT_B;
    } ;

    /* sub second register */
    union
    {
        __IM  uint32_t SUBSEC;

        struct
        {
            __IM  uint32_t SUBSEC     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } SUBSEC_B;
    } ;

    /* shift control register */
    union
    {
        __OM  uint32_t SHIFT;

        struct
        {
            __OM  uint32_t SFSEC      : 15;
            __IM  uint32_t RESERVED1  : 16;
            __OM  uint32_t ADD1SECEN  : 1;
        } SHIFT_B;
    } ;

    /* timestamp time register */
    union
    {
        __IM  uint32_t TSTIME;

        struct
        {
            __IM  uint32_t SECU       : 4;
            __IM  uint32_t SECT       : 3;
            __IM  uint32_t RESERVED1  : 1;
            __IM  uint32_t MINU       : 4;
            __IM  uint32_t MINT       : 3;
            __IM  uint32_t RESERVED2  : 1;
            __IM  uint32_t HRU        : 4;
            __IM  uint32_t HRT        : 2;
            __IM  uint32_t TIMEFCFG   : 1;
            __IM  uint32_t RESERVED3  : 9;
        } TSTIME_B;
    } ;

    /* timestamp date register */
    union
    {
        __IM  uint32_t TSDATE;

        struct
        {
            __IM  uint32_t DAYU       : 4;
            __IM  uint32_t DAYT       : 2;
            __IM  uint32_t RESERVED1  : 2;
            __IM  uint32_t MONU       : 4;
            __IM  uint32_t MONT       : 1;
            __IM  uint32_t WEEKSEL    : 3;
            __IM  uint32_t RESERVED2  : 16;
        } TSDATE_B;
    } ;

    /* time-stamp sub second register */
    union
    {
        __IM  uint32_t TSSUBSEC;

        struct
        {
            __IM  uint32_t SUBSEC     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } TSSUBSEC_B;
    } ;

    /* calibration register */
    union
    {
        __IOM uint32_t CAL;

        struct
        {
            __IOM uint32_t RECALF     : 9;
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t CAL16CFG   : 1;
            __IOM uint32_t CAL8CFG    : 1;
            __IOM uint32_t ICALFEN    : 1;
            __IM  uint32_t RESERVED2  : 16;
        } CAL_B;
    } ;

    /* tamper and alternate function configuration register */
    union
    {
        __IOM uint32_t TACFG;

        struct
        {
            __IOM uint32_t TP1EN      : 1;
            __IOM uint32_t TP1ALCFG   : 1;
            __IOM uint32_t TPIEN      : 1;
            __IOM uint32_t TP2EN      : 1;
            __IOM uint32_t TP2ALCFG   : 1;
            __IOM uint32_t TP3EN      : 1;
            __IOM uint32_t TP3ALCFG   : 1;
            __IOM uint32_t TPTSEN     : 1;
            __IOM uint32_t TPSFSEL    : 3;
            __IOM uint32_t TPFCSEL    : 2;
            __IOM uint32_t TPPRDUSEL  : 2;
            __IOM uint32_t TPPUDIS    : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t PC13VAL    : 1;
            __IOM uint32_t PC13EN     : 1;
            __IOM uint32_t PC14VAL    : 1;
            __IOM uint32_t PC14EN     : 1;
            __IOM uint32_t PC15VAL    : 1;
            __IOM uint32_t PC15EN     : 1;
            __IM  uint32_t RESERVED2  : 8;
        } TACFG_B;
    } ;

    /* alarm A sub second register */
    union
    {
        __IOM uint32_t ALRMASS;

        struct
        {
            __IOM uint32_t SUBSEC     : 15;
            __IM  uint32_t RESERVED1  : 9;
            __IOM uint32_t MASKSEL    : 4;
            __IM  uint32_t RESERVED2  : 4;
        } ALRMASS_B;
    } ;

    __IM  uint32_t RESERVED2[2];

    union
    {
        __IOM uint32_t BAKP0;

        struct
        {
            __IOM uint32_t BAKP       : 32;
        } BAKP0_B;
    } ;

    union
    {
        __IOM uint32_t BAKP1;

        struct
        {
            __IOM uint32_t BAKP       : 32;
        } BAKP1_B;
    } ;
    union
    {
        __IOM uint32_t BAKP2;

        struct
        {
            __IOM uint32_t BAKP       : 32;
        } BAKP2_B;
    } ;
    union
    {
        __IOM uint32_t BAKP3;

        struct
        {
            __IOM uint32_t BAKP       : 32;
        } BAKP3_B;
    } ;
    union
    {
        __IOM uint32_t BAKP4;

        struct
        {
            __IOM uint32_t BAKP       : 32;
        } BAKP4_B;
    } ;
} RTC_T;

/**
  * @brief Serial peripheral interface (SPI1)
  */

typedef struct
{
    /* control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t CPHA       : 1;
            __IOM uint32_t CPOL       : 1;
            __IOM uint32_t MSMCFG     : 1;
            __IOM uint32_t BRSEL      : 3;
            __IOM uint32_t SPIEN      : 1;
            __IOM uint32_t LSBSEL     : 1;
            __IOM uint32_t ISSEL      : 1;
            __IOM uint32_t SSEN       : 1;
            __IOM uint32_t RXOMEN     : 1;
            __IOM uint32_t CRCLSEL    : 1;
            __IOM uint32_t CRCNXT     : 1;
            __IOM uint32_t CRCEN      : 1;
            __IOM uint32_t BMOEN      : 1;
            __IOM uint32_t BMEN       : 1;
            __IM  uint32_t RESERVED1  : 16;
        } CTRL1_B;
    } ;

    /* control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t RXDEN      : 1;
            __IOM uint32_t TXDEN      : 1;
            __IOM uint32_t SSOEN      : 1;
            __IOM uint32_t NSSPEN     : 1;
            __IOM uint32_t FRFCFG     : 1;
            __IOM uint32_t ERRIEN     : 1;
            __IOM uint32_t RXBNEIEN   : 1;
            __IOM uint32_t TXBEIEN    : 1;
            __IOM uint32_t DSCFG      : 4;
            __IOM uint32_t FRTCFG     : 1;
            __IOM uint32_t LDRX       : 1;
            __IOM uint32_t LDTX       : 1;
            __IM  uint32_t RESERVED1  : 17;
        } CTRL2_B;
    } ;

    /* status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t RXBNEFLG   : 1;
            __IM  uint32_t TXBEFLG    : 1;
            __IM  uint32_t SCHDIR     : 1;
            __IM  uint32_t UDRFLG     : 1;
            __IOM uint32_t CRCEFLG    : 1;
            __IM  uint32_t MEFLG      : 1;
            __IM  uint32_t OVRFLG     : 1;
            __IM  uint32_t BSYFLG     : 1;
            __IM  uint32_t FRECFG     : 1;
            __IM  uint32_t FRLSEL     : 2;
            __IM  uint32_t FTLSEL     : 2;
            __IM  uint32_t RESERVED1  : 19;
        } STS_B;
    } ;

    /* data register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA       : 16;
            __IM  uint32_t RESERVED1  : 16;
        } DATA_B;
    } ;

    /* CRC polynomial register */
    union
    {
        __IOM uint32_t CRCPOLY;

        struct
        {
            __IOM uint32_t CRCPOLY    : 16;
            __IM  uint32_t RESERVED1  : 16;
        } CRCPOLY_B;
    } ;

    /*RX CRC register */
    union
    {

        __IM  uint32_t RXCRC;

        struct
        {
            __IM  uint32_t RXCRC      : 16;
            __IM  uint32_t RESERVED1  : 16;
        } RXCRC_B;
    } ;

    /* TX CRC register */
    union
    {

        __IM  uint32_t TXCRC;

        struct
        {
            __IM  uint32_t TXCRC      : 16;
            __IM  uint32_t RESERVED1  : 16;
        } TXCRC_B;
    } ;

    /* I2S CFG register */
    union
    {
        __IOM uint32_t I2SCFG;

        struct
        {
            __IOM uint32_t CHLEN      : 1;
            __IOM uint32_t DATALEN    : 2;
            __IOM uint32_t CPOL       : 1;
            __IOM uint32_t I2SSSEL    : 2;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t PFSSEL     : 1;
            __IOM uint32_t I2SMOD     : 2;
            __IOM uint32_t I2SEN      : 1;
            __IOM uint32_t MODESEL    : 1;
            __IM  uint32_t RESERVED2  : 20;
        } I2SCFG_B;
    } ;

    /* I2S Prescaler */
    union
    {
        __IOM uint32_t I2SPSC;

        struct
        {
            __IOM uint32_t I2SPSC     : 8;
            __IOM uint32_t ODDPSC     : 1;
            __IOM uint32_t MCOEN      : 1;
            __IM  uint32_t RESERVED1  : 22;
        } I2SPSC_B;
    } ;
} SPI_T;

/**
  * @brief System configuration controller (SYSCFG)
  */

typedef struct
{
    /* configuration register 1 */
    union
    {
        __IOM uint32_t CFG1;

        struct
        {
            __IOM uint32_t MMSEL        : 2;
            __IM  uint32_t RESERVED1    : 4;
            __IOM uint32_t IRSEL        : 2;
            __IOM uint32_t ADCDMARMP    : 1;
            __IOM uint32_t USART1TXRMP  : 1;
            __IOM uint32_t USART1RXRMP  : 1;
            __IOM uint32_t TMR16DMARMP  : 1;
            __IOM uint32_t TMR17DMARMP  : 1;
            __IOM uint32_t TMR16DMARMP2 : 1;
            __IOM uint32_t TMR17DMARMP2 : 1;
            __IM  uint32_t RESERVED2    : 1;
            __IOM uint32_t I2CPB6FMP    : 1;
            __IOM uint32_t I2CPB7FMP    : 1;
            __IOM uint32_t I2CPB8FMP    : 1;
            __IOM uint32_t I2CPB9FMP    : 1;
            __IOM uint32_t I2C1FMP      : 1;
            __IOM uint32_t I2C2FMP      : 1;
            __IOM uint32_t I2CPA9FMP    : 1;
            __IOM uint32_t I2CPA10FMP   : 1;
            __IOM uint32_t SPI2DMARMP   : 1;
            __IOM uint32_t USART2DMARMP : 1;
            __IOM uint32_t USART3DMARMP : 1;
            __IOM uint32_t I2C1DMARMP   : 1;
            __IOM uint32_t TMR1DMARMP   : 1;
            __IOM uint32_t TMR2DMARMP   : 1;
            __IOM uint32_t TMR3DMARMP   : 1;
            __IM  uint32_t RESERVED3    : 1;
        } CFG1_B;
    } ;
    __IM  uint32_t  RESERVED;

    /* external interrupt configuration register 1 */
    union
    {

        __IOM uint32_t EINTCFG1;

        struct
        {
            __IOM uint32_t EINT0      : 4;
            __IOM uint32_t EINT1      : 4;
            __IOM uint32_t EINT2      : 4;
            __IOM uint32_t EINT3      : 4;
            __IM  uint32_t RESERVED1  : 16;
        } EINTCFG1_B;
    } ;

    /* external interrupt configuration register 2 */
    union
    {
        __IOM uint32_t EINTCFG2;

        struct
        {
            __IOM uint32_t EINT4      : 4;
            __IOM uint32_t EINT5      : 4;
            __IOM uint32_t EINT6      : 4;
            __IOM uint32_t EINT7      : 4;
            __IM  uint32_t RESERVED1  : 16;
        } EINTCFG2_B;
    } ;

    /* external interrupt configuration register 3 */
    union
    {
        __IOM uint32_t EINTCFG3;

        struct
        {
            __IOM uint32_t EINT8      : 4;
            __IOM uint32_t EINT9      : 4;
            __IOM uint32_t EINT10     : 4;
            __IOM uint32_t EINT11     : 4;
            __IM  uint32_t RESERVED1  : 16;
        } EINTCFG3_B;
    } ;

    /* external interrupt configuration register 4 */
    union
    {
        __IOM uint32_t EINTCFG4;

        struct
        {
            __IOM uint32_t EINT12     : 4;
            __IOM uint32_t EINT13     : 4;
            __IOM uint32_t EINT14     : 4;
            __IOM uint32_t EINT15     : 4;
            __IM  uint32_t RESERVED1  : 16;
        } EINTCFG4_B;
    } ;

    /* configuration register 2 */
    union
    {
        __IOM uint32_t CFG2;

        struct
        {
            __IOM uint32_t LOCK       : 1;
            __IOM uint32_t SRAMLOCK   : 1;
            __IOM uint32_t PVDLOCK    : 1;
            __IM  uint32_t RESERVED1  : 5;
            __IOM uint32_t SRAMEFLG   : 1;
            __IM  uint32_t RESERVED2  : 23;
        } CFG2_B;
    } ;
} SYSCFG_T;

/**
  * @brief Touch sensing controller (TSC)
  */

typedef struct
{
    /* I/O group 1~8 counter register */
    union
    {
        __IM  uint32_t IOGCNT;

        struct
        {
            __IM  uint32_t CNTVAL     : 14;
            __IM  uint32_t RESERVED1  : 18;
        } IOGCNT_B;
    };
} TSC_IOGroupRegister_T;

typedef struct
{
    /* configuration register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t TSCEN      : 1;
            __IOM uint32_t STARTAFLG  : 1;
            __IOM uint32_t AMCFG      : 1;
            __IOM uint32_t SYNPPOL    : 1;
            __IOM uint32_t IODEFCFG   : 1;
            __IOM uint32_t MCNTVSEL   : 3;
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t PGCDFSEL   : 3;
            __IOM uint32_t SSCDFSEL   : 1;
            __IOM uint32_t SSEN       : 1;
            __IOM uint32_t SSERRVSEL  : 7;
            __IOM uint32_t CTPLSEL    : 4;
            __IOM uint32_t CTPHSEL    : 4;
        } CTRL_B;
    } ;

    /* interrupt enable register */
    union
    {
        __IOM uint32_t INTEN;

        struct
        {
            __IOM uint32_t EOAIEN     : 1;
            __IOM uint32_t MCEIEN     : 1;
            __IM  uint32_t RESERVED1  : 30;
        } INTEN_B;
    } ;

    /* interrupt clear register */
    union
    {
        __IOM uint32_t INTFCLR;

        struct
        {
            __IOM uint32_t EOAICLR    : 1;
            __IOM uint32_t MCEICLR    : 1;
            __IM  uint32_t RESERVED1  : 30;
        } INTFCLR_B;
    } ;

    /* interrupt status register */
    union
    {
        __IOM uint32_t INTSTS;

        struct
        {
            __IOM uint32_t EOAFLG     : 1;
            __IOM uint32_t MCEFLG     : 1;
            __IM  uint32_t RESERVED1  : 30;
        } INTSTS_B;
    } ;

    /* I/O hysteresis control register */
    union
    {
        __IOM uint32_t IOHCTRL;

        struct
        {
            __IOM uint32_t G1P1       : 1;
            __IOM uint32_t G1P2       : 1;
            __IOM uint32_t G1P3       : 1;
            __IOM uint32_t G1P4       : 1;
            __IOM uint32_t G2P1       : 1;
            __IOM uint32_t G2P2       : 1;
            __IOM uint32_t G2P3       : 1;
            __IOM uint32_t G2P4       : 1;
            __IOM uint32_t G3P1       : 1;
            __IOM uint32_t G3P2       : 1;
            __IOM uint32_t G3P3       : 1;
            __IOM uint32_t G3P4       : 1;
            __IOM uint32_t G4P1       : 1;
            __IOM uint32_t G4P2       : 1;
            __IOM uint32_t G4P3       : 1;
            __IOM uint32_t G4P4       : 1;
            __IOM uint32_t G5P1       : 1;
            __IOM uint32_t G5P2       : 1;
            __IOM uint32_t G5P3       : 1;
            __IOM uint32_t G5P4       : 1;
            __IOM uint32_t G6P1       : 1;
            __IOM uint32_t G6P2       : 1;
            __IOM uint32_t G6P3       : 1;
            __IOM uint32_t G6P4       : 1;
            __IM  uint32_t RESERVED1  : 8;
        } IOHCTRL_B;
    } ;
    __IM  uint32_t  RESERVED;

    /* I/O analog switch control register */
    union
    {
        __IOM uint32_t IOASWCTRL;

        struct
        {
            __IOM uint32_t G1P1       : 1;
            __IOM uint32_t G1P2       : 1;
            __IOM uint32_t G1P3       : 1;
            __IOM uint32_t G1P4       : 1;
            __IOM uint32_t G2P1       : 1;
            __IOM uint32_t G2P2       : 1;
            __IOM uint32_t G2P3       : 1;
            __IOM uint32_t G2P4       : 1;
            __IOM uint32_t G3P1       : 1;
            __IOM uint32_t G3P2       : 1;
            __IOM uint32_t G3P3       : 1;
            __IOM uint32_t G3P4       : 1;
            __IOM uint32_t G4P1       : 1;
            __IOM uint32_t G4P2       : 1;
            __IOM uint32_t G4P3       : 1;
            __IOM uint32_t G4P4       : 1;
            __IOM uint32_t G5P1       : 1;
            __IOM uint32_t G5P2       : 1;
            __IOM uint32_t G5P3       : 1;
            __IOM uint32_t G5P4       : 1;
            __IOM uint32_t G6P1       : 1;
            __IOM uint32_t G6P2       : 1;
            __IOM uint32_t G6P3       : 1;
            __IOM uint32_t G6P4       : 1;
            __IM  uint32_t RESERVED1  : 8;
        } IOASWCTRL_B;
    } ;
    __IM  uint32_t  RESERVED1;

    /* I/O sampling control register  */
    union
    {
        __IOM uint32_t IOSMPCTRL;

        struct
        {
            __IOM uint32_t G1P1       : 1;
            __IOM uint32_t G1P2       : 1;
            __IOM uint32_t G1P3       : 1;
            __IOM uint32_t G1P4       : 1;
            __IOM uint32_t G2P1       : 1;
            __IOM uint32_t G2P2       : 1;
            __IOM uint32_t G2P3       : 1;
            __IOM uint32_t G2P4       : 1;
            __IOM uint32_t G3P1       : 1;
            __IOM uint32_t G3P2       : 1;
            __IOM uint32_t G3P3       : 1;
            __IOM uint32_t G3P4       : 1;
            __IOM uint32_t G4P1       : 1;
            __IOM uint32_t G4P2       : 1;
            __IOM uint32_t G4P3       : 1;
            __IOM uint32_t G4P4       : 1;
            __IOM uint32_t G5P1       : 1;
            __IOM uint32_t G5P2       : 1;
            __IOM uint32_t G5P3       : 1;
            __IOM uint32_t G5P4       : 1;
            __IOM uint32_t G6P1       : 1;
            __IOM uint32_t G6P2       : 1;
            __IOM uint32_t G6P3       : 1;
            __IOM uint32_t G6P4       : 1;
            __IM  uint32_t RESERVED1  : 8;
        } IOSMPCTRL_B;
    } ;
    __IM  uint32_t  RESERVED2;

    /* I/O channel control register */
    union
    {
        __IOM uint32_t IOCHCTRL;

        struct
        {
            __IOM uint32_t G1P1       : 1;
            __IOM uint32_t G1P2       : 1;
            __IOM uint32_t G1P3       : 1;
            __IOM uint32_t G1P4       : 1;
            __IOM uint32_t G2P1       : 1;
            __IOM uint32_t G2P2       : 1;
            __IOM uint32_t G2P3       : 1;
            __IOM uint32_t G2P4       : 1;
            __IOM uint32_t G3P1       : 1;
            __IOM uint32_t G3P2       : 1;
            __IOM uint32_t G3P3       : 1;
            __IOM uint32_t G3P4       : 1;
            __IOM uint32_t G4P1       : 1;
            __IOM uint32_t G4P2       : 1;
            __IOM uint32_t G4P3       : 1;
            __IOM uint32_t G4P4       : 1;
            __IOM uint32_t G5P1       : 1;
            __IOM uint32_t G5P2       : 1;
            __IOM uint32_t G5P3       : 1;
            __IOM uint32_t G5P4       : 1;
            __IOM uint32_t G6P1       : 1;
            __IOM uint32_t G6P2       : 1;
            __IOM uint32_t G6P3       : 1;
            __IOM uint32_t G6P4       : 1;
            __IM  uint32_t RESERVED1  : 8;
        } IOCHCTRL_B;
    } ;
    __IM  uint32_t  RESERVED3;

    /* I/O group control status register */
    union
    {
        __IOM uint32_t IOGCSTS;

        struct
        {
            __IOM uint32_t G1EN       : 1;
            __IOM uint32_t G2EN       : 1;
            __IOM uint32_t G3EN       : 1;
            __IOM uint32_t G4EN       : 1;
            __IOM uint32_t G5EN       : 1;
            __IOM uint32_t G6EN       : 1;
            __IOM uint32_t G7EN       : 1;
            __IOM uint32_t G8EN       : 1;
            __IM  uint32_t RESERVED1  : 8;
            __IM  uint32_t G1STS      : 1;
            __IM  uint32_t G2STS      : 1;
            __IM  uint32_t G3STS      : 1;
            __IM  uint32_t G4STS      : 1;
            __IM  uint32_t G5STS      : 1;
            __IM  uint32_t G6STS      : 1;
            __IM  uint32_t G7STS      : 1;
            __IM  uint32_t G8STS      : 1;
            __IM  uint32_t RESERVED2  : 8;
        } IOGCSTS_B;
    } ;

    TSC_IOGroupRegister_T IOGxCNT[8];
} TSC_T;

/**
  * @brief Advanced-timers (TMR1)
  */

typedef struct
{
    /* control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t CNTEN      : 1;
            __IOM uint32_t UD         : 1;
            __IOM uint32_t URSSEL     : 1;
            __IOM uint32_t SPMEN      : 1;
            __IOM uint32_t CNTDIR     : 1;
            __IOM uint32_t CAMSEL     : 2;
            __IOM uint32_t ARPEN      : 1;
            __IOM uint32_t CLKDIV     : 2;
            __IM  uint32_t RESERVED1  : 22;
        } CTRL1_B;
    } ;

    /* control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t CCPEN      : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t CCUSEL     : 1;
            __IOM uint32_t CCDSEL     : 1;
            __IOM uint32_t MMSEL      : 3;
            __IOM uint32_t TI1SEL     : 1;
            __IOM uint32_t OC1OIS     : 1;
            __IOM uint32_t OC1NOIS    : 1;
            __IOM uint32_t OC2OIS     : 1;
            __IOM uint32_t OC2NOIS    : 1;
            __IOM uint32_t OC3OIS     : 1;
            __IOM uint32_t OC3NOIS    : 1;
            __IOM uint32_t OC4OIS     : 1;
            __IM  uint32_t RESERVED2  : 17;
        } CTRL2_B;
    } ;

    /* slave mode control register */
    union
    {
        __IOM uint32_t SMCTRL;

        struct
        {
            __IOM uint32_t SMFSEL     : 3;
            __IOM uint32_t OCCSEL     : 1;
            __IOM uint32_t TRGSEL     : 3;
            __IOM uint32_t MSMEN      : 1;
            __IOM uint32_t ETFCFG     : 4;
            __IOM uint32_t ETPCFG     : 2;
            __IOM uint32_t ECEN       : 1;
            __IOM uint32_t ETPOL      : 1;
            __IM  uint32_t RESERVED1  : 16;
        } SMCTRL_B;
    } ;

    /* DMA/Interrupt enable register */
    union
    {
        __IOM uint32_t DIEN;

        struct
        {
            __IOM uint32_t UIEN       : 1;
            __IOM uint32_t CC1IEN     : 1;
            __IOM uint32_t CC2IEN     : 1;
            __IOM uint32_t CC3IEN     : 1;
            __IOM uint32_t CC4IEN     : 1;
            __IOM uint32_t COMIEN     : 1;
            __IOM uint32_t TRGIEN     : 1;
            __IOM uint32_t BRKIEN     : 1;
            __IOM uint32_t UDIEN      : 1;
            __IOM uint32_t CC1DEN     : 1;
            __IOM uint32_t CC2DEN     : 1;
            __IOM uint32_t CC3DEN     : 1;
            __IOM uint32_t CC4DEN     : 1;
            __IOM uint32_t COMDEN     : 1;
            __IOM uint32_t TRGDEN     : 1;
            __IM  uint32_t RESERVED1  : 17;
        } DIEN_B;
    } ;

    /* status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t UIFLG      : 1;
            __IOM uint32_t CC1IFLG    : 1;
            __IOM uint32_t CC2IFLG    : 1;
            __IOM uint32_t CC3IFLG    : 1;
            __IOM uint32_t CC4IFLG    : 1;
            __IOM uint32_t COMIFLG    : 1;
            __IOM uint32_t TRGIFLG    : 1;
            __IOM uint32_t BRKIFLG    : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t CC1RCFLG   : 1;
            __IOM uint32_t CC2RCFLG   : 1;
            __IOM uint32_t CC3RCFLG   : 1;
            __IOM uint32_t CC4RCFLG   : 1;
            __IM  uint32_t RESERVED2  : 19;
        } STS_B;
    } ;

    /* event generation register */
    union
    {
        __OM  uint32_t CEG;

        struct
        {
            __OM  uint32_t UEG        : 1;
            __OM  uint32_t CC1EG      : 1;
            __OM  uint32_t CC2EG      : 1;
            __OM  uint32_t CC3EG      : 1;
            __OM  uint32_t CC4EG      : 1;
            __OM  uint32_t COMG       : 1;
            __OM  uint32_t TEG        : 1;
            __OM  uint32_t BEG        : 1;
            __IM  uint32_t RESERVED1  : 24;
        } CEG_B;
    } ;

    union
    {
        /* capture/compare mode register (output mode) */
        union
        {
            __IOM uint32_t CCM1_OUTPUT;

            struct
            {
                __IOM uint32_t CC1SEL     : 2;
                __IOM uint32_t OC1FEN     : 1;
                __IOM uint32_t OC1PEN     : 1;
                __IOM uint32_t OC1MOD     : 3;
                __IOM uint32_t OC1CEN     : 1;
                __IOM uint32_t CC2SEL     : 2;
                __IOM uint32_t OC2FEN     : 1;
                __IOM uint32_t OC2PEN     : 1;
                __IOM uint32_t OC2MOD     : 3;
                __IOM uint32_t OC2CEN     : 1;
                __IM  uint32_t RESERVED1  : 16;
            } CCM1_OUTPUT_B;
        } ;

        /* capture/compare mode register 1 (input mode) */
        union
        {
            __IOM uint32_t CCM1_INPUT;

            struct
            {
                __IOM uint32_t CC1SEL     : 2;
                __IOM uint32_t IC1PSC     : 2;
                __IOM uint32_t IC1F       : 4;
                __IOM uint32_t CC2SEL     : 2;
                __IOM uint32_t IC2PSC     : 2;
                __IOM uint32_t IC2F       : 4;
                __IM  uint32_t RESERVED1  : 16;
            } CCM1_INPUT_B;
        } ;
    };

    union
    {
        /* capture/compare mode register (output mode) */
        union
        {
            __IOM uint32_t CCM2_OUTPUT;

            struct
            {
                __IOM uint32_t CC3SEL     : 2;
                __IOM uint32_t OC3FEN     : 1;
                __IOM uint32_t OC3PEN     : 1;
                __IOM uint32_t OC3MOD     : 3;
                __IOM uint32_t OC3CEN     : 1;
                __IOM uint32_t CC4SEL     : 2;
                __IOM uint32_t OC4FEN     : 1;
                __IOM uint32_t OC4PEN     : 1;
                __IOM uint32_t OC4MOD     : 3;
                __IOM uint32_t OC4CEN     : 1;
                __IM  uint32_t RESERVED1  : 16;
            } CCM2_OUTPUT_B;
        } ;

        /* capture/compare mode register 2 (input mode) */
        union
        {
            __IOM uint32_t CCM2_INPUT;

            struct
            {
                __IOM uint32_t CC3SEL     : 2;
                __IOM uint32_t IC3PSC     : 2;
                __IOM uint32_t IC3F       : 4;
                __IOM uint32_t CC4SEL     : 2;
                __IOM uint32_t IC4PSC     : 2;
                __IOM uint32_t IC4F       : 4;
                __IM  uint32_t RESERVED1  : 16;
            } CCM2_INPUT_B;
        } ;
    };

    /* capture/compare enable register */
    union
    {
        __IOM uint32_t CCEN;

        struct
        {
            __IOM uint32_t CC1EN      : 1;
            __IOM uint32_t CC1POL     : 1;
            __IOM uint32_t CC1NEN     : 1;
            __IOM uint32_t CC1NPOL    : 1;
            __IOM uint32_t CC2EN      : 1;
            __IOM uint32_t CC2POL     : 1;
            __IOM uint32_t CC2NEN     : 1;
            __IOM uint32_t CC2NPOL    : 1;
            __IOM uint32_t CC3EN      : 1;
            __IOM uint32_t CC3POL     : 1;
            __IOM uint32_t CC3NEN     : 1;
            __IOM uint32_t CC3NPOL    : 1;
            __IOM uint32_t CC4EN      : 1;
            __IOM uint32_t CC4POL     : 1;
            __IM  uint32_t RESERVED1  : 18;
        } CCEN_B;
    } ;

    /* counter */
    union
    {
        __IOM uint32_t CNT;

        struct
        {
            __IOM uint32_t CNT        : 32;
        } CNT_B;
    } ;

    /* prescaler */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint32_t PSC        : 16;
            __IM  uint32_t RESERVED1  : 16;
        } PSC_B;
    } ;

    /* auto-reload register */
    union
    {
        __IOM uint32_t AUTORLD;

        struct
        {
            __IOM uint32_t AUTORLD    : 32;
        } AUTORLD_B;
    } ;

    /* repetition counter register */
    union
    {
        __IOM uint32_t REPCNT;

        struct
        {
            __IOM uint32_t REPCNT     : 8;
            __IM  uint32_t RESERVED1  : 24;
        } REPCNT_B;
    } ;

    /* capture/compare register 1 */
    union
    {
        __IOM uint32_t CC1;

        struct
        {
            __IOM uint32_t CC1        : 32;
        } CC1_B;
    } ;

    /* capture/compare register 2 */
    union
    {
        __IOM uint32_t CC2;

        struct
        {
            __IOM uint32_t CC2        : 32;
        } CC2_B;
    } ;

    /* capture/compare register 3 */
    union
    {
        __IOM uint32_t CC3;

        struct
        {
            __IOM uint32_t CC3        : 32;
        } CC3_B;
    } ;

    /* capture/compare register 4 */
    union
    {
        __IOM uint32_t CC4;

        struct
        {
            __IOM uint32_t CC4        : 32;
        } CC4_B;
    } ;

    /* break and dead-time register */
    union
    {
        __IOM uint32_t BDT;

        struct
        {
            __IOM uint32_t DTS        : 8;
            __IOM uint32_t LOCKCFG    : 2;
            __IOM uint32_t IMOS       : 1;
            __IOM uint32_t RMOS       : 1;
            __IOM uint32_t BRKEN      : 1;
            __IOM uint32_t BRKPOL     : 1;
            __IOM uint32_t AOEN       : 1;
            __IOM uint32_t MOEN       : 1;
            __IM  uint32_t RESERVED1  : 16;
        } BDT_B;
    } ;

    /* DMA control register */
    union
    {
        __IOM uint32_t DCTRL;

        struct
        {
            __IOM uint32_t DBADDR     : 5;
            __IM  uint32_t RESERVED1  : 3;
            __IOM uint32_t DBLEN      : 5;
            __IM  uint32_t RESERVED2  : 19;
        } DCTRL_B;
    } ;

    /* DMA address for full transfer */
    union
    {
        __IOM uint32_t DMADDR;

        struct
        {
            __IOM uint32_t DMADDR     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } DMADDR_B;
    } ;

    /* TMR14 Remap */
    union
    {
        __IOM uint32_t OPT;

        struct
        {
            __IOM uint32_t RMPSEL     : 2;
            __IM  uint32_t RESERVED1  : 30;
        } OPT_B;
    } ;
} TMR_T;

/**
  * @brief Universal synchronous asynchronous receiver transmitter (USART)
  */

typedef struct
{
    /* Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t UEN        : 1;
            __IOM uint32_t USWMEN     : 1;
            __IOM uint32_t RXEN       : 1;
            __IOM uint32_t TXEN       : 1;
            __IOM uint32_t IDLEIEN    : 1;
            __IOM uint32_t RXBNEIEN   : 1;
            __IOM uint32_t TXCIEN     : 1;
            __IOM uint32_t TXBEIEN    : 1;
            __IOM uint32_t PEIEN      : 1;
            __IOM uint32_t PCFG       : 1;
            __IOM uint32_t PCEN       : 1;
            __IOM uint32_t WUPMCFG    : 1;
            __IOM uint32_t DBLCFG0    : 1;
            __IOM uint32_t RXMUTEEN   : 1;
            __IOM uint32_t CMIEN      : 1;
            __IOM uint32_t OSMCFG     : 1;
            __IOM uint32_t DDLTEN     : 5;
            __IOM uint32_t DLTEN      : 5;
            __IOM uint32_t RXTOIEN    : 1;
            __IOM uint32_t EOBIEN     : 1;
            __IOM uint32_t DBLCFG1    : 1;
            __IM  uint32_t RESERVED2  : 3;
        } CTRL1_B;
    } ;

    /* Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IM  uint32_t RESERVED1  : 4;
            __IOM uint32_t ADDRLEN    : 1;
            __IOM uint32_t LBDLCFG    : 1;
            __IOM uint32_t LBDIEN     : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t LBCPOEN    : 1;
            __IOM uint32_t CPHA       : 1;
            __IOM uint32_t CPOL       : 1;
            __IOM uint32_t CLKEN      : 1;
            __IOM uint32_t STOPCFG    : 2;
            __IOM uint32_t LINMEN     : 1;
            __IOM uint32_t SWAPEN     : 1;
            __IOM uint32_t RXINVEN    : 1;
            __IOM uint32_t TXINVEN    : 1;
            __IOM uint32_t BINVEN     : 1;
            __IOM uint32_t MSBFEN     : 1;
            __IOM uint32_t ABRDEN     : 1;
            __IOM uint32_t ABRDCFG    : 2;
            __IOM uint32_t RXTODEN    : 1;
            __IOM uint32_t ADDRL      : 4;
            __IOM uint32_t ADDRH      : 4;
        } CTRL2_B;
    } ;

    /* Control register 3 */
    union
    {
        __IOM uint32_t CTRL3;

        struct
        {
            __IOM uint32_t ERRIEN     : 1;
            __IOM uint32_t IREN       : 1;
            __IOM uint32_t IRLPEN     : 1;
            __IOM uint32_t HDEN       : 1;
            __IOM uint32_t SCNACKEN   : 1;
            __IOM uint32_t SCEN       : 1;
            __IOM uint32_t DMARXEN    : 1;
            __IOM uint32_t DMATXEN    : 1;
            __IOM uint32_t RTSEN      : 1;
            __IOM uint32_t CTSEN      : 1;
            __IOM uint32_t CTSIEN     : 1;
            __IOM uint32_t SAMCFG     : 1;
            __IOM uint32_t OVRDEDIS   : 1;
            __IOM uint32_t DDISRXEEN  : 1;
            __IOM uint32_t DEN        : 1;
            __IOM uint32_t DPCFG      : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t SCARCCFG   : 3;
            __IOM uint32_t WSIFLGSEL  : 2;
            __IOM uint32_t WSMIEN     : 1;
            __IM  uint32_t RESERVED2  : 9;
        } CTRL3_B;
    } ;

    /* Baud rate register */
    union
    {
        __IOM uint32_t BR;

        struct
        {
            __IOM uint32_t FBR        : 4;
            __IOM uint32_t MBR        : 12;
            __IM  uint32_t RESERVED1  : 16;
        } BR_B;
    } ;

    /* Guard time and prescaler */
    union
    {
        __IOM uint32_t GTPSC;

        struct
        {
            __IOM uint32_t PSC        : 8;
            __IOM uint32_t GRDT       : 8;
            __IM  uint32_t RESERVED1  : 16;
        } GTPSC_B;
    } ;

    /* Receiver timeout register */
    union
    {
        __IOM uint32_t RXTO;

        struct
        {
            __IOM uint32_t RXTO       : 24;
            __IOM uint32_t BLEN       : 8;
        } RXTO_B;
    } ;

    /* Request register */
    union
    {
        __IOM uint32_t REQUEST;

        struct
        {
            __IOM uint32_t ABRDQ      : 1;
            __IOM uint32_t TXBFQ      : 1;
            __IOM uint32_t MUTEQ      : 1;
            __IOM uint32_t RXDFQ      : 1;
            __IOM uint32_t TXDFQ      : 1;
            __IM  uint32_t RESERVED1  : 27;
        } REQUEST_B;
    } ;

    /* Interrupt & status register */
    union
    {
        __IM  uint32_t STS;

        struct
        {
            __IM  uint32_t PEFLG      : 1;
            __IM  uint32_t FEFLG      : 1;
            __IM  uint32_t NEFLG      : 1;
            __IM  uint32_t OVREFLG    : 1;
            __IM  uint32_t IDLEFLG    : 1;
            __IM  uint32_t RXBNEFLG   : 1;
            __IM  uint32_t TXCFLG     : 1;
            __IM  uint32_t TXBEFLG    : 1;
            __IM  uint32_t LBDFLG     : 1;
            __IM  uint32_t CTSFLG     : 1;
            __IM  uint32_t CTSCFG     : 1;
            __IM  uint32_t RXTOFLG    : 1;
            __IM  uint32_t EOBFLG     : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IM  uint32_t ABRDEFLG   : 1;
            __IM  uint32_t ABRDFLG    : 1;
            __IM  uint32_t BSYFLG     : 1;
            __IM  uint32_t CMFLG      : 1;
            __IM  uint32_t TXBFFLG    : 1;
            __IM  uint32_t RXWFMUTE   : 1;
            __IM  uint32_t WSMFLG     : 1;
            __IM  uint32_t TXENACKFLG : 1;
            __IM  uint32_t RXENACKFLG : 1;
            __IM  uint32_t RESERVED2  : 9;
        } STS_B;
    } ;

    /* Interrupt flag clear register */
    union
    {
        __IOM uint32_t INTFCLR;

        struct
        {
            __IOM uint32_t PECLR      : 1;
            __IOM uint32_t FECLR      : 1;
            __IOM uint32_t NECLR      : 1;
            __IOM uint32_t OVRECLR    : 1;
            __IOM uint32_t IDLECLR    : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t TXCCLR     : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t LBDCLR     : 1;
            __IOM uint32_t CTSCLR     : 1;
            __IM  uint32_t RESERVED3  : 1;
            __IOM uint32_t RXTOCLR    : 1;
            __IOM uint32_t EOBCLR     : 1;
            __IM  uint32_t RESERVED4  : 4;
            __IOM uint32_t CMCLR      : 1;
            __IM  uint32_t RESERVED5  : 2;
            __IOM uint32_t WSMCLR     : 1;
            __IM  uint32_t RESERVED6  : 11;
        } INTFCLR_B;
    } ;

    /* Receive data register */
    union
    {
        __IM  uint32_t RXDATA;

        struct
        {
            __IM  uint32_t RXDATA     : 9;
            __IM  uint32_t RESERVED1  : 23;
        } RXDATA_B;
    } ;

    /* Transmit data register */
    union
    {
        __IOM uint32_t TXDATA;

        struct
        {
            __IOM uint32_t TXDATA     : 9;
            __IM  uint32_t RESERVED1  : 23;
        } TXDATA_B;
    } ;
} USART_T;

/**
  * @brief Window watchdog (WWDT)
  */

typedef struct
{
    union
    {
        /* Control register */
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t CNT        : 7;
            __IOM uint32_t WWDTEN     : 1;
            __IM  uint32_t RESERVED1  : 24;
        } CTRL_B;
    } ;

    union
    {
        /* Configuration register */
        __IOM uint32_t CFG;

        struct
        {
            __IOM uint32_t WIN        : 7;
            __IOM uint32_t TBPSC      : 2;
            __IOM uint32_t EWIEN      : 1;
            __IM  uint32_t RESERVED1  : 22;
        } CFG_B;
    } ;

    union
    {
        /* Status register  */
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t EWIFLG     : 1;
            __IM  uint32_t RESERVED1  : 31;
        } STS_B;
    } ;
} WWDT_T;

/**
 * @brief   Universal Serial Bus Device (USB)
 */

typedef union
{
    __IOM uint32_t EP;

    struct
    {
        __IOM uint32_t ADDR           : 4;
        __IOM uint32_t TXSTS          : 2;
        __IOM uint32_t TXDTOG         : 1;
        __IOM uint32_t CTFT           : 1;
        __IOM uint32_t KIND           : 1;
        __IOM uint32_t TYPE           : 2;
        __IOM uint32_t SETUP          : 1;
        __IOM uint32_t RXSTS          : 2;
        __IOM uint32_t RXDTOG         : 1;
        __IOM uint32_t CTFR           : 1;
        __IM  uint32_t RESERVED       : 16;
    } EP_B;
} USB_EP_REG_T;

typedef struct
{
    /* Endpoint */
    USB_EP_REG_T EP[8];

    __IOM uint32_t RESERVED1[8];

    /**
     * @brief   Control register
     */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t FORRST     : 1;
            __IOM uint32_t PWRDOWN    : 1;
            __IOM uint32_t LPWREN     : 1;
            __IOM uint32_t FORSUS     : 1;
            __IOM uint32_t WKUPREQ    : 1;
            __IOM uint32_t L1WKUPREQ  : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t L1STSREQIM : 1;
            __IOM uint32_t ESOFIEN    : 1;
            __IOM uint32_t SOFIEN     : 1;
            __IOM uint32_t RSTIEN     : 1;
            __IOM uint32_t SUSIEN     : 1;
            __IOM uint32_t WKUPIEN    : 1;
            __IOM uint32_t ERRIEN     : 1;
            __IOM uint32_t PMAOUIEN   : 1;
            __IOM uint32_t CTRIEN     : 1;
            __IM  uint32_t RESERVED2  : 16;
        } CTRL_B;
    };

    /**
     * @brief   Interrupt status register
     */
    union
    {
        __IOM uint32_t INTSTS;

        struct
        {
            __IOM uint32_t EPID       : 4;
            __IOM uint32_t DOT        : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t L1STSREQ   : 1;
            __IOM uint32_t ESOFFLG    : 1;
            __IOM uint32_t SOFFLG     : 1;
            __IOM uint32_t RSTREQ     : 1;
            __IOM uint32_t SUSREQ     : 1;
            __IOM uint32_t WUPREQ     : 1;
            __IOM uint32_t ERRFLG     : 1;
            __IOM uint32_t PMOFLG     : 1;
            __IOM uint32_t CTFLG      : 1;
            __IM  uint32_t RESERVED2  : 16;
        } INTSTS_B;
    };

    /**
     * @brief   Frame number register
     */
    union
    {
        __IOM uint32_t FRANUM;

        struct
        {
            __IOM uint32_t FRANUM     : 11;
            __IOM uint32_t LSOFNUM    : 2;
            __IOM uint32_t LOCK       : 1;
            __IOM uint32_t RXDMSTS    : 1;
            __IOM uint32_t RXDPSTS    : 1;
            __IM  uint32_t RESERVED   : 16;
        } FRANUM_B;
    };

    /**
     * @brief   Device address register
     */
    union
    {
        __IOM uint32_t ADDR;

        struct
        {
            __IOM uint32_t ADDR       : 7;
            __IOM uint32_t USBDEN     : 1;
            __IM  uint32_t RESERVED   : 24;
        } ADDR_B;
    };

    /**
     * @brief   Buffer table address register
     */
    union
    {
        __IOM uint32_t BUFFTB;

        struct
        {
            __IM  uint32_t RESERVED1  : 3;
            __IOM uint32_t BUFFTB     : 13;
            __IM  uint32_t RESERVED2  : 16;
        } BUFFTB_B;
    };

    /**
     * @brief   LPM control and status regiter
     */
    union
    {
        __IOM uint32_t LPMCTRLSTS;

        struct
        {
            __IOM uint32_t LPMEN      : 1;
            __IOM uint32_t LPMACKEN   : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t REMWAKE    : 1;
            __IOM uint32_t BESL       : 4;
            __IM  uint32_t RESERVED2  : 24;
        } LPMCTRLSTS_B;
    };

    /**
     * @brief   Battery charging detector regiter
     */
    union
    {
        __IOM uint32_t BCD;

        struct
        {
            __IOM uint32_t BCDEN      : 1;
            __IOM uint32_t DCDEN      : 1;
            __IOM uint32_t PDEN       : 1;
            __IOM uint32_t SDEN       : 1;
            __IOM uint32_t DCDFLG     : 1;
            __IOM uint32_t PDFLG      : 1;
            __IOM uint32_t SDFLG      : 1;
            __IOM uint32_t DMPUDFLG   : 1;
            __IM  uint32_t RESERVED1  : 7;
            __IOM uint32_t DPPUCTRL   : 1;
            __IM  uint32_t RESERVED2  : 16;
        } BCD_B;
    };
} USBD_T;

/**@} end of group Peripheral_registers_structures*/

/** @defgroup Peripheral_memory_map
  @{
*/

/*@} end of group Device_Register*/

/* FMC base address in the alias region */
#define FMC_BASE                ((uint32_t)0x08000000)
/* SRAM base address in the alias region */
#define SRAM_BASE               ((uint32_t)0x20000000)
/* Peripheral base address in the alias region */
#define PERIPH_BASE             ((uint32_t)0x40000000)

/* Peripheral memory map */
#define APBPERIPH_BASE           PERIPH_BASE
#define AHBPERIPH_BASE          (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE         (PERIPH_BASE + 0x08000000)

#define TMR2_BASE               (APBPERIPH_BASE + 0x00000000)
#define TMR3_BASE               (APBPERIPH_BASE + 0x00000400)
#define TMR6_BASE               (APBPERIPH_BASE + 0x00001000)
#define TMR7_BASE               (APBPERIPH_BASE + 0x00001400)
#define TMR14_BASE              (APBPERIPH_BASE + 0x00002000)
#define RTC_BASE                (APBPERIPH_BASE + 0x00002800)
#define WWDT_BASE               (APBPERIPH_BASE + 0x00002C00)
#define IWDT_BASE               (APBPERIPH_BASE + 0x00003000)
#define SPI2_BASE               (APBPERIPH_BASE + 0x00003800)
#define USART2_BASE             (APBPERIPH_BASE + 0x00004400)
#define USART3_BASE             (APBPERIPH_BASE + 0x00004800)
#define USART4_BASE             (APBPERIPH_BASE + 0x00004C00)
#define USART5_BASE             (APBPERIPH_BASE + 0x00005000)
#define I2C1_BASE               (APBPERIPH_BASE + 0x00005400)
#define I2C2_BASE               (APBPERIPH_BASE + 0x00005800)
#define USBD_BASE               (APBPERIPH_BASE + 0x00005C00)
#define CAN_BASE                (APBPERIPH_BASE + 0x00006400)
#define CRS_BASE                (APBPERIPH_BASE + 0x00006C00)
#define PMU_BASE                (APBPERIPH_BASE + 0x00007000)
#define DAC_BASE                (APBPERIPH_BASE + 0x00007400)
#define CEC_BASE                (APBPERIPH_BASE + 0x00007800)

#define SYSCFG_BASE             (APBPERIPH_BASE + 0x00010000)
#define COMP_BASE               (APBPERIPH_BASE + 0x0001001C)
#define EINT_BASE               (APBPERIPH_BASE + 0x00010400)
#define USART6_BASE             (APBPERIPH_BASE + 0x00011400)
#define USART7_BASE             (APBPERIPH_BASE + 0x00011800)
#define USART8_BASE             (APBPERIPH_BASE + 0x00011C00)
#define ADC_BASE                (APBPERIPH_BASE + 0x00012400)
#define TMR1_BASE               (APBPERIPH_BASE + 0x00012C00)
#define SPI1_BASE               (APBPERIPH_BASE + 0x00013000)
#define USART1_BASE             (APBPERIPH_BASE + 0x00013800)
#define TMR15_BASE              (APBPERIPH_BASE + 0x00014000)
#define TMR16_BASE              (APBPERIPH_BASE + 0x00014400)
#define TMR17_BASE              (APBPERIPH_BASE + 0x00014800)
#define DBG_BASE                (APBPERIPH_BASE + 0x00015800)

#define DMA1_BASE               (AHBPERIPH_BASE + 0x00000000)
#define DMA1_CHANNEL_1_BASE     (DMA1_BASE + 0x00000008)
#define DMA1_CHANNEL_2_BASE     (DMA1_BASE + 0x0000001C)
#define DMA1_CHANNEL_3_BASE     (DMA1_BASE + 0x00000030)
#define DMA1_CHANNEL_4_BASE     (DMA1_BASE + 0x00000044)
#define DMA1_CHANNEL_5_BASE     (DMA1_BASE + 0x00000058)
#define DMA1_CHANNEL_6_BASE     (DMA1_BASE + 0x0000006C)
#define DMA1_CHANNEL_7_BASE     (DMA1_BASE + 0x00000080)
#define DMA2_BASE               (AHBPERIPH_BASE + 0x00000400)
#define DMA2_CHANNEL_1_BASE     (DMA2_BASE + 0x00000008)
#define DMA2_CHANNEL_2_BASE     (DMA2_BASE + 0x0000001C)
#define DMA2_CHANNEL_3_BASE     (DMA2_BASE + 0x00000030)
#define DMA2_CHANNEL_4_BASE     (DMA2_BASE + 0x00000044)
#define DMA2_CHANNEL_5_BASE     (DMA2_BASE + 0x00000058)

#define RCM_BASE                (AHBPERIPH_BASE + 0x00001000)
#define FMC_R_BASE              (AHBPERIPH_BASE + 0x00002000)
#define CRC_BASE                (AHBPERIPH_BASE + 0x00003000)
#define TSC_BASE                (AHBPERIPH_BASE + 0x00004000)
#define OB_BASE                        ((uint32_t)0x1FFFF800)

#define GPIOA_BASE              (AHB2PERIPH_BASE + 0x00000000)
#define GPIOB_BASE              (AHB2PERIPH_BASE + 0x00000400)
#define GPIOC_BASE              (AHB2PERIPH_BASE + 0x00000800)
#define GPIOD_BASE              (AHB2PERIPH_BASE + 0x00000C00)
#define GPIOE_BASE              (AHB2PERIPH_BASE + 0x00001000)
#define GPIOF_BASE              (AHB2PERIPH_BASE + 0x00001400)

/**@} end of group Peripheral_memory_map*/

/** @defgroup Peripheral_declaration
  @{
*/

#define ADC                     ((ADC_T*)           ADC_BASE)
#define CAN                     ((CAN_T*)           CAN_BASE)
#define CEC                     ((CEC_T*)           CEC_BASE)
#define CRS                     ((CRS_T*)           CRS_BASE)
#define CRC                     ((CRC_T*)           CRC_BASE)
#define COMP                    ((COMP_T*)          COMP_BASE)
#define DAC                     ((DAC_T*)           DAC_BASE)
#define DBG                     ((DBG_T*)           DBG_BASE)
#define EINT                    ((EINT_T*)          EINT_BASE)
#define FMC                     ((FMC_T*)           FMC_R_BASE)
#define I2C1                    ((I2C_T*)           I2C1_BASE)
#define I2C2                    ((I2C_T*)           I2C2_BASE)
#define IWDT                    ((IWDT_T*)          IWDT_BASE)
#define OB                      ((OB_T*)            OB_BASE)
#define PMU                     ((PMU_T*)           PMU_BASE)
#define RCM                     ((RCM_T*)           RCM_BASE)
#define RTC                     ((RTC_T*)           RTC_BASE)
#define SPI1                    ((SPI_T*)           SPI1_BASE)
#define SPI2                    ((SPI_T*)           SPI2_BASE)
#define SYSCFG                  ((SYSCFG_T*)        SYSCFG_BASE)
#define TSC                     ((TSC_T*)           TSC_BASE)
#define USART1                  ((USART_T*)         USART1_BASE)
#define USART2                  ((USART_T*)         USART2_BASE)
#define USART3                  ((USART_T*)         USART3_BASE)
#define USART4                  ((USART_T*)         USART4_BASE)
#define USART5                  ((USART_T*)         USART5_BASE)
#define USART6                  ((USART_T*)         USART6_BASE)
#define USART7                  ((USART_T*)         USART7_BASE)
#define USART8                  ((USART_T*)         USART8_BASE)
#define USBD                    ((USBD_T*)          USBD_BASE)
#define WWDT                    ((WWDT_T*)          WWDT_BASE)

#define DMA1                    ((DMA_T*)           DMA1_BASE)
#define DMA1_CHANNEL_1          ((DMA_CHANNEL_T*)   DMA1_CHANNEL_1_BASE)
#define DMA1_CHANNEL_2          ((DMA_CHANNEL_T*)   DMA1_CHANNEL_2_BASE)
#define DMA1_CHANNEL_3          ((DMA_CHANNEL_T*)   DMA1_CHANNEL_3_BASE)
#define DMA1_CHANNEL_4          ((DMA_CHANNEL_T*)   DMA1_CHANNEL_4_BASE)
#define DMA1_CHANNEL_5          ((DMA_CHANNEL_T*)   DMA1_CHANNEL_5_BASE)
#define DMA1_CHANNEL_6          ((DMA_CHANNEL_T*)   DMA1_CHANNEL_6_BASE)
#define DMA1_CHANNEL_7          ((DMA_CHANNEL_T*)   DMA1_CHANNEL_7_BASE)
#define DMA2                    ((DMA_T *)          DMA2_BASE)
#define DMA2_CHANNEL_1          ((DMA_CHANNEL_T *)  DMA2_CHANNEL_1_BASE)
#define DMA2_CHANNEL_2          ((DMA_CHANNEL_T *)  DMA2_CHANNEL_2_BASE)
#define DMA2_CHANNEL_3          ((DMA_CHANNEL_T *)  DMA2_CHANNEL_3_BASE)
#define DMA2_CHANNEL_4          ((DMA_CHANNEL_T *)  DMA2_CHANNEL_4_BASE)
#define DMA2_CHANNEL_5          ((DMA_CHANNEL_T *)  DMA2_CHANNEL_5_BASE)

#define GPIOF                   ((GPIO_T*)          GPIOF_BASE)
#define GPIOE                   ((GPIO_T*)          GPIOE_BASE)
#define GPIOD                   ((GPIO_T*)          GPIOD_BASE)
#define GPIOC                   ((GPIO_T*)          GPIOC_BASE)
#define GPIOB                   ((GPIO_T*)          GPIOB_BASE)
#define GPIOA                   ((GPIO_T*)          GPIOA_BASE)

#define TMR1                    ((TMR_T*)           TMR1_BASE)
#define TMR2                    ((TMR_T*)           TMR2_BASE)
#define TMR3                    ((TMR_T*)           TMR3_BASE)
#define TMR6                    ((TMR_T*)           TMR6_BASE)
#define TMR7                    ((TMR_T*)           TMR7_BASE)
#define TMR14                   ((TMR_T*)           TMR14_BASE)
#define TMR15                   ((TMR_T*)           TMR15_BASE)
#define TMR16                   ((TMR_T*)           TMR16_BASE)
#define TMR17                   ((TMR_T*)           TMR17_BASE)

/**@} end of group Peripheral_declaration*/

/** @defgroup Exported_Macros
  @{
*/

/* Define one bit mask */
#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**@} end of group Exported_Macros*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __APM32F0xx_H */

/**@} end of group APM32F0xx */
/**@} end of group CMSIS */
