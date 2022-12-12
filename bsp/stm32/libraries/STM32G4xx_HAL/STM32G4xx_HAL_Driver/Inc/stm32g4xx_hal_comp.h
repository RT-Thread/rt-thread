/**
  ******************************************************************************
  * @file    stm32g4xx_hal_comp.h
  * @author  MCD Application Team
  * @brief   Header file of COMP HAL module.
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
#ifndef STM32G4xx_HAL_COMP_H
#define STM32G4xx_HAL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"
#include "stm32g4xx_ll_exti.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */


/** @addtogroup COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup COMP_Exported_Types COMP Exported Types
  * @{
  */

/**
  * @brief  COMP Init structure definition
  */
typedef struct
{

  uint32_t InputPlus;          /*!< Set comparator input plus (non-inverting input).
                                    This parameter can be a value of @ref COMP_InputPlus */

  uint32_t InputMinus;         /*!< Set comparator input minus (inverting input).
                                    This parameter can be a value of @ref COMP_InputMinus */

  uint32_t Hysteresis;         /*!< Set comparator hysteresis mode of the input minus.
                                    This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t OutputPol;          /*!< Set comparator output polarity.
                                    This parameter can be a value of @ref COMP_OutputPolarity */

  uint32_t BlankingSrce;       /*!< Set comparator blanking source.
                                    This parameter can be a value of @ref COMP_BlankingSrce */

  uint32_t TriggerMode;        /*!< Set the comparator output triggering External Interrupt Line (EXTI).
                                    This parameter can be a value of @ref COMP_EXTI_TriggerMode */

} COMP_InitTypeDef;

/**
  * @brief  HAL COMP state machine: HAL COMP states definition
  */
#define COMP_STATE_BITFIELD_LOCK  (0x10U)
typedef enum
{
  HAL_COMP_STATE_RESET             = 0x00U,                                             /*!< COMP not yet initialized                             */
  HAL_COMP_STATE_RESET_LOCKED      = (HAL_COMP_STATE_RESET | COMP_STATE_BITFIELD_LOCK), /*!< COMP not yet initialized and configuration is locked */
  HAL_COMP_STATE_READY             = 0x01U,                                             /*!< COMP initialized and ready for use                   */
  HAL_COMP_STATE_READY_LOCKED      = (HAL_COMP_STATE_READY | COMP_STATE_BITFIELD_LOCK), /*!< COMP initialized but configuration is locked         */
  HAL_COMP_STATE_BUSY              = 0x02U,                                             /*!< COMP is running                                      */
  HAL_COMP_STATE_BUSY_LOCKED       = (HAL_COMP_STATE_BUSY | COMP_STATE_BITFIELD_LOCK)   /*!< COMP is running and configuration is locked          */
} HAL_COMP_StateTypeDef;

/**
  * @brief  COMP Handle Structure definition
  */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
typedef struct __COMP_HandleTypeDef
#else
typedef struct
#endif
{
  COMP_TypeDef       *Instance;       /*!< Register base address    */
  COMP_InitTypeDef   Init;            /*!< COMP required parameters */
  HAL_LockTypeDef    Lock;            /*!< Locking object           */
  __IO HAL_COMP_StateTypeDef  State;  /*!< COMP communication state */
  __IO uint32_t      ErrorCode;       /*!< COMP error code */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
  void (* TriggerCallback)(struct __COMP_HandleTypeDef *hcomp);   /*!< COMP trigger callback */
  void (* MspInitCallback)(struct __COMP_HandleTypeDef *hcomp);   /*!< COMP Msp Init callback */
  void (* MspDeInitCallback)(struct __COMP_HandleTypeDef *hcomp); /*!< COMP Msp DeInit callback */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
} COMP_HandleTypeDef;

#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL COMP Callback ID enumeration definition
  */
typedef enum
{
  HAL_COMP_TRIGGER_CB_ID                = 0x00U,  /*!< COMP trigger callback ID */
  HAL_COMP_MSPINIT_CB_ID                = 0x01U,  /*!< COMP Msp Init callback ID */
  HAL_COMP_MSPDEINIT_CB_ID              = 0x02U   /*!< COMP Msp DeInit callback ID */
} HAL_COMP_CallbackIDTypeDef;

/**
  * @brief  HAL COMP Callback pointer definition
  */
typedef  void (*pCOMP_CallbackTypeDef)(COMP_HandleTypeDef *hcomp); /*!< pointer to a COMP callback function */

