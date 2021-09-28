/**
  ******************************************************************************
  * @file    stm32g0xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
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
#ifndef STM32G0xx_HAL_RCC_EX_H
#define STM32G0xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal_def.h"

/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
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
                                        This parameter can be a value of @ref RCCEx_USART1_Clock_Source */
#if defined(RCC_CCIPR_USART2SEL)
  uint32_t Usart2ClockSelection;   /*!< Specifies USART2 clock source.
                                        This parameter can be a value of @ref RCCEx_USART2_Clock_Source */
#endif /* RCC_CCIPR_USART2SEL */

#if defined(RCC_CCIPR_USART3SEL)
  uint32_t Usart3ClockSelection;   /*!< Specifies USART3 clock source.
                                        This parameter can be a value of @ref RCCEx_USART3_Clock_Source */
#endif /* RCC_CCIPR_USART3SEL */

#if defined(LPUART1)
  uint32_t Lpuart1ClockSelection;  /*!< Specifies LPUART1 clock source
                                        This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */
#endif /* LPUART1 */

#if defined(LPUART2)
  uint32_t Lpuart2ClockSelection;  /*!< Specifies LPUART2 clock source
                                        This parameter can be a value of @ref RCCEx_LPUART2_Clock_Source */
#endif /* LPUART2 */

  uint32_t I2c1ClockSelection;     /*!< Specifies I2C1 clock source
                                        This parameter can be a value of @ref RCCEx_I2C1_Clock_Source */

#if defined(RCC_CCIPR_I2C2SEL)
  uint32_t I2c2ClockSelection;     /*!< Specifies I2C2 clock source
                                        This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */
#endif /* RCC_CCIPR_I2C2SEL */

  uint32_t I2s1ClockSelection;     /*!< Specifies I2S1 clock source
                                        This parameter can be a value of @ref RCCEx_I2S1_Clock_Source */
#if defined(RCC_CCIPR2_I2S2SEL)
  uint32_t I2s2ClockSelection;     /*!< Specifies I2S2 clock source
                                        This parameter can be a value of @ref RCCEx_I2S2_Clock_Source */
#endif /* RCC_CCIPR2_I2S2SEL */
#if defined(RCC_CCIPR_LPTIM1SEL)
  uint32_t Lptim1ClockSelection;   /*!< Specifies LPTIM1 clock source
                                        This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source */
#endif /* RCC_CCIPR_LPTIM1SEL */
#if defined(RCC_CCIPR_LPTIM2SEL)
  uint32_t Lptim2ClockSelection;   /*!< Specifies LPTIM2 clock source
                                        This parameter can be a value of @ref RCCEx_LPTIM2_Clock_Source */
#endif /* RCC_CCIPR_LPTIM2SEL */
#if defined(RNG)
  uint32_t RngClockSelection;      /*!< Specifies RNG clock source
                                        This parameter can be a value of @ref RCCEx_RNG_Clock_Source */
#endif /* RNG */
  uint32_t AdcClockSelection;      /*!< Specifies ADC interface clock source
                                        This parameter can be a value of @ref RCCEx_ADC_Clock_Source */
#if defined(CEC)
  uint32_t CecClockSelection;      /*!< Specifies CEC Clock clock source
                                        This parameter can be a value of @ref RCCEx_CEC_Clock_Source */
#endif /* CEC */
#if defined(RCC_CCIPR_TIM1SEL)
  uint32_t Tim1ClockSelection;     /*!< Specifies TIM1 Clock clock source
                                         This parameter can be a value of @ref RCCEx_TIM1_Clock_Source */
#endif /* RCC_CCIPR_TIM1SEL */
#if defined(RCC_CCIPR_TIM15SEL)
  uint32_t Tim15ClockSelection;    /*!< Specifies TIM15 Clock clock source
                                         This parameter can be a value of @ref RCCEx_TIM15_Clock_Source */
#endif /* RCC_CCIPR_TIM15SEL */
  uint32_t RTCClockSelection;      /*!< Specifies RTC clock source.
                                        This parameter can be a value of @ref RCC_RTC_Clock_Source */
#if defined(RCC_CCIPR2_USBSEL)
  uint32_t UsbClockSelection;      /*!< Specifies USB Clock clock source
                                        This parameter can be a value of @ref RCCEx_USB_Clock_Source */
#endif /* RCC_CCIPR2_USBSEL */
#if defined(FDCAN1) || defined(FDCAN2)
  uint32_t FdcanClockSelection;    /*!< Specifies FDCAN Clock clock source
                                        This parameter can be a value of @ref RCCEx_FDCAN_Clock_Source */
#endif /* FDCAN1 || FDCAN2 */
} RCC_PeriphCLKInitTypeDef;

#if defined(CRS)

/**
  * @brief RCC_CRS Init structure definition
  */
typedef struct
{
  uint32_t Prescaler;             /*!< Specifies the division factor of the SYNC signal.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroDivider */

  uint32_t Source;                /*!< Specifies the SYNC signal source.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroSource */

  uint32_t Polarity;              /*!< Specifies the input polarity for the SYNC signal source.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroPolarity */

  uint32_t ReloadValue;           /*!< Specifies the value to be loaded in the frequency error counter with each SYNC event.
                                       It can be calculated in using macro __HAL_RCC_CRS_RELOADVALUE_CALCULATE(__FTARGET__, __FSYNC__)
                                       This parameter must be a number between 0 and 0xFFFF or a value of @ref RCCEx_CRS_ReloadValueDefault .*/

  uint32_t ErrorLimitValue;       /*!< Specifies the value to be used to evaluate the captured frequency error value.
                                       This parameter must be a number between 0 and 0xFF or a value of @ref RCCEx_CRS_ErrorLimitDefault */

  uint32_t HSI48CalibrationValue; /*!< Specifies a user-programmable trimming value to the HSI48 oscillator.
                                       This parameter must be a number between 0 and 0x7F or a value of @ref RCCEx_CRS_HSI48CalibrationDefault */

} RCC_CRSInitTypeDef;

/**
  * @brief RCC_CRS Synchronization structure definition
  */
typedef struct
{
  uint32_t ReloadValue;           /*!< Specifies the value loaded in the Counter reload value.
                                       This parameter must be a number between 0 and 0xFFFF */

  uint32_t HSI48CalibrationValue; /*!< Specifies value loaded in HSI48 oscillator smooth trimming.
                                       This parameter must be a number between 0 and 0x7F */

  uint32_t FreqErrorCapture;      /*!< Specifies the value loaded in the .FECAP, the frequency error counter
                                       value latched in the time of the last SYNC event.
                                       This parameter must be a number between 0 and 0xFFFF */

  uint32_t FreqErrorDirection;    /*!< Specifies the value loaded in the .FEDIR, the counting direction of the
                                       frequency error counter latched in the time of the last SYNC event.
                                       It shows whether the actual frequency is below or above the target.
                                       This parameter must be a value of @ref RCCEx_CRS_FreqErrorDirection*/

} RCC_CRSSynchroInfoTypeDef;

