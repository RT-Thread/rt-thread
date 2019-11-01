/**
  ******************************************************************************
  * @file    stm32g4xx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL module.
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
#ifndef STM32G4xx_HAL_RCC_H
#define STM32G4xx_HAL_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
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

  uint32_t PLLSource;  /*!< RCC_PLLSource: PLL entry clock source.
                            This parameter must be a value of @ref RCC_PLL_Clock_Source               */

  uint32_t PLLM;       /*!< PLLM: Division factor for PLL VCO input clock.
                            This parameter must be a value of @ref RCC_PLLM_Clock_Divider             */

  uint32_t PLLN;       /*!< PLLN: Multiplication factor for PLL VCO output clock.
                            This parameter must be a number between Min_Data = 8 and Max_Data = 127    */

  uint32_t PLLP;       /*!< PLLP: Division factor for ADC clock.
                            This parameter must be a value of @ref RCC_PLLP_Clock_Divider             */

  uint32_t PLLQ;       /*!< PLLQ: Division factor for SAI, I2S, USB, FDCAN and QUADSPI clocks.
                            This parameter must be a value of @ref RCC_PLLQ_Clock_Divider             */

  uint32_t PLLR;       /*!< PLLR: Division for the main system clock.
                            User have to set the PLLR parameter correctly to not exceed max frequency 170MHZ.
                            This parameter must be a value of @ref RCC_PLLR_Clock_Divider             */

}RCC_PLLInitTypeDef;

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition
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

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  uint32_t HSI48State;             /*!< The new state of the HSI48.
                                        This parameter can be a value of @ref RCC_HSI48_Config */

  RCC_PLLInitTypeDef PLL;        /*!< Main PLL structure parameters                                               */

}RCC_OscInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a value of @ref RCC_System_Clock_Type      */

  uint32_t SYSCLKSource;          /*!< The clock source used as system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_AHB_Clock_Source       */

  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

  uint32_t APB2CLKDivider;        /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

}RCC_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Timeout_Value Timeout Values
  * @{
  */
#define RCC_DBP_TIMEOUT_VALUE          2U                        /* 2 ms (minimum Tick + 1) */
#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT
/**
  * @}
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE        0x00000000U               /*!< Oscillator configuration unchanged */
#define RCC_OSCILLATORTYPE_HSE         0x00000001U               /*!< HSE to configure */
#define RCC_OSCILLATORTYPE_HSI         0x00000002U               /*!< HSI to configure */
#define RCC_OSCILLATORTYPE_LSE         0x00000004U               /*!< LSE to configure */
#define RCC_OSCILLATORTYPE_LSI         0x00000008U               /*!< LSI to configure */
#define RCC_OSCILLATORTYPE_HSI48       0x00000020U               /*!< HSI48 to configure */
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                    0x00000000U                                /*!< HSE clock deactivation */
#define RCC_HSE_ON                     RCC_CR_HSEON                               /*!< HSE clock activation */
#define RCC_HSE_BYPASS                 (RCC_CR_HSEBYP | RCC_CR_HSEON)             /*!< External clock source for HSE clock */
/**
  * @}
  */

/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                    0x00000000U                                    /*!< LSE clock deactivation */
#define RCC_LSE_ON                     RCC_BDCR_LSEON                                 /*!< LSE clock activation */
#define RCC_LSE_BYPASS                 (RCC_BDCR_LSEBYP | RCC_BDCR_LSEON)             /*!< External clock source for LSE clock */
/**
  * @}
  */

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                    0x00000000U            /*!< HSI clock deactivation */
#define RCC_HSI_ON                     RCC_CR_HSION           /*!< HSI clock activation */
#define RCC_HSICALIBRATION_DEFAULT     0x40U                  /* Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U            /*!< LSI clock deactivation */
#define RCC_LSI_ON                     RCC_CSR_LSION          /*!< LSI clock activation */
/**
  * @}
  */

/** @defgroup RCC_HSI48_Config HSI48 Config
  * @{
  */
#define RCC_HSI48_OFF                  0x00000000U            /*!< HSI48 clock deactivation */
#define RCC_HSI48_ON                   RCC_CRRCR_HSI48ON      /*!< HSI48 clock activation */
/**
  * @}
  */

/** @defgroup RCC_PLL_Config PLL Config
  * @{
  */
#define RCC_PLL_NONE                   0x00000000U            /*!< PLL configuration unchanged */
#define RCC_PLL_OFF                    0x00000001U            /*!< PLL deactivation */
#define RCC_PLL_ON                     0x00000002U            /*!< PLL activation */
/**
  * @}
  */

/** @defgroup RCC_PLLM_Clock_Divider PLLM Clock Divider
  * @{
  */
#define RCC_PLLM_DIV1                  0x00000001U             /*!< PLLM division factor = 1  */
#define RCC_PLLM_DIV2                  0x00000002U             /*!< PLLM division factor = 2  */
#define RCC_PLLM_DIV3                  0x00000003U             /*!< PLLM division factor = 3  */
#define RCC_PLLM_DIV4                  0x00000004U             /*!< PLLM division factor = 4  */
#define RCC_PLLM_DIV5                  0x00000005U             /*!< PLLM division factor = 5  */
#define RCC_PLLM_DIV6                  0x00000006U             /*!< PLLM division factor = 6  */
#define RCC_PLLM_DIV7                  0x00000007U             /*!< PLLM division factor = 7  */
#define RCC_PLLM_DIV8                  0x00000008U             /*!< PLLM division factor = 8  */
#define RCC_PLLM_DIV9                  0x00000009U             /*!< PLLM division factor = 9  */
#define RCC_PLLM_DIV10                 0x0000000AU             /*!< PLLM division factor = 10 */
#define RCC_PLLM_DIV11                 0x0000000BU             /*!< PLLM division factor = 11 */
#define RCC_PLLM_DIV12                 0x0000000CU             /*!< PLLM division factor = 12 */
#define RCC_PLLM_DIV13                 0x0000000DU             /*!< PLLM division factor = 13 */
#define RCC_PLLM_DIV14                 0x0000000EU             /*!< PLLM division factor = 14 */
#define RCC_PLLM_DIV15                 0x0000000FU             /*!< PLLM division factor = 15 */
#define RCC_PLLM_DIV16                 0x00000010U             /*!< PLLM division factor = 16 */
/**
  * @}
  */

/** @defgroup RCC_PLLP_Clock_Divider PLLP Clock Divider
  * @{
  */
#define RCC_PLLP_DIV2                  0x00000002U             /*!< PLLP division factor = 2  */
#define RCC_PLLP_DIV3                  0x00000003U             /*!< PLLP division factor = 3  */
#define RCC_PLLP_DIV4                  0x00000004U             /*!< PLLP division factor = 4  */
#define RCC_PLLP_DIV5                  0x00000005U             /*!< PLLP division factor = 5  */
#define RCC_PLLP_DIV6                  0x00000006U             /*!< PLLP division factor = 6  */
#define RCC_PLLP_DIV7                  0x00000007U             /*!< PLLP division factor = 7  */
#define RCC_PLLP_DIV8                  0x00000008U             /*!< PLLP division factor = 8  */
#define RCC_PLLP_DIV9                  0x00000009U             /*!< PLLP division factor = 9  */
#define RCC_PLLP_DIV10                 0x0000000AU             /*!< PLLP division factor = 10 */
#define RCC_PLLP_DIV11                 0x0000000BU             /*!< PLLP division factor = 11 */
#define RCC_PLLP_DIV12                 0x0000000CU             /*!< PLLP division factor = 12 */
#define RCC_PLLP_DIV13                 0x0000000DU             /*!< PLLP division factor = 13 */
#define RCC_PLLP_DIV14                 0x0000000EU             /*!< PLLP division factor = 14 */
#define RCC_PLLP_DIV15                 0x0000000FU             /*!< PLLP division factor = 15 */
#define RCC_PLLP_DIV16                 0x00000010U             /*!< PLLP division factor = 16 */
#define RCC_PLLP_DIV17                 0x00000011U             /*!< PLLP division factor = 17 */
#define RCC_PLLP_DIV18                 0x00000012U             /*!< PLLP division factor = 18 */
#define RCC_PLLP_DIV19                 0x00000013U             /*!< PLLP division factor = 19 */
#define RCC_PLLP_DIV20                 0x00000014U             /*!< PLLP division factor = 20 */
#define RCC_PLLP_DIV21                 0x00000015U             /*!< PLLP division factor = 21 */
#define RCC_PLLP_DIV22                 0x00000016U             /*!< PLLP division factor = 22 */
#define RCC_PLLP_DIV23                 0x00000017U             /*!< PLLP division factor = 23 */
#define RCC_PLLP_DIV24                 0x00000018U             /*!< PLLP division factor = 24 */
#define RCC_PLLP_DIV25                 0x00000019U             /*!< PLLP division factor = 25 */
#define RCC_PLLP_DIV26                 0x0000001AU             /*!< PLLP division factor = 26 */
#define RCC_PLLP_DIV27                 0x0000001BU             /*!< PLLP division factor = 27 */
#define RCC_PLLP_DIV28                 0x0000001CU             /*!< PLLP division factor = 28 */
#define RCC_PLLP_DIV29                 0x0000001DU             /*!< PLLP division factor = 29 */
#define RCC_PLLP_DIV30                 0x0000001EU             /*!< PLLP division factor = 30 */
#define RCC_PLLP_DIV31                 0x0000001FU             /*!< PLLP division factor = 31 */
/**
  * @}
  */

/** @defgroup RCC_PLLQ_Clock_Divider PLLQ Clock Divider
  * @{
  */
#define RCC_PLLQ_DIV2                  0x00000002U             /*!< PLLQ division factor = 2 */
#define RCC_PLLQ_DIV4                  0x00000004U             /*!< PLLQ division factor = 4 */
#define RCC_PLLQ_DIV6                  0x00000006U             /*!< PLLQ division factor = 6 */
#define RCC_PLLQ_DIV8                  0x00000008U             /*!< PLLQ division factor = 8 */
/**
  * @}
  */

/** @defgroup RCC_PLLR_Clock_Divider PLLR Clock Divider
  * @{
  */
#define RCC_PLLR_DIV2                  0x00000002U             /*!< PLLR division factor = 2 */
#define RCC_PLLR_DIV4                  0x00000004U             /*!< PLLR division factor = 4 */
#define RCC_PLLR_DIV6                  0x00000006U             /*!< PLLR division factor = 6 */
#define RCC_PLLR_DIV8                  0x00000008U             /*!< PLLR division factor = 8 */
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_NONE             0x00000000U              /*!< No clock selected as PLL entry clock source  */
#define RCC_PLLSOURCE_HSI              RCC_PLLCFGR_PLLSRC_HSI  /*!< HSI clock selected as PLL entry clock source */
#define RCC_PLLSOURCE_HSE              RCC_PLLCFGR_PLLSRC_HSE  /*!< HSE clock selected as PLL entry clock source */
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Output PLL Clock Output
  * @{
  */
#define RCC_PLL_ADCCLK                 RCC_PLLCFGR_PLLPEN      /*!< PLLADCCLK selection from main PLL */
#define RCC_PLL_48M1CLK                RCC_PLLCFGR_PLLQEN      /*!< PLL48M1CLK selection from main PLL */
#define RCC_PLL_SYSCLK                 RCC_PLLCFGR_PLLREN      /*!< PLLCLK selection from main PLL */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Type System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK           0x00000001U              /*!< SYSCLK to configure */
#define RCC_CLOCKTYPE_HCLK             0x00000002U              /*!< HCLK to configure */
#define RCC_CLOCKTYPE_PCLK1            0x00000004U              /*!< PCLK1 to configure */
#define RCC_CLOCKTYPE_PCLK2            0x00000008U              /*!< PCLK2 to configure */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI           RCC_CFGR_SW_HSI    /*!< HSI selection as system clock */
#define RCC_SYSCLKSOURCE_HSE           RCC_CFGR_SW_HSE    /*!< HSE selection as system clock */
#define RCC_SYSCLKSOURCE_PLLCLK        RCC_CFGR_SW_PLL    /*!< PLL selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_HSI    RCC_CFGR_SWS_HSI   /*!< HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE    RCC_CFGR_SWS_HSE   /*!< HSE used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK RCC_CFGR_SWS_PLL   /*!< PLL used as system clock */
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1                RCC_CFGR_HPRE_DIV1   /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2                RCC_CFGR_HPRE_DIV2   /*!< SYSCLK divided by 2 */
#define RCC_SYSCLK_DIV4                RCC_CFGR_HPRE_DIV4   /*!< SYSCLK divided by 4 */
#define RCC_SYSCLK_DIV8                RCC_CFGR_HPRE_DIV8   /*!< SYSCLK divided by 8 */
#define RCC_SYSCLK_DIV16               RCC_CFGR_HPRE_DIV16  /*!< SYSCLK divided by 16 */
#define RCC_SYSCLK_DIV64               RCC_CFGR_HPRE_DIV64  /*!< SYSCLK divided by 64 */
#define RCC_SYSCLK_DIV128              RCC_CFGR_HPRE_DIV128 /*!< SYSCLK divided by 128 */
#define RCC_SYSCLK_DIV256              RCC_CFGR_HPRE_DIV256 /*!< SYSCLK divided by 256 */
#define RCC_SYSCLK_DIV512              RCC_CFGR_HPRE_DIV512 /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_APB1_APB2_Clock_Source APB1 APB2 Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                  RCC_CFGR_PPRE1_DIV1  /*!< HCLK not divided */
#define RCC_HCLK_DIV2                  RCC_CFGR_PPRE1_DIV2  /*!< HCLK divided by 2 */
#define RCC_HCLK_DIV4                  RCC_CFGR_PPRE1_DIV4  /*!< HCLK divided by 4 */
#define RCC_HCLK_DIV8                  RCC_CFGR_PPRE1_DIV8  /*!< HCLK divided by 8 */
#define RCC_HCLK_DIV16                 RCC_CFGR_PPRE1_DIV16 /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source RTC Clock Source
  * @{
  */
#define RCC_RTCCLKSOURCE_NONE          0x00000000U             /*!< No clock used as RTC clock */
#define RCC_RTCCLKSOURCE_LSE           RCC_BDCR_RTCSEL_0       /*!< LSE oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_LSI           RCC_BDCR_RTCSEL_1       /*!< LSI oscillator clock used as RTC clock */
#define RCC_RTCCLKSOURCE_HSE_DIV32     RCC_BDCR_RTCSEL         /*!< HSE oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define RCC_MCO1                       0x00000000U
#define RCC_MCO                        RCC_MCO1               /*!< MCO1 to be compliant with other families with 2 MCOs*/
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Source MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_NOCLOCK         0x00000000U                            /*!< MCO1 output disabled, no clock on MCO1 */
#define RCC_MCO1SOURCE_SYSCLK          RCC_CFGR_MCOSEL_0                      /*!< SYSCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_HSI             (RCC_CFGR_MCOSEL_0| RCC_CFGR_MCOSEL_1) /*!< HSI selection as MCO1 source */
#define RCC_MCO1SOURCE_HSE             RCC_CFGR_MCOSEL_2                      /*!< HSE selection as MCO1 source */
#define RCC_MCO1SOURCE_PLLCLK          (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_2)  /*!< PLLCLK selection as MCO1 source */
#define RCC_MCO1SOURCE_LSI             (RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2)  /*!< LSI selection as MCO1 source */
#define RCC_MCO1SOURCE_LSE             (RCC_CFGR_MCOSEL_0|RCC_CFGR_MCOSEL_1|RCC_CFGR_MCOSEL_2) /*!< LSE selection as MCO1 source */
#define RCC_MCO1SOURCE_HSI48           RCC_CFGR_MCOSEL_3                      /*!< HSI48 selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_MCOx_Clock_Prescaler MCO1 Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                   RCC_CFGR_MCOPRE_DIV1     /*!< MCO not divided  */
#define RCC_MCODIV_2                   RCC_CFGR_MCOPRE_DIV2     /*!< MCO divided by 2 */
#define RCC_MCODIV_4                   RCC_CFGR_MCOPRE_DIV4     /*!< MCO divided by 4 */
#define RCC_MCODIV_8                   RCC_CFGR_MCOPRE_DIV8     /*!< MCO divided by 8 */
#define RCC_MCODIV_16                  RCC_CFGR_MCOPRE_DIV16    /*!< MCO divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_IT_LSIRDY                  RCC_CIFR_LSIRDYF      /*!< LSI Ready Interrupt flag */
#define RCC_IT_LSERDY                  RCC_CIFR_LSERDYF      /*!< LSE Ready Interrupt flag */
#define RCC_IT_HSIRDY                  RCC_CIFR_HSIRDYF      /*!< HSI16 Ready Interrupt flag */
#define RCC_IT_HSERDY                  RCC_CIFR_HSERDYF      /*!< HSE Ready Interrupt flag */
#define RCC_IT_PLLRDY                  RCC_CIFR_PLLRDYF      /*!< PLL Ready Interrupt flag */
#define RCC_IT_CSS                     RCC_CIFR_CSSF        /*!< Clock Security System Interrupt flag */
#define RCC_IT_LSECSS                  RCC_CIFR_LSECSSF     /*!< LSE Clock Security System Interrupt flag */
#define RCC_IT_HSI48RDY                RCC_CIFR_HSI48RDYF   /*!< HSI48 Ready Interrupt flag */
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
  *                 - 100: CRRCR register
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                ((CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos) /*!< HSI Ready flag */
#define RCC_FLAG_HSERDY                ((CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos) /*!< HSE Ready flag */
#define RCC_FLAG_PLLRDY                ((CR_REG_INDEX << 5U) | RCC_CR_PLLRDY_Pos) /*!< PLL Ready flag */

/* Flags in the BDCR register */
#define RCC_FLAG_LSERDY                ((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSERDY_Pos)  /*!< LSE Ready flag */
#define RCC_FLAG_LSECSSD               ((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSECSSD_Pos) /*!< LSE Clock Security System Interrupt flag */

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY                ((CSR_REG_INDEX << 5U) | RCC_CSR_LSIRDY_Pos)    /*!< LSI Ready flag */
#define RCC_FLAG_OBLRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_OBLRSTF_Pos)   /*!< Option Byte Loader reset flag */
#define RCC_FLAG_PINRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_PINRSTF_Pos)   /*!< PIN reset flag */
#define RCC_FLAG_BORRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_BORRSTF_Pos)   /*!< BOR reset flag */
#define RCC_FLAG_SFTRST                ((CSR_REG_INDEX << 5U) | RCC_CSR_SFTRSTF_Pos)   /*!< Software Reset flag */
#define RCC_FLAG_IWDGRST               ((CSR_REG_INDEX << 5U) | RCC_CSR_IWDGRSTF_Pos)  /*!< Independent Watchdog reset flag */
#define RCC_FLAG_WWDGRST               ((CSR_REG_INDEX << 5U) | RCC_CSR_WWDGRSTF_Pos)  /*!< Window watchdog reset flag */
#define RCC_FLAG_LPWRRST               ((CSR_REG_INDEX << 5U) | RCC_CSR_LPWRRSTF_Pos)  /*!< Low-Power reset flag */

/* Flags in the CRRCR register */
#define RCC_FLAG_HSI48RDY              ((CRRCR_REG_INDEX << 5U) | RCC_CRRCR_HSI48RDY_Pos) /*!< HSI48 Ready flag */
/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Config
  * @{
  */
#define RCC_LSEDRIVE_LOW                 0x00000000U            /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW           RCC_BDCR_LSEDRV_0      /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH          RCC_BDCR_LSEDRV_1      /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_HIGH                RCC_BDCR_LSEDRV        /*!< LSE high drive capability */
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

#define __HAL_RCC_DMA1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_DMA2_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_DMAMUX1_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMAMUX1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMAMUX1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_CORDIC_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CORDICEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CORDICEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_FMAC_CLK_ENABLE()              do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FMACEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FMACEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_FLASH_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_CRC_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_DMA1_CLK_DISABLE()           CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN)

#define __HAL_RCC_DMA2_CLK_DISABLE()           CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN)

#define __HAL_RCC_DMAMUX1_CLK_DISABLE()        CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMAMUX1EN)

#define __HAL_RCC_CORDIC_CLK_DISABLE()         CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CORDICEN)

#define __HAL_RCC_FMAC_CLK_DISABLE()           CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FMACEN)

#define __HAL_RCC_FLASH_CLK_DISABLE()          CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN)

#define __HAL_RCC_CRC_CLK_DISABLE()            CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN)

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

#define __HAL_RCC_GPIOA_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_GPIOB_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_GPIOC_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_GPIOD_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_GPIOE_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_GPIOF_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_GPIOG_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_ADC12_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC12EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC12EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC345EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC345EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(DAC2)
#define __HAL_RCC_DAC2_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC3EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC3EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(DAC4)
#define __HAL_RCC_DAC4_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC4EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC4EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* AES */

#define __HAL_RCC_RNG_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)


#define __HAL_RCC_GPIOA_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN)

#define __HAL_RCC_GPIOB_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN)

#define __HAL_RCC_GPIOC_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN)

#define __HAL_RCC_GPIOD_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN)

#define __HAL_RCC_GPIOE_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN)

#define __HAL_RCC_GPIOF_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN)

#define __HAL_RCC_GPIOG_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN)

#define __HAL_RCC_ADC12_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC12EN)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_CLK_DISABLE()         CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC345EN)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_CLK_DISABLE()           CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC1EN)

#if defined(DAC2)
#define __HAL_RCC_DAC2_CLK_DISABLE()           CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC2EN)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_CLK_DISABLE()           CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC3EN)

#if defined(DAC4)
#define __HAL_RCC_DAC4_CLK_DISABLE()           CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC4EN)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_CLK_DISABLE()            CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN);
#endif /* AES */

#define __HAL_RCC_RNG_CLK_DISABLE()            CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN)

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

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* QUADSPI */

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_CLK_DISABLE()            CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_CLK_DISABLE()           CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN)
#endif /* QUADSPI */

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

#define __HAL_RCC_TIM2_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_TIM3_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_TIM4_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(TIM5)
#define __HAL_RCC_TIM5_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_TIM7_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_CRS_CLK_ENABLE()             do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_RTCAPB_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_WWDG_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_SPI2_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_SPI3_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_USART2_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_USART3_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(UART4)
#define __HAL_RCC_UART4_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* UART5 */

#define __HAL_RCC_I2C1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_I2C2_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_USB_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USBEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USBEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_FDCANEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_FDCANEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_PWREN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_PWREN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_I2C3_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_LPTIM1_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_LPUART1_CLK_ENABLE()         do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPUART1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPUART1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_UCPD1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_UCPD1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_TIM2_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN)

#define __HAL_RCC_TIM3_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN)

#define __HAL_RCC_TIM4_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN)

#if defined(TIM5)
#define __HAL_RCC_TIM5_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN)

#define __HAL_RCC_TIM7_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN)

#define __HAL_RCC_CRS_CLK_DISABLE()            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN);

#define __HAL_RCC_RTCAPB_CLK_DISABLE()         CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN);

#define __HAL_RCC_WWDG_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDG2EN)

#define __HAL_RCC_SPI2_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN)

#define __HAL_RCC_SPI3_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN)

#define __HAL_RCC_USART2_CLK_DISABLE()         CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN)

#define __HAL_RCC_USART3_CLK_DISABLE()         CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN)

#if defined(UART4)
#define __HAL_RCC_UART4_CLK_DISABLE()          CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_CLK_DISABLE()          CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN)
#endif /* UART5 */

#define __HAL_RCC_I2C1_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN)

#define __HAL_RCC_I2C2_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN)

#define __HAL_RCC_USB_CLK_DISABLE()            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USBEN)

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_CLK_DISABLE()          CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_FDCANEN)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_CLK_DISABLE()            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_PWREN)

#define __HAL_RCC_I2C3_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN)

#define __HAL_RCC_LPTIM1_CLK_DISABLE()         CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN)

#define __HAL_RCC_LPUART1_CLK_DISABLE()        CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPUART1EN)

#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_DISABLE()           CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_CLK_DISABLE()          CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_UCPD1EN)

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

#define __HAL_RCC_SYSCFG_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_TIM1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_SPI1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_TIM8_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_USART1_CLK_ENABLE()          do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_TIM16_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#define __HAL_RCC_TIM17_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(TIM20)
#define __HAL_RCC_TIM20_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM20EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM20EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_CLK_ENABLE()            do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_CLK_ENABLE()           do { \
                                                 __IO uint32_t tmpreg; \
                                                 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_HRTIM1EN); \
                                                 /* Delay after an RCC peripheral clock enabling */ \
                                                 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_HRTIM1EN); \
                                                 UNUSED(tmpreg); \
                                               } while(0)
