/**
  ******************************************************************************
  * @file    stm32u5xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended  module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_RCC_EX_H
#define STM32U5xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
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
  * @brief  PLL2 Clock structure definition
  */
typedef struct
{
  uint32_t PLL2Source;  /*!< RCC_PLL2Source: PLL2 entry clock source.
                            This parameter must be a value of @ref RCC_PLL_Clock_Source               */

  uint32_t PLL2M;       /*!< PLL2M: Division factor for PLL2 VCO input clock.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 63    */

  uint32_t PLL2N;       /*!< PLL2N: Multiplication factor for PLL2 VCO output clock.
                             This parameter must be a number between Min_Data = 4 and Max_Data = 512   */

  uint32_t PLL2P;       /*!< PLL2P: Division factor for system clock.
                             This parameter must be a number between Min_Data = 2 and Max_Data = 128   */

  uint32_t PLL2Q;        /*!< PLL2Q: Division factor for peripheral clocks.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 128   */

  uint32_t PLL2R;        /*!< PLL2R: Division factor for peripheral clocks.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 128
                             odd division factors are not allowed                                      */

  uint32_t PLL2RGE;      /*!<PLL2RGE: PLL2 clock Input range
                          This parameter must be a value of @ref RCC_PLL_VCI_Range                    */

  uint32_t PLL2FRACN;    /*!<PLL2FRACN: Specifies Fractional Part Of The Multiplication Factor for
                            PLL2 VCO It should be a value between 0 and 8191                           */

  uint32_t PLL2ClockOut; /*!< PLL2ClockOut: specifies PLL2 output clock to be enabled.
                                  This parameter must be a value of @ref RCC_PLL2_Clock_Output */
} RCC_PLL2InitTypeDef;


/**
  * @brief  PLL3 Clock structure definition
  */
typedef struct
{
  uint32_t PLL3Source;  /*!< RCC_PLL3Source: PLL3 entry clock source.
                            This parameter must be a value of @ref RCC_PLL_Clock_Source               */

  uint32_t PLL3M;       /*!< PLL3M: Division factor for PLL3 VCO input clock.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 63    */

  uint32_t PLL3N;       /*!< PLL3N: Multiplication factor for PLL3 VCO output clock.
                             This parameter must be a number between Min_Data = 4 and Max_Data = 512   */

  uint32_t PLL3P;       /*!< PLL3P: Division factor for system clock.
                             This parameter must be a number between Min_Data = 2 and Max_Data = 128   */

  uint32_t PLL3Q;        /*!< PLL3Q: Division factor for peripheral clocks.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 128   */

  uint32_t PLL3R;        /*!< PLL3R: Division factor for peripheral clocks.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 128
                             odd division factors are not allowed                                      */

  uint32_t PLL3RGE;      /*!<PLL3RGE: PLL3 clock Input range
                          This parameter must be a value of @ref RCC_PLL_VCI_Range                    */

  uint32_t PLL3FRACN;    /*!<PLL3FRACN: Specifies Fractional Part Of The Multiplication Factor for
                            PLL3 VCO It should be a value between 0 and 8191                           */

  uint32_t PLL3ClockOut; /*!< PLL3ClockOut: specifies PLL3 output clock to be enabled.
                                  This parameter must be a value of @ref RCC_PLL3_Clock_Output */
} RCC_PLL3InitTypeDef;

/**
  * @brief  RCC PLL1 Clocks structure definition
  */
typedef struct
{
  uint32_t PLL1_P_Frequency;
  uint32_t PLL1_Q_Frequency;
  uint32_t PLL1_R_Frequency;
} PLL1_ClocksTypeDef;

/**
  * @brief  RCC PLL2 Clocks structure definition
  */
typedef struct
{
  uint32_t PLL2_P_Frequency;
  uint32_t PLL2_Q_Frequency;
  uint32_t PLL2_R_Frequency;
} PLL2_ClocksTypeDef;

/**
  * @brief  RCC PLL3 Clocks structure definition
  */
typedef struct
{
  uint32_t PLL3_P_Frequency;
  uint32_t PLL3_Q_Frequency;
  uint32_t PLL3_R_Frequency;
} PLL3_ClocksTypeDef;


/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t PeriphClockSelection;   /*!< The Extended Clock to be configured.
                                        This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  RCC_PLL2InitTypeDef PLL2;        /*!< PLL2structure parameters.
                                        This parameter will be used only when PLL2 is selected as kernel clock Source
                                        for some peripherals */

  RCC_PLL3InitTypeDef PLL3;        /*!< PLL3 structure parameters.
                                        This parameter will be used only when PLL2 is selected as kernel clock Source
                                        for some peripherals */

  uint32_t Usart1ClockSelection;   /*!< Specifies USART1 clock source.
                                        This parameter can be a value of @ref RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection;   /*!< Specifies USART2 clock source.
                                        This parameter can be a value of @ref RCCEx_USART2_Clock_Source */

  uint32_t Usart3ClockSelection;   /*!< Specifies USART3 clock source.
                                        This parameter can be a value of @ref RCCEx_USART3_Clock_Source */

  uint32_t Uart4ClockSelection;    /*!< Specifies UART4 clock source.
                                        This parameter can be a value of @ref RCCEx_UART4_Clock_Source */

  uint32_t Uart5ClockSelection;    /*!< Specifies UART5 clock source.
                                        This parameter can be a value of @ref RCCEx_UART5_Clock_Source */

  uint32_t Lpuart1ClockSelection;  /*!< Specifies LPUART1 clock source.
                                        This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */

  uint32_t I2c1ClockSelection;     /*!< Specifies I2C1 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C1_Clock_Source */

  uint32_t I2c2ClockSelection;     /*!< Specifies I2C2 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C2_Clock_Source */

  uint32_t I2c3ClockSelection;     /*!< Specifies I2C3 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C3_Clock_Source */

  uint32_t I2c4ClockSelection;     /*!< Specifies I2C4 clock source.
                                        This parameter can be a value of @ref RCCEx_I2C4_Clock_Source */

  uint32_t Lptim1ClockSelection;   /*!< Specifies LPTIM1 clock source.
                                         This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source */

  uint32_t Lptim2ClockSelection;   /*!< Specifies LPTIM2 clock source.
                                          This parameter can be a value of @ref RCCEx_LPTIM2_Clock_Source */

  uint32_t Lptim34ClockSelection;  /*!< Specifies LPTIM3 and LPTIM4 clock source.
                                        This parameter can be a value of @ref RCCEx_LPTIM34_Clock_Source */

  uint32_t Fdcan1ClockSelection;   /*!< Specifies FDCAN1 kernel clock source.
                                        This parameter can be a value of @ref RCCEx_FDCAN1_Clock_Source */

  uint32_t Mdf1ClockSelection;     /*!< Specifies MDF1 kernel clock source.
                                        This parameter can be a value of @ref RCCEx_MDF1_Clock_Source */

  uint32_t Adf1ClockSelection;     /*!< Specifies Adf1 kernel clock source.
                                        This parameter can be a value of @ref RCCEx_ADF1_Clock_Source */

  uint32_t Sai1ClockSelection;     /*!< Specifies SAI1 clock source.
                                        This parameter can be a value of @ref RCCEx_SAI1_Clock_Source */

  uint32_t Sai2ClockSelection;     /*!< Specifies SAI2 clock source.
                                        This parameter can be a value of @ref RCCEx_SAI2_Clock_Source */

  uint32_t RngClockSelection;      /*!< Specifies RNG clock source
                                        This parameter can be a value of @ref RCCEx_RNG_Clock_Source  */

  uint32_t SaesClockSelection;     /*!< Specifies SAES clock source
                                        This parameter can be a value of @ref RCCEx_SAES_Clock_Source  */

  uint32_t Clk48ClockSelection;    /*!< Specifies 48Mhz clock source used by USB, RNG and SDMMC1
                                        This parameter can be a value of @ref RCCEx_CLK48_Clock_Source */

  uint32_t SdmmcClockSelection;    /*!< Specifies SDMMC1/2 clock source.
                                        This parameter can be a value of @ref RCCEx_SDMMC_Clock_Source */

  uint32_t AdcDacClockSelection;   /*!< Specifies ADC1, ADC4 and DAC interface clock source.
                                        This parameter can be a value of @ref RCCEx_ADCDAC_Clock_Source */

  uint32_t Dac1ClockSelection;     /*!< Specifies DAC1 interface clock source.
                                        This parameter can be a value of @ref RCCEx_DAC1_Clock_Source */

  uint32_t OspiClockSelection;     /*!< Specifies OctoSPI clock source.
                                        This parameter can be a value of @ref RCCEx_OSPI_Clock_Source */

  uint32_t Spi1ClockSelection;     /*!< Specifies SPI1 clock source
                                        This parameter can be a value of @ref RCCEx_SPI1_Clock_Source    */

  uint32_t Spi2ClockSelection;     /*!< Specifies SPI2 clock source
                                        This parameter can be a value of @ref RCCEx_SPI2_Clock_Source    */

  uint32_t Spi3ClockSelection;     /*!< Specifies SPI3 clock source
                                        This parameter can be a value of @ref RCCEx_SPI3_Clock_Source    */

  uint32_t RTCClockSelection;      /*!< Specifies RTC clock source.
                                        This parameter can be a value of @ref RCC_RTC_Clock_Source */
} RCC_PeriphCLKInitTypeDef;

#if defined(CRS)

/**
  * @brief RCC_CRS Init structure definition
  */
typedef struct
{
  uint32_t Prescaler;             /*!< Specifies the division factor of the SYNC signal.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroDivider  */

  uint32_t Source;                /*!< Specifies the SYNC signal source.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroSource   */

  uint32_t Polarity;              /*!< Specifies the input polarity for the SYNC signal source.
                                       This parameter can be a value of @ref RCCEx_CRS_SynchroPolarity */

  uint32_t ReloadValue;           /*!< Specifies the value to be loaded in the frequency error counter with each SYNC
                                       event. It can be calculated in using macro
                                        __HAL_RCC_CRS_RELOADVALUE_CALCULATE(__FTARGET__, __FSYNC__)
                                       This parameter must be a number between 0 and 0xFFFF or a value of
                                       @ref RCCEx_CRS_ReloadValueDefault .*/

  uint32_t ErrorLimitValue;       /*!< Specifies the value to be used to evaluate the captured frequency error value.
                                       This parameter must be a number between 0 and 0xFF or a value of
                                       @ref RCCEx_CRS_ErrorLimitDefault */

  uint32_t HSI48CalibrationValue; /*!< Specifies a user-programmable trimming value to the HSI48 oscillator.
                                       This parameter must be a number between 0 and 0x3F or a value of
                                       @ref RCCEx_CRS_HSI48CalibrationDefault */

} RCC_CRSInitTypeDef;

