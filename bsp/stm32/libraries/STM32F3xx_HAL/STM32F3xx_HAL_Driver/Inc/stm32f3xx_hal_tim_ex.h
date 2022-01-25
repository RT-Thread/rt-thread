/**
  ******************************************************************************
  * @file    stm32f3xx_hal_tim_ex.h
  * @author  MCD Application Team
  * @brief   Header file of TIM HAL Extended module.
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
#ifndef STM32F3xx_HAL_TIM_EX_H
#define STM32F3xx_HAL_TIM_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup TIMEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Types TIM Extended Exported Types
  * @{
  */

/**
  * @brief  TIM Hall sensor Configuration Structure definition
  */

typedef struct
{
  uint32_t IC1Polarity;         /*!< Specifies the active edge of the input signal.
                                     This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t IC1Prescaler;        /*!< Specifies the Input Capture Prescaler.
                                     This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t IC1Filter;           /*!< Specifies the input capture filter.
                                     This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */

  uint32_t Commutation_Delay;   /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                     This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */
} TIM_HallSensor_InitTypeDef;
/**
  * @}
  */
/* End of exported types -----------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Constants TIM Extended Exported Constants
  * @{
  */

/** @defgroup TIMEx_Remap TIM Extended Remapping
  * @{
  */
#if defined(TIM1)
#define TIM_TIM1_ADC1_NONE                     (0x00000000U) /*!< TIM1_ETR is not connected to any AWD (analog watchdog)*/
#define TIM_TIM1_ADC1_AWD1                     (0x00000001U) /*!< TIM1_ETR is connected to ADC1 AWD1 */
#define TIM_TIM1_ADC1_AWD2                     (0x00000002U) /*!< TIM1_ETR is connected to ADC1 AWD2 */
#define TIM_TIM1_ADC1_AWD3                     (0x00000003U) /*!< TIM1_ETR is connected to ADC1 AWD3 */

#if defined(ADC4)
#define TIM_TIM1_ADC4_NONE                     (0x00000000U) /*!< TIM1_ETR is not connected to any AWD (analog watchdog)*/
#define TIM_TIM1_ADC4_AWD1                     (0x00000004U) /*!< TIM1_ETR is connected to ADC4 AWD1 */
#define TIM_TIM1_ADC4_AWD2                     (0x00000008U) /*!< TIM1_ETR is connected to ADC4 AWD2 */
#define TIM_TIM1_ADC4_AWD3                     (0x0000000CU) /*!< TIM1_ETR is connected to ADC4 AWD3 */
#elif defined(ADC2)
#define TIM_TIM1_ADC2_NONE                     (0x00000000U) /*!< TIM1_ETR is not connected to any AWD (analog watchdog)*/
#define TIM_TIM1_ADC2_AWD1                     (0x00000004U) /*!< TIM1_ETR is connected to ADC2 AWD1 */
#define TIM_TIM1_ADC2_AWD2                     (0x00000008U) /*!< TIM1_ETR is connected to ADC2 AWD2 */
#define TIM_TIM1_ADC2_AWD3                     (0x0000000CU) /*!< TIM1_ETR is connected to ADC2 AWD3 */
#endif /* ADC4 */
#endif /* TIM1 */

#if defined(TIM8)
#define TIM_TIM8_ADC2_NONE                     (0x00000000U) /*!< TIM8_ETR is not connected to any AWD (analog watchdog) */
#define TIM_TIM8_ADC2_AWD1                     (0x00000001U) /*!< TIM8_ETR is connected to ADC2 AWD1 */
#define TIM_TIM8_ADC2_AWD2                     (0x00000002U) /*!< TIM8_ETR is connected to ADC2 AWD2 */
#define TIM_TIM8_ADC2_AWD3                     (0x00000003U) /*!< TIM8_ETR is connected to ADC2 AWD3 */