#endif /* HRTIM1 */

#define __HAL_RCC_SYSCFG_CLK_DISABLE()         CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN)

#define __HAL_RCC_TIM1_CLK_DISABLE()           CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN)

#define __HAL_RCC_SPI1_CLK_DISABLE()           CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN)

#define __HAL_RCC_TIM8_CLK_DISABLE()           CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN)

#define __HAL_RCC_USART1_CLK_DISABLE()         CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN)

#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_DISABLE()           CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_CLK_DISABLE()          CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN)

#define __HAL_RCC_TIM16_CLK_DISABLE()          CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN)

#define __HAL_RCC_TIM17_CLK_DISABLE()          CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN)

#if defined(TIM20)
#define __HAL_RCC_TIM20_CLK_DISABLE()          CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM20EN)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_CLK_DISABLE()           CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_CLK_DISABLE()          CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_HRTIM1EN)
#endif /* HRTIM1 */

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

#define __HAL_RCC_DMA1_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN) != 0U)

#define __HAL_RCC_DMA2_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN) != 0U)

#define __HAL_RCC_DMAMUX1_IS_CLK_ENABLED()     (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMAMUX1EN) != 0U)

#define __HAL_RCC_CORDIC_IS_CLK_ENABLED()      (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CORDICEN) != 0U)

