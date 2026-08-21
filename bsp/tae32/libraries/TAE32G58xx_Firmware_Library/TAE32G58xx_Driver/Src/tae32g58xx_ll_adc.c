/**
  ******************************************************************************
  * @file    tae32g58xx_ll_adc.c
  * @author  MCD Application Team
  * @brief   ADC LL module driver
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
#include "stdlib.h"


#define DBG_TAG             "ADC LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup ADC_LL ADC LL
  * @brief    ADC LL Module Driver
  * @{
  */

#ifdef LL_ADC_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Constants ADC LL Private Constants
  * @brief    ADC LL Private Constants
  * @{
  */

/**
  * @brief ADC Defaul Timeout definition in ms Unit
  */
#define ADC_DEFAULT_TIMEOUT         (100)

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Macros ADC LL Private Macros
  * @brief    ADC LL Private Macros
  * @{
  */

/**
  * @brief  ADC Sample Interrupt Callback Function Macro Definition
  * @param  x ADC Channel Number Range [0, ADC_CH_NUMS - 1]
  * @return None
  */
#define ADC_SAMP_CHx_CONV_DONE_CALLBACK(x)                                                  \
/**                                                                          */             \
/** @brief  ADC Sample Channel x Conversion Done Interrupt Callback Function */             \
/** @param  Instance Specifies ADC peripheral                                */             \
/** @return None                                                             */             \
/**/                                                                                        \
__WEAK void LL_ADC_Samp_Ch##x##ConvDoneCallback(ADC_TypeDef *Instance)                      \
{                                                                                           \
    /* Prevent unused argument(s) compilation warning */                                    \
    LL_UNUSED(Instance);                                                                    \
                                                                                            \
    /* NOTE: This function should not be modified, when the callback is needed,         */  \
    /*       the LL_ADC_Samp_ChxConvDoneCallback could be implemented in the user file  */  \
    /**/                                                                                    \
}

/**
  * @brief  ADC DMA Half Complete Interrupt Callback Function Macro Definition
  * @param  x ADC Channel Number Range [0, ADC_CH_NUMS - 1]
  * @return None
  */
#define ADC_DMA_CHx_HALF_CPLT_CALLBACK(x)                                                   \
/**                                                             */                          \
/** @brief  ADC DMA Half Complete Interrupt Callback Function   */                          \
/** @param  Instance Specifies ADC peripheral                   */                          \
/** @return None                                                */                          \
/**/                                                                                        \
__WEAK void LL_ADC_DMA_Ch##x##HalfCpltCallback(ADC_TypeDef *Instance)                       \
{                                                                                           \
    /* Prevent unused argument(s) compilation warning */                                    \
    LL_UNUSED(Instance);                                                                    \
                                                                                            \
    /* NOTE: This function should not be modified, when the callback is needed,         */  \
    /*       the LL_ADC_DMA_ChxHalfCpltCallback could be implemented in the user file   */  \
    /**/                                                                                    \
}

/**
  * @brief  ADC DMA Complete Interrupt Callback Function Macro Definition
  * @param  x ADC Channel Number Range [0, ADC_CH_NUMS - 1]
  * @return None
  */
#define ADC_DMA_CHx_CPLT_CALLBACK(x)                                                        \
/**                                                         */                              \
/** @brief  ADC DMA Complete Interrupt Callback Function    */                              \
/** @param  Instance Specifies ADC peripheral               */                              \
/** @return None                                            */                              \
/**/                                                                                        \
__WEAK void LL_ADC_DMA_Ch##x##CpltCallback(ADC_TypeDef *Instance)                           \
{                                                                                           \
    /* Prevent unused argument(s) compilation warning */                                    \
    LL_UNUSED(Instance);                                                                    \
                                                                                            \
    /* NOTE: This function should not be modified, when the callback is needed,     */      \
    /*       the LL_ADC_DMA_ChxCpltCallback could be implemented in the user file   */      \
    /**/                                                                                    \
}

/**
  * @}
  */


/* Private Types -------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Types ADC LL Private Types
  * @brief    ADC LL Private Types
  * @{
  */

/**
  * @brief ADC IRQ callback function type definition
  */
typedef void (*ADC_LLIRQCallback)(ADC_TypeDef *Instance);

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Variables ADC LL Private Variables
  * @brief    ADC LL Private Variables
  * @{
  */

/**
  * @brief ADC Sample Channel x Conversion Done Interrupt Callback Function Array
  */
static const ADC_LLIRQCallback ADC_Samp_ChxConvDoneCallback[ADC_CH_NUMS] = {
    LL_ADC_Samp_Ch0ConvDoneCallback,
    LL_ADC_Samp_Ch1ConvDoneCallback,
    LL_ADC_Samp_Ch2ConvDoneCallback,
    LL_ADC_Samp_Ch3ConvDoneCallback,
    LL_ADC_Samp_Ch4ConvDoneCallback,
    LL_ADC_Samp_Ch5ConvDoneCallback,
    LL_ADC_Samp_Ch6ConvDoneCallback,
    LL_ADC_Samp_Ch7ConvDoneCallback,
    LL_ADC_Samp_Ch8ConvDoneCallback,
    LL_ADC_Samp_Ch9ConvDoneCallback,
    LL_ADC_Samp_Ch10ConvDoneCallback,
    LL_ADC_Samp_Ch11ConvDoneCallback,
    LL_ADC_Samp_Ch12ConvDoneCallback,
    LL_ADC_Samp_Ch13ConvDoneCallback,
    LL_ADC_Samp_Ch14ConvDoneCallback,
    LL_ADC_Samp_Ch15ConvDoneCallback,
    LL_ADC_Samp_Ch16ConvDoneCallback,
    LL_ADC_Samp_Ch17ConvDoneCallback,
    LL_ADC_Samp_Ch18ConvDoneCallback,
    LL_ADC_Samp_Ch19ConvDoneCallback,
};

/**
  * @brief ADC DMA Channel x Half Complete Interrupt Callback Function Array
  */
static const ADC_LLIRQCallback ADC_DMA_ChxHalfCpltCallback[ADC_CH_NUMS] = {
    LL_ADC_DMA_Ch0HalfCpltCallback,
    LL_ADC_DMA_Ch1HalfCpltCallback,
    LL_ADC_DMA_Ch2HalfCpltCallback,
    LL_ADC_DMA_Ch3HalfCpltCallback,
    LL_ADC_DMA_Ch4HalfCpltCallback,
    LL_ADC_DMA_Ch5HalfCpltCallback,
    LL_ADC_DMA_Ch6HalfCpltCallback,
    LL_ADC_DMA_Ch7HalfCpltCallback,
    LL_ADC_DMA_Ch8HalfCpltCallback,
    LL_ADC_DMA_Ch9HalfCpltCallback,
    LL_ADC_DMA_Ch10HalfCpltCallback,
    LL_ADC_DMA_Ch11HalfCpltCallback,
    LL_ADC_DMA_Ch12HalfCpltCallback,
    LL_ADC_DMA_Ch13HalfCpltCallback,
    LL_ADC_DMA_Ch14HalfCpltCallback,
    LL_ADC_DMA_Ch15HalfCpltCallback,
    LL_ADC_DMA_Ch16HalfCpltCallback,
    LL_ADC_DMA_Ch17HalfCpltCallback,
    LL_ADC_DMA_Ch18HalfCpltCallback,
    LL_ADC_DMA_Ch19HalfCpltCallback,
};

/**
  * @brief ADC DMA Channel x Complete Interrupt Callback Function Array
  */
static const ADC_LLIRQCallback ADC_DMA_ChxCpltCallback[ADC_CH_NUMS] = {
    LL_ADC_DMA_Ch0CpltCallback,
    LL_ADC_DMA_Ch1CpltCallback,
    LL_ADC_DMA_Ch2CpltCallback,
    LL_ADC_DMA_Ch3CpltCallback,
    LL_ADC_DMA_Ch4CpltCallback,
    LL_ADC_DMA_Ch5CpltCallback,
    LL_ADC_DMA_Ch6CpltCallback,
    LL_ADC_DMA_Ch7CpltCallback,
    LL_ADC_DMA_Ch8CpltCallback,
    LL_ADC_DMA_Ch9CpltCallback,
    LL_ADC_DMA_Ch10CpltCallback,
    LL_ADC_DMA_Ch11CpltCallback,
    LL_ADC_DMA_Ch12CpltCallback,
    LL_ADC_DMA_Ch13CpltCallback,
    LL_ADC_DMA_Ch14CpltCallback,
    LL_ADC_DMA_Ch15CpltCallback,
    LL_ADC_DMA_Ch16CpltCallback,
    LL_ADC_DMA_Ch17CpltCallback,
    LL_ADC_DMA_Ch18CpltCallback,
    LL_ADC_DMA_Ch19CpltCallback,
};


/**
  * @brief Default ADC LL Config
  */
static const ADC_LLCfgTypeDef adc_ll_cfg_def = {
    .bias_cur       = ADC_BIAS_CUR_10uA,
    .sys_dma_req_en = false,
};

/**
  * @brief Init ADC self calibration 
  */
ADC_CALI_ALL_TYPE SelfCali_Param = {
    .ADC0_SIG.offset     = 0,
    .ADC0_SIG.gain     = 0x2000,
    .ADC0_DIF.offset     = 0,
    .ADC0_DIF.gain     = 0x2000,
    .ADC1_SIG.offset     = 0,
    .ADC1_SIG.gain     = 0x2000,
    .ADC1_DIF.offset     = 0,
    .ADC1_DIF.gain     = 0x2000,
    .ADC2_SIG.offset     = 0,
    .ADC2_SIG.gain     = 0x2000,
    .ADC2_DIF.offset     = 0,
    .ADC2_DIF.gain     = 0x2000,
    .ADC3_SIG.offset     = 0,
    .ADC3_SIG.gain     = 0x2000,
    .ADC3_DIF.offset     = 0,
    .ADC3_DIF.gain     = 0x2000,
};
/**
  * @brief Default ADC Cali paramter value
  */

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions ADC LL Exported Functions
  * @brief    ADC LL Exported Functions
  * @{
  */

/** @defgroup ADC_LL_Exported_Functions_Group1 ADC Init and DeInit Functions
  * @brief    ADC Init and DeInit Functions
  * @{
  */

/**
  * @brief  ADC LL Init
  * @param  Instance Specifies ADC peripheral
  * @param  init ADC Init pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_ADC_Init(ADC_TypeDef *Instance, ADC_InitTypeDef *init)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    ADC_LLCfgTypeDef *ll_cfg;

    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_ADC_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance) || __LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC can't Init while it's Running!\n");
        return LL_BUSY;
    }

    //LL config pointer config
    LL_FUNC_ALTER(init->ll_cfg == NULL, ll_cfg = (ADC_LLCfgTypeDef *)&adc_ll_cfg_def, ll_cfg = init->ll_cfg);

    /* Init the low level hardware eg. Clock, NVIC */
    LL_ADC_MspInit(Instance);

    //ADC Analog Config
    __LL_ADC_Channel_En(Instance);
    __LL_ADC_Ref_En(Instance);
    __LL_ADC_Bias_En(Instance);

    //ADC Init
    __LL_ADC_DualSampPhaseDly_Set(Instance, init->dual_phase_dly);
    __LL_ADC_DualMode_Set(Instance, init->dual_mode);
    __LL_ADC_OverRunMode_Set(Instance, init->overrun_mode);

    //ADC LL Config
    __LL_ADC_BiasCur_Set(Instance, ll_cfg->bias_cur);

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_ADC))) {
        LL_FUNC_ALTER(ll_cfg->sys_dma_req_en, __LL_ADC_SysDmaReq_En(Instance), __LL_ADC_SysDmaReq_Dis(Instance));
    }

    //Oversample Config
    if ((ret = LL_ADC_OverSamp_Cfg(Instance, &init->over_samp_cfg)) != LL_OK) {
        return ret;
    }

    //ADC Enable
    __LL_ADC_En(Instance);

    //Wait for ADC to be Ready
    tickstart = LL_GetTick();

    while (!__LL_ADC_IsReadyIntPnd(Instance)) {
        if ((LL_GetTick() - tickstart) > ADC_DEFAULT_TIMEOUT) {
            return LL_TIMEOUT;
        }
    }

    //Clear ADC Ready Interrupt Pending
    __LL_ADC_ReadyIntPnd_Clr(Instance);

    return LL_OK;
}