/**
  * @brief RCC_CRS Synchronization structure definition
  */
typedef struct
{
  uint32_t ReloadValue;           /*!< Specifies the value loaded in the Counter reload value.
                                     This parameter must be a number between 0 and 0xFFFF */

  uint32_t HSI48CalibrationValue; /*!< Specifies value loaded in HSI48 oscillator smooth trimming.
                                     This parameter must be a number between 0 and 0x3F */

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

/** @defgroup RCCEx_MSI_Pll_Mode_Selection MSI Pll Mode Selection
  * @{
  */
#define RCC_MSIKPLL_MODE_SEL             0x00000000U           /*!< PLL mode applied to MSIK (MSI kernel) clock output */
#define RCC_MSISPLL_MODE_SEL             RCC_CR_MSIPLLSEL      /*!< PLL mode applied to MSIS (MSI system) clock output */
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection  RCCEx Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_USART1           0x00000001U
#define RCC_PERIPHCLK_USART2           0x00000002U
#define RCC_PERIPHCLK_USART3           0x00000004U
#define RCC_PERIPHCLK_UART4            0x00000008U
#define RCC_PERIPHCLK_UART5            0x00000010U
#define RCC_PERIPHCLK_LPUART1          0x00000020U
#define RCC_PERIPHCLK_I2C1             0x00000040U
#define RCC_PERIPHCLK_I2C2             0x00000080U
#define RCC_PERIPHCLK_I2C3             0x00000100U
#define RCC_PERIPHCLK_LPTIM1           0x00000200U
#define RCC_PERIPHCLK_LPTIM2           0x00000400U
#define RCC_PERIPHCLK_LPTIM34          0x00000800U
#define RCC_PERIPHCLK_SAES             0x00001000U
#define RCC_PERIPHCLK_SAI1             0x00002000U
#define RCC_PERIPHCLK_SAI2             0x00004000U
#define RCC_PERIPHCLK_ADCDAC           0x00008000U
#define RCC_PERIPHCLK_MDF1             0x00010000U
#define RCC_PERIPHCLK_ADF1             0x00020000U
#define RCC_PERIPHCLK_RTC              0x00040000U
#define RCC_PERIPHCLK_RNG              0x00080000U
#define RCC_PERIPHCLK_CLK48            0x00100000U
#define RCC_PERIPHCLK_SDMMC            0x00200000U
#define RCC_PERIPHCLK_I2C4             0x00400000U
#define RCC_PERIPHCLK_SPI1             0x00800000U
#define RCC_PERIPHCLK_SPI2             0x01000000U
#define RCC_PERIPHCLK_SPI3             0x02000000U
#define RCC_PERIPHCLK_OSPI             0x04000000U
#define RCC_PERIPHCLK_FDCAN1           0x08000000U
#define RCC_PERIPHCLK_DAC1             0x10000000U

#define RCC_PERIPHCLOCK_ALL          (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 |RCC_PERIPHCLK_USART3 | \
                                      RCC_PERIPHCLK_UART4 | RCC_PERIPHCLK_UART5 | RCC_PERIPHCLK_LPUART1 | \
                                      RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_I2C3 | \
                                      RCC_PERIPHCLK_LPTIM1 | RCC_PERIPHCLK_LPTIM2 | RCC_PERIPHCLK_LPTIM34 | \
                                      RCC_PERIPHCLK_SAES | RCC_PERIPHCLK_SAI1 | RCC_PERIPHCLK_SAI2 | \
                                      RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_MDF1 | RCC_PERIPHCLK_ADF1 | \
                                      RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_RNG |RCC_PERIPHCLK_CLK48 | \
                                      RCC_PERIPHCLK_SDMMC | RCC_PERIPHCLK_I2C4 | RCC_PERIPHCLK_SPI1 | \
                                      RCC_PERIPHCLK_SPI2  | RCC_PERIPHCLK_SPI3 |RCC_PERIPHCLK_OSPI | \
                                      RCC_PERIPHCLK_FDCAN1 | RCC_PERIPHCLK_DAC1)
/**
  * @}
  */


/** @defgroup RCC_PLL2_Clock_Output  RCC PLL2 Clock Output
  * @{
  */
#define RCC_PLL2_DIVP                RCC_PLL2CFGR_PLL2PEN
#define RCC_PLL2_DIVQ                RCC_PLL2CFGR_PLL2QEN
#define RCC_PLL2_DIVR                RCC_PLL2CFGR_PLL2REN
/**
  * @}
  */

/** @defgroup RCC_PLL3_Clock_Output  RCC PLL3 Clock Output
  * @{
  */
#define RCC_PLL3_DIVP                RCC_PLL3CFGR_PLL3PEN
#define RCC_PLL3_DIVQ                RCC_PLL3CFGR_PLL3QEN
#define RCC_PLL3_DIVR                RCC_PLL3CFGR_PLL3REN
/**
  * @}
  */

/** @defgroup RCCEx_USART1_Clock_Source USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2      0x00000000U
#define RCC_USART1CLKSOURCE_SYSCLK     RCC_CCIPR1_USART1SEL_0
#define RCC_USART1CLKSOURCE_HSI        RCC_CCIPR1_USART1SEL_1
#define RCC_USART1CLKSOURCE_LSE        (RCC_CCIPR1_USART1SEL_0 | RCC_CCIPR1_USART1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_USART2_Clock_Source USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1      0x00000000U
#define RCC_USART2CLKSOURCE_SYSCLK     RCC_CCIPR1_USART2SEL_0
#define RCC_USART2CLKSOURCE_HSI        RCC_CCIPR1_USART2SEL_1
#define RCC_USART2CLKSOURCE_LSE        (RCC_CCIPR1_USART2SEL_0 | RCC_CCIPR1_USART2SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_USART3_Clock_Source USART3 Clock Source
  * @{
  */