#define TIM_TIM8_ADC3_NONE                     (0x00000000U) /*!< TIM8_ETR is not connected to any AWD (analog watchdog) */
#define TIM_TIM8_ADC3_AWD1                     (0x00000004U) /*!< TIM8_ETR is connected to ADC3 AWD1 */
#define TIM_TIM8_ADC3_AWD2                     (0x00000008U) /*!< TIM8_ETR is connected to ADC3 AWD2 */
#define TIM_TIM8_ADC3_AWD3                     (0x0000000CU) /*!< TIM8_ETR is connected to ADC3 AWD3 */
#endif /* TIM8 */

#if defined(TIM14)
#define TIM_TIM14_GPIO                         (0x00000000U) /*!< TIM14 TI1 is connected to GPIO */
#define TIM_TIM14_RTC                          (0x00000001U) /*!< TIM14 TI1 is connected to RTC_clock */
#define TIM_TIM14_HSE                          (0x00000002U) /*!< TIM14 TI1 is connected to HSE/32U */
#define TIM_TIM14_MCO                          (0x00000003U) /*!< TIM14 TI1 is connected to MCO */
#endif /* TIM14 */

#if defined(TIM16)
#define TIM_TIM16_GPIO                         (0x00000000U) /*!< TIM16 TI1 is connected to GPIO */
#define TIM_TIM16_RTC                          (0x00000001U) /*!< TIM16 TI1 is connected to RTC_clock */
#define TIM_TIM16_HSE                          (0x00000002U) /*!< TIM16 TI1 is connected to HSE/32 */
#define TIM_TIM16_MCO                          (0x00000003U) /*!< TIM16 TI1 is connected to MCO */
#endif /* TIM16 */

#if defined(TIM20)
#define TIM_TIM20_ADC3_NONE                    (0x00000000U) /*!< TIM20_ETR is not connected to any AWD (analog watchdog) */
#define TIM_TIM20_ADC3_AWD1                    (0x00000001U) /*!< TIM20_ETR is connected to ADC3 AWD1 */
#define TIM_TIM20_ADC3_AWD2                    (0x00000002U) /*!< TIM20_ETR is connected to ADC3 AWD2 */
#define TIM_TIM20_ADC3_AWD3                    (0x00000003U) /*!< TIM20_ETR is connected to ADC3 AWD3 */

#define TIM_TIM20_ADC4_NONE                    (0x00000000U) /*!< TIM20_ETR is not connected to any AWD (analog watchdog) */
#define TIM_TIM20_ADC4_AWD1                    (0x00000004U) /*!< TIM20_ETR is connected to ADC4 AWD1 */
#define TIM_TIM20_ADC4_AWD2                    (0x00000008U) /*!< TIM20_ETR is connected to ADC4 AWD2 */
#define TIM_TIM20_ADC4_AWD3                    (0x0000000CU) /*!< TIM20_ETR is connected to ADC4 AWD3 */
#endif /* TIM20 */
/**
  * @}
  */

/**
  * @}
  */
/* End of exported constants -------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Macros TIM Extended Exported Macros
  * @{
  */

/**
  * @}
  */
/* End of exported macro -----------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/** @defgroup TIMEx_Private_Macros TIM Extended Private Macros
  * @{
  */
#if defined(TIM1) && defined(TIM8) && defined(TIM20) && defined(TIM16)
#define IS_TIM_REMAP(__INSTANCE__, __REMAP__)                                        \
  ((((__INSTANCE__) == TIM1)  && ((((__REMAP__) & 0xFFFFFFF0U) == 0x00000000U)))     \
   || (((__INSTANCE__) == TIM8)  && ((((__REMAP__) & 0xFFFFFFF0U) == 0x00000000U)))  \
   || (((__INSTANCE__) == TIM20) && ((((__REMAP__) & 0xFFFFFFF0U) == 0x00000000U)))  \
   || (((__INSTANCE__) == TIM16) && ((((__REMAP__) & 0xFFFFFFFCU) == 0x00000000U))))
#elif defined(TIM1) && defined(TIM8) && defined(TIM16)
#define IS_TIM_REMAP(__INSTANCE__, __REMAP__)                                        \
  ((((__INSTANCE__) == TIM1)  && ((((__REMAP__) & 0xFFFFFFF0U) == 0x00000000U)))     \
   || (((__INSTANCE__) == TIM8)  && ((((__REMAP__) & 0xFFFFFFF0U) == 0x00000000U)))  \
   || (((__INSTANCE__) == TIM16) && ((((__REMAP__) & 0xFFFFFFFCU) == 0x00000000U))))
