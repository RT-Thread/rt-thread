/**
  ******************************************************************************
  * @file    tae32g58xx_ll_hrpwm.c
  * @author  MCD Application Team
  * @brief   HRPWM LL module driver
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


#define DBG_TAG             "HRPWM LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup HRPWM_LL HRPWM LL
  * @brief    HRPWM LL Module Driver
  * @{
  */

#ifdef LL_HRPWM_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/** @defgroup HRPWM_LL_Private_Constants HRPWM LL Private Constants
  * @brief    HRPWM LL Private Constants
  * @{
  */

/**
  * @brief HRPWM Defaul Timeout definition in ms Unit
  */
#define HRPWM_DEFAULT_TIMEOUT       (100)

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup HRPWM_LL_Private_Functions HRPWM LL Private Functions
  * @brief    HRPWM LL Private Functions
  * @{
  */
//Master Config
static LL_StatusETypeDef HRPWM_Mst_SyncCfg(HRPWM_TypeDef *Instance, HRPWM_Mst_SyncCfgTypeDef *cfg);

//Master/Slave Public Config
static LL_StatusETypeDef HRPWM_TmrBaseCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_TmrBaseCfgTypeDef *cfg);
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Mst_TmrBaseCfg(HRPWM_TypeDef *Instance, HRPWM_TmrBaseCfgTypeDef *cfg);
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Slv_TmrBaseCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_TmrBaseCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_TmrCmpCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_TmrCmpCfgTypeDef *cfg);
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Mst_TmrCmpCfg(HRPWM_TypeDef *Instance, HRPWM_TmrCmpCfgTypeDef *cfg);
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Slv_TmrCmpCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_TmrCmpCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_DACTrigCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_DACTrigCfgTypeDef *cfg);
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Mst_DACTrigCfg(HRPWM_TypeDef *Instance, HRPWM_DACTrigCfgTypeDef *cfg);
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Slv_DACTrigCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_DACTrigCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_SysDMACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_SysDMACfgTypeDef *cfg);
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Mst_SysDMACfg(HRPWM_TypeDef *Instance, HRPWM_SysDMACfgTypeDef *cfg);
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Slv_SysDMACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, 
        HRPWM_SysDMACfgTypeDef *cfg);


//Slave Comfig
static LL_StatusETypeDef HRPWM_Slv_TmrRollOverCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_Slv_TmrRollOverCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Slv_TmrEvtFilCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_ExtEvtNumETypeDef evtx, HRPWM_Slv_TmrEvtFilCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Slv_TmrEvtACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_Slv_TmrEvtACfgTypeDef *cfg, HRPWM_Slv_TmrEvtFilCfgTypeDef *evt_fil);
static LL_StatusETypeDef HRPWM_Slv_OutputCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_OutputCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Slv_DeadTimeCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_DeadTimeCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Slv_ChopCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_ChopCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Slv_CapCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_CapCfgTypeDef *cfg);

