/*!
 * @file        apm32f10x.h
 *
 * @brief       CMSIS Cortex-M3 Device Peripheral Access Layer Header File.
 *
 * @details     This file contains all the peripheral register's definitions, bits definitions and memory mapping
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
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
#ifndef __APM32F10X_H
#define __APM32F10X_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  APM32F10X_LD: APM32 Low    density devices, the Flash memory density ranges between 16 and 32 Kbytes.
 *  APM32F10X_MD: APM32 Medium density devices, the Flash memory density ranges between 64 and 128 Kbytes.
 *  APM32F10X_HD: APM32 High   density devices, the Flash memory density ranges between 256 and 512 Kbytes.
 *  APM32F10X_CL: APM32 Connectivity line devices, such as APM32F105xx and APM32F107xx serial devices.
 */
#if !defined (APM32F10X_LD)  && !defined (APM32F10X_MD) && !defined (APM32F10X_HD) && !defined (APM32F10X_CL)
#error "Please select a the target APM32F10x device used in your application (in apm32f10x.h file)"
#endif

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32F10x
  * @brief Peripheral Access Layer
  @{
*/

/** @defgroup HSE_Macros
  @{
*/

/**
 * @brief Define Value of the External oscillator in Hz
 */
#ifndef  HSE_VALUE
#ifndef APM32F10X_CL
#define HSE_VALUE                  ((uint32_t)8000000)
#else
#define HSE_VALUE                  ((uint32_t)25000000)
#endif
#endif

/* Time out for HSE start up */
#define HSE_STARTUP_TIMEOUT         ((uint16_t)0x05000)

/* Value of the Internal oscillator in Hz */
#define HSI_VALUE                   ((uint32_t)8000000)

/**@} end of group HSE_Macros */

/** @defgroup APM32F10x_StdPeripheral_Library_Version
  @{
*/

/**
 * @brief APM32F10x Standard Peripheral Library version number
 */
#define __APM32F10X_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __APM32F10X_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __APM32F10X_STDPERIPH_VERSION_SUB2   (0x07) /*!< [15:8]  sub2 version */
#define __APM32F10X_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __APM32F10X_STDPERIPH_VERSION       ( (__APM32F10X_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__APM32F10X_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__APM32F10X_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__APM32F10X_STDPERIPH_VERSION_RC))

/**@} end of group APM32F0xx_StdPeripheral_Library_Version */

/** @defgroup Configuraion_for_CMSIS
  @{
*/

/* APM32 devices does not provide an MPU */
#define __MPU_PRESENT                  0
/* APM32 uses 4 Bits for the Priority Levels  */
#define __NVIC_PRIO_BITS                4
/* Set to 1 if different SysTick Config is used */
#define __Vendor_SysTickConfig          0

/**@} end of group Configuraion_for_CMSIS */

/** @defgroup Peripheral_Enumerations
  @{
*/

/**
 * @brief APM32F10x Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
typedef enum IRQn
{
    /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

    /******  APM32 specific Interrupt Numbers *********************************************************/
    WWDT_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
    PVD_IRQn                    = 1,      /*!< PVD through EINT Line detection Interrupt            */
    TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
    RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
    FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
    RCM_IRQn                    = 5,      /*!< RCM global Interrupt                                 */
    EINT0_IRQn                  = 6,      /*!< EINT Line0 Interrupt                                 */
    EINT1_IRQn                  = 7,      /*!< EINT Line1 Interrupt                                 */
    EINT2_IRQn                  = 8,      /*!< EINT Line2 Interrupt                                 */
    EINT3_IRQn                  = 9,      /*!< EINT Line3 Interrupt                                 */
    EINT4_IRQn                  = 10,     /*!< EINT Line4 Interrupt                                 */
    DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
    DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
    DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
    DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
    DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
    DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
    DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */

#if defined (APM32F10X_LD)
    /*  APM32F10X Low-density devices specific Interrupt Numbers */
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USBD1_HP_CAN1_TX_IRQn       = 19,     /*!< USB Device 1 High Priority or CAN1 TX Interrupts     */
    USBD1_LP_CAN1_RX0_IRQn      = 20,     /*!< USB Device 1 Low Priority or CAN1 RX0 Interrupts     */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EINT9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_IRQn               = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_UP_IRQn                = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_COM_IRQn           = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_IRQn                   = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_IRQn                   = 29,     /*!< TMR3 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    EINT15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EINT Line Interrupt                */
    USBDWakeUp_IRQn             = 42,     /*!< USB Device WakeUp from suspend through EINT Line Interrupt */
    FPU_IRQn                    = 43,     /*!< FPU Global Interrupt                                 */
    QSPI_IRQn                   = 44,     /*!< QSPI Global Interrupt                                */
    USBD2_HP_IRQn               = 45,     /*!< USB Device 2 High Priority                           */
    USBD2_LP_IRQn               = 46      /*!< USB Device 2 Low Priority                            */

#elif defined (APM32F10X_MD)
    /*  APM32F10X Medium-density devices specific Interrupt Numbers */
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USBD1_HP_CAN1_TX_IRQn       = 19,     /*!< USB Device 1 High Priority or CAN1 TX Interrupts     */
    USBD1_LP_CAN1_RX0_IRQn      = 20,     /*!< USB Device 1 Low Priority or CAN1 RX0 Interrupts     */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EINT9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_IRQn               = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_UP_IRQn                = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_COM_IRQn           = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_IRQn                   = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_IRQn                   = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_IRQn                   = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EINT15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EINT Line Interrupt                */
    USBDWakeUp_IRQn             = 42,     /*!< USB Device WakeUp from suspend through EINT Line Interrupt */
    FPU_IRQn                    = 43,     /*!< FPU Global Interrupt                                 */
    QSPI_IRQn                   = 44,     /*!< QSPI Global Interrupt                                */
    USBD2_HP_IRQn               = 45,     /*!< USB Device 2 High Priority                           */
    USBD2_LP_IRQn               = 46      /*!< USB Device 2 Low Priority                            */

#elif defined (APM32F10X_HD)
    /*  APM32F10X High-density devices specific Interrupt Numbers */
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USBD1_HP_CAN1_TX_IRQn       = 19,     /*!< USB Device 1 High Priority or CAN1 TX Interrupts     */
    USBD1_LP_CAN1_RX0_IRQn      = 20,     /*!< USB Device 1 Low Priority or CAN1 RX0 Interrupts     */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EINT9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_IRQn               = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_UP_IRQn                = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_COM_IRQn           = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_IRQn                   = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_IRQn                   = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_IRQn                   = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EINT15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EINT Line Interrupt                */
    USBDWakeUp_IRQn             = 42,     /*!< USB Device WakeUp from suspend through EINT Line Interrupt */
    TMR8_BRK_IRQn               = 43,     /*!< TMR8 Break Interrupt                                 */
    TMR8_UP_IRQn                = 44,     /*!< TMR8 Update Interrupt                                */
    TMR8_TRG_COM_IRQn           = 45,     /*!< TMR8 Trigger and Commutation Interrupt               */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    EMMC_IRQn                   = 48,     /*!< EMMC global Interrupt                                */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TMR5_IRQn                   = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_IRQn                   = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_IRQn                   = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
    USBD2_HP_CAN2_TX_IRQn       = 61,     /*!< USB Device 2 High Priority or CAN2 TX Interrupts     */
    USBD2_LP_CAN2_RX0_IRQn      = 62,     /*!< USB Device 2 Low Priority or CAN2 RX0 Interrupts     */
    CAN2_RX1_IRQn               = 63,     /*!< CAN2 RX1 Interrupts                                  */
    CAN2_SCE_IRQn               = 64,     /*!< CAN2 SCE Interrupts                                  */
#elif defined (APM32F10X_CL)
    /*  APM32F10X Connectivity-line devices specific Interrupt Numbers */
    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupts                                   */
    CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupts                                  */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EINT9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TMR1_BRK_IRQn               = 24,     /*!< TMR1 Break Interrupt                                 */
    TMR1_UP_IRQn                = 25,     /*!< TMR1 Update Interrupt                                */
    TMR1_TRG_COM_IRQn           = 26,     /*!< TMR1 Trigger and Commutation Interrupt               */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                       */
    TMR2_IRQn                   = 28,     /*!< TMR2 global Interrupt                                */
    TMR3_IRQn                   = 29,     /*!< TMR3 global Interrupt                                */
    TMR4_IRQn                   = 30,     /*!< TMR4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EINT15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EINT Line Interrupt                */
    OTG_FS_WKUP_IRQn            = 42,     /*!< USB Device WakeUp from suspend through EINT Line Interrupt */
    TMR5_IRQn                   = 50,     /*!< TMR5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TMR6_IRQn                   = 54,     /*!< TMR6 global Interrupt                                */
    TMR7_IRQn                   = 55,     /*!< TMR7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_IRQn          = 59,     /*!< DMA2 Channel 4 global Interrupt                      */
    DMA2_Channel5_IRQn          = 60,     /*!< DMA2 Channel 5 global Interrupt                      */
    ETH_IRQn                    = 61,     /*!< ETH global Interrupt                                 */
    ETH_WKUP_IRQn               = 62,     /*!< ETH Wake up Interrupt                                */
    CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupts                                   */
    CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupts                                  */
    CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupts                                  */
    CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupts                                  */
    OTG_FS_IRQn                 = 67,     /*!< OTG FS Interrupts                                    */
#endif
} IRQn_Type;

/**@} end of group Peripheral_Enumerations */


/* Includes */
#include "core_cm3.h"
#include "system_apm32f10x.h"
#include <stdint.h>

/** @defgroup Exported_Types
  @{
*/

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;
typedef const int16_t sc16;
typedef const int8_t sc8;

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;
typedef __I int16_t vsc16;
typedef __I int8_t vsc8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;
typedef const uint16_t uc16;
typedef const uint8_t uc8;

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;
typedef __I uint16_t vuc16;
typedef __I uint8_t vuc8;

#ifndef __IM
#define __IM   __I
#endif
#ifndef __OM
#define __OM   __O
#endif
#ifndef __IOM
#define __IOM  __IO
#endif

enum {BIT_RESET, BIT_SET};
enum {RESET, SET};
enum {DISABLE, ENABLE};
enum {ERROR, SUCCESS};

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
 * @brief Reset and clock management unit (RCM)
 */
typedef struct
{
    /* Clock control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t HSIEN           : 1;
            __IM  uint32_t HSIRDYFLG       : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t HSITRIM         : 5;
            __IM  uint32_t HSICAL          : 8;
            __IOM uint32_t HSEEN           : 1;
            __IM  uint32_t HSERDYFLG       : 1;
            __IOM uint32_t HSEBCFG         : 1;
            __IOM uint32_t CSSEN           : 1;
            __IM  uint32_t RESERVED2       : 4;
            __IOM uint32_t PLL1EN          : 1;
            __IM  uint32_t PLL1RDYFLG      : 1;
            __IOM uint32_t PLL2EN          : 1;
            __IM  uint32_t PLL2RDYFLG      : 1;
            __IOM uint32_t PLL3EN          : 1;
            __IM  uint32_t PLL3RDYFLG      : 1;
            __IM  uint32_t RESERVED3       : 2;
        } CTRL_B;
    };

    /* Clock configuration register */
    union
    {
        __IOM uint32_t CFG;

        struct
        {
            __IOM uint32_t SCLKSEL         : 2;
            __IM  uint32_t SCLKSELSTS      : 2;
            __IOM uint32_t AHBPSC          : 4;
            __IOM uint32_t APB1PSC         : 3;
            __IOM uint32_t APB2PSC         : 3;
            __IOM uint32_t ADCPSC          : 2;
            __IOM uint32_t PLL1SRCSEL      : 1;
#ifdef APM32F10X_CL
            __IOM uint32_t PLLPSC1L        : 1;
            __IOM uint32_t PLL1MULCFG      : 4;
            __IOM uint32_t OTGFSPSC        : 2;
            __IOM uint32_t MCOSEL          : 4;
            __IM  uint32_t RESERVED        : 4;
#else
            __IOM uint32_t PLLHSEPSC       : 1;
            __IOM uint32_t PLL1MULCFG      : 4;
            __IOM uint32_t USBDPSC         : 2;
            __IOM uint32_t MCOSEL          : 3;
            __IOM uint32_t FPUPSC          : 1;
            __IOM uint32_t SDRAMPSC        : 2;
            __IM  uint32_t RESERVED        : 2;
#endif
        } CFG_B;
    } ;

    /* Clock interrupt control register */
    union
    {
        __IOM uint32_t INT;

        struct
        {
            __IM  uint32_t LSIRDYFLG       : 1;
            __IM  uint32_t LSERDYFLG       : 1;
            __IM  uint32_t HSIRDYFLG       : 1;
            __IM  uint32_t HSERDYFLG       : 1;
            __IM  uint32_t PLL1RDYFLG      : 1;
            __IM  uint32_t PLL2RDYFLG      : 1;
            __IM  uint32_t PLL3RDYFLG      : 1;
            __IM  uint32_t CSSFLG          : 1;
            __IOM uint32_t LSIRDYEN        : 1;
            __IOM uint32_t LSERDYEN        : 1;
            __IOM uint32_t HSIRDYEN        : 1;
            __IOM uint32_t HSERDYEN        : 1;
            __IOM uint32_t PLL1RDYEN       : 1;
            __IOM uint32_t PLL2RDYEN       : 1;
            __IOM uint32_t PLL3RDYEN       : 1;
            __IM  uint32_t RESERVED1       : 1;
            __OM  uint32_t LSIRDYCLR       : 1;
            __OM  uint32_t LSERDYCLR       : 1;
            __OM  uint32_t HSIRDYCLR       : 1;
            __OM  uint32_t HSERDYCLR       : 1;
            __OM  uint32_t PLL1RDYCLR      : 1;
            __OM  uint32_t PLL2RDYCLR      : 1;
            __OM  uint32_t PLL3RDYCLR      : 1;
            __OM  uint32_t CSSCLR          : 1;
            __IM  uint32_t RESERVED2       : 8;
        } INT_B;
    } ;

    /* APB2 peripheral reset register */
    union
    {
        __IOM uint32_t APB2RST;

        struct
        {
            __IOM uint32_t AFIORST         : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t PARST           : 1;
            __IOM uint32_t PBRST           : 1;
            __IOM uint32_t PCRST           : 1;
            __IOM uint32_t PDRST           : 1;
            __IOM uint32_t PERST           : 1;
            __IOM uint32_t PFRST           : 1;
            __IOM uint32_t PGRST           : 1;
            __IOM uint32_t ADC1RST         : 1;
            __IOM uint32_t ADC2RST         : 1;
            __IOM uint32_t TMR1RST         : 1;
            __IOM uint32_t SPI1RST         : 1;
            __IOM uint32_t TMR8RST         : 1;
            __IOM uint32_t USART1RST       : 1;
            __IOM uint32_t ADC3RST         : 1;
            __IM  uint32_t RESERVED2       : 16;
        } APB2RST_B;
    } ;

    /* APB1 peripheral reset register */
    union
    {
        __IOM uint32_t APB1RST;

        struct
        {
            __IOM uint32_t TMR2RST         : 1;
            __IOM uint32_t TMR3RST         : 1;
            __IOM uint32_t TMR4RST         : 1;
            __IOM uint32_t TMR5RST         : 1;
            __IOM uint32_t TMR6RST         : 1;
            __IOM uint32_t TMR7RST         : 1;
            __IM  uint32_t RESERVED1       : 5;
            __IOM uint32_t WWDTRST         : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t SPI2RST         : 1;
            __IOM uint32_t SPI3RST         : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t USART2RST       : 1;
            __IOM uint32_t USART3RST       : 1;
            __IOM uint32_t UART4RST        : 1;
            __IOM uint32_t UART5RST        : 1;
            __IOM uint32_t I2C1RST         : 1;
            __IOM uint32_t I2C2RST         : 1;
            __IOM uint32_t USBDRST         : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t CAN1RST         : 1;
            __IOM uint32_t CAN2RST         : 1;
            __IOM uint32_t BAKPRST         : 1;
            __IOM uint32_t PMURST          : 1;
            __IOM uint32_t DACRST          : 1;
            __IM  uint32_t RESERVED5       : 2;
        } APB1RST_B;
    } ;

    /* AHB clock enable register */
    union
    {
        __IOM uint32_t AHBCLKEN;

        struct
        {
            __IOM uint32_t DMA1EN          : 1;
            __IOM uint32_t DMA2EN          : 1;
            __IOM uint32_t SRAMEN          : 1;
            __IOM uint32_t FPUEN           : 1;
            __IOM uint32_t FMCEN           : 1;
            __IOM uint32_t QSPIEN          : 1;
            __IOM uint32_t CRCEN           : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t EMMCEN          : 1;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t SDIOEN          : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t OTGFSEN         : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t MACEN           : 1;
            __IOM uint32_t MACTXEN         : 1;
            __IOM uint32_t MACRXEN         : 1;
            __IM  uint32_t RESERVED5       : 15;
        } AHBCLKEN_B;
    } ;

    /* APB2 clock enable register */
    union
    {
        __IOM uint32_t APB2CLKEN;

        struct
        {
            __IOM uint32_t AFIOEN          : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t PAEN            : 1;
            __IOM uint32_t PBEN            : 1;
            __IOM uint32_t PCEN            : 1;
            __IOM uint32_t PDEN            : 1;
            __IOM uint32_t PEEN            : 1;
            __IOM uint32_t PFEN            : 1;
            __IOM uint32_t PGEN            : 1;
            __IOM uint32_t ADC1EN          : 1;
            __IOM uint32_t ADC2EN          : 1;
            __IOM uint32_t TMR1EN          : 1;
            __IOM uint32_t SPI1EN          : 1;
            __IOM uint32_t TMR8EN          : 1;
            __IOM uint32_t USART1EN        : 1;
            __IOM uint32_t ADC3EN          : 1;
            __IM  uint32_t RESERVED2       : 16;
        } APB2CLKEN_B;
    };

    /* APB1 clock enable register */
    union
    {
        __IOM uint32_t APB1CLKEN;

        struct
        {
            __IOM uint32_t TMR2EN          : 1;
            __IOM uint32_t TMR3EN          : 1;
            __IOM uint32_t TMR4EN          : 1;
            __IOM uint32_t TMR5EN          : 1;
            __IOM uint32_t TMR6EN          : 1;
            __IOM uint32_t TMR7EN          : 1;
            __IM  uint32_t RESERVED1       : 5;
            __IOM uint32_t WWDTEN          : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t SPI2EN          : 1;
            __IOM uint32_t SPI3EN          : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t USART2EN        : 1;
            __IOM uint32_t USART3EN        : 1;
            __IOM uint32_t UART4EN         : 1;
            __IOM uint32_t UART5EN         : 1;
            __IOM uint32_t I2C1EN          : 1;
            __IOM uint32_t I2C2EN          : 1;
            __IOM uint32_t USBDEN          : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t CAN1EN          : 1;
            __IOM uint32_t CAN2EN          : 1;
            __IOM uint32_t BAKPEN          : 1;
            __IOM uint32_t PMUEN           : 1;
            __IOM uint32_t DACEN           : 1;
            __IM  uint32_t RESERVED5       : 2;
        } APB1CLKEN_B;
    } ;

    /* Backup domain control register */
    union
    {
        __IOM uint32_t BDCTRL;

        struct
        {
            __IOM uint32_t LSEEN           : 1;
            __IM  uint32_t LSERDYFLG       : 1;
            __IOM uint32_t LSEBCFG         : 1;
            __IM  uint32_t RESERVED1       : 5;
            __IOM uint32_t RTCSRCSEL       : 2;
            __IM  uint32_t RESERVED2       : 5;
            __IOM uint32_t RTCCLKEN        : 1;
            __IOM uint32_t BDRST           : 1;
            __IM  uint32_t RESERVED3       : 15;
        } BDCTRL_B;
    } ;

    /* Control/status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IOM uint32_t LSIEN           : 1;
            __IM  uint32_t LSIRDYFLG       : 1;
            __IM  uint32_t RESERVED1       : 22;
            __IOM uint32_t RSTFLGCLR       : 1;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t NRSTFLG         : 1;
            __IOM uint32_t PODRSTFLG       : 1;
            __IOM uint32_t SWRSTFLG        : 1;
            __IOM uint32_t IWDTRSTFLG      : 1;
            __IOM uint32_t WWDTRSTFLG      : 1;
            __IOM uint32_t LPWRRSTFLG      : 1;
        } CSTS_B;
    } ;

    /* AHB peripheral reset register */
    union
    {
        __IOM uint32_t AHBRST;

        struct
        {
            __IM  uint32_t RESERVED1       : 12;
            __IOM uint32_t OTGFSRST        : 1;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t MACRST          : 1;
            __IM  uint32_t RESERVED3       : 17;
        } AHBRST_B;
    } ;

    /* Clock configuration register2 */
    union
    {
        __IOM uint32_t CFG2;

        struct
        {
            __IOM uint32_t PLLPSC1         : 4;
            __IOM uint32_t PLLPSC2         : 4;
            __IOM uint32_t PLL2MUL         : 4;
            __IOM uint32_t PLL3MUL         : 4;
            __IOM uint32_t PLLPSC1SRC      : 1;
            __IOM uint32_t I2S2SRCSEL      : 1;
            __IOM uint32_t I2S3SRCSEL      : 1;
            __IM  uint32_t RESERVED1       : 13;
        } CFG2_B;
    } ;
} RCM_T;

/**
 * @brief General purpose I/O (GPIO)
 */
