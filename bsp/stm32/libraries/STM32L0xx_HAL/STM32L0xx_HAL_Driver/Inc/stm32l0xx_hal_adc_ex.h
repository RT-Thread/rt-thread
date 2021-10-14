/**
  ******************************************************************************
  * @file    stm32l0xx_hal_adc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of ADC HAL extended module.
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
#ifndef __STM32L0xx_HAL_ADC_EX_H
#define __STM32L0xx_HAL_ADC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Constants ADC Extended Exported Constants
  * @{
  */

/** @defgroup ADCEx_Channel_Mode ADC Single Ended
  * @{
  */
#define ADC_SINGLE_ENDED                        0x00000000U   /* dummy value */
/**
  * @}
  */

/** @defgroup ADC_regular_external_trigger_source ADC External Trigger Source
  * @{
  */
#define ADC_EXTERNALTRIGCONV_T6_TRGO            (0x00000000U)
#define ADC_EXTERNALTRIGCONV_T21_CC2            (ADC_CFGR1_EXTSEL_0)
#define ADC_EXTERNALTRIGCONV_T2_TRGO            (ADC_CFGR1_EXTSEL_1)
#define ADC_EXTERNALTRIGCONV_T2_CC4             (ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_0)
#define ADC_EXTERNALTRIGCONV_T22_TRGO           (ADC_CFGR1_EXTSEL_2)
#define ADC_EXTERNALTRIGCONV_T3_TRGO            (ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_1)
#define ADC_EXTERNALTRIGCONV_EXT_IT11           (ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_0)
#define ADC_SOFTWARE_START                      (ADC_CFGR1_EXTSEL + 1U)

/* ADC group regular external trigger TIM21_TRGO available only on            */
/* STM32L0 devices categories: Cat.2, Cat.3, Cat.5                            */
#if defined (STM32L031xx) || defined (STM32L041xx) || \
    defined (STM32L051xx) || defined (STM32L052xx) || defined (STM32L053xx) || \
    defined (STM32L062xx) || defined (STM32L063xx) || \
    defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || \
    defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx) || \
    defined (STM32L010x6) || defined (STM32L010x8) || defined (STM32L010xB)
#define ADC_EXTERNALTRIGCONV_T21_TRGO           (ADC_EXTERNALTRIGCONV_T22_TRGO)
#endif

/* ADC group regular external trigger TIM2_CC3 available only on              */
/* STM32L0 devices categories: Cat.1, Cat.2, Cat.5                            */
#if defined (STM32L011xx) || defined (STM32L021xx) || \
    defined (STM32L031xx) || defined (STM32L041xx) || \
    defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || \
    defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx) || \
    defined (STM32L010x4) || defined (STM32L010x6) || defined (STM32L010x8) || defined (STM32L010xB)
#define ADC_EXTERNALTRIGCONV_T2_CC3             (ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_0)
#endif

/**
  * @}
  */

/** @defgroup ADC_SYSCFG_internal_paths_flags_definition ADC SYSCFG internal paths Flags Definition
  * @{
  */
#define ADC_FLAG_SENSOR         SYSCFG_CFGR3_VREFINT_RDYF
#define ADC_FLAG_VREFINT        SYSCFG_VREFINT_ADC_RDYF
/**
  * @}
  */
   
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup ADCEx_Private_Macros ADCEx Private Macros
  * @{
  */

#define IS_ADC_SINGLE_DIFFERENTIAL(SING_DIFF)   ((SING_DIFF) == ADC_SINGLE_ENDED)

/** @defgroup ADCEx_calibration_factor_length_verification ADC Calibration Factor Length Verification
  * @{
  */ 
/**
  * @brief Calibration factor length verification (7 bits maximum)
  * @param _Calibration_Factor_: Calibration factor value
  * @retval None
  */
#define IS_ADC_CALFACT(_Calibration_Factor_) ((_Calibration_Factor_) <= (0x7FU))
/**
  * @}
  */ 

/** @defgroup ADC_External_trigger_Source ADC External Trigger Source
  * @{
  */
#if defined (STM32L031xx) || defined (STM32L041xx) || \
    defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || \
    defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx) || \
    defined (STM32L010x6) || defined (STM32L010x8) || defined (STM32L010xB)
#define IS_ADC_EXTTRIG(CONV) (((CONV) == ADC_EXTERNALTRIGCONV_T6_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T21_CC2  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T2_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T2_CC4   ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T22_TRGO ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T21_TRGO ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T2_CC3   ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T3_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_EXT_IT11 ) || \
                              ((CONV) == ADC_SOFTWARE_START))
#elif defined (STM32L010x4) || defined (STM32L011xx) || defined (STM32L021xx)
#define IS_ADC_EXTTRIG(CONV) (((CONV) == ADC_EXTERNALTRIGCONV_T6_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T21_CC2  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T2_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T2_CC4   ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T22_TRGO ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T2_CC3   ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T3_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_EXT_IT11 ) || \
                              ((CONV) == ADC_SOFTWARE_START))
#elif defined (STM32L051xx) || defined (STM32L052xx) || defined (STM32L053xx) || \
      defined (STM32L062xx) || defined (STM32L063xx)
#define IS_ADC_EXTTRIG(CONV) (((CONV) == ADC_EXTERNALTRIGCONV_T6_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T21_CC2  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T2_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T2_CC4   ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T22_TRGO ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T21_TRGO ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_T3_TRGO  ) || \
                              ((CONV) == ADC_EXTERNALTRIGCONV_EXT_IT11 ) || \
                              ((CONV) == ADC_SOFTWARE_START))
#endif
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADCEx_Exported_Functions
  * @{
  */

/** @addtogroup ADCEx_Exported_Functions_Group1
  * @{
  */
/* IO operation functions *****************************************************/

/* ADC calibration */
HAL_StatusTypeDef   HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc, uint32_t SingleDiff);
uint32_t            HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef* hadc, uint32_t SingleDiff);
HAL_StatusTypeDef   HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef* hadc, uint32_t SingleDiff, uint32_t CalibrationFactor);

/* ADC VrefInt and Temperature sensor functions specific to this STM32 serie */
HAL_StatusTypeDef   HAL_ADCEx_EnableVREFINT(void);
void                HAL_ADCEx_DisableVREFINT(void);
HAL_StatusTypeDef   HAL_ADCEx_EnableVREFINTTempSensor(void);
void                HAL_ADCEx_DisableVREFINTTempSensor(void);
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

#endif /*__STM32L0xx_HAL_ADC_EX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