//Common Config
static LL_StatusETypeDef HRPWM_Comm_ExtEvtCfg(HRPWM_TypeDef *Instance, HRPWM_ExtEvtNumETypeDef evtx,
        HRPWM_Comm_ExtEvtCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Comm_FltCfg(HRPWM_TypeDef *Instance, HRPWM_FltNumETypeDef fltx, HRPWM_Comm_FltCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Comm_ADCTrigCfg(HRPWM_TypeDef *Instance, HRPWM_ADCTrigNumETypeDef adc_trigx,
        HRPWM_Comm_ADCTrigCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Comm_DLLCfg(HRPWM_TypeDef *Instance, HRPWM_Comm_DLLCfgTypeDef *cfg);
static LL_StatusETypeDef HRPWM_Comm_BurstModeCfg(HRPWM_TypeDef *Instance, HRPWM_Comm_BurstModeCfgTypeDef *cfg);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup HRPMW_LL_Exported_Functions HRPMW LL Exported Functions
  * @brief    HRPMW LL Exported Functions
  * @{
  */

/** @defgroup HRPMW_LL_Exported_Functions_Group1 HRPWM Init and DeInit Functions
  * @brief    HRPWM Init and DeInit Functions
  * @{
  */

/**
  * @brief  HRPWM LL Init
  * @param  Instance Specifies HRPWM peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_HRPWM_Init(HRPWM_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_HRPWM_MspInit(Instance);

    return LL_OK;
}

/**
  * @brief  HRPWM LL DeInit
  * @param  Instance Specifies HRPWM peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_HRPWM_DeInit(HRPWM_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Master PWM Disable
    __LL_HRPWM_Mst_PWM_Dis(Instance);

    //All PWMx Disable and Output Stop
    for (uint8_t pwmx = HRPWM_SLV_PWM_0; pwmx < HRPWM_SLV_PWM_NUMS; pwmx++) {
        __LL_HRPWM_Mst_PWMx_Dis(Instance, pwmx);
        __LL_HRPWM_Comm_PWMxOutA_Stop(Instance, pwmx);
        __LL_HRPWM_Comm_PWMxOutB_Stop(Instance, pwmx);
    }

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_HRPWM_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the HRPWM MSP
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_MspInit(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the HRPWM MSP
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_MspDeInit(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup HRPMW_LL_Exported_Functions_Group2 HRPWM Submodule Config Functions
  * @brief    HRPWM Submodule Config Functions
  * @{
  */

/**
  * @brief  HRPWM LL Master Sync Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Master Sync Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Mst_SyncCfg(HRPWM_TypeDef *Instance, HRPWM_Mst_SyncCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return HRPWM_Mst_SyncCfg(Instance, cfg);
}

/**
  * @brief  HRPWM LL Timer Base Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Timer Base to be Config, include Master PWM
  * @param  cfg Timer Base Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_TmrBaseCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_TmrBaseCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return HRPWM_TmrBaseCfg(Instance, pwmx, cfg);
}

/**
  * @brief  HRPWM LL Timer Compare Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Timer Compare to be Config, include Master PWM
  * @param  cfg Timer Compare Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_TmrCmpCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_TmrCmpCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return HRPWM_TmrCmpCfg(Instance, pwmx, cfg);
}

/**
  * @brief  HRPWM LL DAC Trigger Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx DAC Trigger to be Config, include Master PWM
  * @param  cfg DAC Trigger Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_DACTrigCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_DACTrigCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return HRPWM_DACTrigCfg(Instance, pwmx, cfg);
}

/**
  * @brief  HRPWM LL System DMA Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx System DMA to be Config, include Master PWM
  * @param  cfg System DMA Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_SysDMACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_SysDMACfgTypeDef *cfg)
{
    LL_StatusETypeDef ret = LL_FAILED;
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Check whether this config is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support HRPWM System DMA!\n");
        return LL_FAILED;
    }

    ret = HRPWM_SysDMACfg(Instance, pwmx, cfg);
    if (ret != LL_OK) {
        return ret;
    }

    return LL_HRPWM_RegUpd_Frc(Instance, pwmx);
}

/**
  * @brief  HRPWM LL Slave PWMx Timer Roll-Over Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Timer Roll-Over to be Config, not include Master PWM
  * @param  cfg Slave PWMx Timer Roll-Over Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_TmrRollOverCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_Slv_TmrRollOverCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Slv_TmrRollOverCfg(Instance, pwmx, cfg);
}

/**
  * @brief  HRPWM LL Slave PWMx Timer Event Filter Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Timer Event Filter to be Config, not include Master PWM
  * @param  evtx External Event Number to be Config
  * @param  cfg Slave PWMx Timer Event Filter Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_TmrEvtFilCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_ExtEvtNumETypeDef evtx, HRPWM_Slv_TmrEvtFilCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);
    assert_param(evtx < HRPWM_EXT_EVT_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS || evtx >= HRPWM_EXT_EVT_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Slv_TmrEvtFilCfg(Instance, pwmx, evtx, cfg);
}

/**
  * @brief  HRPWM LL Slave PWMx Timer Event A Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Timer Event A to be Config, not include Master PWM
  * @param  cfg Slave PWMx Timer Event A Config Pointer
  * @param  evt_fil Slave PWMx Timer Event Filter Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_TmrEvtACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_Slv_TmrEvtACfgTypeDef *cfg, HRPWM_Slv_TmrEvtFilCfgTypeDef *evt_fil)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);
    assert_param(evt_fil != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS || evt_fil == NULL) {
        return LL_INVALID;
    }

    return HRPWM_Slv_TmrEvtACfg(Instance, pwmx, cfg, evt_fil);
}

/**
  * @brief  HRPWM LL Slave PWMx Output Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Output to be Config, not include Master PWM
  * @param  cfg Slave PWMx Output Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_OutputCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_OutputCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Slv_OutputCfg(Instance, pwmx, cfg);
}

/**
  * @brief  HRPWM LL Slave PWMx DeadTime Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx DeadTime to be Config, not include Master PWM
  * @param  cfg Slave PWMx DeadTime Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_DeadTimeCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_DeadTimeCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Slv_DeadTimeCfg(Instance, pwmx, cfg);
}

/**
  * @brief  HRPWM LL Slave PWMx Chopper Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Chopper to be Config, not include Master PWM
  * @param  cfg Slave PWMx Chopper Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_ChopCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_ChopCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Slv_ChopCfg(Instance, pwmx, cfg);
}

/**
  * @brief  HRPWM LL Slave PWMx Capture Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Capture to be Config, not include Master PWM
  * @param  cfg Slave PWMx Capture Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_CapCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_CapCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Slv_CapCfg(Instance, pwmx, cfg);
}

/**
  * @brief  HRPWM LL Common External Event Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  evtx External Event Nubmer Which to be Config
  * @param  cfg Common External Event Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_ExtEvtCfg(HRPWM_TypeDef *Instance, HRPWM_ExtEvtNumETypeDef evtx,
        HRPWM_Comm_ExtEvtCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(evtx < HRPWM_EXT_EVT_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || evtx >= HRPWM_EXT_EVT_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Comm_ExtEvtCfg(Instance, evtx, cfg);
}

/**
  * @brief  HRPWM LL Common Fault Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  fltx Fault Number Which to be Config
  * @param  cfg Common Fault Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_FltCfg(HRPWM_TypeDef *Instance, HRPWM_FltNumETypeDef fltx, HRPWM_Comm_FltCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(fltx < HRPWM_FLT_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || fltx >= HRPWM_FLT_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Comm_FltCfg(Instance, fltx, cfg);
}

/**
  * @brief  HRPWM LL Common ADC Trigger Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  adc_trigx ADC Trigger Number Which to be Config
  * @param  cfg Common ADC Trigger Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_ADCTrigCfg(HRPWM_TypeDef *Instance, HRPWM_ADCTrigNumETypeDef adc_trigx,
        HRPWM_Comm_ADCTrigCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(adc_trigx < HRPWM_ADC_TRIG_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || adc_trigx >= HRPWM_ADC_TRIG_NUMS) {
        return LL_INVALID;
    }

    return HRPWM_Comm_ADCTrigCfg(Instance, adc_trigx, cfg);
}

/**
  * @brief  HRPWM LL Common DLL Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Common DLL Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_DLLCfg(HRPWM_TypeDef *Instance, HRPWM_Comm_DLLCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return HRPWM_Comm_DLLCfg(Instance, cfg);
}

/**
  * @brief  HRPWM LL Common Burst Mode Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Common Burst Mode Config Pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_BurstModeCfg(HRPWM_TypeDef *Instance, HRPWM_Comm_BurstModeCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return HRPWM_Comm_BurstModeCfg(Instance, cfg);
}

/**
  * @brief  HRPWM LL Common PWMx Output Swap Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Output to be Swap Config, not include Master PWM
  * @param  swap_en Swap Enable/Disable
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_OutputSwapCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, bool swap_en)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Common Output Swap Config
    LL_FUNC_ALTER(swap_en, __LL_HRPWM_Comm_PWMxOutputSwap_En(Instance, pwmx), __LL_HRPWM_Comm_PWMxOutputSwap_Dis(Instance, pwmx));

    return LL_OK;
}

/**
  * @brief  HRPWM LL Common Multi PWMx Output Swap Enable
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmxs Indicate Multi PWMx Output to be Swap Enable, not include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_MultiOutputSwap_En(HRPWM_TypeDef *Instance, uint32_t pwmxs)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_HRPWM_Comm_MultiPWMxOutputSwap_En(Instance, pwmxs);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Common Multi PWMx Output Swap Disable
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmxs Indicate Multi PWMx Output to be Swap Disable, not include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_MultiOutputSwap_Dis(HRPWM_TypeDef *Instance, uint32_t pwmxs)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_HRPWM_Comm_MultiPWMxOutputSwap_Dis(Instance, pwmxs);

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup HRPMW_LL_Exported_Functions_Group3 HRPWM Operation Functions
  * @brief    HRPWM Operation Functions
  * @{
  */

/**
  * @brief  HRPWM LL PWMx Timer Counter Start
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Timer Counter to be Start, include Master PWM
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_TmrCntr_Start(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //PWM Timer Counter Enable
    if (pwmx == HRPWM_MST_PWM) {
        __LL_HRPWM_Mst_PWM_En(Instance);
    } else {
        assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

        if (pwmx >= HRPWM_SLV_PWM_NUMS) {
            return LL_INVALID;
        }

        __LL_HRPWM_Mst_PWMx_En(Instance, pwmx);
    }

    return LL_OK;
}

/**
  * @brief  HRPWM LL Multi PWMx Timer Counter Start Simultaneously
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmxs Indicate Multi PWMx Timer Counter to be Start, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_MultiTmrCntr_Start(HRPWM_TypeDef *Instance, uint32_t pwmxs)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_HRPWM_Mst_MultiPWMx_En(Instance, pwmxs);

    return LL_OK;
}

/**
  * @brief  HRPWM LL PWMx Timer Counter Stop
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Timer Counter to be Stop, include Master PWM
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_TmrCntr_Stop(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //PWM Timer Counter Disable
    if (pwmx == HRPWM_MST_PWM) {
        __LL_HRPWM_Mst_PWM_Dis(Instance);
    } else {
        assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

        if (pwmx >= HRPWM_SLV_PWM_NUMS) {
            return LL_INVALID;
        }

        __LL_HRPWM_Mst_PWMx_Dis(Instance, pwmx);
    }

    return LL_OK;
}

/**
  * @brief  HRPWM LL Multi PWMx Timer Counter Stop Simultaneously
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmxs Indicate Multi PWMx Timer Counter to be Stop, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_MultiTmrCntr_Stop(HRPWM_TypeDef *Instance, uint32_t pwmxs)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_HRPWM_Mst_MultiPWMx_Dis(Instance, pwmxs);

    return LL_OK;
}

/**
  * @brief  HRPWM LL PWMx Timer Counter Reset
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Timer Counter to be Reset, include Master PWM
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_TmrCntr_Rst(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    //PWM Timer Counter Reset
    if (pwmx == HRPWM_MST_PWM) {
        __LL_HRPWM_Comm_MstPWMSwRstCntr_Set(Instance);

        //Wait for Reset complete
        while (__LL_HRPWM_Comm_MstPWMSwRstCntr_Get(Instance)) {
            if ((LL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
                return LL_TIMEOUT;
            }
        }
    } else {
        assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

        if (pwmx >= HRPWM_SLV_PWM_NUMS) {
            return LL_INVALID;
        }

        __LL_HRPWM_Comm_PWMxSwRstCntr_Set(Instance, pwmx);

        //Wait for Reset complete
        while (__LL_HRPWM_Comm_PWMxSwRstCntr_Get(Instance, pwmx)) {
            if ((LL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
                return LL_TIMEOUT;
            }
        }
    }

    return LL_OK;
}

/**
  * @brief  HRPWM LL Multi PWMx Timer Counter Reset
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmxs Indicate Multi PWMx Timer Counter to be Reset, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_MultiTmrCntr_Rst(HRPWM_TypeDef *Instance, uint32_t pwmxs)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    __LL_HRPWM_Comm_MultiPWMxSwRstCntr_Set(Instance, pwmxs);

    //Wait for Reset complete
    while (__LL_HRPWM_Comm_MultiPWMxSwRstCntr_Get(Instance, pwmxs)) {
        if ((LL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
            return LL_TIMEOUT;
        }
    }

    return LL_OK;
}

/**
  * @brief  HRPWM LL Slave PWMx Output Start
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Output to be Start, not include Master PWM
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_Output_Start(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //PWMx Output A/B Start
    __LL_HRPWM_Comm_PWMxOutA_Start(Instance, pwmx);
    __LL_HRPWM_Comm_PWMxOutB_Start(Instance, pwmx);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Multi Slave PWMx Output Start
  * @param  Instance Specifies HRPWM peripheral
  * @param  output_start_mask Output start mask, combination of HRPWM_PWMOutputMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_MultiSlv_Output_Start(HRPWM_TypeDef *Instance, uint32_t output_start_mask)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_HRPWM_Comm_MultiPWMxOutput_Start(Instance, output_start_mask);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Slave PWMx Output Stop
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Output to be Stop, not include Master PWM
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Slv_Output_Stop(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //PWMx Output A/B Stop
    __LL_HRPWM_Comm_PWMxOutA_Stop(Instance, pwmx);
    __LL_HRPWM_Comm_PWMxOutB_Stop(Instance, pwmx);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Multi Slave PWMx Output Stop
  * @param  Instance Specifies HRPWM peripheral
  * @param  output_stop_mask Output stop mask, combination of HRPWM_PWMOutputMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_MultiSlv_Output_Stop(HRPWM_TypeDef *Instance, uint32_t output_stop_mask)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_HRPWM_Comm_MultiPWMxOutput_Stop(Instance, output_stop_mask);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Register Update Enable
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Register Update to be Enable, include Master PWM
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_RegUpd_En(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Common Register Update Enable
    if (pwmx == HRPWM_MST_PWM) {
        __LL_HRPWM_Comm_MstPWMRegUpd_En(Instance);
    } else {
        assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

        if (pwmx >= HRPWM_SLV_PWM_NUMS) {
            return LL_INVALID;
        }

        __LL_HRPWM_Comm_PWMxRegUpd_En(Instance, pwmx);
    }

    return LL_OK;
}

/**
  * @brief  HRPWM LL Multi Register Update Enable
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmxs Indicate Multi PWMx Register Update to be Enable, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_MultiRegUpd_En(HRPWM_TypeDef *Instance, uint32_t pwmxs)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_HRPWM_Comm_MultiPWMRegUpd_En(Instance, pwmxs);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Register Update Disable
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Register Update to be Disable, include Master PWM
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_RegUpd_Dis(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Common Register Update Disable
    if (pwmx == HRPWM_MST_PWM) {
        __LL_HRPWM_Comm_MstPWMRegUpd_Dis(Instance);
    } else {
        assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

        if (pwmx >= HRPWM_SLV_PWM_NUMS) {
            return LL_INVALID;
        }

        __LL_HRPWM_Comm_PWMxRegUpd_Dis(Instance, pwmx);
    }

    return LL_OK;
}

/**
  * @brief  HRPWM LL Multi Register Update Disable
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmxs Indicate Multi PWMx Register Update to be Disable, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_MultiRegUpd_Dis(HRPWM_TypeDef *Instance, uint32_t pwmxs)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_HRPWM_Comm_MultiPWMRegUpd_Dis(Instance, pwmxs);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Register Update Software Force
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Register Update to be Force, include Master PWM
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_RegUpd_Frc(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    //Common Register Update Force
    if (pwmx == HRPWM_MST_PWM) {
        __LL_HRPWM_Comm_MstPWMSwUpdReg_Set(Instance);

        //Wait for update complete
        while (__LL_HRPWM_Comm_MstPWMSwUpdReg_Get(Instance)) {
            if ((LL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
                return LL_TIMEOUT;
            }
        }
    } else {
        assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

        if (pwmx >= HRPWM_SLV_PWM_NUMS) {
            return LL_INVALID;
        }

        __LL_HRPWM_Comm_PWMxSwUpdReg_Set(Instance, pwmx);

        //Wait for update complete
        while (__LL_HRPWM_Comm_PWMxSwUpdReg_Get(Instance, pwmx)) {
            if ((LL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
                return LL_TIMEOUT;
            }
        }
    }

    return LL_OK;
}


/**
  * @brief  HRPWM LL Multi Register Update Software Force
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmxs Indicate Multi PWMx Register Update to be Force, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_MultiRegUpd_Frc(HRPWM_TypeDef *Instance, uint32_t pwmxs)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    __LL_HRPWM_Comm_MultiPWMxSwUpdReg_Set(Instance, pwmxs);

    //Wait for update complete
    while (__LL_HRPWM_Comm_MultiPWMxSwUpdReg_Get(Instance, pwmxs)) {
        if ((LL_GetTick() - tickstart) > HRPWM_DEFAULT_TIMEOUT) {
            return LL_TIMEOUT;
        }
    }

    return LL_OK;
}

/**
  * @brief  HRPWM LL Common DLL Start
  * @param  Instance Specifies HRPWM peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_DLL_Start(HRPWM_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //DLL Enable
    __LL_HRPWM_Comm_DLL_En(Instance);

    //DLL Start
    __LL_HRPWM_Comm_DLL_Start(Instance);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Common DLL Stop
  * @param  Instance Specifies HRPWM peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_DLL_Stop(HRPWM_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //DLL Stop
    __LL_HRPWM_Comm_DLL_Stop(Instance);

    //DLL Disable
    __LL_HRPWM_Comm_DLL_Dis(Instance);

    return LL_OK;
}

/**
  * @brief  HRPWM LL Common Fault Counter Reset
  * @param  Instance Specifies HRPWM peripheral
  * @param  fltx Fault Number Which Counter to be Reset
  * @return LL Status
  */
LL_StatusETypeDef LL_HRPWM_Comm_FltCntrRst(HRPWM_TypeDef *Instance, HRPWM_FltNumETypeDef fltx)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(fltx < HRPWM_FLT_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || fltx >= HRPWM_FLT_NUMS) {
        return LL_INVALID;
    }

    //Common Fault X Counter Reset
    __LL_HRPWM_Comm_FltXCntr_Rst(Instance, fltx);

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup HRPMW_LL_Exported_Functions_Interrupt HRPWM Interrupt Handler and Callback
  * @brief    HRPWM Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  HRPWM Master IRQ Handler
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
void LL_HRPWM_Mst_IRQHandler(HRPWM_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return;
    }

    //HRPWM Master All Interrupt Enalbe and Pending Get
    int_en = __LL_HRPWM_Mst_AllIntEn_Get(Instance);
    int_pending = __LL_HRPWM_Mst_AllIntPnd_Get(Instance);


    //Compare A Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MCMPAIE_Msk) && (int_pending & HRPWM_MST_MISR_MCMPA_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_CmpAIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_CmpACallback(Instance);
    }

    //Compare B Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MCMPBIE_Msk) && (int_pending & HRPWM_MST_MISR_MCMPB_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_CmpBIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_CmpBCallback(Instance);
    }

    //Compare C Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MCMPCIE_Msk) && (int_pending & HRPWM_MST_MISR_MCMPC_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_CmpCIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_CmpCCallback(Instance);
    }

    //Compare D Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MCMPDIE_Msk) && (int_pending & HRPWM_MST_MISR_MCMPD_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_CmpDIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_CmpDCallback(Instance);
    }

    //Period Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MPERIE_Msk) && (int_pending & HRPWM_MST_MISR_MPER_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_PeriodIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_PeriodCallback(Instance);
    }

    //Sync Input Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_SYNCIE_Msk) && (int_pending & HRPWM_MST_MISR_SYNC_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_SyncInputIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_SyncInputCallback(Instance);
    }

    //Update Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MUPDIE_Msk) && (int_pending & HRPWM_MST_MISR_MUPD_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_UpdateIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_UpdateCallback(Instance);
    }

    //Reset Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MRSTIE_Msk) && (int_pending & HRPWM_MST_MISR_MRST_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_RstIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_RstCallback(Instance);
    }

    //Repetition Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MREPIE_Msk) && (int_pending & HRPWM_MST_MISR_MREP_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_RepIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Mst_RepCallback(Instance);
    }
}