/**
  * @brief  ADC LL DeInit
  * @param  Instance Specifies ADC peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_ADC_DeInit(ADC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));

    if (!IS_ADC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //ADC Disable
    __LL_ADC_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_ADC_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the ADC MSP
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_MspInit(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the ADC MSP
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_MspDeInit(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup ADC_LL_Exported_Functions_Group2 ADC Submodule Config Functions
  * @brief    ADC Submodule Config Functions
  * @{
  */

/**
  * @brief  ADC LL Oversample Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC Oversample Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_OverSamp_Cfg(ADC_TypeDef *Instance, ADC_OverSamp_CfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance) || __LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC Oversample can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC Oversample Config
    __LL_ADC_OverSampRightShift_Set(Instance, cfg->shift);
    __LL_ADC_OverSampRatio_Set(Instance, cfg->ratio);
    __LL_ADC_NormOverSampMode_Set(Instance, cfg->norm_mode);
    LL_FUNC_ALTER(cfg->reg_en, __LL_ADC_REG_OverSamp_En(Instance), __LL_ADC_REG_OverSamp_Dis(Instance));
    LL_FUNC_ALTER(cfg->inj_en, __LL_ADC_INJ_OverSamp_En(Instance), __LL_ADC_INJ_OverSamp_Dis(Instance));
    LL_FUNC_ALTER(cfg->trig_en, __LL_ADC_TrigOverSample_En(Instance), __LL_ADC_TrigOverSamp_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  ADC LL Regular Common Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC Regular Common Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_REG_ComCfg(ADC_TypeDef *Instance, ADC_REG_ComCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance)) {
        LOG_E("ADC Regular Common can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC Regular Common Config
    __LL_ADC_REG_ConvMode_Set(Instance, cfg->conv_mode);
    __LL_ADC_REG_DisContConvNum_Set(Instance, cfg->dis_cont_nums);
    LL_FUNC_ALTER(cfg->dis_cont_en, __LL_ADC_REG_DisContConv_En(Instance), __LL_ADC_REG_DisContConv_Dis(Instance));

    __LL_ADC_REG_SeqLen_Set(Instance, cfg->seq_len);
    __LL_ADC_REG_SeqTrigPol_Set(Instance, cfg->trig_pol);
    __LL_ADC_REG_SeqTrigEvt_Set(Instance, cfg->trig_evt);

    return LL_OK;
}

/**
  * @brief  ADC LL Regular Channel Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC Regular Channel Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_REG_ChCfg(ADC_TypeDef *Instance, ADC_REG_ChCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(cfg->ch < ADC_CH_NUMS);
    assert_param(cfg->seq_num < ADC_REG_SEQ_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL || cfg->ch >= ADC_CH_NUMS || cfg->seq_num >= ADC_REG_SEQ_NUMS) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance)) {
        LOG_E("ADC Regular Channel can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC Regular Channel Config
    __LL_ADC_REG_SeqCh_Set(Instance, cfg->seq_num, cfg->ch);
    __LL_ADC_ChConvMode_Set(Instance, cfg->ch, cfg->input_mode);
    __LL_ADC_ChSampTime_Set(Instance, cfg->ch, cfg->samp_time);
    LL_FUNC_ALTER(cfg->done_int_en, __LL_ADC_ChConvDone_INT_En(Instance, cfg->ch), __LL_ADC_ChConvDone_INT_Dis(Instance, cfg->ch));

    return LL_OK;
}

/**
  * @brief  ADC LL Injected Common Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC Injected Common Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_INJ_ComCfg(ADC_TypeDef *Instance, ADC_INJ_ComCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC Injected Common can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC Injected Common Config
    __LL_ADC_INJ_SeqLen_Set(Instance, cfg->seq_len);
    __LL_ADC_INJ_SeqTrigPol_Set(Instance, cfg->trig_pol);
    __LL_ADC_INJ_SeqTrigEvt_Set(Instance, cfg->trig_evt);
    LL_FUNC_ALTER(cfg->auto_conv_en, __LL_ADC_INJ_AutoConv_En(Instance), __LL_ADC_INJ_AutoConv_Dis(Instance));
    LL_FUNC_ALTER(cfg->dis_cont_en, __LL_ADC_INJ_DisContConv_En(Instance), __LL_ADC_INJ_DisContConv_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  ADC LL Injected Channel Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC Injected Channel Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_INJ_ChCfg(ADC_TypeDef *Instance, ADC_INJ_ChCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(cfg->ch < ADC_CH_NUMS);
    assert_param(cfg->seq_num < ADC_INJ_SEQ_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL || cfg->ch >= ADC_CH_NUMS || cfg->seq_num >= ADC_INJ_SEQ_NUMS) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC Injected Channel can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC Injected Channel Config
    __LL_ADC_INJ_SeqCh_Set(Instance, cfg->seq_num, cfg->ch);
    __LL_ADC_ChConvMode_Set(Instance, cfg->ch, cfg->input_mode);
    __LL_ADC_ChSampTime_Set(Instance, cfg->ch, cfg->samp_time);

    return LL_OK;
}

/**
  * @brief  ADC LL AWDG Common Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC AWDG Common Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_AWDG_ComCfg(ADC_TypeDef *Instance, ADC_AWDG_ComCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(cfg->awdg_num < ADC_AWDG_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL || cfg->awdg_num >= ADC_AWDG_NUMS) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance) || __LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC AWDG Common can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC AWDG Common Config
    __LL_ADC_AWDG_Filter_Set(Instance, cfg->awdg_num, cfg->filter);
    __LL_ADC_AWDG_ThresHigh_Set(Instance, cfg->awdg_num, cfg->thres_high);
    __LL_ADC_AWDG_ThresLow_Set(Instance, cfg->awdg_num, cfg->thres_low);
    LL_FUNC_ALTER(cfg->reg_mon_en, __LL_ADC_AWDG_MonitorREG_En(Instance, cfg->awdg_num),
                  __LL_ADC_AWDG_MonitorREG_Dis(Instance, cfg->awdg_num));
    LL_FUNC_ALTER(cfg->inj_mon_en, __LL_ADC_AWDG_MonitorINJ_En(Instance, cfg->awdg_num),
                  __LL_ADC_AWDG_MonitorINJ_Dis(Instance, cfg->awdg_num));

    return LL_OK;
}

/**
  * @brief  ADC LL AWDG Channel Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC AWDG Channel Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_AWDG_ChCfg(ADC_TypeDef *Instance, ADC_AWDG_ChCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(cfg->ch < ADC_CH_NUMS);
    assert_param(cfg->awdg_num < ADC_AWDG_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL || cfg->ch >= ADC_CH_NUMS || cfg->awdg_num >= ADC_AWDG_NUMS) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance) || __LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC AWDG Channel can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC AWDG Channel Config
    LL_FUNC_ALTER(cfg->ch_mon_en, __LL_ADC_AWDG_ChMonitor_En(Instance, cfg->awdg_num, cfg->ch),
                  __LL_ADC_AWDG_ChMonitor_Dis(Instance, cfg->awdg_num, cfg->ch));

    return LL_OK;
}

/**
  * @brief  ADC LL DMA Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC DMA Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_DMA_Cfg(ADC_TypeDef *Instance, ADC_DMA_CfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(cfg->ch < ADC_CH_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL || cfg->ch >= ADC_CH_NUMS) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance) || __LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC DMA can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC DMA Config
    __LL_ADC_ChDMATransAddr_Set(Instance, cfg->ch, cfg->addr);
    __LL_ADC_ChDMATransLen_Set(Instance, cfg->ch, cfg->len);
    __LL_ADC_ChDMACircMode_Set(Instance, cfg->ch, cfg->circ_en);
    __LL_ADC_ChDMAFixAddr_Set(Instance, cfg->ch, cfg->fix_addr_en);
    LL_FUNC_ALTER(cfg->half_int_en, __LL_ADC_ChDMAHalfCplt_INT_En(Instance, cfg->ch), __LL_ADC_ChDMAHalfCplt_INT_Dis(Instance, cfg->ch));
    LL_FUNC_ALTER(cfg->cplt_int_en, __LL_ADC_ChDMACplt_INT_En(Instance, cfg->ch), __LL_ADC_ChDMACplt_INT_Dis(Instance, cfg->ch));

    //DMA Start
    __LL_ADC_ChDMA_Start(Instance, cfg->ch);

    return LL_OK;
}

/**
  * @brief  ADC LL Calibration Config
  * @param  Instance Specifies ADC peripheral
  * @param  cfg ADC Calibration Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_ADC_Cal_Cfg(ADC_TypeDef *Instance, ADC_Cal_CfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(cfg->ch < ADC_CH_NUMS);
    assert_param(cfg->coef_grp < ADC_CAL_COEF_GRP_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL || cfg->ch >= ADC_CH_NUMS || cfg->coef_grp >= ADC_CAL_COEF_GRP_NUMS) {
        return LL_INVALID;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance) || __LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC Calibration can't Config while it's Running!\n");
        return LL_BUSY;
    }

    //ADC Calibration Config
    __LL_ADC_ChCalCoefGrp_Set(Instance, cfg->ch, cfg->coef_grp);
    __LL_ADC_ChSat_Set(Instance, cfg->ch, cfg->sat_dis);
    __LL_ADC_OffsetCoef_Set(Instance, cfg->coef_grp, cfg->offset);
    __LL_ADC_GainCoef_Set(Instance, cfg->coef_grp, cfg->gain);

    return LL_OK;
}

/**
  * @brief  ADC LL Single software self Calibration Config
  * @param  Instance Specifies ADC peripheral
  * @return LL Status
  * @note  
  */
