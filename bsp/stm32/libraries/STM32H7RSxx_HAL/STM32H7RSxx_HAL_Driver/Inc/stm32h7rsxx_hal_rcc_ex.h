/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extension module.
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
#ifndef STM32H7RSxx_HAL_RCC_EX_H
#define STM32H7RSxx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
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
  * @brief  RCC PLL1 Clocks structure definition
  */

/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint32_t PeriphClockSelection;   /*!< The Extended Clock to be configured.
                                        This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t FmcClockSelection;      /*!< Specifies FMC clock source
                                        This parameter can be a value of @ref RCCEx_FMC_Clock_Source    */

  uint32_t Xspi1ClockSelection;    /*!< Specifies XSPI1 clock source
                                        This parameter can be a value of @ref RCCEx_XSPI1_Clock_Source  */

  uint32_t Xspi2ClockSelection;    /*!< Specifies XSPI2 clock source
                                        This parameter can be a value of @ref RCCEx_XSPI2_Clock_Source  */

  uint32_t CkperClockSelection;   /*!< Specifies CKPER clock source
                                        This parameter can be a value of @ref RCCEx_CLKP_Clock_Source   */

  uint32_t AdcClockSelection;      /*!< Specifies ADC interface clock source
                                        This parameter can be a value of @ref RCCEx_ADC_Clock_Source     */

  uint32_t Adf1ClockSelection;     /*!< Specifies ADF1 Clock clock source
                                        This parameter can be a value of @ref RCCEx_ADF1_Clock_Source  */

  uint32_t CecClockSelection;      /*!< Specifies CEC clock source
                                        This parameter can be a value of @ref RCCEx_CEC_Clock_Source     */

  uint32_t Eth1RefClockSelection;     /*!< Specifies ETH1 REF clock source
                                        This parameter can be a value of @ref RCCEx_ETH1REF_Clock_Source   */

  uint32_t Eth1PhyClockSelection;   /*!< Specifies ETH1 PHY clock source
                                        This parameter can be a value of @ref RCCEx_ETH1PHY_Clock_Source   */

  uint32_t FdcanClockSelection;    /*!< Specifies FDCAN kernel clock source
                                        This parameter can be a value of @ref RCCEx_FDCAN_Clock_Source   */

  uint32_t I2c1_I3c1ClockSelection;     /*!< Specifies I2C1/I3C1 clock source
                                        This parameter can be a value of @ref RCCEx_I2C1_I3C1_Clock_Source    */

  uint32_t I2c23ClockSelection;    /*!< Specifies I2C2/I2C3 clock source
                                        This parameter can be a value of @ref RCCEx_I2C23_Clock_Source    */

  uint32_t Lptim1ClockSelection;   /*!< Specifies LPTIM1 clock source
                                        This parameter can be a value of @ref RCCEx_LPTIM1_Clock_Source  */

  uint32_t Lptim23ClockSelection;  /*!< Specifies LPTIM2/LPTIM3 clock source
                                        This parameter can be a value of @ref RCCEx_LPTIM23_Clock_Source  */

  uint32_t Lptim45ClockSelection;  /*!< Specifies LPTIM4/LPTIM5 clock source
                                        This parameter can be a value of @ref RCCEx_LPTIM45_Clock_Source  */

  uint32_t Lpuart1ClockSelection;  /*!< Specifies LPUART1 clock source
                                        This parameter can be a value of @ref RCCEx_LPUART1_Clock_Source */

  uint32_t LtdcClockSelection;     /*!< Specifies LPUART1 clock source
                                        This parameter can be a value of @ref RCCEx_LTDC_Clock_Source */

  uint32_t PssiClockSelection;     /*!< Specifies PSSI clock source
                                        This parameter can be a value of @ref RCCEx_PSSI_Clock_Source   */

  uint32_t Sai1ClockSelection;     /*!< Specifies SAI1 clock source
                                        This parameter can be a value of @ref RCCEx_SAI1_Clock_Source    */

  uint32_t Sai2ClockSelection;     /*!< Specifies SAI2 clock source
                                        This parameter can be a value of @ref RCCEx_SAI2_Clock_Source    */

  uint32_t Sdmmc12ClockSelection;  /*!< Specifies SDMMC clock source
                                        This parameter can be a value of @ref RCCEx_SDMMC12_Clock_Source  */

  uint32_t Spi1ClockSelection;     /*!< Specifies SPI1 clock source
                                        This parameter can be a value of @ref RCCEx_SPI1_Clock_Source    */

  uint32_t Spi23ClockSelection;    /*!< Specifies SPI2/SPI3 clock source
                                        This parameter can be a value of @ref RCCEx_SPI23_Clock_Source    */

  uint32_t Spi45ClockSelection;    /*!< Specifies SPI4/SPI5 clock source
                                        This parameter can be a value of @ref RCCEx_SPI45_Clock_Source    */

  uint32_t Spi6ClockSelection;     /*!< Specifies SPI6 clock source
                                        This parameter can be a value of @ref RCCEx_SPI6_Clock_Source    */

  uint32_t SpdifrxClockSelection;  /*!< Specifies SPDIFRX Clock clock source
                                        This parameter can be a value of @ref RCCEx_SPDIFRX_Clock_Source */

  uint32_t Usart1ClockSelection;   /*!< Specifies USART1 clock source
                                        This parameter can be a value of @ref RCCEx_USART1_Clock_Source  */

  uint32_t Usart234578ClockSelection; /*!< Specifies USART2/USART3/UART4/UART5/UART7/UART8 clock source
                                           This parameter can be a value of @ref RCCEx_USART234578_Clock_Source  */

  uint32_t UsbPhycClockSelection;  /*!< Specifies USB PHYC clock source
                                        This parameter can be a value of @ref RCCEx_USB_PHYC_Clock_Source */

  uint32_t UsbOtgFsClockSelection; /*!< Specifies USB OTG FS clock source
                                        This parameter can be a value of @ref RCCEx_USB_OTGFS_Clock_Source */

  uint32_t RTCClockSelection;      /*!< Specifies RTC Clock clock source
                                        This parameter can be a value of @ref RCC_RTC_Clock_Source       */

  uint32_t TIMPresSelection;       /*!< Specifies TIM Clock Prescalers Selection.
                                        This parameter can be a value of @ref RCCEx_TIM_Prescaler_Selection */
} RCC_PeriphCLKInitTypeDef;

/**
  * @brief RCC_CRS Init structure definition
  */
typedef struct
{
  uint32_t Prescaler;              /*!< Specifies the division factor of the SYNC signal.
                                        This parameter can be a value of @ref RCCEx_CRS_SynchroDivider  */

  uint32_t Source;                 /*!< Specifies the SYNC signal source.
                                        This parameter can be a value of @ref RCCEx_CRS_SynchroSource   */

  uint32_t Polarity;               /*!< Specifies the input polarity for the SYNC signal source.
                                        This parameter can be a value of @ref RCCEx_CRS_SynchroPolarity */

  uint32_t ReloadValue;            /*!< Specifies the value to be loaded in the frequency error counter with each SYNC event.
                                        It can be calculated in using macro __HAL_RCC_CRS_RELOADVALUE_CALCULATE(__FTARGET__, __FSYNC__)
                                        This parameter must be a number between 0 and 0xFFFF or a value of @ref RCCEx_CRS_ReloadValueDefault .*/

  uint32_t ErrorLimitValue;        /*!< Specifies the value to be used to evaluate the captured frequency error value.
                                        This parameter must be a number between 0 and 0xFF or a value of @ref RCCEx_CRS_ErrorLimitDefault */

  uint32_t HSI48CalibrationValue;  /*!< Specifies a user-programmable trimming value to the HSI48 oscillator.
                                        This parameter must be a number between 0 and 0x3F or a value of @ref RCCEx_CRS_HSI48CalibrationDefault */

} RCC_CRSInitTypeDef;

/**
  * @brief RCC_CRS Synchronization structure definition
  */
typedef struct
{
  uint32_t ReloadValue;            /*!< Specifies the value loaded in the Counter reload value.
                                        This parameter must be a number between 0 and 0xFFFF */

  uint32_t HSI48CalibrationValue;  /*!< Specifies value loaded in HSI48 oscillator smooth trimming.
                                        This parameter must be a number between 0 and 0x3F */

  uint32_t FreqErrorCapture;       /*!< Specifies the value loaded in the .FECAP, the frequency error counter
                                        value latched in the time of the last SYNC event.
                                        This parameter must be a number between 0 and 0xFFFF */

  uint32_t FreqErrorDirection;     /*!< Specifies the value loaded in the .FEDIR, the counting direction of the
                                        frequency error counter latched in the time of the last SYNC event.
                                        It shows whether the actual frequency is below or above the target.
                                        This parameter must be a value of @ref RCCEx_CRS_FreqErrorDirection*/

} RCC_CRSSynchroInfoTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants  RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_Periph_Clock_Selection  Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_FMC          (0x00000001U)
#define RCC_PERIPHCLK_XSPI1        (0x00000002U)
#define RCC_PERIPHCLK_XSPI2        (0x00000004U)
#define RCC_PERIPHCLK_CKPER        (0x00000008U)
#define RCC_PERIPHCLK_ADC          (0x00000010U)
#define RCC_PERIPHCLK_ADF1         (0x00000020U)
#define RCC_PERIPHCLK_CEC          (0x00000040U)
#define RCC_PERIPHCLK_ETH1REF      (0x00000080U)
#define RCC_PERIPHCLK_ETH1PHY      (0x00000100U)
#define RCC_PERIPHCLK_FDCAN        (0x00000200U)
#define RCC_PERIPHCLK_I2C23        (0x00000400U)
#define RCC_PERIPHCLK_I2C1_I3C1    (0x00000800U)
#define RCC_PERIPHCLK_LPTIM1       (0x00001000U)
#define RCC_PERIPHCLK_LPTIM23      (0x00002000U)
#define RCC_PERIPHCLK_LPTIM45      (0x00004000U)
#define RCC_PERIPHCLK_LPUART1      (0x00008000U)
#define RCC_PERIPHCLK_LTDC         (0x00010000U)
#define RCC_PERIPHCLK_PSSI         (0x00020000U)
#define RCC_PERIPHCLK_RTC          (0x00040000U)
#define RCC_PERIPHCLK_SAI1         (0x00080000U)
#define RCC_PERIPHCLK_SAI2         (0x00100000U)
#define RCC_PERIPHCLK_SDMMC12      (0x00200000U)
#define RCC_PERIPHCLK_SPDIFRX      (0x00400000U)
#define RCC_PERIPHCLK_SPI1         (0x00800000U)
#define RCC_PERIPHCLK_SPI23        (0x01000000U)
#define RCC_PERIPHCLK_SPI45        (0x02000000U)
#define RCC_PERIPHCLK_SPI6         (0x04000000U)
#define RCC_PERIPHCLK_TIM          (0x08000000U)
#define RCC_PERIPHCLK_USART1       (0x10000000U)
#define RCC_PERIPHCLK_USART234578  (0x20000000U)
#define RCC_PERIPHCLK_USBPHYC      (0x40000000U)
#define RCC_PERIPHCLK_USBOTGFS     (0x80000000U)
/**
  * @}
  */

/** @defgroup RCCEx_FMC_Clock_Source  FMC Clock Source
  * @{
  */
#define RCC_FMCCLKSOURCE_HCLK          0U                        /*!< HCLK selection (default) */
#define RCC_FMCCLKSOURCE_PLL1Q         RCC_CCIPR1_FMCSEL_0       /*!< PLL 'Q' output selection */
#define RCC_FMCCLKSOURCE_PLL2R         RCC_CCIPR1_FMCSEL_1       /*!< PLL2 'R' output selection */
#define RCC_FMCCLKSOURCE_HSI           RCC_CCIPR1_FMCSEL         /*!< HSI selection */
#define RCC_FMCCLKSOURCE_HCLK_DIV4     (RCC_CKPROTR_FMCSWP_2 | RCC_CKPROTR_FMCSWP_0) /*!< HCLK/4 selection (recovery position) */
/**
  * @}
  */