#define RCC_USART3CLKSOURCE_PCLK1      0x00000000U
#define RCC_USART3CLKSOURCE_SYSCLK     RCC_CCIPR1_USART3SEL_0
#define RCC_USART3CLKSOURCE_HSI        RCC_CCIPR1_USART3SEL_1
#define RCC_USART3CLKSOURCE_LSE        (RCC_CCIPR1_USART3SEL_0 | RCC_CCIPR1_USART3SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_UART4_Clock_Source UART4 Clock Source
  * @{
  */
#define RCC_UART4CLKSOURCE_PCLK1       0x00000000U
#define RCC_UART4CLKSOURCE_SYSCLK      RCC_CCIPR1_UART4SEL_0
#define RCC_UART4CLKSOURCE_HSI         RCC_CCIPR1_UART4SEL_1
#define RCC_UART4CLKSOURCE_LSE         (RCC_CCIPR1_UART4SEL_0 | RCC_CCIPR1_UART4SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_UART5_Clock_Source UART5 Clock Source
  * @{
  */
#define RCC_UART5CLKSOURCE_PCLK1       0x00000000U
#define RCC_UART5CLKSOURCE_SYSCLK      RCC_CCIPR1_UART5SEL_0
#define RCC_UART5CLKSOURCE_HSI         RCC_CCIPR1_UART5SEL_1
#define RCC_UART5CLKSOURCE_LSE         (RCC_CCIPR1_UART5SEL_0 | RCC_CCIPR1_UART5SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_LPUART1_Clock_Source LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK3     0x00000000U
#define RCC_LPUART1CLKSOURCE_SYSCLK    RCC_CCIPR3_LPUART1SEL_0
#define RCC_LPUART1CLKSOURCE_HSI       RCC_CCIPR3_LPUART1SEL_1
#define RCC_LPUART1CLKSOURCE_LSE       (RCC_CCIPR3_LPUART1SEL_0 | RCC_CCIPR3_LPUART1SEL_1)
#define RCC_LPUART1CLKSOURCE_MSIK       RCC_CCIPR3_LPUART1SEL_2
/**
  * @}
  */

/** @defgroup RCCEx_I2C1_Clock_Source I2C1 Clock Source
  * @{
  */
#define RCC_I2C1CLKSOURCE_PCLK1        0x00000000U
#define RCC_I2C1CLKSOURCE_SYSCLK       RCC_CCIPR1_I2C1SEL_0
#define RCC_I2C1CLKSOURCE_HSI          RCC_CCIPR1_I2C1SEL_1
#define RCC_I2C1CLKSOURCE_MSIK         (RCC_CCIPR1_I2C1SEL_1 | RCC_CCIPR1_I2C1SEL_0)
/**
  * @}
  */

/** @defgroup RCCEx_I2C2_Clock_Source I2C2 Clock Source
  * @{
  */
#define RCC_I2C2CLKSOURCE_PCLK1        0x00000000U
#define RCC_I2C2CLKSOURCE_SYSCLK       RCC_CCIPR1_I2C2SEL_0
#define RCC_I2C2CLKSOURCE_HSI          RCC_CCIPR1_I2C2SEL_1
#define RCC_I2C2CLKSOURCE_MSIK         (RCC_CCIPR1_I2C2SEL_1 | RCC_CCIPR1_I2C2SEL_0)
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_PCLK3        0x00000000U
#define RCC_I2C3CLKSOURCE_SYSCLK       RCC_CCIPR3_I2C3SEL_0
#define RCC_I2C3CLKSOURCE_HSI          RCC_CCIPR3_I2C3SEL_1
#define RCC_I2C3CLKSOURCE_MSIK         (RCC_CCIPR3_I2C3SEL_0 | RCC_CCIPR3_I2C3SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_I2C4_Clock_Source I2C4 Clock Source
  * @{
  */
#define RCC_I2C4CLKSOURCE_PCLK1        0x00000000U
#define RCC_I2C4CLKSOURCE_SYSCLK       RCC_CCIPR1_I2C4SEL_0
#define RCC_I2C4CLKSOURCE_HSI          RCC_CCIPR1_I2C4SEL_1
#define RCC_I2C4CLKSOURCE_MSIK         (RCC_CCIPR1_I2C4SEL_1 | RCC_CCIPR1_I2C4SEL_0)
/**
  * @}
  */

/** @defgroup RCCEx_RNG_Clock_Source  RCCEx RNG Clock Source
  * @{
  */
#define RCC_RNGCLKSOURCE_HSI48         0x00000000U
#define RCC_RNGCLKSOURCE_HSI48_DIV2    RCC_CCIPR2_RNGSEL_0
#define RCC_RNGCLKSOURCE_HSI           RCC_CCIPR2_RNGSEL_1
/**
  * @}
  */

/** @defgroup RCCEx_SAES_Clock_Source  RCCEx SAES Clock Source
  * @{
  */
#define RCC_SAESCLKSOURCE_SHSI         0x00000000U
#define RCC_SAESCLKSOURCE_SHSI_DIV2    RCC_CCIPR2_SAESSEL
/**
  * @}
  */

/** @defgroup RCCEx_SPI1_Clock_Source SPI1 Clock Source
  * @{
  */
#define RCC_SPI1CLKSOURCE_PCLK2        0x00000000U
#define RCC_SPI1CLKSOURCE_SYSCLK       RCC_CCIPR1_SPI1SEL_0
#define RCC_SPI1CLKSOURCE_HSI          RCC_CCIPR1_SPI1SEL_1
#define RCC_SPI1CLKSOURCE_MSIK         (RCC_CCIPR1_SPI1SEL_0 | RCC_CCIPR1_SPI1SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_SPI2_Clock_Source SPI2 Clock Source
  * @{
  */
#define RCC_SPI2CLKSOURCE_PCLK1        0x00000000U
#define RCC_SPI2CLKSOURCE_SYSCLK       RCC_CCIPR1_SPI2SEL_0
#define RCC_SPI2CLKSOURCE_HSI          RCC_CCIPR1_SPI2SEL_1
#define RCC_SPI2CLKSOURCE_MSIK         (RCC_CCIPR1_SPI2SEL_0 | RCC_CCIPR1_SPI2SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_SPI3_Clock_Source SPI3 Clock Source
  * @{
  */
#define RCC_SPI3CLKSOURCE_PCLK3        0x00000000U
#define RCC_SPI3CLKSOURCE_SYSCLK       RCC_CCIPR3_SPI3SEL_0
#define RCC_SPI3CLKSOURCE_HSI          RCC_CCIPR3_SPI3SEL_1
#define RCC_SPI3CLKSOURCE_MSIK         (RCC_CCIPR3_SPI3SEL_0 | RCC_CCIPR3_SPI3SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM34_Clock_Source LPTIM34 Clock Source
  * @{
  */
#define RCC_LPTIM34CLKSOURCE_MSIK       0x00000000U
#define RCC_LPTIM34CLKSOURCE_LSI        RCC_CCIPR3_LPTIM34SEL_0
#define RCC_LPTIM34CLKSOURCE_HSI        RCC_CCIPR3_LPTIM34SEL_1
#define RCC_LPTIM34CLKSOURCE_LSE        (RCC_CCIPR3_LPTIM34SEL_0 | RCC_CCIPR3_LPTIM34SEL_1)
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_MSIK       0x00000000U
#define RCC_LPTIM1CLKSOURCE_LSI        RCC_CCIPR3_LPTIM1SEL_0
#define RCC_LPTIM1CLKSOURCE_HSI        RCC_CCIPR3_LPTIM1SEL_1
#define RCC_LPTIM1CLKSOURCE_LSE        RCC_CCIPR3_LPTIM1SEL
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM2_Clock_Source LPTIM2 Clock Source
  * @{
  */
#define RCC_LPTIM2CLKSOURCE_PCLK1      0x00000000U
#define RCC_LPTIM2CLKSOURCE_LSI        RCC_CCIPR1_LPTIM2SEL_0
#define RCC_LPTIM2CLKSOURCE_HSI        RCC_CCIPR1_LPTIM2SEL_1
#define RCC_LPTIM2CLKSOURCE_LSE        RCC_CCIPR1_LPTIM2SEL
/**
  * @}
  */

/** @defgroup RCCEx_FDCAN1_Clock_Source FDCAN1 Kernel Clock Source
  * @{
  */
#define RCC_FDCAN1CLKSOURCE_HSE          0x00000000U
#define RCC_FDCAN1CLKSOURCE_PLL1         RCC_CCIPR1_FDCANSEL_0
#define RCC_FDCAN1CLKSOURCE_PLL2         RCC_CCIPR1_FDCANSEL_1
/**
  * @}
  */

/** @defgroup RCCEx_CLK48_Clock_Source CLK48 Clock Source
  * @{
  */
#define RCC_CLK48CLKSOURCE_HSI48        0x00000000U
#define RCC_CLK48CLKSOURCE_PLL2         RCC_CCIPR1_CLK48MSEL_0
#define RCC_CLK48CLKSOURCE_PLL1         RCC_CCIPR1_CLK48MSEL_1
#define RCC_CLK48CLKSOURCE_MSIK         RCC_CCIPR1_CLK48MSEL
/**
  * @}
  */

/** @defgroup RCCEx_ADCDAC_Clock_Source ADC1 Clock Source
  * @{
  */
#define RCC_ADCDACCLKSOURCE_HCLK          0x00000000U
#define RCC_ADCDACCLKSOURCE_SYSCLK        RCC_CCIPR3_ADCDACSEL_0
#define RCC_ADCDACCLKSOURCE_PLL2          RCC_CCIPR3_ADCDACSEL_1
#define RCC_ADCDACCLKSOURCE_HSE           (RCC_CCIPR3_ADCDACSEL_0 | RCC_CCIPR3_ADCDACSEL_1)
#define RCC_ADCDACCLKSOURCE_HSI           RCC_CCIPR3_ADCDACSEL_2
#define RCC_ADCDACCLKSOURCE_MSIK          (RCC_CCIPR3_ADCDACSEL_0 | RCC_CCIPR3_ADCDACSEL_2)
/**
  * @}
  */

/** @defgroup RCCEx_MDF1_Clock_Source MDF1 Clock Source
  * @{
  */
#define RCC_MDF1CLKSOURCE_HCLK       0x00000000U
#define RCC_MDF1CLKSOURCE_PLL1       RCC_CCIPR2_MDF1SEL_0
#define RCC_MDF1CLKSOURCE_PLL3       RCC_CCIPR2_MDF1SEL_1
#define RCC_MDF1CLKSOURCE_PIN        (RCC_CCIPR2_MDF1SEL_0 | RCC_CCIPR2_MDF1SEL_1)
#define RCC_MDF1CLKSOURCE_MSIK       RCC_CCIPR2_MDF1SEL_2
/**
  * @}
  */

/** @defgroup RCCEx_ADF1_Clock_Source ADF1 Clock Source
  * @{
  */
#define RCC_ADF1CLKSOURCE_HCLK       0x00000000U
#define RCC_ADF1CLKSOURCE_PLL1       RCC_CCIPR3_ADF1SEL_0
#define RCC_ADF1CLKSOURCE_PLL3       RCC_CCIPR3_ADF1SEL_1
#define RCC_ADF1CLKSOURCE_PIN       (RCC_CCIPR3_ADF1SEL_0 | RCC_CCIPR3_ADF1SEL_1)
#define RCC_ADF1CLKSOURCE_MSIK       RCC_CCIPR3_ADF1SEL_2
/**
  * @}
  */

/** @defgroup RCCEx_SAI1_Clock_Source SAI1 Clock Source
  * @{
  */
#define RCC_SAI1CLKSOURCE_PLL2         0x00000000U
#define RCC_SAI1CLKSOURCE_PLL3         RCC_CCIPR2_SAI1SEL_0
#define RCC_SAI1CLKSOURCE_PLL1         RCC_CCIPR2_SAI1SEL_1
#define RCC_SAI1CLKSOURCE_PIN          (RCC_CCIPR2_SAI1SEL_1 | RCC_CCIPR2_SAI1SEL_0)
#define RCC_SAI1CLKSOURCE_HSI          RCC_CCIPR2_SAI1SEL_2
/**
  * @}
  */

/** @defgroup RCCEx_SAI2_Clock_Source SAI2 Clock Source
  * @{
  */
#define RCC_SAI2CLKSOURCE_PLL2         0x00000000U
#define RCC_SAI2CLKSOURCE_PLL3         RCC_CCIPR2_SAI2SEL_0
#define RCC_SAI2CLKSOURCE_PLL1         RCC_CCIPR2_SAI2SEL_1
#define RCC_SAI2CLKSOURCE_PIN          (RCC_CCIPR2_SAI2SEL_1 | RCC_CCIPR2_SAI2SEL_0)
#define RCC_SAI2CLKSOURCE_HSI          RCC_CCIPR2_SAI2SEL_2
/**
  * @}
  */

/** @defgroup RCCEx_SDMMC_Clock_Source SDMMC1/2 Clock Source
  * @{
  */
#define RCC_SDMMCCLKSOURCE_CLK48     0x00000000U
#define RCC_SDMMCCLKSOURCE_PLL1      RCC_CCIPR2_SDMMCSEL
/**
  * @}
  */

/** @defgroup RCCEx_OSPI_Clock_Source OctoSPI Clock Source
  * @{
  */
#define RCC_OSPICLKSOURCE_SYSCLK     0x00000000U
#define RCC_OSPICLKSOURCE_MSIK       RCC_CCIPR2_OCTOSPISEL_0
#define RCC_OSPICLKSOURCE_PLL1       RCC_CCIPR2_OCTOSPISEL_1
#define RCC_OSPICLKSOURCE_PLL2       (RCC_CCIPR2_OCTOSPISEL_1|RCC_CCIPR2_OCTOSPISEL_0)
/**
  * @}
  */

/** @defgroup RCCEx_DAC1_Clock_Source DAC1 Clock Source
  * @{
  */
#define RCC_DAC1CLKSOURCE_LSE       0x00000000U
#define RCC_DAC1CLKSOURCE_LSI        RCC_CCIPR3_DAC1SEL
/**
  * @}
  */

/** @defgroup RCC_Timicsel_items RCC timicsel items
  * @brief RCC Timicsel items to configure timicsel
  * @{
  */
#define RCC_TIMIC_HSI_256              RCC_CCIPR1_TIMICSEL_2                                                  /*!<HSI/256 selected for Timer16/17 and LPTimer2 */
#define RCC_TIMIC_MSI_1024             RCC_CCIPR1_TIMICSEL_2                                                  /*!<MSIS/1024 selected for Timer16/17 and LPTimer2*/
#define RCC_TIMIC_MSI_4               (RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_1)                         /*!<MSIS/4 selected for Timer16/17 and LPTimer2*/
#define RCC_TIMIC_MSIK_4              (RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_0)                         /*!<MSIK/1024 selected for Timer16/17 and LPTimer2*/
#define RCC_TIMIC_MSIK_1024           (RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_1 | RCC_CCIPR1_TIMICSEL_0) /*!<MSIK/4 selected for Timer16/17 and LPTimer2*/
/**
  * @}
  */
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
#define RCC_CRS_SYNC_POLARITY_RISING   0x00000000U             /*!< Synchro Active on rising edge (default) */
#define RCC_CRS_SYNC_POLARITY_FALLING  CRS_CFGR_SYNCPOL        /*!< Synchro Active on falling edge */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ReloadValueDefault RCCEx CRS ReloadValueDefault
  * @{
  */
#define RCC_CRS_RELOADVALUE_DEFAULT    0x0000BB7FU       /*!< The reset value of the RELOAD field corresponds
                                                             to a target frequency of 48 MHz and a synchronization
                                                             signal frequency of 1 kHz (SOF signal from USB). */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ErrorLimitDefault RCCEx CRS ErrorLimitDefault
  * @{
  */
#define RCC_CRS_ERRORLIMIT_DEFAULT     0x00000022U         /*!< Default Frequency error limit */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_HSI48CalibrationDefault RCCEx CRS HSI48CalibrationDefault
  * @{
  */
#define RCC_CRS_HSI48CALIBRATION_DEFAULT 0x00000020U       /*!< The default value is 32, which corresponds to
                                                                the middle of the trimming interval.
                                                                The trimming step is around 67 kHz between two
                                                                consecutive TRIM steps. A higher TRIM value
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
#define RCC_CRS_IT_TRIMOVF             CRS_CR_ERRIE          /*!< Trimming overflow or underflow */
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
#endif /* CRS */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */

/** @brief  Macro to adjust the MSI oscillator calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal MSI RC.
  * @param  __MSICALIBRATIONVALUE__: specifies the calibration trimming value
  *         This parameter must be a number between 0 and 0x1F.
  * @param  __MSIRANGE__ : specifies the MSI Range value
  *         This parameter can be one of the following values:
  *            @arg RCC_MSIRANGE_0
  *            @arg RCC_MSIRANGE_1
  *            @arg RCC_MSIRANGE_2
  *            @arg RCC_MSIRANGE_3
  *            @arg RCC_MSIRANGE_4
  *            @arg RCC_MSIRANGE_5
  *            @arg RCC_MSIRANGE_6
  *            @arg RCC_MSIRANGE_7
  *            @arg RCC_MSIRANGE_8
  *            @arg RCC_MSIRANGE_9
  *            @arg RCC_MSIRANGE_10
  *            @arg RCC_MSIRANGE_11
  *            @arg RCC_MSIRANGE_12
  *            @arg RCC_MSIRANGE_13
  *            @arg RCC_MSIRANGE_14
  *            @arg RCC_MSIRANGE_15
  * @retval None
  */
#define __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(__MSICALIBRATIONVALUE__ , __MSIRANGE__) \
  do \
  { \
    if(__MSIRANGE__ >= RCC_MSIRANGE_12) \
    {\
      MODIFY_REG((RCC->ICSCR2), (RCC_ICSCR2_MSITRIM3), ((uint32_t)(__MSICALIBRATIONVALUE__)<<\
                                                        RCC_ICSCR2_MSITRIM3_Pos));\
    }\
    else if(__MSIRANGE__ >= RCC_MSIRANGE_8)\
    {\
      MODIFY_REG((RCC->ICSCR2), (RCC_ICSCR2_MSITRIM2), ((uint32_t)(__MSICALIBRATIONVALUE__)<<\
                                                        RCC_ICSCR2_MSITRIM2_Pos));\
    }\
    else if(__MSIRANGE__ >= RCC_MSIRANGE_4)\
    {\
      MODIFY_REG((RCC->ICSCR2), (RCC_ICSCR2_MSITRIM1), ((uint32_t)(__MSICALIBRATIONVALUE__)<<\
                                                        RCC_ICSCR2_MSITRIM1_Pos));\
    } \
    else /* if(__MSIRANGE__ >= RCC_MSIRANGE_0) */\
    { \
      MODIFY_REG((RCC->ICSCR2), (RCC_ICSCR2_MSITRIM0), ((uint32_t)(__MSICALIBRATIONVALUE__)<<\
                                                        RCC_ICSCR2_MSITRIM0_Pos));\
    } \
  } while(0)

/** @brief  Macro to configure timer input capture clock source.
  * @param  __TIMICSOURCE__ : specifies the TIMIC clock source
  *         This parameter can be one or a combination of the following values:
  *            @arg RCC_TIMIC_HSI_256:     HSI/256 selected for Timer16/17 and LPTimer2
  *            @arg RCC_TIMIC_MSI_1024:    MSIS/1024 selected for Timer16/17 and LPTimer2
  *            @arg RCC_TIMIC_MSI_4:       MSIS/4 selected for Timer16/17 and LPTimer2
  *            @arg RCC_TIMIC_MSIK_1024:   MSIK/1024 selected for Timer16/17 and LPTimer2
  *            @arg RCC_TIMIC_MSIK_4 :     MSIK/4 selected for Timer16/17 and LPTimer2
  * @note      combination to be avoid :
  *            RCC_TIMIC_MSI_1024 and RCC_TIMIC_MSIK_1024
  *            RCC_TIMIC_MSI_4 and RCC_TIMIC_MSIK_4
  * @retval None
  */
#define __HAL_RCC_TIMIC_CLK_CONFIG(__TIMICSOURCE__) \
  do \
  {                                                         \
    /*Disable All TIMIC SOURCE*/                               \
    MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL,(0x00000000));               \
    /*Select TIMIC clock SOURCE*/                                            \
    MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL,(uint32_t)(__TIMICSOURCE__));\
  } while(0)

/** @brief  Macro to disable timer input capture clock source.
  * @retval None
  */
#define __HAL_RCC_TIMIC_CLK_DISABLE() MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL,(0x00000000))

/** @brief  Macros to enable or disable the PLL2.
  * @note   After enabling PLL2, the application software should wait on
  *         PLL2RDY flag to be set indicating that PLL2 clock is stable and can
  *         be used as kernel clock source.
  * @note   The PLL2 is disabled by hardware when entering STOP and STANDBY modes.
  * @retval None
  */
#define __HAL_RCC_PLL2_ENABLE()  SET_BIT(RCC->CR, RCC_CR_PLL2ON)
#define __HAL_RCC_PLL2_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON)

/** @brief  Macro to configure the PLL2 clock source.
  * @note   This function must be used only when all PLL2 is disabled.
  * @param  __PLL2SOURCE__: specifies the PLL2 entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_MSI: MSI oscillator clock selected as PLL2 clock entry
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL2 clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL2 clock entry
  */
#define __HAL_RCC_PLL2_PLLSOURCE_CONFIG(__PLL2SOURCE__) MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2SRC,\
                                                                   (__PLL2SOURCE__))

/** @brief  Macro to get the oscillator used as PLL2 clock source.
  * @retval The oscillator used as PLL2 clock source. The returned value can be one
  *         of the following:
  *              - RCC_PLLSOURCE_NONE: No oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_MSI: MSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSI: HSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSE: HSE oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL2_OSCSOURCE() ((uint32_t)(RCC->PLL2CFGR & RCC_PLL2CFGR_PLL2SRC))

/** @brief  Macro to configures the PLL2  source, multiplication and division factors.
  * @note   This function must be used only when PLL2 is disabled.
  * @param  __PLL2SOURCE__: specifies the PLL2 entry clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_NONE  No clock selected as PLL2 clock entry
  *            @arg @ref RCC_PLLSOURCE_MSI  MSI oscillator clock selected as PLL2 clock entry
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL2 clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL2 clock entry
  * @param  __PLL2M__ specifies the division factor of PLL2 input clock.
  *         This parameter must be a number between Min_Data = 1 and Max_Data = 16
  * @param  __PLL2N__: specifies the multiplication factor for PLL2 VCO output clock
  *          This parameter must be a number between 4 and 512.
  * @note   You have to set the PLL2N parameter correctly to ensure that the VCO
  *         output frequency is between 64 and 344 MHz.
  *         PLL2 clock frequency = f(PLL2) multiplied by PLL2N
  * @param  __PLL2P__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  * @param  __PLL2Q__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  * @param  __PLL2R__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  * @retval None
  */
#define __HAL_RCC_PLL2_CONFIG(__PLL2SOURCE__, __PLL2M__, __PLL2N__, __PLL2P__, __PLL2Q__, __PLL2R__) \
  do \
  { \
    MODIFY_REG(RCC->PLL2CFGR,(RCC_PLL2CFGR_PLL2SRC|RCC_PLL2CFGR_PLL2M), ((__PLL2SOURCE__)<< RCC_PLL2CFGR_PLL2SRC_Pos) |\
               (((__PLL2M__) - 1U) << RCC_PLL2CFGR_PLL2M_Pos));\
    MODIFY_REG(RCC->PLL2DIVR ,(RCC_PLL2DIVR_PLL2N|RCC_PLL2DIVR_PLL2P|RCC_PLL2DIVR_PLL2Q|\
                               RCC_PLL2DIVR_PLL2R), ((((__PLL2N__) - 1U) & RCC_PLL2DIVR_PLL2N) | ((((__PLL2P__) -1U)<< \
                                                     RCC_PLL2DIVR_PLL2P_Pos) & RCC_PLL2DIVR_PLL2P) |\
                                                     ((((__PLL2Q__) -1U) << RCC_PLL2DIVR_PLL2Q_Pos)& \
                                                      RCC_PLL2DIVR_PLL2Q) | ((((__PLL2R__)- 1U) << \
                                                                              RCC_PLL2DIVR_PLL2R_Pos) & \
                                                                             RCC_PLL2DIVR_PLL2R))); \
  } while(0)

/**
  * @brief  Enables or disables each clock output (PLL2_P_CLK, PLL2_Q_CLK, PLL2_R_CLK)
  * @note   Enabling/disabling  Those Clocks can be any time  without the need to stop the PLL2,
  *         This is mainly used to save Power.
  * @param  __PLL2_CLOCKOUT__ specifies the PLL2 clock outputted.
  *         This parameter can be one or a combination of the following values:
  *            @arg RCC_PLL2_DIVP: This clock is used to generate an accurate clock to achieve
  *                                   high-quality audio performance on SAI interface.
  *            @arg RCC_PLL2_DIVQ: This clock is used to generate the clock for the USB FS (48 MHz),
  *                                   the random number generator (<=48 MHz).
  *            @arg RCC_PLL2_DIVR: Clock used to clock ADC peripheral.
  * @retval None
  */
#define __HAL_RCC_PLL2CLKOUT_ENABLE(__PLL2_CLOCKOUT__)   SET_BIT(RCC->PLL2CFGR, (__PLL2_CLOCKOUT__))
#define __HAL_RCC_PLL2CLKOUT_DISABLE(__PLL2_CLOCKOUT__)  CLEAR_BIT(RCC->PLL2CFGR, (__PLL2_CLOCKOUT__))

/**
  * @brief  Macro to get the PLL2 clock output enable status.
  * @param  __PLL2_CLOCKOUT__ specifies the PLL2 clock to be outputted.
  *         This parameter can be one of the following values:
  *         This parameter can be one or a combination of the following values:
  *            @arg RCC_PLL2_DIVP: This clock is used to generate an accurate clock to achieve
  *                                   high-quality audio performance on SAI interface.
  *            @arg RCC_PLL2_DIVQ: This clock is used to generate the clock for the USB FS (48 MHz),
  *                                   the random number generator (<=48 MHz).
  *            @arg RCC_PLL2_DIVR: Clock used to clock ADC peripheral.
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLL2CLKOUT_CONFIG(__PLL2_CLOCKOUT__)  READ_BIT(RCC->PLL2CFGR, (__PLL2_CLOCKOUT__))

/**
  * @brief  Enables or disables Fractional Part Of The Multiplication Factor of PLL2 VCO
  * @note   Enabling/disabling  Fractional Part can be any time  without the need to stop the PLL2
  * @retval None
  */
#define __HAL_RCC_PLL2FRACN_ENABLE()   SET_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2FRACEN)
#define __HAL_RCC_PLL2FRACN_DISABLE()  CLEAR_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2FRACEN)

/**
  * @brief  Macro to configures PLL2 clock Fractional Part Of The Multiplication Factor
  * @note   These bits can be written at any time, allowing dynamic fine-tuning of the PLL2 VCO
  * @param  __PLL2FRACN__: Specifies Fractional Part Of The Multiplication factor for PLL2 VCO
  *                           It should be a value between 0 and 8191
  * @note   Warning: the software has to set correctly these bits to insure that the VCO
  *                  output frequency is between its valid frequency range, which is:
  *                  192 to 836 MHz if PLL2VCOSEL = 0
  *                  150 to 420 MHz if PLL2VCOSEL = 1
  * @retval None
  */
#define  __HAL_RCC_PLL2FRACN_CONFIG(__PLL2FRACN__) MODIFY_REG(RCC->PLL2FRACR, RCC_PLL2FRACR_PLL2FRACN,\
                                                              (uint32_t)(__PLL2FRACN__) << RCC_PLL2FRACR_PLL2FRACN_Pos)

/** @brief  Macro to select  the PLL2  reference frequency range.
  * @param  __PLL2VCIRange__: specifies the PLL2 input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLVCIRANGE_0: Range frequency is between 4 and 8 MHz
  *            @arg RCC_PLLVCIRANGE_1: Range frequency is between 8 and 16 MHz
  * @retval None
  */
#define __HAL_RCC_PLL2_VCIRANGE(__PLL2VCIRange__) \
  MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2RGE, (__PLL2VCIRange__))

/** @brief  Macros to enable or disable the main PLL3.
  * @note   After enabling  PLL3, the application software should wait on
  *         PLL3RDY flag to be set indicating that PLL3 clock is stable and can
  *         be used as kernel clock source.
  * @note   PLL3 is disabled by hardware when entering STOP and STANDBY modes.
  */
#define __HAL_RCC_PLL3_ENABLE()  SET_BIT(RCC->CR, RCC_CR_PLL3ON)
#define __HAL_RCC_PLL3_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_PLL3ON)

/** @brief  Macro to configure the PLL3 clock source.
  * @note   This function must be used only when all PLL3 is disabled.
  * @param  __PLL3SOURCE__: specifies the PLL3 entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSOURCE_MSI: MSI oscillator clock selected as PLL3 clock entry
  *            @arg RCC_PLLSOURCE_HSI: HSI oscillator clock selected as PLL3 clock entry
  *            @arg RCC_PLLSOURCE_HSE: HSE oscillator clock selected as PLL3 clock entry
  *
  */
#define __HAL_RCC_PLL3_PLLSOURCE_CONFIG(__PLL3SOURCE__) MODIFY_REG(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3SRC, \
                                                                   (__PLL3SOURCE__))

/** @brief  Macro to get the oscillator used as PLL3 clock source.
  * @retval The oscillator used as PLL3 clock source. The returned value can be one
  *         of the following:
  *              - RCC_PLLSOURCE_NONE: No oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_MSI: MSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSI: HSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSE: HSE oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL3_OSCSOURCE() ((uint32_t)(RCC->PLL3CFGR & RCC_PLL3CFGR_PLL3SRC))

/** @brief  Macro to configures the PLL3  source, multiplication and division factors.
  * @note   This function must be used only when PLL3 is disabled.
  *
  * @param  __PLL3SOURCE__: specifies the PLL3 entry clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_NONE  No clock selected as PLL3 clock entry
  *            @arg @ref RCC_PLLSOURCE_MSI  MSI oscillator clock selected as PLL3 clock entry
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL3 clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL3 clock entry
  * @param  __PLL3M__ specifies the division factor of PLL3 input clock.
  *         This parameter must be a number between Min_Data = 1 and Max_Data = 16
  * @param  __PLL3N__: specifies the multiplication factor for PLL3 VCO output clock
  *          This parameter must be a number between 4 and 512.
  * @note   You have to set the PLL3N parameter correctly to ensure that the VCO
  *         output frequency is between 64 and 344 MHz.
  *         PLL3 clock frequency = f(PLL3) multiplied by PLL3N
  * @param  __PLL3P__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  * @param  __PLL3Q__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  * @param  __PLL3R__: specifies the division factor for peripheral kernel clocks
  *          This parameter must be a number between 1 and 128
  * @retval None
  */
#define __HAL_RCC_PLL3_CONFIG(__PLL3SOURCE__, __PLL3M__, __PLL3N__, __PLL3P__, __PLL3Q__, __PLL3R__) \
  do\
  {\
    MODIFY_REG(RCC->PLL3CFGR,(RCC_PLL3CFGR_PLL3SRC|RCC_PLL3CFGR_PLL3M), ((__PLL3SOURCE__) << RCC_PLL3CFGR_PLL3SRC_Pos)|\
               (((__PLL3M__) - 1U) << RCC_PLL3CFGR_PLL3M_Pos));\
    MODIFY_REG(RCC->PLL3DIVR ,(RCC_PLL3DIVR_PLL3N|RCC_PLL3DIVR_PLL3P|RCC_PLL3DIVR_PLL3Q|RCC_PLL3DIVR_PLL3R),\
               ((((__PLL3N__) - 1U) & RCC_PLL3DIVR_PLL3N) | ((((__PLL3P__) -1U) << RCC_PLL3DIVR_PLL3P_Pos) &\
                                                             RCC_PLL3DIVR_PLL3P) | ((((__PLL3Q__) -1U) << \
                                                                                    RCC_PLL3DIVR_PLL3Q_Pos) & \
                                                                                    RCC_PLL3DIVR_PLL3Q) | \
                ((((__PLL3R__)- 1U) << RCC_PLL3DIVR_PLL3R_Pos) & RCC_PLL3DIVR_PLL3R))); \
  } while(0)

/**
  * @brief  Macro to configures  PLL3 clock Fractional Part of The Multiplication Factor
  * @note   These bits can be written at any time, allowing dynamic fine-tuning of the PLL3 VCO
  * @param  __PLL3FRACN__: specifies Fractional Part Of The Multiplication Factor for PLL3 VCO
  *                            It should be a value between 0 and 8191
  * @note   Warning: the software has to set correctly these bits to insure that the VCO
  *                  output frequency is between its valid frequency range, which is:
  *                  192 to 836 MHz if PLL3VCOSEL = 0
  *                  150 to 420 MHz if PLL3VCOSEL = 1
  * @retval None
  */
#define  __HAL_RCC_PLL3FRACN_CONFIG(__PLL3FRACN__) MODIFY_REG(RCC->PLL3FRACR, RCC_PLL3FRACR_PLL3FRACN, \
                                                              (uint32_t)(__PLL3FRACN__) << RCC_PLL3FRACR_PLL3FRACN_Pos)

/** @brief  Macro to select  the PLL3  reference frequency range.
  * @param  __PLL3VCIRange__: specifies the PLL1 input frequency range
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLVCIRANGE_0: Range frequency is between 4 and 8 MHz
  *            @arg RCC_PLLVCIRANGE_1: Range frequency is between 8 and 16 MHz
  * @retval None
  */
#define __HAL_RCC_PLL3_VCIRANGE(__PLL3VCIRange__) \
  MODIFY_REG(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3RGE, (__PLL3VCIRange__))

/**
  * @brief  Enables or disables Fractional Part Of The Multiplication Factor of PLL3 VCO
  * @note   Enabling/disabling  Fractional Part can be any time  without the need to stop the PLL3
  * @retval None
  */
#define __HAL_RCC_PLL3FRACN_ENABLE()   SET_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3FRACEN)
#define __HAL_RCC_PLL3FRACN_DISABLE()  CLEAR_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3FRACEN)

/**
  * @brief  Enables or disables each clock output (PLL3_P_CLK, PLL3_Q_CLK, PLL3_R_CLK)
  * @note   Enabling/disabling  Those Clocks can be any time  without the need to stop the PLL3,
  *         This is mainly used to save Power.
  * @param  __PLL3_CLOCKOUT__: specifies the PLL3 clock to be outputted
  *          This parameter can be one of the following values:
  *            @arg RCC_PLL3_DIVP: This clock is used to generate an accurate clock to achieve
  *                                   high-quality audio performance on SAI interface.
  * @retval None
  */
#define __HAL_RCC_PLL3CLKOUT_ENABLE(__PLL3_CLOCKOUT__)  SET_BIT(RCC->PLL3CFGR, (__PLL3_CLOCKOUT__))
#define __HAL_RCC_PLL3CLKOUT_DISABLE(__PLL3_CLOCKOUT__) CLEAR_BIT(RCC->PLL3CFGR, (__PLL3_CLOCKOUT__))

/**
  * @brief  Macro to get clock output enable status (PLL3_SAI2).
  * @param  __PLL3_CLOCKOUT__ specifies the PLL3 clock to be outputted.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLL3_DIVP: This clock is used to generate an accurate clock to achieve
  *                                high-quality audio performance on SAI interface.
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLL3CLKOUT_CONFIG(__PLL3_CLOCKOUT__)  READ_BIT(RCC->PLL3CFGR, (__PLL3_CLOCKOUT__))

/** @brief  Macro to configure the ADC1, ADC4 and DAC interface clock.
  * @param  __ADCDAC_CLKSOURCE__ specifies the ADC1, ADC4 and DAC digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADCDACCLKSOURCE_HCLK clock selected as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_SYSCLK clock selected as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_PLL2 clock selected as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_HSE clock selected as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_HSI clock selected as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_MSIK clock selected as ADC1, ADC4 and DAC  clock
  * @retval None
  */
#define __HAL_RCC_ADCDAC_CONFIG(__ADCDAC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ADCDACSEL, (uint32_t)(__ADCDAC_CLKSOURCE__))

/** @brief  Macro to get the ADCDAC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADCDACCLKSOURCE_HCLK clock used as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_SYSCLK clock used as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_PLL2 clock used as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_HSE clock used as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_HSI clock used as ADC1, ADC4 and DAC  clock
  *            @arg @ref RCC_ADCDACCLKSOURCE_MSIK clock used as ADC1, ADC4 and DAC  clock
  */
#define __HAL_RCC_GET_ADCDAC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_ADCDACSEL)))

/** @brief  Macro to configure the CLK48 source (CLK48CLK).
  * @param  __CLK48_SOURCE__: specifies the CLK48 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_CLK48CLKSOURCE_HSI48: HSI48 selected as CLK48 source
  *            @arg RCC_CLK48CLKSOURCE_PLL2 : PLL2 selected as CLK48 source
  *            @arg RCC_CLK48CLKSOURCE_PLL1 : PLL1 selected as CLK48 source
  *            @arg RCC_CLK48CLKSOURCE_MSIK  : MSIK selected as CLK48 source
  */
#define __HAL_RCC_CLK48_CONFIG(__CLK48_SOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_CLK48MSEL, (uint32_t)(__CLK48_SOURCE__))

/** @brief  macro to get the CLK48 source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_CLK48CLKSOURCE_HSI48: HSI48 used as CLK48 source
  *            @arg RCC_CLK48CLKSOURCE_PLL2 : PLL2 used as CLK48 source
  *            @arg RCC_CLK48CLKSOURCE_PLL1 : PLL1 used as CLK48 source
  *            @arg RCC_CLK48CLKSOURCE_MSIK  : MSIK used as CLK48 source
  */
#define __HAL_RCC_GET_CLK48_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_CLK48MSEL)))

/** @brief  Macro to configure the FDCAN1 kernel clock (FDCAN1CLK).
  * @param  __FDCAN1_CLKSOURCE__ specifies the FDCAN1 kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_FDCAN1CLKSOURCE_HSE  HSE selected as FDCAN1 kernel clock
  *            @arg @ref RCC_FDCAN1CLKSOURCE_PLL1  PLL1 Clock selected as FDCAN1 kernel clock
  *            @arg @ref RCC_FDCAN1CLKSOURCE_PLL2  PLL2 Clock selected as FDCAN1 kernel clock
  * @retval None
  */
#define __HAL_RCC_FDCAN1_CONFIG(__FDCAN1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_FDCANSEL, (uint32_t)(__FDCAN1_CLKSOURCE__))

/** @brief  Macro to get the FDCAN1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_FDCAN1CLKSOURCE_HSE  HSE selected as FDCAN1 kernel clock
  *            @arg @ref RCC_FDCAN1CLKSOURCE_PLL1  PLL1 Clock selected as FDCAN1 kernel clock
  *            @arg @ref RCC_FDCAN1CLKSOURCE_PLL2  PLL2 Clock selected as FDCAN1 kernel clock
  */
#define __HAL_RCC_GET_FDCAN1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_FDCANSEL)))

/** @brief  Macro to configure the LPTIM34 clock (LPTIM34CLK).
  * @param  __LPTIM34_CLKSOURCE__ specifies the LPTIM34 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM34CLKSOURCE_MSIK MSIK selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_LSI  LSI selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_HSI  HSI selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_LSE  LSE selected as LPTIM34 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM34_CONFIG(__LPTIM34_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPTIM34SEL, (uint32_t)(__LPTIM34_CLKSOURCE__))

/** @brief  Macro to get the LPTIM34 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM34CLKSOURCE_MSIK MSIK selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_LSI  LSI selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_HSI  HSI selected as LPTIM34 clock
  *            @arg @ref RCC_LPTIM34CLKSOURCE_LSE  LSE selected as LPTIM34 clock
  */
#define __HAL_RCC_GET_LPTIM34_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPTIM34SEL)))

/** @brief  Macro to configure the LPTIM1 clock (LPTIM1CLK).
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_MSIK  MSIK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  LSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPTIM1SEL, (uint32_t)(__LPTIM1_CLKSOURCE__))

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM1CLKSOURCE_MSIK  MSIK selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_HSI  HSI selected as LPTIM1 clock
  *            @arg @ref RCC_LPTIM1CLKSOURCE_LSE  LSE selected as LPTIM1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPTIM1SEL)))

/** @brief  Macro to configure the LPTIM2 clock (LPTIM2CLK).
  * @param  __LPTIM2_CLKSOURCE__ specifies the LPTIM2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK1 selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI  LSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE  LSE selected as LPTIM2 clock
  * @retval None
  */
#define __HAL_RCC_LPTIM2_CONFIG(__LPTIM2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_LPTIM2SEL, (uint32_t)(__LPTIM2_CLKSOURCE__))

/** @brief  Macro to get the LPTIM2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPTIM2CLKSOURCE_PCLK1  PCLK1 selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_HSI  HSI selected as LPTIM2 clock
  *            @arg @ref RCC_LPTIM2CLKSOURCE_LSE  LSE selected as LPTIM2 clock
  */
#define __HAL_RCC_GET_LPTIM2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_LPTIM2SEL)))

/** @brief  macro to configure the SPI1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI1CLKSOURCE_PCLK2 : PCLK2 Clock selected as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_SYSCLK : SYSCLK Clock selected as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_HSI : HSI Clock selected as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_MSIK : MSIK Clock selected as SPI1 clock
  */

#define __HAL_RCC_SPI1_CONFIG(__SPI1CLKSource__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SPI1SEL, (uint32_t)(__SPI1CLKSource__))

/** @brief  macro to get the SPI1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI1CLKSOURCE_PCLK2 : PCLK2 Clock used as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_SYSCLK : SYSCLK Clock used as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_HSI : HSI Clock used as SPI1 clock
  *            @arg RCC_SPI1CLKSOURCE_MSIK : MSIK Clock used as SPI1 clock
  */
#define __HAL_RCC_GET_SPI1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SPI1SEL)))

/** @brief  macro to configure the SPI2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI2CLKSOURCE_PCLK3 : PCLK3 selected as SPI2 clock
  *            @arg RCC_SPI2CLKSOURCE_SYSCLK : SYSCLK Clock selected as SPI2 clock
  *            @arg RCC_SPI2CLKSOURCE_HSI : HSI Clock selected as SPI2 clock
  *            @arg RCC_SPI2CLKSOURCE_MSIK : MSIK Clock selected as SPI2 clock
  */

#define __HAL_RCC_SPI2_CONFIG(__SPI2CLKSource__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SPI2SEL, (uint32_t)(__SPI2CLKSource__))

/** @brief  macro to get the SPI2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI2CLKSOURCE_PCLK1 : PCLK1 Clock used as SPI2 clock
  *            @arg RCC_SPI2CLKSOURCE_SYSCLK : SYSCLK Clock used as SPI2 clock
  *            @arg RCC_SPI2CLKSOURCE_HSI : HSI Clock used as SPI2 clock
  *            @arg RCC_SPI2CLKSOURCE_MSIK : MSIK Clock used as SPI2 clock
  */
#define __HAL_RCC_GET_SPI2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SPI2SEL)))

/** @brief  macro to configure the SPI3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI3CLKSOURCE_PCLK3 : PCLK3 selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_SYSCLK : SYSCLK Clock selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_HSI : HSI Clock selected as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_MSIK : MSIK Clock selected as SPI3 clock
  */
#define __HAL_RCC_SPI3_CONFIG(__SPI3CLKSource__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_SPI3SEL, (uint32_t)(__SPI3CLKSource__))

/** @brief  macro to get the SPI3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI3CLKSOURCE_PCLK3 : PCLK3 used as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_SYSCLK : SYSCLK Clock used as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_HSI : HSI Clock used as SPI3 clock
  *            @arg RCC_SPI3CLKSOURCE_MSIK : MSIK Clock used as SPI3 clock
  */
#define __HAL_RCC_GET_SPI3_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_SPI3SEL)))


/** @brief  Macro to configure the I2C1 clock (I2C1CLK).
  * @param  __I2C1_CLKSOURCE__ specifies the I2C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_MSIK  MSIK selected as I2C1 clock
  * @retval None
  */
#define __HAL_RCC_I2C1_CONFIG(__I2C1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_I2C1SEL, (uint32_t)(__I2C1_CLKSOURCE__))

/** @brief  Macro to get the I2C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C1CLKSOURCE_PCLK1  PCLK1 selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_SYSCLK  System Clock selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_HSI  HSI selected as I2C1 clock
  *            @arg @ref RCC_I2C1CLKSOURCE_MSIK  MSIK selected as I2C1 clock
  */
#define __HAL_RCC_GET_I2C1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_I2C1SEL)))

/** @brief  Macro to configure the I2C2 clock (I2C2CLK).
  * @param  __I2C2_CLKSOURCE__ specifies the I2C2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_PCLK1  PCLK1 selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_SYSCLK  System Clock selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_HSI  HSI selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_MSIK  MSIK selected as I2C2 clock
  * @retval None
  */
#define __HAL_RCC_I2C2_CONFIG(__I2C2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_I2C2SEL, (uint32_t)(__I2C2_CLKSOURCE__))

/** @brief  Macro to get the I2C2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C2CLKSOURCE_PCLK1  PCLK1 selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_SYSCLK  System Clock selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_HSI  HSI selected as I2C2 clock
  *            @arg @ref RCC_I2C2CLKSOURCE_MSIK  MSIK selected as I2C2 clock
  */
#define __HAL_RCC_GET_I2C2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_I2C2SEL)))

/** @brief  Macro to configure the I2C3 clock (I2C3CLK).
  * @param  __I2C3_CLKSOURCE__ specifies the I2C3 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK3 : PCLK3 selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI : HSI selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_MSIK : MSIK selected as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK : System Clock selected as I2C3 clock
  * @retval None
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_I2C3SEL, (uint32_t)(__I2C3_CLKSOURCE__))

/** @brief  Macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C3CLKSOURCE_PCLK3 : PCLK3 used as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_HSI : HSI used as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_MSIK : MSIK used as I2C3 clock
  *            @arg @ref RCC_I2C3CLKSOURCE_SYSCLK : System Clock used as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_I2C3SEL)))

/** @brief  Macro to configure the I2C4 clock (I2C4CLK).
  * @param  __I2C4_CLKSOURCE__ specifies the I2C4 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_I2C4CLKSOURCE_PCLK1  PCLK1 selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_SYSCLK  System Clock selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_HSI  HSI selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_MSIK  MSIK selected as I2C4 clock
  * @retval None
  */
#define __HAL_RCC_I2C4_CONFIG(__I2C4_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_I2C4SEL, (uint32_t)(__I2C4_CLKSOURCE__))

/** @brief  Macro to get the I2C4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_I2C4CLKSOURCE_PCLK1  PCLK1 selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_SYSCLK  System Clock selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_HSI  HSI selected as I2C4 clock
  *            @arg @ref RCC_I2C4CLKSOURCE_MSIK  MSIK selected as I2C4 clock
  */
#define __HAL_RCC_GET_I2C4_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_I2C4SEL)))

/** @brief  Macro to configure the USART1 clock (USART1CLK).
  * @param  __USART1_CLKSOURCE__ specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2  PCLK1 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  SE selected as USART1 clock
  * @retval None
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USART1SEL, (uint32_t)(__USART1_CLKSOURCE__))

/** @brief  Macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART1CLKSOURCE_PCLK2  PCLK1 selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_HSI  HSI selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_SYSCLK  System Clock selected as USART1 clock
  *            @arg @ref RCC_USART1CLKSOURCE_LSE  LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USART1SEL)))

/** @brief  Macro to configure the USART2 clock (USART2CLK).
  * @param  __USART2_CLKSOURCE__ specifies the USART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  * @retval None
  */
#define __HAL_RCC_USART2_CONFIG(__USART2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USART2SEL, (uint32_t)(__USART2_CLKSOURCE__))

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART2CLKSOURCE_PCLK1  PCLK1 selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_HSI  HSI selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_SYSCLK  System Clock selected as USART2 clock
  *            @arg @ref RCC_USART2CLKSOURCE_LSE  LSE selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USART2SEL)))

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
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USART3SEL, (uint32_t)(__USART3_CLKSOURCE__))

