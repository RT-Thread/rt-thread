/**
  ******************************************************************************
  * @file    stm32f0xx_hal_adc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of ADC HAL Extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
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
#ifndef __STM32F0xx_HAL_ADC_EX_H
#define __STM32F0xx_HAL_ADC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"  

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC)
#define ADC_CCR_ALL     (ADC_CCR_VBATEN | ADC_CCR_TSEN | ADC_CCR_VREFEN)
#else
#define ADC_CCR_ALL     (ADC_CCR_TSEN | ADC_CCR_VREFEN)
#endif

/** @defgroup ADC_External_trigger_source_Regular ADC External trigger source Regular
  * @{
  */
/* List of external triggers with generic trigger name, sorted by trigger     */
/* name:                                                                      */

/* External triggers of regular group for ADC1 */
#define ADC_EXTERNALTRIGCONV_T1_TRGO        ADC1_2_EXTERNALTRIG_T1_TRGO
#define ADC_EXTERNALTRIGCONV_T1_CC4         ADC1_2_EXTERNALTRIG_T1_CC4
#define ADC_EXTERNALTRIGCONV_T3_TRGO        ADC1_2_EXTERNALTRIG_T3_TRGO
#define ADC_SOFTWARE_START                  (ADC_CFGR1_EXTSEL + 1U)

#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC)
#define ADC_EXTERNALTRIGCONV_T2_TRGO        ADC1_2_EXTERNALTRIG_T2_TRGO
#endif 

#if !defined(STM32F030x6) && !defined(STM32F070x6) && !defined(STM32F042x6)
#define ADC_EXTERNALTRIGCONV_T15_TRGO       ADC1_2_EXTERNALTRIG_T15_TRGO
#endif

/**
  * @}
  */ 


/** @defgroup ADC_channels ADC channels
  * @{
  */
/* Note: Depending on devices, some channels may not be available on package  */
/*       pins. Refer to device datasheet for channels availability.           */
/* Note: Channels are used by bitfields for setting of channel selection      */
/*       (register ADC_CHSELR) and used by number for setting of analog       */
/*       watchdog channel (bits AWDCH in register ADC_CFGR1).                 */
/*       Channels are defined with decimal numbers and converted them to      */
/*       bitfields when needed.                                               */
#define ADC_CHANNEL_0           ( 0x00000000U)
#define ADC_CHANNEL_1           ( 0x00000001U)
#define ADC_CHANNEL_2           ( 0x00000002U)
#define ADC_CHANNEL_3           ( 0x00000003U)
#define ADC_CHANNEL_4           ( 0x00000004U)
#define ADC_CHANNEL_5           ( 0x00000005U)
#define ADC_CHANNEL_6           ( 0x00000006U)
#define ADC_CHANNEL_7           ( 0x00000007U)
#define ADC_CHANNEL_8           ( 0x00000008U)
#define ADC_CHANNEL_9           ( 0x00000009U)
#define ADC_CHANNEL_10          ( 0x0000000AU)
#define ADC_CHANNEL_11          ( 0x0000000BU)
#define ADC_CHANNEL_12          ( 0x0000000CU)
#define ADC_CHANNEL_13          ( 0x0000000DU)
#define ADC_CHANNEL_14          ( 0x0000000EU)
#define ADC_CHANNEL_15          ( 0x0000000FU)
#define ADC_CHANNEL_16          ( 0x00000010U)
#define ADC_CHANNEL_17          ( 0x00000011U)

#define ADC_CHANNEL_TEMPSENSOR  ADC_CHANNEL_16
#define ADC_CHANNEL_VREFINT     ADC_CHANNEL_17
    
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC)
#define ADC_CHANNEL_18          ( 0x00000012U)
#define ADC_CHANNEL_VBAT        ADC_CHANNEL_18 
#endif
    
/**
  * @}
  */

/**
  * @}
  */
    
/* Exported macro ------------------------------------------------------------*/


/* Private macros ------------------------------------------------------------*/