#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_Exported_Constants COMP Exported Constants
  * @{
  */

/** @defgroup COMP_Error_Code COMP Error Code
  * @{
  */
#define HAL_COMP_ERROR_NONE             (0x00UL)  /*!< No error */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
#define HAL_COMP_ERROR_INVALID_CALLBACK (0x01UL)  /*!< Invalid Callback error */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup COMP_InputPlus COMP input plus (non-inverting input)
  * @{
  */
#define COMP_INPUT_PLUS_IO1            (0x00000000UL)         /*!< Comparator input plus connected to IO1 (pin PA1 for COMP1, pin PA7 for COMP2, pin PA0 for COMP3, pin PB0 for COMP4, pin PB13 for COMP5, pin PB11 for COMP6, pin PB14 for COMP7). Note: For COMPx instance availability, please refer to datasheet */
#define COMP_INPUT_PLUS_IO2            (COMP_CSR_INPSEL)      /*!< Comparator input plus connected to IO2 (pin PB1 for COMP1, pin PA3 for COMP2, pin PC1 for COMP3, pin PE7 for COMP4, pin PD12 for COMP5, pin PD11 for COMP6, pin PD14 for COMP7). Note: For COMPx instance availability, please refer to datasheet */
/**
  * @}
  */

/** @defgroup COMP_InputMinus COMP input minus (inverting input)
  * @{
  */
#define COMP_INPUT_MINUS_1_4VREFINT    (                                                            COMP_CSR_SCALEN | COMP_CSR_BRGEN)        /*!< Comparator input minus connected to 1/4 VrefInt */
#define COMP_INPUT_MINUS_1_2VREFINT    (                                        COMP_CSR_INMSEL_0 | COMP_CSR_SCALEN | COMP_CSR_BRGEN)        /*!< Comparator input minus connected to 1/2 VrefInt */
#define COMP_INPUT_MINUS_3_4VREFINT    (                    COMP_CSR_INMSEL_1                     | COMP_CSR_SCALEN | COMP_CSR_BRGEN)        /*!< Comparator input minus connected to 3/4 VrefInt */
#define COMP_INPUT_MINUS_VREFINT       (                    COMP_CSR_INMSEL_1 | COMP_CSR_INMSEL_0 | COMP_CSR_SCALEN                 )        /*!< Comparator input minus connected to VrefInt */
#define COMP_INPUT_MINUS_DAC1_CH1      (COMP_CSR_INMSEL_2                     | COMP_CSR_INMSEL_0)                                           /*!< Comparator input minus connected to DAC1 Channel 1 for COMP1/3/4. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define COMP_INPUT_MINUS_DAC1_CH2      (COMP_CSR_INMSEL_2                     | COMP_CSR_INMSEL_0)                                           /*!< Comparator input minus connected to DAC1 Channel 2 for COMP2/5. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define COMP_INPUT_MINUS_DAC2_CH1      (COMP_CSR_INMSEL_2                     | COMP_CSR_INMSEL_0)                                           /*!< Comparator input minus connected to DAC2 Channel 1 for COMP6/7. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define COMP_INPUT_MINUS_DAC3_CH1      (COMP_CSR_INMSEL_2                                        )                                           /*!< Comparator input minus connected to DAC3 Channel 1 for COMP1/3. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define COMP_INPUT_MINUS_DAC3_CH2      (COMP_CSR_INMSEL_2                                        )                                           /*!< Comparator input minus connected to DAC3 Channel 2 for COMP2/4. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define COMP_INPUT_MINUS_DAC4_CH1      (COMP_CSR_INMSEL_2                                        )                                           /*!< Comparator input minus connected to DAC4 Channel 1 for COMP5/7. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define COMP_INPUT_MINUS_DAC4_CH2      (COMP_CSR_INMSEL_2                                        )                                           /*!< Comparator input minus connected to DAC4 Channel 2 for COMP6. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define COMP_INPUT_MINUS_IO1           (COMP_CSR_INMSEL_2 | COMP_CSR_INMSEL_1                    )                                           /*!< Comparator input minus connected to IO1 (pin PA4 for COMP1, pin PA5 for COMP2, pin PF1 for COMP3, pin PE8 for COMP4, pin PB10 for COMP5, pin PD10 for COMP6, pin PD15 for COMP7). Note: For COMPx instance availability, please refer to datasheet */ 
#define COMP_INPUT_MINUS_IO2           (COMP_CSR_INMSEL_2 | COMP_CSR_INMSEL_1 | COMP_CSR_INMSEL_0)                                           /*!< Comparator input minus connected to IO2 (pin PA0 for COMP1, pin PA2 for COMP2, pin PC0 for COMP3, pin PB2 for COMP4, pin PD13 for COMP5, pin PB15 for COMP6, pin PB12 for COMP7). Note: For COMPx instance availability, please refer to datasheet */
/**
  * @}
  */

/** @defgroup COMP_Hysteresis COMP hysteresis
  * @{
  */
#define COMP_HYSTERESIS_NONE           (0x00000000UL)                                        /*!< No hysteresis */
#define COMP_HYSTERESIS_10MV           (                                    COMP_CSR_HYST_0) /*!< Hysteresis level 10mV */
#define COMP_HYSTERESIS_20MV           (                  COMP_CSR_HYST_1                  ) /*!< Hysteresis level 20mV */
#define COMP_HYSTERESIS_30MV           (                  COMP_CSR_HYST_1 | COMP_CSR_HYST_0) /*!< Hysteresis level 30mV */
#define COMP_HYSTERESIS_40MV           (COMP_CSR_HYST_2                                    ) /*!< Hysteresis level 40mV */
#define COMP_HYSTERESIS_50MV           (COMP_CSR_HYST_2                   | COMP_CSR_HYST_0) /*!< Hysteresis level 50mV */
#define COMP_HYSTERESIS_60MV           (COMP_CSR_HYST_2 | COMP_CSR_HYST_1                  ) /*!< Hysteresis level 60mV */
#define COMP_HYSTERESIS_70MV           (COMP_CSR_HYST_2 | COMP_CSR_HYST_1 | COMP_CSR_HYST_0) /*!< Hysteresis level 70mV */
#define COMP_HYSTERESIS_LOW            COMP_HYSTERESIS_10MV  /*!< Hysteresis level low */
#define COMP_HYSTERESIS_MEDIUM         COMP_HYSTERESIS_40MV  /*!< Hysteresis level medium */
#define COMP_HYSTERESIS_HIGH           COMP_HYSTERESIS_70MV  /*!< Hysteresis level high */
/**
  * @}
  */

/** @defgroup COMP_OutputPolarity COMP output Polarity
  * @{
  */
#define COMP_OUTPUTPOL_NONINVERTED     (0x00000000UL)         /*!< COMP output level is not inverted (comparator output is high when the input plus is at a higher voltage than the input minus) */
#define COMP_OUTPUTPOL_INVERTED        (COMP_CSR_POLARITY)    /*!< COMP output level is inverted     (comparator output is low  when the input plus is at a higher voltage than the input minus) */
/**
  * @}
  */

/** @defgroup COMP_BlankingSrce  COMP blanking source
  * @{
  */
#define COMP_BLANKINGSRC_NONE            (0x00000000UL)          /*!<Comparator output without blanking */
#define COMP_BLANKINGSRC_TIM1_OC5_COMP1  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP1). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM1_OC5_COMP2  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP2). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM1_OC5_COMP3  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP3). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM1_OC5_COMP4  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP4). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM1_OC5_COMP5  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP5). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM1_OC5_COMP6  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP6). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM1_OC5_COMP7  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP7). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM2_OC3_COMP1  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM2 OC3 (specific to COMP instance: COMP1). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM2_OC3_COMP2  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM2 OC3 (specific to COMP instance: COMP2). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM2_OC3_COMP5  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM2 OC3 (specific to COMP instance: COMP5). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM2_OC4_COMP3  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM2 OC4 (specific to COMP instance: COMP3). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM2_OC4_COMP6  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM2 OC4 (specific to COMP instance: COMP6). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM3_OC3_COMP1  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP1). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM3_OC3_COMP2  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP2). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM3_OC3_COMP3  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP3). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM3_OC3_COMP5  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP5). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM3_OC3_COMP7  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP7). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM3_OC4_COMP4  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC4 (specific to COMP instance: COMP4). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM8_OC5_COMP1  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP1). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM8_OC5_COMP2  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP2). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM8_OC5_COMP3  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP3). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM8_OC5_COMP4  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP4). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM8_OC5_COMP5  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP5). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM8_OC5_COMP6  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP6). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM8_OC5_COMP7  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP7). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM15_OC1_COMP4 (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM15 OC1 (specific to COMP instance: COMP4). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM15_OC2_COMP6 (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM15 OC2 (specific to COMP instance: COMP6). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM15_OC2_COMP7 (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM15 OC3 (specific to COMP instance: COMP7). Note: For COMPx & TIMx instances availability, please refer to datasheet */
#define COMP_BLANKINGSRC_TIM20_OC5       (COMP_CSR_BLANKING_2 |                       COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM20 OC5 (Common to all COMP instances) */
#define COMP_BLANKINGSRC_TIM15_OC1       (COMP_CSR_BLANKING_2 | COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM15 OC1 (Common to all COMP instances) */
#define COMP_BLANKINGSRC_TIM4_OC3        (COMP_CSR_BLANKING_2 | COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM4 OC3 (Common to all COMP instances) */

/**
  * @}
  */

/** @defgroup COMP_OutputLevel COMP Output Level
  * @{
  */
/* Note: Comparator output level values are fixed to "0" and "1",             */
/* corresponding COMP register bit is managed by HAL function to match        */
/* with these values (independently of bit position in register).             */

/* When output polarity is not inverted, comparator output is low when
   the input plus is at a lower voltage than the input minus */
#define COMP_OUTPUT_LEVEL_LOW              (0x00000000UL)
/* When output polarity is not inverted, comparator output is high when
   the input plus is at a higher voltage than the input minus */
#define COMP_OUTPUT_LEVEL_HIGH             (0x00000001UL)
/**
  * @}
  */

/** @defgroup COMP_EXTI_TriggerMode COMP output to EXTI
  * @{
  */
#define COMP_TRIGGERMODE_NONE                 (0x00000000UL)                                            /*!< Comparator output triggering no External Interrupt Line */
#define COMP_TRIGGERMODE_IT_RISING            (COMP_EXTI_IT | COMP_EXTI_RISING)                         /*!< Comparator output triggering External Interrupt Line event with interruption, on rising edge */
#define COMP_TRIGGERMODE_IT_FALLING           (COMP_EXTI_IT | COMP_EXTI_FALLING)                        /*!< Comparator output triggering External Interrupt Line event with interruption, on falling edge */
#define COMP_TRIGGERMODE_IT_RISING_FALLING    (COMP_EXTI_IT | COMP_EXTI_RISING | COMP_EXTI_FALLING)     /*!< Comparator output triggering External Interrupt Line event with interruption, on both rising and falling edges */
#define COMP_TRIGGERMODE_EVENT_RISING         (COMP_EXTI_EVENT | COMP_EXTI_RISING)                      /*!< Comparator output triggering External Interrupt Line event only (without interruption), on rising edge */
#define COMP_TRIGGERMODE_EVENT_FALLING        (COMP_EXTI_EVENT | COMP_EXTI_FALLING)                     /*!< Comparator output triggering External Interrupt Line event only (without interruption), on falling edge */
#define COMP_TRIGGERMODE_EVENT_RISING_FALLING (COMP_EXTI_EVENT | COMP_EXTI_RISING | COMP_EXTI_FALLING)  /*!< Comparator output triggering External Interrupt Line event only (without interruption), on both rising and falling edges */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMP_Exported_Macros COMP Exported Macros
  * @{
  */

/** @defgroup COMP_Handle_Management  COMP Handle Management
  * @{
  */

/** @brief  Reset COMP handle state.
  * @param  __HANDLE__  COMP handle
  * @retval None
  */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) do{                                                  \
                                                      (__HANDLE__)->State = HAL_COMP_STATE_RESET;      \
                                                      (__HANDLE__)->MspInitCallback = NULL;            \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;          \
                                                    } while(0)
#else
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_COMP_STATE_RESET)
#endif

/**
  * @brief Clear COMP error code (set it to no error code "HAL_COMP_ERROR_NONE").
  * @param __HANDLE__ COMP handle
  * @retval None
  */
#define COMP_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_COMP_ERROR_NONE)

/**
  * @brief  Enable the specified comparator.
  * @param  __HANDLE__  COMP handle
  * @retval None
  */
#define __HAL_COMP_ENABLE(__HANDLE__)              SET_BIT((__HANDLE__)->Instance->CSR, COMP_CSR_EN)

/**
  * @brief  Disable the specified comparator.
  * @param  __HANDLE__  COMP handle
  * @retval None
  */
#define __HAL_COMP_DISABLE(__HANDLE__)             CLEAR_BIT((__HANDLE__)->Instance->CSR, COMP_CSR_EN)

/**
  * @brief  Lock the specified comparator configuration.
  * @note   Using this macro induce HAL COMP handle state machine being no
  *         more in line with COMP instance state.
  *         To keep HAL COMP handle state machine updated, it is recommended
  *         to use function "HAL_COMP_Lock')".
  * @param  __HANDLE__  COMP handle
  * @retval None
  */
#define __HAL_COMP_LOCK(__HANDLE__)                SET_BIT((__HANDLE__)->Instance->CSR, COMP_CSR_LOCK)

/**
  * @brief  Check whether the specified comparator is locked.
  * @param  __HANDLE__  COMP handle
  * @retval Value 0 if COMP instance is not locked, value 1 if COMP instance is locked
  */
#define __HAL_COMP_IS_LOCKED(__HANDLE__)           (READ_BIT((__HANDLE__)->Instance->CSR, COMP_CSR_LOCK) == COMP_CSR_LOCK)

/**
  * @}
  */

/** @defgroup COMP_Exti_Management  COMP external interrupt line management
  * @{
  */

/**
  * @brief  Enable the COMP1 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_RISING_EDGE()    LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_RISING_EDGE()   LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP1 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP1 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP1); \
                                                               LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP1); \
                                                             } while(0)

/**
  * @brief  Disable the COMP1 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                               LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP1); \
                                                               LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP1); \
                                                             } while(0)

/**
  * @brief  Enable the COMP1 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_IT()             LL_EXTI_EnableIT_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_IT()            LL_EXTI_DisableIT_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Generate a software interrupt on the COMP1 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_GENERATE_SWIT()         LL_EXTI_GenerateSWI_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP1 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_EVENT()          LL_EXTI_EnableEvent_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_EVENT()         LL_EXTI_DisableEvent_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Check whether the COMP1 EXTI line flag is set.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP1_EXTI_GET_FLAG()              LL_EXTI_IsActiveFlag_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Clear the COMP1 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_CLEAR_FLAG()            LL_EXTI_ClearFlag_0_31(COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP2 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_RISING_EDGE()    LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_RISING_EDGE()   LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP2); \
                                                               LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP2); \
                                                             } while(0)

/**
  * @brief  Disable the COMP2 EXTI line rising & falling edge trigger.
  * @retval None
  */                                         
#define __HAL_COMP_COMP2_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                               LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP2); \
                                                               LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP2); \
                                                             } while(0)

