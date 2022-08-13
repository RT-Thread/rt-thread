/*!
 * @file        apm32f4xx.h
 *
 * @brief       CMSIS Cortex-M4 Device Peripheral Access Layer Header File.
 *
 * @details     This file contains all the peripheral register's definitions, bits definitions and memory mapping
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __APM32F4XX_H
#define __APM32F4XX_H

#ifdef __cplusplus
  extern "C" {
#endif /* __cplusplus */

/** @addtogroup CMSIS
  @{
*/

/** @defgroup APM32F4xx
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
#define HSE_VALUE                   ((uint32_t)8000000)
#endif

/** Time out for HSE start up */
#define HSE_STARTUP_TIMEOUT         ((uint16_t)0x05000)

/** Value of the Internal oscillator in Hz */
#define HSI_VALUE                   ((uint32_t)16000000)

/**
  * @}
  */

/** @defgroup APM32F4xx_StdPeripheral_Library_Version
  @{
*/

/**
 * @brief Library_Version_Number_Macros
 */
#define __APM32F4XX_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __APM32F4XX_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __APM32F4XX_STDPERIPH_VERSION_SUB2   (0x02) /*!< [15:8]  sub2 version */
#define __APM32F4XX_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __APM32F4XX_STDPERIPH_VERSION        ((__APM32F4XX_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__APM32F4XX_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__APM32F4XX_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__APM32F4XX_STDPERIPH_VERSION_RC))

/**
  * @}
  */

/** @defgroup Configuraion_for_CMSIS
  @{
*/

/** Core revision r0p1 */
#define __CM4_REV                      0x0001
/** APM32 devices provides an MPU */
#define __MPU_PRESENT                  1
/** APM32 uses 4 Bits for the Priority Levels  */
#define __NVIC_PRIO_BITS               4
/** Set to 1 if different SysTick Config is used */
#define __Vendor_SysTickConfig         0
/** APM32 devices provides an FPU */
#define __FPU_PRESENT                  1

/**
 * @brief APM32F4xx Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
typedef enum IRQn
{
    /******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt                           */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                                   */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                                 */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                                    */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                              */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                                    */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                                */

    /******  APM32 specific Interrupt Numbers **********************************************************************/
    WWDT_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
    PVD_IRQn                    = 1,      /*!< PVD through EINT Line detection Interrupt                         */
    TAMP_STAMP_IRQn             = 2,      /*!< Tamper Interrupt                                                  */
    RTC_WKUP_IRQn               = 3,      /*!< RTC global Interrupt                                              */
    FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
    RCM_IRQn                    = 5,      /*!< RCM global Interrupt                                              */
    EINT0_IRQn                  = 6,      /*!< EINT Line0 Interrupt                                              */
    EINT1_IRQn                  = 7,      /*!< EINT Line1 Interrupt                                              */
    EINT2_IRQn                  = 8,      /*!< EINT Line2 Interrupt                                              */
    EINT3_IRQn                  = 9,      /*!< EINT Line3 Interrupt                                              */
    EINT4_IRQn                  = 10,     /*!< EINT Line4 Interrupt                                              */
    DMA1_STR0_IRQn              = 11,     /*!< DMA1 Stream 1 global Interrupt                                    */
    DMA1_STR1_IRQn              = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
    DMA1_STR2_IRQn              = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
    DMA1_STR3_IRQn              = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
    DMA1_STR4_IRQn              = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
    DMA1_STR5_IRQn              = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
    DMA1_STR6_IRQn              = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */

#if defined(APM32F40X)
    ADC_IRQn                    = 18,     /*!< ADC Interrupt                                                     */
    CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupt                                                 */
    CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupt                                                */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
    EINT9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break interrupt and TMR9 global interrupt                    */
    TMR1_UP_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt and TMR10 global interrupt                  */
    TMR1_TRG_COM_TMR11_IRQn     = 26,     /*!< TMR1 Trigger and Commutation Interrupt and TMR11 global interrupt */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                                    */
    TMR2_IRQn                   = 28,     /*!< TMR2 global Interrupt                                             */
    TMR3_IRQn                   = 29,     /*!< TMR3 global Interrupt                                             */
    TMR4_IRQn                   = 30,     /*!< TMR4 global Interrupt                                             */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */
    EINT15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
    RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EINT Line Interrupt                   */
    OTG_FS_WKUP_IRQn            = 42,     /*!< OTG_FS Wakeup through EINT line interrupt                         */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt and TMR12 global interrupt                   */
    TMR8_UP_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt and TMR13 global interrupt                  */
    TMR8_TRG_COM_TMR14_IRQn     = 45,     /*!< TMR8 Trigger and Commutation Interrupt and TMR14 global interrupt */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                                    */
    DMA1_STR7_IRQn              = 47,     /*!< DMA1 Stream 7 Interrupt                                           */
    EMMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                             */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
    TMR5_IRQn                   = 50,     /*!< TMR5 global Interrupt                                             */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
    TMR6_DAC_IRQn               = 54,     /*!< TMR6 global and DAC1&2 underrun error  interrupts                 */
    TMR7_IRQn                   = 55,     /*!< TMR7 global interrupt                                             */
    DMA2_STR0_IRQn              = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
    DMA2_STR1_IRQn              = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
    DMA2_STR2_IRQn              = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
    DMA2_STR3_IRQn              = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
    DMA2_STR4_IRQn              = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
    ETH_IRQn                    = 61,     /*!< Ethernet global Interrupt                                         */
    ETH_WKUP_IRQn               = 62,     /*!< Ethernet Wakeup through EINT line Interrupt                       */
    CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupt                                                 */
    CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupt                                                */
    CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupt                                                */
    CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupt                                                */
    OTG_FS_IRQn                 = 67,     /*!< OTG_FS global Interrupt                                           */
    DMA2_STR5_IRQn              = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
    DMA2_STR6_IRQn              = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
    DMA2_STR7_IRQn              = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
    USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
    I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
    I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
    OTG_HS1_EP1_OUT_IRQn        = 74,     /*!< OTG_HS1 End Point 1 Out global interrupt                          */
    OTG_HS1_EP1_IN_IRQn         = 75,     /*!< OTG_HS1 End Point 1 In global interrupt                           */
    OTG_HS1_WKUP_IRQn           = 76,     /*!< OTG_HS1 Wakeup through EINT interrupt                             */
    OTG_HS1_IRQn                = 77,     /*!< OTG_HS1 global interrupt                                          */
    DCI_IRQn                    = 78,     /*!< DCMI global interrupt                                             */
    FPU_IRQn                    = 81,     /*!< FPU global interrupt                                              */
    SM3_IRQn                    = 82,     /*!< SM3 global interrupt                                              */
    SM4_IRQn                    = 83,     /*!< SM4 global interrupt                                              */
    BN_IRQn                     = 84      /*!< BN global interrupt                                               */
#endif /* APM32F40x */

#if defined(APM32F41X)
    ADC_IRQn                    = 18,     /*!< ADC Interrupt                                                     */
    CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupt                                                 */
    CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupt                                                */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
    EINT9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
    TMR1_BRK_TMR9_IRQn          = 24,     /*!< TMR1 Break interrupt and TMR9 global interrupt                    */
    TMR1_UP_TMR10_IRQn          = 25,     /*!< TMR1 Update Interrupt and TMR10 global interrupt                  */
    TMR1_TRG_COM_TMR11_IRQn     = 26,     /*!< TMR1 Trigger and Commutation Interrupt and TMR11 global interrupt */
    TMR1_CC_IRQn                = 27,     /*!< TMR1 Capture Compare Interrupt                                    */
    TMR2_IRQn                   = 28,     /*!< TMR2 global Interrupt                                             */
    TMR3_IRQn                   = 29,     /*!< TMR3 global Interrupt                                             */
    TMR4_IRQn                   = 30,     /*!< TMR4 global Interrupt                                             */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */
    EINT15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
    RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EINT Line Interrupt                   */
    OTG_FS_WKUP_IRQn            = 42,     /*!< OTG_FS Wakeup through EINT line interrupt                          */
    TMR8_BRK_TMR12_IRQn         = 43,     /*!< TMR8 Break Interrupt and TMR12 global interrupt                   */
    TMR8_UP_TMR13_IRQn          = 44,     /*!< TMR8 Update Interrupt and TMR13 global interrupt                  */
    TMR8_TRG_COM_TMR14_IRQn     = 45,     /*!< TMR8 Trigger and Commutation Interrupt and TMR14 global interrupt */
    TMR8_CC_IRQn                = 46,     /*!< TMR8 Capture Compare Interrupt                                    */
    DMA1_STR7_IRQn              = 47,     /*!< DMA1 Stream 7 Interrupt                                           */
    EMMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                             */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
    TMR5_IRQn                   = 50,     /*!< TMR5 global Interrupt                                             */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
    TMR6_DAC_IRQn               = 54,     /*!< TMR6 global and DAC1&2 underrun error  interrupts                 */
    TMR7_IRQn                   = 55,     /*!< TMR7 global interrupt                                             */
    DMA2_STR0_IRQn              = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
    DMA2_STR1_IRQn              = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
    DMA2_STR2_IRQn              = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
    DMA2_STR3_IRQn              = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
    DMA2_STR4_IRQn              = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
    ETH_IRQn                    = 61,     /*!< Ethernet global Interrupt                                         */
    ETH_WKUP_IRQn               = 62,     /*!< Ethernet Wakeup through EINT line Interrupt                       */
    CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupt                                                 */
    CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupt                                                */
    CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupt                                                */
    CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupt                                                */
    OTG_FS_IRQn                 = 67,     /*!< OTG_FS global Interrupt                                           */
    DMA2_STR5_IRQn              = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
    DMA2_STR6_IRQn              = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
    DMA2_STR7_IRQn              = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
    USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
    I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
    I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
    OTG_HS1_EP1_OUT_IRQn        = 74,     /*!< OTG_HS1 End Point 1 Out global interrupt                          */
    OTG_HS1_EP1_IN_IRQn         = 75,     /*!< OTG_HS1 End Point 1 In global interrupt                           */
    OTG_HS1_WKUP_IRQn           = 76,     /*!< OTG_HS1 Wakeup through EINT interrupt                             */
    OTG_HS1_IRQn                = 77,     /*!< OTG_HS1 global interrupt                                          */
    DCI_IRQn                    = 78,     /*!< DCMI global interrupt                                             */
    CRYP_IRQn                   = 79,     /*!< CRYP crypto global interrupt                                      */
    HASH_RNG_IRQn               = 80,     /*!< Hash and Rng global interrupt                                     */
    FPU_IRQn                    = 81,     /*!< FPU global interrupt                                              */
    SM3_IRQn                    = 82,     /*!< SM3 global interrupt                                              */
    SM4_IRQn                    = 83,     /*!< SM4 global interrupt                                              */
    BN_IRQn                     = 84      /*!< BN global interrupt                                               */
#endif /* APM32F41x */

} IRQn_Type;

/**
  * @}
  */

#include "core_cm4.h"
#include "system_apm32f4xx.h"
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

/**
  * @}
  */

/** @defgroup Peripheral_registers_structures
  @{
*/

/**
* @brief General purpose I/O (GPIO)
*/
typedef struct
{
    /** Port Mode configure register  */
    union
    {
        __IOM uint32_t MODE;

        struct
        {
            __IOM uint32_t MODE0           : 2;
            __IOM uint32_t MODE1           : 2;
            __IOM uint32_t MODE2           : 2;
            __IOM uint32_t MODE3           : 2;
            __IOM uint32_t MODE4           : 2;
            __IOM uint32_t MODE5           : 2;
            __IOM uint32_t MODE6           : 2;
            __IOM uint32_t MODE7           : 2;
            __IOM uint32_t MODE8           : 2;
            __IOM uint32_t MODE9           : 2;
            __IOM uint32_t MODE10          : 2;
            __IOM uint32_t MODE11          : 2;
            __IOM uint32_t MODE12          : 2;
            __IOM uint32_t MODE13          : 2;
            __IOM uint32_t MODE14          : 2;
            __IOM uint32_t MODE15          : 2;
        } MODE_B;
    } ;

    /** Port Output Type configure register  */
    union
    {
        __IOM uint32_t OMODE;

        struct
        {
            __IOM uint32_t OMODE0           : 1;
            __IOM uint32_t OMODE1           : 1;
            __IOM uint32_t OMODE2           : 1;
            __IOM uint32_t OMODE3           : 1;
            __IOM uint32_t OMODE4           : 1;
            __IOM uint32_t OMODE5           : 1;
            __IOM uint32_t OMODE6           : 1;
            __IOM uint32_t OMODE7           : 1;
            __IOM uint32_t OMODE8           : 1;
            __IOM uint32_t OMODE9           : 1;
            __IOM uint32_t OMODE10          : 1;
            __IOM uint32_t OMODE11          : 1;
            __IOM uint32_t OMODE12          : 1;
            __IOM uint32_t OMODE13          : 1;
            __IOM uint32_t OMODE14          : 1;
            __IOM uint32_t OMODE15          : 1;
            __IOM uint32_t RESERVED         : 16;
        } OMODE_B;
    } ;

    /** Port Output Speed configure register  */
    union
    {
        __IOM uint32_t OSSEL;

        struct
        {
            __IOM uint32_t OSSEL0           : 2;
            __IOM uint32_t OSSEL1           : 2;
            __IOM uint32_t OSSEL2           : 2;
            __IOM uint32_t OSSEL3           : 2;
            __IOM uint32_t OSSEL4           : 2;
            __IOM uint32_t OSSEL5           : 2;
            __IOM uint32_t OSSEL6           : 2;
            __IOM uint32_t OSSEL7           : 2;
            __IOM uint32_t OSSEL8           : 2;
            __IOM uint32_t OSSEL9           : 2;
            __IOM uint32_t OSSEL10          : 2;
            __IOM uint32_t OSSEL11          : 2;
            __IOM uint32_t OSSEL12          : 2;
            __IOM uint32_t OSSEL13          : 2;
            __IOM uint32_t OSSEL14          : 2;
            __IOM uint32_t OSSEL15          : 2;
        } OSSEL_B;
    } ;

    /**  port pull-up/pull-down register  */
    union
    {
        __IOM uint32_t PUPD;

        struct
        {
            __IOM uint32_t PUPD0            : 2;
            __IOM uint32_t PUPD1            : 2;
            __IOM uint32_t PUPD2            : 2;
            __IOM uint32_t PUPD3            : 2;
            __IOM uint32_t PUPD4            : 2;
            __IOM uint32_t PUPD5            : 2;
            __IOM uint32_t PUPD6            : 2;
            __IOM uint32_t PUPD7            : 2;
            __IOM uint32_t PUPD8            : 2;
            __IOM uint32_t PUPD9            : 2;
            __IOM uint32_t PUPD10           : 2;
            __IOM uint32_t PUPD11           : 2;
            __IOM uint32_t PUPD12           : 2;
            __IOM uint32_t PUPD13           : 2;
            __IOM uint32_t PUPD14           : 2;
            __IOM uint32_t PUPD15           : 2;
        } PUPD_B;
    } ;

    /** Port data in register */
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

    /** Port data output register */
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

    /**GPIO port bit set/clear register*/
    union
    {
        __OM  uint16_t BSCL;

        struct
        {
            __OM  uint16_t BS0        : 1;
            __OM  uint16_t BS1        : 1;
            __OM  uint16_t BS2        : 1;
            __OM  uint16_t BS3        : 1;
            __OM  uint16_t BS4        : 1;
            __OM  uint16_t BS5        : 1;
            __OM  uint16_t BS6        : 1;
            __OM  uint16_t BS7        : 1;
            __OM  uint16_t BS8        : 1;
            __OM  uint16_t BS9        : 1;
            __OM  uint16_t BS10       : 1;
            __OM  uint16_t BS11       : 1;
            __OM  uint16_t BS12       : 1;
            __OM  uint16_t BS13       : 1;
            __OM  uint16_t BS14       : 1;
            __OM  uint16_t BS15       : 1;
        } BSCL_B;
    } ;

    union
    {
        __OM  uint16_t BSCH;

        struct
        {
            __OM  uint16_t BC0        : 1;
            __OM  uint16_t BC1        : 1;
            __OM  uint16_t BC2        : 1;
            __OM  uint16_t BC3        : 1;
            __OM  uint16_t BC4        : 1;
            __OM  uint16_t BC5        : 1;
            __OM  uint16_t BC6        : 1;
            __OM  uint16_t BC7        : 1;
            __OM  uint16_t BC8        : 1;
            __OM  uint16_t BC9        : 1;
            __OM  uint16_t BC10       : 1;
            __OM  uint16_t BC11       : 1;
            __OM  uint16_t BC12       : 1;
            __OM  uint16_t BC13       : 1;
            __OM  uint16_t BC14       : 1;
            __OM  uint16_t BC15       : 1;
        } BSCH_B;
    };

    /** Port configuration lock register */
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
            __IM  uint32_t RESERVED        : 15;
        } LOCK_B;
    };

    /**  Port Alternate Function Low register  */
    union
    {
        __IOM uint32_t ALFL;

        struct
        {
            __IOM uint32_t ALFSEL0         : 4;
            __IOM uint32_t ALFSEL1         : 4;
            __IOM uint32_t ALFSEL2         : 4;
            __IOM uint32_t ALFSEL3         : 4;
            __IOM uint32_t ALFSEL4         : 4;
            __IOM uint32_t ALFSEL5         : 4;
            __IOM uint32_t ALFSEL6         : 4;
            __IOM uint32_t ALFSEL7         : 4;
        } ALFL_B;
    };

    /**  Port alternate function High register  */
    union
    {
        __IOM uint32_t ALFH;

        struct
        {
            __IOM uint32_t ALFSEL8         : 4;
            __IOM uint32_t ALFSEL9         : 4;
            __IOM uint32_t ALFSEL10        : 4;
            __IOM uint32_t ALFSEL11        : 4;
            __IOM uint32_t ALFSEL12        : 4;
            __IOM uint32_t ALFSEL13        : 4;
            __IOM uint32_t ALFSEL14        : 4;
            __IOM uint32_t ALFSEL15        : 4;
        } ALFH_B;
    };
} GPIO_T;

/**
 * @brief Reset and clock management unit (RCM)
 */
