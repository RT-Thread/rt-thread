/**
  ******************************************************************************
  * @file    stm32u5xx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef __STM32U5xx_HAL_H
#define __STM32U5xx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_conf.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HAL_Exported_Types HAL Exported Types
  * @{
  */

/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/
/** @defgroup HAL_Exported_Variables HAL Exported Variables
  * @{
  */
extern __IO uint32_t            uwTick;
extern uint32_t                 uwTickPrio;
extern HAL_TickFreqTypeDef      uwTickFreq;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup REV_ID device revision ID
  * @{
  */
#define REV_ID_A 0x1000U  /*!< STM32U5 rev.A */
#define REV_ID_B 0x2000U  /*!< STM32U5 rev.B */
/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_FPU_Interrupts FPU Interrupts
  * @{
  */
#define SYSCFG_IT_FPU_IOC              SYSCFG_FPUIMR_FPU_IE_0  /*!< Floating Point Unit Invalid operation Interrupt */
#define SYSCFG_IT_FPU_DZC              SYSCFG_FPUIMR_FPU_IE_1  /*!< Floating Point Unit Divide-by-zero Interrupt */
#define SYSCFG_IT_FPU_UFC              SYSCFG_FPUIMR_FPU_IE_2  /*!< Floating Point Unit Underflow Interrupt */
#define SYSCFG_IT_FPU_OFC              SYSCFG_FPUIMR_FPU_IE_3  /*!< Floating Point Unit Overflow Interrupt */
#define SYSCFG_IT_FPU_IDC              SYSCFG_FPUIMR_FPU_IE_4  /*!< Floating Point Unit Input denormal Interrupt */
#define SYSCFG_IT_FPU_IXC              SYSCFG_FPUIMR_FPU_IE_5  /*!< Floating Point Unit Inexact Interrupt */

/**
  * @}
  */

/** @defgroup SYSCFG_VREFBUF_VoltageScale VREFBUF Voltage Scale
  * @{
  */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE0  ((uint32_t)0x00000000)                  /*!< Voltage reference scale 0 (VREF_OUT1) */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE1  VREFBUF_CSR_VRS_0                       /*!< Voltage reference scale 1 (VREF_OUT2) */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE2  VREFBUF_CSR_VRS_1                       /*!< Voltage reference scale 2 (VREF_OUT3) */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE3  (VREFBUF_CSR_VRS_0 | VREFBUF_CSR_VRS_1) /*!< Voltage reference scale 3 (VREF_OUT4) */

/**
  * @}
  */

/** @defgroup SYSCFG_VREFBUF_HighImpedance VREFBUF High Impedance
  * @{
  */
#define SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE  ((uint32_t)0x00000000) /*!< VREF_plus pin is internally connected to
                                                                           Voltage reference buffer output */
#define SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE   VREFBUF_CSR_HIZ        /*!< VREF_plus pin is high impedance */

/**
  * @}
  */

/** @defgroup SYSCFG_flags_definition Flags
  * @{
  */

#define SYSCFG_FLAG_SRAM2_PE            SYSCFG_CFGR2_SPF       /*!< SRAM2 parity error */
#define SYSCFG_FLAG_SRAM2_BUSY          SYSCFG_SCSR_SRAM2BSY   /*!< SRAM2 busy by erase operation */

/**
  * @}
  */

/** @defgroup SYSCFG_FastModePlus_GPIO Fast-mode Plus on GPIO
  * @{
  */

/** @brief  Fast-mode Plus driving capability on a specific GPIO
  */
#define SYSCFG_FASTMODEPLUS_PB6        SYSCFG_CFGR1_PB6_FMP  /*!< Enable Fast-mode Plus on PB6 */
#define SYSCFG_FASTMODEPLUS_PB7        SYSCFG_CFGR1_PB7_FMP  /*!< Enable Fast-mode Plus on PB7 */
#define SYSCFG_FASTMODEPLUS_PB8        SYSCFG_CFGR1_PB8_FMP  /*!< Enable Fast-mode Plus on PB8 */
#define SYSCFG_FASTMODEPLUS_PB9        SYSCFG_CFGR1_PB9_FMP  /*!< Enable Fast-mode Plus on PB9 */

/**
  * @}
  */

/** @defgroup SYSCFG_Lock_items SYSCFG Lock items
  * @brief SYSCFG items to set lock on
  * @{
  */
#define SYSCFG_MPU_NSEC                SYSCFG_CNSLCKR_LOCKNSMPU            /*!< Non-secure MPU lock (privileged secure or non-secure only) */
#define SYSCFG_VTOR_NSEC               SYSCFG_CNSLCKR_LOCKNSVTOR           /*!< Non-secure VTOR lock (privileged secure or non-secure only) */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define SYSCFG_SAU                     (SYSCFG_CSLCKR_LOCKSAU << 16U)      /*!< SAU lock (privileged secure code only) */
#define SYSCFG_MPU_SEC                 (SYSCFG_CSLCKR_LOCKSMPU << 16U)     /*!< Secure MPU lock (privileged secure code only) */
#define SYSCFG_VTOR_AIRCR_SEC          (SYSCFG_CSLCKR_LOCKSVTAIRCR << 16U) /*!< VTOR_S and AIRCR lock (privileged secure code only) */
#define SYSCFG_LOCK_ALL                (SYSCFG_MPU_NSEC|SYSCFG_VTOR_NSEC|SYSCFG_SAU|SYSCFG_MPU_SEC|SYSCFG_VTOR_AIRCR_SEC)  /*!< All */
#else
#define SYSCFG_LOCK_ALL                (SYSCFG_MPU_NSEC|SYSCFG_VTOR_NSEC)  /*!< All (privileged secure or non-secure only) */
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @defgroup SYSCFG_Attributes_items SYSCFG Attributes items
  * @brief SYSCFG items to configure secure or non-secure attributes on
  * @{
  */
#define SYSCFG_CLK                     SYSCFG_SECCFGR_SYSCFGSEC   /*!< SYSCFG clock control */
#define SYSCFG_CLASSB                  SYSCFG_SECCFGR_CLASSBSEC   /*!< Class B */
#define SYSCFG_FPU                     SYSCFG_SECCFGR_FPUSEC      /*!< FPU */
#define SYSCFG_ALL                     (SYSCFG_CLK | SYSCFG_CLASSB | SYSCFG_FPU) /*!< All */
/**
  * @}
  */

/** @defgroup SYSCFG_attributes SYSCFG attributes
  * @brief SYSCFG secure or non-secure attributes
  * @{
  */
#define SYSCFG_SEC                     0x00000001U   /*!< Secure attribute      */
#define SYSCFG_NSEC                    0x00000000U   /*!< Non-secure attribute  */
/**
  * @}
  */

#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup DBGMCU_Exported_Macros DBGMCU Exported Macros
  * @{
  */

/** @brief  Freeze/Unfreeze Peripherals in Debug mode
  */
#if defined(DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#define __HAL_DBGMCU_FREEZE_TIM2()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM2()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM2_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_FREEZE_TIM3()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM3()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM3_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#define __HAL_DBGMCU_FREEZE_TIM4()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM4()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM4_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM5_STOP)
#define __HAL_DBGMCU_FREEZE_TIM5()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM5_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM5()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM5_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM5_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#define __HAL_DBGMCU_FREEZE_TIM6()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM6()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM6_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#define __HAL_DBGMCU_FREEZE_TIM7()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM7()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM7_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_FREEZE_WWDG()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_WWDG()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_WWDG_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_FREEZE_IWDG()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_IWDG()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_IWDG_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#define __HAL_DBGMCU_FREEZE_I2C1()              SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C1()            CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_I2C1_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#define __HAL_DBGMCU_FREEZE_I2C2()              SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C2()            CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_I2C2_STOP */

#if defined(DBGMCU_APB1FZR2_DBG_I2C4_STOP)
#define __HAL_DBGMCU_FREEZE_I2C4()              SET_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_I2C4_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C4()            CLEAR_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_I2C4_STOP)
#endif /* DBGMCU_APB1FZR2_DBG_I2C4_STOP */

#if defined(DBGMCU_APB1FZR2_DBG_LPTIM2_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM2()            SET_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_LPTIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM2()          CLEAR_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_LPTIM2_STOP)
#endif /* DBGMCU_APB1FZR2_DBG_LPTIM2_STOP */

#if defined(DBGMCU_APB1FZR2_DBG_FDCAN_STOP)
#define __HAL_DBGMCU_FREEZE_FDCAN()             SET_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_FDCAN_STOP)
#define __HAL_DBGMCU_UNFREEZE_FDCAN()           CLEAR_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_FDCAN_STOP)
#endif /* DBGMCU_APB1FZR2_DBG_FDCAN_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM1_STOP)
#define __HAL_DBGMCU_FREEZE_TIM1()              SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM1()            CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM1_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM1_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM8_STOP)
#define __HAL_DBGMCU_FREEZE_TIM8()              SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM8_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM8()            CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM8_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM8_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM15_STOP)
#define __HAL_DBGMCU_FREEZE_TIM15()             SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM15_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM15()           CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM15_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM15_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM16_STOP)
#define __HAL_DBGMCU_FREEZE_TIM16()             SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM16_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM16()           CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM16_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM16_STOP */

#if defined(DBGMCU_APB2FZR_DBG_TIM17_STOP)
#define __HAL_DBGMCU_FREEZE_TIM17()             SET_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM17_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM17()           CLEAR_BIT(DBGMCU->APB2FZR, DBGMCU_APB2FZR_DBG_TIM17_STOP)
#endif /* DBGMCU_APB2FZR_DBG_TIM17_STOP */

#if defined(DBGMCU_APB3FZR_DBG_I2C3_STOP)
#define __HAL_DBGMCU_FREEZE_I2C3()              SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_I2C3_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C3()            CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_I2C3_STOP)
#endif /* DBGMCU_APB3FZR_DBG_I2C3_STOP */

#if defined(DBGMCU_APB3FZR_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM1()            SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM1()          CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM1_STOP)
#endif /* DBGMCU_APB3FZR_DBG_LPTIM1_STOP */

#if defined(DBGMCU_APB3FZR_DBG_LPTIM3_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM3()            SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM3()          CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM3_STOP)
#endif /* DBGMCU_APB3FZR_DBG_LPTIM3_STOP */

#if defined(DBGMCU_APB3FZR_DBG_LPTIM4_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM4()            SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM4_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM4()          CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_LPTIM4_STOP)
#endif /* DBGMCU_APB3FZR_DBG_LPTIM4_STOP */

#if defined(DBGMCU_APB3FZR_DBG_RTC_STOP)
#define __HAL_DBGMCU_FREEZE_RTC()               SET_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_RTC_STOP)
#define __HAL_DBGMCU_UNFREEZE_RTC()             CLEAR_BIT(DBGMCU->APB3FZR, DBGMCU_APB3FZR_DBG_RTC_STOP)
#endif /* DBGMCU_APB3FZR_DBG_RTC_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA0_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA0()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA0_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA0()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA0_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA0_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA1_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA1()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA1()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA1_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA1_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA2_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA2()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA2_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA2()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA2_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA2_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA3_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA3()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA3_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA3()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA3_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA3_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA4_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA4()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA4_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA4()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA4_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA4_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA5_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA5()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA5_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA5()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA5_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA5_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA6_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA6()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA6_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA6()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA6_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA6_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA7_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA7()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA7_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA7()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA7_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA7_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA8_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA8()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA8_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA8()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA8_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA8_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA9_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA9()            SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA9_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA9()          CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA9_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA9_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA10_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA10()           SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA10_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA10()         CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA10_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA10_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA11_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA11()           SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA11_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA11()         CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA11_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA11_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA12_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA12()           SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA12_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA12()         CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA12_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA12_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA13_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA13()           SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA13_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA13()         CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA13_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA13_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA14_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA14()           SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA14_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA14()         CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA14_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA14_STOP */

#if defined(DBGMCU_AHB1FZR_DBG_GPDMA15_STOP)
#define __HAL_DBGMCU_FREEZE_GPDMA15()           SET_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA15_STOP)
#define __HAL_DBGMCU_UNFREEZE_GPDMA15()         CLEAR_BIT(DBGMCU->AHB1FZR, DBGMCU_AHB1FZR_DBG_GPDMA15_STOP)
#endif /* DBGMCU_AHB1FZR_DBG_GPDMA15_STOP */

#if defined(DBGMCU_AHB3FZR_DBG_LPDMA0_STOP)
#define __HAL_DBGMCU_FREEZE_LPDMA0()            SET_BIT(DBGMCU->AHB3FZR, DBGMCU_AHB3FZR_DBG_LPDMA0_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPDMA0()          CLEAR_BIT(DBGMCU->AHB3FZR, DBGMCU_AHB3FZR_DBG_LPDMA0_STOP)
#endif /* DBGMCU_AHB3FZR_DBG_LPDMA0_STOP */

#if defined(DBGMCU_AHB3FZR_DBG_LPDMA1_STOP)
#define __HAL_DBGMCU_FREEZE_LPDMA1()            SET_BIT(DBGMCU->AHB3FZR, DBGMCU_AHB3FZR_DBG_LPDMA1_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPDMA1()          CLEAR_BIT(DBGMCU->AHB3FZR, DBGMCU_AHB3FZR_DBG_LPDMA1_STOP)
#endif /* DBGMCU_AHB3FZR_DBG_LPDMA1_STOP */

#if defined(DBGMCU_AHB3FZR_DBG_LPDMA2_STOP)
#define __HAL_DBGMCU_FREEZE_LPDMA2()            SET_BIT(DBGMCU->AHB3FZR, DBGMCU_AHB3FZR_DBG_LPDMA2_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPDMA2()          CLEAR_BIT(DBGMCU->AHB3FZR, DBGMCU_AHB3FZR_DBG_LPDMA2_STOP)
#endif /* DBGMCU_AHB3FZR_DBG_LPDMA2_STOP */

#if defined(DBGMCU_AHB3FZR_DBG_LPDMA3_STOP)
#define __HAL_DBGMCU_FREEZE_LPDMA3()            SET_BIT(DBGMCU->AHB3FZR, DBGMCU_AHB3FZR_DBG_LPDMA3_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPDMA3()          CLEAR_BIT(DBGMCU->AHB3FZR, DBGMCU_AHB3FZR_DBG_LPDMA3_STOP)
#endif /* DBGMCU_AHB3FZR_DBG_LPDMA3_STOP */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/** @brief  Floating Point Unit interrupt enable/disable macros
  * @param __INTERRUPT__: This parameter can be a value of @ref SYSCFG_FPU_Interrupts
  */
#define __HAL_SYSCFG_FPU_INTERRUPT_ENABLE(__INTERRUPT__)    do {assert_param(IS_SYSCFG_FPU_INTERRUPT((__INTERRUPT__)));\
                                                                 SET_BIT(SYSCFG->FPUIMR, (__INTERRUPT__));\
                                                               }while(0)

#define __HAL_SYSCFG_FPU_INTERRUPT_DISABLE(__INTERRUPT__)   do {assert_param(IS_SYSCFG_FPU_INTERRUPT((__INTERRUPT__)));\
                                                                 CLEAR_BIT(SYSCFG->FPUIMR, (__INTERRUPT__));\
                                                               }while(0)

/** @brief  SYSCFG Break ECC lock.
  *         Enable and lock the connection of Flash ECC error connection to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_ECC_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_ECCL)

/** @brief  SYSCFG Break Cortex-M33 Lockup lock.
  *         Enable and lock the connection of Cortex-M33 LOCKUP (Hardfault) output to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_LOCKUP_LOCK()     SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL)

/** @brief  SYSCFG Break PVD lock.
  *         Enable and lock the PVD connection to Timer1/8/15/16/17 Break input, as well as the PVDE and PLS[2:0] in
  *         the PWR_CR2 register.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_PVD_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_PVDL)

/** @brief  SYSCFG Break SRAM2 parity lock.
  *         Enable and lock the SRAM2 parity error signal connection to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked by system reset.
  */
#define __HAL_SYSCFG_BREAK_SRAM2PARITY_LOCK()  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPL)

/** @brief  Check SYSCFG flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref SYSCFG_FLAG_SRAM2_PE   SRAM2 Parity Error Flag
  *            @arg @ref SYSCFG_FLAG_SRAM2_BUSY SRAM2 Erase Ongoing
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SYSCFG_GET_FLAG(__FLAG__)      ((((((__FLAG__) == SYSCFG_SCSR_SRAM2BSY)? SYSCFG->SCSR : SYSCFG->CFGR2)\
                                                & (__FLAG__))!= 0) ? 1 : 0)

/** @brief  Set the SPF bit to clear the SRAM Parity Error Flag.
  */
#define __HAL_SYSCFG_CLEAR_FLAG()            SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPF)

/** @brief  Fast-mode Plus driving capability enable/disable macros
  * @param __FASTMODEPLUS__: This parameter can be a value of :
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB6 Fast-mode Plus driving capability activation on PB6
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB7 Fast-mode Plus driving capability activation on PB7
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB8 Fast-mode Plus driving capability activation on PB8
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB9 Fast-mode Plus driving capability activation on PB9
  */
#define __HAL_SYSCFG_FASTMODEPLUS_ENABLE(__FASTMODEPLUS__) \
  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
    SET_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
  }while(0)

#define __HAL_SYSCFG_FASTMODEPLUS_DISABLE(__FASTMODEPLUS__) \
  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
    CLEAR_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
  }while(0)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */

#define IS_SYSCFG_FPU_INTERRUPT(__INTERRUPT__) ((((__INTERRUPT__) & SYSCFG_IT_FPU_IOC) == SYSCFG_IT_FPU_IOC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_DZC) == SYSCFG_IT_FPU_DZC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_UFC) == SYSCFG_IT_FPU_UFC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_OFC) == SYSCFG_IT_FPU_OFC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_IDC) == SYSCFG_IT_FPU_IDC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_IXC) == SYSCFG_IT_FPU_IXC))

#define IS_SYSCFG_BREAK_CONFIG(__CONFIG__) (((__CONFIG__) == SYSCFG_BREAK_ECC)           || \
                                            ((__CONFIG__) == SYSCFG_BREAK_PVD)           || \
                                            ((__CONFIG__) == SYSCFG_BREAK_SRAM2_PARITY)  || \
                                            ((__CONFIG__) == SYSCFG_BREAK_LOCKUP))

#define IS_SYSCFG_VREFBUF_VOLTAGE_SCALE(__SCALE__)  (((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE0) || \
                                                     ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE1) || \
                                                     ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE2) || \
                                                     ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE3))

#define IS_SYSCFG_VREFBUF_HIGH_IMPEDANCE(__VALUE__)  (((__VALUE__) == SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE) || \
                                                      ((__VALUE__) == SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE))