/** @defgroup RCCEx_XSPI1_Clock_Source  XSPI1 Clock Source
  * @{
  */
#define RCC_XSPI1CLKSOURCE_HCLK        0U                     /*!< HCLK selection (default) */
#define RCC_XSPI1CLKSOURCE_PLL2S       RCC_CCIPR1_XSPI1SEL_0  /*!< PLL2 'S' output selection */
#define RCC_XSPI1CLKSOURCE_PLL2T       RCC_CCIPR1_XSPI1SEL_1  /*!< PLL2 'T' output selection */
#define RCC_XSPI1CLKSOURCE_HCLK_DIV4   RCC_CKPROTR_XSPI1SWP_2 /*!< HCLK/4 selection (recovery position) */
/**
  * @}
  */

/** @defgroup RCCEx_XSPI2_Clock_Source  XSPI2 Clock Source
  * @{
  */
#define RCC_XSPI2CLKSOURCE_HCLK        0U                     /*!< HCLK selection (default) */
#define RCC_XSPI2CLKSOURCE_PLL2S       RCC_CCIPR1_XSPI2SEL_0  /*!< PLL2 'S' output selection */
#define RCC_XSPI2CLKSOURCE_PLL2T       RCC_CCIPR1_XSPI2SEL_1  /*!< PLL2 'T' output selection */
#define RCC_XSPI2CLKSOURCE_HCLK_DIV4   RCC_CKPROTR_XSPI2SWP_2 /*!< HCLK/4 selection (recovery position) */
/**
  * @}
  */

/** @defgroup RCCEx_CLKP_Clock_Source  CLKP Clock Source
  * @{
  */
#define RCC_CLKPSOURCE_HSI         0U                          /*!< HSI selection (default) */
#define RCC_CLKPSOURCE_CSI         RCC_CCIPR1_CKPERSEL_0     /*!< CSI selection */
#define RCC_CLKPSOURCE_HSE         RCC_CCIPR1_CKPERSEL_1     /*!< HSE selection */
/**
  * @}
  */

/** @defgroup RCCEx_ADC_Clock_Source  ADC Clock Source
  * @{
  */
#define RCC_ADCCLKSOURCE_PLL2P     0U                      /*!< PLL2 'P' output selection (default) */
#define RCC_ADCCLKSOURCE_PLL3R     RCC_CCIPR1_ADCSEL_0   /*!< PLL3 'R' output selection */
#define RCC_ADCCLKSOURCE_CLKP      RCC_CCIPR1_ADCSEL_1   /*!< Clock peripheral output selection */
/**
  * @}
  */

/** @defgroup RCCEx_ADF1_Clock_Source  ADF1 Clock Source
  * @{
  */
#define RCC_ADF1CLKSOURCE_HCLK     0U                        /*!< HCLK selection (default) */
#define RCC_ADF1CLKSOURCE_PLL2P    RCC_CCIPR1_ADF1SEL_0    /*!< PLL2 'P' output selection */
#define RCC_ADF1CLKSOURCE_PLL3P    RCC_CCIPR1_ADF1SEL_1    /*!< PLL3 'P' output selection */
#define RCC_ADF1CLKSOURCE_PIN      (RCC_CCIPR1_ADF1SEL_1 |  RCC_CCIPR1_ADF1SEL_0) /*!< External I2S_PIN selection */
#define RCC_ADF1CLKSOURCE_CSI      RCC_CCIPR1_ADF1SEL_2    /*!< CSI selection */
#define RCC_ADF1CLKSOURCE_HSI      (RCC_CCIPR1_ADF1SEL_2 |  RCC_CCIPR1_ADF1SEL_0) /*!< HSI selection */
/**
  * @}
  */

/** @defgroup RCCEx_CEC_Clock_Source  CEC Clock Source
  * @{
  */
#define RCC_CECCLKSOURCE_LSE       0U                          /*!< LSE selection (default) */
#define RCC_CECCLKSOURCE_LSI       RCC_CCIPR2_CECSEL_0      /*!< LSI selection */
#define RCC_CECCLKSOURCE_CSI       RCC_CCIPR2_CECSEL_1      /*!< CSI divided by 122 selection */
/**
  * @}
  */

/** @defgroup RCCEx_ETH1REF_Clock_Source  ETH1 REF Clock Source
  * @{
  */
#define RCC_ETH1REFCLKSOURCE_PHY      0U                          /*!< ETH PHY selection (default) */
#define RCC_ETH1REFCLKSOURCE_HSE      RCC_CCIPR1_ETH1REFCKSEL_0   /*!< HSE selection */
#define RCC_ETH1REFCLKSOURCE_ETH      RCC_CCIPR1_ETH1REFCKSEL_1   /*!< ETH Feedback output selection */
/**
  * @}
  */

/** @defgroup RCCEx_ETH1PHY_Clock_Source  ETH1 PHY Clock Source
  * @{
  */
#define RCC_ETH1PHYCLKSOURCE_HSE    0U                         /*!< HSE selection (default) */
#define RCC_ETH1PHYCLKSOURCE_PLL3S  RCC_CCIPR1_ETH1PHYCKSEL      /*!< PLL3 'S' output selection */
/**
  * @}
  */

/** @defgroup RCCEx_FDCAN_Clock_Source  FDCAN Kernel Clock Source
  * @{
  */
#define RCC_FDCANCLKSOURCE_HSE     0U                          /*!< HSE selection (default) */
#define RCC_FDCANCLKSOURCE_PLL1Q   RCC_CCIPR2_FDCANSEL_0    /*!< PLL1 'Q' output selection */
#define RCC_FDCANCLKSOURCE_PLL2P   RCC_CCIPR2_FDCANSEL_1    /*!< PLL2 'P' output selection */
/**
  * @}
  */

/** @defgroup RCCEx_I2C23_Clock_Source  I2C2/I2C3 Clock Source
  * @{
  */
#define RCC_I2C23CLKSOURCE_PCLK1   0U                          /*!< PCLK1 selection (default) */
#define RCC_I2C23CLKSOURCE_PLL3R   RCC_CCIPR2_I2C23SEL_0    /*!< PLL3 'R' output selection */
#define RCC_I2C23CLKSOURCE_HSI     RCC_CCIPR2_I2C23SEL_1    /*!< HSI selection */
#define RCC_I2C23CLKSOURCE_CSI     (RCC_CCIPR2_I2C23SEL_1 | RCC_CCIPR2_I2C23SEL_0) /*!< CSI selection */
/**
  * @}
  */

/** @defgroup RCCEx_I2C1_I3C1_Clock_Source  I2C1/I3C1Clock Source
  * @{
  */
