/**
  ******************************************************************************
  * @file    stm32wlxx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WLxx_HAL_RCC_H
#define STM32WLxx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_def.h"
#include "stm32wlxx_ll_rcc.h"
#include "stm32wlxx_ll_bus.h"


/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @addtogroup RCC_Private_Constants
  * @{
  */
/* Defines used for Flags */
#define CR_REG_INDEX              1U
#define BDCR_REG_INDEX            2U
#define CSR_REG_INDEX             3U
#define REG_INDEX_POS             5U

#define RCC_FLAG_MASK             0x1FU

/** @defgroup RCC_Timeout_Value Timeout Values
  * @{
  */
#define RCC_DBP_TIMEOUT_VALUE          2U                   /*!< 2 ms (minimum Tick + 1)  */
#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT  /*!< LSE timeout in ms        */
#define PLL_TIMEOUT_VALUE              10U                 /*!< 10 ms (minimum Tick + 1)  */
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */

#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__)                                     \
  (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                               || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE)   == RCC_OSCILLATORTYPE_HSE)   || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI)   == RCC_OSCILLATORTYPE_HSI)   || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_MSI)   == RCC_OSCILLATORTYPE_MSI)   || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI)   == RCC_OSCILLATORTYPE_LSI)   || \
   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE)   == RCC_OSCILLATORTYPE_LSE))


#define IS_RCC_HSE(__HSE__)  (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON) || \
                              ((__HSE__) == RCC_HSE_BYPASS_PWR))

#define IS_RCC_HSEDIV(__HSEDIV__)  (((__HSEDIV__) == RCC_HSE_DIV1) || ((__HSEDIV__) == RCC_HSE_DIV2))

#define IS_RCC_LSE(__LSE__)  (((__LSE__) == RCC_LSE_OFF)                                              || \
                              ((__LSE__) == RCC_LSE_ON)     || ((__LSE__) == RCC_LSE_ON_RTC_ONLY)     || \
                              ((__LSE__) == RCC_LSE_BYPASS) || ((__LSE__) == RCC_LSE_BYPASS_RTC_ONLY))

#define IS_RCC_HSI(__HSI__)  (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))

#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= (uint32_t)127U)

#define IS_RCC_LSI(__LSI__)  (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))

#define IS_RCC_LSIDIV(__LSIDIV__)  (((__LSIDIV__) == RCC_LSI_DIV1) || ((__LSIDIV__) == RCC_LSI_DIV128))

#define IS_RCC_MSI(__MSI__)  (((__MSI__) == RCC_MSI_OFF) || ((__MSI__) == RCC_MSI_ON))

#define IS_RCC_MSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= (uint32_t)255U)

#define IS_RCC_PLL(__PLL__) (((__PLL__) == RCC_PLL_NONE) ||((__PLL__) == RCC_PLL_OFF) || \
                             ((__PLL__) == RCC_PLL_ON))

#define IS_RCC_PLLSOURCE(__SOURCE__) (((__SOURCE__) == RCC_PLLSOURCE_NONE) || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_MSI)  || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_HSI)  || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_HSE))

#define IS_RCC_PLLM_VALUE(__VALUE__) (((__VALUE__) == RCC_PLLM_DIV1)  || \
                                      ((__VALUE__) == RCC_PLLM_DIV2)  || \
                                      ((__VALUE__) == RCC_PLLM_DIV3)  || \
                                      ((__VALUE__) == RCC_PLLM_DIV4)  || \
                                      ((__VALUE__) == RCC_PLLM_DIV5)  || \
                                      ((__VALUE__) == RCC_PLLM_DIV6)  || \
                                      ((__VALUE__) == RCC_PLLM_DIV7)  || \
                                      ((__VALUE__) == RCC_PLLM_DIV8))

#define IS_RCC_PLLN_VALUE(__VALUE__) ((6U <= (__VALUE__)) && ((__VALUE__) <= 127U))

#define IS_RCC_PLLP_VALUE(__VALUE__) ((RCC_PLLP_DIV2 <= (__VALUE__)) && ((__VALUE__) <= RCC_PLLP_DIV32))

#define IS_RCC_PLLQ_VALUE(__VALUE__) ((RCC_PLLQ_DIV2 <= (__VALUE__)) && ((__VALUE__) <= RCC_PLLQ_DIV8))

#define IS_RCC_PLLR_VALUE(__VALUE__) ((RCC_PLLR_DIV2 <= (__VALUE__)) && ((__VALUE__) <= RCC_PLLR_DIV8))

#define IS_RCC_MSI_CLOCK_RANGE(__RANGE__) (((__RANGE__) == RCC_MSIRANGE_0)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_1)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_2)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_3)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_4)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_5)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_6)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_7)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_8)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_9)  || \
                                           ((__RANGE__) == RCC_MSIRANGE_10) || \
                                           ((__RANGE__) == RCC_MSIRANGE_11))

#if defined(DUAL_CORE)
#define IS_RCC_CLOCKTYPE(__CLK__)   ((1U <= (__CLK__)) && ((__CLK__) <= (RCC_CLOCKTYPE_SYSCLK | \
                                                                         RCC_CLOCKTYPE_HCLK   | \
                                                                         RCC_CLOCKTYPE_PCLK1  | \
                                                                         RCC_CLOCKTYPE_PCLK2  | \
                                                                         RCC_CLOCKTYPE_HCLK2  | \
                                                                         RCC_CLOCKTYPE_HCLK3)))
#else
#define IS_RCC_CLOCKTYPE(__CLK__)   ((1U <= (__CLK__)) && ((__CLK__) <= (RCC_CLOCKTYPE_SYSCLK | \
                                                                         RCC_CLOCKTYPE_HCLK   | \
                                                                         RCC_CLOCKTYPE_PCLK1  | \
                                                                         RCC_CLOCKTYPE_PCLK2  | \
                                                                         RCC_CLOCKTYPE_HCLK3)))
#endif /* DUAL_CORE */

#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_MSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK))

#define IS_RCC_HCLKx(__HCLK__) (((__HCLK__) == RCC_SYSCLK_DIV1)   || ((__HCLK__) == RCC_SYSCLK_DIV2)   || \
                                ((__HCLK__) == RCC_SYSCLK_DIV3)   || ((__HCLK__) == RCC_SYSCLK_DIV4)   || \
                                ((__HCLK__) == RCC_SYSCLK_DIV5)   || ((__HCLK__) == RCC_SYSCLK_DIV6)   || \
                                ((__HCLK__) == RCC_SYSCLK_DIV8)   || ((__HCLK__) == RCC_SYSCLK_DIV10)  || \
                                ((__HCLK__) == RCC_SYSCLK_DIV16)  || ((__HCLK__) == RCC_SYSCLK_DIV32)  || \
                                ((__HCLK__) == RCC_SYSCLK_DIV64)  || ((__HCLK__) == RCC_SYSCLK_DIV128) || \
                                ((__HCLK__) == RCC_SYSCLK_DIV256) || ((__HCLK__) == RCC_SYSCLK_DIV512))

#define IS_RCC_PCLKx(__PCLK__) (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
                                ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
                                ((__PCLK__) == RCC_HCLK_DIV16))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_RTCCLKSOURCE_NONE) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)  || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)  || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32))

#define IS_RCC_MCO(__MCOX__) (((__MCOX__) == RCC_MCO1))

#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK)  || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_MSI)     || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSI)     || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSE)     || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_PLLCLK)  || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_LSI)     || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_LSE)     || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_PLLPCLK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_PLLQCLK))

#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                ((__DIV__) == RCC_MCODIV_16))


#define IS_RCC_STOP_WAKEUPCLOCK(__SOURCE__) (((__SOURCE__) == RCC_STOP_WAKEUPCLOCK_MSI) || \
                                             ((__SOURCE__) == RCC_STOP_WAKEUPCLOCK_HSI))
/**
  * @}
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
                            This parameter must be a value of @ref RCC_PLL_Config                                 */

  uint32_t PLLSource;  /*!< RCC_PLLSource: PLL entry clock source.
                            This parameter must be a value of @ref RCC_PLL_Clock_Source                           */

  uint32_t PLLM;       /*!< PLLM: Division factor for PLL VCO input clock.
                            This parameter must be a value of @ref RCC_PLLM_Clock_Divider                         */

  uint32_t PLLN;       /*!< PLLN: Multiplication factor for PLL VCO output clock.
                            This parameter must be a number between Min_Data = 6 and Max_Data = 127                */

  uint32_t PLLP;       /*!< PLLP: Division factor for ADC clock.
                            This parameter must be a value of @ref RCC_PLLP_Clock_Divider                         */

  uint32_t PLLQ;       /*!< PLLQ: Division factor for I2S2 and RNG clock.
                            This parameter must be a value of @ref RCC_PLLQ_Clock_Divider                         */

  uint32_t PLLR;       /*!< PLLR: Division for the main system clock.
                            User has to set the PLLR parameter correctly to not exceed max frequency 48 MHZ.
                            This parameter must be a value of @ref RCC_PLLR_Clock_Divider                         */

} RCC_PLLInitTypeDef;

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, MSI, LSE and LSI) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a combination of @ref RCC_Oscillator_Type             */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t HSEDiv;               /*!< The division factor of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Div                           */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value (default is @ref RCC_HSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  uint32_t LSIDiv;               /*!< The division factor of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Div                           */

  uint32_t MSIState;             /*!< The new state of the MSI.
                                      This parameter can be a value of @ref RCC_MSI_Config */

  uint32_t MSICalibrationValue;  /*!< The calibration trimming value (default is @ref RCC_MSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF */

  uint32_t MSIClockRange;        /*!< The MSI frequency range.
                                      This parameter can be a value of @ref RCC_MSI_Clock_Range                   */

  RCC_PLLInitTypeDef PLL;        /*!< Main PLL structure parameters                                               */

} RCC_OscInitTypeDef;

/**
  * @brief  RCC System, AHB and APB buses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a combination of @ref RCC_System_Clock_Type          */

  uint32_t SYSCLKSource;          /*!< The clock source used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_System_Clock_Source              */

  uint32_t AHBCLKDivider;         /*!< The AHBx clock (HCLK1) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_AHBx_Clock_Source                */

  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APBx_Clock_Source                */

  uint32_t APB2CLKDivider;        /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APBx_Clock_Source                */

#if defined(DUAL_CORE)
  uint32_t AHBCLK2Divider;        /*!< The AHB clock (HCLK2) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_AHBx_Clock_Source                */

#endif /* DUAL_CORE */
  uint32_t AHBCLK3Divider;        /*!< The AHB shared clock (HCLK3) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_AHBx_Clock_Source                */

} RCC_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE        0x00000000U  /*!< Oscillator configuration unchanged  */
#define RCC_OSCILLATORTYPE_HSE         0x00000001U  /*!< HSE to configure                    */
#define RCC_OSCILLATORTYPE_HSI         0x00000002U  /*!< HSI to configure                    */
#define RCC_OSCILLATORTYPE_LSE         0x00000004U  /*!< LSE to configure                    */
#define RCC_OSCILLATORTYPE_LSI         0x00000008U  /*!< LSI to configure                    */
#define RCC_OSCILLATORTYPE_MSI         0x00000020U  /*!< MSI to configure                    */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                    0x00000000U                                    /*!< HSE clock deactivation                    */
#define RCC_HSE_ON                     RCC_CR_HSEON                                   /*!< HSE clock activation                      */
#define RCC_HSE_BYPASS_PWR             ((uint32_t)(RCC_CR_HSEBYPPWR | RCC_CR_HSEON))  /*!< TCXO external clock source for HSE clock  */
/**
  * @}
  */

/** @defgroup RCC_HSE_Div HSE Div
  * @{
  */
#define RCC_HSE_DIV1                   0x00000000U    /*!< HSE clock not divided    */
#define RCC_HSE_DIV2                   RCC_CR_HSEPRE  /*!< HSE clock divided by 2    */
/**
  * @}
  */

/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                    0U                                                                  /*!< LSE clock deactivation                             */
#define RCC_LSE_ON_RTC_ONLY            RCC_BDCR_LSEON                                                      /*!< LSE clock activation for RTC only                  */
#define RCC_LSE_ON                     ((uint32_t)(RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON))                    /*!< LSE clock activation for RTC and other peripherals */
#define RCC_LSE_BYPASS_RTC_ONLY        ((uint32_t)(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON))                      /*!< External clock source for LSE clock                */
#define RCC_LSE_BYPASS                 ((uint32_t)(RCC_BDCR_LSEBYP | RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON))  /*!< External clock source for LSE clock                */

/**
  * @}
  */

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                    0x00000000U   /*!< HSI clock deactivation */
#define RCC_HSI_ON                     RCC_CR_HSION  /*!< HSI clock activation   */

#define RCC_HSICALIBRATION_DEFAULT     64U           /*!< Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U    /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CSR_LSION  /*!< LSI clock activation   */
/**
  * @}
  */

/** @defgroup RCC_LSI_Div LSI Div
  * @{
  */
