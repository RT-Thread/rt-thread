/**
  ******************************************************************************
  * @file    stm32g4xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#ifndef STM32G4xx_HAL_RCC_EX_H
#define STM32G4xx_HAL_RCC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
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

  uint32_t Usart2ClockSelection;   /*!< Specifies USART2 clock source.
                                        This parameter can be a value of @ref RCCEx_USART2_Clock_Source */

  uint32_t Usart3ClockSelection;   /*!< Specifies USART3 clock source.
                                        This parameter can be a value of @ref RCCEx_USART3_Clock_Source */

#if defined(UART4)
  uint32_t Uart4ClockSelection;    /*!< Specifies UART4 clock source.
                                        This parameter can be a value of @ref RCCEx_UART4_Clock_Source */
#endif /* UART4 */

#if defined(UART5)
  uint32_t Uart5ClockSelection;    /*!< Specifies UART5 clock source.
                                        This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

#endif /* UART5 */

  uint32_t Lpuart1ClockSelection;  /*!< Specifies LPUART1 clock source.
                                        This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */

  uint32_t I2c1ClockSelection;     /*!< Specifies I2C1 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;     /*!< Specifies I2C2 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t I2c3ClockSelection;     /*!< Specifies I2C3 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

#if defined(I2C4)

  uint32_t I2c4ClockSelection;     /*!< Specifies I2C4 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C4_Clock_Source */
#endif /* I2C4 */

  uint32_t Lptim1ClockSelection;   /*!< Specifies LPTIM1 clock source.
                                        This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source */

  uint32_t Sai1ClockSelection;     /*!< Specifies SAI1 clock source.
                                        This parameter can be a value of @ref RCCEx_SAI1_Clock_Source */

  uint32_t I2sClockSelection;     /*!< Specifies I2S clock source.
                                        This parameter can be a value of @ref RCCEx_I2S_Clock_Source */
#if defined(FDCAN1)

  uint32_t FdcanClockSelection;     /*!< Specifies FDCAN clock source.
                                        This parameter can be a value of @ref RCCEx_FDCAN_Clock_Source */
#endif /* FDCAN1 */
#if defined(USB)

  uint32_t UsbClockSelection;      /*!< Specifies USB clock source (warning: same source for RNG).
                                        This parameter can be a value of @ref RCCEx_USB_Clock_Source */
#endif /* USB */

  uint32_t RngClockSelection;      /*!< Specifies RNG clock source (warning: same source for USB).
                                        This parameter can be a value of @ref RCCEx_RNG_Clock_Source */

  uint32_t Adc12ClockSelection;    /*!< Specifies ADC12 interface clock source.
                                        This parameter can be a value of @ref RCCEx_ADC12_Clock_Source */

#if defined(ADC345_COMMON)
  uint32_t Adc345ClockSelection;   /*!< Specifies ADC345 interface clock source.
                                        This parameter can be a value of @ref RCCEx_ADC345_Clock_Source */
#endif /* ADC345_COMMON */

#if defined(QUADSPI)
  uint32_t QspiClockSelection;     /*!< Specifies QuadSPI clock source.
                                        This parameter can be a value of @ref RCCEx_QSPI_Clock_Source */
#endif

  uint32_t RTCClockSelection;      /*!< Specifies RTC clock source.
                                        This parameter can be a value of @ref RCC_RTC_Clock_Source */
}RCC_PeriphCLKInitTypeDef;

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

}RCC_CRSInitTypeDef;

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

}RCC_CRSSynchroInfoTypeDef;

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
#define RCC_PERIPHCLK_USART2           0x00000002U
#define RCC_PERIPHCLK_USART3           0x00000004U
#if defined(UART4)
#define RCC_PERIPHCLK_UART4            0x00000008U
#endif /* UART4 */
#if defined(UART5)
#define RCC_PERIPHCLK_UART5            0x00000010U
#endif /* UART5 */
#define RCC_PERIPHCLK_LPUART1          0x00000020U
#define RCC_PERIPHCLK_I2C1             0x00000040U
#define RCC_PERIPHCLK_I2C2             0x00000080U
#define RCC_PERIPHCLK_I2C3             0x00000100U
#define RCC_PERIPHCLK_LPTIM1           0x00000200U
#define RCC_PERIPHCLK_SAI1             0x00000400U
#define RCC_PERIPHCLK_I2S              0x00000800U
#if defined(FDCAN1)
#define RCC_PERIPHCLK_FDCAN            0x00001000U
#endif /* FDCAN1 */
#define RCC_PERIPHCLK_USB              0x00002000U
#define RCC_PERIPHCLK_RNG              0x00004000U
#define RCC_PERIPHCLK_ADC12            0x00008000U
#if defined(ADC345_COMMON)
#define RCC_PERIPHCLK_ADC345           0x00010000U
#endif /* ADC345_COMMON */
#if defined(I2C4)
#define RCC_PERIPHCLK_I2C4             0x00020000U
#endif /* I2C4 */
#if defined(QUADSPI)
#define RCC_PERIPHCLK_QSPI             0x00040000U
#endif /* QUADSPI */
#define RCC_PERIPHCLK_RTC              0x00080000U
/**
  * @}
  */