#define __HAL_RCC_FMAC_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FMACEN) != 0U)

#define __HAL_RCC_FLASH_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN) != 0U)

#define __HAL_RCC_CRC_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN) != 0U)

#define __HAL_RCC_DMA1_IS_CLK_DISABLED()       (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN) == 0U)

#define __HAL_RCC_DMA2_IS_CLK_DISABLED()       (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN) == 0U)

#define __HAL_RCC_DMAMUX1_IS_CLK_DISABLED()    (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMAMUX1EN) == 0U)

#define __HAL_RCC_CORDIC_IS_CLK_DISABLED()     (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CORDICEN) == 0U)

#define __HAL_RCC_FMAC_IS_CLK_DISABLED()       (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FMACEN) == 0U)

#define __HAL_RCC_FLASH_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN) == 0U)

#define __HAL_RCC_CRC_IS_CLK_DISABLED()        (READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN) == 0U)

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

#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN) != 0U)

#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN) != 0U)

#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN) != 0U)

#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN) != 0U)

#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN) != 0U)

#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN) != 0U)

#define __HAL_RCC_GPIOG_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN) != 0U)

#define __HAL_RCC_ADC12_IS_CLK_ENABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC12EN) != 0U)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_IS_CLK_ENABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC345EN) != 0U)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC1EN) != 0U)

#if defined(DAC2)
#define __HAL_RCC_DAC2_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC2EN) != 0U)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC3EN) != 0U)

#if defined(DAC4)
#define __HAL_RCC_DAC4_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC4EN) != 0U)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN) != 0U)
#endif /* AES */

#define __HAL_RCC_RNG_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN) != 0U)


#define __HAL_RCC_GPIOA_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN) == 0U)

#define __HAL_RCC_GPIOB_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN) == 0U)

#define __HAL_RCC_GPIOC_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN) == 0U)

#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN) == 0U)

#define __HAL_RCC_GPIOE_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN) == 0U)

#define __HAL_RCC_GPIOF_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN) == 0U)

#define __HAL_RCC_GPIOG_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN) == 0U)

#define __HAL_RCC_ADC12_IS_CLK_DISABLED()      (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC12EN) == 0U)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_IS_CLK_DISABLED()     (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC345EN) == 0U)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_IS_CLK_DISABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC1EN) == 0U)

#if defined(DAC2)
#define __HAL_RCC_DAC2_IS_CLK_DISABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC2EN) == 0U)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_IS_CLK_DISABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC3EN) == 0U)

#if defined(DAC4)
#define __HAL_RCC_DAC4_IS_CLK_DISABLED()       (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC4EN) == 0U)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_IS_CLK_DISABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN) == 0U)
#endif /* AES */

#define __HAL_RCC_RNG_IS_CLK_DISABLED()        (READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN) == 0U)

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

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_IS_CLK_ENABLED()         (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN) != 0U)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_IS_CLK_ENABLED()        (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN) != 0U)
#endif /* QUADSPI */

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_IS_CLK_DISABLED()        (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN) == 0U)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_IS_CLK_DISABLED()       (READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN) == 0U)
#endif /* QUADSPI */

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

#define __HAL_RCC_TIM2_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN) != 0U)

#define __HAL_RCC_TIM3_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN) != 0U)

#define __HAL_RCC_TIM4_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN) != 0U)

#if defined(TIM5)
#define __HAL_RCC_TIM5_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN) != 0U)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN) != 0U)

#define __HAL_RCC_TIM7_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN) != 0U)

#define __HAL_RCC_CRS_IS_CLK_ENABLED()         (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN) != 0U)

#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()      (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN) != 0U)

#define __HAL_RCC_WWDG_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN) != 0U)

#define __HAL_RCC_SPI2_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN) != 0U)

#define __HAL_RCC_SPI3_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN) != 0U)

#define __HAL_RCC_USART2_IS_CLK_ENABLED()      (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN) != 0U)

#define __HAL_RCC_USART3_IS_CLK_ENABLED()      (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN) != 0U)

#if defined(UART4)
#define __HAL_RCC_UART4_IS_CLK_ENABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN) != 0U)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_IS_CLK_ENABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN) != 0U)
#endif /* UART5 */

#define __HAL_RCC_I2C1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN) != 0U)

#define __HAL_RCC_I2C2_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN) != 0U)

#define __HAL_RCC_USB_IS_CLK_ENABLED()         (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USBEN) != 0U)

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_IS_CLK_ENABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_FDCANEN) != 0U)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_IS_CLK_ENABLED()         (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_PWREN) != 0U)

#define __HAL_RCC_I2C3_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN) != 0U)

#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()      (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN) != 0U)

#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()     (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPUART1EN) != 0U)

#if defined(I2C4)
#define __HAL_RCC_I2C4_IS_CLK_ENABLED()        (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN) != 0U)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_IS_CLK_ENABLED()       (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_UCPD1EN) != 0U)

#define __HAL_RCC_TIM2_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN) == 0U)

#define __HAL_RCC_TIM3_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN) == 0U)

#define __HAL_RCC_TIM4_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN) == 0U)

#if defined(TIM5)
#define __HAL_RCC_TIM5_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN) == 0U)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN) == 0U)

#define __HAL_RCC_TIM7_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN) == 0U)

#define __HAL_RCC_CRS_IS_CLK_DISABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN) == 0U)

#define __HAL_RCC_RTCAPB_IS_CLK_DISABLED()     (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_RTCAPBEN) == 0U)

#define __HAL_RCC_WWDG_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_WWDGEN) == 0U)

#define __HAL_RCC_SPI2_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN) == 0U)

#define __HAL_RCC_SPI3_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN) == 0U)

#define __HAL_RCC_USART2_IS_CLK_DISABLED()     (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN) == 0U)

#define __HAL_RCC_USART3_IS_CLK_DISABLED()     (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN) == 0U)

#if defined(UART4)
#define __HAL_RCC_UART4_IS_CLK_DISABLED()      (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN) == 0U)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_IS_CLK_DISABLED()      (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN) == 0U)
#endif /* UART5 */

#define __HAL_RCC_I2C1_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN) == 0U)

#define __HAL_RCC_I2C2_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN) == 0U)

#if defined(USB)
#define __HAL_RCC_USB_IS_CLK_DISABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USBEN) == 0U)
#endif /* USB */

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_IS_CLK_DISABLED()      (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_FDCANEN) == 0U)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_IS_CLK_DISABLED()        (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_PWREN) == 0U)

#define __HAL_RCC_I2C3_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN) == 0U)

#define __HAL_RCC_LPTIM1_IS_CLK_DISABLED()     (READ_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN) == 0U)

#define __HAL_RCC_LPUART1_IS_CLK_DISABLED()    (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_LPUART1EN) == 0U)

#if defined(I2C4)
#define __HAL_RCC_I2C4_IS_CLK_DISABLED()       (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN) == 0U)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_IS_CLK_DISABLED()      (READ_BIT(RCC->APB1ENR2, RCC_APB1ENR2_UCPD1EN) == 0U)

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

#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()      (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN) != 0U)

#define __HAL_RCC_TIM1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN) != 0U)

#define __HAL_RCC_SPI1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN) != 0U)