#endif /* CRS */
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
#define RCC_LSCOSOURCE_LSI             0x00000000U           /*!< LSI selection for low speed clock output */
#define RCC_LSCOSOURCE_LSE             RCC_BDCR_LSCOSEL      /*!< LSE selection for low speed clock output */
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_USART1           0x00000001U
#if defined(RCC_CCIPR_USART2SEL)
#define RCC_PERIPHCLK_USART2           0x00000002U
#endif /* RCC_CCIPR_USART2SEL */
#if defined(RCC_CCIPR_USART3SEL)
#define RCC_PERIPHCLK_USART3           0x00000004U
#endif /* RCC_CCIPR_USART3SEL */
#if defined(LPUART1)
#define RCC_PERIPHCLK_LPUART1          0x00000010U
#endif /* LPUART1 */
#define RCC_PERIPHCLK_I2C1             0x00000020U
#if defined(RCC_CCIPR_I2C2SEL)
#define RCC_PERIPHCLK_I2C2             0x00000040U
#endif /* RCC_CCIPR_I2C2SEL */
#if defined(RCC_CCIPR_LPTIM1SEL)
#define RCC_PERIPHCLK_LPTIM1           0x00000200U
#endif /* RCC_CCIPR_LPTIM1SEL */
#if defined(RCC_CCIPR_LPTIM2SEL)
#define RCC_PERIPHCLK_LPTIM2           0x00000400U
#endif /* RCC_CCIPR_LPTIM2SEL */
#define RCC_PERIPHCLK_I2S1             0x00000800U
#if defined(LPUART2)
#define RCC_PERIPHCLK_LPUART2          0x00001000U
#endif /* LPUART2 */
#if defined(RCC_CCIPR2_I2S2SEL)
#define RCC_PERIPHCLK_I2S2             0x00002000U
#endif /* RCC_CCIPR2_I2S2SEL */
#define RCC_PERIPHCLK_ADC              0x00004000U
#define RCC_PERIPHCLK_RTC              0x00020000U
#if defined(RCC_CCIPR_RNGSEL)
#define RCC_PERIPHCLK_RNG              0x00040000U
#endif /* RCC_CCIPR_RNGSEL */
#if defined(RCC_CCIPR_CECSEL)
#define RCC_PERIPHCLK_CEC              0x00080000U
#endif /* RCC_CCIPR_CECSEL */
#if defined(RCC_CCIPR_TIM1SEL)
#define RCC_PERIPHCLK_TIM1             0x00200000U
#endif /* RCC_CCIPR_TIM1SEL */
#if defined(RCC_CCIPR_TIM15SEL)
#define RCC_PERIPHCLK_TIM15            0x00400000U
#endif /* RCC_CCIPR_TIM15SEL */
#if defined(RCC_CCIPR2_USBSEL)
#define RCC_PERIPHCLK_USB              0x01000000U
#endif /* RCC_CCIPR2_USBSEL */
#if defined(FDCAN1) || defined(FDCAN2)
#define RCC_PERIPHCLK_FDCAN            0x02000000U
#endif /* FDCAN1 || FDCAN2 */
/**
  * @}
  */


/** @defgroup RCCEx_USART1_Clock_Source RCC USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK1      0x00000000U                                      /*!< APB clock selected as USART1 clock */
#define RCC_USART1CLKSOURCE_SYSCLK     RCC_CCIPR_USART1SEL_0                            /*!< SYSCLK clock selected as USART1 clock */
#define RCC_USART1CLKSOURCE_HSI        RCC_CCIPR_USART1SEL_1                            /*!< HSI clock selected as USART1 clock */
#define RCC_USART1CLKSOURCE_LSE        (RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1)  /*!< LSE clock selected as USART1 clock */
/**
  * @}
  */

#if defined(RCC_CCIPR_USART2SEL)
/** @defgroup RCCEx_USART2_Clock_Source RCC USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1      0x00000000U                                      /*!< APB clock selected as USART2 clock */
#define RCC_USART2CLKSOURCE_SYSCLK     RCC_CCIPR_USART2SEL_0                            /*!< SYSCLK clock selected as USART2 clock */
#define RCC_USART2CLKSOURCE_HSI        RCC_CCIPR_USART2SEL_1                            /*!< HSI clock selected as USART2 clock */
#define RCC_USART2CLKSOURCE_LSE        (RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1)  /*!< LSE clock selected as USART2 clock */
/**
  * @}
  */
#endif /* RCC_CCIPR_USART2SEL */
#if defined(RCC_CCIPR_USART3SEL)
/** @defgroup RCCEx_USART3_Clock_Source RCC USART3 Clock Source
  * @{
  */
#define RCC_USART3CLKSOURCE_PCLK1      0x00000000U                                      /*!< APB clock selected as USART3 clock */
#define RCC_USART3CLKSOURCE_SYSCLK     RCC_CCIPR_USART3SEL_0                            /*!< SYSCLK clock selected as USART3 clock */
#define RCC_USART3CLKSOURCE_HSI        RCC_CCIPR_USART3SEL_1                            /*!< HSI clock selected as USART3 clock */
#define RCC_USART3CLKSOURCE_LSE        (RCC_CCIPR_USART3SEL_0 | RCC_CCIPR_USART3SEL_1)  /*!< LSE clock selected as USART3 clock */
/**
  * @}
  */
#endif /* RCC_CCIPR_USART3SEL */

#if defined(LPUART1)
/** @defgroup RCCEx_LPUART1_Clock_Source RCC LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK1     0x00000000U                                        /*!< APB clock selected as LPUART1 clock */
#define RCC_LPUART1CLKSOURCE_SYSCLK    RCC_CCIPR_LPUART1SEL_0                             /*!< SYSCLK clock selected as LPUART1 clock */
#define RCC_LPUART1CLKSOURCE_HSI       RCC_CCIPR_LPUART1SEL_1                             /*!< HSI clock selected as LPUART1 clock */
#define RCC_LPUART1CLKSOURCE_LSE       (RCC_CCIPR_LPUART1SEL_0 | RCC_CCIPR_LPUART1SEL_1)  /*!< LSE clock selected as LPUART1 clock */
/**
  * @}
  */
#endif /* LPUART1 */

#if defined(LPUART2)
/** @defgroup RCCEx_LPUART2_Clock_Source RCC LPUART2 Clock Source
  * @{
  */
#define RCC_LPUART2CLKSOURCE_PCLK1     0x00000000U                                        /*!< APB clock selected as LPUART2 clock */
#define RCC_LPUART2CLKSOURCE_SYSCLK    RCC_CCIPR_LPUART2SEL_0                             /*!< SYSCLK clock selected as LPUART2 clock */
#define RCC_LPUART2CLKSOURCE_HSI       RCC_CCIPR_LPUART2SEL_1                             /*!< HSI clock selected as LPUART2 clock */
#define RCC_LPUART2CLKSOURCE_LSE       (RCC_CCIPR_LPUART2SEL_0 | RCC_CCIPR_LPUART2SEL_1)  /*!< LSE clock selected as LPUART2 clock */
/**
  * @}
  */
#endif /* LPUART2 */

/** @defgroup RCCEx_I2C1_Clock_Source RCC I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_PCLK1        0x00000000U                                      /*!< APB clock selected as I2C1 clock */
#define RCC_I2C1CLKSOURCE_SYSCLK       RCC_CCIPR_I2C1SEL_0                              /*!< SYSCLK clock selected as I2C1 clock */
#define RCC_I2C1CLKSOURCE_HSI          RCC_CCIPR_I2C1SEL_1                              /*!< HSI clock selected as I2C1 clock */
/**
  * @}
  */

#if defined(RCC_CCIPR_I2C2SEL)
/** @defgroup RCCEx_I2C2_Clock_Source RCC I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_PCLK1        0x00000000U                                      /*!< APB clock selected as I2C2 clock */
#define RCC_I2C2CLKSOURCE_SYSCLK       RCC_CCIPR_I2C2SEL_0                              /*!< SYSCLK clock selected as I2C2 clock */
#define RCC_I2C2CLKSOURCE_HSI          RCC_CCIPR_I2C2SEL_1                              /*!< HSI clock selected as I2C2 clock */
/**
  * @}
  */
#endif /* RCC_CCIPR_I2C2SEL */

/** @defgroup RCCEx_I2S1_Clock_Source RCC I2S1 Clock Source
  * @{
  */
#if defined(STM32G0C1xx) || defined(STM32G0B1xx) || defined(STM32G0B0xx)
#define RCC_I2S1CLKSOURCE_SYSCLK       0x00000000U                                      /*!< SYSCLK clock selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_PLL          RCC_CCIPR2_I2S1SEL_0                             /*!< PLL "P" selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_HSI          RCC_CCIPR2_I2S1SEL_1                             /*!< HSI clock selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_EXT          RCC_CCIPR2_I2S1SEL                               /*!< External I2S clock source selected as I2S1 clock */
#else
#define RCC_I2S1CLKSOURCE_SYSCLK       0x00000000U                                     /*!< SYSCLK clock selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_PLL          RCC_CCIPR_I2S1SEL_0                             /*!< PLL "P" selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_HSI          RCC_CCIPR_I2S1SEL_1                             /*!< HSI clock selected as I2S1 clock */
#define RCC_I2S1CLKSOURCE_EXT          RCC_CCIPR_I2S1SEL                               /*!< External I2S clock source selected as I2S1 clock */
#endif /* STM32G0C1xx || STM32G0B1xx || STM32G0B0xx */
/**
  * @}
  */