/** @defgroup RCCEx_USART1_Clock_Source USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2      0x00000000U
#define RCC_USART1CLKSOURCE_SYSCLK     RCC_CCIPR_USART1SEL_0
#define RCC_USART1CLKSOURCE_HSI        RCC_CCIPR_USART1SEL_1
#define RCC_USART1CLKSOURCE_LSE        (RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_USART2_Clock_Source USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1      0x00000000U
#define RCC_USART2CLKSOURCE_SYSCLK     RCC_CCIPR_USART2SEL_0
#define RCC_USART2CLKSOURCE_HSI        RCC_CCIPR_USART2SEL_1
#define RCC_USART2CLKSOURCE_LSE        (RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_USART3_Clock_Source USART3 Clock Source
  * @{
  */
#define RCC_USART3CLKSOURCE_PCLK1      0x00000000U
#define RCC_USART3CLKSOURCE_SYSCLK     RCC_CCIPR_USART3SEL_0
#define RCC_USART3CLKSOURCE_HSI        RCC_CCIPR_USART3SEL_1
#define RCC_USART3CLKSOURCE_LSE        (RCC_CCIPR_USART3SEL_0 | RCC_CCIPR_USART3SEL_1)
/**
  * @}
  */

#if defined(UART4)
/** @defgroup RCCEx_UART4_Clock_Source UART4 Clock Source
  * @{
  */
#define RCC_UART4CLKSOURCE_PCLK1       0x00000000U
#define RCC_UART4CLKSOURCE_SYSCLK      RCC_CCIPR_UART4SEL_0
#define RCC_UART4CLKSOURCE_HSI         RCC_CCIPR_UART4SEL_1
#define RCC_UART4CLKSOURCE_LSE         (RCC_CCIPR_UART4SEL_0 | RCC_CCIPR_UART4SEL_1)
/**
  * @}
  */
#endif /* UART4 */

#if defined(UART5)
/** @defgroup RCCEx_UART5_Clock_Source UART5 Clock Source
  * @{
  */
#define RCC_UART5CLKSOURCE_PCLK1       0x00000000U
#define RCC_UART5CLKSOURCE_SYSCLK      RCC_CCIPR_UART5SEL_0
#define RCC_UART5CLKSOURCE_HSI         RCC_CCIPR_UART5SEL_1
#define RCC_UART5CLKSOURCE_LSE         (RCC_CCIPR_UART5SEL_0 | RCC_CCIPR_UART5SEL_1)
/**
  * @}
  */
#endif /* UART5 */

/** @defgroup RCCEx_LPUART1_Clock_Source LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK1     0x00000000U
#define RCC_LPUART1CLKSOURCE_SYSCLK    RCC_CCIPR_LPUART1SEL_0
#define RCC_LPUART1CLKSOURCE_HSI       RCC_CCIPR_LPUART1SEL_1
#define RCC_LPUART1CLKSOURCE_LSE       (RCC_CCIPR_LPUART1SEL_0 | RCC_CCIPR_LPUART1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_I2C1_Clock_Source I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_PCLK1        0x00000000U
#define RCC_I2C1CLKSOURCE_SYSCLK       RCC_CCIPR_I2C1SEL_0
#define RCC_I2C1CLKSOURCE_HSI          RCC_CCIPR_I2C1SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_I2C2_Clock_Source I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_PCLK1        0x00000000U
#define RCC_I2C2CLKSOURCE_SYSCLK       RCC_CCIPR_I2C2SEL_0
#define RCC_I2C2CLKSOURCE_HSI          RCC_CCIPR_I2C2SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_PCLK1        0x00000000U
#define RCC_I2C3CLKSOURCE_SYSCLK       RCC_CCIPR_I2C3SEL_0
#define RCC_I2C3CLKSOURCE_HSI          RCC_CCIPR_I2C3SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_PCLK1      0x00000000U
#define RCC_LPTIM1CLKSOURCE_LSI        RCC_CCIPR_LPTIM1SEL_0
#define RCC_LPTIM1CLKSOURCE_HSI        RCC_CCIPR_LPTIM1SEL_1
#define RCC_LPTIM1CLKSOURCE_LSE        RCC_CCIPR_LPTIM1SEL
/**
  * @}
  */

/** @defgroup RCCEx_SAI1_Clock_Source SAI1 Clock Source
  * @{
  */
#define RCC_SAI1CLKSOURCE_SYSCLK       0x00000000U
#define RCC_SAI1CLKSOURCE_PLL          RCC_CCIPR_SAI1SEL_0
#define RCC_SAI1CLKSOURCE_EXT          RCC_CCIPR_SAI1SEL_1
#define RCC_SAI1CLKSOURCE_HSI          (RCC_CCIPR_SAI1SEL_1 | RCC_CCIPR_SAI1SEL_0)
/**
  * @}
  */

/** @defgroup RCCEx_I2S_Clock_Source I2S Clock Source
  * @{
  */
#define RCC_I2SCLKSOURCE_SYSCLK       0x00000000U
#define RCC_I2SCLKSOURCE_PLL          RCC_CCIPR_I2S23SEL_0
#define RCC_I2SCLKSOURCE_EXT          RCC_CCIPR_I2S23SEL_1
#define RCC_I2SCLKSOURCE_HSI          (RCC_CCIPR_I2S23SEL_1 | RCC_CCIPR_I2S23SEL_0)
/**
  * @}
  */
#if defined(FDCAN1)
/** @defgroup RCCEx_FDCAN_Clock_Source FDCAN Clock Source
  * @{
  */
#define RCC_FDCANCLKSOURCE_HSE          0x00000000U
#define RCC_FDCANCLKSOURCE_PLL          RCC_CCIPR_FDCANSEL_0
#define RCC_FDCANCLKSOURCE_PCLK1        RCC_CCIPR_FDCANSEL_1
/**
  * @}
  */
