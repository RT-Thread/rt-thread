/**
  ******************************************************************************
  * @file    tae32f53xx_ll_can.c
  * @author  MCD Application Team
  * @brief   CAN LL Module Driver.
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
#include "tae32f53xx_ll.h"


#define DBG_TAG             "CAN LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup CAN_LL CAN LL
  * @brief    CAN LL Module Driver
  * @{
  */

#ifdef LL_CAN_MODULE_ENABLED

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup CAN_LL_Private_Functions
  * @{
  */
LL_StatusETypeDef LL_CAN_AcceptFilCfg(CAN_TypeDef *Instance, CAN_AcceptFilCfgTypeDef *fil_cfg);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup CAN_LL_Exported_Functions CAN LL Exported Functions
  * @brief    CAN LL Exported Functions
  * @{
  */

/** @defgroup CAN_LL_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and de-initialization functions
  * @{
  */

/**
  * @brief  CAN LL Init
  * @param  Instance Specifies CAN peripheral
  * @param  user_cfg user config pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_CAN_Init(CAN_TypeDef *Instance, CAN_UserCfgTypeDef *user_cfg)
{
    assert_param(Instance);
    assert_param(user_cfg);

    /* Init the low level hardware eg. Clock, NVIC */
    LL_CAN_MspInit(Instance);

    /* Set reset status to config some register which can config in reset status only */
    __LL_CAN_Reset_Set(Instance);

    //Baudrate config
    assert_param(user_cfg->baudrate);
    __LL_CAN_SS_Prescaler_Set(Instance, (LL_SYSCTRL_AHBClkGet() / 10 / user_cfg->baudrate - 1));

    //Bit timing config
    __LL_CAN_SS_BitTimingSeg1_Set(Instance, user_cfg->bit_timing_seg1);
    __LL_CAN_SS_BitTimingSeg2_Set(Instance, user_cfg->bit_timing_seg2);
    __LL_CAN_SS_SyncJumpWidth_Set(Instance, user_cfg->bit_timing_sjw);

    //Acceptance filter config
    for (uint8_t i = 0; i < user_cfg->accept_fil_cfg_num; i++) {
        LL_CAN_AcceptFilCfg(Instance, (CAN_AcceptFilCfgTypeDef *)&user_cfg->accept_fil_cfg_ptr[i]);
    }

    /*Clear reset status to config other register */
    __LL_CAN_Reset_Clr(Instance);

    //RX buffer almost full and error warning limit set
    __LL_CAN_RxBufAlmostFullLimit_Set(Instance, user_cfg->rx_almost_full_limit);
    __LL_CAN_ErrWarnLimit_Set(Instance, user_cfg->err_limit);

    return LL_OK;
}

/**
  * @brief  CAN LL DeInit
  * @param  Instance Specifies CAN peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_CAN_DeInit(CAN_TypeDef *Instance)
{
    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_CAN_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the CAN MSP.
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_MspInit(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the CAN MSP
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_MspDeInit(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */

/** @defgroup CAN_LL_Exported_Functions_Group2 Send data functions
  * @brief    Send data functions
  * @{
  */

/**
  * @brief  CAN LL send standard primary transmit buffer
  * @param  Instance Specifies CAN peripheral
  * @param  buf_fmt buffer format pointer
  * @param  buf buffer pointer
  * @return success send length in byte
  */
uint32_t LL_CAN_SendStandard_PTB(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf)
{
    uint32_t i, j;

    assert_param(Instance);
    assert_param(buf_fmt);
    assert_param(buf);

    //TX buffer select PTB
    __LL_CAN_TxBufSel_PTB(Instance);

    //Write buffer format data to TX buffer
    Instance->TXBUF[0] = *((uint32_t *)buf_fmt);
    Instance->TXBUF[1] = *(((uint32_t *)buf_fmt) + 1);

    //Write data to TX buffer
    for (i = 0, j = 0; i < buf_fmt->data_len_code; i += 4, j++) {
        Instance->TXBUF[2 + j] = *buf++;
    }

    //TX primary enable
    __LL_CAN_TxPriEn_Set(Instance);

    //Wait TX complete
    while (__LL_CAN_TxPriEn_Get(Instance));

    return buf_fmt->data_len_code;
}

/**
  * @brief  CAN LL send standard secondary transmit buffer
  * @param  Instance Specifies CAN peripheral
  * @param  buf_fmt buffer format pointer
  * @param  buf buffer pointer
  * @return success send length in byte
  */
uint32_t LL_CAN_SendStandard_STB(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf)
{
    uint32_t i, j;

    assert_param(Instance);
    assert_param(buf_fmt);
    assert_param(buf);

    //TX buffer select STB
    __LL_CAN_TxBufSel_STB(Instance);

    //Write buffer format data to TX buffer
    Instance->TXBUF[0] = *((uint32_t *)buf_fmt);
    Instance->TXBUF[1] = *(((uint32_t *)buf_fmt) + 1);

    //Write data to TX buffer
    for (i = 0, j = 0; i < buf_fmt->data_len_code; i += 4, j++) {
        Instance->TXBUF[2 + j] = *buf++;
    }

    //TX buffer Secondary next
    __LL_CAN_TxSecNext_Set(Instance);

    //TX secondary send one start
    __LL_CAN_TxSecOne_Set(Instance);

    //Wait TX complete
    while (__LL_CAN_TxSecOne_Get(Instance));

    return buf_fmt->data_len_code;
}

/**
  * @brief  CAN LL send a multi-package standard secondary transmit buffer
  * @param  Instance Specifies CAN peripheral
  * @param  buf_fmt buffer format pointer
  * @param  buf buffer pointer
  * @param  send_cnt send packets count
  * @return success send length in byte
  */
uint32_t LL_CAN_SendStandard_STB_Multi(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt,
                                       uint32_t *buf, uint32_t send_cnt)
{
    uint32_t i, j, cnt;

    assert_param(Instance);
    assert_param(buf_fmt);
    assert_param(buf);

    //TX buffer select STB
    __LL_CAN_TxBufSel_STB(Instance);

    for (cnt = 0; cnt < send_cnt; cnt++) {
        //Write buffer format data to TX buffer
        Instance->TXBUF[0] = *((uint32_t *)buf_fmt);
        Instance->TXBUF[1] = *(((uint32_t *)buf_fmt) + 1);

        //Write data to TX buffer
        for (i = 0, j = 0; i < buf_fmt->data_len_code; i += 4, j++) {
            Instance->TXBUF[2 + j] = *buf++;
        }

        //TX buffer Secondary next
        __LL_CAN_TxSecNext_Set(Instance);

        //TX buffer Secondary full and send
        if (__LL_CAN_IsTxSecBufFull(Instance)) {
            //TX secondary send all start
            __LL_CAN_TxSecAll_Set(Instance);

            //Wait TX complete
            while (__LL_CAN_TxSecAll_Get(Instance));
        }
    }

    //TX secondary send all start
    __LL_CAN_TxSecAll_Set(Instance);

    //Wait TX complete
    while (__LL_CAN_TxSecAll_Get(Instance));

    return buf_fmt->data_len_code * send_cnt;
}

/**
  * @}
  */

/** @defgroup CAN_LL_Exported_Functions_Interrupt CAN Interrupt handler and call back
  * @brief    CAN Interrupt handler and call back
  * @{
  */

/**
  * @brief  CAN IRQ Handler
  * @param  Instance Specifies CAN peripheral
  * @note   All interrupt pending will be reset immediately after a read access
  * @return None
  */
void LL_CAN_IRQHandler(CAN_TypeDef *Instance)
{
    uint8_t txrx_int_sta = __LL_CAN_IntSta_Get(Instance);
    uint8_t err_int_sta  = __LL_CAN_ErrIntSta_Get(Instance);

    if (txrx_int_sta & CAN_RX_INT_STA_Msk) {
        LL_CAN_RxCallback(Instance);
    }

    if (txrx_int_sta & CAN_RX_BUF_OVER_INT_STA_Msk) {
        LL_CAN_RxOverCallback(Instance);
    }

    if (txrx_int_sta & CAN_RX_BUF_FULL_INT_STA_Msk) {
        LL_CAN_RxFullCallback(Instance);
    }

    if (txrx_int_sta & CAN_RX_BUF_ALMOST_FULL_INT_STA_Msk) {
        LL_CAN_RxAlmostFullCallback(Instance);
    }

    if (txrx_int_sta & CAN_TX_PRI_INT_STA_Msk) {
        LL_CAN_TxPriCallback(Instance);
    }

    if (txrx_int_sta & CAN_TX_SEC_INT_STA_Msk) {
        LL_CAN_TxSecCallback(Instance);
    }

    if (txrx_int_sta & CAN_ERR_INT_STA_Msk) {
        LL_CAN_ErrCallback(Instance);
    }

    if (txrx_int_sta & CAN_ABORT_INT_STA_Msk) {
        LL_CAN_AbortCallback(Instance);
    }


    if (err_int_sta & CAN_ERR_PASS_INT_STA_Msk) {
        LL_CAN_ErrPassiveCallback(Instance);
    }

    if (err_int_sta & CAN_ARB_LOST_INT_STA_Msk) {
        LL_CAN_ArbLostCallback(Instance);
    }

    if (err_int_sta & CAN_BUS_ERR_INT_STA_Msk) {
        LL_CAN_BusErrCallback(Instance);
    }
}


/**
  * @brief  CAN RX interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_RxCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_RxCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN RX over interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_RxOverCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_RxOverCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN RX full interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_RxFullCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_RxFullCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN RX almost full interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_RxAlmostFullCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_RxAlmostFullCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN TX primary interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_TxPriCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_TxPriCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN TX secondary interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_TxSecCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_TxSecCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN error interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_ErrCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_ErrCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN abort interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_AbortCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_AbortCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN error passive interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_ErrPassiveCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_ErrPassiveCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN arbitration lost interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_ArbLostCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_ArbLostCallback could be implemented in the user file
     */
}

