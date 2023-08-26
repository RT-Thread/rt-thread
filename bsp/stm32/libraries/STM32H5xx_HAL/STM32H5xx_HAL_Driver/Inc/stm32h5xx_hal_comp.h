/**
  **********************************************************************************************************************
  * @file    stm32h5xx_hal_comp.h
  * @author  MCD Application Team
  * @brief   Header file of COMP HAL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H5xx_HAL_COMP_H
#define STM32H5xx_HAL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h5xx_hal_def.h"
#include "stm32h5xx_ll_exti.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */
#if defined (COMP1)

/** @addtogroup COMP
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup COMP_Exported_Types COMP Exported Types
  * @{
  */

/**
  * @brief  COMP Init structure definition
  */
typedef struct
{
  uint32_t Mode;               /*!< Set comparator operating mode to adjust power and speed.
                                    Note: For the characteristics of comparator power modes
                                          (propagation delay and power consumption), refer to device datasheet.
                                    This parameter can be a value of @ref COMP_PowerMode */

  uint32_t InputPlus;          /*!< Set comparator input plus (non-inverting input).
                                    This parameter can be a value of @ref COMP_InputPlus */

  uint32_t InputMinus;         /*!< Set comparator input minus (inverting input).
                                    This parameter can be a value of @ref COMP_InputMinus */

  uint32_t Hysteresis;         /*!< Set comparator hysteresis mode of the input minus.
                                    This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t OutputPol;          /*!< Set comparator output polarity.
                                    This parameter can be a value of @ref COMP_OutputPolarity
                                    Note: Specific to comparator of this STM32 series: comparator output
                                          triggers interruption on high level. HAL_COMP_Start_x functions
                                          can change output polarity depending on initial output level. */

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
  HAL_COMP_STATE_RESET        = 0x00,                       /*!< COMP not yet initialized                             */
  HAL_COMP_STATE_RESET_LOCKED = (HAL_COMP_STATE_RESET | \
                                 COMP_STATE_BITFIELD_LOCK), /*!< COMP not yet initialized and configuration is locked */
  HAL_COMP_STATE_READY        = 0x01,                       /*!< COMP initialized and ready for use                   */
  HAL_COMP_STATE_READY_LOCKED = (HAL_COMP_STATE_READY | \
                                 COMP_STATE_BITFIELD_LOCK), /*!< COMP initialized but configuration is locked         */
  HAL_COMP_STATE_BUSY         = 0x02,                       /*!< COMP is running                                      */
  HAL_COMP_STATE_BUSY_LOCKED  = (HAL_COMP_STATE_BUSY | \
                                 COMP_STATE_BITFIELD_LOCK)  /*!< COMP is running and configuration is locked          */

} HAL_COMP_StateTypeDef;

/**
  * @brief  COMP Handle Structure definition
  */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
typedef struct __COMP_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
{
  COMP_TypeDef       *Instance;                                   /*!< Register base address    */
  COMP_InitTypeDef   Init;                                        /*!< COMP required parameters */
  HAL_LockTypeDef    Lock;                                        /*!< Locking object           */
  __IO HAL_COMP_StateTypeDef  State;                              /*!< COMP communication state */
  __IO uint32_t      ErrorCode;                                   /*!< COMP error code          */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
  void (* TriggerCallback)(struct __COMP_HandleTypeDef *hcomp);   /*!< COMP trigger callback    */
  void (* MspInitCallback)(struct __COMP_HandleTypeDef *hcomp);   /*!< COMP Msp Init callback   */
  void (* MspDeInitCallback)(struct __COMP_HandleTypeDef *hcomp); /*!< COMP Msp DeInit callback */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
  uint8_t            InterruptAutoRearm;                          /*!< COMP interrupt auto rearm setting */
} COMP_HandleTypeDef;

#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
/**
  * @brief  HAL COMP Callback ID enumeration definition
  */
typedef enum
{
  HAL_COMP_TRIGGER_CB_ID   = 0x00U,  /*!< COMP trigger callback ID */
  HAL_COMP_MSPINIT_CB_ID   = 0x01U,  /*!< COMP Msp Init callback ID */
  HAL_COMP_MSPDEINIT_CB_ID = 0x02U   /*!< COMP Msp DeInit callback ID */

} HAL_COMP_CallbackIDTypeDef;