typedef struct
{
    /** Clock control register */
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
            __IM  uint32_t RESERVED3       : 4;
        } CTRL_B;
    };

    /** PLL1 configuration register */
    union
    {
        __IOM uint32_t PLL1CFG;

        struct
        {
            __IOM uint32_t PLLB            : 6;
            __IOM uint32_t PLL1A           : 9;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t PLL1C           : 2;
            __IM  uint32_t RESERVED2       : 4;
            __IOM uint32_t PLL1CLKS        : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t PLLD            : 4;
            __IM  uint32_t RESERVED4       : 4;
        } PLL1CFG_B;
    } ;

    /** Clock configuration register */
    union
    {
        __IOM uint32_t CFG;

        struct
        {
            __IOM uint32_t SCLKSEL         : 2;
            __IM  uint32_t SCLKSWSTS       : 2;
            __IOM uint32_t AHBPSC          : 4;
            __IOM uint32_t SDRAMPSC        : 2;
            __IOM uint32_t APB1PSC         : 3;
            __IOM uint32_t APB2PSC         : 3;
            __IOM uint32_t RTCPSC          : 5;
            __IOM uint32_t MCO1SEL         : 2;
            __IOM uint32_t I2SSEL          : 1;
            __IOM uint32_t MCO1PRE         : 3;
            __IOM uint32_t MCO2PRE         : 3;
            __IOM uint32_t MCO2SEL         : 2;
        } CFG_B;
    } ;

    /** Clock interrupt control register */
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
            __IM  uint32_t RESERVED1       : 1;
            __IM  uint32_t CSSFLG          : 1;
            __IOM uint32_t LSIRDYEN        : 1;
            __IOM uint32_t LSERDYEN        : 1;
            __IOM uint32_t HSIRDYEN        : 1;
            __IOM uint32_t HSERDYEN        : 1;
            __IOM uint32_t PLL1RDYEN       : 1;
            __IOM uint32_t PLL2RDYEN       : 1;
            __IM  uint32_t RESERVED2       : 2;
            __OM  uint32_t LSIRDYCLR       : 1;
            __OM  uint32_t LSERDYCLR       : 1;
            __OM  uint32_t HSIRDYCLR       : 1;
            __OM  uint32_t HSERDYCLR       : 1;
            __OM  uint32_t PLL1RDYCLR      : 1;
            __OM  uint32_t PLL2RDYCLR      : 1;
            __IM  uint32_t RESERVED3       : 1;
            __OM  uint32_t CSSCLR          : 1;
            __IM  uint32_t RESERVED4       : 8;
        } INT_B;
    } ;

    /** AHB1 peripheral reset register */
    union
    {
        __IOM uint32_t AHB1RST;

        struct
        {
            __IOM uint32_t PARST           : 1;
            __IOM uint32_t PBRST           : 1;
            __IOM uint32_t PCRST           : 1;
            __IOM uint32_t PDRST           : 1;
            __IOM uint32_t PERST           : 1;
            __IOM uint32_t PFRST           : 1;
            __IOM uint32_t PGRST           : 1;
            __IOM uint32_t PHRST           : 1;
            __IOM uint32_t PIRST           : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t CRCRST          : 1;
            __IM  uint32_t RESERVED2       : 8;
            __IOM uint32_t DMA1RST         : 1;
            __IOM uint32_t DMA2RST         : 1;
            __IM  uint32_t RESERVED3       : 2;
            __IOM uint32_t ETHRST          : 1;
            __IM  uint32_t RESERVED4       : 3;
            __IOM uint32_t OTG_HS1RST        : 1;
            __IM  uint32_t RESERVED5       : 2;
        } AHB1RST_B;
    } ;

    /** AHB2 peripheral reset register */
    union
    {
        __IOM uint32_t AHB2RST;

        struct
        {
            __IOM uint32_t DCIRST          : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t CRYPRST         : 1;
            __IOM uint32_t HASHP           : 1;
            __IOM uint32_t RNGRST          : 1;
            __IOM uint32_t OTG_FSRST        : 1;
            __IM  uint32_t RESERVED2       : 24;
        } AHB2RST_B;
    } ;

    /** AHB3 peripheral reset register */
    union
    {
        __IOM uint32_t AHB3RST;

        struct
        {
            __IOM uint32_t EMMCRST         : 1;
            __IM  uint32_t RESERVED        : 31;
        } AHB3RST_B;
    } ;

    __IM  uint32_t  RESERVED;

    /** APB1 peripheral reset register */
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
            __IOM uint32_t TMR12RST        : 1;
            __IOM uint32_t TMR13RST        : 1;
            __IOM uint32_t TMR14RST        : 1;
            __IM  uint32_t RESERVED1       : 2;
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
            __IOM uint32_t I2C3RST         : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t CAN1RST         : 1;
            __IM  uint32_t CAN2RST         : 1;
            __IM  uint32_t RESERVED5       : 1;
            __IOM uint32_t PMURST          : 1;
            __IOM uint32_t DACRST          : 1;
            __IM  uint32_t RESERVED6       : 2;
        } APB1RST_B;
    } ;

    /** APB2 peripheral reset register */
    union
    {
        __IOM uint32_t APB2RST;

        struct
        {
            __IOM uint32_t TMR1RST         : 1;
            __IOM uint32_t TMR8RST         : 1;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t USART1RST       : 1;
            __IOM uint32_t USART6RST       : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t ADCRST          : 1;
            __IM  uint32_t RESERVED3       : 2;
            __IOM uint32_t SDIORST         : 1;
            __IOM uint32_t SPI1RST         : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t SYSCFGRST       : 1;
            __IM  uint32_t RESERVED5       : 1;
            __IOM uint32_t TMR9RST         : 1;
            __IOM uint32_t TMR10RST        : 1;
            __IOM uint32_t TMR11RST        : 1;
            __IM  uint32_t RESERVED6       : 13;
        } APB2RST_B;
    } ;

    __IM  uint32_t  RESERVED1[2];

    /** AHB1 clock enable register */
    union
    {
        __IOM uint32_t AHB1CLKEN;

        struct
        {
            __IOM uint32_t PAEN            : 1;
            __IOM uint32_t PBEN            : 1;
            __IOM uint32_t PCEN            : 1;
            __IOM uint32_t PDEN            : 1;
            __IOM uint32_t PEEN            : 1;
            __IOM uint32_t PFEN            : 1;
            __IOM uint32_t PGEN            : 1;
            __IOM uint32_t PHEN            : 1;
            __IOM uint32_t PIEN            : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t CRCEN           : 1;
            __IM  uint32_t RESERVED2       : 5;
            __IOM uint32_t BAKPSRAMEN      : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t DRAMEN          : 1;
            __IOM uint32_t DMA1EN          : 1;
            __IOM uint32_t DMA2EN          : 1;
            __IM  uint32_t RESERVED4       : 2;
            __IOM uint32_t ETHEN           : 1;
            __IOM uint32_t ETHTXEN         : 1;
            __IOM uint32_t ETHRXEN         : 1;
            __IOM uint32_t ETHPTPEN        : 1;
            __IOM uint32_t OTG_HS1EN         : 1;
            __IOM uint32_t HSULPIEN        : 1;
            __IM  uint32_t RESERVED5       : 1;
        } AHB1CLKEN_B;
    } ;

    /** AHB2 clock enable register */
    union
    {
        __IOM uint32_t AHB2CLKEN;

        struct
        {
            __IOM uint32_t DCIEN           : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t CRYPEN          : 1;
            __IOM uint32_t HASHP           : 1;
            __IOM uint32_t RNGEN           : 1;
            __IOM uint32_t OTG_FSEN         : 1;
            __IM  uint32_t RESERVED2       : 24;
        } AHB2CLKEN_B;
    };

    /** AHB3 peripheral enable register */
    union
    {
        __IOM uint32_t AHB3CLKEN;

        struct
        {
            __IOM uint32_t EMMCEN          : 1;
            __IM  uint32_t RESERVED        : 31;
        } AHB3CLKEN_B;
    } ;

    __IM  uint32_t  RESERVED2;

    /** APB1 peripheral enable register */
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
            __IOM uint32_t TMR12EN         : 1;
            __IOM uint32_t TMR13EN         : 1;
            __IOM uint32_t TMR14EN         : 1;
            __IM  uint32_t RESERVED1       : 2;
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
            __IOM uint32_t I2C3EN          : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t CAN1EN          : 1;
            __IM  uint32_t CAN2EN          : 1;
            __IM  uint32_t RESERVED5       : 1;
            __IOM uint32_t PMUEN           : 1;
            __IOM uint32_t DACEN           : 1;
            __IM  uint32_t RESERVED6       : 2;
        } APB1CLKEN_B;
    } ;

    /** APB2 peripheral enable register */
    union
    {
        __IOM uint32_t APB2CLKEN;

        struct
        {
            __IOM uint32_t TMR1EN          : 1;
            __IOM uint32_t TMR8EN          : 1;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t USART1EN        : 1;
            __IOM uint32_t USART6EN        : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t ADC1EN          : 1;
            __IOM uint32_t ADC2EN          : 1;
            __IOM uint32_t ADC3EN          : 1;
            __IOM uint32_t SDIOEN          : 1;
            __IOM uint32_t SPI1EN          : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t SYSCFGEN        : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t TMR9EN          : 1;
            __IOM uint32_t TMR10EN         : 1;
            __IOM uint32_t TMR11EN         : 1;
            __IM  uint32_t RESERVED5       : 13;
        } APB2CLKEN_B;
    } ;

    __IM  uint32_t  RESERVED3[2];

    /** AHB1 clock enable register during lowpower mode */
    union
    {
        __IOM uint32_t LPAHB1CLKEN;

        struct
        {
            __IOM uint32_t PAEN            : 1;
            __IOM uint32_t PBEN            : 1;
            __IOM uint32_t PCEN            : 1;
            __IOM uint32_t PDEN            : 1;
            __IOM uint32_t PEEN            : 1;
            __IOM uint32_t PFEN            : 1;
            __IOM uint32_t PGEN            : 1;
            __IOM uint32_t PHEN            : 1;
            __IOM uint32_t PIEN            : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t CRCEN           : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t FMCEN           : 1;
            __IOM uint32_t SRAM1EN         : 1;
            __IOM uint32_t SRAM2EN         : 1;
            __IOM uint32_t BAKPSRAMEN      : 1;
            __IM  uint32_t RESERVED3       : 2;
            __IOM uint32_t DMA1EN          : 1;
            __IOM uint32_t DMA2EN          : 1;
            __IM  uint32_t RESERVED4       : 2;
            __IOM uint32_t ETHEN           : 1;
            __IOM uint32_t ETHTXEN         : 1;
            __IOM uint32_t ETHRXEN         : 1;
            __IOM uint32_t ETHPTPEN        : 1;
            __IOM uint32_t OTG_HS1EN         : 1;
            __IOM uint32_t HSULPIEN        : 1;
            __IM  uint32_t RESERVED5       : 1;
        } LPAHB1CLKEN_B;
    } ;

    /** AHB2 clock enable register during lowpower mode */
    union
    {
        __IOM uint32_t LPAHB2CLKEN;

        struct
        {
            __IOM uint32_t DCIEN           : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t CRYPEN          : 1;
            __IOM uint32_t HASHPEN         : 1;
            __IOM uint32_t RNGEN           : 1;
            __IOM uint32_t OTG_FSEN         : 1;
            __IM  uint32_t RESERVED2       : 24;
        } LPAHB2CLKEN_B;
    };

    /** AHB3 peripheral enable register during lowpower mode */
    union
    {
        __IOM uint32_t LPAHB3CLKEN;

        struct
        {
            __IOM uint32_t EMMCEN          : 1;
            __IM  uint32_t RESERVED        : 31;
        } LPAHB3CLKEN_B;
    } ;

    __IM  uint32_t  RESERVED4;

    /** APB1 peripheral enable register during lowpower mode */
    union
    {
        __IOM uint32_t LPAPB1CLKEN;

        struct
        {
            __IOM uint32_t TMR2EN          : 1;
            __IOM uint32_t TMR3EN          : 1;
            __IOM uint32_t TMR4EN          : 1;
            __IOM uint32_t TMR5EN          : 1;
            __IOM uint32_t TMR6EN          : 1;
            __IOM uint32_t TMR7EN          : 1;
            __IOM uint32_t TMR12EN         : 1;
            __IOM uint32_t TMR13EN         : 1;
            __IOM uint32_t TMR14EN         : 1;
            __IM  uint32_t RESERVED1       : 2;
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
            __IOM uint32_t I2C3EN          : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t CAN1EN          : 1;
            __IM  uint32_t CAN2EN          : 1;
            __IM  uint32_t RESERVED5       : 1;
            __IOM uint32_t PMUEN           : 1;
            __IOM uint32_t DACEN           : 1;
            __IM  uint32_t RESERVED6       : 2;
        } LPAPB1CLKEN_B;
    } ;

    /** APB2 peripheral enable register during lowpower mode */
    union
    {
        __IOM uint32_t LPAPB2CLKEN;

        struct
        {
            __IOM uint32_t TMR1EN          : 1;
            __IOM uint32_t TMR8EN          : 1;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t USART1EN        : 1;
            __IOM uint32_t USART6EN        : 1;
            __IM  uint32_t RESERVED2       : 2;
            __IOM uint32_t ADC1EN          : 1;
            __IOM uint32_t ADC2EN          : 1;
            __IOM uint32_t ADC3EN          : 1;
            __IOM uint32_t SDIOEN          : 1;
            __IOM uint32_t SPI1EN          : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t SYSCFGEN        : 1;
            __IM  uint32_t RESERVED4       : 1;
            __IOM uint32_t TMR9EN          : 1;
            __IOM uint32_t TMR10EN         : 1;
            __IOM uint32_t TMR11EN         : 1;
            __IM  uint32_t RESERVED5       : 13;
        } LPAPB2CLKEN_B;
    } ;

    __IM  uint32_t  RESERVED5[2];

    /** Backup domain control register */
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

    /** Control/status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IOM uint32_t LSIEN           : 1;
            __IM  uint32_t LSIRDYFLG       : 1;
            __IM  uint32_t RESERVED        : 22;
            __IOM uint32_t RSTFLGCLR       : 1;
            __IM  uint32_t BORRSTFLG       : 1;
            __IM  uint32_t PINRSTFLG       : 1;
            __IM  uint32_t PODRSTFLG       : 1;
            __IM  uint32_t SWRSTFLG        : 1;
            __IM  uint32_t IWDTRSTFLG      : 1;
            __IM  uint32_t WWDTRSTFLG      : 1;
            __IM  uint32_t LPWRRSTFLG      : 1;
        } CSTS_B;
    } ;

    __IM  uint32_t  RESERVED6[2];

    /** spread spectrum clock generation register */
    union
    {
        __IOM uint32_t SSCCFG;

        struct
        {
            __IOM uint32_t MODPCFG         : 13;
            __IOM uint32_t STEP            : 15;
            __IM  uint32_t RESERVED        : 2;
            __IOM uint32_t SSSEL           : 1;
            __IM  uint32_t SSEN            : 1;
        } SSCCFG_B;
    } ;

    /** PLL2 configuration register */
    union
    {
        __IOM uint32_t PLL2CFG;

        struct
        {
            __IM  uint32_t RESERVED1       : 6;
            __IOM uint32_t PLL2A           : 9;
            __IM  uint32_t RESERVED2       : 13;
            __IOM uint32_t PLL2C           : 3;
            __IM  uint32_t RESERVED3       : 1;
        } PLL2CFG_B;
    } ;
} RCM_T;

/**
 * @brief Universal synchronous asynchronous receiver transmitter (USART)
 */
typedef struct
{
    /** Status register */
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

    /** TX Buffer Data Register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA            : 9;
            __IM  uint32_t RESERVED        : 23;
        } DATA_B;
    } ;

    /** Baud rate register */
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

    /** Control register 1 */
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
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t OSMCFG          : 1;
            __IM  uint32_t RESERVED2       : 16;
        } CTRL1_B;
    } ;

    /** Control register 2 */
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

    /** Control register 3 */
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
            __IOM uint32_t SAMCFG          : 1;
            __IM  uint32_t RESERVED        : 20;
        } CTRL3_B;
    } ;

    /** Guard TMRe and divider number register */
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
  * @brief FLASH Registers (FMC)
  */

typedef struct
{

    /** Flash access control register  */
    union
    {
        __IOM uint32_t ACCTRL;

        struct
        {
            __IOM uint32_t WAITP      : 3;
            __IM  uint32_t RESERVED1  : 5;
            __IOM uint32_t PREFEN     : 1;
            __IOM uint32_t ICACHEEN   : 1;
            __IOM uint32_t DCACHEEN   : 1;
            __OM  uint32_t ICACHERST  : 1;
            __IOM uint32_t DCACHERST  : 1;
            __IM  uint32_t RESERVED2  : 19;
        } ACCTRL_B;
    } ;

    /** Flash key register  */
    union
    {
        __OM  uint32_t KEY;

        struct
        {
            __OM  uint32_t KEY        : 32;
        } KEY_B;
    } ;

    /** Flash option key register   */
    union
    {
        __OM   uint32_t OPTKEY;

        struct
        {
            __OM  uint32_t OPTKEY      : 32;
        } OPTKEY_B;
    } ;

    /** Flash status register  */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM uint32_t OPRCMP     : 1;
            __IOM uint32_t OPRERR     : 1;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t WPROTERR   : 1;
            __IOM uint32_t PGALGERR   : 1;
            __IOM uint32_t PGPRLERR   : 1;
            __IOM uint32_t PGSEQERR   : 1;
            __IM  uint32_t RESERVED2  : 8;
            __IM  uint32_t BUSY       : 1;
            __IM  uint32_t RESERVED3  : 15;
        } STS_B;
    } ;

    /** Flash control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t PG         : 1;
            __IOM uint32_t SERS       : 1;
            __IOM uint32_t MERS       : 1;
            __IOM uint32_t SNUM       : 4;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t PGSIZE     : 2;
            __IM  uint32_t RESERVED2  : 6;
            __IOM uint32_t START      : 1;
            __IM  uint32_t RESERVED3  : 7;
            __IOM uint32_t OPCINTEN   : 1;
            __IOM uint32_t ERRINTEN   : 1;
            __IM  uint32_t RESERVED4  : 5;
            __IOM uint32_t LOCK       : 1;
        } CTRL_B;
    } ;

    /** Option byte register */
    union
    {
        __IOM  uint32_t OPTCTRL;

        struct
        {
            __IOM uint32_t OPTLOCK    : 1;
            __IOM uint32_t OPTSTART   : 1;
            __IOM uint32_t BORLVL     : 2;
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t WDTSEL     : 1;
            __IOM uint32_t RSTSTOP    : 1;
            __IOM uint32_t RSTSTDB    : 1;
            __IOM uint32_t RPROT      : 8;
            __IOM uint32_t NWPROT     : 12;
            __IM  uint32_t RESERVED2  : 4;
        } OPTCTRL_B;
    } ;
} FMC_T;

/**
 * @brief  CRC calculation unit (CRC)
 */
typedef struct
{
    /** @brief  DATA register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA            : 32;
        } DATA_B;
    } ;

    /** @brief independent DATA register */
    union
    {
        __IOM  uint32_t INDATA;

        struct
        {
            __IOM uint32_t INDATA          : 8;
            __IM  uint32_t RESERVED        : 24;
        } INDATA_B;
    };

    /** @brief Countrol register */
    union
    {
        __OM uint32_t CTRL;

        struct
        {
            __OM  uint32_t RST             : 1;
            __IM  uint32_t RESERVED        : 31;
        } CTRL_B;
    };
} CRC_T;

/**
  * @brief Real-time clock (RTC)
  */
