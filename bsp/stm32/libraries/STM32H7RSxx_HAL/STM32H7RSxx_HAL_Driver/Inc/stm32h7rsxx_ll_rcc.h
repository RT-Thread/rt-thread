/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC LL module.
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
#ifndef STM32H7RSxx_LL_RCC_H
#define STM32H7RSxx_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"
#include <math.h>

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup RCC_LL RCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Constants RCC Private Constants
  * @{
  */
/*
   LL_CLKSOURCE() macro output description

   31            24           16            8             0
   --------------------------------------------------------
   | Mask        | ClkSource   |  Bit       | Register    |
   |             |  Config     | Position   | Offset      |
   --------------------------------------------------------
*/
#define LL_RCC_REG_SHIFT     0U
#define LL_RCC_POS_SHIFT     8U
#define LL_RCC_CONFIG_SHIFT  16U
#define LL_RCC_MASK_SHIFT    24U

/* Clock source register offset vs CCIPR1 register */
#define CCIPR1_OFFSET        0x0UL
#define CCIPR2_OFFSET        0x4UL
#define CCIPR3_OFFSET        0x8UL
#define CCIPR4_OFFSET        0xCUL

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Macros RCC Private Macros
  * @{
  */
#if !defined(UNUSED)
#define UNUSED(x) ((void)(x))
#endif /* UNUSED */

#define LL_CLKSOURCE_SHIFT(__CLKSOURCE__)   (((__CLKSOURCE__) >> LL_RCC_POS_SHIFT   ) & 0x1FUL)

#define LL_CLKSOURCE_MASK(__CLKSOURCE__)   ((((__CLKSOURCE__) >> LL_RCC_MASK_SHIFT  ) &\
                                             0xFFUL) << LL_CLKSOURCE_SHIFT(__CLKSOURCE__))

#define LL_CLKSOURCE_CONFIG(__CLKSOURCE__) ((((__CLKSOURCE__) >> LL_RCC_CONFIG_SHIFT) &\
                                             0xFFUL) << LL_CLKSOURCE_SHIFT(__CLKSOURCE__))

#define LL_CLKSOURCE_REG(__CLKSOURCE__)     (((__CLKSOURCE__) >> LL_RCC_REG_SHIFT   ) & 0xFFUL)

#define LL_CLKSOURCE(__REG__, __MSK__, __POS__, __CLK__) ((uint32_t)((((__MSK__) >> (__POS__)) << LL_RCC_MASK_SHIFT) | \
                                                                     (( __POS__              ) << LL_RCC_POS_SHIFT)  | \
                                                                     (( __REG__              ) << LL_RCC_REG_SHIFT)  | \
                                                                     (((__CLK__) >> (__POS__)) << LL_RCC_CONFIG_SHIFT)))

/**
  * @}
  */

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
  uint32_t SYSCLK_Frequency;
  uint32_t CPUCLK_Frequency;
  uint32_t HCLK_Frequency;
  uint32_t PCLK1_Frequency;
  uint32_t PCLK2_Frequency;
  uint32_t PCLK4_Frequency;
  uint32_t PCLK5_Frequency;
} LL_RCC_ClocksTypeDef;

/**
  * @}
  */

/**
  * @brief  PLL Clocks Frequency Structure
  */
typedef struct
{
  uint32_t PLL_P_Frequency;
  uint32_t PLL_Q_Frequency;
  uint32_t PLL_R_Frequency;
  uint32_t PLL_S_Frequency;
  uint32_t PLL_T_Frequency;
} LL_PLL_ClocksTypeDef;

/**
  * @brief  PLL Spread Spectrum Mode Structure
  */
typedef struct
{
  uint16_t ModulationPeriod;  /* Modulation Period (value between 0 to 2^13-1) */
  uint16_t IncrementStep;     /* Modulation Depth (value between 0 to 2^15-1) */
  uint16_t SpreadMode;        /* LL_RCC_PLL_SPREAD_CENTER or LL_RCC_PLL_SPREAD_DOWN */
  uint16_t DitheringRPDFN;    /* Rectangular probability density function noise enable/disable */
  uint16_t DitheringTPDFN;    /* Triangular probability density function noise enable/disable */
} LL_PLL_SpreadSpectrumTypeDef;

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/* Exported variables --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Variables RCC Exported Variables
  * @{
  */
extern const uint8_t LL_RCC_PrescTable[16];

/**
  * @}
  */

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
#define HSE_VALUE    24000000U  /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE    64000000U  /*!< Value of the HSI oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined  (CSI_VALUE)
#define CSI_VALUE    4000000U   /*!< Value of the CSI oscillator in Hz */
#endif /* CSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768U     /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE    32000U     /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */

#if !defined  (EXTERNAL_CLOCK_VALUE)
#define EXTERNAL_CLOCK_VALUE    12288000U /*!< Value of the I2S_CKIN external oscillator in Hz */
#endif /* EXTERNAL_CLOCK_VALUE */

#if !defined  (HSI48_VALUE)
#define HSI48_VALUE  48000000U  /*!< Value of the HSI48 oscillator in Hz */
#endif /* HSI48_VALUE */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSIDIV  HSI oscillator divider
  * @{
  */
#define LL_RCC_HSI_DIV_1                   0U
#define LL_RCC_HSI_DIV_2                   RCC_CR_HSIDIV_0
#define LL_RCC_HSI_DIV_4                   RCC_CR_HSIDIV_1
#define LL_RCC_HSI_DIV_8                   RCC_CR_HSIDIV
/**
  * @}
  */

/** @defgroup LL_RCC_EC_XSPI1SWP  XSXPI1 kernel clock switch position
  * @{
  */
#define LL_RCC_SWP_XSPI1_NEUTRAL           0U
#define LL_RCC_SWP_XSPI1_HCLK5             RCC_CKPROTR_XSPI1SWP_0
#define LL_RCC_SWP_XSPI1_PLL2S             RCC_CKPROTR_XSPI1SWP_1
#define LL_RCC_SWP_XSPI1_PLL2T             (RCC_CKPROTR_XSPI1SWP_1 | RCC_CKPROTR_XSPI1SWP_0)
#define LL_RCC_SWP_XSPI1_HCLK_DIV4         RCC_CKPROTR_XSPI1SWP_2
/**
  * @}
  */

/** @defgroup LL_RCC_EC_XSPI2SWP  SXPI2 kernel clock switch position
  * @{
  */
#define LL_RCC_SWP_XSPI2_NEUTRAL           0U
#define LL_RCC_SWP_XSPI2_HCLK5             RCC_CKPROTR_XSPI2SWP_0
#define LL_RCC_SWP_XSPI2_PLL2S             RCC_CKPROTR_XSPI2SWP_1
#define LL_RCC_SWP_XSPI2_PLL2T             (RCC_CKPROTR_XSPI2SWP_1 | RCC_CKPROTR_XSPI2SWP_0)
#define LL_RCC_SWP_XSPI2_HCLK_DIV4         RCC_CKPROTR_XSPI2SWP_2
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FMCSWP  FMC kernel clock switch position
  * @{
  */
#define LL_RCC_SWP_FMC_NEUTRAL             0U
#define LL_RCC_SWP_FMC_HCLK5               RCC_CKPROTR_FMCSWP_0
#define LL_RCC_SWP_FMC_PLL1Q               RCC_CKPROTR_FMCSWP_1
#define LL_RCC_SWP_FMC_PLL2R               (RCC_CKPROTR_FMCSWP_1 | RCC_CKPROTR_FMCSWP_0)
#define LL_RCC_SWP_FMC_HSI                 RCC_CKPROTR_FMCSWP_2
#define LL_RCC_SWP_FMC_HCLK_DIV4           (RCC_CKPROTR_FMCSWP_2 | RCC_CKPROTR_FMCSWP_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW                0U
#define LL_RCC_LSEDRIVE_MEDIUMLOW          RCC_BDCR_LSEDRV_0
#define LL_RCC_LSEDRIVE_MEDIUMHIGH         RCC_BDCR_LSEDRV_1
#define LL_RCC_LSEDRIVE_HIGH               RCC_BDCR_LSEDRV
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_HSI           0U
#define LL_RCC_SYS_CLKSOURCE_CSI           RCC_CFGR_SW_0
#define LL_RCC_SYS_CLKSOURCE_HSE           RCC_CFGR_SW_1
#define LL_RCC_SYS_CLKSOURCE_PLL1          (RCC_CFGR_SW_1 | RCC_CFGR_SW_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI    0U                                /*!< HSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_CSI    RCC_CFGR_SWS_0                    /*!< CSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE    RCC_CFGR_SWS_1                    /*!< HSE used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_PLL1   (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0) /*!< PLL1 used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSWAKEUP_CLKSOURCE  System wakeup clock source
  * @{
  */
#define LL_RCC_SYSWAKEUP_CLKSOURCE_HSI     0U
#define LL_RCC_SYSWAKEUP_CLKSOURCE_CSI     RCC_CFGR_STOPWUCK
/**
  * @}
  */

/** @defgroup RCC_LL_EC_KERWAKEUP_CLKSOURCE  Kernel wakeup clock source
  * @{
  */
#define LL_RCC_KERWAKEUP_CLKSOURCE_HSI     0U
#define LL_RCC_KERWAKEUP_CLKSOURCE_CSI     RCC_CFGR_STOPKERWUCK
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV  System prescaler
  * @{
  */
#define LL_RCC_SYSCLK_DIV_1                0U
#define LL_RCC_SYSCLK_DIV_2                RCC_CDCFGR_CPRE_3
#define LL_RCC_SYSCLK_DIV_4                (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_0)
#define LL_RCC_SYSCLK_DIV_8                (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_1)
#define LL_RCC_SYSCLK_DIV_16               (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_1 | RCC_CDCFGR_CPRE_0)
#define LL_RCC_SYSCLK_DIV_64               (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2)
#define LL_RCC_SYSCLK_DIV_128              (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2 | RCC_CDCFGR_CPRE_0)
#define LL_RCC_SYSCLK_DIV_256              (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2 | RCC_CDCFGR_CPRE_1)
#define LL_RCC_SYSCLK_DIV_512              RCC_CDCFGR_CPRE
/**
  * @}
  */

/** @defgroup RCC_LL_EC_AHB_DIV  AHB prescaler
  * @{
  */
#define LL_RCC_AHB_DIV_1                   0U
#define LL_RCC_AHB_DIV_2                   RCC_BMCFGR_BMPRE_3
#define LL_RCC_AHB_DIV_4                   (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_0)
#define LL_RCC_AHB_DIV_8                   (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_1)
#define LL_RCC_AHB_DIV_16                  (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_1 | RCC_BMCFGR_BMPRE_0)
#define LL_RCC_AHB_DIV_64                  (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_2)
#define LL_RCC_AHB_DIV_128                 (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_2 | RCC_BMCFGR_BMPRE_0)
#define LL_RCC_AHB_DIV_256                 (RCC_BMCFGR_BMPRE_3 | RCC_BMCFGR_BMPRE_2 | RCC_BMCFGR_BMPRE_1)
#define LL_RCC_AHB_DIV_512                 RCC_BMCFGR_BMPRE
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV  APB1 prescaler
  * @{
  */
#define LL_RCC_APB1_DIV_1                  0U
#define LL_RCC_APB1_DIV_2                  RCC_APBCFGR_PPRE1_2
#define LL_RCC_APB1_DIV_4                  (RCC_APBCFGR_PPRE1_2 | RCC_APBCFGR_PPRE1_0)
#define LL_RCC_APB1_DIV_8                  (RCC_APBCFGR_PPRE1_2 | RCC_APBCFGR_PPRE1_1)
#define LL_RCC_APB1_DIV_16                 RCC_APBCFGR_PPRE1
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB2_DIV  APB2 prescaler
  * @{
  */
#define LL_RCC_APB2_DIV_1                  0U
#define LL_RCC_APB2_DIV_2                  RCC_APBCFGR_PPRE2_2
#define LL_RCC_APB2_DIV_4                  (RCC_APBCFGR_PPRE2_2 | RCC_APBCFGR_PPRE2_0)
#define LL_RCC_APB2_DIV_8                  (RCC_APBCFGR_PPRE2_2 | RCC_APBCFGR_PPRE2_1)
#define LL_RCC_APB2_DIV_16                 RCC_APBCFGR_PPRE2
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB4_DIV  APB4 prescaler
  * @{
  */
#define LL_RCC_APB4_DIV_1                  0U
#define LL_RCC_APB4_DIV_2                  RCC_APBCFGR_PPRE4_2
#define LL_RCC_APB4_DIV_4                  (RCC_APBCFGR_PPRE4_2 | RCC_APBCFGR_PPRE4_0)
#define LL_RCC_APB4_DIV_8                  (RCC_APBCFGR_PPRE4_2 | RCC_APBCFGR_PPRE4_1)
#define LL_RCC_APB4_DIV_16                 RCC_APBCFGR_PPRE4
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB5_DIV  APB5 prescaler
  * @{
  */
#define LL_RCC_APB5_DIV_1                  0U
#define LL_RCC_APB5_DIV_2                  RCC_APBCFGR_PPRE5_2
#define LL_RCC_APB5_DIV_4                  (RCC_APBCFGR_PPRE5_2 | RCC_APBCFGR_PPRE5_0)
#define LL_RCC_APB5_DIV_8                  (RCC_APBCFGR_PPRE5_2 | RCC_APBCFGR_PPRE5_1)
#define LL_RCC_APB5_DIV_16                 RCC_APBCFGR_PPRE5
/**
  * @}
  */


/** @defgroup RCC_LL_EC_MCOxSOURCE  MCO source selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_HSI              ((RCC_CFGR_MCO1SEL>>16U) | 0U)
#define LL_RCC_MCO1SOURCE_LSE              ((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_0)
#define LL_RCC_MCO1SOURCE_HSE              ((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_1)
#define LL_RCC_MCO1SOURCE_PLL1Q            ((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_1 | RCC_CFGR_MCO1SEL_0)
#define LL_RCC_MCO1SOURCE_HSI48            ((RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_2)
#define LL_RCC_MCO2SOURCE_SYSCLK           ((RCC_CFGR_MCO2SEL>>16U) | 0U)
#define LL_RCC_MCO2SOURCE_PLL2P            ((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_0)
#define LL_RCC_MCO2SOURCE_HSE              ((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_1)
#define LL_RCC_MCO2SOURCE_PLL1P            ((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_1 | RCC_CFGR_MCO2SEL_0)
#define LL_RCC_MCO2SOURCE_CSI              ((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_2)
#define LL_RCC_MCO2SOURCE_LSI              ((RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_2 | RCC_CFGR_MCO2SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCOx_DIV  MCO prescaler
  * @{
  */
#define LL_RCC_MCO1_DIV_1                  ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_0)
#define LL_RCC_MCO1_DIV_2                  ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_1)
#define LL_RCC_MCO1_DIV_3                  ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_1)
#define LL_RCC_MCO1_DIV_4                  ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_2)
#define LL_RCC_MCO1_DIV_5                  ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_2)
#define LL_RCC_MCO1_DIV_6                  ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_2)
#define LL_RCC_MCO1_DIV_7                  ((RCC_CFGR_MCO1PRE>>16U) |\
                                            RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_2)
#define LL_RCC_MCO1_DIV_8                  ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_3)
#define LL_RCC_MCO1_DIV_9                  ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_3)
#define LL_RCC_MCO1_DIV_10                 ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_3)
#define LL_RCC_MCO1_DIV_11                 ((RCC_CFGR_MCO1PRE>>16U) |\
                                            RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_3)
#define LL_RCC_MCO1_DIV_12                 ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_3)
#define LL_RCC_MCO1_DIV_13                 ((RCC_CFGR_MCO1PRE>>16U) |\
                                            RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_3)
#define LL_RCC_MCO1_DIV_14                 ((RCC_CFGR_MCO1PRE>>16U) |\
                                            RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_3)
#define LL_RCC_MCO1_DIV_15                 ((RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE)
#define LL_RCC_MCO2_DIV_1                  ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_0)
#define LL_RCC_MCO2_DIV_2                  ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_1)
#define LL_RCC_MCO2_DIV_3                  ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_0 | RCC_CFGR_MCO2PRE_1)
#define LL_RCC_MCO2_DIV_4                  ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_2)
#define LL_RCC_MCO2_DIV_5                  ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_0 | RCC_CFGR_MCO2PRE_2)
#define LL_RCC_MCO2_DIV_6                  ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_2)
#define LL_RCC_MCO2_DIV_7                  ((RCC_CFGR_MCO2PRE>>16U) |\
                                            RCC_CFGR_MCO2PRE_0 | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_2)
#define LL_RCC_MCO2_DIV_8                  ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_3)
#define LL_RCC_MCO2_DIV_9                  ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_0 | RCC_CFGR_MCO2PRE_3)
#define LL_RCC_MCO2_DIV_10                 ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_3)
#define LL_RCC_MCO2_DIV_11                 ((RCC_CFGR_MCO2PRE>>16U) |\
                                            RCC_CFGR_MCO2PRE_0 | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_3)
#define LL_RCC_MCO2_DIV_12                 ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_3)
#define LL_RCC_MCO2_DIV_13                 ((RCC_CFGR_MCO2PRE>>16U) |\
                                            RCC_CFGR_MCO2PRE_0 | RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_3)
#define LL_RCC_MCO2_DIV_14                 ((RCC_CFGR_MCO2PRE>>16U) |\
                                            RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_3)
#define LL_RCC_MCO2_DIV_15                 ((RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE)