#if defined(RCC_CCIPR2_I2S2SEL)
/** @defgroup RCCEx_I2S2_Clock_Source RCC I2S2 Clock Source
  * @{
  */
#define RCC_I2S2CLKSOURCE_SYSCLK       0x00000000U                                      /*!< SYSCLK clock selected as I2S2 clock */
#define RCC_I2S2CLKSOURCE_PLL          RCC_CCIPR2_I2S2SEL_0                             /*!< PLL "P" selected as I2S2 clock */
#define RCC_I2S2CLKSOURCE_HSI          RCC_CCIPR2_I2S2SEL_1                             /*!< HSI clock selected as I2S2 clock */
#define RCC_I2S2CLKSOURCE_EXT          RCC_CCIPR2_I2S2SEL                               /*!< External I2S clock source selected as I2S2 clock */
/**
  * @}
  */
#endif  /* RCC_CCIPR2_I2S2SEL */

#if defined(RCC_CCIPR_LPTIM1SEL)
/** @defgroup RCCEx_LPTIM1_Clock_Source RCC LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_PCLK1      0x00000000U               /*!< APB clock selected as LPTimer 1 clock */
#define RCC_LPTIM1CLKSOURCE_LSI        RCC_CCIPR_LPTIM1SEL_0     /*!< LSI clock selected as LPTimer 1 clock */
#define RCC_LPTIM1CLKSOURCE_HSI        RCC_CCIPR_LPTIM1SEL_1     /*!< HSI clock selected as LPTimer 1 clock */
#define RCC_LPTIM1CLKSOURCE_LSE        RCC_CCIPR_LPTIM1SEL       /*!< LSE clock selected as LPTimer 1 clock */
/**
  * @}
  */
#endif /* RCC_CCIPR_LPTIM1SEL */

#if defined(RCC_CCIPR_LPTIM2SEL)
/** @defgroup RCCEx_LPTIM2_Clock_Source RCC LPTIM2 Clock Source
  * @{
  */
#define RCC_LPTIM2CLKSOURCE_PCLK1      0x00000000U               /*!< APB clock selected as LPTimer 2 clock */
#define RCC_LPTIM2CLKSOURCE_LSI        RCC_CCIPR_LPTIM2SEL_0     /*!< LSI clock selected as LPTimer 2 clock */
#define RCC_LPTIM2CLKSOURCE_HSI        RCC_CCIPR_LPTIM2SEL_1     /*!< HSI clock selected as LPTimer 2 clock */
#define RCC_LPTIM2CLKSOURCE_LSE        RCC_CCIPR_LPTIM2SEL       /*!< LSE clock selected as LPTimer 2 clock */
/**
  * @}
  */
#endif /* RCC_CCIPR_LPTIM2SEL */

#if defined(RNG)
/** @defgroup RCCEx_RNG_Clock_Source RCC RNG Clock Source
  * @{
  */
#define RCC_RNGCLKSOURCE_NONE          0x00000000U                             /*!< No clock selected */
#define RCC_RNGCLKSOURCE_HSI_DIV8      RCC_CCIPR_RNGSEL_0                      /*!< HSI oscillator divided by 8 clock selected as RNG clock */
#define RCC_RNGCLKSOURCE_SYSCLK        RCC_CCIPR_RNGSEL_1                      /*!< SYSCLK selected as RNG clock */
#define RCC_RNGCLKSOURCE_PLL           (RCC_CCIPR_RNGSEL_0|RCC_CCIPR_RNGSEL_1) /*!< PLL "Q" selected as RNG clock */

/**
  * @}
  */

/** @defgroup RCCEx_RNG_Division_factor RCC RNG Division factor
  * @{
  */
#define RCC_RNGCLK_DIV1           0x00000000U                              /*!< RNG clock not divided  */
#define RCC_RNGCLK_DIV2           RCC_CCIPR_RNGDIV_0                       /*!< RNG clock divided by 2 */
#define RCC_RNGCLK_DIV4           RCC_CCIPR_RNGDIV_1                       /*!< RNG clock divided by 4 */
#define RCC_RNGCLK_DIV8           (RCC_CCIPR_RNGDIV_0|RCC_CCIPR_RNGDIV_1)  /*!< RNG clock divided by 8 */

/**
  * @}
  */
#endif /* RNG */

#if defined(FDCAN1) || defined(FDCAN2)
/** @defgroup RCCEx_FDCAN_Clock_Source RCC FDCAN Clock Source
  * @{
  */
#define RCC_FDCANCLKSOURCE_PCLK1        0x00000000U                        /*!< PCLK1 selected as FDCAN clock */
#define RCC_FDCANCLKSOURCE_PLL          RCC_CCIPR2_FDCANSEL_0              /*!< PLL "Q" selected as FDCAN clock */
#define RCC_FDCANCLKSOURCE_HSE          RCC_CCIPR2_FDCANSEL_1              /*!< HSE oscillator clock selected as FDCAN clock */

/**
  * @}
  */
#endif /* FDCAN1 || FDCAN2 */

#if defined(RCC_CCIPR2_USBSEL)
/** @defgroup RCCEx_USB_Clock_Source USB Clock Source
  * @{
  */
#if defined(RCC_HSI48_SUPPORT)
#define RCC_USBCLKSOURCE_HSI48         0x00000000U            /*!< HSI48 oscillator clock selected as USB clock */
#endif /* RCC_HSI48_SUPPORT */
#define RCC_USBCLKSOURCE_HSE           RCC_CCIPR2_USBSEL_0  /*!< HSE oscillator clock selected as USB clock */
#define RCC_USBCLKSOURCE_PLL           RCC_CCIPR2_USBSEL_1  /*!< PLL "Q" selected as USB clock */
/**
  * @}
  */
#endif /* RCC_CCIPR2_USBSEL */

/** @defgroup RCCEx_ADC_Clock_Source RCC ADC Clock Source
  * @{
  */

#define RCC_ADCCLKSOURCE_SYSCLK       0x00000000U             /*!< SYSCLK used as ADC clock */
#define RCC_ADCCLKSOURCE_PLLADC       RCC_CCIPR_ADCSEL_0      /*!< PLL "P" (PLLADC) used as ADC clock */
#define RCC_ADCCLKSOURCE_HSI          RCC_CCIPR_ADCSEL_1      /*!< HSI used as ADC clock */
/**
  * @}
  */

#if defined(CEC)
/** @defgroup RCCEx_CEC_Clock_Source RCC CEC Clock Source
  * @{
  */
#define RCC_CECCLKSOURCE_HSI_DIV488          0x00000000U      /*!< HSI oscillator clock divided by 488 used as default CEC clock */
#define RCC_CECCLKSOURCE_LSE                 RCC_CCIPR_CECSEL /*!< LSE oscillator clock  used as CEC clock */
/**
  * @}
  */
#endif /* CEC */

#if defined(RCC_CCIPR_TIM1SEL)
/** @defgroup RCCEx_TIM1_Clock_Source RCC TIM1 Clock Source
  * @{
  */
#define RCC_TIM1CLKSOURCE_PCLK1       0x00000000U             /*!< APB clock selected as Timer 1 clock */
#define RCC_TIM1CLKSOURCE_PLL         RCC_CCIPR_TIM1SEL       /*!< PLL "Q" clock selected as Timer 1 clock */
/**
  * @}
  */
#endif /* RCC_CCIPR_TIM1SEL */

#if defined(RCC_CCIPR_TIM15SEL)
/** @defgroup RCCEx_TIM15_Clock_Source RCC TIM15 Clock Source
  * @{
  */
#define RCC_TIM15CLKSOURCE_PCLK1      0x00000000U             /*!< APB clock selected as Timer 15 clock */
#define RCC_TIM15CLKSOURCE_PLL        RCC_CCIPR_TIM15SEL      /*!< PLL "Q" clock selected as Timer 15 clock */

/**
  * @}
  */
#endif /* RCC_CCIPR_TIM15SEL */

#if defined(CRS)

/** @defgroup RCCEx_CRS_Status RCCEx CRS Status
  * @{
  */