typedef struct
{

    /** time register */
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

    /** date register */
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

    /** control register */
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
            __IOM uint32_t DCALEN     : 1;
            __IOM uint32_t ALRAEN     : 1;
            __IOM uint32_t ALRBEN     : 1;
            __IOM uint32_t WUTEN      : 1;
            __IOM uint32_t TSEN       : 1;
            __IOM uint32_t ALRAIEN    : 1;
            __IOM uint32_t ALRBIEN    : 1;
            __IOM uint32_t WUTIEN     : 1;
            __IOM uint32_t TSIEN      : 1;
            __IOM uint32_t STCCFG     : 1;
            __IOM uint32_t WTCCFG     : 1;
            __IOM uint32_t BAKP       : 1;
            __IOM uint32_t CALOSEL    : 1;
            __IOM uint32_t POLCFG     : 1;
            __IOM uint32_t OUTSEL     : 2;
            __IOM uint32_t CALOEN     : 1;
            __IM  uint32_t RESERVED1  : 8;
        } CTRL_B;
    } ;

    /** initialization and status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t ALRAWFLG   : 1;
            __IM  uint32_t ALRBWFLG   : 1;
            __IOM uint32_t WUTWFLG    : 1;
            __IOM uint32_t SOPFLG     : 1;
            __IM  uint32_t INITSFLG   : 1;
            __IOM uint32_t RSFLG      : 1;
            __IM  uint32_t RINITFLG   : 1;
            __IOM uint32_t INITEN     : 1;
            __IOM uint32_t ALRAFLG    : 1;
            __IOM uint32_t ALRBFLG    : 1;
            __IOM uint32_t WUTFLG     : 1;
            __IOM uint32_t TSFLG      : 1;
            __IOM uint32_t TSOVRFLG   : 1;
            __IOM uint32_t TP1FLG     : 1;
            __IOM uint32_t TP2FLG     : 1;
            __IM  uint32_t RESERVED1  : 1;
            __IM  uint32_t RCALPFLG   : 1;
            __IM  uint32_t RESERVED2  : 15;
        } STS_B;
    } ;

    /** prescaler register */
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

    /** auto-reload register */
    union
    {
        __IOM uint32_t AUTORLD;

        struct
        {
            __IOM uint32_t WUAUTORE   : 16;
            __IM  uint32_t RESERVED   : 16;
        } AUTORLD_B;
    } ;

    /** calibration register */
    union
    {
        __IOM uint32_t DCAL;

        struct
        {
            __IOM uint32_t DCAL       : 5;
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t DCALCFG    : 1;
            __IM  uint32_t RESERVED2  : 24;
        } DCAL_B;
    } ;

    /** alarm A register */
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

    /** alarm B register */
    union
    {
        __IOM uint32_t ALRMB;

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
        } ALRMB_B;
    } ;

    /** write protection register */
    union
    {
        __OM  uint32_t WRPROT;

        struct
        {
            __OM  uint32_t KEY        : 16;
            __IM  uint32_t RESERVED   : 16;
        } WRPROT_B;
    } ;

    /** sub second register */
    union
    {
        __IM  uint32_t SUBSEC;

        struct
        {
            __IM  uint32_t SUBSEC     : 16;
            __IM  uint32_t RESERVED   : 16;
        } SUBSEC_B;
    } ;

    /** shift control register */
    union
    {
        __OM  uint32_t SHIFT;

        struct
        {
            __OM  uint32_t SFSEC      : 15;
            __IM  uint32_t RESERVED   : 16;
            __OM  uint32_t ADD1SECEN  : 1;
        } SHIFT_B;
    } ;

    /** timestamp time register */
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

    /** timestamp date register */
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

    /** time-stamp sub second register */
    union
    {
        __IM  uint32_t TSSUBSEC;

        struct
        {
            __IM  uint32_t SUBSEC     : 16;
            __IM  uint32_t RESERVED1  : 16;
        } TSSUBSEC_B;
    } ;

    /** calibration register */
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

    /** tamper and alternate function configuration register */
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
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t TPTSEN     : 1;
            __IOM uint32_t TPSFSEL    : 3;
            __IOM uint32_t TPFCSEL    : 2;
            __IOM uint32_t TPPRDUSEL  : 2;
            __IOM uint32_t TPPUDIS    : 1;
            __IOM uint32_t TP1MSEL    : 1;
            __IOM uint32_t TSMSEL     : 1;
            __IOM uint32_t ALRMOT     : 1;
            __IM  uint32_t RESERVED2  : 13;
        } TACFG_B;
    } ;

    /** alarm A sub second register */
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

    /** alarm B sub second register */
    union
    {
        __IOM uint32_t ALRMBSS;

        struct
        {
            __IOM uint32_t SUBSEC     : 15;
            __IM  uint32_t RESERVED1  : 9;
            __IOM uint32_t MASKSEL    : 4;
            __IM  uint32_t RESERVED2  : 4;
        } ALRMBSS_B;
    } ;

    __IM  uint32_t  RESERVED;

    /** backup register */
    __IOM uint32_t BAKP[20];

} RTC_T;

/**
 * @brief Power Management Unit(PMU)
 */
typedef struct
{
    /** @brief Control register */
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
            __IOM uint32_t FPDSM           : 1;
            __IM  uint32_t RESERVED1       : 4;
            __IOM uint32_t VOSSEL          : 1;
            __IM  uint32_t RESERVED2       : 17;
        } CTRL_B;
    };

    /** @brief PMU Status register */
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IM  uint32_t WUEFLG          : 1;
            __IM  uint32_t SBFLG           : 1;
            __IM  uint32_t PVDOFLG         : 1;
            __IM  uint32_t BKPRFLG         : 1;
            __IM  uint32_t RESERVED1       : 4;
            __IOM uint32_t WKUPCFG         : 1;
            __IOM uint32_t BKPREN          : 1;
            __IM  uint32_t RESERVED2       : 4;
            __IOM uint32_t VOSRFLG         : 1;
            __IM  uint32_t RESERVED3       : 17;
        } CSTS_B;
    };
} PMU_T;

/**
 * @brief Timer register(TMR)
 */
typedef struct
{
    /** control register 1 */
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
            __IM  uint32_t RESERVED   : 22;
        } CTRL1_B;
    } ;

    /** control register 2 */
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

    /** slave mode control register */
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
            __IM  uint32_t RESERVED   : 16;
        } SMCTRL_B;
    } ;

    /** DMA/Interrupt enable register */
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
            __IM  uint32_t RESERVED   : 17;
        } DIEN_B;
    } ;

    /** status register */
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

    /** event generation register */
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
            __IM  uint32_t RESERVED   : 24;
        } CEG_B;
    } ;

    /** @brief Capture the compare mode register 1 */
    union
    {
        __IOM uint32_t CCM1;

        /** @brief Compare mode */
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

        /** @brief Capture mode */
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

    /** @brief Capture the compare mode register 2 */
    union
    {
        __IOM uint32_t CCM2;

        /** @brief Compare mode */
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

        /** @brief Capture mode */
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

    /** capture/compare enable register */
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
            __IM  uint32_t RESERVED   : 18;
        } CCEN_B;
    } ;

    /** counter */
    union
    {
        __IOM uint32_t CNT;

        struct
        {
            __IOM uint32_t CNT        : 32;
        } CNT_B;
    } ;

    /** prescaler */
    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM uint32_t PSC        : 16;
            __IM  uint32_t RESERVED   : 16;
        } PSC_B;
    } ;

    /** auto-reload register */
    union
    {
        __IOM uint32_t AUTORLD;

        struct
        {
            __IOM uint32_t AUTORLD    : 32;
        } AUTORLD_B;
    } ;

    /** repetition counter register */
    union
    {
        __IOM uint32_t REPCNT;

        struct
        {
            __IOM uint32_t REPCNT     : 8;
            __IM  uint32_t RESERVED   : 24;
        } REPCNT_B;
    } ;

    /** capture/compare register 1 */
    union
    {
        __IOM uint32_t CC1;

        struct
        {
            __IOM uint32_t CC1        : 32;
        } CC1_B;
    } ;

    /** capture/compare register 2 */
    union
    {
        __IOM uint32_t CC2;

        struct
        {
            __IOM uint32_t CC2        : 32;
        } CC2_B;
    } ;

    /** capture/compare register 3 */
    union
    {
        __IOM uint32_t CC3;

        struct
        {
            __IOM uint32_t CC3        : 32;
        } CC3_B;
    } ;

    /** capture/compare register 4 */
    union
    {
        __IOM uint32_t CC4;

        struct
        {
            __IOM uint32_t CC4        : 32;
        } CC4_B;
    } ;

    /** break and dead-time register */
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
            __IM  uint32_t RESERVED   : 16;
        } BDT_B;
    } ;

    /** DMA control register */
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

    /** DMA address for full transfer */
    union
    {
        __IOM uint32_t DMADDR;

        struct
        {
            __IOM uint32_t DMADDR     : 32;
        } DMADDR_B;
    } ;

    /** Remap */
    union
    {
        __IOM uint32_t OPT;

        struct
        {
            __IOM uint32_t RMPSEL     : 32;
        } OPT_B;
    } ;
} TMR_T;

/**
 * @brief    Direct Memory Access register(DMA)
 */
typedef struct
{
    union
    {
        __IM uint32_t LINTSTS;

        struct
        {
            __IM  uint32_t FEIFLG0        : 1;
            __IM  uint32_t RESERVED1      : 1;
            __IM  uint32_t DMEIFLG0       : 1;
            __IM  uint32_t TXEIFLG0       : 1;
            __IM  uint32_t HTXIFLG0       : 1;
            __IM  uint32_t TXCIFLG0       : 1;
            __IM  uint32_t FEIFLG1        : 1;
            __IM  uint32_t RESERVED2      : 1;
            __IM  uint32_t DMEIFLG1       : 1;
            __IM  uint32_t TXEIFLG1       : 1;
            __IM  uint32_t HTXIFLG1       : 1;
            __IM  uint32_t TXCIFLG1       : 1;
            __IM  uint32_t RESERVED3      : 4;
            __IM  uint32_t FEIFLG2        : 1;
            __IM  uint32_t RESERVED4      : 1;
            __IM  uint32_t DMEIFLG2       : 1;
            __IM  uint32_t TXEIFLG2       : 1;
            __IM  uint32_t HTXIFLG2       : 1;
            __IM  uint32_t TXCIFLG2       : 1;
            __IM  uint32_t FEIFLG3        : 1;
            __IM  uint32_t RESERVED5      : 1;
            __IM  uint32_t DMEIFLG3       : 1;
            __IM  uint32_t TXEIFLG3       : 1;
            __IM  uint32_t HTXIFLG3       : 1;
            __IM  uint32_t TXCIFLG3       : 1;
            __IM  uint32_t RESERVED6      : 4;
        } LINTSTS_B;
    };

    union
    {
        __IM uint32_t HINTSTS;

        struct
        {
            __IM  uint32_t FEIFLG4        : 1;
            __IM  uint32_t RESERVED1      : 1;
            __IM  uint32_t DMEIFLG4       : 1;
            __IM  uint32_t TXEIFLG4       : 1;
            __IM  uint32_t HTXIFLG4       : 1;
            __IM  uint32_t TXCIFLG4       : 1;
            __IM  uint32_t FEIFLG5        : 1;
            __IM  uint32_t RESERVED2      : 1;
            __IM  uint32_t DMEIFLG5       : 1;
            __IM  uint32_t TXEIFLG5       : 1;
            __IM  uint32_t HTXIFLG5       : 1;
            __IM  uint32_t TXCIFLG5       : 1;
            __IM  uint32_t RESERVED3      : 4;
            __IM  uint32_t FEIFLG6        : 1;
            __IM  uint32_t RESERVED4      : 1;
            __IM  uint32_t DMEIFLG6       : 1;
            __IM  uint32_t TXEIFLG6       : 1;
            __IM  uint32_t HTXIFLG6       : 1;
            __IM  uint32_t TXCIFLG6       : 1;
            __IM  uint32_t FEIFLG7        : 1;
            __IM  uint32_t RESERVED5      : 1;
            __IM  uint32_t DMEIFLG7       : 1;
            __IM  uint32_t TXEIFLG7       : 1;
            __IM  uint32_t HTXIFLG7       : 1;
            __IM  uint32_t TXCIFLG7       : 1;
            __IM  uint32_t RESERVED6      : 4;
        } HINTSTS_B;
    };

    union
    {
        __OM uint32_t LIFCLR;

        struct
        {
            __OM  uint32_t CFEIFLG0       : 1;
            __IM  uint32_t RESERVED1      : 1;
            __OM  uint32_t CDMEIFLG0      : 1;
            __OM  uint32_t CTXEIFLG0      : 1;
            __OM  uint32_t CHTXIFLG0      : 1;
            __OM  uint32_t CTXCIFLG0      : 1;
            __OM  uint32_t CFEIFLG1       : 1;
            __IM  uint32_t RESERVED2      : 1;
            __OM  uint32_t CDMEIFLG1      : 1;
            __OM  uint32_t CTXEIFLG1      : 1;
            __OM  uint32_t CHTXIFLG1      : 1;
            __OM  uint32_t CTXCIFLG1      : 1;
            __IM  uint32_t RESERVED3      : 4;
            __OM  uint32_t CFEIFLG2       : 1;
            __IM  uint32_t RESERVED4      : 1;
            __OM  uint32_t CDMEIFLG2      : 1;
            __OM  uint32_t CTXEIFLG2      : 1;
            __OM  uint32_t CHTXIFLG2      : 1;
            __OM  uint32_t CTXCIFLG2      : 1;
            __OM  uint32_t CFEIFLG3       : 1;
            __IM  uint32_t RESERVED5      : 1;
            __OM  uint32_t CDMEIFLG3      : 1;
            __OM  uint32_t CTXEIFLG3      : 1;
            __OM  uint32_t CHTXIFLG3      : 1;
            __OM  uint32_t CTXCIFLG3      : 1;
            __IM  uint32_t RESERVED6      : 4;
        } LIFCLR_B;
    };

    union
    {
        __OM uint32_t HIFCLR;

        struct
        {
            __OM  uint32_t CFEIFLG4       : 1;
            __IM  uint32_t RESERVED1      : 1;
            __OM  uint32_t CDMEIFLG4      : 1;
            __OM  uint32_t CTXEIFLG4      : 1;
            __OM  uint32_t CHTXIFLG4      : 1;
            __OM  uint32_t CTXCIFLG4      : 1;
            __OM  uint32_t CFEIFLG5       : 1;
            __IM  uint32_t RESERVED2      : 1;
            __OM  uint32_t CDMEIFLG5      : 1;
            __OM  uint32_t CTXEIFLG5      : 1;
            __OM  uint32_t CHTXIFLG5      : 1;
            __OM  uint32_t CTXCIFLG5      : 1;
            __IM  uint32_t RESERVED3      : 4;
            __OM  uint32_t CFEIFLG6       : 1;
            __IM  uint32_t RESERVED4      : 1;
            __OM  uint32_t CDMEIFLG6      : 1;
            __OM  uint32_t CTXEIFLG6      : 1;
            __OM  uint32_t CHTXIFLG6      : 1;
            __OM  uint32_t CTXCIFLG6      : 1;
            __OM  uint32_t CFEIFLG7       : 1;
            __IM  uint32_t RESERVED5      : 1;
            __OM  uint32_t CDMEIFLG7      : 1;
            __OM  uint32_t CTXEIFLG7      : 1;
            __OM  uint32_t CHTXIFLG7      : 1;
            __OM  uint32_t CTXCIFLG7      : 1;
            __IM  uint32_t RESERVED6      : 4;
        } HIFCLR_B;
    };
} DMA_T;

/**
 * @brief DMA Stream register
 */
typedef struct
{
    union
    {
        __IOM uint32_t SCFG;

        struct
        {
            __IOM uint32_t EN            : 1;
            __IOM uint32_t DMEIEN        : 1;
            __IOM uint32_t TXEIEN        : 1;
            __IOM uint32_t HTXIEN        : 1;
            __IOM uint32_t TXCIEN        : 1;
            __IOM uint32_t PERFC         : 1;
            __IOM uint32_t DIRCFG        : 2;
            __IOM uint32_t CIRCMEN       : 1;
            __IOM uint32_t PERIM         : 1;
            __IOM uint32_t MEMIM         : 1;
            __IOM uint32_t PERSIZECFG    : 2;
            __IOM uint32_t MEMSIZECFG    : 2;
            __IOM uint32_t PERIOSIZE     : 1;
            __IOM uint32_t PRILCFG       : 2;
            __IOM uint32_t DBM           : 1;
            __IOM uint32_t CTARG         : 1;
            __IM  uint32_t RESERVED1     : 1;
            __IOM uint32_t PBCFG         : 2;
            __IOM uint32_t MBCFG         : 2;
            __IOM uint32_t CHSEL         : 3;
            __IM  uint32_t RESERVED2     : 4;
        } SCFG_B;
    };

    union
    {
        __IOM uint32_t NDATA;

        struct
        {
            __IOM  uint32_t NDATA        : 16;
            __IM   uint32_t RESERVED     : 16;
        } NDATA_B;
    };

    union
    {
        __IOM uint32_t PADDR;

        struct
        {
            __IOM  uint32_t PADDR         : 32;
        } PADDR_B;

    };

    union
    {
        __IOM uint32_t M0ADDR;

        struct
        {
            __IOM  uint32_t M0ADDR         : 32;
        } M0ADDR_B;

    };

    union
    {
        __IOM uint32_t M1ADDR;

        struct
        {
            __IOM  uint32_t M1ADDR         : 32;
        } M1ADDR_B;

    };

    union
    {
        __IOM uint32_t FCTRL;

        struct
        {
            __IOM  uint32_t FTHSEL         : 2;
            __IOM  uint32_t DMDEN          : 1;
            __IM   uint32_t FSTS           : 3;
            __IM   uint32_t RESERVED1      : 1;
            __IOM  uint32_t FEIEN          : 1;
            __IM   uint32_t RESERVED2      : 24;
        } FCTRL_B;
    };
} DMA_Stream_T;

/**
 * @brief CAN sending mailbox (CAN)
 */
typedef struct
{
    /** @brief CAN Each mailbox contains the sending mailbox identifier register */
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

    /** @brief CAN Send the mailbox data length and timestamp register */
    union
    {
        __IOM uint32_t TXDLEN;

        struct
        {
            __IOM uint32_t DLCODE          : 4;
            __IM  uint32_t RESERVED        : 28;
        } TXDLEN_B;
    };

    /** @brief CAN Send mailbox low byte data register */
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

    /** @brief CAN Send mailbox High byte data register */
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
    /** @brief CAN Each mailbox contains the receive mailbox identifier register */
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

    /** @brief CAN receive the mailbox data length and timestamp register */
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

    /** @brief CAN receive mailbox low byte data register */
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

    /** @briefCAN receive mailbox High byte data register */
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
    /** @brief CAN Filter bank register 1 */
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

    /** @brief CAN Filter bank register 2 */
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
    /** @brief CAN Master control register */
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

    /** @brief CAN Master States register */
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

    /** @brief CAN Send States register */
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

    /** @brief CAN Receive FIFO 0 register */
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

    /** @brief CAN Receive FIFO 1 register */
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

    /** @brief CAN Interrupts register */
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

    /** @brief CAN Error States register */
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

    /** @brief CAN Bit Time register */
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

    CAN_TxMailBox_T  sTxMailBox[3];
    CAN_RxMailBox_T  sRxMailBox[2];

    __IM  uint32_t  RESERVED1[12];

    /** @brief CAN Filter the master control register */
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

    /** @brief CAN Filter register */
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

    __IM  uint32_t  RESERVED2;

    /** @brief CAN Filter bit scale register */
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

    __IM  uint32_t  RESERVED3;

    /** @brief CAN Filter FIFO associated registers */
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

    __IM  uint32_t  RESERVED4;

    /** @brief CAN Filter activation register */
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

    __IM  uint32_t  RESERVED5[8];

    CAN_FilterRegister_T sFilterRegister[28];
} CAN_T;

/**
 * @brief    I2C register (I2C)
 */