#define __HAL_RCC_TIM8_IS_CLK_ENABLED()        (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN) != 0U)

#define __HAL_RCC_USART1_IS_CLK_ENABLED()      (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN) != 0U)

#if defined(SPI4)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()        (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN) != 0U)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_IS_CLK_ENABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN) != 0U)

#define __HAL_RCC_TIM16_IS_CLK_ENABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN) != 0U)

#define __HAL_RCC_TIM17_IS_CLK_ENABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN) != 0U)

#if defined(TIM20)
#define __HAL_RCC_TIM20_IS_CLK_ENABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM20EN) != 0U)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_IS_CLK_ENABLED()        (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN) != 0U)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_IS_CLK_ENABLED()      (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_HRTIM1EN) != 0U)
#endif /* HRTIM1 */


#define __HAL_RCC_SYSCFG_IS_CLK_DISABLED()     (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN) == 0U)

#define __HAL_RCC_TIM1_IS_CLK_DISABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN) == 0U)

#define __HAL_RCC_SPI1_IS_CLK_DISABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN) == 0U)

#define __HAL_RCC_TIM8_IS_CLK_DISABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN) == 0U)

#define __HAL_RCC_USART1_IS_CLK_DISABLED()     (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN) == 0U)

#if defined(SPI4)
#define __HAL_RCC_SPI4_IS_CLK_DISABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN) == 0U)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_IS_CLK_DISABLED()      (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN) == 0U)

#define __HAL_RCC_TIM16_IS_CLK_DISABLED()      (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN) == 0U)

#define __HAL_RCC_TIM17_IS_CLK_DISABLED()      (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN) == 0U)

#if defined(TIM20)
#define __HAL_RCC_TIM20_IS_CLK_DISABLED()      (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM20EN) == 0U)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_IS_CLK_DISABLED()       (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN) == 0U)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_IS_CLK_DISABLED()     (READ_BIT(RCC->APB2ENR, RCC_APB2ENR_HRTIM1EN) == 0U)
#endif /* HRTIM1 */

/**
  * @}
  */

/** @defgroup RCC_AHB1_Force_Release_Reset AHB1 Peripheral Force Release Reset
  * @brief  Force or release AHB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB1_FORCE_RESET()           WRITE_REG(RCC->AHB1RSTR, 0xFFFFFFFFU)

#define __HAL_RCC_DMA1_FORCE_RESET()           SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_DMA1RST)

#define __HAL_RCC_DMA2_FORCE_RESET()           SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_DMA2RST)

#define __HAL_RCC_DMAMUX1_FORCE_RESET()        SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_DMAMUX1RST)

#define __HAL_RCC_CORDIC_FORCE_RESET()         SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_CORDICRST)

#define __HAL_RCC_FMAC_FORCE_RESET()           SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_FMACRST)

#define __HAL_RCC_FLASH_FORCE_RESET()          SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_FLASHRST)

#define __HAL_RCC_CRC_FORCE_RESET()            SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_CRCRST)


#define __HAL_RCC_AHB1_RELEASE_RESET()         WRITE_REG(RCC->AHB1RSTR, 0x00000000U)

#define __HAL_RCC_DMA1_RELEASE_RESET()         CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_DMA1RST)

#define __HAL_RCC_DMA2_RELEASE_RESET()         CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_DMA2RST)

#define __HAL_RCC_DMAMUX1_RELEASE_RESET()      CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_DMAMUX1RST)

#define __HAL_RCC_CORDIC_RELEASE_RESET()       CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_CORDICRST)

#define __HAL_RCC_FMAC_RELEASE_RESET()         CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_FMACRST)

#define __HAL_RCC_FLASH_RELEASE_RESET()        CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_FLASHRST)

#define __HAL_RCC_CRC_RELEASE_RESET()          CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_CRCRST)

/**
  * @}
  */

/** @defgroup RCC_AHB2_Force_Release_Reset AHB2 Peripheral Force Release Reset
  * @brief  Force or release AHB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB2_FORCE_RESET()           WRITE_REG(RCC->AHB2RSTR, 0xFFFFFFFFU)

#define __HAL_RCC_GPIOA_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOARST)

#define __HAL_RCC_GPIOB_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOBRST)

#define __HAL_RCC_GPIOC_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOCRST)

#define __HAL_RCC_GPIOD_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIODRST)

#define __HAL_RCC_GPIOE_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOERST)

#define __HAL_RCC_GPIOF_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOFRST)

#define __HAL_RCC_GPIOG_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOGRST)

#define __HAL_RCC_ADC12_FORCE_RESET()          SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_ADC12RST)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_FORCE_RESET()         SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_ADC345RST)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_FORCE_RESET()           SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_DAC1RST)

#if defined(DAC2)
#define __HAL_RCC_DAC2_FORCE_RESET()           SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_DAC2RST)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_FORCE_RESET()           SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_DAC3RST)

#if defined(DAC4)
#define __HAL_RCC_DAC4_FORCE_RESET()           SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_DAC4RST)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_FORCE_RESET()            SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_AESRST)
#endif /* AES */

#define __HAL_RCC_RNG_FORCE_RESET()            SET_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_RNGRST)


#define __HAL_RCC_AHB2_RELEASE_RESET()         WRITE_REG(RCC->AHB2RSTR, 0x00000000U)

#define __HAL_RCC_GPIOA_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOARST)

#define __HAL_RCC_GPIOB_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOBRST)

#define __HAL_RCC_GPIOC_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOCRST)

#define __HAL_RCC_GPIOD_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIODRST)

#define __HAL_RCC_GPIOE_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOERST)

#define __HAL_RCC_GPIOF_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOFRST)

#define __HAL_RCC_GPIOG_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_GPIOGRST)

#define __HAL_RCC_ADC12_RELEASE_RESET()        CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_ADC12RST)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_RELEASE_RESET()       CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_ADC345RST)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_RELEASE_RESET()         CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_DAC1RST)

#if defined(DAC2)
#define __HAL_RCC_DAC2_RELEASE_RESET()         CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_DAC2RST)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_RELEASE_RESET()         CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_DAC3RST)

#if defined(DAC4)
#define __HAL_RCC_DAC4_RELEASE_RESET()         CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_DAC4RST)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_RELEASE_RESET()          CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_AESRST)
#endif /* AES */

#define __HAL_RCC_RNG_RELEASE_RESET()          CLEAR_BIT(RCC->AHB2RSTR, RCC_AHB2RSTR_RNGRST)

/**
  * @}
  */

/** @defgroup RCC_AHB3_Force_Release_Reset AHB3 Peripheral Force Release Reset
  * @brief  Force or release AHB3 peripheral reset.
  * @{
  */
#define __HAL_RCC_AHB3_FORCE_RESET()           WRITE_REG(RCC->AHB3RSTR, 0xFFFFFFFFU)

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_FORCE_RESET()            SET_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_FMCRST)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_FORCE_RESET()           SET_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_QSPIRST)
#endif /* QUADSPI */

#define __HAL_RCC_AHB3_RELEASE_RESET()         WRITE_REG(RCC->AHB3RSTR, 0x00000000U)

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_RELEASE_RESET()          CLEAR_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_FMCRST)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_RELEASE_RESET()         CLEAR_BIT(RCC->AHB3RSTR, RCC_AHB3RSTR_QSPIRST)
#endif /* QUADSPI */

/**
  * @}
  */

/** @defgroup RCC_APB1_Force_Release_Reset APB1 Peripheral Force Release Reset
  * @brief  Force or release APB1 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB1_FORCE_RESET()           WRITE_REG(RCC->APB1RSTR1, 0xFFFFFFFFU)

#define __HAL_RCC_TIM2_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM2RST)

#define __HAL_RCC_TIM3_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM3RST)

#define __HAL_RCC_TIM4_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM4RST)

#if defined(TIM5)
#define __HAL_RCC_TIM5_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM5RST)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM6RST)

#define __HAL_RCC_TIM7_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM7RST)

#define __HAL_RCC_CRS_FORCE_RESET()            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_CRSRST)

#define __HAL_RCC_SPI2_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI2RST)

#define __HAL_RCC_SPI3_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI3RST)

#define __HAL_RCC_USART2_FORCE_RESET()         SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST)

#define __HAL_RCC_USART3_FORCE_RESET()         SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST)

#if defined(UART4)
#define __HAL_RCC_UART4_FORCE_RESET()          SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_FORCE_RESET()          SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST)
#endif /* UART5 */

#define __HAL_RCC_I2C1_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1RST)

#define __HAL_RCC_I2C2_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C2RST)

#define __HAL_RCC_USB_FORCE_RESET()            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USBRST)

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_FORCE_RESET()          SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_FDCANRST)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_FORCE_RESET()            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_PWRRST)

#define __HAL_RCC_I2C3_FORCE_RESET()           SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C3RST)

#define __HAL_RCC_LPTIM1_FORCE_RESET()         SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_LPTIM1RST)

#define __HAL_RCC_LPUART1_FORCE_RESET()        SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_LPUART1RST)

#if defined(I2C4)
#define __HAL_RCC_I2C4_FORCE_RESET()           SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_I2C4RST)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_FORCE_RESET()          SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_UCPD1RST)

#define __HAL_RCC_APB1_RELEASE_RESET()         WRITE_REG(RCC->APB1RSTR1, 0x00000000U)

#define __HAL_RCC_TIM2_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM2RST)

#define __HAL_RCC_TIM3_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM3RST)

#define __HAL_RCC_TIM4_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM4RST)

#if defined(TIM5)
#define __HAL_RCC_TIM5_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM5RST)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM6RST)

#define __HAL_RCC_TIM7_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_TIM7RST)

#define __HAL_RCC_CRS_RELEASE_RESET()          CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_CRSRST)

#define __HAL_RCC_SPI2_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI2RST)

#define __HAL_RCC_SPI3_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_SPI3RST)

#define __HAL_RCC_USART2_RELEASE_RESET()       CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST)

#define __HAL_RCC_USART3_RELEASE_RESET()       CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST)

#if defined(UART4)
#define __HAL_RCC_UART4_RELEASE_RESET()        CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_RELEASE_RESET()        CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST)
#endif /* UART5 */

#define __HAL_RCC_I2C1_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1RST)

#define __HAL_RCC_I2C2_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C2RST)

#define __HAL_RCC_USB_RELEASE_RESET()          CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USBRST)

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_RELEASE_RESET()        CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_FDCANRST)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_RELEASE_RESET()          CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_PWRRST)

#define __HAL_RCC_I2C3_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C3RST)

#define __HAL_RCC_LPTIM1_RELEASE_RESET()       CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_LPTIM1RST)

#define __HAL_RCC_LPUART1_RELEASE_RESET()      CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_LPUART1RST)

#if defined(I2C4)
#define __HAL_RCC_I2C4_RELEASE_RESET()         CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_I2C4RST)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_RELEASE_RESET()      CLEAR_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_UCPD1RST)

/**
  * @}
  */

/** @defgroup RCC_APB2_Force_Release_Reset APB2 Peripheral Force Release Reset
  * @brief  Force or release APB2 peripheral reset.
  * @{
  */
