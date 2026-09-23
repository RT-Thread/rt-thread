/**
  ******************************************************************************
  * @file    tae32g58xx_ll_iwdg.c
  * @author  MCD Application Team
  * @brief   IWDG LL module driver
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


#define DBG_TAG             "IWDG LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup IWDG_LL IWDG LL
  * @brief    IWDG LL module driver
  * @{
  */

#ifdef LL_IWDG_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/** @defgroup IWDG_LL_Private_Constants IWDG LL Private Constants
  * @brief    IWDG LL Private Constants
  * @{
  */

/**
  * @brief IWDG Defaul Timeout definition in ms Unit
  */
#define IWDG_DEFAULT_TIMEOUT    (100U)

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup IWDG_LL_Private_Functions IWDG LL Private Functions
  * @brief    IWDG LL Private Functions
  * @{
  */
static LL_StatusETypeDef IWDG_WaitForReloadBusy(IWDG_TypeDef *Instance, uint32_t timeout);
static LL_StatusETypeDef IWDG_WaitForPrescalerBusy(IWDG_TypeDef *Instance, uint32_t timeout);

static LL_StatusETypeDef IWDG_ReloadValCfg(IWDG_TypeDef *Instance, uint32_t val);
static LL_StatusETypeDef IWDG_PrescalerDivCfg(IWDG_TypeDef *Instance, IWDG_PreDivETypeDef div);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/** @defgroup IWDG_LL_Exported_Functions IWDG LL Exported Functions
  * @brief    IWDG LL Exported Functions
  * @{
  */

/** @defgroup IWDG_LL_Exported_Functions_Group1 IWDG Init and DeInit Functions
  * @brief    IWDG Init and DeInit Functions
  * @{
  */

/**
  * @brief  IWDG LL Init
  * @param  Instance Specifies IWDG peripheral
  * @param  iwdg_init IWDG init pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_IWDG_Init(IWDG_TypeDef *Instance, IWDG_InitTypeDef *iwdg_init)
{
    LL_StatusETypeDef ret;

    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));
    assert_param(iwdg_init != NULL);

    if (!IS_IWDG_ALL_INSTANCE(Instance) || iwdg_init == NULL) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_IWDG_MspInit(Instance);

    //Reload Value Config
    ret = IWDG_ReloadValCfg(Instance, iwdg_init->reload_val);

    if (ret != LL_OK) {
        LOG_E("Reload value config Fail!\n");
        return ret;
    }

    //Prescaler Div Config
    ret = IWDG_PrescalerDivCfg(Instance, iwdg_init->pre_div);

    if (ret != LL_OK) {
        LOG_E("Prescaler division config Fail!\n");
        return ret;
    }

    //IWDG Work Mode Config
    __LL_IWDG_RegWriteAccess_En(Instance);

    if (iwdg_init->mode == IWDG_MODE_RESET) {   //Reset Mode
        __LL_IWDG_ResetMode_Set(Instance);
        __LL_IWDG_Timeout_INT_Dis(Instance);
    } else {                                    //Interrupt Mode
        __LL_IWDG_IntMode_Set(Instance);
        __LL_IWDG_TimeoutIntPnd_Clr(Instance);
        __LL_IWDG_Timeout_INT_En(Instance);
    }

    __LL_IWDG_RegWriteAccess_Dis(Instance);

    return LL_OK;
}

/**
  * @brief  IWDG LL DeInit
  * @param  Instance Specifies IWDG peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_IWDG_DeInit(IWDG_TypeDef *Instance)
{
    LL_StatusETypeDef ret;

    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //IWDG Stop
    __LL_IWDG_Stop(Instance);

    //Reload Value Config to default
    ret = IWDG_ReloadValCfg(Instance, 0xffffUL);

    if (ret != LL_OK) {
        LOG_E("Reload value config to default Fail!\n");
        return ret;
    }

    //Prescaler Div Config to default
    ret = IWDG_PrescalerDivCfg(Instance, IWDG_PRE_DIV_4);

    if (ret != LL_OK) {
        LOG_E("Prescaler division config to default Fail!\n");
        return ret;
    }

    //IWDG Work mode config to default
    __LL_IWDG_RegWriteAccess_En(Instance);
    __LL_IWDG_Timeout_INT_Dis(Instance);
    __LL_IWDG_ResetMode_Set(Instance);
    __LL_IWDG_RegWriteAccess_Dis(Instance);

    //Interrupt Pending Clear
    __LL_IWDG_TimeoutIntPnd_Clr(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_IWDG_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  IWDG MSP Init
  * @param  Instance IWDG peripheral
  * @return None
  */
__WEAK void LL_IWDG_MspInit(IWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IWDG_MspInit could be implemented in the user file
     */
}

/**
  * @brief  IWDG MSP DeInit
  * @param  Instance IWDG peripheral
  * @return None
  */
__WEAK void LL_IWDG_MspDeInit(IWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IWDG_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup IWDG_LL_Exported_Functions_Group2 IWDG Operation Functions
  * @brief    IWDG Operation Functions
  * @{
  */

/**
  * @brief  IWDG Start
  * @param  Instance Specifies IWDG peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_IWDG_Start(IWDG_TypeDef *Instance)
{
    LL_StatusETypeDef ret;

    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //IWDG Start
    __LL_IWDG_Start(Instance);

    //Refresh Reload Value
    ret = LL_IWDG_Refresh(Instance);

    if (ret != LL_OK) {
        LOG_E("Reload Value Error!\n");
        return ret;
    }

    return LL_OK;
}

/**
  * @brief  IWDG Stop
  * @param  Instance Specifies IWDG peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_IWDG_Stop(IWDG_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //IWDG Start
    __LL_IWDG_Stop(Instance);

    return LL_OK;
}

/**
  * @brief  IWDG Refresh
  * @param  Instance Specifies IWDG peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_IWDG_Refresh(IWDG_TypeDef *Instance)
{
    LL_StatusETypeDef ret;

    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for Reload busy
    ret = IWDG_WaitForReloadBusy(Instance, IWDG_DEFAULT_TIMEOUT);

    if (ret != LL_OK) {
        LOG_E("Wait for Reload Busy state Error before Refresh!\n");
        return ret;
    }

    //Wait for Prescaler busy
    ret = IWDG_WaitForPrescalerBusy(Instance, IWDG_DEFAULT_TIMEOUT);

    if (ret != LL_OK) {
        LOG_E("Wait for Prescaler Busy state Error before Refresh!\n");
        return ret;
    }

    //IWDG Reload Counter
    __LL_IWDG_Reload(Instance);

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup IWDG_LL_Exported_Functions_Interrupt IWDG Interrupt Handler and Callback
  * @brief    IWDG Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  IWDG IRQ Handler
  * @param  Instance Specifies IWDG peripheral
  * @return None
  */
void LL_IWDG_IRQHandler(IWDG_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return;
    }

    if (__LL_IWDG_IsTimeoutIntEn(Instance) && __LL_IWDG_IsTimeoutIntPnd(Instance)) {
        //Interrupt Pending Clear
        __LL_IWDG_TimeoutIntPnd_Clr(Instance);

        //Timeout Callback
        LL_IWDG_TimeOutCallBack(Instance);
    }
}

/**
  * @brief  IWDG Timeout callback
  * @param  Instance Specifies IWDG peripheral
  * @return None
  */
__WEAK void LL_IWDG_TimeOutCallBack(IWDG_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IWDG_TimeOutCallBack could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/** @addtogroup IWDG_LL_Private_Functions
  * @{
  */

/**
  * @brief  IWDG Wait for Reload busy state
  * @param  Instance Specifies IWDG peripheral
  * @param  timeout timeout duration
  * @return LL Status
  */
static LL_StatusETypeDef IWDG_WaitForReloadBusy(IWDG_TypeDef *Instance, uint32_t timeout)
{
    uint32_t tickstart = LL_GetTick();

    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for Reload Busy
    while (__LL_IWDG_IsReloadValUpdating(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            return LL_TIMEOUT;
        }
    }

    return LL_OK;
}

/**
  * @brief  IWDG Wait for Prescaler busy state
  * @param  Instance Specifies IWDG peripheral
  * @param  timeout timeout duration
  * @return LL Status
  */
static LL_StatusETypeDef IWDG_WaitForPrescalerBusy(IWDG_TypeDef *Instance, uint32_t timeout)
{
    uint32_t tickstart = LL_GetTick();

    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for Prescaler Busy
    while (__LL_IWDG_IsPrescalerUpdating(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            return LL_TIMEOUT;
        }
    }

    return LL_OK;
}

/**
  * @brief  IWDG Reload Value Config
  * @param  Instance Specifies IWDG peripheral
  * @param  val Reload Value
  * @return LL Status
  */
static LL_StatusETypeDef IWDG_ReloadValCfg(IWDG_TypeDef *Instance, uint32_t val)
{
    LL_StatusETypeDef ret;

    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for Reload Busy before Config
    ret = IWDG_WaitForReloadBusy(Instance, IWDG_DEFAULT_TIMEOUT);

    if (ret != LL_OK) {
        LOG_E("Wait for Reload Busy state Error before operation!\n");
        return ret;
    }

    //Register Write Access Enable
    __LL_IWDG_RegWriteAccess_En(Instance);

    //Update Reload Value
    __LL_IWDG_ReloadVal_Set(Instance, val);

    //Register Write Access Disable
    __LL_IWDG_RegWriteAccess_Dis(Instance);

    //Wait for Reload Busy after Config
    ret = IWDG_WaitForReloadBusy(Instance, IWDG_DEFAULT_TIMEOUT);

    if (ret != LL_OK) {
        LOG_E("Wait for Reload Busy state Error after operation!\n");
        return ret;
    }

    return LL_OK;
}

/**
  * @brief  IWDG Prescaler Division Config
  * @param  Instance Specifies IWDG peripheral
  * @param  div Prescaler Division
  * @return LL Status
  */
static LL_StatusETypeDef IWDG_PrescalerDivCfg(IWDG_TypeDef *Instance, IWDG_PreDivETypeDef div)
{
    LL_StatusETypeDef ret;

    //Assert param
    assert_param(IS_IWDG_ALL_INSTANCE(Instance));

    if (!IS_IWDG_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Wait for Prescaler Busy before Config
    ret = IWDG_WaitForPrescalerBusy(Instance, IWDG_DEFAULT_TIMEOUT);

    if (ret != LL_OK) {
        LOG_E("Wait for Prescaler Busy state Error before operation!\n");
        return ret;
    }

    //Register Write Access Enable
    __LL_IWDG_RegWriteAccess_En(Instance);

    //Update Prescaler Division
    __LL_IWDG_PrescalerDiv_Set(Instance, div);

    //Register Write Access Disable
    __LL_IWDG_RegWriteAccess_Dis(Instance);

    //Wait for Prescaler Busy after Config
    ret = IWDG_WaitForPrescalerBusy(Instance, IWDG_DEFAULT_TIMEOUT);

    if (ret != LL_OK) {
        LOG_E("Wait for Prescaler Busy state Error after operation!\n");
        return ret;
    }

    return LL_OK;
}

/**
  * @}
  */


#endif /* LL_IWDG_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

