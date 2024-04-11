/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL module.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_RCC_H
#define STM32H7RSxx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"
#include "stm32h7rsxx_ll_rcc.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
  uint32_t PLLState;   /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Config                      */

  uint32_t PLLSource;  /*!< PLL entry clock source.
                            This parameter must be a value of @ref RCC_PLL_Clock_Source               */

  uint32_t PLLM;       /*!< Division factor for PLL VCO input clock.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 63    */

  uint32_t PLLN;       /*!< Multiplication factor for PLL VCO output clock.
                            This parameter must be a number between Min_Data = 8 and Max_Data = 420   */

  uint32_t PLLP;       /*!< Division factor for system clock.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128
                            Odd division factors (except for 1) are not allowed                                      */

  uint32_t PLLQ;       /*!< Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128   */

  uint32_t PLLR;       /*!< Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128   */

  uint32_t PLLS;       /*!< Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 8     */

  uint32_t PLLT;       /*!< Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 8     */

  uint32_t PLLFractional;   /*!< Fractional Part of the Multiplication Factor for PLL VCO.
                            This parameter must be a number  between 0 and 8191                       */

} RCC_PLLInitTypeDef;

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, CSI, LSE and LSI) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t HSIDiv;               /*!< The division factor of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Divider                       */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value.
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  uint32_t HSI48State;           /*!< The new state of the HSI48.
                                      This parameter can be a value of @ref RCC_HSI48_Config                      */

  uint32_t CSIState;             /*!< The new state of the CSI.
                                      This parameter can be a value of @ref RCC_CSI_Config                        */

  RCC_PLLInitTypeDef PLL1;       /*!< Main PLL1 structure parameters                                              */

  RCC_PLLInitTypeDef PLL2;       /*!< PLL2 structure parameters                                                   */

  RCC_PLLInitTypeDef PLL3;       /*!< PLL3 structure parameters                                                   */

} RCC_OscInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a value of @ref RCC_System_Clock_Type                        */

  uint32_t SYSCLKSource;          /*!< The clock source used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_System_Clock_Source                      */

  uint32_t SYSCLKDivider;         /*!< The system clock divider for CPU clock and all bus matrix clocks.
                                       This parameter can be a value of @ref RCC_System_Clock_Divider                     */

  uint32_t AHBCLKDivider;         /*!< The AHB/AXI clock divider for HCLK.
                                       This clock is derived from the system clock divided by the system clock divider.
                                       This parameter can be a value of @ref RCC_HCLK_Clock_Source                        */

  uint32_t APB1CLKDivider;        /*!< The APB1 clock divider for PCLK1.
                                       This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB1_Clock_Source                        */

  uint32_t APB2CLKDivider;        /*!< The APB2 clock divider for PCLK2.
                                       This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB2_Clock_Source                        */

  uint32_t APB4CLKDivider;        /*!< The APB4 clock divider for PCLK4.
                                       This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB4_Clock_Source                        */

  uint32_t APB5CLKDivider;        /*!< The APB5 clock divider for PCLK5.
                                       This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB5_Clock_Source                        */

} RCC_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Oscillator_Type  Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE        0x00000000U  /*!< Oscillator configuration unchanged */
#define RCC_OSCILLATORTYPE_HSE         0x00000001U  /*!< HSE selected */
#define RCC_OSCILLATORTYPE_HSI         0x00000002U  /*!< HSI selected */
#define RCC_OSCILLATORTYPE_LSE         0x00000004U  /*!< LSE selected */
#define RCC_OSCILLATORTYPE_LSI         0x00000008U  /*!< LSI selected */
#define RCC_OSCILLATORTYPE_CSI         0x00000010U  /*!< CSI selected */
#define RCC_OSCILLATORTYPE_HSI48       0x00000020U  /*!< HSI48 selected */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config  HSE Config
  * @{
  */
#define RCC_HSE_OFF                    0U                                                 /*!< HSE clock deactivation */
#define RCC_HSE_ON                     RCC_CR_HSEON                                       /*!< HSE clock activation */
#define RCC_HSE_BYPASS                 (RCC_CR_HSEBYP | RCC_CR_HSEON)                     /*!< HSE bypass analog clock activation */
#define RCC_HSE_BYPASS_DIGITAL         (RCC_CR_HSEEXT | RCC_CR_HSEBYP | RCC_CR_HSEON)     /*!< HSE bypass digital clock activation */
/**
  * @}
  */

/** @defgroup RCC_LSE_Config  LSE Config
  * @{
  */
#define RCC_LSE_OFF                    0U                                                   /*!< LSE clock deactivation */
#define RCC_LSE_ON                     RCC_BDCR_LSEON                                       /*!< LSE clock activation */
#define RCC_LSE_BYPASS                 (RCC_BDCR_LSEBYP | RCC_BDCR_LSEON)                   /*!< LSE bypass analog clock activation */
#define RCC_LSE_BYPASS_DIGITAL         (RCC_BDCR_LSEEXT | RCC_BDCR_LSEBYP | RCC_BDCR_LSEON) /*!< LSE bypass digital clock activation */
/**
  * @}
  */

/** @defgroup RCC_HSI_Config  HSI Config
  * @{
  */
#define RCC_HSI_OFF                    0U                                    /*!< HSI clock deactivation */
#define RCC_HSI_ON                     RCC_CR_HSION                          /*!< HSI clock activation with divider 1 = 64MHz */
/**
  * @}
  */

/** @defgroup RCC_HSI_Calibration_Default  HSI Calibration default
  * @{
  */
#define RCC_HSICALIBRATION_DEFAULT     0x40U               /*!< Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_HSI_Divider  HSI Divider
  * @{
  */
#define RCC_HSI_DIV1                   0U                  /*!< HSI clock activation with divider 1 = 64MHz */
#define RCC_HSI_DIV2                   RCC_CR_HSIDIV_0     /*!< HSI clock activation with divider 2 = 32MHz */
#define RCC_HSI_DIV4                   RCC_CR_HSIDIV_1     /*!< HSI clock activation with divider 4 = 16MHz */
#define RCC_HSI_DIV8                   RCC_CR_HSIDIV       /*!< HSI clock activation with divider 8 = 8MHz */
/**
  * @}
  */

/** @defgroup RCC_HSI48_Config  HSI48 Config
  * @{
  */
#define RCC_HSI48_OFF                  0U                  /*!< HSI48 clock deactivation */
#define RCC_HSI48_ON                   RCC_CR_HSI48ON      /*!< HSI48 clock activation */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config  LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0U                  /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CSR_LSION       /*!< LSI clock activation */
/**
  * @}
  */

/** @defgroup RCC_CSI_Config  CSI Config
  * @{
  */
#define RCC_CSI_OFF                    0U                  /*!< CSI clock deactivation */
#define RCC_CSI_ON                     RCC_CR_CSION        /*!< CSI clock activation */
/**
  * @}
  */

/** @defgroup RCC_CSI_Calibration_Default  CSI Calibration default
  * @{
  */
#define RCC_CSICALIBRATION_DEFAULT     0x20U               /*!< Default CSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_PLL_Config  PLL Config
  * @{
  */
#define RCC_PLL_NONE                   0U                  /*!< PLL configuration unchanged */
#define RCC_PLL_OFF                    1U                  /*!< PLL deactivation */
#define RCC_PLL_ON                     2U                  /*!< PLL activation */
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source  PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI              0U                     /*!< HSI clock selected as PLL entry clock source */
#define RCC_PLLSOURCE_CSI              RCC_PLLCKSELR_PLLSRC_0 /*!< CSI clock selected as PLL entry clock source */
#define RCC_PLLSOURCE_HSE              RCC_PLLCKSELR_PLLSRC_1 /*!< HSE clock selected as PLL entry clock source */
#define RCC_PLLSOURCE_NONE             RCC_PLLCKSELR_PLLSRC   /*!< No clock selected as PLL entry clock source  */
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Output  PLL Clock Output
  * @{
  */
#define RCC_PLL_PCLK                  RCC_PLLCFGR_PLL1PEN   /*!< PLL DIVP divider output enable */
#define RCC_PLL_QCLK                  RCC_PLLCFGR_PLL1QEN   /*!< PLL DIVQ divider output enable */
#define RCC_PLL_RCLK                  RCC_PLLCFGR_PLL1REN   /*!< PLL DIVR divider output enable */
#define RCC_PLL_SCLK                  RCC_PLLCFGR_PLL1SEN   /*!< PLL DIVS divider output enable */
#define RCC_PLL_TCLK                  0x00000200U           /*!< PLL DIVT divider output enable, hardcoded because no definition in CMSIS */
/**
  * @}
  */

/** @defgroup RCC_PLL_VCI_Range  PLL VCI Range
  * @{
  */
#define RCC_PLL_VCOINPUT_RANGE0             0U                    /*!< Clock range frequency for PLL between 1 and 2 MHz (reset) */
#define RCC_PLL_VCOINPUT_RANGE1             RCC_PLLCFGR_PLL1RGE_0 /*!< Clock range frequency for PLL between 2 and 4 MHz  */
#define RCC_PLL_VCOINPUT_RANGE2             RCC_PLLCFGR_PLL1RGE_1 /*!< Clock range frequency for PLL between 4 and 8 MHz  */
#define RCC_PLL_VCOINPUT_RANGE3             RCC_PLLCFGR_PLL1RGE   /*!< Clock range frequency for PLL between 8 and 16 MHz */
/**
  * @}
  */

/** @defgroup RCC_PLL_VCO_Range  PLL VCO Range
  * @{
  */
#define RCC_PLL_VCO_HIGH                    0U                       /*!< Wide PLL VCO output range between 400 and 1600 MHz (reset) */
#define RCC_PLL_VCO_LOW                     RCC_PLLCFGR_PLL1VCOSEL   /*!< Low PLL VCO output range between 150 and 420 MHz        */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Type  System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK           0x00000001U         /*!< SYSCLK to configure */
#define RCC_CLOCKTYPE_HCLK             0x00000002U         /*!< HCLK to configure */
#define RCC_CLOCKTYPE_PCLK1            0x00000004U         /*!< PCLK1 to configure */
#define RCC_CLOCKTYPE_PCLK2            0x00000008U         /*!< PCLK2 to configure */
#define RCC_CLOCKTYPE_PCLK4            0x00000010U         /*!< PCLK4 to configure */
#define RCC_CLOCKTYPE_PCLK5            0x00000020U         /*!< PCLK5 to configure */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source  System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI           0U                  /*!< HSI selection as system clock */
#define RCC_SYSCLKSOURCE_CSI           RCC_CFGR_SW_0       /*!< CSI selection as system clock */
#define RCC_SYSCLKSOURCE_HSE           RCC_CFGR_SW_1       /*!< HSE selection as system clock */
#define RCC_SYSCLKSOURCE_PLLCLK        (RCC_CFGR_SW_1 | RCC_CFGR_SW_0) /*!< PLL1 selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_HSI    0U                  /*!< HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_CSI    RCC_CFGR_SWS_0      /*!< CSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE    RCC_CFGR_SWS_1      /*!< HSE used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0) /*!< PLL1 used as system clock */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Divider  System Clock Divider
  * @{
  */
#define RCC_SYSCLK_DIV1      0U                                                          /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2      RCC_CDCFGR_CPRE_3                                           /*!< SYSCLK divided by 2 */
#define RCC_SYSCLK_DIV4      (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_0)                     /*!< SYSCLK divided by 4 */
#define RCC_SYSCLK_DIV8      (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_1)                     /*!< SYSCLK divided by 8 */
#define RCC_SYSCLK_DIV16     (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_1 | RCC_CDCFGR_CPRE_0) /*!< SYSCLK divided by 16 */
#define RCC_SYSCLK_DIV64     (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2)                     /*!< SYSCLK divided by 64 */
#define RCC_SYSCLK_DIV128    (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2 | RCC_CDCFGR_CPRE_0) /*!< SYSCLK divided by 128 */
#define RCC_SYSCLK_DIV256    (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2 | RCC_CDCFGR_CPRE_1) /*!< SYSCLK divided by 256 */
#define RCC_SYSCLK_DIV512    (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2 | RCC_CDCFGR_CPRE_1 | RCC_CDCFGR_CPRE_0) /*!< SYSCLK divided by 512 */
/**
  * @}
  */


/** @defgroup RCC_HCLK_Clock_Source  HCLK Clock Source
  * @{
  */
#define RCC_HCLK_DIV1        0U                                                             /*!< HCLK not divided */
#define RCC_HCLK_DIV2        RCC_BMCFGR_BMPRE_3                                             /*!< HCLK divided by 2 */
#define RCC_HCLK_DIV4        (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_0)                      /*!< HCLK divided by 4 */
#define RCC_HCLK_DIV8        (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_1)                      /*!< HCLK divided by 8 */
#define RCC_HCLK_DIV16       (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_1 | RCC_BMCFGR_BMPRE_0) /*!< HCLK divided by 16 */
#define RCC_HCLK_DIV64       (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_2)                      /*!< HCLK divided by 64 */
#define RCC_HCLK_DIV128      (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_2 | RCC_BMCFGR_BMPRE_0) /*!< HCLK divided by 128 */
#define RCC_HCLK_DIV256      (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_2 | RCC_BMCFGR_BMPRE_1) /*!< HCLK divided by 256 */
#define RCC_HCLK_DIV512      (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_2 | RCC_BMCFGR_BMPRE_1 | RCC_BMCFGR_BMPRE_0) /*!< HCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Source  APB1 Clock Source
  * @{
  */
#define RCC_APB1_DIV1        0U                                                    /*!< APB1 not divided */
#define RCC_APB1_DIV2        RCC_APBCFGR_PPRE1_2                                   /*!< APB1 divided by 2 */
#define RCC_APB1_DIV4        (RCC_APBCFGR_PPRE1_2 | RCC_APBCFGR_PPRE1_0)           /*!< APB1 divided by 4 */
#define RCC_APB1_DIV8        (RCC_APBCFGR_PPRE1_2 | RCC_APBCFGR_PPRE1_1)           /*!< APB1 divided by 8 */
#define RCC_APB1_DIV16       RCC_APBCFGR_PPRE1                                     /*!< APB1 divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Source  APB2 Clock Source
  * @{
  */
#define RCC_APB2_DIV1        0U                                                    /*!< APB2 not divided */
#define RCC_APB2_DIV2        RCC_APBCFGR_PPRE2_2                                   /*!< APB2 divided by 2 */
#define RCC_APB2_DIV4        (RCC_APBCFGR_PPRE2_2 | RCC_APBCFGR_PPRE2_0)           /*!< APB2 divided by 4 */
#define RCC_APB2_DIV8        (RCC_APBCFGR_PPRE2_2 | RCC_APBCFGR_PPRE2_1)           /*!< APB2 divided by 8 */
#define RCC_APB2_DIV16       RCC_APBCFGR_PPRE2                                     /*!< APB2 divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_APB4_Clock_Source  APB4 Clock Source
  * @{
  */
#define RCC_APB4_DIV1        0U                                                    /*!< APB4 not divided */
#define RCC_APB4_DIV2        RCC_APBCFGR_PPRE4_2                                   /*!< APB4 divided by 2 */
#define RCC_APB4_DIV4        (RCC_APBCFGR_PPRE4_2 | RCC_APBCFGR_PPRE4_0)           /*!< APB4 divided by 4 */
#define RCC_APB4_DIV8        (RCC_APBCFGR_PPRE4_2 | RCC_APBCFGR_PPRE4_1)           /*!< APB4 divided by 8 */
#define RCC_APB4_DIV16       RCC_APBCFGR_PPRE4                                     /*!< APB4 divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_APB5_Clock_Source  APB5 Clock Source
  * @{
  */
#define RCC_APB5_DIV1        0U                                                    /*!< APB5 not divided */
#define RCC_APB5_DIV2        RCC_APBCFGR_PPRE5_2                                   /*!< APB5 divided by 2 */
#define RCC_APB5_DIV4        (RCC_APBCFGR_PPRE5_2 | RCC_APBCFGR_PPRE5_0)           /*!< APB5 divided by 4 */
#define RCC_APB5_DIV8        (RCC_APBCFGR_PPRE5_2 | RCC_APBCFGR_PPRE5_1)           /*!< APB5 divided by 8 */
#define RCC_APB5_DIV16       RCC_APBCFGR_PPRE5                                     /*!< APB5 divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source  RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_DISABLE       0U                                  /*!< RTC clock is disabled */
#define RCC_RTCCLKSOURCE_LSE           RCC_BDCR_RTCSEL_0                   /*!< LSE oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_LSI           RCC_BDCR_RTCSEL_1                   /*!< LSI oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV2      ((0x02U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 2 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV3      ((0x03U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 3 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV4      ((0x04U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 4 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV5      ((0x05U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 5 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV6      ((0x06U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 6 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV7      ((0x07U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 7 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV8      ((0x08U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 8 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV9      ((0x09U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 9 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV10     ((0x0AU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 10 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV11     ((0x0BU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 11 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV12     ((0x0CU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 12 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV13     ((0x0DU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 13 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV14     ((0x0EU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 14 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV15     ((0x0FU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 15 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV16     ((0x10U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 16 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV17     ((0x11U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 17 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV18     ((0x12U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 18 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV19     ((0x13U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 19 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV20     ((0x14U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 20 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV21     ((0x15U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 21 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV22     ((0x16U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 22 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV23     ((0x17U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 23 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV24     ((0x18U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 24 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV25     ((0x19U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 25 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV26     ((0x1AU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 26 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV27     ((0x1BU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 27 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV28     ((0x1CU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 28 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV29     ((0x1DU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 29 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV30     ((0x1EU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 30 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV31     ((0x1FU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 31 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV32     ((0x20U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 32 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV33     ((0x21U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 33 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV34     ((0x22U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 34 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV35     ((0x23U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 35 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV36     ((0x24U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 36 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV37     ((0x25U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 37 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV38     ((0x26U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 38 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV39     ((0x27U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 39 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV40     ((0x28U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 40 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV41     ((0x29U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 41 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV42     ((0x2AU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 42 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV43     ((0x2BU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 43 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV44     ((0x2CU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 44 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV45     ((0x2DU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 45 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV46     ((0x2EU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 46 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV47     ((0x2FU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 47 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV48     ((0x30U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 48 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV49     ((0x31U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 49 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV50     ((0x32U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 50 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV51     ((0x33U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 51 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV52     ((0x34U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 52 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV53     ((0x35U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 53 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV54     ((0x36U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 54 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV55     ((0x37U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 55 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV56     ((0x38U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 56 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV57     ((0x39U << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 57 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV58     ((0x3AU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 58 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV59     ((0x3BU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 59 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV60     ((0x3CU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 60 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV61     ((0x3DU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 61 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV62     ((0x3EU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 62 used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV63     ((0x3FU << 12U) | RCC_BDCR_RTCSEL)  /*!< HSE oscillator clock divided by 63 used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_MCOx_Index  MCOx Index
  * @{
  */

/* @cond */
/* 32     28      20       16      0
   --------------------------------
   | MCO   | GPIO  | GPIO  | GPIO  |
   | Index |  AF   | Port  |  Pin  |
   -------------------------------*/

#define RCC_MCO_GPIOPORT_POS   16U
#define RCC_MCO_GPIOPORT_MASK  (0xFUL << RCC_MCO_GPIOPORT_POS)
#define RCC_MCO_GPIOAF_POS     20U
#define RCC_MCO_GPIOAF_MASK    (0xFFUL << RCC_MCO_GPIOAF_POS)
#define RCC_MCO_INDEX_POS      28U
#define RCC_MCO_INDEX_MASK     (0x1UL << RCC_MCO_INDEX_POS)

#define RCC_MCO1_INDEX         (0x0UL << RCC_MCO_INDEX_POS)             /*!< MCO1 index */
#define RCC_MCO2_INDEX         (0x1UL << RCC_MCO_INDEX_POS)             /*!< MCO2 index */
/* @endcond */

#define RCC_MCO1_PA8           (RCC_MCO1_INDEX |\
                                (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | (GPIO_GET_INDEX(GPIOA) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_8)
#define RCC_MCO1               RCC_MCO1_PA8         /*!< Alias for compatibility */

#define RCC_MCO2_PC9           (RCC_MCO2_INDEX |\
                                (GPIO_AF0_MCO << RCC_MCO_GPIOAF_POS) | (GPIO_GET_INDEX(GPIOC) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_9)
#define RCC_MCO2               RCC_MCO2_PC9         /*!< Alias for compatibility */

#define RCC_MCO                RCC_MCO1             /*!< MCO1 to be compliant with other families with 1 MCO*/
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Source  MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_HSI             0U                                        /*!< HSI clock selected as MCO1 source (reset) */
#define RCC_MCO1SOURCE_LSE             RCC_CFGR_MCO1SEL_0                        /*!< LSE clock selected as MCO1 source */
#define RCC_MCO1SOURCE_HSE             RCC_CFGR_MCO1SEL_1                        /*!< HSE clock selected as MCO1 source */
#define RCC_MCO1SOURCE_PLL1Q           (RCC_CFGR_MCO1SEL_1 | RCC_CFGR_MCO1SEL_0) /*!< PLL1Q clock selected as MCO1 source */
#define RCC_MCO1SOURCE_HSI48           RCC_CFGR_MCO1SEL_2                        /*!< HSI48 clock selected as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Source  MCO2 Clock Source
  * @{
  */
#define RCC_MCO2SOURCE_SYSCLK          0U                                        /*!< System clock selected as MCO2 source (reset) */
#define RCC_MCO2SOURCE_PLL2P           RCC_CFGR_MCO2SEL_0                        /*!< PLL2P clock selected as MCO2 source */
#define RCC_MCO2SOURCE_HSE             RCC_CFGR_MCO2SEL_1                        /*!< HSE clock selected as MCO2 source */
#define RCC_MCO2SOURCE_PLL1P           (RCC_CFGR_MCO2SEL_1 | RCC_CFGR_MCO2SEL_0) /*!< PLL1P clock selected as MCO2 source */
#define RCC_MCO2SOURCE_CSI             RCC_CFGR_MCO2SEL_2                        /*!< CSI clock selected as MCO2 source */
#define RCC_MCO2SOURCE_LSI             (RCC_CFGR_MCO2SEL_2 | RCC_CFGR_MCO2SEL_0) /*!< LSI clock selected as MCO2 source */
/**
  * @}
  */

/** @defgroup RCC_MCOx_Clock_Prescaler  MCOx Clock Prescaler
  * @{
  */
#define RCC_MCODIV_NONE                0U                                                             /*!< No MCO prescaler (reset) */
#define RCC_MCODIV_1                   RCC_CFGR_MCO1PRE_0                                             /*!< MCO divided by 1 */
#define RCC_MCODIV_2                   RCC_CFGR_MCO1PRE_1                                             /*!< MCO divided by 2 */
#define RCC_MCODIV_3                   (RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0)                      /*!< MCO divided by 3 */
#define RCC_MCODIV_4                   RCC_CFGR_MCO1PRE_2                                             /*!< MCO divided by 4 */
#define RCC_MCODIV_5                   (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_0)                      /*!< MCO divided by 5 */
#define RCC_MCODIV_6                   (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1)                      /*!< MCO divided by 6 */
#define RCC_MCODIV_7                   (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0) /*!< MCO divided by 7 */
#define RCC_MCODIV_8                   RCC_CFGR_MCO1PRE_3                                             /*!< MCO divided by 8 */
#define RCC_MCODIV_9                   (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_0)                      /*!< MCO divided by 9 */
#define RCC_MCODIV_10                  (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_1)                      /*!< MCO divided by 10 */
#define RCC_MCODIV_11                  (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0) /*!< MCO divided by 11 */
#define RCC_MCODIV_12                  (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_2)                      /*!< MCO divided by 12 */
#define RCC_MCODIV_13                  (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_0) /*!< MCO divided by 13 */
#define RCC_MCODIV_14                  (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1) /*!< MCO divided by 14 */
#define RCC_MCODIV_15                  RCC_CFGR_MCO1PRE                                               /*!< MCO divided by 15 */
/**
  * @}
  */

/** @defgroup RCC_Interrupt  Interrupt
  * @{
  */
#define RCC_IT_LSIRDY                  RCC_CIFR_LSIRDYF    /*!< LSI Ready Interrupt */
#define RCC_IT_LSERDY                  RCC_CIFR_LSERDYF    /*!< LSE Ready Interrupt */
#define RCC_IT_HSIRDY                  RCC_CIFR_HSIRDYF    /*!< HSI Ready Interrupt */
#define RCC_IT_HSERDY                  RCC_CIFR_HSERDYF    /*!< HSE Ready Interrupt */
#define RCC_IT_CSIRDY                  RCC_CIFR_CSIRDYF    /*!< CSI Ready Interrupt */
#define RCC_IT_HSI48RDY                RCC_CIFR_HSI48RDYF  /*!< HSI48 Ready Interrupt */
#define RCC_IT_PLL1RDY                 RCC_CIFR_PLL1RDYF   /*!< PLL1 Ready Interrupt */
#define RCC_IT_PLL2RDY                 RCC_CIFR_PLL2RDYF   /*!< PLL2 Ready Interrupt */
#define RCC_IT_PLL3RDY                 RCC_CIFR_PLL3RDYF   /*!< PLL3 Ready Interrupt */
#define RCC_IT_LSECSS                  RCC_CIFR_LSECSSF    /*!< LSE Clock Security System Interrupt */
#define RCC_IT_HSECSS                  RCC_CIFR_HSECSSF    /*!< HSE Clock Security System Interrupt (flag only) */
/**
  * @}
  */

/** @defgroup RCC_Flag  Flag
  *        Elements values convention: XXXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XXX  : Register index
  *                 - 001: CR register
  *                 - 010: BDCR register
  *                 - 011: CSR register
  *                 - 100: RSR register
  * @{
  */
#define RCC_FLAG_HSIRDY                ((RCC_CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos)     /*!< HSI Ready flag */
#define RCC_FLAG_HSIDIV                ((RCC_CR_REG_INDEX << 5U) | RCC_CR_HSIDIVF_Pos)    /*!< HSIDIV Ready flag */
#define RCC_FLAG_CSIRDY                ((RCC_CR_REG_INDEX << 5U) | RCC_CR_CSIRDY_Pos)     /*!< CSI Ready flag */
#define RCC_FLAG_HSI48RDY              ((RCC_CR_REG_INDEX << 5U) | RCC_CR_HSI48RDY_Pos)   /*!< HSI48 Ready flag */
#define RCC_FLAG_HSERDY                ((RCC_CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos)     /*!< HSE Ready flag */
#define RCC_FLAG_PLL1RDY               ((RCC_CR_REG_INDEX << 5U) | RCC_CR_PLL1RDY_Pos)    /*!< PLL1 Ready flag */
#define RCC_FLAG_PLL2RDY               ((RCC_CR_REG_INDEX << 5U) | RCC_CR_PLL2RDY_Pos)    /*!< PLL2 Ready flag */
#define RCC_FLAG_PLL3RDY               ((RCC_CR_REG_INDEX << 5U) | RCC_CR_PLL3RDY_Pos)    /*!< PLL3 Ready flag */

/* Flags in the BDCR register */
#define RCC_FLAG_LSERDY                ((RCC_BDCR_REG_INDEX << 5U) | RCC_BDCR_LSERDY_Pos)  /*!< LSE Ready flag */
#define RCC_FLAG_LSECSSD               ((RCC_BDCR_REG_INDEX << 5U) | RCC_BDCR_LSECSSD_Pos) /*!< LSE Clock Security System failure detection flag */

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY                ((RCC_CSR_REG_INDEX << 5U) | RCC_CSR_LSIRDY_Pos)   /*!< LSI Ready flag */

/* Flags in the RSR register */
#define RCC_FLAG_BORRST                ((RCC_RSR_REG_INDEX << 5U) | RCC_RSR_BORRSTF_Pos)  /*!< BOR reset flag */
#define RCC_FLAG_PINRST                ((RCC_RSR_REG_INDEX << 5U) | RCC_RSR_PINRSTF_Pos)  /*!< PIN reset flag */
#define RCC_FLAG_PORRST                ((RCC_RSR_REG_INDEX << 5U) | RCC_RSR_PORRSTF_Pos)  /*!< Power-on reset flag */
#define RCC_FLAG_SFTRST                ((RCC_RSR_REG_INDEX << 5U) | RCC_RSR_SFTRSTF_Pos)  /*!< Software Reset flag */
#define RCC_FLAG_IWDGRST               ((RCC_RSR_REG_INDEX << 5U) | RCC_RSR_IWDGRSTF_Pos) /*!< Independent Watchdog reset flag */
#define RCC_FLAG_WWDGRST               ((RCC_RSR_REG_INDEX << 5U) | RCC_RSR_WWDGRSTF_Pos) /*!< Window watchdog reset flag */
#define RCC_FLAG_LPWRRST               ((RCC_RSR_REG_INDEX << 5U) | RCC_RSR_LPWRRSTF_Pos) /*!< Low-Power reset flag */
/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Config
  * @{
  */
#define RCC_LSEDRIVE_LOW               0U                  /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW         RCC_BDCR_LSEDRV_0   /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH        RCC_BDCR_LSEDRV_1   /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH              RCC_BDCR_LSEDRV     /*!< LSE high drive capability */
/**
  * @}
  */

/** @defgroup RCC_Reset_Flag Reset Flag
  * @{
  */
#define RCC_RESET_FLAG_OBL              RCC_RSR_OBLRSTF    /*!< Option Byte Loader reset flag */
#define RCC_RESET_FLAG_PIN              RCC_RSR_PINRSTF    /*!< PIN reset flag */
#define RCC_RESET_FLAG_PWR              RCC_RSR_BORRSTF    /*!< BOR or POR/PDR reset flag */
#define RCC_RESET_FLAG_SW               RCC_RSR_SFTRSTF    /*!< Software Reset flag */
#define RCC_RESET_FLAG_IWDG             RCC_RSR_IWDGRSTF   /*!< Independent Watchdog reset flag */
#define RCC_RESET_FLAG_WWDG             RCC_RSR_WWDGRSTF   /*!< Window watchdog reset flag */
#define RCC_RESET_FLAG_LPWR             RCC_RSR_LPWRRSTF   /*!< Low power reset flag */
#define RCC_RESET_FLAG_ALL              (RCC_RESET_FLAG_OBL | RCC_RESET_FLAG_PIN | RCC_RESET_FLAG_PWR | \
                                         RCC_RESET_FLAG_SW | RCC_RESET_FLAG_IWDG | RCC_RESET_FLAG_WWDG | \
                                         RCC_RESET_FLAG_LPWR)
/**
  * @}
  */

/** @defgroup RCC_Stop_WakeUpClock  Stop WakeUp Clock
  * @{
  */
#define RCC_STOP_WAKEUPCLOCK_HSI       0U                  /*!< HSI selected as wake up system clock from system Stop (default after reset) */
#define RCC_STOP_WAKEUPCLOCK_CSI       RCC_CFGR_STOPWUCK   /*!< CSI selected as wake up system clock from system Stop */
/**
  * @}
  */

/** @defgroup RCC_Stop_KernelWakeUpClock  Stop Kernel WakeUp Clock
  * @{
  */
#define RCC_STOP_KERWAKEUPCLOCK_HSI    0U                   /*!< HSI selected as wake up kernel clock from system Stop (default after reset) */
#define RCC_STOP_KERWAKEUPCLOCK_CSI    RCC_CFGR_STOPKERWUCK /*!< CSI selected as wake up kernel clock from system Stop */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup RCC_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_AXI_Clock_Gating_Enable_Disable AXI Interconnect, Master and Slave Clock Gating Enable Disable
  * @brief  Enable or disable the clock gating.
  * @note   The dynamic power consumption can be optimized by enabling the functional clock gating.
  *         After reset, the clock gating is enabled (except for JTAG if a JTAG connection has been detected).
  * @{
  */

#define __HAL_RCC_AXI_INTERCONNECT_CLK_GATING_ENABLE()      CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_AXICKG)

#define __HAL_RCC_AXI_MASTER_AHB_CLK_GATING_ENABLE()        CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_AHBCKG)

#define __HAL_RCC_AXI_MASTER_SDMMC1_CLK_GATING_ENABLE()     CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_SDMMCCKG)

#define __HAL_RCC_AXI_MASTER_HPDMA1_CLK_GATING_ENABLE()     CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_HPDMA1CKG)

#define __HAL_RCC_AXI_MASTER_CPU_CLK_GATING_ENABLE()        CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_CPUCKG)

#define __HAL_RCC_AXI_MASTER_GPU2D_0_CLK_GATING_ENABLE()    CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_GPU2DS0CKG)

#define __HAL_RCC_AXI_MASTER_GPU2D_1_CLK_GATING_ENABLE()    CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_GPU2DS1CKG)

#define __HAL_RCC_AXI_MASTER_GPU2D_CACHE_CLK_GATING_ENABLE() CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_GPU2DCKG)

#define __HAL_RCC_AXI_MASTER_DCMIPP_CLK_GATING_ENABLE()     CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_DCMIPPCKG)

#define __HAL_RCC_AXI_MASTER_DMA2D_CLK_GATING_ENABLE()      CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_DMA2DCKG)

#define __HAL_RCC_AXI_MASTER_LTDC_CLK_GATING_ENABLE()       CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_LTDCCKG)

#define __HAL_RCC_AXI_MASTER_GFXMMU_CLK_GATING_ENABLE()     CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_GFXMMUMCKG)

#define __HAL_RCC_AXI_SLAVE_GFXMMU_CLK_GATING_ENABLE()      CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_GFXMMUSCKG)

#define __HAL_RCC_AXI_SLAVE_AHB_CLK_GATING_ENABLE()         CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_AHBSCKG)

#define __HAL_RCC_AXI_SLAVE_FMC_CLK_GATING_ENABLE()         CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_FMCCKG)

#define __HAL_RCC_AXI_SLAVE_XSPI1_CLK_GATING_ENABLE()       CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_XSPI1CKG)

#define __HAL_RCC_AXI_SLAVE_XSPI2_CLK_GATING_ENABLE()       CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_XSPI2CKG)

#define __HAL_RCC_AXI_SLAVE_SRAM0_CLK_GATING_ENABLE()       CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_AXISRAM0CKG)

#define __HAL_RCC_AXI_SLAVE_SRAM1_CLK_GATING_ENABLE()       CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_AXISRAM1CKG)

#define __HAL_RCC_AXI_SLAVE_SRAM2_CLK_GATING_ENABLE()       CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_AXISRAM2CKG)

#define __HAL_RCC_AXI_SLAVE_SRAM3_CLK_GATING_ENABLE()       CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_AXISRAM3CKG)

#define __HAL_RCC_AXI_SLAVE_FLASH_CLK_GATING_ENABLE()       CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_FLIFTCKG)

#define __HAL_RCC_AXI_SLAVE_EXTI_CLK_GATING_ENABLE()        CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_EXTICKG)

#define __HAL_RCC_AXI_SLAVE_JTAG_CLK_GATING_ENABLE()        CLEAR_BIT(RCC->CKGDISR, RCC_CKGDISR_JTAGCKG)


#define __HAL_RCC_AXI_INTERCONNECT_CLK_GATING_DISABLE()     SET_BIT(RCC->CKGDISR, RCC_CKGDISR_AXICKG)

#define __HAL_RCC_AXI_MASTER_AHB_CLK_GATING_DISABLE()       SET_BIT(RCC->CKGDISR, RCC_CKGDISR_AHBCKG)

#define __HAL_RCC_AXI_MASTER_SDMMC1_CLK_GATING_DISABLE()    SET_BIT(RCC->CKGDISR, RCC_CKGDISR_SDMMCCKG)

#define __HAL_RCC_AXI_MASTER_HPDMA1_CLK_GATING_DISABLE()    SET_BIT(RCC->CKGDISR, RCC_CKGDISR_HPDMA1CKG)

#define __HAL_RCC_AXI_MASTER_CPU_CLK_GATING_DISABLE()       SET_BIT(RCC->CKGDISR, RCC_CKGDISR_CPUCKG)

#define __HAL_RCC_AXI_MASTER_GPU_0_CLK_GATING_DISABLE()     SET_BIT(RCC->CKGDISR, RCC_CKGDISR_GPU2DS0CKG)

#define __HAL_RCC_AXI_MASTER_GPU_1_CLK_GATING_DISABLE()     SET_BIT(RCC->CKGDISR, RCC_CKGDISR_GPU2DS1CKG)

#define __HAL_RCC_AXI_MASTER_GPU_CACHE_CLK_GATING_DISABLE() SET_BIT(RCC->CKGDISR, RCC_CKGDISR_GPU2DCKG)

#define __HAL_RCC_AXI_MASTER_DCMIPP_CLK_GATING_DISABLE()    SET_BIT(RCC->CKGDISR, RCC_CKGDISR_DCMIPPCKG)

#define __HAL_RCC_AXI_MASTER_DMA2D_CLK_GATING_DISABLE()     SET_BIT(RCC->CKGDISR, RCC_CKGDISR_DMA2DCKG)

#define __HAL_RCC_AXI_MASTER_LTDC_CLK_GATING_DISABLE()      SET_BIT(RCC->CKGDISR, RCC_CKGDISR_LTDCCKG)

#define __HAL_RCC_AXI_MASTER_GFXMMU_CLK_GATING_DISABLE()    SET_BIT(RCC->CKGDISR, RCC_CKGDISR_GFXMMUMCKG)

#define __HAL_RCC_AXI_SLAVE_GFXMMU_CLK_GATING_DISABLE()     SET_BIT(RCC->CKGDISR, RCC_CKGDISR_GFXMMUSCKG)

#define __HAL_RCC_AXI_SLAVE_AHB_CLK_GATING_DISABLE()        SET_BIT(RCC->CKGDISR, RCC_CKGDISR_AHBSCKG)

#define __HAL_RCC_AXI_SLAVE_FMC_CLK_GATING_DISABLE()        SET_BIT(RCC->CKGDISR, RCC_CKGDISR_FMCCKG)

#define __HAL_RCC_AXI_SLAVE_XSPI1_CLK_GATING_DISABLE()      SET_BIT(RCC->CKGDISR, RCC_CKGDISR_XSPI1CKG)

#define __HAL_RCC_AXI_SLAVE_XSPI2_CLK_GATING_DISABLE()      SET_BIT(RCC->CKGDISR, RCC_CKGDISR_XSPI2CKG)

#define __HAL_RCC_AXI_SLAVE_SRAM0_CLK_GATING_DISABLE()      SET_BIT(RCC->CKGDISR, RCC_CKGDISR_AXISRAM0CKG)

#define __HAL_RCC_AXI_SLAVE_SRAM1_CLK_GATING_DISABLE()      SET_BIT(RCC->CKGDISR, RCC_CKGDISR_AXISRAM1CKG)

#define __HAL_RCC_AXI_SLAVE_SRAM2_CLK_GATING_DISABLE()      SET_BIT(RCC->CKGDISR, RCC_CKGDISR_AXISRAM2CKG)

#define __HAL_RCC_AXI_SLAVE_SRAM3_CLK_GATING_DISABLE()      SET_BIT(RCC->CKGDISR, RCC_CKGDISR_AXISRAM3CKG)

#define __HAL_RCC_AXI_SLAVE_FLASH_CLK_GATING_DISABLE()      SET_BIT(RCC->CKGDISR, RCC_CKGDISR_FLIFTCKG)

#define __HAL_RCC_AXI_SLAVE_EXTI_CLK_GATING_DISABLE()       SET_BIT(RCC->CKGDISR, RCC_CKGDISR_EXTICKG)

#define __HAL_RCC_AXI_SLAVE_JTAG_CLK_GATING_DISABLE()       SET_BIT(RCC->CKGDISR, RCC_CKGDISR_JTAGCKG)

/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable AHB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_GPDMA1_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPDMA1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB1ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_ADC12_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADC12EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB1ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#if defined(ETH)
#define __HAL_RCC_ETH1MAC_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1MACEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB1ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_ETH1TX_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1TXEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB1ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_ETH1RX_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1RXEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB1ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)
#endif /* ETH */

#define __HAL_RCC_USB_OTG_HS_CLK_ENABLE() do { \
                                                __IO uint32_t tmpreg; \
                                                SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN);\
                                                /* Delay after an RCC peripheral clock enabling */ \
                                                tmpreg = READ_REG(RCC->AHB1ENR);\
                                                UNUSED(tmpreg); \
                                              } while(0)

#define __HAL_RCC_USB_OTG_FS_CLK_ENABLE() do { \
                                                __IO uint32_t tmpreg; \
                                                SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGFSEN);\
                                                /* Delay after an RCC peripheral clock enabling */ \
                                                tmpreg = READ_REG(RCC->AHB1ENR);\
                                                UNUSED(tmpreg); \
                                              } while(0)

#define __HAL_RCC_USBPHYC_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_USBPHYCEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB1ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_ADF1_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADF1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB1ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)


#define __HAL_RCC_GPDMA1_CLK_DISABLE() CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPDMA1EN)

#define __HAL_RCC_ADC12_CLK_DISABLE()  CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADC12EN)

#if defined(ETH)
#define __HAL_RCC_ETH1MAC_CLK_DISABLE() CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1MACEN)

#define __HAL_RCC_ETH1TX_CLK_DISABLE() CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1TXEN)

#define __HAL_RCC_ETH1RX_CLK_DISABLE() CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1RXEN)
#endif /* ETH */

#define __HAL_RCC_USB_OTG_HS_CLK_DISABLE() CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN)

#define __HAL_RCC_USB_OTG_FS_CLK_DISABLE() CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGFSEN)

#define __HAL_RCC_USBPHYC_CLK_DISABLE() CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_USBPHYCEN)

#define __HAL_RCC_ADF1_CLK_DISABLE()   CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADF1EN)

/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Disable AHB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_PSSI_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_PSSIEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SDMMC2_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SDMMC2EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_CORDIC_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_CORDICEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SRAM1_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SRAM2_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM2EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_PSSI_CLK_DISABLE()   CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_PSSIEN)

#define __HAL_RCC_SDMMC2_CLK_DISABLE() CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SDMMC2EN)

#define __HAL_RCC_CORDIC_CLK_DISABLE() CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_CORDICEN)

#define __HAL_RCC_SRAM1_CLK_DISABLE()  CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM1EN)

#define __HAL_RCC_SRAM2_CLK_DISABLE()  CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM2EN)

/**
  * @}
  */

/** @defgroup RCC_AHB3_Peripheral_Clock_Enable_Disable AHB3 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_RNG_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_RNGEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB3ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_HASH_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_HASHEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB3ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#if defined(CRYP)
#define __HAL_RCC_CRYP_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_CRYPEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB3ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)
#endif /* CRYP */

#if defined(SAES)
#define __HAL_RCC_SAES_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_SAESEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB3ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)
#endif /* SAES */

#if defined(PKA)
#define __HAL_RCC_PKA_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_PKAEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB3ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)
#endif /* PKA */

#define __HAL_RCC_RNG_CLK_DISABLE()    CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_RNGEN)

#define __HAL_RCC_HASH_CLK_DISABLE()   CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_HASHEN)

#if defined(CRYP)
#define __HAL_RCC_CRYP_CLK_DISABLE()   CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_CRYPEN)
#endif /* CRYP */

#if defined(SAES)
#define __HAL_RCC_SAES_CLK_DISABLE()   CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_SAESEN)
#endif /* SAES */

#if defined(PKA)
#define __HAL_RCC_PKA_CLK_DISABLE()    CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_PKAEN)
#endif /* PKA */

/**
  * @}
  */

/** @defgroup RCC_AHB4_Peripheral_Clock_Enable_Disable AHB4 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB4 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOB_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOC_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOCEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIODEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOE_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOEEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOF_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOFEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOG_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOGEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOH_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOHEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOM_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOMEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPION_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIONEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOO_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOOEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GPIOP_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOPEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_CRC_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_CRCEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_BKPRAM_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_BKPRAMEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)


#define __HAL_RCC_GPIOA_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN)

#define __HAL_RCC_GPIOB_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN)

#define __HAL_RCC_GPIOC_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOCEN)

#define __HAL_RCC_GPIOD_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIODEN)

#define __HAL_RCC_GPIOE_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOEEN)

#define __HAL_RCC_GPIOF_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOFEN)

#define __HAL_RCC_GPIOG_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOGEN)

#define __HAL_RCC_GPIOH_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOHEN)

#define __HAL_RCC_GPIOM_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOMEN)

#define __HAL_RCC_GPION_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIONEN)

#define __HAL_RCC_GPIOO_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOOEN)

#define __HAL_RCC_GPIOP_CLK_DISABLE()  CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOPEN)

#define __HAL_RCC_CRC_CLK_DISABLE()    CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_CRCEN)

#define __HAL_RCC_BKPRAM_CLK_DISABLE() CLEAR_BIT(RCC->AHB4ENR, RCC_AHB4ENR_BKPRAMEN)

/**
  * @}
  */

/** @defgroup RCC_AHB5_Peripheral_Clock_Enable_Disable AHB5 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB5 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_HPDMA1_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_HPDMA1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_DMA2D_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_DMA2DEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#if defined(JPEG)
#define __HAL_RCC_JPEG_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_JPEGEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)
#endif /* JPEG */

#define __HAL_RCC_FMC_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_FMCEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_XSPI1_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPI1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SDMMC1_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_SDMMC1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_XSPI2_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPI2EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_XSPIM_CLK_ENABLE() do { \
                                          __IO uint32_t tmpreg; \
                                          SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPIMEN);\
                                          /* Delay after an RCC peripheral clock enabling */ \
                                          tmpreg = READ_REG(RCC->AHB5ENR);\
                                          UNUSED(tmpreg); \
                                        } while(0)

#if defined(GFXMMU)
#define __HAL_RCC_GFXMMU_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_GFXMMUEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)
#endif /* GFXMMU */

#if defined(GPU2D)
#define __HAL_RCC_GPU2D_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_GPU2DEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->AHB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)
#endif /* GPU2D */

#define __HAL_RCC_HPDMA1_CLK_DISABLE() CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_HPDMA1EN)

#define __HAL_RCC_DMA2D_CLK_DISABLE()  CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_DMA2DEN)

#if defined(JPEG)
#define __HAL_RCC_JPEG_CLK_DISABLE()   CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_JPEGEN)
#endif /* JPEG */

#define __HAL_RCC_FMC_CLK_DISABLE()    CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_FMCEN)

#define __HAL_RCC_XSPI1_CLK_DISABLE()  CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPI1EN)

#define __HAL_RCC_SDMMC1_CLK_DISABLE() CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_SDMMC1EN)

#define __HAL_RCC_XSPI2_CLK_DISABLE()  CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPI2EN)

#define __HAL_RCC_XSPIM_CLK_DISABLE() CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPIMEN)

#if defined(GFXMMU)
#define __HAL_RCC_GFXMMU_CLK_DISABLE() CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_GFXMMUEN)
#endif /* GFXMMU */

#if defined(GPU2D)
#define __HAL_RCC_GPU2D_CLK_DISABLE()  CLEAR_BIT(RCC->AHB5ENR, RCC_AHB5ENR_GPU2DEN)
#endif /* GPU2D */

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_TIM2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM3_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM4_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM5_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM6_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM7_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM12_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM12EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM13_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM13EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM14_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM14EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_LPTIM1_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_WWDG_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_SPI2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_SPI3_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_SPDIFRX_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPDIFRXEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB1ENR1);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_USART2_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_USART3_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_UART4_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_UART5_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_I2C1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1_I3C1EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_I2C2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_I2C3_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_I3C1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1_I3C1EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_CEC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CECEN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_UART7_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART7EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_UART8_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART8EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_CRS_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_CRSEN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_MDIOS_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_MDIOSEN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_FDCAN_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_FDCANEN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_UCPD1_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg; \
                                           SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_UCPD1EN);\
                                           /* Delay after an RCC peripheral clock enabling */ \
                                           tmpreg = READ_REG(RCC->APB1ENR1);\
                                           UNUSED(tmpreg); \
                                         } while(0)

#define __HAL_RCC_TIM2_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN)

#define __HAL_RCC_TIM3_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN)

#define __HAL_RCC_TIM4_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN)

#define __HAL_RCC_TIM5_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN)

#define __HAL_RCC_TIM6_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN)

#define __HAL_RCC_TIM7_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN)

#define __HAL_RCC_TIM12_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM12EN)

#define __HAL_RCC_TIM13_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM13EN)

#define __HAL_RCC_TIM14_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM14EN)

#define __HAL_RCC_LPTIM1_CLK_DISABLE() CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN)

#define __HAL_RCC_SPI2_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN)

#define __HAL_RCC_SPI3_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN)

#define __HAL_RCC_SPDIFRX_CLK_DISABLE() CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPDIFRXEN)

#define __HAL_RCC_USART2_CLK_DISABLE() CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN)

#define __HAL_RCC_USART3_CLK_DISABLE() CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN)

#define __HAL_RCC_UART4_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN)

#define __HAL_RCC_UART5_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN)

#define __HAL_RCC_I2C1_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1_I3C1EN)

#define __HAL_RCC_I2C2_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN)

#define __HAL_RCC_I2C3_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN)

#define __HAL_RCC_I3C1_CLK_DISABLE()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1_I3C1EN)

#define __HAL_RCC_CEC_CLK_DISABLE()    CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CECEN)

#define __HAL_RCC_UART7_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART7EN)

#define __HAL_RCC_UART8_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART8EN)

#define __HAL_RCC_CRS_CLK_DISABLE()    CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_CRSEN)

#define __HAL_RCC_MDIOS_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_MDIOSEN)

#define __HAL_RCC_FDCAN_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_FDCANEN)

#define __HAL_RCC_UCPD1_CLK_DISABLE()  CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_UCPD1EN)

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_TIM1_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_USART1_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SPI1_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SPI4_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_TIM15_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_TIM16_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_TIM17_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_TIM9_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM9EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SPI5_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SAI1_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SAI2_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI2EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB2ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_TIM1_CLK_DISABLE()   CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN)

#define __HAL_RCC_USART1_CLK_DISABLE() CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN)

#define __HAL_RCC_SPI1_CLK_DISABLE()   CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN)

#define __HAL_RCC_SPI4_CLK_DISABLE()   CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN)

#define __HAL_RCC_TIM15_CLK_DISABLE()  CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN)

#define __HAL_RCC_TIM16_CLK_DISABLE()  CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN)

#define __HAL_RCC_TIM17_CLK_DISABLE()  CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN)

#define __HAL_RCC_TIM9_CLK_DISABLE()   CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM9EN)

#define __HAL_RCC_SPI5_CLK_DISABLE()   CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN)

#define __HAL_RCC_SAI1_CLK_DISABLE()   CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN)

#define __HAL_RCC_SAI2_CLK_DISABLE()   CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI2EN)

/**
  * @}
  */

/** @defgroup RCC_APB4_Peripheral_Clock_Enable_Disable APB4 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB4 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_SBS_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_SBSEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_LPUART1_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_LPUART1EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SPI6_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_SPI6EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_LPTIM2_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM2EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_LPTIM3_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM3EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_LPTIM4_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM4EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_LPTIM5_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM5EN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_VREF_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_VREFEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_RTCAPB_CLK_ENABLE()     do { \
                                               __IO uint32_t tmpreg; \
                                               SET_BIT(RCC->APB4ENR, RCC_APB4ENR_RTCAPBEN);\
                                               /* Delay after an RCC peripheral clock enabling */ \
                                               tmpreg = READ_REG(RCC->APB4ENR);\
                                               UNUSED(tmpreg); \
                                             } while(0)

#define __HAL_RCC_DTS_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB4ENR, RCC_APB4ENR_DTSEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB4ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_SBS_CLK_DISABLE()     CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_SBSEN)

#define __HAL_RCC_LPUART1_CLK_DISABLE() CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_LPUART1EN)

#define __HAL_RCC_SPI6_CLK_DISABLE()   CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_SPI6EN)

#define __HAL_RCC_LPTIM2_CLK_DISABLE() CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM2EN)

#define __HAL_RCC_LPTIM3_CLK_DISABLE() CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM3EN)

#define __HAL_RCC_LPTIM4_CLK_DISABLE() CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM4EN)

#define __HAL_RCC_LPTIM5_CLK_DISABLE() CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM5EN)

#define __HAL_RCC_VREF_CLK_DISABLE()   CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_VREFEN)

#define __HAL_RCC_RTCAPB_CLK_DISABLE()    CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_RTCAPBEN)

#define __HAL_RCC_DTS_CLK_DISABLE()    CLEAR_BIT(RCC->APB4ENR, RCC_APB4ENR_DTSEN)

/**
  * @}
  */

/** @defgroup RCC_APB5_Peripheral_Clock_Enable_Disable APB5 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB5 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_LTDC_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB5ENR, RCC_APB5ENR_LTDCEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_DCMIPP_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB5ENR, RCC_APB5ENR_DCMIPPEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_GFXTIM_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg; \
                                            SET_BIT(RCC->APB5ENR, RCC_APB5ENR_GFXTIMEN);\
                                            /* Delay after an RCC peripheral clock enabling */ \
                                            tmpreg = READ_REG(RCC->APB5ENR);\
                                            UNUSED(tmpreg); \
                                          } while(0)

