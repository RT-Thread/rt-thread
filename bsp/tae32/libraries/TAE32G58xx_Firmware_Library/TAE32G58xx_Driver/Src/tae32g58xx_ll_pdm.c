/**
  ******************************************************************************
  * @file    tae32g58xx_ll_pdm.c
  * @author  MCD Application Team
  * @brief   PDM LL module driver
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


#define DBG_TAG             "PDM LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup PDM_LL PDM LL
  * @brief    PDM LL module driver
  * @{
  */

#ifdef LL_PDM_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/** @defgroup PDM_LL_Private_Variables PDM LL Private Variables
  * @brief    PDM LL Private Variables
  * @{
  */

/**
  * @brief Default PDM LL Config
  */
static const PDM_LLCfgypeDef pdm_ll_cfg_def = {
    .mst_rx_delay = 0,              //0~7
    .slv_clk_timeout = 0x3FFF,      //0~0x3ffff

    .fifo_full_thres = 1,           //1~8
    .fifo_w_sync_en = false,
    .fifo_rst_sync_en = false,
    .fifo_full_clr_sync_en = true,
};

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup PDM_LL_Private_Functions PDM LL Private Functions
  * @brief    PDM LL Private Functions
  * @{
  */
static LL_StatusETypeDef PDM_DatFil_Init(PDM_TypeDef *Instance, PDM_DatFil_InitTypeDef *init);
static LL_StatusETypeDef PDM_CmpFil_Init(PDM_TypeDef *Instance, PDM_CmpFil_InitTypeDef *init);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup PDM_LL_Exported_Functions PDM LL Exported Functions
  * @brief    PDM LL Exported Functions
  * @{
  */

/** @defgroup PDM_LL_Exported_Functions_Group1 PDM Init and DeInit Functions
  * @brief    PDM Init and DeInit Functions
  * @{
  */

/**
  * @brief  PDM LL Init
  * @param  Instance Specifies PDM peripheral
  * @param  init PDM Init Pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_PDM_Init(PDM_TypeDef *Instance, PDM_InitTypeDef *init)
{
    PDM_LLCfgypeDef *ll_cfg;

    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_PDM_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    if (!init->dat_fil_init.enable && !init->cmp_fil_init.enable) {
        LOG_E("Data and Comparator Filter both not Enable.\n");
        return LL_ERROR;
    }

    //LL config pointer config
    LL_FUNC_ALTER(init->ll_cfg == NULL, ll_cfg = (PDM_LLCfgypeDef *)&pdm_ll_cfg_def, ll_cfg = init->ll_cfg);

    /* Init the low level hardware eg. Clock, NVIC */
    LL_PDM_MspInit(Instance);

    //Module disable and FIFO reset
    __LL_PDM_Dis(Instance);
    __LL_PDM_FIFO_Rst(Instance);

    //LL Config
    __LL_PDM_Mst_SpiRxDelay_Set(Instance, ll_cfg->mst_rx_delay);
    __LL_PDM_Slv_ClkRolloverTimeout_Set(Instance, ll_cfg->slv_clk_timeout);
    //Data Filter LL Config
    __LL_PDM_FIFOFullThres_Set(Instance, ll_cfg->fifo_full_thres);
    LL_FUNC_ALTER(ll_cfg->fifo_w_sync_en, __LL_PDM_DatFil_WTSYNFLG_CtrlFIFOWrite_En(Instance),
                  __LL_PDM_DatFil_WTSYNFLG_CtrlFIFOWrite_Dis(Instance));
    LL_FUNC_ALTER(ll_cfg->fifo_rst_sync_en, __LL_PDM_DatFil_SDSYNC_RstFIFO_En(Instance), __LL_PDM_DatFil_SDSYNC_RstFIFO_Dis(Instance));
    LL_FUNC_ALTER(ll_cfg->fifo_full_clr_sync_en, __LL_PDM_DatFil_FIFOFullIntClrWTSYNFLG_En(Instance),
                  __LL_PDM_DatFil_FIFOFullIntClrWTSYNFLG_Dis(Instance));

    //PDM Common Config
    LL_FUNC_ALTER(init->dma_en, LL_PDM_DMA_En(Instance), LL_PDM_DMA_Dis(Instance));
    __LL_PDM_Role_Set(Instance, init->role);
    __LL_PDM_InputMode_Set(Instance, init->input_mode);

    if (init->input_mode == PDM_INPUT_MODE_HW) {
        if (init->role == PDM_ROLE_MASTER) {
            assert_param(init->mst_baudrate);

            if (!init->mst_baudrate) {
                return LL_INVALID;
            }

            __LL_PDM_SerialClkPol_Set(Instance, init->mst_sclk_pol);
            __LL_PDM_BaudRate_Set(Instance, LL_RCU_APB1ClkGet() / init->mst_baudrate / 2);
        } else {
            __LL_PDM_Slv_SampleMode_Set(Instance, init->slv_sample_edge);
        }
    }

    //PDM Data Filter Config
    PDM_DatFil_Init(Instance, &init->dat_fil_init);

    //PDM Comparator Filter Config
    PDM_CmpFil_Init(Instance, &init->cmp_fil_init);

    return LL_OK;
}

/**
  * @brief  PDM LL DeInit
  * @param  Instance Specifies PDM peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_PDM_DeInit(PDM_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));

    if (!IS_PDM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //Module disable
    __LL_PDM_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_PDM_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the PDM MSP
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_MspInit(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the PDM MSP
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_MspDeInit(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup PDM_LL_Exported_Functions_Group2 PDM Peripheral Control Functions
  * @brief    PDM Peripheral Control Functions
  * @{
  */

/**
  * @brief  PDM LL Data Filter Reconfig on runtime
  * @param  Instance Specifies PDM peripheral
  * @param  cfg PDM Data Filter Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_PDM_DatFil_Cfg(PDM_TypeDef *Instance, PDM_DatFil_InitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_PDM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return PDM_DatFil_Init(Instance, cfg);
}

/**
  * @brief  PDM LL Comparator Filter Reconfig on runtime
  * @param  Instance Specifies PDM peripheral
  * @param  cfg PDM Comparator Filter Config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_PDM_CmpFil_Cfg(PDM_TypeDef *Instance, PDM_CmpFil_InitTypeDef *cfg)
{
    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_PDM_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    return PDM_CmpFil_Init(Instance, cfg);
}

/**
  * @}
  */


/** @defgroup PDM_LL_Exported_Functions_Group3 PDM Operation Functions
  * @brief    PDM Operation Functions
  * @{
  */

/**
  * @brief  PDM LL Enable
  * @param  Instance Specifies PDM peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_PDM_En(PDM_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));

    if (!IS_PDM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //PDM Enable
    __LL_PDM_En(Instance);

    return LL_OK;
}

/**
  * @brief  PDM LL Disable
  * @param  Instance Specifies PDM peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_PDM_Dis(PDM_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));

    if (!IS_PDM_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //PDM Enable
    __LL_PDM_Dis(Instance);

    return LL_OK;
}

/**
  * @brief  PDM LL Software Input Data Write
  * @param  Instance Specifies PDM peripheral
  * @param  buf Write Data Buffer
  * @param  size Write Data Size in uint16_t(half word) unit
  * @return Success write size in uint16_t(half word) unit
  */
uint32_t LL_PDM_SwInputDat_Write(PDM_TypeDef *Instance, uint16_t *buf, uint32_t size)
{
    uint32_t w_cnt = size;

    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_PDM_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return 0;
    }

    while (w_cnt--) {
        __LL_PDM_SwInputDat_Write(Instance, *buf++);
    }

    return size;
}

/**
  * @}
  */


/** @defgroup PDM_LL_Exported_Functions_Interrupt PDM Interrupt Handler and Callback
  * @brief    PDM Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  PDM LL IRQ Handler
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
void LL_PDM_IRQHandler(PDM_TypeDef *Instance)
{
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));

    if (!IS_PDM_ALL_INSTANCE(Instance)) {
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_PDM_AllIntEn_Get(Instance);
    int_pending = __LL_PDM_AllIntPnd_Get(Instance);


    //Data Filter FIFO Underflow Interrput Handler
    if ((int_en & PDM0_IER_FIUIE_Msk) && (int_pending & PDM0_ISR_FIUINTR_Msk)) {
        //Clear Interrupt Pending
        __LL_PDM_DatFil_FIFOUnderflowIntPnd_Clr(Instance);

        //Callback
        LL_PDM_DatFil_FIFOUnderflowCallback(Instance);
    }

    //PDM Slave Clock Timeout Interrupt Handler
    if ((int_en & PDM0_IER_CTIE_Msk) && (int_pending & PDM0_ISR_CTOINTR_Msk)) {
        //Clear Interrupt Pending
        __LL_PDM_Slv_ClkTimeoutIntPnd_Clr(Instance);

        //Callback
        LL_PDM_Slv_ClkTimeOutCallback(Instance);
    }

    //Data Filter FIFO Full Interrupt Handler
    if ((int_en & PDM0_IER_FFIE_Msk) && (int_pending & PDM0_ISR_FIFINTR_Msk)) {
        //interrupt pending auto clear

        //Callback
        LL_PDM_DatFil_FIFOFullCallback(Instance);
    }

    //Data Filter FIFO Overflow Interrput Handler
    if ((int_en & PDM0_IER_FIOIE_Msk) && (int_pending & PDM0_ISR_FIOINTR_Msk)) {
        //Clear Interrupt Pending
        __LL_PDM_DatFil_FIFOOverflowIntPnd_Clr(Instance);

        //Callback
        LL_PDM_DatFil_FIFOOverflowCallback(Instance);
    }

    //Comparator Filter Data Overflow Interrupt Handler
    if ((int_en & PDM0_IER_DOFIE_Msk) && (int_pending & PDM0_ISR_DOINTR_Msk)) {
        //Clear Interrupt Pending
        __LL_PDM_CmpFil_DatOverflowIntPnd_Clr(Instance);

        //Callback
        LL_PDM_CmpFil_DatOverFlowCallback(Instance);
    }

    //Comparator Filter Data Finish Interrupt Handler
    if ((int_en & PDM0_IER_DFIE_Msk) && (int_pending & PDM0_ISR_DFINTR_Msk)) {
        //Clear Interrupt Pending
        __LL_PDM_CmpFil_DatFinishIntPnd_Clr(Instance);

        //Callback
        LL_PDM_CmpFil_DatFinishCallback(Instance);
    }

    //Comparator Filter Low Level Interrupt Handler
    if ((int_en & PDM0_IER_LLIE_Msk) && (int_pending & PDM0_ISR_LLINTR_Msk)) {
        //Clear Interrupt Pending
        __LL_PDM_CmpFil_LowLvlIntPnd_Clr(Instance);

        //Callback
        LL_PDM_CmpFil_LowLvlCallback(Instance);
    }

    //Comparator Filter High Level Interrupt Handler
    if ((int_en & PDM0_IER_HLIE_Msk) && (int_pending & PDM0_ISR_HLINTR_Msk)) {
        //Clear Interrupt Pending
        __LL_PDM_CmpFil_HighLvlIntPnd_Clr(Instance);

        //Callback
        LL_PDM_CmpFil_HighLvlCallback(Instance);
    }
}

/**
  * @brief  PDM LL Data Filter FIFO Underflow Interrupt Callback Function
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_DatFil_FIFOUnderflowCallback(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_DatFil_FIFOUnderflowCallback could be implemented in the user file
     */
}