/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_HSEDIV  HSE prescaler for RTC clock
  * @{
  */
#define LL_RCC_RTC_NOCLOCK                  0U
#define LL_RCC_RTC_HSE_DIV_2                (RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_3                (RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_4                (RCC_CFGR_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_5                (RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_6                (RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_7                (RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_8                (RCC_CFGR_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_9                (RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_10               (RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_11               (RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_12               (RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_13               (RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_14               (RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_15               (RCC_CFGR_RTCPRE_3 |\
                                             RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_16               (RCC_CFGR_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_17               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_18               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_19               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_20               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_21               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_22               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_23               (RCC_CFGR_RTCPRE_4 |\
                                             RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_24               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_25               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_26               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_27               (RCC_CFGR_RTCPRE_4 |\
                                             RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_28               (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_29               (RCC_CFGR_RTCPRE_4 |\
                                             RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_30               (RCC_CFGR_RTCPRE_4 |\
                                             RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_31               (RCC_CFGR_RTCPRE_4 |\
                                             RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_32               (RCC_CFGR_RTCPRE_5)
#define LL_RCC_RTC_HSE_DIV_33               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_34               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_35               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_36               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_37               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_38               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_39               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_40               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_41               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_42               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_43               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_44               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_45               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_46               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_47               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_48               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_49               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_50               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_51               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_52               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_53               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_54               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_55               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_56               (RCC_CFGR_RTCPRE_5 | RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_57               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_58               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_59               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_60               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_61               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_62               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_63               (RCC_CFGR_RTCPRE_5 |\
                                             RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_2 | RCC_CFGR_RTCPRE_1 | RCC_CFGR_RTCPRE_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC_CLKSOURCE  Peripheral ADC clock source selection
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE_PLL2P          0U
#define LL_RCC_ADC_CLKSOURCE_PLL3R          RCC_CCIPR1_ADCSEL_0
#define LL_RCC_ADC_CLKSOURCE_CLKP           RCC_CCIPR1_ADCSEL_1
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADFx_CLKSOURCE  Peripheral ADF clock source selection
  * @{
  */
#define LL_RCC_ADF1_CLKSOURCE_HCLK          0U
#define LL_RCC_ADF1_CLKSOURCE_PLL2P         RCC_CCIPR1_ADF1SEL_0
#define LL_RCC_ADF1_CLKSOURCE_PLL3P         RCC_CCIPR1_ADF1SEL_1
#define LL_RCC_ADF1_CLKSOURCE_I2S_CKIN      (RCC_CCIPR1_ADF1SEL_1 |  RCC_CCIPR1_ADF1SEL_0)
#define LL_RCC_ADF1_CLKSOURCE_CSI           RCC_CCIPR1_ADF1SEL_2
#define LL_RCC_ADF1_CLKSOURCE_HSI           (RCC_CCIPR1_ADF1SEL_2 |  RCC_CCIPR1_ADF1SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_CEC_CLKSOURCE  Peripheral CEC clock source selection
  * @{
  */
#define LL_RCC_CEC_CLKSOURCE_LSE            0U
#define LL_RCC_CEC_CLKSOURCE_LSI            RCC_CCIPR2_CECSEL_0
#define LL_RCC_CEC_CLKSOURCE_CSI_DIV_122    RCC_CCIPR2_CECSEL_1
/**
  * @}
  */

/** @defgroup RCC_LL_EC_CLKP_CLKSOURCE  Peripheral CLKP clock source selection
  * @{
  */
#define LL_RCC_CLKP_CLKSOURCE_HSI           0U
#define LL_RCC_CLKP_CLKSOURCE_CSI           RCC_CCIPR1_CKPERSEL_0
#define LL_RCC_CLKP_CLKSOURCE_HSE           RCC_CCIPR1_CKPERSEL_1
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ETHxPHY_CLKSOURCE  Peripheral ETHPHY clock source selection
  * @{
  */
#define LL_RCC_ETH1PHY_CLKSOURCE_HSE        0U
#define LL_RCC_ETH1PHY_CLKSOURCE_PLL3S      RCC_CCIPR1_ETH1PHYCKSEL
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ETHxREF_CLKSOURCE  Peripheral ETHREF clock source selection
  * @{
  */
#define LL_RCC_ETH1REF_CLKSOURCE_RMII       0U
#define LL_RCC_ETH1REF_CLKSOURCE_HSE        RCC_CCIPR1_ETH1REFCKSEL_0
#define LL_RCC_ETH1REF_CLKSOURCE_FB         RCC_CCIPR1_ETH1REFCKSEL_1
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FDCAN_CLKSOURCE  Peripheral FDCAN clock source selection
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE_HSE          0U
#define LL_RCC_FDCAN_CLKSOURCE_PLL1Q        RCC_CCIPR2_FDCANSEL_0
#define LL_RCC_FDCAN_CLKSOURCE_PLL2Q        RCC_CCIPR2_FDCANSEL_1
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FMC_CLKSOURCE  Peripheral FMC clock source selection
  * @{
  */
#define LL_RCC_FMC_CLKSOURCE_HCLK           0U
#define LL_RCC_FMC_CLKSOURCE_PLL1Q          RCC_CCIPR1_FMCSEL_0
#define LL_RCC_FMC_CLKSOURCE_PLL2R          RCC_CCIPR1_FMCSEL_1
#define LL_RCC_FMC_CLKSOURCE_HSI            (RCC_CCIPR1_FMCSEL_1 | RCC_CCIPR1_FMCSEL_0)
#define LL_RCC_FMC_CLKSOURCE_HCLK_DIV4      LL_RCC_SWP_FMC_HCLK_DIV4  /* Recovery: Read-only */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2Cx_CLKSOURCE  Peripheral I2C clock source selection
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1         LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C1_I3C1SEL,  RCC_CCIPR2_I2C1_I3C1SEL_Pos,  0U)
#define LL_RCC_I2C1_CLKSOURCE_PLL3R         LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C1_I3C1SEL,  RCC_CCIPR2_I2C1_I3C1SEL_Pos,  RCC_CCIPR2_I2C1_I3C1SEL_0)
#define LL_RCC_I2C1_CLKSOURCE_HSI           LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C1_I3C1SEL,  RCC_CCIPR2_I2C1_I3C1SEL_Pos,  RCC_CCIPR2_I2C1_I3C1SEL_1)
#define LL_RCC_I2C1_CLKSOURCE_CSI           LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C1_I3C1SEL,  RCC_CCIPR2_I2C1_I3C1SEL_Pos,  RCC_CCIPR2_I2C1_I3C1SEL_1 |\
                                                         RCC_CCIPR2_I2C1_I3C1SEL_0)

#define LL_RCC_I2C23_CLKSOURCE_PCLK1        LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C23SEL,  RCC_CCIPR2_I2C23SEL_Pos,  0U)
#define LL_RCC_I2C23_CLKSOURCE_PLL3R        LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C23SEL,  RCC_CCIPR2_I2C23SEL_Pos,  RCC_CCIPR2_I2C23SEL_0)
#define LL_RCC_I2C23_CLKSOURCE_HSI          LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C23SEL,  RCC_CCIPR2_I2C23SEL_Pos,  RCC_CCIPR2_I2C23SEL_1)
#define LL_RCC_I2C23_CLKSOURCE_CSI          LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C23SEL,  RCC_CCIPR2_I2C23SEL_Pos,  RCC_CCIPR2_I2C23SEL_1 |\
                                                         RCC_CCIPR2_I2C23SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I3Cx_CLKSOURCE  Peripheral I3C clock source selection
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE_PCLK1         0U
#define LL_RCC_I3C1_CLKSOURCE_PLL3R         RCC_CCIPR2_I2C1_I3C1SEL_0
#define LL_RCC_I3C1_CLKSOURCE_HSI           RCC_CCIPR2_I2C1_I3C1SEL_1
#define LL_RCC_I3C1_CLKSOURCE_CSI           (RCC_CCIPR2_I2C1_I3C1SEL_1 | RCC_CCIPR2_I2C1_I3C1SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIMx_CLKSOURCE  Peripheral LPTIM clock source selection
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_PCLK1       LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_LPTIM1SEL,  RCC_CCIPR2_LPTIM1SEL_Pos,  0U)
#define LL_RCC_LPTIM1_CLKSOURCE_PLL2P       LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_LPTIM1SEL,  RCC_CCIPR2_LPTIM1SEL_Pos,  RCC_CCIPR2_LPTIM1SEL_0)
#define LL_RCC_LPTIM1_CLKSOURCE_PLL3R       LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_LPTIM1SEL,  RCC_CCIPR2_LPTIM1SEL_Pos,  RCC_CCIPR2_LPTIM1SEL_1)
#define LL_RCC_LPTIM1_CLKSOURCE_LSE         LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_LPTIM1SEL,  RCC_CCIPR2_LPTIM1SEL_Pos,  RCC_CCIPR2_LPTIM1SEL_1 |\
                                                         RCC_CCIPR2_LPTIM1SEL_0)
#define LL_RCC_LPTIM1_CLKSOURCE_LSI         LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_LPTIM1SEL,  RCC_CCIPR2_LPTIM1SEL_Pos,  RCC_CCIPR2_LPTIM1SEL_2)
#define LL_RCC_LPTIM1_CLKSOURCE_CLKP        LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_LPTIM1SEL,  RCC_CCIPR2_LPTIM1SEL_Pos,  RCC_CCIPR2_LPTIM1SEL_2 |\
                                                         RCC_CCIPR2_LPTIM1SEL_0)

#define LL_RCC_LPTIM23_CLKSOURCE_PCLK4      LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM23SEL,   RCC_CCIPR4_LPTIM23SEL_Pos,   0U)
#define LL_RCC_LPTIM23_CLKSOURCE_PLL2P      LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM23SEL,   RCC_CCIPR4_LPTIM23SEL_Pos,   RCC_CCIPR4_LPTIM23SEL_0)
#define LL_RCC_LPTIM23_CLKSOURCE_PLL3R      LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM23SEL,   RCC_CCIPR4_LPTIM23SEL_Pos,   RCC_CCIPR4_LPTIM23SEL_1)
#define LL_RCC_LPTIM23_CLKSOURCE_LSE        LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM23SEL,   RCC_CCIPR4_LPTIM23SEL_Pos,   RCC_CCIPR4_LPTIM23SEL_1 |\
                                                         RCC_CCIPR4_LPTIM23SEL_0)
#define LL_RCC_LPTIM23_CLKSOURCE_LSI        LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM23SEL,   RCC_CCIPR4_LPTIM23SEL_Pos,   RCC_CCIPR4_LPTIM23SEL_2)
#define LL_RCC_LPTIM23_CLKSOURCE_CLKP       LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM23SEL,   RCC_CCIPR4_LPTIM23SEL_Pos,   RCC_CCIPR4_LPTIM23SEL_2 |\
                                                         RCC_CCIPR4_LPTIM23SEL_0)

#define LL_RCC_LPTIM45_CLKSOURCE_PCLK4      LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_Pos, 0U)
#define LL_RCC_LPTIM45_CLKSOURCE_PLL2P      LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL_0)
#define LL_RCC_LPTIM45_CLKSOURCE_PLL3R      LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL_1)
#define LL_RCC_LPTIM45_CLKSOURCE_LSE        LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL_1 |\
                                                         RCC_CCIPR4_LPTIM45SEL_0)
#define LL_RCC_LPTIM45_CLKSOURCE_LSI        LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL_2)
#define LL_RCC_LPTIM45_CLKSOURCE_CLKP       LL_CLKSOURCE(CCIPR4_OFFSET,  RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL_2 |\
                                                         RCC_CCIPR4_LPTIM45SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUARTx_CLKSOURCE  Peripheral LPUART clock source selection
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK4      0U
#define LL_RCC_LPUART1_CLKSOURCE_PLL2Q      RCC_CCIPR4_LPUART1SEL_0
#define LL_RCC_LPUART1_CLKSOURCE_PLL3Q      RCC_CCIPR4_LPUART1SEL_1
#define LL_RCC_LPUART1_CLKSOURCE_HSI        (RCC_CCIPR4_LPUART1SEL_1 | RCC_CCIPR4_LPUART1SEL_0)
#define LL_RCC_LPUART1_CLKSOURCE_CSI        RCC_CCIPR4_LPUART1SEL_2
#define LL_RCC_LPUART1_CLKSOURCE_LSE        (RCC_CCIPR4_LPUART1SEL_2 | RCC_CCIPR4_LPUART1SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LTDC_CLKSOURCE  Peripheral LTDC clock source selection
  * @{
  */
#define LL_RCC_LTDC_CLKSOURCE_PLL3R         0U
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PSSI_CLKSOURCE  Peripheral PSSI clock source selection
  * @{
  */
#define LL_RCC_PSSI_CLKSOURCE_PLL3R         0U
#define LL_RCC_PSSI_CLKSOURCE_CLKP          RCC_CCIPR1_PSSISEL
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SAIx_CLKSOURCE  Peripheral SAI clock source selection
  * @{
  */
#define LL_RCC_SAI1_CLKSOURCE_PLL1Q         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI1SEL, RCC_CCIPR3_SAI1SEL_Pos, 0U)
#define LL_RCC_SAI1_CLKSOURCE_PLL2P         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI1SEL, RCC_CCIPR3_SAI1SEL_Pos, RCC_CCIPR3_SAI1SEL_0)
#define LL_RCC_SAI1_CLKSOURCE_PLL3P         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI1SEL, RCC_CCIPR3_SAI1SEL_Pos, RCC_CCIPR3_SAI1SEL_1)
#define LL_RCC_SAI1_CLKSOURCE_I2S_CKIN      LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI1SEL, RCC_CCIPR3_SAI1SEL_Pos, RCC_CCIPR3_SAI1SEL_0 |\
                                                         RCC_CCIPR3_SAI1SEL_1)
#define LL_RCC_SAI1_CLKSOURCE_CLKP          LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI1SEL, RCC_CCIPR3_SAI1SEL_Pos, RCC_CCIPR3_SAI1SEL_2)

#define LL_RCC_SAI2_CLKSOURCE_PLL1Q         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI2SEL, RCC_CCIPR3_SAI2SEL_Pos, 0U)
#define LL_RCC_SAI2_CLKSOURCE_PLL2P         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI2SEL, RCC_CCIPR3_SAI2SEL_Pos, RCC_CCIPR3_SAI2SEL_0)
#define LL_RCC_SAI2_CLKSOURCE_PLL3P         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI2SEL, RCC_CCIPR3_SAI2SEL_Pos, RCC_CCIPR3_SAI2SEL_1)
#define LL_RCC_SAI2_CLKSOURCE_I2S_CKIN      LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI2SEL, RCC_CCIPR3_SAI2SEL_Pos, RCC_CCIPR3_SAI2SEL_1 |\
                                                         RCC_CCIPR3_SAI2SEL_0)
#define LL_RCC_SAI2_CLKSOURCE_CLKP          LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI2SEL, RCC_CCIPR3_SAI2SEL_Pos, RCC_CCIPR3_SAI2SEL_2)
#define LL_RCC_SAI2_CLKSOURCE_SPDIFRX       LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI2SEL, RCC_CCIPR3_SAI2SEL_Pos, RCC_CCIPR3_SAI1SEL_2 |\
                                                         RCC_CCIPR3_SAI2SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SDMMC_CLKSOURCE  Peripheral SDMMC clock source selection
  * @{
  */
#define LL_RCC_SDMMC_CLKSOURCE_PLL2S        0U
#define LL_RCC_SDMMC_CLKSOURCE_PLL2T        RCC_CCIPR1_SDMMC12SEL
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPDIF_CLKSOURCE  Peripheral SPDIF clock source selection
  * @{
  */
#define LL_RCC_SPDIFRX_CLKSOURCE_PLL1Q      0U
#define LL_RCC_SPDIFRX_CLKSOURCE_PLL2R      RCC_CCIPR2_SPDIFRXSEL_0
#define LL_RCC_SPDIFRX_CLKSOURCE_PLL3R      RCC_CCIPR2_SPDIFRXSEL_1
#define LL_RCC_SPDIFRX_CLKSOURCE_HSI        (RCC_CCIPR2_SPDIFRXSEL_0 | RCC_CCIPR2_SPDIFRXSEL_1)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPIx_CLKSOURCE  Peripheral SPI clock source selection
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE_PLL1Q         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_Pos, 0U)
#define LL_RCC_SPI1_CLKSOURCE_PLL2P         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL_0)
#define LL_RCC_SPI1_CLKSOURCE_PLL3P         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL_1)
#define LL_RCC_SPI1_CLKSOURCE_I2S_CKIN      LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL_1 |\
                                                         RCC_CCIPR3_SPI1SEL_0)
#define LL_RCC_SPI1_CLKSOURCE_CLKP          LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL_2)

#define LL_RCC_SPI23_CLKSOURCE_PLL1Q        LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_Pos, 0U)
#define LL_RCC_SPI23_CLKSOURCE_PLL2P        LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL_0)
#define LL_RCC_SPI23_CLKSOURCE_PLL3P        LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL_1)
#define LL_RCC_SPI23_CLKSOURCE_I2S_CKIN     LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL_1 |\
                                                         RCC_CCIPR2_SPI23SEL_0)
#define LL_RCC_SPI23_CLKSOURCE_CLKP         LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL_2)

#define LL_RCC_SPI45_CLKSOURCE_PCLK2        LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_Pos, 0U)
#define LL_RCC_SPI45_CLKSOURCE_PLL2Q        LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL_0)
#define LL_RCC_SPI45_CLKSOURCE_PLL3Q        LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL_1)
#define LL_RCC_SPI45_CLKSOURCE_HSI          LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL_1 |\
                                                         RCC_CCIPR3_SPI45SEL_0)
#define LL_RCC_SPI45_CLKSOURCE_CSI          LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL_2)
#define LL_RCC_SPI45_CLKSOURCE_HSE          LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL_2 |\
                                                         RCC_CCIPR3_SPI45SEL_0)

#define LL_RCC_SPI6_CLKSOURCE_PCLK4         LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_Pos, 0U)
#define LL_RCC_SPI6_CLKSOURCE_PLL2Q         LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL_0)
#define LL_RCC_SPI6_CLKSOURCE_PLL3Q         LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL_1)
#define LL_RCC_SPI6_CLKSOURCE_HSI           LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL_1 |\
                                                         RCC_CCIPR4_SPI6SEL_0)
#define LL_RCC_SPI6_CLKSOURCE_CSI           LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL_2)
#define LL_RCC_SPI6_CLKSOURCE_HSE           LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL_2 |\
                                                         RCC_CCIPR4_SPI6SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USARTx_CLKSOURCE  Peripheral USART clock source selection
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK2       LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_USART1SEL, RCC_CCIPR3_USART1SEL_Pos, 0U)
#define LL_RCC_USART1_CLKSOURCE_PLL2Q       LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_USART1SEL, RCC_CCIPR3_USART1SEL_Pos, RCC_CCIPR3_USART1SEL_0)
#define LL_RCC_USART1_CLKSOURCE_PLL3Q       LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_USART1SEL, RCC_CCIPR3_USART1SEL_Pos, RCC_CCIPR3_USART1SEL_1)
#define LL_RCC_USART1_CLKSOURCE_HSI         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_USART1SEL, RCC_CCIPR3_USART1SEL_Pos, RCC_CCIPR3_USART1SEL_1 |\
                                                         RCC_CCIPR3_USART1SEL_0)
#define LL_RCC_USART1_CLKSOURCE_CSI         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_USART1SEL, RCC_CCIPR3_USART1SEL_Pos, RCC_CCIPR3_USART1SEL_2)
#define LL_RCC_USART1_CLKSOURCE_LSE         LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_USART1SEL, RCC_CCIPR3_USART1SEL_Pos, RCC_CCIPR3_USART1SEL_2 |\
                                                         RCC_CCIPR3_USART1SEL_0)

#define LL_RCC_USART234578_CLKSOURCE_PCLK1  LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_UART234578SEL, RCC_CCIPR2_UART234578SEL_Pos, 0U)
#define LL_RCC_USART234578_CLKSOURCE_PLL2Q  LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_UART234578SEL, RCC_CCIPR2_UART234578SEL_Pos, RCC_CCIPR2_UART234578SEL_0)
#define LL_RCC_USART234578_CLKSOURCE_PLL3Q  LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_UART234578SEL, RCC_CCIPR2_UART234578SEL_Pos, RCC_CCIPR2_UART234578SEL_1)
#define LL_RCC_USART234578_CLKSOURCE_HSI    LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_UART234578SEL, RCC_CCIPR2_UART234578SEL_Pos, RCC_CCIPR2_UART234578SEL_1 |\
                                                         RCC_CCIPR2_UART234578SEL_0)
