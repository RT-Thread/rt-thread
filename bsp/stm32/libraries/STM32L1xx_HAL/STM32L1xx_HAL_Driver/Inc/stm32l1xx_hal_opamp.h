/**
  ******************************************************************************
  * @file    stm32l1xx_hal_opamp.h
  * @author  MCD Application Team
  * @brief   Header file of OPAMP HAL module.
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
#ifndef STM32L1xx_HAL_OPAMP_H
#define STM32L1xx_HAL_OPAMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L151xDX) || defined (STM32L152xE) || defined (STM32L152xDX) || defined (STM32L162xE) || defined (STM32L162xDX) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup OPAMP
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

/** @defgroup OPAMP_Exported_Types OPAMP Exported Types
  * @{
  */

/** 
  * @brief  OPAMP Init structure definition  
  */
  
typedef struct
{
  uint32_t PowerSupplyRange;            /*!< Specifies the power supply range: above or under 2.4V.
                                             This parameter must be a value of @ref OPAMP_PowerSupplyRange
                                             Caution: This parameter is common to all OPAMP instances: a modification of this parameter for the selected OPAMP impacts the other OPAMP instances. */

  uint32_t PowerMode;                   /*!< Specifies the power mode Normal or Low-Power.
                                             This parameter must be a value of @ref OPAMP_PowerMode */

  uint32_t Mode;                        /*!< Specifies the OPAMP mode
                                             This parameter must be a value of @ref OPAMP_Mode 
                                             mode is either Standalone or Follower */

  uint32_t InvertingInput;              /*!< Specifies the inverting input in Standalone mode
                                               - In Standalone mode:   i.e when mode is OPAMP_STANDALONE_MODE
                                                 This parameter must be a value of @ref OPAMP_InvertingInput 
                                                 InvertingInput is either VM0 or VM1
                                               - In Follower mode:     i.e when mode is OPAMP_FOLLOWER_MODE
                                                 This parameter is Not Applicable */ 

  uint32_t NonInvertingInput;           /*!< Specifies the non inverting input of the opamp:
                                             This parameter must be a value of @ref OPAMP_NonInvertingInput
                                             Note: Non-inverting input availability depends on OPAMP instance:
                                                   OPAMP1: Non-inverting input is either IO0, DAC_Channel1
                                                   OPAMP2: Non-inverting input is either IO0, DAC_Channel1, DAC_Channel2
                                                   OPAMP3: Non-inverting input is either IO0, DAC_Channel2 (OPAMP3 availability depends on STM32L1 devices) */

  uint32_t UserTrimming;                /*!< Specifies the trimming mode 
                                             This parameter must be a value of @ref OPAMP_UserTrimming 
                                             UserTrimming is either factory or user trimming.
                                             Caution: This parameter is common to all OPAMP instances: a modification of this parameter for the selected OPAMP impacts the other OPAMP instances. */

  uint32_t TrimmingValueP;              /*!< Specifies the offset trimming value (PMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 0 and Max_Data = 30 (Trimming value 31 is forbidden)
                                             16 is typical default value */
  
  uint32_t TrimmingValueN;              /*!< Specifies the offset trimming value (NMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 0 and Max_Data = 30 (Trimming value 31 is forbidden)
                                             16 is typical default value */
  
  uint32_t TrimmingValuePLowPower;      /*!< Specifies the offset trimming value (PMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 0 and Max_Data = 30 (Trimming value 31 is forbidden)
                                             16 is typical default value */

  uint32_t TrimmingValueNLowPower;      /*!< Specifies the offset trimming value (NMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 0 and Max_Data = 30 (Trimming value 31 is forbidden)
                                             16 is typical default value */

}OPAMP_InitTypeDef;

/** 
  * @brief  HAL State structures definition  
  */ 

typedef enum
{
  HAL_OPAMP_STATE_RESET               = 0x00000000, /*!< OPAMP is not yet Initialized          */
  
  HAL_OPAMP_STATE_READY               = 0x00000001, /*!< OPAMP is initialized and ready for use */
  HAL_OPAMP_STATE_CALIBBUSY           = 0x00000002, /*!< OPAMP is enabled in auto calibration mode */
 
  HAL_OPAMP_STATE_BUSY                = 0x00000004, /*!< OPAMP is enabled and running in normal mode */                                                                           
  HAL_OPAMP_STATE_BUSYLOCKED          = 0x00000005  /*!< OPAMP is locked
                                                         only system reset allows reconfiguring the opamp. */
    
}HAL_OPAMP_StateTypeDef;

/** 
  * @brief OPAMP Handle Structure definition
  */ 
