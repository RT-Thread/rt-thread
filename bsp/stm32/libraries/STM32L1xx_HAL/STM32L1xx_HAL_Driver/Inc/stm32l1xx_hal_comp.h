/**
  ******************************************************************************
  * @file    stm32l1xx_hal_comp.h
  * @author  MCD Application Team
  * @brief   Header file of COMP HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
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
#ifndef __STM32L1xx_HAL_COMP_H
#define __STM32L1xx_HAL_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
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

  uint32_t InvertingInput;        /*!< Selects the inverting input of the comparator.
                                       This parameter can be a value of @ref COMP_InvertingInput
                                       Note: Inverting input can be changed on the fly, while comparator is running.
                                       Note: This feature is available on COMP2 only. If COMP1 is selected, this parameter is discarded (On COMP1, inverting input is fixed to Vrefint). */

  uint32_t NonInvertingInput;     /*!< Selects the non inverting input of the comparator.
                                       This parameter can be a value of @ref COMPEx_NonInvertingInput */

  uint32_t Output;                /*!< Selects the output redirection of the comparator.
                                       This parameter can be a value of @ref COMP_Output
                                       Note: This feature is available on COMP2 only. If COMP1 is selected, this parameter is discarded. */

  uint32_t Mode;                  /*!< Selects the operating consumption mode of the comparator
                                       to adjust the speed/consumption.
                                       This parameter can be a value of @ref COMP_Mode
                                       Note: This feature is available on COMP2 only. If COMP1 is selected, this parameter is discarded. */

  uint32_t WindowMode;            /*!< Selects the window mode of the 2 comparators.
                                       If enabled, non-inverting inputs of the 2 comparators are connected together and are using inputs of COMP2 only (COMP1 non-inverting input is no more accessible, even from ADC channel VCOMP).
                                       This parameter can be a value of @ref COMP_WindowMode
                                       Note: This feature must be enabled from COMP2 instance. If COMP1 is selected, this parameter is discarded. */

  uint32_t TriggerMode;           /*!< Selects the trigger mode of the comparator when using interruption on EXTI line (interrupt mode).
                                       This parameter can be a value of @ref COMP_TriggerMode
                                       Note: This feature is used with function "HAL_COMP_Start_IT()". In all other functions, this parameter is discarded. */

  uint32_t NonInvertingInputPull; /*!< Selects the internal pulling resistor connected on non inverting input.
                                       This parameter can be a value of @ref COMP_NonInvertingInputPull
                                       Note: To avoid extra power consumption, only one resistor should be enabled at a time.
                                       Note: This feature is available on COMP1 only. If COMP2 is selected, this parameter is discarded. */

}COMP_InitTypeDef;

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_COMP_STATE_RESET             = 0x00,    /*!< COMP not yet initialized or disabled             */
  HAL_COMP_STATE_READY             = 0x01,    /*!< COMP initialized and ready for use               */
  HAL_COMP_STATE_READY_LOCKED      = 0x11,    /*!< COMP initialized but the configuration is locked */
  HAL_COMP_STATE_BUSY              = 0x02,    /*!< COMP is running                                  */
  HAL_COMP_STATE_BUSY_LOCKED       = 0x12     /*!< COMP is running and the configuration is locked  */
}HAL_COMP_StateTypeDef;

/**
  * @brief  COMP Handle Structure definition
  */