#define RCC_I2C1_I3C1CLKSOURCE_PCLK1    0U                            /*!< PCLK1 selection (default) */
#define RCC_I2C1_I3C1CLKSOURCE_PLL3R    RCC_CCIPR2_I2C1_I3C1SEL_0  /*!< PLL3 'R' output selection */
#define RCC_I2C1_I3C1CLKSOURCE_HSI      RCC_CCIPR2_I2C1_I3C1SEL_1  /*!< HSI selection */
#define RCC_I2C1_I3C1CLKSOURCE_CSI      (RCC_CCIPR2_I2C1_I3C1SEL_1 | RCC_CCIPR2_I2C1_I3C1SEL_0) /*!< CSI selection */
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source  LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_PCLK1  0U                          /*!< PCLK1 selection (default) */
#define RCC_LPTIM1CLKSOURCE_PLL2P  RCC_CCIPR2_LPTIM1SEL_0   /*!< PLL2 'P' output selection */
#define RCC_LPTIM1CLKSOURCE_PLL3R  RCC_CCIPR2_LPTIM1SEL_1   /*!< PLL3 'R' output selection */
#define RCC_LPTIM1CLKSOURCE_LSE    (RCC_CCIPR2_LPTIM1SEL_1 | RCC_CCIPR2_LPTIM1SEL_0) /*!< LSE selection */
#define RCC_LPTIM1CLKSOURCE_LSI    RCC_CCIPR2_LPTIM1SEL_2   /*!< LSI selection */
#define RCC_LPTIM1CLKSOURCE_CLKP   (RCC_CCIPR2_LPTIM1SEL_2 | RCC_CCIPR2_LPTIM1SEL_0) /*!< Clock peripheral output selection */
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM23_Clock_Source  LPTIM2/LPTIM3 Clock Source
  * @{
  */
#define RCC_LPTIM23CLKSOURCE_PCLK4  0U                          /*!< PCLK4 selection (default) */
#define RCC_LPTIM23CLKSOURCE_PLL2P  RCC_CCIPR4_LPTIM23SEL_0 /*!< PLL2 'P' output selection */
#define RCC_LPTIM23CLKSOURCE_PLL3R  RCC_CCIPR4_LPTIM23SEL_1 /*!< PLL3 'R' output selection */
#define RCC_LPTIM23CLKSOURCE_LSE    (RCC_CCIPR4_LPTIM23SEL_1 | RCC_CCIPR4_LPTIM23SEL_0) /*!< LSE selection */
#define RCC_LPTIM23CLKSOURCE_LSI    RCC_CCIPR4_LPTIM23SEL_2 /*!< LSI selection */
#define RCC_LPTIM23CLKSOURCE_CLKP   (RCC_CCIPR4_LPTIM23SEL_2 | RCC_CCIPR4_LPTIM23SEL_0) /*!< Clock peripheral output selection */
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM45_Clock_Source  LPTIM4/LPTIM5 Clock Source
  * @{
  */
#define RCC_LPTIM45CLKSOURCE_PCLK4  0U                          /*!< PCLK4 selection (default) */
#define RCC_LPTIM45CLKSOURCE_PLL2P  RCC_CCIPR4_LPTIM45SEL_0 /*!< PLL2 'P' output selection */
#define RCC_LPTIM45CLKSOURCE_PLL3R  RCC_CCIPR4_LPTIM45SEL_1 /*!< PLL3 'R' output selection */
#define RCC_LPTIM45CLKSOURCE_LSE    (RCC_CCIPR4_LPTIM45SEL_1 | RCC_CCIPR4_LPTIM45SEL_0) /*!< LSE selection */
#define RCC_LPTIM45CLKSOURCE_LSI    RCC_CCIPR4_LPTIM45SEL_2 /*!< LSI selection */
#define RCC_LPTIM45CLKSOURCE_CLKP   (RCC_CCIPR4_LPTIM45SEL_2 | RCC_CCIPR4_LPTIM45SEL_0) /*!< Clock peripheral output selection */
/**
  * @}
  */

/** @defgroup RCCEx_LPUART1_Clock_Source  LPUART1 Clock Source
  * @{
  */
#define RCC_LPUART1CLKSOURCE_PCLK4  0U                            /*!< PCLK4 selection (default) */
#define RCC_LPUART1CLKSOURCE_PLL2Q  RCC_CCIPR4_LPUART1SEL_0   /*!< PLL2 'Q' output selection */
#define RCC_LPUART1CLKSOURCE_PLL3Q  RCC_CCIPR4_LPUART1SEL_1   /*!< PLL2 'Q' output selection */
#define RCC_LPUART1CLKSOURCE_HSI    (RCC_CCIPR4_LPUART1SEL_1 | RCC_CCIPR4_LPUART1SEL_0)  /*!< HSI selection */
#define RCC_LPUART1CLKSOURCE_CSI    RCC_CCIPR4_LPUART1SEL_2   /*!< CSI selection */
#define RCC_LPUART1CLKSOURCE_LSE    (RCC_CCIPR4_LPUART1SEL_2 | RCC_CCIPR4_LPUART1SEL_0)  /*!< LSE selection */
/**
  * @}
  */

/** @defgroup RCCEx_LTDC_Clock_Source  LTDC Clock Source
  * @{
  */
#define RCC_LTDCCLKSOURCE_PLL3R     0U                            /*!< PLL3 'R' output selection (unique) */
/**
  * @}
  */

/** @defgroup RCCEx_PSSI_Clock_Source  PSSI Clock Source
  * @{
  */
#define RCC_PSSICLKSOURCE_PLL3R   0U                           /*!< PLL3 'R' output selection (default) */
#define RCC_PSSICLKSOURCE_CLKP    RCC_CCIPR1_PSSISEL         /*!< Clock peripheral output selection */
/**
  * @}
  */

/** @defgroup RCCEx_SAI1_Clock_Source SAI1 Clock Source
  * @{
  */
#define RCC_SAI1CLKSOURCE_PLL1Q    0U                          /*!< PLL1 'Q' output selection (default) */
#define RCC_SAI1CLKSOURCE_PLL2P    RCC_CCIPR3_SAI1SEL_0     /*!< PLL2 'P' output selection */
#define RCC_SAI1CLKSOURCE_PLL3P    RCC_CCIPR3_SAI1SEL_1     /*!< PLL3 'P' output selection */
#define RCC_SAI1CLKSOURCE_PIN      (RCC_CCIPR3_SAI1SEL_1 | RCC_CCIPR3_SAI1SEL_0)  /*!< I2S_PIN selection */
#define RCC_SAI1CLKSOURCE_CLKP     RCC_CCIPR3_SAI1SEL_2     /*!< Clock peripheral output selection */
/**
  * @}
  */

/** @defgroup RCCEx_SAI2_Clock_Source SAI2 Clock Source
  * @{
  */
#define RCC_SAI2CLKSOURCE_PLL1Q    0U                          /*!< PLL1 'Q' output selection (default) */
#define RCC_SAI2CLKSOURCE_PLL2P    RCC_CCIPR3_SAI2SEL_0     /*!< PLL2 'P' output selection */
#define RCC_SAI2CLKSOURCE_PLL3P    RCC_CCIPR3_SAI2SEL_1     /*!< PLL3 'P' output selection */
#define RCC_SAI2CLKSOURCE_PIN      (RCC_CCIPR3_SAI2SEL_1 | RCC_CCIPR3_SAI2SEL_0)  /*!< I2S_PIN selection */
#define RCC_SAI2CLKSOURCE_CLKP     RCC_CCIPR3_SAI2SEL_2     /*!< Clock peripheral output selection */
#define RCC_SAI2CLKSOURCE_SPDIF    (RCC_CCIPR3_SAI2SEL_2 | RCC_CCIPR3_SAI2SEL_0)  /*!< SPDIF output selection */
/**
  * @}
  */

/** @defgroup RCCEx_SDMMC12_Clock_Source  SDMMC Clock Source
  * @{
  */
#define RCC_SDMMC12CLKSOURCE_PLL2S   0U                          /*!< PLL2 'S' output selection (default) */
#define RCC_SDMMC12CLKSOURCE_PLL2T   RCC_CCIPR1_SDMMC12SEL       /*!< PLL2 'T' output selection */
/**
  * @}
  */

/** @defgroup RCCEx_SPDIFRX_Clock_Source  SPDIFRX Clock Source
  * @{
  */
#define RCC_SPDIFRXCLKSOURCE_PLL1Q 0U                          /*!< PLL1 'Q' output selection (default) */
#define RCC_SPDIFRXCLKSOURCE_PLL2R RCC_CCIPR2_SPDIFRXSEL_0  /*!< PLL2 'R' output selection */
#define RCC_SPDIFRXCLKSOURCE_PLL3R RCC_CCIPR2_SPDIFRXSEL_1  /*!< PLL3 'R' output selection */
#define RCC_SPDIFRXCLKSOURCE_HSI   RCC_CCIPR2_SPDIFRXSEL    /*!< HSI selection */
/**
  * @}
  */

/** @defgroup RCCEx_SPI1_Clock_Source  SPI1 Clock Source
  * @{
  */
#define RCC_SPI1CLKSOURCE_PLL1Q    0U                          /*!< PLL1 'Q' output selection (default) */
#define RCC_SPI1CLKSOURCE_PLL2P    RCC_CCIPR3_SPI1SEL_0     /*!< PLL2 'P' output selection */
#define RCC_SPI1CLKSOURCE_PLL3P    RCC_CCIPR3_SPI1SEL_1     /*!< PLL3 'P' output selection */
#define RCC_SPI1CLKSOURCE_PIN      (RCC_CCIPR3_SPI1SEL_1 | RCC_CCIPR3_SPI1SEL_0)  /*!< I2S_PIN selection */
#define RCC_SPI1CLKSOURCE_CLKP     RCC_CCIPR3_SPI1SEL_2     /*!< Clock peripheral output selection */
/**
  * @}
  */

/** @defgroup RCCEx_SPI23_Clock_Source  SPI2/SPI3 Clock Source
  * @{
  */
#define RCC_SPI23CLKSOURCE_PLL1Q   0U                          /*!< PLL1 'Q' output selection (default) */
#define RCC_SPI23CLKSOURCE_PLL2P   RCC_CCIPR2_SPI23SEL_0    /*!< PLL2 'P' output selection */
#define RCC_SPI23CLKSOURCE_PLL3P   RCC_CCIPR2_SPI23SEL_1    /*!< PLL3 'P' output selection */
#define RCC_SPI23CLKSOURCE_PIN     (RCC_CCIPR2_SPI23SEL_1 | RCC_CCIPR2_SPI23SEL_0)  /*!< I2S_PIN selection */
#define RCC_SPI23CLKSOURCE_CLKP    RCC_CCIPR2_SPI23SEL_2    /*!< Clock peripheral output selection */
/**
  * @}
  */

/** @defgroup RCCEx_SPI45_Clock_Source  SPI4/SPI5 Clock Source
  * @{
  */
#define RCC_SPI45CLKSOURCE_PCLK2   0U                          /*!< PCLK2 selection (default) */
#define RCC_SPI45CLKSOURCE_PLL2Q   RCC_CCIPR3_SPI45SEL_0    /*!< PLL2 'Q' output selection */
#define RCC_SPI45CLKSOURCE_PLL3Q   RCC_CCIPR3_SPI45SEL_1    /*!< PLL3 'Q' output selection */
#define RCC_SPI45CLKSOURCE_HSI     (RCC_CCIPR3_SPI45SEL_1 | RCC_CCIPR3_SPI45SEL_0)  /*!< HSI selection */
#define RCC_SPI45CLKSOURCE_CSI     RCC_CCIPR3_SPI45SEL_2    /*!< CSI selection */
#define RCC_SPI45CLKSOURCE_HSE     (RCC_CCIPR3_SPI45SEL_2 | RCC_CCIPR3_SPI45SEL_0)  /*!< HSE selection */
/**
  * @}
  */

/** @defgroup RCCEx_SPI6_Clock_Source  SPI6 Clock Source
  * @{
  */
#define RCC_SPI6CLKSOURCE_PCLK4    0U                          /*!< PCLK4 selection (default) */
#define RCC_SPI6CLKSOURCE_PLL2Q    RCC_CCIPR4_SPI6SEL_0    /*!< PLL2 'Q' output selection */
#define RCC_SPI6CLKSOURCE_PLL3Q    RCC_CCIPR4_SPI6SEL_1    /*!< PLL3 'Q' output selection */
#define RCC_SPI6CLKSOURCE_HSI      (RCC_CCIPR4_SPI6SEL_1 | RCC_CCIPR4_SPI6SEL_0)  /*!< HSI selection */
#define RCC_SPI6CLKSOURCE_CSI      RCC_CCIPR4_SPI6SEL_2    /*!< CSI selection */
#define RCC_SPI6CLKSOURCE_HSE      (RCC_CCIPR4_SPI6SEL_2 | RCC_CCIPR4_SPI6SEL_0)  /*!< HSE selection */
/**
  * @}
  */

/** @defgroup RCCEx_TIM_Prescaler_Selection TIM Prescaler Selection
  * @{
  */
#define RCC_TIMPRES_DISABLE   0U                         /*!< Timers clocks prescaler not set (default) */
#define RCC_TIMPRES_ENABLE    RCC_CFGR_TIMPRE            /*!< Timers clocks prescaler set */

/**
  * @}
  */

/** @defgroup RCCEx_USART1_Clock_Source  USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK2  0U                          /*!< PCLK2 selection (default) */
#define RCC_USART1CLKSOURCE_PLL2Q  RCC_CCIPR3_USART1SEL_0   /*!< PLL2 'Q' output selection */
#define RCC_USART1CLKSOURCE_PLL3Q  RCC_CCIPR3_USART1SEL_1   /*!< PLL2 'Q' output selection */
#define RCC_USART1CLKSOURCE_HSI    (RCC_CCIPR3_USART1SEL_1 | RCC_CCIPR3_USART1SEL_0)  /*!< HSI selection */
#define RCC_USART1CLKSOURCE_CSI    RCC_CCIPR3_USART1SEL_2   /*!< CSI selection */
#define RCC_USART1CLKSOURCE_LSE    (RCC_CCIPR3_USART1SEL_2 | RCC_CCIPR3_USART1SEL_0)  /*!< LSE selection */
/**
  * @}
  */

/** @defgroup RCCEx_USART234578_Clock_Source  USART2/USART3/UART4/UART5/UART7/UART8 Clock Source
  * @{
  */
#define RCC_USART234578CLKSOURCE_PCLK1  0U                            /*!< PCLK1 selection (default) */
#define RCC_USART234578CLKSOURCE_PLL2Q  RCC_CCIPR2_UART234578SEL_0 /*!< PLL2 'Q' output selection */
#define RCC_USART234578CLKSOURCE_PLL3Q  RCC_CCIPR2_UART234578SEL_1 /*!< PLL3 'Q' output selection */
#define RCC_USART234578CLKSOURCE_HSI    (RCC_CCIPR2_UART234578SEL_1 | RCC_CCIPR2_UART234578SEL_0)  /*!< HSI selection */
#define RCC_USART234578CLKSOURCE_CSI    RCC_CCIPR2_UART234578SEL_2   /*!< CSI selection */
#define RCC_USART234578CLKSOURCE_LSE    (RCC_CCIPR2_UART234578SEL_2 | RCC_CCIPR2_UART234578SEL_0)  /*!< LSE selection */
/**
  * @}
  */

/** @defgroup RCCEx_USB_PHYC_Clock_Source  USB PHYC Clock Source
  * @{
  */
#define RCC_USBPHYCCLKSOURCE_HSE       0U                        /*!< HSE selection (default) */
#define RCC_USBPHYCCLKSOURCE_HSE_DIV2  RCC_CCIPR1_USBPHYCSEL_0 /*!< HSE div 2 selection */
#define RCC_USBPHYCCLKSOURCE_PLL3Q     RCC_CCIPR1_USBPHYCSEL_1 /*!< PLL3 'Q' output selection */
/**
  * @}
  */

/** @defgroup RCCEx_USB_OTGFS_Clock_Source  USB OTG FS Clock Source
  * @{
  */
#define RCC_USBOTGFSCLKSOURCE_HSI48    0U                      /*!< HSI48 selection (default) */
#define RCC_USBOTGFSCLKSOURCE_PLL3Q    RCC_CCIPR1_OTGFSSEL_0 /*!< PLL3 'Q' output selection */
#define RCC_USBOTGFSCLKSOURCE_HSE      RCC_CCIPR1_OTGFSSEL_1 /*!< HSE selection */
#define RCC_USBOTGFSCLKSOURCE_CLK48    RCC_CCIPR1_OTGFSSEL   /*!< USBPHYC CLK48 output selection */
/**
  * @}
  */

/** @defgroup RCCEx_Clock_Protection  Clock Protection
  * @{
  */
#define RCC_CLOCKPROTECT_XSPI          RCC_CKPROTR_XSPICKP        /*!< XSPIs clock protection */
#define RCC_CLOCKPROTECT_FMC           RCC_CKPROTR_FMCCKP      /*!< FMC clock protection */
/**
  * @}
  */


/** @defgroup RCCEx_EXTI_LINE_LSECSS  LSE CSS external interrupt line
  * @{
  */
#define RCC_EXTI_LINE_LSECSS           EXTI_IMR1_IM18        /*!< External interrupt line 18 connected to the LSE CSS EXTI Line */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Status  CRS Status
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

/** @defgroup RCCEx_CRS_SynchroSource CRS SynchroSource
  * @{
  */
#define RCC_CRS_SYNC_SOURCE_GPIO          0U                                      /*!< Synchro Signal source GPIO */
#define RCC_CRS_SYNC_SOURCE_LSE          CRS_CFGR_SYNCSRC_0                      /*!< Synchro Signal source LSE */
#define RCC_CRS_SYNC_SOURCE_USB_OTG_FS   CRS_CFGR_SYNCSRC_1                      /*!< Synchro Signal source USB OTG FS SOF (default) */
#define RCC_CRS_SYNC_SOURCE_USB_OTG_HS   (CRS_CFGR_SYNCSRC_1|CRS_CFGR_SYNCSRC_0) /*!< Synchro Signal source USB OTG HS SOF */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroDivider CRS SynchroDivider
  * @{
  */
#define RCC_CRS_SYNC_DIV1              0U                                        /*!< Synchro Signal not divided (default) */
#define RCC_CRS_SYNC_DIV2              CRS_CFGR_SYNCDIV_0                        /*!< Synchro Signal divided by 2 */
#define RCC_CRS_SYNC_DIV4              CRS_CFGR_SYNCDIV_1                        /*!< Synchro Signal divided by 4 */
#define RCC_CRS_SYNC_DIV8              (CRS_CFGR_SYNCDIV_1 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 8 */
#define RCC_CRS_SYNC_DIV16             CRS_CFGR_SYNCDIV_2                        /*!< Synchro Signal divided by 16 */
#define RCC_CRS_SYNC_DIV32             (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 32 */
#define RCC_CRS_SYNC_DIV64             (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_1) /*!< Synchro Signal divided by 64 */
#define RCC_CRS_SYNC_DIV128            CRS_CFGR_SYNCDIV                          /*!< Synchro Signal divided by 128 */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroPolarity CRS SynchroPolarity
  * @{
  */
#define RCC_CRS_SYNC_POLARITY_RISING   0U                      /*!< Synchro Active on rising edge (default) */
#define RCC_CRS_SYNC_POLARITY_FALLING  CRS_CFGR_SYNCPOL        /*!< Synchro Active on falling edge */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ReloadValueDefault CRS ReloadValueDefault
  * @{
  */
#define RCC_CRS_RELOADVALUE_DEFAULT    0x0000BB7FU         /*!< The reset value of the RELOAD field corresponds
                                                                to a target frequency of 48 MHz and a synchronization signal frequency of 1 kHz (SOF signal from USB). */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_ErrorLimitDefault CRS ErrorLimitDefault
  * @{
  */
#define RCC_CRS_ERRORLIMIT_DEFAULT     0x00000022U         /*!< Default Frequency error limit */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_HSI48CalibrationDefault CRS HSI48CalibrationDefault
  * @{
  */
#define RCC_CRS_HSI48CALIBRATION_DEFAULT 0x00000020U       /*!< The default value is 32, which corresponds to the middle of the trimming interval.
                                                                The trimming step is specified in the product datasheet. A higher TRIM value corresponds
                                                                to a higher output frequency */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_FreqErrorDirection CRS FreqErrorDirection
  * @{
  */
#define RCC_CRS_FREQERRORDIR_UP        0U                  /*!< Upcounting direction, the actual frequency is above the target */
#define RCC_CRS_FREQERRORDIR_DOWN      CRS_ISR_FEDIR       /*!< Downcounting direction, the actual frequency is below the target */
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Interrupt_Sources CRS Interrupt Sources
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

/** @defgroup RCCEx_CRS_Flags CRS Flags
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

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */

/** @brief  Macro to configure the ADC clock
  * @param  __ADC_CLKSOURCE__ specifies the ADC digital interface clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_ADCCLKSOURCE_PLL2P  PLL2_P Clock selected as ADC clock
  *            @arg RCC_ADCCLKSOURCE_PLL3R  PLL3_R Clock selected as ADC clock
  *            @arg RCC_ADCCLKSOURCE_CLKP   CLKP Clock selected as ADC clock
  */
#define __HAL_RCC_ADC_CONFIG(__ADC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ADCSEL, (uint32_t)(__ADC_CLKSOURCE__))

/** @brief  Macro to get the ADC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADCCLKSOURCE_PLL2P  PLL2_P Clock selected as ADC clock
  *            @arg RCC_ADCCLKSOURCE_PLL3R  PLL3_R Clock selected as ADC clock
  *            @arg RCC_ADCCLKSOURCE_CLKP   CLKP Clock selected as ADC clock
  */
#define __HAL_RCC_GET_ADC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ADCSEL)))

/** @brief  Macro to configure the ADF1 clock
  * @param  __ADF1_CLKSOURCE__ specifies the ADF1  clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_ADF1CLKSOURCE_HCLK   HCLK Clock selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_PLL2P  PLL2_P Clock selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_PLL3P  PLL3_P Clock selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_PIN    External I2S_CKIN selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_CSI    CSI selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_HSI    HSI selected as ADF1 clock
  */
#define __HAL_RCC_ADF1_CONFIG(__ADF1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ADF1SEL, (uint32_t)(__ADF1_CLKSOURCE__))

/** @brief  Macro to get the ADF1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADF1CLKSOURCE_HCLK   HCLK Clock selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_PLL2P  PLL2_P Clock selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_PLL3P  PLL3_P Clock selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_PIN    External I2S_CKIN selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_CSI    CSI selected as ADF1 clock
  *            @arg RCC_ADF1CLKSOURCE_HSI    HSI selected as ADF1 clock
  */
#define __HAL_RCC_GET_ADF1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ADF1SEL)))

/** @brief  Macro to configure the HDMI-CEC clock source.
  * @param  __CEC_CLKSOURCE__ specifies the CEC clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_CECCLKSOURCE_LSE  LSE selected as CEC clock
  *            @arg RCC_CECCLKSOURCE_LSI  LSI selected as CEC clock
  *            @arg RCC_CECCLKSOURCE_CSI  CSI divided by 122 selected as CEC clock
  */
#define __HAL_RCC_CEC_CONFIG(__CEC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_CECSEL, (uint32_t)(__CEC_CLKSOURCE__))

/** @brief  Macro to get the HDMI-CEC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_CECCLKSOURCE_LSE  LSE selected as CEC clock
  *            @arg RCC_CECCLKSOURCE_LSI  LSI selected as CEC clock
  *            @arg RCC_CECCLKSOURCE_CSI  CSI divided by 122 selected as CEC clock
  */
#define __HAL_RCC_GET_CEC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_CECSEL)))

/** @brief  Macro to configure the CLKP : Oscillator clock for peripheral
  * @param  __CLKP_CLKSOURCE__ specifies Oscillator clock for peripheral
  *         This parameter can be one of the following values:
  *            @arg RCC_CLKPSOURCE_HSI  HSI selected as peripheral clock (default)
  *            @arg RCC_CLKPSOURCE_CSI  CSI selected as peripheral clock
  *            @arg RCC_CLKPSOURCE_HSE  HSE selected as peripheral clock
  */
#define __HAL_RCC_CLKP_CONFIG(__CLKP_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_CKPERSEL, (uint32_t)(__CLKP_CLKSOURCE__))

/** @brief  Macro to get the Oscillator clock for peripheral source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_CLKPSOURCE_HSI  HSI selected as peripheral clock (default)
  *            @arg RCC_CLKPSOURCE_CSI  CSI selected as peripheral clock
  *            @arg RCC_CLKPSOURCE_HSE  HSE selected as peripheral clock
  */
#define __HAL_RCC_GET_CLKP_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_CKPERSEL)))

/** @brief  Macro to configure the ETH1 REF clock source.
  * @param  __ETH1REF_CLKSOURCE__ specifies  clock source for ETH1 REF
  *         This parameter can be one of the following values:
  *            @arg RCC_ETH1REFCLKSOURCE_PHY      ETH PHY selected as ETH1 REF clock (default)
  *            @arg RCC_ETH1REFCLKSOURCE_HSE      HSE selected as ETH1 clock
  *            @arg RCC_ETH1REFCLKSOURCE_ETH      ETH feedback selected as ETH1 REF clock
  */
#define __HAL_RCC_ETH1REF_CONFIG(__ETH1REF_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ETH1REFCKSEL, (uint32_t)(__ETH1REF_CLKSOURCE__))

/** @brief  Macro to get the ETH1 REF clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ETH1REFCLKSOURCE_PHY      ETH PHY selected as ETH1 clock (default)
  *            @arg RCC_ETH1REFCLKSOURCE_HSE      HSE selected as ETH1 clock
  *            @arg RCC_ETH1REFCLKSOURCE_ETH      ETH feedback selected as ETH1 clock
  */
#define __HAL_RCC_GET_ETH1REF_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ETH1REFCKSEL)))

/** @brief  Macro to configure the ETH1 PHY clock source.
  * @param  __ETH1PHY_CLKSOURCE__ specifies  clock source for ETH PHY
  *         This parameter can be one of the following values:
  *            @arg RCC_ETH1PHYCLKSOURCE_HSE    HSE selected as ETH PHY clock (default)
  *            @arg RCC_ETH1PHYCLKSOURCE_PLL3S  PLL3_S selected as ETH PHY clock
  */
#define __HAL_RCC_ETH1PHY_CONFIG(__ETH1PHY_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ETH1PHYCKSEL, (uint32_t)(__ETH1PHY_CLKSOURCE__))

/** @brief  Macro to get the ETH1 PHY clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ETH1PHYCLKSOURCE_HSE    HSE selected as ETH PHY clock (default)
  *            @arg RCC_ETH1PHYCLKSOURCE_PLL3S  PLL3_S selected as ETH PHY clock
  */
#define __HAL_RCC_GET_ETH1PHY_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ETH1PHYCKSEL)))

/** @brief  Macro to configure the FDCAN kernel clock source.
  * @param  __FDCAN_CLKSOURCE__ specifies  clock source for FDCAN kernel
  *         This parameter can be one of the following values:
  *            @arg RCC_FDCANCLKSOURCE_HSE    HSE selected as FDCAN kernel clock (default)
  *            @arg RCC_FDCANCLKSOURCE_PLL1Q  PLL1_Q selected as FDCAN kernel clock
  *            @arg RCC_FDCANCLKSOURCE_PLL2P  PLL2_P selected as FDCAN kernel clock
  */
#define __HAL_RCC_FDCAN_CONFIG(__FDCAN_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_FDCANSEL, (uint32_t)(__FDCAN_CLKSOURCE__))

/** @brief  Macro to get the FDCAN kernel clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_FDCANCLKSOURCE_HSE    HSE selected as FDCAN kernel clock (default)
  *            @arg RCC_FDCANCLKSOURCE_PLL1Q  PLL1_Q selected as FDCAN kernel clock
  *            @arg RCC_FDCANCLKSOURCE_PLL2P  PLL2_P selected as FDCAN kernel clock
  */
#define __HAL_RCC_GET_FDCAN_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_FDCANSEL)))

/** @brief  Macro to configure the FMC clock source.
  *
  * @param  __FMC_CLKSOURCE__ specifies the FMC clock source.
  *            @arg RCC_FMCCLKSOURCE_HCLK  HCLK Clock selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_PLL1Q PLL1_Q Clock selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_PLL2R PLL2_R Clock selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_HSI   HSI selected as FMC clock
  */
#define __HAL_RCC_FMC_CONFIG(__FMC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_FMCSEL, (uint32_t)(__FMC_CLKSOURCE__))

/** @brief  Macro to get the FMC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_FMCCLKSOURCE_HCLK      HCLK Clock selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_PLL1Q     PLL1_Q Clock selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_PLL2R     PLL2_R Clock selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_HSI       HSI selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_HCLK_DIV4 Recovery Clock selected as FMC clock
  */
#define __HAL_RCC_GET_FMC_SOURCE() ((READ_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCSWP) == RCC_FMCCLKSOURCE_HCLK_DIV4) ? \
                                    RCC_FMCCLKSOURCE_HCLK_DIV4 : ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_FMCSEL))))

/** @brief  Macro to configure the I2C1/I3C1 clock source.
  * @param  __I2C1_I3C1_CLKSOURCE__ specifies the I2C1/I3C1clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2C1_I3C1CLKSOURCE_PCLK1  APB1 selected as I2C1/I3C1clock
  *            @arg RCC_I2C1_I3C1CLKSOURCE_PLL3R  PLL3_R selected as I2C1/I3C1clock
  *            @arg RCC_I2C1_I3C1CLKSOURCE_HSI    HSI selected as I2C1/I3C1clock
  *            @arg RCC_I2C1_I3C1CLKSOURCE_CSI    CSI selected as I2C1/I3C1clock
  */
#define __HAL_RCC_I2C1_I3C1_CONFIG(__I2C1_I3C1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2C1_I3C1SEL, (uint32_t)(__I2C1_I3C1_CLKSOURCE__))

/** @brief  Macro to get the I2C1/I3C1clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C1_I3C1CLKSOURCE_PCLK1  APB1 selected as I2C1/I3C1clock
  *            @arg RCC_I2C1_I3C1CLKSOURCE_PLL3R  PLL3_R selected as I2C1/I3C1clock
  *            @arg RCC_I2C1_I3C1CLKSOURCE_HSI    HSI selected as I2C1/I3C1clock
  *            @arg RCC_I2C1_I3C1CLKSOURCE_CSI    CSI selected as I2C1/I3C1clock
  */
#define __HAL_RCC_GET_I2C1_I3C1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2C1_I3C1SEL)))

/** @brief  Macro to configure the I2C2/I2C3 clock source.
  * @param  __I2C23_CLKSOURCE__ specifies the I2C2/I2C3 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2C23CLKSOURCE_PCLK1  APB1 selected as I2C2/I2C3 clock
  *            @arg RCC_I2C23CLKSOURCE_PLL3R  PLL3_R selected as I2C2/I2C3 clock
  *            @arg RCC_I2C23CLKSOURCE_HSI    HSI selected as I2C2/I2C3 clock
  *            @arg RCC_I2C23CLKSOURCE_CSI    CSI selected as I2C2/I2C3 clock
  */
#define __HAL_RCC_I2C23_CONFIG(__I2C23_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2C23SEL, (uint32_t)(__I2C23_CLKSOURCE__))

/** @brief  Macro to get the I2C2/I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C23CLKSOURCE_PCLK1  APB1 selected as I2C2/I2C3 clock
  *            @arg RCC_I2C23CLKSOURCE_PLL3R  PLL3_R selected as I2C2/I2C3 clock
  *            @arg RCC_I2C23CLKSOURCE_HSI    HSI selected as I2C2/I2C3 clock
  *            @arg RCC_I2C23CLKSOURCE_CSI    CSI selected as I2C2/I2C3 clock
  */
#define __HAL_RCC_GET_I2C23_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2C23SEL)))

/** @brief  Macro to configure the I3C1 clock source.
  * @param  __I3C1_CLKSOURCE__ specifies the I3C1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I3C1CLKSOURCE_PCLK1  APB1 selected as I3C1 clock
  *            @arg RCC_I3C1CLKSOURCE_PLL3R  PLL3_R selected as I3C1 clock
  *            @arg RCC_I3C1CLKSOURCE_HSI    HSI selected as I3C1 clock
  *            @arg RCC_I3C1CLKSOURCE_CSI    CSI selected as I3C1 clock
  */
#define __HAL_RCC_I3C1_CONFIG(__I3C1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2C1_I3C1SEL, (uint32_t)(__I3C1_CLKSOURCE__))

/** @brief  Macro to get the I3C1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I3C1CLKSOURCE_PCLK1  APB1 selected as I3C1 clock
  *            @arg RCC_I3C1CLKSOURCE_PLL3R  PLL3_R selected as I3C1 clock
  *            @arg RCC_I3C1CLKSOURCE_HSI    HSI selected as I3C1 clock
  *            @arg RCC_I3C1CLKSOURCE_CSI    CSI selected as I3C1 clock
  */
#define __HAL_RCC_GET_I3C1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2C1_I3C1SEL)))

/** @brief  Macro to configure the LPTIM1 clock source.
  * @param  __LPTIM1_CLKSOURCE__ specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPTIM1CLKSOURCE_PCLK1  APB1 clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_PLL2P  PLL2_P selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_PLL3R  PLL3_R selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_LSE    LSE selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_LSI    LSI Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_CLKP   CLKP selected as LPTIM1 clock
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_LPTIM1SEL, (uint32_t)(__LPTIM1_CLKSOURCE__))

/** @brief  Macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPTIM1CLKSOURCE_PCLK1  APB1 clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_PLL2P  PLL2_P selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_PLL3R  PLL3_R selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_LSE    LSE selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_LSI    LSI Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_CLKP   CLKP selected as LPTIM1 clock
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_LPTIM1SEL)))

/** @brief  Macro to configure the LPTIM2/LPTIM3 clock source.
  * @param  __LPTIM23_CLKSOURCE__ specifies the LPTIM2/LPTIM3 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPTIM23CLKSOURCE_PCLK4  APB4 clock selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_PLL2P  PLL2_P selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_PLL3R  PLL3_R selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_LSE    LSE selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_LSI    LSI Clock selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_CLKP   CLKP selected as LPTIM2/LPTIM3 clock
  */
#define __HAL_RCC_LPTIM23_CONFIG(__LPTIM23_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_LPTIM23SEL, (uint32_t)(__LPTIM23_CLKSOURCE__))

/** @brief  Macro to get the LPTIM2/LPTIM3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPTIM23CLKSOURCE_PCLK4  APB4 clock selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_PLL2P  PLL2_P selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_PLL3R  PLL3_R selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_LSE    LSE selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_LSI    LSI Clock selected as LPTIM2/LPTIM3 clock
  *            @arg RCC_LPTIM23CLKSOURCE_CLKP   CLKP selected as LPTIM2/LPTIM3 clock
  */
#define __HAL_RCC_GET_LPTIM23_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR4, RCC_CCIPR4_LPTIM23SEL)))

/** @brief  Macro to configure the LPTIM4/LPTIM5 clock source.
  * @param  __LPTIM45_CLKSOURCE__ specifies the LPTIM4/LPTIM5 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPTIM45CLKSOURCE_PCLK4  APB4 clock selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_PLL2P  PLL2_P selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_PLL3R  PLL3_R selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_LSE    LSE selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_LSI    LSI Clock selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_CLKP   CLKP selected as LPTIM4/LPTIM5 clock
  */
#define __HAL_RCC_LPTIM45_CONFIG(__LPTIM45_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_LPTIM45SEL, (uint32_t)(__LPTIM45_CLKSOURCE__))

/** @brief  Macro to get the LPTIM4/LPTIM5 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPTIM45CLKSOURCE_PCLK4  APB4 clock selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_PLL2P  PLL2_P selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_PLL3R  PLL3_R selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_LSE    LSE selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_LSI    LSI Clock selected as LPTIM4/LPTIM5 clock
  *            @arg RCC_LPTIM45CLKSOURCE_CLKP   CLKP selected as LPTIM4/LPTIM5 clock
  */
#define __HAL_RCC_GET_LPTIM45_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR4, RCC_CCIPR4_LPTIM45SEL)))

/** @brief  Macro to configure the LPUART1 clock (LPUART1CLK).
  * @param  __LPUART1_CLKSOURCE__ specifies the LPUART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPUART1CLKSOURCE_PCLK4  APB4 Clock selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_PLL2Q  PLL2_Q Clock selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_PLL3Q  PLL3_Q Clock selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_HSI    HSI selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_CSI    CSI Clock selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_LSE    LSE selected as LPUART1 clock
  */
#define __HAL_RCC_LPUART1_CONFIG(__LPUART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_LPUART1SEL, (uint32_t)(__LPUART1_CLKSOURCE__))

/** @brief  Macro to get the LPUART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPUART1CLKSOURCE_PCLK4  APB4 Clock selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_PLL2Q  PLL2_Q Clock selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_PLL3Q  PLL3_Q Clock selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_HSI    HSI selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_CSI    CSI Clock selected as LPUART1 clock
  *            @arg RCC_LPUART1CLKSOURCE_LSE    LSE selected as LPUART1 clock
  */
#define __HAL_RCC_GET_LPUART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR4, RCC_CCIPR4_LPUART1SEL)))

/** @brief  Macro to get the LTDC clock source.
  * @retval The clock source is internally connected to:
  *            @arg RCC_LTDCCLKSOURCE_PLL3R     PLL3_R Clock selected as LTDC clock
  */
#define __HAL_RCC_GET_LTDC_SOURCE() RCC_LTDCCLKSOURCE_PLL3R

/** @brief  Macro to configure the XSPI1 clock source.
  *
  * @param  __XSPI1_CLKSOURCE__ specifies the XSPI1 clock source.
  *            @arg RCC_XSPI1CLKSOURCE_HCLK  HCLK Clock selected as XSPI1 clock
  *            @arg RCC_XSPI1CLKSOURCE_PLL2S PLL2_S Clock selected as XSPI1 clock
  *            @arg RCC_XSPI1CLKSOURCE_PLL2T PLL2_T Clock selected as XSPI1 clock
  */
#define __HAL_RCC_XSPI1_CONFIG(__XSPI1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_XSPI1SEL, (uint32_t)(__XSPI1_CLKSOURCE__))

/** @brief  Macro to get the XSPI1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_XSPI1CLKSOURCE_HCLK  HCLK Clock selected as XSPI1 clock
  *            @arg RCC_XSPI1CLKSOURCE_PLL2S PLL2_S Clock selected as XSPI1 clock
  *            @arg RCC_XSPI1CLKSOURCE_PLL2T PLL2_T Clock selected as XSPI1 clock
  *            @arg RCC_XSPI1CLKSOURCE_HCLK_DIV4 Recovery Clock selected as XSPI1 clock
  */
#define __HAL_RCC_GET_XSPI1_SOURCE() ((READ_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPI1SWP) == RCC_XSPI1CLKSOURCE_HCLK_DIV4) ? \
                                      RCC_XSPI1CLKSOURCE_HCLK_DIV4 : ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_XSPI1SEL))))

