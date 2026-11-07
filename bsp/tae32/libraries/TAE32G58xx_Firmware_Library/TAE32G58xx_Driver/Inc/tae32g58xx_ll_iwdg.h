/**
  ******************************************************************************
  * @file    tae32g58xx_ll_iwdg.h
  * @author  MCD Application Team
  * @brief   Header file of IWDG LL module
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
#ifndef _TAE32G58XX_LL_IWDG_H_
#define _TAE32G58XX_LL_IWDG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup IWDG_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Constants IWDG LL Exported Constants
  * @brief    IWDG LL Exported Constants
  * @{
  */

#define IWDG_KEY_RELOAD             0xAAAAU     /*!< IWDG Reload Counter Enable */
#define IWDG_KEY_START              0xCCCCU     /*!< IWDG Peripheral Start      */
#define IWDG_KEY_STOP               0xDDDDU     /*!< IWDG Peripheral Stop       */
#define IWDG_KEY_WRITE_ACCESS_EN    0x3FACU     /*!< IWDG Write Access Enable   */
#define IWDG_KEY_WRITE_ACCESS_DIS   0x0000U     /*!< IWDG Write Access Disable  */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Macros IWDG LL Exported Macros
  * @brief    IWDG LL Exported Constants
  * @{
  */

/**
  * @brief  Reg Write Access Enable
  * @note   Only CR/RLR/PSCR Registers is controled by this
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_RegWriteAccess_En(__IWDG__)           WRITE_REG((__IWDG__)->KEYR, IWDG_KEY_WRITE_ACCESS_EN)

/**
  * @brief  Reg Write Access Disable
  * @note   Only CR/RLR/PSCR Registers is controled by this
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_RegWriteAccess_Dis(__IWDG__)          WRITE_REG((__IWDG__)->KEYR, IWDG_KEY_WRITE_ACCESS_DIS)

/**
  * @brief  IWDG Start
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_Start(__IWDG__)                       WRITE_REG((__IWDG__)->KEYR, IWDG_KEY_START)

/**
  * @brief  IWDG Stop
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_Stop(__IWDG__)                        WRITE_REG((__IWDG__)->KEYR, IWDG_KEY_STOP)

/**
  * @brief  Reload IWDG counter with value defined in the reload register
  * @note   Flag RLVUPD and PSCUPD must be 0 before refreshing IWDG counter
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_Reload(__IWDG__)                      WRITE_REG((__IWDG__)->KEYR, IWDG_KEY_RELOAD)


/**
  * @brief  Timeout Interrupt Enable
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_Timeout_INT_En(__IWDG__)              SET_BIT((__IWDG__)->CR, IWDG_CR_TOIE_Msk)

/**
  * @brief  Timeout Interrupt Disable
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_Timeout_INT_Dis(__IWDG__)             CLEAR_BIT((__IWDG__)->CR, IWDG_CR_TOIE_Msk)

/**
  * @brief  Judge is Timeout Interrupt Enable or not
  * @param  __IWDG__ Specifies IWDG peripheral
  * @retval 0 Timeout Interrupt is Disable
  * @retval 1 Timeout Interrupt is Enable
  */
#define __LL_IWDG_IsTimeoutIntEn(__IWDG__)              READ_BIT_SHIFT((__IWDG__)->CR, IWDG_CR_TOIE_Msk, IWDG_CR_TOIE_Pos)

/**
  * @brief  Reset Mode Set
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_ResetMode_Set(__IWDG__)               CLEAR_BIT((__IWDG__)->CR, IWDG_CR_MODE_Msk)

/**
  * @brief  Interrupt Mode Set
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_IntMode_Set(__IWDG__)                 SET_BIT((__IWDG__)->CR, IWDG_CR_MODE_Msk)


/**
  * @brief  Reload Value Set
  * @param  __IWDG__ Specifies IWDG peripheral
  * @param  val Reload Value
  * @return None
  */
#define __LL_IWDG_ReloadVal_Set(__IWDG__, val)          WRITE_REG((__IWDG__)->RLR, ((val) & 0xffffUL))

/**
  * @brief  Reload Value Get
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return Reload Value
  */
#define __LL_IWDG_ReloadVal_Get(__IWDG__)               READ_BIT((__IWDG__)->RLR, 0xffffUL)


/**
  * @brief   Prescaler Divider Set
  * @param  __IWDG__ Specifies IWDG peripheral
  * @param  pre_div Prescaler Divider
  * @return None
  */
#define __LL_IWDG_PrescalerDiv_Set(__IWDG__, pre_div)   \
        MODIFY_REG((__IWDG__)->PSCR, IWDG_PSCR_PSC_Msk, (((pre_div) & 0x7UL) << IWDG_PSCR_PSC_Pos))

/**
  * @brief   Prescaler Divider Get
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return Prescaler Divider
  */
#define __LL_IWDG_PrescalerDiv_Get(__IWDG__)            READ_BIT_SHIFT((__IWDG__)->PSCR, IWDG_PSCR_PSC_Msk, IWDG_PSCR_PSC_Pos)


/**
  * @brief   Judge is Timeout Interrupt Pending or not
  * @param  __IWDG__ Specifies IWDG peripheral
  * @retval 0 isn't Timeout Interrupt Pending
  * @retval 1 is Timeout Interrupt Pending
  */
#define __LL_IWDG_IsTimeoutIntPnd(__IWDG__)             READ_BIT_SHIFT((__IWDG__)->SR, IWDG_SR_TOIF_Msk, IWDG_SR_TOIF_Pos)

/**
  * @brief  Timeout Interrupt Pending Clear
  * @param  __IWDG__ Specifies IWDG peripheral
  * @return None
  */
#define __LL_IWDG_TimeoutIntPnd_Clr(__IWDG__)           WRITE_REG((__IWDG__)->SR, IWDG_SR_TOIF_Msk)

/**
  * @brief   Judge is Reload Value Updating or not
  * @param  __IWDG__ Specifies IWDG peripheral
  * @retval 0 Reload Value isn't Updating
  * @retval 1 Reload Value is Updating
  */
#define __LL_IWDG_IsReloadValUpdating(__IWDG__)         READ_BIT_SHIFT((__IWDG__)->SR, IWDG_SR_RLVUPD_Msk, IWDG_SR_RLVUPD_Pos)

/**
  * @brief   Judge is Prescaler Updating or not
  * @param  __IWDG__ Specifies IWDG peripheral
  * @retval 0 Prescaler isn't Updating
  * @retval 1 Prescaler is Updating
  */
#define __LL_IWDG_IsPrescalerUpdating(__IWDG__)         READ_BIT_SHIFT((__IWDG__)->SR, IWDG_SR_PSCUPD_Msk, IWDG_SR_PSCUPD_Pos)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Types IWDG LL Exported Types
  * @brief    IWDG LL Exported Types
  * @{
  */

/**
  * @brief IWDG Prescaler Division enumeration
  */
typedef enum {
    IWDG_PRE_DIV_4 = 0,             /*!< IWDG Prescaler Div 4    */
    IWDG_PRE_DIV_8,                 /*!< IWDG Prescaler Div 8    */
    IWDG_PRE_DIV_16,                /*!< IWDG Prescaler Div 16   */
    IWDG_PRE_DIV_32,                /*!< IWDG Prescaler Div 32   */
    IWDG_PRE_DIV_64,                /*!< IWDG Prescaler Div 64   */
    IWDG_PRE_DIV_128,               /*!< IWDG Prescaler Div 128  */
    IWDG_PRE_DIV_256,               /*!< IWDG Prescaler Div 256  */
    IWDG_PRE_DIV_512,               /*!< IWDG Prescaler Div 512  */
} IWDG_PreDivETypeDef;

/**
  * @brief IWDG Mode enumeration
  */
typedef enum {
    IWDG_MODE_RESET,                /*!< IWDG Mode Reset        */
    IWDG_MODE_INTERRUPT,            /*!< IWDG Mode Interrupt    */
} IWDG_ModeETypeDef;


/**
  * @brief IWDG Init structure definition
  */
typedef struct __IWDG_InitTypeDef {
    uint32_t            reload_val; /*!< IWDG down-counter reload value */
    IWDG_ModeETypeDef   mode;       /*!< IWDG bahavior after timeout    */
    IWDG_PreDivETypeDef pre_div;    /*!< IWDG prescaler division        */
} IWDG_InitTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup IWDG_LL_Exported_Functions
  * @{
  */

/** @addtogroup IWDG_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_IWDG_Init(IWDG_TypeDef *Instance, IWDG_InitTypeDef *iwdg_init);
LL_StatusETypeDef LL_IWDG_DeInit(IWDG_TypeDef *Instance);
void LL_IWDG_MspInit(IWDG_TypeDef *Instance);
void LL_IWDG_MspDeInit(IWDG_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup IWDG_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_IWDG_Start(IWDG_TypeDef *Instance);
LL_StatusETypeDef LL_IWDG_Stop(IWDG_TypeDef *Instance);
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


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_IWDG_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