/**
  * @brief  Enable the COMP2 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_IT()             LL_EXTI_EnableIT_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_IT()            LL_EXTI_DisableIT_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Generate a software interrupt on the COMP2 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_GENERATE_SWIT()         LL_EXTI_GenerateSWI_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_EVENT()          LL_EXTI_EnableEvent_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_EVENT()         LL_EXTI_DisableEvent_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Check whether the COMP2 EXTI line flag is set.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP2_EXTI_GET_FLAG()              LL_EXTI_IsActiveFlag_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Clear the COMP2 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_CLEAR_FLAG()            LL_EXTI_ClearFlag_0_31(COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP3 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_ENABLE_RISING_EDGE()    LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Disable the COMP3 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_DISABLE_RISING_EDGE()   LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Enable the COMP3 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Disable the COMP3 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Enable the COMP3 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP3); \
                                                               LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP3); \
                                                             } while(0)

/**
  * @brief  Disable the COMP3 EXTI line rising & falling edge trigger.
  * @retval None
  */                                         
#define __HAL_COMP_COMP3_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                               LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP3); \
                                                               LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP3); \
                                                             } while(0)

/**
  * @brief  Enable the COMP3 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_ENABLE_IT()             LL_EXTI_EnableIT_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Disable the COMP3 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_DISABLE_IT()            LL_EXTI_DisableIT_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Generate a software interrupt on the COMP3 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_GENERATE_SWIT()         LL_EXTI_GenerateSWI_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Enable the COMP3 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_ENABLE_EVENT()          LL_EXTI_EnableEvent_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Disable the COMP3 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_DISABLE_EVENT()         LL_EXTI_DisableEvent_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Check whether the COMP3 EXTI line flag is set.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP3_EXTI_GET_FLAG()              LL_EXTI_IsActiveFlag_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Clear the COMP3 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP3_EXTI_CLEAR_FLAG()            LL_EXTI_ClearFlag_0_31(COMP_EXTI_LINE_COMP3)

/**
  * @brief  Enable the COMP4 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_ENABLE_RISING_EDGE()    LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Disable the COMP4 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_DISABLE_RISING_EDGE()   LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Enable the COMP4 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Disable the COMP4 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Enable the COMP4 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP4); \
                                                               LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP4); \
                                                             } while(0)

/**
  * @brief  Disable the COMP4 EXTI line rising & falling edge trigger.
  * @retval None
  */                                         