/** @brief  Macro to get the USART3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_USART3CLKSOURCE_PCLK1  PCLK1 selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_HSI  HSI selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_SYSCLK  System Clock selected as USART3 clock
  *            @arg @ref RCC_USART3CLKSOURCE_LSE  LSE selected as USART3 clock
  */
#define __HAL_RCC_GET_USART3_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USART3SEL)))

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
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_UART4SEL, (uint32_t)(__UART4_CLKSOURCE__))

/** @brief  Macro to get the UART4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_UART4CLKSOURCE_PCLK1  PCLK1 selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_HSI  HSI selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_SYSCLK  System Clock selected as UART4 clock
  *            @arg @ref RCC_UART4CLKSOURCE_LSE  LSE selected as UART4 clock
  */
#define __HAL_RCC_GET_UART4_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_UART4SEL)))

/** @brief  Macro to configure the UART5 clock (UART5CLK).
  * @param  __UART5_CLKSOURCE__ specifies the UART5 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_UART5CLKSOURCE_PCLK1  PCLK1 selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_HSI  HSI selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_SYSCLK  System Clock selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_LSE  LSE selected as UART5 clock
  * @retval None
  */
#define __HAL_RCC_UART5_CONFIG(__UART5_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_UART5SEL, (uint32_t)(__UART5_CLKSOURCE__))