/**
  * @brief  HRPWM Master Compare A Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_CmpACallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_CmpACallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Compare B Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_CmpBCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_CmpBCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Compare C Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_CmpCCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_CmpCCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Compare D Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_CmpDCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_CmpDCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Period Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_PeriodCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_PeriodCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Sync Input Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_SyncInputCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_SyncInputCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Update Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_UpdateCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_UpdateCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Reset Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_RstCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_RstCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Master Repetition Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Mst_RepCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Mst_RepCallback could be implemented in the user file
     */
}


/**
  * @brief  HRPWM Slave IRQ Handler
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt to be Handler, not include Master PWM
  * @return None
  */
void LL_HRPWM_Slv_IRQHandler(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return;
    }

    //HRPWM Slave All Interrupt Enalbe and Pending Get
    int_en = __LL_HRPWM_Slv_AllIntEn_Get(Instance, pwmx);
    int_pending = __LL_HRPWM_Slv_AllIntPnd_Get(Instance, pwmx);


    //Compare A Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_CMPAIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_CMPA_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_CmpAIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_CmpACallback(Instance, pwmx);
    }

    //Compare B Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_CMPBIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_CMPB_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_CmpBIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_CmpBCallback(Instance, pwmx);
    }

    //Compare C Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_CMPCIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_CMPC_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_CmpCIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_CmpCCallback(Instance, pwmx);
    }

    //Compare D Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_CMPDIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_CMPD_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_CmpDIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_CmpDCallback(Instance, pwmx);
    }

    //Period/Roll-Over Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_PERIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_PER_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_PrdRollOverIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_PrdRollOverCallback(Instance, pwmx);
    }

    //Update Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_UPDIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_UPD_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_UpdateIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_UpdateCallback(Instance, pwmx);
    }

    //OutA Set Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_SETAIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_SETA_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_OutASetIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_OutASetCallback(Instance, pwmx);
    }

    //OutA Clear Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_CLRAIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_CLRA_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_OutAClrIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_OutAClrCallback(Instance, pwmx);
    }

    //OutB Set Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_SETBIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_SETB_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_OutBSetIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_OutBSetCallback(Instance, pwmx);
    }

    //OutB Clear Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_CLRBIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_CLRB_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_OutBClrIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_OutBClrCallback(Instance, pwmx);
    }

    //Reset Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_RSTIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_RST_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_RstIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_RstCallback(Instance, pwmx);
    }

    //Repetition Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_REPIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_REP_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_RepIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_RepCallback(Instance, pwmx);
    }

    //Capture A Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_CAPAIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_CAPA_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_CapAIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_CapACallback(Instance, pwmx);
    }

    //Capture B Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_CAPBIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_CAPB_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_CapBIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_CapBCallback(Instance, pwmx);
    }

    //Delayed Protection Interrupt Handler
    if ((int_en & HRPWM_SLV0_PWMDIER_DLYPRTIE_Msk) && (int_pending & HRPWM_SLV0_PWMISR_DLYPRT_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Slv_DlyProtIntPnd_Clr(Instance, pwmx);

        //Callback
        LL_HRPWM_Slv_DlyProtCallback(Instance, pwmx);
    }
}