#define __HAL_COMP_COMP4_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                               LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP4); \
                                                               LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP4); \
                                                             } while(0)

/**
  * @brief  Enable the COMP4 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_ENABLE_IT()             LL_EXTI_EnableIT_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Disable the COMP4 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_DISABLE_IT()            LL_EXTI_DisableIT_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Generate a software interrupt on the COMP4 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_GENERATE_SWIT()         LL_EXTI_GenerateSWI_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Enable the COMP4 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_ENABLE_EVENT()          LL_EXTI_EnableEvent_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Disable the COMP4 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_DISABLE_EVENT()         LL_EXTI_DisableEvent_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Check whether the COMP4 EXTI line flag is set.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP4_EXTI_GET_FLAG()              LL_EXTI_IsActiveFlag_0_31(COMP_EXTI_LINE_COMP4)

/**
  * @brief  Clear the COMP4 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP4_EXTI_CLEAR_FLAG()            LL_EXTI_ClearFlag_0_31(COMP_EXTI_LINE_COMP4)

#if  defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G473xx) || defined(STM32G483xx)
/**
  * @brief  Enable the COMP5 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_ENABLE_RISING_EDGE()    LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Disable the COMP5 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_DISABLE_RISING_EDGE()   LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Enable the COMP5 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Disable the COMP5 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Enable the COMP5 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP5); \
                                                               LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP5); \
                                                             } while(0)

/**
  * @brief  Disable the COMP5 EXTI line rising & falling edge trigger.
  * @retval None
  */                                         
