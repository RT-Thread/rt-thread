/**
  ******************************************************************************
  * @file    tae32g58xx_ll_dac.c
  * @author  MCD Application Team
  * @brief   DAC LL module driver
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


#define DBG_TAG             "DAC LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup DAC_LL DAC LL
  * @brief    DAC LL Module Driver
  * @{
  */

#ifdef LL_DAC_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Functions DAC LL Exported Functions
  * @brief    DAC LL Exported Functions
  * @{
  */

/** @defgroup DAC_LL_Exported_Functions_Group1 DAC Init and DeInit Functions
  * @brief    DAC Init and DeInit Functions
  * @{
  */

/**
  * @brief  DAC LL Init
  * @param  Instance Specifies DAC peripheral
  * @param  init DAC Init pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_DAC_Init(DAC_TypeDef *Instance, DAC_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_DAC_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_DAC_MspInit(Instance);

    //DAC Disable Before Init
    __LL_DAC_Dis(Instance);

    //DAC Init
    LL_FUNC_ALTER(init->trig_en, __LL_DAC_Trig_En(Instance), __LL_DAC_Trig_Dis(Instance));
    LL_FUNC_ALTER(init->buf_out_en, __LL_DAC_BufOutput_En(Instance), __LL_DAC_BufOutput_Dis(Instance));
    LL_FUNC_ALTER(init->bypass_buf_out_en, __LL_DAC_BypassBufOutput_En(Instance), __LL_DAC_BypassBufOutput_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  DAC LL DeInit
  * @param  Instance Specifies DAC peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_DAC_DeInit(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    if (!IS_DAC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //DAC Disable
    __LL_DAC_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_DAC_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the DAC MSP
  * @param  Instance Specifies DAC peripheral
  * @return None
  */
__WEAK void LL_DAC_MspInit(DAC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DAC_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the DAC MSP
  * @param  Instance Specifies DAC peripheral
  * @return None
  */
__WEAK void LL_DAC_MspDeInit(DAC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DAC_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup DAC_LL_Exported_Functions_Group2 DAC Config Functions
  * @brief    DAC Config Functions
  * @{
  */

/**
  * @brief  DAC Sawtooth Config
  * @param  Instance Specifies DAC peripheral
  * @param  cfg Sawtooth Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_SAW_Cfg(DAC_TypeDef *Instance, DAC_SAW_CfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_DAC_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Sawtooth/Triangle Generate all Disable Before Conifg
    __LL_DAC_SAW_Gen_Dis(Instance);
    __LL_DAC_TRI_Gen_Dis(Instance);

    //Sawtooth Config
    __LL_DAC_SAW_GenDir_Set(Instance, cfg->dir);
    __LL_DAC_SAW_RstDat_Set(Instance, cfg->rst_val);
    __LL_DAC_SAW_StepDat_Set(Instance, cfg->step_val);
    __LL_DAC_SAW_RstTrigSrc_Set(Instance, cfg->rst_trig_src);
    __LL_DAC_SAW_StepTrigSrc_Set(Instance, cfg->step_trig_src);

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_DAC))) {
        __LL_DAC_SAW_UpdMode_Set(Instance, cfg->upd_mode);
    }

    //Sawtooth Generate Enable
    __LL_DAC_SAW_Gen_En(Instance);

    return LL_OK;
}

/**
  * @brief  DAC Triangle Config
  * @param  Instance Specifies DAC peripheral
  * @param  cfg Triangle Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_TRI_Cfg(DAC_TypeDef *Instance, DAC_TRI_CfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_DAC_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Sawtooth/Triangle Generate all Disable Before Conifg
    __LL_DAC_SAW_Gen_Dis(Instance);
    __LL_DAC_TRI_Gen_Dis(Instance);

    //Triangle Config
    __LL_DAC_TRI_InitVal_Set(Instance, cfg->init_val);
    __LL_DAC_TRI_MaxAmp_Set(Instance, cfg->max_amp);
    __LL_DAC_TRI_GenDir_Set(Instance, cfg->dir);
    __LL_DAC_TRI_TrigSrc_Set(Instance, cfg->step_trig_src);

    //Triangle Generate Enable
    __LL_DAC_TRI_Gen_En(Instance);

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup DAC_LL_Exported_Functions_Group3 DAC Operation Functions
  * @brief    DAC Operation Functions
  * @{
  */

/**
  * @brief  DAC LL Start
  * @param  Instance Specifies DAC peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_Start(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    if (!IS_DAC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //DAC Enable
    __LL_DAC_En(Instance);

    return LL_OK;
}

/**
  * @brief  DAC LL Stop
  * @param  Instance Specifies DAC peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_Stop(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    if (!IS_DAC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //DAC Disable
    __LL_DAC_Dis(Instance);

    return LL_OK;
}

/**
  * @brief  DAC LL Value Set
  * @param  Instance Specifies DAC peripheral
  * @param  val Value to set
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_ValueSet(DAC_TypeDef *Instance, uint16_t val)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    if (!IS_DAC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_DAC_Dat_Write(Instance, val);

    return LL_OK;
}

/**
  * @brief  DAC LL Value Get
  * @param  Instance Specifies DAC peripheral
  * @return Get Value
  */
uint16_t LL_DAC_ValueGet(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    if (!IS_DAC_ALL_INSTANCE(Instance)) {
        return 0;
    }

    return (uint16_t)__LL_DAC_Dat_Read(Instance);
}

/**
  * @}
  */


/** @defgroup DAC_LL_Exported_Functions_Group4 DAC Software Trigger Functions
  * @brief    DAC Software Trigger Functions
  * @{
  */

/**
  * @brief  DAC LL Sawtooth Software Trigger Reset
  * @param  Instance Specifies DAC peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_SAW_RstSwTrig(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    if (!IS_DAC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_DAC_SAW_RstSw_Trig(Instance);

    return LL_OK;
}

/**
  * @brief  DAC LL Sawtooth Software Trigger Step
  * @param  Instance Specifies DAC peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_SAW_StepSwTrig(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    if (!IS_DAC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_DAC_SAW_StepSw_Trig(Instance);

    return LL_OK;
}

/**
  * @brief  DAC LL Triangle Software Trigger Step
  * @param  Instance Specifies DAC peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_DAC_TRI_StepSwTrig(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));

    if (!IS_DAC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_DAC_TRI_StepSw_Trig(Instance);

    return LL_OK;
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


#endif  /* LL_DAC_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