LL_StatusETypeDef LL_ADC_Single_Calibration(ADC_TypeDef *Instance)
{
    //Define variables to store user register configuration values
    volatile uint32_t temp_vref_reg = 0;
    volatile uint32_t temp_reg[4] = {0};
    volatile int16_t user_cal_buf[1024] = {0};
    volatile uint32_t temp = 0;
    
    int32_t int_vref_value = 0;
    int32_t int_vss_value = 0;
    int32_t recheck_value = 0;
    
    //Stop ADC Conversion
    __LL_ADC_Dis(Instance);
    while(__LL_ADC_IsRunning(Instance));

    //Store register value
    temp_vref_reg = READ_REG(SYSCTRL->ATCR);
    temp_reg[0] = READ_REG(Instance->CFGR0);
    temp_reg[1] = READ_REG(Instance->CFGR1);
    temp_reg[2] = READ_REG(Instance->CCR);
    
    //Config Vref Source
    __LL_SYSCTRL_SpRegWrite_Unlock(SYSCTRL);
    __LL_SYSCTRL_VREFBUFOutputVol_Set(SYSCTRL, SYSCTRL_VREFBUF_VOL_2V9);
    __LL_SYSCTRL_VREFBUF_En(SYSCTRL);
    //ADBUF Source select VR1P1
    __LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
    __LL_SYSCTRL_ADCBuf_En(SYSCTRL);
    __LL_SYSCTRL_ADCBufSrc_Sel(SYSCTRL, 3);
    //Wait ADBUF Enable
    for(uint16_t k=500; k>0; k++);

    //ADC Config
    //LR Software Trigger
    __LL_ADC_REG_SeqLen_Set(Instance, 0);
    __LL_ADC_REG_SeqTrigPol_Set(Instance, 0);
    __LL_ADC_REG_SeqTrigEvt_Set(Instance, 0);
    
    //Single
    WRITE_REG(Instance->SIGSEL, 0);
    
    //SAT0 \ SAT17 \ SAT18 
    __LL_ADC_ChSat_Set(Instance, ADC_CH_0, 1);
    __LL_ADC_ChSat_Set(Instance, ADC_CH_17, 1);
    __LL_ADC_ChSat_Set(Instance, ADC_CH_18, 1);
    
    //Sampclk SAMP0\SAMP17\SAMP18 = 1
    __LL_ADC_ChSampTime_Set(Instance, ADC_CH_0, ADC_SAMP_TIME_6_CYCLES);
    __LL_ADC_ChSampTime_Set(Instance, ADC_CH_17, ADC_SAMP_TIME_6_CYCLES);
    __LL_ADC_ChSampTime_Set(Instance, ADC_CH_18, ADC_SAMP_TIME_6_CYCLES);
    
    //SQR  Channel 0 VSS SQR0 = 0;
    __LL_ADC_REG_SeqCh_Set(Instance, ADC_REG_SEQ_NUM_1, ADC_CH_0);
    
    //Turn off saturation function
    SET_BIT(Instance->CR, BIT(31));
    if(Instance == ADC0) {
        //ADC0 0x40038000
        temp = *(__IO uint32_t *)(0x400380F4);
        temp |= BIT(15);
        *(__IO uint32_t *)(0x400380F4) = temp;
    } else if (Instance == ADC1) {
        //ADC1 
        temp = *(__IO uint32_t *)(0x400384F4);
        temp |= BIT(15);
        *(__IO uint32_t *)(0x400384F4) = temp;
    } else if (Instance == ADC2) {
        //ADC2 
        temp = *(__IO uint32_t *)(0x400388F4);
        temp |= BIT(15);
        *(__IO uint32_t *)(0x400388F4) = temp;
    }else if (Instance == ADC3) {
        //ADC3 
        temp = *(__IO uint32_t *)(0x40038CF4);
        temp |= BIT(15);
        *(__IO uint32_t *)(0x40038CF4) = temp;
    }
    CLEAR_BIT(Instance->CR, BIT(31));
    
    //cal Turn off saturation function
    __LL_ADC_OffsetCoef_Set(Instance, ADC_CAL_COEF_GRP_0, 0);
    __LL_ADC_GainCoef_Set(Instance, ADC_CAL_COEF_GRP_0, 0x2000);

    //ADEN
    __LL_ADC_En(Instance);
    while(!(__LL_ADC_IsReadyIntPnd(Instance)));

    __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);
    //Read VSS Data
    for(uint16_t k=0; k<1024; k++) {
        __LL_ADC_REG_Conv_Start(Instance);
        while(!(__LL_ADC_REG_IsConvEndIntPnd(Instance)));
        __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);
        user_cal_buf[k] = __LL_ADC_REG_SeqDat_Read(Instance);
    }
    
    for(uint16_t i=0; i<1024; i++) {
        int_vss_value += user_cal_buf[i];
    }
    int_vss_value = int_vss_value/1024;
    
    //SQR  Channel 18 Vref SQR0 = 18;
    __LL_ADC_REG_SeqCh_Set(Instance, ADC_REG_SEQ_NUM_1, ADC_CH_18);

    //Read Vref Data
    for(uint16_t k=0; k<1024; k++) {
        __LL_ADC_REG_Conv_Start(Instance);
        while(!(__LL_ADC_REG_IsConvEndIntPnd(Instance)));
        __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);
        user_cal_buf[k] = __LL_ADC_REG_SeqDat_Read(Instance);
    }
    for(uint16_t i=0; i<1024; i++) {
        int_vref_value += user_cal_buf[i];
    }
    int_vref_value = int_vref_value/1024;
    
    if(Instance == ADC0) {
        //Calibration
        SelfCali_Param.ADC0_SIG.gain = (uint32_t)(8191 << 13) / (int_vref_value - int_vss_value);
        SelfCali_Param.ADC0_SIG.offset = -((SelfCali_Param.ADC0_SIG.gain * int_vss_value) >> 13);
        
        Instance->OFR0 = SelfCali_Param.ADC0_SIG.offset;
        Instance->GCR0 = SelfCali_Param.ADC0_SIG.gain;
    } else if(Instance == ADC1) {
        //Calibration
        SelfCali_Param.ADC1_SIG.gain = (uint32_t)(8191 << 13) / (int_vref_value - int_vss_value);
        SelfCali_Param.ADC1_SIG.offset = -((SelfCali_Param.ADC1_SIG.gain * int_vss_value) >> 13);
        
        Instance->OFR0 = SelfCali_Param.ADC1_SIG.offset;
        Instance->GCR0 = SelfCali_Param.ADC1_SIG.gain;
    } else if(Instance == ADC2) {
        //Calibration
        SelfCali_Param.ADC2_SIG.gain = (uint32_t)(8191 << 13) / (int_vref_value - int_vss_value);
        SelfCali_Param.ADC2_SIG.offset = -((SelfCali_Param.ADC2_SIG.gain * int_vss_value) >> 13);
        
        Instance->OFR0 = SelfCali_Param.ADC2_SIG.offset;
        Instance->GCR0 = SelfCali_Param.ADC2_SIG.gain;
    } else if(Instance == ADC3) {
        //Calibration
        SelfCali_Param.ADC3_SIG.gain = (uint32_t)(8191 << 13) / (int_vref_value - int_vss_value);
        SelfCali_Param.ADC3_SIG.offset = -((SelfCali_Param.ADC3_SIG.gain * int_vss_value) >> 13);
        
        Instance->OFR0 = SelfCali_Param.ADC3_SIG.offset;
        Instance->GCR0 = SelfCali_Param.ADC3_SIG.gain;
    }
    
    //SQR  Channel 17 VR1P1 SQR0 = 17;
    __LL_ADC_REG_SeqCh_Set(Instance, ADC_REG_SEQ_NUM_1, ADC_CH_17);
    //Wait ADBUF Enable
    for(uint16_t k=100; k>0; k++);
    
    //Read Vref Data
    for(uint16_t k=0; k<1024; k++) {
        __LL_ADC_REG_Conv_Start(Instance);
        while(!(__LL_ADC_REG_IsConvEndIntPnd(Instance)));
        __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);
        user_cal_buf[k] = __LL_ADC_REG_SeqDat_Read(Instance);
    }
    for(uint16_t i=0; i<1024; i++) {
        recheck_value += user_cal_buf[i];
    }
    recheck_value = recheck_value/1024;

    //First Stop ADC Conversion
    __LL_ADC_Dis(Instance);
    while(__LL_ADC_IsRunning(Instance));
    
    //Restore configuration
    __LL_SYSCTRL_ADCBuf_Dis(SYSCTRL);
    __LL_SYSCTRL_ADCBufSrc_Sel(SYSCTRL, 0);
    MODIFY_REG(SYSCTRL->ATCR, 0xFFFFFFFF, temp_vref_reg);
    WRITE_REG(Instance->SIGSEL, 0xFFFFF);
    WRITE_REG(Instance->CFGR0, temp_reg[0]);
    WRITE_REG(Instance->CFGR1, temp_reg[1]);
    WRITE_REG(Instance->CCR, temp_reg[2]);
    __LL_ADC_REG_SeqCh_Set(Instance, ADC_REG_SEQ_NUM_1, ADC_CH_0);
    __LL_ADC_OffsetCoef_Set(Instance, ADC_CAL_COEF_GRP_0, 0);
    __LL_ADC_GainCoef_Set(Instance, ADC_CAL_COEF_GRP_0, 0x2000);
    //SAT0 \ SAT17 \ SAT18
    __LL_ADC_ChSat_Set(Instance, ADC_CH_0, 0);
    __LL_ADC_ChSat_Set(Instance, ADC_CH_17, 0);
    __LL_ADC_ChSat_Set(Instance, ADC_CH_18, 0);
    
    //Sampclk SAMP0\SAMP17\SAMP18 = 1
    __LL_ADC_ChSampTime_Set(Instance, ADC_CH_0, ADC_SAMP_TIME_2_CYCLES);
    __LL_ADC_ChSampTime_Set(Instance, ADC_CH_17, ADC_SAMP_TIME_2_CYCLES);
    __LL_ADC_ChSampTime_Set(Instance, ADC_CH_18, ADC_SAMP_TIME_2_CYCLES);
    WRITE_REG(Instance->ISR, 0xffff);
    
    //ADEN
    __LL_ADC_En(Instance);
    while(!(__LL_ADC_IsReadyIntPnd(Instance)));
    
    //Lock
    __LL_SYSCTRL_SpRegWrite_Lock(SYSCTRL);
    
    if(abs(recheck_value - 3389) > 20) {
        return LL_ERROR;
    }

    return LL_OK;
}