#define LL_RCC_USART234578_CLKSOURCE_CSI    LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_UART234578SEL, RCC_CCIPR2_UART234578SEL_Pos, RCC_CCIPR2_UART234578SEL_2)
#define LL_RCC_USART234578_CLKSOURCE_LSE    LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_UART234578SEL, RCC_CCIPR2_UART234578SEL_Pos, RCC_CCIPR2_UART234578SEL_2 |\
                                                         RCC_CCIPR2_UART234578SEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_OTGFS_CLKSOURCE  Peripheral OTGFS kernel clock source selection
  * @{
  */
#define LL_RCC_OTGFS_CLKSOURCE_HSI48        0U
#define LL_RCC_OTGFS_CLKSOURCE_PLL3Q        RCC_CCIPR1_OTGFSSEL_0
#define LL_RCC_OTGFS_CLKSOURCE_HSE          RCC_CCIPR1_OTGFSSEL_1
#define LL_RCC_OTGFS_CLKSOURCE_CLK48        (RCC_CCIPR1_OTGFSSEL_1 | RCC_CCIPR1_OTGFSSEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USBPHYC_CLKSOURCE  Peripheral USBPHYC kernel clock source selection
  * @{
  */
#define LL_RCC_USBPHYC_CLKSOURCE_HSE        0U
#define LL_RCC_USBPHYC_CLKSOURCE_HSE_DIV_2  RCC_CCIPR1_USBPHYCSEL_0
#define LL_RCC_USBPHYC_CLKSOURCE_PLL3Q      RCC_CCIPR1_USBPHYCSEL_1
#define LL_RCC_USBPHYC_CLKSOURCE_DISABLE    (RCC_CCIPR1_USBPHYCSEL_1 | RCC_CCIPR1_USBPHYCSEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USBREF_CLKSOURCE  Peripheral USBREF clock source selection
  * @{
  */
#define LL_RCC_USBREF_CLKSOURCE_16M         (RCC_CCIPR1_USBREFCKSEL_1 | RCC_CCIPR1_USBREFCKSEL_0)
#define LL_RCC_USBREF_CLKSOURCE_19_2M       RCC_CCIPR1_USBREFCKSEL_3
#define LL_RCC_USBREF_CLKSOURCE_20M         (RCC_CCIPR1_USBREFCKSEL_3 | RCC_CCIPR1_USBREFCKSEL_0)
#define LL_RCC_USBREF_CLKSOURCE_24M         (RCC_CCIPR1_USBREFCKSEL_3 | RCC_CCIPR1_USBREFCKSEL_1)
#define LL_RCC_USBREF_CLKSOURCE_26M         (RCC_CCIPR1_USBREFCKSEL_3 |\
                                             RCC_CCIPR1_USBREFCKSEL_2 | RCC_CCIPR1_USBREFCKSEL_1)
#define LL_RCC_USBREF_CLKSOURCE_32M         (RCC_CCIPR1_USBREFCKSEL_3 |\
                                             RCC_CCIPR1_USBREFCKSEL_1 | RCC_CCIPR1_USBREFCKSEL_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_XSPI_CLKSOURCE  Peripheral XSPI clock source selection
  * @{
  */
#define LL_RCC_XSPI1_CLKSOURCE_HCLK         LL_CLKSOURCE(CCIPR1_OFFSET, RCC_CCIPR1_XSPI1SEL, RCC_CCIPR1_XSPI1SEL_Pos, 0U)
#define LL_RCC_XSPI1_CLKSOURCE_PLL2S        LL_CLKSOURCE(CCIPR1_OFFSET, RCC_CCIPR1_XSPI1SEL, RCC_CCIPR1_XSPI1SEL_Pos, RCC_CCIPR1_XSPI1SEL_0)
#define LL_RCC_XSPI1_CLKSOURCE_PLL2T        LL_CLKSOURCE(CCIPR1_OFFSET, RCC_CCIPR1_XSPI1SEL, RCC_CCIPR1_XSPI1SEL_Pos, RCC_CCIPR1_XSPI1SEL_1)
#define LL_RCC_XSPI1_CLKSOURCE_HCLK_DIV4    LL_RCC_SWP_XSPI1_HCLK_DIV4 /* Recovery: Read-only */

#define LL_RCC_XSPI2_CLKSOURCE_HCLK         LL_CLKSOURCE(CCIPR1_OFFSET, RCC_CCIPR1_XSPI2SEL, RCC_CCIPR1_XSPI2SEL_Pos, 0U)
#define LL_RCC_XSPI2_CLKSOURCE_PLL2S        LL_CLKSOURCE(CCIPR1_OFFSET, RCC_CCIPR1_XSPI2SEL, RCC_CCIPR1_XSPI2SEL_Pos, RCC_CCIPR1_XSPI2SEL_0)
#define LL_RCC_XSPI2_CLKSOURCE_PLL2T        LL_CLKSOURCE(CCIPR1_OFFSET, RCC_CCIPR1_XSPI2SEL, RCC_CCIPR1_XSPI2SEL_Pos, RCC_CCIPR1_XSPI2SEL_1)
#define LL_RCC_XSPI2_CLKSOURCE_HCLK_DIV4    LL_RCC_SWP_XSPI2_HCLK_DIV4 /* Recovery: Read-only */
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_ADC_CLKSOURCE
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE                RCC_CCIPR1_ADCSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_ADFx_CLKSOURCE
  * @{
  */
#define LL_RCC_ADF1_CLKSOURCE               RCC_CCIPR1_ADF1SEL
/**
  * @}
  */


/** @addtogroup RCC_LL_EC_CEC_CLKSOURCE
  * @{
  */
#define LL_RCC_CEC_CLKSOURCE                RCC_CCIPR2_CECSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_CLKP_CLKSOURCE
  * @{
  */
#define LL_RCC_CLKP_CLKSOURCE               RCC_CCIPR1_CKPERSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_ETHxPHY_CLKSOURCE
  * @{
  */
#define LL_RCC_ETH1PHY_CLKSOURCE            RCC_CCIPR1_ETH1PHYCKSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_ETHxREF_CLKSOURCE
  * @{
  */
#define LL_RCC_ETH1REF_CLKSOURCE            RCC_CCIPR1_ETH1REFCKSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_FDCAN_CLKSOURCE
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE              RCC_CCIPR2_FDCANSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_FMC_CLKSOURCE
  * @{
  */
#define LL_RCC_FMC_CLKSOURCE                RCC_CCIPR1_FMCSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_I2Cx_CLKSOURCE
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE               LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C1_I3C1SEL, RCC_CCIPR2_I2C1_I3C1SEL_Pos, 0U)
#define LL_RCC_I2C23_CLKSOURCE              LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_I2C23SEL, RCC_CCIPR2_I2C23SEL_Pos, 0U)
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_I3Cx_CLKSOURCE
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE               RCC_CCIPR2_I2C1_I3C1SEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_LPTIMx_CLKSOURCE
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE             LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_LPTIM1SEL, RCC_CCIPR2_LPTIM1SEL_Pos, 0U)
#define LL_RCC_LPTIM23_CLKSOURCE            LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_LPTIM23SEL, RCC_CCIPR4_LPTIM23SEL_Pos, 0U)
#define LL_RCC_LPTIM45_CLKSOURCE            LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_Pos, 0U)
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_LPUARTx_CLKSOURCE
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE            RCC_CCIPR4_LPUART1SEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_OTGFS_CLKSOURCE
  * @{
  */
#define LL_RCC_OTGFS_CLKSOURCE              RCC_CCIPR1_OTGFSSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_PSSI_CLKSOURCE
  * @{
  */
#define LL_RCC_PSSI_CLKSOURCE               RCC_CCIPR1_PSSISEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_SAIx_CLKSOURCE
  * @{
  */
#define LL_RCC_SAI1_CLKSOURCE               LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI1SEL, RCC_CCIPR3_SAI1SEL_Pos, 0U)
#define LL_RCC_SAI2_CLKSOURCE               LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SAI2SEL, RCC_CCIPR3_SAI2SEL_Pos, 0U)
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_SDMMC_CLKSOURCE
  * @{
  */
#define LL_RCC_SDMMC_CLKSOURCE              RCC_CCIPR1_SDMMC12SEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_SPDIFRX_CLKSOURCE
  * @{
  */
#define LL_RCC_SPDIFRX_CLKSOURCE            RCC_CCIPR2_SPDIFRXSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_SPIx_CLKSOURCE
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE               LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_Pos, 0U)
#define LL_RCC_SPI23_CLKSOURCE              LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_Pos, 0U)
#define LL_RCC_SPI45_CLKSOURCE              LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_Pos, 0U)
#define LL_RCC_SPI6_CLKSOURCE               LL_CLKSOURCE(CCIPR4_OFFSET, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_Pos, 0U)
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_USARTx_CLKSOURCE
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE             LL_CLKSOURCE(CCIPR3_OFFSET, RCC_CCIPR3_USART1SEL, RCC_CCIPR3_USART1SEL_Pos, 0U)
#define LL_RCC_USART234578_CLKSOURCE        LL_CLKSOURCE(CCIPR2_OFFSET, RCC_CCIPR2_UART234578SEL, RCC_CCIPR2_UART234578SEL_Pos, 0U)
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_USBPHYC_CLKSOURCE
  * @{
  */
#define LL_RCC_USBPHYC_CLKSOURCE            RCC_CCIPR1_USBPHYCSEL
/**
  * @}
  */

/** @addtogroup RCC_LL_EC_USBREF_CLKSOURCE
  * @{
  */
#define LL_RCC_USBREF_CLKSOURCE             RCC_CCIPR1_USBREFCKSEL
/**
  * @}
  */


/** @addtogroup RCC_LL_EC_XSPIx_CLKSOURCE
  * @{
  */
#define LL_RCC_XSPI1_CLKSOURCE              LL_CLKSOURCE(CCIPR1_OFFSET, RCC_CCIPR1_XSPI1SEL, RCC_CCIPR1_XSPI1SEL_Pos, 0U)
#define LL_RCC_XSPI2_CLKSOURCE              LL_CLKSOURCE(CCIPR1_OFFSET, RCC_CCIPR1_XSPI2SEL, RCC_CCIPR1_XSPI2SEL_Pos, 0U)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE          0U
#define LL_RCC_RTC_CLKSOURCE_LSE           RCC_BDCR_RTCSEL_0
#define LL_RCC_RTC_CLKSOURCE_LSI           RCC_BDCR_RTCSEL_1
#define LL_RCC_RTC_CLKSOURCE_HSE           (RCC_BDCR_RTCSEL_0 | RCC_BDCR_RTCSEL_1)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_TIM_CLKPRESCALER  Timers clocks prescalers selection
  * @{
  */
#define LL_RCC_TIM_PRESCALER_DISABLE         0U
#define LL_RCC_TIM_PRESCALER_ENABLE          RCC_CFGR_TIMPRE
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLSOURCE   All PLLs entry clock source
  * @{
  */
#define LL_RCC_PLLSOURCE_HSI               0U
#define LL_RCC_PLLSOURCE_CSI               RCC_PLLCKSELR_PLLSRC_0
#define LL_RCC_PLLSOURCE_HSE               RCC_PLLCKSELR_PLLSRC_1
#define LL_RCC_PLLSOURCE_NONE              (RCC_PLLCKSELR_PLLSRC_1 | RCC_PLLCKSELR_PLLSRC_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLINPUTRANGE   All PLLs input range
  * @{
  */
#define LL_RCC_PLLINPUTRANGE_1_2           0U
#define LL_RCC_PLLINPUTRANGE_2_4           RCC_PLLCFGR_PLL1RGE_0
#define LL_RCC_PLLINPUTRANGE_4_8           RCC_PLLCFGR_PLL1RGE_1
#define LL_RCC_PLLINPUTRANGE_8_16          (RCC_PLLCFGR_PLL1RGE_1 | RCC_PLLCFGR_PLL1RGE_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLVCORANGE   All PLLs VCO range
  * @{
  */
#define LL_RCC_PLLVCORANGE_WIDE            0U                     /*!< VCO output range: 400 to 1600 MHz */
#define LL_RCC_PLLVCORANGE_MEDIUM          RCC_PLLCFGR_PLL1VCOSEL /*!< VCO output range: 150 to 420 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL_SPREAD_SEL  PLL Spread Spectrum Selection
  * @{
  */
#define LL_RCC_PLL_SPREAD_CENTER           0U                      /*!< PLL center spread spectrum selection */
#define LL_RCC_PLL_SPREAD_DOWN             RCC_PLL1SSCGR_SPREADSEL /*!< PLL down spread spectrum selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL_DITHERING_TPDFN  PLL Dithering TPDF Noise Control
  * @{
  */
#define LL_RCC_PLL_DITHERING_TPDFN_ENABLE  0U                      /*!< PLL Dithering TPDF Noise injection enabled */
#define LL_RCC_PLL_DITHERING_TPDFN_DISABLE RCC_PLL1SSCGR_TPDFNDIS  /*!< PLL Dithering TPDF Noise injection disabled */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL_DITHERING_RPDFN  PLL Dithering RPDF Noise Control
  * @{
  */
#define LL_RCC_PLL_DITHERING_RPDFN_ENABLE  0U                      /*!< PLL Dithering RPDF Noise injection enabled */
#define LL_RCC_PLL_DITHERING_RPDFN_DISABLE RCC_PLL1SSCGR_RPDFNDIS  /*!< PLL Dithering RPDF Noise injection disabled */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
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
  * @brief  Helper macro to calculate the SYSCLK frequency
  * @param  __SYSINPUTCLKFREQ__ Frequency of the input of sys_ck (based on HSE/CSI/HSI/PLL1P)
  * @param  __SYSPRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval SYSCLK clock frequency (in Hz)
  */
#define LL_RCC_CALC_SYSCLK_FREQ(__SYSINPUTCLKFREQ__, __SYSPRESCALER__) ((__SYSINPUTCLKFREQ__) >> ((LL_RCC_PrescTable[((__SYSPRESCALER__) &\
                                                                        RCC_CDCFGR_CPRE) >> RCC_CDCFGR_CPRE_Pos]) & 0x1FU))

/**
  * @brief  Helper macro to calculate the HCLK frequency
  * @param  __SYSCLKFREQ__ SYSCLK frequency.
  * @param  __HPRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_AHB_DIV_1
  *         @arg @ref LL_RCC_AHB_DIV_2
  *         @arg @ref LL_RCC_AHB_DIV_4
  *         @arg @ref LL_RCC_AHB_DIV_8
  *         @arg @ref LL_RCC_AHB_DIV_16
  *         @arg @ref LL_RCC_AHB_DIV_64
  *         @arg @ref LL_RCC_AHB_DIV_128
  *         @arg @ref LL_RCC_AHB_DIV_256
  *         @arg @ref LL_RCC_AHB_DIV_512
  * @retval HCLK clock frequency (in Hz)
  */
#define LL_RCC_CALC_HCLK_FREQ(__SYSCLKFREQ__, __HPRESCALER__) ((__SYSCLKFREQ__) >> ((LL_RCC_PrescTable[((__HPRESCALER__) &\
                                                               RCC_BMCFGR_BMPRE) >>  RCC_BMCFGR_BMPRE_Pos]) & 0x1FU))

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
#define LL_RCC_CALC_PCLK1_FREQ(__HCLKFREQ__, __APB1PRESCALER__) ((__HCLKFREQ__) >> ((LL_RCC_PrescTable[((__APB1PRESCALER__) &\
                                                                 RCC_APBCFGR_PPRE1) >>  RCC_APBCFGR_PPRE1_Pos]) & 0x1FU))

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
#define LL_RCC_CALC_PCLK2_FREQ(__HCLKFREQ__, __APB2PRESCALER__) ((__HCLKFREQ__) >> ((LL_RCC_PrescTable[((__APB2PRESCALER__) &\
                                                                 RCC_APBCFGR_PPRE2) >> RCC_APBCFGR_PPRE2_Pos]) & 0x1FU))

/**
  * @brief  Helper macro to calculate the PCLK4 frequency (ABP4)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB4PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB4_DIV_1
  *         @arg @ref LL_RCC_APB4_DIV_2
  *         @arg @ref LL_RCC_APB4_DIV_4
  *         @arg @ref LL_RCC_APB4_DIV_8
  *         @arg @ref LL_RCC_APB4_DIV_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK4_FREQ(__HCLKFREQ__, __APB4PRESCALER__) ((__HCLKFREQ__) >> ((LL_RCC_PrescTable[((__APB4PRESCALER__) &\
                                                                 RCC_APBCFGR_PPRE4) >>  RCC_APBCFGR_PPRE4_Pos]) & 0x1FU))

/**
  * @brief  Helper macro to calculate the PCLK5 frequency (APB5)
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB5PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB5_DIV_1
  *         @arg @ref LL_RCC_APB5_DIV_2
  *         @arg @ref LL_RCC_APB5_DIV_4
  *         @arg @ref LL_RCC_APB5_DIV_8
  *         @arg @ref LL_RCC_APB5_DIV_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK5_FREQ(__HCLKFREQ__, __APB5PRESCALER__) ((__HCLKFREQ__) >> ((LL_RCC_PrescTable[((__APB5PRESCALER__) &\
                                                                 RCC_APBCFGR_PPRE5) >> RCC_APBCFGR_PPRE5_Pos]) & 0x1FU))

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EC_PERIPH_FREQUENCY Peripheral clock frequency
  * @{
  */
#define LL_RCC_PERIPH_FREQUENCY_NO         0U                 /*!< No clock enabled for the peripheral            */
#define LL_RCC_PERIPH_FREQUENCY_NA         0xFFFFFFFFU        /*!< Frequency cannot be provided as external clock */
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

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
  * @brief  Enable the Clock Security System.
  * @note Once HSE Clock Security System is enabled it cannot be changed anymore unless
  *       a reset occurs or system enter in standby mode.
  * @rmtoll CR           HSECSSON         LL_RCC_HSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSECSSON);
}