#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
typedef struct __OPAMP_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */
{
  OPAMP_TypeDef       *Instance;                    /*!< OPAMP instance's registers base address   */
  OPAMP_InitTypeDef   Init;                         /*!< OPAMP required parameters */
  HAL_StatusTypeDef Status;                         /*!< OPAMP peripheral status   */
  HAL_LockTypeDef   Lock;                           /*!< Locking object          */
  __IO HAL_OPAMP_StateTypeDef  State;               /*!< OPAMP communication state */
  
#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
void (* MspInitCallback)                (struct __OPAMP_HandleTypeDef *hopamp);
void (* MspDeInitCallback)              (struct __OPAMP_HandleTypeDef *hopamp);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

} OPAMP_HandleTypeDef;

/** 
  * @brief HAl_OPAMP_TrimmingValueTypeDef definition 
  */ 

typedef  uint32_t HAL_OPAMP_TrimmingValueTypeDef;

/**
  * @}
  */

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL OPAMP Callback ID enumeration definition
  */
typedef enum
{
  HAL_OPAMP_MSPINIT_CB_ID                     = 0x01U,  /*!< OPAMP MspInit Callback ID           */
  HAL_OPAMP_MSPDEINIT_CB_ID                   = 0x02U,  /*!< OPAMP MspDeInit Callback ID         */
  HAL_OPAMP_ALL_CB_ID                         = 0x03U   /*!< OPAMP All ID                        */
}HAL_OPAMP_CallbackIDTypeDef;

/**
  * @brief  HAL OPAMP Callback pointer definition
  */
typedef void (*pOPAMP_CallbackTypeDef)(OPAMP_HandleTypeDef *hopamp);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */


/* Exported constants --------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Constants OPAMP Exported Constants
  * @{
  */

/**
  * OTR register Mask 
  */
#define OPAMP_TRIM_VALUE_MASK   OPAMP_OTR_AO1_OPT_OFFSET_TRIM_LOW
    
/**
  * CSR register Mask 
  */
#define OPAMP_CSR_INSTANCE_OFFSET   ( 8U) /* Offset of each OPAMP instance into register CSR */
#define OPAMP_OTR_INSTANCE_OFFSET   (10U) /* Offset of each OPAMP instance into register OTR */
    
        
/** @defgroup OPAMP_Mode OPAMP Mode
  * @{
  */
#define OPAMP_STANDALONE_MODE            0x00000000U  /*!< OPAMP standalone mode */
#define OPAMP_FOLLOWER_MODE              0x00000001U  /*!< OPAMP follower mode */

/**
  * @}
  */

/** @defgroup OPAMP_NonInvertingInput OPAMP NonInvertingInput
  * @{
  */
#define OPAMP_NONINVERTINGINPUT_IO0       0x00000000U   /*!< Comparator non-inverting input connected to dedicated IO pin low-leakage */
#define OPAMP_NONINVERTINGINPUT_DAC_CH1   0x00000001U   /*!< Comparator non-inverting input connected internally to DAC channel 1. Available only on OPAMP1 and OPAMP2. */
#define OPAMP_NONINVERTINGINPUT_DAC_CH2   0x00000002U   /*!< Comparator non-inverting input connected internally to DAC channel 2. Available only on OPAMP2 and OPAMP3 (OPAMP3 availability depends on STM32L1 devices). */

/**
  * @}
  */

/** @defgroup OPAMP_InvertingInput OPAMP InvertingInput
  * @{
  */
/* Note: Literal "OPAMP_SEC_INVERTINGINPUT_IO1" is a legacy naming of "OPAMP_INVERTINGINPUT_IO1". It is equivalent and must be replaced by "OPAMP_INVERTINGINPUT_IO1". */
#define OPAMP_INVERTINGINPUT_IO0         0x00000000U   /*!< Comparator inverting input connected to dedicated IO pin low-leakage */
#define OPAMP_INVERTINGINPUT_IO1         0x00000001U   /*!< Comparator inverting input connected to alternative IO pin available on some device packages */

/**
  * @}
  */

/** @defgroup OPAMP_PowerMode OPAMP PowerMode
  * @{
  */
#define OPAMP_POWERMODE_NORMAL        0x00000000U
#define OPAMP_POWERMODE_LOWPOWER      0x00000001U

/**
  * @}
  */

/** @defgroup OPAMP_PowerSupplyRange OPAMP PowerSupplyRange
  * @{
  */
#define OPAMP_POWERSUPPLY_LOW          0x00000000U             /*!< Power supply range low (VDDA lower than 2.4V) */
#define OPAMP_POWERSUPPLY_HIGH         OPAMP_CSR_AOP_RANGE     /*!< Power supply range high (VDDA higher than 2.4V) */

/**
  * @}
  */ 

/** @defgroup OPAMP_UserTrimming OPAMP User Trimming
  * @{
  */
