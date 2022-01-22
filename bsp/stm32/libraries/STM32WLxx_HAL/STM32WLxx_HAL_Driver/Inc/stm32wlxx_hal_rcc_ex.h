/**
  ******************************************************************************
  * @file    stm32wlxx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended module.
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
#ifndef STM32WLxx_HAL_RCC_EX_H
#define STM32WLxx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_def.h"
#include "stm32wlxx_ll_exti.h"
#include "stm32wlxx_ll_pwr.h"

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */
/* Private constants ---------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Constants
  * @{
  */
/* Define used for IS_RCC_* macros below */
#define RCC_PERIPHCLOCK_ALL             (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_I2S2 | \
                                         RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2 | \
                                         RCC_PERIPHCLK_I2C3 | RCC_PERIPHCLK_LPTIM1 | RCC_PERIPHCLK_LPTIM2 | \
                                         RCC_PERIPHCLK_LPTIM3 | RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_RNG | \
                                         RCC_PERIPHCLK_RTC )
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Macros
  * @{
  */

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))

#define IS_RCC_PERIPHCLOCK(__SELECTION__)   ((((__SELECTION__) & RCC_PERIPHCLOCK_ALL) != 0x00u) && \
                                             (((__SELECTION__) & ~RCC_PERIPHCLOCK_ALL) == 0x00u))

#define IS_RCC_USART1CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK2)  || \
                                             ((__SOURCE__) == RCC_USART1CLKSOURCE_SYSCLK) || \
                                             ((__SOURCE__) == RCC_USART1CLKSOURCE_LSE)    || \
                                             ((__SOURCE__) == RCC_USART1CLKSOURCE_HSI))

#define IS_RCC_USART2CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_USART2CLKSOURCE_PCLK1)  || \
                                             ((__SOURCE__) == RCC_USART2CLKSOURCE_SYSCLK) || \
                                             ((__SOURCE__) == RCC_USART2CLKSOURCE_LSE)    || \
                                             ((__SOURCE__) == RCC_USART2CLKSOURCE_HSI))

#define IS_RCC_I2S2CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_I2S2CLKSOURCE_PLL)  || \
                                           ((__SOURCE__) == RCC_I2S2CLKSOURCE_HSI)  || \
                                           ((__SOURCE__) == RCC_I2S2CLKSOURCE_PIN))

#define IS_RCC_LPUART1CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_LPUART1CLKSOURCE_PCLK1)  || \
                                              ((__SOURCE__) == RCC_LPUART1CLKSOURCE_SYSCLK) || \
                                              ((__SOURCE__) == RCC_LPUART1CLKSOURCE_LSE)    || \
                                              ((__SOURCE__) == RCC_LPUART1CLKSOURCE_HSI))

#define IS_RCC_I2C1CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_I2C1CLKSOURCE_PCLK1) || \
                                           ((__SOURCE__) == RCC_I2C1CLKSOURCE_SYSCLK)|| \
                                           ((__SOURCE__) == RCC_I2C1CLKSOURCE_HSI))

#define IS_RCC_I2C2CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_I2C2CLKSOURCE_PCLK1) || \
                                           ((__SOURCE__) == RCC_I2C2CLKSOURCE_SYSCLK)|| \
                                           ((__SOURCE__) == RCC_I2C2CLKSOURCE_HSI))


#define IS_RCC_I2C3CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_I2C3CLKSOURCE_PCLK1) || \
                                           ((__SOURCE__) == RCC_I2C3CLKSOURCE_SYSCLK)|| \
                                           ((__SOURCE__) == RCC_I2C3CLKSOURCE_HSI))

#define IS_RCC_LPTIM1CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_LPTIM1CLKSOURCE_PCLK1) || \
                                             ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSI)   || \
                                             ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_HSI)   || \
                                             ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSE))

#define IS_RCC_LPTIM2CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_LPTIM2CLKSOURCE_PCLK1) || \
                                             ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSI)   || \
                                             ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_HSI)   || \
                                             ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSE))

#define IS_RCC_LPTIM3CLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_LPTIM3CLKSOURCE_PCLK1) || \
                                             ((__SOURCE__) == RCC_LPTIM3CLKSOURCE_LSI)   || \
                                             ((__SOURCE__) == RCC_LPTIM3CLKSOURCE_HSI)   || \
                                             ((__SOURCE__) == RCC_LPTIM3CLKSOURCE_LSE))