/**
  * @brief  Enable HSE external oscillator (HSE Bypass)
  * @rmtoll CR           HSEBYP        LL_RCC_HSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableBypass(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Disable HSE external oscillator (HSE Bypass)
  * @rmtoll CR           HSEBYP        LL_RCC_HSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Select the Analog HSE external clock type in Bypass mode
  * @rmtoll CR           HSEEXT        LL_RCC_HSE_SelectAnalogClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_SelectAnalogClock(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEEXT);
}

/**
  * @brief  Select the Digital HSE external clock type in Bypass mode
  * @rmtoll CR           HSEEXT        LL_RCC_HSE_SelectDigitalClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_SelectDigitalClock(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEEXT);
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
  return ((READ_BIT(RCC->CR, RCC_CR_HSERDY) == RCC_CR_HSERDY) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI HSI
  * @{
  */

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
  return ((READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RCC_CR_HSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI new divider applied and ready
  * @rmtoll CR           HSIDIVF        LL_RCC_HSI_IsDividerReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsDividerReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIDIVF) == RCC_CR_HSIDIVF) ? 1UL : 0UL);
}

/**
  * @brief  Set HSI divider
  * @rmtoll CR           HSIDIV        LL_RCC_HSI_SetDivider
  * @param  Divider This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  * @retval None.
  */
__STATIC_INLINE void LL_RCC_HSI_SetDivider(uint32_t Divider)
{
  MODIFY_REG(RCC->CR, RCC_CR_HSIDIV, Divider);
}

/**
  * @brief  Get HSI divider
  * @rmtoll CR           HSIDIV        LL_RCC_HSI_GetDivider
  * @retval can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetDivider(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_HSIDIV));
}

/**
  * @brief  Enable HSI oscillator in Stop mode
  * @rmtoll CR           HSIKERON        LL_RCC_HSI_EnableStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_EnableStopMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Disable HSI oscillator in Stop mode
  * @rmtoll CR           HSIKERON        LL_RCC_HSI_DisableStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_DisableStopMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Check if HSI oscillator in Stop mode has been enabled or not
  * @rmtoll CR           HSIKERON         LL_RCC_HSI_IsEnabledStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledStopMode(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIKERON) == (RCC_CR_HSIKERON)) ? 1UL : 0UL);
}

/**
  * @brief  Enable XSPI clock protection
  * @rmtoll CKPROTR           XSPICKP        LL_RCC_EnableXSPIClockProtection
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableXSPIClockProtection(void)
{
  SET_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPICKP);
}

/**
  * @brief  Disable XSPI clock protection
  * @rmtoll CKPROTR           XSPICKP        LL_RCC_DisableXSPIClockProtection
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableXSPIClockProtection(void)
{
  CLEAR_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPICKP);
}

/**
  * @brief  Check if XSPI clock protection has been enabled or not
  * @rmtoll CKPROTR           XSPICKP         LL_RCC_IsEnabledXSPIClockProtection
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledXSPIClockProtection(void)
{
  return ((READ_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPICKP) == (RCC_CKPROTR_XSPICKP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable FMC clock protection
  * @rmtoll CKPROTR           FMCCKP        LL_RCC_EnableFMCClockProtection
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableFMCClockProtection(void)
{
  SET_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCCKP);
}

/**
  * @brief  Disable FMC clock protection
  * @rmtoll CKPROTR           FMCCKP        LL_RCC_DisableFMCClockProtection
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableFMCClockProtection(void)
{
  CLEAR_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCCKP);
}

/**
  * @brief  Check if FMC clock protection has been enabled or not
  * @rmtoll CKPROTR           FMCCKP         LL_RCC_IsEnabledFMCClockProtection
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledFMCClockProtection(void)
{
  return ((READ_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCCKP) == (RCC_CKPROTR_FMCCKP)) ? 1UL : 0UL);
}

/**
  * @brief  Get XSPI2 kernel clock switch position
  * @rmtoll CKPROTR        XSPI2SWP       LL_RCC_GetXSPI2SwitchPosition
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SWP_XSPI2_NEUTRAL
            @arg @ref LL_RCC_SWP_XSPI2_HCLK5
            @arg @ref LL_RCC_SWP_XSPI2_PLL2S
            @arg @ref LL_RCC_SWP_XSPI2_PLL2T
            @arg @ref LL_RCC_SWP_XSPI2_HCLK_DIV4
  */
__STATIC_INLINE uint32_t LL_RCC_GetXSPI2SwitchPosition(void)
{
  return (READ_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPI2SWP));
}

/**
  * @brief  Get XSPI1 kernel clock switch position
  * @rmtoll CKPROTR        XSPI1SWP       LL_RCC_GetXSPI1SwitchPosition
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SWP_XSPI1_NEUTRAL
            @arg @ref LL_RCC_SWP_XSPI1_HCLK5
            @arg @ref LL_RCC_SWP_XSPI1_PLL2S
            @arg @ref LL_RCC_SWP_XSPI1_PLL2T
            @arg @ref LL_RCC_SWP_XSPI1_HCLK_DIV4
  */
__STATIC_INLINE uint32_t LL_RCC_GetXSPI1SwitchPosition(void)
{
  return (READ_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPI1SWP));
}

/**
  * @brief  Get FMC kernel clock switch position
  * @rmtoll CKPROTR        FMCSWP       LL_RCC_GetFMCSwitchPosition
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SWP_FMC_NEUTRAL
            @arg @ref LL_RCC_SWP_FMC_HCLK5
            @arg @ref LL_RCC_SWP_FMC_PLL1Q
            @arg @ref LL_RCC_SWP_FMC_PLL2R
            @arg @ref LL_RCC_SWP_FMC_HSI
            @arg @ref LL_RCC_SWP_FMC_HCLK_DIV4
  */
__STATIC_INLINE uint32_t LL_RCC_GetFMCSwitchPosition(void)
{
  return (READ_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCSWP));
}

/**
  * @brief  Get HSI Calibration value
  * @note When HSITRIM is written, HSICAL is updated with the sum of
  *       HSITRIM and the factory trim value
  * @rmtoll HSICFGR        HSICAL        LL_RCC_HSI_GetCalibration
  * @retval A value between 0 and 4095 (0xFFF)
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->HSICFGR, RCC_HSICFGR_HSICAL) >> RCC_HSICFGR_HSICAL_Pos);
}

/**
  * @brief  Set HSI Calibration trimming
  * @note user-programmable trimming value that is added to the HSICAL
  * @note Default value is 64, which, when added to the HSICAL value,
  *       should trim the HSI to 64 MHz +/- 1 %
  * @rmtoll HSICFGR        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  Value Parameter can be a value between 0 and 127
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->HSICFGR, RCC_HSICFGR_HSITRIM, Value << RCC_HSICFGR_HSITRIM_Pos);
}

/**
  * @brief  Get HSI Calibration trimming
  * @rmtoll HSICFGR        HSITRIM       LL_RCC_HSI_GetCalibTrimming
  * @retval A value between 0 and 127
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->HSICFGR, RCC_HSICFGR_HSITRIM) >> RCC_HSICFGR_HSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_CSI CSI
  * @{
  */

/**
  * @brief  Enable CSI oscillator
  * @rmtoll CR           CSION         LL_RCC_CSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_CSION);
}

/**
  * @brief  Disable CSI oscillator
  * @rmtoll CR           CSION         LL_RCC_CSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_CSION);
}

/**
  * @brief  Check if CSI clock is ready
  * @rmtoll CR           CSIRDY        LL_RCC_CSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_CSIRDY) == RCC_CR_CSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable CSI oscillator in Stop mode
  * @rmtoll CR           CSIKERON         LL_RCC_CSI_EnableStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_EnableStopMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_CSIKERON);
}

/**
  * @brief  Disable CSI oscillator in Stop mode
  * @rmtoll CR           CSIKERON         LL_RCC_CSI_DisableStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_DisableStopMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_CSIKERON);
}

/**
  * @brief  Check if CSI oscillator in Stop mode has been enabled or not
  * @rmtoll CR           CSIKERON         LL_RCC_CSI_IsEnabledStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_IsEnabledStopMode(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_CSIKERON) == (RCC_CR_CSIKERON)) ? 1UL : 0UL);
}

/**
  * @brief  Get CSI Calibration value
  * @note When CSITRIM is written, CSICAL is updated with the sum of
  *       CSITRIM and the factory trim value
  * @rmtoll CSICFGR        CSICAL        LL_RCC_CSI_GetCalibration
  * @retval A value between 0 and 255 (0xFF)
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->CSICFGR, RCC_CSICFGR_CSICAL) >> RCC_CSICFGR_CSICAL_Pos);
}

/**
  * @brief  Set CSI Calibration trimming
  * @note user-programmable trimming value that is added to the CSICAL
  * @note Default value is 16, which, when added to the CSICAL value,
  *       should trim the CSI to 4 MHz +/- 1 %
  * @rmtoll CSICFGR        CSITRIM       LL_RCC_CSI_SetCalibTrimming
  * @param  Value can be a value between 0 and 31
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->CSICFGR, RCC_CSICFGR_CSITRIM, Value << RCC_CSICFGR_CSITRIM_Pos);
}

/**
  * @brief  Get CSI Calibration trimming
  * @rmtoll CSICFGR        CSITRIM       LL_RCC_CSI_GetCalibTrimming
  * @retval A value between 0 and 31
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->CSICFGR, RCC_CSICFGR_CSITRIM) >> RCC_CSICFGR_CSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI48 HSI48
  * @{
  */

/**
  * @brief  Enable HSI48 oscillator
  * @rmtoll CR           HSI48ON         LL_RCC_HSI48_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSI48ON);
}

/**
  * @brief  Disable HSI48 oscillator
  * @rmtoll CR           HSI48ON         LL_RCC_HSI48_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI48_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSI48ON);
}

/**
  * @brief  Check if HSI48 clock is ready
  * @rmtoll CR           HSI48RDY        LL_RCC_HSI48_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSI48RDY) == RCC_CR_HSI48RDY) ? 1UL : 0UL);
}

/**
  * @brief  Get HSI48 Calibration value
  * @note When HSI48TRIM is written, HSI48CAL is updated with the sum of
  *       HSI48TRIM and the factory trim value
  * @rmtoll CRRCR        HSI48CAL        LL_RCC_HSI48_GetCalibration
  * @retval A value between 0 and 1023 (0x3FF)
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->CRRCR, RCC_CRRCR_HSI48CAL) >> RCC_CRRCR_HSI48CAL_Pos);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable the Clock Security System on LSE.
  * @note Once LSE Clock Security System is enabled it cannot be changed anymore unless
  *       a clock failure is detected.
  * @rmtoll BDCR          LSECSSON         LL_RCC_LSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Disable the Clock Security System on LSE.
  * @note Once LSE Clock Security System is enabled it cannot be changed anymore unless
  *       a clock failure is detected.
  * @rmtoll BDCR          LSECSSON         LL_RCC_LSE_DisableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Check if LSE failure is detected by Clock Security System
  * @rmtoll BDCR         LSECSSD       LL_RCC_LSE_IsFailureDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsFailureDetected(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSD) == RCC_BDCR_LSECSSD) ? 1UL : 0UL);
}

/**
  * @brief  Re-arm the Clock Security System on LSE.
  * @note Once a clock failure is detected, the LSE Clock Security System can be re-armed providing that
  *       LSECSSON is disabled.
  * @rmtoll BDCR          LSECSSRA         LL_RCC_LSE_ReArmCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_ReArmCSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSRA);
}

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
  * @brief  Enable Low-speed external DIGITAL clock type in Bypass mode (not to be used if RTC is active).
  * @note   The external clock must be enabled with the LSEON bit, to be used by the device.
  *         The LSEEXT bit can be written only if the LSE oscillator is disabled.
  * @rmtoll BDCR         LSEEXT        LL_RCC_LSE_SelectDigitalClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SelectDigitalClock(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEEXT);
}

/**
  * @brief  Enable Low-speed external ANALOG clock type in Bypass mode (default after Backup domain reset).
  * @note   The external clock must be enabled with the LSEON bit, to be used by the device.
  *         The LSEEXT bit can be written only if the LSE oscillator is disabled.
  * @rmtoll BDCR         LSEEXT        LL_RCC_LSE_SelectAnalogClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SelectAnalogClock(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEEXT);
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
  * @brief  Check if LSE oscillator Ready
  * @rmtoll BDCR         LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == RCC_BDCR_LSERDY) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

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
  return ((READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == RCC_CSR_LSIRDY) ? 1UL : 0UL);
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
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_PLL1
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
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_CSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_PLL1
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}

/**
  * @brief  Configure the system wakeup clock source
  * @rmtoll CFGR         STOPWUCK       LL_RCC_SetSysWakeUpClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSWAKEUP_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYSWAKEUP_CLKSOURCE_CSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSysWakeUpClkSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPWUCK, Source);
}

/**
  * @brief  Get the system wakeup clock source
  * @rmtoll CFGR         STOPWUCK           LL_RCC_GetSysWakeUpClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSWAKEUP_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYSWAKEUP_CLKSOURCE_CSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysWakeUpClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_STOPWUCK));
}

/**
  * @brief  Configure the kernel wakeup clock source
  * @rmtoll CFGR         STOPKERWUCK       LL_RCC_SetKerWakeUpClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_KERWAKEUP_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_KERWAKEUP_CLKSOURCE_CSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetKerWakeUpClkSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPKERWUCK, Source);
}

/**
  * @brief  Get the kernel wakeup clock source
  * @rmtoll CFGR         STOPKERWUCK           LL_RCC_GetKerWakeUpClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_KERWAKEUP_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_KERWAKEUP_CLKSOURCE_CSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetKerWakeUpClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_STOPKERWUCK));
}

/**
  * @brief  Set System prescaler
  * @rmtoll CDCFGR        CPRE          LL_RCC_SetSysPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSysPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CDCFGR, RCC_CDCFGR_CPRE, Prescaler);
}

/**
  * @brief  Set AHB prescaler
  * @rmtoll BMCFGR        BMPRE         LL_RCC_SetAHBPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_AHB_DIV_1
  *         @arg @ref LL_RCC_AHB_DIV_2
  *         @arg @ref LL_RCC_AHB_DIV_4
  *         @arg @ref LL_RCC_AHB_DIV_8
  *         @arg @ref LL_RCC_AHB_DIV_16
  *         @arg @ref LL_RCC_AHB_DIV_64
  *         @arg @ref LL_RCC_AHB_DIV_128
  *         @arg @ref LL_RCC_AHB_DIV_256
  *         @arg @ref LL_RCC_AHB_DIV_512
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->BMCFGR, RCC_BMCFGR_BMPRE, Prescaler);
}

/**
  * @brief  Set APB1 prescaler
  * @rmtoll APBCFGR         PPRE1         LL_RCC_SetAPB1Prescaler
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
  MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE1, Prescaler);
}

/**
  * @brief  Set APB2 prescaler
  * @rmtoll APBCFGR         PPRE2         LL_RCC_SetAPB2Prescaler
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
  MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE2, Prescaler);
}

/**
  * @brief  Set APB4 prescaler
  * @rmtoll APBCFGR         PPRE4         LL_RCC_SetAPB4Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB4_DIV_1
  *         @arg @ref LL_RCC_APB4_DIV_2
  *         @arg @ref LL_RCC_APB4_DIV_4
  *         @arg @ref LL_RCC_APB4_DIV_8
  *         @arg @ref LL_RCC_APB4_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB4Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE4, Prescaler);
}

/**
  * @brief  Set APB5 prescaler
  * @rmtoll APBCFGR         PPRE5         LL_RCC_SetAPB5Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB5_DIV_1
  *         @arg @ref LL_RCC_APB5_DIV_2
  *         @arg @ref LL_RCC_APB5_DIV_4
  *         @arg @ref LL_RCC_APB5_DIV_8
  *         @arg @ref LL_RCC_APB5_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB5Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE5, Prescaler);
}

/**
  * @brief  Get System prescaler
  * @rmtoll CDCFGR        CPRE          LL_RCC_GetSysPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_DIV_1
  *         @arg @ref LL_RCC_SYSCLK_DIV_2
  *         @arg @ref LL_RCC_SYSCLK_DIV_4
  *         @arg @ref LL_RCC_SYSCLK_DIV_8
  *         @arg @ref LL_RCC_SYSCLK_DIV_16
  *         @arg @ref LL_RCC_SYSCLK_DIV_64
  *         @arg @ref LL_RCC_SYSCLK_DIV_128
  *         @arg @ref LL_RCC_SYSCLK_DIV_256
  *         @arg @ref LL_RCC_SYSCLK_DIV_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CDCFGR, RCC_CDCFGR_CPRE));
}

/**
  * @brief  Get AHB prescaler
  * @rmtoll BMCFGR       BMPRE         LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_AHB_DIV_1
  *         @arg @ref LL_RCC_AHB_DIV_2
  *         @arg @ref LL_RCC_AHB_DIV_4
  *         @arg @ref LL_RCC_AHB_DIV_8
  *         @arg @ref LL_RCC_AHB_DIV_16
  *         @arg @ref LL_RCC_AHB_DIV_64
  *         @arg @ref LL_RCC_AHB_DIV_128
  *         @arg @ref LL_RCC_AHB_DIV_256
  *         @arg @ref LL_RCC_AHB_DIV_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->BMCFGR, RCC_BMCFGR_BMPRE));
}

/**
  * @brief  Get APB1 prescaler
  * @rmtoll APBCFGR         PPRE1         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE1));
}

/**
  * @brief  Get APB2 prescaler
  * @rmtoll APBCFGR         PPRE2         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE2));
}

/**
  * @brief  Get APB4 prescaler
  * @rmtoll APBCFGR         PPRE4         LL_RCC_GetAPB4Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB4_DIV_1
  *         @arg @ref LL_RCC_APB4_DIV_2
  *         @arg @ref LL_RCC_APB4_DIV_4
  *         @arg @ref LL_RCC_APB4_DIV_8
  *         @arg @ref LL_RCC_APB4_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB4Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE4));
}

/**
  * @brief  Get APB5 prescaler
  * @rmtoll APBCFGR         PPRE5         LL_RCC_GetAPB5Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB5_DIV_1
  *         @arg @ref LL_RCC_APB5_DIV_2
  *         @arg @ref LL_RCC_APB5_DIV_4
  *         @arg @ref LL_RCC_APB5_DIV_8
  *         @arg @ref LL_RCC_APB5_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB5Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE5));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MCO MCO
  * @{
  */