#elif defined(TIM1) && defined(TIM16)
#define IS_TIM_REMAP(__INSTANCE__, __REMAP__)                                        \
  ((((__INSTANCE__) == TIM1)  && ((((__REMAP__) & 0xFFFFFFF0U) == 0x00000000U)))     \
   || (((__INSTANCE__) == TIM16) && ((((__REMAP__) & 0xFFFFFFFCU) == 0x00000000U))))
#elif defined(TIM14)
#define IS_TIM_REMAP(__INSTANCE__, __REMAP__)                                        \
  (((__INSTANCE__) == TIM14)  && (((__REMAP__) & 0xFFFFFFFCU) == 0x00000000U))
#endif /* TIM1 && TIM8 && TIM20 && TIM16 */

/**
  * @}
  */
/* End of private macro ------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup TIMEx_Exported_Functions TIM Extended Exported Functions
  * @{
  */

/** @addtogroup TIMEx_Exported_Functions_Group1 Extended Timer Hall Sensor functions
  *  @brief    Timer Hall Sensor functions
  * @{
  */
/*  Timer Hall Sensor functions  **********************************************/
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Init(TIM_HandleTypeDef *htim, TIM_HallSensor_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_DeInit(TIM_HandleTypeDef *htim);

void HAL_TIMEx_HallSensor_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIMEx_HallSensor_MspDeInit(TIM_HandleTypeDef *htim);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop(TIM_HandleTypeDef *htim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_IT(TIM_HandleTypeDef *htim);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_DMA(TIM_HandleTypeDef *htim);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group2 Extended Timer Complementary Output Compare functions
  *  @brief   Timer Complementary Output Compare functions
  * @{
  */
/*  Timer Complementary Output Compare functions  *****************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIMEx_OCN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group3 Extended Timer Complementary PWM functions
  *  @brief    Timer Complementary PWM functions
  * @{
  */
/*  Timer Complementary PWM functions  ****************************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group4 Extended Timer Complementary One Pulse functions
  *  @brief    Timer Complementary One Pulse functions
  * @{
  */
/*  Timer Complementary One Pulse functions  **********************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group5 Extended Peripheral Control functions
  *  @brief    Peripheral Control functions
  * @{
  */
/* Extended Control functions  ************************************************/
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                              uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_IT(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                 uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_DMA(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                  uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim,
                                                        TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,
                                                TIM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);
#if defined(TIM_CCR5_CCR5)
HAL_StatusTypeDef HAL_TIMEx_GroupChannel5(TIM_HandleTypeDef *htim, uint32_t Channels);
#endif /* TIM_CCR5_CCR5 */
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group6 Extended Callbacks functions
  * @brief    Extended Callbacks functions
  * @{
  */
/* Extended Callback **********************************************************/
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim);
#if defined(TIM_BDTR_BK2E)
void HAL_TIMEx_Break2Callback(TIM_HandleTypeDef *htim);
#endif /* TIM_BDTR_BK2E */
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group7 Extended Peripheral State functions
  * @brief    Extended Peripheral State functions
  * @{
  */
/* Extended Peripheral State functions  ***************************************/
HAL_TIM_StateTypeDef HAL_TIMEx_HallSensor_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIMEx_GetChannelNState(TIM_HandleTypeDef *htim,  uint32_t ChannelN);
/**
  * @}
  */

/**
  * @}
  */
/* End of exported functions -------------------------------------------------*/

/* Private functions----------------------------------------------------------*/
/** @addtogroup TIMEx_Private_Functions TIMEx Private Functions
  * @{
  */
void TIMEx_DMACommutationCplt(DMA_HandleTypeDef *hdma);
void TIMEx_DMACommutationHalfCplt(DMA_HandleTypeDef *hdma);
/**
  * @}
  */
/* End of private functions --------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* STM32F3xx_HAL_TIM_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