#define RCC_CRS_NONE                   0x00000000U
#define RCC_CRS_TIMEOUT                0x00000001U
#define RCC_CRS_SYNCOK                 0x00000002U
#define RCC_CRS_SYNCWARN               0x00000004U
#define RCC_CRS_SYNCERR                0x00000008U
#define RCC_CRS_SYNCMISS               0x00000010U
#define RCC_CRS_TRIMOVF                0x00000020U
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroSource RCCEx CRS SynchroSource
  * @{
  */
#define RCC_CRS_SYNC_SOURCE_GPIO       0x00000000U             /*!< Synchro Signal source GPIO */
#define RCC_CRS_SYNC_SOURCE_LSE        CRS_CFGR_SYNCSRC_0      /*!< Synchro Signal source LSE */
#define RCC_CRS_SYNC_SOURCE_USB        CRS_CFGR_SYNCSRC_1      /*!< Synchro Signal source USB SOF (default)*/
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroDivider RCCEx CRS SynchroDivider
  * @{
  */
#define RCC_CRS_SYNC_DIV1        0x00000000U                               /*!< Synchro Signal not divided (default) */
#define RCC_CRS_SYNC_DIV2        CRS_CFGR_SYNCDIV_0                        /*!< Synchro Signal divided by 2 */
#define RCC_CRS_SYNC_DIV4        CRS_CFGR_SYNCDIV_1                        /*!< Synchro Signal divided by 4 */
#define RCC_CRS_SYNC_DIV8        (CRS_CFGR_SYNCDIV_1 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 8 */
#define RCC_CRS_SYNC_DIV16       CRS_CFGR_SYNCDIV_2                        /*!< Synchro Signal divided by 16 */
#define RCC_CRS_SYNC_DIV32       (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 32 */
#define RCC_CRS_SYNC_DIV64       (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_1) /*!< Synchro Signal divided by 64 */
#define RCC_CRS_SYNC_DIV128      CRS_CFGR_SYNCDIV                          /*!< Synchro Signal divided by 128 */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroPolarity RCCEx CRS SynchroPolarity
  * @{
  */
#define RCC_CRS_SYNC_POLARITY_RISING   0x00000000U         /*!< Synchro Active on rising edge (default) */
#define RCC_CRS_SYNC_POLARITY_FALLING  CRS_CFGR_SYNCPOL    /*!< Synchro Active on falling edge */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ReloadValueDefault RCCEx CRS ReloadValueDefault
  * @{
  */
#define RCC_CRS_RELOADVALUE_DEFAULT    0x0000BB7FU   /*!< The reset value of the RELOAD field corresponds
                                                          to a target frequency of 48 MHz and a synchronization signal frequency of 1 kHz (SOF signal from USB). */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ErrorLimitDefault RCCEx CRS ErrorLimitDefault
  * @{
  */
#define RCC_CRS_ERRORLIMIT_DEFAULT     0x00000022U   /*!< Default Frequency error limit */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_HSI48CalibrationDefault RCCEx CRS HSI48CalibrationDefault
  * @{
  */
#define RCC_CRS_HSI48CALIBRATION_DEFAULT 0x00000040U /*!< The default value is 64, which corresponds to the middle of the trimming interval.
                                                          The trimming step is specified in the product datasheet. A higher TRIM value
                                                          corresponds to a higher output frequency */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_FreqErrorDirection RCCEx CRS FreqErrorDirection
  * @{
  */
#define RCC_CRS_FREQERRORDIR_UP        0x00000000U   /*!< Upcounting direction, the actual frequency is above the target */
#define RCC_CRS_FREQERRORDIR_DOWN      CRS_ISR_FEDIR /*!< Downcounting direction, the actual frequency is below the target */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Interrupt_Sources RCCEx CRS Interrupt Sources
  * @{
  */
#define RCC_CRS_IT_SYNCOK              CRS_CR_SYNCOKIE       /*!< SYNC event OK */
#define RCC_CRS_IT_SYNCWARN            CRS_CR_SYNCWARNIE     /*!< SYNC warning */
#define RCC_CRS_IT_ERR                 CRS_CR_ERRIE          /*!< Error */
#define RCC_CRS_IT_ESYNC               CRS_CR_ESYNCIE        /*!< Expected SYNC */
#define RCC_CRS_IT_SYNCERR             CRS_CR_ERRIE          /*!< SYNC error */
#define RCC_CRS_IT_SYNCMISS            CRS_CR_ERRIE          /*!< SYNC missed */
#define RCC_CRS_IT_TRIMOVF             CRS_CR_ERRIE           /*!< Trimming overflow or underflow */

/**
  * @}
  */

/** @defgroup RCCEx_CRS_Flags RCCEx CRS Flags
  * @{
  */
#define RCC_CRS_FLAG_SYNCOK            CRS_ISR_SYNCOKF       /*!< SYNC event OK flag     */
#define RCC_CRS_FLAG_SYNCWARN          CRS_ISR_SYNCWARNF     /*!< SYNC warning flag      */
#define RCC_CRS_FLAG_ERR               CRS_ISR_ERRF          /*!< Error flag        */
#define RCC_CRS_FLAG_ESYNC             CRS_ISR_ESYNCF        /*!< Expected SYNC flag     */
#define RCC_CRS_FLAG_SYNCERR           CRS_ISR_SYNCERR       /*!< SYNC error */
#define RCC_CRS_FLAG_SYNCMISS          CRS_ISR_SYNCMISS      /*!< SYNC missed*/
#define RCC_CRS_FLAG_TRIMOVF           CRS_ISR_TRIMOVF       /*!< Trimming overflow or underflow */

/**
  * @}
  */

#endif /* CRS */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
 * @{
 */


/** @brief  Macro to configure the I2C1 clock (I2C1CLK).
  *
  * @param  __I2C1_CLKSOURCE__  specifies the I2C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C1SEL, (uint32_t)(__I2C1_CLKSOURCE__))

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_I2C1SEL)))

#if defined(RCC_CCIPR_I2C2SEL)
/** @brief  Macro to configure the I2C2 clock (I2C2CLK).
  *
  * @param  __I2C2_CLKSOURCE__  specifies the I2C2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_HSI  HSI selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_SYSCLK  System Clock selected as I2C2 clock
  */
#define __HAL_RCC_I2C2_CONFIG(__I2C2_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C2SEL, (uint32_t)(__I2C2_CLKSOURCE__))

/** @brief  Macro to get the I2C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_HSI  HSI selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_SYSCLK  System Clock selected as I2C2 clock
  */
#define __HAL_RCC_GET_I2C2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_I2C2SEL)))
#endif /* RCC_CCIPR_I2C2SEL */

/** @brief  Macro to configure the I2S1 clock (I2S1CLK).
  *
  * @param  __I2S1_CLKSOURCE__  specifies the I2S1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2S1CLKSOURCE_SYSCLK  System Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_PLL     PLLP Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_HSI     HSI Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_EXT     External clock selected as I2S1 clock
  */
#if defined(STM32G0C1xx) || defined(STM32G0B1xx) || defined(STM32G0B0xx)
#define __HAL_RCC_I2S1_CONFIG(__I2S1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2S1SEL, (uint32_t)(__I2S1_CLKSOURCE__))
#else
#define __HAL_RCC_I2S1_CONFIG(__I2S1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2S1SEL, (uint32_t)(__I2S1_CLKSOURCE__))
#endif /* STM32G0C1xx || STM32G0B1xx || STM32G0B0xx */
/** @brief  Macro to get the I2S1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2S1CLKSOURCE_SYSCLK  System Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_PLL     PLLP Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_HSI     HSI Clock selected as I2S1 clock
  *            @arg @ref RCC_I2S1CLKSOURCE_EXT     External clock selected as I2S1 clock
  */
#if defined(STM32G0C1xx) || defined(STM32G0B1xx) || defined(STM32G0B0xx)
#define __HAL_RCC_GET_I2S1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2S1SEL)))
#else
#define __HAL_RCC_GET_I2S1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_I2S1SEL)))
#endif /* STM32G0C1xx || STM32G0B1xx || STM32G0B0xx */

#if defined(RCC_CCIPR2_I2S2SEL)
/** @brief  Macro to configure the I2S2 clock (I2S2CLK).
  *
  * @param  __I2S2_CLKSOURCE__  specifies the I2S2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2S2CLKSOURCE_SYSCLK  System Clock selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_PLL     PLLP Clock selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_HSI     HSI Clock selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_EXT     External clock selected as I2S2 clock
  */
#define __HAL_RCC_I2S2_CONFIG(__I2S2_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2S2SEL, (uint32_t)(__I2S2_CLKSOURCE__))

/** @brief  Macro to get the I2S2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2S2CLKSOURCE_SYSCLK  System Clock selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_PLL     PLLP Clock selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_HSI     HSI Clock selected as I2S2 clock
  *            @arg @ref RCC_I2S2CLKSOURCE_EXT     External clock selected as I2S2 clock
  */
#define __HAL_RCC_GET_I2S2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2S2SEL)))
#endif /* RCC_CCIPR2_I2S2SEL */

/** @brief  Macro to configure the USART1 clock (USART1CLK).
  *
  * @param  __USART1_CLKSOURCE__ specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK1   PCLK1 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART1SEL, (uint32_t)(__USART1_CLKSOURCE__))

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK1   PCLK1 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_USART1SEL)))

#if defined(RCC_CCIPR_USART2SEL)
/** @brief  Macro to configure the USART2 clock (USART2CLK).
  *
  * @param  __USART2_CLKSOURCE__ specifies the USART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1   PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  */
#define __HAL_RCC_USART2_CONFIG(__USART2_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART2SEL, (uint32_t)(__USART2_CLKSOURCE__))

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1   PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_USART2SEL)))
#endif /* RCC_CCIPR_USART2SEL */

#if defined(RCC_CCIPR_USART3SEL)
/** @brief  Macro to configure the USART3 clock (USART3CLK).
  *
  * @param  __USART3_CLKSOURCE__ specifies the USART3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART3CLKSOURCE_PCLK1   PCLK1 selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_HSI  HSI selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_SYSCLK  System Clock selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_LSE  LSE selected as USART3 clock
  */
#define __HAL_RCC_USART3_CONFIG(__USART3_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART3SEL, (uint32_t)(__USART3_CLKSOURCE__))

/** @brief  Macro to get the USART3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART3CLKSOURCE_PCLK1   PCLK1 selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_HSI  HSI selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_SYSCLK  System Clock selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_LSE  LSE selected as USART3 clock
  */
#define __HAL_RCC_GET_USART3_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_USART3SEL)))
#endif /* RCC_CCIPR_USART3SEL */

#if defined(RCC_CCIPR_LPUART1SEL)
/** @brief  Macro to configure the LPUART1 clock (LPUART1CLK).
  *
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK1   PCLK1 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPUART1SEL, (uint32_t)(__LPUART1_CLKSOURCE__))

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK1  PCLK1 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPUART1SEL)))
#endif /* RCC_CCIPR_LPUART1SEL */

#if defined(RCC_CCIPR_LPUART2SEL)
/** @brief  Macro to configure the LPUART2 clock (LPUART2CLK).
  *
  * @param  __LPUART2_CLKSOURCE__ specifies the LPUART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART2CLKSOURCE_PCLK1   PCLK1 selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_HSI  HSI selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_SYSCLK  System Clock selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_LSE  LSE selected as LPUART2 clock
  */
#define __HAL_RCC_LPUART2_CONFIG(__LPUART2_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPUART2SEL, (uint32_t)(__LPUART2_CLKSOURCE__))

/** @brief  Macro to get the LPUART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART2CLKSOURCE_PCLK1  PCLK1 selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_HSI HSI selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_SYSCLK System Clock selected as LPUART2 clock
  *            @arg @ref RCC_LPUART2CLKSOURCE_LSE LSE selected as LPUART2 clock
  */
#define __HAL_RCC_GET_LPUART2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPUART2SEL)))
#endif /* RCC_CCIPR_LPUART2SEL */

#if defined(RCC_CCIPR_LPTIM1SEL)
/** @brief  Macro to configure the LPTIM1 clock (LPTIM1CLK).
  *
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK1  PCLK1 selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  HSI  selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  LSI  selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE  selected as LPTIM1 clock
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPTIM1SEL, (uint32_t)(__LPTIM1_CLKSOURCE__))

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK1  PCLK1 selected as LPUART1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPTIM1SEL)))
#endif /* RCC_CCIPR_LPTIM1SEL */

#if defined(RCC_CCIPR_LPTIM2SEL)
/** @brief  Macro to configure the LPTIM2 clock (LPTIM2CLK).
  *
  * @param  __LPTIM2_CLKSOURCE__ specifies the LPTIM2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK1 selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI  HSI  selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI  LSI  selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE  LSE  selected as LPTIM2 clock
  */
#define __HAL_RCC_LPTIM2_CONFIG(__LPTIM2_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPTIM2SEL, (uint32_t)(__LPTIM2_CLKSOURCE__))

/** @brief  Macro to get the LPTIM2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK1 selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI  System Clock selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE  LSE selected as LPTIM2 clock
  */
#define __HAL_RCC_GET_LPTIM2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_LPTIM2SEL)))
#endif /* RCC_CCIPR_LPTIM2SEL */

#if defined(CEC)
/** @brief  Macro to configure the CEC clock (CECCLK).
  *
  * @param  __CEC_CLKSOURCE__ specifies the CEC clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_CECCLKSOURCE_HSI_DIV488 HSI_DIV_488 selected as CEC clock
  *            @arg @ref RCC_CECCLKSOURCE_LSE LSE selected as CEC clock
  */
#define __HAL_RCC_CEC_CONFIG(__CEC_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_CECSEL, (uint32_t)(__CEC_CLKSOURCE__))

/** @brief  Macro to get the CEC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_CECCLKSOURCE_HSI_DIV488 HSI_DIV_488 Clock selected as CEC clock
  *            @arg @ref RCC_CECCLKSOURCE_LSE  LSE selected as CEC clock
  */
#define __HAL_RCC_GET_CEC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_CECSEL)))
#endif /* CEC */

#if defined(RNG)
/** @brief  Macro to configure the RNG clock.
  *
  *
  * @param  __RNG_CLKSOURCE__ specifies the RNG clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RNGCLKSOURCE_NONE  No clock selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_HSI_DIV8 HSI Clock divided by 8 selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_SYSCLK System Clock selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_PLL PLLQ Output Clock selected as RNG clock
  */
#define __HAL_RCC_RNG_CONFIG(__RNG_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_RNGSEL, (uint32_t)(__RNG_CLKSOURCE__))

/** @brief  Macro to get the RNG clock.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_RNGCLKSOURCE_NONE  No clock selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_HSI_DIV8 HSI Clock divide by 8 selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_SYSCLK System clock selected as RNG clock
  *            @arg @ref RCC_RNGCLKSOURCE_PLL PLLQ Output Clock selected as RNG clock
  */
#define __HAL_RCC_GET_RNG_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_RNGSEL)))

/** @brief  Macro to configure the RNG clock.
  *
  *
  * @param  __RNG_CLKDIV__ specifies the RNG clock division factor.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RNGCLK_DIV1  RNG Clock not divided
  *            @arg @ref RCC_RNGCLK_DIV2  RNG Clock divided by 2
  *            @arg @ref RCC_RNGCLK_DIV4  RNG Clock divided by 4
  *            @arg @ref RCC_RNGCLK_DIV8  RNG Clock divided by 8
  */
#define __HAL_RCC_RNGDIV_CONFIG(__RNG_CLKDIV__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_RNGDIV, (uint32_t)(__RNG_CLKDIV__))

/** @brief  Macro to get the RNG clock division factor.
  * @retval The division factor can be one of the following values:
  *            @arg @ref RCC_RNGCLK_DIV1   RNG Clock not divided
  *            @arg @ref RCC_RNGCLK_DIV2   RNG Clock divided by 2
  *            @arg @ref RCC_RNGCLK_DIV4   RNG Clock divided by 4
  *            @arg @ref RCC_RNGCLK_DIV8   RNG Clock divided by 8
  */
#define __HAL_RCC_GET_RNG_DIV() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_RNGDIV)))
#endif /* RNG */

/** @brief  Macro to configure the ADC interface clock
  * @param  __ADC_CLKSOURCE__ specifies the ADC digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_PLLADC PLL "P" (PLLADC) Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK System Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSI HSI Clock selected as ADC clock
  */
#define __HAL_RCC_ADC_CONFIG(__ADC_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADCSEL, (uint32_t)(__ADC_CLKSOURCE__))

/** @brief  Macro to get the ADC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADCCLKSOURCE_PLLADC PLL "P" (PLLADC) Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_SYSCLK System Clock selected as ADC clock
  *            @arg @ref RCC_ADCCLKSOURCE_HSI HSI Clock selected as ADC clock
  */
#define __HAL_RCC_GET_ADC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_ADCSEL)))

#if defined(RCC_CCIPR_TIM1SEL)
/** @brief  Macro to configure the TIM1 interface clock
  * @param  __TIM1_CLKSOURCE__ specifies the TIM1 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_TIM1CLKSOURCE_PLL PLLQ Output Clock selected as TIM1 clock
  *            @arg @ref RCC_TIM1CLKSOURCE_PCLK1 System Clock selected as TIM1 clock
  */
#define __HAL_RCC_TIM1_CONFIG(__TIM1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_TIM1SEL, (uint32_t)(__TIM1_CLKSOURCE__))

/** @brief  Macro to get the TIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_TIM1CLKSOURCE_PLL PLLQ Output Clock selected as TIM1 clock
  *            @arg @ref RCC_TIM1CLKSOURCE_PCLK1  System Clock selected as TIM1 clock
  */
#define __HAL_RCC_GET_TIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_TIM1SEL)))
#endif /* RCC_CCIPR_TIM1SEL */

#if defined(RCC_CCIPR_TIM15SEL)
/** @brief  Macro to configure the TIM15 interface clock
  * @param  __TIM15_CLKSOURCE__ specifies the TIM15 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_TIM15CLKSOURCE_PLL PLLQ Output Clock selected as TIM15 clock
  *            @arg RCC_TIM15CLKSOURCE_PCLK1  System Clock selected as TIM15 clock
  */
#define __HAL_RCC_TIM15_CONFIG(__TIM15_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_TIM15SEL, (uint32_t)(__TIM15_CLKSOURCE__))

/** @brief  Macro to get the TIM15 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_TIM15CLKSOURCE_PLL PLLQ Output Clock selected as TIM15 clock
  *            @arg @ref RCC_TIM15CLKSOURCE_PCLK1  System Clock selected as TIM15 clock
  */
#define __HAL_RCC_GET_TIM15_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_TIM15SEL)))
#endif /* RCC_CCIPR_TIM15SEL */

#if defined(RCC_CCIPR2_USBSEL)
/** @brief  Macro to configure the USB interface clock
  * @param  __USB_CLKSOURCE__ specifies the USB digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_USBCLKSOURCE_PLL    PLLQ Output Clock selected as USB clock (*)
  *            @arg @ref RCC_USBCLKSOURCE_HSE    HSE Output Clock selected as USB clock
  *            @arg @ref RCC_USBCLKSOURCE_HSI48  HSI48 Clock selected as USB clock (*)
  *  (*) Feature not available on all devices
  */
#define __HAL_RCC_USB_CONFIG(__USB_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_USBSEL, (uint32_t)(__USB_CLKSOURCE__))

/** @brief  Macro to get the USB clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USBCLKSOURCE_HSI48  HSI48 Clock selected as USB clock
  *            @arg @ref RCC_USBCLKSOURCE_HSE    HSE Output Clock selected as USB clock
  *            @arg @ref RCC_USBCLKSOURCE_PLL    PLLQ Output Clock selected as USB clock
  */
#define __HAL_RCC_GET_USB_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_USBSEL)))
#endif /* RCC_CCIPR2_USBSEL */

#if defined(FDCAN1) || defined(FDCAN2)
/** @brief  Macro to configure the FDCAN interface clock
  * @param  __FDCAN_CLKSOURCE__ specifies the FDCAN digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_FDCANCLKSOURCE_PLL    PLLQ Output Clock selected as FDCAN clock
  *            @arg RCC_FDCANCLKSOURCE_PCLK1  System Clock selected as FDCAN clock
  *            @arg RCC_FDCANCLKSOURCE_HSE    HSE Clock selected as FDCAN clock
  */
#define __HAL_RCC_FDCAN_CONFIG(__FDCAN_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_FDCANSEL, (uint32_t)(__FDCAN_CLKSOURCE__))

/** @brief  Macro to get the FDCAN clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_FDCANCLKSOURCE_PLL    PLLQ Output Clock selected as FDCAN clock
  *            @arg @ref RCC_FDCANCLKSOURCE_PCLK1  System Clock selected as FDCAN clock
  *            @arg @ref RCC_FDCANCLKSOURCE_HSE    HSE Clock selected as FDCAN clock
  */
#define __HAL_RCC_GET_FDCAN_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_FDCANSEL)))
#endif /* FDCAN1 || FDCAN2 */

#if defined(CRS)

/**
  * @brief  Enable the specified CRS interrupts.
  * @param  __INTERRUPT__ specifies the CRS interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *              @arg @ref RCC_CRS_IT_SYNCOK  SYNC event OK interrupt
  *              @arg @ref RCC_CRS_IT_SYNCWARN  SYNC warning interrupt
  *              @arg @ref RCC_CRS_IT_ERR  Synchronization or trimming error interrupt
  *              @arg @ref RCC_CRS_IT_ESYNC  Expected SYNC interrupt
  * @retval None
  */
#define __HAL_RCC_CRS_ENABLE_IT(__INTERRUPT__)   SET_BIT(CRS->CR, (__INTERRUPT__))

/**
  * @brief  Disable the specified CRS interrupts.
  * @param  __INTERRUPT__ specifies the CRS interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *              @arg @ref RCC_CRS_IT_SYNCOK  SYNC event OK interrupt
  *              @arg @ref RCC_CRS_IT_SYNCWARN  SYNC warning interrupt
  *              @arg @ref RCC_CRS_IT_ERR  Synchronization or trimming error interrupt
  *              @arg @ref RCC_CRS_IT_ESYNC  Expected SYNC interrupt
  * @retval None
  */
#define __HAL_RCC_CRS_DISABLE_IT(__INTERRUPT__)  CLEAR_BIT(CRS->CR, (__INTERRUPT__))

/** @brief  Check whether the CRS interrupt has occurred or not.
  * @param  __INTERRUPT__ specifies the CRS interrupt source to check.
  *         This parameter can be one of the following values:
  *              @arg @ref RCC_CRS_IT_SYNCOK  SYNC event OK interrupt
  *              @arg @ref RCC_CRS_IT_SYNCWARN  SYNC warning interrupt
  *              @arg @ref RCC_CRS_IT_ERR  Synchronization or trimming error interrupt
  *              @arg @ref RCC_CRS_IT_ESYNC  Expected SYNC interrupt
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_RCC_CRS_GET_IT_SOURCE(__INTERRUPT__)  ((READ_BIT(CRS->CR, (__INTERRUPT__)) != 0U) ? SET : RESET)

/** @brief  Clear the CRS interrupt pending bits
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *              @arg @ref RCC_CRS_IT_SYNCOK  SYNC event OK interrupt
  *              @arg @ref RCC_CRS_IT_SYNCWARN  SYNC warning interrupt
  *              @arg @ref RCC_CRS_IT_ERR  Synchronization or trimming error interrupt
  *              @arg @ref RCC_CRS_IT_ESYNC  Expected SYNC interrupt
  *              @arg @ref RCC_CRS_IT_TRIMOVF  Trimming overflow or underflow interrupt
  *              @arg @ref RCC_CRS_IT_SYNCERR  SYNC error interrupt
  *              @arg @ref RCC_CRS_IT_SYNCMISS  SYNC missed interrupt
  */
/* CRS IT Error Mask */
#define  RCC_CRS_IT_ERROR_MASK                 (RCC_CRS_IT_TRIMOVF | RCC_CRS_IT_SYNCERR | RCC_CRS_IT_SYNCMISS)

#define __HAL_RCC_CRS_CLEAR_IT(__INTERRUPT__)  do { \
                                                 if(((__INTERRUPT__) & RCC_CRS_IT_ERROR_MASK) != 0U) \
                                                 { \
                                                   WRITE_REG(CRS->ICR, CRS_ICR_ERRC | ((__INTERRUPT__) & ~RCC_CRS_IT_ERROR_MASK)); \
                                                 } \
                                                 else \
                                                 { \
                                                   WRITE_REG(CRS->ICR, (__INTERRUPT__)); \
                                                 } \
                                               } while(0)

/**
  * @brief  Check whether the specified CRS flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_CRS_FLAG_SYNCOK  SYNC event OK
  *              @arg @ref RCC_CRS_FLAG_SYNCWARN  SYNC warning
  *              @arg @ref RCC_CRS_FLAG_ERR  Error
  *              @arg @ref RCC_CRS_FLAG_ESYNC  Expected SYNC
  *              @arg @ref RCC_CRS_FLAG_TRIMOVF  Trimming overflow or underflow
  *              @arg @ref RCC_CRS_FLAG_SYNCERR  SYNC error
  *              @arg @ref RCC_CRS_FLAG_SYNCMISS  SYNC missed
  * @retval The new state of _FLAG_ (TRUE or FALSE).
  */
#define __HAL_RCC_CRS_GET_FLAG(__FLAG__)  (READ_BIT(CRS->ISR, (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear the CRS specified FLAG.
  * @param __FLAG__ specifies the flag to clear.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_CRS_FLAG_SYNCOK  SYNC event OK
  *              @arg @ref RCC_CRS_FLAG_SYNCWARN  SYNC warning
  *              @arg @ref RCC_CRS_FLAG_ERR  Error
  *              @arg @ref RCC_CRS_FLAG_ESYNC  Expected SYNC
  *              @arg @ref RCC_CRS_FLAG_TRIMOVF  Trimming overflow or underflow
  *              @arg @ref RCC_CRS_FLAG_SYNCERR  SYNC error
  *              @arg @ref RCC_CRS_FLAG_SYNCMISS  SYNC missed
  * @note RCC_CRS_FLAG_ERR clears RCC_CRS_FLAG_TRIMOVF, RCC_CRS_FLAG_SYNCERR, RCC_CRS_FLAG_SYNCMISS and consequently RCC_CRS_FLAG_ERR
  * @retval None
  */

/* CRS Flag Error Mask */
#define RCC_CRS_FLAG_ERROR_MASK                (RCC_CRS_FLAG_TRIMOVF | RCC_CRS_FLAG_SYNCERR | RCC_CRS_FLAG_SYNCMISS)

#define __HAL_RCC_CRS_CLEAR_FLAG(__FLAG__)     do { \
                                                 if(((__FLAG__) & RCC_CRS_FLAG_ERROR_MASK) != 0U) \
                                                 { \
                                                   WRITE_REG(CRS->ICR, CRS_ICR_ERRC | ((__FLAG__) & ~RCC_CRS_FLAG_ERROR_MASK)); \
                                                 } \
                                                 else \
                                                 { \
                                                   WRITE_REG(CRS->ICR, (__FLAG__)); \
                                                 } \
                                               } while(0)

#endif /* CRS */

/**
  * @}
  */

#if defined(CRS)

/** @defgroup RCCEx_CRS_Extended_Features RCCEx CRS Extended Features
  * @{
  */
/**
  * @brief  Enable the oscillator clock for frequency error counter.
  * @note   when the CEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_FREQ_ERROR_COUNTER_ENABLE()  SET_BIT(CRS->CR, CRS_CR_CEN)

/**
  * @brief  Disable the oscillator clock for frequency error counter.
  * @retval None
  */
#define __HAL_RCC_CRS_FREQ_ERROR_COUNTER_DISABLE() CLEAR_BIT(CRS->CR, CRS_CR_CEN)

/**
  * @brief  Enable the automatic hardware adjustment of TRIM bits.
  * @note   When the AUTOTRIMEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_AUTOMATIC_CALIB_ENABLE()     SET_BIT(CRS->CR, CRS_CR_AUTOTRIMEN)

/**
  * @brief  Enable or disable the automatic hardware adjustment of TRIM bits.
  * @retval None
  */
#define __HAL_RCC_CRS_AUTOMATIC_CALIB_DISABLE()    CLEAR_BIT(CRS->CR, CRS_CR_AUTOTRIMEN)

/**
  * @brief  Macro to calculate reload value to be set in CRS register according to target and sync frequencies
  * @note   The RELOAD value should be selected according to the ratio between the target frequency and the frequency
  *             of the synchronization source after prescaling. It is then decreased by one in order to
  *             reach the expected synchronization on the zero value. The formula is the following:
  *             RELOAD = (fTARGET / fSYNC) -1
  * @param  __FTARGET__ Target frequency (value in Hz)
  * @param  __FSYNC__ Synchronization signal frequency (value in Hz)
  * @retval None
  */
#define __HAL_RCC_CRS_RELOADVALUE_CALCULATE(__FTARGET__, __FSYNC__)  (((__FTARGET__) / (__FSYNC__)) - 1U)

/**
  * @}
  */

#endif /* CRS */

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

void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);

/**
  * @}
  */

#if defined(CRS)

/** @addtogroup RCCEx_Exported_Functions_Group3
  * @{
  */

void              HAL_RCCEx_CRSConfig(RCC_CRSInitTypeDef *pInit);
void              HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void);
void              HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo);
uint32_t          HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout);
void              HAL_RCCEx_CRS_IRQHandler(void);
void              HAL_RCCEx_CRS_SyncOkCallback(void);
void              HAL_RCCEx_CRS_SyncWarnCallback(void);
void              HAL_RCCEx_CRS_ExpectedSyncCallback(void);
void              HAL_RCCEx_CRS_ErrorCallback(uint32_t Error);