/**
  * @brief  ADC LL Differ software self Calibration Config
  * @param  Instance Specifies ADC peripheral
  * @return LL Status
  * @note  
  */
LL_StatusETypeDef LL_ADC_Differ_Calibration(ADC_TypeDef *Instance)
{
    volatile int bgr_value = (READ_BIT(SYSCTRL->ATCR, SYSCTRL_ATCR_BGV_Msk) >> 20) + 4095;
    //Define variables to store user register configuration values
    volatile uint32_t temp_vref_reg = 0;
    volatile uint32_t temp_reg[3] = {0};
    volatile int16_t user_cal_buf[1024] = {0};
    volatile uint32_t temp = 0;
    
    int32_t int_vref_value = 0;
    int32_t int_vss_value = 0;
    int32_t recheck_value = 0;
    
    //Stop ADC Conversion
    __LL_ADC_Dis(Instance);
    while(__LL_ADC_IsRunning(Instance));

    //Store Register
    temp_vref_reg = READ_REG(SYSCTRL->ATCR);
    temp_reg[0] = READ_REG(Instance->CFGR0);
    temp_reg[1] = READ_REG(Instance->CFGR1);
    temp_reg[2] = READ_REG(Instance->CCR);

    //Config Vref Source and clkdiv
    __LL_SYSCTRL_SpRegWrite_Unlock(SYSCTRL);
    __LL_SYSCTRL_VREFBUFOutputVol_Set(SYSCTRL, SYSCTRL_VREFBUF_VOL_2V9);
    __LL_SYSCTRL_VREFBUF_En(SYSCTRL);
    
    //Config ADBUF VBGR
    __LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
    __LL_SYSCTRL_ADCBuf_En(SYSCTRL);
    __LL_SYSCTRL_ADCBufSrc_Sel(SYSCTRL, 2);
    
    //Wait ADBUF Enable
    for(uint16_t k=500; k>0; k++);

    //ADC Config
    //LR Software Trigger
    __LL_ADC_REG_SeqLen_Set(Instance, 0);
    __LL_ADC_REG_SeqTrigPol_Set(Instance, 0);
    __LL_ADC_REG_SeqTrigEvt_Set(Instance, 0);
    
    //Differ
    WRITE_REG(Instance->SIGSEL, 0xFFFFF);
    
    //SAT0 \ SAT17 \ SAT18
    __LL_ADC_ChSat_Set(Instance, ADC_CH_17, 1);
    
    //Sampclk SAMP0\SAMP17\SAMP18 = 1
    __LL_ADC_ChSampTime_Set(Instance, ADC_CH_17, ADC_SAMP_TIME_6_CYCLES);
    
    //SQR  Channel 0 VSS SQR0 = 0;
    __LL_ADC_REG_SeqCh_Set(Instance, ADC_REG_SEQ_NUM_1, ADC_CH_17);
    
    //Turn off saturation function
    SET_BIT(Instance->CR, BIT(31));
    if(Instance == ADC0) {
        //ADC0 0x40038000
        temp = *(__IO uint32_t *)(0x400380FC);
        temp |= BIT(15);
        *(__IO uint32_t *)(0x400380FC) = temp;
    } else if (Instance == ADC1) {
        //ADC1 
        temp = *(__IO uint32_t *)(0x400384FC);
        temp |= BIT(15);
        *(__IO uint32_t *)(0x400384FC) = temp;
    } else if (Instance == ADC2) {
        //ADC2 
        temp = *(__IO uint32_t *)(0x400388FC);
        temp |= BIT(15);
        *(__IO uint32_t *)(0x400388FC) = temp;
    }else if (Instance == ADC3) {
        //ADC3 
        temp = *(__IO uint32_t *)(0x40038CFC);
        temp |= BIT(15);
        *(__IO uint32_t *)(0x40038CFC) = temp;
    }
    CLEAR_BIT(Instance->CR, BIT(31));

    
    //Config 
    __LL_ADC_OffsetCoef_Set(Instance, ADC_CAL_COEF_GRP_0, 0);
    __LL_ADC_GainCoef_Set(Instance, ADC_CAL_COEF_GRP_0, 0x2000);

    //ADEN
    __LL_ADC_En(Instance);
    while(!(__LL_ADC_IsReadyIntPnd(Instance)));
    
    __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);
    
    //Read VBGR Data
    for(uint16_t k=0; k<1024; k++) {
        __LL_ADC_REG_Conv_Start(Instance);
        while(!(__LL_ADC_REG_IsConvEndIntPnd(Instance)));
        __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);
        user_cal_buf[k] = __LL_ADC_REG_SeqDat_Read(Instance);
    }
    for(uint16_t i=0; i<1024; i++) {
        int_vss_value += user_cal_buf[i];
    }
    int_vss_value = int_vss_value/1024;
    
    //SQR Channel 17 = VR1P1 Vref SQR0 = 18;
    __LL_SYSCTRL_ADCBufSrc_Sel(SYSCTRL, 3);
    //Read Vref Data
    for(uint16_t k=0; k<1024; k++) {
        __LL_ADC_REG_Conv_Start(Instance);
        while(!(__LL_ADC_REG_IsConvEndIntPnd(Instance)));
        __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);
        user_cal_buf[k] = __LL_ADC_REG_SeqDat_Read(Instance);
    }
    for(uint16_t i=0; i<1024; i++) {
        int_vref_value += user_cal_buf[i];
    }
    int_vref_value = int_vref_value/1024;
    
    if(Instance == ADC0) {
        //Calibration
        SelfCali_Param.ADC0_DIF.gain = (uint32_t)((5790 - bgr_value) << 13) / (int_vref_value - int_vss_value);
        SelfCali_Param.ADC0_DIF.offset = (((5790 + bgr_value) - ((SelfCali_Param.ADC0_DIF.gain * (int_vref_value + int_vss_value)) >> 13)) >> 1);
        
        Instance->OFR0 = SelfCali_Param.ADC0_DIF.offset;
        Instance->GCR0 = SelfCali_Param.ADC0_DIF.gain;
    } else if(Instance == ADC1) {
        //Calibration
        SelfCali_Param.ADC1_DIF.gain = (uint32_t)((5790 - bgr_value) << 13) / (int_vref_value - int_vss_value);
        SelfCali_Param.ADC1_DIF.offset = (((5790 + bgr_value) - ((SelfCali_Param.ADC1_DIF.gain * (int_vref_value + int_vss_value)) >> 13)) >> 1);
        
        Instance->OFR0 = SelfCali_Param.ADC1_DIF.offset;
        Instance->GCR0 = SelfCali_Param.ADC1_DIF.gain;
    } else if(Instance == ADC2) {
        //Calibration
        SelfCali_Param.ADC2_DIF.gain = (uint32_t)((5790 - bgr_value) << 13) / (int_vref_value - int_vss_value);
        SelfCali_Param.ADC2_DIF.offset = (((5790 + bgr_value) - ((SelfCali_Param.ADC2_DIF.gain * (int_vref_value + int_vss_value)) >> 13)) >> 1);
        
        Instance->OFR0 = SelfCali_Param.ADC2_DIF.offset;
        Instance->GCR0 = SelfCali_Param.ADC2_DIF.gain;
    } else if(Instance == ADC3) {
        //Calibration
        SelfCali_Param.ADC3_DIF.gain = (uint32_t)((5790 - bgr_value) << 13) / (int_vref_value - int_vss_value);
        SelfCali_Param.ADC3_DIF.offset = (((5790 + bgr_value) - ((SelfCali_Param.ADC3_DIF.gain * (int_vref_value + int_vss_value)) >> 13)) >> 1);
        
        Instance->OFR0 = SelfCali_Param.ADC3_DIF.offset;
        Instance->GCR0 = SelfCali_Param.ADC3_DIF.gain;
    }
    //SQR  Channel 17 VR1P1 SQR0 = 17;
    __LL_SYSCTRL_ADCBufSrc_Sel(SYSCTRL, 3);
    for(uint16_t k=100; k>0; k++);
    
    //Read Vref Data
    for(uint16_t k=0; k<1024; k++) {
        __LL_ADC_REG_Conv_Start(Instance);
        while(!(__LL_ADC_REG_IsConvEndIntPnd(Instance)));
        __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);
        user_cal_buf[k] = __LL_ADC_REG_SeqDat_Read(Instance);
    }
    for(uint16_t i=0; i<1024; i++) {
        recheck_value += user_cal_buf[i];
    }
    recheck_value = recheck_value/1024;
    
    //Stop ADC conversion
    __LL_ADC_Dis(Instance);
    while(__LL_ADC_IsRunning(Instance));

    //Restore Config
    MODIFY_REG(SYSCTRL->ATCR, 0xFFFFFFFF, temp_vref_reg);
    WRITE_REG(Instance->CFGR0, temp_reg[0]);
    WRITE_REG(Instance->CFGR1, temp_reg[1]);
    WRITE_REG(Instance->CCR, temp_reg[2]);
    __LL_ADC_REG_SeqCh_Set(Instance, ADC_REG_SEQ_NUM_1, ADC_CH_0);
    __LL_ADC_OffsetCoef_Set(Instance, ADC_CAL_COEF_GRP_0, 0);
    __LL_ADC_GainCoef_Set(Instance, ADC_CAL_COEF_GRP_0, 0x2000);
    __LL_ADC_ChSat_Set(Instance, ADC_CH_17, 0);
    __LL_ADC_ChSampTime_Set(Instance, ADC_CH_17, ADC_SAMP_TIME_2_CYCLES);
    WRITE_REG(Instance->ISR, 0xffff);
    
    //ADEN
    __LL_ADC_En(Instance);
    while(!(__LL_ADC_IsReadyIntPnd(Instance)));
    
    //Lock
    __LL_SYSCTRL_SpRegWrite_Lock(SYSCTRL);
    
    if(abs(recheck_value - 5790) > 5) {
        return LL_ERROR;
    }

    return LL_OK;
}