/**
  * @brief  Configure MCOx
  * @rmtoll CFGR         MCO1SEL       LL_RCC_ConfigMCO\n
  *         CFGR         MCO1PRE       LL_RCC_ConfigMCO\n
  *         CFGR         MCO2SEL          LL_RCC_ConfigMCO\n
  *         CFGR         MCO2PRE       LL_RCC_ConfigMCO
  * @param  MCOxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_PLL1Q
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI48
  *         @arg @ref LL_RCC_MCO2SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_PLL2P
  *         @arg @ref LL_RCC_MCO2SOURCE_HSE
  *         @arg @ref LL_RCC_MCO2SOURCE_PLL1P
  *         @arg @ref LL_RCC_MCO2SOURCE_CSI
  *         @arg @ref LL_RCC_MCO2SOURCE_LSI
  * @param  MCOxPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1_DIV_1
  *         @arg @ref LL_RCC_MCO1_DIV_2
  *         @arg @ref LL_RCC_MCO1_DIV_3
  *         @arg @ref LL_RCC_MCO1_DIV_4
  *         @arg @ref LL_RCC_MCO1_DIV_5
  *         @arg @ref LL_RCC_MCO1_DIV_6
  *         @arg @ref LL_RCC_MCO1_DIV_7
  *         @arg @ref LL_RCC_MCO1_DIV_8
  *         @arg @ref LL_RCC_MCO1_DIV_9
  *         @arg @ref LL_RCC_MCO1_DIV_10
  *         @arg @ref LL_RCC_MCO1_DIV_11
  *         @arg @ref LL_RCC_MCO1_DIV_12
  *         @arg @ref LL_RCC_MCO1_DIV_13
  *         @arg @ref LL_RCC_MCO1_DIV_14
  *         @arg @ref LL_RCC_MCO1_DIV_15
  *         @arg @ref LL_RCC_MCO2_DIV_1
  *         @arg @ref LL_RCC_MCO2_DIV_2
  *         @arg @ref LL_RCC_MCO2_DIV_3
  *         @arg @ref LL_RCC_MCO2_DIV_4
  *         @arg @ref LL_RCC_MCO2_DIV_5
  *         @arg @ref LL_RCC_MCO2_DIV_6
  *         @arg @ref LL_RCC_MCO2_DIV_7
  *         @arg @ref LL_RCC_MCO2_DIV_8
  *         @arg @ref LL_RCC_MCO2_DIV_9
  *         @arg @ref LL_RCC_MCO2_DIV_10
  *         @arg @ref LL_RCC_MCO2_DIV_11
  *         @arg @ref LL_RCC_MCO2_DIV_12
  *         @arg @ref LL_RCC_MCO2_DIV_13
  *         @arg @ref LL_RCC_MCO2_DIV_14
  *         @arg @ref LL_RCC_MCO2_DIV_15
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t MCOxSource, uint32_t MCOxPrescaler)
{
  MODIFY_REG(RCC->CFGR, (MCOxSource << 16U) | (MCOxPrescaler << 16U), (MCOxSource & 0xFFFF0000U) | (MCOxPrescaler & 0xFFFF0000U));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Configure periph clock source
  * @rmtoll CCIPR1         *     LL_RCC_SetClockSource\n
  *         CCIPR2        *     LL_RCC_SetClockSource\n
  *         CCIPR3        *     LL_RCC_SetClockSource\n
  *         CCIPR4       *     LL_RCC_SetClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_SPDIFRX
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2T
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_PLL2T
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetClockSource(uint32_t ClkSource)
{
  volatile uint32_t *pReg = (uint32_t *)((uint32_t)&RCC->CCIPR1 + LL_CLKSOURCE_REG(ClkSource));
  MODIFY_REG(*pReg, LL_CLKSOURCE_MASK(ClkSource), LL_CLKSOURCE_CONFIG(ClkSource));
}

/**
  * @brief  Configure ADCx Kernel clock source
  * @rmtoll CCIPR1        ADCSEL        LL_RCC_SetADCClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_CLKP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADCClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ADCSEL, ClkSource);
}

/**
  * @brief  Configure ADFx Kernel clock source
  * @rmtoll CCIPR1         ADF1SEL        LL_RCC_SetADFClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADFClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ADF1SEL, ClkSource);
}

/**
  * @brief  Configure CECx clock source
  * @rmtoll CCIPR2         CECSEL        LL_RCC_SetCECClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CEC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_CEC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_CEC_CLKSOURCE_CSI_DIV_122
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCECClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_CECSEL, ClkSource);
}

/**
  * @brief  Configure CLKP Kernel clock source
  * @rmtoll CCIPR1         CKPERSEL        LL_RCC_SetCLKPClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE_HSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCLKPClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_CKPERSEL, ClkSource);
}

/**
  * @brief  Configure ETHx PHY clock source
  * @rmtoll CCIPR1      ETH1PHYCKSEL   LL_RCC_SetETHPHYClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH1PHY_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ETH1PHY_CLKSOURCE_PLL3S
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETHPHYClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ETH1PHYCKSEL, ClkSource);
}

/**
  * @brief  Configure ETHx REF clock source
  * @rmtoll CCIPR1      ETH1REFCKSEL   LL_RCC_SetETHREFClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH1REF_CLKSOURCE_RMII
  *         @arg @ref LL_RCC_ETH1REF_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ETH1REF_CLKSOURCE_FB
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETHREFClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ETH1REFCKSEL, ClkSource);
}

/**
  * @brief  Configure FDCANx Kernel clock source
  * @rmtoll CCIPR2       FDCANSEL        LL_RCC_SetFDCANClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL2Q
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFDCANClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_FDCANSEL, ClkSource);
}

/**
  * @brief  Configure FMCx Kernel clock source
  * @rmtoll CCIPR1       FMCSEL         LL_RCC_SetFMCClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_PLL2R
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFMCClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_FMCSEL, ClkSource);
}

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll CCIPR2       I2C1_I3C1SEL   LL_RCC_SetI2CClockSource
  * @rmtoll CCIPR2       I2C23SEL       LL_RCC_SetI2CClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_CSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}

/**
  * @brief  Configure I3Cx clock source
  * @rmtoll CCIPR2       I2C1_I3C1SEL   LL_RCC_SetI3CClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_CSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3CClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2C1_I3C1SEL, ClkSource);
}

/**
  * @brief  Configure LPTIMx clock source
  * @rmtoll CCIPR2       LPTIM1SEL     LL_RCC_SetLPTIMClockSource\n
  *         CCIPR4       LPTIM23SEL    LL_RCC_SetLPTIMClockSource\n
  *         CCIPR4       LPTIM45SEL    LL_RCC_SetLPTIMClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_CLKP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}

/**
  * @brief  Configure LPUARTx clock source
  * @rmtoll CCIPR4       LPUART1SEL     LL_RCC_SetLPUARTClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_LPUART1SEL, ClkSource);
}

/**
  * @brief  Configure OTGFSx clock source
  * @rmtoll CCIPR1       OTGFSSEL      LL_RCC_SetOTGFSClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE_CLK48
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE_PLL3Q
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetOTGFSClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_OTGFSSEL, ClkSource);
}

/**
  * @brief  Configure XSPIx Kernel clock source
  * @rmtoll CCIPR1       XSPI1SEL        LL_RCC_SetXSPIClockSource\n
  *         CCIPR1       XSPI2SEL        LL_RCC_SetXSPIClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2T
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_PLL2T
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetXSPIClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}

/**
  * @brief  Configure PSSI clock source
  * @rmtoll CCIPR1       PSSISEL        LL_RCC_SetPSSIClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSSI_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_PSSI_CLKSOURCE_CLKP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetPSSIClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_PSSISEL, ClkSource);
}

/**
  * @brief  Configure SAIx clock source
  * @rmtoll CCIPR3       SAI1SEL      LL_RCC_SetSAIClockSource\n
  *         CCIPR3       SAI2SEL      LL_RCC_SetSAIClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_SPDIFRX
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAIClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}

/**
  * @brief  Configure SDMMCx clock source
  * @rmtoll CCIPR1       SDMMCSEL      LL_RCC_SetSDMMCClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_SDMMC_CLKSOURCE_PLL2T
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMCClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SDMMC12SEL, ClkSource);
}

/**
  * @brief  Configure SPDIFRX Kernel clock source
  * @rmtoll CCIPR2       SPDIFRXSEL        LL_RCC_SetSPDIFRXClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE_PLL2R
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPDIFRXClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SPDIFRXSEL, ClkSource);
}

/**
  * @brief  Configure SPIx Kernel clock source
  * @rmtoll CCIPR3       SPI1SEL        LL_RCC_SetSPIClockSource\n
  *         CCIPR2       SPI23SEL       LL_RCC_SetSPIClockSource\n
  *         CCIPR3       SPI45SEL       LL_RCC_SetSPIClockSource\n
  *         CCIPR4      SPI6SEL        LL_RCC_SetSPIClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPIClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}

/**
  * @brief  Configure USARTx clock source
  * @rmtoll CCIPR3       USART1SEL     LL_RCC_SetUSARTClockSource\n
  *         CCIPR2       UART234578SEL LL_RCC_SetUSARTClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}

/**
  * @brief  Configure USBPHYC clock source
  * @rmtoll CCIPR1       USBPHYCSEL    LL_RCC_SetUSBPHYCClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE_DISABLE
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE_HSE_DIV_2
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE_PLL3Q
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSBPHYCClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USBPHYCSEL, ClkSource);
}

/**
  * @brief  Configure USBREF clock source
  * @rmtoll CCIPR1       USBREFCKSEL   LL_RCC_SetUSBREFClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_16M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_19_2M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_20M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_24M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_26M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_32M
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSBREFClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_USBREFCKSEL, ClkSource);
}

/**
  * @brief  Get periph clock source
  * @rmtoll CCIPR1     *     LL_RCC_GetClockSource\n
  *         CCIPR2     *     LL_RCC_GetClockSource\n
  *         CCIPR3     *     LL_RCC_GetClockSource\n
  *         CCIPR4     *     LL_RCC_GetClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_SPDIFRX
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2T
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_PLL2T
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_GetClockSource(uint32_t Periph)
{
  const volatile uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&RCC->CCIPR1) + LL_CLKSOURCE_REG(Periph)));
  return (uint32_t)(Periph | (((READ_BIT(*pReg, LL_CLKSOURCE_MASK(Periph))) >> LL_CLKSOURCE_SHIFT(Periph)) << LL_RCC_CONFIG_SHIFT));
}

/**
  * @brief  Get ADC Kernel clock source
  * @rmtoll CCIPR1       ADCSEL        LL_RCC_GetADCClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_CLKP
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ADCSEL));
}

/**
  * @brief  Get ADF clock source
  * @rmtoll CCIPR1          ADF1SEL        LL_RCC_GetADFClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetADFClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ADF1SEL));
}

/**
  * @brief  Get CEC clock source
  * @rmtoll CCIPR2        CECSEL        LL_RCC_GetCECClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CEC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_CEC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_CEC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_CEC_CLKSOURCE_CSI_DIV_122
  */
__STATIC_INLINE uint32_t LL_RCC_GetCECClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_CECSEL));
}

/**
  * @brief  Get CLKP Kernel clock source
  * @rmtoll CCIPR1       CKPERSEL        LL_RCC_GetCLKPClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetCLKPClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_CKPERSEL));
}

/**
  * @brief  Get ETH PHY clock source
  * @rmtoll CCIPR1       ETH1PHYCKSEL  LL_RCC_GetETHPHYClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH1PHY_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ETH1PHY_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ETH1PHY_CLKSOURCE_PLL3S
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHPHYClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ETH1PHYCKSEL));
}

/**
  * @brief  Get ETH REF clock source
  * @rmtoll CCIPR1       ETH1REFCKSEL  LL_RCC_GetETHREFClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH1REF_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ETH1REF_CLKSOURCE_RMII
  *         @arg @ref LL_RCC_ETH1REF_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ETH1REF_CLKSOURCE_FB
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHREFClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ETH1REFCKSEL));
}

/**
  * @brief  Get FDCAN Kernel clock source
  * @rmtoll CCIPR2       FDCANSEL        LL_RCC_GetFDCANClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL2Q
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCANClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_FDCANSEL));
}

/**
  * @brief  Get FMC Kernel clock source
  * @rmtoll CCIPR1       FMCSEL        LL_RCC_GetFMCClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_PLL2R
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetFMCClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_FMCSEL));
}

/**
  * @brief  Get I2Cx clock source
  * @rmtoll CCIPR2       I2C1_I3C1SEL   LL_RCC_GetI2CClockSource
  * @rmtoll CCIPR2       I2C23SEL       LL_RCC_GetI2CClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE_CSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get I3Cx clock source
  * @rmtoll CCIPR2       I2C1_I3C1SEL    LL_RCC_GetI3CClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_CSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3CClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2C1_I3C1SEL));
}

/**
  * @brief  Get LPTIM clock source
  * @rmtoll CCIPR2       LPTIM1SEL     LL_RCC_GetLPTIMClockSource\n
  *         CCIPR4       LPTIM23SEL    LL_RCC_GetLPTIMClockSource\n
  *         CCIPR4       LPTIM45SEL    LL_RCC_GetLPTIMClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_CLKP
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get LPUART clock source
  * @rmtoll CCIPR4       LPUART1SEL     LL_RCC_GetLPUARTClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR4, RCC_CCIPR4_LPUART1SEL));
}

/**
  * @brief  Get OTGFS clock source
  * @rmtoll CCIPR1       OTGFSSEL      LL_RCC_GetOTGFSClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_OTGFS_CLKSOURCE_CLK48
  */
__STATIC_INLINE uint32_t LL_RCC_GetOTGFSClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_OTGFSSEL));
}

/**
  * @brief  Get XSPI Kernel clock source
  * @rmtoll CCIPR1      XSPI1SEL        LL_RCC_GetXSPIClockSource\n
  *         CCIPR1      XSPI2SEL        LL_RCC_GetXSPIClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2T
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE_PLL2T
  */
__STATIC_INLINE uint32_t LL_RCC_GetXSPIClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get PSSI clock source
  * @rmtoll CCIPR1      PSSISEL      LL_RCC_GetPSSIClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSSI_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PSSI_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_PSSI_CLKSOURCE_CLKP
  */
__STATIC_INLINE uint32_t LL_RCC_GetPSSIClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_PSSISEL));
}