/**
  * @}
  */

#endif /* CRS */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCCEx_Private_Macros RCCEx Private Macros
  * @{
  */

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))

#if defined(STM32G0C1xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)  == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART3)  == RCC_PERIPHCLK_USART3)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART2) == RCC_PERIPHCLK_LPUART2) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C2)    == RCC_PERIPHCLK_I2C2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S2)    == RCC_PERIPHCLK_I2S2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM2)  == RCC_PERIPHCLK_LPTIM2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)     == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_CEC)     == RCC_PERIPHCLK_CEC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_FDCAN)   == RCC_PERIPHCLK_FDCAN)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_USB)     == RCC_PERIPHCLK_USB)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM15)   == RCC_PERIPHCLK_TIM15))

#elif defined(STM32G0B1xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)  == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART3)  == RCC_PERIPHCLK_USART3)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART2) == RCC_PERIPHCLK_LPUART2) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C2)    == RCC_PERIPHCLK_I2C2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S2)    == RCC_PERIPHCLK_I2S2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM2)  == RCC_PERIPHCLK_LPTIM2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_CEC)     == RCC_PERIPHCLK_CEC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_FDCAN)   == RCC_PERIPHCLK_FDCAN)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_USB)     == RCC_PERIPHCLK_USB)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM15)   == RCC_PERIPHCLK_TIM15))