/**
  * @brief  HRPWM Slave PWMx Compare A Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_CmpACallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_CmpACallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Compare B Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_CmpBCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_CmpBCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Compare C Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_CmpCCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_CmpCCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Compare D Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_CmpDCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_CmpDCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Period/Roll-Over Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_PrdRollOverCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_PrdRollOverCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Update Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_UpdateCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_UpdateCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx OutA Set Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_OutASetCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_OutASetCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx OutA Clear Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_OutAClrCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_OutAClrCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx OutB Set Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_OutBSetCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_OutBSetCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx OutB Clear Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_OutBClrCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_OutBClrCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Reset Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_RstCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_RstCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Repetition Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_RepCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_RepCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Capture A Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_CapACallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_CapACallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Capture B Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_CapBCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_CapBCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Slave PWMx Delayed Protection Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Interrupt Callback, not include Master PWM
  * @return None
  */
__WEAK void LL_HRPWM_Slv_DlyProtCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pwmx);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Slv_DlyProtCallback could be implemented in the user file
     */
}


/**
  * @brief  HRPWM Common IRQ Handler
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
void LL_HRPWM_Comm_IRQHandler(HRPWM_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));

    if (!IS_HRPWM_ALL_INSTANCE(Instance)) {
        return;
    }

    //HRPWM Common All Interrupt Enalbe and Pending Get
    int_en = __LL_HRPWM_Comm_AllIntEn_Get(Instance);
    int_pending = __LL_HRPWM_Comm_AllIntPnd_Get(Instance);


    //Fault 0 Interrupt Handler
    if ((int_en & HRPWM_COM_IER_FLT0IE_Msk) && (int_pending & HRPWM_COM_ISR_FLT0_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_Flt0IntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_Flt0Callback(Instance);
    }

    //Fault 1 Interrupt Handler
    if ((int_en & HRPWM_COM_IER_FLT1IE_Msk) && (int_pending & HRPWM_COM_ISR_FLT1_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_Flt1IntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_Flt1Callback(Instance);
    }

    //Fault 2 Interrupt Handler
    if ((int_en & HRPWM_COM_IER_FLT2IE_Msk) && (int_pending & HRPWM_COM_ISR_FLT2_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_Flt2IntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_Flt2Callback(Instance);
    }

    //Fault 3 Interrupt Handler
    if ((int_en & HRPWM_COM_IER_FLT3IE_Msk) && (int_pending & HRPWM_COM_ISR_FLT3_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_Flt3IntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_Flt3Callback(Instance);
    }

    //Fault 4 Interrupt Handler
    if ((int_en & HRPWM_COM_IER_FLT4IE_Msk) && (int_pending & HRPWM_COM_ISR_FLT4_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_Flt4IntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_Flt4Callback(Instance);
    }

    //Fault 5 Interrupt Handler
    if ((int_en & HRPWM_COM_IER_FLT5IE_Msk) && (int_pending & HRPWM_COM_ISR_FLT5_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_Flt5IntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_Flt5Callback(Instance);
    }

    //Fault 6 Interrupt Handler
    if ((int_en & HRPWM_COM_IER_FLT6IE_Msk) && (int_pending & HRPWM_COM_ISR_FLT6_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_Flt6IntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_Flt6Callback(Instance);
    }

    //Fault 7 Interrupt Handler
    if ((int_en & HRPWM_COM_IER_FLT7IE_Msk) && (int_pending & HRPWM_COM_ISR_FLT7_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_Flt7IntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_Flt7Callback(Instance);
    }

    //System Fault Interrupt Handler
    if ((int_en & HRPWM_COM_IER_SYSFLTIE_Msk) && (int_pending & HRPWM_COM_ISR_SYSFLT_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_SysFltIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_SysFltCallback(Instance);
    }

    //Burst Mode Period Interrupt Handler
    if ((int_en & HRPWM_COM_IER_BMPERIE_Msk) && (int_pending & HRPWM_COM_ISR_BMPER_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Comm_BurstModePrdIntPnd_Clr(Instance);

        //Callback
        LL_HRPWM_Comm_BurstPrdCallback(Instance);
    }
}

/**
  * @brief  HRPWM Common Fault 0 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_Flt0Callback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_Flt0Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 1 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_Flt1Callback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_Flt1Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 2 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_Flt2Callback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_Flt2Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 3 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_Flt3Callback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_Flt3Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 4 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_Flt4Callback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_Flt4Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 5 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_Flt5Callback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_Flt5Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 6 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_Flt6Callback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_Flt6Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Fault 7 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_Flt7Callback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_Flt7Callback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common System Fault Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_SysFltCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_SysFltCallback could be implemented in the user file
     */
}

/**
  * @brief  HRPWM Common Busrt Mode Period Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__WEAK void LL_HRPWM_Comm_BurstPrdCallback(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_Comm_BurstPrdCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup HRPWM_LL_Private_Functions
  * @{
  */

