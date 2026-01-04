/**
  ******************************************************************************
  * @file    tae32g58xx_ll_qei.c
  * @author  MCD Application Team
  * @brief   QEI LL module driver
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


#define DBG_TAG             "QEI LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup QEI_LL QEI LL
  * @brief    QEI LL module driver
  * @{
  */

#ifdef LL_QEI_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup QEI_LL_Private_Functions QEI LL Private Functions
  * @brief    QEI LL Private Functions
  * @{
  */
static LL_StatusETypeDef QEI_PosCnt_Init(QEI_TypeDef *Instance, QEI_PosCnt_InitTypeDef *init);
static LL_StatusETypeDef QEI_Tmr_Init(QEI_TypeDef *Instance, QEI_Tmr_InitTypeDef *init);
static LL_StatusETypeDef QEI_Cmp_Init(QEI_TypeDef *Instance, QEI_Cmp_InitTypeDef *init);
static LL_StatusETypeDef QEI_Cap_Init(QEI_TypeDef *Instance, QEI_Cap_InitTypeDef *init);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup QEI_LL_Exported_Functions QEI LL Exported Functions
  * @brief    QEI LL Exported Functions
  * @{
  */

/** @defgroup QEI_LL_Exported_Functions_Groupp1 QEI Init and DeInit Functions
  * @brief    QEI Init and DeInit Functions
  * @{
  */

/**
  * @brief  QEI LL Init
  * @param  Instance Specifies QEI peripheral
  * @param  init QEI Init Pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_QEI_Init(QEI_TypeDef *Instance, QEI_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_QEI_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_QEI_MspInit(Instance);

    QEI_Tmr_Init(Instance, &init->tmr_init);
    QEI_Cmp_Init(Instance, &init->cmp_init);
    QEI_Cap_Init(Instance, &init->cap_init);

    return QEI_PosCnt_Init(Instance, &init->pos_cnt_init);
}

/**
  * @brief  QEI LL DeInit
  * @param  Instance Specifies QEI peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_QEI_DeInit(QEI_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));

    if (!IS_QEI_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //QEI Disable
    __LL_QEI_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_QEI_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the QEI MSP
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_MspInit(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the QEI MSP
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_MspDeInit(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup QEI_LL_Exported_Functions_Groupp2 QEI Operation Functions
  * @brief    QEI Operation Functions
  * @{
  */

/**
  * @brief  QEI Enable
  * @param  Instance Specifies QEI peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_QEI_En(QEI_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));

    if (!IS_QEI_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //QEI Enable
    __LL_QEI_En(Instance);

    return LL_OK;
}

/**
  * @brief  QEI Disable
  * @param  Instance Specifies QEI peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_QEI_Dis(QEI_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));

    if (!IS_QEI_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //QEI Enable
    __LL_QEI_Dis(Instance);

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup QEI_LL_Exported_Functions_Interrupt QEI Interrupt Handler and Callback
  * @brief    QEI Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  QEI IRQ Handler
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
void LL_QEI_IRQHandler(QEI_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));

    if (!IS_QEI_ALL_INSTANCE(Instance)) {
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_QEI_AllIntEn_Get(Instance);
    int_pending = __LL_QEI_AllIntPnd_Get(Instance);


    //Capture Done Interrupt Handler
    if ((int_en & QEI0_IENR_CDE_Msk) && (int_pending & QEI0_IENR_CDE_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_CapDoneIntPnd_Clr(Instance);

        //Callback
        LL_QEI_CapDoneCallback(Instance);
    }

    //Positon Counter Reset Interrupt Handler
    if ((int_en & QEI0_IENR_PRE_Msk) && (int_pending & QEI0_STSR_PRS_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_PosCntRstIntPnd_Clr(Instance);

        //Callback
        LL_QEI_PosCntRstCallback(Instance);
    }

    //Positon Counter Initial Interrupt Handler
    if ((int_en & QEI0_IENR_PIE_Msk) && (int_pending & QEI0_STSR_PIS_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_PosCntInitIntPnd_Clr(Instance);

        //Callback
        LL_QEI_PosCntInitCallback(Instance);
    }

    //Timer Overflow Interrupt Handler
    if ((int_en & QEI0_IENR_UTO_Msk) && (int_pending & QEI0_STSR_UTO_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_TmrOverflowIntPnd_Clr(Instance);

        //Callback
        LL_QEI_TmrOverflowCallback(Instance);
    }

    //Positon Counter Latch Interrupt Handler
    if ((int_en & QEI0_IENR_IEL_Msk) && (int_pending & QEI0_STSR_IEL_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_PosCntLatchIntPnd_Clr(Instance);

        //Callback
        LL_QEI_PosCntLatchCallback(Instance);
    }

    //Positon Counter Compare Interrupt Handler
    if ((int_en & QEI0_IENR_PCM_Msk) && (int_pending & QEI0_STSR_PCM_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_PosCntCmpIntPnd_Clr(Instance);

        //Callback
        LL_QEI_PosCntCmpCallback(Instance);
    }

    //Positon Counter Overflow Interrupt Handler
    if ((int_en & QEI0_IENR_PCO_Msk) && (int_pending & QEI0_STSR_PCO_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_PosCntOverflowIntPnd_Clr(Instance);

        //Callback
        LL_QEI_PosCntOverflowCallback(Instance);
    }

    //Positon Counter Underflow Interrupt Handler
    if ((int_en & QEI0_IENR_PCU_Msk) && (int_pending & QEI0_STSR_PCU_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_PosCntUnderflowIntPnd_Clr(Instance);

        //Callback
        LL_QEI_PosCntUnderflowCallback(Instance);
    }

    //Direction Change Interrupt Handler
    if ((int_en & QEI0_IENR_QDC_Msk) && (int_pending & QEI0_STSR_QDC_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_DirChangeIntPnd_Clr(Instance);

        //Callback
        LL_QEI_DirChangeCallback(Instance);
    }

    //Phase Error Interrupt Handler
    if ((int_en & QEI0_IENR_QPE_Msk) && (int_pending & QEI0_STSR_PHE_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_PhaseErrIntPnd_Clr(Instance);

        //Callback
        LL_QEI_PhaseErrCallback(Instance);
    }

    //Position Counter Interrupt Handler
    if ((int_en & QEI0_IENR_PCE_Msk) && (int_pending & QEI0_STSR_PCE_Msk)) {
        //Interrupt Pending Clear
        __LL_QEI_PosCntErrIntPnd_Clr(Instance);

        //Callback
        LL_QEI_PosCntErrCallback(Instance);
    }
}


/**
  * @brief  Capture Done Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_CapDoneCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_CapDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Reset Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_PosCntRstCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_PosCntRstCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Initial Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_PosCntInitCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_PosCntInitCallback could be implemented in the user file
     */
}

/**
  * @brief  Timer Overflow Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_TmrOverflowCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_TmrOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Latch Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_PosCntLatchCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_PosCntLatchCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Compare Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_PosCntCmpCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_PosCntCmpCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Overflow Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_PosCntOverflowCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_PosCntOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Underflow Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_PosCntUnderflowCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_PosCntUnderflowCallback could be implemented in the user file
     */
}