/**
 * @brief ADC LL Auto Calibration Config
 * @param Instance Specifies ADC peripheral
 * @param cfg Auto Calibration Config pointer
 * @return LL Status
 */
LL_StatusETypeDef LL_ADC_AutoCal_Cfg(ADC_TypeDef *Instance, ADC_AutoCal_CfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(cfg->ch < ADC_CH_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || cfg == NULL || cfg->ch >= ADC_CH_NUMS || 
        cfg->auto_cal_ratio > ADC_OVER_SAMP_RATIO_256) {
        return LL_INVALID;
    }

    //Check whether this config is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support Auto Calibration!\n");
        return LL_FAILED;
    }

    //Check ADC is Running or not
    if (__LL_ADC_REG_IsConvRunning(Instance) || __LL_ADC_INJ_IsConvRunning(Instance)) {
        LOG_E("ADC Calibration can't Config while it's Running!\n");
        return LL_BUSY;
    }

    if (__LL_ADC_IsCalStarting(Instance)) {
        LOG_E("Auto-calibration can't Config while it's Starting!\n");
        return LL_BUSY;
    }

    //ADC Auto-calibration Config
    __LL_ADC_CalMode_Set(Instance, cfg->mode);
    __LL_ADC_AutoCalRatio_Set(Instance, cfg->auto_cal_ratio);

    return LL_OK;
}