typedef struct
{
    /* Port configure register low */
    union
    {
        __IOM uint32_t CFGLOW;

        struct
        {
            __IOM uint32_t MODE0           : 2;
            __IOM uint32_t CFG0            : 2;
            __IOM uint32_t MODE1           : 2;
            __IOM uint32_t CFG1            : 2;
            __IOM uint32_t MODE2           : 2;
            __IOM uint32_t CFG2            : 2;
            __IOM uint32_t MODE3           : 2;
            __IOM uint32_t CFG3            : 2;
            __IOM uint32_t MODE4           : 2;
            __IOM uint32_t CFG4            : 2;
            __IOM uint32_t MODE5           : 2;
            __IOM uint32_t CFG5            : 2;
            __IOM uint32_t MODE6           : 2;
            __IOM uint32_t CFG6            : 2;
            __IOM uint32_t MODE7           : 2;
            __IOM uint32_t CFG7            : 2;
        } CFGLOW_B;
    } ;

    /* Port configure register high */
    union
    {
        __IOM uint32_t CFGHIG;

        struct
        {
            __IOM uint32_t MODE8           : 2;
            __IOM uint32_t CFG8            : 2;
            __IOM uint32_t MODE9           : 2;
            __IOM uint32_t CFG9            : 2;
            __IOM uint32_t MODE10          : 2;
            __IOM uint32_t CFG10           : 2;
            __IOM uint32_t MODE11          : 2;
            __IOM uint32_t CFG11           : 2;
            __IOM uint32_t MODE12          : 2;
            __IOM uint32_t CFG12           : 2;
            __IOM uint32_t MODE13          : 2;
            __IOM uint32_t CFG13           : 2;
            __IOM uint32_t MODE14          : 2;
            __IOM uint32_t CFG14           : 2;
            __IOM uint32_t MODE15          : 2;
            __IOM uint32_t CFG15           : 2;
        } CFGHIG_B;
    } ;

    /* Port data in register */
    union
    {
        __IM  uint32_t IDATA;

        struct
        {
            __IM  uint32_t IDATA0          : 1;
            __IM  uint32_t IDATA1          : 1;
            __IM  uint32_t IDATA2          : 1;
            __IM  uint32_t IDATA3          : 1;
            __IM  uint32_t IDATA4          : 1;
            __IM  uint32_t IDATA5          : 1;
            __IM  uint32_t IDATA6          : 1;
            __IM  uint32_t IDATA7          : 1;
            __IM  uint32_t IDATA8          : 1;
            __IM  uint32_t IDATA9          : 1;
            __IM  uint32_t IDATA10         : 1;
            __IM  uint32_t IDATA11         : 1;
            __IM  uint32_t IDATA12         : 1;
            __IM  uint32_t IDATA13         : 1;
            __IM  uint32_t IDATA14         : 1;
            __IM  uint32_t IDATA15         : 1;
            __IM  uint32_t RESERVED        : 16;
        } IDATA_B;
    } ;

    /* Port data output register */
    union
    {
        __IOM uint32_t ODATA;

        struct
        {
            __IOM uint32_t ODATA0          : 1;
            __IOM uint32_t ODATA1          : 1;
            __IOM uint32_t ODATA2          : 1;
            __IOM uint32_t ODATA3          : 1;
            __IOM uint32_t ODATA4          : 1;
            __IOM uint32_t ODATA5          : 1;
            __IOM uint32_t ODATA6          : 1;
            __IOM uint32_t ODATA7          : 1;
            __IOM uint32_t ODATA8          : 1;
            __IOM uint32_t ODATA9          : 1;
            __IOM uint32_t ODATA10         : 1;
            __IOM uint32_t ODATA11         : 1;
            __IOM uint32_t ODATA12         : 1;
            __IOM uint32_t ODATA13         : 1;
            __IOM uint32_t ODATA14         : 1;
            __IOM uint32_t ODATA15         : 1;
            __IM  uint32_t RESERVED        : 16;
        } ODATA_B;
    } ;

    /* Port bit set/clear register */
    union
    {
        __OM  uint32_t BSC;

        struct
        {
            __OM  uint32_t BS0             : 1;
            __OM  uint32_t BS1             : 1;
            __OM  uint32_t BS2             : 1;
            __OM  uint32_t BS3             : 1;
            __OM  uint32_t BS4             : 1;
            __OM  uint32_t BS5             : 1;
            __OM  uint32_t BS6             : 1;
            __OM  uint32_t BS7             : 1;
            __OM  uint32_t BS8             : 1;
            __OM  uint32_t BS9             : 1;
            __OM  uint32_t BS10            : 1;
            __OM  uint32_t BS11            : 1;
            __OM  uint32_t BS12            : 1;
            __OM  uint32_t BS13            : 1;
            __OM  uint32_t BS14            : 1;
            __OM  uint32_t BS15            : 1;
            __OM  uint32_t BR0             : 1;
            __OM  uint32_t BC1             : 1;
            __OM  uint32_t BC2             : 1;
            __OM  uint32_t BR3             : 1;
            __OM  uint32_t BC4             : 1;
            __OM  uint32_t BC5             : 1;
            __OM  uint32_t BC6             : 1;
            __OM  uint32_t BC7             : 1;
            __OM  uint32_t BC8             : 1;
            __OM  uint32_t BC9             : 1;
            __OM  uint32_t BC10            : 1;
            __OM  uint32_t BC11            : 1;
            __OM  uint32_t BC12            : 1;
            __OM  uint32_t BC13            : 1;
            __OM  uint32_t BC14            : 1;
            __OM  uint32_t BC15            : 1;
        } BSC_B;
    } ;

    /* Port bit clear register */
    union
    {
        __OM  uint32_t BC;

        struct
        {
            __OM  uint32_t BC0             : 1;
            __OM  uint32_t BC1             : 1;
            __OM  uint32_t BC2             : 1;
            __OM  uint32_t BC3             : 1;
            __OM  uint32_t BC4             : 1;
            __OM  uint32_t BC5             : 1;
            __OM  uint32_t BC6             : 1;
            __OM  uint32_t BC7             : 1;
            __OM  uint32_t BC8             : 1;
            __OM  uint32_t BC9             : 1;
            __OM  uint32_t BC10            : 1;
            __OM  uint32_t BC11            : 1;
            __OM  uint32_t BC12            : 1;
            __OM  uint32_t BC13            : 1;
            __OM  uint32_t BC14            : 1;
            __OM  uint32_t BC15            : 1;
            __IM  uint32_t RESERVED        : 16;
        } BC_B;
    } ;

    /* Port configuration lock register */
    union
    {
        __IOM uint32_t LOCK;

        struct
        {
            __IOM uint32_t LOCK0           : 1;
            __IOM uint32_t LOCK1           : 1;
            __IOM uint32_t LOCK2           : 1;
            __IOM uint32_t LOCK3           : 1;
            __IOM uint32_t LOCK4           : 1;
            __IOM uint32_t LOCK5           : 1;
            __IOM uint32_t LOCK6           : 1;
            __IOM uint32_t LOCK7           : 1;
            __IOM uint32_t LOCK8           : 1;
            __IOM uint32_t LOCK9           : 1;
            __IOM uint32_t LOCK10          : 1;
            __IOM uint32_t LOCK11          : 1;
            __IOM uint32_t LOCK12          : 1;
            __IOM uint32_t LOCK13          : 1;
            __IOM uint32_t LOCK14          : 1;
            __IOM uint32_t LOCK15          : 1;
            __IOM uint32_t LOCKKEY         : 1;
            __IM  uint32_t RESERVED        : 16;
        } LOCK_B;
    } ;
} GPIO_T;

/**
 * @brief Alternate function I/O (AFIO)
 */
typedef struct
{
    /* Event control register */
    union
    {
        __IOM uint32_t EVCTRL;

        struct
        {
            __IOM uint32_t PINSEL          : 4;
            __IOM uint32_t PORTSEL         : 3;
            __IOM uint32_t EVOEN           : 1;
            __IM  uint32_t RESERVED        : 24;
        } EVCTRL_B;
    } ;

    /* Alternate function IO remap and Serial wire JTAG configuration register */
    union
    {
        __IOM uint32_t REMAP1;

        struct
        {
            __IOM uint32_t SPI1RMP           : 1;
            __IOM uint32_t I2C1RMP           : 1;
            __IOM uint32_t USART1RMP         : 1;
            __IOM uint32_t USART2RMP         : 1;
            __IOM uint32_t USART3RMP         : 2;
            __IOM uint32_t TMR1RMP           : 2;
            __IOM uint32_t TMR2RMP           : 2;
            __IOM uint32_t TMR3RMP           : 2;
            __IOM uint32_t TMR4RMP           : 1;
            __IOM uint32_t CAN1RMP           : 2;
            __IOM uint32_t PD01RMP           : 1;
            __IOM uint32_t TMR5CH4IRMP       : 1;
#if defined(APM32F10X_CL)
            __IM  uint32_t RESERVED1         : 4;
            __IOM uint32_t MACRMP            : 1;
            __IOM uint32_t CAN2RMP           : 1;
            __IOM uint32_t MACEISEL          : 1;
            __IOM uint32_t SWJCFG            : 3;
            __IM  uint32_t RESERVED2         : 1;
            __IOM uint32_t SPI3RMP           : 1;
            __IOM uint32_t TMR2ITR1RMP       : 1;
            __IOM uint32_t PTPPPSRMP         : 1;
            __IM  uint32_t RESERVED3         : 1;
#else
            __IOM uint32_t ADC1_ETRGINJC_RMP : 1;
            __IOM uint32_t ADC1_ETRGREGC_RMP : 1;
            __IOM uint32_t ADC2_ETRGINJC_RMP : 1;
            __IOM uint32_t ADC2_ETRGREGC_RMP : 1;
            __IM  uint32_t RESERVED1         : 1;
            __IOM uint32_t CAN2RMP           : 1;
            __IM  uint32_t RESERVED2         : 1;
            __OM  uint32_t SWJCFG            : 3;
            __IM  uint32_t RESERVED3         : 5;
#endif
        } REMAP1_B;
    } ;

    /* External interrupt select register1 */
    union
    {
        __IOM uint32_t EINTSEL1;

        struct
        {
            __IOM uint32_t EINT0           : 4;
            __IOM uint32_t EINT1           : 4;
            __IOM uint32_t EINT2           : 4;
            __IOM uint32_t EINT3           : 4;
            __IM  uint32_t RESERVED        : 16;
        } EINTSEL1_B;
    } ;

    /* External interrupt select register2 */
    union
    {
        __IOM uint32_t EINTSEL2;

        struct
        {
            __IOM uint32_t EINT4           : 4;
            __IOM uint32_t EINT5           : 4;
            __IOM uint32_t EINT6           : 4;
            __IOM uint32_t EINT7           : 4;
            __IM  uint32_t RESERVED        : 16;
        } EINTSEL2_B;
    } ;

    /* External interrupt select register3 */
    union
    {
        __IOM uint32_t EINTSEL3;

        struct
        {
            __IOM uint32_t EINT8           : 4;
            __IOM uint32_t EINT9           : 4;
            __IOM uint32_t EINT10          : 4;
            __IOM uint32_t EINT11          : 4;
            __IM  uint32_t RESERVED        : 16;
        } EINTSEL3_B;
    } ;

    /* External interrupt select register4 */
    union
    {
        __IOM uint32_t EINTSEL4;

        struct
        {
            __IOM uint32_t EINT12          : 4;
            __IOM uint32_t EINT13          : 4;
            __IOM uint32_t EINT14          : 4;
            __IOM uint32_t EINT15          : 4;
            __IM  uint32_t RESERVED        : 16;
        } EINTSEL4_B;
    } ;
    __IM  uint32_t  RESERVED;

    /* Alternate function IO remap register2 */
    union
    {
        __IOM uint32_t REMAP2;

        struct
        {
            __IM  uint32_t RESERVED1       : 10;
            __IOM uint32_t EMMCNADV        : 1;
            __IM  uint32_t RESERVED2       : 21;
        } REMAP2_B;
    } ;
} AFIO_T;

/**
 * @brief Universal synchronous asynchronous receiver  transmitter (USART)
 */
typedef struct
{
    /* Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t PEFLG           : 1;
            __IM  uint32_t FEFLG           : 1;
            __IM  uint32_t NEFLG           : 1;
            __IM  uint32_t OVREFLG         : 1;
            __IM  uint32_t IDLEFLG         : 1;
            __IOM uint32_t RXBNEFLG        : 1;
            __IOM uint32_t TXCFLG          : 1;
            __IM  uint32_t TXBEFLG         : 1;
            __IOM uint32_t LBDFLG          : 1;
            __IOM uint32_t CTSFLG          : 1;
            __IM  uint32_t RESERVED        : 22;
        } STS_B;
    } ;

    /* TX Buffer Data Register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA            : 9;
            __IM  uint32_t RESERVED        : 23;
        } DATA_B;
    } ;

    /* Baud rate register */
    union
    {
        __IOM uint32_t BR;

        struct
        {
            __IOM uint32_t FBR             : 4;
            __IOM uint32_t IBR             : 12;
            __IM  uint32_t RESERVED        : 16;
        } BR_B;
    } ;

    /* Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t TXBF            : 1;
            __IOM uint32_t RXMUTEEN        : 1;
            __IOM uint32_t RXEN            : 1;
            __IOM uint32_t TXEN            : 1;
            __IOM uint32_t IDLEIEN         : 1;
            __IOM uint32_t RXBNEIEN        : 1;
            __IOM uint32_t TXCIEN          : 1;
            __IOM uint32_t TXBEIEN         : 1;
            __IOM uint32_t PEIEN           : 1;
            __IOM uint32_t PCFG            : 1;
            __IOM uint32_t PCEN            : 1;
            __IOM uint32_t WUPMCFG         : 1;
            __IOM uint32_t DBLCFG          : 1;
            __IOM uint32_t UEN             : 1;
            __IM  uint32_t RESERVED        : 18;
        } CTRL1_B;
    } ;

    /* Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t ADDR            : 4;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t LBDLCFG         : 1;
            __IOM uint32_t LBDIEN          : 1;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t LBCPOEN         : 1;
            __IOM uint32_t CPHA            : 1;
            __IOM uint32_t CPOL            : 1;
            __IOM uint32_t CLKEN           : 1;
            __IOM uint32_t STOPCFG         : 2;
            __IOM uint32_t LINMEN          : 1;
            __IM  uint32_t RESERVED3       : 17;
        } CTRL2_B;
    } ;

    /* Control register 3 */
    union
    {
        __IOM uint32_t CTRL3;

        struct
        {
            __IOM uint32_t ERRIEN          : 1;
            __IOM uint32_t IREN            : 1;
            __IOM uint32_t IRLPEN          : 1;
            __IOM uint32_t HDEN            : 1;
            __IOM uint32_t SCNACKEN        : 1;
            __IOM uint32_t SCEN            : 1;
            __IOM uint32_t DMARXEN         : 1;
            __IOM uint32_t DMATXEN         : 1;
            __IOM uint32_t RTSEN           : 1;
            __IOM uint32_t CTSEN           : 1;
            __IOM uint32_t CTSIEN          : 1;
            __IM  uint32_t RESERVED        : 21;
        } CTRL3_B;
    } ;

    /* Guard TMRe and divider number register */
    union
    {
        __IOM uint32_t GTPSC;

        struct
        {
            __IOM uint32_t PSC             : 8;
            __IOM uint32_t GRDT            : 8;
            __IM  uint32_t RESERVED        : 16;
        } GTPSC_B;
    } ;
} USART_T;

/**
 * @brief Flash memory controller(FMC)
 */
typedef struct
{
    /* FMC access control register */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t WS              : 3;
            __IOM uint32_t HCAEN           : 1;
            __IOM uint32_t PBEN            : 1;
            __IM  uint32_t PBSF            : 1;
            __IM  uint32_t RESERVED        : 26;
        } CTRL1_B;
    } ;

    /* key register */
    union
    {
        __OM  uint32_t KEY;

        struct
        {
            __OM  uint32_t KEY             : 32;
        } KEY_B;
    } ;

    /* option byte key register */
    union
    {
        __OM  uint32_t OBKEY;

        struct
        {
            __OM  uint32_t OBKEY           : 32;
        } OBKEY_B;
    };

    /* status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t BUSYF           : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t PEF             : 1;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t WPEF            : 1;
            __IOM uint32_t OCF             : 1;
            __IM  uint32_t RESERVED3       : 26;
        } STS_B;
    };

    /* status register */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t PG              : 1;
            __IOM uint32_t PAGEERA         : 1;
            __IOM uint32_t MASSERA         : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t OBP             : 1;
            __IOM uint32_t OBE             : 1;
            __IOM uint32_t STA             : 1;
            __IOM uint32_t LOCK            : 1;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t OBWEN           : 1;
            __IOM uint32_t ERRIE           : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t OCIE            : 1;
            __IM  uint32_t RESERVED4       : 19;
        } CTRL2_B;
    } ;

    /* address register */
    union
    {
        __OM  uint32_t ADDR;

        struct
        {
            __OM  uint32_t ADDR            : 32;
        } ADDR_B;
    };

    __IM  uint32_t  RESERVED;

    /* Option byte register */
    union
    {
        __IOM  uint32_t OBCS;

        struct
        {
            __IM  uint32_t OBE             : 1;
            __IM  uint32_t READPROT        : 1;
            __IM  uint32_t WDTSEL          : 1;
            __IM  uint32_t RSTSTOP         : 1;
            __IM  uint32_t RSTSTDB         : 1;
            __IM  uint32_t UOB             : 5;
            __IM  uint32_t DATA0           : 8;
            __IM  uint32_t DATA1           : 8;
            __IM  uint32_t RESERVED        : 6;
        } OBCS_B;
    };

    /* Write protection register */
    union
    {
        __IM  uint32_t WRTPROT;

        struct
        {
            __IM  uint32_t WRTPORT         : 32;
        } WRTPORT_B;
    };
} FMC_T;

/**
 * @brief  CRC calculation unit (CRC)
 */