#define __HAL_RCC_LTDC_CLK_DISABLE()   CLEAR_BIT(RCC->APB5ENR, RCC_APB5ENR_LTDCEN)

#define __HAL_RCC_DCMIPP_CLK_DISABLE() CLEAR_BIT(RCC->APB5ENR, RCC_APB5ENR_DCMIPPEN)

#define __HAL_RCC_GFXTIM_CLK_DISABLE() CLEAR_BIT(RCC->APB5ENR, RCC_APB5ENR_GFXTIMEN)

/**
  * @}
  */

/** @defgroup RCC_AHB1_Clock_Enable_Disable_Status AHB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_GPDMA1_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPDMA1EN) != 0U)

#define __HAL_RCC_ADC12_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADC12EN) != 0U)

#if defined(ETH)
#define __HAL_RCC_ETH1MAC_IS_CLK_ENABLED() (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1MACEN) != 0U)

#define __HAL_RCC_ETH1TX_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1TXEN) != 0U)

#define __HAL_RCC_ETH1RX_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETH1RXEN) != 0U)
#endif /* ETH */

#define __HAL_RCC_USB_OTG_HS_IS_CLK_ENABLED() (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN) != 0U)

#define __HAL_RCC_USB_OTG_FS_IS_CLK_ENABLED() (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGFSEN) != 0U)