/**
  * @brief  Direction Change Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_DirChangeCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_DirChangeCallback could be implemented in the user file
     */
}

/**
  * @brief  Phase Error Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_PhaseErrCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_PhaseErrCallback could be implemented in the user file
     */
}

/**
  * @brief  Position Counter Error Interrupt Callback Function
  * @param  Instance Specifies QEI peripheral
  * @return None
  */
__WEAK void LL_QEI_PosCntErrCallback(QEI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_QEI_PosCntErrCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup QEI_LL_Private_Functions
  * @{
  */

/**
  * @brief  QEI Position Counter Init
  * @param  Instance Specifies QEI peripheral
  * @param  init  QEI Position Counter Init Pointer
  * @return Status of the Initialization
  */
static LL_StatusETypeDef QEI_PosCnt_Init(QEI_TypeDef *Instance, QEI_PosCnt_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_QEI_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //Init/Max Value Init
    __LL_QEI_PosCntInit_Set(Instance, init->init_val);
    __LL_QEI_PosCntMax_Set(Instance, init->max_val);

    //Input Signal Config
    __LL_QEI_IdxInputPol_Set(Instance, init->idx_pol);
    __LL_QEI_QEAInputPol_Set(Instance, init->qea_pol);
    __LL_QEI_QEBInputPol_Set(Instance, init->qeb_pol);
    LL_FUNC_ALTER(init->swap_en, __LL_QEI_QEA_B_Swap_En(Instance), __LL_QEI_QEA_B_Swap_Dis(Instance));

    //Work Mode Config
    __LL_QEI_PosCntWorkMode_Set(Instance, init->work_mode);
    __LL_QEI_DirCntMode_Set(Instance, init->dir_cnt_mode);
    __LL_QEI_ClkRateMode_Set(Instance, init->clk_rate_mode);
    __LL_QEI_PosCntRstMode_Set(Instance, init->rst_mode);

    //Index Control Config
    __LL_QEI_PosCntIdxInitEdge_Set(Instance, init->idx_init_edge);
    __LL_QEI_PosCntIdxLatchEdge_Set(Instance, init->idx_latch_edge);
    LL_FUNC_ALTER(init->idx_rst_en, __LL_QEI_IdxRstPosCnt_En(Instance), __LL_QEI_IdxRstPosCnt_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  QEI Timer Init
  * @param  Instance Specifies QEI peripheral
  * @param  init  QEI Timer Init Pointer
  * @return Status of the Initialization
  */
static LL_StatusETypeDef QEI_Tmr_Init(QEI_TypeDef *Instance, QEI_Tmr_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_QEI_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    if (!init->enable) {
        __LL_QEI_Tmr_Dis(Instance);
        return LL_OK;
    }

    //Timer Start/Period Value Config
    __LL_QEI_TmrCnt_Set(Instance, init->start_val);
    __LL_QEI_TmrCntPeriod_Set(Instance, init->period_val);

    //Timer Enable
    __LL_QEI_Tmr_En(Instance);

    return LL_OK;
}

/**
  * @brief  QEI Compare Init
  * @param  Instance Specifies QEI peripheral
  * @param  init  QEI Compare Init Pointer
  * @return Status of the Initialization
  */
static LL_StatusETypeDef QEI_Cmp_Init(QEI_TypeDef *Instance, QEI_Cmp_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_QEI_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    if (!init->enable) {
        __LL_QEI_PosCntCmp_Dis(Instance);
        return LL_OK;
    }

    //Compare Config
    __LL_QEI_PosCntCmp_Set(Instance, init->cmp_val);
    LL_FUNC_ALTER(init->shadow_en, __LL_QEI_PosCntCmpShadow_En(Instance), __LL_QEI_PosCntCmpShadow_Dis(Instance));

    //Compare Enable
    __LL_QEI_PosCntCmp_En(Instance);

    return LL_OK;
}

/**
  * @brief  QEI Capture Init
  * @param  Instance Specifies QEI peripheral
  * @param  init  QEI Capture Init Pointer
  * @return Status of the Initialization
  */
static LL_StatusETypeDef QEI_Cap_Init(QEI_TypeDef *Instance, QEI_Cap_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_QEI_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_QEI_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    if (!init->enable) {
        __LL_QEI_Cap_Dis(Instance);
        return LL_OK;
    }

    //Capture Config
    __LL_QEI_CapEvtDiv_Set(Instance, init->evt_div);
    __LL_QEI_CapTmrClkDiv_Set(Instance, init->tmr_clk_div);
    __LL_QEI_CapLatchMode_Set(Instance, init->latch_mode);

    //Capture Enable
    __LL_QEI_Cap_En(Instance);

    return LL_OK;
}

/**
  * @}
  */


#endif  /* LL_QEI_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