typedef struct
{
    /* @brief  DATA register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA            : 32;
        } DATA_B;
    } ;

    /* @brief independent DATA register */
    union
    {
        __IOM  uint32_t INDATA;

        struct
        {
            __IOM uint32_t INDATA          : 8;
            __IM  uint32_t RESERVED        : 24;
        } INDATA_B;
    };

    /* @brief Countrol register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t RST             : 1;
            __IM  uint32_t RESERVED        : 31;
        } CTRL_B;
    };
} CRC_T;

/**
 * @brief Real time clock (RTC)
 */
typedef struct
{
    /* @brief Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t SECIEN          : 1;
            __IOM uint32_t ALRIEN          : 1;
            __IOM uint32_t OVRIEN          : 1;
            __IM  uint32_t RESERVED        : 29;
        } CTRL_B;
    };

    /* @brief Control and State register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IOM uint32_t SECFLG          : 1;
            __IOM uint32_t ALRFLG          : 1;
            __IOM uint32_t OVRFLG          : 1;
            __IOM uint32_t RSYNCFLG        : 1;
            __IOM uint32_t CFGMFLG         : 1;
            __IM  uint32_t OCFLG           : 1;
            __IM  uint32_t RESERVED        : 26;
        } CSTS_B;
    };

    /* @brief RTC predivision loading register High Bit */
    union
    {
        __OM uint32_t PSCRLDH;

        struct
        {
            __OM  uint32_t PSCRLDH         : 4;
            __IM  uint32_t RESERVED        : 28;
        } PSCRLDH_B;
    };

    /* @brief  RTC predivision loading register Low Bit */
    union
    {
        __OM uint32_t PSCRLDL;

        struct
        {
            __OM  uint32_t PSCRLDL         : 16;
            __IM  uint32_t RESERVED        : 16;
        } PSCRLDL_B;
    };

    /* @brief RTC predivider remainder register High Bit */
    union
    {
        __IM uint32_t PSCH;

        struct
        {
            __IM  uint32_t PSCH            : 4;
            __IM  uint32_t RESERVED        : 28;
        } PSCH_B;
    };

    /* @brief RTC predivider remainder register Low Bit */
    union
    {
        __IM uint32_t PSCL;

        struct
        {
            __IM  uint32_t PSCL            : 16;
            __IM  uint32_t RESERVED        : 16;
        } PSCL_B;
    };

    /* @brief RTC count register High Bit */
    union
    {
        __IOM uint32_t CNTH;

        struct
        {
            __IOM uint32_t CNTH            : 16;
            __IM  uint32_t RESERVED        : 16;
        } CNTH_B;
    };

    /* @brief RTC count register Low Bit */
    union
    {
        __IOM uint32_t CNTL;

        struct
        {
            __IOM uint32_t CNTL            : 16;
            __IM  uint32_t RESERVED        : 16;
        } CNTL_B;
    };

    /* @brief RTC alarm clock register High Bit */
    union
    {
        __OM uint32_t ALRH;

        struct
        {
            __OM  uint32_t ALRH            : 16;
            __IM  uint32_t RESERVED        : 16;
        } ALRH_B;
    };

    /* @brief RTC alarm clock register Low Bit */
    union
    {
        __OM uint32_t ALRL;

        struct
        {
            __OM  uint32_t ALRL            : 16;
            __IM  uint32_t RESERVED        : 16;
        } ALRL_B;
    };
} RTC_T;

/**
 * @brief Power Management Unit(PMU)
 */
typedef struct
{
    /* @brief Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t LPDSCFG         : 1;
            __IOM uint32_t PDDSCFG         : 1;
            __IOM uint32_t WUFLGCLR        : 1;
            __IOM uint32_t SBFLGCLR        : 1;
            __IOM uint32_t PVDEN           : 1;
            __IOM uint32_t PLSEL           : 3;
            __IOM uint32_t BPWEN           : 1;
            __IM  uint32_t RESERVED        : 23;
        } CTRL_B;
    };

    /* @brief PMU Status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IM  uint32_t WUEFLG          : 1;
            __IM  uint32_t SBFLG           : 1;
            __IM  uint32_t PVDOFLG         : 1;
            __IM  uint32_t RESERVED        : 5;
            __IOM uint32_t WKUPCFG         : 1;
            __IM  uint32_t RESERVED2       : 23;
        } CSTS_B;
    };
} PMU_T;

/**
 * @brief Backup register (BAKPR)
 */
typedef struct
{
    __IM  uint32_t  RESERVED;

    /* @brief BAKPR DATA1 register */
    union
    {
        __IOM uint32_t DATA1;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA1_B;
    };

    /* @brief BAKPR DATA2 register */
    union
    {
        __IOM uint32_t DATA2;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA2_B;
    };

    /* @brief BAKPR DATA3 register */
    union
    {
        __IOM uint32_t DATA3;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA3_B;
    };

    /* @brief BAKPR DATA4 register */
    union
    {
        __IOM uint32_t DATA4;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA4_B;
    };

    /* @brief BAKPR DATA5 register */
    union
    {
        __IOM uint32_t DATA5;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA5_B;
    };

    /* @brief BAKPR DATA6 register */
    union
    {
        __IOM uint32_t DATA6;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA6_B;
    };

    /* @brief BAKPR DATA7 register */
    union
    {
        __IOM uint32_t DATA7;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA7_B;
    };

    /* @brief BAKPR DATA8 register */
    union
    {
        __IOM uint32_t DATA8;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA8_B;
    };

    /* @brief BAKPR DATA9 register */
    union
    {
        __IOM uint32_t DATA9;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA9_B;
    };

    /* @brief BAKPR DATA10 register */
    union
    {
        __IOM uint32_t DATA10;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA10_B;
    };

    /* @brief BAKPR Clock Calibration register */
    union
    {
        __IOM uint32_t CLKCAL;

        struct
        {
            __IOM uint32_t CALVALUE        : 7;
            __IOM uint32_t CALCOEN         : 1;
            __IOM uint32_t ASPOEN          : 1;
            __IOM uint32_t ASPOSEL         : 1;
            __IM  uint32_t RESERVED        : 22;
        } CLKCAL_B;
    } ;

    /* @brief BAKPR Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t TPFCFG          : 1;
            __IOM uint32_t TPALCFG         : 1;
            __IM  uint32_t RESERVED        : 30;
        } CTRL_B;
    };

    /* @brief BAKPR Control register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __OM  uint32_t TECLR           : 1;
            __OM  uint32_t TICLR           : 1;
            __IOM uint32_t TPIEN           : 1;
            __IM  uint32_t RESERVED1       : 5;
            __IM  uint32_t TEFLG           : 1;
            __IM  uint32_t TIFLG           : 1;
            __IM  uint32_t RESERVED2       : 22;
        } CSTS_B;
    };

    __IM  uint32_t  RESERVED1[2];

    /* @briefBAKPR DATA11 register */
    union
    {
        __IOM uint32_t DATA11;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA11_B;
    };

    /* @briefBAKPR DATA12 register */
    union
    {
        __IOM uint32_t DATA12;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA12_B;
    };

    /* @briefBAKPR DATA13 register */
    union
    {
        __IOM uint32_t DATA13;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA13_B;
    };

    /* @briefBAKPR DATA14 register */
    union
    {
        __IOM uint32_t DATA14;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA14_B;
    };

    /* @briefBAKPR DATA15 register */
    union
    {
        __IOM uint32_t DATA15;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA15_B;
    };

    /* @briefBAKPR DATA16 register */
    union
    {
        __IOM uint32_t DATA16;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA16_B;
    };

    /* @briefBAKPR DATA17 register */
    union
    {
        __IOM uint32_t DATA17;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA17_B;
    };

    /* @briefBAKPR DATA18 register */
    union
    {
        __IOM uint32_t DATA18;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA18_B;
    };

    /* @briefBAKPR DATA19 register */
    union
    {
        __IOM uint32_t DATA19;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA19_B;
    };

    /* @briefBAKPR DATA20 register */
    union
    {
        __IOM uint32_t DATA20;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA20_B;
    };

    /* @briefBAKPR DATA21 register */
    union
    {
        __IOM uint32_t DATA21;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA21_B;
    };

    /* @briefBAKPR DATA22 register */
    union
    {
        __IOM uint32_t DATA22;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA22_B;
    };

    /* @briefBAKPR DATA23 register */
    union
    {
        __IOM uint32_t DATA23;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA23_B;
    };

    /* @briefBAKPR DATA24 register */
    union
    {
        __IOM uint32_t DATA24;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA24_B;
    };

    /* @briefBAKPR DATA25 register */
    union
    {
        __IOM uint32_t DATA25;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA25_B;
    };

    /* @briefBAKPR DATA26 register */
    union
    {
        __IOM uint32_t DATA26;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA26_B;
    };

    /* @briefBAKPR DATA27 register */
    union
    {
        __IOM uint32_t DATA27;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA27_B;
    };

    /* @briefBAKPR DATA28 register */
    union
    {
        __IOM uint32_t DATA28;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA28_B;
    };

    /* @briefBAKPR DATA29 register */
    union
    {
        __IOM uint32_t DATA29;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA29_B;
    };

    /* @briefBAKPR DATA30 register */
    union
    {
        __IOM uint32_t DATA30;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA30_B;
    };

    /* @briefBAKPR DATA31 register */
    union
    {
        __IOM uint32_t DATA31;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA31_B;
    };

    /* @briefBAKPR DATA32 register */
    union
    {
        __IOM uint32_t DATA32;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA32_B;
    };

    /* @briefBAKPR DATA33 register */
    union
    {
        __IOM uint32_t DATA33;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA33_B;
    };

    /* @briefBAKPR DATA34 register */
    union
    {
        __IOM uint32_t DATA34;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA34_B;
    };

    /* @briefBAKPR DATA35 register */
    union
    {
        __IOM uint32_t DATA35;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA35_B;
    };

    /* @briefBAKPR DATA36 register */
    union
    {
        __IOM uint32_t DATA36;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA36_B;
    };

    /* @briefBAKPR DATA37 register */
    union
    {
        __IOM uint32_t DATA37;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA37_B;
    };

    /* @briefBAKPR DATA38 register */
    union
    {
        __IOM uint32_t DATA38;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA38_B;
    };

    /* @briefBAKPR DATA39 register */
    union
    {
        __IOM uint32_t DATA39;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA39_B;
    };

    /* @briefBAKPR DATA40 register */
    union
    {
        __IOM uint32_t DATA40;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA40_B;
    };

    /* @briefBAKPR DATA41 register */
    union
    {
        __IOM uint32_t DATA41;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA41_B;
    };

    /* @briefBAKPR DATA42 register */
    union
    {
        __IOM uint32_t DATA42;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA42_B;
    };
} BAKPR_T;

/**
 * @brief Timer register(TMR)
 */
typedef struct
{
    /* @brief Countrol register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t CNTEN           : 1;
            __IOM uint32_t UD              : 1;
            __IOM uint32_t URSSEL          : 1;
            __IOM uint32_t SPMEN           : 1;
            __IOM uint32_t CNTDIR          : 1;
            __IOM uint32_t CAMSEL          : 2;
            __IOM uint32_t ARPEN           : 1;
            __IOM uint32_t CLKDIV          : 2;
            __IM  uint32_t RESERVED        : 22;
        } CTRL1_B;
    };

    /* @brief Countrol register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t CCPEN           : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t CCUSEL          : 1;
            __IOM uint32_t CCDSEL          : 1;
            __IOM uint32_t MMSEL           : 3;
            __IOM uint32_t TI1SEL          : 1;
            __IOM uint32_t OC1OIS          : 1;
            __IOM uint32_t OC1NOIS         : 1;
            __IOM uint32_t OC2OIS          : 1;
            __IOM uint32_t OC2NOIS         : 1;
            __IOM uint32_t OC3OIS          : 1;
            __IOM uint32_t OC3NOIS         : 1;
            __IOM uint32_t OC4OIS          : 1;
            __IM  uint32_t RESERVED2       : 17;
        } CTRL2_B;
    };

    /* @brief Control register from mode */
    union
    {
        __IOM uint32_t SMCTRL;

        struct
        {
            __IOM uint32_t SMFSEL          : 3;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t TRGSEL          : 3;
            __IOM uint32_t MSMEN           : 1;
            __IOM uint32_t ETFCFG          : 4;
            __IOM uint32_t ETPCFG          : 2;
            __IOM uint32_t ECEN            : 1;
            __IOM uint32_t ETPOL           : 1;
            __IM  uint32_t RESERVED2       : 16;
        } SMCTRL_B;
    };

    /* @brief DMA and Interrupt enable register */
    union
    {
        __IOM  uint32_t DIEN;

        struct
        {
            __IOM uint32_t UIEN            : 1;
            __IOM uint32_t CC1IEN          : 1;
            __IOM uint32_t CC2IEN          : 1;
            __IOM uint32_t CC3IEN          : 1;
            __IOM uint32_t CC4IEN          : 1;
            __IOM uint32_t COMIEN          : 1;
            __IOM uint32_t TRGIEN          : 1;
            __IOM uint32_t BRKIEN          : 1;
            __IOM uint32_t UDIEN           : 1;
            __IOM uint32_t CC1DEN          : 1;
            __IOM uint32_t CC2DEN          : 1;
            __IOM uint32_t CC3DEN          : 1;
            __IOM uint32_t CC4DEN          : 1;
            __IOM uint32_t COMDEN          : 1;
            __IOM uint32_t TRGDEN          : 1;
            __IM  uint32_t RESERVED        : 17;
        } DIEN_B;
    };

    /* @brief Status register */
    union
    {
        __IOM  uint32_t STS;

        struct
        {
            __IOM uint32_t UIFLG           : 1;
            __IOM uint32_t CC1IFLG         : 1;
            __IOM uint32_t CC2IFLG         : 1;
            __IOM uint32_t CC3IFLG         : 1;
            __IOM uint32_t CC4IFLG         : 1;
            __IOM uint32_t COMIFLG         : 1;
            __IOM uint32_t TRGIFLG         : 1;
            __IOM uint32_t BRKIFLG         : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t CC1RCFLG        : 1;
            __IOM uint32_t CC2RCFLG        : 1;
            __IOM uint32_t CC3RCFLG        : 1;
            __IOM uint32_t CC4RCFLG        : 1;
            __IM  uint32_t RESERVED2       : 19;
        } STS_B;
    };

    /* @brief Software controls event generation registers */
    union
    {
        __OM  uint32_t CEG;

        struct
        {
            __OM  uint32_t UEG             : 1;
            __OM  uint32_t CC1EG           : 1;
            __OM  uint32_t CC2EG           : 1;
            __OM  uint32_t CC3EG           : 1;
            __OM  uint32_t CC4EG           : 1;
            __OM  uint32_t COMG            : 1;
            __OM  uint32_t TEG             : 1;
            __OM  uint32_t BEG             : 1;
            __IM  uint32_t RESERVED        : 24;
        } CEG_B;
    };

    /* @brief Capture the compare mode register 1 */
    union
    {
        __IOM uint32_t CCM1;

        /* @brief Compare mode */
        struct
        {
            __IOM uint32_t CC1SEL          : 2;
            __IOM uint32_t OC1FEN          : 1;
            __IOM uint32_t OC1PEN          : 1;
            __IOM uint32_t OC1MOD          : 3;
            __IOM uint32_t OC1CEN          : 1;
            __IOM uint32_t CC2SEL          : 2;
            __IOM uint32_t OC2FEN          : 1;
            __IOM uint32_t OC2PEN          : 1;
            __IOM uint32_t OC2MOD          : 3;
            __IOM uint32_t OC2CEN          : 1;
            __IM  uint32_t RESERVED        : 16;
        } CCM1_COMPARE_B;

        /* @brief Capture mode */
        struct
        {
            __IOM uint32_t CC1SEL          : 2;
            __IOM uint32_t IC1PSC          : 2;
            __IOM uint32_t IC1F            : 4;
            __IOM uint32_t CC2SEL          : 2;
            __IOM uint32_t IC2PSC          : 2;
            __IOM uint32_t IC2F            : 4;
            __IM  uint32_t RESERVED        : 16;
        } CCM1_CAPTURE_B;
    };

    /* @brief Capture the compare mode register 2 */
    union
    {
        __IOM uint32_t CCM2;

        /* @brief Compare mode */
        struct
        {
            __IOM uint32_t CC3SEL          : 2;
            __IOM uint32_t OC3FEN          : 1;
            __IOM uint32_t OC3PEN          : 1;
            __IOM uint32_t OC3MOD          : 3;
            __IOM uint32_t OC3CEN          : 1;
            __IOM uint32_t CC4SEL          : 2;
            __IOM uint32_t OC4FEN          : 1;
            __IOM uint32_t OC4PEN          : 1;
            __IOM uint32_t OC4MOD          : 3;
            __IOM uint32_t OC4CEN          : 1;
            __IM  uint32_t RESERVED        : 16;
        } CCM2_COMPARE_B;

        /* @brief Capture mode */
        struct
        {
            __IOM uint32_t CC3SEL          : 2;
            __IOM uint32_t IC3PSC          : 2;
            __IOM uint32_t IC3F            : 4;
            __IOM uint32_t CC4SEL          : 2;
            __IOM uint32_t IC4PSC          : 2;
            __IOM uint32_t IC4F            : 4;
            __IM  uint32_t RESERVED        : 16;
        } CCM2_CAPTURE_B;
    };

    /* @brief Channel control register */
    union
    {
        __IOM uint32_t CCEN;

        struct
        {
            __IOM uint32_t CC1EN           : 1;
            __IOM uint32_t CC1POL          : 1;
            __IOM uint32_t CC1NEN          : 1;
            __IOM uint32_t CC1NPOL         : 1;
            __IOM uint32_t CC2EN           : 1;
            __IOM uint32_t CC2POL          : 1;
            __IOM uint32_t CC2NEN          : 1;
            __IOM uint32_t CC2NPOL         : 1;
            __IOM uint32_t CC3EN           : 1;
            __IOM uint32_t CC3POL          : 1;
            __IOM uint32_t CC3NEN          : 1;
            __IOM uint32_t CC3NPOL         : 1;
            __IOM uint32_t CC4EN           : 1;
            __IOM uint32_t CC4POL          : 1;
            __IM uint32_t RESERVED         : 18;
        } CCEN_B;
    };

    /* @brief Counting register */
    union
    {
        __IOM uint32_t CNT;

        struct
        {
            __IOM uint32_t CNT             : 16;
            __IM  uint32_t RESERVED        : 16;
        } CNT_B;
    };

    /* @brief Division register */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint32_t PSC             : 16;
            __IM  uint32_t RESERVED        : 16;
        } PSC_B;
    };

    /* @brief Automatic reload register */
    union
    {
        __IOM uint32_t AUTORLD;

        struct
        {
            __IOM uint32_t AUTORLD         : 16;
            __IM  uint32_t RESERVED        : 16;
        } AUTORLD_B;
    };

    /* @brief Repeat count register */
    union
    {
        __IOM uint32_t REPCNT;

        struct
        {
            __IOM uint32_t REPCNT          : 8;
            __IM  uint32_t RESERVED        : 24;
        } REPCNT_B;
    };

    /* @brief Capture comparison register channel 1 */
    union
    {
        __IOM uint32_t CC1;

        struct
        {
            __IOM uint32_t CC1             : 16;
            __IM  uint32_t RESERVED        : 16;
        } CC1_B;
    };

    /* @brief Capture comparison register channel 2 */
    union
    {
        __IOM uint32_t CC2;

        struct
        {
            __IOM uint32_t CC2             : 16;
            __IM  uint32_t RESERVED        : 16;
        } CC2_B;
    };

    /* @brief Capture comparison register channel 3 */
    union
    {
        __IOM uint32_t CC3;

        struct
        {
            __IOM uint32_t CC3             : 16;
            __IM  uint32_t RESERVED        : 16;
        } CC3_B;
    };

    /* @brief Capture comparison register channel 4 */
    union
    {
        __IOM uint32_t CC4;

        struct
        {
            __IOM uint32_t CC4             : 16;
            __IM  uint32_t RESERVED        : 16;
        } CC4_B;
    };

    /* @brief Brake and dead zone registers */
    union
    {
        __IOM uint32_t BDT;

        struct
        {
            __IOM uint32_t DTS             : 8;
            __IOM uint32_t LOCKCFG         : 2;
            __IOM uint32_t IMOS            : 1;
            __IOM uint32_t RMOS            : 1;
            __IOM uint32_t BRKEN           : 1;
            __IOM uint32_t BRKPOL          : 1;
            __IOM uint32_t AOEN            : 1;
            __IOM uint32_t MOEN            : 1;
            __IM  uint32_t RESERVED        : 16;
        } BDT_B;
    };

    /* @brief DMA control register */
    union
    {
        __IOM uint32_t DCTRL;

        struct
        {
            __IOM uint32_t DBADDR          : 5;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t DBLEN           : 5;
            __IM  uint32_t RESERVED2       : 19;
        } DCTRL_B;
    };

    /* @brief Consecutive DMA addresses */
    union
    {
        __IOM uint32_t DMADDR;
        struct
        {
            __IOM uint32_t DMADDR          : 16;
            __IM  uint32_t RESERVED2       : 16;
        } DMADDR_B;
    };
} TMR_T;

/**
 * @brief    Direct Memory Access register(DMA)
 */
typedef struct
{
    /* @brief Interrupt status register */
    union
    {
        __IM uint32_t INTSTS;

        struct
        {
            __IM  uint32_t GINTFLG1        : 1;
            __IM  uint32_t TCFLG1          : 1;
            __IM  uint32_t HTFLG1          : 1;
            __IM  uint32_t TERRFLG1        : 1;
            __IM  uint32_t GINTFLG2        : 1;
            __IM  uint32_t TCFLG2          : 1;
            __IM  uint32_t HTFLG2          : 1;
            __IM  uint32_t TERRFLG2        : 1;
            __IM  uint32_t GINTFLG3        : 1;
            __IM  uint32_t TCFLG3          : 1;
            __IM  uint32_t HTFLG3          : 1;
            __IM  uint32_t TERRFLG3        : 1;
            __IM  uint32_t GINTFLG4        : 1;
            __IM  uint32_t TCFLG4          : 1;
            __IM  uint32_t HTFLG4          : 1;
            __IM  uint32_t TERRFLG4        : 1;
            __IM  uint32_t GINTFLG5        : 1;
            __IM  uint32_t TCFLG5          : 1;
            __IM  uint32_t HTFLG5          : 1;
            __IM  uint32_t TERRFLG5        : 1;
            __IM  uint32_t GINTFLG6        : 1;
            __IM  uint32_t TCFLG6          : 1;
            __IM  uint32_t HTFLG6          : 1;
            __IM  uint32_t TERRFLG6        : 1;
            __IM  uint32_t GINTFLG7        : 1;
            __IM  uint32_t TCFLG7          : 1;
            __IM  uint32_t HTFLG7          : 1;
            __IM  uint32_t TERRFLG7        : 1;
            __IM  uint32_t RESERVED        : 4;
        } INTSTS_B;
    };

    /* @brief Interrupt reset register */
    union
    {
        __OM uint32_t INTFCLR;

        struct
        {
            __OM  uint32_t GINTCLR1        : 1;
            __OM  uint32_t TCCLR1          : 1;
            __OM  uint32_t HTCLR1          : 1;
            __OM  uint32_t TERRCLR1        : 1;
            __OM  uint32_t GINTCLR2        : 1;
            __OM  uint32_t TCCLR2          : 1;
            __OM  uint32_t HTCLR2          : 1;
            __OM  uint32_t TERRCLR2        : 1;
            __OM  uint32_t GINTCLR3        : 1;
            __OM  uint32_t TCCLR3          : 1;
            __OM  uint32_t HTCLR3          : 1;
            __OM  uint32_t TERRCLR3        : 1;
            __OM  uint32_t GINTCLR4        : 1;
            __OM  uint32_t TCCLR4          : 1;
            __OM  uint32_t HTCLR4          : 1;
            __OM  uint32_t TERRCLR4        : 1;
            __OM  uint32_t GINTCLR5        : 1;
            __OM  uint32_t TCCLR5          : 1;
            __OM  uint32_t HTCLR5          : 1;
            __OM  uint32_t TERRCLR5        : 1;
            __OM  uint32_t GINTCLR6        : 1;
            __OM  uint32_t TCCLR6          : 1;
            __OM  uint32_t HTCLR6          : 1;
            __OM  uint32_t TERRCLR6        : 1;
            __OM  uint32_t GINTCLR7        : 1;
            __OM  uint32_t TCCLR7          : 1;
            __OM  uint32_t HTCLR7          : 1;
            __OM  uint32_t TERRCLR7        : 1;
            __IM  uint32_t RESERVED        : 4;
        } INTFCLR_B;
    };
} DMA_T;

/**
 * @brief DMA Channel register
 */
typedef struct
{
    /* @brief DMA Channel setup register */
    union
    {

        __IOM uint32_t CHCFG;

        struct
        {
            __IOM uint32_t CHEN            : 1;
            __IOM uint32_t TCINTEN         : 1;
            __IOM uint32_t HTINTEN         : 1;
            __IOM uint32_t TERRINTEN       : 1;
            __IOM uint32_t DIRCFG          : 1;
            __IOM uint32_t CIRMODE         : 1;
            __IOM uint32_t PERIMODE        : 1;
            __IOM uint32_t MIMODE          : 1;
            __IOM uint32_t PERSIZE         : 2;
            __IOM uint32_t MEMSIZE         : 2;
            __IOM uint32_t CHPL            : 2;
            __IOM uint32_t M2MMODE         : 1;
            __IM  uint32_t RESERVED        : 17;
        } CHCFG_B;
    };

    /* @brief DMA Channel transfer number register*/
    union
    {
        __IOM uint32_t CHNDATA;

        struct
        {
            __IOM uint32_t NDATA           : 16;
            __IM  uint32_t RESERVED        : 16;
        } CHNDATA_B;
    };

    /* @brief DMA Channel peripheral address register */
    union
    {
        __IOM uint32_t CHPADDR;

        struct
        {
            __IOM uint32_t PERADDR         : 32;
        } CHPADDR_B;
    };

    /* @brief DMA Channel memory address register */
    union
    {
        __IOM uint32_t CHMADDR;

        struct
        {
            __IOM uint32_t MEMADDR         : 32;
        } CHMADDR_B;
    };
} DMA_Channel_T;

/**
 * @brief CAN sending mailbox
 */
typedef struct
{
    /* @brief CAN Each mailbox contains the sending mailbox identifier register */
    union
    {
        __IOM uint32_t TXMID;

        struct
        {
            __IOM uint32_t TXMREQ          : 1;
            __IOM uint32_t TXRFREQ         : 1;
            __IOM uint32_t IDTYPESEL       : 1;
            __IOM uint32_t EXTID           : 18;
            __IOM uint32_t STDID           : 11;
        } TXMID_B;
    };

    /* @brief CAN Send the mailbox data length and timestamp register */
    union
    {
        __IOM uint32_t TXDLEN;

        struct
        {
            __IOM uint32_t DLCODE          : 4;
            __IOM uint32_t RESERVED        : 28;
        } TXDLEN_B;
    };

    /* @brief CAN Send mailbox low byte data register */
    union
    {
        __IOM uint32_t TXMDL;

        struct
        {
            __IOM uint32_t DATABYTE0       : 8;
            __IOM uint32_t DATABYTE1       : 8;
            __IOM uint32_t DATABYTE2       : 8;
            __IOM uint32_t DATABYTE3       : 8;
        } TXMDL_B;
    };

    /* @brief CAN Send mailbox High byte data register */
    union
    {
        __IOM uint32_t TXMDH;

        struct
        {
            __IOM uint32_t DATABYTE4       : 8;
            __IOM uint32_t DATABYTE5       : 8;
            __IOM uint32_t DATABYTE6       : 8;
            __IOM uint32_t DATABYTE7       : 8;
        } TXMDH_B;
    };
} CAN_TxMailBox_T;

/**
 * @brief CAN receive mailbox
 */
typedef struct
{
    /* @brief CAN Each mailbox contains the receive mailbox identifier register */
    union
    {
        __IM uint32_t RXMID;

        struct
        {
            __IM  uint32_t RESERVED        : 1;
            __IM  uint32_t RFTXREQ         : 1;
            __IM  uint32_t IDTYPESEL       : 1;
            __IM  uint32_t EXTID           : 18;
            __IM  uint32_t STDID           : 11;
        } RXMID_B;
    };

    /* @brief CAN receive the mailbox data length and timestamp register */
    union
    {
        __IM uint32_t RXDLEN;

        struct
        {
            __IM  uint32_t DLCODE          : 4;
            __IM  uint32_t RESERVED1       : 4;
            __IM  uint32_t FMIDX           : 8;
            __IM  uint32_t RESERVED2       : 16;
        } RXDLEN_B;
    };

    /* @brief CAN receive mailbox low byte data register */
    union
    {
        __IM uint32_t RXMDL;

        struct
        {
            __IM  uint32_t DATABYTE0       : 8;
            __IM  uint32_t DATABYTE1       : 8;
            __IM  uint32_t DATABYTE2       : 8;
            __IM  uint32_t DATABYTE3       : 8;
        } RXMDL_B;
    };

    /* @briefCAN receive mailbox High byte data register */
    union
    {
        __IOM uint32_t RXMDH;

        struct
        {
            __IM  uint32_t DATABYTE4       : 8;
            __IM  uint32_t DATABYTE5       : 8;
            __IM  uint32_t DATABYTE6       : 8;
            __IM  uint32_t DATABYTE7       : 8;
        } RXMDH_B;
    };
} CAN_RxMailBox_T;

/**
 * @brief CAN Filter bank register
 */
typedef struct
{
    /* @brief CAN Filter bank register 1 */
    union
    {
        __IOM uint32_t  FBANK1;

        struct
        {
            __IOM uint32_t FBIT0           : 1;
            __IOM uint32_t FBIT1           : 1;
            __IOM uint32_t FBIT2           : 1;
            __IOM uint32_t FBIT3           : 1;
            __IOM uint32_t FBIT4           : 1;
            __IOM uint32_t FBIT5           : 1;
            __IOM uint32_t FBIT6           : 1;
            __IOM uint32_t FBIT7           : 1;
            __IOM uint32_t FBIT8           : 1;
            __IOM uint32_t FBIT9           : 1;
            __IOM uint32_t FBIT10          : 1;
            __IOM uint32_t FBIT11          : 1;
            __IOM uint32_t FBIT12          : 1;
            __IOM uint32_t FBIT13          : 1;
            __IOM uint32_t FBIT14          : 1;
            __IOM uint32_t FBIT15          : 1;
            __IOM uint32_t FBIT16          : 1;
            __IOM uint32_t FBIT17          : 1;
            __IOM uint32_t FBIT18          : 1;
            __IOM uint32_t FBIT19          : 1;
            __IOM uint32_t FBIT20          : 1;
            __IOM uint32_t FBIT21          : 1;
            __IOM uint32_t FBIT22          : 1;
            __IOM uint32_t FBIT23          : 1;
            __IOM uint32_t FBIT24          : 1;
            __IOM uint32_t FBIT25          : 1;
            __IOM uint32_t FBIT26          : 1;
            __IOM uint32_t FBIT27          : 1;
            __IOM uint32_t FBIT28          : 1;
            __IOM uint32_t FBIT29          : 1;
            __IOM uint32_t FBIT30          : 1;
            __IOM uint32_t FBIT31          : 1;
        } FBANK1_B;
    };

    /* @brief CAN Filter bank register 2 */
    union
    {
        __IOM uint32_t  FBANK2;

        struct
        {
            __IOM uint32_t FBIT0           : 1;
            __IOM uint32_t FBIT1           : 1;
            __IOM uint32_t FBIT2           : 1;
            __IOM uint32_t FBIT3           : 1;
            __IOM uint32_t FBIT4           : 1;
            __IOM uint32_t FBIT5           : 1;
            __IOM uint32_t FBIT6           : 1;
            __IOM uint32_t FBIT7           : 1;
            __IOM uint32_t FBIT8           : 1;
            __IOM uint32_t FBIT9           : 1;
            __IOM uint32_t FBIT10          : 1;
            __IOM uint32_t FBIT11          : 1;
            __IOM uint32_t FBIT12          : 1;
            __IOM uint32_t FBIT13          : 1;
            __IOM uint32_t FBIT14          : 1;
            __IOM uint32_t FBIT15          : 1;
            __IOM uint32_t FBIT16          : 1;
            __IOM uint32_t FBIT17          : 1;
            __IOM uint32_t FBIT18          : 1;
            __IOM uint32_t FBIT19          : 1;
            __IOM uint32_t FBIT20          : 1;
            __IOM uint32_t FBIT21          : 1;
            __IOM uint32_t FBIT22          : 1;
            __IOM uint32_t FBIT23          : 1;
            __IOM uint32_t FBIT24          : 1;
            __IOM uint32_t FBIT25          : 1;
            __IOM uint32_t FBIT26          : 1;
            __IOM uint32_t FBIT27          : 1;
            __IOM uint32_t FBIT28          : 1;
            __IOM uint32_t FBIT29          : 1;
            __IOM uint32_t FBIT30          : 1;
            __IOM uint32_t FBIT31          : 1;
        } FBANK2_B;
    };
} CAN_FilterRegister_T;

/**
 * @brief     Controller Area Network(CAN)
 */