/** @brief  Macro to get the UART5 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_UART5CLKSOURCE_PCLK1  PCLK1 selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_HSI  HSI selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_SYSCLK  System Clock selected as UART5 clock
  *            @arg @ref RCC_UART5CLKSOURCE_LSE  LSE selected as UART5 clock
  */
#define __HAL_RCC_GET_UART5_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_UART5SEL)))

/** @brief  Macro to configure the LPUART1 clock (LPUART1CLK).
  *
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK3  PCLK3 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_MSIK  MSIK selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  * @retval None
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPUART1SEL, (uint32_t)(__LPUART1_CLKSOURCE__))

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_LPUART1CLKSOURCE_PCLK3  PCLK3 selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_HSI  HSI selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_MSIK  MSIK selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_SYSCLK  System Clock selected as LPUART1 clock
  *            @arg @ref RCC_LPUART1CLKSOURCE_LSE  LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPUART1SEL)))


/** @brief  Macro to configure the OctoSPI clock.
  * @param  __OSPI_CLKSOURCE__ specifies the OctoSPI clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_OSPICLKSOURCE_SYSCLK  System Clock selected as OctoSPI clock
  *            @arg @ref RCC_OSPICLKSOURCE_MSIK   MSIK clock selected as OctoSPI clock
  *            @arg @ref RCC_OSPICLKSOURCE_PLL1   PLL1 Q divider clock selected as OctoSPI clock
  *            @arg @ref RCC_OSPICLKSOURCE_PLL2   PLL2 Q divider clock selected as OctoSPI clock
  * @retval None
  */