#define __HAL_RCC_USBPHYC_IS_CLK_ENABLED() (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_USBPHYCEN) != 0U)

#define __HAL_RCC_ADF1_IS_CLK_ENABLED()    (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADF1EN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_AHB2_Clock_Enable_Disable_Status AHB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_PSSI_IS_CLK_ENABLED()    (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_PSSIEN) != 0U)

#define __HAL_RCC_SDMMC2_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SDMMC2EN) != 0U)

#define __HAL_RCC_CORDIC_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_CORDICEN) != 0U)

#define __HAL_RCC_SRAM1_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM1EN) != 0U)

#define __HAL_RCC_SRAM2_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_SRAM2EN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_AHB3_Clock_Enable_Disable_Status AHB3 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB3 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_RNG_IS_CLK_ENABLED()     (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_RNGEN) != 0U)

#define __HAL_RCC_HASH_IS_CLK_ENABLED()    (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_HASHEN) != 0U)

#if defined(CRYP)
#define __HAL_RCC_CRYP_IS_CLK_ENABLED()    (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_CRYPEN) != 0U)
#endif /* CRYP */

#if defined(SAES)
#define __HAL_RCC_SAES_IS_CLK_ENABLED()    (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_SAESEN) != 0U)
#endif /* SAES */

#if defined(PKA)
#define __HAL_RCC_PKA_IS_CLK_ENABLED()     (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_PKAEN) != 0U)
#endif /* PKA */

/**
  * @}
  */

/** @defgroup RCC_AHB4_Clock_Enable_Disable_Status AHB4 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB4 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN) != 0U)

#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN) != 0U)

#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOCEN) != 0U)

#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIODEN) != 0U)

#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOEEN) != 0U)

#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOFEN) != 0U)

#define __HAL_RCC_GPIOG_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOGEN) != 0U)

#define __HAL_RCC_GPIOH_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOHEN) != 0U)

#define __HAL_RCC_GPIOM_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOMEN) != 0U)

#define __HAL_RCC_GPION_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIONEN) != 0U)

#define __HAL_RCC_GPIOO_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOOEN) != 0U)

#define __HAL_RCC_GPIOP_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOPEN) != 0U)

#define __HAL_RCC_CRC_IS_CLK_ENABLED()     (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_CRCEN) != 0U)

#define __HAL_RCC_BKPRAM_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_BKPRAMEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_AHB5_Clock_Enable_Disable_Status AHB5 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB5 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_HPDMA1_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_HPDMA1EN) != 0U)

#define __HAL_RCC_DMA2D_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_DMA2DEN) != 0U)

#if defined(JPEG)
#define __HAL_RCC_JPEG_IS_CLK_ENABLED()    (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_JPEGEN) != 0U)
#endif /* JPEG */

#define __HAL_RCC_FMC_IS_CLK_ENABLED()     (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_FMCEN) != 0U)

#define __HAL_RCC_XSPI1_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPI1EN) != 0U)

#define __HAL_RCC_SDMMC1_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_SDMMC1EN) != 0U)

#define __HAL_RCC_XSPI2_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPI2EN) != 0U)

#define __HAL_RCC_XSPIM_IS_CLK_ENABLED() (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPIMEN) != 0U)

#if defined(GFXMMU)
#define __HAL_RCC_GFXMMU_IS_CLK_ENABLED()  (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_GFXMMUEN) != 0U)
#endif /* GFXMMU */

#if defined(GPU2D)
#define __HAL_RCC_GPU2D_IS_CLK_ENABLED()   (READ_BIT(RCC->AHB5ENR, RCC_AHB5ENR_GPU2DEN) != 0U)
#endif /* GPU2D */

/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Enable_Disable_Status APB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_TIM2_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN) != 0U)

#define __HAL_RCC_TIM3_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN) != 0U)

#define __HAL_RCC_TIM4_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN) != 0U)

#define __HAL_RCC_TIM5_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN) != 0U)

#define __HAL_RCC_TIM6_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN) != 0U)

#define __HAL_RCC_TIM7_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN) != 0U)

#define __HAL_RCC_TIM12_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM12EN) != 0U)

#define __HAL_RCC_TIM13_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM13EN) != 0U)

#define __HAL_RCC_TIM14_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM14EN) != 0U)

#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()  (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN) != 0U)

#define __HAL_RCC_WWDG_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN) != 0U)

#define __HAL_RCC_SPI2_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN) != 0U)

#define __HAL_RCC_SPI3_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN) != 0U)

#define __HAL_RCC_SPDIFRX_IS_CLK_ENABLED() (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPDIFRXEN) != 0U)

#define __HAL_RCC_USART2_IS_CLK_ENABLED()  (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN) != 0U)

#define __HAL_RCC_USART3_IS_CLK_ENABLED()  (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN) != 0U)

#define __HAL_RCC_UART4_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN) != 0U)

#define __HAL_RCC_UART5_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN) != 0U)

#define __HAL_RCC_I2C1_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1_I3C1EN) != 0U)

#define __HAL_RCC_I2C2_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN) != 0U)

#define __HAL_RCC_I2C3_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN) != 0U)

#define __HAL_RCC_I3C1_IS_CLK_ENABLED()    (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1_I3C1EN) != 0U)

#define __HAL_RCC_CEC_IS_CLK_ENABLED()     (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CECEN) != 0U)

#define __HAL_RCC_UART7_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART7EN) != 0U)

#define __HAL_RCC_UART8_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART8EN) != 0U)

#define __HAL_RCC_CRS_IS_CLK_ENABLED()     (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_CRSEN) != 0U)

#define __HAL_RCC_MDIOS_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_MDIOSEN) != 0U)

#define __HAL_RCC_FDCAN_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_FDCANEN) != 0U)

#define __HAL_RCC_UCPD1_IS_CLK_ENABLED()   (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_UCPD1EN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Enable_Disable_Status APB2 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_TIM1_IS_CLK_ENABLED()    (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN) != 0U)

#define __HAL_RCC_USART1_IS_CLK_ENABLED()  (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN) != 0U)

#define __HAL_RCC_SPI1_IS_CLK_ENABLED()    (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN) != 0U)

#define __HAL_RCC_SPI4_IS_CLK_ENABLED()    (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN) != 0U)

#define __HAL_RCC_TIM15_IS_CLK_ENABLED()   (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN) != 0U)

#define __HAL_RCC_TIM16_IS_CLK_ENABLED()   (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN) != 0U)

#define __HAL_RCC_TIM17_IS_CLK_ENABLED()   (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN) != 0U)

#define __HAL_RCC_TIM9_IS_CLK_ENABLED()    (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM9EN) != 0U)

#define __HAL_RCC_SPI5_IS_CLK_ENABLED()    (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN) != 0U)

#define __HAL_RCC_SAI1_IS_CLK_ENABLED()    (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN) != 0U)

#define __HAL_RCC_SAI2_IS_CLK_ENABLED()    (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI2EN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_APB4_Clock_Enable_Disable_Status APB4 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB4 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_SBS_IS_CLK_ENABLED()     (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_SBSEN) != 0U)

#define __HAL_RCC_LPUART1_IS_CLK_ENABLED() (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_LPUART1EN) != 0U)