typedef struct
{
    /* @brief CAN Master control register */
    union
    {
        __IOM uint32_t MCTRL;

        struct
        {
            __IOM uint32_t INITREQ         : 1;
            __IOM uint32_t SLEEPREQ        : 1;
            __IOM uint32_t TXFPCFG         : 1;
            __IOM uint32_t RXFLOCK         : 1;
            __IOM uint32_t ARTXMD          : 1;
            __IOM uint32_t AWUPCFG         : 1;
            __IOM uint32_t ALBOFFM         : 1;
            __IM  uint32_t RESERVED1       : 8;
            __IOM uint32_t SWRST           : 1;
            __IOM uint32_t DBGFRZE         : 1;
            __IM  uint32_t RESERVED2       : 15;
        } MCTRL_B;
    };

    /* @brief CAN Master States register */
    union
    {
        __IOM uint32_t MSTS;

        struct
        {
            __IM  uint32_t INITFLG         : 1;
            __IM  uint32_t SLEEPFLG        : 1;
            __IOM uint32_t ERRIFLG         : 1;
            __IOM uint32_t WUPIFLG         : 1;
            __IOM uint32_t SLEEPIFLG       : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IM  uint32_t TXMFLG          : 1;
            __IM  uint32_t RXMFLG          : 1;
            __IM  uint32_t LSAMVALUE       : 1;
            __IM  uint32_t RXSIGL          : 1;
            __IM  uint32_t RESERVED2       : 20;
        } MSTS_B;
    };

    /* @brief CAN Send States register */
    union
    {
        __IOM uint32_t TXSTS;

        struct
        {
            __IOM uint32_t REQCFLG0        : 1;
            __IOM uint32_t TXSUSFLG0       : 1;
            __IOM uint32_t ARBLSTFLG0      : 1;
            __IOM uint32_t TXERRFLG0       : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t ABREQFLG0       : 1;
            __IOM uint32_t REQCFLG1        : 1;
            __IOM uint32_t TXSUSFLG1       : 1;
            __IOM uint32_t ARBLSTFLG1      : 1;
            __IOM uint32_t TXERRFLG1       : 1;
            __IM  uint32_t RESERVED2       : 3;
            __IOM uint32_t ABREQFLG1       : 1;
            __IOM uint32_t REQCFLG2        : 1;
            __IOM uint32_t TXSUSFLG2       : 1;
            __IOM uint32_t ARBLSTFLG2      : 1;
            __IOM uint32_t TXERRFLG2       : 1;
            __IM  uint32_t RESERVED3       : 3;
            __IOM uint32_t ABREQFLG2       : 1;
            __IM  uint32_t EMNUM           : 2;
            __IM  uint32_t TXMEFLG0        : 1;
            __IM  uint32_t TXMEFLG1        : 1;
            __IM  uint32_t TXMEFLG2        : 1;
            __IM  uint32_t LOWESTP0        : 1;
            __IM  uint32_t LOWESTP1        : 1;
            __IM  uint32_t LOWESTP2        : 1;
        } TXSTS_B;
    };

    /* @brief CAN Receive FIFO 0 register */
    union
    {
        __IOM uint32_t RXF0;

        struct
        {
            __IM  uint32_t FMNUM0          : 2;
            __IM  uint32_t RESERVED        : 1;
            __IOM uint32_t FFULLFLG0       : 1;
            __IOM uint32_t FOVRFLG0        : 1;
            __IOM uint32_t RFOM0           : 1;
            __IM  uint32_t RESERVED1       : 26;
        } RXF0_B;
    };

    /* @brief CAN Receive FIFO 1 register */
    union
    {
        __IOM uint32_t RXF1;

        struct
        {
            __IM  uint32_t FMNUM1          : 2;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t FFULLFLG1       : 1;
            __IOM uint32_t FOVRFLG1        : 1;
            __IOM uint32_t RFOM1           : 1;
            __IM  uint32_t RESERVED2       : 26;
        } RXF1_B;
    };

    /* @brief CAN Interrupts register */
    union
    {
        __IOM uint32_t INTEN;

        struct
        {
            __IOM uint32_t TXMEIEN         : 1;
            __IOM uint32_t FMIEN0          : 1;
            __IOM uint32_t FFULLIEN0       : 1;
            __IOM uint32_t FOVRIEN0        : 1;
            __IOM uint32_t FMIEN1          : 1;
            __IOM uint32_t FFULLIEN1       : 1;
            __IOM uint32_t FOVRIEN1        : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t ERRWIEN         : 1;
            __IOM uint32_t ERRPIEN         : 1;
            __IOM uint32_t BOFFIEN         : 1;
            __IOM uint32_t LECIEN          : 1;
            __IM  uint32_t RESERVED2       : 3;
            __IOM uint32_t ERRIEN          : 1;
            __IOM uint32_t WUPIEN          : 1;
            __IOM uint32_t SLEEPIEN        : 1;
            __IM  uint32_t RESERVED3       : 14;
        } INTEN_B;
    };

    /* @brief CAN Error States register */
    union
    {
        __IOM uint32_t ERRSTS;

        struct
        {
            __IM  uint32_t ERRWFLG         : 1;
            __IM  uint32_t ERRPFLG         : 1;
            __IM  uint32_t BOFLG           : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t LERRC           : 3;
            __IM  uint32_t RESERVED2       : 9;
            __IM  uint32_t TXERRCNT        : 8;
            __IM  uint32_t RXERRCNT        : 8;
        } ERRSTS_B;
    };

    /* @brief CAN Bit Time register */
    union
    {
        __IOM uint32_t BITTIM;

        struct
        {
            __IOM uint32_t BRPSC           : 10;
            __IM  uint32_t RESERVED1       : 6;
            __IOM uint32_t TIMSEG1         : 4;
            __IOM uint32_t TIMSEG2         : 3;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t RSYNJW          : 2;
            __IM  uint32_t RESERVED3       : 4;
            __IOM uint32_t LBKMEN          : 1;
            __IOM uint32_t SILMEN          : 1;
        } BITTIM_B;
    };

    __IM uint32_t RESERVED0[88];

    CAN_TxMailBox_T sTxMailBox[3];
    CAN_RxMailBox_T sRxMailBox[2];

    __IM uint32_t RESERVED1[12];

    /* @brief CAN Filter the master control register */
    union
    {
        __IOM uint32_t FCTRL;

        struct
        {
            __IOM uint32_t FINITEN         : 1;
            __IM  uint32_t RESERVED        : 7;
            __IOM uint32_t CAN2BN          : 6;
            __IM  uint32_t RESERVED1       : 18;
        } FCTRL_B;
    };

    /* @brief CAN Filter register */
    union
    {
        __IOM uint32_t FMCFG;

        struct
        {
            __IOM uint32_t FMCFG0          : 1;
            __IOM uint32_t FMCFG1          : 1;
            __IOM uint32_t FMCFG2          : 1;
            __IOM uint32_t FMCFG3          : 1;
            __IOM uint32_t FMCFG4          : 1;
            __IOM uint32_t FMCFG5          : 1;
            __IOM uint32_t FMCFG6          : 1;
            __IOM uint32_t FMCFG7          : 1;
            __IOM uint32_t FMCFG8          : 1;
            __IOM uint32_t FMCFG9          : 1;
            __IOM uint32_t FMCFG10         : 1;
            __IOM uint32_t FMCFG11         : 1;
            __IOM uint32_t FMCFG12         : 1;
            __IOM uint32_t FMCFG13         : 1;
            __IOM uint32_t FMCFG14         : 1;
            __IOM uint32_t FMCFG15         : 1;
            __IOM uint32_t FMCFG16         : 1;
            __IOM uint32_t FMCFG17         : 1;
            __IOM uint32_t FMCFG18         : 1;
            __IOM uint32_t FMCFG19         : 1;
            __IOM uint32_t FMCFG20         : 1;
            __IOM uint32_t FMCFG21         : 1;
            __IOM uint32_t FMCFG22         : 1;
            __IOM uint32_t FMCFG23         : 1;
            __IOM uint32_t FMCFG24         : 1;
            __IOM uint32_t FMCFG25         : 1;
            __IOM uint32_t FMCFG26         : 1;
            __IOM uint32_t FMCFG27         : 1;
            __IM  uint32_t RESERVED        : 4;
        } FMCFG_B;
    };

    __IM uint32_t RESERVED2;

    /* @brief CAN Filter bit scale register */
    union
    {
        __IOM uint32_t FSCFG;

        struct
        {
            __IOM uint32_t FSCFG0          : 1;
            __IOM uint32_t FSCFG1          : 1;
            __IOM uint32_t FSCFG2          : 1;
            __IOM uint32_t FSCFG3          : 1;
            __IOM uint32_t FSCFG4          : 1;
            __IOM uint32_t FSCFG5          : 1;
            __IOM uint32_t FSCFG6          : 1;
            __IOM uint32_t FSCFG7          : 1;
            __IOM uint32_t FSCFG8          : 1;
            __IOM uint32_t FSCFG9          : 1;
            __IOM uint32_t FSCFG10         : 1;
            __IOM uint32_t FSCFG11         : 1;
            __IOM uint32_t FSCFG12         : 1;
            __IOM uint32_t FSCFG13         : 1;
            __IOM uint32_t FSCFG14         : 1;
            __IOM uint32_t FSCFG15         : 1;
            __IOM uint32_t FSCFG16         : 1;
            __IOM uint32_t FSCFG17         : 1;
            __IOM uint32_t FSCFG18         : 1;
            __IOM uint32_t FSCFG19         : 1;
            __IOM uint32_t FSCFG20         : 1;
            __IOM uint32_t FSCFG21         : 1;
            __IOM uint32_t FSCFG22         : 1;
            __IOM uint32_t FSCFG23         : 1;
            __IOM uint32_t FSCFG24         : 1;
            __IOM uint32_t FSCFG25         : 1;
            __IOM uint32_t FSCFG26         : 1;
            __IOM uint32_t FSCFG27         : 1;
            __IM  uint32_t RESERVED        : 4;
        } FSCFG_B;
    };

    __IM uint32_t RESERVED3;

    /* @brief CAN Filter FIFO associated registers */
    union
    {
        __IOM uint32_t FFASS;

        struct
        {
            __IOM uint32_t FFASS0          : 1;
            __IOM uint32_t FFASS1          : 1;
            __IOM uint32_t FFASS2          : 1;
            __IOM uint32_t FFASS3          : 1;
            __IOM uint32_t FFASS4          : 1;
            __IOM uint32_t FFASS5          : 1;
            __IOM uint32_t FFASS6          : 1;
            __IOM uint32_t FFASS7          : 1;
            __IOM uint32_t FFASS8          : 1;
            __IOM uint32_t FFASS9          : 1;
            __IOM uint32_t FFASS10         : 1;
            __IOM uint32_t FFASS11         : 1;
            __IOM uint32_t FFASS12         : 1;
            __IOM uint32_t FFASS13         : 1;
            __IOM uint32_t FFASS14         : 1;
            __IOM uint32_t FFASS15         : 1;
            __IOM uint32_t FFASS16         : 1;
            __IOM uint32_t FFASS17         : 1;
            __IOM uint32_t FFASS18         : 1;
            __IOM uint32_t FFASS19         : 1;
            __IOM uint32_t FFASS20         : 1;
            __IOM uint32_t FFASS21         : 1;
            __IOM uint32_t FFASS22         : 1;
            __IOM uint32_t FFASS23         : 1;
            __IOM uint32_t FFASS24         : 1;
            __IOM uint32_t FFASS25         : 1;
            __IOM uint32_t FFASS26         : 1;
            __IOM uint32_t FFASS27         : 1;
            __IM  uint32_t RESERVED        : 4;
        } FFASS_B;
    };

    __IM uint32_t RESERVED4;

    /* @brief CAN Filter activation register */
    union
    {
        __IOM uint32_t FACT;

        struct
        {
            __IOM uint32_t FACT0           : 1;
            __IOM uint32_t FACT1           : 1;
            __IOM uint32_t FACT2           : 1;
            __IOM uint32_t FACT3           : 1;
            __IOM uint32_t FACT4           : 1;
            __IOM uint32_t FACT5           : 1;
            __IOM uint32_t FACT6           : 1;
            __IOM uint32_t FACT7           : 1;
            __IOM uint32_t FACT8           : 1;
            __IOM uint32_t FACT9           : 1;
            __IOM uint32_t FACT10          : 1;
            __IOM uint32_t FACT11          : 1;
            __IOM uint32_t FACT12          : 1;
            __IOM uint32_t FACT13          : 1;
            __IOM uint32_t FACT14          : 1;
            __IOM uint32_t FACT15          : 1;
            __IOM uint32_t FACT16          : 1;
            __IOM uint32_t FACT17          : 1;
            __IOM uint32_t FACT18          : 1;
            __IOM uint32_t FACT19          : 1;
            __IOM uint32_t FACT20          : 1;
            __IOM uint32_t FACT21          : 1;
            __IOM uint32_t FACT22          : 1;
            __IOM uint32_t FACT23          : 1;
            __IOM uint32_t FACT24          : 1;
            __IOM uint32_t FACT25          : 1;
            __IOM uint32_t FACT26          : 1;
            __IOM uint32_t FACT27          : 1;
            __IM  uint32_t RESERVED        : 4;
        } FACT_B;
    };

    __IM uint32_t RESERVED5[8];

    CAN_FilterRegister_T sFilterRegister[28];

} CAN_T;

/**
 * @brief    I2C register (I2C)
 */
typedef struct
{
    /* @brief Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t I2CEN           : 1;
            __IOM uint32_t SMBEN           : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t SMBTCFG         : 1;
            __IOM uint32_t ARPEN           : 1;
            __IOM uint32_t PECEN           : 1;
            __IOM uint32_t SRBEN           : 1;
            __IOM uint32_t CLKSTRETCHD     : 1;
            __IOM uint32_t START           : 1;
            __IOM uint32_t STOP            : 1;
            __IOM uint32_t ACKEN           : 1;
            __IOM uint32_t ACKPOS          : 1;
            __IOM uint32_t PEC             : 1;
            __IOM uint32_t ALERTEN         : 1;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t SWRST           : 1;
            __IM  uint32_t RESERVED3       : 16;
        } CTRL1_B;
    } ;

    /* @brief Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t CLKFCFG         : 6;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t ERRIEN          : 1;
            __IOM uint32_t EVIEN           : 1;
            __IOM uint32_t BUFIEN          : 1;
            __IOM uint32_t DMAEN           : 1;
            __IOM uint32_t LTCFG           : 1;
            __IM  uint32_t RESERVED2       : 19;
        } CTRL2_B;
    } ;

    /* @brief Slave machine address register 1 */
    union
    {
        __IOM uint32_t SADDR1;

        struct
        {
            __IOM uint32_t ADDR0           : 1;
            __IOM uint32_t ADDR1_7         : 7;
            __IOM uint32_t ADDR8_9         : 2;
            __IM  uint32_t RESERVED1       : 5;
            __IOM uint32_t ADDRLEN         : 1;
            __IM  uint32_t RESERVED2       : 16;
        } SADDR1_B;
    };

    /* @brief Slave machine address register 2 */
    union
    {
        __IOM uint32_t SADDR2;

        struct
        {
            __IOM uint32_t ADDRNUM         : 1;
            __IOM uint32_t ADDR2           : 7;
            __IM  uint32_t RESERVED        : 24;
        } SADDR2_B;
    };

    /* @brief Cache data register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA            : 8;
            __IM  uint32_t RESERVED        : 24;
        } DATA_B;
    };

    /* @brief Status register 1 */
    union
    {
        __IOM uint32_t STS1;

        struct
        {
            __IM  uint32_t STARTFLG        : 1;
            __IM  uint32_t ADDRFLG         : 1;
            __IM  uint32_t BTCFLG          : 1;
            __IM  uint32_t ADDR10FLG       : 1;
            __IM  uint32_t STOPFLG         : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IM  uint32_t RXBNEFLG        : 1;
            __IM  uint32_t TXBEFLG         : 1;
            __IOM uint32_t BERRFLG         : 1;
            __IOM uint32_t ALFLG           : 1;
            __IOM uint32_t AEFLG           : 1;
            __IOM uint32_t OVRURFLG        : 1;
            __IOM uint32_t PECEFLG         : 1;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t TTEFLG          : 1;
            __IOM uint32_t SMBALTFLG       : 1;
            __IM  uint32_t RESERVED3       : 16;
        } STS1_B;
    };

    /* @brief Status register 2 */
    union
    {
        __IOM uint32_t STS2;

        struct
        {
            __IM  uint32_t MSFLG           : 1;
            __IM  uint32_t BUSBSYFLG       : 1;
            __IM  uint32_t TRFLG           : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IM  uint32_t GENCALLFLG      : 1;
            __IM  uint32_t SMBDADDRFLG     : 1;
            __IM  uint32_t SMMHADDR        : 1;
            __IM  uint32_t DUALADDRFLG     : 1;
            __IM  uint32_t PECVALUE        : 8;
            __IM  uint32_t RESERVED2       : 16;
        } STS2_B;
    };

    /* @brief Clock control register */
    union
    {
        __IOM uint32_t CLKCTRL;

        struct
        {
            __IOM uint32_t CLKS            : 12;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t FDUTYCFG        : 1;
            __IOM uint32_t SPEEDCFG        : 1;
            __IM  uint32_t RESERVED2       : 16;
        } CLKCTRL_B;
    };

    /* @brief  Maximum rise time */
    union
    {
        __IOM uint32_t RISETMAX;

        struct
        {
            __IOM uint32_t RISETMAX        : 6;
            __IM  uint32_t RESERVED        : 26;
        } RISETMAX_B;
    };

    __IM uint32_t RESERVED[55];

    /* @brief I2C Switching register */
    union
    {
        __IOM uint32_t I2C_SWITCH;

        struct
        {
            __IOM uint32_t I2C_SWITCH          : 1;
            __IM uint32_t RESERVED1        : 31;
        } SWITCH_B;
    };
} I2C_T;


typedef struct
{
    __IOM uint16_t RDP;
    __IOM uint16_t USER;
    __IOM uint16_t Data0;
    __IOM uint16_t Data1;
    __IOM uint16_t WRP0;
    __IOM uint16_t WRP1;
    __IOM uint16_t WRP2;
    __IOM uint16_t WRP3;
} OB_T;

/**
 * @brief Analog to Digital Converter(ADC)
 */
typedef struct
{

    /* Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t AWDFLG          : 1;
            __IOM uint32_t EOCFLG          : 1;
            __IOM uint32_t INJEOCFLG       : 1;
            __IOM uint32_t INJCSFLG        : 1;
            __IOM uint32_t REGCSFLG        : 1;
            __IM  uint32_t RESERVED        : 27;
        } STS_B;
    };

    /* Control register1*/
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t AWDCHSEL        : 5;
            __IOM uint32_t EOCIEN          : 1;
            __IOM uint32_t AWDIEN          : 1;
            __IOM uint32_t INJEOCIEN       : 1;
            __IOM uint32_t SCANEN          : 1;
            __IOM uint32_t AWDSGLEN        : 1;
            __IOM uint32_t INJGACEN        : 1;
            __IOM uint32_t REGDISCEN       : 1;
            __IOM uint32_t INJDISCEN       : 1;
            __IOM uint32_t DISCNUMCFG      : 3;
            __IOM uint32_t DUALMCFG        : 4;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t INJAWDEN        : 1;
            __IOM uint32_t REGAWDEN        : 1;
            __IM  uint32_t RESERVED2       : 8;
        } CTRL1_B;
    };

    /* Control register2*/
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t ADCEN           : 1;
            __IOM uint32_t CONTCEN         : 1;
            __IOM uint32_t CAL             : 1;
            __IOM uint32_t CALRST          : 1;
            __IM  uint32_t RESERVED1       : 4;
            __IOM uint32_t DMAEN           : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t DALIGNCFG       : 1;
            __IOM uint32_t INJGEXTTRGSEL   : 3;
            __IOM uint32_t INJEXTTRGEN     : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t REGEXTTRGSEL    : 3;
            __IOM uint32_t REGEXTTRGEN     : 1;
            __IOM uint32_t INJSWSC         : 1;
            __IOM uint32_t REGSWSC         : 1;
            __IOM uint32_t TSVREFEN        : 1;
            __IM  uint32_t RESERVED4       : 8;
        } CTRL2_B;
    };

    /* Sample time register1*/
    union
    {
        __IOM uint32_t SMPTIM1;

        struct
        {
            __IOM uint32_t SMPCYCCFG10     : 3;
            __IOM uint32_t SMPCYCCFG11     : 3;
            __IOM uint32_t SMPCYCCFG12     : 3;
            __IOM uint32_t SMPCYCCFG13     : 3;
            __IOM uint32_t SMPCYCCFG14     : 3;
            __IOM uint32_t SMPCYCCFG15     : 3;
            __IOM uint32_t SMPCYCCFG16     : 3;
            __IOM uint32_t SMPCYCCFG17     : 3;
            __IM  uint32_t RESERVED        : 8;
        } SMPTIM1_B;
    };

    /* Sample time register2*/
    union
    {
        __IOM uint32_t SMPTIM2;

        struct
        {
            __IOM uint32_t SMPCYCCFG0      : 3;
            __IOM uint32_t SMPCYCCFG1      : 3;
            __IOM uint32_t SMPCYCCFG2      : 3;
            __IOM uint32_t SMPCYCCFG3      : 3;
            __IOM uint32_t SMPCYCCFG4      : 3;
            __IOM uint32_t SMPCYCCFG5      : 3;
            __IOM uint32_t SMPCYCCFG6      : 3;
            __IOM uint32_t SMPCYCCFG7      : 3;
            __IOM uint32_t SMPCYCCFG8      : 3;
            __IOM uint32_t SMPCYCCFG9      : 3;
            __IM  uint32_t RESERVED        : 2;
        } SMPTIM2_B;
    };

    /* Injected channel Data offset register1*/
    union
    {
        __IOM uint32_t INJDOF1;

        struct
        {
            __IOM  uint32_t INJDOF1        : 12;
            __IM   uint32_t RESERVED       : 20;
        } INJDOF1_B;
    };

    /* Injected channel Data offset register2*/
    union
    {
        __IOM uint32_t INJDOF2;

        struct
        {
            __IOM  uint32_t INJDOF2        : 12;
            __IM   uint32_t RESERVED       : 20;
        } INJDOF2_B;
    };

    /* Injected channel Data offset register3*/
    union
    {
        __IOM uint32_t INJDOF3;

        struct
        {
            __IOM  uint32_t INJDOF3        : 12;
            __IM   uint32_t RESERVED       : 20;
        } INJDOF3_B;
    };

    /* Injected channel Data offset register4*/
    union
    {
        __IOM uint32_t INJDOF4;

        struct
        {
            __IOM  uint32_t INJDOF4        : 12;
            __IM   uint32_t RESERVED       : 20;
        } INJDOF4_B;
    };

    /* Analog watchdog high threshold register*/
    union
    {
        __IOM uint32_t AWDHT;

        struct
        {
            __IOM  uint32_t AWDHT          : 12;
            __IM   uint32_t RESERVED       : 20;
        } AWDHT_B;
    };

    /* Analog watchdog low threshold register*/
    union
    {
        __IOM uint32_t AWDLT;

        struct
        {
            __IOM  uint32_t AWDLT          : 12;
            __IM   uint32_t RESERVED       : 20;
        } AWDLT_B;
    };

    /* Regular channel sequence register1*/
    union
    {
        __IOM uint32_t REGSEQ1;

        struct
        {
            __IOM uint32_t REGSEQC13       : 5;
            __IOM uint32_t REGSEQC14       : 5;
            __IOM uint32_t REGSEQC15       : 5;
            __IOM uint32_t REGSEQC16       : 5;
            __IOM uint32_t REGSEQLEN       : 4;
            __IM  uint32_t RESERVED        : 8;
        } REGSEQ1_B;
    };

    /* Regular channel sequence register2*/
    union
    {
        __IOM uint32_t REGSEQ2;

        struct
        {
            __IOM uint32_t REGSEQC7        : 5;
            __IOM uint32_t REGSEQC8        : 5;
            __IOM uint32_t REGSEQC9        : 5;
            __IOM uint32_t REGSEQC10       : 5;
            __IOM uint32_t REGSEQC11       : 5;
            __IOM uint32_t REGSEQC12       : 5;
            __IM  uint32_t RESERVED        : 2;
        } REGSEQ2_B;
    };

    /* Regular channel sequence register3*/
    union
    {
        __IOM uint32_t REGSEQ3;

        struct
        {
            __IOM uint32_t REGSEQC1        : 5;
            __IOM uint32_t REGSEQC2        : 5;
            __IOM uint32_t REGSEQC3        : 5;
            __IOM uint32_t REGSEQC4        : 5;
            __IOM uint32_t REGSEQC5        : 5;
            __IOM uint32_t REGSEQC6        : 5;
            __IM  uint32_t RESERVED        : 2;
        } REGSEQ3_B;
    };

    /* Injected sequence register*/
    union
    {
        __IOM uint32_t INJSEQ;

        struct
        {
            __IOM uint32_t INJSEQC1        : 5;
            __IOM uint32_t INJSEQC2        : 5;
            __IOM uint32_t INJSEQC3        : 5;
            __IOM uint32_t INJSEQC4        : 5;
            __IOM uint32_t INJSEQLEN       : 2;
            __IM  uint32_t RESERVED        : 10;
        } INJSEQ_B;
    };

    /* Injected Data register1*/
    union
    {
        __IM uint32_t INJDATA1;

        struct
        {
            __IM   uint32_t INJDATA        : 16;
            __IM   uint32_t RESERVED       : 16;
        } INJDATA1_B;
    };

    /* Injected Data register2*/
    union
    {
        __IM uint32_t INJDATA2;

        struct
        {
            __IM   uint32_t INJDATA        : 16;
            __IM   uint32_t RESERVED       : 16;
        } INJDATA2_B;
    };

    /* Injected Data register3*/
    union
    {
        __IM uint32_t INJDATA3;

        struct
        {
            __IM   uint32_t INJDATA        : 16;
            __IM   uint32_t RESERVED       : 16;
        } INJDATA3_B;
    };

    /* Injected Data register4*/
    union
    {
        __IM uint32_t INJDATA4;

        struct
        {
            __IM   uint32_t INJDATA        : 16;
            __IM   uint32_t RESERVED       : 16;
        } INJDATA4_B;
    };

    /* Regular Data register*/
    union
    {
        __IOM uint32_t REGDATA;

        struct
        {
            __IM  uint32_t REGDATA         : 16;
            __IM  uint32_t ADC2DATA        : 16;
        } REGDATA_B;
    };
} ADC_T;