#define __HAL_COMP_COMP5_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                               LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP5); \
                                                               LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP5); \
                                                             } while(0)

/**
  * @brief  Enable the COMP5 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_ENABLE_IT()             LL_EXTI_EnableIT_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Disable the COMP5 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_DISABLE_IT()            LL_EXTI_DisableIT_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Generate a software interrupt on the COMP5 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_GENERATE_SWIT()         LL_EXTI_GenerateSWI_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Enable the COMP5 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_ENABLE_EVENT()          LL_EXTI_EnableEvent_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Disable the COMP5 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_DISABLE_EVENT()         LL_EXTI_DisableEvent_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Check whether the COMP5 EXTI line flag is set.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP5_EXTI_GET_FLAG()              LL_EXTI_IsActiveFlag_0_31(COMP_EXTI_LINE_COMP5)

/**
  * @brief  Clear the COMP5 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP5_EXTI_CLEAR_FLAG()            LL_EXTI_ClearFlag_0_31(COMP_EXTI_LINE_COMP5)

#endif /* STM32G474xx || STM32G484xx || STM32G473xx || STM32G483xx*/
#if  defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G473xx) || defined(STM32G483xx)
/**
  * @brief  Enable the COMP6 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_ENABLE_RISING_EDGE()    LL_EXTI_EnableRisingTrig_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Disable the COMP6 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_DISABLE_RISING_EDGE()   LL_EXTI_DisableRisingTrig_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Enable the COMP6 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableFallingTrig_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Disable the COMP6 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableFallingTrig_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Enable the COMP6 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               LL_EXTI_EnableRisingTrig_32_63(COMP_EXTI_LINE_COMP6); \
                                                               LL_EXTI_EnableFallingTrig_32_63(COMP_EXTI_LINE_COMP6); \
                                                             } while(0)

/**
  * @brief  Disable the COMP6 EXTI line rising & falling edge trigger.
  * @retval None
  */                                         