#endif /* FDCAN1 */

/** @defgroup RCCEx_RNG_Clock_Source RNG Clock Source
  * @{
  */
#define RCC_RNGCLKSOURCE_HSI48         0x00000000U
#define RCC_RNGCLKSOURCE_PLL           RCC_CCIPR_CLK48SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_USB_Clock_Source USB Clock Source
  * @{
  */
#define RCC_USBCLKSOURCE_HSI48         0x00000000U
#define RCC_USBCLKSOURCE_PLL           RCC_CCIPR_CLK48SEL_1
/**
  * @}
  */

/** @defgroup RCCEx_ADC12_Clock_Source ADC12 Clock Source
  * @{
  */
#define RCC_ADC12CLKSOURCE_NONE        0x00000000U
#define RCC_ADC12CLKSOURCE_PLL         RCC_CCIPR_ADC12SEL_0
#define RCC_ADC12CLKSOURCE_SYSCLK      RCC_CCIPR_ADC12SEL_1
/**
  * @}
  */

#if defined(ADC345_COMMON)
/** @defgroup RCCEx_ADC345_Clock_Source ADC345 Clock Source
  * @{
  */
#define RCC_ADC345CLKSOURCE_NONE     0x00000000U
#define RCC_ADC345CLKSOURCE_PLL      RCC_CCIPR_ADC345SEL_0
#define RCC_ADC345CLKSOURCE_SYSCLK   RCC_CCIPR_ADC345SEL_1
/**
  * @}
  */
#endif /* ADC345_COMMON */

#if defined(I2C4)
/** @defgroup RCCEx_I2C4_Clock_Source I2C4 Clock Source
  * @{
  */
#define RCC_I2C4CLKSOURCE_PCLK1        0x00000000U
#define RCC_I2C4CLKSOURCE_SYSCLK       RCC_CCIPR2_I2C4SEL_0
#define RCC_I2C4CLKSOURCE_HSI          RCC_CCIPR2_I2C4SEL_1
/**
  * @}
  */
#endif /* I2C4 */

#if defined(QUADSPI)
/** @defgroup RCCEx_QSPI_Clock_Source QuadSPI Clock Source
  * @{
  */
#define RCC_QSPICLKSOURCE_SYSCLK    0x00000000U
#define RCC_QSPICLKSOURCE_HSI       RCC_CCIPR2_QSPISEL_0
#define RCC_QSPICLKSOURCE_PLL       RCC_CCIPR2_QSPISEL_1
/**
  * @}
  */
#endif /* QUADSPI */

/** @defgroup RCCEx_EXTI_LINE_LSECSS  RCC LSE CSS external interrupt line
  * @{
  */
#define RCC_EXTI_LINE_LSECSS           EXTI_IMR1_IM19        /*!< External interrupt line 19 connected to the LSE CSS EXTI Line */
/**
  * @}
  */

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
#define RCC_CRS_SYNC_POLARITY_RISING   0x00000000U             /*!< Synchro Active on rising edge (default) */
#define RCC_CRS_SYNC_POLARITY_FALLING  CRS_CFGR_SYNCPOL        /*!< Synchro Active on falling edge */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ReloadValueDefault RCCEx CRS ReloadValueDefault
  * @{
  */
#define RCC_CRS_RELOADVALUE_DEFAULT    0x0000BB7FU             /*!< The reset value of the RELOAD field corresponds
                                                                    to a target frequency of 48 MHz and a synchronization signal frequency of 1 kHz (SOF signal from USB). */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ErrorLimitDefault RCCEx CRS ErrorLimitDefault
  * @{
  */
#define RCC_CRS_ERRORLIMIT_DEFAULT     0x00000022U             /*!< Default Frequency error limit */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_HSI48CalibrationDefault RCCEx CRS HSI48CalibrationDefault
  * @{
  */
#define RCC_CRS_HSI48CALIBRATION_DEFAULT 0x00000020U             /*!< The default value is 32, which corresponds to the middle of the trimming interval.
                                                                      The trimming step is around 67 kHz between two consecutive TRIM steps. A higher TRIM value
                                                                      corresponds to a higher output frequency */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_FreqErrorDirection RCCEx CRS FreqErrorDirection
  * @{
  */
#define RCC_CRS_FREQERRORDIR_UP        0x00000000U               /*!< Upcounting direction, the actual frequency is above the target */
#define RCC_CRS_FREQERRORDIR_DOWN      CRS_ISR_FEDIR             /*!< Downcounting direction, the actual frequency is below the target */
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

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
 * @{
 */

/** @brief  Macro to configure the USART1 clock (USART1CLK).
  *
  * @param  __USART1_CLKSOURCE__ specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2  PCLK2 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  * @retval None
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART1SEL, (__USART1_CLKSOURCE__))

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2  PCLK2 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_USART1SEL))

/** @brief  Macro to configure the USART2 clock (USART2CLK).
  *
  * @param  __USART2_CLKSOURCE__ specifies the USART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  * @retval None
  */
#define __HAL_RCC_USART2_CONFIG(__USART2_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART2SEL, (__USART2_CLKSOURCE__))

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_USART2SEL))

/** @brief  Macro to configure the USART3 clock (USART3CLK).
  *
  * @param  __USART3_CLKSOURCE__ specifies the USART3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART3CLKSOURCE_PCLK1  PCLK1 selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_HSI  HSI selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_SYSCLK  System Clock selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_LSE  LSE selected as USART3 clock
  * @retval None
  */
#define __HAL_RCC_USART3_CONFIG(__USART3_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_USART3SEL, (__USART3_CLKSOURCE__))

/** @brief  Macro to get the USART3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART3CLKSOURCE_PCLK1  PCLK1 selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_HSI  HSI selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_SYSCLK  System Clock selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_LSE  LSE selected as USART3 clock
  */
#define __HAL_RCC_GET_USART3_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_USART3SEL))

#if defined(UART4)
/** @brief  Macro to configure the UART4 clock (UART4CLK).
  *
  * @param  __UART4_CLKSOURCE__ specifies the UART4 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_UART4CLKSOURCE_PCLK1  PCLK1 selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_HSI  HSI selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_SYSCLK  System Clock selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_LSE  LSE selected as UART4 clock
  * @retval None
  */
#define __HAL_RCC_UART4_CONFIG(__UART4_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_UART4SEL, (__UART4_CLKSOURCE__))

/** @brief  Macro to get the UART4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_UART4CLKSOURCE_PCLK1  PCLK1 selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_HSI  HSI selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_SYSCLK  System Clock selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_LSE  LSE selected as UART4 clock
  */
#define __HAL_RCC_GET_UART4_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_UART4SEL))
#endif /* UART4 */

#if defined(UART5)

/** @brief  Macro to configure the UART5 clock (UART5CLK).
  *
  * @param  __UART5_CLKSOURCE__ specifies the UART5 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_UART5CLKSOURCE_PCLK1  PCLK1 selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_HSI  HSI selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_SYSCLK  System Clock selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_LSE  LSE selected as UART5 clock
  * @retval None
  */
#define __HAL_RCC_UART5_CONFIG(__UART5_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_UART5SEL, (__UART5_CLKSOURCE__))

/** @brief  Macro to get the UART5 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_UART5CLKSOURCE_PCLK1  PCLK1 selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_HSI  HSI selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_SYSCLK  System Clock selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_LSE  LSE selected as UART5 clock
  */
#define __HAL_RCC_GET_UART5_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_UART5SEL))

#endif /* UART5 */

/** @brief  Macro to configure the LPUART1 clock (LPUART1CLK).
  *
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK1  PCLK1 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  * @retval None
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPUART1SEL, (__LPUART1_CLKSOURCE__))

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK1  PCLK1 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_LPUART1SEL))

/** @brief  Macro to configure the I2C1 clock (I2C1CLK).
  *
  * @param  __I2C1_CLKSOURCE__ specifies the I2C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  * @retval None
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C1SEL, (__I2C1_CLKSOURCE__))

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_I2C1SEL))


/** @brief  Macro to configure the I2C2 clock (I2C2CLK).
  *
  * @param  __I2C2_CLKSOURCE__ specifies the I2C2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_PCLK1  PCLK1 selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_HSI  HSI selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_SYSCLK  System Clock selected as I2C2 clock
  * @retval None
  */
#define __HAL_RCC_I2C2_CONFIG(__I2C2_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C2SEL, (__I2C2_CLKSOURCE__))

/** @brief  Macro to get the I2C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_PCLK1  PCLK1 selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_HSI  HSI selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_SYSCLK  System Clock selected as I2C2 clock
  */
#define __HAL_RCC_GET_I2C2_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_I2C2SEL))

/** @brief  Macro to configure the I2C3 clock (I2C3CLK).
  *
  * @param  __I2C3_CLKSOURCE__ specifies the I2C3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK1  PCLK1 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI  HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK  System Clock selected as I2C3 clock
  * @retval None
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2C3SEL, (__I2C3_CLKSOURCE__))

/** @brief  Macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK1  PCLK1 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI  HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK  System Clock selected as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_I2C3SEL))

#if defined(I2C4)

/** @brief  Macro to configure the I2C4 clock (I2C4CLK).
  *
  * @param  __I2C4_CLKSOURCE__ specifies the I2C4 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C4CLKSOURCE_PCLK1  PCLK1 selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_HSI  HSI selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_SYSCLK  System Clock selected as I2C4 clock
  * @retval None
  */
#define __HAL_RCC_I2C4_CONFIG(__I2C4_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2C4SEL, (__I2C4_CLKSOURCE__))

/** @brief  Macro to get the I2C4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C4CLKSOURCE_PCLK1  PCLK1 selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_HSI  HSI selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_SYSCLK  System Clock selected as I2C4 clock
  */
#define __HAL_RCC_GET_I2C4_SOURCE() (READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2C4SEL))

#endif /* I2C4 */

/** @brief  Macro to configure the LPTIM1 clock (LPTIM1CLK).
  *
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK1  PCLK1 selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPTIM1SEL, (__LPTIM1_CLKSOURCE__))

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_PCLK1  PCLK1 selected as LPUART1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_LPTIM1SEL))

/**
  * @brief  Macro to configure the SAI1 clock source.
  * @param  __SAI1_CLKSOURCE__ defines the SAI1 clock source. This clock is derived
  *         from the HSI, system PLL, System Clock or external clock.
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_SAI1CLKSOURCE_SYSCLK SAI1 clock = System Clock
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL    SAI1 clock = PLL "Q" clock
  *             @arg @ref RCC_SAI1CLKSOURCE_EXT    SAI1 clock = EXT
  *             @arg @ref RCC_SAI1CLKSOURCE_HSI    SAI1 clock = HSI
  *
  * @retval None
  */
#define __HAL_RCC_SAI1_CONFIG(__SAI1_CLKSOURCE__)\
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_SAI1SEL, (__SAI1_CLKSOURCE__))

/** @brief  Macro to get the SAI1 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg @ref RCC_SAI1CLKSOURCE_SYSCLK SAI1 clock = System Clock
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL    SAI1 clock = PLL "Q" clock
  *             @arg @ref RCC_SAI1CLKSOURCE_EXT    SAI1 clock = EXT
  *             @arg @ref RCC_SAI1CLKSOURCE_HSI    SAI1 clock = HSI
  *
  */
#define __HAL_RCC_GET_SAI1_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_SAI1SEL))

/**
  * @brief  Macro to configure the I2S clock source.
  * @param  __I2S_CLKSOURCE__ defines the I2S clock source. This clock is derived
  *         from the HSI, system PLL, System Clock or external clock.
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_I2SCLKSOURCE_SYSCLK I2S clock = System Clock
  *             @arg @ref RCC_I2SCLKSOURCE_PLL    I2S clock = PLL "Q" clock
  *             @arg @ref RCC_I2SCLKSOURCE_EXT    I2S clock = EXT
  *             @arg @ref RCC_I2SCLKSOURCE_HSI    I2S clock = HSI
  *
  * @retval None
  */
#define __HAL_RCC_I2S_CONFIG(__I2S_CLKSOURCE__)\
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2S23SEL, (__I2S_CLKSOURCE__))

/** @brief  Macro to get the I2S clock source.
  * @retval The clock source can be one of the following values:
  *             @arg @ref RCC_I2SCLKSOURCE_SYSCLK I2S clock = System Clock
  *             @arg @ref RCC_I2SCLKSOURCE_PLL    I2S clock = PLL "Q" clock
  *             @arg @ref RCC_I2SCLKSOURCE_EXT    I2S clock = EXT
  *             @arg @ref RCC_I2SCLKSOURCE_HSI    I2S clock = HSI
  *
  */
#define __HAL_RCC_GET_I2S_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_I2S23SEL)))

#if defined(FDCAN1)
/**
  * @brief  Macro to configure the FDCAN clock source.
  * @param  __FDCAN_CLKSOURCE__ defines the FDCAN clock source. This clock is derived
  *         from the HSE, system PLL or PCLK1.
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_FDCANCLKSOURCE_HSE   FDCAN clock = HSE
  *             @arg @ref RCC_FDCANCLKSOURCE_PLL   FDCAN clock = PLL "Q" clock
  *             @arg @ref RCC_FDCANCLKSOURCE_PCLK1 FDCAN clock = PCLK1
  *
  * @retval None
  */
#define __HAL_RCC_FDCAN_CONFIG(__FDCAN_CLKSOURCE__)\
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_FDCANSEL, (uint32_t)(__FDCAN_CLKSOURCE__))

/** @brief  Macro to get the FDCAN clock source.
  * @retval The clock source can be one of the following values:
  *             @arg @ref RCC_FDCANCLKSOURCE_HSE   FDCAN clock = HSE
  *             @arg @ref RCC_FDCANCLKSOURCE_PLL   FDCAN clock = PLL "Q" clock
  *             @arg @ref RCC_FDCANCLKSOURCE_PCLK1 FDCAN clock = PCLK1
  *
  */
#define __HAL_RCC_GET_FDCAN_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR, RCC_CCIPR_FDCANSEL)))
#endif /* FDCAN1 */

/** @brief  Macro to configure the RNG clock.
  *
  * @note  USB and RNG peripherals share the same 48MHz clock source.
  *
  * @param  __RNG_CLKSOURCE__ specifies the RNG clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RNGCLKSOURCE_HSI48  HSI48 selected as RNG clock for devices with HSI48
  *            @arg @ref RCC_RNGCLKSOURCE_PLL  PLL Clock selected as RNG clock
  * @retval None
  */
#define __HAL_RCC_RNG_CONFIG(__RNG_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_CLK48SEL, (__RNG_CLKSOURCE__))

/** @brief  Macro to get the RNG clock.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_RNGCLKSOURCE_HSI48  HSI48 selected as RNG clock for devices with HSI48
  *            @arg @ref RCC_RNGCLKSOURCE_PLL  PLL "Q" clock selected as RNG clock
  */
#define __HAL_RCC_GET_RNG_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_CLK48SEL))

#if defined(USB)

/** @brief  Macro to configure the USB clock (USBCLK).
  *
  * @note  USB, RNG peripherals share the same 48MHz clock source.
  *
  * @param  __USB_CLKSOURCE__ specifies the USB clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_USBCLKSOURCE_HSI48  HSI48 selected as 48MHz clock for devices with HSI48
  *            @arg @ref RCC_USBCLKSOURCE_PLL  PLL "Q" clock (PLL48M1CLK) selected as USB clock
  * @retval None
  */
#define __HAL_RCC_USB_CONFIG(__USB_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_CLK48SEL, (__USB_CLKSOURCE__))

/** @brief  Macro to get the USB clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USBCLKSOURCE_HSI48  HSI48 selected as 48MHz clock for devices with HSI48
  *            @arg @ref RCC_USBCLKSOURCE_PLL  PLL "Q" clock (PLL48M1CLK) selected as USB clock
  */
#define __HAL_RCC_GET_USB_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_CLK48SEL))

#endif /* USB */

/** @brief  Macro to configure the ADC12 interface clock.
  * @param  __ADC12_CLKSOURCE__ specifies the ADC12 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADC12CLKSOURCE_NONE    No clock selected as ADC12 clock
  *            @arg @ref RCC_ADC12CLKSOURCE_PLL     PLL Clock selected as ADC12 clock
  *            @arg @ref RCC_ADC12CLKSOURCE_SYSCLK  System Clock selected as ADC12 clock
  * @retval None
  */
#define __HAL_RCC_ADC12_CONFIG(__ADC12_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADC12SEL, (__ADC12_CLKSOURCE__))

/** @brief  Macro to get the ADC12 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADC12CLKSOURCE_NONE    No clock selected as ADC12 clock
  *            @arg @ref RCC_ADC12CLKSOURCE_PLL     PLL Clock selected as ADC12 clock
  *            @arg @ref RCC_ADC12CLKSOURCE_SYSCLK  System Clock selected as ADC12 clock
  */
#define __HAL_RCC_GET_ADC12_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_ADC12SEL))

#if defined(ADC345_COMMON)
/** @brief  Macro to configure the ADC345 interface clock.
  * @param  __ADC345_CLKSOURCE__ specifies the ADC345 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADC345CLKSOURCE_NONE    No clock selected as ADC345 clock
  *            @arg @ref RCC_ADC345CLKSOURCE_PLL     PLL Clock selected as ADC345 clock
  *            @arg @ref RCC_ADC345CLKSOURCE_SYSCLK  System Clock selected as ADC345 clock
  * @retval None
  */
#define __HAL_RCC_ADC345_CONFIG(__ADC345_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADC345SEL, __ADC345_CLKSOURCE__)

/** @brief  Macro to get the ADC345 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADC345CLKSOURCE_NONE    No clock selected as ADC345 clock
  *            @arg @ref RCC_ADC345CLKSOURCE_PLL     PLL Clock selected as ADC345 clock
  *            @arg @ref RCC_ADC345CLKSOURCE_SYSCLK  System Clock selected as ADC345 clock
  */
#define __HAL_RCC_GET_ADC345_SOURCE() (READ_BIT(RCC->CCIPR, RCC_CCIPR_ADC345SEL))
#endif /* ADC345_COMMON */

#if defined(QUADSPI)

/** @brief  Macro to configure the QuadSPI clock.
  * @param  __QSPI_CLKSOURCE__ specifies the QuadSPI clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_QSPICLKSOURCE_SYSCLK  System Clock selected as QuadSPI clock
  *            @arg @ref RCC_QSPICLKSOURCE_HSI     HSI clock selected as QuadSPI clock
  *            @arg @ref RCC_QSPICLKSOURCE_PLL     PLL Q divider clock selected as QuadSPI clock
  * @retval None
  */
#define __HAL_RCC_QSPI_CONFIG(__QSPI_CLKSOURCE__) \
                  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_QSPISEL, __QSPI_CLKSOURCE__)