#define __HAL_RCC_APB2_FORCE_RESET()           WRITE_REG(RCC->APB2RSTR, 0xFFFFFFFFU)

#define __HAL_RCC_SYSCFG_FORCE_RESET()         SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SYSCFGRST)

#define __HAL_RCC_TIM1_FORCE_RESET()           SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST)

#define __HAL_RCC_SPI1_FORCE_RESET()           SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST)

#define __HAL_RCC_TIM8_FORCE_RESET()           SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM8RST)

#define __HAL_RCC_USART1_FORCE_RESET()         SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST)

#if defined(SPI4)
#define __HAL_RCC_SPI4_FORCE_RESET()           SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI4RST)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_FORCE_RESET()          SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM15RST)

#define __HAL_RCC_TIM16_FORCE_RESET()          SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST)

#define __HAL_RCC_TIM17_FORCE_RESET()          SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM17RST)

#if defined(TIM20)
#define __HAL_RCC_TIM20_FORCE_RESET()          SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM20RST)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_FORCE_RESET()           SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI1RST)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_FORCE_RESET()         SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_HRTIM1RST)
#endif /* HRTIM1 */


#define __HAL_RCC_APB2_RELEASE_RESET()         WRITE_REG(RCC->APB2RSTR, 0x00000000U)

#define __HAL_RCC_SYSCFG_RELEASE_RESET()       CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SYSCFGRST)

#define __HAL_RCC_TIM1_RELEASE_RESET()         CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST)

#define __HAL_RCC_SPI1_RELEASE_RESET()         CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST)

#define __HAL_RCC_TIM8_RELEASE_RESET()         CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM8RST)

#define __HAL_RCC_USART1_RELEASE_RESET()       CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST)

#if defined(SPI4)
#define __HAL_RCC_SPI4_RELEASE_RESET()         CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SPI4RST)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_RELEASE_RESET()        CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM15RST)

#define __HAL_RCC_TIM16_RELEASE_RESET()        CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST)

#define __HAL_RCC_TIM17_RELEASE_RESET()        CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM17RST)

#if defined(TIM20)
#define __HAL_RCC_TIM20_RELEASE_RESET()        CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM20RST)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_RELEASE_RESET()         CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SAI1RST)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_RELEASE_RESET()       CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_HRTIM1RST)
#endif /* HRTIM1 */

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

#define __HAL_RCC_DMA1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMA1SMEN)

#define __HAL_RCC_DMA2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMA2SMEN)

#define __HAL_RCC_DMAMUX1_CLK_SLEEP_ENABLE()   SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMAMUX1SMEN)

#define __HAL_RCC_CORDIC_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CORDICSMEN)

#define __HAL_RCC_FMAC_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FMACSMEN)

#define __HAL_RCC_FLASH_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FLASHSMEN)

#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_SRAM1SMEN)

#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CRCSMEN)


#define __HAL_RCC_DMA1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMA1SMEN)

#define __HAL_RCC_DMA2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMA2SMEN)

#define __HAL_RCC_DMAMUX1_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMAMUX1SMEN)

#define __HAL_RCC_CORDIC_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CORDICSMEN)

#define __HAL_RCC_FMAC_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FMACSMEN)

#define __HAL_RCC_FLASH_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FLASHSMEN)

#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_SRAM1SMEN)

#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CRCSMEN)

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

#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOASMEN)

#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOBSMEN)

#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOCSMEN)

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIODSMEN)

#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOESMEN)

#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOFSMEN)

#define __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOGSMEN)

#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SRAM2SMEN)

#define __HAL_RCC_CCM_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_CCMSRAMSMEN)

#define __HAL_RCC_ADC12_CLK_SLEEP_ENABLE()     SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_ADC12SMEN)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_CLK_SLEEP_ENABLE()    SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_ADC345SMEN)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC1SMEN)

#if defined(DAC2)
#define __HAL_RCC_DAC2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC2SMEN)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC3SMEN)

#if defined(DAC4)
#define __HAL_RCC_DAC4_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC4SMEN)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_AESSMEN)
#endif /* AES */

#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_RNGSMEN)


#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOASMEN)

#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOBSMEN)

#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOCSMEN)

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIODSMEN)

#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOESMEN)

#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOFSMEN)

#define __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOGSMEN)

#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SRAM2SMEN)

#define __HAL_RCC_CCM_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_CCMSRAMSMEN)

#define __HAL_RCC_ADC12_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_ADC12SMEN)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_ADC345SMEN)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC1SMEN)

#if defined(DAC2)
#define __HAL_RCC_DAC2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC2SMEN)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC3SMEN)

#if defined(DAC4)
#define __HAL_RCC_DAC4_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC4SMEN)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_AESSMEN)
#endif /* AES */

#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_RNGSMEN)

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

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_CLK_SLEEP_ENABLE()       SET_BIT(RCC->AHB3SMENR, RCC_AHB3SMENR_FMCSMEN)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_CLK_SLEEP_ENABLE()      SET_BIT(RCC->AHB3SMENR, RCC_AHB3SMENR_QSPISMEN)
#endif /* QUADSPI */

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->AHB3SMENR, RCC_AHB3SMENR_FMCSMEN)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->AHB3SMENR, RCC_AHB3SMENR_QSPISMEN)
#endif /* QUADSPI */

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

#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM2SMEN)

#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM3SMEN)

#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM4SMEN)

#if defined(TIM5)
#define __HAL_RCC_TIM5_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM5SMEN)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM6SMEN)

#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM7SMEN)

#define __HAL_RCC_CRS_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_CRSSMEN)

#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_RTCAPBSMEN)

#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_WWDGSMEN)

#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_SPI2SMEN)

#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_SPI3SMEN)

#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART2SMEN)

#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART3SMEN)

#if defined(UART4)
#define __HAL_RCC_UART4_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_UART4SMEN)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_UART5SMEN)
#endif /* UART5 */

#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C1SMEN)

#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C2SMEN)

#if defined(USB)
#define __HAL_RCC_USB_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USBSMEN)
#endif /* USB */

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_FDCANSMEN)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_CLK_SLEEP_ENABLE()       SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_PWRSMEN)

#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C3SMEN)

#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_LPTIM1SMEN)

#define __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE()   SET_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_LPUART1SMEN)

#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_I2C4SMEN)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_UCPD1SMEN)


#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM2SMEN)

#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM3SMEN)

#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM4SMEN)

#if defined(TIM5)
#define __HAL_RCC_TIM5_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM5SMEN)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM6SMEN)

#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM7SMEN)

#define __HAL_RCC_CRS_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_CRSSMEN)

#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_RTCAPBSMEN)

#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_WWDGSMEN)

#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_SPI2SMEN)

#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_SPI3SMEN)

#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART2SMEN)

#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART3SMEN)

#if defined(UART4)
#define __HAL_RCC_UART4_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_UART4SMEN)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_UART5SMEN)
#endif /* UART5 */

#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C1SMEN)

#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C2SMEN)

#if defined(USB)
#define __HAL_RCC_USB_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USBSMEN)
#endif /* USB */

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_FDCANSMEN)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_PWRSMEN)

#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C3SMEN)

#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_LPTIM1SMEN)

#define __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE()  CLEAR_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_LPUART1SMEN)

#if defined(I2C4)
#define __HAL_RCC_I2C4_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_I2C4SMEN)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_UCPD1SMEN)

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

#define __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SYSCFGSMEN)

#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM1SMEN)

#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI1SMEN)

#define __HAL_RCC_TIM8_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM8SMEN)

#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_USART1SMEN)

#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI4SMEN)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM15SMEN)

#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM16SMEN)

#define __HAL_RCC_TIM17_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM17SMEN)

#if defined(TIM20)
#define __HAL_RCC_TIM20_CLK_SLEEP_ENABLE()     SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM20SMEN)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SAI1SMEN)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_CLK_SLEEP_ENABLE()    SET_BIT(RCC->APB2SMENR, RCC_APB2SMENR_HRTIM1SMEN)
#endif /* HRTIM1 */


#define __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SYSCFGSMEN)

#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM1SMEN)

#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI1SMEN)

#define __HAL_RCC_TIM8_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM8SMEN)

#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_USART1SMEN)

#if defined(SPI4)
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI4SMEN)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM15SMEN)

#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM16SMEN)

#define __HAL_RCC_TIM17_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM17SMEN)

#if defined(TIM20)
#define __HAL_RCC_TIM20_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM20SMEN)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SAI1SMEN)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_CLK_SLEEP_DISABLE()   CLEAR_BIT(RCC->APB2SMENR, RCC_APB2SMENR_HRTIM1SMEN)
#endif /* HRTIM1 */

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

#define __HAL_RCC_DMA1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMA1SMEN) != 0U)

#define __HAL_RCC_DMA2_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMA2SMEN) != 0U)

#define __HAL_RCC_DMAMUX1_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMAMUX1SMEN) != 0U)

#define __HAL_RCC_CORDIC_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CORDICSMEN) != 0U)

#define __HAL_RCC_FMAC_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FMACSMEN) != 0U)

#define __HAL_RCC_FLASH_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FLASHSMEN) != 0U)

#define __HAL_RCC_SRAM1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_SRAM1SMEN) != 0U)

#define __HAL_RCC_CRC_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CRCSMEN) != 0U)


#define __HAL_RCC_DMA1_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMA1SMEN) == 0U)

#define __HAL_RCC_DMA2_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMA2SMEN) == 0U)

#define __HAL_RCC_DMAMUX1_IS_CLK_SLEEP_DISABLED() (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_DMAMUX1SMEN) == 0U)

#define __HAL_RCC_CORDIC_IS_CLK_SLEEP_DISABLED() (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CORDICSMEN) == 0U)

#define __HAL_RCC_FMAC_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FMACSMEN) == 0U)

#define __HAL_RCC_FLASH_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_FLASHSMEN) == 0U)

#define __HAL_RCC_SRAM1_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_SRAM1SMEN) == 0U)

#define __HAL_RCC_CRC_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->AHB1SMENR, RCC_AHB1SMENR_CRCSMEN) == 0U)

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

#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOASMEN) != 0U)

#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOBSMEN) != 0U)

#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOCSMEN) != 0U)

#define __HAL_RCC_GPIOD_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIODSMEN) != 0U)

#define __HAL_RCC_GPIOE_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOESMEN) != 0U)

#define __HAL_RCC_GPIOF_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOFSMEN) != 0U)

#define __HAL_RCC_GPIOG_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOGSMEN) != 0U)

#define __HAL_RCC_SRAM2_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SRAM2SMEN) != 0U)

#define __HAL_RCC_CCM_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_CCMSRAMSMEN) != 0U)

#define __HAL_RCC_ADC12_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_ADC12SMEN) != 0U)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_IS_CLK_SLEEP_ENABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_ADC345SMEN) != 0U)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC1SMEN) != 0U)

#if defined(DAC2)
#define __HAL_RCC_DAC2_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC2SMEN) != 0U)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC3SMEN) != 0U)

#if defined(DAC4)
#define __HAL_RCC_DAC4_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC4SMEN) != 0U)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_AESSMEN) != 0U)
#endif /* AES */

#define __HAL_RCC_RNG_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_RNGSMEN) != 0U)