#define __HAL_RCC_SPI6_IS_CLK_ENABLED()    (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_SPI6EN) != 0U)

#define __HAL_RCC_LPTIM2_IS_CLK_ENABLED()  (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM2EN) != 0U)

#define __HAL_RCC_LPTIM3_IS_CLK_ENABLED()  (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM3EN) != 0U)

#define __HAL_RCC_LPTIM4_IS_CLK_ENABLED()  (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM4EN) != 0U)

#define __HAL_RCC_LPTIM5_IS_CLK_ENABLED()  (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_LPTIM5EN) != 0U)

#define __HAL_RCC_VREF_IS_CLK_ENABLED()    (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_VREFEN) != 0U)

#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()     (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_RTCAPBEN) != 0U)

#define __HAL_RCC_DTS_IS_CLK_ENABLED()     (READ_BIT(RCC->APB4ENR, RCC_APB4ENR_DTSEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_APB5_Clock_Enable_Disable_Status APB5 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB5 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_LTDC_IS_CLK_ENABLED()    (READ_BIT(RCC->APB5ENR, RCC_APB5ENR_LTDCEN) != 0U)

#define __HAL_RCC_DCMIPP_IS_CLK_ENABLED()  (READ_BIT(RCC->APB5ENR, RCC_APB5ENR_DCMIPPEN) != 0U)

#define __HAL_RCC_GFXTIM_IS_CLK_ENABLED()  (READ_BIT(RCC->APB5ENR, RCC_APB5ENR_GFXTIMEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_AHB1_Force_Release_Reset AHB1 Peripheral Force Release Reset
  * @brief  Force or release AHB1 peripheral reset.
  * @{
  */

#define __HAL_RCC_AHB1_FORCE_RESET()       WRITE_REG(RCC->AHB1RSTR, 0x8E008030UL)
#define __HAL_RCC_AHB1_RELEASE_RESET()     WRITE_REG(RCC->AHB1RSTR, 0UL)

#define __HAL_RCC_GPDMA1_FORCE_RESET()     SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_GPDMA1RST)
#define __HAL_RCC_GPDMA1_RELEASE_RESET()   CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_GPDMA1RST)

#define __HAL_RCC_ADC12_FORCE_RESET()      SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_ADC12RST)
#define __HAL_RCC_ADC12_RELEASE_RESET()    CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_ADC12RST)

#if defined(ETH)
#define __HAL_RCC_ETH1_FORCE_RESET()       SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_ETH1RST)
#define __HAL_RCC_ETH1_RELEASE_RESET()     CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_ETH1RST)
#endif /* ETH */

#define __HAL_RCC_USB_OTG_HS_FORCE_RESET()   SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_OTGHSRST)
#define __HAL_RCC_USB_OTG_HS_RELEASE_RESET() CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_OTGHSRST)

#define __HAL_RCC_USB_OTG_FS_FORCE_RESET()   SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_OTGFSRST)
#define __HAL_RCC_USB_OTG_FS_RELEASE_RESET() CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_OTGFSRST)

#define __HAL_RCC_USBPHYC_FORCE_RESET()    SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_USBPHYCRST)
#define __HAL_RCC_USBPHYC_RELEASE_RESET()  CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_USBPHYCRST)

#define __HAL_RCC_ADF1_FORCE_RESET()       SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_ADF1RST)
#define __HAL_RCC_ADF1_RELEASE_RESET()     CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_ADF1RST)

/**
  * @}
  */

/** @defgroup RCC_AHB2_Force_Release_Reset AHB2 Peripheral Force Release Reset
  * @brief  Force or release AHB2 peripheral reset.
  * @{
  */

#define __HAL_RCC_AHB2_FORCE_RESET()       WRITE_REG(RCC->AHB2RSTR, 0x00004202UL)
#define __HAL_RCC_AHB2_RELEASE_RESET()     WRITE_REG(RCC->AHB2RSTR, 0UL)

#define __HAL_RCC_PSSI_FORCE_RESET()       SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_PSSIRST)
#define __HAL_RCC_PSSI_RELEASE_RESET()     CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_PSSIRST)

#define __HAL_RCC_SDMMC2_FORCE_RESET()     SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_SDMMC2RST)
#define __HAL_RCC_SDMMC2_RELEASE_RESET()   CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_SDMMC2RST)

#define __HAL_RCC_CORDIC_FORCE_RESET()     SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_CORDICRST)
#define __HAL_RCC_CORDIC_RELEASE_RESET()   CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_CORDICRST)

/**
  * @}
  */

/** @defgroup RCC_AHB3_Force_Release_Reset AHB3 Peripheral Force Release Reset
  * @brief  Force or release AHB3 peripheral reset.
  * @{
  */

#define __HAL_RCC_AHB3_FORCE_RESET()       WRITE_REG(RCC->AHB3RSTR, 0x00000057UL)
#define __HAL_RCC_AHB3_RELEASE_RESET()     WRITE_REG(RCC->AHB3RSTR, 0UL)

#define __HAL_RCC_RNG_FORCE_RESET()        SET_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_RNGRST)
#define __HAL_RCC_RNG_RELEASE_RESET()      CLEAR_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_RNGRST)

#define __HAL_RCC_HASH_FORCE_RESET()       SET_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_HASHRST)
#define __HAL_RCC_HASH_RELEASE_RESET()     CLEAR_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_HASHRST)

#if defined(CRYP)
#define __HAL_RCC_CRYP_FORCE_RESET()       SET_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_CRYPRST)
#define __HAL_RCC_CRYP_RELEASE_RESET()     CLEAR_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_CRYPRST)
#endif /* CRYP */

#if defined(SAES)
#define __HAL_RCC_SAES_FORCE_RESET()       SET_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_SAESRST)
#define __HAL_RCC_SAES_RELEASE_RESET()     CLEAR_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_SAESRST)
#endif /* SAES */

#if defined(PKA)
#define __HAL_RCC_PKA_FORCE_RESET()        SET_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_PKARST)
#define __HAL_RCC_PKA_RELEASE_RESET()      CLEAR_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_PKARST)
#endif /* PKA */

/**
  * @}
  */

/** @defgroup RCC_AHB4_Force_Release_Reset AHB4 Peripheral Force Release Reset
  * @brief  Force or release AHB4 peripheral reset.
  * @{
  */

#define __HAL_RCC_AHB4_FORCE_RESET()       WRITE_REG(RCC->AHB4RSTR, 0x0008B0FFUL)
#define __HAL_RCC_AHB4_RELEASE_RESET()     WRITE_REG(RCC->AHB4RSTR, 0UL)

#define __HAL_RCC_GPIOA_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOARST)
#define __HAL_RCC_GPIOA_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOARST)

#define __HAL_RCC_GPIOB_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOBRST)
#define __HAL_RCC_GPIOB_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOBRST)

#define __HAL_RCC_GPIOC_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOCRST)
#define __HAL_RCC_GPIOC_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOCRST)

#define __HAL_RCC_GPIOD_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIODRST)
#define __HAL_RCC_GPIOD_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIODRST)

#define __HAL_RCC_GPIOE_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOERST)
#define __HAL_RCC_GPIOE_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOERST)

#define __HAL_RCC_GPIOF_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOFRST)
#define __HAL_RCC_GPIOF_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOFRST)

#define __HAL_RCC_GPIOG_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOGRST)
#define __HAL_RCC_GPIOG_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOGRST)

#define __HAL_RCC_GPIOH_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOHRST)
#define __HAL_RCC_GPIOH_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOHRST)

#define __HAL_RCC_GPIOM_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOMRST)
#define __HAL_RCC_GPIOM_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOMRST)

#define __HAL_RCC_GPION_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIONRST)
#define __HAL_RCC_GPION_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIONRST)

#define __HAL_RCC_GPIOO_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOORST)
#define __HAL_RCC_GPIOO_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOORST)

#define __HAL_RCC_GPIOP_FORCE_RESET()      SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOPRST)
#define __HAL_RCC_GPIOP_RELEASE_RESET()    CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_GPIOPRST)

#define __HAL_RCC_CRC_FORCE_RESET()        SET_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_CRCRST)
#define __HAL_RCC_CRC_RELEASE_RESET()      CLEAR_BIT(RCC->AHB4RSTR, RCC_AHB4RSTR_CRCRST)

/**
  * @}
  */

/** @defgroup RCC_AHB5_Force_Release_Reset AHB5 Peripheral Force Release Reset
  * @brief  Force or release AHB5 peripheral reset.
  * @{
  */

#define __HAL_RCC_AHB5_FORCE_RESET()       WRITE_REG(RCC->AHB5RSTR, 0x0018513BUL)
#define __HAL_RCC_AHB5_RELEASE_RESET()     WRITE_REG(RCC->AHB5RSTR, 0UL)

#define __HAL_RCC_HPDMA1_FORCE_RESET()     SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_HPDMA1RST)
#define __HAL_RCC_HPDMA1_RELEASE_RESET()   CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_HPDMA1RST)

#define __HAL_RCC_DMA2D_FORCE_RESET()      SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_DMA2DRST)
#define __HAL_RCC_DMA2D_RELEASE_RESET()    CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_DMA2DRST)

#if defined(JPEG)
#define __HAL_RCC_JPEG_FORCE_RESET()       SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_JPEGRST)
#define __HAL_RCC_JPEG_RELEASE_RESET()     CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_JPEGRST)
#endif /* JPEG */

#define __HAL_RCC_FMC_FORCE_RESET()        SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_FMCRST)
#define __HAL_RCC_FMC_RELEASE_RESET()      CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_FMCRST)

#define __HAL_RCC_XSPI1_FORCE_RESET()      SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_XSPI1RST)
#define __HAL_RCC_XSPI1_RELEASE_RESET()    CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_XSPI1RST)

#define __HAL_RCC_SDMMC1_FORCE_RESET()     SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_SDMMC1RST)
#define __HAL_RCC_SDMMC1_RELEASE_RESET()   CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_SDMMC1RST)

#define __HAL_RCC_XSPI2_FORCE_RESET()      SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_XSPI2RST)
#define __HAL_RCC_XSPI2_RELEASE_RESET()    CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_XSPI2RST)

#define __HAL_RCC_XSPIM_FORCE_RESET()   SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_XSPIMRST)
#define __HAL_RCC_XSPIM_RELEASE_RESET() CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_XSPIMRST)

#if defined(GFXMMU)
#define __HAL_RCC_GFXMMU_FORCE_RESET()     SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_GFXMMURST)
#define __HAL_RCC_GFXMMU_RELEASE_RESET()   CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_GFXMMURST)
#endif /* GFXMMU */

#if defined(GPU2D)
#define __HAL_RCC_GPU2D_FORCE_RESET()      SET_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_GPU2DRST)
#define __HAL_RCC_GPU2D_RELEASE_RESET()    CLEAR_BIT(RCC->AHB5RSTR, RCC_AHB5RSTR_GPU2DRST)
#endif /* GPU2D */

/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset APB1 Peripheral Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{
  */

#define __HAL_RCC_APB1_FORCE_RESET()       do { \
                                                WRITE_REG(RCC->APB1RSTR1, 0xC8FFC3FFUL); \
                                                WRITE_REG(RCC->APB1RSTR2, 0x08000122UL); \
                                              } while(0)
#define __HAL_RCC_APB1_RELEASE_RESET()     do { \
                                                WRITE_REG(RCC->APB1RSTR1, 0UL); \
                                                WRITE_REG(RCC->APB1RSTR2, 0UL); \
                                              } while(0)

#define __HAL_RCC_TIM2_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM2RST)
#define __HAL_RCC_TIM2_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM2RST)

#define __HAL_RCC_TIM3_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM3RST)
#define __HAL_RCC_TIM3_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM3RST)

#define __HAL_RCC_TIM4_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM4RST)
#define __HAL_RCC_TIM4_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM4RST)

#define __HAL_RCC_TIM5_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM5RST)
#define __HAL_RCC_TIM5_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM5RST)

#define __HAL_RCC_TIM6_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM6RST)
#define __HAL_RCC_TIM6_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM6RST)

#define __HAL_RCC_TIM7_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM7RST)
#define __HAL_RCC_TIM7_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM7RST)

#define __HAL_RCC_TIM12_FORCE_RESET()      SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM12RST)
#define __HAL_RCC_TIM12_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM12RST)

#define __HAL_RCC_TIM13_FORCE_RESET()      SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM13RST)
#define __HAL_RCC_TIM13_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM13RST)

#define __HAL_RCC_TIM14_FORCE_RESET()      SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM14RST)
#define __HAL_RCC_TIM14_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM14RST)

#define __HAL_RCC_LPTIM1_FORCE_RESET()     SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_LPTIM1RST)
#define __HAL_RCC_LPTIM1_RELEASE_RESET()   CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_LPTIM1RST)

#define __HAL_RCC_SPI2_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI2RST)
#define __HAL_RCC_SPI2_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI2RST)

#define __HAL_RCC_SPI3_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI3RST)
#define __HAL_RCC_SPI3_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI3RST)

#define __HAL_RCC_SPDIFRX_FORCE_RESET()    SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPDIFRXRST)
#define __HAL_RCC_SPDIFRX_RELEASE_RESET()  CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPDIFRXRST)

#define __HAL_RCC_USART2_FORCE_RESET()     SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST)
#define __HAL_RCC_USART2_RELEASE_RESET()   CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST)

#define __HAL_RCC_USART3_FORCE_RESET()     SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST)
#define __HAL_RCC_USART3_RELEASE_RESET()   CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST)

#define __HAL_RCC_UART4_FORCE_RESET()      SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST)
#define __HAL_RCC_UART4_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST)

#define __HAL_RCC_UART5_FORCE_RESET()      SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST)
#define __HAL_RCC_UART5_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST)

#define __HAL_RCC_I2C1_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1_I3C1RST)
#define __HAL_RCC_I2C1_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1_I3C1RST)

#define __HAL_RCC_I2C2_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C2RST)
#define __HAL_RCC_I2C2_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C2RST)

#define __HAL_RCC_I2C3_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C3RST)
#define __HAL_RCC_I2C3_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C3RST)

#define __HAL_RCC_I3C1_FORCE_RESET()       SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1_I3C1RST)
#define __HAL_RCC_I3C1_RELEASE_RESET()     CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1_I3C1RST)

#define __HAL_RCC_CEC_FORCE_RESET()        SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_CECRST)
#define __HAL_RCC_CEC_RELEASE_RESET()      CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_CECRST)

#define __HAL_RCC_UART7_FORCE_RESET()      SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART7RST)
#define __HAL_RCC_UART7_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART7RST)

#define __HAL_RCC_UART8_FORCE_RESET()      SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART8RST)
#define __HAL_RCC_UART8_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART8RST)

#define __HAL_RCC_CRS_FORCE_RESET()        SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_CRSRST)
#define __HAL_RCC_CRS_RELEASE_RESET()      CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_CRSRST)

#define __HAL_RCC_MDIOS_FORCE_RESET()      SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_MDIOSRST)
#define __HAL_RCC_MDIOS_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_MDIOSRST)

#define __HAL_RCC_FDCAN_FORCE_RESET()      SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_FDCANRST)
#define __HAL_RCC_FDCAN_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_FDCANRST)

#define __HAL_RCC_UCPD1_FORCE_RESET()      SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_UCPD1RST)
#define __HAL_RCC_UCPD1_RELEASE_RESET()    CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_UCPD1RST)

/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset APB2 Peripheral Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{
  */

#define __HAL_RCC_APB2_FORCE_RESET()       WRITE_REG(RCC->APB2RSTR, 0xC8FFC3FFUL)
#define __HAL_RCC_APB2_RELEASE_RESET()     WRITE_REG(RCC->APB2RSTR, 0UL)

#define __HAL_RCC_TIM1_FORCE_RESET()       SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST)
#define __HAL_RCC_TIM1_RELEASE_RESET()     CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST)

#define __HAL_RCC_USART1_FORCE_RESET()     SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST)
#define __HAL_RCC_USART1_RELEASE_RESET()   CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST)

#define __HAL_RCC_SPI1_FORCE_RESET()       SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST)
#define __HAL_RCC_SPI1_RELEASE_RESET()     CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST)

#define __HAL_RCC_SPI4_FORCE_RESET()       SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI4RST)
#define __HAL_RCC_SPI4_RELEASE_RESET()     CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI4RST)

#define __HAL_RCC_TIM15_FORCE_RESET()      SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM15RST)
#define __HAL_RCC_TIM15_RELEASE_RESET()    CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM15RST)

#define __HAL_RCC_TIM16_FORCE_RESET()      SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST)
#define __HAL_RCC_TIM16_RELEASE_RESET()    CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST)

#define __HAL_RCC_TIM17_FORCE_RESET()      SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM17RST)
#define __HAL_RCC_TIM17_RELEASE_RESET()    CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM17RST)

#define __HAL_RCC_TIM9_FORCE_RESET()       SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM9RST)
#define __HAL_RCC_TIM9_RELEASE_RESET()     CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM9RST)

#define __HAL_RCC_SPI5_FORCE_RESET()       SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI5RST)
#define __HAL_RCC_SPI5_RELEASE_RESET()     CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI5RST)

#define __HAL_RCC_SAI1_FORCE_RESET()       SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI1RST)
#define __HAL_RCC_SAI1_RELEASE_RESET()     CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI1RST)

#define __HAL_RCC_SAI2_FORCE_RESET()       SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI2RST)
#define __HAL_RCC_SAI2_RELEASE_RESET()     CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI2RST)

/**
  * @}
  */

/** @defgroup RCC_APB4_Force_Release_Reset APB4 Peripheral Force Release Reset
  * @brief  Force or release APB4 peripheral reset.
  * @{
  */

#define __HAL_RCC_APB4_FORCE_RESET()       WRITE_REG(RCC->APB4RSTR, 0x04009E2AUL)
#define __HAL_RCC_APB4_RELEASE_RESET()     WRITE_REG(RCC->APB4RSTR, 0UL)

#define __HAL_RCC_SBS_FORCE_RESET()        SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_SBSRST)
#define __HAL_RCC_SBS_RELEASE_RESET()      CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_SBSRST)

#define __HAL_RCC_LPUART1_FORCE_RESET()    SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPUART1RST)
#define __HAL_RCC_LPUART1_RELEASE_RESET()  CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPUART1RST)

#define __HAL_RCC_SPI6_FORCE_RESET()       SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_SPI6RST)
#define __HAL_RCC_SPI6_RELEASE_RESET()     CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_SPI6RST)

#define __HAL_RCC_LPTIM2_FORCE_RESET()     SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPTIM2RST)
#define __HAL_RCC_LPTIM2_RELEASE_RESET()   CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPTIM2RST)

#define __HAL_RCC_LPTIM3_FORCE_RESET()     SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPTIM3RST)
#define __HAL_RCC_LPTIM3_RELEASE_RESET()   CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPTIM3RST)

#define __HAL_RCC_LPTIM4_FORCE_RESET()     SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPTIM4RST)
#define __HAL_RCC_LPTIM4_RELEASE_RESET()   CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPTIM4RST)

#define __HAL_RCC_LPTIM5_FORCE_RESET()     SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPTIM5RST)
#define __HAL_RCC_LPTIM5_RELEASE_RESET()   CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_LPTIM5RST)

#define __HAL_RCC_VREF_FORCE_RESET()       SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_VREFRST)
#define __HAL_RCC_VREF_RELEASE_RESET()     CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_VREFRST)

#define __HAL_RCC_DTS_FORCE_RESET()        SET_BIT(RCC->APB4RSTR, RCC_APB4RSTR_DTSRST)
#define __HAL_RCC_DTS_RELEASE_RESET()      CLEAR_BIT(RCC->APB4RSTR, RCC_APB4RSTR_DTSRST)

/**
  * @}
  */

/** @defgroup RCC_APB5_Force_Release_Reset APB5 Peripheral Force Release Reset
  * @brief  Force or release APB5 peripheral reset.
  * @{
  */

#define __HAL_RCC_APB5_FORCE_RESET()       WRITE_REG(RCC->APB5RSTR, 0x00000016UL)
#define __HAL_RCC_APB5_RELEASE_RESET()     WRITE_REG(RCC->APB5RSTR, 0UL)

#define __HAL_RCC_LTDC_FORCE_RESET()       SET_BIT(RCC->APB5RSTR, RCC_APB5RSTR_LTDCRST)
#define __HAL_RCC_LTDC_RELEASE_RESET()     CLEAR_BIT(RCC->APB5RSTR, RCC_APB5RSTR_LTDCRST)

#define __HAL_RCC_DCMIPP_FORCE_RESET()     SET_BIT(RCC->APB5RSTR, RCC_APB5RSTR_DCMIPPRST)
#define __HAL_RCC_DCMIPP_RELEASE_RESET()   CLEAR_BIT(RCC->APB5RSTR, RCC_APB5RSTR_DCMIPPRST)

#define __HAL_RCC_GFXTIM_FORCE_RESET()     SET_BIT(RCC->APB5RSTR, RCC_APB5RSTR_GFXTIMRST)
#define __HAL_RCC_GFXTIM_RELEASE_RESET()   CLEAR_BIT(RCC->APB5RSTR, RCC_APB5RSTR_GFXTIMRST)

/**
  * @}
  */


/** @defgroup RCC_AHB1_Clock_Sleep_Enable_Disable AHB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_GPDMA1_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_GPDMA1LPEN)

#define __HAL_RCC_ADC12_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ADC12LPEN)
#if defined(ETH)
#define __HAL_RCC_ETH1MAC_CLK_SLEEP_ENABLE() SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1MACLPEN)

#define __HAL_RCC_ETH1TX_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1TXLPEN)

#define __HAL_RCC_ETH1RX_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1RXLPEN)
#endif /* ETH */

#define __HAL_RCC_USB_OTG_HS_CLK_SLEEP_ENABLE() SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_OTGHSLPEN)

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_ENABLE() SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_OTGFSLPEN)