/** @brief  Macro to get the QuadSPI clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_QSPICLKSOURCE_SYSCLK  System Clock selected as QuadSPI clock
  *            @arg @ref RCC_QSPICLKSOURCE_HSI     HSI clock selected as QuadSPI clock
  *            @arg @ref RCC_QSPICLKSOURCE_PLL     PLL Q divider clock selected as QuadSPI clock
  */
#define __HAL_RCC_GET_QSPI_SOURCE() (READ_BIT(RCC->CCIPR2, RCC_CCIPR2_QSPISEL))

#endif /* QUADSPI */

/** @defgroup RCCEx_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/**
  * @brief Enable the RCC LSE CSS Extended Interrupt Line.
  * @retval None
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_IT()      SET_BIT(EXTI->IMR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Disable the RCC LSE CSS Extended Interrupt Line.
  * @retval None
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_IT()     CLEAR_BIT(EXTI->IMR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Enable the RCC LSE CSS Event Line.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Disable the RCC LSE CSS Event Line.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR1, RCC_EXTI_LINE_LSECSS)


/**
  * @brief  Enable the RCC LSE CSS Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI->FTSR1, RCC_EXTI_LINE_LSECSS)


/**
  * @brief Disable the RCC LSE CSS Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR1, RCC_EXTI_LINE_LSECSS)


/**
  * @brief  Enable the RCC LSE CSS Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Disable the RCC LSE CSS Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Enable the RCC LSE CSS Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                      \
    __HAL_RCC_LSECSS_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_RCC_LSECSS_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the RCC LSE CSS Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                       \
    __HAL_RCC_LSECSS_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_RCC_LSECSS_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Check whether the specified RCC LSE CSS EXTI interrupt flag is set or not.
  * @retval EXTI RCC LSE CSS Line Status.
  */