/** @brief  Macro to configure the XSPI2 clock source.
  *
  * @param  __XSPI2_CLKSOURCE__ specifies the XSPI2 clock source.
  *            @arg RCC_XSPI2CLKSOURCE_HCLK  HCLK Clock selected as XSPI2 clock
  *            @arg RCC_XSPI2CLKSOURCE_PLL2S PLL2_S Clock selected as XSPI2 clock
  *            @arg RCC_XSPI2CLKSOURCE_PLL2T PLL2_T Clock selected as XSPI2 clock
  */
#define __HAL_RCC_XSPI2_CONFIG(__XSPI2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_XSPI2SEL, (uint32_t)(__XSPI2_CLKSOURCE__))

/** @brief  Macro to get the XSPI2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_XSPI2CLKSOURCE_HCLK  HCLK Clock selected as XSPI2 clock
  *            @arg RCC_XSPI2CLKSOURCE_PLL2S PLL2_S Clock selected as XSPI2 clock
  *            @arg RCC_XSPI2CLKSOURCE_PLL2T PLL2_T Clock selected as XSPI2 clock
  *            @arg RCC_XSPI2CLKSOURCE_HCLK_DIV4 Recovery Clock selected as XSPI2 clock
  */
#define __HAL_RCC_GET_XSPI2_SOURCE() ((READ_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPI2SWP) == RCC_XSPI2CLKSOURCE_HCLK_DIV4) ? \
                                      RCC_XSPI2CLKSOURCE_HCLK_DIV4 : ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_XSPI2SEL))))