/**
  * @}
  */


/** @defgroup ADC_LL_Exported_Functions_Interrupt ADC Interrupt Handler and Callback
  * @brief    ADC Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  ADC Normal IRQ Handler
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
void LL_ADC_Norm_IRQHandler(ADC_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));

    if (!IS_ADC_ALL_INSTANCE(Instance)) {
        return;
    }

    //ADC Normal All Interrupt Enalbe and Pending Get
    int_en = __LL_ADC_NormAllIntEn_Get(Instance);
    int_pending = __LL_ADC_NormAllIntPending_Get(Instance);


    //Sample End Interrupt Handler
    if ((int_en & ADC0_IER_EOSMPIE_Msk) && (int_pending & ADC0_ISR_EOSMP_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_SampEndIntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_SampEndCallback(Instance);
    }

    //ADC Ready Interrupt Handler
    if ((int_en & ADC0_IER_ADRDYIE_Msk) && (int_pending & ADC0_ISR_ADRDY_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_ReadyIntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_ReadyCallback(Instance);
    }

    //AWDG2 Interrupt Handler
    if ((int_en & ADC0_IER_AWD2IE_Msk) && (int_pending & ADC0_ISR_AWD2_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_AWDG2IntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_AWDG2Callback(Instance);
    }

    //AWDG1 Interrupt Handler
    if ((int_en & ADC0_IER_AWD1IE_Msk) && (int_pending & ADC0_ISR_AWD1_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_AWDG1IntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_AWDG1Callback(Instance);
    }

    //AWDG0 Interrupt Handler
    if ((int_en & ADC0_IER_AWD0IE_Msk) && (int_pending & ADC0_ISR_AWD0_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_AWDG0IntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_AWDG0Callback(Instance);
    }

    //Overflow Interrupt Handler
    if ((int_en & ADC0_IER_OVRIE_Msk) && (int_pending & ADC0_ISR_OVR_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_OverflowIntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_OverflowCallback(Instance);
    }

    //Injected Sequence End Interrupt Handler
    if ((int_en & ADC0_IER_JEOSIE_Msk) && (int_pending & ADC0_ISR_JEOS_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_INJ_SeqEndIntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_INJ_SeqEndCallback(Instance);
    }

    //Injected Conversion End Interrupt Handler
    if ((int_en & ADC0_IER_JEOCIE_Msk) && (int_pending & ADC0_ISR_JEOC_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_INJ_ConvEndIntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_INJ_ConvEndCallback(Instance);
    }

    //Regular Sequence End Interrupt Handler
    if ((int_en & ADC0_IER_EOSIE_Msk) && (int_pending & ADC0_ISR_EOS_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_REG_SeqEndIntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_REG_SeqEndCallback(Instance);
    }

    //Regular Conversion End Interrupt Handler
    if ((int_en & ADC0_IER_EOCIE_Msk) && (int_pending & ADC0_ISR_EOC_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_REG_ConvEndIntPnd_Clr(Instance);

        //Callback
        LL_ADC_Norm_REG_ConvEndCallback(Instance);
    }
}

/**
  * @brief  ADC Normal Sample End Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_SampEndCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_SampEndCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal Ready Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_ReadyCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_ReadyCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal AWDG2 Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_AWDG2Callback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_AWDG2Callback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal AWDG1 Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_AWDG1Callback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_AWDG1Callback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal AWDG0 Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_AWDG0Callback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_AWDG0Callback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal Overflow Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_OverflowCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_OverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal Injected Sequence End Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_INJ_SeqEndCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_INJ_SeqEndCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal Injected Conversion End Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_INJ_ConvEndCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_INJ_ConvEndCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal Regular Sequence End Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_REG_SeqEndCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_REG_SeqEndCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC Normal Regular Conversion End Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
__WEAK void LL_ADC_Norm_REG_ConvEndCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Norm_REG_ConvEndCallback could be implemented in the user file
     */
}