#define __HAL_COMP_COMP6_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                               LL_EXTI_DisableRisingTrig_32_63(COMP_EXTI_LINE_COMP6); \
                                                               LL_EXTI_DisableFallingTrig_32_63(COMP_EXTI_LINE_COMP6); \
                                                             } while(0)

/**
  * @brief  Enable the COMP6 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_ENABLE_IT()             LL_EXTI_EnableIT_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Disable the COMP6 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_DISABLE_IT()            LL_EXTI_DisableIT_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Generate a software interrupt on the COMP6 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_GENERATE_SWIT()         LL_EXTI_GenerateSWI_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Enable the COMP6 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_ENABLE_EVENT()          LL_EXTI_EnableEvent_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Disable the COMP6 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_DISABLE_EVENT()         LL_EXTI_DisableEvent_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Check whether the COMP6 EXTI line flag is set.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP6_EXTI_GET_FLAG()              LL_EXTI_IsActiveFlag_32_63(COMP_EXTI_LINE_COMP6)

/**
  * @brief  Clear the COMP6 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP6_EXTI_CLEAR_FLAG()            LL_EXTI_ClearFlag_32_63(COMP_EXTI_LINE_COMP6)

#endif /* STM32G474xx || STM32G484xx || STM32G473xx || STM32G483xx*/
#if  defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G473xx) || defined(STM32G483xx)
/**
  * @brief  Enable the COMP7 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_ENABLE_RISING_EDGE()    LL_EXTI_EnableRisingTrig_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Disable the COMP7 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_DISABLE_RISING_EDGE()   LL_EXTI_DisableRisingTrig_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Enable the COMP7 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableFallingTrig_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Disable the COMP7 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableFallingTrig_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Enable the COMP7 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               LL_EXTI_EnableRisingTrig_32_63(COMP_EXTI_LINE_COMP7); \
                                                               LL_EXTI_EnableFallingTrig_32_63(COMP_EXTI_LINE_COMP7); \
                                                             } while(0)

/**
  * @brief  Disable the COMP7 EXTI line rising & falling edge trigger.
  * @retval None
  */                                         
#define __HAL_COMP_COMP7_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                               LL_EXTI_DisableRisingTrig_32_63(COMP_EXTI_LINE_COMP7); \
                                                               LL_EXTI_DisableFallingTrig_32_63(COMP_EXTI_LINE_COMP7); \
                                                             } while(0)

