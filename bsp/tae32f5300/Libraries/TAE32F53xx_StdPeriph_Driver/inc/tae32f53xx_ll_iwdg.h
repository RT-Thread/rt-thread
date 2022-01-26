/**
  ******************************************************************************
  * @file    tae32f53xx_ll_iwdg.h
  * @author  MCD Application Team
  * @brief   Header file of IWDG LL module.
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
#ifndef _TAE32F53XX_LL_IWDG_H_
#define _TAE32F53XX_LL_IWDG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup IWDG_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Types IWDG LL Exported Types
  * @brief    IWDG LL Exported Types
  * @{
  */

/**
  * @brief IWDG Prescaler enumeration
  */
typedef enum {
    IWDG_PRESCALER_4    = IWDG_PSCR_PSC_0,             /*!< IWDG prescaler set to 4   */
    IWDG_PRESCALER_8    = IWDG_PSCR_PSC_1,             /*!< IWDG prescaler set to 8   */
    IWDG_PRESCALER_16   = IWDG_PSCR_PSC_2,             /*!< IWDG prescaler set to 16  */
    IWDG_PRESCALER_32   = IWDG_PSCR_PSC_3,             /*!< IWDG prescaler set to 32  */
    IWDG_PRESCALER_64   = IWDG_PSCR_PSC_4,             /*!< IWDG prescaler set to 64  */
    IWDG_PRESCALER_128  = IWDG_PSCR_PSC_5,             /*!< IWDG prescaler set to 128 */
    IWDG_PRESCALER_256  = IWDG_PSCR_PSC_6,             /*!< IWDG prescaler set to 256 */
    IWDG_PRESCALER_512  = IWDG_PSCR_PSC_7,             /*!< IWDG prescaler set to 512 */
} IWDG_PreScalerETypeDef;


/**
    @brief IWDG Mode enumeration
  */
typedef enum {
    IWDG_MODE_RESET     = IWDG_CR_MODE_RESET,          /*!< IWDG Reset after timeout               */
    IWDG_MODE_INTERRUPT = IWDG_CR_MODE_INTERRUPT,      /*!< IWDG Trigger a interrupt after timeout */
} IWDG_ModeETypeDef;


/**
  * @brief IWDG Init structure definition
  */