typedef struct
{
    /** @brief Control register 1 */
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

    /** @brief Control register 2 */
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

    /** @brief Slave machine address register 1 */
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

    /** @brief Slave machine address register 2 */
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

    /** @brief Cache data register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA            : 8;
            __IM  uint32_t RESERVED        : 24;
        } DATA_B;
    };

    /** @brief Status register 1 */
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

    /** @brief Status register 2 */
    union
    {
        __IM uint32_t STS2;

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

    /** @brief Clock control register */
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

    /** @brief  Maximum rise time */
    union
    {
        __IOM uint32_t RISETMAX;

        struct
        {
            __IOM uint32_t RISETMAX        : 6;
            __IM  uint32_t RESERVED        : 26;
        } RISETMAX_B;
    };
} I2C_T;

/**
 * @brief Analog to Digital Converter(ADC)
 */
typedef struct
{
    /** interrupt and status register */
    union
    {
        __IOM  uint32_t STS;

        struct
        {
            __IOM uint32_t AWDFLG     : 1;
            __IOM uint32_t EOCFLG     : 1;
            __IOM uint32_t INJEOCFLG  : 1;
            __IOM uint32_t INJCSFLG   : 1;
            __IOM uint32_t REGCSFLG   : 1;
            __IOM uint32_t OVREFLG    : 1;
            __IM  uint32_t RESERVED1  : 26;
        } STS_B;
    } ;

    /** Control register1*/

    union
    {
        __IOM uint32_t CTRL1;

        struct
        {
            __IOM uint32_t AWDCHSEL      : 5;
            __IOM uint32_t EOCIEN        : 1;
            __IOM uint32_t AWDIEN        : 1;
            __IOM uint32_t INJEOCIEN     : 1;
            __IOM uint32_t SCANEN        : 1;
            __IOM uint32_t AWDSGLEN      : 1;
            __IOM uint32_t INJGACEN      : 1;
            __IOM uint32_t REGDISCEN     : 1;
            __IOM uint32_t INJDISCEN     : 1;
            __IOM uint32_t DISCNUMCFG    : 3;
            __IM  uint32_t RESERVED1     : 6;
            __IOM uint32_t INJAWDEN      : 1;
            __IOM uint32_t REGAWDEN      : 1;
            __IOM uint32_t RESSEL        : 2;
            __IOM uint32_t OVRIEN        : 1;
            __IM  uint32_t RESERVED2     : 5;
        } CTRL1_B;
    } ;
    /** Control register2*/
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t ADCEN           : 1;
            __IOM uint32_t CONTCEN         : 1;
            __IM  uint32_t RESERVED1       : 6;
            __IOM uint32_t DMAEN           : 1;
            __IOM uint32_t DMADISSEL       : 1;
            __IOM uint32_t EOCSEL          : 1;
            __IOM uint32_t DALIGNCFG       : 1;
            __IM  uint32_t RESERVED2       : 4;
            __IOM uint32_t INJGEXTTRGSEL   : 4;
            __IOM uint32_t INJEXTTRGEN     : 2;
            __IOM uint32_t INJCHSC         : 1;
            __IM  uint32_t RESERVED3       : 1;
            __IOM uint32_t REGEXTTRGSEL    : 4;
            __IOM uint32_t REGEXTTRGEN     : 2;
            __IOM uint32_t REGCHSC         : 1;
            __IM  uint32_t RESERVED4       : 1;
        } CTRL2_B;
    } ;

    /** Sample time register1*/
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
            __IOM uint32_t SMPCYCCFG18     : 3;
            __IM  uint32_t RESERVED        : 5;
        } SMPTIM1_B;
    };

    /** Sample time register2*/
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

    /** Injected channel Data offset register1*/
    union
    {
        __IOM uint32_t INJDOF1;

        struct
        {
            __IOM  uint32_t INJDOF1        : 12;
            __IM   uint32_t RESERVED       : 20;
        } INJDOF1_B;
    };

    /** Injected channel Data offset register2*/
    union
    {
        __IOM uint32_t INJDOF2;

        struct
        {
            __IOM  uint32_t INJDOF2        : 12;
            __IM   uint32_t RESERVED       : 20;
        } INJDOF2_B;
    };

    /** Injected channel Data offset register3*/
    union
    {
        __IOM uint32_t INJDOF3;

        struct
        {
            __IOM  uint32_t INJDOF3        : 12;
            __IM   uint32_t RESERVED       : 20;
        } INJDOF3_B;
    };

    /** Injected channel Data offset register4*/
    union
    {
        __IOM uint32_t INJDOF4;

        struct
        {
            __IOM  uint32_t INJDOF4        : 12;
            __IM   uint32_t RESERVED       : 20;
        } INJDOF4_B;
    };

    /** Analog watchdog high threshold register*/
    union
    {
        __IOM uint32_t AWDHT;

        struct
        {
            __IOM  uint32_t AWDHT          : 12;
            __IM   uint32_t RESERVED       : 20;
        } AWDHT_B;
    };

    /** Analog watchdog low threshold register*/
    union
    {
        __IOM uint32_t AWDLT;

        struct
        {
            __IOM  uint32_t AWDLT          : 12;
            __IM   uint32_t RESERVED       : 20;
        } AWDLT_B;
    };

    /** Regular channel sequence register1*/
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

    /** Regular channel sequence register2*/
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

    /** Regular channel sequence register3*/
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

    /** Injected sequence register*/
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

    /** Injected Data register1*/
    union
    {
        __IM uint32_t INJDATA1;

        struct
        {
            __IM   uint32_t INJDATA        : 16;
            __IM   uint32_t RESERVED       : 16;
        } INJDATA1_B;
    };

    /** Injected Data register2*/
    union
    {
        __IM uint32_t INJDATA2;

        struct
        {
            __IM   uint32_t INJDATA        : 16;
            __IM   uint32_t RESERVED       : 16;
        } INJDATA2_B;
    };

    /** Injected Data register3*/
    union
    {
        __IM uint32_t INJDATA3;

        struct
        {
            __IM   uint32_t INJDATA        : 16;
            __IM   uint32_t RESERVED       : 16;
        } INJDATA3_B;
    };

    /** Injected Data register4*/
    union
    {
        __IM uint32_t INJDATA4;

        struct
        {
            __IM   uint32_t INJDATA        : 16;
            __IM   uint32_t RESERVED       : 16;
        } INJDATA4_B;
    };

    /** Regular Data register*/
    union
    {
        __IOM uint32_t REGDATA;

        struct
        {
            __IM  uint32_t REGDATA         : 16;
            __IM  uint32_t RESERVED        : 16;
        } REGDATA_B;
    };
} ADC_T;

typedef struct
{
    /**Common status register*/
    union
    {
        __IOM uint32_t CSTS;

        struct
        {
            __IM uint32_t AWDFLG1        : 1;
            __IM uint32_t EOCFLG1        : 1;
            __IM uint32_t INJEOCFLG1     : 1;
            __IM uint32_t INJCSFLG1      : 1;
            __IM uint32_t REGCSFLG1      : 1;
            __IM uint32_t OVRFLG1        : 1;
            __IM uint32_t RESERVED1      : 2;
            __IM uint32_t AWDFLG2        : 1;
            __IM uint32_t EOCFLG2        : 1;
            __IM uint32_t INJEOCFLG2     : 1;
            __IM uint32_t INJCSFLG2      : 1;
            __IM uint32_t REGCSFLG2      : 1;
            __IM uint32_t OVRFLG2        : 1;
            __IM uint32_t RESERVED2      : 2;
            __IM uint32_t AWDFLG3        : 1;
            __IM uint32_t EOCFLG3        : 1;
            __IM uint32_t INJEOCFLG3     : 1;
            __IM uint32_t INJCSFLG3      : 1;
            __IM uint32_t REGCSFLG3      : 1;
            __IM uint32_t OVRFLG3        : 1;
            __IM uint32_t RESERVED3      : 2;
        } CSTS_B;
    } ;

    /** Common control register*/
    union
    {
        __IOM uint32_t CCTRL;

        struct
        {
            __IOM uint32_t ADCMSEL      : 5;
            __IM  uint32_t RESERVED1    : 3;
            __IOM uint32_t SMPDEL2      : 4;
            __IM  uint32_t RESERVED2    : 1;
            __IOM uint32_t DMADISSEL    : 1;
            __IOM uint32_t DMAMODE      : 2;
            __IOM uint32_t ADCPRE       : 2;
            __IM  uint32_t RESERVED3    : 4;
            __IOM uint32_t VBATEN       : 1;
            __IOM uint32_t TSVREFEN     : 1;
            __IM  uint32_t RESERVED4    : 8;
        } CCTRL_B;
    } ;

    /** Common regular data register for dual and triple modes */
    union
    {
        __IOM uint32_t CDATA;

        struct
        {
            __IM uint32_t DATA1     : 16;
            __IM uint32_t DATA2     : 16;
        } CDATA_B;
    } ;
} ADC_Common_T;

/**
 * @brief    External Interrupt/Event Controller (EINT)
 */
typedef struct
{
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
            __IOM uint32_t IMASK19         : 1;
            __IOM uint32_t IMASK20         : 1;
            __IOM uint32_t IMASK21         : 1;
            __IOM uint32_t IMASK22         : 1;
            __IM   uint32_t RESERVED       : 9;
        } IMASK_B;
    };

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
            __IOM uint32_t EMASK19         : 1;
            __IOM uint32_t EMASK20         : 1;
            __IOM uint32_t EMASK21         : 1;
            __IOM uint32_t EMASK22         : 1;
            __IM   uint32_t RESERVED       : 9;
        } EMASK_B;
    };

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
            __IOM uint32_t RTEN19          : 1;
            __IOM uint32_t RTEN20          : 1;
            __IOM uint32_t RTEN21          : 1;
            __IOM uint32_t RTEN22          : 1;
            __IM   uint32_t RESERVED       : 9;
        } RTEN_B;
    };

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
            __IOM uint32_t FTEN19          : 1;
            __IOM uint32_t FTEN20          : 1;
            __IOM uint32_t FTEN21          : 1;
            __IOM uint32_t FTEN22          : 1;
            __IM   uint32_t RESERVED       : 9;
        } FTEN_B;
    };

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
            __IOM uint32_t SWINTE19        : 1;
            __IOM uint32_t SWINTE20        : 1;
            __IOM uint32_t SWINTE21        : 1;
            __IOM uint32_t SWINTE22        : 1;
            __IM   uint32_t RESERVED       : 9;
        } SWINTE_B;
    };

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
            __IOM uint32_t IPEND19         : 1;
            __IOM uint32_t IPEND20         : 1;
            __IOM uint32_t IPEND21         : 1;
            __IOM uint32_t IPEND22         : 1;
            __IM   uint32_t RESERVED       : 9;
        } IPEND_B;
    };
} EINT_T;

/**
 * @brief    Independent WATCHDOG (IWDT)
 */
typedef struct
{
    union
    {
        __IOM uint32_t KEY;

        struct
        {
            __OM   uint32_t KEY            : 16;
            __IM   uint32_t RESERVED       : 16;
        } KEY_B;
    };

    union
    {
        __IOM uint32_t PSC;

        struct
        {
            __IOM  uint32_t PSC            : 3;
            __IM   uint32_t RESERVED       : 29;
        } PSC_B;
    };

    union
    {
        __IOM uint32_t CNTRLD;

        struct
        {
            __IOM  uint32_t CNTRLD         : 12;
            __IM   uint32_t RESERVED       : 20;
        } CNTRLD_B;
    };

    union
    {
        __IM uint32_t STS;

        struct
        {
            __IM   uint32_t PSCUFLG        : 1;
            __IM   uint32_t CNTUFLG        : 1;
            __IM   uint32_t RESERVED       : 30;
        } STS_B;
    };
} IWDT_T;

/**
 * @brief    Window WATCHDOG (WWDT)
 */
typedef struct
{
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM  uint32_t CNT            : 7;
            __IOM  uint32_t WWDTEN         : 1;
            __IM   uint32_t RESERVED       : 24;
        } CTRL_B;
    };

    union
    {
        __IOM uint32_t CFG;

        struct
        {
            __IOM  uint32_t WIN            : 7;
            __IOM  uint32_t TBPSC          : 2;
            __IOM  uint32_t EWIEN          : 1;
            __IM   uint32_t RESERVED       : 22;
        } CFG_B;
    };

    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM  uint32_t EWIFLG          : 1;
            __IM   uint32_t RESERVED       : 31;
        } STS_B;
    };
} WWDT_T;

/**
 * @brief Serial peripheral interface(SPI)
 */
typedef struct
{
    /** Control register 1 */
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

    /** Control register 2 */
    union
    {
        __IOM uint32_t CTRL2;

        struct
        {
            __IOM uint32_t RXDEN           : 1;
            __IOM uint32_t TXDEN           : 1;
            __IOM uint32_t SSOEN           : 1;
            __IM  uint32_t RESERVED1       : 1;
            __IOM uint32_t FRFCFG          : 1;
            __IOM uint32_t ERRIEN          : 1;
            __IOM uint32_t RXBNEIEN        : 1;
            __IOM uint32_t TXBEIEN         : 1;
            __IM  uint32_t RESERVED2       : 24;
        } CTRL2_B;
    };

    /** Status register */
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
            __IM  uint32_t FFERR           : 1;
            __IM  uint32_t RESERVED        : 23;
        } STS_B;
    };

    /** Data register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IOM uint32_t DATA            : 16;
            __IM  uint32_t RESERVED        : 16;
        } DATA_B;
    };

    /** CRC polynomial register */
    union
    {
        __IOM uint32_t CRCPOLY;

        struct
        {
            __IOM uint32_t CRCPOLY         : 16;
            __IM  uint32_t RESERVED        : 16;
        } CRCPOLY_B;
    };

    /** Receive CRC register */
    union
    {
        __IM uint32_t RXCRC;

        struct
        {
            __IM  uint32_t RXCRC           : 16;
            __IM  uint32_t RESERVED        : 16;
        } RXCRC_B;
    };

    /** Transmit CRC register */
    union
    {
        __IM uint32_t TXCRC;

        struct
        {
            __IM  uint32_t TXCRC           : 16;
            __IM  uint32_t RESERVED        : 16;
        } TXCRC_B;
    };

    /** Transmit I2S CTRL register */
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

    /** Transmit I2S DIV register */
    union
    {
        __IOM uint32_t I2SPSC;

        struct
        {
            __IOM uint32_t I2SPSC          : 8;
            __IOM uint32_t ODDPSC          : 1;
            __IOM uint32_t MCOEN           : 1;
            __IM  uint32_t RESERVED        : 22;
        } I2SPSC_B;
    };
} SPI_T;

/**
 * @brief Secure digital input/output interface (SDIO)
 */
typedef struct
{
    /** Power control register */
    union
    {
        __IOM uint32_t PWRCTRL;

        struct
        {
            __IOM  uint32_t PWRCTRL        : 2;
            __IM   uint32_t RESERVED       : 30;
        } PWRCTRL_B;
    };

    /** Clock control register */
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

    /** Argument register */
    union
    {
        __IOM uint32_t ARG;

        struct
        {
            __IOM  uint32_t CMDARG         : 32;
        } ARG_B;
    };

    /** Command register */
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

    /** Command response register */
    union
    {
        __IM uint32_t CMDRES;

        struct
        {
            __IM  uint32_t CMDRES          : 6;
            __IM  uint32_t RESERVED        : 26;
        } CMDRES_B;
    };

    /** SDIO response register1 */
    union
    {
        __IM uint32_t RES1;

        struct
        {
            __IM  uint32_t CARDSTS1        : 32;
        } RES1_B;
    };

    /** SDIO response register2 */
    union
    {
        __IM uint32_t RES2;

        struct
        {
            __IM  uint32_t CARDSTS2        : 32;
        } RES2_B;
    };

    /** SDIO response register3 */
    union
    {
        __IM uint32_t RES3;

        struct
        {
            __IM  uint32_t CARDSTS3        : 32;
        } RES3_B;
    };

    /** SDIO response register4 */
    union
    {
        __IM uint32_t RES4;

        struct
        {
            __IM  uint32_t CARDSTS4        : 32;
        } RES4_B;
    };

    /** Data timer register */
    union
    {
        __IOM uint32_t DATATIME;

        struct
        {
            __IOM  uint32_t DATATIME       : 32;
        } DTMR_B;
    };

    /** Data length register */
    union
    {
        __IOM uint32_t DATALEN;

        struct
        {
            __IOM uint32_t DATALEN         : 25;
            __IM  uint32_t RESERVED        : 7;
        } DLEN_B;
    };

    /** Data control register */
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

    /** Data count register */
    union
    {
        __IM uint32_t DCNT;

        struct
        {
            __IM  uint32_t DATACNT         : 25;
            __IM  uint32_t RESERVED        : 7;
        } DCNT_B;
    };

    /** SDIO status register */
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

    /** SDIO interrupt clear register */
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

    /** SDIO interrupt mask register */
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

    /** SDIO FIFO count register */
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

    /** SDIO data FIFO register */
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
    /** Control register */
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
            __IOM uint32_t DMAUDIEN1       : 1;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t ENCH2           : 1;
            __IOM uint32_t BUFFDCH2        : 1;
            __IOM uint32_t TRGENCH2        : 1;
            __IOM uint32_t TRGSELCH2       : 3;
            __IOM uint32_t WAVENCH2        : 2;
            __IOM uint32_t MAMPSELCH2      : 4;
            __IOM uint32_t DMAENCH2        : 1;
            __IOM uint32_t DMAUDIEN2       : 1;
            __IM  uint32_t RESERVED2       : 2;
        } CTRL_B;
    };

    /** Software trigger register */
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

    /** Channel1 12-bit right-aligned register */
    union
    {
        __IOM uint32_t DH12R1;

        struct
        {
            __IOM uint32_t DATA            : 12;
            __IM  uint32_t RESERVED        : 20;
        } DH12R1_B;
    };

    /** Channel1 12-bit left-aligned register */
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

    /** Channel1 8-bit right-aligned register */
    union
    {
        __IOM uint32_t DH8R1;

        struct
        {
            __IOM uint32_t DATA            : 8;
            __IM  uint32_t RESERVED        : 24;
        } DH8R1_B;
    };

    /** Channel2 12-bit right-aligned register */
    union
    {
        __IOM uint32_t DH12R2;

        struct
        {
            __IOM uint32_t DATA            : 12;
            __IM  uint32_t RESERVED        : 20;
        } DH12R2_B;
    };

    /** Channel2 12-bit left-aligned register */
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

    /** Channel2 8-bit right-aligned register */
    union
    {
        __IOM uint32_t DH8R2;

        struct
        {
            __IOM uint32_t DATA            : 8;
            __IM  uint32_t RESERVED        : 24;
        } DH8R2_B;
    };

    /** Channel1,Channel2 12-bit right-aligned register */
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

    /** Channel1,Channel2 12-bit left-aligned register */
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

    /** Channel1,Channel2 8-bit right-aligned register */
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

    /** Channel1 data output register */
    union
    {
        __IM uint32_t DATAOCH1;

        struct
        {
            __IM  uint32_t DATA            : 12;
            __IM  uint32_t RESERVED        : 20;
        } DATAOCH1_B;
    };

    /** Channel2 data output register */
    union
    {
        __IM uint32_t DATAOCH2;

        struct
        {
            __IM  uint32_t DATA            : 12;
            __IM  uint32_t RESERVED        : 20;
        } DATAOCH2_B;
    };

    /** DAC status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM  uint32_t RESERVED1       : 13;
            __IOM uint32_t DMAUDFLG1       : 1;
            __IM  uint32_t RESERVED2       : 15;
            __IOM uint32_t DMAUDFLG2       : 1;
            __IM  uint32_t RESERVED3       : 2;
        } STS_B;
    };
} DAC_T;

/**
 * @brief Static Memory Controller (SMC) Bank1
 */