/**
  * @brief  ADC Sample Channel IRQ Handler
  * @param  Instance Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type ADC Channel Number
  * @return None
  */
void LL_ADC_Samp_ChIRQHandler(ADC_TypeDef *Instance, ADC_ChETypeDef ch)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(ch < ADC_CH_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || ch >= ADC_CH_NUMS) {
        return;
    }

    //Sample Channel Conversion Done Interrupt Handler
    if (__LL_ADC_IsChConvDoneIntEn(Instance, ch) && __LL_ADC_IsChConvDoneIntPnd(Instance, ch)) {
        //Clear Interrupt Pending
        __LL_ADC_ChConvDoneIntPnd_Clr(Instance, ch);

        //Callback
        ADC_Samp_ChxConvDoneCallback[ch](Instance);
        LL_ADC_Samp_ChConvDoneCallback(Instance, ch);
    }
}

/**
  * @brief  ADC Sample Channel Conversion Done Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type ADC Channel Number
  * @return None
  */
__WEAK void LL_ADC_Samp_ChConvDoneCallback(ADC_TypeDef *Instance, ADC_ChETypeDef ch)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(ch);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_Samp_ChConvDoneCallback could be implemented in the user file
     */
}


/**
  * @brief  ADC DMA Channel Half Complete IRQ Handler
  * @param  Instance Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type ADC Channel Number
  * @return None
  */
void LL_ADC_DMA_ChHalfCpltIRQHandler(ADC_TypeDef *Instance, ADC_ChETypeDef ch)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(ch < ADC_CH_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || ch >= ADC_CH_NUMS) {
        return;
    }

    //DMA Channel Half Complete Interrupt Handler
    if (__LL_ADC_IsChDMAHalfCpltIntEn(Instance, ch) && __LL_ADC_IsChDMAHalfCpltIntPnd(Instance, ch)) {
        //Clear Interrupt Pending
        __LL_ADC_ChDMAHalfCpltIntPnd_Clr(Instance, ch);

        //Callback
        ADC_DMA_ChxHalfCpltCallback[ch](Instance);
        LL_ADC_DMA_ChHalfCpltCallback(Instance, ch);
    }
}

/**
  * @brief  ADC DMA Channel Half Complete Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type ADC Channel Number
  * @return None
  */
__WEAK void LL_ADC_DMA_ChHalfCpltCallback(ADC_TypeDef *Instance, ADC_ChETypeDef ch)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(ch);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_DMA_ChHalfCpltCallback could be implemented in the user file
     */
}


/**
  * @brief  ADC DMA Channel Complete IRQ Handler
  * @param  Instance Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type ADC Channel Number
  * @return None
  */
void LL_ADC_DMA_ChCpltIRQHandler(ADC_TypeDef *Instance, ADC_ChETypeDef ch)
{
    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(ch < ADC_CH_NUMS);

    if (!IS_ADC_ALL_INSTANCE(Instance) || ch >= ADC_CH_NUMS) {
        return;
    }

    //DMA Channel Complete Interrupt Handler
    if (__LL_ADC_IsChDMACpltIntEn(Instance, ch) && __LL_ADC_IsChDMACpltIntPnd(Instance, ch)) {
        //Clear Interrupt Pending
        __LL_ADC_ChDMACpltIntPnd_Clr(Instance, ch);

        //Callback
        ADC_DMA_ChxCpltCallback[ch](Instance);
        LL_ADC_DMA_ChCpltCallback(Instance, ch);
    }
}

/**
  * @brief  ADC DMA Channel Complete Interrupt Callback
  * @param  Instance Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type ADC Channel Number
  * @return None
  */