#define __HAL_RCC_LSECSS_EXTI_GET_FLAG()       (READ_BIT(EXTI->PR1, RCC_EXTI_LINE_LSECSS) == RCC_EXTI_LINE_LSECSS)

/**
  * @brief Clear the RCC LSE CSS EXTI flag.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_CLEAR_FLAG()     WRITE_REG(EXTI->PR1, RCC_EXTI_LINE_LSECSS)

/**
  * @brief Generate a Software interrupt on the RCC LSE CSS EXTI line.
  * @retval None.
  */
#define __HAL_RCC_LSECSS_EXTI_GENERATE_SWIT()  SET_BIT(EXTI->SWIER1, RCC_EXTI_LINE_LSECSS)


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


/**
  * @}
  */

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
  * @brief  Enable the automatic hardware adjustement of TRIM bits.
  * @note   When the AUTOTRIMEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_AUTOMATIC_CALIB_ENABLE()     SET_BIT(CRS->CR, CRS_CR_AUTOTRIMEN)

/**
  * @brief  Enable or disable the automatic hardware adjustement of TRIM bits.
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

void              HAL_RCCEx_EnableLSECSS(void);
void              HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_EnableLSECSS_IT(void);
void              HAL_RCCEx_LSECSS_IRQHandler(void);
void              HAL_RCCEx_LSECSS_Callback(void);
void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);

/**
  * @}
  */

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

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Macros
  * @{
  */

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))