#define __HAL_RCC_USBPHYC_CLK_SLEEP_ENABLE() SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_USBPHYCLPEN)

#define __HAL_RCC_ADF1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ADF1LPEN)


#define __HAL_RCC_GPDMA1_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_GPDMA1LPEN)

#define __HAL_RCC_ADC12_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ADC12LPEN)

#if defined(ETH)
#define __HAL_RCC_ETH1MAC_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1MACLPEN)

#define __HAL_RCC_ETH1TX_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1TXLPEN)

#define __HAL_RCC_ETH1RX_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1RXLPEN)
#endif /* ETH */

#define __HAL_RCC_USB_OTG_HS_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_OTGHSLPEN)

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_OTGFSLPEN)

#define __HAL_RCC_USBPHYC_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_USBPHYCLPEN)

#define __HAL_RCC_ADF1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ADF1LPEN)

/**
  * @}
  */

/** @defgroup RCC_AHB2_Clock_Sleep_Enable_Disable AHB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_PSSI_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_PSSILPEN)

#define __HAL_RCC_SDMMC2_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SDMMC2LPEN)

#define __HAL_RCC_CORDIC_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_CORDICLPEN)

#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SRAM1LPEN)

#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SRAM2LPEN)


#define __HAL_RCC_PSSI_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_PSSILPEN)

#define __HAL_RCC_SDMMC2_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SDMMC2LPEN)

#define __HAL_RCC_CORDIC_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_CORDICLPEN)

#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SRAM1LPEN)

#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SRAM2LPEN)

/**
  * @}
  */

/** @defgroup RCC_AHB3_Clock_Sleep_Enable_Disable AHB3 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB3 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_RNGLPEN)

#define __HAL_RCC_HASH_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_HASHLPEN)

#if defined(CRYP)
#define __HAL_RCC_CRYP_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_CRYPLPEN)
#endif /* CRYP */

#if defined(SAES)
#define __HAL_RCC_SAES_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_SAESLPEN)
#endif /* SAES */

#if defined(PKA)
#define __HAL_RCC_PKA_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_PKALPEN)
#endif /* PKA */


#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_RNGLPEN)

#define __HAL_RCC_HASH_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_HASHLPEN)

#if defined(CRYP)
#define __HAL_RCC_CRYP_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_CRYPLPEN)
#endif /* CRYP */

#if defined(SAES)
#define __HAL_RCC_SAES_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_SAESLPEN)
#endif /* SAES */

#if defined(PKA)
#define __HAL_RCC_PKA_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_PKALPEN)
#endif /* PKA */

/**
  * @}
  */

/** @defgroup RCC_AHB4_Clock_Sleep_Enable_Disable AHB4 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB4 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOALPEN)

#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOBLPEN)

#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOCLPEN)

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIODLPEN)

#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOELPEN)

#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOFLPEN)

#define __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOGLPEN)

#define __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOHLPEN)

#define __HAL_RCC_GPIOM_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOMLPEN)

#define __HAL_RCC_GPION_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIONLPEN)

#define __HAL_RCC_GPIOO_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOOLPEN)

#define __HAL_RCC_GPIOP_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOPLPEN)

#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_CRCLPEN)

#define __HAL_RCC_BKPRAM_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_BKPRAMLPEN)


#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOALPEN)

#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOBLPEN)

#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOCLPEN)

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIODLPEN)

#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOELPEN)

#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOFLPEN)

#define __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOGLPEN)

#define __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOHLPEN)

#define __HAL_RCC_GPIOM_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOMLPEN)

#define __HAL_RCC_GPION_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIONLPEN)

#define __HAL_RCC_GPIOO_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOOLPEN)

#define __HAL_RCC_GPIOP_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOPLPEN)

#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_CRCLPEN)

#define __HAL_RCC_BKPRAM_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_BKPRAMLPEN)

/**
  * @}
  */

/** @defgroup RCC_AHB5_Clock_Sleep_Enable_Disable AHB5 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_HPDMA1_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_HPDMA1LPEN)

#define __HAL_RCC_DMA2D_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DMA2DLPEN)

#define __HAL_RCC_FLASH_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_FLASHLPEN)

#if defined(JPEG)
#define __HAL_RCC_JPEG_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_JPEGLPEN)
#endif /* JPEG */

#define __HAL_RCC_FMC_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_FMCLPEN)

#define __HAL_RCC_XSPI1_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPI1LPEN)

#define __HAL_RCC_SDMMC1_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_SDMMC1LPEN)

#define __HAL_RCC_XSPI2_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPI2LPEN)

#define __HAL_RCC_XSPIM_CLK_SLEEP_ENABLE() SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPIMLPEN)

#if defined(GFXMMU)
#define __HAL_RCC_GFXMMU_CLK_SLEEP_ENABLE()  SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_GFXMMULPEN)
#endif /* GFXMMU */

#if defined(GPU2D)
#define __HAL_RCC_GPU2D_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_GPU2DLPEN)
#endif /* GPU2D */

#define __HAL_RCC_DTCM1_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DTCM1LPEN)

#define __HAL_RCC_DTCM2_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DTCM2LPEN)

#define __HAL_RCC_ITCM_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_ITCMLPEN)

#define __HAL_RCC_AXISRAM_CLK_SLEEP_ENABLE() SET_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_AXISRAMLPEN)


#define __HAL_RCC_HPDMA1_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_HPDMA1LPEN)

#define __HAL_RCC_DMA2D_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DMA2DLPEN)

#define __HAL_RCC_FLASH_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_FLASHLPEN)

#if defined(JPEG)
#define __HAL_RCC_JPEG_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_JPEGLPEN)
#endif /* JPEG */

#define __HAL_RCC_FMC_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_FMCLPEN)

#define __HAL_RCC_XSPI1_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPI1LPEN)

#define __HAL_RCC_SDMMC1_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_SDMMC1LPEN)

#define __HAL_RCC_XSPI2_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPI2LPEN)

#define __HAL_RCC_XSPIM_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPIMLPEN)

#if defined(GFXMMU)
#define __HAL_RCC_GFXMMU_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_GFXMMULPEN)
#endif /* GFXMMU */

#if defined(GPU2D)
#define __HAL_RCC_GPU2D_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_GPU2DLPEN)
#endif /* GPU2D */

#define __HAL_RCC_DTCM1_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DTCM1LPEN)

#define __HAL_RCC_DTCM2_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DTCM2LPEN)

#define __HAL_RCC_ITCM_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_ITCMLPEN)

#define __HAL_RCC_AXISRAM_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_AXISRAMLPEN)

/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Sleep_Enable_Disable APB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM2LPEN)

#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM3LPEN)

#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM4LPEN)

#define __HAL_RCC_TIM5_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM5LPEN)

#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM6LPEN)

#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM7LPEN)

#define __HAL_RCC_TIM12_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM12LPEN)

#define __HAL_RCC_TIM13_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM13LPEN)

#define __HAL_RCC_TIM14_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM14LPEN)

#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE() SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_LPTIM1LPEN)

#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_WWDGLPEN)

#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPI2LPEN)

#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPI3LPEN)

#define __HAL_RCC_SPDIFRX_CLK_SLEEP_ENABLE() SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPDIFRXLPEN)

#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE() SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_USART2LPEN)

#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE() SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_USART3LPEN)

#define __HAL_RCC_UART4_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART4LPEN)

#define __HAL_RCC_UART5_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART5LPEN)

#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C1_I3C1LPEN)

#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C2LPEN)

#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C3LPEN)

#define __HAL_RCC_I3C1_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C1_I3C1LPEN)

#define __HAL_RCC_CEC_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_CECLPEN)

#define __HAL_RCC_UART7_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART7LPEN)

#define __HAL_RCC_UART8_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART8LPEN)

#define __HAL_RCC_CRS_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_CRSLPEN)

#define __HAL_RCC_MDIOS_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_MDIOSLPEN)

#define __HAL_RCC_FDCAN_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_FDCANLPEN)

#define __HAL_RCC_UCPD1_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_UCPD1LPEN)


#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM2LPEN)

#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM3LPEN)

#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM4LPEN)

#define __HAL_RCC_TIM5_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM5LPEN)

#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM6LPEN)

#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM7LPEN)

#define __HAL_RCC_TIM12_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM12LPEN)

#define __HAL_RCC_TIM13_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM13LPEN)

#define __HAL_RCC_TIM14_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM14LPEN)

#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_LPTIM1LPEN)

#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_WWDGLPEN)

#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPI2LPEN)

#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPI3LPEN)

#define __HAL_RCC_SPDIFRX_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPDIFRXLPEN)

#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_USART2LPEN)

#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_USART3LPEN)

#define __HAL_RCC_UART4_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART4LPEN)

#define __HAL_RCC_UART5_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART5LPEN)

#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C1_I3C1LPEN)

#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C2LPEN)

#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C3LPEN)

#define __HAL_RCC_I3C1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C1_I3C1LPEN)

#define __HAL_RCC_CEC_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_CECLPEN)

#define __HAL_RCC_UART7_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART7LPEN)

#define __HAL_RCC_UART8_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART8LPEN)

#define __HAL_RCC_CRS_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_CRSLPEN)

#define __HAL_RCC_MDIOS_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_MDIOSLPEN)

#define __HAL_RCC_FDCAN_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_FDCANLPEN)

#define __HAL_RCC_UCPD1_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_UCPD1LPEN)

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Sleep_Enable_Disable APB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM1LPEN)

#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_USART1LPEN)

#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI1LPEN)

#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI4LPEN)

#define __HAL_RCC_TIM15_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM15LPEN)

#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM16LPEN)

#define __HAL_RCC_TIM17_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM17LPEN)

#define __HAL_RCC_TIM9_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM9LPEN)

#define __HAL_RCC_SPI5_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI5LPEN)

#define __HAL_RCC_SAI1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SAI1LPEN)

#define __HAL_RCC_SAI2_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SAI2LPEN)


#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM1LPEN)

#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_USART1LPEN)

#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI1LPEN)

#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI4LPEN)

#define __HAL_RCC_TIM15_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM15LPEN)

#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM16LPEN)

#define __HAL_RCC_TIM17_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM17LPEN)

#define __HAL_RCC_TIM9_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM9LPEN)

#define __HAL_RCC_SPI5_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI5LPEN)

#define __HAL_RCC_SAI1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SAI1LPEN)

#define __HAL_RCC_SAI2_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SAI2LPEN)

/**
  * @}
  */

/** @defgroup RCC_APB4_Clock_Sleep_Enable_Disable APB4 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB4 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_SBS_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_SBSLPEN)

#define __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE() SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPUART1LPEN)

#define __HAL_RCC_SPI6_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_SPI6LPEN)

#define __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM2LPEN)

#define __HAL_RCC_LPTIM3_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM3LPEN)

#define __HAL_RCC_LPTIM4_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM4LPEN)

#define __HAL_RCC_LPTIM5_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM5LPEN)

#define __HAL_RCC_VREF_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_VREFLPEN)

#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_RTCAPBLPEN)

#define __HAL_RCC_DTS_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB4LPENR, RCC_APB4LPENR_DTSLPEN)


#define __HAL_RCC_SBS_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_SBSLPEN)

#define __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPUART1LPEN)

#define __HAL_RCC_SPI6_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_SPI6LPEN)

#define __HAL_RCC_LPTIM2_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM2LPEN)

#define __HAL_RCC_LPTIM3_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM3LPEN)

#define __HAL_RCC_LPTIM4_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM4LPEN)

#define __HAL_RCC_LPTIM5_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM5LPEN)

#define __HAL_RCC_VREF_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_VREFLPEN)

#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_RTCAPBLPEN)

#define __HAL_RCC_DTS_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB4LPENR, RCC_APB4LPENR_DTSLPEN)

/**
  * @}
  */

/** @defgroup RCC_APB5_Clock_Sleep_Enable_Disable APB5 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB5 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_LTDC_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB5LPENR, RCC_APB5LPENR_LTDCLPEN)

#define __HAL_RCC_DCMIPP_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB5LPENR, RCC_APB5LPENR_DCMIPPLPEN)

#define __HAL_RCC_GFXTIM_CLK_SLEEP_ENABLE()  SET_BIT(RCC->APB5LPENR, RCC_APB5LPENR_GFXTIMLPEN)


#define __HAL_RCC_LTDC_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB5LPENR, RCC_APB5LPENR_LTDCLPEN)

#define __HAL_RCC_DCMIPP_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB5LPENR, RCC_APB5LPENR_DCMIPPLPEN)

#define __HAL_RCC_GFXTIM_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->APB5LPENR, RCC_APB5LPENR_GFXTIMLPEN)

/**
  * @}
  */

/** @defgroup RCC_AHB1_Clock_Sleep_Enable_Disable_Status AHB1 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the AHB1 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_GPDMA1_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_GPDMA1LPEN) != 0U)

#define __HAL_RCC_ADC12_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ADC12LPEN) != 0U)
#if defined(ETH)
#define __HAL_RCC_ETH1MAC_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1MACLPEN) != 0U)

#define __HAL_RCC_ETH1TX_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1TXLPEN) != 0U)

#define __HAL_RCC_ETH1RX_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ETH1RXLPEN) != 0U)
#endif /* ETH */

#define __HAL_RCC_USB_OTG_HS_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_OTGHSLPEN) != 0U)

#define __HAL_RCC_USB_OTG_FS_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_OTGFSLPEN) != 0U)

#define __HAL_RCC_USBPHYC_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_USBPHYCLPEN) != 0U)

#define __HAL_RCC_ADF1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_ADF1LPEN) != 0U)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Clock_Sleep_Enable_Disable_Status AHB2 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the AHB2 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_PSSI_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_PSSILPEN) != 0U)

#define __HAL_RCC_SDMMC2_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SDMMC2LPEN) != 0U)

#define __HAL_RCC_CORDIC_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_CORDICLPEN) != 0U)

#define __HAL_RCC_SRAM1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SRAM1LPEN) != 0U)

#define __HAL_RCC_SRAM2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2LPENR, RCC_AHB2LPENR_SRAM2LPEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_AHB3_Clock_Sleep_Enable_Disable_Status AHB3 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the AHB3 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_RNG_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_RNGLPEN) != 0U)

#define __HAL_RCC_HASH_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_HASHLPEN) != 0U)

#if defined(CRYP)
#define __HAL_RCC_CRYP_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_CRYPLPEN) != 0U)
#endif /* CRYP */

#if defined(SAES)
#define __HAL_RCC_SAES_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_SAESLPEN) != 0U)
#endif /* SAES */

#if defined(PKA)
#define __HAL_RCC_PKA_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB3LPENR, RCC_AHB3LPENR_PKALPEN) != 0U)
#endif /* PKA */

/**
  * @}
  */

/** @defgroup RCC_AHB4_Clock_Sleep_Enable_Disable_Status AHB4 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the AHB4 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOALPEN) != 0U)

#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOBLPEN) != 0U)

#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOCLPEN) != 0U)

#define __HAL_RCC_GPIOD_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIODLPEN) != 0U)

#define __HAL_RCC_GPIOE_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOELPEN) != 0U)

#define __HAL_RCC_GPIOF_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOFLPEN) != 0U)

#define __HAL_RCC_GPIOG_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOGLPEN) != 0U)

#define __HAL_RCC_GPIOH_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOHLPEN) != 0U)

#define __HAL_RCC_GPIOM_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOMLPEN) != 0U)

#define __HAL_RCC_GPION_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIONLPEN) != 0U)

#define __HAL_RCC_GPIOO_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOOLPEN) != 0U)

#define __HAL_RCC_GPIOP_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_GPIOPLPEN) != 0U)

#define __HAL_RCC_CRC_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_CRCLPEN) != 0U)

#define __HAL_RCC_BKPRAM_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB4LPENR, RCC_AHB4LPENR_BKPRAMLPEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_AHB5_Clock_Sleep_Enable_Disable_Status AHB5 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the AHB5 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_HPDMA1_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_HPDMA1LPEN) != 0U)

#define __HAL_RCC_DMA2D_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DMA2DLPEN) != 0U)

#define __HAL_RCC_FLASH_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_FLASHLPEN) != 0U)

#if defined(JPEG)
#define __HAL_RCC_JPEG_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_JPEGLPEN) != 0U)
#endif /* JPEG */

#define __HAL_RCC_FMC_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_FMCLPEN) != 0U)

#define __HAL_RCC_XSPI1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPI1LPEN) != 0U)

#define __HAL_RCC_SDMMC1_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_SDMMC1LPEN) != 0U)

#define __HAL_RCC_XSPI2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPI2LPEN) != 0U)

#define __HAL_RCC_XSPIM_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_XSPIMLPEN) != 0U)

#if defined(GFXMMU)
#define __HAL_RCC_GFXMMU_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_GFXMMULPEN) != 0U)
#endif /* GFXMMU */

#if defined(GPU2D)
#define __HAL_RCC_GPU2D_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_GPU2DLPEN) != 0U)
#endif /* GPU2D */

#define __HAL_RCC_DTCM1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DTCM1LPEN) != 0U)

#define __HAL_RCC_DTCM2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_DTCM2LPEN) != 0U)

#define __HAL_RCC_ITCM_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_ITCMLPEN) != 0U)

#define __HAL_RCC_AXISRAM_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->AHB5LPENR, RCC_AHB5LPENR_AXISRAMLPEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Sleep_Enable_Disable_Status APB1 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the APB1 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_TIM2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM2LPEN) != 0U)

#define __HAL_RCC_TIM3_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM3LPEN) != 0U)

#define __HAL_RCC_TIM4_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM4LPEN) != 0U)

#define __HAL_RCC_TIM5_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM5LPEN) != 0U)

#define __HAL_RCC_TIM6_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM6LPEN) != 0U)

#define __HAL_RCC_TIM7_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM7LPEN) != 0U)

#define __HAL_RCC_TIM12_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM12LPEN) != 0U)

#define __HAL_RCC_TIM13_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM13LPEN) != 0U)

#define __HAL_RCC_TIM14_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_TIM14LPEN) != 0U)

#define __HAL_RCC_LPTIM1_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_LPTIM1LPEN) != 0U)

#define __HAL_RCC_WWDG_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_WWDGLPEN) != 0U)

#define __HAL_RCC_SPI2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPI2LPEN) != 0U)

#define __HAL_RCC_SPI3_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPI3LPEN) != 0U)

#define __HAL_RCC_SPDIFRX_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_SPDIFRXLPEN) != 0U)

#define __HAL_RCC_USART2_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_USART2LPEN) != 0U)

#define __HAL_RCC_USART3_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_USART3LPEN) != 0U)

#define __HAL_RCC_UART4_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART4LPEN) != 0U)

#define __HAL_RCC_UART5_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART5LPEN) != 0U)

#define __HAL_RCC_I2C1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C1_I3C1LPEN) != 0U)

#define __HAL_RCC_I2C2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C2LPEN) != 0U)

#define __HAL_RCC_I2C3_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C3LPEN) != 0U)

#define __HAL_RCC_I3C1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_I2C1_I3C1LPEN) != 0U)

#define __HAL_RCC_CEC_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_CECLPEN) != 0U)

#define __HAL_RCC_UART7_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART7LPEN) != 0U)

#define __HAL_RCC_UART8_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR1, RCC_APB1LPENR1_UART8LPEN) != 0U)