/**
  * @brief  HAL COMP Callback pointer definition
  */
typedef  void (*pCOMP_CallbackTypeDef)(COMP_HandleTypeDef *hcomp); /*!< pointer to a COMP callback function */

#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup COMP_Exported_Constants COMP Exported Constants
  * @{
  */

/** @defgroup COMP_Error_Code COMP Error Code
  * @{
  */
#define HAL_COMP_ERROR_NONE             (0x00UL)   /*!< No error */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
#define HAL_COMP_ERROR_INVALID_CALLBACK (0x01U)   /*!< Invalid Callback error */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup COMP_PowerMode COMP power mode
  * @{
  */
/* Note: For the characteristics of comparator power modes                    */
/*       (propagation delay and power consumption),                           */
/*       refer to device datasheet.                                           */
#define COMP_POWERMODE_HIGHSPEED       (0x00000000UL)         /*!< High Speed */
#define COMP_POWERMODE_MEDIUMSPEED     (COMP_CFGR1_PWRMODE_0) /*!< Medium Speed */
#define COMP_POWERMODE_ULTRALOWPOWER   (COMP_CFGR1_PWRMODE)   /*!< Ultra-low power mode */
/**
  * @}
  */

/** @defgroup COMP_InputPlus COMP input plus (non-inverting input)
  * @{
  */
#define COMP_INPUT_PLUS_IO1            (0x00000000UL)         /*!< Comparator input plus connected to IO1 (pin PB0) */
#define COMP_INPUT_PLUS_IO2            (COMP_CFGR2_INPSEL0)   /*!< Comparator input plus connected to IO2 (pin PA0) */
#define COMP_INPUT_PLUS_IO3            (COMP_CFGR1_INPSEL1)   /*!< Comparator input plus connected to IO3 (pin PB2) */
#define COMP_INPUT_PLUS_DAC1_CH1       (COMP_CFGR1_INPSEL2)   /*!< Comparator input plus connected to (DAC1_CH1) */
/**
  * @}
  */

/** @defgroup COMP_InputMinus COMP input minus (inverting input)
  * @{
  */
#define COMP_INPUT_MINUS_1_4VREFINT  (COMP_CFGR1_SCALEN |\
                                      COMP_CFGR1_BRGEN)       /*!< Comparator input minus connected to 1/4 VrefInt    */
#define COMP_INPUT_MINUS_1_2VREFINT  (COMP_CFGR1_INMSEL_0 |\
                                      COMP_CFGR1_SCALEN |\
                                      COMP_CFGR1_BRGEN)       /*!< Comparator input minus connected to 1/2 VrefInt    */
#define COMP_INPUT_MINUS_3_4VREFINT  (COMP_CFGR1_INMSEL_1 |\
                                      COMP_CFGR1_SCALEN |\
                                      COMP_CFGR1_BRGEN)       /*!< Comparator input minus connected to 3/4 VrefInt    */
#define COMP_INPUT_MINUS_VREFINT     (COMP_CFGR1_INMSEL_1 |\
                                      COMP_CFGR1_INMSEL_0 |\
                                      COMP_CFGR1_SCALEN)      /*!< Comparator input minus connected to VrefInt        */
#define COMP_INPUT_MINUS_DAC1_CH1    (COMP_CFGR1_INMSEL_2)    /*!< Comparator input minus connected to DAC1 channel 1 */
#define COMP_INPUT_MINUS_IO1         (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_0)    /*!< Comparator input minus connected to IO1 (pin PC4)  */
#define COMP_INPUT_MINUS_IO2         (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_1)    /*!< Comparator input minus connected to IO2 (pin PB1)  */
#define COMP_INPUT_MINUS_IO3         (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_1 |\
                                      COMP_CFGR1_INMSEL_0)    /*!< Comparator input minus connected to IO3 (pin PA5)  */
#define COMP_INPUT_MINUS_TEMPSENSOR  (COMP_CFGR1_INMSEL_3)    /*!< Comparator input minus connected to internal
                                     temperature sensor (also accessible through ADC peripheral) */
#define COMP_INPUT_MINUS_VBAT        (COMP_CFGR1_INMSEL_3 |\
                                      COMP_CFGR1_INMSEL_0)    /*!< Comparator input minus connected to Vbat/4:
                                     Vbat voltage through a divider ladder of factor 1/4 to have input voltage
                                     always below Vdda. */

