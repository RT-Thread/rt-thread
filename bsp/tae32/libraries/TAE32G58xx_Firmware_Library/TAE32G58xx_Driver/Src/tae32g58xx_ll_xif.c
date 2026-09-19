/**
  ******************************************************************************
  * @file    tae32g58xx_ll_xif.c
  * @author  MCD Application Team
  * @brief   XIF LL module driver
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
#include <string.h>


#define DBG_TAG             "XIF LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup XIF_LL XIF LL
  * @brief    XIF LL module driver
  * @{
  */

#ifdef LL_XIF_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/** @defgroup XIF_LL_Private_Types XIF LL Private Types
  * @brief    XIF LL Private Types
  * @{
  */

/**
  * @brief XIF IRQ callback function type definition
  */
typedef void (*XIF_LLIRQCallback)(XIF_TypeDef *Instance);

/**
  * @brief  XIF Transmission definition
  */
typedef struct __XIF_TransTypeDef {
    uint16_t *buf;                  /*!< XIF Transmission Buffer Pointer    */
    uint32_t size;                  /*!< XIF Transmission Buffer Size       */
    uint32_t cnt;                   /*!< XIF Transmission Counter           */
    XIF_LLIRQCallback isr;          /*!< Interrupt Service Routine          */
    XIF_StateETypeDef state;        /*!< XIF Transmission State             */
#ifdef LL_DMA_MODULE_ENABLED
    DMA_ChannelETypeDef dma_ch;     /*!< XIF Transmission DMA Channel       */
#endif
} XIF_TransTypeDef;

/**
  * @brief XIF handle Structure definition
  */
typedef struct __XIF_HandleTypeDef {
    volatile XIF_TransTypeDef tx_ctrl;      /*!< XIF Transmission Tx Control    */
    volatile XIF_TransTypeDef rx_ctrl;      /*!< XIF Transmission Rx Control    */

    XIF_UserCallbackTypeDef user_callback;  /*!< User Callback                  */
} XIF_HandleTypeDef;

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup XIF_LL_Private_Variables XIF LL Private Variables
  * @brief    XIF LL Private Variables
  * @{
  */

/**
  * @brief Default XIF LL Config
  */
static const XIF_LLCfgTypeDef xif_ll_cfg_def = {
    .rx_fifo_full_thres  = 1,       // 1~8
    .busy_timeout = 0xffff,         // 0~0xffff
    .dly_chain = XIF_DLY_CHAIN_NONE,
    .tx_fifo_empty_thres = 1,       // 1~8
};

/**
  * @brief XIF Handle global variable
  */
static XIF_HandleTypeDef xif_hdl_global[XIF_INSTANCE_NUMS];

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup XIF_LL_Private_Functions XIF LL Private Functions
  * @brief    XIF LL Private Functions
  * @{
  */
static XIF_HandleTypeDef *XIF_Handle_Get(XIF_TypeDef *Instance);

static void XIF_Tx_ISR(XIF_TypeDef *Instance);
static void XIF_Rx_ISR(XIF_TypeDef *Instance);
static void XIF_CloseTx_ISR(XIF_TypeDef *Instance);
static void XIF_CloseRx_ISR(XIF_TypeDef *Instance);
void XIF_WaitBusyTimeout_ISR(XIF_TypeDef *Instance);

#ifdef LL_DMA_MODULE_ENABLED
    static DMA_ChannelETypeDef XIF_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg);
    static void XIF_DMA_DeInit(DMA_ChannelETypeDef ch);
    static void XIF_DMAReceiveCplt(XIF_TypeDef *Instance);
    static void XIF_DMATransmitCplt(XIF_TypeDef *Instance);
    static void XIF_DMAHalfTransmitCplt(XIF_TypeDef *Instance);
    static void XIF_DMAHalfReceiveCplt(XIF_TypeDef *Instance);
    static void XIF_DMATransmitError(XIF_TypeDef *Instance);
    static void XIF_DMAReceiveError(XIF_TypeDef *Instance);
#endif
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup XIF_LL_Exported_Functions XIF LL Exported Functions
  * @brief    XIF LL Exported Functions
  * @{
  */

/** @defgroup XIF_LL_Exported_Functions_Group1 XIF Init and DeInit Functions
  * @brief    XIF Init and DeInit Functions
  * @{
  */

/**
  * @brief  XIF LL Init
  * @param  Instance Specifies XIF peripheral
  * @param  user_cfg user config pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_XIF_Init(XIF_TypeDef *Instance, XIF_UserCfgTypeDef *user_cfg)
{
    XIF_HandleTypeDef *xif_hdl;
    XIF_LLCfgTypeDef  *ll_cfg;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));
    assert_param(user_cfg != NULL);

    if (!IS_XIF_ALL_INSTANCE(Instance) || user_cfg == NULL) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } else if ((xif_hdl->tx_ctrl.state != XIF_STATE_RESET) || (xif_hdl->rx_ctrl.state != XIF_STATE_RESET)) {
        LOG_E("This XIF[0x%08" PRIx32 "] is being used!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    xif_hdl->tx_ctrl.state = XIF_STATE_BUSY;
    xif_hdl->rx_ctrl.state = XIF_STATE_BUSY;

    //LL config pointer config
    LL_FUNC_ALTER(user_cfg->ll_cfg == NULL, ll_cfg = (XIF_LLCfgTypeDef *)&xif_ll_cfg_def, ll_cfg = user_cfg->ll_cfg);

    /* Init the low level hardware eg. Clock, NVIC */
    LL_XIF_MspInit(Instance);

    //Module disable and software reset
    __LL_XIF_Dis(Instance);
    __LL_XIF_Sw_Rst(Instance);

    //LL Config
    __LL_XIF_DlyChain_Set(Instance, ll_cfg->dly_chain);
    __LL_XIF_RxFIFOFullThres_Set(Instance, ll_cfg->rx_fifo_full_thres);
    __LL_XIF_BUSY_Timeout_Set(Instance, ll_cfg->busy_timeout);

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_XIF))) {
        __LL_XIF_TxFIFOEmptyThres_Set(Instance, ll_cfg->tx_fifo_empty_thres);
    }

    //User Config
    __LL_XIF_RD_HighTimeLen_Set(Instance, user_cfg->rd_high_len);
    __LL_XIF_RD_LowTimeLen_Set(Instance, user_cfg->rd_low_len);
    __LL_XIF_CONVST_LowTimeLen_Set(Instance, user_cfg->convst_low_len);
    __LL_XIF_RESET_HighTimeLen_Set(Instance, user_cfg->reset_high_len);
    __LL_XIF_RxDatCnt_Set(Instance, user_cfg->ch_per_frame);
    LL_FUNC_ALTER(user_cfg->reload_mode_en, __LL_XIF_ReloadMode_En(Instance), __LL_XIF_ReloadMode_Dis(Instance));

    //All Interrupt Pending Clear
    __LL_XIF_AllIntPnd_Clr(Instance);

    //XIF Handle Init
    xif_hdl->tx_ctrl.state = XIF_STATE_READY;
    xif_hdl->rx_ctrl.state = XIF_STATE_READY;
    xif_hdl->user_callback = user_cfg->user_callback;