/**
 * @brief External Interrupt(EINT)
 */
typedef struct
{
    /* Interrupt mask register */
    union
    {
        __IOM uint32_t IMASK;

        struct
        {
            __IOM uint32_t IMASK0          : 1;
            __IOM uint32_t IMASK1          : 1;
            __IOM uint32_t IMASK2          : 1;
            __IOM uint32_t IMASK3          : 1;
            __IOM uint32_t IMASK4          : 1;
            __IOM uint32_t IMASK5          : 1;
            __IOM uint32_t IMASK6          : 1;
            __IOM uint32_t IMASK7          : 1;
            __IOM uint32_t IMASK8          : 1;
            __IOM uint32_t IMASK9          : 1;
            __IOM uint32_t IMASK10         : 1;
            __IOM uint32_t IMASK11         : 1;
            __IOM uint32_t IMASK12         : 1;
            __IOM uint32_t IMASK13         : 1;
            __IOM uint32_t IMASK14         : 1;
            __IOM uint32_t IMASK15         : 1;
            __IOM uint32_t IMASK16         : 1;
            __IOM uint32_t IMASK17         : 1;
            __IOM uint32_t IMASK18         : 1;
            __IM  uint32_t RESERVED        : 12;
        } IMASK_B;
    };

    /* Event mask register */
    union
    {
        __IOM uint32_t EMASK;

        struct
        {
            __IOM uint32_t EMASK0          : 1;
            __IOM uint32_t EMASK1          : 1;
            __IOM uint32_t EMASK2          : 1;
            __IOM uint32_t EMASK3          : 1;
            __IOM uint32_t EMASK4          : 1;
            __IOM uint32_t EMASK5          : 1;
            __IOM uint32_t EMASK6          : 1;
            __IOM uint32_t EMASK7          : 1;
            __IOM uint32_t EMASK8          : 1;
            __IOM uint32_t EMASK9          : 1;
            __IOM uint32_t EMASK10         : 1;
            __IOM uint32_t EMASK11         : 1;
            __IOM uint32_t EMASK12         : 1;
            __IOM uint32_t EMASK13         : 1;
            __IOM uint32_t EMASK14         : 1;
            __IOM uint32_t EMASK15         : 1;
            __IOM uint32_t EMASK16         : 1;
            __IOM uint32_t EMASK17         : 1;
            __IOM uint32_t EMASK18         : 1;
            __IM  uint32_t RESERVED        : 12;
        } EEN_B;
    };

    /* Rising Trigger Event Enable register */
    union
    {
        __IOM uint32_t RTEN;

        struct
        {
            __IOM uint32_t RTEN0           : 1;
            __IOM uint32_t RTEN1           : 1;
            __IOM uint32_t RTEN2           : 1;
            __IOM uint32_t RTEN3           : 1;
            __IOM uint32_t RTEN4           : 1;
            __IOM uint32_t RTEN5           : 1;
            __IOM uint32_t RTEN6           : 1;
            __IOM uint32_t RTEN7           : 1;
            __IOM uint32_t RTEN8           : 1;
            __IOM uint32_t RTEN9           : 1;
            __IOM uint32_t RTEN10          : 1;
            __IOM uint32_t RTEN11          : 1;
            __IOM uint32_t RTEN12          : 1;
            __IOM uint32_t RTEN13          : 1;
            __IOM uint32_t RTEN14          : 1;
            __IOM uint32_t RTEN15          : 1;
            __IOM uint32_t RTEN16          : 1;
            __IOM uint32_t RTEN17          : 1;
            __IOM uint32_t RTEN18          : 1;
            __IM  uint32_t RESERVED        : 12;
        } RTEN_B;
    };

    /* Falling Trigger Event Enable register */
    union
    {
        __IOM uint32_t FTEN;

        struct
        {
            __IOM uint32_t FTEN0           : 1;
            __IOM uint32_t FTEN1           : 1;
            __IOM uint32_t FTEN2           : 1;
            __IOM uint32_t FTEN3           : 1;
            __IOM uint32_t FTEN4           : 1;
            __IOM uint32_t FTEN5           : 1;
            __IOM uint32_t FTEN6           : 1;
            __IOM uint32_t FTEN7           : 1;
            __IOM uint32_t FTEN8           : 1;
            __IOM uint32_t FTEN9           : 1;
            __IOM uint32_t FTEN10          : 1;
            __IOM uint32_t FTEN11          : 1;
            __IOM uint32_t FTEN12          : 1;
            __IOM uint32_t FTEN13          : 1;
            __IOM uint32_t FTEN14          : 1;
            __IOM uint32_t FTEN15          : 1;
            __IOM uint32_t FTEN16          : 1;
            __IOM uint32_t FTEN17          : 1;
            __IOM uint32_t FTEN18          : 1;
            __IM  uint32_t RESERVED        : 12;
        } FTEN_B;
    };

    /* Software Interrupt Enable register */
    union
    {
        __IOM uint32_t SWINTE;

        struct
        {
            __IOM uint32_t SWINTE0         : 1;
            __IOM uint32_t SWINTE1         : 1;
            __IOM uint32_t SWINTE2         : 1;
            __IOM uint32_t SWINTE3         : 1;
            __IOM uint32_t SWINTE4         : 1;
            __IOM uint32_t SWINTE5         : 1;
            __IOM uint32_t SWINTE6         : 1;
            __IOM uint32_t SWINTE7         : 1;
            __IOM uint32_t SWINTE8         : 1;
            __IOM uint32_t SWINTE9         : 1;
            __IOM uint32_t SWINTE10        : 1;
            __IOM uint32_t SWINTE11        : 1;
            __IOM uint32_t SWINTE12        : 1;
            __IOM uint32_t SWINTE13        : 1;
            __IOM uint32_t SWINTE14        : 1;
            __IOM uint32_t SWINTE15        : 1;
            __IOM uint32_t SWINTE16        : 1;
            __IOM uint32_t SWINTE17        : 1;
            __IOM uint32_t SWINTE18        : 1;
            __IM  uint32_t RESERVED        : 12;
        } SWINTE_B;
    };

    /* Interrupt Flag Enable register */
    union
    {
        __IOM uint32_t IPEND;

        struct
        {
            __IOM uint32_t IPEND0          : 1;
            __IOM uint32_t IPEND1          : 1;
            __IOM uint32_t IPEND2          : 1;
            __IOM uint32_t IPEND3          : 1;
            __IOM uint32_t IPEND4          : 1;
            __IOM uint32_t IPEND5          : 1;
            __IOM uint32_t IPEND6          : 1;
            __IOM uint32_t IPEND7          : 1;
            __IOM uint32_t IPEND8          : 1;
            __IOM uint32_t IPEND9          : 1;
            __IOM uint32_t IPEND10         : 1;
            __IOM uint32_t IPEND11         : 1;
            __IOM uint32_t IPEND12         : 1;
            __IOM uint32_t IPEND13         : 1;
            __IOM uint32_t IPEND14         : 1;
            __IOM uint32_t IPEND15         : 1;
            __IOM uint32_t IPEND16         : 1;
            __IOM uint32_t IPEND17         : 1;
            __IOM uint32_t IPEND18         : 1;
            __IM  uint32_t RESERVED        : 12;
        } IF_B;
    };
} EINT_T;

/**
 * @brief Independent watchdog(IWDT)
 */
typedef struct
{

    /* Keyword register */
    union
    {
        __OM uint32_t KEY;

        struct
        {
            __OM  uint32_t KEY             : 16;
            __IM  uint32_t RESERVED        : 16;
        } KEY_B;
    };

    /* Frequency Divider register */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint32_t PSC             : 3;
            __IM  uint32_t RESERVED        : 29;
        } DIV_B;
    };

    /* Reload values register */
    union
    {
        __IOM uint32_t CNTRLD;

        struct
        {
            __IOM uint32_t CNTRLD          : 12;
            __IM  uint32_t RESERVED        : 20;
        } CNTRLD_B;
    };

    /* Status register */
    union
    {
        __IM uint32_t STS;

        struct
        {
            __IM  uint32_t PSCUFLG         : 1;
            __IM  uint32_t CNTUFLG         : 1;
            __IM  uint32_t RESERVED        : 30;
        } STS_B;
    };
} IWDT_T;

/**
 * @brief Serial peripheral interface(SPI)
 */
typedef struct
{
    /* Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t CPHA            : 1;
            __IOM uint32_t CPOL            : 1;
            __IOM uint32_t MSMCFG          : 1;
            __IOM uint32_t BRSEL           : 3;
            __IOM uint32_t SPIEN           : 1;
            __IOM uint32_t LSBSEL          : 1;
            __IOM uint32_t ISSEL           : 1;
            __IOM uint32_t SSEN            : 1;
            __IOM uint32_t RXOMEN          : 1;
            __IOM uint32_t DFLSEL          : 1;
            __IOM uint32_t CRCNXT          : 1;
            __IOM uint32_t CRCEN           : 1;
            __IOM uint32_t BMOEN           : 1;
            __IOM uint32_t BMEN            : 1;
            __IM  uint32_t RESERVED        : 16;
        } CTRL1_B;
    };

    /* Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t RXDEN           : 1;
            __IOM uint32_t TXDEN           : 1;
            __IOM uint32_t SSOEN           : 1;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t ERRIEN          : 1;
            __IOM uint32_t RXBNEIEN        : 1;
            __IOM uint32_t TXBEIEN         : 1;
            __IM  uint32_t RESERVED2       : 24;
        } CTRL2_B;
    };

    /* Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t RXBNEFLG        : 1;
            __IM  uint32_t TXBEFLG         : 1;
            __IM  uint32_t SCHDIR          : 1;
            __IM  uint32_t UDRFLG          : 1;
            __IOM uint32_t CRCEFLG         : 1;
            __IM  uint32_t MEFLG           : 1;
            __IM  uint32_t OVRFLG          : 1;
            __IM  uint32_t BSYFLG          : 1;
            __IM  uint32_t RESERVED        : 24;
        } STS_B;
    };

    /* Data register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA_B;
    };

    /* CRC polynomial register */
    union
    {
        __IOM uint32_t CRCPOLY;

        struct
        {
            __IOM uint32_t CRCPOLY         : 16;
            __IM  uint32_t RESERVED        : 16;
        } CRCPOLY_B;
    };

    /* Receive CRC register */
    union
    {
        __IM uint32_t RXCRC;

        struct
        {
            __IM  uint32_t RXCRC           : 16;
            __IM  uint32_t RESERVED        : 16;
        } RXCRC_B;
    };

    /* Transmit CRC register */
    union
    {
        __IM uint32_t TXCRC;

        struct
        {
            __IM  uint32_t TXCRC           : 16;
            __IM  uint32_t RESERVED        : 16;
        } TXCRC_B;
    };

    /* Transmit I2S CTRL register */
    union
    {
        __IOM uint32_t I2SCFG;

        struct
        {
            __IOM uint32_t CHLEN           : 1;
            __IOM uint32_t DATLEN          : 2;
            __IOM uint32_t CPOL            : 1;
            __IOM uint32_t I2SSSEL         : 2;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t PFSSEL          : 1;
            __IOM uint32_t I2SMOD          : 2;
            __IOM uint32_t I2SEN           : 1;
            __IOM uint32_t MODESEL         : 1;
            __IM  uint32_t RESERVED2       : 20;
        } I2SCFG_B;
    };

    /* Transmit I2S DIV register */
    union
    {
        __IOM uint32_t I2SPSC;

        struct
        {
            __IOM uint32_t I2SPSC          : 8;
            __IOM uint32_t ODDPSC          : 1;
            __IOM uint32_t MCIEN           : 1;
            __IM  uint32_t RESERVED1       : 22;
        } I2SPSC_B;
    };
} SPI_T;

/**
 * @brief Window watchdog (WWDT)
 */
typedef struct
{

    /* Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t CNT             : 7;
            __IOM uint32_t WWDTEN          : 1;
            __IM  uint32_t RESERVED        : 24;
        } CTRL_B;
    };

    /* Configure register */
    union
    {
        __IOM uint32_t CFG;

        struct
        {
            __IOM uint32_t WIN             : 7;
            __IOM uint32_t TBPSC           : 2;
            __IOM uint32_t EWIEN           : 1;
            __IM  uint32_t RESERVED        : 22;
        } CFG_B;
    };

    /* Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t EWIFLG          : 1;
            __IM  uint32_t RESERVED        : 31;
        } STS_B;
    };
} WWDT_T;

/**
 * @brief Secure digital input/output interface (SDIO)
 */
typedef struct
{
    /* Power control register */
    union
    {
        __IOM uint32_t PWRCTRL;

        struct
        {
            __IOM  uint32_t PWRCTRL        : 2;
            __IM  uint32_t RESERVED        : 30;
        } PWRCTRL_B;
    };

    /* Clock control register */
    union
    {
        __IOM uint32_t CLKCTRL;

        struct
        {
            __IOM uint32_t CLKDIV          : 8;
            __IOM uint32_t CLKEN           : 1;
            __IOM uint32_t PWRSAV          : 1;
            __IOM uint32_t BYPASSEN        : 1;
            __IOM uint32_t WBSEL           : 2;
            __IOM uint32_t DEPSEL          : 1;
            __IOM uint32_t HFCEN           : 1;
            __IM  uint32_t RESERVED        : 17;
        } CLKCTRL_B;
    };

    /* Argument register */
    union
    {
        __IOM uint32_t ARG;

        struct
        {
            __IOM  uint32_t CMDARG         : 32;
        } ARG_B;
    };

    /* Command register */
    union
    {
        __IOM uint32_t CMD;

        struct
        {
            __IOM uint32_t CMDINDEX        : 6;
            __IOM uint32_t WAITRES         : 2;
            __IOM uint32_t WAITINT         : 1;
            __IOM uint32_t WENDDATA        : 1;
            __IOM uint32_t CPSMEN          : 1;
            __IOM uint32_t SDIOSC          : 1;
            __IOM uint32_t CMDCPEN         : 1;
            __IOM uint32_t INTEN           : 1;
            __IOM uint32_t ATACMD          : 1;
            __IM  uint32_t RESERVED        : 17;
        } CMD_B;
    };

    /* Command response register */
    union
    {
        __IM uint32_t CMDRES;

        struct
        {
            __IM  uint32_t CMDRES          : 6;
            __IM  uint32_t RESERVED        : 26;
        } CMDRES_B;
    };

    /* SDIO response register1 */
    union
    {
        __IM uint32_t RES1;

        struct
        {
            __IM  uint32_t CARDSTS1        : 32;
        } RES1_B;
    };

    /* SDIO response register2 */
    union
    {
        __IM uint32_t RES2;

        struct
        {
            __IM  uint32_t CARDSTS2        : 32;
        } RES2_B;
    };

    /* SDIO response register3 */
    union
    {
        __IM uint32_t RES3;

        struct
        {
            __IM  uint32_t CARDSTS3        : 32;
        } RES3_B;
    };

    /* SDIO response register4 */
    union
    {
        __IM uint32_t RES4;

        struct
        {
            __IM  uint32_t CARDSTS4        : 32;
        } RES4_B;
    };

    /* Data timer register */
    union
    {
        __IOM uint32_t DATATIME;

        struct
        {
            __IOM  uint32_t DATATIME       : 32;
        } DTMR_B;
    };

    /* Data length register */
    union
    {
        __IOM uint32_t DATALEN;

        struct
        {
            __IOM uint32_t DATALEN         : 25;
            __IM  uint32_t RESERVED        : 7;
        } DLEN_B;
    };

    /* Data control register */
    union
    {
        __IOM uint32_t DCTRL;

        struct
        {
            __IOM uint32_t DTEN            : 1;
            __IOM uint32_t DTDRCFG         : 1;
            __IOM uint32_t DTSEL           : 1;
            __IOM uint32_t DMAEN           : 1;
            __IOM uint32_t DBSIZE          : 4;
            __IOM uint32_t RWSTR           : 1;
            __IOM uint32_t RWSTOP          : 1;
            __IOM uint32_t RDWAIT          : 1;
            __IOM uint32_t SDIOF           : 1;
            __IM  uint32_t RESERVED        : 20;
        } DCTRL_B;
    };

    /* Data count register */
    union
    {
        __IM uint32_t DCNT;

        struct
        {
            __IM  uint32_t DATACNT         : 25;
            __IM  uint32_t RESERVED        : 7;
        } DCNT_B;
    };

    /* SDIO status register */
    union
    {
        __IM uint32_t STS;

        struct
        {
            __IM  uint32_t COMRESP         : 1;
            __IM  uint32_t DBDR            : 1;
            __IM  uint32_t CMDRESTO        : 1;
            __IM  uint32_t DATATO          : 1;
            __IM  uint32_t TXUDRER         : 1;
            __IM  uint32_t RXOVRER         : 1;
            __IM  uint32_t CMDRES          : 1;
            __IM  uint32_t CMDSENT         : 1;
            __IM  uint32_t DATAEND         : 1;
            __IM  uint32_t SBE             : 1;
            __IM  uint32_t DBCP            : 1;
            __IM  uint32_t CMDACT          : 1;
            __IM  uint32_t TXACT           : 1;
            __IM  uint32_t RXACT           : 1;
            __IM  uint32_t TXFHF           : 1;
            __IM  uint32_t RXFHF           : 1;
            __IM  uint32_t TXFF            : 1;
            __IM  uint32_t RXFF            : 1;
            __IM  uint32_t TXFE            : 1;
            __IM  uint32_t RXFE            : 1;
            __IM  uint32_t TXDA            : 1;
            __IM  uint32_t RXDA            : 1;
            __IM  uint32_t SDIOINT         : 1;
            __IM  uint32_t ATAEND          : 1;
            __IM  uint32_t RESERVED        : 8;
        } STS_B;
    };

    /* SDIO interrupt clear register */
    union
    {
        __IOM uint32_t ICF;

        struct
        {
            __IOM uint32_t DBCE            : 1;
            __IOM uint32_t CRCE            : 1;
            __IOM uint32_t CRTO            : 1;
            __IOM uint32_t DTO             : 1;
            __IOM uint32_t TXFUE           : 1;
            __IOM uint32_t RXFOE           : 1;
            __IOM uint32_t CMDRES          : 1;
            __IOM uint32_t CMDSENT         : 1;
            __IOM uint32_t DATAEND         : 1;
            __IOM uint32_t SBE             : 1;
            __IOM uint32_t DBCP            : 1;
            __IM  uint32_t RESERVED1       : 11;
            __IOM uint32_t SDIOIT          : 1;
            __IOM uint32_t ATAEND          : 1;
            __IM  uint32_t RESERVED2       : 8;
        } ICF_B;
    };

    /* SDIO interrupt mask register */
    union
    {
        __IOM uint32_t MASK;

        struct
        {
            __IOM uint32_t CCRCFAIL        : 1;
            __IOM uint32_t DCRCFAIL        : 1;
            __IOM uint32_t CMDTO           : 1;
            __IOM uint32_t DATATO          : 1;
            __IOM uint32_t TXURER          : 1;
            __IOM uint32_t RXORER          : 1;
            __IOM uint32_t CMDRESRC        : 1;
            __IOM uint32_t CMDSENT         : 1;
            __IOM uint32_t DATAEND         : 1;
            __IOM uint32_t STRTER          : 1;
            __IOM uint32_t DBEND           : 1;
            __IOM uint32_t CMDACT          : 1;
            __IOM uint32_t TXACT           : 1;
            __IOM uint32_t RXACT           : 1;
            __IOM uint32_t TXHFERT         : 1;
            __IOM uint32_t RXHFFUL         : 1;
            __IOM uint32_t TXFUL           : 1;
            __IOM uint32_t RXFUL           : 1;
            __IOM uint32_t TXEPT           : 1;
            __IOM uint32_t RXFEIE          : 1;
            __IOM uint32_t TXDAVB          : 1;
            __IOM uint32_t RXDAVB          : 1;
            __IOM uint32_t SDIOINTREC      : 1;
            __IOM uint32_t ATACLPREC       : 1;
            __IM  uint32_t RESERVED        : 8;
        } MASK_B;
    };

    __IM  uint32_t  RESERVED[2];

    /* SDIO FIFO count register */
    union
    {
        __IM uint32_t FIFOCNT;

        struct
        {
            __IM  uint32_t FIFOCNT         : 24;
            __IM  uint32_t RESERVED        : 8;
        } FIFOCNT_B;
    };

    __IM  uint32_t  RESERVED1[13];

    /* SDIO data FIFO register */
    union
    {
        __IOM uint32_t FIFODATA;

        struct
        {
            __IOM  uint32_t FIFODATA       : 32;
        } FIFODATA_B;
    };
} SDIO_T;

/**
 * @brief Digital to Analog Converter(DAC)
 */
typedef struct
{
    /* Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t ENCH1           : 1;
            __IOM uint32_t BUFFDCH1        : 1;
            __IOM uint32_t TRGENCH1        : 1;
            __IOM uint32_t TRGSELCH1       : 3;
            __IOM uint32_t WAVENCH1        : 2;
            __IOM uint32_t MAMPSELCH1      : 4;
            __IOM uint32_t DMAENCH1        : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t ENCH2           : 1;
            __IOM uint32_t BUFFDCH2        : 1;
            __IOM uint32_t TRGENCH2        : 1;
            __IOM uint32_t TRGSELCH2       : 3;
            __IOM uint32_t WAVENCH2        : 2;
            __IOM uint32_t MAMPSELCH2      : 4;
            __IOM uint32_t DMAENCH2        : 1;
            __IM  uint32_t RESERVED2       : 3;
        } CTRL_B;
    };

    /* Software trigger register */
    union
    {
        __OM uint32_t SWTRG;

        struct
        {
            __OM   uint32_t SWTRG1         : 1;
            __OM   uint32_t SWTRG2         : 1;
            __IM   uint32_t RESERVED       : 30;
        } SWTRG_B;
    };

    /* Channel1 12-bit right-aligned register */
    union
    {
        __IOM uint32_t DH12R1;

        struct
        {
            __IOM uint32_t DATA            : 12;
            __IM  uint32_t RESERVED        : 20;
        } DH12R1_B;
    };

    /* Channel1 12-bit left-aligned register */
    union
    {
        __IOM uint32_t DH12L1;

        struct
        {
            __IM  uint32_t RESERVED1       : 4;
            __IOM uint32_t DATA            : 12;
            __IM  uint32_t RESERVED2       : 16;
        } DH12L1_B;
    };

    /* Channel1 8-bit right-aligned register */
    union
    {
        __IOM uint32_t DH8R1;

        struct
        {
            __IOM uint32_t DATA            : 8;
            __IM  uint32_t RESERVED        : 24;
        } DH8R1_B;
    };

    /* Channel2 12-bit right-aligned register */
    union
    {
        __IOM uint32_t DH12R2;

        struct
        {
            __IOM uint32_t DATA            : 12;
            __IM  uint32_t RESERVED        : 20;
        } DH12R2_B;
    };

    /* Channel2 12-bit left-aligned register */
    union
    {
        __IOM uint32_t DH12L2;

        struct
        {
            __IM  uint32_t RESERVED1       : 4;
            __IOM uint32_t DATA            : 12;
            __IM  uint32_t RESERVED2       : 16;
        } DH12L2_B;
    };

    /* Channel2 8-bit right-aligned register */
    union
    {
        __IOM uint32_t DH8R2;

        struct
        {
            __IOM uint32_t DATA            : 8;
            __IM  uint32_t RESERVED        : 24;
        } DH8R2_B;
    };

    /* Channel1,Channel2 12-bit right-aligned register */
    union
    {
        __IOM uint32_t DH12RDUAL;

        struct
        {
            __IOM uint32_t DATACH1         : 12;
            __IM  uint32_t RESERVED1       : 4;
            __IOM uint32_t DATACH2         : 12;
            __IM  uint32_t RESERVED2       : 4;
        } DH12RDUAL_B;
    };

    /* Channel1,Channel2 12-bit left-aligned register */
    union
    {
        __IOM uint32_t DH12LDUAL;

        struct
        {
            __IM  uint32_t RESERVED1       : 4;
            __IOM uint32_t DATACH1         : 12;
            __IM  uint32_t RESERVED2       : 4;
            __IOM uint32_t DATACH2         : 12;
        } DH12LDUAL_B;
    };

    /* Channel1,Channel2 8-bit right-aligned register */
    union
    {
        __IOM uint32_t DH8RDUAL;

        struct
        {
            __IOM uint32_t DATACH1         : 8;
            __IOM uint32_t DATACH2         : 8;
            __IM  uint32_t RESERVED        : 16;
        } DH8RDUAL_B;
    };

    /* Channel1 data output register */
    union
    {
        __IM uint32_t DATAOCH1;

        struct
        {
            __IM  uint32_t DATA            : 12;
            __IM  uint32_t RESERVED        : 20;
        } DATAOCH1_B;
    };

    /* Channel2 data output register */
    union
    {
        __IM uint32_t DATAOCH2;

        struct
        {
            __IM  uint32_t DATA            : 12;
            __IM  uint32_t RESERVED        : 20;
        } DATAOCH2_B;
    };
} DAC_T;

/**
 * @brief SMC Register
 */
typedef struct
{
    /* SRAM/NOR-Flash chip-select control register */
    union
    {
        __IOM uint32_t CSCTRL;

        struct
        {
            __IOM uint32_t MBKEN           : 1;
            __IOM uint32_t ADMUXEN         : 1;
            __IOM uint32_t MTYPECFG        : 2;
            __IOM uint32_t MDBWIDCFG       : 2;
            __IOM uint32_t NORFMACCEN      : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t BURSTEN         : 1;
            __IOM uint32_t WSPOLCFG        : 1;
            __IOM uint32_t WRAPBEN         : 1;
            __IOM uint32_t WTIMCFG         : 1;
            __IOM uint32_t WREN            : 1;
            __IOM uint32_t WAITEN          : 1;
            __IOM uint32_t EXTMODEEN       : 1;
            __IOM uint32_t WSASYNCEN       : 1;
            __IOM uint32_t CRAMPSIZECFG    : 3;
            __IOM uint32_t WRBURSTEN       : 1;
            __IOM uint32_t RESERVED2       : 12;
        } CSCTRL_B;
    };
} SNCTRL_T;

typedef struct
{
    /* SRAM/NOR-Flash write timing registers */
    union
    {
        __IOM uint32_t WRTTIM;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ACCMODECFG      : 2;
            __IM  uint32_t RESERVED2       : 2;
        } WRTTIM_T;
    };
} SNWCLK_T;