typedef struct
{
    /** SRAM/NOR-Flash chip-select control register 1 */
    union
    {
        __IOM uint32_t CSCTRL1;

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
            __IM  uint32_t RESERVED2       : 12;
        } CSCTRL1_B;
    };

    /** SRAM/NOR-Flash chip-select timing register 1 */
    union
    {
        __IOM uint32_t CSTIM1;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ASYNCACCCFG     : 2;
            __IM  uint32_t RESERVED        : 2;
        } CSTIM1_B;
    };

    /** SRAM/NOR-Flash chip-select control register 2 */
    union
    {
        __IOM uint32_t CSCTRL2;

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
            __IM  uint32_t RESERVED2       : 12;
        } CSCTRL2_B;
    };

    /** SRAM/NOR-Flash chip-select timing register 2 */
    union
    {
        __IOM uint32_t CSTIM2;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ASYNCACCCFG     : 2;
            __IM  uint32_t RESERVED        : 2;
        } CSTIM2_B;
    };

    /** SRAM/NOR-Flash chip-select control register 3 */
    union
    {
        __IOM uint32_t CSCTRL3;

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
            __IM  uint32_t RESERVED2       : 12;
        } CSCTRL3_B;
    };

    /** SRAM/NOR-Flash chip-select timing register 3 */
    union
    {
        __IOM uint32_t CSTIM3;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ASYNCACCCFG     : 2;
            __IM  uint32_t RESERVED        : 2;
        } CSTIM3_B;
    };

    /** SRAM/NOR-Flash chip-select control register 4 */
    union
    {
        __IOM uint32_t CSCTRL4;

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
            __IM  uint32_t RESERVED2       : 12;
        } CSCTRL4_B;
    };

    /** SRAM/NOR-Flash chip-select timing register 4 */
    union
    {
        __IOM uint32_t CSTIM4;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ASYNCACCCFG     : 2;
            __IM  uint32_t RESERVED        : 2;
        } CSTIM4_B;
    };
} SMC_Bank1_T;

/**
 * @brief Static Memory Controller (SMC) Bank1E
 */
typedef struct
{
    /** SRAM/NOR-Flash write timing registers 1 */
    union
    {
        __IOM uint32_t WRTTIM1;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ASYNCACCCFG     : 2;
            __IM  uint32_t RESERVED        : 2;
        } WRTTIM1_B;
    };

    __IM  uint32_t  RESERVED;

    /** SRAM/NOR-Flash write timing registers 2 */
    union
    {
        __IOM uint32_t WRTTIM2;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ASYNCACCCFG     : 2;
            __IM  uint32_t RESERVED        : 2;
        } WRTTIM2_B;
    };

    __IM  uint32_t  RESERVED1;

    /** SRAM/NOR-Flash write timing registers 3 */
    union
    {
        __IOM uint32_t WRTTIM3;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ASYNCACCCFG     : 2;
            __IM  uint32_t RESERVED        : 2;
        } WRTTIM3_B;
    };

    __IOM  uint32_t  RESERVED2;

    /** SRAM/NOR-Flash write timing registers 4 */
    union
    {
        __IOM uint32_t WRTTIM4;

        struct
        {
            __IOM uint32_t ADDRSETCFG      : 4;
            __IOM uint32_t ADDRHLDCFG      : 4;
            __IOM uint32_t DATASETCFG      : 8;
            __IOM uint32_t BUSTURNCFG      : 4;
            __IOM uint32_t CLKDIVCFG       : 4;
            __IOM uint32_t DATALATCFG      : 4;
            __IOM uint32_t ASYNCACCCFG     : 2;
            __IM  uint32_t RESERVED        : 2;
        } WRTTIM4_B;
    };
} SMC_Bank1E_T;

/**
 * @brief  Static Memory Controller (SMC) Bank 2
 */
typedef struct
{
    /** PC Card/NAND Flash control register 2 */
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

    /** FIFO status and interrupt register 2 */
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
            __IM  uint32_t RESERVED        : 16;
        } STSINT2_B;
    };
    /** Common memory space timing register 2 */
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

    /** Attribute memory space timing register 2 */
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

    __IM uint32_t RESERVED;

    /** ECC result register 2 */
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
 * @brief Flexible Static Memory Controller (SMC) Bank 3
 */
typedef struct
{
    /** PC Card/NAND Flash control register 3 */
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

    /** FIFO status and interrupt register 3 */
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

    /** Common memory space timing register 3 */
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

    /** Attribute memory space timing register 3 */
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

    __IM uint32_t RESERVED;

    /** ECC result register 3 */
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
 * @brief Flexible Static Memory Controller (SMC) Bank 4
 */
typedef struct
{
    /** PC Card/NAND Flash control register 4 */
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

    /** FIFO status and interrupt register 4 */
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

    /** Common memory space timing register 4 */
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

    /** Attribute memory space timing register 4 */
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

    /** I/O space timing register 4 */
    union
    {
        __IOM uint32_t IOSTIM4;

        struct
        {
            __IOM uint32_t SET             : 8;
            __IOM uint32_t WAIT            : 8;
            __IOM uint32_t HLD             : 8;
            __IOM uint32_t HIZ             : 8;
        } IOSTIM4_B;
    };
} SMC_Bank4_T;

/**
 * @brief Dynamic memory controler (DMC)
 */
typedef struct
{
    /** @brief Configuraion register */
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

    /** @brief Timing register 0 */
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

    /** @brief Timing register 1 */
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

    /** @brief Control register 1 */
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
            __IOM uint32_t BANKNUMCFG      : 4;
            __IM  uint32_t RESERVED2       : 16;
        } CTRL1_B;
    };

    /** @brief Refresh register */
    union
    {
        __IOM uint32_t REF;
        struct
        {
            __IOM uint32_t RCYCCFG         : 16;
            __IM  uint32_t RESERVED        : 16;
        } REF_B;
    };

    __IM uint32_t RESERVED[251];

    /** @brief Switch register */
    union
    {
        __IOM uint32_t SW;
        struct
        {
            __IOM uint32_t MCSW            : 1;
            __IM  uint32_t RESERVED        : 31;
        } SW_B;
    };

    /** @brief Control register 2 */
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
    /** @brief ID register */
    union
    {
        __IM  uint32_t IDCODE;
        struct
        {
            __IM  uint32_t EQR             : 12;
            __IM  uint32_t RESERVED        : 4;
            __IM  uint32_t WVR             : 16;
        } IDCODE_B;
    };

    /** @brief Control register */
    union
    {
        __IOM uint32_t CFG;
        struct
        {
            __IOM uint32_t SLEEP_CLK_STS   : 1;
            __IOM uint32_t STOP_CLK_STS    : 1;
            __IOM uint32_t STANDBY_CLK_STS : 1;
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t TRACE_IOEN      : 1;
            __IOM uint32_t TRACE_MODE      : 2;
            __IM  uint32_t RESERVED2       : 24;
        } CFG_B;
    };

    /** @brief APB1F register */
    union
    {
        __IOM uint32_t APB1F;
        struct
        {
            __IOM uint32_t TMR2_STS                  : 1;
            __IOM uint32_t TMR3_STS                  : 1;
            __IOM uint32_t TMR4_STS                  : 1;
            __IOM uint32_t TMR5_STS                  : 1;
            __IOM uint32_t TMR6_STS                  : 1;
            __IOM uint32_t TMR7_STS                  : 1;
            __IOM uint32_t TMR12_STS                 : 1;
            __IOM uint32_t TMR13_STS                 : 1;
            __IOM uint32_t TMR14_STS                 : 1;
            __IM  uint32_t RESERVED1                 : 1;
            __IOM uint32_t RTC_STS                   : 1;
            __IOM uint32_t WWDT_STS                  : 1;
            __IOM uint32_t IWDT_STS                  : 1;
            __IM  uint32_t RESERVED2                 : 8;
            __IOM uint32_t I2C1_SMBUS_TIMEOUT_STS    : 1;
            __IOM uint32_t I2C2_SMBUS_TIMEOUT_STS    : 1;
            __IOM uint32_t I2C3_SMBUS_TIMEOUT_STS    : 1;
            __IM  uint32_t RESERVED3                 : 1;
            __IOM uint32_t CAN1_STS                  : 1;
            __IOM uint32_t CAN2_STS                  : 1;
            __IM  uint32_t RESERVED4                 : 5;
        } APB1F_B;
    };

    /** @brief APB2F register */
    union
    {
        __IOM uint32_t APB2F;
        struct
        {
            __IOM uint32_t TMR1_STS                  : 1;
            __IOM uint32_t TMR8_STS                  : 1;
            __IM  uint32_t RESERVED1                 : 14;
            __IOM uint32_t TMR9_STS                  : 1;
            __IOM uint32_t TMR10_STS                 : 1;
            __IOM uint32_t TMR11_STS                 : 1;
            __IM  uint32_t RESERVED2                 : 23;
        } APB2F_B;
    };
} DBGMCU_T;

/**
 * @brief Digital camera interface (DCI)
 */
typedef struct
{
    /** @brief DCI control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t CEN           : 1;
            __IOM uint32_t CMODE         : 1;
            __IOM uint32_t CROPF         : 1;
            __IOM uint32_t JPGFM         : 1;
            __IOM uint32_t ESYNCSEL      : 1;
            __IOM uint32_t PXCLKPOL      : 1;
            __IOM uint32_t HSYNCPOL      : 1;
            __IOM uint32_t VSYNCPOL      : 1;
            __IOM uint32_t FCRCFG        : 2;
            __IOM uint32_t EXDMOD        : 2;
            __IM  uint32_t RESERVED1     : 2;
            __IOM uint32_t DCIEN         : 1;
            __IM  uint32_t RESERVED2     : 17;
        } CTRL_B;
    } ;

    /** @brief DCI status register*/
    union
    {
        __IM uint32_t STS;

        struct
        {
            __IM uint32_t HSYNCSTS       : 1;
            __IM uint32_t VSYNCSTS       : 1;
            __IM uint32_t FIFONEMP       : 1;
            __IM uint32_t RESERVED       : 29;
        } STS_B;
    };

    /** @brief DCI raw interrupt status register */
    union
    {
        __IM uint32_t RINTSTS;

        struct
        {
            __IM uint32_t CC_RINT           : 1;
            __IM uint32_t OVR_RINT          : 1;
            __IM uint32_t SYNCERR_RINT      : 1;
            __IM uint32_t VSYNC_RINT        : 1;
            __IM uint32_t LINE_RINT         : 1;
            __IM uint32_t RESERVED          : 27;
        } RINTSTS_B;
    };

    /** @brief DCI interrupt enable register */
    union
    {
        __IOM uint32_t INTEN;

        struct
        {
            __IOM uint32_t CCINTEN           : 1;
            __IOM uint32_t OVRINTEN          : 1;
            __IOM uint32_t SYNCERRINTEN      : 1;
            __IOM uint32_t VSYNCINTEN        : 1;
            __IOM uint32_t LINEINTEN         : 1;
            __IM  uint32_t RESERVED          : 22;
        } INTEN_B;
    };

    /** @brief DCI masked interrupt status register */
    union
    {
        __IM uint32_t MINTSTS;

        struct
        {
            __IM uint32_t CC_MINT           : 1;
            __IM uint32_t OVR_MINT          : 1;
            __IM uint32_t SYNCERR_MINT      : 1;
            __IM uint32_t VSYNC_MINT        : 1;
            __IM uint32_t LINE_MINT         : 1;
            __IM uint32_t RESERVED          : 27;
        } MINTSTS_B;
    };

    /** @brief DCI interrupt clear registe */
    union
    {
        __IOM uint32_t INTCLR;

        struct
        {
            __OM uint32_t CC_INTCLR           : 1;
            __OM uint32_t OVR_INTCLR          : 1;
            __OM uint32_t SYNCERR_INTCLR      : 1;
            __OM uint32_t VSYNC_INTCLR        : 1;
            __OM uint32_t LINE_INTCLR         : 1;
            __IM uint32_t RESERVED            : 22;
        } INTCLR_B;
    };

    /** @brief DCI embedded synchronization code register */
    union
    {
        __IOM uint32_t ESYNCC;

        struct
        {
            __IOM uint32_t FSDC           : 8;
            __IOM uint32_t LSDC           : 8;
            __IOM uint32_t LEDC           : 8;
            __IOM uint32_t FEDC           : 8;
        } ESYNCC_B;
    };

    /** @brief DCI embedded synchronization unmask register */
    union
    {
        __IOM uint32_t ESYNCUM;

        struct
        {
            __IOM uint32_t FSDUM           : 8;
            __IOM uint32_t LSDUM           : 8;
            __IOM uint32_t LEDUM           : 8;
            __IOM uint32_t FEDUM           : 8;
        } ESYNCUM_B;
    };

    /** @brief DCI crop window start register */
    union
    {
        __IOM uint32_t CROPWSTAT;

        struct
        {
            __IOM uint32_t HOFSCNT           : 14;
            __IM  uint32_t RESERVED1         : 2;
            __IOM uint32_t VSLINECNT         : 13;
            __IM  uint32_t RESERVED2         : 3;
        } CROPWSTAT_B;
    };

    /** @brief DCI crop window size register */
    union
    {
        __IOM uint32_t CROPWSIZE;

        struct
        {
            __IOM uint32_t CCNT           : 14;
            __IM  uint32_t RESERVED1      : 2;
            __IOM uint32_t VLINECNT       : 14;
            __IM  uint32_t RESERVED2      : 2;
        } CROPWSIZE_B;
    };

    /** @brief DCI data register */
    union
    {
        __IOM uint32_t DATA;

        struct
        {
            __IM uint32_t DATA0          : 8;
            __IM uint32_t DATA1          : 8;
            __IM uint32_t DATA2          : 8;
            __IM uint32_t DATA3          : 8;
        } DATA_B;
    };
} DCI_T;

/**
 * @brief System configuration controller (SYSCFG)
 */
typedef struct
{
    union
    {
        __IOM uint32_t MMSEL;

        struct
        {
            __IOM uint32_t MMSEL         : 2;
            __IM  uint32_t RESERVED      : 30;
        } MMSEL_B;
    };
    /** @brief Peripheral Mode Configuration register */
    union
    {
        __IOM uint32_t PMC;

        struct
        {
            __IM uint32_t RESERVED1        : 23;
            __IOM uint32_t ENETSEL         : 1;
            __IM uint32_t RESERVED2        : 8;
        } PMC_B;
    };

    /** @brief External Interrupt Configuration register1 */
    union
    {
        __IOM uint32_t EINTCFG1;

        struct
        {
            __IOM uint32_t EINT0           : 4;
            __IOM uint32_t EINT1           : 4;
            __IOM uint32_t EINT2           : 4;
            __IOM uint32_t EINT3           : 4;
            __IM  uint32_t RESERVED        : 16;
        } EINTCFG1_B;
    };

    /** @brief External Interrupt Configuration register2 */
    union
    {
        __IOM uint32_t EINTCFG2;

        struct
        {
            __IOM uint32_t EINT4           : 4;
            __IOM uint32_t EINT5           : 4;
            __IOM uint32_t EINT6           : 4;
            __IOM uint32_t EINT7           : 4;
            __IM  uint32_t RESERVED        : 16;
        } EINTCFG2_B;
    };

    /** @brief External Interrupt Configuration register3 */
    union
    {
        __IOM uint32_t EINTCFG3;

        struct
        {
            __IOM uint32_t EINT8           : 4;
            __IOM uint32_t EINT9           : 4;
            __IOM uint32_t EINT10          : 4;
            __IOM uint32_t EINT11          : 4;
            __IM  uint32_t RESERVED        : 16;
        } EINTCFG3_B;
    };

    /** @brief External Interrupt Configuration register4 */
    union
    {
        __IOM uint32_t EINTCFG4;

        struct
        {
            __IOM uint32_t EINT12          : 4;
            __IOM uint32_t EINT13          : 4;
            __IOM uint32_t EINT14          : 4;
            __IOM uint32_t EINT15          : 4;
            __IM  uint32_t RESERVED        : 16;
        } EINTCFG4_B;
    };

    __IM  uint32_t  RESERVED[2];

    /** @brief Compensation cell control register */
    union
    {
        __IOM uint32_t CCCTRL;

        struct
        {
            __IOM uint32_t CCPD            : 1;
            __IM uint32_t RESERVED1        : 6;
            __IOM uint32_t RDYFLG          : 1;
            __IM  uint32_t RESERVED        : 24;
        } CCCTRL_B;
    };
} SYSCFG_T;

/**
 * @brief Ethernet (ETH)
 */
