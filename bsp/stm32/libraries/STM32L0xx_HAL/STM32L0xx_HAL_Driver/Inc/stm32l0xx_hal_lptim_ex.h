/**
  ******************************************************************************
  * @file    stm32l0xx_hal_lptim_ex.h
  * @author  MCD Application Team
  * @brief   Header file of LPTIM Extended HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) 2016 STMicroelectronics.
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
#ifndef __STM32L0xx_HAL_LPTIM_EX_H
#define __STM32L0xx_HAL_LPTIM_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup LPTIMEx LPTIMEx
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup LPTIMEx_Exported_Constants LPTIMEx Exported Constants
  * @{
  */


/** @defgroup LPTIMEx_Trigger_Source LPTIMEx Trigger source
  * @{
  */
#define LPTIM_TRIGSOURCE_SOFTWARE               0x0000FFFFU                                    /*!< LPTIM counter triggered by software*/
#define LPTIM_TRIGSOURCE_0                      0x00000000U                                    /*!< LPTIM counter triggered by GPIO (alternate function LPTIM_ETR) */
#define LPTIM_TRIGSOURCE_1                      LPTIM_CFGR_TRIGSEL_0                           /*!< LPTIM counter triggered by RTC alarm A */
#define LPTIM_TRIGSOURCE_2                      LPTIM_CFGR_TRIGSEL_1                           /*!< LPTIM counter triggered by RTC alarm B */
#define LPTIM_TRIGSOURCE_3                      (LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_1)  /*!< LPTIM counter triggered by RTC_TAMP1 input detection */
#define LPTIM_TRIGSOURCE_4                      LPTIM_CFGR_TRIGSEL_2                           /*!< LPTIM counter triggered by RTC_TAMP2 input detection */
#if defined(RTC_TAMPER3_SUPPORT)
#define LPTIM_TRIGSOURCE_5                      (LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_2)  /*!< LPTIM counter triggered by RTC_TAMP3 input detection */
#endif /* RTC_TAMPER3_SUPPORT */
#if defined(COMP1) && defined(COMP2)
#define LPTIM_TRIGSOURCE_6                      (LPTIM_CFGR_TRIGSEL_1 | LPTIM_CFGR_TRIGSEL_2)  /*!< LPTIM counter triggered by COMP1_OUT */
#define LPTIM_TRIGSOURCE_7                      LPTIM_CFGR_TRIGSEL                             /*!< LPTIM counter triggered by COMP2_OUT */
#endif /* COMP1 && COMP2 */
/**
  * @}
  */

 /**
  * @}
  */

   /** @addtogroup LPTIMEx_Private
  * @{
  */
#if defined(RTC_TAMPER3_SUPPORT) && defined(COMP1) && defined(COMP2)
#define IS_LPTIM_TRG_SOURCE(__TRIG__)           (((__TRIG__) == LPTIM_TRIGSOURCE_SOFTWARE) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_0) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_1) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_2) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_3) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_4) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_5) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_6) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_7))
#elif defined(RTC_TAMPER3_SUPPORT)
#define IS_LPTIM_TRG_SOURCE(__TRIG__)           (((__TRIG__) == LPTIM_TRIGSOURCE_SOFTWARE) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_0) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_1) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_2) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_3) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_4) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_5))
#else
#define IS_LPTIM_TRG_SOURCE(__TRIG__)           (((__TRIG__) == LPTIM_TRIGSOURCE_SOFTWARE) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_0) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_1) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_2) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_3) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_4) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_6) || \
                                                 ((__TRIG__) == LPTIM_TRIGSOURCE_7))
#endif /* RTC_TAMPER3_SUPPORT && COMP1 && COMP2 */
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

#endif /* __STM32L0xx_HAL_LPTIM_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