/**
  * @brief  HRPWM Master Sync Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Master Sync Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Mst_SyncCfg(HRPWM_TypeDef *Instance, HRPWM_Mst_SyncCfgTypeDef *cfg)
{
    LL_StatusETypeDef ret = LL_ERROR;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Sync Mode Disable
    if (cfg->mode == HRPWM_MST_SYNC_MODE_DIS) {
        __LL_HRPWM_Mst_SyncEvtInput_Dis(Instance);
        __LL_HRPWM_Mst_SyncEvtOutput_Dis(Instance);
        return LL_OK;
    }

    //Sync Mode Master (Sync Output)
    if (cfg->mode & HRPWM_MST_SYNC_MODE_MST) {
        __LL_HRPWM_Mst_SyncEvtOutputSrc_Set(Instance, cfg->out_src);
        __LL_HRPWM_Mst_SyncEvtOutputPol_Set(Instance, cfg->out_pol);
        __LL_HRPWM_Mst_SyncEvtOutput_En(Instance);
        ret = LL_OK;
    }

    //Sync Mode Slave (Sync Input)
    if (cfg->mode & HRPWM_MST_SYNC_MODE_SLV) {
        __LL_HRPWM_Mst_SyncEvtInputSrc_Set(Instance, cfg->in_src);
        __LL_HRPWM_Mst_SyncEvtInput_En(Instance);
        ret = LL_OK;
    }

    return ret;
}


/**
  * @brief  HRPWM Timer Base Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Timer Base to be Config, include Master PWM
  * @param  cfg Timer Base Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_TmrBaseCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_TmrBaseCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Timer Base Config
    if (pwmx == HRPWM_MST_PWM) {
        return HRPWM_Mst_TmrBaseCfg(Instance, cfg);
    } else {
        return HRPWM_Slv_TmrBaseCfg(Instance, pwmx, cfg);
    }
}

/**
  * @brief  HRPWM Master PWM Timer Base Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Master PWM Timer Base Config Pointer
  * @return LL Status
  */
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Mst_TmrBaseCfg(HRPWM_TypeDef *Instance, HRPWM_TmrBaseCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Master PWM Timer Base Config
    __LL_HRPWM_Mst_INT_En_Cfg(Instance, cfg->int_en_msk);
    __LL_HRPWM_Mst_DMA_En_Cfg(Instance, cfg->dma_en_msk);
    __LL_HRPWM_Mst_ClkDiv_Set(Instance, cfg->clk_prescl);
    __LL_HRPWM_Mst_WorkMode_Set(Instance, cfg->work_mode);
    __LL_HRPWM_Mst_RepPeriod_Set(Instance, cfg->rep_prd);
    __LL_HRPWM_Mst_CntrPeriod_Set(Instance, cfg->cntr_prd);
    __LL_HRPWM_Mst_UpdateGate_Set(Instance, cfg->mst_upd_gate);
    LL_FUNC_ALTER(cfg->single_retrig_en, __LL_HRPWM_Mst_ReTrigMode_En(Instance), __LL_HRPWM_Mst_ReTrigMode_Dis(Instance));
    LL_FUNC_ALTER(cfg->sync_rst_en, __LL_HRPWM_Mst_SyncEvtRstMstPWM_En(Instance), __LL_HRPWM_Mst_SyncEvtRstMstPWM_Dis(Instance));
    LL_FUNC_ALTER(cfg->sync_start_en, __LL_HRPWM_Mst_SyncEvtStartMstPWM_En(Instance), __LL_HRPWM_Mst_SyncEvtStartMstPWM_Dis(Instance));
    LL_FUNC_ALTER(cfg->burst_cnt_stop_en, __LL_HRPWM_Comm_MstPWMCntrStopInBurstMode_En(Instance),
                  __LL_HRPWM_Comm_MstPWMCntrStopInBurstMode_Dis(Instance));

    __LL_HRPWM_Mst_IntlvdMode_Set(Instance, cfg->intlvd_mode);
    LL_FUNC_ALTER(cfg->half_mode_en, __LL_HRPWM_Mst_HalfMode_En(Instance), __LL_HRPWM_Mst_HalfMode_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Base Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Timer Base to be Config, not include Master PWM
  * @param  cfg Slave PWMx Timer Base Config Pointer
  * @return LL Status
  */
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Slv_TmrBaseCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_TmrBaseCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Slave PWMx Timer Base Config
    __LL_HRPWM_Slv_INT_En_Cfg(Instance, pwmx, cfg->int_en_msk);
    __LL_HRPWM_Slv_DMA_En_Cfg(Instance, pwmx, cfg->dma_en_msk);
    __LL_HRPWM_Slv_ClkDiv_Set(Instance, pwmx, cfg->clk_prescl);
    __LL_HRPWM_Slv_WorkMode_Set(Instance, pwmx, cfg->work_mode);
    __LL_HRPWM_Slv_RepPeriod_Set(Instance, pwmx, cfg->rep_prd);
    __LL_HRPWM_Slv_CntrPeriod_Set(Instance, pwmx, cfg->cntr_prd);
    LL_FUNC_ALTER(cfg->single_retrig_en, __LL_HRPWM_Slv_ReTrigMode_En(Instance, pwmx), __LL_HRPWM_Slv_ReTrigMode_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->sync_rst_en, __LL_HRPWM_Slv_SyncEvtRstPWMx_En(Instance, pwmx), __LL_HRPWM_Slv_SyncEvtRstPWMx_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->sync_start_en, __LL_HRPWM_Slv_SyncEvtStartPWMx_En(Instance, pwmx),
                  __LL_HRPWM_Slv_SyncEvtStartPWMx_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->burst_cnt_stop_en, __LL_HRPWM_Comm_PWMxCntrStopInBurstMode_En(Instance, pwmx),
                  __LL_HRPWM_Comm_PWMxCntrStopInBurstMode_Dis(Instance, pwmx));

    __LL_HRPWM_Slv_CntrRstEvtEn_Cfg(Instance, pwmx, cfg->cntr_rst_evt);
    __LL_HRPWM_Slv_ReSyncMode_Set(Instance, pwmx, cfg->resync_mode);

    __LL_HRPWM_Slv_IntlvdMode_Set(Instance, pwmx, cfg->intlvd_mode);
    LL_FUNC_ALTER(cfg->half_mode_en, __LL_HRPWM_Slv_HalfMode_En(Instance, pwmx), __LL_HRPWM_Slv_HalfMode_Dis(Instance, pwmx));

    __LL_HRPWM_Slv_UpdateGate_Set(Instance, pwmx, cfg->upd_gate);
    __LL_HRPWM_Slv_CmpBAutoDlyMode_Set(Instance, pwmx, cfg->cmpB_auto_dly_mode);
    __LL_HRPWM_Slv_CmpDAutoDlyMode_Set(Instance, pwmx, cfg->cmpD_auto_dly_mode);
    LL_FUNC_ALTER(cfg->push_pull_en, __LL_HRPWM_Slv_PushPullMode_En(Instance, pwmx), __LL_HRPWM_Slv_PushPullMode_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->trig_half_en, __LL_HRPWM_Slv_TrigHalfMode_En(Instance, pwmx), __LL_HRPWM_Slv_TrigHalfMode_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->cmpA_greatr_than_en, __LL_HRPWM_Slv_CmpAGreaterThanMode_En(Instance, pwmx),
                  __LL_HRPWM_Slv_CmpAGreaterThanMode_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->cmpC_greatr_than_en, __LL_HRPWM_Slv_CmpCGreaterThanMode_En(Instance, pwmx),
                  __LL_HRPWM_Slv_CmpCGreaterThanMode_Dis(Instance, pwmx));

    return LL_OK;
}

/**
  * @brief  HRPWM Timer Compare Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx Timer Compare to be Config, include Master PWM
  * @param  cfg Timer Compare Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_TmrCmpCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_TmrCmpCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Timer Compare Config
    if (pwmx == HRPWM_MST_PWM) {
        return HRPWM_Mst_TmrCmpCfg(Instance, cfg);
    } else {
        return HRPWM_Slv_TmrCmpCfg(Instance, pwmx, cfg);
    }
}

/**
  * @brief  HRPWM Master PWM Timer Compare Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Master PWM Timer Compare Config Pointer
  * @return LL Status
  */
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Mst_TmrCmpCfg(HRPWM_TypeDef *Instance, HRPWM_TmrCmpCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Master PWM Timer Compare Config
    __LL_HRPWM_Mst_CmpAVal_Set(Instance, cfg->cmp_a_val);
    __LL_HRPWM_Mst_CmpBVal_Set(Instance, cfg->cmp_b_val);
    __LL_HRPWM_Mst_CmpCVal_Set(Instance, cfg->cmp_c_val);
    __LL_HRPWM_Mst_CmpDVal_Set(Instance, cfg->cmp_d_val);

    LL_FUNC_ALTER(cfg->pre_load_en, __LL_HRPWM_Mst_Preload_En(Instance), __LL_HRPWM_Mst_Preload_Dis(Instance));
    LL_FUNC_ALTER(cfg->rep_upd_en, __LL_HRPWM_Mst_RepTrigUpd_En(Instance), __LL_HRPWM_Mst_RepTrigUpd_Dis(Instance));
    LL_FUNC_ALTER(cfg->rst_ro_upd_en, __LL_HRPWM_Mst_RstRollOverTrigUpd_En(Instance), __LL_HRPWM_Mst_RstRollOverTrigUpd_Dis(Instance));

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Compare Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Timer Compare to be Config, not include Master PWM
  * @param  cfg Slave PWMx Timer Compare Config Pointer
  * @return LL Status
  */
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Slv_TmrCmpCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_TmrCmpCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Slave PWMx Timer Compare Config
    __LL_HRPWM_Slv_CmpAVal_Set(Instance, pwmx, cfg->cmp_a_val);
    __LL_HRPWM_Slv_CmpBVal_Set(Instance, pwmx, cfg->cmp_b_val);
    __LL_HRPWM_Slv_CmpCVal_Set(Instance, pwmx, cfg->cmp_c_val);
    __LL_HRPWM_Slv_CmpDVal_Set(Instance, pwmx, cfg->cmp_d_val);

    LL_FUNC_ALTER(cfg->pre_load_en, __LL_HRPWM_Slv_Preload_En(Instance, pwmx), __LL_HRPWM_Slv_Preload_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->rep_upd_en, __LL_HRPWM_Slv_RepTrigUpd_En(Instance, pwmx), __LL_HRPWM_Slv_RepTrigUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->rst_ro_upd_en, __LL_HRPWM_Slv_RstRollOverTrigUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_RstRollOverTrigUpd_Dis(Instance, pwmx));

    LL_FUNC_ALTER(cfg->mst_pwm_upd_en, __LL_HRPWM_Slv_MstPWMUpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_MstPWMUpdEvtTrigPWMxUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->pwm0_upd_en, __LL_HRPWM_Slv_PWM0UpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_PWM0UpdEvtTrigPWMxUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->pwm1_upd_en, __LL_HRPWM_Slv_PWM1UpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_PWM1UpdEvtTrigPWMxUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->pwm2_upd_en, __LL_HRPWM_Slv_PWM2UpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_PWM2UpdEvtTrigPWMxUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->pwm3_upd_en, __LL_HRPWM_Slv_PWM3UpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_PWM3UpdEvtTrigPWMxUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->pwm4_upd_en, __LL_HRPWM_Slv_PWM4UpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_PWM4UpdEvtTrigPWMxUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->pwm5_upd_en, __LL_HRPWM_Slv_PWM5UpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_PWM5UpdEvtTrigPWMxUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->pwm6_upd_en, __LL_HRPWM_Slv_PWM6UpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_PWM6UpdEvtTrigPWMxUpd_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->pwm7_upd_en, __LL_HRPWM_Slv_PWM7UpdEvtTrigPWMxUpd_En(Instance, pwmx),
                  __LL_HRPWM_Slv_PWM7UpdEvtTrigPWMxUpd_Dis(Instance, pwmx));

    return LL_OK;
}

/**
  * @brief  HRPWM DAC Trigger Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx DAC Trigger to be Config, include Master PWM
  * @param  cfg DAC Trigger Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_DACTrigCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_DACTrigCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //DAC Trigger Config
    if (pwmx == HRPWM_MST_PWM) {
        return HRPWM_Mst_DACTrigCfg(Instance, cfg);
    } else {
        return HRPWM_Slv_DACTrigCfg(Instance, pwmx, cfg);
    }
}

/**
  * @brief  HRPWM Master PWM DAC Trigger Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Master PWM DAC Trigger Config Pointer
  * @return LL Status
  */
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Mst_DACTrigCfg(HRPWM_TypeDef *Instance, HRPWM_DACTrigCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Master PWM DAC Trigger Config
    __LL_HRPWM_Mst_DACSyncSrc_Set(Instance, cfg->sync_src);

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx DAC Trigger Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx DAC Trigger to be Config, not include Master PWM
  * @param  cfg Slave PWMx DAC Trigger Config Pointer
  * @return LL Status
  */
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Slv_DACTrigCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_DACTrigCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Slave PWMx DAC Trigger Config
    __LL_HRPWM_Slv_DACSyncSrc_Set(Instance, pwmx, cfg->sync_src);
    __LL_HRPWM_Slv_DACRstTrigSrc_Set(Instance, pwmx, cfg->rst_trig_src);
    __LL_HRPWM_Slv_DACStepTrigSrc_Set(Instance, pwmx, cfg->step_trig_src);
    LL_FUNC_ALTER(cfg->trig_en, __LL_HRPWM_Slv_DACRstStepTrig_En(Instance, pwmx), __LL_HRPWM_Slv_DACRstStepTrig_Dis(Instance, pwmx));

    return LL_OK;
}

/**
  * @brief  HRPWM System DMA Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which PWMx System DMA to be Config, include Master PWM
  * @param  cfg System DMA Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_SysDMACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_SysDMACfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //System DMA Config
    if (pwmx == HRPWM_MST_PWM) {
        return HRPWM_Mst_SysDMACfg(Instance, cfg);
    } else {
        return HRPWM_Slv_SysDMACfg(Instance, pwmx, cfg);
    }
}

/**
  * @brief  HRPWM Master PWM System DMA Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Master PWM System DMA Config Pointer
  * @return LL Status
  */
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Mst_SysDMACfg(HRPWM_TypeDef *Instance, HRPWM_SysDMACfgTypeDef *cfg)
{
    uint32_t count;
    uint32_t mask;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || 
        (cfg->write_upd_en == true && cfg->sys_dma_buf_addr == ((uint32_t)NULL))) {
        return LL_INVALID;
    }

    count = 0;
    mask = cfg->mst_reg_upd;

    if (cfg->write_upd_en == true) {
        while (mask) {
            mask &= (mask - 1);
            count++;
        }

        if ((count * sizeof(uint32_t)) > cfg->sys_dma_buf_size) {
            return LL_INVALID;
        }
    }

    //Master PWM System DMA Config
    if (cfg->write_upd_en == true) {
        // __LL_HRPWM_Mst_SysDMAAddr_Write(Instance, cfg->sys_dma_buf_addr);
        LL_FUNC_ALTER(cfg->mst_reg_upd != HRPWM_COMM_BURST_DMA_MST_REG_UPD_NONE, 
                __LL_HRPWM_Mst_SysDMAWriteUpd_Set(Instance, cfg->mst_reg_upd), 
                __LL_HRPWM_Mst_SysDMAWriteUpd_Reset(Instance, HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL));
    } else {
        __LL_HRPWM_Mst_SysDMAWriteUpd_Reset(Instance, HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL);
    }

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx System DMA Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx System DMA to be Config, not include Master PWM
  * @param  cfg Slave PWMx System DMA Config Pointer
  * @return LL Status
  */
__STATIC_FORCEINLINE LL_StatusETypeDef HRPWM_Slv_SysDMACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_SysDMACfgTypeDef *cfg)
{
    uint32_t count;
    uint32_t mask;

    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS || 
        (cfg->write_upd_en == true && cfg->sys_dma_buf_addr == ((uint32_t)NULL))) {
        return LL_INVALID;
    }

    count = 0;
    mask = cfg->slv_reg_upd;

    if (cfg->write_upd_en == true) {
        while (mask) {
            mask &= (mask - 1);
            count++;
        }

        if ((count * sizeof(uint32_t)) > cfg->sys_dma_buf_size) {
            return LL_INVALID;
        }
    }

    //Slave PWMx System DMA Config
    if (cfg->write_upd_en == true) {
        // __LL_HRPWM_Slv_SysDMAAddr_Write(Instance, pwmx, cfg->sys_dma_buf_addr); 
        LL_FUNC_ALTER(cfg->slv_reg_upd != HRPWM_COMM_BURST_DMA_SLV_REG_UPD_NONE, 
                    __LL_HRPWM_Slv_SysDMAWriteUpd_Set(Instance, pwmx, cfg->slv_reg_upd), 
                    __LL_HRPWM_Slv_SysDMAWriteUpd_Reset(Instance, pwmx, HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ALL));        
    } else {
        __LL_HRPWM_Slv_SysDMAWriteUpd_Reset(Instance, pwmx, HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ALL);
    }

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Roll-Over Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Timer Roll-Over to be Config, not include Master PWM
  * @param  cfg Slave PWMx Timer Roll-Over Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Slv_TmrRollOverCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_Slv_TmrRollOverCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Slave PWMx Timer Roll-Over Config
    __LL_HRPWM_SLV_CntrDirMode_Set(Instance, pwmx, cfg->dir_mode);
    __LL_HRPWM_Slv_CntrRollOverMode_Set(Instance, pwmx, cfg->cntr_ro_mode);
    __LL_HRPWM_Slv_OutputRollOverMode_Set(Instance, pwmx, cfg->out_ro_mode);
    __LL_HRPWM_Slv_ADCRollOverMode_Set(Instance, pwmx, cfg->adc_ro_mode);
    __LL_HRPWM_Slv_EvtRollOverMode_Set(Instance, pwmx, cfg->evt_ro_mode);
    __LL_HRPWM_Slv_FltRollOverMode_Set(Instance, pwmx, cfg->flt_ro_mode);

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Event Filter Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Timer Event Filter to be Config, not include Master PWM
  * @param  evtx External Event Number to be Config
  * @param  cfg Slave PWMx Timer Event Filter Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Slv_TmrEvtFilCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_ExtEvtNumETypeDef evtx, HRPWM_Slv_TmrEvtFilCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);
    assert_param(evtx < HRPWM_EXT_EVT_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS || evtx >= HRPWM_EXT_EVT_NUMS) {
        return LL_INVALID;
    }

    //Slave PWMx Timer Event Filter Config
    __LL_HRPWM_Slv_ExtEvtFil_Set(Instance, pwmx, evtx, cfg->fil);
    LL_FUNC_ALTER(cfg->blk_latch_en, __LL_HRPWM_Slv_ExtEvtBlkLatch_En(Instance, pwmx, evtx),
                  __LL_HRPWM_Slv_ExtEvtBlkLatch_Dis(Instance, pwmx, evtx));

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Timer Event A Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Timer Event A to be Config, not include Master PWM
  * @param  cfg Slave PWMx Timer Event A Config Pointer
  * @param  evt_fil Slave PWMx Timer Event Filter Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Slv_TmrEvtACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_Slv_TmrEvtACfgTypeDef *cfg, HRPWM_Slv_TmrEvtFilCfgTypeDef *evt_fil)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);
    assert_param(evt_fil != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS || evt_fil == NULL) {
        return LL_INVALID;
    }

    //Check Event A Enable or not
    if (!cfg->enable) {
        //Event A Counter Disable
        __LL_HRPWM_Slv_EvtACntr_Dis(Instance, pwmx);
        return LL_OK;
    }

    //Slave PWMx Timer Event A Config
    __LL_HRPWM_Slv_EvtASrc_Set(Instance, pwmx, cfg->src);
    __LL_HRPWM_Slv_EvtACntrThres_Set(Instance, pwmx, cfg->thres);
    __LL_HRPWM_Slv_EvtACntrRstMode_Set(Instance, pwmx, cfg->rst_mode);

    //Event Filter Config
    __LL_HRPWM_Slv_ExtEvtFil_Set(Instance, pwmx, cfg->src, evt_fil->fil);
    LL_FUNC_ALTER(evt_fil->blk_latch_en, __LL_HRPWM_Slv_ExtEvtBlkLatch_En(Instance, pwmx, cfg->src),
                  __LL_HRPWM_Slv_ExtEvtBlkLatch_Dis(Instance, pwmx, cfg->src));

    //Event A Counter Enable
    __LL_HRPWM_Slv_EvtACntr_En(Instance, pwmx);

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Output Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Output to be Config, not include Master PWM
  * @param  cfg Slave PWMx Output Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Slv_OutputCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_OutputCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Slave PWMx Output Config
    __LL_HRPWM_Slv_OutASetEvtEn_Cfg(Instance, pwmx, cfg->Aout_set_evt_msk);
    __LL_HRPWM_Slv_OutAClrEvtEn_Cfg(Instance, pwmx, cfg->Aout_clr_evt_msk);
    __LL_HRPWM_Slv_OutAPol_Set(Instance, pwmx, cfg->Aout_pol);
    __LL_HRPWM_Slv_OutAIdleLvl_Set(Instance, pwmx, cfg->Aout_idle_lvl);
    __LL_HRPWM_Slv_OutAFltLvl_Set(Instance, pwmx, cfg->Aout_flt_lvl);
    LL_FUNC_ALTER(cfg->Aidle_deadtime_en, __LL_HRPWM_Slv_OutAIdleDeadTime_En(Instance, pwmx),
                  __LL_HRPWM_Slv_OutAIdleDeadTime_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->Aburst_idle_en, __LL_HRPWM_Slv_OutABurstModeIdle_En(Instance, pwmx),
                  __LL_HRPWM_Slv_OutABurstModeIdle_Dis(Instance, pwmx));

    __LL_HRPWM_Slv_OutBSetEvtEn_Cfg(Instance, pwmx, cfg->Bout_set_evt_msk);
    __LL_HRPWM_Slv_OutBClrEvtEn_Cfg(Instance, pwmx, cfg->Bout_clr_evt_msk);
    __LL_HRPWM_Slv_OutBPol_Set(Instance, pwmx, cfg->Bout_pol);
    __LL_HRPWM_Slv_OutBIdleLvl_Set(Instance, pwmx, cfg->Bout_idle_lvl);
    __LL_HRPWM_Slv_OutBFltLvl_Set(Instance, pwmx, cfg->Bout_flt_lvl);
    LL_FUNC_ALTER(cfg->Bidle_deadtime_en, __LL_HRPWM_Slv_OutBIdleDeadTime_En(Instance, pwmx),
                  __LL_HRPWM_Slv_OutBIdleDeadTime_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->Bburst_idle_en, __LL_HRPWM_Slv_OutBBurstModeIdle_En(Instance, pwmx),
                  __LL_HRPWM_Slv_OutBBurstModeIdle_Dis(Instance, pwmx));

    __LL_HRPWM_Slv_DlyProtMech_Set(Instance, pwmx, cfg->dly_prot_mode);
    LL_FUNC_ALTER(cfg->dly_prot_en, __LL_HRPWM_Slv_DlyProt_En(Instance, pwmx), __LL_HRPWM_Slv_DlyProt_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->swap_en, __LL_HRPWM_Comm_PWMxOutputSwap_En(Instance, pwmx), __LL_HRPWM_Comm_PWMxOutputSwap_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->bal_idle_auto_rcvr_en, __LL_HRPWM_Slv_BalIdleAutoRcvr_En(Instance, pwmx),
                  __LL_HRPWM_Slv_BalIdleAutoRcvr_Dis(Instance, pwmx));

    for (uint8_t i = HRPWM_FLT_NUM_0; i < HRPWM_FLT_NUMS; i++) {
        LL_FUNC_ALTER(cfg->flt_en[i], __LL_HRPWM_Slv_FltX_En(Instance, pwmx, i), __LL_HRPWM_Slv_FltX_Dis(Instance, pwmx, i));
    }

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx DeadTime Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx DeadTime to be Config, not include Master PWM
  * @param  cfg Slave PWMx DeadTime Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Slv_DeadTimeCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_DeadTimeCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Check DeadTime Enable or not
    if (!cfg->enable) {
        __LL_HRPWM_Slv_DeadTime_Dis(Instance, pwmx);
        return LL_OK;
    }

    //Slave PWMx DeadTime Config
    __LL_HRPWM_Slv_RisingDtTime_Set(Instance, pwmx, cfg->rising_time);
    __LL_HRPWM_Slv_FallingDtTime_Set(Instance, pwmx, cfg->falling_time);
    __LL_HRPWM_Slv_RisingDtDir_Set(Instance, pwmx, cfg->rising_dir);
    __LL_HRPWM_Slv_FallingDtDir_Set(Instance, pwmx, cfg->falling_dir);

    //DeadTime Enable
    __LL_HRPWM_Slv_DeadTime_En(Instance, pwmx);

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Chopper Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Chopper to be Config, not include Master PWM
  * @param  cfg Slave PWMx Chopper Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Slv_ChopCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_ChopCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Slave PWMx Chopper Config
    __LL_HRPWM_Slv_ChopDuty_Set(Instance, pwmx, cfg->duty);
    __LL_HRPWM_Slv_ChopFreqDiv_Set(Instance, pwmx, cfg->freq_div);
    __LL_HRPWM_Slv_ChopStartPulseWidth_Set(Instance, pwmx, cfg->start_pulse_width);
    LL_FUNC_ALTER(cfg->Aout_chop_en, __LL_HRPWM_Slv_OutAChop_En(Instance, pwmx), __LL_HRPWM_Slv_OutAChop_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->Bout_chop_en, __LL_HRPWM_Slv_OutBChop_En(Instance, pwmx), __LL_HRPWM_Slv_OutBChop_Dis(Instance, pwmx));

    return LL_OK;
}