#define RCC_LSI_DIV1                   LL_RCC_LSI_PREDIV_1    /*!< LSI clock not divided    */
#define RCC_LSI_DIV128                 LL_RCC_LSI_PREDIV_128  /*!< LSI clock divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_MSI_Config MSI Config
  * @{
  */
#define RCC_MSI_OFF                    0x00000000U   /*!< MSI clock deactivation */
#define RCC_MSI_ON                     RCC_CR_MSION  /*!< MSI clock activation   */

#define RCC_MSICALIBRATION_DEFAULT     0U            /*!< Default MSI calibration trimming value */
/**
  * @}
  */


/** @defgroup RCC_PLL_Config PLL Config
  * @{
  */
#define RCC_PLL_NONE                   0x00000000U  /*!< PLL configuration unchanged */
#define RCC_PLL_OFF                    0x00000001U  /*!< PLL deactivation            */
#define RCC_PLL_ON                     0x00000002U  /*!< PLL activation              */
/**
  * @}
  */

/** @defgroup RCC_PLLM_Clock_Divider PLLM Clock Divider
  * @{
  */
#define RCC_PLLM_DIV1                  LL_RCC_PLLM_DIV_1  /*!< PLLM division factor = 1  */
#define RCC_PLLM_DIV2                  LL_RCC_PLLM_DIV_2  /*!< PLLM division factor = 2  */
#define RCC_PLLM_DIV3                  LL_RCC_PLLM_DIV_3  /*!< PLLM division factor = 3  */
#define RCC_PLLM_DIV4                  LL_RCC_PLLM_DIV_4  /*!< PLLM division factor = 4  */
#define RCC_PLLM_DIV5                  LL_RCC_PLLM_DIV_5  /*!< PLLM division factor = 5  */
#define RCC_PLLM_DIV6                  LL_RCC_PLLM_DIV_6  /*!< PLLM division factor = 6  */
#define RCC_PLLM_DIV7                  LL_RCC_PLLM_DIV_7  /*!< PLLM division factor = 7  */
#define RCC_PLLM_DIV8                  LL_RCC_PLLM_DIV_8  /*!< PLLM division factor = 8  */
/**
  * @}
  */

/** @defgroup RCC_PLLP_Clock_Divider PLLP Clock Divider
  * @{
  */
#define RCC_PLLP_DIV2                  LL_RCC_PLLP_DIV_2   /*!< PLLP division factor = 2  */
#define RCC_PLLP_DIV3                  LL_RCC_PLLP_DIV_3   /*!< PLLP division factor = 3  */
#define RCC_PLLP_DIV4                  LL_RCC_PLLP_DIV_4   /*!< PLLP division factor = 4  */
#define RCC_PLLP_DIV5                  LL_RCC_PLLP_DIV_5   /*!< PLLP division factor = 5  */
#define RCC_PLLP_DIV6                  LL_RCC_PLLP_DIV_6   /*!< PLLP division factor = 6  */
#define RCC_PLLP_DIV7                  LL_RCC_PLLP_DIV_7   /*!< PLLP division factor = 7  */
#define RCC_PLLP_DIV8                  LL_RCC_PLLP_DIV_8   /*!< PLLP division factor = 8  */
#define RCC_PLLP_DIV9                  LL_RCC_PLLP_DIV_9   /*!< PLLP division factor = 9  */
#define RCC_PLLP_DIV10                 LL_RCC_PLLP_DIV_10  /*!< PLLP division factor = 10 */
#define RCC_PLLP_DIV11                 LL_RCC_PLLP_DIV_11  /*!< PLLP division factor = 11 */
#define RCC_PLLP_DIV12                 LL_RCC_PLLP_DIV_12  /*!< PLLP division factor = 12 */
#define RCC_PLLP_DIV13                 LL_RCC_PLLP_DIV_13  /*!< PLLP division factor = 13 */
#define RCC_PLLP_DIV14                 LL_RCC_PLLP_DIV_14  /*!< PLLP division factor = 14 */
#define RCC_PLLP_DIV15                 LL_RCC_PLLP_DIV_15  /*!< PLLP division factor = 15 */
#define RCC_PLLP_DIV16                 LL_RCC_PLLP_DIV_16  /*!< PLLP division factor = 16 */
#define RCC_PLLP_DIV17                 LL_RCC_PLLP_DIV_17  /*!< PLLP division factor = 17 */
#define RCC_PLLP_DIV18                 LL_RCC_PLLP_DIV_18  /*!< PLLP division factor = 18 */
#define RCC_PLLP_DIV19                 LL_RCC_PLLP_DIV_19  /*!< PLLP division factor = 19 */
#define RCC_PLLP_DIV20                 LL_RCC_PLLP_DIV_20  /*!< PLLP division factor = 20 */
#define RCC_PLLP_DIV21                 LL_RCC_PLLP_DIV_21  /*!< PLLP division factor = 21 */
#define RCC_PLLP_DIV22                 LL_RCC_PLLP_DIV_22  /*!< PLLP division factor = 22 */
#define RCC_PLLP_DIV23                 LL_RCC_PLLP_DIV_23  /*!< PLLP division factor = 23 */
#define RCC_PLLP_DIV24                 LL_RCC_PLLP_DIV_24  /*!< PLLP division factor = 24 */
#define RCC_PLLP_DIV25                 LL_RCC_PLLP_DIV_25  /*!< PLLP division factor = 25 */
#define RCC_PLLP_DIV26                 LL_RCC_PLLP_DIV_26  /*!< PLLP division factor = 26 */
#define RCC_PLLP_DIV27                 LL_RCC_PLLP_DIV_27  /*!< PLLP division factor = 27 */
#define RCC_PLLP_DIV28                 LL_RCC_PLLP_DIV_28  /*!< PLLP division factor = 28 */
#define RCC_PLLP_DIV29                 LL_RCC_PLLP_DIV_29  /*!< PLLP division factor = 29 */
#define RCC_PLLP_DIV30                 LL_RCC_PLLP_DIV_30  /*!< PLLP division factor = 30 */
#define RCC_PLLP_DIV31                 LL_RCC_PLLP_DIV_31  /*!< PLLP division factor = 31 */
#define RCC_PLLP_DIV32                 LL_RCC_PLLP_DIV_32  /*!< PLLP division factor = 32 */
/**
  * @}
  */

/** @defgroup RCC_PLLQ_Clock_Divider PLLQ Clock Divider
  * @{
  */
#define RCC_PLLQ_DIV2                  LL_RCC_PLLQ_DIV_2  /*!< PLLQ division factor = 2 */
#define RCC_PLLQ_DIV3                  LL_RCC_PLLQ_DIV_3  /*!< PLLQ division factor = 3 */
#define RCC_PLLQ_DIV4                  LL_RCC_PLLQ_DIV_4  /*!< PLLQ division factor = 4 */
#define RCC_PLLQ_DIV5                  LL_RCC_PLLQ_DIV_5  /*!< PLLQ division factor = 5 */
#define RCC_PLLQ_DIV6                  LL_RCC_PLLQ_DIV_6  /*!< PLLQ division factor = 6 */
#define RCC_PLLQ_DIV7                  LL_RCC_PLLQ_DIV_7  /*!< PLLQ division factor = 7 */
#define RCC_PLLQ_DIV8                  LL_RCC_PLLQ_DIV_8  /*!< PLLQ division factor = 8 */
/**
  * @}
  */

/** @defgroup RCC_PLLR_Clock_Divider PLLR Clock Divider
  * @{
  */
#define RCC_PLLR_DIV2                  LL_RCC_PLLR_DIV_2  /*!< PLLR division factor = 2 */
#define RCC_PLLR_DIV3                  LL_RCC_PLLR_DIV_3  /*!< PLLR division factor = 3 */
#define RCC_PLLR_DIV4                  LL_RCC_PLLR_DIV_4  /*!< PLLR division factor = 4 */
#define RCC_PLLR_DIV5                  LL_RCC_PLLR_DIV_5  /*!< PLLR division factor = 5 */
#define RCC_PLLR_DIV6                  LL_RCC_PLLR_DIV_6  /*!< PLLR division factor = 6 */
#define RCC_PLLR_DIV7                  LL_RCC_PLLR_DIV_7  /*!< PLLR division factor = 7 */
#define RCC_PLLR_DIV8                  LL_RCC_PLLR_DIV_8  /*!< PLLR division factor = 8 */
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_NONE             LL_RCC_PLLSOURCE_NONE  /*!< No clock selected as PLL entry clock source  */
#define RCC_PLLSOURCE_MSI              LL_RCC_PLLSOURCE_MSI   /*!< MSI clock selected as PLL entry clock source */
#define RCC_PLLSOURCE_HSI              LL_RCC_PLLSOURCE_HSI   /*!< HSI clock selected as PLL entry clock source */
#define RCC_PLLSOURCE_HSE              LL_RCC_PLLSOURCE_HSE   /*!< HSE clock selected as PLL entry clock source */
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Output PLL Clock Output
  * @{
  */
#define RCC_PLL_SYSCLK                 RCC_PLLCFGR_PLLREN  /*!< PLLCLK selected from main PLL     */
#define RCC_PLL_I2S2CLK                RCC_PLLCFGR_PLLQEN  /*!< PLLI2S2CLK selected from main PLL */
#define RCC_PLL_RNGCLK                 RCC_PLLCFGR_PLLQEN  /*!< PLLRNGCLK selected from main PLL  */
#define RCC_PLL_ADCCLK                 RCC_PLLCFGR_PLLPEN  /*!< PLLADCCLK selected from main PLL  */
/**
  * @}
  */

/** @defgroup RCC_MSI_Clock_Range MSI Clock Range
  * @{
  */
#define RCC_MSIRANGE_0                 LL_RCC_MSIRANGE_0   /*!< MSI = 100 KHz  */
#define RCC_MSIRANGE_1                 LL_RCC_MSIRANGE_1   /*!< MSI = 200 KHz  */
#define RCC_MSIRANGE_2                 LL_RCC_MSIRANGE_2   /*!< MSI = 400 KHz  */
#define RCC_MSIRANGE_3                 LL_RCC_MSIRANGE_3   /*!< MSI = 800 KHz  */
#define RCC_MSIRANGE_4                 LL_RCC_MSIRANGE_4   /*!< MSI = 1 MHz    */
#define RCC_MSIRANGE_5                 LL_RCC_MSIRANGE_5   /*!< MSI = 2 MHz    */
#define RCC_MSIRANGE_6                 LL_RCC_MSIRANGE_6   /*!< MSI = 4 MHz    */
#define RCC_MSIRANGE_7                 LL_RCC_MSIRANGE_7   /*!< MSI = 8 MHz    */
#define RCC_MSIRANGE_8                 LL_RCC_MSIRANGE_8   /*!< MSI = 16 MHz   */
#define RCC_MSIRANGE_9                 LL_RCC_MSIRANGE_9   /*!< MSI = 24 MHz   */
#define RCC_MSIRANGE_10                LL_RCC_MSIRANGE_10  /*!< MSI = 32 MHz   */
#define RCC_MSIRANGE_11                LL_RCC_MSIRANGE_11  /*!< MSI = 48 MHz   */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Type System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK           0x00000001U  /*!< SYSCLK to configure */
#define RCC_CLOCKTYPE_HCLK             0x00000002U  /*!< HCLK to configure   */
#define RCC_CLOCKTYPE_PCLK1            0x00000004U  /*!< PCLK1 to configure  */
#define RCC_CLOCKTYPE_PCLK2            0x00000008U  /*!< PCLK2 to configure  */
#if defined(DUAL_CORE)
#define RCC_CLOCKTYPE_HCLK2            0x00000020U  /*!< HCLK2 to configure  */
#endif /* DUAL_CORE */
#define RCC_CLOCKTYPE_HCLK3            0x00000040U  /*!< HCLK3 to configure  */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_MSI           LL_RCC_SYS_CLKSOURCE_MSI  /*!< MSI selected as system clock */
#define RCC_SYSCLKSOURCE_HSI           LL_RCC_SYS_CLKSOURCE_HSI  /*!< HSI selected as system clock */
#define RCC_SYSCLKSOURCE_HSE           LL_RCC_SYS_CLKSOURCE_HSE  /*!< HSE selected as system clock */
#define RCC_SYSCLKSOURCE_PLLCLK        LL_RCC_SYS_CLKSOURCE_PLL  /*!< PLL selected as system clock */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_MSI    LL_RCC_SYS_CLKSOURCE_STATUS_MSI  /*!< MSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSI    LL_RCC_SYS_CLKSOURCE_STATUS_HSI  /*!< HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE    LL_RCC_SYS_CLKSOURCE_STATUS_HSE  /*!< HSE used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK LL_RCC_SYS_CLKSOURCE_STATUS_PLL  /*!< PLL used as system clock */
/**
  * @}
  */

/** @defgroup RCC_AHBx_Clock_Source AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1                LL_RCC_SYSCLK_DIV_1    /*!< SYSCLK not divided    */
#define RCC_SYSCLK_DIV2                LL_RCC_SYSCLK_DIV_2    /*!< SYSCLK divided by 2   */
#define RCC_SYSCLK_DIV3                LL_RCC_SYSCLK_DIV_3    /*!< SYSCLK divided by 3   */
#define RCC_SYSCLK_DIV4                LL_RCC_SYSCLK_DIV_4    /*!< SYSCLK divided by 4   */
#define RCC_SYSCLK_DIV5                LL_RCC_SYSCLK_DIV_5    /*!< SYSCLK divided by 5   */
#define RCC_SYSCLK_DIV6                LL_RCC_SYSCLK_DIV_6    /*!< SYSCLK divided by 6   */
#define RCC_SYSCLK_DIV8                LL_RCC_SYSCLK_DIV_8    /*!< SYSCLK divided by 8   */
#define RCC_SYSCLK_DIV10               LL_RCC_SYSCLK_DIV_10   /*!< SYSCLK divided by 10  */
#define RCC_SYSCLK_DIV16               LL_RCC_SYSCLK_DIV_16   /*!< SYSCLK divided by 16  */
#define RCC_SYSCLK_DIV32               LL_RCC_SYSCLK_DIV_32   /*!< SYSCLK divided by 32  */
#define RCC_SYSCLK_DIV64               LL_RCC_SYSCLK_DIV_64   /*!< SYSCLK divided by 64  */
#define RCC_SYSCLK_DIV128              LL_RCC_SYSCLK_DIV_128  /*!< SYSCLK divided by 128 */
#define RCC_SYSCLK_DIV256              LL_RCC_SYSCLK_DIV_256  /*!< SYSCLK divided by 256 */
#define RCC_SYSCLK_DIV512              LL_RCC_SYSCLK_DIV_512  /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_APBx_Clock_Source APB1 Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                  LL_RCC_APB1_DIV_1   /*!< HCLK not divided   */
#define RCC_HCLK_DIV2                  LL_RCC_APB1_DIV_2   /*!< HCLK divided by 2  */
#define RCC_HCLK_DIV4                  LL_RCC_APB1_DIV_4   /*!< HCLK divided by 4  */
#define RCC_HCLK_DIV8                  LL_RCC_APB1_DIV_8   /*!< HCLK divided by 8  */
#define RCC_HCLK_DIV16                 LL_RCC_APB1_DIV_16  /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_NONE           LL_RCC_RTC_CLKSOURCE_NONE       /*!< No clock used as RTC clock                           */
#define RCC_RTCCLKSOURCE_LSE            LL_RCC_RTC_CLKSOURCE_LSE        /*!< LSE oscillator clock used as RTC clock               */
#define RCC_RTCCLKSOURCE_LSI            LL_RCC_RTC_CLKSOURCE_LSI        /*!< LSI oscillator clock used as RTC clock               */
#define RCC_RTCCLKSOURCE_HSE_DIV32      LL_RCC_RTC_CLKSOURCE_HSE_DIV32  /*!< HSE oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define RCC_MCO1                       0x00000000U  /*!< MCO1 index                                         */
#define RCC_MCO                        RCC_MCO1     /*!< MCO to be compliant with other families with 1 MCO */
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Source MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_NOCLOCK         LL_RCC_MCO1SOURCE_NOCLOCK  /*!< MCO1 output disabled, no clock on MCO1          */
#define RCC_MCO1SOURCE_SYSCLK          LL_RCC_MCO1SOURCE_SYSCLK   /*!< SYSCLK selected as MCO1 source                  */
#define RCC_MCO1SOURCE_MSI             LL_RCC_MCO1SOURCE_MSI      /*!< MSI selected as MCO1 source                     */
#define RCC_MCO1SOURCE_HSI             LL_RCC_MCO1SOURCE_HSI      /*!< HSI selected as MCO1 source                     */
#define RCC_MCO1SOURCE_HSE             LL_RCC_MCO1SOURCE_HSE      /*!< HSE after stabilization selected as MCO1 source */
#define RCC_MCO1SOURCE_PLLCLK          LL_RCC_MCO1SOURCE_PLLCLK   /*!< Main PLLRCLK selected as MCO1 source            */
#define RCC_MCO1SOURCE_LSI             LL_RCC_MCO1SOURCE_LSI      /*!< LSI selected as MCO1 source                     */
#define RCC_MCO1SOURCE_LSE             LL_RCC_MCO1SOURCE_LSE      /*!< LSE selected as MCO1 source                     */
#define RCC_MCO1SOURCE_PLLPCLK         LL_RCC_MCO1SOURCE_PLLPCLK  /*!< Main PLLPCLK selected as MCO1 source            */
#define RCC_MCO1SOURCE_PLLQCLK         LL_RCC_MCO1SOURCE_PLLQCLK  /*!< Main PLLQCLK selected as MCO1 source            */
/**
  * @}
  */

/** @defgroup RCC_MCOx_Clock_Prescaler MCO Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                   LL_RCC_MCO1_DIV_1    /*!< MCO not divided */
#define RCC_MCODIV_2                   LL_RCC_MCO1_DIV_2    /*!< MCO divided by 2 */
#define RCC_MCODIV_4                   LL_RCC_MCO1_DIV_4    /*!< MCO divided by 4 */
#define RCC_MCODIV_8                   LL_RCC_MCO1_DIV_8    /*!< MCO divided by 8 */
#define RCC_MCODIV_16                  LL_RCC_MCO1_DIV_16  /*!< MCO divided by 16 */
/**
  * @}
  */


/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_LSIRDY                  LL_RCC_CIFR_LSIRDYF   /*!< LSI Ready Interrupt flag                 */
#define RCC_IT_LSERDY                  LL_RCC_CIFR_LSERDYF   /*!< LSE Ready Interrupt flag                 */
#define RCC_IT_MSIRDY                  LL_RCC_CIFR_MSIRDYF   /*!< MSI Ready Interrupt flag                 */
#define RCC_IT_HSIRDY                  LL_RCC_CIFR_HSIRDYF   /*!< HSI Ready Interrupt flag                 */
#define RCC_IT_HSERDY                  LL_RCC_CIFR_HSERDYF   /*!< HSE Ready Interrupt flag                 */
#define RCC_IT_PLLRDY                  LL_RCC_CIFR_PLLRDYF   /*!< PLL Ready Interrupt flag                 */
#define RCC_IT_HSECSS                  LL_RCC_CIFR_CSSF      /*!< HSE Clock Security System Interrupt flag */
#define RCC_IT_LSECSS                  LL_RCC_CIFR_LSECSSF   /*!< LSE Clock Security System Interrupt flag */
/**
  * @}
  */


/** @defgroup RCC_Flag Flags
  *        Elements values convention: XXXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XXX  : Register index
  *                 - 001: CR register
  *                 - 010: BDCR register
  *                 - 011: CSR register
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_MSIRDY                ((CR_REG_INDEX << REG_INDEX_POS) | RCC_CR_MSIRDY_Pos)         /*!< MSI Ready flag                                   */
#define RCC_FLAG_HSIRDY                ((CR_REG_INDEX << REG_INDEX_POS) | RCC_CR_HSIRDY_Pos)         /*!< HSI Ready flag                                   */
#define RCC_FLAG_HSIKERDY              ((CR_REG_INDEX << REG_INDEX_POS) | RCC_CR_HSIKERDY_Pos)       /*!< HSI Ready flag                                   */
#define RCC_FLAG_HSERDY                ((CR_REG_INDEX << REG_INDEX_POS) | RCC_CR_HSERDY_Pos)         /*!< HSE Ready flag                                   */
#define RCC_FLAG_PLLRDY                ((CR_REG_INDEX << REG_INDEX_POS) | RCC_CR_PLLRDY_Pos)         /*!< PLL Ready flag                                   */

/* Flags in the BDCR register */
#define RCC_FLAG_LSERDY                ((BDCR_REG_INDEX << REG_INDEX_POS) | RCC_BDCR_LSERDY_Pos)     /*!< LSE Ready flag                                   */
#define RCC_FLAG_LSECSSD               ((BDCR_REG_INDEX << REG_INDEX_POS) | RCC_BDCR_LSECSSD_Pos)    /*!< LSE Clock Security System failure detection flag */
#define RCC_FLAG_LSESYSRDY             ((BDCR_REG_INDEX << REG_INDEX_POS) | RCC_BDCR_LSESYSRDY_Pos)  /*!< LSE system clock ready flag                      */

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY                ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_LSIRDY_Pos)       /*!< LSI Ready flag                                   */
#define RCC_FLAG_RFRST                 ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_RFRSTF_Pos)       /*!< Sub-GHz radio reset flag                         */
#define RCC_FLAG_RFILARSTF             ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_RFILARSTF_Pos)    /*!< Sub-GHz radio illegal command flag               */
#define RCC_FLAG_OBLRST                ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_OBLRSTF_Pos)      /*!< Option Byte Loader reset flag                    */
#define RCC_FLAG_PINRST                ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_PINRSTF_Pos)      /*!< Pin reset flag (NRST pin)                        */
#define RCC_FLAG_BORRST                ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_BORRSTF_Pos)      /*!< BOR reset flag                                   */
#define RCC_FLAG_SFTRST                ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_SFTRSTF_Pos)      /*!< Software Reset flag                              */
#define RCC_FLAG_IWDGRST               ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_IWDGRSTF_Pos)     /*!< Watchdog reset flag                              */
#define RCC_FLAG_WWDGRST               ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_WWDGRSTF_Pos)     /*!< Window watchdog reset flag                       */
#define RCC_FLAG_LPWRRST               ((CSR_REG_INDEX << REG_INDEX_POS) | RCC_CSR_LPWRRSTF_Pos)     /*!< Low-Power reset flag                             */
/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Configuration
  * @{
  */
#define RCC_LSEDRIVE_LOW                 LL_RCC_LSEDRIVE_LOW         /*!< LSE low drive capability         */
#define RCC_LSEDRIVE_MEDIUMLOW           LL_RCC_LSEDRIVE_MEDIUMLOW   /*!< LSE medium low drive capability  */
#define RCC_LSEDRIVE_MEDIUMHIGH          LL_RCC_LSEDRIVE_MEDIUMHIGH  /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH                LL_RCC_LSEDRIVE_HIGH        /*!< LSE high drive capability        */
/**
  * @}
  */

/** @defgroup RCC_Stop_WakeUpClock Wake-Up from STOP Clock
  * @{
  */
#define RCC_STOP_WAKEUPCLOCK_MSI       LL_RCC_STOP_WAKEUPCLOCK_MSI  /*!< MSI selected after wake-up from STOP */
#define RCC_STOP_WAKEUPCLOCK_HSI       LL_RCC_STOP_WAKEUPCLOCK_HSI  /*!< HSI selected after wake-up from STOP */
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

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable AHB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_DMA1_CLK_ENABLE()                 LL_C2_AHB1_GRP1_EnableClock(LL_C2_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_CLK_ENABLE()                 LL_C2_AHB1_GRP1_EnableClock(LL_C2_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_CLK_ENABLE()              LL_C2_AHB1_GRP1_EnableClock(LL_C2_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_CLK_ENABLE()                  LL_C2_AHB1_GRP1_EnableClock(LL_C2_AHB1_GRP1_PERIPH_CRC)

#define __HAL_RCC_DMA1_CLK_DISABLE()                LL_C2_AHB1_GRP1_DisableClock(LL_C2_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_CLK_DISABLE()                LL_C2_AHB1_GRP1_DisableClock(LL_C2_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_CLK_DISABLE()             LL_C2_AHB1_GRP1_DisableClock(LL_C2_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_CLK_DISABLE()                 LL_C2_AHB1_GRP1_DisableClock(LL_C2_AHB1_GRP1_PERIPH_CRC)
#else
#define __HAL_RCC_DMA1_CLK_ENABLE()                 LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_CLK_ENABLE()                 LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_CLK_ENABLE()              LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_CLK_ENABLE()                  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CRC)

#define __HAL_RCC_DMA1_CLK_DISABLE()                LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_CLK_DISABLE()                LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_CLK_DISABLE()             LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_CLK_DISABLE()                 LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_CRC)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_GPIOA_CLK_ENABLE()                LL_C2_AHB2_GRP1_EnableClock(LL_C2_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_ENABLE()                LL_C2_AHB2_GRP1_EnableClock(LL_C2_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_CLK_ENABLE()                LL_C2_AHB2_GRP1_EnableClock(LL_C2_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_CLK_ENABLE()                LL_C2_AHB2_GRP1_EnableClock(LL_C2_AHB2_GRP1_PERIPH_GPIOH)

#define __HAL_RCC_GPIOA_CLK_DISABLE()               LL_C2_AHB2_GRP1_DisableClock(LL_C2_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_DISABLE()               LL_C2_AHB2_GRP1_DisableClock(LL_C2_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_CLK_DISABLE()               LL_C2_AHB2_GRP1_DisableClock(LL_C2_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_CLK_DISABLE()               LL_C2_AHB2_GRP1_DisableClock(LL_C2_AHB2_GRP1_PERIPH_GPIOH)
#else
#define __HAL_RCC_GPIOA_CLK_ENABLE()                LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_ENABLE()                LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_CLK_ENABLE()                LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_CLK_ENABLE()                LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH)

#define __HAL_RCC_GPIOA_CLK_DISABLE()               LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_DISABLE()               LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_CLK_DISABLE()               LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_CLK_DISABLE()               LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOH)
#endif /* CORE_CM0PLUS */
/**
  * @}
  */

/** @defgroup RCC_AHB3_Clock_Enable_Disable AHB3 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_PKA_CLK_ENABLE()                  LL_C2_AHB3_GRP1_EnableClock(LL_C2_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_CLK_ENABLE()                  LL_C2_AHB3_GRP1_EnableClock(LL_C2_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_CLK_ENABLE()                  LL_C2_AHB3_GRP1_EnableClock(LL_C2_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_HSEM_CLK_ENABLE()                 LL_C2_AHB3_GRP1_EnableClock(LL_C2_AHB3_GRP1_PERIPH_HSEM)
#define __HAL_RCC_IPCC_CLK_ENABLE()                 LL_C2_AHB3_GRP1_EnableClock(LL_C2_AHB3_GRP1_PERIPH_IPCC)
#define __HAL_RCC_FLASH_CLK_ENABLE()                LL_C2_AHB3_GRP1_EnableClock(LL_C2_AHB3_GRP1_PERIPH_FLASH)

#define __HAL_RCC_PKA_CLK_DISABLE()                 LL_C2_AHB3_GRP1_DisableClock(LL_C2_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_CLK_DISABLE()                 LL_C2_AHB3_GRP1_DisableClock(LL_C2_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_CLK_DISABLE()                 LL_C2_AHB3_GRP1_DisableClock(LL_C2_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_HSEM_CLK_DISABLE()                LL_C2_AHB3_GRP1_DisableClock(LL_C2_AHB3_GRP1_PERIPH_HSEM)
#define __HAL_RCC_IPCC_CLK_DISABLE()                LL_C2_AHB3_GRP1_DisableClock(LL_C2_AHB3_GRP1_PERIPH_IPCC)
#define __HAL_RCC_FLASH_CLK_DISABLE()               LL_C2_AHB3_GRP1_DisableClock(LL_C2_AHB3_GRP1_PERIPH_FLASH)
#else
#define __HAL_RCC_PKA_CLK_ENABLE()                  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_CLK_ENABLE()                  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_CLK_ENABLE()                  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_HSEM_CLK_ENABLE()                 LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_HSEM)
#define __HAL_RCC_IPCC_CLK_ENABLE()                 LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_IPCC)
#define __HAL_RCC_FLASH_CLK_ENABLE()                LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_FLASH)

#define __HAL_RCC_PKA_CLK_DISABLE()                 LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_CLK_DISABLE()                 LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_CLK_DISABLE()                 LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_HSEM_CLK_DISABLE()                LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_HSEM)
#define __HAL_RCC_IPCC_CLK_DISABLE()                LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_IPCC)
#define __HAL_RCC_FLASH_CLK_DISABLE()               LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_FLASH)
#endif /* CORE_CM0PLUS */
/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_TIM2_CLK_ENABLE()                 LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_CLK_ENABLE()               LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_SPI2_CLK_ENABLE()                 LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_CLK_ENABLE()               LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_CLK_ENABLE()                 LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_CLK_ENABLE()                 LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_CLK_ENABLE()                 LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_CLK_ENABLE()                  LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_CLK_ENABLE()               LL_C2_APB1_GRP1_EnableClock(LL_C2_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPTIM2_CLK_ENABLE()               LL_C2_APB1_GRP2_EnableClock(LL_C2_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_CLK_ENABLE()               LL_C2_APB1_GRP2_EnableClock(LL_C2_APB1_GRP2_PERIPH_LPTIM3)
#define __HAL_RCC_LPUART1_CLK_ENABLE()              LL_C2_APB1_GRP2_EnableClock(LL_C2_APB1_GRP2_PERIPH_LPUART1)

#define __HAL_RCC_TIM2_CLK_DISABLE()                LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_CLK_DISABLE()              LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_SPI2_CLK_DISABLE()                LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_CLK_DISABLE()              LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_CLK_DISABLE()                LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_CLK_DISABLE()                LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_CLK_DISABLE()                LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_CLK_DISABLE()                 LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_CLK_DISABLE()              LL_C2_APB1_GRP1_DisableClock(LL_C2_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPTIM2_CLK_DISABLE()              LL_C2_APB1_GRP2_DisableClock(LL_C2_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_CLK_DISABLE()              LL_C2_APB1_GRP2_DisableClock(LL_C2_APB1_GRP2_PERIPH_LPTIM3)
#define __HAL_RCC_LPUART1_CLK_DISABLE()             LL_C2_APB1_GRP2_DisableClock(LL_C2_APB1_GRP2_PERIPH_LPUART1)
#else
#define __HAL_RCC_TIM2_CLK_ENABLE()                 LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_CLK_ENABLE()               LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_SPI2_CLK_ENABLE()                 LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_CLK_ENABLE()               LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_CLK_ENABLE()                 LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_CLK_ENABLE()                 LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_CLK_ENABLE()                 LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_CLK_ENABLE()                  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_CLK_ENABLE()               LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPTIM2_CLK_ENABLE()               LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_CLK_ENABLE()               LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_LPTIM3)
#define __HAL_RCC_LPUART1_CLK_ENABLE()              LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_LPUART1)

#define __HAL_RCC_TIM2_CLK_DISABLE()                LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_CLK_DISABLE()              LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_SPI2_CLK_DISABLE()                LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_CLK_DISABLE()              LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_CLK_DISABLE()                LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_CLK_DISABLE()                LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_CLK_DISABLE()                LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_CLK_DISABLE()                 LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_CLK_DISABLE()              LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPTIM2_CLK_DISABLE()              LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_CLK_DISABLE()              LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_LPTIM3)
#define __HAL_RCC_LPUART1_CLK_DISABLE()             LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_LPUART1)
#endif /* CORE_CM0PLUS */

#define __HAL_RCC_WWDG_CLK_ENABLE()                 LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG)

#define __HAL_RCC_WWDG_CLK_DISABLE()                LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_WWDG)

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_ADC_CLK_ENABLE()                  LL_C2_APB2_GRP1_EnableClock(LL_C2_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_CLK_ENABLE()                 LL_C2_APB2_GRP1_EnableClock(LL_C2_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_CLK_ENABLE()                 LL_C2_APB2_GRP1_EnableClock(LL_C2_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_CLK_ENABLE()               LL_C2_APB2_GRP1_EnableClock(LL_C2_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_CLK_ENABLE()                LL_C2_APB2_GRP1_EnableClock(LL_C2_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_CLK_ENABLE()                LL_C2_APB2_GRP1_EnableClock(LL_C2_APB2_GRP1_PERIPH_TIM17)

#define __HAL_RCC_ADC_CLK_DISABLE()                 LL_C2_APB2_GRP1_DisableClock(LL_C2_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_CLK_DISABLE()                LL_C2_APB2_GRP1_DisableClock(LL_C2_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_CLK_DISABLE()                LL_C2_APB2_GRP1_DisableClock(LL_C2_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_CLK_DISABLE()              LL_C2_APB2_GRP1_DisableClock(LL_C2_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_CLK_DISABLE()               LL_C2_APB2_GRP1_DisableClock(LL_C2_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_CLK_DISABLE()               LL_C2_APB2_GRP1_DisableClock(LL_C2_APB2_GRP1_PERIPH_TIM17)
#else
#define __HAL_RCC_ADC_CLK_ENABLE()                  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_CLK_ENABLE()                 LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_CLK_ENABLE()                 LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_CLK_ENABLE()               LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_CLK_ENABLE()                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_CLK_ENABLE()                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17)

#define __HAL_RCC_ADC_CLK_DISABLE()                 LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_CLK_DISABLE()                LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_CLK_DISABLE()                LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_CLK_DISABLE()              LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_CLK_DISABLE()               LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_CLK_DISABLE()               LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM17)
#endif /* CORE_CM0PLUS */
/**
  * @}
  */


/** @defgroup RCC_APB3_Clock_Enable_Disable APB3 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_SUBGHZSPI_CLK_ENABLE()            LL_C2_APB3_GRP1_EnableClock(LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI)

#define __HAL_RCC_SUBGHZSPI_CLK_DISABLE()           LL_C2_APB3_GRP1_DisableClock(LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI)
#else
#define __HAL_RCC_SUBGHZSPI_CLK_ENABLE()            LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_SUBGHZSPI)

#define __HAL_RCC_SUBGHZSPI_CLK_DISABLE()           LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_SUBGHZSPI)
#endif /* CORE_CM0PLUS */


/* Aliases used by CubeMX for HAL SUBGHZ Init, MspInit and DeInit generation */
#define __HAL_RCC_SUBGHZ_CLK_ENABLE()               __HAL_RCC_SUBGHZSPI_CLK_ENABLE()
#define __HAL_RCC_SUBGHZ_CLK_DISABLE()              __HAL_RCC_SUBGHZSPI_CLK_DISABLE()
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable_Status AHB1 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the AHB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_DMA1_IS_CLK_ENABLED()             LL_C2_AHB1_GRP1_IsEnabledClock(LL_C2_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_IS_CLK_ENABLED()             LL_C2_AHB1_GRP1_IsEnabledClock(LL_C2_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_IS_CLK_ENABLED()          LL_C2_AHB1_GRP1_IsEnabledClock(LL_C2_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()              LL_C2_AHB1_GRP1_IsEnabledClock(LL_C2_AHB1_GRP1_PERIPH_CRC)
#else
#define __HAL_RCC_DMA1_IS_CLK_ENABLED()             LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_IS_CLK_ENABLED()             LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_IS_CLK_ENABLED()          LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()              LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_CRC)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()            LL_C2_AHB2_GRP1_IsEnabledClock(LL_C2_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()            LL_C2_AHB2_GRP1_IsEnabledClock(LL_C2_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()            LL_C2_AHB2_GRP1_IsEnabledClock(LL_C2_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_IS_CLK_ENABLED()            LL_C2_AHB2_GRP1_IsEnabledClock(LL_C2_AHB2_GRP1_PERIPH_GPIOH)
#else
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()            LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()            LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()            LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_IS_CLK_ENABLED()            LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOH)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_PKA_IS_CLK_ENABLED()              LL_C2_AHB3_GRP1_IsEnabledClock(LL_C2_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_IS_CLK_ENABLED()              LL_C2_AHB3_GRP1_IsEnabledClock(LL_C2_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_IS_CLK_ENABLED()              LL_C2_AHB3_GRP1_IsEnabledClock(LL_C2_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_HSEM_IS_CLK_ENABLED()             LL_C2_AHB3_GRP1_IsEnabledClock(LL_C2_AHB3_GRP1_PERIPH_HSEM)
#define __HAL_RCC_IPCC_IS_CLK_ENABLED()             LL_C2_AHB3_GRP1_IsEnabledClock(LL_C2_AHB3_GRP1_PERIPH_IPCC)
#define __HAL_RCC_FLASH_IS_CLK_ENABLED()            LL_C2_AHB3_GRP1_IsEnabledClock(LL_C2_AHB3_GRP1_PERIPH_FLASH)
#else
#define __HAL_RCC_PKA_IS_CLK_ENABLED()              LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_IS_CLK_ENABLED()              LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_IS_CLK_ENABLED()              LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_HSEM_IS_CLK_ENABLED()             LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_HSEM)
#define __HAL_RCC_IPCC_IS_CLK_ENABLED()             LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_IPCC)
#define __HAL_RCC_FLASH_IS_CLK_ENABLED()            LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_FLASH)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()             LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()           LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()             LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_IS_CLK_ENABLED()           LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()             LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_IS_CLK_ENABLED()             LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()             LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()              LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()           LL_C2_APB1_GRP1_IsEnabledClock(LL_C2_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPTIM2_IS_CLK_ENABLED()           LL_C2_APB1_GRP2_IsEnabledClock(LL_C2_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_IS_CLK_ENABLED()           LL_C2_APB1_GRP2_IsEnabledClock(LL_C2_APB1_GRP2_PERIPH_LPTIM3)
#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()          LL_C2_APB1_GRP2_IsEnabledClock(LL_C2_APB1_GRP2_PERIPH_LPUART1)
#else
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()             LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()           LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()             LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_IS_CLK_ENABLED()           LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()             LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_IS_CLK_ENABLED()             LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()             LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()              LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()           LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPTIM2_IS_CLK_ENABLED()           LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_IS_CLK_ENABLED()           LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_LPTIM3)
#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()          LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_LPUART1)
#endif /* CORE_CM0PLUS */

#define __HAL_RCC_WWDG_IS_CLK_ENABLED()             LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_WWDG)
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_ADC_IS_CLK_ENABLED()              LL_C2_APB2_GRP1_IsEnabledClock(LL_C2_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()             LL_C2_APB2_GRP1_IsEnabledClock(LL_C2_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()             LL_C2_APB2_GRP1_IsEnabledClock(LL_C2_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_IS_CLK_ENABLED()           LL_C2_APB2_GRP1_IsEnabledClock(LL_C2_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()            LL_C2_APB2_GRP1_IsEnabledClock(LL_C2_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()            LL_C2_APB2_GRP1_IsEnabledClock(LL_C2_APB2_GRP1_PERIPH_TIM17)
#else
#define __HAL_RCC_ADC_IS_CLK_ENABLED()              LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()             LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()             LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_IS_CLK_ENABLED()           LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()            LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()            LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM17)
#endif /* CORE_CM0PLUS */
/**
  * @}
  */

/** @defgroup RCC_APB3_Clock_Enable_Disable_Status APB3 Peripheral Clock Enabled or Disabled Status
  * @brief  Check whether the APB3 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_SUBGHZSPI_IS_CLK_ENABLED()        LL_C2_APB3_GRP1_IsEnabledClock(LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI)
#else
#define __HAL_RCC_SUBGHZSPI_IS_CLK_ENABLED()        LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_SUBGHZSPI)
#endif /* CORE_CM0PLUS */

/* Aliases used by CubeMX for HAL SUBGHZ Init, MspInit and DeInit generation */
#define __HAL_RCC_SUBGHZ_IS_CLK_ENABLED()           __HAL_RCC_SUBGHZSPI_IS_CLK_ENABLED()
/**
  * @}
  */

/** @defgroup RCC_AHB1_Force_Release_Reset AHB1 Peripheral Force Release Reset
  * @brief  Force or release AHB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB1_FORCE_RESET()                LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_ALL)
#define __HAL_RCC_DMA1_FORCE_RESET()                LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_FORCE_RESET()                LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_FORCE_RESET()             LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_FORCE_RESET()                 LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_CRC)

#define __HAL_RCC_AHB1_RELEASE_RESET()              LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_ALL)
#define __HAL_RCC_DMA1_RELEASE_RESET()              LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_RELEASE_RESET()              LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_RELEASE_RESET()           LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_RELEASE_RESET()               LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_CRC)
/**
  * @}
  */

/** @defgroup RCC_AHB2_Force_Release_Reset AHB2 Peripheral Force Release Reset
  * @brief  Force or release AHB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB2_FORCE_RESET()                LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_ALL)
#define __HAL_RCC_GPIOA_FORCE_RESET()               LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_FORCE_RESET()               LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_FORCE_RESET()               LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_FORCE_RESET()               LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOH)

#define __HAL_RCC_AHB2_RELEASE_RESET()              LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_ALL)
#define __HAL_RCC_GPIOA_RELEASE_RESET()             LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_RELEASE_RESET()             LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_RELEASE_RESET()             LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_RELEASE_RESET()             LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOH)
/**
  * @}
  */

/** @defgroup RCC_AHB3_Force_Release_Reset AHB3 Peripheral Force Release Reset
  * @brief  Force or release AHB3 peripheral reset.
  * @{
  */
#if defined (DUAL_CORE)
#define __HAL_RCC_IPCC_FORCE_RESET()                LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_IPCC)
#define __HAL_RCC_IPCC_RELEASE_RESET()              LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_IPCC)
#endif /* DUAL_CORE */

#define __HAL_RCC_AHB3_FORCE_RESET()                LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_ALL)
#define __HAL_RCC_PKA_FORCE_RESET()                 LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_FORCE_RESET()                 LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_FORCE_RESET()                 LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_HSEM_FORCE_RESET()                LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_HSEM)
#define __HAL_RCC_FLASH_FORCE_RESET()               LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_FLASH)

#define __HAL_RCC_AHB3_RELEASE_RESET()              LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_ALL)
#define __HAL_RCC_PKA_RELEASE_RESET()               LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_RELEASE_RESET()               LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_RELEASE_RESET()               LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_HSEM_RELEASE_RESET()              LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_HSEM)
#define __HAL_RCC_FLASH_RELEASE_RESET()             LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_FLASH)
/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset APB1 Peripheral Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB1L_FORCE_RESET()               LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_ALL)
#define __HAL_RCC_TIM2_FORCE_RESET()                LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_SPI2_FORCE_RESET()                LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_FORCE_RESET()              LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_FORCE_RESET()                LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_FORCE_RESET()                LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_FORCE_RESET()                LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_FORCE_RESET()                 LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_FORCE_RESET()              LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_APB1H_FORCE_RESET()               LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_ALL)
#define __HAL_RCC_LPUART1_FORCE_RESET()             LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_LPUART1)
#define __HAL_RCC_LPTIM2_FORCE_RESET()              LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_FORCE_RESET()              LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_LPTIM3)

#define __HAL_RCC_APB1_FORCE_RESET() do {                                \
                                           __HAL_RCC_APB1L_FORCE_RESET();\
                                           __HAL_RCC_APB1H_FORCE_RESET();\
                                        } while(0U)

#define __HAL_RCC_APB1L_RELEASE_RESET()             LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_ALL)
#define __HAL_RCC_TIM2_RELEASE_RESET()              LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_USART2_RELEASE_RESET()            LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_SPI2_RELEASE_RESET()              LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_I2C1_RELEASE_RESET()              LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_RELEASE_RESET()              LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_RELEASE_RESET()              LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_RELEASE_RESET()               LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_RELEASE_RESET()            LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_APB1H_RELEASE_RESET()             LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_ALL)
#define __HAL_RCC_LPUART1_RELEASE_RESET()           LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_LPUART1)
#define __HAL_RCC_LPTIM2_RELEASE_RESET()            LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_RELEASE_RESET()            LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_LPTIM3)

#define __HAL_RCC_APB1_RELEASE_RESET() do {                                \
                                            __HAL_RCC_APB1L_RELEASE_RESET();\
                                            __HAL_RCC_APB1H_RELEASE_RESET();\
                                          } while(0U)
/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset APB2 Peripheral Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB2_FORCE_RESET()                LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_ALL)
#define __HAL_RCC_ADC_FORCE_RESET()                 LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_FORCE_RESET()                LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_FORCE_RESET()                LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_FORCE_RESET()              LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_FORCE_RESET()               LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_FORCE_RESET()               LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM17)

#define __HAL_RCC_APB2_RELEASE_RESET()              LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_ALL)
#define __HAL_RCC_ADC_RELEASE_RESET()               LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_RELEASE_RESET()              LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_RELEASE_RESET()              LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_RELEASE_RESET()            LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_RELEASE_RESET()             LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_RELEASE_RESET()             LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM17)
/**
  * @}
  */

/** @defgroup RCC_APB3_Force_Release_Reset APB3 Peripheral Force Release Reset
  * @brief  Force or release APB3 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB3_FORCE_RESET()                LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_ALL)
#define __HAL_RCC_SUBGHZSPI_FORCE_RESET()           LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_SUBGHZSPI)

#define __HAL_RCC_APB3_RELEASE_RESET()              LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_ALL)
#define __HAL_RCC_SUBGHZSPI_RELEASE_RESET()         LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_SUBGHZSPI)

/* Aliases used by CubeMX for HAL SUBGHZ Init, MspInit and DeInit generation */
#define __HAL_RCC_SUBGHZ_FORCE_RESET()              __HAL_RCC_SUBGHZSPI_FORCE_RESET()
#define __HAL_RCC_SUBGHZ_RELEASE_RESET()            __HAL_RCC_SUBGHZSPI_RELEASE_RESET()
/**
  * @}
  */

/** @defgroup RCC_SUBGHZ_Force_Release_Reset SUBGHZ Radio Force Release Reset
  * @brief  Force or release SUBGHZ Radio reset.
  * @{
  */
#define __HAL_RCC_SUBGHZ_RADIO_FORCE_RESET()              SET_BIT(RCC->CSR, RCC_CSR_RFRST)

#define __HAL_RCC_SUBGHZ_RADIO_RELEASE_RESET()            CLEAR_BIT(RCC->CSR, RCC_CSR_RFRST)
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_DMA1_CLK_SLEEP_ENABLE()           LL_C2_AHB1_GRP1_EnableClockSleep(LL_C2_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_CLK_SLEEP_ENABLE()           LL_C2_AHB1_GRP1_EnableClockSleep(LL_C2_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_CLK_SLEEP_ENABLE()        LL_C2_AHB1_GRP1_EnableClockSleep(LL_C2_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()            LL_C2_AHB1_GRP1_EnableClockSleep(LL_C2_AHB1_GRP1_PERIPH_CRC)

#define __HAL_RCC_DMA1_CLK_SLEEP_DISABLE()          LL_C2_AHB1_GRP1_DisableClockSleep(LL_C2_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_CLK_SLEEP_DISABLE()          LL_C2_AHB1_GRP1_DisableClockSleep(LL_C2_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_CLK_SLEEP_DISABLE()       LL_C2_AHB1_GRP1_DisableClockSleep(LL_C2_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()           LL_C2_AHB1_GRP1_DisableClockSleep(LL_C2_AHB1_GRP1_PERIPH_CRC)
#else
#define __HAL_RCC_DMA1_CLK_SLEEP_ENABLE()           LL_AHB1_GRP1_EnableClockSleep(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_CLK_SLEEP_ENABLE()           LL_AHB1_GRP1_EnableClockSleep(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_CLK_SLEEP_ENABLE()        LL_AHB1_GRP1_EnableClockSleep(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()            LL_AHB1_GRP1_EnableClockSleep(LL_AHB1_GRP1_PERIPH_CRC)

#define __HAL_RCC_DMA1_CLK_SLEEP_DISABLE()          LL_AHB1_GRP1_DisableClockSleep(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_CLK_SLEEP_DISABLE()          LL_AHB1_GRP1_DisableClockSleep(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_CLK_SLEEP_DISABLE()       LL_AHB1_GRP1_DisableClockSleep(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()           LL_AHB1_GRP1_DisableClockSleep(LL_AHB1_GRP1_PERIPH_CRC)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()          LL_C2_AHB2_GRP1_EnableClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()          LL_C2_AHB2_GRP1_EnableClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()          LL_C2_AHB2_GRP1_EnableClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE()          LL_C2_AHB2_GRP1_EnableClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOH)

#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()         LL_C2_AHB2_GRP1_DisableClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()         LL_C2_AHB2_GRP1_DisableClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()         LL_C2_AHB2_GRP1_DisableClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE()         LL_C2_AHB2_GRP1_DisableClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOH)
#else
#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()          LL_AHB2_GRP1_EnableClockSleep(LL_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()          LL_AHB2_GRP1_EnableClockSleep(LL_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()          LL_AHB2_GRP1_EnableClockSleep(LL_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE()          LL_AHB2_GRP1_EnableClockSleep(LL_AHB2_GRP1_PERIPH_GPIOH)

#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()         LL_AHB2_GRP1_DisableClockSleep(LL_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()         LL_AHB2_GRP1_DisableClockSleep(LL_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()         LL_AHB2_GRP1_DisableClockSleep(LL_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE()         LL_AHB2_GRP1_DisableClockSleep(LL_AHB2_GRP1_PERIPH_GPIOH)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_PKA_CLK_SLEEP_ENABLE()            LL_C2_AHB3_GRP1_EnableClockSleep(LL_C2_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_CLK_SLEEP_ENABLE()            LL_C2_AHB3_GRP1_EnableClockSleep(LL_C2_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()            LL_C2_AHB3_GRP1_EnableClockSleep(LL_C2_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()          LL_C2_AHB3_GRP1_EnableClockSleep(LL_C2_AHB3_GRP1_PERIPH_SRAM1)
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()          LL_C2_AHB3_GRP1_EnableClockSleep(LL_C2_AHB3_GRP1_PERIPH_SRAM2)
#define __HAL_RCC_FLASH_CLK_SLEEP_ENABLE()          LL_C2_AHB3_GRP1_EnableClockSleep(LL_C2_AHB3_GRP1_PERIPH_FLASH)

#define __HAL_RCC_PKA_CLK_SLEEP_DISABLE()           LL_C2_AHB3_GRP1_DisableClockSleep(LL_C2_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_CLK_SLEEP_DISABLE()           LL_C2_AHB3_GRP1_DisableClockSleep(LL_C2_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()           LL_C2_AHB3_GRP1_DisableClockSleep(LL_C2_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()         LL_C2_AHB3_GRP1_DisableClockSleep(LL_C2_AHB3_GRP1_PERIPH_SRAM1)
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()         LL_C2_AHB3_GRP1_DisableClockSleep(LL_C2_AHB3_GRP1_PERIPH_SRAM2)
#define __HAL_RCC_FLASH_CLK_SLEEP_DISABLE()         LL_C2_AHB3_GRP1_DisableClockSleep(LL_C2_AHB3_GRP1_PERIPH_FLASH)
#else
#define __HAL_RCC_PKA_CLK_SLEEP_ENABLE()            LL_AHB3_GRP1_EnableClockSleep(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_CLK_SLEEP_ENABLE()            LL_AHB3_GRP1_EnableClockSleep(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()            LL_AHB3_GRP1_EnableClockSleep(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()          LL_AHB3_GRP1_EnableClockSleep(LL_AHB3_GRP1_PERIPH_SRAM1)
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()          LL_AHB3_GRP1_EnableClockSleep(LL_AHB3_GRP1_PERIPH_SRAM2)
#define __HAL_RCC_FLASH_CLK_SLEEP_ENABLE()          LL_AHB3_GRP1_EnableClockSleep(LL_AHB3_GRP1_PERIPH_FLASH)

#define __HAL_RCC_PKA_CLK_SLEEP_DISABLE()           LL_AHB3_GRP1_DisableClockSleep(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_CLK_SLEEP_DISABLE()           LL_AHB3_GRP1_DisableClockSleep(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()           LL_AHB3_GRP1_DisableClockSleep(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()         LL_AHB3_GRP1_DisableClockSleep(LL_AHB3_GRP1_PERIPH_SRAM1)
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()         LL_AHB3_GRP1_DisableClockSleep(LL_AHB3_GRP1_PERIPH_SRAM2)
#define __HAL_RCC_FLASH_CLK_SLEEP_DISABLE()         LL_AHB3_GRP1_DisableClockSleep(LL_AHB3_GRP1_PERIPH_FLASH)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()           LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()         LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()           LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()         LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()           LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()           LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()           LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_CLK_SLEEP_ENABLE()            LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()         LL_C2_APB1_GRP1_EnableClockSleep(LL_C2_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE()        LL_C2_APB1_GRP2_EnableClockSleep(LL_C2_APB1_GRP2_PERIPH_LPUART1)
#define __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE()         LL_C2_APB1_GRP2_EnableClockSleep(LL_C2_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_ENABLE()         LL_C2_APB1_GRP2_EnableClockSleep(LL_C2_APB1_GRP2_PERIPH_LPTIM3)

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()          LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()        LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE()        LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()          LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()          LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()          LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()          LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_CLK_SLEEP_DISABLE()          LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()        LL_C2_APB1_GRP1_DisableClockSleep(LL_C2_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE()       LL_C2_APB1_GRP2_DisableClockSleep(LL_C2_APB1_GRP2_PERIPH_LPUART1)
#define __HAL_RCC_LPTIM2_CLK_SLEEP_DISABLE()        LL_C2_APB1_GRP2_DisableClockSleep(LL_C2_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_DISABLE()        LL_C2_APB1_GRP2_DisableClockSleep(LL_C2_APB1_GRP2_PERIPH_LPTIM3)
#else
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()           LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()         LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()           LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()         LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()           LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()           LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()           LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_CLK_SLEEP_ENABLE()            LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()         LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE()        LL_APB1_GRP2_EnableClockSleep(LL_APB1_GRP2_PERIPH_LPUART1)
#define __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE()         LL_APB1_GRP2_EnableClockSleep(LL_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_ENABLE()         LL_APB1_GRP2_EnableClockSleep(LL_APB1_GRP2_PERIPH_LPTIM3)

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()          LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()        LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE()        LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()          LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()          LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()          LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()          LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_CLK_SLEEP_DISABLE()           LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()        LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE()       LL_APB1_GRP2_DisableClockSleep(LL_APB1_GRP2_PERIPH_LPUART1)
#define __HAL_RCC_LPTIM2_CLK_SLEEP_DISABLE()        LL_APB1_GRP2_DisableClockSleep(LL_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_DISABLE()        LL_APB1_GRP2_DisableClockSleep(LL_APB1_GRP2_PERIPH_LPTIM3)
#endif /* CORE_CM0PLUS */

#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()           LL_APB1_GRP1_EnableClockSleep(LL_APB1_GRP1_PERIPH_WWDG)

#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()          LL_APB1_GRP1_DisableClockSleep(LL_APB1_GRP1_PERIPH_WWDG)
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_ADC_CLK_SLEEP_ENABLE()            LL_C2_APB2_GRP1_EnableClockSleep(LL_C2_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()           LL_C2_APB2_GRP1_EnableClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()           LL_C2_APB2_GRP1_EnableClockSleep(LL_C2_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()         LL_C2_APB2_GRP1_EnableClockSleep(LL_C2_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()          LL_C2_APB2_GRP1_EnableClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_CLK_SLEEP_ENABLE()          LL_C2_APB2_GRP1_EnableClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM17)

#define __HAL_RCC_ADC_CLK_SLEEP_DISABLE()           LL_C2_APB2_GRP1_DisableClockSleep(LL_C2_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()          LL_C2_APB2_GRP1_DisableClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()          LL_C2_APB2_GRP1_DisableClockSleep(LL_C2_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE()        LL_C2_APB2_GRP1_DisableClockSleep(LL_C2_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()         LL_C2_APB2_GRP1_DisableClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_CLK_SLEEP_DISABLE()         LL_C2_APB2_GRP1_DisableClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM17)
#else
#define __HAL_RCC_ADC_CLK_SLEEP_ENABLE()            LL_APB2_GRP1_EnableClockSleep(LL_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()           LL_APB2_GRP1_EnableClockSleep(LL_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()           LL_APB2_GRP1_EnableClockSleep(LL_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()         LL_APB2_GRP1_EnableClockSleep(LL_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()          LL_APB2_GRP1_EnableClockSleep(LL_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_CLK_SLEEP_ENABLE()          LL_APB2_GRP1_EnableClockSleep(LL_APB2_GRP1_PERIPH_TIM17)

#define __HAL_RCC_ADC_CLK_SLEEP_DISABLE()           LL_APB2_GRP1_DisableClockSleep(LL_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()          LL_APB2_GRP1_DisableClockSleep(LL_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()          LL_APB2_GRP1_DisableClockSleep(LL_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE()        LL_APB2_GRP1_DisableClockSleep(LL_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()         LL_APB2_GRP1_DisableClockSleep(LL_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_CLK_SLEEP_DISABLE()         LL_APB2_GRP1_DisableClockSleep(LL_APB2_GRP1_PERIPH_TIM17)
#endif /* CORE_CM0PLUS */
/**
  * @}
  */

/** @defgroup RCC_APB3_Clock_Sleep_Enable_Disable APB3 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_SUBGHZSPI_CLK_SLEEP_ENABLE()      LL_C2_APB3_GRP1_EnableClockSleep(LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI)

#define __HAL_RCC_SUBGHZSPI_CLK_SLEEP_DISABLE()     LL_C2_APB3_GRP1_DisableClockSleep(LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI)
#else
#define __HAL_RCC_SUBGHZSPI_CLK_SLEEP_ENABLE()      LL_APB3_GRP1_EnableClockSleep(LL_APB3_GRP1_PERIPH_SUBGHZSPI)

#define __HAL_RCC_SUBGHZSPI_CLK_SLEEP_DISABLE()     LL_APB3_GRP1_DisableClockSleep(LL_APB3_GRP1_PERIPH_SUBGHZSPI)
#endif /* CORE_CM0PLUS */

/* Aliases used by CubeMX for HAL SUBGHZ Init, MspInit and DeInit generation */
#define __HAL_RCC_SUBGHZ_CLK_SLEEP_ENABLE()         __HAL_RCC_SUBGHZSPI_CLK_SLEEP_ENABLE()
#define __HAL_RCC_SUBGHZ_CLK_SLEEP_DISABLE()        __HAL_RCC_SUBGHZSPI_CLK_SLEEP_DISABLE()
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_DMA1_IS_CLK_SLEEP_ENABLED()       LL_C2_AHB1_GRP1_IsEnabledClockSleep(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_IS_CLK_SLEEP_ENABLED()       LL_C2_AHB1_GRP1_IsEnabledClockSleep(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_IS_CLK_SLEEP_ENABLED()    LL_C2_AHB1_GRP1_IsEnabledClockSleep(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_IS_CLK_SLEEP_ENABLED()        LL_C2_AHB1_GRP1_IsEnabledClockSleep(LL_AHB1_GRP1_PERIPH_CRC)
#else
#define __HAL_RCC_DMA1_IS_CLK_SLEEP_ENABLED()       LL_AHB1_GRP1_IsEnabledClockSleep(LL_AHB1_GRP1_PERIPH_DMA1)
#define __HAL_RCC_DMA2_IS_CLK_SLEEP_ENABLED()       LL_AHB1_GRP1_IsEnabledClockSleep(LL_AHB1_GRP1_PERIPH_DMA2)
#define __HAL_RCC_DMAMUX1_IS_CLK_SLEEP_ENABLED()    LL_AHB1_GRP1_IsEnabledClockSleep(LL_AHB1_GRP1_PERIPH_DMAMUX1)
#define __HAL_RCC_CRC_IS_CLK_SLEEP_ENABLED()        LL_AHB1_GRP1_IsEnabledClockSleep(LL_AHB1_GRP1_PERIPH_CRC)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_ENABLED()      LL_C2_AHB2_GRP1_IsEnabledClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_ENABLED()      LL_C2_AHB2_GRP1_IsEnabledClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_ENABLED()      LL_C2_AHB2_GRP1_IsEnabledClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_IS_CLK_SLEEP_ENABLED()      LL_C2_AHB2_GRP1_IsEnabledClockSleep(LL_C2_AHB2_GRP1_PERIPH_GPIOH)
#else
#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_ENABLED()      LL_AHB2_GRP1_IsEnabledClockSleep(LL_AHB2_GRP1_PERIPH_GPIOA)
#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_ENABLED()      LL_AHB2_GRP1_IsEnabledClockSleep(LL_AHB2_GRP1_PERIPH_GPIOB)
#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_ENABLED()      LL_AHB2_GRP1_IsEnabledClockSleep(LL_AHB2_GRP1_PERIPH_GPIOC)
#define __HAL_RCC_GPIOH_IS_CLK_SLEEP_ENABLED()      LL_AHB2_GRP1_IsEnabledClockSleep(LL_AHB2_GRP1_PERIPH_GPIOH)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_PKA_IS_CLK_SLEEP_ENABLED()        LL_C2_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_IS_CLK_SLEEP_ENABLED()        LL_C2_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_IS_CLK_SLEEP_ENABLED()        LL_C2_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_SRAM1_IS_CLK_SLEEP_ENABLED()      LL_C2_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_SRAM1)
#define __HAL_RCC_SRAM2_IS_CLK_SLEEP_ENABLED()      LL_C2_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_SRAM2)
#define __HAL_RCC_FLASH_IS_CLK_SLEEP_ENABLED()      LL_C2_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_FLASH)
#else
#define __HAL_RCC_PKA_IS_CLK_SLEEP_ENABLED()        LL_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_PKA)
#define __HAL_RCC_AES_IS_CLK_SLEEP_ENABLED()        LL_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_AES)
#define __HAL_RCC_RNG_IS_CLK_SLEEP_ENABLED()        LL_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_RNG)
#define __HAL_RCC_SRAM1_IS_CLK_SLEEP_ENABLED()      LL_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_SRAM1)
#define __HAL_RCC_SRAM2_IS_CLK_SLEEP_ENABLED()      LL_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_SRAM2)
#define __HAL_RCC_FLASH_IS_CLK_SLEEP_ENABLED()      LL_AHB3_GRP1_IsEnabledClockSleep(LL_AHB3_GRP1_PERIPH_FLASH)
#endif /* CORE_CM0PLUS */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_TIM2_IS_CLK_SLEEP_ENABLED()       LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_ENABLED()     LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_USART2_IS_CLK_SLEEP_ENABLED()     LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_SPI2_IS_CLK_SLEEP_ENABLED()       LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_I2C1_IS_CLK_SLEEP_ENABLED()       LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_IS_CLK_SLEEP_ENABLED()       LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_IS_CLK_SLEEP_ENABLED()       LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_IS_CLK_SLEEP_ENABLED()        LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_IS_CLK_SLEEP_ENABLED()     LL_C2_APB1_GRP1_IsEnabledClockSleep(LL_C2_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPUART1_IS_CLK_SLEEP_ENABLED()    LL_C2_APB1_GRP2_IsEnabledClockSleep(LL_C2_APB1_GRP2_PERIPH_LPUART1)
#define __HAL_RCC_LPTIM2_IS_CLK_SLEEP_ENABLED()     LL_C2_APB1_GRP2_IsEnabledClockSleep(LL_C2_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_IS_CLK_SLEEP_ENABLED()     LL_C2_APB1_GRP2_IsEnabledClockSleep(LL_C2_APB1_GRP2_PERIPH_LPTIM3)
#else
#define __HAL_RCC_TIM2_IS_CLK_SLEEP_ENABLED()       LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_TIM2)
#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_ENABLED()     LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_RTCAPB)
#define __HAL_RCC_USART2_IS_CLK_SLEEP_ENABLED()     LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_USART2)
#define __HAL_RCC_SPI2_IS_CLK_SLEEP_ENABLED()       LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_SPI2)
#define __HAL_RCC_I2C1_IS_CLK_SLEEP_ENABLED()       LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_I2C1)
#define __HAL_RCC_I2C2_IS_CLK_SLEEP_ENABLED()       LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_I2C2)
#define __HAL_RCC_I2C3_IS_CLK_SLEEP_ENABLED()       LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_I2C3)
#define __HAL_RCC_DAC_IS_CLK_SLEEP_ENABLED()        LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_DAC)
#define __HAL_RCC_LPTIM1_IS_CLK_SLEEP_ENABLED()     LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_LPTIM1)

#define __HAL_RCC_LPUART1_IS_CLK_SLEEP_ENABLED()    LL_APB1_GRP2_IsEnabledClockSleep(LL_APB1_GRP2_PERIPH_LPUART1)
#define __HAL_RCC_LPTIM2_IS_CLK_SLEEP_ENABLED()     LL_APB1_GRP2_IsEnabledClockSleep(LL_APB1_GRP2_PERIPH_LPTIM2)
#define __HAL_RCC_LPTIM3_IS_CLK_SLEEP_ENABLED()     LL_APB1_GRP2_IsEnabledClockSleep(LL_APB1_GRP2_PERIPH_LPTIM3)
#endif /* CORE_CM0PLUS */

#define __HAL_RCC_WWDG_IS_CLK_SLEEP_ENABLED()       LL_APB1_GRP1_IsEnabledClockSleep(LL_APB1_GRP1_PERIPH_WWDG)
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
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_ADC_IS_CLK_SLEEP_ENABLED()        LL_C2_APB2_GRP1_IsEnabledClockSleep(LL_C2_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_IS_CLK_SLEEP_ENABLED()       LL_C2_APB2_GRP1_IsEnabledClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_IS_CLK_SLEEP_ENABLED()       LL_C2_APB2_GRP1_IsEnabledClockSleep(LL_C2_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_IS_CLK_SLEEP_ENABLED()     LL_C2_APB2_GRP1_IsEnabledClockSleep(LL_C2_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_IS_CLK_SLEEP_ENABLED()      LL_C2_APB2_GRP1_IsEnabledClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_IS_CLK_SLEEP_ENABLED()      LL_C2_APB2_GRP1_IsEnabledClockSleep(LL_C2_APB2_GRP1_PERIPH_TIM17)
#else
#define __HAL_RCC_ADC_IS_CLK_SLEEP_ENABLED()        LL_APB2_GRP1_IsEnabledClockSleep(LL_APB2_GRP1_PERIPH_ADC)
#define __HAL_RCC_TIM1_IS_CLK_SLEEP_ENABLED()       LL_APB2_GRP1_IsEnabledClockSleep(LL_APB2_GRP1_PERIPH_TIM1)
#define __HAL_RCC_SPI1_IS_CLK_SLEEP_ENABLED()       LL_APB2_GRP1_IsEnabledClockSleep(LL_APB2_GRP1_PERIPH_SPI1)
#define __HAL_RCC_USART1_IS_CLK_SLEEP_ENABLED()     LL_APB2_GRP1_IsEnabledClockSleep(LL_APB2_GRP1_PERIPH_USART1)
#define __HAL_RCC_TIM16_IS_CLK_SLEEP_ENABLED()      LL_APB2_GRP1_IsEnabledClockSleep(LL_APB2_GRP1_PERIPH_TIM16)
#define __HAL_RCC_TIM17_IS_CLK_SLEEP_ENABLED()      LL_APB2_GRP1_IsEnabledClockSleep(LL_APB2_GRP1_PERIPH_TIM17)
#endif /* CORE_CM0PLUS */
/**
  * @}
  */

/** @defgroup RCC_APB3_Clock_Sleep_Enable_Disable_Status APB3 Peripheral Clock Sleep Enabled or Disabled Status
  * @brief  Check whether the APB3 peripheral clock during Low Power (Sleep) mode is enabled or not.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#if defined(CORE_CM0PLUS)
#define __HAL_RCC_SUBGHZSPI_IS_CLK_SLEEP_ENABLED()    \
  LL_C2_APB3_GRP1_IsEnabledClockSleep(LL_C2_APB3_GRP1_PERIPH_SUBGHZSPI)
#else
#define __HAL_RCC_SUBGHZSPI_IS_CLK_SLEEP_ENABLED()    \
  LL_APB3_GRP1_IsEnabledClockSleep(LL_APB3_GRP1_PERIPH_SUBGHZSPI)
#endif /* CORE_CM0PLUS */

/* Aliases used by CubeMX for HAL SUBGHZ Init, MspInit and DeInit generation */
#define __HAL_RCC_SUBGHZ_IS_CLK_SLEEP_ENABLED()       __HAL_RCC_SUBGHZSPI_IS_CLK_SLEEP_ENABLED()
/**
  * @}
  */

/** @defgroup RCC_Backup_Domain_Reset RCC Backup Domain Reset
  * @{
  */

/** @brief  Macros to force or release the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_CSR register.
  * @note   The SRAM2 is not affected by this reset.
  * @retval None
  */
#define __HAL_RCC_BACKUPRESET_FORCE()   LL_RCC_ForceBackupDomainReset()
#define __HAL_RCC_BACKUPRESET_RELEASE() LL_RCC_ReleaseBackupDomainReset()
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Configuration RCC RTC Clock Configuration
  * @{
  */

/** @brief  Macros to enable or disable the RTC clock.
  * @note   As the RTC is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the RTC
  *         (to be done once after reset).
  * @note   These macros must be used after the RTC clock source was selected.
  * @retval None
  */
#define __HAL_RCC_RTC_ENABLE()         LL_RCC_EnableRTC()
#define __HAL_RCC_RTC_DISABLE()        LL_RCC_DisableRTC()
/**
  * @}
  */

/** @brief  Macros to enable the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP, STANDBY or SHUTDOWN modes.
  *         It is enabled by hardware to force the HSI oscillator ON when STOPWUCK=1
  *         or HSIASFS = 1 when leaving Stop modes, or in case of failure of the HSE
  *         crystal oscillator and Security System CSS is enabled.
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.
  * @retval None
  */
#define __HAL_RCC_HSI_ENABLE()  LL_RCC_HSI_Enable()

/** @brief  Macro to disable the Internal High Speed oscillator (HSI).
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_HSI_DISABLE() LL_RCC_HSI_Disable()

/** @brief  Macro to adjust the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between Min_data=0 and Max_Data=127.
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__)  \
  LL_RCC_HSI_SetCalibTrimming(__HSICALIBRATIONVALUE__)

/**
  * @brief    Macros to enable or disable the wakeup the Internal High Speed oscillator (HSI)
  *           in parallel to the Internal Multi Speed oscillator (MSI) used at system wakeup.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSIAUTOMATIC_START_ENABLE()   LL_RCC_HSI_EnableAutoFromStop()
#define __HAL_RCC_HSIAUTOMATIC_START_DISABLE()  LL_RCC_HSI_DisableAutoFromStop()

/**
  * @brief    Macros to enable or disable the force of the Internal High Speed oscillator (HSI)
  *           in STOP mode to be quickly available as kernel clock for USARTs and I2Cs.
  * @note     Keeping the HSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the HSI startup time.
  * @note     The enable of this function has not effect on the HSION bit.
  * @retval None
  */
#define __HAL_RCC_HSISTOP_ENABLE()     LL_RCC_HSI_EnableInStopMode()
#define __HAL_RCC_HSISTOP_DISABLE()    LL_RCC_HSI_DisableInStopMode()

/**
  * @brief  Macros to enable or disable the Internal Multi Speed oscillator (MSI).
  * @note   The MSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after
  *         startup from Reset, wakeup from STOP and STANDBY mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  * @note   MSI can not be stopped if it is used as system clock source.
  *         In this case, you have to select another source of the system
  *         clock then stop the MSI.
  * @note   After enabling the MSI, the application software should wait on
  *         MSIRDY flag to be set indicating that MSI clock is stable and can
  *         be used as system clock source.
  * @note   When the MSI is stopped, MSIRDY flag goes low after 6 MSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_MSI_ENABLE()  LL_RCC_MSI_Enable()
#define __HAL_RCC_MSI_DISABLE() LL_RCC_MSI_Disable()

/** @brief  Macro to adjust the Internal Multi Speed oscillator (MSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal MSI RC.
  *         Refer to the Application Note AN3300 for more details on how to
  *         calibrate the MSI.
  * @param  __MSICALIBRATIONVALUE__  specifies the calibration trimming value
  *         (default is @ref RCC_MSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 255.
  * @retval None
  */
#define __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(__MSICALIBRATIONVALUE__)  \
  LL_RCC_MSI_SetCalibTrimming(__MSICALIBRATIONVALUE__)

/**
  * @brief  Macro configures the Internal Multi Speed oscillator (MSI) clock range in run mode
  * @note     After restart from Reset , the MSI clock is around 4 MHz.
  *           After stop the startup clock can be MSI (at any of its possible
  *           frequencies, the one that was used before entering stop mode) or HSI.
  *          After Standby its frequency can be selected between 4 possible values
  *          (1, 2, 4 or 8 MHz).
  * @note     MSIRANGE can be modified when MSI is OFF (MSION=0) or when MSI is ready
  *          (MSIRDY=1).
  * @note    The MSI clock range after reset can be modified on the fly.
  * @param  __MSIRANGEVALUE__ specifies the MSI clock range.
  *         This parameter must be one of the following values:
  *            @arg @ref RCC_MSIRANGE_0  MSI clock is around 100 KHz
  *            @arg @ref RCC_MSIRANGE_1  MSI clock is around 200 KHz
  *            @arg @ref RCC_MSIRANGE_2  MSI clock is around 400 KHz
  *            @arg @ref RCC_MSIRANGE_3  MSI clock is around 800 KHz
  *            @arg @ref RCC_MSIRANGE_4  MSI clock is around 1 MHz
  *            @arg @ref RCC_MSIRANGE_5  MSI clock is around 2 MHz
  *            @arg @ref RCC_MSIRANGE_6  MSI clock is around 4 MHz (default after Reset)
  *            @arg @ref RCC_MSIRANGE_7  MSI clock is around 8 MHz
  *            @arg @ref RCC_MSIRANGE_8  MSI clock is around 16 MHz
  *            @arg @ref RCC_MSIRANGE_9  MSI clock is around 24 MHz
  *            @arg @ref RCC_MSIRANGE_10  MSI clock is around 32 MHz
  *            @arg @ref RCC_MSIRANGE_11  MSI clock is around 48 MHz
  * @retval None
  */
#define __HAL_RCC_MSI_RANGE_CONFIG(__MSIRANGEVALUE__)  do {                                                            \
                                                            SET_BIT(RCC->CR, RCC_CR_MSIRGSEL);                         \
                                                            MODIFY_REG(RCC->CR, RCC_CR_MSIRANGE, (__MSIRANGEVALUE__)); \
                                                          } while(0)

/**
  * @brief  Macro configures the Internal Multi Speed oscillator (MSI) clock range after Standby mode
  *         After Standby its frequency can be selected between 4 possible values (1, 2, 4 or 8 MHz).
  * @param  __MSIRANGEVALUE__ specifies the MSI clock range.
  *         This parameter must be one of the following values:
  *            @arg @ref RCC_MSIRANGE_4  MSI clock is around 1 MHz
  *            @arg @ref RCC_MSIRANGE_5  MSI clock is around 2 MHz
  *            @arg @ref RCC_MSIRANGE_6  MSI clock is around 4 MHz (default after Reset)
  *            @arg @ref RCC_MSIRANGE_7  MSI clock is around 8 MHz
  * @retval None
  */
#define __HAL_RCC_MSI_STANDBY_RANGE_CONFIG(__MSIRANGEVALUE__) \
  MODIFY_REG(RCC->CSR, RCC_CSR_MSISRANGE, (__MSIRANGEVALUE__) << 4U)

/** @brief  Macro to get the Internal Multi Speed oscillator (MSI) clock range in run mode
  * @retval MSI clock range.
  *         This parameter must be one of the following values:
  *            @arg @ref RCC_MSIRANGE_0  MSI clock is around 100 KHz
  *            @arg @ref RCC_MSIRANGE_1  MSI clock is around 200 KHz
  *            @arg @ref RCC_MSIRANGE_2  MSI clock is around 400 KHz
  *            @arg @ref RCC_MSIRANGE_3  MSI clock is around 800 KHz
  *            @arg @ref RCC_MSIRANGE_4  MSI clock is around 1 MHz
  *            @arg @ref RCC_MSIRANGE_5  MSI clock is around 2 MHz
  *            @arg @ref RCC_MSIRANGE_6  MSI clock is around 4 MHz (default after Reset)
  *            @arg @ref RCC_MSIRANGE_7  MSI clock is around 8 MHz
  *            @arg @ref RCC_MSIRANGE_8  MSI clock is around 16 MHz
  *            @arg @ref RCC_MSIRANGE_9  MSI clock is around 24 MHz
  *            @arg @ref RCC_MSIRANGE_10  MSI clock is around 32 MHz
  *            @arg @ref RCC_MSIRANGE_11  MSI clock is around 48 MHz
  */
#define __HAL_RCC_GET_MSI_RANGE()  ((READ_BIT(RCC->CR, RCC_CR_MSIRGSEL) != 0U) ?       \
                                    (uint32_t)(READ_BIT(RCC->CR, RCC_CR_MSIRANGE)) :  \
                                    (uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_MSISRANGE) >> 4))

/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI_ENABLE()         LL_RCC_LSI_Enable()
#define __HAL_RCC_LSI_DISABLE()        LL_RCC_LSI_Disable()

/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   Transition RCC_HSE_BYPASS_PWR to RCC_HSE_ON and RCC_HSE_ON to
  *         RCC_HSE_BYPASS_PWR are not supported by this macro. User should
  *         request a transition to RCC_HSE_OFF first and then RCC_HSE_ON or
  *         RCC_HSE_BYPASS_PWR.
  * @note   After enabling the HSE (RCC_HSE_ON, RCC_HSE_BYPASS_PWR),
  *         the application software should wait on HSERDY flag to be set indicating
  *         that HSE clock is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @note   PB0 must be configured in analog mode prior enabling the HSE with
  *         RCC_HSE_BYPASS_PWR.
  * @param  __STATE__  specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_HSE_OFF         Turn OFF the HSE oscillator, HSERDY flag
  *                                          goes low after 6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON          Turn ON the HSE oscillator.
  *            @arg @ref RCC_HSE_BYPASS_PWR  HSE32 driven from an external TCXO powered by the PB0-VDDTCXO pin.
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)  do {                                            \
                                              if((__STATE__) == RCC_HSE_ON)              \
                                              {                                          \
                                                LL_RCC_HSE_Enable();                     \
                                              }                                          \
                                              else if((__STATE__) == RCC_HSE_BYPASS_PWR) \
                                              {                                          \
                                                LL_RCC_HSE_EnableTcxo();                 \
                                                LL_RCC_HSE_Enable();                     \
                                              }                                          \
                                              else                                       \
                                              {                                          \
                                                LL_RCC_HSE_Disable();                    \
                                                LL_RCC_HSE_DisableTcxo();                \
                                              }                                          \
                                            } while(0U)

/** @brief  Macros to enable or disable the HSE Prescaler
  * @note   HSE prescaler shall be enabled when HSE is used as
  *         system clock source and Voltage scaling range 1
  *         (Low-power range) is selected.
  * @retval None
  */
#define __HAL_RCC_HSE_DIV2_ENABLE()         LL_RCC_HSE_EnableDiv2()
#define __HAL_RCC_HSE_DIV2_DISABLE()        LL_RCC_HSE_DisableDiv2()

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE).
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this macro. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_BYPASS), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  __STATE__  specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF  Turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON  Turn ON the LSE oscillator.
  *            @arg @ref RCC_LSE_BYPASS  LSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__)  do {                                          \
                                              if((__STATE__) == RCC_LSE_ON)            \
                                              {                                        \
                                                LL_RCC_LSE_Enable();                   \
                                              }                                        \
                                              else if((__STATE__) == RCC_LSE_BYPASS)   \
                                              {                                        \
                                                LL_RCC_LSE_EnableBypass();             \
                                                LL_RCC_LSE_Enable();                   \
                                              }                                        \
                                              else                                     \
                                              {                                        \
                                                LL_RCC_LSE_Disable();                  \
                                                LL_RCC_LSE_DisableBypass();            \
                                              }                                        \
                                            } while(0U)

/** @brief  Macro to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it cannot be changed unless the
  *         Backup domain is reset using @ref __HAL_RCC_BACKUPRESET_FORCE() macro, or by
  *         a Power On Reset (POR).
  *
  * @param  __RTC_CLKSOURCE__  specifies the RTC clock source.
  *         This parameter can be one of the following values:*
  *            @arg @ref RCC_RTCCLKSOURCE_NONE  none clock selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  *
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *         RTC clock source).
  * @retval None
  */
#define __HAL_RCC_RTC_CONFIG(__RTC_CLKSOURCE__)  LL_RCC_SetRTCClockSource(__RTC_CLKSOURCE__)

/** @brief  Macro to get the RTC clock source.
  * @retval The returned value can be one of the following:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE  none clock selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  */
#define  __HAL_RCC_GET_RTC_SOURCE() LL_RCC_GetRTCClockSource()

/** @brief  Macros to enable or disable the main PLL.
  * @note   After enabling the main PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL can not be disabled if it is used as system clock source
  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
  * @retval None
  */
#define __HAL_RCC_PLL_ENABLE()         LL_RCC_PLL_Enable()
#define __HAL_RCC_PLL_DISABLE()        LL_RCC_PLL_Disable()

/** @brief  Macro to configure the PLL clock source.
  * @note   This function must be used only when the main PLL is disabled.
  * @param  __PLLSOURCE__  specifies the PLL entry clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_NONE  No clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_MSI  MSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL clock entry
  * @retval None
  *
  */
#define __HAL_RCC_PLL_PLLSOURCE_CONFIG(__PLLSOURCE__) \
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC, (__PLLSOURCE__))
/**
  * @brief  Macro to configure the main PLL clock source, multiplication and division factors.
  * @note   This function must be used only when the main PLL is disabled.
  *
  * @param  __PLLSOURCE__  specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_NONE  No clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_MSI  MSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL clock entry
  *
  * @param  __PLLM__  specifies the division factor for PLL VCO input clock.
  *         This parameter must be a value of @ref RCC_PLLM_Clock_Divider.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 2.66 to 16 MHz. It is recommended to select a frequency
  *         of 16 MHz to limit PLL jitter.
  *
  * @param  __PLLN__  specifies the multiplication factor for PLL VCO output clock.
  *         This parameter must be a number between 6 and 127.
  * @note   You have to set the PLLN parameter correctly to ensure that the VCO
  *         output frequency is between 96 and 344 MHz.
  *
  * @param  __PLLP__  specifies the division factor for ADC clock.
  *         This parameter must be a value of @ref RCC_PLLP_Clock_Divider.
  *
  * @param  __PLLQ__  specifies the division factor for I2S2 and RNG clocks.
  *         This parameter must be a value of @ref RCC_PLLQ_Clock_Divider
  *
  * @note   RNG need a frequency lower than or equal to 48 MHz to work correctly.
  *
  * @param  __PLLR__  specifies the division factor for the main system clock.
  *         This parameter must be a value of @ref RCC_PLLR_Clock_Divider
  * @note   You have to set the PLLR parameter correctly to not exceed 48 MHZ.
  * @retval None
  */
#define __HAL_RCC_PLL_CONFIG(__PLLSOURCE__, __PLLM__, __PLLN__, __PLLP__, __PLLQ__,__PLLR__ ) \
  MODIFY_REG(RCC->PLLCFGR,                                                    \
             (RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN |      \
              RCC_PLLCFGR_PLLP   | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLR),      \
             ((uint32_t) (__PLLSOURCE__)                      |               \
              (uint32_t) (__PLLM__)                           |               \
              (uint32_t) ((__PLLN__) << RCC_PLLCFGR_PLLN_Pos) |               \
              (uint32_t) (__PLLP__)                           |               \
              (uint32_t) (__PLLQ__)                           |               \
              (uint32_t) (__PLLR__)))

/** @brief  Macro to get the oscillator used as PLL clock source.
  * @retval The oscillator used as PLL clock source. The returned value can be one
  *         of the following:
  *              @arg @ref RCC_PLLSOURCE_NONE No oscillator is used as PLL clock source.
  *              @arg @ref RCC_PLLSOURCE_MSI MSI oscillator is used as PLL clock source.
  *              @arg @ref RCC_PLLSOURCE_HSI HSI oscillator is used as PLL clock source.
  *              @arg @ref RCC_PLLSOURCE_HSE HSE oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE()  LL_RCC_PLL_GetMainSource()

/**
  * @brief  Enable or disable each clock output (RCC_PLL_SYSCLK, RCC_PLL_I2S2CLK, RCC_PLL_RNGCLK, RCC_PLL_ADCCLK)
  * @note   Enabling/disabling clock outputs RCC_PLL_I2S2CLK, RCC_PLL_RNGCLK and RCC_PLL_ADCCLK can be done at anytime
  *         without the need to stop the PLL in order to save power. But RCC_PLL_SYSCLK cannot
  *         be stopped if used as System Clock.
  * @param  __PLLCLOCKOUT__  specifies the PLL clock to be output.
  *          This parameter can be one or a combination of the following values:
  *            @arg @ref RCC_PLL_ADCCLK  This clock is used to generate the clock for ADC
  *            @arg @ref RCC_PLL_I2S2CLK  This Clock is used to generate the clock for the I2S
  *            @arg @ref RCC_PLL_RNGCLK  This clock is used to generate the clock for RNG
  *            @arg @ref RCC_PLL_SYSCLK  This Clock is used to generate the high speed system clock (up to 48 MHz)
  * @retval None
  */
#define __HAL_RCC_PLLCLKOUT_ENABLE(__PLLCLOCKOUT__)   SET_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

#define __HAL_RCC_PLLCLKOUT_DISABLE(__PLLCLOCKOUT__)  CLEAR_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

/**
  * @brief  Get clock output enable status (RCC_PLL_SYSCLK, RCC_PLL_I2S2CLK, RCC_PLL_RNGCLK, RCC_PLL_ADCCLK)
  * @param  __PLLCLOCKOUT__  specifies the output PLL clock to be checked.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_PLL_ADCCLK  same
  *            @arg @ref RCC_PLL_I2S2CLK  This Clock is used to generate the clock for the I2S
  *            @arg @ref RCC_PLL_RNGCLK  This clock is used to generate the clock for RNG
  *            @arg @ref RCC_PLL_SYSCLK  This Clock is used to generate the high speed system clock (up to 48 MHz)
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLLCLKOUT_CONFIG(__PLLCLOCKOUT__)  READ_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__  specifies the system clock source.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_SYSCLKSOURCE_MSI MSI oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_HSI HSI oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_HSE HSE oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_PLLCLK PLL output is used as system clock source.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__)  LL_RCC_SetSysClkSource(__SYSCLKSOURCE__)

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_MSI MSI used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_HSI HSI used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_HSE HSE used as system clock.
  *              @arg @ref RCC_SYSCLKSOURCE_STATUS_PLLCLK PLL used as system clock.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE()  LL_RCC_GetSysClkSource()

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @param  __LSEDRIVE__  specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW  LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW  LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH  LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH  LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__)  LL_RCC_LSE_SetDriveCapability(__LSEDRIVE__)

/**
  * @brief  Macro to configure the wake up from stop clock.
  * @param  __STOPWUCLK__  specifies the clock source used after wake up from stop.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_MSI  MSI selected as system clock source
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_HSI  HSI selected as system clock source
  * @retval None
  */
#define __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(__STOPWUCLK__)  LL_RCC_SetClkAfterWakeFromStop(__STOPWUCLK__)


/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK  MCO output disabled
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK  System  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_MSI     MSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI     HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE     HSE clock selected as MCO sourcee
  *            @arg @ref RCC_MCO1SOURCE_PLLCLK  Main PLL clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSI  LSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSE  LSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLLPCLK  main PLLP clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLLQCLK  main PLLQ clock selected as MCO source
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1   MCO clock source is divided by 1
  *            @arg @ref RCC_MCODIV_2   MCO clock source is divided by 2
  *            @arg @ref RCC_MCODIV_4   MCO clock source is divided by 4
  *            @arg @ref RCC_MCODIV_8   MCO clock source is divided by 8
  *            @arg @ref RCC_MCODIV_16  MCO clock source is divided by 16
  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__)  LL_RCC_ConfigMCO((__MCOCLKSOURCE__), (__MCODIV__))

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/** @brief  Enable RCC interrupt.
  * @param  __INTERRUPT__  specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY     LSI ready interrupt enable
  *            @arg @ref RCC_IT_LSERDY      LSE ready interrupt enable
  *            @arg @ref RCC_IT_MSIRDY      HSI ready interrupt enable
  *            @arg @ref RCC_IT_HSIRDY      HSI ready interrupt enable
  *            @arg @ref RCC_IT_HSERDY      HSE ready interrupt enable
  *            @arg @ref RCC_IT_PLLRDY      Main PLL ready interrupt enable
  *            @arg @ref RCC_IT_LSECSS      LSE Clock security system interrupt enable
  * @retval None
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt.
  * @param  __INTERRUPT__  specifies the RCC interrupt sources to be disabled.
    *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY     LSI ready interrupt enable
  *            @arg @ref RCC_IT_LSERDY      LSE ready interrupt enable
  *            @arg @ref RCC_IT_MSIRDY      HSI ready interrupt enable
  *            @arg @ref RCC_IT_HSIRDY      HSI ready interrupt enable
  *            @arg @ref RCC_IT_HSERDY      HSE ready interrupt enable
  *            @arg @ref RCC_IT_PLLRDY      Main PLL ready interrupt enable
  *            @arg @ref RCC_IT_LSECSS      LSE Clock security system interrupt enable
  * @retval None
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear RCC interrupt pending bits (Perform Byte access to RCC_CICR[17:0]
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__  specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY  LSI ready interrupt clear
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt clear
  *            @arg @ref RCC_IT_MSIRDY   HSI ready interrupt clear
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt clear
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt clear
  *            @arg @ref RCC_IT_PLLRDY   Main PLL ready interrupt clear
  *            @arg @ref RCC_IT_HSECSS   HSE Clock security system interrupt clear
  *            @arg @ref RCC_IT_LSECSS   LSE Clock security system interrupt clear
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->CICR = (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__  specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_LSIRDY  LSI ready interrupt flag
  *            @arg @ref RCC_IT_LSERDY   LSE ready interrupt flag
  *            @arg @ref RCC_IT_MSIRDY   HSI ready interrupt flag
  *            @arg @ref RCC_IT_HSIRDY   HSI ready interrupt flag
  *            @arg @ref RCC_IT_HSERDY   HSE ready interrupt flag
  *            @arg @ref RCC_IT_PLLRDY   Main PLL ready interrupt flag
  *            @arg @ref RCC_IT_HSECSS   HSE Clock security system interrupt flag
  *            @arg @ref RCC_IT_LSECSS   LSE Clock security system interrupt flag
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: LPWRRSTF, WWDGRSTF, IWDGRSTF, SFTRSTF,
           BORRSTF, PINRSTF, OBLRSTF, and RFILARSTF.
  * @retval None
 */
#define __HAL_RCC_CLEAR_RESET_FLAGS() LL_RCC_ClearResetFlags()

/** @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__  specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_MSIRDY     MSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSIRDY     HSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSERDY     HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_PLLRDY     Main PLL clock ready
  *            @arg @ref RCC_FLAG_LSERDY     LSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSECSSD    Clock security system failure on LSE oscillator detection
  *            @arg @ref RCC_FLAG_LSESYSRDY  LSE system clock ready flag
  *            @arg @ref RCC_FLAG_LSIRDY     LSI oscillator clock ready
  *            @arg @ref RCC_FLAG_RFRST      Sub-GHz radio reset flag
  *            @arg @ref RCC_FLAG_RFILARSTF  Sub-GHz radio illegal command flag
  *            @arg @ref RCC_FLAG_BORRST     BOR reset
  *            @arg @ref RCC_FLAG_OBLRST     OBLRST reset
  *            @arg @ref RCC_FLAG_PINRST     Pin reset
  *            @arg @ref RCC_FLAG_SFTRST     Software reset
  *            @arg @ref RCC_FLAG_IWDGRST    Independent Watchdog reset
  *            @arg @ref RCC_FLAG_WWDGRST    Window Watchdog reset
  *            @arg @ref RCC_FLAG_LPWRRST    Low Power reset
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__)                                                 \
  (((((((__FLAG__) >> REG_INDEX_POS) == CR_REG_INDEX) ? RCC->CR :                    \
      ((((__FLAG__) >> REG_INDEX_POS) == BDCR_REG_INDEX) ? RCC->BDCR :               \
       ((((__FLAG__) >> REG_INDEX_POS) == CSR_REG_INDEX) ? RCC->CSR : RCC->CIFR))) & \
     (1U << ((__FLAG__) & RCC_FLAG_MASK))) != RESET) ? 1UL : 0UL)

/**
  * @}
  */

/**
  * @}
  */

/* Include RCC HAL Extended module */
#include "stm32wlxx_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions
  * @{
  */


/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  **********************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void              HAL_RCC_EnableCSS(void);
uint32_t          HAL_RCC_GetSysClockFreq(void);

uint32_t          HAL_RCC_GetHCLKFreq(void);
#if defined(DUAL_CORE)
uint32_t          HAL_RCC_GetHCLK2Freq(void);
#endif /* DUAL_CORE */
uint32_t          HAL_RCC_GetHCLK3Freq(void);

uint32_t          HAL_RCC_GetPCLK1Freq(void);
uint32_t          HAL_RCC_GetPCLK2Freq(void);

void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);
/* LSE & HSE CSS NMI IRQ handler */
void              HAL_RCC_NMI_IRQHandler(void);
/* User Callbacks in non blocking mode (IT mode) */
void              HAL_RCC_CSSCallback(void);

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

#endif /* STM32WLxx_HAL_RCC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


