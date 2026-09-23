/**
  ******************************************************************************
  * @file    tae32g58xx_ll_cmp.c
  * @author  MCD Application Team
  * @brief   CMP LL module driver
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


#define DBG_TAG             "CMP LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup CMP_LL CMP LL
  * @brief    CMP LL Module Driver
  * @{
  */

#ifdef LL_CMP_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Functions CMP LL Exported Functions
  * @brief    CMP LL Exported Functions
  * @{
  */

/** @defgroup CMP_LL_Exported_Functions_Group1 CMP Init and DeInit Functions
  * @brief    CMP Init and DeInit Functions
  * @{
  */

/**
  * @brief  CMP LL Init
  * @param  Instance Specifies CMP peripheral
  * @param  init CMP Init pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_CMP_Init(CMP_TypeDef *Instance, CMP_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_CMP_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_CMP_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_CMP_MspInit(Instance);

    //CMP Disable Before Init
    __LL_CMP_Dis(Instance);

    //CMP Init
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        if (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_CMP)) {
            LL_FUNC_ALTER(init->output_sync_en, __LL_CMP_OutputSync_En(Instance), __LL_CMP_OutputSync_Dis(Instance));
        }
        
    } else {
        __LL_CMP_InputSrc_Set(Instance, init->input_src);
    }
    
    __LL_CMP_NegInSrc_Set(Instance, init->neg_in_src);
    __LL_CMP_PosiInSrc_Set(Instance, init->posi_in_src);

    __LL_CMP_Hyst_Set(Instance, init->hyst);
    __LL_CMP_BlkEvt_Set(Instance, init->blk_evt);
    __LL_CMP_OutputDbc_Set(Instance, init->output_dbc);

    LL_FUNC_ALTER(init->rising_int_en, __LL_CMP_RisingEdge_INT_En(Instance), __LL_CMP_RisingEdge_INT_Dis(Instance));
    LL_FUNC_ALTER(init->falling_int_en, __LL_CMP_FallingEdge_INT_En(Instance), __LL_CMP_FallingEdge_INT_Dis(Instance));
    LL_FUNC_ALTER(init->output_invert_en, __LL_CMP_OutputInvert_En(Instance), __LL_CMP_OutputInvert_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  CMP LL DeInit
  * @param  Instance Specifies CMP peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_CMP_DeInit(CMP_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    if (!IS_CMP_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //CMP Disable
    __LL_CMP_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_CMP_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the CMP MSP
  * @param  Instance Specifies CMP peripheral
  * @return None
  */
__WEAK void LL_CMP_MspInit(CMP_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CMP_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the CMP MSP
  * @param  Instance Specifies CMP peripheral
  * @return None
  */
__WEAK void LL_CMP_MspDeInit(CMP_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CMP_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup CMP_LL_Exported_Functions_Group2 CMP Operation Functions
  * @brief    CMP Operation Functions
  * @{
  */

/**
  * @brief  CMP LL Start
  * @param  Instance Specifies CMP peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_CMP_Start(CMP_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    if (!IS_CMP_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //CMP Enable
    __LL_CMP_En(Instance);

    return LL_OK;
}

/**
  * @brief  CMP LL Stop
  * @param  Instance Specifies CMP peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_CMP_Stop(CMP_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    if (!IS_CMP_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //CMP Disable
    __LL_CMP_Dis(Instance);

    return LL_OK;
}

/**
 * @brief CMP Software Blanking Enable
 * @param Instance Specifies CMP peripheral
 * @return LL Status 
 */
LL_StatusETypeDef LL_CMP_SwBlanking_En(CMP_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    if (!IS_CMP_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Check whether this function is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support Software Blanking!\n");
        return LL_FAILED;
    }

    //CMP enable software blanking event
    __LL_CMP_BlkEvt_Set(Instance, CMP_BLK_EVT_NONE);

    if(__LL_CMP_BlkEvt_Get(Instance) == CMP_BLK_EVT_NONE) {
        //CMP enable software blanking
        __LL_CMP_SwBlanking_En(Instance);
    } else {
        return LL_FAILED;
    }
    
    
    return LL_OK;
}

/**
 * @brief CMP Software Blanking Disable
 * @param Instance Specifies CMP peripheral
 * @return LL Status 
 */
LL_StatusETypeDef LL_CMP_SwBlanking_Dis(CMP_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    if (!IS_CMP_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Check whether this function is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support Software Blanking!\n");
        return LL_FAILED;
    }

    //CMP disable software blanking
    __LL_CMP_SwBlanking_Dis(Instance);
    
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup CMP_LL_Exported_Functions_Interrupt CMP Interrupt Handler and Callback
  * @brief    CMP Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  CMP IRQ Handler
  * @param  Instance Specifies CMP peripheral
  * @return None
  */
void LL_CMP_IRQHandler(CMP_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_CMP_ALL_INSTANCE(Instance));

    if (!IS_CMP_ALL_INSTANCE(Instance)) {
        return;
    }

    //CMP Rising Edge Interrupt Handler
    if (__LL_CMP_IsRisingEdgeIntEn(Instance) && __LL_CMP_IsRisingEdgeIntPnd(Instance)) {
        //Clear Interrupt Pending
        __LL_CMP_RisingEdgeIntPnd_Clr(Instance);

        //Callback
        LL_CMP_RisingEdgeCallback(Instance);
    }

    //CMP Falling Edge Interrupt Handler
    if (__LL_CMP_IsFallingEdgeIntEn(Instance) && __LL_CMP_IsFallingEdgeIntPnd(Instance)) {
        //Clear Interrupt Pending
        __LL_CMP_FallingEdgeIntPnd_Clr(Instance);

        //Callback
        LL_CMP_FallingEdgeCallback(Instance);
    }
}

/**
  * @brief  CMP Rising Edge Interrupt Callback
  * @param  Instance Specifies CMP peripheral
  * @return None
  */
__WEAK void LL_CMP_RisingEdgeCallback(CMP_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CMP_RisingEdgeCallback could be implemented in the user file
     */
}

/**
  * @brief  CMP Falling Edge Interrupt Callback
  * @param  Instance Specifies CMP peripheral
  * @return None
  */
__WEAK void LL_CMP_FallingEdgeCallback(CMP_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CMP_FallingEdgeCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


#endif  /* LL_CMP_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