/**
  * @brief  HRPWM Slave PWMx Capture Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  pwmx Indicate which Slave PWMx Capture to be Config, not include Master PWM
  * @param  cfg Slave PWMx Capture Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Slv_CapCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_CapCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(pwmx < HRPWM_SLV_PWM_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || pwmx >= HRPWM_SLV_PWM_NUMS) {
        return LL_INVALID;
    }

    //Slave PWMx Capture Config
    __LL_HPRWM_Slv_CapAEvtEn_Cfg(Instance, pwmx, cfg->capA_trig_evt);
    __LL_HPRWM_Slv_CapBEvtEn_Cfg(Instance, pwmx, cfg->capB_trig_evt);
    LL_FUNC_ALTER(cfg->capA_int_en, __LL_HRPWM_Slv_CapA_INT_En(Instance, pwmx), __LL_HRPWM_Slv_CapA_INT_Dis(Instance, pwmx));
    LL_FUNC_ALTER(cfg->capB_int_en, __LL_HRPWM_Slv_CapB_INT_En(Instance, pwmx), __LL_HRPWM_Slv_CapB_INT_Dis(Instance, pwmx));

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_HRPWM))) {
        __LL_HRPWM_Slv_CapAMode_Set(Instance, pwmx, cfg->capA_mode);
        __LL_HRPWM_Slv_CapBMode_Set(Instance, pwmx, cfg->capB_mode);
    }

    return LL_OK;
}


/**
  * @brief  HRPWM Common External Event Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  evtx External Event Nubmer Which to be Config
  * @param  cfg Common External Event Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Comm_ExtEvtCfg(HRPWM_TypeDef *Instance, HRPWM_ExtEvtNumETypeDef evtx,
        HRPWM_Comm_ExtEvtCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(evtx < HRPWM_EXT_EVT_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || evtx >= HRPWM_EXT_EVT_NUMS) {
        return LL_INVALID;
    }

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) && (cfg->src >= HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT0)) {
        return LL_INVALID;
    }

    //Common External Event Config
    __LL_HRPWM_Comm_ExtEvtSampClkDiv_Set(Instance, cfg->samp_clk_div);

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        __LL_HRPWM_Comm_ExtEvtXInputSrcEx_Set(Instance, evtx, cfg->src);
    }
    else {
        __LL_HRPWM_Comm_ExtEvtXInputSrc_Set(Instance, evtx, cfg->src);
    }
    
    __LL_HRPWM_Comm_ExtEvtXInputPol_Set(Instance, evtx, cfg->pol);
    __LL_HRPWM_Comm_ExtEvtXFilLen_Set(Instance, evtx, cfg->fil_len);
    __LL_HRPWM_Comm_ExtEvtXInputActEdge_Set(Instance, evtx, cfg->act_edge);
    LL_FUNC_ALTER(cfg->fast_mode_en, __LL_HRPWM_Comm_ExtEvtXFastMode_En(Instance, evtx),
                  __LL_HRPWM_Comm_ExtEvtXFastMode_Dis(Instance, evtx));

    return LL_OK;
}

/**
  * @brief  HRPWM Common Fault Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  fltx Fault Number Which to be Config
  * @param  cfg Common Fault Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Comm_FltCfg(HRPWM_TypeDef *Instance, HRPWM_FltNumETypeDef fltx, HRPWM_Comm_FltCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(fltx < HRPWM_FLT_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || fltx >= HRPWM_FLT_NUMS) {
        return LL_INVALID;
    }

    //Common Fault Config
    __LL_HRPWM_Comm_FltSampClkDiv_Set(Instance, cfg->samp_clk_div);
    LL_FUNC_ALTER(cfg->sys_flt_int_en, __LL_HRPWM_Comm_SysFlt_INT_En(Instance), __LL_HRPWM_Comm_SysFlt_INT_Dis(Instance));
    LL_FUNC_ALTER(cfg->burst_prd_int_en, __LL_HRPWM_Comm_BurstModePrd_INT_En(Instance), __LL_HRPWM_Comm_BurstModePrd_INT_Dis(Instance));

    __LL_HRPWM_Comm_FltXInputSrc_Set(Instance, fltx, cfg->src);
    __LL_HRPWM_Comm_FltXInputPol_Set(Instance, fltx, cfg->pol);
    __LL_HRPWM_Comm_FltXFilLen_Set(Instance, fltx, cfg->fil_len);
    __LL_HRPWM_Comm_FltXCntrThres_Set(Instance, fltx, cfg->thres);
    __LL_HRPWM_Comm_FltXCntrRstMode_Set(Instance, fltx, cfg->rst_mode);
    LL_FUNC_ALTER(cfg->int_en, __LL_HRPWM_Comm_FltX_INT_En(Instance, fltx), __LL_HRPWM_Comm_FltX_INT_Dis(Instance, fltx));
    LL_FUNC_ALTER(cfg->input_en, __LL_HRPWM_Comm_FltXInput_En(Instance, fltx), __LL_HRPWM_Comm_FltXInput_Dis(Instance, fltx));

    __LL_HRPWM_Comm_FltXBlkSrc_Set(Instance, fltx, cfg->blk_src);
    LL_FUNC_ALTER(cfg->blk_en, __LL_HRPWM_Comm_FltXBlk_En(Instance, fltx), __LL_HRPWM_Comm_FltXBlk_Dis(Instance, fltx));

    return LL_OK;
}

/**
  * @brief  HRPWM Common ADC Trigger Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  adc_trigx ADC Trigger Number Which to be Config
  * @param  cfg Common ADC Trigger Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Comm_ADCTrigCfg(HRPWM_TypeDef *Instance, HRPWM_ADCTrigNumETypeDef adc_trigx,
        HRPWM_Comm_ADCTrigCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);
    assert_param(adc_trigx < HRPWM_ADC_TRIG_NUMS);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL || adc_trigx >= HRPWM_ADC_TRIG_NUMS) {
        return LL_INVALID;
    }

    //Common ADC Trigger Config
    switch (adc_trigx) {
        case HRPWM_ADC_TRIG_NUM_0:
            __LL_HRPWM_Comm_ADCTrig0EvtSrcEn_Cfg(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig0EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig0UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_1:
            __LL_HRPWM_Comm_ADCTrig1EvtSrcEn_Cfg(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig1EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig1UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_2:
            __LL_HRPWM_Comm_ADCTrig2EvtSrcEn_Cfg(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig2EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig2UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_3:
            __LL_HRPWM_Comm_ADCTrig3EvtSrcEn_Cfg(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig3EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig3UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_4:
            __LL_HRPWM_Comm_ADCTrig4EvtSrc_Set(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig4EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig4UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_5:
            __LL_HRPWM_Comm_ADCTrig5EvtSrc_Set(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig5EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig5UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_6:
            __LL_HRPWM_Comm_ADCTrig6EvtSrc_Set(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig6EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig6UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_7:
            __LL_HRPWM_Comm_ADCTrig7EvtSrc_Set(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig7EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig7UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_8:
            __LL_HRPWM_Comm_ADCTrig8EvtSrc_Set(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig8EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig8UpdSrc_Set(Instance, cfg->upd_src);
            break;

        case HRPWM_ADC_TRIG_NUM_9:
            __LL_HRPWM_Comm_ADCTrig9EvtSrc_Set(Instance, cfg->trig_evt);
            __LL_HRPWM_Comm_ADCTrig9EvtLen_Set(Instance, cfg->trig_len);
            __LL_HRPWM_Comm_ADCTrig9UpdSrc_Set(Instance, cfg->upd_src);
            break;

        default:
            LOG_E("Common ADC Tirgger Number-[%d] Invalid!\n", adc_trigx);
            return LL_INVALID;
    }

    __LL_HRPWM_Comm_ADCTrigXPostScaler_Set(Instance, adc_trigx, cfg->post_scaler);

    return LL_OK;
}

/**
  * @brief  HRPWM Common DLL Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Common DLL Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Comm_DLLCfg(HRPWM_TypeDef *Instance, HRPWM_Comm_DLLCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //DLL Config
    __LL_HRPWM_Comm_DLLCur_Set(Instance, cfg->cur);

    return LL_OK;
}

/**
  * @brief  HRPWM Common Burst Mode Config
  * @param  Instance Specifies HRPWM peripheral
  * @param  cfg Common Burst Mode Config Pointer
  * @return LL Status
  */