#define __HAL_RCC_CRS_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_CRSLPEN) != 0U)

#define __HAL_RCC_MDIOS_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_MDIOSLPEN) != 0U)

#define __HAL_RCC_FDCAN_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_FDCANLPEN) != 0U)

#define __HAL_RCC_UCPD1_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB1LPENR2, RCC_APB1LPENR2_UCPD1LPEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Sleep_Enable_Disable_Status APB2 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the APB2 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_TIM1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM1LPEN) != 0U)

#define __HAL_RCC_USART1_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_USART1LPEN) != 0U)

#define __HAL_RCC_SPI1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI1LPEN) != 0U)

#define __HAL_RCC_SPI4_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI4LPEN) != 0U)

#define __HAL_RCC_TIM15_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM15LPEN) != 0U)

#define __HAL_RCC_TIM16_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM16LPEN) != 0U)

#define __HAL_RCC_TIM17_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM17LPEN) != 0U)

#define __HAL_RCC_TIM9_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_TIM9LPEN) != 0U)

#define __HAL_RCC_SPI5_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SPI5LPEN) != 0U)

#define __HAL_RCC_SAI1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SAI1LPEN) != 0U)

#define __HAL_RCC_SAI2_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2LPENR, RCC_APB2LPENR_SAI2LPEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_APB4_Clock_Sleep_Enable_Disable_Status APB4 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the APB4 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_SBS_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_SBSLPEN) != 0U)

#define __HAL_RCC_LPUART1_IS_CLK_SLEEP_ENABLED() (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPUART1LPEN) != 0U)

#define __HAL_RCC_SPI6_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_SPI6LPEN) != 0U)

#define __HAL_RCC_LPTIM2_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM2LPEN) != 0U)

#define __HAL_RCC_LPTIM3_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM3LPEN) != 0U)

#define __HAL_RCC_LPTIM4_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM4LPEN) != 0U)

#define __HAL_RCC_LPTIM5_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_LPTIM5LPEN) != 0U)

#define __HAL_RCC_VREF_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_VREFLPEN) != 0U)

#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_RTCAPBLPEN) != 0U)

#define __HAL_RCC_DTS_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB4LPENR, RCC_APB4LPENR_DTSLPEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_APB5_Clock_Sleep_Enable_Disable_Status APB5 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the APB5 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */

#define __HAL_RCC_LTDC_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB5LPENR, RCC_APB5LPENR_LTDCLPEN) != 0U)

#define __HAL_RCC_DCMIPP_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB5LPENR, RCC_APB5LPENR_DCMIPPLPEN) != 0U)

#define __HAL_RCC_GFXTIM_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->APB5LPENR, RCC_APB5LPENR_GFXTIMLPEN) != 0U)

/**
  * @}
  */

/** @defgroup RCC_Osc_config Oscillators configuration
  * @{
  */

/** @brief  Macro to enable or disable the Internal High Speed oscillator (HSI).
  * @note     After enabling the HSI, the application software should wait on
  *           HSIRDY and HSIDIVF flags to be set indicating that the HSI clock is
  *           stable and the divider ready and that HSI clock can be used to clock
  *           the PLL and/or system clock.
  * @note     HSI can not be stopped if it is used directly or through the PLL
  *           as system clock. In this case, you have to select another source
  *           of the system clock then stop the HSI.
  * @note     The HSI is stopped by hardware when entering STOP and STANDBY modes.
  * @param    __STATE__ specifies the new state of the HSI.
  *           This parameter can be one of the following values:
  *            @arg @ref RCC_HSI_OFF turn OFF the HSI oscillator
  *            @arg @ref RCC_HSI_ON turn ON the HSI oscillator (divide it by 1 (default after reset))
  *            @arg @ref RCC_HSI_DIV2 turn ON the HSI oscillator and divide it by 2
  *            @arg @ref RCC_HSI_DIV4 turn ON the HSI oscillator and divide it by 4
  *            @arg @ref RCC_HSI_DIV8 turn ON the HSI oscillator and divide it by 8
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  */
#define __HAL_RCC_HSI_CONFIG(__STATE__) \
  MODIFY_REG(RCC->CR, RCC_CR_HSION | RCC_CR_HSIDIV , (uint32_t)(__STATE__))

/** @brief  Macro to get the HSI divider.
  * @retval The HSI divider. The returned value can be one
  *         of the following:
  *            - RCC_CR_HSIDIV_1  HSI oscillator divided by 1 (default after reset)
  *            - RCC_CR_HSIDIV_2  HSI oscillator divided by 2
  *            - RCC_CR_HSIDIV_4  HSI oscillator divided by 4
  *            - RCC_CR_HSIDIV_8  HSI oscillator divided by 8
  */
#define __HAL_RCC_GET_HSI_DIVIDER() ((uint32_t)(READ_BIT(RCC->CR, RCC_CR_HSIDIV)))

/** @brief  Macros to enable or disable the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after start-up
  *         from Reset, wakeup from STOP and STANDBY mode, or in case of failure
  *         of the HSE used directly or indirectly as system clock (if the Clock
  *         Security System CSS is enabled).
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  */
#define __HAL_RCC_HSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_HSION)

#define __HAL_RCC_HSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_HSION)

/** @brief  Macro to adjust the Internal High Speed 64MHz oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 0x7F.
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__) \
  MODIFY_REG(RCC->HSICFGR, RCC_HSICFGR_HSITRIM, (uint32_t)(__HSICALIBRATIONVALUE__) << RCC_HSICFGR_HSITRIM_Pos);

/**
  * @brief    Macros to enable or disable the force of the Internal High Speed oscillator (HSI)
  *           in STOP mode to be quickly available as kernel clock for some peripherals.
  * @note     Keeping the HSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the HSI start-up time.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSISTOP_ENABLE()     SET_BIT(RCC->CR, RCC_CR_HSIKERON)

#define __HAL_RCC_HSISTOP_DISABLE()    CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON)

/**
  * @brief  Macros to enable or disable the Internal oscillator (CSI).
  * @note     The CSI is stopped by hardware when entering STOP and STANDBY modes.
  *           It is used (enabled by hardware) as system clock source after
  *           start-up from Reset, wakeup from STOP and STANDBY mode, or in case
  *           of failure of the HSE used directly or indirectly as system clock
  *           (if the Clock Security System CSS is enabled).
  * @note     CSI can not be stopped if it is used as system clock source.
  *           In this case, you have to select another source of the system
  *           clock then stop the CSI.
  * @note     After enabling the CSI, the application software should wait on
  *           CSIRDY flag to be set indicating that CSI clock is stable and can
  *           be used as system clock source.
  * @note     When the CSI is stopped, CSIRDY flag goes low after 6 CSI oscillator
  *           clock cycles.
  */
#define __HAL_RCC_CSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_CSION)

#define __HAL_RCC_CSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_CSION)

/** @brief  Macro to adjust the Internal oscillator (CSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal CSI RC.
  * @param  __CSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_CSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 0x3F.
  * @retval None
  */
#define __HAL_RCC_CSI_CALIBRATIONVALUE_ADJUST(__CSICALIBRATIONVALUE__) \
  MODIFY_REG(RCC->CSICFGR, RCC_CSICFGR_CSITRIM, (uint32_t)(__CSICALIBRATIONVALUE__) << RCC_CSICFGR_CSITRIM_Pos);

/**
  * @brief    Macros to enable or disable the force of the Low-power Internal oscillator (CSI)
  *           in STOP mode to be quickly available as kernel clock for USARTs and I2Cs.
  * @note     Keeping the CSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the CSI start-up time.
  * @note     The enable of this function has not effect on the CSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_CSISTOP_ENABLE()     SET_BIT(RCC->CR, RCC_CR_CSIKERON)

#define __HAL_RCC_CSISTOP_DISABLE()    CLEAR_BIT(RCC->CR, RCC_CR_CSIKERON)

/**
  * @brief  Macro to enable or disable the Internal High Speed oscillator for USB (HSI48).
  * @note   After enabling the HSI48, the application software should wait on
  *         HSI48RDY flag to be set indicating that HSI48 clock is stable and can
  *         be used to clock the USB.
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_HSI48_ENABLE()    SET_BIT(RCC->CR, RCC_CR_HSI48ON);

#define __HAL_RCC_HSI48_DISABLE()   CLEAR_BIT(RCC->CR, RCC_CR_HSI48ON);

/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  */
#define __HAL_RCC_LSI_ENABLE()         SET_BIT(RCC->CSR, RCC_CSR_LSION)

#define __HAL_RCC_LSI_DISABLE()        CLEAR_BIT(RCC->CSR, RCC_CSR_LSION)

/**
  * @brief  Macro to configure the External High Speed oscillator (__HSE__).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   This function reset the CSSON bit, so if the clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  __STATE__ specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_OFF            turn OFF the HSE oscillator, HSERDY flag goes low after
  *                                        6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON             turn ON the HSE oscillator.
  *            @arg @ref RCC_HSE_BYPASS         HSE oscillator bypassed with external clock (analog).
  *            @arg @ref RCC_HSE_BYPASS_DIGITAL HSE oscillator bypassed with external digital clock.
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)                                \
  do {                                               \
    if ((__STATE__) == RCC_HSE_ON)                   \
    {                                                \
      SET_BIT(RCC->CR, RCC_CR_HSEON);                \
    }                                                \
    else if ((__STATE__) == RCC_HSE_OFF)             \
    {                                                \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEON);              \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEEXT);             \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);             \
    }                                                \
    else if ((__STATE__) == RCC_HSE_BYPASS)          \
    {                                                \
      SET_BIT(RCC->CR, RCC_CR_HSEBYP);               \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEEXT);             \
      SET_BIT(RCC->CR, RCC_CR_HSEON);                \
    }                                                \
    else if((__STATE__) == RCC_HSE_BYPASS_DIGITAL)   \
    {                                                \
      SET_BIT(RCC->CR, RCC_CR_HSEBYP);               \
      SET_BIT(RCC->CR, RCC_CR_HSEEXT);               \
      SET_BIT(RCC->CR, RCC_CR_HSEON);                \
    }                                                \
    else                                             \
    {                                                \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEON);              \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);             \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEEXT);             \
    }                                                \
  } while(0)

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   Transition LSE Bypass to LSE On and LSE On to LSE Bypass are not supported by this macro.
  *         User should request a transition to LSE Off first and then LSE On or LSE Bypass.
  * @note   The external input clock can have a frequency up to 1 MHz and be low swing (analog) or digital(*).
            A duty cycle close to 50% is recommended.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE (RCC_LSE_ON, RCC_LSE_BYPASS or RCC_LSE_BYPASS_DIGITAL), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @note   If the RTC is used, the LSE bypass must not be configured in digital mode but in low swing analog mode (*)
  * @param  __STATE__ specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF            turn OFF the LSE oscillator, LSERDY flag goes low after
  *                                        6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON             turn ON the LSE oscillator.
  *            @arg @ref RCC_LSE_BYPASS         LSE oscillator bypassed with external clock (analog).
  *            @arg @ref RCC_LSE_BYPASS_DIGITAL LSE oscillator bypassed with external digital clock.
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__) \
  do {                                               \
    if((__STATE__) == RCC_LSE_ON)                    \
    {                                                \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);            \
    }                                                \
    else if((__STATE__) == RCC_LSE_OFF)              \
    {                                                \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);          \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEEXT);         \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);         \
    }                                                \
    else if((__STATE__) == RCC_LSE_BYPASS)           \
    {                                                \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);           \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEEXT);         \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);            \
    }                                                \
    else if((__STATE__) == RCC_LSE_BYPASS_DIGITAL)   \
    {                                                \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);           \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEEXT);           \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);            \
    }                                                \
    else                                             \
    {                                                \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);          \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);         \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEEXT);         \
    }                                                \
  } while(0)

/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_config RCC_RTC_Clock_config
  * @{
  */

/** @brief  Macros to enable or disable the the RTC clock.
  * @note   These macros must be used only after the RTC clock source was selected.
  */
#define __HAL_RCC_RTC_ENABLE()         SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

#define __HAL_RCC_RTC_DISABLE()        CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

/** @brief  Macros to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it cannot be changed unless the
  *         Backup domain is reset using __HAL_RCC_BACKUPRESET_FORCE() and
  *         __HAL_RCC_BACKUPRESET_RELEASE() macros, or by a Power On Reset (POR).
  * @param  __RTC_CLKSOURCE__ specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RTCCLKSOURCE_LSE      LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI      LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV2  HSE divide by 2 selected as RTC clock up to
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV63 for HSE divide by 63
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *         RTC clock source).
  */
#define __HAL_RCC_RTC_CLKPRESCALER(__RTC_CLKSOURCE__) \
  ((((__RTC_CLKSOURCE__) & (0x3FU << 12U)) != 0U) ? \
   MODIFY_REG(RCC->CFGR, RCC_CFGR_RTCPRE, (((__RTC_CLKSOURCE__) & (~RCC_BDCR_RTCSEL)) >> 4U)) : \
   CLEAR_BIT(RCC->CFGR, RCC_CFGR_RTCPRE))

#define __HAL_RCC_RTC_CONFIG(__RTC_CLKSOURCE__) \
  do { \
    __HAL_RCC_RTC_CLKPRESCALER(__RTC_CLKSOURCE__); \
    SET_BIT(RCC->BDCR, ((__RTC_CLKSOURCE__) & RCC_BDCR_RTCSEL)); \
  } while(0)

#define __HAL_RCC_GET_RTC_SOURCE() \
  ((READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL) == RCC_BDCR_RTCSEL) ? \
   ((READ_BIT(RCC->CFGR, RCC_CFGR_RTCPRE) << 4U) | RCC_BDCR_RTCSEL) : READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL))

/** @brief  Macros to force or release the Vswitch backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_BDCR register.
  * @note   The BKPSRAM is not affected by this reset.
  */
#define __HAL_RCC_BACKUPRESET_FORCE()   SET_BIT(RCC->BDCR, RCC_BDCR_VSWRST)

#define __HAL_RCC_BACKUPRESET_RELEASE() CLEAR_BIT(RCC->BDCR, RCC_BDCR_VSWRST)

/**
  * @}
  */

/** @defgroup RCC_PLL_Clocks_config PLL Clocks configuration
  * @{
  */

/** @brief  Macro to configure the PLLs clock source.
  * @note   This function must be used only when all PLLs are disabled.
  * @param  __PLLSOURCE__ specifies the PLLs entry clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_CSI  CSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_NONE No oscillator clock selected as PLL clock entry (consumption gain)
  */
#define __HAL_RCC_PLLSOURCE_CONFIG(__PLLSOURCE__) \
  MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC, (__PLLSOURCE__))

/** @brief  Macro to get the oscillator used as PLL clock source.
  * @retval The oscillator used as PLL clock source.
  *         The returned value can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator is used as PLL clock source.
  *            @arg @ref RCC_PLLSOURCE_CSI  CSI oscillator is used as PLL clock source.
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator is used as PLL clock source.
  *            @arg @ref RCC_PLLSOURCE_NONE No oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE() \
  READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC)

/** @brief  Macros to enable or disable the PLL1.
  * @note   After enabling the main PLL, the application software should wait on
  *         PLL1RDY flag to be set indicating that PLL1 clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL can not be disabled if it is used as system clock source
  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_PLL1_ENABLE()         SET_BIT(RCC->CR, RCC_CR_PLL1ON)

#define __HAL_RCC_PLL1_DISABLE()        CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON)

/**
  * @brief  Enables or disables each clock output (PLL_P_CLK, PLL_Q_CLK, PLL_R_CLK, PLL_S_CLK, PLL_T_CLK)
  * @note   PLL_P_CLK cannot be stopped if used as System Clock
  * @param  __PLL_CLOCKOUT__ specifies the PLL clock to be output
  *          This parameter can be one or a combination of the following values:
  *            @arg @ref RCC_PLL_PCLK This clock is used to generate system clock up to 500MHz
  *            @arg @ref RCC_PLL_QCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_RCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_SCLK This clock is used to generate peripherals clock up to 500MHz
  *
  * @retval None
  */
#define __HAL_RCC_PLL1CLKOUT_ENABLE(__PLL_CLOCKOUT__)   SET_BIT(RCC->PLLCFGR, (__PLL_CLOCKOUT__))

#define __HAL_RCC_PLL1CLKOUT_DISABLE(__PLL_CLOCKOUT__)  CLEAR_BIT(RCC->PLLCFGR, (__PLL_CLOCKOUT__))

/**
  * @brief  Macro to get the PLL1 clock output enable status.
  * @param  __PLL_CLOCKOUT__ specifies the PLL1 clock to be output.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLL_PCLK This clock is used to generate system clock up to 500MHz
  *            @arg @ref RCC_PLL_QCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_RCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_SCLK This clock is used to generate peripherals clock up to 500MHz
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLL1CLKOUT_CONFIG(__PLL_CLOCKOUT__)   READ_BIT(RCC->PLLCFGR, (__PLL_CLOCKOUT__))

/**
  * @brief  Enables or disables Fractional Part Of The Multiplication Factor of PLL1 VCO
  * @note   Enabling/disabling  Fractional Part can be any time  without the need to stop the PLL1
  * @retval None
  */
#define __HAL_RCC_PLL1_FRACN_ENABLE()   SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN)

#define __HAL_RCC_PLL1_FRACN_DISABLE()  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN)

/**
  * @brief  Macro to configure the main PLL clock source, multiplication and division factors.
  * @note   This function must be used only when the main PLL is disabled.
  *
  * @param  __PLLSOURCE__ specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_HSI HSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_CSI CSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE HSE oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_NONE No oscillator clock selected as PLL clock entry (consumption gain)
  * @note   This clock source is common for PLL1, PLL2 and PLL3. It cannot be
  *         change on any PLL if another PLL is already enabled.
  *
  * @param  __PLL1M__ specifies the division factor for PLL VCO input clock
  *          This parameter must be a number between 1 and 63.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 1 to 16 MHz.
  *
  * @param  __PLL1N__ specifies the multiplication factor for PLL VCO output clock
  *          This parameter must be a number between 8 and 420.
  * @note   You have to set the PLLN parameter correctly to ensure that the VCO
  *         output frequency is between 150 and 420 MHz (when in medium VCO range) or
  *         between 128 and 560 MHZ (when in wide VCO range)
  *
  * @param  __PLL1P__ specifies the division factor for system  clock.
  *          This parameter must be a number between 1 and 128 (where odd numbers are not allowed)
  *
  * @param  __PLL1Q__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  *
  * @param  __PLL1R__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  *
  * @param  __PLL1S__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 8
  *
  *
  * @note   To insure an optimal behavior of the PLL when one of the post-divider (DIVP, DIVQ,
  *         DIVR, DIVS or DIVT) is not used, application shall clear the enable bit (PLL1yEN)
  *         and assign lowest possible value to  __PLL1P__, __PLL1Q__,  __PLL1R__,  __PLL1S__
  *         or __PLL1T__ parameters.
  * @retval None
  */

#define __HAL_RCC_PLL1_CONFIG(__PLLSOURCE__, __PLL1M__, __PLL1N__, __PLL1P__, __PLL1Q__, __PLL1R__, __PLL1S__) \
  do { \
    MODIFY_REG(RCC->PLLCKSELR, (RCC_PLLCKSELR_PLLSRC | RCC_PLLCKSELR_DIVM1) , ((__PLLSOURCE__) | ( (__PLL1M__) << RCC_PLLCKSELR_DIVM1_Pos)));  \
    WRITE_REG(RCC->PLL1DIVR1, ((((__PLL1N__) - 1U) & RCC_PLL1DIVR1_DIVN) | \
                               ((((__PLL1P__) - 1U) << RCC_PLL1DIVR1_DIVP_Pos) & RCC_PLL1DIVR1_DIVP) | \
                               ((((__PLL1Q__) - 1U) << RCC_PLL1DIVR1_DIVQ_Pos) & RCC_PLL1DIVR1_DIVQ) | \
                               ((((__PLL1R__) - 1U) << RCC_PLL1DIVR1_DIVR_Pos) & RCC_PLL1DIVR1_DIVR))); \
    MODIFY_REG(RCC->PLL1DIVR2, RCC_PLL1DIVR2_DIVS, \
               (((__PLL1S__) - 1U) & RCC_PLL1DIVR2_DIVS)); \
  } while(0)

