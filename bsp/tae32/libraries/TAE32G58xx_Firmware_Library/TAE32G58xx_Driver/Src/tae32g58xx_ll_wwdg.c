/**
  ******************************************************************************
  * @file    tae32g58xx_ll_wwdg.c
  * @author  MCD Application Team
  * @brief   WWDG LL module driver
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

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"


#define DBG_TAG             "WWDG LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup WWDG_LL WWDG LL
  * @brief    WWDG LL module driver
  * @{
  */

#ifdef LL_WWDG_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup WWDG_LL_Exported_Functions WWDG LL Exported Functions
  * @brief    WWDG LL Exported Functions
  * @{
  */

/** @defgroup WWDG_LL_Exported_Functions_Group1 WWDG Init and DeInit Functions
  * @brief    WWDG Init and DeInit Functions
  * @{
  */

/**
  * @brief  WWDG LL Init
  * @param  Instance Specifies WWDG peripheral
  * @param  wwdg_init WWDG init pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_WWDG_Init(WWDG_TypeDef *Instance, WWDG_InitTypeDef *wwdg_init)
{
    //Assert param
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));
    assert_param(wwdg_init != NULL);

    if (!IS_WWDG_ALL_INSTANCE(Instance) || wwdg_init == NULL) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_WWDG_MspInit(Instance);

    //WWDG Init
    __LL_WWDG_WindowVal_Set(Instance, wwdg_init->window);
    __LL_WWDG_CounterVal_Set(Instance, wwdg_init->counter);
    __LL_WWDG_PrescalerDiv_Set(Instance, wwdg_init->pre_div);
    __LL_WWDG_EarlyWakeupIntPnd_Clr(Instance);
    LL_FUNC_ALTER(wwdg_init->early_wk_int_en, __LL_WWDG_EarlyWakeup_INT_En(Instance), __LL_WWDG_EarlyWakeup_INT_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  WWDG LL DeInit
  * @param  Instance Specifies WWDG peripheral
  * @return status of the de-initialization
  */
LL_StatusETypeDef LL_WWDG_DeInit(WWDG_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));

    if (!IS_WWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //WWDG DeInit
    __LL_WWDG_Dis(Instance);
    __LL_WWDG_EarlyWakeup_INT_Dis(Instance);
    __LL_WWDG_EarlyWakeupIntPnd_Clr(Instance);

    __LL_WWDG_WindowVal_Set(Instance, 0xffffUL);
    __LL_WWDG_CounterVal_Set(Instance, 0xffffUL);
    __LL_WWDG_PrescalerDiv_Set(Instance, 0x00);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_WWDG_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  WWDG MSP Init
  * @param  Instance Specifies WWDG peripheral
  * @return None
  */
__WEAK void LL_WWDG_MspInit(WWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_WWDG_MspInit could be implemented in the user file
     */
}

/**
  * @brief  WWDG MSP DeInit
  * @param  Instance Specifies WWDG peripheral
  * @return None
  */
__WEAK void LL_WWDG_MspDeInit(WWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_WWDG_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup WWDG_LL_Exported_Functions_Group2 WWDG Operation Functions
  * @brief    WWDG Operation Functions
  * @{
  */

/**
  * @brief  WWDG Start
  * @param  Instance Specifies WWDG peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_WWDG_Start(WWDG_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));

    if (!IS_WWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //WWDG Enable to Start
    __LL_WWDG_En(Instance);

    return LL_OK;
}

/**
  * @brief  WWDG Stop
  * @param  Instance Specifies WWDG peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_WWDG_Stop(WWDG_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));

    if (!IS_WWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //WWDG Disable to Stop
    __LL_WWDG_Dis(Instance);

    return LL_OK;
}

/**
  * @brief  WWDG Refresh
  * @param  Instance Specifies WWDG peripheral
  * @param  counter Counter value to refresh with
  * @return LL Status
  */
LL_StatusETypeDef LL_WWDG_Refresh(WWDG_TypeDef *Instance, uint32_t counter)
{
    //Assert param
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));

    if (!IS_WWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Refresh Counter
    __LL_WWDG_CounterVal_Set(Instance, counter);

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup WWDG_LL_Exported_Functions_Interrupt WWDG Interrupt Handler and Callback
  * @brief    WWDG Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  WWDG IRQ Handler
  * @param  Instance Specifies WWDG peripheral
  * @return None
  */
void LL_WWDG_IRQHandler(WWDG_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_WWDG_ALL_INSTANCE(Instance));

    if (!IS_WWDG_ALL_INSTANCE(Instance)) {
        return;
    }

    if (__LL_WWDG_IsEarlyWakeupIntEn(Instance) && __LL_WWDG_IsEarlyWakeupIntPnd(Instance)) {
        //Interrupt Pending Clear
        __LL_WWDG_EarlyWakeupIntPnd_Clr(Instance);

        //Early Wakeup Callback
        LL_WWDG_EarlyWakeUpCallback(Instance);
    }
}

/**
  * @brief  WWDG Early Wakeup Interrupt Callback
  * @param  Instance Specifies WWDG peripheral
  * @return None
  */
__WEAK void LL_WWDG_EarlyWakeUpCallback(WWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_WWDG_EarlyWakeupCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


#endif /* LL_WWDG_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