typedef struct
{
    /**
     * @brief ETH_MAC
     */

    /** @brief CFG register */
    union
    {
        __IOM uint32_t CFG;
        struct
        {
            __IM  uint32_t RESERVED1                 : 2;
            __IOM uint32_t RXEN                      : 1;
            __IOM uint32_t TXEN                      : 1;
            __IOM uint32_t DC                        : 1;
            __IOM uint32_t BL                        : 2;
            __IOM uint32_t ACS                       : 1;
            __IM  uint32_t RESERVED2                 : 1;
            __IOM uint32_t DISR                      : 1;
            __IOM uint32_t IPC                       : 1;
            __IOM uint32_t DM                        : 1;
            __IOM uint32_t LBM                       : 1;
            __IOM uint32_t DISRXO                    : 1;
            __IOM uint32_t SSEL                      : 1;
            __IM  uint32_t RESERVED3                 : 1;
            __IOM uint32_t DISCRS                    : 1;
            __IOM uint32_t IFG                       : 3;
            __IM  uint32_t RESERVED4                 : 2;
            __IOM uint32_t JDIS                      : 1;
            __IOM uint32_t WDTDIS                    : 1;
            __IM  uint32_t RESERVED5                 : 1;
            __IOM uint32_t CST                       : 1;
            __IM  uint32_t RESERVED6                 : 6;
        } CFG_B;
    };

    /** @brief FRAF register */
    union
    {
        __IOM uint32_t FRAF;
        struct
        {
            __IOM uint32_t PR                        : 1;
            __IOM uint32_t HUC                       : 1;
            __IOM uint32_t HMC                       : 1;
            __IOM uint32_t DAIF                      : 1;
            __IOM uint32_t PM                        : 1;
            __IOM uint32_t DISBF                     : 1;
            __IOM uint32_t PCTRLF                    : 2;
            __IOM uint32_t SAIF                      : 1;
            __IOM uint32_t SAFEN                     : 1;
            __IOM uint32_t HPF                       : 1;
            __IM  uint32_t RESERVED1                 : 20;
            __IOM uint32_t RXA                       : 1;
        } FRAF_B;
    };

    /** @brief HTH register */
    union
    {
        __IOM uint32_t HTH;
        struct
        {
            __IOM uint32_t HTH                         : 32;
        } HTH_B;
    };

    /** @brief HTL register */
    union
    {
        __IOM uint32_t HTL;
        struct
        {
            __IOM uint32_t HTL                         : 32;
        } HTL_B;
    };

    /** @brief ADDR register */
    union
    {
        __IOM uint32_t ADDR;
        struct
        {
            __IOM uint32_t MB                          : 1;
            __IOM uint32_t MW                          : 1;
            __IOM uint32_t CR                          : 3;
            __IM  uint32_t RESERVED1                   : 1;
            __IOM uint32_t MR                          : 5;
            __IOM uint32_t PA                          : 5;
            __IM  uint32_t RESERVED2                   : 16;
        } ADDR_B;
    };

    /** @brief DATA register */
    union
    {
        __IOM uint32_t DATA;
        struct
        {
            __IOM uint32_t MD                          : 16;
            __IM  uint32_t RESERVED1                   : 16;
        } DATA_B;
    };

    /** @brief FCTRL register */
    union
    {
        __IOM uint32_t FCTRL;
        struct
        {
            __IOM uint32_t FCTRLB                      : 1;
            __IOM uint32_t TXFCTRLEN                   : 1;
            __IOM uint32_t RXFCTRLEN                   : 1;
            __IOM uint32_t UNPFDETE                    : 1;
            __IOM uint32_t PTSEL                       : 2;
            __IM  uint32_t RESERVED1                   : 1;
            __IOM uint32_t ZQPDIS                      : 1;
            __IM  uint32_t RESERVED2                   : 8;
            __IOM uint32_t PT                          : 16;
        } FCTRL_B;
    };

    /** @brief VLANT register */
    union
    {
        __IOM uint32_t VLANT;
        struct
        {
            __IOM uint32_t VLANTID                     : 16;
            __IOM uint32_t VLANTCOMP                   : 1;
            __IM  uint32_t RESERVED                    : 15;
        } VLANT_B;
    };

    __IM  uint32_t  RESERVED0[2];

    /** @brief WKUPFFL register */
    union
    {
        __IOM uint32_t WKUPFFL;
        struct
        {
            __IOM uint32_t FLXBMASK                    : 32;
        } WKUPFFL_B;
    };

    union
    {
        __IOM uint32_t PMTCTRLSTS;
        struct
        {
            __IOM uint32_t PD                          : 1;
            __IOM uint32_t MPEN                        : 1;
            __IOM uint32_t WKUPFEN                     : 1;
            __IM  uint32_t RESERVED1                   : 2;
            __IOM uint32_t MPRX                        : 1;
            __IOM uint32_t WKUPFRX                     : 1;
            __IM  uint32_t RESERVED2                   : 2;
            __IOM uint32_t GUN                         : 1;
            __IM  uint32_t RESERVED3                   : 21;
            __IOM uint32_t WKUPFRST                    : 1;
        } PMTCTRLSTS_B;
    } ;

    __IM  uint32_t  RESERVED1;

    /** @brief DBG register */
    union
    {
        __IM  uint32_t DBG;
        struct
        {
            __IM  uint32_t RPESTS                      : 1;
            __IM  uint32_t RFCFCSTS                    : 2;
            __IM  uint32_t RESERVED1                   : 1;
            __IM  uint32_t RWCSTS                      : 1;
            __IM  uint32_t RRCSTS                      : 2;
            __IM  uint32_t RESERVED2                   : 1;
            __IM  uint32_t RXFSTS                      : 2;
            __IM  uint32_t RESERVED3                   : 6;
            __IM  uint32_t TPESTS                      : 1;
            __IM  uint32_t TFCSTS                      : 2;
            __IM  uint32_t TXPAUSED                    : 1;
            __IM  uint32_t TRCSTS                      : 2;
            __IM  uint32_t TWCSTS                      : 1;
            __IM  uint32_t RESERVED4                   : 1;
            __IM  uint32_t TXFSTS                      : 1;
            __IM  uint32_t TXSTSFSTS                   : 1;
            __IM  uint32_t RESERVED5                   : 6;
        } DBG_B;
    };

    /** @brief ISTS register */
    union
    {
        __IM  uint32_t ISTS;
        struct
        {
            __IM  uint32_t RESERVED1                   : 3;
            __IM  uint32_t PMTIS                       : 1;
            __IM  uint32_t MMCIS                       : 1;
            __IM  uint32_t MMCRXIS                     : 1;
            __IM  uint32_t MMCTXIS                     : 1;
            __IM  uint32_t RESERVED2                   : 2;
            __IM  uint32_t TSIS                        : 1;
            __IM  uint32_t RESERVED3                   : 22;
        } ISTS_B;
    };

    /** @brief IMASK register */
    union
    {
        __IOM uint32_t IMASK;
        struct
        {
            __IM  uint32_t RESERVED1                   : 3;
            __IOM uint32_t PMTIM                       : 1;
            __IM  uint32_t RESERVED2                   : 5;
            __IOM uint32_t TSTIM                       : 1;
            __IM  uint32_t RESERVED3                   : 6;
        } IMASK_B;
    };

    /** @brief ADDR0H register */
    union
    {
        __IOM uint32_t ADDR0H;
        struct
        {
            __IOM uint32_t ADDR0H                      : 16;
            __IM  uint32_t RESERVED                    : 15;
            __IM  uint32_t AL1                         : 1;
        } ADDR0H_B;
    };

    /** @brief ADDR0L register */
    union
    {
        __IOM uint32_t ADDR0L;
        struct
        {
            __IOM uint32_t ADDR0L                      : 32;
        } ADDR0L_B;
    };

    /** @brief ADDR1H register */
    union
    {
        __IOM uint32_t ADDR1H;
        struct
        {
            __IOM uint32_t ADDR1H                      : 16;
            __IM  uint32_t RESERVED                    : 8;
            __IOM uint32_t MASKBCTRL                   : 6;
            __IOM uint32_t ADDRSEL                     : 1;
            __IOM uint32_t ADDREN                      : 1;
        } ADDR1H_B;
    };

    /** @brief ADDR1L register */
    union
    {
        __IOM uint32_t ADDR1L;
        struct
        {
            __IOM uint32_t ADDR1L                      : 32;
        } ADDR1L_B;
    };

    /** @brief ADDR2H register */
    union
    {
        __IOM uint32_t ADDR2H;
        struct
        {
            __IOM uint32_t ADDR2H                      : 16;
            __IM  uint32_t RESERVED                    : 8;
            __IOM uint32_t MASKBCTRL                   : 6;
            __IOM uint32_t ADDRSEL                     : 1;
            __IOM uint32_t ADDREN                      : 1;
        } ADDR2H_B;
    };

    /** @brief ADDR2L register */
    union
    {
        __IOM uint32_t ADDR2L;
        struct
        {
            __IOM uint32_t ADDR2L                      : 32;
        } ADDR2L_B;
    };

    /** @brief ADDR3H register */
    union
    {
        __IOM uint32_t ADDR3H;
        struct
        {
            __IOM uint32_t ADDR3H                      : 16;
            __IM  uint32_t RESERVED                    : 8;
            __IOM uint32_t MASKBCTRL                   : 6;
            __IOM uint32_t ADDRSEL                     : 1;
            __IOM uint32_t ADDREN                      : 1;
        } ADDR3H_B;
    };

    /** @brief ADDR3L register */
    union
    {
        __IOM uint32_t ADDR3L;
        struct
        {
            __IOM uint32_t ADDR3L                      : 32;
        } ADDR3L_B;
    };

    __IM uint32_t RESERVED2[40];
    /**
     * @brief MAC management counters (MMC)
     */
    /** Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM uint32_t CNTRST          : 1;
            __IOM uint32_t CNTSTOPRO       : 1;
            __IOM uint32_t RSTOR           : 1;
            __IOM uint32_t MCNTF           : 1;
            __IOM uint32_t MCNTP           : 1;
            __IOM uint32_t MCNTVALP        : 1;
            __IM  uint32_t RESERVED        : 26;
        } CTRL_B;
    } ;

    /** RX Interrupt Register */
    union
    {
        __IOM uint32_t RXINT;

        struct
        {
            __IM  uint32_t RESERVED1       : 5;
            __IM  uint32_t RXFCE           : 1;
            __IM  uint32_t RXFAE           : 1;
            __IM  uint32_t RESERVED2       : 10;
            __IM  uint32_t RXGUNF          : 1;
            __IM  uint32_t RESERVED3       : 14;
        } RXINT_B;
    } ;

    /** TX Interrupt Register */
    union
    {
        __IOM uint32_t TXINT;

        struct
        {
            __IM  uint32_t RESERVED1       : 14;
            __IM  uint32_t TXGFSCOL        : 1;
            __IM  uint32_t TXGFMCOL        : 1;
            __IM  uint32_t RESERVED2       : 5;
            __IM  uint32_t TXGF            : 1;
            __IM  uint32_t RESERVED3       : 10;
        } TXINT_B;
    } ;

    /** RX Interrupt Mask Register */
    union
    {
        __IOM uint32_t RXINTMASK;

        struct
        {
            __IM  uint32_t RESERVED1       : 5;
            __IOM uint32_t RXFCEM          : 1;
            __IOM uint32_t RXFAEM          : 1;
            __IM  uint32_t RESERVED2       : 10;
            __IOM uint32_t RXGUNFM         : 1;
            __IM  uint32_t RESERVED3       : 14;
        } RXINTMASK_B;
    } ;

    /** TX Interrupt Mask Register */
    union
    {
        __IOM uint32_t TXINTMASK;

        struct
        {
            __IM  uint32_t RESERVED1       : 14;
            __IOM uint32_t TXGFSCOLM       : 1;
            __IOM uint32_t TXGFMCOLM       : 1;
            __IM  uint32_t RESERVED2       : 5;
            __IOM uint32_t TXGFM           : 1;
            __IM  uint32_t RESERVED3       : 10;
        } TXINTMASK_B;
    } ;

    __IM  uint32_t  RESERVED3[14];

    /** TX Good Frames After a Single Collision Counter Register */
    union
    {
        __IM uint32_t TXGFSCCNT;

        struct
        {
            __IM  uint32_t TXGFSCCNT       : 32;
        } TXGFSCCNT_B;
    } ;

    /** TX Good Frames After More Than a Single Collision Counter Register */
    union
    {
        __IM uint32_t TXGFMCCNT;

        struct
        {
            __IM  uint32_t TXGFMCCNT       : 32;
        } TXGFMCCNT_B;
    } ;

    __IM  uint32_t  RESERVED4[5];

    /** TX Good Frames Counter Register */
    union
    {
        __IM uint32_t TXGFCNT;

        struct
        {
            __IM  uint32_t TXGFCNT       : 32;
        } TXGFCNT_B;
    } ;

    __IM  uint32_t  RESERVED5[10];

    /** RX Frames With CRC Error Counter Register */
    union
    {
        __IM uint32_t RXFCECNT;

        struct
        {
            __IM  uint32_t RXFCECNT       : 32;
        } RXFCECNT_B;
    } ;

    /** RX Frames With Alignment Error Counter Register */
    union
    {
        __IM uint32_t RXFAECNT;

        struct
        {
            __IM  uint32_t RXFAECNT       : 32;
        } RXFAECNT_B;
    } ;

    __IM  uint32_t  RESERVED6[10];

    /** RX Good Unicast Frames Counter Register */
    union
    {
        __IM uint32_t RXGUNCNT;

        struct
        {
            __IM  uint32_t RXGUNCNT       : 32;
        } RXGUNCNT_B;
    } ;

    __IM  uint32_t  RESERVED7[334];

    /**
      * @brief Ethernet: Precision time protocol (Ethernet_PTP)
      */
    union
    {
        __IOM uint32_t TSCTRL;                      /*!< (@ 0x00000000) Ethernet PTP time stamp control register                   */

        struct
        {
            __IOM uint32_t TSEN       : 1;            /*!< [0..0] Time Stamp Enable                                                  */
            __IOM uint32_t TSUDSEL    : 1;            /*!< [1..1] Time Stamp Update Mode Select                                      */
            __IOM uint32_t TSSTINIT   : 1;            /*!< [2..2] Time Stamp System Time Initialize                                  */
            __IOM uint32_t TSSTUD     : 1;            /*!< [3..3] Time Stamp System Time Update                                      */
            __IOM uint32_t TSTRGIEN   : 1;            /*!< [4..4] Time Stamp Trigger Interrupt Enable                                */
            __IOM uint32_t TSADDUD    : 1;            /*!< [5..5] Time Stamp Addend Register Update                                  */
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t TSSNEN     : 1;            /*!< [8..8] Time Stamp Snapshot for Received Frames Enable                     */
            __IOM uint32_t TSSUBRO    : 1;            /*!< [9..9] Time Stamp Subsecond Rollover                                      */
            __IOM uint32_t LISTVSEL   : 1;            /*!< [10..10] Listening Version Select                                         */
            __IOM uint32_t TSSPTPEN   : 1;            /*!< [11..11] Time Stamp Snapshot for PTP Ethernet Frames Enable               */
            __IOM uint32_t TSS6EN     : 1;            /*!< [12..12] Time stamp snapshot for IPv6 frames Enable                       */
            __IOM uint32_t TSS4EN     : 1;            /*!< [13..13] Time Stamp Snapshot for IPv4 Frames Enable                       */
            __IOM uint32_t TSSMESEL   : 1;            /*!< [14..14] Time Stamp Snapshot for Message Select                           */
            __IOM uint32_t TSSMNSEL   : 1;            /*!< [15..15] Time Stamp Snapshot for Master Node Select                       */
            __IOM uint32_t TSCLKNSEL  : 2;            /*!< [17..16] Time stamp Clock Node Select                                     */
            __IOM uint32_t TSSPTPFMACEN : 1;          /*!< [18..18] Time Stamp PTP Frame Filtering MAC Address Enable                */
            __IM  uint32_t RESERVED12  : 13;
        } TSCTRL_B;
    } ;

    union
    {
        __IOM uint32_t SUBSECI;                     /*!< (@ 0x00000004) Ethernet PTP subsecond increment register                  */

        struct
        {
            __IOM uint32_t STSUBSECI  : 8;            /*!< [7..0] System Time Subseconds Incremen                                    */
            __IM  uint32_t RESERVED   : 24;
        } SUBSECI_B;
    } ;

    union
    {
        __IM  uint32_t TSH;                         /*!< (@ 0x00000008) Ethernet PTP time stamp high register                      */

        struct
        {
            __IM  uint32_t STSEC      : 32;           /*!< [31..0] System Time Second Value                                          */
        } TSH_B;
    } ;

    union
    {
        __IM  uint32_t TSL;                         /*!< (@ 0x0000000C) Ethernet PTP time stamp low register                       */

        struct
        {
            __IM  uint32_t STSUBSEC   : 31;           /*!< [30..0] System Time Subseconds Value                                      */
            __IM  uint32_t STSEL      : 1;            /*!< [31..31] System Time Select                                               */
        } TSL_B;
    } ;

    union
    {
        __IOM uint32_t TSHUD;                       /*!< (@ 0x00000010) Ethernet PTP time stamp high update register               */

        struct
        {
            __IOM uint32_t TSUDSEC    : 32;           /*!< [31..0] Time Stamp Update Second Value                                    */
        } TSHUD_B;
    } ;

    union
    {
        __IOM uint32_t TSLUD;                       /*!< (@ 0x00000014) Ethernet PTP time stamp low update register                */

        struct
        {
            __IOM uint32_t TSUDSUBSEC : 31;           /*!< [30..0] Time Stamp Update Subseconds Value                                */
            __IOM uint32_t TSUDSEL    : 1;            /*!< [31..31] Time Stamp Update Select                                         */
        } TSLUD_B;
    } ;

    union
    {
        __IOM uint32_t TSA;                         /*!< (@ 0x00000018) Ethernet PTP time stamp addend register                    */

        struct
        {
            __IOM uint32_t TSA        : 32;           /*!< [31..0] Time Stamp Addend Value                                           */
        } TSA_B;
    } ;

    union
    {
        __IOM uint32_t TTSH;                        /*!< (@ 0x0000001C) Ethernet PTP target time high register                     */

        struct
        {
            __IOM uint32_t TTSH       : 32;           /*!< [31..0] Target Time Stamp High Value                                      */
        } TTSH_B;
    } ;

    union
    {
        __IOM uint32_t TTSL;                        /*!< (@ 0x00000020) Ethernet PTP target time low register                      */

        struct
        {
            __IOM uint32_t TTSL       : 32;           /*!< [31..0] Target Time Stamp Low Value                                       */
        } TTSL_B;
    } ;
    __IM  uint32_t  RESERVED8;

    union
    {
        __IM  uint32_t TSSTS;                       /*!< (@ 0x00000028) Ethernet PTP time stamp status register                    */

        struct
        {
            __IM  uint32_t TSSECOVR   : 1;            /*!< [0..0] Time Stamp Second Value Overflow                                   */
            __IM  uint32_t TTSRD      : 1;            /*!< [1..1] Target Time Stamp Value Reached                                    */
            __IM  uint32_t RESERVED   : 30;
        } TSSTS_B;
    } ;

    union
    {
        __IM  uint32_t PPSCTRL;                     /*!< (@ 0x0000002C) Ethernet PTP PPS control register                          */

        struct
        {
            __IM  uint32_t PPSFSEL    : 4;            /*!< [3..0] PPS Frequency Selection                                            */
            __IM  uint32_t RESERVED   : 28;
        } PPSCTRL_B;
    } ;

    __IM  uint32_t  RESERVED9[564];

    /**
      * @brief Ethernet: DMA controller operation (Ethernet_DMA)
      */
    union
    {
        __IOM uint32_t DMABMOD;                     /*!< (@ 0x00000000) Ethernet DMA bus mode register                             */

        struct
        {
            __IOM uint32_t SWR        : 1;            /*!< [0..0] Software Reset                                                     */
            __IOM uint32_t DAS        : 1;            /*!< [1..1] DMA Arbitration Scheme                                             */
            __IOM uint32_t DSL        : 5;            /*!< [6..2] Descriptor Skip Length                                             */
            __IOM uint32_t EDFEN      : 1;            /*!< [7..7] Enhanced Descriptor Format Enable                                  */
            __IOM uint32_t PBL        : 6;            /*!< [13..8] Programmable Burst Length                                         */
            __IOM uint32_t PR         : 2;            /*!< [15..14] Priority Ratio                                                   */
            __IOM uint32_t FB         : 1;            /*!< [16..16] Fixed Burst                                                      */
            __IOM uint32_t RPBL       : 6;            /*!< [22..17] Rx DMA PBL                                                       */
            __IOM uint32_t USP        : 1;            /*!< [23..23] Use Separate PBL                                                 */
            __IOM uint32_t PBLx4      : 1;            /*!< [24..24] PBLx4 Mode                                                       */
            __IOM uint32_t AAL        : 1;            /*!< [25..25] Address-Aligned Beats                                            */
            __IOM uint32_t MB         : 1;            /*!< [26..26] Mixed Burst                                                      */
            __IM  uint32_t RESERVED   : 5;
        } DMABMOD_B;
    } ;

    union
    {
        __IOM uint32_t DMATXPD;                     /*!< (@ 0x00000004) Ethernet DMA transmit poll demand register                 */

        struct
        {
            __IOM uint32_t TXPD       : 32;           /*!< [31..0] Transmit Poll Demand                                              */
        } DMATXPD_B;
    } ;

    union
    {
        __IOM uint32_t DMARXPD;                     /*!< (@ 0x00000008) EHERNET DMA receive poll demand register                   */

        struct
        {
            __IOM uint32_t RXPD       : 32;           /*!< [31..0] Receive Poll Demand                                               */
        } DMARXPD_B;
    } ;

    union
    {
        __IOM uint32_t DMARXDLADDR;                 /*!< (@ 0x0000000C) Ethernet DMA receive descriptor list address
                                                                    register                                                   */

        struct
        {
            __IOM uint32_t RXSTA      : 32;           /*!< [31..0] Start of Receive List                                             */
        } DMARXDLADDR_B;
    } ;

    union
    {
        __IOM uint32_t DMATXDLADDR;                 /*!< (@ 0x00000010) Ethernet DMA transmit descriptor list address
                                                                    register                                                   */

        struct
        {
            __IOM uint32_t TXSTA      : 32;           /*!< [31..0] Start of Transmit List                                            */
        } DMATXDLADDR_B;
    } ;

    union
    {
        __IOM uint32_t DMASTS;                      /*!< (@ 0x00000014) Ethernet DMA status register                               */

        struct
        {
            __IOM uint32_t TXFLG      : 1;            /*!< [0..0] Transmit Flag                                                      */
            __IOM uint32_t TXSFLG     : 1;            /*!< [1..1] Transmit Stopped Flag                                              */
            __IOM uint32_t TXBU       : 1;            /*!< [2..2] Transmit Buffer Unavailable                                        */
            __IOM uint32_t TXJTO      : 1;            /*!< [3..3] Transmit Jabber Timeout                                            */
            __IOM uint32_t RXOVF      : 1;            /*!< [4..4] Receive Overflow                                                   */
            __IOM uint32_t TXUNF      : 1;            /*!< [5..5] Transmit Underflow                                                 */
            __IOM uint32_t RXFLG      : 1;            /*!< [6..6] Receive Flag                                                       */
            __IOM uint32_t RXBU       : 1;            /*!< [7..7] Receive Buffer Unavailable                                         */
            __IOM uint32_t RXSFLG     : 1;            /*!< [8..8] Receive Stopped Flag                                               */
            __IOM uint32_t RXWTOFLG   : 1;            /*!< [9..9] Receive Watchdog Timeout Flag                                      */
            __IOM uint32_t ETXFLG     : 1;            /*!< [10..10] Early Transmit Flag                                              */
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t FBERRFLG   : 1;            /*!< [13..13] Fatal Bus Error Flag                                             */
            __IOM uint32_t ERXFLG     : 1;            /*!< [14..14] Early Receive Flag                                               */
            __IOM uint32_t AINTS      : 1;            /*!< [15..15] Abnormal Interrupt Summary                                       */
            __IOM uint32_t NINTS      : 1;            /*!< [16..16] Normal Interrupt Summary                                         */
            __IM  uint32_t RXSTS      : 3;            /*!< [19..17] Receive Process State                                            */
            __IM  uint32_t TXSTS      : 3;            /*!< [22..20] Transmit Process State                                           */
            __IM  uint32_t ERRB       : 3;            /*!< [25..23] Error Bits                                                       */
            __IM  uint32_t RESERVED2  : 1;
            __IM  uint32_t MMCFLG     : 1;            /*!< [27..27] MMC Flag                                                         */
            __IM  uint32_t PMTFLG     : 1;            /*!< [28..28] PMT Flag                                                         */
            __IM  uint32_t TSTFLG     : 1;            /*!< [29..29] Timestamp Trigger Flag                                           */
            __IM  uint32_t RESERVED3  : 2;
        } DMASTS_B;
    } ;

    union
    {
        __IOM uint32_t DMAOPMOD;                    /*!< (@ 0x00000018) Ethernet DMA operation mode register                       */

        struct
        {
            __IM  uint32_t            : 1;
            __IOM uint32_t STRX       : 1;            /*!< [1..1] Start or Stop Receive                                              */
            __IOM uint32_t OSECF      : 1;            /*!< [2..2] Operate on Second Frame                                            */
            __IOM uint32_t RXTHCTRL   : 2;            /*!< [4..3] Receive Threshold Control                                          */
            __IM  uint32_t RESERVED1  : 1;
            __IOM uint32_t FUF        : 1;            /*!< [6..6] Forward Undersized Good Frames                                     */
            __IOM uint32_t FERRF      : 1;            /*!< [7..7] Forward Error Frames                                               */
            __IM  uint32_t RESERVED2  : 5;
            __IOM uint32_t STTX       : 1;            /*!< [13..13] Start or Stop Transmission Command                               */
            __IOM uint32_t TXTHCTRL   : 3;            /*!< [16..14] Transmit Threshold Control                                       */
            __IM  uint32_t RESERVED3  : 3;
            __IOM uint32_t FTXF       : 1;            /*!< [20..20] Flush Transmit FIFO                                              */
            __IOM uint32_t TXSF       : 1;            /*!< [21..21] Transmit Store and Forward                                       */
            __IM  uint32_t RESERVED4  : 2;
            __IOM uint32_t DISFRXF    : 1;            /*!< [24..24] Disable Flushing of Received Frames                              */
            __IOM uint32_t RXSF       : 1;            /*!< [25..25] Receive Store and Forward                                        */
            __IOM uint32_t DISDT      : 1;            /*!< [26..26] Disable Dropping of TCP/IP Checksum Error Frames                 */
            __IM  uint32_t RESERVED5  : 5;
        } DMAOPMOD_B;
    } ;

    union
    {
        __IOM uint32_t DMAINTEN;                    /*!< (@ 0x0000001C) Ethernet DMA interrupt enable register                     */

        struct
        {
            __IOM uint32_t TXIEN      : 1;            /*!< [0..0] Transmit Interrupt Enable                                          */
            __IOM uint32_t TXSEN      : 1;            /*!< [1..1] Transmit Stopped Enable                                            */
            __IOM uint32_t TXBUEN     : 1;            /*!< [2..2] Transmit Buffer Unavailable Enable                                 */
            __IOM uint32_t TXJTOEN    : 1;            /*!< [3..3] Transmit Jabber Timeout Enable                                     */
            __IOM uint32_t RXOVFEN    : 1;            /*!< [4..4] Receive Overflow Interrupt Enable                                  */
            __IOM uint32_t TXUNFEN    : 1;            /*!< [5..5] Transmit Underflow Interrupt Enable                                */
            __IOM uint32_t RXIEN      : 1;            /*!< [6..6] Receive Interrupt Enable                                           */
            __IOM uint32_t RXBUEN     : 1;            /*!< [7..7] Receive Buffer Unavailable Enable                                  */
            __IOM uint32_t RXSEN      : 1;            /*!< [8..8] Receive Stopped Enable                                             */
            __IOM uint32_t RXWTOEN    : 1;            /*!< [9..9] Receive Watchdog Timeout Enable                                    */
            __IOM uint32_t ETXIEN     : 1;            /*!< [10..10] Early Transmit Interrupt Enable                                  */
            __IM  uint32_t RESERVED1  : 2;
            __IOM uint32_t FBERREN    : 1;            /*!< [13..13] Fatal Bus Error Enable                                           */
            __IOM uint32_t ERXIEN     : 1;            /*!< [14..14] Early Receive Interrupt Enable                                   */
            __IOM uint32_t AINTSEN    : 1;            /*!< [15..15] Abnormal Interrupt Summary Enable                                */
            __IOM uint32_t NINTSEN    : 1;            /*!< [16..16] Normal Interrupt Summary Enable                                  */
            __IM  uint32_t RESERVED2  : 15;
        } DMAINTEN_B;
    } ;

    union
    {
        __IOM uint32_t DMAMFABOCNT;                 /*!< (@ 0x00000020) Ethernet DMA missed frame and buffer overflow
                                                                    counter register                                           */

        struct
        {
            __IOM uint32_t MISFCNT    : 16;           /*!< [15..0] Missed Frame Counter                                              */
            __IOM uint32_t MISFCNTOVF : 1;            /*!< [16..16] Overflow Bit for Missed Frame Counter                            */
            __IOM uint32_t AMISFCNT   : 11;           /*!< [27..17] Missed Frame Counter                                             */
            __IOM uint32_t OVFCNTOVF  : 1;            /*!< [28..28] Overflow Bit for FIFO Overflow Counter                           */
            __IM  uint32_t RESERVED   : 3;
        } DMAMFABOCNT_B;
    } ;

    union
    {
        __IOM uint32_t DMARXFLGWDT;                 /*!< (@ 0x00000024) Ethernet DMA receive status watchdog timer register        */

        struct
        {
            __IOM uint32_t RXWDTCNT   : 8;            /*!< [7..0] RXFLG Watchdog Timer Count                                         */
            __IM  uint32_t RESERVED   : 24;
        } DMARXFLGWDT_B;
    } ;
    __IM  uint32_t  RESERVED10[8];

    union
    {
        __IM  uint32_t DMAHTXD;                     /*!< (@ 0x00000048) Ethernet DMA current host transmit descriptor
                                                                    register                                                   */
        struct
        {
            __IM  uint32_t HTXDADDRP  : 32;           /*!< [31..0] Host Transmit Descriptor Address Pointer                          */
        } DMAHTXD_B;
    } ;

    union
    {
        __IM  uint32_t DMAHRXD;                     /*!< (@ 0x0000004C) Ethernet DMA current host receive descriptor
                                                                    register                                                   */
        struct
        {
            __IM  uint32_t HRXDADDRP  : 32;           /*!< [31..0] Host Receive Descriptor Address Pointer                           */
        } DMAHRXD_B;
    } ;

    union
    {
        __IM  uint32_t DMAHTXBADDR;                 /*!< (@ 0x00000050) Ethernet DMA current host transmit buffer address
                                                                    register                                                   */

        struct
        {
            __IM  uint32_t HTXBADDRP  : 32;           /*!< [31..0] Host Transmit Buffer Address Pointer                              */
        } DMAHTXBADDR_B;
    } ;

    union
    {
        __IM  uint32_t DMAHRXBADDR;                 /*!< (@ 0x00000054) Ethernet DMA current host receive buffer address
                                                                    register                                                   */

        struct
        {
            __IM  uint32_t HRXBADDRP  : 32;           /*!< [31..0] Host Receive Buffer Address Pointer                               */
        } DMAHRXBADDR_B;
    } ;
} ETH_T;

