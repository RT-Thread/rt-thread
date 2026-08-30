/**
  ******************************************************************************
  * @file    tae32g58xx_ll_tmr.c
  * @author  MCD Application Team
  * @brief   TMR LL module driver
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


#define DBG_TAG             "TMR LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup TMR_LL TMR LL
  * @brief    TMR LL module driver
  * @{
  */

#ifdef LL_TMR_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/** @defgroup TMR_LL_Private_Constants TMR LL Private Constants
  * @brief    TMR LL Private Constants
  * @{
  */

/**
  * @brief TMR Defaul Timeout definition in ms Unit
  */
#define TMR_DEFAULT_TIMEOUT                 (10)

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/** @defgroup TMR_LL_Private_Macros TMR LL Private Macros
  * @brief    TMR LL Private Macros
  * @{
  */

/**
  * @brief  TMR Input Capture Channel Config Macro Definition
  * @param  Instance Specifies TMR peripheral
  * @param  x Channel Number Range [0, 3]
  * @param  cfg_ptr TMR_InputCapInitTypeDef type Config Pointer
  * @return None
  */
#define TMR_INPUT_CAP_CHx_CFG(Instance, x, cfg_ptr)                             \
    do {                                                                        \
        __LL_TMR_CC##x##_CapFil_Set(Instance, cfg_ptr->filter);                 \
        __LL_TMR_CC##x##_CapPrescaler_Set(Instance, cfg_ptr->prescaler);        \
        __LL_TMR_CC##x##_CapCmpDir_Set(Instance, cfg_ptr->input_map);           \
        __LL_TMR_CC##x##_CapPol_Set(Instance, cfg_ptr->pol);                    \
        __LL_TMR_CH##x##_CapInputSrc_Set(Instance, cfg_ptr->input_src);         \
        __LL_TMR_CC##x##_Cap_En(Instance);                                      \
    } while (0)

/**
  * @brief  TMR Output Compare Channel Config Macro Definition
  * @param  Instance Specifies TMR peripheral
  * @param  x Channel Number Range [0, 3]
  * @param  cfg_ptr TMR_OutputCmpInitTypeDef type Config Pointer
  * @return None
  */
#define TMR_OUTPUT_CMP_CHx_CFG(Instance, x, cfg_ptr)                            \
    do {                                                                        \
        LL_FUNC_ALTER(cfg_ptr->auto_preload_en,                                 \
                      __LL_TMR_CC##x##_CmpAutoPreload_En(Instance),             \
                      __LL_TMR_CC##x##_CmpAutoPreload_Dis(Instance));           \
        __LL_TMR_CC##x##_CmpVal_Set(Instance, cfg_ptr->match_val);              \
        __LL_TMR_CC##x##_CmpMode_Set(Instance, cfg_ptr->mode);                  \
        __LL_TMR_CC##x##_CapCmpDir_Set(Instance, 0x00);                         \
        LL_FUNC_ALTER(cfg_ptr->trig_output_en,                                  \
                      __LL_TMR_CH##x##_Trig_En(Instance),                       \
                      __LL_TMR_CH##x##_Trig_Dis(Instance));                     \
        LL_FUNC_ALTER(cfg_ptr->OC_en,                                           \
                      __LL_TMR_CC##x##_Cmp_En(Instance),                        \
                      __LL_TMR_CC##x##_Cmp_Dis(Instance));                      \
        LL_FUNC_ALTER(cfg_ptr->OCN_en,                                          \
                      __LL_TMR_CC##x##N_Cmp_En(Instance),                       \
                      __LL_TMR_CC##x##N_Cmp_Dis(Instance));                     \
        __LL_TMR_CC##x##_CmpPol_Set(Instance, cfg_ptr->OC_pol);                 \
        __LL_TMR_CC##x##N_CmpPol_Set(Instance, cfg_ptr->OCN_pol);               \
        __LL_TMR_CH##x##_OutputIdleState_Set(Instance, cfg_ptr->OC_idle_sta);   \
        __LL_TMR_CH##x##N_OutputIdleState_Set(Instance, cfg_ptr->OCN_idle_sta); \
    } while (0)

/**
  * @}
  */


/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup TMR_LL_Private_Functions TMR LL Private Functions
  * @brief    TMR LL Private Functions
  * @{
  */
__STATIC_INLINE LL_StatusETypeDef TMR_Base_Init(TMR_TypeDef *Instance, TMR_BaseInitTypeDef *init);
__STATIC_INLINE LL_StatusETypeDef TMR_InputCap_Init(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_InputCapInitTypeDef *init);
__STATIC_INLINE LL_StatusETypeDef TMR_OutputCmp_Init(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_OutputCmpInitTypeDef *init);
__STATIC_INLINE LL_StatusETypeDef TMR_Slv_Init(TMR_TypeDef *Instance, TMR_SlvInitTypeDef *init);
__STATIC_INLINE LL_StatusETypeDef TMR_BrkDz_Init(TMR_TypeDef *Instance, TMR_BrkDzInitTypeDef *init);
__STATIC_INLINE LL_StatusETypeDef TMR_LowPwr_Init(TMR_TypeDef *Instance, TMR_LowPwrInitTypeDef *init);
__STATIC_INLINE LL_StatusETypeDef TMR_LowPwrBase_Init(TMR_TypeDef *Instance, TMR_BaseInitTypeDef *init, uint32_t timeout);
__STATIC_INLINE LL_StatusETypeDef TMR_LowPwrOutputCmp_Init(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_OutputCmpInitTypeDef *init, uint32_t timeout);
__STATIC_INLINE LL_StatusETypeDef TMR_LowPwrSlv_Init(TMR_TypeDef *Instance, TMR_SlvInitTypeDef *init);


/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup TMR_LL_Exported_Functions TMR LL Exported Functions
  * @brief    TMR LL Exported Functions
  * @{
  */

/** @defgroup TMR_LL_Exported_Functions_Group1 TMR Init and DeInit Functions
  * @brief    TMR Init and DeInit Functions
  * @{
  */

/**
  * @brief  TMR LL Init
  * @param  Instance Specifies TMR peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_TMR_Init(TMR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_TMR_MspInit(Instance);

    return LL_OK;
}

/**
  * @brief  TMR LL DeInit
  * @param  Instance Specifies TMR peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_TMR_DeInit(TMR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //ALL Function (Base/Input Capture/Output Compare) Disable
    __LL_TMR_CC0_Cap_Dis(Instance);
    __LL_TMR_CC1_Cap_Dis(Instance);
    __LL_TMR_CC2_Cap_Dis(Instance);
    __LL_TMR_CC3_Cap_Dis(Instance);
    __LL_TMR_CC0N_Cmp_Dis(Instance);
    __LL_TMR_CC1N_Cmp_Dis(Instance);
    __LL_TMR_CC2N_Cmp_Dis(Instance);
    __LL_TMR_CC3N_Cmp_Dis(Instance);

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (IS_LPTMR_ALL_INSTANCE(Instance))) {
        if (__LL_LPTMR_IsEn(Instance)) {
            __LL_LPTMR_Dis(Instance);
        }
    } else {
        __LL_TMR_Dis(Instance);
    }

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_TMR_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  TMR MSP Init
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_MspInit(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_MspInit could be implemented in the user file
     */
}

/**
  * @brief  TMR MSP DeInit
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_MspDeInit(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup TMR_LL_Exported_Functions_Group2 TMR Peripheral Control Functions
  * @brief    TMR Peripheral Control Functions
  * @{
  */

/**
  * @brief  TMR Base Function Config
  * @param  Instance Specifies TMR peripheral
  * @param  cfg TMR base config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_Base_Cfg(TMR_TypeDef *Instance, TMR_BaseInitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_TMR_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return TMR_Base_Init(Instance, cfg);
}

/**
  * @brief  LPTMR Base Function Config
  * @note   Only LPTMR support Low Power Function
  * @param  Instance Specifies TMR peripheral
  * @param  cfg TMR base config pointer
  * @param  timeout Configuration updata timeout (Recommended: at least 2 ticks)
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_LowPwrBase_Cfg(TMR_TypeDef *Instance, TMR_BaseInitTypeDef *cfg, uint32_t timeout)
{
    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_LPTMR_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Check whether this config is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support TMR Low Power Config!\n");
        return LL_FAILED;
    }

    return TMR_LowPwrBase_Init(Instance, cfg, timeout);
}

/**
  * @brief  TMR Input Capture Function Config
  * @note   BSTMR don't support Input Capture Function
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Capture Channel
  * @param  cfg TMR Input Capture config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_InputCap_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_InputCapInitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(!IS_BSTMR_ALL_INSTANCE(Instance));
    assert_param(!IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_TMR_ALL_INSTANCE(Instance) || IS_BSTMR_ALL_INSTANCE(Instance) || IS_LPTMR_ALL_INSTANCE(Instance) ||cfg == NULL) {
        return LL_INVALID;
    }

    return TMR_InputCap_Init(Instance, ch, cfg);
}

/**
  * @brief  TMR Output Compare Function Config
  * @note   BSTMR don't support Output Compare Function
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Compare Channel
  * @param  cfg TMR Output Compare config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_OutputCmp_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_OutputCmpInitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(!IS_BSTMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_TMR_ALL_INSTANCE(Instance) || IS_BSTMR_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return TMR_OutputCmp_Init(Instance, ch, cfg);
}

/**
  * @brief  LPTMR Output Compare Function Config
  * @note   Only LPTMR support Low Power Function
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Compare Channel
  * @param  cfg TMR Output Compare config pointer
  * @param  timeout Configuration updata timeout (Recommended: at least 2 ticks)
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_LowPwrOutputCmp_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch,
        TMR_OutputCmpInitTypeDef *cfg, uint32_t timeout)
{
    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_LPTMR_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Check whether this config is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support TMR Low Power Config!\n");
        return LL_FAILED;
    }

    return TMR_LowPwrOutputCmp_Init(Instance, ch, cfg, timeout);
}

/**
  * @brief  TMR Slave Function Config
  * @note   BSTMR don't support Slave Function
  * @param  Instance Specifies TMR peripheral
  * @param  cfg TMR Slave config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_Slv_Cfg(TMR_TypeDef *Instance, TMR_SlvInitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(!IS_BSTMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_TMR_ALL_INSTANCE(Instance) || IS_BSTMR_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return TMR_Slv_Init(Instance, cfg);
}

/**
  * @brief  LPTMR Slave Function Config
  * @note   Only LPTMR support Low Power Function
  * @param  Instance Specifies TMR peripheral
  * @param  cfg TMR Slave config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_LowPwrSlv_Cfg(TMR_TypeDef *Instance, TMR_SlvInitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_LPTMR_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Check whether this config is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support TMR Low Power Config!\n");
        return LL_FAILED;
    }

    return TMR_LowPwrSlv_Init(Instance, cfg);
}

/**
  * @brief  TMR Break/DeadZone Function Config
  * @note   Only GPTMRX and ADTMR support Break/DeadZone Function
  * @param  Instance Specifies TMR peripheral
  * @param  cfg TMR Break/DeadZone config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_BrkDz_Cfg(TMR_TypeDef *Instance, TMR_BrkDzInitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_GPTMRX_ALL_INSTANCE(Instance) || IS_ADTMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!(IS_GPTMRX_ALL_INSTANCE(Instance) || IS_ADTMR_ALL_INSTANCE(Instance)) || cfg == NULL) {
        return LL_INVALID;
    }

    return TMR_BrkDz_Init(Instance, cfg);
}

/**
  * @brief  TMR Low Power Config
  * @note   Only LPTMR support Low Power Function
  * @param  Instance Specifies TMR peripheral
  * @param  cfg TMR Low Power config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_LowPwr_Cfg(TMR_TypeDef *Instance, TMR_LowPwrInitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if ((!IS_LPTMR_ALL_INSTANCE(Instance)) || (cfg == NULL)) {
        return LL_INVALID;
    }

    //Check whether this config is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support TMR Low Power Config!\n");
        return LL_FAILED;
    }

    return TMR_LowPwr_Init(Instance, cfg);
}

/**
  * @}
  */


/** @defgroup TMR_LL_Exported_Functions_Group3 TMR Operation Functions
  * @brief    TMR Operation Functions
  * @{
  */

/**
  * @brief  Timer Start
  * @param  Instance Specifies TMR peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_Start(TMR_TypeDef *Instance)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Timer Start
    __LL_TMR_En(Instance);

    //Do not enable LPTMR immediately after disabling
    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (IS_LPTMR_ALL_INSTANCE(Instance))) {
        tickstart = LL_GetTick();
        while (!__LL_LPTMR_IsEn(Instance)) {
            __LL_LPTMR_En(Instance);
            if (LL_GetTick() - tickstart > 2) {
                return LL_FAILED;
            }
        }
    }

    return LL_OK;
}

/**
  * @brief  Low Power Timer Start
  * @param  Instance Specifies TMR peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_LowPwrStart(TMR_TypeDef *Instance)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));

    if (!IS_LPTMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Timer Start
    __LL_LPTMR_En(Instance);

    //Do not enable LPTMR immediately after disabling
    tickstart = LL_GetTick();
    while (!__LL_LPTMR_IsEn(Instance)) {
        __LL_LPTMR_En(Instance);
        if (LL_GetTick() - tickstart > TMR_DEFAULT_TIMEOUT) {
            return LL_FAILED;
        }
    }

    return LL_OK;
}


/**
  * @brief  Timer Stop
  * @param  Instance Specifies TMR peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_Stop(TMR_TypeDef *Instance)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Timer Stop
    __LL_TMR_Dis(Instance);

    //Do not disable LPTMR immediately after disabling
    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (IS_LPTMR_ALL_INSTANCE(Instance))) {
        tickstart = LL_GetTick();
        while (__LL_LPTMR_IsEn(Instance)) {
            if (LL_GetTick() - tickstart > TMR_DEFAULT_TIMEOUT) {
                return LL_FAILED;
            }
        }
    }

    return LL_OK;
}


/**
  * @brief  Low Power Timer Stop
  * @param  Instance Specifies TMR peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_LowPwrStop(TMR_TypeDef *Instance)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));

    if (!IS_LPTMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Timer Stop
    __LL_LPTMR_Dis(Instance);

    //Do not disable LPTMR immediately after disabling
    tickstart = LL_GetTick();
    while (__LL_LPTMR_IsEn(Instance)) {
        if (LL_GetTick() - tickstart > TMR_DEFAULT_TIMEOUT) {
            return LL_FAILED;
        }
    }

    return LL_OK;
}


/**
  * @brief  Timer Start with Interrupt Enable
  * @note   Please Enable other Interrupt (e.g. Input Capture/Output Compare) before if need
  * @param  Instance Specifies TMR peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_Start_IT(TMR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Overflow Interrupt Enable Default
    __LL_TMR_Overflow_INT_En(Instance);

    //Update Event Interrupt Enable if Update event is Enable
    if (__LL_TMR_IsUpdateEvtEn(Instance)) {
        __LL_TMR_UpdateEvt_INT_En(Instance);
    }

    //Timer Start
    __LL_TMR_En(Instance);

    return LL_OK;
}

/**
  * @brief  Timer Stop with Interrupt Disable
  * @note   Please Disbale other Interrupt (e.g. Input Capture/Output Compare) before if need
  * @param  Instance Specifies TMR peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_Stop_IT(TMR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Counter Overflow Disable
    __LL_TMR_Overflow_INT_Dis(Instance);

    //Update Event Interrupt Disable
    __LL_TMR_UpdateEvt_INT_Dis(Instance);

    //Timer Stop
    __LL_TMR_Dis(Instance);

    return LL_OK;
}

/**
  * @brief  TMR Input Capture/Output Compare Interrupt Enable/Disable
  * @note   BSTMR don't support Capture/Compare Interrupt
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Input Capture/Output Compare Channel
  * @param  int_en Interrupt Enable/Disable
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_CapCmpInt_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, bool int_en)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(!IS_BSTMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance) || IS_BSTMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    switch (ch) {
        case TMR_CAP_CMP_CH_0:
            LL_FUNC_ALTER(int_en, __LL_TMR_CC0_CapCmp_INT_En(Instance), __LL_TMR_CC0_CapCmp_INT_Dis(Instance));
            break;

        case TMR_CAP_CMP_CH_1:
            LL_FUNC_ALTER(int_en, __LL_TMR_CC1_CapCmp_INT_En(Instance), __LL_TMR_CC1_CapCmp_INT_Dis(Instance));
            break;

        case TMR_CAP_CMP_CH_2:
            LL_FUNC_ALTER(int_en, __LL_TMR_CC2_CapCmp_INT_En(Instance), __LL_TMR_CC2_CapCmp_INT_Dis(Instance));
            break;

        case TMR_CAP_CMP_CH_3:
            LL_FUNC_ALTER(int_en, __LL_TMR_CC3_CapCmp_INT_En(Instance), __LL_TMR_CC3_CapCmp_INT_Dis(Instance));
            break;

        default:
            LOG_E("Invalid Channel-[%d]!\n", ch);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @brief  TMR Output Compare Interrupt Enable/Disable
  * @note   BSTMR don't support Compare Interrupt
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Input Capture/Output Compare Channel
  * @param  int_en Interrupt Enable/Disable
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_LowPwrCmpInt_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, bool int_en)
{
    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));

    if (!IS_LPTMR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    switch (ch) {
        case TMR_CAP_CMP_CH_0:
            LL_FUNC_ALTER(int_en, __LL_LPTMR_Cmp_INT_En(Instance), __LL_LPTMR_Cmp_INT_Dis(Instance));
            break;

        default:
            LOG_E("Invalid Channel-[%d]!\n", ch);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @brief  Generate a software event
  * @param  Instance Specifies TMR peripheral
  * @param  evt specifies event to generate
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_EvtGen(TMR_TypeDef *Instance, TMR_EvtGenETypeDef evt)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(evt < TMR_EVT_GEN_NUMS);

    if (!IS_TMR_ALL_INSTANCE(Instance) || evt >= TMR_EVT_GEN_NUMS) {
        return LL_INVALID;
    }

    __LL_TMR_EvtX_Gen(Instance, evt);

    return LL_OK;
}

/**
  * @brief  Low Power Timer Generate a software event
  * @param  Instance Specifies TMR peripheral
  * @param  evt specifies event to generate
  * @return LL Status
  */
LL_StatusETypeDef LL_TMR_LowPwrEvtGen(TMR_TypeDef *Instance, TMR_EvtGenETypeDef evt)
{
    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(evt < TMR_EVT_GEN_NUMS);

    if (!IS_LPTMR_ALL_INSTANCE(Instance) || evt >= TMR_EVT_GEN_NUMS) {
        return LL_INVALID;
    }

    __LL_LPTMR_EvtX_Gen(Instance, evt);

    return LL_OK;
}


/**
  * @brief  Timer Input Capture Value Get
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Input Capture Channel
  * @return Capture Value
  */
uint32_t LL_TMR_InputCapVal_Get(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance)) {
        return 0;
    }

    switch (ch) {
        case TMR_CAP_CMP_CH_0:
            return __LL_TMR_CC0_CapVal_Get(Instance);

        case TMR_CAP_CMP_CH_1:
            return __LL_TMR_CC1_CapVal_Get(Instance);

        case TMR_CAP_CMP_CH_2:
            return __LL_TMR_CC2_CapVal_Get(Instance);

        case TMR_CAP_CMP_CH_3:
            return __LL_TMR_CC3_CapVal_Get(Instance);

        default:
            LOG_E("Invalid Capture Channel-[%d]!\n", ch);
            return 0;
    }
}

/**
  * @}
  */


/** @defgroup TMR_LL_Exported_Functions_Interrupt TMR Interrupt Handler and Callback
  * @brief    TMR Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  TMR IRQ Handler
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
void LL_TMR_IRQHandler(TMR_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (!IS_TMR_ALL_INSTANCE(Instance)) {
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_TMR_AllIntEn_Get(Instance);
    int_pending = __LL_TMR_AllIntPnd_Get(Instance);


    //Counter Overflow Interrupt Handler
    if ((int_en & TMR9_IER_OVIE_Msk) && (int_pending & TMR9_SR_OVIF_Msk)) {
        //Claer Interrupt Pending
        __LL_TMR_OverflowIntPnd_Clr(Instance);

        //Callback
        LL_TMR_OverflowCallback(Instance);
    }

    //Counter Update Interrupt Handler
    if ((int_en & TMR9_IER_UIE_Msk) && (int_pending & TMR9_SR_UIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_UpdateIntPnd_Clr(Instance);

        //Callback
        LL_TMR_UpdateCallback(Instance);
    }


    //Trigger Interrupt Handler
    if ((int_en & TMR9_IER_TIE_Msk) && (int_pending & TMR9_SR_TIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_TrigIntPnd_Clr(Instance);

        //Callback
        LL_TMR_TrigCallback(Instance);
    }


    //Break 0 Interrupt Handler
    if ((int_en & TMR9_IER_BIE_Msk) && (int_pending & TMR9_SR_B0IF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_Brk0IntPnd_Clr(Instance);

        //Callback
        LL_TMR_Brk0Callback(Instance);
    }

    //Break 1 Interrupt Handler
    if ((int_en & TMR9_IER_BIE_Msk) && (int_pending & TMR9_SR_B1IF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_Brk1IntPnd_Clr(Instance);

        //Callback
        LL_TMR_Brk1Callback(Instance);
    }

    //System Fault Break Interrupt Handler
    if ((int_en & TMR9_IER_BIE_Msk) && (int_pending & TMR9_SR_SBIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_SysFaultBrkIntPnd_Clr(Instance);

        //Callback
        LL_TMR_SysFaultBrkCallback(Instance);
    }


    //CH3 OverCapture Interrupt Handler
    if ((int_en & TMR9_IER_C3OIE_Msk) && (int_pending & TMR9_SR_CC3OIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC3_OverCapIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH3_OverCapCallback(Instance);
    }

    //CH3 Capture/Compare Interrupt Handler
    if ((int_en & TMR9_IER_C3MIE_Msk) && (int_pending & TMR9_SR_CC3MIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC3_CapCmpIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH3_CapCmpCallback(Instance);
    }

    //CH2 OverCapture Interrupt Handler
    if ((int_en & TMR9_IER_C2OIE_Msk) && (int_pending & TMR9_SR_CC2OIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC2_OverCapIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH2_OverCapCallback(Instance);
    }

    //CH2 Capture/Compare Interrupt Handler
    if ((int_en & TMR9_IER_C2MIE_Msk) && (int_pending & TMR9_SR_CC2MIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC2_CapCmpIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH2_CapCmpCallback(Instance);
    }

    //CH1 OverCapture Interrupt Handler
    if ((int_en & TMR9_IER_C1OIE_Msk) && (int_pending & TMR9_SR_CC1OIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC1_OverCapIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH1_OverCapCallback(Instance);
    }

    //CH1 Capture/Compare Interrupt Handler
    if ((int_en & TMR9_IER_C1MIE_Msk) && (int_pending & TMR9_SR_CC1MIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC1_CapCmpIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH1_CapCmpCallback(Instance);
    }

    //CH0 OverCapture Interrupt Handler
    if ((int_en & TMR9_IER_C0OIE_Msk) && (int_pending & TMR9_SR_CC0OIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC0_OverCapIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH0_OverCapCallback(Instance);
    }

    //CH0 Capture/Compare Interrupt Handler
    if ((int_en & TMR9_IER_C0MIE_Msk) && (int_pending & TMR9_SR_CC0MIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC0_CapCmpIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH0_CapCmpCallback(Instance);
    }
}

/**
  * @brief  TMR Update IRQ Handler
  * @param  Instance Specifies TMR peripheral
  * @note   Only ADTMR separate Update/Trigger/Break/CaptureCompare Interrupt entry
  * @return None
  */
void LL_TMR_Upd_IRQHandler(TMR_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_ADTMR_ALL_INSTANCE(Instance));

    if (!IS_ADTMR_ALL_INSTANCE(Instance)) {
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_TMR_AllIntEn_Get(Instance);
    int_pending = __LL_TMR_AllIntPnd_Get(Instance);


    //Counter Overflow Interrupt Handler
    if ((int_en & TMR9_IER_OVIE_Msk) && (int_pending & TMR9_SR_OVIF_Msk)) {
        //Claer Interrupt Pending
        __LL_TMR_OverflowIntPnd_Clr(Instance);

        //Callback
        LL_TMR_OverflowCallback(Instance);
    }

    //Counter Update Interrupt Handler
    if ((int_en & TMR9_IER_UIE_Msk) && (int_pending & TMR9_SR_UIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_UpdateIntPnd_Clr(Instance);

        //Callback
        LL_TMR_UpdateCallback(Instance);
    }
}

/**
  * @brief  TMR Trigger IRQ Handler
  * @param  Instance Specifies TMR peripheral
  * @note   Only ADTMR separate Update/Trigger/Break/CaptureCompare Interrupt entry
  * @return None
  */
void LL_TMR_Trg_IRQHandler(TMR_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_ADTMR_ALL_INSTANCE(Instance));

    if (!IS_ADTMR_ALL_INSTANCE(Instance)) {
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_TMR_AllIntEn_Get(Instance);
    int_pending = __LL_TMR_AllIntPnd_Get(Instance);


    //Trigger Interrupt Handler
    if ((int_en & TMR9_IER_TIE_Msk) && (int_pending & TMR9_SR_TIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_TrigIntPnd_Clr(Instance);

        //Callback
        LL_TMR_TrigCallback(Instance);
    }
}

/**
  * @brief  TMR Break IRQ Handler
  * @param  Instance Specifies TMR peripheral
  * @note   Only ADTMR separate Update/Trigger/Break/CaptureCompare Interrupt entry
  * @return None
  */
void LL_TMR_Brk_IRQHandler(TMR_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_ADTMR_ALL_INSTANCE(Instance));

    if (!IS_ADTMR_ALL_INSTANCE(Instance)) {
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_TMR_AllIntEn_Get(Instance);
    int_pending = __LL_TMR_AllIntPnd_Get(Instance);


    //Break 0 Interrupt Handler
    if ((int_en & TMR9_IER_BIE_Msk) && (int_pending & TMR9_SR_B0IF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_Brk0IntPnd_Clr(Instance);

        //Callback
        LL_TMR_Brk0Callback(Instance);
    }

    //Break 1 Interrupt Handler
    if ((int_en & TMR9_IER_BIE_Msk) && (int_pending & TMR9_SR_B1IF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_Brk1IntPnd_Clr(Instance);

        //Callback
        LL_TMR_Brk1Callback(Instance);
    }

    //System Fault Break Interrupt Handler
    if ((int_en & TMR9_IER_BIE_Msk) && (int_pending & TMR9_SR_SBIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_SysFaultBrkIntPnd_Clr(Instance);

        //Callback
        LL_TMR_SysFaultBrkCallback(Instance);
    }
}

/**
  * @brief  TMR Capture/Compare IRQ Handler
  * @param  Instance Specifies TMR peripheral
  * @note   Only ADTMR separate Update/Trigger/Break/CaptureCompare Interrupt entry
  * @return None
  */
void LL_TMR_CC_IRQHandler(TMR_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_ADTMR_ALL_INSTANCE(Instance));

    if (!IS_ADTMR_ALL_INSTANCE(Instance)) {
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_TMR_AllIntEn_Get(Instance);
    int_pending = __LL_TMR_AllIntPnd_Get(Instance);


    //CH3 OverCapture Interrupt Handler
    if ((int_en & TMR9_IER_C3OIE_Msk) && (int_pending & TMR9_SR_CC3OIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC3_OverCapIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH3_OverCapCallback(Instance);
    }

    //CH3 Capture/Compare Interrupt Handler
    if ((int_en & TMR9_IER_C3MIE_Msk) && (int_pending & TMR9_SR_CC3MIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC3_CapCmpIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH3_CapCmpCallback(Instance);
    }

    //CH2 OverCapture Interrupt Handler
    if ((int_en & TMR9_IER_C2OIE_Msk) && (int_pending & TMR9_SR_CC2OIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC2_OverCapIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH2_OverCapCallback(Instance);
    }

    //CH2 Capture/Compare Interrupt Handler
    if ((int_en & TMR9_IER_C2MIE_Msk) && (int_pending & TMR9_SR_CC2MIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC2_CapCmpIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH2_CapCmpCallback(Instance);
    }

    //CH1 OverCapture Interrupt Handler
    if ((int_en & TMR9_IER_C1OIE_Msk) && (int_pending & TMR9_SR_CC1OIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC1_OverCapIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH1_OverCapCallback(Instance);
    }

    //CH1 Capture/Compare Interrupt Handler
    if ((int_en & TMR9_IER_C1MIE_Msk) && (int_pending & TMR9_SR_CC1MIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC1_CapCmpIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH1_CapCmpCallback(Instance);
    }

    //CH0 OverCapture Interrupt Handler
    if ((int_en & TMR9_IER_C0OIE_Msk) && (int_pending & TMR9_SR_CC0OIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC0_OverCapIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH0_OverCapCallback(Instance);
    }

    //CH0 Capture/Compare Interrupt Handler
    if ((int_en & TMR9_IER_C0MIE_Msk) && (int_pending & TMR9_SR_CC0MIF_Msk)) {
        //Clear Interrupt Pending
        __LL_TMR_CC0_CapCmpIntPnd_Clr(Instance);

        //Callback
        LL_TMR_CH0_CapCmpCallback(Instance);
    }
}


/**
  * @brief  TMR Overflow Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_OverflowCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_OverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR Update Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_UpdateCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_UpdateCallback could be implemented in the user file
     */
}


/**
  * @brief  TMR Trigger Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_TrigCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_TrigCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR Break 0 Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_Brk0Callback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_Brk0Callback could be implemented in the user file
     */
}

/**
  * @brief  TMR Break 1 Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_Brk1Callback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_Brk1Callback could be implemented in the user file
     */
}

/**
  * @brief  TMR System Fault Break Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_SysFaultBrkCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_SysFaultBrkCallback could be implemented in the user file
     */
}


/**
  * @brief  TMR CH3 OverCapture Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_CH3_OverCapCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_CH3_OverCapCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR CH3 Capture/Compare Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_CH3_CapCmpCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_CH3_CapCmpCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR CH2 OverCapture Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_CH2_OverCapCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_CH2_OverCapCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR CH2 Capture/Compare Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_CH2_CapCmpCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_CH2_CapCmpCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR CH1 OverCapture Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_CH1_OverCapCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_CH1_OverCapCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR CH1 Capture/Compare Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_CH1_CapCmpCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_CH1_CapCmpCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR CH0 OverCapture Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_CH0_OverCapCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_CH0_OverCapCallback could be implemented in the user file
     */
}

/**
  * @brief  TMR CH0 Capture/Compare Interrupt Callback Function
  * @param  Instance Specifies TMR peripheral
  * @return None
  */
__WEAK void LL_TMR_CH0_CapCmpCallback(TMR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_TMR_CH0_CapCmpCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup TMR_LL_Private_Functions
  * @{
  */

/**
  * @brief  TMR Base Function Init
  * @param  Instance Specifies TMR peripheral
  * @param  init TMR base init pointer
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_Base_Init(TMR_TypeDef *Instance, TMR_BaseInitTypeDef *init)
{
    uint32_t tickstart;
    const uint32_t timeout = TMR_DEFAULT_TIMEOUT;

    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_TMR_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //Base Config
    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (IS_LPTMR_ALL_INSTANCE(Instance))) {
        __LL_LPTMR_CounterPeriod_Set(Instance, init->period);
        tickstart = LL_GetTick();
        while (!__LL_LPTMR_IsPrdUpdDone(Instance)) {
            if (LL_GetTick() - tickstart > timeout) {
                return LL_TIMEOUT;
            }
        }

        __LL_LPTMR_PrescalerDivVal_Set(Instance, init->prescaler);
    } else {
        __LL_TMR_CounterPeriod_Set(Instance, init->period);
        __LL_TMR_PrescalerDivVal_Set(Instance, init->prescaler);
    }

    __LL_TMR_WorkMode_Set(Instance, init->work_mode);
    __LL_TMR_MstMode_Set(Instance, init->mst_mode);
    __LL_TMR_UpdateEvtSrc_Set(Instance, init->update_evt_src);
    LL_FUNC_ALTER(init->update_evt_en, __LL_TMR_UpdateEvt_En(Instance), __LL_TMR_UpdateEvt_Dis(Instance));
    LL_FUNC_ALTER(init->auto_preload_en, __LL_TMR_AutoPreload_En(Instance), __LL_TMR_AutoPreload_Dis(Instance));

    __LL_TMR_TrigOutputWidth_Set(Instance, init->trgo_width);

    //Advance Config
    __LL_TMR_CounterRepeatVal_Set(Instance, init->rep_cnt);
    __LL_TMR_CtrAlignMode_Set(Instance, init->ctr_align_mode);
    __LL_TMR_CntDir_Set(Instance, init->cnt_dir);
    __LL_TMR_DzDigFilClkDiv_Set(Instance, init->dz_clk_div);

    return LL_OK;
}

/**
  * @brief  LPTMR Base Function Init
  * @param  Instance Specifies TMR peripheral
  * @param  init LPTMR base init pointer
  * @param  timeout Configuration updata timeout (Recommended: at least 2 ticks)
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_LowPwrBase_Init(TMR_TypeDef *Instance, TMR_BaseInitTypeDef *init, uint32_t timeout)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_LPTMR_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //Base Config
    LL_FUNC_ALTER(init->auto_preload_en, __LL_LPTMR_AutoPreload_En(Instance), __LL_LPTMR_AutoPreload_Dis(Instance));

    __LL_LPTMR_CounterPeriod_Set(Instance, init->period);
    tickstart = LL_GetTick();
    if (LL_WAIT_FOREVER == timeout) {
        while (!__LL_LPTMR_IsPrdUpdDone(Instance));
    } else {
        while (!__LL_LPTMR_IsPrdUpdDone(Instance)) {
            if (LL_GetTick() - tickstart > timeout) {
                return LL_TIMEOUT;
            }
        }
    }

    __LL_LPTMR_PrescalerDivVal_Set(Instance, init->prescaler);
    __LL_LPTMR_WorkMode_Set(Instance, init->work_mode);
    
    return LL_OK;
}

/**
  * @brief  TMR Input Capture Function Init
  * @note   BSTMR and LPTMR don't support Input Capture Function
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Capture Channel
  * @param  init TMR Input Capture init pointer
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_InputCap_Init(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_InputCapInitTypeDef *init)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(!IS_BSTMR_ALL_INSTANCE(Instance));
    assert_param(!IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_TMR_ALL_INSTANCE(Instance) || IS_BSTMR_ALL_INSTANCE(Instance) || IS_LPTMR_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //Input Capture Init
    switch (ch) {
        case TMR_CAP_CMP_CH_0:
            TMR_INPUT_CAP_CHx_CFG(Instance, 0, init);
            break;

        case TMR_CAP_CMP_CH_1:
            TMR_INPUT_CAP_CHx_CFG(Instance, 1, init);
            break;

        case TMR_CAP_CMP_CH_2:
            TMR_INPUT_CAP_CHx_CFG(Instance, 2, init);
            break;

        case TMR_CAP_CMP_CH_3:
            TMR_INPUT_CAP_CHx_CFG(Instance, 3, init);
            break;

        default:
            LOG_E("Invalid Capture Channel-[%d]!\n", ch);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @brief  TMR Output Compare Function Init
  * @note   BSTMR don't support Output Compare Function
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Compare Channel
  * @param  init TMR Output Compare init pointer
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_OutputCmp_Init(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_OutputCmpInitTypeDef *init)
{
    uint32_t tickstart;
    const uint32_t timeout = TMR_DEFAULT_TIMEOUT;

    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(!IS_BSTMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_TMR_ALL_INSTANCE(Instance) || IS_BSTMR_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (IS_LPTMR_ALL_INSTANCE(Instance))) {
        if (TMR_CAP_CMP_CH_0 == ch) {
            //Output Compare Init
            LL_FUNC_ALTER(init->auto_preload_en,
                        __LL_LPTMR_CmpAutoPreload_En(Instance),
                        __LL_LPTMR_CmpAutoPreload_Dis(Instance));
            __LL_LPTMR_CmpPol_Set(Instance, init->OC_pol);

            __LL_LPTMR_CmpVal_Set(Instance, init->match_val);
            tickstart = LL_GetTick();
            if (LL_WAIT_FOREVER == timeout) {
                while (!__LL_LPTMR_IsCmpUpdDone(Instance));
            } else {
                while (!__LL_LPTMR_IsCmpUpdDone(Instance)) {
                    if (LL_GetTick() - tickstart > timeout) {
                        return LL_TIMEOUT;
                    }
                }
            }

            LL_FUNC_ALTER(init->OC_en,
                        __LL_LPTMR_Cmp_En(Instance),
                        __LL_LPTMR_Cmp_Dis(Instance));

            return LL_OK;        
        } else {
            return LL_INVALID;
        }
    }

    //Output Compare Init
    switch (ch) {
        case TMR_CAP_CMP_CH_0:
            TMR_OUTPUT_CMP_CHx_CFG(Instance, 0, init);
            break;

        case TMR_CAP_CMP_CH_1:
            TMR_OUTPUT_CMP_CHx_CFG(Instance, 1, init);
            break;

        case TMR_CAP_CMP_CH_2:
            TMR_OUTPUT_CMP_CHx_CFG(Instance, 2, init);
            break;

        case TMR_CAP_CMP_CH_3:
            TMR_OUTPUT_CMP_CHx_CFG(Instance, 3, init);
            break;

        default:
            LOG_E("Invalid Compare Channel-[%d]!\n", ch);
            return LL_INVALID;
    }

    //Compare Trigger Output Width Config
    __LL_TMR_CapCmpTrigWidth_Set(Instance, init->trgcc_width);

    return LL_OK;
}

/**
  * @brief  LPTMR Output Compare Function Init
  * @note   Only LPTMR support Low Power Function
  * @param  Instance Specifies TMR peripheral
  * @param  ch TMR_CapCmpChETypeDef type Compare Channel
  * @param  init TMR Output Compare init pointer
  * @param  timeout Compare value updata timeout (Recommended: at least 2 ticks)
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_LowPwrOutputCmp_Init(TMR_TypeDef *Instance, 
        TMR_CapCmpChETypeDef ch, TMR_OutputCmpInitTypeDef *init, uint32_t timeout)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_LPTMR_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    if (TMR_CAP_CMP_CH_0 == ch) {
        //Output Compare Init
        LL_FUNC_ALTER(init->auto_preload_en,
                      __LL_LPTMR_CmpAutoPreload_En(Instance),
                      __LL_LPTMR_CmpAutoPreload_Dis(Instance));
        __LL_LPTMR_CmpPol_Set(Instance, init->OC_pol);

        __LL_LPTMR_CmpVal_Set(Instance, init->match_val);
        tickstart = LL_GetTick();
        if (LL_WAIT_FOREVER == timeout) {
            while (!__LL_LPTMR_IsCmpUpdDone(Instance));
        } else {
            while (!__LL_LPTMR_IsCmpUpdDone(Instance)) {
                if (LL_GetTick() - tickstart > timeout) {
                    return LL_TIMEOUT;
                }
            }
        }

        LL_FUNC_ALTER(init->OC_en,
                      __LL_LPTMR_Cmp_En(Instance),
                      __LL_LPTMR_Cmp_Dis(Instance));

        return LL_OK;        
    } else {
        return LL_INVALID;
    }


}


/**
  * @brief  TMR Slave Function Init
  * @note   BSTMR don't support Slave Function
  * @param  Instance Specifies TMR peripheral
  * @param  init TMR Slave init pointer
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_Slv_Init(TMR_TypeDef *Instance, TMR_SlvInitTypeDef *init)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));
    assert_param(!IS_BSTMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_TMR_ALL_INSTANCE(Instance) || IS_BSTMR_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //TMR Slave Config
    __LL_TMR_Trigger_Set(Instance, init->trig);
    __LL_TMR_ETRMode_Set(Instance, init->etr_mode);
    __LL_TMR_ETREdgeMode_Set(Instance, init->etr_edge_mode);
    __LL_TMR_ETRInputSrc_Set(Instance, init->etr_input_src);
    __LL_TMR_SlaveMode_Set(Instance, init->slv_mode);
    __LL_TMR_ETRFilter_Set(Instance, init->etr_filter);
    LL_FUNC_ALTER(init->fast_sync_en, __LL_TMR_MstSlvFastSync_En(Instance), __LL_TMR_MstSlvFastSync_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  LPTMR Slave Function Init
  * @note   Only LPTMR support Low Power Function
  * @param  Instance Specifies TMR peripheral
  * @param  init TMR Slave init pointer
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_LowPwrSlv_Init(TMR_TypeDef *Instance, TMR_SlvInitTypeDef *init)
{
    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_LPTMR_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //TMR Slave Config
    __LL_LPTMR_Trigger_Set(Instance, init->trig);
    __LL_LPTMR_ETRMode_Set(Instance, init->etr_mode);
    __LL_LPTMR_ETREdgeMode_Set(Instance, init->etr_edge_mode);
    __LL_LPTMR_SlaveMode_Set(Instance, init->slv_mode);
    __LL_LPTMR_ETRFilter_Set(Instance, init->etr_filter);

    return LL_OK;
}

/**
  * @brief  TMR Break/DeadZone Function Init
  * @note   Only GPTMRX and ADTMR support Break/DeadZone Function
  * @param  Instance Specifies TMR peripheral
  * @param  init TMR Break/DeadZone init pointer
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_BrkDz_Init(TMR_TypeDef *Instance, TMR_BrkDzInitTypeDef *init)
{
    //Assert param
    assert_param(IS_GPTMRX_ALL_INSTANCE(Instance) || IS_ADTMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!(IS_GPTMRX_ALL_INSTANCE(Instance) || IS_ADTMR_ALL_INSTANCE(Instance)) || init == NULL) {
        return LL_INVALID;
    }

    //TMR Break/DeadZone Config
    __LL_TMR_Brk0Pol_Set(Instance, init->brk0_pol);
    __LL_TMR_Brk0Fil_Set(Instance, init->brk0_filter);
    __LL_TMR_Brk1Pol_Set(Instance, init->brk1_pol);
    __LL_TMR_Brk1Fil_Set(Instance, init->brk1_filter);
    __LL_TMR_Brk0_InputEn_Set(Instance, init->brk0_input_src);
    __LL_TMR_Brk1_InputEn_Set(Instance, init->brk1_input_src);
    __LL_TMR_Brk0_InputPol_Set(Instance, init->brk0_input_pol);
    __LL_TMR_Brk1_InputPol_Set(Instance, init->brk1_input_pol);
    __LL_TMR_DeadTime_Set(Instance, init->dead_time);
    __LL_TMR_RunModeOffSta(Instance, init->run_off_sta);
    __LL_TMR_IdleModeOffSta(Instance, init->idle_off_sta);
    LL_FUNC_ALTER(init->brk0_enable, __LL_TMR_Brk0_En(Instance), __LL_TMR_Brk0_Dis(Instance));
    LL_FUNC_ALTER(init->brk1_enable, __LL_TMR_Brk1_En(Instance), __LL_TMR_Brk1_Dis(Instance));
    LL_FUNC_ALTER(init->auto_output_en, __LL_TMR_AutoOutput_En(Instance), __LL_TMR_AutoOutput_Dis(Instance));
    LL_FUNC_ALTER(init->main_output_en, __LL_TMR_MainOutput_En(Instance), __LL_TMR_MainOutput_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  TMR Low Power Function Init
  * @note   Only LPTMR support Low Power Function
  * @param  Instance Specifies TMR peripheral
  * @param  init TMR Low Power init pointer
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef TMR_LowPwr_Init(TMR_TypeDef *Instance, TMR_LowPwrInitTypeDef *init)
{
    //Assert param
    assert_param(IS_LPTMR_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if ((!IS_LPTMR_ALL_INSTANCE(Instance)) || (init == NULL)) {
        return LL_INVALID;
    }

    //LPTMR Config
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        switch (init->lp_clk_src) {
            case TMR_LP_CLK_SRC_APB0CLK:
                LL_RCU_LPTMR_ClkCfg(RCU_CLK_SRC_EX_APB0CLK);
                break;

            case TMR_LP_CLK_SRC_HSI:
                LL_RCU_LPTMR_ClkCfg(RCU_CLK_SRC_EX_HSI);
                break;

            case TMR_LP_CLK_SRC_HSE:
                LL_RCU_LPTMR_ClkCfg(RCU_CLK_SRC_EX_HSE);
                break;

            case TMR_LP_CLK_SRC_LSI:
                LL_RCU_LPTMR_ClkCfg(RCU_CLK_SRC_EX_LSI);
                break;

            default:
                return LL_INVALID;
        }
    }    

    return LL_OK;
}

/**
  * @}
  */


#endif /* LL_TMR_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

