/**
  ******************************************************************************
  * @file    stm32wlxx_ll_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC LL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32WLxx_LL_RCC_H
#define __STM32WLxx_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx.h"

/** @addtogroup STM32WLxx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup RCC_LL RCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Variables RCC Private Variables
  * @{
  */

#define HSE_CONTROL_UNLOCK_KEY 0xCAFECAFEU

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_Private_Macros RCC Private Macros
  * @{
  */
/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_Exported_Types RCC Exported Types
  * @{
  */

/** @defgroup LL_ES_CLOCK_FREQ Clocks Frequency Structure
  * @{
  */

/**
  * @brief  RCC Clocks Frequency Structure
  */
typedef struct
{
  uint32_t SYSCLK_Frequency;         /*!< SYSCLK clock frequency */
  uint32_t HCLK1_Frequency;          /*!< HCLK1 clock frequency  */
#if defined(DUAL_CORE)
  uint32_t HCLK2_Frequency;          /*!< HCLK2 clock frequency  */
#endif /* DUAL_CORE */
  uint32_t HCLK3_Frequency;          /*!< HCLK3 clock frequency  */
  uint32_t PCLK1_Frequency;          /*!< PCLK1 clock frequency  */
  uint32_t PCLK2_Frequency;          /*!< PCLK2 clock frequency  */
} LL_RCC_ClocksTypeDef;

/**
  * @}
  */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_LL_EC_OSC_VALUES Oscillator Values adaptation
  * @brief    Defines used to adapt values of different oscillators
  * @note     These values could be modified in the user environment according to
  *           HW set-up.
  * @{
  */
#if !defined  (HSE_VALUE)
#define HSE_VALUE    32000000U  /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE    16000000U  /*!< Value of the HSI oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768U     /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE    32000U     /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */

#if !defined  (EXTERNAL_CLOCK_VALUE)
#define EXTERNAL_CLOCK_VALUE    48000U /*!< Value of the I2S_CKIN external oscillator in Hz */
#endif /* EXTERNAL_CLOCK_VALUE */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_WriteReg function
  * @{
  */
#define LL_RCC_CICR_LSIRDYC                RCC_CICR_LSIRDYC    /*!< LSI Ready Interrupt Clear */
#define LL_RCC_CICR_LSERDYC                RCC_CICR_LSERDYC     /*!< LSE Ready Interrupt Clear */
#define LL_RCC_CICR_MSIRDYC                RCC_CICR_MSIRDYC     /*!< MSI Ready Interrupt Clear */
#define LL_RCC_CICR_HSIRDYC                RCC_CICR_HSIRDYC     /*!< HSI Ready Interrupt Clear */
#define LL_RCC_CICR_HSERDYC                RCC_CICR_HSERDYC     /*!< HSE Ready Interrupt Clear */
#define LL_RCC_CICR_PLLRDYC                RCC_CICR_PLLRDYC     /*!< PLL Ready Interrupt Clear */
#define LL_RCC_CICR_LSECSSC                RCC_CICR_LSECSSC     /*!< LSE Clock Security System Interrupt Clear */
#define LL_RCC_CICR_CSSC                   RCC_CICR_CSSC        /*!< Clock Security System Interrupt Clear */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_ReadReg function
  * @{
  */
#define LL_RCC_CIFR_LSIRDYF                RCC_CIFR_LSIRDYF     /*!< LSI Ready Interrupt flag */
#define LL_RCC_CIFR_LSERDYF                RCC_CIFR_LSERDYF     /*!< LSE Ready Interrupt flag */
#define LL_RCC_CIFR_MSIRDYF                RCC_CIFR_MSIRDYF     /*!< MSI Ready Interrupt flag */
#define LL_RCC_CIFR_HSIRDYF                RCC_CIFR_HSIRDYF     /*!< HSI Ready Interrupt flag */
#define LL_RCC_CIFR_HSERDYF                RCC_CIFR_HSERDYF     /*!< HSE Ready Interrupt flag */
#define LL_RCC_CIFR_PLLRDYF                RCC_CIFR_PLLRDYF     /*!< PLL Ready Interrupt flag */
#define LL_RCC_CIFR_LSECSSF                RCC_CIFR_LSECSSF     /*!< LSE Clock Security System Interrupt flag */
#define LL_RCC_CIFR_CSSF                   RCC_CIFR_CSSF        /*!< Clock Security System Interrupt flag */
#define LL_RCC_CSR_LPWRRSTF                RCC_CSR_LPWRRSTF     /*!< Low-Power reset flag */
#define LL_RCC_CSR_OBLRSTF                 RCC_CSR_OBLRSTF      /*!< OBL reset flag */
#define LL_RCC_CSR_PINRSTF                 RCC_CSR_PINRSTF      /*!< PIN reset flag */
#define LL_RCC_CSR_SFTRSTF                 RCC_CSR_SFTRSTF      /*!< Software Reset flag */
#define LL_RCC_CSR_IWDGRSTF                RCC_CSR_IWDGRSTF     /*!< Independent Watchdog reset flag */
#define LL_RCC_CSR_WWDGRSTF                RCC_CSR_WWDGRSTF     /*!< Window watchdog reset flag */
#define LL_RCC_CSR_BORRSTF                 RCC_CSR_BORRSTF      /*!< BOR reset flag */
#define LL_RCC_CSR_RFILASTF                RCC_CSR_RFILARSTF    /*!< Radio illegal access flag */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_RCC_ReadReg and  LL_RCC_WriteReg functions
  * @{
  */
#define LL_RCC_CIER_LSIRDYIE               RCC_CIER_LSIRDYIE      /*!< LSI Ready Interrupt Enable */
#define LL_RCC_CIER_LSERDYIE               RCC_CIER_LSERDYIE      /*!< LSE Ready Interrupt Enable */
#define LL_RCC_CIER_MSIRDYIE               RCC_CIER_MSIRDYIE      /*!< MSI Ready Interrupt Enable */
#define LL_RCC_CIER_HSIRDYIE               RCC_CIER_HSIRDYIE      /*!< HSI Ready Interrupt Enable */
#define LL_RCC_CIER_HSERDYIE               RCC_CIER_HSERDYIE      /*!< HSE Ready Interrupt Enable */
#define LL_RCC_CIER_PLLRDYIE               RCC_CIER_PLLRDYIE      /*!< PLL Ready Interrupt Enable */
#define LL_RCC_CIER_LSECSSIE               RCC_CIER_LSECSSIE      /*!< LSE CSS Interrupt Enable */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW                0x00000000U             /*!< Xtal mode lower driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMLOW          RCC_BDCR_LSEDRV_0       /*!< Xtal mode medium low driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH         RCC_BDCR_LSEDRV_1       /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_HIGH               RCC_BDCR_LSEDRV         /*!< Xtal mode higher driving capability */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIRANGE  MSI clock ranges
  * @{
  */
#define LL_RCC_MSIRANGE_0                  RCC_CR_MSIRANGE_0  /*!< MSI = 100 KHz  */
#define LL_RCC_MSIRANGE_1                  RCC_CR_MSIRANGE_1  /*!< MSI = 200 KHz  */
#define LL_RCC_MSIRANGE_2                  RCC_CR_MSIRANGE_2  /*!< MSI = 400 KHz  */
#define LL_RCC_MSIRANGE_3                  RCC_CR_MSIRANGE_3  /*!< MSI = 800 KHz  */
#define LL_RCC_MSIRANGE_4                  RCC_CR_MSIRANGE_4  /*!< MSI = 1 MHz    */
#define LL_RCC_MSIRANGE_5                  RCC_CR_MSIRANGE_5  /*!< MSI = 2 MHz    */
#define LL_RCC_MSIRANGE_6                  RCC_CR_MSIRANGE_6  /*!< MSI = 4 MHz    */
#define LL_RCC_MSIRANGE_7                  RCC_CR_MSIRANGE_7  /*!< MSI = 8 MHz    */
#define LL_RCC_MSIRANGE_8                  RCC_CR_MSIRANGE_8  /*!< MSI = 16 MHz   */
#define LL_RCC_MSIRANGE_9                  RCC_CR_MSIRANGE_9  /*!< MSI = 24 MHz   */
#define LL_RCC_MSIRANGE_10                 RCC_CR_MSIRANGE_10 /*!< MSI = 32 MHz   */
#define LL_RCC_MSIRANGE_11                 RCC_CR_MSIRANGE_11 /*!< MSI = 48 MHz   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSISRANGE  MSI range after Standby mode
  * @{
  */
#define LL_RCC_MSISRANGE_4                 RCC_CSR_MSISRANGE_1  /*!< MSI = 1 MHz    */
#define LL_RCC_MSISRANGE_5                 RCC_CSR_MSISRANGE_2  /*!< MSI = 2 MHz    */
#define LL_RCC_MSISRANGE_6                 RCC_CSR_MSISRANGE_4  /*!< MSI = 4 MHz    */
#define LL_RCC_MSISRANGE_7                 RCC_CSR_MSISRANGE_8  /*!< MSI = 8 MHz    */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE  LSCO Selection
  * @{
  */
#define LL_RCC_LSCO_CLKSOURCE_LSI          0x00000000U           /*!< LSI selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_LSE          RCC_BDCR_LSCOSEL      /*!< LSE selection for low speed clock  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_MSI           0x00000000U    /*!< MSI selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSI           RCC_CFGR_SW_0    /*!< HSI selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSE           RCC_CFGR_SW_1    /*!< HSE selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_PLL           (RCC_CFGR_SW_1 | RCC_CFGR_SW_0)    /*!< PLL selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_MSI    0x00000000U   /*!< MSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI    RCC_CFGR_SWS_0   /*!< HSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE    RCC_CFGR_SWS_1   /*!< HSE used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_PLL    (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0)   /*!< PLL used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV  AHB prescaler
  * @{
  */
#define LL_RCC_SYSCLK_DIV_1                0x00000000U   /*!< SYSCLK not divided */
#define LL_RCC_SYSCLK_DIV_2                RCC_CFGR_HPRE_3   /*!< SYSCLK divided by 2 */
#define LL_RCC_SYSCLK_DIV_3                RCC_CFGR_HPRE_0   /*!< SYSCLK divided by 3 */
#define LL_RCC_SYSCLK_DIV_4                (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_0)   /*!< SYSCLK divided by 4 */
#define LL_RCC_SYSCLK_DIV_5                RCC_CFGR_HPRE_1   /*!< SYSCLK divided by 5 */
#define LL_RCC_SYSCLK_DIV_6                (RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0)   /*!< SYSCLK divided by 6 */
#define LL_RCC_SYSCLK_DIV_8                (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1)   /*!< SYSCLK divided by 8 */
#define LL_RCC_SYSCLK_DIV_10               (RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1)  /*!< SYSCLK divided by 10 */
#define LL_RCC_SYSCLK_DIV_16               (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0)  /*!< SYSCLK divided by 16 */
#define LL_RCC_SYSCLK_DIV_32               (RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0)  /*!< SYSCLK divided by 32 */
#define LL_RCC_SYSCLK_DIV_64               (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2)  /*!< SYSCLK divided by 64 */
#define LL_RCC_SYSCLK_DIV_128              (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0) /*!< SYSCLK divided by 128 */
#define LL_RCC_SYSCLK_DIV_256              (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1) /*!< SYSCLK divided by 256 */
#define LL_RCC_SYSCLK_DIV_512              (RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0) /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV  APB low-speed prescaler (APB1)
  * @{
  */
#define LL_RCC_APB1_DIV_1                  0x00000000U                            /*!< HCLK1 not divided */
#define LL_RCC_APB1_DIV_2                  RCC_CFGR_PPRE1_2                       /*!< HCLK1 divided by 2 */
#define LL_RCC_APB1_DIV_4                  (RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE1_0)  /*!< HCLK1 divided by 4 */
#define LL_RCC_APB1_DIV_8                  (RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE1_1)  /*!< HCLK1 divided by 8 */
#define LL_RCC_APB1_DIV_16                 (RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_0) /*!< HCLK1 divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB2_DIV  APB high-speed prescaler (APB2)
  * @{
  */
#define LL_RCC_APB2_DIV_1                  0x00000000U                            /*!< HCLK1 not divided */
#define LL_RCC_APB2_DIV_2                  RCC_CFGR_PPRE2_2                       /*!< HCLK1 divided by 2 */
#define LL_RCC_APB2_DIV_4                  (RCC_CFGR_PPRE2_2 | RCC_CFGR_PPRE2_0)  /*!< HCLK1 divided by 4 */
#define LL_RCC_APB2_DIV_8                  (RCC_CFGR_PPRE2_2 | RCC_CFGR_PPRE2_1)  /*!< HCLK1 divided by 8 */
#define LL_RCC_APB2_DIV_16                 (RCC_CFGR_PPRE2_2 | RCC_CFGR_PPRE2_1 | RCC_CFGR_PPRE2_0) /*!< HCLK1 divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_STOP_WAKEUPCLOCK  Wakeup from Stop and CSS backup clock selection
  * @{
  */
#define LL_RCC_STOP_WAKEUPCLOCK_MSI        0x00000000U             /*!< MSI selection after wake-up from STOP */
#define LL_RCC_STOP_WAKEUPCLOCK_HSI        RCC_CFGR_STOPWUCK       /*!< HSI selection after wake-up from STOP */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1SOURCE  MCO1 SOURCE selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_NOCLOCK          0x00000000U                                             /*!< MCO output disabled, no clock on MCO */
#define LL_RCC_MCO1SOURCE_SYSCLK           RCC_CFGR_MCOSEL_0                                       /*!< SYSCLK selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_MSI              RCC_CFGR_MCOSEL_1                                       /*!< MSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSI              (RCC_CFGR_MCOSEL_0| RCC_CFGR_MCOSEL_1)                  /*!< HSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSE              RCC_CFGR_MCOSEL_2                                       /*!< HSE after stabilization selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_PLLCLK           (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_2)                   /*!< Main PLLR selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSI              (RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2)                   /*!< LSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSE              RCC_CFGR_MCOSEL_3                                       /*!< LSE selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_PLLPCLK          (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_2|RCC_CFGR_MCOSEL_3) /*!< Main PLLQ selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_PLLQCLK          (RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2|RCC_CFGR_MCOSEL_3) /*!< Main PLLP selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1_DIV  MCO1 prescaler
  * @{
  */
#define LL_RCC_MCO1_DIV_1                  0x00000000U                                   /*!< MCO not divided */
#define LL_RCC_MCO1_DIV_2                  RCC_CFGR_MCOPRE_0                             /*!< MCO divided by 2 */
#define LL_RCC_MCO1_DIV_4                  RCC_CFGR_MCOPRE_1                             /*!< MCO divided by 4 */
#define LL_RCC_MCO1_DIV_8                  (RCC_CFGR_MCOPRE_1 | RCC_CFGR_MCOPRE_0)       /*!< MCO divided by 8 */
#define LL_RCC_MCO1_DIV_16                 RCC_CFGR_MCOPRE_2                             /*!< MCO divided by 16 */
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EC_PERIPH_FREQUENCY Peripheral clock frequency
  * @{
  */
#define LL_RCC_PERIPH_FREQUENCY_NO         0x00000000U                 /*!< No clock enabled for the peripheral            */
#define LL_RCC_PERIPH_FREQUENCY_NA         0xFFFFFFFFU                 /*!< Frequency cannot be provided as external clock */
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/** @defgroup RCC_LL_EC_USART1_CLKSOURCE USARTx CLKSOURCE
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK2      (RCC_CCIPR_USART1SEL << 16U)                           /*!< PCLK2 clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_SYSCLK     ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL_0) /*!< SYSCLK clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_HSI        ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL_1) /*!< HSI clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_LSE        ((RCC_CCIPR_USART1SEL << 16U) | RCC_CCIPR_USART1SEL)   /*!< LSE clock used as USART1 clock source */
#define LL_RCC_USART2_CLKSOURCE_PCLK1      (RCC_CCIPR_USART2SEL << 16U)                           /*!< PCLK1 clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_SYSCLK     ((RCC_CCIPR_USART2SEL << 16U) | RCC_CCIPR_USART2SEL_0) /*!< SYSCLK clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_HSI        ((RCC_CCIPR_USART2SEL << 16U) | RCC_CCIPR_USART2SEL_1) /*!< HSI clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_LSE        ((RCC_CCIPR_USART2SEL << 16U) | RCC_CCIPR_USART2SEL)   /*!< LSE clock used as USART2 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2S2_CLKSOURCE Peripheral I2S clock source selection
  * @{
  */
#define LL_RCC_I2S2_CLKSOURCE_PLL         RCC_CCIPR_I2S2SEL_0          /*!< PLL clock used as I2S2 clock source */
#define LL_RCC_I2S2_CLKSOURCE_HSI         RCC_CCIPR_I2S2SEL_1          /*!< HSI clock used as I2S2 clock source */
#define LL_RCC_I2S2_CLKSOURCE_PIN         RCC_CCIPR_I2S2SEL            /*!< External clock used as I2S2 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART1_CLKSOURCE LPUART1 CLKSOURCE
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK1     0x00000000U               /*!< PCLK1 selected as LPUART1 clock */
#define LL_RCC_LPUART1_CLKSOURCE_SYSCLK    RCC_CCIPR_LPUART1SEL_0    /*!< SYCLK selected as LPUART1 clock */
#define LL_RCC_LPUART1_CLKSOURCE_HSI       RCC_CCIPR_LPUART1SEL_1    /*!< HSI selected as LPUART1 clock */
#define LL_RCC_LPUART1_CLKSOURCE_LSE       RCC_CCIPR_LPUART1SEL      /*!< LSE selected as LPUART1 clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2Cx_CLKSOURCE I2Cx CLKSOURCE
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1        (uint32_t)((RCC_CCIPR_I2C1SEL << 4) | (0x00000000U >> 4))         /*!< PCLK1 selected as I2C1 clock */
#define LL_RCC_I2C1_CLKSOURCE_SYSCLK       (uint32_t)((RCC_CCIPR_I2C1SEL << 4) | (RCC_CCIPR_I2C1SEL_0 >> 4)) /*!< SYSCLK selected as I2C1 clock */
#define LL_RCC_I2C1_CLKSOURCE_HSI          (uint32_t)((RCC_CCIPR_I2C1SEL << 4) | (RCC_CCIPR_I2C1SEL_1 >> 4)) /*!< HSI selected as I2C1 clock */
#define LL_RCC_I2C2_CLKSOURCE_PCLK1        (uint32_t)((RCC_CCIPR_I2C2SEL << 4) | (0x00000000U >> 4))         /*!< PCLK1 selected as I2C2 clock */
#define LL_RCC_I2C2_CLKSOURCE_SYSCLK       (uint32_t)((RCC_CCIPR_I2C2SEL << 4) | (RCC_CCIPR_I2C2SEL_0 >> 4)) /*!< SYSCLK selected as I2C2 clock */
#define LL_RCC_I2C2_CLKSOURCE_HSI          (uint32_t)((RCC_CCIPR_I2C2SEL << 4) | (RCC_CCIPR_I2C2SEL_1 >> 4)) /*!< HSI selected as I2C2 clock */
#define LL_RCC_I2C3_CLKSOURCE_PCLK1        (uint32_t)((RCC_CCIPR_I2C3SEL << 4) | (0x00000000U >> 4))         /*!< PCLK1 selected as I2C3 clock */
#define LL_RCC_I2C3_CLKSOURCE_SYSCLK       (uint32_t)((RCC_CCIPR_I2C3SEL << 4) | (RCC_CCIPR_I2C3SEL_0 >> 4)) /*!< SYSCLK selected as I2C3 clock */
#define LL_RCC_I2C3_CLKSOURCE_HSI          (uint32_t)((RCC_CCIPR_I2C3SEL << 4) | (RCC_CCIPR_I2C3SEL_1 >> 4)) /*!< HSI selected as I2C3 clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIMx_CLKSOURCE LPTIMx CLKSOURCE
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_PCLK1      (uint32_t)(RCC_CCIPR_LPTIM1SEL | (0x00000000U >> 16))           /*!< PCLK1 selected as LPTIM1 clock */
#define LL_RCC_LPTIM1_CLKSOURCE_LSI        (uint32_t)(RCC_CCIPR_LPTIM1SEL | (RCC_CCIPR_LPTIM1SEL_0 >> 16)) /*!< LSI selected as LPTIM1 clock */
#define LL_RCC_LPTIM1_CLKSOURCE_HSI        (uint32_t)(RCC_CCIPR_LPTIM1SEL | (RCC_CCIPR_LPTIM1SEL_1 >> 16)) /*!< HSI selected as LPTIM1 clock */
#define LL_RCC_LPTIM1_CLKSOURCE_LSE        (uint32_t)(RCC_CCIPR_LPTIM1SEL | (RCC_CCIPR_LPTIM1SEL >> 16))   /*!< LSE selected as LPTIM1 clock */
#define LL_RCC_LPTIM2_CLKSOURCE_PCLK1      (uint32_t)(RCC_CCIPR_LPTIM2SEL | (0x00000000U >> 16))           /*!< PCLK1 selected as LPTIM2 clock */
#define LL_RCC_LPTIM2_CLKSOURCE_LSI        (uint32_t)(RCC_CCIPR_LPTIM2SEL | (RCC_CCIPR_LPTIM2SEL_0 >> 16)) /*!< LSI selected as LPTIM2 clock */
#define LL_RCC_LPTIM2_CLKSOURCE_HSI        (uint32_t)(RCC_CCIPR_LPTIM2SEL | (RCC_CCIPR_LPTIM2SEL_1 >> 16)) /*!< HSI selected as LPTIM2 clock */
#define LL_RCC_LPTIM2_CLKSOURCE_LSE        (uint32_t)(RCC_CCIPR_LPTIM2SEL | (RCC_CCIPR_LPTIM2SEL >> 16))   /*!< LSE selected as LPTIM2 clock */
#define LL_RCC_LPTIM3_CLKSOURCE_PCLK1      (uint32_t)(RCC_CCIPR_LPTIM3SEL | (0x00000000U >> 16))           /*!< PCLK1 selected as LPTIM3 clock */
#define LL_RCC_LPTIM3_CLKSOURCE_LSI        (uint32_t)(RCC_CCIPR_LPTIM3SEL | (RCC_CCIPR_LPTIM3SEL_0 >> 16)) /*!< LSI selected as LPTIM3 clock */
#define LL_RCC_LPTIM3_CLKSOURCE_HSI        (uint32_t)(RCC_CCIPR_LPTIM3SEL | (RCC_CCIPR_LPTIM3SEL_1 >> 16)) /*!< HSI selected as LPTIM3 clock */
#define LL_RCC_LPTIM3_CLKSOURCE_LSE        (uint32_t)(RCC_CCIPR_LPTIM3SEL | (RCC_CCIPR_LPTIM3SEL >> 16))   /*!< LSE selected as LPTIM3 clock */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC_CLKSRC ADC CLKSRC
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE_NONE             0x00000000U        /*!< no Clock used as ADC clock*/
#define LL_RCC_ADC_CLKSOURCE_HSI              RCC_CCIPR_ADCSEL_0 /*!< HSI selected as ADC clock*/
#define LL_RCC_ADC_CLKSOURCE_PLL              RCC_CCIPR_ADCSEL_1 /*!< PLL selected as ADC clock*/
#define LL_RCC_ADC_CLKSOURCE_SYSCLK           RCC_CCIPR_ADCSEL   /*!< SYSCLK selected as ADC clock*/
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RNG_CLKSRC RNG CLKSRC
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE_PLL              0x00000000U        /*!< PLL selected as RNG Clock */
#define LL_RCC_RNG_CLKSOURCE_LSI              RCC_CCIPR_RNGSEL_0 /*!< LSI selected as RNG clock*/
#define LL_RCC_RNG_CLKSOURCE_LSE              RCC_CCIPR_RNGSEL_1 /*!< LSE selected as RNG clock*/
#define LL_RCC_RNG_CLKSOURCE_MSI              (RCC_CCIPR_RNGSEL_1 | RCC_CCIPR_RNGSEL_0)  /*!< MSI selected as RNG clock*/
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USARTx USARTx
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE            RCC_CCIPR_USART1SEL   /*!< USART1 clock source selection bits */
#define LL_RCC_USART2_CLKSOURCE            RCC_CCIPR_USART2SEL   /*!< USART2 clock source selection bits */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2S2 Peripheral I2S get clock source
  * @{
  */
#define LL_RCC_I2S2_CLKSOURCE              RCC_CCIPR_I2S2SEL /*!< I2S2 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART1 LPUART1
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE           RCC_CCIPR_LPUART1SEL  /*!< LPUART1 clock source selection bits */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2Cx I2Cx
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE              RCC_CCIPR_I2C1SEL    /*!< I2C1 clock source selection bits */
#define LL_RCC_I2C2_CLKSOURCE              RCC_CCIPR_I2C2SEL    /*!< I2C2 clock source selection bits */
#define LL_RCC_I2C3_CLKSOURCE              RCC_CCIPR_I2C3SEL    /*!< I2C3 clock source selection bits */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIMx LPTIMx
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE            RCC_CCIPR_LPTIM1SEL  /*!< LPTIM1 clock source selection bits */
#define LL_RCC_LPTIM2_CLKSOURCE            RCC_CCIPR_LPTIM2SEL  /*!< LPTIM2 clock source selection bits */
#define LL_RCC_LPTIM3_CLKSOURCE            RCC_CCIPR_LPTIM3SEL  /*!< LPTIM2 clock source selection bits */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_RNG RNG
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE               RCC_CCIPR_RNGSEL  /*!< RNG clock source selection bits */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC ADC
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE               RCC_CCIPR_ADCSEL   /*!< ADC clock source selection bits */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE          0x00000000U                   /*!< No clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSE           RCC_BDCR_RTCSEL_0             /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI           RCC_BDCR_RTCSEL_1             /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV32     RCC_BDCR_RTCSEL               /*!< HSE oscillator clock divided by 32 used as RTC clock */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLSOURCE  PLL entry clock source
  * @{
  */
#define LL_RCC_PLLSOURCE_NONE              0x00000000U             /*!< No clock */
#define LL_RCC_PLLSOURCE_MSI               RCC_PLLCFGR_PLLSRC_0  /*!< MSI clock selected as PLL entry clock source */
#define LL_RCC_PLLSOURCE_HSI               RCC_PLLCFGR_PLLSRC_1  /*!< HSI clock selected as PLL entry clock source */
#define LL_RCC_PLLSOURCE_HSE               (RCC_PLLCFGR_PLLSRC_1 | RCC_PLLCFGR_PLLSRC_0)  /*!< HSE clock selected as PLL entry clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLM_DIV  PLL.division factor
  * @{
  */
#define LL_RCC_PLLM_DIV_1                  0x00000000U                                 /*!< PLL division factor by 1 */
#define LL_RCC_PLLM_DIV_2                  (RCC_PLLCFGR_PLLM_0)                        /*!< PLL division factor by 2 */
#define LL_RCC_PLLM_DIV_3                  (RCC_PLLCFGR_PLLM_1)                        /*!< PLL division factor by 3 */
#define LL_RCC_PLLM_DIV_4                  ((RCC_PLLCFGR_PLLM_1 | RCC_PLLCFGR_PLLM_0)) /*!< PLL division factor by 4 */
#define LL_RCC_PLLM_DIV_5                  (RCC_PLLCFGR_PLLM_2)                        /*!< PLL division factor by 5 */
#define LL_RCC_PLLM_DIV_6                  ((RCC_PLLCFGR_PLLM_2 | RCC_PLLCFGR_PLLM_0)) /*!< PLL division factor by 6 */
#define LL_RCC_PLLM_DIV_7                  ((RCC_PLLCFGR_PLLM_2 | RCC_PLLCFGR_PLLM_1)) /*!< PLL division factor by 7 */
#define LL_RCC_PLLM_DIV_8                  (RCC_PLLCFGR_PLLM)                          /*!< PLL division factor by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLR_DIV  PLL division factor (PLLR)
  * @{
  */
#define LL_RCC_PLLR_DIV_2                  (RCC_PLLCFGR_PLLR_0)                     /*!< Main PLL division factor for PLLCLK (system clock) by 2 */
#define LL_RCC_PLLR_DIV_3                  (RCC_PLLCFGR_PLLR_1)                     /*!< Main PLL division factor for PLLCLK (system clock) by 3 */
#define LL_RCC_PLLR_DIV_4                  (RCC_PLLCFGR_PLLR_1|RCC_PLLCFGR_PLLR_0)  /*!< Main PLL division factor for PLLCLK (system clock) by 4 */
#define LL_RCC_PLLR_DIV_5                  (RCC_PLLCFGR_PLLR_2)                     /*!< Main PLL division factor for PLLCLK (system clock) by 5 */
#define LL_RCC_PLLR_DIV_6                  (RCC_PLLCFGR_PLLR_2|RCC_PLLCFGR_PLLR_0)  /*!< Main PLL division factor for PLLCLK (system clock) by 6 */
#define LL_RCC_PLLR_DIV_7                  (RCC_PLLCFGR_PLLR_2|RCC_PLLCFGR_PLLR_1)  /*!< Main PLL division factor for PLLCLK (system clock) by 7 */
#define LL_RCC_PLLR_DIV_8                  (RCC_PLLCFGR_PLLR)                       /*!< Main PLL division factor for PLLCLK (system clock) by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLP_DIV  PLL division factor (PLLP)
  * @{
  */
#define LL_RCC_PLLP_DIV_2                  (RCC_PLLCFGR_PLLP_0)                                              /*!< Main PLL division factor for PLLP output by 2 */
#define LL_RCC_PLLP_DIV_3                  (RCC_PLLCFGR_PLLP_1)                                              /*!< Main PLL division factor for PLLP output by 3 */
#define LL_RCC_PLLP_DIV_4                  (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_1)                           /*!< Main PLL division factor for PLLP output by 4 */
#define LL_RCC_PLLP_DIV_5                  (RCC_PLLCFGR_PLLP_2)                                              /*!< Main PLL division factor for PLLP output by 5 */
#define LL_RCC_PLLP_DIV_6                  (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_2)                           /*!< Main PLL division factor for PLLP output by 6 */
#define LL_RCC_PLLP_DIV_7                  (RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_2)                           /*!< Main PLL division factor for PLLP output by 7 */
#define LL_RCC_PLLP_DIV_8                  (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_2)        /*!< Main PLL division factor for PLLP output by 8 */
#define LL_RCC_PLLP_DIV_9                  (RCC_PLLCFGR_PLLP_3)                                              /*!< Main PLL division factor for PLLP output by 9 */
#define LL_RCC_PLLP_DIV_10                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_3)                           /*!< Main PLL division factor for PLLP output by 10 */
#define LL_RCC_PLLP_DIV_11                 (RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_3)                           /*!< Main PLL division factor for PLLP output by 11 */
#define LL_RCC_PLLP_DIV_12                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_3)        /*!< Main PLL division factor for PLLP output by 12 */
#define LL_RCC_PLLP_DIV_13                 (RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_3)                           /*!< Main PLL division factor for PLLP output by 13 */
#define LL_RCC_PLLP_DIV_14                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_3)        /*!< Main PLL division factor for PLLP output by 14 */
#define LL_RCC_PLLP_DIV_15                 (RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_3)        /*!< Main PLL division factor for PLLP output by 15 */
#define LL_RCC_PLLP_DIV_16                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_3)/*!< Main PLL division factor for PLLP output by 16 */
#define LL_RCC_PLLP_DIV_17                 (RCC_PLLCFGR_PLLP_4)                                              /*!< Main PLL division factor for PLLP output by 17 */
#define LL_RCC_PLLP_DIV_18                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_4)                           /*!< Main PLL division factor for PLLP output by 18 */
#define LL_RCC_PLLP_DIV_19                 (RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_4)                           /*!< Main PLL division factor for PLLP output by 19 */
#define LL_RCC_PLLP_DIV_20                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_4)        /*!< Main PLL division factor for PLLP output by 20 */
#define LL_RCC_PLLP_DIV_21                 (RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_4)                           /*!< Main PLL division factor for PLLP output by 21 */
#define LL_RCC_PLLP_DIV_22                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_4)        /*!< Main PLL division factor for PLLP output by 22 */
#define LL_RCC_PLLP_DIV_23                 (RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_4)        /*!< Main PLL division factor for PLLP output by 23 */
#define LL_RCC_PLLP_DIV_24                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_4)/*!< Main PLL division factor for PLLP output by 24 */
#define LL_RCC_PLLP_DIV_25                 (RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_4)                           /*!< Main PLL division factor for PLLP output by 25 */
#define LL_RCC_PLLP_DIV_26                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_4)        /*!< Main PLL division factor for PLLP output by 26 */
#define LL_RCC_PLLP_DIV_27                 (RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_4)        /*!< Main PLL division factor for PLLP output by 27*/
#define LL_RCC_PLLP_DIV_28                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_4)/*!< Main PLL division factor for PLLP output by 28 */
#define LL_RCC_PLLP_DIV_29                 (RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_4)        /*!< Main PLL division factor for PLLP output by 29 */
#define LL_RCC_PLLP_DIV_30                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_4)/*!< Main PLL division factor for PLLP output by 30 */
#define LL_RCC_PLLP_DIV_31                 (RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_4)/*!< Main PLL division factor for PLLP output by 31 */
#define LL_RCC_PLLP_DIV_32                 (RCC_PLLCFGR_PLLP_0|RCC_PLLCFGR_PLLP_1|RCC_PLLCFGR_PLLP_2|RCC_PLLCFGR_PLLP_3|RCC_PLLCFGR_PLLP_4)/*!< Main PLL division factor for PLLP output by 32 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLQ_DIV  PLL division factor (PLLQ)
  * @{
  */
#define LL_RCC_PLLQ_DIV_2                  (RCC_PLLCFGR_PLLQ_0)                    /*!< Main PLL division factor for PLLQ output by 2 */
#define LL_RCC_PLLQ_DIV_3                  (RCC_PLLCFGR_PLLQ_1)                    /*!< Main PLL division factor for PLLQ output by 3 */
#define LL_RCC_PLLQ_DIV_4                  (RCC_PLLCFGR_PLLQ_1|RCC_PLLCFGR_PLLQ_0) /*!< Main PLL division factor for PLLQ output by 4 */
#define LL_RCC_PLLQ_DIV_5                  (RCC_PLLCFGR_PLLQ_2)                    /*!< Main PLL division factor for PLLQ output by 5 */
#define LL_RCC_PLLQ_DIV_6                  (RCC_PLLCFGR_PLLQ_2|RCC_PLLCFGR_PLLQ_0) /*!< Main PLL division factor for PLLQ output by 6 */
#define LL_RCC_PLLQ_DIV_7                  (RCC_PLLCFGR_PLLQ_2|RCC_PLLCFGR_PLLQ_1) /*!< Main PLL division factor for PLLQ output by 7 */
#define LL_RCC_PLLQ_DIV_8                  (RCC_PLLCFGR_PLLQ)                      /*!< Main PLL division factor for PLLQ output by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIRANGESEL  MSI clock range selection
  * @{
  */
#define LL_RCC_MSIRANGESEL_STANDBY         0U                  /*!< MSI Range is provided by MSISRANGE */
#define LL_RCC_MSIRANGESEL_RUN             1U                  /*!< MSI Range is provided by MSIRANGE */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSIPRE  LSI division factor
  * @{
  */
#define LL_RCC_LSI_PREDIV_1                0x00000000U         /*!< LSI division factor by 1   */
#define LL_RCC_LSI_PREDIV_128              RCC_CSR_LSIPRE      /*!< LSI division factor by 128 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RCC register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_RCC_WriteReg(__REG__, __VALUE__) WRITE_REG(RCC->__REG__, (__VALUE__))

/**
  * @brief  Read a value in RCC register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_RCC_ReadReg(__REG__) READ_REG(RCC->__REG__)
/**
  * @}
  */

/** @defgroup RCC_LL_EM_CALC_FREQ Calculate frequencies
  * @{
  */

/**
  * @brief  Helper macro to calculate the PLLRCLK frequency on system domain
  * @note ex: @ref __LL_RCC_CALC_PLLCLK_FREQ (HSE_VALUE,@ref LL_RCC_PLL_GetDivider (),
  *             @ref LL_RCC_PLL_GetN (), @ref LL_RCC_PLL_GetR ());
  * @param  __INPUTFREQ__ PLL Input frequency (based on MSI/HSE/HSI)
  * @param  __PLLM__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  __PLLN__ Between Min_Data = 6 and Max_Data = 127
  * @param  __PLLR__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLR_DIV_2
  *         @arg @ref LL_RCC_PLLR_DIV_3
  *         @arg @ref LL_RCC_PLLR_DIV_4
  *         @arg @ref LL_RCC_PLLR_DIV_5
  *         @arg @ref LL_RCC_PLLR_DIV_6
  *         @arg @ref LL_RCC_PLLR_DIV_7
  *         @arg @ref LL_RCC_PLLR_DIV_8
  * @retval PLL clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLLCLK_FREQ(__INPUTFREQ__, __PLLM__, __PLLN__, __PLLR__)  \
  ((__INPUTFREQ__) * (__PLLN__)  / ((((__PLLM__)>> RCC_PLLCFGR_PLLM_Pos) + 1U)) / \
   (((__PLLR__) >> RCC_PLLCFGR_PLLR_Pos) + 1U))

/**
  * @brief  Helper macro to calculate the PLLPCLK frequency used on ADC domain
  * @note ex: @ref __LL_RCC_CALC_PLLCLK_ADC_FREQ (HSE_VALUE,@ref LL_RCC_PLL_GetDivider (),
  *             @ref LL_RCC_PLL_GetN (), @ref LL_RCC_PLL_GetP ());
  * @param  __INPUTFREQ__ PLL Input frequency (based on MSI/HSE/HSI)
  * @param  __PLLM__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  __PLLN__ Between Min_Data = 6 and Max_Data = 127
  * @param  __PLLP__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLP_DIV_2
  *         @arg @ref LL_RCC_PLLP_DIV_3
  *         @arg @ref LL_RCC_PLLP_DIV_4
  *         @arg @ref LL_RCC_PLLP_DIV_5
  *         @arg @ref LL_RCC_PLLP_DIV_6
  *         @arg @ref LL_RCC_PLLP_DIV_7
  *         @arg @ref LL_RCC_PLLP_DIV_8
  *         @arg @ref LL_RCC_PLLP_DIV_9
  *         @arg @ref LL_RCC_PLLP_DIV_10
  *         @arg @ref LL_RCC_PLLP_DIV_11
  *         @arg @ref LL_RCC_PLLP_DIV_12
  *         @arg @ref LL_RCC_PLLP_DIV_13
  *         @arg @ref LL_RCC_PLLP_DIV_14
  *         @arg @ref LL_RCC_PLLP_DIV_15
  *         @arg @ref LL_RCC_PLLP_DIV_16
  *         @arg @ref LL_RCC_PLLP_DIV_17
  *         @arg @ref LL_RCC_PLLP_DIV_18
  *         @arg @ref LL_RCC_PLLP_DIV_19
  *         @arg @ref LL_RCC_PLLP_DIV_20
  *         @arg @ref LL_RCC_PLLP_DIV_21
  *         @arg @ref LL_RCC_PLLP_DIV_22
  *         @arg @ref LL_RCC_PLLP_DIV_23
  *         @arg @ref LL_RCC_PLLP_DIV_24
  *         @arg @ref LL_RCC_PLLP_DIV_25
  *         @arg @ref LL_RCC_PLLP_DIV_26
  *         @arg @ref LL_RCC_PLLP_DIV_27
  *         @arg @ref LL_RCC_PLLP_DIV_28
  *         @arg @ref LL_RCC_PLLP_DIV_29
  *         @arg @ref LL_RCC_PLLP_DIV_30
  *         @arg @ref LL_RCC_PLLP_DIV_31
  *         @arg @ref LL_RCC_PLLP_DIV_32
  * @retval PLL clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLLCLK_ADC_FREQ(__INPUTFREQ__, __PLLM__, __PLLN__, __PLLP__)  \
  ((__INPUTFREQ__) * (__PLLN__) / ((((__PLLM__)>> RCC_PLLCFGR_PLLM_Pos) + 1U)) / \
   (((__PLLP__) >> RCC_PLLCFGR_PLLP_Pos) + 1U))

/**
  * @brief  Helper macro to calculate the PLLQCLK frequency used on RNG domain
  * @note ex: @ref __LL_RCC_CALC_PLLCLK_RNG_FREQ (HSE_VALUE,@ref LL_RCC_PLL_GetDivider (),
  *             @ref LL_RCC_PLL_GetN (), @ref LL_RCC_PLL_GetQ ());
  * @param  __INPUTFREQ__ PLL Input frequency (based on MSI/HSE/HSI)
  * @param  __PLLM__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  __PLLN__ Between Min_Data = 6 and Max_Data = 127
  * @param  __PLLQ__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLQ_DIV_2
  *         @arg @ref LL_RCC_PLLQ_DIV_3
  *         @arg @ref LL_RCC_PLLQ_DIV_4
  *         @arg @ref LL_RCC_PLLQ_DIV_5
  *         @arg @ref LL_RCC_PLLQ_DIV_6
  *         @arg @ref LL_RCC_PLLQ_DIV_7
  *         @arg @ref LL_RCC_PLLQ_DIV_8
  * @retval PLL clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLLCLK_RNG_FREQ(__INPUTFREQ__, __PLLM__, __PLLN__, __PLLQ__)  \
  ((__INPUTFREQ__) * (__PLLN__) / ((((__PLLM__)>> RCC_PLLCFGR_PLLM_Pos) + 1U)) / \
   (((__PLLQ__) >> RCC_PLLCFGR_PLLQ_Pos) + 1U))

/**
  * @brief  Helper macro to calculate the PLLQCLK frequency used on I2S domain
  * @note ex: @ref __LL_RCC_CALC_PLLCLK_I2S2_FREQ (HSE_VALUE,@ref LL_RCC_PLL_GetDivider (),
  *             @ref LL_RCC_PLL_GetN (), @ref LL_RCC_PLL_GetQ ());
  * @param  __INPUTFREQ__ PLL Input frequency (based on MSI/HSE/HSI)
  * @param  __PLLM__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  __PLLN__ Between Min_Data = 6 and Max_Data = 127
  * @param  __PLLQ__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLQ_DIV_2
  *         @arg @ref LL_RCC_PLLQ_DIV_3
  *         @arg @ref LL_RCC_PLLQ_DIV_4
  *         @arg @ref LL_RCC_PLLQ_DIV_5
  *         @arg @ref LL_RCC_PLLQ_DIV_6
  *         @arg @ref LL_RCC_PLLQ_DIV_7
  *         @arg @ref LL_RCC_PLLQ_DIV_8
  * @retval PLL clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PLLCLK_I2S2_FREQ __LL_RCC_CALC_PLLCLK_RNG_FREQ

/**
  * @brief  Helper macro to calculate the HCLK1 frequency
  * @param  __SYSCLKFREQ__ SYSCLK frequency (based on MSI/HSE/HSI/PLLCLK)
  * @param  __CPU1PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval HCLK1 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HCLK1_FREQ(__SYSCLKFREQ__,__CPU1PRESCALER__)  \
  ((__SYSCLKFREQ__) / AHBPrescTable[((__CPU1PRESCALER__) & RCC_CFGR_HPRE) >>  RCC_CFGR_HPRE_Pos])

#if defined(DUAL_CORE)
/**
  * @brief  Helper macro to calculate the HCLK2 frequency
  * @param  __SYSCLKFREQ__ SYSCLK frequency (based on MSI/HSE/HSI/PLLCLK)
  * @param  __CPU2PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval HCLK2 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HCLK2_FREQ(__SYSCLKFREQ__, __CPU2PRESCALER__)  \
  ((__SYSCLKFREQ__) / AHBPrescTable[((__CPU2PRESCALER__) &  RCC_EXTCFGR_C2HPRE) >>  RCC_EXTCFGR_C2HPRE_Pos])
#endif  /* DUAL_CORE */

/**
  * @brief  Helper macro to calculate the HCLK3 frequency
  * @param  __SYSCLKFREQ__ SYSCLK frequency (based on MSI/HSE/HSI/PLLCLK)
  * @param  __AHB3PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval HCLK3 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_HCLK3_FREQ(__SYSCLKFREQ__, __AHB3PRESCALER__)  \
  ((__SYSCLKFREQ__) / AHBPrescTable[(((__AHB3PRESCALER__) >> 4U) & RCC_EXTCFGR_SHDHPRE) >>  RCC_EXTCFGR_SHDHPRE_Pos])


/**
  * @brief  Helper macro to calculate the PCLK1 frequency (ABP1)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB1PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK1_FREQ(__HCLKFREQ__, __APB1PRESCALER__)  \
  ((__HCLKFREQ__) >> APBPrescTable[(__APB1PRESCALER__) >>  RCC_CFGR_PPRE1_Pos])

/**
  * @brief  Helper macro to calculate the PCLK2 frequency (ABP2)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB2PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  * @retval PCLK2 clock frequency (in Hz)
  */
#define __LL_RCC_CALC_PCLK2_FREQ(__HCLKFREQ__, __APB2PRESCALER__)  \
  ((__HCLKFREQ__) >> APBPrescTable[(__APB2PRESCALER__) >>  RCC_CFGR_PPRE2_Pos])

/**
  * @brief  Helper macro to calculate the MSI frequency (in Hz)
  * @note __MSISEL__ can be retrieved thanks to function LL_RCC_MSI_IsEnabledRangeSelect()
  * @note if __MSISEL__ is equal to LL_RCC_MSIRANGESEL_STANDBY,
  *        __MSIRANGE__can be retrieved by LL_RCC_MSI_GetRangeAfterStandby()
  *        else by LL_RCC_MSI_GetRange()
  *        ex: __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
  *              (LL_RCC_MSI_IsEnabledRangeSelect()?
  *               LL_RCC_MSI_GetRange():
  *               LL_RCC_MSI_GetRangeAfterStandby()))
  * @param  __MSISEL__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGESEL_STANDBY
  *         @arg @ref LL_RCC_MSIRANGESEL_RUN
  * @param  __MSIRANGE__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGE_0
  *         @arg @ref LL_RCC_MSIRANGE_1
  *         @arg @ref LL_RCC_MSIRANGE_2
  *         @arg @ref LL_RCC_MSIRANGE_3
  *         @arg @ref LL_RCC_MSIRANGE_4
  *         @arg @ref LL_RCC_MSIRANGE_5
  *         @arg @ref LL_RCC_MSIRANGE_6
  *         @arg @ref LL_RCC_MSIRANGE_7
  *         @arg @ref LL_RCC_MSIRANGE_8
  *         @arg @ref LL_RCC_MSIRANGE_9
  *         @arg @ref LL_RCC_MSIRANGE_10
  *         @arg @ref LL_RCC_MSIRANGE_11
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  * @retval MSI clock frequency (in Hz)
  */
#define __LL_RCC_CALC_MSI_FREQ(__MSISEL__, __MSIRANGE__)    \
  (((__MSISEL__) == LL_RCC_MSIRANGESEL_STANDBY) ? \
   (MSIRangeTable[((__MSIRANGE__) & RCC_CSR_MSISRANGE_Msk) >> RCC_CSR_MSISRANGE_Pos ]) : \
   (MSIRangeTable[((__MSIRANGE__) & RCC_CR_MSIRANGE_Msk) >> RCC_CR_MSIRANGE_Pos]))

/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_LL_EF_HSE HSE
  * @{
  */

/**
  * @brief  Enable HSE VDDTCXO output on package pin PB0-VDDTCXO
  * @note PB0 must be configured in analog mode prior enabling VDDTCXO supply
  * @rmtoll CR           HSEBYPPWR        LL_RCC_HSE_EnableTcxo
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableTcxo(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEBYPPWR);
}

/**
  * @brief  Disable HSE VDDTCXO output on package pin PB0-VDDTCXO
  * @rmtoll CR           HSEBYPPWR        LL_RCC_HSE_DisableTcxo
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_DisableTcxo(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYPPWR);
}

/**
  * @brief  Get HSE VDDTCXO output on package pin PB0-VDDTCXO
  * @rmtoll CR           HSEBYPPWR        LL_RCC_HSE_IsEnabledTcxo
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabledTcxo(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEBYPPWR) == (RCC_CR_HSEBYPPWR)) ? 1UL : 0UL);
}


/**
  * @brief  Enable HSE sysclk and pll prescaler division by 2
  * @rmtoll CR           HSEPRE        LL_RCC_HSE_EnableDiv2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableDiv2(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEPRE);
}

/**
  * @brief  Disable HSE sysclk and pll prescaler division by 2
  * @rmtoll CR           HSEPRE        LL_RCC_HSE_DisableDiv2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_DisableDiv2(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEPRE);
}

/**
  * @brief  Get HSE sysclk and pll prescaler  division by 2
  * @rmtoll CR           HSEPRE        LL_RCC_HSE_IsEnabledDiv2
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabledDiv2(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEPRE) == (RCC_CR_HSEPRE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Clock Security System.
  * @rmtoll CR           CSSON         LL_RCC_HSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_CSSON);
}

/**
  * @brief  Enable HSE crystal oscillator (HSE ON)
  * @rmtoll CR           HSEON         LL_RCC_HSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Disable HSE crystal oscillator (HSE ON)
  * @rmtoll CR           HSEON         LL_RCC_HSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Check if HSE oscillator Ready
  * @rmtoll CR           HSERDY        LL_RCC_HSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI HSI
  * @{
  */

/**
  * @brief  Enable HSI even in stop mode
  * @note HSI oscillator is forced ON even in Stop mode
  * @rmtoll CR           HSIKERON      LL_RCC_HSI_EnableInStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_EnableInStopMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Disable HSI in stop mode
  * @rmtoll CR           HSIKERON      LL_RCC_HSI_DisableInStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_DisableInStopMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Check if HSI in stop mode is ready
  * @rmtoll CR           HSIKERON        LL_RCC_HSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledInStopMode(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIKERON) == (RCC_CR_HSIKERON)) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSI oscillator
  * @rmtoll CR           HSION         LL_RCC_HSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Disable HSI oscillator
  * @rmtoll CR           HSION         LL_RCC_HSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Check if HSI clock is ready
  * @rmtoll CR           HSIRDY        LL_RCC_HSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSI Automatic from stop mode
  * @rmtoll CR           HSIASFS       LL_RCC_HSI_EnableAutoFromStop
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_EnableAutoFromStop(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSIASFS);
}

/**
  * @brief  Disable HSI Automatic from stop mode
  * @rmtoll CR           HSIASFS       LL_RCC_HSI_DisableAutoFromStop
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_DisableAutoFromStop(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSIASFS);
}
/**
  * @brief  Get HSI Calibration value
  * @note When HSITRIM is written, HSICAL is updated with the sum of
  *       HSITRIM and the factory trim value
  * @rmtoll ICSCR        HSICAL        LL_RCC_HSI_GetCalibration
  * @retval Between Min_Data = 0x00 and Max_Data = 0xFF
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_HSICAL) >> RCC_ICSCR_HSICAL_Pos);
}

/**
  * @brief  Set HSI Calibration trimming
  * @note user-programmable trimming value that is added to the HSICAL
  * @note Default value is 64, which, when added to the HSICAL value,
  *       should trim the HSI to 16 MHz +/- 1 %
  * @rmtoll ICSCR        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 127
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSITRIM, Value << RCC_ICSCR_HSITRIM_Pos);
}

/**
  * @brief  Get HSI Calibration trimming
  * @rmtoll ICSCR        HSITRIM       LL_RCC_HSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 127
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_HSITRIM) >> RCC_ICSCR_HSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable  Low Speed External (LSE) crystal.
  * @rmtoll BDCR         LSEON         LL_RCC_LSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Disable  Low Speed External (LSE) crystal.
  * @rmtoll BDCR         LSEON         LL_RCC_LSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Check if Low Speed External (LSE) crystal has been enabled or not
  * @rmtoll BDCR         LSEON         LL_RCC_LSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSEON) == (RCC_BDCR_LSEON)) ? 1UL : 0UL);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll BDCR         LSEBYP        LL_RCC_LSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll BDCR         LSEBYP        LL_RCC_LSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Set LSE oscillator drive capability
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  * @rmtoll BDCR         LSEDRV        LL_RCC_LSE_SetDriveCapability
  * @param  LSEDrive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t LSEDrive)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, LSEDrive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll BDCR         LSEDRV        LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_LSEDRV));
}

/**
  * @brief  Enable Clock security system on LSE.
  * @rmtoll BDCR         LSECSSON      LL_RCC_LSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Disable Clock security system on LSE.
  * @note Clock security system can be disabled only after a LSE
  *       failure detection. In that case it MUST be disabled by software.
  * @rmtoll BDCR         LSECSSON      LL_RCC_LSE_DisableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Enable LSE oscillator propagation for system clock
  * @rmtoll BDCR         LSESYSEN      LL_RCC_LSE_EnablePropagation
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnablePropagation(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);
}

/**
  * @brief  Disable LSE oscillator propagation for system clock
  * @rmtoll BDCR         LSESYSEN      LL_RCC_LSE_DisablePropagation
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisablePropagation(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);
}

/**
  * @brief  Check if LSE oscillator propagation for system clock Ready
  * @rmtoll BDCR         LSEYSRDY     LL_RCC_LSE_IsPropagationReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsPropagationReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) == (RCC_BDCR_LSESYSRDY)) ? 1UL : 0UL);
}


/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll BDCR         LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == (RCC_BDCR_LSERDY)) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSS on LSE failure Detection
  * @rmtoll BDCR         LSECSSD       LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSD) == (RCC_BDCR_LSECSSD)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */


/**
  * @brief  Set LSI division factor
  * @rmtoll CSR          LSIPRE     LL_RCC_LSI_SetPrediv
  * @param  LSI_PREDIV This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSI_PREDIV_1
  *         @arg @ref LL_RCC_LSI_PREDIV_128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_SetPrediv(uint32_t LSI_PREDIV)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_LSIPRE, LSI_PREDIV);
}

/**
  * @brief  Get LSI division factor
  * @rmtoll CSR          LSIPRE     LL_RCC_LSI_GetPrediv
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSI_PREDIV_1
  *         @arg @ref LL_RCC_LSI_PREDIV_128
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_GetPrediv(void)
{
  return (READ_BIT(RCC->CSR, RCC_CSR_LSIPRE));
}


/**
  * @brief  Enable LSI Oscillator
  * @rmtoll CSR          LSION         LL_RCC_LSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  SET_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Disable LSI Oscillator
  * @rmtoll CSR          LSION         LL_RCC_LSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Check if LSI is Ready
  * @rmtoll CSR          LSIRDY        LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == (RCC_CSR_LSIRDY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MSI MSI
  * @{
  */

/**
  * @brief  Enable MSI oscillator
  * @rmtoll CR           MSION         LL_RCC_MSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSION);
}

/**
  * @brief  Disable MSI oscillator
  * @rmtoll CR           MSION         LL_RCC_MSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSION);
}

/**
  * @brief  Check if MSI oscillator Ready
  * @rmtoll CR           MSIRDY        LL_RCC_MSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIRDY) == (RCC_CR_MSIRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSI PLL-mode (Hardware auto calibration with LSE)
  * @note MSIPLLEN must be enabled after LSE is enabled (LSEON enabled)
  *       and ready (LSERDY set by hardware)
  * @note hardware protection to avoid enabling MSIPLLEN if LSE is not
  *       ready
  * @rmtoll CR           MSIPLLEN      LL_RCC_MSI_EnablePLLMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_EnablePLLMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Disable MSI-PLL mode
  * @note cleared by hardware when LSE is disabled (LSEON = 0) or when
  *       the Clock Security System on LSE detects a LSE failure
  * @rmtoll CR           MSIPLLEN      LL_RCC_MSI_DisablePLLMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_DisablePLLMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Enable MSI clock range selection with MSIRANGE register
  * @note Write 0 has no effect. After a standby or a reset
  *       MSIRGSEL is at 0 and the MSI range value is provided by
  *       MSISRANGE
  * @rmtoll CR           MSIRGSEL      LL_RCC_MSI_EnableRangeSelection
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_EnableRangeSelection(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIRGSEL);
}

/**
  * @brief  Check if MSI clock range is selected with MSIRANGE register
  * @rmtoll CR           MSIRGSEL      LL_RCC_MSI_IsEnabledRangeSelect
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_IsEnabledRangeSelect(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIRGSEL) == (RCC_CR_MSIRGSEL)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the Internal Multi Speed oscillator (MSI) clock range in run mode.
  * @rmtoll CR           MSIRANGE      LL_RCC_MSI_SetRange
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGE_0
  *         @arg @ref LL_RCC_MSIRANGE_1
  *         @arg @ref LL_RCC_MSIRANGE_2
  *         @arg @ref LL_RCC_MSIRANGE_3
  *         @arg @ref LL_RCC_MSIRANGE_4
  *         @arg @ref LL_RCC_MSIRANGE_5
  *         @arg @ref LL_RCC_MSIRANGE_6
  *         @arg @ref LL_RCC_MSIRANGE_7
  *         @arg @ref LL_RCC_MSIRANGE_8
  *         @arg @ref LL_RCC_MSIRANGE_9
  *         @arg @ref LL_RCC_MSIRANGE_10
  *         @arg @ref LL_RCC_MSIRANGE_11
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetRange(uint32_t Range)
{
  MODIFY_REG(RCC->CR, RCC_CR_MSIRANGE, Range);
}

/**
  * @brief  Get the Internal Multi Speed oscillator (MSI) clock range in run mode.
  * @rmtoll CR           MSIRANGE      LL_RCC_MSI_GetRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGE_0
  *         @arg @ref LL_RCC_MSIRANGE_1
  *         @arg @ref LL_RCC_MSIRANGE_2
  *         @arg @ref LL_RCC_MSIRANGE_3
  *         @arg @ref LL_RCC_MSIRANGE_4
  *         @arg @ref LL_RCC_MSIRANGE_5
  *         @arg @ref LL_RCC_MSIRANGE_6
  *         @arg @ref LL_RCC_MSIRANGE_7
  *         @arg @ref LL_RCC_MSIRANGE_8
  *         @arg @ref LL_RCC_MSIRANGE_9
  *         @arg @ref LL_RCC_MSIRANGE_10
  *         @arg @ref LL_RCC_MSIRANGE_11
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetRange(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_MSIRANGE));
}

/**
  * @brief  Configure MSI range used after standby
  * @rmtoll CSR          MSISRANGE     LL_RCC_MSI_SetRangeAfterStandby
  * @param  Range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetRangeAfterStandby(uint32_t Range)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_MSISRANGE, Range);
}

/**
  * @brief  Get MSI range used after standby
  * @rmtoll CSR          MSISRANGE     LL_RCC_MSI_GetRangeAfterStandby
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetRangeAfterStandby(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_MSISRANGE));
}

/**
  * @brief  Get MSI Calibration value
  * @note When MSITRIM is written, MSICAL is updated with the sum of
  *       MSITRIM and the factory trim value
  * @rmtoll ICSCR        MSICAL        LL_RCC_MSI_GetCalibration
  * @retval Between Min_Data = 0 and Max_Data = 255
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_MSICAL) >> RCC_ICSCR_MSICAL_Pos);
}

/**
  * @brief  Set MSI Calibration trimming
  * @note user-programmable trimming value that is added to the MSICAL
  * @rmtoll ICSCR        MSITRIM       LL_RCC_MSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0 and Max_Data = 255
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_MSITRIM, Value << RCC_ICSCR_MSITRIM_Pos);
}

/**
  * @brief  Get MSI Calibration trimming
  * @rmtoll ICSCR        MSITRIM       LL_RCC_MSI_GetCalibTrimming
  * @retval Between 0 and 255
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR, RCC_ICSCR_MSITRIM) >> RCC_ICSCR_MSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSCO LSCO
  * @{
  */

/**
  * @brief  Enable Low speed clock
  * @rmtoll BDCR         LSCOEN        LL_RCC_LSCO_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @brief  Disable Low speed clock
  * @rmtoll BDCR         LSCOEN        LL_RCC_LSCO_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @brief  Configure Low speed clock selection
  * @rmtoll BDCR         LSCOSEL       LL_RCC_LSCO_SetSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSCO_SetSource(uint32_t Source)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL, Source);
}

/**
  * @brief  Get Low speed clock selection
  * @rmtoll BDCR         LSCOSEL       LL_RCC_LSCO_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_LSCO_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_LSCOSEL));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_RF RF
  * @{
  */

/**
  * @brief  Enable radio reset
  * @rmtoll CSR           RFRST        LL_RCC_RF_EnableReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RF_EnableReset(void)
{
  SET_BIT(RCC->CSR, RCC_CSR_RFRST);
}

/**
  * @brief  Disable radio reset
  * @rmtoll CSR           RFRST        LL_RCC_RF_DisableReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RF_DisableReset(void)
{
  CLEAR_BIT(RCC->CSR, RCC_CSR_RFRST);
}

/**
  * @brief  Get radio reset
  * @rmtoll CSR           RFRST        LL_RCC_RF_IsEnabledReset
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_RF_IsEnabledReset(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_RFRST) == (RCC_CSR_RFRST)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Radio in reset is set or not.
  * @rmtoll CSR          RFRSTF      LL_RCC_IsRFUnderReset
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsRFUnderReset(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_RFRSTF) == (RCC_CSR_RFRSTF)) ? 1UL : 0UL);
}


/**
  * @}
  */


/** @defgroup RCC_LL_EF_System System
  * @{
  */

/**
  * @brief  Configure the system clock source
  * @rmtoll CFGR         SW            LL_RCC_SetSysClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_MSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_PLL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSysClkSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, Source);
}

/**
  * @brief  Get the system clock source
  * @rmtoll CFGR         SWS           LL_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_MSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_PLL
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}


/**
  * @brief  Set AHB prescaler
  * @rmtoll CFGR         HPRE          LL_RCC_SetAHBPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, Prescaler);
}

#if defined(DUAL_CORE)
/**
  * @brief  Set CPU2 AHB prescaler
  * @rmtoll EXTCFGR         C2HPRE          LL_C2_RCC_SetAHBPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_C2_RCC_SetAHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->EXTCFGR, RCC_EXTCFGR_C2HPRE, Prescaler);
}
#endif /* DUAL_CORE */

/**
  * @brief  Set AHB3 prescaler
  * @rmtoll EXTCFGR         SHDHPRE          LL_RCC_SetAHB3Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHB3Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->EXTCFGR, RCC_EXTCFGR_SHDHPRE, Prescaler >> 4);
}

/**
  * @brief  Set APB1 prescaler
  * @rmtoll CFGR         PPRE1         LL_RCC_SetAPB1Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB1Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, Prescaler);
}

/**
  * @brief  Set APB2 prescaler
  * @rmtoll CFGR         PPRE2         LL_RCC_SetAPB2Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB2Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, Prescaler);
}

/**
  * @brief  Get AHB prescaler
  * @rmtoll CFGR         HPRE          LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_HPRE));
}

#if defined(DUAL_CORE)
/**
  * @brief  Get C2 AHB prescaler
  * @rmtoll EXTCFGR         C2HPRE          LL_C2_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  */
__STATIC_INLINE uint32_t LL_C2_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->EXTCFGR, RCC_EXTCFGR_C2HPRE));
}
#endif /* DUAL_CORE */

/**
  * @brief  Get AHB3 prescaler
  * @rmtoll EXTCFGR         SHDHPRE          LL_RCC_GetAHB3Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_3
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_5
  *         @arg @ref LL_RCC_SYSCLK_DIV_6
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_10
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_32
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHB3Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->EXTCFGR, RCC_EXTCFGR_SHDHPRE) << 4);
}

/**
  * @brief  Get APB1 prescaler
  * @rmtoll CFGR         PPRE1         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1));
}

/**
  * @brief  Get APB2 prescaler
  * @rmtoll CFGR         PPRE2         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE2));
}

/**
  * @brief  Set Clock After Wake-Up From Stop mode
  * @rmtoll CFGR         STOPWUCK      LL_RCC_SetClkAfterWakeFromStop
  * @param  Clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_MSI
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetClkAfterWakeFromStop(uint32_t Clock)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPWUCK, Clock);
}

/**
  * @brief  Get Clock After Wake-Up From Stop mode
  * @rmtoll CFGR         STOPWUCK      LL_RCC_GetClkAfterWakeFromStop
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_MSI
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetClkAfterWakeFromStop(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_STOPWUCK));
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_MCO MCO
  * @{
  */

/**
  * @brief  Configure MCOx
  * @rmtoll CFGR         MCOSEL        LL_RCC_ConfigMCO\n
  *         CFGR         MCOPRE        LL_RCC_ConfigMCO
  * @param  MCOxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO1SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_MSI
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_PLLCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_LSI
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  *         @arg @ref LL_RCC_MCO1SOURCE_PLLQCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_PLLPCLK
  * @param  MCOxPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1_DIV_1
  *         @arg @ref LL_RCC_MCO1_DIV_2
  *         @arg @ref LL_RCC_MCO1_DIV_4
  *         @arg @ref LL_RCC_MCO1_DIV_8
  *         @arg @ref LL_RCC_MCO1_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t MCOxSource, uint32_t MCOxPrescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCOSEL | RCC_CFGR_MCOPRE, MCOxSource | MCOxPrescaler);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Configure USARTx clock source
  * @rmtoll CCIPR        USART1SEL     LL_RCC_SetUSARTClockSource
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t USARTxSource)
{
  MODIFY_REG(RCC->CCIPR, (USARTxSource >> 16), (USARTxSource & 0x0000FFFFU));
}

/**
  * @brief  Configure I2Sx clock source
  * @rmtoll CCIPR        I2S2SEL       LL_RCC_SetI2SClockSource
  * @param  I2SxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2S2_CLKSOURCE_PLL
  *         @arg @ref LL_RCC_I2S2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2S2_CLKSOURCE_PIN
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2SClockSource(uint32_t I2SxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_I2S2SEL, I2SxSource);
}

/**
  * @brief  Configure LPUARTx clock source
  * @rmtoll CCIPR        LPUART1SEL    LL_RCC_SetLPUARTClockSource
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t LPUARTxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_LPUART1SEL, LPUARTxSource);
}

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll CCIPR        I2CxSEL       LL_RCC_SetI2CClockSource
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t I2CxSource)
{
  MODIFY_REG(RCC->CCIPR, ((I2CxSource >> 4) & 0x000FF000U), ((I2CxSource << 4) & 0x000FF000U));
}

/**
  * @brief  Configure LPTIMx clock source
  * @rmtoll CCIPR        LPTIMxSEL     LL_RCC_SetLPTIMClockSource
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t LPTIMxSource)
{
  MODIFY_REG(RCC->CCIPR, (LPTIMxSource & 0xFFFF0000U), (LPTIMxSource << 16));
}

/**
  * @brief  Configure RNG clock source
  * @rmtoll CCIPR        RNGSEL      LL_RCC_SetRNGClockSource
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_PLL
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_MSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRNGClockSource(uint32_t RNGxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_RNGSEL, RNGxSource);
}


/**
  * @brief  Configure ADC clock source
  * @rmtoll CCIPR        ADCSEL        LL_RCC_SetADCClockSource
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_SYSCLK
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADCClockSource(uint32_t ADCxSource)
{
  MODIFY_REG(RCC->CCIPR, RCC_CCIPR_ADCSEL, ADCxSource);
}

/**
  * @brief  Get USARTx clock source
  * @rmtoll CCIPR        USART1SEL     LL_RCC_GetUSARTClockSource
  * @param  USARTx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t USARTx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, USARTx) | (USARTx << 16));
}

/**
  * @brief  Get I2Sx clock source
  * @rmtoll CCIPR        I2S2SEL        LL_RCC_GetI2SClockSource
  * @param  I2Sx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2S2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2S2_CLKSOURCE_PLL
  *         @arg @ref LL_RCC_I2S2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2S2_CLKSOURCE_PIN
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2SClockSource(uint32_t I2Sx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, I2Sx));
}

/**
  * @brief  Get LPUARTx clock source
  * @rmtoll CCIPR        LPUART1SEL    LL_RCC_GetLPUARTClockSource
  * @param  LPUARTx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t LPUARTx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, LPUARTx));
}

/**
  * @brief  Get I2Cx clock source
  * @rmtoll CCIPR        I2CxSEL       LL_RCC_GetI2CClockSource
  * @param  I2Cx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t I2Cx)
{
  return (uint32_t)((READ_BIT(RCC->CCIPR, I2Cx) >> 4) | (I2Cx << 4));
}

/**
  * @brief  Get LPTIMx clock source
  * @rmtoll CCIPR        LPTIMxSEL     LL_RCC_GetLPTIMClockSource
  * @param  LPTIMx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE_LSE

  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t LPTIMx)
{
  return (uint32_t)((READ_BIT(RCC->CCIPR, LPTIMx) >> 16) | LPTIMx);
}

/**
  * @brief  Get RNGx clock source
  * @rmtoll CCIPR        RNGSEL      LL_RCC_GetRNGClockSource
  * @param  RNGx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_PLL
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_MSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetRNGClockSource(uint32_t RNGx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, RNGx));
}

/**
  * @brief  Get ADCx clock source
  * @rmtoll CCIPR        ADCSEL        LL_RCC_GetADCClockSource
  * @param  ADCx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_SYSCLK
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCClockSource(uint32_t ADCx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR, ADCx));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source
  * @note Once the RTC clock source has been selected, it cannot be changed anymore unless
  *       the Backup domain is reset, or unless a failure is detected on LSE (LSECSSD is
  *       set). The BDRST bit can be used to reset them.
  * @rmtoll BDCR         RTCSEL        LL_RCC_SetRTCClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRTCClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, Source);
}

/**
  * @brief  Get RTC Clock Source
  * @rmtoll BDCR         RTCSEL        LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL));
}

/**
  * @brief  Enable RTC
  * @rmtoll BDCR         RTCEN         LL_RCC_EnableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Disable RTC
  * @rmtoll BDCR         RTCEN         LL_RCC_DisableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll BDCR         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_RTCEN) == (RCC_BDCR_RTCEN)) ? 1UL : 0UL);
}

/**
  * @brief  Force the Backup domain reset
  * @rmtoll BDCR         BDRST         LL_RCC_ForceBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll BDCR         BDRST         LL_RCC_ReleaseBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_PLL PLL
  * @{
  */

/**
  * @brief  Enable PLL
  * @rmtoll CR           PLLON         LL_RCC_PLL_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLLON);
}

/**
  * @brief  Disable PLL
  * @note Cannot be disabled if the PLL clock is used as the system clock
  * @rmtoll CR           PLLON         LL_RCC_PLL_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
}

/**
  * @brief  Check if PLL Ready
  * @rmtoll CR           PLLRDY        LL_RCC_PLL_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL used for SYSCLK Domain
  * @note PLL Source and PLLM Divider can be written only when PLL is disabled
  * @note PLLN/PLLR can be written only when PLL is disabled
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_ConfigDomain_SYS\n
  *         PLLCFGR      PLLM          LL_RCC_PLL_ConfigDomain_SYS\n
  *         PLLCFGR      PLLN          LL_RCC_PLL_ConfigDomain_SYS\n
  *         PLLCFGR      PLLR          LL_RCC_PLL_ConfigDomain_SYS
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  * @param  PLLM This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  PLLN Between 6 and 127
  * @param  PLLR This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLR_DIV_2
  *         @arg @ref LL_RCC_PLLR_DIV_3
  *         @arg @ref LL_RCC_PLLR_DIV_4
  *         @arg @ref LL_RCC_PLLR_DIV_5
  *         @arg @ref LL_RCC_PLLR_DIV_6
  *         @arg @ref LL_RCC_PLLR_DIV_7
  *         @arg @ref LL_RCC_PLLR_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_ConfigDomain_SYS(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLR)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLR,
             Source | PLLM | (PLLN << RCC_PLLCFGR_PLLN_Pos) | PLLR);
}

/**
  * @brief  Configure PLL used for ADC domain clock
  * @note PLL Source and PLLM Divider can be written only when PLL is disabled
  * @note PLLN/PLLP can be written only when PLL is disabled
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_ConfigDomain_ADC\n
  *         PLLCFGR      PLLM          LL_RCC_PLL_ConfigDomain_ADC\n
  *         PLLCFGR      PLLN          LL_RCC_PLL_ConfigDomain_ADC\n
  *         PLLCFGR      PLLP          LL_RCC_PLL_ConfigDomain_ADC
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  * @param  PLLM This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  PLLN Between 6 and 127
  * @param  PLLP This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLP_DIV_2
  *         @arg @ref LL_RCC_PLLP_DIV_3
  *         @arg @ref LL_RCC_PLLP_DIV_4
  *         @arg @ref LL_RCC_PLLP_DIV_5
  *         @arg @ref LL_RCC_PLLP_DIV_6
  *         @arg @ref LL_RCC_PLLP_DIV_7
  *         @arg @ref LL_RCC_PLLP_DIV_8
  *         @arg @ref LL_RCC_PLLP_DIV_9
  *         @arg @ref LL_RCC_PLLP_DIV_10
  *         @arg @ref LL_RCC_PLLP_DIV_11
  *         @arg @ref LL_RCC_PLLP_DIV_12
  *         @arg @ref LL_RCC_PLLP_DIV_13
  *         @arg @ref LL_RCC_PLLP_DIV_14
  *         @arg @ref LL_RCC_PLLP_DIV_15
  *         @arg @ref LL_RCC_PLLP_DIV_16
  *         @arg @ref LL_RCC_PLLP_DIV_17
  *         @arg @ref LL_RCC_PLLP_DIV_18
  *         @arg @ref LL_RCC_PLLP_DIV_19
  *         @arg @ref LL_RCC_PLLP_DIV_20
  *         @arg @ref LL_RCC_PLLP_DIV_21
  *         @arg @ref LL_RCC_PLLP_DIV_22
  *         @arg @ref LL_RCC_PLLP_DIV_23
  *         @arg @ref LL_RCC_PLLP_DIV_24
  *         @arg @ref LL_RCC_PLLP_DIV_25
  *         @arg @ref LL_RCC_PLLP_DIV_26
  *         @arg @ref LL_RCC_PLLP_DIV_27
  *         @arg @ref LL_RCC_PLLP_DIV_28
  *         @arg @ref LL_RCC_PLLP_DIV_29
  *         @arg @ref LL_RCC_PLLP_DIV_30
  *         @arg @ref LL_RCC_PLLP_DIV_31
  *         @arg @ref LL_RCC_PLLP_DIV_32
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_ConfigDomain_ADC(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP,
             Source | PLLM | (PLLN << RCC_PLLCFGR_PLLN_Pos) | PLLP);
}

/**
  * @brief  Configure PLL used for RNG domain clock
  * @note PLL Source and PLLM Divider can be written only when PLL is disabled
  * @note PLLN/PLLQ can be written only when PLL is disabled
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_ConfigDomain_RNG\n
  *         PLLCFGR      PLLM          LL_RCC_PLL_ConfigDomain_RNG\n
  *         PLLCFGR      PLLN          LL_RCC_PLL_ConfigDomain_RNG\n
  *         PLLCFGR      PLLQ          LL_RCC_PLL_ConfigDomain_RNG
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  * @param  PLLM This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  PLLN Between 6 and 127
  * @param  PLLQ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLQ_DIV_2
  *         @arg @ref LL_RCC_PLLQ_DIV_3
  *         @arg @ref LL_RCC_PLLQ_DIV_4
  *         @arg @ref LL_RCC_PLLQ_DIV_5
  *         @arg @ref LL_RCC_PLLQ_DIV_6
  *         @arg @ref LL_RCC_PLLQ_DIV_7
  *         @arg @ref LL_RCC_PLLQ_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_ConfigDomain_RNG(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLQ)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLQ,
             Source | PLLM | (PLLN << RCC_PLLCFGR_PLLN_Pos) | PLLQ);
}

/**
  * @brief  Configure PLL used for I2S domain clock
  * @note PLL Source and PLLM Divider can be written only when PLL is disabled
  * @note PLLN/PLLQ can be written only when PLL is disabled
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_ConfigDomain_I2S\n
  *         PLLCFGR      PLLM          LL_RCC_PLL_ConfigDomain_I2S\n
  *         PLLCFGR      PLLN          LL_RCC_PLL_ConfigDomain_I2S\n
  *         PLLCFGR      PLLQ          LL_RCC_PLL_ConfigDomain_I2S
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  * @param  PLLM This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  * @param  PLLN Between 6 and 127
  * @param  PLLQ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLQ_DIV_2
  *         @arg @ref LL_RCC_PLLQ_DIV_3
  *         @arg @ref LL_RCC_PLLQ_DIV_4
  *         @arg @ref LL_RCC_PLLQ_DIV_5
  *         @arg @ref LL_RCC_PLLQ_DIV_6
  *         @arg @ref LL_RCC_PLLQ_DIV_7
  *         @arg @ref LL_RCC_PLLQ_DIV_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_ConfigDomain_I2S(uint32_t Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLQ)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLQ,
             Source | PLLM | (PLLN << RCC_PLLCFGR_PLLN_Pos) | PLLQ);
}

/**
  * @brief  Get Main PLL multiplication factor for VCO
  * @rmtoll PLLCFGR      PLLN          LL_RCC_PLL_GetN
  * @retval Between 6 and 127
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >>  RCC_PLLCFGR_PLLN_Pos);
}

/**
  * @brief  Get Main PLL division factor for PLLP
  * @rmtoll PLLCFGR      PLLP       LL_RCC_PLL_GetP
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLP_DIV_2
  *         @arg @ref LL_RCC_PLLP_DIV_3
  *         @arg @ref LL_RCC_PLLP_DIV_4
  *         @arg @ref LL_RCC_PLLP_DIV_5
  *         @arg @ref LL_RCC_PLLP_DIV_6
  *         @arg @ref LL_RCC_PLLP_DIV_7
  *         @arg @ref LL_RCC_PLLP_DIV_8
  *         @arg @ref LL_RCC_PLLP_DIV_9
  *         @arg @ref LL_RCC_PLLP_DIV_10
  *         @arg @ref LL_RCC_PLLP_DIV_11
  *         @arg @ref LL_RCC_PLLP_DIV_12
  *         @arg @ref LL_RCC_PLLP_DIV_13
  *         @arg @ref LL_RCC_PLLP_DIV_14
  *         @arg @ref LL_RCC_PLLP_DIV_15
  *         @arg @ref LL_RCC_PLLP_DIV_16
  *         @arg @ref LL_RCC_PLLP_DIV_17
  *         @arg @ref LL_RCC_PLLP_DIV_18
  *         @arg @ref LL_RCC_PLLP_DIV_19
  *         @arg @ref LL_RCC_PLLP_DIV_20
  *         @arg @ref LL_RCC_PLLP_DIV_21
  *         @arg @ref LL_RCC_PLLP_DIV_22
  *         @arg @ref LL_RCC_PLLP_DIV_23
  *         @arg @ref LL_RCC_PLLP_DIV_24
  *         @arg @ref LL_RCC_PLLP_DIV_25
  *         @arg @ref LL_RCC_PLLP_DIV_26
  *         @arg @ref LL_RCC_PLLP_DIV_27
  *         @arg @ref LL_RCC_PLLP_DIV_28
  *         @arg @ref LL_RCC_PLLP_DIV_29
  *         @arg @ref LL_RCC_PLLP_DIV_30
  *         @arg @ref LL_RCC_PLLP_DIV_31
  *         @arg @ref LL_RCC_PLLP_DIV_32
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetP(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP));
}

/**
  * @brief  Get Main PLL division factor for PLLQ
  * @note used for PLL48MCLK selected for USB, RNG (48 MHz clock)
  * @rmtoll PLLCFGR      PLLQ          LL_RCC_PLL_GetQ
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLQ_DIV_2
  *         @arg @ref LL_RCC_PLLQ_DIV_3
  *         @arg @ref LL_RCC_PLLQ_DIV_4
  *         @arg @ref LL_RCC_PLLQ_DIV_5
  *         @arg @ref LL_RCC_PLLQ_DIV_6
  *         @arg @ref LL_RCC_PLLQ_DIV_7
  *         @arg @ref LL_RCC_PLLQ_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetQ(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ));
}

/**
  * @brief  Get Main PLL division factor for PLLR
  * @note used for PLLCLK (system clock)
  * @rmtoll PLLCFGR      PLLR          LL_RCC_PLL_GetR
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLR_DIV_2
  *         @arg @ref LL_RCC_PLLR_DIV_3
  *         @arg @ref LL_RCC_PLLR_DIV_4
  *         @arg @ref LL_RCC_PLLR_DIV_5
  *         @arg @ref LL_RCC_PLLR_DIV_6
  *         @arg @ref LL_RCC_PLLR_DIV_7
  *         @arg @ref LL_RCC_PLLR_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetR(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLR));
}

/**
  * @brief  Get Division factor for the main PLL and other PLL
  * @rmtoll PLLCFGR      PLLM          LL_RCC_PLL_GetDivider
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLM_DIV_1
  *         @arg @ref LL_RCC_PLLM_DIV_2
  *         @arg @ref LL_RCC_PLLM_DIV_3
  *         @arg @ref LL_RCC_PLLM_DIV_4
  *         @arg @ref LL_RCC_PLLM_DIV_5
  *         @arg @ref LL_RCC_PLLM_DIV_6
  *         @arg @ref LL_RCC_PLLM_DIV_7
  *         @arg @ref LL_RCC_PLLM_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetDivider(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM));
}

/**
  * @brief  Enable PLL output mapped on ADC domain clock
  * @rmtoll PLLCFGR      PLLPEN        LL_RCC_PLL_EnableDomain_ADC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_EnableDomain_ADC(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN);
}

/**
  * @brief  Disable PLL output mapped on ADC domain clock
  * @note In order to save power, when the PLLCLK  of the PLL is
  *       not used,  should be 0
  * @rmtoll PLLCFGR      PLLPEN        LL_RCC_PLL_DisableDomain_ADC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_DisableDomain_ADC(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN);
}


/**
  * @brief  Enable PLL output mapped on RNG domain clock
  * @rmtoll PLLCFGR      PLLQEN        LL_RCC_PLL_EnableDomain_RNG
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_EnableDomain_RNG(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQEN);
}

/**
  * @brief  Disable PLL output mapped on RNG domain clock
  * @note In order to save power, when the PLLCLK  of the PLL is
  *       not used,  should be 0
  * @rmtoll PLLCFGR      PLLQEN        LL_RCC_PLL_DisableDomain_RNG
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_DisableDomain_RNG(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQEN);
}

/**
  * @brief  Enable PLL output mapped on I2S domain clock
  * @rmtoll PLLCFGR      PLLQEN        LL_RCC_PLL_EnableDomain_I2S
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_EnableDomain_I2S(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQEN);
}

/**
  * @brief  Disable PLL output mapped on I2S domain clock
  * @note In order to save power, when the PLLCLK  of the PLL is
  *       not used,  should be 0
  * @rmtoll PLLCFGR      PLLQEN        LL_RCC_PLL_DisableDomain_I2S
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_DisableDomain_I2S(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQEN);
}

/**
  * @brief  Enable PLL output mapped on SYSCLK domain
  * @rmtoll PLLCFGR      PLLREN        LL_RCC_PLL_EnableDomain_SYS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_EnableDomain_SYS(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN);
}

/**
  * @brief  Disable PLL output mapped on SYSCLK domain
  * @note Cannot be disabled if the PLL clock is used as the system clock
  * @note In order to save power, when the PLLCLK  of the PLL is
  *       not used, Main PLL  should be 0
  * @rmtoll PLLCFGR      PLLREN        LL_RCC_PLL_DisableDomain_SYS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_DisableDomain_SYS(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN);
}

/**
  * @brief  Configure PLL clock source
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_SetMainSource
  * @param PLLSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_SetMainSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL clock source.
  * @rmtoll PLLCFGR      PLLSRC        LL_RCC_PLL_GetMainSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  *         @arg @ref LL_RCC_PLLSOURCE_MSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetMainSource(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC));
}

/**
  * @}
  */



/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear LSI ready interrupt flag
  * @rmtoll CICR         LSIRDYC       LL_RCC_ClearFlag_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSIRDYC);
}

/**
  * @brief  Clear LSE ready interrupt flag
  * @rmtoll CICR         LSERDYC       LL_RCC_ClearFlag_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSERDYC);
}

/**
  * @brief  Clear MSI ready interrupt flag
  * @rmtoll CICR         MSIRDYC       LL_RCC_ClearFlag_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSIRDYC);
}

/**
  * @brief  Clear HSI ready interrupt flag
  * @rmtoll CICR         HSIRDYC       LL_RCC_ClearFlag_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSIRDYC);
}

/**
  * @brief  Clear HSE ready interrupt flag
  * @rmtoll CICR         HSERDYC       LL_RCC_ClearFlag_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSERDYC);
}

/**
  * @brief  Clear PLL ready interrupt flag
  * @rmtoll CICR         PLLRDYC       LL_RCC_ClearFlag_PLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLLRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLLRDYC);
}

/**
  * @brief  Clear Clock security system interrupt flag
  * @rmtoll CICR         CSSC          LL_RCC_ClearFlag_HSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_CSSC);
}

/**
  * @brief  Clear LSE Clock security system interrupt flag
  * @rmtoll CICR         LSECSSC       LL_RCC_ClearFlag_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSECSSC);
}

/**
  * @brief  Check if LSI ready interrupt occurred or not
  * @rmtoll CIFR         LSIRDYF       LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSIRDYF) == (RCC_CIFR_LSIRDYF)) ? 1UL : 0UL);

}

/**
  * @brief  Check if LSE ready interrupt occurred or not
  * @rmtoll CIFR         LSERDYF       LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSERDYF) == (RCC_CIFR_LSERDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSI ready interrupt occurred or not
  * @rmtoll CIFR         MSIRDYF       LL_RCC_IsActiveFlag_MSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSIRDYF) == (RCC_CIFR_MSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt occurred or not
  * @rmtoll CIFR         HSIRDYF       LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIRDYF) == (RCC_CIFR_HSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll CIFR         HSERDYF       LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == (RCC_CIFR_HSERDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL ready interrupt occurred or not
  * @rmtoll CIFR         PLLRDYF       LL_RCC_IsActiveFlag_PLLRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLLRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLLRDYF) == (RCC_CIFR_PLLRDYF)) ? 1UL : 0UL);

}

/**
  * @brief  Check if Clock security system interrupt occurred or not
  * @rmtoll CIFR         CSSF          LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_CSSF) == (RCC_CIFR_CSSF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE Clock security system interrupt occurred or not
  * @rmtoll CIFR         LSECSSF       LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSECSSF) == (RCC_CIFR_LSECSSF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HCLK1 prescaler flag value has been applied or not
  * @rmtoll CFGR         HPREF       LL_RCC_IsActiveFlag_HPRE
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HPRE(void)
{
  return ((READ_BIT(RCC->CFGR, RCC_CFGR_HPREF) == (RCC_CFGR_HPREF)) ? 1UL : 0UL);
}

#if defined(DUAL_CORE)
/**
  * @brief  Check if HCLK2 prescaler flag value has been applied or not
  * @rmtoll EXTCFGR         C2HPREF       LL_RCC_IsActiveFlag_C2HPRE
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_C2HPRE(void)
{
  return ((READ_BIT(RCC->EXTCFGR, RCC_EXTCFGR_C2HPREF) == (RCC_EXTCFGR_C2HPREF)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  Check if HCLK3 prescaler flag value has been applied or not
  * @rmtoll EXTCFGR         SHDHPREF       LL_RCC_IsActiveFlag_SHDHPRE
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SHDHPRE(void)
{
  return ((READ_BIT(RCC->EXTCFGR, RCC_EXTCFGR_SHDHPREF) == (RCC_EXTCFGR_SHDHPREF)) ? 1UL : 0UL);
}


/**
  * @brief  Check if PLCK1 prescaler flag value has been applied or not
  * @rmtoll CFGR         PPRE1F       LL_RCC_IsActiveFlag_PPRE1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PPRE1(void)
{
  return ((READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1F) == (RCC_CFGR_PPRE1F)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLCK2 prescaler flag value has been applied or not
  * @rmtoll CFGR         PPRE2F       LL_RCC_IsActiveFlag_PPRE2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PPRE2(void)
{
  return ((READ_BIT(RCC->CFGR, RCC_CFGR_PPRE2F) == (RCC_CFGR_PPRE2F)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Independent Watchdog reset is set or not.
  * @rmtoll CSR          IWDGRSTF      LL_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_IWDGRSTF) == (RCC_CSR_IWDGRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Radio illegal access is set or not.
  * @rmtoll CSR          RFILARSTF      LL_RCC_IsActiveFlag_RFILARST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_RFILARST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_RFILARSTF) == (RCC_CSR_RFILARSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Low Power reset is set or not.
  * @rmtoll CSR          LPWRRSTF      LL_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPWRRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_LPWRRSTF) == (RCC_CSR_LPWRRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Option byte reset is set or not.
  * @rmtoll CSR          OBLRSTF       LL_RCC_IsActiveFlag_OBLRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_OBLRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_OBLRSTF) == (RCC_CSR_OBLRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Pin reset is set or not.
  * @rmtoll CSR          PINRSTF       LL_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PINRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_PINRSTF) == (RCC_CSR_PINRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Software reset is set or not.
  * @rmtoll CSR          SFTRSTF       LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_SFTRSTF) == (RCC_CSR_SFTRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Window Watchdog reset is set or not.
  * @rmtoll CSR          WWDGRSTF      LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_WWDGRSTF) == (RCC_CSR_WWDGRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag BOR reset is set or not.
  * @rmtoll CSR          BORRSTF       LL_RCC_IsActiveFlag_BORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_BORRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_BORRSTF) == (RCC_CSR_BORRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Set RMVF bit to clear the reset flags.
  * @rmtoll CSR          RMVF          LL_RCC_ClearResetFlags
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll CIER         LSIRDYIE      LL_RCC_EnableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Enable LSE ready interrupt
  * @rmtoll CIER         LSERDYIE      LL_RCC_EnableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Enable MSI ready interrupt
  * @rmtoll CIER         MSIRDYIE      LL_RCC_EnableIT_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSIRDYIE);
}

/**
  * @brief  Enable HSI ready interrupt
  * @rmtoll CIER         HSIRDYIE      LL_RCC_EnableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Enable HSE ready interrupt
  * @rmtoll CIER         HSERDYIE      LL_RCC_EnableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Enable PLL ready interrupt
  * @rmtoll CIER         PLLRDYIE      LL_RCC_EnableIT_PLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLLRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLLRDYIE);
}

/**
  * @brief  Enable LSE clock security system interrupt
  * @rmtoll CIER         LSECSSIE      LL_RCC_EnableIT_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSECSS(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSECSSIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll CIER         LSIRDYIE      LL_RCC_DisableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Disable LSE ready interrupt
  * @rmtoll CIER         LSERDYIE      LL_RCC_DisableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Disable MSI ready interrupt
  * @rmtoll CIER         MSIRDYIE      LL_RCC_DisableIT_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSIRDYIE);
}

/**
  * @brief  Disable HSI ready interrupt
  * @rmtoll CIER         HSIRDYIE      LL_RCC_DisableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Disable HSE ready interrupt
  * @rmtoll CIER         HSERDYIE      LL_RCC_DisableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Disable PLL ready interrupt
  * @rmtoll CIER         PLLRDYIE      LL_RCC_DisableIT_PLLRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLLRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLLRDYIE);
}

/**
  * @brief  Disable LSE clock security system interrupt
  * @rmtoll CIER         LSECSSIE      LL_RCC_DisableIT_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSECSS(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSECSSIE);
}

/**
  * @brief  Checks if LSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSIRDYIE      LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSIRDYIE) == (RCC_CIER_LSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if LSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSERDYIE      LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSERDYIE) == (RCC_CIER_LSERDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if MSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         MSIRDYIE      LL_RCC_IsEnabledIT_MSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSIRDYIE) == (RCC_CIER_MSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSIRDYIE      LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIRDYIE) == (RCC_CIER_HSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSERDYIE      LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == (RCC_CIER_HSERDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL ready interrupt source is enabled or disabled.
  * @rmtoll CIER         PLLRDYIE      LL_RCC_IsEnabledIT_PLLRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLLRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLLRDYIE) == (RCC_CIER_PLLRDYIE)) ? 1UL : 0UL);

}

/**
  * @brief  Checks if LSECSS interrupt source is enabled or disabled.
  * @rmtoll CIER         LSECSSIE      LL_RCC_IsEnabledIT_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSECSS(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSECSSIE) == (RCC_CIER_LSECSSIE)) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_RCC_DeInit(void);
/**
  * @}
  */

/** @defgroup RCC_LL_EF_Get_Freq Get system and peripherals clocks frequency functions
  * @{
  */
void        LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks);
uint32_t    LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource);
uint32_t    LL_RCC_GetI2CClockFreq(uint32_t I2CxSource);
uint32_t    LL_RCC_GetI2SClockFreq(uint32_t I2SxSource);
uint32_t    LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource);
uint32_t    LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource);
uint32_t    LL_RCC_GetRNGClockFreq(uint32_t RNGxSource);
uint32_t    LL_RCC_GetADCClockFreq(uint32_t ADCxSource);
uint32_t    LL_RCC_GetRTCClockFreq(void);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32WLxx_LL_RCC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