/**
 * @brief    CRYP register (CRYP)
 */
typedef struct
{
    /** @brief Control register  */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IM  uint32_t RESERVED1       : 2;
            __IOM uint32_t ALGODIRSEL      : 1;
            __IOM uint32_t ALGOMSEL        : 3;
            __IOM uint32_t DTSEL           : 2;
            __IOM uint32_t KSIZESEL        : 2;
            __IM  uint32_t RESERVED2       : 4;
            __IOM uint32_t FFLUSH          : 1;
            __IOM uint32_t CRYPEN          : 1;
            __IM  uint32_t RESERVED3       : 16;
        } CTRL_B;
    } ;

    /** @brief Status register */
    union
    {
        __IM uint32_t STS;

        struct
        {
            __IM  uint32_t IFEMPT         : 1;
            __IM  uint32_t IFFULL         : 1;
            __IM  uint32_t OFEMPT         : 1;
            __IM  uint32_t OFFULL         : 1;
            __IM  uint32_t BUSY           : 1;
            __IM  uint32_t RESERVED       : 27;
        } STS_B;
    };

    /** @brief Input data register */
    union
    {
        __IOM uint32_t DATAIN;

        struct
        {
            __IOM uint32_t DATAIN          : 32;
        } DATAIN_B;
    };

    /** @brief Output data register */
    union
    {
        __IM uint32_t DATAOUT;

        struct
        {
            __IM uint32_t DATAOUT          : 32;
        } DATAOUT_B;
    };

    /** @brief Control DMA register */
    union
    {
        __IOM uint32_t DMACTRL;

        struct
        {
            __IOM uint32_t INEN             : 1;
            __IOM uint32_t OUTEN            : 1;
            __IM  uint32_t RESERVED         : 30;
        } DMACTRL_B;
    };

    /** @brief Service Interrupt Mask register */
    union
    {
        __IOM uint32_t INTMASK;

        struct
        {
            __IOM uint32_t INIMASK          : 1;
            __IOM uint32_t OUTIMASK         : 1;
            __IM  uint32_t RESERVED         : 30;
        } INTMASK_B;
    };

    /** @brief Service Raw Interrupt Status register */
    union
    {
        __IM uint32_t INTSTS;

        struct
        {
            __IM uint32_t INISTS            : 1;
            __IM uint32_t OUTISTS           : 1;
            __IM  uint32_t RESERVED         : 30;
        } INTSTS_B;
    };

    /** @brief Service Masked Interrupt Status register */
    union
    {
        __IOM uint32_t MINTSTS;

        struct
        {
            __IOM uint32_t INMISTS           : 1;
            __IOM uint32_t OUTMISTS          : 1;
            __IM  uint32_t RESERVED          : 30;
        } MINTSTS_B;
    };

    /** @brief Key0L register */
    union
    {
        __OM uint32_t K0L;

        struct
        {
            __OM  uint32_t Bx         : 32;
        } K0L_B;
    };

    /** @brief Key0R register */
    union
    {
        __OM uint32_t K0R;

        struct
        {
            __OM  uint32_t Bx         : 32;
        } K0R_B;
    };

    /** @brief Key1L register */
    union
    {
        __OM uint32_t K1L;

        struct
        {
            __OM  uint32_t KyBx         : 32;
        } K1L_B;
    };

    /** @brief Key1R register */
    union
    {
        __OM uint32_t K1R;

        struct
        {
            __OM  uint32_t KyBx         : 32;
        } K1R_B;
    };

    /** @brief Key2L register */
    union
    {
        __OM uint32_t K2L;

        struct
        {
            __OM  uint32_t KyBx         : 32;
        } K2L_B;
    };

    /** @brief Key2R register */
    union
    {
        __OM uint32_t K2R;

        struct
        {
            __OM  uint32_t KyBx         : 32;
        } K2R_B;
    };

    /** @brief Key3L register */
    union
    {
        __OM uint32_t K3L;

        struct
        {
            __OM  uint32_t KyBx         : 32;
        } K3L_B;
    };

    /** @brief Key3R register */
    union
    {
        __OM uint32_t K3R;

        struct
        {
            __OM  uint32_t KyBx         : 32;
        } K3R_B;
    };

    /** @brief Initialize the vector register register */
    union
    {
        __IOM uint32_t IV0L;

        struct
        {
            __IOM  uint32_t IVx         : 32;
        } IV0L_B;
    };

    /** @brief Initialize the vector register register */
    union
    {
        __IOM uint32_t IV0R;

        struct
        {
            __IOM  uint32_t IVx         : 32;
        } IV0R_B;
    };

    /** @brief Initialize the vector register register */
    union
    {
        __IOM uint32_t IV1L;

        struct
        {
            __IOM  uint32_t IVx         : 32;
        } IV1L_B;
    };

    /** @brief Initialize the vector register register */
    union
    {
        __IOM uint32_t IV1R;

        struct
        {
            __IOM  uint32_t IVx         : 32;
        } IV1R_B;
    };

} CRYP_T;

/**
* @brief The registers of HASH
*/
typedef struct
{
    /** @brief HASH Control register */
    union
    {
        __IOM uint32_t CTRL;
        struct
        {
            __IM  uint32_t RESERVED        : 2;
            __IOM uint32_t INITCAL         : 1;
            __IOM uint32_t DMAEN           : 1;
            __IOM uint32_t DTYPE           : 2;
            __IOM uint32_t MODESEL         : 1;
            __IOM uint32_t ALGSEL          : 1;
            __IOM uint32_t WNUM            : 4;
            __IOM uint32_t DINNEMPT        : 1;
            __IM  uint32_t RESERVED1       : 3;
            __IOM uint32_t LKEYSEL         : 1;
            __IM  uint32_t RESERVED2       : 15;
        } CTRL_B;
    };

    /** @brief HASH Input Data register */
    union
    {
        __IOM uint32_t INDATA;
        struct
        {
            __IOM uint32_t INDATA         : 32;
        } INDATA_B;
    };

    /** @brief HASH Start register */
    union
    {
        __IOM uint32_t START;
        struct
        {
            __IOM uint32_t LWNUM          : 5;
            __IM  uint32_t RESERVED1      : 3;
            __OM  uint32_t DIGCAL         : 1;
            __IM  uint32_t RESERVED2      : 23;
        } START_B;
    };

    __IO uint32_t DIG[5];

    /** @brief HASH interrupt enable register */
    union
    {
        __IOM uint32_t INT;
        struct
        {
            __IOM uint32_t INDATA         : 1;
            __IOM uint32_t DCALC          : 1;
            __IM  uint32_t RESERVED1      : 30;
        } INT_B;
    };

    /** @brief HASH status register */
    union
    {
        __IOM uint32_t STS;
        struct
        {
            __IOM uint32_t INDATAINT      : 1;
            __IOM uint32_t DCALCINT       : 1;
            __IM  uint32_t DMA            : 1;
            __IM  uint32_t BUSY           : 1;
            __IM  uint32_t RESERVED       : 28;
        } STS_B;
    };

    __IM uint32_t RESERVED[52];

    /** @brief HASH context swap register */
    __IOM uint32_t CTSWAP[51];

} HASH_T;

/**
 * @brief    Random Number Generator (RNG)
 */
typedef struct
{
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IM   uint32_t RESERVED       : 2;
            __IOM  uint32_t RNGEN          : 1;
            __IOM  uint32_t INTEN          : 1;
            __IM   uint32_t RESERVED1      : 28;
        } CTRL_B;
    };

    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IM   uint32_t DATARDY        : 1;
            __IM   uint32_t CLKERCSTS      : 1;
            __IM   uint32_t FSCSTS         : 1;
            __IM   uint32_t RESERVED1      : 2;
            __IOM  uint32_t CLKERINT       : 1;
            __IOM  uint32_t FSINT          : 1;
            __IM   uint32_t RESERVED2      : 25;
        } STS_B;
    };

    union
    {
        __IM uint32_t DATA;

        struct
        {
            __IM   uint32_t DATA           : 32;
        } DATA_B;
    };
} RNG_T;

/**
 * @brief    Big number module (BN)
 */
typedef struct
{
    /** Revision register */
    union
    {
        __IM uint32_t REV;

        struct
        {
            __IM   uint32_t MIN            : 8;
            __IM   uint32_t MID            : 8;
            __IM   uint32_t MAJ            : 8;
            __IM   uint32_t RESERVED       : 8;
        } REV_B;

    };

    /** Control register */
    union
    {
        __IOM uint32_t CTRL;

        struct
        {
            __IOM   uint32_t START          : 1;
            __IOM   uint32_t SP             : 3;
            __IOM   uint32_t SELECT         : 4;
            __IOM   uint32_t IE             : 1;
            __IM    uint32_t RESERVED       : 23;
        } CTRL_B;

    };

    /** Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM   uint32_t DONE           : 1;
            __IOM   uint32_t BUSY           : 1;
            __IOM   uint32_t CB             : 1;
            __IOM   uint32_t TR             : 1;
            __IOM   uint32_t INF            : 1;
            __IOM   uint32_t EVEN           : 1;
            __IOM   uint32_t ZERO           : 1;
            __IOM   uint32_t ATTACKED       : 1;
            __IOM   uint32_t BLEN           : 16;
            __IM    uint32_t RESERVED       : 8;
        } STS_B;
    };

    /**  Operand Width register */
    union
    {
        __IOM uint32_t WID;

        struct
        {
            __IOM   uint32_t PWID           : 7;
            __IM    uint32_t RESERVED       : 7;
            __IOM   uint32_t KWID           : 4;
            __IM    uint32_t RESERVED1      : 14;
        } WID_B;
    };

    __IM uint32_t        RESERVED[12];

    /** P/M register */
    union
    {
        __IOM uint32_t P;

        struct
        {
            __IOM   uint32_t P_REG           : 32;
        } P_B;
    };

    /** BN Operand/EC Parameter A register */
    union
    {
        __IOM uint32_t A;

        struct
        {
            __IOM   uint32_t A_REG           : 32;
        } A_B;
    };

    /** BN Operand/EC Parameter B register */
    union
    {
        __IOM uint32_t B;

        struct
        {
            __IOM   uint32_t B_REG           : 32;
        } B_B;
    };

    /** ECC Key register */
    union
    {
        __IOM uint32_t K;

        struct
        {
            __IOM   uint32_t K_REG           : 32;
        } K_B;
    };

    /** ECC PX register */
    union
    {
        __IOM uint32_t PX;

        struct
        {
            __IOM   uint32_t PX_REG           : 32;
        } PX_B;
    };

    /** ECC PY register */
    union
    {
        __IOM uint32_t PY;

        struct
        {
            __IOM   uint32_t PY_REG           : 32;
        } PY_B;
    };

    /** ECC SX register */
    union
    {
        __IOM uint32_t SX;

        struct
        {
            __IOM   uint32_t SX_REG           : 32;
        } SX_B;
    };

    /** ECC SY register */
    union
    {
        __IOM uint32_t SY;

        struct
        {
            __IOM   uint32_t SY_REG           : 32;
        } SY_B;
    };

    /** ECC Result RX register */
    union
    {
        __IM uint32_t RX;

        struct
        {
            __IM   uint32_t RX_REG           : 32;
        } RX_B;
    };

    /** ECC Result RY register */
    union
    {
        __IM uint32_t RY;

        struct
        {
            __IM   uint32_t RY_REG           : 32;
        } RY_B;
    };

    /** Random Number register */
    union
    {
        __OM uint32_t RND;

        struct
        {
            __OM   uint32_t RND_REG          : 32;
        } RND_B;
    };
} BN_T;