/**
  * @}
  */

/** @defgroup COMP_Hysteresis COMP hysteresis
  * @{
  */
#define COMP_HYSTERESIS_NONE           (0x00000000UL)                       /*!< No hysteresis */
#define COMP_HYSTERESIS_LOW            (COMP_CFGR1_HYST_0)                  /*!< Hysteresis level low */
#define COMP_HYSTERESIS_MEDIUM         (COMP_CFGR1_HYST_1)                  /*!< Hysteresis level medium */
#define COMP_HYSTERESIS_HIGH           (COMP_CFGR1_HYST_0 | COMP_CFGR1_HYST_1) /*!< Hysteresis level high */
/**
  * @}
  */

/** @defgroup COMP_OutputPolarity COMP output Polarity
  * @{
  */
#define COMP_OUTPUTPOL_NONINVERTED     (0x00000000UL)          /*!< COMP output level is not inverted (comparator output
                                                                    is high when the input plus is at a higher voltage
                                                                    than the input minus) */
#define COMP_OUTPUTPOL_INVERTED        (COMP_CFGR1_POLARITY)   /*!< COMP output level is inverted (comparator output is
                                                                    low when the input plus is at a higher voltage than
                                                                    the input minus) */
/**
  * @}
  */

/** @defgroup COMP_BlankingSrce  COMP blanking source
  * @{
  */
#define COMP_BLANKINGSRC_NONE            (0x00000000UL)           /*!< Comparator output without blanking */
#define COMP_BLANKINGSRC_TIM1_OC5        (COMP_CFGR1_BLANKING_0)  /*!< TIM1 OC5 selected as blanking source */
#define COMP_BLANKINGSRC_TIM2_OC3        (COMP_CFGR1_BLANKING_1)  /*!< TIM2 OC3 selected as blanking source */
#define COMP_BLANKINGSRC_TIM3_OC3        (COMP_CFGR1_BLANKING_0 |\
                                          COMP_CFGR1_BLANKING_1)  /*!< TIM3 OC3 selected as blanking source */
#define COMP_BLANKINGSRC_TIM3_OC4        (COMP_CFGR1_BLANKING_2)  /*!< TIM3 OC4 selected as blanking source */
#define COMP_BLANKINGSRC_LPTIM1_OC2      (COMP_CFGR1_BLANKING_2 |\
                                          COMP_CFGR1_BLANKING_0)  /*!< LPTIM1 OC2 selected as blanking source */
#define COMP_BLANKINGSRC_LPTIM2_OC2      (COMP_CFGR1_BLANKING_2 |\
                                          COMP_CFGR1_BLANKING_1)  /*!< LPTIM2 OC2 selected as blanking source */
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
#define COMP_TRIGGERMODE_NONE                 (0x00000000UL)          /*!< Comparator output triggering no External
                                                                           Interrupt Line */
#define COMP_TRIGGERMODE_IT_RISING_FALLING    (COMP_EXTI_IT |\
                                               COMP_EXTI_RISING |\
                                               COMP_EXTI_FALLING)     /*!< Comparator output triggering interrupt
                                              on rising and falling edges.
                                              Note: Specific to comparator of this STM32 series: comparator output
                                                    triggers interruption on high level. HAL_COMP_Start_x functions
                                                    can change output polarity depending on initial output level. */
/**
  * @}
  */

/** @defgroup COMP_Flag COMP Flag
  * @{
  */
#define COMP_FLAG_C1I           COMP_SR_C1IF           /*!< Comparator 1 Interrupt Flag */
#define COMP_FLAG_LOCK          COMP_CFGR1_LOCK        /*!< Lock flag                   */
/**
  * @}
  */

/** @defgroup COMP_IT_CLEAR_Flags  COMP Interruption Clear Flags
  * @{
  */
#define COMP_CLEAR_C1IF          COMP_ICFR_CC1IF     /*!< Clear Comparator 1 Interrupt Flag */
/**
  * @}
  */

/** @defgroup COMP_Interrupts_Definitions COMP Interrupts Definitions
  * @{
  */