/**
  * @brief  Macro to configure the PSSI clock source.
  * @param  __PSSI_CLKSOURCE__ defines the PSSI clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_PSSICLKSOURCE_PLL3R  PLL3_R selected as PSSI clock
  *             @arg RCC_PSSICLKSOURCE_CLKP   Peripheral clock selected as PSSI clock
  * @retval None
  */
#define __HAL_RCC_PSSI_CONFIG(__PSSI_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_PSSISEL, (__PSSI_CLKSOURCE__))

/** @brief  Macro to get the PSSI clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_PSSICLKSOURCE_PLL3R  PLL3_R selected as PSSI clock
  *             @arg RCC_PSSICLKSOURCE_CLKP   Peripheral clock selected as PSSI clock
  */
#define __HAL_RCC_GET_PSSI_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_PSSISEL)))

/**
  * @brief  Macro to configure the SAI1 clock source.
  * @param  __SAI1_CLKSOURCE__ defines the SAI1 clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SAI1CLKSOURCE_PLL1Q  PLL1_Q selected as SAI1 clock
  *             @arg RCC_SAI1CLKSOURCE_PLL2P  PLL2_P selected as SAI1 clock
  *             @arg RCC_SAI1CLKSOURCE_PLL3P  PLL3_P selected as SAI1 clock
  *             @arg RCC_SAI1CLKSOURCE_PIN    External I2S_CKIN selected as SAI1 clock
  *             @arg RCC_SAI1CLKSOURCE_CLKP   Peripheral clock selected as SAI1 clock
  * @retval None
  */