/**
 * @brief Flexible Static Memory Controller
 */
typedef struct
{
    __IO uint32_t SNCTRL_T[8];
} SMC_Bank1_T;

/**
 * @brief Flexible Static Memory Controller Bank1E
 */
typedef struct
{
    __IO uint32_t WRTTIM[7];
} SMC_Bank1E_T;

/**
 * @brief Flexible Static Memory Controller Bank 2
 */
typedef struct
{
    /* PC Card/NAND Flash control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t WAITFEN         : 1;
            __IOM uint32_t MBKEN           : 1;
            __IOM uint32_t MTYPECFG        : 1;
            __IOM uint32_t DBWIDCFG        : 2;
            __IOM uint32_t ECCEN           : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t C2RDCFG         : 4;
            __IOM uint32_t A2RDCFG         : 4;
            __IOM uint32_t ECCPSCFG        : 3;
            __IM  uint32_t RESERVED3       : 12;
        } CTRL2_B;
    };

    /* FIFO status and interrupt register 2 */
    union
    {
        __IOM uint32_t STSINT2;

        struct
        {
            __IOM uint32_t IREFLG          : 1;
            __IOM uint32_t IHLFLG          : 1;
            __IOM uint32_t IFEFLG          : 1;
            __IOM uint32_t IREDEN          : 1;
            __IOM uint32_t IHLDEN          : 1;
            __IOM uint32_t IFEDEN          : 1;
            __IM  uint32_t FEFLG           : 1;
            __IM  uint32_t RESERVED        : 25;
        } STSINT2_B;
    };
    /* Common memory space timing register 2 */
    union
    {
        __IOM uint32_t CMSTIM2;

        struct
        {
            __IOM uint32_t SET2            : 8;
            __IOM uint32_t WAIT2           : 8;
            __IOM uint32_t HLD2            : 8;
            __IOM uint32_t HIZ2            : 8;
        } CMSTIM2_B;
    };

    /* Attribute memory space timing register 2 */
    union
    {
        __IOM uint32_t AMSTIM2;

        struct
        {
            __IOM uint32_t SET2            : 8;
            __IOM uint32_t WAIT2           : 8;
            __IOM uint32_t HLD2            : 8;
            __IOM uint32_t HIZ2            : 8;
        } AMSTIM2_B;
    };

    __IOM uint32_t RESERVED;

    /* ECC result register 2 */
    union
    {
        __IM  uint32_t ECCRS2;

        struct
        {
            __IM  uint32_t ECCRS2          : 32;
        } ECCRS2_B;
    };
} SMC_Bank2_T;

/**
 * @brief Flexible Static Memory Controller Bank 3
 */
typedef struct
{
    /* PC Card/NAND Flash control register 3 */
    union
    {
        __IOM uint32_t CTRL3;

        struct
        {
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t WAITFEN         : 1;
            __IOM uint32_t MBKEN           : 1;
            __IOM uint32_t MTYPECFG        : 1;
            __IOM uint32_t DBWIDCFG        : 2;
            __IOM uint32_t ECCEN           : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t C2RDCFG         : 4;
            __IOM uint32_t A2RDCFG         : 4;
            __IOM uint32_t ECCPSCFG        : 3;
            __IM  uint32_t RESERVED3       : 12;
        } CTRL3_B;
    };

    /* FIFO status and interrupt register 3 */
    union
    {
        __IOM uint32_t STSINT3;

        struct
        {
            __IOM uint32_t IREFLG          : 1;
            __IOM uint32_t IHLFLG          : 1;
            __IOM uint32_t IFEFLG          : 1;
            __IOM uint32_t IREDEN          : 1;
            __IOM uint32_t IHLDEN          : 1;
            __IOM uint32_t IFEDEN          : 1;
            __IM  uint32_t FEFLG           : 1;
            __IM  uint32_t RESERVED        : 16;
        } STSINT3_B;
    };

    /* Common memory space timing register 3 */
    union
    {
        __IOM uint32_t CMSTIM3;

        struct
        {
            __IOM uint32_t SET3            : 8;
            __IOM uint32_t WAIT3           : 8;
            __IOM uint32_t HLD3            : 8;
            __IOM uint32_t HIZ3            : 8;
        } CMSTIM3_B;
    };

    /* Attribute memory space timing register 3 */
    union
    {
        __IOM uint32_t AMSTIM3;

        struct
        {
            __IOM uint32_t SET3            : 8;
            __IOM uint32_t WAIT3           : 8;
            __IOM uint32_t HLD3            : 8;
            __IOM uint32_t HIZ3            : 8;
        } AMSTIM3_B;
    };

    __IOM uint32_t RESERVED;

    /* ECC result register 3 */
    union
    {
        __IM  uint32_t ECCRS3;

        struct
        {
            __IM  uint32_t ECCRS3       : 32;
        } ECCRS3_B;
    };
} SMC_Bank3_T;

/**
 * @brief Flexible Static Memory Controller Bank 4
 */
typedef struct
{
    /* PC Card/NAND Flash control register 4 */
    union
    {
        __IOM uint32_t CTRL4;

        struct
        {
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t WAITFEN         : 1;
            __IOM uint32_t MBKEN           : 1;
            __IOM uint32_t MTYPECFG        : 1;
            __IOM uint32_t DBWIDCFG        : 2;
            __IOM uint32_t ECCEN           : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t C2RDCFG         : 4;
            __IOM uint32_t A2RDCFG         : 4;
            __IOM uint32_t ECCPSCFG        : 3;
            __IM  uint32_t RESERVED3       : 12;
        } CTRL4_B;
    };

    /* FIFO status and interrupt register 4 */
    union
    {
        __IOM uint32_t STSINT4;

        struct
        {
            __IOM uint32_t IREFLG          : 1;
            __IOM uint32_t IHLFLG          : 1;
            __IOM uint32_t IFEFLG          : 1;
            __IOM uint32_t IREDEN          : 1;
            __IOM uint32_t IHLDEN          : 1;
            __IOM uint32_t IFEDEN          : 1;
            __IM  uint32_t FEFLG           : 1;
            __IM  uint32_t RESERVED        : 16;
        } STSINT4_B;
    };

    /* Common memory space timing register 4 */
    union
    {
        __IOM uint32_t CMSTIM4;

        struct
        {
            __IOM uint32_t SET4            : 8;
            __IOM uint32_t WAIT4           : 8;
            __IOM uint32_t HLD4            : 8;
            __IOM uint32_t HIZ4            : 8;
        } CMSTIM4_B;
    };

    /* Attribute memory space timing register 4 */
    union
    {
        __IOM uint32_t AMSTIM4;

        struct
        {
            __IOM uint32_t SET4            : 8;
            __IOM uint32_t WAIT4           : 8;
            __IOM uint32_t HLD4            : 8;
            __IOM uint32_t HIZ4            : 8;
        } AMSTIM4_B;
    };

    /* I/O space timing register 4 */
    union
    {
        __IOM uint32_t IOSTIM4;

        struct
        {
            __IOM uint32_t SET4            : 8;
            __IOM uint32_t WAIT4           : 8;
            __IOM uint32_t HLD4            : 8;
            __IOM uint32_t HIZ4            : 8;
        } IOSTIM4_B;
    };
} SMC_Bank4_T;

/**
 * @brief Queued serial peripheral interface(QSPI)
 */
typedef struct
{
    /* @brief Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;
        struct
        {
            __IOM uint32_t DFS             : 5;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t CPHA            : 1;
            __IOM uint32_t CPOL            : 1;
            __IOM uint32_t TXMODE          : 2;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t SSTEN           : 1;
            __IM  uint32_t RESERVED3       : 7;
            __IOM uint32_t FRF             : 2;
            __IM  uint32_t RESERVED4       : 8;
        } CTRL1_B;
    };

    /* @brief Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;
        struct
        {
            __IOM uint32_t NDF             : 16;
            __IM  uint32_t RESERVED        : 16;
        } CTRL2_B;
    };

    /* @brief QSPI Enable register */
    union
    {
        __IOM uint32_t SSIEN;
        struct
        {
            __IOM uint32_t EN              : 1;
            __IM  uint32_t RESERVED        : 31;
        } SSIEN_B;
    };

    __IM  uint32_t RESERVED;

    /* @brief QSPI Slave enable register */
    union
    {
        __IOM uint32_t SLAEN;
        struct
        {
            __IOM uint32_t SLAEN           : 1;
            __IM  uint32_t RESERVED        : 31;
        } SLAEN_B;
    };

    /* @brief Baudrate register */
    union
    {
        __IOM uint32_t BR;
        struct
        {
            __IOM uint32_t CLKDIV          : 16;
            __IM  uint32_t RESERVED        : 16;
        } BR_B;
    };

    /* @brief Transmission FIFO threshhold level register */
    union
    {
        __IOM uint32_t TFTL;
        struct
        {
            __IOM uint32_t TFT             : 3;
            __IM  uint32_t RESERVED1       : 13;
            __IOM uint32_t TFTH            : 3;
            __IM  uint32_t RESERVED2       : 13;
        } TFTL_B;
    };

    /* @brief Reception FIFO threshhold level register */
    union
    {
        __IOM uint32_t RFTL;
        struct
        {
            __IOM uint32_t RFT             : 3;
            __IM  uint32_t RESERVED        : 29;
        } RFTL_B;
    };

    /* @brief Transmission FIFO level register */
    union
    {
        __IOM uint32_t TFL;
        struct
        {
            __IOM uint32_t TFL             : 3;
            __IM  uint32_t RESERVED        : 29;
        } TFL_B;
    };

    /* @brief Reception FIFO level register */
    union
    {
        __IOM uint32_t RFL;
        struct
        {
            __IOM uint32_t RFL             : 3;
            __IM  uint32_t RESERVED        : 29;
        } RFL_B;
    };

    /* @brief Status register */
    union
    {
        __IOM uint32_t STS;
        struct
        {
            __IOM uint32_t BUSYF           : 1;
            __IOM uint32_t TFNF            : 1;
            __IOM uint32_t TFEF            : 1;
            __IOM uint32_t RFNEF           : 1;
            __IOM uint32_t RFFF            : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t DCEF            : 1;
            __IM  uint32_t RESERVED2       : 25;
        } STS_B;
    };

    /* @brief Interrupt enable register */
    union
    {
        __IOM uint32_t INTEN;
        struct
        {
            __IOM uint32_t TFEIE           : 1;
            __IOM uint32_t TFOIE           : 1;
            __IOM uint32_t RFUIE           : 1;
            __IOM uint32_t RFOIE           : 1;
            __IOM uint32_t RFFIE           : 1;
            __IOM uint32_t MSTIE           : 1;
            __IM  uint32_t RESERVED        : 26;
        } INTEN_B;
    };

    /* @brief Interrupt status register */
    union
    {
        __IM uint32_t ISTS;
        struct
        {
            __IM  uint32_t TFEIF           : 1;
            __IM  uint32_t TFOIF           : 1;
            __IM  uint32_t RFUIF           : 1;
            __IM  uint32_t RFOIF           : 1;
            __IM  uint32_t RFFIF           : 1;
            __IM  uint32_t MSTIF           : 1;
            __IM  uint32_t RESERVED        : 26;
        } ISTS_B;
    };

    /* @brief Raw interrupt register */
    union
    {
        __IM uint32_t RIS;
        struct
        {
            __IM  uint32_t TFEIF           : 1;
            __IM  uint32_t TFOIF           : 1;
            __IM  uint32_t RFUIF           : 1;
            __IM  uint32_t RXOIR           : 1;
            __IM  uint32_t RXFIR           : 1;
            __IM  uint32_t MSTIR           : 1;
            __IM  uint32_t RESERVED        : 26;
        } RIS_B;
    };

    /* @brief Transmission FIFO overflow interrupt clear register */
    union
    {
        __IM uint32_t TFOIC;
        struct
        {
            __IM  uint32_t TFOIC           : 1;
            __IM  uint32_t RESERVED        : 31;
        } TFOIC_B;
    };

    /* @brief Reception FIFO overflow interrupt clear register */
    union
    {
        __IM uint32_t RFOIC;
        struct
        {
            __IM  uint32_t RFOIC           : 1;
            __IM  uint32_t RESERVED        : 31;
        } RFOIC_B;
    };

    /* @brief Reception FIFO underflow interrupt clear register */
    union
    {
        __IM uint32_t RFUIC;
        struct
        {
            __IM  uint32_t RFUIC           : 1;
            __IM  uint32_t RESERVED        : 31;
        } RFUIC_B;
    };

    /* @brief Master interrupt clear register */
    union
    {
        __IM uint32_t MIC;
        struct
        {
            __IM  uint32_t MIC             : 1;
            __IM  uint32_t RESERVED        : 31;
        } MIC_B;
    };

    /* @brief Interrupt clear register */
    union
    {
        __IM uint32_t ICF;
        struct
        {
            __IM  uint32_t ICF             : 1;
            __IM  uint32_t RESERVED        : 31;
        } ICF_B;
    };

    __IM  uint32_t RESERVED1[5];

    /* @brief Data register */
    union
    {
        __IOM uint32_t DATA;
        struct
        {
            __IOM  uint32_t DATA           : 32;
        } DATA_B;
    };

    __IM  uint32_t RESERVED2[35];

    /* @brief Reception sample register */
    union
    {
        __IOM uint32_t RSD;
        struct
        {
            __IOM uint32_t RSD             : 8;
            __IM  uint32_t RESERVED1       : 8;
            __IOM uint32_t RSE             : 1;
            __IM  uint32_t RESERVED2       : 15;
        } RSD_B;
    };

    /* @brief Reception sample register */
    union
    {
        __IOM uint32_t CTRL3;
        struct
        {
            __IOM uint32_t IAT             : 2;
            __IOM uint32_t ADDRLEN         : 4;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t INSLEN          : 2;
            __IM  uint32_t RESERVED2       : 1;
            __IOM uint32_t WAITCYC         : 5;
            __IM  uint32_t RESERVED3       : 14;
            __IOM uint32_t CSEN            : 1;
            __IM  uint32_t RESERVED4       : 1;
        } CTRL3_B;
    };

    __IM  uint32_t  RESERVED3[66];

    /* @brief IO switch register */
    union
    {
        __IOM uint32_t IOSW;
        struct
        {
            __IOM uint32_t IOSW            : 1;
            __IM  uint32_t RESERVED        : 31;
        } IOSW_B;
    };
} QSPI_T;

/**
 * @brief SEC Inter-integrated circuit (SCI2C)
 */