#define __HAL_RCC_GPIOA_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOASMEN) == 0U)

#define __HAL_RCC_GPIOB_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOBSMEN) == 0U)

#define __HAL_RCC_GPIOC_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOCSMEN) == 0U)

#define __HAL_RCC_GPIOD_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIODSMEN) == 0U)

#define __HAL_RCC_GPIOE_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOESMEN) == 0U)

#define __HAL_RCC_GPIOF_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOFSMEN) == 0U)

#define __HAL_RCC_GPIOG_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOGSMEN) == 0U)

#define __HAL_RCC_SRAM2_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_SRAM2SMEN) == 0U)

#define __HAL_RCC_CCM_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_CCMSRAMSMEN) == 0U)

#define __HAL_RCC_ADC12_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_ADC12SMEN) == 0U)

#if defined(ADC345_COMMON)
#define __HAL_RCC_ADC345_IS_CLK_SLEEP_DISABLED() (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_ADC345SMEN) == 0U)
#endif /* ADC345_COMMON */

#define __HAL_RCC_DAC1_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC1SMEN) == 0U)

#if defined(DAC2)
#define __HAL_RCC_DAC2_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC2SMEN) == 0U)
#endif /* DAC2 */

#define __HAL_RCC_DAC3_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC3SMEN) == 0U)

#if defined(DAC4)
#define __HAL_RCC_DAC4_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_DAC4SMEN) == 0U)
#endif /* DAC4 */

#if defined(AES)
#define __HAL_RCC_AES_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_AESSMEN) == 0U)
#endif /* AES */

#define __HAL_RCC_RNG_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_RNGSMEN) == 0U)

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

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->AHB3SMENR, RCC_AHB3SMENR_FMCSMEN) != 0U)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->AHB3SMENR, RCC_AHB3SMENR_QSPISMEN) != 0U)
#endif /* QUADSPI */

#if defined(FMC_BANK1)
#define __HAL_RCC_FMC_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->AHB3SMENR, RCC_AHB3SMENR_FMCSMEN) == 0U)
#endif /* FMC_BANK1 */

#if defined(QUADSPI)
#define __HAL_RCC_QSPI_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->AHB3SMENR, RCC_AHB3SMENR_QSPISMEN) == 0U)
#endif /* QUADSPI */

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

#define __HAL_RCC_TIM2_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM2SMEN) != 0U)

#define __HAL_RCC_TIM3_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM3SMEN) != 0U)

#define __HAL_RCC_TIM4_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM4SMEN) != 0U)

#if defined(TIM5)
#define __HAL_RCC_TIM5_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM5SMEN) != 0U)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM6SMEN) != 0U)

#define __HAL_RCC_TIM7_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM7SMEN) != 0U)

#define __HAL_RCC_CRS_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_CRSSMEN) != 0U)

#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_RTCAPBSMEN) != 0U)

#define __HAL_RCC_WWDG_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_WWDGSMEN) != 0U)

#define __HAL_RCC_SPI2_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_SPI2SMEN) != 0U)

#define __HAL_RCC_SPI3_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_SPI3SMEN) != 0U)

#define __HAL_RCC_USART2_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART2SMEN) != 0U)

#define __HAL_RCC_USART3_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART3SMEN) != 0U)

#if defined(UART4)
#define __HAL_RCC_UART4_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_UART4SMEN) != 0U)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_UART5SMEN) != 0U)
#endif /* UART5 */

#define __HAL_RCC_I2C1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C1SMEN) != 0U)

#define __HAL_RCC_I2C2_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C2SMEN) != 0U)

#define __HAL_RCC_USB_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USBSMEN) != 0U)

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_FDCANSMEN) != 0U)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_IS_CLK_SLEEP_ENABLED()       (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_PWRSMEN) != 0U)

#define __HAL_RCC_I2C3_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C3SMEN) != 0U)

#define __HAL_RCC_LPTIM1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_LPTIM1SMEN) != 0U)

#define __HAL_RCC_LPUART1_IS_CLK_SLEEP_ENABLED()   (READ_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_LPUART1SMEN) != 0U)

#if defined(I2C4)
#define __HAL_RCC_I2C4_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_I2C4SMEN) != 0U)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_UCPD1SMEN) != 0U)


#define __HAL_RCC_TIM2_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM2SMEN) == 0U)

#define __HAL_RCC_TIM3_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM3SMEN) == 0U)

#define __HAL_RCC_TIM4_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM4SMEN) == 0U)

#if defined(TIM5)
#define __HAL_RCC_TIM5_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM5SMEN) == 0U)
#endif /* TIM5 */

#define __HAL_RCC_TIM6_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM6SMEN) == 0U)

#define __HAL_RCC_TIM7_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_TIM7SMEN) == 0U)

#define __HAL_RCC_CRS_IS_CLK_SLEEP_DISABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_CRSSMEN) == 0U)

#define __HAL_RCC_RTCAPB_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_RTCAPBSMEN) == 0U)

#define __HAL_RCC_WWDG_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_WWDGSMEN) == 0U)

#define __HAL_RCC_SPI2_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_SPI2SMEN) == 0U)

#define __HAL_RCC_SPI3_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_SPI3SMEN) == 0U)

#define __HAL_RCC_USART2_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART2SMEN) == 0U)

#define __HAL_RCC_USART3_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USART3SMEN) == 0U)

#if defined(UART4)
#define __HAL_RCC_UART4_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_UART4SMEN) == 0U)
#endif /* UART4 */

#if defined(UART5)
#define __HAL_RCC_UART5_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_UART5SMEN) == 0U)
#endif /* UART5 */

#define __HAL_RCC_I2C1_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C1SMEN) == 0U)

#define __HAL_RCC_I2C2_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C2SMEN) == 0U)

#define __HAL_RCC_USB_IS_CLK_SLEEP_DISABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_USBSMEN) == 0U)

#if defined(FDCAN1)
#define __HAL_RCC_FDCAN_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_FDCANSMEN) == 0U)
#endif /* FDCAN1 */

#define __HAL_RCC_PWR_IS_CLK_SLEEP_DISABLED()      (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_PWRSMEN) == 0U)

#define __HAL_RCC_I2C3_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_I2C3SMEN) == 0U)

#define __HAL_RCC_LPTIM1_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APB1SMENR1, RCC_APB1SMENR1_LPTIM1SMEN) == 0U)

#define __HAL_RCC_LPUART1_IS_CLK_SLEEP_DISABLED()  (READ_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_LPUART1SMEN) == 0U)

#if defined(I2C4)
#define __HAL_RCC_I2C4_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_I2C4SMEN) == 0U)
#endif /* I2C4 */

#define __HAL_RCC_UCPD1_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APB1SMENR2, RCC_APB1SMENR2_UCPD1SMEN) == 0U)

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

#define __HAL_RCC_SYSCFG_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SYSCFGSMEN) != 0U)

#define __HAL_RCC_TIM1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM1SMEN) != 0U)

#define __HAL_RCC_SPI1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI1SMEN) != 0U)

#define __HAL_RCC_TIM8_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM8SMEN) != 0U)

#define __HAL_RCC_USART1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_USART1SMEN) != 0U)

#if defined(SPI4)
#define __HAL_RCC_SPI4_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI4SMEN) != 0U)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM15SMEN) != 0U)

#define __HAL_RCC_TIM16_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM16SMEN) != 0U)

#define __HAL_RCC_TIM17_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM17SMEN) != 0U)

#if defined(TIM20)
#define __HAL_RCC_TIM20_IS_CLK_SLEEP_ENABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM20SMEN) != 0U)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_IS_CLK_SLEEP_ENABLED()      (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SAI1SMEN) != 0U)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_IS_CLK_SLEEP_ENABLED()    (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_HRTIM1SMEN) != 0U)
#endif /* HRTIM1 */


#define __HAL_RCC_SYSCFG_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SYSCFGSMEN) == 0U)

#define __HAL_RCC_TIM1_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM1SMEN) == 0U)

#define __HAL_RCC_SPI1_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI1SMEN) == 0U)

#define __HAL_RCC_TIM8_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM8SMEN) == 0U)

#define __HAL_RCC_USART1_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_USART1SMEN) == 0U)

#if defined(SPI4)
#define __HAL_RCC_SPI4_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SPI4SMEN) == 0U)
#endif /* SPI4 */

#define __HAL_RCC_TIM15_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM15SMEN) == 0U)

#define __HAL_RCC_TIM16_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM16SMEN) == 0U)

#define __HAL_RCC_TIM17_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM17SMEN) == 0U)

#if defined(TIM20)
#define __HAL_RCC_TIM20_IS_CLK_SLEEP_DISABLED()    (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_TIM20SMEN) == 0U)
#endif /* TIM20 */

#define __HAL_RCC_SAI1_IS_CLK_SLEEP_DISABLED()     (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_SAI1SMEN) == 0U)

#if defined(HRTIM1)
#define __HAL_RCC_HRTIM1_IS_CLK_SLEEP_DISABLED()   (READ_BIT(RCC->APB2SMENR, RCC_APB2SMENR_HRTIM1SMEN) == 0U)
#endif /* HRTIM1 */


/**
  * @}
  */

/** @defgroup RCC_Backup_Domain_Reset RCC Backup Domain Reset
  * @{
  */

/** @brief  Macros to force or release the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_CSR register.
  * @note   The BKPSRAM is not affected by this reset.
  * @retval None
  */
#define __HAL_RCC_BACKUPRESET_FORCE()   SET_BIT(RCC->BDCR, RCC_BDCR_BDRST)

#define __HAL_RCC_BACKUPRESET_RELEASE() CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST)

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
#define __HAL_RCC_RTC_ENABLE()         SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

#define __HAL_RCC_RTC_DISABLE()        CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN)

/**
  * @}
  */

/** @brief  Macros to enable or disable the Internal High Speed 16MHz oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after startup
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
  * @retval None
  */
#define __HAL_RCC_HSI_ENABLE()  SET_BIT(RCC->CR, RCC_CR_HSION)

#define __HAL_RCC_HSI_DISABLE() CLEAR_BIT(RCC->CR, RCC_CR_HSION)

/** @brief  Macro to adjust the Internal High Speed 16MHz oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @param  __HSICALIBRATIONVALUE__ specifies the calibration trimming value
  *         (default is RCC_HSICALIBRATION_DEFAULT).
  *         This parameter must be a number between 0 and 0x7F.
  * @retval None
  */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICALIBRATIONVALUE__) \
                  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSITRIM, (__HSICALIBRATIONVALUE__) << RCC_ICSCR_HSITRIM_Pos)