#define __HAL_RCC_OSPI_CONFIG(__OSPI_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_OCTOSPISEL, (uint32_t)(__OSPI_CLKSOURCE__))

/** @brief  Macro to get the OctoSPI clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_OSPICLKSOURCE_SYSCLK  System Clock selected as OctoSPI clock
  *            @arg @ref RCC_OSPICLKSOURCE_MSIK   MSIK clock selected as OctoSPI clock
  *            @arg @ref RCC_OSPICLKSOURCE_PLL1   PLL1 Q divider clock selected as OctoSPI clock
  *            @arg @ref RCC_OSPICLKSOURCE_PLL2   PLL2 Q divider clock selected as OctoSPI clock
  */
#define __HAL_RCC_GET_OSPI_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_OCTOSPISEL)))

/** @brief  Macro to configure the SDMMC1/2 clock (SDMMCCLK).
  * @param  __SDMMC_CLKSOURCE__: specifies the SDMMC1/2 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_SDMMCCLKSOURCE_CLK48: CLK48 selected as SDMMC1/2 clock
  *            @arg RCC_SDMMCCLKSOURCE_PLL1: PLL1 P selected as SDMMC1/2 clock
  */
#define __HAL_RCC_SDMMC_CONFIG(__SDMMC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SDMMCSEL, (uint32_t)(__SDMMC_CLKSOURCE__))