typedef struct
{
    /* @brief Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;
        struct
        {
            __IOM uint32_t MST             : 1;
            __IOM uint32_t SPD             : 2;
            __IOM uint32_t SAM             : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t RSTAEN          : 1;
            __IOM uint32_t SLADIS          : 1;
            __IOM uint32_t DSA             : 1;
            __IOM uint32_t TFEIC           : 1;
            __IOM uint32_t RFFIE           : 1;
            __IOM uint32_t DSMA            : 1;
            __IM uint32_t RESERVED2        : 21;
        } CTRL1_B;
    };

    /* @brief Master address register */
    union
    {
        __IOM uint32_t TARADDR;
        struct
        {
            __IOM uint32_t ADDR            : 10;
            __IOM uint32_t STA             : 1;
            __IOM uint32_t GCEN            : 1;
            __IOM uint32_t MAM             : 1;
            __IM uint32_t RESERVED         : 19;
        } TARADDR_B;
    };

    /* @brief Slave address register */
    union
    {
        __IOM uint32_t SLAADDR;
        struct
        {
            __IOM uint32_t ADDR            : 10;
            __IM uint32_t RESERVED         : 22;
        } SLAADDR_B;
    };

    /* @brief High speed master code register */
    union
    {
        __IOM uint32_t HSMC;
        struct
        {
            __IOM uint32_t HSMC            : 4;
            __IM uint32_t RESERVED         : 28;
        } HSMC_B;
    };

    /* @brief Data register */
    union
    {
        __IOM uint32_t DATA;
        struct
        {
            __IOM uint32_t DATA            : 8;
            __IOM uint32_t CMD             : 1;
            __IOM uint32_t STOP            : 1;
            __IM uint32_t RESERVED         : 22;
        } DATA_B;
    };

    /* @brief Standard speed clock high counter register */
    union
    {
        __IOM uint32_t SSCHC;
        struct
        {
            __IOM uint32_t CNT             : 16;
            __IM uint32_t RESERVED         : 16;
        } SSCHC_B;
    };

    /* @brief Standard speed clock low counter register */
    union
    {
        __IOM uint32_t SSCLC;
        struct
        {
            __IOM uint32_t CNT             : 16;
            __IM uint32_t RESERVED         : 16;
        } SSCLC_B;
    };

    /* @brief Fast speed clock high counter register */
    union
    {
        __IOM uint32_t FSCHC;
        struct
        {
            __IOM uint32_t CNT             : 16;
            __IM uint32_t RESERVED         : 16;
        } FSCHC_B;
    };

    /* @brief Fast speed clock low counter register */
    union
    {
        __IOM uint32_t FSCLC;
        struct
        {
            __IOM uint32_t CNT             : 16;
            __IM uint32_t RESERVED         : 16;
        } FSCLC_B;
    };

    /* @brief High speed clock high counter */
    union
    {
        __IOM uint32_t HSCHC;
        struct
        {
            __IOM uint32_t CNT             : 16;
            __IM uint32_t RESERVED         : 16;
        } HSCHC_B;
    };

    /* @brief High speed clock low counter register */
    union
    {
        __IOM uint32_t HSCLC;
        struct
        {
            __IOM uint32_t CNT             : 16;
            __IM uint32_t RESERVED         : 16;
        } HSCLC_B;
    };

    /* @brief Interrupt status register */
    union
    {
        __IM uint32_t INTSTS;
        struct
        {
            __IM uint32_t RFUIF            : 1;
            __IM uint32_t RFOIF            : 1;
            __IM uint32_t RFFIF            : 1;
            __IM uint32_t TFOIF            : 1;
            __IM uint32_t TFEIF            : 1;
            __IM uint32_t RRIF             : 1;
            __IM uint32_t TAIF             : 1;
            __IM uint32_t RDIF             : 1;
            __IM uint32_t ACTIF            : 1;
            __IM uint32_t STPDIF           : 1;
            __IM uint32_t STADIF           : 1;
            __IM uint32_t GCIF             : 1;
            __IM uint32_t RSTADIF          : 1;
            __IM uint32_t MOHIF            : 1;
            __IM uint32_t RESERVED         : 18;
        } INTSTS_B;
    };

    /* @brief Interrupt enable register */
    union
    {
        __IOM uint32_t INTEN;
        struct
        {
            __IOM uint32_t RFUIE           : 1;
            __IOM uint32_t RFOIE           : 1;
            __IOM uint32_t RFFIE           : 1;
            __IOM uint32_t TFOIE           : 1;
            __IOM uint32_t TFEIE           : 1;
            __IOM uint32_t RRIE            : 1;
            __IOM uint32_t TAIE            : 1;
            __IOM uint32_t RDIE            : 1;
            __IOM uint32_t ACTIE           : 1;
            __IOM uint32_t STPDIE          : 1;
            __IOM uint32_t STADIE          : 1;
            __IOM uint32_t GCIE            : 1;
            __IOM uint32_t RSTADIE         : 1;
            __IOM uint32_t MOHIE           : 1;
            __IM uint32_t RESERVED         : 18;
        } INTEN_B;
    };

    /* @brief Raw interrupt status register */
    union
    {
        __IM uint32_t RIS;
        struct
        {
            __IM uint32_t RFUIF            : 1;
            __IM uint32_t RFOIF            : 1;
            __IM uint32_t RFFIF            : 1;
            __IM uint32_t TFOIF            : 1;
            __IM uint32_t TFEIF            : 1;
            __IM uint32_t RRIF             : 1;
            __IM uint32_t TAIF             : 1;
            __IM uint32_t RDIF             : 1;
            __IM uint32_t ACTIF            : 1;
            __IM uint32_t STPDIF           : 1;
            __IM uint32_t STADIF           : 1;
            __IM uint32_t GCIF             : 1;
            __IM uint32_t RSTADIF          : 1;
            __IM uint32_t MOHIF            : 1;
            __IM uint32_t RESERVED         : 18;
        } RIS_B;
    };

    /* @brief Reception FIFO threshold register */
    union
    {
        __IOM uint32_t RFT;
        struct
        {
            __IOM uint32_t RFT             : 8;
            __IM uint32_t RESERVED         : 24;
        } RFT_B;
    };

    /* @brief Transmission FIFO threshold register */
    union
    {
        __IOM uint32_t TFT;
        struct
        {
            __IOM uint32_t TFT             : 8;
            __IM uint32_t RESERVED         : 24;
        } TFT_B;
    };

    /* @brief Interruption clear register */
    union
    {
        __IM uint32_t INTCLR;
        struct
        {
            __IM uint32_t INTCLR           : 1;
            __IM uint32_t RESERVED         : 31;
        } INTCLR_B;
    };

    /* @brief Reception FIFO underflow interruption clear register */
    union
    {
        __IM uint32_t RFUIC;
        struct
        {
            __IM uint32_t RFUIC            : 1;
            __IM uint32_t RESERVED         : 31;
        } RFUIC_B;
    };

    /* @brief Reception FIFO overflow interruption clear register */
    union
    {
        __IM uint32_t RFOIC;
        struct
        {
            __IM uint32_t RFOIC            : 1;
            __IM uint32_t RESERVED         : 31;
        } RFOIC_B;
    };

    /* @brief Transmission FIFO overflow interruption clear register */
    union
    {
        __IM uint32_t TFOIC;
        struct
        {
            __IM uint32_t TFOIC            : 1;
            __IM uint32_t RESERVED         : 31;
        } TFOIC_B;
    };

    /* @brief Reception request interruption clear register */
    union
    {
        __IM uint32_t RRIC;
        struct
        {
            __IM uint32_t RRIC             : 1;
            __IM uint32_t RESERVED         : 31;
        } RRIC_B;
    };

    /* @brief Transmission abort interruption clear register */
    union
    {
        __IM uint32_t TAIC;
        struct
        {
            __IM uint32_t TAIC             : 1;
            __IM uint32_t RESERVED         : 31;
        } TAIC_B;
    };

    /* @brief Receive done interruption clear register */
    union
    {
        __IM uint32_t RDIC;
        struct
        {
            __IM uint32_t RDIC             : 1;
            __IM uint32_t RESERVED         : 31;
        } RDIC_B;
    };

    /* @brief Activity interruption clear register */
    union
    {
        __IM uint32_t AIC;
        struct
        {
            __IM uint32_t AIC              : 1;
            __IM uint32_t RESERVED         : 31;
        } AIC_B;
    };

    /* @brief Stop detection interruption clear register */
    union
    {
        __IM uint32_t STPDIC;
        struct
        {
            __IM uint32_t STPDIC           : 1;
            __IM uint32_t RESERVED         : 31;
        } STPDIC_B;
    };

    /* @brief Start detection interruption clear register */
    union
    {
        __IM uint32_t STADIC;
        struct
        {
            __IM uint32_t STADIC           : 1;
            __IM uint32_t RESERVED         : 31;
        } STADIC_B;
    };

    /* @brief General call interruption clear register */
    union
    {
        __IM uint32_t GCIC;
        struct
        {
            __IM uint32_t GCIC             : 1;
            __IM uint32_t RESERVED         : 31;
        } GCIC_B;
    };

    /* @brief Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;
        struct
        {
            __IOM uint32_t I2CEN           : 1;
            __IOM uint32_t ABR             : 1;
            __IOM uint32_t TCB             : 1;
            __IM uint32_t RESERVED         : 29;
        } CTRL2_B;
    };

    /* @brief Status register 1 */
    union
    {
        __IM uint32_t STS1;
        struct
        {
            __IM uint32_t ACTF             : 1;
            __IM uint32_t TFNFF            : 1;
            __IM uint32_t TFEF             : 1;
            __IM uint32_t RFNEF            : 1;
            __IM uint32_t RFFF             : 1;
            __IM uint32_t MAF              : 1;
            __IM uint32_t SAF              : 1;
            __IM uint32_t RESERVED         : 24;
        } STS1_B;
    };

    /* @brief Transmission FIFO level */
    union
    {
        __IOM uint32_t TFL;
        struct
        {
            __IOM uint32_t TFL             : 4;
            __IM uint32_t RESERVED         : 28;
        } TFL_B;
    };

    /* @brief Reception FIFO level */
    union
    {
        __IOM uint32_t RFL;
        struct
        {
            __IOM uint32_t RFL             : 4;
            __IM uint32_t RESERVED         : 28;
        } RFL_B;
    };

    /* @brief SDA hold time length register */
    union
    {
        __IOM uint32_t SDAHOLD;
        struct
        {
            __IOM uint32_t TXHOLD          : 16;
            __IOM uint32_t RXHOLD          : 8;
            __IM uint32_t RESERVED         : 8;
        } SDAHOLD_B;
    };

    /* @brief Transmission abort source register */
    union
    {
        __IM uint32_t TAS;
        struct
        {
            __IM uint32_t AD7NA            : 1;
            __IM uint32_t AD10NA1          : 1;
            __IM uint32_t AD10NA2          : 1;
            __IM uint32_t TDNA             : 1;
            __IM uint32_t GCNA             : 1;
            __IM uint32_t GCR              : 1;
            __IM uint32_t HSAD             : 1;
            __IM uint32_t SNR              : 1;
            __IM uint32_t RNR10B           : 1;
            __IM uint32_t MSTDIS           : 1;
            __IM uint32_t ARBLOST          : 1;
            __IM uint32_t LFTF             : 1;
            __IM uint32_t SAL              : 1;
            __IM uint32_t SRI              : 1;
            __IM uint32_t USRARB           : 1;
            __IM uint32_t FLUCNT           : 1;
            __IM uint32_t RESERVED         : 16;
        } TAS_B;
    };

    /* @brief Slave data NACK only register */
    union
    {
        __IOM uint32_t SDNO;
        struct
        {
            __IOM uint32_t NACK            : 1;
            __IM uint32_t RESERVED         : 31;
        } SDNO_B;
    };

    /* @brief DMA control register */
    union
    {
        __IOM uint32_t DMACTRL;
        struct
        {
            __IOM uint32_t RXEN            : 1;
            __IOM uint32_t TXEN            : 1;
            __IM uint32_t RESERVED         : 30;
        } DMACTRL_B;
    };

    /* @brief DMA transmission data level register */
    union
    {
        __IOM uint32_t DTDL;
        struct
        {
            __IOM uint32_t DTDL            : 4;
            __IM uint32_t RESERVED         : 28;
        } DTDL_B;
    };

    /* @brief DMA teception data level register */
    union
    {
        __IOM uint32_t DRDL;
        struct
        {
            __IOM uint32_t DRDL            : 4;
            __IM uint32_t RESERVED         : 28;
        } DRDL_B;
    };

    /* @brief SDA delay register */
    union
    {
        __IOM uint32_t SDADLY;
        struct
        {
            __IOM uint32_t SDADLY          : 8;
            __IM uint32_t RESERVED         : 24;
        } SDADLY_B;
    };

    /* @brief Genernal call ACK register */
    union
    {
        __IOM uint32_t GCA;
        struct
        {
            __IOM uint32_t GCA             : 1;
            __IM uint32_t RESERVED         : 31;
        } GCA_B;
    };

    /* @brief Status register 2 */
    union
    {
        __IM uint32_t STS2;
        struct
        {
            __IM uint32_t I2CEN            : 1;
            __IM uint32_t SDWB             : 1;
            __IM uint32_t SRDL             : 1;
            __IM uint32_t RESERVED         : 29;
        } STS2_B;
    };

    /* @brief Low speed spike suppression limit */
    union
    {
        __IOM uint32_t LSSSL;
        struct
        {
            __IOM uint32_t LSSSL           : 8;
            __IM uint32_t RESERVED         : 24;
        } LSSSL_B;
    };

    /* @brief High speed spike suppression limit */
    union
    {
        __IOM uint32_t HSSSL;
        struct
        {
            __IOM uint32_t HSSSL           : 8;
            __IM uint32_t RESERVED         : 24;
        } HSSSL_B;
    };

    uint32_t RESERVED[22];

    /* @brief Switch register */
    union
    {
        __IOM uint32_t SW;
        struct
        {
            __IOM uint32_t SW              : 1;
            __IM uint32_t RESERVED         : 31;
        } SW_B;
    };
} SCI2C_T;

/**
 * @brief Dynamic memory controler (DMC)
 */
typedef struct
{
    /* @brief Configuraion register */
    union
    {
        __IOM uint32_t CFG;
        struct
        {
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t BAWCFG          : 2;
            __IOM uint32_t RAWCFG          : 4;
            __IOM uint32_t CAWCFG          : 4;
            __IOM uint32_t DWCFG           : 2;
            __IM  uint32_t RESERVED2       : 17;
        } CFG_B;
    };

    /* @brief Timing register 0 */
    union
    {
        __IOM uint32_t TIM0;
        struct
        {
            __IOM uint32_t CASLSEL0        : 2;
            __IOM uint32_t RASMINTSEL      : 4;
            __IOM uint32_t DTIMSEL         : 3;
            __IOM uint32_t PCPSEL          : 3;
            __IOM uint32_t WRTIMSEL        : 2;
            __IOM uint32_t ARPSEL          : 4;
            __IOM uint32_t XSR0            : 4;
            __IOM uint32_t ATACP           : 4;
            __IOM uint32_t ECASLSEL1       : 1;
            __IOM uint32_t EXSR1           : 5;
        } TIM0_B;
    };

    /* @brief Timing register 1 */
    union
    {
        __IOM uint32_t TIM1;
        struct
        {
            __IOM uint32_t STBTIM          : 16;
            __IOM uint32_t ARNUMCFG        : 4;
            __IM  uint32_t RESERVED        : 12;
        } TIM1_B;
    };

    /* @brief Control register 1 */
    union
    {
        __IOM uint32_t CTRL1;
        struct
        {
            __IOM uint32_t INIT            : 1;
            __IOM uint32_t SRMEN           : 1;
            __IOM uint32_t PDMEN           : 1;
            __IOM uint32_t PCACFG          : 1;
            __IOM uint32_t FRBSREN         : 1;
            __IOM uint32_t FRASREN         : 1;
            __IOM uint32_t RDNUMMCFG       : 3;
            __IOM uint32_t MODESET         : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IM  uint32_t SRMFLG          : 1;
            __IOM uint32_t BANKNUMCFG      : 5;
            __IM  uint32_t RESERVED2       : 15;
        } CTRL1_B;
    };

    /* @brief Refresh register */
    union
    {
        __IOM uint32_t REF;
        struct
        {
            __IOM uint32_t RCYCCFG         : 16;
            __IM  uint32_t RESERVED        : 16;
        } REF_B;
    };

    /* @brief Chip select register */
    union
    {
        __IOM uint32_t CHIPSEL;
        struct
        {
            __IM  uint32_t RESERVED        : 16;
            __IOM uint32_t BACHIPSEL       : 16;

        } CHIPSEL_B;
    };

    __IM  uint32_t  RESERVED[15];

    /* @brief Mask register */
    union
    {
        __IOM uint32_t MASK;
        struct
        {
            __IOM uint32_t MSIZESEL        : 5;
            __IOM uint32_t MTYPESEL        : 3;
            __IM  uint32_t RESERVED        : 24;
        } MASK_B;
    };

    __IM  uint32_t  RESERVED1[234];

    /* @brief Switch register */
    union
    {
        __IOM uint32_t SW;
        struct
        {
            __IOM uint32_t MCSW            : 1;
            __IM  uint32_t RESERVED        : 31;
        } SW_B;
    };

    /* @brief Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;
        struct
        {
            __IOM uint32_t CPHACFG         : 1;
            __IOM uint32_t RDDEN           : 1;
            __IOM uint32_t RDDCFG          : 3;
            __IOM uint32_t WPEN            : 1;
            __IOM uint32_t BUFFEN          : 1;
            __IOM uint32_t WRPBSEL         : 1;
            __IM  uint32_t RESERVED        : 24;
        } CTRL2_B;
    };
} DMC_T;

/**
 * @brief Debug MCU(DBGMCU)
 */
typedef struct
{
    /* @brief ID register */
    union
    {
        __IOM uint32_t IDCODE;
        struct
        {
            __IOM uint32_t EQR             : 12;
            __IM  uint32_t RESERVED        : 4;
            __IOM uint32_t WVR             : 16;
        } IDCODE_B;
    };

    /* @brief Control register */
    union
    {
        __IOM uint32_t CFG;
        struct
        {
            __IOM uint32_t SLEEP_CLK_STS   : 1;
            __IOM uint32_t STOP_CLK_STS    : 1;
            __IOM uint32_t STANDBY_CLK_STS : 1;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t IOEN            : 1;
            __IOM uint32_t MODE            : 2;
            __IOM uint32_t IWDT_STS        : 1;
            __IOM uint32_t WWDT_STS        : 1;
            __IOM uint32_t TMR1_STS        : 1;
            __IOM uint32_t TMR2_STS        : 1;
            __IOM uint32_t TMR3_STS        : 1;
            __IOM uint32_t TMR4_STS        : 1;
            __IOM uint32_t CAN1_STS        : 1;
            __IOM uint32_t I2C1_SMBUS_TIMEOUT_STS : 1;
            __IOM uint32_t I2C2_SMBUS_TIMEOUT_STS : 1;
            __IOM uint32_t TMR8_STS        : 1;
            __IOM uint32_t TMR5_STS        : 1;
            __IOM uint32_t TMR6_STS        : 1;
            __IOM uint32_t TMR7_STS        : 1;
            __IOM uint32_t CAN2_STS        : 1;
            __IM  uint32_t RESERVED2       : 3;
            __IOM uint32_t TMR12_STS       : 1;
            __IOM uint32_t TMR13_STS       : 1;
            __IOM uint32_t TMR14_STS       : 1;
            __IOM uint32_t TMR9_STS        : 1;
            __IOM uint32_t TMR10_STS       : 1;
            __IOM uint32_t TMR11_STS       : 1;
            __IM  uint32_t RESERVED3       : 1;
        } CFG_B;
    };
} DBGMCU_T;

/**
 * @brief   USB Device controler(USBD)
 */
typedef union
{
    __IOM uint32_t EP;

    struct
    {
        __IOM uint32_t ADDR                : 4;
        __IOM uint32_t TXSTS               : 2;
        __IOM uint32_t TXDTOG              : 1;
        __IOM uint32_t CTFT                : 1;
        __IOM uint32_t KIND                : 1;
        __IOM uint32_t TYPE                : 2;
        __IOM uint32_t SETUP               : 1;
        __IOM uint32_t RXSTS               : 2;
        __IOM uint32_t RXDTOG              : 1;
        __IOM uint32_t CTFR                : 1;
        __IM  uint32_t RESERVED            : 16;
    } EP_B;
} USBD_EP_REG_T;

typedef struct
{
    /* Endpoint */
    USBD_EP_REG_T EP[8];

    __IM  uint32_t  RESERVED[8];

    /* @brief Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t FORRST          : 1;
            __IOM uint32_t PWRDOWN         : 1;
            __IOM uint32_t LPWREN          : 1;
            __IOM uint32_t FORSUS          : 1;
            __IOM uint32_t WUPREQ          : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t ESOFIEN         : 1;
            __IOM uint32_t SOFIEN          : 1;
            __IOM uint32_t RSTIEN          : 1;
            __IOM uint32_t SUSIEN          : 1;
            __IOM uint32_t WUPIEN          : 1;
            __IOM uint32_t ERRIEN          : 1;
            __IOM uint32_t PMAOUIEN        : 1;
            __IOM uint32_t CTRIEN          : 1;
            __IM  uint32_t RESERVED2       : 16;
        } CTRL_B;
    };

    /* @brief Interrupt status register */
    union
    {
        __IOM uint32_t INTSTS;

        struct
        {
            __IOM uint32_t EPID            : 4;
            __IOM uint32_t DOT             : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t ESOFFLG         : 1;
            __IOM uint32_t SOFFLG          : 1;
            __IOM uint32_t RSTREQ          : 1;
            __IOM uint32_t SUSREQ          : 1;
            __IOM uint32_t WUPREQ          : 1;
            __IOM uint32_t ERRFLG          : 1;
            __IOM uint32_t PMOFLG          : 1;
            __IOM uint32_t CTFLG           : 1;
            __IM  uint32_t RESERVED2       : 16;
        } INTSTS_B;
    };

    /* @brief Frame number register */
    union
    {
        __IM uint32_t FRANUM;

        struct
        {
            __IM  uint32_t FRANUM          : 11;
            __IM  uint32_t LSOFNUM         : 2;
            __IM  uint32_t LOCK            : 1;
            __IM  uint32_t RXDMSTS         : 1;
            __IM  uint32_t RXDPSTS         : 1;
            __IM  uint32_t RESERVED        : 16;
        } FRANUM_B;
    };

    /* @brief Device address register */
    union
    {
        __IOM uint32_t ADDR;

        struct
        {
            __IOM uint32_t ADDR            : 7;
            __IOM uint32_t USBDEN          : 1;
            __IM  uint32_t RESERVED        : 24;
        } ADDR_B;
    };

    /* @brief Buffer table address register */
    union
    {
        __IOM uint32_t BUFFTB;

        struct
        {
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t BUFFTB          : 13;
            __IM  uint32_t RESERVED2       : 16;
        } BUFFTB_B;
    };

    __IM  uint32_t  RESERVED1[43];

    /* @brief Buffer table address register  */
    union
    {
        __IOM uint32_t USB_SWITCH;

        struct
        {
            __IOM uint32_t USB_SWITCH           : 1;
            __IM  uint32_t RESERVED         : 31;
        } SWITCH_B;
    };
} USBD_T;

/**
  * @brief Ethernet: media access control (Ethernet_MAC)
  */

typedef struct
{

    union
    {
        __IOM uint32_t CFG;

        struct
        {
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t RXEN       : 1;
            __IOM uint32_t TXEN       : 1;
            __IOM uint32_t DC         : 1;
            __IOM uint32_t BL         : 2;
            __IOM uint32_t ACS        : 1;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t DISR       : 1;
            __IOM uint32_t IPC        : 1;
            __IOM uint32_t DM         : 1;
            __IOM uint32_t LBM        : 1;
            __IOM uint32_t DISRXO     : 1;
            __IOM uint32_t SSEL       : 1;
            __IM  uint32_t RESERVED3  : 1;
            __IOM uint32_t DISCRS     : 1;
            __IOM uint32_t IFG        : 3;
            __IM  uint32_t RESERVED4  : 2;
            __IOM uint32_t JDIS       : 1;
            __IOM uint32_t WDTDIS     : 1;
        } CFG_B;
    } ;

    union
    {
        __IOM uint32_t FRAF;

        struct
        {
            __IOM uint32_t PR         : 1;
            __IOM uint32_t HUC        : 1;
            __IOM uint32_t HMC        : 1;
            __IOM uint32_t DAIF       : 1;
            __IOM uint32_t PM         : 1;
            __IOM uint32_t DISBF      : 1;
            __IOM uint32_t PCTRLF     : 1;
            __IOM uint32_t SAIF       : 1;
            __IOM uint32_t SAFEN      : 1;
            __IOM uint32_t HPF        : 1;
            __IM  uint32_t RESERVED1  : 21;
            __IOM uint32_t RXA        : 1;
        } FRAF_B;
    } ;

    union
    {
        __IOM uint32_t HTH;

        struct
        {
            __IOM uint32_t HTH        : 32;
        } HTH_B;
    } ;

    union
    {
        __IOM uint32_t HTL;

        struct
        {
            __IOM uint32_t HTL        : 32;
        } HTL_B;
    } ;

    union
    {
        __IOM uint32_t ADDR;

        struct
        {
            __IOM uint32_t MB         : 1;
            __IOM uint32_t MW         : 1;
            __IOM uint32_t CR         : 3;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t MR         : 5;
            __IOM uint32_t PA         : 5;
        } ADDR_B;
    } ;

    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t MD         : 16;
        } DATA_B;
    } ;

    union
    {
        __IOM uint32_t FCTRL;

        struct
        {
            __IOM uint32_t FCTRLB     : 1;
            __IOM uint32_t TXFCTRLEN  : 1;
            __IOM uint32_t RXFCTRLEN  : 1;
            __IOM uint32_t UNPFDETE   : 1;
            __IOM uint32_t PTSEL      : 2;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t ZQPDIS     : 1;
            __IM  uint32_t RESERVED2  : 8;
            __IOM uint32_t PT         : 16;
        } FCTRL_B;
    } ;

    union
    {
        __IOM uint32_t VLANT;

        struct
        {
            __IOM uint32_t VLANTID    : 16;
            __IOM uint32_t VLANTCOMP  : 1;
        } VLANT_B;
    } ;
    __IM  uint32_t  RESERVED[2];
    __IOM uint32_t  REMWKUPFFL;

    union
    {
        __IOM  uint32_t PMTCTRLSTS;

        struct
        {
            __IOM  uint32_t PD        : 1;
            __IOM  uint32_t MPEN      : 1;
            __IOM  uint32_t WKUPFEN   : 1;
            __IM  uint32_t  RESERVED1 : 2;
            __IOM  uint32_t MPRX      : 1;
            __IOM  uint32_t WKUPFRX   : 1;
            __IM  uint32_t  RESERVED2 : 2;
            __IOM  uint32_t GUN       : 1;
            __IM  uint32_t  RESERVED3 : 21;
            __IOM  uint32_t WKUPFRST  : 1;
        } PMTCTRLSTS_B;
    } ;
    __IM  uint32_t  RESERVED1[2];

    union
    {
        __IOM uint32_t ISTS;

        struct
        {
            __IM  uint32_t RESERVED1  : 3;
            __IM  uint32_t PMTIS      : 1;
            __IM  uint32_t MMCIS      : 1;
            __IM  uint32_t MMCRXIS    : 1;
            __IM  uint32_t MMCTXIS    : 1;
            __IM  uint32_t RESERVED2  : 2;
            __IOM uint32_t TSIS       : 1;
        } ISTS_B;
    } ;

    union
    {
        __IOM uint32_t IMASK;

        struct
        {
            __IM  uint32_t RESERVED1  : 3;
            __IOM uint32_t PMTIM      : 1;
            __IM  uint32_t RESERVED2  : 5;
            __IOM uint32_t TSTIM      : 1;
        } IMASK_B;
    } ;

    union
    {
        __IOM uint32_t ADDR0H;

        struct
        {
            __IOM uint32_t ADDR0H     : 16;
            __IM  uint32_t RESERVED1  : 15;
            __IM  uint32_t AL1        : 1;
        } ADDR0H_B;
    } ;

    union
    {
        __IOM uint32_t ADDR0L;

        struct
        {
            __IOM uint32_t ADDR0L     : 32;
        } ADDR0L_B;
    } ;

    union
    {
        __IOM uint32_t ADDR1H;

        struct
        {
            __IOM uint32_t ADDR1H     : 16;
            __IM  uint32_t RESERVED1  : 8;
            __IOM uint32_t MASKBCTRL  : 6;
            __IOM uint32_t ADDRSEL    : 1;
            __IOM uint32_t ADDREN     : 1;
        } ADDR1H_B;
    } ;

    union
    {
        __IOM uint32_t ADDR1L;

        struct
        {
            __IOM uint32_t ADDR1L     : 32;
        } ADDR1L_B;
    } ;

    union
    {
        __IOM uint32_t ADDR2H;

        struct
        {
            __IOM uint32_t ADDR2H     : 16;
            __IM  uint32_t RESERVED1  : 8;
            __IOM uint32_t MASKBCTRL  : 6;
            __IOM uint32_t ADDRSEL    : 1;
            __IOM uint32_t ADDREN     : 1;
        } ADDR2H_B;
    } ;

    union
    {
        __IOM uint32_t ADDR2L;

        struct
        {
            __IOM uint32_t ADDR2L     : 31;
        } ADDR2L_B;
    } ;

    union
    {
        __IOM uint32_t ADDR3H;

        struct
        {
            __IOM uint32_t ADDR3H     : 16;
            __IM  uint32_t RESERVED1  : 8;
            __IOM uint32_t MASKBCTRL  : 6;
            __IOM uint32_t ADDRSEL    : 1;
            __IOM uint32_t ADDREN     : 1;
        } ADDR3H_B;
    } ;

    union
    {
        __IOM uint32_t ADDR3L;

        struct
        {
            __IOM uint32_t ADDR3L     : 32;
        } ADDR3L_B;
    } ;
    __IM  uint32_t  RESERVED2[40];

    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t CNTRST     : 1;
            __IOM uint32_t CNTSTOPRO  : 1;
            __IOM uint32_t RSTOR      : 1;
            __IOM uint32_t MCNTF      : 1;
            __IM  uint32_t RESERVED1  : 28;
        } CTRL_B;
    } ;

    union
    {
        __IOM uint32_t RXINT;

        struct
        {
            __IM  uint32_t RESERVED1  : 5;
            __IOM uint32_t RXFCE      : 1;
            __IOM uint32_t RXFAE      : 1;
            __IM  uint32_t RESERVED2  : 10;
            __IOM uint32_t RXGUNF     : 1;
        } RXINT_B;
    } ;

    union
    {
        __IOM uint32_t TXINT;

        struct
        {
            __IM  uint32_t RESERVED1  : 14;
            __IOM uint32_t TXGFSCOL   : 1;
            __IOM uint32_t TXGFMCOL   : 1;
            __IM  uint32_t RESERVED2  : 5;
            __IOM uint32_t TXGF       : 1;
        } TXINT_B;
    } ;

    union
    {
        __IOM uint32_t RXINTMASK;

        struct
        {
            __IM  uint32_t RESERVED1  : 5;
            __IOM uint32_t RXFCEM     : 1;
            __IOM uint32_t RXFAEM     : 1;
            __IM  uint32_t RESERVED2  : 10;
            __IOM uint32_t RXGUNFM    : 1;
        } RXINTMASK_B;
    } ;

    union
    {
        __IOM uint32_t TXINTMASK;

        struct
        {
            __IM  uint32_t RESERVED1  : 14;
            __IOM uint32_t TXGFSCOLM  : 1;
            __IOM uint32_t TXGFMCOLM  : 1;
            __IM  uint32_t RESERVED2  : 5;
            __IOM uint32_t TXGFM      : 1;
        } TXINTMASK_B;
    } ;
    __IM  uint32_t  RESERVED3[14];

    union
    {
        __IM  uint32_t TXGFSCCNT;

        struct
        {
            __IM  uint32_t TXGFSCCNT  : 32;
        } TXGFSCCNT_B;
    } ;

    union
    {
        __IM  uint32_t TXGFMCCNT;

        struct
        {
            __IM  uint32_t TXGFMCCNT  : 32;
        } TXGFMCCNT_B;
    } ;
    __IM  uint32_t  RESERVED4[5];

    union
    {
        __IM  uint32_t TXGFCNT;

        struct
        {
            __IM  uint32_t TXGFCNT    : 32;
        } TXGFCNT_B;
    } ;
    __IM  uint32_t  RESERVED5[10];

    union
    {
        __IM  uint32_t RXFCECNT;

        struct
        {
            __IM  uint32_t RXFCECNT   : 32;
        } RXFCECNT_B;
    } ;

    union
    {
        __IM  uint32_t RXFAECNT;

        struct
        {
            __IM  uint32_t RXFAECNT   : 32;
        } RXFAECNT_B;
    } ;
    __IM  uint32_t  RESERVED6[10];

    union
    {
        __IM  uint32_t RXGUNCNT;

        struct
        {
            __IM  uint32_t RXGUNCNT   : 32;
        } RXGUNCNT_B;
    } ;
    __IM  uint32_t  RESERVED7[334];

    union
    {
        __IOM uint32_t TSCTRL;

        struct
        {
            __IOM uint32_t TSEN       : 1;
            __IOM uint32_t TSUDSEL    : 1;
            __IOM uint32_t TSSTINIT   : 1;
            __IOM uint32_t TSSTUD     : 1;
            __IOM uint32_t TSTRGIEN   : 1;
            __IOM uint32_t TSADDUD    : 1;
        } TSCTRL_B;
    } ;

    union
    {
        __IOM uint32_t SUBSECI;

        struct
        {
            __IOM uint32_t STSUBSECI  : 8;
        } SUBSECI_B;
    } ;

    union
    {
        __IM  uint32_t TSH;

        struct
        {
            __IM  uint32_t STSEC      : 32;
        } TSH_B;
    } ;

    union
    {
        __IM  uint32_t TSL;

        struct
        {
            __IM  uint32_t STSUBSEC   : 31;
            __IM  uint32_t STSEL      : 1;
        } TSL_B;
    } ;

    union
    {
        __IOM uint32_t TSHUD;

        struct
        {
            __IOM uint32_t TSUDSEC    : 32;
        } TSHUD_B;
    } ;

    union
    {
        __IOM uint32_t TSLUD;

        struct
        {
            __IOM uint32_t TSUDSUBSEC : 31;
            __IOM uint32_t TSUDSEL    : 1;
        } TSLUD_B;
    } ;

    union
    {
        __IOM uint32_t TSA;

        struct
        {
            __IOM uint32_t TSA        : 32;
        } TSA_B;
    } ;

    union
    {
        __IOM uint32_t TTSH;

        struct
        {
            __IOM uint32_t TTSH       : 32;
        } TTSH_B;
    } ;

    union
    {
        __IOM uint32_t TTSL;

        struct
        {
            __IOM uint32_t TTSL       : 32;
        } TTSL_B;
    } ;
    __IM  uint32_t  RESERVED8[567];

    union
    {
        __IOM uint32_t DMABMOD;

        struct
        {
            __IOM uint32_t SWR        : 1;
            __IOM uint32_t DAS        : 1;
            __IOM uint32_t DSL        : 5;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t PBL        : 6;
            __IOM uint32_t PR         : 2;
            __IOM uint32_t FB         : 1;
            __IOM uint32_t RPBL       : 6;
            __IOM uint32_t USP        : 1;
            __IOM uint32_t PBLx4      : 1;
            __IOM uint32_t AAL        : 1;
        } DMABMOD_B;
    } ;

    union
    {
        __IOM uint32_t DMATXPD;

        struct
        {
            __IOM uint32_t TXPD       : 32;
        } DMATXPD_B;
    } ;

    union
    {
        __IOM uint32_t DMARXPD;

        struct
        {
            __IOM uint32_t RXPD       : 32;
        } DMARXPD_B;
    } ;

    union
    {
        __IOM uint32_t DMARXDLADDR;

        struct
        {
            __IOM uint32_t RXSTA      : 32;
        } DMARXDLADDR_B;
    } ;

    union
    {
        __IOM uint32_t DMATXDLADDR;

        struct
        {
            __IOM uint32_t TXSTA      : 32;
        } DMATXDLADDR_B;
    } ;

    union
    {
        __IOM uint32_t DMASTS;

        struct
        {
            __IOM uint32_t TXFLG      : 1;
            __IOM uint32_t TXSFLG     : 1;
            __IOM uint32_t TXBU       : 1;
            __IOM uint32_t TXJTO      : 1;
            __IOM uint32_t RXOVF      : 1;
            __IOM uint32_t TXUNF      : 1;
            __IOM uint32_t RXFLG      : 1;
            __IOM uint32_t RXBU       : 1;
            __IOM uint32_t RXSFLG     : 1;
            __IOM uint32_t RXWTOFLG   : 1;
            __IOM uint32_t ETXFLG     : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t FBERRFLG   : 1;
            __IOM uint32_t ERXFLG     : 1;
            __IOM uint32_t AINTS      : 1;
            __IOM uint32_t NINTS      : 1;
            __IM  uint32_t RXSTS      : 3;
            __IM  uint32_t TXSTS      : 3;
            __IM  uint32_t ERRB       : 3;
            __IM  uint32_t RESERVED2  : 1;
            __IM  uint32_t MMCFLG     : 1;
            __IM  uint32_t PMTFLG     : 1;
            __IM  uint32_t TSTFLG     : 1;
        } DMASTS_B;
    } ;

    union
    {
        __IOM uint32_t DMAOPMOD;

        struct
        {
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t STRX       : 1;
            __IOM uint32_t OSECF      : 1;
            __IOM uint32_t RXTHCTRL   : 2;
            __IM  uint32_t RESERVED2  : 1;
            __IOM uint32_t FUF        : 1;
            __IOM uint32_t FERRF      : 1;
            __IM  uint32_t RESERVED3  : 5;
            __IOM uint32_t STTX       : 1;
            __IOM uint32_t TXTHCTRL   : 3;
            __IM  uint32_t RESERVED4  : 3;
            __IOM uint32_t FTXF       : 1;
            __IOM uint32_t TXSF       : 1;
            __IM  uint32_t RESERVED5  : 2;
            __IOM uint32_t DISFRXF    : 1;
            __IOM uint32_t RXSF       : 1;
            __IOM uint32_t DISDT      : 1;
        } DMAOPMOD_B;
    } ;

    union
    {
        __IOM uint32_t DMAINTEN;

        struct
        {
            __IOM uint32_t TXIEN      : 1;
            __IOM uint32_t TXSEN      : 1;
            __IOM uint32_t TXBUEN     : 1;
            __IOM uint32_t TXJTOEN    : 1;
            __IOM uint32_t RXOVFEN    : 1;
            __IOM uint32_t TXUNFEN    : 1;
            __IOM uint32_t RXIEN      : 1;
            __IOM uint32_t RXBUEN     : 1;
            __IOM uint32_t RXSEN      : 1;
            __IOM uint32_t RXWTOEN    : 1;
            __IOM uint32_t ETXIEN     : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t FBERREN    : 1;
            __IOM uint32_t ERXIEN     : 1;
            __IOM uint32_t AINTSEN    : 1;
            __IOM uint32_t NINTSEN    : 1;
        } DMAINTEN_B;
    } ;

    union
    {
        __IM  uint32_t DMAMFABOCNT;

        struct
        {
            __IM  uint32_t MISFCNT    : 16;
            __IM  uint32_t MISFCNTOVF : 1;
            __IM  uint32_t AMISFCNT   : 11;
            __IM  uint32_t OVFCNTOVF  : 1;
        } DMAMFABOCNT_B;
    } ;
    __IM  uint32_t  RESERVED9[9];

    union
    {
        __IM  uint32_t DMAHTXD;

        struct
        {
            __IM  uint32_t HTXDADDRP  : 32;
        } DMAHTXD_B;
    } ;

    union
    {
        __IM  uint32_t DMAHRXD;

        struct
        {
            __IM  uint32_t HRXDADDRP  : 32;
        } DMAHRXD_B;
    } ;

    union
    {
        __IM  uint32_t DMAHTXBADDR;

        struct
        {
            __IM  uint32_t HTXBADDRP  : 32;
        } DMAHTXBADDR_B;
    } ;

    union
    {
        __IM  uint32_t DMAHRXBADDR;

        struct
        {
            __IM  uint32_t HRXBADDRP  : 32;
        } DMAHRXBADDR_B;
    } ;
} ETH_T;