/** @defgroup ADCEx_Private_Macros ADCEx Private Macros
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/**
  * @brief Test if the selected ADC channel is an internal channel
  *        VrefInt/TempSensor/Vbat
  *        Note: On STM32F0, availability of internal channel Vbat depends on
  *              devices lines.
  * @param __CHANNEL__ ADC channel
  * @retval None
  */
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC)
#define ADC_IS_CHANNEL_INTERNAL(__CHANNEL__)                                   \
 (((__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR) ||                                 \
  ((__CHANNEL__) == ADC_CHANNEL_VREFINT)    ||                                 \
  ((__CHANNEL__) == ADC_CHANNEL_VBAT)                                          \
 )
#else
#define ADC_IS_CHANNEL_INTERNAL(__CHANNEL__)                                   \
 (((__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR) ||                                 \
  ((__CHANNEL__) == ADC_CHANNEL_VREFINT)                                       \
 )
#endif
   
/**
  * @brief Select the internal measurement path to be enabled/disabled 
  *        corresponding to the selected ADC internal channel 
  *        VrefInt/TempSensor/Vbat.
  *        Note: On STM32F0, availability of internal channel Vbat depends on
  *              devices lines.
  * @param __CHANNEL__ ADC channel
  * @retval Bit of register ADC_CCR
  */
#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC)
#define ADC_CHANNEL_INTERNAL_PATH(__CHANNEL__)                                 \
 (( (__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR                                    \
  )?                                                                           \
   (ADC_CCR_TSEN)                                                              \
   :                                                                           \
   (                                                                           \
     ( (__CHANNEL__) == ADC_CHANNEL_VREFINT                                    \
     )?                                                                        \
      (ADC_CCR_VREFEN)                                                         \
      :                                                                        \
      (ADC_CCR_VBATEN)                                                         \
   )                                                                           \
 )
#else
#define ADC_CHANNEL_INTERNAL_PATH(__CHANNEL__)                                 \
 (( (__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR                                    \
  )?                                                                           \
   (ADC_CCR_TSEN)                                                              \
   :                                                                           \
   (ADC_CCR_VREFEN)                                                            \
 )
#endif
   
   
#if defined (STM32F030x6) || defined (STM32F070x6)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_SOFTWARE_START))
#elif defined (STM32F042x6)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_SOFTWARE_START))   

#elif defined (STM32F030xC) || defined (STM32F070xB) || defined (STM32F030x8)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO) || \
                                 ((REGTRIG) == ADC_SOFTWARE_START))
#else
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO) || \
                                 ((REGTRIG) == ADC_SOFTWARE_START))   
#endif

#if !defined(STM32F030x6) && !defined(STM32F030x8) && !defined(STM32F070x6) && !defined(STM32F070xB) && !defined(STM32F030xC)
#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_0)           || \
                                 ((CHANNEL) == ADC_CHANNEL_1)           || \
                                 ((CHANNEL) == ADC_CHANNEL_2)           || \
                                 ((CHANNEL) == ADC_CHANNEL_3)           || \
                                 ((CHANNEL) == ADC_CHANNEL_4)           || \
                                 ((CHANNEL) == ADC_CHANNEL_5)           || \
                                 ((CHANNEL) == ADC_CHANNEL_6)           || \
                                 ((CHANNEL) == ADC_CHANNEL_7)           || \
                                 ((CHANNEL) == ADC_CHANNEL_8)           || \
                                 ((CHANNEL) == ADC_CHANNEL_9)           || \
                                 ((CHANNEL) == ADC_CHANNEL_10)          || \
                                 ((CHANNEL) == ADC_CHANNEL_11)          || \
                                 ((CHANNEL) == ADC_CHANNEL_12)          || \
                                 ((CHANNEL) == ADC_CHANNEL_13)          || \
                                 ((CHANNEL) == ADC_CHANNEL_14)          || \
                                 ((CHANNEL) == ADC_CHANNEL_15)          || \
                                 ((CHANNEL) == ADC_CHANNEL_TEMPSENSOR)  || \
                                 ((CHANNEL) == ADC_CHANNEL_VREFINT)     || \
                                 ((CHANNEL) == ADC_CHANNEL_VBAT)          )
#else
#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_0)           || \
                                 ((CHANNEL) == ADC_CHANNEL_1)           || \
                                 ((CHANNEL) == ADC_CHANNEL_2)           || \
                                 ((CHANNEL) == ADC_CHANNEL_3)           || \
                                 ((CHANNEL) == ADC_CHANNEL_4)           || \
                                 ((CHANNEL) == ADC_CHANNEL_5)           || \
                                 ((CHANNEL) == ADC_CHANNEL_6)           || \
                                 ((CHANNEL) == ADC_CHANNEL_7)           || \
                                 ((CHANNEL) == ADC_CHANNEL_8)           || \
                                 ((CHANNEL) == ADC_CHANNEL_9)           || \
                                 ((CHANNEL) == ADC_CHANNEL_10)          || \
                                 ((CHANNEL) == ADC_CHANNEL_11)          || \
                                 ((CHANNEL) == ADC_CHANNEL_12)          || \
                                 ((CHANNEL) == ADC_CHANNEL_13)          || \
                                 ((CHANNEL) == ADC_CHANNEL_14)          || \
                                 ((CHANNEL) == ADC_CHANNEL_15)          || \
                                 ((CHANNEL) == ADC_CHANNEL_TEMPSENSOR)  || \
                                 ((CHANNEL) == ADC_CHANNEL_VREFINT)       )
#endif

/**
  * @}
  */ 

   
/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADCEx_Exported_Functions
  * @{
  */

/* IO operation functions  *****************************************************/
/** @addtogroup ADCEx_Exported_Functions_Group1
  * @{
  */

/* ADC calibration */
HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc);
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

#endif /* __STM32F0xx_HAL_ADC_EX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