/**
  * @brief  Enable the COMP7 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_ENABLE_IT()             LL_EXTI_EnableIT_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Disable the COMP7 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_DISABLE_IT()            LL_EXTI_DisableIT_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Generate a software interrupt on the COMP7 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_GENERATE_SWIT()         LL_EXTI_GenerateSWI_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Enable the COMP7 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_ENABLE_EVENT()          LL_EXTI_EnableEvent_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Disable the COMP7 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_DISABLE_EVENT()         LL_EXTI_DisableEvent_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Check whether the COMP7 EXTI line flag is set.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP7_EXTI_GET_FLAG()              LL_EXTI_IsActiveFlag_32_63(COMP_EXTI_LINE_COMP7)

/**
  * @brief  Clear the COMP7 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP7_EXTI_CLEAR_FLAG()            LL_EXTI_ClearFlag_32_63(COMP_EXTI_LINE_COMP7)

#endif /* STM32G474xx || STM32G484xx || STM32G473xx || STM32G483xx */
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup COMP_Private_Constants COMP Private Constants
  * @{
  */

/** @defgroup COMP_ExtiLine COMP EXTI Lines
  * @{
  */
#define COMP_EXTI_LINE_COMP1           (LL_EXTI_LINE_21)  /*!< EXTI line 21 connected to COMP1 output. Note: For COMPx instance availability, please refer to datasheet */
#define COMP_EXTI_LINE_COMP2           (LL_EXTI_LINE_22)  /*!< EXTI line 22 connected to COMP2 output. Note: For COMPx instance availability, please refer to datasheet */
#define COMP_EXTI_LINE_COMP3           (LL_EXTI_LINE_29)  /*!< EXTI line 29 connected to COMP3 output. Note: For COMPx instance availability, please refer to datasheet */
#define COMP_EXTI_LINE_COMP4           (LL_EXTI_LINE_30)  /*!< EXTI line 30 connected to COMP4 output. Note: For COMPx instance availability, please refer to datasheet */
#if defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G473xx) || defined(STM32G483xx)
#define COMP_EXTI_LINE_COMP5           (LL_EXTI_LINE_31)  /*!< EXTI line 31 connected to COMP5 output. Note: For COMPx instance availability, please refer to datasheet */
#define COMP_EXTI_LINE_COMP6           (LL_EXTI_LINE_32)  /*!< EXTI line 32 connected to COMP6 output. Note: For COMPx instance availability, please refer to datasheet */
#define COMP_EXTI_LINE_COMP7           (LL_EXTI_LINE_33)  /*!< EXTI line 33 connected to COMP7 output. Note: For COMPx instance availability, please refer to datasheet */
#endif
/**
  * @}
  */

/** @defgroup COMP_ExtiLine COMP EXTI Lines
  * @{
  */
#define COMP_EXTI_IT                        (0x00000001UL)  /*!< EXTI line event with interruption */
#define COMP_EXTI_EVENT                     (0x00000002UL)  /*!< EXTI line event only (without interruption) */
#define COMP_EXTI_RISING                    (0x00000010UL)  /*!< EXTI line event on rising edge */
#define COMP_EXTI_FALLING                   (0x00000020UL)  /*!< EXTI line event on falling edge */
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup COMP_Private_Macros COMP Private Macros
  * @{
  */

/** @defgroup COMP_GET_EXTI_LINE COMP private macros to get EXTI line associated with comparators
  * @{
  */
/**
  * @brief  Get the specified EXTI line for a comparator instance.
  * @param  __INSTANCE__  specifies the COMP instance.
  * @retval value of @ref COMP_ExtiLine
  */
#if defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G473xx) || defined(STM32G483xx)
#define COMP_GET_EXTI_LINE(__INSTANCE__)    (((__INSTANCE__) == COMP1) ? COMP_EXTI_LINE_COMP1  \
                                             :((__INSTANCE__) == COMP2) ? COMP_EXTI_LINE_COMP2 \
                                             :((__INSTANCE__) == COMP3) ? COMP_EXTI_LINE_COMP3 \
                                             :((__INSTANCE__) == COMP4) ? COMP_EXTI_LINE_COMP4 \
                                             :((__INSTANCE__) == COMP5) ? COMP_EXTI_LINE_COMP5 \
                                             :((__INSTANCE__) == COMP6) ? COMP_EXTI_LINE_COMP6 \
                                             : COMP_EXTI_LINE_COMP7)
#elif defined(STM32GBK1CB) || defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx)
#define COMP_GET_EXTI_LINE(__INSTANCE__)    (((__INSTANCE__) == COMP1) ? COMP_EXTI_LINE_COMP1  \
                                             :((__INSTANCE__) == COMP2) ? COMP_EXTI_LINE_COMP2 \
                                             :((__INSTANCE__) == COMP3) ? COMP_EXTI_LINE_COMP3 \
                                             : COMP_EXTI_LINE_COMP4)
#endif
/**
  * @}
  */

/** @defgroup COMP_IS_COMP_Private_Definitions COMP private macros to check input parameters
  * @{
  */
#define IS_COMP_INPUT_PLUS(__COMP_INSTANCE__, __INPUT_PLUS__) (((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO1) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO2))

#if defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G473xx) || defined(STM32G483xx)
#define IS_COMP_INPUT_MINUS(__COMP_INSTANCE__, __INPUT_MINUS__) (((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_4VREFINT)  || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_2VREFINT)  || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_3_4VREFINT)  || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_VREFINT)     || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO1)         || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO2)         || \
                                                                 (((__COMP_INSTANCE__) == COMP1)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC3_CH1))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP2)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH2)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC3_CH2))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP3)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC3_CH1))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP4)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC3_CH2))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP5)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH2)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC4_CH1))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP6)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC2_CH1)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC4_CH2))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP7)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC2_CH1)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC4_CH1))    \
                                                                 ))
#elif defined(STM32GBK1CB) || defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || defined(STM32G491xx) || defined(STM32G4A1xx)
#define IS_COMP_INPUT_MINUS(__COMP_INSTANCE__, __INPUT_MINUS__) (((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_4VREFINT)  || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_2VREFINT)  || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_3_4VREFINT)  || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_VREFINT)     || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO1)         || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO2)         || \
                                                                 (((__COMP_INSTANCE__) == COMP1)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC3_CH1))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP2)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH2)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC3_CH2))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP3)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC3_CH1))    \
                                                                 )                                                      || \
                                                                 (((__COMP_INSTANCE__) == COMP4)                        && \
                                                                  (((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)  || \
                                                                   ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC3_CH2))    \
                                                                 ))
#endif


#define IS_COMP_HYSTERESIS(__HYSTERESIS__)  (((__HYSTERESIS__) == COMP_HYSTERESIS_NONE)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_10MV)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_20MV)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_30MV)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_40MV)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_50MV)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_60MV)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_70MV)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_LOW)    || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_MEDIUM) || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_HIGH))