/**
  * @brief  Macro to configures the PLL1 clock Fractional Part Of The Multiplication Factor
  *
  * @note   These bits can be written at any time, allowing dynamic fine-tuning of the PLL1 VCO
  *
  * @param  __PLL1FRACN__ specifies Fractional Part Of The Multiplication Factor for PLL1 VCO.
  *                       It should be a value between 0 and 8191
  * @note   Warning: The software has to set correctly these bits to insure that the VCO
  *                  output frequency is between its valid frequency range, which is:
  *                   128 to 560 MHz if PLL1VCOSEL = 0
  *                   150 to 420 MHz if PLL1VCOSEL = 1.
  *
  * @retval None
  */
#define  __HAL_RCC_PLL1_FRACN_CONFIG(__PLL1FRACN__) \
  MODIFY_REG(RCC->PLL1FRACR, RCC_PLL1FRACR_FRACN, (uint32_t)(__PLL1FRACN__) << RCC_PLL1FRACR_FRACN_Pos)

/** @brief  Macro to select the PLL1 reference frequency range.
  * @param  __PLL_VCOINPUT_RANGE__ specifies the PLL1 input frequency range
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLL_VCOINPUT_RANGE0 Range frequency is between 1 and 2 MHz
  *            @arg @ref RCC_PLL_VCOINPUT_RANGE1 Range frequency is between 2 and 4 MHz
  *            @arg @ref RCC_PLL_VCOINPUT_RANGE2 Range frequency is between 4 and 8 MHz
  *            @arg @ref RCC_PLL_VCOINPUT_RANGE3 Range frequency is between 8 and 16 MHz
  *
  * @retval None
  */
#define __HAL_RCC_PLL1_VCOINPUT_RANGE(__PLL_VCOINPUT_RANGE__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL1RGE, (__PLL_VCOINPUT_RANGE__))

/** @brief  Macro to select the PLL1 reference frequency range.
  * @param  __PLLVCORANGE__ specifies the PLL1 input frequency range
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLL_VCO_HIGH   Range frequency is between 128 to 560 MHz
  *            @arg @ref RCC_PLL_VCO_LOW    Range frequency is between 150 and 420 MHz
  * @retval None
  */
#define __HAL_RCC_PLL1_VCORANGE(__PLLVCORANGE__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL1VCOSEL, (__PLLVCORANGE__))

/** @brief  Macros to enable or disable PLL2.
  * @note   After enabling PLL2, the application software should wait on
  *         PLL2RDY flag to be set indicating that PLL2 clock is stable and can
  *         be used as kernel clock source.
  * @note   PLL2 is disabled by hardware when entering Stop and Standby modes.
  */
#define __HAL_RCC_PLL2_ENABLE()         SET_BIT(RCC->CR, RCC_CR_PLL2ON)
#define __HAL_RCC_PLL2_DISABLE()        CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON)

/**
  * @brief  Enables or disables each clock output (PLL2_P_CLK, PLL2_Q_CLK, PLL2_R_CLK, PLL2_S_CLK, PLL2_T_CLK)
  * @param  __PLL_CLOCKOUT__ Specifies the PLL2 clock(s) to be output
  *          This parameter can be one or a combination of the following values:
  *            @arg @ref RCC_PLL_PCLK This clock is used to generate system clock up to 500MHz
  *            @arg @ref RCC_PLL_QCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_RCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_SCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_TCLK This clock is used to generate peripherals clock up to 500MHz
  * @retval None
  */
#define __HAL_RCC_PLL2CLKOUT_ENABLE(__PLL_CLOCKOUT__)   SET_BIT(RCC->PLLCFGR, ((__PLL_CLOCKOUT__) << (RCC_PLLCFGR_PLL2PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos)))

#define __HAL_RCC_PLL2CLKOUT_DISABLE(__PLL_CLOCKOUT__)  CLEAR_BIT(RCC->PLLCFGR, ((__PLL_CLOCKOUT__) << (RCC_PLLCFGR_PLL2PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos)))

/**
  * @brief  Macro to get the PLL2 clock output enable status.
  * @param  __PLL_CLOCKOUT__ specifies the PLL2 clock to be output.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLL_PCLK This clock is used to generate system clock up to 500MHz
  *            @arg @ref RCC_PLL_QCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_RCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_SCLK This clock is used to generate peripherals clock up to 500MHz
  *            @arg @ref RCC_PLL_TCLK This clock is used to generate peripherals clock up to 500MHz
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLL2CLKOUT_CONFIG(__PLL_CLOCKOUT__)   (READ_BIT(RCC->PLLCFGR, ((__PLL_CLOCKOUT__) << (RCC_PLLCFGR_PLL2PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos))) \
                                                             >> (RCC_PLLCFGR_PLL2PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos))

/**
  * @brief  Enables or disables Fractional Part Of The Multiplication Factor of PLL2 VCO
  * @note   Enabling/disabling  Fractional Part can be any time  without the need to stop the PLL2
  * @retval None
  */
#define __HAL_RCC_PLL2_FRACN_ENABLE()   SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACEN)

#define __HAL_RCC_PLL2_FRACN_DISABLE()  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACEN)

/**
  * @brief  Macro to configures the PLL2  multiplication and division factors.
  * @note   This function must be used only when PLL2 is disabled.
  *
  * @param  __PLLSOURCE__ specifies the PLL2 clock source
  *          This parameter must be a value of @ref RCC_PLL_Clock_Source
  * @note   PLL2 clock source is addressing a common clock source for all PLLs.
  *
  * @param  __PLL2M__ specifies the division factor for PLL2 VCO input clock
  *          This parameter must be a number between 1 and 63.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 1 to 16 MHz.
  *
  * @param  __PLL2N__ specifies the multiplication factor for PLL2 VCO output clock
  *          This parameter must be a number between 4 and 512 or between 8 and 420(*).
  * @note   You have to set the PLL2N parameter correctly to ensure that the VCO
  *         output frequency is between 150 and 420 MHz (when in medium VCO range) or
  *         between 192 and 836 MHZ or between 128 and 560 MHZ(*) (when in wide VCO range)
  *
  * @param  __PLL2P__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128.
  *
  * @param  __PLL2Q__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128.
  *
  * @param  __PLL2R__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128.
  *
  * @param  __PLL2S__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 8.
  *
  * @param  __PLL2T__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 8.
  *
  * @note   To insure an optimal behavior of the PLL when one of the post-divider (DIVP, DIVQ,
  *         DIVR, DIVS and DIVT) is not used, application shall clear the enable bit (PLL2yEN)
  *         and assign lowest possible value to  __PLL2P__, __PLL2Q__, __PLL2R__, __PLL2S__
  *         or __PLL2T__ parameters.
  * @retval None
  */

#define __HAL_RCC_PLL2_CONFIG(__PLLSOURCE__, __PLL2M__, __PLL2N__, __PLL2P__, __PLL2Q__, __PLL2R__, __PLL2S__, __PLL2T__) \
  do{ \
    MODIFY_REG(RCC->PLLCKSELR, (RCC_PLLCKSELR_DIVM2 | RCC_PLLCKSELR_PLLSRC), \
               (((__PLL2M__) << RCC_PLLCKSELR_DIVM2_Pos) | (__PLLSOURCE__))); \
    WRITE_REG(RCC->PLL2DIVR1,  ((((__PLL2N__) - 1U) & RCC_PLL2DIVR1_DIVN) | \
                                ((((__PLL2P__) - 1U) << RCC_PLL2DIVR1_DIVP_Pos) & RCC_PLL2DIVR1_DIVP) | \
                                ((((__PLL2Q__) - 1U) << RCC_PLL2DIVR1_DIVQ_Pos) & RCC_PLL2DIVR1_DIVQ) | \
                                ((((__PLL2R__) - 1U) << RCC_PLL2DIVR1_DIVR_Pos) & RCC_PLL2DIVR1_DIVR))); \
    MODIFY_REG(RCC->PLL2DIVR2, (RCC_PLL2DIVR2_DIVS | RCC_PLL2DIVR2_DIVT) , \
               ((((__PLL2S__) - 1U) & RCC_PLL2DIVR2_DIVS) | \
                ((((__PLL2T__) - 1U) << RCC_PLL2DIVR2_DIVT_Pos) & RCC_PLL2DIVR2_DIVT))); \
  } while(0)

/**
  * @brief  Macro to configures PLL2 clock Fractional Part Of The Multiplication Factor
  *
  * @note   These bits can be written at any time, allowing dynamic fine-tuning of the PLL2 VCO
  *
  * @param  __PLL2FRACN__ Specifies Fractional Part Of The Multiplication factor for PLL2 VCO
  *                       It should be a value between 0 and 8191
  * @note   Warning: the software has to set correctly these bits to insure that the VCO
  *                  output frequency is between its valid frequency range, which is:
  *                  192 to 836 MHz or 128 to 560 MHz(*) if PLL2VCOSEL = 0
  *                  150 to 420 MHz if PLL2VCOSEL = 1.
  *
  *
  * @retval None
  */
#define  __HAL_RCC_PLL2_FRACN_CONFIG(__PLL2FRACN__) \
  MODIFY_REG(RCC->PLL2FRACR, RCC_PLL2FRACR_FRACN,((uint32_t)(__PLL2FRACN__) << RCC_PLL2FRACR_FRACN_Pos))

/** @brief  Macro to select the PLL2  reference frequency range.
  * @param  __PLL_VCOINPUT_RANGE__ specifies the PLL2 input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL_VCOINPUT_RANGE0: Range frequency is between 1 and 2 MHz
  *            @arg RCC_PLL_VCOINPUT_RANGE1: Range frequency is between 2 and 4 MHz
  *            @arg RCC_PLL_VCOINPUT_RANGE2: Range frequency is between 4 and 8 MHz
  *            @arg RCC_PLL_VCOINPUT_RANGE3: Range frequency is between 8 and 16 MHz
  * @retval None
  */
#define __HAL_RCC_PLL2_VCOINPUT_RANGE(__PLL_VCOINPUT_RANGE__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL2RGE, ((__PLL_VCOINPUT_RANGE__) << (RCC_PLLCFGR_PLL2RGE_Pos - RCC_PLLCFGR_PLL1RGE_Pos)))


/** @brief  Macro to select  the PLL2  reference frequency range.
  * @param  __PLLVCORANGE__ Specifies the PLL2 input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL_VCO_HIGH: Range frequency is between 192 and 836 MHz or between 128 to 560 MHz(*)
  *            @arg RCC_PLL_VCO_LOW: Range frequency is between 150 and 420 MHz
  *
  *
  * @retval None
  */
#define __HAL_RCC_PLL2_VCORANGE(__PLLVCORANGE__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL2VCOSEL, ((__PLLVCORANGE__) << (RCC_PLLCFGR_PLL2VCOSEL_Pos - RCC_PLLCFGR_PLL1VCOSEL_Pos)))

/** @brief  Macros to enable or disable the main PLL3.
  * @note   After enabling  PLL3, the application software should wait on
  *         PLL3RDY flag to be set indicating that PLL3 clock is stable and can
  *         be used as kernel clock source.
  * @note   PLL3 is disabled by hardware when entering Stop and Standby modes.
  */
#define __HAL_RCC_PLL3_ENABLE()         SET_BIT(RCC->CR, RCC_CR_PLL3ON)
#define __HAL_RCC_PLL3_DISABLE()        CLEAR_BIT(RCC->CR, RCC_CR_PLL3ON)

/**
  * @brief  Enables or disables Fractional Part Of The Multiplication Factor of PLL3 VCO
  * @note   Enabling/disabling  Fractional Part can be any time  without the need to stop the PLL3
  * @retval None
  */
#define __HAL_RCC_PLL3_FRACN_ENABLE()   SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3FRACEN)

#define __HAL_RCC_PLL3_FRACN_DISABLE()  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3FRACEN)

/**
  * @brief  Enables or disables each clock output (PLL3_P_CLK, PLL3_Q_CLK, PLL3_R_CLK, PLL3_S_CLK, PLL3_T_CLK)
  * @param  __PLL_CLOCKOUT__ Specifies the PLL3 clock(s) to be output
  *          This parameter can be one or a combination of the following values:
  *            @arg RCC_PLL_PCLK
  *            @arg RCC_PLL_QCLK
  *            @arg RCC_PLL_RCLK
  *            @arg RCC_PLL_SCLK
  * @retval SET / RESET
  */
#define __HAL_RCC_PLL3CLKOUT_ENABLE(__PLL_CLOCKOUT__)   SET_BIT(RCC->PLLCFGR, ((__PLL_CLOCKOUT__) << (RCC_PLLCFGR_PLL3PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos)))

#define __HAL_RCC_PLL3CLKOUT_DISABLE(__PLL_CLOCKOUT__)  CLEAR_BIT(RCC->PLLCFGR, ((__PLL_CLOCKOUT__) << (RCC_PLLCFGR_PLL3PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos)))

/**
  * @brief  Macro to get the PLL3 clock output enable status.
  * @param  __PLL_CLOCKOUT__ specifies the PLL3 clock(s) to be output.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL_PCLK
  *            @arg RCC_PLL_QCLK
  *            @arg RCC_PLL_RCLK
  *            @arg RCC_PLL_SCLK
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLL3CLKOUT_CONFIG(__PLL_CLOCKOUT__)   (READ_BIT(RCC->PLLCFGR, ((__PLL_CLOCKOUT__) << (RCC_PLLCFGR_PLL3PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos))) \
                                                             >> (RCC_PLLCFGR_PLL3PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos))

/**
  * @brief  Macro to configures the PLL3  multiplication and division factors.
  * @note   This function must be used only when PLL3 is disabled.
  *
  * @param  __PLLSOURCE__ specifies the PLL3 clock source
  *          This parameter must be a value of @ref RCC_PLL_Clock_Source
  * @note   PLL3 clock source is addressing a common clock source for all PLLs.
  *
  * @param  __PLL3M__ specifies the division factor for PLL3 VCO input clock
  *          This parameter must be a number between 1 and 63.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 1 to 16 MHz.
  *
  * @param  __PLL3N__ specifies the multiplication factor for PLL3 VCO output clock
  *          This parameter must be a number between 4 and 512.
  * @note   You have to set the PLL3N parameter correctly to ensure that the VCO
  *         output frequency is between 150 and 420 MHz (when in medium VCO range) or
  *         between 192 and 836 MHZ or between 128 and 560 MHZ(*) (when in wide VCO range)
  *
  * @param  __PLL3P__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 2 and 128 (where odd numbers not allowed)
  *
  * @param  __PLL3Q__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  *
  * @param  __PLL3R__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  *
  * @param  __PLL3S__ specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 8.
  *
  * @note   To insure an optimal behavior of the PLL when one of the post-divider (DIVP, DIVQ,
  *         DIVR, DIVS and DIVT) is not used, application shall clear the enable bit (PLL3yEN)
  *         and assign lowest possible value to  __PLL3P__, __PLL3Q__, __PLL3R__, __PLL3S__
  *         or __PLL3T__ parameters.
  */

#define __HAL_RCC_PLL3_CONFIG(__PLLSOURCE__, __PLL3M__, __PLL3N__, __PLL3P__, __PLL3Q__, __PLL3R__, __PLL3S__) \
  do{ \
    MODIFY_REG(RCC->PLLCKSELR, (RCC_PLLCKSELR_DIVM3 | RCC_PLLCKSELR_PLLSRC), \
               (((__PLL3M__) << RCC_PLLCKSELR_DIVM3_Pos) | (__PLLSOURCE__))); \
    WRITE_REG(RCC->PLL3DIVR1,  ((((__PLL3N__) - 1U) & RCC_PLL3DIVR1_DIVN) | \
                                ((((__PLL3P__) - 1U) << RCC_PLL3DIVR1_DIVP_Pos) & RCC_PLL3DIVR1_DIVP) | \
                                ((((__PLL3Q__) - 1U) << RCC_PLL3DIVR1_DIVQ_Pos) & RCC_PLL3DIVR1_DIVQ) | \
                                ((((__PLL3R__) - 1U) << RCC_PLL3DIVR1_DIVR_Pos) & RCC_PLL3DIVR1_DIVR))); \
    MODIFY_REG(RCC->PLL3DIVR2, RCC_PLL3DIVR2_DIVS, \
               (((__PLL3S__) - 1U) & RCC_PLL3DIVR2_DIVS)); \
  } while(0)

/**
  * @brief  Macro to configures  PLL3 clock Fractional Part of The Multiplication Factor
  *
  * @note   These bits can be written at any time, allowing dynamic fine-tuning of the PLL3 VCO
  *
  * @param  __PLL3FRACN__ specifies Fractional Part Of The Multiplication Factor for PLL3 VCO
  *                       It should be a value between 0 and 8191
  * @note   Warning: the software has to set correctly these bits to insure that the VCO
  *                  output frequency is between its valid frequency range, which is:
  *                  192 to 836 MHz or 128 to 560 MHz(*) if PLL3VCOSEL = 0
  *                  150 to 420 MHz if PLL3VCOSEL = 1.
  *
  *
  * @retval None
  */
#define  __HAL_RCC_PLL3_FRACN_CONFIG(__PLL3FRACN__) MODIFY_REG(RCC->PLL3FRACR, RCC_PLL3FRACR_FRACN, (uint32_t)(__PLL3FRACN__) << RCC_PLL3FRACR_FRACN_Pos)

/** @brief  Macro to select  the PLL3  reference frequency range.
  * @param  __PLL_VCOINPUT_RANGE__ specifies the PLL1 input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL_VCOINPUT_RANGE0: Range frequency is between 1 and 2 MHz
  *            @arg RCC_PLL_VCOINPUT_RANGE1: Range frequency is between 2 and 4 MHz
  *            @arg RCC_PLL_VCOINPUT_RANGE2: Range frequency is between 4 and 8 MHz
  *            @arg RCC_PLL_VCOINPUT_RANGE3: Range frequency is between 8 and 16 MHz
  * @retval None
  */
#define __HAL_RCC_PLL3_VCOINPUT_RANGE(__PLL_VCOINPUT_RANGE__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL3RGE, ((__PLL_VCOINPUT_RANGE__) << (RCC_PLLCFGR_PLL3RGE_Pos - RCC_PLLCFGR_PLL1RGE_Pos)))

/** @brief  Macro to select  the PLL3  reference frequency range.
  * @param  __PLLVCORANGE__ specifies the PLL1 input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLL_VCO_HIGH: Range frequency is between 192 and 836 MHz  or between 128 to 560 MHz(*)
  *            @arg RCC_PLL_VCO_HIGH: Range frequency is between 150 and 420 MHz
  *
  *
  * @retval None
  */
#define __HAL_RCC_PLL3_VCORANGE(__PLLVCORANGE__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL3VCOSEL, ((__PLLVCORANGE__) << (RCC_PLLCFGR_PLL3VCOSEL_Pos - RCC_PLLCFGR_PLL1VCOSEL_Pos)))

/**
  * @}
  */

/** @defgroup RCC_sysclk_config System clock source configuration
  * @{
  */

/**
  * @brief Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__ specifies the system clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_SYSCLKSOURCE_HSI    HSI oscillator is used as system clock source.
  *            @arg @ref RCC_SYSCLKSOURCE_CSI    CSI oscillator is used as system clock source.
  *            @arg @ref RCC_SYSCLKSOURCE_HSE    HSE oscillator is used as system clock source.
  *            @arg @ref RCC_SYSCLKSOURCE_PLLCLK PLL1 output is used as system clock source.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) \
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (__SYSCLKSOURCE__))

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock.
  *         The returned value can be one of the following values:
  *            @arg @ref RCC_SYSCLKSOURCE_STATUS_HSI    HSI used as system clock.
  *            @arg @ref RCC_SYSCLKSOURCE_STATUS_CSI    CSI used as system clock.
  *            @arg @ref RCC_SYSCLKSOURCE_STATUS_HSE    HSE used as system clock.
  *            @arg @ref RCC_SYSCLKSOURCE_STATUS_PLLCLK PLL1 used as system clock.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE() \
  READ_BIT(RCC->CFGR, RCC_CFGR_SWS)

/**
  * @}
  */

/** @addtogroup RCC_Osc_config
  * @{
  */

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   This parameter cannot be updated while LSE is ON.
  * @param  __LSEDRIVE__ specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW        LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW  LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH       LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) \
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, (uint32_t)(__LSEDRIVE__));
/**
  * @}
  */

/** @defgroup RCC_wkup_config Wakeup from stop configuration
  * @{
  */

/**
  * @brief  Macro to configure the wake up from stop clock.
  * @param  __STOPWUCLK__ specifies the clock source used after wake up from stop
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_HSI HSI selected as system clock source
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_CSI CSI selected as system clock source
  * @retval None
  */
#define __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(__STOPWUCLK__) \
  MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPWUCK, (__STOPWUCLK__))

