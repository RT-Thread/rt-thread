/**
  ******************************************************************************
  * @file    tae32f53xx_ll_wwdg.h
  * @author  MCD Application Team
  * @brief   Header file of WWDG LL module.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_WWDG_H_
#define _TAE32F53XX_LL_WWDG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup WWDG_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup WWDG_LL_Exported_Types WWDG LL Exported Types
  * @brief    WWDG LL Exported Types
  * @{
  */

/**
    @brief WWDG Early Wakeup Interrupt Mode
  */
typedef enum {
    WWDG_EWI_DISABLE    = 0x00000000U,         /*!< Rsest                          */
    WWDG_EWI_ENABLE     = WWDG_CR_EWIE,        /*!< Early Wakeup Interrupt         */
} WWDG_EWIETypeDef;

/**
  * @brief WWDG Init structure definition
  */
typedef struct __WWDG_InitTypeDef {
    uint32_t Prescaler;         /*!< Specifies the prescaler value of the WWDG.
                                     This parameter must be a number Min_Data = 0x00 and Max_Data = 0xFFFF          */

    uint32_t Window;            /*!< Specifies the WWDG window value to be compared to the downcounter.
                                     This parameter must be a number Min_Data = 0x40 and Max_Data = 0xFFFF          */

    uint32_t Counter;           /*!< Specifies the WWDG free-running downcounter value.
                                     This parameter must be a number between Min_Data = 0x40 and Max_Data = 0xFFFF  */

    WWDG_EWIETypeDef EWIMode;   /*!< Specifies if WWDG Early Wakeup Interupt is enable or not.                      */
} WWDG_InitTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup WWDG_LL_Exported_Constants WWDG LL Exported Constants
  * @brief    WWDG LL Exported Constants
  * @{
  */

/** @defgroup WWDG_Interrupt_definition WWDG Interrupt definition
  * @{
  */
#define WWDG_IT_EWIE                        WWDG_CR_EWIE        /*!< Early wakeup interrupt         */
/**
  * @}
  */

/** @defgroup WWDG_Flag_definition WWDG Flag definition
  * @brief WWDG Flag definition
  * @{
  */
#define WWDG_FLAG_EWIF                      WWDG_ISR_EWIF       /*!< Early wakeup interrupt flag    */
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup WWDG_LL_Exported_Macros WWDG LL Exported Macros
  * @brief    WWDG LL Exported Macros
  * @{
  */

/**
  * @brief  Enable the WWDG peripheral.
  * @param  __INSTANCE__ WWDG peripheral
  * @retval None
  */
#define __LL_WWDG_ENABLE(__INSTANCE__)                              SET_BIT((__INSTANCE__)->CR, WWDG_CR_WEN)

/**
  * @brief  Disable the WWDG peripheral.
  * @param  __INSTANCE__ WWDG peripheral
  * @retval None
  */
#define __LL_WWDG_DISABLE(__INSTANCE__)                             CLEAR_BIT((__INSTANCE__)->CR, WWDG_CR_WEN)

/**
  * @brief  Enable the specified WWDG interrupt.
  * @param  __INSTANCE__ WWDG peripheral
  * @param  __INTERRUPT__ specifies the interrupt to enable.
  *         This parameter can be one of the following values:
  *             @arg WWDG_IT_EWIE: Early wakeup interrupt
  * @retval None
  */
#define __LL_WWDG_IT_ENABLE(__INSTANCE__, __INTERRUPT__)            SET_BIT((__INSTANCE__)->CR, (__INTERRUPT__))

/**
  * @brief  Disable the specified WWDG interrupt.
  * @param  __INSTANCE__ WWDG peripheral
  * @param  __INTERRUPT__ specifies the interrupt to enable.
  *         This parameter can be one of the following values:
  *             @arg WWDG_IT_EWIE: Early wakeup interrupt
  * @retval None
  */
#define __LL_WWDG_IT_DISABLE(__INSTANCE__, __INTERRUPT__)           CLEAR_BIT((__INSTANCE__)->CR, (__INTERRUPT__))

/**
  * @brief  Check whether the specified WWDG flag is set or not.
  * @param  __INSTANCE__ WWDG peripheral
  * @param  __FLAG__  specifies the flag to check.
  *         This parameter can be one of the following values:
  *             @arg WWDG_FLAG_EWIF: Early wakeup interrupt flag
  * @retval The new state of WWDG_FLAG (SET or RESET).
  */

#define __LL_WWDG_GET_FLAG(__INSTANCE__, __FLAG__)  ((READ_BIT((__INSTANCE__)->ISR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)
/**
  * @brief  Clears the WWDG's pending flags.
  * @param  __INSTANCE__ WWDG peripheral
  * @param  __FLAG__ specifies the flag to clear.
  *         This parameter can be one of the following values:
  *             @arg WWDG_FLAG_EWIF: Early wakeup interrupt flag
  * @retval None
  */

#define __LL_WWDG_CLEAR_FLAG(__INSTANCE__, __FLAG__)                WRITE_REG((__INSTANCE__)->ISR, (__FLAG__))

/**
  * @brief  Checks if the specified WWDG interrupt source is enabled or disabled.
  * @param  __INSTANCE__ WWDG peripheral
  * @param  __INTERRUPT__ specifies the WWDG interrupt source to check.
  *         This parameter can be one of the following values:
  *             @arg WWDG_IT_EWIE: Early Wakeup Interrupt
  * @retval state of __INTERRUPT__ (SET or RESET).
  */
#define __LL_WWDG_CHECK_IT_SOURCE(__INSTANCE__, __INTERRUPT__)      \
        ((READ_BIT((__INSTANCE__)->CR, (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @brief  Get the WWDG Counter Register value on runtime.
  * @param  __INSTANCE__ WWDG peripheral
  * @retval 16-bit value of the WWDG counter register (WWDG_CVR)
  */
#define __LL_WWDG_GET_COUNTER(__INSTANCE__)                         (READ_REG((__INSTANCE__)->CVR))

/**
  * @brief  Set the WWDG Counter Register value to refresh WWDG.
  * @param  __INSTANCE__ WWDG peripheral
  * @param  __COUNTER__ specifies WWDG counter value to refresh with
  * @retval None
  */
#define __LL_WWDG_SET_COUNTER(__INSTANCE__, __COUNTER__)            WRITE_REG((__INSTANCE__)->CVR, __COUNTER__)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup WWDG_LL_Exported_Functions
  * @{
  */

/** @addtogroup WWDG_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_WWDG_Init(WWDG_TypeDef *Instance, WWDG_InitTypeDef *Init);
LL_StatusETypeDef LL_WWDG_DeInit(WWDG_TypeDef *Instance);
void LL_WWDG_MspInit(WWDG_TypeDef *Instance);
void LL_WWDG_MspDeInit(WWDG_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup WWDG_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_WWDG_Refresh(WWDG_TypeDef *Instance, uint16_t Counter);
/**
  * @}
  */


/** @addtogroup WWDG_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_WWDG_IRQHandler(WWDG_TypeDef *Instance);
void LL_WWDG_EarlyWakeUpCallback(WWDG_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup WWDG_LL_Private_Macros WWDG LL Private Macros
  * @brief    WWDG LL Private Macros
  * @{
  */

/**
  * @brief  Judge is WWDG prescaler or not
  * @param  __PRESCALER__ prescaler to judge
  * @retval 0 isn't WWDG prescaler
  * @retval 1 is WWDG prescaler
  */
#define IS_WWDG_PRESCALER(__PRESCALER__)            ((__PRESCALER__) <= 0xFFFFUL)

/**
  * @brief  Judge is WWDG window or not
  * @param  __WINDOW__ window to judge
  * @retval 0 isn't WWDG window
  * @retval 1 is WWDG window
  */
#define IS_WWDG_WINDOW(__WINDOW__)                  ((__WINDOW__) <= 0xFFFFUL)

/**
  * @brief  Judge is WWDG counter or not
  * @param  __COUNTER__ counter to judge
  * @retval 0 isn't WWDG counter
  * @retval 1 is WWDG counter
  */
#define IS_WWDG_COUNTER(__COUNTER__)                ((__COUNTER__) <= 0xFFFFUL)

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_WWDG_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