#define COMP_IT_EN               COMP_CFGR1_ITEN
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
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
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) do{                                                  \
                                                      (__HANDLE__)->State = HAL_COMP_STATE_RESET;      \
                                                      (__HANDLE__)->MspInitCallback = NULL;            \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;          \
                                                    } while(0)
#else
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_COMP_STATE_RESET)
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @brief Clear COMP error code (set it to no error code "HAL_COMP_ERROR_NONE").
  * @param __HANDLE__ COMP handle
  * @retval None
  */
#define COMP_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_COMP_ERROR_NONE)

/**
  * @brief  Enable the specified comparator.
  * @param  __HANDLE__ COMP handle
  * @retval None
  */
#define __HAL_COMP_ENABLE(__HANDLE__)        SET_BIT((__HANDLE__)->Instance->CFGR1, COMP_CFGR1_EN)

/**
  * @brief  Disable the specified comparator.
  * @param  __HANDLE__ COMP handle
  * @retval None
  */
#define __HAL_COMP_DISABLE(__HANDLE__)       CLEAR_BIT((__HANDLE__)->Instance->CFGR1, COMP_CFGR1_EN)

/**
  * @brief  Lock the specified comparator configuration.
  * @note   Using this macro induce HAL COMP handle state machine being no
  *         more in line with COMP instance state.
  *         To keep HAL COMP handle state machine updated, it is recommended
  *         to use function "HAL_COMP_Lock')".
  * @param  __HANDLE__ COMP handle
  * @retval None
  */
#define __HAL_COMP_LOCK(__HANDLE__)         SET_BIT((__HANDLE__)->Instance->CFGR1, COMP_CFGR1_LOCK)

/**
  * @brief  Check whether the specified comparator is locked.
  * @param  __HANDLE__  COMP handle
  * @retval Value 0 if COMP instance is not locked, value 1 if COMP instance is locked
  */
#define __HAL_COMP_IS_LOCKED(__HANDLE__)   (READ_BIT((__HANDLE__)->Instance->CFGR1, COMP_CFGR1_LOCK) == COMP_CFGR1_LOCK)

/**
  * @}
  */

/** @defgroup COMP_Exti_Management  COMP external interrupt line management
  * @{
  */

/** @brief  Checks if the specified COMP interrupt source is enabled or disabled.
  * @param  __HANDLE__ specifies the COMP Handle.
  *         This parameter can be COMP1.
  * @param  __INTERRUPT__ specifies the COMP interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg COMP_IT_EN Comparator interrupt enable
  *
  * @retval State of interruption (TRUE or FALSE)
  */