__WEAK void LL_ADC_DMA_ChCpltCallback(ADC_TypeDef *Instance, ADC_ChETypeDef ch)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(ch);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_DMA_ChCpltCallback could be implemented in the user file
     */
}


/**
  * @brief  ADC Sample IRQ Handler
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
void LL_ADC_Samp_IRQHandler(ADC_TypeDef *Instance)
{
    ADC_ChETypeDef ch;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));

    if (!IS_ADC_ALL_INSTANCE(Instance)) {
        return;
    }

    //ADC Sample All Interrupt Enalbe and Pending Get
    int_en = __LL_ADC_SampAllIntEn_Get(Instance);
    int_pending = __LL_ADC_SampAllIntPending_Get(Instance);


    for (ch = ADC_CH_0; ch < ADC_CH_NUMS; ch++) {
        //Channel Conversion Done Interrupt Handler
        if ((int_en & BIT(ch)) && (int_pending & BIT(ch))) {
            //Clear Interrupt Pending
            __LL_ADC_ChConvDoneIntPnd_Clr(Instance, ch);

            //Callback
            ADC_Samp_ChxConvDoneCallback[ch](Instance);
            LL_ADC_Samp_ChConvDoneCallback(Instance, ch);
        }
    }
}

ADC_SAMP_CHx_CONV_DONE_CALLBACK(0);                     /*!< ADC Sample Channel 0 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(1);                     /*!< ADC Sample Channel 1 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(2);                     /*!< ADC Sample Channel 2 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(3);                     /*!< ADC Sample Channel 3 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(4);                     /*!< ADC Sample Channel 4 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(5);                     /*!< ADC Sample Channel 5 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(6);                     /*!< ADC Sample Channel 6 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(7);                     /*!< ADC Sample Channel 7 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(8);                     /*!< ADC Sample Channel 8 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(9);                     /*!< ADC Sample Channel 9 Conversion Done Interrupt Callback    */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(10);                    /*!< ADC Sample Channel 10 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(11);                    /*!< ADC Sample Channel 11 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(12);                    /*!< ADC Sample Channel 12 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(13);                    /*!< ADC Sample Channel 13 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(14);                    /*!< ADC Sample Channel 14 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(15);                    /*!< ADC Sample Channel 15 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(16);                    /*!< ADC Sample Channel 16 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(17);                    /*!< ADC Sample Channel 17 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(18);                    /*!< ADC Sample Channel 18 Conversion Done Interrupt Callback   */
ADC_SAMP_CHx_CONV_DONE_CALLBACK(19);                    /*!< ADC Sample Channel 19 Conversion Done Interrupt Callback   */


/**
  * @brief  ADC DMA Half Complete IRQ Handler
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
void LL_ADC_DMA_HalfCpltIRQHandler(ADC_TypeDef *Instance)
{
    ADC_ChETypeDef ch;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));

    if (!IS_ADC_ALL_INSTANCE(Instance)) {
        return;
    }

    //ADC DMA Half Complete All Interrupt Enalbe and Pending Get
    int_en = __LL_ADC_DMAHalfCpltAllIntEn_Get(Instance);
    int_pending = __LL_ADC_DMAHalfCpltAllIntPending_Get(Instance);


    for (ch = ADC_CH_0; ch < ADC_CH_NUMS; ch++) {
        //DMA Half Complete Interrupt Handler
        if ((int_en & BIT(ch)) && (int_pending & BIT(ch))) {
            //Clear Interrupt Pending
            __LL_ADC_ChDMAHalfCpltIntPnd_Clr(Instance, ch);

            //Callback
            ADC_DMA_ChxHalfCpltCallback[ch](Instance);
            LL_ADC_DMA_ChHalfCpltCallback(Instance, ch);
        }
    }
}

ADC_DMA_CHx_HALF_CPLT_CALLBACK(0);                      /*!< ADC DMA Channel 0 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(1);                      /*!< ADC DMA Channel 1 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(2);                      /*!< ADC DMA Channel 2 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(3);                      /*!< ADC DMA Channel 3 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(4);                      /*!< ADC DMA Channel 4 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(5);                      /*!< ADC DMA Channel 5 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(6);                      /*!< ADC DMA Channel 6 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(7);                      /*!< ADC DMA Channel 7 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(8);                      /*!< ADC DMA Channel 8 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(9);                      /*!< ADC DMA Channel 9 Half Complete Interrupt Callback     */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(10);                     /*!< ADC DMA Channel 10 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(11);                     /*!< ADC DMA Channel 11 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(12);                     /*!< ADC DMA Channel 12 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(13);                     /*!< ADC DMA Channel 13 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(14);                     /*!< ADC DMA Channel 14 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(15);                     /*!< ADC DMA Channel 15 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(16);                     /*!< ADC DMA Channel 16 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(17);                     /*!< ADC DMA Channel 17 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(18);                     /*!< ADC DMA Channel 18 Half Complete Interrupt Callback    */
ADC_DMA_CHx_HALF_CPLT_CALLBACK(19);                     /*!< ADC DMA Channel 19 Half Complete Interrupt Callback    */


/**
  * @brief  ADC DMA Complete IRQ Handler
  * @param  Instance Specifies ADC peripheral
  * @return None
  */
void LL_ADC_DMA_CpltIRQHandler(ADC_TypeDef *Instance)
{
    ADC_ChETypeDef ch;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));

    if (!IS_ADC_ALL_INSTANCE(Instance)) {
        return;
    }

    //ADC DMA Complete All Interrupt Enalbe and Pending Get
    int_en = __LL_ADC_DMACpltAllIntEn_Get(Instance);
    int_pending = __LL_ADC_DMACpltAllIntPending_Get(Instance);


    for (ch = ADC_CH_0; ch < ADC_CH_NUMS; ch++) {
        //DMA Complete Interrupt Handler
        if ((int_en & BIT(ch)) && (int_pending & BIT(ch))) {
            //Clear Interrupt Pending
            __LL_ADC_ChDMACpltIntPnd_Clr(Instance, ch);

            //Callback
            ADC_DMA_ChxCpltCallback[ch](Instance);
            LL_ADC_DMA_ChCpltCallback(Instance, ch);
        }
    }
}

ADC_DMA_CHx_CPLT_CALLBACK(0);                    /*!< ADC DMA Channel 0  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(1);                    /*!< ADC DMA Channel 1  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(2);                    /*!< ADC DMA Channel 2  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(3);                    /*!< ADC DMA Channel 3  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(4);                    /*!< ADC DMA Channel 4  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(5);                    /*!< ADC DMA Channel 5  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(6);                    /*!< ADC DMA Channel 6  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(7);                    /*!< ADC DMA Channel 7  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(8);                    /*!< ADC DMA Channel 8  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(9);                    /*!< ADC DMA Channel 9  Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(10);                   /*!< ADC DMA Channel 10 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(11);                   /*!< ADC DMA Channel 11 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(12);                   /*!< ADC DMA Channel 12 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(13);                   /*!< ADC DMA Channel 13 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(14);                   /*!< ADC DMA Channel 14 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(15);                   /*!< ADC DMA Channel 15 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(16);                   /*!< ADC DMA Channel 16 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(17);                   /*!< ADC DMA Channel 17 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(18);                   /*!< ADC DMA Channel 18 Complete Interrupt Callback    */
ADC_DMA_CHx_CPLT_CALLBACK(19);                   /*!< ADC DMA Channel 19 Complete Interrupt Callback    */

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


#endif  /* LL_ADC_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