/** @brief  macro to get the SDMMC1/2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SDMMCCLKSOURCE_CLK48: CLK48 selected as SDMMC1/2 clock
  *            @arg RCC_SDMMCCLKSOURCE_PLL1: PLL1 P selected as SDMMC1/2 clock
  */
#define __HAL_RCC_GET_SDMMC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SDMMCSEL)))

/** @brief macro to configure the RNG clock (RNGCLK).
  * @param  __RNG_CLKSource__: specifies the RNG clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_RNGCLKSOURCE_HSI48: HSI48 selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_HSI48_DIV2: HSI48/2 selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_HSI: HSI selected as RNG clock
  */
#define __HAL_RCC_RNG_CONFIG(__RNG_CLKSource__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_RNGSEL, (uint32_t)(__RNG_CLKSource__))

/** @brief  macro to get the RNG clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_RNGCLKSOURCE_HSI48: HSI48 selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_HSI48_DIV2: HSI48/2 selected as RNG clock
  *            @arg RCC_RNGCLKSOURCE_HSI: HSI selected as RNG clock
  */
#define __HAL_RCC_GET_RNG_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_RNGSEL)))

/** @brief macro to configure the SAES clock (SAESCLK).
  * @param  __SAES_CLKSource__: specifies the SAES clock source.
  *         This parameter can be one of the following values:
  *             @arg RCC_SAESCLKSOURCE_SHSI: SHSI selected as SAES clock
  *             @arg RCC_SAESCLKSOURCE_SHSI_DIV2: SHSI/2 selected as SAES clock
  */
#define __HAL_RCC_SAES_CONFIG(__SAES_CLKSource__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SAESSEL, (uint32_t)(__SAES_CLKSource__))

/** @brief  macro to get the SAES clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SAESCLKSOURCE_SHSI: SHSI selected as SAES clock
  *            @arg RCC_SAESCLKSOURCE_SHSI_DIV2: SHSI/2 selected as SAES clock
  */
#define __HAL_RCC_GET_SAES_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SAESSEL)))

/**
  * @brief  Macro to configure the SAI1 clock source.
  * @param  __SAI1_CLKSOURCE__ defines the SAI1 clock source. This clock is derived
  *         from the PLL2, system PLL or external clock (through a dedicated pin).
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL2 SAI1 clock = PLL2 "P" clock (PLL2CLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL3 SAI1 clock = PLL3 "P" clock (PLL3CLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL1 SAI1 clock = PLL1 "P" clock (PLL1CLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_PIN  SAI1 clock = External Clock (SAI1_EXTCLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_HSI  SAI1 clock = HSI16
  *
  * @note  HSI16 is automatically set as SAI1 clock source when PLL are disabled for devices without PLL3.
  * @retval None
  */