#if defined(STM32G474xx) || defined(STM32G484xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)      == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)      == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART3)      == RCC_PERIPHCLK_USART3)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_UART4)       == RCC_PERIPHCLK_UART4)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_UART5)       == RCC_PERIPHCLK_UART5)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1)     == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)        == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C2)        == RCC_PERIPHCLK_I2C2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C3)        == RCC_PERIPHCLK_I2C3)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C4)        == RCC_PERIPHCLK_I2C4)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)      == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_SAI1)        == RCC_PERIPHCLK_SAI1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S)         == RCC_PERIPHCLK_I2S)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_FDCAN)       == RCC_PERIPHCLK_FDCAN)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_USB)         == RCC_PERIPHCLK_USB)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)         == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC12)       == RCC_PERIPHCLK_ADC12)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC345)      == RCC_PERIPHCLK_ADC345)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_QSPI)        == RCC_PERIPHCLK_QSPI)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)         == RCC_PERIPHCLK_RTC))

#elif defined(STM32G473xx) || defined(STM32G483xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)      == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)      == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART3)      == RCC_PERIPHCLK_USART3)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_UART4)       == RCC_PERIPHCLK_UART4)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_UART5)       == RCC_PERIPHCLK_UART5)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1)     == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)        == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C2)        == RCC_PERIPHCLK_I2C2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C3)        == RCC_PERIPHCLK_I2C3)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C4)        == RCC_PERIPHCLK_I2C4)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)      == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_SAI1)        == RCC_PERIPHCLK_SAI1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S)         == RCC_PERIPHCLK_I2S)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_FDCAN)       == RCC_PERIPHCLK_FDCAN)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_USB)         == RCC_PERIPHCLK_USB)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)         == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC12)       == RCC_PERIPHCLK_ADC12)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC345)      == RCC_PERIPHCLK_ADC345)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_QSPI)        == RCC_PERIPHCLK_QSPI)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)         == RCC_PERIPHCLK_RTC))