#define OPAMP_TRIMMING_FACTORY         0x00000000U                           /*!< Factory trimming */
#define OPAMP_TRIMMING_USER           OPAMP_OTR_OT_USER                      /*!< User trimming */

/**
  * @}
  */

/** @defgroup OPAMP_FactoryTrimming OPAMP FactoryTrimming
  * @{
  */
#define OPAMP_FACTORYTRIMMING_DUMMY    0xFFFFFFFFU                                      /*!< Dummy value if trimming value could not be retrieved */

#define OPAMP_FACTORYTRIMMING_P        0U                                               /*!< Offset trimming P */
#define OPAMP_FACTORYTRIMMING_N        POSITION_VAL(OPAMP_OTR_AO1_OPT_OFFSET_TRIM_HIGH) /*!< Offset trimming N */

/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup OPAMP_Private_Constants OPAMP Private Constants
  * @{
  */

/* Offset trimming time: during calibration, minimum time needed between two  */
/* steps to have 1 mV accuracy.                                               */
/* Refer to datasheet, electrical characteristics: parameter tOFFTRIM Typ=1ms.*/
/* Unit: ms.                                                                  */
#define OPAMP_TRIMMING_DELAY               ((uint32_t) 1)

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup OPAMP_Private_Macro OPAMP Private Macro
  * @{
  */

/** @brief Reset OPAMP handle state
  * @param  __HANDLE__ OPAMP handle.
  * @retval None
  */
#define __HAL_OPAMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_OPAMP_STATE_RESET)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/

/** @defgroup OPAMP_Private_Macro OPAMP Private Macro
  * @{
  */

/**
  * @brief Select the OPAMP bit OPAxPD (power-down) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_OPAXPD(__HANDLE__)                                           \
  (OPAMP_CSR_OPA1PD << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))
    
/**
  * @brief Select the OPAMP bit S3SELx (switch 3) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_S3SELX(__HANDLE__)                                           \
  (OPAMP_CSR_S3SEL1 << ((OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET) & 0x1fU))

/**
  * @brief Select the OPAMP bit S4SELx (switch 4) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_S4SELX(__HANDLE__)                                           \
  (OPAMP_CSR_S4SEL1 << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit S5SELx (switch 5) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_S5SELX(__HANDLE__)                                           \
  (OPAMP_CSR_S5SEL1 << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit S3SELx (switch 6) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_S6SELX(__HANDLE__)                                           \
  (OPAMP_CSR_S6SEL1 << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit OPAxCAL_L (offset calibration for differential 
  * pair P) corresponding to the selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_OPAXCAL_L(__HANDLE__)                                        \
  (OPAMP_CSR_OPA1CAL_L << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))
    
/**
  * @brief Select the OPAMP bit OPAxCAL_H (offset calibration for differential 
  * pair N) corresponding to the selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_OPAXCAL_H(__HANDLE__)                                        \
  (OPAMP_CSR_OPA1CAL_H << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit OPAxLPM (low power mode) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_OPAXLPM(__HANDLE__)                                          \
  (OPAMP_CSR_OPA1LPM << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))
    
/**
  * @brief Select the OPAMP bits of all switches corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_ALL_SWITCHES(__HANDLE__)                                     \
  ( ( ((__HANDLE__)->Instance != OPAMP2)                                       \
    )?                                                                         \
     (                                                                         \
       ((OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1) << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))  \
       |                                                                       \
       (OPAMP_CSR_ANAWSEL1 << (OPAMP_INSTANCE_DECIMAL(__HANDLE__)))        \
     )                                                                         \
    :                                                                          \
     (                                                                         \
       ((OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1) << (OPAMP_INSTANCE_DECIMAL(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))  \
       |                                                                       \
       (OPAMP_CSR_ANAWSEL1 << (OPAMP_INSTANCE_DECIMAL(__HANDLE__)))        \
       |                                                                       \
       (OPAMP_CSR_S7SEL2)                                                      \
     )                                                                         \
  )
    
/**
  * @brief Select the OPAMP bit ANAWSELx (switch SanA) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_ANAWSELX(__HANDLE__)                                         \
  (OPAMP_CSR_ANAWSEL1 << (OPAMP_INSTANCE_DECIMAL(__HANDLE__)))

/**
  * @brief Select the OPAMP bit OPAxCALOUT in function of the selected 
  * OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define OPAMP_CSR_OPAXCALOUT(__HANDLE__)                                       \
  (OPAMP_CSR_OPA1CALOUT << (OPAMP_INSTANCE_DECIMAL(__HANDLE__)))

/**
  * @brief Select the OPAMP trimming bits position value (position of LSB) 
  * in register OPAMP_OTR or register OPAMP_LPOTR in function of the selected
  * OPAMP instance and the transistors differential pair high (PMOS) or 
  * low (NMOS).
  * @param __HANDLE__: OPAMP handle
  * @param __TRIM_HIGH_LOW__: transistors differential pair high or low.
  * Must be a value of @ref OPAMP_FactoryTrimming.
  * @retval None
  */
#define OPAMP_OFFSET_TRIM_BITSPOSITION(__HANDLE__, __TRIM_HIGH_LOW__)          \
  ((OPAMP_INSTANCE_DECIMAL((__HANDLE__)) * OPAMP_OTR_INSTANCE_OFFSET) + (__TRIM_HIGH_LOW__))
    
/**
  * @brief Shift the OPAMP trimming bits to register OPAMP_OTR or register 
  * OPAMP_LPOTR in function of the selected OPAMP instance and the transistors
  * differential pair high (PMOS) or low (NMOS).
  * @param __HANDLE__: OPAMP handle
  * @param __TRIM_HIGH_LOW__: transistors differential pair high or low.
  * Must be a value of @ref OPAMP_FactoryTrimming.
  * @param __TRIMMING_VALUE__: Trimming value
  * @retval None
  */
#define OPAMP_OFFSET_TRIM_SET(__HANDLE__, __TRIM_HIGH_LOW__, __TRIMMING_VALUE__) \
  ((__TRIMMING_VALUE__) << (OPAMP_OFFSET_TRIM_BITSPOSITION((__HANDLE__), (__TRIM_HIGH_LOW__))))
    
/**
  * @brief Check that trimming value is within correct range
  * @param TRIMMINGVALUE: OPAMP trimming value
  * @retval None
  */
#define IS_OPAMP_TRIMMINGVALUE(TRIMMINGVALUE) ((TRIMMINGVALUE) <= 30U)

#define IS_OPAMP_FUNCTIONAL_NORMALMODE(INPUT) (((INPUT) == OPAMP_STANDALONE_MODE) || \
                                               ((INPUT) == OPAMP_FOLLOWER_MODE))

#define IS_OPAMP_INVERTING_INPUT(INPUT) (((INPUT) == OPAMP_INVERTINGINPUT_IO0) || \
                                         ((INPUT) == OPAMP_INVERTINGINPUT_IO1)   )