typedef struct __COMP_HandleTypeDef
{
  COMP_TypeDef       *Instance;       /*!< Register base address    */
  COMP_InitTypeDef   Init;            /*!< COMP required parameters */
  HAL_LockTypeDef    Lock;            /*!< Locking object           */
  __IO HAL_COMP_StateTypeDef  State;  /*!< COMP communication state */
  __IO uint32_t      ErrorCode;       /*!< COMP Error code */
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
#define HAL_COMP_ERROR_NONE             (0x00U)   /*!< No error */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
#define HAL_COMP_ERROR_INVALID_CALLBACK (0x01U)   /*!< Invalid Callback error */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup COMP_Output COMP Output
  * @{
  */
#define COMP_OUTPUT_TIM2IC4                     (0x00000000U)                                               /*!< COMP2 output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR                (                                        COMP_CSR_OUTSEL_0) /*!< COMP2 output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM3IC4                     (                    COMP_CSR_OUTSEL_1                    ) /*!< COMP2 output connected to TIM3 Input Capture 4 */
#define COMP_OUTPUT_TIM3OCREFCLR                (                    COMP_CSR_OUTSEL_1 | COMP_CSR_OUTSEL_0) /*!< COMP2 output connected to TIM3 OCREF Clear */
#define COMP_OUTPUT_TIM4IC4                     (COMP_CSR_OUTSEL_2                                        ) /*!< COMP2 output connected to TIM4 Input Capture 4 */
#define COMP_OUTPUT_TIM4OCREFCLR                (COMP_CSR_OUTSEL_2                     | COMP_CSR_OUTSEL_0) /*!< COMP2 output connected to TIM4 OCREF Clear */
#define COMP_OUTPUT_TIM10IC1                    (COMP_CSR_OUTSEL_2 | COMP_CSR_OUTSEL_1                    ) /*!< COMP2 output connected to TIM10 Input Capture 1 */
#define COMP_OUTPUT_NONE                        (COMP_CSR_OUTSEL_2 | COMP_CSR_OUTSEL_1 | COMP_CSR_OUTSEL_0) /*!< COMP2 output is not connected to other peripherals */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_TIM2IC4)      || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC4)      || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC4)      || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4OCREFCLR) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM10IC1)     || \
                                ((OUTPUT) == COMP_OUTPUT_NONE)           )
/**
  * @}
  */

/** @defgroup COMP_InvertingInput COMP InvertingInput
  * @{
  */
/* Inverting Input specific to COMP2 */
#define COMP_INVERTINGINPUT_IO                  (                                      COMP_CSR_INSEL_0) /*!< External I/O (COMP2_INM connected to pin PB3) connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_VREFINT             (                   COMP_CSR_INSEL_1                   ) /*!< VREFINT connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_3_4VREFINT          (                   COMP_CSR_INSEL_1 | COMP_CSR_INSEL_0) /*!< 3/4 VREFINT connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_1_2VREFINT          (COMP_CSR_INSEL_2                                      ) /*!< 1/2 VREFINT connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_1_4VREFINT          (COMP_CSR_INSEL_2                    | COMP_CSR_INSEL_0) /*!< 1/4 VREFINT connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_DAC1                (COMP_CSR_INSEL_2 | COMP_CSR_INSEL_1                   ) /*!< DAC_OUT1 (PA4) connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_DAC2                (COMP_CSR_INSEL_2 | COMP_CSR_INSEL_1 | COMP_CSR_INSEL_0) /*!< DAC2_OUT (PA5) connected to comparator 2 inverting input */

#define IS_COMP_INVERTINGINPUT(INPUT) (((INPUT) == COMP_INVERTINGINPUT_IO)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_VREFINT)    || \
                                       ((INPUT) == COMP_INVERTINGINPUT_3_4VREFINT) || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_2VREFINT) || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_4VREFINT) || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC2)         )
/**
  * @}
  */

/** @defgroup COMP_Mode COMP Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_MODE_LOWSPEED          (0x00000000U)           /*!< Low Speed */
#define COMP_MODE_HIGHSPEED         COMP_CSR_SPEED          /*!< High Speed */

#define IS_COMP_MODE(SPEED)    (((SPEED) == COMP_MODE_LOWSPEED) || \
                                ((SPEED) == COMP_MODE_HIGHSPEED))
/**
  * @}
  */

/** @defgroup COMP_WindowMode COMP WindowMode
  * @{
  */
#define COMP_WINDOWMODE_DISABLE               (0x00000000U)  /*!< Window mode disabled: COMP1 non-inverting input is independant */
#define COMP_WINDOWMODE_ENABLE                COMP_CSR_WNDWE          /*!< Window mode enabled: COMP1 non-inverting input is no more accessible, even from ADC channel VCOMP) (connected to COMP2 non-inverting input) */

#define IS_COMP_WINDOWMODE(WINDOWMODE) (((WINDOWMODE) == COMP_WINDOWMODE_DISABLE) || \
                                        ((WINDOWMODE) == COMP_WINDOWMODE_ENABLE))
/**
  * @}
  */

/** @defgroup COMP_OutputLevel COMP OutputLevel
  * @{
  */
/* Comparator output is low when the non-inverting input is at a lower        */
/* voltage than the inverting input.                                          */
#define COMP_OUTPUTLEVEL_LOW                   (0x00000000U)

/* Comparator output is high when the non-inverting input is at a higher      */
/* voltage than the inverting input.                                          */
#define COMP_OUTPUTLEVEL_HIGH                  (0x00000001U)
/**
  * @}
  */

/** @defgroup COMP_TriggerMode COMP TriggerMode
  * @{
  */
#define COMP_TRIGGERMODE_NONE                  (0x00000000U)   /*!< No External Interrupt trigger detection */
#define COMP_TRIGGERMODE_IT_RISING             (0x00000001U)   /*!< External Interrupt Mode with Rising edge trigger detection */
#define COMP_TRIGGERMODE_IT_FALLING            (0x00000002U)   /*!< External Interrupt Mode with Falling edge trigger detection */
#define COMP_TRIGGERMODE_IT_RISING_FALLING     (0x00000003U)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */

#define IS_COMP_TRIGGERMODE(MODE)  (((MODE) == COMP_TRIGGERMODE_NONE)             || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_RISING)        || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_FALLING)       || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_RISING_FALLING)  )
/**
  * @}
  */

/** @defgroup COMP_ExtiLineEvent COMP ExtiLineEvent
  * @{
  */
#define COMP_EXTI_LINE_COMP1             EXTI_RTSR_TR21  /*!< External interrupt line 21 Connected to COMP1 */
#define COMP_EXTI_LINE_COMP2             EXTI_RTSR_TR22  /*!< External interrupt line 22 Connected to COMP2 */

/**
  * @}
  */

/** @defgroup COMP_NonInvertingInputPull COMP NonInvertingInputPull
  * @{
  */
#define COMP_NONINVERTINGINPUT_NOPULL           (0x00000000U)           /*!< No internal pull-up or pull-down resistor connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_10KPU            COMP_CSR_10KPU          /*!< Internal 10kOhm pull-up resistor connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_10KPD            COMP_CSR_10KPD          /*!< Internal 10kOhm pull-down resistor connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_400KPU           COMP_CSR_400KPU         /*!< Internal 400kOhm pull-up resistor connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_400KPD           COMP_CSR_400KPD         /*!< Internal 400kOhm pull-down resistor connected to comparator non inverting input */

#define IS_COMP_NONINVERTINGINPUTPULL(INPUT) (((INPUT) == COMP_NONINVERTINGINPUT_NOPULL) || \
                                              ((INPUT) == COMP_NONINVERTINGINPUT_10KPU)  || \
                                              ((INPUT) == COMP_NONINVERTINGINPUT_10KPD)  || \
                                              ((INPUT) == COMP_NONINVERTINGINPUT_400KPU) || \
                                              ((INPUT) == COMP_NONINVERTINGINPUT_400KPD)   )
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/** @defgroup COMP_Exported_Macro COMP Exported Macro
  * @{
  */

/** @defgroup COMP_Handle_Management  COMP Handle Management
  * @{
  */