#define IS_SYSCFG_VREFBUF_TRIMMING(__VALUE__)  (((__VALUE__) > 0U) && ((__VALUE__) <= VREFBUF_CCR_TRIM))

#define IS_SYSCFG_FASTMODEPLUS(__PIN__) ((((__PIN__) & SYSCFG_FASTMODEPLUS_PB6) == SYSCFG_FASTMODEPLUS_PB6) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7) == SYSCFG_FASTMODEPLUS_PB7) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB8) == SYSCFG_FASTMODEPLUS_PB8) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB9) == SYSCFG_FASTMODEPLUS_PB9))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

#define IS_SYSCFG_ATTRIBUTES(__ATTRIBUTES__) (((__ATTRIBUTES__) == SYSCFG_SEC)  ||\
                                              ((__ATTRIBUTES__) == SYSCFG_NSEC))

#define IS_SYSCFG_ITEMS_ATTRIBUTES(__ITEM__) ((((__ITEM__) & SYSCFG_CLK)    == SYSCFG_CLK)    || \
                                              (((__ITEM__) & SYSCFG_CLASSB) == SYSCFG_CLASSB) || \
                                              (((__ITEM__) & SYSCFG_FPU)    == SYSCFG_FPU)    || \
                                              (((__ITEM__) & ~(SYSCFG_ALL)) == 0U))