/**
  * @brief    Macros to enable or disable the force of the Internal High Speed oscillator (HSI)
  *           in STOP mode to be quickly available as kernel clock for USARTs and I2Cs.
  * @note     Keeping the HSI ON in STOP mode allows to avoid slowing down the communication
  *           speed because of the HSI startup time.
  * @note     The enable of this function has not effect on the HSION bit.
  *           This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSISTOP_ENABLE()     SET_BIT(RCC->CR, RCC_CR_HSIKERON)

#define __HAL_RCC_HSISTOP_DISABLE()    CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON)

/** @brief  Macros to enable or disable the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
#define __HAL_RCC_LSI_ENABLE()         SET_BIT(RCC->CSR, RCC_CSR_LSION)

#define __HAL_RCC_LSI_DISABLE()        CLEAR_BIT(RCC->CSR, RCC_CSR_LSION)

/**
  * @brief  Macro to configure the External High Speed oscillator (HSE).
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this macro. User should request a transition to HSE Off
  *         first and then HSE On or HSE Bypass.
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
  *            @arg @ref RCC_HSE_OFF  Turn OFF the HSE oscillator, HSERDY flag goes low after
  *                                   6 HSE oscillator clock cycles.
  *            @arg @ref RCC_HSE_ON  Turn ON the HSE oscillator.
  *            @arg @ref RCC_HSE_BYPASS  HSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_HSE_CONFIG(__STATE__)                                    \
                    do {                                                   \
                      if((__STATE__) == RCC_HSE_ON)                        \
                      {                                                    \
                        SET_BIT(RCC->CR, RCC_CR_HSEON);                    \
                      }                                                    \
                      else if((__STATE__) == RCC_HSE_BYPASS)               \
                      {                                                    \
                        SET_BIT(RCC->CR, RCC_CR_HSEBYP);                   \
                        SET_BIT(RCC->CR, RCC_CR_HSEON);                    \
                      }                                                    \
                      else                                                 \
                      {                                                    \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEON);                  \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);                 \
                      }                                                    \
                    } while(0)

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
  * @param  __STATE__ specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LSE_OFF  Turn OFF the LSE oscillator, LSERDY flag goes low after
  *                                   6 LSE oscillator clock cycles.
  *            @arg @ref RCC_LSE_ON  Turn ON the LSE oscillator.
  *            @arg @ref RCC_LSE_BYPASS  LSE oscillator bypassed with external clock.
  * @retval None
  */
#define __HAL_RCC_LSE_CONFIG(__STATE__)                                        \
                    do {                                                       \
                      if((__STATE__) == RCC_LSE_ON)                            \
                      {                                                        \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);                    \
                      }                                                        \
                      else if((__STATE__) == RCC_LSE_BYPASS)                   \
                      {                                                        \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                   \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);                    \
                      }                                                        \
                      else                                                     \
                      {                                                        \
                        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);                  \
                        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                 \
                      }                                                        \
                    } while(0)

/** @brief  Macros to enable or disable the Internal High Speed 48MHz oscillator (HSI48).
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  * @note   After enabling the HSI48, the application software should wait on HSI48RDY
  *         flag to be set indicating that HSI48 clock is stable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
#define __HAL_RCC_HSI48_ENABLE()  SET_BIT(RCC->CRRCR, RCC_CRRCR_HSI48ON)

#define __HAL_RCC_HSI48_DISABLE() CLEAR_BIT(RCC->CRRCR, RCC_CRRCR_HSI48ON)

/** @brief  Macros to configure the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using the Power Backup Access macro before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it cannot be changed unless the
  *         Backup domain is reset using __HAL_RCC_BACKUPRESET_FORCE() macro, or by
  *         a Power On Reset (POR).
  *
  * @param  __RTC_CLKSOURCE__ specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE  No clock selected as RTC clock.
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
#define __HAL_RCC_RTC_CONFIG(__RTC_CLKSOURCE__)  \
                  MODIFY_REG( RCC->BDCR, RCC_BDCR_RTCSEL, (__RTC_CLKSOURCE__))


/** @brief  Macro to get the RTC clock source.
  * @retval The returned value can be one of the following:
  *            @arg @ref RCC_RTCCLKSOURCE_NONE  No clock selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSE  LSE selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_LSI  LSI selected as RTC clock.
  *            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV32  HSE clock divided by 32 selected
  */
#define  __HAL_RCC_GET_RTC_SOURCE() (READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL))

/** @brief  Macros to enable or disable the main PLL.
  * @note   After enabling the main PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The main PLL can not be disabled if it is used as system clock source
  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
  * @retval None
  */
#define __HAL_RCC_PLL_ENABLE()         SET_BIT(RCC->CR, RCC_CR_PLLON)

#define __HAL_RCC_PLL_DISABLE()        CLEAR_BIT(RCC->CR, RCC_CR_PLLON)

/** @brief  Macro to configure the PLL clock source.
  * @note   This function must be used only when the main PLL is disabled.
  * @param  __PLLSOURCE__ specifies the PLL entry clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_NONE  No clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL clock entry
  * @retval None
  *
  */
#define __HAL_RCC_PLL_PLLSOURCE_CONFIG(__PLLSOURCE__) \
                  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC, (__PLLSOURCE__))

/** @brief  Macro to configure the PLL source division factor M.
  * @note   This function must be used only when the main PLL is disabled.
  * @param  __PLLM__ specifies the division factor for PLL VCO input clock
  *         This parameter must be a value of @ref RCC_PLLM_Clock_Divider.
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 2.66 to 8 MHz. It is recommended to select a frequency
  *         of 8 MHz to limit PLL jitter.
  * @retval None
  *
  */
#define __HAL_RCC_PLL_PLLM_CONFIG(__PLLM__) \
                  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, ((__PLLM__) - 1) << RCC_PLLCFGR_PLLM_Pos)

/**
  * @brief  Macro to configure the main PLL clock source, multiplication and division factors.
  * @note   This macro must be used only when the main PLL is disabled.
  * @note   This macro preserves the PLL's output clocks enable state.
  *
  * @param  __PLLSOURCE__ specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_PLLSOURCE_NONE  No clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSI  HSI oscillator clock selected as PLL clock entry
  *            @arg @ref RCC_PLLSOURCE_HSE  HSE oscillator clock selected as PLL clock entry
  *
  * @param  __PLLM__ specifies the division factor for PLL VCO input clock.
  *          This parameter must be a value of @ref RCC_PLLM_Clock_Divider
  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
  *         frequency ranges from 2.66 to 8 MHz. It is recommended to select a frequency
  *         of 8 MHz to limit PLL jitter.
  *
  * @param  __PLLN__ specifies the multiplication factor for PLL VCO output clock.
  *          This parameter must be a number between 8 and 127.
  * @note   You have to set the PLLN parameter correctly to ensure that the VCO
  *         output frequency is between 64 and 344 MHz.
  *
  * @param  __PLLP__ specifies the division factor for SAI clock.
  *          This parameter must be a number in the range (2 to 31).
  *
  * @param  __PLLQ__ specifies the division factor for OTG FS, SDMMC1 and RNG clocks.
  *          This parameter must be in the range (2, 4, 6 or 8).
  * @note   If the USB OTG FS is used in your application, you have to set the
  *         PLLQ parameter correctly to have 48 MHz clock for the USB. However,
  *         the SDMMC1 and RNG need a frequency lower than or equal to 48 MHz to work
  *         correctly.
  * @param  __PLLR__ specifies the division factor for the main system clock.
  * @note   You have to set the PLLR parameter correctly to not exceed 170MHZ.
  *          This parameter must be in the range (2, 4, 6 or 8).
  * @retval None
  */
#define __HAL_RCC_PLL_CONFIG(__PLLSOURCE__, __PLLM__, __PLLN__, __PLLP__, __PLLQ__,__PLLR__ ) \
                  MODIFY_REG(RCC->PLLCFGR, \
                             (RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | \
                              RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLR | RCC_PLLCFGR_PLLPDIV), \
                             ((__PLLSOURCE__) | \
                              (((__PLLM__) - 1U) << RCC_PLLCFGR_PLLM_Pos) | \
                              ((__PLLN__) << RCC_PLLCFGR_PLLN_Pos) | \
                              ((((__PLLQ__) >> 1U) - 1U) << RCC_PLLCFGR_PLLQ_Pos) | \
                              ((((__PLLR__) >> 1U) - 1U) << RCC_PLLCFGR_PLLR_Pos) | \
                              ((__PLLP__) << RCC_PLLCFGR_PLLPDIV_Pos)))

/** @brief  Macro to get the oscillator used as PLL clock source.
  * @retval The oscillator used as PLL clock source. The returned value can be one
  *         of the following:
  *              - RCC_PLLSOURCE_NONE: No oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSI: HSI oscillator is used as PLL clock source.
  *              - RCC_PLLSOURCE_HSE: HSE oscillator is used as PLL clock source.
  */
#define __HAL_RCC_GET_PLL_OSCSOURCE() (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC))

/**
  * @brief  Enable or disable each clock output (RCC_PLL_SYSCLK, RCC_PLL_48M1CLK, RCC_PLL_ADCCLK)
  * @note   Enabling/disabling clock outputs RCC_PLL_ADCCLK and RCC_PLL_48M1CLK can be done at anytime
  *         without the need to stop the PLL in order to save power. But RCC_PLL_SYSCLK cannot
  *         be stopped if used as System Clock.
  * @param  __PLLCLOCKOUT__ specifies the PLL clock to be output.
  *          This parameter can be one or a combination of the following values:
  *            @arg @ref RCC_PLL_ADCCLK  This clock is used to generate a clock on ADC.
  *            @arg @ref RCC_PLL_48M1CLK  This Clock is used to generate the clock for the USB (48 MHz),
  *                                   FDCAN (<=48 MHz) and QSPI (<=48 MHz).
  *            @arg @ref RCC_PLL_SYSCLK  This Clock is used to generate the high speed system clock (up to 170MHz)
  * @retval None
  */
#define __HAL_RCC_PLLCLKOUT_ENABLE(__PLLCLOCKOUT__)   SET_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

#define __HAL_RCC_PLLCLKOUT_DISABLE(__PLLCLOCKOUT__)  CLEAR_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

/**
  * @brief  Get clock output enable status (RCC_PLL_SYSCLK, RCC_PLL_48M1CLK, RCC_PLL_SAI3CLK)
  * @param  __PLLCLOCKOUT__ specifies the output PLL clock to be checked.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_PLL_ADCCLK  This clock is used to generate a clock on ADC.
  *            @arg @ref RCC_PLL_48M1CLK  This Clock is used to generate the clock for the USB (48 MHz),
  *                                   FDCAN (<=48 MHz) and QSPI (<=48 MHz).
  *            @arg @ref RCC_PLL_SYSCLK  This Clock is used to generate the high speed system clock (up to 170MHz)
  * @retval SET / RESET
  */
#define __HAL_RCC_GET_PLLCLKOUT_CONFIG(__PLLCLOCKOUT__)  READ_BIT(RCC->PLLCFGR, (__PLLCLOCKOUT__))

/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__ specifies the system clock source.
  *          This parameter can be one of the following values:
  *              - RCC_SYSCLKSOURCE_HSI: HSI oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_HSE: HSE oscillator is used as system clock source.
  *              - RCC_SYSCLKSOURCE_PLLCLK: PLL output is used as system clock source.
  * @retval None
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) \
                  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (__SYSCLKSOURCE__))

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *              - RCC_SYSCLKSOURCE_STATUS_HSI: HSI used as system clock.
  *              - RCC_SYSCLKSOURCE_STATUS_HSE: HSE used as system clock.
  *              - RCC_SYSCLKSOURCE_STATUS_PLLCLK: PLL used as system clock.
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE() (READ_BIT(RCC->CFGR, RCC_CFGR_SWS))