/** @brief Reset COMP handle state
  * @param  __HANDLE__ COMP handle.
  * @retval None
  */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) do{                                                   \
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
  * @brief Enables the specified comparator
  * @param  __HANDLE__ COMP handle.
  * @retval None.
  */
#define __HAL_COMP_ENABLE(__HANDLE__)                                          \
  ( ( ((__HANDLE__)->Instance == COMP1)                                        \
    )?                                                                         \
     SET_BIT(COMP->CSR, COMP_CSR_CMP1EN)                                       \
     :                                                                         \
     MODIFY_REG(COMP->CSR, COMP_CSR_INSEL, (__HANDLE__)->Init.InvertingInput ) \
  )

/**
  * @brief Disables the specified comparator
  * @param  __HANDLE__ COMP handle.
  * @retval None.
  */
#define __HAL_COMP_DISABLE(__HANDLE__)                                         \
  ( ( ((__HANDLE__)->Instance == COMP1)                                        \
    )?                                                                         \
     CLEAR_BIT(COMP->CSR, COMP_CSR_CMP1EN)                                     \
     :                                                                         \
     CLEAR_BIT(COMP->CSR, COMP_CSR_INSEL)                                      \
  )

/** @brief  Checks whether the specified COMP flag is set or not.
  * @param  __HANDLE__ specifies the COMP Handle.
  * @param  __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg COMP_FLAG_LOCK:  lock flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_COMP_GET_FLAG(__HANDLE__, __FLAG__) (READ_BIT((__HANDLE__)->Instance->CSR, (__FLAG__)) == (__FLAG__))

/**
  * @brief  Enable the COMP1 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_RISING_EDGE()    SET_BIT(EXTI->RTSR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_RISING_EDGE()   CLEAR_BIT(EXTI->RTSR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP1 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP1 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               __HAL_COMP_COMP1_EXTI_ENABLE_RISING_EDGE(); \
                                                               __HAL_COMP_COMP1_EXTI_ENABLE_FALLING_EDGE(); \
                                                             } while(0)

/**
  * @brief  Disable the COMP1 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                               __HAL_COMP_COMP1_EXTI_DISABLE_RISING_EDGE(); \
                                                               __HAL_COMP_COMP1_EXTI_DISABLE_FALLING_EDGE(); \
                                                             } while(0)

/**
  * @brief  Enable the COMP1 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_IT()             SET_BIT(EXTI->IMR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_IT()            CLEAR_BIT(EXTI->IMR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP1 EXTI Line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_EVENT()           SET_BIT(EXTI->EMR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI Line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_EVENT()          CLEAR_BIT(EXTI->EMR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Check whether the COMP1 EXTI line flag is set or not.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP1_EXTI_GET_FLAG()              READ_BIT(EXTI->PR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Clear the the COMP1 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_CLEAR_FLAG()            WRITE_REG(EXTI->PR, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Generates a Software interrupt on COMP1 EXTI Line.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_GENERATE_SWIT()              SET_BIT(EXTI->SWIER, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP2 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_RISING_EDGE()    SET_BIT(EXTI->RTSR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_RISING_EDGE()   CLEAR_BIT(EXTI->RTSR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                               __HAL_COMP_COMP2_EXTI_ENABLE_RISING_EDGE(); \
                                                               __HAL_COMP_COMP2_EXTI_ENABLE_FALLING_EDGE(); \
                                                             } while(0)

/**
  * @brief  Disable the COMP2 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_RISING_FALLING_EDGE()   do { \
                                                               __HAL_COMP_COMP2_EXTI_DISABLE_RISING_EDGE(); \
                                                               __HAL_COMP_COMP2_EXTI_DISABLE_FALLING_EDGE(); \
                                                             } while(0)

/**
  * @brief  Enable the COMP2 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_IT()             SET_BIT(EXTI->IMR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_IT()            CLEAR_BIT(EXTI->IMR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI Line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_EVENT()           SET_BIT(EXTI->EMR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI Line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_EVENT()          CLEAR_BIT(EXTI->EMR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Check whether the COMP2 EXTI line flag is set or not.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP2_EXTI_GET_FLAG()              READ_BIT(EXTI->PR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Clear the the COMP2 EXTI flag.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_CLEAR_FLAG()            WRITE_REG(EXTI->PR, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Generates a Software interrupt on COMP1 EXTI Line.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_GENERATE_SWIT()              SET_BIT(EXTI->SWIER, COMP_EXTI_LINE_COMP2)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/

/** @defgroup COMP_Private_Macro COMP Private Macro
  * @{
  */

/**
  * @brief  Get the specified EXTI line for a comparator instance
  * @param  __INSTANCE__ specifies the COMP instance.
  * @retval value of @ref COMP_ExtiLineEvent
  */
#define COMP_GET_EXTI_LINE(__INSTANCE__)                                       \
  ( ( ((__INSTANCE__) == COMP1)                                                \
    )?                                                                         \
     (COMP_EXTI_LINE_COMP1)                                                    \
     :                                                                         \
     (COMP_EXTI_LINE_COMP2)                                                    \
  )

/**
  * @brief Select the COMP register CSR bit CMPxOUT corresponding to the
  * selected COMP instance.
  * @param __HANDLE__: COMP handle
  * @retval Comparator register CSR bit COMP_CSR_CMP1OUT or COMP_CSR_CMP2OUT
  */
#define __COMP_CSR_CMPXOUT(__HANDLE__)                                         \
  ( ( ((__HANDLE__)->Instance == COMP1)                                        \
    )?                                                                         \
     (COMP_CSR_CMP1OUT)                                                        \
     :                                                                         \
     (COMP_CSR_CMP2OUT)                                                        \
  )

/**
  * @brief Verification of COMP state: enabled or disabled
  * @param __HANDLE__: COMP handle
  * @retval SET (COMP enabled) or RESET (COMP disabled)
  */
#define __COMP_IS_ENABLED(__HANDLE__)                                          \
  ( ( ((__HANDLE__)->Instance == COMP1)                                        \
    )?                                                                         \
     (((READ_BIT(COMP->CSR , COMP_CSR_CMP1EN) == COMP_CSR_CMP1EN)              \
      ) ? SET : RESET)                                                         \
     :                                                                         \
     (((READ_BIT(COMP->CSR , COMP_CSR_INSEL) != RESET)                         \
      ) ? SET : RESET)                                                         \
  )

/**
  * @}
  */


/* Include COMP HAL Extension module */
#include "stm32l1xx_hal_comp_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_Exported_Functions
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
/** @addtogroup COMP_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_DeInit (COMP_HandleTypeDef *hcomp);
void HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp);
void HAL_COMP_MspDeInit(COMP_HandleTypeDef *hcomp);

#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_COMP_RegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID, pCOMP_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_COMP_UnRegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @}
  */

/* I/O operation functions  *****************************************************/
/** @addtogroup COMP_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Start_IT(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop_IT(COMP_HandleTypeDef *hcomp);
void HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/* Peripheral Control functions  ************************************************/
/** @addtogroup COMP_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef *hcomp);
uint32_t HAL_COMP_GetOutputLevel(COMP_HandleTypeDef *hcomp);

/* Callback in Interrupt mode */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
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

#endif /* __STM32L1xx_HAL_COMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