/**
  * @brief  Get SAIx clock source
  * @rmtoll CCIPR3     SAI1SEL      LL_RCC_GetSAIClockSource\n
  *         CCIPR3     SAI2SEL      LL_RCC_GetSAIClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_SPDIFRX
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAIClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get SDMMC clock source
  * @rmtoll CCIPR1      SDMMCSEL      LL_RCC_GetSDMMCClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_SDMMC_CLKSOURCE_PLL2T
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMCClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SDMMC12SEL));
}

/**
  * @brief  Get SPDIFRX Kernel clock source
  * @rmtoll CCIPR2      SPDIFRXSEL        LL_RCC_GetSPDIFRXClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE_PLL2R
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPDIFRXClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SPDIFRXSEL));
}

/**
  * @brief  Get SPIx Kernel clock source
  * @rmtoll CCIPR3     SPI1SEL         LL_RCC_GetSPIClockSource\n
  *         CCIPR2     SPI23SEL        LL_RCC_GetSPIClockSource\n
  *         CCIPR3     SPI45SEL        LL_RCC_GetSPIClockSource\n
  *         CCIPR4    SPI6SEL         LL_RCC_GetSPIClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_I2S_CKIN
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_CLKP
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPIClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get USARTx clock source
  * @rmtoll CCIPR3      USART1SEL      LL_RCC_GetUSARTClockSource\n
  *         CCIPR2      UART234578SEL  LL_RCC_GetUSARTClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get USBPHYC clock source
  * @rmtoll CCIPR1       USBPHYCSEL    LL_RCC_GetUSBPHYCClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE_DISABLE
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE_HSE_DIV_2
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE_PLL3Q
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBPHYCClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USBPHYCSEL));
}

/**
  * @brief  Configure USBREF clock frequency
  * @rmtoll CCIPR1       USBREFCKSEL   LL_RCC_GetUSBREFClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_16M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_19_2M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_20M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_24M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_26M
  *         @arg @ref LL_RCC_USBREF_CLKSOURCE_32M
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBREFClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (READ_BIT(RCC->CCIPR1, RCC_CCIPR1_USBREFCKSEL));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source
  * @note   Once the RTC clock source has been selected, it cannot be changed anymore unless
  *         the Backup domain is reset, or unless a failure is detected on LSE (LSECSSD is
  *         set). The BDRST bit can be used to reset them.
  * @rmtoll BDCR         RTCSEL        LL_RCC_SetRTCClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE
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
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE
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
  * @rmtoll BDCR         VSWRST         LL_RCC_ForceBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_VSWRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll BDCR         VSWRST          LL_RCC_ReleaseBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_VSWRST);
}

/**
  * @brief  Set HSE Prescalers for RTC Clock
  * @rmtoll CFGR         RTCPRE        LL_RCC_SetRTC_HSEPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_NOCLOCK
  *         @arg @ref LL_RCC_RTC_HSE_DIV_2
  *         @arg @ref LL_RCC_RTC_HSE_DIV_3
  *         @arg @ref LL_RCC_RTC_HSE_DIV_4
  *         @arg @ref LL_RCC_RTC_HSE_DIV_5
  *         @arg @ref LL_RCC_RTC_HSE_DIV_6
  *         @arg @ref LL_RCC_RTC_HSE_DIV_7
  *         @arg @ref LL_RCC_RTC_HSE_DIV_8
  *         @arg @ref LL_RCC_RTC_HSE_DIV_9
  *         @arg @ref LL_RCC_RTC_HSE_DIV_10
  *         @arg @ref LL_RCC_RTC_HSE_DIV_11
  *         @arg @ref LL_RCC_RTC_HSE_DIV_12
  *         @arg @ref LL_RCC_RTC_HSE_DIV_13
  *         @arg @ref LL_RCC_RTC_HSE_DIV_14
  *         @arg @ref LL_RCC_RTC_HSE_DIV_15
  *         @arg @ref LL_RCC_RTC_HSE_DIV_16
  *         @arg @ref LL_RCC_RTC_HSE_DIV_17
  *         @arg @ref LL_RCC_RTC_HSE_DIV_18
  *         @arg @ref LL_RCC_RTC_HSE_DIV_19
  *         @arg @ref LL_RCC_RTC_HSE_DIV_20
  *         @arg @ref LL_RCC_RTC_HSE_DIV_21
  *         @arg @ref LL_RCC_RTC_HSE_DIV_22
  *         @arg @ref LL_RCC_RTC_HSE_DIV_23
  *         @arg @ref LL_RCC_RTC_HSE_DIV_24
  *         @arg @ref LL_RCC_RTC_HSE_DIV_25
  *         @arg @ref LL_RCC_RTC_HSE_DIV_26
  *         @arg @ref LL_RCC_RTC_HSE_DIV_27
  *         @arg @ref LL_RCC_RTC_HSE_DIV_28
  *         @arg @ref LL_RCC_RTC_HSE_DIV_29
  *         @arg @ref LL_RCC_RTC_HSE_DIV_30
  *         @arg @ref LL_RCC_RTC_HSE_DIV_31
  *         @arg @ref LL_RCC_RTC_HSE_DIV_32
  *         @arg @ref LL_RCC_RTC_HSE_DIV_33
  *         @arg @ref LL_RCC_RTC_HSE_DIV_34
  *         @arg @ref LL_RCC_RTC_HSE_DIV_35
  *         @arg @ref LL_RCC_RTC_HSE_DIV_36
  *         @arg @ref LL_RCC_RTC_HSE_DIV_37
  *         @arg @ref LL_RCC_RTC_HSE_DIV_38
  *         @arg @ref LL_RCC_RTC_HSE_DIV_39
  *         @arg @ref LL_RCC_RTC_HSE_DIV_40
  *         @arg @ref LL_RCC_RTC_HSE_DIV_41
  *         @arg @ref LL_RCC_RTC_HSE_DIV_42
  *         @arg @ref LL_RCC_RTC_HSE_DIV_43
  *         @arg @ref LL_RCC_RTC_HSE_DIV_44
  *         @arg @ref LL_RCC_RTC_HSE_DIV_45
  *         @arg @ref LL_RCC_RTC_HSE_DIV_46
  *         @arg @ref LL_RCC_RTC_HSE_DIV_47
  *         @arg @ref LL_RCC_RTC_HSE_DIV_48
  *         @arg @ref LL_RCC_RTC_HSE_DIV_49
  *         @arg @ref LL_RCC_RTC_HSE_DIV_50
  *         @arg @ref LL_RCC_RTC_HSE_DIV_51
  *         @arg @ref LL_RCC_RTC_HSE_DIV_52
  *         @arg @ref LL_RCC_RTC_HSE_DIV_53
  *         @arg @ref LL_RCC_RTC_HSE_DIV_54
  *         @arg @ref LL_RCC_RTC_HSE_DIV_55
  *         @arg @ref LL_RCC_RTC_HSE_DIV_56
  *         @arg @ref LL_RCC_RTC_HSE_DIV_57
  *         @arg @ref LL_RCC_RTC_HSE_DIV_58
  *         @arg @ref LL_RCC_RTC_HSE_DIV_59
  *         @arg @ref LL_RCC_RTC_HSE_DIV_60
  *         @arg @ref LL_RCC_RTC_HSE_DIV_61
  *         @arg @ref LL_RCC_RTC_HSE_DIV_62
  *         @arg @ref LL_RCC_RTC_HSE_DIV_63
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRTC_HSEPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_RTCPRE, Prescaler);
}

/**
  * @brief  Get HSE Prescalers for RTC Clock
  * @rmtoll CFGR         RTCPRE        LL_RCC_GetRTC_HSEPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_NOCLOCK
  *         @arg @ref LL_RCC_RTC_HSE_DIV_2
  *         @arg @ref LL_RCC_RTC_HSE_DIV_3
  *         @arg @ref LL_RCC_RTC_HSE_DIV_4
  *         @arg @ref LL_RCC_RTC_HSE_DIV_5
  *         @arg @ref LL_RCC_RTC_HSE_DIV_6
  *         @arg @ref LL_RCC_RTC_HSE_DIV_7
  *         @arg @ref LL_RCC_RTC_HSE_DIV_8
  *         @arg @ref LL_RCC_RTC_HSE_DIV_9
  *         @arg @ref LL_RCC_RTC_HSE_DIV_10
  *         @arg @ref LL_RCC_RTC_HSE_DIV_11
  *         @arg @ref LL_RCC_RTC_HSE_DIV_12
  *         @arg @ref LL_RCC_RTC_HSE_DIV_13
  *         @arg @ref LL_RCC_RTC_HSE_DIV_14
  *         @arg @ref LL_RCC_RTC_HSE_DIV_15
  *         @arg @ref LL_RCC_RTC_HSE_DIV_16
  *         @arg @ref LL_RCC_RTC_HSE_DIV_17
  *         @arg @ref LL_RCC_RTC_HSE_DIV_18
  *         @arg @ref LL_RCC_RTC_HSE_DIV_19
  *         @arg @ref LL_RCC_RTC_HSE_DIV_20
  *         @arg @ref LL_RCC_RTC_HSE_DIV_21
  *         @arg @ref LL_RCC_RTC_HSE_DIV_22
  *         @arg @ref LL_RCC_RTC_HSE_DIV_23
  *         @arg @ref LL_RCC_RTC_HSE_DIV_24
  *         @arg @ref LL_RCC_RTC_HSE_DIV_25
  *         @arg @ref LL_RCC_RTC_HSE_DIV_26
  *         @arg @ref LL_RCC_RTC_HSE_DIV_27
  *         @arg @ref LL_RCC_RTC_HSE_DIV_28
  *         @arg @ref LL_RCC_RTC_HSE_DIV_29
  *         @arg @ref LL_RCC_RTC_HSE_DIV_30
  *         @arg @ref LL_RCC_RTC_HSE_DIV_31
  *         @arg @ref LL_RCC_RTC_HSE_DIV_32
  *         @arg @ref LL_RCC_RTC_HSE_DIV_33
  *         @arg @ref LL_RCC_RTC_HSE_DIV_34
  *         @arg @ref LL_RCC_RTC_HSE_DIV_35
  *         @arg @ref LL_RCC_RTC_HSE_DIV_36
  *         @arg @ref LL_RCC_RTC_HSE_DIV_37
  *         @arg @ref LL_RCC_RTC_HSE_DIV_38
  *         @arg @ref LL_RCC_RTC_HSE_DIV_39
  *         @arg @ref LL_RCC_RTC_HSE_DIV_40
  *         @arg @ref LL_RCC_RTC_HSE_DIV_41
  *         @arg @ref LL_RCC_RTC_HSE_DIV_42
  *         @arg @ref LL_RCC_RTC_HSE_DIV_43
  *         @arg @ref LL_RCC_RTC_HSE_DIV_44
  *         @arg @ref LL_RCC_RTC_HSE_DIV_45
  *         @arg @ref LL_RCC_RTC_HSE_DIV_46
  *         @arg @ref LL_RCC_RTC_HSE_DIV_47
  *         @arg @ref LL_RCC_RTC_HSE_DIV_48
  *         @arg @ref LL_RCC_RTC_HSE_DIV_49
  *         @arg @ref LL_RCC_RTC_HSE_DIV_50
  *         @arg @ref LL_RCC_RTC_HSE_DIV_51
  *         @arg @ref LL_RCC_RTC_HSE_DIV_52
  *         @arg @ref LL_RCC_RTC_HSE_DIV_53
  *         @arg @ref LL_RCC_RTC_HSE_DIV_54
  *         @arg @ref LL_RCC_RTC_HSE_DIV_55
  *         @arg @ref LL_RCC_RTC_HSE_DIV_56
  *         @arg @ref LL_RCC_RTC_HSE_DIV_57
  *         @arg @ref LL_RCC_RTC_HSE_DIV_58
  *         @arg @ref LL_RCC_RTC_HSE_DIV_59
  *         @arg @ref LL_RCC_RTC_HSE_DIV_60
  *         @arg @ref LL_RCC_RTC_HSE_DIV_61
  *         @arg @ref LL_RCC_RTC_HSE_DIV_62
  *         @arg @ref LL_RCC_RTC_HSE_DIV_63
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTC_HSEPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_RTCPRE));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_TIM_CLOCK_PRESCALER TIM
  * @{
  */

/**
  * @brief  Set Timers Clock Prescalers
  * @rmtoll CFGR         TIMPRE        LL_RCC_SetTIMPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_TIM_PRESCALER_DISABLE
  *         @arg @ref LL_RCC_TIM_PRESCALER_ENABLE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTIMPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_TIMPRE, Prescaler);
}

/**
  * @brief  Get Timers Clock Prescalers
  * @rmtoll CFGR         TIMPRE        LL_RCC_GetTIMPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_TIM_PRESCALER_DISABLE
  *         @arg @ref LL_RCC_TIM_PRESCALER_ENABLE
  */
__STATIC_INLINE uint32_t LL_RCC_GetTIMPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_TIMPRE));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_USBPHYC USBPHYC
  * @{
  */

/**
  * @brief  Enable USBPHYC power-down
  * @rmtoll AHB1LPENR    UCPDCTRL         LL_RCC_USBPHYC_EnablePowerDown
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USBPHYC_EnablePowerDown(void)
{
  SET_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_UCPDCTRL);
}

/**
  * @brief  Disable USBPHYC power-down
  * @rmtoll AHB1LPENR    UCPDCTRL         LL_RCC_USBPHYC_DisablePowerDown
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USBPHYC_DisablePowerDown(void)
{
  CLEAR_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_UCPDCTRL);
}

/**
  * @brief  Check if USBPHYC is powered-down
  * @rmtoll AHB1LPENR    UCPDCTRL         LL_RCC_USBPHYC_IsEnabledPowerDown
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_USBPHYC_IsEnabledPowerDown(void)
{
  return ((READ_BIT(RCC->AHB1LPENR, RCC_AHB1LPENR_UCPDCTRL) == (RCC_AHB1LPENR_UCPDCTRL)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL PLL
  * @{
  */

/**
  * @brief  Set the oscillator used as PLL clock source.
  * @note   PLL clock source is common to all PLLs.
  * @note   PLLSRC can be written only when all PLLs are disabled.
  * @rmtoll PLLCKSELR    PLLSRC        LL_RCC_PLL_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_CSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL clock source.
  * @rmtoll PLLCKSELR    PLLSRC        LL_RCC_PLL_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_CSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC));
}

/**
  * @brief  Enable PLL1
  * @rmtoll CR           PLL1ON         LL_RCC_PLL1_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLL1ON);
}

/**
  * @brief  Disable PLL1
  * @note Cannot be disabled if the PLL1 clock is used as the system clock
  * @rmtoll CR           PLL1ON         LL_RCC_PLL1_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON);
}

/**
  * @brief  Check if PLL1 Ready
  * @rmtoll CR           PLL1RDY        LL_RCC_PLL1_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_PLL1RDY) == (RCC_CR_PLL1RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL1 used for SYSCLK Domain
  * @note PLL Source, DIVM1, DIVN and DIVP can be written only when PLL is disabled.
  * @note PLLN/PLLR can be written only when PLL is disabled.
  * @rmtoll PLLCKSELR    PLLSRC        LL_RCC_PLL1_ConfigDomain_SYS\n
  *         PLLCKSELR    DIVM1         LL_RCC_PLL1_ConfigDomain_SYS\n
  *         PLL1DIVR1    DIVN          LL_RCC_PLL1_ConfigDomain_SYS\n
  *         PLL1DIVR1    DIVP          LL_RCC_PLL1_ConfigDomain_SYS
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_CSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  *         @arg @ref LL_RCC_PLLSOURCE_NONE
  * @param  M parameter can be a value between 1 and 64
  * @param  N parameter can be a value between 8 to 420
  * @param  P parameter can be a value between 2 and 128 (odd division factor not supported)
  *
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_SYS(uint32_t Source, uint32_t M, uint32_t N, uint32_t P)
{
  MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM1 | RCC_PLLCKSELR_PLLSRC,
             (M << RCC_PLLCKSELR_DIVM1_Pos) | Source);
  MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVP | RCC_PLL1DIVR1_DIVN,
             ((P - 1UL) << RCC_PLL1DIVR1_DIVP_Pos) | ((N - 1UL) << RCC_PLL1DIVR1_DIVN_Pos));
}

/**
  * @brief  Enable PLL1P
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1PEN         LL_RCC_PLL1P_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1P_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN);
}

/**
  * @brief  Enable PLL1Q
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1QEN         LL_RCC_PLL1Q_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1Q_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1QEN);
}

/**
  * @brief  Enable PLL1R
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1REN         LL_RCC_PLL1R_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1R_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1REN);
}

/**
  * @brief  Enable PLL1S
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1SEN         LL_RCC_PLL1S_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1S_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SEN);
}

/**
  * @brief  Enable PLL1 FRACN
  * @rmtoll PLLCFGR      PLL1FRACEN         LL_RCC_PLL1FRACN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1FRACN_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN);
}

/**
  * @brief  Check if PLL1 P is enabled
  * @rmtoll PLLCFGR      PLL1PEN         LL_RCC_PLL1P_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1P_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN) == RCC_PLLCFGR_PLL1PEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1 Q is enabled
  * @rmtoll PLLCFGR      PLL1QEN         LL_RCC_PLL1Q_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1Q_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1QEN) == RCC_PLLCFGR_PLL1QEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1 R is enabled
  * @rmtoll PLLCFGR      PLL1REN         LL_RCC_PLL1R_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1R_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1REN) == RCC_PLLCFGR_PLL1REN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1 S is enabled
  * @rmtoll PLLCFGR      PLL1SEN         LL_RCC_PLL1S_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1S_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SEN) == RCC_PLLCFGR_PLL1SEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1 FRACN is enabled
  * @rmtoll PLLCFGR      PLL1FRACEN         LL_RCC_PLL1FRACN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1FRACN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN) == RCC_PLLCFGR_PLL1FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Disable PLL1P
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1PEN         LL_RCC_PLL1P_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1P_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN);
}

/**
  * @brief  Disable PLL1Q
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1QEN         LL_RCC_PLL1Q_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1Q_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1QEN);
}

/**
  * @brief  Disable PLL1R
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1REN         LL_RCC_PLL1R_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1R_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1REN);
}

/**
  * @brief  Disable PLL1S
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1SEN         LL_RCC_PLL1S_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1S_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SEN);
}

/**
  * @brief  Disable PLL1 FRACN
  * @rmtoll PLLCFGR      PLL1FRACEN         LL_RCC_PLL1FRACN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1FRACN_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN);
}

/**
  * @brief  Get PLL1 VCO Input Range
  * @rmtoll PLLCFGR      PLL1RGE       LL_RCC_PLL1_GetVCOInputRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetVCOInputRange(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1RGE));
}

/**
  * @brief  Get PLL1 VCO OutputRange
  * @rmtoll PLLCFGR      PLL1VCOSEL       LL_RCC_PLL1_GetVCOOutputRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_WIDE
  *         @arg @ref LL_RCC_PLLVCORANGE_MEDIUM
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetVCOOutputRange(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1VCOSEL));
}

/**
  * @brief  Set PLL1 VCO Input Range
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1RGE       LL_RCC_PLL1_SetVCOInputRange
  * @param  InputRange This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_SetVCOInputRange(uint32_t InputRange)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL1RGE, InputRange);
}

/**
  * @brief  Set PLL1 VCO OutputRange
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCFGR      PLL1VCOSEL       LL_RCC_PLL1_SetVCOOutputRange
  * @param  VCORange This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_WIDE
  *         @arg @ref LL_RCC_PLLVCORANGE_MEDIUM
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_SetVCOOutputRange(uint32_t VCORange)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL1VCOSEL, VCORange);
}

/**
  * @brief  Get PLL1 N Coefficient
  * @rmtoll PLL1DIVR1    DIVN          LL_RCC_PLL1_GetN
  * @retval A value between 8 and 420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetN(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVN) >>  RCC_PLL1DIVR1_DIVN_Pos) + 1UL);
}

/**
  * @brief  Get PLL1 M Coefficient
  * @rmtoll PLLCKSELR    DIVM1          LL_RCC_PLL1_GetM
  * @retval A value between 0 and 63
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetM(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM1) >>  RCC_PLLCKSELR_DIVM1_Pos);
}

/**
  * @brief  Get PLL1 P Coefficient
  * @rmtoll PLL1DIVR1    DIVP          LL_RCC_PLL1_GetP
  * @retval A value between 2 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetP(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVP) >>  RCC_PLL1DIVR1_DIVP_Pos) + 1UL);
}

/**
  * @brief  Get PLL1 Q Coefficient
  * @rmtoll PLL1DIVR1    DIVQ          LL_RCC_PLL1_GetQ
  * @retval A value between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetQ(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVQ) >>  RCC_PLL1DIVR1_DIVQ_Pos) + 1UL);
}

/**
  * @brief  Get PLL1 R Coefficient
  * @rmtoll PLL1DIVR1    DIVR          LL_RCC_PLL1_GetR
  * @retval A value between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetR(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVR) >>  RCC_PLL1DIVR1_DIVR_Pos) + 1UL);
}

/**
  * @brief  Get PLL1 S Coefficient
  * @rmtoll PLL1DIVR2    DIVS          LL_RCC_PLL1_GetS
  * @retval A value between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetS(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR2, RCC_PLL1DIVR2_DIVS) >>  RCC_PLL1DIVR2_DIVS_Pos) + 1UL);
}

/**
  * @brief  Get PLL1 FRACN Coefficient
  * @rmtoll PLL1FRACR    FRACN         LL_RCC_PLL1_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetFRACN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1FRACR, RCC_PLL1FRACR_FRACN) >>  RCC_PLL1FRACR_FRACN_Pos);
}

/**
  * @brief  Set PLL1 N Coefficient
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLL1DIVR1    DIVN          LL_RCC_PLL1_SetN
  * @param  N parameter can be a value between 8 and 420
  */
__STATIC_INLINE void LL_RCC_PLL1_SetN(uint32_t N)
{
  MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVN, (N - 1UL) << RCC_PLL1DIVR1_DIVN_Pos);
}

/**
  * @brief  Set PLL1 M Coefficient
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLLCKSELR    DIVM1          LL_RCC_PLL1_SetM
  * @param  M parameter can be a value between 1 and 64
  */
__STATIC_INLINE void LL_RCC_PLL1_SetM(uint32_t M)
{
  MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM1, M << RCC_PLLCKSELR_DIVM1_Pos);
}

/**
  * @brief  Set PLL1 P Coefficient
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLL1DIVR1    DIVP          LL_RCC_PLL1_SetP
  * @param  P parameter can be a value between 2 and 128 (odd division factor not supported)
  */
__STATIC_INLINE void LL_RCC_PLL1_SetP(uint32_t P)
{
  MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVP, (P - 1UL) << RCC_PLL1DIVR1_DIVP_Pos);
}

/**
  * @brief  Set PLL1 Q Coefficient
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLL1DIVR1    DIVQ          LL_RCC_PLL1_SetQ
  * @param  Q parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL1_SetQ(uint32_t Q)
{
  MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVQ, (Q - 1UL) << RCC_PLL1DIVR1_DIVQ_Pos);
}

/**
  * @brief  Set PLL1 R Coefficient
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLL1DIVR1    DIVR          LL_RCC_PLL1_SetR
  * @param  R parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL1_SetR(uint32_t R)
{
  MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVR, (R - 1UL) << RCC_PLL1DIVR1_DIVR_Pos);
}

/**
  * @brief  Set PLL1 S Coefficient
  * @note   This API shall be called only when PLL1 is disabled.
  * @rmtoll PLL1DIVR2    DIVS          LL_RCC_PLL1_SetS
  * @param  S parameter can be a value between 1 and 8
  */
__STATIC_INLINE void LL_RCC_PLL1_SetS(uint32_t S)
{
  MODIFY_REG(RCC->PLL1DIVR2, RCC_PLL1DIVR2_DIVS, (S - 1UL) << RCC_PLL1DIVR2_DIVS_Pos);
}