/**
  * @brief  Macro to configure the External Low Speed oscillator (LSE) drive capability.
  * @note   As the LSE is in the Backup domain and write access is denied to
  *         this domain after reset, you have to enable write access using
  *         HAL_PWR_EnableBkUpAccess() function before to configure the LSE
  *         (to be done once after reset).
  * @param  __LSEDRIVE__ specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSEDRIVE_LOW  LSE oscillator low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMLOW  LSE oscillator medium low drive capability.
  *            @arg @ref RCC_LSEDRIVE_MEDIUMHIGH  LSE oscillator medium high drive capability.
  *            @arg @ref RCC_LSEDRIVE_HIGH  LSE oscillator high drive capability.
  * @retval None
  */
#define __HAL_RCC_LSEDRIVE_CONFIG(__LSEDRIVE__) \
                  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, (__LSEDRIVE__))

/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK  MCO output disabled
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK  System  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI  HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE  HSE clock selected as MCO sourcee
  *            @arg @ref RCC_MCO1SOURCE_PLLCLK  Main PLL clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSI  LSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSE  LSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI48  HSI48 clock selected as MCO source for devices with HSI48
  * @param  __MCODIV__ specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1   MCO clock source is divided by 1
  *            @arg @ref RCC_MCODIV_2   MCO clock source is divided by 2
  *            @arg @ref RCC_MCODIV_4   MCO clock source is divided by 4
  *            @arg @ref RCC_MCODIV_8   MCO clock source is divided by 8
  *            @arg @ref RCC_MCODIV_16  MCO clock source is divided by 16
  */
#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
                 MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCOSEL | RCC_CFGR_MCOPRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

/** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
  * @brief macros to manage the specified RCC Flags and interrupts.
  * @{
  */

/** @brief  Enable RCC interrupt (Perform Byte access to RCC_CIR[14:8] bits to enable
  *         the selected interrupts).
  * @param  __INTERRUPT__ specifies the RCC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY  LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY  LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY  HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY  HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY  Main PLL ready interrupt
  *            @arg @ref RCC_IT_LSECSS  LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY  HSI48 ready interrupt for devices with HSI48
  * @retval None
  */
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief Disable RCC interrupt (Perform Byte access to RCC_CIR[14:8] bits to disable
  *        the selected interrupts).
  * @param  __INTERRUPT__ specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY  LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY  LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY  HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY  HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY  Main PLL ready interrupt
  *            @arg @ref RCC_IT_LSECSS  LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY  HSI48 ready interrupt for devices with HSI48
  * @retval None
  */
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->CIER, (__INTERRUPT__))

/** @brief  Clear the RCC's interrupt pending bits (Perform Byte access to RCC_CIR[23:16]
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref RCC_IT_LSIRDY  LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY  LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY  HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY  HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY  Main PLL ready interrupt
  *            @arg @ref RCC_IT_CSS  HSE Clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS  LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY  HSI48 ready interrupt for devices with HSI48
  * @retval None
  */
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->CICR = (__INTERRUPT__))

/** @brief  Check whether the RCC interrupt has occurred or not.
  * @param  __INTERRUPT__ specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_IT_LSIRDY  LSI ready interrupt
  *            @arg @ref RCC_IT_LSERDY  LSE ready interrupt
  *            @arg @ref RCC_IT_HSIRDY  HSI ready interrupt
  *            @arg @ref RCC_IT_HSERDY  HSE ready interrupt
  *            @arg @ref RCC_IT_PLLRDY  Main PLL ready interrupt
  *            @arg @ref RCC_IT_CSS  HSE Clock security system interrupt
  *            @arg @ref RCC_IT_LSECSS  LSE Clock security system interrupt
  *            @arg @ref RCC_IT_HSI48RDY HSI48 ready interrupt for devices with HSI48
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIFR & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Set RMVF bit to clear the reset flags.
  *        The reset flags are: RCC_FLAG_FWRRST, RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_BORRST,
  *        RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST and RCC_FLAG_LPWRRST.
  * @retval None
 */
#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

/** @brief  Check whether the selected RCC flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_HSIRDY  HSI oscillator clock ready
  *            @arg @ref RCC_FLAG_HSERDY  HSE oscillator clock ready
  *            @arg @ref RCC_FLAG_PLLRDY  Main PLL clock ready
  *            @arg @ref RCC_FLAG_HSI48RDY  HSI48 clock ready for devices with HSI48
  *            @arg @ref RCC_FLAG_LSERDY  LSE oscillator clock ready
  *            @arg @ref RCC_FLAG_LSECSSD  Clock security system failure on LSE oscillator detection
  *            @arg @ref RCC_FLAG_LSIRDY  LSI oscillator clock ready
  *            @arg @ref RCC_FLAG_BORRST  BOR reset
  *            @arg @ref RCC_FLAG_OBLRST  OBLRST reset
  *            @arg @ref RCC_FLAG_PINRST  Pin reset
  *            @arg @ref RCC_FLAG_SFTRST  Software reset
  *            @arg @ref RCC_FLAG_IWDGRST  Independent Watchdog reset
  *            @arg @ref RCC_FLAG_WWDGRST  Window Watchdog reset
  *            @arg @ref RCC_FLAG_LPWRRST  Low Power reset
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5U) == 1U) ? RCC->CR :                     \
                                        ((((__FLAG__) >> 5U) == 4U) ? RCC->CRRCR :                  \
                                        ((((__FLAG__) >> 5U) == 2U) ? RCC->BDCR :                   \
                                        ((((__FLAG__) >> 5U) == 3U) ? RCC->CSR : RCC->CIFR)))) &    \
                                          ((uint32_t)1U << ((__FLAG__) & RCC_FLAG_MASK))) != 0U) \
                                            ? 1U : 0U)

/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @addtogroup RCC_Private_Constants
  * @{
  */
/* Defines used for Flags */
#define CR_REG_INDEX              1U
#define BDCR_REG_INDEX            2U
#define CSR_REG_INDEX             3U
#define CRRCR_REG_INDEX           4U

#define RCC_FLAG_MASK             0x1FU

/* Define used for IS_RCC_CLOCKTYPE() */
#define RCC_CLOCKTYPE_ALL              (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2)  /*!< All clcoktype to configure */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_Private_Macros
  * @{
  */

#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                               || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE)   == RCC_OSCILLATORTYPE_HSE)   || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI)   == RCC_OSCILLATORTYPE_HSI)   || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI48) == RCC_OSCILLATORTYPE_HSI48) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI)   == RCC_OSCILLATORTYPE_LSI)   || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE)   == RCC_OSCILLATORTYPE_LSE))

#define IS_RCC_HSE(__HSE__)  (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON) || \
                              ((__HSE__) == RCC_HSE_BYPASS))

#define IS_RCC_LSE(__LSE__)  (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON) || \
                              ((__LSE__) == RCC_LSE_BYPASS))

#define IS_RCC_HSI(__HSI__)  (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))

#define IS_RCC_HSI_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= (RCC_ICSCR_HSITRIM >> RCC_ICSCR_HSITRIM_Pos))

#define IS_RCC_LSI(__LSI__)  (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))

#define IS_RCC_HSI48(__HSI48__)  (((__HSI48__) == RCC_HSI48_OFF) || ((__HSI48__) == RCC_HSI48_ON))

#define IS_RCC_PLL(__PLL__) (((__PLL__) == RCC_PLL_NONE) ||((__PLL__) == RCC_PLL_OFF) || \
                             ((__PLL__) == RCC_PLL_ON))

#define IS_RCC_PLLSOURCE(__SOURCE__) (((__SOURCE__) == RCC_PLLSOURCE_NONE) || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_HSI)  || \
                                      ((__SOURCE__) == RCC_PLLSOURCE_HSE))

#define IS_RCC_PLLM_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 16U))

#define IS_RCC_PLLN_VALUE(__VALUE__) ((8U <= (__VALUE__)) && ((__VALUE__) <= 127U))

#define IS_RCC_PLLP_VALUE(__VALUE__) (((__VALUE__) >= 2U) && ((__VALUE__) <= 31U))

#define IS_RCC_PLLQ_VALUE(__VALUE__) (((__VALUE__) == 2U) || ((__VALUE__) == 4U) || \
                                      ((__VALUE__) == 6U) || ((__VALUE__) == 8U))

#define IS_RCC_PLLR_VALUE(__VALUE__) (((__VALUE__) == 2U) || ((__VALUE__) == 4U) || \
                                      ((__VALUE__) == 6U) || ((__VALUE__) == 8U))

#define IS_RCC_CLOCKTYPE(__CLK__)  ((((__CLK__) & RCC_CLOCKTYPE_ALL) != 0x00UL) && (((__CLK__) & ~RCC_CLOCKTYPE_ALL) == 0x00UL))

#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK))

#define IS_RCC_HCLK(__HCLK__) (((__HCLK__) == RCC_SYSCLK_DIV1)   || ((__HCLK__) == RCC_SYSCLK_DIV2)   || \
                               ((__HCLK__) == RCC_SYSCLK_DIV4)   || ((__HCLK__) == RCC_SYSCLK_DIV8)   || \
                               ((__HCLK__) == RCC_SYSCLK_DIV16)  || ((__HCLK__) == RCC_SYSCLK_DIV64)  || \
                               ((__HCLK__) == RCC_SYSCLK_DIV128) || ((__HCLK__) == RCC_SYSCLK_DIV256) || \
                               ((__HCLK__) == RCC_SYSCLK_DIV512))

#define IS_RCC_PCLK(__PCLK__) (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
                               ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
                               ((__PCLK__) == RCC_HCLK_DIV16))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_RTCCLKSOURCE_NONE)   || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)    || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)    || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32))

#define IS_RCC_MCO(__MCOX__) ((__MCOX__) == RCC_MCO1)

#define IS_RCC_MCO1SOURCE(__SOURCE__) (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_SYSCLK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSI) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSE) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_PLLCLK) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_LSE) || \
                                       ((__SOURCE__) == RCC_MCO1SOURCE_HSI48))

#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1) || ((__DIV__) == RCC_MCODIV_2) || \
                                ((__DIV__) == RCC_MCODIV_4) || ((__DIV__) == RCC_MCODIV_8) || \
                                ((__DIV__) == RCC_MCODIV_16))

#define IS_RCC_LSE_DRIVE(__DRIVE__) (((__DRIVE__) == RCC_LSEDRIVE_LOW)        || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                     ((__DRIVE__) == RCC_LSEDRIVE_HIGH))

/**
  * @}
  */

/* Include RCC HAL Extended module */
#include "stm32g4xx_hal_rcc_ex.h"

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
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void              HAL_RCC_EnableCSS(void);
void              HAL_RCC_EnableLSECSS(void);
void              HAL_RCC_DisableLSECSS(void);
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLK1Freq(void);
uint32_t          HAL_RCC_GetPCLK2Freq(void);
void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);
/* CSS NMI IRQ handler */
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

#endif /* STM32G4xx_HAL_RCC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