#define __HAL_RCC_SAI1_CONFIG(__SAI1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_SAI1SEL, (__SAI1_CLKSOURCE__))

/** @brief  Macro to get the SAI1 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SAI1CLKSOURCE_PLL1Q  PLL1_Q selected as SAI1 clock
  *             @arg RCC_SAI1CLKSOURCE_PLL2P  PLL2_P selected as SAI1 clock
  *             @arg RCC_SAI1CLKSOURCE_PLL3P  PLL3_P selected as SAI1 clock
  *             @arg RCC_SAI1CLKSOURCE_PIN    External I2S_CKIN selected as SAI1 clock
  *             @arg RCC_SAI1CLKSOURCE_CLKP   Peripheral clock selected as SAI1 clock
  */
#define __HAL_RCC_GET_SAI1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_SAI1SEL)))

/**
  * @brief  Macro to configure the SAI2 clock source.
  * @param  __SAI2_CLKSOURCE__ defines the SAI2 clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SAI2CLKSOURCE_PLL1Q  PLL1_Q selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_PLL2P  PLL2_P selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_PLL3P  PLL3_P selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_PIN    External I2S_CKIN selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_CLKP   Peripheral clock selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_SPDIF  SPDIF output clock selected as SAI2 clock
  * @retval None
  */
#define __HAL_RCC_SAI2_CONFIG(__SAI2_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_SAI2SEL, (__SAI2_CLKSOURCE__))

/** @brief  Macro to get the SAI2 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SAI2CLKSOURCE_PLL1Q  PLL1_Q selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_PLL2P  PLL2_P selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_PLL3P  PLL3_P selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_PIN    External I2S_CKIN selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_CLKP   Peripheral clock selected as SAI2 clock
  *             @arg RCC_SAI2CLKSOURCE_SPDIF  SPDIF output clock selected as SAI2 clock
  */
#define __HAL_RCC_GET_SAI2_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_SAI2SEL)))


/** @brief  Macro to configure the SDMMC kernel clock source.
  * @param  __SDMMC12_CLKSOURCE__ specifies  clock source  for SDMMC
  *        This parameter can be one of the following values:
  *            @arg RCC_SDMMC12CLKSOURCE_PLL2S  PLL2_S selected as SDMMC kernel clock
  *            @arg RCC_SDMMC12CLKSOURCE_PLL2T  PLL2_R selected as SDMMC kernel clock
  */
#define __HAL_RCC_SDMMC12_CONFIG(__SDMMC12_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SDMMC12SEL, (uint32_t)(__SDMMC12_CLKSOURCE__))

/** @brief  Macro to get the SDMMC kernel clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SDMMC12CLKSOURCE_PLL2S  PLL2_S selected as SDMMC12 kernel clock
  *            @arg RCC_SDMMC12CLKSOURCE_PLL2T  PLL2_R selected as SDMMC12 kernel clock
  */
#define __HAL_RCC_GET_SDMMC12_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SDMMC12SEL)))

/**
  * @brief  Macro to Configure the SPDIFRX clock source.
  * @param  __SPDIFRX_CLKSOURCE__ defines the SPDIFRX clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SPDIFRXCLKSOURCE_PLL1Q  PLL1_Q selected as SPDIFRX clock
  *             @arg RCC_SPDIFRXCLKSOURCE_PLL2R  PLL2_R selected as SPDIFRX clock
  *             @arg RCC_SPDIFRXCLKSOURCE_PLL3R  PLL3_R selected as SPDIFRX clock
  *             @arg RCC_SPDIFRXCLKSOURCE_HSI    HSI selected as SPDIFRX clock
  * @retval None
  */
#define __HAL_RCC_SPDIFRX_CONFIG(__SPDIFRX_CLKSOURCE__ ) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SPDIFRXSEL, (__SPDIFRX_CLKSOURCE__))

/**
  * @brief  Macro to get the SPDIFRX clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SPDIFRXCLKSOURCE_PLL1Q  PLL1_Q selected as SPDIFRX clock
  *             @arg RCC_SPDIFRXCLKSOURCE_PLL2R  PLL2_R selected as SPDIFRX clock
  *             @arg RCC_SPDIFRXCLKSOURCE_PLL3R  PLL3_R selected as SPDIFRX clock
  *             @arg RCC_SPDIFRXCLKSOURCE_HSI    HSI selected as SPDIFRX clock
  * @retval None
  */
#define __HAL_RCC_GET_SPDIFRX_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SPDIFRXSEL)))

/**
  * @brief  Macro to configure the SPI1 clock source.
  * @param  __SPI1_CLKSOURCE__ defines the SPI1 clock source.
  *         This parameter can be one of the following values:
  *             @arg RCC_SPI1CLKSOURCE_PLL1Q  PLL1_Q selected as SPI1 clock
  *             @arg RCC_SPI1CLKSOURCE_PLL2P  PLL2_P selected as SPI1 clock
  *             @arg RCC_SPI1CLKSOURCE_PLL3P  PLL3_P selected as SPI1 clock
  *             @arg RCC_SPI1CLKSOURCE_PIN    External I2S_CKIN selected as SPI1 clock
  *             @arg RCC_SPI1CLKSOURCE_CLKP   Peripheral clock selected as SPI1 clock
  * @retval None
  */
#define __HAL_RCC_SPI1_CONFIG(__SPI1_CLKSOURCE__ ) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_SPI1SEL, (__SPI1_CLKSOURCE__))

/** @brief  Macro to get the SPI1 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SPI1CLKSOURCE_PLL1Q  PLL1_Q selected as SPI1 clock
  *             @arg RCC_SPI1CLKSOURCE_PLL2P  PLL2_P selected as SPI1 clock
  *             @arg RCC_SPI1CLKSOURCE_PLL3P  PLL3_P selected as SPI1 clock
  *             @arg RCC_SPI1CLKSOURCE_PIN    External I2S_CKIN selected as SPI1 clock
  *             @arg RCC_SPI1CLKSOURCE_CLKP   Peripheral clock selected as SPI1 clock
  */
#define __HAL_RCC_GET_SPI1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_SPI1SEL)))

/**
  * @brief  Macro to configure the SPI2/SPI3 clock source.
  * @param  __SPI23_CLKSOURCE__ defines the SPI2/SPI3 clock source.
  *         This parameter can be one of the following values:
  *             @arg RCC_SPI23CLKSOURCE_PLL1Q  PLL1_Q selected as SPI2/SPI3 clock
  *             @arg RCC_SPI23CLKSOURCE_PLL2P  PLL2_P selected as SPI2/SPI3 clock
  *             @arg RCC_SPI23CLKSOURCE_PLL3P  PLL3_P selected as SPI2/SPI3 clock
  *             @arg RCC_SPI23CLKSOURCE_PIN    External I2S_CKIN selected as SPI2/SPI3 clock
  *             @arg RCC_SPI23CLKSOURCE_CLKP   Peripheral clock selected as SPI2/SPI3 clock
  * @retval None
  */
#define __HAL_RCC_SPI23_CONFIG(__SPI23_CLKSOURCE__ ) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SPI23SEL, (__SPI23_CLKSOURCE__))

/** @brief  Macro to get the SPI2/SPI3 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SPI23CLKSOURCE_PLL1Q  PLL1_Q selected as SPI2/SPI3 clock
  *             @arg RCC_SPI23CLKSOURCE_PLL2P  PLL2_P selected as SPI2/SPI3 clock
  *             @arg RCC_SPI23CLKSOURCE_PLL3P  PLL3_P selected as SPI2/SPI3 clock
  *             @arg RCC_SPI23CLKSOURCE_PIN    External I2S_CKIN selected as SPI2/SPI3 clock
  *             @arg RCC_SPI23CLKSOURCE_CLKP   Peripheral clock selected as SPI2/SPI3 clock
  */
#define __HAL_RCC_GET_SPI23_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SPI23SEL)))

/**
  * @brief  Macro to configure the SPI4/SPI5 clock source.
  * @param  __SPI45_CLKSOURCE__ defines the SPI4/SPI5 clock source.
  *         This parameter can be one of the following values:
  *             @arg RCC_SPI45CLKSOURCE_PCLK2  APB2 Clock selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_PLL2Q  PLL2_Q selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_PLL3Q  PLL3_Q selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_HSI    HSI selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_CSI    CSI selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_HSE    HSE selected as SPI4/SPI5 clock
  * @retval None
  */
#define __HAL_RCC_SPI45_CONFIG(__SPI45_CLKSOURCE__ ) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_SPI45SEL, (__SPI45_CLKSOURCE__))

/** @brief  Macro to get the SPI4/SPI5 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SPI45CLKSOURCE_PCLK2  APB2 Clock selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_PLL2Q  PLL2_Q selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_PLL3Q  PLL3_Q selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_HSI    HSI selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_CSI    CSI selected as SPI4/SPI5 clock
  *             @arg RCC_SPI45CLKSOURCE_HSE    HSE selected as SPI4/SPI5 clock
  */
#define __HAL_RCC_GET_SPI45_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_SPI45SEL)))