#elif defined(STM32G471xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)      == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)      == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART3)      == RCC_PERIPHCLK_USART3)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_UART4)       == RCC_PERIPHCLK_UART4)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_UART5)       == RCC_PERIPHCLK_UART5)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1)     == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)        == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C2)        == RCC_PERIPHCLK_I2C2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C3)        == RCC_PERIPHCLK_I2C3)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C4)        == RCC_PERIPHCLK_I2C4)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)      == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_SAI1)        == RCC_PERIPHCLK_SAI1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S)         == RCC_PERIPHCLK_I2S)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_USB)         == RCC_PERIPHCLK_USB)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)         == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC12)       == RCC_PERIPHCLK_ADC12)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)         == RCC_PERIPHCLK_RTC))

#elif defined(STM32G431xx) || defined(STM32G441xx)

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)      == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)      == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART3)      == RCC_PERIPHCLK_USART3)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_UART4)       == RCC_PERIPHCLK_UART4)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1)     == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)        == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C2)        == RCC_PERIPHCLK_I2C2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C3)        == RCC_PERIPHCLK_I2C3)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)      == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_SAI1)        == RCC_PERIPHCLK_SAI1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S)         == RCC_PERIPHCLK_I2S)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_FDCAN)       == RCC_PERIPHCLK_FDCAN)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_USB)         == RCC_PERIPHCLK_USB)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)         == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC12)       == RCC_PERIPHCLK_ADC12)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)         == RCC_PERIPHCLK_RTC))

#elif defined(STM32GBK1CB)
#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
               ((((__SELECTION__) & RCC_PERIPHCLK_USART1)      == RCC_PERIPHCLK_USART1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART2)      == RCC_PERIPHCLK_USART2)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_USART3)      == RCC_PERIPHCLK_USART3)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPUART1)     == RCC_PERIPHCLK_LPUART1) || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C1)        == RCC_PERIPHCLK_I2C1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C2)        == RCC_PERIPHCLK_I2C2)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2C3)        == RCC_PERIPHCLK_I2C3)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)      == RCC_PERIPHCLK_LPTIM1)  || \
                (((__SELECTION__) & RCC_PERIPHCLK_SAI1)        == RCC_PERIPHCLK_SAI1)    || \
                (((__SELECTION__) & RCC_PERIPHCLK_I2S)         == RCC_PERIPHCLK_I2S)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_FDCAN)       == RCC_PERIPHCLK_FDCAN)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_USB)         == RCC_PERIPHCLK_USB)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_RNG)         == RCC_PERIPHCLK_RNG)     || \
                (((__SELECTION__) & RCC_PERIPHCLK_ADC12)       == RCC_PERIPHCLK_ADC12)   || \
                (((__SELECTION__) & RCC_PERIPHCLK_RTC)         == RCC_PERIPHCLK_RTC))

#endif /* STM32G474xx || STM32G484xx */