#elif defined(STM32G0B0xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)  == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART3)  == RCC_PERIPHCLK_USART3)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C2)    == RCC_PERIPHCLK_I2C2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S2)    == RCC_PERIPHCLK_I2S2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_USB)     == RCC_PERIPHCLK_USB))

#elif defined(STM32G081xx)
#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)  == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM2)  == RCC_PERIPHCLK_LPTIM2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)     == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_CEC)     == RCC_PERIPHCLK_CEC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM15)   == RCC_PERIPHCLK_TIM15))
#elif defined(STM32G071xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)  == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM2)  == RCC_PERIPHCLK_LPTIM2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_CEC)     == RCC_PERIPHCLK_CEC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM15)   == RCC_PERIPHCLK_TIM15))

#elif defined(STM32G070xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)  == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC))

#elif defined(STM32G061xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM2)  == RCC_PERIPHCLK_LPTIM2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)     == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM15)   == RCC_PERIPHCLK_TIM15))

#elif defined(STM32G051xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM2)  == RCC_PERIPHCLK_LPTIM2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM15)   == RCC_PERIPHCLK_TIM15))

#elif defined(STM32G041xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM2)  == RCC_PERIPHCLK_LPTIM2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)     == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1))

#elif defined(STM32G031xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)  == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM2)  == RCC_PERIPHCLK_LPTIM2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_TIM1)    == RCC_PERIPHCLK_TIM1))

