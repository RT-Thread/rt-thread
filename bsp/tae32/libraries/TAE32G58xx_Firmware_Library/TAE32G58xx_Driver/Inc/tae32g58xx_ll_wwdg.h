/**
  ******************************************************************************
  * @file    tae32g58xx_ll_wwdg.h
  * @author  MCD Application Team
  * @brief   Header file for WWDG LL module
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
#ifndef _TAE32G58XX_LL_WWDG_H_
#define _TAE32G58XX_LL_WWDG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup WWDG_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup WWDG_LL_Exported_Macros WWDG LL Exported Macros
  * @brief    WWDG LL Exported Macros
  * @{
  */

/**
  * @brief  Early Wakeup Interrupt Enable
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return None
  */
#define __LL_WWDG_EarlyWakeup_INT_En(__WWDG__)          SET_BIT((__WWDG__)->CR, WWDG_CR_EWIE_Msk)

/**
  * @brief  Early Wakeup Interrupt Disable
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return None
  */
#define __LL_WWDG_EarlyWakeup_INT_Dis(__WWDG__)         CLEAR_BIT((__WWDG__)->CR, WWDG_CR_EWIE_Msk)

/**
  * @brief  Judge is Early Wakeup Interrupt Enable or not
  * @param  __WWDG__ Specifies WWDG peripheral
  * @retval 0 Early Wakeup Interrupt is Disable
  * @retval 1 Early Wakeup Interrupt is Enable
  */
#define __LL_WWDG_IsEarlyWakeupIntEn(__WWDG__)          READ_BIT_SHIFT((__WWDG__)->CR, WWDG_CR_EWIE_Msk, WWDG_CR_EWIE_Pos)

/**
  * @brief  WWDG peripheral Enable
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return None
  */
#define __LL_WWDG_En(__WWDG__)                          SET_BIT((__WWDG__)->CR, WWDG_CR_WEN_Msk)

/**
  * @brief  WWDG peripheral Disable
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return None
  */
#define __LL_WWDG_Dis(__WWDG__)                         CLEAR_BIT((__WWDG__)->CR, WWDG_CR_WEN_Msk)


/**
  * @brief  Window Value Set
  * @param  __WWDG__ Specifies WWDG peripheral
  * @param  val Window Value
  * @return None
  */
#define __LL_WWDG_WindowVal_Set(__WWDG__, val)          WRITE_REG((__WWDG__)->WVR, ((val) & 0xffffUL))

/**
  * @brief  Window Value Get
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return Window Value
  */
#define __LL_WWDG_WindowVal_Get(__WWDG__)               READ_BIT_SHIFT((__WWDG__)->WVR, WWDG_WVR_WV_Msk, WWDG_WVR_WV_Pos)


/**
  * @brief  Counter Value Set
  * @param  __WWDG__ Specifies WWDG peripheral
  * @param  val Counter Value
  * @return None
  */
#define __LL_WWDG_CounterVal_Set(__WWDG__, val)         WRITE_REG((__WWDG__)->CVR, ((val) & 0xffffUL))

/**
  * @brief  Counter Value Get
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return Counter Value
  */
#define __LL_WWDG_CounterVal_Get(__WWDG__)              READ_BIT_SHIFT((__WWDG__)->CVR, WWDG_CVR_CV_Msk, WWDG_CVR_CV_Pos)


/**
  * @brief  Prescaler Division Set
  * @param  __WWDG__ Specifies WWDG peripheral
  * @param  div Prescaler Division
  * @return None
  */
#define __LL_WWDG_PrescalerDiv_Set(__WWDG__, div)       WRITE_REG((__WWDG__)->PSCR, ((div) & 0xffffUL))

/**
  * @brief  Prescaler Division Get
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return Prescaler Division
  */
#define __LL_WWDG_PrescalerDiv_Get(__WWDG__)            READ_BIT_SHIFT((__WWDG__)->PSCR, WWDG_PSCR_PSC_Msk, WWDG_PSCR_PSC_Pos)


/**
  * @brief  Judge is Early Wakeup Interrupt Pending or not
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return 0 isn't Early Wakeup Interrupt Pending
  * @return 1 is Early Wakeup Interrupt Pending
  */
#define __LL_WWDG_IsEarlyWakeupIntPnd(__WWDG__)         READ_BIT_SHIFT((__WWDG__)->ISR, WWDG_ISR_EWIF_Msk, WWDG_ISR_EWIF_Pos)

/**
  * @brief  Early Wakeup Interrupt Pending Clear
  * @param  __WWDG__ Specifies WWDG peripheral
  * @return None
  */
#define __LL_WWDG_EarlyWakeupIntPnd_Clr(__WWDG__)       WRITE_REG((__WWDG__)->ISR, WWDG_ISR_EWIF_Msk)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup WWDG_LL_Exported_Types WWDG LL Exported Types
  * @brief    WWDG LL Exported Types
  * @{
  */

/**
  * @brief WWDG Init structure definition
  */
typedef struct __WWDG_InitTypeDef {
    uint32_t pre_div;         /*!< WWDG prescaler value, [0x00, 0xFFFF]                 */
    uint32_t window;          /*!< WWDG window value, [0x40, 0xFFFF]                    */
    uint32_t counter;         /*!< WWDG free-running downcounter value, [0x40, 0xFFFF]  */
    bool early_wk_int_en;     /*!< WWDG Early Wakeup Interupt enable                    */
} WWDG_InitTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup WWDG_LL_Exported_Functions
  * @{
  */

/** @addtogroup WWDG_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_WWDG_Init(WWDG_TypeDef *Instance, WWDG_InitTypeDef *wwdg_init);
LL_StatusETypeDef LL_WWDG_DeInit(WWDG_TypeDef *Instance);
void LL_WWDG_MspInit(WWDG_TypeDef *Instance);
void LL_WWDG_MspDeInit(WWDG_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup WWDG_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_WWDG_Start(WWDG_TypeDef *Instance);
LL_StatusETypeDef LL_WWDG_Stop(WWDG_TypeDef *Instance);
LL_StatusETypeDef LL_WWDG_Refresh(WWDG_TypeDef *Instance, uint32_t counter);
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


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_WWDG_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