/**
  * @brief  Macro to configure the SPI6 clock source.
  * @param  __SPI6_CLKSOURCE__ defines the SPI6 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_SPI6CLKSOURCE_PCLK4  APB4 Clock selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_PLL2Q  PLL2_Q selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_PLL3Q  PLL3_Q selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_HSI    HSI selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_CSI    CSI selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_HSE    HSE selected as SPI6 clock
  * @retval None
  */
#define __HAL_RCC_SPI6_CONFIG(__SPI6_CLKSOURCE__ ) \
  MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_SPI6SEL, (__SPI6_CLKSOURCE__))

/** @brief  Macro to get the SPI6 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPI6CLKSOURCE_PCLK4  APB4 Clock selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_PLL2Q  PLL2_Q selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_PLL3Q  PLL3_Q selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_HSI    HSI selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_CSI    CSI selected as SPI6 clock
  *            @arg RCC_SPI6CLKSOURCE_HSE    HSE selected as SPI6 clock
  */
#define __HAL_RCC_GET_SPI6_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR4, RCC_CCIPR4_SPI6SEL)))

/** @brief  Macro to configure the USART1 clock source.
  * @param  __USART1_CLKSOURCE__ specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USART1CLKSOURCE_PCLK2  APB2 Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_PLL2Q  PLL2_Q selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_PLL3Q  PLL3_Q selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_HSI    HSI selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_CSI    CSI selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_LSE    LSE selected as USART1 clock
  */
#define __HAL_RCC_USART1_CONFIG(__USART1_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_USART1SEL, (uint32_t)(__USART1_CLKSOURCE__))

/** @brief  Macro to get the USART1/6/9* /10* clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART1CLKSOURCE_PCLK2  APB2 Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_PLL2Q  PLL2_Q selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_PLL3Q  PLL3_Q selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_HSI    HSI selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_CSI    CSI selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_LSE    LSE selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_USART1SEL)))

/** @brief  Macro to configure the USART2/USART3/UART4/UART5/UART7/UART8 clock source.
  * @param  __USART234578_CLKSOURCE__ specifies the USART2/UART3/UART4/UART5/UART7/UART8 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USART234578CLKSOURCE_PCLK1  APB1 Clock selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_PLL2Q  PLL2_Q Clock selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_PLL3Q  PLL3_Q Clock selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_HSI    HSI selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_CSI    CSI Clock selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_LSE    LSE selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  */
#define __HAL_RCC_USART234578_CONFIG(__USART234578_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_UART234578SEL, (uint32_t)(__USART234578_CLKSOURCE__))

/** @brief  Macro to get the USART2/USART3/UART4/UART5/UART7/UART8 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART234578CLKSOURCE_PCLK1  APB1 Clock selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_PLL2Q  PLL2_Q Clock selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_PLL3Q  PLL3_Q Clock selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_HSI    HSI selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_CSI    CSI Clock selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  *            @arg RCC_USART234578CLKSOURCE_LSE    LSE selected as USART2/USART3/UART4/UART5/UART7/UART8 clock
  */
#define __HAL_RCC_GET_USART234578_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_UART234578SEL)))

/** @brief  Macro to configure the Timers clocks prescalers
  * @param  __PRESC__  specifies the Timers clocks prescalers selection
  *         This parameter can be one of the following values:
  *            @arg RCC_TIMPRES_DISABLE
  *                 The timers kernel clock is equal to:
  *                   - PCLKx_freq, if PCLKx = RCC_APBx_DIV1
  *                   - 2*PCLKx_freq, otherwise (default after reset)
  *            @arg RCC_TIMPRES_ENABLE
  *                 The timers kernel clock is equal to:
  *                   - PCLKx_freq, if PCLKx = RCC_APBx_DIV1
  *                   - 2*PCLKx_freq, if PCLKx = RCC_APBx_DIV2
  *                   - 4*PCLKx_freq, otherwise
  */
#define __HAL_RCC_TIMCLKPRESCALER_CONFIG(__PRESC__) \
  MODIFY_REG(RCC->CFGR, RCC_CFGR_TIMPRE, (uint32_t)(__PRESC__))

/** @brief  Macro to get the Timers clocks prescalers
  * @retval The parameter can be one of the following values:
  *            @arg RCC_TIMPRES_DISABLE
  *                 The timers kernel clock is equal to:
  *                   - PCLKx_freq, if PCLKx = RCC_APBx_DIV1
  *                   - 2*PCLKx_freq, otherwise (default after reset)
  *            @arg RCC_TIMPRES_ENABLE
  *                 The timers kernel clock is equal to:
  *                   - PCLKx_freq, if PCLKx = RCC_APBx_DIV1
  *                   - 2*PCLKx_freq, if PCLKx = RCC_APBx_DIV2
  *                   - 4*PCLKx_freq, otherwise
  */
#define __HAL_RCC_GET_TIMCLKPRESCALER() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_TIMPRE)))

/** @brief  Macro to configure the USBPHYC clock.
  * @param  __USBPHYC_CLKSOURCE__ specifies the USBPHYC clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USBPHYCCLKSOURCE_HSE       HSE selected as USBPHYC clock
  *            @arg RCC_USBPHYCCLKSOURCE_HSE_DIV2  HSE divided by 2 selected as USBPHYC clock
  *            @arg RCC_USBPHYCCLKSOURCE_PLL3Q     PLL3_Q Clock selected as USBPHYC clock
  */
#define __HAL_RCC_USBPHYC_CONFIG(__USBPHYC_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USBPHYCSEL, (uint32_t)(__USBPHYC_CLKSOURCE__))

/** @brief  Macro to get the USBPHYC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USBPHYCCLKSOURCE_HSE       HSE selected as USBPHYC clock
  *            @arg RCC_USBPHYCCLKSOURCE_HSE_DIV2  HSE divided by 2 selected as USBPHYC clock
  *            @arg RCC_USBPHYCCLKSOURCE_PLL3Q     PLL3_Q Clock selected as USBPHYC clock
  */
#define __HAL_RCC_GET_USBPHYC_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USBPHYCSEL)))

/** @brief  Macro to configure the USB OTGFS clock.
  * @param  __USBOTGFS_CLKSOURCE__ specifies the USB OTGFS clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USBOTGFSCLKSOURCE_HSI48    HSI48 selected as USB OTGFS clock
  *            @arg RCC_USBOTGFSCLKSOURCE_PLL3Q    PLL3_Q Clock selected as USB OTGFS clock
  *            @arg RCC_USBOTGFSCLKSOURCE_HSE      HSI48 selected as USB OTGFS clock
  *            @arg RCC_USBOTGFSCLKSOURCE_CLK48    USBPHYC CLK48 output selected as USB OTGFS clock
  */
#define __HAL_RCC_USBOTGFS_CONFIG(__USBOTGFS_CLKSOURCE__) \
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_OTGFSSEL, (uint32_t)(__USBOTGFS_CLKSOURCE__))

/** @brief  Macro to get the USB OTGFS clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USBOTGFSCLKSOURCE_HSI48    HSI48 selected as USB OTGFS clock
  *            @arg RCC_USBOTGFSCLKSOURCE_PLL3Q    PLL3_Q Clock selected as USB OTGFS clock
  *            @arg RCC_USBOTGFSCLKSOURCE_HSE      HSI48 selected as USB OTGFS clock
  *            @arg RCC_USBOTGFSCLKSOURCE_CLK48    USBPHYC CLK48 output selected as USB OTGFS clock
  */
#define __HAL_RCC_GET_USBOTGFS_SOURCE() ((uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_OTGFSSEL)))

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
#define  RCC_CRS_IT_ERROR_MASK                 ((uint32_t)(RCC_CRS_IT_TRIMOVF |\
                                                           RCC_CRS_IT_SYNCERR | RCC_CRS_IT_SYNCMISS))

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
#define RCC_CRS_FLAG_ERROR_MASK                ((uint32_t)(RCC_CRS_FLAG_TRIMOVF |\
                                                           RCC_CRS_FLAG_SYNCERR | RCC_CRS_FLAG_SYNCMISS))

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

/** @defgroup RCCEx_CRS_Extended_Features CRS Extended Features
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
  *             of the synchronization source after pre-scaling. It is then decreased by one in order to
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
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);
void     HAL_RCCEx_EnableClockProtection(uint32_t ProtectClk);
void     HAL_RCCEx_DisableClockProtection(uint32_t ProtectClk);
/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */
void     HAL_RCCEx_WakeUpStopCLKConfig(uint32_t WakeUpClk);
void     HAL_RCCEx_KerWakeUpStopCLKConfig(uint32_t WakeUpClk);
void     HAL_RCCEx_EnableLSECSS(void);
void     HAL_RCCEx_DisableLSECSS(void);
void     HAL_RCCEx_EnableLSECSS_IT(void);
void     HAL_RCCEx_LSECSS_IRQHandler(void);
void     HAL_RCCEx_LSECSS_Callback(void);
/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group3
  * @{
  */
void     HAL_RCCEx_CRSConfig(const RCC_CRSInitTypeDef *pInit);
void     HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void);
void     HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo);
uint32_t HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout);
void     HAL_RCCEx_CRS_IRQHandler(void);
void     HAL_RCCEx_CRS_SyncOkCallback(void);
void     HAL_RCCEx_CRS_SyncWarnCallback(void);
void     HAL_RCCEx_CRS_ExpectedSyncCallback(void);
void     HAL_RCCEx_CRS_ErrorCallback(uint32_t Error);
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

/** @defgroup RCCEx_IS_RCC_Definitions Private macros to check input parameters
  * @{
  */

#define IS_RCC_PERIPHCLOCK(__SELECTION__)  \
  ((((__SELECTION__) & RCC_PERIPHCLK_FMC)         == RCC_PERIPHCLK_FMC)         || \
   (((__SELECTION__) & RCC_PERIPHCLK_XSPI1)       == RCC_PERIPHCLK_XSPI1)       || \
   (((__SELECTION__) & RCC_PERIPHCLK_XSPI2)       == RCC_PERIPHCLK_XSPI2)       || \
   (((__SELECTION__) & RCC_PERIPHCLK_CKPER)       == RCC_PERIPHCLK_CKPER)       || \
   (((__SELECTION__) & RCC_PERIPHCLK_ADC)         == RCC_PERIPHCLK_ADC)         || \
   (((__SELECTION__) & RCC_PERIPHCLK_ADF1)        == RCC_PERIPHCLK_ADF1)        || \
   (((__SELECTION__) & RCC_PERIPHCLK_CEC)         == RCC_PERIPHCLK_CEC)         || \
   (((__SELECTION__) & RCC_PERIPHCLK_ETH1REF)     == RCC_PERIPHCLK_ETH1REF)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_ETH1PHY)     == RCC_PERIPHCLK_ETH1PHY)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_FDCAN)       == RCC_PERIPHCLK_FDCAN)       || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2C1_I3C1)   == RCC_PERIPHCLK_I2C1_I3C1)   || \
   (((__SELECTION__) & RCC_PERIPHCLK_I2C23)       == RCC_PERIPHCLK_I2C23)       || \
   (((__SELECTION__) & RCC_PERIPHCLK_LPTIM1)      == RCC_PERIPHCLK_LPTIM1)      || \
   (((__SELECTION__) & RCC_PERIPHCLK_LPTIM23)     == RCC_PERIPHCLK_LPTIM23)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_LPTIM45)     == RCC_PERIPHCLK_LPTIM45)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_LPUART1)     == RCC_PERIPHCLK_LPUART1)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_LTDC)        == RCC_PERIPHCLK_LTDC)        || \
   (((__SELECTION__) & RCC_PERIPHCLK_PSSI)        == RCC_PERIPHCLK_PSSI)        || \
   (((__SELECTION__) & RCC_PERIPHCLK_RTC)         == RCC_PERIPHCLK_RTC)         || \
   (((__SELECTION__) & RCC_PERIPHCLK_SAI1)        == RCC_PERIPHCLK_SAI1)        || \
   (((__SELECTION__) & RCC_PERIPHCLK_SAI2)        == RCC_PERIPHCLK_SAI2)        || \
   (((__SELECTION__) & RCC_PERIPHCLK_SDMMC12)     == RCC_PERIPHCLK_SDMMC12)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_SPDIFRX)     == RCC_PERIPHCLK_SPDIFRX)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_SPI1)        == RCC_PERIPHCLK_SPI1)        || \
   (((__SELECTION__) & RCC_PERIPHCLK_SPI23)       == RCC_PERIPHCLK_SPI23)       || \
   (((__SELECTION__) & RCC_PERIPHCLK_SPI45)       == RCC_PERIPHCLK_SPI45)       || \
   (((__SELECTION__) & RCC_PERIPHCLK_SPI6)        == RCC_PERIPHCLK_SPI6)        || \
   (((__SELECTION__) & RCC_PERIPHCLK_TIM)         == RCC_PERIPHCLK_TIM)         || \
   (((__SELECTION__) & RCC_PERIPHCLK_USART1)      == RCC_PERIPHCLK_USART1)      || \
   (((__SELECTION__) & RCC_PERIPHCLK_USART234578) == RCC_PERIPHCLK_USART234578) || \
   (((__SELECTION__) & RCC_PERIPHCLK_USBPHYC)     == RCC_PERIPHCLK_USBPHYC)     || \
   (((__SELECTION__) & RCC_PERIPHCLK_USBOTGFS)    == RCC_PERIPHCLK_USBOTGFS))