#elif defined(STM32G030xx) || defined(STM32G050xx) 

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)  == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)    == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S1)    == RCC_PERIPHCLK_I2S1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC)     == RCC_PERIPHCLK_ADC)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)     == RCC_PERIPHCLK_RTC))
#endif /* STM32G0C1xx */

#define IS_RCC_USART1CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_USART1CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_USART1CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_USART1CLKSOURCE_HSI))

#if defined(RCC_CCIPR_USART2SEL)
#define IS_RCC_USART2CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USART2CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_USART2CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_USART2CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_USART2CLKSOURCE_HSI))
#endif /* RCC_CCIPR_USART2SEL */

#if defined(RCC_CCIPR_USART3SEL)
#define IS_RCC_USART3CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USART3CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_USART3CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_USART3CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_USART3CLKSOURCE_HSI))
#endif /* RCC_CCIPR_USART3SEL */

#if defined(LPUART1)
#define IS_RCC_LPUART1CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_LPUART1CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_LPUART1CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_LPUART1CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_LPUART1CLKSOURCE_HSI))
#endif /* LPUART1 */

#if defined(LPUART2)
#define IS_RCC_LPUART2CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_LPUART2CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_LPUART2CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_LPUART2CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_LPUART2CLKSOURCE_HSI))
#endif /* LPUART2 */