#ifdef LL_DMA_MODULE_ENABLED
    xif_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    xif_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
#endif

    return LL_OK;
}

/**
  * @brief  XIF LL DeInit
  * @param  Instance Specifies XIF peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_XIF_DeInit(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));

    if (!IS_XIF_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } else if ((xif_hdl->tx_ctrl.state == XIF_STATE_BUSY_WRITE) || (xif_hdl->rx_ctrl.state == XIF_STATE_BUSY_READ)) {
        LOG_E("This XIF[0x%08" PRIx32 "] is being used!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    xif_hdl->tx_ctrl.state = XIF_STATE_BUSY;
    xif_hdl->rx_ctrl.state = XIF_STATE_BUSY;

    //XIF Module Disable
    __LL_XIF_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_XIF_MspDeInit(Instance);

    memset((void *)xif_hdl, 0, sizeof(XIF_HandleTypeDef));
    xif_hdl->tx_ctrl.state = XIF_STATE_RESET;
    xif_hdl->rx_ctrl.state = XIF_STATE_RESET;

#ifdef LL_DMA_MODULE_ENABLED
    xif_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    xif_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
#endif

    return LL_OK;
}

/**
  * @brief  XIF LL Reset
  * @param  Instance Specifies XIF peripheral
  * @return Status of the Reset
  */
LL_StatusETypeDef LL_XIF_Reset(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;
    IRQn_Type irq_num;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));

    if (!IS_XIF_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } 

    irq_num = GET_XIF_IRQ_NUMBER(Instance);
    if (irq_num < 0) {
        LOG_E("XIF IRQ does not exist!\n");
        return LL_ERROR;
    }

    //Clear pending and interrupt disable
    __disable_irq();
    CLEAR_BIT(Instance->ENABLE, 0x13UL);
    CLEAR_BIT(Instance->CTRL, 0x700F000UL);
    SET_BIT(Instance->ISR, 0x6000EUL);
    SET_BIT(Instance->ENABLE, 0x4UL);
    NVIC_ClearPendingIRQ(irq_num);
    NVIC_DisableIRQ(irq_num);
    __enable_irq();

    xif_hdl->tx_ctrl.state = XIF_STATE_BUSY;
    xif_hdl->rx_ctrl.state = XIF_STATE_BUSY;

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_XIF_MspDeInit(Instance);

    memset((void *)xif_hdl, 0, sizeof(XIF_HandleTypeDef));
    xif_hdl->tx_ctrl.state = XIF_STATE_RESET;
    xif_hdl->rx_ctrl.state = XIF_STATE_RESET;

#ifdef LL_DMA_MODULE_ENABLED
    xif_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    xif_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
#endif

    return LL_OK;
}

/**
  * @brief  Initializes the XIF MSP
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
__WEAK void LL_XIF_MspInit(XIF_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_XIF_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the XIF MSP
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
__WEAK void LL_XIF_MspDeInit(XIF_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_XIF_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Register an User XIF Callback
  * @note   User can register callback only in XIF Ready State
  * @param  Instance Specifies XIF peripheral
  * @param  CallbackID ID of the callback to be registered
  * @param  pCallback pointer to the Callback function
  * @return LL Status
  */