#define IS_OPAMP_POWERMODE(TRIMMING) (((TRIMMING) == OPAMP_POWERMODE_NORMAL) || \
                                      ((TRIMMING) == OPAMP_POWERMODE_LOWPOWER) )

#define IS_OPAMP_POWER_SUPPLY_RANGE(RANGE) (((RANGE) == OPAMP_POWERSUPPLY_LOW) || \
                                            ((RANGE) == OPAMP_POWERSUPPLY_HIGH)  )

#define IS_OPAMP_TRIMMING(TRIMMING) (((TRIMMING) == OPAMP_TRIMMING_FACTORY) || \
                                     ((TRIMMING) == OPAMP_TRIMMING_USER))

#define IS_OPAMP_FACTORYTRIMMING(TRIMMING) (((TRIMMING) == OPAMP_FACTORYTRIMMING_N) || \
                                            ((TRIMMING) == OPAMP_FACTORYTRIMMING_P)   )

/**
  * @}
  */


/* Include OPAMP HAL Extension module */
#include "stm32l1xx_hal_opamp_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup OPAMP_Exported_Functions
  * @{
  */

/** @addtogroup OPAMP_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_DeInit (OPAMP_HandleTypeDef *hopamp);
void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef *hopamp);
void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef *hopamp);
/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group2
  * @{
  */

/* I/O operation functions  *****************************************************/
HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef *hopamp);

/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group3
  * @{
  */

/* Peripheral Control functions  ************************************************/
#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
/* OPAMP callback registering/unregistering */
HAL_StatusTypeDef HAL_OPAMP_RegisterCallback (OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackID, pOPAMP_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_OPAMP_UnRegisterCallback (OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

HAL_StatusTypeDef HAL_OPAMP_Lock(OPAMP_HandleTypeDef *hopamp);
HAL_OPAMP_TrimmingValueTypeDef HAL_OPAMP_GetTrimOffset (OPAMP_HandleTypeDef *hopamp, uint32_t trimmingoffset);

/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group4
  * @{
  */

/* Peripheral State functions  **************************************************/
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef *hopamp);

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

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L151xDX || STM32L152xE || STM32L152xDX || STM32L162xE || STM32L162xDX || STM32L162xC || STM32L152xC || STM32L151xC */
#ifdef __cplusplus
}
#endif

#endif /* STM32L1xx_HAL_OPAMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