/**
  * @brief  Set PLL1 FRACN Coefficient
  * @rmtoll PLL1FRACR    FRACN         LL_RCC_PLL1_SetFRACN
  * @param  FRACN parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL1_SetFRACN(uint32_t FRACN)
{
  MODIFY_REG(RCC->PLL1FRACR, RCC_PLL1FRACR_FRACN, FRACN << RCC_PLL1FRACR_FRACN_Pos);
}

/**
  * @brief  Enable Spread Spectrum for PLL1.
  * @note   Configuration to be done with LL_RCC_PLL1_ConfigSpreadSpectrum
  * @rmtoll PLLCFGR      PLL1SSCGEN    LL_RCC_PLL1_EnableSpreadSpectrum
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableSpreadSpectrum(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SSCGEN);
}

/**
  * @brief  Disable Spread Spectrum for PLL1.
  * @rmtoll PLLCFGR      PLL1SSCGEN    LL_RCC_PLL1_DisableSpreadSpectrum
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableSpreadSpectrum(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SSCGEN);
}

/**
  * @brief  Check if Spread Spectrum for PLL1 is enabled
  * @rmtoll PLLCFGR      PLL1SSCGEN       LL_RCC_PLL1_IsEnabledSpreadSpectrum
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledSpreadSpectrum(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SSCGEN) == RCC_PLLCFGR_PLL1SSCGEN) ? 1UL : 0UL);
}

/**
  * @brief  Get Spread Spectrum Modulation Period for PLL1
  * @rmtoll PLL1SSCGR    MODPER        LL_RCC_PLL1_GetModulationPeriod
  * @retval Between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetModulationPeriod(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_MODPER));
}

/**
  * @brief  Get Spread Spectrum Increment Step for PLL1
  * @rmtoll PLL1SSCGR    INCSTEP       LL_RCC_PLL1_GetIncrementStep
  * @retval Between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetIncrementStep(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_INCSTEP) >> RCC_PLL1SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Get Spread Spectrum Selection for PLL1
  * @rmtoll PLL1SSCGR    SPREADSEL     LL_RCC_PLL1_GetSpreadSelection
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetSpreadSelection(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_SPREADSEL));
}

/**
  * @brief  Check if Dithering RPDF Noise for PLL1 is enabled
  * @rmtoll PLL1SSCGR      RPDFNDIS       LL_RCC_PLL1_IsEnabledRPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledRPDFNDithering(void)
{
  return ((READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_RPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Check if Dithering TPDF Noise for PLL1 is enabled
  * @rmtoll PLL1SSCGR      TPDFNDIS       LL_RCC_PLL1_IsEnabledTPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledTPDFNDithering(void)
{
  return ((READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_TPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2
  * @rmtoll CR           PLL2ON        LL_RCC_PLL2_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLL2ON);
}

/**
  * @brief  Disable PLL2
  * @note Cannot be disabled if the PLL2 clock is used as the system clock
  * @rmtoll CR           PLL2ON        LL_RCC_PLL2_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON);
}

/**
  * @brief  Check if PLL2 Ready
  * @rmtoll CR           PLL2RDY       LL_RCC_PLL2_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_PLL2RDY) == RCC_CR_PLL2RDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2P
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2PEN       LL_RCC_PLL2P_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2P_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2PEN);
}

/**
  * @brief  Enable PLL2Q
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2QEN       LL_RCC_PLL2Q_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2Q_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2QEN);
}

/**
  * @brief  Enable PLL2R
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2REN       LL_RCC_PLL2R_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2R_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2REN);
}

/**
  * @brief  Enable PLL2S
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2SEN       LL_RCC_PLL2S_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2S_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SEN);
}

/**
  * @brief  Enable PLL2T
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2TEN       LL_RCC_PLL2T_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2T_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2TEN);
}

/**
  * @brief  Enable PLL2 FRACN
  * @rmtoll PLLCFGR      PLL2FRACEN    LL_RCC_PLL2FRACN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2FRACN_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACEN);
}

/**
  * @brief  Check if PLL2 P is enabled
  * @rmtoll PLLCFGR      PLL2PEN       LL_RCC_PLL2P_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2P_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2PEN) == RCC_PLLCFGR_PLL2PEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 Q is enabled
  * @rmtoll PLLCFGR      PLL2QEN       LL_RCC_PLL2Q_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2Q_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2QEN) == RCC_PLLCFGR_PLL2QEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 R is enabled
  * @rmtoll PLLCFGR      PLL2REN       LL_RCC_PLL2R_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2R_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2REN) == RCC_PLLCFGR_PLL2REN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 S is enabled
  * @rmtoll PLLCFGR      PLL2SEN       LL_RCC_PLL2S_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2S_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SEN) == RCC_PLLCFGR_PLL2SEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 T is enabled
  * @rmtoll PLLCFGR      PLL2TEN       LL_RCC_PLL2T_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2T_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2TEN) == RCC_PLLCFGR_PLL2TEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 FRACN is enabled
  * @rmtoll PLLCFGR      PLL2FRACEN    LL_RCC_PLL2FRACN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2FRACN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACEN) == RCC_PLLCFGR_PLL2FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Disable PLL2P
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2PEN       LL_RCC_PLL2P_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2P_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2PEN);
}

/**
  * @brief  Disable PLL2Q
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2QEN       LL_RCC_PLL2Q_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2Q_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2QEN);
}

/**
  * @brief  Disable PLL2R
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2REN       LL_RCC_PLL2R_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2R_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2REN);
}

/**
  * @brief  Disable PLL2S
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2SEN       LL_RCC_PLL2S_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2S_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SEN);
}

/**
  * @brief  Disable PLL2T
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2TEN       LL_RCC_PLL2T_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2T_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2TEN);
}

/**
  * @brief  Disable PLL2 FRACN
  * @rmtoll PLLCFGR      PLL2FRACEN    LL_RCC_PLL2FRACN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2FRACN_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACEN);
}

/**
  * @brief  Get PLL2 VCO Input Range
  * @rmtoll PLLCFGR      PLL2RGE       LL_RCC_PLL2_GetVCOInputRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetVCOInputRange(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2RGE) >> 11U);
}

/**
  * @brief  Get PLL2 VCO OutputRange
  * @rmtoll PLLCFGR      PLL2VCOSEL       LL_RCC_PLL2_GetVCOOutputRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_WIDE
  *         @arg @ref LL_RCC_PLLVCORANGE_MEDIUM
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetVCOOutputRange(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2VCOSEL) >> 11U);
}

/**
  * @brief  Set PLL2 VCO Input Range
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2RGE       LL_RCC_PLL2_SetVCOInputRange
  * @param  InputRange This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_SetVCOInputRange(uint32_t InputRange)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL2RGE, (InputRange << 11U));
}

/**
  * @brief  Set PLL2 VCO OutputRange
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCFGR      PLL2VCOSEL       LL_RCC_PLL2_SetVCOOutputRange
  * @param  VCORange This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_WIDE
  *         @arg @ref LL_RCC_PLLVCORANGE_MEDIUM
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_SetVCOOutputRange(uint32_t VCORange)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL2VCOSEL, (VCORange << 11U));
}

/**
  * @brief  Get PLL2 N Coefficient
  * @rmtoll PLL2DIVR1    DIVN          LL_RCC_PLL2_GetN
  * @retval A value between 8 and 420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetN(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVN) >>  RCC_PLL2DIVR1_DIVN_Pos) + 1UL);
}

/**
  * @brief  Get PLL2 M Coefficient
  * @rmtoll PLLCKSELR    DIVM2         LL_RCC_PLL2_GetM
  * @retval A value between 0 and 63
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetM(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM2) >>  RCC_PLLCKSELR_DIVM2_Pos);
}

/**
  * @brief  Get PLL2 P Coefficient
  * @rmtoll PLL2DIVR1    DIVP          LL_RCC_PLL2_GetP
  * @retval A value between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetP(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVP) >>  RCC_PLL2DIVR1_DIVP_Pos) + 1UL);
}

/**
  * @brief  Get PLL2 Q Coefficient
  * @rmtoll PLL2DIVR1    DIVQ          LL_RCC_PLL2_GetQ
  * @retval A value between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetQ(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVQ) >>  RCC_PLL2DIVR1_DIVQ_Pos) + 1UL);
}

/**
  * @brief  Get PLL2 R Coefficient
  * @rmtoll PLL2DIVR1    DIVR          LL_RCC_PLL2_GetR
  * @retval A value between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetR(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVR) >>  RCC_PLL2DIVR1_DIVR_Pos) + 1UL);
}

/**
  * @brief  Get PLL2 S Coefficient
  * @rmtoll PLL2DIVR2    DIVS          LL_RCC_PLL2_GetS
  * @retval A value between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetS(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR2, RCC_PLL2DIVR2_DIVS) >>  RCC_PLL2DIVR2_DIVS_Pos) + 1UL);
}

/**
  * @brief  Get PLL2 T Coefficient
  * @rmtoll PLL2DIVR2    DIVT          LL_RCC_PLL2_GetT
  * @retval A value between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetT(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR2, RCC_PLL2DIVR2_DIVT) >>  RCC_PLL2DIVR2_DIVT_Pos) + 1UL);
}

/**
  * @brief  Get PLL2 FRACN Coefficient
  * @rmtoll PLL2FRACR    FRACN         LL_RCC_PLL2_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFRACN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2FRACR, RCC_PLL2FRACR_FRACN) >>  RCC_PLL2FRACR_FRACN_Pos);
}

/**
  * @brief  Set PLL2 N Coefficient
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLL2DIVR1    DIVN          LL_RCC_PLL2_SetN
  * @param  N parameter can be a value between 8 and 420
  */
__STATIC_INLINE void LL_RCC_PLL2_SetN(uint32_t N)
{
  MODIFY_REG(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVN, (N - 1UL) << RCC_PLL2DIVR1_DIVN_Pos);
}

/**
  * @brief  Set PLL2 M Coefficient
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLLCKSELR    DIVM2         LL_RCC_PLL2_SetM
  * @param  M parameter can be a value between 1 and 64
  */
__STATIC_INLINE void LL_RCC_PLL2_SetM(uint32_t M)
{
  MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM2, M << RCC_PLLCKSELR_DIVM2_Pos);
}

/**
  * @brief  Set PLL2 P Coefficient
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLL2DIVR1    DIVP          LL_RCC_PLL2_SetP
  * @param  P parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL2_SetP(uint32_t P)
{
  MODIFY_REG(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVP, (P - 1UL) << RCC_PLL2DIVR1_DIVP_Pos);
}

/**
  * @brief  Set PLL2 Q Coefficient
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLL2DIVR1    DIVQ          LL_RCC_PLL2_SetQ
  * @param  Q parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL2_SetQ(uint32_t Q)
{
  MODIFY_REG(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVQ, (Q - 1UL) << RCC_PLL2DIVR1_DIVQ_Pos);
}

/**
  * @brief  Set PLL2 R Coefficient
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLL2DIVR1    DIVR          LL_RCC_PLL2_SetR
  * @param  R parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL2_SetR(uint32_t R)
{
  MODIFY_REG(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVR, (R - 1UL) << RCC_PLL2DIVR1_DIVR_Pos);
}

/**
  * @brief  Set PLL2 S Coefficient
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLL2DIVR2    DIVS          LL_RCC_PLL2_SetS
  * @param  S parameter can be a value between 1 and 8
  */
__STATIC_INLINE void LL_RCC_PLL2_SetS(uint32_t S)
{
  MODIFY_REG(RCC->PLL2DIVR2, RCC_PLL2DIVR2_DIVS, (S - 1UL) << RCC_PLL2DIVR2_DIVS_Pos);
}

/**
  * @brief  Set PLL2 T Coefficient
  * @note   This API shall be called only when PLL2 is disabled.
  * @rmtoll PLL2DIVR2    DIVT          LL_RCC_PLL2_SetT
  * @param  T parameter can be a value between 1 and 8
  */
__STATIC_INLINE void LL_RCC_PLL2_SetT(uint32_t T)
{
  MODIFY_REG(RCC->PLL2DIVR2, RCC_PLL2DIVR2_DIVT, (T - 1UL) << RCC_PLL2DIVR2_DIVT_Pos);
}

/**
  * @brief  Set PLL2 FRACN Coefficient
  * @rmtoll PLL2FRACR    FRACN         LL_RCC_PLL2_SetFRACN
  * @param  FRACN parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL2_SetFRACN(uint32_t FRACN)
{
  MODIFY_REG(RCC->PLL2FRACR, RCC_PLL2FRACR_FRACN, FRACN << RCC_PLL2FRACR_FRACN_Pos);
}

/**
  * @brief  Enable Spread Spectrum for PLL2.
  * @note   Configuration to be done with LL_RCC_PLL2_ConfigSpreadSpectrum
  * @rmtoll PLLCFGR      PLL2SSCGEN    LL_RCC_PLL2_EnableSpreadSpectrum
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableSpreadSpectrum(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SSCGEN);
}

/**
  * @brief  Disable Spread Spectrum for PLL2.
  * @rmtoll PLLCFGR      PLL2SSCGEN    LL_RCC_PLL2_DisableSpreadSpectrum
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableSpreadSpectrum(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SSCGEN);
}

/**
  * @brief  Check if Spread Spectrum for PLL2 is enabled
  * @rmtoll PLLCFGR      PLL2SSCGEN       LL_RCC_PLL2_IsEnabledSpreadSpectrum
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledSpreadSpectrum(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SSCGEN) == RCC_PLLCFGR_PLL2SSCGEN) ? 1UL : 0UL);
}

/**
  * @brief  Get Spread Spectrum Modulation Period for PLL2
  * @rmtoll PLL2SSCGR    MODPER        LL_RCC_PLL2_GetModulationPeriod
  * @retval Between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetModulationPeriod(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_MODPER));
}

/**
  * @brief  Get Spread Spectrum Increment Step for PLL2
  * @rmtoll PLL2SSCGR    INCSTEP       LL_RCC_PLL2_GetIncrementStep
  * @retval Between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetIncrementStep(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_INCSTEP) >> RCC_PLL2SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Get Spread Spectrum Selection for PLL2
  * @rmtoll PLL2SSCGR    SPREADSEL     LL_RCC_PLL2_GetSpreadSelection
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetSpreadSelection(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_SPREADSEL));
}


/**
  * @brief  Check if Dithering RPDF Noise for PLL2 is enabled
  * @rmtoll PLL2SSCGR      RPDFNDIS       LL_RCC_PLL2_IsEnabledRPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledRPDFNDithering(void)
{
  return ((READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_RPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Check if Dithering TPDF Noise for PLL2 is enabled
  * @rmtoll PLL2SSCGR      TPDFNDIS       LL_RCC_PLL2_IsEnabledTPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledTPDFNDithering(void)
{
  return ((READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_TPDFNDIS) == 0U) ? 1UL : 0UL);
}
/**
  * @brief  Enable PLL3
  * @rmtoll CR           PLL3ON        LL_RCC_PLL3_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLL3ON);
}

/**
  * @brief  Disable PLL3
  * @note Cannot be disabled if the PLL3 clock is used as the system clock
  * @rmtoll CR           PLL3ON        LL_RCC_PLL3_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLL3ON);
}

/**
  * @brief  Check if PLL3 Ready
  * @rmtoll CR           PLL3RDY       LL_RCC_PLL3_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_PLL3RDY) == RCC_CR_PLL3RDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL3P
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3PEN       LL_RCC_PLL3P_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3P_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3PEN);
}

/**
  * @brief  Enable PLL3Q
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3QEN       LL_RCC_PLL3Q_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3Q_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3QEN);
}

/**
  * @brief  Enable PLL3R
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3REN       LL_RCC_PLL3R_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3R_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3REN);
}

/**
  * @brief  Enable PLL3S
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3SEN       LL_RCC_PLL3S_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3S_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SEN);
}

/**
  * @brief  Enable PLL3 FRACN
  * @rmtoll PLLCFGR      PLL3FRACEN    LL_RCC_PLL3FRACN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3FRACN_Enable(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3FRACEN);
}

/**
  * @brief  Check if PLL3 P is enabled
  * @rmtoll PLLCFGR      PLL3PEN       LL_RCC_PLL3P_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3P_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3PEN) == RCC_PLLCFGR_PLL3PEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 Q is enabled
  * @rmtoll PLLCFGR      PLL3QEN       LL_RCC_PLL3Q_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3Q_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3QEN) == RCC_PLLCFGR_PLL3QEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 R is enabled
  * @rmtoll PLLCFGR      PLL3REN       LL_RCC_PLL3R_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3R_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3REN) == RCC_PLLCFGR_PLL3REN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 S is enabled
  * @rmtoll PLLCFGR      PLL3SEN       LL_RCC_PLL3S_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3S_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SEN) == RCC_PLLCFGR_PLL3SEN) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 FRACN is enabled
  * @rmtoll PLLCFGR      PLL3FRACEN    LL_RCC_PLL3FRACN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3FRACN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3FRACEN) == RCC_PLLCFGR_PLL3FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Disable PLL3P
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3PEN       LL_RCC_PLL3P_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3P_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3PEN);
}

/**
  * @brief  Disable PLL3Q
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3QEN       LL_RCC_PLL3Q_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3Q_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3QEN);
}

/**
  * @brief  Disable PLL3R
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3REN       LL_RCC_PLL3R_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3R_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3REN);
}

/**
  * @brief  Disable PLL3S
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3SEN       LL_RCC_PLL3S_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3S_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SEN);
}

/**
  * @brief  Disable PLL3 FRACN
  * @rmtoll PLLCFGR      PLL3FRACEN    LL_RCC_PLL3FRACN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3FRACN_Disable(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3FRACEN);
}

/**
  * @brief  Get PLL3 VCO Input Range
  * @rmtoll PLLCFGR      PLL3RGE       LL_RCC_PLL3_GetVCOInputRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetVCOInputRange(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3RGE) >> 22U);
}

/**
  * @brief  Get PLL3 VCO OutputRange
  * @rmtoll PLLCFGR      PLL3VCOSEL       LL_RCC_PLL3_GetVCOOutputRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_WIDE
  *         @arg @ref LL_RCC_PLLVCORANGE_MEDIUM
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetVCOOutputRange(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3VCOSEL) >> 22U);
}

/**
  * @brief  Set PLL3 VCO Input Range
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3RGE       LL_RCC_PLL3_SetVCOInputRange
  * @param  InputRange This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_SetVCOInputRange(uint32_t InputRange)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL3RGE, (InputRange << 22U));
}

/**
  * @brief  Set PLL3 VCO OutputRange
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCFGR      PLL3VCOSEL       LL_RCC_PLL3_SetVCOOutputRange
  * @param  VCORange This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_WIDE
  *         @arg @ref LL_RCC_PLLVCORANGE_MEDIUM
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_SetVCOOutputRange(uint32_t VCORange)
{
  MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL3VCOSEL, (VCORange << 22U));
}

/**
  * @brief  Get PLL3 N Coefficient
  * @rmtoll PLL3DIVR1    DIVN          LL_RCC_PLL3_GetN
  * @retval A value between 8 and 420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetN(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVN) >>  RCC_PLL3DIVR1_DIVN_Pos) + 1UL);
}

/**
  * @brief  Get PLL3 M Coefficient
  * @rmtoll PLLCKSELR    DIVM3         LL_RCC_PLL3_GetM
  * @retval A value between 0 and 63
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetM(void)
{
  return (uint32_t)(READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM3) >>  RCC_PLLCKSELR_DIVM3_Pos);
}

/**
  * @brief  Get PLL3 P Coefficient
  * @rmtoll PLL3DIVR1    DIVP          LL_RCC_PLL3_GetP
  * @retval A value between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetP(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVP) >>  RCC_PLL3DIVR1_DIVP_Pos) + 1UL);
}

/**
  * @brief  Get PLL3 Q Coefficient
  * @rmtoll PLL3DIVR1    DIVQ          LL_RCC_PLL3_GetQ
  * @retval A value between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetQ(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVQ) >>  RCC_PLL3DIVR1_DIVQ_Pos) + 1UL);
}

/**
  * @brief  Get PLL3 R Coefficient
  * @rmtoll PLL3DIVR1    DIVR          LL_RCC_PLL3_GetR
  * @retval A value between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetR(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVR) >>  RCC_PLL3DIVR1_DIVR_Pos) + 1UL);
}

/**
  * @brief  Get PLL3 S Coefficient
  * @rmtoll PLL3DIVR2    DIVS          LL_RCC_PLL3_GetS
  * @retval A value between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetS(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR2, RCC_PLL3DIVR2_DIVS) >>  RCC_PLL3DIVR2_DIVS_Pos) + 1UL);
}

/**
  * @brief  Get PLL3 FRACN Coefficient
  * @rmtoll PLL3FRACR    FRACN         LL_RCC_PLL3_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetFRACN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3FRACR, RCC_PLL3FRACR_FRACN) >>  RCC_PLL3FRACR_FRACN_Pos);
}

/**
  * @brief  Set PLL3 N Coefficient
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLL3DIVR1    DIVN          LL_RCC_PLL3_SetN
  * @param  N parameter can be a value between 8 and 420
  */