#define IS_RCC_ADCCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_ADCCLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_ADCCLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_ADCCLKSOURCE_CLKP))

#define IS_RCC_ADF1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_ADF1CLKSOURCE_HCLK)  || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_PLL3P) || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_PIN)   || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_CSI)   || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_HSI))

#define IS_RCC_CECCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_CECCLKSOURCE_LSE) || \
   ((__SOURCE__) == RCC_CECCLKSOURCE_LSI) || \
   ((__SOURCE__) == RCC_CECCLKSOURCE_CSI))

#define IS_RCC_CKPERCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_CLKPSOURCE_HSI) || \
   ((__SOURCE__) == RCC_CLKPSOURCE_CSI) || \
   ((__SOURCE__) == RCC_CLKPSOURCE_HSE))

#define IS_RCC_ETH1REFCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_ETH1REFCLKSOURCE_PHY) || \
   ((__SOURCE__) == RCC_ETH1REFCLKSOURCE_HSE) || \
   ((__SOURCE__) == RCC_ETH1REFCLKSOURCE_ETH))

#define IS_RCC_ETH1PHYCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_ETH1PHYCLKSOURCE_HSE) || \
   ((__SOURCE__) == RCC_ETH1PHYCLKSOURCE_PLL3S))

#define IS_RCC_FDCANCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_FDCANCLKSOURCE_HSE)   || \
   ((__SOURCE__) == RCC_FDCANCLKSOURCE_PLL1Q) || \
   ((__SOURCE__) == RCC_FDCANCLKSOURCE_PLL2P))

#define IS_RCC_FMCCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_FMCCLKSOURCE_HCLK)  || \
   ((__SOURCE__) == RCC_FMCCLKSOURCE_PLL1Q) || \
   ((__SOURCE__) == RCC_FMCCLKSOURCE_PLL2R) || \
   ((__SOURCE__) == RCC_FMCCLKSOURCE_HSI))

#define IS_RCC_I2C1_I3C1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_I2C1_I3C1CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_I2C1_I3C1CLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_I2C1_I3C1CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_I2C1_I3C1CLKSOURCE_CSI))

#define IS_RCC_I2C23CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_I2C23CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_I2C23CLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_I2C23CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_I2C23CLKSOURCE_CSI))

#define IS_RCC_I3C1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_I3C1CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_I3C1CLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_I3C1CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_I3C1CLKSOURCE_CSI))

#define IS_RCC_LPTIM1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_LPTIM1CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSE)   || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSI)   || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_CLKP))

#define IS_RCC_LPTIM23CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_LPTIM23CLKSOURCE_PCLK4) || \
   ((__SOURCE__) == RCC_LPTIM23CLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_LPTIM23CLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_LPTIM23CLKSOURCE_LSE)   || \
   ((__SOURCE__) == RCC_LPTIM23CLKSOURCE_LSI)   || \
   ((__SOURCE__) == RCC_LPTIM23CLKSOURCE_CLKP))

#define IS_RCC_LPTIM45CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_LPTIM45CLKSOURCE_PCLK4) || \
   ((__SOURCE__) == RCC_LPTIM45CLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_LPTIM45CLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_LPTIM45CLKSOURCE_LSE)   || \
   ((__SOURCE__) == RCC_LPTIM45CLKSOURCE_LSI)   || \
   ((__SOURCE__) == RCC_LPTIM45CLKSOURCE_CLKP))

#define IS_RCC_LPUART1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_LPUART1CLKSOURCE_PCLK4) || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_PLL2Q) || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_PLL3Q) || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_CSI)   || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_LSE))

#define IS_RCC_LTDCCLKSOURCE(__SOURCE__) \
  ((__SOURCE__) == RCC_LTDCCLKSOURCE_PLL3R)

#define IS_RCC_XSPI1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_XSPI1CLKSOURCE_HCLK)  || \
   ((__SOURCE__) == RCC_XSPI1CLKSOURCE_PLL2S) || \
   ((__SOURCE__) == RCC_XSPI1CLKSOURCE_PLL2T))

#define IS_RCC_XSPI2CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_XSPI2CLKSOURCE_HCLK)  || \
   ((__SOURCE__) == RCC_XSPI2CLKSOURCE_PLL2S) || \
   ((__SOURCE__) == RCC_XSPI2CLKSOURCE_PLL2T))

#define IS_RCC_PSSICLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_PSSICLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_PSSICLKSOURCE_CLKP))

#define IS_RCC_SAI1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL1Q) || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL3P) || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_CLKP)  || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PIN))

#define IS_RCC_SAI2CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL1Q) || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL3P) || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_CLKP)  || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PIN)   || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_SPDIF))

#define IS_RCC_SDMMC12CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SDMMC12CLKSOURCE_PLL2S)  || \
   ((__SOURCE__) == RCC_SDMMC12CLKSOURCE_PLL2T))

#define IS_RCC_SPDIFRXCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPDIFRXCLKSOURCE_PLL1Q) || \
   ((__SOURCE__) == RCC_SPDIFRXCLKSOURCE_PLL2R) || \
   ((__SOURCE__) == RCC_SPDIFRXCLKSOURCE_PLL3R) || \
   ((__SOURCE__) == RCC_SPDIFRXCLKSOURCE_HSI))

#define IS_RCC_SPI1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI1CLKSOURCE_PLL1Q) || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_PLL3P) || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_PIN)   || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_CLKP))

#define IS_RCC_SPI23CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI23CLKSOURCE_PLL1Q) || \
   ((__SOURCE__) == RCC_SPI23CLKSOURCE_PLL2P) || \
   ((__SOURCE__) == RCC_SPI23CLKSOURCE_PLL3P) || \
   ((__SOURCE__) == RCC_SPI23CLKSOURCE_PIN)   || \
   ((__SOURCE__) == RCC_SPI23CLKSOURCE_CLKP))

#define IS_RCC_SPI45CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI45CLKSOURCE_PCLK2) || \
   ((__SOURCE__) == RCC_SPI45CLKSOURCE_PLL2Q) || \
   ((__SOURCE__) == RCC_SPI45CLKSOURCE_PLL3Q) || \
   ((__SOURCE__) == RCC_SPI45CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_SPI45CLKSOURCE_CSI)   || \
   ((__SOURCE__) == RCC_SPI45CLKSOURCE_HSE))

#define IS_RCC_SPI6CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI6CLKSOURCE_PCLK4) || \
   ((__SOURCE__) == RCC_SPI6CLKSOURCE_PLL2Q) || \
   ((__SOURCE__) == RCC_SPI6CLKSOURCE_PLL3Q) || \
   ((__SOURCE__) == RCC_SPI6CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_SPI6CLKSOURCE_CSI)   || \
   ((__SOURCE__) == RCC_SPI6CLKSOURCE_HSE))

#define IS_RCC_USART1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK2) || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_PLL2Q) || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_PLL3Q) || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_CSI)   || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_LSE))

#define IS_RCC_USART234578CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_USART234578CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_USART234578CLKSOURCE_PLL2Q) || \
   ((__SOURCE__) == RCC_USART234578CLKSOURCE_PLL3Q) || \
   ((__SOURCE__) == RCC_USART234578CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_USART234578CLKSOURCE_LSE)   || \
   ((__SOURCE__) == RCC_USART234578CLKSOURCE_CSI))

#define IS_RCC_USBPHYCCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_USBPHYCCLKSOURCE_HSE)      || \
   ((__SOURCE__) == RCC_USBPHYCCLKSOURCE_HSE_DIV2) || \
   ((__SOURCE__) == RCC_USBPHYCCLKSOURCE_PLL3Q))

#define IS_RCC_USBOTGFSCLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_USBOTGFSCLKSOURCE_HSI48) || \
   ((__SOURCE__) == RCC_USBOTGFSCLKSOURCE_PLL3Q) || \
   ((__SOURCE__) == RCC_USBOTGFSCLKSOURCE_HSE)   || \
   ((__SOURCE__) == RCC_USBOTGFSCLKSOURCE_CLK48))

#define IS_RCC_TIMCLKPRESCALER(__VALUE__)  \
  (((__VALUE__) == RCC_TIMPRES_DISABLE) || \
   ((__VALUE__) == RCC_TIMPRES_ENABLE))

#define IS_RCC_CLOCKPROTECTION(__CLOCK__) \
  ((((__CLOCK__) & RCC_CLOCKPROTECT_FMC) == RCC_CLOCKPROTECT_FMC) || \
   (((__CLOCK__) & RCC_CLOCKPROTECT_XSPI) == RCC_CLOCKPROTECT_XSPI) || \
   (((__CLOCK__) & ~(RCC_CLOCKPROTECT_FMC | RCC_CLOCKPROTECT_XSPI)) == 0U))


#define IS_RCC_CRS_SYNC_SOURCE(__SOURCE__) (((__SOURCE__) == RCC_CRS_SYNC_SOURCE_LSE)  || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_USB_OTG_FS) || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_USB_OTG_HS) || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_GPIO))

#define IS_RCC_CRS_SYNC_DIV(__DIV__)       (((__DIV__) == RCC_CRS_SYNC_DIV1)  || ((__DIV__) == RCC_CRS_SYNC_DIV2)  || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV4)  || ((__DIV__) == RCC_CRS_SYNC_DIV8)  || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV16) || ((__DIV__) == RCC_CRS_SYNC_DIV32) || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV64) || ((__DIV__) == RCC_CRS_SYNC_DIV128))

#define IS_RCC_CRS_SYNC_POLARITY(__POLARITY__) (((__POLARITY__) == RCC_CRS_SYNC_POLARITY_RISING) || \
                                                ((__POLARITY__) == RCC_CRS_SYNC_POLARITY_FALLING))

#define IS_RCC_CRS_RELOADVALUE(__VALUE__)  ((__VALUE__) <= CRS_CFGR_RELOAD)

#define IS_RCC_CRS_ERRORLIMIT(__VALUE__)   ((__VALUE__) <= (CRS_CFGR_FELIM >> CRS_CFGR_FELIM_Pos))

#define IS_RCC_CRS_HSI48CALIBRATION(__VALUE__) ((__VALUE__) <= (CRS_CR_TRIM >> CRS_CR_TRIM_Pos))

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

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_RCC_EX_H */