LL_StatusETypeDef LL_XIF_RegisterCallback(XIF_TypeDef *Instance, XIF_UserCallbackIdETypeDef CallbackID, XIF_UserCallback pCallback)
{
    XIF_HandleTypeDef *xif_hdl;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));

    if (!IS_XIF_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    }

    //Check callback pointer valid or not
    if (pCallback == NULL) {
        LOG_E("The callback pointer which to be registered is NULL!\n");
        return LL_INVALID;
    }

    //Register user callback
    switch (CallbackID) {
        case XIF_TX_CPLT_CB_ID:
            if (xif_hdl->tx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Tx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.TxCpltCallback = pCallback;
            break;

        case XIF_RX_CPLT_CB_ID:
            if (xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Rx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.RxCpltCallback = pCallback;
            break;

        case XIF_TX_HALF_CPLT_CB_ID:
            if (xif_hdl->tx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Tx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.TxHalfCpltCallback = pCallback;
            break;

        case XIF_RX_HALF_CPLT_CB_ID:
            if (xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Rx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.RxHalfCpltCallback = pCallback;
            break;

        case XIF_ERROR_CB_ID:
            if (xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Error callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.ErrorCallback = pCallback;
            break;

        default:
            LOG_E("XIF user callback ID-[%d] is Invalid!\n", CallbackID);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @brief  UnRegister an User XIF Callback
  * @note   User can unregister callback only in XIF Ready State
  * @param  Instance Specifies XIF peripheral
  * @param  CallbackID ID of the callback to be unregistered
  * @return LL Status
  */
LL_StatusETypeDef LL_XIF_UnRegisterCallback(XIF_TypeDef *Instance, XIF_UserCallbackIdETypeDef CallbackID)
{
    XIF_HandleTypeDef *xif_hdl;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));

    if (!IS_XIF_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    }

    //UnRegister user callback
    switch (CallbackID) {
        case XIF_TX_CPLT_CB_ID:
            if (xif_hdl->tx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Tx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.TxCpltCallback = NULL;
            break;

        case XIF_RX_CPLT_CB_ID:
            if (xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Rx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.RxCpltCallback = NULL;
            break;

        case XIF_TX_HALF_CPLT_CB_ID:
            if (xif_hdl->tx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Tx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.TxHalfCpltCallback = NULL;
            break;

        case XIF_RX_HALF_CPLT_CB_ID:
            if (xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Rx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.RxHalfCpltCallback = NULL;
            break;

        case XIF_ERROR_CB_ID:
            if (xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
                LOG_E("This XIF[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Error callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            xif_hdl->user_callback.ErrorCallback = NULL;
            break;

        default:
            LOG_E("XIF user callback ID-[%d] is Invalid!\n", CallbackID);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup XIF_LL_Exported_Functions_Group2 XIF Operation Functions
  * @brief    XIF Operation Functions
  * @{
  */

/**
  * @brief  XIF Transmit an amount of data in CPU blocking mode
  * @param  Instance Specifies XIF peripheral
  * @param  buf  Transmit buffer pointer
  * @param  size amount of data to be transmitted in uint16_t unit
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_XIF_Transmit_CPU(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    XIF_HandleTypeDef *xif_hdl;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_XIF_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //Check whether this function is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support XIF Blocking Transmit!\n");
        return LL_FAILED;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } else if (xif_hdl->tx_ctrl.state != XIF_STATE_READY || xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
        LOG_E("This XIF[0x%08" PRIx32 "] isn't in READY state, can't start operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    xif_hdl->tx_ctrl.state = XIF_STATE_BUSY_WRITE;
    xif_hdl->tx_ctrl.cnt = 0;
    xif_hdl->tx_ctrl.isr = NULL;
    xif_hdl->tx_ctrl.buf = buf;
    xif_hdl->tx_ctrl.size = size;

    __LL_XIF_TsfDir_Set(Instance, XIF_TSF_DIR_TX);

    //Clear TxFIFO and TX Done Pending
    __LL_XIF_TxDoneIntPnd_Clr(Instance);
    __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);
    __LL_XIF_En(Instance);
    tickstart = LL_GetTick();

    //Transmit data loop
    while (xif_hdl->tx_ctrl.cnt < xif_hdl->tx_ctrl.size) {
        //if CPU has been broken a long time by Interrupt, the TxDone flag maybe set
        if (__LL_XIF_IsTxDoneIntPnd(Instance)) {
            __LL_XIF_TxDoneIntPnd_Clr(Instance);
        }

        //Wait TxFIFO to be not full
        while (__LL_XIF_IsTxFIFOFull(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }

            //Check Error State (Wait BUSY Timeout)
            if (xif_hdl->tx_ctrl.state == XIF_STATE_ERROR || __LL_XIF_IsWaitBUSYTimeoutIntPnd(Instance)) {
                __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);
                LOG_E("Wait BUSY signal timeout!\n");
                ret = LL_ERROR;
                goto exit;
            }
        }

        //Write data to TxFIFO
        __LL_XIF_TxFIFODat_Write(Instance, *xif_hdl->tx_ctrl.buf++);
        
        xif_hdl->tx_ctrl.cnt++;
    }

    //Wait for XIF Transmit completed
    if (!__LL_XIF_IsReloadModeEn(Instance)) {
        while (!__LL_XIF_IsTxDoneIntPnd(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                ret = LL_TIMEOUT;
                goto exit;
            }
        }        
    }

    //Clear TX Done Pending
    if (__LL_XIF_IsTxDoneIntPnd(Instance)) {
        __LL_XIF_TxDoneIntPnd_Clr(Instance);
    }

    ret = LL_OK;

exit:
    //Disable XIF to stop transmit
    __LL_XIF_Dis(Instance);

    xif_hdl->tx_ctrl.state = XIF_STATE_READY;
    return ret;
}

/**
  * @brief  XIF Receive an amount of data in CPU blocking mode
  * @param  Instance Specifies XIF peripheral
  * @param  buf  Receive buffer pointer
  * @param  size amount of data to be received in uint16_t unit
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_XIF_Receive_CPU(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    XIF_HandleTypeDef *xif_hdl;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_XIF_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } else if (xif_hdl->tx_ctrl.state != XIF_STATE_READY || xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
        LOG_E("This XIF[0x%08" PRIx32 "] isn't in READY state, can't start operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    xif_hdl->rx_ctrl.state = XIF_STATE_BUSY_READ;
    xif_hdl->rx_ctrl.buf = buf;
    xif_hdl->rx_ctrl.size = size;
    xif_hdl->rx_ctrl.cnt = 0;
    xif_hdl->rx_ctrl.isr = NULL;

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        __LL_XIF_TsfDir_Set(Instance, XIF_TSF_DIR_RX);
    }

    //Enable XIF to start transmit
    __LL_XIF_RxDoneIntPnd_Clr(Instance);
    __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);
    __LL_XIF_En(Instance);
    tickstart = LL_GetTick();

    //Receive loop
    while (xif_hdl->rx_ctrl.cnt < xif_hdl->rx_ctrl.size) {
        //Wait RxFIFO to be not empty
        while (__LL_XIF_IsRxFIFOEmpty(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }

            //Check Error State (Wait BUSY Timeout)
            if (xif_hdl->rx_ctrl.state == XIF_STATE_ERROR || __LL_XIF_IsWaitBUSYTimeoutIntPnd(Instance)) {
                __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);
                LOG_E("Wait BUSY signal timeout!\n");
                ret = LL_ERROR;
                goto exit;
            }
        }

        *xif_hdl->rx_ctrl.buf++ = __LL_XIF_Dat_Read(Instance);
        xif_hdl->rx_ctrl.cnt++;
    }

    //Clear RX Done Pending
    if (__LL_XIF_IsRxDoneIntPnd(Instance)) {
        __LL_XIF_RxDoneIntPnd_Clr(Instance);
    }

    ret = LL_OK;

exit:
    //Disable XIF to stop transmit
    __LL_XIF_Dis(Instance);

    xif_hdl->rx_ctrl.state = XIF_STATE_READY;
    return ret;
}

/**
  * @brief  XIF Transmit an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies XIF peripheral
  * @param  buf  Transmit buffer pointer
  * @param  size amount of data to be transmitted in uint16_t unit
  * @return LL Status
  */
LL_StatusETypeDef LL_XIF_Transmit_IT(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size)
{
    XIF_HandleTypeDef *xif_hdl;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_XIF_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } else if (xif_hdl->tx_ctrl.state != XIF_STATE_READY || xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
        LOG_E("This XIF[0x%08" PRIx32 "] isn't in READY state, can't start operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Check whether this function is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support XIF Interrupt Transmit!\n");
        return LL_FAILED;
    }

    //Transmit config
    xif_hdl->tx_ctrl.state = XIF_STATE_BUSY_WRITE;
    xif_hdl->tx_ctrl.buf = buf;
    xif_hdl->tx_ctrl.size = size;
    xif_hdl->tx_ctrl.cnt = 0;
    xif_hdl->tx_ctrl.isr = XIF_Tx_ISR;

    __LL_XIF_TsfDir_Set(Instance, XIF_TSF_DIR_TX);

    //Clear TxFIFO and TX Done Pending
    __LL_XIF_TxDoneIntPnd_Clr(Instance);
    __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);
    __LL_XIF_En(Instance);

    //Enable TxFIFO Empty interrupt
    __LL_XIF_TxFIFOEmpty_INT_En(Instance);

    //Enable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  XIF Receive an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies XIF peripheral
  * @param  buf  Receive buffer pointer
  * @param  size amount of data to be received in uint16_t unit
  * @return LL Status
  */
LL_StatusETypeDef LL_XIF_Receive_IT(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size)
{
    XIF_HandleTypeDef *xif_hdl;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_XIF_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } else if (xif_hdl->tx_ctrl.state != XIF_STATE_READY || xif_hdl->rx_ctrl.state != XIF_STATE_READY){
        LOG_E("This XIF[0x%08" PRIx32 "] isn't in READY state, can't start operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    xif_hdl->rx_ctrl.state = XIF_STATE_BUSY_READ;
    xif_hdl->rx_ctrl.buf = buf;
    xif_hdl->rx_ctrl.size = size;
    xif_hdl->rx_ctrl.cnt = 0;
    xif_hdl->rx_ctrl.isr = XIF_Rx_ISR;

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        __LL_XIF_TsfDir_Set(Instance, XIF_TSF_DIR_RX);
    }

    //Enable XIF to start transmit
    __LL_XIF_RxDoneIntPnd_Clr(Instance);
    __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);
    __LL_XIF_En(Instance);

    //Enable RxFIFO Full interrupt
    __LL_XIF_RxFIFOFull_INT_En(Instance);

    //Enable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_En(Instance);

    return LL_OK;
}

#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  XIF Transmit an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies XIF peripheral
  * @param  buf  Transmit buffer pointer
  * @param  size amount of data to be transmitted in uint16_t unit
  * @return LL Status
  */
LL_StatusETypeDef LL_XIF_Transmit_DMA(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size)
{
    XIF_HandleTypeDef *xif_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_XIF_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } else if (xif_hdl->tx_ctrl.state != XIF_STATE_READY || xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
        LOG_E("This XIF[0x%08" PRIx32 "] isn't in READY state, can't start operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Check whether this function is supported
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        LOG_E("The chip not support XIF DMA Transmit!\n");
        return LL_FAILED;
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0x0, sizeof(dma_user_cfg));
    dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_16b;
    dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_16b;

    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == XIF) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_XIF_TX;
    } else {
        LOG_E("XIF DMA source handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Transmit Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_P2M;
    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_callback = (DMA_IRQCallback)XIF_DMATransmitCplt;
    dma_user_cfg.end_arg = Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)XIF_DMATransmitError;
    dma_user_cfg.err_arg = Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)XIF_DMAHalfTransmitCplt;
    dma_user_cfg.half_arg = Instance;

    xif_hdl->tx_ctrl.dma_ch = XIF_DMA_Init(&dma_user_cfg);

    if (xif_hdl->tx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("XIF receive request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit config
    xif_hdl->tx_ctrl.state = XIF_STATE_BUSY_WRITE;
    xif_hdl->tx_ctrl.buf = buf;
    xif_hdl->tx_ctrl.size = size;
    xif_hdl->tx_ctrl.cnt = 0;
    xif_hdl->tx_ctrl.isr = NULL;

    __LL_XIF_TsfDir_Set(Instance, XIF_TSF_DIR_TX);

    //Enable Tx DMA Requset
    __LL_XIF_TxDMA_En(Instance);

    //Enable XIF to start transmit
    __LL_XIF_TxDoneIntPnd_Clr(Instance);
    __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);
    __LL_XIF_En(Instance);

    //Enable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_En(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, xif_hdl->tx_ctrl.dma_ch, (uint32_t)&Instance->DATA, (uint32_t)buf, xif_hdl->tx_ctrl.size * 2);

    return LL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies XIF peripheral
  * @param  buf  Receive buffer pointer
  * @param  size amount of data to be received in uint16_t unit
  * @return LL Status
  */
LL_StatusETypeDef LL_XIF_Receive_DMA(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size)
{
    XIF_HandleTypeDef *xif_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_XIF_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return LL_ERROR;
    } else if (xif_hdl->tx_ctrl.state != XIF_STATE_READY || xif_hdl->rx_ctrl.state != XIF_STATE_READY) {
        LOG_E("This XIF[0x%08" PRIx32 "] isn't in READY state, can't start operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0x0, sizeof(dma_user_cfg));
    dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_16b;
    dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_16b;

    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == XIF) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_XIF_RX;
    } else {
        LOG_E("XIF DMA source handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Receive Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_P2M;
    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_callback = (DMA_IRQCallback)XIF_DMAReceiveCplt;
    dma_user_cfg.end_arg = Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)XIF_DMAReceiveError;
    dma_user_cfg.err_arg = Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)XIF_DMAHalfReceiveCplt;
    dma_user_cfg.half_arg = Instance;

    xif_hdl->rx_ctrl.dma_ch = XIF_DMA_Init(&dma_user_cfg);

    if (xif_hdl->rx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("XIF receive request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit config
    xif_hdl->rx_ctrl.state = XIF_STATE_BUSY_READ;
    xif_hdl->rx_ctrl.buf = buf;
    xif_hdl->rx_ctrl.size = size;
    xif_hdl->rx_ctrl.cnt = 0;
    xif_hdl->rx_ctrl.isr = NULL;

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        __LL_XIF_TsfDir_Set(Instance, XIF_TSF_DIR_RX);
    }

    //Enable Rx DMA Requset
    __LL_XIF_RxDMA_En(Instance);

    //Enable XIF to start transmit
    __LL_XIF_RxDoneIntPnd_Clr(Instance);
    __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);
    __LL_XIF_En(Instance);

    //Enable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_En(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, xif_hdl->rx_ctrl.dma_ch, (uint32_t)&Instance->DATA, (uint32_t)buf, xif_hdl->rx_ctrl.size * 2);

    return LL_OK;
}

#endif

/**
  * @}
  */


/** @defgroup XIF_LL_Exported_Functions_Interrupt XIF Interrupt Handler and Callback
  * @brief    XIF Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  XIF IRQ Handler
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
void LL_XIF_IRQHandler(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));

    if (!IS_XIF_ALL_INSTANCE(Instance)) {
        return;
    }

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_XIF_AllIntEn_Get(Instance);
    int_pending = __LL_XIF_AllIntPnd_Get(Instance);


    //RxFIFO Full Interrupt Handler
    if ((int_en & XIF_CTRL_RXFIE_Msk) && (int_pending & XIF_ISR_RXFI_Msk)) {
        //Interrupt Pending auto clear

        if (xif_hdl->rx_ctrl.isr) {
            xif_hdl->rx_ctrl.isr(Instance);
        }

        //Callback
        LL_XIF_RxFullCallback(Instance);
    }

    //RxFIFO Overflow Interrupt Handler
    if ((int_en & XIF_CTRL_RXOFIE_Msk) && (int_pending & XIF_ISR_RXOFI_Msk)) {
        //Clear Interrupt Pending
        __LL_XIF_RxFIFOOverflowIntPnd_Clr(Instance);

        //Callback
        LL_XIF_RxOverflowCallback(Instance);
    }

    //Rx Done Interrupt Handler
    if ((int_en & XIF_CTRL_RXDIE_Msk) && (int_pending & XIF_ISR_RXDI_Msk)) {
        //Clear Interrupt Pending
        __LL_XIF_RxDoneIntPnd_Clr(Instance);

        //Callback
        LL_XIF_RxDoneCallback(Instance);
    }

    //Wait BUSY Timeout Interrupt Handler
    if ((int_en & XIF_CTRL_BTOIE_Msk) && (int_pending & XIF_ISR_BTOI_Msk)) {
        //Clear Interrupt Pending
        __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(Instance);

        XIF_WaitBusyTimeout_ISR(Instance);

        //Callback
        LL_XIF_WaitBusyTimeoutCallback(Instance);
    }

    //The following features are available for later versions
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        return;
    }

    //TxFIFO Empty Interrupt Handler
    if ((int_en & XIF_CTRL_TXEIE_Msk) && (int_pending & XIF_ISR_TXEI_Msk)) {
        //Interrupt Pending auto clear

        if (xif_hdl->tx_ctrl.isr) {
            xif_hdl->tx_ctrl.isr(Instance);
        }

        //Callback
        LL_XIF_TxEmptyCallback(Instance);
    }

    //Tx Done Interrupt Handler
    if ((int_en & XIF_CTRL_TXDIE_Msk) && (int_pending & XIF_ISR_TXDI_Msk)) {
        //Clear Interrupt Pending
        __LL_XIF_TxDoneIntPnd_Clr(Instance);

        //Callback
        LL_XIF_TxDoneCallback(Instance);
    }

}

/**
  * @brief  XIF TxFIFO Empty Interrupt Callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
__WEAK void LL_XIF_TxEmptyCallback(XIF_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_XIF_TxEmptyCallback could be implemented in the user file
     */
}

/**
  * @brief  XIF Tx Done Interrupt Callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
__WEAK void LL_XIF_TxDoneCallback(XIF_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_XIF_TxDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  XIF RxFIFO Full Interrupt Callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
__WEAK void LL_XIF_RxFullCallback(XIF_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_XIF_RxFullCallback could be implemented in the user file
     */
}

/**
  * @brief  XIF RxFIFO Overflow Interrupt Callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
__WEAK void LL_XIF_RxOverflowCallback(XIF_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_XIF_RxOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  XIF Rx Done Interrupt Callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
__WEAK void LL_XIF_RxDoneCallback(XIF_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_XIF_RxDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  XIF Wait BUSY Timeout Interrupt Callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
__WEAK void LL_XIF_WaitBusyTimeoutCallback(XIF_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_XIF_WaitBusyTimeoutCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup XIF_LL_Private_Functions
  * @{
  */

/**
  * @brief  XIF Handle Get
  * @param  Instance Specifies XIF peripheral
  * @return XIF_HandleTypeDef pointer
  */
static XIF_HandleTypeDef *XIF_Handle_Get(XIF_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_XIF_ALL_INSTANCE(Instance));

    if (Instance == XIF) {
        return &xif_hdl_global[XIF_INSTANCE_0];
    }

    return NULL;
}

/**
  * @brief  Handle the end of the TX transaction
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_CloseTx_ISR(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Disable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_Dis(Instance);

    //Disable TxFIFO Full interrupt
    __LL_XIF_TxFIFOEmpty_INT_Dis(Instance);
    xif_hdl->tx_ctrl.isr = NULL;

    //Clear TX Done Pending
    if (__LL_XIF_IsTxDoneIntPnd(Instance)) {
        __LL_XIF_TxDoneIntPnd_Clr(Instance);
    }

    //Disable XIF to stop transmit
    __LL_XIF_Dis(Instance);

    xif_hdl->tx_ctrl.state = XIF_STATE_READY;
}

/**
  * @brief  Handle the end of the RX transaction
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_CloseRx_ISR(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Disable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_Dis(Instance);

    //Disable RxFIFO Full interrupt
    __LL_XIF_RxFIFOFull_INT_Dis(Instance);
    xif_hdl->rx_ctrl.isr = NULL;

    //Clear RX Done Pending
    if (__LL_XIF_IsRxDoneIntPnd(Instance)) {
        __LL_XIF_RxDoneIntPnd_Clr(Instance);
    }

    //Disable XIF to stop transmit
    __LL_XIF_Dis(Instance);

    xif_hdl->rx_ctrl.state = XIF_STATE_READY;
}

/**
  * @brief  Handle the data transmit in Interrupt mode
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_Tx_ISR(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Write data to TxFIFO
    if ((!__LL_XIF_IsTxFIFOFull(Instance)) && (xif_hdl->tx_ctrl.cnt < xif_hdl->tx_ctrl.size)) {
        //if TxDone flag has been set before write data to TxFIFO, clear it
        if (__LL_XIF_IsTxDoneIntPnd(Instance)) {
            __LL_XIF_TxDoneIntPnd_Clr(Instance);
        }

        __LL_XIF_TxFIFODat_Write(Instance, *xif_hdl->tx_ctrl.buf);
        xif_hdl->tx_ctrl.buf++;
        xif_hdl->tx_ctrl.cnt++;
    }

    //Write Complete
    if (xif_hdl->tx_ctrl.cnt >= xif_hdl->tx_ctrl.size) {
        //Close Tx Communication
        XIF_CloseTx_ISR(Instance);

        //Tx Complete Callback
        if (xif_hdl->user_callback.TxCpltCallback) {
            xif_hdl->user_callback.TxCpltCallback();
        }
    }
}

/**
  * @brief  Handle the data receive in Interrupt mode
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_Rx_ISR(XIF_TypeDef *Instance)
{
    //uint8_t rx_fifo_trig_lvl;
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //rx_fifo_trig_lvl = __LL_XIF_RxFIFOFullThres_Get(Instance);

    //Read data from RxFIFO
    while (!__LL_XIF_IsRxFIFOEmpty(Instance) && xif_hdl->rx_ctrl.cnt < xif_hdl->rx_ctrl.size) { //rx_fifo_trig_lvl--
        *xif_hdl->rx_ctrl.buf++ = __LL_XIF_Dat_Read(Instance);
        xif_hdl->rx_ctrl.cnt++;
    }

    //Rx Complete
    if (xif_hdl->rx_ctrl.cnt >= xif_hdl->rx_ctrl.size) {
        //Close Rx Communication
        XIF_CloseRx_ISR(Instance);

        //Rx Complete Callback
        if (xif_hdl->user_callback.RxCpltCallback) {
            xif_hdl->user_callback.RxCpltCallback();
        }
    }
}

/**
  * @brief  XIF Wait BUSY Timeout Interrupt Callback
  * @note   User must invoking LL_XIF_DeInit before reinitializing XIF when BUSY Timeout occured 
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
void XIF_WaitBusyTimeout_ISR(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Set Error State
    xif_hdl->tx_ctrl.state = XIF_STATE_ERROR;
    xif_hdl->rx_ctrl.state = XIF_STATE_ERROR;

    if (xif_hdl->tx_ctrl.isr != NULL) {                     //Interrupt Transmit on going
        //Abort Tx Communication
        XIF_CloseTx_ISR(Instance);

        if (xif_hdl->user_callback.ErrorCallback) {
            xif_hdl->user_callback.ErrorCallback();
        }
    }

    if (xif_hdl->rx_ctrl.isr != NULL) {                     //Interrupt Transmit on going
        //Abort Rx Communication
        XIF_CloseRx_ISR(Instance);

        if (xif_hdl->user_callback.ErrorCallback) {
            xif_hdl->user_callback.ErrorCallback();
        }
    }

#ifdef LL_DMA_MODULE_ENABLED

    if (xif_hdl->tx_ctrl.dma_ch != DMA_CHANNEL_INVALID) {   //DMA Transmit on going
        XIF_DMATransmitError(Instance);
    }

    if (xif_hdl->rx_ctrl.dma_ch != DMA_CHANNEL_INVALID) {   //DMA Transmit on going
        XIF_DMAReceiveError(Instance);
    }

#endif
}

#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  XIF DMA Init
  * @param  dma_user_cfg user dma config pointer
  * @return DMA_ChannelETypeDef
  */
static DMA_ChannelETypeDef XIF_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg)
{
    LL_StatusETypeDef ret;
    DMA_ChannelETypeDef ch;

    if (dma_user_cfg == NULL) {
        return DMA_CHANNEL_INVALID;
    }

    //User DMA channel request
    ch = LL_DMA_ChannelRequest();

    if (ch == DMA_CHANNEL_INVALID) {
        LOG_E("Requset DMA channel Fail!\n");
        return DMA_CHANNEL_INVALID;
    }

    //User DMA init
    ret = LL_DMA_Init(DMA, ch, dma_user_cfg);

    if (ret != LL_OK) {
        LOG_E("DMA LL init fail!\n");
        LL_DMA_ChannelRelease(ch);
        return DMA_CHANNEL_INVALID;
    }

    return ch;
}

/**
  * @brief  XIF DMA DeInit
  * @param  ch DMA channel to Deinit
  * @return None
  */
static void XIF_DMA_DeInit(DMA_ChannelETypeDef ch)
{
    if (ch == DMA_CHANNEL_INVALID) {
        return;
    }

    LL_DMA_Stop_IT(DMA, ch);
    LL_DMA_DeInit(DMA, ch);
    LL_DMA_ChannelRelease(ch);
}

/**
  * @brief  DMA XIF transmit process complete callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_DMATransmitCplt(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Disable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_Dis(Instance);

    //Disable Tx DMA Request
    __LL_XIF_TxDMA_Dis(Instance);

    //DMA DeInit
    XIF_DMA_DeInit(xif_hdl->tx_ctrl.dma_ch);
    xif_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;

    //Clear RX Done Pending
    if (__LL_XIF_IsTxDoneIntPnd(Instance)) {
        __LL_XIF_TxDoneIntPnd_Clr(Instance);
    }

    //Disable XIF to stop transmit
    __LL_XIF_Dis(Instance);

    xif_hdl->tx_ctrl.cnt = xif_hdl->tx_ctrl.size;
    xif_hdl->tx_ctrl.state = XIF_STATE_READY;

    //Rx Complete Callback
    if (xif_hdl->user_callback.TxCpltCallback) {
        xif_hdl->user_callback.TxCpltCallback();
    }
}

/**
  * @brief  DMA XIF receive process complete callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_DMAReceiveCplt(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Disable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_Dis(Instance);

    //Disable Rx DMA Request
    __LL_XIF_RxDMA_Dis(Instance);

    //DMA DeInit
    XIF_DMA_DeInit(xif_hdl->rx_ctrl.dma_ch);
    xif_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;

    //Clear RX Done Pending
    if (__LL_XIF_IsRxDoneIntPnd(Instance)) {
        __LL_XIF_RxDoneIntPnd_Clr(Instance);
    }

    //Disable XIF to stop transmit
    __LL_XIF_Dis(Instance);

    xif_hdl->rx_ctrl.cnt = xif_hdl->rx_ctrl.size;
    xif_hdl->rx_ctrl.state = XIF_STATE_READY;

    //Rx Complete Callback
    if (xif_hdl->user_callback.RxCpltCallback) {
        xif_hdl->user_callback.RxCpltCallback();
    }
}

/**
  * @brief  DMA XIF half transmit process complete callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_DMAHalfTransmitCplt(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Tx Half Complete Callback
    if (xif_hdl->user_callback.TxHalfCpltCallback) {
        xif_hdl->user_callback.TxHalfCpltCallback();
    }
}

/**
  * @brief  DMA XIF half receive process complete callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_DMAHalfReceiveCplt(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Rx Half Complete Callback
    if (xif_hdl->user_callback.RxHalfCpltCallback) {
        xif_hdl->user_callback.RxHalfCpltCallback();
    }
}

/**
  * @brief  DMA XIF transmit process error callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_DMATransmitError(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Disable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_Dis(Instance);

    //Disable Tx DMA Request
    __LL_XIF_TxDMA_Dis(Instance);

    //DMA DeInit
    XIF_DMA_DeInit(xif_hdl->tx_ctrl.dma_ch);
    xif_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;

    //Disable XIF to stop transmit
    __LL_XIF_Dis(Instance);

    xif_hdl->tx_ctrl.state = XIF_STATE_READY;

    if (xif_hdl->user_callback.ErrorCallback) {
        xif_hdl->user_callback.ErrorCallback();
    }
}

/**
  * @brief  DMA XIF receive process error callback
  * @param  Instance Specifies XIF peripheral
  * @return None
  */
static void XIF_DMAReceiveError(XIF_TypeDef *Instance)
{
    XIF_HandleTypeDef *xif_hdl;

    //XIF handle get
    xif_hdl = XIF_Handle_Get(Instance);

    if (xif_hdl == NULL) {
        LOG_E("Get XIF handle error!\n");
        return;
    }

    //Disable Wait BUSY Timeout interrupt
    __LL_XIF_WaitBusyTimeout_INT_Dis(Instance);

    //Disable Rx DMA Request
    __LL_XIF_RxDMA_Dis(Instance);

    //DMA DeInit
    XIF_DMA_DeInit(xif_hdl->rx_ctrl.dma_ch);
    xif_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;

    //Disable XIF to stop transmit
    __LL_XIF_Dis(Instance);

    xif_hdl->rx_ctrl.state = XIF_STATE_READY;

    if (xif_hdl->user_callback.ErrorCallback) {
        xif_hdl->user_callback.ErrorCallback();
    }
}

#endif

/**
  * @}
  */


#endif /* LL_XIF_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