/**
  * @brief  PDM LL Slave Clock Timeout Interrupt Callback Function
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_Slv_ClkTimeOutCallback(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_Slv_ClkTimeOutCallback could be implemented in the user file
     */
}

/**
  * @brief  PDM LL Data Filter FIFO Full Interrupt Callback Function
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_DatFil_FIFOFullCallback(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_DatFil_FIFOFullCallback could be implemented in the user file
     */
}

/**
  * @brief  PDM LL Data Filter FIFO Overflow Interrupt Callback Function
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_DatFil_FIFOOverflowCallback(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_DatFil_FIFOOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  PDM LL Comparator Filter Data Overflow Interrupt Callback Function
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_CmpFil_DatOverFlowCallback(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_CmpFil_DatOverFlowCallback could be implemented in the user file
     */
}

/**
  * @brief  PDM LL Comparator Filter Data Finish Interrupt Callback Function
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_CmpFil_DatFinishCallback(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_CmpFil_DatFinishCallback could be implemented in the user file
     */
}

/**
  * @brief  PDM LL Comparator Filter Low Level Interrupt Callback Function
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_CmpFil_LowLvlCallback(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_CmpFil_LowLvlCallback could be implemented in the user file
     */
}

/**
  * @brief  PDM LL Comparator Filter High Level Interrupt Callback Function
  * @param  Instance Specifies PDM peripheral
  * @return None
  */