/**
  * @brief  Macro to configure the Kernel wake up from stop clock.
  * @param  __STOPKERWUCLK__ specifies the Kernel clock source used after wake up from stop
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_STOP_KERWAKEUPCLOCK_HSI HSI selected as Kernel clock source
  *            @arg @ref RCC_STOP_KERWAKEUPCLOCK_CSI CSI selected as Kernel clock source
  * @retval None
  */
#define __HAL_RCC_KERWAKEUPSTOP_CLK_CONFIG(__STOPKERWUCLK__) \
  MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPKERWUCK, (__STOPKERWUCLK__))
/**
  * @}
  */

/** @defgroup RCC_MCOx_Clock_Config RCC MCOx Clock Config
  * @{
  */

/** @brief  Macro to configure the MCO1 clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_HSI       HSI clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_LSE       LSE clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_HSE       HSE clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_PLL1Q     PLL1Q clock selected as MCO1 source
  *            @arg @ref RCC_MCO1SOURCE_HSI48     HSI48 selected as MCO1 source
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1 up to RCC_MCODIV_15  : divider applied to MCO1 clock
  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO1 | RCC_CFGR_MCO1PRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

/** @brief  Macro to configure the MCO2 clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO2SOURCE_SYSCLK System clock (SYSCLK) selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_PLL2P  PLL2P clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_HSE    HSE clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_PLL1P  PLL1P clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_CSI    CSI clock selected as MCO2 source
  *            @arg @ref RCC_MCO2SOURCE_LSI    LSI clock selected as MCO2 source
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1 up to RCC_MCODIV_15  : divider applied to MCO2 clock
  */
#define __HAL_RCC_MCO2_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO2 | RCC_CFGR_MCO2PRE), ((__MCOCLKSOURCE__) | ((__MCODIV__) << 7U)));

/**
  * @}
  */

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */
/** @brief  Enable RCC interrupt.
  * @param  __INTERRUPT__ specifies the RCC interrupt source(s) to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt
  *            @arg @ref RCC_IT_CSIRDY   CSI ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt
  *            @arg @ref RCC_IT_PLL1RDY  PLL1 ready interrupt
  *            @arg @ref RCC_IT_PLL2RDY  PLL2 ready interrupt
  *            @arg @ref RCC_IT_PLL3RDY  PLL3 ready interrupt
  *            @arg @ref RCC_IT_LSECSS   Clock security system interrupt
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Disable RCC interrupt.
  * @param  __INTERRUPT__ specifies the RCC interrupt source(s) to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt
  *            @arg @ref RCC_IT_CSIRDY   CSI ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt
  *            @arg @ref RCC_IT_PLL1RDY  PLL1 ready interrupt
  *            @arg @ref RCC_IT_PLL2RDY  PLL2 ready interrupt
  *            @arg @ref RCC_IT_PLL3RDY  PLL3 ready interrupt
  *            @arg @ref RCC_IT_LSECSS   LSE clock security system interrupt
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear the RCC's interrupt pending bits
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt
  *            @arg @ref RCC_IT_CSIRDY   CSI ready interrupt
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt
  *            @arg @ref RCC_IT_PLL1RDY  PLL1 ready interrupt
  *            @arg @ref RCC_IT_PLL2RDY  PLL2 ready interrupt
  *            @arg @ref RCC_IT_PLL3RDY  PLL3 ready interrupt
  *            @arg @ref RCC_IT_LSECSS   LSE clock security system interrupt
  *            @arg @ref RCC_IT_HSECSS   HSE clock security interrupt
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) WRITE_REG(RCC->CICR, (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__ specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_LSIRDY   LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt
  *            @arg @ref RCC_IT_CSIRDY   CSI ready interrupt
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt
  *            @arg @ref RCC_IT_PLL1RDY  PLL1 ready interrupt
  *            @arg @ref RCC_IT_PLL2RDY  PLL2 ready interrupt
  *            @arg @ref RCC_IT_PLL3RDY  PLL3 ready interrupt
  *            @arg @ref RCC_IT_LSECSS   LSE clock security system interrupt
  *            @arg @ref RCC_IT_HSECSS   HSE clock security interrupt
  * @retval The pending state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) (READ_BIT(RCC->CIFR, (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: RCC_FLAG_BORRST, RCC_FLAG_PINRST, RCC_FLAG_PORRST,
  *        RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST and RCC_FLAG_LPWRRST.
 */
#define __HAL_RCC_CLEAR_RESET_FLAGS() SET_BIT(RCC->RSR, RCC_RSR_RMVF)

/** @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_HSIRDY   HSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSIDIV   HSI divider ready
  *            @arg @ref RCC_FLAG_CSIRDY   CSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSI48RDY HSI48 clock ready
  *            @arg @ref RCC_FLAG_HSERDY   HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_PLL1RDY  PLL1 clock ready
  *            @arg @ref RCC_FLAG_PLL2RDY  PLL2 clock ready
  *            @arg @ref RCC_FLAG_PLL3RDY  PLL3 clock ready
  *            @arg @ref RCC_FLAG_LSERDY   LSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSECSSD  Clock security system failure on LSE oscillator detection
  *            @arg @ref RCC_FLAG_LSIRDY   LSI oscillator clock ready
  *            @arg @ref RCC_FLAG_BORRST   BOR reset
  *            @arg @ref RCC_FLAG_PINRST   Pin reset
  *            @arg @ref RCC_FLAG_PORRST   Power-on reset
  *            @arg @ref RCC_FLAG_SFTRST   Software reset
  *            @arg @ref RCC_FLAG_IWDGRST  Independent Watchdog reset
  *            @arg @ref RCC_FLAG_WWDGRST  Window Watchdog reset
  *            @arg @ref RCC_FLAG_LPWRRST  Low Power reset
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5U) == RCC_CR_REG_INDEX)        ? RCC->CR :                  \
                                         ((((__FLAG__) >> 5U) == RCC_BDCR_REG_INDEX)     ? RCC->BDCR :                \
                                          ((((__FLAG__) >> 5U) == RCC_CSR_REG_INDEX)     ? RCC->CSR :                 \
                                           ((((__FLAG__) >> 5U) == RCC_RSR_REG_INDEX)    ? RCC->RSR : RCC->CIFR)))) & \
                                        (1UL << ((__FLAG__) & RCC_FLAG_MASK))) != 0U) ? 1U : 0U)

/**
  * @}
  */

/**
  * @}
  */

/* Include RCC HAL Extension module */
#include "stm32h7rsxx_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions
  * @{
 */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions  ************************************************/
void     HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void     HAL_RCC_EnableCSS(void);
void     HAL_RCC_DisableCSS(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
uint32_t HAL_RCC_GetPCLK4Freq(void);
uint32_t HAL_RCC_GetPCLK5Freq(void);
uint32_t HAL_RCC_GetPLL1PFreq(void);
uint32_t HAL_RCC_GetPLL1QFreq(void);
uint32_t HAL_RCC_GetPLL1RFreq(void);
uint32_t HAL_RCC_GetPLL1SFreq(void);
uint32_t HAL_RCC_GetPLL2PFreq(void);
uint32_t HAL_RCC_GetPLL2QFreq(void);
uint32_t HAL_RCC_GetPLL2RFreq(void);
uint32_t HAL_RCC_GetPLL2SFreq(void);
uint32_t HAL_RCC_GetPLL2TFreq(void);
uint32_t HAL_RCC_GetPLL3PFreq(void);
uint32_t HAL_RCC_GetPLL3QFreq(void);
uint32_t HAL_RCC_GetPLL3RFreq(void);
uint32_t HAL_RCC_GetPLL3SFreq(void);
void     HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void     HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);
/* CSS NMI IRQ handler */
void     HAL_RCC_NMI_IRQHandler(void);
/* User callbacks in non blocking mode (IT mode) */
void     HAL_RCC_HSECSSCallback(void);
void     HAL_RCC_LSECSSCallback(void);
uint32_t          HAL_RCC_GetResetSource(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants
  * @{
  */
#define RCC_PLL_VCOINPUTFREQ_MAX            16000000U /* Maximum VCO input frequency is 16 MHz */
#define RCC_PLL_VCOINPUTFREQ_MIN             1000000U /* Minimum VCO input frequency is 1 MHz */

#define RCC_PLL_TIMEOUT_VALUE         (50U)    /* 50 ms */

/* Defines used for Flags */
#define RCC_CR_REG_INDEX              1U
#define RCC_BDCR_REG_INDEX            2U
#define RCC_CSR_REG_INDEX             3U
#define RCC_RSR_REG_INDEX             4U

#define RCC_FLAG_MASK             0x0000001FU

#define RCC_LSE_TIMEOUT_VALUE         LSE_STARTUP_TIMEOUT

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */

/** @defgroup RCC_IS_RCC_Definitions RCC Private macros to check input parameters
  * @{
  */

#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_CSI) == RCC_OSCILLATORTYPE_CSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI48) == RCC_OSCILLATORTYPE_HSI48))

#define IS_RCC_HSE(__HSE__) (((__HSE__) == RCC_HSE_OFF)    || ((__HSE__) == RCC_HSE_ON) || \
                             ((__HSE__) == RCC_HSE_BYPASS) || ((__HSE__) == RCC_HSE_BYPASS_DIGITAL))

#define IS_RCC_LSE(__LSE__) (((__LSE__) == RCC_LSE_OFF)    || ((__LSE__) == RCC_LSE_ON) || \
                             ((__LSE__) == RCC_LSE_BYPASS) || ((__LSE__) == RCC_LSE_BYPASS_DIGITAL))

#define IS_RCC_HSI(__HSI__) (((__HSI__) == RCC_HSI_OFF)    || ((__HSI__) == RCC_HSI_ON))

#define IS_RCC_HSIDIV(__HSIDIV__) (((__HSIDIV__) == RCC_HSI_DIV1) || ((__HSIDIV__) == RCC_HSI_DIV2) || \
                                   ((__HSIDIV__) == RCC_HSI_DIV4) || ((__HSIDIV__) == RCC_HSI_DIV8))

#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) \
                                                 <= (uint32_t)( RCC_HSICFGR_HSITRIM  >>  RCC_HSICFGR_HSITRIM_Pos))

#define IS_RCC_HSI48(__HSI48__) (((__HSI48__) == RCC_HSI48_OFF) || ((__HSI48__) == RCC_HSI48_ON))

#define IS_RCC_LSI(__LSI__) (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))

#define IS_RCC_CSI(__CSI__) (((__CSI__) == RCC_CSI_OFF) || ((__CSI__) == RCC_CSI_ON))

#define IS_RCC_CSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) \
                                                 <= (uint32_t)( RCC_CSICFGR_CSITRIM  >>  RCC_CSICFGR_CSITRIM_Pos))

#define IS_RCC_PLL(__PLL__) (((__PLL__) == RCC_PLL_NONE) || ((__PLL__) == RCC_PLL_OFF) || \
                             ((__PLL__) == RCC_PLL_ON))

#define IS_RCC_PLLSOURCE(__SOURCE__) (((__SOURCE__) == RCC_PLLSOURCE_HSI) || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_CSI) || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_HSE))

#define IS_RCC_PLLM_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 63U))

#define IS_RCC_PLLN_VALUE(__VALUE__) ((8U <= (__VALUE__)) && ((__VALUE__) <= 420U))

#define IS_RCC_PLLP_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 128U))

#define IS_RCC_PLLQ_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 128U))

#define IS_RCC_PLLR_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 128U))

#define IS_RCC_PLLS_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 8U))

#define IS_RCC_PLLT_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 8U))

#define IS_RCC_PLL_VCOINPUTFREQ(__VALUE__)  ((RCC_PLL_VCOINPUTFREQ_MIN <= (__VALUE__)) &&\
                                             ((__VALUE__) <= RCC_PLL_VCOINPUTFREQ_MAX))

#define IS_RCC_PLLFRACN_VALUE(__VALUE__) ((__VALUE__) <= 8191U)

#define IS_RCC_PLLCLOCKOUT_VALUE(__VALUE__) (((__VALUE__) == RCC_PLL_PCLK) || \
                                             ((__VALUE__) == RCC_PLL_QCLK) || \
                                             ((__VALUE__) == RCC_PLL_RCLK) || \
                                             ((__VALUE__) == RCC_PLL_SCLK))

#define IS_RCC_PLLRGE_VALUE(__VALUE__) (((__VALUE__) == RCC_PLL_VCOINPUT_RANGE0)  || \
                                        ((__VALUE__) == RCC_PLL_VCOINPUT_RANGE1)  || \
                                        ((__VALUE__) == RCC_PLL_VCOINPUT_RANGE2)  || \
                                        ((__VALUE__) == RCC_PLL_VCOINPUT_RANGE3))

#define IS_RCC_PLLVCO_VALUE(__VALUE__) (((__VALUE__) == RCC_PLL_VCO_HIGH)  || \
                                        ((__VALUE__) == RCC_PLL_VCO_LOW))

#define IS_RCC_CLOCKTYPE(__CLK__) ((1U <= (__CLK__)) && ((__CLK__) <= 63U))

#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_CSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK))

#define IS_RCC_SYSCLK(__SYSCLK__) (((__SYSCLK__) == RCC_SYSCLK_DIV1)   || ((__SYSCLK__) == RCC_SYSCLK_DIV2)   || \
                                   ((__SYSCLK__) == RCC_SYSCLK_DIV4)   || ((__SYSCLK__) == RCC_SYSCLK_DIV8)   || \
                                   ((__SYSCLK__) == RCC_SYSCLK_DIV16)  || ((__SYSCLK__) == RCC_SYSCLK_DIV64)  || \
                                   ((__SYSCLK__) == RCC_SYSCLK_DIV128) || ((__SYSCLK__) == RCC_SYSCLK_DIV256) || \
                                   ((__SYSCLK__) == RCC_SYSCLK_DIV512))

#define IS_RCC_HCLK(__HCLK__) (((__HCLK__) == RCC_HCLK_DIV1)   || ((__HCLK__) == RCC_HCLK_DIV2)   || \
                               ((__HCLK__) == RCC_HCLK_DIV4)   || ((__HCLK__) == RCC_HCLK_DIV8)   || \
                               ((__HCLK__) == RCC_HCLK_DIV16)  || ((__HCLK__) == RCC_HCLK_DIV64)  || \
                               ((__HCLK__) == RCC_HCLK_DIV128) || ((__HCLK__) == RCC_HCLK_DIV256) || \
                               ((__HCLK__) == RCC_HCLK_DIV512))

#define IS_RCC_PCLK1(__PCLK1__) (((__PCLK1__) == RCC_APB1_DIV1) || ((__PCLK1__) == RCC_APB1_DIV2) || \
                                 ((__PCLK1__) == RCC_APB1_DIV4) || ((__PCLK1__) == RCC_APB1_DIV8) || \
                                 ((__PCLK1__) == RCC_APB1_DIV16))

#define IS_RCC_PCLK2(__PCLK2__) (((__PCLK2__) == RCC_APB2_DIV1) || ((__PCLK2__) == RCC_APB2_DIV2) || \
                                 ((__PCLK2__) == RCC_APB2_DIV4) || ((__PCLK2__) == RCC_APB2_DIV8) || \
                                 ((__PCLK2__) == RCC_APB2_DIV16))

#define IS_RCC_PCLK4(__PCLK4__) (((__PCLK4__) == RCC_APB4_DIV1) || ((__PCLK4__) == RCC_APB4_DIV2) || \
                                 ((__PCLK4__) == RCC_APB4_DIV4) || ((__PCLK4__) == RCC_APB4_DIV8) || \
                                 ((__PCLK4__) == RCC_APB4_DIV16))

#define IS_RCC_PCLK5(__PCLK5__) (((__PCLK5__) == RCC_APB5_DIV1) || ((__PCLK5__) == RCC_APB5_DIV2) || \
                                 ((__PCLK5__) == RCC_APB5_DIV4) || ((__PCLK5__) == RCC_APB5_DIV8) || \
                                 ((__PCLK5__) == RCC_APB5_DIV16))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)       || ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)       || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV2)  || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV3)  || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV4)  || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV5)  || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV6)  || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV7)  || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV8)  || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV9)  || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV10) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV11) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV12) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV13) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV14) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV15) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV16) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV17) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV18) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV19) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV20) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV21) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV22) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV23) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV24) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV25) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV26) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV27) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV28) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV29) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV30) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV31) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV33) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV34) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV35) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV36) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV37) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV38) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV39) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV40) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV41) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV42) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV43) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV44) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV45) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV46) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV47) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV48) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV49) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV50) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV51) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV52) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV53) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV54) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV55) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV56) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV57) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV58) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV59) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV60) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV61) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV62) || ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV63) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_DISABLE))

#define IS_RCC_MCO(__MCOX__) (((__MCOX__) == RCC_MCO1_PA8) || \
                              ((__MCOX__) == RCC_MCO2_PC9))

#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO1SOURCE_HSI) || ((__SOURCE__) == RCC_MCO1SOURCE_LSE)   || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSE) || ((__SOURCE__) == RCC_MCO1SOURCE_PLL1Q) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSI48))

#define IS_RCC_MCO2SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO2SOURCE_SYSCLK) || ((__SOURCE__) == RCC_MCO2SOURCE_PLL2P) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_HSE)    || ((__SOURCE__) == RCC_MCO2SOURCE_PLL1P) || \
                                       ((__SOURCE__) == RCC_MCO2SOURCE_CSI)    || ((__SOURCE__) == RCC_MCO2SOURCE_LSI))

#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_NONE) || ((__DIV__) == RCC_MCODIV_1)  || \
                                ((__DIV__) == RCC_MCODIV_2)    || ((__DIV__) == RCC_MCODIV_3)  || \
                                ((__DIV__) == RCC_MCODIV_4)    || ((__DIV__) == RCC_MCODIV_5)  || \
                                ((__DIV__) == RCC_MCODIV_6)    || ((__DIV__) == RCC_MCODIV_7)  || \
                                ((__DIV__) == RCC_MCODIV_8)    || ((__DIV__) == RCC_MCODIV_9)  || \
                                ((__DIV__) == RCC_MCODIV_10)   || ((__DIV__) == RCC_MCODIV_11) || \
                                ((__DIV__) == RCC_MCODIV_12)   || ((__DIV__) == RCC_MCODIV_13) || \
                                ((__DIV__) == RCC_MCODIV_14)   || ((__DIV__) == RCC_MCODIV_15))

#define IS_RCC_LSE_DRIVE(__DRIVE__)             (((__DRIVE__) == RCC_LSEDRIVE_LOW)        || \
                                                 ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                                 ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                                 ((__DRIVE__) == RCC_LSEDRIVE_HIGH))

#define IS_RCC_FLAG(__FLAG__) (((__FLAG__) == RCC_FLAG_HSIRDY)  || ((__FLAG__) == RCC_FLAG_HSIDIV )  || \
                               ((__FLAG__) == RCC_FLAG_CSIRDY)  || ((__FLAG__) == RCC_FLAG_HSI48RDY) || \
                               ((__FLAG__) == RCC_FLAG_HSERDY)  || ((__FLAG__) == RCC_FLAG_PLL1RDY)  || \
                               ((__FLAG__) == RCC_FLAG_PLL2RDY) || ((__FLAG__) == RCC_FLAG_PLL3RDY)  || \
                               ((__FLAG__) == RCC_FLAG_LSERDY)  || ((__FLAG__) == RCC_FLAG_LSECSSD)  || \
                               ((__FLAG__) == RCC_FLAG_LSIRDY)  || ((__FLAG__) == RCC_FLAG_BORRST)   || \
                               ((__FLAG__) == RCC_FLAG_PINRST)  || ((__FLAG__) == RCC_FLAG_PORRST)   || \
                               ((__FLAG__) == RCC_FLAG_SFTRST)  || ((__FLAG__) == RCC_FLAG_IWDGRST)  || \
                               ((__FLAG__) == RCC_FLAG_WWDGRST) || ((__FLAG__) == RCC_FLAG_LPWRRST))

#define IS_RCC_HSICALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= 0x7FU)

#define IS_RCC_CSICALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= 0x3FU)

#define IS_RCC_STOP_WAKEUPCLOCK(__SOURCE__) (((__SOURCE__) == RCC_STOP_WAKEUPCLOCK_CSI) || \
                                             ((__SOURCE__) == RCC_STOP_WAKEUPCLOCK_HSI))

#define IS_RCC_STOP_KERWAKEUPCLOCK(__SOURCE__) (((__SOURCE__) == RCC_STOP_KERWAKEUPCLOCK_CSI) || \
                                                ((__SOURCE__) == RCC_STOP_KERWAKEUPCLOCK_HSI))
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_RCC_H */