#define IS_RCC_USART1CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK2)  || \
                ((__SOURCE__) == RCC_USART1CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_USART1CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_USART1CLKSOURCE_HSI))

#define IS_RCC_USART2CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USART2CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_USART2CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_USART2CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_USART2CLKSOURCE_HSI))

#define IS_RCC_USART3CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USART3CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_USART3CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_USART3CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_USART3CLKSOURCE_HSI))

#if defined(UART4)
#define IS_RCC_UART4CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_UART4CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_UART4CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_UART4CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_UART4CLKSOURCE_HSI))
#endif /* UART4 */

#if defined(UART5)
#define IS_RCC_UART5CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_UART5CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_UART5CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_UART5CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_UART5CLKSOURCE_HSI))

#endif /* UART5 */

#define IS_RCC_LPUART1CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_LPUART1CLKSOURCE_PCLK1)  || \
                ((__SOURCE__) == RCC_LPUART1CLKSOURCE_SYSCLK) || \
                ((__SOURCE__) == RCC_LPUART1CLKSOURCE_LSE)    || \
                ((__SOURCE__) == RCC_LPUART1CLKSOURCE_HSI))

#define IS_RCC_I2C1CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2C1CLKSOURCE_PCLK1) || \
                ((__SOURCE__) == RCC_I2C1CLKSOURCE_SYSCLK)|| \
                ((__SOURCE__) == RCC_I2C1CLKSOURCE_HSI))

#define IS_RCC_I2C2CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2C2CLKSOURCE_PCLK1) || \
                ((__SOURCE__) == RCC_I2C2CLKSOURCE_SYSCLK)|| \
                ((__SOURCE__) == RCC_I2C2CLKSOURCE_HSI))

#define IS_RCC_I2C3CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2C3CLKSOURCE_PCLK1) || \
                ((__SOURCE__) == RCC_I2C3CLKSOURCE_SYSCLK)|| \
                ((__SOURCE__) == RCC_I2C3CLKSOURCE_HSI))

#if defined(I2C4)

#define IS_RCC_I2C4CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2C4CLKSOURCE_PCLK1) || \
                ((__SOURCE__) == RCC_I2C4CLKSOURCE_SYSCLK)|| \
                ((__SOURCE__) == RCC_I2C4CLKSOURCE_HSI))

#endif /* I2C4 */

#define IS_RCC_LPTIM1CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_LPTIM1CLKSOURCE_PCLK1) || \
                ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSI)   || \
                ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_HSI)   || \
                ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSE))

#define IS_RCC_SAI1CLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_SAI1CLKSOURCE_SYSCLK)  || \
                ((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL)     || \
                ((__SOURCE__) == RCC_SAI1CLKSOURCE_EXT)     || \
                ((__SOURCE__) == RCC_SAI1CLKSOURCE_HSI))

#define IS_RCC_I2SCLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_I2SCLKSOURCE_SYSCLK)  || \
                ((__SOURCE__) == RCC_I2SCLKSOURCE_PLL)     || \
                ((__SOURCE__) == RCC_I2SCLKSOURCE_EXT)     || \
                ((__SOURCE__) == RCC_I2SCLKSOURCE_HSI))

#if defined(FDCAN1)
#define IS_RCC_FDCANCLKSOURCE(__SOURCE__)   \
               (((__SOURCE__) == RCC_FDCANCLKSOURCE_HSE) || \
                ((__SOURCE__) == RCC_FDCANCLKSOURCE_PLL) || \
                ((__SOURCE__) == RCC_FDCANCLKSOURCE_PCLK1))

#endif /* FDCAN1 */
#define IS_RCC_RNGCLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_RNGCLKSOURCE_HSI48)   || \
                ((__SOURCE__) == RCC_RNGCLKSOURCE_PLL))

#if defined(USB)
#define IS_RCC_USBCLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_USBCLKSOURCE_HSI48)   || \
                ((__SOURCE__) == RCC_USBCLKSOURCE_PLL))

#endif /* USB */

#define IS_RCC_ADC12CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_ADC12CLKSOURCE_NONE)    || \
                ((__SOURCE__) == RCC_ADC12CLKSOURCE_PLL)     || \
                ((__SOURCE__) == RCC_ADC12CLKSOURCE_SYSCLK))

#if defined(ADC345_COMMON)
#define IS_RCC_ADC345CLKSOURCE(__SOURCE__)  \
               (((__SOURCE__) == RCC_ADC345CLKSOURCE_NONE)    || \
                ((__SOURCE__) == RCC_ADC345CLKSOURCE_PLL)     || \
                ((__SOURCE__) == RCC_ADC345CLKSOURCE_SYSCLK))
#endif /* ADC345_COMMON */

#if defined(QUADSPI)

#define IS_RCC_QSPICLKSOURCE(__SOURCE__)  \
                (((__SOURCE__) == RCC_QSPICLKSOURCE_HSI)   || \
                 ((__SOURCE__) == RCC_QSPICLKSOURCE_SYSCLK)|| \
                 ((__SOURCE__) == RCC_QSPICLKSOURCE_PLL))

#endif /* QUADSPI */

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

#define IS_RCC_CRS_HSI48CALIBRATION(__VALUE__) (((__VALUE__) <= 0x3FU))

#define IS_RCC_CRS_FREQERRORDIR(__DIR__)   (((__DIR__) == RCC_CRS_FREQERRORDIR_UP) || \
                                            ((__DIR__) == RCC_CRS_FREQERRORDIR_DOWN))

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

#endif /* STM32G4xx_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