__WEAK void LL_PDM_CmpFil_HighLvlCallback(PDM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_PDM_CmpFil_HighLvlCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup PDM_LL_Private_Functions
  * @{
  */

/**
  * @brief  PDM Data Filter Init
  * @param  Instance Specifies PDM peripheral
  * @param  init PDM Data Filter Init pointer
  * @return LL Status
  */
static LL_StatusETypeDef PDM_DatFil_Init(PDM_TypeDef *Instance, PDM_DatFil_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_PDM_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //Data Filter Enable Config
    if (!init->enable) {
        __LL_PDM_DatFil_Dis(Instance);
        return LL_OK;
    }

    __LL_PDM_DatFil_En(Instance);

    //Data Filter Bypass Config
    if (init->bypass_en) {
        __LL_PDM_DatFil_Bypass_En(Instance);
        return LL_OK;
    }

    __LL_PDM_DatFil_Bypass_Dis(Instance);

    //Filter Structure/OSR Config
    assert_param(__LL_PDM_DatFil_IsOSR_Valid(init->over_sample_rate));

    if (!__LL_PDM_DatFil_IsOSR_Valid(init->over_sample_rate)) {
        return LL_INVALID;
    }

    __LL_PDM_DatFil_OverSampleRate_Set(Instance, init->over_sample_rate);
    __LL_PDM_DatFil_Structure_Set(Instance, init->fil_stru);

    //Output Data Length Config
    __LL_PDM_DatFil_OutputDatLen_Set(Instance, init->dat_len);

    if (init->dat_len == PDM_DAT_FIL_DAT_LEN_16BIT) {
        assert_param(__LL_PDM_DatFil_IsShiftValid(init->shift_bit));

        if (!__LL_PDM_DatFil_IsShiftValid(init->shift_bit)) {
            return LL_INVALID;
        }

        __LL_PDM_DatFil_Shift_Set(Instance, init->shift_bit);
    }

    //SDSYNC Config
    if (init->sdsync_en) {
        __LL_PDM_DatFil_SDSYNC_En(Instance);
        __LL_PDM_DatFil_SDSYNC_Evt_Sel(Instance, init->sync_evt);
    } else {
        __LL_PDM_DatFil_SDSYNC_Dis(Instance);
    }

    return LL_OK;
}

/**
  * @brief  PDM Comparator Filter Init
  * @param  Instance Specifies PDM peripheral
  * @param  init PDM Comparator Filter Init pointer
  * @return LL Status
  */
static LL_StatusETypeDef PDM_CmpFil_Init(PDM_TypeDef *Instance, PDM_CmpFil_InitTypeDef *init)
{
    //Assert param
    assert_param(IS_PDM_ALL_INSTANCE(Instance));
    assert_param(init != NULL);

    if (!IS_PDM_ALL_INSTANCE(Instance) || init == NULL) {
        return LL_INVALID;
    }

    //Comparator Filter Enable Config
    if (!init->enable) {
        __LL_PDM_CmpFil_Dis(Instance);
        return LL_OK;
    }

    __LL_PDM_CmpFil_En(Instance);

    //Comparator Filter Bypass Config
    if (init->bypass_en) {
        __LL_PDM_CmpFil_Bypass_En(Instance);
        return LL_OK;
    }

    __LL_PDM_CmpFil_Bypass_Dis(Instance);

    //Common Config
    assert_param(__LL_PDM_CmpFil_IsOSR_Valid(init->over_sample_rate));

    if (!__LL_PDM_CmpFil_IsOSR_Valid(init->over_sample_rate)) {
        return LL_INVALID;
    }

    __LL_PDM_CmpFil_OverSampleRate_Set(Instance, init->over_sample_rate);
    __LL_PDM_CmpFil_Structure_Set(Instance, init->fil_stru);
    __LL_PDM_CmpFil_Output_Sel(Instance, init->output);

    //High/Low Level Threshold Config
    __LL_PDM_CmpFil_HighLvlThres_Set(Instance, init->high_lvl_thres);
    __LL_PDM_CmpFil_LowLvlThres_Set(Instance, init->low_lvl_thres);

    return LL_OK;
}

/**
  * @}
  */


#endif  /* LL_PDM_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