#define __HAL_RCC_SAI1_CONFIG(__SAI1_CLKSOURCE__)\
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SAI1SEL, (uint32_t)(__SAI1_CLKSOURCE__))

/** @brief  Macro to get the SAI1 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL2  SAI1 clock = PLL2 "P" clock (PLL2CLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL3  SAI1 clock = PLL3 "P" clock (PLL3CLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_PLL1  SAI1 clock  = PLL "P" clock (PLL1CLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_PIN  SAI1 clock = External Clock (SAI1_EXTCLK)
  *             @arg @ref RCC_SAI1CLKSOURCE_HSI  SAI1 clock = HSI16
  * @note  Despite returned values RCC_SAI1CLKSOURCE_PLL2 or RCC_SAI1CLKSOURCE_PLL, HSI16 is automatically set as SAI1
  *        clock source when PLLs are disabled for devices without PLL3.
  */
#define __HAL_RCC_GET_SAI1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SAI1SEL)))

/**
  * @brief  Macro to configure the SAI2 clock source.
  * @param  __SAI2_CLKSOURCE__ defines the SAI2 clock source. This clock is derived
  *         from the PLL3, system PLL or external clock (through a dedicated pin).
  *          This parameter can be one of the following values:
  *             @arg @ref RCC_SAI2CLKSOURCE_PLL2  SAI2 clock = PLL2 "P" clock (PLL2CLK)
  *             @arg @ref RCC_SAI2CLKSOURCE_PLL3  SAI2 clock = PLL3 "P" clock (PLL3CLK)
  *             @arg @ref RCC_SAI2CLKSOURCE_PLL1  SAI2 clock = PLL1 "P" clock (PLL1CLK)
  *             @arg @ref RCC_SAI2CLKSOURCE_PIN  SAI2 clock = External Clock (SAI2_EXTCLK)
  *             @arg @ref RCC_SAI2CLKSOURCE_HSI  SAI2 clock = HSI16
  * @retval None
  */
#define __HAL_RCC_SAI2_CONFIG(__SAI2_CLKSOURCE__ )\
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SAI2SEL, (uint32_t)(__SAI2_CLKSOURCE__))

/** @brief  Macro to get the SAI2 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg @ref RCC_SAI2CLKSOURCE_PLL2  SAI2 clock = PLL2 "P" clock (PLL2CLK)
  *             @arg @ref RCC_SAI2CLKSOURCE_PLL3  SAI2 clock = PLL3 "P" clock (PLL3CLK)
  *             @arg @ref RCC_SAI2CLKSOURCE_PLL1  SAI2 clock = PLL1 "P" clock (PLL1CLK)
  *             @arg @ref RCC_SAI2CLKSOURCE_PIN  SAI2 clock = External Clock (SAI2_EXTCLK)
  *             @arg @ref RCC_SAI2CLKSOURCE_HSI  SAI2 clock = HSI16
  */
#define __HAL_RCC_GET_SAI2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SAI2SEL)))

/** @brief  Macro to configure the MDF1 clock.
  * @param  __MDF1_CLKSOURCE__ specifies the MDF1 clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_MDF1CLKSOURCE_HCLK  HCLK Clock selected as MDF1 clock
  *            @arg @ref RCC_MDF1CLKSOURCE_PLL1  PLL1 P Clock selected as MDF1 clock
  *            @arg @ref RCC_MDF1CLKSOURCE_PLL3  PLL3 Q Clock selected as MDF1 clock
  *            @arg @ref RCC_MDF1CLKSOURCE_PIN   External Clock (SAI1_EXTCLK) selected as MDF1 clock
  *            @arg @ref RCC_MDF1CLKSOURCE_MSIK  MSIK Clock selected as MDF1 clock
  * @retval None
  */
#define __HAL_RCC_MDF1_CONFIG(__MDF1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_MDF1SEL, (uint32_t)(__MDF1_CLKSOURCE__))

/** @brief  Macro to get the MDF1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_MDF1CLKSOURCE_HCLK  HCLK Clock used as MDF1 clock
  *            @arg @ref RCC_MDF1CLKSOURCE_PLL1  PLL1  Clock used as MDF1 clock
  *            @arg @ref RCC_MDF1CLKSOURCE_PLL3  PLL3  Clock used as MDF1 clock
  *            @arg @ref RCC_MDF1CLKSOURCE_PIN   External Clock (SAI1_EXTCLK) used as MDF1 clock
  *            @arg @ref RCC_MDF1CLKSOURCE_MSIK  MSIK Clock used as MDF1 clock
  */
#define __HAL_RCC_GET_MDF1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_MDF1SEL)))

/** @brief  Macro to configure the ADF1 clock.
  * @param  __ADF1_CLKSOURCE__ specifies the ADF1 clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_ADF1CLKSOURCE_HCLK  HCLK Clock selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_PLL1  PLL1 P Clock selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_PLL3  PLL3 Q Clock selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_PIN   External Clock (SAI1_EXTCLK) selected as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_MSIK  MSI Clock selected as ADF1 clock
  * @retval None
  */
#define __HAL_RCC_ADF1_CONFIG(__ADF1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ADF1SEL, (uint32_t)(__ADF1_CLKSOURCE__))

/** @brief  Macro to get the ADF1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_ADF1CLKSOURCE_HCLK  HCLK Clock used as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_PLL1  PLL1 P Clock used as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_PLL3  PLL3 Q Clock used as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_PIN   External Clock (SAI1_EXTCLK) used as ADF1 clock
  *            @arg @ref RCC_ADF1CLKSOURCE_MSIK   MSI Clock used as ADF1 clock
  */
#define __HAL_RCC_GET_ADF1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_ADF1SEL)))

/** @brief  Macro to configure the DAC1 interface clock.
  * @param  __DAC1_CLKSOURCE__ specifies the DAC1 digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_DAC1CLKSOURCE_LSE LSE clock selected as DAC1 clock
  *            @arg @ref RCC_DAC1CLKSOURCE_LSI LSI clock selected as DAC1 clock
  * @retval None
  */
#define __HAL_RCC_DAC1_CONFIG(__DAC1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_DAC1SEL, (uint32_t)(__DAC1_CLKSOURCE__))

/** @brief  Macro to get the DAC1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg @ref RCC_DAC1CLKSOURCE_LSE LSE clock selected as DAC1 clock
  *            @arg @ref RCC_DAC1CLKSOURCE_LSI LSI clock selected as DAC1 clock
  */
#define __HAL_RCC_GET_DAC1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_DAC1SEL)))

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
#define __HAL_RCC_CRS_GET_IT_SOURCE(__INTERRUPT__)  ((READ_BIT(CRS->CR, (__INTERRUPT__)) != RESET) ? SET : RESET)

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
#define  RCC_CRS_IT_ERROR_MASK             ((uint32_t)(RCC_CRS_IT_TRIMOVF | RCC_CRS_IT_SYNCERR | RCC_CRS_IT_SYNCMISS))

#define __HAL_RCC_CRS_CLEAR_IT(__INTERRUPT__)  do { \
                                                    if(((__INTERRUPT__) & RCC_CRS_IT_ERROR_MASK) != 0U) \
                                                    { \
                                                      WRITE_REG(CRS->ICR, CRS_ICR_ERRC |\
                                                      ((__INTERRUPT__) & ~RCC_CRS_IT_ERROR_MASK)); \
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
  * @note RCC_CRS_FLAG_ERR clears RCC_CRS_FLAG_TRIMOVF, RCC_CRS_FLAG_SYNCERR, RCC_CRS_FLAG_SYNCMISS and consequently
  *             RCC_CRS_FLAG_ERR
  * @retval None
  */
#define RCC_CRS_FLAG_ERROR_MASK        ((uint32_t)(RCC_CRS_FLAG_TRIMOVF | RCC_CRS_FLAG_SYNCERR | \
                                                   RCC_CRS_FLAG_SYNCMISS))

#define __HAL_RCC_CRS_CLEAR_FLAG(__FLAG__)   do { \
                                                  if(((__FLAG__) & RCC_CRS_FLAG_ERROR_MASK) != 0U) \
                                                  { \
                                                    WRITE_REG(CRS->ICR, CRS_ICR_ERRC | \
                                                    ((__FLAG__) & ~RCC_CRS_FLAG_ERROR_MASK)); \
                                                  } \
                                                  else \
                                                  { \
                                                    WRITE_REG(CRS->ICR, (__FLAG__)); \
                                                  } \
                                                } while(0)

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

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *pPeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *pPeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);
void     HAL_RCCEx_GetPLL1ClockFreq(PLL1_ClocksTypeDef *PLL1_Clocks);
void     HAL_RCCEx_GetPLL2ClockFreq(PLL2_ClocksTypeDef *PLL2_Clocks);
void     HAL_RCCEx_GetPLL3ClockFreq(PLL3_ClocksTypeDef *PLL3_Clocks);
/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_EnablePLL2(RCC_PLL2InitTypeDef  *PLL2Init);
HAL_StatusTypeDef HAL_RCCEx_DisablePLL2(void);
HAL_StatusTypeDef HAL_RCCEx_EnablePLL3(RCC_PLL3InitTypeDef  *PLL3Init);
HAL_StatusTypeDef HAL_RCCEx_DisablePLL3(void);
HAL_StatusTypeDef HAL_RCCEx_EnableMSIPLLFastStartup(void);
HAL_StatusTypeDef HAL_RCCEx_DisableMSIPLLFastStartup(void);
HAL_StatusTypeDef HAL_RCCEx_EnableMSIPLLModeSelection(uint32_t MSIPLLModeSelection);
void              HAL_RCCEx_WakeUpStopCLKConfig(uint32_t WakeUpClk);
void              HAL_RCCEx_KerWakeUpStopCLKConfig(uint32_t WakeUpClk);
void              HAL_RCCEx_StandbyMSIRangeConfig(uint32_t MSIRange);
void              HAL_RCCEx_EnableLSECSS(void);
void              HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_LSECSS_IRQHandler(void);
void              HAL_RCCEx_LSECSS_Callback(void);
void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);
void              HAL_RCCEx_EnableMSIPLLMode(void);
void              HAL_RCCEx_DisableMSIPLLMode(void);

/**
  * @}
  */

#if defined(CRS)

/** @addtogroup RCCEx_Exported_Functions_Group3
  * @{
  */
void              HAL_RCCEx_CRSConfig(const RCC_CRSInitTypeDef *const pInit);
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

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_HAL_RCC_EX_H */