/**
 * @brief    SM3
 */
typedef struct
{
    /** Revision Register */
    union
    {
        __IM uint32_t REV;

        struct
        {
            __IM   uint32_t MIN            : 8;
            __IM   uint32_t MID            : 8;
            __IM   uint32_t MAJ            : 8;
            __IM   uint32_t RESERVED       : 8;
        } REV_B;
    };

    /** Control Register */
    union
    {
        __IOM uint32_t CTRL;
        struct
        {
            __IOM   uint32_t START          : 1;
            __IOM   uint32_t IE             : 1;
            __IOM   uint32_t INIMODE        : 1;
            __IOM   uint32_t PADMODE        : 1;
            __IOM   uint32_t ENDIAN         : 1;
            __IM    uint32_t RESERVED       : 27;
        } CTRL_B;
    };

    /** Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM   uint32_t DONE           : 1;
            __IOM   uint32_t BUSY           : 1;
            __IM    uint32_t RESERVED       : 30;
        } STS_B;
    };

    /** Data input length higher register */
    union
    {
        __OM uint32_t DILH;

        struct
        {
            __OM   uint32_t DATA           : 32;
        } DILH_B;
    };

    /** Data input length lower register */
    union
    {
        __OM uint32_t DILL;

        struct
        {
            __OM   uint32_t DATA           : 32;
        } DILL_B;
    };

    /** Input Message Register[16](0x14-0x50) */
    __IOM uint32_t DIN[16];
    /** Input Initial Value[8](0x54-0x70) */
    __IOM uint32_t IV[8];
    /** Output Message Digest Register[8](0x74-0x90) */
    __IM  uint32_t DOUT[8];

} SM3_T;

/**
 * @brief    SM4
 */
typedef struct
{
    /** Revision Register */
    union
    {
        __IM uint32_t REV;

        struct
        {
            __IM   uint32_t REC0           : 1;
            __IM   uint32_t REC1           : 1;
            __IM   uint32_t RESERVED       : 30;
        } REV_B;
    };

    /** Control Register */
    union
    {
        __IOM uint32_t CTRL;
        struct
        {
            __IOM   uint32_t START          : 1;
            __IOM   uint32_t IE             : 1;
            __IOM   uint32_t ENC            : 1;
            __IOM   uint32_t MODE           : 1;
            __IM    uint32_t RESERVED       : 28;
        } CTRL_B;
    };

    /** Status register */
    union
    {
        __IOM uint32_t STS;

        struct
        {
            __IOM   uint32_t DONE           : 1;
            __IOM   uint32_t BUSY           : 1;
            __IM    uint32_t RESERVED       : 30;
        } STS_B;
    };

    /** SM4 key register[4](0x0C..0x18) */
    __IOM uint32_t KEY[4];
    /** SM4 data input register[4](0x20..0x28) */
    __IOM uint32_t DIN[4];
    /** SM4 data output register[4](0x2C..0x38) */
    __IM  uint32_t DOUT[4];
    /** SM4 initial vector register[4](0x3C..0x48) */
    __IOM uint32_t IV[4];
} SM4_T;

/**
  * @}
  */

/** @defgroup Peripheral_memory_map
  @{
*/

/** FMC base address in the alias region */
#define FMC_BASE                ((uint32_t)0x08000000)
/** CCM(core coupled memory) data RAM(64 KB) base address in the alias region */
#define CCMDATARAM_BASE         ((uint32_t)0x10000000)
/** SRAM1 base address in the alias region */
#define SRAM1_BASE              ((uint32_t)0x20000000)
/** SRAM2 base address in the alias region */
#define SRAM2_BASE              ((uint32_t)0x2001C000)
/** SRAM3 base address in the alias region */
#define SRAM3_BASE              ((uint32_t)0x20020000)
/** Peripheral base address in the alias region */
#define PERIPH_BASE             ((uint32_t)0x40000000)
/** Backup SRAM(4 KB) base address in the alias region */
#define BKPSRAM_BASE            ((uint32_t)0x40024000)

/** CCM(core coupled memory) data RAM(64 KB) base address in the bit-band region */
#define CCMDATARAM_BB_BASE      ((uint32_t)0x12000000)
/** SRAM1 base address in the bit-band region */
#define SRAM1_BB_BASE           ((uint32_t)0x22000000)
/** SRAM2 base address in the bit-band region */
#define SRAM2_BB_BASE           ((uint32_t)0x22380000)
/** SRAM3 base address in the bit-band region */
#define SRAM3_BB_BASE           ((uint32_t)0x22400000)
/** Peripheral base address in the bit-band region */
#define PERIPH_BB_BASE          ((uint32_t)0x42000000)
/** Backup SRAM(4 KB) base address in the bit-band region */
#define BKPSRAM_BB_BASE         ((uint32_t)0x42480000)

/** Legacy defines */
#define SRAM_BASE               SRAM1_BASE
#define SRAM_BB_BASE            SRAM1_BB_BASE

/** EMMC registers base address */
#define SMC_R_BASE              ((uint32_t)0xA0000000)
/** QSPI registers base address */
#define QSPI_BASE               ((uint32_t)0xA0000000)
/** DMC registers base address */
#define DMC_BASE                ((uint32_t)0xA0000000)

/** Peripheral memory map */
#define APB1PERIPH_BASE         PERIPH_BASE
#define APB2PERIPH_BASE         (PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE         (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE         (PERIPH_BASE + 0x10000000)

/** APB1 peripherals */
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
#define I2S2ext_BASE            (APB1PERIPH_BASE + 0x3400)
#define SPI2_BASE               (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE               (APB1PERIPH_BASE + 0x3C00)
#define I2S3ext_BASE            (APB1PERIPH_BASE + 0x4000)
#define USART2_BASE             (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE             (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE              (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE              (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE               (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE               (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASE               (APB1PERIPH_BASE + 0x5C00)
#define CAN1_BASE               (APB1PERIPH_BASE + 0x6400)
#define CAN2_BASE               (APB1PERIPH_BASE + 0x6800)
#define PMU_BASE                (APB1PERIPH_BASE + 0x7000)
#define DAC_BASE                (APB1PERIPH_BASE + 0x7400)
#define UART7_BASE              (APB1PERIPH_BASE + 0x7800)
#define UART8_BASE              (APB1PERIPH_BASE + 0x7C00)

/** APB2 peripherals */
#define TMR1_BASE               (APB2PERIPH_BASE + 0x0000)
#define TMR8_BASE               (APB2PERIPH_BASE + 0x0400)
#define USART1_BASE             (APB2PERIPH_BASE + 0x1000)
#define USART6_BASE             (APB2PERIPH_BASE + 0x1400)
#define UART9_BASE              (APB2PERIPH_BASE + 0x1800U)
#define UART10_BASE             (APB2PERIPH_BASE + 0x1C00U)
#define ADC1_BASE               (APB2PERIPH_BASE + 0x2000)
#define ADC2_BASE               (APB2PERIPH_BASE + 0x2100)
#define ADC3_BASE               (APB2PERIPH_BASE + 0x2200)
#define ADC_BASE                (APB2PERIPH_BASE + 0x2300)
#define SDIO_BASE               (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE               (APB2PERIPH_BASE + 0x3000)
#define SPI4_BASE               (APB2PERIPH_BASE + 0x3400)
#define SYSCFG_BASE             (APB2PERIPH_BASE + 0x3800)
#define EINT_BASE               (APB2PERIPH_BASE + 0x3C00)
#define TMR9_BASE               (APB2PERIPH_BASE + 0x4000)
#define TMR10_BASE              (APB2PERIPH_BASE + 0x4400)
#define TMR11_BASE              (APB2PERIPH_BASE + 0x4800)
#define SPI5_BASE               (APB2PERIPH_BASE + 0x5000)
#define SPI6_BASE               (APB2PERIPH_BASE + 0x5400)
#define SAI1_BASE               (APB2PERIPH_BASE + 0x5800)
#define SAI1_Block_A_BASE       (SAI1_BASE + 0x004)
#define SAI1_Block_B_BASE       (SAI1_BASE + 0x024)

/** AHB1 peripherals */
#define GPIOA_BASE              (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE              (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE              (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE              (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE              (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASE              (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASE              (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASE              (AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASE              (AHB1PERIPH_BASE + 0x2000)
#define GPIOJ_BASE              (AHB1PERIPH_BASE + 0x2400)
#define GPIOK_BASE              (AHB1PERIPH_BASE + 0x2800)
#define CRC_BASE                (AHB1PERIPH_BASE + 0x3000)
#define RCM_BASE                (AHB1PERIPH_BASE + 0x3800)
#define FMC_R_BASE              (AHB1PERIPH_BASE + 0x3C00)
#define DMA1_BASE               (AHB1PERIPH_BASE + 0x6000)
#define DMA1_Stream0_BASE       (DMA1_BASE + 0x010)
#define DMA1_Stream1_BASE       (DMA1_BASE + 0x028)
#define DMA1_Stream2_BASE       (DMA1_BASE + 0x040)
#define DMA1_Stream3_BASE       (DMA1_BASE + 0x058)
#define DMA1_Stream4_BASE       (DMA1_BASE + 0x070)
#define DMA1_Stream5_BASE       (DMA1_BASE + 0x088)
#define DMA1_Stream6_BASE       (DMA1_BASE + 0x0A0)
#define DMA1_Stream7_BASE       (DMA1_BASE + 0x0B8)
#define DMA2_BASE                (AHB1PERIPH_BASE + 0x6400)
#define DMA2_Stream0_BASE       (DMA2_BASE + 0x010)
#define DMA2_Stream1_BASE       (DMA2_BASE + 0x028)
#define DMA2_Stream2_BASE       (DMA2_BASE + 0x040)
#define DMA2_Stream3_BASE       (DMA2_BASE + 0x058)
#define DMA2_Stream4_BASE       (DMA2_BASE + 0x070)
#define DMA2_Stream5_BASE       (DMA2_BASE + 0x088)
#define DMA2_Stream6_BASE       (DMA2_BASE + 0x0A0)
#define DMA2_Stream7_BASE       (DMA2_BASE + 0x0B8)
#define ETH_BASE                (AHB1PERIPH_BASE + 0x8000)
#define ETH_MAC_BASE            (ETH_BASE)
#define ETH_MMC_BASE            (ETH_BASE + 0x0100)
#define ETH_PTP_BASE            (ETH_BASE + 0x0700)
#define ETH_DMA_BASE            (ETH_BASE + 0x1000)
#define DMA2D_BASE              (AHB1PERIPH_BASE + 0xB000)

/** AHB2 peripherals */
#define DCI_BASE                (AHB2PERIPH_BASE + 0x50000)
#define CRYP_BASE               (AHB2PERIPH_BASE + 0x60000)
#define HASH_BASE               (AHB2PERIPH_BASE + 0x60400)
#define HASH_DIGEST_BASE        (AHB2PERIPH_BASE + 0x60710)
#define RNG_BASE                (AHB2PERIPH_BASE + 0x60800)

#define SMC_Bank1_R_BASE        (SMC_R_BASE + 0x0000)
#define SMC_Bank1E_R_BASE       (SMC_R_BASE + 0x0104)
#define SMC_Bank2_R_BASE        (SMC_R_BASE + 0x0060)
#define SMC_Bank3_R_BASE        (SMC_R_BASE + 0x0080)
#define SMC_Bank4_R_BASE        (SMC_R_BASE + 0x00A0)

/* Debug MCU registers base address */
#define DBGMCU_BASE             ((uint32_t )0xE0042000)
/** Big number (BN) registers base address */
#define BN_BASE                 ((uint32_t )0x500A0000)
/** SM3 registers base address */
#define SM3_BASE                ((uint32_t )0x50080000)
/** SM4 registers base address */
#define SM4_BASE                ((uint32_t )0x50080400)

/**
  * @}
  */

/** @defgroup Peripheral_declaration
  @{
*/

#define TMR2                    ((TMR_T *) TMR2_BASE)
#define TMR3                    ((TMR_T *) TMR3_BASE)
#define TMR4                    ((TMR_T *) TMR4_BASE)
#define TMR5                    ((TMR_T *) TMR5_BASE)
#define TMR6                    ((TMR_T *) TMR6_BASE)
#define TMR7                    ((TMR_T *) TMR7_BASE)
#define TMR12                   ((TMR_T *) TMR12_BASE)
#define TMR13                   ((TMR_T *) TMR13_BASE)
#define TMR14                   ((TMR_T *) TMR14_BASE)
#define RTC                     ((RTC_T *) RTC_BASE)
#define WWDT                    ((WWDT_T *) WWDT_BASE)
#define IWDT                    ((IWDT_T *) IWDT_BASE)
#define I2S2ext                 ((SPI_T *) I2S2ext_BASE)
#define SPI2                    ((SPI_T *) SPI2_BASE)
#define SPI3                    ((SPI_T *) SPI3_BASE)
#define I2S3ext                 ((SPI_T *) I2S3ext_BASE)
#define USART2                  ((USART_T *) USART2_BASE)
#define USART3                  ((USART_T *) USART3_BASE)
#define UART4                   ((USART_T *) UART4_BASE)
#define UART5                   ((USART_T *) UART5_BASE)
#define I2C1                    ((I2C_T *) I2C1_BASE)
#define I2C2                    ((I2C_T *) I2C2_BASE)
#define I2C3                    ((I2C_T *) I2C3_BASE)
#define CAN1                    ((CAN_T *) CAN1_BASE)
#define CAN2                    ((CAN_T *) CAN2_BASE)
#define PMU                     ((PMU_T *) PMU_BASE)
#define DAC                     ((DAC_T *) DAC_BASE)
#define UART7                   ((USART_T *) UART7_BASE)
#define UART8                   ((USART_T *) UART8_BASE)
#define UART9                   ((USART_T *) UART9_BASE)
#define UART10                  ((USART_T *) UART10_BASE)
#define TMR1                    ((TMR_T *) TMR1_BASE)
#define TMR8                    ((TMR_T *) TMR8_BASE)
#define USART1                  ((USART_T *) USART1_BASE)
#define USART6                  ((USART_T *) USART6_BASE)
#define ADC                     ((ADC_Common_T *) ADC_BASE)
#define ADC1                    ((ADC_T *) ADC1_BASE)
#define ADC2                    ((ADC_T *) ADC2_BASE)
#define ADC3                    ((ADC_T *) ADC3_BASE)
#define SDIO                    ((SDIO_T *) SDIO_BASE)
#define SPI1                    ((SPI_T *) SPI1_BASE)
#define SPI4                    ((SPI_T *) SPI4_BASE)
#define SYSCFG                  ((SYSCFG_T *) SYSCFG_BASE)
#define EINT                    ((EINT_T *) EINT_BASE)
#define TMR9                    ((TMR_T *) TMR9_BASE)
#define TMR10                   ((TMR_T *) TMR10_BASE)
#define TMR11                   ((TMR_T *) TMR11_BASE)
#define SPI5                    ((SPI_T *) SPI5_BASE)
#define SPI6                    ((SPI_T *) SPI6_BASE)
#define SAI1                    ((SAI_T *) SAI1_BASE)
#define SAI1_Block_A            ((SAI_Block_T *)SAI1_Block_A_BASE)
#define SAI1_Block_B            ((SAI_Block_T *)SAI1_Block_B_BASE)
#define GPIOA                   ((GPIO_T *) GPIOA_BASE)
#define GPIOB                   ((GPIO_T *) GPIOB_BASE)
#define GPIOC                   ((GPIO_T *) GPIOC_BASE)
#define GPIOD                   ((GPIO_T *) GPIOD_BASE)
#define GPIOE                   ((GPIO_T *) GPIOE_BASE)
#define GPIOF                   ((GPIO_T *) GPIOF_BASE)
#define GPIOG                   ((GPIO_T *) GPIOG_BASE)
#define GPIOH                   ((GPIO_T *) GPIOH_BASE)
#define GPIOI                   ((GPIO_T *) GPIOI_BASE)
#define GPIOJ                   ((GPIO_T *) GPIOJ_BASE)
#define GPIOK                   ((GPIO_T *) GPIOK_BASE)
#define CRC                     ((CRC_T *) CRC_BASE)
#define RCM                     ((RCM_T *) RCM_BASE)
#define FMC                     ((FMC_T *) FMC_R_BASE)
#define DMA1                    ((DMA_T *) DMA1_BASE)
#define DMA1_Stream0            ((DMA_Stream_T *) DMA1_Stream0_BASE)
#define DMA1_Stream1            ((DMA_Stream_T *) DMA1_Stream1_BASE)
#define DMA1_Stream2            ((DMA_Stream_T *) DMA1_Stream2_BASE)
#define DMA1_Stream3            ((DMA_Stream_T *) DMA1_Stream3_BASE)
#define DMA1_Stream4            ((DMA_Stream_T *) DMA1_Stream4_BASE)
#define DMA1_Stream5            ((DMA_Stream_T *) DMA1_Stream5_BASE)
#define DMA1_Stream6            ((DMA_Stream_T *) DMA1_Stream6_BASE)
#define DMA1_Stream7            ((DMA_Stream_T *) DMA1_Stream7_BASE)
#define DMA2                    ((DMA_T *) DMA2_BASE)
#define DMA2_Stream0            ((DMA_Stream_T *) DMA2_Stream0_BASE)
#define DMA2_Stream1            ((DMA_Stream_T *) DMA2_Stream1_BASE)
#define DMA2_Stream2            ((DMA_Stream_T *) DMA2_Stream2_BASE)
#define DMA2_Stream3            ((DMA_Stream_T *) DMA2_Stream3_BASE)
#define DMA2_Stream4            ((DMA_Stream_T *) DMA2_Stream4_BASE)
#define DMA2_Stream5            ((DMA_Stream_T *) DMA2_Stream5_BASE)
#define DMA2_Stream6            ((DMA_Stream_T *) DMA2_Stream6_BASE)
#define DMA2_Stream7            ((DMA_Stream_T *) DMA2_Stream7_BASE)
#define ETH                     ((ETH_T *) ETH_BASE)
#define DMA2D                   ((DMA2D_T *)DMA2D_BASE)
#define DCI                     ((DCI_T *) DCI_BASE)
#define CRYP                    ((CRYP_T *) CRYP_BASE)
#define HASH                    ((HASH_T *) HASH_BASE)
#define RNG                     ((RNG_T *) RNG_BASE)

#define SMC_Bank1               ((SMC_Bank1_T *) SMC_Bank1_R_BASE)
#define SMC_Bank1E              ((SMC_Bank1E_T *) SMC_Bank1E_R_BASE)
#define SMC_Bank2               ((SMC_Bank2_T *) SMC_Bank2_R_BASE)
#define SMC_Bank3               ((SMC_Bank3_T *) SMC_Bank3_R_BASE)
#define SMC_Bank4               ((SMC_Bank4_T *) SMC_Bank4_R_BASE)

#define DBGMCU                  ((DBGMCU_T *) DBGMCU_BASE)
#define BN                      ((BN_T *) BN_BASE)
#define SM3                     ((SM3_T *) SM3_BASE)
#define SM4                     ((SM4_T *) SM4_BASE)
#define DMC                     ((DMC_T *) DMC_BASE)

/**
  * @}
  */

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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_H */

/**@} end of group APM32F4xx */
/**@} end of group CMSIS */