#define IS_COMP_OUTPUTPOL(__POL__)          (((__POL__) == COMP_OUTPUTPOL_NONINVERTED) || \
                                             ((__POL__) == COMP_OUTPUTPOL_INVERTED))

/* Note: Output blanking source depends on COMP instances     */
/*       Better use IS_COMP_BLANKINGSRC_INSTANCE instead      */
/*       Macro kept for compatibility with other STM32 series */
#define IS_COMP_BLANKINGSRCE(__OUTPUT_BLANKING_SOURCE__)                    \
  (   ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)               \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP1)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP2)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP3)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP4)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP5)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP6)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP7)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP1)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP2)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP5)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC4_COMP3)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC4_COMP6)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP1)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP2)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP3)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP5)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP7)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC4_COMP4)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP1)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP2)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP3)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP4)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP5)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP6)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP7)     \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC1_COMP4)    \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC2_COMP6)    \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC2_COMP7)    \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM20_OC5)          \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC1)          \
   || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM4_OC3)           \
  )
#if defined(STM32G474xx) || defined(STM32G484xx) || defined(STM32G473xx) || defined(STM32G483xx)
#define IS_COMP_BLANKINGSRC_INSTANCE(__INSTANCE__, __OUTPUT_BLANKING_SOURCE__)  \
   ((((__INSTANCE__) == COMP1) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP1)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP2) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP2)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP3) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC4_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP3)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP4) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC4_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC1_COMP4)))       \
    ||                                                                          \
    (((__INSTANCE__) == COMP5) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP5)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP5)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP5)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP5)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP6) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP6)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC4_COMP6)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP6)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC2_COMP6)))       \
    ||                                                                          \
    (((__INSTANCE__) == COMP7) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP7)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP7)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP7)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC2_COMP7)))       \
    || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM20_OC5)             \
    || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC1)             \
    || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM4_OC3)              \
    )
#elif defined(STM32GBK1CB) || defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx)
#define IS_COMP_BLANKINGSRC_INSTANCE(__INSTANCE__, __OUTPUT_BLANKING_SOURCE__)  \
   ((((__INSTANCE__) == COMP1) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP1)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP2) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP2)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP3) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC4_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP3)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP4) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC4_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC1_COMP4)))       \
    || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC1)             \
    || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM4_OC3)              \
    )
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
#define IS_COMP_BLANKINGSRC_INSTANCE(__INSTANCE__, __OUTPUT_BLANKING_SOURCE__)  \
   ((((__INSTANCE__) == COMP1) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP1)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP1)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP2) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP2)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP2)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP3) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM2_OC4_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3_COMP3)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP3)))        \
    ||                                                                          \
    (((__INSTANCE__) == COMP4) &&                                               \
    (((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_NONE)            ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM3_OC4_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM8_OC5_COMP4)  ||      \
     ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC1_COMP4)))       \
    || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM20_OC5)             \
    || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM15_OC1)             \
    || ((__OUTPUT_BLANKING_SOURCE__) == COMP_BLANKINGSRC_TIM4_OC3)              \
    )
#endif

#define IS_COMP_TRIGGERMODE(__MODE__)       (((__MODE__) == COMP_TRIGGERMODE_NONE)                 || \
                                             ((__MODE__) == COMP_TRIGGERMODE_IT_RISING)            || \
                                             ((__MODE__) == COMP_TRIGGERMODE_IT_FALLING)           || \
                                             ((__MODE__) == COMP_TRIGGERMODE_IT_RISING_FALLING)    || \
                                             ((__MODE__) == COMP_TRIGGERMODE_EVENT_RISING)         || \
                                             ((__MODE__) == COMP_TRIGGERMODE_EVENT_FALLING)        || \
                                             ((__MODE__) == COMP_TRIGGERMODE_EVENT_RISING_FALLING))

#define IS_COMP_OUTPUT_LEVEL(__OUTPUT_LEVEL__) (((__OUTPUT_LEVEL__) == COMP_OUTPUT_LEVEL_LOW)     || \
                                                ((__OUTPUT_LEVEL__) == COMP_OUTPUT_LEVEL_HIGH))

/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_Exported_Functions
  * @{
  */

/** @addtogroup COMP_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_MspDeInit(COMP_HandleTypeDef *hcomp);

#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_COMP_RegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID,
                                            pCOMP_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_COMP_UnRegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
/**
  * @}
  */

/* IO operation functions  *****************************************************/
/** @addtogroup COMP_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/* Peripheral Control functions  ************************************************/
/** @addtogroup COMP_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef *hcomp);
uint32_t          HAL_COMP_GetOutputLevel(COMP_HandleTypeDef *hcomp);
/* Callback in interrupt mode */
void              HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/* Peripheral State functions  **************************************************/
/** @addtogroup COMP_Exported_Functions_Group4
  * @{
  */
HAL_COMP_StateTypeDef HAL_COMP_GetState(COMP_HandleTypeDef *hcomp);
uint32_t              HAL_COMP_GetError(COMP_HandleTypeDef *hcomp);
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

#endif /* STM32G4xx_HAL_COMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