static LL_StatusETypeDef HRPWM_Comm_BurstModeCfg(HRPWM_TypeDef *Instance, HRPWM_Comm_BurstModeCfgTypeDef *cfg)
{
    //Assert param
    assert_param(IS_HRPWM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_HRPWM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //Check Burst Mode Enable or not
    if (!cfg->enable) {
        __LL_HRPWM_Comm_BurstMode_Dis(Instance);
        return LL_OK;
    }

    //Burst Mode Common Config
    __LL_HRPWM_Comm_BurstWorkMode_Set(Instance, cfg->work_mode);
    __LL_HRPWM_Comm_BurstModePrd_Set(Instance, cfg->cntr_prd);
    __LL_HRPWM_Comm_BurstModeCmpVal_Set(Instance, cfg->cmp_val);
    __LL_HRPWM_Comm_BurstModeClkSrc_Set(Instance, cfg->clk_src);
    __LL_HRPWM_Comm_BurstModeClkPrescl_Set(Instance, cfg->clk_prescl);
    __LL_HRPWM_Comm_BurstModeTrigEvtEn_Cfg(Instance, cfg->trig_evt);
    LL_FUNC_ALTER(cfg->pre_load_en, __LL_HRPWM_Comm_BurstModePreload_En(Instance), __LL_HRPWM_Comm_BurstModePreload_Dis(Instance));

    //Burst DMA Register Update Config
    __LL_HRPWM_Comm_BurstDMAAddr_Set(Instance, cfg->reg_upd_addr);
    __LL_HRPWM_Comm_BurstDMAMstPWMRegUpd_Set(Instance, cfg->mst_reg_upd);

    for (uint8_t pwmx = 0; pwmx < HRPWM_SLV_PWM_NUMS; pwmx++) {
        __LL_HRPWM_Comm_BurstDMASlvPWMxRegUpd_Set(Instance, pwmx, cfg->slv_reg_upd[pwmx]);
    }

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_HRPWM))) {
        __LL_HRPWM_Comm_BurstModeTrigMode_Set(Instance, cfg->trig_mode);
        __LL_HRPWM_Comm_BurstDMAWriteAddr_Set(Instance, cfg->reg_write_addr);
        LL_FUNC_ALTER(cfg->mst_burst_dma_dis, __LL_HRPWM_Mst_BurstDMADis_Assert(Instance), __LL_HRPWM_Mst_BurstDMADis_Release(Instance));

        for (uint8_t pwmx = 0; pwmx < HRPWM_SLV_PWM_NUMS; pwmx++) {
            LL_FUNC_ALTER(cfg->slv_burst_dma_dis[pwmx], __LL_HRPWM_Slv_PWMxBurstDMADis_Assert(Instance, pwmx), 
                          __LL_HRPWM_Slv_PWMxBurstDMADis_Release(Instance, pwmx));
        }
    }

    //Burst Mode Enable
    __LL_HRPWM_Comm_BurstMode_En(Instance);

    return LL_OK;
}

/**
  * @}
  */


#endif  /* LL_HRPWM_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