#define IS_RCC_I2C1CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2C1CLKSOURCE_PCLK1)   || \
                ((__SOURCE__) == RCC_I2C1CLKSOURCE_SYSCLK)  || \
                ((__SOURCE__) == RCC_I2C1CLKSOURCE_HSI))

#if defined(RCC_CCIPR_I2C2SEL)
#define IS_RCC_I2C2CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2C2CLKSOURCE_PCLK1)   || \
                ((__SOURCE__) == RCC_I2C2CLKSOURCE_SYSCLK)  || \
                ((__SOURCE__) == RCC_I2C2CLKSOURCE_HSI))

#endif /* RCC_CCIPR_I2C2SEL */

#define IS_RCC_I2S1CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2S1CLKSOURCE_SYSCLK)|| \
                ((__SOURCE__) == RCC_I2S1CLKSOURCE_PLL)   || \
                ((__SOURCE__) == RCC_I2S1CLKSOURCE_HSI)   || \
                ((__SOURCE__) == RCC_I2S1CLKSOURCE_EXT))

#if defined(RCC_CCIPR2_I2S2SEL)
#define IS_RCC_I2S2CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2S2CLKSOURCE_SYSCLK)|| \
                ((__SOURCE__) == RCC_I2S2CLKSOURCE_PLL)   || \
                ((__SOURCE__) == RCC_I2S2CLKSOURCE_HSI)   || \
                ((__SOURCE__) == RCC_I2S2CLKSOURCE_EXT))
#endif /* RCC_CCIPR2_I2S2SEL */

#if defined(RCC_CCIPR_LPTIM1SEL)
#define IS_RCC_LPTIM1CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_LPTIM1CLKSOURCE_PCLK1)|| \
                ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSI)  || \
                ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_HSI)  || \
                ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSE))
#endif /* RCC_CCIPR_LPTIM1SEL */

#if defined(RCC_CCIPR_LPTIM2SEL)
#define IS_RCC_LPTIM2CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_LPTIM2CLKSOURCE_PCLK1)|| \
                ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSI)  || \
                ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_HSI)  || \
                ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSE))
#endif /* RCC_CCIPR_LPTIM2SEL */

#define IS_RCC_ADCCLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_ADCCLKSOURCE_PLLADC)  || \
                ((__SOURCE__) == RCC_ADCCLKSOURCE_SYSCLK)  || \
                ((__SOURCE__) == RCC_ADCCLKSOURCE_HSI))

#if defined(RNG)
#define IS_RCC_RNGCLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_RNGCLKSOURCE_NONE)         || \
                ((__SOURCE__) == RCC_RNGCLKSOURCE_HSI_DIV8)     || \
                ((__SOURCE__) == RCC_RNGCLKSOURCE_SYSCLK)       || \
                ((__SOURCE__) == RCC_RNGCLKSOURCE_PLL))
#define IS_RCC_RNGDIV(__DIV__)  \
               (((__DIV__) == RCC_RNGCLK_DIV1) || \
                ((__DIV__) == RCC_RNGCLK_DIV2) || \
                ((__DIV__) == RCC_RNGCLK_DIV4) || \
                ((__DIV__) == RCC_RNGCLK_DIV8))
#endif /* RNG */

#if defined(CEC)
#define IS_RCC_CECCLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_CECCLKSOURCE_HSI_DIV488)|| \
                ((__SOURCE__) == RCC_CECCLKSOURCE_LSE))
#endif /* CEC */

#if defined(FDCAN1) || defined(FDCAN2)
#define IS_RCC_FDCANCLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_FDCANCLKSOURCE_HSE)|| \
                ((__SOURCE__) == RCC_FDCANCLKSOURCE_PLL)|| \
                ((__SOURCE__) == RCC_FDCANCLKSOURCE_PCLK1))

#endif /* FDCAN1 */

#if defined(RCC_HSI48_SUPPORT)
#define IS_RCC_USBCLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USBCLKSOURCE_HSI48)|| \
                ((__SOURCE__) == RCC_USBCLKSOURCE_HSE)  || \
                ((__SOURCE__) == RCC_USBCLKSOURCE_PLL))
#else
#define IS_RCC_USBCLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USBCLKSOURCE_HSE)|| \
                ((__SOURCE__) == RCC_USBCLKSOURCE_PLL))
#endif /* RCC_HSI48_SUPPORT */

#if defined(RCC_CCIPR_TIM1SEL)
#define IS_RCC_TIM1CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_TIM1CLKSOURCE_PLL)     || \
                ((__SOURCE__) == RCC_TIM1CLKSOURCE_PCLK1))
#endif /* RCC_CCIPR_TIM1SEL */

#if defined(RCC_CCIPR_TIM15SEL)
#define IS_RCC_TIM15CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_TIM15CLKSOURCE_PLL)     || \
                ((__SOURCE__) == RCC_TIM15CLKSOURCE_PCLK1))
#endif /* RCC_CCIPR_TIM15SEL */

#if defined(CRS)

#define IS_RCC_CRS_SYNC_SOURCE(__SOURCE__) (((__SOURCE__) == RCC_CRS_SYNC_SOURCE_GPIO) || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_LSE)  || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_USB))

#define IS_RCC_CRS_SYNC_DIV(__DIV__)       (((__DIV__) == RCC_CRS_SYNC_DIV1)  || ((__DIV__) == RCC_CRS_SYNC_DIV2)  || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV4)  || ((__DIV__) == RCC_CRS_SYNC_DIV8)  || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV16) || ((__DIV__) == RCC_CRS_SYNC_DIV32) || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV64) || ((__DIV__) == RCC_CRS_SYNC_DIV128))

#define IS_RCC_CRS_SYNC_POLARITY(__POLARITY__) (((__POLARITY__) == RCC_CRS_SYNC_POLARITY_RISING) || \
                                                ((__POLARITY__) == RCC_CRS_SYNC_POLARITY_FALLING))

#define IS_RCC_CRS_RELOADVALUE(__VALUE__)  (((__VALUE__) <= 0xFFFFU))

#define IS_RCC_CRS_ERRORLIMIT(__VALUE__)   (((__VALUE__) <= 0xFFU))

#define IS_RCC_CRS_HSI48CALIBRATION(__VALUE__) (((__VALUE__) <= 0x7FU))

#define IS_RCC_CRS_FREQERRORDIR(__DIR__)   (((__DIR__) == RCC_CRS_FREQERRORDIR_UP) || \
                                            ((__DIR__) == RCC_CRS_FREQERRORDIR_DOWN))

#endif /* CRS */

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

#endif /* STM32G0xx_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