__STATIC_INLINE void LL_RCC_PLL3_SetN(uint32_t N)
{
  MODIFY_REG(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVN, (N - 1UL) << RCC_PLL3DIVR1_DIVN_Pos);
}

/**
  * @brief  Set PLL3 M Coefficient
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLLCKSELR    DIVM3         LL_RCC_PLL3_SetM
  * @param  M parameter can be a value between 1 and 64
  */
__STATIC_INLINE void LL_RCC_PLL3_SetM(uint32_t M)
{
  MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM3, M << RCC_PLLCKSELR_DIVM3_Pos);
}

/**
  * @brief  Set PLL3 P Coefficient
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLL3DIVR1    DIVP          LL_RCC_PLL3_SetP
  * @param  P parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL3_SetP(uint32_t P)
{
  MODIFY_REG(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVP, (P - 1UL) << RCC_PLL3DIVR1_DIVP_Pos);
}

/**
  * @brief  Set PLL3 Q Coefficient
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLL3DIVR1    DIVQ          LL_RCC_PLL3_SetQ
  * @param  Q parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL3_SetQ(uint32_t Q)
{
  MODIFY_REG(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVQ, (Q - 1UL) << RCC_PLL3DIVR1_DIVQ_Pos);
}

/**
  * @brief  Set PLL3 R Coefficient
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLL3DIVR1    DIVR          LL_RCC_PLL3_SetR
  * @param  R parameter can be a value between 1 and 128
  */
__STATIC_INLINE void LL_RCC_PLL3_SetR(uint32_t R)
{
  MODIFY_REG(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVR, (R - 1UL) << RCC_PLL3DIVR1_DIVR_Pos);
}

/**
  * @brief  Set PLL3 S Coefficient
  * @note   This API shall be called only when PLL3 is disabled.
  * @rmtoll PLL3DIVR2    DIVS          LL_RCC_PLL3_SetS
  * @param  S parameter can be a value between 1 and 8
  */
__STATIC_INLINE void LL_RCC_PLL3_SetS(uint32_t S)
{
  MODIFY_REG(RCC->PLL3DIVR2, RCC_PLL3DIVR2_DIVS, (S - 1UL) << RCC_PLL3DIVR2_DIVS_Pos);
}

/**
  * @brief  Set PLL3 FRACN Coefficient
  * @rmtoll PLL3FRACR    FRACN         LL_RCC_PLL3_SetFRACN
  * @param  FRACN parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL3_SetFRACN(uint32_t FRACN)
{
  MODIFY_REG(RCC->PLL3FRACR, RCC_PLL3FRACR_FRACN, FRACN << RCC_PLL3FRACR_FRACN_Pos);
}


/**
  * @brief  Enable Spread Spectrum for PLL3.
  * @note   Configuration to be done with LL_RCC_PLL3_ConfigSpreadSpectrum
  * @rmtoll PLLCFGR      PLL3SSCGEN    LL_RCC_PLL3_EnableSpreadSpectrum
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableSpreadSpectrum(void)
{
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SSCGEN);
}

/**
  * @brief  Disable Spread Spectrum for PLL3.
  * @rmtoll PLLCFGR      PLL3SSCGEN    LL_RCC_PLL3_DisableSpreadSpectrum
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableSpreadSpectrum(void)
{
  CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SSCGEN);
}

/**
  * @brief  Check if Spread Spectrum for PLL3 is enabled
  * @rmtoll PLLCFGR      PLL3SSCGEN       LL_RCC_PLL3_IsEnabledSpreadSpectrum
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledSpreadSpectrum(void)
{
  return ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SSCGEN) == RCC_PLLCFGR_PLL3SSCGEN) ? 1UL : 0UL);
}

/**
  * @brief  Get Spread Spectrum Modulation Period for PLL3
  * @rmtoll PLL3SSCGR    MODPER        LL_RCC_PLL3_GetModulationPeriod
  * @retval Between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetModulationPeriod(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_MODPER));
}

/**
  * @brief  Get Spread Spectrum Increment Step for PLL3
  * @rmtoll PLL3SSCGR    INCSTEP       LL_RCC_PLL3_GetIncrementStep
  * @retval Between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetIncrementStep(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_INCSTEP) >> RCC_PLL3SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Get Spread Spectrum Selection for PLL3
  * @rmtoll PLL3SSCGR    SPREADSEL     LL_RCC_PLL3_GetSpreadSelection
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetSpreadSelection(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_SPREADSEL));
}


/**
  * @brief  Check if Dithering RPDF Noise for PLL3 is enabled
  * @rmtoll PLL3SSCGR      RPDFNDIS       LL_RCC_PLL3_IsEnabledRPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledRPDFNDithering(void)
{
  return ((READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_RPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Check if Dithering TPDF Noise for PLL3 is enabled
  * @rmtoll PLL3SSCGR      TPDFNDIS       LL_RCC_PLL3_IsEnabledTPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledTPDFNDithering(void)
{
  return ((READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_TPDFNDIS) == 0U) ? 1UL : 0UL);
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
  * @brief  Clear CSI ready interrupt flag
  * @rmtoll CICR         CSIRDYC       LL_RCC_ClearFlag_CSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_CSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_CSIRDYC);
}

/**
  * @brief  Clear HSI48 ready interrupt flag
  * @rmtoll CICR         HSI48RDYC       LL_RCC_ClearFlag_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSI48RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSI48RDYC);
}

/**
  * @brief  Clear PLL1 ready interrupt flag
  * @rmtoll CICR         PLL1RDYC       LL_RCC_ClearFlag_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL1RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLL1RDYC);
}

/**
  * @brief  Clear PLL2 ready interrupt flag
  * @rmtoll CICR         PLL2RDYC       LL_RCC_ClearFlag_PLL2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL2RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLL2RDYC);
}

/**
  * @brief  Clear PLL3 ready interrupt flag
  * @rmtoll CICR         PLL3RDYC       LL_RCC_ClearFlag_PLL3RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL3RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLL3RDYC);
}

/**
  * @brief  Clear LSE Clock security system interrupt flag
  * @rmtoll CICR         LSECSSC         LL_RCC_ClearFlag_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSECSSC);
}

/**
  * @brief  Clear HSE Clock security system interrupt flag
  * @rmtoll CICR         HSECSSC         LL_RCC_ClearFlag_HSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSECSSC);
}

/**
  * @brief  Check if LSI ready interrupt occurred or not
  * @rmtoll CIFR         LSIRDYF       LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSIRDYF) == RCC_CIFR_LSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE ready interrupt occurred or not
  * @rmtoll CIFR         LSERDYF       LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSERDYF) == RCC_CIFR_LSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt occurred or not
  * @rmtoll CIFR         HSIRDYF       LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIRDYF) == RCC_CIFR_HSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll CIFR         HSERDYF       LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == RCC_CIFR_HSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSI ready interrupt occurred or not
  * @rmtoll CIFR         CSIRDYF       LL_RCC_IsActiveFlag_CSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_CSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_CSIRDYF) == RCC_CIFR_CSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI48 ready interrupt occurred or not
  * @rmtoll CIFR         HSI48RDYF       LL_RCC_IsActiveFlag_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSI48RDYF) == RCC_CIFR_HSI48RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1 ready interrupt occurred or not
  * @rmtoll CIFR         PLL1RDYF       LL_RCC_IsActiveFlag_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL1RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLL1RDYF) == RCC_CIFR_PLL1RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 ready interrupt occurred or not
  * @rmtoll CIFR         PLL2RDYF       LL_RCC_IsActiveFlag_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL2RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLL2RDYF) == RCC_CIFR_PLL2RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 ready interrupt occurred or not
  * @rmtoll CIFR         PLL3RDYF       LL_RCC_IsActiveFlag_PLL3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL3RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLL3RDYF) == RCC_CIFR_PLL3RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE Clock security system interrupt occurred or not
  * @rmtoll CIFR         LSECSSF          LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSECSSF) == RCC_CIFR_LSECSSF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE Clock security system interrupt occurred or not
  * @rmtoll CIFR         HSECSSF          LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSECSSF) == RCC_CIFR_HSECSSF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Low Power reset is set or not.
  * @rmtoll RSR          LPWRRSTF       LL_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPWRRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_LPWRRSTF) == RCC_RSR_LPWRRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Window Watchdog reset is set or not.
  * @rmtoll RSR          WWDGRSTF      LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_WWDGRSTF) == RCC_RSR_WWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Independent Watchdog reset is set or not.
  * @rmtoll RSR          IWDGRSTF      LL_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDGRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_IWDGRSTF) == RCC_RSR_IWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Software reset is set or not.
  * @rmtoll RSR          SFTRSTF        LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_SFTRSTF) == RCC_RSR_SFTRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag POR/PDR reset is set or not.
  * @rmtoll RSR          PORRSTF       LL_RCC_IsActiveFlag_PORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PORRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_PORRSTF) == RCC_RSR_PORRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Pin reset is set or not.
  * @rmtoll RSR          PINRSTF       LL_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PINRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_PINRSTF) == RCC_RSR_PINRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag BOR reset is set or not.
  * @rmtoll RSR          BORRSTF       LL_RCC_IsActiveFlag_BORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_BORRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_BORRSTF) == (RCC_RSR_BORRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Set RMVF bit to clear all reset flags.
  * @rmtoll RSR          RMVF          LL_RCC_ClearResetFlags
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  SET_BIT(RCC->RSR, RCC_RSR_RMVF);
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
  * @brief  Enable CSI ready interrupt
  * @rmtoll CIER         CSIRDYIE      LL_RCC_EnableIT_CSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_CSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_CSIRDYIE);
}

/**
  * @brief  Enable HSI48 ready interrupt
  * @rmtoll CIER         HSI48RDYIE      LL_RCC_EnableIT_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSI48RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}

/**
  * @brief  Enable PLL1 ready interrupt
  * @rmtoll CIER         PLL1RDYIE      LL_RCC_EnableIT_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL1RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE);
}

/**
  * @brief  Enable PLL2 ready interrupt
  * @rmtoll CIER         PLL2RDYIE  LL_RCC_EnableIT_PLL2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL2RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE);
}

/**
  * @brief  Enable PLL3 ready interrupt
  * @rmtoll CIER         PLL3RDYIE  LL_RCC_EnableIT_PLL3RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL3RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE);
}

/**
  * @brief  Enable LSECSS interrupt
  * @rmtoll CIER         LSECSSIE  LL_RCC_EnableIT_LSECSS
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
  * @brief  Disable CSI ready interrupt
  * @rmtoll CIER         CSIRDYIE      LL_RCC_DisableIT_CSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_CSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_CSIRDYIE);
}

/**
  * @brief  Disable HSI48 ready interrupt
  * @rmtoll CIER         HSI48RDYIE      LL_RCC_DisableIT_HSI48RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSI48RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}

/**
  * @brief  Disable PLL1 ready interrupt
  * @rmtoll CIER         PLL1RDYIE      LL_RCC_DisableIT_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL1RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE);
}

/**
  * @brief  Disable PLL2 ready interrupt
  * @rmtoll CIER         PLL2RDYIE  LL_RCC_DisableIT_PLL2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL2RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE);
}

/**
  * @brief  Disable PLL3 ready interrupt
  * @rmtoll CIER         PLL3RDYIE  LL_RCC_DisableIT_PLL3RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL3RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE);
}

/**
  * @brief  Disable LSECSS interrupt
  * @rmtoll CIER         LSECSSIE  LL_RCC_DisableIT_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSECSS(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSECSSIE);
}

/**
  * @brief  Checks if LSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSIRDYIE      LL_RCC_IsEnableIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSIRDYIE) == RCC_CIER_LSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if LSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         LSERDYIE      LL_RCC_IsEnableIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_LSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSERDYIE) == RCC_CIER_LSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSIRDYIE      LL_RCC_IsEnableIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIRDYIE) == RCC_CIER_HSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSE ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSERDYIE      LL_RCC_IsEnableIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_HSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == RCC_CIER_HSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if CSI ready interrupt source is enabled or disabled.
  * @rmtoll CIER         CSIRDYIE      LL_RCC_IsEnableIT_CSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_CSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_CSIRDYIE) == RCC_CIER_CSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSI48 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         HSI48RDYIE      LL_RCC_IsEnableIT_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE) == RCC_CIER_HSI48RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL1 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         PLL1RDYIE      LL_RCC_IsEnableIT_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_PLL1RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE) == RCC_CIER_PLL1RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL2 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         PLL2RDYIE  LL_RCC_IsEnableIT_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_PLL2RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE) == RCC_CIER_PLL2RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL3 ready interrupt source is enabled or disabled.
  * @rmtoll CIER         PLL3RDYIE  LL_RCC_IsEnableIT_PLL3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_PLL3RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE) == RCC_CIER_PLL3RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Checks if LSECSS interrupt source is enabled or disabled.
  * @rmtoll CIER         LSECSSIE  LL_RCC_IsEnableIT_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnableIT_LSECSS(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSECSSIE) == RCC_CIER_LSECSSIE) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_CALC_FREQ Calculate frequencies
  * @{
  */
/**
  * @brief  Helper function to calculate the PLL frequency output
  * @note ex: @ref LL_RCC_CalcPLLClockFreq (HSE_VALUE, @ref LL_RCC_PLL1_GetM (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetFRACN (), @ref LL_RCC_PLL1_GetP ());
  * @param  PLLInputFreq PLL Input frequency (based on HSE/(HSI/HSIDIV)/CSI)
  * @param  M      Between 1 and 63
  * @param  N      Between 4 and 512
  * @param  FRACN  Between 0 and 0x1FFF
  * @param  PQR    VCO output divider (P, Q or R)
  *                Between 1 and 128, except for PLL1P Odd value not allowed
  * @retval PLL1 clock frequency (in Hz)
  */
__STATIC_INLINE uint32_t LL_RCC_CalcPLLClockFreq(uint32_t PLLInputFreq, uint32_t M, uint32_t N, uint32_t FRACN,
                                                 uint32_t PQR)
{
  float_t freq;

  freq = ((float_t)PLLInputFreq / (float_t)M) * ((float_t)N + ((float_t)FRACN / (float_t)0x2000));

  freq = freq / (float_t)PQR;

  return (uint32_t)freq;
}
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EF_Init De-initialization function
  * @{
  */
void LL_RCC_DeInit(void);
/**
  * @}
  */

/** @defgroup RCC_LL_EF_Get_Freq Get system and peripherals clocks frequency functions
  * @{
  */
void        LL_RCC_GetPLL1ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
void        LL_RCC_GetPLL2ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
void        LL_RCC_GetPLL3ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
void        LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks);

void        LL_RCC_PLL1_ConfigSpreadSpectrum(const LL_PLL_SpreadSpectrumTypeDef *pConfig);
void        LL_RCC_PLL2_ConfigSpreadSpectrum(const LL_PLL_SpreadSpectrumTypeDef *pConfig);
void        LL_RCC_PLL3_ConfigSpreadSpectrum(const LL_PLL_SpreadSpectrumTypeDef *pConfig);

uint32_t    LL_RCC_GetADCClockFreq(uint32_t ADCxSource);
uint32_t    LL_RCC_GetADFClockFreq(uint32_t ADFxSource);
uint32_t    LL_RCC_GetCECClockFreq(uint32_t CECxSource);
uint32_t    LL_RCC_GetCLKPClockFreq(uint32_t CLKPxSource);
uint32_t    LL_RCC_GetETHPHYClockFreq(uint32_t ETHxSource);
uint32_t    LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource);
uint32_t    LL_RCC_GetFMCClockFreq(uint32_t FMCxSource);
uint32_t    LL_RCC_GetI2CClockFreq(uint32_t I2CxSource);
uint32_t    LL_RCC_GetI3CClockFreq(uint32_t I3CxSource);
uint32_t    LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource);
uint32_t    LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource);
uint32_t    LL_RCC_GetXSPIClockFreq(uint32_t XSPIxSource);
uint32_t    LL_RCC_GetPSSIClockFreq(uint32_t PSSIxSource);
uint32_t    LL_RCC_GetSAIClockFreq(uint32_t SAIxSource);
uint32_t    LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource);
uint32_t    LL_RCC_GetSPDIFRXClockFreq(uint32_t SPDIFRXxSource);
uint32_t    LL_RCC_GetSPIClockFreq(uint32_t SPIxSource);
uint32_t    LL_RCC_GetUARTClockFreq(uint32_t UARTxSource);
uint32_t    LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource);
uint32_t    LL_RCC_GetUSBPHYCClockFreq(uint32_t USBPHYCxSource);

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

#endif /* STM32H7RSxx_LL_RCC_H */