/**@} end of group Peripheral_registers_structures*/

/** @defgroup Peripheral_memory_map
  @{
*/

/* FMC base address in the alias region */
#define FMC_BASE                ((uint32_t)0x08000000)
/* SRAM base address in the alias region */
#define SRAM_BASE               ((uint32_t)0x20000000)
/* Peripheral base address in the alias region */
#define PERIPH_BASE             ((uint32_t)0x40000000)

/* SRAM base address in the bit-band region */
#define SRAM_BB_BASE            ((uint32_t)0x22000000)
/* Peripheral base address in the bit-band region */
#define PERIPH_BB_BASE          ((uint32_t)0x42000000)

/* SMC registers base address */
#define SMC_R_BASE             ((uint32_t)0xA0000000)
/* QSPI registers base address */
#define QSPI_BASE               ((uint32_t)0xA0000000)
/* DMC registers base address */
#define DMC_BASE                ((uint32_t)0xA0000000)

/* Peripheral memory map */
#define APB1PERIPH_BASE         PERIPH_BASE
#define APB2PERIPH_BASE         (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE          (PERIPH_BASE + 0x20000)

#define TMR2_BASE               (APB1PERIPH_BASE + 0x0000)
#define TMR3_BASE               (APB1PERIPH_BASE + 0x0400)
#define TMR4_BASE               (APB1PERIPH_BASE + 0x0800)
#define TMR5_BASE               (APB1PERIPH_BASE + 0x0C00)
#define TMR6_BASE               (APB1PERIPH_BASE + 0x1000)
#define TMR7_BASE               (APB1PERIPH_BASE + 0x1400)
#define TMR12_BASE              (APB1PERIPH_BASE + 0x1800)
#define TMR13_BASE              (APB1PERIPH_BASE + 0x1C00)
#define TMR14_BASE              (APB1PERIPH_BASE + 0x2000)
#define RTC_BASE                (APB1PERIPH_BASE + 0x2800)
#define WWDT_BASE               (APB1PERIPH_BASE + 0x2C00)
#define IWDT_BASE               (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE               (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE               (APB1PERIPH_BASE + 0x3C00)
#define USART2_BASE             (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE             (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE              (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE              (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE               (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE               (APB1PERIPH_BASE + 0x5800)
#define USBD_BASE               (APB1PERIPH_BASE + 0X5C00)
#define CAN1_BASE               (APB1PERIPH_BASE + 0x6400)
#define CAN2_BASE               (APB1PERIPH_BASE + 0x6800)
#define BAKPR_BASE              (APB1PERIPH_BASE + 0x6C00)
#define PMU_BASE                (APB1PERIPH_BASE + 0x7000)
#define DAC_BASE                (APB1PERIPH_BASE + 0x7400)
#define CEC_BASE                (APB1PERIPH_BASE + 0x7800)

#define AFIO_BASE               (APB2PERIPH_BASE + 0x0000)
#define EINT_BASE               (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE              (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE              (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE              (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE              (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE              (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE              (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE              (APB2PERIPH_BASE + 0x2000)
#define ADC1_BASE               (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE               (APB2PERIPH_BASE + 0x2800)
#define TMR1_BASE               (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE               (APB2PERIPH_BASE + 0x3000)
#define TMR8_BASE               (APB2PERIPH_BASE + 0x3400)
#define USART1_BASE             (APB2PERIPH_BASE + 0x3800)
#define ADC3_BASE               (APB2PERIPH_BASE + 0x3C00)
#define TMR15_BASE              (APB2PERIPH_BASE + 0x4000)
#define TMR16_BASE              (APB2PERIPH_BASE + 0x4400)
#define TMR17_BASE              (APB2PERIPH_BASE + 0x4800)
#define TMR9_BASE               (APB2PERIPH_BASE + 0x4C00)
#define TMR10_BASE              (APB2PERIPH_BASE + 0x5000)
#define TMR11_BASE              (APB2PERIPH_BASE + 0x5400)

#define SDIO_BASE               (PERIPH_BASE + 0x18000)

#define DMA1_BASE               (AHBPERIPH_BASE + 0x0000)
#define DMA1_Channel1_BASE      (AHBPERIPH_BASE + 0x0008)
#define DMA1_Channel2_BASE      (AHBPERIPH_BASE + 0x001C)
#define DMA1_Channel3_BASE      (AHBPERIPH_BASE + 0x0030)
#define DMA1_Channel4_BASE      (AHBPERIPH_BASE + 0x0044)
#define DMA1_Channel5_BASE      (AHBPERIPH_BASE + 0x0058)
#define DMA1_Channel6_BASE      (AHBPERIPH_BASE + 0x006C)
#define DMA1_Channel7_BASE      (AHBPERIPH_BASE + 0x0080)
#define DMA2_BASE               (AHBPERIPH_BASE + 0x0400)
#define DMA2_Channel1_BASE      (AHBPERIPH_BASE + 0x0408)
#define DMA2_Channel2_BASE      (AHBPERIPH_BASE + 0x041C)
#define DMA2_Channel3_BASE      (AHBPERIPH_BASE + 0x0430)
#define DMA2_Channel4_BASE      (AHBPERIPH_BASE + 0x0444)
#define DMA2_Channel5_BASE      (AHBPERIPH_BASE + 0x0458)
#define RCM_BASE                (AHBPERIPH_BASE + 0x1000)
#define CRC_BASE                (AHBPERIPH_BASE + 0x3000)

#define ETH_BASE                (AHBPERIPH_BASE + 0x8000)
#define ETH_MAC_BASE            (ETH_BASE)
#define ETH_MMC_BASE            (ETH_BASE + 0x0100)
#define ETH_PTP_BASE            (ETH_BASE + 0x0700)
#define ETH_DMA_BASE            (ETH_BASE + 0x1000)
/* FMC registers base address */
#define FMC_R_BASE              (AHBPERIPH_BASE + 0x2000)
/* FMC Option Bytes base address */
#define OB_BASE                 ((uint32_t)0x1FFFF800)

/* SMC Bank1 registers base address */
#define SMC_Bank1_R_BASE       (SMC_R_BASE + 0x0000)
/* SMC Bank1E registers base address */
#define SMC_Bank1E_R_BASE      (SMC_R_BASE + 0x0104)
/* SMC Bank2 registers base address */
#define SMC_Bank2_R_BASE       (SMC_R_BASE + 0x0060)
/* SMC Bank3 registers base address */
#define SMC_Bank3_R_BASE       (SMC_R_BASE + 0x0080)
/*SMC Bank4 registers base address  */
#define SMC_Bank4_R_BASE       (SMC_R_BASE + 0x00A0)

/* Debug MCU registers base address */
#define DBGMCU_BASE             ((uint32_t)0xE0042000)

/**@} end of group Peripheral_memory_map*/

/** @defgroup Peripheral_declaration
  @{
*/

#define CRC                     ((CRC_T *) CRC_BASE)
#define RTC                     ((RTC_T *) RTC_BASE)
#define PMU                     ((PMU_T *) PMU_BASE)
#define BAKPR                   ((BAKPR_T *) BAKPR_BASE)
#define TMR1                    ((TMR_T *) TMR1_BASE)
#define TMR2                    ((TMR_T *) TMR2_BASE)
#define TMR3                    ((TMR_T *) TMR3_BASE)
#define TMR4                    ((TMR_T *) TMR4_BASE)
#define TMR5                    ((TMR_T *) TMR5_BASE)
#define TMR6                    ((TMR_T *) TMR6_BASE)
#define TMR7                    ((TMR_T *) TMR7_BASE)
#define TMR8                    ((TMR_T *) TMR8_BASE)
#define TMR9                    ((TMR_T *) TMR9_BASE)
#define TMR10                   ((TMR_T *) TMR10_BASE)
#define TMR11                   ((TMR_T *) TMR11_BASE)
#define TMR12                   ((TMR_T *) TMR12_BASE)
#define TMR13                   ((TMR_T *) TMR13_BASE)
#define TMR14                   ((TMR_T *) TMR14_BASE)
#define TMR15                   ((TMR_T *) TMR15_BASE)
#define TMR16                   ((TMR_T *) TMR16_BASE)
#define TMR17                   ((TMR_T *) TMR17_BASE)

#define DMA1                    ((DMA_T *) DMA1_BASE)
#define DMA2                    ((DMA_T *) DMA2_BASE)

#define DMA1_Channel1           ((DMA_Channel_T *) DMA1_Channel1_BASE)
#define DMA1_Channel2           ((DMA_Channel_T *) DMA1_Channel2_BASE)
#define DMA1_Channel3           ((DMA_Channel_T *) DMA1_Channel3_BASE)
#define DMA1_Channel4           ((DMA_Channel_T *) DMA1_Channel4_BASE)
#define DMA1_Channel5           ((DMA_Channel_T *) DMA1_Channel5_BASE)
#define DMA1_Channel6           ((DMA_Channel_T *) DMA1_Channel6_BASE)
#define DMA1_Channel7           ((DMA_Channel_T *) DMA1_Channel7_BASE)

#define DMA2_Channel1           ((DMA_Channel_T *) DMA2_Channel1_BASE)
#define DMA2_Channel2           ((DMA_Channel_T *) DMA2_Channel2_BASE)
#define DMA2_Channel3           ((DMA_Channel_T *) DMA2_Channel3_BASE)
#define DMA2_Channel4           ((DMA_Channel_T *) DMA2_Channel4_BASE)
#define DMA2_Channel5           ((DMA_Channel_T *) DMA2_Channel5_BASE)

#define CAN1                    ((CAN_T *) CAN1_BASE)
#define CAN2                    ((CAN_T *) CAN2_BASE)

#define I2C1                    ((I2C_T *) I2C1_BASE)
#define I2C2                    ((I2C_T *) I2C2_BASE)

#define OB                      ((OB_T *) OB_BASE)

#define ADC1                    ((ADC_T *) ADC1_BASE)
#define ADC2                    ((ADC_T *) ADC2_BASE)
#define ADC3                    ((ADC_T *) ADC3_BASE)

#define EINT                    ((EINT_T *) EINT_BASE)

#define IWDT                    ((IWDT_T *) IWDT_BASE)
#define SDIO                    ((SDIO_T *) SDIO_BASE)
#define DAC                     ((DAC_T *) DAC_BASE)

#define SPI1                    ((SPI_T *) SPI1_BASE)
#define SPI2                    ((SPI_T *) SPI2_BASE)
#define SPI3                    ((SPI_T *) SPI3_BASE)

#define WWDT                    ((WWDT_T *) WWDT_BASE)
#define USART2                  ((USART_T *) USART2_BASE)
#define USART3                  ((USART_T *) USART3_BASE)
#define UART4                   ((USART_T *) UART4_BASE)
#define UART5                   ((USART_T *) UART5_BASE)
#define AFIO                    ((AFIO_T *) AFIO_BASE)
#define GPIOA                   ((GPIO_T *) GPIOA_BASE)
#define GPIOB                   ((GPIO_T *) GPIOB_BASE)
#define GPIOC                   ((GPIO_T *) GPIOC_BASE)
#define GPIOD                   ((GPIO_T *) GPIOD_BASE)
#define GPIOE                   ((GPIO_T *) GPIOE_BASE)
#define GPIOF                   ((GPIO_T *) GPIOF_BASE)
#define GPIOG                   ((GPIO_T *) GPIOG_BASE)
#define USART1                  ((USART_T *) USART1_BASE)
#define RCM                     ((RCM_T *) RCM_BASE)
#define FMC                     ((FMC_T *) FMC_R_BASE)
#define USBD                    ((USBD_T *)USBD_BASE)

#define SMC_Bank1              ((SMC_Bank1_T *) SMC_Bank1_R_BASE)
#define SMC_Bank1E             ((SMC_Bank1E_T *)SMC_Bank1E_R_BASE)
#define SMC_Bank2              ((SMC_Bank2_T *) SMC_Bank2_R_BASE)
#define SMC_Bank3              ((SMC_Bank3_T *) SMC_Bank3_R_BASE)
#define SMC_Bank4              ((SMC_Bank4_T *) SMC_Bank4_R_BASE)

#define DBGMCU                  ((DBGMCU_T *) DBGMCU_BASE)

#define I2C3                    ((SCI2C_T *)(I2C1_BASE))
#define I2C4                    ((SCI2C_T *)(I2C2_BASE))

#if defined (APM32F10X_MD) || defined (APM32F10X_LD)
#define QSPI                    ((QSPI_T *)QSPI_BASE)
#endif
#if defined (APM32F10X_HD)
#define DMC                     ((DMC_T *)DMC_BASE)
#endif

#if defined (APM32F10X_CL)
#define ETH                     ((ETH_T *) ETH_BASE)
#endif

/**@} end of group Peripheral_declaration*/

/** @defgroup Exported_Macros
  @{
*/

/* Define one bit mask */
#define BIT0                    ((uint32_t)0x00000001)
#define BIT1                    ((uint32_t)0x00000002)
#define BIT2                    ((uint32_t)0x00000004)
#define BIT3                    ((uint32_t)0x00000008)
#define BIT4                    ((uint32_t)0x00000010)
#define BIT5                    ((uint32_t)0x00000020)
#define BIT6                    ((uint32_t)0x00000040)
#define BIT7                    ((uint32_t)0x00000080)
#define BIT8                    ((uint32_t)0x00000100)
#define BIT9                    ((uint32_t)0x00000200)
#define BIT10                   ((uint32_t)0x00000400)
#define BIT11                   ((uint32_t)0x00000800)
#define BIT12                   ((uint32_t)0x00001000)
#define BIT13                   ((uint32_t)0x00002000)
#define BIT14                   ((uint32_t)0x00004000)
#define BIT15                   ((uint32_t)0x00008000)
#define BIT16                   ((uint32_t)0x00010000)
#define BIT17                   ((uint32_t)0x00020000)
#define BIT18                   ((uint32_t)0x00040000)
#define BIT19                   ((uint32_t)0x00080000)
#define BIT20                   ((uint32_t)0x00100000)
#define BIT21                   ((uint32_t)0x00200000)
#define BIT22                   ((uint32_t)0x00400000)
#define BIT23                   ((uint32_t)0x00800000)
#define BIT24                   ((uint32_t)0x01000000)
#define BIT25                   ((uint32_t)0x02000000)
#define BIT26                   ((uint32_t)0x04000000)
#define BIT27                   ((uint32_t)0x08000000)
#define BIT28                   ((uint32_t)0x10000000)
#define BIT29                   ((uint32_t)0x20000000)
#define BIT30                   ((uint32_t)0x40000000)
#define BIT31                   ((uint32_t)0x80000000)

#define SET_BIT(REG, BIT)       ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)     ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)      ((REG) & (BIT))

#define CLEAR_REG(REG)          ((REG) = (0x0))

#define WRITE_REG(REG, VAL)     ((REG) = (VAL))

#define READ_REG(REG)           ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**@} end of group Exported_Macros*/
/**@} end of group APM32F10x */
/**@} end of group CMSIS */

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_H */