#define IS_SYSCFG_LOCK_ITEMS(__ITEM__) ((((__ITEM__) & SYSCFG_MPU_NSEC)       == SYSCFG_MPU_NSEC)       || \
                                        (((__ITEM__) & SYSCFG_VTOR_NSEC)      == SYSCFG_VTOR_NSEC)      || \
                                        (((__ITEM__) & SYSCFG_SAU)            == SYSCFG_SAU)            || \
                                        (((__ITEM__) & SYSCFG_MPU_SEC)        == SYSCFG_MPU_SEC)        || \
                                        (((__ITEM__) & SYSCFG_VTOR_AIRCR_SEC) == SYSCFG_VTOR_AIRCR_SEC) || \
                                        (((__ITEM__) & ~(SYSCFG_LOCK_ALL)) == 0U))

#else

#define IS_SYSCFG_LOCK_ITEMS(__ITEM__) ((((__ITEM__) & SYSCFG_MPU_NSEC)  == SYSCFG_MPU_NSEC)    || \
                                        (((__ITEM__) & SYSCFG_VTOR_NSEC) == SYSCFG_VTOR_NSEC)   || \
                                        (((__ITEM__) & ~(SYSCFG_LOCK_ALL)) == 0U))


#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group3
  * @{
  */

/* DBGMCU Peripheral Control functions  *****************************************/
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4
  * @{
  */

/* SYSCFG Control functions  ****************************************************/
void HAL_SYSCFG_SRAM2Erase(void);

void HAL_SYSCFG_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling);
void HAL_SYSCFG_VREFBUF_HighImpedanceConfig(uint32_t Mode);
void HAL_SYSCFG_VREFBUF_TrimmingConfig(uint32_t TrimmingValue);
HAL_StatusTypeDef HAL_SYSCFG_EnableVREFBUF(void);
void HAL_SYSCFG_DisableVREFBUF(void);

void HAL_SYSCFG_EnableIOAnalogSwitchBooster(void);
void HAL_SYSCFG_DisableIOAnalogSwitchBooster(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group5
  * @{
  */

/* SYSCFG Lock functions ********************************************/
void              HAL_SYSCFG_Lock(uint32_t Item);
HAL_StatusTypeDef HAL_SYSCFG_GetLock(uint32_t *pItem);

/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @addtogroup HAL_Exported_Functions_Group6
  * @{
  */

/* SYSCFG Attributes functions ********************************************/
void              HAL_SYSCFG_ConfigAttributes(uint32_t Item, uint32_t Attributes);
HAL_StatusTypeDef HAL_SYSCFG_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes);

/**
  * @}
  */

#endif /* __ARM_FEATURE_CMSE */

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

#endif /* __STM32U5xx_HAL_H */