typedef struct __IWDG_InitTypeDef {
    IWDG_PreScalerETypeDef Prescaler; /*!< Select the prescaler of the IWDG. */
    uint32_t Reload_val;              /*!< Specifies the IWDG down-counter reload value.
                                         This parameter must be a number between Min_Data = 0 and Max_Data = 0x0FFF */
    IWDG_ModeETypeDef Mode;           /*!< Specifies the IWDG bahavior after timeout.*/
} IWDG_InitTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Constants IWDG LL Exported Constants
  * @brief    IWDG LL Exported Constants
  * @{
  */

/** @defgroup IWDG_Interrupt_definition IWDG interrupt Definition
  * @{
  */
#define IWDG_IT_TOIE                    IWDG_CR_TOIE            /*!< IWDG Timeout Interrupte Enable */
/**
  * @}
  */

/** @defgroup IWDG_Flag_definition IWDG Flag Definition
  * @{
  */
#define IWDG_FLAG_PSCUPD                IWDG_SR_PSCUPD          /*!< IWDG Prescaler Update flag     */
#define IWDG_FLAG_RLVUPD                IWDG_SR_RLVUPD          /*!< IWDG Reload Value Update flag  */
#define IWDG_FLAG_TOIF                  IWDG_SR_TOIF            /*!< IWDG Timeout Interrupt flag    */
/**
  * @}
  */

/** @defgroup IWDG_Key_definition IWDG Key Definition
  * @{
  */
#define IWDG_KEY_RELOAD                 0x0000AAAAU             /*!< IWDG Reload Counter Enable     */
#define IWDG_KEY_ENABLE                 0x0000CCCCU             /*!< IWDG Peripheral Enable         */
#define IWDG_KEY_DISABLE                0x0000DDDDU             /*!< IWDG Peripheral Disable        */
#define IWDG_KEY_WRITE_ACCESS_ENABLE    0x00005003U             /*!< IWDG Write Access Enable       */
#define IWDG_KEY_WRITE_ACCESS_DISABLE   0x00000000U             /*!< IWDG Write Access Disable      */
/**
  * @}
  */


/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Macros IWDG LL Exported Macros
  * @brief    IWDG LL Exported Constants
  * @{
  */

/**
  * @brief  Enable write access to IWDG_PSCR, IWDG_RLR and IWDG_CR registers.
  * @param  __INSTANCE__ IWDG peripheral
  * @return None
  */
#define __LL_IWDG_ENABLE_WRITE_ACCESS(__INSTANCE__)             WRITE_REG((__INSTANCE__)->KEYR, IWDG_KEY_WRITE_ACCESS_ENABLE)

/**
  * @brief  Disable write access to IWDG_PSCR, IWDG_RLR and IWDG_CR registers.
  * @param  __INSTANCE__ IWDG peripheral
  * @return None
  */
#define __LL_IWDG_DISABLE_WRITE_ACCESS(__INSTANCE__)            WRITE_REG((__INSTANCE__)->KEYR, IWDG_KEY_WRITE_ACCESS_DISABLE)


/**
  * @brief  Enable the IWDG peripheral.
  * @param  __INSTANCE__ IWDG peripheral
  * @return None
  */
#define __LL_IWDG_START(__INSTANCE__)                           WRITE_REG((__INSTANCE__)->KEYR, IWDG_KEY_ENABLE)

/**
  * @brief  Disable the IWDG peripheral.
  * @param  __INSTANCE__ IWDG peripheral
  * @return None
  */
#define __LL_IWDG_STOP(__INSTANCE__)                            WRITE_REG((__INSTANCE__)->KEYR, IWDG_KEY_DISABLE)

/** @brief  Enable the specified IWDG interrupt.
  * @note   __LL_IWDG_ENABLE_WRITE_ACCESS() must be called to enable write access before enable
  *         the IWDG interrupt.
  * @param  __INSTANCE__ IWDG peripheral
  * @param  __INTERRUPT__ specifies the IWDG interrupt source to enable.
  *         This parameter can be one of the following values:
  *             @arg IWDG_IT_TOIE: Timeout interrupt flag
  * @retrun None
  */
#define __LL_IWDG_ENABLE_IT(__INSTANCE__, __INTERRUPT__)        SET_BIT((__INSTANCE__)->CR, (__INTERRUPT__))

/** @brief  Disable the specified TIM interrupt.
  * @note   __LL_IWDG_ENABLE_WRITE_ACCESS() must be called to enable write access before disable
  *         the IWDG interrupt.
  * @param  __INSTANCE__ IWDG peripheral
  * @param  __INTERRUPT__ specifies the IWDG interrupt source to enable.
  *         This parameter can be one of the following values:
  *             @arg IWDG_IT_TOIE: Timeout interrupt flag
  * @retval None
  */
#define __LL_IWDG_DISABLE_IT(__INSTANCE__, __INTERRUPT__)       CLEAR_BIT((__INSTANCE__)->CR, (__INTERRUPT__))


/** @brief  Check whether the specified IWDG status or interrupt flag is set or not.
  * @param  __INSTANCE__ IWDG peripheral
  * @param  __FLAG__ specifies the IWDG flag to check.
  *         This parameter can be one of the following values:
  *             @arg IWDG_FLAG_PSCUPD: Prescaler value update flag
  *             @arg IWDG_FLAG_RLVUPD: Reload value update flag
  *             @arg IWDG_FLAG_TOIF: Timeout interrupt flag
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_IWDG_GET_FLAG(__INSTANCE__, __FLAG__)              \
        ((READ_BIT((__INSTANCE__)->SR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Clear the specified IWDG status or interrupt flag.
  * @param  __INSTANCE__ IWDG peripheral
  * @param  __FLAG__ specifies the IWDG flag to clear.
  *         This parameter can be one of the following values:
  *             @arg IWDG_FLAG_TOIF: Timeout interrupt flag
  * @return None
  */
#define __LL_IWDG_CLEAR_FLAG(__INSTANCE__, __FLAG__)            WRITE_REG((__INSTANCE__)->SR, (__FLAG__))

/**
  * @brief  Check whether the specified IWDG interrupt source is enabled or not.
  * @param  __INSTANCE__ IWDG peripheral
  * @param  __INTERRUPT__ specifies the IWDG interrupt source to check.
  *         This parameter can be one of the following values:
  *             @arg IWDG_IT_TOIE: Timeout interrupt
  * @return The state of __INTERRUPT__ (SET or RESET).
  */
#define __LL_IWDG_IT_CHECK_SOURCE(__INSTANCE__, __INTERRUPT__)  \
        ((READ_BIT((__INSTANCE__)->CR, (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @brief  Reload IWDG counter with value defined in the reload register
  *         (write access to IWDG_PR & IWDG_RLR registers disabled).
  * @note   Flag RLVUPD and PSCUPD must be 0 before refreshing IWDG counter.
  * @param  __INSTANCE__  IWDG peripheral
  * @return None
  */
#define __LL_IWDG_RELOAD_COUNTER(__INSTANCE__)                  WRITE_REG((__INSTANCE__)->KEYR, IWDG_KEY_RELOAD)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup IWDG_LL_Exported_Functions
  * @{
  */

/** @addtogroup IWDG_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_IWDG_Init(IWDG_TypeDef *Instance, IWDG_InitTypeDef *Init);
LL_StatusETypeDef LL_IWDG_DeInit(IWDG_TypeDef *Instance);
void LL_IWDG_MspInit(IWDG_TypeDef *Instance);
void LL_IWDG_MspDeInit(IWDG_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup IWDG_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_IWDG_Refresh(IWDG_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup IWDG_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_IWDG_IRQHandler(IWDG_TypeDef *Instance);
void LL_IWDG_TimeOutCallBack(IWDG_TypeDef *Instance);
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
/** @defgroup IWDG_LL_Private_Macros IWDG LL Private Macros
  * @brief    IWDG LL Private Macros
  * @{
  */

/**
  * @brief  Check IWDG prescaler value.
  * @param  __PRESCALER__  IWDG prescaler value
  * @return None
  */

/**
  * @brief  Check IWDG reload value.
  * @param  __RELOAD__  IWDG reload value
  * @return None
  */
#define IS_IWDG_RELOAD_Val(__RELOAD__)              ((__RELOAD__) <= IWDG_RLR_RLV)

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


#endif /* _TAE32F53XX_LL_IWDG_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