#define IS_RCC_RNGCLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_RNGCLKSOURCE_PLL)     || \
                                          ((__SOURCE__) == RCC_RNGCLKSOURCE_LSI)     || \
                                          ((__SOURCE__) == RCC_RNGCLKSOURCE_LSE)     || \
                                          ((__SOURCE__) == RCC_RNGCLKSOURCE_MSI))

#define IS_RCC_ADCCLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_ADCCLKSOURCE_NONE) || \
                                          ((__SOURCE__) == RCC_ADCCLKSOURCE_HSI)  || \
                                          ((__SOURCE__) == RCC_ADCCLKSOURCE_PLL)  || \
                                          ((__SOURCE__) == RCC_ADCCLKSOURCE_SYSCLK))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */

/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t PeriphClockSelection;   /*!< The Extended Clock to be configured.
                                        This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t Usart1ClockSelection;   /*!< Specifies USART1 clock source.
                                        This parameter can be a value of @ref RCCEx_USART1_Clock_Source    */

  uint32_t Usart2ClockSelection;   /*!< Specifies USART2 clock source.
                                        This parameter can be a value of @ref RCCEx_USART2_Clock_Source    */

  uint32_t I2s2ClockSelection;     /*!< Specifies I2S2 clock source.
                                        This parameter can be a value of @ref RCCEx_I2S2_Clock_Source      */

  uint32_t Lpuart1ClockSelection;  /*!< Specifies LPUART1 clock source.
                                        This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source   */

  uint32_t I2c1ClockSelection;     /*!< Specifies I2C1 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C1_Clock_Source      */

  uint32_t I2c2ClockSelection;     /*!< Specifies I2C2 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C2_Clock_Source      */

  uint32_t I2c3ClockSelection;     /*!< Specifies I2C3 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C3_Clock_Source      */

  uint32_t Lptim1ClockSelection;   /*!< Specifies LPTIM1 clock source.
                                        This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source    */

  uint32_t Lptim2ClockSelection;   /*!< Specifies LPTIM2 clock source.
                                        This parameter can be a value of @ref RCCEx_LPTIM2_Clock_Source    */

  uint32_t Lptim3ClockSelection;   /*!< Specifies LPTIM3 clock source.
                                        This parameter can be a value of @ref RCCEx_LPTIM3_Clock_Source    */

  uint32_t AdcClockSelection;      /*!< Specifies ADC interface clock source.
                                      This parameter can be a value of @ref RCCEx_ADC_Clock_Source         */

  uint32_t RngClockSelection;      /*!< Specifies RNG clock source.
                                        This parameter can be a value of @ref RCCEx_RNG_Clock_Source       */

  uint32_t RTCClockSelection;      /*!< Specifies RTC clock source.
                                        This parameter can be a value of @ref RCC_RTC_Clock_Source         */

} RCC_PeriphCLKInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_LSCO_Clock_Source Low Speed Clock Source
  * @{
  */
#define RCC_LSCOSOURCE_LSI             LL_RCC_LSCO_CLKSOURCE_LSI  /*!< LSI selection for low speed clock output */
#define RCC_LSCOSOURCE_LSE             LL_RCC_LSCO_CLKSOURCE_LSE  /*!< LSE selection for low speed clock output */
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_USART1           0x00000001U  /*!< USART1 Peripheral Clock Selection      */
#define RCC_PERIPHCLK_USART2           0x00000002U  /*!< USART2 Peripheral Clock Selection      */
#define RCC_PERIPHCLK_I2S2             0x00000010U  /*!< I2S2 Peripheral Clock Selection        */
#define RCC_PERIPHCLK_LPUART1          0x00000020U  /*!< LPUART1 Peripheral Clock Selection     */
#define RCC_PERIPHCLK_I2C1             0x00000040U  /*!< I2C1 Peripheral Clock Selection        */
#define RCC_PERIPHCLK_I2C2             0x00000080U  /*!< I2C2 Peripheral Clock Selection        */
#define RCC_PERIPHCLK_I2C3             0x00000100U  /*!< I2C3 Peripheral Clock Selection        */
#define RCC_PERIPHCLK_LPTIM1           0x00000200U  /*!< LPTIM1 Peripheral Clock Selection      */
#define RCC_PERIPHCLK_LPTIM2           0x00000400U  /*!< LPTIM2 Peripheral Clock Selection      */
#define RCC_PERIPHCLK_LPTIM3           0x00000800U  /*!< LPTIM3 Peripheral Clock Selection      */
#define RCC_PERIPHCLK_ADC              0x00004000U  /*!< ADC Peripheral Clock Selection         */
#define RCC_PERIPHCLK_RNG              0x00008000U  /*!< RNG Peripheral Clock Selection         */
#define RCC_PERIPHCLK_RTC              0x00010000U  /*!< RTC Peripheral Clock Selection         */
/**
  * @}
  */

/** @defgroup RCCEx_USART1_Clock_Source USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2      LL_RCC_USART1_CLKSOURCE_PCLK2   /*!< APB2 clock selected as USART1 clock   */
#define RCC_USART1CLKSOURCE_SYSCLK     LL_RCC_USART1_CLKSOURCE_SYSCLK  /*!< SYSCLK clock selected as USART1 clock */
#define RCC_USART1CLKSOURCE_HSI        LL_RCC_USART1_CLKSOURCE_HSI     /*!< HSI clock selected as USART1 clock    */
#define RCC_USART1CLKSOURCE_LSE        LL_RCC_USART1_CLKSOURCE_LSE     /*!< LSE clock selected as USART1 clock    */
/**
  * @}
  */

/** @defgroup RCCEx_USART2_Clock_Source USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1      LL_RCC_USART2_CLKSOURCE_PCLK1   /*!< APB1 clock selected as USART2 clock*/
#define RCC_USART2CLKSOURCE_SYSCLK     LL_RCC_USART2_CLKSOURCE_SYSCLK  /*!< SYSCLK clock selected as USART2 clock*/
#define RCC_USART2CLKSOURCE_HSI        LL_RCC_USART2_CLKSOURCE_HSI     /*!< HSI clock selected as USART2 clock*/
#define RCC_USART2CLKSOURCE_LSE        LL_RCC_USART2_CLKSOURCE_LSE     /*!< LSE clock selected as USART2 clock*/
/**
  * @}
  */

/** @defgroup RCCEx_I2S2_Clock_Source I2S Clock Source
  * @{
  */
#define RCC_I2S2CLKSOURCE_PLL        LL_RCC_I2S2_CLKSOURCE_PLL       /*!< PLL "Q" clock selected as I2S2 clock source */
#define RCC_I2S2CLKSOURCE_HSI        LL_RCC_I2S2_CLKSOURCE_HSI       /*!< HSI clock selected as I2S2 clock */
#define RCC_I2S2CLKSOURCE_PIN        LL_RCC_I2S2_CLKSOURCE_PIN       /*!< External clock selected as I2S2 clock */
/**
  * @}
  */

/** @defgroup RCCEx_LPUART1_Clock_Source LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK1     LL_RCC_LPUART1_CLKSOURCE_PCLK1    /*!< APB1 clock selected as LPUART1 clock*/
#define RCC_LPUART1CLKSOURCE_SYSCLK    LL_RCC_LPUART1_CLKSOURCE_SYSCLK   /*!< SYSCLK clock selected as LPUART1 clock*/
#define RCC_LPUART1CLKSOURCE_HSI       LL_RCC_LPUART1_CLKSOURCE_HSI      /*!< HSI clock selected as LPUART1 clock*/
#define RCC_LPUART1CLKSOURCE_LSE       LL_RCC_LPUART1_CLKSOURCE_LSE      /*!< LSE clock selected as LPUART1 clock*/
/**
  * @}
  */

/** @defgroup RCCEx_I2C1_Clock_Source I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_PCLK1        LL_RCC_I2C1_CLKSOURCE_PCLK1   /*!< APB1 clock selected as I2C1 clock */
#define RCC_I2C1CLKSOURCE_SYSCLK       LL_RCC_I2C1_CLKSOURCE_SYSCLK  /*!< SYSCLK clock selected as I2C1 clock */
#define RCC_I2C1CLKSOURCE_HSI          LL_RCC_I2C1_CLKSOURCE_HSI     /*!< HSI clock selected as I2C1 clock */
/**
  * @}
  */

/** @defgroup RCCEx_I2C2_Clock_Source I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_PCLK1        LL_RCC_I2C2_CLKSOURCE_PCLK1   /*!< APB1 clock selected as I2C2 clock */
#define RCC_I2C2CLKSOURCE_SYSCLK       LL_RCC_I2C2_CLKSOURCE_SYSCLK  /*!< SYSCLK clock selected as I2C2 clock */
#define RCC_I2C2CLKSOURCE_HSI          LL_RCC_I2C2_CLKSOURCE_HSI     /*!< HSI clock selected as I2C2 clock */
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_PCLK1        LL_RCC_I2C3_CLKSOURCE_PCLK1   /*!< APB1 clock selected as I2C3 clock */
#define RCC_I2C3CLKSOURCE_SYSCLK       LL_RCC_I2C3_CLKSOURCE_SYSCLK  /*!< SYSCLK clock selected as I2C3 clock */
#define RCC_I2C3CLKSOURCE_HSI          LL_RCC_I2C3_CLKSOURCE_HSI     /*!< HSI clock selected as I2C3 clock */
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_PCLK1      LL_RCC_LPTIM1_CLKSOURCE_PCLK1  /*!< APB1 clock selected as LPTIM1 clock */
#define RCC_LPTIM1CLKSOURCE_LSI        LL_RCC_LPTIM1_CLKSOURCE_LSI    /*!< LSI clock selected as LPTIM1 clock  */
#define RCC_LPTIM1CLKSOURCE_HSI        LL_RCC_LPTIM1_CLKSOURCE_HSI    /*!< HSI clock selected as LPTIM1 clock  */
#define RCC_LPTIM1CLKSOURCE_LSE        LL_RCC_LPTIM1_CLKSOURCE_LSE    /*!< LSE clock selected as LPTIM1 clock  */
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM2_Clock_Source LPTIM2 Clock Source
  * @{
  */
#define RCC_LPTIM2CLKSOURCE_PCLK1      LL_RCC_LPTIM2_CLKSOURCE_PCLK1  /*!< APB1 clock selected as LPTIM2 clock */
#define RCC_LPTIM2CLKSOURCE_LSI        LL_RCC_LPTIM2_CLKSOURCE_LSI    /*!< LSI clock selected as LPTIM2 clock  */
#define RCC_LPTIM2CLKSOURCE_HSI        LL_RCC_LPTIM2_CLKSOURCE_HSI    /*!< HSI clock selected as LPTIM2 clock  */
#define RCC_LPTIM2CLKSOURCE_LSE        LL_RCC_LPTIM2_CLKSOURCE_LSE    /*!< LSE clock selected as LPTIM2 clock  */
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM3_Clock_Source LPTIM3 Clock Source
  * @{
  */
#define RCC_LPTIM3CLKSOURCE_PCLK1      LL_RCC_LPTIM3_CLKSOURCE_PCLK1  /*!< APB1 clock selected as LPTIM3 clock */
#define RCC_LPTIM3CLKSOURCE_LSI        LL_RCC_LPTIM3_CLKSOURCE_LSI    /*!< LSI clock selected as LPTIM3 clock  */
#define RCC_LPTIM3CLKSOURCE_HSI        LL_RCC_LPTIM3_CLKSOURCE_HSI    /*!< HSI clock selected as LPTIM3 clock  */
#define RCC_LPTIM3CLKSOURCE_LSE        LL_RCC_LPTIM3_CLKSOURCE_LSE    /*!< LSE clock selected as LPTIM3 clock  */
/**
  * @}
  */

/** @defgroup RCCEx_RNG_Clock_Source RNG Clock Source
  * @{
  */
#define RCC_RNGCLKSOURCE_PLL           LL_RCC_RNG_CLKSOURCE_PLL  /*!< PLL "Q" clock selected as RNG clock     */
#define RCC_RNGCLKSOURCE_LSI           LL_RCC_RNG_CLKSOURCE_LSI  /*!< LSI clock selected as RNG clock         */
#define RCC_RNGCLKSOURCE_LSE           LL_RCC_RNG_CLKSOURCE_LSE  /*!< LSE clock selected as RNG clock         */
#define RCC_RNGCLKSOURCE_MSI           LL_RCC_RNG_CLKSOURCE_MSI  /*!< MSI clock selected as RNG clock         */
/**
  * @}
  */

/** @defgroup RCCEx_ADC_Clock_Source ADC Clock Source
  * @{
  */
#define RCC_ADCCLKSOURCE_NONE          LL_RCC_ADC_CLKSOURCE_NONE    /*!< None clock selected as ADC clock        */
#define RCC_ADCCLKSOURCE_HSI           LL_RCC_ADC_CLKSOURCE_HSI     /*!< HSI clock selected as ADC clock     */
#define RCC_ADCCLKSOURCE_PLL           LL_RCC_ADC_CLKSOURCE_PLL     /*!< PLL "P" clock selected as ADC clock     */
#define RCC_ADCCLKSOURCE_SYSCLK        LL_RCC_ADC_CLKSOURCE_SYSCLK  /*!< SYSCLK clock selected as ADC clock      */
/**
  * @}
  */

/** @defgroup RCCEx_EXTI_LINE_LSECSS  RCC LSE CSS external interrupt line
  * @{
  */
#define  RCC_EXTI_LINE_LSECSS          EXTI_IMR1_IM19  /*!< External interrupt line 18 connected to the LSE CSS EXTI Line */
/**
  * @}
  */

/** @defgroup RCCEx_EXTI_LINE_HSECSS  RCC HSE CSS external interrupt line
  * @{
  */
#define  RCC_EXTI_LINE_HSECSS          EXTI_IMR2_IM43  /*!< External interrupt line 43 connected to the HSE CSS EXTI Line */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */

/*============================================================================*/

/** @brief  Macro to configure the USART1 clock (USART1CLK).
  * @param  __USART1_CLKSOURCE__ specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2   PCLK2 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI     HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE     LSE selected as USART1 clock
  * @retval None
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__)  LL_RCC_SetUSARTClockSource(__USART1_CLKSOURCE__)

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2   PCLK2 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI     HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE     LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE()  LL_RCC_GetUSARTClockSource(LL_RCC_USART1_CLKSOURCE)

/** @brief  Macro to configure the USART2 clock (USART2CLK).
  * @param  __USART2_CLKSOURCE__ specifies the USART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1   PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI     HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE     LSE selected as USART2 clock
  * @retval None
  */
#define __HAL_RCC_USART2_CONFIG(__USART2_CLKSOURCE__)  LL_RCC_SetUSARTClockSource(__USART2_CLKSOURCE__)

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1   PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI     HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE     LSE selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE()  LL_RCC_GetUSARTClockSource(LL_RCC_USART2_CLKSOURCE)

/** @brief  Macro to configure the I2S2 clock (I2S2CLK).
  * @param  __I2S2_CLKSOURCE__ specifies the I2S2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2S2CLKSOURCE_PLL           PLL "Q" selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_HSI           HSI selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_PIN           External clock selected as I2S2 clock
  * @retval None
  */
#define __HAL_RCC_I2S2_CONFIG(__I2S2_CLKSOURCE__)  LL_RCC_SetI2SClockSource(__I2S2_CLKSOURCE__)

/** @brief  Macro to get the I2S2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2S2CLKSOURCE_PLL       PLL "Q" selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_HSI       HSI selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_PIN       External clock selected as I2S2 clock
  */
#define __HAL_RCC_GET_I2S2_SOURCE()  LL_RCC_GetI2SClockSource(LL_RCC_I2S2_CLKSOURCE)

/** @brief  Macro to configure the LPUART clock (LPUART1CLK).
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK1   PCLK1 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI     HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE     LSE selected as LPUART1 clock
  * @retval None
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__)  LL_RCC_SetLPUARTClockSource(__LPUART1_CLKSOURCE__)

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK1   PCLK1 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI     HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE     LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE()  LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE)

/** @brief  Macro to configure the I2C1 clock (I2C1CLK).
  * @param  __I2C1_CLKSOURCE__ specifies the I2C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1   PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI     HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  * @retval None
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1_CLKSOURCE__)  LL_RCC_SetI2CClockSource(__I2C1_CLKSOURCE__)

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1   PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI     HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE()  LL_RCC_GetI2CClockSource(LL_RCC_I2C1_CLKSOURCE)

/** @brief  Macro to configure the I2C2 clock (I2C2CLK).
  * @param  __I2C2_CLKSOURCE__ specifies the I2C2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_PCLK1   PCLK1 selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_HSI     HSI selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_SYSCLK  System Clock selected as I2C2 clock
  * @retval None
  */
#define __HAL_RCC_I2C2_CONFIG(__I2C2_CLKSOURCE__)  LL_RCC_SetI2CClockSource(__I2C2_CLKSOURCE__)

/** @brief  Macro to get the I2C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_PCLK1   PCLK1 selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_HSI     HSI selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_SYSCLK  System Clock selected as I2C2 clock
  */
#define __HAL_RCC_GET_I2C2_SOURCE()  LL_RCC_GetI2CClockSource(LL_RCC_I2C2_CLKSOURCE)

/** @brief  Macro to configure the I2C3 clock (I2C3CLK).
  * @param  __I2C3_CLKSOURCE__ specifies the I2C3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK1   PCLK1 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI     HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK  System Clock selected as I2C3 clock
  * @retval None
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3_CLKSOURCE__)  LL_RCC_SetI2CClockSource(__I2C3_CLKSOURCE__)

/** @brief  Macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK1   PCLK1 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI     HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK  System Clock selected as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE()  LL_RCC_GetI2CClockSource(LL_RCC_I2C3_CLKSOURCE)

/** @brief  Macro to configure the LPTIM1 clock (LPTIM1CLK).
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK1  PCLK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI   HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI   LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE   LSE selected as LPTIM1 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__)  LL_RCC_SetLPTIMClockSource(__LPTIM1_CLKSOURCE__)

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK1  PCLK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI   HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI   System Clock selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE   LSE selected as LPTIM1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE()  LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE)

/** @brief  Macro to configure the LPTIM2 clock (LPTIM2CLK).
  * @param  __LPTIM2_CLKSOURCE__ specifies the LPTIM2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI   HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI   LSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE   LSE selected as LPTIM2 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM2_CONFIG(__LPTIM2_CLKSOURCE__)  LL_RCC_SetLPTIMClockSource(__LPTIM2_CLKSOURCE__)

/** @brief  Macro to get the LPTIM2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI   HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI   System Clock selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE   LSE selected as LPTIM2 clock
  */
#define __HAL_RCC_GET_LPTIM2_SOURCE()  LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM2_CLKSOURCE)

/** @brief  Macro to configure the LPTIM3 clock (LPTIM3CLK).
  * @param  __LPTIM3_CLKSOURCE__ specifies the LPTIM3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM3CLKSOURCE_PCLK1  PCLK selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_LSI   HSI selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_HSI   LSI selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_LSE   LSE selected as LPTIM3 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM3_CONFIG(__LPTIM3_CLKSOURCE__)  LL_RCC_SetLPTIMClockSource(__LPTIM3_CLKSOURCE__)

/** @brief  Macro to get the LPTIM3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM3CLKSOURCE_PCLK1  PCLK selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_LSI   HSI selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_HSI   System Clock selected as LPTIM3 clock
  *            @arg @ref RCC_LPTIM3CLKSOURCE_LSE   LSE selected as LPTIM3 clock
  */
#define __HAL_RCC_GET_LPTIM3_SOURCE()  LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM3_CLKSOURCE)

/** @brief  Macro to configure the RNG clock.
  * @param  __RNG_CLKSOURCE__ specifies the RNG clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RNGCLKSOURCE_PLL      PLL "Q" Clock selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_LSI      LSI selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_LSE      LSE selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_MSI      MSI selected as RNG clock
  * @retval None
  */
#define __HAL_RCC_RNG_CONFIG(__RNG_CLKSOURCE__)  LL_RCC_SetRNGClockSource(__RNG_CLKSOURCE__)

/** @brief  Macro to get the RNG clock.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_RNGCLKSOURCE_PLL      PLL "Q" Clock selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_LSI      LSI selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_LSE      LSE selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_MSI      MSI selected as RNG clock
  */
#define __HAL_RCC_GET_RNG_SOURCE()  LL_RCC_GetRNGClockSource(LL_RCC_RNG_CLKSOURCE)

/** @brief  Macro to configure the ADC interface clock.
  * @param  __ADC_CLKSOURCE__ specifies the ADC digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_NONE    No clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSI     HSI Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_PLL     PLL "P" Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK  System Clock selected as ADC clock
  * @retval None
  */
#define __HAL_RCC_ADC_CONFIG(__ADC_CLKSOURCE__)  LL_RCC_SetADCClockSource(__ADC_CLKSOURCE__)

/** @brief  Macro to get the ADC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_NONE    No clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSI     HSI Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_PLL     PLL "P" Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK  System Clock selected as ADC clock
  */
#define __HAL_RCC_GET_ADC_SOURCE()  LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE)


#if defined(DUAL_CORE)

#if defined(CORE_CM0PLUS)
#define __HAL_RCC_LSECSS_EXTI_ENABLE_IT()            LL_C2_EXTI_EnableIT_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_DISABLE_IT()           LL_C2_EXTI_DisableIT_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_ENABLE_EVENT()         LL_C2_EXTI_EnableEvent_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_DISABLE_EVENT()        LL_C2_EXTI_DisableEvent_0_31(RCC_EXTI_LINE_LSECSS)

#define __HAL_RCC_HSECSS_EXTI_ENABLE_IT()            LL_C2_EXTI_EnableIT_32_63(RCC_EXTI_LINE_HSECSS)
#define __HAL_RCC_HSECSS_EXTI_DISABLE_IT()           LL_C2_EXTI_DisableIT_32_63(RCC_EXTI_LINE_HSECSS)
#else
#define __HAL_RCC_LSECSS_EXTI_ENABLE_IT()            LL_EXTI_EnableIT_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_DISABLE_IT()           LL_EXTI_DisableIT_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_ENABLE_EVENT()         LL_EXTI_EnableEvent_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_DISABLE_EVENT()        LL_EXTI_DisableEvent_0_31(RCC_EXTI_LINE_LSECSS)

#define __HAL_RCC_HSECSS_EXTI_ENABLE_IT()            LL_EXTI_EnableIT_32_63(RCC_EXTI_LINE_HSECSS)
#define __HAL_RCC_HSECSS_EXTI_DISABLE_IT()           LL_EXTI_DisableIT_32_63(RCC_EXTI_LINE_HSECSS)
#endif /* CORE_CM0PLUS */

#else

#define __HAL_RCC_LSECSS_EXTI_ENABLE_IT()            LL_EXTI_EnableIT_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_DISABLE_IT()           LL_EXTI_DisableIT_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_ENABLE_EVENT()         LL_EXTI_EnableEvent_0_31(RCC_EXTI_LINE_LSECSS)
#define __HAL_RCC_LSECSS_EXTI_DISABLE_EVENT()        LL_EXTI_DisableEvent_0_31(RCC_EXTI_LINE_LSECSS)

#define __HAL_RCC_HSECSS_EXTI_ENABLE_IT()            LL_EXTI_EnableIT_32_63(RCC_EXTI_LINE_HSECSS)
#define __HAL_RCC_HSECSS_EXTI_DISABLE_IT()           LL_EXTI_DisableIT_32_63(RCC_EXTI_LINE_HSECSS)

#endif /* DUAL_CORE */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

void              HAL_RCCEx_WakeUpStopCLKConfig(uint32_t WakeUpClk);

void              HAL_RCCEx_EnableLSECSS(void);
void              HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_EnableLSECSS_IT(void);
void              HAL_RCCEx_LSECSS_IRQHandler(void);
void              HAL_RCCEx_LSECSS_Callback(void);

void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);

void              HAL_RCCEx_EnableMSIPLLMode(void);
void              HAL_RCCEx_DisableMSIPLLMode(void);


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

#endif /* STM32WLxx_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