/**
  * @brief  CAN bus error interrupt callback
  * @param  Instance Specifies CAN peripheral
  * @return None
  */
__WEAK void LL_CAN_BusErrCallback(CAN_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CAN_BusErrCallback could be implemented in the user file
     */
}


/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup CAN_LL_Private_Functions CAN LL Private Functions
  * @brief    CAN LL Private Functions
  * @{
  */

/**
  * @brief  CAN LL acceptance filter config
  * @param  Instance Specifies CAN peripheral
  * @param  fil_cfg filter config pointer
  * @return Config result
  */
LL_StatusETypeDef LL_CAN_AcceptFilCfg(CAN_TypeDef *Instance, CAN_AcceptFilCfgTypeDef *fil_cfg)
{
    assert_param(Instance);
    assert_param(fil_cfg);

    //Check in reset status or not
    if (!__LL_CAN_ResetSta_Get(Instance)) {
        LOG_E("Acceptance filter register can config in reset status only!\n");
        return LL_ERROR;
    }

    //CAN acceptance filter Code and Mask config
    __LL_CAN_AcceptFilAddr_Set(Instance, fil_cfg->slot);
    __LL_CAN_AcceptFilContentSel_Code(Instance);
    __LL_CAN_AcceptFilCodeOrMaskVal_Set(Instance, fil_cfg->code_val);
    __LL_CAN_AcceptFilContentSel_Mask(Instance);
    __LL_CAN_AcceptFilCodeOrMaskVal_Set(Instance, fil_cfg->mask_val);

    //CAN acceptance filter enable
    __LL_CAN_AcceptFil_En(Instance, ((uint8_t)fil_cfg->slot));

    return LL_OK;
}


/**
  * @}
  */

#endif  /* LL_CAN_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