#define __HAL_COMP_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) \
  ((((__HANDLE__)->Instance->CFGR1 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks whether the specified COMP flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg COMP_FLAG_C1I Comparator 1 Interrupt Flag
  *            @retval State of flag (TRUE or FALSE)
  */
#define __HAL_COMP_GET_FLAG(__FLAG__)     ((COMP1->SR & (__FLAG__)) == (__FLAG__))

/** @brief  Clears the specified COMP pending flag.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_CLEAR_C1IF Clear Comparator 1 Interrupt Flag
  * @retval None
  */
#define __HAL_COMP_CLEAR_FLAG(__FLAG__)   (COMP1->ICFR = (__FLAG__))

/** @brief  Clear the COMP C1I  flag.
  * @retval None
  */
#define __HAL_COMP_CLEAR_C1IFLAG()   __HAL_COMP_CLEAR_FLAG( COMP_CLEAR_C1IF)

/** @brief  Enable the specified COMP interrupt.
  * @param  __HANDLE__ specifies the COMP Handle.
  * @param  __INTERRUPT__ specifies the COMP interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg COMP_CFGR1_ITEN Comparator  interrupt
  * @retval None
  */
#define __HAL_COMP_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((__HANDLE__)->Instance->CFGR1) |= (__INTERRUPT__) )

/** @brief  Disable the specified COMP interrupt.
  * @param  __HANDLE__ specifies the COMP Handle.
  * @param  __INTERRUPT__ specifies the COMP interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg COMP_CFGR1_ITEN Comparator  interrupt
  * @retval None
  */
#define __HAL_COMP_DISABLE_IT(__HANDLE__,__INTERRUPT__) (((__HANDLE__)->Instance->CFGR1) &= ~(__INTERRUPT__))

/**
  * @}
  */

/**
  * @}
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup COMP_Private_Constants COMP Private Constants
  * @{
  */

/** @defgroup COMP_ExtiLine COMP EXTI Lines
  * @{
  */
#define COMP_EXTI_LINE_COMP1           (EXTI_IMR1_IM29)  /*!< EXTI line 29 connected to COMP1 output */
/**
  * @}
  */

/** @defgroup COMP_ExtiLine COMP EXTI Lines
  * @{
  */
#define COMP_EXTI_IT                        (0x00000001UL)  /*!< EXTI line event with interruption */
#define COMP_EXTI_RISING                    (0x00000010UL)  /*!< EXTI line event on rising edge */
#define COMP_EXTI_FALLING                   (0x00000020UL)  /*!< EXTI line event on falling edge */
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
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
#define COMP_GET_EXTI_LINE(__INSTANCE__)    (COMP_EXTI_LINE_COMP1)
/**
  * @}
  */

/** @defgroup COMP_IS_COMP_Private_Definitions COMP private macros to check input parameters
  * @{
  */
#define IS_COMP_POWERMODE(__POWERMODE__)    (((__POWERMODE__) == COMP_POWERMODE_HIGHSPEED)    || \
                                             ((__POWERMODE__) == COMP_POWERMODE_MEDIUMSPEED)  || \
                                             ((__POWERMODE__) == COMP_POWERMODE_ULTRALOWPOWER)  )

#define IS_COMP_INPUT_PLUS(__COMP_INSTANCE__, __INPUT_PLUS__) (((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO1) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO2) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO3) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_DAC1_CH1))

#define IS_COMP_INPUT_MINUS(__COMP_INSTANCE__, __INPUT_MINUS__) (((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_4VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_2VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_3_4VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_VREFINT)    || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)   || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO1)        || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO2)        || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO3)        || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_TEMPSENSOR) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_VBAT))

#define IS_COMP_HYSTERESIS(__HYSTERESIS__)  (((__HYSTERESIS__) == COMP_HYSTERESIS_NONE)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_LOW)    || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_MEDIUM) || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_HIGH))

#define IS_COMP_OUTPUTPOL(__POL__)          (((__POL__) == COMP_OUTPUTPOL_NONINVERTED) || \
                                             ((__POL__) == COMP_OUTPUTPOL_INVERTED))

#define IS_COMP_BLANKINGSRCE(__SOURCE__)    (((__SOURCE__) == COMP_BLANKINGSRC_NONE)       || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5)   || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3)   || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3)   || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_TIM3_OC4)   || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_LPTIM1_OC2) || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_LPTIM2_OC2))


#define IS_COMP_TRIGGERMODE(__MODE__)       (((__MODE__) == COMP_TRIGGERMODE_NONE)                 || \
                                             ((__MODE__) == COMP_TRIGGERMODE_IT_RISING_FALLING))

#define IS_COMP_OUTPUT_LEVEL(__OUTPUT_LEVEL__) (((__OUTPUT_LEVEL__) == COMP_OUTPUT_LEVEL_LOW)     || \
                                                ((__OUTPUT_LEVEL__) == COMP_OUTPUT_LEVEL_HIGH))

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup COMP_Exported_Functions
  * @{
  */

/** @addtogroup COMP_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions */
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_MspDeInit(COMP_HandleTypeDef *hcomp);
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
/* Callbacks Register/UnRegister functions */
HAL_StatusTypeDef HAL_COMP_RegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID,
                                            pCOMP_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_COMP_UnRegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
/**
  * @}
  */

/* IO operation functions */
/** @addtogroup COMP_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Start_IT_OneShot(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Start_IT_AutoRearm(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop_IT(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp);

/**
  * @}
  */

/* Peripheral Control functions */
/** @addtogroup COMP_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef *hcomp);
uint32_t          HAL_COMP_GetOutputLevel(const COMP_HandleTypeDef *hcomp);
/* Callback in interrupt mode */
void              HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/* Peripheral State functions */
/** @addtogroup COMP_Exported_Functions_Group4
  * @{
  */
HAL_COMP_StateTypeDef HAL_COMP_GetState(const COMP_HandleTypeDef *hcomp);
uint32_t              HAL_COMP_GetError(const COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* COMP1 */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_COMP_H */
